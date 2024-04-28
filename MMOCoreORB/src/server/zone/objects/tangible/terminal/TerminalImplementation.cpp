/*
 * TerminalImplementation.cpp
 *
 *  Created on: 11/08/2009
 *      Author: victor
 */

#include "server/zone/objects/tangible/terminal/Terminal.h"

void TerminalImplementation::initializeTransientMembers() {
	TangibleObjectImplementation::initializeTransientMembers();

	setLoggingName("Terminal");
}

void TerminalImplementation::notifyInsert(TreeEntry* object) {
	auto sceneO = static_cast<SceneObject*>(object);
	uint64 scnoID = sceneO->getObjectID();

	if (sceneO == nullptr) {
		return;
	}

	sendTo(sceneO, true, false);
}