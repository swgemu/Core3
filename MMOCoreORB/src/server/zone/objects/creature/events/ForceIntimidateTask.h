
#ifndef FORCEINTIMIDATETASK_H_
#define FORCEINTIMIDATETASK_H_

#include "server/zone/objects/creature/CreatureObject.h"
#include "server/zone/managers/combat/CreatureAttackData.h"

class ForceIntimidateTask : public Task {
	ManagedReference<CreatureObject*> sourceCreo;
	const CreatureAttackData data;
	Reference<SortedVector<ManagedReference<TangibleObject*> >* > targets;
	int targetIndex;

public:
	ForceIntimidateTask(CreatureObject* creo, SortedVector<ManagedReference<TangibleObject*> >* targets, const CombatQueueCommand *command) : data("", command, 0) {
		sourceCreo = creo;
		targetIndex = 0;
		this->targets = targets;

	}

	void run() {
		Locker locker(sourceCreo);

		for (int index=targetIndex;  index < targets->size(); index++) {

			TangibleObject* tar = targets->get(index);

			if(tar == NULL)
				continue;

			CreatureObject* tarCreo = tar->asCreatureObject();
			if(tarCreo != NULL && tarCreo != sourceCreo) {

				sourceCreo->doCombatAnimation(tarCreo, STRING_HASHCODE("force_intimidate_chain"), 0x01, data.getTrails());
				sourceCreo = tarCreo;

				targetIndex = index+1;
				if(targetIndex < targets->size())
					schedule(100);

				return;
			}
		}
	}
};

#endif /* FORCEINTIMIDATETASK_H_ */
