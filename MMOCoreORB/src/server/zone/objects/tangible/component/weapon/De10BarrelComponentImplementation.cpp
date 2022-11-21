/*
 * De10BarrelComponentImplementation.cpp
 *
 * Author: Hakry
 * Date: 11/21/2022
 */

#include "server/zone/objects/tangible/component/weapon/De10BarrelComponent.h"
#include "server/zone/packets/scene/AttributeListMessage.h"
#include "server/zone/managers/loot/LootManager.h"
#include "server/zone/objects/player/PlayerObject.h"

void De10BarrelComponentImplementation::initializeTransientMembers() {
	ComponentImplementation::initializeTransientMembers();
}

void De10BarrelComponentImplementation::fillAttributeList(AttributeListMessage* alm, CreatureObject* creature) {
	if (creature == nullptr) {
		return;
	}

	if (volume > 0) {
		alm->insertAttribute("volume", volume);
	}

	if (creature->isPlayerCreature()) {
		PlayerObject* ghost = creature->getPlayerObject();

		if (ghost != nullptr) {
			String attribute;

			float value;
			double power;
			int precision;

			// Shot hidden attributes to staff
			bool showStats = ghost->isPrivileged();

			String footer;

			for (int i = 0; i < keyList.size(); ++i) {
				footer = "";

				attribute = keyList.get(i);
				value = attributeMap.get(attribute);
				precision = precisionMap.get(attribute);

				if (precision >= 0 && showStats) {
					if (precision >= 10) {
						footer = "%";
						precision -= 10;
					}

					StringBuffer displayvalue;

					displayvalue << Math::getPrecision(value, precision);

					displayvalue << footer;

					alm->insertAttribute(attribute, displayvalue.toString());
				}
			}
		}
	}
}

void De10BarrelComponentImplementation::updateCraftingValues(CraftingValues* values, bool firstUpdate) {
	String attribute;
	float value;
	int precision;
	String title;

	attributeMap.removeAll();
	precisionMap.removeAll();
	titleMap.removeAll();
	keyList.removeAll();

	if (firstUpdate) {
		if (values->hasProperty("useCount")) {
			int count = values->getCurrentValue("useCount");

			// Crafting components dropped or crafted with a single use do not display a "1" (#6924)
			if (count > 1)
				setUseCount(count);
		}
	}

	for (int i = 0; i < values->getExperimentalPropertySubtitleSize(); ++i) {
		attribute = values->getExperimentalPropertySubtitle(i);

		if (attribute == "useCount")
			continue;

		value = values->getCurrentValue(attribute);
		precision = values->getPrecision(attribute);
		title = values->getExperimentalPropertyTitle(attribute);

		if (!hasKey(attribute))
			keyList.add(attribute);

		attributeMap.put(attribute, value);
		precisionMap.put(attribute, precision);
		titleMap.put(attribute, title);

		if (firstUpdate) {
			// All values on DE-10 Pistol Barrels are hidden
			hiddenMap.put(attribute, true);
		}
	}
}