/*
Copyright (C) 2007 <SWGEmu>

This File is part of Core3.

This program is free software; you can redistribute
it and/or modify it under the terms of the GNU Lesser
General Public License as published by the Free Software
Foundation; either version 2 of the License,
or (at your option) any later version.

This program is distributed in the hope that it will be useful,
but WITHOUT ANY WARRANTY; without even the implied warranty of
MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.
See the GNU Lesser General Public License for
more details.

You should have received a copy of the GNU Lesser General
Public License along with this program; if not, write to
the Free Software Foundation, Inc., 51 Franklin St, Fifth Floor, Boston, MA 02110-1301 USA

Linking Engine3 statically or dynamically with other modules
is making a combined work based on Engine3.
Thus, the terms and conditions of the GNU Lesser General Public License
cover the whole combination.

In addition, as a special exception, the copyright holders of Engine3
give you permission to combine Engine3 program with free software
programs or libraries that are released under the GNU LGPL and with
code included in the standard release of Core3 under the GNU LGPL
license (or modified versions of such code, with unchanged license).
You may copy and distribute such a system following the terms of the
GNU LGPL for Engine3 and the licenses of the other code concerned,
provided that you include the source code of that other code when
and as the GNU LGPL requires distribution of source code.

Note that people who make modified versions of Engine3 are not obligated
to grant this special exception for their modified versions;
it is their choice whether to do so. The GNU Lesser General Public License
gives permission to release a modified version without this exception;
this exception also makes it possible to release a modified version
which carries forward this exception.
*/

#include "CommandConfigManager.h"

#include "server/zone/objects/creature/commands/commands.h"
#include "server/zone/objects/creature/CreatureState.h"
#include "server/zone/objects/creature/CreaturePosture.h"


#include "server/zone/ZoneProcessServer.h"
#include "CommandList.h"

CommandList* CommandConfigManager::slashCommands = NULL;
ZoneProcessServer* CommandConfigManager::server = NULL;

CommandConfigManager::CommandConfigManager(ZoneProcessServer* serv) {
	server = serv;

	init();

	registerFunctions();
	registerGlobals();
}

void CommandConfigManager::registerSpecialCommands() {
	QueueCommand* admin = new QueueCommand("admin", server);
	slashCommands->put(admin);

	QueueCommand* req = new RequestQuestTimersAndCountersCommand("requestquesttimersandcounters", server);
	slashCommands->put(req);
}

void CommandConfigManager::registerFunctions() {
	//lua generic
	lua_register(getLuaState(), "RunSlashCommandsFile", runSlashCommandsFile);

	//AddSkills

	lua_register(getLuaState(), "AddActionShot1Command", addActionShot1Command);
	lua_register(getLuaState(), "AddActionShot2Command", addActionShot2Command);
	lua_register(getLuaState(), "AddActivateCloneCommand", addActivateCloneCommand);
	lua_register(getLuaState(), "AddActivateQuestCommand", addActivateQuestCommand);
	lua_register(getLuaState(), "AddAddAllowedPlayerCommand", addAddAllowedPlayerCommand);
	lua_register(getLuaState(), "AddAddBannedPlayerCommand", addAddBannedPlayerCommand);
	lua_register(getLuaState(), "AddAddFriendCommand", addAddFriendCommand);
	lua_register(getLuaState(), "AddAddIgnoreCommand", addAddIgnoreCommand);
	lua_register(getLuaState(), "AddAddMapLocationCommand", addAddMapLocationCommand);
	lua_register(getLuaState(), "AddAddPowerCommand", addAddPowerCommand);
	lua_register(getLuaState(), "AddAdjustLotCountCommand", addAdjustLotCountCommand);
	lua_register(getLuaState(), "AddAiIgnoreCommand", addAiIgnoreCommand);
	lua_register(getLuaState(), "AddAimCommand", addAimCommand);
	lua_register(getLuaState(), "AddAlertCommand", addAlertCommand);
	lua_register(getLuaState(), "AddAnimalAttackCommand", addAnimalAttackCommand);
	lua_register(getLuaState(), "AddAnimalCalmCommand", addAnimalCalmCommand);
	lua_register(getLuaState(), "AddAnimalScareCommand", addAnimalScareCommand);
	lua_register(getLuaState(), "AddAnonCommand", addAnonCommand);
	lua_register(getLuaState(), "AddApplyDiseaseCommand", addApplyDiseaseCommand);
	lua_register(getLuaState(), "AddApplyPoisonCommand", addApplyPoisonCommand);
	lua_register(getLuaState(), "AddApplyPowerupCommand", addApplyPowerupCommand);
	lua_register(getLuaState(), "AddAreatrackCommand", addAreatrackCommand);
	lua_register(getLuaState(), "AddAssignDroidCommand", addAssignDroidCommand);
	lua_register(getLuaState(), "AddAssistCommand", addAssistCommand);
	lua_register(getLuaState(), "AddAssociateDroidControlDeviceWithShipCommand", addAssociateDroidControlDeviceWithShipCommand);
	lua_register(getLuaState(), "AddAttackCommand", addAttackCommand);
	lua_register(getLuaState(), "AddAuctionCommand", addAuctionCommand);
	lua_register(getLuaState(), "AddAuctionAcceptCommand", addAuctionAcceptCommand);
	lua_register(getLuaState(), "AddAuctionBidCommand", addAuctionBidCommand);
	lua_register(getLuaState(), "AddAuctionCancelCommand", addAuctionCancelCommand);
	lua_register(getLuaState(), "AddAuctionCreateCommand", addAuctionCreateCommand);
	lua_register(getLuaState(), "AddAuctionQueryCommand", addAuctionQueryCommand);
	lua_register(getLuaState(), "AddAuctionRetrieveCommand", addAuctionRetrieveCommand);
	lua_register(getLuaState(), "AddAuctionsayCommand", addAuctionsayCommand);
	lua_register(getLuaState(), "AddAvoidIncapacitationCommand", addAvoidIncapacitationCommand);
	lua_register(getLuaState(), "AddBandFlourishCommand", addBandFlourishCommand);
	lua_register(getLuaState(), "AddBattlefieldStatusCommand", addBattlefieldStatusCommand);
	lua_register(getLuaState(), "AddBerserk1Command", addBerserk1Command);
	lua_register(getLuaState(), "AddBerserk2Command", addBerserk2Command);
	lua_register(getLuaState(), "AddBetCommand", addBetCommand);
	lua_register(getLuaState(), "AddBleedingShotCommand", addBleedingShotCommand);
	lua_register(getLuaState(), "AddBlindAttackCommand", addBlindAttackCommand);
	lua_register(getLuaState(), "AddBoardShuttleCommand", addBoardShuttleCommand);
	lua_register(getLuaState(), "AddBodyShot1Command", addBodyShot1Command);
	lua_register(getLuaState(), "AddBodyShot2Command", addBodyShot2Command);
	lua_register(getLuaState(), "AddBodyShot3Command", addBodyShot3Command);
	lua_register(getLuaState(), "AddBoostmoraleCommand", addBoostmoraleCommand);
	lua_register(getLuaState(), "AddBroadcastCommand", addBroadcastCommand);
	lua_register(getLuaState(), "AddBroadcastAreaCommand", addBroadcastAreaCommand);
	lua_register(getLuaState(), "AddBroadcastGalaxyCommand", addBroadcastGalaxyCommand);
	lua_register(getLuaState(), "AddBroadcastPlanetCommand", addBroadcastPlanetCommand);
	lua_register(getLuaState(), "AddBurstRunCommand", addBurstRunCommand);
	lua_register(getLuaState(), "AddBurstShot1Command", addBurstShot1Command);
	lua_register(getLuaState(), "AddBurstShot2Command", addBurstShot2Command);
	lua_register(getLuaState(), "AddCancelCraftingSessionCommand", addCancelCraftingSessionCommand);
	lua_register(getLuaState(), "AddCenterOfBeingCommand", addCenterOfBeingCommand);
	lua_register(getLuaState(), "AddChangeBandMusicCommand", addChangeBandMusicCommand);
	lua_register(getLuaState(), "AddChangeDanceCommand", addChangeDanceCommand);
	lua_register(getLuaState(), "AddChangeMusicCommand", addChangeMusicCommand);
	lua_register(getLuaState(), "AddChannelForceCommand", addChannelForceCommand);
	lua_register(getLuaState(), "AddChargeShot1Command", addChargeShot1Command);
	lua_register(getLuaState(), "AddChargeShot2Command", addChargeShot2Command);
	lua_register(getLuaState(), "AddCheckForceStatusCommand", addCheckForceStatusCommand);
	lua_register(getLuaState(), "AddCitybanCommand", addCitybanCommand);
	lua_register(getLuaState(), "AddCitypardonCommand", addCitypardonCommand);
	lua_register(getLuaState(), "AddClaimVeteranRewardCommand", addClaimVeteranRewardCommand);
	lua_register(getLuaState(), "AddClearCompletedQuestCommand", addClearCompletedQuestCommand);
	lua_register(getLuaState(), "AddClearVeteranRewardCommand", addClearVeteranRewardCommand);
	lua_register(getLuaState(), "AddClientQualifiedForSkillCommand", addClientQualifiedForSkillCommand);
	lua_register(getLuaState(), "AddCloneCommand", addCloneCommand);
	lua_register(getLuaState(), "AddCloseContainerCommand", addCloseContainerCommand);
	lua_register(getLuaState(), "AddColorlightsCommand", addColorlightsCommand);
	lua_register(getLuaState(), "AddCombatCommand", addCombatCommand);
	lua_register(getLuaState(), "AddCombatEscapeCommand", addCombatEscapeCommand);
	lua_register(getLuaState(), "AddCombatModeCheckCommand", addCombatModeCheckCommand);
	lua_register(getLuaState(), "AddCombatSpamCommand", addCombatSpamCommand);
	lua_register(getLuaState(), "AddCombatTargetCommand", addCombatTargetCommand);
	lua_register(getLuaState(), "AddCompleteQuestCommand", addCompleteQuestCommand);
	lua_register(getLuaState(), "AddConcealCommand", addConcealCommand);
	lua_register(getLuaState(), "AddConcealShotCommand", addConcealShotCommand);
	lua_register(getLuaState(), "AddConfusionShotCommand", addConfusionShotCommand);
	lua_register(getLuaState(), "AddConsentCommand", addConsentCommand);
	lua_register(getLuaState(), "AddCorpseCommand", addCorpseCommand);
	lua_register(getLuaState(), "AddCounterAttackCommand", addCounterAttackCommand);
	lua_register(getLuaState(), "AddCoupDeGraceCommand", addCoupDeGraceCommand);
	lua_register(getLuaState(), "AddCraftCommand", addCraftCommand);
	lua_register(getLuaState(), "AddCreateCreatureCommand", addCreateCreatureCommand);
	lua_register(getLuaState(), "AddCreateManfSchematicCommand", addCreateManfSchematicCommand);
	lua_register(getLuaState(), "AddCreateMissionElementCommand", addCreateMissionElementCommand);
	lua_register(getLuaState(), "AddCreateNPCCommand", addCreateNPCCommand);
	lua_register(getLuaState(), "AddCreatePrototypeCommand", addCreatePrototypeCommand);
	lua_register(getLuaState(), "AddCreateSpawningElementCommand", addCreateSpawningElementCommand);
	lua_register(getLuaState(), "AddCreateSpawningElementWithDifficultyCommand", addCreateSpawningElementWithDifficultyCommand);
	lua_register(getLuaState(), "AddCreatureAreaAttackCommand", addCreatureAreaAttackCommand);
	lua_register(getLuaState(), "AddCreatureAreaBleedingCommand", addCreatureAreaBleedingCommand);
	lua_register(getLuaState(), "AddCreatureAreaComboCommand", addCreatureAreaComboCommand);
	lua_register(getLuaState(), "AddCreatureAreaDiseaseCommand", addCreatureAreaDiseaseCommand);
	lua_register(getLuaState(), "AddCreatureAreaKnockdownCommand", addCreatureAreaKnockdownCommand);
	lua_register(getLuaState(), "AddCreatureAreaPoisonCommand", addCreatureAreaPoisonCommand);
	lua_register(getLuaState(), "AddCreditsCommand", addCreditsCommand);
	lua_register(getLuaState(), "AddCripplingShotCommand", addCripplingShotCommand);
	lua_register(getLuaState(), "AddCsAppendCommentCommand", addCsAppendCommentCommand);
	lua_register(getLuaState(), "AddCsCancelTicketCommand", addCsCancelTicketCommand);
	lua_register(getLuaState(), "AddCsConnectPlayerCommand", addCsConnectPlayerCommand);
	lua_register(getLuaState(), "AddCsCreateTicketCommand", addCsCreateTicketCommand);
	lua_register(getLuaState(), "AddCsDisconnectPlayerCommand", addCsDisconnectPlayerCommand);
	lua_register(getLuaState(), "AddCsGetArticleCommand", addCsGetArticleCommand);
	lua_register(getLuaState(), "AddCsGetCommentsCommand", addCsGetCommentsCommand);
	lua_register(getLuaState(), "AddCsGetTicketsCommand", addCsGetTicketsCommand);
	lua_register(getLuaState(), "AddCsRequestCategoriesCommand", addCsRequestCategoriesCommand);
	lua_register(getLuaState(), "AddCsSearchKnowledgeBaseCommand", addCsSearchKnowledgeBaseCommand);
	lua_register(getLuaState(), "AddCuiConsentResponseCommand", addCuiConsentResponseCommand);
	lua_register(getLuaState(), "AddCureDiseaseCommand", addCureDiseaseCommand);
	lua_register(getLuaState(), "AddCurePoisonCommand", addCurePoisonCommand);
	lua_register(getLuaState(), "AddCustomizeDroidCommand", addCustomizeDroidCommand);
	lua_register(getLuaState(), "AddCustomizeVehicleCommand", addCustomizeVehicleCommand);
	lua_register(getLuaState(), "AddDatabaseCommand", addDatabaseCommand);
	lua_register(getLuaState(), "AddDazzleCommand", addDazzleCommand);
	lua_register(getLuaState(), "AddDeactivateQuestCommand", addDeactivateQuestCommand);
	lua_register(getLuaState(), "AddDeathBlowCommand", addDeathBlowCommand);
	lua_register(getLuaState(), "AddDeathCountCommand", addDeathCountCommand);
	lua_register(getLuaState(), "AddDeclareOvertCommand", addDeclareOvertCommand);
	lua_register(getLuaState(), "AddDeclareresidenceCommand", addDeclareresidenceCommand);
	lua_register(getLuaState(), "AddDeclineCommand", addDeclineCommand);
	lua_register(getLuaState(), "AddDefaultAttackCommand", addDefaultAttackCommand);
	lua_register(getLuaState(), "AddDefuseMinefieldCommand", addDefuseMinefieldCommand);
	lua_register(getLuaState(), "AddDelegateFactionPointsCommand", addDelegateFactionPointsCommand);
	lua_register(getLuaState(), "AddDenyServiceCommand", addDenyServiceCommand);
	lua_register(getLuaState(), "AddDeployTrapCommand", addDeployTrapCommand);
	lua_register(getLuaState(), "AddDestroyCommand", addDestroyCommand);
	lua_register(getLuaState(), "AddDestroystructureCommand", addDestroystructureCommand);
	lua_register(getLuaState(), "AddDetonateDroidCommand", addDetonateDroidCommand);
	lua_register(getLuaState(), "AddDiagnoseCommand", addDiagnoseCommand);
	lua_register(getLuaState(), "AddDisarmingShot1Command", addDisarmingShot1Command);
	lua_register(getLuaState(), "AddDisarmingShot2Command", addDisarmingShot2Command);
	lua_register(getLuaState(), "AddDisbandCommand", addDisbandCommand);
	lua_register(getLuaState(), "AddDismissGroupMemberCommand", addDismissGroupMemberCommand);
	lua_register(getLuaState(), "AddDismountCommand", addDismountCommand);
	lua_register(getLuaState(), "AddDismountandstoreCommand", addDismountandstoreCommand);
	lua_register(getLuaState(), "AddDistractCommand", addDistractCommand);
	lua_register(getLuaState(), "AddDiveShotCommand", addDiveShotCommand);
	lua_register(getLuaState(), "AddDizzyAttackCommand", addDizzyAttackCommand);
	lua_register(getLuaState(), "AddDoubleTapCommand", addDoubleTapCommand);
	lua_register(getLuaState(), "AddDragIncapacitatedPlayerCommand", addDragIncapacitatedPlayerCommand);
	lua_register(getLuaState(), "AddDrainForceCommand", addDrainForceCommand);
	lua_register(getLuaState(), "AddDuelCommand", addDuelCommand);
	lua_register(getLuaState(), "AddDumpTargetInformationCommand", addDumpTargetInformationCommand);
	lua_register(getLuaState(), "AddDumpZoneInformationCommand", addDumpZoneInformationCommand);
	lua_register(getLuaState(), "AddEatCommand", addEatCommand);
	lua_register(getLuaState(), "AddEditAppearanceCommand", addEditAppearanceCommand);
	lua_register(getLuaState(), "AddEditBankCommand", addEditBankCommand);
	lua_register(getLuaState(), "AddEditBankAccountCommand", addEditBankAccountCommand);
	lua_register(getLuaState(), "AddEditStatsCommand", addEditStatsCommand);
	lua_register(getLuaState(), "AddEmboldenpetsCommand", addEmboldenpetsCommand);
	lua_register(getLuaState(), "AddEmptyMailTargetCommand", addEmptyMailTargetCommand);
	lua_register(getLuaState(), "AddEndDuelCommand", addEndDuelCommand);
	lua_register(getLuaState(), "AddEnragepetsCommand", addEnragepetsCommand);
	lua_register(getLuaState(), "AddEquilibriumCommand", addEquilibriumCommand);
	lua_register(getLuaState(), "AddExecuteKnowledgeBaseMessageCommand", addExecuteKnowledgeBaseMessageCommand);
	lua_register(getLuaState(), "AddExtinguishFireCommand", addExtinguishFireCommand);
	lua_register(getLuaState(), "AddExtractObjectCommand", addExtractObjectCommand);
	lua_register(getLuaState(), "AddEyeShotCommand", addEyeShotCommand);
	lua_register(getLuaState(), "AddFactoryCrateSplitCommand", addFactoryCrateSplitCommand);
	lua_register(getLuaState(), "AddFanShotCommand", addFanShotCommand);
	lua_register(getLuaState(), "AddFastBlastCommand", addFastBlastCommand);
	lua_register(getLuaState(), "AddFeignDeathCommand", addFeignDeathCommand);
	lua_register(getLuaState(), "AddFindCommand", addFindCommand);
	lua_register(getLuaState(), "AddFindFriendCommand", addFindFriendCommand);
	lua_register(getLuaState(), "AddFindMyTrainerCommand", addFindMyTrainerCommand);
	lua_register(getLuaState(), "AddFindObjectCommand", addFindObjectCommand);
	lua_register(getLuaState(), "AddFindPlayerCommand", addFindPlayerCommand);
	lua_register(getLuaState(), "AddFireAcidCone1Command", addFireAcidCone1Command);
	lua_register(getLuaState(), "AddFireAcidCone2Command", addFireAcidCone2Command);
	lua_register(getLuaState(), "AddFireAcidSingle1Command", addFireAcidSingle1Command);
	lua_register(getLuaState(), "AddFireAcidSingle2Command", addFireAcidSingle2Command);
	lua_register(getLuaState(), "AddFireHeavyWeaponCommand", addFireHeavyWeaponCommand);
	lua_register(getLuaState(), "AddFirejetCommand", addFirejetCommand);
	lua_register(getLuaState(), "AddFireLightningCone1Command", addFireLightningCone1Command);
	lua_register(getLuaState(), "AddFireLightningCone2Command", addFireLightningCone2Command);
	lua_register(getLuaState(), "AddFireLightningSingle1Command", addFireLightningSingle1Command);
	lua_register(getLuaState(), "AddFireLightningSingle2Command", addFireLightningSingle2Command);
	lua_register(getLuaState(), "AddFirstAidCommand", addFirstAidCommand);
	lua_register(getLuaState(), "AddFishCommand", addFishCommand);
	lua_register(getLuaState(), "AddFlameCone1Command", addFlameCone1Command);
	lua_register(getLuaState(), "AddFlameCone2Command", addFlameCone2Command);
	lua_register(getLuaState(), "AddFlameSingle1Command", addFlameSingle1Command);
	lua_register(getLuaState(), "AddFlameSingle2Command", addFlameSingle2Command);
	lua_register(getLuaState(), "AddFlashSpeederCommand", addFlashSpeederCommand);
	lua_register(getLuaState(), "AddFlourishCommand", addFlourishCommand);
	lua_register(getLuaState(), "AddFlurryShot1Command", addFlurryShot1Command);
	lua_register(getLuaState(), "AddFlurryShot2Command", addFlurryShot2Command);
	lua_register(getLuaState(), "AddFlushingShot1Command", addFlushingShot1Command);
	lua_register(getLuaState(), "AddFlushingShot2Command", addFlushingShot2Command);
	lua_register(getLuaState(), "AddForageCommand", addForageCommand);
	lua_register(getLuaState(), "AddForceAbsorb1Command", addForceAbsorb1Command);
	lua_register(getLuaState(), "AddForceAbsorb2Command", addForceAbsorb2Command);
	lua_register(getLuaState(), "AddForceArmor1Command", addForceArmor1Command);
	lua_register(getLuaState(), "AddForceArmor2Command", addForceArmor2Command);
	lua_register(getLuaState(), "AddForceChokeCommand", addForceChokeCommand);
	lua_register(getLuaState(), "AddForceCommandCommand", addForceCommandCommand);
	lua_register(getLuaState(), "AddForceCureDiseaseCommand", addForceCureDiseaseCommand);
	lua_register(getLuaState(), "AddForceCurePoisonCommand", addForceCurePoisonCommand);
	lua_register(getLuaState(), "AddForceFeedback1Command", addForceFeedback1Command);
	lua_register(getLuaState(), "AddForceFeedback2Command", addForceFeedback2Command);
	lua_register(getLuaState(), "AddForceIntimidate1Command", addForceIntimidate1Command);
	lua_register(getLuaState(), "AddForceIntimidate2Command", addForceIntimidate2Command);
	lua_register(getLuaState(), "AddForceKnockdown1Command", addForceKnockdown1Command);
	lua_register(getLuaState(), "AddForceKnockdown2Command", addForceKnockdown2Command);
	lua_register(getLuaState(), "AddForceKnockdown3Command", addForceKnockdown3Command);
	lua_register(getLuaState(), "AddForceLightningCone1Command", addForceLightningCone1Command);
	lua_register(getLuaState(), "AddForceLightningCone2Command", addForceLightningCone2Command);
	lua_register(getLuaState(), "AddForceLightningSingle1Command", addForceLightningSingle1Command);
	lua_register(getLuaState(), "AddForceLightningSingle2Command", addForceLightningSingle2Command);
	lua_register(getLuaState(), "AddForceMeditateCommand", addForceMeditateCommand);
	lua_register(getLuaState(), "AddForceOfWillCommand", addForceOfWillCommand);
	lua_register(getLuaState(), "AddForceProtectionCommand", addForceProtectionCommand);
	lua_register(getLuaState(), "AddForceResistBleedingCommand", addForceResistBleedingCommand);
	lua_register(getLuaState(), "AddForceResistDiseaseCommand", addForceResistDiseaseCommand);
	lua_register(getLuaState(), "AddForceResistPoisonCommand", addForceResistPoisonCommand);
	lua_register(getLuaState(), "AddForceResistStatesCommand", addForceResistStatesCommand);
	lua_register(getLuaState(), "AddForceRun1Command", addForceRun1Command);
	lua_register(getLuaState(), "AddForceRun2Command", addForceRun2Command);
	lua_register(getLuaState(), "AddForceRun3Command", addForceRun3Command);
	lua_register(getLuaState(), "AddForceShield1Command", addForceShield1Command);
	lua_register(getLuaState(), "AddForceShield2Command", addForceShield2Command);
	lua_register(getLuaState(), "AddForceSpeed1Command", addForceSpeed1Command);
	lua_register(getLuaState(), "AddForceSpeed2Command", addForceSpeed2Command);
	lua_register(getLuaState(), "AddForceThrow1Command", addForceThrow1Command);
	lua_register(getLuaState(), "AddForceThrow2Command", addForceThrow2Command);
	lua_register(getLuaState(), "AddForceWeaken1Command", addForceWeaken1Command);
	lua_register(getLuaState(), "AddForceWeaken2Command", addForceWeaken2Command);
	lua_register(getLuaState(), "AddFormupCommand", addFormupCommand);
	lua_register(getLuaState(), "AddFreezePlayerCommand", addFreezePlayerCommand);
	lua_register(getLuaState(), "AddFullAutoArea1Command", addFullAutoArea1Command);
	lua_register(getLuaState(), "AddFullAutoArea2Command", addFullAutoArea2Command);
	lua_register(getLuaState(), "AddFullAutoSingle1Command", addFullAutoSingle1Command);
	lua_register(getLuaState(), "AddFullAutoSingle2Command", addFullAutoSingle2Command);
	lua_register(getLuaState(), "AddGCommand", addGCommand);
	lua_register(getLuaState(), "AddGallopCommand", addGallopCommand);
	lua_register(getLuaState(), "AddGallopStopCommand", addGallopStopCommand);
	lua_register(getLuaState(), "AddGcCommand", addGcCommand);
	lua_register(getLuaState(), "AddGcwStatusCommand", addGcwStatusCommand);
	lua_register(getLuaState(), "AddGenerateCraftedItemCommand", addGenerateCraftedItemCommand);
	lua_register(getLuaState(), "AddGetAccountInfoCommand", addGetAccountInfoCommand);
	lua_register(getLuaState(), "AddGetAttributesCommand", addGetAttributesCommand);
	lua_register(getLuaState(), "AddGetAttributesBatchCommand", addGetAttributesBatchCommand);
	lua_register(getLuaState(), "AddGetFriendListCommand", addGetFriendListCommand);
	lua_register(getLuaState(), "AddGetGameTimeCommand", addGetGameTimeCommand);
	lua_register(getLuaState(), "AddGetIgnoreListCommand", addGetIgnoreListCommand);
	lua_register(getLuaState(), "AddGetMapLocationsCommand", addGetMapLocationsCommand);
	lua_register(getLuaState(), "AddGetObjVarsCommand", addGetObjVarsCommand);
	lua_register(getLuaState(), "AddGetPlayerIdCommand", addGetPlayerIdCommand);
	lua_register(getLuaState(), "AddGetPrototypeCommand", addGetPrototypeCommand);
	lua_register(getLuaState(), "AddGetRankCommand", addGetRankCommand);
	lua_register(getLuaState(), "AddGetSpawnDelaysCommand", addGetSpawnDelaysCommand);
	lua_register(getLuaState(), "AddGetStationNameCommand", addGetStationNameCommand);
	lua_register(getLuaState(), "AddGetVeteranRewardTimeCommand", addGetVeteranRewardTimeCommand);
	lua_register(getLuaState(), "AddGetVeteranRewardTimeCsCommand", addGetVeteranRewardTimeCsCommand);
	lua_register(getLuaState(), "AddGiveItemCommand", addGiveItemCommand);
	lua_register(getLuaState(), "AddGiveMaintenanceToVendorCommand", addGiveMaintenanceToVendorCommand);
	lua_register(getLuaState(), "AddGivevendormaintCommand", addGivevendormaintCommand);
	lua_register(getLuaState(), "AddGmForceCommandCommand", addGmForceCommandCommand);
	lua_register(getLuaState(), "AddGmCreateClassResourceCommand", addGmCreateClassResourceCommand);
	lua_register(getLuaState(), "AddGmCreateSpecificResourceCommand", addGmCreateSpecificResourceCommand);
	lua_register(getLuaState(), "AddGmForceRankCommand", addGmForceRankCommand);
	lua_register(getLuaState(), "AddGmFsVillageCommand", addGmFsVillageCommand);
	lua_register(getLuaState(), "AddGmJediStateCommand", addGmJediStateCommand);
	lua_register(getLuaState(), "AddGmReviveCommand", addGmReviveCommand);
	lua_register(getLuaState(), "AddGotoCommand", addGotoCommand);
	lua_register(getLuaState(), "AddGrantBadgeCommand", addGrantBadgeCommand);
	lua_register(getLuaState(), "AddGrantPadawanTrialsEligibilityCommand", addGrantPadawanTrialsEligibilityCommand);
	lua_register(getLuaState(), "AddGrantSkillCommand", addGrantSkillCommand);
	lua_register(getLuaState(), "AddGrantTitleCommand", addGrantTitleCommand);
	lua_register(getLuaState(), "AddGrantZoningRightsCommand", addGrantZoningRightsCommand);
	lua_register(getLuaState(), "AddGroupChatCommand", addGroupChatCommand);
	lua_register(getLuaState(), "AddGroupSayCommand", addGroupSayCommand);
	lua_register(getLuaState(), "AddGsayCommand", addGsayCommand);
	lua_register(getLuaState(), "AddGtellCommand", addGtellCommand);
	lua_register(getLuaState(), "AddGuildCommand", addGuildCommand);
	lua_register(getLuaState(), "AddGuildremoveCommand", addGuildremoveCommand);
	lua_register(getLuaState(), "AddGuildsayCommand", addGuildsayCommand);
	lua_register(getLuaState(), "AddGuildstatusCommand", addGuildstatusCommand);
	lua_register(getLuaState(), "AddHarmfulCommand", addHarmfulCommand);
	lua_register(getLuaState(), "AddHarmlessCommand", addHarmlessCommand);
	lua_register(getLuaState(), "AddHarvestCorpseCommand", addHarvestCorpseCommand);
	lua_register(getLuaState(), "AddHarvesterActivateCommand", addHarvesterActivateCommand);
	lua_register(getLuaState(), "AddHarvesterDeactivateCommand", addHarvesterDeactivateCommand);
	lua_register(getLuaState(), "AddHarvesterDiscardHopperCommand", addHarvesterDiscardHopperCommand);
	lua_register(getLuaState(), "AddHarvesterGetResourceDataCommand", addHarvesterGetResourceDataCommand);
	lua_register(getLuaState(), "AddHarvesterHarvestCommand", addHarvesterHarvestCommand);
	lua_register(getLuaState(), "AddHarvesterMakeCrateCommand", addHarvesterMakeCrateCommand);
	lua_register(getLuaState(), "AddHarvesterSelectResourceCommand", addHarvesterSelectResourceCommand);
	lua_register(getLuaState(), "AddHarvesterTakeSurveyCommand", addHarvesterTakeSurveyCommand);
	lua_register(getLuaState(), "AddHasVeteranRewardCommand", addHasVeteranRewardCommand);
	lua_register(getLuaState(), "AddHaveconsentCommand", addHaveconsentCommand);
	lua_register(getLuaState(), "AddHeadShot1Command", addHeadShot1Command);
	lua_register(getLuaState(), "AddHeadShot2Command", addHeadShot2Command);
	lua_register(getLuaState(), "AddHeadShot3Command", addHeadShot3Command);
	lua_register(getLuaState(), "AddHealActionSelf1Command", addHealActionSelf1Command);
	lua_register(getLuaState(), "AddHealActionSelf2Command", addHealActionSelf2Command);
	lua_register(getLuaState(), "AddHealActionWoundOther1Command", addHealActionWoundOther1Command);
	lua_register(getLuaState(), "AddHealActionWoundOther2Command", addHealActionWoundOther2Command);
	lua_register(getLuaState(), "AddHealActionWoundSelf1Command", addHealActionWoundSelf1Command);
	lua_register(getLuaState(), "AddHealActionWoundSelf2Command", addHealActionWoundSelf2Command);
	lua_register(getLuaState(), "AddHealAllOther1Command", addHealAllOther1Command);
	lua_register(getLuaState(), "AddHealAllOther2Command", addHealAllOther2Command);
	lua_register(getLuaState(), "AddHealAllSelf1Command", addHealAllSelf1Command);
	lua_register(getLuaState(), "AddHealAllSelf2Command", addHealAllSelf2Command);
	lua_register(getLuaState(), "AddHealBattleFatigueOther1Command", addHealBattleFatigueOther1Command);
	lua_register(getLuaState(), "AddHealBattleFatigueOther2Command", addHealBattleFatigueOther2Command);
	lua_register(getLuaState(), "AddHealBattleFatigueSelf1Command", addHealBattleFatigueSelf1Command);
	lua_register(getLuaState(), "AddHealBattleFatigueSelf2Command", addHealBattleFatigueSelf2Command);
	lua_register(getLuaState(), "AddHealDamageCommand", addHealDamageCommand);
	lua_register(getLuaState(), "AddHealDroidDamageCommand", addHealDroidDamageCommand);
	lua_register(getLuaState(), "AddHealDroidWoundCommand", addHealDroidWoundCommand);
	lua_register(getLuaState(), "AddHealEnhanceCommand", addHealEnhanceCommand);
	lua_register(getLuaState(), "AddHealHealthSelf1Command", addHealHealthSelf1Command);
	lua_register(getLuaState(), "AddHealHealthSelf2Command", addHealHealthSelf2Command);
	lua_register(getLuaState(), "AddHealHealthWoundOther1Command", addHealHealthWoundOther1Command);
	lua_register(getLuaState(), "AddHealHealthWoundOther2Command", addHealHealthWoundOther2Command);
	lua_register(getLuaState(), "AddHealHealthWoundSelf1Command", addHealHealthWoundSelf1Command);
	lua_register(getLuaState(), "AddHealHealthWoundSelf2Command", addHealHealthWoundSelf2Command);
	lua_register(getLuaState(), "AddHealMindCommand", addHealMindCommand);
	lua_register(getLuaState(), "AddHealMindSelf1Command", addHealMindSelf1Command);
	lua_register(getLuaState(), "AddHealMindSelf2Command", addHealMindSelf2Command);
	lua_register(getLuaState(), "AddHealMindWoundOther1Command", addHealMindWoundOther1Command);
	lua_register(getLuaState(), "AddHealMindWoundOther2Command", addHealMindWoundOther2Command);
	lua_register(getLuaState(), "AddHealMindWoundSelf1Command", addHealMindWoundSelf1Command);
	lua_register(getLuaState(), "AddHealMindWoundSelf2Command", addHealMindWoundSelf2Command);
	lua_register(getLuaState(), "AddHealPetCommand", addHealPetCommand);
	lua_register(getLuaState(), "AddHealStateCommand", addHealStateCommand);
	lua_register(getLuaState(), "AddHealStatesOtherCommand", addHealStatesOtherCommand);
	lua_register(getLuaState(), "AddHealStatesSelfCommand", addHealStatesSelfCommand);
	lua_register(getLuaState(), "AddHealthShot1Command", addHealthShot1Command);
	lua_register(getLuaState(), "AddHealthShot2Command", addHealthShot2Command);
	lua_register(getLuaState(), "AddHealWoundCommand", addHealWoundCommand);
	lua_register(getLuaState(), "AddHoloEmoteCommand", addHoloEmoteCommand);
	lua_register(getLuaState(), "AddImagedesignCommand", addImagedesignCommand);
	lua_register(getLuaState(), "AddInitializeComponentCommand", addInitializeComponentCommand);
	lua_register(getLuaState(), "AddInnateCommand", addInnateCommand);
	lua_register(getLuaState(), "AddInsertItemIntoShipComponentSlotCommand", addInsertItemIntoShipComponentSlotCommand);
	lua_register(getLuaState(), "AddInstallMissionTerminalCommand", addInstallMissionTerminalCommand);
	lua_register(getLuaState(), "AddInstallShipComponentCommand", addInstallShipComponentCommand);
	lua_register(getLuaState(), "AddInsureCommand", addInsureCommand);
	lua_register(getLuaState(), "AddIntimidate1Command", addIntimidate1Command);
	lua_register(getLuaState(), "AddIntimidate2Command", addIntimidate2Command);
	lua_register(getLuaState(), "AddIntimidationAttackCommand", addIntimidationAttackCommand);
	lua_register(getLuaState(), "AddInviteCommand", addInviteCommand);
	lua_register(getLuaState(), "AddInvulnerableCommand", addInvulnerableCommand);
	lua_register(getLuaState(), "AddItemmovebackCommand", addItemmovebackCommand);
	lua_register(getLuaState(), "AddItemmovedownCommand", addItemmovedownCommand);
	lua_register(getLuaState(), "AddItemmoveforwardCommand", addItemmoveforwardCommand);
	lua_register(getLuaState(), "AddItemmoveupCommand", addItemmoveupCommand);
	lua_register(getLuaState(), "AddItemrotateleftCommand", addItemrotateleftCommand);
	lua_register(getLuaState(), "AddItemrotaterightCommand", addItemrotaterightCommand);
	lua_register(getLuaState(), "AddJediMindTrickCommand", addJediMindTrickCommand);
	lua_register(getLuaState(), "AddJoinCommand", addJoinCommand);
	lua_register(getLuaState(), "AddJoinGameCommand", addJoinGameCommand);
	lua_register(getLuaState(), "AddKickCommand", addKickCommand);
	lua_register(getLuaState(), "AddKillCommand", addKillCommand);
	lua_register(getLuaState(), "AddKillPlayerCommand", addKillPlayerCommand);
	lua_register(getLuaState(), "AddKipUpShotCommand", addKipUpShotCommand);
	lua_register(getLuaState(), "AddKneelCommand", addKneelCommand);
	lua_register(getLuaState(), "AddKnockdownAttackCommand", addKnockdownAttackCommand);
	lua_register(getLuaState(), "AddKnockdownFireCommand", addKnockdownFireCommand);
	lua_register(getLuaState(), "AddLagCommand", addLagCommand);
	lua_register(getLuaState(), "AddLastDitchCommand", addLastDitchCommand);
	lua_register(getLuaState(), "AddLaunchFireworkCommand", addLaunchFireworkCommand);
	lua_register(getLuaState(), "AddLeaveGameCommand", addLeaveGameCommand);
	lua_register(getLuaState(), "AddLeaveGroupCommand", addLeaveGroupCommand);
	lua_register(getLuaState(), "AddLegShot1Command", addLegShot1Command);
	lua_register(getLuaState(), "AddLegShot2Command", addLegShot2Command);
	lua_register(getLuaState(), "AddLegShot3Command", addLegShot3Command);
	lua_register(getLuaState(), "AddLfgCommand", addLfgCommand);
	lua_register(getLuaState(), "AddListActiveQuestsCommand", addListActiveQuestsCommand);
	lua_register(getLuaState(), "AddListCompletedQuestsCommand", addListCompletedQuestsCommand);
	lua_register(getLuaState(), "AddListenCommand", addListenCommand);
	lua_register(getLuaState(), "AddListGuildsCommand", addListGuildsCommand);
	lua_register(getLuaState(), "AddLogoutCommand", addLogoutCommand);
	lua_register(getLuaState(), "AddLootCommand", addLootCommand);
	lua_register(getLuaState(), "AddLootAiCorpseCommand", addLootAiCorpseCommand);
	lua_register(getLuaState(), "AddLootPlayerCorpseCommand", addLootPlayerCorpseCommand);
	lua_register(getLuaState(), "AddLowBlowCommand", addLowBlowCommand);
	lua_register(getLuaState(), "AddMakeLeaderCommand", addMakeLeaderCommand);
	lua_register(getLuaState(), "AddMakeSurveyCommand", addMakeSurveyCommand);
	lua_register(getLuaState(), "AddManufactureCommand", addManufactureCommand);
	lua_register(getLuaState(), "AddMaskscentCommand", addMaskscentCommand);
	lua_register(getLuaState(), "AddMaxCombatAbilityCommand", addMaxCombatAbilityCommand);
	lua_register(getLuaState(), "AddMaxStatsCommand", addMaxStatsCommand);
	lua_register(getLuaState(), "AddMedicalForageCommand", addMedicalForageCommand);
	lua_register(getLuaState(), "AddMeditateCommand", addMeditateCommand);
	lua_register(getLuaState(), "AddMediumDiseaseCommand", addMediumDiseaseCommand);
	lua_register(getLuaState(), "AddMediumPoisonCommand", addMediumPoisonCommand);
	lua_register(getLuaState(), "AddMelee1hBlindHit1Command", addMelee1hBlindHit1Command);
	lua_register(getLuaState(), "AddMelee1hBlindHit2Command", addMelee1hBlindHit2Command);
	lua_register(getLuaState(), "AddMelee1hBodyHit1Command", addMelee1hBodyHit1Command);
	lua_register(getLuaState(), "AddMelee1hBodyHit2Command", addMelee1hBodyHit2Command);
	lua_register(getLuaState(), "AddMelee1hBodyHit3Command", addMelee1hBodyHit3Command);
	lua_register(getLuaState(), "AddMelee1hDizzyHit1Command", addMelee1hDizzyHit1Command);
	lua_register(getLuaState(), "AddMelee1hDizzyHit2Command", addMelee1hDizzyHit2Command);
	lua_register(getLuaState(), "AddMelee1hHealthHit1Command", addMelee1hHealthHit1Command);
	lua_register(getLuaState(), "AddMelee1hHealthHit2Command", addMelee1hHealthHit2Command);
	lua_register(getLuaState(), "AddMelee1hHit1Command", addMelee1hHit1Command);
	lua_register(getLuaState(), "AddMelee1hHit2Command", addMelee1hHit2Command);
	lua_register(getLuaState(), "AddMelee1hHit3Command", addMelee1hHit3Command);
	lua_register(getLuaState(), "AddMelee1hLunge1Command", addMelee1hLunge1Command);
	lua_register(getLuaState(), "AddMelee1hLunge2Command", addMelee1hLunge2Command);
	lua_register(getLuaState(), "AddMelee1hScatterHit1Command", addMelee1hScatterHit1Command);
	lua_register(getLuaState(), "AddMelee1hScatterHit2Command", addMelee1hScatterHit2Command);
	lua_register(getLuaState(), "AddMelee1hSpinAttack1Command", addMelee1hSpinAttack1Command);
	lua_register(getLuaState(), "AddMelee1hSpinAttack2Command", addMelee1hSpinAttack2Command);
	lua_register(getLuaState(), "AddMelee2hArea1Command", addMelee2hArea1Command);
	lua_register(getLuaState(), "AddMelee2hArea2Command", addMelee2hArea2Command);
	lua_register(getLuaState(), "AddMelee2hArea3Command", addMelee2hArea3Command);
	lua_register(getLuaState(), "AddMelee2hHeadHit1Command", addMelee2hHeadHit1Command);
	lua_register(getLuaState(), "AddMelee2hHeadHit2Command", addMelee2hHeadHit2Command);
	lua_register(getLuaState(), "AddMelee2hHeadHit3Command", addMelee2hHeadHit3Command);
	lua_register(getLuaState(), "AddMelee2hHit1Command", addMelee2hHit1Command);
	lua_register(getLuaState(), "AddMelee2hHit2Command", addMelee2hHit2Command);
	lua_register(getLuaState(), "AddMelee2hHit3Command", addMelee2hHit3Command);
	lua_register(getLuaState(), "AddMelee2hLunge1Command", addMelee2hLunge1Command);
	lua_register(getLuaState(), "AddMelee2hLunge2Command", addMelee2hLunge2Command);
	lua_register(getLuaState(), "AddMelee2hMindHit1Command", addMelee2hMindHit1Command);
	lua_register(getLuaState(), "AddMelee2hMindHit2Command", addMelee2hMindHit2Command);
	lua_register(getLuaState(), "AddMelee2hSpinAttack1Command", addMelee2hSpinAttack1Command);
	lua_register(getLuaState(), "AddMelee2hSpinAttack2Command", addMelee2hSpinAttack2Command);
	lua_register(getLuaState(), "AddMelee2hSweep1Command", addMelee2hSweep1Command);
	lua_register(getLuaState(), "AddMelee2hSweep2Command", addMelee2hSweep2Command);
	lua_register(getLuaState(), "AddMildDiseaseCommand", addMildDiseaseCommand);
	lua_register(getLuaState(), "AddMildPoisonCommand", addMildPoisonCommand);
	lua_register(getLuaState(), "AddMindBlast1Command", addMindBlast1Command);
	lua_register(getLuaState(), "AddMindBlast2Command", addMindBlast2Command);
	lua_register(getLuaState(), "AddMindShot1Command", addMindShot1Command);
	lua_register(getLuaState(), "AddMindShot2Command", addMindShot2Command);
	lua_register(getLuaState(), "AddMoneyCommand", addMoneyCommand);
	lua_register(getLuaState(), "AddMountCommand", addMountCommand);
	lua_register(getLuaState(), "AddMoveFurnitureCommand", addMoveFurnitureCommand);
	lua_register(getLuaState(), "AddMultiTargetPistolShotCommand", addMultiTargetPistolShotCommand);
	lua_register(getLuaState(), "AddMultiTargetShotCommand", addMultiTargetShotCommand);
	lua_register(getLuaState(), "AddNameStructureCommand", addNameStructureCommand);
	lua_register(getLuaState(), "AddNewbiehelperCommand", addNewbiehelperCommand);
	lua_register(getLuaState(), "AddNewbieRequestStartingLocationsCommand", addNewbieRequestStartingLocationsCommand);
	lua_register(getLuaState(), "AddNewbieSelectStartingLocationCommand", addNewbieSelectStartingLocationCommand);
	lua_register(getLuaState(), "AddNextCraftingStageCommand", addNextCraftingStageCommand);
	lua_register(getLuaState(), "AddNpcCommand", addNpcCommand);
	lua_register(getLuaState(), "AddNpcConversationSelectCommand", addNpcConversationSelectCommand);
	lua_register(getLuaState(), "AddNpcConversationStartCommand", addNpcConversationStartCommand);
	lua_register(getLuaState(), "AddNpcConversationStopCommand", addNpcConversationStopCommand);
	lua_register(getLuaState(), "AddObjectCommand", addObjectCommand);
	lua_register(getLuaState(), "AddObjvarCommand", addObjvarCommand);
	lua_register(getLuaState(), "AddOpenContainerCommand", addOpenContainerCommand);
	lua_register(getLuaState(), "AddOverChargeShot1Command", addOverChargeShot1Command);
	lua_register(getLuaState(), "AddOverChargeShot2Command", addOverChargeShot2Command);
	lua_register(getLuaState(), "AddOverrideActiveMonthsCommand", addOverrideActiveMonthsCommand);
	lua_register(getLuaState(), "AddOverridePadawanTrialsEligibilityCommand", addOverridePadawanTrialsEligibilityCommand);
	lua_register(getLuaState(), "AddPanicShotCommand", addPanicShotCommand);
	lua_register(getLuaState(), "AddPauseDanceCommand", addPauseDanceCommand);
	lua_register(getLuaState(), "AddPauseMusicCommand", addPauseMusicCommand);
	lua_register(getLuaState(), "AddPaWithdrawCommand", addPaWithdrawCommand);
	lua_register(getLuaState(), "AddPaymaintenanceCommand", addPaymaintenanceCommand);
	lua_register(getLuaState(), "AddPeaceCommand", addPeaceCommand);
	lua_register(getLuaState(), "AddPermissionListModifyCommand", addPermissionListModifyCommand);
	lua_register(getLuaState(), "AddPistolMeleeDefense1Command", addPistolMeleeDefense1Command);
	lua_register(getLuaState(), "AddPistolMeleeDefense2Command", addPistolMeleeDefense2Command);
	lua_register(getLuaState(), "AddPlaceBattlefieldStructureCommand", addPlaceBattlefieldStructureCommand);
	lua_register(getLuaState(), "AddPlaceStructureCommand", addPlaceStructureCommand);
	lua_register(getLuaState(), "AddPlaceStructureModeCommand", addPlaceStructureModeCommand);
	lua_register(getLuaState(), "AddPlanetCommand", addPlanetCommand);
	lua_register(getLuaState(), "AddPlanetsayCommand", addPlanetsayCommand);
	lua_register(getLuaState(), "AddPlanetwarpCommand", addPlanetwarpCommand);
	lua_register(getLuaState(), "AddPlanetwarpTargetCommand", addPlanetwarpTargetCommand);
	lua_register(getLuaState(), "AddPointBlankArea1Command", addPointBlankArea1Command);
	lua_register(getLuaState(), "AddPointBlankArea2Command", addPointBlankArea2Command);
	lua_register(getLuaState(), "AddPointBlankSingle1Command", addPointBlankSingle1Command);
	lua_register(getLuaState(), "AddPointBlankSingle2Command", addPointBlankSingle2Command);
	lua_register(getLuaState(), "AddPolearmActionHit1Command", addPolearmActionHit1Command);
	lua_register(getLuaState(), "AddPolearmActionHit2Command", addPolearmActionHit2Command);
	lua_register(getLuaState(), "AddPolearmArea1Command", addPolearmArea1Command);
	lua_register(getLuaState(), "AddPolearmArea2Command", addPolearmArea2Command);
	lua_register(getLuaState(), "AddPolearmHit1Command", addPolearmHit1Command);
	lua_register(getLuaState(), "AddPolearmHit2Command", addPolearmHit2Command);
	lua_register(getLuaState(), "AddPolearmHit3Command", addPolearmHit3Command);
	lua_register(getLuaState(), "AddPolearmLegHit1Command", addPolearmLegHit1Command);
	lua_register(getLuaState(), "AddPolearmLegHit2Command", addPolearmLegHit2Command);
	lua_register(getLuaState(), "AddPolearmLegHit3Command", addPolearmLegHit3Command);
	lua_register(getLuaState(), "AddPolearmLunge1Command", addPolearmLunge1Command);
	lua_register(getLuaState(), "AddPolearmLunge2Command", addPolearmLunge2Command);
	lua_register(getLuaState(), "AddPolearmSpinAttack1Command", addPolearmSpinAttack1Command);
	lua_register(getLuaState(), "AddPolearmSpinAttack2Command", addPolearmSpinAttack2Command);
	lua_register(getLuaState(), "AddPolearmStun1Command", addPolearmStun1Command);
	lua_register(getLuaState(), "AddPolearmStun2Command", addPolearmStun2Command);
	lua_register(getLuaState(), "AddPolearmSweep1Command", addPolearmSweep1Command);
	lua_register(getLuaState(), "AddPolearmSweep2Command", addPolearmSweep2Command);
	lua_register(getLuaState(), "AddPostureDownAttackCommand", addPostureDownAttackCommand);
	lua_register(getLuaState(), "AddPostureUpAttackCommand", addPostureUpAttackCommand);
	lua_register(getLuaState(), "AddPowerBoostCommand", addPowerBoostCommand);
	lua_register(getLuaState(), "AddProneCommand", addProneCommand);
	lua_register(getLuaState(), "AddPurchaseReinforcementCommand", addPurchaseReinforcementCommand);
	lua_register(getLuaState(), "AddPurchaseTicketCommand", addPurchaseTicketCommand);
	lua_register(getLuaState(), "AddQuickHealCommand", addQuickHealCommand);
	lua_register(getLuaState(), "AddRallyCommand", addRallyCommand);
	lua_register(getLuaState(), "AddReconnectToTransferServerCommand", addReconnectToTransferServerCommand);
	lua_register(getLuaState(), "AddRecruitSkillTrainerCommand", addRecruitSkillTrainerCommand);
	lua_register(getLuaState(), "AddRegainConsciousnessCommand", addRegainConsciousnessCommand);
	lua_register(getLuaState(), "AddRegenerationCommand", addRegenerationCommand);
	lua_register(getLuaState(), "AddRegisterWithLocationCommand", addRegisterWithLocationCommand);
	lua_register(getLuaState(), "AddReloadCommand", addReloadCommand);
	lua_register(getLuaState(), "AddRemoteCommand", addRemoteCommand);
	lua_register(getLuaState(), "AddRemoveAllowedPlayerCommand", addRemoveAllowedPlayerCommand);
	lua_register(getLuaState(), "AddRemoveBannedPlayerCommand", addRemoveBannedPlayerCommand);
	lua_register(getLuaState(), "AddRemoveFriendCommand", addRemoveFriendCommand);
	lua_register(getLuaState(), "AddRemoveIgnoreCommand", addRemoveIgnoreCommand);
	lua_register(getLuaState(), "AddRepairBattlefieldStructureCommand", addRepairBattlefieldStructureCommand);
	lua_register(getLuaState(), "AddRepairShipComponentInSlotCommand", addRepairShipComponentInSlotCommand);
	lua_register(getLuaState(), "AddReportCommand", addReportCommand);
	lua_register(getLuaState(), "AddRequestBadgesCommand", addRequestBadgesCommand);
	lua_register(getLuaState(), "AddRequestBiographyCommand", addRequestBiographyCommand);
	lua_register(getLuaState(), "AddRequestCharacterMatchCommand", addRequestCharacterMatchCommand);
	lua_register(getLuaState(), "AddRequestCharacterSheetInfoCommand", addRequestCharacterSheetInfoCommand);
	lua_register(getLuaState(), "AddRequestCoreSampleCommand", addRequestCoreSampleCommand);
	lua_register(getLuaState(), "AddRequestCraftingSessionCommand", addRequestCraftingSessionCommand);
	lua_register(getLuaState(), "AddRequestDraftSlotsCommand", addRequestDraftSlotsCommand);
	lua_register(getLuaState(), "AddRequestDraftSlotsBatchCommand", addRequestDraftSlotsBatchCommand);
	lua_register(getLuaState(), "AddRequestManfSchematicSlotsCommand", addRequestManfSchematicSlotsCommand);
	lua_register(getLuaState(), "AddRequestResourceWeightsCommand", addRequestResourceWeightsCommand);
	lua_register(getLuaState(), "AddRequestResourceWeightsBatchCommand", addRequestResourceWeightsBatchCommand);
	lua_register(getLuaState(), "AddRequestSetStatMigrationDataCommand", addRequestSetStatMigrationDataCommand);
	lua_register(getLuaState(), "AddRequestStatMigrationDataCommand", addRequestStatMigrationDataCommand);
	lua_register(getLuaState(), "AddRequestStatMigrationStartCommand", addRequestStatMigrationStartCommand);
	lua_register(getLuaState(), "AddRequestStatMigrationStopCommand", addRequestStatMigrationStopCommand);
	lua_register(getLuaState(), "AddRequestStimpackCommand", addRequestStimpackCommand);
	lua_register(getLuaState(), "AddRequestSurveyCommand", addRequestSurveyCommand);
	lua_register(getLuaState(), "AddRequestWaypointAtPositionCommand", addRequestWaypointAtPositionCommand);
	lua_register(getLuaState(), "AddRescueCommand", addRescueCommand);
	lua_register(getLuaState(), "AddResendLoginMessageToAllCommand", addResendLoginMessageToAllCommand);
	lua_register(getLuaState(), "AddResetJediCommand", addResetJediCommand);
	lua_register(getLuaState(), "AddResourceCommand", addResourceCommand);
	lua_register(getLuaState(), "AddResourceContainerSplitCommand", addResourceContainerSplitCommand);
	lua_register(getLuaState(), "AddResourceContainerTransferCommand", addResourceContainerTransferCommand);
	lua_register(getLuaState(), "AddResourceSetNameCommand", addResourceSetNameCommand);
	lua_register(getLuaState(), "AddResSampleLoopCommand", addResSampleLoopCommand);
	lua_register(getLuaState(), "AddRestartConversionCommand", addRestartConversionCommand);
	lua_register(getLuaState(), "AddRestartCraftingSessionCommand", addRestartCraftingSessionCommand);
	lua_register(getLuaState(), "AddRetreatCommand", addRetreatCommand);
	lua_register(getLuaState(), "AddRevivePlayerCommand", addRevivePlayerCommand);
	lua_register(getLuaState(), "AddRevokeBadgeCommand", addRevokeBadgeCommand);
	lua_register(getLuaState(), "AddRevokeSkillCommand", addRevokeSkillCommand);
	lua_register(getLuaState(), "AddRolePlayCommand", addRolePlayCommand);
	lua_register(getLuaState(), "AddRollShotCommand", addRollShotCommand);
	lua_register(getLuaState(), "AddRotateFurnitureCommand", addRotateFurnitureCommand);
	lua_register(getLuaState(), "AddSaber1hComboHit1Command", addSaber1hComboHit1Command);
	lua_register(getLuaState(), "AddSaber1hComboHit2Command", addSaber1hComboHit2Command);
	lua_register(getLuaState(), "AddSaber1hComboHit3Command", addSaber1hComboHit3Command);
	lua_register(getLuaState(), "AddSaber1hFlurryCommand", addSaber1hFlurryCommand);
	lua_register(getLuaState(), "AddSaber1hFlurry2Command", addSaber1hFlurry2Command);
	lua_register(getLuaState(), "AddSaber1hHeadHit1Command", addSaber1hHeadHit1Command);
	lua_register(getLuaState(), "AddSaber1hHeadHit2Command", addSaber1hHeadHit2Command);
	lua_register(getLuaState(), "AddSaber1hHeadHit3Command", addSaber1hHeadHit3Command);
	lua_register(getLuaState(), "AddSaber1hHit1Command", addSaber1hHit1Command);
	lua_register(getLuaState(), "AddSaber1hHit2Command", addSaber1hHit2Command);
	lua_register(getLuaState(), "AddSaber1hHit3Command", addSaber1hHit3Command);
	lua_register(getLuaState(), "AddSaber2hBodyHit1Command", addSaber2hBodyHit1Command);
	lua_register(getLuaState(), "AddSaber2hBodyHit2Command", addSaber2hBodyHit2Command);
	lua_register(getLuaState(), "AddSaber2hBodyHit3Command", addSaber2hBodyHit3Command);
	lua_register(getLuaState(), "AddSaber2hFrenzyCommand", addSaber2hFrenzyCommand);
	lua_register(getLuaState(), "AddSaber2hHit1Command", addSaber2hHit1Command);
	lua_register(getLuaState(), "AddSaber2hHit2Command", addSaber2hHit2Command);
	lua_register(getLuaState(), "AddSaber2hHit3Command", addSaber2hHit3Command);
	lua_register(getLuaState(), "AddSaber2hPhantomCommand", addSaber2hPhantomCommand);
	lua_register(getLuaState(), "AddSaber2hSweep1Command", addSaber2hSweep1Command);
	lua_register(getLuaState(), "AddSaber2hSweep2Command", addSaber2hSweep2Command);
	lua_register(getLuaState(), "AddSaber2hSweep3Command", addSaber2hSweep3Command);
	lua_register(getLuaState(), "AddSaberPolearmDervishCommand", addSaberPolearmDervishCommand);
	lua_register(getLuaState(), "AddSaberPolearmDervish2Command", addSaberPolearmDervish2Command);
	lua_register(getLuaState(), "AddSaberPolearmHit1Command", addSaberPolearmHit1Command);
	lua_register(getLuaState(), "AddSaberPolearmHit2Command", addSaberPolearmHit2Command);
	lua_register(getLuaState(), "AddSaberPolearmHit3Command", addSaberPolearmHit3Command);
	lua_register(getLuaState(), "AddSaberPolearmLegHit1Command", addSaberPolearmLegHit1Command);
	lua_register(getLuaState(), "AddSaberPolearmLegHit2Command", addSaberPolearmLegHit2Command);
	lua_register(getLuaState(), "AddSaberPolearmLegHit3Command", addSaberPolearmLegHit3Command);
	lua_register(getLuaState(), "AddSaberPolearmSpinAttack1Command", addSaberPolearmSpinAttack1Command);
	lua_register(getLuaState(), "AddSaberPolearmSpinAttack2Command", addSaberPolearmSpinAttack2Command);
	lua_register(getLuaState(), "AddSaberPolearmSpinAttack3Command", addSaberPolearmSpinAttack3Command);
	lua_register(getLuaState(), "AddSaberSlash1Command", addSaberSlash1Command);
	lua_register(getLuaState(), "AddSaberSlash2Command", addSaberSlash2Command);
	lua_register(getLuaState(), "AddSaberThrow1Command", addSaberThrow1Command);
	lua_register(getLuaState(), "AddSaberThrow2Command", addSaberThrow2Command);
	lua_register(getLuaState(), "AddSaberThrow3Command", addSaberThrow3Command);
	lua_register(getLuaState(), "AddSampleCommand", addSampleCommand);
	lua_register(getLuaState(), "AddSampleDNACommand", addSampleDNACommand);
	lua_register(getLuaState(), "AddScatterShot1Command", addScatterShot1Command);
	lua_register(getLuaState(), "AddScatterShot2Command", addScatterShot2Command);
	lua_register(getLuaState(), "AddScriptCommand", addScriptCommand);
	lua_register(getLuaState(), "AddSearchCorpseCommand", addSearchCorpseCommand);
	lua_register(getLuaState(), "AddSecretSpawnSpamCommand", addSecretSpawnSpamCommand);
	lua_register(getLuaState(), "AddSeGogglesCommand", addSeGogglesCommand);
	lua_register(getLuaState(), "AddSelectDraftSchematicCommand", addSelectDraftSchematicCommand);
	lua_register(getLuaState(), "AddServerCommand", addServerCommand);
	lua_register(getLuaState(), "AddServerDestroyObjectCommand", addServerDestroyObjectCommand);
	lua_register(getLuaState(), "AddServerSysGroupCommand", addServerSysGroupCommand);
	lua_register(getLuaState(), "AddSetBiographyAdminCommand", addSetBiographyAdminCommand);
	lua_register(getLuaState(), "AddSetBiographyCommand", addSetBiographyCommand);
	lua_register(getLuaState(), "AddSetBoostmoraleCommand", addSetBoostmoraleCommand);
	lua_register(getLuaState(), "AddSetChargeCommand", addSetChargeCommand);
	lua_register(getLuaState(), "AddSetCurrentSkillTitleCommand", addSetCurrentSkillTitleCommand);
	lua_register(getLuaState(), "AddSetExperienceCommand", addSetExperienceCommand);
	lua_register(getLuaState(), "AddSetFactionCommand", addSetFactionCommand);
	lua_register(getLuaState(), "AddSetFactionStandingCommand", addSetFactionStandingCommand);
	lua_register(getLuaState(), "AddSetFirstNameCommand", addSetFirstNameCommand);
	lua_register(getLuaState(), "AddSetFormupCommand", addSetFormupCommand);
	lua_register(getLuaState(), "AddSetGodModeCommand", addSetGodModeCommand);
	lua_register(getLuaState(), "AddSetHueCommand", addSetHueCommand);
	lua_register(getLuaState(), "AddSetIntimidateCommand", addSetIntimidateCommand);
	lua_register(getLuaState(), "AddSetLastNameCommand", addSetLastNameCommand);
	lua_register(getLuaState(), "AddSetLoginMessageCommand", addSetLoginMessageCommand);
	lua_register(getLuaState(), "AddSetLoginTitleCommand", addSetLoginTitleCommand);
	lua_register(getLuaState(), "AddSetMatchMakingCharacterIdCommand", addSetMatchMakingCharacterIdCommand);
	lua_register(getLuaState(), "AddSetMatchMakingPersonalIdCommand", addSetMatchMakingPersonalIdCommand);
	lua_register(getLuaState(), "AddSetMaximumSpawnTimeCommand", addSetMaximumSpawnTimeCommand);
	lua_register(getLuaState(), "AddSetMinimumSpawnTimeCommand", addSetMinimumSpawnTimeCommand);
	lua_register(getLuaState(), "AddSetMoodCommand", addSetMoodCommand);
	lua_register(getLuaState(), "AddSetMoodInternalCommand", addSetMoodInternalCommand);
	lua_register(getLuaState(), "AddSetNameCommand", addSetNameCommand);
	lua_register(getLuaState(), "AddSetNameCommand", addSetNameCommand);
	lua_register(getLuaState(), "AddSetOwnerCommand", addSetOwnerCommand);
	lua_register(getLuaState(), "AddSetPerformanceBuffTargetCommand", addSetPerformanceBuffTargetCommand);
	lua_register(getLuaState(), "AddSetpermissionCommand", addSetpermissionCommand);
	lua_register(getLuaState(), "AddSetPlanetLimitCommand", addSetPlanetLimitCommand);
	lua_register(getLuaState(), "AddSetPlayerAppearanceCommand", addSetPlayerAppearanceCommand);
	lua_register(getLuaState(), "AddSetPlayerStateCommand", addSetPlayerStateCommand);
	lua_register(getLuaState(), "AddSetprivacyCommand", addSetprivacyCommand);
	lua_register(getLuaState(), "AddSetPublicStateCommand", addSetPublicStateCommand);
	lua_register(getLuaState(), "AddSetRankCommand", addSetRankCommand);
	lua_register(getLuaState(), "AddSetRetreatCommand", addSetRetreatCommand);
	lua_register(getLuaState(), "AddSetSpeedCommand", addSetSpeedCommand);
	lua_register(getLuaState(), "AddSetSpokenLanguageCommand", addSetSpokenLanguageCommand);
	lua_register(getLuaState(), "AddSetSteadyaimCommand", addSetSteadyaimCommand);
	lua_register(getLuaState(), "AddSetTEFCommand", addSetTEFCommand);
	lua_register(getLuaState(), "AddSetVeteranRewardCommand", addSetVeteranRewardCommand);
	lua_register(getLuaState(), "AddSetWarcryCommand", addSetWarcryCommand);
	lua_register(getLuaState(), "AddSetWaypointActiveStatusCommand", addSetWaypointActiveStatusCommand);
	lua_register(getLuaState(), "AddSetWaypointNameCommand", addSetWaypointNameCommand);
	lua_register(getLuaState(), "AddShowCouncilRankCommand", addShowCouncilRankCommand);
	lua_register(getLuaState(), "AddShowDanceVisualsCommand", addShowDanceVisualsCommand);
	lua_register(getLuaState(), "AddShowFactionInformationCommand", addShowFactionInformationCommand);
	lua_register(getLuaState(), "AddShowMusicianVisualsCommand", addShowMusicianVisualsCommand);
	lua_register(getLuaState(), "AddShowPvPRatingCommand", addShowPvPRatingCommand);
	lua_register(getLuaState(), "AddShowSpawnRegionCommand", addShowSpawnRegionCommand);
	lua_register(getLuaState(), "AddSitServerCommand", addSitServerCommand);
	lua_register(getLuaState(), "AddSkillCommand", addSkillCommand);
	lua_register(getLuaState(), "AddSmokebombCommand", addSmokebombCommand);
	lua_register(getLuaState(), "AddSniperShotCommand", addSniperShotCommand);
	lua_register(getLuaState(), "AddSnoopCommand", addSnoopCommand);
	lua_register(getLuaState(), "AddSocialCommand", addSocialCommand);
	lua_register(getLuaState(), "AddSocialInternalCommand", addSocialInternalCommand);
	lua_register(getLuaState(), "AddSpatialChatCommand", addSpatialChatCommand);
	lua_register(getLuaState(), "AddSpatialChatInternalCommand", addSpatialChatInternalCommand);
	lua_register(getLuaState(), "AddSpawnStatusCommand", addSpawnStatusCommand);
	lua_register(getLuaState(), "AddSplitCreditsWithGroupCommand", addSplitCreditsWithGroupCommand);
	lua_register(getLuaState(), "AddSpotlightCommand", addSpotlightCommand);
	lua_register(getLuaState(), "AddSprayShotCommand", addSprayShotCommand);
	lua_register(getLuaState(), "AddStandCommand", addStandCommand);
	lua_register(getLuaState(), "AddStartBandCommand", addStartBandCommand);
	lua_register(getLuaState(), "AddStartCitySpawnerCommand", addStartCitySpawnerCommand);
	lua_register(getLuaState(), "AddStartDanceCommand", addStartDanceCommand);
	lua_register(getLuaState(), "AddStartleShot1Command", addStartleShot1Command);
	lua_register(getLuaState(), "AddStartleShot2Command", addStartleShot2Command);
	lua_register(getLuaState(), "AddStartMusicCommand", addStartMusicCommand);
	lua_register(getLuaState(), "AddStartSpawnerCommand", addStartSpawnerCommand);
	lua_register(getLuaState(), "AddStartTargetSpawnerCommand", addStartTargetSpawnerCommand);
	lua_register(getLuaState(), "AddStartTraceLoggingCommand", addStartTraceLoggingCommand);
	lua_register(getLuaState(), "AddStatCommand", addStatCommand);
	lua_register(getLuaState(), "AddSteadyaimCommand", addSteadyaimCommand);
	lua_register(getLuaState(), "AddStopBandCommand", addStopBandCommand);
	lua_register(getLuaState(), "AddStopBleedingCommand", addStopBleedingCommand);
	lua_register(getLuaState(), "AddStopCitySpawnerCommand", addStopCitySpawnerCommand);
	lua_register(getLuaState(), "AddStopCraftingSessionCommand", addStopCraftingSessionCommand);
	lua_register(getLuaState(), "AddStopDanceCommand", addStopDanceCommand);
	lua_register(getLuaState(), "AddStoplisteningCommand", addStoplisteningCommand);
	lua_register(getLuaState(), "AddStopMusicCommand", addStopMusicCommand);
	lua_register(getLuaState(), "AddStoppingShotCommand", addStoppingShotCommand);
	lua_register(getLuaState(), "AddStopSpawnerCommand", addStopSpawnerCommand);
	lua_register(getLuaState(), "AddStopTargetSpawnerCommand", addStopTargetSpawnerCommand);
	lua_register(getLuaState(), "AddStopTraceLoggingCommand", addStopTraceLoggingCommand);
	lua_register(getLuaState(), "AddStopwatchingCommand", addStopwatchingCommand);
	lua_register(getLuaState(), "AddStrafeShot1Command", addStrafeShot1Command);
	lua_register(getLuaState(), "AddStrafeShot2Command", addStrafeShot2Command);
	lua_register(getLuaState(), "AddStrongDiseaseCommand", addStrongDiseaseCommand);
	lua_register(getLuaState(), "AddStrongPoisonCommand", addStrongPoisonCommand);
	lua_register(getLuaState(), "AddStructurestatusCommand", addStructurestatusCommand);
	lua_register(getLuaState(), "AddStunAttackCommand", addStunAttackCommand);
	lua_register(getLuaState(), "AddSuppressionFire1Command", addSuppressionFire1Command);
	lua_register(getLuaState(), "AddSuppressionFire2Command", addSuppressionFire2Command);
	lua_register(getLuaState(), "AddSurpriseShotCommand", addSurpriseShotCommand);
	lua_register(getLuaState(), "AddSurrenderSkillCommand", addSurrenderSkillCommand);
	lua_register(getLuaState(), "AddSurveyCommand", addSurveyCommand);
	lua_register(getLuaState(), "AddSynchronizedUiListenCommand", addSynchronizedUiListenCommand);
	lua_register(getLuaState(), "AddSynchronizedUiStopListeningCommand", addSynchronizedUiStopListeningCommand);
	lua_register(getLuaState(), "AddSystemMessageCommand", addSystemMessageCommand);
	lua_register(getLuaState(), "AddTakeCoverCommand", addTakeCoverCommand);
	lua_register(getLuaState(), "AddTameCommand", addTameCommand);
	lua_register(getLuaState(), "AddTargetCommand", addTargetCommand);
	lua_register(getLuaState(), "AddTauntCommand", addTauntCommand);
	lua_register(getLuaState(), "AddTeachCommand", addTeachCommand);
	lua_register(getLuaState(), "AddTeleportCommand", addTeleportCommand);
	lua_register(getLuaState(), "AddTeleportTargetCommand", addTeleportTargetCommand);
	lua_register(getLuaState(), "AddTeleportToCommand", addTeleportToCommand);
	lua_register(getLuaState(), "AddTellpetCommand", addTellpetCommand);
	lua_register(getLuaState(), "AddTendDamageCommand", addTendDamageCommand);
	lua_register(getLuaState(), "AddTendDamageToolCommand", addTendDamageToolCommand);
	lua_register(getLuaState(), "AddTendWoundCommand", addTendWoundCommand);
	lua_register(getLuaState(), "AddTendWoundsToolCommand", addTendWoundsToolCommand);
	lua_register(getLuaState(), "AddThreatenShotCommand", addThreatenShotCommand);
	lua_register(getLuaState(), "AddThrowGrenadeCommand", addThrowGrenadeCommand);
	lua_register(getLuaState(), "AddThrowTrapCommand", addThrowTrapCommand);
	lua_register(getLuaState(), "AddTipCommand", addTipCommand);
	lua_register(getLuaState(), "AddToggleAwayFromKeyBoardCommand", addToggleAwayFromKeyBoardCommand);
	lua_register(getLuaState(), "AddToggleDisplayingFactionRankCommand", addToggleDisplayingFactionRankCommand);
	lua_register(getLuaState(), "AddTorsoShotCommand", addTorsoShotCommand);
	lua_register(getLuaState(), "AddTotalHealOtherCommand", addTotalHealOtherCommand);
	lua_register(getLuaState(), "AddTotalHealSelfCommand", addTotalHealSelfCommand);
	lua_register(getLuaState(), "AddTransferForceCommand", addTransferForceCommand);
	lua_register(getLuaState(), "AddTransferItemCommand", addTransferItemCommand);
	lua_register(getLuaState(), "AddTransferItemArmorCommand", addTransferItemArmorCommand);
	lua_register(getLuaState(), "AddTransferItemMiscCommand", addTransferItemMiscCommand);
	lua_register(getLuaState(), "AddTransferItemWeaponCommand", addTransferItemWeaponCommand);
	lua_register(getLuaState(), "AddTransferstructureCommand", addTransferstructureCommand);
	lua_register(getLuaState(), "AddTumbleToKneelingCommand", addTumbleToKneelingCommand);
	lua_register(getLuaState(), "AddTumbleToProneCommand", addTumbleToProneCommand);
	lua_register(getLuaState(), "AddTumbleToStandingCommand", addTumbleToStandingCommand);
	lua_register(getLuaState(), "AddUnarmedBlind1Command", addUnarmedBlind1Command);
	lua_register(getLuaState(), "AddUnarmedBodyHit1Command", addUnarmedBodyHit1Command);
	lua_register(getLuaState(), "AddUnarmedCombo1Command", addUnarmedCombo1Command);
	lua_register(getLuaState(), "AddUnarmedCombo2Command", addUnarmedCombo2Command);
	lua_register(getLuaState(), "AddUnarmedDizzy1Command", addUnarmedDizzy1Command);
	lua_register(getLuaState(), "AddUnarmedHeadHit1Command", addUnarmedHeadHit1Command);
	lua_register(getLuaState(), "AddUnarmedHit1Command", addUnarmedHit1Command);
	lua_register(getLuaState(), "AddUnarmedHit2Command", addUnarmedHit2Command);
	lua_register(getLuaState(), "AddUnarmedHit3Command", addUnarmedHit3Command);
	lua_register(getLuaState(), "AddUnarmedKnockdown1Command", addUnarmedKnockdown1Command);
	lua_register(getLuaState(), "AddUnarmedKnockdown2Command", addUnarmedKnockdown2Command);
	lua_register(getLuaState(), "AddUnarmedLegHit1Command", addUnarmedLegHit1Command);
	lua_register(getLuaState(), "AddUnarmedLunge1Command", addUnarmedLunge1Command);
	lua_register(getLuaState(), "AddUnarmedLunge2Command", addUnarmedLunge2Command);
	lua_register(getLuaState(), "AddUnarmedSpinAttack1Command", addUnarmedSpinAttack1Command);
	lua_register(getLuaState(), "AddUnarmedSpinAttack2Command", addUnarmedSpinAttack2Command);
	lua_register(getLuaState(), "AddUnarmedStun1Command", addUnarmedStun1Command);
	lua_register(getLuaState(), "AddUnassociateDroidControlDeviceWithShipCommand", addUnassociateDroidControlDeviceWithShipCommand);
	lua_register(getLuaState(), "AddUnCityBanCommand", addUnCityBanCommand);
	lua_register(getLuaState(), "AddUnconsentCommand", addUnconsentCommand);
	lua_register(getLuaState(), "AddUnderHandShotCommand", addUnderHandShotCommand);
	lua_register(getLuaState(), "AddUnfreezePlayerCommand", addUnfreezePlayerCommand);
	lua_register(getLuaState(), "AddUninstallShipComponentCommand", addUninstallShipComponentCommand);
	lua_register(getLuaState(), "AddUninviteCommand", addUninviteCommand);
	lua_register(getLuaState(), "AddUnsnoopCommand", addUnsnoopCommand);
	lua_register(getLuaState(), "AddUseReconDroneCommand", addUseReconDroneCommand);
	lua_register(getLuaState(), "AddUseSkillBuffCommand", addUseSkillBuffCommand);
	lua_register(getLuaState(), "AddVentriloquismCommand", addVentriloquismCommand);
	lua_register(getLuaState(), "AddToggleCombatTauntsCommand", addToggleCombatTauntsCommand);
	lua_register(getLuaState(), "AddVertFurnitureCommand", addVertFurnitureCommand);
	lua_register(getLuaState(), "AddVitalizeCommand", addVitalizeCommand);
	lua_register(getLuaState(), "AddVolleyFireCommand", addVolleyFireCommand);
	lua_register(getLuaState(), "AddVolleyFireAttackCommand", addVolleyFireAttackCommand);
	lua_register(getLuaState(), "AddWarcry1Command", addWarcry1Command);
	lua_register(getLuaState(), "AddWarcry2Command", addWarcry2Command);
	lua_register(getLuaState(), "AddWarningShotCommand", addWarningShotCommand);
	lua_register(getLuaState(), "AddWatchCommand", addWatchCommand);
	lua_register(getLuaState(), "AddWildShot1Command", addWildShot1Command);
	lua_register(getLuaState(), "AddWildShot2Command", addWildShot2Command);
	lua_register(getLuaState(), "AddWipeItemsCommand", addWipeItemsCommand);
	lua_register(getLuaState(), "AddWookieeRoarCommand", addWookieeRoarCommand);
	lua_register(getLuaState(), "AddCityInfoCommand", addCityInfoCommand);
	lua_register(getLuaState(), "AddEjectCommand", addEjectCommand);
	lua_register(getLuaState(), "AddLaunchIntoSpaceCommand", addLaunchIntoSpaceCommand);
	lua_register(getLuaState(), "AddUnstickCommand", addUnstickCommand);
	lua_register(getLuaState(), "AddWaypointCommand", addWaypointCommand);
	lua_register(getLuaState(), "AddCreateVendorCommand", addCreateVendorCommand);


}

void CommandConfigManager::registerGlobals() {

	//states
	setGlobalLong("INVALID_STATE", CreatureState::INVALID);
	setGlobalLong("COVER_STATE", CreatureState::COVER);
	setGlobalLong("COMBAT_STATE", CreatureState::COMBAT);
	setGlobalLong("PEACE_STATE", CreatureState::PEACE);
	setGlobalLong("AIMING_STATE", CreatureState::AIMING);
	setGlobalLong("ALERT_STATE", CreatureState::ALERT);
	setGlobalLong("BERSERK_STATE", CreatureState::BERSERK);
	setGlobalLong("FEIGNDEATH_STATE", CreatureState::FEIGNDEATH);
	setGlobalLong("COMBATATTITUDEEVASIVE_STATE", CreatureState::COMBATATTITUDEEVASIVE);
	setGlobalLong("COMBATATTITUDENORMAL_STATE", CreatureState::COMBATATTITUDENORMAL);
	setGlobalLong("COMBATATTITUDEAGGRESSIVE_STATE", CreatureState::COMBATATTITUDEAGGRESSIVE);
	setGlobalLong("TUMBLING_STATE", CreatureState::TUMBLING);
	setGlobalLong("RALLIED_STATE", CreatureState::RALLIED);
	setGlobalLong("STUNNED_STATE", CreatureState::STUNNED);
	setGlobalLong("BLINDED_STATE", CreatureState::BLINDED);
	setGlobalLong("DIZZY_STATE",  CreatureState::DIZZY);
	setGlobalLong("INTIMIDATED_STATE", CreatureState::INTIMIDATED);
	setGlobalLong("IMMOBILIZED_STATE", CreatureState::SNARED);
	setGlobalLong("FROZEN_STATE", CreatureState::ROOTED);
	setGlobalLong("SWIMMING_STATE", CreatureState::SWIMMING);
	setGlobalLong("SITTINGONCHAIR_STATE", CreatureState::SITTINGONCHAIR);
	setGlobalLong("CRAFTING_STATE", CreatureState::CRAFTING);
	setGlobalLong("GLOWINGJEDI_STATE", CreatureState::GLOWINGJEDI);
	setGlobalLong("MASKSCENT_STATE", CreatureState::MASKSCENT);
	setGlobalLong("POISONED_STATE", CreatureState::POISONED);
	setGlobalLong("BLEEDING_STATE", CreatureState::BLEEDING);
	setGlobalLong("DISEASED_STATE", CreatureState::DISEASED);
	setGlobalLong("ONFIRE_STATE", CreatureState::ONFIRE);
	setGlobalLong("RIDINGMOUNT_STATE", CreatureState::RIDINGMOUNT);
	setGlobalLong("MOUNTEDCREATURE_STATE", CreatureState::MOUNTEDCREATURE);
	setGlobalLong("PILOTSHIP_STATE", CreatureState::PILOTSHIP);
	setGlobalLong("SHIPOPERATIONS_STATE", CreatureState::SHIPOPERATIONS);
	setGlobalLong("SHIPGUNNER_STATE", CreatureState::SHIPGUNNER);

	//TODO: remove this - there is no centered state?
	setGlobalLong("CENTERED_STATE", 0x80000000);

	//TODO: What is this? Can it be removed? who thought 0x123 would be a mask?
	setGlobalLong("MEDITATE", 0x123);

	// postures

	setGlobalInt("INVALID_POSTURE", CreaturePosture::INVALID);
	setGlobalInt("UPRIGHT_POSTURE", CreaturePosture::UPRIGHT);
	setGlobalInt("CROUCHED_POSTURE", CreaturePosture::CROUCHED);
	setGlobalInt("PRONE_POSTURE", CreaturePosture::PRONE);
	setGlobalInt("SNEAKING_POSTURE", CreaturePosture::SNEAKING);
	setGlobalInt("BLOCKING_POSTURE", CreaturePosture::BLOCKING);
	setGlobalInt("CLIMBING_POSTURE", CreaturePosture::CLIMBING);
	setGlobalInt("FLYING_POSTURE", CreaturePosture::FLYING);
	setGlobalInt("LYINGDOWN_POSTURE", CreaturePosture::LYINGDOWN);
	setGlobalInt("SITTING_POSTURE", CreaturePosture::SITTING);
	setGlobalInt("SKILLANIMATING_POSTURE", CreaturePosture::SKILLANIMATING);
	setGlobalInt("DRIVINGVEHICLE_POSTURE", CreaturePosture::DRIVINGVEHICLE);
	setGlobalInt("RIDINGCREATURE_POSTURE", CreaturePosture::RIDINGCREATURE);
	setGlobalInt("KNOCKEDDOWN_POSTURE", CreaturePosture::KNOCKEDDOWN);
	setGlobalInt("INCAPACITATED_POSTURE", CreaturePosture::INCAPACITATED);
	setGlobalInt("DEAD_POSTURE", CreaturePosture::DEAD);

}

int CommandConfigManager::runSlashCommandsFile(lua_State* L) {
	String filename;

	filename = getStringParameter(L);

	runFile("scripts/commands/" + filename, L);

	return 0;
}

void CommandConfigManager::parseOptions(LuaObject &slashcommand, QueueCommand* command) {

	/*String field = slashcommand.getStringField("animation");
	command->setAnimation(field);*/

	uint64 mask = slashcommand.getLongField("invalidStateMask");
	command->setStateMask(mask);

	String field = slashcommand.getStringField("invalidPostures");
	command->setInvalidPostures(field);

	/*int num = slashcommand.getIntField("target");
	command->setTarget(num);*/

	int num = slashcommand.getIntField("targetType");
	command->setTargetType(num);

	num = slashcommand.getIntField("disabled");
	command->setDisabled(num);

	num = slashcommand.getIntField("maxRangeToTarget");
	command->setMaxRange(num);

	num = slashcommand.getIntField("addToCombatQueue");
	command->setAddToCombatQueue(num);

	field = slashcommand.getStringField("characterAbility");
	command->setCharacterAbility(field);

	field = slashcommand.getStringField("defaultPriority");
	command->setDefaultPriority(field);

	float time = slashcommand.getFloatField("defaultTime");
	command->setDefaultTime(time);

}

void CommandConfigManager::parseAlternativeNames(String& alternativeNames, QueueCommand* slashCommand) {
	StringTokenizer tokenizer(alternativeNames);
	tokenizer.setDelimeter(",");

	String token = "";
	while (tokenizer.hasMoreTokens()) {
		tokenizer.getStringToken(token);

		slashCommands->put(token, slashCommand);
	}
}

void CommandConfigManager::parseSlashCommand(LuaObject &slashcommand, QueueCommand* slashCommand) {

	parseOptions(slashcommand, slashCommand);

	slashCommands->put(slashCommand);

	/*String alternativeNames = slashcommand.getStringField("alternativeNames");
	if (!alternativeNames.isEmpty())
		parseAlternativeNames(alternativeNames, slashCommand);*/
}

int CommandConfigManager::addActionShot1Command(lua_State* L) {
	LuaObject slashcommand(L);
	if (!slashcommand.isValidTable())
		return 0;

	ActionShot1Command* slashCommand = new ActionShot1Command(slashcommand.getStringField("name"), server);
	parseSlashCommand(slashcommand, slashCommand);
	return 1;
}

int CommandConfigManager::addActionShot2Command(lua_State* L) {
	LuaObject slashcommand(L);
	if (!slashcommand.isValidTable())
		return 0;

	ActionShot2Command* slashCommand = new ActionShot2Command(slashcommand.getStringField("name"), server);
	parseSlashCommand(slashcommand, slashCommand);
	return 1;
}

int CommandConfigManager::addActivateCloneCommand(lua_State* L) {
	LuaObject slashcommand(L);
	if (!slashcommand.isValidTable())
		return 0;

	ActivateCloneCommand* slashCommand = new ActivateCloneCommand(slashcommand.getStringField("name"), server);
	parseSlashCommand(slashcommand, slashCommand);
	return 1;
}

int CommandConfigManager::addActivateQuestCommand(lua_State* L) {
	LuaObject slashcommand(L);
	if (!slashcommand.isValidTable())
		return 0;

	ActivateQuestCommand* slashCommand = new ActivateQuestCommand(slashcommand.getStringField("name"), server);
	parseSlashCommand(slashcommand, slashCommand);
	return 1;
}

int CommandConfigManager::addAddAllowedPlayerCommand(lua_State* L) {
	LuaObject slashcommand(L);
	if (!slashcommand.isValidTable())
		return 0;

	AddAllowedPlayerCommand* slashCommand = new AddAllowedPlayerCommand(slashcommand.getStringField("name"), server);
	parseSlashCommand(slashcommand, slashCommand);
	return 1;
}

int CommandConfigManager::addAddBannedPlayerCommand(lua_State* L) {
	LuaObject slashcommand(L);
	if (!slashcommand.isValidTable())
		return 0;

	AddBannedPlayerCommand* slashCommand = new AddBannedPlayerCommand(slashcommand.getStringField("name"), server);
	parseSlashCommand(slashcommand, slashCommand);
	return 1;
}

int CommandConfigManager::addAddFriendCommand(lua_State* L) {
	LuaObject slashcommand(L);
	if (!slashcommand.isValidTable())
		return 0;

	AddFriendCommand* slashCommand = new AddFriendCommand(slashcommand.getStringField("name"), server);
	parseSlashCommand(slashcommand, slashCommand);
	return 1;
}

int CommandConfigManager::addAddIgnoreCommand(lua_State* L) {
	LuaObject slashcommand(L);
	if (!slashcommand.isValidTable())
		return 0;

	AddIgnoreCommand* slashCommand = new AddIgnoreCommand(slashcommand.getStringField("name"), server);
	parseSlashCommand(slashcommand, slashCommand);
	return 1;
}

int CommandConfigManager::addAddMapLocationCommand(lua_State* L) {
	LuaObject slashcommand(L);
	if (!slashcommand.isValidTable())
		return 0;

	AddMapLocationCommand* slashCommand = new AddMapLocationCommand(slashcommand.getStringField("name"), server);
	parseSlashCommand(slashcommand, slashCommand);
	return 1;
}

int CommandConfigManager::addAddPowerCommand(lua_State* L) {
	LuaObject slashcommand(L);
	if (!slashcommand.isValidTable())
		return 0;

	AddPowerCommand* slashCommand = new AddPowerCommand(slashcommand.getStringField("name"), server);
	parseSlashCommand(slashcommand, slashCommand);
	return 1;
}

int CommandConfigManager::addAdjustLotCountCommand(lua_State* L) {
	LuaObject slashcommand(L);
	if (!slashcommand.isValidTable())
		return 0;

	AdjustLotCountCommand* slashCommand = new AdjustLotCountCommand(slashcommand.getStringField("name"), server);
	parseSlashCommand(slashcommand, slashCommand);
	return 1;
}

int CommandConfigManager::addAiIgnoreCommand(lua_State* L) {
	LuaObject slashcommand(L);
	if (!slashcommand.isValidTable())
		return 0;

	AiIgnoreCommand* slashCommand = new AiIgnoreCommand(slashcommand.getStringField("name"), server);
	parseSlashCommand(slashcommand, slashCommand);
	return 1;
}

int CommandConfigManager::addAimCommand(lua_State* L) {
	LuaObject slashcommand(L);
	if (!slashcommand.isValidTable())
		return 0;

	AimCommand* slashCommand = new AimCommand(slashcommand.getStringField("name"), server);
	parseSlashCommand(slashcommand, slashCommand);
	return 1;
}

int CommandConfigManager::addAlertCommand(lua_State* L) {
	LuaObject slashcommand(L);
	if (!slashcommand.isValidTable())
		return 0;

	AlertCommand* slashCommand = new AlertCommand(slashcommand.getStringField("name"), server);
	parseSlashCommand(slashcommand, slashCommand);
	return 1;
}

int CommandConfigManager::addAnimalAttackCommand(lua_State* L) {
	LuaObject slashcommand(L);
	if (!slashcommand.isValidTable())
		return 0;

	AnimalAttackCommand* slashCommand = new AnimalAttackCommand(slashcommand.getStringField("name"), server);
	parseSlashCommand(slashcommand, slashCommand);
	return 1;
}

int CommandConfigManager::addAnimalCalmCommand(lua_State* L) {
	LuaObject slashcommand(L);
	if (!slashcommand.isValidTable())
		return 0;

	AnimalCalmCommand* slashCommand = new AnimalCalmCommand(slashcommand.getStringField("name"), server);
	parseSlashCommand(slashcommand, slashCommand);
	return 1;
}

int CommandConfigManager::addAnimalScareCommand(lua_State* L) {
	LuaObject slashcommand(L);
	if (!slashcommand.isValidTable())
		return 0;

	AnimalScareCommand* slashCommand = new AnimalScareCommand(slashcommand.getStringField("name"), server);
	parseSlashCommand(slashcommand, slashCommand);
	return 1;
}

int CommandConfigManager::addAnonCommand(lua_State* L) {
	LuaObject slashcommand(L);
	if (!slashcommand.isValidTable())
		return 0;

	AnonCommand* slashCommand = new AnonCommand(slashcommand.getStringField("name"), server);
	parseSlashCommand(slashcommand, slashCommand);
	return 1;
}

int CommandConfigManager::addApplyDiseaseCommand(lua_State* L) {
	LuaObject slashcommand(L);
	if (!slashcommand.isValidTable())
		return 0;

	ApplyDiseaseCommand* slashCommand = new ApplyDiseaseCommand(slashcommand.getStringField("name"), server);
	parseSlashCommand(slashcommand, slashCommand);
	return 1;
}

int CommandConfigManager::addApplyPoisonCommand(lua_State* L) {
	LuaObject slashcommand(L);
	if (!slashcommand.isValidTable())
		return 0;

	ApplyPoisonCommand* slashCommand = new ApplyPoisonCommand(slashcommand.getStringField("name"), server);
	parseSlashCommand(slashcommand, slashCommand);
	return 1;
}

int CommandConfigManager::addApplyPowerupCommand(lua_State* L) {
	LuaObject slashcommand(L);
	if (!slashcommand.isValidTable())
		return 0;

	ApplyPowerupCommand* slashCommand = new ApplyPowerupCommand(slashcommand.getStringField("name"), server);
	parseSlashCommand(slashcommand, slashCommand);
	return 1;
}

int CommandConfigManager::addAreatrackCommand(lua_State* L) {
	LuaObject slashcommand(L);
	if (!slashcommand.isValidTable())
		return 0;

	AreatrackCommand* slashCommand = new AreatrackCommand(slashcommand.getStringField("name"), server);
	parseSlashCommand(slashcommand, slashCommand);
	return 1;
}

int CommandConfigManager::addAssignDroidCommand(lua_State* L) {
	LuaObject slashcommand(L);
	if (!slashcommand.isValidTable())
		return 0;

	AssignDroidCommand* slashCommand = new AssignDroidCommand(slashcommand.getStringField("name"), server);
	parseSlashCommand(slashcommand, slashCommand);
	return 1;
}

int CommandConfigManager::addAssistCommand(lua_State* L) {
	LuaObject slashcommand(L);
	if (!slashcommand.isValidTable())
		return 0;

	AssistCommand* slashCommand = new AssistCommand(slashcommand.getStringField("name"), server);
	parseSlashCommand(slashcommand, slashCommand);
	return 1;
}

int CommandConfigManager::addAssociateDroidControlDeviceWithShipCommand(lua_State* L) {
	LuaObject slashcommand(L);
	if (!slashcommand.isValidTable())
		return 0;

	AssociateDroidControlDeviceWithShipCommand* slashCommand = new AssociateDroidControlDeviceWithShipCommand(slashcommand.getStringField("name"), server);
	parseSlashCommand(slashcommand, slashCommand);
	return 1;
}

int CommandConfigManager::addAttackCommand(lua_State* L) {
	LuaObject slashcommand(L);
	if (!slashcommand.isValidTable())
		return 0;

	AttackCommand* slashCommand = new AttackCommand(slashcommand.getStringField("name"), server);
	parseSlashCommand(slashcommand, slashCommand);
	return 1;
}

int CommandConfigManager::addAuctionCommand(lua_State* L) {
	LuaObject slashcommand(L);
	if (!slashcommand.isValidTable())
		return 0;

	AuctionCommand* slashCommand = new AuctionCommand(slashcommand.getStringField("name"), server);
	parseSlashCommand(slashcommand, slashCommand);
	return 1;
}

int CommandConfigManager::addAuctionAcceptCommand(lua_State* L) {
	LuaObject slashcommand(L);
	if (!slashcommand.isValidTable())
		return 0;

	AuctionAcceptCommand* slashCommand = new AuctionAcceptCommand(slashcommand.getStringField("name"), server);
	parseSlashCommand(slashcommand, slashCommand);
	return 1;
}

int CommandConfigManager::addAuctionBidCommand(lua_State* L) {
	LuaObject slashcommand(L);
	if (!slashcommand.isValidTable())
		return 0;

	AuctionBidCommand* slashCommand = new AuctionBidCommand(slashcommand.getStringField("name"), server);
	parseSlashCommand(slashcommand, slashCommand);
	return 1;
}

int CommandConfigManager::addAuctionCancelCommand(lua_State* L) {
	LuaObject slashcommand(L);
	if (!slashcommand.isValidTable())
		return 0;

	AuctionCancelCommand* slashCommand = new AuctionCancelCommand(slashcommand.getStringField("name"), server);
	parseSlashCommand(slashcommand, slashCommand);
	return 1;
}

int CommandConfigManager::addAuctionCreateCommand(lua_State* L) {
	LuaObject slashcommand(L);
	if (!slashcommand.isValidTable())
		return 0;

	AuctionCreateCommand* slashCommand = new AuctionCreateCommand(slashcommand.getStringField("name"), server);
	parseSlashCommand(slashcommand, slashCommand);
	return 1;
}

int CommandConfigManager::addAuctionQueryCommand(lua_State* L) {
	LuaObject slashcommand(L);
	if (!slashcommand.isValidTable())
		return 0;

	AuctionQueryCommand* slashCommand = new AuctionQueryCommand(slashcommand.getStringField("name"), server);
	parseSlashCommand(slashcommand, slashCommand);
	return 1;
}

int CommandConfigManager::addAuctionRetrieveCommand(lua_State* L) {
	LuaObject slashcommand(L);
	if (!slashcommand.isValidTable())
		return 0;

	AuctionRetrieveCommand* slashCommand = new AuctionRetrieveCommand(slashcommand.getStringField("name"), server);
	parseSlashCommand(slashcommand, slashCommand);
	return 1;
}

int CommandConfigManager::addAuctionsayCommand(lua_State* L) {
	LuaObject slashcommand(L);
	if (!slashcommand.isValidTable())
		return 0;

	AuctionsayCommand* slashCommand = new AuctionsayCommand(slashcommand.getStringField("name"), server);
	parseSlashCommand(slashcommand, slashCommand);
	return 1;
}

int CommandConfigManager::addAvoidIncapacitationCommand(lua_State* L) {
	LuaObject slashcommand(L);
	if (!slashcommand.isValidTable())
		return 0;

	AvoidIncapacitationCommand* slashCommand = new AvoidIncapacitationCommand(slashcommand.getStringField("name"), server);
	parseSlashCommand(slashcommand, slashCommand);
	return 1;
}

int CommandConfigManager::addBandFlourishCommand(lua_State* L) {
	LuaObject slashcommand(L);
	if (!slashcommand.isValidTable())
		return 0;

	BandFlourishCommand* slashCommand = new BandFlourishCommand(slashcommand.getStringField("name"), server);
	parseSlashCommand(slashcommand, slashCommand);
	return 1;
}

int CommandConfigManager::addBattlefieldStatusCommand(lua_State* L) {
	LuaObject slashcommand(L);
	if (!slashcommand.isValidTable())
		return 0;

	BattlefieldStatusCommand* slashCommand = new BattlefieldStatusCommand(slashcommand.getStringField("name"), server);
	parseSlashCommand(slashcommand, slashCommand);
	return 1;
}

int CommandConfigManager::addBerserk1Command(lua_State* L) {
	LuaObject slashcommand(L);
	if (!slashcommand.isValidTable())
		return 0;

	Berserk1Command* slashCommand = new Berserk1Command(slashcommand.getStringField("name"), server);
	parseSlashCommand(slashcommand, slashCommand);
	return 1;
}

int CommandConfigManager::addBerserk2Command(lua_State* L) {
	LuaObject slashcommand(L);
	if (!slashcommand.isValidTable())
		return 0;

	Berserk2Command* slashCommand = new Berserk2Command(slashcommand.getStringField("name"), server);
	parseSlashCommand(slashcommand, slashCommand);
	return 1;
}

int CommandConfigManager::addBetCommand(lua_State* L) {
	LuaObject slashcommand(L);
	if (!slashcommand.isValidTable())
		return 0;

	BetCommand* slashCommand = new BetCommand(slashcommand.getStringField("name"), server);
	parseSlashCommand(slashcommand, slashCommand);
	return 1;
}

int CommandConfigManager::addBleedingShotCommand(lua_State* L) {
	LuaObject slashcommand(L);
	if (!slashcommand.isValidTable())
		return 0;

	BleedingShotCommand* slashCommand = new BleedingShotCommand(slashcommand.getStringField("name"), server);
	parseSlashCommand(slashcommand, slashCommand);
	return 1;
}

int CommandConfigManager::addBlindAttackCommand(lua_State* L) {
	LuaObject slashcommand(L);
	if (!slashcommand.isValidTable())
		return 0;

	BlindAttackCommand* slashCommand = new BlindAttackCommand(slashcommand.getStringField("name"), server);
	parseSlashCommand(slashcommand, slashCommand);
	return 1;
}

int CommandConfigManager::addBoardShuttleCommand(lua_State* L) {
	LuaObject slashcommand(L);
	if (!slashcommand.isValidTable())
		return 0;

	BoardShuttleCommand* slashCommand = new BoardShuttleCommand(slashcommand.getStringField("name"), server);
	parseSlashCommand(slashcommand, slashCommand);
	return 1;
}

int CommandConfigManager::addBodyShot1Command(lua_State* L) {
	LuaObject slashcommand(L);
	if (!slashcommand.isValidTable())
		return 0;

	BodyShot1Command* slashCommand = new BodyShot1Command(slashcommand.getStringField("name"), server);
	parseSlashCommand(slashcommand, slashCommand);
	return 1;
}

int CommandConfigManager::addBodyShot2Command(lua_State* L) {
	LuaObject slashcommand(L);
	if (!slashcommand.isValidTable())
		return 0;

	BodyShot2Command* slashCommand = new BodyShot2Command(slashcommand.getStringField("name"), server);
	parseSlashCommand(slashcommand, slashCommand);
	return 1;
}

int CommandConfigManager::addBodyShot3Command(lua_State* L) {
	LuaObject slashcommand(L);
	if (!slashcommand.isValidTable())
		return 0;

	BodyShot3Command* slashCommand = new BodyShot3Command(slashcommand.getStringField("name"), server);
	parseSlashCommand(slashcommand, slashCommand);
	return 1;
}

int CommandConfigManager::addBoostmoraleCommand(lua_State* L) {
	LuaObject slashcommand(L);
	if (!slashcommand.isValidTable())
		return 0;

	BoostmoraleCommand* slashCommand = new BoostmoraleCommand(slashcommand.getStringField("name"), server);
	parseSlashCommand(slashcommand, slashCommand);
	return 1;
}

int CommandConfigManager::addBroadcastCommand(lua_State* L) {
	LuaObject slashcommand(L);
	if (!slashcommand.isValidTable())
		return 0;

	BroadcastCommand* slashCommand = new BroadcastCommand(slashcommand.getStringField("name"), server);
	parseSlashCommand(slashcommand, slashCommand);
	return 1;
}

int CommandConfigManager::addBroadcastAreaCommand(lua_State* L) {
	LuaObject slashcommand(L);
	if (!slashcommand.isValidTable())
		return 0;

	BroadcastAreaCommand* slashCommand = new BroadcastAreaCommand(slashcommand.getStringField("name"), server);
	parseSlashCommand(slashcommand, slashCommand);
	return 1;
}

int CommandConfigManager::addBroadcastGalaxyCommand(lua_State* L) {
	LuaObject slashcommand(L);
	if (!slashcommand.isValidTable())
		return 0;

	BroadcastGalaxyCommand* slashCommand = new BroadcastGalaxyCommand(slashcommand.getStringField("name"), server);
	parseSlashCommand(slashcommand, slashCommand);
	return 1;
}

int CommandConfigManager::addBroadcastPlanetCommand(lua_State* L) {
	LuaObject slashcommand(L);
	if (!slashcommand.isValidTable())
		return 0;

	BroadcastPlanetCommand* slashCommand = new BroadcastPlanetCommand(slashcommand.getStringField("name"), server);
	parseSlashCommand(slashcommand, slashCommand);
	return 1;
}

int CommandConfigManager::addBurstRunCommand(lua_State* L) {
	LuaObject slashcommand(L);
	if (!slashcommand.isValidTable())
		return 0;

	BurstRunCommand* slashCommand = new BurstRunCommand(slashcommand.getStringField("name"), server);
	parseSlashCommand(slashcommand, slashCommand);
	return 1;
}

int CommandConfigManager::addBurstShot1Command(lua_State* L) {
	LuaObject slashcommand(L);
	if (!slashcommand.isValidTable())
		return 0;

	BurstShot1Command* slashCommand = new BurstShot1Command(slashcommand.getStringField("name"), server);
	parseSlashCommand(slashcommand, slashCommand);
	return 1;
}

int CommandConfigManager::addBurstShot2Command(lua_State* L) {
	LuaObject slashcommand(L);
	if (!slashcommand.isValidTable())
		return 0;

	BurstShot2Command* slashCommand = new BurstShot2Command(slashcommand.getStringField("name"), server);
	parseSlashCommand(slashcommand, slashCommand);
	return 1;
}

int CommandConfigManager::addCancelCraftingSessionCommand(lua_State* L) {
	LuaObject slashcommand(L);
	if (!slashcommand.isValidTable())
		return 0;

	CancelCraftingSessionCommand* slashCommand = new CancelCraftingSessionCommand(slashcommand.getStringField("name"), server);
	parseSlashCommand(slashcommand, slashCommand);
	return 1;
}

int CommandConfigManager::addCenterOfBeingCommand(lua_State* L) {
	LuaObject slashcommand(L);
	if (!slashcommand.isValidTable())
		return 0;

	CenterOfBeingCommand* slashCommand = new CenterOfBeingCommand(slashcommand.getStringField("name"), server);
	parseSlashCommand(slashcommand, slashCommand);
	return 1;
}

int CommandConfigManager::addChangeBandMusicCommand(lua_State* L) {
	LuaObject slashcommand(L);
	if (!slashcommand.isValidTable())
		return 0;

	ChangeBandMusicCommand* slashCommand = new ChangeBandMusicCommand(slashcommand.getStringField("name"), server);
	parseSlashCommand(slashcommand, slashCommand);
	return 1;
}

int CommandConfigManager::addChangeDanceCommand(lua_State* L) {
	LuaObject slashcommand(L);
	if (!slashcommand.isValidTable())
		return 0;

	ChangeDanceCommand* slashCommand = new ChangeDanceCommand(slashcommand.getStringField("name"), server);
	parseSlashCommand(slashcommand, slashCommand);
	return 1;
}

int CommandConfigManager::addChangeMusicCommand(lua_State* L) {
	LuaObject slashcommand(L);
	if (!slashcommand.isValidTable())
		return 0;

	ChangeMusicCommand* slashCommand = new ChangeMusicCommand(slashcommand.getStringField("name"), server);
	parseSlashCommand(slashcommand, slashCommand);
	return 1;
}

int CommandConfigManager::addChannelForceCommand(lua_State* L) {
	LuaObject slashcommand(L);
	if (!slashcommand.isValidTable())
		return 0;

	ChannelForceCommand* slashCommand = new ChannelForceCommand(slashcommand.getStringField("name"), server);
	parseSlashCommand(slashcommand, slashCommand);
	return 1;
}

int CommandConfigManager::addChargeShot1Command(lua_State* L) {
	LuaObject slashcommand(L);
	if (!slashcommand.isValidTable())
		return 0;

	ChargeShot1Command* slashCommand = new ChargeShot1Command(slashcommand.getStringField("name"), server);
	parseSlashCommand(slashcommand, slashCommand);
	return 1;
}

int CommandConfigManager::addChargeShot2Command(lua_State* L) {
	LuaObject slashcommand(L);
	if (!slashcommand.isValidTable())
		return 0;

	ChargeShot2Command* slashCommand = new ChargeShot2Command(slashcommand.getStringField("name"), server);
	parseSlashCommand(slashcommand, slashCommand);
	return 1;
}

int CommandConfigManager::addCheckForceStatusCommand(lua_State* L) {
	LuaObject slashcommand(L);
	if (!slashcommand.isValidTable())
		return 0;

	CheckForceStatusCommand* slashCommand = new CheckForceStatusCommand(slashcommand.getStringField("name"), server);
	parseSlashCommand(slashcommand, slashCommand);
	return 1;
}

int CommandConfigManager::addCitybanCommand(lua_State* L) {
	LuaObject slashcommand(L);
	if (!slashcommand.isValidTable())
		return 0;

	CitybanCommand* slashCommand = new CitybanCommand(slashcommand.getStringField("name"), server);
	parseSlashCommand(slashcommand, slashCommand);
	return 1;
}

int CommandConfigManager::addCitypardonCommand(lua_State* L) {
	LuaObject slashcommand(L);
	if (!slashcommand.isValidTable())
		return 0;

	CitypardonCommand* slashCommand = new CitypardonCommand(slashcommand.getStringField("name"), server);
	parseSlashCommand(slashcommand, slashCommand);
	return 1;
}

int CommandConfigManager::addClaimVeteranRewardCommand(lua_State* L) {
	LuaObject slashcommand(L);
	if (!slashcommand.isValidTable())
		return 0;

	ClaimVeteranRewardCommand* slashCommand = new ClaimVeteranRewardCommand(slashcommand.getStringField("name"), server);
	parseSlashCommand(slashcommand, slashCommand);
	return 1;
}

int CommandConfigManager::addClearCompletedQuestCommand(lua_State* L) {
	LuaObject slashcommand(L);
	if (!slashcommand.isValidTable())
		return 0;

	ClearCompletedQuestCommand* slashCommand = new ClearCompletedQuestCommand(slashcommand.getStringField("name"), server);
	parseSlashCommand(slashcommand, slashCommand);
	return 1;
}

int CommandConfigManager::addClearVeteranRewardCommand(lua_State* L) {
	LuaObject slashcommand(L);
	if (!slashcommand.isValidTable())
		return 0;

	ClearVeteranRewardCommand* slashCommand = new ClearVeteranRewardCommand(slashcommand.getStringField("name"), server);
	parseSlashCommand(slashcommand, slashCommand);
	return 1;
}

int CommandConfigManager::addClientQualifiedForSkillCommand(lua_State* L) {
	LuaObject slashcommand(L);
	if (!slashcommand.isValidTable())
		return 0;

	ClientQualifiedForSkillCommand* slashCommand = new ClientQualifiedForSkillCommand(slashcommand.getStringField("name"), server);
	parseSlashCommand(slashcommand, slashCommand);
	return 1;
}

int CommandConfigManager::addCloneCommand(lua_State* L) {
	LuaObject slashcommand(L);
	if (!slashcommand.isValidTable())
		return 0;

	CloneCommand* slashCommand = new CloneCommand(slashcommand.getStringField("name"), server);
	parseSlashCommand(slashcommand, slashCommand);
	return 1;
}

int CommandConfigManager::addCloseContainerCommand(lua_State* L) {
	LuaObject slashcommand(L);
	if (!slashcommand.isValidTable())
		return 0;

	CloseContainerCommand* slashCommand = new CloseContainerCommand(slashcommand.getStringField("name"), server);
	parseSlashCommand(slashcommand, slashCommand);
	return 1;
}

int CommandConfigManager::addColorlightsCommand(lua_State* L) {
	LuaObject slashcommand(L);
	if (!slashcommand.isValidTable())
		return 0;

	ColorlightsCommand* slashCommand = new ColorlightsCommand(slashcommand.getStringField("name"), server);
	parseSlashCommand(slashcommand, slashCommand);
	return 1;
}

int CommandConfigManager::addCombatCommand(lua_State* L) {
	LuaObject slashcommand(L);
	if (!slashcommand.isValidTable())
		return 0;

	CombatCommand* slashCommand = new CombatCommand(slashcommand.getStringField("name"), server);
	parseSlashCommand(slashcommand, slashCommand);
	return 1;
}

int CommandConfigManager::addCombatEscapeCommand(lua_State* L) {
	LuaObject slashcommand(L);
	if (!slashcommand.isValidTable())
		return 0;

	CombatEscapeCommand* slashCommand = new CombatEscapeCommand(slashcommand.getStringField("name"), server);
	parseSlashCommand(slashcommand, slashCommand);
	return 1;
}

int CommandConfigManager::addCombatModeCheckCommand(lua_State* L) {
	LuaObject slashcommand(L);
	if (!slashcommand.isValidTable())
		return 0;

	CombatModeCheckCommand* slashCommand = new CombatModeCheckCommand(slashcommand.getStringField("name"), server);
	parseSlashCommand(slashcommand, slashCommand);
	return 1;
}

int CommandConfigManager::addCombatSpamCommand(lua_State* L) {
	LuaObject slashcommand(L);
	if (!slashcommand.isValidTable())
		return 0;

	CombatSpamCommand* slashCommand = new CombatSpamCommand(slashcommand.getStringField("name"), server);
	parseSlashCommand(slashcommand, slashCommand);
	return 1;
}

int CommandConfigManager::addCombatTargetCommand(lua_State* L) {
	LuaObject slashcommand(L);
	if (!slashcommand.isValidTable())
		return 0;

	CombatTargetCommand* slashCommand = new CombatTargetCommand(slashcommand.getStringField("name"), server);
	parseSlashCommand(slashcommand, slashCommand);
	return 1;
}

int CommandConfigManager::addCompleteQuestCommand(lua_State* L) {
	LuaObject slashcommand(L);
	if (!slashcommand.isValidTable())
		return 0;

	CompleteQuestCommand* slashCommand = new CompleteQuestCommand(slashcommand.getStringField("name"), server);
	parseSlashCommand(slashcommand, slashCommand);
	return 1;
}

int CommandConfigManager::addConcealCommand(lua_State* L) {
	LuaObject slashcommand(L);
	if (!slashcommand.isValidTable())
		return 0;

	ConcealCommand* slashCommand = new ConcealCommand(slashcommand.getStringField("name"), server);
	parseSlashCommand(slashcommand, slashCommand);
	return 1;
}

int CommandConfigManager::addConcealShotCommand(lua_State* L) {
	LuaObject slashcommand(L);
	if (!slashcommand.isValidTable())
		return 0;

	ConcealShotCommand* slashCommand = new ConcealShotCommand(slashcommand.getStringField("name"), server);
	parseSlashCommand(slashcommand, slashCommand);
	return 1;
}

int CommandConfigManager::addConfusionShotCommand(lua_State* L) {
	LuaObject slashcommand(L);
	if (!slashcommand.isValidTable())
		return 0;

	ConfusionShotCommand* slashCommand = new ConfusionShotCommand(slashcommand.getStringField("name"), server);
	parseSlashCommand(slashcommand, slashCommand);
	return 1;
}

int CommandConfigManager::addConsentCommand(lua_State* L) {
	LuaObject slashcommand(L);
	if (!slashcommand.isValidTable())
		return 0;

	ConsentCommand* slashCommand = new ConsentCommand(slashcommand.getStringField("name"), server);
	parseSlashCommand(slashcommand, slashCommand);
	return 1;
}

int CommandConfigManager::addCorpseCommand(lua_State* L) {
	LuaObject slashcommand(L);
	if (!slashcommand.isValidTable())
		return 0;

	CorpseCommand* slashCommand = new CorpseCommand(slashcommand.getStringField("name"), server);
	parseSlashCommand(slashcommand, slashCommand);
	return 1;
}

int CommandConfigManager::addCounterAttackCommand(lua_State* L) {
	LuaObject slashcommand(L);
	if (!slashcommand.isValidTable())
		return 0;

	CounterAttackCommand* slashCommand = new CounterAttackCommand(slashcommand.getStringField("name"), server);
	parseSlashCommand(slashcommand, slashCommand);
	return 1;
}

int CommandConfigManager::addCoupDeGraceCommand(lua_State* L) {
	LuaObject slashcommand(L);
	if (!slashcommand.isValidTable())
		return 0;

	CoupDeGraceCommand* slashCommand = new CoupDeGraceCommand(slashcommand.getStringField("name"), server);
	parseSlashCommand(slashcommand, slashCommand);
	return 1;
}

int CommandConfigManager::addCraftCommand(lua_State* L) {
	LuaObject slashcommand(L);
	if (!slashcommand.isValidTable())
		return 0;

	CraftCommand* slashCommand = new CraftCommand(slashcommand.getStringField("name"), server);
	parseSlashCommand(slashcommand, slashCommand);
	return 1;
}

int CommandConfigManager::addCreateCreatureCommand(lua_State* L) {
	LuaObject slashcommand(L);
	if (!slashcommand.isValidTable())
		return 0;

	CreateCreatureCommand* slashCommand = new CreateCreatureCommand(slashcommand.getStringField("name"), server);
	parseSlashCommand(slashcommand, slashCommand);
	return 1;
}

int CommandConfigManager::addCreateManfSchematicCommand(lua_State* L) {
	LuaObject slashcommand(L);
	if (!slashcommand.isValidTable())
		return 0;

	CreateManfSchematicCommand* slashCommand = new CreateManfSchematicCommand(slashcommand.getStringField("name"), server);
	parseSlashCommand(slashcommand, slashCommand);
	return 1;
}

int CommandConfigManager::addCreateMissionElementCommand(lua_State* L) {
	LuaObject slashcommand(L);
	if (!slashcommand.isValidTable())
		return 0;

	CreateMissionElementCommand* slashCommand = new CreateMissionElementCommand(slashcommand.getStringField("name"), server);
	parseSlashCommand(slashcommand, slashCommand);
	return 1;
}

int CommandConfigManager::addCreateNPCCommand(lua_State* L) {
	LuaObject slashcommand(L);
	if (!slashcommand.isValidTable())
		return 0;

	CreateNPCCommand* slashCommand = new CreateNPCCommand(slashcommand.getStringField("name"), server);
	parseSlashCommand(slashcommand, slashCommand);
	return 1;
}

int CommandConfigManager::addCreatePrototypeCommand(lua_State* L) {
	LuaObject slashcommand(L);
	if (!slashcommand.isValidTable())
		return 0;

	CreatePrototypeCommand* slashCommand = new CreatePrototypeCommand(slashcommand.getStringField("name"), server);
	parseSlashCommand(slashcommand, slashCommand);
	return 1;
}

int CommandConfigManager::addCreateSpawningElementCommand(lua_State* L) {
	LuaObject slashcommand(L);
	if (!slashcommand.isValidTable())
		return 0;

	CreateSpawningElementCommand* slashCommand = new CreateSpawningElementCommand(slashcommand.getStringField("name"), server);
	parseSlashCommand(slashcommand, slashCommand);
	return 1;
}

int CommandConfigManager::addCreateSpawningElementWithDifficultyCommand(lua_State* L) {
	LuaObject slashcommand(L);
	if (!slashcommand.isValidTable())
		return 0;

	CreateSpawningElementWithDifficultyCommand* slashCommand = new CreateSpawningElementWithDifficultyCommand(slashcommand.getStringField("name"), server);
	parseSlashCommand(slashcommand, slashCommand);
	return 1;
}

int CommandConfigManager::addCreatureAreaAttackCommand(lua_State* L) {
	LuaObject slashcommand(L);
	if (!slashcommand.isValidTable())
		return 0;

	CreatureAreaAttackCommand* slashCommand = new CreatureAreaAttackCommand(slashcommand.getStringField("name"), server);
	parseSlashCommand(slashcommand, slashCommand);
	return 1;
}

int CommandConfigManager::addCreatureAreaBleedingCommand(lua_State* L) {
	LuaObject slashcommand(L);
	if (!slashcommand.isValidTable())
		return 0;

	CreatureAreaBleedingCommand* slashCommand = new CreatureAreaBleedingCommand(slashcommand.getStringField("name"), server);
	parseSlashCommand(slashcommand, slashCommand);
	return 1;
}

int CommandConfigManager::addCreatureAreaComboCommand(lua_State* L) {
	LuaObject slashcommand(L);
	if (!slashcommand.isValidTable())
		return 0;

	CreatureAreaComboCommand* slashCommand = new CreatureAreaComboCommand(slashcommand.getStringField("name"), server);
	parseSlashCommand(slashcommand, slashCommand);
	return 1;
}

int CommandConfigManager::addCreatureAreaDiseaseCommand(lua_State* L) {
	LuaObject slashcommand(L);
	if (!slashcommand.isValidTable())
		return 0;

	CreatureAreaDiseaseCommand* slashCommand = new CreatureAreaDiseaseCommand(slashcommand.getStringField("name"), server);
	parseSlashCommand(slashcommand, slashCommand);
	return 1;
}

int CommandConfigManager::addCreatureAreaKnockdownCommand(lua_State* L) {
	LuaObject slashcommand(L);
	if (!slashcommand.isValidTable())
		return 0;

	CreatureAreaKnockdownCommand* slashCommand = new CreatureAreaKnockdownCommand(slashcommand.getStringField("name"), server);
	parseSlashCommand(slashcommand, slashCommand);
	return 1;
}

int CommandConfigManager::addCreatureAreaPoisonCommand(lua_State* L) {
	LuaObject slashcommand(L);
	if (!slashcommand.isValidTable())
		return 0;

	CreatureAreaPoisonCommand* slashCommand = new CreatureAreaPoisonCommand(slashcommand.getStringField("name"), server);
	parseSlashCommand(slashcommand, slashCommand);
	return 1;
}

int CommandConfigManager::addCreditsCommand(lua_State* L) {
	LuaObject slashcommand(L);
	if (!slashcommand.isValidTable())
		return 0;

	CreditsCommand* slashCommand = new CreditsCommand(slashcommand.getStringField("name"), server);
	parseSlashCommand(slashcommand, slashCommand);
	return 1;
}

int CommandConfigManager::addCripplingShotCommand(lua_State* L) {
	LuaObject slashcommand(L);
	if (!slashcommand.isValidTable())
		return 0;

	CripplingShotCommand* slashCommand = new CripplingShotCommand(slashcommand.getStringField("name"), server);
	parseSlashCommand(slashcommand, slashCommand);
	return 1;
}

int CommandConfigManager::addCsAppendCommentCommand(lua_State* L) {
	LuaObject slashcommand(L);
	if (!slashcommand.isValidTable())
		return 0;

	CsAppendCommentCommand* slashCommand = new CsAppendCommentCommand(slashcommand.getStringField("name"), server);
	parseSlashCommand(slashcommand, slashCommand);
	return 1;
}

int CommandConfigManager::addCsCancelTicketCommand(lua_State* L) {
	LuaObject slashcommand(L);
	if (!slashcommand.isValidTable())
		return 0;

	CsCancelTicketCommand* slashCommand = new CsCancelTicketCommand(slashcommand.getStringField("name"), server);
	parseSlashCommand(slashcommand, slashCommand);
	return 1;
}

int CommandConfigManager::addCsConnectPlayerCommand(lua_State* L) {
	LuaObject slashcommand(L);
	if (!slashcommand.isValidTable())
		return 0;

	CsConnectPlayerCommand* slashCommand = new CsConnectPlayerCommand(slashcommand.getStringField("name"), server);
	parseSlashCommand(slashcommand, slashCommand);
	return 1;
}

int CommandConfigManager::addCsCreateTicketCommand(lua_State* L) {
	LuaObject slashcommand(L);
	if (!slashcommand.isValidTable())
		return 0;

	CsCreateTicketCommand* slashCommand = new CsCreateTicketCommand(slashcommand.getStringField("name"), server);
	parseSlashCommand(slashcommand, slashCommand);
	return 1;
}

int CommandConfigManager::addCsDisconnectPlayerCommand(lua_State* L) {
	LuaObject slashcommand(L);
	if (!slashcommand.isValidTable())
		return 0;

	CsDisconnectPlayerCommand* slashCommand = new CsDisconnectPlayerCommand(slashcommand.getStringField("name"), server);
	parseSlashCommand(slashcommand, slashCommand);
	return 1;
}

int CommandConfigManager::addCsGetArticleCommand(lua_State* L) {
	LuaObject slashcommand(L);
	if (!slashcommand.isValidTable())
		return 0;

	CsGetArticleCommand* slashCommand = new CsGetArticleCommand(slashcommand.getStringField("name"), server);
	parseSlashCommand(slashcommand, slashCommand);
	return 1;
}

int CommandConfigManager::addCsGetCommentsCommand(lua_State* L) {
	LuaObject slashcommand(L);
	if (!slashcommand.isValidTable())
		return 0;

	CsGetCommentsCommand* slashCommand = new CsGetCommentsCommand(slashcommand.getStringField("name"), server);
	parseSlashCommand(slashcommand, slashCommand);
	return 1;
}

int CommandConfigManager::addCsGetTicketsCommand(lua_State* L) {
	LuaObject slashcommand(L);
	if (!slashcommand.isValidTable())
		return 0;

	CsGetTicketsCommand* slashCommand = new CsGetTicketsCommand(slashcommand.getStringField("name"), server);
	parseSlashCommand(slashcommand, slashCommand);
	return 1;
}

int CommandConfigManager::addCsRequestCategoriesCommand(lua_State* L) {
	LuaObject slashcommand(L);
	if (!slashcommand.isValidTable())
		return 0;

	CsRequestCategoriesCommand* slashCommand = new CsRequestCategoriesCommand(slashcommand.getStringField("name"), server);
	parseSlashCommand(slashcommand, slashCommand);
	return 1;
}

int CommandConfigManager::addCsSearchKnowledgeBaseCommand(lua_State* L) {
	LuaObject slashcommand(L);
	if (!slashcommand.isValidTable())
		return 0;

	CsSearchKnowledgeBaseCommand* slashCommand = new CsSearchKnowledgeBaseCommand(slashcommand.getStringField("name"), server);
	parseSlashCommand(slashcommand, slashCommand);
	return 1;
}

int CommandConfigManager::addCuiConsentResponseCommand(lua_State* L) {
	LuaObject slashcommand(L);
	if (!slashcommand.isValidTable())
		return 0;

	CuiConsentResponseCommand* slashCommand = new CuiConsentResponseCommand(slashcommand.getStringField("name"), server);
	parseSlashCommand(slashcommand, slashCommand);
	return 1;
}

int CommandConfigManager::addCureDiseaseCommand(lua_State* L) {
	LuaObject slashcommand(L);
	if (!slashcommand.isValidTable())
		return 0;

	CureDiseaseCommand* slashCommand = new CureDiseaseCommand(slashcommand.getStringField("name"), server);
	parseSlashCommand(slashcommand, slashCommand);
	return 1;
}

int CommandConfigManager::addCurePoisonCommand(lua_State* L) {
	LuaObject slashcommand(L);
	if (!slashcommand.isValidTable())
		return 0;

	CurePoisonCommand* slashCommand = new CurePoisonCommand(slashcommand.getStringField("name"), server);
	parseSlashCommand(slashcommand, slashCommand);
	return 1;
}

int CommandConfigManager::addCustomizeDroidCommand(lua_State* L) {
	LuaObject slashcommand(L);
	if (!slashcommand.isValidTable())
		return 0;

	CustomizeDroidCommand* slashCommand = new CustomizeDroidCommand(slashcommand.getStringField("name"), server);
	parseSlashCommand(slashcommand, slashCommand);
	return 1;
}

int CommandConfigManager::addCustomizeVehicleCommand(lua_State* L) {
	LuaObject slashcommand(L);
	if (!slashcommand.isValidTable())
		return 0;

	CustomizeVehicleCommand* slashCommand = new CustomizeVehicleCommand(slashcommand.getStringField("name"), server);
	parseSlashCommand(slashcommand, slashCommand);
	return 1;
}

int CommandConfigManager::addDatabaseCommand(lua_State* L) {
	LuaObject slashcommand(L);
	if (!slashcommand.isValidTable())
		return 0;

	DatabaseCommand* slashCommand = new DatabaseCommand(slashcommand.getStringField("name"), server);
	parseSlashCommand(slashcommand, slashCommand);
	return 1;
}

int CommandConfigManager::addDazzleCommand(lua_State* L) {
	LuaObject slashcommand(L);
	if (!slashcommand.isValidTable())
		return 0;

	DazzleCommand* slashCommand = new DazzleCommand(slashcommand.getStringField("name"), server);
	parseSlashCommand(slashcommand, slashCommand);
	return 1;
}

int CommandConfigManager::addDeactivateQuestCommand(lua_State* L) {
	LuaObject slashcommand(L);
	if (!slashcommand.isValidTable())
		return 0;

	DeactivateQuestCommand* slashCommand = new DeactivateQuestCommand(slashcommand.getStringField("name"), server);
	parseSlashCommand(slashcommand, slashCommand);
	return 1;
}

int CommandConfigManager::addDeathBlowCommand(lua_State* L) {
	LuaObject slashcommand(L);
	if (!slashcommand.isValidTable())
		return 0;

	DeathBlowCommand* slashCommand = new DeathBlowCommand(slashcommand.getStringField("name"), server);
	parseSlashCommand(slashcommand, slashCommand);
	return 1;
}

int CommandConfigManager::addDeathCountCommand(lua_State* L) {
	LuaObject slashcommand(L);
	if (!slashcommand.isValidTable())
		return 0;

	DeathCountCommand* slashCommand = new DeathCountCommand(slashcommand.getStringField("name"), server);
	parseSlashCommand(slashcommand, slashCommand);
	return 1;
}

int CommandConfigManager::addDeclareOvertCommand(lua_State* L) {
	LuaObject slashcommand(L);
	if (!slashcommand.isValidTable())
		return 0;

	DeclareOvertCommand* slashCommand = new DeclareOvertCommand(slashcommand.getStringField("name"), server);
	parseSlashCommand(slashcommand, slashCommand);
	return 1;
}

int CommandConfigManager::addDeclareresidenceCommand(lua_State* L) {
	LuaObject slashcommand(L);
	if (!slashcommand.isValidTable())
		return 0;

	DeclareresidenceCommand* slashCommand = new DeclareresidenceCommand(slashcommand.getStringField("name"), server);
	parseSlashCommand(slashcommand, slashCommand);
	return 1;
}

int CommandConfigManager::addDeclineCommand(lua_State* L) {
	LuaObject slashcommand(L);
	if (!slashcommand.isValidTable())
		return 0;

	DeclineCommand* slashCommand = new DeclineCommand(slashcommand.getStringField("name"), server);
	parseSlashCommand(slashcommand, slashCommand);
	return 1;
}

int CommandConfigManager::addDefaultAttackCommand(lua_State* L) {
	LuaObject slashcommand(L);
	if (!slashcommand.isValidTable())
		return 0;

	DefaultAttackCommand* slashCommand = new DefaultAttackCommand(slashcommand.getStringField("name"), server);
	parseSlashCommand(slashcommand, slashCommand);
	return 1;
}

int CommandConfigManager::addDefuseMinefieldCommand(lua_State* L) {
	LuaObject slashcommand(L);
	if (!slashcommand.isValidTable())
		return 0;

	DefuseMinefieldCommand* slashCommand = new DefuseMinefieldCommand(slashcommand.getStringField("name"), server);
	parseSlashCommand(slashcommand, slashCommand);
	return 1;
}

int CommandConfigManager::addDelegateFactionPointsCommand(lua_State* L) {
	LuaObject slashcommand(L);
	if (!slashcommand.isValidTable())
		return 0;

	DelegateFactionPointsCommand* slashCommand = new DelegateFactionPointsCommand(slashcommand.getStringField("name"), server);
	parseSlashCommand(slashcommand, slashCommand);
	return 1;
}

int CommandConfigManager::addDenyServiceCommand(lua_State* L) {
	LuaObject slashcommand(L);
	if (!slashcommand.isValidTable())
		return 0;

	DenyServiceCommand* slashCommand = new DenyServiceCommand(slashcommand.getStringField("name"), server);
	parseSlashCommand(slashcommand, slashCommand);
	return 1;
}

int CommandConfigManager::addDeployTrapCommand(lua_State* L) {
	LuaObject slashcommand(L);
	if (!slashcommand.isValidTable())
		return 0;

	DeployTrapCommand* slashCommand = new DeployTrapCommand(slashcommand.getStringField("name"), server);
	parseSlashCommand(slashcommand, slashCommand);
	return 1;
}

int CommandConfigManager::addDestroyCommand(lua_State* L) {
	LuaObject slashcommand(L);
	if (!slashcommand.isValidTable())
		return 0;

	DestroyCommand* slashCommand = new DestroyCommand(slashcommand.getStringField("name"), server);
	parseSlashCommand(slashcommand, slashCommand);
	return 1;
}

int CommandConfigManager::addDestroystructureCommand(lua_State* L) {
	LuaObject slashcommand(L);
	if (!slashcommand.isValidTable())
		return 0;

	DestroystructureCommand* slashCommand = new DestroystructureCommand(slashcommand.getStringField("name"), server);
	parseSlashCommand(slashcommand, slashCommand);
	return 1;
}

int CommandConfigManager::addDetonateDroidCommand(lua_State* L) {
	LuaObject slashcommand(L);
	if (!slashcommand.isValidTable())
		return 0;

	DetonateDroidCommand* slashCommand = new DetonateDroidCommand(slashcommand.getStringField("name"), server);
	parseSlashCommand(slashcommand, slashCommand);
	return 1;
}

int CommandConfigManager::addDiagnoseCommand(lua_State* L) {
	LuaObject slashcommand(L);
	if (!slashcommand.isValidTable())
		return 0;

	DiagnoseCommand* slashCommand = new DiagnoseCommand(slashcommand.getStringField("name"), server);
	parseSlashCommand(slashcommand, slashCommand);
	return 1;
}

int CommandConfigManager::addDisarmingShot1Command(lua_State* L) {
	LuaObject slashcommand(L);
	if (!slashcommand.isValidTable())
		return 0;

	DisarmingShot1Command* slashCommand = new DisarmingShot1Command(slashcommand.getStringField("name"), server);
	parseSlashCommand(slashcommand, slashCommand);
	return 1;
}

int CommandConfigManager::addDisarmingShot2Command(lua_State* L) {
	LuaObject slashcommand(L);
	if (!slashcommand.isValidTable())
		return 0;

	DisarmingShot2Command* slashCommand = new DisarmingShot2Command(slashcommand.getStringField("name"), server);
	parseSlashCommand(slashcommand, slashCommand);
	return 1;
}

int CommandConfigManager::addDisbandCommand(lua_State* L) {
	LuaObject slashcommand(L);
	if (!slashcommand.isValidTable())
		return 0;

	DisbandCommand* slashCommand = new DisbandCommand(slashcommand.getStringField("name"), server);
	parseSlashCommand(slashcommand, slashCommand);
	return 1;
}

int CommandConfigManager::addDismissGroupMemberCommand(lua_State* L) {
	LuaObject slashcommand(L);
	if (!slashcommand.isValidTable())
		return 0;

	DismissGroupMemberCommand* slashCommand = new DismissGroupMemberCommand(slashcommand.getStringField("name"), server);
	parseSlashCommand(slashcommand, slashCommand);
	return 1;
}

int CommandConfigManager::addDismountCommand(lua_State* L) {
	LuaObject slashcommand(L);
	if (!slashcommand.isValidTable())
		return 0;

	DismountCommand* slashCommand = new DismountCommand(slashcommand.getStringField("name"), server);
	parseSlashCommand(slashcommand, slashCommand);
	return 1;
}

int CommandConfigManager::addDismountandstoreCommand(lua_State* L) {
	LuaObject slashcommand(L);
	if (!slashcommand.isValidTable())
		return 0;

	DismountandstoreCommand* slashCommand = new DismountandstoreCommand(slashcommand.getStringField("name"), server);
	parseSlashCommand(slashcommand, slashCommand);
	return 1;
}

int CommandConfigManager::addDistractCommand(lua_State* L) {
	LuaObject slashcommand(L);
	if (!slashcommand.isValidTable())
		return 0;

	DistractCommand* slashCommand = new DistractCommand(slashcommand.getStringField("name"), server);
	parseSlashCommand(slashcommand, slashCommand);
	return 1;
}

int CommandConfigManager::addDiveShotCommand(lua_State* L) {
	LuaObject slashcommand(L);
	if (!slashcommand.isValidTable())
		return 0;

	DiveShotCommand* slashCommand = new DiveShotCommand(slashcommand.getStringField("name"), server);
	parseSlashCommand(slashcommand, slashCommand);
	return 1;
}

int CommandConfigManager::addDizzyAttackCommand(lua_State* L) {
	LuaObject slashcommand(L);
	if (!slashcommand.isValidTable())
		return 0;

	DizzyAttackCommand* slashCommand = new DizzyAttackCommand(slashcommand.getStringField("name"), server);
	parseSlashCommand(slashcommand, slashCommand);
	return 1;
}

int CommandConfigManager::addDoubleTapCommand(lua_State* L) {
	LuaObject slashcommand(L);
	if (!slashcommand.isValidTable())
		return 0;

	DoubleTapCommand* slashCommand = new DoubleTapCommand(slashcommand.getStringField("name"), server);
	parseSlashCommand(slashcommand, slashCommand);
	return 1;
}

int CommandConfigManager::addDragIncapacitatedPlayerCommand(lua_State* L) {
	LuaObject slashcommand(L);
	if (!slashcommand.isValidTable())
		return 0;

	DragIncapacitatedPlayerCommand* slashCommand = new DragIncapacitatedPlayerCommand(slashcommand.getStringField("name"), server);
	parseSlashCommand(slashcommand, slashCommand);
	return 1;
}

int CommandConfigManager::addDrainForceCommand(lua_State* L) {
	LuaObject slashcommand(L);
	if (!slashcommand.isValidTable())
		return 0;

	DrainForceCommand* slashCommand = new DrainForceCommand(slashcommand.getStringField("name"), server);
	parseSlashCommand(slashcommand, slashCommand);
	return 1;
}

int CommandConfigManager::addDuelCommand(lua_State* L) {
	LuaObject slashcommand(L);
	if (!slashcommand.isValidTable())
		return 0;

	DuelCommand* slashCommand = new DuelCommand(slashcommand.getStringField("name"), server);
	parseSlashCommand(slashcommand, slashCommand);
	return 1;
}

int CommandConfigManager::addDumpTargetInformationCommand(lua_State* L) {
	LuaObject slashcommand(L);
	if (!slashcommand.isValidTable())
		return 0;

	DumpTargetInformationCommand* slashCommand = new DumpTargetInformationCommand(slashcommand.getStringField("name"), server);
	parseSlashCommand(slashcommand, slashCommand);
	return 1;
}

int CommandConfigManager::addDumpZoneInformationCommand(lua_State* L) {
	LuaObject slashcommand(L);
	if (!slashcommand.isValidTable())
		return 0;

	DumpZoneInformationCommand* slashCommand = new DumpZoneInformationCommand(slashcommand.getStringField("name"), server);
	parseSlashCommand(slashcommand, slashCommand);
	return 1;
}

int CommandConfigManager::addEatCommand(lua_State* L) {
	LuaObject slashcommand(L);
	if (!slashcommand.isValidTable())
		return 0;

	EatCommand* slashCommand = new EatCommand(slashcommand.getStringField("name"), server);
	parseSlashCommand(slashcommand, slashCommand);
	return 1;
}

int CommandConfigManager::addEditAppearanceCommand(lua_State* L) {
	LuaObject slashcommand(L);
	if (!slashcommand.isValidTable())
		return 0;

	EditAppearanceCommand* slashCommand = new EditAppearanceCommand(slashcommand.getStringField("name"), server);
	parseSlashCommand(slashcommand, slashCommand);
	return 1;
}

int CommandConfigManager::addEditBankCommand(lua_State* L) {
	LuaObject slashcommand(L);
	if (!slashcommand.isValidTable())
		return 0;

	EditBankCommand* slashCommand = new EditBankCommand(slashcommand.getStringField("name"), server);
	parseSlashCommand(slashcommand, slashCommand);
	return 1;
}

int CommandConfigManager::addEditBankAccountCommand(lua_State* L) {
	LuaObject slashcommand(L);
	if (!slashcommand.isValidTable())
		return 0;

	EditBankAccountCommand* slashCommand = new EditBankAccountCommand(slashcommand.getStringField("name"), server);
	parseSlashCommand(slashcommand, slashCommand);
	return 1;
}

int CommandConfigManager::addEditStatsCommand(lua_State* L) {
	LuaObject slashcommand(L);
	if (!slashcommand.isValidTable())
		return 0;

	EditStatsCommand* slashCommand = new EditStatsCommand(slashcommand.getStringField("name"), server);
	parseSlashCommand(slashcommand, slashCommand);
	return 1;
}

int CommandConfigManager::addEmboldenpetsCommand(lua_State* L) {
	LuaObject slashcommand(L);
	if (!slashcommand.isValidTable())
		return 0;

	EmboldenpetsCommand* slashCommand = new EmboldenpetsCommand(slashcommand.getStringField("name"), server);
	parseSlashCommand(slashcommand, slashCommand);
	return 1;
}

int CommandConfigManager::addEmptyMailTargetCommand(lua_State* L) {
	LuaObject slashcommand(L);
	if (!slashcommand.isValidTable())
		return 0;

	EmptyMailTargetCommand* slashCommand = new EmptyMailTargetCommand(slashcommand.getStringField("name"), server);
	parseSlashCommand(slashcommand, slashCommand);
	return 1;
}

int CommandConfigManager::addEndDuelCommand(lua_State* L) {
	LuaObject slashcommand(L);
	if (!slashcommand.isValidTable())
		return 0;

	EndDuelCommand* slashCommand = new EndDuelCommand(slashcommand.getStringField("name"), server);
	parseSlashCommand(slashcommand, slashCommand);
	return 1;
}

int CommandConfigManager::addEnragepetsCommand(lua_State* L) {
	LuaObject slashcommand(L);
	if (!slashcommand.isValidTable())
		return 0;

	EnragepetsCommand* slashCommand = new EnragepetsCommand(slashcommand.getStringField("name"), server);
	parseSlashCommand(slashcommand, slashCommand);
	return 1;
}

int CommandConfigManager::addEquilibriumCommand(lua_State* L) {
	LuaObject slashcommand(L);
	if (!slashcommand.isValidTable())
		return 0;

	EquilibriumCommand* slashCommand = new EquilibriumCommand(slashcommand.getStringField("name"), server);
	parseSlashCommand(slashcommand, slashCommand);
	return 1;
}

int CommandConfigManager::addExecuteKnowledgeBaseMessageCommand(lua_State* L) {
	LuaObject slashcommand(L);
	if (!slashcommand.isValidTable())
		return 0;

	ExecuteKnowledgeBaseMessageCommand* slashCommand = new ExecuteKnowledgeBaseMessageCommand(slashcommand.getStringField("name"), server);
	parseSlashCommand(slashcommand, slashCommand);
	return 1;
}

int CommandConfigManager::addExtinguishFireCommand(lua_State* L) {
	LuaObject slashcommand(L);
	if (!slashcommand.isValidTable())
		return 0;

	ExtinguishFireCommand* slashCommand = new ExtinguishFireCommand(slashcommand.getStringField("name"), server);
	parseSlashCommand(slashcommand, slashCommand);
	return 1;
}

int CommandConfigManager::addExtractObjectCommand(lua_State* L) {
	LuaObject slashcommand(L);
	if (!slashcommand.isValidTable())
		return 0;

	ExtractObjectCommand* slashCommand = new ExtractObjectCommand(slashcommand.getStringField("name"), server);
	parseSlashCommand(slashcommand, slashCommand);
	return 1;
}

int CommandConfigManager::addEyeShotCommand(lua_State* L) {
	LuaObject slashcommand(L);
	if (!slashcommand.isValidTable())
		return 0;

	EyeShotCommand* slashCommand = new EyeShotCommand(slashcommand.getStringField("name"), server);
	parseSlashCommand(slashcommand, slashCommand);
	return 1;
}

int CommandConfigManager::addFactoryCrateSplitCommand(lua_State* L) {
	LuaObject slashcommand(L);
	if (!slashcommand.isValidTable())
		return 0;

	FactoryCrateSplitCommand* slashCommand = new FactoryCrateSplitCommand(slashcommand.getStringField("name"), server);
	parseSlashCommand(slashcommand, slashCommand);
	return 1;
}

int CommandConfigManager::addFanShotCommand(lua_State* L) {
	LuaObject slashcommand(L);
	if (!slashcommand.isValidTable())
		return 0;

	FanShotCommand* slashCommand = new FanShotCommand(slashcommand.getStringField("name"), server);
	parseSlashCommand(slashcommand, slashCommand);
	return 1;
}

int CommandConfigManager::addFastBlastCommand(lua_State* L) {
	LuaObject slashcommand(L);
	if (!slashcommand.isValidTable())
		return 0;

	FastBlastCommand* slashCommand = new FastBlastCommand(slashcommand.getStringField("name"), server);
	parseSlashCommand(slashcommand, slashCommand);
	return 1;
}

int CommandConfigManager::addFeignDeathCommand(lua_State* L) {
	LuaObject slashcommand(L);
	if (!slashcommand.isValidTable())
		return 0;

	FeignDeathCommand* slashCommand = new FeignDeathCommand(slashcommand.getStringField("name"), server);
	parseSlashCommand(slashcommand, slashCommand);
	return 1;
}

int CommandConfigManager::addFindCommand(lua_State* L) {
	LuaObject slashcommand(L);
	if (!slashcommand.isValidTable())
		return 0;

	FindCommand* slashCommand = new FindCommand(slashcommand.getStringField("name"), server);
	parseSlashCommand(slashcommand, slashCommand);
	return 1;
}

int CommandConfigManager::addFindFriendCommand(lua_State* L) {
	LuaObject slashcommand(L);
	if (!slashcommand.isValidTable())
		return 0;

	FindFriendCommand* slashCommand = new FindFriendCommand(slashcommand.getStringField("name"), server);
	parseSlashCommand(slashcommand, slashCommand);
	return 1;
}

int CommandConfigManager::addFindMyTrainerCommand(lua_State* L) {
	LuaObject slashcommand(L);
	if (!slashcommand.isValidTable())
		return 0;

	FindMyTrainerCommand* slashCommand = new FindMyTrainerCommand(slashcommand.getStringField("name"), server);
	parseSlashCommand(slashcommand, slashCommand);
	return 1;
}

int CommandConfigManager::addFindObjectCommand(lua_State* L) {
	LuaObject slashcommand(L);
	if (!slashcommand.isValidTable())
		return 0;

	FindObjectCommand* slashCommand = new FindObjectCommand(slashcommand.getStringField("name"), server);
	parseSlashCommand(slashcommand, slashCommand);
	return 1;
}

int CommandConfigManager::addFindPlayerCommand(lua_State* L) {
	LuaObject slashcommand(L);
	if (!slashcommand.isValidTable())
		return 0;

	FindPlayerCommand* slashCommand = new FindPlayerCommand(slashcommand.getStringField("name"), server);
	parseSlashCommand(slashcommand, slashCommand);
	return 1;
}

int CommandConfigManager::addFireAcidCone1Command(lua_State* L) {
	LuaObject slashcommand(L);
	if (!slashcommand.isValidTable())
		return 0;

	FireAcidCone1Command* slashCommand = new FireAcidCone1Command(slashcommand.getStringField("name"), server);
	parseSlashCommand(slashcommand, slashCommand);
	return 1;
}

int CommandConfigManager::addFireAcidCone2Command(lua_State* L) {
	LuaObject slashcommand(L);
	if (!slashcommand.isValidTable())
		return 0;

	FireAcidCone2Command* slashCommand = new FireAcidCone2Command(slashcommand.getStringField("name"), server);
	parseSlashCommand(slashcommand, slashCommand);
	return 1;
}

int CommandConfigManager::addFireAcidSingle1Command(lua_State* L) {
	LuaObject slashcommand(L);
	if (!slashcommand.isValidTable())
		return 0;

	FireAcidSingle1Command* slashCommand = new FireAcidSingle1Command(slashcommand.getStringField("name"), server);
	parseSlashCommand(slashcommand, slashCommand);
	return 1;
}

int CommandConfigManager::addFireAcidSingle2Command(lua_State* L) {
	LuaObject slashcommand(L);
	if (!slashcommand.isValidTable())
		return 0;

	FireAcidSingle2Command* slashCommand = new FireAcidSingle2Command(slashcommand.getStringField("name"), server);
	parseSlashCommand(slashcommand, slashCommand);
	return 1;
}

int CommandConfigManager::addFireHeavyWeaponCommand(lua_State* L) {
	LuaObject slashcommand(L);
	if (!slashcommand.isValidTable())
		return 0;

	FireHeavyWeaponCommand* slashCommand = new FireHeavyWeaponCommand(slashcommand.getStringField("name"), server);
	parseSlashCommand(slashcommand, slashCommand);
	return 1;
}

int CommandConfigManager::addFirejetCommand(lua_State* L) {
	LuaObject slashcommand(L);
	if (!slashcommand.isValidTable())
		return 0;

	FirejetCommand* slashCommand = new FirejetCommand(slashcommand.getStringField("name"), server);
	parseSlashCommand(slashcommand, slashCommand);
	return 1;
}

int CommandConfigManager::addFireLightningCone1Command(lua_State* L) {
	LuaObject slashcommand(L);
	if (!slashcommand.isValidTable())
		return 0;

	FireLightningCone1Command* slashCommand = new FireLightningCone1Command(slashcommand.getStringField("name"), server);
	parseSlashCommand(slashcommand, slashCommand);
	return 1;
}

int CommandConfigManager::addFireLightningCone2Command(lua_State* L) {
	LuaObject slashcommand(L);
	if (!slashcommand.isValidTable())
		return 0;

	FireLightningCone2Command* slashCommand = new FireLightningCone2Command(slashcommand.getStringField("name"), server);
	parseSlashCommand(slashcommand, slashCommand);
	return 1;
}

int CommandConfigManager::addFireLightningSingle1Command(lua_State* L) {
	LuaObject slashcommand(L);
	if (!slashcommand.isValidTable())
		return 0;

	FireLightningSingle1Command* slashCommand = new FireLightningSingle1Command(slashcommand.getStringField("name"), server);
	parseSlashCommand(slashcommand, slashCommand);
	return 1;
}

int CommandConfigManager::addFireLightningSingle2Command(lua_State* L) {
	LuaObject slashcommand(L);
	if (!slashcommand.isValidTable())
		return 0;

	FireLightningSingle2Command* slashCommand = new FireLightningSingle2Command(slashcommand.getStringField("name"), server);
	parseSlashCommand(slashcommand, slashCommand);
	return 1;
}

int CommandConfigManager::addFirstAidCommand(lua_State* L) {
	LuaObject slashcommand(L);
	if (!slashcommand.isValidTable())
		return 0;

	FirstAidCommand* slashCommand = new FirstAidCommand(slashcommand.getStringField("name"), server);
	parseSlashCommand(slashcommand, slashCommand);
	return 1;
}

int CommandConfigManager::addFishCommand(lua_State* L) {
	LuaObject slashcommand(L);
	if (!slashcommand.isValidTable())
		return 0;

	FishCommand* slashCommand = new FishCommand(slashcommand.getStringField("name"), server);
	parseSlashCommand(slashcommand, slashCommand);
	return 1;
}

int CommandConfigManager::addFlameCone1Command(lua_State* L) {
	LuaObject slashcommand(L);
	if (!slashcommand.isValidTable())
		return 0;

	FlameCone1Command* slashCommand = new FlameCone1Command(slashcommand.getStringField("name"), server);
	parseSlashCommand(slashcommand, slashCommand);
	return 1;
}

int CommandConfigManager::addFlameCone2Command(lua_State* L) {
	LuaObject slashcommand(L);
	if (!slashcommand.isValidTable())
		return 0;

	FlameCone2Command* slashCommand = new FlameCone2Command(slashcommand.getStringField("name"), server);
	parseSlashCommand(slashcommand, slashCommand);
	return 1;
}

int CommandConfigManager::addFlameSingle1Command(lua_State* L) {
	LuaObject slashcommand(L);
	if (!slashcommand.isValidTable())
		return 0;

	FlameSingle1Command* slashCommand = new FlameSingle1Command(slashcommand.getStringField("name"), server);
	parseSlashCommand(slashcommand, slashCommand);
	return 1;
}

int CommandConfigManager::addFlameSingle2Command(lua_State* L) {
	LuaObject slashcommand(L);
	if (!slashcommand.isValidTable())
		return 0;

	FlameSingle2Command* slashCommand = new FlameSingle2Command(slashcommand.getStringField("name"), server);
	parseSlashCommand(slashcommand, slashCommand);
	return 1;
}

int CommandConfigManager::addFlashSpeederCommand(lua_State* L) {
	LuaObject slashcommand(L);
	if (!slashcommand.isValidTable())
		return 0;

	FlashSpeederCommand* slashCommand = new FlashSpeederCommand(slashcommand.getStringField("name"), server);
	parseSlashCommand(slashcommand, slashCommand);
	return 1;
}

int CommandConfigManager::addFlourishCommand(lua_State* L) {
	LuaObject slashcommand(L);
	if (!slashcommand.isValidTable())
		return 0;

	FlourishCommand* slashCommand = new FlourishCommand(slashcommand.getStringField("name"), server);
	parseSlashCommand(slashcommand, slashCommand);
	return 1;
}

int CommandConfigManager::addFlurryShot1Command(lua_State* L) {
	LuaObject slashcommand(L);
	if (!slashcommand.isValidTable())
		return 0;

	FlurryShot1Command* slashCommand = new FlurryShot1Command(slashcommand.getStringField("name"), server);
	parseSlashCommand(slashcommand, slashCommand);
	return 1;
}

int CommandConfigManager::addFlurryShot2Command(lua_State* L) {
	LuaObject slashcommand(L);
	if (!slashcommand.isValidTable())
		return 0;

	FlurryShot2Command* slashCommand = new FlurryShot2Command(slashcommand.getStringField("name"), server);
	parseSlashCommand(slashcommand, slashCommand);
	return 1;
}

int CommandConfigManager::addFlushingShot1Command(lua_State* L) {
	LuaObject slashcommand(L);
	if (!slashcommand.isValidTable())
		return 0;

	FlushingShot1Command* slashCommand = new FlushingShot1Command(slashcommand.getStringField("name"), server);
	parseSlashCommand(slashcommand, slashCommand);
	return 1;
}

int CommandConfigManager::addFlushingShot2Command(lua_State* L) {
	LuaObject slashcommand(L);
	if (!slashcommand.isValidTable())
		return 0;

	FlushingShot2Command* slashCommand = new FlushingShot2Command(slashcommand.getStringField("name"), server);
	parseSlashCommand(slashcommand, slashCommand);
	return 1;
}

int CommandConfigManager::addForageCommand(lua_State* L) {
	LuaObject slashcommand(L);
	if (!slashcommand.isValidTable())
		return 0;

	ForageCommand* slashCommand = new ForageCommand(slashcommand.getStringField("name"), server);
	parseSlashCommand(slashcommand, slashCommand);
	return 1;
}

int CommandConfigManager::addForceAbsorb1Command(lua_State* L) {
	LuaObject slashcommand(L);
	if (!slashcommand.isValidTable())
		return 0;

	ForceAbsorb1Command* slashCommand = new ForceAbsorb1Command(slashcommand.getStringField("name"), server);
	parseSlashCommand(slashcommand, slashCommand);
	return 1;
}

int CommandConfigManager::addForceAbsorb2Command(lua_State* L) {
	LuaObject slashcommand(L);
	if (!slashcommand.isValidTable())
		return 0;

	ForceAbsorb2Command* slashCommand = new ForceAbsorb2Command(slashcommand.getStringField("name"), server);
	parseSlashCommand(slashcommand, slashCommand);
	return 1;
}

int CommandConfigManager::addForceArmor1Command(lua_State* L) {
	LuaObject slashcommand(L);
	if (!slashcommand.isValidTable())
		return 0;

	ForceArmor1Command* slashCommand = new ForceArmor1Command(slashcommand.getStringField("name"), server);
	parseSlashCommand(slashcommand, slashCommand);
	return 1;
}

int CommandConfigManager::addForceArmor2Command(lua_State* L) {
	LuaObject slashcommand(L);
	if (!slashcommand.isValidTable())
		return 0;

	ForceArmor2Command* slashCommand = new ForceArmor2Command(slashcommand.getStringField("name"), server);
	parseSlashCommand(slashcommand, slashCommand);
	return 1;
}

int CommandConfigManager::addForceChokeCommand(lua_State* L) {
	LuaObject slashcommand(L);
	if (!slashcommand.isValidTable())
		return 0;

	ForceChokeCommand* slashCommand = new ForceChokeCommand(slashcommand.getStringField("name"), server);
	parseSlashCommand(slashcommand, slashCommand);
	return 1;
}

int CommandConfigManager::addForceCommandCommand(lua_State* L) {
	LuaObject slashcommand(L);
	if (!slashcommand.isValidTable())
		return 0;

	ForceCommandCommand* slashCommand = new ForceCommandCommand(slashcommand.getStringField("name"), server);
	parseSlashCommand(slashcommand, slashCommand);
	return 1;
}

int CommandConfigManager::addForceCureDiseaseCommand(lua_State* L) {
	LuaObject slashcommand(L);
	if (!slashcommand.isValidTable())
		return 0;

	ForceCureDiseaseCommand* slashCommand = new ForceCureDiseaseCommand(slashcommand.getStringField("name"), server);
	parseSlashCommand(slashcommand, slashCommand);
	return 1;
}

int CommandConfigManager::addForceCurePoisonCommand(lua_State* L) {
	LuaObject slashcommand(L);
	if (!slashcommand.isValidTable())
		return 0;

	ForceCurePoisonCommand* slashCommand = new ForceCurePoisonCommand(slashcommand.getStringField("name"), server);
	parseSlashCommand(slashcommand, slashCommand);
	return 1;
}

int CommandConfigManager::addForceFeedback1Command(lua_State* L) {
	LuaObject slashcommand(L);
	if (!slashcommand.isValidTable())
		return 0;

	ForceFeedback1Command* slashCommand = new ForceFeedback1Command(slashcommand.getStringField("name"), server);
	parseSlashCommand(slashcommand, slashCommand);
	return 1;
}

int CommandConfigManager::addForceFeedback2Command(lua_State* L) {
	LuaObject slashcommand(L);
	if (!slashcommand.isValidTable())
		return 0;

	ForceFeedback2Command* slashCommand = new ForceFeedback2Command(slashcommand.getStringField("name"), server);
	parseSlashCommand(slashcommand, slashCommand);
	return 1;
}

int CommandConfigManager::addForceIntimidate1Command(lua_State* L) {
	LuaObject slashcommand(L);
	if (!slashcommand.isValidTable())
		return 0;

	ForceIntimidate1Command* slashCommand = new ForceIntimidate1Command(slashcommand.getStringField("name"), server);
	parseSlashCommand(slashcommand, slashCommand);
	return 1;
}

int CommandConfigManager::addForceIntimidate2Command(lua_State* L) {
	LuaObject slashcommand(L);
	if (!slashcommand.isValidTable())
		return 0;

	ForceIntimidate2Command* slashCommand = new ForceIntimidate2Command(slashcommand.getStringField("name"), server);
	parseSlashCommand(slashcommand, slashCommand);
	return 1;
}

int CommandConfigManager::addForceKnockdown1Command(lua_State* L) {
	LuaObject slashcommand(L);
	if (!slashcommand.isValidTable())
		return 0;

	ForceKnockdown1Command* slashCommand = new ForceKnockdown1Command(slashcommand.getStringField("name"), server);
	parseSlashCommand(slashcommand, slashCommand);
	return 1;
}

int CommandConfigManager::addForceKnockdown2Command(lua_State* L) {
	LuaObject slashcommand(L);
	if (!slashcommand.isValidTable())
		return 0;

	ForceKnockdown2Command* slashCommand = new ForceKnockdown2Command(slashcommand.getStringField("name"), server);
	parseSlashCommand(slashcommand, slashCommand);
	return 1;
}

int CommandConfigManager::addForceKnockdown3Command(lua_State* L) {
	LuaObject slashcommand(L);
	if (!slashcommand.isValidTable())
		return 0;

	ForceKnockdown3Command* slashCommand = new ForceKnockdown3Command(slashcommand.getStringField("name"), server);
	parseSlashCommand(slashcommand, slashCommand);
	return 1;
}

int CommandConfigManager::addForceLightningCone1Command(lua_State* L) {
	LuaObject slashcommand(L);
	if (!slashcommand.isValidTable())
		return 0;

	ForceLightningCone1Command* slashCommand = new ForceLightningCone1Command(slashcommand.getStringField("name"), server);
	parseSlashCommand(slashcommand, slashCommand);
	return 1;
}

int CommandConfigManager::addForceLightningCone2Command(lua_State* L) {
	LuaObject slashcommand(L);
	if (!slashcommand.isValidTable())
		return 0;

	ForceLightningCone2Command* slashCommand = new ForceLightningCone2Command(slashcommand.getStringField("name"), server);
	parseSlashCommand(slashcommand, slashCommand);
	return 1;
}

int CommandConfigManager::addForceLightningSingle1Command(lua_State* L) {
	LuaObject slashcommand(L);
	if (!slashcommand.isValidTable())
		return 0;

	ForceLightningSingle1Command* slashCommand = new ForceLightningSingle1Command(slashcommand.getStringField("name"), server);
	parseSlashCommand(slashcommand, slashCommand);
	return 1;
}

int CommandConfigManager::addForceLightningSingle2Command(lua_State* L) {
	LuaObject slashcommand(L);
	if (!slashcommand.isValidTable())
		return 0;

	ForceLightningSingle2Command* slashCommand = new ForceLightningSingle2Command(slashcommand.getStringField("name"), server);
	parseSlashCommand(slashcommand, slashCommand);
	return 1;
}

int CommandConfigManager::addForceMeditateCommand(lua_State* L) {
	LuaObject slashcommand(L);
	if (!slashcommand.isValidTable())
		return 0;

	ForceMeditateCommand* slashCommand = new ForceMeditateCommand(slashcommand.getStringField("name"), server);
	parseSlashCommand(slashcommand, slashCommand);
	return 1;
}

int CommandConfigManager::addForceOfWillCommand(lua_State* L) {
	LuaObject slashcommand(L);
	if (!slashcommand.isValidTable())
		return 0;

	ForceOfWillCommand* slashCommand = new ForceOfWillCommand(slashcommand.getStringField("name"), server);
	parseSlashCommand(slashcommand, slashCommand);
	return 1;
}

int CommandConfigManager::addForceProtectionCommand(lua_State* L) {
	LuaObject slashcommand(L);
	if (!slashcommand.isValidTable())
		return 0;

	ForceProtectionCommand* slashCommand = new ForceProtectionCommand(slashcommand.getStringField("name"), server);
	parseSlashCommand(slashcommand, slashCommand);
	return 1;
}

int CommandConfigManager::addForceResistBleedingCommand(lua_State* L) {
	LuaObject slashcommand(L);
	if (!slashcommand.isValidTable())
		return 0;

	ForceResistBleedingCommand* slashCommand = new ForceResistBleedingCommand(slashcommand.getStringField("name"), server);
	parseSlashCommand(slashcommand, slashCommand);
	return 1;
}

int CommandConfigManager::addForceResistDiseaseCommand(lua_State* L) {
	LuaObject slashcommand(L);
	if (!slashcommand.isValidTable())
		return 0;

	ForceResistDiseaseCommand* slashCommand = new ForceResistDiseaseCommand(slashcommand.getStringField("name"), server);
	parseSlashCommand(slashcommand, slashCommand);
	return 1;
}

int CommandConfigManager::addForceResistPoisonCommand(lua_State* L) {
	LuaObject slashcommand(L);
	if (!slashcommand.isValidTable())
		return 0;

	ForceResistPoisonCommand* slashCommand = new ForceResistPoisonCommand(slashcommand.getStringField("name"), server);
	parseSlashCommand(slashcommand, slashCommand);
	return 1;
}

int CommandConfigManager::addForceResistStatesCommand(lua_State* L) {
	LuaObject slashcommand(L);
	if (!slashcommand.isValidTable())
		return 0;

	ForceResistStatesCommand* slashCommand = new ForceResistStatesCommand(slashcommand.getStringField("name"), server);
	parseSlashCommand(slashcommand, slashCommand);
	return 1;
}

int CommandConfigManager::addForceRun1Command(lua_State* L) {
	LuaObject slashcommand(L);
	if (!slashcommand.isValidTable())
		return 0;

	ForceRun1Command* slashCommand = new ForceRun1Command(slashcommand.getStringField("name"), server);
	parseSlashCommand(slashcommand, slashCommand);
	return 1;
}

int CommandConfigManager::addForceRun2Command(lua_State* L) {
	LuaObject slashcommand(L);
	if (!slashcommand.isValidTable())
		return 0;

	ForceRun2Command* slashCommand = new ForceRun2Command(slashcommand.getStringField("name"), server);
	parseSlashCommand(slashcommand, slashCommand);
	return 1;
}

int CommandConfigManager::addForceRun3Command(lua_State* L) {
	LuaObject slashcommand(L);
	if (!slashcommand.isValidTable())
		return 0;

	ForceRun3Command* slashCommand = new ForceRun3Command(slashcommand.getStringField("name"), server);
	parseSlashCommand(slashcommand, slashCommand);
	return 1;
}

int CommandConfigManager::addForceShield1Command(lua_State* L) {
	LuaObject slashcommand(L);
	if (!slashcommand.isValidTable())
		return 0;

	ForceShield1Command* slashCommand = new ForceShield1Command(slashcommand.getStringField("name"), server);
	parseSlashCommand(slashcommand, slashCommand);
	return 1;
}

int CommandConfigManager::addForceShield2Command(lua_State* L) {
	LuaObject slashcommand(L);
	if (!slashcommand.isValidTable())
		return 0;

	ForceShield2Command* slashCommand = new ForceShield2Command(slashcommand.getStringField("name"), server);
	parseSlashCommand(slashcommand, slashCommand);
	return 1;
}

int CommandConfigManager::addForceSpeed1Command(lua_State* L) {
	LuaObject slashcommand(L);
	if (!slashcommand.isValidTable())
		return 0;

	ForceSpeed1Command* slashCommand = new ForceSpeed1Command(slashcommand.getStringField("name"), server);
	parseSlashCommand(slashcommand, slashCommand);
	return 1;
}

int CommandConfigManager::addForceSpeed2Command(lua_State* L) {
	LuaObject slashcommand(L);
	if (!slashcommand.isValidTable())
		return 0;

	ForceSpeed2Command* slashCommand = new ForceSpeed2Command(slashcommand.getStringField("name"), server);
	parseSlashCommand(slashcommand, slashCommand);
	return 1;
}

int CommandConfigManager::addForceThrow1Command(lua_State* L) {
	LuaObject slashcommand(L);
	if (!slashcommand.isValidTable())
		return 0;

	ForceThrow1Command* slashCommand = new ForceThrow1Command(slashcommand.getStringField("name"), server);
	parseSlashCommand(slashcommand, slashCommand);
	return 1;
}

int CommandConfigManager::addForceThrow2Command(lua_State* L) {
	LuaObject slashcommand(L);
	if (!slashcommand.isValidTable())
		return 0;

	ForceThrow2Command* slashCommand = new ForceThrow2Command(slashcommand.getStringField("name"), server);
	parseSlashCommand(slashcommand, slashCommand);
	return 1;
}

int CommandConfigManager::addForceWeaken1Command(lua_State* L) {
	LuaObject slashcommand(L);
	if (!slashcommand.isValidTable())
		return 0;

	ForceWeaken1Command* slashCommand = new ForceWeaken1Command(slashcommand.getStringField("name"), server);
	parseSlashCommand(slashcommand, slashCommand);
	return 1;
}

int CommandConfigManager::addForceWeaken2Command(lua_State* L) {
	LuaObject slashcommand(L);
	if (!slashcommand.isValidTable())
		return 0;

	ForceWeaken2Command* slashCommand = new ForceWeaken2Command(slashcommand.getStringField("name"), server);
	parseSlashCommand(slashcommand, slashCommand);
	return 1;
}

int CommandConfigManager::addFormupCommand(lua_State* L) {
	LuaObject slashcommand(L);
	if (!slashcommand.isValidTable())
		return 0;

	FormupCommand* slashCommand = new FormupCommand(slashcommand.getStringField("name"), server);
	parseSlashCommand(slashcommand, slashCommand);
	return 1;
}

int CommandConfigManager::addFreezePlayerCommand(lua_State* L) {
	LuaObject slashcommand(L);
	if (!slashcommand.isValidTable())
		return 0;

	FreezePlayerCommand* slashCommand = new FreezePlayerCommand(slashcommand.getStringField("name"), server);
	parseSlashCommand(slashcommand, slashCommand);
	return 1;
}

int CommandConfigManager::addFullAutoArea1Command(lua_State* L) {
	LuaObject slashcommand(L);
	if (!slashcommand.isValidTable())
		return 0;

	FullAutoArea1Command* slashCommand = new FullAutoArea1Command(slashcommand.getStringField("name"), server);
	parseSlashCommand(slashcommand, slashCommand);
	return 1;
}

int CommandConfigManager::addFullAutoArea2Command(lua_State* L) {
	LuaObject slashcommand(L);
	if (!slashcommand.isValidTable())
		return 0;

	FullAutoArea2Command* slashCommand = new FullAutoArea2Command(slashcommand.getStringField("name"), server);
	parseSlashCommand(slashcommand, slashCommand);
	return 1;
}

int CommandConfigManager::addFullAutoSingle1Command(lua_State* L) {
	LuaObject slashcommand(L);
	if (!slashcommand.isValidTable())
		return 0;

	FullAutoSingle1Command* slashCommand = new FullAutoSingle1Command(slashcommand.getStringField("name"), server);
	parseSlashCommand(slashcommand, slashCommand);
	return 1;
}

int CommandConfigManager::addFullAutoSingle2Command(lua_State* L) {
	LuaObject slashcommand(L);
	if (!slashcommand.isValidTable())
		return 0;

	FullAutoSingle2Command* slashCommand = new FullAutoSingle2Command(slashcommand.getStringField("name"), server);
	parseSlashCommand(slashcommand, slashCommand);
	return 1;
}

int CommandConfigManager::addGCommand(lua_State* L) {
	LuaObject slashcommand(L);
	if (!slashcommand.isValidTable())
		return 0;

	GCommand* slashCommand = new GCommand(slashcommand.getStringField("name"), server);
	parseSlashCommand(slashcommand, slashCommand);
	return 1;
}

int CommandConfigManager::addGallopCommand(lua_State* L) {
	LuaObject slashcommand(L);
	if (!slashcommand.isValidTable())
		return 0;

	GallopCommand* slashCommand = new GallopCommand(slashcommand.getStringField("name"), server);
	parseSlashCommand(slashcommand, slashCommand);
	return 1;
}

int CommandConfigManager::addGallopStopCommand(lua_State* L) {
	LuaObject slashcommand(L);
	if (!slashcommand.isValidTable())
		return 0;

	GallopStopCommand* slashCommand = new GallopStopCommand(slashcommand.getStringField("name"), server);
	parseSlashCommand(slashcommand, slashCommand);
	return 1;
}

int CommandConfigManager::addGcCommand(lua_State* L) {
	LuaObject slashcommand(L);
	if (!slashcommand.isValidTable())
		return 0;

	GcCommand* slashCommand = new GcCommand(slashcommand.getStringField("name"), server);
	parseSlashCommand(slashcommand, slashCommand);
	return 1;
}

int CommandConfigManager::addGcwStatusCommand(lua_State* L) {
	LuaObject slashcommand(L);
	if (!slashcommand.isValidTable())
		return 0;

	GcwStatusCommand* slashCommand = new GcwStatusCommand(slashcommand.getStringField("name"), server);
	parseSlashCommand(slashcommand, slashCommand);
	return 1;
}

int CommandConfigManager::addGenerateCraftedItemCommand(lua_State* L) {
	LuaObject slashcommand(L);
	if (!slashcommand.isValidTable())
		return 0;

	GenerateCraftedItemCommand* slashCommand = new GenerateCraftedItemCommand(slashcommand.getStringField("name"), server);
	parseSlashCommand(slashcommand, slashCommand);
	return 1;
}

int CommandConfigManager::addGetAccountInfoCommand(lua_State* L) {
	LuaObject slashcommand(L);
	if (!slashcommand.isValidTable())
		return 0;

	GetAccountInfoCommand* slashCommand = new GetAccountInfoCommand(slashcommand.getStringField("name"), server);
	parseSlashCommand(slashcommand, slashCommand);
	return 1;
}

int CommandConfigManager::addGetAttributesCommand(lua_State* L) {
	LuaObject slashcommand(L);
	if (!slashcommand.isValidTable())
		return 0;

	GetAttributesCommand* slashCommand = new GetAttributesCommand(slashcommand.getStringField("name"), server);
	parseSlashCommand(slashcommand, slashCommand);
	return 1;
}

int CommandConfigManager::addGetAttributesBatchCommand(lua_State* L) {
	LuaObject slashcommand(L);
	if (!slashcommand.isValidTable())
		return 0;

	GetAttributesBatchCommand* slashCommand = new GetAttributesBatchCommand(slashcommand.getStringField("name"), server);
	parseSlashCommand(slashcommand, slashCommand);
	return 1;
}

int CommandConfigManager::addGetFriendListCommand(lua_State* L) {
	LuaObject slashcommand(L);
	if (!slashcommand.isValidTable())
		return 0;

	GetFriendListCommand* slashCommand = new GetFriendListCommand(slashcommand.getStringField("name"), server);
	parseSlashCommand(slashcommand, slashCommand);
	return 1;
}

int CommandConfigManager::addGetGameTimeCommand(lua_State* L) {
	LuaObject slashcommand(L);
	if (!slashcommand.isValidTable())
		return 0;

	GetGameTimeCommand* slashCommand = new GetGameTimeCommand(slashcommand.getStringField("name"), server);
	parseSlashCommand(slashcommand, slashCommand);
	return 1;
}

int CommandConfigManager::addGetIgnoreListCommand(lua_State* L) {
	LuaObject slashcommand(L);
	if (!slashcommand.isValidTable())
		return 0;

	GetIgnoreListCommand* slashCommand = new GetIgnoreListCommand(slashcommand.getStringField("name"), server);
	parseSlashCommand(slashcommand, slashCommand);
	return 1;
}

int CommandConfigManager::addGetMapLocationsCommand(lua_State* L) {
	LuaObject slashcommand(L);
	if (!slashcommand.isValidTable())
		return 0;

	GetMapLocationsCommand* slashCommand = new GetMapLocationsCommand(slashcommand.getStringField("name"), server);
	parseSlashCommand(slashcommand, slashCommand);
	return 1;
}

int CommandConfigManager::addGetObjVarsCommand(lua_State* L) {
	LuaObject slashcommand(L);
	if (!slashcommand.isValidTable())
		return 0;

	GetObjVarsCommand* slashCommand = new GetObjVarsCommand(slashcommand.getStringField("name"), server);
	parseSlashCommand(slashcommand, slashCommand);
	return 1;
}

int CommandConfigManager::addGetPlayerIdCommand(lua_State* L) {
	LuaObject slashcommand(L);
	if (!slashcommand.isValidTable())
		return 0;

	GetPlayerIdCommand* slashCommand = new GetPlayerIdCommand(slashcommand.getStringField("name"), server);
	parseSlashCommand(slashcommand, slashCommand);
	return 1;
}

int CommandConfigManager::addGetPrototypeCommand(lua_State* L) {
	LuaObject slashcommand(L);
	if (!slashcommand.isValidTable())
		return 0;

	GetPrototypeCommand* slashCommand = new GetPrototypeCommand(slashcommand.getStringField("name"), server);
	parseSlashCommand(slashcommand, slashCommand);
	return 1;
}

int CommandConfigManager::addGetRankCommand(lua_State* L) {
	LuaObject slashcommand(L);
	if (!slashcommand.isValidTable())
		return 0;

	GetRankCommand* slashCommand = new GetRankCommand(slashcommand.getStringField("name"), server);
	parseSlashCommand(slashcommand, slashCommand);
	return 1;
}

int CommandConfigManager::addGetSpawnDelaysCommand(lua_State* L) {
	LuaObject slashcommand(L);
	if (!slashcommand.isValidTable())
		return 0;

	GetSpawnDelaysCommand* slashCommand = new GetSpawnDelaysCommand(slashcommand.getStringField("name"), server);
	parseSlashCommand(slashcommand, slashCommand);
	return 1;
}

int CommandConfigManager::addGetStationNameCommand(lua_State* L) {
	LuaObject slashcommand(L);
	if (!slashcommand.isValidTable())
		return 0;

	GetStationNameCommand* slashCommand = new GetStationNameCommand(slashcommand.getStringField("name"), server);
	parseSlashCommand(slashcommand, slashCommand);
	return 1;
}

int CommandConfigManager::addGetVeteranRewardTimeCommand(lua_State* L) {
	LuaObject slashcommand(L);
	if (!slashcommand.isValidTable())
		return 0;

	GetVeteranRewardTimeCommand* slashCommand = new GetVeteranRewardTimeCommand(slashcommand.getStringField("name"), server);
	parseSlashCommand(slashcommand, slashCommand);
	return 1;
}

int CommandConfigManager::addGetVeteranRewardTimeCsCommand(lua_State* L) {
	LuaObject slashcommand(L);
	if (!slashcommand.isValidTable())
		return 0;

	GetVeteranRewardTimeCsCommand* slashCommand = new GetVeteranRewardTimeCsCommand(slashcommand.getStringField("name"), server);
	parseSlashCommand(slashcommand, slashCommand);
	return 1;
}

int CommandConfigManager::addGiveItemCommand(lua_State* L) {
	LuaObject slashcommand(L);
	if (!slashcommand.isValidTable())
		return 0;

	GiveItemCommand* slashCommand = new GiveItemCommand(slashcommand.getStringField("name"), server);
	parseSlashCommand(slashcommand, slashCommand);
	return 1;
}

int CommandConfigManager::addGiveMaintenanceToVendorCommand(lua_State* L) {
	LuaObject slashcommand(L);
	if (!slashcommand.isValidTable())
		return 0;

	GiveMaintenanceToVendorCommand* slashCommand = new GiveMaintenanceToVendorCommand(slashcommand.getStringField("name"), server);
	parseSlashCommand(slashcommand, slashCommand);
	return 1;
}

int CommandConfigManager::addGivevendormaintCommand(lua_State* L) {
	LuaObject slashcommand(L);
	if (!slashcommand.isValidTable())
		return 0;

	GivevendormaintCommand* slashCommand = new GivevendormaintCommand(slashcommand.getStringField("name"), server);
	parseSlashCommand(slashcommand, slashCommand);
	return 1;
}

int CommandConfigManager::addGmForceCommandCommand(lua_State* L) {
	LuaObject slashcommand(L);
	if (!slashcommand.isValidTable())
		return 0;

	GmForceCommandCommand* slashCommand = new GmForceCommandCommand(slashcommand.getStringField("name"), server);
	parseSlashCommand(slashcommand, slashCommand);
	return 1;
}

int CommandConfigManager::addGmCreateClassResourceCommand(lua_State* L) {
	LuaObject slashcommand(L);
	if (!slashcommand.isValidTable())
		return 0;

	GmCreateClassResourceCommand* slashCommand = new GmCreateClassResourceCommand(slashcommand.getStringField("name"), server);
	parseSlashCommand(slashcommand, slashCommand);
	return 1;
}

int CommandConfigManager::addGmCreateSpecificResourceCommand(lua_State* L) {
	LuaObject slashcommand(L);
	if (!slashcommand.isValidTable())
		return 0;

	GmCreateSpecificResourceCommand* slashCommand = new GmCreateSpecificResourceCommand(slashcommand.getStringField("name"), server);
	parseSlashCommand(slashcommand, slashCommand);
	return 1;
}

int CommandConfigManager::addGmForceRankCommand(lua_State* L) {
	LuaObject slashcommand(L);
	if (!slashcommand.isValidTable())
		return 0;

	GmForceRankCommand* slashCommand = new GmForceRankCommand(slashcommand.getStringField("name"), server);
	parseSlashCommand(slashcommand, slashCommand);
	return 1;
}

int CommandConfigManager::addGmFsVillageCommand(lua_State* L) {
	LuaObject slashcommand(L);
	if (!slashcommand.isValidTable())
		return 0;

	GmFsVillageCommand* slashCommand = new GmFsVillageCommand(slashcommand.getStringField("name"), server);
	parseSlashCommand(slashcommand, slashCommand);
	return 1;
}

int CommandConfigManager::addGmJediStateCommand(lua_State* L) {
	LuaObject slashcommand(L);
	if (!slashcommand.isValidTable())
		return 0;

	GmJediStateCommand* slashCommand = new GmJediStateCommand(slashcommand.getStringField("name"), server);
	parseSlashCommand(slashcommand, slashCommand);
	return 1;
}

int CommandConfigManager::addGmReviveCommand(lua_State* L) {
	LuaObject slashcommand(L);
	if (!slashcommand.isValidTable())
		return 0;

	GmReviveCommand* slashCommand = new GmReviveCommand(slashcommand.getStringField("name"), server);
	parseSlashCommand(slashcommand, slashCommand);
	return 1;
}

int CommandConfigManager::addGotoCommand(lua_State* L) {
	LuaObject slashcommand(L);
	if (!slashcommand.isValidTable())
		return 0;

	GotoCommand* slashCommand = new GotoCommand(slashcommand.getStringField("name"), server);
	parseSlashCommand(slashcommand, slashCommand);
	return 1;
}

int CommandConfigManager::addGrantBadgeCommand(lua_State* L) {
	LuaObject slashcommand(L);
	if (!slashcommand.isValidTable())
		return 0;

	GrantBadgeCommand* slashCommand = new GrantBadgeCommand(slashcommand.getStringField("name"), server);
	parseSlashCommand(slashcommand, slashCommand);
	return 1;
}

int CommandConfigManager::addGrantPadawanTrialsEligibilityCommand(lua_State* L) {
	LuaObject slashcommand(L);
	if (!slashcommand.isValidTable())
		return 0;

	GrantPadawanTrialsEligibilityCommand* slashCommand = new GrantPadawanTrialsEligibilityCommand(slashcommand.getStringField("name"), server);
	parseSlashCommand(slashcommand, slashCommand);
	return 1;
}

int CommandConfigManager::addGrantSkillCommand(lua_State* L) {
	LuaObject slashcommand(L);
	if (!slashcommand.isValidTable())
		return 0;

	GrantSkillCommand* slashCommand = new GrantSkillCommand(slashcommand.getStringField("name"), server);
	parseSlashCommand(slashcommand, slashCommand);
	return 1;
}

int CommandConfigManager::addGrantTitleCommand(lua_State* L) {
	LuaObject slashcommand(L);
	if (!slashcommand.isValidTable())
		return 0;

	GrantTitleCommand* slashCommand = new GrantTitleCommand(slashcommand.getStringField("name"), server);
	parseSlashCommand(slashcommand, slashCommand);
	return 1;
}

int CommandConfigManager::addGrantZoningRightsCommand(lua_State* L) {
	LuaObject slashcommand(L);
	if (!slashcommand.isValidTable())
		return 0;

	GrantZoningRightsCommand* slashCommand = new GrantZoningRightsCommand(slashcommand.getStringField("name"), server);
	parseSlashCommand(slashcommand, slashCommand);
	return 1;
}

int CommandConfigManager::addGroupChatCommand(lua_State* L) {
	LuaObject slashcommand(L);
	if (!slashcommand.isValidTable())
		return 0;

	GroupChatCommand* slashCommand = new GroupChatCommand(slashcommand.getStringField("name"), server);
	parseSlashCommand(slashcommand, slashCommand);
	return 1;
}

int CommandConfigManager::addGroupSayCommand(lua_State* L) {
	LuaObject slashcommand(L);
	if (!slashcommand.isValidTable())
		return 0;

	GroupSayCommand* slashCommand = new GroupSayCommand(slashcommand.getStringField("name"), server);
	parseSlashCommand(slashcommand, slashCommand);
	return 1;
}

int CommandConfigManager::addGsayCommand(lua_State* L) {
	LuaObject slashcommand(L);
	if (!slashcommand.isValidTable())
		return 0;

	GsayCommand* slashCommand = new GsayCommand(slashcommand.getStringField("name"), server);
	parseSlashCommand(slashcommand, slashCommand);
	return 1;
}

int CommandConfigManager::addGtellCommand(lua_State* L) {
	LuaObject slashcommand(L);
	if (!slashcommand.isValidTable())
		return 0;

	GtellCommand* slashCommand = new GtellCommand(slashcommand.getStringField("name"), server);
	parseSlashCommand(slashcommand, slashCommand);
	return 1;
}

int CommandConfigManager::addGuildCommand(lua_State* L) {
	LuaObject slashcommand(L);
	if (!slashcommand.isValidTable())
		return 0;

	GuildCommand* slashCommand = new GuildCommand(slashcommand.getStringField("name"), server);
	parseSlashCommand(slashcommand, slashCommand);
	return 1;
}

int CommandConfigManager::addGuildremoveCommand(lua_State* L) {
	LuaObject slashcommand(L);
	if (!slashcommand.isValidTable())
		return 0;

	GuildremoveCommand* slashCommand = new GuildremoveCommand(slashcommand.getStringField("name"), server);
	parseSlashCommand(slashcommand, slashCommand);
	return 1;
}

int CommandConfigManager::addGuildsayCommand(lua_State* L) {
	LuaObject slashcommand(L);
	if (!slashcommand.isValidTable())
		return 0;

	GuildsayCommand* slashCommand = new GuildsayCommand(slashcommand.getStringField("name"), server);
	parseSlashCommand(slashcommand, slashCommand);
	return 1;
}

int CommandConfigManager::addGuildstatusCommand(lua_State* L) {
	LuaObject slashcommand(L);
	if (!slashcommand.isValidTable())
		return 0;

	GuildstatusCommand* slashCommand = new GuildstatusCommand(slashcommand.getStringField("name"), server);
	parseSlashCommand(slashcommand, slashCommand);
	return 1;
}

int CommandConfigManager::addHarmfulCommand(lua_State* L) {
	LuaObject slashcommand(L);
	if (!slashcommand.isValidTable())
		return 0;

	HarmfulCommand* slashCommand = new HarmfulCommand(slashcommand.getStringField("name"), server);
	parseSlashCommand(slashcommand, slashCommand);
	return 1;
}

int CommandConfigManager::addHarmlessCommand(lua_State* L) {
	LuaObject slashcommand(L);
	if (!slashcommand.isValidTable())
		return 0;

	HarmlessCommand* slashCommand = new HarmlessCommand(slashcommand.getStringField("name"), server);
	parseSlashCommand(slashcommand, slashCommand);
	return 1;
}

int CommandConfigManager::addHarvestCorpseCommand(lua_State* L) {
	LuaObject slashcommand(L);
	if (!slashcommand.isValidTable())
		return 0;

	HarvestCorpseCommand* slashCommand = new HarvestCorpseCommand(slashcommand.getStringField("name"), server);
	parseSlashCommand(slashcommand, slashCommand);
	return 1;
}

int CommandConfigManager::addHarvesterActivateCommand(lua_State* L) {
	LuaObject slashcommand(L);
	if (!slashcommand.isValidTable())
		return 0;

	HarvesterActivateCommand* slashCommand = new HarvesterActivateCommand(slashcommand.getStringField("name"), server);
	parseSlashCommand(slashcommand, slashCommand);
	return 1;
}

int CommandConfigManager::addHarvesterDeactivateCommand(lua_State* L) {
	LuaObject slashcommand(L);
	if (!slashcommand.isValidTable())
		return 0;

	HarvesterDeactivateCommand* slashCommand = new HarvesterDeactivateCommand(slashcommand.getStringField("name"), server);
	parseSlashCommand(slashcommand, slashCommand);
	return 1;
}

int CommandConfigManager::addHarvesterDiscardHopperCommand(lua_State* L) {
	LuaObject slashcommand(L);
	if (!slashcommand.isValidTable())
		return 0;

	HarvesterDiscardHopperCommand* slashCommand = new HarvesterDiscardHopperCommand(slashcommand.getStringField("name"), server);
	parseSlashCommand(slashcommand, slashCommand);
	return 1;
}

int CommandConfigManager::addHarvesterGetResourceDataCommand(lua_State* L) {
	LuaObject slashcommand(L);
	if (!slashcommand.isValidTable())
		return 0;

	HarvesterGetResourceDataCommand* slashCommand = new HarvesterGetResourceDataCommand(slashcommand.getStringField("name"), server);
	parseSlashCommand(slashcommand, slashCommand);
	return 1;
}

int CommandConfigManager::addHarvesterHarvestCommand(lua_State* L) {
	LuaObject slashcommand(L);
	if (!slashcommand.isValidTable())
		return 0;

	HarvesterHarvestCommand* slashCommand = new HarvesterHarvestCommand(slashcommand.getStringField("name"), server);
	parseSlashCommand(slashcommand, slashCommand);
	return 1;
}

int CommandConfigManager::addHarvesterMakeCrateCommand(lua_State* L) {
	LuaObject slashcommand(L);
	if (!slashcommand.isValidTable())
		return 0;

	HarvesterMakeCrateCommand* slashCommand = new HarvesterMakeCrateCommand(slashcommand.getStringField("name"), server);
	parseSlashCommand(slashcommand, slashCommand);
	return 1;
}

int CommandConfigManager::addHarvesterSelectResourceCommand(lua_State* L) {
	LuaObject slashcommand(L);
	if (!slashcommand.isValidTable())
		return 0;

	HarvesterSelectResourceCommand* slashCommand = new HarvesterSelectResourceCommand(slashcommand.getStringField("name"), server);
	parseSlashCommand(slashcommand, slashCommand);
	return 1;
}

int CommandConfigManager::addHarvesterTakeSurveyCommand(lua_State* L) {
	LuaObject slashcommand(L);
	if (!slashcommand.isValidTable())
		return 0;

	HarvesterTakeSurveyCommand* slashCommand = new HarvesterTakeSurveyCommand(slashcommand.getStringField("name"), server);
	parseSlashCommand(slashcommand, slashCommand);
	return 1;
}

int CommandConfigManager::addHasVeteranRewardCommand(lua_State* L) {
	LuaObject slashcommand(L);
	if (!slashcommand.isValidTable())
		return 0;

	HasVeteranRewardCommand* slashCommand = new HasVeteranRewardCommand(slashcommand.getStringField("name"), server);
	parseSlashCommand(slashcommand, slashCommand);
	return 1;
}

int CommandConfigManager::addHaveconsentCommand(lua_State* L) {
	LuaObject slashcommand(L);
	if (!slashcommand.isValidTable())
		return 0;

	HaveconsentCommand* slashCommand = new HaveconsentCommand(slashcommand.getStringField("name"), server);
	parseSlashCommand(slashcommand, slashCommand);
	return 1;
}

int CommandConfigManager::addHeadShot1Command(lua_State* L) {
	LuaObject slashcommand(L);
	if (!slashcommand.isValidTable())
		return 0;

	HeadShot1Command* slashCommand = new HeadShot1Command(slashcommand.getStringField("name"), server);
	parseSlashCommand(slashcommand, slashCommand);
	return 1;
}

int CommandConfigManager::addHeadShot2Command(lua_State* L) {
	LuaObject slashcommand(L);
	if (!slashcommand.isValidTable())
		return 0;

	HeadShot2Command* slashCommand = new HeadShot2Command(slashcommand.getStringField("name"), server);
	parseSlashCommand(slashcommand, slashCommand);
	return 1;
}

int CommandConfigManager::addHeadShot3Command(lua_State* L) {
	LuaObject slashcommand(L);
	if (!slashcommand.isValidTable())
		return 0;

	HeadShot3Command* slashCommand = new HeadShot3Command(slashcommand.getStringField("name"), server);
	parseSlashCommand(slashcommand, slashCommand);
	return 1;
}

int CommandConfigManager::addHealActionSelf1Command(lua_State* L) {
	LuaObject slashcommand(L);
	if (!slashcommand.isValidTable())
		return 0;

	HealActionSelf1Command* slashCommand = new HealActionSelf1Command(slashcommand.getStringField("name"), server);
	parseSlashCommand(slashcommand, slashCommand);
	return 1;
}

int CommandConfigManager::addHealActionSelf2Command(lua_State* L) {
	LuaObject slashcommand(L);
	if (!slashcommand.isValidTable())
		return 0;

	HealActionSelf2Command* slashCommand = new HealActionSelf2Command(slashcommand.getStringField("name"), server);
	parseSlashCommand(slashcommand, slashCommand);
	return 1;
}

int CommandConfigManager::addHealActionWoundOther1Command(lua_State* L) {
	LuaObject slashcommand(L);
	if (!slashcommand.isValidTable())
		return 0;

	HealActionWoundOther1Command* slashCommand = new HealActionWoundOther1Command(slashcommand.getStringField("name"), server);
	parseSlashCommand(slashcommand, slashCommand);
	return 1;
}

int CommandConfigManager::addHealActionWoundOther2Command(lua_State* L) {
	LuaObject slashcommand(L);
	if (!slashcommand.isValidTable())
		return 0;

	HealActionWoundOther2Command* slashCommand = new HealActionWoundOther2Command(slashcommand.getStringField("name"), server);
	parseSlashCommand(slashcommand, slashCommand);
	return 1;
}

int CommandConfigManager::addHealActionWoundSelf1Command(lua_State* L) {
	LuaObject slashcommand(L);
	if (!slashcommand.isValidTable())
		return 0;

	HealActionWoundSelf1Command* slashCommand = new HealActionWoundSelf1Command(slashcommand.getStringField("name"), server);
	parseSlashCommand(slashcommand, slashCommand);
	return 1;
}

int CommandConfigManager::addHealActionWoundSelf2Command(lua_State* L) {
	LuaObject slashcommand(L);
	if (!slashcommand.isValidTable())
		return 0;

	HealActionWoundSelf2Command* slashCommand = new HealActionWoundSelf2Command(slashcommand.getStringField("name"), server);
	parseSlashCommand(slashcommand, slashCommand);
	return 1;
}

int CommandConfigManager::addHealAllOther1Command(lua_State* L) {
	LuaObject slashcommand(L);
	if (!slashcommand.isValidTable())
		return 0;

	HealAllOther1Command* slashCommand = new HealAllOther1Command(slashcommand.getStringField("name"), server);
	parseSlashCommand(slashcommand, slashCommand);
	return 1;
}

int CommandConfigManager::addHealAllOther2Command(lua_State* L) {
	LuaObject slashcommand(L);
	if (!slashcommand.isValidTable())
		return 0;

	HealAllOther2Command* slashCommand = new HealAllOther2Command(slashcommand.getStringField("name"), server);
	parseSlashCommand(slashcommand, slashCommand);
	return 1;
}

int CommandConfigManager::addHealAllSelf1Command(lua_State* L) {
	LuaObject slashcommand(L);
	if (!slashcommand.isValidTable())
		return 0;

	HealAllSelf1Command* slashCommand = new HealAllSelf1Command(slashcommand.getStringField("name"), server);
	parseSlashCommand(slashcommand, slashCommand);
	return 1;
}

int CommandConfigManager::addHealAllSelf2Command(lua_State* L) {
	LuaObject slashcommand(L);
	if (!slashcommand.isValidTable())
		return 0;

	HealAllSelf2Command* slashCommand = new HealAllSelf2Command(slashcommand.getStringField("name"), server);
	parseSlashCommand(slashcommand, slashCommand);
	return 1;
}

int CommandConfigManager::addHealBattleFatigueOther1Command(lua_State* L) {
	LuaObject slashcommand(L);
	if (!slashcommand.isValidTable())
		return 0;

	HealBattleFatigueOther1Command* slashCommand = new HealBattleFatigueOther1Command(slashcommand.getStringField("name"), server);
	parseSlashCommand(slashcommand, slashCommand);
	return 1;
}

int CommandConfigManager::addHealBattleFatigueOther2Command(lua_State* L) {
	LuaObject slashcommand(L);
	if (!slashcommand.isValidTable())
		return 0;

	HealBattleFatigueOther2Command* slashCommand = new HealBattleFatigueOther2Command(slashcommand.getStringField("name"), server);
	parseSlashCommand(slashcommand, slashCommand);
	return 1;
}

int CommandConfigManager::addHealBattleFatigueSelf1Command(lua_State* L) {
	LuaObject slashcommand(L);
	if (!slashcommand.isValidTable())
		return 0;

	HealBattleFatigueSelf1Command* slashCommand = new HealBattleFatigueSelf1Command(slashcommand.getStringField("name"), server);
	parseSlashCommand(slashcommand, slashCommand);
	return 1;
}

int CommandConfigManager::addHealBattleFatigueSelf2Command(lua_State* L) {
	LuaObject slashcommand(L);
	if (!slashcommand.isValidTable())
		return 0;

	HealBattleFatigueSelf2Command* slashCommand = new HealBattleFatigueSelf2Command(slashcommand.getStringField("name"), server);
	parseSlashCommand(slashcommand, slashCommand);
	return 1;
}

int CommandConfigManager::addHealDamageCommand(lua_State* L) {
	LuaObject slashcommand(L);
	if (!slashcommand.isValidTable())
		return 0;

	HealDamageCommand* slashCommand = new HealDamageCommand(slashcommand.getStringField("name"), server);
	parseSlashCommand(slashcommand, slashCommand);
	return 1;
}

int CommandConfigManager::addHealDroidDamageCommand(lua_State* L) {
	LuaObject slashcommand(L);
	if (!slashcommand.isValidTable())
		return 0;

	HealDroidDamageCommand* slashCommand = new HealDroidDamageCommand(slashcommand.getStringField("name"), server);
	parseSlashCommand(slashcommand, slashCommand);
	return 1;
}

int CommandConfigManager::addHealDroidWoundCommand(lua_State* L) {
	LuaObject slashcommand(L);
	if (!slashcommand.isValidTable())
		return 0;

	HealDroidWoundCommand* slashCommand = new HealDroidWoundCommand(slashcommand.getStringField("name"), server);
	parseSlashCommand(slashcommand, slashCommand);
	return 1;
}

int CommandConfigManager::addHealEnhanceCommand(lua_State* L) {
	LuaObject slashcommand(L);
	if (!slashcommand.isValidTable())
		return 0;

	HealEnhanceCommand* slashCommand = new HealEnhanceCommand(slashcommand.getStringField("name"), server);
	parseSlashCommand(slashcommand, slashCommand);
	return 1;
}

int CommandConfigManager::addHealHealthSelf1Command(lua_State* L) {
	LuaObject slashcommand(L);
	if (!slashcommand.isValidTable())
		return 0;

	HealHealthSelf1Command* slashCommand = new HealHealthSelf1Command(slashcommand.getStringField("name"), server);
	parseSlashCommand(slashcommand, slashCommand);
	return 1;
}

int CommandConfigManager::addHealHealthSelf2Command(lua_State* L) {
	LuaObject slashcommand(L);
	if (!slashcommand.isValidTable())
		return 0;

	HealHealthSelf2Command* slashCommand = new HealHealthSelf2Command(slashcommand.getStringField("name"), server);
	parseSlashCommand(slashcommand, slashCommand);
	return 1;
}

int CommandConfigManager::addHealHealthWoundOther1Command(lua_State* L) {
	LuaObject slashcommand(L);
	if (!slashcommand.isValidTable())
		return 0;

	HealHealthWoundOther1Command* slashCommand = new HealHealthWoundOther1Command(slashcommand.getStringField("name"), server);
	parseSlashCommand(slashcommand, slashCommand);
	return 1;
}

int CommandConfigManager::addHealHealthWoundOther2Command(lua_State* L) {
	LuaObject slashcommand(L);
	if (!slashcommand.isValidTable())
		return 0;

	HealHealthWoundOther2Command* slashCommand = new HealHealthWoundOther2Command(slashcommand.getStringField("name"), server);
	parseSlashCommand(slashcommand, slashCommand);
	return 1;
}

int CommandConfigManager::addHealHealthWoundSelf1Command(lua_State* L) {
	LuaObject slashcommand(L);
	if (!slashcommand.isValidTable())
		return 0;

	HealHealthWoundSelf1Command* slashCommand = new HealHealthWoundSelf1Command(slashcommand.getStringField("name"), server);
	parseSlashCommand(slashcommand, slashCommand);
	return 1;
}

int CommandConfigManager::addHealHealthWoundSelf2Command(lua_State* L) {
	LuaObject slashcommand(L);
	if (!slashcommand.isValidTable())
		return 0;

	HealHealthWoundSelf2Command* slashCommand = new HealHealthWoundSelf2Command(slashcommand.getStringField("name"), server);
	parseSlashCommand(slashcommand, slashCommand);
	return 1;
}

int CommandConfigManager::addHealMindCommand(lua_State* L) {
	LuaObject slashcommand(L);
	if (!slashcommand.isValidTable())
		return 0;

	HealMindCommand* slashCommand = new HealMindCommand(slashcommand.getStringField("name"), server);
	parseSlashCommand(slashcommand, slashCommand);
	return 1;
}

int CommandConfigManager::addHealMindSelf1Command(lua_State* L) {
	LuaObject slashcommand(L);
	if (!slashcommand.isValidTable())
		return 0;

	HealMindSelf1Command* slashCommand = new HealMindSelf1Command(slashcommand.getStringField("name"), server);
	parseSlashCommand(slashcommand, slashCommand);
	return 1;
}

int CommandConfigManager::addHealMindSelf2Command(lua_State* L) {
	LuaObject slashcommand(L);
	if (!slashcommand.isValidTable())
		return 0;

	HealMindSelf2Command* slashCommand = new HealMindSelf2Command(slashcommand.getStringField("name"), server);
	parseSlashCommand(slashcommand, slashCommand);
	return 1;
}

int CommandConfigManager::addHealMindWoundOther1Command(lua_State* L) {
	LuaObject slashcommand(L);
	if (!slashcommand.isValidTable())
		return 0;

	HealMindWoundOther1Command* slashCommand = new HealMindWoundOther1Command(slashcommand.getStringField("name"), server);
	parseSlashCommand(slashcommand, slashCommand);
	return 1;
}

int CommandConfigManager::addHealMindWoundOther2Command(lua_State* L) {
	LuaObject slashcommand(L);
	if (!slashcommand.isValidTable())
		return 0;

	HealMindWoundOther2Command* slashCommand = new HealMindWoundOther2Command(slashcommand.getStringField("name"), server);
	parseSlashCommand(slashcommand, slashCommand);
	return 1;
}

int CommandConfigManager::addHealMindWoundSelf1Command(lua_State* L) {
	LuaObject slashcommand(L);
	if (!slashcommand.isValidTable())
		return 0;

	HealMindWoundSelf1Command* slashCommand = new HealMindWoundSelf1Command(slashcommand.getStringField("name"), server);
	parseSlashCommand(slashcommand, slashCommand);
	return 1;
}

int CommandConfigManager::addHealMindWoundSelf2Command(lua_State* L) {
	LuaObject slashcommand(L);
	if (!slashcommand.isValidTable())
		return 0;

	HealMindWoundSelf2Command* slashCommand = new HealMindWoundSelf2Command(slashcommand.getStringField("name"), server);
	parseSlashCommand(slashcommand, slashCommand);
	return 1;
}

int CommandConfigManager::addHealPetCommand(lua_State* L) {
	LuaObject slashcommand(L);
	if (!slashcommand.isValidTable())
		return 0;

	HealPetCommand* slashCommand = new HealPetCommand(slashcommand.getStringField("name"), server);
	parseSlashCommand(slashcommand, slashCommand);
	return 1;
}

int CommandConfigManager::addHealStateCommand(lua_State* L) {
	LuaObject slashcommand(L);
	if (!slashcommand.isValidTable())
		return 0;

	HealStateCommand* slashCommand = new HealStateCommand(slashcommand.getStringField("name"), server);
	parseSlashCommand(slashcommand, slashCommand);
	return 1;
}

int CommandConfigManager::addHealStatesOtherCommand(lua_State* L) {
	LuaObject slashcommand(L);
	if (!slashcommand.isValidTable())
		return 0;

	HealStatesOtherCommand* slashCommand = new HealStatesOtherCommand(slashcommand.getStringField("name"), server);
	parseSlashCommand(slashcommand, slashCommand);
	return 1;
}

int CommandConfigManager::addHealStatesSelfCommand(lua_State* L) {
	LuaObject slashcommand(L);
	if (!slashcommand.isValidTable())
		return 0;

	HealStatesSelfCommand* slashCommand = new HealStatesSelfCommand(slashcommand.getStringField("name"), server);
	parseSlashCommand(slashcommand, slashCommand);
	return 1;
}

int CommandConfigManager::addHealthShot1Command(lua_State* L) {
	LuaObject slashcommand(L);
	if (!slashcommand.isValidTable())
		return 0;

	HealthShot1Command* slashCommand = new HealthShot1Command(slashcommand.getStringField("name"), server);
	parseSlashCommand(slashcommand, slashCommand);
	return 1;
}

int CommandConfigManager::addHealthShot2Command(lua_State* L) {
	LuaObject slashcommand(L);
	if (!slashcommand.isValidTable())
		return 0;

	HealthShot2Command* slashCommand = new HealthShot2Command(slashcommand.getStringField("name"), server);
	parseSlashCommand(slashcommand, slashCommand);
	return 1;
}

int CommandConfigManager::addHealWoundCommand(lua_State* L) {
	LuaObject slashcommand(L);
	if (!slashcommand.isValidTable())
		return 0;

	HealWoundCommand* slashCommand = new HealWoundCommand(slashcommand.getStringField("name"), server);
	parseSlashCommand(slashcommand, slashCommand);
	return 1;
}

int CommandConfigManager::addHoloEmoteCommand(lua_State* L) {
	LuaObject slashcommand(L);
	if (!slashcommand.isValidTable())
		return 0;

	HoloEmoteCommand* slashCommand = new HoloEmoteCommand(slashcommand.getStringField("name"), server);
	parseSlashCommand(slashcommand, slashCommand);
	return 1;
}

int CommandConfigManager::addImagedesignCommand(lua_State* L) {
	LuaObject slashcommand(L);
	if (!slashcommand.isValidTable())
		return 0;

	ImagedesignCommand* slashCommand = new ImagedesignCommand(slashcommand.getStringField("name"), server);
	parseSlashCommand(slashcommand, slashCommand);
	return 1;
}

int CommandConfigManager::addInitializeComponentCommand(lua_State* L) {
	LuaObject slashcommand(L);
	if (!slashcommand.isValidTable())
		return 0;

	InitializeComponentCommand* slashCommand = new InitializeComponentCommand(slashcommand.getStringField("name"), server);
	parseSlashCommand(slashcommand, slashCommand);
	return 1;
}

int CommandConfigManager::addInnateCommand(lua_State* L) {
	LuaObject slashcommand(L);
	if (!slashcommand.isValidTable())
		return 0;

	InnateCommand* slashCommand = new InnateCommand(slashcommand.getStringField("name"), server);
	parseSlashCommand(slashcommand, slashCommand);
	return 1;
}

int CommandConfigManager::addInsertItemIntoShipComponentSlotCommand(lua_State* L) {
	LuaObject slashcommand(L);
	if (!slashcommand.isValidTable())
		return 0;

	InsertItemIntoShipComponentSlotCommand* slashCommand = new InsertItemIntoShipComponentSlotCommand(slashcommand.getStringField("name"), server);
	parseSlashCommand(slashcommand, slashCommand);
	return 1;
}

int CommandConfigManager::addInstallMissionTerminalCommand(lua_State* L) {
	LuaObject slashcommand(L);
	if (!slashcommand.isValidTable())
		return 0;

	InstallMissionTerminalCommand* slashCommand = new InstallMissionTerminalCommand(slashcommand.getStringField("name"), server);
	parseSlashCommand(slashcommand, slashCommand);
	return 1;
}

int CommandConfigManager::addInstallShipComponentCommand(lua_State* L) {
	LuaObject slashcommand(L);
	if (!slashcommand.isValidTable())
		return 0;

	InstallShipComponentCommand* slashCommand = new InstallShipComponentCommand(slashcommand.getStringField("name"), server);
	parseSlashCommand(slashcommand, slashCommand);
	return 1;
}

int CommandConfigManager::addInsureCommand(lua_State* L) {
	LuaObject slashcommand(L);
	if (!slashcommand.isValidTable())
		return 0;

	InsureCommand* slashCommand = new InsureCommand(slashcommand.getStringField("name"), server);
	parseSlashCommand(slashcommand, slashCommand);
	return 1;
}

int CommandConfigManager::addIntimidate1Command(lua_State* L) {
	LuaObject slashcommand(L);
	if (!slashcommand.isValidTable())
		return 0;

	Intimidate1Command* slashCommand = new Intimidate1Command(slashcommand.getStringField("name"), server);
	parseSlashCommand(slashcommand, slashCommand);
	return 1;
}

int CommandConfigManager::addIntimidate2Command(lua_State* L) {
	LuaObject slashcommand(L);
	if (!slashcommand.isValidTable())
		return 0;

	Intimidate2Command* slashCommand = new Intimidate2Command(slashcommand.getStringField("name"), server);
	parseSlashCommand(slashcommand, slashCommand);
	return 1;
}

int CommandConfigManager::addIntimidationAttackCommand(lua_State* L) {
	LuaObject slashcommand(L);
	if (!slashcommand.isValidTable())
		return 0;

	IntimidationAttackCommand* slashCommand = new IntimidationAttackCommand(slashcommand.getStringField("name"), server);
	parseSlashCommand(slashcommand, slashCommand);
	return 1;
}

int CommandConfigManager::addInviteCommand(lua_State* L) {
	LuaObject slashcommand(L);
	if (!slashcommand.isValidTable())
		return 0;

	InviteCommand* slashCommand = new InviteCommand(slashcommand.getStringField("name"), server);
	parseSlashCommand(slashcommand, slashCommand);
	return 1;
}

int CommandConfigManager::addInvulnerableCommand(lua_State* L) {
	LuaObject slashcommand(L);
	if (!slashcommand.isValidTable())
		return 0;

	InvulnerableCommand* slashCommand = new InvulnerableCommand(slashcommand.getStringField("name"), server);
	parseSlashCommand(slashcommand, slashCommand);
	return 1;
}

int CommandConfigManager::addItemmovebackCommand(lua_State* L) {
	LuaObject slashcommand(L);
	if (!slashcommand.isValidTable())
		return 0;

	ItemmovebackCommand* slashCommand = new ItemmovebackCommand(slashcommand.getStringField("name"), server);
	parseSlashCommand(slashcommand, slashCommand);
	return 1;
}

int CommandConfigManager::addItemmovedownCommand(lua_State* L) {
	LuaObject slashcommand(L);
	if (!slashcommand.isValidTable())
		return 0;

	ItemmovedownCommand* slashCommand = new ItemmovedownCommand(slashcommand.getStringField("name"), server);
	parseSlashCommand(slashcommand, slashCommand);
	return 1;
}

int CommandConfigManager::addItemmoveforwardCommand(lua_State* L) {
	LuaObject slashcommand(L);
	if (!slashcommand.isValidTable())
		return 0;

	ItemmoveforwardCommand* slashCommand = new ItemmoveforwardCommand(slashcommand.getStringField("name"), server);
	parseSlashCommand(slashcommand, slashCommand);
	return 1;
}

int CommandConfigManager::addItemmoveupCommand(lua_State* L) {
	LuaObject slashcommand(L);
	if (!slashcommand.isValidTable())
		return 0;

	ItemmoveupCommand* slashCommand = new ItemmoveupCommand(slashcommand.getStringField("name"), server);
	parseSlashCommand(slashcommand, slashCommand);
	return 1;
}

int CommandConfigManager::addItemrotateleftCommand(lua_State* L) {
	LuaObject slashcommand(L);
	if (!slashcommand.isValidTable())
		return 0;

	ItemrotateleftCommand* slashCommand = new ItemrotateleftCommand(slashcommand.getStringField("name"), server);
	parseSlashCommand(slashcommand, slashCommand);
	return 1;
}

int CommandConfigManager::addItemrotaterightCommand(lua_State* L) {
	LuaObject slashcommand(L);
	if (!slashcommand.isValidTable())
		return 0;

	ItemrotaterightCommand* slashCommand = new ItemrotaterightCommand(slashcommand.getStringField("name"), server);
	parseSlashCommand(slashcommand, slashCommand);
	return 1;
}

int CommandConfigManager::addJediMindTrickCommand(lua_State* L) {
	LuaObject slashcommand(L);
	if (!slashcommand.isValidTable())
		return 0;

	JediMindTrickCommand* slashCommand = new JediMindTrickCommand(slashcommand.getStringField("name"), server);
	parseSlashCommand(slashcommand, slashCommand);
	return 1;
}

int CommandConfigManager::addJoinCommand(lua_State* L) {
	LuaObject slashcommand(L);
	if (!slashcommand.isValidTable())
		return 0;

	JoinCommand* slashCommand = new JoinCommand(slashcommand.getStringField("name"), server);
	parseSlashCommand(slashcommand, slashCommand);
	return 1;
}

int CommandConfigManager::addJoinGameCommand(lua_State* L) {
	LuaObject slashcommand(L);
	if (!slashcommand.isValidTable())
		return 0;

	JoinGameCommand* slashCommand = new JoinGameCommand(slashcommand.getStringField("name"), server);
	parseSlashCommand(slashcommand, slashCommand);
	return 1;
}

int CommandConfigManager::addKickCommand(lua_State* L) {
	LuaObject slashcommand(L);
	if (!slashcommand.isValidTable())
		return 0;

	KickCommand* slashCommand = new KickCommand(slashcommand.getStringField("name"), server);
	parseSlashCommand(slashcommand, slashCommand);
	return 1;
}

int CommandConfigManager::addKillCommand(lua_State* L) {
	LuaObject slashcommand(L);
	if (!slashcommand.isValidTable())
		return 0;

	KillCommand* slashCommand = new KillCommand(slashcommand.getStringField("name"), server);
	parseSlashCommand(slashcommand, slashCommand);
	return 1;
}

int CommandConfigManager::addKillPlayerCommand(lua_State* L) {
	LuaObject slashcommand(L);
	if (!slashcommand.isValidTable())
		return 0;

	KillPlayerCommand* slashCommand = new KillPlayerCommand(slashcommand.getStringField("name"), server);
	parseSlashCommand(slashcommand, slashCommand);
	return 1;
}

int CommandConfigManager::addKipUpShotCommand(lua_State* L) {
	LuaObject slashcommand(L);
	if (!slashcommand.isValidTable())
		return 0;

	KipUpShotCommand* slashCommand = new KipUpShotCommand(slashcommand.getStringField("name"), server);
	parseSlashCommand(slashcommand, slashCommand);
	return 1;
}

int CommandConfigManager::addKneelCommand(lua_State* L) {
	LuaObject slashcommand(L);
	if (!slashcommand.isValidTable())
		return 0;

	KneelCommand* slashCommand = new KneelCommand(slashcommand.getStringField("name"), server);
	parseSlashCommand(slashcommand, slashCommand);
	return 1;
}

int CommandConfigManager::addKnockdownAttackCommand(lua_State* L) {
	LuaObject slashcommand(L);
	if (!slashcommand.isValidTable())
		return 0;

	KnockdownAttackCommand* slashCommand = new KnockdownAttackCommand(slashcommand.getStringField("name"), server);
	parseSlashCommand(slashcommand, slashCommand);
	return 1;
}

int CommandConfigManager::addKnockdownFireCommand(lua_State* L) {
	LuaObject slashcommand(L);
	if (!slashcommand.isValidTable())
		return 0;

	KnockdownFireCommand* slashCommand = new KnockdownFireCommand(slashcommand.getStringField("name"), server);
	parseSlashCommand(slashcommand, slashCommand);
	return 1;
}

int CommandConfigManager::addLagCommand(lua_State* L) {
	LuaObject slashcommand(L);
	if (!slashcommand.isValidTable())
		return 0;

	LagCommand* slashCommand = new LagCommand(slashcommand.getStringField("name"), server);
	parseSlashCommand(slashcommand, slashCommand);
	return 1;
}

int CommandConfigManager::addLastDitchCommand(lua_State* L) {
	LuaObject slashcommand(L);
	if (!slashcommand.isValidTable())
		return 0;

	LastDitchCommand* slashCommand = new LastDitchCommand(slashcommand.getStringField("name"), server);
	parseSlashCommand(slashcommand, slashCommand);
	return 1;
}

int CommandConfigManager::addLaunchFireworkCommand(lua_State* L) {
	LuaObject slashcommand(L);
	if (!slashcommand.isValidTable())
		return 0;

	LaunchFireworkCommand* slashCommand = new LaunchFireworkCommand(slashcommand.getStringField("name"), server);
	parseSlashCommand(slashcommand, slashCommand);
	return 1;
}

int CommandConfigManager::addLeaveGameCommand(lua_State* L) {
	LuaObject slashcommand(L);
	if (!slashcommand.isValidTable())
		return 0;

	LeaveGameCommand* slashCommand = new LeaveGameCommand(slashcommand.getStringField("name"), server);
	parseSlashCommand(slashcommand, slashCommand);
	return 1;
}

int CommandConfigManager::addLeaveGroupCommand(lua_State* L) {
	LuaObject slashcommand(L);
	if (!slashcommand.isValidTable())
		return 0;

	LeaveGroupCommand* slashCommand = new LeaveGroupCommand(slashcommand.getStringField("name"), server);
	parseSlashCommand(slashcommand, slashCommand);
	return 1;
}

int CommandConfigManager::addLegShot1Command(lua_State* L) {
	LuaObject slashcommand(L);
	if (!slashcommand.isValidTable())
		return 0;

	LegShot1Command* slashCommand = new LegShot1Command(slashcommand.getStringField("name"), server);
	parseSlashCommand(slashcommand, slashCommand);
	return 1;
}

int CommandConfigManager::addLegShot2Command(lua_State* L) {
	LuaObject slashcommand(L);
	if (!slashcommand.isValidTable())
		return 0;

	LegShot2Command* slashCommand = new LegShot2Command(slashcommand.getStringField("name"), server);
	parseSlashCommand(slashcommand, slashCommand);
	return 1;
}

int CommandConfigManager::addLegShot3Command(lua_State* L) {
	LuaObject slashcommand(L);
	if (!slashcommand.isValidTable())
		return 0;

	LegShot3Command* slashCommand = new LegShot3Command(slashcommand.getStringField("name"), server);
	parseSlashCommand(slashcommand, slashCommand);
	return 1;
}

int CommandConfigManager::addLfgCommand(lua_State* L) {
	LuaObject slashcommand(L);
	if (!slashcommand.isValidTable())
		return 0;

	LfgCommand* slashCommand = new LfgCommand(slashcommand.getStringField("name"), server);
	parseSlashCommand(slashcommand, slashCommand);
	return 1;
}

int CommandConfigManager::addListActiveQuestsCommand(lua_State* L) {
	LuaObject slashcommand(L);
	if (!slashcommand.isValidTable())
		return 0;

	ListActiveQuestsCommand* slashCommand = new ListActiveQuestsCommand(slashcommand.getStringField("name"), server);
	parseSlashCommand(slashcommand, slashCommand);
	return 1;
}

int CommandConfigManager::addListCompletedQuestsCommand(lua_State* L) {
	LuaObject slashcommand(L);
	if (!slashcommand.isValidTable())
		return 0;

	ListCompletedQuestsCommand* slashCommand = new ListCompletedQuestsCommand(slashcommand.getStringField("name"), server);
	parseSlashCommand(slashcommand, slashCommand);
	return 1;
}

int CommandConfigManager::addListenCommand(lua_State* L) {
	LuaObject slashcommand(L);
	if (!slashcommand.isValidTable())
		return 0;

	ListenCommand* slashCommand = new ListenCommand(slashcommand.getStringField("name"), server);
	parseSlashCommand(slashcommand, slashCommand);
	return 1;
}

int CommandConfigManager::addListGuildsCommand(lua_State* L) {
	LuaObject slashcommand(L);
	if (!slashcommand.isValidTable())
		return 0;

	ListGuildsCommand* slashCommand = new ListGuildsCommand(slashcommand.getStringField("name"), server);
	parseSlashCommand(slashcommand, slashCommand);
	return 1;
}

int CommandConfigManager::addLogoutCommand(lua_State* L) {
	LuaObject slashcommand(L);
	if (!slashcommand.isValidTable())
		return 0;

	LogoutCommand* slashCommand = new LogoutCommand(slashcommand.getStringField("name"), server);
	parseSlashCommand(slashcommand, slashCommand);
	return 1;
}

int CommandConfigManager::addLootCommand(lua_State* L) {
	LuaObject slashcommand(L);
	if (!slashcommand.isValidTable())
		return 0;

	LootCommand* slashCommand = new LootCommand(slashcommand.getStringField("name"), server);
	parseSlashCommand(slashcommand, slashCommand);
	return 1;
}

int CommandConfigManager::addLootAiCorpseCommand(lua_State* L) {
	LuaObject slashcommand(L);
	if (!slashcommand.isValidTable())
		return 0;

	LootAiCorpseCommand* slashCommand = new LootAiCorpseCommand(slashcommand.getStringField("name"), server);
	parseSlashCommand(slashcommand, slashCommand);
	return 1;
}

int CommandConfigManager::addLootPlayerCorpseCommand(lua_State* L) {
	LuaObject slashcommand(L);
	if (!slashcommand.isValidTable())
		return 0;

	LootPlayerCorpseCommand* slashCommand = new LootPlayerCorpseCommand(slashcommand.getStringField("name"), server);
	parseSlashCommand(slashcommand, slashCommand);
	return 1;
}

int CommandConfigManager::addLowBlowCommand(lua_State* L) {
	LuaObject slashcommand(L);
	if (!slashcommand.isValidTable())
		return 0;

	LowBlowCommand* slashCommand = new LowBlowCommand(slashcommand.getStringField("name"), server);
	parseSlashCommand(slashcommand, slashCommand);
	return 1;
}

int CommandConfigManager::addMakeLeaderCommand(lua_State* L) {
	LuaObject slashcommand(L);
	if (!slashcommand.isValidTable())
		return 0;

	MakeLeaderCommand* slashCommand = new MakeLeaderCommand(slashcommand.getStringField("name"), server);
	parseSlashCommand(slashcommand, slashCommand);
	return 1;
}

int CommandConfigManager::addMakeSurveyCommand(lua_State* L) {
	LuaObject slashcommand(L);
	if (!slashcommand.isValidTable())
		return 0;

	MakeSurveyCommand* slashCommand = new MakeSurveyCommand(slashcommand.getStringField("name"), server);
	parseSlashCommand(slashcommand, slashCommand);
	return 1;
}

int CommandConfigManager::addManufactureCommand(lua_State* L) {
	LuaObject slashcommand(L);
	if (!slashcommand.isValidTable())
		return 0;

	ManufactureCommand* slashCommand = new ManufactureCommand(slashcommand.getStringField("name"), server);
	parseSlashCommand(slashcommand, slashCommand);
	return 1;
}

int CommandConfigManager::addMaskscentCommand(lua_State* L) {
	LuaObject slashcommand(L);
	if (!slashcommand.isValidTable())
		return 0;

	MaskscentCommand* slashCommand = new MaskscentCommand(slashcommand.getStringField("name"), server);
	parseSlashCommand(slashcommand, slashCommand);
	return 1;
}

int CommandConfigManager::addMaxCombatAbilityCommand(lua_State* L) {
	LuaObject slashcommand(L);
	if (!slashcommand.isValidTable())
		return 0;

	MaxCombatAbilityCommand* slashCommand = new MaxCombatAbilityCommand(slashcommand.getStringField("name"), server);
	parseSlashCommand(slashcommand, slashCommand);
	return 1;
}

int CommandConfigManager::addMaxStatsCommand(lua_State* L) {
	LuaObject slashcommand(L);
	if (!slashcommand.isValidTable())
		return 0;

	MaxStatsCommand* slashCommand = new MaxStatsCommand(slashcommand.getStringField("name"), server);
	parseSlashCommand(slashcommand, slashCommand);
	return 1;
}

int CommandConfigManager::addMedicalForageCommand(lua_State* L) {
	LuaObject slashcommand(L);
	if (!slashcommand.isValidTable())
		return 0;

	MedicalForageCommand* slashCommand = new MedicalForageCommand(slashcommand.getStringField("name"), server);
	parseSlashCommand(slashcommand, slashCommand);
	return 1;
}

int CommandConfigManager::addMeditateCommand(lua_State* L) {
	LuaObject slashcommand(L);
	if (!slashcommand.isValidTable())
		return 0;

	MeditateCommand* slashCommand = new MeditateCommand(slashcommand.getStringField("name"), server);
	parseSlashCommand(slashcommand, slashCommand);
	return 1;
}

int CommandConfigManager::addMediumDiseaseCommand(lua_State* L) {
	LuaObject slashcommand(L);
	if (!slashcommand.isValidTable())
		return 0;

	MediumDiseaseCommand* slashCommand = new MediumDiseaseCommand(slashcommand.getStringField("name"), server);
	parseSlashCommand(slashcommand, slashCommand);
	return 1;
}

int CommandConfigManager::addMediumPoisonCommand(lua_State* L) {
	LuaObject slashcommand(L);
	if (!slashcommand.isValidTable())
		return 0;

	MediumPoisonCommand* slashCommand = new MediumPoisonCommand(slashcommand.getStringField("name"), server);
	parseSlashCommand(slashcommand, slashCommand);
	return 1;
}

int CommandConfigManager::addMelee1hBlindHit1Command(lua_State* L) {
	LuaObject slashcommand(L);
	if (!slashcommand.isValidTable())
		return 0;

	Melee1hBlindHit1Command* slashCommand = new Melee1hBlindHit1Command(slashcommand.getStringField("name"), server);
	parseSlashCommand(slashcommand, slashCommand);
	return 1;
}

int CommandConfigManager::addMelee1hBlindHit2Command(lua_State* L) {
	LuaObject slashcommand(L);
	if (!slashcommand.isValidTable())
		return 0;

	Melee1hBlindHit2Command* slashCommand = new Melee1hBlindHit2Command(slashcommand.getStringField("name"), server);
	parseSlashCommand(slashcommand, slashCommand);
	return 1;
}

int CommandConfigManager::addMelee1hBodyHit1Command(lua_State* L) {
	LuaObject slashcommand(L);
	if (!slashcommand.isValidTable())
		return 0;

	Melee1hBodyHit1Command* slashCommand = new Melee1hBodyHit1Command(slashcommand.getStringField("name"), server);
	parseSlashCommand(slashcommand, slashCommand);
	return 1;
}

int CommandConfigManager::addMelee1hBodyHit2Command(lua_State* L) {
	LuaObject slashcommand(L);
	if (!slashcommand.isValidTable())
		return 0;

	Melee1hBodyHit2Command* slashCommand = new Melee1hBodyHit2Command(slashcommand.getStringField("name"), server);
	parseSlashCommand(slashcommand, slashCommand);
	return 1;
}

int CommandConfigManager::addMelee1hBodyHit3Command(lua_State* L) {
	LuaObject slashcommand(L);
	if (!slashcommand.isValidTable())
		return 0;

	Melee1hBodyHit3Command* slashCommand = new Melee1hBodyHit3Command(slashcommand.getStringField("name"), server);
	parseSlashCommand(slashcommand, slashCommand);
	return 1;
}

int CommandConfigManager::addMelee1hDizzyHit1Command(lua_State* L) {
	LuaObject slashcommand(L);
	if (!slashcommand.isValidTable())
		return 0;

	Melee1hDizzyHit1Command* slashCommand = new Melee1hDizzyHit1Command(slashcommand.getStringField("name"), server);
	parseSlashCommand(slashcommand, slashCommand);
	return 1;
}

int CommandConfigManager::addMelee1hDizzyHit2Command(lua_State* L) {
	LuaObject slashcommand(L);
	if (!slashcommand.isValidTable())
		return 0;

	Melee1hDizzyHit2Command* slashCommand = new Melee1hDizzyHit2Command(slashcommand.getStringField("name"), server);
	parseSlashCommand(slashcommand, slashCommand);
	return 1;
}

int CommandConfigManager::addMelee1hHealthHit1Command(lua_State* L) {
	LuaObject slashcommand(L);
	if (!slashcommand.isValidTable())
		return 0;

	Melee1hHealthHit1Command* slashCommand = new Melee1hHealthHit1Command(slashcommand.getStringField("name"), server);
	parseSlashCommand(slashcommand, slashCommand);
	return 1;
}

int CommandConfigManager::addMelee1hHealthHit2Command(lua_State* L) {
	LuaObject slashcommand(L);
	if (!slashcommand.isValidTable())
		return 0;

	Melee1hHealthHit2Command* slashCommand = new Melee1hHealthHit2Command(slashcommand.getStringField("name"), server);
	parseSlashCommand(slashcommand, slashCommand);
	return 1;
}

int CommandConfigManager::addMelee1hHit1Command(lua_State* L) {
	LuaObject slashcommand(L);
	if (!slashcommand.isValidTable())
		return 0;

	Melee1hHit1Command* slashCommand = new Melee1hHit1Command(slashcommand.getStringField("name"), server);
	parseSlashCommand(slashcommand, slashCommand);
	return 1;
}

int CommandConfigManager::addMelee1hHit2Command(lua_State* L) {
	LuaObject slashcommand(L);
	if (!slashcommand.isValidTable())
		return 0;

	Melee1hHit2Command* slashCommand = new Melee1hHit2Command(slashcommand.getStringField("name"), server);
	parseSlashCommand(slashcommand, slashCommand);
	return 1;
}

int CommandConfigManager::addMelee1hHit3Command(lua_State* L) {
	LuaObject slashcommand(L);
	if (!slashcommand.isValidTable())
		return 0;

	Melee1hHit3Command* slashCommand = new Melee1hHit3Command(slashcommand.getStringField("name"), server);
	parseSlashCommand(slashcommand, slashCommand);
	return 1;
}

int CommandConfigManager::addMelee1hLunge1Command(lua_State* L) {
	LuaObject slashcommand(L);
	if (!slashcommand.isValidTable())
		return 0;

	Melee1hLunge1Command* slashCommand = new Melee1hLunge1Command(slashcommand.getStringField("name"), server);
	parseSlashCommand(slashcommand, slashCommand);
	return 1;
}

int CommandConfigManager::addMelee1hLunge2Command(lua_State* L) {
	LuaObject slashcommand(L);
	if (!slashcommand.isValidTable())
		return 0;

	Melee1hLunge2Command* slashCommand = new Melee1hLunge2Command(slashcommand.getStringField("name"), server);
	parseSlashCommand(slashcommand, slashCommand);
	return 1;
}

int CommandConfigManager::addMelee1hScatterHit1Command(lua_State* L) {
	LuaObject slashcommand(L);
	if (!slashcommand.isValidTable())
		return 0;

	Melee1hScatterHit1Command* slashCommand = new Melee1hScatterHit1Command(slashcommand.getStringField("name"), server);
	parseSlashCommand(slashcommand, slashCommand);
	return 1;
}

int CommandConfigManager::addMelee1hScatterHit2Command(lua_State* L) {
	LuaObject slashcommand(L);
	if (!slashcommand.isValidTable())
		return 0;

	Melee1hScatterHit2Command* slashCommand = new Melee1hScatterHit2Command(slashcommand.getStringField("name"), server);
	parseSlashCommand(slashcommand, slashCommand);
	return 1;
}

int CommandConfigManager::addMelee1hSpinAttack1Command(lua_State* L) {
	LuaObject slashcommand(L);
	if (!slashcommand.isValidTable())
		return 0;

	Melee1hSpinAttack1Command* slashCommand = new Melee1hSpinAttack1Command(slashcommand.getStringField("name"), server);
	parseSlashCommand(slashcommand, slashCommand);
	return 1;
}

int CommandConfigManager::addMelee1hSpinAttack2Command(lua_State* L) {
	LuaObject slashcommand(L);
	if (!slashcommand.isValidTable())
		return 0;

	Melee1hSpinAttack2Command* slashCommand = new Melee1hSpinAttack2Command(slashcommand.getStringField("name"), server);
	parseSlashCommand(slashcommand, slashCommand);
	return 1;
}

int CommandConfigManager::addMelee2hArea1Command(lua_State* L) {
	LuaObject slashcommand(L);
	if (!slashcommand.isValidTable())
		return 0;

	Melee2hArea1Command* slashCommand = new Melee2hArea1Command(slashcommand.getStringField("name"), server);
	parseSlashCommand(slashcommand, slashCommand);
	return 1;
}

int CommandConfigManager::addMelee2hArea2Command(lua_State* L) {
	LuaObject slashcommand(L);
	if (!slashcommand.isValidTable())
		return 0;

	Melee2hArea2Command* slashCommand = new Melee2hArea2Command(slashcommand.getStringField("name"), server);
	parseSlashCommand(slashcommand, slashCommand);
	return 1;
}

int CommandConfigManager::addMelee2hArea3Command(lua_State* L) {
	LuaObject slashcommand(L);
	if (!slashcommand.isValidTable())
		return 0;

	Melee2hArea3Command* slashCommand = new Melee2hArea3Command(slashcommand.getStringField("name"), server);
	parseSlashCommand(slashcommand, slashCommand);
	return 1;
}

int CommandConfigManager::addMelee2hHeadHit1Command(lua_State* L) {
	LuaObject slashcommand(L);
	if (!slashcommand.isValidTable())
		return 0;

	Melee2hHeadHit1Command* slashCommand = new Melee2hHeadHit1Command(slashcommand.getStringField("name"), server);
	parseSlashCommand(slashcommand, slashCommand);
	return 1;
}

int CommandConfigManager::addMelee2hHeadHit2Command(lua_State* L) {
	LuaObject slashcommand(L);
	if (!slashcommand.isValidTable())
		return 0;

	Melee2hHeadHit2Command* slashCommand = new Melee2hHeadHit2Command(slashcommand.getStringField("name"), server);
	parseSlashCommand(slashcommand, slashCommand);
	return 1;
}

int CommandConfigManager::addMelee2hHeadHit3Command(lua_State* L) {
	LuaObject slashcommand(L);
	if (!slashcommand.isValidTable())
		return 0;

	Melee2hHeadHit3Command* slashCommand = new Melee2hHeadHit3Command(slashcommand.getStringField("name"), server);
	parseSlashCommand(slashcommand, slashCommand);
	return 1;
}

int CommandConfigManager::addMelee2hHit1Command(lua_State* L) {
	LuaObject slashcommand(L);
	if (!slashcommand.isValidTable())
		return 0;

	Melee2hHit1Command* slashCommand = new Melee2hHit1Command(slashcommand.getStringField("name"), server);
	parseSlashCommand(slashcommand, slashCommand);
	return 1;
}

int CommandConfigManager::addMelee2hHit2Command(lua_State* L) {
	LuaObject slashcommand(L);
	if (!slashcommand.isValidTable())
		return 0;

	Melee2hHit2Command* slashCommand = new Melee2hHit2Command(slashcommand.getStringField("name"), server);
	parseSlashCommand(slashcommand, slashCommand);
	return 1;
}

int CommandConfigManager::addMelee2hHit3Command(lua_State* L) {
	LuaObject slashcommand(L);
	if (!slashcommand.isValidTable())
		return 0;

	Melee2hHit3Command* slashCommand = new Melee2hHit3Command(slashcommand.getStringField("name"), server);
	parseSlashCommand(slashcommand, slashCommand);
	return 1;
}

int CommandConfigManager::addMelee2hLunge1Command(lua_State* L) {
	LuaObject slashcommand(L);
	if (!slashcommand.isValidTable())
		return 0;

	Melee2hLunge1Command* slashCommand = new Melee2hLunge1Command(slashcommand.getStringField("name"), server);
	parseSlashCommand(slashcommand, slashCommand);
	return 1;
}

int CommandConfigManager::addMelee2hLunge2Command(lua_State* L) {
	LuaObject slashcommand(L);
	if (!slashcommand.isValidTable())
		return 0;

	Melee2hLunge2Command* slashCommand = new Melee2hLunge2Command(slashcommand.getStringField("name"), server);
	parseSlashCommand(slashcommand, slashCommand);
	return 1;
}

int CommandConfigManager::addMelee2hMindHit1Command(lua_State* L) {
	LuaObject slashcommand(L);
	if (!slashcommand.isValidTable())
		return 0;

	Melee2hMindHit1Command* slashCommand = new Melee2hMindHit1Command(slashcommand.getStringField("name"), server);
	parseSlashCommand(slashcommand, slashCommand);
	return 1;
}

int CommandConfigManager::addMelee2hMindHit2Command(lua_State* L) {
	LuaObject slashcommand(L);
	if (!slashcommand.isValidTable())
		return 0;

	Melee2hMindHit2Command* slashCommand = new Melee2hMindHit2Command(slashcommand.getStringField("name"), server);
	parseSlashCommand(slashcommand, slashCommand);
	return 1;
}

int CommandConfigManager::addMelee2hSpinAttack1Command(lua_State* L) {
	LuaObject slashcommand(L);
	if (!slashcommand.isValidTable())
		return 0;

	Melee2hSpinAttack1Command* slashCommand = new Melee2hSpinAttack1Command(slashcommand.getStringField("name"), server);
	parseSlashCommand(slashcommand, slashCommand);
	return 1;
}

int CommandConfigManager::addMelee2hSpinAttack2Command(lua_State* L) {
	LuaObject slashcommand(L);
	if (!slashcommand.isValidTable())
		return 0;

	Melee2hSpinAttack2Command* slashCommand = new Melee2hSpinAttack2Command(slashcommand.getStringField("name"), server);
	parseSlashCommand(slashcommand, slashCommand);
	return 1;
}

int CommandConfigManager::addMelee2hSweep1Command(lua_State* L) {
	LuaObject slashcommand(L);
	if (!slashcommand.isValidTable())
		return 0;

	Melee2hSweep1Command* slashCommand = new Melee2hSweep1Command(slashcommand.getStringField("name"), server);
	parseSlashCommand(slashcommand, slashCommand);
	return 1;
}

int CommandConfigManager::addMelee2hSweep2Command(lua_State* L) {
	LuaObject slashcommand(L);
	if (!slashcommand.isValidTable())
		return 0;

	Melee2hSweep2Command* slashCommand = new Melee2hSweep2Command(slashcommand.getStringField("name"), server);
	parseSlashCommand(slashcommand, slashCommand);
	return 1;
}

int CommandConfigManager::addMildDiseaseCommand(lua_State* L) {
	LuaObject slashcommand(L);
	if (!slashcommand.isValidTable())
		return 0;

	MildDiseaseCommand* slashCommand = new MildDiseaseCommand(slashcommand.getStringField("name"), server);
	parseSlashCommand(slashcommand, slashCommand);
	return 1;
}

int CommandConfigManager::addMildPoisonCommand(lua_State* L) {
	LuaObject slashcommand(L);
	if (!slashcommand.isValidTable())
		return 0;

	MildPoisonCommand* slashCommand = new MildPoisonCommand(slashcommand.getStringField("name"), server);
	parseSlashCommand(slashcommand, slashCommand);
	return 1;
}

int CommandConfigManager::addMindBlast1Command(lua_State* L) {
	LuaObject slashcommand(L);
	if (!slashcommand.isValidTable())
		return 0;

	MindBlast1Command* slashCommand = new MindBlast1Command(slashcommand.getStringField("name"), server);
	parseSlashCommand(slashcommand, slashCommand);
	return 1;
}

int CommandConfigManager::addMindBlast2Command(lua_State* L) {
	LuaObject slashcommand(L);
	if (!slashcommand.isValidTable())
		return 0;

	MindBlast2Command* slashCommand = new MindBlast2Command(slashcommand.getStringField("name"), server);
	parseSlashCommand(slashcommand, slashCommand);
	return 1;
}

int CommandConfigManager::addMindShot1Command(lua_State* L) {
	LuaObject slashcommand(L);
	if (!slashcommand.isValidTable())
		return 0;

	MindShot1Command* slashCommand = new MindShot1Command(slashcommand.getStringField("name"), server);
	parseSlashCommand(slashcommand, slashCommand);
	return 1;
}

int CommandConfigManager::addMindShot2Command(lua_State* L) {
	LuaObject slashcommand(L);
	if (!slashcommand.isValidTable())
		return 0;

	MindShot2Command* slashCommand = new MindShot2Command(slashcommand.getStringField("name"), server);
	parseSlashCommand(slashcommand, slashCommand);
	return 1;
}

int CommandConfigManager::addMoneyCommand(lua_State* L) {
	LuaObject slashcommand(L);
	if (!slashcommand.isValidTable())
		return 0;

	MoneyCommand* slashCommand = new MoneyCommand(slashcommand.getStringField("name"), server);
	parseSlashCommand(slashcommand, slashCommand);
	return 1;
}

int CommandConfigManager::addMountCommand(lua_State* L) {
	LuaObject slashcommand(L);
	if (!slashcommand.isValidTable())
		return 0;

	MountCommand* slashCommand = new MountCommand(slashcommand.getStringField("name"), server);
	parseSlashCommand(slashcommand, slashCommand);
	return 1;
}

int CommandConfigManager::addMoveFurnitureCommand(lua_State* L) {
	LuaObject slashcommand(L);
	if (!slashcommand.isValidTable())
		return 0;

	MoveFurnitureCommand* slashCommand = new MoveFurnitureCommand(slashcommand.getStringField("name"), server);
	parseSlashCommand(slashcommand, slashCommand);
	return 1;
}

int CommandConfigManager::addMultiTargetPistolShotCommand(lua_State* L) {
	LuaObject slashcommand(L);
	if (!slashcommand.isValidTable())
		return 0;

	MultiTargetPistolShotCommand* slashCommand = new MultiTargetPistolShotCommand(slashcommand.getStringField("name"), server);
	parseSlashCommand(slashcommand, slashCommand);
	return 1;
}

int CommandConfigManager::addMultiTargetShotCommand(lua_State* L) {
	LuaObject slashcommand(L);
	if (!slashcommand.isValidTable())
		return 0;

	MultiTargetShotCommand* slashCommand = new MultiTargetShotCommand(slashcommand.getStringField("name"), server);
	parseSlashCommand(slashcommand, slashCommand);
	return 1;
}

int CommandConfigManager::addNameStructureCommand(lua_State* L) {
	LuaObject slashcommand(L);
	if (!slashcommand.isValidTable())
		return 0;

	NameStructureCommand* slashCommand = new NameStructureCommand(slashcommand.getStringField("name"), server);
	parseSlashCommand(slashcommand, slashCommand);
	return 1;
}

int CommandConfigManager::addNewbiehelperCommand(lua_State* L) {
	LuaObject slashcommand(L);
	if (!slashcommand.isValidTable())
		return 0;

	NewbiehelperCommand* slashCommand = new NewbiehelperCommand(slashcommand.getStringField("name"), server);
	parseSlashCommand(slashcommand, slashCommand);
	return 1;
}

int CommandConfigManager::addNewbieRequestStartingLocationsCommand(lua_State* L) {
	LuaObject slashcommand(L);
	if (!slashcommand.isValidTable())
		return 0;

	NewbieRequestStartingLocationsCommand* slashCommand = new NewbieRequestStartingLocationsCommand(slashcommand.getStringField("name"), server);
	parseSlashCommand(slashcommand, slashCommand);
	return 1;
}

int CommandConfigManager::addNewbieSelectStartingLocationCommand(lua_State* L) {
	LuaObject slashcommand(L);
	if (!slashcommand.isValidTable())
		return 0;

	NewbieSelectStartingLocationCommand* slashCommand = new NewbieSelectStartingLocationCommand(slashcommand.getStringField("name"), server);
	parseSlashCommand(slashcommand, slashCommand);
	return 1;
}

int CommandConfigManager::addNextCraftingStageCommand(lua_State* L) {
	LuaObject slashcommand(L);
	if (!slashcommand.isValidTable())
		return 0;

	NextCraftingStageCommand* slashCommand = new NextCraftingStageCommand(slashcommand.getStringField("name"), server);
	parseSlashCommand(slashcommand, slashCommand);
	return 1;
}

int CommandConfigManager::addNpcCommand(lua_State* L) {
	LuaObject slashcommand(L);
	if (!slashcommand.isValidTable())
		return 0;

	NpcCommand* slashCommand = new NpcCommand(slashcommand.getStringField("name"), server);
	parseSlashCommand(slashcommand, slashCommand);
	return 1;
}

int CommandConfigManager::addNpcConversationSelectCommand(lua_State* L) {
	LuaObject slashcommand(L);
	if (!slashcommand.isValidTable())
		return 0;

	NpcConversationSelectCommand* slashCommand = new NpcConversationSelectCommand(slashcommand.getStringField("name"), server);
	parseSlashCommand(slashcommand, slashCommand);
	return 1;
}

int CommandConfigManager::addNpcConversationStartCommand(lua_State* L) {
	LuaObject slashcommand(L);
	if (!slashcommand.isValidTable())
		return 0;

	NpcConversationStartCommand* slashCommand = new NpcConversationStartCommand(slashcommand.getStringField("name"), server);
	parseSlashCommand(slashcommand, slashCommand);
	return 1;
}

int CommandConfigManager::addNpcConversationStopCommand(lua_State* L) {
	LuaObject slashcommand(L);
	if (!slashcommand.isValidTable())
		return 0;

	NpcConversationStopCommand* slashCommand = new NpcConversationStopCommand(slashcommand.getStringField("name"), server);
	parseSlashCommand(slashcommand, slashCommand);
	return 1;
}

int CommandConfigManager::addObjectCommand(lua_State* L) {
	LuaObject slashcommand(L);
	if (!slashcommand.isValidTable())
		return 0;

	ObjectCommand* slashCommand = new ObjectCommand(slashcommand.getStringField("name"), server);
	parseSlashCommand(slashcommand, slashCommand);
	return 1;
}

int CommandConfigManager::addObjvarCommand(lua_State* L) {
	LuaObject slashcommand(L);
	if (!slashcommand.isValidTable())
		return 0;

	ObjvarCommand* slashCommand = new ObjvarCommand(slashcommand.getStringField("name"), server);
	parseSlashCommand(slashcommand, slashCommand);
	return 1;
}

int CommandConfigManager::addOpenContainerCommand(lua_State* L) {
	LuaObject slashcommand(L);
	if (!slashcommand.isValidTable())
		return 0;

	OpenContainerCommand* slashCommand = new OpenContainerCommand(slashcommand.getStringField("name"), server);
	parseSlashCommand(slashcommand, slashCommand);
	return 1;
}

int CommandConfigManager::addOverChargeShot1Command(lua_State* L) {
	LuaObject slashcommand(L);
	if (!slashcommand.isValidTable())
		return 0;

	OverChargeShot1Command* slashCommand = new OverChargeShot1Command(slashcommand.getStringField("name"), server);
	parseSlashCommand(slashcommand, slashCommand);
	return 1;
}

int CommandConfigManager::addOverChargeShot2Command(lua_State* L) {
	LuaObject slashcommand(L);
	if (!slashcommand.isValidTable())
		return 0;

	OverChargeShot2Command* slashCommand = new OverChargeShot2Command(slashcommand.getStringField("name"), server);
	parseSlashCommand(slashcommand, slashCommand);
	return 1;
}

int CommandConfigManager::addOverrideActiveMonthsCommand(lua_State* L) {
	LuaObject slashcommand(L);
	if (!slashcommand.isValidTable())
		return 0;

	OverrideActiveMonthsCommand* slashCommand = new OverrideActiveMonthsCommand(slashcommand.getStringField("name"), server);
	parseSlashCommand(slashcommand, slashCommand);
	return 1;
}

int CommandConfigManager::addOverridePadawanTrialsEligibilityCommand(lua_State* L) {
	LuaObject slashcommand(L);
	if (!slashcommand.isValidTable())
		return 0;

	OverridePadawanTrialsEligibilityCommand* slashCommand = new OverridePadawanTrialsEligibilityCommand(slashcommand.getStringField("name"), server);
	parseSlashCommand(slashcommand, slashCommand);
	return 1;
}

int CommandConfigManager::addPanicShotCommand(lua_State* L) {
	LuaObject slashcommand(L);
	if (!slashcommand.isValidTable())
		return 0;

	PanicShotCommand* slashCommand = new PanicShotCommand(slashcommand.getStringField("name"), server);
	parseSlashCommand(slashcommand, slashCommand);
	return 1;
}

int CommandConfigManager::addPauseDanceCommand(lua_State* L) {
	LuaObject slashcommand(L);
	if (!slashcommand.isValidTable())
		return 0;

	PauseDanceCommand* slashCommand = new PauseDanceCommand(slashcommand.getStringField("name"), server);
	parseSlashCommand(slashcommand, slashCommand);
	return 1;
}

int CommandConfigManager::addPauseMusicCommand(lua_State* L) {
	LuaObject slashcommand(L);
	if (!slashcommand.isValidTable())
		return 0;

	PauseMusicCommand* slashCommand = new PauseMusicCommand(slashcommand.getStringField("name"), server);
	parseSlashCommand(slashcommand, slashCommand);
	return 1;
}

int CommandConfigManager::addPaWithdrawCommand(lua_State* L) {
	LuaObject slashcommand(L);
	if (!slashcommand.isValidTable())
		return 0;

	PaWithdrawCommand* slashCommand = new PaWithdrawCommand(slashcommand.getStringField("name"), server);
	parseSlashCommand(slashcommand, slashCommand);
	return 1;
}

int CommandConfigManager::addPaymaintenanceCommand(lua_State* L) {
	LuaObject slashcommand(L);
	if (!slashcommand.isValidTable())
		return 0;

	PaymaintenanceCommand* slashCommand = new PaymaintenanceCommand(slashcommand.getStringField("name"), server);
	parseSlashCommand(slashcommand, slashCommand);
	return 1;
}

int CommandConfigManager::addPeaceCommand(lua_State* L) {
	LuaObject slashcommand(L);
	if (!slashcommand.isValidTable())
		return 0;

	PeaceCommand* slashCommand = new PeaceCommand(slashcommand.getStringField("name"), server);
	parseSlashCommand(slashcommand, slashCommand);
	return 1;
}

int CommandConfigManager::addPermissionListModifyCommand(lua_State* L) {
	LuaObject slashcommand(L);
	if (!slashcommand.isValidTable())
		return 0;

	PermissionListModifyCommand* slashCommand = new PermissionListModifyCommand(slashcommand.getStringField("name"), server);
	parseSlashCommand(slashcommand, slashCommand);
	return 1;
}

int CommandConfigManager::addPistolMeleeDefense1Command(lua_State* L) {
	LuaObject slashcommand(L);
	if (!slashcommand.isValidTable())
		return 0;

	PistolMeleeDefense1Command* slashCommand = new PistolMeleeDefense1Command(slashcommand.getStringField("name"), server);
	parseSlashCommand(slashcommand, slashCommand);
	return 1;
}

int CommandConfigManager::addPistolMeleeDefense2Command(lua_State* L) {
	LuaObject slashcommand(L);
	if (!slashcommand.isValidTable())
		return 0;

	PistolMeleeDefense2Command* slashCommand = new PistolMeleeDefense2Command(slashcommand.getStringField("name"), server);
	parseSlashCommand(slashcommand, slashCommand);
	return 1;
}

int CommandConfigManager::addPlaceBattlefieldStructureCommand(lua_State* L) {
	LuaObject slashcommand(L);
	if (!slashcommand.isValidTable())
		return 0;

	PlaceBattlefieldStructureCommand* slashCommand = new PlaceBattlefieldStructureCommand(slashcommand.getStringField("name"), server);
	parseSlashCommand(slashcommand, slashCommand);
	return 1;
}

int CommandConfigManager::addPlaceStructureCommand(lua_State* L) {
	LuaObject slashcommand(L);
	if (!slashcommand.isValidTable())
		return 0;

	PlaceStructureCommand* slashCommand = new PlaceStructureCommand(slashcommand.getStringField("name"), server);
	parseSlashCommand(slashcommand, slashCommand);
	return 1;
}

int CommandConfigManager::addPlaceStructureModeCommand(lua_State* L) {
	LuaObject slashcommand(L);
	if (!slashcommand.isValidTable())
		return 0;

	PlaceStructureModeCommand* slashCommand = new PlaceStructureModeCommand(slashcommand.getStringField("name"), server);
	parseSlashCommand(slashcommand, slashCommand);
	return 1;
}

int CommandConfigManager::addPlanetCommand(lua_State* L) {
	LuaObject slashcommand(L);
	if (!slashcommand.isValidTable())
		return 0;

	PlanetCommand* slashCommand = new PlanetCommand(slashcommand.getStringField("name"), server);
	parseSlashCommand(slashcommand, slashCommand);
	return 1;
}

int CommandConfigManager::addPlanetsayCommand(lua_State* L) {
	LuaObject slashcommand(L);
	if (!slashcommand.isValidTable())
		return 0;

	PlanetsayCommand* slashCommand = new PlanetsayCommand(slashcommand.getStringField("name"), server);
	parseSlashCommand(slashcommand, slashCommand);
	return 1;
}

int CommandConfigManager::addPlanetwarpCommand(lua_State* L) {
	LuaObject slashcommand(L);
	if (!slashcommand.isValidTable())
		return 0;

	PlanetwarpCommand* slashCommand = new PlanetwarpCommand(slashcommand.getStringField("name"), server);
	parseSlashCommand(slashcommand, slashCommand);
	return 1;
}

int CommandConfigManager::addPlanetwarpTargetCommand(lua_State* L) {
	LuaObject slashcommand(L);
	if (!slashcommand.isValidTable())
		return 0;

	PlanetwarpTargetCommand* slashCommand = new PlanetwarpTargetCommand(slashcommand.getStringField("name"), server);
	parseSlashCommand(slashcommand, slashCommand);
	return 1;
}

int CommandConfigManager::addPointBlankArea1Command(lua_State* L) {
	LuaObject slashcommand(L);
	if (!slashcommand.isValidTable())
		return 0;

	PointBlankArea1Command* slashCommand = new PointBlankArea1Command(slashcommand.getStringField("name"), server);
	parseSlashCommand(slashcommand, slashCommand);
	return 1;
}

int CommandConfigManager::addPointBlankArea2Command(lua_State* L) {
	LuaObject slashcommand(L);
	if (!slashcommand.isValidTable())
		return 0;

	PointBlankArea2Command* slashCommand = new PointBlankArea2Command(slashcommand.getStringField("name"), server);
	parseSlashCommand(slashcommand, slashCommand);
	return 1;
}

int CommandConfigManager::addPointBlankSingle1Command(lua_State* L) {
	LuaObject slashcommand(L);
	if (!slashcommand.isValidTable())
		return 0;

	PointBlankSingle1Command* slashCommand = new PointBlankSingle1Command(slashcommand.getStringField("name"), server);
	parseSlashCommand(slashcommand, slashCommand);
	return 1;
}

int CommandConfigManager::addPointBlankSingle2Command(lua_State* L) {
	LuaObject slashcommand(L);
	if (!slashcommand.isValidTable())
		return 0;

	PointBlankSingle2Command* slashCommand = new PointBlankSingle2Command(slashcommand.getStringField("name"), server);
	parseSlashCommand(slashcommand, slashCommand);
	return 1;
}

int CommandConfigManager::addPolearmActionHit1Command(lua_State* L) {
	LuaObject slashcommand(L);
	if (!slashcommand.isValidTable())
		return 0;

	PolearmActionHit1Command* slashCommand = new PolearmActionHit1Command(slashcommand.getStringField("name"), server);
	parseSlashCommand(slashcommand, slashCommand);
	return 1;
}

int CommandConfigManager::addPolearmActionHit2Command(lua_State* L) {
	LuaObject slashcommand(L);
	if (!slashcommand.isValidTable())
		return 0;

	PolearmActionHit2Command* slashCommand = new PolearmActionHit2Command(slashcommand.getStringField("name"), server);
	parseSlashCommand(slashcommand, slashCommand);
	return 1;
}

int CommandConfigManager::addPolearmArea1Command(lua_State* L) {
	LuaObject slashcommand(L);
	if (!slashcommand.isValidTable())
		return 0;

	PolearmArea1Command* slashCommand = new PolearmArea1Command(slashcommand.getStringField("name"), server);
	parseSlashCommand(slashcommand, slashCommand);
	return 1;
}

int CommandConfigManager::addPolearmArea2Command(lua_State* L) {
	LuaObject slashcommand(L);
	if (!slashcommand.isValidTable())
		return 0;

	PolearmArea2Command* slashCommand = new PolearmArea2Command(slashcommand.getStringField("name"), server);
	parseSlashCommand(slashcommand, slashCommand);
	return 1;
}

int CommandConfigManager::addPolearmHit1Command(lua_State* L) {
	LuaObject slashcommand(L);
	if (!slashcommand.isValidTable())
		return 0;

	PolearmHit1Command* slashCommand = new PolearmHit1Command(slashcommand.getStringField("name"), server);
	parseSlashCommand(slashcommand, slashCommand);
	return 1;
}

int CommandConfigManager::addPolearmHit2Command(lua_State* L) {
	LuaObject slashcommand(L);
	if (!slashcommand.isValidTable())
		return 0;

	PolearmHit2Command* slashCommand = new PolearmHit2Command(slashcommand.getStringField("name"), server);
	parseSlashCommand(slashcommand, slashCommand);
	return 1;
}

int CommandConfigManager::addPolearmHit3Command(lua_State* L) {
	LuaObject slashcommand(L);
	if (!slashcommand.isValidTable())
		return 0;

	PolearmHit3Command* slashCommand = new PolearmHit3Command(slashcommand.getStringField("name"), server);
	parseSlashCommand(slashcommand, slashCommand);
	return 1;
}

int CommandConfigManager::addPolearmLegHit1Command(lua_State* L) {
	LuaObject slashcommand(L);
	if (!slashcommand.isValidTable())
		return 0;

	PolearmLegHit1Command* slashCommand = new PolearmLegHit1Command(slashcommand.getStringField("name"), server);
	parseSlashCommand(slashcommand, slashCommand);
	return 1;
}

int CommandConfigManager::addPolearmLegHit2Command(lua_State* L) {
	LuaObject slashcommand(L);
	if (!slashcommand.isValidTable())
		return 0;

	PolearmLegHit2Command* slashCommand = new PolearmLegHit2Command(slashcommand.getStringField("name"), server);
	parseSlashCommand(slashcommand, slashCommand);
	return 1;
}

int CommandConfigManager::addPolearmLegHit3Command(lua_State* L) {
	LuaObject slashcommand(L);
	if (!slashcommand.isValidTable())
		return 0;

	PolearmLegHit3Command* slashCommand = new PolearmLegHit3Command(slashcommand.getStringField("name"), server);
	parseSlashCommand(slashcommand, slashCommand);
	return 1;
}

int CommandConfigManager::addPolearmLunge1Command(lua_State* L) {
	LuaObject slashcommand(L);
	if (!slashcommand.isValidTable())
		return 0;

	PolearmLunge1Command* slashCommand = new PolearmLunge1Command(slashcommand.getStringField("name"), server);
	parseSlashCommand(slashcommand, slashCommand);
	return 1;
}

int CommandConfigManager::addPolearmLunge2Command(lua_State* L) {
	LuaObject slashcommand(L);
	if (!slashcommand.isValidTable())
		return 0;

	PolearmLunge2Command* slashCommand = new PolearmLunge2Command(slashcommand.getStringField("name"), server);
	parseSlashCommand(slashcommand, slashCommand);
	return 1;
}

int CommandConfigManager::addPolearmSpinAttack1Command(lua_State* L) {
	LuaObject slashcommand(L);
	if (!slashcommand.isValidTable())
		return 0;

	PolearmSpinAttack1Command* slashCommand = new PolearmSpinAttack1Command(slashcommand.getStringField("name"), server);
	parseSlashCommand(slashcommand, slashCommand);
	return 1;
}

int CommandConfigManager::addPolearmSpinAttack2Command(lua_State* L) {
	LuaObject slashcommand(L);
	if (!slashcommand.isValidTable())
		return 0;

	PolearmSpinAttack2Command* slashCommand = new PolearmSpinAttack2Command(slashcommand.getStringField("name"), server);
	parseSlashCommand(slashcommand, slashCommand);
	return 1;
}

int CommandConfigManager::addPolearmStun1Command(lua_State* L) {
	LuaObject slashcommand(L);
	if (!slashcommand.isValidTable())
		return 0;

	PolearmStun1Command* slashCommand = new PolearmStun1Command(slashcommand.getStringField("name"), server);
	parseSlashCommand(slashcommand, slashCommand);
	return 1;
}

int CommandConfigManager::addPolearmStun2Command(lua_State* L) {
	LuaObject slashcommand(L);
	if (!slashcommand.isValidTable())
		return 0;

	PolearmStun2Command* slashCommand = new PolearmStun2Command(slashcommand.getStringField("name"), server);
	parseSlashCommand(slashcommand, slashCommand);
	return 1;
}

int CommandConfigManager::addPolearmSweep1Command(lua_State* L) {
	LuaObject slashcommand(L);
	if (!slashcommand.isValidTable())
		return 0;

	PolearmSweep1Command* slashCommand = new PolearmSweep1Command(slashcommand.getStringField("name"), server);
	parseSlashCommand(slashcommand, slashCommand);
	return 1;
}

int CommandConfigManager::addPolearmSweep2Command(lua_State* L) {
	LuaObject slashcommand(L);
	if (!slashcommand.isValidTable())
		return 0;

	PolearmSweep2Command* slashCommand = new PolearmSweep2Command(slashcommand.getStringField("name"), server);
	parseSlashCommand(slashcommand, slashCommand);
	return 1;
}

int CommandConfigManager::addPostureDownAttackCommand(lua_State* L) {
	LuaObject slashcommand(L);
	if (!slashcommand.isValidTable())
		return 0;

	PostureDownAttackCommand* slashCommand = new PostureDownAttackCommand(slashcommand.getStringField("name"), server);
	parseSlashCommand(slashcommand, slashCommand);
	return 1;
}

int CommandConfigManager::addPostureUpAttackCommand(lua_State* L) {
	LuaObject slashcommand(L);
	if (!slashcommand.isValidTable())
		return 0;

	PostureUpAttackCommand* slashCommand = new PostureUpAttackCommand(slashcommand.getStringField("name"), server);
	parseSlashCommand(slashcommand, slashCommand);
	return 1;
}

int CommandConfigManager::addPowerBoostCommand(lua_State* L) {
	LuaObject slashcommand(L);
	if (!slashcommand.isValidTable())
		return 0;

	PowerBoostCommand* slashCommand = new PowerBoostCommand(slashcommand.getStringField("name"), server);
	parseSlashCommand(slashcommand, slashCommand);
	return 1;
}

int CommandConfigManager::addProneCommand(lua_State* L) {
	LuaObject slashcommand(L);
	if (!slashcommand.isValidTable())
		return 0;

	ProneCommand* slashCommand = new ProneCommand(slashcommand.getStringField("name"), server);
	parseSlashCommand(slashcommand, slashCommand);
	return 1;
}

int CommandConfigManager::addPurchaseReinforcementCommand(lua_State* L) {
	LuaObject slashcommand(L);
	if (!slashcommand.isValidTable())
		return 0;

	PurchaseReinforcementCommand* slashCommand = new PurchaseReinforcementCommand(slashcommand.getStringField("name"), server);
	parseSlashCommand(slashcommand, slashCommand);
	return 1;
}

int CommandConfigManager::addPurchaseTicketCommand(lua_State* L) {
	LuaObject slashcommand(L);
	if (!slashcommand.isValidTable())
		return 0;

	PurchaseTicketCommand* slashCommand = new PurchaseTicketCommand(slashcommand.getStringField("name"), server);
	parseSlashCommand(slashcommand, slashCommand);
	return 1;
}

int CommandConfigManager::addQuickHealCommand(lua_State* L) {
	LuaObject slashcommand(L);
	if (!slashcommand.isValidTable())
		return 0;

	QuickHealCommand* slashCommand = new QuickHealCommand(slashcommand.getStringField("name"), server);
	parseSlashCommand(slashcommand, slashCommand);
	return 1;
}

int CommandConfigManager::addRallyCommand(lua_State* L) {
	LuaObject slashcommand(L);
	if (!slashcommand.isValidTable())
		return 0;

	RallyCommand* slashCommand = new RallyCommand(slashcommand.getStringField("name"), server);
	parseSlashCommand(slashcommand, slashCommand);
	return 1;
}

int CommandConfigManager::addReconnectToTransferServerCommand(lua_State* L) {
	LuaObject slashcommand(L);
	if (!slashcommand.isValidTable())
		return 0;

	ReconnectToTransferServerCommand* slashCommand = new ReconnectToTransferServerCommand(slashcommand.getStringField("name"), server);
	parseSlashCommand(slashcommand, slashCommand);
	return 1;
}

int CommandConfigManager::addRecruitSkillTrainerCommand(lua_State* L) {
	LuaObject slashcommand(L);
	if (!slashcommand.isValidTable())
		return 0;

	RecruitSkillTrainerCommand* slashCommand = new RecruitSkillTrainerCommand(slashcommand.getStringField("name"), server);
	parseSlashCommand(slashcommand, slashCommand);
	return 1;
}

int CommandConfigManager::addRegainConsciousnessCommand(lua_State* L) {
	LuaObject slashcommand(L);
	if (!slashcommand.isValidTable())
		return 0;

	RegainConsciousnessCommand* slashCommand = new RegainConsciousnessCommand(slashcommand.getStringField("name"), server);
	parseSlashCommand(slashcommand, slashCommand);
	return 1;
}

int CommandConfigManager::addRegenerationCommand(lua_State* L) {
	LuaObject slashcommand(L);
	if (!slashcommand.isValidTable())
		return 0;

	RegenerationCommand* slashCommand = new RegenerationCommand(slashcommand.getStringField("name"), server);
	parseSlashCommand(slashcommand, slashCommand);
	return 1;
}

int CommandConfigManager::addRegisterWithLocationCommand(lua_State* L) {
	LuaObject slashcommand(L);
	if (!slashcommand.isValidTable())
		return 0;

	RegisterWithLocationCommand* slashCommand = new RegisterWithLocationCommand(slashcommand.getStringField("name"), server);
	parseSlashCommand(slashcommand, slashCommand);
	return 1;
}

int CommandConfigManager::addReloadCommand(lua_State* L) {
	LuaObject slashcommand(L);
	if (!slashcommand.isValidTable())
		return 0;

	ReloadCommand* slashCommand = new ReloadCommand(slashcommand.getStringField("name"), server);
	parseSlashCommand(slashcommand, slashCommand);
	return 1;
}

int CommandConfigManager::addRemoteCommand(lua_State* L) {
	LuaObject slashcommand(L);
	if (!slashcommand.isValidTable())
		return 0;

	RemoteCommand* slashCommand = new RemoteCommand(slashcommand.getStringField("name"), server);
	parseSlashCommand(slashcommand, slashCommand);
	return 1;
}

int CommandConfigManager::addRemoveAllowedPlayerCommand(lua_State* L) {
	LuaObject slashcommand(L);
	if (!slashcommand.isValidTable())
		return 0;

	RemoveAllowedPlayerCommand* slashCommand = new RemoveAllowedPlayerCommand(slashcommand.getStringField("name"), server);
	parseSlashCommand(slashcommand, slashCommand);
	return 1;
}

int CommandConfigManager::addRemoveBannedPlayerCommand(lua_State* L) {
	LuaObject slashcommand(L);
	if (!slashcommand.isValidTable())
		return 0;

	RemoveBannedPlayerCommand* slashCommand = new RemoveBannedPlayerCommand(slashcommand.getStringField("name"), server);
	parseSlashCommand(slashcommand, slashCommand);
	return 1;
}

int CommandConfigManager::addRemoveFriendCommand(lua_State* L) {
	LuaObject slashcommand(L);
	if (!slashcommand.isValidTable())
		return 0;

	RemoveFriendCommand* slashCommand = new RemoveFriendCommand(slashcommand.getStringField("name"), server);
	parseSlashCommand(slashcommand, slashCommand);
	return 1;
}

int CommandConfigManager::addRemoveIgnoreCommand(lua_State* L) {
	LuaObject slashcommand(L);
	if (!slashcommand.isValidTable())
		return 0;

	RemoveIgnoreCommand* slashCommand = new RemoveIgnoreCommand(slashcommand.getStringField("name"), server);
	parseSlashCommand(slashcommand, slashCommand);
	return 1;
}

int CommandConfigManager::addRepairBattlefieldStructureCommand(lua_State* L) {
	LuaObject slashcommand(L);
	if (!slashcommand.isValidTable())
		return 0;

	RepairBattlefieldStructureCommand* slashCommand = new RepairBattlefieldStructureCommand(slashcommand.getStringField("name"), server);
	parseSlashCommand(slashcommand, slashCommand);
	return 1;
}

int CommandConfigManager::addRepairShipComponentInSlotCommand(lua_State* L) {
	LuaObject slashcommand(L);
	if (!slashcommand.isValidTable())
		return 0;

	RepairShipComponentInSlotCommand* slashCommand = new RepairShipComponentInSlotCommand(slashcommand.getStringField("name"), server);
	parseSlashCommand(slashcommand, slashCommand);
	return 1;
}

int CommandConfigManager::addReportCommand(lua_State* L) {
	LuaObject slashcommand(L);
	if (!slashcommand.isValidTable())
		return 0;

	ReportCommand* slashCommand = new ReportCommand(slashcommand.getStringField("name"), server);
	parseSlashCommand(slashcommand, slashCommand);
	return 1;
}

int CommandConfigManager::addRequestBadgesCommand(lua_State* L) {
	LuaObject slashcommand(L);
	if (!slashcommand.isValidTable())
		return 0;

	RequestBadgesCommand* slashCommand = new RequestBadgesCommand(slashcommand.getStringField("name"), server);
	parseSlashCommand(slashcommand, slashCommand);
	return 1;
}

int CommandConfigManager::addRequestBiographyCommand(lua_State* L) {
	LuaObject slashcommand(L);
	if (!slashcommand.isValidTable())
		return 0;

	RequestBiographyCommand* slashCommand = new RequestBiographyCommand(slashcommand.getStringField("name"), server);
	parseSlashCommand(slashcommand, slashCommand);
	return 1;
}

int CommandConfigManager::addRequestCharacterMatchCommand(lua_State* L) {
	LuaObject slashcommand(L);
	if (!slashcommand.isValidTable())
		return 0;

	RequestCharacterMatchCommand* slashCommand = new RequestCharacterMatchCommand(slashcommand.getStringField("name"), server);
	parseSlashCommand(slashcommand, slashCommand);
	return 1;
}

int CommandConfigManager::addRequestCharacterSheetInfoCommand(lua_State* L) {
	LuaObject slashcommand(L);
	if (!slashcommand.isValidTable())
		return 0;

	RequestCharacterSheetInfoCommand* slashCommand = new RequestCharacterSheetInfoCommand(slashcommand.getStringField("name"), server);
	parseSlashCommand(slashcommand, slashCommand);
	return 1;
}

int CommandConfigManager::addRequestCoreSampleCommand(lua_State* L) {
	LuaObject slashcommand(L);
	if (!slashcommand.isValidTable())
		return 0;

	RequestCoreSampleCommand* slashCommand = new RequestCoreSampleCommand(slashcommand.getStringField("name"), server);
	parseSlashCommand(slashcommand, slashCommand);
	return 1;
}

int CommandConfigManager::addRequestCraftingSessionCommand(lua_State* L) {
	LuaObject slashcommand(L);
	if (!slashcommand.isValidTable())
		return 0;

	RequestCraftingSessionCommand* slashCommand = new RequestCraftingSessionCommand(slashcommand.getStringField("name"), server);
	parseSlashCommand(slashcommand, slashCommand);
	return 1;
}

int CommandConfigManager::addRequestDraftSlotsCommand(lua_State* L) {
	LuaObject slashcommand(L);
	if (!slashcommand.isValidTable())
		return 0;

	RequestDraftSlotsCommand* slashCommand = new RequestDraftSlotsCommand(slashcommand.getStringField("name"), server);
	parseSlashCommand(slashcommand, slashCommand);
	return 1;
}

int CommandConfigManager::addRequestDraftSlotsBatchCommand(lua_State* L) {
	LuaObject slashcommand(L);
	if (!slashcommand.isValidTable())
		return 0;

	RequestDraftSlotsBatchCommand* slashCommand = new RequestDraftSlotsBatchCommand(slashcommand.getStringField("name"), server);
	parseSlashCommand(slashcommand, slashCommand);
	return 1;
}

int CommandConfigManager::addRequestManfSchematicSlotsCommand(lua_State* L) {
	LuaObject slashcommand(L);
	if (!slashcommand.isValidTable())
		return 0;

	RequestManfSchematicSlotsCommand* slashCommand = new RequestManfSchematicSlotsCommand(slashcommand.getStringField("name"), server);
	parseSlashCommand(slashcommand, slashCommand);
	return 1;
}

int CommandConfigManager::addRequestResourceWeightsCommand(lua_State* L) {
	LuaObject slashcommand(L);
	if (!slashcommand.isValidTable())
		return 0;

	RequestResourceWeightsCommand* slashCommand = new RequestResourceWeightsCommand(slashcommand.getStringField("name"), server);
	parseSlashCommand(slashcommand, slashCommand);
	return 1;
}

int CommandConfigManager::addRequestResourceWeightsBatchCommand(lua_State* L) {
	LuaObject slashcommand(L);
	if (!slashcommand.isValidTable())
		return 0;

	RequestResourceWeightsBatchCommand* slashCommand = new RequestResourceWeightsBatchCommand(slashcommand.getStringField("name"), server);
	parseSlashCommand(slashcommand, slashCommand);
	return 1;
}

int CommandConfigManager::addRequestSetStatMigrationDataCommand(lua_State* L) {
	LuaObject slashcommand(L);
	if (!slashcommand.isValidTable())
		return 0;

	RequestSetStatMigrationDataCommand* slashCommand = new RequestSetStatMigrationDataCommand(slashcommand.getStringField("name"), server);
	parseSlashCommand(slashcommand, slashCommand);
	return 1;
}

int CommandConfigManager::addRequestStatMigrationDataCommand(lua_State* L) {
	LuaObject slashcommand(L);
	if (!slashcommand.isValidTable())
		return 0;

	RequestStatMigrationDataCommand* slashCommand = new RequestStatMigrationDataCommand(slashcommand.getStringField("name"), server);
	parseSlashCommand(slashcommand, slashCommand);
	return 1;
}

int CommandConfigManager::addRequestStatMigrationStartCommand(lua_State* L) {
	LuaObject slashcommand(L);
	if (!slashcommand.isValidTable())
		return 0;

	RequestStatMigrationStartCommand* slashCommand = new RequestStatMigrationStartCommand(slashcommand.getStringField("name"), server);
	parseSlashCommand(slashcommand, slashCommand);
	return 1;
}

int CommandConfigManager::addRequestStatMigrationStopCommand(lua_State* L) {
	LuaObject slashcommand(L);
	if (!slashcommand.isValidTable())
		return 0;

	RequestStatMigrationStopCommand* slashCommand = new RequestStatMigrationStopCommand(slashcommand.getStringField("name"), server);
	parseSlashCommand(slashcommand, slashCommand);
	return 1;
}

int CommandConfigManager::addRequestStimpackCommand(lua_State* L) {
	LuaObject slashcommand(L);
	if (!slashcommand.isValidTable())
		return 0;

	RequestStimpackCommand* slashCommand = new RequestStimpackCommand(slashcommand.getStringField("name"), server);
	parseSlashCommand(slashcommand, slashCommand);
	return 1;
}

int CommandConfigManager::addRequestSurveyCommand(lua_State* L) {
	LuaObject slashcommand(L);
	if (!slashcommand.isValidTable())
		return 0;

	RequestSurveyCommand* slashCommand = new RequestSurveyCommand(slashcommand.getStringField("name"), server);
	parseSlashCommand(slashcommand, slashCommand);
	return 1;
}

int CommandConfigManager::addRequestWaypointAtPositionCommand(lua_State* L) {
	LuaObject slashcommand(L);
	if (!slashcommand.isValidTable())
		return 0;

	RequestWaypointAtPositionCommand* slashCommand = new RequestWaypointAtPositionCommand(slashcommand.getStringField("name"), server);
	parseSlashCommand(slashcommand, slashCommand);
	return 1;
}

int CommandConfigManager::addRescueCommand(lua_State* L) {
	LuaObject slashcommand(L);
	if (!slashcommand.isValidTable())
		return 0;

	RescueCommand* slashCommand = new RescueCommand(slashcommand.getStringField("name"), server);
	parseSlashCommand(slashcommand, slashCommand);
	return 1;
}

int CommandConfigManager::addResendLoginMessageToAllCommand(lua_State* L) {
	LuaObject slashcommand(L);
	if (!slashcommand.isValidTable())
		return 0;

	ResendLoginMessageToAllCommand* slashCommand = new ResendLoginMessageToAllCommand(slashcommand.getStringField("name"), server);
	parseSlashCommand(slashcommand, slashCommand);
	return 1;
}

int CommandConfigManager::addResetJediCommand(lua_State* L) {
	LuaObject slashcommand(L);
	if (!slashcommand.isValidTable())
		return 0;

	ResetJediCommand* slashCommand = new ResetJediCommand(slashcommand.getStringField("name"), server);
	parseSlashCommand(slashcommand, slashCommand);
	return 1;
}

int CommandConfigManager::addResourceCommand(lua_State* L) {
	LuaObject slashcommand(L);
	if (!slashcommand.isValidTable())
		return 0;

	ResourceCommand* slashCommand = new ResourceCommand(slashcommand.getStringField("name"), server);
	parseSlashCommand(slashcommand, slashCommand);
	return 1;
}

int CommandConfigManager::addResourceContainerSplitCommand(lua_State* L) {
	LuaObject slashcommand(L);
	if (!slashcommand.isValidTable())
		return 0;

	ResourceContainerSplitCommand* slashCommand = new ResourceContainerSplitCommand(slashcommand.getStringField("name"), server);
	parseSlashCommand(slashcommand, slashCommand);
	return 1;
}

int CommandConfigManager::addResourceContainerTransferCommand(lua_State* L) {
	LuaObject slashcommand(L);
	if (!slashcommand.isValidTable())
		return 0;

	ResourceContainerTransferCommand* slashCommand = new ResourceContainerTransferCommand(slashcommand.getStringField("name"), server);
	parseSlashCommand(slashcommand, slashCommand);
	return 1;
}

int CommandConfigManager::addResourceSetNameCommand(lua_State* L) {
	LuaObject slashcommand(L);
	if (!slashcommand.isValidTable())
		return 0;

	ResourceSetNameCommand* slashCommand = new ResourceSetNameCommand(slashcommand.getStringField("name"), server);
	parseSlashCommand(slashcommand, slashCommand);
	return 1;
}

int CommandConfigManager::addResSampleLoopCommand(lua_State* L) {
	LuaObject slashcommand(L);
	if (!slashcommand.isValidTable())
		return 0;

	ResSampleLoopCommand* slashCommand = new ResSampleLoopCommand(slashcommand.getStringField("name"), server);
	parseSlashCommand(slashcommand, slashCommand);
	return 1;
}

int CommandConfigManager::addRestartConversionCommand(lua_State* L) {
	LuaObject slashcommand(L);
	if (!slashcommand.isValidTable())
		return 0;

	RestartConversionCommand* slashCommand = new RestartConversionCommand(slashcommand.getStringField("name"), server);
	parseSlashCommand(slashcommand, slashCommand);
	return 1;
}

int CommandConfigManager::addRestartCraftingSessionCommand(lua_State* L) {
	LuaObject slashcommand(L);
	if (!slashcommand.isValidTable())
		return 0;

	RestartCraftingSessionCommand* slashCommand = new RestartCraftingSessionCommand(slashcommand.getStringField("name"), server);
	parseSlashCommand(slashcommand, slashCommand);
	return 1;
}

int CommandConfigManager::addRetreatCommand(lua_State* L) {
	LuaObject slashcommand(L);
	if (!slashcommand.isValidTable())
		return 0;

	RetreatCommand* slashCommand = new RetreatCommand(slashcommand.getStringField("name"), server);
	parseSlashCommand(slashcommand, slashCommand);
	return 1;
}

int CommandConfigManager::addRevivePlayerCommand(lua_State* L) {
	LuaObject slashcommand(L);
	if (!slashcommand.isValidTable())
		return 0;

	RevivePlayerCommand* slashCommand = new RevivePlayerCommand(slashcommand.getStringField("name"), server);
	parseSlashCommand(slashcommand, slashCommand);
	return 1;
}

int CommandConfigManager::addRevokeBadgeCommand(lua_State* L) {
	LuaObject slashcommand(L);
	if (!slashcommand.isValidTable())
		return 0;

	RevokeBadgeCommand* slashCommand = new RevokeBadgeCommand(slashcommand.getStringField("name"), server);
	parseSlashCommand(slashcommand, slashCommand);
	return 1;
}

int CommandConfigManager::addRevokeSkillCommand(lua_State* L) {
	LuaObject slashcommand(L);
	if (!slashcommand.isValidTable())
		return 0;

	RevokeSkillCommand* slashCommand = new RevokeSkillCommand(slashcommand.getStringField("name"), server);
	parseSlashCommand(slashcommand, slashCommand);
	return 1;
}

int CommandConfigManager::addRolePlayCommand(lua_State* L) {
	LuaObject slashcommand(L);
	if (!slashcommand.isValidTable())
		return 0;

	RolePlayCommand* slashCommand = new RolePlayCommand(slashcommand.getStringField("name"), server);
	parseSlashCommand(slashcommand, slashCommand);
	return 1;
}

int CommandConfigManager::addRollShotCommand(lua_State* L) {
	LuaObject slashcommand(L);
	if (!slashcommand.isValidTable())
		return 0;

	RollShotCommand* slashCommand = new RollShotCommand(slashcommand.getStringField("name"), server);
	parseSlashCommand(slashcommand, slashCommand);
	return 1;
}

int CommandConfigManager::addRotateFurnitureCommand(lua_State* L) {
	LuaObject slashcommand(L);
	if (!slashcommand.isValidTable())
		return 0;

	RotateFurnitureCommand* slashCommand = new RotateFurnitureCommand(slashcommand.getStringField("name"), server);
	parseSlashCommand(slashcommand, slashCommand);
	return 1;
}

int CommandConfigManager::addSaber1hComboHit1Command(lua_State* L) {
	LuaObject slashcommand(L);
	if (!slashcommand.isValidTable())
		return 0;

	Saber1hComboHit1Command* slashCommand = new Saber1hComboHit1Command(slashcommand.getStringField("name"), server);
	parseSlashCommand(slashcommand, slashCommand);
	return 1;
}

int CommandConfigManager::addSaber1hComboHit2Command(lua_State* L) {
	LuaObject slashcommand(L);
	if (!slashcommand.isValidTable())
		return 0;

	Saber1hComboHit2Command* slashCommand = new Saber1hComboHit2Command(slashcommand.getStringField("name"), server);
	parseSlashCommand(slashcommand, slashCommand);
	return 1;
}

int CommandConfigManager::addSaber1hComboHit3Command(lua_State* L) {
	LuaObject slashcommand(L);
	if (!slashcommand.isValidTable())
		return 0;

	Saber1hComboHit3Command* slashCommand = new Saber1hComboHit3Command(slashcommand.getStringField("name"), server);
	parseSlashCommand(slashcommand, slashCommand);
	return 1;
}

int CommandConfigManager::addSaber1hFlurryCommand(lua_State* L) {
	LuaObject slashcommand(L);
	if (!slashcommand.isValidTable())
		return 0;

	Saber1hFlurryCommand* slashCommand = new Saber1hFlurryCommand(slashcommand.getStringField("name"), server);
	parseSlashCommand(slashcommand, slashCommand);
	return 1;
}

int CommandConfigManager::addSaber1hFlurry2Command(lua_State* L) {
	LuaObject slashcommand(L);
	if (!slashcommand.isValidTable())
		return 0;

	Saber1hFlurry2Command* slashCommand = new Saber1hFlurry2Command(slashcommand.getStringField("name"), server);
	parseSlashCommand(slashcommand, slashCommand);
	return 1;
}

int CommandConfigManager::addSaber1hHeadHit1Command(lua_State* L) {
	LuaObject slashcommand(L);
	if (!slashcommand.isValidTable())
		return 0;

	Saber1hHeadHit1Command* slashCommand = new Saber1hHeadHit1Command(slashcommand.getStringField("name"), server);
	parseSlashCommand(slashcommand, slashCommand);
	return 1;
}

int CommandConfigManager::addSaber1hHeadHit2Command(lua_State* L) {
	LuaObject slashcommand(L);
	if (!slashcommand.isValidTable())
		return 0;

	Saber1hHeadHit2Command* slashCommand = new Saber1hHeadHit2Command(slashcommand.getStringField("name"), server);
	parseSlashCommand(slashcommand, slashCommand);
	return 1;
}

int CommandConfigManager::addSaber1hHeadHit3Command(lua_State* L) {
	LuaObject slashcommand(L);
	if (!slashcommand.isValidTable())
		return 0;

	Saber1hHeadHit3Command* slashCommand = new Saber1hHeadHit3Command(slashcommand.getStringField("name"), server);
	parseSlashCommand(slashcommand, slashCommand);
	return 1;
}

int CommandConfigManager::addSaber1hHit1Command(lua_State* L) {
	LuaObject slashcommand(L);
	if (!slashcommand.isValidTable())
		return 0;

	Saber1hHit1Command* slashCommand = new Saber1hHit1Command(slashcommand.getStringField("name"), server);
	parseSlashCommand(slashcommand, slashCommand);
	return 1;
}

int CommandConfigManager::addSaber1hHit2Command(lua_State* L) {
	LuaObject slashcommand(L);
	if (!slashcommand.isValidTable())
		return 0;

	Saber1hHit2Command* slashCommand = new Saber1hHit2Command(slashcommand.getStringField("name"), server);
	parseSlashCommand(slashcommand, slashCommand);
	return 1;
}

int CommandConfigManager::addSaber1hHit3Command(lua_State* L) {
	LuaObject slashcommand(L);
	if (!slashcommand.isValidTable())
		return 0;

	Saber1hHit3Command* slashCommand = new Saber1hHit3Command(slashcommand.getStringField("name"), server);
	parseSlashCommand(slashcommand, slashCommand);
	return 1;
}

int CommandConfigManager::addSaber2hBodyHit1Command(lua_State* L) {
	LuaObject slashcommand(L);
	if (!slashcommand.isValidTable())
		return 0;

	Saber2hBodyHit1Command* slashCommand = new Saber2hBodyHit1Command(slashcommand.getStringField("name"), server);
	parseSlashCommand(slashcommand, slashCommand);
	return 1;
}

int CommandConfigManager::addSaber2hBodyHit2Command(lua_State* L) {
	LuaObject slashcommand(L);
	if (!slashcommand.isValidTable())
		return 0;

	Saber2hBodyHit2Command* slashCommand = new Saber2hBodyHit2Command(slashcommand.getStringField("name"), server);
	parseSlashCommand(slashcommand, slashCommand);
	return 1;
}

int CommandConfigManager::addSaber2hBodyHit3Command(lua_State* L) {
	LuaObject slashcommand(L);
	if (!slashcommand.isValidTable())
		return 0;

	Saber2hBodyHit3Command* slashCommand = new Saber2hBodyHit3Command(slashcommand.getStringField("name"), server);
	parseSlashCommand(slashcommand, slashCommand);
	return 1;
}

int CommandConfigManager::addSaber2hFrenzyCommand(lua_State* L) {
	LuaObject slashcommand(L);
	if (!slashcommand.isValidTable())
		return 0;

	Saber2hFrenzyCommand* slashCommand = new Saber2hFrenzyCommand(slashcommand.getStringField("name"), server);
	parseSlashCommand(slashcommand, slashCommand);
	return 1;
}

int CommandConfigManager::addSaber2hHit1Command(lua_State* L) {
	LuaObject slashcommand(L);
	if (!slashcommand.isValidTable())
		return 0;

	Saber2hHit1Command* slashCommand = new Saber2hHit1Command(slashcommand.getStringField("name"), server);
	parseSlashCommand(slashcommand, slashCommand);
	return 1;
}

int CommandConfigManager::addSaber2hHit2Command(lua_State* L) {
	LuaObject slashcommand(L);
	if (!slashcommand.isValidTable())
		return 0;

	Saber2hHit2Command* slashCommand = new Saber2hHit2Command(slashcommand.getStringField("name"), server);
	parseSlashCommand(slashcommand, slashCommand);
	return 1;
}

int CommandConfigManager::addSaber2hHit3Command(lua_State* L) {
	LuaObject slashcommand(L);
	if (!slashcommand.isValidTable())
		return 0;

	Saber2hHit3Command* slashCommand = new Saber2hHit3Command(slashcommand.getStringField("name"), server);
	parseSlashCommand(slashcommand, slashCommand);
	return 1;
}

int CommandConfigManager::addSaber2hPhantomCommand(lua_State* L) {
	LuaObject slashcommand(L);
	if (!slashcommand.isValidTable())
		return 0;

	Saber2hPhantomCommand* slashCommand = new Saber2hPhantomCommand(slashcommand.getStringField("name"), server);
	parseSlashCommand(slashcommand, slashCommand);
	return 1;
}

int CommandConfigManager::addSaber2hSweep1Command(lua_State* L) {
	LuaObject slashcommand(L);
	if (!slashcommand.isValidTable())
		return 0;

	Saber2hSweep1Command* slashCommand = new Saber2hSweep1Command(slashcommand.getStringField("name"), server);
	parseSlashCommand(slashcommand, slashCommand);
	return 1;
}

int CommandConfigManager::addSaber2hSweep2Command(lua_State* L) {
	LuaObject slashcommand(L);
	if (!slashcommand.isValidTable())
		return 0;

	Saber2hSweep2Command* slashCommand = new Saber2hSweep2Command(slashcommand.getStringField("name"), server);
	parseSlashCommand(slashcommand, slashCommand);
	return 1;
}

int CommandConfigManager::addSaber2hSweep3Command(lua_State* L) {
	LuaObject slashcommand(L);
	if (!slashcommand.isValidTable())
		return 0;

	Saber2hSweep3Command* slashCommand = new Saber2hSweep3Command(slashcommand.getStringField("name"), server);
	parseSlashCommand(slashcommand, slashCommand);
	return 1;
}

int CommandConfigManager::addSaberPolearmDervishCommand(lua_State* L) {
	LuaObject slashcommand(L);
	if (!slashcommand.isValidTable())
		return 0;

	SaberPolearmDervishCommand* slashCommand = new SaberPolearmDervishCommand(slashcommand.getStringField("name"), server);
	parseSlashCommand(slashcommand, slashCommand);
	return 1;
}

int CommandConfigManager::addSaberPolearmDervish2Command(lua_State* L) {
	LuaObject slashcommand(L);
	if (!slashcommand.isValidTable())
		return 0;

	SaberPolearmDervish2Command* slashCommand = new SaberPolearmDervish2Command(slashcommand.getStringField("name"), server);
	parseSlashCommand(slashcommand, slashCommand);
	return 1;
}

int CommandConfigManager::addSaberPolearmHit1Command(lua_State* L) {
	LuaObject slashcommand(L);
	if (!slashcommand.isValidTable())
		return 0;

	SaberPolearmHit1Command* slashCommand = new SaberPolearmHit1Command(slashcommand.getStringField("name"), server);
	parseSlashCommand(slashcommand, slashCommand);
	return 1;
}

int CommandConfigManager::addSaberPolearmHit2Command(lua_State* L) {
	LuaObject slashcommand(L);
	if (!slashcommand.isValidTable())
		return 0;

	SaberPolearmHit2Command* slashCommand = new SaberPolearmHit2Command(slashcommand.getStringField("name"), server);
	parseSlashCommand(slashcommand, slashCommand);
	return 1;
}

int CommandConfigManager::addSaberPolearmHit3Command(lua_State* L) {
	LuaObject slashcommand(L);
	if (!slashcommand.isValidTable())
		return 0;

	SaberPolearmHit3Command* slashCommand = new SaberPolearmHit3Command(slashcommand.getStringField("name"), server);
	parseSlashCommand(slashcommand, slashCommand);
	return 1;
}

int CommandConfigManager::addSaberPolearmLegHit1Command(lua_State* L) {
	LuaObject slashcommand(L);
	if (!slashcommand.isValidTable())
		return 0;

	SaberPolearmLegHit1Command* slashCommand = new SaberPolearmLegHit1Command(slashcommand.getStringField("name"), server);
	parseSlashCommand(slashcommand, slashCommand);
	return 1;
}

int CommandConfigManager::addSaberPolearmLegHit2Command(lua_State* L) {
	LuaObject slashcommand(L);
	if (!slashcommand.isValidTable())
		return 0;

	SaberPolearmLegHit2Command* slashCommand = new SaberPolearmLegHit2Command(slashcommand.getStringField("name"), server);
	parseSlashCommand(slashcommand, slashCommand);
	return 1;
}

int CommandConfigManager::addSaberPolearmLegHit3Command(lua_State* L) {
	LuaObject slashcommand(L);
	if (!slashcommand.isValidTable())
		return 0;

	SaberPolearmLegHit3Command* slashCommand = new SaberPolearmLegHit3Command(slashcommand.getStringField("name"), server);
	parseSlashCommand(slashcommand, slashCommand);
	return 1;
}

int CommandConfigManager::addSaberPolearmSpinAttack1Command(lua_State* L) {
	LuaObject slashcommand(L);
	if (!slashcommand.isValidTable())
		return 0;

	SaberPolearmSpinAttack1Command* slashCommand = new SaberPolearmSpinAttack1Command(slashcommand.getStringField("name"), server);
	parseSlashCommand(slashcommand, slashCommand);
	return 1;
}

int CommandConfigManager::addSaberPolearmSpinAttack2Command(lua_State* L) {
	LuaObject slashcommand(L);
	if (!slashcommand.isValidTable())
		return 0;

	SaberPolearmSpinAttack2Command* slashCommand = new SaberPolearmSpinAttack2Command(slashcommand.getStringField("name"), server);
	parseSlashCommand(slashcommand, slashCommand);
	return 1;
}

int CommandConfigManager::addSaberPolearmSpinAttack3Command(lua_State* L) {
	LuaObject slashcommand(L);
	if (!slashcommand.isValidTable())
		return 0;

	SaberPolearmSpinAttack3Command* slashCommand = new SaberPolearmSpinAttack3Command(slashcommand.getStringField("name"), server);
	parseSlashCommand(slashcommand, slashCommand);
	return 1;
}

int CommandConfigManager::addSaberSlash1Command(lua_State* L) {
	LuaObject slashcommand(L);
	if (!slashcommand.isValidTable())
		return 0;

	SaberSlash1Command* slashCommand = new SaberSlash1Command(slashcommand.getStringField("name"), server);
	parseSlashCommand(slashcommand, slashCommand);
	return 1;
}

int CommandConfigManager::addSaberSlash2Command(lua_State* L) {
	LuaObject slashcommand(L);
	if (!slashcommand.isValidTable())
		return 0;

	SaberSlash2Command* slashCommand = new SaberSlash2Command(slashcommand.getStringField("name"), server);
	parseSlashCommand(slashcommand, slashCommand);
	return 1;
}

int CommandConfigManager::addSaberThrow1Command(lua_State* L) {
	LuaObject slashcommand(L);
	if (!slashcommand.isValidTable())
		return 0;

	SaberThrow1Command* slashCommand = new SaberThrow1Command(slashcommand.getStringField("name"), server);
	parseSlashCommand(slashcommand, slashCommand);
	return 1;
}

int CommandConfigManager::addSaberThrow2Command(lua_State* L) {
	LuaObject slashcommand(L);
	if (!slashcommand.isValidTable())
		return 0;

	SaberThrow2Command* slashCommand = new SaberThrow2Command(slashcommand.getStringField("name"), server);
	parseSlashCommand(slashcommand, slashCommand);
	return 1;
}

int CommandConfigManager::addSaberThrow3Command(lua_State* L) {
	LuaObject slashcommand(L);
	if (!slashcommand.isValidTable())
		return 0;

	SaberThrow3Command* slashCommand = new SaberThrow3Command(slashcommand.getStringField("name"), server);
	parseSlashCommand(slashcommand, slashCommand);
	return 1;
}

int CommandConfigManager::addSampleCommand(lua_State* L) {
	LuaObject slashcommand(L);
	if (!slashcommand.isValidTable())
		return 0;

	SampleCommand* slashCommand = new SampleCommand(slashcommand.getStringField("name"), server);
	parseSlashCommand(slashcommand, slashCommand);
	return 1;
}

int CommandConfigManager::addSampleDNACommand(lua_State* L) {
	LuaObject slashcommand(L);
	if (!slashcommand.isValidTable())
		return 0;

	SampleDNACommand* slashCommand = new SampleDNACommand(slashcommand.getStringField("name"), server);
	parseSlashCommand(slashcommand, slashCommand);
	return 1;
}

int CommandConfigManager::addScatterShot1Command(lua_State* L) {
	LuaObject slashcommand(L);
	if (!slashcommand.isValidTable())
		return 0;

	ScatterShot1Command* slashCommand = new ScatterShot1Command(slashcommand.getStringField("name"), server);
	parseSlashCommand(slashcommand, slashCommand);
	return 1;
}

int CommandConfigManager::addScatterShot2Command(lua_State* L) {
	LuaObject slashcommand(L);
	if (!slashcommand.isValidTable())
		return 0;

	ScatterShot2Command* slashCommand = new ScatterShot2Command(slashcommand.getStringField("name"), server);
	parseSlashCommand(slashcommand, slashCommand);
	return 1;
}

int CommandConfigManager::addScriptCommand(lua_State* L) {
	LuaObject slashcommand(L);
	if (!slashcommand.isValidTable())
		return 0;

	ScriptCommand* slashCommand = new ScriptCommand(slashcommand.getStringField("name"), server);
	parseSlashCommand(slashcommand, slashCommand);
	return 1;
}

int CommandConfigManager::addSearchCorpseCommand(lua_State* L) {
	LuaObject slashcommand(L);
	if (!slashcommand.isValidTable())
		return 0;

	SearchCorpseCommand* slashCommand = new SearchCorpseCommand(slashcommand.getStringField("name"), server);
	parseSlashCommand(slashcommand, slashCommand);
	return 1;
}

int CommandConfigManager::addSecretSpawnSpamCommand(lua_State* L) {
	LuaObject slashcommand(L);
	if (!slashcommand.isValidTable())
		return 0;

	SecretSpawnSpamCommand* slashCommand = new SecretSpawnSpamCommand(slashcommand.getStringField("name"), server);
	parseSlashCommand(slashcommand, slashCommand);
	return 1;
}

int CommandConfigManager::addSeGogglesCommand(lua_State* L) {
	LuaObject slashcommand(L);
	if (!slashcommand.isValidTable())
		return 0;

	SeGogglesCommand* slashCommand = new SeGogglesCommand(slashcommand.getStringField("name"), server);
	parseSlashCommand(slashcommand, slashCommand);
	return 1;
}

int CommandConfigManager::addSelectDraftSchematicCommand(lua_State* L) {
	LuaObject slashcommand(L);
	if (!slashcommand.isValidTable())
		return 0;

	SelectDraftSchematicCommand* slashCommand = new SelectDraftSchematicCommand(slashcommand.getStringField("name"), server);
	parseSlashCommand(slashcommand, slashCommand);
	return 1;
}

int CommandConfigManager::addServerCommand(lua_State* L) {
	LuaObject slashcommand(L);
	if (!slashcommand.isValidTable())
		return 0;

	ServerCommand* slashCommand = new ServerCommand(slashcommand.getStringField("name"), server);
	parseSlashCommand(slashcommand, slashCommand);
	return 1;
}

int CommandConfigManager::addServerDestroyObjectCommand(lua_State* L) {
	LuaObject slashcommand(L);
	if (!slashcommand.isValidTable())
		return 0;

	ServerDestroyObjectCommand* slashCommand = new ServerDestroyObjectCommand(slashcommand.getStringField("name"), server);
	parseSlashCommand(slashcommand, slashCommand);
	return 1;
}

int CommandConfigManager::addServerSysGroupCommand(lua_State* L) {
	LuaObject slashcommand(L);
	if (!slashcommand.isValidTable())
		return 0;

	ServerSysGroupCommand* slashCommand = new ServerSysGroupCommand(slashcommand.getStringField("name"), server);
	parseSlashCommand(slashcommand, slashCommand);
	return 1;
}

int CommandConfigManager::addSetBiographyAdminCommand(lua_State* L) {
	LuaObject slashcommand(L);
	if (!slashcommand.isValidTable())
		return 0;

	SetBiographyAdminCommand* slashCommand = new SetBiographyAdminCommand(slashcommand.getStringField("name"), server);
	parseSlashCommand(slashcommand, slashCommand);
	return 1;
}

int CommandConfigManager::addSetBiographyCommand(lua_State* L) {
	LuaObject slashcommand(L);
	if (!slashcommand.isValidTable())
		return 0;

	SetBiographyCommand* slashCommand = new SetBiographyCommand(slashcommand.getStringField("name"), server);
	parseSlashCommand(slashcommand, slashCommand);
	return 1;
}

int CommandConfigManager::addSetBoostmoraleCommand(lua_State* L) {
	LuaObject slashcommand(L);
	if (!slashcommand.isValidTable())
		return 0;

	SetBoostmoraleCommand* slashCommand = new SetBoostmoraleCommand(slashcommand.getStringField("name"), server);
	parseSlashCommand(slashcommand, slashCommand);
	return 1;
}

int CommandConfigManager::addSetChargeCommand(lua_State* L) {
	LuaObject slashcommand(L);
	if (!slashcommand.isValidTable())
		return 0;

	SetChargeCommand* slashCommand = new SetChargeCommand(slashcommand.getStringField("name"), server);
	parseSlashCommand(slashcommand, slashCommand);
	return 1;
}

int CommandConfigManager::addSetCurrentSkillTitleCommand(lua_State* L) {
	LuaObject slashcommand(L);
	if (!slashcommand.isValidTable())
		return 0;

	SetCurrentSkillTitleCommand* slashCommand = new SetCurrentSkillTitleCommand(slashcommand.getStringField("name"), server);
	parseSlashCommand(slashcommand, slashCommand);
	return 1;
}

int CommandConfigManager::addSetExperienceCommand(lua_State* L) {
	LuaObject slashcommand(L);
	if (!slashcommand.isValidTable())
		return 0;

	SetExperienceCommand* slashCommand = new SetExperienceCommand(slashcommand.getStringField("name"), server);
	parseSlashCommand(slashcommand, slashCommand);
	return 1;
}

int CommandConfigManager::addSetFactionCommand(lua_State* L) {
	LuaObject slashcommand(L);
	if (!slashcommand.isValidTable())
		return 0;

	SetFactionCommand* slashCommand = new SetFactionCommand(slashcommand.getStringField("name"), server);
	parseSlashCommand(slashcommand, slashCommand);
	return 1;
}

int CommandConfigManager::addSetFactionStandingCommand(lua_State* L) {
	LuaObject slashcommand(L);
	if (!slashcommand.isValidTable())
		return 0;

	SetFactionStandingCommand* slashCommand = new SetFactionStandingCommand(slashcommand.getStringField("name"), server);
	parseSlashCommand(slashcommand, slashCommand);
	return 1;
}

int CommandConfigManager::addSetFirstNameCommand(lua_State* L) {
	LuaObject slashcommand(L);
	if (!slashcommand.isValidTable())
		return 0;

	SetFirstNameCommand* slashCommand = new SetFirstNameCommand(slashcommand.getStringField("name"), server);
	parseSlashCommand(slashcommand, slashCommand);
	return 1;
}

int CommandConfigManager::addSetFormupCommand(lua_State* L) {
	LuaObject slashcommand(L);
	if (!slashcommand.isValidTable())
		return 0;

	SetFormupCommand* slashCommand = new SetFormupCommand(slashcommand.getStringField("name"), server);
	parseSlashCommand(slashcommand, slashCommand);
	return 1;
}

int CommandConfigManager::addSetGodModeCommand(lua_State* L) {
	LuaObject slashcommand(L);
	if (!slashcommand.isValidTable())
		return 0;

	SetGodModeCommand* slashCommand = new SetGodModeCommand(slashcommand.getStringField("name"), server);
	parseSlashCommand(slashcommand, slashCommand);
	return 1;
}

int CommandConfigManager::addSetHueCommand(lua_State* L) {
	LuaObject slashcommand(L);
	if (!slashcommand.isValidTable())
		return 0;

	SetHueCommand* slashCommand = new SetHueCommand(slashcommand.getStringField("name"), server);
	parseSlashCommand(slashcommand, slashCommand);
	return 1;
}

int CommandConfigManager::addSetIntimidateCommand(lua_State* L) {
	LuaObject slashcommand(L);
	if (!slashcommand.isValidTable())
		return 0;

	SetIntimidateCommand* slashCommand = new SetIntimidateCommand(slashcommand.getStringField("name"), server);
	parseSlashCommand(slashcommand, slashCommand);
	return 1;
}

int CommandConfigManager::addSetLastNameCommand(lua_State* L) {
	LuaObject slashcommand(L);
	if (!slashcommand.isValidTable())
		return 0;

	SetLastNameCommand* slashCommand = new SetLastNameCommand(slashcommand.getStringField("name"), server);
	parseSlashCommand(slashcommand, slashCommand);
	return 1;
}

int CommandConfigManager::addSetLoginMessageCommand(lua_State* L) {
	LuaObject slashcommand(L);
	if (!slashcommand.isValidTable())
		return 0;

	SetLoginMessageCommand* slashCommand = new SetLoginMessageCommand(slashcommand.getStringField("name"), server);
	parseSlashCommand(slashcommand, slashCommand);
	return 1;
}

int CommandConfigManager::addSetLoginTitleCommand(lua_State* L) {
	LuaObject slashcommand(L);
	if (!slashcommand.isValidTable())
		return 0;

	SetLoginTitleCommand* slashCommand = new SetLoginTitleCommand(slashcommand.getStringField("name"), server);
	parseSlashCommand(slashcommand, slashCommand);
	return 1;
}

int CommandConfigManager::addSetMatchMakingCharacterIdCommand(lua_State* L) {
	LuaObject slashcommand(L);
	if (!slashcommand.isValidTable())
		return 0;

	SetMatchMakingCharacterIdCommand* slashCommand = new SetMatchMakingCharacterIdCommand(slashcommand.getStringField("name"), server);
	parseSlashCommand(slashcommand, slashCommand);
	return 1;
}

int CommandConfigManager::addSetMatchMakingPersonalIdCommand(lua_State* L) {
	LuaObject slashcommand(L);
	if (!slashcommand.isValidTable())
		return 0;

	SetMatchMakingPersonalIdCommand* slashCommand = new SetMatchMakingPersonalIdCommand(slashcommand.getStringField("name"), server);
	parseSlashCommand(slashcommand, slashCommand);
	return 1;
}

int CommandConfigManager::addSetMaximumSpawnTimeCommand(lua_State* L) {
	LuaObject slashcommand(L);
	if (!slashcommand.isValidTable())
		return 0;

	SetMaximumSpawnTimeCommand* slashCommand = new SetMaximumSpawnTimeCommand(slashcommand.getStringField("name"), server);
	parseSlashCommand(slashcommand, slashCommand);
	return 1;
}

int CommandConfigManager::addSetMinimumSpawnTimeCommand(lua_State* L) {
	LuaObject slashcommand(L);
	if (!slashcommand.isValidTable())
		return 0;

	SetMinimumSpawnTimeCommand* slashCommand = new SetMinimumSpawnTimeCommand(slashcommand.getStringField("name"), server);
	parseSlashCommand(slashcommand, slashCommand);
	return 1;
}

int CommandConfigManager::addSetMoodCommand(lua_State* L) {
	LuaObject slashcommand(L);
	if (!slashcommand.isValidTable())
		return 0;

	SetMoodCommand* slashCommand = new SetMoodCommand(slashcommand.getStringField("name"), server);
	parseSlashCommand(slashcommand, slashCommand);
	return 1;
}

int CommandConfigManager::addSetMoodInternalCommand(lua_State* L) {
	LuaObject slashcommand(L);
	if (!slashcommand.isValidTable())
		return 0;

	SetMoodInternalCommand* slashCommand = new SetMoodInternalCommand(slashcommand.getStringField("name"), server);
	parseSlashCommand(slashcommand, slashCommand);
	return 1;
}

int CommandConfigManager::addSetNameCommand(lua_State* L) {
	LuaObject slashcommand(L);
	if (!slashcommand.isValidTable())
		return 0;

	SetNameCommand* slashCommand = new SetNameCommand(slashcommand.getStringField("name"), server);
	parseSlashCommand(slashcommand, slashCommand);
	return 1;
}

int CommandConfigManager::addSetOwnerCommand(lua_State* L) {
	LuaObject slashcommand(L);
	if (!slashcommand.isValidTable())
		return 0;

	SetOwnerCommand* slashCommand = new SetOwnerCommand(slashcommand.getStringField("name"), server);
	parseSlashCommand(slashcommand, slashCommand);
	return 1;
}

int CommandConfigManager::addSetPerformanceBuffTargetCommand(lua_State* L) {
	LuaObject slashcommand(L);
	if (!slashcommand.isValidTable())
		return 0;

	SetPerformanceBuffTargetCommand* slashCommand = new SetPerformanceBuffTargetCommand(slashcommand.getStringField("name"), server);
	parseSlashCommand(slashcommand, slashCommand);
	return 1;
}

int CommandConfigManager::addSetpermissionCommand(lua_State* L) {
	LuaObject slashcommand(L);
	if (!slashcommand.isValidTable())
		return 0;

	SetpermissionCommand* slashCommand = new SetpermissionCommand(slashcommand.getStringField("name"), server);
	parseSlashCommand(slashcommand, slashCommand);
	return 1;
}

int CommandConfigManager::addSetPlanetLimitCommand(lua_State* L) {
	LuaObject slashcommand(L);
	if (!slashcommand.isValidTable())
		return 0;

	SetPlanetLimitCommand* slashCommand = new SetPlanetLimitCommand(slashcommand.getStringField("name"), server);
	parseSlashCommand(slashcommand, slashCommand);
	return 1;
}

int CommandConfigManager::addSetPlayerAppearanceCommand(lua_State* L) {
	LuaObject slashcommand(L);
	if (!slashcommand.isValidTable())
		return 0;

	SetPlayerAppearanceCommand* slashCommand = new SetPlayerAppearanceCommand(slashcommand.getStringField("name"), server);
	parseSlashCommand(slashcommand, slashCommand);
	return 1;
}

int CommandConfigManager::addSetPlayerStateCommand(lua_State* L) {
	LuaObject slashcommand(L);
	if (!slashcommand.isValidTable())
		return 0;

	SetPlayerStateCommand* slashCommand = new SetPlayerStateCommand(slashcommand.getStringField("name"), server);
	parseSlashCommand(slashcommand, slashCommand);
	return 1;
}

int CommandConfigManager::addSetprivacyCommand(lua_State* L) {
	LuaObject slashcommand(L);
	if (!slashcommand.isValidTable())
		return 0;

	SetprivacyCommand* slashCommand = new SetprivacyCommand(slashcommand.getStringField("name"), server);
	parseSlashCommand(slashcommand, slashCommand);
	return 1;
}

int CommandConfigManager::addSetPublicStateCommand(lua_State* L) {
	LuaObject slashcommand(L);
	if (!slashcommand.isValidTable())
		return 0;

	SetPublicStateCommand* slashCommand = new SetPublicStateCommand(slashcommand.getStringField("name"), server);
	parseSlashCommand(slashcommand, slashCommand);
	return 1;
}

int CommandConfigManager::addSetRankCommand(lua_State* L) {
	LuaObject slashcommand(L);
	if (!slashcommand.isValidTable())
		return 0;

	SetRankCommand* slashCommand = new SetRankCommand(slashcommand.getStringField("name"), server);
	parseSlashCommand(slashcommand, slashCommand);
	return 1;
}

int CommandConfigManager::addSetRetreatCommand(lua_State* L) {
	LuaObject slashcommand(L);
	if (!slashcommand.isValidTable())
		return 0;

	SetRetreatCommand* slashCommand = new SetRetreatCommand(slashcommand.getStringField("name"), server);
	parseSlashCommand(slashcommand, slashCommand);
	return 1;
}

int CommandConfigManager::addSetSpeedCommand(lua_State* L) {
	LuaObject slashcommand(L);
	if (!slashcommand.isValidTable())
		return 0;

	SetSpeedCommand* slashCommand = new SetSpeedCommand(slashcommand.getStringField("name"), server);
	parseSlashCommand(slashcommand, slashCommand);
	return 1;
}

int CommandConfigManager::addSetSpokenLanguageCommand(lua_State* L) {
	LuaObject slashcommand(L);
	if (!slashcommand.isValidTable())
		return 0;

	SetSpokenLanguageCommand* slashCommand = new SetSpokenLanguageCommand(slashcommand.getStringField("name"), server);
	parseSlashCommand(slashcommand, slashCommand);
	return 1;
}

int CommandConfigManager::addSetSteadyaimCommand(lua_State* L) {
	LuaObject slashcommand(L);
	if (!slashcommand.isValidTable())
		return 0;

	SetSteadyaimCommand* slashCommand = new SetSteadyaimCommand(slashcommand.getStringField("name"), server);
	parseSlashCommand(slashcommand, slashCommand);
	return 1;
}

int CommandConfigManager::addSetTEFCommand(lua_State* L) {
	LuaObject slashcommand(L);
	if (!slashcommand.isValidTable())
		return 0;

	SetTEFCommand* slashCommand = new SetTEFCommand(slashcommand.getStringField("name"), server);
	parseSlashCommand(slashcommand, slashCommand);
	return 1;
}

int CommandConfigManager::addSetVeteranRewardCommand(lua_State* L) {
	LuaObject slashcommand(L);
	if (!slashcommand.isValidTable())
		return 0;

	SetVeteranRewardCommand* slashCommand = new SetVeteranRewardCommand(slashcommand.getStringField("name"), server);
	parseSlashCommand(slashcommand, slashCommand);
	return 1;
}

int CommandConfigManager::addSetWarcryCommand(lua_State* L) {
	LuaObject slashcommand(L);
	if (!slashcommand.isValidTable())
		return 0;

	SetWarcryCommand* slashCommand = new SetWarcryCommand(slashcommand.getStringField("name"), server);
	parseSlashCommand(slashcommand, slashCommand);
	return 1;
}

int CommandConfigManager::addSetWaypointActiveStatusCommand(lua_State* L) {
	LuaObject slashcommand(L);
	if (!slashcommand.isValidTable())
		return 0;

	SetWaypointActiveStatusCommand* slashCommand = new SetWaypointActiveStatusCommand(slashcommand.getStringField("name"), server);
	parseSlashCommand(slashcommand, slashCommand);
	return 1;
}

int CommandConfigManager::addSetWaypointNameCommand(lua_State* L) {
	LuaObject slashcommand(L);
	if (!slashcommand.isValidTable())
		return 0;

	SetWaypointNameCommand* slashCommand = new SetWaypointNameCommand(slashcommand.getStringField("name"), server);
	parseSlashCommand(slashcommand, slashCommand);
	return 1;
}

int CommandConfigManager::addShowCouncilRankCommand(lua_State* L) {
	LuaObject slashcommand(L);
	if (!slashcommand.isValidTable())
		return 0;

	ShowCouncilRankCommand* slashCommand = new ShowCouncilRankCommand(slashcommand.getStringField("name"), server);
	parseSlashCommand(slashcommand, slashCommand);
	return 1;
}

int CommandConfigManager::addShowDanceVisualsCommand(lua_State* L) {
	LuaObject slashcommand(L);
	if (!slashcommand.isValidTable())
		return 0;

	ShowDanceVisualsCommand* slashCommand = new ShowDanceVisualsCommand(slashcommand.getStringField("name"), server);
	parseSlashCommand(slashcommand, slashCommand);
	return 1;
}

int CommandConfigManager::addShowFactionInformationCommand(lua_State* L) {
	LuaObject slashcommand(L);
	if (!slashcommand.isValidTable())
		return 0;

	ShowFactionInformationCommand* slashCommand = new ShowFactionInformationCommand(slashcommand.getStringField("name"), server);
	parseSlashCommand(slashcommand, slashCommand);
	return 1;
}

int CommandConfigManager::addShowMusicianVisualsCommand(lua_State* L) {
	LuaObject slashcommand(L);
	if (!slashcommand.isValidTable())
		return 0;

	ShowMusicianVisualsCommand* slashCommand = new ShowMusicianVisualsCommand(slashcommand.getStringField("name"), server);
	parseSlashCommand(slashcommand, slashCommand);
	return 1;
}

int CommandConfigManager::addShowPvPRatingCommand(lua_State* L) {
	LuaObject slashcommand(L);
	if (!slashcommand.isValidTable())
		return 0;

	ShowPvPRatingCommand* slashCommand = new ShowPvPRatingCommand(slashcommand.getStringField("name"), server);
	parseSlashCommand(slashcommand, slashCommand);
	return 1;
}

int CommandConfigManager::addShowSpawnRegionCommand(lua_State* L) {
	LuaObject slashcommand(L);
	if (!slashcommand.isValidTable())
		return 0;

	ShowSpawnRegionCommand* slashCommand = new ShowSpawnRegionCommand(slashcommand.getStringField("name"), server);
	parseSlashCommand(slashcommand, slashCommand);
	return 1;
}

int CommandConfigManager::addSitServerCommand(lua_State* L) {
	LuaObject slashcommand(L);
	if (!slashcommand.isValidTable())
		return 0;

	SitServerCommand* slashCommand = new SitServerCommand(slashcommand.getStringField("name"), server);
	parseSlashCommand(slashcommand, slashCommand);
	return 1;
}

int CommandConfigManager::addSkillCommand(lua_State* L) {
	LuaObject slashcommand(L);
	if (!slashcommand.isValidTable())
		return 0;

	SkillCommand* slashCommand = new SkillCommand(slashcommand.getStringField("name"), server);
	parseSlashCommand(slashcommand, slashCommand);
	return 1;
}

int CommandConfigManager::addSmokebombCommand(lua_State* L) {
	LuaObject slashcommand(L);
	if (!slashcommand.isValidTable())
		return 0;

	SmokebombCommand* slashCommand = new SmokebombCommand(slashcommand.getStringField("name"), server);
	parseSlashCommand(slashcommand, slashCommand);
	return 1;
}

int CommandConfigManager::addSniperShotCommand(lua_State* L) {
	LuaObject slashcommand(L);
	if (!slashcommand.isValidTable())
		return 0;

	SniperShotCommand* slashCommand = new SniperShotCommand(slashcommand.getStringField("name"), server);
	parseSlashCommand(slashcommand, slashCommand);
	return 1;
}

int CommandConfigManager::addSnoopCommand(lua_State* L) {
	LuaObject slashcommand(L);
	if (!slashcommand.isValidTable())
		return 0;

	SnoopCommand* slashCommand = new SnoopCommand(slashcommand.getStringField("name"), server);
	parseSlashCommand(slashcommand, slashCommand);
	return 1;
}

int CommandConfigManager::addSocialCommand(lua_State* L) {
	LuaObject slashcommand(L);
	if (!slashcommand.isValidTable())
		return 0;

	SocialCommand* slashCommand = new SocialCommand(slashcommand.getStringField("name"), server);
	parseSlashCommand(slashcommand, slashCommand);
	return 1;
}

int CommandConfigManager::addSocialInternalCommand(lua_State* L) {
	LuaObject slashcommand(L);
	if (!slashcommand.isValidTable())
		return 0;

	SocialInternalCommand* slashCommand = new SocialInternalCommand(slashcommand.getStringField("name"), server);
	parseSlashCommand(slashcommand, slashCommand);
	return 1;
}

int CommandConfigManager::addSpatialChatCommand(lua_State* L) {
	LuaObject slashcommand(L);
	if (!slashcommand.isValidTable())
		return 0;

	SpatialChatCommand* slashCommand = new SpatialChatCommand(slashcommand.getStringField("name"), server);
	parseSlashCommand(slashcommand, slashCommand);
	return 1;
}

int CommandConfigManager::addSpatialChatInternalCommand(lua_State* L) {
	LuaObject slashcommand(L);
	if (!slashcommand.isValidTable())
		return 0;

	SpatialChatInternalCommand* slashCommand = new SpatialChatInternalCommand(slashcommand.getStringField("name"), server);
	parseSlashCommand(slashcommand, slashCommand);
	return 1;
}

int CommandConfigManager::addSpawnStatusCommand(lua_State* L) {
	LuaObject slashcommand(L);
	if (!slashcommand.isValidTable())
		return 0;

	SpawnStatusCommand* slashCommand = new SpawnStatusCommand(slashcommand.getStringField("name"), server);
	parseSlashCommand(slashcommand, slashCommand);
	return 1;
}

int CommandConfigManager::addSplitCreditsWithGroupCommand(lua_State* L) {
	LuaObject slashcommand(L);
	if (!slashcommand.isValidTable())
		return 0;

	SplitCreditsWithGroupCommand* slashCommand = new SplitCreditsWithGroupCommand(slashcommand.getStringField("name"), server);
	parseSlashCommand(slashcommand, slashCommand);
	return 1;
}

int CommandConfigManager::addSpotlightCommand(lua_State* L) {
	LuaObject slashcommand(L);
	if (!slashcommand.isValidTable())
		return 0;

	SpotlightCommand* slashCommand = new SpotlightCommand(slashcommand.getStringField("name"), server);
	parseSlashCommand(slashcommand, slashCommand);
	return 1;
}

int CommandConfigManager::addSprayShotCommand(lua_State* L) {
	LuaObject slashcommand(L);
	if (!slashcommand.isValidTable())
		return 0;

	SprayShotCommand* slashCommand = new SprayShotCommand(slashcommand.getStringField("name"), server);
	parseSlashCommand(slashcommand, slashCommand);
	return 1;
}

int CommandConfigManager::addStandCommand(lua_State* L) {
	LuaObject slashcommand(L);
	if (!slashcommand.isValidTable())
		return 0;

	StandCommand* slashCommand = new StandCommand(slashcommand.getStringField("name"), server);
	parseSlashCommand(slashcommand, slashCommand);
	return 1;
}

int CommandConfigManager::addStartBandCommand(lua_State* L) {
	LuaObject slashcommand(L);
	if (!slashcommand.isValidTable())
		return 0;

	StartBandCommand* slashCommand = new StartBandCommand(slashcommand.getStringField("name"), server);
	parseSlashCommand(slashcommand, slashCommand);
	return 1;
}

int CommandConfigManager::addStartCitySpawnerCommand(lua_State* L) {
	LuaObject slashcommand(L);
	if (!slashcommand.isValidTable())
		return 0;

	StartCitySpawnerCommand* slashCommand = new StartCitySpawnerCommand(slashcommand.getStringField("name"), server);
	parseSlashCommand(slashcommand, slashCommand);
	return 1;
}

int CommandConfigManager::addStartDanceCommand(lua_State* L) {
	LuaObject slashcommand(L);
	if (!slashcommand.isValidTable())
		return 0;

	StartDanceCommand* slashCommand = new StartDanceCommand(slashcommand.getStringField("name"), server);
	parseSlashCommand(slashcommand, slashCommand);
	return 1;
}

int CommandConfigManager::addStartleShot1Command(lua_State* L) {
	LuaObject slashcommand(L);
	if (!slashcommand.isValidTable())
		return 0;

	StartleShot1Command* slashCommand = new StartleShot1Command(slashcommand.getStringField("name"), server);
	parseSlashCommand(slashcommand, slashCommand);
	return 1;
}

int CommandConfigManager::addStartleShot2Command(lua_State* L) {
	LuaObject slashcommand(L);
	if (!slashcommand.isValidTable())
		return 0;

	StartleShot2Command* slashCommand = new StartleShot2Command(slashcommand.getStringField("name"), server);
	parseSlashCommand(slashcommand, slashCommand);
	return 1;
}

int CommandConfigManager::addStartMusicCommand(lua_State* L) {
	LuaObject slashcommand(L);
	if (!slashcommand.isValidTable())
		return 0;

	StartMusicCommand* slashCommand = new StartMusicCommand(slashcommand.getStringField("name"), server);
	parseSlashCommand(slashcommand, slashCommand);
	return 1;
}

int CommandConfigManager::addStartSpawnerCommand(lua_State* L) {
	LuaObject slashcommand(L);
	if (!slashcommand.isValidTable())
		return 0;

	StartSpawnerCommand* slashCommand = new StartSpawnerCommand(slashcommand.getStringField("name"), server);
	parseSlashCommand(slashcommand, slashCommand);
	return 1;
}

int CommandConfigManager::addStartTargetSpawnerCommand(lua_State* L) {
	LuaObject slashcommand(L);
	if (!slashcommand.isValidTable())
		return 0;

	StartTargetSpawnerCommand* slashCommand = new StartTargetSpawnerCommand(slashcommand.getStringField("name"), server);
	parseSlashCommand(slashcommand, slashCommand);
	return 1;
}

int CommandConfigManager::addStartTraceLoggingCommand(lua_State* L) {
	LuaObject slashcommand(L);
	if (!slashcommand.isValidTable())
		return 0;

	StartTraceLoggingCommand* slashCommand = new StartTraceLoggingCommand(slashcommand.getStringField("name"), server);
	parseSlashCommand(slashcommand, slashCommand);
	return 1;
}

int CommandConfigManager::addStatCommand(lua_State* L) {
	LuaObject slashcommand(L);
	if (!slashcommand.isValidTable())
		return 0;

	StatCommand* slashCommand = new StatCommand(slashcommand.getStringField("name"), server);
	parseSlashCommand(slashcommand, slashCommand);
	return 1;
}

int CommandConfigManager::addSteadyaimCommand(lua_State* L) {
	LuaObject slashcommand(L);
	if (!slashcommand.isValidTable())
		return 0;

	SteadyaimCommand* slashCommand = new SteadyaimCommand(slashcommand.getStringField("name"), server);
	parseSlashCommand(slashcommand, slashCommand);
	return 1;
}

int CommandConfigManager::addStopBandCommand(lua_State* L) {
	LuaObject slashcommand(L);
	if (!slashcommand.isValidTable())
		return 0;

	StopBandCommand* slashCommand = new StopBandCommand(slashcommand.getStringField("name"), server);
	parseSlashCommand(slashcommand, slashCommand);
	return 1;
}

int CommandConfigManager::addStopBleedingCommand(lua_State* L) {
	LuaObject slashcommand(L);
	if (!slashcommand.isValidTable())
		return 0;

	StopBleedingCommand* slashCommand = new StopBleedingCommand(slashcommand.getStringField("name"), server);
	parseSlashCommand(slashcommand, slashCommand);
	return 1;
}

int CommandConfigManager::addStopCitySpawnerCommand(lua_State* L) {
	LuaObject slashcommand(L);
	if (!slashcommand.isValidTable())
		return 0;

	StopCitySpawnerCommand* slashCommand = new StopCitySpawnerCommand(slashcommand.getStringField("name"), server);
	parseSlashCommand(slashcommand, slashCommand);
	return 1;
}

int CommandConfigManager::addStopCraftingSessionCommand(lua_State* L) {
	LuaObject slashcommand(L);
	if (!slashcommand.isValidTable())
		return 0;

	StopCraftingSessionCommand* slashCommand = new StopCraftingSessionCommand(slashcommand.getStringField("name"), server);
	parseSlashCommand(slashcommand, slashCommand);
	return 1;
}

int CommandConfigManager::addStopDanceCommand(lua_State* L) {
	LuaObject slashcommand(L);
	if (!slashcommand.isValidTable())
		return 0;

	StopDanceCommand* slashCommand = new StopDanceCommand(slashcommand.getStringField("name"), server);
	parseSlashCommand(slashcommand, slashCommand);
	return 1;
}

int CommandConfigManager::addStoplisteningCommand(lua_State* L) {
	LuaObject slashcommand(L);
	if (!slashcommand.isValidTable())
		return 0;

	StoplisteningCommand* slashCommand = new StoplisteningCommand(slashcommand.getStringField("name"), server);
	parseSlashCommand(slashcommand, slashCommand);
	return 1;
}

int CommandConfigManager::addStopMusicCommand(lua_State* L) {
	LuaObject slashcommand(L);
	if (!slashcommand.isValidTable())
		return 0;

	StopMusicCommand* slashCommand = new StopMusicCommand(slashcommand.getStringField("name"), server);
	parseSlashCommand(slashcommand, slashCommand);
	return 1;
}

int CommandConfigManager::addStoppingShotCommand(lua_State* L) {
	LuaObject slashcommand(L);
	if (!slashcommand.isValidTable())
		return 0;

	StoppingShotCommand* slashCommand = new StoppingShotCommand(slashcommand.getStringField("name"), server);
	parseSlashCommand(slashcommand, slashCommand);
	return 1;
}

int CommandConfigManager::addStopSpawnerCommand(lua_State* L) {
	LuaObject slashcommand(L);
	if (!slashcommand.isValidTable())
		return 0;

	StopSpawnerCommand* slashCommand = new StopSpawnerCommand(slashcommand.getStringField("name"), server);
	parseSlashCommand(slashcommand, slashCommand);
	return 1;
}

int CommandConfigManager::addStopTargetSpawnerCommand(lua_State* L) {
	LuaObject slashcommand(L);
	if (!slashcommand.isValidTable())
		return 0;

	StopTargetSpawnerCommand* slashCommand = new StopTargetSpawnerCommand(slashcommand.getStringField("name"), server);
	parseSlashCommand(slashcommand, slashCommand);
	return 1;
}

int CommandConfigManager::addStopTraceLoggingCommand(lua_State* L) {
	LuaObject slashcommand(L);
	if (!slashcommand.isValidTable())
		return 0;

	StopTraceLoggingCommand* slashCommand = new StopTraceLoggingCommand(slashcommand.getStringField("name"), server);
	parseSlashCommand(slashcommand, slashCommand);
	return 1;
}

int CommandConfigManager::addStopwatchingCommand(lua_State* L) {
	LuaObject slashcommand(L);
	if (!slashcommand.isValidTable())
		return 0;

	StopwatchingCommand* slashCommand = new StopwatchingCommand(slashcommand.getStringField("name"), server);
	parseSlashCommand(slashcommand, slashCommand);
	return 1;
}

int CommandConfigManager::addStrafeShot1Command(lua_State* L) {
	LuaObject slashcommand(L);
	if (!slashcommand.isValidTable())
		return 0;

	StrafeShot1Command* slashCommand = new StrafeShot1Command(slashcommand.getStringField("name"), server);
	parseSlashCommand(slashcommand, slashCommand);
	return 1;
}

int CommandConfigManager::addStrafeShot2Command(lua_State* L) {
	LuaObject slashcommand(L);
	if (!slashcommand.isValidTable())
		return 0;

	StrafeShot2Command* slashCommand = new StrafeShot2Command(slashcommand.getStringField("name"), server);
	parseSlashCommand(slashcommand, slashCommand);
	return 1;
}

int CommandConfigManager::addStrongDiseaseCommand(lua_State* L) {
	LuaObject slashcommand(L);
	if (!slashcommand.isValidTable())
		return 0;

	StrongDiseaseCommand* slashCommand = new StrongDiseaseCommand(slashcommand.getStringField("name"), server);
	parseSlashCommand(slashcommand, slashCommand);
	return 1;
}

int CommandConfigManager::addStrongPoisonCommand(lua_State* L) {
	LuaObject slashcommand(L);
	if (!slashcommand.isValidTable())
		return 0;

	StrongPoisonCommand* slashCommand = new StrongPoisonCommand(slashcommand.getStringField("name"), server);
	parseSlashCommand(slashcommand, slashCommand);
	return 1;
}

int CommandConfigManager::addStructurestatusCommand(lua_State* L) {
	LuaObject slashcommand(L);
	if (!slashcommand.isValidTable())
		return 0;

	StructurestatusCommand* slashCommand = new StructurestatusCommand(slashcommand.getStringField("name"), server);
	parseSlashCommand(slashcommand, slashCommand);
	return 1;
}

int CommandConfigManager::addStunAttackCommand(lua_State* L) {
	LuaObject slashcommand(L);
	if (!slashcommand.isValidTable())
		return 0;

	StunAttackCommand* slashCommand = new StunAttackCommand(slashcommand.getStringField("name"), server);
	parseSlashCommand(slashcommand, slashCommand);
	return 1;
}

int CommandConfigManager::addSuppressionFire1Command(lua_State* L) {
	LuaObject slashcommand(L);
	if (!slashcommand.isValidTable())
		return 0;

	SuppressionFire1Command* slashCommand = new SuppressionFire1Command(slashcommand.getStringField("name"), server);
	parseSlashCommand(slashcommand, slashCommand);
	return 1;
}

int CommandConfigManager::addSuppressionFire2Command(lua_State* L) {
	LuaObject slashcommand(L);
	if (!slashcommand.isValidTable())
		return 0;

	SuppressionFire2Command* slashCommand = new SuppressionFire2Command(slashcommand.getStringField("name"), server);
	parseSlashCommand(slashcommand, slashCommand);
	return 1;
}

int CommandConfigManager::addSurpriseShotCommand(lua_State* L) {
	LuaObject slashcommand(L);
	if (!slashcommand.isValidTable())
		return 0;

	SurpriseShotCommand* slashCommand = new SurpriseShotCommand(slashcommand.getStringField("name"), server);
	parseSlashCommand(slashcommand, slashCommand);
	return 1;
}

int CommandConfigManager::addSurrenderSkillCommand(lua_State* L) {
	LuaObject slashcommand(L);
	if (!slashcommand.isValidTable())
		return 0;

	SurrenderSkillCommand* slashCommand = new SurrenderSkillCommand(slashcommand.getStringField("name"), server);
	parseSlashCommand(slashcommand, slashCommand);
	return 1;
}

int CommandConfigManager::addSurveyCommand(lua_State* L) {
	LuaObject slashcommand(L);
	if (!slashcommand.isValidTable())
		return 0;

	SurveyCommand* slashCommand = new SurveyCommand(slashcommand.getStringField("name"), server);
	parseSlashCommand(slashcommand, slashCommand);
	return 1;
}

int CommandConfigManager::addSynchronizedUiListenCommand(lua_State* L) {
	LuaObject slashcommand(L);
	if (!slashcommand.isValidTable())
		return 0;

	SynchronizedUiListenCommand* slashCommand = new SynchronizedUiListenCommand(slashcommand.getStringField("name"), server);
	parseSlashCommand(slashcommand, slashCommand);
	return 1;
}

int CommandConfigManager::addSynchronizedUiStopListeningCommand(lua_State* L) {
	LuaObject slashcommand(L);
	if (!slashcommand.isValidTable())
		return 0;

	SynchronizedUiStopListeningCommand* slashCommand = new SynchronizedUiStopListeningCommand(slashcommand.getStringField("name"), server);
	parseSlashCommand(slashcommand, slashCommand);
	return 1;
}

int CommandConfigManager::addSystemMessageCommand(lua_State* L) {
	LuaObject slashcommand(L);
	if (!slashcommand.isValidTable())
		return 0;

	SystemMessageCommand* slashCommand = new SystemMessageCommand(slashcommand.getStringField("name"), server);
	parseSlashCommand(slashcommand, slashCommand);
	return 1;
}

int CommandConfigManager::addTakeCoverCommand(lua_State* L) {
	LuaObject slashcommand(L);
	if (!slashcommand.isValidTable())
		return 0;

	TakeCoverCommand* slashCommand = new TakeCoverCommand(slashcommand.getStringField("name"), server);
	parseSlashCommand(slashcommand, slashCommand);
	return 1;
}

int CommandConfigManager::addTameCommand(lua_State* L) {
	LuaObject slashcommand(L);
	if (!slashcommand.isValidTable())
		return 0;

	TameCommand* slashCommand = new TameCommand(slashcommand.getStringField("name"), server);
	parseSlashCommand(slashcommand, slashCommand);
	return 1;
}

int CommandConfigManager::addTargetCommand(lua_State* L) {
	LuaObject slashcommand(L);
	if (!slashcommand.isValidTable())
		return 0;

	TargetCommand* slashCommand = new TargetCommand(slashcommand.getStringField("name"), server);
	parseSlashCommand(slashcommand, slashCommand);
	return 1;
}

int CommandConfigManager::addTauntCommand(lua_State* L) {
	LuaObject slashcommand(L);
	if (!slashcommand.isValidTable())
		return 0;

	TauntCommand* slashCommand = new TauntCommand(slashcommand.getStringField("name"), server);
	parseSlashCommand(slashcommand, slashCommand);
	return 1;
}

int CommandConfigManager::addTeachCommand(lua_State* L) {
	LuaObject slashcommand(L);
	if (!slashcommand.isValidTable())
		return 0;

	TeachCommand* slashCommand = new TeachCommand(slashcommand.getStringField("name"), server);
	parseSlashCommand(slashcommand, slashCommand);
	return 1;
}

int CommandConfigManager::addTeleportCommand(lua_State* L) {
	LuaObject slashcommand(L);
	if (!slashcommand.isValidTable())
		return 0;

	TeleportCommand* slashCommand = new TeleportCommand(slashcommand.getStringField("name"), server);
	parseSlashCommand(slashcommand, slashCommand);
	return 1;
}

int CommandConfigManager::addTeleportTargetCommand(lua_State* L) {
	LuaObject slashcommand(L);
	if (!slashcommand.isValidTable())
		return 0;

	TeleportTargetCommand* slashCommand = new TeleportTargetCommand(slashcommand.getStringField("name"), server);
	parseSlashCommand(slashcommand, slashCommand);
	return 1;
}

int CommandConfigManager::addTeleportToCommand(lua_State* L) {
	LuaObject slashcommand(L);
	if (!slashcommand.isValidTable())
		return 0;

	TeleportToCommand* slashCommand = new TeleportToCommand(slashcommand.getStringField("name"), server);
	parseSlashCommand(slashcommand, slashCommand);
	return 1;
}

int CommandConfigManager::addTellpetCommand(lua_State* L) {
	LuaObject slashcommand(L);
	if (!slashcommand.isValidTable())
		return 0;

	TellpetCommand* slashCommand = new TellpetCommand(slashcommand.getStringField("name"), server);
	parseSlashCommand(slashcommand, slashCommand);
	return 1;
}

int CommandConfigManager::addTendDamageCommand(lua_State* L) {
	LuaObject slashcommand(L);
	if (!slashcommand.isValidTable())
		return 0;

	TendDamageCommand* slashCommand = new TendDamageCommand(slashcommand.getStringField("name"), server);
	parseSlashCommand(slashcommand, slashCommand);
	return 1;
}

int CommandConfigManager::addTendDamageToolCommand(lua_State* L) {
	LuaObject slashcommand(L);
	if (!slashcommand.isValidTable())
		return 0;

	TendDamageToolCommand* slashCommand = new TendDamageToolCommand(slashcommand.getStringField("name"), server);
	parseSlashCommand(slashcommand, slashCommand);
	return 1;
}

int CommandConfigManager::addTendWoundCommand(lua_State* L) {
	LuaObject slashcommand(L);
	if (!slashcommand.isValidTable())
		return 0;

	TendWoundCommand* slashCommand = new TendWoundCommand(slashcommand.getStringField("name"), server);
	parseSlashCommand(slashcommand, slashCommand);
	return 1;
}

int CommandConfigManager::addTendWoundsToolCommand(lua_State* L) {
	LuaObject slashcommand(L);
	if (!slashcommand.isValidTable())
		return 0;

	TendWoundsToolCommand* slashCommand = new TendWoundsToolCommand(slashcommand.getStringField("name"), server);
	parseSlashCommand(slashcommand, slashCommand);
	return 1;
}

int CommandConfigManager::addThreatenShotCommand(lua_State* L) {
	LuaObject slashcommand(L);
	if (!slashcommand.isValidTable())
		return 0;

	ThreatenShotCommand* slashCommand = new ThreatenShotCommand(slashcommand.getStringField("name"), server);
	parseSlashCommand(slashcommand, slashCommand);
	return 1;
}

int CommandConfigManager::addThrowGrenadeCommand(lua_State* L) {
	LuaObject slashcommand(L);
	if (!slashcommand.isValidTable())
		return 0;

	ThrowGrenadeCommand* slashCommand = new ThrowGrenadeCommand(slashcommand.getStringField("name"), server);
	parseSlashCommand(slashcommand, slashCommand);
	return 1;
}

int CommandConfigManager::addThrowTrapCommand(lua_State* L) {
	LuaObject slashcommand(L);
	if (!slashcommand.isValidTable())
		return 0;

	ThrowTrapCommand* slashCommand = new ThrowTrapCommand(slashcommand.getStringField("name"), server);
	parseSlashCommand(slashcommand, slashCommand);
	return 1;
}

int CommandConfigManager::addTipCommand(lua_State* L) {
	LuaObject slashcommand(L);
	if (!slashcommand.isValidTable())
		return 0;

	TipCommand* slashCommand = new TipCommand(slashcommand.getStringField("name"), server);
	parseSlashCommand(slashcommand, slashCommand);
	return 1;
}

int CommandConfigManager::addToggleAwayFromKeyBoardCommand(lua_State* L) {
	LuaObject slashcommand(L);
	if (!slashcommand.isValidTable())
		return 0;

	ToggleAwayFromKeyBoardCommand* slashCommand = new ToggleAwayFromKeyBoardCommand(slashcommand.getStringField("name"), server);
	parseSlashCommand(slashcommand, slashCommand);
	return 1;
}

int CommandConfigManager::addToggleDisplayingFactionRankCommand(lua_State* L) {
	LuaObject slashcommand(L);
	if (!slashcommand.isValidTable())
		return 0;

	ToggleDisplayingFactionRankCommand* slashCommand = new ToggleDisplayingFactionRankCommand(slashcommand.getStringField("name"), server);
	parseSlashCommand(slashcommand, slashCommand);
	return 1;
}

int CommandConfigManager::addTorsoShotCommand(lua_State* L) {
	LuaObject slashcommand(L);
	if (!slashcommand.isValidTable())
		return 0;

	TorsoShotCommand* slashCommand = new TorsoShotCommand(slashcommand.getStringField("name"), server);
	parseSlashCommand(slashcommand, slashCommand);
	return 1;
}

int CommandConfigManager::addTotalHealOtherCommand(lua_State* L) {
	LuaObject slashcommand(L);
	if (!slashcommand.isValidTable())
		return 0;

	TotalHealOtherCommand* slashCommand = new TotalHealOtherCommand(slashcommand.getStringField("name"), server);
	parseSlashCommand(slashcommand, slashCommand);
	return 1;
}

int CommandConfigManager::addTotalHealSelfCommand(lua_State* L) {
	LuaObject slashcommand(L);
	if (!slashcommand.isValidTable())
		return 0;

	TotalHealSelfCommand* slashCommand = new TotalHealSelfCommand(slashcommand.getStringField("name"), server);
	parseSlashCommand(slashcommand, slashCommand);
	return 1;
}

int CommandConfigManager::addTransferForceCommand(lua_State* L) {
	LuaObject slashcommand(L);
	if (!slashcommand.isValidTable())
		return 0;

	TransferForceCommand* slashCommand = new TransferForceCommand(slashcommand.getStringField("name"), server);
	parseSlashCommand(slashcommand, slashCommand);
	return 1;
}

int CommandConfigManager::addTransferItemCommand(lua_State* L) {
	LuaObject slashcommand(L);
	if (!slashcommand.isValidTable())
		return 0;

	TransferItemCommand* slashCommand = new TransferItemCommand(slashcommand.getStringField("name"), server);
	parseSlashCommand(slashcommand, slashCommand);
	return 1;
}

int CommandConfigManager::addTransferItemArmorCommand(lua_State* L) {
	LuaObject slashcommand(L);
	if (!slashcommand.isValidTable())
		return 0;

	TransferItemArmorCommand* slashCommand = new TransferItemArmorCommand(slashcommand.getStringField("name"), server);
	parseSlashCommand(slashcommand, slashCommand);
	return 1;
}

int CommandConfigManager::addTransferItemMiscCommand(lua_State* L) {
	LuaObject slashcommand(L);
	if (!slashcommand.isValidTable())
		return 0;

	TransferItemMiscCommand* slashCommand = new TransferItemMiscCommand(slashcommand.getStringField("name"), server);
	parseSlashCommand(slashcommand, slashCommand);
	return 1;
}

int CommandConfigManager::addTransferItemWeaponCommand(lua_State* L) {
	LuaObject slashcommand(L);
	if (!slashcommand.isValidTable())
		return 0;

	TransferItemWeaponCommand* slashCommand = new TransferItemWeaponCommand(slashcommand.getStringField("name"), server);
	parseSlashCommand(slashcommand, slashCommand);
	return 1;
}

int CommandConfigManager::addTransferstructureCommand(lua_State* L) {
	LuaObject slashcommand(L);
	if (!slashcommand.isValidTable())
		return 0;

	TransferstructureCommand* slashCommand = new TransferstructureCommand(slashcommand.getStringField("name"), server);
	parseSlashCommand(slashcommand, slashCommand);
	return 1;
}

int CommandConfigManager::addTumbleToKneelingCommand(lua_State* L) {
	LuaObject slashcommand(L);
	if (!slashcommand.isValidTable())
		return 0;

	TumbleToKneelingCommand* slashCommand = new TumbleToKneelingCommand(slashcommand.getStringField("name"), server);
	parseSlashCommand(slashcommand, slashCommand);
	return 1;
}

int CommandConfigManager::addTumbleToProneCommand(lua_State* L) {
	LuaObject slashcommand(L);
	if (!slashcommand.isValidTable())
		return 0;

	TumbleToProneCommand* slashCommand = new TumbleToProneCommand(slashcommand.getStringField("name"), server);
	parseSlashCommand(slashcommand, slashCommand);
	return 1;
}

int CommandConfigManager::addTumbleToStandingCommand(lua_State* L) {
	LuaObject slashcommand(L);
	if (!slashcommand.isValidTable())
		return 0;

	TumbleToStandingCommand* slashCommand = new TumbleToStandingCommand(slashcommand.getStringField("name"), server);
	parseSlashCommand(slashcommand, slashCommand);
	return 1;
}

int CommandConfigManager::addUnarmedBlind1Command(lua_State* L) {
	LuaObject slashcommand(L);
	if (!slashcommand.isValidTable())
		return 0;

	UnarmedBlind1Command* slashCommand = new UnarmedBlind1Command(slashcommand.getStringField("name"), server);
	parseSlashCommand(slashcommand, slashCommand);
	return 1;
}

int CommandConfigManager::addUnarmedBodyHit1Command(lua_State* L) {
	LuaObject slashcommand(L);
	if (!slashcommand.isValidTable())
		return 0;

	UnarmedBodyHit1Command* slashCommand = new UnarmedBodyHit1Command(slashcommand.getStringField("name"), server);
	parseSlashCommand(slashcommand, slashCommand);
	return 1;
}

int CommandConfigManager::addUnarmedCombo1Command(lua_State* L) {
	LuaObject slashcommand(L);
	if (!slashcommand.isValidTable())
		return 0;

	UnarmedCombo1Command* slashCommand = new UnarmedCombo1Command(slashcommand.getStringField("name"), server);
	parseSlashCommand(slashcommand, slashCommand);
	return 1;
}

int CommandConfigManager::addUnarmedCombo2Command(lua_State* L) {
	LuaObject slashcommand(L);
	if (!slashcommand.isValidTable())
		return 0;

	UnarmedCombo2Command* slashCommand = new UnarmedCombo2Command(slashcommand.getStringField("name"), server);
	parseSlashCommand(slashcommand, slashCommand);
	return 1;
}

int CommandConfigManager::addUnarmedDizzy1Command(lua_State* L) {
	LuaObject slashcommand(L);
	if (!slashcommand.isValidTable())
		return 0;

	UnarmedDizzy1Command* slashCommand = new UnarmedDizzy1Command(slashcommand.getStringField("name"), server);
	parseSlashCommand(slashcommand, slashCommand);
	return 1;
}

int CommandConfigManager::addUnarmedHeadHit1Command(lua_State* L) {
	LuaObject slashcommand(L);
	if (!slashcommand.isValidTable())
		return 0;

	UnarmedHeadHit1Command* slashCommand = new UnarmedHeadHit1Command(slashcommand.getStringField("name"), server);
	parseSlashCommand(slashcommand, slashCommand);
	return 1;
}

int CommandConfigManager::addUnarmedHit1Command(lua_State* L) {
	LuaObject slashcommand(L);
	if (!slashcommand.isValidTable())
		return 0;

	UnarmedHit1Command* slashCommand = new UnarmedHit1Command(slashcommand.getStringField("name"), server);
	parseSlashCommand(slashcommand, slashCommand);
	return 1;
}

int CommandConfigManager::addUnarmedHit2Command(lua_State* L) {
	LuaObject slashcommand(L);
	if (!slashcommand.isValidTable())
		return 0;

	UnarmedHit2Command* slashCommand = new UnarmedHit2Command(slashcommand.getStringField("name"), server);
	parseSlashCommand(slashcommand, slashCommand);
	return 1;
}

int CommandConfigManager::addUnarmedHit3Command(lua_State* L) {
	LuaObject slashcommand(L);
	if (!slashcommand.isValidTable())
		return 0;

	UnarmedHit3Command* slashCommand = new UnarmedHit3Command(slashcommand.getStringField("name"), server);
	parseSlashCommand(slashcommand, slashCommand);
	return 1;
}

int CommandConfigManager::addUnarmedKnockdown1Command(lua_State* L) {
	LuaObject slashcommand(L);
	if (!slashcommand.isValidTable())
		return 0;

	UnarmedKnockdown1Command* slashCommand = new UnarmedKnockdown1Command(slashcommand.getStringField("name"), server);
	parseSlashCommand(slashcommand, slashCommand);
	return 1;
}

int CommandConfigManager::addUnarmedKnockdown2Command(lua_State* L) {
	LuaObject slashcommand(L);
	if (!slashcommand.isValidTable())
		return 0;

	UnarmedKnockdown2Command* slashCommand = new UnarmedKnockdown2Command(slashcommand.getStringField("name"), server);
	parseSlashCommand(slashcommand, slashCommand);
	return 1;
}

int CommandConfigManager::addUnarmedLegHit1Command(lua_State* L) {
	LuaObject slashcommand(L);
	if (!slashcommand.isValidTable())
		return 0;

	UnarmedLegHit1Command* slashCommand = new UnarmedLegHit1Command(slashcommand.getStringField("name"), server);
	parseSlashCommand(slashcommand, slashCommand);
	return 1;
}

int CommandConfigManager::addUnarmedLunge1Command(lua_State* L) {
	LuaObject slashcommand(L);
	if (!slashcommand.isValidTable())
		return 0;

	UnarmedLunge1Command* slashCommand = new UnarmedLunge1Command(slashcommand.getStringField("name"), server);
	parseSlashCommand(slashcommand, slashCommand);
	return 1;
}

int CommandConfigManager::addUnarmedLunge2Command(lua_State* L) {
	LuaObject slashcommand(L);
	if (!slashcommand.isValidTable())
		return 0;

	UnarmedLunge2Command* slashCommand = new UnarmedLunge2Command(slashcommand.getStringField("name"), server);
	parseSlashCommand(slashcommand, slashCommand);
	return 1;
}

int CommandConfigManager::addUnarmedSpinAttack1Command(lua_State* L) {
	LuaObject slashcommand(L);
	if (!slashcommand.isValidTable())
		return 0;

	UnarmedSpinAttack1Command* slashCommand = new UnarmedSpinAttack1Command(slashcommand.getStringField("name"), server);
	parseSlashCommand(slashcommand, slashCommand);
	return 1;
}

int CommandConfigManager::addUnarmedSpinAttack2Command(lua_State* L) {
	LuaObject slashcommand(L);
	if (!slashcommand.isValidTable())
		return 0;

	UnarmedSpinAttack2Command* slashCommand = new UnarmedSpinAttack2Command(slashcommand.getStringField("name"), server);
	parseSlashCommand(slashcommand, slashCommand);
	return 1;
}

int CommandConfigManager::addUnarmedStun1Command(lua_State* L) {
	LuaObject slashcommand(L);
	if (!slashcommand.isValidTable())
		return 0;

	UnarmedStun1Command* slashCommand = new UnarmedStun1Command(slashcommand.getStringField("name"), server);
	parseSlashCommand(slashcommand, slashCommand);
	return 1;
}

int CommandConfigManager::addUnassociateDroidControlDeviceWithShipCommand(lua_State* L) {
	LuaObject slashcommand(L);
	if (!slashcommand.isValidTable())
		return 0;

	UnassociateDroidControlDeviceWithShipCommand* slashCommand = new UnassociateDroidControlDeviceWithShipCommand(slashcommand.getStringField("name"), server);
	parseSlashCommand(slashcommand, slashCommand);
	return 1;
}

int CommandConfigManager::addUnCityBanCommand(lua_State* L) {
	LuaObject slashcommand(L);
	if (!slashcommand.isValidTable())
		return 0;

	UnCityBanCommand* slashCommand = new UnCityBanCommand(slashcommand.getStringField("name"), server);
	parseSlashCommand(slashcommand, slashCommand);
	return 1;
}

int CommandConfigManager::addUnconsentCommand(lua_State* L) {
	LuaObject slashcommand(L);
	if (!slashcommand.isValidTable())
		return 0;

	UnconsentCommand* slashCommand = new UnconsentCommand(slashcommand.getStringField("name"), server);
	parseSlashCommand(slashcommand, slashCommand);
	return 1;
}

int CommandConfigManager::addUnderHandShotCommand(lua_State* L) {
	LuaObject slashcommand(L);
	if (!slashcommand.isValidTable())
		return 0;

	UnderHandShotCommand* slashCommand = new UnderHandShotCommand(slashcommand.getStringField("name"), server);
	parseSlashCommand(slashcommand, slashCommand);
	return 1;
}

int CommandConfigManager::addUnfreezePlayerCommand(lua_State* L) {
	LuaObject slashcommand(L);
	if (!slashcommand.isValidTable())
		return 0;

	UnfreezePlayerCommand* slashCommand = new UnfreezePlayerCommand(slashcommand.getStringField("name"), server);
	parseSlashCommand(slashcommand, slashCommand);
	return 1;
}

int CommandConfigManager::addUninstallShipComponentCommand(lua_State* L) {
	LuaObject slashcommand(L);
	if (!slashcommand.isValidTable())
		return 0;

	UninstallShipComponentCommand* slashCommand = new UninstallShipComponentCommand(slashcommand.getStringField("name"), server);
	parseSlashCommand(slashcommand, slashCommand);
	return 1;
}

int CommandConfigManager::addUninviteCommand(lua_State* L) {
	LuaObject slashcommand(L);
	if (!slashcommand.isValidTable())
		return 0;

	UninviteCommand* slashCommand = new UninviteCommand(slashcommand.getStringField("name"), server);
	parseSlashCommand(slashcommand, slashCommand);
	return 1;
}

int CommandConfigManager::addUnsnoopCommand(lua_State* L) {
	LuaObject slashcommand(L);
	if (!slashcommand.isValidTable())
		return 0;

	UnsnoopCommand* slashCommand = new UnsnoopCommand(slashcommand.getStringField("name"), server);
	parseSlashCommand(slashcommand, slashCommand);
	return 1;
}

int CommandConfigManager::addUseReconDroneCommand(lua_State* L) {
	LuaObject slashcommand(L);
	if (!slashcommand.isValidTable())
		return 0;

	UseReconDroneCommand* slashCommand = new UseReconDroneCommand(slashcommand.getStringField("name"), server);
	parseSlashCommand(slashcommand, slashCommand);
	return 1;
}

int CommandConfigManager::addUseSkillBuffCommand(lua_State* L) {
	LuaObject slashcommand(L);
	if (!slashcommand.isValidTable())
		return 0;

	UseSkillBuffCommand* slashCommand = new UseSkillBuffCommand(slashcommand.getStringField("name"), server);
	parseSlashCommand(slashcommand, slashCommand);
	return 1;
}

int CommandConfigManager::addVentriloquismCommand(lua_State* L) {
	LuaObject slashcommand(L);
	if (!slashcommand.isValidTable())
		return 0;

	VentriloquismCommand* slashCommand = new VentriloquismCommand(slashcommand.getStringField("name"), server);
	parseSlashCommand(slashcommand, slashCommand);
	return 1;
}

int CommandConfigManager::addToggleCombatTauntsCommand(lua_State* L) {
	LuaObject slashcommand(L);
	if (!slashcommand.isValidTable())
		return 0;

	ToggleCombatTauntsCommand* slashCommand = new ToggleCombatTauntsCommand(slashcommand.getStringField("name"), server);
	parseSlashCommand(slashcommand, slashCommand);
	return 1;
}

int CommandConfigManager::addVertFurnitureCommand(lua_State* L) {
	LuaObject slashcommand(L);
	if (!slashcommand.isValidTable())
		return 0;

	VertFurnitureCommand* slashCommand = new VertFurnitureCommand(slashcommand.getStringField("name"), server);
	parseSlashCommand(slashcommand, slashCommand);
	return 1;
}

int CommandConfigManager::addVitalizeCommand(lua_State* L) {
	LuaObject slashcommand(L);
	if (!slashcommand.isValidTable())
		return 0;

	VitalizeCommand* slashCommand = new VitalizeCommand(slashcommand.getStringField("name"), server);
	parseSlashCommand(slashcommand, slashCommand);
	return 1;
}

int CommandConfigManager::addVolleyFireCommand(lua_State* L) {
	LuaObject slashcommand(L);
	if (!slashcommand.isValidTable())
		return 0;

	VolleyFireCommand* slashCommand = new VolleyFireCommand(slashcommand.getStringField("name"), server);
	parseSlashCommand(slashcommand, slashCommand);
	return 1;
}

int CommandConfigManager::addVolleyFireAttackCommand(lua_State* L) {
	LuaObject slashcommand(L);
	if (!slashcommand.isValidTable())
		return 0;

	VolleyFireAttackCommand* slashCommand = new VolleyFireAttackCommand(slashcommand.getStringField("name"), server);
	parseSlashCommand(slashcommand, slashCommand);
	return 1;
}

int CommandConfigManager::addWarcry1Command(lua_State* L) {
	LuaObject slashcommand(L);
	if (!slashcommand.isValidTable())
		return 0;

	Warcry1Command* slashCommand = new Warcry1Command(slashcommand.getStringField("name"), server);
	parseSlashCommand(slashcommand, slashCommand);
	return 1;
}

int CommandConfigManager::addWarcry2Command(lua_State* L) {
	LuaObject slashcommand(L);
	if (!slashcommand.isValidTable())
		return 0;

	Warcry2Command* slashCommand = new Warcry2Command(slashcommand.getStringField("name"), server);
	parseSlashCommand(slashcommand, slashCommand);
	return 1;
}

int CommandConfigManager::addWarningShotCommand(lua_State* L) {
	LuaObject slashcommand(L);
	if (!slashcommand.isValidTable())
		return 0;

	WarningShotCommand* slashCommand = new WarningShotCommand(slashcommand.getStringField("name"), server);
	parseSlashCommand(slashcommand, slashCommand);
	return 1;
}

int CommandConfigManager::addWatchCommand(lua_State* L) {
	LuaObject slashcommand(L);
	if (!slashcommand.isValidTable())
		return 0;

	WatchCommand* slashCommand = new WatchCommand(slashcommand.getStringField("name"), server);
	parseSlashCommand(slashcommand, slashCommand);
	return 1;
}

int CommandConfigManager::addWildShot1Command(lua_State* L) {
	LuaObject slashcommand(L);
	if (!slashcommand.isValidTable())
		return 0;

	WildShot1Command* slashCommand = new WildShot1Command(slashcommand.getStringField("name"), server);
	parseSlashCommand(slashcommand, slashCommand);
	return 1;
}

int CommandConfigManager::addWildShot2Command(lua_State* L) {
	LuaObject slashcommand(L);
	if (!slashcommand.isValidTable())
		return 0;

	WildShot2Command* slashCommand = new WildShot2Command(slashcommand.getStringField("name"), server);
	parseSlashCommand(slashcommand, slashCommand);
	return 1;
}

int CommandConfigManager::addWipeItemsCommand(lua_State* L) {
	LuaObject slashcommand(L);
	if (!slashcommand.isValidTable())
		return 0;

	WipeItemsCommand* slashCommand = new WipeItemsCommand(slashcommand.getStringField("name"), server);
	parseSlashCommand(slashcommand, slashCommand);
	return 1;
}

int CommandConfigManager::addWookieeRoarCommand(lua_State* L) {
	LuaObject slashcommand(L);
	if (!slashcommand.isValidTable())
		return 0;

	WookieeRoarCommand* slashCommand = new WookieeRoarCommand(slashcommand.getStringField("name"), server);
	parseSlashCommand(slashcommand, slashCommand);
	return 1;
}

int CommandConfigManager::addCityInfoCommand(lua_State* L) {
	LuaObject slashcommand(L);
	if (!slashcommand.isValidTable())
		return 0;

	CityInfoCommand* slashCommand = new CityInfoCommand(slashcommand.getStringField("name"), server);
	parseSlashCommand(slashcommand, slashCommand);
	return 1;
}

int CommandConfigManager::addEjectCommand(lua_State* L) {
	LuaObject slashcommand(L);
	if (!slashcommand.isValidTable())
		return 0;

	EjectCommand* slashCommand = new EjectCommand(slashcommand.getStringField("name"), server);
	parseSlashCommand(slashcommand, slashCommand);
	return 1;
}

int CommandConfigManager::addLaunchIntoSpaceCommand(lua_State* L) {
	LuaObject slashcommand(L);
	if (!slashcommand.isValidTable())
		return 0;

	LaunchIntoSpaceCommand* slashCommand = new LaunchIntoSpaceCommand(slashcommand.getStringField("name"), server);
	parseSlashCommand(slashcommand, slashCommand);
	return 1;
}

int CommandConfigManager::addUnstickCommand(lua_State* L) {
	LuaObject slashcommand(L);
	if (!slashcommand.isValidTable())
		return 0;

	UnstickCommand* slashCommand = new UnstickCommand(slashcommand.getStringField("name"), server);
	parseSlashCommand(slashcommand, slashCommand);
	return 1;
}

int CommandConfigManager::addWaypointCommand(lua_State* L) {
	LuaObject slashcommand(L);
	if (!slashcommand.isValidTable())
		return 0;

	WaypointCommand* slashCommand = new WaypointCommand(slashcommand.getStringField("name"), server);
	parseSlashCommand(slashcommand, slashCommand);
	return 1;
}

int CommandConfigManager::addCreateVendorCommand(lua_State* L) {
	LuaObject slashcommand(L);
	if (!slashcommand.isValidTable())
		return 0;

	CreateVendorCommand* slashCommand = new CreateVendorCommand(slashcommand.getStringField("name"), server);
	parseSlashCommand(slashcommand, slashCommand);
	return 1;
}




