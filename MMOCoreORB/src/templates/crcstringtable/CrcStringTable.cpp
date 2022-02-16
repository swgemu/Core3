#include "templates/crcstringtable/CrcStringTable.h"

CrcStringTable::CrcStringTable() {
}

CrcStringTable::~CrcStringTable() {
}

void CrcStringTable::readObject(IffStream* iffStream) {
	iffStream->openForm('CSTB');

	uint32 version = iffStream->getNextFormType();
	iffStream->openForm(version);

	Chunk* chunk = iffStream->openChunk('DATA');
	int32 totalColumns = chunk->readSignedInt();

	iffStream->closeChunk('DATA');

	chunk = iffStream->openChunk('CRCT'); // We don't need these
	iffStream->closeChunk('CRCT');

	chunk = iffStream->openChunk('STRT'); // Don't need these either
	iffStream->closeChunk('STRT');

	chunk = iffStream->openChunk('STNG');

	for (int i = 0; i < totalColumns; ++i) {
		String stringVal;
		chunk->readString(stringVal);

		uint32 stringCrc = stringVal.hashCode();

		tableData.put(stringCrc, stringVal);
	}

	iffStream->closeChunk('STNG');

	iffStream->closeForm(version);

	iffStream->closeForm('CSTB');
}
