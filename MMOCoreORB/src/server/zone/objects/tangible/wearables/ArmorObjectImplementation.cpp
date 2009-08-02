/*
 * ArmorObjectImplementation.cpp
 *
 *  Created on: 02/08/2009
 *      Author: victor
 */

#include "ArmorObject.h"

ArmorObjectImplementation::ArmorObjectImplementation(LuaObject* templateData) :
	WearableObjectImplementation(templateData) {
	setLoggingName("ArmorObject");
}
