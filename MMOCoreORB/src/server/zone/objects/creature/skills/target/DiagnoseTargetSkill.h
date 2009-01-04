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

#ifndef DIAGNOSETARGETSKILL_H_
#define DIAGNOSETARGETSKILL_H_

#include "../TargetSkill.h"
#include "../../../../objects.h"

class DiagnoseTargetSkill : public TargetSkill {
protected:
	String effectName;
	float speed;
	int mindCost;

public:
	DiagnoseTargetSkill(const String& name, const char* aname, ZoneProcessServerImplementation* serv) : TargetSkill(name, aname, DIAGNOSE, serv) {
		effectName = aname;
		speed = 0;
		mindCost = 0;
	}

	void doAnimations(CreatureObject* creature, CreatureObject* targetCreature) {
		if (!effectName.isEmpty())
			targetCreature->playEffect(effectName, "");

		if (creature == targetCreature)
			creature->doAnimation("heal_self");
		else
			creature->doAnimation("heal_other");
	}

	int doSkill(CreatureObject* creature, SceneObject* target, const String& modifier, bool doAnimation = true) {
		CreatureObject* creatureTarget;
		Player* player = (Player*) creature;

		if (target->isPlayer() || target->isNonPlayerCreature()) {
			creatureTarget = (CreatureObject*) target;
		} else {
			creature->sendSystemMessage("You can only diagnose a player or a creature.");
			return 0;
		}

		if (creatureTarget == creature) {
			creature->sendSystemMessage("You can't diagnose yourself.");
			return 0;
		}

		/*TODO: Close an already opened Diagnose box before sending a new one??
		if (player->hasSuiBox(SuiWindowType::DIAGNOSE))
			player->removeSuiBox(SuiWindowType::DIAGNOSE);
		*/

		String targetName = "";
		UnicodeString UnicodeStringName = UnicodeString("");
		UnicodeStringName = creatureTarget->getCharacterName();
		targetName = UnicodeStringName.toString();

		SuiListBox* sui = new SuiListBox(player, SuiWindowType::DIAGNOSE);
		StringBuffer title;
		title << "Patient " << targetName.toCharArray();
		sui->setPromptTitle(title.toString());

		StringBuffer text;
		text << "Below is a listing of the wound and Battle Fatigue levels of " << targetName.toCharArray() << ". Wounds are healed through /tendwound or use of wound Medpacks. High levels of Battle Fatigue can inhibit the healing process, and Battle Fatigue can only be healed by the patient choosing to watch performing entertainers.";
		sui->setPromptText(text.toString());
		sui->setCancelButton(false);

		StringBuffer health;
		health << "Health -- " << creatureTarget->getHealthWounds();
		sui->addMenuItem(health.toString());

		StringBuffer strength;
		strength << "Strength -- " << creatureTarget->getStrengthWounds();
		sui->addMenuItem(strength.toString());

		StringBuffer constitution;
		constitution << "Constitution -- " << creatureTarget->getConstitutionWounds();
		sui->addMenuItem(constitution.toString());

		StringBuffer action;
		action << "Action -- " << creatureTarget->getActionWounds();
		sui->addMenuItem(action.toString());

		StringBuffer quickness;
		quickness << "Quickness -- " << creatureTarget->getQuicknessWounds();
		sui->addMenuItem(quickness.toString());

		StringBuffer stamina;
		stamina << "Stamina -- " << creatureTarget->getStaminaWounds();
		sui->addMenuItem(stamina.toString());

		StringBuffer mind;
		mind << "Mind -- " << creatureTarget->getMindWounds();
		sui->addMenuItem(mind.toString());

		StringBuffer focus;
		focus << "Focus -- " << creatureTarget->getFocusWounds();
		sui->addMenuItem(focus.toString());

		StringBuffer willpower;
		willpower << "Willpower -- " << creatureTarget->getWillpowerWounds();
		sui->addMenuItem(willpower.toString());

		StringBuffer battlefatigue;
		battlefatigue << "Battle Fatigue -- " << creatureTarget->getShockWounds();
		sui->addMenuItem(battlefatigue.toString());

		player->addSuiBox(sui);
		player->sendMessage(sui->generateMessage());

		//TODO: Are there animations for diagnose?
		//doAnimations(creature, targetCreature);
		return 0;
	}

	virtual bool calculateCost(CreatureObject* creature) {
		return creature->changeMindBar(mindCost);
	}

	void setSpeed(float sp) {
		speed = sp;
	}

	void setEffectName(const String& name) {
		effectName = name;
	}

	inline float getSpeed() {
		return speed;
	}

	inline void setMindCost(int cost) {
		mindCost = cost;
	}

};

#endif /*DIAGNOSETARGETSKILL_H_*/
