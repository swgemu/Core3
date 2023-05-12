#ifndef SHIPAPPEARANCEDATA_H_
#define SHIPAPPEARANCEDATA_H_

#include "engine/engine.h"
#include "templates/manager/DataArchiveStore.h"
#include "templates/datatables/DataTableIff.h"
#include "server/zone/objects/ship/ComponentSlots.h"

class DataTableRow;

class ShipAppearanceData : public Object {
protected:
	HashTable<String, String> appearanceMap;
	HashTable<uint32, String> advancedMap;
	HashTable<uint32, String> defaultMap;

	String dataName;

public:
	ShipAppearanceData(const String& chassisName) {
		dataName = chassisName;

		readChassisIff();
	}

	void readChassisIff() {
		IffStream* iffStream = DataArchiveStore::instance()->openIffFile("datatables/space/ship_chassis_" + dataName + ".iff");
		if (iffStream == nullptr) {
			return;
		}

		DataTableIff dataTable;
		dataTable.readObject(iffStream);

		for (int i = 0; i < dataTable.getTotalRows(); ++i) {
			DataTableRow* row = dataTable.getRow(i);
			if (row == nullptr || row->getCellsSize() == 0) {
				break;
			}

			String key;
			String value;

			for (int i = 0; i < row->getCellsSize(); ++i) {
				auto cell = row->getCell(i);
				if (cell == nullptr || cell->toString() == "") {
					continue;
				}

				if (i == 0) {
					key = cell->toString();
				} else {
					value = cell->toString();
					break;
				}
			}

			if (key != "" && value != "") {
				int slot = prefixToSlot(key);

				if (slot != -1) {
					if (defaultMap.get(slot) == "" && !value.contains("_s02")) {
						defaultMap.put(slot, key);
					}

					if (advancedMap.get(slot) == "" && value.contains("_s02")) {
						advancedMap.put(slot, key);
					}
				}

				appearanceMap.put(key, value);
			}
		}

		delete iffStream;
	}

	const String& getDefaultAppearance(uint32 slot) const {
		return defaultMap.get(slot);
	}

	const String& getAdvancedAppearance(uint32 slot) const {
		return advancedMap.get(slot);
	}

	bool contains(const String& dataName) const {
		return appearanceMap.get(dataName) != "";
	}

	int size() const {
		return appearanceMap.size();
	}

	int prefixToSlot(const String& entry) const {
		if (entry.length() < 4) {
			return -1;
		}

		uint32 prefixCRC = entry.subString(0,3).hashCode();

		switch (prefixCRC) {
			case String::hashCode("rct"): return Components::REACTOR;
			case String::hashCode("eng"): return Components::ENGINE;
			case String::hashCode("shd"): return Components::SHIELD0;
			case String::hashCode("arm"): return Components::ARMOR0;
			case String::hashCode("cap"): return Components::CAPACITOR;
			case String::hashCode("bst"): return Components::BOOSTER;
			case String::hashCode("ddi"): return Components::DROID_INTERFACE;
			case String::hashCode("bdg"): return Components::BRIDGE;
			case String::hashCode("hgr"): return Components::HANGAR;
			case String::hashCode("tst"): return Components::TARGETING_STATION;
			case String::hashCode("wpn"): return Components::WEAPON_START;
			default: return -1;
		}
	}
};

#endif // SHIPAPPEARANCEDATA_H_
