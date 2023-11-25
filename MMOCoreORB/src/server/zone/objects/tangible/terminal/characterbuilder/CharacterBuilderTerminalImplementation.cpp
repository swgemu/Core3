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

	// info(true) << " giveDnaTestingSet -- called for DNA set: " << testName;

	Lua* lua = new Lua();
	lua->init();

	lua->runFile("scripts/managers/crafting/bio_dna_sets.lua");

	LuaObject luaObject = lua->getGlobalObject("dnaTests");

	if (!luaObject.isValidTable()) {
		return;
	}

	// info(true) << "dnaTests table is valid -- with a size of " << luaObject.getTableSize();

	for (int i = 1; i <= luaObject.getTableSize(); i++) {
		LuaObject checkTable = luaObject.getObjectAt(i);

		//info(true) << "Table Num: " << i;

		if (!checkTable.isValidTable())
			continue;

		String tableName = checkTable.getStringAt(1);

		// info(true) << "Checking against table name: " << tableName;

		if (tableName != testName) {
			checkTable.pop();
			continue;
		}

		readDnaTable(&checkTable, player, testName);

		checkTable.pop();
		break;
	}

	luaObject.pop();

	delete lua;
	lua = nullptr;
}

void CharacterBuilderTerminalImplementation::readDnaTable(LuaObject* dnaSetTable, CreatureObject* player, const String& testName) {
	if (dnaSetTable == nullptr || player == nullptr)
		return;

	// info(true) << "DNASet table is valid with a size of: " << dnaSetTable->getTableSize();

	auto zoneServer = player->getZoneServer();

	if (zoneServer == nullptr)
		return;

	auto craftingManager = zoneServer->getCraftingManager();

	if (craftingManager == nullptr)
		return;

	ManagedReference<SceneObject*> inventory = player->getSlottedObject("inventory");

	if (inventory == nullptr)
		return;

	Locker lock(player);

	for (int i = 2; i <= dnaSetTable->getTableSize(); i++) {
		// info(true) << "pulling DNA Sample: " << i;

		LuaObject dnaTable = dnaSetTable->getObjectAt(i);

		if (!dnaTable.isValidTable()) {
			continue;
		}

		int quality = dnaTable.getIntField("quality");
		String type = "object/tangible/component/dna/dna_sample_average.iff";

		if (quality == 1) {
			type = "object/tangible/component/dna/dna_sample_very_high.iff";
		} else if (quality == 2) {
			type = "object/tangible/component/dna/dna_sample_high.iff";
		} else if (quality == 3) {
			type = "object/tangible/component/dna/dna_sample_above_average.iff";
		} else if (quality == 5) {
			type = "object/tangible/component/dna/dna_sample_below_average.iff";
		} else if (quality == 6) {
			type = "object/tangible/component/dna/dna_sample_low.iff";
		} else if (quality == 7) {
			type = "object/tangible/component/dna/dna_sample_very_low.iff";
		}

		ManagedReference<DnaComponent*> prototype = zoneServer->createObject(type.hashCode(), 1).castTo<DnaComponent*>();

		if (prototype == nullptr)
			continue;

		Locker plock(prototype, player);

		prototype->setSource(dnaTable.getStringField("source"));

		prototype->setQuality(quality);
		prototype->setLevel(dnaTable.getIntField("level"));

		prototype->setSerialNumber(craftingManager->generateSerial());

		// setStats(int cle, int end, int fie, int pow, int ite, int cou, int dep, int dex, int frt, int har)
		prototype->setStats(dnaTable.getIntField("cleverness"), dnaTable.getIntField("endurance"), dnaTable.getIntField("fierocity"), dnaTable.getIntField("power"), dnaTable.getIntField("intellect"), dnaTable.getIntField("courage"), dnaTable.getIntField("dependability"), dnaTable.getIntField("dexterity"),
							dnaTable.getIntField("fortitude"), dnaTable.getIntField("hardiness"));

		prototype->setStun(dnaTable.getFloatField("stun"));
		prototype->setKinetic(dnaTable.getFloatField("kinetic"));
		prototype->setEnergy(dnaTable.getFloatField("energy"));
		prototype->setBlast(dnaTable.getFloatField("blast"));
		prototype->setHeat(dnaTable.getFloatField("heat"));
		prototype->setCold(dnaTable.getFloatField("cold"));
		prototype->setElectric(dnaTable.getFloatField("electric"));
		prototype->setAcid(dnaTable.getFloatField("acid"));
		prototype->setSaber(dnaTable.getFloatField("lightsaber"));

		prototype->setArmorRating(dnaTable.getIntField("armorRating"));
		prototype->setRanged(dnaTable.getBooleanField("ranged"));

		LuaObject specialResists = dnaTable.getObjectField("specialResists");

		if (specialResists.isValidTable()) {
			for (int j = 1; j <= specialResists.getTableSize(); j++) {
				int resist = specialResists.getIntAt(j);

				// info(true) << "Adding special resists: " << resist;

				prototype->setSpecialResist(resist);
			}
		}

		specialResists.pop();

		prototype->setSpecialAttackOne(dnaTable.getStringField("special1"));
		prototype->setSpecialAttackTwo(dnaTable.getStringField("special2"));

		plock.release();

		Locker locker(inventory, player);

		if (inventory->transferObject(prototype, -1, true, false)) {
			inventory->broadcastObject(prototype, true);
		} else {
			prototype->destroyObjectFromDatabase(true);
		}

		dnaTable.pop();
	}
}
