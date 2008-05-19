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

#ifndef HEALSELFSKILL_H_
#define HEALSELFSKILL_H_

#include "../SelfSkill.h"

class HealSelfSkill : public SelfSkill {
protected:
	int healHealth;
	int healAction;
	int healMind;
	
	bool healDamage;

	float speed;

	bool healDizzy;
	bool healStun;
	bool healBlind;
	bool healIntimidate;
	
	bool healPoison;
	bool healDisease;
	bool healBleeding;
	bool healFire;
	
public:
	HealSelfSkill(const string& name, const char* aname, ZoneProcessServerImplementation* serv) : SelfSkill(name, aname, HEAL, serv) {
		speed = 0.0f;

		healHealth = 0;
		healAction = 0;
		healMind = 0;
		
		healDizzy = false;
		healStun = false;
		healBlind = false;
		healIntimidate = false;
		
		healPoison = false;
		healDisease = false;
		healBleeding = false;
		healFire = false;
	}
	
	void doSkill(CreatureObject* creature, string& modifier) {
		calculateHeal(creature);
		doAnimations(creature);
	}
	
	bool isUseful(CreatureObject* creature) {
		if (creature->isOnFullHealth() && !creature->hasStates())
			return false;
		return true;
	}
	
	float calculateSpeed(CreatureObject* creature) {
		return speed;
	}
	
	void doAnimations(CreatureObject* creature) {
		if (effectName.size() != 0)
			creature->playEffect(effectName, "");
			
		if (secondaryAnim.size() != 0)
			creature->doAnimation(secondaryAnim);
	}

	void calculateHeal(CreatureObject* creature) {
		if (healDamage) {
			float medicineUse = (float)creature->getSkillMod("healing_ability");
			
			float health = (float)healHealth * (medicineUse / 100);
			float action = (float)healAction * (medicineUse / 100);
			float mind = (float)healMind * (medicineUse / 100);
			
			creature->changeHAMBars((int)health, (int)action, (int)mind);
		}

		if (healDizzy && creature->isDizzied())
			creature->clearState(CreatureObjectImplementation::DIZZY_STATE);

		if (healBlind && creature->isBlinded())
			creature->clearState(CreatureObjectImplementation::BLINDED_STATE);

		if (healStun && creature->isStunned())
			creature->clearState(CreatureObjectImplementation::STUNNED_STATE);
	
		if (healPoison && creature->isPoisoned())
			creature->clearState(CreatureObjectImplementation::POISONED_STATE);
			
		if (healFire && creature->isOnFire())
			creature->clearState(CreatureObjectImplementation::ONFIRE_STATE);
			
		if (healBleeding && creature->isBleeding())
			creature->clearState(CreatureObjectImplementation::BLEEDING_STATE);
		
		if (healDisease && creature->isDiseased())
			creature->clearState(CreatureObjectImplementation::DISEASED_STATE);
			
		if (healIntimidate && creature->isIntimidated())
			creature->clearState(CreatureObjectImplementation::INTIMIDATED_STATE);
		
		creature->updateStates();
		
	}
	
	virtual bool calculateCost(CreatureObject* creature) {
		if (creature->isKnockedDown()) {
			creature->sendSystemMessage("You can't heal while KnockedDown.");
			return false;
		}
		else
			return creature->changeMindBar(-150);
	}
	
	void setHealHealth(int hea) {
		healHealth = hea;
		healDamage = true;
	}
	
	void setHealAction (int act) {
		healAction = act;
		healDamage = true;
	}
	
	void setHealMind (int mnd) {
		healMind = mnd;
		healDamage = true;
	}

	void setSpeed(float sp) {
		speed = sp;
	}

	void setHealDizzy(bool doheal) {
		healDizzy = doheal;
	}

	void setHealStun(bool doheal) {
		healStun = doheal;
	}

	void setHealBlind(bool doheal) {
		healBlind = doheal;
	}
	
	void setHealIntimidate(bool doheal) {
		healIntimidate = doheal;
	}
	
	void setHealPoison(bool doheal) {
		healPoison = doheal;
	}
	
	void setHealFire(bool doheal) {
		healFire = doheal;
	}
	
	void setHealDisease(bool doheal) {
		healDisease = doheal;
	}
	
	void setHealBleeding(bool doheal) {
		healBleeding = doheal;
	}

	inline bool getHealDamage() {
		return healAction || healHealth || healMind;
	}

};

#endif /*HEALSELFSKILL_H_*/
