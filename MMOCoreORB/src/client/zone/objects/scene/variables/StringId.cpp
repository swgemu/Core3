/*
				Copyright <SWGEmu>
		See file COPYING for copying conditions.*/

#include "StringId.h"

StringId::StringId() : Serializable() {
	addSerializableVariables();
}

StringId::StringId(const StringId& id) : Object(), Serializable() {
	file = id.file;
	stringID = id.stringID;

	customName = id.customName;

	addSerializableVariables();
}

StringId::StringId(const String& fullPath) : Serializable() {
	setStringId(fullPath);

	addSerializableVariables();
}

StringId::StringId(const String& fil, const String& stringId) : Serializable() {
	file = fil;
	stringID = stringId;

	addSerializableVariables();
}

StringId::StringId(const UnicodeString& custom) : Serializable() {
	customName = custom;

	addSerializableVariables();
}

void StringId::addSerializableVariables() {
	addSerializableVariable("file", &file);
	addSerializableVariable("stringID", &stringID);
	addSerializableVariable("customName", &customName);
}
