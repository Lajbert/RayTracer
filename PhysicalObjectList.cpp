#include "PhysicalObjectList.h"
#include "Sphere.h"
#include "MathUtils.h"
#include "Lambert.h"
#include "Metal.h"
#include "Dialectric.h"
#include "CheckerTexture.h"
#include "UniformColorTexture.h"
#include "MovingSphere.h"
#include "BVHNode.h"
#include "NoiseTexture.h"
#include "DiffuseLight.h"
#include "Rectangle.h"
#include "NormalFlipper.h"
#include "Box.h"
#include "Translate.h"
#include "Rotate.h"

PhysicalObjectList::PhysicalObjectList(PhysicalObject ** list, int size)
{
	this->list = list;
	this->size = size;
}

bool PhysicalObjectList::Hit(const Ray & ray, float minTolerance, float maxTolerance, HitData& hitData) const
{
	HitData tmpData;
	bool hit = false;
	float closestHit = maxTolerance;
	
	for (int i = 0; i < size; i++) {
		if (list[i]->Hit(ray, minTolerance, closestHit, tmpData)) {
			hit = true;
			closestHit = tmpData.t;
			hitData = tmpData;
		}
	}

	return hit;
}

PhysicalObject * PhysicalObjectList::RandomScene()
{
	int n = 500;
	PhysicalObject** list = new PhysicalObject*[n + 1];
	Texture* checker = new CheckerTexture(new UniformColorTexture(Vector3f(0, 0, 0)), new UniformColorTexture(Vector3f(1, 1, 1)));
	list[0] = new Sphere(Vector3f(0, -1000, 0), 1000, new Lambert(checker));
	int i = 1;
	for (int a = -11; a < 11; a++) {
		for (int b = -11; b < 11; b++) {
			float chooseMat = MathUtils::GetRandom();
			Vector3f center(a + 0.9 * MathUtils::GetRandom(), 0.2, b + 0.9 * MathUtils::GetRandom());
			if ((center - Vector3f(4, 0.2, 0)).GetLength() > 0.9) {
				if (chooseMat < 0.8) { // diffuses
					list[i++] = new MovingSphere(center, center + Vector3f(0, 0.5 * MathUtils::GetRandom(), 0), 0.0, 1.0, 0.2, new Lambert(new UniformColorTexture(Vector3f(MathUtils::GetRandom() * MathUtils::GetRandom(), MathUtils::GetRandom() * MathUtils::GetRandom(), MathUtils::GetRandom() * MathUtils::GetRandom()))));
					//list[i++] = new Sphere(center, 0.2, new Lambert(new UniformColorTexture(Vector3f(MathUtils::GetRandom() * MathUtils::GetRandom(), MathUtils::GetRandom() * MathUtils::GetRandom(), MathUtils::GetRandom() * MathUtils::GetRandom()))));
				}
				else if (chooseMat < 0.95) { // metal
					list[i++] = new Sphere(center, 0.2, new Metal(Vector3f(0.5 * (1 + MathUtils::GetRandom()), 0.5 * (1 + MathUtils::GetRandom()), 0.5 * (1 + MathUtils::GetRandom())), 0.5 * MathUtils::GetRandom()));
				}
				else { // glass
					Vector3f glassColor = Vector3f(MathUtils::GetRandom(), MathUtils::GetRandom(), MathUtils::GetRandom());
					if (i % 2 == 0) {
						glassColor = Vector3f(1.0, 1.0, 1.0);
					}
					list[i++] = new Sphere(center, 0.2, new Dialectric(1.5, glassColor));
				}
			}
		}
	}
	list[i++] = new Sphere(Vector3f(0, 1, 0), 1.0, new Dialectric(1.5));
	list[i++] = new Sphere(Vector3f(-4, 1, 0), 1.0, new Lambert(new UniformColorTexture(Vector3f(0.4, 0.2, 0.1))));
	list[i++] = new Sphere(Vector3f(4, 1, 0), 1.0, new Metal(Vector3f(0.7, 0.6, 0.5), 0.0));
	
	return new BVHNode(list, i, 0.0, 1.0);
	//return new PhysicalObjectList(list, i);
}

PhysicalObject * PhysicalObjectList::SmallScene()
{
	PhysicalObject** objects = new PhysicalObject*[5];
	objects[0] = new Sphere(Vector3f(0, 0, -1), 0.5, new Lambert(new UniformColorTexture(Vector3f(0.8, 0.3, 0.3))));
	objects[1] = new Sphere(Vector3f(0, -100.5, -1), 100, new Lambert(new UniformColorTexture(Vector3f(0.8, 0.8, 0.0))));
	objects[2] = new Sphere(Vector3f(1, 0, -1), 0.5, new Metal(Vector3f(0.8, 0.6, 0.2), 0.1));
	Vector3f glassColor = Vector3f(MathUtils::GetRandom(), MathUtils::GetRandom(), MathUtils::GetRandom());
	objects[3] = new Sphere(Vector3f(-1, 0, -1), 0.5, new Dialectric(1.5, glassColor));
	objects[4] = new Sphere(Vector3f(-1, 0, -1), -0.45, new Dialectric(1.5, glassColor));
	return new PhysicalObjectList(objects, 5);
}

PhysicalObject * PhysicalObjectList::PerlinSpheres()
{
	Texture *perlinTexture = new NoiseTexture(4);
	PhysicalObject ** list = new PhysicalObject*[2];
	list[0] = new Sphere(Vector3f(0, -1000, 0), 1000, new Lambert(perlinTexture));
	list[1] = new Sphere(Vector3f(0, 2, 0), 2, new Lambert(perlinTexture));
	return new PhysicalObjectList(list, 2);
}

PhysicalObject * PhysicalObjectList::SimpleLight() {
	Texture * perlinTexture = new NoiseTexture(4);
	PhysicalObject ** list = new PhysicalObject*[4];
	list[0] = new Sphere(Vector3f(0, -1000, 0), 1000, new Lambert(perlinTexture));
	list[1] = new Sphere(Vector3f(0, 2, 0), 2, new Lambert(perlinTexture));
	//list[2] = new Sphere(Vector3f(0, 7, 0), 2, new DiffuseLight(new ConstantTexture(Vector3f(4, 4, 4))));
	list[2] = new Sphere(Vector3f(0, 7, 0), 2, new Lambert(perlinTexture));
	list[3] = new XYRectangle(3, 5, 1, 3, -2, new DiffuseLight(new UniformColorTexture(Vector3f(4, 4, 4))));
	return new PhysicalObjectList(list, 4);
}

PhysicalObject * PhysicalObjectList::CornellBox()
{
	PhysicalObject ** list = new PhysicalObject*[8];
	int i = 0;
	Material * red = new Lambert(new UniformColorTexture(Vector3f(0.65, 0.05, 0.05)));
	Material * white = new Lambert(new UniformColorTexture(Vector3f(0.73, 0.73, 0.73)));
	Material * green = new Lambert(new UniformColorTexture(Vector3f(0.12, 0.45, 0.15)));
	Material * light = new DiffuseLight(new UniformColorTexture(Vector3f(15, 15, 15)));
	list[i++] = new NormalFlipper(new YZRectangle(0, 555, 0, 555, 555, green));
	list[i++] = new YZRectangle(0, 555, 0, 555, 0, red);
	list[i++] = new XZRectangle(213, 343, 227, 332, 554.9, light);
	list[i++] = new NormalFlipper(new XZRectangle(0, 555, 0, 555, 555, white));
	list[i++] = new XZRectangle(0, 555, 0, 555, 0, white);
	list[i++] = new NormalFlipper(new XYRectangle(0, 555, 0, 555, 555, white));
	list[i++] = new Translate(new YRotate(new Box(Vector3f(0, 0, 0), Vector3f(165, 165, 165), white), -18), Vector3f(130, 0, 65));
	list[i++] = new Translate(new YRotate(new Box(Vector3f(0, 0, 0), Vector3f(165, 330, 165), white), 15), Vector3f(265, 0, 295));
	return new PhysicalObjectList(list, i);
}

bool PhysicalObjectList::BoundingBoxHit(float startTime, float endTime, BoundingBox & box) const
{
	if (this->size < 1) {
		return false;
	}
	BoundingBox tempBox;
	bool firstTrue = list[0]->BoundingBoxHit(startTime, endTime, tempBox);
	if (!firstTrue) {
		return false;
	}
	box = tempBox;
	for (int i = 1; i < this->size; i++) {
		if (list[0]->BoundingBoxHit(startTime, endTime, tempBox)) {
			box = MathUtils::GetSurroundingBox(box, tempBox);
		} else {
			return false;
		}
	}
	return true;
}
