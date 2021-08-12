
#ifndef FORCEINTIMIDATETASK_H_
#define FORCEINTIMIDATETASK_H_

#include "server/zone/objects/creature/CreatureObject.h"
#include "server/zone/managers/combat/CreatureAttackData.h"

class ForceIntimidateTask : public Task {
	ManagedReference<CreatureObject*> targetCreature;
	const CreatureAttackData data;
	Reference<SortedVector<ManagedReference<TangibleObject*> >* > targets;

public:
	ForceIntimidateTask(CreatureObject* targetCreo, SortedVector<ManagedReference<TangibleObject*> >* targets, const CombatQueueCommand *command) : data("", command, 0) {
		targetCreature = targetCreo;
		this->targets = targets;
	}

	void run() {
		if (targetCreature == nullptr) {
			return;
		}

		for (int i = 0;  i < targets->size(); i++) {
			TangibleObject* chainTarget = targets->get(i);

			if (chainTarget == nullptr) {
				continue;
			}

			CreatureObject* chainCreature = chainTarget->asCreatureObject();

			if (chainCreature != nullptr && chainCreature != targetCreature) {
				Locker locker(targetCreature);

				targetCreature->doCombatAnimation(chainCreature, STRING_HASHCODE("force_intimidate_chain"), 0x01, data.getTrails());

				locker.release();

				targetCreature = chainCreature;
			}
		}
	}
};

#endif /* FORCEINTIMIDATETASK_H_ */