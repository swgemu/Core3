/*
				Copyright <SWGEmu>
		See file COPYING for copying conditions.
*/

#include "server/db/ServerDatabase.h"
#include "server/db/MantisDatabase.h"
#include "PlayerCreationManager.h"
#include "ProfessionDefaultsInfo.h"
#include "RacialCreationData.h"
#include "HairStyleInfo.h"
#include "server/zone/managers/player/PlayerManager.h"
#include "server/login/packets/ErrorMessage.h"
#include "server/chat/ChatManager.h"
#include "server/login/account/Account.h"
#include "server/zone/objects/player/sui/messagebox/SuiMessageBox.h"
#include "server/zone/objects/player/PlayerObject.h"
#include "server/zone/packets/MessageCallback.h"
#include "server/zone/packets/charcreation/ClientCreateCharacterCallback.h"
#include "server/zone/packets/charcreation/ClientCreateCharacterSuccess.h"
#include "server/zone/managers/templates/TemplateManager.h"
#include "server/zone/templates/datatables/DataTableIff.h"
#include "server/zone/templates/datatables/DataTableRow.h"
#include "server/zone/templates/creation/SkillDataForm.h"
#include "server/zone/templates/tangible/PlayerCreatureTemplate.h"
#include "server/ServerCore.h"
#include "server/zone/objects/intangible/ShipControlDevice.h"
#include "server/zone/objects/ship/ShipObject.h"
#include "server/zone/managers/customization/CustomizationIdManager.h"
#include "server/zone/managers/skill/imagedesign/ImageDesignManager.h"
#include "server/zone/templates/customization/AssetCustomizationManagerTemplate.h"
#include "server/zone/templates/params/PaletteColorCustomizationVariable.h"
#include "server/zone/templates/customization/BasicRangedIntCustomizationVariable.h"
#include "server/zone/managers/jedi/JediManager.h"

PlayerCreationManager::PlayerCreationManager() :
		Logger("PlayerCreationManager") {

	setLogging(true);
	setGlobalLogging(false);

	zoneServer = ServerCore::getZoneServer();

	racialCreationData.setNoDuplicateInsertPlan();
	professionDefaultsInfo.setNoDuplicateInsertPlan();
	hairStyleInfo.setNoDuplicateInsertPlan();

	startingCash = 100;
	startingBank = 1000;

	freeGodMode = false;

	loadRacialCreationData();
	loadDefaultCharacterItems();
	loadProfessionDefaultsInfo();
	loadHairStyleInfo();
	loadLuaConfig();
}

PlayerCreationManager::~PlayerCreationManager() {
}

void PlayerCreationManager::loadRacialCreationData() {
	TemplateManager* templateManager = TemplateManager::instance();
	IffStream* iffStream = templateManager->openIffFile(
			"datatables/creation/attribute_limits.iff");

	if (iffStream == NULL) {
		error("Could not open attribute limits file.");
		return;
	}

	DataTableIff attributeLimitsTable;
	attributeLimitsTable.readObject(iffStream);

	delete iffStream;

	iffStream = templateManager->openIffFile(
			"datatables/creation/racial_mods.iff");

	DataTableIff racialModsTable;
	racialModsTable.readObject(iffStream);

	delete iffStream;

	for (int i = 0; i < attributeLimitsTable.getTotalRows(); ++i) {
		DataTableRow* attributeLimitRow = attributeLimitsTable.getRow(i);

		String maleTemplate;
		String femaleTemplate;

		attributeLimitRow->getValue(0, maleTemplate);
		attributeLimitRow->getValue(1, femaleTemplate);

		Vector<DataTableRow*> maleRows = racialModsTable.getRowsByColumn(0,
				maleTemplate);
		Vector<DataTableRow*> femaleRows = racialModsTable.getRowsByColumn(1,
				femaleTemplate);

		Reference<RacialCreationData*> rcd = new RacialCreationData();
		rcd->parseAttributeData(attributeLimitRow);

		if (!maleTemplate.isEmpty()) {
			if (maleRows.size() > 0)
				rcd->parseRacialModData(maleRows.get(0));

			racialCreationData.put(maleTemplate, rcd);
		}

		if (!femaleTemplate.isEmpty()) {
			if (femaleRows.size() > 0)
				rcd->parseRacialModData(femaleRows.get(0));

			racialCreationData.put(femaleTemplate, rcd);
		}
	}

	info(
			"Loaded " + String::valueOf(racialCreationData.size())
					+ " playable species.");
}

void PlayerCreationManager::loadProfessionDefaultsInfo() {
	TemplateManager* templateManager = TemplateManager::instance();
	IffStream* iffStream = templateManager->openIffFile(
			"creation/profession_defaults.iff");

	if (iffStream == NULL) {
		error("Could not open creation profession data.");
		return;
	}

	SkillDataForm pfdt;
	pfdt.readObject(iffStream);

	delete iffStream;

	//Load the data into useful structs and store them in a map.
	for (int i = 0; i < pfdt.getTotalPaths(); ++i) {
		String name = pfdt.getSkillNameAt(i);
		String path = pfdt.getPathBySkillName(name);
		iffStream = templateManager->openIffFile(path);

		if (iffStream == NULL)
			continue;

		Reference<ProfessionDefaultsInfo*> pdi = new ProfessionDefaultsInfo();
		pdi->readObject(iffStream);

		delete iffStream;

		professionDefaultsInfo.put(name, pdi);
		//info("Loading: " + pfdt.getSkillNameAt(i) + " Path: " + pfdt.getPathBySkillName(pfdt.getSkillNameAt(i)), true);
	}

	//Now we want to load the profession mods.
	iffStream = templateManager->openIffFile(
			"datatables/creation/profession_mods.iff");

	DataTableIff dtiff;
	dtiff.readObject(iffStream);

	delete iffStream;

	for (int i = 0; i < dtiff.getTotalRows(); ++i) {
		DataTableRow* row = dtiff.getRow(i);

		String key;
		row->getValue(0, key);

		//Check if the professionInfo for this exists.
		Reference<ProfessionDefaultsInfo*> pdi = professionDefaultsInfo.get(
				key);

		if (pdi == NULL)
			continue;

		for (int i = 1; i < 10; ++i) {
			int value = 0;
			row->getValue(i, value);
			pdi->setAttributeMod(i - 1, value);
		}
	}

	info(
			"Loaded " + String::valueOf(professionDefaultsInfo.size())
					+ " creation professions.");
}

void PlayerCreationManager::loadDefaultCharacterItems() {
	IffStream* iffStream = TemplateManager::instance()->openIffFile(
			"creation/default_pc_equipment.iff");

	if (iffStream == NULL) {
		error("Couldn't load creation default items.");
		return;
	}

	iffStream->openForm('LOEQ');

	uint32 version = iffStream->getNextFormType();
	Chunk* versionChunk = iffStream->openForm(version);

	for (int i = 0; i < versionChunk->getChunksSize(); ++i) {
		Chunk* ptmpChunk = iffStream->openForm('PTMP');

		String templateName;
		Chunk* nameChunk = iffStream->openChunk('NAME');
		nameChunk->readString(templateName);
		iffStream->closeChunk('NAME');

		SortedVector < String > items;

		for (int j = 1; j < ptmpChunk->getChunksSize(); ++j) {
			Chunk* itemChunk = iffStream->openChunk('ITEM');
			String itemTemplate;
			int unk1 = itemChunk->readInt();
			itemChunk->readString(itemTemplate);
			itemTemplate = itemTemplate.replaceFirst("shared_", "");
			items.put(itemTemplate);
			iffStream->closeChunk('ITEM');
		}

		defaultCharacterEquipment.put(templateName, items);
		iffStream->closeForm('PTMP');
	}

	iffStream->closeForm(version);
	iffStream->closeForm('LOEQ');

	delete iffStream;
}

void PlayerCreationManager::loadHairStyleInfo() {
	IffStream* iffStream = TemplateManager::instance()->openIffFile(
			"creation/default_pc_hairstyles.iff");

	if (iffStream == NULL) {
		error("Couldn't load creation hair styles.");
		return;
	}

	iffStream->openForm('HAIR');

	uint32 version = iffStream->getNextFormType();
	Chunk* versionChunk = iffStream->openForm(version);

	int totalHairStyles = 0;

	for (int i = 0; i < versionChunk->getChunksSize(); ++i) {
		Reference<HairStyleInfo*> hsi = new HairStyleInfo();
		hsi->readObject(iffStream);

		hairStyleInfo.put(hsi->getPlayerTemplate(), hsi);

		totalHairStyles += hsi->getTotalStyles();

		//info("Loaded " + String::valueOf(hsi->getTotalStyles()) + " hair styles for template " + hsi->getPlayerTemplate());
	}

	iffStream->closeForm(version);
	iffStream->closeForm('HAIR');

	delete iffStream;

	info(
			"Loaded " + String::valueOf(totalHairStyles)
					+ " total creation hair styles.");
}

void PlayerCreationManager::loadLuaConfig() {
	info("Loading configuration script.");

	Lua* lua = new Lua();
	lua->init();

	lua->runFile("scripts/managers/player_creation_manager.lua");

	startingCash = lua->getGlobalInt("startingCash");
	startingBank = lua->getGlobalInt("startingBank");
	skillPoints = lua->getGlobalInt("skillPoints");
	freeGodMode = lua->getGlobalByte("freeGodMode");

	loadLuaStartingItems(lua);

	delete lua;
	lua = NULL;
}

void PlayerCreationManager::loadLuaStartingItems(Lua* lua) {
	// Catch potential errors from loading starting items.
	try {
		// Read professions.
		Vector < String > professions;
		LuaObject professionsLuaObject = lua->getGlobalObject("professions");
		for (int professionNumber = 1;
				professionNumber <= professionsLuaObject.getTableSize();
				professionNumber++) {
			professions.add(professionsLuaObject.getStringAt(professionNumber));
		}
		professionsLuaObject.pop();

		// Read profession specific items.
		LuaObject professionSpecificItems = lua->getGlobalObject(
				"professionSpecificItems");
		for (int professionNumber = 0; professionNumber < professions.size();
				professionNumber++) {
			LuaObject professionSpecificItemList =
					professionSpecificItems.getObjectField(
							professions.get(professionNumber));
			for (int itemNumber = 1;
					itemNumber <= professionSpecificItemList.getTableSize();
					itemNumber++) {
				professionDefaultsInfo.get(professions.get(professionNumber))->getStartingItems()->add(
						professionSpecificItemList.getStringAt(itemNumber));
			}
			professionSpecificItemList.pop();
		}
		professionSpecificItems.pop();

		// Read common starting items.
		LuaObject commonStartingItemsLuaObject = lua->getGlobalObject(
				"commonStartingItems");
		for (int itemNumber = 1;
				itemNumber <= commonStartingItemsLuaObject.getTableSize();
				itemNumber++) {
			commonStartingItems.add(
					commonStartingItemsLuaObject.getStringAt(itemNumber));
		}
		commonStartingItemsLuaObject.pop();
	} catch (Exception& e) {
		error("Failed to load starting items.");
		error(e.getMessage());
	}
}

bool PlayerCreationManager::createCharacter(MessageCallback* data) {
	TemplateManager* templateManager = TemplateManager::instance();

	ClientCreateCharacterCallback* callback = cast<
			ClientCreateCharacterCallback*>(data);
	ZoneClientSession* client = data->getClient();

	if (client->getCharacterCount(zoneServer.get()->getGalaxyID()) >= 10) {
		ErrorMessage* errMsg = new ErrorMessage("Create Error", "You are limited to 10 characters per galaxy.", 0x0);
		client->sendMessage(errMsg);

		return false;
	}

	PlayerManager* playerManager = zoneServer.get()->getPlayerManager();

	SkillManager* skillManager = SkillManager::instance();

	//Get all the data and validate it.
	UnicodeString characterName;
	callback->getCharacterName(characterName);

	//TODO: Replace this at some point?
	if (!playerManager->checkPlayerName(callback))
		return false;

	String raceFile;
	callback->getRaceFile(raceFile);

	uint32 serverObjectCRC = raceFile.hashCode();

	PlayerCreatureTemplate* playerTemplate =
			dynamic_cast<PlayerCreatureTemplate*>(templateManager->getTemplate(
					serverObjectCRC));

	if (playerTemplate == NULL) {
		error("Unknown player template selected: " + raceFile);
		return false;
	}

	int raceID = playerTemplate->getRace();


	String fileName = playerTemplate->getTemplateFileName();
	String clientTemplate = templateManager->getTemplateFile(
			playerTemplate->getClientObjectCRC());

	RacialCreationData* raceData = racialCreationData.get(fileName);

	if (raceData == NULL)
		raceData = racialCreationData.get(0); //Just get the first race, since they tried to create a race that doesn't exist.

	String profession, customization, hairTemplate, hairCustomization;
	callback->getSkill(profession);

	if (profession.contains("jedi"))
		profession = "crafting_artisan";

	callback->getCustomizationString(customization);
	callback->getHairObject(hairTemplate);
	callback->getHairCustomization(hairCustomization);

	float height = callback->getHeight();
	height = MAX(MIN(height, playerTemplate->getMaxScale()),
			playerTemplate->getMinScale());

	//validate biography
	UnicodeString bio;
	callback->getBiography(bio);

	bool doTutorial = callback->getTutorialFlag();
	//bool doTutorial = false;

	ManagedReference<CreatureObject*> playerCreature =
			zoneServer.get()->createObject(
					serverObjectCRC, 2).castTo<CreatureObject*>();

	if (playerCreature == NULL) {
		error("Could not create player with template: " + raceFile);
		return false;
	}

	Locker playerLocker(playerCreature);

	playerCreature->createChildObjects();
	playerCreature->setHeight(height);
	playerCreature->setCustomObjectName(characterName, false); //TODO: Validate with Name Manager.

	client->setPlayer(playerCreature);
	playerCreature->setClient(client);

	// Set starting cash and starting bank
	playerCreature->setCashCredits(startingCash, false);
	playerCreature->setBankCredits(startingBank, false);

	ManagedReference<PlayerObject*> ghost = playerCreature->getPlayerObject();

	if (ghost != NULL) {
		//Set skillpoints before adding any skills.
		ghost->setSkillPoints(skillPoints);
		ghost->setStarterProfession(profession);
	}

	addCustomization(playerCreature, customization,
			playerTemplate->getAppearanceFilename());
	addHair(playerCreature, hairTemplate, hairCustomization);
	if (!doTutorial) {
		addProfessionStartingItems(playerCreature, profession, clientTemplate,
				false);
		addStartingItems(playerCreature, clientTemplate, false);
		addRacialMods(playerCreature, fileName,
				playerTemplate->getStartingSkills(),
				playerTemplate->getStartingItems(), false);
	} else {
		addProfessionStartingItems(playerCreature, profession, clientTemplate,
				true);
		addStartingItems(playerCreature, clientTemplate, true);
		addRacialMods(playerCreature, fileName,
				playerTemplate->getStartingSkills(),
				playerTemplate->getStartingItems(), true);
	}

	// Set starting cash and starting bank
	playerCreature->setCashCredits(startingCash, false);
	playerCreature->setBankCredits(startingBank, false);

	if (ghost != NULL) {

		ghost->setAccountID(client->getAccountID());

		if (!freeGodMode) {
			try {
				uint32 accID = client->getAccountID();

				ManagedReference<Account*> playerAccount = playerManager->getAccount(accID);

				if (playerAccount == NULL) {
					playerCreature->destroyPlayerCreatureFromDatabase(true);
					return false;
				}

				int accountPermissionLevel = playerAccount->getAdminLevel();
				String accountName = playerAccount->getUsername();

				if(accountPermissionLevel > 0 && (accountPermissionLevel == 9 || accountPermissionLevel == 10 || accountPermissionLevel == 12 || accountPermissionLevel == 15)) {
					playerManager->updatePermissionLevel(playerCreature, accountPermissionLevel);

					/*
					Reference<ShipControlDevice*> shipControlDevice = zoneServer->createObject(String("object/intangible/ship/sorosuub_space_yacht_pcd.iff").hashCode(), 1).castTo<ShipControlDevice*>();
					//ShipObject* ship = (ShipObject*) server->createObject(String("object/ship/player/player_sorosuub_space_yacht.iff").hashCode(), 1);
					Reference<ShipObject*> ship = zoneServer->createObject(String("object/ship/player/player_basic_tiefighter.iff").hashCode(), 1).castTo<ShipObject*>();

					shipControlDevice->setControlledObject(ship);

					if (!shipControlDevice->transferObject(ship, 4))
						info("Adding of ship to device failed");

					ManagedReference<SceneObject*> datapad = playerCreature->getSlottedObject("datapad");

					if (datapad != NULL) {
						if (!datapad->transferObject(shipControlDevice, -1)) {
							shipControlDevice->destroyObjectFromDatabase(true);
						}
					} else {
						shipControlDevice->destroyObjectFromDatabase(true);
						error("could not get datapad from player");
					}
					*/
				}

				if (accountPermissionLevel < 9) {
					try {
						StringBuffer query;
						//query << "SELECT UNIX_TIMESTAMP(creation_date) FROM characters c WHERE galaxy_id = " << zoneServer.get()->getGalaxyID() << " AND account_id = " << client->getAccountID() << " ORDER BY creation_date desc;";
						uint32 galaxyId = zoneServer.get()->getGalaxyID();
						uint32 accountId = client->getAccountID();
						query << "(SELECT UNIX_TIMESTAMP(c.creation_date) as t FROM characters as c WHERE c.account_id = " << accountId << " AND c.galaxy_id = " << galaxyId << " ORDER BY c.creation_date DESC) UNION (SELECT UNIX_TIMESTAMP(d.creation_date) FROM deleted_characters as d WHERE d.account_id = " << accountId << " AND d.galaxy_id = " << galaxyId << " ORDER BY d.creation_date DESC) ORDER BY t DESC LIMIT 1";

						Reference<ResultSet*> res = ServerDatabase::instance()->executeQuery(query);

						if (res != NULL && res->next()) {
							uint32 sec = res->getUnsignedInt(0);

							Time timeVal(sec);

							if (timeVal.miliDifference() < 86400000) {
								ErrorMessage* errMsg = new ErrorMessage("Create Error", "You are only permitted to create one character every 24 hours. Repeat attempts prior to 24 hours elapsing will reset the timer.", 0x0);
								client->sendMessage(errMsg);

								playerCreature->destroyPlayerCreatureFromDatabase(true);
								return false;
							}
							//timeVal.se
						}
					} catch (DatabaseException& e) {
						error(e.getMessage());
					}

					Locker locker(&charCountMutex);

					if (lastCreatedCharacter.containsKey(accID)) {
						Time lastCreatedTime = lastCreatedCharacter.get(accID);

						if (lastCreatedTime.miliDifference() < 86400000) {
							ErrorMessage* errMsg = new ErrorMessage("Create Error", "You are only permitted to create one character every 24 hours. Repeat attempts prior to 24 hours elapsing will reset the timer.", 0x0);
							client->sendMessage(errMsg);

							playerCreature->destroyPlayerCreatureFromDatabase(true);
							return false;
						} else {
							lastCreatedTime.updateToCurrentTime();

							lastCreatedCharacter.put(accID, lastCreatedTime);
						}
					} else {
						lastCreatedCharacter.put(accID, Time());
					}
				}

			} catch (Exception& e) {
				error(e.getMessage());
			}
		} else {
			playerManager->updatePermissionLevel(playerCreature, PermissionLevelList::instance()->getLevelNumber("admin"));
		}

		if (doTutorial)
			playerManager->createTutorialBuilding(playerCreature);
		else
			playerManager->createSkippedTutorialBuilding(playerCreature);

		ValidatedPosition* lastValidatedPosition =
				ghost->getLastValidatedPosition();
		lastValidatedPosition->update(playerCreature);

		ghost->setBiography(bio);
		ghost->setRaceID(raceID);

		ghost->setLanguageID(playerTemplate->getDefaultLanguage());
	}

	ClientCreateCharacterSuccess* msg = new ClientCreateCharacterSuccess(
			playerCreature->getObjectID());
	playerCreature->sendMessage(msg);

	ChatManager* chatManager = zoneServer.get()->getChatManager();
	chatManager->addPlayer(playerCreature);

	String firstName = playerCreature->getFirstName();
	String lastName = playerCreature->getLastName();

	try {
		StringBuffer query;
		query
				<< "INSERT INTO `characters_dirty` (`character_oid`, `account_id`, `galaxy_id`, `firstname`, `surname`, `race`, `gender`, `template`)"
				<< " VALUES (" << playerCreature->getObjectID() << ","
				<< client->getAccountID() << "," << zoneServer.get()->getGalaxyID()
				<< "," << "'" << firstName.escapeString() << "','"
				<< lastName.escapeString() << "'," << raceID << "," << 0 << ",'"
				<< raceFile.escapeString() << "')";

		ServerDatabase::instance()->executeStatement(query);
	} catch (DatabaseException& e) {
		error(e.getMessage());
	}

	playerManager->addPlayer(playerCreature);

	// Copy claimed veteran rewards from player's alt character
	uint32 accID = client->getAccountID();
	ManagedReference<Account*> playerAccount = playerManager->getAccount(accID);
	if (playerAccount != NULL && ghost != NULL) {

		// Find the first alt character
		ManagedReference<CreatureObject*> altPlayer = NULL;
		CharacterList* characters = playerAccount->getCharacterList();
		for(int i = 0; i < characters->size(); ++i) {
			CharacterListEntry* entry = &characters->get(i);
			if(entry->getGalaxyID() == zoneServer.get()->getGalaxyID() &&
		       entry->getFirstName() != playerCreature->getFirstName() ) {

				altPlayer = playerManager->getPlayer(entry->getFirstName());
				if( altPlayer != NULL ){
					break;
				}
			}
		}

		// Record the rewards if alt player was found
		if( altPlayer != NULL && altPlayer->getPlayerObject() != NULL){

			Locker alocker( altPlayer );
			for( int i = 0; i < playerManager->getNumVeteranRewardMilestones(); i++ ){
				int milestone = playerManager->getVeteranRewardMilestone(i);
				String claimedReward = altPlayer->getPlayerObject()->getChosenVeteranReward(milestone);
				if( !claimedReward.isEmpty() ){
					ghost->addChosenVeteranReward(milestone,claimedReward);
				}
			}
		}
	}

	client->addCharacter(playerCreature->getObjectID(), zoneServer.get()->getGalaxyID());

	JediManager::instance()->onPlayerCreated(playerCreature);

	ManagedReference<SuiMessageBox*> box = new SuiMessageBox(playerCreature, SuiWindowType::NONE);
	box->setPromptTitle("PLEASE NOTE");
	box->setPromptText("You are limited to creating one character every 24 hours. Attempting to create another character or deleting your character before the 24 hour timer expires will reset the timer.");

	ghost->addSuiBox(box);
	playerCreature->sendMessage(box->generateMessage());

	return true;
}

int PlayerCreationManager::getMaximumAttributeLimit(const String& race,
		int attributeNumber) {
	String maleRace = race + "_male";

	if (attributeNumber < 0 || attributeNumber > 8) {
		attributeNumber = 0;
	}

	Reference<RacialCreationData*> racialData = racialCreationData.get(
			maleRace);

	if (racialData != NULL) {
		return racialData->getAttributeMax(attributeNumber);
	} else {
		return racialCreationData.get("human_male")->getAttributeMax(
				attributeNumber);
	}
}

int PlayerCreationManager::getMinimumAttributeLimit(const String& race,
		int attributeNumber) {
	String maleRace = race + "_male";

	if (attributeNumber < 0 || attributeNumber > 8) {
		attributeNumber = 0;
	}

	Reference<RacialCreationData*> racialData = racialCreationData.get(
			maleRace);

	if (racialData != NULL) {
		return racialData->getAttributeMin(attributeNumber);
	} else {
		return racialCreationData.get("human_male")->getAttributeMin(
				attributeNumber);
	}
}

int PlayerCreationManager::getTotalAttributeLimit(const String& race) {
	String maleRace = race + "_male";

	Reference<RacialCreationData*> racialData = racialCreationData.get(
			maleRace);

	if (racialData != NULL) {
		return racialData->getAttributeTotal();
	} else {
		return racialCreationData.get("human_male")->getAttributeTotal();
	}
}

bool PlayerCreationManager::validateCharacterName(const String& characterName) {
	return true;
}

void PlayerCreationManager::addStartingItems(CreatureObject* creature,
		const String& clientTemplate, bool equipmentOnly) {
	SortedVector < String > *items = NULL;

	if (!defaultCharacterEquipment.contains(clientTemplate))
		items = &defaultCharacterEquipment.get(0);
	else
		items = &defaultCharacterEquipment.get(clientTemplate);

	for (int i = 0; i < items->size(); ++i) {
		String itemTemplate = items->get(i);

		//instance()->info("Add Starting Items: " + itemTemplate, true);

		ManagedReference<SceneObject*> item = zoneServer->createObject(
				itemTemplate.hashCode(), 1);

		if (item != NULL) {
			String error;
			if (creature->canAddObject(item, 4, error) == 0) {
				creature->transferObject(item, 4, false);
			} else {
				item->destroyObjectFromDatabase(true);
			}
		}

	}

	// Get inventory.
	if (!equipmentOnly) {
		SceneObject* inventory = creature->getSlottedObject("inventory");
		if (inventory == NULL) {
			return;
		}

		//Add common starting items.
		for (int itemNumber = 0; itemNumber < commonStartingItems.size();
				itemNumber++) {
			ManagedReference<SceneObject*> item = zoneServer->createObject(
					commonStartingItems.get(itemNumber).hashCode(), 1);
			if (item != NULL) {
				if (!inventory->transferObject(item, -1, false)) {
					item->destroyObjectFromDatabase(true);
				}
			}
		}
	}
}

void PlayerCreationManager::addProfessionStartingItems(CreatureObject* creature,
		const String& profession, const String& clientTemplate,
		bool equipmentOnly) {
	ProfessionDefaultsInfo* professionData = professionDefaultsInfo.get(
			profession);

	if (professionData == NULL)
		professionData = professionDefaultsInfo.get(0);

	Reference<Skill*> startingSkill = professionData->getSkill();
	//Reference<Skill*> startingSkill = SkillManager::instance()->getSkill("crafting_artisan_novice");

	//Starting skill.
	SkillManager::instance()->awardSkill(startingSkill->getSkillName(),
			creature, false, true, true);

	//Set the hams.
	for (int i = 0; i < 9; ++i) {
		int mod = professionData->getAttributeMod(i);
		creature->setBaseHAM(i, mod, false);
		creature->setHAM(i, mod, false);
		creature->setMaxHAM(i, mod, false);
	}

	SortedVector < String > *itemTemplates = professionData->getProfessionItems(
			clientTemplate);

	if (itemTemplates == NULL)
		return;

	for (int i = 0; i < itemTemplates->size(); ++i) {
		String itemTemplate = itemTemplates->get(i);

		//instance()->info("Add Profession Starting Items: " + itemTemplate, true);

		ManagedReference<SceneObject*> item;

		try {
			item = zoneServer->createObject(itemTemplate.hashCode(), 1);
		} catch (Exception& e) {
		}

		if (item != NULL) {
			String error;
			if (creature->canAddObject(item, 4, error) == 0) {
				creature->transferObject(item, 4, false);
			} else {
				item->destroyObjectFromDatabase(true);
			}
		} else {
			error(
					"could not create item in PlayerCreationManager::addProfessionStartingItems: "
							+ itemTemplate);
		}
	}

	// Get inventory.
	if (!equipmentOnly) {
		SceneObject* inventory = creature->getSlottedObject("inventory");
		if (inventory == NULL) {
			return;
		}

		//Add profession specific items.
		for (int itemNumber = 0;
				itemNumber < professionData->getStartingItems()->size();
				itemNumber++) {
			String itemTemplate = professionData->getStartingItems()->get(
					itemNumber);

			ManagedReference<SceneObject*> item = zoneServer->createObject(
					itemTemplate.hashCode(), 1);

			if (item != NULL) {
				if (!inventory->transferObject(item, -1, false)) {
					item->destroyObjectFromDatabase(true);
				}
			} else if (item == NULL) {
				error("could not create profession item " + itemTemplate);
			}
		}
	}
}

void PlayerCreationManager::addHair(CreatureObject* creature,
		const String& hairTemplate, const String& hairCustomization) {
	if (hairTemplate.isEmpty())
		return;

	HairStyleInfo* hairInfo = hairStyleInfo.get(hairTemplate);

	if (hairInfo == NULL)
		hairInfo = hairStyleInfo.get(0);

	HairAssetData* hairAssetData =
			CustomizationIdManager::instance()->getHairAssetData(hairTemplate);

	if (hairAssetData == NULL) {
		error("no hair asset data detected for " + hairTemplate);
		return;
	}

	if (hairAssetData->getServerPlayerTemplate()
			!= creature->getObjectTemplate()->getFullTemplateString()) {
		error(
				"hair " + hairTemplate
						+ " is not compatible with this creature player "
						+ creature->getObjectTemplate()->getFullTemplateString());
		return;
	}

	if (!hairAssetData->isAvailableAtCreation()) {
		error("hair " + hairTemplate + " not available at creation");
		return;
	}

	ManagedReference<SceneObject*> hair = zoneServer->createObject(
			hairTemplate.hashCode(), 1);

	//TODO: Validate hairCustomization
	if (hair == NULL) {
		return;
	}

	if (!hair->isTangibleObject()) {
		hair->destroyObjectFromDatabase(true);
		return;
	}

	TangibleObject* tanoHair = cast<TangibleObject*>(hair.get());
	tanoHair->setContainerDenyPermission("owner",
			ContainerPermissions::MOVECONTAINER);
	tanoHair->setContainerDefaultDenyPermission(
			ContainerPermissions::MOVECONTAINER);

	String appearanceFilename =
			tanoHair->getObjectTemplate()->getAppearanceFilename();

	CustomizationVariables data;

	data.parseFromClientString(hairCustomization);

	if (ImageDesignManager::validateCustomizationString(&data,
			appearanceFilename, -1))
		tanoHair->setCustomizationString(hairCustomization);

	creature->transferObject(tanoHair, 4);
}

void PlayerCreationManager::addCustomization(CreatureObject* creature,
		const String& customizationString, const String& appearanceFilename) {
	//TODO: Validate customizationString
	CustomizationVariables data;

	data.parseFromClientString(customizationString);

	if (ImageDesignManager::validateCustomizationString(&data,
			appearanceFilename, -1))
		creature->setCustomizationString(customizationString);
}

void PlayerCreationManager::addStartingItemsInto(CreatureObject* creature,
		SceneObject* container) {

	if (creature == NULL || container == NULL
			|| !creature->isPlayerCreature()) {
		instance()->info("addStartingItemsInto: NULL or not PlayerCreature");
		return;
	}

	PlayerCreatureTemplate* playerTemplate =
			dynamic_cast<PlayerCreatureTemplate*>(creature->getObjectTemplate());

	if (playerTemplate == NULL) {
		instance()->info("addStartingItemsInto: playerTemplate NULL");
		return;
	}

	//Add common starting items.
	for (int itemNumber = 0; itemNumber < commonStartingItems.size();
			itemNumber++) {
		ManagedReference<SceneObject*> item = zoneServer->createObject(
				commonStartingItems.get(itemNumber).hashCode(), 1);
		if (item != NULL && container != NULL && !item->isWeaponObject()) {
			if (!container->transferObject(item, -1, true)) {
				item->destroyObjectFromDatabase(true);
			}
		} else if (item != NULL) {
			item->destroyObjectFromDatabase(true);
		}
	}

	//Add profession specific items.
	PlayerObject* player = creature->getPlayerObject();
	if (player == NULL) {
		instance()->info("addStartingItemsInto: playerObject NULL");
		return;
	}

	String profession = player->getStarterProfession();

	ProfessionDefaultsInfo* professionData = professionDefaultsInfo.get(
			profession);

	if (professionData == NULL)
		professionData = professionDefaultsInfo.get(0);

	for (int itemNumber = 0;
			itemNumber < professionData->getStartingItems()->size();
			itemNumber++) {
		ManagedReference<SceneObject*> item = zoneServer->createObject(
				professionData->getStartingItems()->get(itemNumber).hashCode(),
				1);
		if (item != NULL && container != NULL && !item->isWeaponObject()) {
			if (!container->transferObject(item, -1, true)) {
				item->destroyObjectFromDatabase(true);
			}
		} else if (item != NULL) {
			item->destroyObjectFromDatabase(true);
		}
	}

	//Add race specific items.
	Vector < String > *startingItems = playerTemplate->getStartingItems();

	if (startingItems != NULL) {
		for (int i = 0; i < startingItems->size(); ++i) {
			ManagedReference<SceneObject*> item = zoneServer->createObject(
					startingItems->get(i).hashCode(), 1);

			if (item != NULL && container != NULL && !item->isWeaponObject()) {
				if (!container->transferObject(item, -1, true)) {
					item->destroyObjectFromDatabase(true);
				}
			} else if (item != NULL) {
				item->destroyObjectFromDatabase(true);
			}
		}

	}
}

void PlayerCreationManager::addStartingWeaponsInto(CreatureObject* creature,
		SceneObject* container) {
	if (creature == NULL || container == NULL || !creature->isPlayerCreature())
		return;

//	container = creature->getSlottedObject("inventory");

	PlayerCreatureTemplate* playerTemplate =
			dynamic_cast<PlayerCreatureTemplate*>(creature->getObjectTemplate());

	if (playerTemplate == NULL) {
		instance()->info("addStartingWeaponsInto: playerTemplate NULL");
		return;
	}

	PlayerObject* player = creature->getPlayerObject();
	if (player == NULL) {
		instance()->info("addStartingWeaponsInto: playerObject NULL");
		return;
	}

	String profession = player->getStarterProfession();

	ProfessionDefaultsInfo* professionData = professionDefaultsInfo.get(
			profession);

	if (professionData == NULL)
		professionData = professionDefaultsInfo.get(0);


	//Add common starting items.
	for (int itemNumber = 0; itemNumber < commonStartingItems.size();
			itemNumber++) {
		ManagedReference<SceneObject*> item = zoneServer->createObject(
				commonStartingItems.get(itemNumber).hashCode(), 1);
		if (item != NULL && container != NULL && item->isWeaponObject()) {
			if (container->transferObject(item, -1, true)) {
				item->sendTo(creature, true);
			} else {
				item->destroyObjectFromDatabase(true);
			}
		} else if (item != NULL) {
			item->destroyObjectFromDatabase(true);
		}
	}


	//Add profession specific items.
	for (int itemNumber = 0;
			itemNumber < professionData->getStartingItems()->size();
			itemNumber++) {
		ManagedReference<SceneObject*> item = zoneServer->createObject(
				professionData->getStartingItems()->get(itemNumber).hashCode(),
				1);
		if (item != NULL && container != NULL && item->isWeaponObject()) {
			if (container->transferObject(item, -1, true)) {
				item->sendTo(creature, true);
			} else {
				item->destroyObjectFromDatabase(true);
			}
		} else if (item != NULL) {
			item->destroyObjectFromDatabase(true);
		}
	}


	//Add race specific items.
	Vector < String > *startingItems = playerTemplate->getStartingItems();

	if (startingItems != NULL) {
		for (int i = 0; i < startingItems->size(); ++i) {
			ManagedReference<SceneObject*> item = zoneServer->createObject(
					startingItems->get(i).hashCode(), 1);

			if (item != NULL && container != NULL && item->isWeaponObject()) {
				if (container->transferObject(item, -1, true)) {
					item->sendTo(creature, true);
				} else {
					item->destroyObjectFromDatabase(true);
				}
			} else if (item != NULL) {
				item->destroyObjectFromDatabase(true);
			}
		}
	}
}

void PlayerCreationManager::addRacialMods(CreatureObject* creature,
		const String& race, Vector<String>* startingSkills,
		Vector<String>* startingItems, bool equipmentOnly) {
	Reference<RacialCreationData*> racialData = racialCreationData.get(race);

	if (racialData == NULL)
		racialData = racialCreationData.get(0);

	for (int i = 0; i < 9; ++i) {
		int mod = racialData->getAttributeMod(i) + creature->getBaseHAM(i);
		creature->setBaseHAM(i, mod, false);
		creature->setHAM(i, mod, false);
		creature->setMaxHAM(i, mod, false);
	}

	if (startingSkills != NULL) {
		for (int i = 0; i < startingSkills->size(); ++i) {
			SkillManager::instance()->awardSkill(startingSkills->get(i),
					creature, false, true, true);
		}
	}

	// Get inventory.
	if (!equipmentOnly) {
		SceneObject* inventory = creature->getSlottedObject("inventory");
		if (inventory == NULL) {
			return;
		}

		if (startingItems != NULL) {
			for (int i = 0; i < startingItems->size(); ++i) {
				ManagedReference<SceneObject*> item = zoneServer->createObject(
						startingItems->get(i).hashCode(), 1);

				if (item != NULL) {
					if (!inventory->transferObject(item, -1, false)) {
						item->destroyObjectFromDatabase(true);
					}
				}

			}
		}
	}
}
