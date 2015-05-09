/*
				Copyright <SWGEmu>
		See file COPYING for copying conditions.*/

#ifndef FORCEABSORB1COMMAND_H_
#define FORCEABSORB1COMMAND_H_

#include "JediQueueCommand.h"

class ForceAbsorb1Command : public JediQueueCommand {
public:

	ForceAbsorb1Command(const String& name, ZoneProcessServer* server)
		: JediQueueCommand(name, server) {
		// BuffCRC's, first one is used.
		buffCRCs.add(BuffCRC::JEDI_FORCE_ABSORB_1);
		buffCRCs.add(BuffCRC::JEDI_FORCE_ABSORB_2);

		// Skill mods.
		skillMods.put("force_absorb", 1);

		// Event Types.
		eventTypes.add(ObserverEventType::FORCEBUFFHIT);

	}

	int doQueueCommand(CreatureObject* creature, const uint64& target, const UnicodeString& arguments) const {

		// Return.
		return doJediSelfBuffCommand(creature);
	}

	void handleBuff(SceneObject* creature, ManagedObject* object, int64 param) {
		ManagedReference<CreatureObject*> creo = cast<CreatureObject*>(creature);
		if (creo == NULL)
			return;

		// Client Effect upon hit (needed)
		creo->playEffect("clienteffect/pl_force_absorb_hit.cef", "");
	}

};

#endif //FORCEABSORB1COMMAND_H_
