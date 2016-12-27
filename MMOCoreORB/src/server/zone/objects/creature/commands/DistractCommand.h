/*
				Copyright <SWGEmu>
		See file COPYING for copying conditions.*/

#ifndef DISTRACTCOMMAND_H_
#define DISTRACTCOMMAND_H_

class DistractCommand : public QueueCommand {
public:

	DistractCommand(const String& name, ZoneProcessServer* server)
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

		if (!creature->isDancing()) {
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
		effect << "clienteffect/entertainer_distract_level_" << dec << actionModifier << ".cef";
		creature->playEffect(effect.toString(), "");

		creature->sendSystemMessage("@performance:effect_perform_distract");

		return SUCCESS;
	}

};

#endif //DISTRACTCOMMAND_H_
