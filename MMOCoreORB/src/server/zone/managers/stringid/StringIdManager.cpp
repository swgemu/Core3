/*
 * StringIdManager.cpp
 *
 *  Created on: 25/12/2011
 *      Author: victor
 */

#include "StringIdManager.h"
#include "server/zone/templates/string/StringFile.h"
#include "server/zone/managers/templates/TemplateManager.h"
#include "server/zone/managers/templates/DataArchiveStore.h"

void StringIdManager::populateDatabase() {
	int count = 0;

	TemplateManager::instance();
	TreeArchive* treeArchive = DataArchiveStore::instance()->getTreeArchive();

	Vector<String>* files = treeArchive->getFilesAndSubDirectoryFiles("string/en");

	if (files == NULL) {
		error("string/en directory missing");

		ObjectDatabaseManager::instance()->commitLocalTransaction();
		return;
	}

	for (int i = 0; i < files->size(); ++i) {
		String file = files->get(i);

		ObjectInputStream* stream = TemplateManager::instance()->openTreFile(files->get(i));

		if (stream == NULL) {
			//error("could not open file " + files->get(i));

			continue;
		} else {
			if (stream->size() > 4) {
				//info("opening " + files->get(i), true);

				StringFile stringFile;
				if (!stringFile.load(stream)) {
					delete stream;

					error("could not parse " + files->get(i));
					continue;
				}

				file = file.replaceFirst("string/en/","");
				file = file.replaceFirst(".stf","");

				HashTable<String, UnicodeString>* hashTable = stringFile.getStringMap();

				HashTableIterator<String, UnicodeString> iterator = hashTable->iterator();

				while (iterator.hasNext()) {
					String name;
					UnicodeString value;

					iterator.getNextKeyAndValue(name, value);

					String full = "@" + file + ":" + name;

					//info("key = " + full + " value = " + value.toString(), true);

					ObjectOutputStream* data = new ObjectOutputStream();
					value.toBinaryStream(data);

					uint64 longKey = (uint64)full.hashCode();

					ObjectOutputStream* key = new ObjectOutputStream();
					TypeInfo<uint64>::toBinaryStream(&longKey, key);

					stringsDatabase->putData(key, data);
					++count;
				}

			}

			delete stream;
		}
	}

	delete files;

	info("writing to the db " + String::valueOf(count) + " strings", true);
}

StringIdManager::StringIdManager() : Logger("StringIdManager") {
	databaseManager = ObjectDatabaseManager::instance();
	bool fill = databaseManager->getDatabaseID("strings") == 0xFFFF;

	stringsDatabase = databaseManager->loadLocalDatabase("strings", true);

	if (fill || ServerCore::truncateDatabases() || ServerCore::hasArgument("reloadstrings"))
		populateDatabase();

	ObjectDatabaseManager::instance()->commitLocalTransaction();

	//info("test string = " + getStringId(String("@city/city:city_expand_body").hashCode()).toString(), true);
}

StringIdManager::~StringIdManager() {}

UnicodeString StringIdManager::getStringId(uint32 crc) {
	ObjectInputStream data;
	UnicodeString str = "";

	uint64 longKey = (uint64) crc;
	ObjectOutputStream key;
	TypeInfo<uint64>::toBinaryStream(&longKey, &key);

	if (stringsDatabase->getData(&key, &data) == 0)
		str.parseFromBinaryStream(&data);

	return str;
}
