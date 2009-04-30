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

#ifndef TAMETARGETSKILL_H_
#define TAMETARGETSKILL_H_


#include "../../pet/CreaturePet.h"
#include "events/TameEvent.h"

class TameTargetSkill : public TargetSkill {

public:
	/*
	 * The constructor. Camo Type is set to NONE.
	 * \param name The skill name
	 * \param serv The ZoneProcessServerImplementation.
	 */
	TameTargetSkill(const String& name, ZoneProcessServerImplementation* serv) : TargetSkill(name, "", TAME, serv) {
	}


	/*
	 * Activates the target skill (conceal).
	 * \param creature The creature, that activates the skill.
	 * \param target The target to conceal, if null the self.
	 * \param modifier The modifiers, not used.
	 */
	virtual int doSkill(CreatureObject* creature, SceneObject* target, const String& modifier, bool doAnimation = true) {
		Player* player = (Player*) creature;

		if(player == NULL)
			return 0;
		if (!target->isNonPlayerCreature())
			return 0;

		Creature* targetCreature = (Creature*) target;

		if (targetCreature == NULL)
			return 0;

		if (!targetCreature->isBaby()) {
			player->sendSystemMessage("Failed to tame creature");
			return 0;
		}

		if (targetCreature->isInCombat()) {
			player->sendSystemMessage("Failed to tame creature");
			return 0;
		}

		if (targetCreature->isAggressive() && player->getSkillMod("tame_aggro") == 0) {
			player->sendSystemMessage("pet/pet_menu","sys_lack_skill");
			return 0;
		}

		if (targetCreature->getLevel() > player->getSkillMod("tame_level")) {
			player->sendSystemMessage("pet/pet_menu","sys_lack_skill");
			return 0;
		}

		if (!player->isInRange(targetCreature,10.0f)) {
			player->sendSystemMessage("Failed to tame creature");
			return 0;
		}

		int stage = 0;

		if (!modifier.isEmpty())
			stage = Integer::valueOf(modifier);

		tame(player,targetCreature,stage);
		return 0;

	}

	void tame(Player* player, Creature* creature, int stage) {
		if (player == NULL || creature == NULL)
			return;
		if (creature->isInCombat()) {
			player->sendSystemMessage("Failed to tame creature");
			return;
		}
		switch(stage) {
			case 0:
				if (!player->canStoreMorePets()) {
					player->sendSystemMessage("pet/pet_menu","sys_too_many_stored");
					return;
				}

				if (System::random(1) == 1)
					player->say("Good..er..boy?");
				else
					player->say("Don't be scared.");

			break;
			case 1:
				if (System::random(1) == 1)
					player->say("Steady");
				else
					player->say("Easy");
			break;
			case 2:
				player->say("Don't bite me.");
				bool notInRange = !player->isInRange(creature,10.0f);

				if (notInRange || (creature->isAggressive() && creature->getLevel() > System::random(player->getSkillMod("tame_aggro")))) {
					player->sendSystemMessage("Failed to tame Creature");
					if (System::random(1) == 1) {
						/*System::out << "attack aggro\n";
						creature->updateTarget(player);
						creature->setCombatState();*/
					}
					return;
				}else if (notInRange || creature->getLevel() > System::random(player->getSkillMod("tame_non_aggro"))) {
					player->sendSystemMessage("Failed to tame creature");
					if (System::random(4) == 1) {
						/*System::out << "attack\n";
						creature->updateTarget(player);
						creature->setCombatState();*/
					}
					return;
				}

				CreaturePet* pet = new CreaturePet(player,player->getNewItemID());

				if (pet == NULL) {
					return;
				}
				pet->init(creature,0.5f);
				creature->unload();
				pet->createDataPad();

				String chType = "creaturehandler";
				player->addXp(chType, pet->getLevel() * 50,true);
				//System::out << pet->isCreature() << "/" << pet->isNPC() << "/" << pet->isPlayer() <<"\n";
				//System::out << pet->isAggressive() << "/" << pet->isKiller() << "\n";
				//System::out << pet->isCHPet() << "/" << pet->isDroid() << "/" << pet->isFactionPet() <<"\n";
				return;

		}

		TameEvent* event = new TameEvent(player,creature,++stage);
		ZoneProcessServerImplementation* server = player->getZoneProcessServer();
		server->addEvent(event);

	}

	/*
	 * Does the animation.
	 * \param creature The creature The creature, that activates the skill.
	 */
	void doAnimations(CreatureObject* creature) {
	}


	/*
	 * Returns the speed of the skill.
	 * \return creature The creature The creature, that activates the skill.
	 */
	float calculateSpeed(CreatureObject* creature) {
			return 0;
	}

	/*
	 * Checks if the skill can be used
	 * \param creature The creature, that is checked.
	 * \return Returns false if not usefull else true.
	 */
	bool isUseful(CreatureObject* creature) {
		return true;
	}


	/*
	 * Calculates the costs of the skill.
	 * \param creature The creature, that is checked.
	 * \return Returns if costs are applied.
	 */
	virtual bool calculateCost(CreatureObject* creature) {
		return true;
	}

};

#endif
