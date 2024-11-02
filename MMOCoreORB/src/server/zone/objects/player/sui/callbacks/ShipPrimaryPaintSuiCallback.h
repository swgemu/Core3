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
#include "server/zone/objects/player/sui/callbacks/ColorWithKitSuiCallback.h"


class ShipPrimaryPaintSuiCallback : public SuiCallback {
public:
	ShipPrimaryPaintSuiCallback(ZoneServer* serv) : SuiCallback(serv) {
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

		//Calculate the appropriate texture index to use based on the kit's string ID - e.g. texture_kit_s03 will use an index of 2
		ManagedReference<SceneObject*> obj = sui->getUsingObject().get();
		if (obj == nullptr)
			return;

		ManagedReference<TangibleObject*> customizationKit = obj->asTangibleObject();
		if (customizationKit == nullptr)
			return;

		//Get the target ship from the SuiListBox, which has its object ID stored
		SuiListBox* listbox = cast<SuiListBox*>(sui);

		int idx = Integer::valueOf(args->get(0).toString());
		if (idx >= listbox->getMenuSize() || idx < 0)
			return;

		uint64 oid = listbox->getMenuObjectID(idx);

		Reference<SceneObject*> object = server->getObject(oid);
		if (object == nullptr)
			return;

		ManagedReference<TangibleObject*> ship = object->asTangibleObject();
		if ( ship != nullptr) {
			String varKey = "/shared_owner/index_color_1";
			ManagedReference<SuiColorBox*> cbox = new SuiColorBox(creature, SuiWindowType::CUSTOMIZE_KIT);
			cbox->setCallback(new ColorWithKitSuiCallback(server, customizationKit));
			cbox->setColorPalette(varKey);
			cbox->setUsingObject(ship);

			ManagedReference<PlayerObject*> ghost = creature->getPlayerObject();
			ghost->addSuiBox(cbox);
			creature->sendMessage(cbox->generateMessage());
		}
	}
};

#endif /* SHIPTEXTURESUICALLBACK_H_ */
