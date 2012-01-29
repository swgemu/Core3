/*
Copyright (C) 2007 <SWGEmu>
This File is part of Core3.
This program is free software; you can redistribute
it and/or modify it under the terms of the GNU Lesser
General Public License as published by the Free Software
Foundation; either version 2 of the License,
or (at your option) any later version.

This program is distributed in the hope that it will be useful,
but WITHOUT ANY WARRANTY; without even the implied warranty of
MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.
See the GNU Lesser General Public License for
more details.

You should have received a copy of the GNU Lesser General
Public License along with this program; if not, write to
the Free Software Foundation, Inc., 51 Franklin St, Fifth Floor, Boston, MA 02110-1301 USA

Linking Engine3 statically or dynamically with other modules
is making a combined work based on Engine3.
Thus, the terms and conditions of the GNU Lesser General Public License
cover the whole combination.

In addition, as a special exception, the copyright holders of Engine3
give you permission to combine Engine3 program with free software
programs or libraries that are released under the GNU LGPL and with
code included in the standard release of Core3 under the GNU LGPL
license (or modified versions of such code, with unchanged license).
You may copy and distribute such a system following the terms of the
GNU LGPL for Engine3 and the licenses of the other code concerned,
provided that you include the source code of that other code when
and as the GNU LGPL requires distribution of source code.

Note that people who make modified versions of Engine3 are not obligated
to grant this special exception for their modified versions;
it is their choice whether to do so. The GNU Lesser General Public License
gives permission to release a modified version without this exception;
this exception also makes it possible to release a modified version
which carries forward this exception.

*/

#include "server/db/ServerDatabase.h"
#include "server/db/MantisDatabase.h"
#include "PlayerCreationManager.h"
#include "ProfessionDefaultsInfo.h"
#include "RacialCreationData.h"
#include "HairStyleInfo.h"
#include "../PlayerManager.h"
#include "server/chat/ChatManager.h"
#include "server/login/account/Account.h"
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

#define FREE_GOD_MODE

PlayerCreationManager::PlayerCreationManager()
		: Logger("PlayerCreationManager") {

	setLogging(true);
	setGlobalLogging(false);

	zoneServer = ServerCore::getZoneServer();

	racialCreationData.setNoDuplicateInsertPlan();
	professionDefaultsInfo.setNoDuplicateInsertPlan();
	hairStyleInfo.setNoDuplicateInsertPlan();

	startingCash = 100;
	startingBank = 1000;

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
	IffStream* iffStream = templateManager->openIffFile("datatables/creation/attribute_limits.iff");

	if (iffStream == NULL) {
		error("Could not open attribute limits file.");
		return;
	}

	DataTableIff attributeLimitsTable;
	attributeLimitsTable.readObject(iffStream);

	delete iffStream;

	iffStream = templateManager->openIffFile("datatables/creation/racial_mods.iff");

	DataTableIff racialModsTable;
	racialModsTable.readObject(iffStream);

	delete iffStream;

	for (int i = 0; i < attributeLimitsTable.getTotalRows(); ++i) {
		DataTableRow* attributeLimitRow = attributeLimitsTable.getRow(i);

		String maleTemplate;
		String femaleTemplate;

		attributeLimitRow->getValue(0, maleTemplate);
		attributeLimitRow->getValue(1, femaleTemplate);

		Vector<DataTableRow*> maleRows = racialModsTable.getRowsByColumn(0, maleTemplate);
		Vector<DataTableRow*> femaleRows = racialModsTable.getRowsByColumn(1, femaleTemplate);

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

	info("Loaded " + String::valueOf(racialCreationData.size()) + " playable species.");
}

void PlayerCreationManager::loadProfessionDefaultsInfo() {
	TemplateManager* templateManager = TemplateManager::instance();
	IffStream* iffStream = templateManager->openIffFile("creation/profession_defaults.iff");

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
	}

	//Now we want to load the profession mods.
	iffStream = templateManager->openIffFile("datatables/creation/profession_mods.iff");

	DataTableIff dtiff;
	dtiff.readObject(iffStream);

	delete iffStream;

	for (int i = 0; i < dtiff.getTotalRows(); ++i) {
		DataTableRow* row = dtiff.getRow(i);

		String key;
		row->getValue(0, key);

		//Check if the professionInfo for this exists.
		Reference<ProfessionDefaultsInfo*> pdi = professionDefaultsInfo.get(key);

		if (pdi == NULL)
			continue;

		for (int i = 1; i < 10; ++i) {
			int value = 0;
			row->getValue(i, value);
			pdi->setAttributeMod(i - 1, value);
		}
	}

	info("Loaded " + String::valueOf(professionDefaultsInfo.size()) + " creation professions.");
}

void PlayerCreationManager::loadDefaultCharacterItems() {
	IffStream* iffStream = TemplateManager::instance()->openIffFile("creation/default_pc_equipment.iff");

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

		SortedVector<String> items;

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
}

void PlayerCreationManager::loadHairStyleInfo() {
	IffStream* iffStream = TemplateManager::instance()->openIffFile("creation/default_pc_hairstyles.iff");

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

	info("Loaded " + String::valueOf(totalHairStyles) + " total creation hair styles.");
}

void PlayerCreationManager::loadLuaConfig() {
	info("Loading configuration script.");

	Lua* lua = new Lua();
	lua->init();

	lua->runFile("scripts/managers/player_creation_manager.lua");

	startingCash = lua->getGlobalInt("startingCash");
	startingBank = lua->getGlobalInt("startingBank");
	skillPoints = lua->getGlobalInt("skillPoints");

	loadLuaStartingItems(lua);

	delete lua;
	lua = NULL;
}

void PlayerCreationManager::loadLuaStartingItems(Lua* lua) {
	// Catch potential errors from loading starting items.
	try {
		// Read professions.
		Vector<String> professions;
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
				professionDefaultsInfo.get(professions.get(professionNumber))->getStartingItems()->add(professionSpecificItemList.getStringAt(itemNumber));
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
	}
	catch (Exception e) {
		error("Failed to load starting items.");
		error(e.getMessage());
	}
}

bool PlayerCreationManager::createCharacter(MessageCallback* data) {
	TemplateManager* templateManager = TemplateManager::instance();

	ClientCreateCharacterCallback* callback = cast<ClientCreateCharacterCallback*>( data);
	ZoneClientSession* client = data->getClient();

	PlayerManager* playerManager = zoneServer->getPlayerManager();

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

	if (playerTemplate == NULL) {
		error("Unknown player template selected: " + raceFile);
		return false;
	}

	int raceID = playerTemplate->getRace();


	String fileName = playerTemplate->getTemplateFileName();
	String clientTemplate = templateManager->getTemplateFile(playerTemplate->getClientObjectCRC());

	RacialCreationData* raceData = racialCreationData.get(fileName);

	if (raceData == NULL)
		raceData = racialCreationData.get(0); //Just get the first race, since they tried to create a race that doesn't exist.

	String profession, customization, hairTemplate, hairCustomization;
	callback->getSkill(profession);
	callback->getCustomizationString(customization);
	callback->getHairObject(hairTemplate);
	callback->getHairCustomization(hairCustomization);

	float height = callback->getHeight();
	height = MAX(MIN(height, playerTemplate->getMaxScale()), playerTemplate->getMinScale());

	//validate biography
	UnicodeString bio;
	callback->getBiography(bio);

	bool doTutorial = callback->getTutorialFlag();
	//bool doTutorial = false;

	ManagedReference<CreatureObject*> playerCreature = dynamic_cast<CreatureObject*>(zoneServer->createObject(serverObjectCRC, 2));

	if (playerCreature == NULL) {
		error("Could not create player with template: " + raceFile);
		return false;
	}

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

	addCustomization(playerCreature, customization);
	addHair(playerCreature, hairTemplate, hairCustomization);
	if (!doTutorial) {
		addProfessionStartingItems(playerCreature, profession, clientTemplate, false);
		addStartingItems(playerCreature, clientTemplate, false);
		addRacialMods(playerCreature, fileName, playerTemplate->getStartingSkills(), playerTemplate->getStartingItems(), false);
	} else {
		addProfessionStartingItems(playerCreature, profession, clientTemplate, true);
		addStartingItems(playerCreature, clientTemplate, true);
		addRacialMods(playerCreature, fileName, playerTemplate->getStartingSkills(), playerTemplate->getStartingItems(), true);
	}

	// Set starting cash and starting bank
	playerCreature->setCashCredits(startingCash, false);
	playerCreature->setBankCredits(startingBank, false);

	if (ghost != NULL) {

		ghost->setAccountID(client->getAccountID());

#ifndef FREE_GOD_MODE
		try {
			uint32 accID = client->getAccountID();

			String query = "SELECT username FROM accounts WHERE account_id = " + String::valueOf(accID);

			Reference<ResultSet*> res = ServerDatabase::instance()->executeQuery(query);

			if (res->next()) {
				String accountName = res->getString(0);

				query = "SELECT access_level from mantis_user_table where username = '" + accountName;
				query += "'";

				res = MantisDatabase::instance()->executeQuery(query);

				if (res->next()) {
					uint32 level = res->getUnsignedInt(0);

					if (level > 25) {
						ghost->setAdminLevel(2);
						skillManager->addAbility(ghost, "admin", false);
					}
				}
			}

		} catch (Exception& e) {
			error(e.getMessage());
		}
#else
		//********************************
		// Uncomment to make all new players admins
		ghost->setAdminLevel(2);
		skillManager->addAbility(ghost, "admin", false);
		//********************************
#endif

		if (doTutorial)
			playerManager->createTutorialBuilding(playerCreature);
		else
			playerManager->createSkippedTutorialBuilding(playerCreature);

		ValidatedPosition* lastValidatedPosition = ghost->getLastValidatedPosition();
		lastValidatedPosition->update(playerCreature);

		playerManager->generateHologrindSkills(playerCreature);

		ghost->setBiography(bio);
		ghost->setRaceID(raceID);
	}

	//Add a ship
	ShipControlDevice* shipControlDevice = cast<ShipControlDevice*>( zoneServer->createObject(String("object/intangible/ship/basic_tiefighter_pcd.iff").hashCode(), 1));
	//ShipObject* ship = cast<ShipObject*>( server->createObject(String("object/ship/player/player_sorosuub_space_yacht.iff").hashCode(), 1));
	ShipObject* ship = cast<ShipObject*>( zoneServer->createObject(String("object/ship/player/player_basic_tiefighter.iff").hashCode(), 1));

	shipControlDevice->setControlledObject(ship);

	if (!shipControlDevice->transferObject(ship, 4))
		error("Adding of ship to device failed");

	SceneObject* datapad = playerCreature->getSlottedObject("datapad");
	datapad->transferObject(shipControlDevice, -1);

	ClientCreateCharacterSuccess* msg = new ClientCreateCharacterSuccess(playerCreature->getObjectID());
	playerCreature->sendMessage(msg);

	ChatManager* chatManager = zoneServer->getChatManager();
	chatManager->addPlayer(playerCreature);

	String firstName = playerCreature->getFirstName();
	String lastName = playerCreature->getLastName();

	try {
		StringBuffer query;
		query << "INSERT INTO `characters_dirty` (`character_oid`, `account_id`, `galaxy_id`, `firstname`, `surname`, `race`, `gender`, `template`)"
				<< " VALUES (" <<  playerCreature->getObjectID() << "," << client->getAccountID() <<  "," << zoneServer->getGalaxyID() << ","
				<< "'" << firstName.escapeString() << "','" << lastName.escapeString() << "'," << raceID << "," <<  0 << ",'" << raceFile.escapeString() << "')";

		ServerDatabase::instance()->executeStatement(query);
	} catch (DatabaseException& e) {
		error(e.getMessage());
	}

	playerManager->addPlayer(playerCreature);

	client->addCharacter(playerCreature->getObjectID());

	return true;
}

int PlayerCreationManager::getMaximumAttributeLimit(const String& race, int attributeNumber) {
	String maleRace = race + "_male";

	if (attributeNumber < 0 || attributeNumber > 8) {
		attributeNumber = 0;
	}

	Reference<RacialCreationData*> racialData = racialCreationData.get(maleRace);

	if (racialData != NULL) {
		return racialData->getAttributeMax(attributeNumber);
	} else {
		return racialCreationData.get("human_male")->getAttributeMax(attributeNumber);
	}
}

int PlayerCreationManager::getMinimumAttributeLimit(const String& race, int attributeNumber) {
	String maleRace = race + "_male";

	if (attributeNumber < 0 || attributeNumber > 8) {
		attributeNumber = 0;
	}

	Reference<RacialCreationData*> racialData = racialCreationData.get(maleRace);

	if (racialData != NULL) {
		return racialData->getAttributeMin(attributeNumber);
	} else {
		return racialCreationData.get("human_male")->getAttributeMin(attributeNumber);
	}
}

int PlayerCreationManager::getTotalAttributeLimit(const String& race) {
	String maleRace = race + "_male";

	Reference<RacialCreationData*> racialData = racialCreationData.get(maleRace);

	if (racialData != NULL) {
		return racialData->getAttributeTotal();
	} else {
		return racialCreationData.get("human_male")->getAttributeTotal();
	}
}

bool PlayerCreationManager::validateCharacterName(const String& characterName) {
	return true;
}

void PlayerCreationManager::addStartingItems(CreatureObject* creature, const String& clientTemplate, bool equipmentOnly) {
	SortedVector<String>* items = NULL;

	if (!defaultCharacterEquipment.contains(clientTemplate))
		items = &defaultCharacterEquipment.get(0);
	else
		items = &defaultCharacterEquipment.get(clientTemplate);

	for (int i = 0; i < items->size(); ++i) {
		String itemTemplate = items->get(i);

		ManagedReference<SceneObject*> item = zoneServer->createObject(itemTemplate.hashCode(), 1);

		if (item != NULL)
			creature->transferObject(item, 4, false);
	}

	// Get inventory.
	if (!equipmentOnly) {
		SceneObject* inventory = creature->getSlottedObject("inventory");

		//Add common starting items.
		for (int itemNumber = 0; itemNumber < commonStartingItems.size(); itemNumber++) {
			ManagedReference<SceneObject*> item = zoneServer->createObject(commonStartingItems.get(itemNumber).hashCode(), 1);
			if (item != NULL && inventory != NULL) {
				inventory->transferObject(item, -1, false);
			}
		}
	}
}

void PlayerCreationManager::addProfessionStartingItems(CreatureObject* creature, const String& profession, const String& clientTemplate, bool equipmentOnly) {
	ProfessionDefaultsInfo* professionData = professionDefaultsInfo.get(profession);

	if (professionData == NULL)
		professionData = professionDefaultsInfo.get(0);

	Reference<Skill*> startingSkill = professionData->getSkill();

	//Starting skill.
	SkillManager::instance()->awardSkill(startingSkill->getSkillName(), creature, false, true, true);

	SortedVector<String>* itemTemplates = professionData->getProfessionItems(clientTemplate);

	if (itemTemplates == NULL)
		return;

	for (int i = 0; i < itemTemplates->size(); ++i) {
		String itemTemplate = itemTemplates->get(i);

		ManagedReference<SceneObject*> item;

		try {
			item = zoneServer->createObject(itemTemplate.hashCode(), 1);
		} catch (Exception& e) {

		}

		if (item != NULL)
			creature->transferObject(item, 4, false);
		else
			error("could not create profession item " + itemTemplate);
	}

	// Get inventory.
	if (!equipmentOnly) {
		SceneObject* inventory = creature->getSlottedObject("inventory");

		//Add profession specific items.
		for (int itemNumber = 0; itemNumber < professionData->getStartingItems()->size(); itemNumber++) {
			String itemTemplate = professionData->getStartingItems()->get(itemNumber);

			ManagedReference<SceneObject*> item = zoneServer->createObject(itemTemplate.hashCode(), 1);

			if (item != NULL && inventory != NULL) {
				inventory->transferObject(item, -1, false);
			} else if (item == NULL) {
				error("could not create profession item " + itemTemplate);
			}
		}
	}

	//Set the hams.
	for (int i = 0; i < 9; ++i) {
		int mod = professionData->getAttributeMod(i);
		creature->setBaseHAM(i, mod, false);
		creature->setHAM(i, mod, false);
		creature->setMaxHAM(i, mod, false);
	}
}

void PlayerCreationManager::addHair(CreatureObject* creature, const String& hairTemplate, const String& hairCustomization) {
	if (hairTemplate.isEmpty())
		return;

	HairStyleInfo* hairInfo = hairStyleInfo.get(hairTemplate);

	if (hairInfo == NULL)
		hairInfo = hairStyleInfo.get(0);

	ManagedReference<SceneObject*> hair = zoneServer->createObject(hairTemplate.hashCode(), 1);

	//TODO: Validate hairCustomization
	if (hair == NULL || !hair->isTangibleObject())
		return;

	TangibleObject* tanoHair = cast<TangibleObject*>( hair.get());
	tanoHair->setCustomizationString(hairCustomization);

	creature->transferObject(tanoHair, 4);
}

void PlayerCreationManager::addCustomization(CreatureObject* creature, const String& customizationString) {
	//TODO: Validate customizationString

	creature->setCustomizationString(customizationString);
}

void PlayerCreationManager::addStartingItemsInto(CreatureObject* creature, SceneObject* container) {

	if (creature == NULL || container == NULL || !creature->isPlayerCreature()) {
		instance()->info("addStartingItemsInto: NULL or not PlayerCreature");
		return;
	}

	PlayerCreatureTemplate* playerTemplate = dynamic_cast<PlayerCreatureTemplate*>(creature->getObjectTemplate());

	if (playerTemplate == NULL) {
		instance()->info("addStartingItemsInto: playerTemplate NULL");
		return;
	}

	//Add common starting items.
	for (int itemNumber = 0; itemNumber < commonStartingItems.size(); itemNumber++) {
		ManagedReference<SceneObject*> item = zoneServer->createObject(commonStartingItems.get(itemNumber).hashCode(), 1);
		if (item != NULL && container != NULL && !item->isWeaponObject()) {
			container->transferObject(item, -1, true);
		}
	}

	//Add profession specific items.
	PlayerObject* player = creature->getPlayerObject();
	if (player == NULL) {
		instance()->info("addStartingItemsInto: playerObject NULL");
		return;
	}

	String profession = player->getStarterProfession();

	ProfessionDefaultsInfo* professionData = professionDefaultsInfo.get(profession);

	if (professionData == NULL)
		professionData = professionDefaultsInfo.get(0);

	for (int itemNumber = 0; itemNumber < professionData->getStartingItems()->size(); itemNumber++) {
		ManagedReference<SceneObject*> item = zoneServer->createObject(professionData->getStartingItems()->get(itemNumber).hashCode(), 1);
		if (item != NULL && container != NULL && !item->isWeaponObject()) {
			container->transferObject(item, -1, true);
		}
	}


	//Add race specific items.
	Vector<String>* startingItems = playerTemplate->getStartingItems();

	if (startingItems != NULL) {
		for (int i = 0; i < startingItems->size(); ++i) {
			ManagedReference<SceneObject*> item = zoneServer->createObject(startingItems->get(i).hashCode(), 1);

			if (item != NULL && container != NULL && !item->isWeaponObject())
				container->transferObject(item, -1, true);
		}

	}
}

void PlayerCreationManager::addStartingWeaponsInto(CreatureObject* creature, SceneObject* container) {
	if (creature == NULL || container == NULL || !creature->isPlayerCreature())
		return;

//	container = creature->getSlottedObject("inventory");

	PlayerCreatureTemplate* playerTemplate = dynamic_cast<PlayerCreatureTemplate*>(creature->getObjectTemplate());

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

	ProfessionDefaultsInfo* professionData = professionDefaultsInfo.get(profession);

	if (professionData == NULL)
		professionData = professionDefaultsInfo.get(0);


	//Add common starting items.
	for (int itemNumber = 0; itemNumber < commonStartingItems.size(); itemNumber++) {
		ManagedReference<SceneObject*> item = zoneServer->createObject(commonStartingItems.get(itemNumber).hashCode(), 1);
		if (item != NULL && container != NULL && item->isWeaponObject()) {
			item->sendTo(creature, true);
			container->transferObject(item, -1, true);
		}
	}


	//Add profession specific items.
	for (int itemNumber = 0; itemNumber < professionData->getStartingItems()->size(); itemNumber++) {
		ManagedReference<SceneObject*> item = zoneServer->createObject(professionData->getStartingItems()->get(itemNumber).hashCode(), 1);
		if (item != NULL && container != NULL && item->isWeaponObject()) {
			item->sendTo(creature, true);
			container->transferObject(item, -1, true);
		}
	}


	//Add race specific items.
	Vector<String>* startingItems = playerTemplate->getStartingItems();

	if (startingItems != NULL) {
		for (int i = 0; i < startingItems->size(); ++i) {
			ManagedReference<SceneObject*> item = zoneServer->createObject(startingItems->get(i).hashCode(), 1);

			if (item != NULL && container != NULL && item->isWeaponObject()) {
				item->sendTo(creature, true);
				container->transferObject(item, -1, true);
			}
		}
	}
}

void PlayerCreationManager::addRacialMods(CreatureObject* creature, const String& race, Vector<String>* startingSkills, Vector<String>* startingItems, bool equipmentOnly) {
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
			SkillManager::instance()->awardSkill(startingSkills->get(i), creature, false, true, true);
		}
	}

	// Get inventory.
	if (!equipmentOnly) {
		SceneObject* inventory = creature->getSlottedObject("inventory");

		if (startingItems != NULL) {
			for (int i = 0; i < startingItems->size(); ++i) {
				ManagedReference<SceneObject*> item = zoneServer->createObject(startingItems->get(i).hashCode(), 1);

				if (item != NULL && inventory != NULL)
					inventory->transferObject(item, -1, false);
			}
		}
	}
}
