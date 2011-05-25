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

#ifndef COMMANDCONFIGMANAGER_H_
#define COMMANDCONFIGMANAGER_H_

#include "engine/engine.h"

#include "server/zone/objects/creature/commands/QueueCommand.h"

namespace server {
namespace zone {
class ZoneProcessServer;
}
}

using namespace server::zone;

namespace server {
namespace zone {
namespace managers {
namespace objectcontroller {
namespace command {

class CommandList;

class CommandConfigManager : public Lua {
public:
	static ZoneProcessServer* server;
	static CommandList* slashCommands;

	CommandConfigManager(ZoneProcessServer* serv);

	void registerFunctions();
	void registerGlobals();

	void registerSpecialCommands();

	bool loadSlashCommandsFile(CommandList* sCommands) {
		slashCommands = sCommands;
		//info("Loading commands...");
		//return runFile("scripts/commands/commands.lua");
		return runFile("scripts/commands/commands.lua");
	}

	//lua functions
	static int runSlashCommandsFile(lua_State* L);

	static void parseOptions(LuaObject& slashcommand, QueueCommand* command);
	static void parseAlternativeNames(String& alternativeNames, QueueCommand* slashCommand);
	static void parseSlashCommand(LuaObject &command, QueueCommand* slashCommand);

	// AddSlashCommand functions
	static int addActionShot1Command(lua_State* L);
	static int addActionShot2Command(lua_State* L);
	static int addActivateCloneCommand(lua_State* L);
	static int addActivateQuestCommand(lua_State* L);
	static int addAddAllowedPlayerCommand(lua_State* L);
	static int addAddBannedPlayerCommand(lua_State* L);
	static int addAddFriendCommand(lua_State* L);
	static int addAddIgnoreCommand(lua_State* L);
	static int addAddMapLocationCommand(lua_State* L);
	static int addAddPowerCommand(lua_State* L);
	static int addAdjustLotCountCommand(lua_State* L);
	static int addAiIgnoreCommand(lua_State* L);
	static int addAimCommand(lua_State* L);
	static int addAlertCommand(lua_State* L);
	static int addAnimalAttackCommand(lua_State* L);
	static int addAnimalCalmCommand(lua_State* L);
	static int addAnimalScareCommand(lua_State* L);
	static int addAnonCommand(lua_State* L);
	static int addApplyDiseaseCommand(lua_State* L);
	static int addApplyPoisonCommand(lua_State* L);
	static int addApplyPowerupCommand(lua_State* L);
	static int addAreatrackCommand(lua_State* L);
	static int addAssignDroidCommand(lua_State* L);
	static int addAssistCommand(lua_State* L);
	static int addAssociateDroidControlDeviceWithShipCommand(lua_State* L);
	static int addAttackCommand(lua_State* L);
	static int addAuctionCommand(lua_State* L);
	static int addAuctionAcceptCommand(lua_State* L);
	static int addAuctionBidCommand(lua_State* L);
	static int addAuctionCancelCommand(lua_State* L);
	static int addAuctionCreateCommand(lua_State* L);
	static int addAuctionQueryCommand(lua_State* L);
	static int addAuctionRetrieveCommand(lua_State* L);
	static int addAuctionsayCommand(lua_State* L);
	static int addAvoidIncapacitationCommand(lua_State* L);
	static int addBandFlourishCommand(lua_State* L);
	static int addBattlefieldStatusCommand(lua_State* L);
	static int addBerserk1Command(lua_State* L);
	static int addBerserk2Command(lua_State* L);
	static int addBetCommand(lua_State* L);
	static int addBleedingShotCommand(lua_State* L);
	static int addBlindAttackCommand(lua_State* L);
	static int addBoardShuttleCommand(lua_State* L);
	static int addBodyShot1Command(lua_State* L);
	static int addBodyShot2Command(lua_State* L);
	static int addBodyShot3Command(lua_State* L);
	static int addBoostmoraleCommand(lua_State* L);
	static int addBroadcastCommand(lua_State* L);
	static int addBroadcastAreaCommand(lua_State* L);
	static int addBroadcastGalaxyCommand(lua_State* L);
	static int addBroadcastPlanetCommand(lua_State* L);
	static int addBurstRunCommand(lua_State* L);
	static int addBurstShot1Command(lua_State* L);
	static int addBurstShot2Command(lua_State* L);
	static int addCancelCraftingSessionCommand(lua_State* L);
	static int addCenterOfBeingCommand(lua_State* L);
	static int addChangeBandMusicCommand(lua_State* L);
	static int addChangeDanceCommand(lua_State* L);
	static int addChangeMusicCommand(lua_State* L);
	static int addChannelForceCommand(lua_State* L);
	static int addChargeShot1Command(lua_State* L);
	static int addChargeShot2Command(lua_State* L);
	static int addCheckForceStatusCommand(lua_State* L);
	static int addCitybanCommand(lua_State* L);
	static int addCitypardonCommand(lua_State* L);
	static int addClaimVeteranRewardCommand(lua_State* L);
	static int addClearCompletedQuestCommand(lua_State* L);
	static int addClearVeteranRewardCommand(lua_State* L);
	static int addClientQualifiedForSkillCommand(lua_State* L);
	static int addCloneCommand(lua_State* L);
	static int addCloseContainerCommand(lua_State* L);
	static int addColorlightsCommand(lua_State* L);
	static int addCombatCommand(lua_State* L);
	static int addCombatEscapeCommand(lua_State* L);
	static int addCombatModeCheckCommand(lua_State* L);
	static int addCombatSpamCommand(lua_State* L);
	static int addCombatTargetCommand(lua_State* L);
	static int addCompleteQuestCommand(lua_State* L);
	static int addConcealCommand(lua_State* L);
	static int addConcealShotCommand(lua_State* L);
	static int addConfusionShotCommand(lua_State* L);
	static int addConsentCommand(lua_State* L);
	static int addCorpseCommand(lua_State* L);
	static int addCounterAttackCommand(lua_State* L);
	static int addCoupDeGraceCommand(lua_State* L);
	static int addCraftCommand(lua_State* L);
	static int addCreateCreatureCommand(lua_State* L);
	static int addCreateManfSchematicCommand(lua_State* L);
	static int addCreateMissionElementCommand(lua_State* L);
	static int addCreateNPCCommand(lua_State* L);
	static int addCreatePrototypeCommand(lua_State* L);
	static int addCreateSpawningElementCommand(lua_State* L);
	static int addCreateSpawningElementWithDifficultyCommand(lua_State* L);
	static int addCreatureAreaAttackCommand(lua_State* L);
	static int addCreatureAreaBleedingCommand(lua_State* L);
	static int addCreatureAreaComboCommand(lua_State* L);
	static int addCreatureAreaDiseaseCommand(lua_State* L);
	static int addCreatureAreaKnockdownCommand(lua_State* L);
	static int addCreatureAreaPoisonCommand(lua_State* L);
	static int addCreditsCommand(lua_State* L);
	static int addCripplingShotCommand(lua_State* L);
	static int addCsAppendCommentCommand(lua_State* L);
	static int addCsCancelTicketCommand(lua_State* L);
	static int addCsConnectPlayerCommand(lua_State* L);
	static int addCsCreateTicketCommand(lua_State* L);
	static int addCsDisconnectPlayerCommand(lua_State* L);
	static int addCsGetArticleCommand(lua_State* L);
	static int addCsGetCommentsCommand(lua_State* L);
	static int addCsGetTicketsCommand(lua_State* L);
	static int addCsRequestCategoriesCommand(lua_State* L);
	static int addCsSearchKnowledgeBaseCommand(lua_State* L);
	static int addCuiConsentResponseCommand(lua_State* L);
	static int addCureDiseaseCommand(lua_State* L);
	static int addCurePoisonCommand(lua_State* L);
	static int addCustomizeDroidCommand(lua_State* L);
	static int addCustomizeVehicleCommand(lua_State* L);
	static int addDatabaseCommand(lua_State* L);
	static int addDazzleCommand(lua_State* L);
	static int addDeactivateQuestCommand(lua_State* L);
	static int addDeathBlowCommand(lua_State* L);
	static int addDeathCountCommand(lua_State* L);
	static int addDeclareOvertCommand(lua_State* L);
	static int addDeclareresidenceCommand(lua_State* L);
	static int addDeclineCommand(lua_State* L);
	static int addDefaultAttackCommand(lua_State* L);
	static int addDefuseMinefieldCommand(lua_State* L);
	static int addDelegateFactionPointsCommand(lua_State* L);
	static int addDenyServiceCommand(lua_State* L);
	static int addDeployTrapCommand(lua_State* L);
	static int addDestroyCommand(lua_State* L);
	static int addDestroystructureCommand(lua_State* L);
	static int addDetonateDroidCommand(lua_State* L);
	static int addDiagnoseCommand(lua_State* L);
	static int addDisarmingShot1Command(lua_State* L);
	static int addDisarmingShot2Command(lua_State* L);
	static int addDisbandCommand(lua_State* L);
	static int addDismissGroupMemberCommand(lua_State* L);
	static int addDismountCommand(lua_State* L);
	static int addDismountandstoreCommand(lua_State* L);
	static int addDistractCommand(lua_State* L);
	static int addDiveShotCommand(lua_State* L);
	static int addDizzyAttackCommand(lua_State* L);
	static int addDoubleTapCommand(lua_State* L);
	static int addDragIncapacitatedPlayerCommand(lua_State* L);
	static int addDrainForceCommand(lua_State* L);
	static int addDuelCommand(lua_State* L);
	static int addDumpTargetInformationCommand(lua_State* L);
	static int addDumpZoneInformationCommand(lua_State* L);
	static int addEatCommand(lua_State* L);
	static int addEditAppearanceCommand(lua_State* L);
	static int addEditBankCommand(lua_State* L);
	static int addEditBankAccountCommand(lua_State* L);
	static int addEditStatsCommand(lua_State* L);
	static int addEmboldenpetsCommand(lua_State* L);
	static int addEmptyMailTargetCommand(lua_State* L);
	static int addEndDuelCommand(lua_State* L);
	static int addEnragepetsCommand(lua_State* L);
	static int addEquilibriumCommand(lua_State* L);
	static int addExecuteKnowledgeBaseMessageCommand(lua_State* L);
	static int addExtinguishFireCommand(lua_State* L);
	static int addExtractObjectCommand(lua_State* L);
	static int addEyeShotCommand(lua_State* L);
	static int addFactoryCrateSplitCommand(lua_State* L);
	static int addFanShotCommand(lua_State* L);
	static int addFastBlastCommand(lua_State* L);
	static int addFeignDeathCommand(lua_State* L);
	static int addFindCommand(lua_State* L);
	static int addFindFriendCommand(lua_State* L);
	static int addFindMyTrainerCommand(lua_State* L);
	static int addFindObjectCommand(lua_State* L);
	static int addFindPlayerCommand(lua_State* L);
	static int addFireAcidCone1Command(lua_State* L);
	static int addFireAcidCone2Command(lua_State* L);
	static int addFireAcidSingle1Command(lua_State* L);
	static int addFireAcidSingle2Command(lua_State* L);
	static int addFireHeavyWeaponCommand(lua_State* L);
	static int addFirejetCommand(lua_State* L);
	static int addFireLightningCone1Command(lua_State* L);
	static int addFireLightningCone2Command(lua_State* L);
	static int addFireLightningSingle1Command(lua_State* L);
	static int addFireLightningSingle2Command(lua_State* L);
	static int addFirstAidCommand(lua_State* L);
	static int addFishCommand(lua_State* L);
	static int addFlameCone1Command(lua_State* L);
	static int addFlameCone2Command(lua_State* L);
	static int addFlameSingle1Command(lua_State* L);
	static int addFlameSingle2Command(lua_State* L);
	static int addFlashSpeederCommand(lua_State* L);
	static int addFlourishCommand(lua_State* L);
	static int addFlurryShot1Command(lua_State* L);
	static int addFlurryShot2Command(lua_State* L);
	static int addFlushingShot1Command(lua_State* L);
	static int addFlushingShot2Command(lua_State* L);
	static int addForageCommand(lua_State* L);
	static int addForceAbsorb1Command(lua_State* L);
	static int addForceAbsorb2Command(lua_State* L);
	static int addForceArmor1Command(lua_State* L);
	static int addForceArmor2Command(lua_State* L);
	static int addForceChokeCommand(lua_State* L);
	static int addForceCommandCommand(lua_State* L);
	static int addForceCureDiseaseCommand(lua_State* L);
	static int addForceCurePoisonCommand(lua_State* L);
	static int addForceFeedback1Command(lua_State* L);
	static int addForceFeedback2Command(lua_State* L);
	static int addForceIntimidate1Command(lua_State* L);
	static int addForceIntimidate2Command(lua_State* L);
	static int addForceKnockdown1Command(lua_State* L);
	static int addForceKnockdown2Command(lua_State* L);
	static int addForceKnockdown3Command(lua_State* L);
	static int addForceLightningCone1Command(lua_State* L);
	static int addForceLightningCone2Command(lua_State* L);
	static int addForceLightningSingle1Command(lua_State* L);
	static int addForceLightningSingle2Command(lua_State* L);
	static int addForceMeditateCommand(lua_State* L);
	static int addForceOfWillCommand(lua_State* L);
	static int addForceProtectionCommand(lua_State* L);
	static int addForceResistBleedingCommand(lua_State* L);
	static int addForceResistDiseaseCommand(lua_State* L);
	static int addForceResistPoisonCommand(lua_State* L);
	static int addForceResistStatesCommand(lua_State* L);
	static int addForceRun1Command(lua_State* L);
	static int addForceRun2Command(lua_State* L);
	static int addForceRun3Command(lua_State* L);
	static int addForceShield1Command(lua_State* L);
	static int addForceShield2Command(lua_State* L);
	static int addForceSpeed1Command(lua_State* L);
	static int addForceSpeed2Command(lua_State* L);
	static int addForceThrow1Command(lua_State* L);
	static int addForceThrow2Command(lua_State* L);
	static int addForceWeaken1Command(lua_State* L);
	static int addForceWeaken2Command(lua_State* L);
	static int addFormupCommand(lua_State* L);
	static int addFreezePlayerCommand(lua_State* L);
	static int addFullAutoArea1Command(lua_State* L);
	static int addFullAutoArea2Command(lua_State* L);
	static int addFullAutoSingle1Command(lua_State* L);
	static int addFullAutoSingle2Command(lua_State* L);
	static int addGCommand(lua_State* L);
	static int addGallopCommand(lua_State* L);
	static int addGallopStopCommand(lua_State* L);
	static int addGcCommand(lua_State* L);
	static int addGcwStatusCommand(lua_State* L);
	static int addGenerateCraftedItemCommand(lua_State* L);
	static int addGetAccountInfoCommand(lua_State* L);
	static int addGetAttributesCommand(lua_State* L);
	static int addGetAttributesBatchCommand(lua_State* L);
	static int addGetFriendListCommand(lua_State* L);
	static int addGetGameTimeCommand(lua_State* L);
	static int addGetIgnoreListCommand(lua_State* L);
	static int addGetMapLocationsCommand(lua_State* L);
	static int addGetObjVarsCommand(lua_State* L);
	static int addGetPlayerIdCommand(lua_State* L);
	static int addGetPrototypeCommand(lua_State* L);
	static int addGetRankCommand(lua_State* L);
	static int addGetSpawnDelaysCommand(lua_State* L);
	static int addGetStationNameCommand(lua_State* L);
	static int addGetVeteranRewardTimeCommand(lua_State* L);
	static int addGetVeteranRewardTimeCsCommand(lua_State* L);
	static int addGiveItemCommand(lua_State* L);
	static int addGiveMaintenanceToVendorCommand(lua_State* L);
	static int addGivevendormaintCommand(lua_State* L);
	static int addGmForceCommandCommand(lua_State* L);
	static int addGmCreateClassResourceCommand(lua_State* L);
	static int addGmCreateSpecificResourceCommand(lua_State* L);
	static int addGmForceRankCommand(lua_State* L);
	static int addGmFsVillageCommand(lua_State* L);
	static int addGmJediStateCommand(lua_State* L);
	static int addGmReviveCommand(lua_State* L);
	static int addGotoCommand(lua_State* L);
	static int addGrantBadgeCommand(lua_State* L);
	static int addGrantPadawanTrialsEligibilityCommand(lua_State* L);
	static int addGrantSkillCommand(lua_State* L);
	static int addGrantTitleCommand(lua_State* L);
	static int addGrantZoningRightsCommand(lua_State* L);
	static int addGroupChatCommand(lua_State* L);
	static int addGroupSayCommand(lua_State* L);
	static int addGsayCommand(lua_State* L);
	static int addGtellCommand(lua_State* L);
	static int addGuildCommand(lua_State* L);
	static int addGuildremoveCommand(lua_State* L);
	static int addGuildsayCommand(lua_State* L);
	static int addGuildstatusCommand(lua_State* L);
	static int addHarmfulCommand(lua_State* L);
	static int addHarmlessCommand(lua_State* L);
	static int addHarvestCorpseCommand(lua_State* L);
	static int addHarvesterActivateCommand(lua_State* L);
	static int addHarvesterDeactivateCommand(lua_State* L);
	static int addHarvesterDiscardHopperCommand(lua_State* L);
	static int addHarvesterGetResourceDataCommand(lua_State* L);
	static int addHarvesterHarvestCommand(lua_State* L);
	static int addHarvesterMakeCrateCommand(lua_State* L);
	static int addHarvesterSelectResourceCommand(lua_State* L);
	static int addHarvesterTakeSurveyCommand(lua_State* L);
	static int addHasVeteranRewardCommand(lua_State* L);
	static int addHaveconsentCommand(lua_State* L);
	static int addHeadShot1Command(lua_State* L);
	static int addHeadShot2Command(lua_State* L);
	static int addHeadShot3Command(lua_State* L);
	static int addHealActionSelf1Command(lua_State* L);
	static int addHealActionSelf2Command(lua_State* L);
	static int addHealActionWoundOther1Command(lua_State* L);
	static int addHealActionWoundOther2Command(lua_State* L);
	static int addHealActionWoundSelf1Command(lua_State* L);
	static int addHealActionWoundSelf2Command(lua_State* L);
	static int addHealAllOther1Command(lua_State* L);
	static int addHealAllOther2Command(lua_State* L);
	static int addHealAllSelf1Command(lua_State* L);
	static int addHealAllSelf2Command(lua_State* L);
	static int addHealBattleFatigueOther1Command(lua_State* L);
	static int addHealBattleFatigueOther2Command(lua_State* L);
	static int addHealBattleFatigueSelf1Command(lua_State* L);
	static int addHealBattleFatigueSelf2Command(lua_State* L);
	static int addHealDamageCommand(lua_State* L);
	static int addHealDroidDamageCommand(lua_State* L);
	static int addHealDroidWoundCommand(lua_State* L);
	static int addHealEnhanceCommand(lua_State* L);
	static int addHealHealthSelf1Command(lua_State* L);
	static int addHealHealthSelf2Command(lua_State* L);
	static int addHealHealthWoundOther1Command(lua_State* L);
	static int addHealHealthWoundOther2Command(lua_State* L);
	static int addHealHealthWoundSelf1Command(lua_State* L);
	static int addHealHealthWoundSelf2Command(lua_State* L);
	static int addHealMindCommand(lua_State* L);
	static int addHealMindSelf1Command(lua_State* L);
	static int addHealMindSelf2Command(lua_State* L);
	static int addHealMindWoundOther1Command(lua_State* L);
	static int addHealMindWoundOther2Command(lua_State* L);
	static int addHealMindWoundSelf1Command(lua_State* L);
	static int addHealMindWoundSelf2Command(lua_State* L);
	static int addHealPetCommand(lua_State* L);
	static int addHealStateCommand(lua_State* L);
	static int addHealStatesOtherCommand(lua_State* L);
	static int addHealStatesSelfCommand(lua_State* L);
	static int addHealthShot1Command(lua_State* L);
	static int addHealthShot2Command(lua_State* L);
	static int addHealWoundCommand(lua_State* L);
	static int addHoloEmoteCommand(lua_State* L);
	static int addImagedesignCommand(lua_State* L);
	static int addInitializeComponentCommand(lua_State* L);
	static int addInnateCommand(lua_State* L);
	static int addInsertItemIntoShipComponentSlotCommand(lua_State* L);
	static int addInstallMissionTerminalCommand(lua_State* L);
	static int addInstallShipComponentCommand(lua_State* L);
	static int addInsureCommand(lua_State* L);
	static int addIntimidate1Command(lua_State* L);
	static int addIntimidate2Command(lua_State* L);
	static int addIntimidationAttackCommand(lua_State* L);
	static int addInviteCommand(lua_State* L);
	static int addInvulnerableCommand(lua_State* L);
	static int addItemmovebackCommand(lua_State* L);
	static int addItemmovedownCommand(lua_State* L);
	static int addItemmoveforwardCommand(lua_State* L);
	static int addItemmoveupCommand(lua_State* L);
	static int addItemrotateleftCommand(lua_State* L);
	static int addItemrotaterightCommand(lua_State* L);
	static int addJediMindTrickCommand(lua_State* L);
	static int addJoinCommand(lua_State* L);
	static int addJoinGameCommand(lua_State* L);
	static int addKickCommand(lua_State* L);
	static int addKillCommand(lua_State* L);
	static int addKillPlayerCommand(lua_State* L);
	static int addKipUpShotCommand(lua_State* L);
	static int addKneelCommand(lua_State* L);
	static int addKnockdownAttackCommand(lua_State* L);
	static int addKnockdownFireCommand(lua_State* L);
	static int addLagCommand(lua_State* L);
	static int addLastDitchCommand(lua_State* L);
	static int addLaunchFireworkCommand(lua_State* L);
	static int addLeaveGameCommand(lua_State* L);
	static int addLeaveGroupCommand(lua_State* L);
	static int addLegShot1Command(lua_State* L);
	static int addLegShot2Command(lua_State* L);
	static int addLegShot3Command(lua_State* L);
	static int addLfgCommand(lua_State* L);
	static int addListActiveQuestsCommand(lua_State* L);
	static int addListCompletedQuestsCommand(lua_State* L);
	static int addListenCommand(lua_State* L);
	static int addListGuildsCommand(lua_State* L);
	static int addLogoutCommand(lua_State* L);
	static int addLootCommand(lua_State* L);
	static int addLootAiCorpseCommand(lua_State* L);
	static int addLootPlayerCorpseCommand(lua_State* L);
	static int addLowBlowCommand(lua_State* L);
	static int addMakeLeaderCommand(lua_State* L);
	static int addMakeSurveyCommand(lua_State* L);
	static int addManufactureCommand(lua_State* L);
	static int addMaskscentCommand(lua_State* L);
	static int addMaxCombatAbilityCommand(lua_State* L);
	static int addMaxStatsCommand(lua_State* L);
	static int addMedicalForageCommand(lua_State* L);
	static int addMeditateCommand(lua_State* L);
	static int addMediumDiseaseCommand(lua_State* L);
	static int addMediumPoisonCommand(lua_State* L);
	static int addMelee1hBlindHit1Command(lua_State* L);
	static int addMelee1hBlindHit2Command(lua_State* L);
	static int addMelee1hBodyHit1Command(lua_State* L);
	static int addMelee1hBodyHit2Command(lua_State* L);
	static int addMelee1hBodyHit3Command(lua_State* L);
	static int addMelee1hDizzyHit1Command(lua_State* L);
	static int addMelee1hDizzyHit2Command(lua_State* L);
	static int addMelee1hHealthHit1Command(lua_State* L);
	static int addMelee1hHealthHit2Command(lua_State* L);
	static int addMelee1hHit1Command(lua_State* L);
	static int addMelee1hHit2Command(lua_State* L);
	static int addMelee1hHit3Command(lua_State* L);
	static int addMelee1hLunge1Command(lua_State* L);
	static int addMelee1hLunge2Command(lua_State* L);
	static int addMelee1hScatterHit1Command(lua_State* L);
	static int addMelee1hScatterHit2Command(lua_State* L);
	static int addMelee1hSpinAttack1Command(lua_State* L);
	static int addMelee1hSpinAttack2Command(lua_State* L);
	static int addMelee2hArea1Command(lua_State* L);
	static int addMelee2hArea2Command(lua_State* L);
	static int addMelee2hArea3Command(lua_State* L);
	static int addMelee2hHeadHit1Command(lua_State* L);
	static int addMelee2hHeadHit2Command(lua_State* L);
	static int addMelee2hHeadHit3Command(lua_State* L);
	static int addMelee2hHit1Command(lua_State* L);
	static int addMelee2hHit2Command(lua_State* L);
	static int addMelee2hHit3Command(lua_State* L);
	static int addMelee2hLunge1Command(lua_State* L);
	static int addMelee2hLunge2Command(lua_State* L);
	static int addMelee2hMindHit1Command(lua_State* L);
	static int addMelee2hMindHit2Command(lua_State* L);
	static int addMelee2hSpinAttack1Command(lua_State* L);
	static int addMelee2hSpinAttack2Command(lua_State* L);
	static int addMelee2hSweep1Command(lua_State* L);
	static int addMelee2hSweep2Command(lua_State* L);
	static int addMildDiseaseCommand(lua_State* L);
	static int addMildPoisonCommand(lua_State* L);
	static int addMindBlast1Command(lua_State* L);
	static int addMindBlast2Command(lua_State* L);
	static int addMindShot1Command(lua_State* L);
	static int addMindShot2Command(lua_State* L);
	static int addMoneyCommand(lua_State* L);
	static int addMountCommand(lua_State* L);
	static int addMoveFurnitureCommand(lua_State* L);
	static int addMultiTargetPistolShotCommand(lua_State* L);
	static int addMultiTargetShotCommand(lua_State* L);
	static int addNameStructureCommand(lua_State* L);
	static int addNewbiehelperCommand(lua_State* L);
	static int addNewbieRequestStartingLocationsCommand(lua_State* L);
	static int addNewbieSelectStartingLocationCommand(lua_State* L);
	static int addNextCraftingStageCommand(lua_State* L);
	static int addNpcCommand(lua_State* L);
	static int addNpcConversationSelectCommand(lua_State* L);
	static int addNpcConversationStartCommand(lua_State* L);
	static int addNpcConversationStopCommand(lua_State* L);
	static int addObjectCommand(lua_State* L);
	static int addObjvarCommand(lua_State* L);
	static int addOpenContainerCommand(lua_State* L);
	static int addOverChargeShot1Command(lua_State* L);
	static int addOverChargeShot2Command(lua_State* L);
	static int addOverrideActiveMonthsCommand(lua_State* L);
	static int addOverridePadawanTrialsEligibilityCommand(lua_State* L);
	static int addPanicShotCommand(lua_State* L);
	static int addPauseDanceCommand(lua_State* L);
	static int addPauseMusicCommand(lua_State* L);
	static int addPaWithdrawCommand(lua_State* L);
	static int addPaymaintenanceCommand(lua_State* L);
	static int addPeaceCommand(lua_State* L);
	static int addPermissionListModifyCommand(lua_State* L);
	static int addPistolMeleeDefense1Command(lua_State* L);
	static int addPistolMeleeDefense2Command(lua_State* L);
	static int addPlaceBattlefieldStructureCommand(lua_State* L);
	static int addPlaceStructureCommand(lua_State* L);
	static int addPlaceStructureModeCommand(lua_State* L);
	static int addPlanetCommand(lua_State* L);
	static int addPlanetsayCommand(lua_State* L);
	static int addPlanetwarpCommand(lua_State* L);
	static int addPlanetwarpTargetCommand(lua_State* L);
	static int addPointBlankArea1Command(lua_State* L);
	static int addPointBlankArea2Command(lua_State* L);
	static int addPointBlankSingle1Command(lua_State* L);
	static int addPointBlankSingle2Command(lua_State* L);
	static int addPolearmActionHit1Command(lua_State* L);
	static int addPolearmActionHit2Command(lua_State* L);
	static int addPolearmArea1Command(lua_State* L);
	static int addPolearmArea2Command(lua_State* L);
	static int addPolearmHit1Command(lua_State* L);
	static int addPolearmHit2Command(lua_State* L);
	static int addPolearmHit3Command(lua_State* L);
	static int addPolearmLegHit1Command(lua_State* L);
	static int addPolearmLegHit2Command(lua_State* L);
	static int addPolearmLegHit3Command(lua_State* L);
	static int addPolearmLunge1Command(lua_State* L);
	static int addPolearmLunge2Command(lua_State* L);
	static int addPolearmSpinAttack1Command(lua_State* L);
	static int addPolearmSpinAttack2Command(lua_State* L);
	static int addPolearmStun1Command(lua_State* L);
	static int addPolearmStun2Command(lua_State* L);
	static int addPolearmSweep1Command(lua_State* L);
	static int addPolearmSweep2Command(lua_State* L);
	static int addPostureDownAttackCommand(lua_State* L);
	static int addPostureUpAttackCommand(lua_State* L);
	static int addPowerBoostCommand(lua_State* L);
	static int addProneCommand(lua_State* L);
	static int addPurchaseReinforcementCommand(lua_State* L);
	static int addPurchaseTicketCommand(lua_State* L);
	static int addQuickHealCommand(lua_State* L);
	static int addRallyCommand(lua_State* L);
	static int addReconnectToTransferServerCommand(lua_State* L);
	static int addRecruitSkillTrainerCommand(lua_State* L);
	static int addRegainConsciousnessCommand(lua_State* L);
	static int addRegenerationCommand(lua_State* L);
	static int addRegisterWithLocationCommand(lua_State* L);
	static int addReloadCommand(lua_State* L);
	static int addRemoteCommand(lua_State* L);
	static int addRemoveAllowedPlayerCommand(lua_State* L);
	static int addRemoveBannedPlayerCommand(lua_State* L);
	static int addRemoveFriendCommand(lua_State* L);
	static int addRemoveIgnoreCommand(lua_State* L);
	static int addRepairBattlefieldStructureCommand(lua_State* L);
	static int addRepairShipComponentInSlotCommand(lua_State* L);
	static int addReportCommand(lua_State* L);
	static int addRequestBadgesCommand(lua_State* L);
	static int addRequestBiographyCommand(lua_State* L);
	static int addRequestCharacterMatchCommand(lua_State* L);
	static int addRequestCharacterSheetInfoCommand(lua_State* L);
	static int addRequestCoreSampleCommand(lua_State* L);
	static int addRequestCraftingSessionCommand(lua_State* L);
	static int addRequestDraftSlotsCommand(lua_State* L);
	static int addRequestDraftSlotsBatchCommand(lua_State* L);
	static int addRequestManfSchematicSlotsCommand(lua_State* L);
	static int addRequestResourceWeightsCommand(lua_State* L);
	static int addRequestResourceWeightsBatchCommand(lua_State* L);
	static int addRequestSetStatMigrationDataCommand(lua_State* L);
	static int addRequestStatMigrationDataCommand(lua_State* L);
	static int addRequestStatMigrationStartCommand(lua_State* L);
	static int addRequestStatMigrationStopCommand(lua_State* L);
	static int addRequestStimpackCommand(lua_State* L);
	static int addRequestSurveyCommand(lua_State* L);
	static int addRequestWaypointAtPositionCommand(lua_State* L);
	static int addRescueCommand(lua_State* L);
	static int addResendLoginMessageToAllCommand(lua_State* L);
	static int addResetJediCommand(lua_State* L);
	static int addResourceCommand(lua_State* L);
	static int addResourceContainerSplitCommand(lua_State* L);
	static int addResourceContainerTransferCommand(lua_State* L);
	static int addResourceSetNameCommand(lua_State* L);
	static int addResSampleLoopCommand(lua_State* L);
	static int addRestartConversionCommand(lua_State* L);
	static int addRestartCraftingSessionCommand(lua_State* L);
	static int addRetreatCommand(lua_State* L);
	static int addRevivePlayerCommand(lua_State* L);
	static int addRevokeBadgeCommand(lua_State* L);
	static int addRevokeSkillCommand(lua_State* L);
	static int addRolePlayCommand(lua_State* L);
	static int addRollShotCommand(lua_State* L);
	static int addRotateFurnitureCommand(lua_State* L);
	static int addSaber1hComboHit1Command(lua_State* L);
	static int addSaber1hComboHit2Command(lua_State* L);
	static int addSaber1hComboHit3Command(lua_State* L);
	static int addSaber1hFlurryCommand(lua_State* L);
	static int addSaber1hFlurry2Command(lua_State* L);
	static int addSaber1hHeadHit1Command(lua_State* L);
	static int addSaber1hHeadHit2Command(lua_State* L);
	static int addSaber1hHeadHit3Command(lua_State* L);
	static int addSaber1hHit1Command(lua_State* L);
	static int addSaber1hHit2Command(lua_State* L);
	static int addSaber1hHit3Command(lua_State* L);
	static int addSaber2hBodyHit1Command(lua_State* L);
	static int addSaber2hBodyHit2Command(lua_State* L);
	static int addSaber2hBodyHit3Command(lua_State* L);
	static int addSaber2hFrenzyCommand(lua_State* L);
	static int addSaber2hHit1Command(lua_State* L);
	static int addSaber2hHit2Command(lua_State* L);
	static int addSaber2hHit3Command(lua_State* L);
	static int addSaber2hPhantomCommand(lua_State* L);
	static int addSaber2hSweep1Command(lua_State* L);
	static int addSaber2hSweep2Command(lua_State* L);
	static int addSaber2hSweep3Command(lua_State* L);
	static int addSaberPolearmDervishCommand(lua_State* L);
	static int addSaberPolearmDervish2Command(lua_State* L);
	static int addSaberPolearmHit1Command(lua_State* L);
	static int addSaberPolearmHit2Command(lua_State* L);
	static int addSaberPolearmHit3Command(lua_State* L);
	static int addSaberPolearmLegHit1Command(lua_State* L);
	static int addSaberPolearmLegHit2Command(lua_State* L);
	static int addSaberPolearmLegHit3Command(lua_State* L);
	static int addSaberPolearmSpinAttack1Command(lua_State* L);
	static int addSaberPolearmSpinAttack2Command(lua_State* L);
	static int addSaberPolearmSpinAttack3Command(lua_State* L);
	static int addSaberSlash1Command(lua_State* L);
	static int addSaberSlash2Command(lua_State* L);
	static int addSaberThrow1Command(lua_State* L);
	static int addSaberThrow2Command(lua_State* L);
	static int addSaberThrow3Command(lua_State* L);
	static int addSampleCommand(lua_State* L);
	static int addSampleDNACommand(lua_State* L);
	static int addScatterShot1Command(lua_State* L);
	static int addScatterShot2Command(lua_State* L);
	static int addScriptCommand(lua_State* L);
	static int addSearchCorpseCommand(lua_State* L);
	static int addSecretSpawnSpamCommand(lua_State* L);
	static int addSeGogglesCommand(lua_State* L);
	static int addSelectDraftSchematicCommand(lua_State* L);
	static int addServerCommand(lua_State* L);
	static int addServerDestroyObjectCommand(lua_State* L);
	static int addServerSysGroupCommand(lua_State* L);
	static int addSetBiographyAdminCommand(lua_State* L);
	static int addSetBiographyCommand(lua_State* L);
	static int addSetBoostmoraleCommand(lua_State* L);
	static int addSetChargeCommand(lua_State* L);
	static int addSetCurrentSkillTitleCommand(lua_State* L);
	static int addSetExperienceCommand(lua_State* L);
	static int addSetFactionCommand(lua_State* L);
	static int addSetFactionStandingCommand(lua_State* L);
	static int addSetFirstNameCommand(lua_State* L);
	static int addSetFormupCommand(lua_State* L);
	static int addSetGodModeCommand(lua_State* L);
	static int addSetHueCommand(lua_State* L);
	static int addSetIntimidateCommand(lua_State* L);
	static int addSetLastNameCommand(lua_State* L);
	static int addSetLoginMessageCommand(lua_State* L);
	static int addSetLoginTitleCommand(lua_State* L);
	static int addSetMatchMakingCharacterIdCommand(lua_State* L);
	static int addSetMatchMakingPersonalIdCommand(lua_State* L);
	static int addSetMaximumSpawnTimeCommand(lua_State* L);
	static int addSetMinimumSpawnTimeCommand(lua_State* L);
	static int addSetMoodCommand(lua_State* L);
	static int addSetMoodInternalCommand(lua_State* L);
	static int addSetNameCommand(lua_State* L);
	static int addSetOwnerCommand(lua_State* L);
	static int addSetPerformanceBuffTargetCommand(lua_State* L);
	static int addSetpermissionCommand(lua_State* L);
	static int addSetPlanetLimitCommand(lua_State* L);
	static int addSetPlayerAppearanceCommand(lua_State* L);
	static int addSetPlayerStateCommand(lua_State* L);
	static int addSetprivacyCommand(lua_State* L);
	static int addSetPublicStateCommand(lua_State* L);
	static int addSetRankCommand(lua_State* L);
	static int addSetRetreatCommand(lua_State* L);
	static int addSetSpeedCommand(lua_State* L);
	static int addSetSpokenLanguageCommand(lua_State* L);
	static int addSetSteadyaimCommand(lua_State* L);
	static int addSetTEFCommand(lua_State* L);
	static int addSetVeteranRewardCommand(lua_State* L);
	static int addSetWarcryCommand(lua_State* L);
	static int addSetWaypointActiveStatusCommand(lua_State* L);
	static int addSetWaypointNameCommand(lua_State* L);
	static int addShowCouncilRankCommand(lua_State* L);
	static int addShowDanceVisualsCommand(lua_State* L);
	static int addShowFactionInformationCommand(lua_State* L);
	static int addShowMusicianVisualsCommand(lua_State* L);
	static int addShowPvPRatingCommand(lua_State* L);
	static int addShowSpawnRegionCommand(lua_State* L);
	static int addSitServerCommand(lua_State* L);
	static int addSkillCommand(lua_State* L);
	static int addSmokebombCommand(lua_State* L);
	static int addSniperShotCommand(lua_State* L);
	static int addSnoopCommand(lua_State* L);
	static int addSocialCommand(lua_State* L);
	static int addSocialInternalCommand(lua_State* L);
	static int addSpatialChatCommand(lua_State* L);
	static int addSpatialChatInternalCommand(lua_State* L);
	static int addSpawnStatusCommand(lua_State* L);
	static int addSplitCreditsWithGroupCommand(lua_State* L);
	static int addSpotlightCommand(lua_State* L);
	static int addSprayShotCommand(lua_State* L);
	static int addStandCommand(lua_State* L);
	static int addStartBandCommand(lua_State* L);
	static int addStartCitySpawnerCommand(lua_State* L);
	static int addStartDanceCommand(lua_State* L);
	static int addStartleShot1Command(lua_State* L);
	static int addStartleShot2Command(lua_State* L);
	static int addStartMusicCommand(lua_State* L);
	static int addStartSpawnerCommand(lua_State* L);
	static int addStartTargetSpawnerCommand(lua_State* L);
	static int addStartTraceLoggingCommand(lua_State* L);
	static int addStatCommand(lua_State* L);
	static int addSteadyaimCommand(lua_State* L);
	static int addStopBandCommand(lua_State* L);
	static int addStopBleedingCommand(lua_State* L);
	static int addStopCitySpawnerCommand(lua_State* L);
	static int addStopCraftingSessionCommand(lua_State* L);
	static int addStopDanceCommand(lua_State* L);
	static int addStoplisteningCommand(lua_State* L);
	static int addStopMusicCommand(lua_State* L);
	static int addStoppingShotCommand(lua_State* L);
	static int addStopSpawnerCommand(lua_State* L);
	static int addStopTargetSpawnerCommand(lua_State* L);
	static int addStopTraceLoggingCommand(lua_State* L);
	static int addStopwatchingCommand(lua_State* L);
	static int addStrafeShot1Command(lua_State* L);
	static int addStrafeShot2Command(lua_State* L);
	static int addStrongDiseaseCommand(lua_State* L);
	static int addStrongPoisonCommand(lua_State* L);
	static int addStructurestatusCommand(lua_State* L);
	static int addStunAttackCommand(lua_State* L);
	static int addSuppressionFire1Command(lua_State* L);
	static int addSuppressionFire2Command(lua_State* L);
	static int addSurpriseShotCommand(lua_State* L);
	static int addSurrenderSkillCommand(lua_State* L);
	static int addSurveyCommand(lua_State* L);
	static int addSynchronizedUiListenCommand(lua_State* L);
	static int addSynchronizedUiStopListeningCommand(lua_State* L);
	static int addSystemMessageCommand(lua_State* L);
	static int addTakeCoverCommand(lua_State* L);
	static int addTameCommand(lua_State* L);
	static int addTargetCommand(lua_State* L);
	static int addTauntCommand(lua_State* L);
	static int addTeachCommand(lua_State* L);
	static int addTeleportCommand(lua_State* L);
	static int addTeleportTargetCommand(lua_State* L);
	static int addTeleportToCommand(lua_State* L);
	static int addTellpetCommand(lua_State* L);
	static int addTendDamageCommand(lua_State* L);
	static int addTendDamageToolCommand(lua_State* L);
	static int addTendWoundCommand(lua_State* L);
	static int addTendWoundsToolCommand(lua_State* L);
	static int addThreatenShotCommand(lua_State* L);
	static int addThrowGrenadeCommand(lua_State* L);
	static int addThrowTrapCommand(lua_State* L);
	static int addTipCommand(lua_State* L);
	static int addToggleAwayFromKeyBoardCommand(lua_State* L);
	static int addToggleDisplayingFactionRankCommand(lua_State* L);
	static int addTorsoShotCommand(lua_State* L);
	static int addTotalHealOtherCommand(lua_State* L);
	static int addTotalHealSelfCommand(lua_State* L);
	static int addTransferForceCommand(lua_State* L);
	static int addTransferItemCommand(lua_State* L);
	static int addTransferItemArmorCommand(lua_State* L);
	static int addTransferItemMiscCommand(lua_State* L);
	static int addTransferItemWeaponCommand(lua_State* L);
	static int addTransferstructureCommand(lua_State* L);
	static int addTumbleToKneelingCommand(lua_State* L);
	static int addTumbleToProneCommand(lua_State* L);
	static int addTumbleToStandingCommand(lua_State* L);
	static int addUnarmedBlind1Command(lua_State* L);
	static int addUnarmedBodyHit1Command(lua_State* L);
	static int addUnarmedCombo1Command(lua_State* L);
	static int addUnarmedCombo2Command(lua_State* L);
	static int addUnarmedDizzy1Command(lua_State* L);
	static int addUnarmedHeadHit1Command(lua_State* L);
	static int addUnarmedHit1Command(lua_State* L);
	static int addUnarmedHit2Command(lua_State* L);
	static int addUnarmedHit3Command(lua_State* L);
	static int addUnarmedKnockdown1Command(lua_State* L);
	static int addUnarmedKnockdown2Command(lua_State* L);
	static int addUnarmedLegHit1Command(lua_State* L);
	static int addUnarmedLunge1Command(lua_State* L);
	static int addUnarmedLunge2Command(lua_State* L);
	static int addUnarmedSpinAttack1Command(lua_State* L);
	static int addUnarmedSpinAttack2Command(lua_State* L);
	static int addUnarmedStun1Command(lua_State* L);
	static int addUnassociateDroidControlDeviceWithShipCommand(lua_State* L);
	static int addUnCityBanCommand(lua_State* L);
	static int addUnconsentCommand(lua_State* L);
	static int addUnderHandShotCommand(lua_State* L);
	static int addUnfreezePlayerCommand(lua_State* L);
	static int addUninstallShipComponentCommand(lua_State* L);
	static int addUninviteCommand(lua_State* L);
	static int addUnsnoopCommand(lua_State* L);
	static int addUseReconDroneCommand(lua_State* L);
	static int addUseSkillBuffCommand(lua_State* L);
	static int addVentriloquismCommand(lua_State* L);
	static int addToggleCombatTauntsCommand(lua_State* L);
	static int addVertFurnitureCommand(lua_State* L);
	static int addVitalizeCommand(lua_State* L);
	static int addVolleyFireCommand(lua_State* L);
	static int addVolleyFireAttackCommand(lua_State* L);
	static int addWarcry1Command(lua_State* L);
	static int addWarcry2Command(lua_State* L);
	static int addWarningShotCommand(lua_State* L);
	static int addWatchCommand(lua_State* L);
	static int addWildShot1Command(lua_State* L);
	static int addWildShot2Command(lua_State* L);
	static int addWipeItemsCommand(lua_State* L);
	static int addWookieeRoarCommand(lua_State* L);
	static int addCityInfoCommand(lua_State* L);
	static int addEjectCommand(lua_State* L);
	static int addLaunchIntoSpaceCommand(lua_State* L);
	static int addUnstickCommand(lua_State* L);
	static int addWaypointCommand(lua_State* L);
	static int addCreateVendorCommand(lua_State* L);



};

}
}
}
}
}

using namespace server::zone::managers::objectcontroller::command;



#endif /*SLASHCOMMANDCONFIGMANAGER_H_*/
