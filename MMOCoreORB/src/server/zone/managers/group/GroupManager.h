/*
				Copyright <SWGEmu>
		See file COPYING for copying conditions.*/

#ifndef GROUPMANAGER_H_
#define GROUPMANAGER_H_

#include "engine/engine.h"

namespace server {
 namespace zone {
  class ZoneServer;
 }
}

using namespace server::zone;

namespace server {
 namespace zone {
  namespace objects {
   namespace group {
	   class GroupObject;
   }
  }
 }
}

using namespace server::zone::objects::group;


namespace server {
 namespace zone {
  namespace objects {
   namespace creature {
	   class CreatureObject;
   }
  }
 }
}

using namespace server::zone::objects::creature;

class GroupManager : public Singleton<GroupManager>, public Object {

public:
	enum {
		FREEFORALL = 0,
		MASTERLOOTER = 1,
		LOTTERY = 2,
		RANDOM = 3
	};

private:
	bool playerIsInvitingOwnPet(CreatureObject* inviter, CreatureObject* target);

public:
	GroupManager();

	void inviteToGroup(CreatureObject* leader, CreatureObject* target);
	void joinGroup(CreatureObject* player);

	void kickFromGroup(ManagedReference<GroupObject*> group, CreatureObject* player, CreatureObject* memberToKick);
	void leaveGroup(ManagedReference<GroupObject*> group, CreatureObject* player);
	void makeLeader(GroupObject* group, CreatureObject* player, CreatureObject* newLeader);

	void changeLootRule(GroupObject* group, int newRule);
	void changeMasterLooter(GroupObject* group, CreatureObject* newLooter, bool enableRule);
	void sendMasterLooterList(GroupObject* group, CreatureObject* leader);
	void notifyMasterLooter(GroupObject* group);

	void disbandGroup(ManagedReference<GroupObject*> group, CreatureObject* player);

	GroupObject* createGroup(CreatureObject* leader);



};

#endif /*GROUPMANAGER_H_*/
