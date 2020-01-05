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

		debug() << "stringCount = " << stringCount;

		VectorMap<uint32, String> id;
		VectorMap<uint32, UnicodeString> desc;

		uint32 num, key, size;

		for (int i = 0; i < stringCount; ++i) {
			num = inputFile->readInt();
			key = inputFile->readInt();

			UnicodeString description;

			uint32 len = inputFile->readInt();
			inputFile->shiftOffset(len * 2);

			description.append(reinterpret_cast<uint16*>(inputFile->getBuffer() + inputFile->getOffset() - len * 2), len);

			desc.put(num, description);

			debug() << "num = " << num
					<< " description = " << description;
		}

		for (int j = 0; j < stringCount; ++j) {
			num = inputFile->readInt();
			size = inputFile->readInt();

			inputFile->shiftOffset(size);

			String str;
			StringBuffer buffer;

			buffer.append(inputFile->getBuffer() + inputFile->getOffset() - size, size);

			str = buffer.toString();

			id.put(num, str);

			debug() << "string = " << str;
		}

		stringMap.removeAll();

		for (int i = 0; i < stringCount; ++i) {
			String idKey = id.get(i);
			uint32 num = id.elementAt(i).getKey();

			UnicodeString description = desc.get(num);

			stringMap.put(std::move(idKey), std::move(description));
		}

		return true;
	} catch (const Exception& e) {
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
