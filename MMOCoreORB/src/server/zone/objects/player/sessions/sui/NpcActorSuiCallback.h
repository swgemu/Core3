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
			return;
		}

		bool cancelPressed = (eventIndex == 1);

		if (cancelPressed) {
			return;
		}

		if (!suiBox->isListBox() || args->size() < 1) {
			return;
		}

		auto listBox = cast<SuiListBox*>(suiBox);

		if (listBox == nullptr) {
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

		// Item selected
		int idx = Integer::valueOf(args->get(0).toString());
		int menuID = listBox->getMenuObjectID(idx);

		npcActorSession->setNpcActorSelection(menuID);
	}
};

#endif /* #define NPCACTORSUICALLBACK_H_ */