/*
 * SchematicList.h
 *
 *  Created on: 6/3/2010
 *      Author: kyle
 */

#ifndef SCHEMATICLIST_H_
#define SCHEMATICLIST_H_

#include "engine/engine.h"
#include "server/zone/objects/scene/variables/DeltaVector.h"
#include "server/zone/objects/draftschematic/DraftSchematic.h"

class SchematicList : public DeltaVector<ManagedReference<DraftSchematic* > > {
protected:

	/// This vector is for schematics without skills when we need to reload them
	/// when skills are dropped
	VectorMap<ManagedReference<DraftSchematic* >, int > rewardedSchematics;

public:
	SchematicList() {
		rewardedSchematics.setNoDuplicateInsertPlan();
	}

	SchematicList(const SchematicList& list) : Object(), DeltaVector<ManagedReference<DraftSchematic* > >(list) {
		rewardedSchematics.setNoDuplicateInsertPlan();
		rewardedSchematics = list.rewardedSchematics;
	}

	bool add(DraftSchematic* schematic, DeltaMessage* message = NULL, int updates = 1);

	bool addRewardedSchematic(DraftSchematic* schematic, int quantity);

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
