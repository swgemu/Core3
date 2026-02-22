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
	ManagedReference<ShipPaintKit*> customizationKit;

public:
	ShipColorWithKitSuiCallback(ZoneServer* serv, ShipPaintKit* kit) : SuiCallback(serv), customizationKit(kit) {
	}

	void run(CreatureObject* creature, SuiBox* sui, uint32 eventIndex, Vector<UnicodeString>* args) {
		bool cancelPressed = (eventIndex == 1);

		if (creature == nullptr || customizationKit == nullptr)
			return;

		if (!cancelPressed && args->size() > 0) {
			ManagedReference<TangibleObject*> ship = sui->getUsingObject().castTo<TangibleObject*>();

			if (ship != nullptr) {
				int colorIndex = Integer::valueOf(args->get(0).toString());
				String varKey = sui->getPromptTitle();

				Locker shipLocker(ship);
				ship->setCustomizationVariable(varKey, colorIndex, true);
				shipLocker.release();

				Locker kitLocker(customizationKit);

				int charges = customizationKit->getCharges() - 1;
				customizationKit->setCharges(charges);

				if (varKey == "/shared_owner/index_color_1") {
					customizationKit->setPrimaryUsed(true);
				} else if (varKey == "/shared_owner/index_color_2") {
					customizationKit->setSecondaryUsed(true);
				}

				customizationKit->sendAttributeListTo(creature);

				if (charges <= 0) {
					customizationKit->destroyObjectFromWorld(true);
				}
				kitLocker.release();
			}
		}
	}
};

#endif /* SHIPCOLORWITHKITSUICALLBACK_H_ */