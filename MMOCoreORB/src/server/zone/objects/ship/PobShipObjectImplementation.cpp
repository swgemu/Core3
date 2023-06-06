/*
				Copyright <SWGEmu>
		See file COPYING for copying conditions.
*/

#include "server/zone/objects/ship/PobShipObject.h"
#include "server/zone/objects/ship/ShipObject.h"
#include "templates/tangible/SharedShipObjectTemplate.h"
#include "server/zone/objects/ship/PlayerLaunchPoints.h"
#include "server/zone/objects/ship/DamageSparkLocations.h"

void PobShipObjectImplementation::loadTemplateData(SharedObjectTemplate* templateData) {
	ShipObjectImplementation::loadTemplateData(templateData);

	SharedShipObjectTemplate* ssot = dynamic_cast<SharedShipObjectTemplate*>(templateData);

	if (ssot != nullptr) {
		const auto sparkLocs = ssot->getSparkLocations();

		for (int i = 0; i < sparkLocs.size(); i++) {
			String cellName = sparkLocs.elementAt(i).getKey();
			Vector<Vector3> locations = sparkLocs.elementAt(i).getValue();

			for (int k = 0; k < locations.size(); k++) {
				Vector3 point(locations.get(k));
				sparkLocations.addSparkLocation(cellName, point);
			}
		}

		const auto launchLocs = ssot->getLaunchLocations();

		for (int i = 0; i < launchLocs.size(); i++) {
			String cellName = launchLocs.elementAt(i).getKey();
			Vector<Vector3> locations = launchLocs.elementAt(i).getValue();

			for (int k = 0; k < locations.size(); k++) {
				Vector3 point(locations.get(k));
				launchPoints.addLaunchPoint(cellName, point);
			}
		}
	}
}

PobShipObject* PobShipObject::asPobShipObject() {
	return this;
}

PobShipObject* PobShipObjectImplementation::asPobShipObject() {
	return _this.getReferenceUnsafeStaticCast();
}

bool PobShipObject::isPobShipObject() {
	return true;
}

bool PobShipObjectImplementation::isPobShipObject() {
	return true;
}

String PobShipObjectImplementation::getRandomLaunchCell() {
	String cell = launchPoints.getRandomCell();
	return cell;
}

Vector3 PobShipObjectImplementation::getLaunchPointInCell(const String& cellName) {
	auto locations = launchPoints.getSpawnLocations(cellName);
	int random = System::random(locations.size() - 1);
	Vector3 location(locations.get(random));

	return location;
}
