/*
 * LootLotteryBallot.h
 *
 *  Created on: March 19, 2015
 *      Author: Anakis
 */

#ifndef LOOTLOTTERYBALLOT_H_
#define LOOTLOTTERYBALLOT_H_

#include "engine/engine.h"
#include "system/util/Vector.h"

class LootLotteryBallot : public Object {

protected:

	ManagedWeakReference<CreatureObject*> player;
	SortedVector<uint64> lootSelections;

public:

     LootLotteryBallot(CreatureObject* pl, Vector<uint64> selection) {
    	 player = pl;
    	 selection.clone(lootSelections);
     }

     bool hasSelection(uint64 objectID) {
    	 return lootSelections.contains(objectID);
     }

     CreatureObject* getPlayer() {
    	 return player.get();
     }

};

#endif /* LOOTLOTTERYBALLOT_H_ */
