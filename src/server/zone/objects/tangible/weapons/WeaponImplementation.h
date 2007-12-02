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

#ifndef WEAPONIMPLEMENTATION_H_
#define WEAPONIMPLEMENTATION_H_

#include "../../creature/CreatureObject.h"
#include "../../creature/CreatureObjectImplementation.h"

#include "../TangibleObject.h"

#include "../Inventory.h"
#include "../InventoryImplementation.h"

#include "Weapon.h"

class CombatManager;

class WeaponImplementation : public WeaponServant {
protected:
	int type;
	
	int category;

	float minDamage;
	float maxDamage;
	
	float attackSpeed;
	
	int healthAttackCost;
	int actionAttackCost;
	int mindAttackCost;
	
	int pointBlankAccuracy;
	int pointBlankRange;
	
	int idealRange;
	int idealAccuracy;
	
	int maxRange;
	int maxRangeAccuracy;
	
	int woundsRatio;
	
	int armorPiercing;

public:

	static const int MELEE = 0x10;
	static const int RANGED = 0x20;
	static const int JEDI = 0x30;

	static const int UNARMED = 0;
	static const int ONEHANDED = 1;
	static const int TWOHANDED = 2;
	static const int POLEARM = 3;
	static const int PISTOL = 4;
	static const int CARBINE = 5;
	static const int RIFLE = 6;
	static const int ONEHANDSABER = 7;
	static const int TWOHANDSABER = 8;
	static const int POLEARMSABER = 9;
	
	static const int NONE = 0;
	static const int LIGHT = 1;
	static const int MEDIUM = 2;
	static const int HEAVY = 3;
	 

public:
	WeaponImplementation(uint64 objid, uint32 tempCRC, const unicode& n, const string& tempn, bool eqp, int tp, int cat) 
			: WeaponServant(objid, n, tempn, tempCRC, WEAPON) {
		type = tp;
		category = cat;
		
		equipped = eqp;

		initialize();
}

	WeaponImplementation(CreatureObject* creature, const string& temp, const unicode& n, const string& tempn, bool eqp, int tp, int cat) 
			: WeaponServant(creature->getNewItemID(), WEAPON) {
		objectCRC = String::hashCode(temp);

		name = n;
		
		type = tp;
		category = cat;
		
		templateName = tempn;

		if (equipped = eqp)
			setContainer(creature, 0x04);
		else
			setContainer(creature->getInventory(), 0xFFFFFFFF);
		
		initialize();
	}

	void initialize() {
		templateTypeName = "weapon_name";

		minDamage = 50;
		maxDamage = 100;
		
		attackSpeed = 1.0f;
		
		healthAttackCost = 15;
		actionAttackCost = 10;
		mindAttackCost = 5;
		
		pointBlankRange = 0;
		pointBlankAccuracy = 0;
		
		idealRange = 2;
		idealAccuracy = 15;
				
		maxRange = 5;
		maxRangeAccuracy = 0;
		
		woundsRatio = 10;
		
		armorPiercing = NONE;
	}
	
	void sendTo(Player* player, bool doClose = true);
	void generateAttributes(SceneObject* obj);

	inline float getMinDamage() {
		return minDamage;
	}

	inline float getMaxDamage() {
		return maxDamage;
	}

	inline float getAttackSpeed() {
		return attackSpeed;
	}

	inline int getHealthAttackCost() {
		return healthAttackCost;
	}

	inline int getActionAttackCost() {
		return actionAttackCost;
	}

	inline int getMindAttackCost() {
		return mindAttackCost;
	}
	
	inline int getType() {
		return type;
	}
	
	inline bool isJedi() {
		return (category == JEDI);
	}
	
	inline bool isMelee() {
		return (category == MELEE);
	}
	
	inline bool isRanged() {
		return (category == RANGED) ;
	}
	
	inline int getCategory() {
		return category;
	}
	
	inline int getPointBlankRange() {
		return pointBlankRange;
	}
	
	inline int getPointBlankAccuracy() {
		return pointBlankAccuracy;
	}
	
	inline int getMaxRange() {
		return maxRange;
	}
	
	inline int getMaxRangeAccuracy() {
		return maxRangeAccuracy;
	}
	
	inline int getIdealRange() {
		return idealRange;
	}
	
	inline int getIdealAccuracy() {
		return idealAccuracy;
	}
	
	inline int getWoundsRatio() {
		return woundsRatio;
	}

	friend class CombatManager;
	
};

#endif /*WEAPONIMPLEMENTATION_H_*/
