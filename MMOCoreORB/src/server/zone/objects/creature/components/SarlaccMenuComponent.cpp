#include "SarlaccMenuComponent.h"
#include "server/zone/Zone.h"
#include "server/zone/ZoneServer.h"
#include "server/zone/objects/creature/CreatureObject.h"
#include "server/zone/objects/player/PlayerObject.h"
#include "server/zone/objects/scene/components/ObjectMenuComponent.h"
#include "server/zone/packets/object/ObjectMenuResponse.h"
#include "server/zone/managers/objectcontroller/ObjectController.h"

void SarlaccMenuComponent::fillObjectMenuResponse(SceneObject* sceneObject, ObjectMenuResponse* menuResponse, CreatureObject* player) {
	TangibleObjectMenuComponent::fillObjectMenuResponse(sceneObject, menuResponse, player);

	menuResponse->addRadialMenuItem(20, 3, "@mob/sarlacc:extract_bile"); // Extract Bile
}

int SarlaccMenuComponent::handleObjectMenuSelect(SceneObject* sceneObject, CreatureObject* player, byte selectedID) {
	if (selectedID == 20) {
		Locker plocker(player, sceneObject);

		ManagedReference<SceneObject*> inventory = player->getSlottedObject("inventory");

		if (inventory->hasFullContainerObjects()) {
			player->sendSystemMessage("@error_message:inv_full"); // Your inventory is full.
			return 0;
		}

		SceneObject* sco = NULL;
		for (int i=0; i< inventory->getContainerObjectsSize(); i++) {
			sco = inventory->getContainerObject(i);
			if (sco == NULL)
				continue;
			if (sco->getServerObjectCRC() == String("object/tangible/loot/quest/quest_item_sarlacc_bile_jar.iff").hashCode()) {
				player->sendSystemMessage("@mob/sarlacc:bile_already"); // You already have a good sample of bile. It probably isn't wise to risk getting more.
				return 0;
			}
			if (sco->getContainerObjectsSize() > 0) {
				for (int j=0; j < sco->getContainerObjectsSize(); j++) {
					SceneObject* child = sco->getContainerObject(j);

					if (child == NULL)
						continue;

					if (child->getServerObjectCRC() == String("object/tangible/loot/quest/quest_item_sarlacc_bile_jar.iff").hashCode()) {
						player->sendSystemMessage("@mob/sarlacc:bile_already"); // You already have a good sample of bile. It probably isn't wise to risk getting more.
						return 0;
					}
				}
			}
		}

		if( !player->getCooldownTimerMap()->isPast("extractBileCooldown") ){
			player->sendSystemMessage("@mob/sarlacc:bile_fail"); // You fail to find enough bile to collect. You need to wait for more to accumulate.
			return 0;
		}

		Reference<SceneObject*> bileSceno = player->getZoneServer()->createObject(String("object/tangible/loot/quest/quest_item_sarlacc_bile_jar.iff").hashCode(), 1);
		if (bileSceno == NULL)
			return 0;

		inventory->transferObject(bileSceno, -1);
		inventory->broadcastObject(bileSceno, true);
		player->sendSystemMessage("@mob/sarlacc:bile_success"); // Despite being nearly overwhelmed by the stench of decay and the reaching tentacles, you manage to collect a sufficient sample of bile.
		player->getCooldownTimerMap()->updateToCurrentAndAddMili("extractBileCooldown", 1000 * 60 * 30); // 30 min cooldown

		return 1;
	}

	return 0;
}

