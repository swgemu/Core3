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

#ifndef BASEAREAIMPLEMENTATION_H_
#define BASEAREAIMPLEMENTATION_H_

#include "engine/engine.h"
#include "Area.h"
#include "ActiveArea.h"
#include "NoBuildArea.h"
#include "BaseArea.h"

#include "AreaImplementation.h"

class BaseAreaImplementation : public BaseAreaServant {
protected:
	Vector<ActiveArea *> activeAreas;
	Vector<NoBuildArea *> noBuildAreas;

public:
	BaseAreaImplementation(Coordinate * center, float width, float height) : BaseAreaServant(center, width, height) {

	}

	BaseAreaImplementation(float minXPos, float maxXPos, float minYPos, float maxYPos) : BaseAreaServant(minXPos, maxXPos, minYPos, maxYPos) {

	}

	~BaseAreaImplementation() {
		activeAreas.removeAll();
		noBuildAreas.removeAll();
	}

	inline uint8 getType() {
		return BASE;
	}

	inline bool containsActiveAreas() {
		return !activeAreas.isEmpty();
	}

	inline bool containsNoBuildAreas() {
		return !noBuildAreas.isEmpty();
	}

	void addArea(Area * ar) {
		if (!this->contains(ar))
			return;

		switch (ar->getType()) {
		case ACTIVE:
			activeAreas.add((ActiveArea *) ar);
		case NOBUILD:
			noBuildAreas.add((NoBuildArea *) ar);
		}
	}

	void removeArea(Area * ar) {
		if (!this->contains(ar))
			return;

		switch (ar->getType()) {
		case ACTIVE:
			activeAreas.removeElement((ActiveArea *) ar);
		case NOBUILD:
			noBuildAreas.removeElement((NoBuildArea *) ar);
		}
	}

	NoBuildArea * getNoBuildArea(float x, float y) {
		for (uint32 i = 0; i < noBuildAreas.size(); i++) {
			NoBuildArea * temp = noBuildAreas.get(i);
			if (temp->contains(x,y))
				return temp;
		}

		return NULL;
	}

	ActiveArea * getNoActiveArea(float x, float y) {
		for (uint32 i = 0; i < activeAreas.size(); i++) {
			ActiveArea * temp = activeAreas.get(i);
			if (temp->contains(x,y))
				return temp;
		}

		return NULL;
	}
};

#endif /* BASEAREAIMPLEMENTATION_H_ */
