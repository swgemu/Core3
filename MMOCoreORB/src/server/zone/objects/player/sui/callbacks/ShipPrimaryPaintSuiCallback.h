/*
 * ShipPrimaryPaintSuiCallback.h
 *
 *  Created on: 7/16/2023
 *      Author: Halyn
 */

#ifndef SHIPPRIMARYPAINTSUICALLBACK_H_
#define SHIPPRIMARYPAINTSUICALLBACK_H_

#include "server/zone/objects/player/sui/SuiCallback.h"
#include "server/zone/objects/player/sui/colorbox/SuiColorBox.h"
#include "server/zone/objects/player/sui/listbox/SuiListBox.h"
#include "server/zone/objects/player/sui/callbacks/ShipColorWithKitSuiCallback.h"
#include "server/zone/objects/tangible/tool/ShipPaintKit.h"



class ShipPrimaryPaintSuiCallback : public SuiCallback {
	ManagedReference<ShipPaintKit*> customizationKit;
public:
	ShipPrimaryPaintSuiCallback(ZoneServer* serv, ShipPaintKit* kit) : SuiCallback(serv), customizationKit(kit) {
	}

	void run(CreatureObject* creature, SuiBox* sui, uint32 eventIndex, Vector<UnicodeString>* args) {
		bool cancelPressed = (eventIndex == 1);

		if (creature == nullptr)
			return;

		ZoneServer* server = creature->getZoneServer();

		if (server == nullptr)
			return;

		if (!sui->isListBox() || args->size() <= 0 || cancelPressed)
			return;

		//Get the target ship from the SuiListBox, which has its object ID stored
		SuiListBox* listbox = cast<SuiListBox*>(sui);

		int idx = Integer::valueOf(args->get(0).toString());
		if (idx >= listbox->getMenuSize() || idx < 0)
			return;

		uint64 oid = listbox->getMenuObjectID(idx);

		SceneObject* object = server->getObject(oid);
		if (object == nullptr)
			return;

		TangibleObject* ship = object->asTangibleObject();
		if ( ship != nullptr && customizationKit != nullptr) {

			if (customizationKit->getPrimaryUsed())
				return;

			String varKey = "/shared_owner/index_color_1";
			ManagedReference<SuiColorBox*> cbox = new SuiColorBox(creature, SuiWindowType::CUSTOMIZE_KIT);
			cbox->setCallback(new ShipColorWithKitSuiCallback(server, customizationKit));
			cbox->setColorPalette(varKey);
			cbox->setUsingObject(ship);
			cbox->setPromptTitle(varKey);

			ManagedReference<PlayerObject*> ghost = creature->getPlayerObject();
			if (ghost != nullptr) {
				ghost->closeSuiWindowType(SuiWindowType::CUSTOMIZE_KIT);
				ghost->addSuiBox(cbox);
				creature->sendMessage(cbox->generateMessage());
			}
		}
	}
};

#endif /* SHIPPRIMARYTEXTURESUICALLBACK_H_ */
