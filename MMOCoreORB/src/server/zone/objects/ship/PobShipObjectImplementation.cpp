/*
				Copyright <SWGEmu>
		See file COPYING for copying conditions.
*/

#include "server/zone/objects/ship/PobShipObject.h"
#include "templates/tangible/SharedShipObjectTemplate.h"
#include "system/util/VectorMap.h"

void PobShipObjectImplementation::loadTemplateData(SharedObjectTemplate* templateData) {
	ShipObjectImplementation::loadTemplateData(templateData);

	SharedShipObjectTemplate* ssot = dynamic_cast<SharedShipObjectTemplate*>(templateData);

	if (ssot != nullptr) {
		const auto sparkLocs = ssot->getSparkLocations();

		if (sparkLocs != nullptr) {
			for (int i = 0; i < sparkLocs->size(); i++) {
				int cellNum = sparkLocs->elementAt(i).getKey();
				Vector<Vector3> locations = sparkLocs->elementAt(i).getValue();
				Vector<Vector3*> locs;

				for (int k = 0; k < locations.size(); k++) {
					Vector3* coords(&locations.get(k));
					locs.emplace(coords);
				}

				sparkLocations.put(cellNum, &locs);
			}
		}

		const auto launchLocs = ssot->getLaunchLocations();

		if (launchLocs != nullptr) {
			for (int i = 0; i < launchLocs->size(); i++) {
				int cellNum = launchLocs->elementAt(i).getKey();
				Vector<Vector3> locations = launchLocs->elementAt(i).getValue();
				Vector<Vector3*> locs;

				for (int k = 0; k < locations.size(); k++) {
					Vector3* coords(&locations.get(k));
					locs.emplace(coords);
				}

				launchPoints.put(cellNum, &locs);
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