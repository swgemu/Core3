#ifndef SHIPTURRETDATA_H_
#define SHIPTURRETDATA_H_

#include "engine/engine.h"
#include "templates/datatables/DataTableRow.h"

class ShipTurretData: public Object {
protected:
	String chassisName;
	int weaponIndex;
	float minYaw;
	float maxYaw;
	float minPitch;
	float maxPitch;

public:
	ShipTurretData() {
		weaponIndex = 0;
		minYaw = 0.f;
		maxYaw = 0.f;
		minPitch = 0.f;
		maxPitch = 0.f;
	}

	void readObject(DataTableRow* row) {
		if (row == nullptr || row->getCellsSize() < 6) {
			return;
		}

		row->getCell(0)->getValue(chassisName);
		row->getCell(1)->getValue(weaponIndex);
		row->getCell(2)->getValue(minYaw);
		row->getCell(3)->getValue(maxYaw);
		row->getCell(4)->getValue(minPitch);
		row->getCell(5)->getValue(maxPitch);
	}

	void readObject(LuaObject* row) {
		if (row == nullptr || row->getTableSize() < 6) {
			Logger log("ShipTurretData");
			log.info(true) << "!row " << row->getTableSize();
		}

		chassisName = row->getStringAt(1);
		weaponIndex = row->getIntAt(2);
		minYaw = row->getFloatAt(3);
		maxYaw = row->getFloatAt(4);
		minPitch = row->getFloatAt(5);
		maxPitch = row->getFloatAt(6);
	}

	const String& getChassisName() const {
		return chassisName;
	}

	int getWeaponIndex() const {
		return weaponIndex;
	}

	float getMinYaw() const {
		return minYaw;
	}

	float getMaxYaw() const {
		return maxYaw;
	}

	float getMinPitch() const {
		return minPitch;
	}

	float getMaxPitch() const {
		return maxPitch;
	}

	void setChassisName(const String& name) {
		chassisName = name;
	}

	void setWeaponIndex(int index) {
		weaponIndex = index;
	}

	void setMinYaw(float minY) {
		minYaw = minY;
	}

	void setMaxYaw(float maxY) {
		maxYaw = maxY;
	}

	void setMinPitch(float minP) {
		minPitch = minP;
	}

	void setMaxPitch(float maxP) {
		maxPitch = maxP;
	}
};

#endif //SHIPTURRETDATA_H_
