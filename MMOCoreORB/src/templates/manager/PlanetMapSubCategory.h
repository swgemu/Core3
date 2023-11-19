/*
 * PlanetMapSubCategory.h
 */

#ifndef PLANETMAPSUBCATEGORY_H_
#define PLANETMAPSUBCATEGORY_H_

#include "templates/datatables/DataTableRow.h"
#include "server/zone/managers/planet/MapLocationType.h"

class PlanetMapSubCategory : public Object {
	String name;
	int nameCRC;
	int index;

	bool activatable;
	String faction;
	bool factionVisibleOnly;

public:
	PlanetMapSubCategory() {
		name = "";
		nameCRC = 0;
		index = 0;

		activatable = false;
		factionVisibleOnly = false;
	}

	PlanetMapSubCategory(const PlanetMapSubCategory& pmc) : Object() {
		name = pmc.name;
		nameCRC = pmc.nameCRC;
		index = pmc.index;

		activatable = pmc.activatable;
		faction = pmc.faction;
		factionVisibleOnly = pmc.factionVisibleOnly;
	}

	PlanetMapSubCategory& operator=(const PlanetMapSubCategory& pmc) {
		if (this == &pmc)
			return *this;

		name = pmc.name;
		nameCRC = pmc.nameCRC;
		index = pmc.index;

		activatable = pmc.activatable;
		faction = pmc.faction;
		factionVisibleOnly = pmc.factionVisibleOnly;

		return *this;
	}

	inline ~PlanetMapSubCategory() {
	}

	int compareTo(const PlanetMapSubCategory& pmc) const {
		return name.compareTo(pmc.name);
	}

	void parseFromDataTableRow(const DataTableRow* row) {
		try {
			bool subCheck = false;
			row->getValue(3, subCheck);

			// These should only be sub categories
			if (!subCheck)
				return;

			row->getValue(0, name);
			nameCRC = name.hashCode();
			row->getValue(1, index);
			//row->getValue(2, category);
			//row->getValue(3, subCategory);
			row->getValue(4, activatable);
			row->getValue(5, faction);
			row->getValue(6, factionVisibleOnly);

		} catch (const Exception& ex) {
			System::out << "Error parsing PlanetMapSubCategory: " + ex.getMessage() << endl;
		}
	}

	inline const String& getName() const {
		return name;
	}

	inline int getCrc() const {
		return nameCRC;
	}

	inline int getIndex() const {
		return index;
	}

	inline bool canBeActive() const {
		return activatable;
	}

	inline const String& getFaction() const {
		return faction;
	}

	inline bool isFactionVisibleOnly() const {
		return factionVisibleOnly;
	}
};

#endif /* PLANETMAPSUBCATEGORY_H_ */
