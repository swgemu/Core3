/*
				Copyright <SWGEmu>
		See file COPYING for copying conditions.*/

/**
 * \file SchematicMap.h
 * \author Kyle Burkhardt
 * \date 6-01-10
 */

#ifndef SCHEMATICMAP_H_
#define SCHEMATICMAP_H_

#include "server/zone/ZoneServer.h"

#include "server/zone/objects/draftschematic/DraftSchematic.h"

#include "server/zone/managers/object/ObjectManager.h"
#include "server/zone/objects/player/PlayerObject.h"

#include "DraftSchematicGroup.h"

class SchematicMap : public Singleton<SchematicMap>, public Lua {

	VectorMap<uint32, ManagedReference<DraftSchematic* > > schematicCrcMap;
	VectorMap<String, DraftSchematicGroup* > groupMap;
	ManagedReference<ZoneServer*> zoneServer;
	ObjectManager* objectManager;

	VectorMap<uint32, String> iffGroupMap;

public:

	SchematicMap();
	~SchematicMap();

	void initialize(ZoneServer* server);

	void loadDraftSchematicDatabase();

	bool addSchematics(PlayerObject* playerObject, Vector<String> schematicgroups, bool updateClient);
	void removeSchematics(PlayerObject* playerObject, Vector<String> schematicgroups, bool updateClient);
//	bool addSchematic(PlayerObject* playerObject, DraftSchematic* schematic, bool updateClient);
//	void removeSchematic(PlayerObject* playerObject, DraftSchematic* schematic, bool updateClient);

	void sendDraftSlotsTo(CreatureObject* player, uint32 schematicID);
	void sendResourceWeightsTo(CreatureObject* player, uint32 schematicID);

	DraftSchematic* get(uint32 schemid) {
		return schematicCrcMap.get(schemid);
	}

private:

	void loadSchematicGroups();
	void loadDraftSchematicFile();
	void buildSchematicGroups();
};

#endif /* SCHEMATICMAP_H_ */
