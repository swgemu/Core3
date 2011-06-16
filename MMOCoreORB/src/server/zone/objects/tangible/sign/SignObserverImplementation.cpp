/*
 * SignObserverImplementation.cpp
 *
 *  Created on: Jun 16, 2011
 *      Author: crush
 */

#include "SignObserver.h"
#include "SignObject.h"
#include "server/zone/objects/scene/SceneObject.h"

void SignObserverImplementation::notifyObjectNameChanged(SceneObject* object) {
	if (signObject == NULL)
		return;

	signObject->setCustomObjectName(object->getCustomObjectName(), true);
}
