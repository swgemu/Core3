/*
 * MakeMasterLooterCommand.h
 *
 *  Modified on: March 4, 2015
 *      Author: Anakis
 */

#ifndef MAKEMASTERLOOTERCOMMAND_H_
#define MAKEMASTERLOOTERCOMMAND_H_

#include "server/zone/objects/scene/SceneObject.h"

class MakeMasterLooterCommand : public QueueCommand {
public:

	MakeMasterLooterCommand(const String& name, ZoneProcessServer* server)
		: QueueCommand(name, server) {

	}

	int doQueueCommand(CreatureObject* creature, const uint64& target, const UnicodeString& arguments) {

		if (!checkStateMask(creature))
			return INVALIDSTATE;

		if (!checkInvalidLocomotions(creature))
			return INVALIDLOCOMOTION;

		//Check is in a group.
		ManagedReference<GroupObject*> group = creature->getGroup();
		if (group == NULL) {
			creature->sendSystemMessage("@group:group_only"); //You can only set or check group looting options if you are in a group."
			return GENERALERROR;
		}

		//Check is group leader.
		if (group->getLeader() != creature) {
			creature->sendSystemMessage("@group:leader_only"); //"Only the Group Leader can set the looting options."
			return GENERALERROR;
		}

		GroupManager* manager = GroupManager::instance();

		//Check if current target is valid to be Master Looter. If not, send the list of potential Master Looters.
		ManagedReference<SceneObject*> object = server->getZoneServer()->getObject(target);
		if (object != NULL && object->isPlayerCreature() && group->hasMember(object)) {
			CreatureObject* targetPlayer = cast<CreatureObject*>(object.get());
			manager->changeMasterLooter(group, creature, targetPlayer, true);
			return SUCCESS;
		} else
			manager->sendMasterLooterList(group, creature);

		return SUCCESS;
	}

};




#endif /* MAKEMASTERLOOTERCOMMAND_H_ */
