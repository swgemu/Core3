/*
 * ShipTextureSuiCallback.h
 *
 *  Created on: 7/16/2023
 *      Author: Halyn
 */

#ifndef SHIPTEXTURESUICALLBACK_H_
#define SHIPTEXTURESUICALLBACK_H_

#include "server/zone/objects/player/sui/SuiCallback.h"


class ShipTextureSuiCallback : public SuiCallback {
public:
	ShipTextureSuiCallback(ZoneServer* serv) : SuiCallback(serv) {
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

		String entry = obj->getObjectNameStringIdName();
		int textureIndex = Integer::valueOf(entry.charAt(entry.length() - 1)) - 1;

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
			//set the ship's new texture
			Locker slocker(ship, creature);
			ship->setCustomizationVariable("/shared_owner/index_texture_1", textureIndex, true);
			creature->sendSystemMessage("@texture_kit:changed_paint_job");
			slocker.release();

			//eliminate the texture kit now that it's been used
			Locker tlocker(obj, creature);
			obj->destroyObjectFromWorld(true);
			obj->destroyObjectFromDatabase(true);
		}
	}
};

#endif /* SHIPTEXTURESUICALLBACK_H_ */
