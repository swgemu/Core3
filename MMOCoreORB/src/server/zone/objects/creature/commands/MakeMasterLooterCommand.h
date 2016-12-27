/*
 * MakeMasterLooterCommand.h
 *
 *  Modified on: March 4, 2015
 *      Author: Anakis
 */

#ifndef MAKEMASTERLOOTERCOMMAND_H_
#define MAKEMASTERLOOTERCOMMAND_H_

class MakeMasterLooterCommand : public QueueCommand {
public:

	MakeMasterLooterCommand(const String& name, ZoneProcessServer* server)
		: QueueCommand(name, server) {

	}

	int doQueueCommand(CreatureObject* creature, const uint64& target, const UnicodeString& arguments) const {

		if (!checkStateMask(creature))
			return INVALIDSTATE;

		if (!checkInvalidLocomotions(creature))
			return INVALIDLOCOMOTION;

		//Check is in a group.
		ManagedReference<GroupObject*> group = creature->getGroup();
		if (group == NULL) {
			StringIdChatParameter groupOnly("group","group_only"); //You can only set or check group looting options if you are in a group."
			creature->sendSystemMessage(groupOnly);
			return GENERALERROR;
		}

		Locker glocker(group, creature);

		//Check is group leader.
		if (group->getLeader() != creature) {
			StringIdChatParameter leaderOnly("group","leader_only"); //"Only the Group Leader can set the looting options."
			creature->sendSystemMessage(leaderOnly);
			return GENERALERROR;
		}

		GroupManager* manager = GroupManager::instance();

		//Check if current target is valid to be Master Looter. If not, send the list of potential Master Looters.
		ManagedReference<CreatureObject*> object = server->getZoneServer()->getObject(target).castTo<CreatureObject*>();
		if (object != NULL && object->isPlayerCreature() && group->hasMember(object)) {
			manager->changeMasterLooter(group, object, true);
			return SUCCESS;
		} else
			manager->sendMasterLooterList(group, creature);

		return SUCCESS;
	}

};




#endif /* MAKEMASTERLOOTERCOMMAND_H_ */
