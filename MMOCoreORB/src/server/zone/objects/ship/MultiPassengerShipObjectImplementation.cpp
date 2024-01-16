/*
				Copyright <SWGEmu>
		See file COPYING for copying conditions.
*/

#include "server/zone/objects/ship/MultiPassengerShipObject.h"
#include "server/zone/Zone.h"

void MultiPassengerShipObjectImplementation::loadTemplateData(SharedObjectTemplate* templateData) {
	FighterShipObjectImplementation::loadTemplateData(templateData);
}

void MultiPassengerShipObjectImplementation::loadTemplateData(SharedShipObjectTemplate* ssot) {
	if (ssot == nullptr) {
		return;
	}

	FighterShipObjectImplementation::loadTemplateData(ssot);
}

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
