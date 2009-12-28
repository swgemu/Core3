/*
 * WaypointObject.h
 *
 *  Created on: 28/12/2009
 *      Author: victor
 */

#ifndef WAYPOINTOBJECT_H_
#define WAYPOINTOBJECT_H_

#include "engine/engine.h"

class WaypointObject : public Serializable {
protected:
	uint64 objectID;
	uint32 cellID; //?

	float positionX, positionZ, positionY;
	uint64 unknown;//? cell object id maybe
	uint32 planetCRC;

	UnicodeString customName;

	uint8 color;
	uint8 active;

public:
	WaypointObject();
	WaypointObject(const WaypointObject& obj);

	void copy(const WaypointObject& obj);

	inline void operator=(const WaypointObject& obj) {
		copy(obj);
	}

	void addSerializableVariables();

	bool toBinaryStream(ObjectOutputStream* stream);
	bool parseFromBinaryStream(ObjectInputStream* stream);

    uint8 getActive() const {
		return active;
	}

	uint32 getCellID() const {
		return cellID;
	}

	uint8 getColor() const {
		return color;
	}

	UnicodeString getCustomName() const {
		return customName;
	}

	uint64 getObjectID() const {
		return objectID;
	}

	uint32 getPlanetCRC() const {
		return planetCRC;
	}

	float getPositionX() const {
		return positionX;
	}

	uint64 getUnknown() const {
		return unknown;
	}

	void setActive(uint8 active) {
		this->active = active;
	}

	void setCellID(uint32 cellID) {
		this->cellID = cellID;
	}

	void setColor(uint8 color) {
		this->color = color;
	}

	void setCustomName(UnicodeString customName) {
		this->customName = customName;
	}

	void setObjectID(uint64 objectID) {
		this->objectID = objectID;
	}

	void setPlanetCRC(uint32 planetCRC) {
		this->planetCRC = planetCRC;
	}

	void setPositionX(float positionX) {
		this->positionX = positionX;
	}

	void setUnknown(uint64 unknown) {
		this->unknown = unknown;
	}

};

#endif /* WAYPOINTOBJECT_H_ */
