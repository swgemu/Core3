#ifndef GROWABLEPLANTSUICALLBACK_H_
#define GROWABLEPLANTSUICALLBACK_H_

#include "server/zone/objects/player/sui/SuiCallback.h"
#include "server/zone/objects/player/sui/listbox/SuiListBox.h"
#include "server/zone/objects/tangible/misc/PlantObject.h"
#include "server/zone/managers/crafting/CraftingManager.h"
#include "server/zone/managers/object/ObjectManager.h"
#include "server/zone/objects/resource/ResourceContainer.h"

class GrowablePlantSuiCallback : public SuiCallback {
public:
	GrowablePlantSuiCallback(ZoneServer* server)
		: SuiCallback(server) {
	}

	void run(CreatureObject* player, SuiBox* suiBox, bool cancelPressed, Vector<UnicodeString>* args) {
		if (!suiBox->isListBox() || cancelPressed)
			return;

		if (args->size() < 1)
			return;

		int index = Integer::valueOf(args->get(0).toString());

		if (index == -1)
			return;

		SuiListBox* listBox = cast<SuiListBox*>(suiBox);

		ManagedReference<SceneObject*> obj = suiBox->getUsingObject();

		if (obj == NULL)
			return;

		ManagedReference<PlantObject*> plant = cast<PlantObject*>(obj.get());

		if (plant == NULL)
			return;

		Locker clocker(plant, player);

		uint64 resourceID = listBox->getMenuObjectID(index);

		ManagedReference<ResourceContainer*> resource = (server->getObject(resourceID)).castTo<ResourceContainer*>();

		if (resource == NULL)
			return;

		ManagedReference<SceneObject*> playerParent = resource->getParentRecursively(SceneObjectType::PLAYERCREATURE).get();

		if (playerParent == NULL)
			return;

		int quantity = resource->getQuantity();

		if (quantity < 25) {
			player->sendSystemMessage("@plant_grow:not_enough_resource"); // You don't have enough resources of this type to apply to the plant.
			return;
		}

		int type = 0;

		ManagedReference<ResourceSpawn*> spawn = resource->getSpawnObject();

		if (spawn == NULL)
			return;

		if (!spawn->isType("organic") && !spawn->isType("water"))
			return;

		if (spawn->isType("organic")) {
			int critAttribOne = spawn->getValueOf(plant->getCriticalAttributeOne());
			int critAttribTwo = spawn->getValueOf(plant->getCriticalAttributeTwo());
			int nutrientLevel = plant->getNutrientLevel();

			if (nutrientLevel >= 100) {
				player->sendSystemMessage("@plant_grow:too_much_nutrients"); // The plant's soil is already filled with nutrients.
				return;
			}

			if (critAttribOne == 0)
				critAttribOne = critAttribTwo;
			else if (critAttribTwo == 0)
				critAttribTwo = critAttribOne;

			int factor = (critAttribOne + critAttribTwo) / 2;
			int newQuality = (factor * 25 + plant->getNutrientQuality() * nutrientLevel) / (nutrientLevel + 25);

			nutrientLevel += 5;

			plant->setNutrientLevel(nutrientLevel);
			plant->setNutrientQuality(newQuality);

			player->sendSystemMessage("@plant_grow:apply_nutrients"); // You apply nutrients to the plant.
		} else {
			int quality = spawn->getValueOf(CraftingManager::OQ);
			int waterLevel = plant->getWaterLevel();

			if (waterLevel >= 100) {
				player->sendSystemMessage("@plant_grow:too_much_water"); // The plant's soil is already saturated with water.
				return;
			}

			int newQuality = (quality * 25 + plant->getNutrientQuality() * waterLevel) / (waterLevel + 25);
			waterLevel += 5;

			plant->setWaterQuality(newQuality);
			plant->setWaterLevel(waterLevel);

			player->sendSystemMessage("@plant_grow:apply_water"); // You apply water to the plant.
		}

		resource->setQuantity(quantity - 25, true);
	}
};

#endif /* GROWABLEPLANTSUICALLBACK_H_ */
