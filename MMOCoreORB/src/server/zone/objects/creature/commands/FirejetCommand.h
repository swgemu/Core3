/*
				Copyright <SWGEmu>
		See file COPYING for copying conditions.*/

#ifndef FIREJETCOMMAND_H_
#define FIREJETCOMMAND_H_

class FirejetCommand : public QueueCommand {
public:

	FirejetCommand(const String& name, ZoneProcessServer* server)
		: QueueCommand(name, server) {

	}

	int doQueueCommand(CreatureObject* creature, const uint64& target, const UnicodeString& arguments) const {

		if (!checkStateMask(creature))
			return INVALIDSTATE;

		if (!checkInvalidLocomotions(creature))
			return INVALIDLOCOMOTION;

		if (!creature->isEntertaining()) {
			creature->sendSystemMessage("@performance:effect_not_performing");
			return GENERALERROR;
		}

		if (!creature->isPlayingMusic()) {
			creature->sendSystemMessage("@performance:effect_not_performing_correct");
			return GENERALERROR;
		}

		int actionModifier = Integer::valueOf(arguments.toString());

		if (actionModifier > 3 || actionModifier < 1)
			actionModifier = 3;

		int actionCost = 30 * actionModifier;
		actionCost = creature->calculateCostAdjustment(CreatureAttribute::QUICKNESS, actionCost);
		if (creature->getHAM(CreatureAttribute::ACTION) <= actionCost) {
			creature->sendSystemMessage("@performance:effect_too_tired");
			return GENERALERROR;
		}
		creature->inflictDamage(creature, CreatureAttribute::ACTION, actionCost, true);

		StringBuffer effect;
		effect << "clienteffect/entertainer_fire_jets_level_" << dec << actionModifier << ".cef";
		creature->playEffect(effect.toString(), "");

		creature->sendSystemMessage("@performance:effect_perform_fire_jets");

		return SUCCESS;
	}

};

#endif //FIREJETCOMMAND_H_
