/*
 * PowerupObjectImplementation.cpp
 *
 *  Created on: march 3, 2012
 *      Author: Kyle
 */


#include "PowerupObject.h"
#include "server/zone/templates/tangible/PowerupTemplate.h"
#include "server/zone/packets/scene/AttributeListMessage.h"
#include "server/zone/objects/tangible/weapon/WeaponObject.h"

float PowerupObjectImplementation::MAXPRIMARY = 33.16;
float PowerupObjectImplementation::MAXSECONDARY = 16.33;

void PowerupObjectImplementation::fillAttributeList(AttributeListMessage* alm, CreatureObject* object) {

	TangibleObjectImplementation::fillAttributeList(alm, object);

	alm->insertAttribute("cat_pup.pup_uses", uses);

	for(int i  = 0; i < modifiers.size(); ++i) {
		PowerupStat* stat = &modifiers.get(i);
		StringBuffer val;
		val << Math::getPrecision(stat->getValue(), 2) << "%";
		alm->insertAttribute(stat->getPupAttribute(), val.toString());
	}
}

void PowerupObjectImplementation::fillWeaponAttributeList(AttributeListMessage* alm, WeaponObject* weapon) {

	alm->insertAttribute("cat_pup.pup_uses", uses);

	for(int i  = 0; i < modifiers.size(); ++i) {
		PowerupStat* stat = &modifiers.get(i);

		float value = getWeaponStat(stat->getAttributeToModify(), weapon, true);
		float valueNoPup = getWeaponStat(stat->getAttributeToModify(), weapon, false);

		String sign = "+";
		if(value < valueNoPup)
			sign = "-";
		else if(value == valueNoPup)
			sign = "";

		float pupvalue = (stat->getValue() / 100.f) * valueNoPup;

		StringBuffer val;
		val << sign << Math::getPrecision(pupvalue, 2);
		alm->insertAttribute(stat->getPupAttribute(), val.toString());
	}
}

float PowerupObjectImplementation::getWeaponStat(const String& attrib, WeaponObject* weapon, bool withPup) {

	if(attrib == "pointBlankAccuracy")
		return weapon->getPointBlankAccuracy(withPup);
	else if(attrib == "idealRange")
		return weapon->getIdealRange(withPup);
	else if(attrib == "maxRange")
		return weapon->getMaxRange(withPup);
	else if(attrib == "idealAccuracy")
		return weapon->getIdealAccuracy(withPup);
	else if(attrib == "maxRangeAccuracy")
		return weapon->getMaxRangeAccuracy(withPup);
	else if(attrib == "attackSpeed")
		return weapon->getAttackSpeed(withPup);
	else if(attrib == "maxDamage")
		return weapon->getMaxDamage(withPup);
	else if(attrib == "minDamage")
		return weapon->getMinDamage(withPup);
	else if(attrib == "woundsRatio")
		return weapon->getWoundsRatio(withPup);
	else if(attrib == "damageRadius")
		return weapon->getDamageRadius(withPup);
	else if(attrib == "healthAttackCost")
		return weapon->getHealthAttackCost(withPup);
	else if(attrib == "actionAttackCost")
		return weapon->getActionAttackCost(withPup);
	else if(attrib == "mindAttackCost")
		return weapon->getMindAttackCost(withPup);

	return 0;
}

void PowerupObjectImplementation::updateCraftingValues(CraftingValues* values, bool firstUpdate) {
	/// effect 1-100

	Reference<PowerupTemplate*> pup = cast<PowerupTemplate*>(templateObject.get());
	if(pup == NULL) {
		return;
	}

	if(firstUpdate) {

		String key;
		String value;

		if(pup->hasPrimaryAttribute()) {
			PowerupStat stat = pup->getRandomPrimaryAttribute();
			modifiers.add(stat);

			StringBuffer name;
			name << "A " << stat.getName() << " " << pup->getBaseName();

			setCustomObjectName(name.toString(), true);
		}

		type = pup->getType().toLowerCase();
		uses = System::random(50) + 50;

	} else {

		if(pup->hasSecondaryAttribute()) {

			PowerupStat stat = pup->getRandomSecondaryAttribute();

			if(System::random(2) == 1) {
				for(int i = 0; i < modifiers.size(); ++i) {
					if(stat == modifiers.get(i))  {
						return;
					}
				}

				if(modifiers.size() == 1) {
					StringBuffer name;
					name << getCustomObjectName().toString() << " of " << stat.getName();

					setCustomObjectName(name.toString(), true);
				}

				modifiers.add(stat);
			}
		}
	}

	float val = values->getCurrentValue("effect");

	for(int i  = 0; i < modifiers.size(); ++i) {
		PowerupStat* stat = &modifiers.get(i);

		// Primary Stat always increases
		if(i == 0) {
			stat->setValue((val / values->getMaxValue("effect")) * MAXPRIMARY);
			continue;
		}

		// First secondary stat has weird rules
		if(i == 1) {

			/// If there is only 1 secondary stat, it increases as expected
			if(modifiers.size() == 2) {

				stat->setValue((val / values->getMaxValue("effect")) * MAXSECONDARY);
				continue;

			/// If there are more than 1 secondary stat, and the values
			/// is less than 10, the first secondary stat doesn't increase
			} else if(modifiers.size() >= 2 && stat->getValue() < 10) {

				continue;
			}
		}

		/// It seems like we divide the change in values between the
		/// Remaining stats
		float statsLeft = modifiers.size() - i;

		float newValue = (val / values->getMaxValue("effect")) * MAXSECONDARY;
		float valueChange = (newValue - stat->getValue()) / statsLeft;

		stat->setValue(stat->getValue() + valueChange);
	}
}

float PowerupObjectImplementation::getPowerupStat(const String& attribName) {

	for(int i = 0; i < modifiers.size(); ++i) {
		PowerupStat* stat = &modifiers.get(i);

		if(attribName.toLowerCase() ==
				stat->getAttributeToModify().toLowerCase()) {

			return stat->getValue() / 100.f;
		}
	}

	return 0;
}
