/*
Copyright (C) 2007 <SWGEmu>. All rights reserved.
Distribution of this file for usage outside of Core3 is prohibited.
*/

#include <autogen/server/zone/ZoneServer.h>
#include "server/zone/TreeEntry.h"
#include "server/zone/TreeNode.h"
#include "server/zone/objects/scene/SceneObject.h"
#include "server/zone/objects/tangible/TangibleObject.h"

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
	return (((px - getPositionX()) * (px - getPositionX())) + ((py - getPositionY()) * (py - getPositionY())) <= radius * radius );
}

bool TreeEntryImplementation::containsPoint(float px, float py, float pz) {
	return ((((px - getPositionX()) * (px - getPositionX())) + ((py - getPositionY()) * (py - getPositionY()))
			+ ((pz - getPositionZ()) * (pz - getPositionZ()))) <= radius * radius * radius );
}

bool TreeEntryImplementation::isInSWArea(TreeNode *node) const {
	if (node->dividerZ != 0)
		return coordinates.getPositionX() >= node->minX && coordinates.getPositionX() < node->dividerX &&
			coordinates.getPositionY() >= node->minY && coordinates.getPositionY() < node->dividerY &&
				coordinates.getPositionZ() >= node->minZ && coordinates.getPositionZ() < node->dividerZ;

	else
		return coordinates.getPositionX() >= node->minX && coordinates.getPositionX() < node->dividerX &&
			coordinates.getPositionY() >= node->minY && coordinates.getPositionY() < node->dividerY;

	Logger::console.info(String::valueOf(node->dividerZ), true);
}

bool TreeEntryImplementation::isInSEArea(TreeNode* node) const {
	if (node->dividerZ != 0)
		return coordinates.getPositionX() >= node->dividerX && coordinates.getPositionX() < node->maxX &&
			coordinates.getPositionY() >= node->minY && coordinates.getPositionY() < node->dividerY &&
				coordinates.getPositionZ() >= node->minZ && coordinates.getPositionZ() < node->dividerZ;
	else
		return coordinates.getPositionX() >= node->dividerX && coordinates.getPositionX() < node->maxX &&
			coordinates.getPositionY() >= node->minY && coordinates.getPositionY() < node->dividerY;
	Logger::console.info(String::valueOf(node->dividerZ), true);
}

bool TreeEntryImplementation::isInNWArea(TreeNode* node) const {
	if (node->dividerZ != 0)
		return coordinates.getPositionX() >= node->minX && coordinates.getPositionX() < node->dividerX &&
			coordinates.getPositionY() >= node->dividerY && coordinates.getPositionY() < node->maxY &&
				coordinates.getPositionZ() >= node->minZ && coordinates.getPositionZ() < node->dividerZ;
	else
		return coordinates.getPositionX() >= node->minX && coordinates.getPositionX() < node->dividerX &&
			coordinates.getPositionY() >= node->dividerY && coordinates.getPositionY() < node->maxY;

	Logger::console.info(String::valueOf(node->dividerZ), true);
}

bool TreeEntryImplementation::isInNEArea(TreeNode* node) const {
	if (node->dividerZ != 0)
		return coordinates.getPositionX() >= node->dividerX && coordinates.getPositionX() < node->maxX &&
			coordinates.getPositionY() >= node->dividerY && coordinates.getPositionY() < node->maxY &&
				coordinates.getPositionZ() >= node->minZ && coordinates.getPositionZ() < node->dividerZ;
	else
		return coordinates.getPositionX() >= node->dividerX && coordinates.getPositionX() < node->maxX &&
			coordinates.getPositionY() >= node->dividerY && coordinates.getPositionY() < node->maxY;

	Logger::console.info(String::valueOf(node->dividerZ), true);
}

bool TreeEntryImplementation::isInSW2Area(TreeNode* node) const {
	if (node->dividerZ != 0)
		return coordinates.getPositionX() >= node->minX && coordinates.getPositionX() < node->dividerX &&
			coordinates.getPositionY() >= node->minY && coordinates.getPositionY() < node->dividerY &&
				coordinates.getPositionZ() >= node->dividerZ && coordinates.getPositionZ() < node->maxZ;
	else
		return 0;
	Logger::console.info(String::valueOf(node->dividerZ), true);
}

bool TreeEntryImplementation::isInSE2Area(TreeNode* node) const {
	if (node->dividerZ != 0)
		return coordinates.getPositionX() >= node->dividerX && coordinates.getPositionX() < node->maxX &&
			coordinates.getPositionY() >= node->minY && coordinates.getPositionY() < node->dividerY &&
				coordinates.getPositionZ() >= node->dividerZ && coordinates.getPositionZ() < node->maxZ;
	else
		return 0;
Logger::console.info(String::valueOf(node->dividerZ), true);
}

bool TreeEntryImplementation::isInNE2Area(TreeNode* node) const {
	if (node->dividerZ != 0)
		return coordinates.getPositionX() >= node->dividerX && coordinates.getPositionX() < node->maxX &&
			coordinates.getPositionY() >= node->dividerY && coordinates.getPositionY() < node->maxY &&
				coordinates.getPositionZ() >= node->dividerZ && coordinates.getPositionZ() < node->maxZ;
	else
		return 0;
Logger::console.info(String::valueOf(node->dividerZ), true);
}

bool TreeEntryImplementation::isInNW2Area(TreeNode* node) const {
	if (node->dividerZ != 0)
		return coordinates.getPositionX() >= node->minX && coordinates.getPositionX() < node->dividerX &&
			coordinates.getPositionY() >= node->dividerY && coordinates.getPositionY() < node->maxY &&
				coordinates.getPositionZ() >= node->dividerZ && coordinates.getPositionZ() < node->maxZ;
	else
		return 0;
Logger::console.info(String::valueOf(node->dividerZ), true);
}

bool TreeEntryImplementation::isInArea(TreeNode* node) const {
		return (coordinates.getPositionX() + radius > node->dividerX && coordinates.getPositionX() - radius < node->dividerX) ||
			(coordinates.getPositionY() + radius > node->dividerY && coordinates.getPositionY() - radius < node->dividerY);
Logger::console.info(String::valueOf(node->dividerZ), true);
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
	if (isInQuadTree() == true) {
		return ZoneServer::CLOSEOBJECTRANGE;
	} else {
		return ZoneServer::SPACEOBJECTRANGE;
	}
}