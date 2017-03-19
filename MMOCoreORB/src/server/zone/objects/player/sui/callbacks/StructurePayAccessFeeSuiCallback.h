/*
 * StructurePayAccessFeeSuiCallback.h
 *
 *  Created on: June 2, 2012
 *      Author: Kyle
 */

#ifndef STRUCTUREPAYACCESSFEESUICALLBACK_H_
#define STRUCTUREPAYACCESSFEESUICALLBACK_H_

#include "server/zone/objects/player/sui/SuiCallback.h"
#include "server/zone/objects/building/BuildingObject.h"

class StructurePayAccessFeeSuiCallback: public SuiCallback {

public:
	StructurePayAccessFeeSuiCallback(ZoneServer* serv) : SuiCallback(serv) {

	}

	void run(CreatureObject* player, SuiBox* sui, uint32 eventIndex, Vector<UnicodeString>* args) {
		bool cancelPressed = (eventIndex == 1);

		if(!sui->isMessageBox() || cancelPressed)
			return;

		ManagedReference<SceneObject*> usingObject = sui->getUsingObject().get();

		if (usingObject == NULL || !usingObject->isBuildingObject())
			return;

		BuildingObject* buildingObject = cast<BuildingObject*>(usingObject.get());


		buildingObject->payAccessFee(player);

	}
};

#endif /* STRUCTUREPAYACCESSFEESUICALLBACK_H_ */
