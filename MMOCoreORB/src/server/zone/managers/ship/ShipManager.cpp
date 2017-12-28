/*
 * ShipManager.cpp
 *
 *  Created on: 18/10/2013
 *      Author: victor
 */

#include "ShipManager.h"

#include <stddef.h>

#include "engine/util/iffstream/IffStream.h"
#include "server/zone/objects/ship/ShipComponent.h"
#include "templates/datatables/DataTableIff.h"
#include "templates/manager/DataArchiveStore.h"

class DataTableRow;

ShipManager::ShipManager() {
	IffStream* iffStream = DataArchiveStore::instance()->openIffFile(
			"datatables/space/ship_components.iff");

	if (iffStream == NULL) {
		fatal("datatables/space/ship_components.iff could not be found.");
		return;
	}

	DataTableIff dtiff;
	dtiff.readObject(iffStream);

	for (int i = 0; i < dtiff.getTotalRows(); ++i) {
		DataTableRow* row = dtiff.getRow(i);

		Reference<ShipComponent*> component = new ShipComponent();
		component->readObject(row);

		//info("loaded ship component " + component->getName() + " crc:0x" + String::hexvalueOf(int(component->getName().hashCode())), true);

		shipComponents.put(component->getName().hashCode(), component);
	}

	delete iffStream;
}

