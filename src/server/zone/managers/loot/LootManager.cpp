#include "LootManager.h"

#include "../../objects.h"

LootManager::LootManager(ZoneProcessServerImplementation* procServer) {
	processServer = procServer;
}

void LootManager::lootCorpse(Player* player, Creature* creature) {
	//Pre: player wlocked, creature unlocked
	//Post: player wlocked, creature unlocked
	
	try {
		creature->wlock(player);
		
		if (!creature->isInQuadTree()) {
			creature->unlock();
			return;
		}

		if (!creature->isDead()) {
			creature->unlock();
			return;
		}
		
		createLoot(creature);

		int credits = creature->getCashCredits();

		if (credits > 0) {	
			creature->setCashCredits(0);

			player->addCashCredits(credits);

			stringstream creditText;
			creditText << "You loot " << credits << " credits from corpse of " << creature->getCharacterName().c_str() << ".";

			player->sendSystemMessage(creditText.str());
		}

		Container* lootContainer = creature->getLootContainer();
				
		if (lootContainer != NULL && lootContainer->objectsSize() > 0) {
			for (int i = lootContainer->objectsSize() - 1; i >= 0; --i) {
				TangibleObject* lootItem = (TangibleObject*) lootContainer->getObject(i);
				
				lootContainer->removeObject(i);

				lootItem->setObjectID(player->getNewItemID());
				player->addInventoryItem(lootItem);

				lootItem->sendTo(player);

				lootItem->setPersistent(false);
				
				if (player->getGroupObject()!=NULL) {
					stringstream grouptxt;
					grouptxt << player->getCharacterName().c_str() << " looted " << lootItem->getName().c_str() << "\\#ffffff from " << creature->getCharacterName().c_str();
					
					unicode utxt = unicode(grouptxt.str());
					Message* packet = new ChatSystemMessage(utxt);

					player->getGroupObject()->broadcastMessage(packet);
				}
			}

			player->sendSystemMessage("You have completely looted the corpse of all items.");
		} else 
			player->sendSystemMessage("You find nothing else of value on the selected corpse.");

		creature->removeFromQueue();

		creature->unload();
		
		creature->queueRespawn();

		creature->unlock();
	} catch (...) {
		cout << "Unreported exception caugh in LootManager::lootCorpse(Player* player, Creature* creature)";
		creature->unlock();
	}
}

void LootManager::createLoot(Creature* creature) {
	//Pre: creature wlocked
	//Post: creature wlocked
	
	Container* lootContainer = creature->getLootContainer();
	
	if (lootContainer != NULL && lootContainer->objectsSize() > 0)
		return;
		
	int creatureLevel = creature->getLevel();

	if (creatureLevel == 0) 
		creatureLevel = 1;

	int weaponDropRate = 1500;
	int armorDropRate = 1500;
	int junkDropRate = 1250;
	int creditDropRate = 1500;
	
	creature->setCashCredits(0);

	int itemcount = System::random(2) + 1;

	for (int i = 0; i < itemcount; ++i) {
		if (System::random(armorDropRate) + creatureLevel > 1000) 
			createArmorLoot(creature, creatureLevel);
		
		if (System::random(weaponDropRate) + creatureLevel > 1000)
			createWeaponLoot(creature, creatureLevel);
		
		if (System::random(junkDropRate) > 1000)
			createJunkLoot(creature);
		
		if (System::random(creditDropRate) + creatureLevel > 1000)
			creature->setCashCredits(creatureLevel * System::random(1234) / 25);
	}
}

void LootManager::createWeaponLoot(Creature* creature, int creatureLevel) {
	Weapon* item = NULL;
	
	switch (System::random(12)) {
	case 0 :	// UNARMED
		UnarmedMeleeWeaponImplementation* unarmedImpl = new UnarmedMeleeWeaponImplementation(creature, 
				"object/weapon/melee/special/shared_vibroknuckler.iff",	unicode("a Vibroknuckler"), "vibroknuckler", false);
		
		item = (Weapon*) unarmedImpl->deploy();
		break;
	case 1 :	// ONEHANDED
		OneHandedMeleeWeaponImplementation* onehandImpl = new OneHandedMeleeWeaponImplementation(creature, 
				"object/weapon/melee/baton/shared_baton_gaderiffi.iff", unicode("a Gaderiffi"), "baton_gaderiffi", false);
		onehandImpl->setDamageType(WeaponImplementation::KINETIC);
		onehandImpl->setArmorPiercing(WeaponImplementation::NONE);
		item = (Weapon*) onehandImpl->deploy();
		break;
	case 2 :	// TWOHANDED
		TwoHandedMeleeWeaponImplementation* twohandImpl = new TwoHandedMeleeWeaponImplementation(creature, 
				"object/weapon/melee/2h_sword/shared_2h_sword_maul.iff", unicode("a Power Hammer"), "2h_sword_battleaxe", false);
		twohandImpl->setDamageType(WeaponImplementation::BLAST);
		twohandImpl->setArmorPiercing(WeaponImplementation::MEDIUM);
		item = (Weapon*) twohandImpl->deploy();
		break;
	case 3 :	// POLEARM
		PolearmMeleeWeaponImplementation* polearmImpl = new PolearmMeleeWeaponImplementation(creature, 
				"object/weapon/melee/polearm/shared_lance_vibrolance.iff", unicode("a Vibrolance"), "lance_vibrolance", false);
		polearmImpl->setDamageType(WeaponImplementation::ELECTRICITY);
		polearmImpl->setArmorPiercing(WeaponImplementation::LIGHT);
		item = (Weapon*) polearmImpl->deploy();
		break;
	case 4 :	// PISTOL
		PistolRangedWeaponImplementation* pistolImpl = new PistolRangedWeaponImplementation(creature, 
				"object/weapon/ranged/pistol/shared_pistol_cdef.iff", unicode("a CDEF Pistol"), "pistol_cdef", false);
		pistolImpl->setDamageType(WeaponImplementation::ENERGY);
		pistolImpl->setArmorPiercing(WeaponImplementation::NONE);
		item = (Weapon*) pistolImpl->deploy();
		break;
	case 5 :	// CARBINE
		CarbineRangedWeaponImplementation* carbImpl = new CarbineRangedWeaponImplementation(creature,
				"object/weapon/ranged/carbine/shared_carbine_cdef.iff", unicode("a CDEF Carbine"), "carbine_cdef", false);
		carbImpl->setDamageType(WeaponImplementation::ENERGY);
		carbImpl->setArmorPiercing(WeaponImplementation::NONE);
		item = (Weapon*) carbImpl->deploy();
		break;
	case 6 :	// RIFLE
		RifleRangedWeaponImplementation* rifleImpl = new RifleRangedWeaponImplementation(creature, 
				"object/weapon/ranged/rifle/shared_rifle_t21.iff", unicode("a T21 Rifle"), "rifle_t21", false);
		rifleImpl->setDamageType(WeaponImplementation::ENERGY);
		rifleImpl->setArmorPiercing(WeaponImplementation::HEAVY);
		item = (Weapon*) rifleImpl->deploy();
		break;
	case 7 :	// ONEHANDED
		OneHandedMeleeWeaponImplementation* onehand2Impl = new OneHandedMeleeWeaponImplementation(creature, 
				"object/weapon/melee/baton/shared_baton_stun.iff", unicode("a Stun Baton"), "baton_stun", false);
		onehand2Impl->setDamageType(WeaponImplementation::STUN);
		onehand2Impl->setArmorPiercing(WeaponImplementation::NONE);
		item = (Weapon*) onehand2Impl->deploy();
		break;
	case 8 :	// TWOHANDED
		TwoHandedMeleeWeaponImplementation* twohand2Impl = new TwoHandedMeleeWeaponImplementation(creature, 
				"object/weapon/melee/2h_sword/shared_2h_sword_scythe.iff", unicode("a Scythe"), "2h_sword_scythe", false);
		twohand2Impl->setDamageType(WeaponImplementation::KINETIC);
		twohand2Impl->setArmorPiercing(WeaponImplementation::MEDIUM);
		item = (Weapon*) twohand2Impl->deploy();
		break;
	case 9 :	// POLEARM
		PolearmMeleeWeaponImplementation* polearm2Impl = new PolearmMeleeWeaponImplementation(creature, 
				"object/weapon/melee/polearm/shared_polearm_vibro_axe.iff", unicode("a Long Vibro Axe"), "lance_vibro_axe", false);
		polearm2Impl->setDamageType(WeaponImplementation::KINETIC);
		polearm2Impl->setArmorPiercing(WeaponImplementation::MEDIUM);
		item = (Weapon*) polearm2Impl->deploy();
		break;
	case 10 :	// PISTOL
		PistolRangedWeaponImplementation* pistol2Impl = new PistolRangedWeaponImplementation(creature, 
				"object/weapon/ranged/pistol/shared_pistol_dx2.iff", unicode("a DX2 Pistol"), "pistol_dx2", false);
		pistol2Impl->setDamageType(WeaponImplementation::ACID);
		pistol2Impl->setArmorPiercing(WeaponImplementation::LIGHT);
		item = (Weapon*) pistol2Impl->deploy();
		break;
	case 11 :	// CARBINE
		CarbineRangedWeaponImplementation* carb2Impl = new CarbineRangedWeaponImplementation(creature, 
				"object/weapon/ranged/carbine/shared_carbine_dxr6.iff", unicode("a DX6R Carbine"), "carbine_dx6r", false);
		carb2Impl->setDamageType(WeaponImplementation::ACID);
		carb2Impl->setArmorPiercing(WeaponImplementation::LIGHT);
		item = (Weapon*) carb2Impl->deploy();
		break;
	case 12 :	// RIFLE
		RifleRangedWeaponImplementation* rifle2Impl = new RifleRangedWeaponImplementation(creature, 
				"object/weapon/ranged/rifle/shared_rifle_tenloss_dxr6_disruptor_loot.iff", unicode("a DX6R Rifle"), "rifle_tenloss_dxr6", false);
		rifle2Impl->setDamageType(WeaponImplementation::ACID);
		rifle2Impl->setArmorPiercing(WeaponImplementation::MEDIUM);
		item = (Weapon*) rifle2Impl->deploy();
		break;
	case 13 :	// FLAMETHROWER
		RifleRangedWeaponImplementation* flamerImpl = new RifleRangedWeaponImplementation(creature, 
				"object/weapon/ranged/rifle/shared_rifle_flame_thrower.iff", unicode("a Flamethrower"), "rifle_flame_thrower", false);
		flamerImpl->setDamageType(WeaponImplementation::HEAT);
		flamerImpl->setArmorPiercing(WeaponImplementation::NONE);
		item = (Weapon*) flamerImpl->deploy();
		break;
	}
	
	if (item != NULL) {
		item->setWeaponStats(creatureLevel);
		item->setConditionDamage(System::random(649));
		creature->addLootItem(item);
	}
}

void LootManager::createArmorLoot(Creature* creature, int creatureLevel) {
	Armor* item = NULL;
	uint32 objectCRC = creature->getObjectCRC();

	switch (System::random(5)){
	case 0:
		switch (System::random(8)) {
		case 0 :
			ArmorImplementation* chest1Impl = new ArmorImplementation(creature, 0x7B476F26, 
					unicode("Composite Chestplate"), "armor_composite_chestplate", false);
			chest1Impl->setType(ArmorImplementation::CHEST);
			item = (Armor*) chest1Impl->deploy();
			break;
		case 1 :
			ArmorImplementation* helmet1Impl = new ArmorImplementation(creature, 0x9AF51EAA, 
					unicode("Composite Helmet"), "armor_composite_helmet", false);
			helmet1Impl->setType(ArmorImplementation::HEAD);
			item = (Armor*) helmet1Impl->deploy();
			break;
		case 2 :
			ArmorImplementation* boots1Impl = new ArmorImplementation(creature, 0xDB91E9DB, 
					unicode("Composite Boots"), "armor_composite_boots", false);
			boots1Impl->setType(ArmorImplementation::FOOT);
			item = (Armor*) boots1Impl->deploy();
			break;
		case 3 :
			ArmorImplementation* gloves1Impl = new ArmorImplementation(creature, 0x2C35FFA2, 
					unicode("Composite Gloves"), "armor_composite_gloves", false);
			gloves1Impl->setType(ArmorImplementation::HAND);
			item = (Armor*) gloves1Impl->deploy();
			break;
		case 4 :
			ArmorImplementation* pants1Impl = new ArmorImplementation(creature, 0xC294C432, 
					unicode("Composite Leggings"), "armor_composite_pants", false);
			pants1Impl->setType(ArmorImplementation::LEG);
			item = (Armor*) pants1Impl->deploy();
			break;
		case 5 :
			ArmorImplementation* bicepl1Impl = new ArmorImplementation(creature, 0x13A4DA11, 
					unicode("Composite Bicep"), "armor_composite_bicep_l", false);
			bicepl1Impl->setType(ArmorImplementation::BICEPL);
			item = (Armor*) bicepl1Impl->deploy();
			break;
		case 6 :
			ArmorImplementation* bicepr1Impl = new ArmorImplementation(creature, 0x63719F82, 
					unicode("Composite Bicep"), "armor_composite_bicep_r", false);
			bicepr1Impl->setType(ArmorImplementation::BICEPR);
			item = (Armor*) bicepr1Impl->deploy();
			break;
		case 7 :
			ArmorImplementation* bracerl1Impl = new ArmorImplementation(creature, 0x4DB0192D, 
					unicode("Composite Bracer"), "armor_composite_bracer_l", false);
			bracerl1Impl->setType(ArmorImplementation::BRACERL);
			item = (Armor*) bracerl1Impl->deploy();
			break;
		case 8 :
			ArmorImplementation* bracerr1Impl = new ArmorImplementation(creature, 0x3D655CBE, 
					unicode("Composite Bracer"), "armor_composite_bracer_r", false);
			bracerr1Impl->setType(ArmorImplementation::BRACERR);
			item = (Armor*) bracerr1Impl->deploy();
			break;
		}
		break;
	case 1:
		if (creatureLevel > 99 && System::random(1) == 1) {
			switch (System::random(8)) {	// BH Armor
			case 0 :
				ArmorImplementation* chest2Impl = new ArmorImplementation(creature, 0x4FD29AA3, 
						unicode("Bounty Hunter Chestplate"), "armor_bounty_hunter_chestplate", false);
				chest2Impl->setType(ArmorImplementation::CHEST);
				item = (Armor*) chest2Impl->deploy();
				break;
			case 1 :
				ArmorImplementation* helmet2Impl = new ArmorImplementation(creature, 0x30DB6875, 
						unicode("Bounty Hunter Helmet"), "armor_bounty_hunter_helmet", false);
				helmet2Impl->setType(ArmorImplementation::HEAD);
				item = (Armor*) helmet2Impl->deploy();
				break;
			case 2 :
				ArmorImplementation* boots2Impl = new ArmorImplementation(creature, 0x219DF586, 
						unicode("Bounty Hunter Boots"), "armor_bounty_hunter_boots", false);
				boots2Impl->setType(ArmorImplementation::FOOT);
				item = (Armor*) boots2Impl->deploy();
				break;
			case 3 :
				ArmorImplementation* gloves2Impl = new ArmorImplementation(creature, 0x861B897D, 
						unicode("Bounty Hunter Gloves"), "armor_bounty_hunter_gloves", false);
				gloves2Impl->setType(ArmorImplementation::HAND);
				item = (Armor*) gloves2Impl->deploy();
				break;
			case 4 :
				ArmorImplementation* pants2Impl = new ArmorImplementation(creature, 0x9873E13B, 
						unicode("Bounty Hunter Leggings"), "armor_bounty_hunter_pants", false);
				pants2Impl->setType(ArmorImplementation::LEG);
				item = (Armor*) pants2Impl->deploy();
				break;
			case 5 :
				ArmorImplementation* bicepl2Impl = new ArmorImplementation(creature, 0xE37785C9, 
						unicode("Bounty Hunter Bicep"), "armor_bounty_hunter_bicep_l", false);
				bicepl2Impl->setType(ArmorImplementation::BICEPL);
				item = (Armor*) bicepl2Impl->deploy();
				break;
			case 6 :
				ArmorImplementation* bicepr2Impl = new ArmorImplementation(creature, 0x93A2C05A, 
						unicode("Bounty Hunter Bicep"), "armor_bounty_hunter_bicep_r", false);
				bicepr2Impl->setType(ArmorImplementation::BICEPR);
				item = (Armor*) bicepr2Impl->deploy();
				break;
			case 7 :
				ArmorImplementation* bracerl2Impl = new ArmorImplementation(creature, 0x17573C24, 
						unicode("Bounty Hunter Bracer"), "armor_bounty_hunter_bracer_l", false);
				bracerl2Impl->setType(ArmorImplementation::BRACERL);
				item = (Armor*) bracerl2Impl->deploy();
				break;
			case 8 :
				ArmorImplementation* bracerr2Impl = new ArmorImplementation(creature, 0x678279B7, 
						unicode("Bounty Hunter Bracer"), "armor_bounty_hunter_bracer_r", false);	
				bracerr2Impl->setType(ArmorImplementation::BRACERR);
				item = (Armor*) bracerr2Impl->deploy();
				break;
			}
		}
		
		break;
	case 2:
		if (creatureLevel > 149 && System::random(2) == 1) {
			switch (System::random(8)) {	// Mando Armor
			case 0 :
				ArmorImplementation* chest3Impl = new ArmorImplementation(creature, 0x24525C1C, 
						unicode("Mandalorian Chestplate"), "armor_mandalorian_chest", false);
				chest3Impl->setType(ArmorImplementation::CHEST);
				item = (Armor*) chest3Impl->deploy();
				break;
			case 1 :
				ArmorImplementation* helmet3Impl = new ArmorImplementation(creature, 0x37A4683E, 
						unicode("Mandalorian Helmet"), "armor_mandalorian_helmet", false);
				helmet3Impl->setType(ArmorImplementation::HEAD);
				item = (Armor*) helmet3Impl->deploy();
				break;
			case 2 :
				ArmorImplementation* boots3Impl = new ArmorImplementation(creature, 0x84AD5603, 
						unicode("Mandalorian Boots"), "armor_mandalorian_shoes", false);
				boots3Impl->setType(ArmorImplementation::FOOT);
				item = (Armor*) boots3Impl->deploy();
				break;
			case 3 :
				ArmorImplementation* gloves3Impl = new ArmorImplementation(creature, 0x81648936, 
						unicode("Mandalorian Gloves"), "armor_mandalorian_gloves", false);
				gloves3Impl->setType(ArmorImplementation::HAND);
				item = (Armor*) gloves3Impl->deploy();
				break;
			case 4 :
				ArmorImplementation* pants3Impl = new ArmorImplementation(creature, 0x770C3F1B, 
						unicode("Mandalorian Leggings"), "armor_mandalorian_pants", false);
				pants3Impl->setType(ArmorImplementation::LEG);
				item = (Armor*) pants3Impl->deploy();
				break;
			case 5 :
				ArmorImplementation* bicepl3Impl = new ArmorImplementation(creature, 0x82309ECC, 
						unicode("Mandalorian Bicep"), "armor_mandalorian_bicep_l", false);
				bicepl3Impl->setType(ArmorImplementation::BICEPL);
				item = (Armor*) bicepl3Impl->deploy();
				break;
			case 6 :
				ArmorImplementation* bicepr3Impl = new ArmorImplementation(creature, 0xF2E5DB5F, 
						unicode("Mandalorian Bicep"), "armor_mandalorian_bicep_r", false);
				bicepr3Impl->setType(ArmorImplementation::BICEPR);
				item = (Armor*) bicepr3Impl->deploy();
				break;
			case 7 :
				ArmorImplementation* bracerl3Impl = new ArmorImplementation(creature, 0xF828E204, 
						unicode("Mandalorian Bracer"), "armor_mandalorian_bracer_l", false);
				bracerl3Impl->setType(ArmorImplementation::BRACERL);
				item = (Armor*) bracerl3Impl->deploy();
				break;
			case 8 :
				ArmorImplementation* bracerr3Impl = new ArmorImplementation(creature, 0x88FDA797, 
						unicode("Mandalorian Bracer"), "armor_mandalorian_bracer_r", false);
				bracerr3Impl->setType(ArmorImplementation::BRACERR);
				item = (Armor*) bracerr3Impl->deploy();
				break;
			}
		}
		
		break;
	case 3:
		if (objectCRC == 0xBA7F23CD) { 
			switch (System::random(8)) {
			case 0 :
				ArmorImplementation* chest4Impl = new ArmorImplementation(creature, 0xF22790E, 
						unicode("Stormtrooper Chestplate"), "armor_stormtrooper_chest", false);
				chest4Impl->setType(ArmorImplementation::CHEST);
				item = (Armor*) chest4Impl->deploy();
				break;
			case 1 :
				ArmorImplementation* helmet4Impl = new ArmorImplementation(creature, 0xC499637D, 
						unicode("Stormtrooper Helmet"), "armor_stormtrooper_helmet", false);
				helmet4Impl->setType(ArmorImplementation::HEAD);
				item = (Armor*) helmet4Impl->deploy();
				break;
			case 2 :
				ArmorImplementation* boots4Impl = new ArmorImplementation(creature, 0x7833E9D6, 
						unicode("Stormtrooper Boots"), "armor_stormtrooper_boots", false);
				boots4Impl->setType(ArmorImplementation::FOOT);
				item = (Armor*) boots4Impl->deploy();
				break;
			case 3 :
				ArmorImplementation* gloves4Impl = new ArmorImplementation(creature, 0x72598275, 
						unicode("Stormtrooper Gloves"), "armor_stormtrooper_gloves", false);
				gloves4Impl->setType(ArmorImplementation::HAND);
				item = (Armor*) gloves4Impl->deploy();
				break;
			case 4 :
				ArmorImplementation* pants4Impl = new ArmorImplementation(creature, 0x1863926A, 
						unicode("Stormtrooper Leggings"), "armor_stormtrooper_pants", false);
				pants4Impl->setType(ArmorImplementation::LEG);
				item = (Armor*) pants4Impl->deploy();
				break;
			case 5 :
				ArmorImplementation* bicepl4Impl = new ArmorImplementation(creature, 0x3BC0061C, 
						unicode("Stormtrooper Bicep"), "armor_stormtrooper_bicep_l", false);
				bicepl4Impl->setType(ArmorImplementation::BICEPL);
				item = (Armor*) bicepl4Impl->deploy();
				break;
			case 6 :
				ArmorImplementation* bicepr4Impl = new ArmorImplementation(creature, 0x4B15438F, 
						unicode("Stormtrooper Bicep"), "armor_stormtrooper_bicep_r", false);
				bicepr4Impl->setType(ArmorImplementation::BICEPR);
				item = (Armor*) bicepr4Impl->deploy();
				break;
			case 7 :
				ArmorImplementation* bracerl4Impl = new ArmorImplementation(creature, 0x97474F75, 
						unicode("Stormtrooper Bracer"), "armor_stormtrooper_bracer_l", false);
				bracerl4Impl->setType(ArmorImplementation::BRACERL);
				item = (Armor*) bracerl4Impl->deploy();
				break;
			case 8 :
				ArmorImplementation* bracerr4Impl = new ArmorImplementation(creature, 0xE7920AE6, 
						unicode("Stormtrooper Bracer"), "armor_stormtrooper_bracer_r", false);
				bracerr4Impl->setType(ArmorImplementation::BRACERR);
				item = (Armor*) bracerr4Impl->deploy();
				break;
			}
		}
		
		break;
	case 4:
		if (objectCRC == 0x1527DF01 || objectCRC == 0x71F874) {
			switch (System::random(5)) {
			case 0 :
				ArmorImplementation* chest5Impl = new ArmorImplementation(creature, 0x98A41A65, 
						unicode("Marine Chestplate"), "armor_marine_chest", false);
				chest5Impl->setType(ArmorImplementation::CHEST);
				item = (Armor*) chest5Impl->deploy();
				break;
			case 1 :
				ArmorImplementation* helmet5Impl = new ArmorImplementation(creature, 0x1890B6F4, 
						unicode("Marine Helmet"), "armor_marine_helmet", false);
				helmet5Impl->setType(ArmorImplementation::HEAD);
				item = (Armor*) helmet5Impl->deploy();
				break;
			case 2 :
				ArmorImplementation* boots5Impl = new ArmorImplementation(creature, 0xA06D625, 
						unicode("Marine Boots"), "armor_marine_boots", false);
				boots5Impl->setType(ArmorImplementation::FOOT);
				item = (Armor*) boots5Impl->deploy();
				break;
			case 3 :
				ArmorImplementation* pants5Impl = new ArmorImplementation(creature, 0xF3D42F59, 
						unicode("Marine Leggings"), "armor_marine_pants", false);
				pants5Impl->setType(ArmorImplementation::LEG);
				item = (Armor*) pants5Impl->deploy();
				break;
			case 4 :
				ArmorImplementation* bicepl5Impl = new ArmorImplementation(creature, 0x16825F91, 
						unicode("Marine Bicep"), "armor_marine_bicep_l", false);
				bicepl5Impl->setType(ArmorImplementation::BICEPL);
				item = (Armor*) bicepl5Impl->deploy();
				break;
			case 5 :
				ArmorImplementation* bicepr5Impl = new ArmorImplementation(creature, 0x66571A02, 
						unicode("Marine Bicep"), "armor_marine_bicep_r", false);
				bicepr5Impl->setType(ArmorImplementation::BICEPR);
				item = (Armor*) bicepr5Impl->deploy();
				break;
			}
		}
		break;
	case 5:
		if ((objectCRC == 0xF0663601 || objectCRC == 0xAA197516) && System::random(10) == 7) {
			ArmorImplementation* nsImpl = new ArmorImplementation(creature, 0x2E943BD2, unicode("Nightsister Bicep"), "nightsister_bicep_r", false);
			nsImpl->setType(ArmorImplementation::BICEPR);
			item = (Armor*) nsImpl->deploy();
		break;
		}
	}
		
	if (item != NULL) {
		item->setArmorStats(creatureLevel);
		creature->addLootItem(item);
	}
}

void LootManager::createJunkLoot(Creature* creature) {
	TangibleObject* item = NULL;

	switch (System::random(10)) {
	case 0 :
		TangibleObjectImplementation* item0Impl = new TangibleObjectImplementation(creature, unicode("a Viewscreen (broken)"), 
				"object/tangible/loot/tool/shared_viewscreen_broken_s2.iff", 0xBC03F94);
		item = item0Impl->deploy();
		break;
	case 1 :
		TangibleObjectImplementation* item1Impl = new TangibleObjectImplementation(creature, unicode("Binoculars (broken)"), 
				"object/tangible/loot/tool/shared_binoculars_broken_s1.iff", 0x1E84585F);
		item = item1Impl->deploy();
		break;
	case 2 :
		TangibleObjectImplementation* item2Impl = new TangibleObjectImplementation(creature, unicode("a Human Skull"), 
				"object/tangible/loot/misc/shared_loot_skull_human.iff", 0x25B24532);
		item = item2Impl->deploy();
		break;
	case 3 :
		TangibleObjectImplementation* item3Impl = new TangibleObjectImplementation(creature, unicode("an Impulse Detector (broken)"), 
				"/tangible/loot/tool/shared_impulse_detector_broken_s3.iff", 0x2D13F714);
		item = item3Impl->deploy();
		break;
	case 4 :
		TangibleObjectImplementation* item4Impl = new TangibleObjectImplementation(creature, unicode("a Cage"), 
				"object/tangible/loot/misc/shared_cage_s01.iff", 0x3238DD4A);
		item = item4Impl->deploy();
		break;
	case 5 :
		TangibleObjectImplementation* item5Impl = new TangibleObjectImplementation(creature, unicode("a Rare Artifact"), 
				"object/tangible/loot/misc/shared_artifact_rare_s01.iff", 0x3393694D);
		item = item5Impl->deploy();
		break;
	case 6 :
		TangibleObjectImplementation* item6Impl = new TangibleObjectImplementation(creature, unicode("Holocron Splinters"), 
				"object/tangible/loot/misc/shared_holocron_splinters_sith_s01.iff", 0x3CEA7897);
		item = item6Impl->deploy();
		break;
	case 7 :
		TangibleObjectImplementation* item7Impl = new TangibleObjectImplementation(creature, unicode("a Calibrator (broken)"), 
				"object/tangible/loot/tool/shared_calibrator_broken.iff", 0x5289E0D9);
		item = item7Impl->deploy();
		break;
	case 8 :
		TangibleObjectImplementation* item8Impl = new TangibleObjectImplementation(creature, unicode("a Corrupt Datadisk"), 
				"object/tangible/loot/misc/shared_datadisk_corrupt.iff", 0x5F4B8D76);
		item = item8Impl->deploy();
		break;
	case 9 :
		TangibleObjectImplementation* item9Impl = new TangibleObjectImplementation(creature, unicode("Jawa Beads"), 
				"object/tangible/loot/misc/shared_jawa_beads.iff", 0x619F4DFD);
		item = item9Impl->deploy();
		break;
	case 10 :
		TangibleObjectImplementation* item10Impl = new TangibleObjectImplementation(creature, unicode("a Briefcase"), 
				"object/tangible/loot/misc/shared_briefcase_s01.iff", 0x6C34F325);
		item = item10Impl->deploy();
		break;
	case 11 :
		FireworkImplementation* fireworkImpl = new FireworkImplementation(((Player*)creature), 0x7C540DEB, 
				unicode("a Firework"), "object/tangible/firework/shared_firework_s04.iff");
		item = fireworkImpl->deploy();
		break;
	case 12 :
		HolocronImplementation* holoImpl = new HolocronImplementation(((Player*)creature), 0x9BA06548, 
				unicode("Holocron"), "object/tangible/jedi/shared_jedi_holocron_light.iff");
		item = holoImpl->deploy();
		break;
	}
	
	if (item != NULL)
		creature->addLootItem(item);
}
