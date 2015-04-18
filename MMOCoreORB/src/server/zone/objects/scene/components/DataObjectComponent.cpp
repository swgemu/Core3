/*
				Copyright <SWGEmu>
		See file COPYING for copying conditions.
*/

#include "DataObjectComponent.h"
#include "server/zone/objects/scene/SceneObject.h"

DataObjectComponent::DataObjectComponent() {

}

DataObjectComponent::~DataObjectComponent() {

}

void DataObjectComponent::initializeTransientMembers() {

}

void DataObjectComponent::notifyObjectDestroyingFromDatabase() {

}

void DataObjectComponent::setParent(SceneObject* object) {
	parent = object;
}

SceneObject* DataObjectComponent::getParent() {
	return parent.get().get();
}

