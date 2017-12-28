#include <stddef.h>

#include "engine/core/Task.h"
#include "server/zone/objects/area/SarlaccArea.h"
#include "server/zone/objects/area/events/SarlaccEruptTask.h"
#include "server/zone/objects/creature/CreatureObject.h"
#include "server/zone/objects/scene/SceneObject.h"
#include "server/zone/packets/scene/PlayClientEffectLocMessage.h"
#include "system/lang/Time.h"
#include "system/lang/ref/Reference.h"
#include "system/lang/ref/WeakReference.h"
#include "system/platform.h"

void SarlaccAreaImplementation::notifyEnter(SceneObject* object) {
	if (object == NULL || !object->isPlayerCreature())
		return;

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

		Reference<Task*> task = new SarlaccEruptTask(_this.getReferenceUnsafeStaticCast());
		task->execute();

		updateEruptTime();
	}
}
