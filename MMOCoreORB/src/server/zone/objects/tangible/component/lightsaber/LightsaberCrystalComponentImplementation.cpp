/*
 * LightsaberCrystalComponentImplementation.cpp
 *
 *      Author: Katherine
 */

#include "engine/engine.h"
#include "server/zone/objects/player/sui/messagebox/SuiMessageBox.h"
#include "server/zone/objects/tangible/component/lightsaber/LightsaberCrystalComponent.h"
#include "server/zone/packets/object/ObjectMenuResponse.h"
#include "server/zone/objects/tangible/wearables/WearableContainerObject.h"
#include "server/zone/packets/scene/AttributeListMessage.h"
#include "server/zone/objects/player/PlayerObject.h"
#include "server/zone/objects/player/sui/callbacks/LightsaberCrystalTuneSuiCallback.h"
#include "server/zone/objects/tangible/weapon/WeaponObject.h"
#include "server/zone/managers/stringid/StringIdManager.h"
#include "server/zone/managers/loot/CrystalData.h"
#include "server/zone/managers/loot/LootManager.h"
#include "server/zone/ZoneServer.h"

void LightsaberCrystalComponentImplementation::initializeTransientMembers() {
	ComponentImplementation::initializeTransientMembers();

	setLoggingName("LightsaberCrystalComponent");
}

void LightsaberCrystalComponentImplementation::notifyLoadFromDatabase() {
	// Randomize item level and stats for existing crystals based on original quality value
	// TODO: Remove this on a server wipe when old variables are removed
	if (color == 31 && (minimumDamage != maximumDamage || itemLevel == 0)) {
		if (quality == POOR)
			itemLevel = 1 + System::random(38); // 1-39
		else if (quality == FAIR)
			itemLevel = 40 + System::random(29); // 40-69
		else if (quality == GOOD)
			itemLevel = 70 + System::random(29); // 70-99
		else if (quality == QUALITY)
			itemLevel = 100 + System::random(39); // 100-139
		else if (quality == SELECT)
			itemLevel = 140 + System::random(79); // 140-219
		else if (quality == PREMIUM)
			itemLevel = 220 + System::random(109); // 220-329
		else
			itemLevel = 330 + System::random(20);

		attackSpeed = 0.0;
		minimumDamage = 0;
		maximumDamage = 0;
		sacHealth = 0;
		sacAction = 0;
		sacMind = 0;
		woundChance = 0;
		forceCost = 0;
		floatForceCost = 0.0;

		generateCrystalStats();
	}

	TangibleObjectImplementation::notifyLoadFromDatabase();
}

void LightsaberCrystalComponentImplementation::generateCrystalStats() {
	ManagedReference<LootManager*> lootManager = getZoneServer()->getLootManager();

	if (lootManager == NULL)
		return;

	CrystalData* crystalData = lootManager->getCrystalData(getObjectTemplate()->getTemplateFileName());

	if (crystalData == NULL) {
		error("Unable to find crystal stats for " + getObjectTemplate()->getTemplateFileName());
		return;
	}

	int minStat = crystalData->getMinHitpoints();
	int maxStat = crystalData->getMaxHitpoints();

	setMaxCondition(getRandomizedStat(minStat, maxStat, itemLevel));

	if (color == 31) {
		int minStat = crystalData->getMinDamage();
		int maxStat = crystalData->getMaxDamage();

		damage = getRandomizedStat(minStat, maxStat, itemLevel);

		minStat = crystalData->getMinHealthSac();
		maxStat = crystalData->getMaxHealthSac();

		sacHealth = getRandomizedStat(minStat, maxStat, itemLevel);

		minStat = crystalData->getMinActionSac();
		maxStat = crystalData->getMaxActionSac();

		sacAction = getRandomizedStat(minStat, maxStat, itemLevel);

		minStat = crystalData->getMinMindSac();
		maxStat = crystalData->getMaxMindSac();

		sacMind = getRandomizedStat(minStat, maxStat, itemLevel);

		minStat = crystalData->getMinWoundChance();
		maxStat = crystalData->getMaxWoundChance();

		woundChance = getRandomizedStat(minStat, maxStat, itemLevel);

		float minFloatStat = crystalData->getMinForceCost();
		float maxFloatStat = crystalData->getMaxForceCost();

		floatForceCost = getRandomizedStat(minFloatStat, maxFloatStat, itemLevel);

		minFloatStat = crystalData->getMinAttackSpeed();
		maxFloatStat = crystalData->getMaxAttackSpeed();

		attackSpeed = Math::getPrecision(getRandomizedStat(minFloatStat, maxFloatStat, itemLevel), 2);
	}

	quality = getCrystalQuality();
}

void LightsaberCrystalComponentImplementation::validateCrystalStats() {
	ManagedReference<LootManager*> lootManager = getZoneServer()->getLootManager();

	if (lootManager == NULL)
		return;

	CrystalData* crystalData = lootManager->getCrystalData(getObjectTemplate()->getTemplateFileName());

	if (crystalData == NULL) {
		error("Unable to find crystal stats for " + getObjectTemplate()->getTemplateFileName());
		return;
	}

	int minStat = crystalData->getMinHitpoints();
	int maxStat = crystalData->getMaxHitpoints();

	if (getMaxCondition() > maxStat || getMaxCondition() < minStat)
		setMaxCondition(getRandomizedStat(minStat, maxStat, itemLevel));

	if (color == 31) {
		minStat = crystalData->getMinDamage();
		maxStat = crystalData->getMaxDamage();

		if (damage > maxStat || damage < minStat)
			damage = getRandomizedStat(minStat, maxStat, itemLevel);

		minStat = crystalData->getMinHealthSac();
		maxStat = crystalData->getMaxHealthSac();

		if (sacHealth > maxStat || sacHealth < minStat)
			sacHealth = getRandomizedStat(minStat, maxStat, itemLevel);

		minStat = crystalData->getMinActionSac();
		maxStat = crystalData->getMaxActionSac();

		if (sacAction > maxStat || sacAction < minStat)
			sacAction = getRandomizedStat(minStat, maxStat, itemLevel);

		minStat = crystalData->getMinMindSac();
		maxStat = crystalData->getMaxMindSac();

		if (sacMind > maxStat || sacMind < minStat)
			sacMind = getRandomizedStat(minStat, maxStat, itemLevel);

		minStat = crystalData->getMinWoundChance();
		maxStat = crystalData->getMaxWoundChance();

		if (woundChance > maxStat || woundChance < minStat)
			woundChance = getRandomizedStat(minStat, maxStat, itemLevel);

		float minFloatStat = crystalData->getMinForceCost();
		float maxFloatStat = crystalData->getMaxForceCost();

		if (floatForceCost > maxFloatStat || floatForceCost < minFloatStat)
			floatForceCost = getRandomizedStat(minFloatStat, maxFloatStat, itemLevel);

		minFloatStat = crystalData->getMinAttackSpeed();
		maxFloatStat = crystalData->getMaxAttackSpeed();

		if (attackSpeed > maxFloatStat || attackSpeed < minFloatStat)
			attackSpeed = Math::getPrecision(getRandomizedStat(minFloatStat, maxFloatStat, itemLevel), 2);
	}
}

int LightsaberCrystalComponentImplementation::getCrystalQuality() {
	if (itemLevel < 40)
		return POOR;
	else if (itemLevel < 70)
		return FAIR;
	else if (itemLevel < 100)
		return GOOD;
	else if (itemLevel < 140)
		return QUALITY;
	else if (itemLevel < 220)
		return SELECT;
	else if (itemLevel < 330)
		return PREMIUM;
	else
		return FLAWLESS;
}

int LightsaberCrystalComponentImplementation::getRandomizedStat(int min, int max, int itemLevel) {
	bool invertedValues = false;
	int invertedMin = min;
	int invertedMax = max;

	if (min > max) {
		int temp = min;
		min = max;
		max = temp;

		invertedValues = true;
	}

	float avgLevel = (float)(itemLevel - 60) / 220.f;

	float midLevel = min + ((max - min) * avgLevel);

	if (midLevel < min) {
		max += (midLevel - min);
		midLevel = min;
	}

	if (midLevel > max) {
		min += (midLevel - max);
		midLevel = max;
	}

	int randMin = min + System::random((int)(midLevel + 0.5f) - min);
	int randMax = (int)(midLevel + 0.5f) + System::random(max - midLevel);

	int result = randMin + System::random(randMax - randMin);

	if (invertedValues)
		result = invertedMin + (invertedMax - result);

	return result;
}

float LightsaberCrystalComponentImplementation::getRandomizedStat(float min, float max, int itemLevel) {
	bool invertedValues = false;
	float invertedMin = min;
	float invertedMax = max;

	if (min > max) {
		float temp = min;
		min = max;
		max = temp;

		invertedValues = true;
	}

	float avgLevel = (float)(itemLevel - 60) / 220.f;

	float midLevel = min + ((max - min) * avgLevel);

	if (midLevel < min) {
		max += (midLevel - min);
		midLevel = min;
	}

	if (midLevel > max) {
		min += (midLevel - max);
		midLevel = max;
	}

	float randMin = System::getMTRand()->rand(midLevel - min) + min;
	float randMax = System::getMTRand()->rand(max - midLevel) + midLevel;

	float result = System::getMTRand()->rand(randMax - randMin) + randMin;

	if (invertedValues)
		result = invertedMin + (invertedMax - result);

	return result;
}

void LightsaberCrystalComponentImplementation::fillAttributeList(AttributeListMessage* alm, CreatureObject* object) {
	TangibleObjectImplementation::fillAttributeList(alm, object);

	PlayerObject* player = object->getPlayerObject();
	if (object->hasSkill("force_title_jedi_rank_01") || player->isPrivileged()) {
		if (ownerID == 0) {
			StringBuffer str;
			str << "\\#pcontrast2 UNTUNED";
			alm->insertAttribute("crystal_owner", str);
		} else {
			alm->insertAttribute("crystal_owner", ownerName);
		}

		if (getColor() != 31) {
			StringBuffer str3;
			str3 << "@jedi_spam:saber_color_" << getColor();
			alm->insertAttribute("color", str3);
		} else {
			if (ownerID != 0 || player->isPrivileged()) {
				alm->insertAttribute("mindamage", damage);
				alm->insertAttribute("maxdamage", damage);
				alm->insertAttribute("wpn_attack_speed", attackSpeed);
				alm->insertAttribute("wpn_wound_chance", woundChance);
				alm->insertAttribute("wpn_attack_cost_health", sacHealth);
				alm->insertAttribute("wpn_attack_cost_action", sacAction);
				alm->insertAttribute("wpn_attack_cost_mind", sacMind);
				alm->insertAttribute("forcecost", (int)getForceCost());

				// For debugging
				if (player->isPrivileged()) {
					StringBuffer str;
					str << "@jedi_spam:crystal_quality_" << getQuality();
					alm->insertAttribute("challenge_level", itemLevel);
					alm->insertAttribute("crystal_quality", str);
				}
			} else {
				StringBuffer str;
				str << "@jedi_spam:crystal_quality_" << getQuality();
				alm->insertAttribute("crystal_quality", str);
			}
		}
	}
}

void LightsaberCrystalComponentImplementation::fillObjectMenuResponse(ObjectMenuResponse* menuResponse, CreatureObject* player) {
	if (ownerID == 0 && player->hasSkill("force_title_jedi_rank_01") && hasPlayerAsParent(player)) {
		String text = "@jedi_spam:tune_crystal";
		menuResponse->addRadialMenuItem(128, 3, text);
	}

	PlayerObject* ghost = player->getPlayerObject();
	if (ghost != NULL && ghost->isPrivileged()) {
		menuResponse->addRadialMenuItem(129, 3, "Staff Commands");

		if (getColor() == 31)
			menuResponse->addRadialMenuItemToRadialID(129, 130, 3, "Recalculate Stats");

		if (ownerID != 0)
			menuResponse->addRadialMenuItemToRadialID(129, 131, 3, "Untune Crystal");
	}

	ComponentImplementation::fillObjectMenuResponse(menuResponse, player);
}

int LightsaberCrystalComponentImplementation::handleObjectMenuSelect(CreatureObject* player, byte selectedID) {
	if (selectedID == 128 && player->hasSkill("force_title_jedi_rank_01") && hasPlayerAsParent(player) && ownerID == 0) {
		ManagedReference<SuiMessageBox*> suiMessageBox = new SuiMessageBox(player, SuiWindowType::TUNE_CRYSTAL);

		suiMessageBox->setPromptTitle("@jedi_spam:confirm_tune_title");
		suiMessageBox->setPromptText("@jedi_spam:confirm_tune_prompt");
		suiMessageBox->setCancelButton(true, "Cancel");
		suiMessageBox->setUsingObject(_this.getReferenceUnsafeStaticCast());
		suiMessageBox->setCallback(new LightsaberCrystalTuneSuiCallback(player->getZoneServer()));

		player->getPlayerObject()->addSuiBox(suiMessageBox);
		player->sendMessage(suiMessageBox->generateMessage());
	}

	PlayerObject* ghost = player->getPlayerObject();
	if (ghost != NULL && ghost->isPrivileged()){
		if (selectedID == 130 && getColor() == 31) {
			generateCrystalStats();
		} else if (selectedID == 131 && ownerID != 0) {
			ownerID = 0;

			String tuneName = StringIdManager::instance()->getStringId(objectName.getFullPath().hashCode()).toString();
			if (getCustomObjectName().toString().contains("(Exceptional)"))
				tuneName = tuneName + " (Exceptional)\\#.";
			else if (getCustomObjectName().toString().contains("(Legendary)"))
				tuneName = tuneName + " (Legendary)\\#.";
			else
				tuneName = tuneName + "\\#.";
		}
	}

	return 0;
}

bool LightsaberCrystalComponentImplementation::hasPlayerAsParent(CreatureObject* player) {
	ManagedReference<SceneObject*> wearableParent = getParentRecursively(SceneObjectType::WEARABLECONTAINER);
	SceneObject* inventory = player->getSlottedObject("inventory");
	SceneObject* bank = player->getSlottedObject("bank");

	// Check if crystal is inside a wearable container in bank or inventory
	if (wearableParent != NULL) {
		ManagedReference<WearableContainerObject*> wearable = cast<WearableContainerObject*>(wearableParent.get());

		if (wearable != NULL) {
			SceneObject* parentOfWearableParent = wearable->getParent().get();

			if (parentOfWearableParent == inventory || parentOfWearableParent == bank)
				return true;
		}
	} else {
		// Check if crystal is in inventory or bank
		SceneObject* thisParent = getParent().get();

		if (thisParent == inventory || thisParent == bank)
			return true;
	}
	return false;
}

void LightsaberCrystalComponentImplementation::tuneCrystal(CreatureObject* player) {
	if(!player->hasSkill("force_title_jedi_rank_01") || !hasPlayerAsParent(player)) {
		return;
	}

	if (getColor() == 31) {
		ManagedReference<PlayerObject*> ghost = player->getPlayerObject();

		if (ghost == NULL)
			return;

		int tuningCost = 100 + (quality * 75);

		if (ghost->getForcePower() <= tuningCost) {
			player->sendSystemMessage("@jedi_spam:no_force_power");
			return;
		}

		ghost->setForcePower(ghost->getForcePower() - tuningCost);
	}

	if (ownerID == 0) {
		validateCrystalStats();

		ownerID = player->getObjectID();
		ownerName = player->getDisplayedName();

		// Color code is lime green.
		String tuneName = StringIdManager::instance()->getStringId(objectName.getFullPath().hashCode()).toString();
		if (getCustomObjectName().toString().contains("(Exceptional)"))
			tuneName = "\\#00FF00" + tuneName + " (Exceptional) (tuned)\\#.";
		else if (getCustomObjectName().toString().contains("(Legendary)"))
			tuneName = "\\#00FF00" + tuneName + " (Legendary) (tuned)\\#.";
		else
			tuneName = "\\#00FF00" + tuneName + " (tuned)\\#.";

		setCustomObjectName(tuneName, true);
		player->notifyObservers(ObserverEventType::TUNEDCRYSTAL, _this.getReferenceUnsafeStaticCast(), 0);
		player->sendSystemMessage("@jedi_spam:crystal_tune_success");
	}
}

void LightsaberCrystalComponentImplementation::updateCrystal(int value){
	byte type = 0x02;
	setCustomizationVariable(type, value, true);
}

void LightsaberCrystalComponentImplementation::updateCraftingValues(CraftingValues* values, bool firstUpdate) {
	int colorMax = values->getMaxValue("color");
	int color = values->getCurrentValue("color");

	if (colorMax != 31) {
		int finalColor = Math::min(color, 11);
		setColor(finalColor);
		updateCrystal(finalColor);
	} else {
		setColor(31);
		updateCrystal(31);
	}

	generateCrystalStats();

	ComponentImplementation::updateCraftingValues(values, firstUpdate);
}

int LightsaberCrystalComponentImplementation::inflictDamage(TangibleObject* attacker, int damageType, float damage, bool destroy, bool notifyClient) {
	if (isDestroyed()) {
		return 0;
	}

	TangibleObjectImplementation::inflictDamage(attacker, damageType, damage, destroy, notifyClient);

	if (isDestroyed()) {
		ManagedReference<WeaponObject*> weapon = cast<WeaponObject*>(_this.getReferenceUnsafeStaticCast()->getParent().get()->getParent().get().get());

		if (weapon != NULL) {
			if (getColor() == 31) {
				weapon->setAttackSpeed(weapon->getAttackSpeed() - getAttackSpeed());
				weapon->setMinDamage(weapon->getMinDamage() - getDamage());
				weapon->setMaxDamage(weapon->getMaxDamage() - getDamage());
				weapon->setHealthAttackCost(weapon->getHealthAttackCost() - getSacHealth());
				weapon->setActionAttackCost(weapon->getActionAttackCost() - getSacAction());
				weapon->setMindAttackCost(weapon->getMindAttackCost() - getSacMind());
				weapon->setWoundsRatio(weapon->getWoundsRatio() - getWoundChance());
				weapon->setForceCost(weapon->getForceCost() - getForceCost());
			}

			if (getColor() != 31) {
				weapon->setBladeColor(31);
				weapon->setCustomizationVariable("/private/index_color_blade", 31, true);

				if (weapon->isEquipped()) {
					ManagedReference<CreatureObject*> parent = cast<CreatureObject*>(weapon->getParent().get().get());
					ManagedReference<SceneObject*> inventory = parent->getSlottedObject("inventory");
					inventory->transferObject(weapon, -1, true, true);
					parent->sendSystemMessage("@jedi_spam:lightsaber_no_color"); //That lightsaber can not be used until it has a color-modifying Force crystal installed.
				}
			}
		}
	}

	return 0;
}
