#include <math.h>

#include "TreeNode.h"

#include "server/zone/TreeEntry.h"
#include "server/zone/QuadTree.h"
#include "server/zone/Octree.h"
#include "server/zone/objects/scene/SceneObject.h"

#define NO_ENTRY_REF_COUNTING

using namespace server::zone;

TreeNode::TreeNode() {
	objects.setNoDuplicateInsertPlan();

	nodeType = TreeNode::QUADTREE_NODE;

	minX = 0.f, minY = 0.f, minZ = 0.f, maxX = 0.f, maxY = 0.f, maxZ = 0.f;

	dividerX = 0.f, dividerY = 0.f,	dividerZ = 0.f;

	centerX = 0.f, centerY = 0.f, centerZ = 0.f, radius = 0.f;
}

// Octree node
TreeNode::TreeNode(float minx, float miny, float minz, float maxx, float maxy, float maxz, TreeNode* parent) {
	objects.setNoDuplicateInsertPlan();

	parentNode = parent;

	minX = minx;
	minY = miny;
	minZ = minz;
	maxX = maxx;
	maxY = maxy;
	maxZ = maxz;

	nodeType = TreeNode::OCTREE_NODE;

	if (!validateNode() || minX > maxX || minY > maxY || minZ > maxZ) {
		StringBuffer msg;
		msg << "[Octree] invalid node in create - " << toStringData();
		Logger::console.error(msg);
	}

	dividerX = (minX + maxX) / 2;
	dividerY = (minY + maxY) / 2;
	dividerZ = (minZ + maxZ) / 2;

	setBoundingSphere();
}

// Quadtree node
TreeNode::TreeNode(float minx, float miny, float maxx, float maxy, TreeNode *parent) {
	objects.setNoDuplicateInsertPlan();

	parentNode = parent;
	minX = minx;
	minY = miny;
	maxX = maxx;
	maxY = maxy;
	dividerZ = 0.f;

	nodeType = TreeNode::QUADTREE_NODE;

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

void TreeNode::addObject(TreeEntry* obj) {
	if (!validateNode()) {
		Logger::console.error() << "[TreeNode] invalid node in addObject() - " << toStringData() << "\n";
	}

#ifdef DEBUG_TREE_NODE
	SceneObject* sceneO = cast<SceneObject*>(obj);

	if (sceneO != nullptr && sceneO->isPlayerShip()) {
		if (obj->getNode() != nullptr) {
			auto oldNode = obj->getNode();

			Logger::console.info(true) << "\033[42;30m" << " Player ship is already assigned to a tree node!!! Old Node: " << oldNode->toStringData()<< "\n" << "\033[0m";
		}

		Logger::console.info(true) << "\033[42;30m" << __FUNCTION__ << "() -- ADDED Octree Object ID: " << sceneO->getObjectID() << " " << sceneO->getDisplayedName() <<  " - Octree Node: " << toStringData() << "\n" << "\033[0m";

		// StackTrace::printStackTrace();
	}
#endif // DEBUG_TREE_NODE

	objects.put(obj);
	obj->setNode(this);
}

void TreeNode::removeObject(TreeEntry* obj) {
	if (!objects.drop(obj)) {
		Logger::console.error() << "TreeNode::removeObject -- Object ID: " << obj->getObjectID() <<  "] not found on Tree" << toStringData() << "\n";
		return;
	}

	obj->setNode(nullptr);

#ifdef DEBUG_TREE_NODE
	SceneObject* sceneO = cast<SceneObject*>(obj);

	if (sceneO != nullptr && sceneO->isPlayerShip()) {
		Logger::console.info(true) << "\033[42;30m" << __FUNCTION__ << "() -- REMOVED Octree Object ID: " << sceneO->getObjectID() << " " << sceneO->getDisplayedName() <<  " - Octree Node: " << toStringData() << "\n" << "\033[0m";
	}
#endif // DEBUG_TREE_NODE
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

bool TreeNode::testInsideOctree(TreeEntry* obj) const {
	float x = obj->getPositionX();
	float y = obj->getPositionY();
	float z = obj->getPositionZ();

	bool ret = ((x > minX) && (x < maxX) && (y > minY) && (y < maxY) && (z > minZ) && (z < maxZ));

#ifdef DEBUG_TREE_NODE_AI
	SceneObject* scno = cast<SceneObject*>(obj);

	if (!ret && scno->isShipAiAgent()) {
		Logger::console.info(true) << "TreeNode::testInsideOctree[" << obj->getObjectID() << "] - X = " << x << " Z = " << z << " Y = " << y << " " << " Node -- " << nodeName << " - " <<
		" (Min X: " << (int)minX << ", Min Y: " << (int)minY << ", Min Z: " << (int)minZ <<
		", Max X: " << (int)maxX << ", Max Y: " << (int)maxY << ", Max Z: " << (int)maxZ << ")" <<
		"[Total Objects in Node: " << objects.size() << "]";
	}
#endif // DEBUG_TREE_NODE_AI

	return ret;
}

bool TreeNode::testInRange(float x, float y, float z, float range) const {
	float distance = range + radius;
	return squaredDistanceToCenter(x,y,z) <= (distance * distance);
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

void TreeNode::setBoundingSphere() {
	if (nodeType == TreeNode::OCTREE_NODE) {
		centerX = (maxX - minX) * 0.5f;
		centerY = (maxY - minY) * 0.5f;
		centerZ = (maxZ - minZ) * 0.5f;
		radius = sqrtf(centerX*centerX + centerY*centerY + centerZ*centerZ);
	} else {
		/* unused variable in quadtree
		centerX = (maxX - minX) * 0.5f;
		centerY = (maxY - minY) * 0.5f;
		radius = sqrtf(centerX*centerX + centerY*centerY);*/
	}
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

		//if (Octree::doLog())
			//Logger::console.info(true) << "deleting node (" << this << ")\n";

		//delete this;
	}
}

String TreeNode::toStringData() {
	StringBuffer msg;
	msg <<
	" Node -- Type: " << nodeType << " - " <<
	" (Min X: " << (int)minX << ", Min Y: " << (int)minY << ", Min Z: " << (int)minZ <<
	", Max X: " << (int)maxX << ", Max Y: " << (int)maxY << ", Max Z: " << (int)maxZ << ")" <<
	"[Total Objects in Node: " << objects.size() << "]";

	return msg.toString();
}
