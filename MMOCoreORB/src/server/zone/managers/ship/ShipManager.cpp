/*
 * ShipManager.cpp
 *
 *  Created on: 18/10/2013
 *      Author: victor
 */

#include "ShipManager.h"
#include "templates/manager/DataArchiveStore.h"
#include "templates/datatables/DataTableIff.h"

ShipManager::ShipManager() {
	IffStream* iffStream = DataArchiveStore::instance()->openIffFile(
			"datatables/space/ship_components.iff");

	if (iffStream == nullptr) {
		fatal("datatables/space/ship_components.iff could not be found.");
		return;
	}

	DataTableIff dtiff;
	dtiff.readObject(iffStream);

	for (int i = 0; i < dtiff.getTotalRows(); ++i) {
		DataTableRow* row = dtiff.getRow(i);

		Reference<ShipComponent*> component = new ShipComponent();
		component->readObject(row);

		debug() << "loaded ship component " << component->getName() << " crc: " << component->getName();

		shipComponents.put(component->getName().hashCode(), component);
	}

	delete iffStream;
}

