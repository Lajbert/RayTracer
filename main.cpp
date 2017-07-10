#include <iostream>
#include <fstream>
#include <thread>
#include <float.h>

#include "Vector3f.h"
#include "Ray.h"
#include "PhysicalObject.h"
#include "PhysicalObjectList.h"
#include "Camera.h"
#include "Metal.h"

#include <random>
#include <mutex>
#include <ctime>
#include <cstdio>

using namespace std;

// increasing this will affect render time by n*m. That is a lot!
const int IMAGE_WIDTH = 500;
const int IMAGE_HEIGHT = 500;

// every row is a work unit for the threads
const int ROW_SLICES = IMAGE_HEIGHT;

// More samples mean less noise and more accurate image. Increases render time approximately linearly.
const int NUMBER_OF_SAMPLES = 50;

// The number of logical CPU cores = number of parallel threads
const int CPU_CORES = 4;

// The maximum number of bounces that a light ray can have before forced absorbing. The effect on the render time heavily depends on the scene complexity and setup.
const int MAX_LIGHT_BOUNCES = 50;

// the final image that we will print out. This array will be filled by multiple threads, each element of the array is a Vector3f representing RGB colors.
Vector3f image[IMAGE_HEIGHT][IMAGE_WIDTH];

// this contains the thread number and row intervals that will be passed to each thread.
// this looks like: imageSlices[THREAD_NUMBER][INTERVAL_FROM] - imageSlices[THREAD_NUMBER][INTERVAL_TO]
//int imageSlices[CPU_CORES][2];

// this contains the rows still left for processing
int rowsToProcess[ROW_SLICES];

bool LOG_PROGRESS = true;

/*
 This returns the color of the pixel that the ray is sent to. It works recursively.
 First, we check if we hit anything in the scene. If we don't hit anything, we'll return the 
 color of the background. If we hit, the light ray can be absorbed, reflacted or refracted, depending on the material.
 Our light ray can be bounced at maximum MAX_LIGHT_BOUNCES times, after that we make it absorbed.
 In case of bouncing lights, we call this function recursively until we reach the bounce limit or the light is absorbed.

Vector3f Color(const Ray& ray, PhysicalObject *scene, int depth)
{
	HitData hitData;
	if (scene->Hit(ray, 0.001, FLT_MAX, hitData)) { // 0.001 to resolve shadow acne problem
		Ray scattered;
		Vector3f attenuation;
		// if the light ray is scattered, we co recursive
		if (depth < MAX_LIGHT_BOUNCES && hitData.material->Scatter(ray, hitData, attenuation, scattered)) {
			// recursive call for the next bounce, also adding the attenuation from the current bounce
			return attenuation *  Color(scattered, scene, depth + 1);
		}
		return Vector3f(0, 0, 0); // light ray absorbed
	}

	// This time, we didn't hit anything, so drawing the background.
	// Linear interpolation for the background from blue(the upper the bluer) to white (the downer the whiter). The interplation is:
	// blended_value = (1 - t) * start_value + t * end_value
	Vector3f unitDirection = UnitVector(ray.GetDirection()); // -1.0 < y < 1.0
	float t = 0.5 * (unitDirection.y() + 1.0); // 0.0 < t < 1.0
	Vector3f white(1.0, 1.0, 1.0);
	Vector3f blue(0.5, 0.7, 1.0);
	return (1.0 - t) * white + t * blue;
}
*/

Vector3f Color(const Ray& ray, PhysicalObject *scene, int depth)
{
	HitData hitData;
	if (scene->Hit(ray, 0.001, FLT_MAX, hitData)) { // 0.001 to resolve shadow acne problem
		Ray scattered;
		Vector3f attenuation;
		Vector3f emitted = hitData.material->GetEmitted(hitData.u, hitData.v, hitData.hitPoint);
		// if the light ray is scattered, we co recursive
		if (depth < MAX_LIGHT_BOUNCES && hitData.material->Scatter(ray, hitData, attenuation, scattered)) {
			// recursive call for the next bounce, also adding the attenuation from the current bounce
			return emitted + attenuation * Color(scattered, scene, depth + 1);
		}
		else {
			return emitted;
		}
		 
	}
	else {
		// light ray absorbed
		return Vector3f(0, 0, 0);
	}
}

/*
void RayTrace_backup(int startRow, int endRow, int startColumn, int endColumn, PhysicalObject* scene, Camera camera, int threadNumber) {

	for (int i = startRow - 1; i >= endRow; i--) { // row by row, from up to bottom
		for (int j = startColumn; j < endColumn; j++) { //each row is filled from left to right
			Vector3f color(0, 0, 0);
			for (int k = 0; k < NUMBER_OF_SAMPLES; k++) { // sending multiple rays to each pixel for sampling
				// we send each ray to random position in the pixel along horizontal and vertical axis
				// and then calculate an average for all the colors that we get (good for antialiasing!)
				float u = float(j + MathUtils::GetRandom()) / float(IMAGE_WIDTH);
				float v = float(i + MathUtils::GetRandom()) / float(IMAGE_HEIGHT);
				Ray ray = camera.GetRay(u, v);
				color += Color(ray, scene, 0);
			}

			color /= float(NUMBER_OF_SAMPLES);

			// gamma correction
			color = Vector3f(sqrt(color[0]), sqrt(color[1]), sqrt(color[2]));

			int red = int(255.99 * color[0]);
			int green = int(255.99 * color[1]);
			int blue = int(255.99 * color[2]);

			image[i][j] = Vector3f(red, green, blue);
		}
	}
	cout << "Thread " << threadNumber << "(" << startRow << "-" << endRow << ") finished!\n";
}

*/

/*
This function returns the number of the next row to be processed. Since multiple threads can access
it at the same time, we use a simple mutex to make sure that this number is always correct, no
rows will be processed twice and no rows will be skipped.
*/
std::mutex mtx;
int GetNextRow() {
	std::lock_guard<std::mutex> lg(mtx);
	for (int i = 0; i < ROW_SLICES; i++) {
		if (rowsToProcess[i] != -1) {
			rowsToProcess[i] = -1;
			return i;
		}
	}
	return -1;
}

/*
Actual ray tracing.
This is a work unit that can run in parallel on multiple CPU-s. The parameters are only read
and the 2D array that represents the image is also devided into different rows, each row is written
by different thread with no overlap, so there is no need to synchronize anything and don't have to worry about
thread safety when generating the pixels.
Each thread operates on different row of the image, from top to bottom.
We send multiple rays in random position in each pixel, and then we calculate the average of the colors to
set the final color.
*/
void RayTrace(PhysicalObject* scene, Camera camera) {	
	int row;
	while (true) {
		row = GetNextRow();
		if (row == -1) {
			return;
		}
		std::thread::id this_id = std::this_thread::get_id();
		for (int j = 0; j < IMAGE_WIDTH; j++) { //each row is filled from left to right
			Vector3f color(0, 0, 0);
			for (int k = 0; k < NUMBER_OF_SAMPLES; k++) { // sending multiple rays to each pixel for sampling
															// we send each ray to random position in the pixel along horizontal and vertical axis
															// and then calculate an average for all the colors that we get (good for antialiasing!)
				float u = float(j + MathUtils::GetRandom()) / float(IMAGE_WIDTH);
				float v = float(row + MathUtils::GetRandom()) / float(IMAGE_HEIGHT);
				Ray ray = camera.GetRay(u, v);
				color += Color(ray, scene, 0);
			}

			color /= float(NUMBER_OF_SAMPLES);

			// gamma correction
			color = Vector3f(sqrt(color[0]), sqrt(color[1]), sqrt(color[2]));

			int red = int(255.99 * color[0]);
			int green = int(255.99 * color[1]);
			int blue = int(255.99 * color[2]);

			image[row][j] = Vector3f(red, green, blue);
		}
		if (LOG_PROGRESS) {
			cout << 100 * (float)((float)row / (float)IMAGE_HEIGHT) << "%..." << endl;
		}
		//cout << "Row " << row << " in thread " << this_id << " finished!\n";
	}
}

/*
 Cheap solution for slicing the image rows to different intervals for multithreading.
 Each thread will operate on different (and equal) row intervals, we don't devide columns.

void SliceImageToCPUCores() {
	int unit = IMAGE_HEIGHT / CPU_CORES;
	int previousEnd = IMAGE_HEIGHT;
	for (int i = CPU_CORES - 1; i >= 0; i--) {
		int start = previousEnd;
		int end = i * unit;
		previousEnd = end;
		imageSlices[i][0] = start;
		imageSlices[i][1] = end;
	}
}
*/

/*
Each row is going to be calculated by a different thread, so we are creating an array to know which row has been 
processed already.
*/
void CreateRowSlices() {
	for (int i = 0; i < IMAGE_HEIGHT; i++) {
		rowsToProcess[i] = i;
	}
}


int main() {

	PhysicalObject* scene = PhysicalObjectList::CornellBox();

	// setting up the camera
	Vector3f lookFrom(278, 278, -800);
	Vector3f lookAt(278, 278, 0);
	float distanceToFocus = 10;
	float aperture = 0;
	float fieldOfView = 40;
	Camera camera(lookFrom, lookAt, Vector3f(0, 1, 0), fieldOfView, float(IMAGE_WIDTH) / float(IMAGE_HEIGHT), aperture, distanceToFocus, 0.0, 1.0);

	CreateRowSlices();

	cout << "Starting rendering...\n";

	/*
	We create an array as big as the number of CPU cores, each element will be a thread
	This is necessary, because in standard C++, threads start running automatically as soon as they are created
	and we need to keep store them to be able to call join() function on them on the next iteration.
	The following code wouldn't work:

	for (int i = CPU_CORES - 1; i >= 0; i--) {
	// create the thread
	thread t(RayTrace, imageSlices[i][0], imageSlices[i][1], scene, camera, i);

	// and stop the execution of the main thread immediately with the join(), meaining that main thread (thus the for loop )
	// will wait until the t finishes the execution and only then it will start the next thread, which will stop the main thread again...
	// and it goes on, so the execution will only happen on one thread at a time sequentially without paralellism
	t.join();
	}
	This is why we need to create and start all the threads first, and call the join() only after all of them are
	created and running the main thread will only stops execion when the rendering threads are running and won't start
	writing the file untill all have retunred.
	*/

	// to keep of the threads
	thread threads[CPU_CORES];
	// creating the threads will make them run immediately, but we don't call .join() just yet to let the main thread execute untils
	// all of the worker threads are created
	clock_t begin = clock();
	for (int i = CPU_CORES - 1; i >= 0; i--) {
		threads[i] = thread(RayTrace, scene, camera);
	}

	// when all threads are created, we will call .join() on each of them so the main thread will until all finishes, so it won't start
	// writing an unfinished image to the file
	for (int i = CPU_CORES - 1; i >= 0; i--) {
		threads[i].join();
	}

	clock_t end = clock();
	double elapsed_secs = double(end - begin) / CLOCKS_PER_SEC;

	cout << "Rendering finished in " << (elapsed_secs / 60) << " minutes, writing file...\n";

	// writing the image to a simple PPM file. The most simple image file format, just google it if you don't know.
	ofstream myfile;
	myfile.open("image_mac.ppm");

	myfile << "P3\n" << IMAGE_WIDTH << " " << IMAGE_HEIGHT -1 << "\n255\n";

	// each RGB value will be printed to the file from the array.
	for (int i = IMAGE_HEIGHT - 1; i > 0; i--) {
		for (int j = 0; j < IMAGE_WIDTH; j++) {
			Vector3f color = image[i][j]; // color of the pixel
			myfile << color.r() << " " << color.g() << " " << color.b() << "\n";
		}
	}
	myfile.close();

	cout << "Finished writing file, press ENTER to exit...";

	return 0;
}