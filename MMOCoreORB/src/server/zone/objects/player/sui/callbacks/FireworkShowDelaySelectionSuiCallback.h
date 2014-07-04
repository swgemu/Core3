#ifndef FIREWORKSHOWDELAYSELECTIONSUICALLBACK_H_
#define FIREWORKSHOWDELAYSELECTIONSUICALLBACK_H_

#include "server/zone/objects/player/sui/SuiCallback.h"
#include "server/zone/objects/tangible/firework/components/FireworkShowMenuComponent.h"
#include "server/zone/objects/tangible/firework/components/FireworkShowDataComponent.h"
#include "server/zone/objects/player/sui/transferbox/SuiTransferBox.h"
#include "server/zone/objects/player/sui/listbox/SuiListBox.h"
#include "server/zone/objects/player/sui/fireworkdelaybox/SuiFireworkDelayBox.h"
#include "server/zone/managers/object/ObjectManager.h"


class FireworkShowDelaySelectionSuiCallback : public SuiCallback {
public:
	FireworkShowDelaySelectionSuiCallback(ZoneServer* server) : SuiCallback(server) {
	}

	void run(CreatureObject* player, SuiBox* suiBox, bool cancelPressed, Vector<UnicodeString>* args) {
		if (!suiBox->isFireworkDelayBox() || cancelPressed || args->size() < 2)
			return;

		int delay = Integer::valueOf(args->get(1).toString()) * 100; // SUI returns delay in tenths of a second

		if (delay < 0)
			return;

		if (delay < 1000)
			delay = 1000; // Minimum of 1.0 second delay

		ManagedReference<SceneObject*> fireworkShow = suiBox->getUsingObject();

		if (fireworkShow == NULL || !fireworkShow->isFireworkObject())
			return;

		DataObjectComponent* data = fireworkShow->getDataObjectComponent()->get();

		if(data == NULL || !data->isFireworkShowData())
			return;

		FireworkShowDataComponent* fireworkShowData = cast<FireworkShowDataComponent*>(data);

		SuiFireworkDelayBox* suiDelay = cast<SuiFireworkDelayBox*>( suiBox);

		int fireworkIndex = suiDelay->getFireworkIndex();

		fireworkShowData->setFireworkDelay(fireworkIndex, delay);

		FireworkShowMenuComponent* showMenu = cast<FireworkShowMenuComponent*>(fireworkShow->getObjectMenuComponent());
		showMenu->modifyEvent(player, fireworkShow.castTo<FireworkObject*>());

	}
};

#endif /* FIREWORKSHOWDELAYSELECTIONSUICALLBACK_H_ */
