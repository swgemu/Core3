#include "server/zone/objects/area/SarlaccArea.h"
#include "server/zone/objects/creature/CreatureObject.h"
#include "server/zone/objects/player/PlayerObject.h"
#include "server/zone/objects/creature/CreatureAttribute.h"
#include "server/zone/packets/scene/PlayClientEffectLocMessage.h"
#include "server/zone/Zone.h"

void SarlaccAreaImplementation::notifyEnter(SceneObject* object) {
	if (object == NULL || !object->isPlayerCreature())
		return;

	Locker plocker(object);

	CreatureObject* player = cast<CreatureObject*>(object);

	if (player == NULL)
		return;

	if (getRadius() == 60) {
		player->sendSystemMessage("@mob/sarlacc:sarlacc_poison"); // The air is thick with the smell of rot and disease.
	} else {
		Time currentTime;
		int timeDiff = currentTime.getMiliTime() - lastErupt.getMiliTime();

		if (timeDiff < 10000) // 10 second cooldown on erupt
			return;

		PlayClientEffectLoc* effectLoc = new PlayClientEffectLoc("clienteffect/cr_sarlacc_erupt.cef", "tatooine", getPositionX(), getPositionZ(), getPositionY(), 0, 3);
		player->broadcastMessage(effectLoc, true);

		Reference<SortedVector<ManagedReference<QuadTreeEntry*> >*> closeObjects = new SortedVector<ManagedReference<QuadTreeEntry*> >();
		zone->getInRangeObjects(getWorldPositionX(), getWorldPositionY(), 60, closeObjects, true);

		for (int i = 0; i < closeObjects->size(); ++i) {
			SceneObject* scno = cast<SceneObject*>(closeObjects->get(i).get());

			if (scno != NULL && scno->isPlayerCreature()) {
				ManagedReference<CreatureObject*> playerCreature = cast<CreatureObject*>(scno);

				if (playerCreature == NULL)
					continue;

				playerCreature->sendSystemMessage("@mob/sarlacc:sarlacc_erupt"); // The Sarlacc suddenly erupts, spewing a diseased and corrosive substance into the air!

				if (playerCreature->getSkillMod("resistance_disease") < 24) {
					playerCreature->addDotState(player, CreatureState::DISEASED, 0, 30 + System::random(20), CreatureAttribute::HEALTH, 30 * 60, 2000, 0);
					playerCreature->sendSystemMessage("@mob/sarlacc:sarlacc_dot"); // You suddenly feel weak and sick.
				}
			}
		}

		lastErupt.updateToCurrentTime();

	}
}
