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

#ifndef SHIPOBJECTIMPLEMENTATION_H_
#define SHIPOBJECTIMPLEMENTATION_H_

#include "engine/engine.h"

#include "../scene/SceneObject.h"
#include "../scene/SceneObjectImplementation.h"

#include "../player/Player.h"
#include "../player/PlayerImplementation.h"

#include "../intangible/IntangibleObject.h"
#include "../intangible/IntangibleObjectImplementation.h"

#include "../tangible/component/ShipComponent.h"
#include "../tangible/component/ShipComponentImplementation.h"

//class CreatureObject;

class ShipObjectImplementation : public ShipObjectServant {
	Player* owner;

	IntangibleObject* shipBody;

	String stfName;
	UnicodeString ownerName;

	int activeComponentListSize;

	//SHIP1 vars
	uint32 unkShip1UpdateCnt;
	uint32 unkShip1UpdateCnt2;
	uint32 energyDrainUpdateCnt;
	uint32 compMassUpdateCnt;
	uint32 unkShip1UpdateCnt3;
	float shieldChargeRate;
	float capacitorChargeRate;
	float totalEnergy;

	//SHIP3 vars
	float chassisCur;
	float chassisMax;
	uint32 curArmorUpdateCnt;
	uint32 maxArmorUpdateCnt;
	uint32 curHitpointsUpdateCnt;
	uint32 maxHitpointsUpdateCnt;
	uint32 unkShip3UpdateCnt;
	float frontshieldMax; //denom
	float backshieldMax; //denom

	//SHIP4 vars
	float totalMass;

	//SHIP6 vars
	uint32 crcUpdateCnt;
	float maxSpeed;
	float frontshieldCur; //numer
	float backshieldCur; //numer

private:
	Vector<ShipComponent*> componentList;

public:
	ShipObjectImplementation(uint64 oid, Player* SOwner);

	~ShipObjectImplementation();

	void init();

	void sendToOwner(bool inSpace);
	void sendTo(Player* player, bool inSpace, bool doClose = true);

	inline void setShipBody(IntangibleObject* tsb) {
		shipBody = tsb;
	}

	IntangibleObject* getShipBody() {
		return shipBody;
	}

	inline void setStfName(const String& Name) {
		stfName = Name;
	}

	inline String& getStfName() {
		return stfName;
	}

	inline UnicodeString& getOwnerName() {
		return ownerName;
	}

	//<Component Funcs>
	inline int getComponentListSize() {
		return componentList.size();
	}

	inline void calcActiveComponentListSize() {
		activeComponentListSize = 0;
		for (int i = 0; i < componentList.size(); i++) {
			if (componentList.get(i)->getComponentCrc() != 0) {
				activeComponentListSize++;
			}
		}
	}

	inline int getActiveComponentListSize() {
		return activeComponentListSize;
	}

	void addComponent(ShipComponent* tsc);

	void removeComponent(int compId);

	ShipComponent* getComponent(int compId) {
		if (componentList.get(compId)->getComponentCrc() != 0) {
			return componentList.get(compId);
		} else {
			return NULL;
		}
	}
	//</Component Funcs>


	////////////////////////////////
	//SHIP1
	////////////////////////////////

	//<Delta/Update Counters>

	inline uint32 getNextUnkShip1UpdateCnt() {
		return unkShip1UpdateCnt++;
	}

	inline uint32 getNextUnkShip1UpdateCnt2() {
		return unkShip1UpdateCnt2++;
	}

	inline uint32 getNextEnergyDrainUpdateCnt() {
		return energyDrainUpdateCnt++;
	}

	inline uint32 getNextCompMassUpdateCnt() {
		return compMassUpdateCnt++;
	}

	inline uint32 getNextUnkShip1UpdateCnt3() {
		return unkShip1UpdateCnt3++;
	}

	//</Delta/Update Counters>

	inline void setTotalMass(float ttm) {
		totalMass = ttm;
	}

	inline float getShieldChargeRate() {
		return shieldChargeRate;
	}

	inline float getCapacitorChargeRate() {
		return capacitorChargeRate;
	}

	inline void setTotalEnergy(float tte) {
		totalEnergy = tte;
	}

	inline float getTotalEnergy() {
		return totalEnergy;
	}


	////////////////////////////////
	//SHIP3
	////////////////////////////////

	inline float getChassisCur() {
		return chassisCur;
	}

	inline float getChassisMax() {
		return chassisMax;
	}

	//<Delta/Update Counters>

	inline uint32 getNextCurArmorUpdateCnt() {
		return curArmorUpdateCnt++;
	}

	inline uint32 getNextMaxArmorUpdateCnt() {
		return maxArmorUpdateCnt++;
	}

	inline uint32 getNextCurHitpointsUpdateCnt() {
		return curHitpointsUpdateCnt++;
	}

	inline uint32 getNextMaxHitpointsUpdateCnt() {
		return maxHitpointsUpdateCnt++;
	}

	inline uint32 getNextUnkShip3UpdateCnt() {
		return unkShip3UpdateCnt++;
	}

	//</Delta/Update Counters>

	inline float getFrontshieldMax() {
		return frontshieldMax;
	}

	inline float getBackshieldMax() {
		return backshieldMax;
	}


	////////////////////////////////
	//SHIP4
	////////////////////////////////

	inline float getTotalMass() {
		return totalMass;
	}

	inline float getWeaponCharge() {
		//pull the weapon component and get the current charge
		return 500.0f; //temp
	}


	////////////////////////////////
	//SHIP6
	////////////////////////////////

	//<Delta/Update Counters>

	inline uint32 getNextCrcUpdateCnt() {
		return crcUpdateCnt;
	}

	//</Delta/Update Counters>

	inline float getMaxSpeed() {
		return maxSpeed; //this value * 10 = max speed
	}

	inline float getFrontshieldCur() {
		return frontshieldCur;
	}

	inline float getBackshieldCur() {
		return backshieldCur;
	}



	friend class ShipObjectMessage1;
	friend class ShipObjectMessage3;
	friend class ShipObjectMessage4;
	friend class ShipObjectMessage6;

	//make sure to befriend deltas here as well

};

#endif /*SHIPOBJECTIMPLEMENTATION_H_*/
