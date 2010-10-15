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

#ifndef LOGINCLIENTTOKEN_H_
#define LOGINCLIENTTOKEN_H_

#include "engine/engine.h"
#include "../account/Account.h"

namespace server {
namespace login {

	namespace account {
		class Account;
	}

	using namespace server::login::account;

namespace packets {

	class LoginClientToken : public BaseMessage {
	public:
		LoginClientToken(String& username, uint32 sessionKey, uint32 accountid, uint32 stationid) : BaseMessage() {
			insertShort(0x04);
			insertInt(0xAAB296C6);

			/* BaseMessage(100)

			insertInt(0x00000038 + 4); //size

			//session key:
			insertInt(0x00000020);
			insertInt(0x00000015);
			insertInt(0xDE93D60E);
			insertInt(0x8EBFEFD2);
			insertInt(0xEED2ACA1);
			insertInt(0x30BE554C);
			insertInt(0x0D23BE5F);
			insertInt(0xF958ABB4);
			insertInt(0x67796962);
			insertInt(0xD36E19E8);
			insertInt(0x4A3A9B86);
			insertInt(0xFAA172A1);
			insertInt(0x9FFF968F);
			insertInt(0x295A62A5);
			insertInt(accountid); //Account ID*/

			insertInt(0x00000008); //size

			insertInt(sessionKey);
			insertInt(accountid); //Account ID

			insertInt(stationid); //Station ID
			insertAscii(username); //Station Account Name

			insertByte(0);
			insertShort(0);
		}

		LoginClientToken(Account* account, uint32 sessionID) : BaseMessage() {
			insertShort(0x04);
			insertInt(0xAAB296C6);

			insertInt(0x00000008);

			insertInt(sessionID);
			insertInt(account->getAccountID());
			insertInt(account->getStationID());
			insertAscii(account->getUsername());

			insertByte(0);
			insertShort(0);
		}

		static void parse(Packet* pack) {
			uint16 ackSequence = pack->parseShort();
		}
	};
}
}
}

using namespace server::login::packets;
#endif /*LOGINCLIENTTOKEN_H_*/
