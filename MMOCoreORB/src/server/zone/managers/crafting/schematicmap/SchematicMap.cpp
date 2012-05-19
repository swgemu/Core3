/*
Copyright (C) 2010 <SWGEmu>

This File is part of Core3.

This program is free software; you can redistribute
it and/or modify it under the terms of the GNU Lesser
General Public License as published by the Free Software
Foundation; either version 3 of the License,
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

/**
 * \file SchematicMap.cpp
 * \author Kyle Burkhardt
 * \date 6-01-10
 */

#include "SchematicMap.h"
#include "server/zone/objects/draftschematic/draftslot/DraftSlot.h"
#include "server/zone/objects/draftschematic/resourceweight/ResourceWeight.h"
#include "engine/engine.h"

//VectorMap<uint32, ManagedReference<DraftSchematic* > > SchematicMap::schematicIdMap;
//VectorMap<String, DraftSchematicGroup* > SchematicMap::groupMap;
//ZoneServer* SchematicMap::zoneServer = NULL;

SchematicMap::SchematicMap() {

	info("Loading schematics...");

	Lua::init();

	iffGroupMap.setAllowDuplicateInsertPlan();
	groupMap.setNullValue(NULL);
}

SchematicMap::~SchematicMap() {
	while(groupMap.size() > 0)
		delete groupMap.get(0);
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

	buildSchematicGroups();
}

void SchematicMap::loadDraftSchematicDatabase() {

	ObjectDatabase* schematicDatabase = ObjectDatabaseManager::instance()->loadObjectDatabase("draftschematics", true);

	ObjectDatabaseIterator iterator(schematicDatabase);

	uint64 objectID = 0;
	int count = 0;

	while (iterator.getNextKey(objectID)) {

		ManagedReference<DraftSchematic* > draftSchematic = dynamic_cast<DraftSchematic*> (zoneServer->getObject(objectID));

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
	runFile("scripts/crafting/config.lua");

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

		DraftSchematic* schematic = schematicCrcMap.get(servercrc);

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
		String groupName = entry.getValue();

		DraftSchematic* schematic = schematicCrcMap.get(entry.getKey());

		if(schematic != NULL) {

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
		Vector<String> schematicgroups, bool updateClient) {

	Vector<ManagedReference<DraftSchematic* > > schematics;

	for (int i = 0; i < schematicgroups.size(); ++i) {

		String groupName = schematicgroups.get(i);

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
		Vector<String> schematicgroups, bool updateClient) {

	Vector<ManagedReference<DraftSchematic* > > schematics;

	for (int i = 0; i < schematicgroups.size(); ++i) {

		String groupName = schematicgroups.get(i);

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
