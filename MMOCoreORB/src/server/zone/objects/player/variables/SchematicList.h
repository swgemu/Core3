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

	/// This vector is for limited use schematics when we need to reload them
	/// when skills are dropped
	Vector<ManagedReference<DraftSchematic* > > limitedUseSchematics;

public:
	SchematicList() {

	}

	SchematicList(const SchematicList& list) : Object(), DeltaVector<ManagedReference<DraftSchematic* > >(list) {
		limitedUseSchematics = list.limitedUseSchematics;
	}

	bool add(DraftSchematic* schematic, DeltaMessage* message = NULL, int updates = 1);


	void awardLimitedUseSchematics();
	bool updateUseCount(DraftSchematic* schematic);

	bool contains(DraftSchematic* schematic);
	bool contains(Vector<ManagedReference<DraftSchematic* > > filteredschematics, DraftSchematic* schematic);
	DraftSchematic* searchForDuplicate(Vector<ManagedReference<DraftSchematic* > > filteredschematics, DraftSchematic* schematic);

	/*bool toString(String& str);
	bool parseFromString(const String& str, int version = 0);*/

	bool toBinaryStream(ObjectOutputStream* stream);
	bool parseFromBinaryStream(ObjectInputStream* stream);

	void getLimitedUseSchematicList(Vector<ManagedReference<DraftSchematic*> >& schematics);
	void loadLimitedUseSchematics(Vector<ManagedReference<DraftSchematic*> >& schematics);

	Vector<ManagedReference<DraftSchematic* > > filterSchematicList(CreatureObject* player, Vector<uint32>* enabledTabs, int complexityLevel);

	void insertToMessage(BaseMessage* msg);
};


#endif /* SCHEMATICLIST_H_ */
