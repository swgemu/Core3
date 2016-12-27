/*
				Copyright <SWGEmu>
		See file COPYING for copying conditions.*/

#ifndef GALAXYLIST_H_
#define GALAXYLIST_H_

#include "server/db/ServerDatabase.h"

class GalaxyList {
	ResultSet* galaxies;

public:
	GalaxyList() {
		StringBuffer query;
		query << "SELECT * FROM galaxy";

		galaxies = ServerDatabase::instance()->executeQuery(query);
	}

	~GalaxyList() {
		if (galaxies != NULL)
			delete galaxies;
	}

	bool next() {
		return galaxies->next();
	}

	uint32 getGalaxyID() {
		return galaxies->getUnsignedInt(0);
	}

	void getGalaxyName(String& name) {
		name = galaxies->getString(1);
	}

	void getGalaxyAddress(String& address) {
		address = galaxies->getString(2);
	}

	uint16 getGalaxyPort() {
		return galaxies->getUnsignedInt(3);
	}

	uint16 getGalaxyPingPort() {
		return galaxies->getUnsignedInt(4);
	}

	uint32 getGalaxyPopulation() {
		return galaxies->getUnsignedInt(5);
	}
	
	inline int size() {
		return galaxies->size();
	} 
	
};

#endif /*GALAXYLIST_H_*/
