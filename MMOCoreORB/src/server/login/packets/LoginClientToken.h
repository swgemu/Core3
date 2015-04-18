/*
				Copyright <SWGEmu>
		See file COPYING for copying conditions.*/

#ifndef LOGINCLIENTTOKEN_H_
#define LOGINCLIENTTOKEN_H_

#include "engine/engine.h"
#include "server/login/account/Account.h"

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
