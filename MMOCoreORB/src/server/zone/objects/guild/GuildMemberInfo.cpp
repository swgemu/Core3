/*
 * GuildMemberInfo.cpp
 *
 *  Created on: Nov 4, 2010
 *      Author: crush
 */

#include "GuildMemberInfo.h"
#include "GuildObject.h"

GuildMemberInfo::GuildMemberInfo(uint64 playerid) : Object() {
	playerID = playerid;
	permissions = GuildObject::PERMISSION_NONE;
	declaredAllegiance = 0;

	//addSerializableVariables();
}

int GuildMemberInfo::compareTo(const GuildMemberInfo& gmi) const {
	if (playerID < gmi.playerID)
		return 1;
	else if (playerID > gmi.playerID)
		return -1;
	else
		return 0;
}

GuildMemberInfo& GuildMemberInfo::operator=(const GuildMemberInfo& gmi) {
	if (this == &gmi)
		return *this;

	playerID = gmi.playerID;
	guildTitle = gmi.guildTitle;
	permissions = gmi.permissions;
	declaredAllegiance = gmi.declaredAllegiance;

	return *this;
}
