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

#ifndef SHIPCOMPONENTIMPLEMENTATION_H_
#define SHIPCOMPONENTIMPLEMENTATION_H_

#include "engine/engine.h"

#include "ShipComponent.h"

#include "../../player/Player.h"

#include "../TangibleObject.h"
#include "../TangibleObjectImplementation.h"

class ShipComponentImplementation : public ShipComponentServant {
protected:
	int tempComponentId;
	int componentType;
	uint32 componentCrc;
	float curArmor;
	float maxArmor;
	float curHitpoints;
	float maxHitpoints;
	float energyDrain;
	float mass;

	Player* ply;

	/*
	 public:
	 static const int REACTOR = 0;
	 static const int ENGINE = 1;
	 static const int SHIELD = 2;
	 static const int FRONT_ARMOR = 3;
	 static const int REAR_ARMOR = 4;
	 static const int CAPACITOR = 5;
	 static const int BOOSTER = 6;
	 static const int DROID_INTERFACE = 7;
	 static const int WEAPON = 8;
	 static const int ORDNANCE = 9;
	 static const int AMMO = 10;
	 static const int COUNTER_LAUNCHER = 11;
	 static const int COUNTER_PACK = 12;
	 static const int FLIGHT_COMP = 13;
	 */

public:
	ShipComponentImplementation(Player* player, uint32 tempCRC,
			const UnicodeString& n, const String& tempn) :
		ShipComponentServant(player->getNewItemID(), SHIPCOMPONENT) {
		objectCRC = tempCRC;

		name = n;

		templateTypeName = "wearables_name"; //figure out what this is for components
		templateName = tempn;

		ply = player;

		tempComponentId = 0;
		componentCrc = 0;
		curArmor = 0.0f;
		maxArmor = 0.0f;
		curHitpoints = 0.0f;
		maxHitpoints = 0.0f;
		energyDrain = 0.0f;
		mass = 0.0f;
		componentType = 0xFF;

		setParent((TangibleObject*) player->getInventory(), 0xFFFFFFFF);
	}

	~ShipComponentImplementation() {
	}

	void erase() {
		componentCrc = 0;
		curArmor = 0.0f;
		maxArmor = 0.0f;
		curHitpoints = 0.0f;
		maxHitpoints = 0.0f;
		energyDrain = 0.0f;
		mass = 0.0f;
	}

	int useObject(Player* player) {
		return 0;
	}

	//val manip

	inline uint32 getComponentCrc() {
		return componentCrc;
	}

	inline void setComponentCrc(uint32 tcc) {
		componentCrc = tcc;
	}

	inline float getCurArmor() {
		return curArmor;
	}

	inline void setCurArmor(float tca) {
		curArmor = tca;
	}

	inline float getMaxArmor() {
		return maxArmor;
	}

	inline void setMaxArmor(float tma) {
		maxArmor = tma;
	}

	inline float getCurHitpoints() {
		return curHitpoints;
	}

	inline void setCurHitpoints(float tch) {
		curHitpoints = tch;
	}

	inline float getMaxHitpoints() {
		return maxHitpoints;
	}

	inline void setMaxHitpoints(float tmh) {
		maxHitpoints = tmh;
	}

	inline float getEnergyDrain() {
		return energyDrain;
	}

	inline void setEnergyDrain(float ted) {
		energyDrain = ted;
	}

	inline float getMass() {
		return mass;
	}

	inline void setMass(float tm) {
		mass = tm;
	}

	//type set/get

	inline void setCompType(int tct) {
		componentType = tct;
	}

	inline bool getCompType() {
		return componentType;
	}

	/*
	 inline bool isReactor() {
	 componentType == REACTOR;
	 }

	 inline bool isEngine() {
	 componentType == ENGINE;
	 }

	 inline bool isShield() {
	 componentType == SHIELD;
	 }

	 inline bool isFrontArmor() {
	 componentType == FRONT_ARMOR;
	 }

	 inline bool isRearArmor() {
	 componentType == REAR_ARMOR;
	 }

	 inline bool isCapacitor() {
	 componentType == CAPACITOR;
	 }

	 inline bool isBooster() {
	 componentType == BOOSTER;
	 }

	 inline bool isDroidInterface() {
	 componentType == DROID_INTERFACE;
	 }

	 inline bool isWeapon() {
	 componentType == WEAPON;
	 }

	 inline bool isOrdnance() {
	 componentType == ORDNANCE;
	 }

	 inline bool isAmmo() {
	 componentType == AMMO;
	 }

	 inline bool isCounterLauncher() {
	 componentType == COUNTER_LAUNCHER;
	 }

	 inline bool isCounterPack() {
	 componentType == COUNTER_PACK;
	 }

	 inline bool isFlightComputer() {
	 componentType == FLIGHT_COMP;
	 }
	 */

};

#endif /*SHIPCOMPONENT_H_*/
