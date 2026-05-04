/*
			Copyright <SWGEmu>
	See file COPYING for copying conditions.
*/

#ifndef VREPAIR_H_
#define VREPAIR_H_

#include "SpaceQueueCommand.h"
#include "server/zone/objects/ship/ShipObject.h"
#include "server/zone/objects/ship/ShipComponentFlag.h"
#include "server/zone/objects/ship/ComponentSlots.h"
#include "server/zone/packets/scene/PlayClientEffectLocMessage.h"

class VrepairCommand : public SpaceQueueCommand {
	static const int GLOBAL_COOLDOWN_MS = 240000;

public:
	VrepairCommand(const String& name, ZoneProcessServer* server)
		: SpaceQueueCommand(name, server) {}

	int doQueueCommand(CreatureObject* creature, const uint64& target, const UnicodeString& arguments) const {
		if (!checkSpaceStates(creature))
			return INVALIDSTATE;

		auto ship = getPlayerShip(creature);

		if (ship == nullptr)
			return GENERALERROR;

		if (!creature->checkCooldownRecovery("command_pilot"))
			return GENERALERROR;

		Locker slock(ship, creature);

		if (!ship->isComponentFunctional(Components::REACTOR)) {
			{ StringIdChatParameter _smid("space/space_interaction", "systems_not_ready"); creature->sendSystemMessage(_smid); }
			return GENERALERROR;
		}

		// Worst = highest HP damage %; skip uninstalled slots and maxHP < 1.
		auto componentMap = ship->getShipComponentMap();
		uint32 worstSlot = 0;
		bool worstFound = false;
		float highestPct = 0.f;
		float worstMaxHP = 0.f;
		float totalMaxHP = 0.f;
		float pctSum = 0.f;
		int badCount = 0;
		int componentCount = componentMap->size();

		for (int i = 0; i < componentCount; ++i) {
			uint32 slot = componentMap->getKeyAt(i);
			float maxHP = ship->getMaxHitpointsMap()->get(slot);
			float curHP = ship->getCurrentHitpointsMap()->get(slot);

			if (!ship->isComponentInstalled(slot) || maxHP < 1.f) {
				++badCount;
				continue;
			}

			totalMaxHP += maxHP;
			float pct = ((maxHP - curHP) / maxHP) * 100.f;
			pctSum += pct;

			if (pct > highestPct) {
				highestPct = pct;
				worstSlot = slot;
				worstFound = true;
				worstMaxHP = maxHP;
			}
		}

		// delta = worst% minus average of all other components
		int divisor = componentCount - badCount - 1;
		float avgOther = (divisor > 0) ? ((pctSum - highestPct) / (float)divisor) : 0.f;
		float delta = highestPct - avgOther;

		const auto& pos = ship->getPosition();
		ship->broadcastMessage(new PlayClientEffectLoc("clienteffect/space_command/sys_manipulation.cef", "", pos.getX(), pos.getZ(), pos.getY()), true);

		if (!worstFound || delta < 5.f) {
			{ StringIdChatParameter _smid("space/space_interaction", "vampiric_repair_useless_abort"); creature->sendSystemMessage(_smid); }
			ship->broadcastMessage(new PlayClientEffectLoc("clienteffect/space_command/emergency_power_on.cef", "", pos.getX(), pos.getZ(), pos.getY()), true);
			return GENERALERROR;
		}

		// Snapshot before any HP changes — protects a pre-existing DISABLED from the re-enable below.
		bool worstWasDisabled = ship->hasComponentFlag(worstSlot, ShipComponentFlag::DISABLED);

		initializePilotCommandTimer(creature, GLOBAL_COOLDOWN_MS);

		float pool = (delta / 100.f) * worstMaxHP;

		auto deltaVector = ship->getDeltaVector();

		// Repair first; skill check only adjusts pool cost.
		float worstCurHP = ship->getCurrentHitpointsMap()->get(worstSlot);
		ship->setComponentHitpoints(worstSlot, Math::min(worstCurHP + pool, worstMaxHP), nullptr, 2, deltaVector);

		int successLevel = doPilotCommandSkillCheck(creature, RISK_LEVEL2);

		if (successLevel == 1) pool -= pool * 0.15f; // great success: 15% cheaper
		else if (successLevel == 2) pool -= pool * 0.05f; // good success: 5% cheaper
		else if (successLevel == 4) pool += pool * 0.05f; // slight fail: 5% costlier
		else if (successLevel == 6) pool += pool * 0.20f; // big fail: 20% costlier

		// Drain proportionally; per-slot floor at 1 HP.
		if (totalMaxHP > 0.f) {
			for (int i = 0; i < componentCount; ++i) {
				uint32 slot = componentMap->getKeyAt(i);
				float maxHP = ship->getMaxHitpointsMap()->get(slot);

				if (!ship->isComponentInstalled(slot) || maxHP < 1.f)
					continue;

				float curHP = ship->getCurrentHitpointsMap()->get(slot);
				float hitPointDelta = (maxHP / totalMaxHP) * pool;

				if (hitPointDelta > curHP)
					hitPointDelta = Math::max(0.f, curHP - 1.f);

				ship->setComponentHitpoints(slot, curHP - hitPointDelta, nullptr, 2, deltaVector);
			}
		}

		// Worst can drain to 0 here; no 1 HP floor (re-enabled below if needed).
		if (pool > 0.f) {
			float worstHPNow = ship->getCurrentHitpointsMap()->get(worstSlot);
			ship->setComponentHitpoints(worstSlot, Math::max(0.f, worstHPNow - pool), nullptr, 2, deltaVector);
		}

		if (deltaVector != nullptr)
			deltaVector->sendMessages(ship);

		// Do NOT use resetAllComponents — it clears DISABLED flags from active E* buffs.
		ship->resetEfficiency();

		// Re-enable worst only if vrepair drove it to 0; don't undo a pre-existing disable.
		float worstHPFinal = ship->getCurrentHitpointsMap()->get(worstSlot);

		if (worstHPFinal <= 0.f && !worstWasDisabled && ship->hasComponentFlag(worstSlot, ShipComponentFlag::DISABLED)) {
			ship->removeComponentFlag(worstSlot, ShipComponentFlag::DISABLED);
		}

		ship->broadcastMessage(new PlayClientEffectLoc("clienteffect/space_command/emergency_power_on.cef", "", pos.getX(), pos.getZ(), pos.getY()), true);

		{ StringIdChatParameter _smid("space/space_interaction", "vampiric_repair_underway"); creature->sendSystemMessage(_smid); }

		// 1-6 used for pool adjustments above; convert to 0-based for switch.
		--successLevel;

		switch (successLevel) {
			case 5: { StringIdChatParameter _smid("space/space_interaction", "vampiric_big_fail"); creature->sendSystemMessage(_smid); } break;
			case 3: { StringIdChatParameter _smid("space/space_interaction", "vampiric_slight_fail"); creature->sendSystemMessage(_smid); } break;
			case 2: { StringIdChatParameter _smid("space/space_interaction", "vampiric_success"); creature->sendSystemMessage(_smid); } break;
			case 1: { StringIdChatParameter _smid("space/space_interaction", "vampiric_good_success"); creature->sendSystemMessage(_smid); } break;
			case 0: { StringIdChatParameter _smid("space/space_interaction", "vampiric_great_success"); creature->sendSystemMessage(_smid); } break;
			default: break;
		}

		return SUCCESS;
	}

};

#endif // VREPAIR_H_
