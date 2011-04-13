/*
 * StartingLocation.h
 *
 *  Created on: Apr 4, 2011
 *      Author: crush
 */

#ifndef STARTINGLOCATION_H_
#define STARTINGLOCATION_H_

#include "engine/engine.h"
#include "server/zone/templates/datatables/DataTableRow.h"
#include "server/zone/templates/datatables/DataTableCell.h"
#include "server/zone/objects/terrain/PlanetNames.h"

class StartingLocation : public Object {
	String location;
	String planet;
	String cell;
	String image;
	String description;

	float x;
	float y;
	float z;
	float radius;
	float heading;

	int zoneID;

public:
	StartingLocation() {
		x = 0.f;
		y = 0.f;
		z = 0.f;
		radius = 0.f;
		heading = 0.f;
		zoneID = 0;
	}

	StartingLocation(const StartingLocation& sl) : Object() {
		location = sl.location;
		planet = sl.planet;
		x = sl.x;
		y = sl.y;
		z = sl.z;
		cell = sl.cell;
		image = sl.image;
		description = sl.description;
		radius = sl.radius;
		heading = sl.heading;
		zoneID = sl.zoneID;
	}

	StartingLocation& operator= (const StartingLocation& sl) {
		if (this == &sl)
			return *this;

		location = sl.location;
		planet = sl.planet;
		x = sl.x;
		y = sl.y;
		z = sl.z;
		cell = sl.cell;
		image = sl.image;
		description = sl.description;
		radius = sl.radius;
		heading = sl.heading;
		zoneID = sl.zoneID;

		return *this;
	}

	int compareTo(const StartingLocation& sl) const {
		return location.compareTo(sl.location);
	}

	void parseFromDataTableRow(DataTableRow* row) {
		if (row == NULL)
			return;

		try {
			row->getCell(0)->getValue(location);
			row->getCell(1)->getValue(planet);
			row->getCell(2)->getValue(x);
			row->getCell(3)->getValue(y);
			row->getCell(4)->getValue(cell);
			row->getCell(5)->getValue(image);

			//Get the zone ID from the image path.
			//17 = "/styles.location." 17 characters long
			zoneID = Planet::getPlanetID(image.subString(17, image.lastIndexOf('.')));

			row->getCell(6)->getValue(description);
			row->getCell(7)->getValue(radius);
			row->getCell(8)->getValue(heading);
		} catch (Exception& e) {
			System::out << "Error parsing values in StartingLocation. Possible column mismatch." << endl;
		}
	}

	void insertToMessage(Message* msg) {
		msg->insertAscii(location);
		msg->insertAscii(planet);
		msg->insertFloat(x);
		msg->insertFloat(y);
		msg->insertAscii(cell);
		msg->insertAscii(image);
		msg->insertAscii(description);
		msg->insertByte(0x01);
	}

	inline float getX() const {
		return x;
	}

	inline float getY() const {
		return y;
	}

	inline float getZ() const {
		return z;
	}

	inline float getHeading() const {
		return heading;
	}

	inline uint64 getCell() const {
		return Long::valueOf(cell);
	}

	inline int getZoneID() const {
		return zoneID;
	}

	inline String getLocation() const {
		return location;
	}
};

#endif /* STARTINGLOCATION_H_ */
