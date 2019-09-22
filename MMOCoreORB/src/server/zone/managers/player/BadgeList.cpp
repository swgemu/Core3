#include "BadgeList.h"
#include "conf/ConfigManager.h"
#include "templates/datatables/DataTableIff.h"
#include "templates/manager/DataArchiveStore.h"

BadgeList::BadgeList() : Logger("BadgeList") {
	setLogLevel(Logger::INFO);

	badges.setNullValue(nullptr);
	names.setNullValue(nullptr);

	loadData();
}
BadgeList::~BadgeList() {
	for (int i = 0; i < badges.size(); i++) {
		const Badge* badge = badges.get(i);
		if (badge != nullptr) {
			delete badge;
		}
	}
}

void BadgeList::loadData() {
	debug("Loading badges.");

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

	UniqueReference<IffStream*> iffStream(DataArchiveStore::instance()->openIffFile("datatables/badge/badge_map.iff"));

	if (iffStream == nullptr) {
		error() << "Couldn't load badge map.";
		return;
	}

	DataTableIff dtiff;
	dtiff.readObject(iffStream);

	int i;
	for (i = 0; i < dtiff.getTotalRows(); ++i) {
		Badge* badge = new Badge();
		DataTableRow* row = dtiff.getRow(i);

		badge->readFromRow(row);

		debug() << "Adding badge " <<
			badge->getKey() << " " << badge->getIndex();

		add(badge);
	}

	info(true) << "Loaded " << i << " badges.";
}

void BadgeList::add(Badge* badge) {
	if (badge == nullptr) return;

	badges.put(badge->getIndex(), badge);
	names.put(badge->getKey(), badge);
}
