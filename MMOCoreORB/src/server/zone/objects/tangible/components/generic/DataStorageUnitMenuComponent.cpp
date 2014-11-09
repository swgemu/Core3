/*
 * DataStorageUnitMenuComponent
 *
 *  Created on: 11/8/2014
 *      Author: Klivian
 */

#include "server/zone/objects/creature/CreatureObject.h"
#include "server/zone/objects/player/PlayerObject.h"
#include "DataStorageUnitMenuComponent.h"
#include "server/zone/objects/scene/components/ObjectMenuComponent.h"
#include "server/zone/objects/tangible/components/generic/DataStorageUnitDataComponent.h"
#include "server/zone/packets/object/ObjectMenuResponse.h"
#include "server/zone/objects/player/sui/messagebox/SuiMessageBox.h"

void DataStorageUnitMenuComponent::fillObjectMenuResponse(SceneObject* sceneObject,
		ObjectMenuResponse* menuResponse, CreatureObject* player) {

	if(!sceneObject->isTangibleObject())
		return;

	TangibleObject* tano = cast<TangibleObject*>(sceneObject);
	if(tano == NULL)
		return;

	menuResponse->addRadialMenuItem(18, 3, "@ui_radial:item_activate"); // Activate

	TangibleObjectMenuComponent::fillObjectMenuResponse(sceneObject, menuResponse, player);
}

int DataStorageUnitMenuComponent::handleObjectMenuSelect(SceneObject* sceneObject,
		CreatureObject* player, byte selectedID) {

	if (selectedID != 20 && selectedID != 18) {
		return TangibleObjectMenuComponent::handleObjectMenuSelect(sceneObject, player, selectedID);
	}

	if(!sceneObject->isTangibleObject())
		return 0;

	ManagedReference<TangibleObject*> tano = cast<TangibleObject*>(sceneObject);

	if (!player->isPlayerCreature())
		return 0;

	DataObjectComponent* data = tano->getDataObjectComponent()->get();
	if(data == NULL || !data->isDataStorageUnitData())
		return 0;

	DataStorageUnitDataComponent* dsuData = cast<DataStorageUnitDataComponent*>(data);
	if( dsuData == NULL )
		return 0;

	// ID is an integer from 1 to 12
	String title = "@theme_park/book_text:title_" + String::valueOf( dsuData->getId() );
	String text  = "@theme_park/book_text:text_"  + String::valueOf( dsuData->getId() );

	// Build and send SUI to player
	ManagedReference<SuiMessageBox*> box = new SuiMessageBox(player, SuiWindowType::DATA_STORAGE_UNIT_MESSAGE);
	box->setPromptTitle(title);
	box->setPromptText(text);
	box->setUsingObject(player);
	box->setForceCloseDisabled();

	player->getPlayerObject()->addSuiBox(box);
	player->sendMessage(box->generateMessage());

	return 0;
}
