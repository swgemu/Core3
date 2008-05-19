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

#ifndef ENHANCESELFSKILL_H_
#define ENHANCESELFSKILL_H_

#include "../SelfSkill.h"

class EnhanceSelfSkill : public SelfSkill {
protected:
	float speed;

	float duration;
	
	int healthBonus;
	int actionBonus;
	int mindBonus;

	int accuracyBonus;
	int defenseBonus;
	
	int damageBonus;
	float speedBonus;
	
	string startFlyText;
	string finishFlyText;
	
	int state;
	
	int requiredState;

public:
	EnhanceSelfSkill(const string& Name, const char* effect, ZoneProcessServerImplementation* serv) : SelfSkill(Name, effect, ENHANCE, serv) {
		duration = 0;
		
		healthBonus = 0;
		actionBonus = 0;
		mindBonus = 0;
				
		damageBonus = 0;
		accuracyBonus = 0;
		
		defenseBonus = 0;
		speedBonus = 0.f;
		
		speed = 0.f;
		
		state = 0;
		
		requiredState = 0;
	}
	
	void doSkill(CreatureObject* creature, string& modifier) {
		calculateEnhancements(creature);
		doAnimations(creature);
		
		creature->addQueuedState(nameCRC);
	}
	
	void doAnimations(CreatureObject* creature) {
		if (startFlyText.size() != 0)
			creature->showFlyText("combat_effects", startFlyText , 0, 255, 0);
			
		if (effectName.size() != 0)
			creature->playEffect(effectName, "");
	}
	
	void finish(CreatureObject* creature) {
		if (!creature->removeQueuedState(nameCRC))
			return;
		
		removeEnhancements(creature);
		
		if (finishFlyText.size() != 0)
			creature->showFlyText("combat_effects", finishFlyText, 255, 0, 0);
	}
		
	float calculateSpeed(CreatureObject* creature) {
		return speed;
	}

	void calculateEnhancements(CreatureObject* creature) {
		if (healthBonus != 0)
			creature->changeMaxHealthBar(healthBonus);
		
		if (actionBonus != 0)
			creature->changeMaxActionBar(actionBonus);
		
		if (mindBonus != 0)
			creature->changeMaxMindBar(mindBonus);
		
		if (accuracyBonus != 0)
			creature->setAccuracy(creature->getAccuracy() + accuracyBonus);
		
		if (damageBonus != 0)
			creature->setDamageBonus(creature->getDamageBonus() + damageBonus);
		
		if (defenseBonus != 0)
			creature->setDefenseBonus(creature->getDefenseBonus() + defenseBonus);
		
		if (state != 0)
			creature->setState(state);
	}
	
	void removeEnhancements(CreatureObject* creature) {
		if (healthBonus != 0)
			creature->changeMaxHealthBar(-healthBonus);

		if (actionBonus != 0)
			creature->changeMaxActionBar(-actionBonus);

		if (mindBonus != 0)
			creature->changeMaxMindBar(-mindBonus);

		if (accuracyBonus != 0)
			creature->setAccuracy(creature->getAccuracy() - accuracyBonus);

		if (damageBonus != 0)
			creature->setDamageBonus(creature->getDamageBonus() - damageBonus);

		if (defenseBonus != 0)
			creature->setDefenseBonus(creature->getDefenseBonus() - defenseBonus);
		
		if (state != 0)
			creature->clearState(state);
	}
	
	bool isUseful(CreatureObject* creature) {
		if (creature->hasQueuedState(nameCRC))
			return false;
		else
			return true;
	}
	
	virtual bool calculateCost(CreatureObject* creature) {
		if (requiredState != 0) {
			if (requiredState == 0x123) {
				if (!creature->isMeditating())
					return false;
				else
					return true;
			} else if (!creature->hasState(requiredState))
				return false;
		}
		
		return true;
	}
	
	void setHealthBonus(int hl) {
		healthBonus = hl;
	}
	
	void setActionBonus(int bn) {
		actionBonus = bn;
	}
	
	void setMindBonus(int mb) {
		mindBonus = mb;
	}

	void setDamageBonus(int bn) {
		damageBonus = bn;
	}
	
	void setAccuracyBonus(int bn) {
		accuracyBonus = bn;
	}

	void setDefenseBonus(int def) {
		defenseBonus = def;
	}

	void setSpeedBonus(float speed) {
		speedBonus = speed;
	}

	void setFlyText(const string& name, const string& fname) {
		startFlyText = name;
		finishFlyText = fname;
	}
	
	void setDuration(float dur) {
		duration = dur;
	}
	
	void setSpeed(float sp) {
		speed = sp;
	}
	
	void setRequiredState(int st) {
		requiredState = st;
	}
	
	inline int getDamageBonus() {
		return damageBonus;
	}

	inline int getAccuracyBonus() {
		return accuracyBonus;
	}
	
	inline int getdDefenseBonus() {
		return defenseBonus;
	}
	
	inline float getSpeedBonus() {
		return speedBonus;
	}
	
	inline float getDuration() {
		return duration;
	}
	
};

#endif /*ENHANCESELFSKILL_H_*/
