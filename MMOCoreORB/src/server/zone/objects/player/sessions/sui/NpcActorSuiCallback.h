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

		auto eventPerkDeed = listBox->getUsingObject().castTo<EventPerkDeed*>();

		if (eventPerkDeed == nullptr) {
			return;
		}

		// Item selected
		int idx = Integer::valueOf(args->get(0).toString());
		uint64 menuID = listBox->getMenuObjectID(idx);

 		player->info(true) << "NpcActorSuiCallback -- for player: " << player->getDisplayedName() << " ID: " << player->getObjectID() << " EventPerkDeed ID: " << eventPerkDeed->getObjectID();





		/*
		generated = true;

		EventPerkDataComponent* data = cast<EventPerkDataComponent*>(object->getDataObjectComponent()->get());

		if (data == nullptr) {
			player->sendSystemMessage("Error: no dataObjectComponent.");
			object->destroyObjectFromDatabase(true);
			return 1;
		}

		data->setDeed(thisEventDeed);


		// USE THIS TO SET THE MENU FOR ACCES IN  LUA

		// object/tangible/event_perk/race_droid.iff
		// Values stored using setLuaStringData because the perk is handled from lua
		if (object->getServerObjectCRC() == 0x785C60BF) {
			object->setLuaStringData("ownerID", String::valueOf(player->getObjectID()));
		}


		// Task to destroy the event perk will need to be assigned after actor selection

		if (removeEventPerkDeedTask != nullptr && generatedTimeToLive > 0) {
			Time currentTime;
			uint64 timeDelta = currentTime.getMiliTime() - purchaseTime.getMiliTime();

			if (timeDelta >= generatedTimeToLive)
				removeEventPerkDeedTask->execute();
			else
				removeEventPerkDeedTask->reschedule(generatedTimeToLive - timeDelta);
		}


		// Deed will need to be destroyed after selection as well


		destroyObjectFromWorld(true);


		*/


	}
};

#endif /* #define NPCACTORSUICALLBACK_H_ */