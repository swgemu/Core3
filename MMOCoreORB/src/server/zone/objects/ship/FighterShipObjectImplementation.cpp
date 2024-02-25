/*
				Copyright <SWGEmu>
		See file COPYING for copying conditions.
*/

#include "server/zone/objects/ship/FighterShipObject.h"

void FighterShipObjectImplementation::loadTemplateData(SharedObjectTemplate* templateData) {
	ShipObjectImplementation::loadTemplateData(templateData);
}

void FighterShipObjectImplementation::loadTemplateData(SharedShipObjectTemplate* ssot) {
	if (ssot == nullptr) {
		return;
	}

	ShipObjectImplementation::loadTemplateData(ssot);
}

FighterShipObject* FighterShipObject::asFighterShipObject() {
	return this;
}

FighterShipObject* FighterShipObjectImplementation::asFighterShipObject() {
	return _this.getReferenceUnsafeStaticCast();
}

bool FighterShipObject::isFighterShipObject() {
	return true;
}

bool FighterShipObjectImplementation::isFighterShipObject() {
	return true;
}
