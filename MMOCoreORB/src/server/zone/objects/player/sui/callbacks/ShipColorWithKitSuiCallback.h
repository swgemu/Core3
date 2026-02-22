/*
 * ShipColorWithKitSuiCallback.h
 *
 * Created on: 2/18/2026
 * Author: Fastburn
*/
#ifndef SHIPCOLORWITHKITSUICALLBACK_H_
#define SHIPCOLORWITHKITSUICALLBACK_H_

#include "server/zone/objects/tangible/TangibleObject.h"
#include "server/zone/objects/player/sui/SuiCallback.h"
#include "server/zone/objects/tangible/tool/ShipPaintKit.h"

class ShipColorWithKitSuiCallback : public SuiCallback {
	ManagedWeakReference<ShipPaintKit*> customizationKit;

public:
	ShipColorWithKitSuiCallback(ZoneServer* serv, ShipPaintKit* kit) : SuiCallback(serv), customizationKit(kit) {
	}

	void run(CreatureObject* creature, SuiBox* sui, uint32 eventIndex, Vector<UnicodeString>* args) {
		bool cancelPressed = (eventIndex == 1);

		ManagedReference<ShipPaintKit*> kit = customizationKit.get();

		if (creature == nullptr || kit == nullptr || cancelPressed || args->size() == 0)
			return;

		ManagedReference<TangibleObject*> ship = sui->getUsingObject().castTo<TangibleObject*>();

		if (ship == nullptr || !ship->isShipObject())
			return;

		String varKey = sui->getPromptTitle();

		if (varKey == "/shared_owner/index_color_1") {
			if (kit->getPrimaryUsed())
				return;

			kit->setPrimaryUsed(true);
		} else if (varKey == "/shared_owner/index_color_2") {
			if (kit->getSecondaryUsed())
				return;

			kit->setSecondaryUsed(true);
		}

		int colorIndex = Integer::valueOf(args->get(0).toString());

		Locker kitLocker(kit);
		Locker shipLocker(ship, kit);

		ship->setCustomizationVariable(varKey, colorIndex, true);

		if (kit->getPrimaryUsed() && kit->getSecondaryUsed()) {
			kit->destroyObjectFromWorld(true);
			kit->destroyObjectFromDatabase(true);
		}
	}
};

#endif /* SHIPCOLORWITHKITSUICALLBACK_H_ */