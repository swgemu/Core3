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

#include "DraftSchematicGroup.h"
#include "engine/core/ManagedReference.h"
#include "engine/lua/Lua.h"
#include "engine/util/Singleton.h"
#include "server/zone/ZoneServer.h"
#include "server/zone/managers/object/ObjectManager.h"
#include "server/zone/objects/draftschematic/DraftSchematic.h"
#include "server/zone/objects/player/PlayerObject.h"
#include "system/lang/String.h"
#include "system/platform.h"
#include "system/util/Vector.h"
#include "system/util/VectorMap.h"

class DraftSchematicGroup;
namespace server {
namespace zone {
namespace managers {
namespace object {
class ObjectManager;
}  // namespace object
}  // namespace managers
namespace objects {
namespace creature {
class CreatureObject;
}  // namespace creature
namespace player {
class PlayerObject;
}  // namespace player
}  // namespace objects
}  // namespace zone
}  // namespace server

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

	bool addSchematics(PlayerObject* playerObject, const Vector<String>& schematicgroups, bool updateClient);
	void removeSchematics(PlayerObject* playerObject, const Vector<String>& schematicgroups, bool updateClient);
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
