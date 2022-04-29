/*
				Copyright <SWGEmu>
		See file COPYING for copying conditions.*/

#ifndef GALAXYLIST_H_
#define GALAXYLIST_H_

#include "server/db/ServerDatabase.h"
#include "conf/ConfigManager.h"

// #define USE_RANDOM_EXTRA_PORTS

class Galaxy {
	uint32 id = 0;
	String name;
	String address;
	uint32 port = 0;
	uint32 pingPort = 0;
	uint32 population = 0;
#ifdef USE_RANDOM_EXTRA_PORTS
	Vector<uint32> extraPorts;
#endif // USE_RANDOM_EXTRA_PORTS
public:
	Galaxy() = default;

	Galaxy(ResultSet *result) {
		id = result->getUnsignedInt(0);
		name = result->getString(1);
		address = result->getString(2);
		port = result->getUnsignedInt(3);
		pingPort = result->getUnsignedInt(4);
		population = result->getUnsignedInt(5);
#ifdef USE_RANDOM_EXTRA_PORTS
		extraPorts.add(port);

		try {
			String extraPortStrings = result->getString(6);

			if (!extraPortStrings.isEmpty()) {
				StringTokenizer tokenizer(extraPortStrings);
				tokenizer.setDelimiter(",");

				while (tokenizer.hasMoreTokens() && extraPorts.size() < 256) {
					try {
						uint32 newPort = tokenizer.getIntToken();

						if (newPort != 0)
							extraPorts.add(newPort);
					} catch (Exception e) {
						// Do nothing
					}
				}
			}
		} catch (Exception e) {
			// Do Nothing
		}
#endif // USE_RANDOM_EXTRA_PORTS
	}

	uint32 getID() const {
		return id;
	}

	const String& getName() const {
		return name;
	}

	const String& getAddress() const {
		return address;
	}

	uint32 getPort() const {
		return port;
	}

	uint32 getPingPort() const {
		return pingPort;
	}

	uint32 getPopulation() const {
		return population;
	}

	uint16 getRandomPort() const {
#ifdef USE_RANDOM_EXTRA_PORTS
		const static auto type = ConfigManager::instance()->getInt("Core3.ZonePortsBalancer", 1);

		if (type == 1) {
			static AtomicInteger roundRobin;

			return (uint16)extraPorts.get(roundRobin.increment() % extraPorts.size());
		} else {
			return (uint16)extraPorts.get(System::random(extraPorts.size() - 1));
		}
#else // USE_RANDOM_EXTRA_PORTS
		return port;
#endif // USE_RANDOM_EXTRA_PORTS
	}

	bool toBinaryStream(ObjectOutputStream* stream) {
		return false;
	}

	bool parseFromBinaryStream(ObjectInputStream* stream) {
		return false;
	}

	String toString() const {
		StringBuffer buf;

		buf << "Galaxy("
			<< "id: " << id
			<< ", name: " << name
			<< ", address: " << address
			<< ", port: " << port
			<< ", pingPort: " << pingPort
			<< ", population: " << population
		;
#ifdef USE_RANDOM_EXTRA_PORTS

		buf << ", extraPorts:";

		for (auto port : extraPorts)
			buf << " " << port;
#endif
		buf << ")";

		return buf.toString();
	}
};

class GalaxyList {
	Vector<Galaxy> galaxies;
	Galaxy current;
	int curIdx = 0;

public:
	GalaxyList(uint32 accountid) {
		StringBuffer query;
		query << "SELECT g.* FROM `galaxy` g"
			<< " LEFT OUTER JOIN `galaxy_access` ga ON ga.`galaxy_id` = g.`galaxy_id` AND (ga.`account_id` = 0 OR ga.`account_id` = " << accountid << ")"
			<< " WHERE (ga.`account_id` != 0 AND (ga.`expires` IS NULL OR ga.`expires` > NOW()))"
			<< " OR NOT EXISTS (SELECT * FROM `galaxy_access` gb WHERE gb.`galaxy_id` = g.`galaxy_id`)"
			<< " ORDER BY g.`galaxy_id`"
			;

		UniqueReference<ResultSet*> results(ServerDatabase::instance()->executeQuery(query));

		if (results == nullptr)
			return;

		while (results->next()) {
			galaxies.add(Galaxy(results));
		}

		curIdx = 0;
	}

	bool next() {
		if (curIdx < galaxies.size()) {
			current = galaxies.get(curIdx++);
			return true;
		}

		return false;
	}

	bool isAllowed(uint32 galaxyID) const {
		for (auto& galaxy : galaxies) {
			if (galaxy.getID() == galaxyID)
				return true;
		}

		return false;
	}

	uint32 getID() const {
		return current.getID();
	}

	const String& getName() const {
		return current.getName();
	}

	const String& getAddress() const {
		return current.getAddress();
	}

	uint16 getPort() const {
		return current.getPort();
	}

	uint16 getRandomPort() const {
		return current.getRandomPort();
	}

	uint16 getPingPort() const {
		return current.getPingPort();
	}

	uint32 getPopulation() const {
		return current.getPopulation();
	}

	String toString() const {
		return current.toString();
	}

	inline int size() const {
		return galaxies.size();
	}
};

#endif /*GALAXYLIST_H_*/
