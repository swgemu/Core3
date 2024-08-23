//
// Created by g on 12/21/17.
//

#include "ShipChassisData.h"
#include "templates/datatables/DataTableIff.h"
#include "templates/datatables/DataTableRow.h"
#include "templates/manager/DataArchiveStore.h"

ShipChassisData::ShipChassisData(DataTableRow* row, Vector<String>& columnNames) : Object() {
	row->getCell(0)->getValue(name);
	row->getCell(3)->getValue(wingOpenSpeed);

	const int start = 4;
	const int numComponents = (columnNames.size()-start)/3;
	String compatability;
	int hitweight;
	bool targetable;
	for (int i=start; i<columnNames.size(); i+=3) {
		String componentName = columnNames.get(i);
		row->getCell(i)->getValue(compatability);
		if (compatability.isEmpty()) {
			continue;
		}
		row->getCell(i+1)->getValue(hitweight);
		row->getCell(i+2)->getValue(targetable);
		componentMap.put(componentName, new ComponentSlotData(componentName, compatability, hitweight, targetable));
	}

	loadComponentHardpoints();
}

ShipChassisData::~ShipChassisData() {
	componentMap.removeAll();
}

void ShipChassisData::loadComponentHardpoints() {
	String filename = "datatables/space/ship_chassis_" + name + ".iff";
	IffStream* iffStream = DataArchiveStore::instance()->openIffFile(filename);

	if (iffStream == nullptr) {
		return;
	}

	DataTableIff dtiff;
	dtiff.readObject(iffStream);

	Vector<String> columns(dtiff.getTotalColumns(), 3);
	for (int i = 0; i < dtiff.getTotalColumns(); i++) {
		columns.add(dtiff.getColumnNameByIndex(i));
	}

	for (int i = 0; i < dtiff.getTotalRows(); ++i) {
		DataTableRow* row = dtiff.getRow(i);
		String name;
		row->getCell(0)->getValue(name);

		float range = 0.0f;
		if (columns.get(dtiff.getTotalColumns() - 1) == "hit_range") {
			row->getCell(dtiff.getTotalColumns() - 1)->getValue(range);
		}

		for (int j = 1; j < dtiff.getTotalColumns(); j++) {
			if (columns.get(j) == "hit_range") {
				continue;
			}

			String value;
			row->getCell(j)->getValue(value);

			if (value.isEmpty()) {
				continue;
			}

			const String& slotName = columns.get(j);
			ComponentSlotData* slotData = componentMap.get(slotName);

			if (slotData == nullptr) {
				slotData = new ComponentSlotData(slotName, "", 0, true);
				componentMap.put(slotName, slotData);
			}

			StringTokenizer hardpointTokenizer(value);
			hardpointTokenizer.setDelimiter(",");
			Vector<const ComponentHardpoint*> hardpoints;

			while (hardpointTokenizer.hasMoreTokens()) {
				String hardpoint;
				hardpointTokenizer.getStringToken(hardpoint);

				StringTokenizer templateTokenizer(hardpoint);
				templateTokenizer.setDelimiter(":");

				String first;
				String second;
				templateTokenizer.getStringToken(first);

				if (!templateTokenizer.hasMoreTokens()) {
					hardpoints.add(new ComponentHardpoint("", first, range));
				} else {
					templateTokenizer.getStringToken(second);
					hardpoints.add(new ComponentHardpoint(first, second, range));
				}
			}

			slotData->addHardpointData(name, hardpoints);
		}
	}
	delete iffStream;
}
