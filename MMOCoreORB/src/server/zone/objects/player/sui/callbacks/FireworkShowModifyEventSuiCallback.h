#ifndef FIREWORKSHOWMODIFYEVENTSUICALLBACK_H_
#define FIREWORKSHOWMODIFYEVENTSUICALLBACK_H_

#include "server/zone/objects/tangible/firework/components/FireworkShowMenuComponent.h"
#include "server/zone/objects/player/sui/SuiCallback.h"
#include "server/zone/ZoneServer.h"
#include "server/zone/objects/tangible/firework/components/FireworkShowDataComponent.h"
#include "server/zone/objects/player/sui/callbacks/FireworkShowDelaySelectionSuiCallback.h"
#include "server/zone/objects/player/sui/transferbox/SuiTransferBox.h"
#include "server/zone/objects/player/sui/listbox/SuiListBox.h"
#include "server/zone/objects/player/sui/fireworkdelaybox/SuiFireworkDelayBox.h"
#include "server/zone/managers/object/ObjectManager.h"

class FireworkShowModifyEventSuiCallback : public SuiCallback {
public:
	FireworkShowModifyEventSuiCallback(ZoneServer* server)
		: SuiCallback(server) {
	}

	void run(CreatureObject* player, SuiBox* suiBox, bool cancelPressed, Vector<UnicodeString>* args) {
		if (!suiBox->isListBox() || cancelPressed)
			return;

		if (args->size() < 1)
			return;

		int index = Integer::valueOf(args->get(0).toString());

		if (index == -1)
			return;

		SuiListBox* listBox = cast<SuiListBox*>(suiBox);
		uint64 fireworkObjectID = listBox->getMenuObjectID(index);

		ManagedReference<FireworkObject*> firework = (server->getObject(fireworkObjectID)).castTo<FireworkObject*>();

		if (firework == NULL || !firework->isFireworkObject())
			return;

		ManagedReference<SceneObject*> fireworkShow = suiBox->getUsingObject();

		if (fireworkShow == NULL || !fireworkShow->isFireworkObject())
			return;

		DataObjectComponent* data = fireworkShow->getDataObjectComponent()->get();

		if(data == NULL || !data->isFireworkShowData())
			return;

		FireworkShowDataComponent* fireworkShowData = cast<FireworkShowDataComponent*>(data);

		int fireworkIndex = fireworkShowData->getIndexOfFirework(firework);
		int fireworkDelay = fireworkShowData->getFireworkDelay(fireworkIndex);

		if (fireworkIndex == -1)
			return;

		ManagedReference<SuiFireworkDelayBox*> suiDelayBox = new SuiFireworkDelayBox(player, SuiWindowType::FIREWORK_SHOW_DELAYSELECTION, fireworkIndex);
		suiDelayBox->setPromptTitle("@firework:modify_delay_title"); // Delay Selection
		suiDelayBox->setPromptText("@firework:modify_delay_prompt"); // Select the amount of time (in tenths of a second) you would like to have as a delay between this event and the prior event.
		suiDelayBox->addFrom("Available", String::valueOf(100 - (fireworkDelay / 100)), String::valueOf(100 - (fireworkDelay / 100)), "1"); // SUI expects delay in tenths of a second
		suiDelayBox->addTo("Delay", String::valueOf(fireworkDelay / 100), String::valueOf(fireworkDelay / 100), "1");
		suiDelayBox->setUsingObject(fireworkShow);

		suiDelayBox->setCallback(new FireworkShowDelaySelectionSuiCallback(server));
		player->getPlayerObject()->addSuiBox(suiDelayBox);
		player->sendMessage(suiDelayBox->generateMessage());

	}
};

#endif /* FIREWORKSHOWMODIFYEVENTSUICALLBACK_H_ */
