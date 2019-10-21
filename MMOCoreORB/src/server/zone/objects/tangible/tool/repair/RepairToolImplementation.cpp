/*
 * RepairToolImplementation.cpp
 *
 *  Created on: Mar 21, 2012
 *      Author: Kyle
 */

#include "server/zone/objects/tangible/tool/repair/RepairTool.h"
#include "templates/tangible/tool/RepairToolTemplate.h"
#include "server/zone/objects/player/PlayerObject.h"
#include "server/zone/managers/player/PlayerManager.h"
#include "server/zone/objects/manufactureschematic/craftingvalues/CraftingValues.h"
#include "server/zone/packets/scene/AttributeListMessage.h"
#include "server/zone/objects/player/sui/listbox/SuiListBox.h"
#include "server/zone/objects/player/sui/callbacks/RepairToolSuiCallback.h"

void RepairToolImplementation::loadTemplateData(SharedObjectTemplate* templateData) {
	TangibleObjectImplementation::loadTemplateData(templateData);
}

void RepairToolImplementation::fillAttributeList(AttributeListMessage* msg, CreatureObject* object) {
	TangibleObjectImplementation::fillAttributeList(msg, object);
	msg->insertAttribute("quality", Math::getPrecision(quality, 1));
}

void RepairToolImplementation::updateCraftingValues(CraftingValues* values, bool firstUpdate) {
	quality = values->getCurrentValue("quality");
}
int RepairToolImplementation::handleObjectMenuSelect(CreatureObject* player, byte selectedID) {

	switch( selectedID ) {
	case 20:
		sendRepairListTo(player);
		break;
	default:
		break;
	}

	return TangibleObjectImplementation::handleObjectMenuSelect(player, selectedID);
}

void RepairToolImplementation::sendRepairListTo(CreatureObject* player) {

	if (!isASubChildOf(player))
		return;

	PlayerManager* playerManager = player->getZoneServer()->getPlayerManager();

	// Get canRepairType mask from this tools RepairToolTemplate

	if (templateObject == nullptr || !templateObject->isRepairToolTemplate())
		return;

	RepairToolTemplate* repairToolData = templateObject.castTo<RepairToolTemplate*>().get();

	if ( repairToolData == nullptr )
		return;
                
	Vector<ManagedReference<SceneObject*> > repairableItems = playerManager->getInventoryItemsOfType(player, repairToolData -> getRepairType());
	
	
	ManagedReference<SuiListBox*> listbox = new SuiListBox(player, SuiWindowType::REPAIR_TOOL_DIALOG);

	for (int i = 0; i < repairableItems.size(); i++) {
		SceneObject* item = repairableItems.get(i);

		ManagedReference<TangibleObject*> tano = cast<TangibleObject*>(item);

		if (tano != nullptr ) {
			// Not broken (1/1) but still damaged.
			bool inNeedOfRepair = (!(tano -> isBroken()) && (tano -> getConditionDamage() > 0));
			if (inNeedOfRepair) {
				listbox->addMenuItem( tano->getDisplayedName(), tano->getObjectID());
			}
		}
	}

	listbox->setCallback(new RepairToolSuiCallback(player->getZoneServer()));
	listbox->setPromptTitle("@repairable_objects");
	listbox->setPromptText("@select_repair");
	listbox->setUsingObject(_this.getReferenceUnsafeStaticCast());
	listbox->setCancelButton(true, "@cancel");
	listbox->setOkButton(true, "@repair");

	player->getPlayerObject()->addSuiBox(listbox);
	player->sendMessage(listbox->generateMessage());
}
