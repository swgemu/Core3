#ifndef GROWABLEPLANTPULSETASK_H_
#define GROWABLEPLANTPULSETASK_H_

#include "server/zone/objects/creature/CreatureObject.h"
#include "server/zone/objects/tangible/misc/PlantObject.h"

namespace server {
namespace zone {
namespace objects {
namespace tangible {
namespace tasks {

class GrowablePlantPulseTask : public Task {
	ManagedReference<PlantObject*> plant;

public:
	GrowablePlantPulseTask(PlantObject* pl) {
		plant = pl;
	}

	void run() {
		if (plant == NULL)
			return;

		Locker locker(plant);

		Time currentTime;

		Time* lastPulse = plant->getLastPulse();

		// Cycles handles multiple pulses if server was offline during task trigger
		int cycles = (currentTime.getMiliTime() - lastPulse->getMiliTime()) / (PlantObject::PULSERATE * 1000);

		if (cycles < 1)
			cycles = 1;
		else if (cycles > 10)
			cycles = 10;

		ManagedReference<SceneObject*> parent = plant->getRootParent();

		if (parent == NULL || !parent->isBuildingObject()) {
			plant->updateLastPulse();
			this->reschedule(PlantObject::PULSERATE * 1000);
			return;
		}

		plant->updateLastPulse();

		int waterDiff = plant->getWaterLevel() - plant->getIdealWaterLevel();
		int nutrientDiff = plant->getNutrientLevel() - plant->getIdealNutrientLevel();

		if (waterDiff < 20 && nutrientDiff < 20) {
			int healthUpdate = (((40 - (waterDiff + waterDiff)) * (plant->getWaterQuality() + plant->getNutrientQuality()) / 2000) / 5) * cycles;

			if (healthUpdate < 1)
				healthUpdate = 1;

			int health = plant->getPlantHealth() + healthUpdate;

			if (health > 100)
				health = 100;

			plant->setPlantHealth(health);
			plant->setGrowthRate(healthUpdate / cycles);

			if (health > 70) {
				int healthPerCycle = healthUpdate / cycles;
				int growthUpdate = (((health / 20) + healthPerCycle) * (plant->getWaterQuality() + plant->getNutrientQuality()) / 2000) * cycles;

				plant->setGrowth(plant->getGrowth() + growthUpdate);
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

			int health = plant->getPlantHealth() - healthUpdate;
			plant->setPlantHealth(health);

			int healthPerCycle = healthUpdate / cycles;
			int growthRate = healthPerCycle / 2;

			if (growthRate < 1)
				growthRate = 1;

			plant->setGrowthRate(growthRate * -1);

			if (health < 1) {
				plant->changeSize(0);
				return;
			}
		}

		int nutrientLevel = plant->getNutrientLevel() - cycles;

		if (nutrientLevel < 0)
			nutrientLevel = 0;

		int waterLevel = plant->getWaterLevel() - cycles;

		if (waterLevel < 0)
			waterLevel = 0;

		plant->setNutrientLevel(nutrientLevel);
		plant->setWaterLevel(waterLevel);

		if (plant->getGrowth() > 100) {
			if (plant->getSize() < 3) {
				plant->setGrowth(0);
				plant->changeSize(plant->getSize() + 1);
				return;
			} else {
				plant->setGrowth(0);
				int fruit = plant->getFruit();

				if (fruit < 10)
					plant->setFruit(fruit + 1);
			}
		}

		this->reschedule(PlantObject::PULSERATE * 1000);
	}
};

}
}
}
}
}

using namespace server::zone::objects::tangible::tasks;

#endif /* GROWABLEPLANTPULSETASK_H_ */
