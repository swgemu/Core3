/*
Copyright (C) 2007 <SWGEmu>

This File is part of Core3.

This program is free software; you can redistribute
it and/or modify it under the terms of the GNU Lesser
General Public License as published by the Free Software
Foundation; either version 2 of the License,
or (at your option) any later version.

This program is distributed in the hope that it will be useful,
but WITHOUT ANY WARRANTY; without even the implied warranty of
MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.
See the GNU Lesser General Public License for
more details.

You should have received a copy of the GNU Lesser General
Public License along with this program; if not, write to
the Free Software Foundation, Inc., 51 Franklin St, Fifth Floor, Boston, MA 02110-1301 USA

Linking Engine3 statically or dynamically with other modules
is making a combined work based on Engine3.
Thus, the terms and conditions of the GNU Lesser General Public License
cover the whole combination.

In addition, as a special exception, the copyright holders of Engine3
give you permission to combine Engine3 program with free software
programs or libraries that are released under the GNU LGPL and with
code included in the standard release of Core3 under the GNU LGPL
license (or modified versions of such code, with unchanged license).
You may copy and distribute such a system following the terms of the
GNU LGPL for Engine3 and the licenses of the other code concerned,
provided that you include the source code of that other code when
and as the GNU LGPL requires distribution of source code.

Note that people who make modified versions of Engine3 are not obligated
to grant this special exception for their modified versions;
it is their choice whether to do so. The GNU Lesser General Public License
gives permission to release a modified version without this exception;
this exception also makes it possible to release a modified version
which carries forward this exception.
*/

#include "TangibleObject.h"

#include "../../managers/object/ObjectManager.h"
#include "../scene/variables/CustomizationVariables.h"
#include "server/zone/packets/object/ObjectMenuResponse.h"
#include "server/zone/packets/tangible/TangibleObjectMessage3.h"
#include "server/zone/packets/tangible/TangibleObjectMessage6.h"
#include "server/zone/packets/tangible/TangibleObjectMessage7.h"
#include "server/zone/packets/tangible/TangibleObjectDeltaMessage3.h"
#include "server/zone/packets/tangible/TangibleObjectDeltaMessage6.h"
#include "server/zone/packets/scene/AttributeListMessage.h"
#include "server/zone/templates/SharedTangibleObjectTemplate.h"
#include "server/zone/objects/creature/CreatureFlag.h"
#include "server/zone/packets/tangible/UpdatePVPStatusMessage.h"
#include "server/zone/objects/creature/CreatureObject.h"
#include "server/zone/managers/crafting/CraftingManager.h"
#include "server/zone/objects/tangible/component/Component.h"
#include "server/zone/objects/factorycrate/FactoryCrate.h"
#include "server/zone/objects/player/sessions/SlicingSession.h"

void TangibleObjectImplementation::initializeTransientMembers() {
	SceneObjectImplementation::initializeTransientMembers();

	setLoggingName("TangibleObject");
}

void TangibleObjectImplementation::loadTemplateData(SharedObjectTemplate* templateData) {
	SceneObjectImplementation::loadTemplateData(templateData);

	SharedTangibleObjectTemplate* tanoData = dynamic_cast<SharedTangibleObjectTemplate*>(templateData);

	targetable = tanoData->getTargetable();

	playerUseMask = tanoData->getPlayerUseMask();

	maxCondition = tanoData->getMaxCondition();

	useCount = tanoData->getUseCount();

	optionsBitmask = tanoData->getOptionsBitmask();
	pvpStatusBitmask = tanoData->getPvpStatusBitmask();

	sliceable = tanoData->getSliceable();

}

void TangibleObjectImplementation::sendBaselinesTo(SceneObject* player) {
	info("sending tano baselines");

	BaseMessage* tano3 = new TangibleObjectMessage3(_this);
	player->sendMessage(tano3);

	BaseMessage* tano6 = new TangibleObjectMessage6(_this);
	player->sendMessage(tano6);

	if (player->isPlayerCreature())
		sendPvpStatusTo((CreatureObject*) player);
}

void TangibleObjectImplementation::sendPvpStatusTo(CreatureObject* player) {
	uint32 newPvpStatusBitmask = pvpStatusBitmask;

	if (!(newPvpStatusBitmask & CreatureFlag::ATTACKABLE)) {
		if (isAttackableBy(player))
			newPvpStatusBitmask |= CreatureFlag::ATTACKABLE;
	}

	if (!(newPvpStatusBitmask & CreatureFlag::AGGRESSIVE)) {
		if (isAggressiveTo(player))
			newPvpStatusBitmask |= CreatureFlag::AGGRESSIVE;
	}

	BaseMessage* pvp = new UpdatePVPStatusMessage(_this, newPvpStatusBitmask);
	player->sendMessage(pvp);
}

void TangibleObjectImplementation::synchronizedUIListen(SceneObject* player, int value) {
	// Send TANO7 Baseline
	TangibleObjectMessage7* tano7 = new TangibleObjectMessage7(_this);
	player->sendMessage(tano7);
}

void TangibleObjectImplementation::synchronizedUIStopListen(SceneObject* player, int value) {

}

void TangibleObjectImplementation::setDefender(SceneObject* defender) {
	if (defender == _this)
		return;

	if (defenderList.size() == 0) {
		addDefender(defender);
		return;
	}

	ManagedReference<SceneObject*> temp = NULL;

	int i = 0;
	for (; i < defenderList.size(); i++) {
		if (defenderList.get(i) == defender) {
			if (i == 0)
				return;

			temp = defenderList.get(0);

			TangibleObjectDeltaMessage6* dtano6 = new TangibleObjectDeltaMessage6((TangibleObject*) _this);
			dtano6->startUpdate(0x01);

			defenderList.set(0, defender, dtano6, 2);
			defenderList.set(i, temp, dtano6, 0);

			dtano6->close();

			broadcastMessage(dtano6, true);

			break;
		}
	}

	if (i == defenderList.size())
		addDefender(defender);
	else
		setCombatState();
}

void TangibleObjectImplementation::addDefender(SceneObject* defender) {
	if (defender == _this)
		return;

	for (int i = 0; i < defenderList.size(); ++i) {
		if (defender == defenderList.get(i))
			return;
	}

	//info("adding defender");

	TangibleObjectDeltaMessage6* dtano6 = new TangibleObjectDeltaMessage6((TangibleObject*) _this);
	dtano6->startUpdate(0x01);

	defenderList.add(defender, dtano6);

	dtano6->close();

	broadcastMessage(dtano6, true);

	setCombatState();
}

void TangibleObjectImplementation::removeDefenders() {
	//info("removing all defenders");
	if (defenderList.size() == 0) {
		//info("no defenders in list");
		return;
	}

	TangibleObjectDeltaMessage6* dtano6 = new TangibleObjectDeltaMessage6((TangibleObject*) _this);
	dtano6->startUpdate(0x01);

	defenderList.removeAll(dtano6);

	dtano6->close();

	broadcastMessage(dtano6, true);

	//info("removed all defenders");
}

void TangibleObjectImplementation::removeDefender(SceneObject* defender) {
		//info("trying to remove defender");
	for (int i = 0; i < defenderList.size(); ++i) {
		if (defenderList.get(i) == defender) {
			info("removing defender");

			TangibleObjectDeltaMessage6* dtano6 = new TangibleObjectDeltaMessage6(_this);

			dtano6->startUpdate(0x01);

			if (defenderList.size() == 1)
				defenderList.removeAll(dtano6);
			else
				defenderList.remove(i, dtano6);

			dtano6->close();

			broadcastMessage(dtano6, true);

			//info("defender found and removed");
			break;
		}
	}

	if (defenderList.size() == 0)
		clearCombatState(false);

	//info("finished removing defender");
}

void TangibleObjectImplementation::fillAttributeList(AttributeListMessage* alm, CreatureObject* object) {
	SceneObjectImplementation::fillAttributeList(alm, object);

	if (maxCondition > 0) {
		StringBuffer cond;
		cond << (maxCondition-conditionDamage) << "/" << maxCondition;

		alm->insertAttribute("condition", cond);
	}

	alm->insertAttribute("volume", volume);
}

void TangibleObjectImplementation::setCustomizationVariable(byte type, byte value, bool notifyClient) {
	customizationVariables.setVariable(type, value);

	if (!notifyClient)
		return;

	TangibleObjectDeltaMessage3* dtano3 = new TangibleObjectDeltaMessage3(_this);
	dtano3->updateCustomizationString();
	dtano3->close();

	broadcastMessage(dtano3, true);
}

void TangibleObjectImplementation::setCustomizationVariable(const String& type, byte value, bool notifyClient) {
	customizationVariables.setVariable(type,value);

	if(!notifyClient)
		return;

	TangibleObjectDeltaMessage3* dtano3 = new TangibleObjectDeltaMessage3(_this);
	dtano3->updateCustomizationString();
	dtano3->close();

	broadcastMessage(dtano3, true);

}

void TangibleObjectImplementation::setUseCount(uint32 newUseCount, bool notifyClient) {
	if (useCount == newUseCount)
		return;

	useCount = newUseCount;

	if (useCount < 1) {

		broadcastDestroy(_this, true);

		if (parent != NULL) {
			parent->removeObject(_this, true);
		}

		destroyObjectFromDatabase(true);

		return;
	}

	if (!notifyClient)
		return;

	TangibleObjectDeltaMessage3* dtano3 = new TangibleObjectDeltaMessage3(_this);
	dtano3->setQuantity(useCount);
	dtano3->close();

	broadcastMessage(dtano3, true);
}

void TangibleObjectImplementation::decreaseUseCount(CreatureObject* player) {
	setUseCount(useCount - 1);
}

void TangibleObjectImplementation::setConditionDamage(int condDamage, bool notifyClient) {
	if (conditionDamage == condDamage)
		return;

	conditionDamage = condDamage;

	if (!notifyClient)
		return;

	TangibleObjectDeltaMessage3* dtano3 = new TangibleObjectDeltaMessage3(_this);
	dtano3->updateConditionDamage();
	dtano3->close();

	broadcastMessage(dtano3, true);
}

int TangibleObjectImplementation::inflictDamage(TangibleObject* attacker, int damageType, int damage, bool destroy, bool notifyClient) {
	int newConditionDamage = conditionDamage + damage;

	if (!destroy && newConditionDamage >= maxCondition)
		newConditionDamage = maxCondition - 1;

	setConditionDamage(newConditionDamage, notifyClient);

	if (newConditionDamage >= maxCondition)
		notifyObjectDestructionObservers(attacker, newConditionDamage);

	return 0;
}

int TangibleObjectImplementation::notifyObjectDestructionObservers(TangibleObject* attacker, int condition) {
	notifyObservers(ObserverEventType::OBJECTDESTRUCTION, attacker, condition);

	return 1;
}

int TangibleObjectImplementation::healDamage(TangibleObject* healer, int damageType, int damageToHeal, bool notifyClient) {
	int newConditionDamage = conditionDamage - damageToHeal;

	int returnValue = damageToHeal;

	if (newConditionDamage < 0)
		returnValue = damageToHeal + newConditionDamage;

	if (returnValue < 0)
		returnValue = 0;

	setConditionDamage(MAX(0, newConditionDamage), notifyClient);

	return returnValue;
}

void TangibleObjectImplementation::setCustomObjectName(const UnicodeString& name, bool notifyClient) {
	objectName.setCustomString(name);

	if (!notifyClient)
		return;

	TangibleObjectDeltaMessage3* dtano3 = new TangibleObjectDeltaMessage3(_this);
	dtano3->updateName(name);
	dtano3->close();

	broadcastMessage(dtano3, true);
}

void TangibleObjectImplementation::setOptionsBitmask(uint32 bitmask, bool notifyClient) {
	if (bitmask == optionsBitmask)
		return;

	optionsBitmask = bitmask;

	if (!notifyClient)
		return;

	TangibleObjectDeltaMessage3* dtano3 = new TangibleObjectDeltaMessage3(_this);
	dtano3->updateOptionsBitmask();
	dtano3->close();

	broadcastMessage(dtano3, true);
}

void TangibleObjectImplementation::setInitialCraftingValues(ManufactureSchematic* manufactureSchematic, int assemblySuccess) {

	if(manufactureSchematic == NULL || manufactureSchematic->getDraftSchematic() == NULL)
		return;

	ManagedReference<DraftSchematic* > draftSchematic = manufactureSchematic->getDraftSchematic();
	CraftingValues* craftingValues = manufactureSchematic->getCraftingValues();
	ManagedReference<CraftingManager* > craftingManager = getZoneServer()->getCraftingManager();

	float value, maxPercentage, currentPercentage, weightedSum;
	String itemName;

	// These 2 values are pretty standard, adding these
	itemName = "xp";
	value = float(draftSchematic->getXpAmount());
	craftingValues->addExperimentalProperty("", itemName, value, value, 0, 1);

	itemName = "complexity";
	value = manufactureSchematic->getComplexity();
	craftingValues->addExperimentalProperty("", itemName, value, value, 0, 1);

	float modifier = craftingManager->calculateAssemblyValueModifier(assemblySuccess);
	int subtitleCounter = 0;

	for (int i = 0; i < draftSchematic->getResourceWeightCount(); ++i) {

		// Grab the first weight group
		Reference<ResourceWeight* > resourceWeight = draftSchematic->getResourceWeight(i);

		// Getting the title ex: expDamage
		String experimentalTitle = resourceWeight->getExperimentalTitle();

		// Getting the subtitle ex: minDamage
		String property = resourceWeight->getPropertyName();

		weightedSum = 0;

		craftingValues->addExperimentalProperty(experimentalTitle, property,
				resourceWeight->getMinValue(), resourceWeight->getMaxValue(),
				resourceWeight->getPrecision(), resourceWeight->isFiller());

		for (int ii = 0; ii < resourceWeight->getPropertyListSize(); ++ii) {

			// Based on the script we cycle through each exp group

			// Get the type from the type/weight
			int type = (resourceWeight->getTypeAndWeight(ii) >> 4);

			// Get the calculation percentage
			float percentage = resourceWeight->getPropertyPercentage(ii);

			// add to the weighted sum based on type and percentage
			weightedSum += craftingManager->getWeightedValue(manufactureSchematic, type) * percentage;
		}

		// > 0 ensures that we don't add things when there is NaN value
		if (weightedSum > 0) {

			// This is the formula for max experimenting percentages
			maxPercentage = ((weightedSum / 10.0f) * .01f);

			// Based on the weighted sum, we can get the initial %
			currentPercentage = (craftingManager->getAssemblyPercentage(weightedSum)) * modifier;

			craftingValues->setMaxPercentage(property, maxPercentage);
			craftingValues->setCurrentPercentage(property, currentPercentage);

			subtitleCounter++;

		}
	}

	craftingValues->recalculateValues(true);

	if (applyComponentStats(manufactureSchematic)) {
		craftingValues->recalculateValues(true);
	}
}

bool TangibleObjectImplementation::applyComponentStats(ManufactureSchematic* manufactureSchematic) {

	if(manufactureSchematic == NULL || manufactureSchematic->getDraftSchematic() == NULL)
		return false;

	float max, min, currentvalue, propertyvalue;
	int precision;
	bool modified = false;
	bool hidden;
	String experimentalTitle, property;

	CraftingValues* craftingValues = manufactureSchematic->getCraftingValues();
	ManagedReference<DraftSchematic* > draftSchematic = manufactureSchematic->getDraftSchematic();

	for (int i = 0; i < manufactureSchematic->getSlotCount(); ++i) {

		Reference<IngredientSlot* > ingredientSlot = manufactureSchematic->getIngredientSlot(i);
		Reference<DraftSlot* > draftSlot = draftSchematic->getDraftSlot(i);

		if (ingredientSlot != NULL) {

			ManagedReference<TangibleObject*> tano = ingredientSlot->get();

			if (tano == NULL)
				continue;

			if (tano->isComponent()) {

				ManagedReference<Component*> component = (Component*) tano.get();

				for (int j = 0; j < component->getPropertyCount(); ++j) {

					property = component->getProperty(j); // charges

					modified = true;

					if (craftingValues->hasProperty(property) && !component->getAttributeHidden(property)) {

						max = craftingValues->getMaxValue(property);

						min = craftingValues->getMinValue(property);

						hidden = craftingValues->isHidden(property);

						currentvalue = craftingValues->getCurrentValue(property);

						propertyvalue = component->getAttributeValue(property) * draftSlot->getContribution();

						currentvalue += propertyvalue;
						min += propertyvalue;
						max += propertyvalue;

						craftingValues->setMinValue(property, min);
						craftingValues->setMaxValue(property, max);

						if (draftSlot->getCombineType() == CraftingManager::COMPONENTLINEAR) {

							craftingValues->setCurrentValue(property, currentvalue);

						} else if (draftSlot->getCombineType() == CraftingManager::COMPONENTPERCENTAGE) {

							craftingValues->setCurrentPercentage(property, currentvalue);

						}
					} else if(!component->getAttributeHidden(property)) {

						currentvalue = component->getAttributeValue(property);
						precision = component->getAttributePrecision(property);
						experimentalTitle = component->getAttributeTitle(property);

						craftingValues->addExperimentalProperty(experimentalTitle, property, currentvalue, currentvalue, precision, false);
						craftingValues->setCurrentPercentage(property, .5f);
						craftingValues->setMaxPercentage(property, 1.0f);
						craftingValues->setCurrentValue(property, currentvalue);
					}
				}
			}
		}
	}
	//craftingValues->toString();

	return modified;
}

FactoryCrate* TangibleObjectImplementation::createFactoryCrate(bool insertSelf) {

	String file;
	uint32 type = getGameObjectType();

	if(type & SceneObject::ARMOR)
		file = "object/factory/factory_crate_armor.iff";
	else if(type == SceneObject::CHEMICAL || type == SceneObject::PHARMACEUTICAL || type == SceneObject::PETMEDECINE)
		file = "object/factory/factory_crate_chemicals.iff";
	else if(type & SceneObject::CLOTHING)
		file = "object/factory/factory_crate_clothing.iff";
	else if(type == SceneObject::ELECTRONICS)
		file = "object/factory/factory_crate_electronics.iff";
	else if(type == SceneObject::FOOD || type == SceneObject::DRINK)
		file = "object/factory/factory_crate_food.iff";
	else if(type == SceneObject::FURNITURE)
		file = "object/factory/factory_crate_furniture.iff";
	else if(type & SceneObject::INSTALLATION)
		file = "object/factory/factory_crate_installation.iff";
	else if(type & SceneObject::WEAPON)
		file = "object/factory/factory_crate_weapon.iff";
	else
		file = "object/factory/factory_crate_generic_items.iff";

	ObjectManager* objectManager = ObjectManager::instance();

	FactoryCrate* crate = dynamic_cast<FactoryCrate*>(getZoneServer()->createObject(file.hashCode(), 2));

	if (crate == NULL)
		return NULL;

	crate->setOptionsBitmask(0x2100);

	if (insertSelf) {

		setOptionsBitmask(0x2100);
		updateToDatabase();

		if (parent != NULL) {
			parent->removeObject(_this, true);
		}

		crate->addObject(_this, -1, false);

	} else {

		ManagedReference<TangibleObject*> protoclone = (TangibleObject*) objectManager->cloneObject(_this);

		if (protoclone == NULL)
			return NULL;

		protoclone->setParent(NULL);
		protoclone->setOptionsBitmask(0x2100);
		protoclone->updateToDatabase();
		crate->addObject(protoclone, -1, false);
	}

	crate->setObjectName(*getObjectName());

	crate->setUseCount(1);

	crate->updateToDatabase();

	return crate;
}
