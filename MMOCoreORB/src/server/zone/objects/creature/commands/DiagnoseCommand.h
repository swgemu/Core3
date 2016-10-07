/*
				Copyright <SWGEmu>
		See file COPYING for copying conditions.*/

#ifndef DIAGNOSECOMMAND_H_
#define DIAGNOSECOMMAND_H_

#include "server/zone/objects/scene/SceneObject.h"
#include "server/zone/objects/player/sui/listbox/SuiListBox.h"

class DiagnoseCommand : public QueueCommand {
	float range;
public:

	DiagnoseCommand(const String& name, ZoneProcessServer* server)
		: QueueCommand(name, server) {

		range = 6;
	}

	int doQueueCommand(CreatureObject* creature, const uint64& target, const UnicodeString& arguments) const {

		if (!checkStateMask(creature))
			return INVALIDSTATE;

		if (!checkInvalidLocomotions(creature))
			return INVALIDLOCOMOTION;

		PlayerObject* ghost = creature->getPlayerObject();

		if (ghost == NULL)
			return GENERALERROR;

		ManagedReference<SceneObject*> object = server->getZoneServer()->getObject(target);

		if (object == NULL || (!object->isPlayerCreature() && !object->isPet())) {
			creature->sendSystemMessage("@healing_response:healing_response_b6"); //You cannot diagnose that.
			return GENERALERROR;
		}

		CreatureObject* creatureTarget = cast<CreatureObject*>(object.get());

		Locker clocker(creatureTarget, creature);

		if(!checkDistance(creature, creatureTarget, range)) {
			StringIdChatParameter params("@cmd_err:target_range_prose"); //Your target is too far away to %TO.
			params.setTO("Diagnose");
			creature->sendSystemMessage(params);
			return TOOFAR;
		}

		if (!creatureTarget->isHealableBy(creature)) {
			creature->sendSystemMessage("@healing:pvp_no_help"); //It would be unwise to help such a patient.
			return GENERALERROR;
		}

		// Close already opened Sui Box...
		ghost->closeSuiWindowType(SuiWindowType::MEDIC_DIAGNOSE);

		ManagedReference<SuiListBox*> sui = new SuiListBox(creature, SuiWindowType::MEDIC_DIAGNOSE);

		String patient = creatureTarget->getDisplayedName();

		StringBuffer title;
		title << "Patient " << patient;
		sui->setPromptTitle(title.toString());

		StringBuffer text;
		text << "Below is a listing of the wound and Battle Fatigue levels of " << patient << ". Wounds are healed through /tendwound or use of wound Medpacks. High levels of Battle Fatigue can inhibit the healing process, and Battle Fatigue can only be healed by the patient choosing to watch performing entertainers.";
		sui->setPromptText(text.toString());
		sui->setCancelButton(false, "");

		StringBuffer health;
		health << "Health -- " << creatureTarget->getWounds(CreatureAttribute::HEALTH);
		sui->addMenuItem(health.toString());

		StringBuffer strength;
		strength << "Strength -- " << creatureTarget->getWounds(CreatureAttribute::STRENGTH);
		sui->addMenuItem(strength.toString());

		StringBuffer constitution;
		constitution << "Constitution -- " << creatureTarget->getWounds(CreatureAttribute::CONSTITUTION);
		sui->addMenuItem(constitution.toString());

		StringBuffer action;
		action << "Action -- " << creatureTarget->getWounds(CreatureAttribute::ACTION);
		sui->addMenuItem(action.toString());

		StringBuffer quickness;
		quickness << "Quickness -- " << creatureTarget->getWounds(CreatureAttribute::QUICKNESS);
		sui->addMenuItem(quickness.toString());

		StringBuffer stamina;
		stamina << "Stamina -- " << creatureTarget->getWounds(CreatureAttribute::STAMINA);
		sui->addMenuItem(stamina.toString());

		StringBuffer mind;
		mind << "Mind -- " << creatureTarget->getWounds(CreatureAttribute::MIND);
		sui->addMenuItem(mind.toString());

		StringBuffer focus;
		focus << "Focus -- " << creatureTarget->getWounds(CreatureAttribute::FOCUS);
		sui->addMenuItem(focus.toString());

		StringBuffer willpower;
		willpower << "Willpower -- " << creatureTarget->getWounds(CreatureAttribute::WILLPOWER);
		sui->addMenuItem(willpower.toString());

		StringBuffer battlefatigue;
		battlefatigue << "Battle Fatigue -- " << creatureTarget->getShockWounds();
		sui->addMenuItem(battlefatigue.toString());

		ghost->addSuiBox(sui);
		creature->sendMessage(sui->generateMessage());

		return SUCCESS;
	}

};

#endif //DIAGNOSECOMMAND_H_
