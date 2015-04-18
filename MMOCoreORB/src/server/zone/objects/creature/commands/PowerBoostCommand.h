/*
				Copyright <SWGEmu>
		See file COPYING for copying conditions.*/

#ifndef POWERBOOSTCOMMAND_H_
#define POWERBOOSTCOMMAND_H_

#include "server/zone/objects/scene/SceneObject.h"
#include "server/zone/managers/player/PlayerManager.h"
#include "server/zone/objects/creature/CreatureAttribute.h"

#include "server/zone/objects/creature/buffs/PowerBoostBuff.h"

class PowerBoostCommand : public QueueCommand {
public:

	PowerBoostCommand(const String& name, ZoneProcessServer* server)
		: QueueCommand(name, server) {
	}

	int doQueueCommand(CreatureObject* creature, const uint64& target, const UnicodeString& arguments) const {

		if (!checkStateMask(creature))
			return INVALIDSTATE;

		if (!creature->isPlayerCreature())
			return GENERALERROR;

		//return GENERALERROR;

		//TODO: fix powerboost cancel

		// Replaced INVALIDLOCOMOTION check to return message if user is not meditating.
		if(!creature->isMeditating()) {
			creature->sendSystemMessage("@teraskasi:powerboost_fail"); // You must be meditating to perform that command.
			return GENERALERROR;
		}

		CreatureObject* player = cast<CreatureObject*>(creature);

		uint32 buffcrc = BuffCRC::SKILL_BUFF_POWERBOOST;

		if(player->hasBuff(buffcrc)) {
			player->sendSystemMessage("@teraskasi:powerboost_active"); // [meditation] You are unable to channel your energies any further.
			return GENERALERROR;
		}

		int baseMind = player->getBaseHAM(CreatureAttribute::MIND);

		int pbBonus = baseMind / 2;

		int meditateMod = player->getSkillMod("meditate");

		/*
		 * Taken from scrapbook
		 * Duration: 5 min + (meditate skill mod/100 * 5min)
		 */
		int duration = 300 + ((meditateMod/100) * 300);

		if(player->getHAM(CreatureAttribute::MIND) <= pbBonus) {
			player->sendSystemMessage("@teraskasi:powerboost_mind"); // [mediation] You currently lack the mental capacity to focus your energies.
			return GENERALERROR;
		}

		String buffname = "skill.buff.powerboost";
		ManagedReference<Buff*> buff = new PowerBoostBuff(player, buffname, buffname.hashCode(), pbBonus, duration);
		player->addBuff(buff);

		return SUCCESS;
	}

};

#endif //POWERBOOSTCOMMAND_H_
