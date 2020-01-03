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
#include "server/ServerCore.h"

class OnlineZoneClientMap : public HashTable<uint32, Vector<Reference<ZoneClientSession*> > >, private Logger {
protected:
	HashTable<String, Reference<SortedVector<uint32>*> > ip_list;
	ReadWriteLock mutex;

	using self_table_type = HashTable<uint32, Vector<Reference<ZoneClientSession*> > >;

public:
	OnlineZoneClientMap() {
		setLoggingName("OnlineZoneClientMap");
	}

	void accountLoggedIn(const String& ip, uint32 accountId, int galaxyId) {
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

		insertLogEntry(accountId, galaxyId, ip, 0, onlineCount);

		if (onlineCount >= ConfigManager::instance()->getInt("Core3.LogOnlineCount", 3)) {
			String delim = " ";
			StringBuffer msg;

			msg << "onlineCount: " << onlineCount << " ip: " << ip << " accounts:";

			for (int i = 0;i < account_list->size(); i++) {
				msg << delim << account_list->get(i);
				delim = ", ";
			}

			info(msg.toString(), true);
		}
	}

	void accountLoggedOut(const String& ip, uint32 accountId, int galaxyId) {
		int onlineCount = -1;

		Locker locker(&mutex);
		Reference<SortedVector<uint32>* > account_list = ip_list.get(ip);

		if (account_list != nullptr) {
			account_list->drop(accountId);
			onlineCount = account_list->size();
		}

		insertLogEntry(accountId, galaxyId, ip, 1, onlineCount);

		if (account_list != nullptr && account_list->size() == 0)
			ip_list.remove(ip);
	}

	SortedVector<uint32> getAccountsLoggedIn(const String& ip) {
		ReadLocker locker(&mutex);

		SortedVector<uint32> ret;
		Reference<SortedVector<uint32>*> account_list = ip_list.get(ip);

		if (account_list != nullptr)
			ret.addAll(*account_list);

		return ret;
	}

	int getDistinctIps() const {
		return ip_list.size();
	}

private:
	void insertLogEntry(uint32 accountId, int galaxyId, const String& ipAddress, int logout, int onlineCount) {
		StringBuffer query;

		if (ServerCore::getSchemaVersion() >= 1001)
			query << "insert into account_ips (account_id, galaxy_id, ip, logout, online_count) values"
				<< "(" << accountId
				<< ", " << galaxyId
				<< ", '" << ipAddress << "'"
				<< ", " << logout
				<< ", " << onlineCount
				<< ");";
		else
			query << "insert into account_ips (account_id, ip, logout) values"
				<< "(" << accountId
				<< ", '" << ipAddress << "'"
				<< ", " << logout
				<< ");";

		try {
			ServerDatabase::instance()->executeStatement(query);
		} catch (const DatabaseException& e) {
			error(e.getMessage());
		}
	}
};

#endif /* ONLINEZONECLIENTMAP_H_ */
