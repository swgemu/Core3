#include <math.h>

#include "TreeNode.h"

#include "server/zone/TreeEntry.h"
#include "server/zone/QuadTree.h"
#include "server/zone/OctTree.h"
#include "server/zone/objects/scene/SceneObject.h"

#define NO_ENTRY_REF_COUNTING

using namespace server::zone;

TreeNode::TreeNode() {
	objects.setNoDuplicateInsertPlan();

	minX = 0, minY = 0, minZ = 0, maxX = 0, maxY = 0, maxZ = 0;

	dividerX = 0, dividerY = 0,	dividerZ = -1;
}

TreeNode::TreeNode(float minx, float miny, float minz, float maxx, float maxy, float maxz, TreeNode *parent) {
	objects.setNoDuplicateInsertPlan();

	parentNode = parent;

	minX = minx;
	minY = miny;
	minZ = minz;
	maxX = maxx;
	maxY = maxy;
	maxZ = maxz;

	if (!validateNode() || minX > maxX || minY > maxY || minZ > maxZ) {
		StringBuffer msg;
		msg << "[OctTree] invalid node in create - " << toStringData();
		Logger::console.error(msg);
	}

	dividerX = (minX + maxX) / 2;
	dividerY = (minY + maxY) / 2;
	dividerZ = (minZ + maxZ) / 2;
}

TreeNode::TreeNode(float minx, float miny, float maxx, float maxy, TreeNode *parent) {
	objects.setNoDuplicateInsertPlan();

	parentNode = parent;
	minX = minx;
	minY = miny;
	maxX = maxx;
	maxY = maxy;
	dividerZ = -1.f;

	if (!validateNode() || minX > maxX || minY > maxY) {
	StringBuffer msg;
		msg << "[QuadTree] invalid node in create - " << toStringData();
		Logger::console.error(msg);
	}

	dividerX = (minX + maxX) / 2;
	dividerY = (minY + maxY) / 2;
}

TreeNode::~TreeNode() {
}

void TreeNode::addObject(TreeEntry *obj) {
	/*if (dividerZ != -1 && OctTree::doLog())
		Logger::console.info(true) << hex << "object [" << obj->getObjectID() <<  "] added to OctTree"
		<< toStringData() << "\n";
	else if (dividerZ == 0 && QuadTree::doLog())
		Logger::console.info(true) << hex << "object [" << obj->getObjectID() <<  "] added to QuadTree"
		<< toStringData() << "\n";
	*/

	if (!validateNode())
		Logger::console.error() << "[TreeNode] invalid node in addObject() - " << toStringData() << "\n";

	objects.put(obj);
	obj->setNode(this);
}

void TreeNode::removeObject(TreeEntry* obj) {


	if (!objects.drop(obj)) {
		Logger::console.info(true) << "TreeNode::removeObject -- Object ID: " << obj->getObjectID() <<  "] not found on Tree" << toStringData() << "\n";
	} else {
		obj->setNode(nullptr);

		if (OctTree::doLog()) {
			SceneObject* sceneO = cast<SceneObject*>(obj);

			if (sceneO != nullptr && dividerX != 0) {
				//Logger::console.info(true) << "TreeNode::removeObject -- OctTree Object ID: " << sceneO->getObjectID() << " " << sceneO->getDisplayedName() <<  " - removed object from Oct Tree Node: " << toStringData() << "\n";
			}
		}
	}
}

void TreeNode::removeObject(int index) {
	//Logger::console.info(true) << "TreeNode::removeObject by index #" << index;

	TreeEntry* obj = objects.remove(index);
	obj->setNode(nullptr);
}

bool TreeNode::testInsideQuadTree(TreeEntry* obj) const {
	float x = obj->getPositionX();
	float y = obj->getPositionY();

	//Logger::console.info(true) << "TreeNode::testInsideQuadTree called - X = " << x << " Y = " << y;
	//Logger::console.info(true) << " minX = " << minX << " maxX = " << maxX << " minZ = " << minZ << " maxZ = " << maxZ << " minY = " << minY << " maxY = " << maxY;

	return x >= minX && x <= maxX && y >= minY && y <= maxY;
}

bool TreeNode::testInsideOctTree(TreeEntry* obj) const {
	float x = obj->getPositionX();
	float y = obj->getPositionY();
	float z = obj->getPositionZ();

	//Logger::console.info(true) << "TreeNode::testInsideOctTree called - X = " << x << " Z = " << z << " Y = " << y;
	//Logger::console.info(true) << " minX = " << minX << " maxX = " << maxX << " minZ = " << minZ << " maxZ = " << maxZ << " minY = " << minY << " maxY = " << maxY;

	return x >= minX && x <= maxX && y >= minY && y <= maxY && z >= minZ && z <= maxZ;
}

bool TreeNode::testInRange(float x, float y, float z, float range) const {
	bool insideX = (minX <= x) && (x < maxX);
	bool insideY = (minY <= y) && (y < maxY);
	bool insideZ = (minZ <= z) && (z < maxZ);

	if (insideX && insideY && insideZ) {
		return true;
	}

	bool closeenoughX = (fabs(minX - x) < range || fabs(maxX - x) < range);
	bool closeenoughY = (fabs(minY - y) < range || fabs(maxY - y) < range);
	bool closeenoughZ = (fabs(minZ - z) < range || fabs(maxZ - z) < range);

	if ((insideX || closeenoughX) && (insideY || closeenoughY) && (insideZ || closeenoughZ)) {
		return true;
	}

	return false;
}

bool TreeNode::testInRange(float x, float y, float range) const {
	bool insideX = (minX <= x) && (x < maxX);
	bool insideY = (minY <= y) && (y < maxY);

	if (insideX && insideY)
		return true;

	bool closeenoughX = (fabs(minX - x) <= range || fabs(maxX - x) <= range);
	bool closeenoughY = (fabs(minY - y) <= range || fabs(maxY - y) <= range);

	if ((insideX || closeenoughX) && (insideY || closeenoughY))
		return true;
	else
		return false;
}

void TreeNode::check () {
	Reference<TreeNode*> parentNode = this->parentNode.get();

	if (isEmpty() && !hasSubNodes() && parentNode != nullptr) {
		if (parentNode->nwNode == this)
			parentNode->nwNode = nullptr;
		else if (parentNode->neNode == this)
			parentNode->neNode = nullptr;
		else if (parentNode->swNode == this)
			parentNode->swNode = nullptr;
		else if (parentNode->seNode == this)
			parentNode->seNode = nullptr;
		else if (parentNode->nwNode2 == this)
			parentNode->nwNode2 = nullptr;
		else if (parentNode->neNode2 == this)
			parentNode->neNode2 = nullptr;
		else if (parentNode->swNode2 == this)
			parentNode->swNode2 = nullptr;
		else if (parentNode->seNode2 == this)
			parentNode->seNode2 = nullptr;

		//if (OctTree::doLog())
			//Logger::console.info(true) << "deleting node (" << this << ")\n";

		//delete this;
	}
}

String TreeNode::toStringData() {
	StringBuffer s;
	s << " Node " << this << " (" << (int) minX << ","
			<< (int) minY << "," << (int) minZ << "," << (int) maxX << "," << (int) maxY << ","
			<< (int) maxZ << ") [" << objects.size() << "]";

	return s.toString();
}
