/*
 * PowerupObjectImplementation.cpp
 *
 * Created on: march 3, 2012
 * Author: Kyle
 *
 * Modified: November 19, 2022
 * By: Hakry
 */

#include "server/zone/objects/tangible/powerup/PowerupObject.h"
#include "templates/tangible/PowerupTemplate.h"
#include "server/zone/packets/scene/AttributeListMessage.h"
#include "server/zone/objects/tangible/weapon/WeaponObject.h"

//#define DEBUG_POWERUPS

void PowerupObjectImplementation::fillAttributeList(AttributeListMessage* alm, CreatureObject* object) {
	TangibleObjectImplementation::fillAttributeList(alm, object);

	alm->insertAttribute("cat_pup.pup_uses", uses);

	for (int i = 0; i < modifiers.size(); ++i) {
		PowerupStat* stat = &modifiers.get(i);
		StringBuffer val;
		val << Math::getPrecision(stat->getValue(), 2) << "%";
		alm->insertAttribute(stat->getPupAttribute(), val.toString());
	}
}

void PowerupObjectImplementation::fillWeaponAttributeList(AttributeListMessage* alm, WeaponObject* weapon) {
	alm->insertAttribute("cat_pup.pup_uses", uses);

	for (int i = 0; i < modifiers.size(); ++i) {
		PowerupStat* stat = &modifiers.get(i);

		float value = getWeaponStat(stat->getAttributeToModify(), weapon, true);
		float valueNoPup = getWeaponStat(stat->getAttributeToModify(), weapon, false);

		String sign = "";

		float pupvalue = (stat->getValue() / 100.f) * valueNoPup;

		if (pupvalue >= 0)
			sign = "+";

		StringBuffer val;
		val << sign << Math::getPrecision(pupvalue, 2);
		alm->insertAttribute(stat->getPupAttribute(), val.toString());
	}
}

float PowerupObjectImplementation::getWeaponStat(const String& attrib, WeaponObject* weapon, bool withPup) const {
	if (attrib == "pointBlankAccuracy")
		return weapon->getPointBlankAccuracy(withPup);
	else if (attrib == "idealRange")
		return weapon->getIdealRange(withPup);
	else if (attrib == "maxRange")
		return weapon->getMaxRange(withPup);
	else if (attrib == "idealAccuracy")
		return weapon->getIdealAccuracy(withPup);
	else if (attrib == "maxRangeAccuracy")
		return weapon->getMaxRangeAccuracy(withPup);
	else if (attrib == "attackSpeed")
		return weapon->getAttackSpeed(withPup);
	else if (attrib == "maxDamage")
		return weapon->getMaxDamage(withPup);
	else if (attrib == "minDamage")
		return weapon->getMinDamage(withPup);
	else if (attrib == "woundsRatio")
		return weapon->getWoundsRatio(withPup);
	else if (attrib == "damageRadius")
		return weapon->getDamageRadius(withPup);
	else if (attrib == "healthAttackCost")
		return weapon->getHealthAttackCost(withPup);
	else if (attrib == "actionAttackCost")
		return weapon->getActionAttackCost(withPup);
	else if (attrib == "mindAttackCost")
		return weapon->getMindAttackCost(withPup);
	else if (attrib == "pointBlankRange")
		return weapon->getPointBlankRange(withPup);

	return 0;
}

void PowerupObjectImplementation::addSecondaryStat(CraftingValues* values, PowerupTemplate* pupTemplate) {
#ifdef DEBUG_POWERUPS
	info(true) << "PowerupObjectImplementation::addSecondaryStat -- called";
#endif // DEBUG_POWERUPS

	if (values == nullptr || pupTemplate == nullptr)
		return;

	// do not attempt to add another secondary stat if the powerup already has all possible stats
	if ((modifiers.size() - 1) >= pupTemplate->getTotalSecondaryAttributes())
		return;

	Vector<PowerupStat> secondaryStats = pupTemplate->getSecondaryAttributes();
	PowerupStat newStat = secondaryStats.get(System::random(secondaryStats.size() - 1));

	// Pup has no secondaries yet, nothing to check against
	if (modifiers.size() == 1) {
		modifiers.add(newStat);

#ifdef DEBUG_POWERUPS
		info(true) << "Pup adding stat " << newStat.getAttributeToModify() << " with a value of " << newStat.getValue();
#endif // DEBUG_POWERUPS

		return;
	}

	bool foundStat = false;

	while (!foundStat) {
		bool hasStat = false;

		// Check that powerup does not already contain the stat
		for (int i = 0; i < modifiers.size(); i++) {
			PowerupStat checkStat = modifiers.get(i);

#ifdef DEBUG_POWERUPS
			info(true) << "Checking newStat " << newStat.getAttributeToModify() << " against " << checkStat.getAttributeToModify();
#endif // DEBUG_POWERUPS

			if (newStat.getAttributeToModify() == checkStat.getAttributeToModify()) {
				hasStat = true;
			}
		}

		if (!hasStat) {
			foundStat = true;
			modifiers.add(newStat);

#ifdef DEBUG_POWERUPS
			info(true) << "Pup adding stat " << newStat.getAttributeToModify() << " with a value of " << newStat.getValue();
#endif // DEBUG_POWERUPS
			return;
		}

		newStat = secondaryStats.get(System::random(secondaryStats.size() - 1));
	}
}

void PowerupObjectImplementation::updateCraftingValues(CraftingValues* values, bool firstUpdate) {
#ifdef DEBUG_POWERUPS
	info(true) << "========== START -  PowerupObjectImplementation::updateCraftingValues ==========";
	info(true) << getCustomObjectName() <<  " Type = " << type;
#endif // DEBUG_POWERUPS

	Reference<PowerupTemplate*> pupTemplate = cast<PowerupTemplate*>(templateObject.get());

	if (pupTemplate == nullptr) {
		return;
	}

	float effect = values->getCurrentValue("effect");
	float maxEffect = values->getMaxValue("effect");

	if (firstUpdate) {
		// Handle first update during assembly to add base values and add primary stat
#ifdef DEBUG_POWERUPS
		info(true) << "PowerupObjectImplementation::updateCraftingValues  -- first update";
#endif // DEBUG_POWERUPS

		String key;
		String value;

		if (pupTemplate->hasPrimaryAttribute()) {
			PowerupStat stat = pupTemplate->getRandomPrimaryAttribute();
			modifiers.add(stat);

			StringBuffer name;
			name << "A " << stat.getName() << " " << pupTemplate->getBaseName();

#ifdef DEBUG_POWERUPS
			info(true) << "Adding Primary attribute: " << stat.getAttributeToModify();
#endif // DEBUG_POWERUPS

			setCustomObjectName(name.toString(), true);
		}

		type = pupTemplate->getType().toLowerCase();
		uses = 100; // Powerups are always 100 uses

#ifdef DEBUG_POWERUPS
		info(true) << "Type = " << type << " Uses = " << uses;
#endif // DEBUG_POWERUPS

	// Handle subsequent crafting updates derived from experimentation
	} else if (pupTemplate->hasSecondaryAttribute()) {
		int roll = System::random(100);

#ifdef DEBUG_POWERUPS
		info(true) << "has secondary attribute -- Current Effect = " << effect << " with a roll of " << roll;
#endif // DEBUG_POWERUPS

		// 1st secondary stat -- Effect is greater than 25% check to apply the stat - roll chance 50%
		if ((effect >= 25.f) && modifiers.size() == 1 && roll < 50) {
			addSecondaryStat(values, pupTemplate);

			// Handle the naming with the 1st secondary stat added
			PowerupStat secondaryNameStat = modifiers.get(1);

			StringBuffer name;
			name << getCustomObjectName().toString() << " of " << secondaryNameStat.getName();

#ifdef DEBUG_POWERUPS
			info(true) << "Pup name set = " << name.toString();
#endif // DEBUG_POWERUPS

			setCustomObjectName(name.toString(), true);

		// 2nd+ secondary stats -- Effect is greater than 50% check to apply thestat - roll chance 10%
		} else if ((effect >= 50.f) && modifiers.size() == 2 && roll < 10) {
			addSecondaryStat(values, pupTemplate);
		// 3rd secondary stat
		} else if ((effect >= 70.f) && modifiers.size() == 3 && roll < 10) {
			addSecondaryStat(values, pupTemplate);
		} else if ((effect >= 90.f) && modifiers.size() == 4 && roll < 10) {
			addSecondaryStat(values, pupTemplate);
		}
	}

#ifdef DEBUG_POWERUPS
	info(true) << "Starting stat updates:";
#endif // DEBUG_POWERUPS

	float lastSecondary = 0.0f;

	for (int i = 0; i < modifiers.size(); ++i) {
		PowerupStat* stat = &modifiers.get(i);

		if (stat == nullptr)
			continue;

		float modVal = (effect / maxEffect) * MAXPRIMARY;

#ifdef DEBUG_POWERUPS
		info(true) << "Iterating Mod #" << i;
#endif // DEBUG_POWERUPS

		// Primary Stat increase directly
		if (i == 0) {
			if (modVal >= MAXPRIMARY)
				modVal = MAXPRIMARY;
#ifdef DEBUG_POWERUPS
			info(true) << "Setting " << stat->getAttributeToModify() << " as primary Modifier #0 from " << stat->getValue() << " to " << modVal;
#endif // DEBUG_POWERUPS

			stat->setValue(modVal);
			lastSecondary = modVal;
			continue;
		} else if (i == 1 && (modifiers.size() > 2) && (stat->getValue() < 10.0f)) {
#ifdef DEBUG_POWERUPS
			info(true) << "1st secondary mod - " << stat->getAttributeToModify() << " is skipped for any further stat updates";
#endif // DEBUG_POWERUPS
			continue;
		}

		lastSecondary /= 2.0f;

		// Calculate mod for secondaries
		if (lastSecondary > MAXSECONDARY)
			lastSecondary = MAXSECONDARY;

#ifdef DEBUG_POWERUPS
		info(true) << "Setting stat: " << stat->getAttributeToModify() << " from " << stat->getValue() << " to " << lastSecondary;
#endif // DEBUG_POWERUPS

		stat->setValue(lastSecondary);
	}

#ifdef DEBUG_POWERUPS
	info(true) << "========== END -  PowerupObjectImplementation::updateCraftingValues ==========";
#endif // DEBUG_POWERUPS
}

float PowerupObjectImplementation::getPowerupStat(const String& attribName) const {
	for (int i = 0; i < modifiers.size(); ++i) {
		const PowerupStat* stat = &modifiers.get(i);

		if (attribName.toLowerCase() == stat->getAttributeToModify().toLowerCase()) {
			return stat->getValue() / 100.f;
		}
	}

	return 0;
}

void PowerupObjectImplementation::addPowerupStat(const String& attributeToMod, const String& name, const String& pupAttrib, float value) {
	PowerupStat newStat(attributeToMod, name, pupAttrib);
	newStat.setValue(value);

	modifiers.add(newStat);
}
