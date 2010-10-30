/*
 * GuildMemberList.h
 *
 *  Created on: Oct 27, 2010
 *      Author: crush
 */

#ifndef GUILDMEMBERLIST_H_
#define GUILDMEMBERLIST_H_

#include "engine/engine.h"

namespace server {
 namespace zone {
  namespace objects {
   namespace guild {

    class GuildMemberInfo;

	class GuildMemberList : public VectorMap<uint64, GuildMemberInfo*> {
		uint64 guildLeaderID;

	public:
		GuildMemberList() : VectorMap<uint64, GuildMemberInfo*>() {
			setNullValue(NULL);
			setNoDuplicateInsertPlan();
			setSize(500, false);
		}

		inline uint64 getGuildLeaderID() {
			return guildLeaderID;
		}
	};

   }
  }
 }
}

using namespace server::zone::objects::guild;


#endif /* GUILDMEMBERLIST_H_ */
