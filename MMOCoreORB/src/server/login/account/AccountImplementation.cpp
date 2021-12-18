/*
				Copyright <SWGEmu>
		See file COPYING for copying conditions.*/


#include "../objects.h"
#include "server/login/account/Account.h"
#include "../objects/GalaxyBanEntry.h"

AccountImplementation::AccountImplementation() {
	created = 0;
	initializeTransientMembers();
}

void AccountImplementation::initializeTransientMembers() {
	active = false;
	accountID = 0;
	stationID = 0;
	adminLevel = 0;
	banExpires = 0;
	banAdmin = 0;
}

void AccountImplementation::updateFromDatabase() {
	Locker locker(_this.getReferenceUnsafeStaticCast());

	updateAccount();
	updateCharacters();
	updateGalaxyBans();
}

Reference<GalaxyAccountInfo*> AccountImplementation::getGalaxyAccountInfo(const String& galaxyName) {
	Reference<GalaxyAccountInfo*> info = galaxyAccountInfo.get(galaxyName);

	if(info == nullptr) {
		info = new GalaxyAccountInfo();

		galaxyAccountInfo.put(galaxyName, info);
	}

	return info;
}

void AccountImplementation::addGalaxyBan(GalaxyBanEntry* ban, uint32 galaxy) {
	galaxyBans.put(galaxy, ban);
}

void AccountImplementation::updateAccount() {
	StringBuffer query;
	query << "SELECT a.active, a.admin_level, "
			<< "IFNULL((SELECT b.reason FROM account_bans b WHERE b.account_id = a.account_id AND b.expires > UNIX_TIMESTAMP() ORDER BY b.expires DESC LIMIT 1), ''), "
			<< "IFNULL((SELECT b.expires FROM account_bans b WHERE b.account_id = a.account_id AND b.expires > UNIX_TIMESTAMP() ORDER BY b.expires DESC LIMIT 1), 0), "
			<< "IFNULL((SELECT b.issuer_id FROM account_bans b WHERE b.account_id = a.account_id AND b.expires > UNIX_TIMESTAMP() ORDER BY b.expires DESC LIMIT 1), 0) "
			<< "FROM accounts a WHERE a.account_id = '" << accountID << "' LIMIT 1;";

	UniqueReference<ResultSet*> result(ServerDatabase::instance()->executeQuery(query));

	if (result->next()) {
		setActive(result->getBoolean(0));
		setAdminLevel(result->getInt(1));

		setBanReason(result->getString(2));
		setBanExpires(result->getUnsignedInt(3));
		setBanAdmin(result->getUnsignedInt(4));
	}
}

void AccountImplementation::updateCharacters() {
	characterList = new CharacterList(getAccountID(), getUsername());
}

void AccountImplementation::updateGalaxyBans() {
	StringBuffer query;
	query << "SELECT * FROM galaxy_bans as gb WHERE account_id=" << getAccountID() << " and expires > UNIX_TIMESTAMP()";

	UniqueReference<ResultSet*> results(ServerDatabase::instance()->executeQuery(query));

	galaxyBans.removeAll();

	while (results->next()) {
		Reference<GalaxyBanEntry*> entry = new GalaxyBanEntry();

		entry->setAccountID(results->getUnsignedInt(1));
		entry->setBanAdmin(results->getUnsignedInt(2));
		entry->setGalaxyID(results->getUnsignedInt(3));
		Time bancreated(results->getUnsignedInt(4));
		entry->setCreationDate(bancreated);

		Time banexpires(results->getUnsignedInt(5));
		entry->setBanExpiration(banexpires);

		entry->setBanReason(results->getString(6));

		galaxyBans.put(entry->getGalaxyID(), entry);
	}
}

bool AccountImplementation::isBanned() const {
	return banExpires > time(0);
}

const GalaxyBanEntry* AccountImplementation::getGalaxyBan(const uint32 galaxy) const {
	return galaxyBans.get(galaxy);
}

GalaxyBanEntry* AccountImplementation::getGalaxyBan(const uint32 galaxy) {
	return galaxyBans.get(galaxy);
}

const CharacterListEntry* AccountImplementation::getCharacterBan(const uint32 galaxy, const String& name) const {
	for (int i = 0; i < characterList->size(); ++i) {
		const CharacterListEntry* entry = &characterList->get(i);

		if (entry->getFirstName() == name &&
				entry->getGalaxyID() == galaxy &&
				entry->isBanned())
			return entry;
	}

	return nullptr;
}

CharacterListEntry* AccountImplementation::getCharacterBan(const uint32 galaxy, const String& name) {
	for (int i = 0; i < characterList->size(); ++i) {
		CharacterListEntry* entry = &characterList->get(i);

		if (entry->getFirstName() == name &&
				entry->getGalaxyID() == galaxy &&
				entry->isBanned())
			return entry;
	}

	return nullptr;
}

CharacterList* AccountImplementation::getCharacterList() {
	if (characterList == nullptr)
		updateCharacters();

	return characterList;
}

uint32 AccountImplementation::getAgeInDays() const {
	if (created == 0) {
		throw Exception("Account Object has created set as 0 in getAgeInDays");
	}

	Time currentTime;
	Time createdTime(getTimeCreated());
	uint32 ageSecs = currentTime.getTime() - createdTime.getTime();
	return ageSecs / 24 / 60 / 60;
}

bool AccountImplementation::isSqlLoaded() const {
	return (accountID || stationID || adminLevel || created);
}
