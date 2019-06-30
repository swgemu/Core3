/*
 * OnlineZoneClientMap.h
 *
 *  Created on: 11/06/2012
 *      Author: victor
 */

#ifndef ONLINEZONECLIENTMAP_H_
#define ONLINEZONECLIENTMAP_H_

#include "server/zone/ZoneClientSession.h"
#include "server/db/ServerDatabase.h"

class OnlineZoneClientMap : public HashTable<uint32, Vector<Reference<ZoneClientSession*> > >, Logger {
protected:
	HashTable<String, Reference<SortedVector<uint32>*> > ip_list;
	ReadWriteLock mutex;

public:
	OnlineZoneClientMap() {
		setLoggingName("OnlineZoneClientMap");
	}

	void addAccount(const String& ip, uint32 accountId) {
		int onlineCount = -1;

		Locker locker(&mutex);
		Reference<SortedVector<uint32>* > account_list = ip_list.get(ip);

		if (account_list == nullptr) {
			account_list = new SortedVector<uint32>();
			account_list->setNoDuplicateInsertPlan();
			account_list->put(accountId);

			ip_list.put(ip, account_list);
			onlineCount = 1;
		} else {
			account_list->put(accountId);
			onlineCount = account_list->size();
		}

		try {
			StringBuffer query;
			query << "insert into account_ips (account_id, ip, online_count) values(" << accountId << ", '" << ip << "', " << onlineCount << ");";
			ServerDatabase::instance()->executeStatement(query);
		} catch(DatabaseException& e) {
			try {
				StringBuffer query;
				query << "insert into account_ips (account_id, ip) values(" << accountId << ", '" << ip << "');";
				ServerDatabase::instance()->executeStatement(query);
			} catch(DatabaseException& e) {
				error(e.getMessage());
			}
		}

		if (onlineCount >= ConfigManager::instance()->getInt("Core3.LogOnlineCount", 3)) {
			String delim = " ";
			StringBuffer msg;

			msg << "onlineCount: " << onlineCount << " ip: " << ip << " accounts:";

			for (int i = 0;i < account_list->size(); i++) {
				msg << delim << account_list->get(i);
				delim = ", ";
			}

			error(msg.toString());
		}
	}

	void accountLoggedOut(const String& ip, uint32 accountId) {
		int onlineCount = -1;

		Locker locker(&mutex);
		Reference<SortedVector<uint32>* > account_list = ip_list.get(ip);

		if (account_list != nullptr) {
			account_list->drop(accountId);
			onlineCount = account_list->size();
		}

		try {
			StringBuffer query;
			query << "insert into account_ips (account_id, ip, logout, online_count) values(" << accountId << ", '" << ip << "', " << 1 << ", " << onlineCount << ");";
			ServerDatabase::instance()->executeStatement(query);
		} catch(DatabaseException& e) {
			try {
				StringBuffer query;
				query << "insert into account_ips (account_id, ip, logout) values(" << accountId << ", '" << ip << "', " << 1 << ");";
				ServerDatabase::instance()->executeStatement(query);
			} catch(DatabaseException& e) {
				error(e.getMessage());
			}
		}

		if (account_list != nullptr && account_list->size() == 0)
			ip_list.remove(ip);
	}

	SortedVector<uint32> getAccountsLoggedIn(const String& ip) {
		mutex.rlock();

		SortedVector<uint32> ret;
		Reference<SortedVector<uint32>*> account_list = ip_list.get(ip);

		if (account_list != nullptr)
			ret.addAll(*account_list);

		mutex.runlock();

		return ret;
	}

	int getDistinctIps() {
		return ip_list.size();
	}
};

#endif /* ONLINEZONECLIENTMAP_H_ */
