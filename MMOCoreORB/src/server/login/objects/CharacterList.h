/*
Copyright (C) 2007 <SWGEmu>

This File is part of Core3.

This program is free software; you can redistribute
it and/or modify it under the terms of the GNU Lesser
General Public License as published by the Free Software
Foundation; either version 2 of the License,
or (at your option) any later version.

This program is distributed in the hope that it will be useful,
but WITHOUT ANY WARRANTY; without even the implied warranty of
MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.
See the GNU Lesser General Public License for
more details.

You should have received a copy of the GNU Lesser General
Public License along with this program; if not, write to
the Free Software Foundation, Inc., 51 Franklin St, Fifth Floor, Boston, MA 02110-1301 USA

Linking Engine3 statically or dynamically with other modules
is making a combined work based on Engine3.
Thus, the terms and conditions of the GNU Lesser General Public License
cover the whole combination.

In addition, as a special exception, the copyright holders of Engine3
give you permission to combine Engine3 program with free software
programs or libraries that are released under the GNU LGPL and with
code included in the standard release of Core3 under the GNU LGPL
license (or modified versions of such code, with unchanged license).
You may copy and distribute such a system following the terms of the
GNU LGPL for Engine3 and the licenses of the other code concerned,
provided that you include the source code of that other code when
and as the GNU LGPL requires distribution of source code.

Note that people who make modified versions of Engine3 are not obligated
to grant this special exception for their modified versions;
it is their choice whether to do so. The GNU Lesser General Public License
gives permission to release a modified version without this exception;
this exception also makes it possible to release a modified version
which carries forward this exception.
*/

#ifndef CHARACTERLIST_H_
#define CHARACTERLIST_H_

#include "../../db/ServerDatabase.h"

#include "server/zone/objects/player/Races.h"
#include "server/zone/objects/scene/variables/StringId.h"
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

		ResultSet* characters;

		StringBuffer query;
		query << "SELECT DISTINCT characters.character_oid, characters.account_id, characters.galaxy_id, characters.firstname, "
			<< "characters.surname, characters.race, characters.gender, characters.template, UNIX_TIMESTAMP(characters.creation_date), "
			<< "(select galaxy.name from galaxy where galaxy.galaxy_id = characters.galaxy_id LIMIT 1) as galaxyname, "
			<< "IFNULL((SELECT b.reason FROM character_bans b WHERE b.account_id = characters.account_id AND characters.firstname = b.name AND b.expires > UNIX_TIMESTAMP() ORDER BY b.expires DESC LIMIT 1), ''), "
			<< "IFNULL((SELECT b.expires FROM character_bans b WHERE b.account_id = characters.account_id AND characters.firstname = b.name AND b.expires > UNIX_TIMESTAMP() ORDER BY b.expires DESC LIMIT 1), 0), "
			<< "IFNULL((SELECT b.issuer_id FROM character_bans b WHERE b.account_id = characters.account_id AND characters.firstname = b.name AND b.expires > UNIX_TIMESTAMP() ORDER BY b.expires DESC LIMIT 1), 0) "
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

		delete characters;
	}
};

#endif /*CHARACTERLIST_H_*/
