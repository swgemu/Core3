#ifndef GROWABLEPLANTPULSETASK_H_
#define GROWABLEPLANTPULSETASK_H_

#include "server/zone/objects/tangible/misc/PlantObject.h"
#include "server/zone/ZoneServer.h"

namespace server {
namespace zone {
namespace objects {
namespace tangible {
namespace tasks {

class GrowablePlantPulseTask : public Task {
	ManagedWeakReference<PlantObject*> plant;

public:
	GrowablePlantPulseTask(PlantObject* pl) {
		plant = pl;
	}

	void run() {
		ManagedReference<PlantObject*> strongRef = plant.get();

		if (strongRef == nullptr)
			return;

		if (strongRef->getSize() == 0)
			return;

		if (strongRef->getZoneServer()->isServerLoading()) {
			reschedule(1800 * 1000);
			return;
		}

		Locker locker(strongRef);

		Time* lastPulse = strongRef->getLastPulse();

		// Cycles handles multiple pulses if server was offline during task trigger
		int cycles = lastPulse->miliDifference() / (PlantObject::PULSERATE * 1000);

		if (cycles < 1)
			cycles = 1;
		else if (cycles > 10)
			cycles = 10;

		ManagedReference<SceneObject*> rootParent = strongRef->getRootParent();
		ManagedReference<SceneObject*> parent = strongRef->getParent().get();

		strongRef->updateLastPulse();

		if (parent == nullptr || rootParent == nullptr || !rootParent->isBuildingObject() || !parent->isCellObject()) {
			reschedule(PlantObject::PULSERATE * 1000);
			return;
		}

		int waterDiff = abs(strongRef->getWaterLevel() - strongRef->getIdealWaterLevel());
		int nutrientDiff = abs(strongRef->getNutrientLevel() - strongRef->getIdealNutrientLevel());

		if (waterDiff < 20 && nutrientDiff < 20) {
			int healthUpdate = (((50 - (waterDiff + nutrientDiff)) * (strongRef->getWaterQuality() + strongRef->getNutrientQuality()) / 2000) / 5) * cycles;

			if (healthUpdate < 1)
				healthUpdate = 1;

			int health = strongRef->getPlantHealth() + healthUpdate;

			if (health > 100)
				health = 100;

			strongRef->setPlantHealth(health);
			strongRef->setGrowthRate(healthUpdate / cycles);

			if (health > 70) {
				int healthPerCycle = healthUpdate / cycles;
				int growthUpdate = (((health / 20) + healthPerCycle) * (strongRef->getWaterQuality() + strongRef->getNutrientQuality()) / 2000) * cycles;

				strongRef->setGrowth(strongRef->getGrowth() + growthUpdate);
			}
		} else {
			if (waterDiff < 20)
				waterDiff = 20;
			if (nutrientDiff < 20)
				nutrientDiff = 20;

			int healthUpdate = (((waterDiff - 20) + (nutrientDiff - 20)) / 10) * cycles;

			if (healthUpdate > 6)
				healthUpdate = 6;
			if (healthUpdate < 1)
				healthUpdate = 1;

			int health = strongRef->getPlantHealth() - healthUpdate;
			strongRef->setPlantHealth(health);

			int healthPerCycle = healthUpdate / cycles;
			int growthRate = healthPerCycle / 2;

			if (growthRate < 1)
				growthRate = 1;

			strongRef->setGrowthRate(growthRate * -1);

			if (health < 1) {
				strongRef->changeSize(0);
				return;
			}
		}

		int nutrientLevel = strongRef->getNutrientLevel() - cycles;

		if (nutrientLevel < 0)
			nutrientLevel = 0;

		int waterLevel = strongRef->getWaterLevel() - cycles;

		if (waterLevel < 0)
			waterLevel = 0;

		strongRef->setNutrientLevel(nutrientLevel);
		strongRef->setWaterLevel(waterLevel);

		if (strongRef->getGrowth() > 100) {
			if (strongRef->getSize() < 3) {
				strongRef->setGrowth(0);
				strongRef->changeSize(strongRef->getSize() + 1);
				return;
			} else {
				strongRef->setGrowth(0);
				int fruit = strongRef->getFruit();

				if (fruit < 10)
					strongRef->setFruit(fruit + 1);
			}
		}

		reschedule(PlantObject::PULSERATE * 1000);
	}
};

}
}
}
}
}

using namespace server::zone::objects::tangible::tasks;

#endif /* GROWABLEPLANTPULSETASK_H_ */
