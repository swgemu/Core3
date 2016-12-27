/*
 * StartingLocation.h
 *
 *  Created on: Apr 4, 2011
 *      Author: crush
 */

#ifndef STARTINGLOCATION_H_
#define STARTINGLOCATION_H_

#include "templates/datatables/DataTableRow.h"

class StartingLocation : public Object {
	String zoneName;
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
		zoneName = sl.zoneName;
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
		zoneName = sl.zoneName;

		return *this;
	}

	int compareTo(const StartingLocation& sl) const {
		return location.compareTo(sl.location);
	}

	void parseFromDataTableRow(DataTableRow* row) {
		if (row == NULL)
			return;

		try {
			//New style has added the z position.
			if (row->getCellsSize() > 9) {
				row->getValue(0, location);
				row->getValue(1, planet);
				row->getValue(2, x);
				row->getValue(3, z);
				row->getValue(4, y);
				row->getValue(5, cell);
				row->getValue(6, image);
				row->getValue(7, description);
				row->getValue(8, radius);
				row->getValue(9, heading);
			} else {
				row->getValue(0, location);
				row->getValue(1, planet);
				row->getValue(2, x);
				row->getValue(3, y);
				row->getValue(4, cell);
				row->getValue(5, image);
				row->getValue(6, description);
				row->getValue(7, radius);
				row->getValue(8, heading);
			}
		} catch (Exception& e) {
			System::out << "Error parsing values in StartingLocation. Possible column mismatch." << endl;
		}

		//Get the terrain name from the image path.
		//17 = "/styles.location." 17 characters long
		zoneName = image.subString(17, image.lastIndexOf('.'));
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

	inline String getZoneName() const {
		return zoneName;
	}

	inline String getLocation() const {
		return location;
	}
};

#endif /* STARTINGLOCATION_H_ */
