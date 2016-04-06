#include "BadgeList.h"
#include "conf/ConfigManager.h"
#include "templates/datatables/DataTableIff.h"
#include "templates/manager/DataArchiveStore.h"

BadgeList::BadgeList() : Logger("BadgeList") {
	badges.setNullValue(NULL);
	names.setNullValue(NULL);
	loadData();
}
BadgeList::~BadgeList() {
	for (int i = 0; i < badges.size(); i++) {
		const Badge* badge = badges.get(i);
		if (badge != NULL) {
			delete badge;
		}
	}
}

void BadgeList::loadData() {
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
		add(badge);
	}

	info("Loaded " + String::valueOf(i) + " badges.", true);

	delete iffStream;
}

void BadgeList::add(Badge* badge) {
	if (badge == NULL) return;

	badges.put(badge->getIndex(), badge);
	names.put(badge->getKey(), badge);
}
