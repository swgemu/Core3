/*
 * StringFile.h
 *
 *  Created on: 25/12/2011
 *      Author: victor
 */

#ifndef STRINGFILE_H_
#define STRINGFILE_H_

#include "engine/log/Logger.h"
#include "system/lang.h"
#include "system/lang/String.h"
#include "system/lang/UnicodeString.h"
#include "system/util/HashTable.h"

namespace sys {
namespace io {
class ObjectInputStream;
}  // namespace io
}  // namespace sys

class StringFile : public Logger {
	HashTable<String, UnicodeString> stringMap;

public:
	StringFile();
	~StringFile();

	bool load(ObjectInputStream* inputFile);

	HashTable<String, UnicodeString>* getStringMap() {
		return &stringMap;
	}

	UnicodeString getValue(const String& id) {
		return stringMap.get(id);
	}

protected:
	bool checkHeader(ObjectInputStream* inputFile);
};

#endif /* STRINGFILE_H_ */
