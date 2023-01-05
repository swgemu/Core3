//
// Created by vagrant on 8/23/17.
//

#ifndef CORE3_SHIPPROJECTILEDATA_H_H
#define CORE3_SHIPPROJECTILEDATA_H_H

#include "engine/engine.h"
#include "templates/datatables/DataTableRow.h"

class ShipProjectileData : public Object {
protected:
	String name;
	int index;
	float range;
	float squaredRange;
	float speed;
	bool usesAmmo;
	bool missile;
	bool countermeasure;
	bool mining;
	bool tractor;
public:
	ShipProjectileData() {

	}

	void readObject(DataTableRow *row) {
		int temp;
		row->getCell(0)->getValue(name);
		row->getCell(1)->getValue(index);
		row->getCell(2)->getValue(range);
		squaredRange = range * range;
		row->getCell(3)->getValue(speed);
		row->getCell(4)->getValue(usesAmmo);
		row->getCell(5)->getValue(missile);
		row->getCell(6)->getValue(countermeasure);
		row->getCell(7)->getValue(mining);
		row->getCell(8)->getValue(tractor);
		//StringBuffer buffer;
	   // buffer << "Loaded Projectile- Speed: " << speed << endl;
		//static Logger logger;
	   // logger.info(buffer.toString(), true);
	}

	String getName() const {
		return name;
	}

	int getIndex() const {
		return index;
	}

	bool isTractorBeam() const {
		return tractor;
	}

	bool isMiningLaser() const {
		return mining;
	}

	bool isCountermeasure() const {
		return countermeasure;
	}

	bool isMissile() const {
		return missile;
	}

	bool consumesAmmo() const {
		return usesAmmo;
	}

	float getSpeed() const {
		return speed;
	}

	float getRange() const {
		return range;
	}

	float getSquaredRange() const {
		return squaredRange;
	}

};
#endif //CORE3_SHIPPROJECTILEDATA_H_H
