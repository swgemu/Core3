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

class PatrolPoint {
	float positionX;
	float positionY;
	float positionZ;
	
	uint64 cellID;
	
	bool reached;
	
public:
	PatrolPoint() {
		positionX = 0;
		positionZ = 0;
		positionY = 0;

		cellID = 0;

		reached = false;
	}

	PatrolPoint(float posX, float posZ, float posY, uint64 cellid = 0) {
		positionX = posX;
		positionZ = posZ;
		positionY = posY;

		cellID = cellid;

		reached = false;
	}
	
	//getters
	inline float getPositionX() {
		return positionX;
	}
	
	inline float getPositionY() {
		return positionY;
	}
	
	inline float getPositionZ() {
		return positionZ;
	}
	
	inline uint64 getCellID() {
		return cellID;
	}
	
	inline bool isReached() {
		return reached;
	}
	
	//setters
	inline void setPosition(float x, float z, float y) {
		positionX = x;
		positionZ = z;
		positionY = y;
	}
	
	inline void setPositionX(float x) {
		positionX = x;
	}
	
	inline void setPositionZ(float z) {
		positionZ = z;
	}
	
	inline void setPositionY(float y) {
		positionY = y;
	}
	
	inline void setCellID(uint64 cellid) {
		cellID = cellid;
	}
	
	inline void setReached(bool value) {
		reached = value;
	}
};

#endif /*PATROLPOINT_H_*/
