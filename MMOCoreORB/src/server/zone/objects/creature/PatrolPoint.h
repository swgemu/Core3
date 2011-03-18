/*
Copyright (C) 2007 <SWGEmu>
 
This File is part of Core3.
 
This program is free software; you can redistribute 
it and/or modify it under the terms of the GNU Lesser 
General Public License as published by the Free Software
Foundation; either version 2 of the License, 
or (at your option) any later version.
 
This program is distributed in the hope that it will be useful, 
but WITHOUT ANY WARRANTY; without even the implied warranty of 
MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. 
See the GNU Lesser General Public License for
more details.
 
You should have received a copy of the GNU Lesser General 
Public License along with this program; if not, write to
the Free Software Foundation, Inc., 51 Franklin St, Fifth Floor, Boston, MA 02110-1301 USA
 
Linking Engine3 statically or dynamically with other modules 
is making a combined work based on Engine3. 
Thus, the terms and conditions of the GNU Lesser General Public License 
cover the whole combination.
 
In addition, as a special exception, the copyright holders of Engine3 
give you permission to combine Engine3 program with free software 
programs or libraries that are released under the GNU LGPL and with 
code included in the standard release of Core3 under the GNU LGPL 
license (or modified versions of such code, with unchanged license). 
You may copy and distribute such a system following the terms of the 
GNU LGPL for Engine3 and the licenses of the other code concerned, 
provided that you include the source code of that other code when 
and as the GNU LGPL requires distribution of source code.
 
Note that people who make modified versions of Engine3 are not obligated 
to grant this special exception for their modified versions; 
it is their choice whether to do so. The GNU Lesser General Public License 
gives permission to release a modified version without this exception; 
this exception also makes it possible to release a modified version 
which carries forward this exception.
*/

#ifndef PATROLPOINT_H_
#define PATROLPOINT_H_

#include "system/lang.h"
#include "server/zone/objects/scene/SceneObject.h"
#include "server/zone/objects/cell/CellObject.h"
#include "server/zone/objects/building/BuildingObject.h"
#include "server/zone/objects/scene/WorldCoordinates.h"

class PatrolPoint : public Serializable {
	WorldCoordinates position;

	bool reached;
	
	Time estimatedTimeOfArrival;

public:
	PatrolPoint() {
		reached = true;

		addSerializableVariables();
	}

	PatrolPoint(const Vector3& pos, SceneObject* cell = NULL) : position(pos, cell) {
		reached = false;

		addSerializableVariables();
	}

	PatrolPoint(float posX, float posZ, float posY, SceneObject* cell = NULL) : position(Vector3(posX, posY, posZ), cell) {
		reached = false;

		addSerializableVariables();
	}
	
	PatrolPoint(const PatrolPoint& point) : Object(), Serializable() {
		position = point.position;

		reached = point.reached;

		addSerializableVariables();
	}

	PatrolPoint& operator=(const PatrolPoint& p) {
		if (this == &p)
			return *this;

		position = p.position;

		reached = p.reached;

		return *this;
	}

	inline void addSerializableVariables() {
		addSerializableVariable("position", &position);
		addSerializableVariable("reached", &reached);
		addSerializableVariable("estimatedTimeOfArrival", &estimatedTimeOfArrival);
	}

	Vector3 getWorldPosition() {
		return position.getWorldPosition();
	}

	bool isInRange(SceneObject* obj, float range) {
		Vector3 thisWorldPos = getWorldPosition();
		Vector3 objWorldPos = obj->getWorldPosition();

		return thisWorldPos.squaredDistanceTo(objWorldPos) <= (range * range);
	}

	bool isInRange(PatrolPoint* obj, float range) {
		Vector3 thisWorldPos = getWorldPosition();
		Vector3 objWorldPos = obj->getWorldPosition();

		return thisWorldPos.squaredDistanceTo(objWorldPos) <= (range * range);
	}

	inline WorldCoordinates getCoordinates() {
		return position;
	}

	//getters
	inline float getPositionX() {
		return position.getX();
	}
	
	inline float getPositionY() {
		return position.getY();
	}
	
	inline float getPositionZ() {
		return position.getZ();
	}
	
	inline SceneObject* getCell() {
		return position.getCell();
	}
	
	inline Time* getEstimatedTimeOfArrival() {
		return &estimatedTimeOfArrival;
	}

	inline bool isReached() {
		return reached;
	}
	
	inline bool isPastTimeOfArrival() {
		return estimatedTimeOfArrival.isPast() || estimatedTimeOfArrival.isPresent();
	}

	//setters
	inline void setPosition(float x, float z, float y) {
		position.setCoordinates(Vector3(x, y, z));
	}
	
	inline void setPositionX(float x) {
		position.setX(x);
	}
	
	inline void setPositionZ(float z) {
		position.setZ(z);
	}
	
	inline void setPositionY(float y) {
		position.setY(y);
	}
	
	inline void setCell(SceneObject* cell) {
		if ((cell != NULL && cell->isCellObject()) || cell == NULL)
			position.setCell(cell);
	}
	
	inline void setReached(bool value) {
		reached = value;
	}

	inline void addEstimatedTimeOfArrival(uint32 mili) {
		estimatedTimeOfArrival.updateToCurrentTime();
		estimatedTimeOfArrival.addMiliTime(mili);
	}
};

#endif /*PATROLPOINT_H_*/
