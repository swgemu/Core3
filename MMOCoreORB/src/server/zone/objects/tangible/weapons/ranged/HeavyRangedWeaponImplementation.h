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

#ifndef HEAVYRANGEDWEAPONIMPLEMENTATION_H_
#define HEAVYRANGEDWEAPONIMPLEMENTATION_H_

#include "../../../player/Player.h"

#include "HeavyRangedWeapon.h"

class HeavyRangedWeaponImplementation : public HeavyRangedWeaponServant {
	
public:
	HeavyRangedWeaponImplementation(uint64 objid, uint32 tempcrc, const UnicodeString& n, const String& tempn, bool eqp = false) 
			: HeavyRangedWeaponServant(objid, tempcrc, n, tempn, TangibleObjectImplementation::HEAVYWEAPON, eqp) {
		initialize();
	}

	HeavyRangedWeaponImplementation(CreatureObject* creature, const String& temp, const UnicodeString& n, const String& tempn, bool eqp = false) 
			: HeavyRangedWeaponServant(creature, temp, n, tempn, TangibleObjectImplementation::HEAVYWEAPON, eqp) {
		initialize();
	}

	void initialize() {
		objectSubType = TangibleObjectImplementation::HEAVYWEAPON;
		
		setType(HEAVYROCKETLAUNCHER);
		setCategory(RANGED);
		
		setDamageType(BLAST);
		setArmorPiercing(HEAVY);
		
		setUsesRemaining(50);
		
		setAttackSpeed(7.1f);
		
		setMinDamage(678);
		setMaxDamage(1217);
		setWoundsRatio(36);
		
		setPointBlankAccuracy(-100);
		setPointBlankRange(0);
		
		setIdealAccuracy(22);
		setIdealRange(48);
		
		setMaxRangeAccuracy(21);
		setMaxRange(64);

		setHealthAttackCost(114);
		setActionAttackCost(75);
		setMindAttackCost(65);
		
		cert = "cert_heavy_rocket_launcher";
	}
	
	int useObject(Player* player) {
		SceneObject* obj = player->getTarget();
	
		if (obj == NULL) {
			player->sendSystemMessage("Invalid target");
			return 0;
		}
	
		if (!obj->isPlayer() && !obj->isNonPlayerCreature()) {
			player->sendSystemMessage("Invalid target");
			return 0;
		}
	
		player->sendSystemMessage("Firing rocket");	
	
		/*player->doCombatAnimation((CreatureObject*)obj, 0x683374B3, true);
	
		int healthDmg = System::random((int)maxDamage - (int)minDamage) + (int)minDamage;
		int actionDmg = System::random((int)maxDamage - (int)minDamage) + (int)minDamage;
		int mindDmg = System::random((int)maxDamage - (int)minDamage) + (int)minDamage;
	
		((CreatureObject*)obj)->changeHAMBars(-healthDmg, -actionDmg, -mindDmg, true);
		
		if (!decreaseUsesRemaining()) {
			//remove(player, false);
			return 0;
		}
		 */
		return 0;
	}
	
	/*void remove(Player* player) {
		ItemManager* itemManager = player->getZone()->getZoneServer()->getItemManager();
		
		itemManager->deletePlayerItem(player, _this, false);
		
		player->removeInventoryItem(objectID);
		
		BaseMessage* msg = new SceneObjectDestroyMessage(objectID);
		player->sendMessage(msg);
	}*/
	
};

#endif /*HEAVYRANGEDWEAPONIMPLEMENTATION_H_*/
