/*
 * PersistentMessageImplementation.cpp
 *
 *  Created on: 13/03/2010
 *      Author: victor
 */

#include "PersistentMessage.h"

void PersistentMessageImplementation::setParameterizedBody(ParameterizedStringId& body) {
	stringIdBody = body;
}

int PersistentMessageImplementation::getMailID() {
	return Long::hashCode(_this->_getObjectID());
}

uint64 PersistentMessageImplementation::getObjectID() {
	return _this->_getObjectID();
}
