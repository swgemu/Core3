/*
				Copyright <SWGEmu>
		See file COPYING for copying conditions.*/

#ifndef GALAXYLIST_H_
#define GALAXYLIST_H_

#include "server/db/ServerDatabase.h"

//#define USE_RANDOM_EXTRA_PORTS

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

	uint16 getRandomGalaxyPort() {
#ifndef USE_RANDOM_EXTRA_PORTS
		return getGalaxyPort();
#else
		auto mainPort = getGalaxyPort();
		auto extraPorts = getExtraPorts();

		int ports[256];
		ports[0] = mainPort;

		int count = 1;

		StringTokenizer tokenizer(extraPorts);
		tokenizer.setDelimiter(",");

		while (tokenizer.hasMoreTokens() && count < 256) {
			ports[count++] = tokenizer.getIntToken();
		}

		uint16 port = (uint16) ports[System::random(count - 1)];

		return port;
#endif
	}

	uint16 getGalaxyPingPort() {
		return galaxies->getUnsignedInt(4);
	}

	uint32 getGalaxyPopulation() {
		return galaxies->getUnsignedInt(5);
	}

	String getExtraPorts() {
#ifdef USE_RANDOM_EXTRA_PORTS
		return galaxies->getString(6);
#else
		return "";
#endif
	}

	inline int size() {
		return galaxies->size();
	} 
	
};

#endif /*GALAXYLIST_H_*/
