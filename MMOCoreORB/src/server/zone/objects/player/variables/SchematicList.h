/*
 * SchematicList.h
 *
 *  Created on: 6/3/2010
 *      Author: kyle
 */

#ifndef SCHEMATICLIST_H_
#define SCHEMATICLIST_H_

#include <stddef.h>
#include <algorithm>

#include "engine/core/ManagedReference.h"
#include "engine/engine.h"
#include "server/zone/objects/draftschematic/DraftSchematic.h"
#include "server/zone/objects/scene/variables/DeltaVector.h"
#include "system/lang/Object.h"
#include "system/platform.h"
#include "system/util/Vector.h"
#include "system/util/VectorMap.h"

class DeltaMessage;
namespace engine {
namespace service {
namespace proto {
class BaseMessage;
}  // namespace proto
}  // namespace service
}  // namespace engine
namespace server {
namespace zone {
namespace objects {
namespace creature {
class CreatureObject;
}  // namespace creature
namespace scene {
class SceneObject;
}  // namespace scene
}  // namespace objects
}  // namespace zone
}  // namespace server
namespace sys {
namespace io {
class ObjectInputStream;
class ObjectOutputStream;
}  // namespace io
}  // namespace sys

class SchematicList : public DeltaVector<ManagedReference<DraftSchematic* > > {
protected:

	/// This vector is for schematics without skills when we need to reload them
	/// when skills are dropped
	VectorMap<ManagedReference<DraftSchematic* >, int > rewardedSchematics;

public:
	enum {MISSION = 0, LOOT, QUEST};

	SchematicList() {
		rewardedSchematics.setNoDuplicateInsertPlan();
	}

	SchematicList(const SchematicList& list) : Object(), DeltaVector<ManagedReference<DraftSchematic* > >(list) {
		rewardedSchematics.setNoDuplicateInsertPlan();
		rewardedSchematics = list.rewardedSchematics;
	}

	bool add(DraftSchematic* schematic, DeltaMessage* message = NULL, int updates = 1);

	bool addRewardedSchematic(DraftSchematic* schematic, short type, int quantity);

	void addRewardedSchematics(SceneObject* player);
	void removeRewardedSchematic(DraftSchematic* schematic);
	bool decreaseSchematicUseCount(DraftSchematic* schematic);

	bool contains(DraftSchematic* schematic);
	bool contains(Vector<ManagedReference<DraftSchematic* > > filteredschematics, DraftSchematic* schematic);
	DraftSchematic* searchForDuplicate(Vector<ManagedReference<DraftSchematic* > > filteredschematics, DraftSchematic* schematic);

	bool toBinaryStream(ObjectOutputStream* stream);
	bool parseFromBinaryStream(ObjectInputStream* stream);

	Vector<ManagedReference<DraftSchematic* > > filterSchematicList(CreatureObject* player, Vector<uint32>* enabledTabs, int complexityLevel);

	void insertToMessage(BaseMessage* msg);
};


#endif /* SCHEMATICLIST_H_ */
