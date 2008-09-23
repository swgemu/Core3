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


#include "objects.h"

#include "LoginPacketHandler.h"
#include "LoginClient.h"

void LoginPacketHandler::handleMessage(Message* pack) {
	stringstream msg;
	msg << "parsing " << pack->toString();
	//info(msg);

	uint16 opcount = pack->parseShort();
	uint32 opcode = pack->parseInt();

	switch (opcount) {
	case 01:
		break;
	case 02:
		break;
	case 03:
		switch (opcode) {
			case 0xE87AD031:
			handleDeleteCharacterMessage(pack);
			break;
		}
		break;
	case 04:
		switch (opcode) {
		case 0x41131F96: //LoginClientID CLIENT VERSION BUILD DATE AND LOGIN INFO
			handleLoginClientID(pack);
			break;
		}
		break;
	case 05:
		break;
	default:
		break;
	}
}

void LoginPacketHandler::handleLoginClientID(Message* pack) {
	LoginClient* client = (LoginClient*) pack->getClient();

	string errtype, errmsg;
	Message* ver;

	Account account(pack);

	if (!account.checkVersion()) {
		errtype = "Login Error";
		errmsg = "The client you are using is out of date. Go to the SWGEmu Updates forum and read the 11/03/07 Client Notice.";
		ver = new ErrorMessage(errtype, errmsg, 0x00);
		client->sendMessage(ver);
	} else {
		int validateResult = account.validate(configManager);

		if(validateResult != ACCOUNTOK){

			validateResult = account.create(configManager);

			if(validateResult == ACCOUNTOK){

				account.validate(configManager);

			}
		}

		switch (validateResult) {
		case ACCOUNTOK:
			account.login(client);
			return;
		case ACCOUNTINUSE:
			errtype = "Bad Password";
			errmsg= "Either you have mistyped your password, or this account is already in use.";
			ver = new ErrorMessage(errtype, errmsg, 0x00);
			client->sendMessage(ver);
			return;
		case ACCOUNTBADPW:
			errtype = "Password Error";
			errmsg= "Incorrect password entered.  Try again";
			ver = new ErrorMessage(errtype, errmsg, 0x00);
			client->sendMessage(ver);
			return;
		case ACCOUNTBANNED:
			errtype = "User Banned";
			errmsg = "Your Account is Banned.";
			ver = new ErrorMessage(errtype, errmsg, 0x00);
			client->sendMessage(ver);
			return;
		case ACCOUNTAUTOREGDISABLED:
			errtype = "Login Error";
			errmsg = "Auto Registration is disabled, please obtain an account from a server administrator";
			ver = new ErrorMessage(errtype, errmsg, 0x00);
			client->sendMessage(ver);
			return;
		case ACCOUNTDOESNTEXIST:
			errtype = "Invalid Account";
			errmsg = "The specified user is not a registered forum user, please register on the forums to access this server.";
			ver = new ErrorMessage(errtype, errmsg, 0x00);
			client->sendMessage(ver);
			return;
		case ACCOUNTNOTACTIVE:
			errtype = "Inactive Account";
			errmsg = "You have not responded to your activation email, and will not be allowed to log on until you do.";
			ver = new ErrorMessage(errtype, errmsg, 0x00);
			client->sendMessage(ver);
			return;
		default:
			break;
		}
	}
}

void LoginPacketHandler::handleDeleteCharacterMessage(Message* pack) {
	LoginClient* client = (LoginClient*) pack->getClient();

	uint32 ServerId = pack->parseInt();
    uint64 charId = pack->parseLong();
    int dbDelete;
    string firstName;

    try {
		stringstream query;

		query << "SELECT lower(firstname) FROM characters WHERE character_id = " << charId <<" and galaxy_id = " << ServerId << ";";
		ResultSet* res = ServerDatabase::instance()->executeQuery(query);

		if (res->next())
			firstName = res->getString(0);


		query.str(""); // clear stream
		query << "DELETE FROM character_items WHERE character_id = '" << charId <<"';";
		ServerDatabase::instance()->executeStatement(query);

		query.str(""); // clear stream
		query << "DELETE FROM character_faction WHERE character_id = '" << charId <<"';";
		ServerDatabase::instance()->executeStatement(query);

		query.str(""); // clear stream
		query << "DELETE FROM character_profession WHERE character_id = '" << charId <<"';";
		ServerDatabase::instance()->executeStatement(query);

		query.str(""); // clear stream
		query << "DELETE FROM character_badge WHERE character_id = '" << charId <<"';";
		ServerDatabase::instance()->executeStatement(query);

		query.str("");
		query << "DELETE FROM waypoints WHERE owner_id = '" << charId <<"';";
		ServerDatabase::instance()->executeStatement(query);

		query.str("");
		query << "DELETE FROM friendlist WHERE character_id = '" << charId <<"';";
		ServerDatabase::instance()->executeStatement(query);

		query.str("");
		query << "DELETE FROM friendlist WHERE friend_id = '" << charId <<"';";
		ServerDatabase::instance()->executeStatement(query);

		query.str("");
		query << "DELETE FROM ignorelist WHERE character_id = '" << charId <<"';";
		ServerDatabase::instance()->executeStatement(query);

		query.str("");
		query << "DELETE FROM ignorelist WHERE ignore_id = '" << charId <<"';";
		ServerDatabase::instance()->executeStatement(query);

		query.str("");
		query << "DELETE FROM mail WHERE lower(recv_name) = '" << firstName <<"';";
		ServerDatabase::instance()->executeStatement(query);


		/* ToDO: Revisit this, when mail attachments are functionally
		query.str("");
		query << "DELETE FROM mail_attachment WHERE lower(name) = '" << firstName <<"';";
		ServerDatabase::instance()->executeStatement(query);
		*/

		query.str(""); // clear stream
		query << "DELETE FROM characters WHERE character_id = '" << charId <<"' and galaxy_id = '" << ServerId << "';";
		ServerDatabase::instance()->executeStatement(query);

		query.str("");
		query << "DELETE FROM consentlist WHERE character_id = '" << charId << "';";
		ServerDatabase::instance()->executeStatement(query);

		delete res;
		dbDelete = 0;
    } catch(DatabaseException& e) {

   		dbDelete = 1;
   	}

   	Message* msg = new DeleteCharacterReplyMessage(dbDelete);
	client->sendMessage(msg);
}


