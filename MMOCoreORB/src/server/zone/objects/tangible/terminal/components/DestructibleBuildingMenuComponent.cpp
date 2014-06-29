#include "DestructibleBuildingMenuComponent.h"
#include "server/zone/Zone.h"
#include "server/zone/objects/player/PlayerObject.h"
#include "server/zone/packets/object/ObjectMenuResponse.h"
#include "server/zone/objects/scene/SceneObject.h"
#include "server/zone/objects/creature/CreatureObject.h"
#include "server/zone/objects/structure/StructureObject.h"
//#include "server/zone/managers/structure/StructureManager.h"
#include "server/zone/objects/building/BuildingObject.h"
//#include "server/chat/StringIdChatParameter.h"
#include "server/zone/objects/tangible/TangibleObject.h"
//#include "server/zone/objects/cell/CellObject.h"
#include "server/zone/managers/structure/tasks/DestroyStructureTask.h"

void DestructibleBuildingMenuComponent::fillObjectMenuResponse(SceneObject* sceneObject, ObjectMenuResponse* menuResponse, CreatureObject* player) {

	ManagedReference<BuildingObject*> building = cast<BuildingObject*>(sceneObject->getParentRecursively(SceneObjectType::BUILDING).get().get());

	if (building == NULL || player->isDead() || player->isIncapacitated())
		return;

	Zone* zone = building->getZone();

	if(zone == NULL)
		return;

	Reference<Task*> pendingTask = building->getPendingTask("destruction");

	if (pendingTask == NULL && building->isOwnerOf(player)) {
		menuResponse->addRadialMenuItem(227, 3, "@self_destruct:self_destruct"); // Set Self Destruct
		menuResponse->addRadialMenuItemToRadialID(227, 128, 3, "@self_destruct:fifteen"); // 15 seconds
		menuResponse->addRadialMenuItemToRadialID(227, 129, 3, "@self_destruct:thirty"); // 30 seconds
	}

	return;
}

int DestructibleBuildingMenuComponent::handleObjectMenuSelect(SceneObject* sceneObject, CreatureObject* player, byte selectedID) {

	ManagedReference<BuildingObject*> building = cast<BuildingObject*>(sceneObject->getParentRecursively(SceneObjectType::BUILDING).get().get());

	if (building == NULL || player->isDead() || player->isIncapacitated())
		return 0;

	Reference<Task*> pendingTask = building->getPendingTask("destruction");

	if (pendingTask != NULL)
		return 0;

	pendingTask = new DestroyStructureTask(building);

	if (selectedID == 128) {
		building->addPendingTask("destruction", pendingTask, 15000);
		player->sendSystemMessage("@self_destruct:fifteen_seconds");
	} else if (selectedID == 129) {
		building->addPendingTask("destruction", pendingTask, 30000);
		player->sendSystemMessage("@self_destruct:thirty_seconds");
	}
	return 0;
}


