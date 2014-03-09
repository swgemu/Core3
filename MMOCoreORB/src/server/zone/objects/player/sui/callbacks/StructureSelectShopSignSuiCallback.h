/*
 * StructureSelectShopSignSuiCallback.h
 *
 *  Created on: March 9, 2014
 *      Author: Klivian
 */

#ifndef STRUCTURESELECTSHOPSIGNSUICALLBACK_H_
#define STRUCTURESELECTSHOPSIGNSUICALLBACK_H_

#include "server/zone/objects/player/sui/SuiCallback.h"
#include "server/zone/objects/creature/CreatureObject.h"
#include "server/zone/objects/structure/StructureObject.h"
#include "server/zone/managers/structure/StructureManager.h"


class StructureSelectShopSignSuiCallback : public SuiCallback {
public:
	StructureSelectShopSignSuiCallback(ZoneServer* serv) : SuiCallback(serv) {
	}

	void run(CreatureObject* creature, SuiBox* suiBox, bool cancelPressed, Vector<UnicodeString>* args) {

		if (!suiBox->isListBox() || cancelPressed)
			return;

		if (args->size() < 1)
			return;

		ManagedReference<SceneObject*> object = suiBox->getUsingObject();

		if (object == NULL || !object->isBuildingObject())
			return;

		SuiListBox* suiListBox = cast<SuiListBox*>( suiBox);

		int index = Integer::valueOf(args->get(0).toString());
		String shopSignName = suiListBox->getMenuItemName(index);

		// Set the shop sign
		StructureObject* structure = cast<StructureObject*>(object.get());
		ManagedReference<Zone*> zone = structure->getZone();
		if (zone == NULL)
			return;

		//Creature is already locked (done in handleSuiEventNotification in SuiManager).
		Locker _lock(structure, creature);

		StructureManager::instance()->setShopSign(structure, creature, shopSignName);
	}
};

#endif /* STRUCTURESELECTSHOPSIGNSUICALLBACK_H_ */
