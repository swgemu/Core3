/*
				Copyright <SWGEmu>
		See file COPYING for copying conditions.*/

#ifndef FORCEABSORB1COMMAND_H_
#define FORCEABSORB1COMMAND_H_

class ForceAbsorb1Command : public JediQueueCommand {
public:

	ForceAbsorb1Command(const String& name, ZoneProcessServer* server) : JediQueueCommand(name, server) {
		buffCRC = BuffCRC::JEDI_FORCE_ABSORB_1;
		blockingCRCs.add(BuffCRC::JEDI_FORCE_ABSORB_2);
		singleUseEventTypes.add(ObserverEventType::FORCEABSORB);

		// Skill mods.
		skillMods.put("force_absorb", 1);
	}

	int doQueueCommand(CreatureObject* creature, const uint64& target, const UnicodeString& arguments) const override {
		return doJediSelfBuffCommand(creature);
	}

	void handleBuff(SceneObject* creature, ManagedObject* object, int64 param) const override {
		ManagedReference<CreatureObject*> player = creature->asCreatureObject();

		if (player == nullptr)
			return;

		ManagedReference<PlayerObject*> ghost = player->getPlayerObject();

		if (ghost == nullptr)
			return;

		// Client Effect upon hit (needed)
		player->playEffect("clienteffect/pl_force_absorb_hit.cef", "");

		int fCost = param * getFrsModifiedExtraForceCost(player, 0.15f);
		ghost->setForcePower(ghost->getForcePower() + fCost);

		CombatManager::instance()->sendMitigationCombatSpam(player, nullptr, fCost, CombatManager::FORCEABSORB);
	}
};

#endif //FORCEABSORB1COMMAND_H_
