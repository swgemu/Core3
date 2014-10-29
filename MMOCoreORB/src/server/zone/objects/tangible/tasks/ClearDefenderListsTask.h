/*
 * ClearDefenderLists.h
 *
 *  Created on: 10/04/2012
 *      Author: victor
 */

#ifndef CLEARDEFENDERLISTSTASK_H_
#define CLEARDEFENDERLISTSTASK_H_

#include "server/zone/objects/tangible/TangibleObject.h"

class ClearDefenderListsTask : public Task {
	DeltaVector<ManagedReference<SceneObject* > > defenderList;
	ManagedReference<TangibleObject*> tangibleObject;
public:
	ClearDefenderListsTask(const DeltaVector<ManagedReference<SceneObject* > >& list, TangibleObject* tano) :
		defenderList(list), tangibleObject(tano) {

	}

	void run() {
		Locker locker(tangibleObject);

		for (int i = 0; i < defenderList.size(); ++i) {
			SceneObject* defender = defenderList.get(i);

			if (defender == NULL || !defender->isTangibleObject())
				continue;

			Locker clocker(defender, tangibleObject);

			(cast<TangibleObject*>(defender))->removeDefender(tangibleObject);
		}

		tangibleObject->removeDefenders();
	}
};



#endif /* CLEARDEFENDERLISTS_H_ */
