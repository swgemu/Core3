/*
				Copyright <SWGEmu>
		See file COPYING for copying conditions.*/

#ifndef STRINGLIST_H_
#define STRINGLIST_H_

#include "ObjectControllerMessage.h"

class StringList : public ObjectControllerMessage {
	uint8 optionCount;

public:

	StringList(CreatureObject* creo) : ObjectControllerMessage(creo->getObjectID(), 0x0B, 0xE0) {
		optionCount = 0;
		insertByte(0);
	}

	void insertOption(const String& file, const String& str) {
		insertUnicode(UnicodeString("@" + file + ":" + str));
		updateOptionCount();
	}

	void insertOption(const String& option) {
		insertUnicode(UnicodeString(option));
		updateOptionCount();
	}

	void insertOption(const UnicodeString& option) {
		insertUnicode(option);
		updateOptionCount();
	}

	void updateOptionCount() {
		insertByte(30, ++optionCount);
	}

	int getOptionCount() {
		return optionCount;
	}
};

#endif
