/*
 * AiAgentImplementation.cpp
 *
 *  Created on: 13/07/2010
 *      Author: victor
 */

#include <engine/core/ManagedReference.h>
#include <server/zone/CloseObjectsVector.h>
#include <engine/util/u3d/Vector3.h>
#include <system/lang/IllegalArgumentException.h>
#include <system/lang/ref/Reference.h>
#include <system/lang/String.h>
#include <system/lang/StringBuffer.h>
#include <system/lang/System.h>
#include <system/lang/Time.h>
#include <system/thread/Locker.h>
#include <system/thread/Mutex.h>
#include <system/thread/ReadLocker.h>
#include <system/util/SortedVector.h>
#include <system/util/Vector.h>
#include <system/util/VectorMap.h>

#include "server/zone/objects/creature/ai/bt/Behavior.h"
#include "server/zone/managers/objectcontroller/ObjectController.h"
#include "server/zone/managers/creature/CreatureManager.h"
#include "server/zone/managers/creature/PetManager.h"
#include "server/zone/managers/planet/PlanetManager.h"
#include "server/zone/managers/reaction/ReactionManager.h"
#include "server/zone/objects/cell/CellObject.h"
#include "server/zone/objects/creature/ai/AiAgent.h"
#include "server/zone/objects/creature/ai/Creature.h"
#include "server/zone/objects/creature/conversation/ConversationObserver.h"
#include "server/zone/objects/creature/commands/CombatQueueCommand.h"
#include "server/zone/objects/intangible/PetControlDevice.h"
#include "server/zone/objects/player/PlayerObject.h"
#include "server/zone/objects/tangible/weapon/WeaponObject.h"
#include "server/zone/Zone.h"
#include "server/zone/ZoneServer.h"
#include "server/zone/managers/collision/CollisionManager.h"
#include "server/zone/managers/collision/PathFinderManager.h"
#include "server/zone/managers/combat/CombatManager.h"
#include "server/zone/managers/components/ComponentManager.h"
#include "server/zone/managers/conversation/ConversationManager.h"
#include "server/zone/managers/creature/AiMap.h"
#include "server/zone/managers/creature/CreatureTemplateManager.h"
#include "server/zone/managers/faction/FactionManager.h"
#include "server/zone/managers/gcw/GCWManager.h"
#include "server/zone/managers/name/NameManager.h"
#include "server/zone/managers/stringid/StringIdManager.h"
#include "server/zone/packets/object/StartNpcConversation.h"
#include "server/zone/packets/scene/AttributeListMessage.h"
#include "server/zone/packets/scene/LightUpdateTransformMessage.h"
#include "server/zone/packets/scene/LightUpdateTransformWithParentMessage.h"
#include "server/zone/packets/scene/UpdateTransformMessage.h"
#include "server/zone/packets/scene/UpdateTransformWithParentMessage.h"
#include "server/zone/objects/creature/ai/CreatureTemplate.h"
#include "templates/mobile/MobileOutfit.h"
#include "templates/mobile/MobileOutfitGroup.h"
#include "templates/SharedObjectTemplate.h"
#include "server/zone/objects/player/FactionStatus.h"
#include "templates/params/ObserverEventType.h"
#include "server/zone/objects/scene/variables/DeltaVector.h"
#include "server/zone/objects/scene/WorldCoordinates.h"
#include "server/zone/objects/tangible/threat/ThreatMap.h"
#include "templates/params/creature/CreatureAttribute.h"
#include "templates/params/creature/CreatureFlag.h"
#include "templates/params/creature/CreaturePosture.h"
#include "templates/params/creature/CreatureState.h"
#include "server/zone/objects/creature/damageovertime/DamageOverTimeList.h"
#include "server/zone/objects/creature/ai/events/AiMoveEvent.h"
#include "server/zone/objects/creature/ai/events/AiThinkEvent.h"
#include "server/zone/objects/creature/events/CamoTask.h"
#include "server/zone/objects/creature/events/DespawnCreatureOnPlayerDissappear.h"
#include "server/zone/objects/creature/events/DespawnCreatureTask.h"
#include "server/zone/objects/creature/events/RespawnCreatureTask.h"
#include "server/zone/objects/creature/ai/PatrolPoint.h"
#include "server/zone/objects/creature/ai/PatrolPointsVector.h"
#include "server/zone/objects/creature/ai/variables/CreatureAttackMap.h"
#include "server/zone/objects/creature/ai/variables/CurrentFoundPath.h"
#include "server/zone/managers/creature/SpawnObserver.h"
#include "server/zone/managers/creature/DynamicSpawnObserver.h"
#include "server/zone/packets/ui/CreateClientPathMessage.h"
#include "server/zone/objects/staticobject/StaticObject.h"
#include "server/zone/objects/building/BuildingObject.h"
#include "server/zone/objects/transaction/TransactionLog.h"
#include "server/chat/ChatManager.h"

//#define DEBUG_PATHING
//#define DEBUG
//#define SHOW_NEXT_POSITION

void AiAgentImplementation::loadTemplateData(SharedObjectTemplate* templateData) {
	CreatureObjectImplementation::loadTemplateData(templateData);
}

int AiAgentImplementation::calculateAttackMinDamage(int level) {
	int minDmg = Math::max(getDamageMin(), 20 + (level * 5));
	if (petDeed != nullptr) {
		minDmg = petDeed->getMinDamage();
		if (level < petDeed->getLevel()) {
			// reduce by level range
			float percent = (float)level/(float)petDeed->getLevel();
			minDmg *= percent;
		}
	}
	if (isDroidObject()) {
		minDmg = getDamageMin();
	}
	return minDmg;
}

int AiAgentImplementation::calculateAttackMaxDamage(int level) {
	int dmg = Math::max(getDamageMax(), calculateAttackMinDamage(level) * 2);
	if (petDeed != nullptr) {
		dmg = petDeed->getMaxDamage();
		if (level < petDeed->getLevel()) {
			float percent = (float)level/(float)petDeed->getLevel();
			dmg *= percent;
		}
	}
	if (isDroidObject()) {
		dmg = getDamageMax();
	}
	return dmg;
}

float AiAgentImplementation::calculateAttackSpeed(int level) {
	float speed = 3.5f - ((float)level / 100.f);
	return speed;
}

void AiAgentImplementation::loadTemplateData(CreatureTemplate* templateData) {
	npcTemplate = templateData;

	setPvpStatusBitmask(npcTemplate->getPvpBitmask());
	if (npcTemplate->getPvpBitmask() == 0)
		closeobjects = nullptr;

	optionsBitmask = npcTemplate->getOptionsBitmask();
	creatureBitmask = npcTemplate->getCreatureBitmask();

	convoTemplateCRC = npcTemplate->getConversationTemplate();

	level = getTemplateLevel();

	planetMapCategory = npcTemplate->getPlanetMapCategory();

	if (getHueValue() == -1 && npcTemplate->getTotalHues() > 0) {
		int randHue = npcTemplate->getRandomHue();
		setHue(randHue);
	}

	loadWeaponTemplateData();
	setupAttackMaps();

	int ham = 0;
	baseHAM.removeAll();
	if (petDeed == nullptr) {
		for (int i = 0; i < 9; ++i) {
			if (i % 3 == 0) {
				ham = System::random(getHamMaximum() - getHamBase()) + getHamBase();
				if (isDroidObject() && isPet())
					ham = getHamMaximum();
				baseHAM.add(ham);
			} else
				baseHAM.add(ham/10);
		}
	} else {
		int health = petDeed->getHealth();
		baseHAM.add(health);
		baseHAM.add(health/10);
		baseHAM.add(health/10);
		int action = petDeed->getAction();
		baseHAM.add(action);
		baseHAM.add(action/10);
		baseHAM.add(action/10);
		int mind = petDeed->getMind();
		baseHAM.add(mind);
		baseHAM.add(mind/10);
		baseHAM.add(mind/10);
	}

	hamList.removeAll();
	for (int i = 0; i < 9; ++i) {
		hamList.add(baseHAM.get(i));
	}

	maxHamList.removeAll();
	for (int i = 0; i < 9; ++i) {
		maxHamList.add(baseHAM.get(i));
	}

	objectName = npcTemplate->getObjectName();

	if (npcTemplate->getRandomNameType() != NameManagerType::TAG) {
		NameManager* nm = server->getNameManager();

		int templSpecies = getSpecies();

		if (!npcTemplate->getRandomNameTag()) {
			setCustomObjectName(nm->makeCreatureName(npcTemplate->getRandomNameType(), templSpecies), false);
		} else {
			String newName = nm->makeCreatureName(npcTemplate->getRandomNameType(), templSpecies);
			newName += " (";

			if (objectName == "")
				newName += templateData->getCustomName();
			else
				newName += StringIdManager::instance()->getStringId(objectName.getFullPath().hashCode()).toString();

			newName += ")";
			setCustomObjectName(newName, false);
		}
	} else {
		setCustomObjectName(templateData->getCustomName(), false);
	}

	setHeight(templateData->getScale(), false);

	String currentLogName = getLoggingName();

	if (!currentLogName.contains(npcTemplate->getTemplateName())) {
		StringBuffer logName;
		logName << getLoggingName() << "[" << npcTemplate->getTemplateName() << "]";

		setLoggingName(logName.toString());

		// Check for template level logging setting
		StringBuffer configName;
		configName << "Core3.AiAgent." << npcTemplate->getTemplateName() << ".LogLevel";

		auto templateLogLevel = ConfigManager::instance()->getInt(configName.toString(), -1);

		if (templateLogLevel >= 0) {
			setLogLevel(static_cast<Logger::LogLevel>(templateLogLevel));
		}

		debug() << "loadTemplateData(" << npcTemplate->getTemplateName() << ")";
	}

	String factionString = npcTemplate->getFaction();

	if (!factionString.isEmpty() && (factionString == "imperial" || factionString == "rebel")) {
		setFaction(factionString.hashCode());
	}

	if (!loadedOutfit) {
		loadedOutfit = true;
		String outfit = npcTemplate->getOutfit();

		if (!outfit.isEmpty()) {
			MobileOutfitGroup* group = CreatureTemplateManager::instance()->getMobileOutfitGroup(outfit);

			if (group != nullptr) {
				Vector<MobileOutfit>* outfits = group->getOutfits();

				int num = System::random(outfits->size() - 1);

				if (num > -1) {
					MobileOutfit* clothes = &outfits->get(num);

					Vector<OutfitTangibleObject>* objects = clothes->getObjects();

					for (int i = 0; i < objects->size(); ++i) {
						OutfitTangibleObject* obj = &objects->get(i);

						String templ = obj->getObjectTemplate();

						ManagedReference<TangibleObject*> tano = (getZoneServer()->createObject(templ.hashCode(), getPersistenceLevel())).castTo<TangibleObject*>();

						if (tano != nullptr) {
							Locker objLocker(tano);

							VectorMap<String, uint8>* cust = obj->getCustomizationVariables();

							for (int j = 0; j < cust->size(); ++j) {
								tano->setCustomizationVariable(cust->elementAt(j).getKey(), cust->elementAt(j).getValue());
							}

							if (!transferObject(tano, 4, false) && tano->isPersistent()) {
								tano->destroyObjectFromDatabase(true);
							}
						}

					}
				}
			} else {
				error("null outfit group " + outfit);
			}
		}
	}

	String conTemp = npcTemplate->getContainerComponentTemplate();
	if (!conTemp.isEmpty()) {
		containerComponent = cast<ContainerComponent*>(ComponentManager::instance()->getComponent<SceneObjectComponent*>(conTemp));
	}

	if (!isPet() && isNpc() && getMoodID() == 0 && System::random(50) < 15) {
		ZoneServer* zoneServer = asAiAgent()->getZoneServer();

		if (zoneServer != nullptr) {
			ChatManager* chatManager = zoneServer->getChatManager();

			if (chatManager != nullptr) {
				unsigned int id = chatManager->getRandomMoodID();

				setMood(id);
			}
		}
	}
}

void AiAgentImplementation::loadWeaponTemplateData() {
	if (npcTemplate == nullptr) {
		Logger::console.info(true) << __FILE__ << ":" << __LINE__ << ":" << __FUNCTION__ << ": " << *_this.getReferenceUnsafeStaticCast();
		return;
	}

	float minDmg = npcTemplate->getDamageMin();
	float maxDmg = npcTemplate->getDamageMax();
	float speed = calculateAttackSpeed(level);

	float globalSpeedOverride = CreatureTemplateManager::instance()->getGlobalAttackSpeedOverride();
	float customSpeed = npcTemplate->getAttackSpeed();

	if (globalSpeedOverride > 0.0f)
		speed = globalSpeedOverride;
	else if (customSpeed > 0.0f)
		speed = customSpeed;

	bool allowedWeapon = true;

	if (petDeed != nullptr) {
		minDmg = petDeed->getMinDamage();
		maxDmg = petDeed->getMaxDamage();
		allowedWeapon = petDeed->getRanged();
	}

	Reference<WeaponObject*> defaultWeap = asCreatureObject()->getSlottedObject("default_weapon").castTo<WeaponObject*>();

	if (defaultWeap != nullptr) {
		defaultWeapon = defaultWeap;
		// set the damage of the default weapon
		defaultWeapon->setMinDamage(minDmg);
		defaultWeapon->setMaxDamage(maxDmg);

		if (petDeed != nullptr) {
			defaultWeapon->setAttackSpeed(petDeed->getAttackSpeed());
		} else if (isPet()) {
			defaultWeapon->setAttackSpeed(speed);
		}

		primaryWeapon = defaultWeapon;
	}

	String primaryWeap = npcTemplate->getPrimaryWeapon();
	uint32 primaryWeapHash = primaryWeap.hashCode();

	if (primaryWeapHash != STRING_HASHCODE("unarmed") && primaryWeapHash != STRING_HASHCODE("none")) {
		uint32 weaponCRC = 0;

		if (primaryWeap.indexOf(".iff") != -1) {
			weaponCRC = primaryWeap.hashCode();
		} else {
			const Vector<String>& primaryTemplates = CreatureTemplateManager::instance()->getWeapons(primaryWeap);

			if (primaryTemplates.size() > 0) {
				String& weaponTemplate = primaryTemplates.get(System::random(primaryTemplates.size() - 1));
				weaponCRC = weaponTemplate.hashCode();
			}
		}

		if (weaponCRC != 0)
			primaryWeapon = createWeapon(weaponCRC, true);
	}

	String secondaryWeap = npcTemplate->getSecondaryWeapon();
	uint32 secondaryWeapHash = secondaryWeap.hashCode();

	if (secondaryWeapHash == STRING_HASHCODE("unarmed")) {
		secondaryWeapon = defaultWeapon;
	} else if (secondaryWeapHash != STRING_HASHCODE("none")) {
		uint32 weaponCRC = 0;

		if (secondaryWeap.indexOf(".iff") != -1) {
			weaponCRC = primaryWeap.hashCode();
		} else {
			const Vector<String>& secondaryTemplates = CreatureTemplateManager::instance()->getWeapons(secondaryWeapHash);

			if (secondaryTemplates.size() > 0) {
				String& weaponTemplate = secondaryTemplates.get(System::random(secondaryTemplates.size() - 1));
				weaponCRC = weaponTemplate.hashCode();
			}
		}

		if (weaponCRC != 0)
			secondaryWeapon = createWeapon(weaponCRC, false);
	}

	String thrownWeap = npcTemplate->getThrownWeapon();

	if (thrownWeap != "") {
		uint32 weaponCRC = 0;

		const Vector<String>& thrownTemplates = CreatureTemplateManager::instance()->getWeapons(thrownWeap.hashCode());

		if (thrownTemplates.size() > 0) {
			String& weaponTemplate = thrownTemplates.get(System::random(thrownTemplates.size() - 1));
			weaponCRC = weaponTemplate.hashCode();
		}

		if (weaponCRC != 0) {
			thrownWeapon = createWeapon(weaponCRC, false);
		}
	}
}

WeaponObject* AiAgentImplementation::createWeapon(uint32 templateCRC, bool primaryWeapon) {
	ZoneServer* zoneServer = getZoneServer();

	if (zoneServer == nullptr)
		return nullptr;

	ObjectController* objectController = zoneServer->getObjectController();

	if (objectController == nullptr)
		return nullptr;

	SceneObject* inventory = asAiAgent()->getSlottedObject("inventory");

	if (inventory == nullptr)
		return nullptr;

	WeaponObject* newWeapon = nullptr;

	if (templateCRC == STRING_HASHCODE("none")) {
		if (primaryWeapon) {
			newWeapon = getDefaultWeapon();
		} else {
			return nullptr;
		}
	} else if (templateCRC == STRING_HASHCODE("unarmed")) {
		newWeapon = getDefaultWeapon();
	} else {
		newWeapon = (zoneServer->createObject(templateCRC, getPersistenceLevel())).castTo<WeaponObject*>();
	}

	float minDmg = npcTemplate->getDamageMin();
	float maxDmg = npcTemplate->getDamageMax();
	float speed = calculateAttackSpeed(level);

	float globalSpeedOverride = CreatureTemplateManager::instance()->getGlobalAttackSpeedOverride();
	float customSpeed = npcTemplate->getAttackSpeed();

	if (globalSpeedOverride > 0.0f)
		speed = globalSpeedOverride;
	else if (customSpeed > 0.0f)
		speed = customSpeed;

	bool allowedWeapon = true;

	if (petDeed != nullptr) {
		minDmg = petDeed->getMinDamage();
		maxDmg = petDeed->getMaxDamage();
	}

	if (newWeapon != nullptr) {
		float mod = 1 - (0.1 * newWeapon->getArmorPiercing());
		newWeapon->setMinDamage(minDmg * mod);
		newWeapon->setMaxDamage(maxDmg * mod);

		SharedWeaponObjectTemplate* weaoTemp = cast<SharedWeaponObjectTemplate*>(newWeapon->getObjectTemplate());

		if (weaoTemp != nullptr && weaoTemp->getPlayerRaces()->size() > 0) {
			newWeapon->setAttackSpeed(speed);
		} else if (petDeed != nullptr) {
			newWeapon->setAttackSpeed(petDeed->getAttackSpeed());
		}

		if (newWeapon != defaultWeapon) {
			if (inventory->transferObject(newWeapon, -1, false, true))
				inventory->broadcastObject(newWeapon, true);
		}
	}

	return newWeapon;
}

void AiAgentImplementation::setupAttackMaps() {
	primaryAttackMap = nullptr;
	secondaryAttackMap = nullptr;
	defaultAttackMap = nullptr;

	ZoneServer* zoneServer = getZoneServer();

	if (zoneServer == nullptr)
		return;

	ObjectController* objectController = zoneServer->getObjectController();

	if (objectController == nullptr)
		return;

	const CreatureAttackMap* attackMap;

	if (petDeed != nullptr)
		attackMap = petDeed->getAttacks();
	else
		attackMap = npcTemplate->getPrimaryAttacks();

	Reference<WeaponObject*> defaultWeapon = asAiAgent()->getDefaultWeapon();
	defaultAttackMap = new CreatureAttackMap();
	primaryAttackMap = new CreatureAttackMap();
	secondaryAttackMap = new CreatureAttackMap();

	for (int i = 0; i < attackMap->size(); i++) {
		const CombatQueueCommand* attack = cast<const CombatQueueCommand*>(objectController->getQueueCommand(attackMap->getCommand(i)));

		if (attack == nullptr)
			continue;

		if (primaryWeapon != nullptr && (attack->getWeaponType() & primaryWeapon->getWeaponBitmask())) {
			primaryAttackMap->add(attackMap->get(i));
		}

		if (defaultWeapon != nullptr && (attack->getWeaponType() & defaultWeapon->getWeaponBitmask())) {
			defaultAttackMap->add(attackMap->get(i));
		}
	}

	if (petDeed == nullptr) {
		attackMap = npcTemplate->getSecondaryAttacks();

		for (int i = 0; i < attackMap->size(); i++) {
			const CombatQueueCommand* attack = cast<const CombatQueueCommand*>(objectController->getQueueCommand(attackMap->getCommand(i)));

			if (attack == nullptr)
				continue;

			if (secondaryWeapon != nullptr && (attack->getWeaponType() & secondaryWeapon->getWeaponBitmask())) {
				secondaryAttackMap->add(attackMap->get(i));

			}

			if (defaultWeapon != nullptr && (attack->getWeaponType() & defaultWeapon->getWeaponBitmask())) {
				defaultAttackMap->add(attackMap->get(i));
			}
		}
	}

	// if we didn't get any attacks or the weapon is nullptr, drop the reference to the attack maps
	if (defaultAttackMap != nullptr && defaultAttackMap->isEmpty())
		defaultAttackMap = nullptr;

	if (primaryAttackMap != nullptr && primaryAttackMap->isEmpty())
		primaryAttackMap = nullptr;

	if (secondaryAttackMap != nullptr && secondaryAttackMap->isEmpty())
		secondaryAttackMap = nullptr;

	attackMap = nullptr;
}

void AiAgentImplementation::unequipWeapons() {
	if (currentWeapon == nullptr) {
		currentWeapon = defaultWeapon;
		return;
	}

	SceneObject* inventory = asAiAgent()->getSlottedObject("inventory");

	if (inventory == nullptr)
		return;

	if (currentWeapon == defaultWeapon)
		return;

	ZoneServer* zoneServer = getZoneServer();

	if (zoneServer == nullptr)
		return;

	ObjectController* objectController = zoneServer->getObjectController();

	if (objectController == nullptr)
		return;

	objectController->transferObject(currentWeapon, inventory, -1, true, true);

	currentWeapon = defaultWeapon;
}

void AiAgentImplementation::equipPrimaryWeapon() {
	if (primaryWeapon == nullptr || currentWeapon == primaryWeapon)
		return;

	unequipWeapons();

	if (primaryWeapon == defaultWeapon) {
		currentWeapon = defaultWeapon;
	} else {
		transferObject(primaryWeapon, 4, false);
		broadcastObject(primaryWeapon, false);
		currentWeapon = primaryWeapon;
	}
}

void AiAgentImplementation::equipSecondaryWeapon() {
	if (secondaryWeapon == nullptr || currentWeapon == secondaryWeapon)
		return;

	unequipWeapons();

	if (secondaryWeapon == defaultWeapon) {
		currentWeapon = defaultWeapon;
	} else {
		transferObject(secondaryWeapon, 4, false);
		broadcastObject(secondaryWeapon, false);
		currentWeapon = secondaryWeapon;
	}
}

void AiAgentImplementation::setLevel(int lvl, bool randomHam) {
	if (lvl <= 0)
		return;

	CreatureObjectImplementation::setLevel(lvl);

	level = lvl;

	if (npcTemplate == nullptr) {
		return;
	}

	int baseLevel = getTemplateLevel();

	if (baseLevel == lvl)
		return;

	float minDmg = calculateAttackMinDamage(baseLevel);
	float maxDmg = calculateAttackMaxDamage(baseLevel);
	float speed = calculateAttackSpeed(lvl);

	float globalSpeedOverride = CreatureTemplateManager::instance()->getGlobalAttackSpeedOverride();
	float customSpeed = npcTemplate->getAttackSpeed();

	if (globalSpeedOverride > 0.0f)
		speed = globalSpeedOverride;
	else if (customSpeed > 0.0f)
		speed = customSpeed;

	float ratio = ((float)lvl) / (float)baseLevel;

	minDmg *= ratio;
	maxDmg *= ratio;

	if (primaryWeapon != nullptr) {
		float mod = 1 - 0.1*primaryWeapon->getArmorPiercing();
		primaryWeapon->setMinDamage(minDmg * mod);
		primaryWeapon->setMaxDamage(maxDmg * mod);

		SharedWeaponObjectTemplate* weaoTemp = cast<SharedWeaponObjectTemplate*>(primaryWeapon->getObjectTemplate());
		if (weaoTemp != nullptr && weaoTemp->getPlayerRaces()->size() > 0) {
			primaryWeapon->setAttackSpeed(speed);
		} else if (petDeed != nullptr) {
			primaryWeapon->setAttackSpeed(petDeed->getAttackSpeed());
		}
	}

	if (secondaryWeapon != nullptr) {
		float mod = 1 - 0.1*secondaryWeapon->getArmorPiercing();
		secondaryWeapon->setMinDamage(minDmg * mod);
		secondaryWeapon->setMaxDamage(maxDmg * mod);

		SharedWeaponObjectTemplate* weaoTemp = cast<SharedWeaponObjectTemplate*>(secondaryWeapon->getObjectTemplate());
		if (weaoTemp != nullptr && weaoTemp->getPlayerRaces()->size() > 0) {
			secondaryWeapon->setAttackSpeed(speed);
		} else if (petDeed != nullptr) {
			secondaryWeapon->setAttackSpeed(petDeed->getAttackSpeed());
		}
	}

	Reference<WeaponObject*> defaultWeapon = asAiAgent()->getDefaultWeapon();
	if (defaultWeapon != nullptr) {
		defaultWeapon->setMinDamage(minDmg);
		defaultWeapon->setMaxDamage(maxDmg);
		if(petDeed != nullptr)
			defaultWeapon->setAttackSpeed(petDeed->getAttackSpeed());
		else if(isPet())
			defaultWeapon->setAttackSpeed(speed);
	}

	int baseHamMax = ((float)getHamMaximum()) * ratio;
	int baseHam = ((float)getHamBase()) * ratio;

	int ham = 0;

	for (int i = 0; i < 9; ++i) {
		if (i % 3 == 0) {
			if (randomHam)
				ham = System::random(baseHamMax - baseHam) + baseHam;
			else
				ham = ((baseHamMax - baseHam) / 2) + baseHam;

			setBaseHAM(i, ham);
		} else
			setBaseHAM(i, ham / 100);
	}

	for (int i = 0; i < 9; ++i) {
		setHAM(i, baseHAM.get(i));
	}

	for (int i = 0; i < 9; ++i) {
		setMaxHAM(i, baseHAM.get(i));
	}
}

void AiAgentImplementation::initializeTransientMembers() {
	CreatureObjectImplementation::initializeTransientMembers();

	auto aiLogLevel = ConfigManager::instance()->getInt("Core3.AiAgent.LogLevel", LogLevel::WARNING);

	if (aiLogLevel >= 0) {
		// Files should end up in: log/ai/YYYY-MM-DD/HH-MM/oid/AiAgent-{timestamp}-{oid}.log
		Time now;
		StringBuffer logFilename;
		logFilename << "log/ai/"
			<< now.getFormattedTime("%Y-%m-%d/%H-%M")
			<< "/" << getObjectID()
			<< "/AiAgent-" << now.getTime() << "-" << getObjectID() << ".log";

		setFileLogger(logFilename.toString(), false, false);
		setLogSynchronized(true);
		setLogToConsole(false);
		setGlobalLogging(false);
		setLogLevel(static_cast<Logger::LogLevel>(aiLogLevel));
	} else {
		setLogLevel(LogLevel::ERROR);
		setGlobalLogging(true);
	}

	setLoggingName("AiAgent");

	// Handling of old pets on new AI
	if (controlDevice != nullptr) {
		if (npcTemplate == nullptr) {
			// Old pets with no templates have to be destroyed
			TransactionLog trx(TrxCode::SERVERDESTROYOBJECT, asAiAgent(), controlDevice.get());

			ManagedReference<CreatureObject*> linkedCreature = getLinkedCreature().get();
			if (linkedCreature != nullptr) {
				trx.addState("Owner Name: ", linkedCreature->getFirstName());
				trx.addState("Owner ID", linkedCreature->getObjectID());
			}

			trx.commit();
			destroyObjectFromDatabase();
			controlDevice.get()->destroyObjectFromDatabase();
			return;
		} else if (!(getOptionsBitmask() & OptionBitmask::AIENABLED)) {
			Logger::console.info(true) << __FILE__ << ":" << __LINE__ << ":" << __FUNCTION__ << ": " << *_this.getReferenceUnsafeStaticCast();
			loadTemplateData(npcTemplate);
		}

		if (defaultWeapon == nullptr)
			loadWeaponTemplateData();
	}

	setAITemplate();

	if (npcTemplate != nullptr)
		setupAttackMaps();

	rescheduleTrackingTask();
}

void AiAgentImplementation::notifyLoadFromDatabase() {
	CreatureObjectImplementation::notifyLoadFromDatabase();

	if (npcTemplate != nullptr && convoTemplateCRC != 0) {
		ConversationTemplate* conversationTemplate = CreatureTemplateManager::instance()->getConversationTemplate(convoTemplateCRC);

		if (conversationTemplate == nullptr) {
			uint64 tempCRC = npcTemplate->getConversationTemplate();

			if (convoTemplateCRC != tempCRC)
				convoTemplateCRC = tempCRC;
		}
	}
}

void AiAgentImplementation::notifyPositionUpdate(QuadTreeEntry* entry) {
	CreatureObjectImplementation::notifyPositionUpdate(entry);

	SceneObject* object = static_cast<SceneObject*>(entry);

	CreatureObject* creo = object->asCreatureObject();
}

void AiAgentImplementation::doRecovery(int latency) {
	if (isDead() || getZoneUnsafe() == nullptr) {
		blackboard.removeAll();
		return;
	}

	activateHAMRegeneration(latency);
	activateStateRecovery();
	activatePostureRecovery();

	// we only want to activate recovery if we need to -- it will restart when we need it
	if (defenderList.size() > 0 || damageOverTimeList.hasDot()
			|| getHAM(CreatureAttribute::HEALTH) < getMaxHAM(CreatureAttribute::HEALTH)
			|| getHAM(CreatureAttribute::ACTION) < getMaxHAM(CreatureAttribute::ACTION)
			|| getHAM(CreatureAttribute::MIND) < getMaxHAM(CreatureAttribute::MIND)
			|| getWounds(CreatureAttribute::CONSTITUTION) > 0 || getWounds(CreatureAttribute::STRENGTH) > 0
			|| getWounds(CreatureAttribute::QUICKNESS) > 0 || getWounds(CreatureAttribute::STAMINA) > 0
			|| getWounds(CreatureAttribute::FOCUS) > 0 || getWounds(CreatureAttribute::WILLPOWER) > 0)
		activateRecovery();
}

bool AiAgentImplementation::selectSpecialAttack() {
	Reference<WeaponObject*> strongWeapon = thrownWeapon;

	if (strongWeapon != nullptr && System::random(100) > 95) {
		Locker locker(strongWeapon);

		Reference<SceneObject*> followCopy = getFollowObject().get();

		if (followCopy != nullptr) {
			auto targetID = followCopy->getObjectID();
			Reference<AiAgent*> strongAiAgent = asAiAgent();

			Core::getTaskManager()->executeTask([strongAiAgent, targetID, strongWeapon] () {
				Locker lock(strongAiAgent);

				if (strongAiAgent->getThrownWeapon() != nullptr) {
					strongAiAgent->enqueueCommand(STRING_HASHCODE("throwgrenade"), 0, targetID, String::valueOf(strongWeapon->getObjectID()), 1);

					Locker locker(strongWeapon);

					if (strongWeapon->getUseCount() < 1) {
						strongWeapon->destroyObjectFromWorld(true);
						strongAiAgent->clearThrownWeapon();
					}
				} else {
					strongAiAgent->error() << "AiAgentThrowGrenadeLambda: thrownWeapon changed to nullptr";
				}
			}, "AiAgentThrowGrenadeLambda");

		}
	}

	const CreatureAttackMap* attackMap = getAttackMap();

	if (attackMap == nullptr) {
		selectDefaultAttack();
		return true;
	}

	return selectSpecialAttack(attackMap->getRandomAttackNumber());
}

bool AiAgentImplementation::selectSpecialAttack(int attackNum) {
	const CreatureAttackMap* attackMap = getAttackMap();

	if (attackMap == nullptr) {
#ifdef DEBUG_AI
		if (peekBlackboard("aiDebug") && readBlackboard("aiDebug") == true)
			info("attackMap == nullptr", true);
#endif // DEBUG_AI
		return false;
	}

	if (attackNum < 0) {
		return selectSpecialAttack();
	}

	if (attackNum >= attackMap->size()) {
#ifdef DEBUG_AI
		if (peekBlackboard("aiDebug") && readBlackboard("aiDebug") == true)
			info("attackNum >= attackMap->size()", true);
#endif // DEBUG_AI
		return false;
	}

	String cmd = attackMap->getCommand(attackNum);

	if (cmd.isEmpty()) {
#ifdef DEBUG_AI
		if (peekBlackboard("aiDebug") && readBlackboard("aiDebug") == true)
			info("cmd.isEmpty()", true);
#endif // DEBUG_AI
		return false;
	}

	nextActionCRC = cmd.hashCode();
	nextActionArgs = attackMap->getArguments(attackNum);

	ZoneServer* zoneServer = getZoneServer();
	if (zoneServer == nullptr)
		return false;

	ObjectController* objectController = zoneServer->getObjectController();
	if (objectController == nullptr)
		return false;

	const QueueCommand* queueCommand = objectController->getQueueCommand(nextActionCRC);
	ManagedReference<SceneObject*> followCopy = getFollowObject().get();

	if (queueCommand == nullptr || followCopy == nullptr)
		return false;

	return true;
}

bool AiAgentImplementation::selectDefaultAttack() {
	if (npcTemplate == nullptr)
		nextActionCRC = STRING_HASHCODE("defaultattack");
	else
		nextActionCRC = npcTemplate->getDefaultAttack().hashCode();

	nextActionArgs = "";

	return true;
}

const QueueCommand* AiAgentImplementation::getNextAction() {
	if (getZoneServer() == nullptr || getZoneServer()->getObjectController() == nullptr)
		return nullptr;

	return getZoneServer()->getObjectController()->getQueueCommand(nextActionCRC);
}

int AiAgentImplementation::enqueueAttack(int priority) {
	ManagedReference<SceneObject*> followCopy = getFollowObject().get();

	if (followCopy != nullptr) {
		enqueueCommand(nextActionCRC, 0, followCopy->getObjectID(), nextActionArgs, priority);
		nextActionCRC = 0;
		nextActionArgs = "";

		return 0;
	}

	return 1;
}

bool AiAgentImplementation::validateStateAttack() {
	ManagedReference<SceneObject*> followCopy = getFollowObject().get();

	if (followCopy == nullptr)
		return false;

	if (!followCopy->isCreatureObject()) {
		// Do not attempt to apply States to Non-CreO Targets
		return true;
	}

	return validateStateAttack(followCopy->asCreatureObject(), nextActionCRC);
}

SceneObject* AiAgentImplementation::getTargetFromMap() {
	TangibleObject* target = getThreatMap()->getHighestThreatAttacker();

	if (target != nullptr && !defenderList.contains(target) && target->getDistanceTo(asAiAgent()) < 128.f && target->isAttackableBy(asAiAgent()) && lastDamageReceived.miliDifference() < 20000) {
		if (target->isCreatureObject()) {
			CreatureObject* creoTarget = target->asCreatureObject();

			if (creoTarget != nullptr && !creoTarget->isDead() && !creoTarget->isIncapacitated()) {
				addDefender(target);
			}
		} else {
			addDefender(target);
		}
	} else if (target != nullptr && defenderList.contains(target) && (!target->isInRange(asAiAgent(), 128) || !target->isAttackableBy(asAiAgent()))) {
		if (target->isCreatureObject()) {
			CreatureObject* tarCreo = target->asCreatureObject();

			if (tarCreo->isDead() || tarCreo->isIncapacitated()) {
				removeDefender(target);
				target = nullptr;
			}
		} else {
			removeDefender(target);
			target = nullptr;
		}
	}

	return target;
}

SceneObject* AiAgentImplementation::getTargetFromDefenders() {
	SceneObject* target = nullptr;

	if (defenderList.size() > 0) {
		for (int i = 0; i < defenderList.size(); ++i) {
			SceneObject* tarObj = defenderList.get(i);

			if (tarObj != nullptr && tarObj->isCreatureObject()) {
				CreatureObject* targetCreature = tarObj->asCreatureObject();

				if (!targetCreature->isDead() && !targetCreature->isIncapacitated() && targetCreature->getDistanceTo(asAiAgent()) < 128.f && targetCreature->isAttackableBy(asAiAgent())) {
					target = targetCreature;

					break;
				} else {
					// if the object on the defender list is no longer attackable, remove it
					removeDefender(targetCreature);
				}
			} else if (tarObj != nullptr && tarObj->isTangibleObject()) {
				TangibleObject* targetTano = tarObj->asTangibleObject();

				if (!targetTano->isDestroyed() && targetTano->getDistanceTo(asAiAgent()) < 128.f && targetTano->isAttackableBy(asAiAgent())) {
					target = targetTano;
					break;
				} else {
					removeDefender(targetTano);
				}
			}
		}
	}

	return target;
}

SceneObject* AiAgentImplementation::getTargetFromTargetsMap(TangibleObject* target) {
	if (target == nullptr) {
		return nullptr;
	}

	Locker threatLock(target, asAiAgent());
	ManagedReference<SceneObject*> prospect = target->getThreatMap()->getHighestThreatAttacker();

	return prospect;
}

SceneObject* AiAgentImplementation::getTargetFromTargetsDefenders() {
	SceneObject* newTarget = nullptr;
	ManagedReference<CreatureObject*> followCopy = getFollowObject().get().castTo<CreatureObject*>();

	if (followCopy == nullptr)
		return nullptr;

	Locker clocker(followCopy, asAiAgent());

	const DeltaVector<ManagedReference<SceneObject*> >* defenders = followCopy->getDefenderList();

	if (defenders->size() > 0) {
		for (int i = 0; i < defenders->size(); ++i) {
			SceneObject* tarObj = defenders->get(i);

			if (tarObj != nullptr && tarObj->isCreatureObject()) {
				CreatureObject* targetCreature = tarObj->asCreatureObject();

				if (!targetCreature->isDead() && !targetCreature->isIncapacitated() && targetCreature->isInRange(asAiAgent(), 128.f) && targetCreature->isAttackableBy(asAiAgent())) {
					newTarget = targetCreature;

					break;
				}
			} else if (tarObj != nullptr && tarObj->isTangibleObject()) {
				TangibleObject* targetTano = tarObj->asTangibleObject();

				if (!targetTano->isDestroyed() && targetTano->getDistanceTo(asAiAgent()) < 128.f && targetTano->isAttackableBy(asAiAgent())) {
					newTarget = targetTano;
					break;
				}
			}
		}
	}

	return newTarget;
}

bool AiAgentImplementation::validateTarget() {
	ManagedReference<SceneObject*> followCopy = asAiAgent()->getFollowObject().get();

	return validateTarget(followCopy);
}

bool AiAgentImplementation::validateTarget(SceneObject* target) {
	if (target == nullptr) {
		//info("validateTarget target == nullptr", true);
		return false;
	}

	if (!target->isInRange(asAiAgent(), 128)) {
		//info("validateTarget not in range", true);
		return false;
	}

	if (target->isCreatureObject()) {
		CreatureObject* targetCreO = target->asCreatureObject();

		if (targetCreO == nullptr || targetCreO->isInvulnerable() || targetCreO->isInvisible()) {
			// info("validateTarget failed CREO checks", true);
			return false;
		}

		if (!targetCreO->isAttackableBy(asAiAgent()) || targetCreO->isDead() || targetCreO->isIncapacitated()) {
			return false;
		}
	} else if (target->isTangibleObject()) {
		TangibleObject* targetTangibleObject = target->asTangibleObject();

		if (targetTangibleObject == nullptr || !targetTangibleObject->isAttackableBy(asAiAgent()) || targetTangibleObject->isDestroyed()) {
			//info("validateTarget failed TANO checks", true);
			return false;
		}
	} else {
		return false;
	}

	//info("validateTarget returning true", true);
	return true;
}

int AiAgentImplementation::notifyAttack(Observable* observable) {
	// TODO: add reaction attacks
	return 0;
}

int AiAgentImplementation::handleObjectMenuSelect(CreatureObject* player, byte selectedID) {
	if (isDead() && !isPet()) {
		switch (selectedID) {
		case 35:
			player->executeObjectControllerAction(STRING_HASHCODE("loot"), getObjectID(), "");

			return 0;
		case 36:
			player->executeObjectControllerAction(STRING_HASHCODE("loot"), getObjectID(), "all");

			return 0;
		}
	}

	return CreatureObjectImplementation::handleObjectMenuSelect(player, selectedID);
}

bool AiAgentImplementation::validateStateAttack(CreatureObject* target, unsigned int actionCRC) {
	ManagedReference<ObjectController*> objectController = getZoneServer()->getObjectController();
	const CombatQueueCommand* queueCommand = cast<const CombatQueueCommand*>(objectController->getQueueCommand(actionCRC));

	const VectorMap<uint8, StateEffect>* effects = queueCommand->getStateEffects();

	if (effects->size() == 0) {
		return true;
	}

	for (int i = 0; i < effects->size(); i++) {
		uint8 effectType = effects->elementAt(i).getKey();

		switch (effectType) {
		case CommandEffect::BLIND:
			if (!target->hasState(CreatureState::BLINDED)) {
				return true;
			}
			break;
		case CommandEffect::DIZZY:
			if (!target->hasState(CreatureState::DIZZY)) {
				return true;
			}
			break;
		case CommandEffect::INTIMIDATE:
			if (!target->hasState(CreatureState::INTIMIDATED)) {
				return true;
			}
			break;
		case CommandEffect::STUN:
			if (!target->hasState(CreatureState::STUNNED)) {
				return true;
			}
			break;
		case CommandEffect::KNOCKDOWN:
			if (!target->isKnockedDown() && target->checkKnockdownRecovery()) {
				return true;
			}
			break;
		case CommandEffect::POSTUREUP:
			if (!target->isStanding() && target->checkPostureUpRecovery()) {
				return true;
			}
			break;
		case CommandEffect::POSTUREDOWN:
			if (!target->isProne() && target->checkPostureDownRecovery()) {
				return true;
			}
			break;
		case CommandEffect::NEXTATTACKDELAY:
			if (!target->hasAttackDelay()) {
				return true;
			}
			break;
		default:
			break;
		}
	}

	return false;
}

void AiAgentImplementation::setDespawnOnNoPlayerInRange(bool val) {
	if (despawnOnNoPlayerInRange == val)
		return;

	despawnOnNoPlayerInRange = val;

	if (val && numberOfPlayersInRange <= 0) {
		if (despawnEvent == nullptr) {
			despawnEvent = new DespawnCreatureOnPlayerDissappear(asAiAgent());
		}

		if (!despawnEvent->isScheduled())
			despawnEvent->schedule(30000);
	}
}

void AiAgentImplementation::runAway(CreatureObject* target, float range, bool random = false) {
	if (getParent().get() != nullptr || getParentID() > 0 || target == nullptr || asAiAgent()->getZoneUnsafe() == nullptr) {
		setMovementState(AiAgent::PATHING_HOME);
		return;
	}

	setTargetObject(target);
	clearPatrolPoints();

	notifyObservers(ObserverEventType::FLEEING, target);
	sendReactionChat(target, ReactionManager::FLEE);

	setMovementState(AiAgent::FLEEING);

	Vector3 runTrajectory;
	Vector3 agentPosition = getPosition();
	Vector3 creaturePosition = target->getPosition();

	if (random) {
		runTrajectory.setX((creaturePosition.getX() + System::random(20)) - (agentPosition.getX() + System::random(20)));
		runTrajectory.setY((creaturePosition.getY() + System::random(20)) - (agentPosition.getY() + System::random(20)));
	} else {
		runTrajectory.setX(agentPosition.getX() - creaturePosition.getX());
		runTrajectory.setY(agentPosition.getY() - creaturePosition.getY());
	}

	float directionAngle = atan2(runTrajectory.getX(), runTrajectory.getY());

	directionAngle = M_PI / 2 - directionAngle;

	if (directionAngle < 0) {
		float a = M_PI + directionAngle;
		directionAngle = M_PI + a;
	}

	runTrajectory = agentPosition + (range * runTrajectory);

	setNextPosition(runTrajectory.getX(), getZoneUnsafe()->getHeight(runTrajectory.getX(), runTrajectory.getY()), runTrajectory.getY(), getParent().get().castTo<CellObject*>());
}

void AiAgentImplementation::leash() {
	homeLocation.setReached(false);
	setMovementState(AiAgent::LEASHING);

	eraseBlackboard("targetProspect");
	setFollowObject(nullptr);
	storeFollowObject();

	CombatManager::instance()->forcePeace(asAiAgent());

	clearPatrolPoints();
	clearDots();
	currentFoundPath = nullptr;
}

void AiAgentImplementation::setDefender(SceneObject* defender) {
	if (defender == nullptr)
		return;

	CreatureObjectImplementation::setDefender(defender);

	setFollowObject(defender);
	setMovementState(AiAgent::FOLLOWING);
	activateRecovery();
}

bool AiAgentImplementation::killPlayer(SceneObject* prospect) {
	if (prospect == nullptr || !prospect->isCreatureObject()) {
		setFollowObject(nullptr);
		return false;
	}

	faceObject(prospect, true);

	PatrolPoint point = prospect->getPosition();
	setNextPosition(point.getPositionX(), point.getPositionZ(), point.getPositionY(), prospect->getParent().get().castTo<CellObject*>());
	activateMovementEvent();

	if (prospect->isInRange(asAiAgent(), 6.f)) {
		ZoneServer* zoneServer = getZoneServer();

		if (zoneServer == nullptr) {
			return false;
		}

		PlayerManager* playerMan = zoneServer->getPlayerManager();
		CreatureObject* prospectCreo = prospect->asCreatureObject();

		if (playerMan != nullptr && prospectCreo != nullptr) {
			Locker klock(prospectCreo);
			playerMan->killPlayer(asCreatureObject(), prospectCreo, 0, false);

			return true;
		}
	}

	return false;
}

bool AiAgentImplementation::stalkProspect(SceneObject* prospect) {
	if (prospect == nullptr || !prospect->isCreatureObject())
		return false;

	CreatureObject* creature = prospect->asCreatureObject();

	if (creature != nullptr && creature->isPlayerCreature() && creature->hasSkill("outdoors_ranger_novice")) {
		StringIdChatParameter param;
		param.setStringId("@skl_use:notify_stalked"); // "It seems that you are being stalked by %TO."
		param.setTO(getObjectName());
		creature->sendSystemMessage(param);
	}

	setStalkObject(prospect);

	PatrolPoint point = prospect->getPosition();
	setNextPosition(point.getPositionX(), point.getPositionZ(), point.getPositionY(), prospect->getParent().get().castTo<CellObject*>());

	return true;
}

void AiAgentImplementation::healTarget(CreatureObject* healTarget) {
	if (healTarget == nullptr || healTarget->isDead()) {
		return;
	}

#ifdef DEBUG_AIHEAL
	ZoneServer* zoneServer = asAiAgent()->getZoneServer();

	ChatManager* chatManager = nullptr;

	if (zoneServer != nullptr)
		chatManager = zoneServer->getChatManager();
#endif

	asAiAgent()->clearQueueActions();

	uint32 socialGroup = getSocialGroup().hashCode();

	if (socialGroup == STRING_HASHCODE("nightsister") || socialGroup == STRING_HASHCODE("mtn_clan") || socialGroup == STRING_HASHCODE("force") || socialGroup == STRING_HASHCODE("spider_nightsister")) {
		if (healTarget == asAiAgent()) {
			healTarget->playEffect("clienteffect/pl_force_heal_self.cef");

#ifdef DEBUG_AIHEAL
			if (chatManager != nullptr)
				chatManager->broadcastChatMessage(asAiAgent(), "Healing myself!", 0, 0, asAiAgent()->getMoodID());
#endif

		} else {
			asAiAgent()->doCombatAnimation(healTarget, STRING_HASHCODE("force_healing_1"), 0, 0xFF);

#ifdef DEBUG_AIHEAL
			if (chatManager != nullptr)
				chatManager->broadcastChatMessage(asAiAgent(), "Healing target!", 0, 0, asAiAgent()->getMoodID());
#endif
		}
	} else {
		if (healTarget == asAiAgent()) {
			asAiAgent()->doAnimation("heal_self");

#ifdef DEBUG_AIHEAL
			if (chatManager != nullptr)
				chatManager->broadcastChatMessage(asAiAgent(), "Healing myself!", 0, 0, asAiAgent()->getMoodID());
#endif

		} else {
			asAiAgent()->doAnimation("heal_other");

#ifdef DEBUG_AIHEAL
			if (chatManager != nullptr)
				chatManager->broadcastChatMessage(asAiAgent(), "Healing target!", 0, 0, asAiAgent()->getMoodID());
#endif
		}

		healTarget->playEffect("clienteffect/healing_healdamage.cef");
	}

	Locker healLock(healTarget);

	int healthMax = healTarget->getMaxHAM(CreatureAttribute::HEALTH) - healTarget->getWounds(CreatureAttribute::HEALTH);
	int actionMax = healTarget->getMaxHAM(CreatureAttribute::ACTION) - healTarget->getWounds(CreatureAttribute::ACTION);
	int mindMax = healTarget->getMaxHAM(CreatureAttribute::MIND) - healTarget->getWounds(CreatureAttribute::MIND);

	int healthDam = healthMax - healTarget->getHAM(CreatureAttribute::HEALTH);
	int actionDam = actionMax - healTarget->getHAM(CreatureAttribute::ACTION);
	int mindDam = mindMax - healTarget->getHAM(CreatureAttribute::MIND);

	int healAmount = getLevel() * 20;

	if (healAmount > healthDam) {
		healTarget->healDamage(asAiAgent(), CreatureAttribute::HEALTH, healthMax, true, false);
	} else {
		healTarget->healDamage(asAiAgent(), CreatureAttribute::HEALTH, healAmount, true, false);
	}

	if (healAmount > actionDam) {
		healTarget->healDamage(asAiAgent(), CreatureAttribute::ACTION, actionMax, true, false);
	} else {
		healTarget->healDamage(asAiAgent(), CreatureAttribute::ACTION, healAmount, true, false);
	}

	if (healAmount > mindDam) {
		healTarget->healDamage(asAiAgent(), CreatureAttribute::MIND, mindMax, true, false);
	} else {
		healTarget->healDamage(asAiAgent(), CreatureAttribute::MIND, healAmount, true, false);
	}
}

void AiAgentImplementation::queueDizzyFallEvent() {
	if (isNonPlayerCreatureObject())
		CreatureObjectImplementation::queueDizzyFallEvent();
}

void AiAgentImplementation::addDefender(SceneObject* defender) {
	if (defender == nullptr) {
		return;
	}

	CreatureObjectImplementation::addDefender(defender);

	if (defender->isTangibleObject() && threatMap != nullptr) {
		threatMap->addAggro(defender->asTangibleObject(), 1);
	}

	notifyPackMobs(defender);
}

void AiAgentImplementation::removeDefender(SceneObject* defender) {
	CreatureObjectImplementation::removeDefender(defender);

	if (defender == nullptr)
		return;

	if (defender->isTangibleObject()) {
		getThreatMap()->dropDamage(defender->asTangibleObject());
	}

	if (getFollowObject().get() == defender) {
		TangibleObject* target = getThreatMap()->getHighestThreatAttacker();

		if (target == nullptr && defenderList.size() > 0) {
			SceneObject* tarObj = defenderList.get(0);

			if (tarObj != nullptr && tarObj->isTangibleObject()) {
				target = tarObj->asTangibleObject();
			}
		}

		if (target != nullptr)
			setDefender(target);
		else
			restoreFollowObject();
	}

	activateRecovery();
}

/**
 * Clears the combat state
 * @pre { this object is locked }
 * @post { this object is locked, this object is not in a combat state }
 * @param clearDefenders if true the defender vector will be emptied
 */
void AiAgentImplementation::clearCombatState(bool clearDefenders) {
	CreatureObjectImplementation::clearCombatState(clearDefenders);

	if (threatMap != nullptr)
		threatMap->removeAll();

	notifyObservers(ObserverEventType::PEACE);
	sendReactionChat(nullptr, ReactionManager::CALM);
}

void AiAgentImplementation::notifyInsert(QuadTreeEntry* entry) {
	CreatureObjectImplementation::notifyInsert(entry);

	SceneObject* scno = static_cast<SceneObject*>( entry);

	if (scno == asAiAgent())
		return;

	if (scno == nullptr)
		return;

	CreatureObject* creo = scno->asCreatureObject();
	if (creo != nullptr && !creo->isInvisible() && creo->isPlayerCreature()) {
		int newValue = (int) numberOfPlayersInRange.increment();
		activateMovementEvent();
	}
}

void AiAgentImplementation::clearDespawnEvent() {
	despawnEvent = nullptr;
}

void AiAgentImplementation::respawn(Zone* zone, int level) {
	if (getZoneUnsafe() != nullptr)
		return;

	blackboard.removeAll();
	CreatureManager* creatureManager = zone->getCreatureManager();

	if (npcTemplate != nullptr && creatureManager != nullptr && isCreature()) {
		int chance = 2000;
		int babiesSpawned = 0;

		ManagedReference<SceneObject*> home = homeObject.get();

		if (home != nullptr) {
			SortedVector<ManagedReference<Observer*> > observers = home->getObservers(ObserverEventType::CREATUREDESPAWNED);
			DynamicSpawnObserver* observer = nullptr;

			for (int i = 0; i < observers.size(); i++) {
				observer = observers.get(i).castTo<DynamicSpawnObserver*>();

				if (observer != nullptr) {
					break;
				}
			}

			if (observer != nullptr) {
				chance = 500;
				babiesSpawned = observer->getBabiesSpawned();
			}
		}

		if (creatureManager->checkSpawnAsBaby(npcTemplate->getTame(), babiesSpawned, chance)) {
			Creature* creature = cast<Creature*>(asAiAgent());

			if (creature) {
				creature->loadTemplateDataForBaby(npcTemplate);
			} else {
				error("object is not a Creature but returned true to spawn as a baby");
			}
		}
	} else {
		setLevel(level);
	}

	clearRunningChain();
	clearCombatState(true);

	setPosture(CreaturePosture::UPRIGHT, false);

	initializePosition(homeLocation.getPositionX(), homeLocation.getPositionZ(), homeLocation.getPositionY());

	CellObject* cell = homeLocation.getCell();

	setNextPosition(homeLocation.getPositionX(), homeLocation.getPositionZ(), homeLocation.getPositionY());
	nextStepPosition.setPosition(homeLocation.getPositionX(), homeLocation.getPositionZ(), homeLocation.getPositionY());
	nextStepPosition.setCell(cell);

	Locker zoneLocker(zone);

	if (cell != nullptr)
		cell->transferObject(asAiAgent(), -1);
	else
		zone->transferObject(asAiAgent(), -1, true);

	respawnCounter++;

	activateMovementEvent();
}

void AiAgentImplementation::sendBaselinesTo(SceneObject* player) {
	ReadLocker locker(&despawnMutex);

	CreatureObjectImplementation::sendBaselinesTo(player);
}

void AiAgentImplementation::notifyDespawn(Zone* zone) {
	Locker mLocker(&movementEventMutex);
	if (moveEvent != nullptr) {
		moveEvent->cancel();
		moveEvent->clearCreatureObject();
		moveEvent = nullptr;
	}

	mLocker.release();

	for (int i = 0; i < movementMarkers.size(); ++i) {
		ManagedReference<SceneObject*> marker = movementMarkers.get(i);
		Locker clocker(marker, asAiAgent());
		marker->destroyObjectFromWorld(false);
	}

	SceneObject* creatureInventory = asAiAgent()->getSlottedObject("inventory");

	if (creatureInventory != nullptr) {
		Locker clocker(creatureInventory, asAiAgent());
		creatureInventory->setContainerOwnerID(0);
	}

	if (npcTemplate == nullptr)
		return;

	int oldLevel = level;

	Locker locker(&despawnMutex);

	loadTemplateData(templateObject);
	loadTemplateData(npcTemplate);

	if (oldLevel != level)
		setLevel(level);

	stateBitmask = 0;

	shockWounds = 0;

	if (threatMap != nullptr)
		threatMap->removeAll();

	locker.release();

	//Delete all loot out of inventory
	ManagedReference<SceneObject*> inventory = asAiAgent()->getSlottedObject("inventory");

	if (inventory != nullptr) {
		while (inventory->getContainerObjectsSize() > 0) {
			ManagedReference<SceneObject*> obj = inventory->getContainerObject(0);
			inventory->removeFromContainerObjects(0);
			obj->destroyObjectFromWorld(false);
			obj->destroyObjectFromDatabase(true);
		}
	}

	setTargetObject(nullptr);
	setFollowObject(nullptr);

	//asAiAgent()->printReferenceHolders();

	//printf("%d ref count\n", asAiAgent()->getReferenceCount());

	ManagedReference<SceneObject*> home = homeObject.get();

	if (home != nullptr) {
		home->notifyObservers(ObserverEventType::CREATUREDESPAWNED, asAiAgent());
		return;
	}

	notifyObservers(ObserverEventType::CREATUREDESPAWNED);

	if (respawnTimer <= 0) {
		return;
	}

	float respawn = respawnTimer * 1000;

	if (randomRespawn) {
		respawn = System::random(respawn) + (respawn / 2.f);
	}

	Reference<Task*> task = new RespawnCreatureTask(asAiAgent(), zone, level);
	task->schedule(respawn);
}

void AiAgentImplementation::scheduleDespawn(int timeToDespawn) {
	if (getPendingTask("despawn") != nullptr)
		return;

	Reference<DespawnCreatureTask*> despawn = new DespawnCreatureTask(asAiAgent());
	addPendingTask("despawn", despawn, timeToDespawn * 1000);
}

void AiAgentImplementation::notifyDissapear(QuadTreeEntry* entry) {
	CreatureObjectImplementation::notifyDissapear(entry);

	SceneObject* scno = static_cast<SceneObject*>( entry);

	if (scno == asAiAgent())
		return;

	if (scno == getFollowObject().get()) {
			ManagedReference<AiAgent*> ai = asAiAgent();
			ManagedReference<SceneObject*> sceno = scno;

			Core::getTaskManager()->executeTask([=] () {
				Locker locker(ai);
				Locker clocker(sceno, ai);

				if (sceno == ai->getFollowObject().get()) {
					ai->restoreFollowObject();
				}
			}, "RestoreFollowObjectLambda");
	}

	if (scno->isPlayerCreature()) {
		CreatureObject* creo = scno->asCreatureObject();
		if (!creo->isInvisible()) {
			int32 newValue = (int32) numberOfPlayersInRange.decrement();

			if (newValue < 0) {
				int oldValue;

				do {
					oldValue = (int)numberOfPlayersInRange.get();

					newValue = oldValue;

					if (newValue < 0)
						newValue = 0;
				} while (!numberOfPlayersInRange.compareAndSet((uint32)oldValue, (uint32)newValue));
			}

			if (newValue == 0) {
				if (despawnOnNoPlayerInRange && (despawnEvent == nullptr) && !isPet()) {
					despawnEvent = new DespawnCreatureOnPlayerDissappear(asAiAgent());
					despawnEvent->schedule(30000);
				}
			} else if (newValue < 0) {
				error("numberOfPlayersInRange below 0");
			}

			activateMovementEvent();
		}
	}
}

void AiAgentImplementation::activateRecovery() {
	if (thinkEvent == nullptr) {
		thinkEvent = new AiThinkEvent(asAiAgent());

		thinkEvent->schedule(2000);
	}

	if (!thinkEvent->isScheduled())
		thinkEvent->schedule(2000);
}

void AiAgentImplementation::activatePostureRecovery() {
	if (isKnockedDown() && !hasPostureChangeDelay()) {
		enqueueCommand(STRING_HASHCODE("stand"), 0, 0, "");
		return;
	}

	if (isProne() || isKneeling()) {
		if (isInCombat()) {
			if (System::random(100) > 75 && postureSet.miliDifference() > 0) {
				enqueueCommand(STRING_HASHCODE("stand"), 0, 0, "");
				return;
			}

			ManagedReference<SceneObject*> followCopy = getFollowObject().get();

			if (followCopy != nullptr) {
				float sqrDist = getPosition().squaredDistanceTo(followCopy->getPosition());

				if ((weapon != nullptr && Math::sqrt(sqrDist) > weapon->getMaxRange()) || !checkLineOfSight(followCopy)) {
					enqueueCommand(STRING_HASHCODE("stand"), 0, 0, "");
				}
			}
		} else {
			enqueueCommand(STRING_HASHCODE("stand"), 0, 0, "");
		}
	}
}

void AiAgentImplementation::activateHAMRegeneration(int latency) {
	if (isIncapacitated() || isDead() || isInCombat())
		return;

	uint32 healthTick = (uint32) Math::max(1.f, (float) ceil(getMaxHAM(CreatureAttribute::HEALTH) / 300000.f * latency));
	uint32 actionTick = (uint32) Math::max(1.f, (float) ceil(getMaxHAM(CreatureAttribute::ACTION) / 300000.f * latency));
	uint32 mindTick   = (uint32) Math::max(1.f, (float) ceil(getMaxHAM(CreatureAttribute::MIND) / 300000.f * latency));

	healDamage(asCreatureObject(), CreatureAttribute::HEALTH, healthTick, true, false);
	healDamage(asCreatureObject(), CreatureAttribute::ACTION, actionTick, true, false);
	healDamage(asCreatureObject(), CreatureAttribute::MIND,   mindTick,   true, false);

	activatePassiveWoundRegeneration();
}

void AiAgentImplementation::updateCurrentPosition(PatrolPoint* nextPosition) {
	if (nextPosition == nullptr)
		return;

	setPosition(nextPosition->getPositionX(), nextPosition->getPositionZ(), nextPosition->getPositionY());

	CellObject* cell = nextPosition->getCell();

	/*StringBuffer reachedPosition;
	reachedPosition << "(" << nextPosition->getPositionX() << ", " << nextPosition->getPositionY() << ")";
	info("reached " + reachedPosition.toString(), true);*/

	if (getZoneUnsafe() == nullptr)
		return;

	if (cell != nullptr && cell->getParent().get() != nullptr)
		updateZoneWithParent(cell, false, false);
	else
		updateZone(false, false);

	removeOutOfRangeObjects();
}

void AiAgentImplementation::updatePetSwimmingState() {
	if (parent != nullptr) {
		return;
	}

	Zone* zone = getZoneUnsafe();

	if (zone == nullptr) {
		return;
	}

	PlanetManager* planetManager = zone->getPlanetManager();

	if (planetManager == nullptr) {
		return;
	}

	TerrainManager* terrainManager = planetManager->getTerrainManager();

	if (terrainManager == nullptr) {
		return;
	}

	float waterHeight;
	bool waterIsDefined = terrainManager->getWaterHeight(getPositionX(), getPositionY(), waterHeight);
	float petHeight = getPositionZ();
	float swimVar = (waterHeight - swimHeight + 0.2f);

	if (waterIsDefined && (swimVar - petHeight > 0.1)) {
		// Pet is in the water.
		setState(CreatureState::SWIMMING, true);
		return;
	}

	// Terrain is above water level.
	clearState(CreatureState::SWIMMING, true);
}

void AiAgentImplementation::checkNewAngle() {
	ManagedReference<SceneObject*> followCopy = getFollowObject().get();

	if (followCopy == nullptr)
		return;

	// info("Check new angle called ", true);

	faceObject(followCopy, true);
}

// It is important to know that the return of this function determines whether
// or not an AI should try to continue finding positions next tick. If true,
// the AI has not reached the first patrolPoint in their queue and if false,
// they have and that patrolPoint has been popped (and saved if necessary).
bool AiAgentImplementation::findNextPosition(float maxDistance, bool walk) {
	/*
	 * SETUP: Calculate and initialize situational variables
	 */

#ifdef DEBUG_AI
	if (peekBlackboard("aiDebug") && readBlackboard("aiDebug") == true)
		info("findNextPosition(" + String::valueOf(maxDistance) + ", " + String::valueOf(walk) + ")", true);
#endif // DEBUG_AI

	Locker locker(&targetMutex);

	WorldCoordinates nextMovementPosition;

	float newSpeed = runSpeed; // float CreatureObjectImplementation::DEFAULTRUNSPEED = 5.376f;
	int posture = getPosture();
	int movementState = getMovementState();

	if (posture == CreaturePosture::CROUCHED) //move to BT?
		return false;

	if (movementState == AiAgent::FLEEING)
		newSpeed *= 0.7f;

	if ((walk && movementState != AiAgent::FLEEING) || posture == CreaturePosture::PRONE)
		newSpeed = walkSpeed;

	if (hasState(CreatureState::IMMOBILIZED))
		newSpeed = newSpeed / 2.f;

	if (hasState(CreatureState::FROZEN))
		newSpeed = 0.01f;

	float updateTicks = float(UPDATEMOVEMENTINTERVAL) / 1000.f;
	float maxSpeed = newSpeed * updateTicks; // maxSpeed is the distance able to travel in time updateTicks

	PathFinderManager* pathFinder = PathFinderManager::instance();
	float maxDist = maxSpeed;

	bool found = false;
	auto currentPosition = getWorldPosition();

#ifdef DEBUG_PATHING
	CreateClientPathMessage* pathMessage = new CreateClientPathMessage();
	if (getParent() == nullptr) {
		pathMessage->addCoordinate(getPositionX(), getZone()->getHeight(getPositionX(), getPositionY()), getPositionY());
	} else {
		pathMessage->addCoordinate(getPositionX(), getPositionZ(), getPositionY());
	}
#endif

	// setNextPosition adds a point to patrolPoints at spot 0 -- usually by the setDestination function
	while (!found && getPatrolPointSize() > 0) {
		PatrolPoint endMovementPosition = getNextPosition();

		if (currentPosition.squaredDistanceTo(endMovementPosition.getWorldPosition()) <= maxDistance * maxDistance) {
			patrolPoints.remove(0);
			break;
		}

#ifdef DEBUG_AI
		if (peekBlackboard("aiDebug") && readBlackboard("aiDebug") == true)
			info("targetPosition: " + endMovementPosition.toString(), true);
#endif // DEBUG_AI

		/*
		*	STEP 1: Find a path if there is not a previously found path
		*/

		Reference<Vector<WorldCoordinates>* > path;

		if (currentFoundPath == nullptr) {
			// No prior path or path is null, find new path
			path = currentFoundPath = static_cast<CurrentFoundPath*>(pathFinder->findPath(asAiAgent(), endMovementPosition.getCoordinates(), getZoneUnsafe()));
		} else {
			ManagedReference<SceneObject*> currentCell = getParent().get();

			if (currentCell != nullptr && !currentCell->isCellObject())
				currentCell = nullptr;

			// We already have a path
			const WorldCoordinates endMovementCoords = endMovementPosition.getCoordinates();

			if (currentCell != nullptr && endMovementPosition.getCell() != nullptr && currentFoundPath->get(currentFoundPath->size() - 1).getWorldPosition().squaredDistanceTo(endMovementCoords.getWorldPosition()) > 3 * 3) {
				// Our target has moved, so we will need a new path with a new position.
				path = currentFoundPath = static_cast<CurrentFoundPath*>(pathFinder->findPath(asAiAgent(), endMovementPosition.getCoordinates(), getZoneUnsafe()));
			} else {
				// Our target is close to where it was before, so our path begins where we are standing
				WorldCoordinates curr(asAiAgent());
				path = currentFoundPath;

				path->set(0, curr);
			}
		}

		if (path == nullptr) {
			// we weren't able to find a path, so remove this location from patrolPoints and try again with the next one
			PatrolPoint oldPoint = patrolPoints.remove(0);

			if (getMovementState() == AiAgent::PATROLLING)
				savedPatrolPoints.add(oldPoint);

			if (isRetreating())
				homeLocation.setReached(true);

			if (getPatrolPointSize() == 0) {
				CellObject* sourceCell = getParent().get().castTo<CellObject*>();
				error("nullptr or empty path in AiAgent::findNextPosition. Source was " + getPosition().toString() + " in " + String::valueOf(sourceCell != nullptr ? sourceCell->getCellNumber() : 0) + ". Destination was " + oldPoint.toString());

				found = false;
				break;
			}

			continue;
		}

		float endMovementDistance = endMovementPosition.getWorldPosition().squaredDistanceTo(currentPosition);
		float maxSquared = maxDistance * maxDistance;

		if (endMovementDistance < maxSquared) {
			patrolPoints.remove(0);
			break;
		}

		// Get rid of duplicate/invalid points in path
		pathFinder->filterPastPoints(path, asAiAgent());

		/*
		 * STEP 2: Calculate distance to travel & apply it to find position along the path
		 */

		if (endMovementDistance > maxSquared) {
			// this is the actual "distance we can travel" calculation. We only want to
			// go to the edge of the maxDistance radius and stop, so select the minimum
			// of either our max travel distance (maxSpeed) or the distance from the
			// maxDistance radius
			maxDist = Math::min(maxSpeed, endMovementDistance - maxSquared + 0.1f);
		} else {
			break;
		}

		if (path->size() < 2) {
			// we know path size is at least one, so somehow we got a one-position path (this shouldn't happen)
			// just use the one position as our next point don't set found because this is our current position
			nextMovementPosition = path->get(0);
		} else {
			// the farthest we will move is one point in the path, and the movement update time will change to reflect that
			nextMovementPosition = path->get(1);
			found = true;

			float nextMovementDistance = fabs(nextMovementPosition.getWorldPosition().distanceTo(currentPosition));

#ifdef DEBUG_PATHING
			printf("findNexPosition - Path Size = %i \n", path->size());
			printf("Start of Calc \n");
			printf("max distance = %f \n", maxDist);
			printf("Next Movement Position x = %f , ", nextMovementPosition.getX());
			printf(" y = %f \n", nextMovementPosition.getY());

			for (int i = 0; i < path->size(); ++i) {
				WorldCoordinates pos = path->get(i);

				printf("Point # %i ", i);
				printf(" X = %f , ", pos.getX());
				printf(" Y = %f \n", pos.getY());

				if (pos.isCellEdge())
					printf("<----- Point is a Cell Edge ------> \n");

				if (pos.getCell() == nullptr)
					printf(" Cell is null \n");
			}
#endif

			if (nextMovementDistance > maxDist && nextMovementDistance > 0) {
				// nextMovementPosition is further then the maxDist
				// Calculate the distance we can go and set the new nextMovementPosition
				Vector3 currentPos = currentPosition;
				Vector3 newPosition;

				// Issue - We are assigning AI to a location outside of the actual cell boundary
				if (nextMovementPosition.getCell() != nullptr && !nextMovementPosition.isCellEdge()) {
					currentPos = PathFinderManager::transformToModelSpace(currentPos, nextMovementPosition.getCell()->getParent().get());
				}

				if (nextMovementPosition.isCellEdge() && nextMovementPosition.getCell() != nullptr) {
					newPosition.setX(nextMovementPosition.getX());
					newPosition.setY(nextMovementPosition.getY());
				} else {
					float dx = nextMovementPosition.getX() - currentPos.getX();
					float dy = nextMovementPosition.getY() - currentPos.getY();

					newPosition.setX(currentPos.getX() + (maxDist * (dx / nextMovementDistance)));
					newPosition.setY(currentPos.getY() + (maxDist * (dy / nextMovementDistance)));
				}

				newPosition.setZ(0.f);

				Zone* zone = getZoneUnsafe();

				// We must check that the end movement position does not end in a cell because AI will be placed on the overhangs of buildings before entering
				if (nextMovementPosition.getCell() == nullptr && endMovementPosition.getCell() == nullptr && zone != nullptr) {
					newPosition.setZ(getWorldZ(newPosition));

					PlanetManager* planetManager = zone->getPlanetManager();

					if (planetManager != nullptr) {
						TerrainManager* terrainManager = planetManager->getTerrainManager();

						if (terrainManager != nullptr) {
							float waterHeight;
							bool waterIsDefined = terrainManager->getWaterHeight(newPosition.getX(), newPosition.getY(), waterHeight);

							if (waterIsDefined && (waterHeight > newPosition.getZ()) && isSwimming()) {
								newPosition.setZ(waterHeight - swimHeight);
							}
						}
					}
				} else {
					float z = getPositionZ();
					float dz = nextMovementPosition.getZ() - z;

					newPosition.setZ(z + (maxDist * (dz / nextMovementDistance)));
				}

				nextMovementPosition.setX(newPosition.getX());
				nextMovementPosition.setY(newPosition.getY());
				nextMovementPosition.setZ(newPosition.getZ());
			}
		}

#ifdef DEBUG_PATHING
		for (int i = 1; i < path->size(); ++i) { // i = 0 is our position
			const WorldCoordinates& nextPositionDebug = path->get(i);

			Vector3 nextWorldPos = nextPositionDebug.getWorldPosition();

			if (nextPositionDebug.getCell() == nullptr)
				pathMessage->addCoordinate(nextWorldPos.getX(), currentPosition.getZ(), nextWorldPos.getY());
			else
				pathMessage->addCoordinate(nextWorldPos.getX(), nextWorldPos.getZ(), nextWorldPos.getY());

#ifdef SHOW_NEXT_POSITION
			if (showNextMovementPosition) {
				for (int i = 0; i < movementMarkers.size(); ++i) {
					ManagedReference<SceneObject*> marker = movementMarkers.get(i);
					Locker clocker(marker, asAiAgent());
					marker->destroyObjectFromWorld(false);
				}

				movementMarkers.removeAll();

				Reference<SceneObject*> movementMarker = getZoneServer()->createObject(STRING_HASHCODE("object/path_waypoint/path_waypoint.iff"), 0);

				Locker clocker(movementMarker, asAiAgent());

				movementMarker->initializePosition(nextPositionDebug.getX(), nextPositionDebug.getZ(), nextPositionDebug.getY());
				StringBuffer msg;
				msg << "Next Position: path distance: " << nextPositionDebug.getWorldPosition().distanceTo(getWorldPosition()) << " maxDist:" << maxDist;
				movementMarker->setCustomObjectName(msg.toString(), false);

				CellObject* cellObject = nextPositionDebug.getCell();

				if (cellObject != nullptr) {
					cellObject->transferObject(movementMarker, -1, true);
				} else {
					getZone()->transferObject(movementMarker, -1, false);
				}

				movementMarkers.add(movementMarker);

				clocker.release();

				for (int i = 0; i < path->size(); ++i) {
					WorldCoordinates* coord = &path->get(i);
					CellObject* coordCell = coord->getCell();

					movementMarker = getZoneServer()->createObject(STRING_HASHCODE("object/path_waypoint/path_waypoint.iff"), 0);

					Locker clocker(movementMarker, asAiAgent());

					movementMarker->initializePosition(coord->getPoint().getX(), coord->getPoint().getZ(), coord->getPoint().getY());

					if (coordCell != nullptr) {
						coordCell->transferObject(movementMarker, -1, true);
					} else {
						getZone()->transferObject(movementMarker, -1, false);
					}

					movementMarkers.add(movementMarker);
				}
			}
#endif
		}
#endif
	}

#ifdef DEBUG_PATHING
	broadcastMessage(pathMessage, false);
#endif

	/*
	 * STEP 3: Finish the update tick
	 */

	if (found) {
		// Set the next place we will be if we are to move
		Vector3 nextWorldPos = nextMovementPosition.getWorldPosition();
		float distance = currentPosition.distanceTo(nextWorldPos);

		if (!(distance > 0 && newSpeed > 0.1)) {
			found = false;
		} else {
			nextStepPosition.setPosition(nextMovementPosition.getX(), nextMovementPosition.getZ(), nextMovementPosition.getY());
			nextStepPosition.setCell(nextMovementPosition.getCell());
			nextStepPosition.setReached(false);

			float dx = nextMovementPosition.getX() - getPositionX();
			float dy = nextMovementPosition.getY() - getPositionY();

			float directionAngle = atan2(dy, dx);

			directionAngle = M_PI / 2 - directionAngle;

			if (directionAngle < 0) {
				float a = M_PI + directionAngle;
				directionAngle = M_PI + a;
			}

			float error = fabs(directionAngle - direction.getRadians());

			if (error >= 0.05) {
				setDirection(directionAngle);
			}

			auto interval = UPDATEMOVEMENTINTERVAL;
			nextMovementInterval = Math::min((int)((Math::min(distance, maxDist) / newSpeed) * 1000 + 0.5), interval);
			currentSpeed = newSpeed;

			// Tell the clients where to expect us next tick -- requires that we have found a destination
			broadcastNextPositionUpdate(&nextStepPosition);
		}
	}

	if (!found) {
		uint32 movementState = getMovementState();

		if ((movementState == AiAgent::PATROLLING || movementState == AiAgent::WATCHING) && patrolPoints.size() > 0)
			savedPatrolPoints.add(patrolPoints.remove(0));

		if (movementState == AiAgent::EVADING)
			setMovementState(AiAgent::FOLLOWING);

		ManagedReference<SceneObject*> followCopy = followObject.get();

		if (followCopy == nullptr)
			notifyObservers(ObserverEventType::DESTINATIONREACHED);

		if (isRetreating())
			homeLocation.setReached(true);

		currentFoundPath = nullptr;
		targetCellObject = nullptr;
		currentSpeed = 0;
	}

	completeMove();
	updateLocomotion();

	return (getMovementState() == AiAgent::FLEEING && !fleeDelay.isPast()) || found;
}

bool AiAgentImplementation::checkLineOfSight(SceneObject* obj) {
	return CollisionManager::checkLineOfSight(asAiAgent(), obj);
}

float AiAgentImplementation::getWorldZ(const Vector3& position) {
	float zCoord = 0.f;

	Zone* zone = getZoneUnsafe();
	if (zone == nullptr)
		return zCoord;

	IntersectionResults intersections;

	if (closeobjects != nullptr) {
		Vector<QuadTreeEntry*> closeObjects(closeobjects->size(), 10);

		closeobjects->safeCopyReceiversTo(closeObjects, CloseObjectsVector::COLLIDABLETYPE);
		CollisionManager::getWorldFloorCollisions(position.getX(), position.getY(), zone, &intersections, closeObjects);

		zCoord = zone->getPlanetManager()->findClosestWorldFloor(position.getX(), position.getY(), position.getZ(), getSwimHeight(), &intersections, nullptr);
	} else {
		SortedVector<ManagedReference<QuadTreeEntry*> > closeObjects;

#ifdef COV_DEBUG
		zone->info("Null closeobjects vector in AiAgentImplementation::getWorldZ", true);
#endif

		Vector3 worldPosition = getWorldPosition();
		zone->getInRangeObjects(worldPosition.getX(), worldPosition.getY(), 128, &closeObjects, true);

		CollisionManager::getWorldFloorCollisions(position.getX(), position.getY(), zone, &intersections, closeObjects);

		zCoord = zone->getPlanetManager()->findClosestWorldFloor(position.getX(), position.getY(), position.getZ(), getSwimHeight(), &intersections, nullptr);
	}

	return zCoord;
}

void AiAgentImplementation::doMovement() {
	//info("doMovement", true);
	Reference<Behavior*> rootBehavior = getBehaviorTree(BehaviorTreeSlot::NONE);
	assert(rootBehavior != nullptr);

	// Do pre-checks (these should remain hard-coded)
	if (asAiAgent()->isDead() || asAiAgent()->isIncapacitated() || (asAiAgent()->getZoneUnsafe() == nullptr) || !(getOptionsBitmask() & OptionBitmask::AIENABLED)) {
		setFollowObject(nullptr);
		return;
	}

	Time startTime;
	startTime.updateToCurrentTime();

	//if (isWaiting())
	//	stopWaiting();

#ifdef DEBUG_AI
	if (peekBlackboard("aiDebug") && readBlackboard("aiDebug") == true)
		info("Performing root behavior: " + rootBehavior->print(), true);
#endif // DEBUG_AI
	// activate AI
	Behavior::Status actionStatus = rootBehavior->doAction(asAiAgent());

	if (actionStatus == Behavior::RUNNING)
		popRunningChain(); // don't keep root in the running chain

	//if (actionStatus == Behavior::RUNNING) {
	//	std::cout << "Running chain: (" << runningChain.size() << ")" << std::endl;
	//	for (int i = 0; i < runningChain.size(); ++i) {
	//		std::cout << "0x" << std::hex << runningChain.get(i) << std::endl;;
	//	}
	//}

#ifdef DEBUG_AI
	if (peekBlackboard("aiDebug") && readBlackboard("aiDebug") == true)
		info("rootBehavior->doAction() took " + String::valueOf((int)startTime.miliDifference()) + "ms to complete.", true);
#endif // DEBUG_AI

	activateMovementEvent();
}

void AiAgentImplementation::setAIDebug(bool flag) {
#ifdef DEBUG_AI
	writeBlackboard("aiDebug", flag);
#endif // DEBUG_AI
	info() << "setAIDebug(" << flag << ")";

	if (flag) {
		setLogLevel(LogLevel::DEBUG);
	} else {
		auto aiLogLevel = ConfigManager::instance()->getInt("Core3.AiAgent.LogLevel", -1);

		if (aiLogLevel >= 0) {
			setLogLevel(static_cast<Logger::LogLevel>(aiLogLevel));
		} else {
			setLogLevel(Logger::LogLevel::ERROR);
		}
	}
}

bool AiAgentImplementation::getAIDebug() {
#ifdef DEBUG_AI
	return peekBlackboard("aiDebug") && readBlackboard("aiDebug") == true;
#else // DEBUG_AI
	return getLogLevel() >= LogLevel::DEBUG;
#endif // DEBUG_AI
}

bool AiAgentImplementation::isRunningBehavior(unsigned int id) {
	return runningChain.contains(id);
}

void AiAgentImplementation::addRunningID(unsigned int id) {
	runningChain.add(id); // this adds to the back
}

void AiAgentImplementation::popRunningChain() {
	// pop_back
	runningChain.remove(runningChain.size() - 1);
}

uint32 AiAgentImplementation::peekRunningChain() {
	return runningChain.get(runningChain.size() - 1);
}

void AiAgentImplementation::clearRunningChain() {
	runningChain.removeAll();
}

void AiAgentImplementation::setAITemplate() {
	btreeMap.removeAll();
	blackboard.removeAll();

	uint64 customMap = customAiMap;

	if (npcTemplate.get() != nullptr && customAiMap == 0)
		customMap = npcTemplate.get()->getCustomAiMap();

	for (const auto& slot : BehaviorTreeSlot()) {
		Behavior* btree = AiMap::instance()->getTemplate(creatureBitmask, slot, customMap);

		if (btree == nullptr)
			continue;

		setTree(btree, slot);
	}

	activateMovementEvent();
}

Behavior* AiAgentImplementation::getBehaviorTree(const BehaviorTreeSlot& slot) {
	return btreeMap.get(slot).get();
}

void AiAgentImplementation::setTree(Behavior* subRoot, const BehaviorTreeSlot& slot) {
	if (subRoot == nullptr) {
		btreeMap.drop(slot);
		return;
	}

	btreeMap.put(slot, subRoot);
}

void AiAgentImplementation::removeTree(const BehaviorTreeSlot& slot) {
	setTree(NULL, slot);
}

void AiAgentImplementation::loadCreatureBitmask() {
}

void AiAgentImplementation::unloadCreatureBitmask() {
}

bool AiAgentImplementation::generatePatrol(int num, float dist) {
	Zone* zone = getZoneUnsafe();

	if (zone == nullptr)
		return false;

	uint32 savedState = getMovementState(); // save this off in case we fail

	if (savedState == AiAgent::LEASHING)
		return false;

	if (savedState != AiAgent::PATROLLING || savedState != AiAgent::WATCHING) {
		setMovementState(AiAgent::PATROLLING); // this clears patrol points
		clearSavedPatrolPoints();
	}

	if (isInNavMesh()) {
		Vector3 homeCoords;
		homeCoords.setX(homeLocation.getPositionX());
		homeCoords.setY(homeLocation.getPositionY());
		homeCoords.setZ(homeLocation.getPositionZ());

		Sphere sphere(homeCoords, dist);
		Vector3 result;

		for (int i = 0; i < num; i++) {
			if (PathFinderManager::instance()->getSpawnPointInArea(sphere, zone, result, false)) {
				PatrolPoint point(result);
				addPatrolPoint(point);
			}
		}
	} else {
		SortedVector<QuadTreeEntry*> closeObjects;

		if (closeobjects != nullptr) {
			closeobjects->safeCopyReceiversTo(closeObjects, CloseObjectsVector::COLLIDABLETYPE);
		} else {
#ifdef COV_DEBUG
			zone->info("Null closeobjects vector in AiAgentImplementation::generatePatrol", true);
#endif

			Vector3 worldPosition = getWorldPosition();
			zone->getInRangeObjects(worldPosition.getX(), worldPosition.getY(), 128, &closeObjects, true);
		}

		for (int i = 0; i < num; i++) {
			PatrolPoint newPoint;
			newPoint.setPositionX(homeLocation.getPositionX() + (-1 * dist + (float)System::random((unsigned int)dist * 2)));
			newPoint.setPositionY(homeLocation.getPositionY() + (-1 * dist + (float)System::random((unsigned int)dist * 2)));
			newPoint.setPositionZ(homeLocation.getPositionZ());

			ManagedReference<SceneObject*> strongParent = getParent().get();
			if (strongParent != nullptr && strongParent->isCellObject()) {
				newPoint.setCell(strongParent.castTo<CellObject*>());
			}

			if (newPoint.getCell() == nullptr && zone != nullptr) {
				PlanetManager* planetManager = zone->getPlanetManager();
				IntersectionResults intersections;

				CollisionManager::getWorldFloorCollisions(newPoint.getPositionX(), newPoint.getPositionY(), zone, &intersections, closeObjects);

				newPoint.setPositionZ(planetManager->findClosestWorldFloor(newPoint.getPositionX(), newPoint.getPositionY(), newPoint.getPositionZ(), this->getSwimHeight(), &intersections, (CloseObjectsVector*) this->getCloseObjects()));
			}

			addPatrolPoint(newPoint);
		}
	}

	if (getPatrolPointSize() > 0)
		return true;

	setMovementState(savedState);
	return false;
}

float AiAgentImplementation::getMaxDistance() {
	if (isRetreating() || isFleeing())
		return 0.1f;

	ManagedReference<SceneObject*> followCopy = getFollowObject().get();
	unsigned int stateCopy = getMovementState();

	// info("getmaxDistance - stateCopy: " + String::valueOf(stateCopy) /*+ " Max Distance: " + String::valueOf(maxDistance)*/, true);
	switch (stateCopy) {
	case AiAgent::OBLIVIOUS:
		return 2.0f;
	case AiAgent::WATCHING:
		return 1.5f;
		break;
	case AiAgent::PATROLLING:
	case AiAgent::LEASHING:
		return 0.1f;
		break;
	case AiAgent::STALKING: {
		int stalkRad = 0;
		if (peekBlackboard("stalkRadius"))
			stalkRad = readBlackboard("stalkRadius").get<int>() / 5;

		return stalkRad > 0 ? stalkRad : 10;
		break;
	}
	case AiAgent::FOLLOWING:
		if (followCopy == nullptr)
			return 0.1f;

		if (!CollisionManager::checkLineOfSight(asAiAgent(), followCopy)) {
			return 1.0f;
		} else if (!isInCombat()) {
			if (peekBlackboard("formationOffset")) {
				if (isPet()) {
					return 0.1f;
				} else {
					return 1.0f;
				}
			} else {
				if (isPet() && isDroid())
					return 2.0f;

				return 4.0f;
			}
		} else if (getWeapon() != nullptr) {
			WeaponObject* currentWeapon = getWeapon();
			float weapMaxRange = 1.0f;

			if (currentWeapon != nullptr) {
				weapMaxRange = Math::min(currentWeapon->getIdealRange(), currentWeapon->getMaxRange());

				if (currentWeapon->isMeleeWeapon() && weapMaxRange > 8) {
					weapMaxRange = 3.f;
				}

				weapMaxRange = Math::max(1.0f, weapMaxRange + getTemplateRadius() + followCopy->getTemplateRadius());
			}

			return weapMaxRange;
		} else {
			return 1 + getTemplateRadius() + followCopy->getTemplateRadius();
		}
		break;
	case AiAgent::PATHING_HOME:
		return 0.1f;
		break;
	case AiAgent::MOVING_TO_HEAL:
		return 1.5f;
		break;
	}

	return 5.f;
}

int AiAgentImplementation::setDestination() {
	//info("setDestination start", true);

	ManagedReference<SceneObject*> followCopy = getFollowObject().get();
	unsigned int stateCopy = getMovementState();

	// info("setDestination - stateCopy: " + String::valueOf(stateCopy), true);
	// info("homeLocation: " + homeLocation.toString(), true);

	switch (stateCopy) {
	case AiAgent::OBLIVIOUS:
		break;
	case AiAgent::FLEEING: {
		float range = fleeRange;

		if (peekBlackboard("fleeRange"))
			range = readBlackboard("fleeRange").get<float>() / 4;

		if (followCopy == nullptr || !isInRange(followCopy, 128.f)
				|| getPatrolPointSize() == 0 || getNextPosition().isInRange(asAiAgent(), range > 5.f ? range : 5.f)) {
			eraseBlackboard("fleeRange");
			setMovementState(AiAgent::PATHING_HOME);
			return setDestination();
		}

		break;
	}
	case AiAgent::LEASHING:
		if (!isRetreating()) {
			setMovementState(AiAgent::PATHING_HOME);
			return setDestination();
		}

		if (!homeLocation.isInRange(asAiAgent(), 1.0f)) {
			homeLocation.setReached(false);
			addPatrolPoint(homeLocation);
		} else {
			setDirection(Math::deg2rad(homeLocation.getDirection()));
			broadcastNextPositionUpdate(&homeLocation);
			homeLocation.setReached(true);
		}

		break;
	case AiAgent::PATROLLING:
		if (getPatrolPointSize() == 0) {
			setPatrolPoints(savedPatrolPoints);
			clearSavedPatrolPoints();
		}

		break;
	case AiAgent::WATCHING:
		if (followCopy == nullptr || alertedTime.isPast()) {
			setMovementState(AiAgent::PATHING_HOME);
			return setDestination();
		}

		break;
	case AiAgent::STALKING:
		if (followCopy == nullptr || !followCopy->isInRange(asAiAgent(), 128)) {
			setMovementState(AiAgent::PATHING_HOME);
			return setDestination();
		}

		setNextPosition(followCopy->getPositionX(), followCopy->getPositionZ(), followCopy->getPositionY(), followCopy->getParent().get().castTo<CellObject*>());
		break;
	case AiAgent::FOLLOWING: {
		if (followCopy == nullptr) {
			setMovementState(AiAgent::PATHING_HOME);
			return setDestination();
		}

		clearPatrolPoints();

		if (!isPet() && followCopy->getParent().get() != nullptr) {
			ManagedReference<SceneObject*> rootParent = followCopy->getRootParent();

			if (rootParent != nullptr && rootParent->isBuildingObject()) {
				BuildingObject* rootBuilding = rootParent.castTo<BuildingObject*>();

				if (rootBuilding != nullptr && rootBuilding->isPrivateStructure()) {
					leash();
					return setDestination();
				}
			}
		}

		PatrolPoint nextPos = followCopy->getPosition();

		if (peekBlackboard("formationOffset") && !isInCombat()) {
			Vector3 formationOffset = readBlackboard("formationOffset").get<Vector3>();
			float directionAngle = followCopy->getDirection()->getRadians();
			float xRotated = (formationOffset.getX() * Math::cos(directionAngle) + formationOffset.getY() * Math::sin(directionAngle));
			float yRotated = (-formationOffset.getX() * Math::sin(directionAngle) + formationOffset.getY() * Math::cos(directionAngle));

			nextPos.setPositionX(nextPos.getPositionX() + xRotated);
			nextPos.setPositionY(nextPos.getPositionY() + yRotated);
		} else {
			checkNewAngle();
		}

		setNextPosition(nextPos.getPositionX(), nextPos.getPositionZ(), nextPos.getPositionY(), followCopy->getParent().get().castTo<CellObject*>());
		break;
	}
	case AiAgent::EVADING:
		if (followCopy == nullptr || getPatrolPointSize() == 0) {
			setMovementState(AiAgent::PATHING_HOME);
			return setDestination();
		}

		break;
	case AiAgent::PATHING_HOME: {
		clearPatrolPoints();

		if (creatureBitmask & CreatureFlag::STATIC || homeLocation.getCell() != nullptr || getParent().get() != nullptr) {
			if (!homeLocation.isInRange(asAiAgent(), 1.f)) {
				homeLocation.setReached(false);
				addPatrolPoint(homeLocation);
			} else {
				float dirDiff = fabs(getDirectionAngle() - homeLocation.getDirection());

				if (dirDiff >= 0.5) {
					setDirection(Math::deg2rad(homeLocation.getDirection()));
					broadcastNextPositionUpdate(&homeLocation);
				}

				setOblivious();
				homeLocation.setReached(true);
			}
		} else {
			homeLocation.setReached(true);
			setOblivious();
		}

		break;
	}
	case AiAgent::MOVING_TO_HEAL: {
		if (!peekBlackboard("healTarget")) {
			if (followCopy != nullptr) {
				setMovementState(AiAgent::FOLLOWING);
			} else {
				setMovementState(AiAgent::PATHING_HOME);
			}
		} else {
			ManagedReference<CreatureObject*> healTarget = readBlackboard("healTarget").get<ManagedReference<CreatureObject*> >().get();

			if (healTarget != nullptr) {
				clearPatrolPoints();
				Vector3 targetPos = healTarget->getPosition();
				setNextPosition(targetPos.getX(), targetPos.getZ(), targetPos.getY(), healTarget->getParent().get().castTo<CellObject*>());
			}
		}
		break;
	}
	default:
		if (creatureBitmask & CreatureFlag::STATIC || homeLocation.getCell() != nullptr) {
			setMovementState(AiAgent::PATHING_HOME);
		} else if (followCopy == nullptr) {
			setMovementState(AiAgent::PATROLLING);
		}
		break;
	}

	//info("setDestination end " + String::valueOf(getPatrolPointSize()), true);

	return getPatrolPointSize();
}

bool AiAgentImplementation::completeMove() {
	if (!nextStepPosition.isReached()) {
		updateCurrentPosition(&nextStepPosition);

		nextStepPosition.setReached(true);
	}

	return true;
}

void AiAgentImplementation::setWait(int wait) {
	cooldownTimerMap->updateToCurrentAndAddMili("waitTimer", wait);
}

void AiAgentImplementation::stopWaiting() {
	if (peekBlackboard("isWaiting"))
		eraseBlackboard("isWaiting");
	cooldownTimerMap->updateToCurrentTime("waitTimer");
}

bool AiAgentImplementation::isWaiting() const {
	return !cooldownTimerMap->isPast("waitTimer");
}

bool AiAgentImplementation::isCamouflaged(CreatureObject* creature) {
	if (creature == nullptr)
		return false;

	Locker locker(&targetMutex);

	CreatureObject* effectiveTarget = creature;

	if (creature->isVehicleObject() || creature->isMount()) {
		effectiveTarget = creature->getSlottedObject("rider").castTo<CreatureObject*>();
	}

	if (effectiveTarget == nullptr || !effectiveTarget->isPlayerCreature())
		return false;

	uint32 concealCRC = STRING_HASHCODE("skill_buff_mask_scent");

	bool concealed = effectiveTarget->hasBuff(concealCRC);

	if ((!concealed && !isMonster()) || isPet() || isDroid() || isAndroid())
		return false;

	bool scentMasked = effectiveTarget->hasBuff(STRING_HASHCODE("skill_buff_mask_scent_self"));
	uint64 effectiveTargetID = effectiveTarget->getObjectID();

	if (!concealed && !scentMasked) {
		camouflagedObjects.drop(effectiveTargetID);
		return false;
	}

	// Don't check if it's already been checked
	if (camouflagedObjects.contains(effectiveTargetID))
		return true;

	if (!isStalker() && !isAggressiveTo(effectiveTarget))
		return false;

	StringBuffer camoDebug;

	int concealMod = 0;

	if (concealed) {
		ConcealBuff* concealBuff = cast<ConcealBuff*>(effectiveTarget->getBuff(concealCRC));

		if (concealBuff == nullptr)
			return false;

		String buffPlanet = concealBuff->getPlanetName();

		if (buffPlanet != getZoneUnsafe()->getZoneName())
			return false;

		concealMod = effectiveTarget->getSkillModFromBuffs("private_conceal");

		camoDebug << "Concealed = true. Conceal Mod = " << concealMod <<". ";
	}

	int mod = 0;

	if (concealed) {
		mod = concealMod;

		if (concealMod > 0) {
			mod += effectiveTarget->getSkillMod("camouflage") / 2;
		}
	} else {
		mod = effectiveTarget->getSkillMod("mask_scent");

		if (mod > 0)
			mod /= 2;
	}

	camoDebug << " Initial Mod = " << mod << ". ";

	if (mod < 5)
		return false;

	PlayerManager* playerMan = server->getPlayerManager();

	if (playerMan == nullptr)
		return false;

	int playerLevel = playerMan->calculatePlayerLevel(effectiveTarget);
	int creatureLevel = getLevel();

	if (effectiveTarget->isGrouped()) {
		Reference<GroupObject*> group = effectiveTarget->getGroup();

		if (group != nullptr) {
			Locker locker(group);
			playerLevel += group->getGroupLevel(false);
		}
	}

	camoDebug << " Player Level = " << playerLevel << ".  Creature Level = " << creatureLevel << ". ";

	if ((playerLevel - creatureLevel) >= 10) {
#ifdef DEBUG_CAMOUFLAGE
		effectiveTarget->sendSystemMessage(camoDebug.toString());
#endif
		return true;
	}

	float roll = (100 + mod) - creatureLevel;

	camoDebug << " Initial Roll = " << roll << ". ";

	if (effectiveTarget->getPosture() == CreaturePosture::PRONE) {
		roll += 15;
	}

	if (effectiveTarget->isRunning()) {
		roll -= 10;
	} else if (effectiveTarget->isWalking()) {
		roll -= 5;
	}

	if (creatureLevel > (2 * mod))
		roll -= 20;

	if (concealed) {
		if (roll > 98)
			roll = 98;
	} else {
		if (roll > 95)
			roll = 95;
	}

	if (!isMonster())
		roll -= 5;

	camoDebug << "Roll after calcs = " << roll << ". ";

	bool success = (System::random(100) +1) < roll ? true : false;

	if (success) {
		camouflagedObjects.put(effectiveTargetID);

		camoDebug << "Success";
	} else {
		camouflagedObjects.drop(effectiveTargetID);

		camoDebug << "Failure";
	}

#ifdef DEBUG_CAMOUFLAGE
	effectiveTarget->sendSystemMessage(camoDebug.toString());
#endif

	Reference<Task*> camoTask = new CamoTask(effectiveTarget, asAiAgent(), !concealed, success);
	camoTask->execute();

	return success;
}

void AiAgentImplementation::activateMovementEvent() {
	if (getZoneUnsafe() == nullptr || !(getOptionsBitmask() & OptionBitmask::AIENABLED))
		return;

	const static uint64 minScheduleTime = 100;

	Locker locker(&movementEventMutex);

	if (numberOfPlayersInRange.get() <= 0 && getFollowObject().get() == nullptr && !isRetreating()) {
		if (moveEvent != nullptr) {
			moveEvent->clearCreatureObject();
			moveEvent = nullptr;
		}

		return;
	}

	if (moveEvent == nullptr) {
		moveEvent = new AiMoveEvent(asAiAgent());

		moveEvent->schedule(nextMovementInterval);
	}

	try {
		if (!moveEvent->isScheduled())
			moveEvent->schedule(nextMovementInterval);
	} catch (IllegalArgumentException& e) {

	}

	if (isPet()) {
		updatePetSwimmingState();
	}

	nextMovementInterval = UPDATEMOVEMENTINTERVAL;
}

void AiAgentImplementation::setNextPosition(float x, float z, float y, CellObject* cell) {
	//info("setNextPosition(" + String::valueOf(x) + ", " + String::valueOf(z) + ", " + String::valueOf(y) + ")", true);

	Locker locker(&targetMutex);

	PatrolPoint point(x, z, y, cell);

	patrolPoints.add(0, point);
}

void AiAgentImplementation::setNextStepPosition(float x, float z, float y, CellObject* cell) {
	Locker locker(&targetMutex);

	PatrolPoint point(x, z, y, cell);

	nextStepPosition = point;
}

void AiAgentImplementation::broadcastNextPositionUpdate(PatrolPoint* point) {
	BasePacket* msg = nullptr;
	++movementCounter;

	if (point == nullptr) {
		if (parent.get() != nullptr)
			msg = new UpdateTransformWithParentMessage(asAiAgent());
		else
			msg = new UpdateTransformMessage(asAiAgent());
	} else {
		if (point->getCell() != nullptr) {
			msg = new LightUpdateTransformWithParentMessage(asAiAgent(), point->getPositionX(), point->getPositionZ(), point->getPositionY(), point->getCell()->getObjectID());
		} else {
			msg = new LightUpdateTransformMessage(asAiAgent(), point->getPositionX(), point->getPositionZ(), point->getPositionY());
		}
	}

 	broadcastMessage(msg, false);
}

int AiAgentImplementation::notifyObjectDestructionObservers(TangibleObject* attacker, int condition, bool isCombatAction) {
	sendReactionChat(attacker, ReactionManager::DEATH);

	if (isPet()) {
		PetManager* petManager = getZoneServer()->getPetManager();

		petManager->notifyDestruction(attacker, asAiAgent(), condition, isCombatAction);

	} else {
		if (getZoneUnsafe() != nullptr) {
			CreatureManager* creatureManager = getZoneUnsafe()->getCreatureManager();

			creatureManager->notifyDestruction(attacker, asAiAgent(), condition, isCombatAction);
		}
	}

	return CreatureObjectImplementation::notifyObjectDestructionObservers(attacker, condition, isCombatAction);
}

int AiAgentImplementation::notifyConverseObservers(CreatureObject* converser) {
	notifyObservers(ObserverEventType::CONVERSE, converser);

	return 1;
}

int AiAgentImplementation::inflictDamage(TangibleObject* attacker, int damageType, float damage, bool destroy, bool notifyClient, bool isCombatAction) {
	lastDamageReceived.updateToCurrentTime();

	activateRecovery();

	if (damage > 0) {
		// This damage is DOT or other types of non direct combat damage, it should not count towards loot and thus not be added to the threat map damage.
		// Adding aggro should still be done.
		getThreatMap()->addAggro(attacker, 1);
	}

	notifyObservers(ObserverEventType::DAMAGERECEIVED, attacker);
	return CreatureObjectImplementation::inflictDamage(attacker, damageType, damage, destroy, notifyClient, isCombatAction);
}

int AiAgentImplementation::inflictDamage(TangibleObject* attacker, int damageType, float damage, bool destroy, const String& xp, bool notifyClient, bool isCombatAction) {
	lastDamageReceived.updateToCurrentTime();

	activateRecovery();

	if (damage > 0) {
		getThreatMap()->addDamage(attacker, damage, xp);
	}

	notifyObservers(ObserverEventType::DAMAGERECEIVED, attacker);

	return CreatureObjectImplementation::inflictDamage(attacker, damageType, damage, destroy, notifyClient, isCombatAction);
}

void AiAgentImplementation::notifyPackMobs(SceneObject* attacker) {
	if (lastPackNotify.miliDifference() < 2000)
		return;

	auto closeObjectsVector = getCloseObjects();
	Vector<QuadTreeEntry*> closeObjects(closeObjectsVector->size(), 10);
	closeObjectsVector->safeCopyReceiversTo(closeObjects, CloseObjectsVector::CREOTYPE);
	uint32 socialGroup = getSocialGroup().toLowerCase().hashCode();

	for (int i = 0; i < closeObjects.size(); ++i) {
		SceneObject* object = static_cast<SceneObject*>(closeObjects.get(i));

		if (!object->isCreatureObject())
			continue;

		CreatureObject* creo = object->asCreatureObject();

		if (creo == nullptr || creo->isDead() || creo == asAiAgent() || creo->isPlayerCreature() || creo->isInCombat())
			continue;

		if (creo->getParentID() != getParentID())
			continue;

		if (!(creo->getPvpStatusBitmask() & CreatureFlag::ATTACKABLE))
			continue;

		AiAgent* agent = creo->asAiAgent();

		if (!(agent->getCreatureBitmask() & CreatureFlag::PACK))
			continue;

		String targetSocialGroup = agent->getSocialGroup().toLowerCase();

		if (targetSocialGroup.isEmpty() || targetSocialGroup.hashCode() != socialGroup)
			continue;

		float packRange = 20.f + (getLevel() / 100.f);

		if (getPvpStatusBitmask() & CreatureFlag::AGGRESSIVE)
			packRange += 5.f;

		if (!agent->isInRange(asAiAgent(), packRange))
			continue;

		if (!CollisionManager::checkLineOfSight(asAiAgent(), creo))
			continue;

		Core::getTaskManager()->executeTask([=] () {
			Locker locker(agent);

			agent->showFlyText("npc_reaction/flytext", "threaten", 0xFF, 0, 0);
			agent->addDefender(attacker);
		}, "PackAttackLambda");
	}

	lastPackNotify.updateToCurrentTime();
}

void AiAgentImplementation::fillAttributeList(AttributeListMessage* alm, CreatureObject* player) {

	if (isDead()) {
		return;
	}

	if (getArmor() == 0)
		alm->insertAttribute("armorrating", "None");
	else if (getArmor() == 1)
		alm->insertAttribute("armorrating", "Light");
	else if (getArmor() == 2)
		alm->insertAttribute("armorrating", "Medium");
	else if (getArmor() == 3)
		alm->insertAttribute("armorrating", "Heavy");

	if (isSpecialProtection(SharedWeaponObjectTemplate::KINETIC)) {
		StringBuffer txt;
		txt << Math::getPrecision(getKinetic(), 1) << "%";
		alm->insertAttribute("cat_armor_special_protection.armor_eff_kinetic", txt.toString());
	}

	if (isSpecialProtection(SharedWeaponObjectTemplate::ENERGY)) {
		StringBuffer txt;
		txt << Math::getPrecision(getEnergy(), 1) << "%";
		alm->insertAttribute("cat_armor_special_protection.armor_eff_energy", txt.toString());
	}

	if (isSpecialProtection(SharedWeaponObjectTemplate::ELECTRICITY)) {
		StringBuffer txt;
		txt << Math::getPrecision(getElectricity(), 1) << "%";
		alm->insertAttribute("cat_armor_special_protection.armor_eff_elemental_electrical", txt.toString());
	}

	if (isSpecialProtection(SharedWeaponObjectTemplate::STUN)) {
		StringBuffer txt;
		txt << Math::getPrecision(getStun(), 1) << "%";
		alm->insertAttribute("cat_armor_special_protection.armor_eff_stun", txt.toString());
	}

	if (isSpecialProtection(SharedWeaponObjectTemplate::BLAST)) {
		StringBuffer txt;
		txt << Math::getPrecision(getBlast(), 1) << "%";
		alm->insertAttribute("cat_armor_special_protection.armor_eff_blast", txt.toString());
	}

	if (isSpecialProtection(SharedWeaponObjectTemplate::HEAT)) {
		StringBuffer txt;
		txt << Math::getPrecision(getHeat(), 1) << "%";
		alm->insertAttribute("cat_armor_special_protection.armor_eff_elemental_heat", txt.toString());
	}

	if (isSpecialProtection(SharedWeaponObjectTemplate::COLD)) {
		StringBuffer txt;
		txt << Math::getPrecision(getCold(), 1) << "%";
		alm->insertAttribute("cat_armor_special_protection.armor_eff_elemental_cold", txt.toString());
	}

	if (isSpecialProtection(SharedWeaponObjectTemplate::ACID)) {
		StringBuffer txt;
		txt << Math::getPrecision(getAcid(), 1) << "%";
		alm->insertAttribute("cat_armor_special_protection.armor_eff_elemental_acid", txt.toString());
	}

	if (isSpecialProtection(SharedWeaponObjectTemplate::LIGHTSABER)) {
		StringBuffer txt;
		txt << Math::getPrecision(getLightSaber(), 1) << "%";
		alm->insertAttribute("cat_armor_special_protection.armor_eff_restraint", txt.toString());
	}

	if (getKinetic() > 0 && !isSpecialProtection(SharedWeaponObjectTemplate::KINETIC)) {
		StringBuffer txt;
		txt << Math::getPrecision(getKinetic(), 1) << "%";
		alm->insertAttribute("cat_armor_effectiveness.armor_eff_kinetic", txt.toString());
	}

	if (getEnergy() > 0 && !isSpecialProtection(SharedWeaponObjectTemplate::ENERGY)) {
		StringBuffer txt;
		txt << Math::getPrecision(getEnergy(), 1) << "%";
		alm->insertAttribute("cat_armor_effectiveness.armor_eff_energy", txt.toString());
	}

	if (getElectricity() > 0 && !isSpecialProtection(SharedWeaponObjectTemplate::ELECTRICITY)) {
		StringBuffer txt;
		txt << Math::getPrecision(getElectricity(), 1) << "%";
		alm->insertAttribute("cat_armor_effectiveness.armor_eff_elemental_electrical", txt.toString());
	}

	if (getStun() > 0 && !isSpecialProtection(SharedWeaponObjectTemplate::STUN)) {
		StringBuffer txt;
		txt << Math::getPrecision(getStun(), 1) << "%";
		alm->insertAttribute("cat_armor_effectiveness.armor_eff_stun", txt.toString());
	}

	if (getBlast() > 0 && !isSpecialProtection(SharedWeaponObjectTemplate::BLAST)) {
		StringBuffer txt;
		txt << Math::getPrecision(getBlast(), 1) << "%";
		alm->insertAttribute("cat_armor_effectiveness.armor_eff_blast", txt.toString());
	}

	if (getHeat() > 0 && !isSpecialProtection(SharedWeaponObjectTemplate::HEAT)) {
		StringBuffer txt;
		txt << Math::getPrecision(getHeat(), 1) << "%";
		alm->insertAttribute("cat_armor_effectiveness.armor_eff_elemental_heat", txt.toString());
	}

	if (getCold() > 0 && !isSpecialProtection(SharedWeaponObjectTemplate::COLD)) {
		StringBuffer txt;
		txt << Math::getPrecision(getCold(), 1) << "%";
		alm->insertAttribute("cat_armor_effectiveness.armor_eff_elemental_cold", txt.toString());
	}

	if (getAcid() > 0 && !isSpecialProtection(SharedWeaponObjectTemplate::ACID)) {
		StringBuffer txt;
		txt << Math::getPrecision(getAcid(), 1) << "%";
		alm->insertAttribute("cat_armor_effectiveness.armor_eff_elemental_acid", txt.toString());
	}

	if (getLightSaber() > 0 && !isSpecialProtection(SharedWeaponObjectTemplate::LIGHTSABER)) {
		StringBuffer txt;
		txt << Math::getPrecision(getLightSaber(), 1) << "%";
		alm->insertAttribute("cat_armor_effectiveness.armor_eff_restraint", txt.toString());
	}

	if (getKinetic() < 0)
		alm->insertAttribute("cat_armor_vulnerability.armor_eff_kinetic", "-");

	if (getEnergy() < 0)
		alm->insertAttribute("cat_armor_vulnerability.armor_eff_energy", "-");

	if (getElectricity() < 0)
		alm->insertAttribute("cat_armor_vulnerability.armor_eff_elemental_electrical", "-");

	if (getStun() < 0)
		alm->insertAttribute("cat_armor_vulnerability.armor_eff_stun", "-");

	if (getBlast() < 0)
		alm->insertAttribute("cat_armor_vulnerability.armor_eff_blast", "-");

	if (getHeat() < 0)
		alm->insertAttribute("cat_armor_vulnerability.armor_eff_elemental_heat", "-");

	if (getCold() < 0)
		alm->insertAttribute("cat_armor_vulnerability.armor_eff_elemental_cold", "-");

	if (getAcid() < 0)
		alm->insertAttribute("cat_armor_vulnerability.armor_eff_elemental_acid", "-");

	if (getLightSaber() < 0)
		alm->insertAttribute("cat_armor_vulnerability.armor_eff_restraint", "-");

	if (isPet())
	{
		ManagedReference<CreatureObject*> owner = getLinkedCreature().get();

		if (owner != nullptr)
		{
			StringBuffer fullName;
			fullName << owner->getFirstName();
			if(!owner->getLastName().isEmpty())
				fullName << " " << owner->getLastName();

			alm->insertAttribute("@obj_attr_n:owner", fullName.toString());
		}
	}

	if (player->getPlayerObject() && player->getPlayerObject()->hasGodMode()) {
		ManagedReference<SceneObject*> home = homeObject.get();

		if (home != nullptr) {
			int type = 0;
			if (home->getObserverCount(ObserverEventType::OBJECTDESTRUCTION) > 0)
				type = ObserverEventType::OBJECTDESTRUCTION;
			else if (home->getObserverCount(ObserverEventType::CREATUREDESPAWNED) > 0)
				type = ObserverEventType::CREATUREDESPAWNED;

			if (type != 0) {
				ManagedReference<SpawnObserver*> spawnObserver = nullptr;
				SortedVector<ManagedReference<Observer*> > observers = home->getObservers(type);

				for (int i = 0; i < observers.size(); i++) {
					spawnObserver = cast<SpawnObserver*>(observers.get(i).get());
					if (spawnObserver != nullptr)
						break;
				}

				if (spawnObserver) {
					String name = spawnObserver->getLairTemplateName();
					alm->insertAttribute("blank_entry" , "");
					alm->insertAttribute("object_type" , name);
					alm->insertAttribute("blank_entry" , "");
				}
			}
		}
	}
}

bool AiAgentImplementation::sendConversationStartTo(SceneObject* player) {
	if (!player->isPlayerCreature() || isDead() || convoTemplateCRC == 0)
		return false;

	//Face player.
	faceObject(player);

	PatrolPoint current(coordinates.getPosition(), getParent().get().castTo<CellObject*>());

	broadcastNextPositionUpdate(&current);

	CreatureObject* playerCreature = cast<CreatureObject*>( player);

	ConversationTemplate* conversationTemplate = CreatureTemplateManager::instance()->getConversationTemplate(convoTemplateCRC);

	if (conversationTemplate == nullptr) {
		error("Could not find the conversation template.");
		return false;
	}

	if (conversationTemplate->getConversationTemplateType() == ConversationTemplate::ConversationTemplateTypeLua && conversationTemplate->getLuaClassHandler() == "trainerConvHandler") {
		ManagedReference<CityRegion*> city = player->getCityRegion().get();

		if (city != nullptr && !city->isClientRegion() && city->isBanned(player->getObjectID())) {
			playerCreature->sendSystemMessage("@city/city:banned_services"); // You are banned from using this city's services.
			return false;
		}
	}

	StartNpcConversation* conv = new StartNpcConversation(playerCreature, getObjectID(), "");
	player->sendMessage(conv);

	SortedVector<ManagedReference<Observer*> > observers = getObservers(ObserverEventType::STARTCONVERSATION);

	for (int i = 0;  i < observers.size(); ++i) {
		if (dynamic_cast<ConversationObserver*>(observers.get(i).get()) != nullptr)
			return true;
	}

	//Create conversation observer.
	ConversationObserver* conversationObserver = ConversationManager::instance()->getConversationObserver(convoTemplateCRC);

	if (conversationObserver != nullptr) {
		//Register observers.
		registerObserver(ObserverEventType::CONVERSE, conversationObserver);
		registerObserver(ObserverEventType::STARTCONVERSATION, conversationObserver);
		registerObserver(ObserverEventType::SELECTCONVERSATION, conversationObserver);
		registerObserver(ObserverEventType::STOPCONVERSATION, conversationObserver);
	} else {
		error("Could not create conversation observer.");
		return false;
	}

	return true;
}

bool AiAgentImplementation::isAggressiveTo(CreatureObject* target) {
	if (target->isIncapacitated() || !isAttackableBy(target) || !target->isAttackableBy(asAiAgent()) || target->isVehicleObject())
		return false;

	if (getParentID() != 0 && getParentID() != target->getParentID()) {
		Reference<CellObject*> curCell = getParent().get().castTo<CellObject*>();

		if (curCell != nullptr) {
			auto perms = curCell->getContainerPermissions();

			if (!perms->hasInheritPermissionsFromParent()) {
				if (!curCell->checkContainerPermission(target, ContainerPermissions::WALKIN)) {
					return false;
				}
			}
		}
	}

	// grab the GCW faction
	uint32 targetFaction = target->getFaction();
	PlayerObject* ghost = target->getPlayerObject();

	if (ghost != nullptr && ghost->hasCrackdownTefTowards(getFaction())) {
		return true;
	}

	// check the GCW factions if both entities have one
	if (getFaction() != 0 && targetFaction != 0) {

		// this is basically the isEnemy check, but with the GCW faction (they should both return the same thing)
		if (ghost == nullptr && (targetFaction != getFaction()))
			return true;
		// this is the same thing, but ensures that if the target is a player, that they aren't on leave
		else if (ghost != nullptr && (targetFaction != getFaction()) && target->getFactionStatus() != FactionStatus::ONLEAVE)
			return true;
	}

	// now grab the generic faction (which could include imp/reb)
	String factionString = getFactionString();

	if (!factionString.isEmpty()) {
		// for players, we are only an enemy if the standing is less than -3000, but we are
		// forced to non-aggressive status if the standing is over 3000, otherwise use the
		// pvpStatusBitmask to determine aggressiveness
		if (target->isPlayerCreature() && ghost != nullptr && !(getOptionsBitmask() & CreatureFlag::IGNORE_FACTION_STANDING)) {
			float targetsStanding = ghost->getFactionStanding(factionString);

			if (targetsStanding <= -3000)
				return true;
			else if (targetsStanding >= 3000)
				return false;

		// AI can check the enemy strings directly vs other AI (since they don't have a
		// standing)
		} else if (target->isAiAgent()) {
			AiAgent* targetAi = target->asAiAgent();

			if (targetAi != nullptr && FactionManager::instance()->isEnemy(factionString, targetAi->getFactionString()))
				return true;
		}
	}

	if (isCarnivore() && target->isAiAgent()) {
		AiAgent* targetAi = target->asAiAgent();

		if (targetAi != nullptr && targetAi->isHerbivore())
			return true;
	}

	// if we've made it this far then the target is a valid target, but we will only be aggressive based on the pvpStatusBitmask
	return getPvpStatusBitmask() & CreatureFlag::AGGRESSIVE;
}

bool AiAgentImplementation::hasLoot(){
	SceneObject* inventory = asAiAgent()->getSlottedObject("inventory");

	if(inventory == nullptr)
		return false;

	return inventory->getContainerObjectsSize() > 0;
}

void AiAgentImplementation::sendDefaultConversationTo(SceneObject* player) {
}

void AiAgentImplementation::selectConversationOption(int option, SceneObject* obj) {
}

bool AiAgentImplementation::isEventMob() const {
	if (getDisplayedName().contains(" (event)"))
		return true;

	return false;
}

void AiAgentImplementation::setCombatState() {
	CreatureObjectImplementation::setCombatState();

	ManagedReference<SceneObject*> home = homeObject.get();

	if (home != nullptr)
		home->notifyObservers(ObserverEventType::AIMESSAGE, asAiAgent(), ObserverEventType::STARTCOMBAT);

	notifyObservers(ObserverEventType::STARTCOMBAT, asAiAgent());

	ManagedReference<SceneObject*> followCopy = getFollowObject().get();
	if (followCopy != nullptr && followCopy->isTangibleObject()) {
		ManagedReference<TangibleObject*> target = cast<TangibleObject*>(followCopy.get());
		ManagedReference<AiAgent*> ai = asAiAgent();

		Core::getTaskManager()->executeTask([=] () {
			Locker locker(ai);
			Locker clocker(target, ai);

			if (target->hasDefender(ai))
				ai->sendReactionChat(followCopy, ReactionManager::ATTACKED);
		}, "SendAttackedChatLambda");
	}
}

bool AiAgentImplementation::hasRangedWeapon() {
	return (primaryWeapon != nullptr && primaryWeapon->isRangedWeapon()) || (secondaryWeapon != nullptr && secondaryWeapon->isRangedWeapon());
}

bool AiAgentImplementation::getUseRanged() {
	if (isPet()) {
		ManagedReference<PetControlDevice*> pcd = getControlDevice().get().castTo<PetControlDevice*>();

		if (pcd != nullptr && pcd->getUseRanged()) {
			return true;
		}
	}

	return false;
}

bool AiAgentImplementation::hasSpecialAttack(int num) {
	const CreatureAttackMap* attackMap = getAttackMap();
	if (attackMap == nullptr) {
		return false;
	}

	if (num == 0 || (num > attackMap->size())) {
		return false;
	}

	String cmd = attackMap->getCommand(num - 1);

	if (cmd.isEmpty()) {
		return false;
	}

	return true;
}

bool AiAgentImplementation::isAttackableBy(TangibleObject* object) {
	if (object == nullptr)
		return false;

	if (object->isCreatureObject())
		return isAttackableBy(object->asCreatureObject());

	if (isDead() || isIncapacitated() || getMovementState() == AiAgent::LEASHING)
		return false;

	if (isPet()) {
		ManagedReference<PetControlDevice*> pcd = getControlDevice().get().castTo<PetControlDevice*>();

		if (pcd != nullptr && pcd->getPetType() == PetManager::FACTIONPET && object->isNeutral())
			return false;

		ManagedReference<CreatureObject*> owner = getLinkedCreature().get();

		if (owner == nullptr)
			return false;

		return owner->isAttackableBy(object, true);
	}

	if (pvpStatusBitmask == 0)
		return false;

	unsigned int targetFaction = object->getFaction();

	if (targetFaction != 0 && getFaction() != 0) {
		if (targetFaction == getFaction()) {
			return false;
		}
	}

	return true;
}

bool AiAgentImplementation::isAttackableBy(CreatureObject* object) {
	if (object == nullptr || object == asAiAgent())
		return false;

	if (isDead() || isIncapacitated() || getMovementState() == AiAgent::LEASHING)
		return false;

	if (isPet()) {
		ManagedReference<PetControlDevice*> pcd = getControlDevice().get().castTo<PetControlDevice*>();
		if (pcd != nullptr && pcd->getPetType() == PetManager::FACTIONPET && object->isNeutral()) {
			return false;
		}

		ManagedReference<CreatureObject*> owner = getLinkedCreature().get();

		if (owner == nullptr) {
			return false;
		}

		return owner->isAttackableBy(object, true);
	}

	if (object->isPet() || object->isVehicleObject()) {
		ManagedReference<PetControlDevice*> pcd = object->getControlDevice().get().castTo<PetControlDevice*>();

		if (pcd != nullptr && pcd->getPetType() == PetManager::FACTIONPET && isNeutral())
			return false;

		ManagedReference<CreatureObject*> owner = object->getLinkedCreature().get();

		if (owner == nullptr)
			return false;

		return isAttackableBy(owner);
	}

	if (pvpStatusBitmask == 0)
		return false;

	if (object->isPlayerCreature()) {
		Reference<PlayerObject*> ghost = object->getPlayerObject();
		if (ghost != nullptr && ghost->hasCrackdownTefTowards(getFaction())) {
			return true;
		}
	}

	unsigned int targetFaction = object->getFaction();

	if (getFaction() != 0) {
		if (targetFaction == getFaction())
			return false;

		if (targetFaction == 0 || (object->isPlayerCreature() && object->getFactionStatus() == FactionStatus::ONLEAVE))
			return false;
	}

	if (object->isAiAgent()) {
		if ((creatureBitmask & CreatureFlag::NOAIAGGRO) && !object->isPet())
			return false;

		AiAgent* ai = object->asAiAgent();

		const CreatureTemplate* targetTemplate = ai->getCreatureTemplate();

		if ((npcTemplate.get() != nullptr && targetTemplate != nullptr) && (npcTemplate->getTemplateName() == targetTemplate->getTemplateName()))
			return false;

		String targetSocialGroup = ai->getSocialGroup().toLowerCase();

		if (!targetSocialGroup.isEmpty() && targetSocialGroup != "self" && targetSocialGroup == getSocialGroup().toLowerCase())
			return false;

		uint32 targetLairTemplateCRC = ai->getLairTemplateCRC();

		if (targetLairTemplateCRC != 0 && targetLairTemplateCRC == getLairTemplateCRC())
			return false;
	}

	return true;
}

void AiAgentImplementation::restoreFollowObject() {
	Locker locker(&targetMutex);
	ManagedReference<SceneObject*> obj = followStore.get();
	locker.release();
	if (obj == nullptr) {
		setMovementState(AiAgent::PATHING_HOME);
		return;
	} else if (getCloseObjects() != nullptr && !getCloseObjects()->contains(obj.get())) {
		setMovementState(AiAgent::PATHING_HOME);
		return;
	} else if (obj->isCreatureObject() && obj->asCreatureObject()->isInvisible()) {
		setMovementState(AiAgent::PATHING_HOME);
		return;
	} else {
		setFollowObject(obj);
	}
}
String AiAgentImplementation::getPersonalityStf() {
	if (npcTemplate == nullptr)
		return "";
	else
		return npcTemplate->getPersonalityStf();
}

void AiAgentImplementation::sendReactionChat(SceneObject* object, int type, int state, bool force) {
	if (object == nullptr || (!getCooldownTimerMap()->isPast("reaction_chat") && !force) || getZoneUnsafe() == nullptr || !isNpc() || isDead()) {
		return;
	}

	ReactionManager* reactionManager = getZoneServer()->getReactionManager();

	if (reactionManager != nullptr)
		reactionManager->sendChatReaction(asAiAgent(), object, type, state, force);
}

void AiAgentImplementation::setMaxHAM(int type, int value, bool notifyClient) {
		CreatureObjectImplementation::setMaxHAM(type, value, notifyClient);
		activateRecovery();
	}

float AiAgentImplementation::getEffectiveResist() {
	if (!isSpecialProtection(SharedWeaponObjectTemplate::ACID) && getAcid() > 0)
		return getAcid();
	if (!isSpecialProtection(SharedWeaponObjectTemplate::BLAST) && getBlast() > 0)
		return getBlast();
	if (!isSpecialProtection(SharedWeaponObjectTemplate::COLD) && getCold() > 0)
		return getCold();
	if (!isSpecialProtection(SharedWeaponObjectTemplate::ELECTRICITY) && getElectricity() > 0)
		return getElectricity();
	if (!isSpecialProtection(SharedWeaponObjectTemplate::ENERGY) && getEnergy() > 0)
		return getEnergy();
	if (!isSpecialProtection(SharedWeaponObjectTemplate::HEAT) && getHeat() > 0)
		return getHeat();
	if (!isSpecialProtection(SharedWeaponObjectTemplate::KINETIC) && getKinetic() > 0)
		return getKinetic();
	if (!isSpecialProtection(SharedWeaponObjectTemplate::LIGHTSABER) && getLightSaber() > 0)
		return getLightSaber();
	if (!isSpecialProtection(SharedWeaponObjectTemplate::STUN) && getStun() > 0)
		return getStun();
	return 0;
}

void AiAgentImplementation::setPatrolPoints(PatrolPointsVector& pVector) {
	Locker locker(&targetMutex);
	patrolPoints = pVector;
}

AiAgent* AiAgentImplementation::asAiAgent() {
	return _this.getReferenceUnsafeStaticCast();
}

AiAgent* AiAgent::asAiAgent() {
	return this;
}

void AiAgentImplementation::reloadTemplate() {
	clearBuffs(false, false);
	loadTemplateData(npcTemplate);

	if (isMount()) {
		setOptionBit(0x1000);
	}
}

void AiAgentImplementation::setConvoTemplate(const String& templateString) {
	uint32 templateCRC = templateString.hashCode();

	ConversationTemplate* conversationTemplate = CreatureTemplateManager::instance()->getConversationTemplate(templateCRC);

	if (conversationTemplate == nullptr) {
		error("Unable to find conversation template " + templateString);
		return;
	}

	convoTemplateCRC = templateCRC;
}

void AiAgentImplementation::setCreatureBit(uint32 option) {
	if (!(creatureBitmask & option)) {
		creatureBitmask = creatureBitmask | option;
	}
}

void AiAgentImplementation::clearCreatureBit(uint32 option) {
	if (creatureBitmask & option) {
		creatureBitmask = creatureBitmask & ~option;
	}
}

bool AiAgentImplementation::isPet() const {
	return (getControlDevice() != nullptr);
}

void AiAgentImplementation::writeBlackboard(const String& key, const BlackboardData& data) {
	blackboard.drop(key);
	blackboard.put(key, data);
}

String AiAgentImplementation::getErrorContext() {
	auto zone = getZone();

	StringBuffer msg;

	msg << "AiAgentImplementation" << ": " << getObjectID() << "; '" << getDisplayedName() << "';";

	msg << " Health: " << getHAM(CreatureAttribute::HEALTH) << ";";
	msg << " Action: " << getHAM(CreatureAttribute::ACTION) << ";";
	msg << " Mind: " << getHAM(CreatureAttribute::MIND) << ";";
	msg << " posture: " << CreaturePosture::postureToString(posture) << ";";
	msg << " Zone: " << (zone != nullptr ? zone->getZoneName() : "nullptr") << ";";
	msg << " at: " << getWorldPosition().toString();

	return msg.toString();
}
