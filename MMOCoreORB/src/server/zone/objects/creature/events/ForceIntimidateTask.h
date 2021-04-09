
#ifndef FORCEINTIMIDATETASK_H_
#define FORCEINTIMIDATETASK_H_

#include "server/zone/objects/creature/CreatureObject.h"
#include "server/zone/managers/combat/CreatureAttackData.h"
#include "server/zone/objects/player/FactionStatus.h"

class ForceIntimidateTask : public Task {
	ManagedReference<CreatureObject*> targetCreature;
	const CreatureAttackData data;
	Reference<SortedVector<ManagedReference<TangibleObject*> >* > targets;
	int targetIndex;

public:
	ForceIntimidateTask(CreatureObject* targetCreo, SortedVector<ManagedReference<TangibleObject*> >* targets, const CombatQueueCommand *command) : data("", command, 0) {
		targetCreature = targetCreo;
		targetIndex = 0;
		this->targets = targets;
	}

	void run() {

		Locker locker(targetCreature);

		int targetsSize = targets->size();

		for (int i = targetIndex;  i < targetsSize; i++) { // <<-- changed i++ to ++i
			TangibleObject* chainTarget = targets->get(i);

			if (chainTarget == nullptr || targetCreature == nullptr) {
				continue;
			}

			CreatureObject* chainCreature = chainTarget->asCreatureObject();

			if (chainCreature != nullptr && chainCreature != targetCreature) {
				for (int j = 0; j < (targetsSize / 2); j++) {
					targetCreature->doCombatAnimation(chainCreature, STRING_HASHCODE("force_intimidate_chain"), 0x01, data.getTrails());
				}

				targetCreature->doCombatAnimation(chainCreature, STRING_HASHCODE("force_intimidate_chain"), 0x01, data.getTrails());

				targetCreature = chainCreature;

				targetIndex = i + 1;

				if (targetIndex < targets->size()) {
					execute();
				}

				return;
			}
		}
	}
};

#endif /* FORCEINTIMIDATETASK_H_ */