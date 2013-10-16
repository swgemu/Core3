/*
 * SlicingToolImplementation.cpp
 *
 *  Created on: Mar 6, 2011
 *      Author: polonel
 */

#include "server/zone/objects/tangible/tool/smuggler/SlicingTool.h"

#include "server/zone/objects/manufactureschematic/craftingvalues/CraftingValues.h"
#include "server/zone/packets/scene/AttributeListMessage.h"
#include "server/zone/packets/tangible/TangibleObjectDeltaMessage3.h"

#include "server/zone/templates/tangible/tool/SlicingToolTemplate.h"
#include "server/zone/objects/player/sessions/SlicingSession.h"

void SlicingToolImplementation::loadTemplateData(SharedObjectTemplate* templateData) {
	TangibleObjectImplementation::loadTemplateData(templateData);

	SlicingToolTemplate* slicingTempl = dynamic_cast<SlicingToolTemplate*> (templateData);

	if (slicingTempl == NULL)
		return;

	effectiveness = slicingTempl->getEffectiveness();

}

int SlicingToolImplementation::handleObjectMenuSelect(CreatureObject* player, byte selectedID) {

	if (!isASubChildOf(player))
		return 0;

	if (selectedID != 20)
		return TangibleObjectImplementation::handleObjectMenuSelect(player, selectedID);

	/*
	ManagedReference<Facade*> facade = player->getActiveSession(SessionFacadeType::SLICING);
	ManagedReference<SlicingSession*> session = dynamic_cast<SlicingSession*>(facade.get());

	if (session == NULL) {
		player->sendSystemMessage("You must be in a slicing session in order to use that.");
		return 0;
	}

	if (getGameObjectType() == SceneObjectType::MOLECULARCLAMP)
		session->useClampFromInventory(_this);

	player->sendSystemMessage("You are unable to use that item right now");
	*/

	return 0;
}

void SlicingToolImplementation::fillAttributeList(AttributeListMessage* msg, CreatureObject* object) {
	TangibleObjectImplementation::fillAttributeList(msg, object);

	uint32 gameObjType = getGameObjectType();

	if (gameObjType != SceneObjectType::MOLECULARCLAMP)
		msg->insertAttribute("craft_tool_effectiveness", Math::getPrecision(effectiveness, 2));
}

void SlicingToolImplementation::updateCraftingValues(CraftingValues* values, bool firstUpdate) {
	effectiveness = values->getCurrentValue("usemodifier");

}

bool SlicingToolImplementation::calculateSuccessRate() {
	if (getGameObjectType() == SceneObjectType::FLOWANALYZER) {
		int chance = System::random(100);
		chance += (chance + effectiveness);
		if (chance > 25) // 25% chance to fail
			return true;
	}

	return false;
}
