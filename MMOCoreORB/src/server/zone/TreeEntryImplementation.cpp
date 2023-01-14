/*
Copyright (C) 2007 <SWGEmu>. All rights reserved.
Distribution of this file for usage outside of Core3 is prohibited.
*/

#include <autogen/server/zone/ZoneServer.h>
#include "server/zone/TreeEntry.h"
#include "server/zone/TreeNode.h"
#include "server/zone/objects/scene/SceneObject.h"
#include "server/zone/objects/tangible/TangibleObject.h"

//#define DEBUG_TREE_ENTRY

TreeEntryImplementation::TreeEntryImplementation(TreeNode *n) {
	node = n;
	bounding = false;

	//visibilityRange = 128;

	closeobjects = nullptr;

	//closeobjects.setInsertPlan(SortedVector<TreeEntry*>::NO_DUPLICATE);

	radius = 0.5f;

	receiverFlags = 0;
}

void TreeEntryImplementation::setNode(TreeNode *n) {
	node = n;
}

bool TreeEntryImplementation::containsPoint(float px, float py) {
#ifdef DEBUG_TREE_ENTRY
	Logger::console.info(true) << "TreeEntryImplementation::containsPoint";
#endif

	return (((px - getPositionX()) * (px - getPositionX())) + ((py - getPositionY()) * (py - getPositionY())) <= radius * radius );
}

bool TreeEntryImplementation::containsPoint(float px, float py, float pz) {
#ifdef DEBUG_TREE_ENTRY
	Logger::console.info(true) << "TreeEntryImplementation::containsPoint";
#endif

	float deltaX = px - getPositionX();
	float deltaY = py - getPositionY();
	float deltaZ = pz - getPositionZ();
	int radiusSq = radius * radius;

	return ((deltaX * deltaX) + (deltaY * deltaY) + (deltaZ * deltaZ)) <= radiusSq;
}

bool TreeEntryImplementation::isInSWArea(TreeNode *node) const {
#ifdef DEBUG_TREE_ENTRY
	Logger::console.Logger::console.info(true) << "TreeEntryImplementation::isInSWArea -- Divider Z: " << node->dividerZ;
#endif

	if (node->dividerZ != 0)
		return coordinates.getPositionX() >= node->minX && coordinates.getPositionX() < node->dividerX &&
			coordinates.getPositionY() >= node->minY && coordinates.getPositionY() < node->dividerY &&
				coordinates.getPositionZ() >= node->minZ && coordinates.getPositionZ() < node->dividerZ;

	else
		return coordinates.getPositionX() >= node->minX && coordinates.getPositionX() < node->dividerX &&
			coordinates.getPositionY() >= node->minY && coordinates.getPositionY() < node->dividerY;
}

bool TreeEntryImplementation::isInSEArea(TreeNode* node) const {
#ifdef DEBUG_TREE_ENTRY
	Logger::console.info(true) << "TreeEntryImplementation::isInSEArea -- Divider Z: " << node->dividerZ;
#endif

	if (node->dividerZ != 0)
		return coordinates.getPositionX() >= node->dividerX && coordinates.getPositionX() < node->maxX &&
			coordinates.getPositionY() >= node->minY && coordinates.getPositionY() < node->dividerY &&
				coordinates.getPositionZ() >= node->minZ && coordinates.getPositionZ() < node->dividerZ;
	else
		return coordinates.getPositionX() >= node->dividerX && coordinates.getPositionX() < node->maxX &&
			coordinates.getPositionY() >= node->minY && coordinates.getPositionY() < node->dividerY;
}

bool TreeEntryImplementation::isInNWArea(TreeNode* node) const {
#ifdef DEBUG_TREE_ENTRY
	Logger::console.info(true) << "TreeEntryImplementation::isInNEArea -- Divider Z: " << node->dividerZ;
#endif

	if (node->dividerZ != 0)
		return coordinates.getPositionX() >= node->minX && coordinates.getPositionX() < node->dividerX &&
			coordinates.getPositionY() >= node->dividerY && coordinates.getPositionY() < node->maxY &&
				coordinates.getPositionZ() >= node->minZ && coordinates.getPositionZ() < node->dividerZ;
	else
		return coordinates.getPositionX() >= node->minX && coordinates.getPositionX() < node->dividerX &&
			coordinates.getPositionY() >= node->dividerY && coordinates.getPositionY() < node->maxY;
}

bool TreeEntryImplementation::isInNEArea(TreeNode* node) const {
#ifdef DEBUG_TREE_ENTRY
	Logger::console.info(true) << "TreeEntryImplementation::isInNEArea -- Divider Z: " << node->dividerZ;
#endif

	if (node->dividerZ != 0)
		return coordinates.getPositionX() >= node->dividerX && coordinates.getPositionX() < node->maxX &&
			coordinates.getPositionY() >= node->dividerY && coordinates.getPositionY() < node->maxY &&
				coordinates.getPositionZ() >= node->minZ && coordinates.getPositionZ() < node->dividerZ;
	else
		return coordinates.getPositionX() >= node->dividerX && coordinates.getPositionX() < node->maxX &&
			coordinates.getPositionY() >= node->dividerY && coordinates.getPositionY() < node->maxY;
}

bool TreeEntryImplementation::isInSW2Area(TreeNode* node) const {
#ifdef DEBUG_TREE_ENTRY
	Logger::console.info(true) << "TreeEntryImplementation::isInSW2Area -- Divider Z: " << node->dividerZ;
#endif

	if (node->dividerZ != 0)
		return coordinates.getPositionX() >= node->minX && coordinates.getPositionX() < node->dividerX &&
			coordinates.getPositionY() >= node->minY && coordinates.getPositionY() < node->dividerY &&
				coordinates.getPositionZ() >= node->dividerZ && coordinates.getPositionZ() < node->maxZ;
	else
		return 0;
}

bool TreeEntryImplementation::isInSE2Area(TreeNode* node) const {
#ifdef DEBUG_TREE_ENTRY
	Logger::console.info(true) << "TreeEntryImplementation::isInSE2Area -- Divider Z: " << node->dividerZ;
#endif

	if (node->dividerZ != 0)
		return coordinates.getPositionX() >= node->dividerX && coordinates.getPositionX() < node->maxX &&
			coordinates.getPositionY() >= node->minY && coordinates.getPositionY() < node->dividerY &&
				coordinates.getPositionZ() >= node->dividerZ && coordinates.getPositionZ() < node->maxZ;
	else
		return 0;

}

bool TreeEntryImplementation::isInNE2Area(TreeNode* node) const {
#ifdef DEBUG_TREE_ENTRY
	Logger::console.info(true) << "TreeEntryImplementation::isInNE2Area -- Divider Z: " << node->dividerZ;
#endif

	if (node->dividerZ != 0)
		return coordinates.getPositionX() >= node->dividerX && coordinates.getPositionX() < node->maxX &&
			coordinates.getPositionY() >= node->dividerY && coordinates.getPositionY() < node->maxY &&
				coordinates.getPositionZ() >= node->dividerZ && coordinates.getPositionZ() < node->maxZ;
	else
		return 0;
}

bool TreeEntryImplementation::isInNW2Area(TreeNode* node) const {
#ifdef DEBUG_TREE_ENTRY
	Logger::console.info(true) << "TreeEntryImplementation::isInNW2Area -- Divider Z: " << node->dividerZ;
#endif

	if (node->dividerZ != 0)
		return coordinates.getPositionX() >= node->minX && coordinates.getPositionX() < node->dividerX &&
			coordinates.getPositionY() >= node->dividerY && coordinates.getPositionY() < node->maxY &&
				coordinates.getPositionZ() >= node->dividerZ && coordinates.getPositionZ() < node->maxZ;
	else
		return 0;
}

bool TreeEntryImplementation::isInArea(TreeNode* node) const {
#ifdef DEBUG_TREE_ENTRY
	Logger::console.info(true) << "TreeEntryImplementation::isInArea -- Divider Z: " << node->dividerZ;
#endif

	return (coordinates.getPositionX() + radius > node->dividerX && coordinates.getPositionX() - radius < node->dividerX) ||
		(coordinates.getPositionY() + radius > node->dividerY && coordinates.getPositionY() - radius < node->dividerY);
}

uint64 TreeEntryImplementation::getObjectID() {
	return _this.getReferenceUnsafeStaticCast()->_getObjectID();
}

TreeEntry* TreeEntryImplementation::getRootParent() {
	ManagedReference<TreeEntry*> grandParent = getParent();
	ManagedReference<TreeEntry*> tempParent = nullptr;

	if (grandParent == nullptr)
		return nullptr;

	while ((tempParent = grandParent->getParent()) != nullptr)
		grandParent = tempParent;

	return grandParent;
}

TreeEntry* TreeEntryImplementation::getParentUnsafe() {
	return parent.getReferenceUnsafe();
}

TreeEntry* TreeEntryImplementation::getRootParentUnsafe() {
	TreeEntry* parent = this->parent.getReferenceUnsafe();

	if (parent == nullptr)
		return nullptr;

	TreeEntry* grandParent = parent;
	TreeEntry* temp = nullptr;

	while ((temp = grandParent->getParentUnsafe()) != nullptr)
		grandParent = temp;

	return grandParent;
}

int TreeEntry::compareTo(TreeEntry* obj) {
	if (getDirtyObjectID() < obj->getDirtyObjectID())
		return 1;
	else if (getDirtyObjectID() > obj->getDirtyObjectID())
		return -1;
	else
		return 0;
}

int TreeEntryImplementation::compareTo(TreeEntry* obj) {
	if (getObjectID() < obj->getObjectID())
		return 1;
	else if (getObjectID() > obj->getObjectID())
		return -1;
	else
		return 0;
}

uint64 TreeEntry::getDirtyObjectID() {
	return _getObjectID();
}

uint64 TreeEntry::getObjectID() {
	return _getObjectID();
}

uint64 TreeEntryImplementation::getDirtyObjectID() {
	return _this.getReferenceUnsafeStaticCast()->_getObjectID();
}

float TreeEntryImplementation::getOutOfRangeDistance() const {
	if (isInQuadTree()) {
		return ZoneServer::CLOSEOBJECTRANGE;
	} else {
		return ZoneServer::SPACEOBJECTRANGE;
	}
}