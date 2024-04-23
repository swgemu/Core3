/*
 * NameNpcActorSuiCallback.h
 *
 * Created: 2024-04-23
 * By: Hakry
 *
 */

#ifndef NAMENPCACTORSUICALLBACK_H_
#define NAMENPCACTORSUICALLBACK_H_

#include "server/zone/objects/player/sui/SuiCallback.h"
#include "server/zone/objects/player/sessions/NpcActorCreationSession.h"

class NameNpcActorSuiCallback : public SuiCallback {
public:
	NameNpcActorSuiCallback(ZoneServer* server) : SuiCallback(server) {
	}

	void run(CreatureObject* player, SuiBox* suiBox, uint32 eventIndex, Vector<UnicodeString>* args) {
		bool cancelPressed = (eventIndex == 1);

		if (!suiBox->isInputBox() || args->size() < 1) {
			return;
		}

		ManagedReference<Facade*> facade = player->getActiveSession(SessionFacadeType::NPCACTORCREATION);

		if (facade == nullptr) {
			return;
		}

		ManagedReference<NpcActorCreationSession*> npcActorSession = dynamic_cast<NpcActorCreationSession*>(facade.get());

		if (npcActorSession == nullptr) {
			return;
		}

		if (cancelPressed) {
			npcActorSession->cancelSession();
			return;
		}

		String name = args->get(0).toString();

		npcActorSession->createNpcActor(name);
	}
};

#endif /* NAMENPCACTORSUICALLBACK_H_ */