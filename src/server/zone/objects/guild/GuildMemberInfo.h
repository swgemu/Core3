/*
 * GuildMemberInfo.h
 *
 *  Created on: Oct 27, 2010
 *      Author: crush
 */

#ifndef GUILDMEMBERINFO_H_
#define GUILDMEMBERINFO_H_

#include "engine/engine.h"

namespace server {
namespace zone {
namespace objects {
namespace guild {

	class GuildObject;

	class GuildMemberInfo {
		uint64 playerID;
		String guildTitle;
		uint8 permissions;
		uint64 declaredAllegiance;
		bool sponsored;

	public:
		GuildMemberInfo(uint64 playerid) {
			playerID = playerid;
			permissions = GuildObject::PERMISSION_NONE;
			declaredAllegiance = 0;
			sponsored = true;
		}
	};

}
}
}
}
using namespace server::zone::objects::guild;

#endif /* GUILDMEMBERINFO_H_ */
