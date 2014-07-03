#ifndef FIREWORKSHOWREORDERSHOWSUICALLBACK_H_
#define FIREWORKSHOWREORDERSHOWSUICALLBACK_H_

#include "server/zone/objects/tangible/firework/components/FireworkShowMenuComponent.h"
#include "server/zone/objects/player/sui/SuiCallback.h"
#include "server/zone/objects/tangible/firework/components/FireworkShowDataComponent.h"
#include "server/zone/objects/player/sui/listbox/SuiListBox.h"
#include "server/zone/managers/object/ObjectManager.h"

class FireworkShowReorderShowSuiCallback : public SuiCallback {
public:
	FireworkShowReorderShowSuiCallback(ZoneServer* server)
		: SuiCallback(server) {
	}

	void run(CreatureObject* player, SuiBox* suiBox, bool cancelPressed, Vector<UnicodeString>* args) {
		if (!suiBox->isListBox())
			return;

		if (args->size() < 2)
			return;

		int index = Integer::valueOf(args->get(1).toString());

		if (index == -1)
			return;

		bool otherPressed = Bool::valueOf(args->get(0).toString());

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

		if (fireworkIndex == -1)
			return;

		if (cancelPressed) { // Move up button
			if (fireworkIndex >= 1)
				fireworkShowData->swapFireworkPositions(fireworkIndex, fireworkIndex - 1);
		} else if (otherPressed) { // Move down button
			if (fireworkIndex < (fireworkShowData->getTotalFireworkCount() - 1))
				fireworkShowData->swapFireworkPositions(fireworkIndex, fireworkIndex + 1);
		}

		if (cancelPressed || otherPressed) {
			FireworkShowMenuComponent* showMenu = cast<FireworkShowMenuComponent*>(fireworkShow->getObjectMenuComponent());
			showMenu->reorderShow(player, fireworkShow.castTo<FireworkObject*>());
		}
	}
};

#endif /* FIREWORKSHOWREORDERSHOWSUICALLBACK_H_ */
