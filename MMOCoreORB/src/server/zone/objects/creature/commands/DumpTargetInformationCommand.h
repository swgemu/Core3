/*
				Copyright <SWGEmu>
		See file COPYING for copying conditions.*/

#ifndef DUMPTARGETINFORMATIONCOMMAND_H_
#define DUMPTARGETINFORMATIONCOMMAND_H_

#include "server/zone/objects/scene/SceneObject.h"

class DumpTargetInformationCommand : public QueueCommand {
public:

	DumpTargetInformationCommand(const String& name, ZoneProcessServer* server)
		: QueueCommand(name, server) {

	}

	int doQueueCommand(CreatureObject* creature, const uint64& target, const UnicodeString& arguments) const {

		if (!checkStateMask(creature))
			return INVALIDSTATE;

		if (!checkInvalidLocomotions(creature))
			return INVALIDLOCOMOTION;

		if (!creature->isPlayerCreature())
			return GENERALERROR;

		CreatureObject* player = cast<CreatureObject*>(creature);

		//Apparently this command doesn't actually pass the targetid, so that probably means that it only accepts a player name
		//TODO: Reimplement this command as @getPlayerInfo
		uint64 targetID = player->getTargetID();

		ManagedReference<SceneObject*> obj = server->getZoneServer()->getObject(targetID);

		if (obj == NULL)
			return INVALIDTARGET;

		ManagedReference<SceneObject*> cell = obj->getParent();

		int cellid = 0;
		uint32 buildingTemplate = 0;

		if (cell != NULL && cell->isCellObject()) {
			cellid = (cast<CellObject*>(cell.get()))->getCellNumber();
			ManagedReference<SceneObject*> building = cell->getParent();
			buildingTemplate = building->getServerObjectCRC();
		}

		StringBuffer msg;

		float posX = obj->getPositionX(), posZ = obj->getPositionZ(), posY = obj->getPositionY();
		Quaternion* direction = obj->getDirection();

		msg << "x = " << posX << ", z = " << posZ << ", y = " << posY << ", ow = " << direction->getW()
				<< ", ox = " << direction->getX() << ", oz = " << direction->getZ() << ", oy = " << direction->getY()
				<< ", cellid = " << cellid;

		if (buildingTemplate != 0)
			msg << endl << TemplateManager::instance()->getTemplateFile(buildingTemplate);

		if (obj->isAiAgent()) {
			AiAgent* objCreo = obj.castTo<AiAgent*>();

			PatrolPoint* home = objCreo->getHomeLocation();
			if (home != NULL) {
				cell = home->getCell();

				if (cell != NULL && cell->isCellObject()) {
					cellid = (cast<CellObject*>(cell.get()))->getCellNumber();
					ManagedReference<SceneObject*> building = cell->getParent();
					buildingTemplate = building->getServerObjectCRC();
				}

				msg << endl << "homeX = " << home->getPositionX() << ", homeZ = " << home->getPositionZ() << ", homeY = " << home->getPositionY()
						<< ", homeCell = " << cellid;

				if (buildingTemplate != 0)
					msg << endl << TemplateManager::instance()->getTemplateFile(buildingTemplate);
			}

			if (objCreo->getPatrolPointSize() > 0) {
				PatrolPoint nextPosition = objCreo->getNextPosition();
				cell = nextPosition.getCell();

				if (cell != NULL && cell->isCellObject()) {
					cellid = (cast<CellObject*>(cell.get()))->getCellNumber();
					ManagedReference<SceneObject*> building = cell->getParent();
					buildingTemplate = building->getServerObjectCRC();
				}

				msg << endl << "nextX = " << nextPosition.getPositionX() << ", nextZ = " << nextPosition.getPositionZ() << ", nextY = " << nextPosition.getPositionY()
						<< ", nextCell = " << cellid;

				if (buildingTemplate != 0)
					msg << endl << TemplateManager::instance()->getTemplateFile(buildingTemplate);
			}

			msg << endl << "numberOfPlayersInRange = " << objCreo->getNumberOfPlayersInRange();
		}

		player->sendSystemMessage(msg.toString());

		ChatManager* chatManager = server->getZoneServer()->getChatManager();
		chatManager->sendMail("System", "dumpTargetInformation", msg.toString(), player->getFirstName());

		return SUCCESS;
	}

};

#endif //DUMPTARGETINFORMATIONCOMMAND_H_
