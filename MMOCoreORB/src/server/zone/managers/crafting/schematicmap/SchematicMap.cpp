/*
				Copyright <SWGEmu>
		See file COPYING for copying conditions.*/

/**
 * \file SchematicMap.cpp
 * \author Kyle Burkhardt
 * \date 6-01-10
 */

#include "SchematicMap.h"

SchematicMap::SchematicMap() : objectManager(NULL) {
	setLoggingName("SchematicMap");
	info("Loading schematics...");

	Lua::init();

	iffGroupMap.setAllowDuplicateInsertPlan();
	groupMap.setNullValue(NULL);
}

SchematicMap::~SchematicMap() {
	while (groupMap.size() > 0) {
		DraftSchematicGroup* group = groupMap.get(0);
		delete group;
		groupMap.remove(0);
	}
}

void SchematicMap::initialize(ZoneServer* server) {
	zoneServer = server;
	objectManager = zoneServer->getObjectManager();

	loadDraftSchematicDatabase();
	loadDraftSchematicFile();
	loadSchematicGroups();
}

void SchematicMap::loadSchematicGroups() {
	TemplateManager* templateManager = TemplateManager::instance();

	IffStream* iffStream = templateManager->openIffFile(
			"datatables/crafting/schematic_group.iff");

	if (iffStream == NULL) {
		info("schematic_group.iff could not be found.", true);
		return;
	}

	DataTableIff dtiff;
	dtiff.readObject(iffStream);

	String groupId, schematicName;

	for (int i = 0; i < dtiff.getTotalRows(); ++i) {

		DataTableRow* row = dtiff.getRow(i);

		row->getCell(0)->getValue(groupId);
		row->getCell(1)->getValue(schematicName);

		iffGroupMap.put(schematicName.hashCode(), groupId);
	}

	delete iffStream;

	buildSchematicGroups();
}

void SchematicMap::loadDraftSchematicDatabase() {

	ObjectDatabase* schematicDatabase = ObjectDatabaseManager::instance()->loadObjectDatabase("draftschematics", true);

	ObjectDatabaseIterator iterator(schematicDatabase);

	uint64 objectID = 0;
	int count = 0;

	while (iterator.getNextKey(objectID)) {

		ManagedReference<DraftSchematic* > draftSchematic = zoneServer->getObject(objectID).castTo<DraftSchematic*>();

		if(draftSchematic != NULL) {

			if(!schematicCrcMap.contains(draftSchematic->getClientObjectCRC()))
				schematicCrcMap.put(draftSchematic->getClientObjectCRC(), draftSchematic);

			if(!schematicCrcMap.contains(draftSchematic->getServerObjectCRC()))
				schematicCrcMap.put(draftSchematic->getServerObjectCRC(), draftSchematic);

			count++;
		}
	}

	info("Loaded " + String::valueOf(count) + " schematics from database", true);
}

void SchematicMap::loadDraftSchematicFile() {
	runFile("scripts/managers/crafting/schematics.lua");

	// Read and create all the items in the config unless they
	// were already loaded from database.

	LuaObject serverScriptCRCList = getGlobalObject("schematics");

	int size = serverScriptCRCList.getTableSize();
	int count = 0;

	lua_State* L = serverScriptCRCList.getLuaState();

	for (int i = 0; i < size; ++i) {

		lua_rawgeti(L, -1, i + 1);
		LuaObject luaObject(L);

		String path = luaObject.getStringField("path");
		uint32 servercrc = path.hashCode();

		Reference<DraftSchematic*> schematic = schematicCrcMap.get(servercrc);

		luaObject.pop();

		if (schematic == NULL) {
			try {
				schematic = dynamic_cast<DraftSchematic*> (objectManager->createObject(servercrc, 1, "draftschematics"));

				if(schematic == NULL) {
					error("Could not create schematic with crc: " + String::valueOf(servercrc));
					continue;
				}

			} catch (Exception& e) {
				error(e.getMessage());
				error("Could not create schematic with template: " + path);
				continue;
			}
			if(!schematicCrcMap.contains(schematic->getServerObjectCRC()))
				schematicCrcMap.put(schematic->getServerObjectCRC(), schematic);

			if(!schematicCrcMap.contains(schematic->getClientObjectCRC()))
				schematicCrcMap.put(schematic->getClientObjectCRC(), schematic);

			count++;

		}
	}

	info("Loaded " + String::valueOf(count) + " schematics from scripts", true);

	serverScriptCRCList.pop();
}

void SchematicMap::buildSchematicGroups() {

	while(iffGroupMap.size() > 0) {
		VectorMapEntry<uint32, String> entry = iffGroupMap.remove(0);
		const String& groupName = entry.getValue();

		DraftSchematic* schematic = schematicCrcMap.get(entry.getKey());

		if(schematic != NULL) {
			Locker locker(schematic);

			schematic->setGroupName(groupName);

			DraftSchematicGroup* group = groupMap.get(groupName);

			if (group == NULL) {
				group = new DraftSchematicGroup();
				groupMap.put(groupName, group);
			}

			if(!group->contains(schematic))
				group->add(schematic);
		}
	}
}

bool SchematicMap::addSchematics(PlayerObject* playerObject,
		const Vector<String>& schematicgroups, bool updateClient) {

	Vector<ManagedReference<DraftSchematic* > > schematics;

	for (int i = 0; i < schematicgroups.size(); ++i) {
		const String& groupName = schematicgroups.get(i);

		if (groupMap.contains(groupName)) {
			DraftSchematicGroup* dsg = groupMap.get(groupName);

			for(int j = 0; j < dsg->size(); ++j)
				schematics.add(dsg->get(j));
		}
	}

	if (schematics.size() > 0)
		return playerObject->addSchematics(schematics, updateClient);

	return false;
}

void SchematicMap::removeSchematics(PlayerObject* playerObject,
		const Vector<String>& schematicgroups, bool updateClient) {

	Vector<ManagedReference<DraftSchematic* > > schematics;

	for (int i = 0; i < schematicgroups.size(); ++i) {
		const String& groupName = schematicgroups.get(i);

		if (groupMap.contains(groupName)) {

			DraftSchematicGroup* dsg = groupMap.get(groupName);

			for (int j = 0; j < dsg->size(); ++j)
				schematics.add(dsg->get(j));
		}
	}

	if (schematics.size() > 0)
		playerObject->removeSchematics(schematics, updateClient);
}

void SchematicMap::sendDraftSlotsTo(CreatureObject* player, uint32 schematicID) {
	ManagedReference<DraftSchematic*> schematic = schematicCrcMap.get(schematicID);

	if (schematic == NULL)
		return;

	/// The client doesn't display correctly all the time
	/// If these aren't sent twice..... no idea why
	schematic->sendDraftSlotsTo(player);
	schematic->sendDraftSlotsTo(player);
}

void SchematicMap::sendResourceWeightsTo(CreatureObject* player, uint32 schematicID) {
	ManagedReference<DraftSchematic*> schematic = schematicCrcMap.get(schematicID);

	if (schematic == NULL)
		return;

	schematic->sendResourceWeightsTo(player);
}
