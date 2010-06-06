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

public:
	bool add(DraftSchematic* schematic, DeltaMessage* message = NULL, int updates = 1);
	bool remove(DraftSchematic* schematic, DeltaMessage* message = NULL, int updates = 1);

	bool toString(String& str);
	bool parseFromString(const String& str, int version = 0);

	bool toBinaryStream(ObjectOutputStream* stream);
	bool parseFromBinaryStream(ObjectInputStream* stream);

	void getCrcList(Vector<uint32>& schematics);
	void loadFromCrcs(Vector<uint32>& schematics);

	void insertToMessage(BaseMessage* msg);
};


#endif /* SCHEMATICLIST_H_ */
