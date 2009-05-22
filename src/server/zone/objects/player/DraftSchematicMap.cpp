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

#include "DraftSchematicMap.h"
#include "../../packets/player/PlayerObjectDeltaMessage9.h"

DraftSchematicMap::DraftSchematicMap(Player* ply) {
	player = ply;
}

DraftSchematicMap::~DraftSchematicMap() {

	removedSchematics.removeAll();
	addedSchematics.removeAll();
	overFlowSchematicVector.removeAll();
	schematicVector.removeAll();
}

void DraftSchematicMap::sendTo() {

	Vector<int> schematicsToRemove;
	Vector<ManagedReference<DraftSchematic> > schematicsToDelete;
	bool doRemove;

	for (int i = 0; i < removedSchematics.size(); i++) {
		ManagedReference<DraftSchematic> schematic = getByID(removedSchematics.get(i));
		if (schematic != NULL) {

			doRemove = true;

			for(int j = 0; j < overFlowSchematicVector.size(); ++j) {
				ManagedReference<DraftSchematic> tempSchematic = overFlowSchematicVector.get(j);
				if(tempSchematic->getObjectCRC() == schematic->getObjectCRC()) {
					doRemove = false;
					overFlowSchematicVector.remove(j);
					break;
				}
			}

			if (doRemove) {
				int index = getIndexOf(schematic->getSchematicID());
				schematicsToRemove.add(index);
				schematicVector.remove(index);
				schematic->finalize();
			}
		}
	}

	Vector<ManagedReference<DraftSchematic> > schematicsToAdd;
	bool doAdd;

	for (int i = 0; i < addedSchematics.size(); i++) {
		ManagedReference<DraftSchematic> schematic = addedSchematics.get(i);
		if (schematic != NULL) {

			doAdd = true;

			for(int j = 0; j < schematicVector.size(); ++j) {
				ManagedReference<DraftSchematic> tempSchematic = schematicVector.get(j);
				if(tempSchematic->getObjectCRC() == schematic->getObjectCRC()) {
					doAdd = false;
					overFlowSchematicVector.add(schematic);
					break;
				}
			}

			if (doAdd) {
				schematicVector.add(schematic);
				schematicsToAdd.add(schematic);
			}
		}
	}

	PlayerObjectDeltaMessage9* dplay9 = new PlayerObjectDeltaMessage9(player->getPlayerObject());
	dplay9->startUpdateDraftSchematics(schematicsToRemove.size() + schematicsToAdd.size());

	for(int i = 0; i < schematicsToRemove.size(); ++i) {
		dplay9->removeDraftSchematic(schematicsToRemove.get(i));
	}

	for(int i = 0; i < schematicsToAdd.size(); ++i)
		dplay9->addDraftSchematic(schematicsToAdd.get(i));

	dplay9->close();
	player->sendMessage(dplay9);

	schematicsToDelete.removeAll();
	schematicsToRemove.removeAll();
	schematicsToAdd.removeAll();
	removedSchematics.removeAll();
	addedSchematics.removeAll();
}

void DraftSchematicMap::add(DraftSchematic* schematic) {
	addedSchematics.add(schematic);
}

void DraftSchematicMap::remove(uint32 objectCRC) {

	ManagedReference<DraftSchematic> schematic = getByCRC(objectCRC);
	removedSchematics.add(schematic->getSchematicID());
}

DraftSchematic* DraftSchematicMap::getByID(uint32 schematicID) {

	for(int i = 0; i < schematicVector.size(); i++) {
		ManagedReference<DraftSchematic> schematic = schematicVector.get(i);
		if(schematic->getSchematicID() == schematicID) {
			return schematic;
		}
	}
	return NULL;
}

DraftSchematic* DraftSchematicMap::getByCRC(uint32 objectCRC) {

	for(int i = 0; i < schematicVector.size(); i++) {
		ManagedReference<DraftSchematic> schematic = schematicVector.get(i);
		if(schematic->getObjectCRC() == objectCRC)
			return schematic;
	}
	return NULL;
}

DraftSchematic* DraftSchematicMap::getByIndex(int index) {
	return schematicVector.get(index);
}

int DraftSchematicMap::getIndexOf(uint32 schematicID) {

	for(int i = 0; i < schematicVector.size(); i++) {
		ManagedReference<DraftSchematic> schematic = schematicVector.get(i);
		if(schematic->getSchematicID() == schematicID)
			return i;
	}
	return -1;
}

