/*
 * SlicingSessionImplementation.cpp
 *
 *  Created on: Mar 5, 2011
 *      Author: polonel
 */

#include "SlicingSession.h"
#include "server/zone/objects/player/sui/SuiWindowType.h"
#include "server/zone/objects/player/sui/listbox/SuiListBox.h"
#include "server/zone/objects/tangible/tool/smuggler/SlicingTool.h"

#include "server/zone/managers/player/PlayerManager.h"
#include "server/zone/managers/loot/LootManager.h"

#include "server/zone/objects/tangible/Container.h"
#include "server/zone/objects/tangible/RelockLootContainerEvent.h"
#include "server/zone/objects/tangible/weapon/WeaponObject.h"
#include "server/zone/objects/tangible/wearables/ArmorObject.h"
#include "server/zone/objects/tangible/terminal/mission/MissionTerminal.h"
#include "server/zone/objects/tangible/tool/smuggler/PrecisionLaserKnife.h"

#include "server/zone/objects/player/sessions/sui/SlicingSessionSuiCallback.h"

#include "server/zone/ZoneServer.h"

int SlicingSessionImplementation::initializeSession() {
	firstCable = System::random(1);
	nodeCable = 0;

	cableBlue = false;
	cableRed = false;

	usedNode = false;
	usedClamp = false;

	relockEvent = NULL;

	return 0;
}

void SlicingSessionImplementation::initalizeSlicingMenu(CreatureObject* pl, TangibleObject* obj) {
	player = pl;
	tangibleObject = obj;

	if (player == NULL || tangibleObject == NULL)
		return;

	if (!tangibleObject->isSliceable())
		return;

	if (tangibleObject->containsActiveSession(SessionFacadeType::SLICING)) {
		player->sendSystemMessage("@slicing/slicing:slicing_underway");
		return;
	}

	if (!hasPrecisionLaserKnife(false)) { // do not remove the item on inital window
		player->sendSystemMessage("@slicing/slicing:no_knife");
		return;
	}

	//bugfix 814,819
	ManagedReference<SceneObject*> inventory = player->getSlottedObject("inventory");
	if (inventory == NULL)
		return;

	if (!inventory->hasObjectInContainer(tangibleObject->getObjectID()) && tangibleObject->getGameObjectType() != SceneObjectType::STATICLOOTCONTAINER) {
		player->sendSystemMessage("The object must be in your inventory in order to perform the slice.");
		return;
	}

	if (tangibleObject->isWeaponObject() && !hasWeaponUpgradeKit()) {
		player->sendSystemMessage("@slicing/slicing:no_weapon_kit");
		return;
	}

	if (tangibleObject->isArmorObject() && !hasArmorUpgradeKit()) {
		player->sendSystemMessage("@slicing/slicing:no_armor_kit");
		return;
	}

	slicingSuiBox = new SuiListBox(player, SuiWindowType::SLICING_MENU, 2);
	slicingSuiBox->setCallback(new SlicingSessionSuiCallback(player->getZoneServer()));

	if (tangibleObject->getGameObjectType() == SceneObjectType::PLAYERLOOTCRATE)
		// Don't close the window when we remove PlayerLootContainer from the player's inventory.
		slicingSuiBox->setForceCloseDisabled();

	slicingSuiBox->setPromptTitle("@slicing/slicing:title");
	slicingSuiBox->setUsingObject(tangibleObject);
	slicingSuiBox->setCancelButton(true, "@cancel");
	generateSliceMenu(slicingSuiBox);

	player->getPlayerObject()->addSuiBox(slicingSuiBox);

	player->addActiveSession(SessionFacadeType::SLICING, _this);
	tangibleObject->addActiveSession(SessionFacadeType::SLICING, _this);

}

void SlicingSessionImplementation::generateSliceMenu(SuiListBox* suiBox) {
	if (player == NULL || tangibleObject == NULL)
		return;

	uint8 progress = getProgress();
	suiBox->removeAllMenuItems();

	StringBuffer prompt;
	prompt << "@slicing/slicing:";
	prompt << getPrefix(tangibleObject);

	if (progress == 0) {
		if (usedClamp)
			prompt << "clamp_" << firstCable;
		else if (usedNode)
			prompt << "analyze_" << nodeCable;
		else
			prompt << progress;

		suiBox->addMenuItem("@slicing/slicing:blue_cable", 0);
		suiBox->addMenuItem("@slicing/slicing:red_cable", 1);

		if (!usedClamp && !usedNode) {
			suiBox->addMenuItem("@slicing/slicing:use_clamp", 2);
			suiBox->addMenuItem("@slicing/slicing:use_analyzer", 3);
		}

	} else if (progress == 1) {
		prompt << progress;

		suiBox->addMenuItem((cableBlue) ? "@slicing/slicing:blue_cable_cut" : "@slicing/slicing:blue_cable", 0);
		suiBox->addMenuItem((cableRed) ? "@slicing/slicing:red_cable_cut" : "@slicing/slicing:red_cable", 1);
	}

	suiBox->setPromptText(prompt.toString());
	player->getPlayerObject()->addSuiBox(suiBox);
	player->sendMessage(suiBox->generateMessage());

}

void SlicingSessionImplementation::handleMenuSelect(CreatureObject* pl, byte menuID, SuiListBox* suiBox) {
	if (tangibleObject == NULL || player == NULL || player != pl)
		return;

	uint8 progress = getProgress();

	if (progress == 0) {
		switch(menuID) {
		case 0: {
			if (hasPrecisionLaserKnife()) {
				if (firstCable != 0)
					handleSliceFailed(); // Handle failed slice attempt
				else
					cableBlue = true;
			} else
				player->sendSystemMessage("@slicing/slicing:no_knife");
			break;
		}
		case 1: {
			if (hasPrecisionLaserKnife()) {
				if (firstCable != 1)
					handleSliceFailed(); // Handle failed slice attempt
				else
					cableRed = true;
			} else
				player->sendSystemMessage("@slicing/slicing:no_knife");
			break;
		}
		case 2:
			handleUseClamp(); // Handle Use of Molecular Clamp
			break;

		case 3: {
			handleUseFlowAnalyzer(); // Handle Use of Flow Analyzer
			break;
		}
		default:
			cancelSession();
		}
	} else {
		if (hasPrecisionLaserKnife()) {
			if (firstCable != menuID)
				handleSlice(suiBox); // Handle Successful Slice
			else
				handleSliceFailed(); // Handle failed slice attempt //bugfix 820
			return;
		} else
			player->sendSystemMessage("@slicing/slicing:no_knife");
	}

	generateSliceMenu(suiBox);

}

void SlicingSessionImplementation::endSlicing() {
	if (player == NULL || tangibleObject == NULL) {
		cancelSession();
		return;
	}

	if (tangibleObject->isMissionTerminal())
		player->addCooldown("slicing.terminal", (2 * (60 * 1000))); // 2min Cooldown

	cancelSession();

}

int SlicingSessionImplementation::getSlicingSkill(CreatureObject* slicer) {

	String skill0 = "combat_smuggler_novice";
	String skill1 = "combat_smuggler_slicing_01";
	String skill2 = "combat_smuggler_slicing_02";
	String skill3 = "combat_smuggler_slicing_03";
	String skill4 = "combat_smuggler_slicing_04";
	String skill5 = "combat_smuggler_master";

	if (slicer->hasSkill(skill5))
		return 5;
	else if (slicer->hasSkill(skill4))
		return 4;
	else if (slicer->hasSkill(skill3))
		return 3;
	else if (slicer->hasSkill(skill2))
		return 2;
	else if (slicer->hasSkill(skill1))
		return 1;
	else if (slicer->hasSkill(skill0))
		return 0;

	return -1;

}

bool SlicingSessionImplementation::hasPrecisionLaserKnife(bool removeItem) {
	if (player == NULL)
		return 0;

	ManagedReference<SceneObject*> inventory = player->getSlottedObject("inventory");

	if (inventory == NULL)
		return false;

	Locker inventoryLocker(inventory);

	VectorMap<uint64, ManagedReference<SceneObject*> >* items = inventory->getContainerObjects();

	for (int i = 0; i < items->size(); ++i) {
		ManagedReference<SceneObject*> sceno = items->get(i);

		uint32 objType = sceno->getGameObjectType();

		if (objType == SceneObjectType::LASERKNIFE) {
			PrecisionLaserKnife* knife = cast<PrecisionLaserKnife*>( sceno.get());
			if (removeItem)
				knife->useCharge(player);
			return 1;
		}
	}

	return 0;

}

bool SlicingSessionImplementation::hasWeaponUpgradeKit() {
	if (player == NULL)
		return false;

	ManagedReference<SceneObject*> inventory = player->getSlottedObject("inventory");

	if (inventory == NULL)
		return false;

	VectorMap<uint64, ManagedReference<SceneObject*> >* items = inventory->getContainerObjects();

	for (int i = 0; i < items->size(); ++i) {
		ManagedReference<SceneObject*> sceno = items->get(i);

		uint32 objType = sceno->getGameObjectType();

		if (objType == SceneObjectType::WEAPONUPGRADEKIT) {
			//inventory->removeObject(sceno, true);
			sceno->destroyObjectFromWorld(true);
			return true;
		}
	}

	return false;

}

bool SlicingSessionImplementation::hasArmorUpgradeKit() {
	if (player == NULL)
		return false;

	ManagedReference<SceneObject*> inventory = player->getSlottedObject("inventory");

	if (inventory == NULL)
		return false;

	VectorMap<uint64, ManagedReference<SceneObject*> >* items = inventory->getContainerObjects();

	for (int i = 0; i < items->size(); ++i) {
		ManagedReference<SceneObject*> sceno = items->get(i);

		uint32 objType = sceno->getGameObjectType();

		if (objType == SceneObjectType::ARMORUPGRADEKIT) {
			sceno->destroyObjectFromWorld(true);
			//inventory->removeObject(sceno, true);
			return true;
		}
	}

	return false;

}

void SlicingSessionImplementation::useClampFromInventory(SlicingTool* clamp) {
	if (clamp == NULL || clamp->getGameObjectType() != SceneObjectType::MOLECULARCLAMP)
		return;

	ManagedReference<SceneObject*> inventory = player->getSlottedObject("inventory");

	Locker inventoryLocker(inventory);

	//inventory->removeObject(clamp, true);
	clamp->destroyObjectFromWorld(true);
	player->sendSystemMessage("@slicing/slicing:used_clamp");
	usedClamp = true;

	//if (player->hasSuiBox(slicingSuiBox->getBoxID()))
	//	player->closeSuiWindowType(SuiWindowType::SLICING_MENU);

}

void SlicingSessionImplementation::handleUseClamp() {
	if (player == NULL || tangibleObject == NULL)
		return;

	ManagedReference<SceneObject*> inventory = player->getSlottedObject("inventory");

	Locker inventoryLocker(inventory);

	VectorMap<uint64, ManagedReference<SceneObject*> >* map = inventory->getContainerObjects();

	for (int i = 0; i < map->size(); ++i) {
		ManagedReference<SceneObject*> sceno = map->get(i);

		uint32 objType = sceno->getGameObjectType();

		if (objType == SceneObjectType::MOLECULARCLAMP) {
			//inventory->removeObject(sceno, true);
			sceno->destroyObjectFromWorld(true);

			player->sendSystemMessage("@slicing/slicing:used_clamp");
			usedClamp = true;
			return;
		}
	}

	player->sendSystemMessage("@slicing/slicing:no_clamp");
}

void SlicingSessionImplementation::handleUseFlowAnalyzer() {
	if (player == NULL || tangibleObject == NULL)
		return;

	ManagedReference<SceneObject*> inventory = player->getSlottedObject("inventory");

	Locker inventoryLocker(inventory);

	VectorMap<uint64, ManagedReference<SceneObject*> >* inventoryObjects = inventory->getContainerObjects();

	for (int i = 0; i < inventoryObjects->size(); ++i) {
		ManagedReference<SceneObject*> sceno = inventoryObjects->get(i);

		uint32 objType = sceno->getGameObjectType();

		if (objType == SceneObjectType::FLOWANALYZER) {
			SlicingTool* node = cast<SlicingTool*>( sceno.get());
			nodeCable = node->calculateSuccessRate();

			if (nodeCable) // PASSED
				nodeCable = firstCable;
			else if (nodeCable == firstCable) { // Failed but the cables are Correct
				if (firstCable)
					nodeCable = 0; // Failed - Make the Cable incorrect
			}

			//inventory->removeObject(sceno, true);
			sceno->destroyObjectFromWorld(true);

			player->sendSystemMessage("@slicing/slicing:used_node");
			usedNode = true;
			return;
		}
	}

	player->sendSystemMessage("@slicing/slicing:no_node");
}

void SlicingSessionImplementation::handleSlice(SuiListBox* suiBox) {
	if (player == NULL || tangibleObject == NULL)
		return;

	Locker locker(player);
	Locker clocker(tangibleObject, player);

	PlayerManager* playerManager = player->getZoneServer()->getPlayerManager();

	suiBox->removeAllMenuItems();
	suiBox->setCancelButton(false,"@cancel");

	StringBuffer prompt;
	prompt << "@slicing/slicing:";
	prompt << getPrefix(tangibleObject) + "examine";
	suiBox->setPromptText(prompt.toString());

	player->getPlayerObject()->addSuiBox(suiBox);
	player->sendMessage(suiBox->generateMessage());

	if (tangibleObject->isContainerObject() || tangibleObject->getGameObjectType() == SceneObjectType::PLAYERLOOTCRATE) {
		handleContainerSlice();
		playerManager->awardExperience(player, "slicing", 125, true); // Container Slice XP
	} else	if (tangibleObject->isMissionTerminal()) {
		MissionTerminal* term = cast<MissionTerminal*>( tangibleObject.get());
		playerManager->awardExperience(player, "slicing", 250, true); // Terminal Slice XP
		term->addSlicer(player);
		player->sendSystemMessage("@slicing/slicing:terminal_success");
	} else if (tangibleObject->isWeaponObject()) {
		handleWeaponSlice();
		playerManager->awardExperience(player, "slicing", 500, true); // Weapon Slice XP
	} else if (tangibleObject->isArmorObject()) {
		handleArmorSlice();
		playerManager->awardExperience(player, "slicing", 1000, true); // Armor Slice XP
	}

	endSlicing();

}

void SlicingSessionImplementation::handleWeaponSlice() {
	if (player == NULL || tangibleObject == NULL || !tangibleObject->isWeaponObject())
		return;

	int sliceSkill = getSlicingSkill(player);
	uint8 min = 0;
	uint8 max = 0;

	switch (sliceSkill) {
	case 5:
		min += 5;
		max += 5;
	case 4:
		min += 5;
		max += 5;
	case 3:
	case 2:
		min += 10;
		max += 25;
		break;
	default:
		return;

	}

	uint8 percentage = System::random(max - min) + min;

	switch(System::random(1)) {
	case 0:
		handleSliceDamage(percentage);
		break;
	case 1:
		handleSliceSpeed(percentage);
		break;
	}
}

void SlicingSessionImplementation::handleSliceDamage(uint8 percent) {
	if (tangibleObject == NULL || player == NULL || !tangibleObject->isWeaponObject())
		return;

	WeaponObject* weap = cast<WeaponObject*>( tangibleObject.get());

	Locker locker(weap);

	//TODO: Check for Weapon Powerups and Remove it before the Slice

	weap->setMinDamage((weap->getMinDamage() * percent / 100) + weap->getMinDamage());
	weap->setMaxDamage((weap->getMaxDamage() * percent / 100) + weap->getMaxDamage());

	weap->setSliced(true);

	StringIdChatParameter params;
	params.setDI(percent);
	params.setStringId("@slicing/slicing:dam_mod");

	player->sendSystemMessage(params);

}

void SlicingSessionImplementation::handleSliceSpeed(uint8 percent) {
	if (tangibleObject == NULL || player == NULL || !tangibleObject->isWeaponObject())
		return;

	WeaponObject* weap = cast<WeaponObject*>( tangibleObject.get());

	Locker locker(weap);

	//TODO: Check for Weapon Powerups and Remove it before the Slice

	weap->setAttackSpeed(weap->getAttackSpeed() - (weap->getAttackSpeed() * percent / 100));

	if (weap->getAttackSpeed() < 1)
		weap->setAttackSpeed(1.0f);

	weap->setSliced(true);

	StringIdChatParameter params;
	params.setDI(percent);
	params.setStringId("@slicing/slicing:spd_mod");

	player->sendSystemMessage(params);
}

void SlicingSessionImplementation::handleArmorSlice() {
	if (tangibleObject == NULL || player == NULL)
		return;

	uint8 sliceType = System::random(1);
	int sliceSkill = getSlicingSkill(player);
	uint8 min = 0;
	uint8 max = 0;

	switch (sliceSkill) {
	case 5:
		min += (sliceType == 0) ? 6 : 5;
		max += (sliceType == 0) ? 5 : 5;
	case 4:
		min += (sliceType == 0) ? 0 : 10;
		max += (sliceType == 0) ? 10 : 10;
	case 3:
		min += (sliceType == 0) ? 5 : 5;
		max += (sliceType == 0) ? 20 : 30;
		break;
	default:
		return;
	}

	uint8 percent = System::random(max - min) + min;

	switch (sliceType) {
	case 0:
		handleSliceEffectiveness(percent);
		break;
	case 1:
		handleSliceEncumbrance(percent);
		break;
	}
}

void SlicingSessionImplementation::handleSliceEncumbrance(uint8 percent) {
	if (tangibleObject == NULL || player == NULL || !tangibleObject->isArmorObject())
		return;

	ArmorObject* armor = cast<ArmorObject*>( tangibleObject.get());

	Locker locker(armor);

	armor->setHealthEncumbrance(armor->getHealthEncumbrance() - (armor->getHealthEncumbrance() * percent / 100));
	armor->setActionEncumbrance(armor->getActionEncumbrance() - (armor->getActionEncumbrance() * percent / 100));
	armor->setMindEncumbrance(armor->getMindEncumbrance() - (armor->getMindEncumbrance() * percent / 100));

	armor->setSliced(true);

	StringIdChatParameter params;
	params.setDI(percent);
	params.setStringId("@slicing/slicing:enc_mod");

	player->sendSystemMessage(params);
}

void SlicingSessionImplementation::handleSliceEffectiveness(uint8 percent) {
	if (tangibleObject == NULL || player == NULL || !tangibleObject->isArmorObject())
		return;

	ArmorObject* armor = cast<ArmorObject*>( tangibleObject.get());

	Locker locker(armor);

	if (!armor->isSpecial(WeaponObject::KINETIC)) {
		armor->setKinetic(armor->getKinetic() + (armor->getKinetic() * percent / 100));
		if (armor->getKinetic() > 90.0f)
			armor->setKinetic(90.0f);
	}

	if (!armor->isSpecial(WeaponObject::ENERGY)) {
			armor->setEnergy(armor->getEnergy() + (armor->getEnergy() * percent / 100));
			if (armor->getEnergy() > 90.0f)
				armor->setEnergy(90.0f);
		}

	if (!armor->isSpecial(WeaponObject::ELECTRICITY)) {
		armor->setElectricity(armor->getElectricity() + (armor->getElectricity() * percent / 100));
		if (armor->getElectricity() > 90.0f)
			armor->setElectricity(90.0f);
	}

	if (!armor->isSpecial(WeaponObject::STUN)) {
		armor->setStun(armor->getStun() + (armor->getStun() * percent / 100));
		if (armor->getStun() > 90.0f)
			armor->setStun(90.0f);
	}
	if (!armor->isSpecial(WeaponObject::BLAST)) {
		armor->setBlast(armor->getBlast() + (armor->getBlast() * percent / 100));
		if (armor->getBlast() > 90.0f)
			armor->setBlast(90.0f);
	}
	if (!armor->isSpecial(WeaponObject::HEAT)) {
		armor->setHeat(armor->getHeat() + (armor->getHeat() * percent / 100));
		if (armor->getHeat() > 90.0f)
			armor->setHeat(90.0f);
	}
	if (!armor->isSpecial(WeaponObject::COLD)) {
		armor->setCold(armor->getCold() + (armor->getCold() * percent / 100));
		if (armor->getCold() > 90.0f)
			armor->setCold(90.0f);
	}
	if (!armor->isSpecial(WeaponObject::ACID)) {
		armor->setAcid(armor->getAcid() + (armor->getAcid() * percent / 100));
		if (armor->getAcid() > 90.0f)
			armor->setAcid(90.0f);
	}
	if (!armor->isSpecial(WeaponObject::LIGHTSABER)) {
		armor->setLightSaber(armor->getLightSaber() + (armor->getLightSaber() * percent / 100));
		if (armor->getLightSaber() > 90.0f)
			armor->setLightSaber(90.0f);
	}

	armor->setSliced(true);

	StringIdChatParameter params;
	params.setDI(percent);
	params.setStringId("@slicing/slicing:eff_mod");

	player->sendSystemMessage(params);
}

void SlicingSessionImplementation::handleContainerSlice() {
	if (tangibleObject == NULL || player == NULL)
		return;

	ManagedReference<SceneObject*> inventory = player->getSlottedObject("inventory");

	if (inventory == NULL)
		return;

	Locker inventoryLocker(inventory);

	LootManager* lootManager = player->getZoneServer()->getLootManager();

	if (tangibleObject->getGameObjectType() == SceneObjectType::PLAYERLOOTCRATE) {
		SceneObject* containerSceno = player->getZoneServer()->createObject(String("object/tangible/container/loot/loot_crate.iff").hashCode(), 1);

		if (containerSceno == NULL)
			return;

		Container* container = dynamic_cast<Container*>(containerSceno);

		if (container == NULL)
			return;

		Locker clocker(container, player);

		lootManager->createLoot(container, "lootedContainer");

		inventory->transferObject(container, -1);
		container->sendTo(player, true);

		if (inventory->hasObjectInContainer(tangibleObject->getObjectID())) {
			//inventory->removeObject(tangibleObject, true);
			tangibleObject->destroyObjectFromWorld(true);
		}

	} else if (tangibleObject->isContainerObject()) {
		Container* container = dynamic_cast<Container*>(tangibleObject.get());

		if (container == NULL)
			return;

		lootManager->createLoot(container, "staticContainer");

		container->setSliced(true);
		container->setLockedStatus(false);

		relockEvent = new RelockLootContainerEvent(container);
		relockEvent->schedule(3600 * 1000); // How long before Relock?? (1 Hour)

	} else
		return;

	player->sendSystemMessage("@slicing/slicing:container_success");
}

void SlicingSessionImplementation::handleSliceFailed() {
	if (tangibleObject == NULL || player == NULL)
			return;

	if (tangibleObject->isMissionTerminal())
		player->sendSystemMessage("@slicing/slicing:terminal_fail");
	else if (tangibleObject->isWeaponObject())
		player->sendSystemMessage("@slicing/slicing:fail_weapon");
	else if (tangibleObject->isArmorObject())
		player->sendSystemMessage("@slicing/slicing:fail_armor");
	else if (tangibleObject->isContainerObject() || tangibleObject->getGameObjectType() == SceneObjectType::PLAYERLOOTCRATE)
		player->sendSystemMessage("@slicing/slicing:container_fail");
	else
		player->sendSystemMessage("Your attempt to slice the object has failed.");

	if (tangibleObject->isContainerObject()) {
		relockEvent = new RelockLootContainerEvent(tangibleObject);
		relockEvent->schedule(3600 * 1000); // This will reactivate the 'broken' lock. (1 Hour)
		tangibleObject->setSliced(true);
	} else if (!tangibleObject->isMissionTerminal()) {
		tangibleObject->setSliced(true);
	}

	endSlicing();
}
