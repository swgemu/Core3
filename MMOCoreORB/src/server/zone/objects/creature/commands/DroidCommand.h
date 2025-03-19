/*
				Copyright <SWGEmu>
		See file COPYING for copying conditions.*/

#ifndef DROID_H_
#define DROID_H_

//#include "CombatQueueCommand.h"
#include "server/zone/managers/ship/ShipManager.h"
#include "server/zone/managers/ship/DroidCommandData.h"
#include "server/zone/managers/ship/tasks/SpaceCommTimerTask.h"
#include "server/zone/managers/stringid/StringIdManager.h"
#include "server/zone/objects/creature/events/DroidCommandNotifyAvailableEvent.h"
#include "server/zone/packets/ship/ShipObjectMessage1.h"
#include "server/zone/packets/ship/ShipObjectMessage3.h"

class DroidCommand : public QueueCommand {

public:

	DroidCommand(const String& name, ZoneProcessServer* server)
		: QueueCommand(name, server) {
	}

	int doQueueCommand(CreatureObject* creature, const uint64& target, const UnicodeString& arguments) const {

		if (!checkStateMask(creature))
			return INVALIDSTATE;

		if (!checkInvalidLocomotions(creature))
			return INVALIDLOCOMOTION;

		if (!creature->isPlayerCreature())
			return GENERALERROR;

		String args = arguments.toString();
		uint32 argsHash = args.hashCode();

		if (args.length() < 1)
			return GENERALERROR;

		ShipManager* shipMan = ShipManager::instance();
		if (shipMan == nullptr)
			return GENERALERROR;

		ManagedReference<ShipObject*> ship = cast<ShipObject*>(creature->getRootParent());
		if (ship == nullptr)
			return GENERALERROR;

		auto zoneServer = creature->getZoneServer();

		if (zoneServer == nullptr)
			return GENERALERROR;

		//no droid interface
		if (!ship->isComponentInstalled(Components::DROID_INTERFACE)) {
			creature->sendSystemMessage("@space/space_interaction:droid_command_fail_no_interface"); //Droid commands are non functional because you do not have a droid interface installed.
			return GENERALERROR;
		}

		//droid interface is disabled
		if (!ship->isComponentFunctional(Components::DROID_INTERFACE)) {
			creature->sendSystemMessage("@space/space_interaction:droid_command_fail_interface_disabled"); //You cannot do flight-computer/droid commands as your droid interface is disabled.
			return GENERALERROR;
		}

		//droid commands on cooldown
		if (!ship->isReadyForDroidCommand()) {
			StringIdChatParameter droidDelayMsg;
			droidDelayMsg.setStringId("space/space_interaction", "droid_command_delay"); //Your flight-computer/astromech cannot perform another command for %DI seconds.
			droidDelayMsg.setDI(ship->timeUntilNextDroidCommand());
			creature->sendSystemMessage(droidDelayMsg);
			return GENERALERROR;
		}

		auto droidControlDevice = cast<IntangibleObject*>(zoneServer->getObject(ship->getShipDroidID()).get());

		//no droid
		if (droidControlDevice == nullptr) {
			creature->sendSystemMessage("@space/space_interaction:droid_command_fail_no_droid"); //You must have a flight-computer/droid to activate droid commands.
			return GENERALERROR;
		}

		if (!ship->hasDroidCommand(argsHash)) {
			creature->sendSystemMessage("@space/space_interaction:droid_command_fail_no_command"); //Your flight-computer/droid is not programmed to do that action.
			return GENERALERROR;
		}

		DroidCommandData* commandData = shipMan->getDroidCommandData(argsHash);
		if (commandData == nullptr)
			return GENERALERROR;

		float delayModifier = commandData->getDelayModifier();
		int componentType = commandData->getComponentType();
		float energyEfficiency = commandData->getEnergyEfficiency();
		float generalEfficiency = commandData->getGeneralEfficiency();
		float damage = commandData->getDamage();
		float frontReinforceRatio = commandData->getFrontReinforceRatio();
		float capacitorReinforcePercentage = commandData->getCapacitorReinforcePercentage();
		float frontShieldRatio = commandData->getFrontShieldRatio();
		StringIdChatParameter stringID = commandData->getStringID();


		int endComponent = componentType;
		if (componentType == 12)
			endComponent = 20;

		//component too damaged
		if (ship->getCurrentHitpointsMap()->get(componentType) < damage) {
			StringIdChatParameter damagedComponentMsg;
			damagedComponentMsg.setStringId("space/space_interaction", "droid_component_too_damaged"); //You cannot modify that %TO because it is too damaged for this command.
			damagedComponentMsg.setTO(ship->getComponentNameMap()->get(componentType));
			creature->sendSystemMessage(damagedComponentMsg);
			return GENERALERROR;
		}

		Locker clocker(ship, creature);

		//apply overloads/tuning
		for (int i = componentType; i <= endComponent; ++i) {
			if (energyEfficiency != 0)
				ship->setEnergyEfficiency(i, energyEfficiency);

			if (generalEfficiency != 0)
				ship->setEfficiency(i, generalEfficiency);

			if (damage > 0) {
				float armor = ship->getCurrentArmorMap()->get(i);
				float hitpoints = ship->getCurrentHitpointsMap()->get(i);
				float damageToInflict = damage;

				if (damageToInflict > armor) {
					damageToInflict = damageToInflict - armor;
					armor = 0.f;
					hitpoints -= damageToInflict;
				} else {
					armor -= damageToInflict;
				}

				ship->setComponentArmor(i, armor);
				ship->setComponentHitpoints(i, hitpoints);
			}
		}

		//capacitor to shield shunt
		if (capacitorReinforcePercentage > 0) {
			float energyPool = ship->getCapacitorEnergy();
			ship->setFrontShield(Math::min(ship->getFrontShield() + energyPool/2.0f, ship->getMaxFrontShield()));
			ship->setRearShield(Math::min(ship->getRearShield() + energyPool/2.0f, ship->getMaxRearShield()));
			ship->setCapacitorEnergy(energyPool * (1.0f - capacitorReinforcePercentage), false, nullptr, nullptr);
		}

		//shield reinforcement
		if (frontReinforceRatio > 0) {
			if (frontReinforceRatio > 1.0f) { //power from rear shield to front shield
				frontReinforceRatio = frontReinforceRatio - 1.0f;
				float rearShield = ship->getRearShield();
				ship->setRearShield(rearShield * (1.0f - frontReinforceRatio));
				ship->setFrontShield(Math::min(ship->getFrontShield() + rearShield * frontReinforceRatio, ship->getMaxFrontShield()));
			} else { //power from front shield to rear shield
				frontReinforceRatio = 1.0f - frontReinforceRatio;
				float frontShield = ship->getFrontShield();
				ship->setFrontShield(frontShield * (1.0f - frontReinforceRatio));
				ship->setRearShield(Math::min(ship->getRearShield() + frontShield * frontReinforceRatio, ship->getMaxRearShield()));
			}
		}

		//shield adjustment
		if (frontShieldRatio > 0) {
			float totalShieldEnergy = ship->getMaxFrontShield() + ship->getMaxRearShield();
			float frontShieldEnergy = totalShieldEnergy / 2.0f * frontShieldRatio;
			ship->setFrontShieldMax(frontShieldEnergy);
			ship->setRearShieldMax(totalShieldEnergy - frontShieldEnergy);
		}

		//broadcast changes to the pilot for updated displays
		ShipObjectMessage1* ship1 = new ShipObjectMessage1(ship);
		creature->sendMessage(ship1);

		ShipObjectMessage3* ship3 = new ShipObjectMessage3(ship);
		creature->sendMessage(ship3);

		//mute/unmute droid is a special case
		String muteDroid = "droidcommand_mutedroid";
		if (argsHash == muteDroid.hashCode()) {
			if (ship->isDroidMuted())
				ship->setDroidFeedback(true);
			else {
				ship->setDroidFeedback(false);
				creature->sendSystemMessage(stringID);
			}
		}

		//apply delay
		ship->setDroidCommandDelay(delayModifier * ship->getDroidCommandSpeed());

		Reference<DroidCommandNotifyAvailableEvent*> task = new DroidCommandNotifyAvailableEvent(creature);
		creature->addPendingTask("droid_command_notify", task, (delayModifier * ship->getDroidCommandSpeed() * 1000));

		//do droid chatter if droid's not muted
		if (!ship->isDroidMuted()) {
			ship->droidChatter(creature, stringID);
		}
		return SUCCESS;
	}
};

#endif //DROID_H_
