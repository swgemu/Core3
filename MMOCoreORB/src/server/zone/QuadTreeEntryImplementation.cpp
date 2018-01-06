/*
Copyright (C) 2007 <SWGEmu>. All rights reserved.
Distribution of this file for usage outside of Core3 is prohibited.
*/

#include <autogen/server/zone/ZoneServer.h>
#include "server/zone/QuadTreeEntry.h"

#include "server/zone/QuadTreeNode.h"

QuadTreeEntryImplementation::QuadTreeEntryImplementation(QuadTreeNode* n) {
	node = n;
	bounding = false;

	//visibilityRange = 128;

	closeobjects = nullptr;

	//closeobjects.setInsertPlan(SortedVector<QuadTreeEntry*>::NO_DUPLICATE);

	radius = 0.5f;

	receiverFlags = 0;
}

void QuadTreeEntryImplementation::setNode(QuadTreeNode* n) {
	node = n;
}

bool QuadTreeEntryImplementation::containsPoint(float px, float py) {
	return (((px - getPositionX()) * (px - getPositionX())) + ((py - getPositionY()) * (py - getPositionY())) <= radius * radius );
}

bool QuadTreeEntryImplementation::isInSWArea(QuadTreeNode* node) const {
	return coordinates.getPositionX() >= node->minX && coordinates.getPositionX() < node->dividerX &&
			coordinates.getPositionY() >= node->minY && coordinates.getPositionY() < node->dividerY;
}

bool QuadTreeEntryImplementation::isInSEArea(QuadTreeNode* node) const {
	return coordinates.getPositionX() >= node->dividerX && coordinates.getPositionX() < node->maxX &&
			coordinates.getPositionY() >= node->minY && coordinates.getPositionY() < node->dividerY;
}

bool QuadTreeEntryImplementation::isInNWArea(QuadTreeNode* node) const {
	return coordinates.getPositionX() >= node->minX && coordinates.getPositionX() < node->dividerX &&
			coordinates.getPositionY() >= node->dividerY && coordinates.getPositionY() < node->maxY;
}

bool QuadTreeEntryImplementation::isInArea(QuadTreeNode* node) const {
	return (coordinates.getPositionX() + radius > node->dividerX && coordinates.getPositionX() - radius < node->dividerX) ||
			(coordinates.getPositionY() + radius > node->dividerY && coordinates.getPositionY() - radius < node->dividerY);
}

uint64 QuadTreeEntryImplementation::getObjectID() {
	return _this.getReferenceUnsafeStaticCast()->_getObjectID();
}

QuadTreeEntry* QuadTreeEntryImplementation::getRootParent() {
	ManagedReference<QuadTreeEntry*> grandParent = getParent();
	ManagedReference<QuadTreeEntry*> tempParent = nullptr;

	if (grandParent == nullptr)
		return nullptr;

	while ((tempParent = grandParent->getParent()) != nullptr)
		grandParent = tempParent;

	return grandParent;
}

QuadTreeEntry* QuadTreeEntryImplementation::getParentUnsafe() {
	return parent.getReferenceUnsafe();
}

QuadTreeEntry* QuadTreeEntryImplementation::getRootParentUnsafe() {
	QuadTreeEntry* parent = this->parent.getReferenceUnsafe();

	if (parent == nullptr)
		return nullptr;

	QuadTreeEntry* grandParent = parent;
	QuadTreeEntry* temp = nullptr;

	while ((temp = grandParent->getParentUnsafe()) != nullptr)
		grandParent = temp;

	return grandParent;
}

int QuadTreeEntry::compareTo(QuadTreeEntry* obj) {
	if (getDirtyObjectID() < obj->getDirtyObjectID())
		return 1;
	else if (getDirtyObjectID() > obj->getDirtyObjectID())
		return -1;
	else
		return 0;
}

int QuadTreeEntryImplementation::compareTo(QuadTreeEntry* obj) {
	if (getObjectID() < obj->getObjectID())
		return 1;
	else if (getObjectID() > obj->getObjectID())
		return -1;
	else
		return 0;
}

uint64 QuadTreeEntry::getDirtyObjectID() {
	return _getObjectID();
}

uint64 QuadTreeEntry::getObjectID() {
	return _getObjectID();
}

uint64 QuadTreeEntryImplementation::getDirtyObjectID() {
	return _this.getReferenceUnsafeStaticCast()->_getObjectID();
}

float QuadTreeEntryImplementation::getOutOfRangeDistance() const {
	return ZoneServer::CLOSEOBJECTRANGE;
}