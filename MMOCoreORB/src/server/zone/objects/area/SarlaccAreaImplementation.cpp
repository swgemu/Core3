#include "server/zone/objects/area/SarlaccArea.h"
#include "server/zone/objects/creature/CreatureObject.h"
#include "server/zone/objects/player/PlayerObject.h"
#include "server/zone/objects/creature/CreatureAttribute.h"
#include "server/zone/Zone.h"

void SarlaccAreaImplementation::notifyEnter(SceneObject* player) {
	if (!player->isPlayerCreature()) {
		return;
	}

	Locker plocker(player);

	CreatureObject* playerCreature = cast<CreatureObject*>(player);

	playerCreature->sendSystemMessage("@mob/sarlacc:sarlacc_poison"); // The air is thick with the smell of rot and disease.

	ManagedReference<SceneObject*> inventory = playerCreature->getSlottedObject("inventory");

	SceneObject* sco = NULL;
	for (int i=0; i< inventory->getContainerObjectsSize(); i++) {
		sco = inventory->getContainerObject(i);
		if (sco == NULL)
			continue;
		if (sco->getServerObjectCRC() == String("object/tangible/wearables/bodysuit/bodysuit_sarlacc_coverall.iff").hashCode()) {
			WearableObject* wearable = cast<WearableObject*>(sco);

			if(wearable == NULL)
				return;

			if (wearable->isEquipped())
			{
				return;
			}
		}
	}
	playerCreature->addDotState(CreatureState::DISEASED, 0, 30 + System::random(20), CreatureAttribute::HEALTH, 30 * 60, 2000, 0);
	playerCreature->sendSystemMessage("@mob/sarlacc:sarlacc_dot"); // You suddenly feel weak and sick.
}
