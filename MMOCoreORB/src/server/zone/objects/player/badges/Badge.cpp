/*
				Copyright <SWGEmu>
		See file COPYING for copying conditions.*/

#include "Badge.h"

Badge::Badge() :
	index(-1),
	category(-1),
	show(-1),
	type(UNKNOWN),
	hasMusic(false)
{}

void Badge::readFromRow(DataTableRow* row) {
	if (row == NULL)
		return;

	const int INDEX = 0;
	const int KEY = 1;
	const int MUSIC = 2;
	const int CATEGORY = 3;
	const int SHOW = 4;
	const int TYPE = 5;

	row->getCell(INDEX)->getValue(index);
	row->getCell(KEY)->getValue(key);
	row->getCell(MUSIC)->getValue(music);
	row->getCell(CATEGORY)->getValue(category);
	row->getCell(SHOW)->getValue(show);
	row->getCell(TYPE)->getValue(typeString);

	type = getTypeFromString(typeString);
	hasMusic = music != "NONE";
}


uint8 Badge::getTypeFromString(const String& typeString) {
	if (typeString == "accumulation") {
		return ACCUMULATION;
	} else if (typeString == "interest") {
		return INTEREST;
	} else if (typeString.contains("exploration")) {
		return EXPLORATION;
	} else if (typeString == "master") {
		return MASTER;
	} else if (typeString == "events") {
		return EVENT;
	} else if (typeString == "content") {
		return CONTENT;
	} else {
		StringBuffer buffer;
		buffer << "Unknown badge type ";
		buffer << typeString;
		buffer << ".";
		Logger::console.error(buffer.toString());
		assert(0 && "Unknown badge type in Badge::getTypeFromString.");

		throw Exception(buffer.toString());
	}
}
