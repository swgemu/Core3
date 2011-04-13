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


class StartingLocation : public Object {
	String terrainName;
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

public:
	StartingLocation() {
		x = 0.f;
		y = 0.f;
		z = 0.f;
		radius = 0.f;
		heading = 0.f;
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
		terrainName = sl.terrainName;
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
		terrainName = sl.terrainName;

		return *this;
	}

	int compareTo(const StartingLocation& sl) const {
		return location.compareTo(sl.location);
	}

	void parseFromDataTableRow(DataTableRow* row) {
		if (row == NULL)
			return;

		row->getCell(0)->getValue(location);
		row->getCell(1)->getValue(planet);
		row->getCell(2)->getValue(x);
		row->getCell(3)->getValue(z);
		row->getCell(4)->getValue(y);
		row->getCell(5)->getValue(cell);
		row->getCell(6)->getValue(image);

		//Get the terrain name from the image path.
		//TODO: Need to find a better way to get the planet id
		//17 = "/styles.location." 17 characters long
		terrainName = image.subString(17, image.lastIndexOf('.'));

		row->getCell(7)->getValue(description);
		row->getCell(8)->getValue(radius);
		row->getCell(9)->getValue(heading);
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

	inline String getTerrainName() const {
		return terrainName;
	}

	inline String getLocation() const {
		return location;
	}
};

#endif /* STARTINGLOCATION_H_ */
