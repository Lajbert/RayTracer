#include "BVHNode.h"
#include "MathUtils.h"
#include "PhysicalObjectList.h"


static int compareBoxesX(const void * a, const void * b)
{
	BoundingBox leftBox;
	BoundingBox rightBox;
	PhysicalObject * ah = *(PhysicalObject**)a;
	PhysicalObject * bh = *(PhysicalObject**)b;
	if (!ah->BoundingBoxHit(0, 0, leftBox) || !bh->BoundingBoxHit(0, 0, rightBox)) {
		std::cerr << "No bounding box in BVHNode constructor\n";
	}
	if (leftBox.GetMin().x() - rightBox.GetMin().x() < 0.0) {
		return -1;
	}
	return 1;
}

static int compareBoxesY(const void * a, const void * b)
{
	BoundingBox leftBox;
	BoundingBox rightBox;
	PhysicalObject * ah = *(PhysicalObject**)a;
	PhysicalObject * bh = *(PhysicalObject**)b;
	if (!ah->BoundingBoxHit(0, 0, leftBox) || !bh->BoundingBoxHit(0, 0, rightBox)) {
		std::cerr << "No bounding box in BVHNode constructor\n";
	}
	if (leftBox.GetMin().y() - rightBox.GetMin().y() < 0.0) {
		return -1;
	}
	return 1;
}

static int compareBoxesZ(const void * a, const void * b)
{
	BoundingBox leftBox;
	BoundingBox rightBox;
	PhysicalObject * ah = *(PhysicalObject**)a;
	PhysicalObject * bh = *(PhysicalObject**)b;
	if (!ah->BoundingBoxHit(0, 0, leftBox) || !bh->BoundingBoxHit(0, 0, rightBox)) {
		std::cerr << "No bounding box in BVHNode constructor\n";
	}
	if (leftBox.GetMin().z() - rightBox.GetMin().z() < 0.0) {
		return -1;
	}
	return 1;
}

BVHNode::BVHNode(PhysicalObject ** list, int n, float startTime, float endTime)
{
	int axis = int(3 * MathUtils::GetRandom());
	if (axis == 0) {
		qsort(list, n, sizeof(PhysicalObject *), compareBoxesX);
	}
	else if (axis == 1) {
		qsort(list, n, sizeof(PhysicalObject *), compareBoxesY);
	}
	else 
	{
		qsort(list, n, sizeof(PhysicalObject *), compareBoxesZ);
	}
	if (n == 1) {
		leftChild = list[0];
		rightChild = list[0];
	}
	else if (n == 2) {
		leftChild = list[0];
		rightChild = list[1];
	}
	else {
		leftChild = new BVHNode(list, n / 2, startTime, endTime);
		rightChild = new BVHNode(list + n / 2, n - n/2, startTime, endTime);
	}
	BoundingBox leftBox;
	BoundingBox rightBox;
	if (!leftChild->BoundingBoxHit(startTime, endTime, leftBox) || !rightChild->BoundingBoxHit(startTime, endTime, rightBox)) {
		std::cerr << "no bounding box in BVHNode constructor!\n";
	}
	boundingBox = MathUtils::GetSurroundingBox(leftBox, rightBox);
}

bool BVHNode::Hit(const Ray & ray, float minTolerance, float maxTolerance, HitData & data) const
{
	if (boundingBox.Hit(ray, minTolerance, maxTolerance)) {
		HitData leftData;
		HitData rightData;

		bool hitLeft = leftChild->Hit(ray, minTolerance, maxTolerance, leftData);
		bool hitRight = rightChild->Hit(ray, minTolerance, maxTolerance, rightData);

		if (hitLeft && hitRight) {
			if (leftData.t < rightData.t) {
				data = leftData;
			}
			else {
				data = rightData;
			}
			return true;
		}
		else if (hitLeft) {
			data = leftData;
			return true;
		}
		else if (hitRight) {
			data = rightData;
			return true;
		}

		return false;
	}
	return false;
}

bool BVHNode::BoundingBoxHit(float startTime, float endTime, BoundingBox & box) const
{
	box = boundingBox;
	return true;
}
