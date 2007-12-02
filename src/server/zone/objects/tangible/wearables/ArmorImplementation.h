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

#ifndef ARMORIMPLEMENTATION_H_
#define ARMORIMPLEMENTATION_H_

#include "../../creature/CreatureObject.h"

#include "Armor.h"

class ArmorImplementation : public ArmorServant {
private:
	int rating;
	
	int healthEncumbrance;
	int actionEncumbrance;
	int mindEncumbrance;
	
	float kinetic;
	bool kineticIsSpecial;
	
	float energy;
	bool energyIsSpecial;
	
	float electricity;
	bool electricityIsSpecial;
	
	float stun;
	bool stunIsSpecial;
	
	float blast;
	bool blastIsSpecial;
	
	float heat;
	bool heatIsSpecial;
	
	float cold;
	bool coldIsSpecial;
	
	float acid;
	bool acidIsSpecial;
	
	float lightSaber;
	bool lightSaberIsSpecial;
	
public:

	static const int LIGHT = 0x10;
	static const int MEDIUM = 0x20;
	static const int HEAVY = 0x30;	
	
public:
	ArmorImplementation(uint64 objid, uint32 tempCRC, const unicode& n, const string& tempn, bool eqp = false)
			: ArmorServant(objid, tempCRC, n, tempn, eqp) {
		initialize();
	}

	ArmorImplementation(CreatureObject* creature, uint32 tempCRC, const unicode& n, const string& tempn, bool eqp = false)
			: ArmorServant(creature, tempCRC, n, tempn, eqp) {
		initialize();
	}

	void initialize() {
		objectSubType = ARMOR;
		
		rating = LIGHT;
		conditionDamage = 10000;
		maxCondition = 50000;
		 	
		healthEncumbrance = 300;
		actionEncumbrance = 124;
		mindEncumbrance = 87; 	
		 	
		kinetic = 50.0f;
		kineticIsSpecial = true;
	
		energy = 50.0f;
		energyIsSpecial = true;
	
		electricity = 50.0f;
		electricityIsSpecial = false;
	
		stun = 50.0f;
		stunIsSpecial = true;
	
		blast = 50.0f;
		blastIsSpecial = false;
	
		heat = 50.0f;
		heatIsSpecial = false;
	
		cold = 50.0f;
		coldIsSpecial = false;
	
		acid = 50.0f;
		acidIsSpecial = false;
	
		lightSaber = 50.0f;
		lightSaberIsSpecial = false;
	}
	
	void sendTo(Player* player, bool doClose = true);
	void generateAttributes(SceneObject* obj);
	
	inline int getRating() {
		return rating;
	}
	
	inline int getMaxCondition() {
		return maxCondition;
	}
	
	inline int getHealthEncumbrance() {
		return healthEncumbrance;
	}

	inline int getActionEncumbrance() {
		return actionEncumbrance;
	}

	inline int getMindEncumbrance() {
		return mindEncumbrance;
	}
	
	inline float getKinetic() {
		return kinetic;	
	}
	
	inline bool isKineticSpecial() {
		return kineticIsSpecial;
	}
	
	inline float getEnergy() {
		return energy;	
	}
	
	inline bool isEnergySpecial() {
		return energyIsSpecial;
	}
	
	inline float getElectricity() {
		return electricity;	
	}
	
	inline bool isElectricitySpecial() {
		return electricityIsSpecial;
	}
	
	inline float getStun() {
		return stun;	
	}
	
	inline bool isStunSpecial() {
		return stunIsSpecial;
	}
	
	inline float getBlast() {
		return blast;	
	}
	
	inline bool isBlastSpecial() { 
		return blastIsSpecial;
	}
	
	inline float getHeat() {
		return heat;	
	}
	
	inline bool isHeatSpecial() {
		return heatIsSpecial;
	}
	
	inline float getCold() {
		return cold;	
	}
	
	inline bool isColdSpecial() {
		return coldIsSpecial;
	}
	
	inline float getAcid() {
		return acid;	
	}
	
	inline bool isAcidSpecial() {
		return acidIsSpecial;
	}
	
	inline float getLightSaber() {
		return lightSaber;	
	}
	
	inline bool isLightSaberSpecial() {
		return lightSaberIsSpecial;
	}
};	
#endif /*ARMORIMPLEMENTATION_H_*/
