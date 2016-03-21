/*
 * StringFile.cpp
 *
 *  Created on: 25/12/2011
 *      Author: victor
 */

#include "StringFile.h"

StringFile::StringFile() {
	setLoggingName("StringFile");
}

StringFile::~StringFile() {

}

bool StringFile::load(ObjectInputStream* inputFile) {
	try {
		if (!checkHeader(inputFile))
			return false;

		byte unknown = inputFile->readByte();
		uint32 unknown1 = inputFile->readInt();
		uint32 stringCount = inputFile->readInt();

		//info("stringCount = " + String::valueOf(stringCount), true);

		VectorMap<uint32, String> id;
		VectorMap<uint32, UnicodeString> desc;

		uint32 num, key, size;

		for (int i = 0; i < stringCount; ++i) {
			num = inputFile->readInt();
			key = inputFile->readInt();
			//size = inputFile->readInt();

			UnicodeString description;

			uint32 len = inputFile->readInt();
			inputFile->shiftOffset(len * 2);

			description.append((unsigned short*) (inputFile->getBuffer() + inputFile->getOffset() - len * 2), len);

			//desc.setElementAt(num - 1, description);
			desc.put(num, description);

			//info("num = " + String::valueOf(num), true);
			//info("description = " + description.toString(), true);
		}

		for (int j = 0; j < stringCount; ++j) {
			num = inputFile->readInt();
			size = inputFile->readInt();

			inputFile->shiftOffset(size);

			String str;
			StringBuffer buffer;

			buffer.append(inputFile->getBuffer() + inputFile->getOffset() - size, size);

			str = buffer.toString();

			//id.setElementAt(num - 1, str);
			id.put(num, str);

			//info("string = " + str, true);
		}

		stringMap.removeAll();

		for (int i = 0; i < stringCount; ++i) {
			String idKey = id.get(i);
			uint32 num = id.elementAt(i).getKey();

			UnicodeString description = desc.get(num);

			stringMap.put(idKey, description);
		}

		return true;
	} catch (Exception& e) {
		error("could not parse string file");
		e.printStackTrace();
	}

	return false;
}

bool StringFile::checkHeader(ObjectInputStream* inputFile) {
	uint16 magic = inputFile->readInt();

	if (magic != 0xABCD)
		return false;

	return true;
}
