#include "server/zone/objects/creature/CreatureObject.h"
#include "server/zone/objects/player/PlayerObject.h"
#include "server/zone/Zone.h"
#include "server/zone/ZoneServer.h"
#include "FireworkShowMenuComponent.h"
#include "server/zone/packets/object/ObjectMenuResponse.h"
#include "server/zone/objects/tangible/firework/components/FireworkShowDataComponent.h"

#include "server/zone/objects/player/sui/callbacks/FireworkShowAddEventSuiCallback.h"
#include "server/zone/objects/player/sui/callbacks/FireworkShowRemoveEventSuiCallback.h"
#include "server/zone/objects/player/sui/callbacks/FireworkShowModifyEventSuiCallback.h"
#include "server/zone/objects/player/sui/callbacks/FireworkShowReorderShowSuiCallback.h"
#include "server/zone/objects/player/sui/listbox/SuiListBox.h"

void FireworkShowMenuComponent::fillObjectMenuResponse(SceneObject* sceneObject,
		ObjectMenuResponse* menuResponse, CreatureObject* player) const {

	if (!sceneObject->isFireworkObject())
		return;

	FireworkObject* fireworkShow = cast<FireworkObject*>(sceneObject);

	if (fireworkShow == NULL)
		return;

	DataObjectComponent* data = fireworkShow->getDataObjectComponent()->get();

	if(data == NULL || !data->isFireworkShowData())
		return;

	FireworkShowDataComponent* fireworkShowData = cast<FireworkShowDataComponent*>(data);
	int totalFireworks = fireworkShowData->getTotalFireworkCount();

	menuResponse->addRadialMenuItem(68, 3, "@firework:mnu_show_data");
	menuResponse->addRadialMenuItemToRadialID(68, 69, 3, "@firework:mnu_add_event");
	if (totalFireworks > 0) {
		menuResponse->addRadialMenuItemToRadialID(68, 70, 3, "@firework:mnu_remove_event");
		menuResponse->addRadialMenuItemToRadialID(68, 71, 3, "@firework:mnu_modify_event");
	}
	if (totalFireworks > 1) {
		menuResponse->addRadialMenuItemToRadialID(68, 72, 3, "@firework:mnu_reorder_show");
	}

	TangibleObjectMenuComponent::fillObjectMenuResponse(sceneObject,
			menuResponse, player);

}

int FireworkShowMenuComponent::handleObjectMenuSelect(SceneObject* sceneObject,
		CreatureObject* player, byte selectedID) const {

	if(!sceneObject->isASubChildOf(player))
		return 0;

	if (!sceneObject->isFireworkObject())
		return 0;

	if (!player->isPlayerCreature())
		return 0;

	if (player->getZone() == NULL)
		return 0;
	FireworkObject* firework = cast<FireworkObject*>(sceneObject);

	switch (selectedID) {
		case 20:
			firework->beginShowLaunch(player);
			break;
		case 68: // showData
			showData(player, firework);
			break;
		case 69: // Add Event
			addEvent(player, firework);
			break;
		case 70:  // Remove Event
			removeEvent(player, firework);
			break;
		case 71:  // Modify Event
			modifyEvent(player, firework);
			break;
		case 72:  // Reorder Show
			reorderShow(player, firework);
			break;
		default:
			return TangibleObjectMenuComponent::handleObjectMenuSelect(sceneObject,	player, selectedID);
		}
	return 0;
}

void FireworkShowMenuComponent::addEvent(CreatureObject* player, FireworkObject* fireworkShow) const {

	DataObjectComponent* data = fireworkShow->getDataObjectComponent()->get();

	if (data == NULL || !data->isFireworkShowData())
		return;

	FireworkShowDataComponent* fireworkShowData = cast<FireworkShowDataComponent*>(data);

	int curFireworks = fireworkShowData->getTotalFireworkCount();
	int showCapacity = fireworkShow->getCapacity();

	ManagedReference<PlayerObject*> ghost = player->getPlayerObject();

	if (ghost == NULL)
		return;

	if (curFireworks >= showCapacity && !ghost->isPrivileged()) {
		player->sendSystemMessage("This firework show is at full capacity.");
		return;
	}

	if (ghost->hasSuiBoxWindowType(SuiWindowType::FIREWORK_SHOW_ADDEVENT) || ghost->hasSuiBoxWindowType(SuiWindowType::FIREWORK_SHOW_REMOVEEVENT)
			|| ghost->hasSuiBoxWindowType(SuiWindowType::FIREWORK_SHOW_REORDERSHOW) || ghost->hasSuiBoxWindowType(SuiWindowType::FIREWORK_SHOW_MODIFYEVENT)
				|| ghost->hasSuiBoxWindowType(SuiWindowType::FIREWORK_SHOW_DELAYSELECTION)) {
		return;
	}

	Locker plocker(player);

	ManagedReference<SuiListBox*> suiBox = new SuiListBox(player, SuiWindowType::FIREWORK_SHOW_ADDEVENT, SuiListBox::HANDLETWOBUTTON);
	suiBox->setPromptTitle("Select Show Addition");
	suiBox->setPromptText("Select the firework to append to the end of the show package.");
	suiBox->setOkButton(true, "@ok");
	suiBox->setCancelButton(true, "@cancel");
	suiBox->setUsingObject(fireworkShow);

	ManagedReference<SceneObject*> inventory = player->getSlottedObject("inventory");
	SceneObject* sceneObject = NULL;

	for (int i = 0; i < inventory->getContainerObjectsSize(); i++) {
		sceneObject = inventory->getContainerObject(i);
		if (sceneObject == NULL)
			continue;

		FireworkObject* firework = cast<FireworkObject*>(sceneObject);
		if (firework == NULL)
			continue;

		DataObjectComponent* data = firework->getDataObjectComponent()->get();

		if (data != NULL && data->isFireworkShowData())
			continue;

		if (sceneObject->getObjectID() != fireworkShow->getObjectID()) {
			String itemWithUseCount = sceneObject->getDisplayedName() + " (" + firework->getUseCount() + ")";
			suiBox->addMenuItem(itemWithUseCount, sceneObject->getObjectID());
		}
	}

	suiBox->setCallback(new FireworkShowAddEventSuiCallback(player->getZoneServer()));
	ghost->addSuiBox(suiBox);
	player->sendMessage(suiBox->generateMessage());
}

void FireworkShowMenuComponent::showData(CreatureObject* player, FireworkObject* fireworkShow) const {
	ManagedReference<PlayerObject*> ghost = player->getPlayerObject();
	if (ghost == NULL || ghost->hasSuiBoxWindowType(SuiWindowType::FIREWORK_SHOW_ADDEVENT) || ghost->hasSuiBoxWindowType(SuiWindowType::FIREWORK_SHOW_REMOVEEVENT)
			|| ghost->hasSuiBoxWindowType(SuiWindowType::FIREWORK_SHOW_REORDERSHOW) || ghost->hasSuiBoxWindowType(SuiWindowType::FIREWORK_SHOW_MODIFYEVENT)
				|| ghost->hasSuiBoxWindowType(SuiWindowType::FIREWORK_SHOW_DELAYSELECTION)) {
		return;
	}

	DataObjectComponent* data = fireworkShow->getDataObjectComponent()->get();

	if (data == NULL || !data->isFireworkShowData())
		return;

	FireworkShowDataComponent* fireworkShowData = cast<FireworkShowDataComponent*>(data);

	Locker plocker(player);

	ManagedReference<SuiListBox*> suiBox = new SuiListBox(player, SuiWindowType::FIREWORK_SHOW_ADDEVENT, SuiListBox::HANDLESINGLEBUTTON);
	suiBox->setPromptTitle("@firework:data_title");
	suiBox->setPromptText("@firework:data_prompt");
	suiBox->setOkButton(true, "@ok");
	suiBox->setUsingObject(fireworkShow);

	int totalFireworks = fireworkShowData->getTotalFireworkCount();

	for (int i = 0; i < totalFireworks; i++) {
		ManagedReference<FireworkObject*> firework = fireworkShowData->getFirework(i);
		String fireworkDelay = String::valueOf(float(fireworkShowData->getFireworkDelay(i)) / 1000.f);
		String menuItem = "(" + String::valueOf(i) + ":" + fireworkDelay + "s) " + firework->getDisplayedName();
		suiBox->addMenuItem(menuItem);
	}

	ghost->addSuiBox(suiBox);
	player->sendMessage(suiBox->generateMessage());
}

void FireworkShowMenuComponent::removeEvent(CreatureObject* player, FireworkObject* fireworkShow) const {
	ManagedReference<PlayerObject*> ghost = player->getPlayerObject();
	if (ghost == NULL || ghost->hasSuiBoxWindowType(SuiWindowType::FIREWORK_SHOW_ADDEVENT) || ghost->hasSuiBoxWindowType(SuiWindowType::FIREWORK_SHOW_REMOVEEVENT)
			|| ghost->hasSuiBoxWindowType(SuiWindowType::FIREWORK_SHOW_REORDERSHOW) || ghost->hasSuiBoxWindowType(SuiWindowType::FIREWORK_SHOW_MODIFYEVENT)
				|| ghost->hasSuiBoxWindowType(SuiWindowType::FIREWORK_SHOW_DELAYSELECTION)) {
		return;
	}

	DataObjectComponent* data = fireworkShow->getDataObjectComponent()->get();

	if (data == NULL || !data->isFireworkShowData())
		return;

	FireworkShowDataComponent* fireworkShowData = cast<FireworkShowDataComponent*>(data);

	Locker plocker(player);

	ManagedReference<SuiListBox*> suiBox = new SuiListBox(player, SuiWindowType::FIREWORK_SHOW_REMOVEEVENT, SuiListBox::HANDLETWOBUTTON);
	suiBox->setPromptTitle("@firework:remove_title"); // Remove Show Event
	suiBox->setPromptText("@firework:remove_prompt"); // Select the show event to remove then click "OK".
	suiBox->setOkButton(true, "@ok");
	suiBox->setCancelButton(true, "@cancel");
	suiBox->setUsingObject(fireworkShow);

	int totalFireworks = fireworkShowData->getTotalFireworkCount();

	for (int i = 0; i < totalFireworks; i++) {
		ManagedReference<FireworkObject*> firework = fireworkShowData->getFirework(i);
		String fireworkDelay = String::valueOf(float(fireworkShowData->getFireworkDelay(i)) / 1000.f);
		String menuItem = "(" + String::valueOf(i) + ":" + fireworkDelay + "s) " + firework->getDisplayedName();
		suiBox->addMenuItem(menuItem, firework->getObjectID());
	}

	suiBox->setCallback(new FireworkShowRemoveEventSuiCallback(player->getZoneServer()));
	ghost->addSuiBox(suiBox);
	player->sendMessage(suiBox->generateMessage());
}

void FireworkShowMenuComponent::modifyEvent(CreatureObject* player, FireworkObject* fireworkShow) const {
	ManagedReference<PlayerObject*> ghost = player->getPlayerObject();
	if (ghost == NULL || ghost->hasSuiBoxWindowType(SuiWindowType::FIREWORK_SHOW_ADDEVENT) || ghost->hasSuiBoxWindowType(SuiWindowType::FIREWORK_SHOW_REMOVEEVENT)
			|| ghost->hasSuiBoxWindowType(SuiWindowType::FIREWORK_SHOW_REORDERSHOW) || ghost->hasSuiBoxWindowType(SuiWindowType::FIREWORK_SHOW_MODIFYEVENT)
				|| ghost->hasSuiBoxWindowType(SuiWindowType::FIREWORK_SHOW_DELAYSELECTION)) {
		return;
	}

	DataObjectComponent* data = fireworkShow->getDataObjectComponent()->get();

	if (data == NULL || !data->isFireworkShowData())
		return;

	FireworkShowDataComponent* fireworkShowData = cast<FireworkShowDataComponent*>(data);

	Locker plocker(player);

	ManagedReference<SuiListBox*> suiBox = new SuiListBox(player, SuiWindowType::FIREWORK_SHOW_MODIFYEVENT, SuiListBox::HANDLETWOBUTTON);
	suiBox->setPromptTitle("@firework:modify_index_title"); // Event Modification
	suiBox->setPromptText("@firework:modify_index_prompt"); // Select the event index for which you would like to modify the delay time.
	suiBox->setOkButton(true, "@ok");
	suiBox->setCancelButton(true, "@cancel");
	suiBox->setUsingObject(fireworkShow);

	int totalFireworks = fireworkShowData->getTotalFireworkCount();

	for (int i = 0; i < totalFireworks; i++) {
		ManagedReference<FireworkObject*> firework = fireworkShowData->getFirework(i);
		String fireworkDelay = String::valueOf(float(fireworkShowData->getFireworkDelay(i)) / 1000.f);
		String menuItem = "(" + String::valueOf(i) + ":" + fireworkDelay + "s) " + firework->getDisplayedName();
		suiBox->addMenuItem(menuItem, firework->getObjectID());
	}

	suiBox->setCallback(new FireworkShowModifyEventSuiCallback(player->getZoneServer()));
	ghost->addSuiBox(suiBox);
	player->sendMessage(suiBox->generateMessage());
}

void FireworkShowMenuComponent::reorderShow(CreatureObject* player, FireworkObject* fireworkShow) const {
	ManagedReference<PlayerObject*> ghost = player->getPlayerObject();
	if (ghost == NULL || ghost->hasSuiBoxWindowType(SuiWindowType::FIREWORK_SHOW_ADDEVENT) || ghost->hasSuiBoxWindowType(SuiWindowType::FIREWORK_SHOW_REMOVEEVENT)
			|| ghost->hasSuiBoxWindowType(SuiWindowType::FIREWORK_SHOW_REORDERSHOW) || ghost->hasSuiBoxWindowType(SuiWindowType::FIREWORK_SHOW_MODIFYEVENT)
				|| ghost->hasSuiBoxWindowType(SuiWindowType::FIREWORK_SHOW_DELAYSELECTION)) {
		return;
	}

	DataObjectComponent* data = fireworkShow->getDataObjectComponent()->get();

	if (data == NULL || !data->isFireworkShowData())
		return;

	FireworkShowDataComponent* fireworkShowData = cast<FireworkShowDataComponent*>(data);

	Locker plocker(player);

	ManagedReference<SuiListBox*> suiBox = new SuiListBox(player, SuiWindowType::FIREWORK_SHOW_REORDERSHOW, SuiListBox::HANDLETHREEBUTTON);
	suiBox->setPromptTitle("@firework:modify_index_title"); // Remove Show Event
	suiBox->setPromptText("@firework:modify_index_prompt"); // Select the event index for which you would like to modify the delay time.
	suiBox->setOkButton(true, "@ui:done");
	suiBox->setCancelButton(true, "@ui:moveup");
	suiBox->setOtherButton(true, "@ui:movedown");
	suiBox->setUsingObject(fireworkShow);

	int totalFireworks = fireworkShowData->getTotalFireworkCount();

	for (int i = 0; i < totalFireworks; i++) {
		ManagedReference<FireworkObject*> firework = fireworkShowData->getFirework(i);
		String fireworkDelay = String::valueOf(float(fireworkShowData->getFireworkDelay(i)) / 1000.f);
		String menuItem = "(" + String::valueOf(i) + ":" + fireworkDelay + "s) " + firework->getDisplayedName();
		suiBox->addMenuItem(menuItem, firework->getObjectID());
	}

	suiBox->setCallback(new FireworkShowReorderShowSuiCallback(player->getZoneServer()));
	ghost->addSuiBox(suiBox);
	player->sendMessage(suiBox->generateMessage());
}
