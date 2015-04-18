/*
				Copyright <SWGEmu>
		See file COPYING for copying conditions.*/

#ifndef FINDPLAYERCOMMAND_H_
#define FINDPLAYERCOMMAND_H_

#include "server/zone/objects/scene/SceneObject.h"
#include "server/zone/objects/player/PlayerObject.h"
#include "server/zone/objects/player/sui/messagebox/SuiMessageBox.h"

class FindPlayerCommand : public QueueCommand {
public:

	FindPlayerCommand(const String& name, ZoneProcessServer* server)
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

		//TODO: Research if this gets handled already by the absence of the 'admin' skill.
		ManagedReference<PlayerObject*> ghost = player->getPlayerObject();

		//if (!ghost->isPrivileged())
			//return GENERALERROR;

		StringTokenizer tokenizer(arguments.toString());
		tokenizer.setDelimeter(" ");

		if (!tokenizer.hasMoreTokens())
			return INVALIDPARAMETERS;

		String targetName;
		tokenizer.getStringToken(targetName);

		PlayerManager* playerManager = server->getZoneServer()->getPlayerManager();
		uint64 objectid = playerManager->getObjectID(targetName);

		ManagedReference<SceneObject*> obj = server->getZoneServer()->getObject(objectid);

		if (obj == NULL || !obj->isPlayerCreature()) {
			//Send message about player not existing.
			StringIdChatParameter params;
			params.setStringId("@player_structure:modify_list_invalid_player"); //%NO is an invalid player name.
			params.setTO(targetName);
			player->sendSystemMessage(params);
			return GENERALERROR;
		}

		CreatureObject* targetObject = cast<CreatureObject*>( obj.get());
		PlayerObject* targetGhost = targetObject->getPlayerObject();

		ManagedReference<SuiMessageBox*> suiBox = new SuiMessageBox(player, 0x00);
		suiBox->setPromptTitle("Find Player Results");

		StringBuffer text;
		text << "Player Name:\t  " << targetObject->getDisplayedName() << "\n";

		text << "Online Status:\t  " << (targetGhost->isOffline() ? "\\#ff3300 Offline" : "\\#00ff33 Online") << "\\#.\n";

		if (targetObject->getZone() != NULL)
			text << "Planet Name:\t " << targetObject->getZone()->getZoneName() << "\n";

		Vector3 worldPosition = targetObject->getWorldPosition();
		text << "World Position:\t  {x:" << worldPosition.getX() << ", z:" << worldPosition.getZ() << ", y:" << worldPosition.getY() << "} " << "\n";

		if (targetObject->getParent() != NULL && targetObject->getParent().get()->isCellObject()) {
			ManagedReference<CellObject*> cell = cast<CellObject*>( targetObject->getParent().get().get());
			Vector3 cellPosition = targetObject->getPosition();
			text << "Cell Position:\t  {x:" << cellPosition.getX() << ", z:" << cellPosition.getZ() << ", y:" << cellPosition.getY() << "} Cell: " << cell->getCellNumber() << " (" << cell->getObjectID() << ")\n";
		}

		Quaternion* dir = targetObject->getDirection();
		text << "Direction:\t\t  {x:" << dir->getX() << ", y:" << dir->getY() << ", z:" << dir->getZ() << ", w:" << dir->getW() << "}\n";

		suiBox->setPromptText(text.toString());

		player->sendMessage(suiBox->generateMessage());

		return SUCCESS;
	}

};

#endif //FINDPLAYERCOMMAND_H_
