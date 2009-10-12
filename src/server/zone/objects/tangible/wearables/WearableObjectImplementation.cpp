/*
 * WearableObjectImplementation.cpp
 *
 *  Created on: 02/08/2009
 *      Author: victor
 */

#include "WearableObject.h"

/*
WearableObjectImplementation::WearableObjectImplementation(LuaObject* templateData) :
	TangibleObjectImplementation(templateData) {
	setLoggingName("WearableObject");
}
*/

void WearableObjectImplementation::initializeTransientMembers() {
	TangibleObjectImplementation::initializeTransientMembers();

	setLoggingName("WearableObject");
}
