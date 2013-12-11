
#ifndef REMOVEPETSFROMGROUPTASK_H_
#define REMOVEPETSFROMGROUPTASK_H_

#include "server/zone/objects/creature/CreatureObject.h"
#include "server/zone/objects/creature/AiAgent.h"
#include "server/zone/objects/group/GroupObject.h"
#include "server/zone/objects/player/PlayerObject.h"

class RemovePetsFromGroupTask : public Task {
	ManagedReference<CreatureObject*> player;
	ManagedReference<GroupObject*> group;
public:
	RemovePetsFromGroupTask(CreatureObject* creo, GroupObject* grp) :
		player(creo), group(grp) {

	}

	void run() {
		Locker locker(player);

		Locker clocker(group, player);

		Reference<PlayerObject*> ghost = player->getPlayerObject();

		for (int i = 0; i < ghost->getActivePetsSize(); i++) {
			ManagedReference<AiAgent*> pet = ghost->getActivePet(i);

			if (pet == NULL)
				continue;

			if (group->hasMember(pet)) {
				group->removeMember(pet);
				pet->updateGroup(NULL);
			}
		}

		if (group->getGroupSize() < 2) {
			group->disband();
			return;
		}

		ManagedReference<SceneObject*> leader = group->getLeader();

		// Make sure new leader isn't a pet
		if (leader == NULL || !leader->isPlayerCreature()) {
			for (int i = 1; i < group->getGroupSize(); i++) {
				ManagedReference<SceneObject*> scno = group->getGroupMember(i);

				if (scno == NULL)
					continue;

				if (scno->isPlayerCreature())
					group->makeLeader(scno);

				break;
			}
		}

		leader = group->getLeader();

		// Disband if only pets remain
		if (leader == NULL || !leader->isPlayerCreature()) {
			group->disband();
		}
	}
};



#endif /* REMOVEPETSFROMGROUPTASK_H_ */
