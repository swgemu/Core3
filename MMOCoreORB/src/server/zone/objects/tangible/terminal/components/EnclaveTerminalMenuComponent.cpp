#include "EnclaveTerminalMenuComponent.h"
#include "server/zone/Zone.h"
#include "server/zone/packets/object/ObjectMenuResponse.h"
#include "server/zone/objects/scene/SceneObject.h"
#include "server/zone/objects/creature/CreatureObject.h"
#include "server/zone/objects/player/PlayerObject.h"
#include "server/zone/objects/building/BuildingObject.h"
#include "server/zone/managers/frs/FrsManager.h"
#include "server/zone/objects/tangible/TangibleObject.h"
#include "server/zone/objects/player/variables/FrsData.h"

void EnclaveTerminalMenuComponent::fillObjectMenuResponse(SceneObject* sceneObject, ObjectMenuResponse* menuResponse, CreatureObject* player) const {
	ManagedReference<BuildingObject*> building = sceneObject->getParentRecursively(SceneObjectType::BUILDING).castTo<BuildingObject*>();

	if (building == NULL || player->isDead() || player->isIncapacitated())
		return;

	ZoneServer* zServ = building->getZoneServer();

	if (zServ == NULL)
		return;

	FrsManager* frsManager = zServ->getFrsManager();

	if (frsManager == NULL)
		return;

	int enclaveType = frsManager->getEnclaveType(building);

	if (enclaveType == 0)
		return;

	int terminalType = getTerminalType(sceneObject);

	if (terminalType == 0)
		return;

	PlayerObject* ghost = player->getPlayerObject();

	if (ghost == NULL)
		return;

	FrsData* frsData = ghost->getFrsData();
	int playerRank = frsData->getRank();

	if (playerRank < 0) {
		player->sendSystemMessage("@force_rank:insufficient_rank_vote"); // You have insufficient rank in order to vote.
		return;
	}

	if (frsData->getCouncilType() == 0)
		return;

	if (terminalType == VOTING) {
		menuResponse->addRadialMenuItem(20, 3, "@force_rank:vote_status"); // Voting Status
		menuResponse->addRadialMenuItemToRadialID(20, 21, 3,"@force_rank:record_vote"); // Record Vote
		menuResponse->addRadialMenuItemToRadialID(20, 22, 3,"@force_rank:accept_promotion"); // Accept Promotion
		menuResponse->addRadialMenuItemToRadialID(20, 24, 3,"@force_rank:petition"); // Petition

		if (playerRank > 7 && enclaveType == FrsManager::COUNCIL_LIGHT)
			menuResponse->addRadialMenuItem(24, 3, "@force_rank:demote_member"); // Demote Lower Tier Member

		menuResponse->addRadialMenuItem(25, 3, "@force_rank:recover_jedi_items"); // Recover Jedi Items

		if (ghost->isPrivileged())
			menuResponse->addRadialMenuItem(26, 3, "Force Phase Change");
	}
}

int EnclaveTerminalMenuComponent::handleObjectMenuSelect(SceneObject* sceneObject, CreatureObject* player, byte selectedID) const {
	if (sceneObject == NULL || !sceneObject->isTangibleObject() || player == NULL || player->isDead() || player->isIncapacitated())
		return 0;

	ManagedReference<BuildingObject*> building = sceneObject->getParentRecursively(SceneObjectType::BUILDING).castTo<BuildingObject*>();

	if (building == NULL)
		return 1;

	ZoneServer* zServ = building->getZoneServer();

	if (zServ == NULL)
		return 1;

	FrsManager* frsManager = zServ->getFrsManager();

	if (frsManager == NULL)
		return 1;

	int enclaveType = frsManager->getEnclaveType(building);

	if (enclaveType == 0)
		return 1;

	int terminalType = getTerminalType(sceneObject);

	if (terminalType == 0)
		return 1;

	PlayerObject* ghost = player->getPlayerObject();

	if (ghost == NULL)
		return 1;

	FrsData* frsData = ghost->getFrsData();
	int playerRank = frsData->getRank();

	if (playerRank < 0) {
		player->sendSystemMessage("@force_rank:insufficient_rank_vote"); // You have insufficient rank in order to vote.
		return 1;
	}

	if (frsData->getCouncilType() == 0)
		return 1;

	if (terminalType == VOTING && (selectedID >= 20 && selectedID <= 26)) {
		if (selectedID == 20)
			frsManager->sendVoteSUI(player, sceneObject, FrsManager::SUI_VOTE_STATUS, enclaveType);
		else if (selectedID == 21)
			frsManager->sendVoteSUI(player, sceneObject, FrsManager::SUI_VOTE_RECORD, enclaveType);
		else if (selectedID == 22)
			frsManager->sendVoteSUI(player, sceneObject, FrsManager::SUI_VOTE_ACCEPT_PROMOTE, enclaveType);
		else if (selectedID == 23)
			frsManager->sendVoteSUI(player, sceneObject, FrsManager::SUI_VOTE_DEMOTE, enclaveType);
		else if (selectedID == 24)
			frsManager->sendVoteSUI(player, sceneObject, FrsManager::SUI_VOTE_PETITION, enclaveType);
		else if (selectedID == 26 && ghost->isPrivileged())
			frsManager->sendVoteSUI(player, sceneObject, FrsManager::SUI_FORCE_PHASE_CHANGE, enclaveType);
		//else
			//frsManager->recoverJediItems(player);
	}

	return 0;
}

int EnclaveTerminalMenuComponent::getTerminalType(SceneObject* terminal) const {
	if (terminal == NULL)
		return 0;

	uint64 terminalCRC = terminal->getServerObjectCRC();

	if (terminalCRC == STRING_HASHCODE("object/tangible/terminal/terminal_light_enclave_voting.iff"))
		return VOTING;
	else if (terminalCRC == STRING_HASHCODE("object/tangible/terminal/terminal_light_enclave_challenge.iff"))
		return LIGHT_CHALLENGE;
	else if (terminalCRC == STRING_HASHCODE("object/tangible/terminal/terminal_dark_enclave_voting.iff"))
		return VOTING;
	else if (terminalCRC == STRING_HASHCODE("object/tangible/terminal/terminal_dark_enclave_challenge.iff"))
		return DARK_CHALLENGE;

	return 0;
}
