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

#ifndef ACCOUNT_H_
#define ACCOUNT_H_

#include "../../db/ServerDatabase.h"

#include "../LoginClient.h"
#include "../objects.h"

#include "GalaxyList.h"
#include "CharacterList.h"

class Account {
	uint32 stationID;

	string username;
	string password;

public:
	int accountID;

	Account(Packet* pack) {
		AccountVersionMessage::parse(pack, username, password);
		MySqlDatabase::escapeString(username);
		MySqlDatabase::escapeString(password);
	}
	
	bool validate() {
		string query = "SELECT * FROM account WHERE username = \'" + username +
					   "\' and password = sha1(\'" + password + "\')";
					   
		ResultSet* res = ServerDatabase::instance()->executeQuery(query);
		
		accountID = -1;
		if (res->next()) {
			accountID = res->getInt(0);
			stationID = res->getUnsignedInt(3);
		}
		
		delete res;
		return accountID != -1;
	}

	bool create() {
		try {
			stringstream query;
		
			query << "INSERT INTO `account` (username,password,station_id,gm,banned,email,joindate,lastlogin) "
               	  << "VALUES ('" << username.c_str() << "',SHA1('" << password.c_str() << "')," 
               	  << System::random() << ",0,0,'ChangeMe@email.com',NOW(),NOW())";
					   
			ServerDatabase::instance()->executeStatement(query);
			
			return true;
		} catch(DatabaseException& e) {
			return false;
		}
	}

	void login(LoginClient* client) {
		if (accountID > 0) {
			Message* lct = new LoginClientToken(username, accountID, stationID);
			client->sendMessage(lct);

			loadGalaxies(client);
	
			CharacterList characters(accountID);
	
			Message* eci = new EnumerateCharacterID(&characters);
			client->sendMessage(eci);
		}
	}

	void loadGalaxies(LoginClient* client) {
		GalaxyList galaxies;
		uint32 galaxyCount = galaxies.size();

		LoginEnumCluster* lec = new LoginEnumCluster(galaxyCount);
		LoginClusterStatus* lcs = new LoginClusterStatus(galaxyCount);

	    while (galaxies.next()) {
	    	uint32 galaxyID = galaxies.getGalaxyID();
	    	
	    	string name;
	    	galaxies.getGalaxyName(name);
	    	
	    	lec->addGalaxy(galaxyID, name);
	    	
   		    string address;
	    	galaxies.getGalaxyAddress(address);
	    	
	    	lcs->addGalaxy(galaxyID, address, galaxies.getGalaxyPort(), galaxies.getGalaxyPingPort());
	    }

		client->sendMessage(lec);
		client->sendMessage(lcs);
	}
	
	friend class AccountVersionMessage;
};

#endif /*ACCOUNT_H_*/
