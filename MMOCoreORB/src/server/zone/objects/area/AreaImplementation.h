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

#ifndef AREAIMPLEMENTATION_H_
#define AREAIMPLEMENTATION_H_

#include "engine/engine.h"
#include "Area.h"
#include "../scene/SceneObject.h"

class AreaImplementation : public AreaServant {
protected:
	float width;
	float height;
	uint8 type;
	uint64 uid;

	float widthMinPos;
	float widthMaxPos;
	float heightMinPos;
	float heightMaxPos;

	static const uint8 BASE = 0x03;
	static const uint8 ACTIVE = 0x01;
	static const uint8 NOBUILD = 0x02;

public:

	AreaImplementation(Coordinate * center, float width, float height) {
		if(width <= 0 || height <= 0)
			throw Exception("Invalid Area Parameters!");

		uid = 0;

		this->width = width;
		this->height = height;

		widthMinPos = center->getPositionX() - width / 2;
		widthMaxPos = center->getPositionX() + width / 2;
		heightMinPos = center->getPositionY() - height / 2;
		heightMaxPos = center->getPositionY() + height / 2;
	}

	AreaImplementation(float minXPos, float maxXPos, float minYPos, float maxYPos) {
		if(minXPos >= maxXPos || minYPos >= maxYPos)
			throw Exception("Invalid Area Parameters!");

		uid = 0;

		widthMinPos = minXPos;
		widthMaxPos = maxXPos;
		heightMinPos = minYPos;
		heightMaxPos = maxYPos;

		width = maxXPos - minXPos;
		height = maxYPos - minYPos;
	}

	virtual ~AreaImplementation() { }

	virtual uint8 getType() { return 255;}

	bool contains(SceneObject * object){
		return contains(object->getPositionX(),object->getPositionY());
	}

	bool contains(Coordinate * coord) {
		return contains(coord->getPositionX(), coord->getPositionY());
	}

	bool contains(float x, float y) {
		return (x > widthMinPos && x <= widthMaxPos) && (y > heightMinPos && y <= heightMaxPos);
	}

	bool contains(Area * reg) {
		AreaImplementation * region = (AreaImplementation *) reg->_getImplementation();
		return (
			contains(region->widthMinPos, region->heightMaxPos) ||
			contains(region->widthMaxPos, region->heightMaxPos) ||
			contains(region->widthMinPos, region->heightMinPos) ||
			contains(region->widthMaxPos, region->heightMinPos)
		);
	}

	inline bool isBaseArea() {
		return (type == BASE);
	}

	inline bool isActiveArea() {
		return (type == ACTIVE);
	}

	inline bool isNoBuildArea() {
		return (type == NOBUILD);
	}

	//Setters
	inline void setWidth(float w) {
		width = w;
	}

	inline void setHeight(float h) {
		height = h;
	}

	inline void setUID(uint64 uid) {
		this->uid = uid;
	}

	//Getters
	inline float getWidth() {
		return width;
	}

	inline float getHeight() {
		return height;
	}

	inline float getMinX() {
		return widthMinPos;
	}

	inline float getMaxX() {
		return widthMaxPos;
	}

	inline float getMinY() {
		return heightMinPos;
	}

	inline float getMaxY() {
		return heightMaxPos;
	}

	inline uint64 getUID() {
		return uid;
	}
};
#endif /* AREAIMPLEMENTATION_H_ */
