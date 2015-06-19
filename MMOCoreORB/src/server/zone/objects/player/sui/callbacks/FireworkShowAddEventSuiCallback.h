#ifndef FIREWORKSHOWADDEVENTSUICALLBACK_H_
#define FIREWORKSHOWADDEVENTSUICALLBACK_H_

#include "server/zone/objects/tangible/firework/components/FireworkShowMenuComponent.h"
#include "server/zone/objects/player/sui/SuiCallback.h"
#include "server/zone/objects/tangible/firework/components/FireworkShowDataComponent.h"
#include "server/zone/objects/player/sui/listbox/SuiListBox.h"
#include "server/zone/managers/object/ObjectManager.h"

class FireworkShowAddEventSuiCallback : public SuiCallback {
public:
	FireworkShowAddEventSuiCallback(ZoneServer* server)
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

		Locker clocker(firework, player);

		ManagedReference<SceneObject*> fireworkShow = suiBox->getUsingObject();

		if (fireworkShow == NULL || !fireworkShow->isFireworkObject())
			return;

		DataObjectComponent* data = fireworkShow->getDataObjectComponent()->get();

		if(data == NULL || !data->isFireworkShowData())
			return;

		FireworkShowDataComponent* fireworkShowData = cast<FireworkShowDataComponent*>(data);

		int curFireworks = fireworkShowData->getTotalFireworkCount();

		if(firework->getUseCount() > 1) {
			ObjectManager* objectManager = ObjectManager::instance();
			ManagedReference<TangibleObject*> clone = cast<TangibleObject*>( objectManager->cloneObject(firework));
			if(clone == NULL)
				return;

			Locker locker(clone);

			if (clone->hasAntiDecayKit()) {
				clone->removeAntiDecayKit();
			}

			clone->setParent(NULL);
			clone->setUseCount(1, false);
			firework->decreaseUseCount();
			firework->broadcastObject(clone, true);

			ManagedReference<FireworkObject*> fireworkClone = clone.castTo<FireworkObject*>();

			fireworkShowData->addFirework(curFireworks, fireworkClone, 1000);
		} else {
			fireworkShowData->addFirework(curFireworks, firework, 1000);
			firework->destroyObjectFromWorld(true);
		}

		ManagedReference<TangibleObject*> fireworkShowObject = fireworkShow.castTo<TangibleObject*>();

		if (fireworkShowObject != NULL ) {
			Locker locker(fireworkShowObject);
			fireworkShowObject->setUseCount(fireworkShowObject->getUseCount() + 1, true);
		}

		FireworkShowMenuComponent* showMenu = cast<FireworkShowMenuComponent*>(fireworkShow->getObjectMenuComponent());
		showMenu->addEvent(player, fireworkShow.castTo<FireworkObject*>());
	}
};

#endif /* FIREWORKSHOWADDEVENTSUICALLBACK_H_ */
