#ifndef FIREWORKSHOWREMOVEEVENTSUICALLBACK_H_
#define FIREWORKSHOWREMOVEEVENTSUICALLBACK_H_

#include "server/zone/objects/tangible/firework/components/FireworkShowMenuComponent.h"
#include "server/zone/objects/player/sui/SuiCallback.h"
#include "server/zone/objects/tangible/firework/components/FireworkShowDataComponent.h"
#include "server/zone/objects/player/sui/listbox/SuiListBox.h"
#include "server/zone/managers/object/ObjectManager.h"

class FireworkShowRemoveEventSuiCallback : public SuiCallback {
public:
	FireworkShowRemoveEventSuiCallback(ZoneServer* server)
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

		if (fireworkIndex == -1)
			return;

		fireworkShowData->removeFirework(fireworkIndex);

		ManagedReference<SceneObject*> inventory = player->getSlottedObject("inventory");

		inventory->transferObject(firework, -1, false);
		firework->sendTo(player, true);

		ManagedReference<TangibleObject*> fireworkShowObject = fireworkShow.castTo<TangibleObject*>();

		if (fireworkShowObject != NULL )
			fireworkShowObject->setUseCount(fireworkShowObject->getUseCount() - 1, true);

		FireworkShowMenuComponent* showMenu = cast<FireworkShowMenuComponent*>(fireworkShow->getObjectMenuComponent());
		showMenu->removeEvent(player, fireworkShow.castTo<FireworkObject*>());

	}
};

#endif /* FIREWORKSHOWREMOVEEVENTSUICALLBACK_H_ */
