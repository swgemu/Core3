/*
 * ConsumableImplementation.cpp
 *
 *  Created on: 14/08/2010
 *      Author: victor
 */

#include "Consumable.h"
#include "server/zone/objects/creature/CreatureObject.h"
#include "server/zone/objects/player/PlayerObject.h"
#include "server/zone/objects/player/Races.h"
#include "server/zone/objects/creature/buffs/DurationBuff.h"
#include "server/zone/objects/creature/buffs/SpiceBuff.h"
#include "server/zone/objects/creature/buffs/DelayedBuff.h"
#include "server/zone/objects/creature/CreatureAttribute.h"
#include "server/zone/packets/scene/AttributeListMessage.h"
#include "server/zone/templates/tangible/ConsumableTemplate.h"
#include "DelayedBuffObserver.h"

void ConsumableImplementation::loadTemplateData(SharedObjectTemplate* templateData) {
	TangibleObjectImplementation::loadTemplateData(templateData);

	ConsumableTemplate* consumable = dynamic_cast<ConsumableTemplate*>(templateData);

	if (consumable == NULL)
		return;

	duration = consumable->getDuration();
	filling = consumable->getFilling();
	nutrition = consumable->getNutrition();

	effectType = consumable->getEffectType();

	eventTypes = *consumable->getEventTypes();

	fillingMin = consumable->getFillingMin();
	fillingMax = consumable->getFillingMax();
	flavorMin = consumable->getFlavorMin();
	flavorMax = consumable->getFlavorMax();
	nutritionMin = consumable->getNutritionMin();
	nutritionMax = consumable->getNutritionMax();
	quantityMin = consumable->getQuantityMin();
	quantityMax = consumable->getQuantityMax();


	modifiers = *consumable->getModifiers();
	buffName = consumable->getBuffName();
	//protected string modifierString;

	//buffCRC = consumable->getBuffCRC();
	buffCRC = buffName.hashCode();

	//consumableType = consumable->getConsumableType(); set by the subobject

	foragedFood = consumable->getForagedFood();

	speciesRestriction = consumable->getSpeciesRestriction();
}

int ConsumableImplementation::handleObjectMenuSelect(CreatureObject* player, byte selectedID) {
	if (selectedID != 20) {
		return TangibleObjectImplementation::handleObjectMenuSelect(player, selectedID);
	}

	if (speciesRestriction == "pets") {
		player->sendSystemMessage("@error_message:pets_only"); //That food is only suitable for pets.
		return 0;
	}

	PlayerObject* ghost = player->getPlayerObject();

	String raceName = player->getSpeciesName();

	if ((speciesRestriction == "2" && raceName != "trandoshan") || (speciesRestriction == "4" && raceName != "wookiee")) {
		player->sendSystemMessage("@error_message:race_restriction"); //That food isn't edible by your species.
		return 0;
	}

	if (isSpice() && player->hasSpice()) {
		player->sendSystemMessage("@spice/spice:sys_already_spiced"); //You are already under the influence of spices.
		return 0;
	}

	if (player->hasBuff(buffCRC)  && (!isAttributeEffect() || isForagedFood())) {
		player->sendSystemMessage("@combat_effects:already_affected"); //You are already under the influence of that food. Eating more won't enhance the effect.
		return 0;
	}

	int availfill = 0;

	if (ghost == NULL)
		return 1;

	if (isFood())
		availfill = ghost->getFoodFillingMax() - ghost->getFoodFilling();

	if (isDrink())
		availfill = ghost->getDrinkFillingMax() - ghost->getDrinkFilling();

	if (filling > availfill) {
		if (isFood())
			player->sendSystemMessage("@error_message:full_food"); //You are too full to eat that.

		if (isDrink())
			player->sendSystemMessage("@error_message:full_drink"); //You are too full to drink that.

		return 1;
	}


	ManagedReference<Buff*> buff = NULL;

	switch (effectType) {
	case EFFECT_ATTRIBUTE: {
		buff = new Buff(player, buffName.hashCode(), duration, BuffType::FOOD);
		setModifiers(buff, false);
		break;
	}

	case EFFECT_SKILL: {
		buff = new Buff(player, buffName.hashCode(), duration, BuffType::FOOD);
		setModifiers(buff, true);
		break;
	}

	case EFFECT_SPICE: {
		buff = new SpiceBuff(player, buffName, String("spice." + buffName + ".up").hashCode(), duration);
		setModifiers(buff, false);
		//buff->parseAttributeModifierString(modifierString);
		player->addBuff(buff);
		//useCharge(player);
		decreaseUseCount();
		return 1;
	}

	case EFFECT_HEALING: {
		int dmghealed = player->healDamage(player, 6, nutrition);

		if (dmghealed <= 0) {
			player->sendSystemMessage("@healing:no_mind_to_heal_self"); //You have no mind to heal.
			return 0;
		}

		StringIdChatParameter stringId("combat_effects", "food_mind_heal");
		stringId.setDI(dmghealed);

		player->sendSystemMessage(stringId);

		break;
	}

	case EFFECT_DURATION: {
		buff = new DurationBuff(player, buffName.hashCode(), duration);
		setModifiers(buff, true);
		//buff->parseSkillModifierString(generateModifierString());
		break;
	}

	case EFFECT_DELAYED: {
		buff = new DelayedBuff(player, buffName.hashCode(), duration);
		setModifiers(buff, true);

		DelayedBuff* delayedBuff = cast<DelayedBuff*>(buff.get());
		delayedBuff->init(&eventTypes);

		break;
	}

	/*case EFFECT_INSTANT: {
		if (modifiers.isEmpty())
			return 0;

		//TODO: Handle each instant effect on its own...
		String effect = modifiers.elementAt(0).getKey();

		if (effect == "slow_dot") {
			//We need to reduce the duration of all the player's current dot effects by nutritions %
			//player->slowDots(nutrition);
		} else if (effect == "burst_run") {
			//We need to reduce the cooldown and efficiency.
			player->activateBurstRun(30, 300 - duration, nutrition);

			if (player->isBurstRunning()) {
				player->sendSystemMessage("@combat_effects:instant_burst_run"); //You instantly burst run at increased efficiency!
			} else {
				//Couldnt burst run yet.
				return 0;
			}
		} else if (effect == "food_reduce") {
			//Tilla till reduces food stomach filling by a percentage
			int currentfilling = player->getFoodFilling();
			player->setFoodFilling(round(currentfilling * (100 - nutrition) / 100.0f), true);
		}
	}*/
	}

	if (buff != NULL)
		player->addBuff(buff);

	if (isFood())
		ghost->setFoodFilling(ghost->getFoodFilling() + filling, true);

	if (isDrink())
		ghost->setDrinkFilling(ghost->getDrinkFilling() + filling, true);

	StringIdChatParameter stringId("base_player", "prose_consume_item");
	stringId.setTT(getObjectID());
	player->sendSystemMessage(stringId);//player->sendSystemMessage("base_player", "prose_consume_item", objectID);;

	//Consume a charge from the item, destroy it if it reaches 0 charges remaining.
	//useCharge(player);
	decreaseUseCount();

	return 0;
}

void ConsumableImplementation::setModifiers(Buff* buff, bool skillModifiers) {
	for (int i = 0; i < modifiers.size(); ++i) {
		String attribute = modifiers.elementAt(i).getKey();
		float value = modifiers.elementAt(i).getValue();

		uint8 hamAttribute = CreatureAttribute::getAttribute(attribute);

		if (!isSpice() && !isForagedFood())
			value = nutrition;

		if (!skillModifiers)
			buff->setAttributeModifier(hamAttribute, (int)value);

		else
			buff->setSkillModifier(attribute, (int)value);
	}
}

void ConsumableImplementation::fillAttributeList(AttributeListMessage* alm, CreatureObject* player) {

	if (maxCondition > 0) {
		StringBuffer cond;
		cond << (maxCondition-(int)conditionDamage) << "/" << maxCondition;

		alm->insertAttribute("condition", cond);
	}

	alm->insertAttribute("volume", volume);

	if (!isAttributeEffect() && !isSpiceEffect()) {
		if (useCount > 0)
			alm->insertAttribute("counter_uses_remaining", useCount);
	} else {
		if (useCount > 0)
			alm->insertAttribute("quantity", useCount);
	}

	if (craftersName != ""){
		alm->insertAttribute("crafter", craftersName);
	}

	if (objectSerial != ""){
		alm->insertAttribute("serial_number", objectSerial);
	}

	switch (effectType) {
	case EFFECT_HEALING: {

		if (filling > 0) {
			if (isFood())
				alm->insertAttribute("stomach_food", filling);
			else if (isDrink())
				alm->insertAttribute("stomach_drink", filling);
		}

		for (int i = 0; i < modifiers.size(); ++i) {
			VectorMapEntry<String, float>* entry = &modifiers.elementAt(i);;
			alm->insertAttribute(entry->getKey() + "_heal", nutrition);
		}

		break;
	}
	case EFFECT_ATTRIBUTE: {

		if (filling > 0) {
			if (isFood())
				alm->insertAttribute("stomach_food", filling);
			else if (isDrink())
				alm->insertAttribute("stomach_drink", filling);
		}

		if (duration <= 0)
			return;

		StringBuffer durationstring;

		int minutes = (int) floor(duration / 60.0f);
		int seconds = duration % 60;

		if (minutes > 0)
			durationstring << minutes << "m ";

		durationstring << seconds << "s";

		int mods = modifiers.size();

		if (mods > 0) {
			alm->insertAttribute("attribmods", mods);

			for (int i = 0; i < mods; ++i) {
				VectorMapEntry<String, float>* entry = &modifiers.elementAt(i);
				StringBuffer nutritionstring;

				if (!isForagedFood())
					nutritionstring << ((nutrition > 0) ? "+" : "") << nutrition << " for " << durationstring.toString();
				else
					nutritionstring << ((entry->getValue() > 0) ? "+" : "") << entry->getValue() << ", " << durationstring.toString();

				alm->insertAttribute("attr_" + entry->getKey(), nutritionstring.toString());
			}
		}
		break;
	}
	case EFFECT_SPICE: {
		int mods = modifiers.size();

		if (mods > 0) {
			StringBuffer durationstring;
			durationstring << duration << "s";

			alm->insertAttribute("attribmods", mods);

			for (int i = 0; i < mods; ++i) {
				VectorMapEntry<String, float>* entry = &modifiers.elementAt(i);
				StringBuffer nutritionstring;
				nutritionstring << ((entry->getValue() > 0) ? "+" : "") << entry->getValue() << ", " << durationstring.toString();
				alm->insertAttribute("attr_" + entry->getKey(), nutritionstring.toString());
			}
		}

		break;
	}
	case EFFECT_SKILL: {

		if (filling > 0) {
			if (isFood())
				alm->insertAttribute("stomach_food", filling);
			else if (isDrink())
				alm->insertAttribute("stomach_drink", filling);
		}

		for (int i = 0; i < modifiers.size(); ++i) {
			VectorMapEntry<String, float>* entry = &modifiers.elementAt(i);
			alm->insertAttribute("skill", "@stat_n:" + entry->getKey());
		}

		StringBuffer nutritionstring;
		nutritionstring << ((nutrition > 0) ? "+" : "") << nutrition;

		alm->insertAttribute("modifier", nutritionstring.toString());

		StringBuffer durationstring;

		int minutes = (int) floor(duration / 60.0f);
		int seconds = duration % 60;

		if (minutes > 0)
			durationstring << minutes << "m ";

		durationstring << seconds << "s";

		alm->insertAttribute("duration", durationstring.toString());

		break;
	}
	case EFFECT_DURATION: {

		if (filling > 0) {
			if (isFood())
				alm->insertAttribute("stomach_food", filling);
			else if (isDrink())
				alm->insertAttribute("stomach_drink", filling);
		}

		for (int i = 0; i < modifiers.size(); ++i) {
			VectorMapEntry<String, float>* entry = &modifiers.elementAt(i);

			String key = entry->getKey();
			float value = entry->getValue();

			alm->insertAttribute("duration_effect", "@obj_attr_n:" + key + "_d");

			alm->insertAttribute(key + "_eff", nutrition);

			StringBuffer durationstring;

			int minutes = (int) floor(duration / 60.0f);
			int seconds = duration % 60;

			if (minutes > 0)
				durationstring << minutes << "m ";

			durationstring << seconds << "s";

			alm->insertAttribute("duration", durationstring.toString());
		}

		break;
	}
	case EFFECT_DELAYED: {

		if (filling > 0) {
			if (isFood())
				alm->insertAttribute("stomach_food", filling);
			else if (isDrink())
				alm->insertAttribute("stomach_drink", filling);
		}

		for (int i = 0; i < modifiers.size(); ++i) {
			VectorMapEntry<String, float>* entry = &modifiers.elementAt(i);

			String key = entry->getKey();
			float value = entry->getValue();

			alm->insertAttribute("delay_effect", "@obj_attr_n:" + key + "_d");

			alm->insertAttribute(key + "_eff", nutrition);

			if (duration > 1)
				alm->insertAttribute(key + "_dur", duration);
		}

		break;
	}
	case EFFECT_INSTANT: {

		if (filling > 0) {
			if (isFood())
				alm->insertAttribute("stomach_food", filling);
			else if (isDrink())
				alm->insertAttribute("stomach_drink", filling);
		}

		for (int i = 0; i < modifiers.size(); ++i) {
			VectorMapEntry<String, float>* entry = &modifiers.elementAt(i);

			String key = entry->getKey();
			float value = entry->getValue();

			alm->insertAttribute("instant_effect", "@obj_attr_n:" + key + "_d");
			alm->insertAttribute(key + "_v1", nutrition);

			if (duration > 1)
				alm->insertAttribute(key + "_v2", duration);
		}
		break;
	}
	}

	if (!speciesRestriction.isEmpty()) {
		if (speciesRestriction == "pets")
			alm->insertAttribute("race_restriction", "@obj_attr_n:speciespet"); //Pets
		else
			alm->insertAttribute("race_restriction", "@obj_attr_n:species" + speciesRestriction);
	}
}
