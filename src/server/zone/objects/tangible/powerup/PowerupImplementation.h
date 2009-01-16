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

#ifndef POWERUPIMPLEMENTATION_H_
#define POWERUPIMPLEMENTATION_H_

#include "engine/engine.h"
#include "Powerup.h"

class Zone;
class Player;

class PowerupImplementation : public PowerupServant {
protected:
	int type;
	int subType;

	int powerup0Type;
	float powerup0Value;
	int powerup1Type;
	float powerup1Value;
	int powerup2Type;
	float powerup2Value;

	int uses;

public:
	static const int MELEE = 1;
	static const int RANGED = 2;
	static const int MINE = 3;
	static const int THROWN = 4;

	static const int BARREL = 1;
	static const int COUPLER = 2;
	static const int GRIP = 3;
	static const int MUZZLE = 4;
	static const int SCOPE = 5;
	static const int STOCK = 6;

public:
	PowerupImplementation(uint64 objID, uint32 tempCRC, const UnicodeString& n, const String& tempn);
	PowerupImplementation(uint64 objID);

	virtual ~PowerupImplementation();

	void initialize();

	void generateName();

	void generateAttributes(SceneObject* obj);

	void updateCraftingValues(DraftSchematic* draftSchematic);

	void parseItemAttributes();

	void addAttributes(AttributeListMessage* alm);

	void setPowerupStats(int modifier);

	void apply(Weapon* weapon);

	void remove(Player* player);

	inline void setPowerupType(int value) {
		type = value;
		String name = "type";
		itemAttributes->setIntAttribute(name, value);
	}

	inline void setPowerupSubType(int value) {
		subType = value;
		String name = "subType";
		itemAttributes->setIntAttribute(name, value);
	}

	inline void setPowerup0Type(int value) {
		powerup0Type = value;
		String name = "powerup0Type";
		itemAttributes->setIntAttribute(name, value);
	}

	inline void setPowerup1Type(int value) {
		powerup1Type = value;
		String name = "powerup1Type";
		itemAttributes->setIntAttribute(name, value);
	}

	inline void setPowerup2Type(int value) {
		powerup2Type = value;
		String name = "powerup2Type";
		itemAttributes->setIntAttribute(name, value);
	}

	inline void setPowerup0Value(float value) {
		powerup0Value = value;
		String name = "powerup0Value";
		itemAttributes->setFloatAttribute(name, value);
	}

	inline void setPowerup1Value(float value) {
		powerup1Value = value;
		String name = "powerup1Value";
		itemAttributes->setFloatAttribute(name, value);
	}

	inline void setPowerup2Value(float value) {
		powerup2Value = value;
		String name = "powerup2Value";
		itemAttributes->setFloatAttribute(name, value);
	}

	inline void setPowerupUses(int value) {
		uses = value;
		String name = "uses";
		itemAttributes->setIntAttribute(name, value);
	}

	inline int getPowerup0Type() {
		return powerup0Type;
	}
	inline int getPowerup1Type() {
		return powerup1Type;
	}
	inline int getPowerup2Type() {
		return powerup2Type;
	}
	inline float getPowerup0Value() {
		return powerup0Value;
	}
	inline float getPowerup1Value() {
		return powerup1Value;
	}
	inline float getPowerup2Value() {
		return powerup2Value;
	}
	inline int getPowerupUses() {
		return uses;
	}
	inline int getPowerupType() {
		return type;
	}
	inline int getPowerupSubType() {
		return subType;
	}

};

#endif

