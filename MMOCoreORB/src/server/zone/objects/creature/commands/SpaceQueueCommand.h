#ifndef SPACEQUEUECOMMAND_H_
#define SPACEQUEUECOMMAND_H_

#include "server/zone/objects/creature/commands/QueueCommand.h"
#include "server/zone/objects/ship/ShipComponentFlag.h"
#include "server/zone/objects/ship/ComponentSlots.h"
#include "server/zone/packets/scene/PlayClientEffectLocMessage.h"

// Fires the "pilot command timer complete" system message when the global pilot
// command cooldown expires.
class PilotCommandTimerTask : public Task {
	ManagedWeakReference<CreatureObject*> weakCreature;

public:
	PilotCommandTimerTask(CreatureObject* creature) : weakCreature(creature) {}

	void run() {
		ManagedReference<CreatureObject*> creature = weakCreature.get();

		if (creature == nullptr)
			return;

		Locker lock(creature);
		creature->removePendingTask("pilotCommandTimer");
		StringIdChatParameter msg("space/space_interaction", "pilot_command_timer_compelete");
		creature->sendSystemMessage(msg);
	}
};

// Shared scram revert task used by all E* emergency commands on failure.
// Re-enables reactor, engine, and (if it disabled it) booster after scram duration expires.
class SpaceScramRevertTask : public Task {
	ManagedWeakReference<ShipObject*> weakShip;
	bool disabledBooster;

public:
	SpaceScramRevertTask(ShipObject* ship, bool booster)
		: weakShip(ship), disabledBooster(booster) {}

	void run() {
		ManagedReference<ShipObject*> ship = weakShip.get();

		if (ship == nullptr)
			return;

		Locker lock(ship);

		if (ship->hasComponentFlag(Components::REACTOR, ShipComponentFlag::DISABLED))
			ship->removeComponentFlag(Components::REACTOR, ShipComponentFlag::DISABLED);

		if (ship->hasComponentFlag(Components::ENGINE, ShipComponentFlag::DISABLED))
			ship->removeComponentFlag(Components::ENGINE, ShipComponentFlag::DISABLED);

		if (disabledBooster && ship->hasComponentFlag(Components::BOOSTER, ShipComponentFlag::DISABLED))
			ship->removeComponentFlag(Components::BOOSTER, ShipComponentFlag::DISABLED);

		ManagedReference<CreatureObject*> owner = ship->getOwner().get();

		if (owner != nullptr) {
			Locker cLock(owner, ship);
			owner->removePendingTask("spaceScramRevert");
		}
	}
};

class SpaceQueueCommand : public QueueCommand {
public:
	SpaceQueueCommand(const String& skillname, ZoneProcessServer* serv) : QueueCommand(skillname, serv) {}

	ManagedReference<ShipObject*> getPlayerShip(CreatureObject* creature) const {
		if (creature == nullptr) {
			return nullptr;
		}

		auto root = creature->getRootParent();

		if (root == nullptr || !root->isShipObject()) {
			return nullptr;
		}

		return root->asShipObject();
	}

	ManagedReference<ShipObject*> getShipTarget(ShipObject* ship) const {
		if (ship == nullptr) {
			return nullptr;
		}

		uint64 targetID = ship->getShipTargetID();

		if (targetID == 0) {
			return nullptr;
		}

		auto zoneServer = ship->getZoneServer();

		if (zoneServer == nullptr) {
			return nullptr;
		}

		auto target = zoneServer->getObject(targetID);

		if (target == nullptr || !target->isShipObject()) {
			return nullptr;
		}

		return target->asShipObject();
	}

	bool isInRange(ShipObject* ship, ShipObject* target, float distance) const {
		if (ship == nullptr || target == nullptr) {
			return false;
		}

		const auto& sPosition = ship->getPosition();
		const auto& tPosition = target->getPosition();

		float sRadius = ship->getBoundingRadius();
		float tRadius = target->getBoundingRadius();

		float distanceSqr = sPosition.squaredDistanceTo(tPosition) - Math::sqr(sRadius + tRadius);
		return distanceSqr <= Math::sqr(distance);
	}

	// Sets the shared global pilot command cooldown and schedules the completion
	// message. delayMs must be in milliseconds.
	void initializePilotCommandTimer(CreatureObject* creature, int delayMs) const {
		creature->addCooldown("command_pilot", delayMs);

		// Cancel any pending timer from a previous command before scheduling the new one.
		creature->removePendingTask("pilotCommandTimer");

		auto timerTask = new PilotCommandTimerTask(creature);
		creature->addPendingTask("pilotCommandTimer", timerTask, delayMs);
	}

	// Command difficulty risk levels for doPilotCommandSkillCheck.
	// RISK_LEVEL6 = 60 intentionally matches RISK_LEVEL3: the reference skill check
	// function defaults to 60 for any unrecognized command level string, so "level6command"
	// falls through to that default. The constant exists to keep callers self-documenting.
	static const int RISK_LEVEL1 = 20;
	static const int RISK_LEVEL2 = 40;
	static const int RISK_LEVEL3 = 60;
	static const int RISK_LEVEL4 = 80;
	static const int RISK_LEVEL5 = 100;
	static const int RISK_LEVEL6 = 60;

	// Returns penalty mods: +20 if recently damaged, +10 if recently fired.
	int getShipPilotCommandSkillMods(CreatureObject* creature) const {
		int mods = 0;
		if (!creature->checkCooldownRecovery("pilot_damage_penalty"))
			mods += 20;
		if (!creature->checkCooldownRecovery("pilot_fire_penalty"))
			mods += 10;
		return mods;
	}

	// Equivalent of allPurposeShipComponentReset: clears component disabled flags
	// and resets all efficiency modifiers to 1.0 across all slots.
	void resetAllComponents(ShipObject* ship) const {
		auto componentMap = ship->getShipComponentMap();

		for (int i = 0; i < componentMap->size(); ++i) {
			uint32 slot = componentMap->getKeyAt(i);
			if (ship->isComponentInstalled(slot))
				ship->resetComponentFlag(slot, true);
		}

		ship->resetEfficiency();
	}

	// Applies the shared E* scram failure: disables reactor, engine, booster (if installed),
	// sends "scramming_reactor" message, and schedules SpaceScramRevertTask (5-50s duration).
	// Ship lock must already be held by the caller (crosslocked with creature).
	void applyEmergencyScram(CreatureObject* creature, ShipObject* ship) const {
		int scramDuration = ((int)System::random(9) + 1) * 5000; // 5-50 seconds

		bool disabledBooster = false;

		if (ship->isComponentInstalled(Components::REACTOR))
			ship->addComponentFlag(Components::REACTOR, ShipComponentFlag::DISABLED);

		if (ship->isComponentInstalled(Components::ENGINE))
			ship->addComponentFlag(Components::ENGINE, ShipComponentFlag::DISABLED);

		if (ship->isComponentInstalled(Components::BOOSTER)
				&& !ship->hasComponentFlag(Components::BOOSTER, ShipComponentFlag::DISABLED)) {
			ship->addComponentFlag(Components::BOOSTER, ShipComponentFlag::DISABLED);
			disabledBooster = true;
		}

		{ StringIdChatParameter _smid("space/space_interaction", "scramming_reactor"); creature->sendSystemMessage(_smid); }

		auto scramRevertTask = new SpaceScramRevertTask(ship, disabledBooster);
		creature->addPendingTask("spaceScramRevert", scramRevertTask, scramDuration);
	}

	// Returns 1 (great success) through 6 (critical failure).
	// risk: use one of the RISK_LEVEL* constants above.
	int doPilotCommandSkillCheck(CreatureObject* creature, int risk) const {
		static constexpr float AVERAGE = 65.f;
		static constexpr float GREAT   = AVERAGE * 0.50f; // 32.5
		static constexpr float GOOD    = AVERAGE * 0.75f; // 48.75
		static constexpr float MODFAIL = AVERAGE * 1.20f; // 78.0

		int   skill      = creature->getSkillMod("pilot_special_tactics");
		int   shipMods   = getShipPilotCommandSkillMods(creature);
		float roll       = System::frandom(99.f) + 1.f;   // [1.0, 100.0)
		float moddedRoll = roll + (float)risk - (float)skill + (float)shipMods;

		if (moddedRoll < GREAT)   return 1;
		if (moddedRoll < GOOD)    return 2;
		if (moddedRoll < AVERAGE) return 3;
		if (moddedRoll < MODFAIL) return 4;
		if (System::random(99) < 50) return 5;
		return 6;
	}
};

#endif // SPACEQUEUECOMMAND_H_
