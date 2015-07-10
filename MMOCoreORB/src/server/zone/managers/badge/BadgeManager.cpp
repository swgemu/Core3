#include "BadgeManager.h"
#include "server/zone/managers/templates/TemplateManager.h"
//#include "server/zone/templates/datatables/DataTableIff.h"
#include "server/zone/templates/datatables/DataTableIff.h"
#include "server/zone/managers/templates/DataArchiveStore.h"
#include "server/conf/ConfigManager.h"

BadgeManager::BadgeManager() : Logger("BadgeManager") {
	loadData();
}

void BadgeManager::loadData() {
	info("Loading badges.");



	// previsouly I was hopeing to use the Templatemanager 
	// but that ends up to be a cyclic dependncy with DirectorManager being involed..
	// so I had to duplicate a bit of code here.
	//ConfigManager::instance()->loadConfigData();
	String path = ConfigManager::instance()->getTrePath();

	if (path.length() <= 0) {
		error("trepath is empty");
		return;
	}

	Vector<String> treFilesToLoad = ConfigManager::instance()->getTreFiles();

	if (treFilesToLoad.size() == 0) {
		error("no tre files to load.");
		return;
	}

	DataArchiveStore::instance()->loadTres(path, treFilesToLoad);

	IffStream* iffStream = DataArchiveStore::instance()->openIffFile("datatables/badge/badge_map.iff");

	if (iffStream == NULL) {
		info("Couldn't load badge map.", true);
		return;
	}

	DataTableIff dtiff;
	dtiff.readObject(iffStream);

	int i;
	for (i = 0; i < dtiff.getTotalRows(); ++i) {

		Badge* badge = new Badge();
		DataTableRow* row = dtiff.getRow(i);

		badge->readFromRow(row);
		info("Adding badge " + badge->getKey() + " " + String::valueOf(badge->getIndex()));
		list.add(badge);
	}

	info("Loaded " + String::valueOf(i) + " badges.", true);

	delete iffStream;
}


const Badge* BadgeManager::get(const uint32 badgeId) {
	return list.get(badgeId);
}

const Badge* BadgeManager::get(const String& key) {
	return list.get(key);
}

VectorMap<unsigned int, const Badge*>* BadgeManager::getMap() {
	return list.getMap();
}
