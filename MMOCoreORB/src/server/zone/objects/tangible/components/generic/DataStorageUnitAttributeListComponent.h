/*
 * DataStorageUnitAttributeListComponent.h
 *
 *  Created on: 11/8/2014
 *      Author: Klivian
 */

#ifndef DATASTORAGEUNITATTRIBUTELISTCOMPONENT_H_
#define DATASTORAGEUNITATTRIBUTELISTCOMPONENT_H_

#include "server/zone/objects/tangible/components/generic/DataStorageUnitDataComponent.h"

class DataStorageUnitAttributeListComponent: public AttributeListComponent {
public:

	/**
	 * Fills the Attributes
	 * @pre { this object is locked }
	 * @post { this object is locked, menuResponse is complete}
	 * @param menuResponse ObjectMenuResponse that will be sent to the client
	 */
	void fillAttributeList(AttributeListMessage* alm, CreatureObject* player, SceneObject* sceneObject) const {

		if(!sceneObject->isTangibleObject())
			return;

		ManagedReference<TangibleObject*> tano = cast<TangibleObject*>(sceneObject);

		if (!player->isPlayerCreature())
			return;

		DataObjectComponent* data = tano->getDataObjectComponent()->get();
		if(data == NULL || !data->isDataStorageUnitData())
			return;

		DataStorageUnitDataComponent* dsuData = cast<DataStorageUnitDataComponent*>(data);
		if( dsuData == NULL )
			return;

		// ID is an integer from 1 to 12
		String title = "@theme_park/book_text:title_" + String::valueOf( dsuData->getId() );
		alm->insertAttribute("contents", title);
	}

};

#endif /* DATASTORAGEUNITATTRIBUTELISTCOMPONENT_H_ */
