/*
				Copyright <SWGEmu>
		See file COPYING for copying conditions.
*/

#include "server/db/ServerDatabase.h"
#include "PlayerCreationManager.h"
#include "server/zone/managers/player/PlayerManager.h"
#include "server/login/packets/ErrorMessage.h"
#include "server/chat/ChatManager.h"
#include "server/chat/room/ChatRoom.h"
#include "server/login/account/Account.h"
#include "server/zone/objects/player/sui/messagebox/SuiMessageBox.h"
#include "server/zone/objects/player/PlayerObject.h"
#include "server/zone/packets/charcreation/ClientCreateCharacterCallback.h"
#include "server/zone/packets/charcreation/ClientCreateCharacterSuccess.h"
#include "templates/manager/TemplateManager.h"
#include "templates/datatables/DataTableIff.h"
#include "templates/datatables/DataTableRow.h"
#include "templates/creation/SkillDataForm.h"
#include "templates/creature/PlayerCreatureTemplate.h"
#include "server/ServerCore.h"
#include "templates/customization/CustomizationIdManager.h"
#include "server/zone/managers/skill/imagedesign/ImageDesignManager.h"
#include "server/zone/managers/jedi/JediManager.h"
#include "server/zone/objects/transaction/TransactionLog.h"
#include "server/zone/managers/player/creation/SendJtlRecruitment.h"

PlayerCreationManager::PlayerCreationManager() : Logger("PlayerCreationManager") {
	setLogging(false);
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

	if (iffStream == nullptr) {
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

		auto maleRows = racialModsTable.getRowsByColumn(0,
				maleTemplate);
		auto femaleRows = racialModsTable.getRowsByColumn(1,
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

	info() << "Loaded " << racialCreationData.size() << " playable species.";
}

void PlayerCreationManager::loadProfessionDefaultsInfo() {
	TemplateManager* templateManager = TemplateManager::instance();
	IffStream* iffStream = templateManager->openIffFile("creation/profession_defaults.iff");

	if (iffStream == nullptr) {
		error("Could not open creation profession data.");
		return;
	}

	SkillDataForm pfdt;
	pfdt.readObject(iffStream);

	delete iffStream;

	// Load the data into useful structs and store them in a map.
	for (int i = 0; i < pfdt.getTotalPaths(); ++i) {
		String name = pfdt.getSkillNameAt(i);
		String path = pfdt.getPathBySkillName(name);
		iffStream = templateManager->openIffFile(path);

		if (iffStream == nullptr)
			continue;

		Reference<ProfessionDefaultsInfo*> pdi = new ProfessionDefaultsInfo();
		pdi->readObject(iffStream);

		delete iffStream;

		professionDefaultsInfo.put(name, pdi);
		debug() << "Loading: " << pfdt.getSkillNameAt(i) << " Path: " << pfdt.getPathBySkillName(pfdt.getSkillNameAt(i));
	}

	// Now we want to load the profession mods.
	iffStream = templateManager->openIffFile("datatables/creation/profession_mods.iff");

	if (iffStream == nullptr) {
		error("Could not open creation profession mods data table");

		return;
	}

	DataTableIff dtiff;
	dtiff.readObject(iffStream);

	delete iffStream;

	for (int i = 0; i < dtiff.getTotalRows(); ++i) {
		DataTableRow* row = dtiff.getRow(i);

		String key;
		row->getValue(0, key);

		// Check if the professionInfo for this exists.
		Reference<ProfessionDefaultsInfo*> pdi = professionDefaultsInfo.get(key);

		if (pdi == nullptr)
			continue;

		for (int i = 1; i < 10; ++i) {
			int value = 0;
			row->getValue(i, value);
			pdi->setAttributeMod(i - 1, value);
		}
	}

	info() << "Loaded " << professionDefaultsInfo.size() << " creation professions.";
}

void PlayerCreationManager::loadDefaultCharacterItems() {
	IffStream* iffStream = TemplateManager::instance()->openIffFile(
			"creation/default_pc_equipment.iff");

	if (iffStream == nullptr) {
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
	IffStream* iffStream = TemplateManager::instance()->openIffFile("creation/default_pc_hairstyles.iff");

	if (iffStream == nullptr) {
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

		debug() << "Loaded " << hsi->getTotalStyles() << " hair styles for template " << hsi->getPlayerTemplate();
	}

	iffStream->closeForm(version);
	iffStream->closeForm('HAIR');

	delete iffStream;

	info() << "Loaded " << totalHairStyles << " total creation hair styles.";
}

void PlayerCreationManager::loadLuaConfig() {
	debug("Loading configuration script.");

	Lua* lua = new Lua();
	lua->init();

	lua->runFile("scripts/managers/player_creation_manager.lua");

	startingCash = lua->getGlobalInt("startingCash");
	startingBank = lua->getGlobalInt("startingBank");
	skillPoints = lua->getGlobalInt("skillPoints");
	freeGodMode = lua->getGlobalByte("freeGodMode");

	loadLuaStartingItems(lua);

	delete lua;
	lua = nullptr;
}

void PlayerCreationManager::loadLuaStartingItems(Lua* lua) {
	// Catch potential errors from loading starting items.
	try {
		// Read professions.
		Vector < String > professions;
		LuaObject professionsLuaObject = lua->getGlobalObject("professions");

		for (int professionNumber = 1; professionNumber <= professionsLuaObject.getTableSize(); professionNumber++) {
			professions.add(professionsLuaObject.getStringAt(professionNumber));
		}

		professionsLuaObject.pop();

		// Read profession specific items.
		LuaObject professionSpecificItems = lua->getGlobalObject("professionSpecificItems");
		for (int professionNumber = 0; professionNumber < professions.size(); professionNumber++) {
			LuaObject professionSpecificItemList = professionSpecificItems.getObjectField(professions.get(professionNumber));

			for (int itemNumber = 1; itemNumber <= professionSpecificItemList.getTableSize(); itemNumber++) {
				auto& val = professionDefaultsInfo.get(professions.get(professionNumber));
				auto itemObj = professionSpecificItemList.getStringAt(itemNumber);
				val->getStartingItems()->add(itemObj);
			}
			professionSpecificItemList.pop();
		}
		professionSpecificItems.pop();

		// Read common starting items.
		LuaObject commonStartingItemsLuaObject = lua->getGlobalObject("commonStartingItems");
		for (int itemNumber = 1; itemNumber <= commonStartingItemsLuaObject.getTableSize(); itemNumber++) {
			commonStartingItems.add(commonStartingItemsLuaObject.getStringAt(itemNumber));
		}
		commonStartingItemsLuaObject.pop();
	} catch (Exception& e) {
		error("Failed to load starting items.");
		error(e.getMessage());
	}
}

bool PlayerCreationManager::createCharacter(ClientCreateCharacterCallback* callback) const {
	TemplateManager* templateManager = TemplateManager::instance();

	auto client = callback->getClient();
	auto maxchars = ConfigManager::instance()->getInt("Core3.PlayerCreationManager.MaxCharactersPerGalaxy", 10);

	if (client->getCharacterCount(zoneServer.get()->getGalaxyID()) >= maxchars) {
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

	PlayerCreatureTemplate* playerTemplate = dynamic_cast<PlayerCreatureTemplate*>(templateManager->getTemplate(serverObjectCRC));

	if (playerTemplate == nullptr) {
		error("Unknown player template selected: " + raceFile);
		return false;
	}

	String fileName = playerTemplate->getTemplateFileName();
	String clientTemplate = templateManager->getTemplateFile(playerTemplate->getClientObjectCRC());

	RacialCreationData* raceData = racialCreationData.get(fileName);

	if (raceData == nullptr)
		raceData = racialCreationData.get(0); //Just get the first race, since they tried to create a race that doesn't exist.

	String profession, customization, hairTemplate, hairCustomization;
	callback->getSkill(profession);

	if (profession.contains("jedi"))
		profession = "crafting_artisan";

	callback->getCustomizationString(customization);
	callback->getHairObject(hairTemplate);
	callback->getHairCustomization(hairCustomization);

	float height = callback->getHeight();
	height = Math::max(Math::min(height, playerTemplate->getMaxScale()), playerTemplate->getMinScale());

	//validate biography
	UnicodeString bio;
	callback->getBiography(bio);

	bool doTutorial = ConfigManager::instance()->getBool("Core3.PlayerCreationManager.EnableTutorial", callback->getTutorialFlag());

	ManagedReference<CreatureObject*> playerCreature = zoneServer.get()->createObject(serverObjectCRC, 2).castTo<CreatureObject*>();

	if (playerCreature == nullptr) {
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
	playerCreature->clearCashCredits(false);
	playerCreature->clearBankCredits(false);

	{
		TransactionLog trx(TrxCode::CHARACTERCREATION, playerCreature, startingCash, true);
		playerCreature->addCashCredits(startingCash, false);
	}
	{
		TransactionLog trx(TrxCode::CHARACTERCREATION, playerCreature, startingBank, false);
		playerCreature->addBankCredits(startingBank, false);
	}

	ManagedReference<PlayerObject*> ghost = playerCreature->getPlayerObject();

	if (ghost != nullptr) {
		//Set skillpoints before adding any skills.
		ghost->setSkillPoints(skillPoints);
		ghost->setStarterProfession(profession);
	}

	addCustomization(playerCreature, customization, playerTemplate->getAppearanceFilename());
	addHair(playerCreature, hairTemplate, hairCustomization);

	if (!doTutorial) {
		addProfessionStartingItems(playerCreature, profession, clientTemplate, false);
		addStartingItems(playerCreature, clientTemplate, false);
		addRacialMods(playerCreature, fileName, &playerTemplate->getStartingSkills(), &playerTemplate->getStartingItems(), false);
	} else {
		addProfessionStartingItems(playerCreature, profession, clientTemplate, true);
		addStartingItems(playerCreature, clientTemplate, true);
		addRacialMods(playerCreature, fileName, &playerTemplate->getStartingSkills(), &playerTemplate->getStartingItems(), true);
	}

	if (ghost != nullptr) {
		int accID = client->getAccountID();
		ghost->setAccountID(accID);
		ghost->initializeAccount();

		if (!freeGodMode) {
			try {
				ManagedReference<Account*> playerAccount = ghost->getAccount();

				if (playerAccount == nullptr) {
					playerCreature->destroyPlayerCreatureFromDatabase(true);
					return false;
				}

				int accountPermissionLevel = playerAccount->getAdminLevel();
				String accountName = playerAccount->getUsername();

				if (accountPermissionLevel > 0 && (accountPermissionLevel == 9 || accountPermissionLevel == 10 || accountPermissionLevel == 12 || accountPermissionLevel == 15)) {
					playerManager->updatePermissionLevel(playerCreature, accountPermissionLevel);
				}

				if (accountPermissionLevel < 9) {
					try {
						StringBuffer query;
						uint32 galaxyId = zoneServer.get()->getGalaxyID();
						uint32 accountId = client->getAccountID();
						query << "(SELECT UNIX_TIMESTAMP(c.creation_date) as t FROM characters as c WHERE c.account_id = " << accountId << " AND c.galaxy_id = " << galaxyId << " ORDER BY c.creation_date DESC) UNION (SELECT UNIX_TIMESTAMP(d.creation_date) FROM deleted_characters as d WHERE d.account_id = " << accountId << " AND d.galaxy_id = " << galaxyId << " ORDER BY d.creation_date DESC) ORDER BY t DESC LIMIT 1";

						UniqueReference<ResultSet*> res(ServerDatabase::instance()->executeQuery(query));

						if (res != nullptr && res->next()) {
							uint32 sec = res->getUnsignedInt(0);

							Time timeVal(sec);

							if (timeVal.miliDifference() < 3600000) {
								ErrorMessage* errMsg = new ErrorMessage("Create Error", "You are only permitted to create one character per hour. Repeat attempts prior to 1 hour elapsing will reset the timer.", 0x0);
								client->sendMessage(errMsg);

								playerCreature->destroyPlayerCreatureFromDatabase(true);
								return false;
							}
						}
					} catch (const DatabaseException& e) {
						error(e.getMessage());
					}

					Locker locker(&charCountMutex);

					if (lastCreatedCharacter.containsKey(accID)) {
						Time lastCreatedTime = lastCreatedCharacter.get(accID);

						if (lastCreatedTime.miliDifference() < 3600000) {
							ErrorMessage* errMsg = new ErrorMessage("Create Error", "You are only permitted to create one character per hour. Repeat attempts prior to 1 hour elapsing will reset the timer.", 0x0);
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
		ghost->setLanguageID(playerTemplate->getDefaultLanguage());

		Time now;
		ghost->setBirthDate(now.getTime());
	}

	ClientCreateCharacterSuccess* msg = new ClientCreateCharacterSuccess(
			playerCreature->getObjectID());
	playerCreature->sendMessage(msg);

	ChatManager* chatManager = zoneServer.get()->getChatManager();
	chatManager->addPlayer(playerCreature);

	String firstName = playerCreature->getFirstName();
	String lastName = playerCreature->getLastName();
	int raceID = playerTemplate->getRace();

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
	} catch (const DatabaseException& e) {
		error(e.getMessage());
	}

	playerManager->addPlayer(playerCreature);

	client->addCharacter(playerCreature->getObjectID(), zoneServer.get()->getGalaxyID());

	JediManager::instance()->onPlayerCreated(playerCreature);

	// Welcome Mail
	chatManager->sendMail("system", "@newbie_tutorial/newbie_mail:welcome_subject", "@newbie_tutorial/newbie_mail:welcome_body", playerCreature->getFirstName());

	// Schedule Task to send out JTL Recruitment Mail
	SendJtlRecruitment* jtlMailTask = new SendJtlRecruitment(playerCreature);

	if (jtlMailTask != nullptr) {
		jtlMailTask->schedule(10000);
	}

	//Join auction chat room
	ghost->addChatRoom(chatManager->getAuctionRoom()->getRoomID());

	ManagedReference<SuiMessageBox*> box = new SuiMessageBox(playerCreature, SuiWindowType::NONE);
	box->setPromptTitle("PLEASE NOTE");
	box->setPromptText("You are limited to creating one character per hour. Attempting to create another character or deleting your character before the 1 hour timer expires will reset the timer.");

	ghost->addSuiBox(box);
	playerCreature->sendMessage(box->generateMessage());

	return true;
}

int PlayerCreationManager::getMaximumAttributeLimit(const String& race,
		int attributeNumber) const {
	String maleRace = race + "_male";

	if (attributeNumber < 0 || attributeNumber > 8) {
		attributeNumber = 0;
	}

	Reference<RacialCreationData*> racialData = racialCreationData.get(
			maleRace);

	if (racialData != nullptr) {
		return racialData->getAttributeMax(attributeNumber);
	} else {
		return racialCreationData.get("human_male")->getAttributeMax(
				attributeNumber);
	}
}

int PlayerCreationManager::getMinimumAttributeLimit(const String& race,
		int attributeNumber) const {
	String maleRace = race + "_male";

	if (attributeNumber < 0 || attributeNumber > 8) {
		attributeNumber = 0;
	}

	Reference<RacialCreationData*> racialData = racialCreationData.get(
			maleRace);

	if (racialData != nullptr) {
		return racialData->getAttributeMin(attributeNumber);
	} else {
		return racialCreationData.get("human_male")->getAttributeMin(
				attributeNumber);
	}
}

int PlayerCreationManager::getTotalAttributeLimit(const String& race) const {
	String maleRace = race + "_male";

	Reference<RacialCreationData*> racialData = racialCreationData.get(
			maleRace);

	if (racialData != nullptr) {
		return racialData->getAttributeTotal();
	} else {
		return racialCreationData.get("human_male")->getAttributeTotal();
	}
}

bool PlayerCreationManager::validateCharacterName(const String& characterName) const {
	return true;
}

void PlayerCreationManager::addStartingItems(CreatureObject* creature,
		const String& clientTemplate, bool equipmentOnly) const {
	const SortedVector < String >* items = nullptr;

	if (!defaultCharacterEquipment.contains(clientTemplate))
		items = &defaultCharacterEquipment.get(0);
	else
		items = &defaultCharacterEquipment.get(clientTemplate);

	for (int i = 0; i < items->size(); ++i) {
		String itemTemplate = items->get(i);

		//instance()->info("Add Starting Items: " + itemTemplate, true);

		ManagedReference<SceneObject*> item = zoneServer->createObject(
				itemTemplate.hashCode(), 1);

		if (item != nullptr) {
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
		if (inventory == nullptr) {
			return;
		}

		//Add common starting items.
		for (int itemNumber = 0; itemNumber < commonStartingItems.size();
				itemNumber++) {
			ManagedReference<SceneObject*> item = zoneServer->createObject(
					commonStartingItems.get(itemNumber).hashCode(), 1);
			if (item != nullptr) {
				if (!inventory->transferObject(item, -1, false)) {
					item->destroyObjectFromDatabase(true);
				}
			}
		}
	}
}

void PlayerCreationManager::addProfessionStartingItems(CreatureObject* creature,
		const String& profession, const String& clientTemplate,
		bool equipmentOnly) const {
	const ProfessionDefaultsInfo* professionData = professionDefaultsInfo.get(
			profession);

	if (professionData == nullptr)
		professionData = professionDefaultsInfo.get(0);

	auto startingSkill = professionData->getSkill();
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

	auto itemTemplates = professionData->getProfessionItems(
			clientTemplate);

	if (itemTemplates == nullptr)
		return;

	for (int i = 0; i < itemTemplates->size(); ++i) {
		String itemTemplate = itemTemplates->get(i);

		//instance()->info("Add Profession Starting Items: " + itemTemplate, true);

		ManagedReference<SceneObject*> item;

		try {
			item = zoneServer->createObject(itemTemplate.hashCode(), 1);
		} catch (Exception& e) {
		}

		if (item != nullptr) {
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
		if (inventory == nullptr) {
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

			if (item != nullptr) {
				if (!inventory->transferObject(item, -1, false)) {
					item->destroyObjectFromDatabase(true);
				}
			} else if (item == nullptr) {
				error("could not create profession item " + itemTemplate);
			}
		}
	}
}

void PlayerCreationManager::addHair(CreatureObject* creature,
		const String& hairTemplate, const String& hairCustomization) const {
	if (hairTemplate.isEmpty())
		return;

	HairStyleInfo* hairInfo = hairStyleInfo.get(hairTemplate);

	if (hairInfo == nullptr)
		hairInfo = hairStyleInfo.get(0);

	HairAssetData* hairAssetData =
			CustomizationIdManager::instance()->getHairAssetData(hairTemplate);

	if (hairAssetData == nullptr) {
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
	if (hair == nullptr) {
		return;
	}

	Locker locker(hair);

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

	if (ImageDesignManager::validateCustomizationString(&data, appearanceFilename))
		tanoHair->setCustomizationString(hairCustomization);

	creature->transferObject(tanoHair, 4);
}

void PlayerCreationManager::addCustomization(CreatureObject* creature,
		const String& customizationString, const String& appearanceFilename) const {
	//TODO: Validate customizationString
	CustomizationVariables data;

	data.parseFromClientString(customizationString);

	if (ImageDesignManager::validateCustomizationString(&data, appearanceFilename))
		creature->setCustomizationString(customizationString);
}

void PlayerCreationManager::addStartingItemsInto(CreatureObject* creature,
		SceneObject* container) const {

	if (creature == nullptr || container == nullptr
			|| !creature->isPlayerCreature()) {
		instance()->info("addStartingItemsInto: nullptr or not PlayerCreature");
		return;
	}

	PlayerCreatureTemplate* playerTemplate =
			dynamic_cast<PlayerCreatureTemplate*>(creature->getObjectTemplate());

	if (playerTemplate == nullptr) {
		instance()->info("addStartingItemsInto: playerTemplate nullptr");
		return;
	}

	//Add common starting items.
	for (int itemNumber = 0; itemNumber < commonStartingItems.size();
			itemNumber++) {
		ManagedReference<SceneObject*> item = zoneServer->createObject(
				commonStartingItems.get(itemNumber).hashCode(), 1);
		if (item != nullptr && container != nullptr && !item->isWeaponObject()) {
			if (!container->transferObject(item, -1, true)) {
				item->destroyObjectFromDatabase(true);
			}
		} else if (item != nullptr) {
			item->destroyObjectFromDatabase(true);
		}
	}

	//Add profession specific items.
	PlayerObject* player = creature->getPlayerObject();
	if (player == nullptr) {
		instance()->info("addStartingItemsInto: playerObject nullptr");
		return;
	}

	String profession = player->getStarterProfession();

	ProfessionDefaultsInfo* professionData = professionDefaultsInfo.get(
			profession);

	if (professionData == nullptr)
		professionData = professionDefaultsInfo.get(0);

	for (int itemNumber = 0;
			itemNumber < professionData->getStartingItems()->size();
			itemNumber++) {
		ManagedReference<SceneObject*> item = zoneServer->createObject(
				professionData->getStartingItems()->get(itemNumber).hashCode(),
				1);
		if (item != nullptr && container != nullptr && !item->isWeaponObject()) {
			if (!container->transferObject(item, -1, true)) {
				item->destroyObjectFromDatabase(true);
			}
		} else if (item != nullptr) {
			item->destroyObjectFromDatabase(true);
		}
	}

	//Add race specific items.
	const Vector <String>& startingItems = playerTemplate->getStartingItems();

	for (int i = 0; i < startingItems.size(); ++i) {
		ManagedReference<SceneObject*> item = zoneServer->createObject(
				startingItems.get(i).hashCode(), 1);

		if (item != nullptr && container != nullptr && !item->isWeaponObject()) {
			if (!container->transferObject(item, -1, true)) {
				item->destroyObjectFromDatabase(true);
			}
		} else if (item != nullptr) {
			item->destroyObjectFromDatabase(true);
		}
	}

}

void PlayerCreationManager::addStartingWeaponsInto(CreatureObject* creature,
		SceneObject* container) const {
	if (creature == nullptr || container == nullptr || !creature->isPlayerCreature())
		return;

//	container = creature->getSlottedObject("inventory");

	PlayerCreatureTemplate* playerTemplate =
			dynamic_cast<PlayerCreatureTemplate*>(creature->getObjectTemplate());

	if (playerTemplate == nullptr) {
		instance()->info("addStartingWeaponsInto: playerTemplate nullptr");
		return;
	}

	PlayerObject* player = creature->getPlayerObject();

	if (player == nullptr) {
		instance()->info("addStartingWeaponsInto: playerObject nullptr");
		return;
	}

	String profession = player->getStarterProfession();

	ProfessionDefaultsInfo* professionData = professionDefaultsInfo.get(
			profession);

	if (professionData == nullptr)
		professionData = professionDefaultsInfo.get(0);


	//Add common starting items.
	for (int itemNumber = 0; itemNumber < commonStartingItems.size();
			itemNumber++) {
		ManagedReference<SceneObject*> item = zoneServer->createObject(
				commonStartingItems.get(itemNumber).hashCode(), 1);
		if (item != nullptr && container != nullptr && item->isWeaponObject()) {
			if (container->transferObject(item, -1, true)) {
				item->sendTo(creature, true);
			} else {
				item->destroyObjectFromDatabase(true);
			}
		} else if (item != nullptr) {
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
		if (item != nullptr && container != nullptr && item->isWeaponObject()) {
			if (container->transferObject(item, -1, true)) {
				item->sendTo(creature, true);
			} else {
				item->destroyObjectFromDatabase(true);
			}
		} else if (item != nullptr) {
			item->destroyObjectFromDatabase(true);
		}
	}


	//Add race specific items.
	const Vector<String>& startingItems = playerTemplate->getStartingItems();

	for (int i = 0; i < startingItems.size(); ++i) {
		ManagedReference<SceneObject*> item = zoneServer->createObject(
				startingItems.get(i).hashCode(), 1);

		if (item != nullptr && container != nullptr && item->isWeaponObject()) {
			if (container->transferObject(item, -1, true)) {
				item->sendTo(creature, true);
			} else {
				item->destroyObjectFromDatabase(true);
			}
		} else if (item != nullptr) {
			item->destroyObjectFromDatabase(true);
		}
	}
}

void PlayerCreationManager::addRacialMods(CreatureObject* creature,
		const String& race, const Vector<String>* startingSkills,
		const Vector<String>* startingItems, bool equipmentOnly) const {
	Reference<RacialCreationData*> racialData = racialCreationData.get(race);

	if (racialData == nullptr)
		racialData = racialCreationData.get(0);

	for (int i = 0; i < 9; ++i) {
		int mod = racialData->getAttributeMod(i) + creature->getBaseHAM(i);
		creature->setBaseHAM(i, mod, false);
		creature->setHAM(i, mod, false);
		creature->setMaxHAM(i, mod, false);
	}

	if (startingSkills != nullptr) {
		for (int i = 0; i < startingSkills->size(); ++i) {
			SkillManager::instance()->awardSkill(startingSkills->get(i),
					creature, false, true, true);
		}
	}

	// Get inventory.
	if (!equipmentOnly) {
		SceneObject* inventory = creature->getSlottedObject("inventory");
		if (inventory == nullptr) {
			return;
		}

		if (startingItems != nullptr) {
			for (int i = 0; i < startingItems->size(); ++i) {
				ManagedReference<SceneObject*> item = zoneServer->createObject(
						startingItems->get(i).hashCode(), 1);

				if (item != nullptr) {
					if (!inventory->transferObject(item, -1, false)) {
						item->destroyObjectFromDatabase(true);
					}
				}

			}
		}
	}
}
