/*
				Copyright <SWGEmu>
		See file COPYING for copying conditions.*/

#ifndef CHARACTERLIST_H_
#define CHARACTERLIST_H_

#include "server/db/ServerDatabase.h"
#include "CharacterListEntry.h"

class CharacterList : public Vector<CharacterListEntry> {

	uint32 accountid;

public:
	CharacterList(uint32 id) {
		accountid = id;
		update();
	}

	~CharacterList() {

	}

	void update() {

		removeAll();

		Reference<ResultSet*> characters;

		StringBuffer query;
		query << "SELECT DISTINCT characters.character_oid, characters.account_id, characters.galaxy_id, characters.firstname, "
			<< "characters.surname, characters.race, characters.gender, characters.template, UNIX_TIMESTAMP(characters.creation_date), "
			<< "IFNULL((select galaxy.name from galaxy where galaxy.galaxy_id = characters.galaxy_id LIMIT 1), ''), "
			<< "IFNULL((SELECT b.reason FROM character_bans b WHERE b.account_id = characters.account_id AND characters.firstname = b.name AND characters.galaxy_id = b.galaxy_id AND b.expires > UNIX_TIMESTAMP() ORDER BY b.expires DESC LIMIT 1), ''), "
			<< "IFNULL((SELECT b.expires FROM character_bans b WHERE b.account_id = characters.account_id AND characters.firstname = b.name AND characters.galaxy_id = b.galaxy_id AND b.expires > UNIX_TIMESTAMP() ORDER BY b.expires DESC LIMIT 1), 0), "
			<< "IFNULL((SELECT b.issuer_id FROM character_bans b WHERE b.account_id = characters.account_id AND characters.firstname = b.name AND characters.galaxy_id = b.galaxy_id AND b.expires > UNIX_TIMESTAMP() ORDER BY b.expires DESC LIMIT 1), 0) "
			<< "FROM characters, galaxy WHERE characters.account_id = " << accountid << " "
			<< "UNION SELECT DISTINCT characters_dirty.character_oid, characters_dirty.account_id, characters_dirty.galaxy_id, "
			<< "characters_dirty.firstname, characters_dirty.surname, characters_dirty.race, characters_dirty.gender, characters_dirty.template, UNIX_TIMESTAMP(characters_dirty.creation_date), "
			<< "(select galaxy.name from galaxy where galaxy.galaxy_id = characters_dirty.galaxy_id LIMIT 1) as galaxyname, "
			<< "IFNULL((SELECT b.reason FROM character_bans b WHERE b.account_id = characters_dirty.account_id AND characters_dirty.firstname = b.name AND b.expires > UNIX_TIMESTAMP() ORDER BY b.expires DESC LIMIT 1), ''), "
			<< "IFNULL((SELECT b.expires FROM character_bans b WHERE b.account_id = characters_dirty.account_id AND characters_dirty.firstname = b.name AND b.expires > UNIX_TIMESTAMP() ORDER BY b.expires DESC LIMIT 1), 0), "
			<< "IFNULL((SELECT b.issuer_id FROM character_bans b WHERE b.account_id = characters_dirty.account_id AND characters_dirty.firstname = b.name AND b.expires > UNIX_TIMESTAMP() ORDER BY b.expires DESC LIMIT 1), 0) "
			<< "FROM characters_dirty WHERE characters_dirty.account_id = " << accountid << " ORDER BY galaxy_id;";

		try {
			characters = ServerDatabase::instance()->executeQuery(query);
		} catch (DatabaseException& e) {
			System::out << "exception caught in ChracterList query" << endl;
			System::out << e.getMessage();
		} catch (...) {
			System::out << "unknown exception caught in ChracterList query" << endl;
		}

		if (characters == NULL)
			return;

		while(characters->next()) {

			CharacterListEntry newEntry;
			newEntry.setObjectID(characters->getUnsignedLong(0));
			newEntry.setAccountID(characters->getUnsignedInt(1));
			newEntry.setGalaxyID(characters->getInt(2));
			newEntry.setFirstName(characters->getString(3));
			newEntry.setSurName(characters->getString(4));

			String race = characters->getString(7);
			newEntry.setRace(race.hashCode());
			Time createdTime(characters->getUnsignedInt(8));
			newEntry.setCreationDate(createdTime);
			newEntry.setGalaxyName(characters->getString(9));

			newEntry.setBanReason(characters->getString(10));
			Time expireTime(characters->getUnsignedInt(11));
			newEntry.setBanExpiration(expireTime);
			newEntry.setBanAdmin(characters->getUnsignedInt(12));

			add(newEntry);
		}
	}
};

#endif /*CHARACTERLIST_H_*/
