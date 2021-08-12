/*
				Copyright <SWGEmu>
		See file COPYING for copying conditions.*/

#ifndef FORCEABSORB2COMMAND_H_
#define FORCEABSORB2COMMAND_H_

class ForceAbsorb2Command : public JediQueueCommand {
public:

	ForceAbsorb2Command(const String& name, ZoneProcessServer* server) : JediQueueCommand(name, server) {
		buffCRC = BuffCRC::JEDI_FORCE_ABSORB_2;
		overrideableCRCs.add(BuffCRC::JEDI_FORCE_ABSORB_1);
		singleUseEventTypes.add(ObserverEventType::FORCEABSORB);
		skillMods.put("force_absorb", 1);
	}

	int doQueueCommand(CreatureObject* creature, const uint64& target, const UnicodeString& arguments) const override {
		return doJediSelfBuffCommand(creature);
	}

	void handleBuff(SceneObject* creature, ManagedObject* object, int64 param) const override {
		ManagedReference<CreatureObject*> player = creature->asCreatureObject();

		if (player == nullptr) {
			return;
		}

		ManagedReference<PlayerObject*> ghost = player->getPlayerObject();

		if (ghost == nullptr) {
			return;
		}

		// Client Effect upon hit (needed)
		player->playEffect("clienteffect/pl_force_absorb_hit.cef", "");

		ghost->setForcePower(ghost->getForcePower() + param);
	}
};

#endif //FORCEABSORB2COMMAND_H_
