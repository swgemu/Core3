/*
 * TerminalImplementation.cpp
 *
 *  Created on: 11/08/2009
 *      Author: victor
 */

#include "Terminal.h"

void TerminalImplementation::initializeTransientMembers() {
	TangibleObjectImplementation::initializeTransientMembers();

	setLoggingName("Terminal");
}


void TerminalImplementation::notifyDissapear(QuadTreeEntry* obj) {
	SceneObjectImplementation* scno = (SceneObjectImplementation*) obj;

	SceneObject* scnoStub = (SceneObject*) scno->_getStub();

	if (scnoStub == controlledObject) {
		removeFromZone();
		destroyObjectFromDatabase(true);
	}

	TangibleObjectImplementation::notifyDissapear(obj);
	//removeNotifiedSentObject(scnoStub);
}
