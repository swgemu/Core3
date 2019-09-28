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

	if (building == nullptr || player->isDead() || player->isIncapacitated())
		return;

	ZoneServer* zServ = building->getZoneServer();

	if (zServ == nullptr)
		return;

	FrsManager* frsManager = zServ->getFrsManager();

	if (frsManager == nullptr)
		return;

	int enclaveType = frsManager->getEnclaveType(building);

	if (enclaveType == 0)
		return;

	int terminalType = getTerminalType(sceneObject);

	if (terminalType == 0)
		return;

	PlayerObject* ghost = player->getPlayerObject();

	if (ghost == nullptr)
		return;

	FrsData* frsData = ghost->getFrsData();
	int playerRank = frsData->getRank();

	if (playerRank < 0 && !ghost->isPrivileged()) {
		player->sendSystemMessage("@force_rank:insufficient_rank_vote"); // You have insufficient rank in order to vote.
		return;
	}

	if (frsData->getCouncilType() == 0 && !ghost->isPrivileged())
		return;

	if (frsManager->isPlayerFightingInArena(player->getObjectID()))
		return;

	if (terminalType == VOTING) {
		menuResponse->addRadialMenuItem(69, 3, "@force_rank:vote_status"); // Voting Status
		menuResponse->addRadialMenuItemToRadialID(69, 70, 3,"@force_rank:record_vote"); // Record Vote
		menuResponse->addRadialMenuItemToRadialID(69, 71, 3,"@force_rank:accept_promotion"); // Accept Promotion
		menuResponse->addRadialMenuItemToRadialID(69, 73, 3,"@force_rank:petition"); // Petition

		if (playerRank > 7 && enclaveType == FrsManager::COUNCIL_LIGHT)
			menuResponse->addRadialMenuItem(75, 3, "@force_rank:demote_member"); // Demote Lower Tier Member

		menuResponse->addRadialMenuItem(74, 3, "@force_rank:recover_jedi_items"); // Recover Jedi Items
#if FRS_TESTING
		if (ghost->isPrivileged())
			menuResponse->addRadialMenuItem(76, 3, "Force Phase Change");
#endif
	} else if (terminalType == LIGHT_CHALLENGE) {
		menuResponse->addRadialMenuItem(69, 3, "@force_rank:challenge_vote_status"); // No-Confidence Vote Status

		if (playerRank > 0) {
			menuResponse->addRadialMenuItemToRadialID(69, 70, 3,"@force_rank:record_challenge_vote"); // Record No-Confidence Vote
			menuResponse->addRadialMenuItemToRadialID(69, 71, 3,"@force_rank:issue_challenge_vote"); // Issue No-Confidence Vote
		}
	} else if (terminalType == DARK_CHALLENGE) {
		menuResponse->addRadialMenuItem(69, 3, "@pvp_rating:ch_terminal_view_scores"); // View Challenge Scores
		menuResponse->addRadialMenuItem(70, 3, "@pvp_rating:ch_terminal_arena_status"); // Arena Status

		if (frsManager->rankHasOpenChallenges(-1))
			menuResponse->addRadialMenuItem(71, 3, "@pvp_rating:ch_terminal_view_challenges"); // View Issued Challenges

		if (frsManager->canPlayerIssueArenaChallenge(player))
			menuResponse->addRadialMenuItem(73, 3,"@pvp_rating:ch_terminal_issue_challenge"); // Issue Challenge

		if (frsManager->canPlayerAcceptArenaChallenge(player))
			menuResponse->addRadialMenuItem(72, 3, "@pvp_rating:ch_terminal_accept_challenge"); // Accept a Challenge
#if FRS_TESTING
		if (ghost->isPrivileged() && !frsManager->isArenaOpen())
			menuResponse->addRadialMenuItem(76, 3, "(TESTING) Open Arena");
#endif
	}
}

int EnclaveTerminalMenuComponent::handleObjectMenuSelect(SceneObject* sceneObject, CreatureObject* player, byte selectedID) const {
	if (sceneObject == nullptr || !sceneObject->isTangibleObject() || player == nullptr || player->isDead() || player->isIncapacitated())
		return 0;

	if (player->getDistanceTo(sceneObject) > 15) {
		player->sendSystemMessage("@pvp_rating:ch_terminal_too_far"); // You are too far away from the terminal to use it.
		return 1;
	}

	ManagedReference<BuildingObject*> building = sceneObject->getParentRecursively(SceneObjectType::BUILDING).castTo<BuildingObject*>();

	if (building == nullptr)
		return 1;

	ZoneServer* zServ = building->getZoneServer();

	if (zServ == nullptr)
		return 1;

	FrsManager* frsManager = zServ->getFrsManager();

	if (frsManager == nullptr)
		return 1;

	int enclaveType = frsManager->getEnclaveType(building);

	if (enclaveType == 0)
		return 1;

	int terminalType = getTerminalType(sceneObject);

	if (terminalType == 0)
		return 1;

	PlayerObject* ghost = player->getPlayerObject();

	if (ghost == nullptr)
		return 1;

	FrsData* frsData = ghost->getFrsData();
	int playerRank = frsData->getRank();

	if (playerRank < 0 && !ghost->isPrivileged()) {
		player->sendSystemMessage("@force_rank:insufficient_rank_vote"); // You have insufficient rank in order to vote.
		return 1;
	}

	if (frsData->getCouncilType() == 0 && !ghost->isPrivileged())
		return 1;

	if (frsManager->isPlayerFightingInArena(player->getObjectID()))
		return 1;

	if (terminalType == VOTING) {
		if (selectedID == 69)
			frsManager->sendVoteSUI(player, sceneObject, FrsManager::SUI_VOTE_STATUS, enclaveType);
		else if (selectedID == 70)
			frsManager->sendVoteSUI(player, sceneObject, FrsManager::SUI_VOTE_RECORD, enclaveType);
		else if (selectedID == 71)
			frsManager->sendVoteSUI(player, sceneObject, FrsManager::SUI_VOTE_ACCEPT_PROMOTE, enclaveType);
		else if (selectedID == 75)
			frsManager->sendVoteSUI(player, sceneObject, FrsManager::SUI_VOTE_DEMOTE, enclaveType);
		else if (selectedID == 73)
			frsManager->sendVoteSUI(player, sceneObject, FrsManager::SUI_VOTE_PETITION, enclaveType);
#if FRS_TESTING
		else if (selectedID == 76 && ghost->isPrivileged())
			frsManager->sendVoteSUI(player, sceneObject, FrsManager::SUI_FORCE_PHASE_CHANGE, enclaveType);
#endif
		else if (selectedID == 74)
			frsManager->recoverJediItems(player);
	} else if (terminalType == LIGHT_CHALLENGE) {
		if (selectedID == 69)
			frsManager->sendChallengeVoteSUI(player, sceneObject, FrsManager::SUI_CHAL_VOTE_STATUS, enclaveType);
		else if (selectedID == 70)
			frsManager->sendChallengeVoteSUI(player, sceneObject, FrsManager::SUI_CHAL_VOTE_RECORD, enclaveType);
		else if (selectedID == 71)
			frsManager->sendChallengeVoteSUI(player, sceneObject, FrsManager::SUI_CHAL_VOTE_ISSUE, enclaveType);
	} else if (terminalType == DARK_CHALLENGE) {
		if (selectedID == 69)
			frsManager->sendArenaChallengeSUI(player, sceneObject, FrsManager::SUI_ARENA_CHAL_SCORES, enclaveType);
		else if (selectedID == 70)
			frsManager->sendArenaChallengeSUI(player, sceneObject, FrsManager::SUI_ARENA_CHAL_STATUS, enclaveType);
		else if (selectedID == 71)
			frsManager->sendArenaChallengeSUI(player, sceneObject, FrsManager::SUI_ARENA_CHAL_VIEW, enclaveType);
		else if (selectedID == 72)
			frsManager->sendArenaChallengeSUI(player, sceneObject, FrsManager::SUI_ARENA_CHAL_ACCEPT, enclaveType);
		else if (selectedID == 73)
			frsManager->sendArenaChallengeSUI(player, sceneObject, FrsManager::SUI_ARENA_CHAL_ISSUE, enclaveType);
#if FRS_TESTING
		else if (selectedID == 76 && ghost->isPrivileged())
			frsManager->forceArenaOpen(player);
#endif
	}

	return 0;
}

int EnclaveTerminalMenuComponent::getTerminalType(SceneObject* terminal) const {
	if (terminal == nullptr)
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
