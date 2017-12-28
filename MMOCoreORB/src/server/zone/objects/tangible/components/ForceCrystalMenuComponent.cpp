/*
 * ForceCrystalMenuComponent.cpp
 */

#include "ForceCrystalMenuComponent.h"

#include "server/zone/objects/creature/CreatureObject.h"
#include "server/zone/objects/tangible/components/TangibleObjectMenuComponent.h"
#include "server/zone/packets/object/ObjectMenuResponse.h"

namespace server {
namespace zone {
namespace objects {
namespace scene {
class SceneObject;
}  // namespace scene
}  // namespace objects
}  // namespace zone
}  // namespace server

void ForceCrystalMenuComponent::fillObjectMenuResponse(SceneObject* sceneObject, ObjectMenuResponse* menuResponse, CreatureObject* player) const {

	TangibleObjectMenuComponent::fillObjectMenuResponse(sceneObject, menuResponse, player);

	menuResponse->addRadialMenuItem(20, 3, "@quest/force_sensitive/intro:crystal_journal"); // Display Journal
}

int ForceCrystalMenuComponent::handleObjectMenuSelect(SceneObject* sceneObject, CreatureObject* creature, byte selectedID) const {
	if (selectedID != 20)
		return 0;

	creature->sendExecuteConsoleCommand("/ui action questJournal");
	return 0;
}
