/*
				Copyright <SWGEmu>
		See file COPYING for copying conditions.*/

#ifndef STRINGID_H_
#define STRINGID_H_

#include "engine/engine.h"

class StringId : public Serializable {
	String file;
	String stringID;

	UnicodeString customName;

private:
	inline void addSerializableVariables();

public:
	StringId();
	StringId(const StringId& id);
	StringId(const String& fullPath);
	StringId(const String& fil, const String& stringId);
	StringId(const UnicodeString& custom);

	void getFullPath(String& str) {
		str = "@" + file + ":" + stringID;
	}

	String& getFile() {
		return file;
	}

	String& getStringID() {
		return stringID;
	}

	UnicodeString& getCustomString() {
		return customName;
	}

	void setCustomString(const UnicodeString& custom) {
		customName = custom;
	}

	void setStringId(const String& fullPath) {
		if (fullPath.isEmpty())
			return;

		if (fullPath.charAt(0) == '@') {
			StringTokenizer tokenizer(fullPath.subString(1));
			tokenizer.setDelimeter(":");

			tokenizer.getStringToken(file);
			tokenizer.getStringToken(stringID);
		}
	}

	void parse(Message* message) {
		message->parseAscii(file);
		message->parseInt();
		message->parseAscii(stringID);
		message->parseUnicode(customName);
	}

};


#endif /* STRINGID_H_ */
