#ifndef SHIPCOUNTERMEASUREDATA_H_
#define SHIPCOUNTERMEASUREDATA_H_

#include "engine/engine.h"
#include "templates/datatables/DataTableRow.h"

class ShipCountermeasureData : public Object {
public:
	enum CountermeasureType : int {
		MK1 = 0,
		MK2 = 1,
		MK3 = 2,
		MK4 = 3,
		MK5 = 4,
		AI1 = 5,
		AI2 = 6
	};

	static int getLauncherAmmoType(const String& dataName) {
		switch (dataName.hashCode()) {
			case String::hashCode("countermeasure_chaff_launcher"):
				return CountermeasureType::MK1;
			case String::hashCode("countermeasure_decoy_launcher"):
				return CountermeasureType::MK2;
			case String::hashCode("countermeasure_microchaff_launcher"):
				return CountermeasureType::MK3;
			case String::hashCode("countermeasure_confuser_launcher"):
				return CountermeasureType::MK4;
			case String::hashCode("countermeasure_em_launcher"):
				return CountermeasureType::MK5;
			default:
				return -1;
		}
	}

	static int getCountermeasureAmmoType(uint32 objectCRC) {
		switch (objectCRC) {
			case String::hashCode("object/tangible/ship/crafted/weapon/missile/countermeasure_chaff_pack.iff"):
				return CountermeasureType::MK1;
			case String::hashCode("object/tangible/ship/crafted/weapon/missile/countermeasure_decoy_pack.iff"):
				return CountermeasureType::MK2;
			case String::hashCode("object/tangible/ship/crafted/weapon/missile/countermeasure_microchaff_pack.iff"):
				return CountermeasureType::MK3;
			case String::hashCode("object/tangible/ship/crafted/weapon/missile/countermeasure_confuser_pack.iff"):
				return CountermeasureType::MK4;
			case String::hashCode("object/tangible/ship/crafted/weapon/missile/countermeasure_em_pack.iff"):
				return CountermeasureType::MK5;
			default:
				return -1;
		}
	}

protected:
	int countermeasureType;
	String appearance;

	int minCount;
	int maxCount;
	float minSpeed;
	float maxSpeed;
	float scatterAngle;

public:
	ShipCountermeasureData() : Object() {
		countermeasureType = 0;
		minCount = 0;
		maxCount = 0;
		minSpeed = 0.f;
		maxSpeed = 0.f;
		scatterAngle = 0.f;
	}

	void readObject(DataTableRow* row) {
		if (row == nullptr || row->getCellsSize() < 7) {
			return;
		}

		row->getCell(0)->getValue(countermeasureType);
		row->getCell(1)->getValue(appearance);
		row->getCell(2)->getValue(minCount);
		row->getCell(3)->getValue(maxCount);
		row->getCell(4)->getValue(minSpeed);
		row->getCell(5)->getValue(maxSpeed);
		row->getCell(6)->getValue(scatterAngle);
	}

	// set
	void setCountermeasureType(int value) {
		countermeasureType = value;
	}

	void setAppearance(const String& value) {
		appearance = value;
	}

	void setMinCount(int value) {
		minCount = value;
	}

	void setMaxCount(int value) {
		maxCount = value;
	}

	void setMinSpeed(int value) {
		minSpeed = value;
	}

	void setMaxSpeed(int value) {
		maxSpeed = value;
	}

	void setScatterAngle(int value) {
		scatterAngle = value;
	}

	// get
	int getCountermeasureType() const {
		return countermeasureType;
	}

	const String& getAppearance() const {
		return appearance;
	}

	int getMinCount() const {
		return minCount;
	}

	int getMaxCount() const {
		return maxCount;
	}

	int getMinSpeed() const {
		return minSpeed;
	}

	int getMaxSpeed() const {
		return maxSpeed;
	}

	int getScatterAngle() const {
		return scatterAngle;
	}
};

#endif //SHIPCOUNTERMEASUREDATA_H_
