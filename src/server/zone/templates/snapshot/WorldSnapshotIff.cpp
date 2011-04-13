/*
 * WorldSnapshotIff.cpp
 *
 *  Created on: Mar 31, 2011
 *      Author: crush
 */

#include "WorldSnapshotIff.h"

WorldSnapshotIff::WorldSnapshotIff() {

}

void WorldSnapshotIff::readObject(IffStream* iffStream) {
	iffStream->openForm('WSNP');

	uint32 version = iffStream->getNextFormType();
	iffStream->openForm(version);

	switch (version) {
	case '0001':
	{
		Chunk* nods = iffStream->openForm('NODS');
		uint32 nodeCount = nods->getChunksSize();

		for (int i = 0; i < nodeCount; ++i) {
			WorldSnapshotNode wsnode;
			wsnode.parse(iffStream);

			nodes.add(wsnode);
		}

		iffStream->closeForm('NODS');
	}
		break;
	case '0000':
	default:
		System::out << "ERROR: Unhandled WorldSnapshotIff version: " << version << endl;
	}

	Chunk* otnl = iffStream->openChunk('OTNL');

	int size = otnl->readInt();

	for (int i = 0; i < size; ++i) {
		String name;
		otnl->readString(name);
		objectTemplateNameList.add(name);
	}

	iffStream->closeChunk('OTNL');

	iffStream->closeForm(version);
	iffStream->closeForm('WSNP');
}
