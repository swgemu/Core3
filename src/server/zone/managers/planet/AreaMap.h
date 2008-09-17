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

#ifndef AREAMAP_H_
#define AREAMAP_H_

#include "../../objects/area/Area.h"
#include "../../objects/area/BaseArea.h"
#include "../../objects/area/ActiveArea.h"
#include "../../objects/area/NoBuildArea.h"

class AreaMap {
	BaseArea * ** baseAreas;

	uint8 xCells;
	uint8 yCells;

	float mapWidth;
	float mapHeight;
	float baseAreaWidth;
	float baseAreaHeight;

	void createBaseAreas() {
		if (baseAreas == NULL)
			return;
		try {
			float yMin = -(mapHeight / 2);
			for(int i = 0; i < yCells; i++) {
				float xMin = -(mapWidth / 2);
				for(int j = 0; j < xCells; j++) {
					baseAreas[j][i] = new BaseArea(xMin, xMin + baseAreaWidth, yMin, yMin + baseAreaHeight);
					xMin += baseAreaWidth;
				}
				yMin += baseAreaHeight;
			}
		} catch (Exception e) {
			cout << "Exception caught in AreaMap: " << e.getMessage() << endl;
		} catch (...) {
			cout << "Unspecified Exception caught in AreaMap" << endl;
		}
	}

public:
	AreaMap(const float mapWidth, const float mapHeight, const float baseAreaWidth, const float baseAreaHeight) {
	  this->mapWidth = mapWidth;
	  this->mapHeight = mapHeight;
	  this->baseAreaWidth = baseAreaWidth;
	  this->baseAreaHeight = baseAreaHeight;

	  xCells = (uint8) ceil(mapWidth / baseAreaWidth);
	  yCells = (uint8) ceil(mapHeight / baseAreaHeight);

	  baseAreas = new BaseArea**[yCells];

	  if(baseAreas != NULL) {
		  for(uint8 i = 0; i < yCells; i++)
			  baseAreas[i] = new BaseArea*[xCells];
	  }

	  createBaseAreas();
	}

	~AreaMap() {
		for(int i = 0; i < yCells; i++) {
			for (int j=0; j<xCells; j++)
				delete(baseAreas[j][i]);
		}
	}

	BaseArea * getBaseArea(float x, float y) {
		const uint16 xIndex = (uint16) ceil((x + mapWidth / 2) / baseAreaWidth) - 1;
		const uint16 yIndex = (uint16) ceil((y + mapHeight / 2) / baseAreaHeight) - 1;

		if (xIndex >= xCells || yIndex >= yCells)
			throw Exception("Base Area out of Bounds!");

		return baseAreas[xIndex][yIndex];
	}

	void addArea(Area * area) {
		BaseArea * ba = getBaseArea(area->getMaxX(), area->getMaxY());
		BaseArea * ba2 = getBaseArea(area->getMinX(), area->getMaxY());
		BaseArea * ba3 = getBaseArea(area->getMinX(), area->getMinY());
		BaseArea * ba4 = getBaseArea(area->getMaxX(), area->getMinY());

		ba->addArea(area);

		if(ba2 != ba)
			ba2->addArea(area);

		if(ba3 != ba && ba3 != ba2)
			ba3->addArea(area);

		if(ba4 != ba && ba4 != ba2 && ba4 != ba3)
			ba4->addArea(area);
	}
};
#endif /* AREAMAP_H_ */
