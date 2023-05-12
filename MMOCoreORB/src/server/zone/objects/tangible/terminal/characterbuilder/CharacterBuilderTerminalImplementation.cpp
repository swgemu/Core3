#include "server/zone/objects/tangible/terminal/characterbuilder/CharacterBuilderTerminal.h"
#include "server/zone/objects/creature/CreatureObject.h"
#include "server/zone/objects/creature/ai/AiAgent.h"
#include "server/zone/objects/player/sui/characterbuilderbox/SuiCharacterBuilderBox.h"
#include "server/zone/managers/skill/SkillManager.h"
#include "templates/tangible/CharacterBuilderTerminalTemplate.h"
#include "server/zone/objects/player/PlayerObject.h"
#include "server/zone/managers/player/PlayerManager.h"
#include "server/zone/managers/jedi/JediManager.h"
#include "server/zone/managers/director/DirectorManager.h"
#include "server/zone/objects/tangible/component/dna/DnaComponent.h"
#include "server/zone/managers/crafting/CraftingManager.h"

void CharacterBuilderTerminalImplementation::loadTemplateData(SharedObjectTemplate* templateData) {
	TangibleObjectImplementation::loadTemplateData(templateData);

	CharacterBuilderTerminalTemplate* terminalData = dynamic_cast<CharacterBuilderTerminalTemplate*>(templateData);

	if (terminalData == nullptr)
		return;

	rootNode = terminalData->getItemList();
}

void CharacterBuilderTerminalImplementation::initializeTransientMembers() {
	TerminalImplementation::initializeTransientMembers();

	setLoggingName("CharacterBuilderTerminal");
}

int CharacterBuilderTerminalImplementation::handleObjectMenuSelect(CreatureObject* player, byte selectedID) {
	if (!ConfigManager::instance()->getCharacterBuilderEnabled())
		return 1;

	debug() << "entering start terminal radial call";

	if (selectedID != 20) // not use object
		return 1;

	sendInitialChoices(player);

	return 0;
}

void CharacterBuilderTerminalImplementation::sendInitialChoices(CreatureObject* player) {
	if (!ConfigManager::instance()->getCharacterBuilderEnabled())
		return;

	debug() << "entering sendInitialChoices";

	if (rootNode == nullptr) {
		player->sendSystemMessage("There was an error initializing the menu for this character builder terminal. Sorry for the inconvenience.");
		return;
	}

	ManagedReference<SuiCharacterBuilderBox*> sui = new SuiCharacterBuilderBox(player, rootNode);
	sui->setUsingObject(_this.getReferenceUnsafeStaticCast());

	player->sendMessage(sui->generateMessage());
	player->getPlayerObject()->addSuiBox(sui);
}

void CharacterBuilderTerminalImplementation::enhanceCharacter(CreatureObject* player) {
	PlayerManager* pm = player->getZoneServer()->getPlayerManager();

	pm->enhanceCharacter(player);

	ManagedReference<PlayerObject*> ghost = player->getPlayerObject();

	if (ghost == nullptr)
		return;

	for (int i = 0; i < ghost->getActivePetsSize(); i++) {
		ManagedReference<AiAgent*> pet = ghost->getActivePet(i);

		if (pet != nullptr) {
			Locker crossLocker(pet, player);

			pm->enhanceCharacter(pet);
		}
	}
}

void CharacterBuilderTerminalImplementation::giveLanguages(CreatureObject* player) {
	SkillManager* skillManager = server->getSkillManager();

	skillManager->awardSkill("social_language_basic_speak", player, true, true, true);
	skillManager->awardSkill("social_language_basic_comprehend", player, true, true, true);
	skillManager->awardSkill("social_language_rodian_speak", player, true, true, true);
	skillManager->awardSkill("social_language_rodian_comprehend", player, true, true, true);
	skillManager->awardSkill("social_language_trandoshan_speak", player, true, true, true);
	skillManager->awardSkill("social_language_trandoshan_comprehend", player, true, true, true);
	skillManager->awardSkill("social_language_moncalamari_speak", player, true, true, true);
	skillManager->awardSkill("social_language_moncalamari_comprehend", player, true, true, true);
	skillManager->awardSkill("social_language_wookiee_speak", player, true, true, true);
	skillManager->awardSkill("social_language_wookiee_comprehend", player, true, true, true);
	skillManager->awardSkill("social_language_bothan_speak", player, true, true, true);
	skillManager->awardSkill("social_language_bothan_comprehend", player, true, true, true);
	skillManager->awardSkill("social_language_twilek_speak", player, true, true, true);
	skillManager->awardSkill("social_language_twilek_comprehend", player, true, true, true);
	skillManager->awardSkill("social_language_zabrak_speak", player, true, true, true);
	skillManager->awardSkill("social_language_zabrak_comprehend", player, true, true, true);
	skillManager->awardSkill("social_language_lekku_speak", player, true, true, true);
	skillManager->awardSkill("social_language_lekku_comprehend", player, true, true, true);
	skillManager->awardSkill("social_language_ithorian_speak", player, true, true, true);
	skillManager->awardSkill("social_language_ithorian_comprehend", player, true, true, true);
	skillManager->awardSkill("social_language_sullustan_speak", player, true, true, true);
	skillManager->awardSkill("social_language_sullustan_comprehend", player, true, true, true);
}

void CharacterBuilderTerminalImplementation::grantGlowyBadges(CreatureObject* player) {
	CharacterBuilderTerminalTemplate* terminalTemplate = dynamic_cast<CharacterBuilderTerminalTemplate*>(templateObject.get());

	if (terminalTemplate == nullptr)
		return;

	PlayerObject* ghost = player->getPlayerObject();

	if (ghost == nullptr)
		return;

	const auto& ids = terminalTemplate->getGlowyBadgeIds();

	for (int i = 0; i < ids.size(); i++) {
		ghost->awardBadge(ids.get(i));
	}
}

void CharacterBuilderTerminalImplementation::grantJediInitiate(CreatureObject* player) {
	if (JediManager::instance()->getJediProgressionType() != JediManager::VILLAGEJEDIPROGRESSION)
		return;

	CharacterBuilderTerminalTemplate* terminalTemplate = dynamic_cast<CharacterBuilderTerminalTemplate*>(templateObject.get());

	if (terminalTemplate == nullptr)
		return;

	PlayerObject* ghost = player->getPlayerObject();

	if (ghost == nullptr)
		return;

	SkillManager* skillManager = server->getSkillManager();

	grantGlowyBadges(player);

	Lua* lua = DirectorManager::instance()->getLuaInstance();

	Reference<LuaFunction*> luaVillageGmCmd = lua->createFunction("FsIntro", "completeVillageIntroFrog", 0);
	*luaVillageGmCmd << player;

	luaVillageGmCmd->callFunction();

	const auto& branches = terminalTemplate->getVillageBranchUnlocks();

	for (int i = 0; i < branches.size(); i++) {
		String branch = branches.get(i);
		player->setScreenPlayState("VillageUnlockScreenPlay:" + branch, 2);
		skillManager->awardSkill(branch + "_04", player, true, true, true);
	}

	luaVillageGmCmd = lua->createFunction("FsOutro", "completeVillageOutroFrog", 0);
	*luaVillageGmCmd << player;

	luaVillageGmCmd->callFunction();
}

void CharacterBuilderTerminalImplementation::giveDnaTestingSet(CreatureObject* player, const String& testName) {
	if (player == nullptr)
		return;

	ZoneServer* zoneServer = player->getZoneServer();

	if (zoneServer == nullptr)
		return;

	ManagedReference<SceneObject*> inventory = player->getSlottedObject("inventory");

	if (inventory == nullptr)
		return;

	/*
	1,"object/tangible/component/dna/dna_sample_very_high.iff")
	2,"object/tangible/component/dna/dna_sample_high.iff")
	3,"object/tangible/component/dna/dna_sample_above_average.iff")
	4,"object/tangible/component/dna/dna_sample_average.iff")
	5,"object/tangible/component/dna/dna_sample_below_average.iff")
	6,"object/tangible/component/dna/dna_sample_low.iff")
	7,"object/tangible/component/dna/dna_sample_very_low.iff")
	*/

	Locker lock(player);

	// http://pets.furrycat.net/creature.html?ju6d14qq
	if (testName == "ju6d14qq") {
		// DNA 1
		ManagedReference<DnaComponent*> prototype1 = player->getZoneServer()->createObject(STRING_HASHCODE("object/tangible/component/dna/dna_sample_high.iff"), 1).castTo<DnaComponent*>();

		if (prototype1 != nullptr) {
			Locker plock(prototype1, player);

			prototype1->setSource("greater sludge panther");

			prototype1->setQuality(2); // High
			prototype1->setLevel(25);

			String serial = zoneServer->getCraftingManager()->generateSerial();
			prototype1->setSerialNumber(serial);

			// setStats(int cle, int end, int fie, int pow, int ite, int cou, int dep, int dex, int frt, int har)
			prototype1->setStats( 244, 509, 418, 308, 445, 508, 956, 440, 112, 484);
			prototype1->setStun(-30);
			prototype1->setKinetic(35);
			prototype1->setEnergy(10);
			prototype1->setBlast(10);
			prototype1->setHeat(-49);
			prototype1->setCold(-27);
			prototype1->setElectric(-50);
			prototype1->setAcid(45);
			prototype1->setSaber(-99);

			prototype1->setArmorRating(0);
			prototype1->setRanged(false);

			prototype1->setSpecialResist(SharedWeaponObjectTemplate::KINETIC);
			prototype1->setSpecialResist(SharedWeaponObjectTemplate::ACID);

			plock.release();

			Locker locker(inventory, player);

			if (inventory->transferObject(prototype1, -1, true, false)) {
				inventory->broadcastObject(prototype1, true);
			} else {
				prototype1->destroyObjectFromDatabase(true);
			}
		}

		// DNA 2
		ManagedReference<DnaComponent*> prototype2 = player->getZoneServer()->createObject(STRING_HASHCODE("object/tangible/component/dna/dna_sample_above_average.iff"), 1).castTo<DnaComponent*>();

		if (prototype2 != nullptr) {
			Locker plock(prototype2, player);

			prototype2->setSource("greater sludge panther");

			prototype2->setQuality(3); // Above Average
			prototype2->setLevel(25);

			String serial = zoneServer->getCraftingManager()->generateSerial();
			prototype2->setSerialNumber(serial);

			//setStats(int cle, int end, int fie, int pow, int ite, int cou, int dep, int dex, int frt, int har)
			prototype2->setStats( 235, 500, 418, 304, 448, 505, 960, 443, 109, 478);
			prototype2->setStun(-55);
			prototype2->setKinetic(35);
			prototype2->setEnergy(10);
			prototype2->setBlast(10);
			prototype2->setHeat(-49);
			prototype2->setCold(-27);
			prototype2->setElectric(-50);
			prototype2->setAcid(45);
			prototype2->setSaber(-99);

			prototype2->setArmorRating(0);
			prototype2->setRanged(false);

			prototype2->setSpecialResist(SharedWeaponObjectTemplate::KINETIC);
			prototype2->setSpecialResist(SharedWeaponObjectTemplate::ACID);

			plock.release();

			Locker locker(inventory, player);

			if (inventory->transferObject(prototype2, -1, true, false)) {
				inventory->broadcastObject(prototype2, true);
			} else {
				prototype2->destroyObjectFromDatabase(true);
			}
		}

		// DNA 3
		ManagedReference<DnaComponent*> prototype3 = player->getZoneServer()->createObject(STRING_HASHCODE("object/tangible/component/dna/dna_sample_very_high.iff"), 1).castTo<DnaComponent*>();

		if (prototype3 != nullptr) {
			Locker plock(prototype2, player);

			prototype3->setSource("shaupaut hunter");

			prototype3->setQuality(1); // Very High
			prototype3->setLevel(22);

			String serial = zoneServer->getCraftingManager()->generateSerial();
			prototype3->setSerialNumber(serial);

			//setStats(int cle, int end, int fie, int pow, int ite, int cou, int dep, int dex, int frt, int har)
			prototype3->setStats( 225, 518, 514, 265, 342, 519, 1000, 320, 114, 354);
			prototype3->setStun(-30);
			prototype3->setKinetic(20);
			prototype3->setEnergy(20);
			prototype3->setBlast(10);
			prototype3->setHeat(-49);
			prototype3->setCold(10);
			prototype3->setElectric(-50);
			prototype3->setAcid(10);
			prototype3->setSaber(-99);

			prototype3->setArmorRating(0);
			prototype3->setRanged(false);

			prototype3->setSpecialResist(SharedWeaponObjectTemplate::KINETIC);
			prototype3->setSpecialResist(SharedWeaponObjectTemplate::ENERGY);

			plock.release();

			Locker locker(inventory, player);

			if (inventory->transferObject(prototype3, -1, true, false)) {
				inventory->broadcastObject(prototype3, true);
			} else {
				prototype3->destroyObjectFromDatabase(true);
			}
		}

		// DNA 4
		ManagedReference<DnaComponent*> prototype4 = player->getZoneServer()->createObject(STRING_HASHCODE("object/tangible/component/dna/dna_sample_high.iff"), 1).castTo<DnaComponent*>();

		if (prototype4 != nullptr) {
			Locker plock(prototype4, player);

			prototype4->setSource("corellian butteryfly defender");

			prototype4->setQuality(1); // High
			prototype4->setLevel(18);

			String serial = zoneServer->getCraftingManager()->generateSerial();
			prototype4->setSerialNumber(serial);

			//setStats(int cle, int end, int fie, int pow, int ite, int cou, int dep, int dex, int frt, int har)
			prototype4->setStats( 190, 506, 96, 270, 130, 509, 755, 124, 60, 125);
			prototype4->setStun(-30);
			prototype4->setKinetic(5);
			prototype4->setEnergy(15);
			prototype4->setBlast(-30);
			prototype4->setHeat(-56);
			prototype4->setCold(-27);
			prototype4->setElectric(-50);
			prototype4->setAcid(-78);
			prototype4->setSaber(-99);

			prototype4->setArmorRating(0);
			prototype4->setRanged(false);

			prototype4->setSpecialResist(SharedWeaponObjectTemplate::ENERGY);

			plock.release();

			Locker locker(inventory, player);

			if (inventory->transferObject(prototype4, -1, true, false)) {
				inventory->broadcastObject(prototype4, true);
			} else {
				prototype4->destroyObjectFromDatabase(true);
			}
		}

		// DNA 5
		ManagedReference<DnaComponent*> prototype5 = player->getZoneServer()->createObject(STRING_HASHCODE("object/tangible/component/dna/dna_sample_high.iff"), 1).castTo<DnaComponent*>();

		if (prototype5 != nullptr) {
			Locker plock(prototype5, player);

			prototype5->setSource("savage guf drolg");

			prototype5->setQuality(1); // High
			prototype5->setLevel(15);

			String serial = zoneServer->getCraftingManager()->generateSerial();
			prototype5->setSerialNumber(serial);

			//setStats(int cle, int end, int fie, int pow, int ite, int cou, int dep, int dex, int frt, int har)
			prototype5->setStats( 183, 514, 104, 220, 139, 510, 763, 163, 62, 148);
			prototype5->setStun(-30);
			prototype5->setKinetic(10);
			prototype5->setEnergy(5);
			prototype5->setBlast(5);
			prototype5->setHeat(-49);
			prototype5->setCold(-27);
			prototype5->setElectric(-50);
			prototype5->setAcid(-86);
			prototype5->setSaber(-99);

			prototype5->setArmorRating(0);
			prototype5->setRanged(false);

			prototype5->setSpecialResist(SharedWeaponObjectTemplate::KINETIC);

			plock.release();

			Locker locker(inventory, player);

			if (inventory->transferObject(prototype5, -1, true, false)) {
				inventory->broadcastObject(prototype5, true);
			} else {
				prototype5->destroyObjectFromDatabase(true);
			}
		}
	} else if (testName == "d5j7caq6") {
		// DNA 1
		ManagedReference<DnaComponent*> prototype1 = player->getZoneServer()->createObject(STRING_HASHCODE("object/tangible/component/dna/dna_sample_very_high.iff"), 1).castTo<DnaComponent*>();

		if (prototype1 != nullptr) {
			Locker plock(prototype1, player);

			prototype1->setSource("reclusive cavern spider queen");

			prototype1->setQuality(1); // Very High
			prototype1->setLevel(70);

			String serial = zoneServer->getCraftingManager()->generateSerial();
			prototype1->setSerialNumber(serial);

								//(cle, end, fier, pow, inte, cour, dep, dex, fort, har)
			prototype1->setStats( 709, 516, 471, 786, 767, 516, 512, 726, 717, 769);

			prototype1->setKinetic(60);
			prototype1->setEnergy(60);
			prototype1->setBlast(60);
			prototype1->setHeat(50);
			prototype1->setCold(20);
			prototype1->setElectric(20);
			prototype1->setAcid(20);
			prototype1->setStun(20);
			prototype1->setSaber(-99);

			prototype1->setArmorRating(1);
			prototype1->setRanged(false);

			prototype1->setSpecialResist(SharedWeaponObjectTemplate::KINETIC);
			prototype1->setSpecialResist(SharedWeaponObjectTemplate::ENERGY);
			prototype1->setSpecialResist(SharedWeaponObjectTemplate::BLAST);
			prototype1->setSpecialResist(SharedWeaponObjectTemplate::HEAT);

			plock.release();

			Locker locker(inventory, player);

			if (inventory->transferObject(prototype1, -1, true, false)) {
				inventory->broadcastObject(prototype1, true);
			} else {
				prototype1->destroyObjectFromDatabase(true);
			}
		}

		// DNA 2
		ManagedReference<DnaComponent*> prototype2 = player->getZoneServer()->createObject(STRING_HASHCODE("object/tangible/component/dna/dna_sample_very_high.iff"), 1).castTo<DnaComponent*>();

		if (prototype2 != nullptr) {
			Locker plock(prototype2, player);

			prototype2->setSource("reclusive cavern spider queen");

			prototype2->setQuality(1); // Very High
			prototype2->setLevel(70);

			String serial = zoneServer->getCraftingManager()->generateSerial();
			prototype2->setSerialNumber(serial);

								//(cle, end, fier, pow, inte, cour, dep, dex, fort, har)
			prototype2->setStats(708, 517, 474, 790, 675, 516, 520, 706, 720, 644);

			prototype2->setKinetic(60);
			prototype2->setEnergy(60);
			prototype2->setBlast(60);
			prototype2->setHeat(50);
			prototype2->setCold(20);
			prototype2->setElectric(20);
			prototype2->setAcid(20);
			prototype2->setStun(20);
			prototype2->setSaber(-99);

			prototype2->setArmorRating(1);
			prototype2->setRanged(false);

			prototype2->setSpecialResist(SharedWeaponObjectTemplate::KINETIC);
			prototype2->setSpecialResist(SharedWeaponObjectTemplate::ENERGY);
			prototype2->setSpecialResist(SharedWeaponObjectTemplate::BLAST);
			prototype2->setSpecialResist(SharedWeaponObjectTemplate::HEAT);

			plock.release();

			Locker locker(inventory, player);

			if (inventory->transferObject(prototype2, -1, true, false)) {
				inventory->broadcastObject(prototype2, true);
			} else {
				prototype2->destroyObjectFromDatabase(true);
			}
		}

		// DNA 3
		ManagedReference<DnaComponent*> prototype3 = player->getZoneServer()->createObject(STRING_HASHCODE("object/tangible/component/dna/dna_sample_very_high.iff"), 1).castTo<DnaComponent*>();

		if (prototype3 != nullptr) {
			Locker plock(prototype2, player);

			prototype3->setSource("reclusive cavern spider queen");

			prototype3->setQuality(1); // Very High
			prototype3->setLevel(70);


			String serial = zoneServer->getCraftingManager()->generateSerial();
			prototype3->setSerialNumber(serial);

								//(cle, end, fier, pow, inte, cour, dep, dex, fort, har)
			prototype3->setStats( 711, 515, 469, 792, 675, 510, 510, 710, 718, 637);

			prototype3->setKinetic(60);
			prototype3->setEnergy(60);
			prototype3->setBlast(60);
			prototype3->setHeat(50);
			prototype3->setCold(20);
			prototype3->setElectric(20);
			prototype3->setAcid(20);
			prototype3->setStun(20);
			prototype3->setSaber(-99);

			prototype3->setArmorRating(1);
			prototype3->setRanged(false);

			prototype3->setSpecialResist(SharedWeaponObjectTemplate::KINETIC);
			prototype3->setSpecialResist(SharedWeaponObjectTemplate::ENERGY);
			prototype3->setSpecialResist(SharedWeaponObjectTemplate::BLAST);
			prototype3->setSpecialResist(SharedWeaponObjectTemplate::HEAT);

			plock.release();

			Locker locker(inventory, player);

			if (inventory->transferObject(prototype3, -1, true, false)) {
				inventory->broadcastObject(prototype3, true);
			} else {
				prototype3->destroyObjectFromDatabase(true);
			}
		}

		// DNA 4
		ManagedReference<DnaComponent*> prototype4 = player->getZoneServer()->createObject(STRING_HASHCODE("object/tangible/component/dna/dna_sample_above_average.iff"), 1).castTo<DnaComponent*>();

		if (prototype4 != nullptr) {
			Locker plock(prototype4, player);

			prototype4->setSource("reclusive cavern spider queen");

			prototype4->setQuality(3); // Above Average
			prototype4->setLevel(70);


			String serial = zoneServer->getCraftingManager()->generateSerial();
			prototype4->setSerialNumber(serial);

								//(cle, end, fier, pow, inte, cour, dep, dex, fort, har)
			prototype4->setStats( 697, 507, 456, 776, 759, 505, 503, 713, 705, 759);

			prototype4->setKinetic(60);
			prototype4->setEnergy(60);
			prototype4->setBlast(60);
			prototype4->setHeat(50);
			prototype4->setCold(20);
			prototype4->setElectric(20);
			prototype4->setAcid(20);
			prototype4->setStun(20);
			prototype4->setSaber(-99);

			prototype4->setArmorRating(1);
			prototype4->setRanged(false);

			prototype4->setSpecialResist(SharedWeaponObjectTemplate::KINETIC);
			prototype4->setSpecialResist(SharedWeaponObjectTemplate::ENERGY);
			prototype4->setSpecialResist(SharedWeaponObjectTemplate::BLAST);
			prototype4->setSpecialResist(SharedWeaponObjectTemplate::HEAT);

			plock.release();

			Locker locker(inventory, player);

			if (inventory->transferObject(prototype4, -1, true, false)) {
				inventory->broadcastObject(prototype4, true);
			} else {
				prototype4->destroyObjectFromDatabase(true);
			}
		}

		// DNA 5
		ManagedReference<DnaComponent*> prototype5 = player->getZoneServer()->createObject(STRING_HASHCODE("object/tangible/component/dna/dna_sample_high.iff"), 1).castTo<DnaComponent*>();

		if (prototype5 != nullptr) {
			Locker plock(prototype5, player);

			prototype5->setSource("kimogila");

			prototype5->setQuality(1); // High
			prototype5->setLevel(95);

			String serial = zoneServer->getCraftingManager()->generateSerial();
			prototype5->setSerialNumber(serial);

								//(cle, end, fier, pow, inte, cour, dep, dex, fort, har)
			prototype5->setStats( 434, 586, 97, 605, 568, 343, 758, 609, 629, 659);

			prototype5->setKinetic(45);
			prototype5->setEnergy(51);
			prototype5->setBlast(49);
			prototype5->setHeat(56);
			prototype5->setCold(32);
			prototype5->setElectric(67);
			prototype5->setAcid(26);
			prototype5->setStun(49);
			prototype5->setSaber(-99);

			prototype5->setArmorRating(1);
			prototype5->setRanged(false);

			prototype5->setSpecialResist(SharedWeaponObjectTemplate::KINETIC);
			prototype5->setSpecialResist(SharedWeaponObjectTemplate::ENERGY);
			prototype5->setSpecialResist(SharedWeaponObjectTemplate::BLAST);
			prototype5->setSpecialResist(SharedWeaponObjectTemplate::HEAT);
			prototype5->setSpecialResist(SharedWeaponObjectTemplate::COLD);
			prototype5->setSpecialResist(SharedWeaponObjectTemplate::ELECTRICITY);
			prototype5->setSpecialResist(SharedWeaponObjectTemplate::ACID);
			prototype5->setSpecialResist(SharedWeaponObjectTemplate::STUN);

			Locker locker(inventory, player);

			if (inventory->transferObject(prototype5, -1, true, false)) {
				inventory->broadcastObject(prototype5, true);
			} else {
				prototype5->destroyObjectFromDatabase(true);
			}
		}
	}
}
