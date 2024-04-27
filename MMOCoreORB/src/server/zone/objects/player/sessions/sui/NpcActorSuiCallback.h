#ifndef NPCACTORSUICALLBACK_H_
#define NPCACTORSUICALLBACK_H_

/*
 * NpcActorSuiCallback.h
 *
 * Created: 2024-04-22
 * By: Hakry
 *
*/

#include "server/zone/objects/player/sui/SuiCallback.h"
#include "server/zone/objects/player/sui/listbox/SuiListBox.h"
#include "server/zone/objects/tangible/deed/eventperk/EventPerkDeed.h"
#include "server/zone/objects/player/sessions/NpcActorCreationSession.h"

class NpcActorSuiCallback : public SuiCallback {
public:
	NpcActorSuiCallback(ZoneServer* server) : SuiCallback(server) {
	}

	void run(CreatureObject* player, SuiBox* suiBox, uint32 eventIndex, Vector<UnicodeString>* args) {
		if (player == nullptr || suiBox == nullptr) {
			clearSession(player);
			return;
		}

		bool cancelPressed = (eventIndex == 1);

		if (cancelPressed) {
			clearSession(player);
			return;
		}

		if (!suiBox->isListBox() || args->size() < 1) {
			clearSession(player);
			return;
		}

		auto listBox = cast<SuiListBox*>(suiBox);

		if (listBox == nullptr) {
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

		// Item selected
		int idx = Integer::valueOf(args->get(0).toString());
		int menuID = listBox->getMenuObjectID(idx);

		npcActorSession->setNpcActorSelection(menuID);
	}

	void clearSession(CreatureObject* player) {
		Locker lock(player);

		player->dropActiveSession(SessionFacadeType::NPCACTORCREATION);
	}
};

#endif /* #define NPCACTORSUICALLBACK_H_ */