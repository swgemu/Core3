/*
 * CreatureSetDefenderTask.h
 *
 *  Created on: Nov 27, 2010
 *      Author: oru
 */

#ifndef CREATURESETDEFENDERTASK_H_
#define CREATURESETDEFENDERTASK_H_

class CreatureSetDefenderTask : public Task {
	ManagedReference<AiAgent*> creature;
	ManagedReference<SceneObject*> defender;
	ManagedReference<Observer*> observer;

	DeltaVector<ManagedReference<SceneObject*> > defenderList;
	bool dropObserver;

public:
	CreatureSetDefenderTask(AiAgent* agent, SceneObject* def, Observer* obs, bool dropObserversFromDefenderList) {
		creature = agent;
		defender = def;
		observer = obs;
		dropObserver = dropObserversFromDefenderList;

		if (dropObserversFromDefenderList)
			defenderList = *creature->getDefenderList();
	}

	void run() {
		Locker locker(creature);

		if (dropObserver) {
			for (int i = 0; i < defenderList.size(); ++i) {
				ManagedReference<SceneObject*>  defender = defenderList.get(i);

				Locker locker(defender, creature);

				defender->dropObserver(ObserverEventType::SPECIALATTACK, observer);
			}
		}


		Locker clocker(defender, creature);

		defender->registerObserver(ObserverEventType::SPECIALATTACK, observer);
	}

};


#endif /* CREATURESETDEFENDERTASK_H_ */
