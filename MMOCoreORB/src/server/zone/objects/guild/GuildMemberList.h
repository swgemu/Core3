/*
 * GuildMemberList.h
 *
 *  Created on: Oct 27, 2010
 *      Author: crush
 */

#ifndef GUILDMEMBERLIST_H_
#define GUILDMEMBERLIST_H_

#include "engine/engine.h"

#include "GuildMemberInfo.h"

namespace server {
 namespace zone {
  namespace objects {
   namespace guild {

	class GuildMemberList : public VectorMap<uint64, GuildMemberInfo> {
		public:

		GuildMemberList() {
			setNoDuplicateInsertPlan();
		}
	};
   }
  }
 }
}

using namespace server::zone::objects::guild;


#endif /* GUILDMEMBERLIST_H_ */
