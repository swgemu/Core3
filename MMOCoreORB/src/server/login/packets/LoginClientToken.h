/*
				Copyright <SWGEmu>
		See file COPYING for copying conditions.*/

#ifndef LOGINCLIENTTOKEN_H_
#define LOGINCLIENTTOKEN_H_

#include "engine/service/proto/BaseMessage.h"
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
		LoginClientToken(const String& username, const String& sessionToken,
				uint32 accountid, uint32 stationid) : BaseMessage() {
			insertShort(0x04);
			insertInt(0xAAB296C6);

			insertInt(sessionToken.length() + 4); //embedding accountid

			for (const auto val : sessionToken) {
				insertByte(val);
			}

			insertInt(accountid);

			insertInt(stationid);
			insertAscii(username); //Station Account Name
		}

		LoginClientToken(Account* account, const String& sessionToken) : BaseMessage() {
			insertShort(0x04);
			insertInt(0xAAB296C6);

			insertInt(sessionToken.length() + 4);

			for (const auto val : sessionToken) {
				insertByte(val);
			}

			insertInt(account->getAccountID());

			insertInt(account->getStationID());
			insertAscii(account->getUsername());
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
