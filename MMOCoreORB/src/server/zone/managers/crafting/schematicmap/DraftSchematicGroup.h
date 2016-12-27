/*
				Copyright <SWGEmu>
		See file COPYING for copying conditions.*/

/**
 * \file DraftSchematicGroup.h
 * \author Kyle Burkhardt
 * \date 6-01-10
 */

#ifndef DRAFTSCHEMATICGROUP_H_
#define DRAFTSCHEMATICGROUP_H_

#include "server/zone/objects/draftschematic/DraftSchematic.h"

class DraftSchematicGroup : public Vector<ManagedReference<DraftSchematic*> > {

public:
	DraftSchematicGroup() {

	}

	~DraftSchematicGroup() {

	}

	bool contains(DraftSchematic* schematic) {
		for(int i = 0; i < size(); ++i) {
			DraftSchematic* existingSchematic = get(i);
			if(existingSchematic->getClientObjectCRC() ==
					schematic->getClientObjectCRC())
				return true;
		}
		return false;
	}

	void print() {
		for(int i = 0; i < size(); ++i) {
			System::out << get(i)->getCustomName() << endl;
		}
	}
};

#endif /* DRAFTSCHEMATICGROUP_H_ */
