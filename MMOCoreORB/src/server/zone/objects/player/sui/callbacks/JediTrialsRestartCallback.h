#ifndef JEDITRIALSRESTARTCALLBACK_H_
#define JEDITRIALSRESTARTCALLBACK_H_

#include "server/zone/objects/player/sui/SuiCallback.h"
#include "server/zone/managers/player/PlayerManager.h"
#include "server/zone/managers/jedi/JediManager.h"

class JediTrialsRestartSuiCallback: public SuiCallback {

public:
	JediTrialsRestartSuiCallback(ZoneServer* serv) :
		SuiCallback(serv) {
	}

	void run(CreatureObject* creature, SuiBox* sui, bool cancelPressed,
			Vector<UnicodeString>* args) {
		if (!sui->isMessageBox() || cancelPressed)
			return;

		if (!creature->isPlayerCreature())
			return;

		if (!cancelPressed) {
			creature->sendSystemMessage("@jedi_trials:padawan_trials_trial_restarted"); // Your current Jedi Padawan trial task has been reset back to the beginning. Meditate at any Force shrine to restart it.
			creature->setScreenPlayState("trials:padawan:currentTrial", 0);
		}
	}
};


#endif
