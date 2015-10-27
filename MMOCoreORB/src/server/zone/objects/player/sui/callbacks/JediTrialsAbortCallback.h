#ifndef JEDITRIALSABORTCALLBACK_H_
#define JEDITRIALSABORTCALLBACK_H_

#include "server/zone/objects/player/sui/SuiCallback.h"
#include "server/zone/managers/player/PlayerManager.h"
#include "server/zone/managers/jedi/JediManager.h"

class JediTrialsAbortSuiCallback: public SuiCallback {

public:
	JediTrialsAbortSuiCallback(ZoneServer* serv) :
		SuiCallback(serv) {
	}

	void run(CreatureObject* creature, SuiBox* sui, bool cancelPressed,
			Vector<UnicodeString>* args) {
		if (!sui->isMessageBox() || cancelPressed)
			return;

		if (!creature->isPlayerCreature())
			return;

		if (!cancelPressed) {
			creature->sendSystemMessage("@jedi_trials:padawan_trials_aborted"); // You have successfully abandoned the Jedi Padawan trials. This has erased all previous progess toward completing the trials. If you wish to start again, simply meditate at any Force shrine.
			creature->setScreenPlayState("trials:padawan:currentTrial", 0);
		}
	}
};


#endif
