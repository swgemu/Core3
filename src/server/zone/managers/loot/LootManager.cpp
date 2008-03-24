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
		
		if (!((CreatureObject*)creature)->isLootOwner(player)) {
			player->sendSystemMessage("You do not have permission to access this corpse.");
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
					BaseMessage* packet = new ChatSystemMessage(utxt);

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
	
	if (lootContainer == NULL)
		return;
	
	if (lootContainer != NULL && lootContainer->objectsSize() > 0)
		return;
		
	int creatureLevel = creature->getLevel();

	if (creatureLevel == 0) 
		creatureLevel = 1;
	
	creature->setCashCredits(0);

	int itemcount = System::random(creatureLevel / 100) + 1;
	
	for (int i = 0; i < itemcount; ++i) {
		int lootchance = System::random(100);
		
		int creaturechancemodifier = creatureLevel / 100;
		
		if (lootchance < 5 + creaturechancemodifier) {
			createArmorLoot(creature, creatureLevel);
		} else if (lootchance < 10 + 2 * creaturechancemodifier) {
			createClothingLoot(creature, creatureLevel);
		} else if (lootchance < 15 + 3 * creaturechancemodifier) {
			createWeaponLoot(creature, creatureLevel);
		} else if (lootchance < 20 + 4 * creaturechancemodifier) {
			createAttachmentLoot(creature, creatureLevel);
		} else if (lootchance < 25 + 5 * creaturechancemodifier) {
			createPowerupLoot(creature, creatureLevel);
		} else {
			createJunkLoot(creature);
			creature->setCashCredits(creatureLevel * System::random(1234) / 25);
		}
	}
}

void LootManager::createWeaponLoot(Creature* creature, int creatureLevel) {
	Weapon* item = NULL;
	WeaponImplementation* itemImpl = NULL;
	string certification = "";
	
	uint32 objectCRC = creature->getObjectCRC();
	
	switch (System::random(21)) {
	case 0 :	// UNARMED
		itemImpl = new UnarmedMeleeWeaponImplementation(creature, 
				"object/weapon/melee/special/shared_vibroknuckler.iff",	unicode("Vibroknuckler"), "vibroknuckler", false);
		itemImpl->setDamageType(WeaponImplementation::KINETIC);
		itemImpl->setArmorPiercing(WeaponImplementation::LIGHT);
		certification = "cert_vibroknuckler";
		break;
	case 1 :	// ONEHANDED
		itemImpl = new OneHandedMeleeWeaponImplementation(creature, 
				"object/weapon/melee/baton/shared_baton_gaderiffi.iff", unicode("Gaderiffi"), "baton_gaderiffi", false);
		itemImpl->setDamageType(WeaponImplementation::KINETIC);
		itemImpl->setArmorPiercing(WeaponImplementation::NONE);
		certification = "cert_baton_gaderiffi";
		break;
	case 2 :	// TWOHANDED
		itemImpl = new TwoHandedMeleeWeaponImplementation(creature, 
				"object/weapon/melee/2h_sword/shared_2h_sword_maul.iff", unicode("Power Hammer"), "2h_sword_battleaxe", false);
		itemImpl->setDamageType(WeaponImplementation::BLAST);
		itemImpl->setArmorPiercing(WeaponImplementation::MEDIUM);
		certification = "cert_sword_2h_maul";
		break;
	case 3 :	// POLEARM
		itemImpl = new PolearmMeleeWeaponImplementation(creature, 
				"object/weapon/melee/polearm/shared_lance_vibrolance.iff", unicode("Vibrolance"), "lance_vibrolance", false);
		itemImpl->setDamageType(WeaponImplementation::ELECTRICITY);
		itemImpl->setArmorPiercing(WeaponImplementation::LIGHT);
		certification = "cert_lance_vibrolance";
		break;
	case 4 :	// PISTOL
		itemImpl = new PistolRangedWeaponImplementation(creature, 
				"object/weapon/ranged/pistol/shared_pistol_cdef.iff", unicode("CDEF Pistol"), "pistol_cdef", false);
		itemImpl->setDamageType(WeaponImplementation::ENERGY);
		itemImpl->setArmorPiercing(WeaponImplementation::NONE);
		break;
	case 5 :	// CARBINE
		itemImpl = new CarbineRangedWeaponImplementation(creature,
				"object/weapon/ranged/carbine/shared_carbine_cdef.iff", unicode("CDEF Carbine"), "carbine_cdef", false);
		itemImpl->setDamageType(WeaponImplementation::ENERGY);
		itemImpl->setArmorPiercing(WeaponImplementation::NONE);
		break;
	case 6 :	// RIFLE
		itemImpl = new RifleRangedWeaponImplementation(creature, 
				"object/weapon/ranged/rifle/shared_rifle_t21.iff", unicode("T21 Rifle"), "rifle_t21", false);
		itemImpl->setDamageType(WeaponImplementation::ENERGY);
		itemImpl->setArmorPiercing(WeaponImplementation::HEAVY);
		certification = "cert_rifle_t21";
		break;
	case 7 :	// ONEHANDED
		itemImpl = new OneHandedMeleeWeaponImplementation(creature, 
				"object/weapon/melee/baton/shared_baton_stun.iff", unicode("Stun Baton"), "baton_stun", false);
		itemImpl->setDamageType(WeaponImplementation::STUN);
		itemImpl->setArmorPiercing(WeaponImplementation::NONE);
		certification = "cert_baton_stun";
		break;
	case 8 :	// TWOHANDED
		itemImpl = new TwoHandedMeleeWeaponImplementation(creature, 
				"object/weapon/melee/2h_sword/shared_2h_sword_scythe.iff", unicode("Scythe"), "2h_sword_scythe", false);
		itemImpl->setDamageType(WeaponImplementation::KINETIC);
		itemImpl->setArmorPiercing(WeaponImplementation::MEDIUM);
		certification = "cert_sword_2h_scythe";
		break;
	case 9 :	// POLEARM
		itemImpl = new PolearmMeleeWeaponImplementation(creature, 
				"object/weapon/melee/polearm/shared_polearm_vibro_axe.iff", unicode("Long Vibro Axe"), "lance_vibro_axe", false);
		itemImpl->setDamageType(WeaponImplementation::KINETIC);
		itemImpl->setArmorPiercing(WeaponImplementation::MEDIUM);
		certification = "cert_polearm_vibro_axe";
		break;
	case 10 :	// PISTOL
		itemImpl = new PistolRangedWeaponImplementation(creature, 
				"object/weapon/ranged/pistol/shared_pistol_dx2.iff", unicode("DX2 Pistol"), "pistol_dx2", false);
		itemImpl->setDamageType(WeaponImplementation::ACID);
		itemImpl->setArmorPiercing(WeaponImplementation::LIGHT);
		certification = "cert_pistol_dx2";
		break;
	case 11 :	// CARBINE
		itemImpl = new CarbineRangedWeaponImplementation(creature, 
				"object/weapon/ranged/carbine/shared_carbine_dxr6.iff", unicode("DXR6 Carbine"), "carbine_dxr6", false);
		itemImpl->setDamageType(WeaponImplementation::ACID);
		itemImpl->setArmorPiercing(WeaponImplementation::LIGHT);
		certification = "cert_carbine_dxr6";
		break;
	case 12 :	// RIFLE
		itemImpl = new RifleRangedWeaponImplementation(creature, 
				"object/weapon/ranged/rifle/shared_rifle_tenloss_dxr6_disruptor_loot.iff", unicode("DXR-6b Disruptor Rifle"), "rifle_tenloss_dxr6", false);
		itemImpl->setDamageType(WeaponImplementation::ACID);
		itemImpl->setArmorPiercing(WeaponImplementation::MEDIUM);
		
		itemImpl->setAttackSpeed(7.4);
		itemImpl->setMinDamage(104);
		itemImpl->setMaxDamage(249);
		itemImpl->setWoundsRatio(22.7);
		
		itemImpl->setPointBlankAccuracy(-60);
		itemImpl->setPointBlankRange(0);

		itemImpl->setIdealAccuracy(60);
		itemImpl->setIdealRange(54);

		itemImpl->setMaxRangeAccuracy(20);
		itemImpl->setMaxRange(64);

		itemImpl->setHealthAttackCost(22);
		itemImpl->setActionAttackCost(44);
		itemImpl->setMindAttackCost(54);
		
		certification = "cert_rifle_t21";  // no cert we need to do it by skill box
		break;
	case 13 :	// POLEARM
		if (objectCRC == 0xAA197516 || objectCRC == 0xF0663601 || objectCRC == 0x158DC349 || 
			objectCRC == 0xB0DC0219 || objectCRC == 0x1FA893FD || objectCRC == 0x90D8EBF8 ||
			objectCRC == 0xAC722907 || objectCRC == 0x2D98A9B3 || objectCRC == 0xD84925C2 ||
			objectCRC == 0x514A2CBF || objectCRC == 0x5861C6A3 || objectCRC == 0x889ADF8D ||
			objectCRC == 0x44F934A9) {
				itemImpl = new PolearmMeleeWeaponImplementation(creature, 
						"object/weapon/melee/polearm/shared_lance_controllerfp_nightsister.iff", unicode("Nightsister Lance"), "lance_controllerfp_nightsister", false);
				itemImpl->setDamageType(WeaponImplementation::KINETIC);
				itemImpl->setArmorPiercing(WeaponImplementation::NONE);
				itemImpl->setMinDamage(7);
				itemImpl->setMaxDamage(133);
				itemImpl->setDot0Attribute(WeaponImplementation::HEALTH);
				itemImpl->setDot0Type(WeaponImplementation::DISEASE);
				itemImpl->setDot0Potency(70);
				itemImpl->setDot0Strength(40);
				itemImpl->setDot0Duration(1200);
				itemImpl->setDot0Uses(8000);
				certification = "cert_lance_controllerfp";
		}
		break;
	case 14 :	// PISTOL
		if (creatureLevel > 150) {
			itemImpl = new PistolRangedWeaponImplementation(creature, 
					"object/weapon/ranged/pistol/shared_pistol_geonosian_sonic_blaster_loot.iff", unicode("Genosian Sonic Blaster"), "pistol_sonic_blaster", false);
			itemImpl->setDamageType(WeaponImplementation::STUN);
			itemImpl->setArmorPiercing(WeaponImplementation::NONE);
			itemImpl->setAttackSpeed(2.6);
			itemImpl->setMinDamage(65);
			itemImpl->setMaxDamage(100);
			itemImpl->setWoundsRatio(4);
			
			itemImpl->setPointBlankAccuracy(18);
			itemImpl->setPointBlankRange(0);
			itemImpl->setIdealAccuracy(34);
			itemImpl->setIdealRange(15);
			itemImpl->setMaxRangeAccuracy(-90);
			itemImpl->setMaxRange(48);
			certification = "cert_pistol_dx2";  // need to add a cert to the db for this
		}
		break;
	case 15 :	// FLAMETHROWER
		itemImpl = new SpecialHeavyRangedWeaponImplementation(creature, 
				"object/weapon/ranged/rifle/shared_rifle_flame_thrower.iff", unicode("Flame Thrower"), "rifle_flame_thrower", false);
		itemImpl->setMinDamage(125);
		itemImpl->setMaxDamage(377);
		itemImpl->setWoundsRatio(36);
		certification = "cert_rifle_flame_thrower";
		break;
	case 16 :	// LAUNCHER PISTOL
		itemImpl = new PistolRangedWeaponImplementation(creature, 
				"object/weapon/ranged/pistol/shared_pistol_launcher.iff", unicode("Launcher Pistol"), "pistol_launcher", false);
		itemImpl->setDamageType(WeaponImplementation::BLAST);
		itemImpl->setArmorPiercing(WeaponImplementation::NONE);

		itemImpl->setAttackSpeed(2.8);
		itemImpl->setMinDamage(56);
		itemImpl->setMaxDamage(217);
		itemImpl->setWoundsRatio(21);
		
		itemImpl->setPointBlankAccuracy(0);
		itemImpl->setPointBlankRange(0);
		itemImpl->setIdealAccuracy(4);
		itemImpl->setIdealRange(0);
		itemImpl->setMaxRangeAccuracy(0);
		itemImpl->setMaxRange(64);
		
		certification = "cert_pistol_launcher";

		break;
	case 17 :	// LASER CARBINE
		itemImpl = new CarbineRangedWeaponImplementation(creature,
				"object/weapon/ranged/carbine/shared_carbine_laser.iff", unicode("Laser Carbine"), "carbine_laser", false);
		itemImpl->setDamageType(WeaponImplementation::ENERGY);
		itemImpl->setArmorPiercing(WeaponImplementation::MEDIUM);
		
		itemImpl->setAttackSpeed(5.0);
		itemImpl->setMinDamage(7);
		itemImpl->setMaxDamage(129);
		itemImpl->setWoundsRatio(7);
		
		itemImpl->setPointBlankAccuracy(-10);
		itemImpl->setPointBlankRange(0);
		itemImpl->setIdealAccuracy(3);
		itemImpl->setIdealRange(50);
		itemImpl->setMaxRangeAccuracy(-40);
		itemImpl->setMaxRange(64);
		
		certification = "cert_carbine_laser";
		break;
	case 18 :	// JAWA ION RIFLE
		itemImpl = new RifleRangedWeaponImplementation(creature, 
				"object/weapon/ranged/rifle/shared_rifle_jawa_ion.iff", unicode("Jawa Ion Rifle"), "rifle_jawa_ion", false);
		itemImpl->setDamageType(WeaponImplementation::STUN);
		itemImpl->setArmorPiercing(WeaponImplementation::LIGHT);
		
		itemImpl->setAttackSpeed(6.8);
		itemImpl->setMinDamage(53);
		itemImpl->setMaxDamage(98);
		itemImpl->setWoundsRatio(4);
		
		itemImpl->setPointBlankAccuracy(-50);
		itemImpl->setPointBlankRange(0);
		itemImpl->setIdealAccuracy(15);
		itemImpl->setIdealRange(40);
		itemImpl->setMaxRangeAccuracy(-80);
		itemImpl->setMaxRange(64);

		certification = "cert_rifle_jawa_ion";
		break;
	case 19 :	// VIBROBLADE
		itemImpl = new OneHandedMeleeWeaponImplementation(creature,
				"object/weapon/melee/knife/shared_knife_vibroblade.iff", unicode("A Vibroblade"), "knife_vibroblade", false);
		itemImpl->setArmorPiercing(WeaponImplementation::LIGHT);
		itemImpl->setDamageType(WeaponImplementation::KINETIC);
		
		itemImpl->setAttackSpeed(4.2);
		itemImpl->setMinDamage(10);
		itemImpl->setMaxDamage(59);
		itemImpl->setWoundsRatio(8.0);

		itemImpl->setPointBlankAccuracy(3);
		itemImpl->setPointBlankRange(0);

		itemImpl->setIdealAccuracy(3);
		itemImpl->setIdealRange(3);

		itemImpl->setMaxRangeAccuracy(3);
		itemImpl->setMaxRange(4);

		itemImpl->setHealthAttackCost(13);
		itemImpl->setActionAttackCost(46);
		itemImpl->setMindAttackCost(13);

		certification = "cert_knife_vibroblade";
		break;
	case 20 :	// DE-10 PISTOL
		if (creatureLevel > 150) {
			itemImpl = new PistolRangedWeaponImplementation(creature, 
					"object/weapon/ranged/pistol/shared_pistol_de_10.iff", unicode("DE-10 Pistol"), "pistol_de_10", false);
			itemImpl->setDamageType(WeaponImplementation::ENERGY);
			itemImpl->setArmorPiercing(WeaponImplementation::LIGHT);
			itemImpl->setAttackSpeed(5.6);
			itemImpl->setMinDamage(128);
			itemImpl->setMaxDamage(320);
			itemImpl->setWoundsRatio(38.7);
			
			itemImpl->setPointBlankAccuracy(-2);
			itemImpl->setPointBlankRange(0);
			itemImpl->setIdealAccuracy(46);
			itemImpl->setIdealRange(20);
			itemImpl->setMaxRangeAccuracy(-80);
			itemImpl->setMaxRange(64);
			certification = "cert_pistol_dx2";  // need to add a cert to the db for this
		}
		break;
	case 21 :	// LIGHT LIGHTNING CANNON
		itemImpl = new SpecialHeavyRangedWeaponImplementation(creature,
				"object/weapon/ranged/rifle/shared_rifle_lightning.iff", unicode("Light Lightning Cannon"), "rifle_lightning", false);
		itemImpl->setType(WeaponImplementation::RIFLELIGHTNING);
		itemImpl->setDamageType(WeaponImplementation::ELECTRICITY);
		itemImpl->setArmorPiercing(WeaponImplementation::LIGHT);
		
		itemImpl->setAttackSpeed(5.6);
		itemImpl->setMinDamage(127.2);
		itemImpl->setMaxDamage(257.3);
		itemImpl->setWoundsRatio(17.2);
		
		itemImpl->setPointBlankAccuracy(-30);
		itemImpl->setPointBlankRange(0);
		itemImpl->setIdealAccuracy(20);
		itemImpl->setIdealRange(48);
		itemImpl->setMaxRangeAccuracy(30);
		itemImpl->setMaxRange(64);
		
		itemImpl->setHealthAttackCost(63);
		itemImpl->setActionAttackCost(66);
		itemImpl->setMindAttackCost(63);
		
		certification = "cert_rifle_lightning";
		break;
	case 22 :	// ROCKET LAUNCHER
		itemImpl = new HeavyRangedWeaponImplementation(creature,
				"object/weapon/ranged/heavy/shared_heavy_rocket_launcher.iff", unicode("Rocket Launcher"), "heavy_rocket_launcher", false);
		itemImpl->setType(WeaponImplementation::HEAVYROCKETLAUNCHER);
		itemImpl->setDamageType(WeaponImplementation::BLAST);
		itemImpl->setArmorPiercing(WeaponImplementation::HEAVY);
		
		itemImpl->setAttackSpeed(7.0);
		itemImpl->setMinDamage(617.2);
		itemImpl->setMaxDamage(987.3);
		itemImpl->setWoundsRatio(37);
		
		itemImpl->setPointBlankAccuracy(-100);
		itemImpl->setPointBlankRange(0);
		itemImpl->setIdealAccuracy(20);
		itemImpl->setIdealRange(48);
		itemImpl->setMaxRangeAccuracy(30);
		itemImpl->setMaxRange(64);
		
		itemImpl->setHealthAttackCost(113);
		itemImpl->setActionAttackCost(86);
		itemImpl->setMindAttackCost(69);
		
		itemImpl->setUsesRemaining(creatureLevel / (System::random(5) + 5));
		
		certification = "cert_heavy_rocket_launcher";
		break;
	}
	if (itemImpl != NULL) {
		item = (Weapon*) itemImpl->deploy();
		
		item->setCert(certification);
		item->setWeaponStats(creatureLevel);
		item->setConditionDamage(System::random(649));
		creature->addLootItem(item);
	}
}

void LootManager::createArmorLoot(Creature* creature, int32 creatureLevel) {
	Armor* item = NULL;
	ArmorImplementation* itemImpl = NULL;
	
	uint32 objectCRC = creature->getObjectCRC();
	
	switch (System::random(5)){
	case 0:
		switch (System::random(8)) {
		case 0 :
			itemImpl = new ArmorImplementation(creature, 0x7B476F26, 
					unicode("Composite Chestplate"), "armor_composite_chestplate", false);
			itemImpl->setType(ArmorImplementation::CHEST);
			break;
		case 1 :
			itemImpl = new ArmorImplementation(creature, 0x9AF51EAA, 
					unicode("Composite Helmet"), "armor_composite_helmet", false);
			itemImpl->setType(ArmorImplementation::HEAD);
			break;
		case 2 :
			itemImpl = new ArmorImplementation(creature, 0xDB91E9DB, 
					unicode("Composite Boots"), "armor_composite_boots", false);
			itemImpl->setType(ArmorImplementation::FOOT);
			break;
		case 3 :
			itemImpl = new ArmorImplementation(creature, 0x2C35FFA2, 
					unicode("Composite Gloves"), "armor_composite_gloves", false);
			itemImpl->setType(ArmorImplementation::HAND);
			break;
		case 4 :
			itemImpl = new ArmorImplementation(creature, 0xC294C432, 
					unicode("Composite Leggings"), "armor_composite_pants", false);
			itemImpl->setType(ArmorImplementation::LEG);
			break;
		case 5 :
			itemImpl = new ArmorImplementation(creature, 0x13A4DA11, 
					unicode("Composite Bicep"), "armor_composite_bicep_l", false);
			itemImpl->setType(ArmorImplementation::BICEPL);
			break;
		case 6 :
			itemImpl = new ArmorImplementation(creature, 0x63719F82, 
					unicode("Composite Bicep"), "armor_composite_bicep_r", false);
			itemImpl->setType(ArmorImplementation::BICEPR);
			break;
		case 7 :
			itemImpl = new ArmorImplementation(creature, 0x4DB0192D, 
					unicode("Composite Bracer"), "armor_composite_bracer_l", false);
			itemImpl->setType(ArmorImplementation::BRACERL);
			break;
		case 8 :
			itemImpl = new ArmorImplementation(creature, 0x3D655CBE, 
					unicode("Composite Bracer"), "armor_composite_bracer_r", false);
			itemImpl->setType(ArmorImplementation::BRACERR);
			break;
		}
		break;
	case 1:
		if (creatureLevel > 99 && System::random(1) == 1) {
			switch (System::random(8)) {	// BH Armor
			case 0 :
				itemImpl = new ArmorImplementation(creature, 0x4FD29AA3, 
						unicode("Bounty Hunter Chestplate"), "armor_bounty_hunter_chestplate", false);
				itemImpl->setType(ArmorImplementation::CHEST);
				break;
			case 1 :
				itemImpl = new ArmorImplementation(creature, 0x30DB6875, 
						unicode("Bounty Hunter Helmet"), "armor_bounty_hunter_helmet", false);
				itemImpl->setType(ArmorImplementation::HEAD);
				break;
			case 2 :
				itemImpl = new ArmorImplementation(creature, 0x219DF586, 
						unicode("Bounty Hunter Boots"), "armor_bounty_hunter_boots", false);
				itemImpl->setType(ArmorImplementation::FOOT);
				break;
			case 3 :
				itemImpl = new ArmorImplementation(creature, 0x861B897D, 
						unicode("Bounty Hunter Gloves"), "armor_bounty_hunter_gloves", false);
				itemImpl->setType(ArmorImplementation::HAND);
				break;
			case 4 :
				itemImpl = new ArmorImplementation(creature, 0x9873E13B, 
						unicode("Bounty Hunter Leggings"), "armor_bounty_hunter_pants", false);
				itemImpl->setType(ArmorImplementation::LEG);
				break;
			case 5 :
				itemImpl = new ArmorImplementation(creature, 0xE37785C9, 
						unicode("Bounty Hunter Bicep"), "armor_bounty_hunter_bicep_l", false);
				itemImpl->setType(ArmorImplementation::BICEPL);
				break;
			case 6 :
				itemImpl = new ArmorImplementation(creature, 0x93A2C05A, 
						unicode("Bounty Hunter Bicep"), "armor_bounty_hunter_bicep_r", false);
				itemImpl->setType(ArmorImplementation::BICEPR);
				break;
			case 7 :
				itemImpl = new ArmorImplementation(creature, 0x17573C24, 
						unicode("Bounty Hunter Bracer"), "armor_bounty_hunter_bracer_l", false);
				itemImpl->setType(ArmorImplementation::BRACERL);
				break;
			case 8 :
				itemImpl = new ArmorImplementation(creature, 0x678279B7, 
						unicode("Bounty Hunter Bracer"), "armor_bounty_hunter_bracer_r", false);	
				itemImpl->setType(ArmorImplementation::BRACERR);
				break;
			}
		}
		
		break;
	case 2:
		if (creatureLevel > 149 && System::random(2) == 1) {
			switch (System::random(8)) {	// Mando Armor
			case 0 :
				itemImpl = new ArmorImplementation(creature, 0x24525C1C, 
						unicode("Mandalorian Chestplate"), "armor_mandalorian_chest", false);
				itemImpl->setType(ArmorImplementation::CHEST);
				break;
			case 1 :
				itemImpl = new ArmorImplementation(creature, 0x37A4683E, 
						unicode("Mandalorian Helmet"), "armor_mandalorian_helmet", false);
				itemImpl->setType(ArmorImplementation::HEAD);
				break;
			case 2 :
				itemImpl = new ArmorImplementation(creature, 0x84AD5603, 
						unicode("Mandalorian Boots"), "armor_mandalorian_shoes", false);
				itemImpl->setType(ArmorImplementation::FOOT);
				break;
			case 3 :
				itemImpl = new ArmorImplementation(creature, 0x81648936, 
						unicode("Mandalorian Gloves"), "armor_mandalorian_gloves", false);
				itemImpl->setType(ArmorImplementation::HAND);
				break;
			case 4 :
				itemImpl = new ArmorImplementation(creature, 0x770C3F1B, 
						unicode("Mandalorian Leggings"), "armor_mandalorian_pants", false);
				itemImpl->setType(ArmorImplementation::LEG);
				break;
			case 5 :
				itemImpl = new ArmorImplementation(creature, 0x82309ECC, 
						unicode("Mandalorian Bicep"), "armor_mandalorian_bicep_l", false);
				itemImpl->setType(ArmorImplementation::BICEPL);
				break;
			case 6 :
				itemImpl = new ArmorImplementation(creature, 0xF2E5DB5F, 
						unicode("Mandalorian Bicep"), "armor_mandalorian_bicep_r", false);
				itemImpl->setType(ArmorImplementation::BICEPR);
				break;
			case 7 :
				itemImpl = new ArmorImplementation(creature, 0xF828E204, 
						unicode("Mandalorian Bracer"), "armor_mandalorian_bracer_l", false);
				itemImpl->setType(ArmorImplementation::BRACERL);
				break;
			case 8 :
				itemImpl = new ArmorImplementation(creature, 0x88FDA797, 
						unicode("Mandalorian Bracer"), "armor_mandalorian_bracer_r", false);
				itemImpl->setType(ArmorImplementation::BRACERR);
				break;
			}
		}
		
		break;
	case 3:
		if (objectCRC == 0xBA7F23CD) { 
			switch (System::random(8)) {
			case 0 :
				itemImpl = new ArmorImplementation(creature, 0xF22790E, 
						unicode("Stormtrooper Chestplate"), "armor_stormtrooper_chest", false);
				itemImpl->setType(ArmorImplementation::CHEST);
				break;
			case 1 :
				itemImpl = new ArmorImplementation(creature, 0xC499637D, 
						unicode("Stormtrooper Helmet"), "armor_stormtrooper_helmet", false);
				itemImpl->setType(ArmorImplementation::HEAD);
				break;
			case 2 :
				itemImpl = new ArmorImplementation(creature, 0x7833E9D6, 
						unicode("Stormtrooper Boots"), "armor_stormtrooper_boots", false);
				itemImpl->setType(ArmorImplementation::FOOT);
				break;
			case 3 :
				itemImpl = new ArmorImplementation(creature, 0x72598275, 
						unicode("Stormtrooper Gloves"), "armor_stormtrooper_gloves", false);
				itemImpl->setType(ArmorImplementation::HAND);
				break;
			case 4 :
				itemImpl = new ArmorImplementation(creature, 0x1863926A, 
						unicode("Stormtrooper Leggings"), "armor_stormtrooper_pants", false);
				itemImpl->setType(ArmorImplementation::LEG);
				break;
			case 5 :
				itemImpl = new ArmorImplementation(creature, 0x3BC0061C, 
						unicode("Stormtrooper Bicep"), "armor_stormtrooper_bicep_l", false);
				itemImpl->setType(ArmorImplementation::BICEPL);
				break;
			case 6 :
				itemImpl = new ArmorImplementation(creature, 0x4B15438F, 
						unicode("Stormtrooper Bicep"), "armor_stormtrooper_bicep_r", false);
				itemImpl->setType(ArmorImplementation::BICEPR);
				break;
			case 7 :
				itemImpl = new ArmorImplementation(creature, 0x97474F75, 
						unicode("Stormtrooper Bracer"), "armor_stormtrooper_bracer_l", false);
				itemImpl->setType(ArmorImplementation::BRACERL);
				break;
			case 8 :
				itemImpl = new ArmorImplementation(creature, 0xE7920AE6, 
						unicode("Stormtrooper Bracer"), "armor_stormtrooper_bracer_r", false);
				itemImpl->setType(ArmorImplementation::BRACERR);
				break;
			}
		}
		
		break;
	case 4:
		if (objectCRC == 0x1527DF01 || objectCRC == 0x71F874) {
			switch (System::random(5)) {
			case 0 :
				itemImpl = new ArmorImplementation(creature, 0x98A41A65, 
						unicode("Marine Chestplate"), "armor_marine_chest", false);
				itemImpl->setType(ArmorImplementation::CHEST);
				break;
			case 1 :
				itemImpl = new ArmorImplementation(creature, 0x1890B6F4, 
						unicode("Marine Helmet"), "armor_marine_helmet", false);
				itemImpl->setType(ArmorImplementation::HEAD);
				break;
			case 2 :
				itemImpl = new ArmorImplementation(creature, 0xA06D625, 
						unicode("Marine Boots"), "armor_marine_boots", false);
				itemImpl->setType(ArmorImplementation::FOOT);
				break;
			case 3 :
				itemImpl = new ArmorImplementation(creature, 0xF3D42F59, 
						unicode("Marine Leggings"), "armor_marine_pants", false);
				itemImpl->setType(ArmorImplementation::LEG);
				break;
			case 4 :
				itemImpl = new ArmorImplementation(creature, 0x16825F91, 
						unicode("Marine Bicep"), "armor_marine_bicep_l", false);
				itemImpl->setType(ArmorImplementation::BICEPL);
				break;
			case 5 :
				itemImpl = new ArmorImplementation(creature, 0x66571A02, 
						unicode("Marine Bicep"), "armor_marine_bicep_r", false);
				itemImpl->setType(ArmorImplementation::BICEPR);
				break;
			}
		}
		break;
	case 5:
		if ((objectCRC == 0xF0663601 || objectCRC == 0xAA197516) && System::random(10) == 7) {
			itemImpl = new ArmorImplementation(creature, 0x2E943BD2, unicode("Nightsister Bicep"), "nightsister_bicep_r", false);
			itemImpl->setType(ArmorImplementation::BICEPR);
		break;
		}
	}
		
	if (itemImpl != NULL) {
		itemImpl->setHealthEncumbrance((System::random(7) + 9) * 19 / 3 + itemImpl->getType());
		itemImpl->setActionEncumbrance((System::random(8) + 9) * 18 / 3 + itemImpl->getType());
		itemImpl->setMindEncumbrance((System::random(9) + 9) * 17 / 3 + itemImpl->getType());		

		item = (Armor*) itemImpl->deploy();
		
		item->setArmorStats(creatureLevel / 2);
		item->setConditionDamage(System::random(item->getMaxCondition() * 3 / 4));
		creature->addLootItem(item);
	}
}

void LootManager::createClothingLoot(Creature* creature, int32 creatureLevel) {
	Wearable* item = NULL;
	WearableImplementation* itemImpl = NULL;
	
	uint32 objectCRC = creature->getObjectCRC();
	
	switch (System::random(5)) {
	case 0 :
		itemImpl = new WearableImplementation(creature, 0x29031E7D,
				unicode("Tusken Boots"), "boots_tusken_raider", false);
		break;
	case 1 :
		itemImpl = new WearableImplementation(creature, 0x67A25943, 
				unicode("Tusken Gloves"), "gloves_tusken_raider", false);
		break;
	case 2 :
		itemImpl = new WearableImplementation(creature, 0xF7B87D4B, 
				unicode("Tusken Helmet"), "helmet_tusken_raider", false);
		break;
	case 3 :
		itemImpl = new WearableImplementation(creature, 0x50EF8B3E, 
				unicode("Tusken Robe"), "robe_tusken_raider", false);
		break;
	case 4 :
		itemImpl = new WearableImplementation(creature, 0xFC978255, 
				unicode("Chef Hat"), "hat_chef", false);
		break;
	case 5 :
		itemImpl = new WearableImplementation(creature, 0x6CE36E4C, 
				unicode("Aakuan Shirt"), "aakuan_shirt", false);
		break;
	}
	
	if (itemImpl != NULL) {
		item = (Wearable*) itemImpl->deploy();
		
		item->setConditionDamage(System::random(item->getMaxCondition()*3/4));
		creature->addLootItem(item);
	}
}


void LootManager::createJunkLoot(Creature* creature) {
	TangibleObject* item = NULL;
	TangibleObjectImplementation* itemImpl = NULL;
	
	switch (System::random(10)) {
	case 0 :
		itemImpl = new TangibleObjectImplementation(creature, unicode("a Viewscreen (broken)"), 
				"object/tangible/loot/tool/shared_viewscreen_broken_s2.iff", 0xBC03F94);
		break;
	case 1 :
		itemImpl = new TangibleObjectImplementation(creature, unicode("Binoculars (broken)"), 
				"object/tangible/loot/tool/shared_binoculars_broken_s1.iff", 0x1E84585F);
		break;
	case 2 :
		itemImpl = new TangibleObjectImplementation(creature, unicode("a Human Skull"), 
				"object/tangible/loot/misc/shared_loot_skull_human.iff", 0x25B24532);
		break;
	case 3 :
		itemImpl = new TangibleObjectImplementation(creature, unicode("an Impulse Detector (broken)"), 
				"/tangible/loot/tool/shared_impulse_detector_broken_s3.iff", 0x2D13F714);
		break;
	case 4 :
		itemImpl = new TangibleObjectImplementation(creature, unicode("a Cage"), 
				"object/tangible/loot/misc/shared_cage_s01.iff", 0x3238DD4A);
		break;
	case 5 :
		itemImpl = new TangibleObjectImplementation(creature, unicode("a Rare Artifact"), 
				"object/tangible/loot/misc/shared_artifact_rare_s01.iff", 0x3393694D);
		break;
	case 6 :
		itemImpl = new TangibleObjectImplementation(creature, unicode("Holocron Splinters"), 
				"object/tangible/loot/misc/shared_holocron_splinters_sith_s01.iff", 0x3CEA7897);
		break;
	case 7 :
		itemImpl = new TangibleObjectImplementation(creature, unicode("a Calibrator (broken)"), 
				"object/tangible/loot/tool/shared_calibrator_broken.iff", 0x5289E0D9);
		break;
	case 8 :
		itemImpl = new TangibleObjectImplementation(creature, unicode("a Corrupt Datadisk"), 
				"object/tangible/loot/misc/shared_datadisk_corrupt.iff", 0x5F4B8D76);
		break;
	case 9 :
		itemImpl = new TangibleObjectImplementation(creature, unicode("Jawa Beads"), 
				"object/tangible/loot/misc/shared_jawa_beads.iff", 0x619F4DFD);
		break;
	case 10 :
		itemImpl = new TangibleObjectImplementation(creature, unicode("a Briefcase"), 
				"object/tangible/loot/misc/shared_briefcase_s01.iff", 0x6C34F325);
		break;
	case 11 :
		itemImpl = new FireworkImplementation(((Player*)creature), 0x7C540DEB, 
				unicode("a Firework"), "object/tangible/firework/shared_firework_s04.iff");
		break;
	case 12 :
		itemImpl = new HolocronImplementation(((Player*)creature), 0x9BA06548, 
				unicode("Holocron"), "object/tangible/jedi/shared_jedi_holocron_light.iff");
		break;
	}
	
	if (itemImpl != NULL) {
		item = itemImpl->deploy();

		creature->addLootItem(item);
	}
}

void LootManager::createAttachmentLoot(Creature* creature, int creatureLevel) {
	Attachment* item = NULL;
	AttachmentImplementation* itemImpl = NULL;
	
	itemImpl = new AttachmentImplementation(creature->getNewItemID(), AttachmentImplementation::ARMOR);
	
	if (itemImpl != NULL) {
		itemImpl->setSkillMods(creatureLevel / 2);
		
		item = itemImpl->deploy();
		creature->addLootItem(item);
	}
}

void LootManager::createPowerupLoot(Creature* creature, int creatureLevel) {
	Powerup* item = NULL;
	PowerupImplementation* itemImpl = NULL;
	
	itemImpl = new PowerupImplementation(creature->getNewItemID());
	
	if (itemImpl != NULL) {
		itemImpl->setPowerupStats(creatureLevel);
		
		item = itemImpl->deploy();
		creature->addLootItem(item);
	}
}
