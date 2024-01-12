/*
				Copyright <SWGEmu>
		See file COPYING for copying conditions.
*/

#include "server/zone/objects/ship/MultiPassengerShipObject.h"
#include "server/zone/Zone.h"

MultiPassengerShipObject* MultiPassengerShipObject::asMultiPassengerShip() {
	return this;
}

MultiPassengerShipObject* MultiPassengerShipObjectImplementation::asMultiPassengerShip() {
	return _this.getReferenceUnsafeStaticCast();
}

bool MultiPassengerShipObject::isMultiPassengerShip() {
	return true;
}

bool MultiPassengerShipObjectImplementation::isMultiPassengerShip() {
	return true;
}
