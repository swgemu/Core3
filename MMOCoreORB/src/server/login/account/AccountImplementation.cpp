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


#include "../objects.h"
#include "Account.h"
#include "AccountManager.h"
#include "../objects/GalaxyBanEntry.h"

AccountImplementation::AccountImplementation() {
}

void AccountImplementation::updateFromDatabase() {

	updateAccount();
	updateCharacters();
	updateGalaxyBans();

}

void AccountImplementation::updateAccount() {
	StringBuffer query;
	query << "SELECT a.active, a.admin_level, "
			<< "IFNULL((SELECT b.reason FROM account_bans b WHERE b.account_id = a.account_id AND b.expires > UNIX_TIMESTAMP() ORDER BY b.expires DESC LIMIT 1), ''), "
			<< "IFNULL((SELECT b.expires FROM account_bans b WHERE b.account_id = a.account_id AND b.expires > UNIX_TIMESTAMP() ORDER BY b.expires DESC LIMIT 1), 0), "
			<< "IFNULL((SELECT b.issuer_id FROM account_bans b WHERE b.account_id = a.account_id AND b.expires > UNIX_TIMESTAMP() ORDER BY b.expires DESC LIMIT 1), 0) "
			<< "FROM accounts a WHERE a.account_id = '" << accountID << "' LIMIT 1;";

	ResultSet* result = ServerDatabase::instance()->executeQuery(query);

	if (result->next()) {

		setActive(result->getBoolean(0));
		setAdminLevel(result->getInt(1));

		setBanReason(result->getString(2));
		setBanExpires(result->getUnsignedInt(3));
		setBanAdmin(result->getUnsignedInt(4));
	}

	delete result;
	result = NULL;
}

void AccountImplementation::updateCharacters() {
	characterList = new CharacterList(getAccountID());
}

void AccountImplementation::updateGalaxyBans() {
	StringBuffer query;
	query << "SELECT *, (SELECT g.name FROM galaxy as g WHERE g.galaxy_id = gb.galaxy_id LIMIT 1) FROM galaxy_bans as gb WHERE account_id=" << getAccountID() << " and expires > UNIX_TIMESTAMP()";

	ResultSet* results = ServerDatabase::instance()->executeQuery(query);

	galaxyBans.removeAll();

	while(results->next()) {
		Reference<GalaxyBanEntry*> entry = new GalaxyBanEntry();

		entry->setAccountID(results->getUnsignedInt(1));
		entry->setBanAdmin(results->getUnsignedInt(2));
		entry->setGalaxyID(results->getUnsignedInt(3));
		Time bancreated(results->getUnsignedInt(4));
		entry->setCreationDate(bancreated);

		Time banexpires(results->getUnsignedInt(5));
		entry->setBanExpiration(banexpires);

		entry->setBanReason(results->getString(6));
		String name = results->getString(7);

		galaxyBans.put(name, entry);
	}

	delete results;
}

bool AccountImplementation::isBanned() {
	return banExpires > time(0);
}

GalaxyBanEntry* AccountImplementation::getGalaxyBan(const String& galaxy) {
	if(galaxyBans.contains(galaxy))
		return galaxyBans.get(galaxy);

	return NULL;
}

CharacterListEntry* AccountImplementation::getCharacterBan(const String& name) {

	if(!characterList->contains(name))
		return NULL;

	CharacterListEntry* entry = &characterList->get(name);

	if(entry->isBanned())
		return entry;

	return NULL;
}

CharacterList* AccountImplementation::getCharacterList() {
	return characterList;
}
