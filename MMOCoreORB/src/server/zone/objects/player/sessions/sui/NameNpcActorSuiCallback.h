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
			clearSession(player);
			return;
		}

		ManagedReference<Facade*> facade = player->getActiveSession(SessionFacadeType::NPCACTORCREATION);

		if (facade == nullptr) {
			clearSession(player);
			return;
		}

		ManagedReference<NpcActorCreationSession*> npcActorSession = dynamic_cast<NpcActorCreationSession*>(facade.get());

		if (npcActorSession == nullptr) {
			clearSession(player);
			return;
		}

		if (cancelPressed) {
			npcActorSession->cancelSession();
			clearSession(player);
			return;
		}

		String name = args->get(0).toString();

		npcActorSession->createNpcActor(name);
	}

	void clearSession(CreatureObject* player) {
		Locker lock(player);

		player->dropActiveSession(SessionFacadeType::NPCACTORCREATION);
	}
};

#endif /* NAMENPCACTORSUICALLBACK_H_ */