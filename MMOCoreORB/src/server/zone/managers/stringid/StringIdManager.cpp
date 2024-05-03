/*
 * StringIdManager.cpp
 *
 *  Created on: 25/12/2011
 *      Author: victor
 */

#include "StringIdManager.h"
#include "server/ServerCore.h"
#include "templates/string/StringFile.h"
#include "templates/manager/TemplateManager.h"
#include "templates/manager/DataArchiveStore.h"
#include "tre3/TreeArchive.h"
#include "conf/ConfigManager.h"

void StringIdManager::populateDatabase() {
	int count = 0;

	TemplateManager::instance();
	const TreeArchive* treeArchive = DataArchiveStore::instance()->getTreeArchive();

	UniqueReference<Vector<String>*> files(treeArchive->getFilesAndSubDirectoryFiles("string/en"));

	if (files == nullptr) {
		error("string/en directory missing");

		ObjectDatabaseManager::instance()->commitLocalTransaction();
		return;
	}

	for (int i = 0; i < files->size(); ++i) {
		String file = files->get(i);

		UniqueReference<ObjectInputStream*> stream(TemplateManager::instance()->openTreFile(files->get(i)));

		if (stream == nullptr) {
			debug() << "could not open file " << files->get(i);

			continue;
		} else {
			if (stream->size() > 4) {
				debug() << "opening " << files->get(i);

				StringFile stringFile;
				if (!stringFile.load(stream)) {
					error("could not parse " + files->get(i));

					continue;
				}

				file = file.replaceFirst("string/en/","");
				file = file.replaceFirst(".stf","");

				const auto& hashTable = stringFile.getStringMap();

				auto iterator = hashTable.iterator();

				while (iterator.hasNext()) {
					String name;
					UnicodeString value;

					iterator.getNextKeyAndValue(name, value);

					String full = "@" + file + ":" + name;

					debug() << "key = " << full << " value = " << value;

					ObjectOutputStream* data = new ObjectOutputStream();
					value.toBinaryStream(data);

					uint64 longKey = (uint64)full.hashCode();

					ObjectOutputStream* key = new ObjectOutputStream();
					TypeInfo<uint64>::toBinaryStream(&longKey, key);

					stringsDatabase->putData(key, data);
					++count;
				}

			}
		}
	}

	info(true) << "writing to the db " << count  << " strings";
}

StringIdManager::StringIdManager() : Logger("StringIdManager") {
	databaseManager = ObjectDatabaseManager::instance();
	bool fill = databaseManager->getDatabaseID("strings") == 0xFFFF;
	bool autoReload = ConfigManager::instance()->getBool("Core3.TreManager.ReloadStrings", false);

	stringsDatabase = databaseManager->loadLocalDatabase("strings", true);

	if (autoReload || fill || ServerCore::truncateDatabases() || ServerCore::hasArgument("reloadstrings")) {
		populateDatabase();
	}

	ObjectDatabaseManager::instance()->commitLocalTransaction();
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

UnicodeString StringIdManager::getStringId(const StringId& id) {
	return getStringId(id.getFullPath().hashCode());
}
