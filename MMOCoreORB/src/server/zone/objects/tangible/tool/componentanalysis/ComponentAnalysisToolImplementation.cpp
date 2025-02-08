/*
 * ComponentAnalysisToolImplementation.cpp
 */

#include "server/zone/objects/tangible/tool/componentanalysis/ComponentAnalysisTool.h"
#include "server/zone/objects/player/PlayerObject.h"
#include "server/zone/managers/loot/LootManager.h"
#include "server/zone/managers/player/PlayerManager.h"
#include "server/zone/objects/manufactureschematic/craftingvalues/CraftingValues.h"
#include "server/zone/packets/scene/AttributeListMessage.h"
#include "server/zone/objects/player/sui/listbox/SuiListBox.h"
#include "server/zone/packets/object/ObjectMenuResponse.h"
#include "server/zone/objects/ship/components/ShipComponent.h"
#include "server/zone/objects/ship/components/ShipArmorComponent.h"
#include "server/zone/objects/ship/components/ShipBoosterComponent.h"
#include "server/zone/objects/ship/components/ShipCapacitorComponent.h"
#include "server/zone/objects/ship/components/ShipDroidInterfaceComponent.h"
#include "server/zone/objects/ship/components/ShipEngineComponent.h"
#include "server/zone/objects/ship/components/ShipReactorComponent.h"
#include "server/zone/objects/ship/components/ShipShieldComponent.h"
#include "server/zone/objects/ship/components/ShipWeaponComponent.h"
#include "server/zone/objects/tangible/misc/SchematicFragment.h"
#include "server/zone/objects/player/sui/callbacks/ReverseEngineeringSuiCallback.h"

void ComponentAnalysisToolImplementation::initializePrivateData() {
	componentType = 0;
	engineeringLevel = 0;
	chargeCounter = 3;
	savedBaseComponent = nullptr;
}

void ComponentAnalysisToolImplementation::fillAttributeList(AttributeListMessage* alm, CreatureObject* object) {
	TangibleObjectImplementation::fillAttributeList(alm, object);

	alm->insertAttribute("@obj_attr_n:charges", chargeCounter);
}

void ComponentAnalysisToolImplementation::updateCraftingValues(CraftingValues* values, bool firstUpdate) {
	for (int i = 0; i < values->getTotalExperimentalAttributes(); ++i) {
		const auto& attribute = values->getAttribute(i);
		auto value = values->getCurrentValue(attribute);

		if (attribute == "charges") {
			chargeCounter = value;
			return;
		}
	}
}

void ComponentAnalysisToolImplementation::fillObjectMenuResponse(ObjectMenuResponse* menuResponse, CreatureObject* player) {
	menuResponse->addRadialMenuItem(20, 3, "@sui:analyze_loot");
}

int ComponentAnalysisToolImplementation::handleObjectMenuSelect(CreatureObject* player, byte selectedID) {
	if (selectedID == 20) {
		int componentCount = getContainerObjectsSize();

		if (componentCount == 0 || componentCount < engineeringLevel) {
			player->sendSystemMessage("@reverse_engineering_tool:too_few");
			return 0;
		}

		if (componentCount > engineeringLevel) {
			player->sendSystemMessage("@reverse_engineering_tool:too_many");
			return 0;
		}

		int skillMod = 0;

		switch (componentType) {
			case SceneObjectType::SCHEMATICFRAGMENT:
			case SceneObjectType::SHIPARMOR:
				skillMod = player->getSkillMod("engineering_reverse");
				break;

			case SceneObjectType::SHIPBOOSTER:
			case SceneObjectType::SHIPENGINE:
				skillMod = player->getSkillMod("propulsion_reverse");
				break;

			case SceneObjectType::SHIPDROIDINTERFACE:
			case SceneObjectType::SHIPREACTOR:
			case SceneObjectType::SHIPWEAPONCAPACITOR:
				skillMod = player->getSkillMod("systems_reverse");
				break;

			case SceneObjectType::SHIPSHIELDGENERATOR:
			case SceneObjectType::SHIPWEAPON:
				skillMod = player->getSkillMod("defense_reverse");
				break;
		}

		if (engineeringLevel > skillMod) {
			player->sendSystemMessage("@reverse_engineering_tool:not_skilled");
			return 0;
		}

		reverseEngineer(player);
	}

	return TangibleObjectImplementation::handleObjectMenuSelect(player, selectedID);
}

int ComponentAnalysisToolImplementation::canAddObject(SceneObject* object, int containmentType, String& errorDescription) {
	//first check - it must be a ship component
	if (!object->isShipComponentObject() && !object->isSchematicFragmentObject()) {
		errorDescription = "@reverse_engineering_tool:wrong_component_type";
		return TransferErrorCode::INVALIDTYPE;
	}

	//second check - if the tool is empty, the component can be loaded; other appropriate checks will run on RE attempt
	if (getContainerObjectsSize() == 0) {
		return 0;
	}

	//third check - component must match type already in tool
	if (object->getGameObjectType() != componentType) {
		errorDescription = "@reverse_engineering_tool:invalid";
		return TransferErrorCode::INVALIDTYPE;
	}

	//fourth check - make sure tool isn't full
	if (getContainerObjectsSize() >= getContainerVolumeLimit()) {
		errorDescription = "@container_error_message:container03"; //This container is full.
		return TransferErrorCode::CONTAINERFULL;
	}

	//differentiate on whether it's a schematic fragment or a ship component
	if (object->isSchematicFragmentObject()) {
		return 0;
	} else {
		//ship components must be of same RE level as those already in tool
		ShipComponent* component = cast<ShipComponent*>(object);

		if (component == nullptr || component->getReverseEngineeringLevel() != engineeringLevel) {
			errorDescription = "@reverse_engineering_tool:invalid";
			return TransferErrorCode::INVALIDTYPE;
		}
	}

	return 0;
}

int ComponentAnalysisToolImplementation::notifyObjectInserted(SceneObject* object) {
	//if this is the first item in the tool, set the component type, level, and base object
	if (getContainerObjectsSize() != 1)
		return 0;

	componentType = object->getGameObjectType();
	savedBaseComponent = object;

	if (object->isSchematicFragmentObject()) {
		SchematicFragment* fragment = cast<SchematicFragment*>(object);

		if (fragment == nullptr)
			return 0;

		engineeringLevel = fragment->getTotalFragments();
	} else {
		ShipComponent* component = cast<ShipComponent*>(object);

		if (component == nullptr)
			return 0;

		engineeringLevel = component->getReverseEngineeringLevel();
	}

	return 0;
}

int ComponentAnalysisToolImplementation::notifyObjectRemoved(SceneObject* object) {
	//if the removed object isn't the base, nothing needs to happen
	if (savedBaseComponent != object)
		return 0;

	//null the base
	savedBaseComponent == nullptr;

	//if there are still objects in the tool, select the new base
	if (getContainerObjectsSize() > 0)
		savedBaseComponent = getContainerObject(0);

	return 0;
}

void ComponentAnalysisToolImplementation::decrementCharges(CreatureObject* player) {
	chargeCounter--;
	if (chargeCounter > 0)
		return;

	destroyObjectFromDatabase(true);
	destroyObjectFromWorld(true);
	player->sendSystemMessage("@reverse_engineering_tool:out_of_charges");
}

void ComponentAnalysisToolImplementation::reverseEngineer(CreatureObject* player) {
	if (player == nullptr)
		return;

	//if the base component is nulled, set a new one before starting
	if (savedBaseComponent == nullptr)
		savedBaseComponent = getContainerObject(0);

	ManagedReference<SceneObject*> baseComponent = savedBaseComponent.get();

	// Ensure we have a base component
	if (baseComponent == nullptr) {
		return;
	}

	//if it's a schematic fragment, proceed with combination
	if (baseComponent->isSchematicFragmentObject()){
		createSchematic(player);
		return;
	}

	auto finalComponent = baseComponent.castTo<ShipComponent*>();

	if (finalComponent == nullptr) {
		return;
	}

	Locker clock(finalComponent, _this.getReferenceUnsafeStaticCast());

	int componentCount = getContainerObjectsSize();

	//combine all RE objects
	for (int i = componentCount - 1; i >= 0; --i) {
		ShipComponent* candidate = getContainerObject(i).castTo<ShipComponent*>();

		if (candidate == nullptr || candidate == finalComponent) {
			continue;
		}

		Locker candidateCross(candidate, finalComponent);

		combineComponent(finalComponent, candidate);

		candidate->destroyObjectFromDatabase(true);
		candidate->destroyObjectFromWorld(true);
	}

	applyEngineeringBonus(player, finalComponent);

	//move the final component to inventory
	ManagedReference<SceneObject*> inventory = player->getSlottedObject("inventory");
	if (inventory == nullptr)
		return;

	inventory->transferObject(finalComponent, -1, true, true);

	decrementCharges(player);

	//random chance of getting a KSE Firespray schematic fragment at the end
	//default chance is 1 in 200
	if (System::random(199) != 1)
		return;

	ManagedReference<LootManager*> lootManager = getZoneServer()->getLootManager();

	if (lootManager == nullptr)
		return;

	TransactionLog trx(TrxCode::PLAYERMISCACTION, player);
	if (lootManager->createLoot(trx, inventory, "space_firespray_schematic_fragments", 1) > 0) {
		player->sendSystemMessage("@reverse_engineering_tool:gotpiece");
		trx.commit(true);
	} else {
		trx.abort() << "KSE fragment creation failed";
	}
}

void ComponentAnalysisToolImplementation::combineComponent(ShipComponent* baseComponent, ShipComponent* component) {
	if (baseComponent == nullptr || component == nullptr)
		return;

	//basic stats for all ship components
	baseComponent->setMass(Math::min(component->getMass(), baseComponent->getMass()));
	baseComponent->setHitpointsMax(Math::max(component->getMaxHitpoints(), baseComponent->getMaxHitpoints()));
	baseComponent->setHitpoints(baseComponent->getMaxHitpoints());
	baseComponent->setArmorMax(Math::max(component->getMaxArmor(), baseComponent->getMaxArmor()));
	baseComponent->setArmor(baseComponent->getMaxArmor());
	baseComponent->setEnergyCost(Math::min(component->getEnergyCost(), baseComponent->getEnergyCost()));

	//switch based on object type
	switch (component->getGameObjectType()) {
		case SceneObjectType::SHIPARMOR:
			break;

		case SceneObjectType::SHIPBOOSTER: {
			ShipBoosterComponent* baseBooster = cast<ShipBoosterComponent*>(baseComponent);
			ShipBoosterComponent* boosterComponent = cast<ShipBoosterComponent*>(component);

			if (baseBooster == nullptr || boosterComponent == nullptr)
				return;

			baseBooster->setBoosterAcceleration(Math::max(baseBooster->getBoosterAcceleration(), boosterComponent->getBoosterAcceleration()));
			baseBooster->setBoosterEnergyConsumptionRate(Math::min(baseBooster->getBoosterEnergyConsumptionRate(), boosterComponent->getBoosterEnergyConsumptionRate()));
			baseBooster->setBoosterEnergy(Math::max(baseBooster->getBoosterEnergy(), boosterComponent->getBoosterEnergy()));
			baseBooster->setBoosterRechargeRate(Math::max(baseBooster->getBoosterRechargeRate(), boosterComponent->getBoosterRechargeRate()));
			baseBooster->setBoosterSpeed(Math::max(baseBooster->getBoosterSpeed(), boosterComponent->getBoosterSpeed()));
			break;
		}

		case SceneObjectType::SHIPWEAPONCAPACITOR: {
			ShipCapacitorComponent* baseCapacitor = cast<ShipCapacitorComponent*>(baseComponent);
			ShipCapacitorComponent* capacitorComponent = cast<ShipCapacitorComponent*>(component);

			if (baseCapacitor == nullptr || capacitorComponent == nullptr)
				return;

			baseCapacitor->setCapacitorEnergy(Math::max(baseCapacitor->getCapacitorEnergy(), capacitorComponent->getCapacitorEnergy()));
			baseCapacitor->setRechargeRate(Math::max(baseCapacitor->getRechargeRate(), capacitorComponent->getRechargeRate()));
			break;
		}

		case SceneObjectType::SHIPDROIDINTERFACE: {
			ShipDroidInterfaceComponent* baseInterface = cast<ShipDroidInterfaceComponent*>(baseComponent);
			ShipDroidInterfaceComponent* interfaceComponent = cast<ShipDroidInterfaceComponent*>(component);

			if (baseInterface == nullptr || interfaceComponent == nullptr)
				return;

			baseInterface->setDroidCommandSpeed(Math::min(baseInterface->getDroidCommandSpeed(), interfaceComponent->getDroidCommandSpeed()));
			break;
		}

		case SceneObjectType::SHIPENGINE: {
			ShipEngineComponent* baseEngine = cast<ShipEngineComponent*>(baseComponent);
			ShipEngineComponent* engineComponent = cast<ShipEngineComponent*>(component);

			if (baseEngine == nullptr || engineComponent == nullptr)
				return;

			baseEngine->setPitchRateMaximum(Math::max(baseEngine->getPitchRateMaximum(), engineComponent->getPitchRateMaximum()));
			baseEngine->setYawRateMaximum(Math::max(baseEngine->getYawRateMaximum(), engineComponent->getYawRateMaximum()));
			baseEngine->setRollRateMaximum(Math::max(baseEngine->getRollRateMaximum(), engineComponent->getRollRateMaximum()));
			baseEngine->setSpeedMaximum(Math::max(baseEngine->getSpeedMaximum(), engineComponent->getSpeedMaximum()));
			break;
		}

		case SceneObjectType::SHIPREACTOR: {
			ShipReactorComponent* baseReactor = cast<ShipReactorComponent*>(baseComponent);
			ShipReactorComponent* reactorComponent = cast<ShipReactorComponent*>(component);

			if (baseReactor == nullptr || reactorComponent == nullptr)
				return;

			baseReactor->setReactorGenerationRate(Math::max(baseReactor->getReactorGenerationRate(), reactorComponent->getReactorGenerationRate()));
			break;
		}

		case SceneObjectType::SHIPSHIELDGENERATOR: {
			ShipShieldComponent* baseShield = cast<ShipShieldComponent*>(baseComponent);
			ShipShieldComponent* shieldComponent = cast<ShipShieldComponent*>(component);

			if (baseShield == nullptr || shieldComponent == nullptr)
				return;

			baseShield->setFrontHitpoints(Math::max(baseShield->getFrontHitpoints(), shieldComponent->getFrontHitpoints()));
			baseShield->setRearHitpoints(Math::max(baseShield->getRearHitpoints(), shieldComponent->getRearHitpoints()));
			baseShield->setRechargeRate(Math::max(baseShield->getRechargeRate(), shieldComponent->getRechargeRate()));
			break;
		}

		case SceneObjectType::SHIPWEAPON: {
			ShipWeaponComponent* baseWeapon = cast<ShipWeaponComponent*>(baseComponent);
			ShipWeaponComponent* weaponComponent = cast<ShipWeaponComponent*>(component);

			if (baseWeapon == nullptr || weaponComponent == nullptr)
				return;

			baseWeapon->setMaxDamage(Math::max(baseWeapon->getMaxDamage(), weaponComponent->getMaxDamage()));
			baseWeapon->setMinDamage(Math::max(baseWeapon->getMinDamage(), weaponComponent->getMinDamage()));
			baseWeapon->setShieldEffectiveness(Math::max(baseWeapon->getShieldEffectiveness(), weaponComponent->getShieldEffectiveness()));
			baseWeapon->setArmorEffectiveness(Math::max(baseWeapon->getArmorEffectiveness(), weaponComponent->getArmorEffectiveness()));
			baseWeapon->setRefireRate(Math::min(baseWeapon->getRefireRate(), weaponComponent->getRefireRate()));
			baseWeapon->setEnergyPerShot(Math::min(baseWeapon->getEnergyPerShot(), weaponComponent->getEnergyPerShot()));
			break;
		}

		default:
			break;
	}

	return;
}

void ComponentAnalysisToolImplementation::applyEngineeringBonus(CreatureObject* player, SceneObject* component) {
	//setup variables
	float bonusPercentage = (floor(engineeringLevel / 2) + 1.0f) / 100.0f;
	float before = 0.0f;
	float after = 0.0f;

	//setup SUI to build out while applying bonuses
	ManagedReference<PlayerObject*> ghost = player->getPlayerObject();

	if (ghost == nullptr)
		return;

	auto zoneServer = component->getZoneServer();

	if (zoneServer == nullptr)
		return;

	if (ghost->hasSuiBoxWindowType(SuiWindowType::REVERSE_ENGINEER))
		ghost->closeSuiWindowType(SuiWindowType::REVERSE_ENGINEER);

	ManagedReference<SuiListBox*> resultsWindow = new SuiListBox(player, SuiWindowType::REVERSE_ENGINEER);
	resultsWindow->setPromptTitle("@reverse_engineering_tool:title");
	resultsWindow->setPromptText("@reverse_engineering_tool:prompt");

	resultsWindow->setUsingObject(component);

	resultsWindow->setOkButton(true, "@ok");
	resultsWindow->setCallback(new ReverseEngineeringSuiCallback(zoneServer));

	//basic stats for all ship components
	ShipComponent* finalComponent = static_cast<ShipComponent*>(component);

	if (finalComponent == nullptr)
		return;

	//set RE level to 0 to indicate it's already REed
	finalComponent->setReverseEngineeringLevel(0);

	//mass
	before = finalComponent->getMass();
	after = before * (1.0f - bonusPercentage);

	finalComponent->setMass(after);

	resultsWindow->addMenuItem("@reverse_engineering_tool:massavg " + String::valueOf(before) + " --- " + "@reverse_engineering_tool:bonusapplied " + String::valueOf(bonusPercentage * 100) + "% --- " +  "@reverse_engineering_tool:finaloutput " + String::valueOf(after));

	//hitpoints
	before = finalComponent->getMaxHitpoints();
	after = before * (1.0f + bonusPercentage);

	finalComponent->setHitpointsMax(after);
	finalComponent->setHitpoints(after);

	resultsWindow->addMenuItem("@reverse_engineering_tool:hpavg " + String::valueOf(before) + " --- " + "@reverse_engineering_tool:bonusapplied " + String::valueOf(bonusPercentage * 100) + "% --- " +  "@reverse_engineering_tool:finaloutput " + String::valueOf(after));

	//armor
	before = finalComponent->getMaxArmor();
	after = before * (1.0f + bonusPercentage);

	finalComponent->setArmorMax(after);
	finalComponent->setArmor(after);

	resultsWindow->addMenuItem("@reverse_engineering_tool:armorhpavg " + String::valueOf(before) + " --- " + "@reverse_engineering_tool:bonusapplied " + String::valueOf(bonusPercentage * 100) + "% --- " +  "@reverse_engineering_tool:finaloutput " + String::valueOf(after));

	//energy maintenance
	before = finalComponent->getEnergyCost();
	after = before * (1.0f - bonusPercentage);

	finalComponent->setEnergyCost(after);

	if (after != 0.0f)
		resultsWindow->addMenuItem("@reverse_engineering_tool:energymaintenance " + String::valueOf(before) + " --- " + "@reverse_engineering_tool:bonusapplied " + String::valueOf(bonusPercentage * 100) + "% --- " +  "@reverse_engineering_tool:finaloutput " + String::valueOf(after));

	//switch based on object type
	switch (finalComponent->getGameObjectType()) {
		case SceneObjectType::SHIPARMOR:
			break;

		case SceneObjectType::SHIPBOOSTER: {
			ShipBoosterComponent* finalBooster = cast<ShipBoosterComponent*>(finalComponent);

			if (finalBooster == nullptr)
				return;

			//acceleration
			before = finalBooster->getBoosterAcceleration();
			after = before * (1.0f + bonusPercentage);

			finalBooster->setBoosterAcceleration(after);

			resultsWindow->addMenuItem("@reverse_engineering_tool:boosteraccel " + String::valueOf(before) + " --- " + "@reverse_engineering_tool:bonusapplied " + String::valueOf(bonusPercentage * 100) + "% --- " +  "@reverse_engineering_tool:finaloutput " + String::valueOf(after));

			//consumption
			before = finalBooster->getBoosterEnergyConsumptionRate();
			after = before * (1.0f - bonusPercentage);

			finalBooster->setBoosterEnergyConsumptionRate(after);

			resultsWindow->addMenuItem("@reverse_engineering_tool:boosterconsumption " + String::valueOf(before) + " --- " + "@reverse_engineering_tool:bonusapplied " + String::valueOf(bonusPercentage * 100) + "% --- " +  "@reverse_engineering_tool:finaloutput " + String::valueOf(after));

			//energy pool
			before = finalBooster->getBoosterEnergy();
			after = before * (1.0f + bonusPercentage);

			finalBooster->setBoosterEnergy(after);

			resultsWindow->addMenuItem("@reverse_engineering_tool:boosterenergy " + String::valueOf(before) + " --- " + "@reverse_engineering_tool:bonusapplied " + String::valueOf(bonusPercentage * 100) + "% --- " +  "@reverse_engineering_tool:finaloutput " + String::valueOf(after));

			//recharge
			before = finalBooster->getBoosterRechargeRate();
			after = before * (1.0f + bonusPercentage);

			finalBooster->setBoosterRechargeRate(after);

			resultsWindow->addMenuItem("@reverse_engineering_tool:boosterrecharge " + String::valueOf(before) + " --- " + "@reverse_engineering_tool:bonusapplied " + String::valueOf(bonusPercentage * 100) + "% --- " +  "@reverse_engineering_tool:finaloutput " + String::valueOf(after));

			//speed
			before = finalBooster->getBoosterSpeed();
			after = before * (1.0f + bonusPercentage);

			finalBooster->setBoosterSpeed(after);

			resultsWindow->addMenuItem("@reverse_engineering_tool:boosterspeed " + String::valueOf(before) + " --- " + "@reverse_engineering_tool:bonusapplied " + String::valueOf(bonusPercentage * 100) + "% --- " +  "@reverse_engineering_tool:finaloutput " + String::valueOf(after));
			break;
		}

		case SceneObjectType::SHIPWEAPONCAPACITOR: {
			ShipCapacitorComponent* finalCapacitor = cast<ShipCapacitorComponent*>(finalComponent);

			if (finalCapacitor == nullptr)
				return;

			//energy pool
			before = finalCapacitor->getCapacitorEnergy();
			after = before * (1.0f + bonusPercentage);

			finalCapacitor->setCapacitorEnergy(after);

			resultsWindow->addMenuItem("@reverse_engineering_tool:capenergy " + String::valueOf(before) + " --- " + "@reverse_engineering_tool:bonusapplied " + String::valueOf(bonusPercentage * 100) + "% --- " +  "@reverse_engineering_tool:finaloutput " + String::valueOf(after));

			//recharge
			before = finalCapacitor->getRechargeRate();
			after = before * (1.0f + bonusPercentage);

			finalCapacitor->setRechargeRate(after);

			resultsWindow->addMenuItem("@reverse_engineering_tool:caprecharge " + String::valueOf(before) + " --- " + "@reverse_engineering_tool:bonusapplied " + String::valueOf(bonusPercentage * 100) + "% --- " +  "@reverse_engineering_tool:finaloutput " + String::valueOf(after));
			break;
		}

		case SceneObjectType::SHIPDROIDINTERFACE: {
			ShipDroidInterfaceComponent* finalInterface = cast<ShipDroidInterfaceComponent*>(finalComponent);

			if (finalInterface == nullptr)
				return;

			//command speed
			before = finalInterface->getDroidCommandSpeed();
			after = before * (1.0f - bonusPercentage);

			finalInterface->setDroidCommandSpeed(after);

			resultsWindow->addMenuItem("@reverse_engineering_tool:commandspeed " + String::valueOf(before) + " --- " + "@reverse_engineering_tool:bonusapplied " + String::valueOf(bonusPercentage * 100) + "% --- " +  "@reverse_engineering_tool:finaloutput " + String::valueOf(after));
			break;
		}

		case SceneObjectType::SHIPENGINE: {
			ShipEngineComponent* finalEngine = cast<ShipEngineComponent*>(finalComponent);

			if (finalEngine == nullptr)
				return;

			//pitch
			before = finalEngine->getPitchRateMaximum();
			after = before * (1.0f + bonusPercentage);

			finalEngine->setPitchRateMaximum(after);

			resultsWindow->addMenuItem("@reverse_engineering_tool:engpitch " + String::valueOf(before * Math::RAD2DEG) + " --- " + "@reverse_engineering_tool:bonusapplied " + String::valueOf(bonusPercentage * 100) + "% --- " +  "@reverse_engineering_tool:finaloutput " + String::valueOf(after * Math::RAD2DEG));

			//yaw
			before = finalEngine->getYawRateMaximum();
			after = before * (1.0f + bonusPercentage);

			finalEngine->setYawRateMaximum(after);

			resultsWindow->addMenuItem("@reverse_engineering_tool:engyaw " + String::valueOf(before * Math::RAD2DEG) + " --- " + "@reverse_engineering_tool:bonusapplied " + String::valueOf(bonusPercentage * 100) + "% --- " +  "@reverse_engineering_tool:finaloutput " + String::valueOf(after * Math::RAD2DEG));

			//roll
			before = finalEngine->getRollRateMaximum();
			after = before * (1.0f + bonusPercentage);

			finalEngine->setRollRateMaximum(after);

			resultsWindow->addMenuItem("@reverse_engineering_tool:engroll " + String::valueOf(before * Math::RAD2DEG) + " --- " + "@reverse_engineering_tool:bonusapplied " + String::valueOf(bonusPercentage * 100) + "% --- " +  "@reverse_engineering_tool:finaloutput " + String::valueOf(after * Math::RAD2DEG));

			//top speed
			before = finalEngine->getSpeedMaximum();
			after = before * (1.0f + bonusPercentage);

			finalEngine->setSpeedMaximum(after);

			resultsWindow->addMenuItem("@reverse_engineering_tool:engspeed " + String::valueOf(before) + " --- " + "@reverse_engineering_tool:bonusapplied " + String::valueOf(bonusPercentage * 100) + "% --- " +  "@reverse_engineering_tool:finaloutput " + String::valueOf(after));
			break;
		}

		case SceneObjectType::SHIPREACTOR: {
			ShipReactorComponent* finalReactor = cast<ShipReactorComponent*>(finalComponent);

			if (finalReactor == nullptr)
				return;

			//reactor generation
			before = finalReactor->getReactorGenerationRate();
			after = before * (1.0f + bonusPercentage);

			finalReactor->setReactorGenerationRate(after);

			resultsWindow->addMenuItem("@reverse_engineering_tool:reactorenergy " + String::valueOf(before) + " --- " + "@reverse_engineering_tool:bonusapplied " + String::valueOf(bonusPercentage * 100) + "% --- " +  "@reverse_engineering_tool:finaloutput " + String::valueOf(after));
			break;
		}

		case SceneObjectType::SHIPSHIELDGENERATOR: {
			ShipShieldComponent* finalShield = cast<ShipShieldComponent*>(finalComponent);

			if (finalShield == nullptr)
				return;

			//front hitpoints
			before = finalShield->getFrontHitpoints();
			after = before * (1.0f + bonusPercentage);

			finalShield->setFrontHitpoints(after);

			resultsWindow->addMenuItem("@reverse_engineering_tool:shdfronthp " + String::valueOf(before) + " --- " + "@reverse_engineering_tool:bonusapplied " + String::valueOf(bonusPercentage * 100) + "% --- " +  "@reverse_engineering_tool:finaloutput " + String::valueOf(after));

			//rear hitpoints
			before = finalShield->getRearHitpoints();
			after = before * (1.0f + bonusPercentage);

			finalShield->setRearHitpoints(after);

			resultsWindow->addMenuItem("@reverse_engineering_tool:shdbackhp " + String::valueOf(before) + " --- " + "@reverse_engineering_tool:bonusapplied " + String::valueOf(bonusPercentage * 100) + "% --- " +  "@reverse_engineering_tool:finaloutput " + String::valueOf(after));

			//recharge rate
			before = finalShield->getRechargeRate();
			after = before * (1.0f + bonusPercentage);

			finalShield->setRechargeRate(after);

			resultsWindow->addMenuItem("@reverse_engineering_tool:shdrecharge " + String::valueOf(before) + " --- " + "@reverse_engineering_tool:bonusapplied " + String::valueOf(bonusPercentage * 100) + "% --- " +  "@reverse_engineering_tool:finaloutput " + String::valueOf(after));
			break;
		}

		case SceneObjectType::SHIPWEAPON: {
			ShipWeaponComponent* finalWeapon = cast<ShipWeaponComponent*>(finalComponent);

			if (finalWeapon == nullptr)
				return;

			//max damage
			before = finalWeapon->getMaxDamage();
			after = before * (1.0f + bonusPercentage);

			finalWeapon->setMaxDamage(after);

			resultsWindow->addMenuItem("@reverse_engineering_tool:wpnmaxdmg " + String::valueOf(before) + " --- " + "@reverse_engineering_tool:bonusapplied " + String::valueOf(bonusPercentage * 100) + "% --- " +  "@reverse_engineering_tool:finaloutput " + String::valueOf(after));

			//min damage
			before = finalWeapon->getMinDamage();
			after = before * (1.0f + bonusPercentage);

			finalWeapon->setMinDamage(after);

			resultsWindow->addMenuItem("@reverse_engineering_tool:wpnmindmg " + String::valueOf(before) + " --- " + "@reverse_engineering_tool:bonusapplied " + String::valueOf(bonusPercentage * 100) + "% --- " +  "@reverse_engineering_tool:finaloutput " + String::valueOf(after));

			//vs shields
			before = finalWeapon->getShieldEffectiveness();
			after = before * (1.0f + bonusPercentage);

			finalWeapon->setShieldEffectiveness(after);

			resultsWindow->addMenuItem("@reverse_engineering_tool:wpnshdeff " + String::valueOf(before) + " --- " + "@reverse_engineering_tool:bonusapplied " + String::valueOf(bonusPercentage * 100) + "% --- " +  "@reverse_engineering_tool:finaloutput " + String::valueOf(after));

			//vs armor
			before = finalWeapon->getArmorEffectiveness();
			after = before * (1.0f + bonusPercentage);

			finalWeapon->setArmorEffectiveness(after);

			resultsWindow->addMenuItem("@reverse_engineering_tool:wpnarmeff " + String::valueOf(before) + " --- " + "@reverse_engineering_tool:bonusapplied " + String::valueOf(bonusPercentage * 100) + "% --- " +  "@reverse_engineering_tool:finaloutput " + String::valueOf(after));

			//refire
			before = finalWeapon->getRefireRate();
			after = before * (1.0f - bonusPercentage);

			finalWeapon->setRefireRate(after);

			resultsWindow->addMenuItem("@reverse_engineering_tool:wpnrate " + String::valueOf(before) + " --- " + "@reverse_engineering_tool:bonusapplied " + String::valueOf(bonusPercentage * 100) + "% --- " +  "@reverse_engineering_tool:finaloutput " + String::valueOf(after));

			//EPS
			before = finalWeapon->getEnergyPerShot();
			after = before * (1.0f - bonusPercentage);

			finalWeapon->setEnergyPerShot(after);

			resultsWindow->addMenuItem("@reverse_engineering_tool:wpnenergypershot " + String::valueOf(before) + " --- " + "@reverse_engineering_tool:bonusapplied " + String::valueOf(bonusPercentage * 100) + "% --- " +  "@reverse_engineering_tool:finaloutput " + String::valueOf(after));
			break;
		}

		default:
			break;
	}

	//send results SUI
	ghost->addSuiBox(resultsWindow);
	player->sendMessage(resultsWindow->generateMessage());

	return;
}

void ComponentAnalysisToolImplementation::createSchematic(CreatureObject* player) {
	if (player == nullptr)
		return;

	auto toolObject = getContainerObject(0);

	// Ensure we have a fragment
	if (toolObject == nullptr || !toolObject->isSchematicFragmentObject()) {
		return;
	}

	SchematicFragment* fragmentObject = toolObject.castTo<SchematicFragment*>();

	if (fragmentObject == nullptr) {
		return;
	}

	uint schematicMask = fragmentObject->getFragmentBitmask();
	uint schematicCRC = fragmentObject->getTargetSchematic();
	uint schematicCount = fragmentObject->getTotalFragments();

	int componentCount = getContainerObjectsSize();

	if (componentCount != schematicCount) {
		player->sendSystemMessage("@reverse_engineering_tool:not_enough");
		return;
	}

	//evaluate all fragments
	for (int i = 1; i < componentCount; ++i) {
		SchematicFragment* candidate = getContainerObject(i).castTo<SchematicFragment*>();

		if (candidate == nullptr || candidate == fragmentObject) {
			continue;
		}

		//if the fragments aren't for the same schematic, abort
		if (schematicCRC != candidate->getTargetSchematic()) {
			player->sendSystemMessage("@reverse_engineering_tool:notunique");
			return;
		}

		schematicMask = schematicMask | candidate->getFragmentBitmask();
	}

	//check if the bitmask is filled appropriately
	if (schematicMask != (std::pow(2, componentCount) - 1)) {
		player->sendSystemMessage("@reverse_engineering_tool:notunique");
		return;
	}

	//ready to create schematic
	ManagedReference<SceneObject*> inventory = player->getSlottedObject("inventory");

	if (inventory == nullptr)
		return ;

	auto zoneServer = player->getZoneServer();

	if (zoneServer == nullptr)
		return;

	ManagedReference<TangibleObject*> rewardSchematic = (zoneServer->createObject(schematicCRC, 1)).castTo<TangibleObject*>();

	if (rewardSchematic == nullptr)
		return;

	inventory->transferObject(rewardSchematic, -1, true, true);
	inventory->broadcastObject(rewardSchematic, true);

	player->sendSystemMessage("@reverse_engineering_tool:gotschematic");

	//destroy the fragments
	for (int i = componentCount - 1; i >= 0; --i) {
		SceneObject* usedFragment = getContainerObject(i);

		if (usedFragment == nullptr) {
			continue;
		}

		Locker cross(usedFragment, player);

		usedFragment->destroyObjectFromDatabase(true);
		usedFragment->destroyObjectFromWorld(true);
	}

	decrementCharges(player);
}
