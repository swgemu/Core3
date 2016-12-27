/*
				Copyright <SWGEmu>
		See file COPYING for copying conditions.*/

#ifndef SARLACCERUPTTASK_H_
#define SARLACCERUPTTASK_H_

#include "engine/engine.h"
#include "server/zone/Zone.h"
#include "server/zone/objects/area/SarlaccArea.h"
#include "server/zone/objects/creature/CreatureObject.h"
#include "templates/params/creature/CreatureAttribute.h"

class SarlaccEruptTask: public Task {
	ManagedReference<SarlaccArea*> sarlaccArea;


public:
	SarlaccEruptTask(SarlaccArea* area) {
		sarlaccArea = area;
	}

	void run() {
		if (sarlaccArea == NULL)
			return;

		Zone* zone = sarlaccArea->getZone();

		Reference<SortedVector<ManagedReference<QuadTreeEntry*> >*> closeObjects = new SortedVector<ManagedReference<QuadTreeEntry*> >();
		zone->getInRangeObjects(sarlaccArea->getWorldPositionX(), sarlaccArea->getWorldPositionY(), 60, closeObjects, true);

		for (int i = 0; i < closeObjects->size(); ++i) {
			SceneObject* scno = cast<SceneObject*>(closeObjects->get(i).get());

			if (scno != NULL && scno->isPlayerCreature()) {
				ManagedReference<CreatureObject*> playerCreature = cast<CreatureObject*>(scno);

				if (playerCreature == NULL)
					continue;

				Locker locker(playerCreature);

				playerCreature->sendSystemMessage("@mob/sarlacc:sarlacc_erupt"); // The Sarlacc suddenly erupts, spewing a diseased and corrosive substance into the air!

				if (playerCreature->getSkillMod("resistance_disease") < 24) {
					playerCreature->addDotState(playerCreature, CreatureState::DISEASED, 0, 30 + System::random(20), CreatureAttribute::HEALTH, 30 * 60, 2000, 0);
					playerCreature->sendSystemMessage("@mob/sarlacc:sarlacc_dot"); // You suddenly feel weak and sick.
				}
			}
		}

	}
};

#endif /* SARLACCERUPTTASK_H_ */
