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

#ifndef POWERBOOSTSELFSKILL_H_
#define POWERBOOSTSELFSKILL_H_

#include "../SelfSkill.h"

class PowerboostSelfSkill : public SelfSkill {

protected:

	float bonus;
	String effect;

public:
	PowerboostSelfSkill(const String& name, const String& eff, ZoneProcessServerImplementation* serv) : SelfSkill(name, eff.toCharArray(), OTHER, serv) {
		effect = eff;
	}

	void doSkill(CreatureObject* creature, String& modifier) {
		if (creature->isPlayer()) {
			Player* player = (Player*) creature;
			if (!player->doPowerboost())
				return;
		}

		int baseMind = creature->getBaseMind();

		//Calculate the Powerboost bonus.
		float hamBonus = (float)baseMind * bonus;
		int pbBonus = (int)hamBonus;
		int pbMind = pbBonus * 2;
		int pbTick = pbBonus / 20;

		//Subtract from the mind pool.
		creature->changeMaxMindBar(-pbBonus);

		//Apply the buff.
		creature->setpbHA(pbBonus);
		creature->setpbMind(pbMind);
		creature->setpbTick(pbTick);
		creature->setpbBonus(pbBonus);

		//Play the effect.
		doEffect(creature);
	}

	void finish(Player* player) {
		CreatureObject* creature = (CreatureObject*)player;
		player->sendSystemMessage("teraskasi", "powerboost_wane"); //"[meditation] You feel the effects of your mental focus begin to wane."

		//Remove the buff.
		int pbBonus = creature->getpbBonus();
		creature->setpbHA(-pbBonus);
		creature->setpbMind(-pbBonus);
		creature->setpbTick(-pbBonus / 20);
		creature->setpbBonus(0);
	}

	void doEffect(CreatureObject* creature) {
		if (!effect.isEmpty()) {
			creature->playEffect(effect, "");
		}
	}

	void setBonus(float bon) {
		bonus = bon;
	}

	float getBonus() {
		return bonus;
	}

	float calculateSpeed(CreatureObject* creature) {
		return 1.0;
	}

	bool calculateCost(CreatureObject* creature) {
		if (!creature->isMeditating() || creature->isInCombat() || creature->isRidingMount())
			return false;
		else
			return true;
	}
};

#endif /*POWERBOOSTSELFSKILL_H_*/
