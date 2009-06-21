/*
 Copyright (C) 2009 <SWGEmu>

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

Contributed by Kyle
 */

#ifndef VBULLETINAUTHENTICATION_H_
#define VBULLETINAUTHENTICATION_H_

#include "Authentication.h"

class VBulletinAuthentication : Authentication {

public:
	String host;
	uint16 port;
	String schemaname;
	String user;
	String pass;
	String bannedGroupID;
	String standardGroupID;
	String userTable;
	String bannedTable;
	String newActivationTable;

public:
	VBulletinAuthentication() {

		host = "127.0.0.1";
		port = 3306;
		schemaname = "swgemu";
		user = "swgemu";
		pass = "123456";
		bannedGroupID = "8";
		standardGroupID = "2";
		userTable = "vb3_users";
		bannedTable = "vb3_bannedusers";
		newActivationTable = "vb3_useractivation";

		configPath = "config/VBulletinAuthentication.lua";
	}

	~VBulletinAuthentication() {

	}

	bool loadConfigData() {

		if (!loadConfigFile())
			return false;

		host = getGlobalString("DBHost");
		port = getGlobalShort("DBPort");
		schemaname = getGlobalString("DBName");
		user = getGlobalString("DBUser");
		pass = getGlobalString("DBPass");
		bannedGroupID = getGlobalString("BannedGroupID");
		standardGroupID = getGlobalString("StandardGroupID");
		userTable = getGlobalString("UserTable");
		bannedTable = getGlobalString("BannedTable");
		newActivationTable = getGlobalString("NewActivationTable");

		return true;
	}

	int authenticate() {

		try {
			StringBuffer query, query2;

			query << "SELECT "
				  << ForumsDatabase::userTable() << ".userid, "
				  << ForumsDatabase::userTable() << ".usergroupid, "
				  << ForumsDatabase::userTable() << ".username, "
				  << ForumsDatabase::userTable() << ".password, "
				  << ForumsDatabase::userTable() << ".salt, "
				  << "(SELECT userid FROM "
				  << ForumsDatabase::bannedTable()
			      << " WHERE userid = (SELECT "
			      << ForumsDatabase::userTable() << ".userid "
			      << "FROM " << ForumsDatabase::userTable()
			      << " WHERE username = \'" << username << "\' LIMIT 1 ) LIMIT 1 ) as banned, "
				  << "(SELECT userid FROM "
				  << ForumsDatabase::newActivationTable()
			      << " WHERE userid = (SELECT "
			      << ForumsDatabase::userTable() << ".userid "
			      << "FROM " << ForumsDatabase::userTable()
			      << " WHERE username = \'" << username << "\' LIMIT 1 ) LIMIT 1 ) as newuser "
				  << " FROM " << ForumsDatabase::userTable()
			      << " WHERE "
			      << ForumsDatabase::userTable() << ".username = \'" << username << "\'";

			ResultSet* res = ForumsDatabase::instance()->executeQuery(query);

			if (res->next()){
				forumUserID = res->getString(0);
				forumUserGroupID = res->getString(1);
				forumUser = res->getString(2);
				forumPass = res->getString(3);
				forumSalt = res->getString(4);

				try {
					String test = res->getString(5);
					isBanned = true;
				} catch (...) {
					isBanned = false;
				}

				if (isBanned){
					delete res;
					return ACCOUNTBANNED;
				}


				try {
					String test = res->getString(6);
					isBanned = true;
				} catch (...) {
					isBanned = false;
				}

				if (isBanned){
					delete res;
					return ACCOUNTNOTACTIVE;
				}

				String forSalt = forumSalt;
				MySqlDatabase::escapeString(forSalt);

				query2 << "SELECT MD5(CONCAT(MD5(\'" + password + "\'), \'" + forSalt + "\'))";
				ResultSet* res2 = ForumsDatabase::instance()->executeQuery(query2);

				if (res2->next()){
					String tempPass = res2->getString(0);

					if (tempPass == forumPass){
						delete res;
						delete res2;
						return ACCOUNTOK; // Good Account
					} else {
						return ACCOUNTBADPW; // Bad Password
					}
				}
				delete res2;
			}

			delete res;

			return ACCOUNTINUSE;
		} catch(DatabaseException& e) {
			System::out << e.getMessage() << endl;
			return SERVERERROR;
		}
	}
};

#endif /* VBULLETINAUTHENTICATION_H_ */
