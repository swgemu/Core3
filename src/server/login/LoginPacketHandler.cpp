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
#include "LoginServer.h"
#include "LoginProcessServerImplementation.h"

#include "account/AccountManager.h"

LoginPacketHandler::LoginPacketHandler(const String& s, LoginProcessServerImplementation* serv)
		: Logger(s) {

	processServer = serv;

	server = processServer->getLoginServer();

	setGlobalLogging(true);
	setLogging(true);
}

void LoginPacketHandler::handleMessage(Message* pack) {
	Reference<LoginClient*> client = server->getLoginClient(pack->getClient());

	StringBuffer msg;
	msg << "parsing " << pack->toStringData();
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
			handleDeleteCharacterMessage(client, pack);
			break;
		}
		break;
	case 04:
		switch (opcode) {
		case 0x41131F96: //LoginClientID CLIENT VERSION BUILD DATE AND LOGIN INFO
			handleLoginClientID(client, pack);
			break;
		}
		break;
	case 05:
		break;
	default:
		break;
	}
}

void LoginPacketHandler::handleLoginClientID(LoginClient* client, Message* pack) {
	AccountManager* accountManager = server->getAccountManager();
	accountManager->loginAccount(client, pack);
}

void LoginPacketHandler::handleDeleteCharacterMessage(LoginClient* client, Message* pack) {
	uint32 ServerId = pack->parseInt();

	//pack->shiftOffset(4);
    uint64 charId = pack->parseLong();

    StringBuffer moveStatement;
    moveStatement << "INSERT INTO deleted_characters SELECT * FROM characters WHERE character_oid = " << charId;


    StringBuffer deleteStatement;
    deleteStatement << "DELETE FROM characters WHERE character_oid = " << charId;

    int dbDelete;

    String firstName;

    try {

		ServerDatabase::instance()->executeStatement(moveStatement);
		ServerDatabase::instance()->executeStatement(deleteStatement);

		dbDelete = 0;
    } catch (DatabaseException& e) {
    	System::out << e.getMessage();
   		dbDelete = 1;
   	} catch (Exception& e) {
   		System::out << e.getMessage();
   	}

   	Message* msg = new DeleteCharacterReplyMessage(dbDelete);
	client->sendMessage(msg);
}


