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


#include "server/zone/ZoneProcessServerImplementation.h"
#include "CommandList.h"

CommandList* CommandConfigManager::slashCommands = NULL;
ZoneProcessServerImplementation* CommandConfigManager::server = NULL;

CommandConfigManager::CommandConfigManager(ZoneProcessServerImplementation* serv) {
	server = serv;

	init();

	registerFunctions();
	registerGlobals();
}

void CommandConfigManager::registerFunctions() {
	//lua generic
	lua_register(getLuaState(), "RunSlashCommandsFile", runSlashCommandsFile);

	//AddSkills
	lua_register(getLuaState(), "AddActivateCloneSlashCommand", addActivateCloneSlashCommand);
	lua_register(getLuaState(), "AddActivateQuestSlashCommand", addActivateQuestSlashCommand);
	lua_register(getLuaState(), "AddAddAllowedPlayerSlashCommand", addAddAllowedPlayerSlashCommand);
	lua_register(getLuaState(), "AddAddBannedPlayerSlashCommand", addAddBannedPlayerSlashCommand);
	lua_register(getLuaState(), "AddAddFriendSlashCommand", addAddFriendSlashCommand);
	lua_register(getLuaState(), "AddAddIgnoreSlashCommand", addAddIgnoreSlashCommand);
	lua_register(getLuaState(), "AddAddMapLocationSlashCommand", addAddMapLocationSlashCommand);
	lua_register(getLuaState(), "AddAddPowerSlashCommand", addAddPowerSlashCommand);
	lua_register(getLuaState(), "AddAdjustLotCountSlashCommand", addAdjustLotCountSlashCommand);
	lua_register(getLuaState(), "AddAdrenalBoostSlashCommand", addAdrenalBoostSlashCommand);
	lua_register(getLuaState(), "AddAiIgnoreSlashCommand", addAiIgnoreSlashCommand);
	lua_register(getLuaState(), "AddAimSlashCommand", addAimSlashCommand);
	lua_register(getLuaState(), "AddAimedShotSlashCommand", addAimedShotSlashCommand);
	lua_register(getLuaState(), "AddAnonSlashCommand", addAnonSlashCommand);
	lua_register(getLuaState(), "AddApplyPowerupSlashCommand", addApplyPowerupSlashCommand);
	lua_register(getLuaState(), "AddAreaTauntSlashCommand", addAreaTauntSlashCommand);
	lua_register(getLuaState(), "AddAreatrackSlashCommand", addAreatrackSlashCommand);
	lua_register(getLuaState(), "AddArmorBreakSlashCommand", addArmorBreakSlashCommand);
	lua_register(getLuaState(), "AddAssignDroidSlashCommand", addAssignDroidSlashCommand);
	lua_register(getLuaState(), "AddAssociateDroidControlDeviceWithShipSlashCommand", addAssociateDroidControlDeviceWithShipSlashCommand);
	lua_register(getLuaState(), "AddAttackSlashCommand", addAttackSlashCommand);
	lua_register(getLuaState(), "AddAuctionAcceptSlashCommand", addAuctionAcceptSlashCommand);
	lua_register(getLuaState(), "AddAuctionBidSlashCommand", addAuctionBidSlashCommand);
	lua_register(getLuaState(), "AddAuctionCancelSlashCommand", addAuctionCancelSlashCommand);
	lua_register(getLuaState(), "AddAuctionCreateSlashCommand", addAuctionCreateSlashCommand);
	lua_register(getLuaState(), "AddAuctionQuerySlashCommand", addAuctionQuerySlashCommand);
	lua_register(getLuaState(), "AddAuctionRetrieveSlashCommand", addAuctionRetrieveSlashCommand);
	lua_register(getLuaState(), "AddAuctionsaySlashCommand", addAuctionsaySlashCommand);
	lua_register(getLuaState(), "AddAvoidIncapacitationSlashCommand", addAvoidIncapacitationSlashCommand);
	lua_register(getLuaState(), "AddBactaInfusionSlashCommand", addBactaInfusionSlashCommand);
	lua_register(getLuaState(), "AddBactaJabSlashCommand", addBactaJabSlashCommand);
	lua_register(getLuaState(), "AddBactaShotSlashCommand", addBactaShotSlashCommand);
	lua_register(getLuaState(), "AddBactaSpraySlashCommand", addBactaSpraySlashCommand);
	lua_register(getLuaState(), "AddBactaTossSlashCommand", addBactaTossSlashCommand);
	lua_register(getLuaState(), "AddBandageSlashCommand", addBandageSlashCommand);
	lua_register(getLuaState(), "AddBattlefieldStatusSlashCommand", addBattlefieldStatusSlashCommand);
	lua_register(getLuaState(), "AddBerserkSlashCommand", addBerserkSlashCommand);
	lua_register(getLuaState(), "AddBetSlashCommand", addBetSlashCommand);
	lua_register(getLuaState(), "AddBindingStrikeSlashCommand", addBindingStrikeSlashCommand);
	lua_register(getLuaState(), "AddBleedAttackSlashCommand", addBleedAttackSlashCommand);
	lua_register(getLuaState(), "AddBlindAttackSlashCommand", addBlindAttackSlashCommand);
	lua_register(getLuaState(), "AddBlindRecoverySlashCommand", addBlindRecoverySlashCommand);
	lua_register(getLuaState(), "AddBoardShuttleSlashCommand", addBoardShuttleSlashCommand);
	lua_register(getLuaState(), "AddBodyHitSlashCommand", addBodyHitSlashCommand);
	lua_register(getLuaState(), "AddBodyShotSlashCommand", addBodyShotSlashCommand);
	lua_register(getLuaState(), "AddBoostmoraleSlashCommand", addBoostmoraleSlashCommand);
	lua_register(getLuaState(), "AddBroadcastSlashCommand", addBroadcastSlashCommand);
	lua_register(getLuaState(), "AddBroadcastAreaSlashCommand", addBroadcastAreaSlashCommand);
	lua_register(getLuaState(), "AddBroadcastGalaxySlashCommand", addBroadcastGalaxySlashCommand);
	lua_register(getLuaState(), "AddBroadcastPlanetSlashCommand", addBroadcastPlanetSlashCommand);
	lua_register(getLuaState(), "AddBurstRunSlashCommand", addBurstRunSlashCommand);
	lua_register(getLuaState(), "AddBurstShotSlashCommand", addBurstShotSlashCommand);
	lua_register(getLuaState(), "AddCancelCraftingSessionSlashCommand", addCancelCraftingSessionSlashCommand);
	lua_register(getLuaState(), "AddCenterOfBeingSlashCommand", addCenterOfBeingSlashCommand);
	lua_register(getLuaState(), "AddChangeBandMusicSlashCommand", addChangeBandMusicSlashCommand);
	lua_register(getLuaState(), "AddChangeDanceSlashCommand", addChangeDanceSlashCommand);
	lua_register(getLuaState(), "AddChangeMusicSlashCommand", addChangeMusicSlashCommand);
	lua_register(getLuaState(), "AddChannelForceSlashCommand", addChannelForceSlashCommand);
	lua_register(getLuaState(), "AddChargeShotSlashCommand", addChargeShotSlashCommand);
	lua_register(getLuaState(), "AddCheckForceStatusSlashCommand", addCheckForceStatusSlashCommand);
	lua_register(getLuaState(), "AddCitybanSlashCommand", addCitybanSlashCommand);
	lua_register(getLuaState(), "AddCityInfoSlashCommand", addCityInfoSlashCommand);
	lua_register(getLuaState(), "AddCitypardonSlashCommand", addCitypardonSlashCommand);
	lua_register(getLuaState(), "AddClaimVeteranRewardSlashCommand", addClaimVeteranRewardSlashCommand);
	lua_register(getLuaState(), "AddClearCompletedQuestSlashCommand", addClearCompletedQuestSlashCommand);
	lua_register(getLuaState(), "AddClearQueueSlashCommand", addClearQueueSlashCommand);
	lua_register(getLuaState(), "AddClearVeteranRewardSlashCommand", addClearVeteranRewardSlashCommand);
	lua_register(getLuaState(), "AddClientQualifiedForSkillSlashCommand", addClientQualifiedForSkillSlashCommand);
	lua_register(getLuaState(), "AddCloneSlashCommand", addCloneSlashCommand);
	lua_register(getLuaState(), "AddCloseContainerSlashCommand", addCloseContainerSlashCommand);
	lua_register(getLuaState(), "AddCloseLotteryContainerSlashCommand", addCloseLotteryContainerSlashCommand);
	lua_register(getLuaState(), "AddCobSlashCommand", addCobSlashCommand);
	lua_register(getLuaState(), "AddColorlightsSlashCommand", addColorlightsSlashCommand);
	lua_register(getLuaState(), "AddCombatSlashCommand", addCombatSlashCommand);
	lua_register(getLuaState(), "AddCombatEscapeSlashCommand", addCombatEscapeSlashCommand);
	lua_register(getLuaState(), "AddCombatModeCheckSlashCommand", addCombatModeCheckSlashCommand);
	lua_register(getLuaState(), "AddCombatSpamSlashCommand", addCombatSpamSlashCommand);
	lua_register(getLuaState(), "AddCombatTargetSlashCommand", addCombatTargetSlashCommand);
	lua_register(getLuaState(), "AddComboAttackSlashCommand", addComboAttackSlashCommand);
	lua_register(getLuaState(), "AddCompleteQuestSlashCommand", addCompleteQuestSlashCommand);
	lua_register(getLuaState(), "AddConcealSlashCommand", addConcealSlashCommand);
	lua_register(getLuaState(), "AddConcealShotSlashCommand", addConcealShotSlashCommand);
	lua_register(getLuaState(), "AddConcussionShotSlashCommand", addConcussionShotSlashCommand);
	lua_register(getLuaState(), "AddConfusionShotSlashCommand", addConfusionShotSlashCommand);
	lua_register(getLuaState(), "AddConsentSlashCommand", addConsentSlashCommand);
	lua_register(getLuaState(), "AddCorpseSlashCommand", addCorpseSlashCommand);
	lua_register(getLuaState(), "AddCounterAttackSlashCommand", addCounterAttackSlashCommand);
	lua_register(getLuaState(), "AddCountertoxinSlashCommand", addCountertoxinSlashCommand);
	lua_register(getLuaState(), "AddCountertoxinSpraySlashCommand", addCountertoxinSpraySlashCommand);
	lua_register(getLuaState(), "AddCoupDeGraceSlashCommand", addCoupDeGraceSlashCommand);
	lua_register(getLuaState(), "AddCoverSlashCommand", addCoverSlashCommand);
	lua_register(getLuaState(), "AddCoverchargeSlashCommand", addCoverchargeSlashCommand);
	lua_register(getLuaState(), "AddCraftSlashCommand", addCraftSlashCommand);
	lua_register(getLuaState(), "AddCreateCreatureSlashCommand", addCreateCreatureSlashCommand);
	lua_register(getLuaState(), "AddCreateManfSchematicSlashCommand", addCreateManfSchematicSlashCommand);
	lua_register(getLuaState(), "AddCreateMissionElementSlashCommand", addCreateMissionElementSlashCommand);
	lua_register(getLuaState(), "AddCreateNPCSlashCommand", addCreateNPCSlashCommand);
	lua_register(getLuaState(), "AddCreatePrototypeSlashCommand", addCreatePrototypeSlashCommand);
	lua_register(getLuaState(), "AddCreateSpawningElementSlashCommand", addCreateSpawningElementSlashCommand);
	lua_register(getLuaState(), "AddCreateSpawningElementWithDifficultySlashCommand", addCreateSpawningElementWithDifficultySlashCommand);
	lua_register(getLuaState(), "AddCreatureAreaAttackSlashCommand", addCreatureAreaAttackSlashCommand);
	lua_register(getLuaState(), "AddCreatureAreaBleedingSlashCommand", addCreatureAreaBleedingSlashCommand);
	lua_register(getLuaState(), "AddCreatureAreaComboSlashCommand", addCreatureAreaComboSlashCommand);
	lua_register(getLuaState(), "AddCreatureAreaDiseaseSlashCommand", addCreatureAreaDiseaseSlashCommand);
	lua_register(getLuaState(), "AddCreatureAreaKnockdownSlashCommand", addCreatureAreaKnockdownSlashCommand);
	lua_register(getLuaState(), "AddCreatureAreaPoisonSlashCommand", addCreatureAreaPoisonSlashCommand);
	lua_register(getLuaState(), "AddCreatureBlindAttackSlashCommand", addCreatureBlindAttackSlashCommand);
	lua_register(getLuaState(), "AddCreatureDizzyAttackSlashCommand", addCreatureDizzyAttackSlashCommand);
	lua_register(getLuaState(), "AddCreatureIntimidationAttackSlashCommand", addCreatureIntimidationAttackSlashCommand);
	lua_register(getLuaState(), "AddCreatureKnockdownAttackSlashCommand", addCreatureKnockdownAttackSlashCommand);
	lua_register(getLuaState(), "AddCreatureMeleeAttackSlashCommand", addCreatureMeleeAttackSlashCommand);
	lua_register(getLuaState(), "AddCreaturePostureDownAttackSlashCommand", addCreaturePostureDownAttackSlashCommand);
	lua_register(getLuaState(), "AddCreaturePostureUpAttackSlashCommand", addCreaturePostureUpAttackSlashCommand);
	lua_register(getLuaState(), "AddCreatureRangedAttackSlashCommand", addCreatureRangedAttackSlashCommand);
	lua_register(getLuaState(), "AddCreatureStunAttackSlashCommand", addCreatureStunAttackSlashCommand);
	lua_register(getLuaState(), "AddCreditsSlashCommand", addCreditsSlashCommand);
	lua_register(getLuaState(), "AddCrippleAttackSlashCommand", addCrippleAttackSlashCommand);
	lua_register(getLuaState(), "AddCripplingShotSlashCommand", addCripplingShotSlashCommand);
	lua_register(getLuaState(), "AddCriticalShotSlashCommand", addCriticalShotSlashCommand);
	lua_register(getLuaState(), "AddCriticalStrikeSlashCommand", addCriticalStrikeSlashCommand);
	lua_register(getLuaState(), "AddCsAppendCommentSlashCommand", addCsAppendCommentSlashCommand);
	lua_register(getLuaState(), "AddCsCancelTicketSlashCommand", addCsCancelTicketSlashCommand);
	lua_register(getLuaState(), "AddCsConnectPlayerSlashCommand", addCsConnectPlayerSlashCommand);
	lua_register(getLuaState(), "AddCsCreateTicketSlashCommand", addCsCreateTicketSlashCommand);
	lua_register(getLuaState(), "AddCsDisconnectPlayerSlashCommand", addCsDisconnectPlayerSlashCommand);
	lua_register(getLuaState(), "AddCsGetArticleSlashCommand", addCsGetArticleSlashCommand);
	lua_register(getLuaState(), "AddCsGetCommentsSlashCommand", addCsGetCommentsSlashCommand);
	lua_register(getLuaState(), "AddCsGetTicketsSlashCommand", addCsGetTicketsSlashCommand);
	lua_register(getLuaState(), "AddCsRequestCategoriesSlashCommand", addCsRequestCategoriesSlashCommand);
	lua_register(getLuaState(), "AddCsSearchKnowledgeBaseSlashCommand", addCsSearchKnowledgeBaseSlashCommand);
	lua_register(getLuaState(), "AddCuiConsentResponseSlashCommand", addCuiConsentResponseSlashCommand);
	lua_register(getLuaState(), "AddCustomizeDroidSlashCommand", addCustomizeDroidSlashCommand);
	lua_register(getLuaState(), "AddCustomizeVehicleSlashCommand", addCustomizeVehicleSlashCommand);
	lua_register(getLuaState(), "AddCyborgBurstRunSlashCommand", addCyborgBurstRunSlashCommand);
	lua_register(getLuaState(), "AddCyborgCriticalSnipeSlashCommand", addCyborgCriticalSnipeSlashCommand);
	lua_register(getLuaState(), "AddCyborgKickDownSlashCommand", addCyborgKickDownSlashCommand);
	lua_register(getLuaState(), "AddCyborgLightningSlashCommand", addCyborgLightningSlashCommand);
	lua_register(getLuaState(), "AddCyborgReviveSlashCommand", addCyborgReviveSlashCommand);
	lua_register(getLuaState(), "AddCyborgStrengthBuffSlashCommand", addCyborgStrengthBuffSlashCommand);
	lua_register(getLuaState(), "AddCyborgSureShotSlashCommand", addCyborgSureShotSlashCommand);
	lua_register(getLuaState(), "AddDatabaseSlashCommand", addDatabaseSlashCommand);
	lua_register(getLuaState(), "AddDazzleSlashCommand", addDazzleSlashCommand);
	lua_register(getLuaState(), "AddDeactivateQuestSlashCommand", addDeactivateQuestSlashCommand);
	lua_register(getLuaState(), "AddDeathBlowSlashCommand", addDeathBlowSlashCommand);
	lua_register(getLuaState(), "AddDeathCountSlashCommand", addDeathCountSlashCommand);
	lua_register(getLuaState(), "AddDeclareOvertSlashCommand", addDeclareOvertSlashCommand);
	lua_register(getLuaState(), "AddDeclareresidenceSlashCommand", addDeclareresidenceSlashCommand);
	lua_register(getLuaState(), "AddDeclineSlashCommand", addDeclineSlashCommand);
	lua_register(getLuaState(), "AddDecontaminateSlashCommand", addDecontaminateSlashCommand);
	lua_register(getLuaState(), "AddDefaultActionSlashCommand", addDefaultActionSlashCommand);
	lua_register(getLuaState(), "AddDefaultAttackSlashCommand", addDefaultAttackSlashCommand);
	lua_register(getLuaState(), "AddDefuseMinefieldSlashCommand", addDefuseMinefieldSlashCommand);
	lua_register(getLuaState(), "AddDelegateFactionPointsSlashCommand", addDelegateFactionPointsSlashCommand);
	lua_register(getLuaState(), "AddDenyServiceSlashCommand", addDenyServiceSlashCommand);
	lua_register(getLuaState(), "AddDeployTrapSlashCommand", addDeployTrapSlashCommand);
	lua_register(getLuaState(), "AddDestroySlashCommand", addDestroySlashCommand);
	lua_register(getLuaState(), "AddDestroystructureSlashCommand", addDestroystructureSlashCommand);
	lua_register(getLuaState(), "AddDetonateDroidSlashCommand", addDetonateDroidSlashCommand);
	lua_register(getLuaState(), "AddDeuteriumTossSlashCommand", addDeuteriumTossSlashCommand);
	lua_register(getLuaState(), "AddDiagnoseSlashCommand", addDiagnoseSlashCommand);
	lua_register(getLuaState(), "AddDisarmingShotSlashCommand", addDisarmingShotSlashCommand);
	lua_register(getLuaState(), "AddDisbandSlashCommand", addDisbandSlashCommand);
	lua_register(getLuaState(), "AddDiseaseInnoculationSlashCommand", addDiseaseInnoculationSlashCommand);
	lua_register(getLuaState(), "AddDisinfectSlashCommand", addDisinfectSlashCommand);
	lua_register(getLuaState(), "AddDismissGroupMemberSlashCommand", addDismissGroupMemberSlashCommand);
	lua_register(getLuaState(), "AddDismountSlashCommand", addDismountSlashCommand);
	lua_register(getLuaState(), "AddDismountandstoreSlashCommand", addDismountandstoreSlashCommand);
	lua_register(getLuaState(), "AddDistractSlashCommand", addDistractSlashCommand);
	lua_register(getLuaState(), "AddDiveShotSlashCommand", addDiveShotSlashCommand);
	lua_register(getLuaState(), "AddDizzyAttackSlashCommand", addDizzyAttackSlashCommand);
	lua_register(getLuaState(), "AddDizzyRecoverySlashCommand", addDizzyRecoverySlashCommand);
	lua_register(getLuaState(), "AddDominateMindSlashCommand", addDominateMindSlashCommand);
	lua_register(getLuaState(), "AddDragPlayerSlashCommand", addDragPlayerSlashCommand);
	lua_register(getLuaState(), "AddDrainForceSlashCommand", addDrainForceSlashCommand);
	lua_register(getLuaState(), "AddDuelSlashCommand", addDuelSlashCommand);
	lua_register(getLuaState(), "AddDuelistStanceSlashCommand", addDuelistStanceSlashCommand);
	lua_register(getLuaState(), "AddDumpTargetInformationSlashCommand", addDumpTargetInformationSlashCommand);
	lua_register(getLuaState(), "AddDumpZoneInformationSlashCommand", addDumpZoneInformationSlashCommand);
	lua_register(getLuaState(), "AddEatSlashCommand", addEatSlashCommand);
	lua_register(getLuaState(), "AddEditAppearanceSlashCommand", addEditAppearanceSlashCommand);
	lua_register(getLuaState(), "AddEditBankSlashCommand", addEditBankSlashCommand);
	lua_register(getLuaState(), "AddEditBankAccountSlashCommand", addEditBankAccountSlashCommand);
	lua_register(getLuaState(), "AddEditStatsSlashCommand", addEditStatsSlashCommand);
	lua_register(getLuaState(), "AddElectrolyteDrainSlashCommand", addElectrolyteDrainSlashCommand);
	lua_register(getLuaState(), "AddEmboldenpetsSlashCommand", addEmboldenpetsSlashCommand);
	lua_register(getLuaState(), "AddEmptyMailTargetSlashCommand", addEmptyMailTargetSlashCommand);
	lua_register(getLuaState(), "AddEndDuelSlashCommand", addEndDuelSlashCommand);
	lua_register(getLuaState(), "AddEndorphineInjectionSlashCommand", addEndorphineInjectionSlashCommand);
	lua_register(getLuaState(), "AddEnragepetsSlashCommand", addEnragepetsSlashCommand);
	lua_register(getLuaState(), "AddEquilibriumSlashCommand", addEquilibriumSlashCommand);
	lua_register(getLuaState(), "AddExecuteKnowledgeBaseMessageSlashCommand", addExecuteKnowledgeBaseMessageSlashCommand);
	lua_register(getLuaState(), "AddExtinguishFireSlashCommand", addExtinguishFireSlashCommand);
	lua_register(getLuaState(), "AddExtractObjectSlashCommand", addExtractObjectSlashCommand);
	lua_register(getLuaState(), "AddEyeShotSlashCommand", addEyeShotSlashCommand);
	lua_register(getLuaState(), "AddFactoryCrateSplitSlashCommand", addFactoryCrateSplitSlashCommand);
	lua_register(getLuaState(), "AddFanShotSlashCommand", addFanShotSlashCommand);
	lua_register(getLuaState(), "AddFeignDeathSlashCommand", addFeignDeathSlashCommand);
	lua_register(getLuaState(), "AddFindSlashCommand", addFindSlashCommand);
	lua_register(getLuaState(), "AddFindFriendSlashCommand", addFindFriendSlashCommand);
	lua_register(getLuaState(), "AddFindMyTrainerSlashCommand", addFindMyTrainerSlashCommand);
	lua_register(getLuaState(), "AddFindObjectSlashCommand", addFindObjectSlashCommand);
	lua_register(getLuaState(), "AddFindPlayerSlashCommand", addFindPlayerSlashCommand);
	lua_register(getLuaState(), "AddFirearmStrikeSlashCommand", addFirearmStrikeSlashCommand);
	lua_register(getLuaState(), "AddFirejetSlashCommand", addFirejetSlashCommand);
	lua_register(getLuaState(), "AddFishSlashCommand", addFishSlashCommand);
	lua_register(getLuaState(), "AddFlashSpeederSlashCommand", addFlashSpeederSlashCommand);
	lua_register(getLuaState(), "AddFlourishSlashCommand", addFlourishSlashCommand);
	lua_register(getLuaState(), "AddForageSlashCommand", addForageSlashCommand);
	lua_register(getLuaState(), "AddForceAbsorbSlashCommand", addForceAbsorbSlashCommand);
	lua_register(getLuaState(), "AddForceArmorSlashCommand", addForceArmorSlashCommand);
	lua_register(getLuaState(), "AddForceAuraSlashCommand", addForceAuraSlashCommand);
	lua_register(getLuaState(), "AddForceBreachSlashCommand", addForceBreachSlashCommand);
	lua_register(getLuaState(), "AddForceChokeSlashCommand", addForceChokeSlashCommand);
	lua_register(getLuaState(), "AddForceCloakSlashCommand", addForceCloakSlashCommand);
	lua_register(getLuaState(), "AddForceCommandSlashCommand", addForceCommandSlashCommand);
	lua_register(getLuaState(), "AddForceCureDiseaseSlashCommand", addForceCureDiseaseSlashCommand);
	lua_register(getLuaState(), "AddForceCurePoisonSlashCommand", addForceCurePoisonSlashCommand);
	lua_register(getLuaState(), "AddForceExtinguishSlashCommand", addForceExtinguishSlashCommand);
	lua_register(getLuaState(), "AddForceFeedbackSlashCommand", addForceFeedbackSlashCommand);
	lua_register(getLuaState(), "AddForceHealSlashCommand", addForceHealSlashCommand);
	lua_register(getLuaState(), "AddForceHitSlashCommand", addForceHitSlashCommand);
	lua_register(getLuaState(), "AddForceInfusionSlashCommand", addForceInfusionSlashCommand);
	lua_register(getLuaState(), "AddForceIntimidateSlashCommand", addForceIntimidateSlashCommand);
	lua_register(getLuaState(), "AddForceKnockdownSlashCommand", addForceKnockdownSlashCommand);
	lua_register(getLuaState(), "AddForceLightningSlashCommand", addForceLightningSlashCommand);
	lua_register(getLuaState(), "AddForceLightningAreaSlashCommand", addForceLightningAreaSlashCommand);
	lua_register(getLuaState(), "AddForceMeditateSlashCommand", addForceMeditateSlashCommand);
	lua_register(getLuaState(), "AddForceOfWillSlashCommand", addForceOfWillSlashCommand);
	lua_register(getLuaState(), "AddForceResistBleedingSlashCommand", addForceResistBleedingSlashCommand);
	lua_register(getLuaState(), "AddForceResistDiseaseSlashCommand", addForceResistDiseaseSlashCommand);
	lua_register(getLuaState(), "AddForceResistPoisonSlashCommand", addForceResistPoisonSlashCommand);
	lua_register(getLuaState(), "AddForceResistStatesSlashCommand", addForceResistStatesSlashCommand);
	lua_register(getLuaState(), "AddForceRunSlashCommand", addForceRunSlashCommand);
	lua_register(getLuaState(), "AddForceSapSlashCommand", addForceSapSlashCommand);
	lua_register(getLuaState(), "AddForceShieldSlashCommand", addForceShieldSlashCommand);
	lua_register(getLuaState(), "AddForceShockSlashCommand", addForceShockSlashCommand);
	lua_register(getLuaState(), "AddForceSpeedSlashCommand", addForceSpeedSlashCommand);
	lua_register(getLuaState(), "AddForceStrikeSlashCommand", addForceStrikeSlashCommand);
	lua_register(getLuaState(), "AddForceSuppressionSlashCommand", addForceSuppressionSlashCommand);
	lua_register(getLuaState(), "AddForceThrowSlashCommand", addForceThrowSlashCommand);
	lua_register(getLuaState(), "AddForceValorSlashCommand", addForceValorSlashCommand);
	lua_register(getLuaState(), "AddForceWaveSlashCommand", addForceWaveSlashCommand);
	lua_register(getLuaState(), "AddForceWeakenSlashCommand", addForceWeakenSlashCommand);
	lua_register(getLuaState(), "AddForceWoundHealSlashCommand", addForceWoundHealSlashCommand);
	lua_register(getLuaState(), "AddFormupSlashCommand", addFormupSlashCommand);
	lua_register(getLuaState(), "AddFreezePlayerSlashCommand", addFreezePlayerSlashCommand);
	lua_register(getLuaState(), "AddFullAutoAreaSlashCommand", addFullAutoAreaSlashCommand);
	//lua_register(getLuaState(), "AddGSlashCommand", addGSlashCommand);
	lua_register(getLuaState(), "AddGallopSlashCommand", addGallopSlashCommand);
	lua_register(getLuaState(), "AddGallopStopSlashCommand", addGallopStopSlashCommand);
	//lua_register(getLuaState(), "AddGcSlashCommand", addGcSlashCommand);
	lua_register(getLuaState(), "AddGcwStatusSlashCommand", addGcwStatusSlashCommand);
	lua_register(getLuaState(), "AddGenerateCraftedItemSlashCommand", addGenerateCraftedItemSlashCommand);
	lua_register(getLuaState(), "AddGetAccountInfoSlashCommand", addGetAccountInfoSlashCommand);
	lua_register(getLuaState(), "AddGetAttributesSlashCommand", addGetAttributesSlashCommand);
	lua_register(getLuaState(), "AddGetAttributesBatchSlashCommand", addGetAttributesBatchSlashCommand);
	lua_register(getLuaState(), "AddGetFriendListSlashCommand", addGetFriendListSlashCommand);
	lua_register(getLuaState(), "AddGetGameTimeSlashCommand", addGetGameTimeSlashCommand);
	lua_register(getLuaState(), "AddGetIgnoreListSlashCommand", addGetIgnoreListSlashCommand);
	lua_register(getLuaState(), "AddGetMapLocationsSlashCommand", addGetMapLocationsSlashCommand);
	lua_register(getLuaState(), "AddGetObjVarsSlashCommand", addGetObjVarsSlashCommand);
	lua_register(getLuaState(), "AddGetPlayerIdSlashCommand", addGetPlayerIdSlashCommand);
	lua_register(getLuaState(), "AddGetPrototypeSlashCommand", addGetPrototypeSlashCommand);
	lua_register(getLuaState(), "AddGetRankSlashCommand", addGetRankSlashCommand);
	lua_register(getLuaState(), "AddGetSpawnDelaysSlashCommand", addGetSpawnDelaysSlashCommand);
	lua_register(getLuaState(), "AddGetStationNameSlashCommand", addGetStationNameSlashCommand);
	lua_register(getLuaState(), "AddGetVeteranRewardTimeSlashCommand", addGetVeteranRewardTimeSlashCommand);
	lua_register(getLuaState(), "AddGetVeteranRewardTimeCsSlashCommand", addGetVeteranRewardTimeCsSlashCommand);
	lua_register(getLuaState(), "AddGiveItemSlashCommand", addGiveItemSlashCommand);
	lua_register(getLuaState(), "AddGiveMaintenanceToVendorSlashCommand", addGiveMaintenanceToVendorSlashCommand);
	lua_register(getLuaState(), "AddGivevendormaintSlashCommand", addGivevendormaintSlashCommand);
	lua_register(getLuaState(), "AddGmCreateClassResourceSlashCommand", addGmCreateClassResourceSlashCommand);
	lua_register(getLuaState(), "AddGmCreateSpecificResourceSlashCommand", addGmCreateSpecificResourceSlashCommand);
	lua_register(getLuaState(), "AddGmForceCommandSlashCommand", addGmForceCommandSlashCommand);
	lua_register(getLuaState(), "AddGmForceRankSlashCommand", addGmForceRankSlashCommand);
	lua_register(getLuaState(), "AddGmFsVillageSlashCommand", addGmFsVillageSlashCommand);
	lua_register(getLuaState(), "AddGmJediStateSlashCommand", addGmJediStateSlashCommand);
	lua_register(getLuaState(), "AddGmReviveSlashCommand", addGmReviveSlashCommand);
	lua_register(getLuaState(), "AddGmWeaponSlashCommand", addGmWeaponSlashCommand);
	lua_register(getLuaState(), "AddGotoSlashCommand", addGotoSlashCommand);
	lua_register(getLuaState(), "AddGrantBadgeSlashCommand", addGrantBadgeSlashCommand);
	lua_register(getLuaState(), "AddGrantPadawanTrialsEligibilitySlashCommand", addGrantPadawanTrialsEligibilitySlashCommand);
	lua_register(getLuaState(), "AddGrantSkillSlashCommand", addGrantSkillSlashCommand);
	lua_register(getLuaState(), "AddGrantTitleSlashCommand", addGrantTitleSlashCommand);
	lua_register(getLuaState(), "AddGrantZoningRightsSlashCommand", addGrantZoningRightsSlashCommand);
	lua_register(getLuaState(), "AddGroupChatSlashCommand", addGroupChatSlashCommand);
	lua_register(getLuaState(), "AddGroupLootSlashCommand", addGroupLootSlashCommand);
	//lua_register(getLuaState(), "AddGroupSaySlashCommand", addGroupSaySlashCommand);
	//lua_register(getLuaState(), "AddGsaySlashCommand", addGsaySlashCommand);
	//lua_register(getLuaState(), "AddGtellSlashCommand", addGtellSlashCommand);
	//lua_register(getLuaState(), "AddGuildSlashCommand", addGuildSlashCommand);
	lua_register(getLuaState(), "AddGuildRemoveSlashCommand", addGuildRemoveSlashCommand);
	lua_register(getLuaState(), "AddGuildsaySlashCommand", addGuildsaySlashCommand);
	lua_register(getLuaState(), "AddGuildstatusSlashCommand", addGuildstatusSlashCommand);
	lua_register(getLuaState(), "AddHandleClientLoginSlashCommand", addHandleClientLoginSlashCommand);
	lua_register(getLuaState(), "AddHarmfulSlashCommand", addHarmfulSlashCommand);
	lua_register(getLuaState(), "AddHarmlessSlashCommand", addHarmlessSlashCommand);
	lua_register(getLuaState(), "AddHarvestCorpseSlashCommand", addHarvestCorpseSlashCommand);
	lua_register(getLuaState(), "AddHarvesterActivateSlashCommand", addHarvesterActivateSlashCommand);
	lua_register(getLuaState(), "AddHarvesterDeactivateSlashCommand", addHarvesterDeactivateSlashCommand);
	lua_register(getLuaState(), "AddHarvesterDiscardHopperSlashCommand", addHarvesterDiscardHopperSlashCommand);
	lua_register(getLuaState(), "AddHarvesterGetResourceDataSlashCommand", addHarvesterGetResourceDataSlashCommand);
	lua_register(getLuaState(), "AddHarvesterHarvestSlashCommand", addHarvesterHarvestSlashCommand);
	lua_register(getLuaState(), "AddHarvesterMakeCrateSlashCommand", addHarvesterMakeCrateSlashCommand);
	lua_register(getLuaState(), "AddHarvesterSelectResourceSlashCommand", addHarvesterSelectResourceSlashCommand);
	lua_register(getLuaState(), "AddHarvesterTakeSurveySlashCommand", addHarvesterTakeSurveySlashCommand);
	lua_register(getLuaState(), "AddHasVeteranRewardSlashCommand", addHasVeteranRewardSlashCommand);
	lua_register(getLuaState(), "AddHaveconsentSlashCommand", addHaveconsentSlashCommand);
	lua_register(getLuaState(), "AddHeadHitSlashCommand", addHeadHitSlashCommand);
	lua_register(getLuaState(), "AddHeadShotSlashCommand", addHeadShotSlashCommand);
	lua_register(getLuaState(), "AddHealDroidDamageSlashCommand", addHealDroidDamageSlashCommand);
	lua_register(getLuaState(), "AddHealDroidWoundSlashCommand", addHealDroidWoundSlashCommand);
	lua_register(getLuaState(), "AddHealPetSlashCommand", addHealPetSlashCommand);
	lua_register(getLuaState(), "AddHealStatesSlashCommand", addHealStatesSlashCommand);
	lua_register(getLuaState(), "AddHealWoundSlashCommand", addHealWoundSlashCommand);
	lua_register(getLuaState(), "AddHemorrhageSlashCommand", addHemorrhageSlashCommand);
	lua_register(getLuaState(), "AddHoloEmoteSlashCommand", addHoloEmoteSlashCommand);
	lua_register(getLuaState(), "AddImagedesignSlashCommand", addImagedesignSlashCommand);
	lua_register(getLuaState(), "AddImpaleSlashCommand", addImpaleSlashCommand);
	lua_register(getLuaState(), "AddInfectSlashCommand", addInfectSlashCommand);
	lua_register(getLuaState(), "AddInitializeComponentSlashCommand", addInitializeComponentSlashCommand);
	lua_register(getLuaState(), "AddInnateSlashCommand", addInnateSlashCommand);
	lua_register(getLuaState(), "AddInsertItemIntoShipComponentSlotSlashCommand", addInsertItemIntoShipComponentSlotSlashCommand);
	lua_register(getLuaState(), "AddInstallMissionTerminalSlashCommand", addInstallMissionTerminalSlashCommand);
	lua_register(getLuaState(), "AddInstallShipComponentSlashCommand", addInstallShipComponentSlashCommand);
	lua_register(getLuaState(), "AddInsureSlashCommand", addInsureSlashCommand);
	lua_register(getLuaState(), "AddIntimidateSlashCommand", addIntimidateSlashCommand);
	lua_register(getLuaState(), "AddIntimidateShotSlashCommand", addIntimidateShotSlashCommand);
	lua_register(getLuaState(), "AddInviteSlashCommand", addInviteSlashCommand);
	lua_register(getLuaState(), "AddInvulnerableSlashCommand", addInvulnerableSlashCommand);
	lua_register(getLuaState(), "AddItemmovebackSlashCommand", addItemmovebackSlashCommand);
	lua_register(getLuaState(), "AddItemmovedownSlashCommand", addItemmovedownSlashCommand);
	lua_register(getLuaState(), "AddItemmoveforwardSlashCommand", addItemmoveforwardSlashCommand);
	lua_register(getLuaState(), "AddItemmoveupSlashCommand", addItemmoveupSlashCommand);
	lua_register(getLuaState(), "AddItemrotateleftSlashCommand", addItemrotateleftSlashCommand);
	lua_register(getLuaState(), "AddItemrotaterightSlashCommand", addItemrotaterightSlashCommand);
	lua_register(getLuaState(), "AddJoinSlashCommand", addJoinSlashCommand);
	lua_register(getLuaState(), "AddJoinGameSlashCommand", addJoinGameSlashCommand);
	lua_register(getLuaState(), "AddKickSlashCommand", addKickSlashCommand);
	lua_register(getLuaState(), "AddKillSlashCommand", addKillSlashCommand);
	lua_register(getLuaState(), "AddKillPlayerSlashCommand", addKillPlayerSlashCommand);
	lua_register(getLuaState(), "AddKipUpShotSlashCommand", addKipUpShotSlashCommand);
	lua_register(getLuaState(), "AddKneecapShotSlashCommand", addKneecapShotSlashCommand);
	lua_register(getLuaState(), "AddKneelSlashCommand", addKneelSlashCommand);
	lua_register(getLuaState(), "AddKnockdownRecoverySlashCommand", addKnockdownRecoverySlashCommand);
	lua_register(getLuaState(), "AddLagSlashCommand", addLagSlashCommand);
	lua_register(getLuaState(), "AddLastDitchSlashCommand", addLastDitchSlashCommand);
	lua_register(getLuaState(), "AddLaunchFireworkSlashCommand", addLaunchFireworkSlashCommand);
	lua_register(getLuaState(), "AddLeaveGameSlashCommand", addLeaveGameSlashCommand);
	lua_register(getLuaState(), "AddLeaveGroupSlashCommand", addLeaveGroupSlashCommand);
	lua_register(getLuaState(), "AddLegHitSlashCommand", addLegHitSlashCommand);
	lua_register(getLuaState(), "AddLegShotSlashCommand", addLegShotSlashCommand);
	lua_register(getLuaState(), "AddLegSweepSlashCommand", addLegSweepSlashCommand);
	lua_register(getLuaState(), "AddLethalShotSlashCommand", addLethalShotSlashCommand);
	lua_register(getLuaState(), "AddLfgSlashCommand", addLfgSlashCommand);
	lua_register(getLuaState(), "AddListActiveQuestsSlashCommand", addListActiveQuestsSlashCommand);
	lua_register(getLuaState(), "AddListCompletedQuestsSlashCommand", addListCompletedQuestsSlashCommand);
	lua_register(getLuaState(), "AddListenSlashCommand", addListenSlashCommand);
	lua_register(getLuaState(), "AddListGuildsSlashCommand", addListGuildsSlashCommand);
	lua_register(getLuaState(), "AddLogoutServerSlashCommand", addLogoutServerSlashCommand);
	lua_register(getLuaState(), "AddLootAllSlashCommand", addLootAllSlashCommand);
	lua_register(getLuaState(), "AddLootSlashCommand", addLootSlashCommand);
	lua_register(getLuaState(), "AddLootPlayerCorpseSlashCommand", addLootPlayerCorpseSlashCommand);
	lua_register(getLuaState(), "AddLowBlowSlashCommand", addLowBlowSlashCommand);
	lua_register(getLuaState(), "AddLungeSlashCommand", addLungeSlashCommand);
	lua_register(getLuaState(), "AddMakeLeaderSlashCommand", addMakeLeaderSlashCommand);
	lua_register(getLuaState(), "AddMakeMasterLooterSlashCommand", addMakeMasterLooterSlashCommand);
	lua_register(getLuaState(), "AddMakeSurveySlashCommand", addMakeSurveySlashCommand);
	lua_register(getLuaState(), "AddManufactureSlashCommand", addManufactureSlashCommand);
	lua_register(getLuaState(), "AddMaskscentSlashCommand", addMaskscentSlashCommand);
	lua_register(getLuaState(), "AddMaxCombatAbilitySlashCommand", addMaxCombatAbilitySlashCommand);
	lua_register(getLuaState(), "AddMaxStatsSlashCommand", addMaxStatsSlashCommand);
	lua_register(getLuaState(), "AddMedicalForageSlashCommand", addMedicalForageSlashCommand);
	lua_register(getLuaState(), "AddMeditateSlashCommand", addMeditateSlashCommand);
	lua_register(getLuaState(), "AddMeleeAssaultSlashCommand", addMeleeAssaultSlashCommand);
	lua_register(getLuaState(), "AddMeleeHitSlashCommand", addMeleeHitSlashCommand);
	lua_register(getLuaState(), "AddMeleeStrikeSlashCommand", addMeleeStrikeSlashCommand);
	lua_register(getLuaState(), "AddMindBlastSlashCommand", addMindBlastSlashCommand);
	lua_register(getLuaState(), "AddMoneySlashCommand", addMoneySlashCommand);
	lua_register(getLuaState(), "AddMountSlashCommand", addMountSlashCommand);
	lua_register(getLuaState(), "AddMoveFurnitureSlashCommand", addMoveFurnitureSlashCommand);
	lua_register(getLuaState(), "AddNameStructureSlashCommand", addNameStructureSlashCommand);
	lua_register(getLuaState(), "AddNeurotoxinSlashCommand", addNeurotoxinSlashCommand);
	lua_register(getLuaState(), "AddNewbiehelperSlashCommand", addNewbiehelperSlashCommand);
	lua_register(getLuaState(), "AddNewbieRequestStartingLocationsSlashCommand", addNewbieRequestStartingLocationsSlashCommand);
	lua_register(getLuaState(), "AddNewbieSelectStartingLocationSlashCommand", addNewbieSelectStartingLocationSlashCommand);
	lua_register(getLuaState(), "AddNextCraftingStageSlashCommand", addNextCraftingStageSlashCommand);
	lua_register(getLuaState(), "AddNpcSlashCommand", addNpcSlashCommand);
	lua_register(getLuaState(), "AddNpcConversationSelectSlashCommand", addNpcConversationSelectSlashCommand);
	lua_register(getLuaState(), "AddNpcConversationStartSlashCommand", addNpcConversationStartSlashCommand);
	lua_register(getLuaState(), "AddNpcConversationStopSlashCommand", addNpcConversationStopSlashCommand);
	lua_register(getLuaState(), "AddNutrientInjectionSlashCommand", addNutrientInjectionSlashCommand);
	lua_register(getLuaState(), "AddObjectSlashCommand", addObjectSlashCommand);
	lua_register(getLuaState(), "AddObjvarSlashCommand", addObjvarSlashCommand);
	lua_register(getLuaState(), "AddOpenContainerSlashCommand", addOpenContainerSlashCommand);
	lua_register(getLuaState(), "AddOpenLotteryContainerSlashCommand", addOpenLotteryContainerSlashCommand);
	lua_register(getLuaState(), "AddOverchargeShotSlashCommand", addOverchargeShotSlashCommand);
	lua_register(getLuaState(), "AddOverrideActiveMonthsSlashCommand", addOverrideActiveMonthsSlashCommand);
	lua_register(getLuaState(), "AddOverridePadawanTrialsEligibilitySlashCommand", addOverridePadawanTrialsEligibilitySlashCommand);
	lua_register(getLuaState(), "AddOverwhelmingShotSlashCommand", addOverwhelmingShotSlashCommand);
	lua_register(getLuaState(), "AddPanicShotSlashCommand", addPanicShotSlashCommand);
	lua_register(getLuaState(), "AddParalyzeSlashCommand", addParalyzeSlashCommand);
	lua_register(getLuaState(), "AddParryRiposteSlashCommand", addParryRiposteSlashCommand);
	lua_register(getLuaState(), "AddPauseDanceSlashCommand", addPauseDanceSlashCommand);
	lua_register(getLuaState(), "AddPauseMusicSlashCommand", addPauseMusicSlashCommand);
	lua_register(getLuaState(), "AddPaWithdrawSlashCommand", addPaWithdrawSlashCommand);
	lua_register(getLuaState(), "AddPaymaintenanceSlashCommand", addPaymaintenanceSlashCommand);
	lua_register(getLuaState(), "AddPeaceSlashCommand", addPeaceSlashCommand);
	lua_register(getLuaState(), "AddPermissionListModifySlashCommand", addPermissionListModifySlashCommand);
	lua_register(getLuaState(), "AddPistolWhipSlashCommand", addPistolWhipSlashCommand);
	lua_register(getLuaState(), "AddPlaceBattlefieldStructureSlashCommand", addPlaceBattlefieldStructureSlashCommand);
	lua_register(getLuaState(), "AddPlacedShotSlashCommand", addPlacedShotSlashCommand);
	lua_register(getLuaState(), "AddPlaceStructureSlashCommand", addPlaceStructureSlashCommand);
	lua_register(getLuaState(), "AddPlaceStructureModeSlashCommand", addPlaceStructureModeSlashCommand);
	lua_register(getLuaState(), "AddPlanetsaySlashCommand", addPlanetsaySlashCommand);
	lua_register(getLuaState(), "AddPlanetwarpSlashCommand", addPlanetwarpSlashCommand);
	lua_register(getLuaState(), "AddPlanetwarpTargetSlashCommand", addPlanetwarpTargetSlashCommand);
	lua_register(getLuaState(), "AddPointBlankAreaSlashCommand", addPointBlankAreaSlashCommand);
	lua_register(getLuaState(), "AddPointBlankShotSlashCommand", addPointBlankShotSlashCommand);
	lua_register(getLuaState(), "AddPoisonInnoculationSlashCommand", addPoisonInnoculationSlashCommand);
	lua_register(getLuaState(), "AddPowerAttackSlashCommand", addPowerAttackSlashCommand);
	lua_register(getLuaState(), "AddPowerBoostSlashCommand", addPowerBoostSlashCommand);
	lua_register(getLuaState(), "AddProneSlashCommand", addProneSlashCommand);
	lua_register(getLuaState(), "AddPurchaseReinforcementSlashCommand", addPurchaseReinforcementSlashCommand);
	lua_register(getLuaState(), "AddPurchaseTicketSlashCommand", addPurchaseTicketSlashCommand);
	lua_register(getLuaState(), "AddQuickDrawSlashCommand", addQuickDrawSlashCommand);
	lua_register(getLuaState(), "AddRallySlashCommand", addRallySlashCommand);
	lua_register(getLuaState(), "AddRangedShotSlashCommand", addRangedShotSlashCommand);
	lua_register(getLuaState(), "AddRapidFireSlashCommand", addRapidFireSlashCommand);
	lua_register(getLuaState(), "AddRecklessShotSlashCommand", addRecklessShotSlashCommand);
	lua_register(getLuaState(), "AddReconnectToTransferServerSlashCommand", addReconnectToTransferServerSlashCommand);
	lua_register(getLuaState(), "AddRecruitSkillTrainerSlashCommand", addRecruitSkillTrainerSlashCommand);
	lua_register(getLuaState(), "AddRegainConsciousnessSlashCommand", addRegainConsciousnessSlashCommand);
	lua_register(getLuaState(), "AddRegenerationSlashCommand", addRegenerationSlashCommand);
	lua_register(getLuaState(), "AddRegisterWithLocationSlashCommand", addRegisterWithLocationSlashCommand);
	lua_register(getLuaState(), "AddReloadSlashCommand", addReloadSlashCommand);
	lua_register(getLuaState(), "AddRemoteSlashCommand", addRemoteSlashCommand);
	lua_register(getLuaState(), "AddRemoveAllowedPlayerSlashCommand", addRemoveAllowedPlayerSlashCommand);
	lua_register(getLuaState(), "AddRemoveBannedPlayerSlashCommand", addRemoveBannedPlayerSlashCommand);
	lua_register(getLuaState(), "AddRemoveFriendSlashCommand", addRemoveFriendSlashCommand);
	lua_register(getLuaState(), "AddRemoveIgnoreSlashCommand", addRemoveIgnoreSlashCommand);
	lua_register(getLuaState(), "AddRepairBattlefieldStructureSlashCommand", addRepairBattlefieldStructureSlashCommand);
	lua_register(getLuaState(), "AddRepairShipComponentInSlotSlashCommand", addRepairShipComponentInSlotSlashCommand);
	lua_register(getLuaState(), "AddReportSlashCommand", addReportSlashCommand);
	lua_register(getLuaState(), "AddRequestBadgesSlashCommand", addRequestBadgesSlashCommand);
	lua_register(getLuaState(), "AddRequestBiographySlashCommand", addRequestBiographySlashCommand);
	lua_register(getLuaState(), "AddRequestCharacterMatchSlashCommand", addRequestCharacterMatchSlashCommand);
	lua_register(getLuaState(), "AddRequestCharacterSheetInfoSlashCommand", addRequestCharacterSheetInfoSlashCommand);
	lua_register(getLuaState(), "AddRequestCoreSampleSlashCommand", addRequestCoreSampleSlashCommand);
	lua_register(getLuaState(), "AddRequestCraftingSessionSlashCommand", addRequestCraftingSessionSlashCommand);
	lua_register(getLuaState(), "AddRequestDraftSlotsSlashCommand", addRequestDraftSlotsSlashCommand);
	lua_register(getLuaState(), "AddRequestDraftSlotsBatchSlashCommand", addRequestDraftSlotsBatchSlashCommand);
	lua_register(getLuaState(), "AddRequestManfSchematicSlotsSlashCommand", addRequestManfSchematicSlotsSlashCommand);
	lua_register(getLuaState(), "AddRequestResourceWeightsSlashCommand", addRequestResourceWeightsSlashCommand);
	lua_register(getLuaState(), "AddRequestResourceWeightsBatchSlashCommand", addRequestResourceWeightsBatchSlashCommand);
	lua_register(getLuaState(), "AddRequestSetStatMigrationDataSlashCommand", addRequestSetStatMigrationDataSlashCommand);
	lua_register(getLuaState(), "AddRequestStatMigrationDataSlashCommand", addRequestStatMigrationDataSlashCommand);
	lua_register(getLuaState(), "AddRequestStatMigrationStartSlashCommand", addRequestStatMigrationStartSlashCommand);
	lua_register(getLuaState(), "AddRequestStatMigrationStopSlashCommand", addRequestStatMigrationStopSlashCommand);
	lua_register(getLuaState(), "AddRequestStimpackSlashCommand", addRequestStimpackSlashCommand);
	lua_register(getLuaState(), "AddRequestSurveySlashCommand", addRequestSurveySlashCommand);
	lua_register(getLuaState(), "AddRequestWaypointAtPositionSlashCommand", addRequestWaypointAtPositionSlashCommand);
	lua_register(getLuaState(), "AddRescueSlashCommand", addRescueSlashCommand);
	lua_register(getLuaState(), "AddResendLoginMessageToAllSlashCommand", addResendLoginMessageToAllSlashCommand);
	lua_register(getLuaState(), "AddResetJediSlashCommand", addResetJediSlashCommand);
	lua_register(getLuaState(), "AddResourceSlashCommand", addResourceSlashCommand);
	lua_register(getLuaState(), "AddResourceContainerSplitSlashCommand", addResourceContainerSplitSlashCommand);
	lua_register(getLuaState(), "AddResourceContainerTransferSlashCommand", addResourceContainerTransferSlashCommand);
	lua_register(getLuaState(), "AddResourceSetNameSlashCommand", addResourceSetNameSlashCommand);
	lua_register(getLuaState(), "AddRespecStatCommitSlashCommand", addRespecStatCommitSlashCommand);
	lua_register(getLuaState(), "AddResSampleLoopSlashCommand", addResSampleLoopSlashCommand);
	lua_register(getLuaState(), "AddRestartConversionSlashCommand", addRestartConversionSlashCommand);
	lua_register(getLuaState(), "AddRestartCraftingSessionSlashCommand", addRestartCraftingSessionSlashCommand);
	lua_register(getLuaState(), "AddRestrainingShotSlashCommand", addRestrainingShotSlashCommand);
	lua_register(getLuaState(), "AddResuscitatePlayerSlashCommand", addResuscitatePlayerSlashCommand);
	lua_register(getLuaState(), "AddRetreatSlashCommand", addRetreatSlashCommand);
	lua_register(getLuaState(), "AddRevivePlayerSlashCommand", addRevivePlayerSlashCommand);
	lua_register(getLuaState(), "AddRevokeBadgeSlashCommand", addRevokeBadgeSlashCommand);
	lua_register(getLuaState(), "AddRevokeSkillSlashCommand", addRevokeSkillSlashCommand);
	lua_register(getLuaState(), "AddRolePlaySlashCommand", addRolePlaySlashCommand);
	lua_register(getLuaState(), "AddRollShotSlashCommand", addRollShotSlashCommand);
	lua_register(getLuaState(), "AddRotateFurnitureSlashCommand", addRotateFurnitureSlashCommand);
	lua_register(getLuaState(), "AddSaberArmorBreakSlashCommand", addSaberArmorBreakSlashCommand);
	lua_register(getLuaState(), "AddSaberBlindSlashCommand", addSaberBlindSlashCommand);
	lua_register(getLuaState(), "AddSaberBodyHitSlashCommand", addSaberBodyHitSlashCommand);
	lua_register(getLuaState(), "AddSaberDervishSlashCommand", addSaberDervishSlashCommand);
	lua_register(getLuaState(), "AddSaberHeadHitSlashCommand", addSaberHeadHitSlashCommand);
	lua_register(getLuaState(), "AddSaberHitSlashCommand", addSaberHitSlashCommand);
	lua_register(getLuaState(), "AddSaberLegHitSlashCommand", addSaberLegHitSlashCommand);
	lua_register(getLuaState(), "AddSaberPowerAttackSlashCommand", addSaberPowerAttackSlashCommand);
	lua_register(getLuaState(), "AddSaberSlashSlashCommand", addSaberSlashSlashCommand);
	lua_register(getLuaState(), "AddSaberSpinAttackSlashCommand", addSaberSpinAttackSlashCommand);
	lua_register(getLuaState(), "AddSaberStrikeSlashCommand", addSaberStrikeSlashCommand);
	lua_register(getLuaState(), "AddSaberStunStrikeSlashCommand", addSaberStunStrikeSlashCommand);
	lua_register(getLuaState(), "AddSaberSweepSlashCommand", addSaberSweepSlashCommand);
	lua_register(getLuaState(), "AddSaberSwipeSlashCommand", addSaberSwipeSlashCommand);
	lua_register(getLuaState(), "AddSaberThrowSlashCommand", addSaberThrowSlashCommand);
	lua_register(getLuaState(), "AddSampleSlashCommand", addSampleSlashCommand);
	lua_register(getLuaState(), "AddSampleDNASlashCommand", addSampleDNASlashCommand);
	lua_register(getLuaState(), "AddScatterHitSlashCommand", addScatterHitSlashCommand);
	lua_register(getLuaState(), "AddScatterShotSlashCommand", addScatterShotSlashCommand);
	lua_register(getLuaState(), "AddScriptSlashCommand", addScriptSlashCommand);
	lua_register(getLuaState(), "AddSearchCorpseSlashCommand", addSearchCorpseSlashCommand);
	lua_register(getLuaState(), "AddSecretSpawnSpamSlashCommand", addSecretSpawnSpamSlashCommand);
	lua_register(getLuaState(), "AddSeGogglesSlashCommand", addSeGogglesSlashCommand);
	lua_register(getLuaState(), "AddSelectDraftSchematicSlashCommand", addSelectDraftSchematicSlashCommand);
	lua_register(getLuaState(), "AddSerotoninInjectionSlashCommand", addSerotoninInjectionSlashCommand);
	lua_register(getLuaState(), "AddServerSlashCommand", addServerSlashCommand);
	lua_register(getLuaState(), "AddServerDestroyObjectSlashCommand", addServerDestroyObjectSlashCommand);
	lua_register(getLuaState(), "AddServerSysGroupSlashCommand", addServerSysGroupSlashCommand);
	lua_register(getLuaState(), "AddSetBiographySlashCommand", addSetBiographySlashCommand);
	lua_register(getLuaState(), "AddSetBiographyAdminSlashCommand", addSetBiographyAdminSlashCommand);
	lua_register(getLuaState(), "AddSetBoostmoraleSlashCommand", addSetBoostmoraleSlashCommand);
	lua_register(getLuaState(), "AddSetChargeSlashCommand", addSetChargeSlashCommand);
	lua_register(getLuaState(), "AddSetCurrentSkillTitleSlashCommand", addSetCurrentSkillTitleSlashCommand);
	lua_register(getLuaState(), "AddSetExperienceSlashCommand", addSetExperienceSlashCommand);
	lua_register(getLuaState(), "AddSetFactionSlashCommand", addSetFactionSlashCommand);
	lua_register(getLuaState(), "AddSetFactionStandingSlashCommand", addSetFactionStandingSlashCommand);
	lua_register(getLuaState(), "AddSetFirstNameSlashCommand", addSetFirstNameSlashCommand);
	lua_register(getLuaState(), "AddSetFormupSlashCommand", addSetFormupSlashCommand);
	lua_register(getLuaState(), "AddSetGodModeSlashCommand", addSetGodModeSlashCommand);
	lua_register(getLuaState(), "AddSetGrievousAuthorizedSlashCommand", addSetGrievousAuthorizedSlashCommand);
	lua_register(getLuaState(), "AddSetHueSlashCommand", addSetHueSlashCommand);
	lua_register(getLuaState(), "AddSetIntimidateSlashCommand", addSetIntimidateSlashCommand);
	lua_register(getLuaState(), "AddSetLastNameSlashCommand", addSetLastNameSlashCommand);
	lua_register(getLuaState(), "AddSetLoginMessageSlashCommand", addSetLoginMessageSlashCommand);
	lua_register(getLuaState(), "AddSetLoginTitleSlashCommand", addSetLoginTitleSlashCommand);
	lua_register(getLuaState(), "AddSetMatchMakingCharacterIdSlashCommand", addSetMatchMakingCharacterIdSlashCommand);
	lua_register(getLuaState(), "AddSetMatchMakingPersonalIdSlashCommand", addSetMatchMakingPersonalIdSlashCommand);
	lua_register(getLuaState(), "AddSetMaximumSpawnTimeSlashCommand", addSetMaximumSpawnTimeSlashCommand);
	lua_register(getLuaState(), "AddSetMinimumSpawnTimeSlashCommand", addSetMinimumSpawnTimeSlashCommand);
	lua_register(getLuaState(), "AddSetMoodSlashCommand", addSetMoodSlashCommand);
	lua_register(getLuaState(), "AddSetMoodInternalSlashCommand", addSetMoodInternalSlashCommand);
	lua_register(getLuaState(), "AddSetNameSlashCommand", addSetNameSlashCommand);
	lua_register(getLuaState(), "AddSetNameSlashCommand", addSetNameSlashCommand);
	lua_register(getLuaState(), "AddSetOwnerSlashCommand", addSetOwnerSlashCommand);
	lua_register(getLuaState(), "AddSetPerformanceBuffTargetSlashCommand", addSetPerformanceBuffTargetSlashCommand);
	lua_register(getLuaState(), "AddSetpermissionSlashCommand", addSetpermissionSlashCommand);
	lua_register(getLuaState(), "AddSetPlanetLimitSlashCommand", addSetPlanetLimitSlashCommand);
	lua_register(getLuaState(), "AddSetPlayerAppearanceSlashCommand", addSetPlayerAppearanceSlashCommand);
	lua_register(getLuaState(), "AddSetPlayerStateSlashCommand", addSetPlayerStateSlashCommand);
	lua_register(getLuaState(), "AddSetprivacySlashCommand", addSetprivacySlashCommand);
	lua_register(getLuaState(), "AddSetPublicStateSlashCommand", addSetPublicStateSlashCommand);
	lua_register(getLuaState(), "AddSetRankSlashCommand", addSetRankSlashCommand);
	lua_register(getLuaState(), "AddSetRetreatSlashCommand", addSetRetreatSlashCommand);
	lua_register(getLuaState(), "AddSetSpeedSlashCommand", addSetSpeedSlashCommand);
	lua_register(getLuaState(), "AddSetSpokenLanguageSlashCommand", addSetSpokenLanguageSlashCommand);
	lua_register(getLuaState(), "AddSetSteadyaimSlashCommand", addSetSteadyaimSlashCommand);
	lua_register(getLuaState(), "AddSetTEFSlashCommand", addSetTEFSlashCommand);
	lua_register(getLuaState(), "AddSetVeteranRewardSlashCommand", addSetVeteranRewardSlashCommand);
	lua_register(getLuaState(), "AddSetWarcrySlashCommand", addSetWarcrySlashCommand);
	lua_register(getLuaState(), "AddSetWaypointActiveStatusSlashCommand", addSetWaypointActiveStatusSlashCommand);
	lua_register(getLuaState(), "AddSetWaypointNameSlashCommand", addSetWaypointNameSlashCommand);
	lua_register(getLuaState(), "AddShockSlashCommand", addShockSlashCommand);
	lua_register(getLuaState(), "AddShowCouncilRankSlashCommand", addShowCouncilRankSlashCommand);
	lua_register(getLuaState(), "AddShowDanceVisualsSlashCommand", addShowDanceVisualsSlashCommand);
	lua_register(getLuaState(), "AddShowFactionInformationSlashCommand", addShowFactionInformationSlashCommand);
	lua_register(getLuaState(), "AddShowMusicianVisualsSlashCommand", addShowMusicianVisualsSlashCommand);
	lua_register(getLuaState(), "AddShowPvPRatingSlashCommand", addShowPvPRatingSlashCommand);
	lua_register(getLuaState(), "AddShowSpawnRegionSlashCommand", addShowSpawnRegionSlashCommand);
	lua_register(getLuaState(), "AddSitServerSlashCommand", addSitServerSlashCommand);
	lua_register(getLuaState(), "AddSkillSlashCommand", addSkillSlashCommand);
	lua_register(getLuaState(), "AddSmokebombSlashCommand", addSmokebombSlashCommand);
	lua_register(getLuaState(), "AddSniperShotSlashCommand", addSniperShotSlashCommand);
	lua_register(getLuaState(), "AddSnoopSlashCommand", addSnoopSlashCommand);
	lua_register(getLuaState(), "AddSocialSlashCommand", addSocialSlashCommand);
	lua_register(getLuaState(), "AddSocialInternalSlashCommand", addSocialInternalSlashCommand);
	lua_register(getLuaState(), "AddSpatialChatSlashCommand", addSpatialChatSlashCommand);
	lua_register(getLuaState(), "AddSpatialChatInternalSlashCommand", addSpatialChatInternalSlashCommand);
	lua_register(getLuaState(), "AddSpawnStatusSlashCommand", addSpawnStatusSlashCommand);
	lua_register(getLuaState(), "AddSpinAttackSlashCommand", addSpinAttackSlashCommand);
	lua_register(getLuaState(), "AddSplitCreditsWithGroupSlashCommand", addSplitCreditsWithGroupSlashCommand);
	lua_register(getLuaState(), "AddSpotlightSlashCommand", addSpotlightSlashCommand);
	lua_register(getLuaState(), "AddSprayShotSlashCommand", addSprayShotSlashCommand);
	lua_register(getLuaState(), "AddStabilizersSlashCommand", addStabilizersSlashCommand);
	lua_register(getLuaState(), "AddStandSlashCommand", addStandSlashCommand);
	lua_register(getLuaState(), "AddStartBandSlashCommand", addStartBandSlashCommand);
	lua_register(getLuaState(), "AddStartCitySpawnerSlashCommand", addStartCitySpawnerSlashCommand);
	lua_register(getLuaState(), "AddStartDanceSlashCommand", addStartDanceSlashCommand);
	lua_register(getLuaState(), "AddStartleShotSlashCommand", addStartleShotSlashCommand);
	lua_register(getLuaState(), "AddStartMusicSlashCommand", addStartMusicSlashCommand);
	lua_register(getLuaState(), "AddStartSpawnerSlashCommand", addStartSpawnerSlashCommand);
	lua_register(getLuaState(), "AddStartTargetSpawnerSlashCommand", addStartTargetSpawnerSlashCommand);
	lua_register(getLuaState(), "AddStartTraceLoggingSlashCommand", addStartTraceLoggingSlashCommand);
	lua_register(getLuaState(), "AddStasisSlashCommand", addStasisSlashCommand);
	lua_register(getLuaState(), "AddStatSlashCommand", addStatSlashCommand);
	lua_register(getLuaState(), "AddSteadyaimSlashCommand", addSteadyaimSlashCommand);
	lua_register(getLuaState(), "AddStopBandSlashCommand", addStopBandSlashCommand);
	lua_register(getLuaState(), "AddStopBleedingSlashCommand", addStopBleedingSlashCommand);
	lua_register(getLuaState(), "AddStopCitySpawnerSlashCommand", addStopCitySpawnerSlashCommand);
	lua_register(getLuaState(), "AddStopCraftingSessionSlashCommand", addStopCraftingSessionSlashCommand);
	lua_register(getLuaState(), "AddStopDanceSlashCommand", addStopDanceSlashCommand);
	lua_register(getLuaState(), "AddStoplisteningSlashCommand", addStoplisteningSlashCommand);
	lua_register(getLuaState(), "AddStopMusicSlashCommand", addStopMusicSlashCommand);
	lua_register(getLuaState(), "AddStoppingShotSlashCommand", addStoppingShotSlashCommand);
	lua_register(getLuaState(), "AddStopSpawnerSlashCommand", addStopSpawnerSlashCommand);
	lua_register(getLuaState(), "AddStopTargetSpawnerSlashCommand", addStopTargetSpawnerSlashCommand);
	lua_register(getLuaState(), "AddStopTraceLoggingSlashCommand", addStopTraceLoggingSlashCommand);
	lua_register(getLuaState(), "AddStopwatchingSlashCommand", addStopwatchingSlashCommand);
	lua_register(getLuaState(), "AddStructurestatusSlashCommand", addStructurestatusSlashCommand);
	lua_register(getLuaState(), "AddStunningBlowSlashCommand", addStunningBlowSlashCommand);
	lua_register(getLuaState(), "AddStunRecoverySlashCommand", addStunRecoverySlashCommand);
	lua_register(getLuaState(), "AddSuppressionFireSlashCommand", addSuppressionFireSlashCommand);
	lua_register(getLuaState(), "AddSurrenderSkillSlashCommand", addSurrenderSkillSlashCommand);
	lua_register(getLuaState(), "AddSurveySlashCommand", addSurveySlashCommand);
	lua_register(getLuaState(), "AddSweepAttackSlashCommand", addSweepAttackSlashCommand);
	lua_register(getLuaState(), "AddSwitchWeaponModeSlashCommand", addSwitchWeaponModeSlashCommand);
	lua_register(getLuaState(), "AddSwordFlurrySlashCommand", addSwordFlurrySlashCommand);
	lua_register(getLuaState(), "AddSynchronizedUiListenSlashCommand", addSynchronizedUiListenSlashCommand);
	lua_register(getLuaState(), "AddSynchronizedUiStopListeningSlashCommand", addSynchronizedUiStopListeningSlashCommand);
	lua_register(getLuaState(), "AddSystemMessageSlashCommand", addSystemMessageSlashCommand);
	lua_register(getLuaState(), "AddTakeCoverSlashCommand", addTakeCoverSlashCommand);
	lua_register(getLuaState(), "AddTameSlashCommand", addTameSlashCommand);
	lua_register(getLuaState(), "AddTargetSlashCommand", addTargetSlashCommand);
	lua_register(getLuaState(), "AddTauntSlashCommand", addTauntSlashCommand);
	lua_register(getLuaState(), "AddTeachSlashCommand", addTeachSlashCommand);
	lua_register(getLuaState(), "AddTeleportSlashCommand", addTeleportSlashCommand);
	lua_register(getLuaState(), "AddTeleportTargetSlashCommand", addTeleportTargetSlashCommand);
	lua_register(getLuaState(), "AddTeleportToSlashCommand", addTeleportToSlashCommand);
	lua_register(getLuaState(), "AddTellpetSlashCommand", addTellpetSlashCommand);
	lua_register(getLuaState(), "AddThrowGrenadeSlashCommand", addThrowGrenadeSlashCommand);
	lua_register(getLuaState(), "AddThrowTrapSlashCommand", addThrowTrapSlashCommand);
	lua_register(getLuaState(), "AddThyroidRuptureSlashCommand", addThyroidRuptureSlashCommand);
	lua_register(getLuaState(), "AddTipSlashCommand", addTipSlashCommand);
	lua_register(getLuaState(), "AddToggleAwayFromKeyBoardSlashCommand", addToggleAwayFromKeyBoardSlashCommand);
	lua_register(getLuaState(), "AddToggleCombatTauntsSlashCommand", addToggleCombatTauntsSlashCommand);
	lua_register(getLuaState(), "AddToggleDisplayingFactionRankSlashCommand", addToggleDisplayingFactionRankSlashCommand);
	lua_register(getLuaState(), "AddTorsoShotSlashCommand", addTorsoShotSlashCommand);
	lua_register(getLuaState(), "AddTotalHealSlashCommand", addTotalHealSlashCommand);
	lua_register(getLuaState(), "AddTransferForceSlashCommand", addTransferForceSlashCommand);
	lua_register(getLuaState(), "AddTransferItemSlashCommand", addTransferItemSlashCommand);
	lua_register(getLuaState(), "AddTransferItemArmorSlashCommand", addTransferItemArmorSlashCommand);
	lua_register(getLuaState(), "AddTransferItemMiscSlashCommand", addTransferItemMiscSlashCommand);
	lua_register(getLuaState(), "AddTransferItemWeaponSlashCommand", addTransferItemWeaponSlashCommand);
	lua_register(getLuaState(), "AddTransferstructureSlashCommand", addTransferstructureSlashCommand);
	lua_register(getLuaState(), "AddTraumatizeSlashCommand", addTraumatizeSlashCommand);
	lua_register(getLuaState(), "AddUnassociateDroidControlDeviceWithShipSlashCommand", addUnassociateDroidControlDeviceWithShipSlashCommand);
	lua_register(getLuaState(), "AddUnCityBanSlashCommand", addUnCityBanSlashCommand);
	lua_register(getLuaState(), "AddUnconsentSlashCommand", addUnconsentSlashCommand);
	lua_register(getLuaState(), "AddUnderhandShotSlashCommand", addUnderhandShotSlashCommand);
	lua_register(getLuaState(), "AddUnfreezePlayerSlashCommand", addUnfreezePlayerSlashCommand);
	lua_register(getLuaState(), "AddUninstallShipComponentSlashCommand", addUninstallShipComponentSlashCommand);
	lua_register(getLuaState(), "AddUninviteSlashCommand", addUninviteSlashCommand);
	lua_register(getLuaState(), "AddUnsnoopSlashCommand", addUnsnoopSlashCommand);
	lua_register(getLuaState(), "AddUseDoctorBagSlashCommand", addUseDoctorBagSlashCommand);
	lua_register(getLuaState(), "AddUseReconDroneSlashCommand", addUseReconDroneSlashCommand);
	lua_register(getLuaState(), "AddUseSkillBuffSlashCommand", addUseSkillBuffSlashCommand);
	lua_register(getLuaState(), "AddVentriloquismSlashCommand", addVentriloquismSlashCommand);
	lua_register(getLuaState(), "AddVertFurnitureSlashCommand", addVertFurnitureSlashCommand);
	lua_register(getLuaState(), "AddVitalizeSlashCommand", addVitalizeSlashCommand);
	lua_register(getLuaState(), "AddVolleyFireSlashCommand", addVolleyFireSlashCommand);
	lua_register(getLuaState(), "AddVolleyFireAttackSlashCommand", addVolleyFireAttackSlashCommand);
	lua_register(getLuaState(), "AddWarcrySlashCommand", addWarcrySlashCommand);
	lua_register(getLuaState(), "AddWarningShotSlashCommand", addWarningShotSlashCommand);
	lua_register(getLuaState(), "AddWatchSlashCommand", addWatchSlashCommand);
	lua_register(getLuaState(), "AddWaypointSlashCommand", addWaypointSlashCommand);
	lua_register(getLuaState(), "AddWipeItemsSlashCommand", addWipeItemsSlashCommand);
	lua_register(getLuaState(), "AddWookieeRoarSlashCommand", addWookieeRoarSlashCommand);
/*	lua_register(getLuaState(), "AddOpenContainerSlashCommand", addOpenContainerSlashCommand);
	lua_register(getLuaState(), "AddGroupSaySlashCommand", addGroupSaySlashCommand);*/
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

	String field = slashcommand.getStringField("animation");
	command->setAnimation(field);

	uint64 mask = slashcommand.getLongField("invalidStateMask");
	command->setStateMask(mask);

	field = slashcommand.getStringField("invalidPostures");
	command->setInvalidPostures(field);

	int num = slashcommand.getIntField("target");
	command->setTarget(num);

	num = slashcommand.getIntField("targetType");
	command->setTargetType(num);

	num = slashcommand.getIntField("disabled");
	command->setDisabled(num);

	num = slashcommand.getIntField("maxRangeToTarget");
	command->setMaxRange(num);

	num = slashcommand.getIntField("addToCombatQueue");
	command->setAddToCombatQueue(num);

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

	String alternativeNames = slashcommand.getStringField("alternativeNames");
	if (!alternativeNames.isEmpty())
		parseAlternativeNames(alternativeNames, slashCommand);
}

int CommandConfigManager::addActivateCloneSlashCommand(lua_State* L) {
	LuaObject slashcommand(L);
	if (!slashcommand.isValidTable())
		return 0;

	ActivateCloneSlashCommand* slashCommand = new ActivateCloneSlashCommand(slashcommand.getStringField("name"), server);
	parseSlashCommand(slashcommand, slashCommand);
	return 1;
}

int CommandConfigManager::addActivateQuestSlashCommand(lua_State* L) {
	LuaObject slashcommand(L);
	if (!slashcommand.isValidTable())
		return 0;

	ActivateQuestSlashCommand* slashCommand = new ActivateQuestSlashCommand(slashcommand.getStringField("name"), server);
	parseSlashCommand(slashcommand, slashCommand);
	return 1;
}

int CommandConfigManager::addAddAllowedPlayerSlashCommand(lua_State* L) {
	LuaObject slashcommand(L);
	if (!slashcommand.isValidTable())
		return 0;

	AddAllowedPlayerSlashCommand* slashCommand = new AddAllowedPlayerSlashCommand(slashcommand.getStringField("name"), server);
	parseSlashCommand(slashcommand, slashCommand);
	return 1;
}

int CommandConfigManager::addAddBannedPlayerSlashCommand(lua_State* L) {
	LuaObject slashcommand(L);
	if (!slashcommand.isValidTable())
		return 0;

	AddBannedPlayerSlashCommand* slashCommand = new AddBannedPlayerSlashCommand(slashcommand.getStringField("name"), server);
	parseSlashCommand(slashcommand, slashCommand);
	return 1;
}

int CommandConfigManager::addAddFriendSlashCommand(lua_State* L) {
	LuaObject slashcommand(L);
	if (!slashcommand.isValidTable())
		return 0;

	AddFriendSlashCommand* slashCommand = new AddFriendSlashCommand(slashcommand.getStringField("name"), server);
	parseSlashCommand(slashcommand, slashCommand);
	return 1;
}

int CommandConfigManager::addAddIgnoreSlashCommand(lua_State* L) {
	LuaObject slashcommand(L);
	if (!slashcommand.isValidTable())
		return 0;

	AddIgnoreSlashCommand* slashCommand = new AddIgnoreSlashCommand(slashcommand.getStringField("name"), server);
	parseSlashCommand(slashcommand, slashCommand);
	return 1;
}

int CommandConfigManager::addAddMapLocationSlashCommand(lua_State* L) {
	LuaObject slashcommand(L);
	if (!slashcommand.isValidTable())
		return 0;

	AddMapLocationSlashCommand* slashCommand = new AddMapLocationSlashCommand(slashcommand.getStringField("name"), server);
	parseSlashCommand(slashcommand, slashCommand);
	return 1;
}

int CommandConfigManager::addAddPowerSlashCommand(lua_State* L) {
	LuaObject slashcommand(L);
	if (!slashcommand.isValidTable())
		return 0;

	AddPowerSlashCommand* slashCommand = new AddPowerSlashCommand(slashcommand.getStringField("name"), server);
	parseSlashCommand(slashcommand, slashCommand);
	return 1;
}

int CommandConfigManager::addAdjustLotCountSlashCommand(lua_State* L) {
	LuaObject slashcommand(L);
	if (!slashcommand.isValidTable()) {
		return 0;
	}

	AdjustLotCountSlashCommand* slashCommand = new AdjustLotCountSlashCommand(slashcommand.getStringField("name"), server);
	parseSlashCommand(slashcommand, slashCommand);
	return 1;
}

int CommandConfigManager::addAdrenalBoostSlashCommand(lua_State* L) {
	LuaObject slashcommand(L);
	if (!slashcommand.isValidTable())
		return 0;

	AdrenalBoostSlashCommand* slashCommand = new AdrenalBoostSlashCommand(slashcommand.getStringField("name"), server);
	parseSlashCommand(slashcommand, slashCommand);
	return 1;
}

int CommandConfigManager::addAiIgnoreSlashCommand(lua_State* L) {
	LuaObject slashcommand(L);
	if (!slashcommand.isValidTable())
		return 0;

	AiIgnoreSlashCommand* slashCommand = new AiIgnoreSlashCommand(slashcommand.getStringField("name"), server);
	parseSlashCommand(slashcommand, slashCommand);
	return 1;
}

int CommandConfigManager::addAimSlashCommand(lua_State* L) {
	LuaObject slashcommand(L);
	if (!slashcommand.isValidTable())
		return 0;

	AimSlashCommand* slashCommand = new AimSlashCommand(slashcommand.getStringField("name"), server);
	parseSlashCommand(slashcommand, slashCommand);
	return 1;
}

int CommandConfigManager::addAimedShotSlashCommand(lua_State* L) {
	LuaObject slashcommand(L);
	if (!slashcommand.isValidTable())
		return 0;

	AimedShotSlashCommand* slashCommand = new AimedShotSlashCommand(slashcommand.getStringField("name"), server);
	parseSlashCommand(slashcommand, slashCommand);
	return 1;
}

int CommandConfigManager::addAnonSlashCommand(lua_State* L) {
	LuaObject slashcommand(L);
	if (!slashcommand.isValidTable())
		return 0;

	AnonSlashCommand* slashCommand = new AnonSlashCommand(slashcommand.getStringField("name"), server);
	parseSlashCommand(slashcommand, slashCommand);
	return 1;
}

int CommandConfigManager::addApplyPowerupSlashCommand(lua_State* L) {
	LuaObject slashcommand(L);
	if (!slashcommand.isValidTable())
		return 0;

	ApplyPowerupSlashCommand* slashCommand = new ApplyPowerupSlashCommand(slashcommand.getStringField("name"), server);
	parseSlashCommand(slashcommand, slashCommand);
	return 1;
}

int CommandConfigManager::addAreaTauntSlashCommand(lua_State* L) {
	LuaObject slashcommand(L);
	if (!slashcommand.isValidTable())
		return 0;

	AreaTauntSlashCommand* slashCommand = new AreaTauntSlashCommand(slashcommand.getStringField("name"), server);
	parseSlashCommand(slashcommand, slashCommand);
	return 1;
}

int CommandConfigManager::addAreatrackSlashCommand(lua_State* L) {
	LuaObject slashcommand(L);
	if (!slashcommand.isValidTable())
		return 0;

	AreatrackSlashCommand* slashCommand = new AreatrackSlashCommand(slashcommand.getStringField("name"), server);
	parseSlashCommand(slashcommand, slashCommand);
	return 1;
}

int CommandConfigManager::addArmorBreakSlashCommand(lua_State* L) {
	LuaObject slashcommand(L);
	if (!slashcommand.isValidTable())
		return 0;

	ArmorBreakSlashCommand* slashCommand = new ArmorBreakSlashCommand(slashcommand.getStringField("name"), server);
	parseSlashCommand(slashcommand, slashCommand);
	return 1;
}

int CommandConfigManager::addAssignDroidSlashCommand(lua_State* L) {
	LuaObject slashcommand(L);
	if (!slashcommand.isValidTable())
		return 0;

	AssignDroidSlashCommand* slashCommand = new AssignDroidSlashCommand(slashcommand.getStringField("name"), server);
	parseSlashCommand(slashcommand, slashCommand);
	return 1;
}

int CommandConfigManager::addAssociateDroidControlDeviceWithShipSlashCommand(lua_State* L) {
	LuaObject slashcommand(L);
	if (!slashcommand.isValidTable())
		return 0;

	AssociateDroidControlDeviceWithShipSlashCommand* slashCommand = new AssociateDroidControlDeviceWithShipSlashCommand(slashcommand.getStringField("name"), server);
	parseSlashCommand(slashcommand, slashCommand);
	return 1;
}

int CommandConfigManager::addAttackSlashCommand(lua_State* L) {
	LuaObject slashcommand(L);
	if (!slashcommand.isValidTable())
		return 0;

	AttackSlashCommand* slashCommand = new AttackSlashCommand(slashcommand.getStringField("name"), server);
	parseSlashCommand(slashcommand, slashCommand);
	return 1;
}

int CommandConfigManager::addAuctionAcceptSlashCommand(lua_State* L) {
	LuaObject slashcommand(L);
	if (!slashcommand.isValidTable())
		return 0;

	AuctionAcceptSlashCommand* slashCommand = new AuctionAcceptSlashCommand(slashcommand.getStringField("name"), server);
	parseSlashCommand(slashcommand, slashCommand);
	return 1;
}

int CommandConfigManager::addAuctionBidSlashCommand(lua_State* L) {
	LuaObject slashcommand(L);
	if (!slashcommand.isValidTable())
		return 0;

	AuctionBidSlashCommand* slashCommand = new AuctionBidSlashCommand(slashcommand.getStringField("name"), server);
	parseSlashCommand(slashcommand, slashCommand);
	return 1;
}

int CommandConfigManager::addAuctionCancelSlashCommand(lua_State* L) {
	LuaObject slashcommand(L);
	if (!slashcommand.isValidTable())
		return 0;

	AuctionCancelSlashCommand* slashCommand = new AuctionCancelSlashCommand(slashcommand.getStringField("name"), server);
	parseSlashCommand(slashcommand, slashCommand);
	return 1;
}

int CommandConfigManager::addAuctionCreateSlashCommand(lua_State* L) {
	LuaObject slashcommand(L);
	if (!slashcommand.isValidTable())
		return 0;

	AuctionCreateSlashCommand* slashCommand = new AuctionCreateSlashCommand(slashcommand.getStringField("name"), server);
	parseSlashCommand(slashcommand, slashCommand);
	return 1;
}

int CommandConfigManager::addAuctionQuerySlashCommand(lua_State* L) {
	LuaObject slashcommand(L);
	if (!slashcommand.isValidTable())
		return 0;

	AuctionQuerySlashCommand* slashCommand = new AuctionQuerySlashCommand(slashcommand.getStringField("name"), server);
	parseSlashCommand(slashcommand, slashCommand);
	return 1;
}

int CommandConfigManager::addAuctionRetrieveSlashCommand(lua_State* L) {
	LuaObject slashcommand(L);
	if (!slashcommand.isValidTable())
		return 0;

	AuctionRetrieveSlashCommand* slashCommand = new AuctionRetrieveSlashCommand(slashcommand.getStringField("name"), server);
	parseSlashCommand(slashcommand, slashCommand);
	return 1;
}

int CommandConfigManager::addAuctionsaySlashCommand(lua_State* L) {
	LuaObject slashcommand(L);
	if (!slashcommand.isValidTable())
		return 0;

	AuctionsaySlashCommand* slashCommand = new AuctionsaySlashCommand(slashcommand.getStringField("name"), server);
	parseSlashCommand(slashcommand, slashCommand);
	return 1;
}

int CommandConfigManager::addAvoidIncapacitationSlashCommand(lua_State* L) {
	LuaObject slashcommand(L);
	if (!slashcommand.isValidTable())
		return 0;

	AvoidIncapacitationSlashCommand* slashCommand = new AvoidIncapacitationSlashCommand(slashcommand.getStringField("name"), server);
	parseSlashCommand(slashcommand, slashCommand);
	return 1;
}

int CommandConfigManager::addBactaInfusionSlashCommand(lua_State* L) {
	LuaObject slashcommand(L);
	if (!slashcommand.isValidTable())
		return 0;

	BactaInfusionSlashCommand* slashCommand = new BactaInfusionSlashCommand(slashcommand.getStringField("name"), server);
	parseSlashCommand(slashcommand, slashCommand);
	return 1;
}

int CommandConfigManager::addBactaJabSlashCommand(lua_State* L) {
	LuaObject slashcommand(L);
	if (!slashcommand.isValidTable())
		return 0;

	BactaJabSlashCommand* slashCommand = new BactaJabSlashCommand(slashcommand.getStringField("name"), server);
	parseSlashCommand(slashcommand, slashCommand);
	return 1;
}

int CommandConfigManager::addBactaShotSlashCommand(lua_State* L) {
	LuaObject slashcommand(L);
	if (!slashcommand.isValidTable())
		return 0;

	BactaShotSlashCommand* slashCommand = new BactaShotSlashCommand(slashcommand.getStringField("name"), server);
	parseSlashCommand(slashcommand, slashCommand);
	return 1;
}

int CommandConfigManager::addBactaSpraySlashCommand(lua_State* L) {
	LuaObject slashcommand(L);
	if (!slashcommand.isValidTable())
		return 0;

	BactaSpraySlashCommand* slashCommand = new BactaSpraySlashCommand(slashcommand.getStringField("name"), server);
	parseSlashCommand(slashcommand, slashCommand);
	return 1;
}

int CommandConfigManager::addBactaTossSlashCommand(lua_State* L) {
	LuaObject slashcommand(L);
	if (!slashcommand.isValidTable())
		return 0;

	BactaTossSlashCommand* slashCommand = new BactaTossSlashCommand(slashcommand.getStringField("name"), server);
	parseSlashCommand(slashcommand, slashCommand);
	return 1;
}

int CommandConfigManager::addBandageSlashCommand(lua_State* L) {
	LuaObject slashcommand(L);
	if (!slashcommand.isValidTable())
		return 0;

	BandageSlashCommand* slashCommand = new BandageSlashCommand(slashcommand.getStringField("name"), server);
	parseSlashCommand(slashcommand, slashCommand);
	return 1;
}

int CommandConfigManager::addBattlefieldStatusSlashCommand(lua_State* L) {
	LuaObject slashcommand(L);
	if (!slashcommand.isValidTable())
		return 0;

	BattlefieldStatusSlashCommand* slashCommand = new BattlefieldStatusSlashCommand(slashcommand.getStringField("name"), server);
	parseSlashCommand(slashcommand, slashCommand);
	return 1;
}

int CommandConfigManager::addBerserkSlashCommand(lua_State* L) {
	LuaObject slashcommand(L);
	if (!slashcommand.isValidTable())
		return 0;

	BerserkSlashCommand* slashCommand = new BerserkSlashCommand(slashcommand.getStringField("name"), server);
	parseSlashCommand(slashcommand, slashCommand);
	return 1;
}

int CommandConfigManager::addBetSlashCommand(lua_State* L) {
	LuaObject slashcommand(L);
	if (!slashcommand.isValidTable())
		return 0;

	BetSlashCommand* slashCommand = new BetSlashCommand(slashcommand.getStringField("name"), server);
	parseSlashCommand(slashcommand, slashCommand);
	return 1;
}

int CommandConfigManager::addBindingStrikeSlashCommand(lua_State* L) {
	LuaObject slashcommand(L);
	if (!slashcommand.isValidTable())
		return 0;

	BindingStrikeSlashCommand* slashCommand = new BindingStrikeSlashCommand(slashcommand.getStringField("name"), server);
	parseSlashCommand(slashcommand, slashCommand);
	return 1;
}

int CommandConfigManager::addBleedAttackSlashCommand(lua_State* L) {
	LuaObject slashcommand(L);
	if (!slashcommand.isValidTable())
		return 0;

	BleedAttackSlashCommand* slashCommand = new BleedAttackSlashCommand(slashcommand.getStringField("name"), server);
	parseSlashCommand(slashcommand, slashCommand);
	return 1;
}

int CommandConfigManager::addBlindAttackSlashCommand(lua_State* L) {
	LuaObject slashcommand(L);
	if (!slashcommand.isValidTable())
		return 0;

	BlindAttackSlashCommand* slashCommand = new BlindAttackSlashCommand(slashcommand.getStringField("name"), server);
	parseSlashCommand(slashcommand, slashCommand);
	return 1;
}

int CommandConfigManager::addBlindRecoverySlashCommand(lua_State* L) {
	LuaObject slashcommand(L);
	if (!slashcommand.isValidTable())
		return 0;

	BlindRecoverySlashCommand* slashCommand = new BlindRecoverySlashCommand(slashcommand.getStringField("name"), server);
	parseSlashCommand(slashcommand, slashCommand);
	return 1;
}

int CommandConfigManager::addBoardShuttleSlashCommand(lua_State* L) {
	LuaObject slashcommand(L);
	if (!slashcommand.isValidTable())
		return 0;

	BoardShuttleSlashCommand* slashCommand = new BoardShuttleSlashCommand(slashcommand.getStringField("name"), server);
	parseSlashCommand(slashcommand, slashCommand);
	return 1;
}

int CommandConfigManager::addBodyHitSlashCommand(lua_State* L) {
	LuaObject slashcommand(L);
	if (!slashcommand.isValidTable())
		return 0;

	BodyHitSlashCommand* slashCommand = new BodyHitSlashCommand(slashcommand.getStringField("name"), server);
	parseSlashCommand(slashcommand, slashCommand);
	return 1;
}

int CommandConfigManager::addBodyShotSlashCommand(lua_State* L) {
	LuaObject slashcommand(L);
	if (!slashcommand.isValidTable())
		return 0;

	BodyShotSlashCommand* slashCommand = new BodyShotSlashCommand(slashcommand.getStringField("name"), server);
	parseSlashCommand(slashcommand, slashCommand);
	return 1;
}

int CommandConfigManager::addBoostmoraleSlashCommand(lua_State* L) {
	LuaObject slashcommand(L);
	if (!slashcommand.isValidTable())
		return 0;

	BoostmoraleSlashCommand* slashCommand = new BoostmoraleSlashCommand(slashcommand.getStringField("name"), server);
	parseSlashCommand(slashcommand, slashCommand);
	return 1;
}

int CommandConfigManager::addBroadcastSlashCommand(lua_State* L) {
	LuaObject slashcommand(L);
	if (!slashcommand.isValidTable())
		return 0;

	BroadcastSlashCommand* slashCommand = new BroadcastSlashCommand(slashcommand.getStringField("name"), server);
	parseSlashCommand(slashcommand, slashCommand);
	return 1;
}

int CommandConfigManager::addBroadcastAreaSlashCommand(lua_State* L) {
	LuaObject slashcommand(L);
	if (!slashcommand.isValidTable())
		return 0;

	BroadcastAreaSlashCommand* slashCommand = new BroadcastAreaSlashCommand(slashcommand.getStringField("name"), server);
	parseSlashCommand(slashcommand, slashCommand);
	return 1;
}

int CommandConfigManager::addBroadcastGalaxySlashCommand(lua_State* L) {
	LuaObject slashcommand(L);
	if (!slashcommand.isValidTable())
		return 0;

	BroadcastGalaxySlashCommand* slashCommand = new BroadcastGalaxySlashCommand(slashcommand.getStringField("name"), server);
	parseSlashCommand(slashcommand, slashCommand);
	return 1;
}

int CommandConfigManager::addBroadcastPlanetSlashCommand(lua_State* L) {
	LuaObject slashcommand(L);
	if (!slashcommand.isValidTable())
		return 0;

	BroadcastPlanetSlashCommand* slashCommand = new BroadcastPlanetSlashCommand(slashcommand.getStringField("name"), server);
	parseSlashCommand(slashcommand, slashCommand);
	return 1;
}

int CommandConfigManager::addBurstRunSlashCommand(lua_State* L) {
	LuaObject slashcommand(L);
	if (!slashcommand.isValidTable())
		return 0;

	BurstRunSlashCommand* slashCommand = new BurstRunSlashCommand(slashcommand.getStringField("name"), server);
	parseSlashCommand(slashcommand, slashCommand);
	return 1;
}

int CommandConfigManager::addBurstShotSlashCommand(lua_State* L) {
	LuaObject slashcommand(L);
	if (!slashcommand.isValidTable())
		return 0;

	BurstShotSlashCommand* slashCommand = new BurstShotSlashCommand(slashcommand.getStringField("name"), server);
	parseSlashCommand(slashcommand, slashCommand);
	return 1;
}

int CommandConfigManager::addCancelCraftingSessionSlashCommand(lua_State* L) {
	LuaObject slashcommand(L);
	if (!slashcommand.isValidTable())
		return 0;

	CancelCraftingSessionSlashCommand* slashCommand = new CancelCraftingSessionSlashCommand(slashcommand.getStringField("name"), server);
	parseSlashCommand(slashcommand, slashCommand);
	return 1;
}

int CommandConfigManager::addCenterOfBeingSlashCommand(lua_State* L) {
	LuaObject slashcommand(L);
	if (!slashcommand.isValidTable())
		return 0;

	CenterOfBeingSlashCommand* slashCommand = new CenterOfBeingSlashCommand(slashcommand.getStringField("name"), server);
	parseSlashCommand(slashcommand, slashCommand);
	return 1;
}

int CommandConfigManager::addChangeBandMusicSlashCommand(lua_State* L) {
	LuaObject slashcommand(L);
	if (!slashcommand.isValidTable())
		return 0;

	ChangeBandMusicSlashCommand* slashCommand = new ChangeBandMusicSlashCommand(slashcommand.getStringField("name"), server);
	parseSlashCommand(slashcommand, slashCommand);
	return 1;
}

int CommandConfigManager::addChangeDanceSlashCommand(lua_State* L) {
	LuaObject slashcommand(L);
	if (!slashcommand.isValidTable())
		return 0;

	ChangeDanceSlashCommand* slashCommand = new ChangeDanceSlashCommand(slashcommand.getStringField("name"), server);
	parseSlashCommand(slashcommand, slashCommand);
	return 1;
}

int CommandConfigManager::addChangeMusicSlashCommand(lua_State* L) {
	LuaObject slashcommand(L);
	if (!slashcommand.isValidTable())
		return 0;

	ChangeMusicSlashCommand* slashCommand = new ChangeMusicSlashCommand(slashcommand.getStringField("name"), server);
	parseSlashCommand(slashcommand, slashCommand);
	return 1;
}

int CommandConfigManager::addChannelForceSlashCommand(lua_State* L) {
	LuaObject slashcommand(L);
	if (!slashcommand.isValidTable())
		return 0;

	ChannelForceSlashCommand* slashCommand = new ChannelForceSlashCommand(slashcommand.getStringField("name"), server);
	parseSlashCommand(slashcommand, slashCommand);
	return 1;
}

int CommandConfigManager::addChargeShotSlashCommand(lua_State* L) {
	LuaObject slashcommand(L);
	if (!slashcommand.isValidTable())
		return 0;

	ChargeShotSlashCommand* slashCommand = new ChargeShotSlashCommand(slashcommand.getStringField("name"), server);
	parseSlashCommand(slashcommand, slashCommand);
	return 1;
}

int CommandConfigManager::addCheckForceStatusSlashCommand(lua_State* L) {
	LuaObject slashcommand(L);
	if (!slashcommand.isValidTable())
		return 0;

	CheckForceStatusSlashCommand* slashCommand = new CheckForceStatusSlashCommand(slashcommand.getStringField("name"), server);
	parseSlashCommand(slashcommand, slashCommand);
	return 1;
}

int CommandConfigManager::addCitybanSlashCommand(lua_State* L) {
	LuaObject slashcommand(L);
	if (!slashcommand.isValidTable())
		return 0;

	CitybanSlashCommand* slashCommand = new CitybanSlashCommand(slashcommand.getStringField("name"), server);
	parseSlashCommand(slashcommand, slashCommand);
	return 1;
}

int CommandConfigManager::addCityInfoSlashCommand(lua_State* L) {
	LuaObject slashcommand(L);
	if (!slashcommand.isValidTable())
		return 0;

	CityInfoSlashCommand* slashCommand = new CityInfoSlashCommand(slashcommand.getStringField("name"), server);
	parseSlashCommand(slashcommand, slashCommand);
	return 1;
}

int CommandConfigManager::addCitypardonSlashCommand(lua_State* L) {
	LuaObject slashcommand(L);
	if (!slashcommand.isValidTable())
		return 0;

	CitypardonSlashCommand* slashCommand = new CitypardonSlashCommand(slashcommand.getStringField("name"), server);
	parseSlashCommand(slashcommand, slashCommand);
	return 1;
}

int CommandConfigManager::addClaimVeteranRewardSlashCommand(lua_State* L) {
	LuaObject slashcommand(L);
	if (!slashcommand.isValidTable())
		return 0;

	ClaimVeteranRewardSlashCommand* slashCommand = new ClaimVeteranRewardSlashCommand(slashcommand.getStringField("name"), server);
	parseSlashCommand(slashcommand, slashCommand);
	return 1;
}

int CommandConfigManager::addClearCompletedQuestSlashCommand(lua_State* L) {
	LuaObject slashcommand(L);
	if (!slashcommand.isValidTable())
		return 0;

	ClearCompletedQuestSlashCommand* slashCommand = new ClearCompletedQuestSlashCommand(slashcommand.getStringField("name"), server);
	parseSlashCommand(slashcommand, slashCommand);
	return 1;
}

int CommandConfigManager::addClearQueueSlashCommand(lua_State* L) {
	LuaObject slashcommand(L);
	if (!slashcommand.isValidTable())
		return 0;

	ClearQueueSlashCommand* slashCommand = new ClearQueueSlashCommand(slashcommand.getStringField("name"), server);
	parseSlashCommand(slashcommand, slashCommand);
	return 1;
}

int CommandConfigManager::addClearVeteranRewardSlashCommand(lua_State* L) {
	LuaObject slashcommand(L);
	if (!slashcommand.isValidTable())
		return 0;

	ClearVeteranRewardSlashCommand* slashCommand = new ClearVeteranRewardSlashCommand(slashcommand.getStringField("name"), server);
	parseSlashCommand(slashcommand, slashCommand);
	return 1;
}

int CommandConfigManager::addClientQualifiedForSkillSlashCommand(lua_State* L) {
	LuaObject slashcommand(L);
	if (!slashcommand.isValidTable())
		return 0;

	ClientQualifiedForSkillSlashCommand* slashCommand = new ClientQualifiedForSkillSlashCommand(slashcommand.getStringField("name"), server);
	parseSlashCommand(slashcommand, slashCommand);
	return 1;
}

int CommandConfigManager::addCloneSlashCommand(lua_State* L) {
	LuaObject slashcommand(L);
	if (!slashcommand.isValidTable())
		return 0;

	CloneSlashCommand* slashCommand = new CloneSlashCommand(slashcommand.getStringField("name"), server);
	parseSlashCommand(slashcommand, slashCommand);
	return 1;
}

int CommandConfigManager::addCloseContainerSlashCommand(lua_State* L) {
	LuaObject slashcommand(L);
	if (!slashcommand.isValidTable())
		return 0;

	CloseContainerSlashCommand* slashCommand = new CloseContainerSlashCommand(slashcommand.getStringField("name"), server);
	parseSlashCommand(slashcommand, slashCommand);
	return 1;
}

int CommandConfigManager::addCloseLotteryContainerSlashCommand(lua_State* L) {
	LuaObject slashcommand(L);
	if (!slashcommand.isValidTable())
		return 0;

	CloseLotteryContainerSlashCommand* slashCommand = new CloseLotteryContainerSlashCommand(slashcommand.getStringField("name"), server);
	parseSlashCommand(slashcommand, slashCommand);
	return 1;
}

int CommandConfigManager::addCobSlashCommand(lua_State* L) {
	LuaObject slashcommand(L);
	if (!slashcommand.isValidTable())
		return 0;

	CobSlashCommand* slashCommand = new CobSlashCommand(slashcommand.getStringField("name"), server);
	parseSlashCommand(slashcommand, slashCommand);
	return 1;
}

int CommandConfigManager::addColorlightsSlashCommand(lua_State* L) {
	LuaObject slashcommand(L);
	if (!slashcommand.isValidTable())
		return 0;

	ColorlightsSlashCommand* slashCommand = new ColorlightsSlashCommand(slashcommand.getStringField("name"), server);
	parseSlashCommand(slashcommand, slashCommand);
	return 1;
}

int CommandConfigManager::addCombatSlashCommand(lua_State* L) {
	LuaObject slashcommand(L);
	if (!slashcommand.isValidTable())
		return 0;

	CombatSlashCommand* slashCommand = new CombatSlashCommand(slashcommand.getStringField("name"), server);
	parseSlashCommand(slashcommand, slashCommand);
	return 1;
}

int CommandConfigManager::addCombatEscapeSlashCommand(lua_State* L) {
	LuaObject slashcommand(L);
	if (!slashcommand.isValidTable())
		return 0;

	CombatEscapeSlashCommand* slashCommand = new CombatEscapeSlashCommand(slashcommand.getStringField("name"), server);
	parseSlashCommand(slashcommand, slashCommand);
	return 1;
}

int CommandConfigManager::addCombatModeCheckSlashCommand(lua_State* L) {
	LuaObject slashcommand(L);
	if (!slashcommand.isValidTable())
		return 0;

	CombatModeCheckSlashCommand* slashCommand = new CombatModeCheckSlashCommand(slashcommand.getStringField("name"), server);
	parseSlashCommand(slashcommand, slashCommand);
	return 1;
}

int CommandConfigManager::addCombatSpamSlashCommand(lua_State* L) {
	LuaObject slashcommand(L);
	if (!slashcommand.isValidTable())
		return 0;

	CombatSpamSlashCommand* slashCommand = new CombatSpamSlashCommand(slashcommand.getStringField("name"), server);
	parseSlashCommand(slashcommand, slashCommand);
	return 1;
}

int CommandConfigManager::addCombatTargetSlashCommand(lua_State* L) {
	LuaObject slashcommand(L);
	if (!slashcommand.isValidTable())
		return 0;

	CombatTargetSlashCommand* slashCommand = new CombatTargetSlashCommand(slashcommand.getStringField("name"), server);
	parseSlashCommand(slashcommand, slashCommand);
	return 1;
}

int CommandConfigManager::addComboAttackSlashCommand(lua_State* L) {
	LuaObject slashcommand(L);
	if (!slashcommand.isValidTable())
		return 0;

	ComboAttackSlashCommand* slashCommand = new ComboAttackSlashCommand(slashcommand.getStringField("name"), server);
	parseSlashCommand(slashcommand, slashCommand);
	return 1;
}

int CommandConfigManager::addCompleteQuestSlashCommand(lua_State* L) {
	LuaObject slashcommand(L);
	if (!slashcommand.isValidTable())
		return 0;

	CompleteQuestSlashCommand* slashCommand = new CompleteQuestSlashCommand(slashcommand.getStringField("name"), server);
	parseSlashCommand(slashcommand, slashCommand);
	return 1;
}

int CommandConfigManager::addConcealSlashCommand(lua_State* L) {
	LuaObject slashcommand(L);
	if (!slashcommand.isValidTable())
		return 0;

	ConcealSlashCommand* slashCommand = new ConcealSlashCommand(slashcommand.getStringField("name"), server);
	parseSlashCommand(slashcommand, slashCommand);
	return 1;
}

int CommandConfigManager::addConcealShotSlashCommand(lua_State* L) {
	LuaObject slashcommand(L);
	if (!slashcommand.isValidTable())
		return 0;

	ConcealShotSlashCommand* slashCommand = new ConcealShotSlashCommand(slashcommand.getStringField("name"), server);
	parseSlashCommand(slashcommand, slashCommand);
	return 1;
}

int CommandConfigManager::addConcussionShotSlashCommand(lua_State* L) {
	LuaObject slashcommand(L);
	if (!slashcommand.isValidTable())
		return 0;

	ConcussionShotSlashCommand* slashCommand = new ConcussionShotSlashCommand(slashcommand.getStringField("name"), server);
	parseSlashCommand(slashcommand, slashCommand);
	return 1;
}

int CommandConfigManager::addConfusionShotSlashCommand(lua_State* L) {
	LuaObject slashcommand(L);
	if (!slashcommand.isValidTable())
		return 0;

	ConfusionShotSlashCommand* slashCommand = new ConfusionShotSlashCommand(slashcommand.getStringField("name"), server);
	parseSlashCommand(slashcommand, slashCommand);
	return 1;
}

int CommandConfigManager::addConsentSlashCommand(lua_State* L) {
	LuaObject slashcommand(L);
	if (!slashcommand.isValidTable())
		return 0;

	ConsentSlashCommand* slashCommand = new ConsentSlashCommand(slashcommand.getStringField("name"), server);
	parseSlashCommand(slashcommand, slashCommand);
	return 1;
}

int CommandConfigManager::addCorpseSlashCommand(lua_State* L) {
	LuaObject slashcommand(L);
	if (!slashcommand.isValidTable())
		return 0;

	CorpseSlashCommand* slashCommand = new CorpseSlashCommand(slashcommand.getStringField("name"), server);
	parseSlashCommand(slashcommand, slashCommand);
	return 1;
}

int CommandConfigManager::addCounterAttackSlashCommand(lua_State* L) {
	LuaObject slashcommand(L);
	if (!slashcommand.isValidTable())
		return 0;

	CounterAttackSlashCommand* slashCommand = new CounterAttackSlashCommand(slashcommand.getStringField("name"), server);
	parseSlashCommand(slashcommand, slashCommand);
	return 1;
}

int CommandConfigManager::addCountertoxinSlashCommand(lua_State* L) {
	LuaObject slashcommand(L);
	if (!slashcommand.isValidTable())
		return 0;

	CountertoxinSlashCommand* slashCommand = new CountertoxinSlashCommand(slashcommand.getStringField("name"), server);
	parseSlashCommand(slashcommand, slashCommand);
	return 1;
}

int CommandConfigManager::addCountertoxinSpraySlashCommand(lua_State* L) {
	LuaObject slashcommand(L);
	if (!slashcommand.isValidTable())
		return 0;

	CountertoxinSpraySlashCommand* slashCommand = new CountertoxinSpraySlashCommand(slashcommand.getStringField("name"), server);
	parseSlashCommand(slashcommand, slashCommand);
	return 1;
}

int CommandConfigManager::addCoupDeGraceSlashCommand(lua_State* L) {
	LuaObject slashcommand(L);
	if (!slashcommand.isValidTable())
		return 0;

	CoupDeGraceSlashCommand* slashCommand = new CoupDeGraceSlashCommand(slashcommand.getStringField("name"), server);
	parseSlashCommand(slashcommand, slashCommand);
	return 1;
}

int CommandConfigManager::addCoverSlashCommand(lua_State* L) {
	LuaObject slashcommand(L);
	if (!slashcommand.isValidTable())
		return 0;

	CoverSlashCommand* slashCommand = new CoverSlashCommand(slashcommand.getStringField("name"), server);
	parseSlashCommand(slashcommand, slashCommand);
	return 1;
}

int CommandConfigManager::addCoverchargeSlashCommand(lua_State* L) {
	LuaObject slashcommand(L);
	if (!slashcommand.isValidTable())
		return 0;

	CoverchargeSlashCommand* slashCommand = new CoverchargeSlashCommand(slashcommand.getStringField("name"), server);
	parseSlashCommand(slashcommand, slashCommand);
	return 1;
}

int CommandConfigManager::addCraftSlashCommand(lua_State* L) {
	LuaObject slashcommand(L);
	if (!slashcommand.isValidTable())
		return 0;

	CraftSlashCommand* slashCommand = new CraftSlashCommand(slashcommand.getStringField("name"), server);
	parseSlashCommand(slashcommand, slashCommand);
	return 1;
}

int CommandConfigManager::addCreateCreatureSlashCommand(lua_State* L) {
	LuaObject slashcommand(L);
	if (!slashcommand.isValidTable())
		return 0;

	CreateCreatureSlashCommand* slashCommand = new CreateCreatureSlashCommand(slashcommand.getStringField("name"), server);
	parseSlashCommand(slashcommand, slashCommand);
	return 1;
}

int CommandConfigManager::addCreateManfSchematicSlashCommand(lua_State* L) {
	LuaObject slashcommand(L);
	if (!slashcommand.isValidTable())
		return 0;

	CreateManfSchematicSlashCommand* slashCommand = new CreateManfSchematicSlashCommand(slashcommand.getStringField("name"), server);
	parseSlashCommand(slashcommand, slashCommand);
	return 1;
}

int CommandConfigManager::addCreateMissionElementSlashCommand(lua_State* L) {
	LuaObject slashcommand(L);
	if (!slashcommand.isValidTable())
		return 0;

	CreateMissionElementSlashCommand* slashCommand = new CreateMissionElementSlashCommand(slashcommand.getStringField("name"), server);
	parseSlashCommand(slashcommand, slashCommand);
	return 1;
}

int CommandConfigManager::addCreateNPCSlashCommand(lua_State* L) {
	LuaObject slashcommand(L);
	if (!slashcommand.isValidTable())
		return 0;

	CreateNPCSlashCommand* slashCommand = new CreateNPCSlashCommand(slashcommand.getStringField("name"), server);
	parseSlashCommand(slashcommand, slashCommand);
	return 1;
}

int CommandConfigManager::addCreatePrototypeSlashCommand(lua_State* L) {
	LuaObject slashcommand(L);
	if (!slashcommand.isValidTable())
		return 0;

	CreatePrototypeSlashCommand* slashCommand = new CreatePrototypeSlashCommand(slashcommand.getStringField("name"), server);
	parseSlashCommand(slashcommand, slashCommand);
	return 1;
}

int CommandConfigManager::addCreateSpawningElementSlashCommand(lua_State* L) {
	LuaObject slashcommand(L);
	if (!slashcommand.isValidTable())
		return 0;

	CreateSpawningElementSlashCommand* slashCommand = new CreateSpawningElementSlashCommand(slashcommand.getStringField("name"), server);
	parseSlashCommand(slashcommand, slashCommand);
	return 1;
}

int CommandConfigManager::addCreateSpawningElementWithDifficultySlashCommand(lua_State* L) {
	LuaObject slashcommand(L);
	if (!slashcommand.isValidTable())
		return 0;

	CreateSpawningElementWithDifficultySlashCommand* slashCommand = new CreateSpawningElementWithDifficultySlashCommand(slashcommand.getStringField("name"), server);
	parseSlashCommand(slashcommand, slashCommand);
	return 1;
}

int CommandConfigManager::addCreatureAreaAttackSlashCommand(lua_State* L) {
	LuaObject slashcommand(L);
	if (!slashcommand.isValidTable())
		return 0;

	CreatureAreaAttackSlashCommand* slashCommand = new CreatureAreaAttackSlashCommand(slashcommand.getStringField("name"), server);
	parseSlashCommand(slashcommand, slashCommand);
	return 1;
}

int CommandConfigManager::addCreatureAreaBleedingSlashCommand(lua_State* L) {
	LuaObject slashcommand(L);
	if (!slashcommand.isValidTable())
		return 0;

	CreatureAreaBleedingSlashCommand* slashCommand = new CreatureAreaBleedingSlashCommand(slashcommand.getStringField("name"), server);
	parseSlashCommand(slashcommand, slashCommand);
	return 1;
}

int CommandConfigManager::addCreatureAreaComboSlashCommand(lua_State* L) {
	LuaObject slashcommand(L);
	if (!slashcommand.isValidTable())
		return 0;

	CreatureAreaComboSlashCommand* slashCommand = new CreatureAreaComboSlashCommand(slashcommand.getStringField("name"), server);
	parseSlashCommand(slashcommand, slashCommand);
	return 1;
}

int CommandConfigManager::addCreatureAreaDiseaseSlashCommand(lua_State* L) {
	LuaObject slashcommand(L);
	if (!slashcommand.isValidTable())
		return 0;

	CreatureAreaDiseaseSlashCommand* slashCommand = new CreatureAreaDiseaseSlashCommand(slashcommand.getStringField("name"), server);
	parseSlashCommand(slashcommand, slashCommand);
	return 1;
}

int CommandConfigManager::addCreatureAreaKnockdownSlashCommand(lua_State* L) {
	LuaObject slashcommand(L);
	if (!slashcommand.isValidTable())
		return 0;

	CreatureAreaKnockdownSlashCommand* slashCommand = new CreatureAreaKnockdownSlashCommand(slashcommand.getStringField("name"), server);
	parseSlashCommand(slashcommand, slashCommand);
	return 1;
}

int CommandConfigManager::addCreatureAreaPoisonSlashCommand(lua_State* L) {
	LuaObject slashcommand(L);
	if (!slashcommand.isValidTable())
		return 0;

	CreatureAreaPoisonSlashCommand* slashCommand = new CreatureAreaPoisonSlashCommand(slashcommand.getStringField("name"), server);
	parseSlashCommand(slashcommand, slashCommand);
	return 1;
}

int CommandConfigManager::addCreatureBlindAttackSlashCommand(lua_State* L) {
	LuaObject slashcommand(L);
	if (!slashcommand.isValidTable())
		return 0;

	CreatureBlindAttackSlashCommand* slashCommand = new CreatureBlindAttackSlashCommand(slashcommand.getStringField("name"), server);
	parseSlashCommand(slashcommand, slashCommand);
	return 1;
}

int CommandConfigManager::addCreatureDizzyAttackSlashCommand(lua_State* L) {
	LuaObject slashcommand(L);
	if (!slashcommand.isValidTable())
		return 0;

	CreatureDizzyAttackSlashCommand* slashCommand = new CreatureDizzyAttackSlashCommand(slashcommand.getStringField("name"), server);
	parseSlashCommand(slashcommand, slashCommand);
	return 1;
}

int CommandConfigManager::addCreatureIntimidationAttackSlashCommand(lua_State* L) {
	LuaObject slashcommand(L);
	if (!slashcommand.isValidTable())
		return 0;

	CreatureIntimidationAttackSlashCommand* slashCommand = new CreatureIntimidationAttackSlashCommand(slashcommand.getStringField("name"), server);
	parseSlashCommand(slashcommand, slashCommand);
	return 1;
}

int CommandConfigManager::addCreatureKnockdownAttackSlashCommand(lua_State* L) {
	LuaObject slashcommand(L);
	if (!slashcommand.isValidTable())
		return 0;

	CreatureKnockdownAttackSlashCommand* slashCommand = new CreatureKnockdownAttackSlashCommand(slashcommand.getStringField("name"), server);
	parseSlashCommand(slashcommand, slashCommand);
	return 1;
}

int CommandConfigManager::addCreatureMeleeAttackSlashCommand(lua_State* L) {
	LuaObject slashcommand(L);
	if (!slashcommand.isValidTable())
		return 0;

	CreatureMeleeAttackSlashCommand* slashCommand = new CreatureMeleeAttackSlashCommand(slashcommand.getStringField("name"), server);
	parseSlashCommand(slashcommand, slashCommand);
	return 1;
}

int CommandConfigManager::addCreaturePostureDownAttackSlashCommand(lua_State* L) {
	LuaObject slashcommand(L);
	if (!slashcommand.isValidTable())
		return 0;

	CreaturePostureDownAttackSlashCommand* slashCommand = new CreaturePostureDownAttackSlashCommand(slashcommand.getStringField("name"), server);
	parseSlashCommand(slashcommand, slashCommand);
	return 1;
}

int CommandConfigManager::addCreaturePostureUpAttackSlashCommand(lua_State* L) {
	LuaObject slashcommand(L);
	if (!slashcommand.isValidTable())
		return 0;

	CreaturePostureUpAttackSlashCommand* slashCommand = new CreaturePostureUpAttackSlashCommand(slashcommand.getStringField("name"), server);
	parseSlashCommand(slashcommand, slashCommand);
	return 1;
}

int CommandConfigManager::addCreatureRangedAttackSlashCommand(lua_State* L) {
	LuaObject slashcommand(L);
	if (!slashcommand.isValidTable())
		return 0;

	CreatureRangedAttackSlashCommand* slashCommand = new CreatureRangedAttackSlashCommand(slashcommand.getStringField("name"), server);
	parseSlashCommand(slashcommand, slashCommand);
	return 1;
}

int CommandConfigManager::addCreatureStunAttackSlashCommand(lua_State* L) {
	LuaObject slashcommand(L);
	if (!slashcommand.isValidTable())
		return 0;

	CreatureStunAttackSlashCommand* slashCommand = new CreatureStunAttackSlashCommand(slashcommand.getStringField("name"), server);
	parseSlashCommand(slashcommand, slashCommand);
	return 1;
}

int CommandConfigManager::addCreditsSlashCommand(lua_State* L) {
	LuaObject slashcommand(L);
	if (!slashcommand.isValidTable())
		return 0;

	CreditsSlashCommand* slashCommand = new CreditsSlashCommand(slashcommand.getStringField("name"), server);
	parseSlashCommand(slashcommand, slashCommand);
	return 1;
}

int CommandConfigManager::addCrippleAttackSlashCommand(lua_State* L) {
	LuaObject slashcommand(L);
	if (!slashcommand.isValidTable())
		return 0;

	CrippleAttackSlashCommand* slashCommand = new CrippleAttackSlashCommand(slashcommand.getStringField("name"), server);
	parseSlashCommand(slashcommand, slashCommand);
	return 1;
}

int CommandConfigManager::addCripplingShotSlashCommand(lua_State* L) {
	LuaObject slashcommand(L);
	if (!slashcommand.isValidTable())
		return 0;

	CripplingShotSlashCommand* slashCommand = new CripplingShotSlashCommand(slashcommand.getStringField("name"), server);
	parseSlashCommand(slashcommand, slashCommand);
	return 1;
}

int CommandConfigManager::addCriticalShotSlashCommand(lua_State* L) {
	LuaObject slashcommand(L);
	if (!slashcommand.isValidTable())
		return 0;

	CriticalShotSlashCommand* slashCommand = new CriticalShotSlashCommand(slashcommand.getStringField("name"), server);
	parseSlashCommand(slashcommand, slashCommand);
	return 1;
}

int CommandConfigManager::addCriticalStrikeSlashCommand(lua_State* L) {
	LuaObject slashcommand(L);
	if (!slashcommand.isValidTable())
		return 0;

	CriticalStrikeSlashCommand* slashCommand = new CriticalStrikeSlashCommand(slashcommand.getStringField("name"), server);
	parseSlashCommand(slashcommand, slashCommand);
	return 1;
}

int CommandConfigManager::addCsAppendCommentSlashCommand(lua_State* L) {
	LuaObject slashcommand(L);
	if (!slashcommand.isValidTable())
		return 0;

	CsAppendCommentSlashCommand* slashCommand = new CsAppendCommentSlashCommand(slashcommand.getStringField("name"), server);
	parseSlashCommand(slashcommand, slashCommand);
	return 1;
}

int CommandConfigManager::addCsCancelTicketSlashCommand(lua_State* L) {
	LuaObject slashcommand(L);
	if (!slashcommand.isValidTable())
		return 0;

	CsCancelTicketSlashCommand* slashCommand = new CsCancelTicketSlashCommand(slashcommand.getStringField("name"), server);
	parseSlashCommand(slashcommand, slashCommand);
	return 1;
}

int CommandConfigManager::addCsConnectPlayerSlashCommand(lua_State* L) {
	LuaObject slashcommand(L);
	if (!slashcommand.isValidTable())
		return 0;

	CsConnectPlayerSlashCommand* slashCommand = new CsConnectPlayerSlashCommand(slashcommand.getStringField("name"), server);
	parseSlashCommand(slashcommand, slashCommand);
	return 1;
}

int CommandConfigManager::addCsCreateTicketSlashCommand(lua_State* L) {
	LuaObject slashcommand(L);
	if (!slashcommand.isValidTable())
		return 0;

	CsCreateTicketSlashCommand* slashCommand = new CsCreateTicketSlashCommand(slashcommand.getStringField("name"), server);
	parseSlashCommand(slashcommand, slashCommand);
	return 1;
}

int CommandConfigManager::addCsDisconnectPlayerSlashCommand(lua_State* L) {
	LuaObject slashcommand(L);
	if (!slashcommand.isValidTable())
		return 0;

	CsDisconnectPlayerSlashCommand* slashCommand = new CsDisconnectPlayerSlashCommand(slashcommand.getStringField("name"), server);
	parseSlashCommand(slashcommand, slashCommand);
	return 1;
}

int CommandConfigManager::addCsGetArticleSlashCommand(lua_State* L) {
	LuaObject slashcommand(L);
	if (!slashcommand.isValidTable())
		return 0;

	CsGetArticleSlashCommand* slashCommand = new CsGetArticleSlashCommand(slashcommand.getStringField("name"), server);
	parseSlashCommand(slashcommand, slashCommand);
	return 1;
}

int CommandConfigManager::addCsGetCommentsSlashCommand(lua_State* L) {
	LuaObject slashcommand(L);
	if (!slashcommand.isValidTable())
		return 0;

	CsGetCommentsSlashCommand* slashCommand = new CsGetCommentsSlashCommand(slashcommand.getStringField("name"), server);
	parseSlashCommand(slashcommand, slashCommand);
	return 1;
}

int CommandConfigManager::addCsGetTicketsSlashCommand(lua_State* L) {
	LuaObject slashcommand(L);
	if (!slashcommand.isValidTable())
		return 0;

	CsGetTicketsSlashCommand* slashCommand = new CsGetTicketsSlashCommand(slashcommand.getStringField("name"), server);
	parseSlashCommand(slashcommand, slashCommand);
	return 1;
}

int CommandConfigManager::addCsRequestCategoriesSlashCommand(lua_State* L) {
	LuaObject slashcommand(L);
	if (!slashcommand.isValidTable())
		return 0;

	CsRequestCategoriesSlashCommand* slashCommand = new CsRequestCategoriesSlashCommand(slashcommand.getStringField("name"), server);
	parseSlashCommand(slashcommand, slashCommand);
	return 1;
}

int CommandConfigManager::addCsSearchKnowledgeBaseSlashCommand(lua_State* L) {
	LuaObject slashcommand(L);
	if (!slashcommand.isValidTable())
		return 0;

	CsSearchKnowledgeBaseSlashCommand* slashCommand = new CsSearchKnowledgeBaseSlashCommand(slashcommand.getStringField("name"), server);
	parseSlashCommand(slashcommand, slashCommand);
	return 1;
}

int CommandConfigManager::addCuiConsentResponseSlashCommand(lua_State* L) {
	LuaObject slashcommand(L);
	if (!slashcommand.isValidTable())
		return 0;

	CuiConsentResponseSlashCommand* slashCommand = new CuiConsentResponseSlashCommand(slashcommand.getStringField("name"), server);
	parseSlashCommand(slashcommand, slashCommand);
	return 1;
}

int CommandConfigManager::addCustomizeDroidSlashCommand(lua_State* L) {
	LuaObject slashcommand(L);
	if (!slashcommand.isValidTable())
		return 0;

	CustomizeDroidSlashCommand* slashCommand = new CustomizeDroidSlashCommand(slashcommand.getStringField("name"), server);
	parseSlashCommand(slashcommand, slashCommand);
	return 1;
}

int CommandConfigManager::addCustomizeVehicleSlashCommand(lua_State* L) {
	LuaObject slashcommand(L);
	if (!slashcommand.isValidTable())
		return 0;

	CustomizeVehicleSlashCommand* slashCommand = new CustomizeVehicleSlashCommand(slashcommand.getStringField("name"), server);
	parseSlashCommand(slashcommand, slashCommand);
	return 1;
}

int CommandConfigManager::addCyborgBurstRunSlashCommand(lua_State* L) {
	LuaObject slashcommand(L);
	if (!slashcommand.isValidTable())
		return 0;

	CyborgBurstRunSlashCommand* slashCommand = new CyborgBurstRunSlashCommand(slashcommand.getStringField("name"), server);
	parseSlashCommand(slashcommand, slashCommand);
	return 1;
}

int CommandConfigManager::addCyborgCriticalSnipeSlashCommand(lua_State* L) {
	LuaObject slashcommand(L);
	if (!slashcommand.isValidTable())
		return 0;

	CyborgCriticalSnipeSlashCommand* slashCommand = new CyborgCriticalSnipeSlashCommand(slashcommand.getStringField("name"), server);
	parseSlashCommand(slashcommand, slashCommand);
	return 1;
}

int CommandConfigManager::addCyborgKickDownSlashCommand(lua_State* L) {
	LuaObject slashcommand(L);
	if (!slashcommand.isValidTable())
		return 0;

	CyborgKickDownSlashCommand* slashCommand = new CyborgKickDownSlashCommand(slashcommand.getStringField("name"), server);
	parseSlashCommand(slashcommand, slashCommand);
	return 1;
}

int CommandConfigManager::addCyborgLightningSlashCommand(lua_State* L) {
	LuaObject slashcommand(L);
	if (!slashcommand.isValidTable())
		return 0;

	CyborgLightningSlashCommand* slashCommand = new CyborgLightningSlashCommand(slashcommand.getStringField("name"), server);
	parseSlashCommand(slashcommand, slashCommand);
	return 1;
}

int CommandConfigManager::addCyborgReviveSlashCommand(lua_State* L) {
	LuaObject slashcommand(L);
	if (!slashcommand.isValidTable())
		return 0;

	CyborgReviveSlashCommand* slashCommand = new CyborgReviveSlashCommand(slashcommand.getStringField("name"), server);
	parseSlashCommand(slashcommand, slashCommand);
	return 1;
}

int CommandConfigManager::addCyborgStrengthBuffSlashCommand(lua_State* L) {
	LuaObject slashcommand(L);
	if (!slashcommand.isValidTable())
		return 0;

	CyborgStrengthBuffSlashCommand* slashCommand = new CyborgStrengthBuffSlashCommand(slashcommand.getStringField("name"), server);
	parseSlashCommand(slashcommand, slashCommand);
	return 1;
}

int CommandConfigManager::addCyborgSureShotSlashCommand(lua_State* L) {
	LuaObject slashcommand(L);
	if (!slashcommand.isValidTable())
		return 0;

	CyborgSureShotSlashCommand* slashCommand = new CyborgSureShotSlashCommand(slashcommand.getStringField("name"), server);
	parseSlashCommand(slashcommand, slashCommand);
	return 1;
}

int CommandConfigManager::addDatabaseSlashCommand(lua_State* L) {
	LuaObject slashcommand(L);
	if (!slashcommand.isValidTable())
		return 0;

	DatabaseSlashCommand* slashCommand = new DatabaseSlashCommand(slashcommand.getStringField("name"), server);
	parseSlashCommand(slashcommand, slashCommand);
	return 1;
}

int CommandConfigManager::addDazzleSlashCommand(lua_State* L) {
	LuaObject slashcommand(L);
	if (!slashcommand.isValidTable())
		return 0;

	DazzleSlashCommand* slashCommand = new DazzleSlashCommand(slashcommand.getStringField("name"), server);
	parseSlashCommand(slashcommand, slashCommand);
	return 1;
}

int CommandConfigManager::addDeactivateQuestSlashCommand(lua_State* L) {
	LuaObject slashcommand(L);
	if (!slashcommand.isValidTable())
		return 0;

	DeactivateQuestSlashCommand* slashCommand = new DeactivateQuestSlashCommand(slashcommand.getStringField("name"), server);
	parseSlashCommand(slashcommand, slashCommand);
	return 1;
}

int CommandConfigManager::addDeathBlowSlashCommand(lua_State* L) {
	LuaObject slashcommand(L);
	if (!slashcommand.isValidTable())
		return 0;

	DeathBlowSlashCommand* slashCommand = new DeathBlowSlashCommand(slashcommand.getStringField("name"), server);
	parseSlashCommand(slashcommand, slashCommand);
	return 1;
}

int CommandConfigManager::addDeathCountSlashCommand(lua_State* L) {
	LuaObject slashcommand(L);
	if (!slashcommand.isValidTable())
		return 0;

	DeathCountSlashCommand* slashCommand = new DeathCountSlashCommand(slashcommand.getStringField("name"), server);
	parseSlashCommand(slashcommand, slashCommand);
	return 1;
}

int CommandConfigManager::addDeclareOvertSlashCommand(lua_State* L) {
	LuaObject slashcommand(L);
	if (!slashcommand.isValidTable())
		return 0;

	DeclareOvertSlashCommand* slashCommand = new DeclareOvertSlashCommand(slashcommand.getStringField("name"), server);
	parseSlashCommand(slashcommand, slashCommand);
	return 1;
}

int CommandConfigManager::addDeclareresidenceSlashCommand(lua_State* L) {
	LuaObject slashcommand(L);
	if (!slashcommand.isValidTable())
		return 0;

	DeclareresidenceSlashCommand* slashCommand = new DeclareresidenceSlashCommand(slashcommand.getStringField("name"), server);
	parseSlashCommand(slashcommand, slashCommand);
	return 1;
}

int CommandConfigManager::addDeclineSlashCommand(lua_State* L) {
	LuaObject slashcommand(L);
	if (!slashcommand.isValidTable())
		return 0;

	DeclineSlashCommand* slashCommand = new DeclineSlashCommand(slashcommand.getStringField("name"), server);
	parseSlashCommand(slashcommand, slashCommand);
	return 1;
}

int CommandConfigManager::addDecontaminateSlashCommand(lua_State* L) {
	LuaObject slashcommand(L);
	if (!slashcommand.isValidTable())
		return 0;

	DecontaminateSlashCommand* slashCommand = new DecontaminateSlashCommand(slashcommand.getStringField("name"), server);
	parseSlashCommand(slashcommand, slashCommand);
	return 1;
}

int CommandConfigManager::addDefaultActionSlashCommand(lua_State* L) {
	LuaObject slashcommand(L);
	if (!slashcommand.isValidTable())
		return 0;

	DefaultActionSlashCommand* slashCommand = new DefaultActionSlashCommand(slashcommand.getStringField("name"), server);
	parseSlashCommand(slashcommand, slashCommand);
	return 1;
}

int CommandConfigManager::addDefaultAttackSlashCommand(lua_State* L) {
	LuaObject slashcommand(L);
	if (!slashcommand.isValidTable())
		return 0;

	DefaultAttackSlashCommand* slashCommand = new DefaultAttackSlashCommand(slashcommand.getStringField("name"), server);
	parseSlashCommand(slashcommand, slashCommand);
	return 1;
}

int CommandConfigManager::addDefuseMinefieldSlashCommand(lua_State* L) {
	LuaObject slashcommand(L);
	if (!slashcommand.isValidTable())
		return 0;

	DefuseMinefieldSlashCommand* slashCommand = new DefuseMinefieldSlashCommand(slashcommand.getStringField("name"), server);
	parseSlashCommand(slashcommand, slashCommand);
	return 1;
}

int CommandConfigManager::addDelegateFactionPointsSlashCommand(lua_State* L) {
	LuaObject slashcommand(L);
	if (!slashcommand.isValidTable())
		return 0;

	DelegateFactionPointsSlashCommand* slashCommand = new DelegateFactionPointsSlashCommand(slashcommand.getStringField("name"), server);
	parseSlashCommand(slashcommand, slashCommand);
	return 1;
}

int CommandConfigManager::addDenyServiceSlashCommand(lua_State* L) {
	LuaObject slashcommand(L);
	if (!slashcommand.isValidTable())
		return 0;

	DenyServiceSlashCommand* slashCommand = new DenyServiceSlashCommand(slashcommand.getStringField("name"), server);
	parseSlashCommand(slashcommand, slashCommand);
	return 1;
}

int CommandConfigManager::addDeployTrapSlashCommand(lua_State* L) {
	LuaObject slashcommand(L);
	if (!slashcommand.isValidTable())
		return 0;

	DeployTrapSlashCommand* slashCommand = new DeployTrapSlashCommand(slashcommand.getStringField("name"), server);
	parseSlashCommand(slashcommand, slashCommand);
	return 1;
}

int CommandConfigManager::addDestroySlashCommand(lua_State* L) {
	LuaObject slashcommand(L);
	if (!slashcommand.isValidTable())
		return 0;

	DestroySlashCommand* slashCommand = new DestroySlashCommand(slashcommand.getStringField("name"), server);
	parseSlashCommand(slashcommand, slashCommand);
	return 1;
}

int CommandConfigManager::addDestroystructureSlashCommand(lua_State* L) {
	LuaObject slashcommand(L);
	if (!slashcommand.isValidTable())
		return 0;

	DestroystructureSlashCommand* slashCommand = new DestroystructureSlashCommand(slashcommand.getStringField("name"), server);
	parseSlashCommand(slashcommand, slashCommand);
	return 1;
}

int CommandConfigManager::addDetonateDroidSlashCommand(lua_State* L) {
	LuaObject slashcommand(L);
	if (!slashcommand.isValidTable())
		return 0;

	DetonateDroidSlashCommand* slashCommand = new DetonateDroidSlashCommand(slashcommand.getStringField("name"), server);
	parseSlashCommand(slashcommand, slashCommand);
	return 1;
}

int CommandConfigManager::addDeuteriumTossSlashCommand(lua_State* L) {
	LuaObject slashcommand(L);
	if (!slashcommand.isValidTable())
		return 0;

	DeuteriumTossSlashCommand* slashCommand = new DeuteriumTossSlashCommand(slashcommand.getStringField("name"), server);
	parseSlashCommand(slashcommand, slashCommand);
	return 1;
}

int CommandConfigManager::addDiagnoseSlashCommand(lua_State* L) {
	LuaObject slashcommand(L);
	if (!slashcommand.isValidTable())
		return 0;

	DiagnoseSlashCommand* slashCommand = new DiagnoseSlashCommand(slashcommand.getStringField("name"), server);
	parseSlashCommand(slashcommand, slashCommand);
	return 1;
}

int CommandConfigManager::addDisarmingShotSlashCommand(lua_State* L) {
	LuaObject slashcommand(L);
	if (!slashcommand.isValidTable())
		return 0;

	DisarmingShotSlashCommand* slashCommand = new DisarmingShotSlashCommand(slashcommand.getStringField("name"), server);
	parseSlashCommand(slashcommand, slashCommand);
	return 1;
}

int CommandConfigManager::addDisbandSlashCommand(lua_State* L) {
	LuaObject slashcommand(L);
	if (!slashcommand.isValidTable())
		return 0;

	DisbandSlashCommand* slashCommand = new DisbandSlashCommand(slashcommand.getStringField("name"), server);
	parseSlashCommand(slashcommand, slashCommand);
	return 1;
}

int CommandConfigManager::addDiseaseInnoculationSlashCommand(lua_State* L) {
	LuaObject slashcommand(L);
	if (!slashcommand.isValidTable())
		return 0;

	DiseaseInnoculationSlashCommand* slashCommand = new DiseaseInnoculationSlashCommand(slashcommand.getStringField("name"), server);
	parseSlashCommand(slashcommand, slashCommand);
	return 1;
}

int CommandConfigManager::addDisinfectSlashCommand(lua_State* L) {
	LuaObject slashcommand(L);
	if (!slashcommand.isValidTable())
		return 0;

	DisinfectSlashCommand* slashCommand = new DisinfectSlashCommand(slashcommand.getStringField("name"), server);
	parseSlashCommand(slashcommand, slashCommand);
	return 1;
}

int CommandConfigManager::addDismissGroupMemberSlashCommand(lua_State* L) {
	LuaObject slashcommand(L);
	if (!slashcommand.isValidTable())
		return 0;

	DismissGroupMemberSlashCommand* slashCommand = new DismissGroupMemberSlashCommand(slashcommand.getStringField("name"), server);
	parseSlashCommand(slashcommand, slashCommand);
	return 1;
}

int CommandConfigManager::addDismountSlashCommand(lua_State* L) {
	LuaObject slashcommand(L);
	if (!slashcommand.isValidTable())
		return 0;

	DismountSlashCommand* slashCommand = new DismountSlashCommand(slashcommand.getStringField("name"), server);
	parseSlashCommand(slashcommand, slashCommand);
	return 1;
}

int CommandConfigManager::addDismountandstoreSlashCommand(lua_State* L) {
	LuaObject slashcommand(L);
	if (!slashcommand.isValidTable())
		return 0;

	DismountandstoreSlashCommand* slashCommand = new DismountandstoreSlashCommand(slashcommand.getStringField("name"), server);
	parseSlashCommand(slashcommand, slashCommand);
	return 1;
}

int CommandConfigManager::addDistractSlashCommand(lua_State* L) {
	LuaObject slashcommand(L);
	if (!slashcommand.isValidTable())
		return 0;

	DistractSlashCommand* slashCommand = new DistractSlashCommand(slashcommand.getStringField("name"), server);
	parseSlashCommand(slashcommand, slashCommand);
	return 1;
}

int CommandConfigManager::addDiveShotSlashCommand(lua_State* L) {
	LuaObject slashcommand(L);
	if (!slashcommand.isValidTable())
		return 0;

	DiveShotSlashCommand* slashCommand = new DiveShotSlashCommand(slashcommand.getStringField("name"), server);
	parseSlashCommand(slashcommand, slashCommand);
	return 1;
}

int CommandConfigManager::addDizzyAttackSlashCommand(lua_State* L) {
	LuaObject slashcommand(L);
	if (!slashcommand.isValidTable())
		return 0;

	DizzyAttackSlashCommand* slashCommand = new DizzyAttackSlashCommand(slashcommand.getStringField("name"), server);
	parseSlashCommand(slashcommand, slashCommand);
	return 1;
}

int CommandConfigManager::addDizzyRecoverySlashCommand(lua_State* L) {
	LuaObject slashcommand(L);
	if (!slashcommand.isValidTable())
		return 0;

	DizzyRecoverySlashCommand* slashCommand = new DizzyRecoverySlashCommand(slashcommand.getStringField("name"), server);
	parseSlashCommand(slashcommand, slashCommand);
	return 1;
}

int CommandConfigManager::addDominateMindSlashCommand(lua_State* L) {
	LuaObject slashcommand(L);
	if (!slashcommand.isValidTable())
		return 0;

	DominateMindSlashCommand* slashCommand = new DominateMindSlashCommand(slashcommand.getStringField("name"), server);
	parseSlashCommand(slashcommand, slashCommand);
	return 1;
}

int CommandConfigManager::addDragPlayerSlashCommand(lua_State* L) {
	LuaObject slashcommand(L);
	if (!slashcommand.isValidTable())
		return 0;

	DragPlayerSlashCommand* slashCommand = new DragPlayerSlashCommand(slashcommand.getStringField("name"), server);
	parseSlashCommand(slashcommand, slashCommand);
	return 1;
}

int CommandConfigManager::addDrainForceSlashCommand(lua_State* L) {
	LuaObject slashcommand(L);
	if (!slashcommand.isValidTable())
		return 0;

	DrainForceSlashCommand* slashCommand = new DrainForceSlashCommand(slashcommand.getStringField("name"), server);
	parseSlashCommand(slashcommand, slashCommand);
	return 1;
}

int CommandConfigManager::addDuelSlashCommand(lua_State* L) {
	LuaObject slashcommand(L);
	if (!slashcommand.isValidTable())
		return 0;

	DuelSlashCommand* slashCommand = new DuelSlashCommand(slashcommand.getStringField("name"), server);
	parseSlashCommand(slashcommand, slashCommand);
	return 1;
}

int CommandConfigManager::addDuelistStanceSlashCommand(lua_State* L) {
	LuaObject slashcommand(L);
	if (!slashcommand.isValidTable())
		return 0;

	DuelistStanceSlashCommand* slashCommand = new DuelistStanceSlashCommand(slashcommand.getStringField("name"), server);
	parseSlashCommand(slashcommand, slashCommand);
	return 1;
}

int CommandConfigManager::addDumpTargetInformationSlashCommand(lua_State* L) {
	LuaObject slashcommand(L);
	if (!slashcommand.isValidTable())
		return 0;

	DumpTargetInformationSlashCommand* slashCommand = new DumpTargetInformationSlashCommand(slashcommand.getStringField("name"), server);
	parseSlashCommand(slashcommand, slashCommand);
	return 1;
}

int CommandConfigManager::addDumpZoneInformationSlashCommand(lua_State* L) {
	LuaObject slashcommand(L);
	if (!slashcommand.isValidTable())
		return 0;

	DumpZoneInformationSlashCommand* slashCommand = new DumpZoneInformationSlashCommand(slashcommand.getStringField("name"), server);
	parseSlashCommand(slashcommand, slashCommand);
	return 1;
}

int CommandConfigManager::addEatSlashCommand(lua_State* L) {
	LuaObject slashcommand(L);
	if (!slashcommand.isValidTable())
		return 0;

	EatSlashCommand* slashCommand = new EatSlashCommand(slashcommand.getStringField("name"), server);
	parseSlashCommand(slashcommand, slashCommand);
	return 1;
}

int CommandConfigManager::addEditAppearanceSlashCommand(lua_State* L) {
	LuaObject slashcommand(L);
	if (!slashcommand.isValidTable())
		return 0;

	EditAppearanceSlashCommand* slashCommand = new EditAppearanceSlashCommand(slashcommand.getStringField("name"), server);
	parseSlashCommand(slashcommand, slashCommand);
	return 1;
}

int CommandConfigManager::addEditBankSlashCommand(lua_State* L) {
	LuaObject slashcommand(L);
	if (!slashcommand.isValidTable())
		return 0;

	EditBankSlashCommand* slashCommand = new EditBankSlashCommand(slashcommand.getStringField("name"), server);
	parseSlashCommand(slashcommand, slashCommand);
	return 1;
}

int CommandConfigManager::addEditBankAccountSlashCommand(lua_State* L) {
	LuaObject slashcommand(L);
	if (!slashcommand.isValidTable())
		return 0;

	EditBankAccountSlashCommand* slashCommand = new EditBankAccountSlashCommand(slashcommand.getStringField("name"), server);
	parseSlashCommand(slashcommand, slashCommand);
	return 1;
}

int CommandConfigManager::addEditStatsSlashCommand(lua_State* L) {
	LuaObject slashcommand(L);
	if (!slashcommand.isValidTable())
		return 0;

	EditStatsSlashCommand* slashCommand = new EditStatsSlashCommand(slashcommand.getStringField("name"), server);
	parseSlashCommand(slashcommand, slashCommand);
	return 1;
}

int CommandConfigManager::addElectrolyteDrainSlashCommand(lua_State* L) {
	LuaObject slashcommand(L);
	if (!slashcommand.isValidTable())
		return 0;

	ElectrolyteDrainSlashCommand* slashCommand = new ElectrolyteDrainSlashCommand(slashcommand.getStringField("name"), server);
	parseSlashCommand(slashcommand, slashCommand);
	return 1;
}

int CommandConfigManager::addEmboldenpetsSlashCommand(lua_State* L) {
	LuaObject slashcommand(L);
	if (!slashcommand.isValidTable())
		return 0;

	EmboldenpetsSlashCommand* slashCommand = new EmboldenpetsSlashCommand(slashcommand.getStringField("name"), server);
	parseSlashCommand(slashcommand, slashCommand);
	return 1;
}

int CommandConfigManager::addEmptyMailTargetSlashCommand(lua_State* L) {
	LuaObject slashcommand(L);
	if (!slashcommand.isValidTable())
		return 0;

	EmptyMailTargetSlashCommand* slashCommand = new EmptyMailTargetSlashCommand(slashcommand.getStringField("name"), server);
	parseSlashCommand(slashcommand, slashCommand);
	return 1;
}

int CommandConfigManager::addEndDuelSlashCommand(lua_State* L) {
	LuaObject slashcommand(L);
	if (!slashcommand.isValidTable())
		return 0;

	EndDuelSlashCommand* slashCommand = new EndDuelSlashCommand(slashcommand.getStringField("name"), server);
	parseSlashCommand(slashcommand, slashCommand);
	return 1;
}

int CommandConfigManager::addEndorphineInjectionSlashCommand(lua_State* L) {
	LuaObject slashcommand(L);
	if (!slashcommand.isValidTable())
		return 0;

	EndorphineInjectionSlashCommand* slashCommand = new EndorphineInjectionSlashCommand(slashcommand.getStringField("name"), server);
	parseSlashCommand(slashcommand, slashCommand);
	return 1;
}

int CommandConfigManager::addEnragepetsSlashCommand(lua_State* L) {
	LuaObject slashcommand(L);
	if (!slashcommand.isValidTable())
		return 0;

	EnragepetsSlashCommand* slashCommand = new EnragepetsSlashCommand(slashcommand.getStringField("name"), server);
	parseSlashCommand(slashcommand, slashCommand);
	return 1;
}

int CommandConfigManager::addEquilibriumSlashCommand(lua_State* L) {
	LuaObject slashcommand(L);
	if (!slashcommand.isValidTable())
		return 0;

	EquilibriumSlashCommand* slashCommand = new EquilibriumSlashCommand(slashcommand.getStringField("name"), server);
	parseSlashCommand(slashcommand, slashCommand);
	return 1;
}

int CommandConfigManager::addExecuteKnowledgeBaseMessageSlashCommand(lua_State* L) {
	LuaObject slashcommand(L);
	if (!slashcommand.isValidTable())
		return 0;

	ExecuteKnowledgeBaseMessageSlashCommand* slashCommand = new ExecuteKnowledgeBaseMessageSlashCommand(slashcommand.getStringField("name"), server);
	parseSlashCommand(slashcommand, slashCommand);
	return 1;
}

int CommandConfigManager::addExtinguishFireSlashCommand(lua_State* L) {
	LuaObject slashcommand(L);
	if (!slashcommand.isValidTable())
		return 0;

	ExtinguishFireSlashCommand* slashCommand = new ExtinguishFireSlashCommand(slashcommand.getStringField("name"), server);
	parseSlashCommand(slashcommand, slashCommand);
	return 1;
}

int CommandConfigManager::addExtractObjectSlashCommand(lua_State* L) {
	LuaObject slashcommand(L);
	if (!slashcommand.isValidTable())
		return 0;

	ExtractObjectSlashCommand* slashCommand = new ExtractObjectSlashCommand(slashcommand.getStringField("name"), server);
	parseSlashCommand(slashcommand, slashCommand);
	return 1;
}

int CommandConfigManager::addEyeShotSlashCommand(lua_State* L) {
	LuaObject slashcommand(L);
	if (!slashcommand.isValidTable())
		return 0;

	EyeShotSlashCommand* slashCommand = new EyeShotSlashCommand(slashcommand.getStringField("name"), server);
	parseSlashCommand(slashcommand, slashCommand);
	return 1;
}

int CommandConfigManager::addFactoryCrateSplitSlashCommand(lua_State* L) {
	LuaObject slashcommand(L);
	if (!slashcommand.isValidTable())
		return 0;

	FactoryCrateSplitSlashCommand* slashCommand = new FactoryCrateSplitSlashCommand(slashcommand.getStringField("name"), server);
	parseSlashCommand(slashcommand, slashCommand);
	return 1;
}

int CommandConfigManager::addFanShotSlashCommand(lua_State* L) {
	LuaObject slashcommand(L);
	if (!slashcommand.isValidTable())
		return 0;

	FanShotSlashCommand* slashCommand = new FanShotSlashCommand(slashcommand.getStringField("name"), server);
	parseSlashCommand(slashcommand, slashCommand);
	return 1;
}

int CommandConfigManager::addFeignDeathSlashCommand(lua_State* L) {
	LuaObject slashcommand(L);
	if (!slashcommand.isValidTable())
		return 0;

	FeignDeathSlashCommand* slashCommand = new FeignDeathSlashCommand(slashcommand.getStringField("name"), server);
	parseSlashCommand(slashcommand, slashCommand);
	return 1;
}

int CommandConfigManager::addFindSlashCommand(lua_State* L) {
	LuaObject slashcommand(L);
	if (!slashcommand.isValidTable())
		return 0;

	FindSlashCommand* slashCommand = new FindSlashCommand(slashcommand.getStringField("name"), server);
	parseSlashCommand(slashcommand, slashCommand);
	return 1;
}

int CommandConfigManager::addFindFriendSlashCommand(lua_State* L) {
	LuaObject slashcommand(L);
	if (!slashcommand.isValidTable())
		return 0;

	FindFriendSlashCommand* slashCommand = new FindFriendSlashCommand(slashcommand.getStringField("name"), server);
	parseSlashCommand(slashcommand, slashCommand);
	return 1;
}

int CommandConfigManager::addFindMyTrainerSlashCommand(lua_State* L) {
	LuaObject slashcommand(L);
	if (!slashcommand.isValidTable())
		return 0;

	FindMyTrainerSlashCommand* slashCommand = new FindMyTrainerSlashCommand(slashcommand.getStringField("name"), server);
	parseSlashCommand(slashcommand, slashCommand);
	return 1;
}

int CommandConfigManager::addFindObjectSlashCommand(lua_State* L) {
	LuaObject slashcommand(L);
	if (!slashcommand.isValidTable())
		return 0;

	FindObjectSlashCommand* slashCommand = new FindObjectSlashCommand(slashcommand.getStringField("name"), server);
	parseSlashCommand(slashcommand, slashCommand);
	return 1;
}

int CommandConfigManager::addFindPlayerSlashCommand(lua_State* L) {
	LuaObject slashcommand(L);
	if (!slashcommand.isValidTable())
		return 0;

	FindPlayerSlashCommand* slashCommand = new FindPlayerSlashCommand(slashcommand.getStringField("name"), server);
	parseSlashCommand(slashcommand, slashCommand);
	return 1;
}

int CommandConfigManager::addFirearmStrikeSlashCommand(lua_State* L) {
	LuaObject slashcommand(L);
	if (!slashcommand.isValidTable())
		return 0;

	FirearmStrikeSlashCommand* slashCommand = new FirearmStrikeSlashCommand(slashcommand.getStringField("name"), server);
	parseSlashCommand(slashcommand, slashCommand);
	return 1;
}

int CommandConfigManager::addFirejetSlashCommand(lua_State* L) {
	LuaObject slashcommand(L);
	if (!slashcommand.isValidTable())
		return 0;

	FirejetSlashCommand* slashCommand = new FirejetSlashCommand(slashcommand.getStringField("name"), server);
	parseSlashCommand(slashcommand, slashCommand);
	return 1;
}

int CommandConfigManager::addFishSlashCommand(lua_State* L) {
	LuaObject slashcommand(L);
	if (!slashcommand.isValidTable())
		return 0;

	FishSlashCommand* slashCommand = new FishSlashCommand(slashcommand.getStringField("name"), server);
	parseSlashCommand(slashcommand, slashCommand);
	return 1;
}

int CommandConfigManager::addFlashSpeederSlashCommand(lua_State* L) {
	LuaObject slashcommand(L);
	if (!slashcommand.isValidTable())
		return 0;

	FlashSpeederSlashCommand* slashCommand = new FlashSpeederSlashCommand(slashcommand.getStringField("name"), server);
	parseSlashCommand(slashcommand, slashCommand);
	return 1;
}

int CommandConfigManager::addFlourishSlashCommand(lua_State* L) {
	LuaObject slashcommand(L);
	if (!slashcommand.isValidTable())
		return 0;

	FlourishSlashCommand* slashCommand = new FlourishSlashCommand(slashcommand.getStringField("name"), server);
	parseSlashCommand(slashcommand, slashCommand);
	return 1;
}

int CommandConfigManager::addForageSlashCommand(lua_State* L) {
	LuaObject slashcommand(L);
	if (!slashcommand.isValidTable())
		return 0;

	ForageSlashCommand* slashCommand = new ForageSlashCommand(slashcommand.getStringField("name"), server);
	parseSlashCommand(slashcommand, slashCommand);
	return 1;
}

int CommandConfigManager::addForceAbsorbSlashCommand(lua_State* L) {
	LuaObject slashcommand(L);
	if (!slashcommand.isValidTable())
		return 0;

	ForceAbsorbSlashCommand* slashCommand = new ForceAbsorbSlashCommand(slashcommand.getStringField("name"), server);
	parseSlashCommand(slashcommand, slashCommand);
	return 1;
}

int CommandConfigManager::addForceArmorSlashCommand(lua_State* L) {
	LuaObject slashcommand(L);
	if (!slashcommand.isValidTable())
		return 0;

	ForceArmorSlashCommand* slashCommand = new ForceArmorSlashCommand(slashcommand.getStringField("name"), server);
	parseSlashCommand(slashcommand, slashCommand);
	return 1;
}

int CommandConfigManager::addForceAuraSlashCommand(lua_State* L) {
	LuaObject slashcommand(L);
	if (!slashcommand.isValidTable())
		return 0;

	ForceAuraSlashCommand* slashCommand = new ForceAuraSlashCommand(slashcommand.getStringField("name"), server);
	parseSlashCommand(slashcommand, slashCommand);
	return 1;
}

int CommandConfigManager::addForceBreachSlashCommand(lua_State* L) {
	LuaObject slashcommand(L);
	if (!slashcommand.isValidTable())
		return 0;

	ForceBreachSlashCommand* slashCommand = new ForceBreachSlashCommand(slashcommand.getStringField("name"), server);
	parseSlashCommand(slashcommand, slashCommand);
	return 1;
}

int CommandConfigManager::addForceChokeSlashCommand(lua_State* L) {
	LuaObject slashcommand(L);
	if (!slashcommand.isValidTable())
		return 0;

	ForceChokeSlashCommand* slashCommand = new ForceChokeSlashCommand(slashcommand.getStringField("name"), server);
	parseSlashCommand(slashcommand, slashCommand);
	return 1;
}

int CommandConfigManager::addForceCloakSlashCommand(lua_State* L) {
	LuaObject slashcommand(L);
	if (!slashcommand.isValidTable())
		return 0;

	ForceCloakSlashCommand* slashCommand = new ForceCloakSlashCommand(slashcommand.getStringField("name"), server);
	parseSlashCommand(slashcommand, slashCommand);
	return 1;
}

int CommandConfigManager::addForceCommandSlashCommand(lua_State* L) {
	LuaObject slashcommand(L);
	if (!slashcommand.isValidTable())
		return 0;

	ForceCommandSlashCommand* slashCommand = new ForceCommandSlashCommand(slashcommand.getStringField("name"), server);
	parseSlashCommand(slashcommand, slashCommand);
	return 1;
}

int CommandConfigManager::addForceCureDiseaseSlashCommand(lua_State* L) {
	LuaObject slashcommand(L);
	if (!slashcommand.isValidTable())
		return 0;

	ForceCureDiseaseSlashCommand* slashCommand = new ForceCureDiseaseSlashCommand(slashcommand.getStringField("name"), server);
	parseSlashCommand(slashcommand, slashCommand);
	return 1;
}

int CommandConfigManager::addForceCurePoisonSlashCommand(lua_State* L) {
	LuaObject slashcommand(L);
	if (!slashcommand.isValidTable())
		return 0;

	ForceCurePoisonSlashCommand* slashCommand = new ForceCurePoisonSlashCommand(slashcommand.getStringField("name"), server);
	parseSlashCommand(slashcommand, slashCommand);
	return 1;
}

int CommandConfigManager::addForceExtinguishSlashCommand(lua_State* L) {
	LuaObject slashcommand(L);
	if (!slashcommand.isValidTable())
		return 0;

	ForceExtinguishSlashCommand* slashCommand = new ForceExtinguishSlashCommand(slashcommand.getStringField("name"), server);
	parseSlashCommand(slashcommand, slashCommand);
	return 1;
}

int CommandConfigManager::addForceFeedbackSlashCommand(lua_State* L) {
	LuaObject slashcommand(L);
	if (!slashcommand.isValidTable())
		return 0;

	ForceFeedbackSlashCommand* slashCommand = new ForceFeedbackSlashCommand(slashcommand.getStringField("name"), server);
	parseSlashCommand(slashcommand, slashCommand);
	return 1;
}

int CommandConfigManager::addForceHealSlashCommand(lua_State* L) {
	LuaObject slashcommand(L);
	if (!slashcommand.isValidTable())
		return 0;

	ForceHealSlashCommand* slashCommand = new ForceHealSlashCommand(slashcommand.getStringField("name"), server);
	parseSlashCommand(slashcommand, slashCommand);
	return 1;
}

int CommandConfigManager::addForceHitSlashCommand(lua_State* L) {
	LuaObject slashcommand(L);
	if (!slashcommand.isValidTable())
		return 0;

	ForceHitSlashCommand* slashCommand = new ForceHitSlashCommand(slashcommand.getStringField("name"), server);
	parseSlashCommand(slashcommand, slashCommand);
	return 1;
}

int CommandConfigManager::addForceInfusionSlashCommand(lua_State* L) {
	LuaObject slashcommand(L);
	if (!slashcommand.isValidTable())
		return 0;

	ForceInfusionSlashCommand* slashCommand = new ForceInfusionSlashCommand(slashcommand.getStringField("name"), server);
	parseSlashCommand(slashcommand, slashCommand);
	return 1;
}

int CommandConfigManager::addForceIntimidateSlashCommand(lua_State* L) {
	LuaObject slashcommand(L);
	if (!slashcommand.isValidTable())
		return 0;

	ForceIntimidateSlashCommand* slashCommand = new ForceIntimidateSlashCommand(slashcommand.getStringField("name"), server);
	parseSlashCommand(slashcommand, slashCommand);
	return 1;
}

int CommandConfigManager::addForceKnockdownSlashCommand(lua_State* L) {
	LuaObject slashcommand(L);
	if (!slashcommand.isValidTable())
		return 0;

	ForceKnockdownSlashCommand* slashCommand = new ForceKnockdownSlashCommand(slashcommand.getStringField("name"), server);
	parseSlashCommand(slashcommand, slashCommand);
	return 1;
}

int CommandConfigManager::addForceLightningSlashCommand(lua_State* L) {
	LuaObject slashcommand(L);
	if (!slashcommand.isValidTable())
		return 0;

	ForceLightningSlashCommand* slashCommand = new ForceLightningSlashCommand(slashcommand.getStringField("name"), server);
	parseSlashCommand(slashcommand, slashCommand);
	return 1;
}

int CommandConfigManager::addForceLightningAreaSlashCommand(lua_State* L) {
	LuaObject slashcommand(L);
	if (!slashcommand.isValidTable())
		return 0;

	ForceLightningAreaSlashCommand* slashCommand = new ForceLightningAreaSlashCommand(slashcommand.getStringField("name"), server);
	parseSlashCommand(slashcommand, slashCommand);
	return 1;
}

int CommandConfigManager::addForceMeditateSlashCommand(lua_State* L) {
	LuaObject slashcommand(L);
	if (!slashcommand.isValidTable())
		return 0;

	ForceMeditateSlashCommand* slashCommand = new ForceMeditateSlashCommand(slashcommand.getStringField("name"), server);
	parseSlashCommand(slashcommand, slashCommand);
	return 1;
}

int CommandConfigManager::addForceOfWillSlashCommand(lua_State* L) {
	LuaObject slashcommand(L);
	if (!slashcommand.isValidTable())
		return 0;

	ForceOfWillSlashCommand* slashCommand = new ForceOfWillSlashCommand(slashcommand.getStringField("name"), server);
	parseSlashCommand(slashcommand, slashCommand);
	return 1;
}

int CommandConfigManager::addForceResistBleedingSlashCommand(lua_State* L) {
	LuaObject slashcommand(L);
	if (!slashcommand.isValidTable())
		return 0;

	ForceResistBleedingSlashCommand* slashCommand = new ForceResistBleedingSlashCommand(slashcommand.getStringField("name"), server);
	parseSlashCommand(slashcommand, slashCommand);
	return 1;
}

int CommandConfigManager::addForceResistDiseaseSlashCommand(lua_State* L) {
	LuaObject slashcommand(L);
	if (!slashcommand.isValidTable())
		return 0;

	ForceResistDiseaseSlashCommand* slashCommand = new ForceResistDiseaseSlashCommand(slashcommand.getStringField("name"), server);
	parseSlashCommand(slashcommand, slashCommand);
	return 1;
}

int CommandConfigManager::addForceResistPoisonSlashCommand(lua_State* L) {
	LuaObject slashcommand(L);
	if (!slashcommand.isValidTable())
		return 0;

	ForceResistPoisonSlashCommand* slashCommand = new ForceResistPoisonSlashCommand(slashcommand.getStringField("name"), server);
	parseSlashCommand(slashcommand, slashCommand);
	return 1;
}

int CommandConfigManager::addForceResistStatesSlashCommand(lua_State* L) {
	LuaObject slashcommand(L);
	if (!slashcommand.isValidTable())
		return 0;

	ForceResistStatesSlashCommand* slashCommand = new ForceResistStatesSlashCommand(slashcommand.getStringField("name"), server);
	parseSlashCommand(slashcommand, slashCommand);
	return 1;
}

int CommandConfigManager::addForceRunSlashCommand(lua_State* L) {
	LuaObject slashcommand(L);
	if (!slashcommand.isValidTable())
		return 0;

	ForceRunSlashCommand* slashCommand = new ForceRunSlashCommand(slashcommand.getStringField("name"), server);
	parseSlashCommand(slashcommand, slashCommand);
	return 1;
}

int CommandConfigManager::addForceSapSlashCommand(lua_State* L) {
	LuaObject slashcommand(L);
	if (!slashcommand.isValidTable())
		return 0;

	ForceSapSlashCommand* slashCommand = new ForceSapSlashCommand(slashcommand.getStringField("name"), server);
	parseSlashCommand(slashcommand, slashCommand);
	return 1;
}

int CommandConfigManager::addForceShieldSlashCommand(lua_State* L) {
	LuaObject slashcommand(L);
	if (!slashcommand.isValidTable())
		return 0;

	ForceShieldSlashCommand* slashCommand = new ForceShieldSlashCommand(slashcommand.getStringField("name"), server);
	parseSlashCommand(slashcommand, slashCommand);
	return 1;
}

int CommandConfigManager::addForceShockSlashCommand(lua_State* L) {
	LuaObject slashcommand(L);
	if (!slashcommand.isValidTable())
		return 0;

	ForceShockSlashCommand* slashCommand = new ForceShockSlashCommand(slashcommand.getStringField("name"), server);
	parseSlashCommand(slashcommand, slashCommand);
	return 1;
}

int CommandConfigManager::addForceSpeedSlashCommand(lua_State* L) {
	LuaObject slashcommand(L);
	if (!slashcommand.isValidTable())
		return 0;

	ForceSpeedSlashCommand* slashCommand = new ForceSpeedSlashCommand(slashcommand.getStringField("name"), server);
	parseSlashCommand(slashcommand, slashCommand);
	return 1;
}

int CommandConfigManager::addForceStrikeSlashCommand(lua_State* L) {
	LuaObject slashcommand(L);
	if (!slashcommand.isValidTable())
		return 0;

	ForceStrikeSlashCommand* slashCommand = new ForceStrikeSlashCommand(slashcommand.getStringField("name"), server);
	parseSlashCommand(slashcommand, slashCommand);
	return 1;
}

int CommandConfigManager::addForceSuppressionSlashCommand(lua_State* L) {
	LuaObject slashcommand(L);
	if (!slashcommand.isValidTable())
		return 0;

	ForceSuppressionSlashCommand* slashCommand = new ForceSuppressionSlashCommand(slashcommand.getStringField("name"), server);
	parseSlashCommand(slashcommand, slashCommand);
	return 1;
}

int CommandConfigManager::addForceThrowSlashCommand(lua_State* L) {
	LuaObject slashcommand(L);
	if (!slashcommand.isValidTable())
		return 0;

	ForceThrowSlashCommand* slashCommand = new ForceThrowSlashCommand(slashcommand.getStringField("name"), server);
	parseSlashCommand(slashcommand, slashCommand);
	return 1;
}

int CommandConfigManager::addForceValorSlashCommand(lua_State* L) {
	LuaObject slashcommand(L);
	if (!slashcommand.isValidTable())
		return 0;

	ForceValorSlashCommand* slashCommand = new ForceValorSlashCommand(slashcommand.getStringField("name"), server);
	parseSlashCommand(slashcommand, slashCommand);
	return 1;
}

int CommandConfigManager::addForceWaveSlashCommand(lua_State* L) {
	LuaObject slashcommand(L);
	if (!slashcommand.isValidTable())
		return 0;

	ForceWaveSlashCommand* slashCommand = new ForceWaveSlashCommand(slashcommand.getStringField("name"), server);
	parseSlashCommand(slashcommand, slashCommand);
	return 1;
}

int CommandConfigManager::addForceWeakenSlashCommand(lua_State* L) {
	LuaObject slashcommand(L);
	if (!slashcommand.isValidTable())
		return 0;

	ForceWeakenSlashCommand* slashCommand = new ForceWeakenSlashCommand(slashcommand.getStringField("name"), server);
	parseSlashCommand(slashcommand, slashCommand);
	return 1;
}

int CommandConfigManager::addForceWoundHealSlashCommand(lua_State* L) {
	LuaObject slashcommand(L);
	if (!slashcommand.isValidTable())
		return 0;

	ForceWoundHealSlashCommand* slashCommand = new ForceWoundHealSlashCommand(slashcommand.getStringField("name"), server);
	parseSlashCommand(slashcommand, slashCommand);
	return 1;
}

int CommandConfigManager::addFormupSlashCommand(lua_State* L) {
	LuaObject slashcommand(L);
	if (!slashcommand.isValidTable())
		return 0;

	FormupSlashCommand* slashCommand = new FormupSlashCommand(slashcommand.getStringField("name"), server);
	parseSlashCommand(slashcommand, slashCommand);
	return 1;
}

int CommandConfigManager::addFreezePlayerSlashCommand(lua_State* L) {
	LuaObject slashcommand(L);
	if (!slashcommand.isValidTable())
		return 0;

	FreezePlayerSlashCommand* slashCommand = new FreezePlayerSlashCommand(slashcommand.getStringField("name"), server);
	parseSlashCommand(slashcommand, slashCommand);
	return 1;
}

int CommandConfigManager::addFullAutoAreaSlashCommand(lua_State* L) {
	LuaObject slashcommand(L);
	if (!slashcommand.isValidTable())
		return 0;

	FullAutoAreaSlashCommand* slashCommand = new FullAutoAreaSlashCommand(slashcommand.getStringField("name"), server);
	parseSlashCommand(slashcommand, slashCommand);
	return 1;
}
/*
int CommandConfigManager::addGSlashCommand(lua_State* L) {
	LuaObject slashcommand(L);
	if (!slashcommand.isValidTable())
		return 0;

	GSlashCommand* slashCommand = new GSlashCommand(slashcommand.getStringField("name"), server);
	parseSlashCommand(slashcommand, slashCommand);
	return 1;
}
*/
int CommandConfigManager::addGallopSlashCommand(lua_State* L) {
	LuaObject slashcommand(L);
	if (!slashcommand.isValidTable())
		return 0;

	GallopSlashCommand* slashCommand = new GallopSlashCommand(slashcommand.getStringField("name"), server);
	parseSlashCommand(slashcommand, slashCommand);
	return 1;
}

int CommandConfigManager::addGallopStopSlashCommand(lua_State* L) {
	LuaObject slashcommand(L);
	if (!slashcommand.isValidTable())
		return 0;

	GallopStopSlashCommand* slashCommand = new GallopStopSlashCommand(slashcommand.getStringField("name"), server);
	parseSlashCommand(slashcommand, slashCommand);
	return 1;
}
/*
int CommandConfigManager::addGcSlashCommand(lua_State* L) {
	LuaObject slashcommand(L);
	if (!slashcommand.isValidTable())
		return 0;

	GcSlashCommand* slashCommand = new GcSlashCommand(slashcommand.getStringField("name"), server);
	parseSlashCommand(slashcommand, slashCommand);
	return 1;
}*/

int CommandConfigManager::addGcwStatusSlashCommand(lua_State* L) {
	LuaObject slashcommand(L);
	if (!slashcommand.isValidTable())
		return 0;

	GcwStatusSlashCommand* slashCommand = new GcwStatusSlashCommand(slashcommand.getStringField("name"), server);
	parseSlashCommand(slashcommand, slashCommand);
	return 1;
}

int CommandConfigManager::addGenerateCraftedItemSlashCommand(lua_State* L) {
	LuaObject slashcommand(L);
	if (!slashcommand.isValidTable())
		return 0;

	GenerateCraftedItemSlashCommand* slashCommand = new GenerateCraftedItemSlashCommand(slashcommand.getStringField("name"), server);
	parseSlashCommand(slashcommand, slashCommand);
	return 1;
}

int CommandConfigManager::addGetAccountInfoSlashCommand(lua_State* L) {
	LuaObject slashcommand(L);
	if (!slashcommand.isValidTable())
		return 0;

	GetAccountInfoSlashCommand* slashCommand = new GetAccountInfoSlashCommand(slashcommand.getStringField("name"), server);
	parseSlashCommand(slashcommand, slashCommand);
	return 1;
}

int CommandConfigManager::addGetAttributesSlashCommand(lua_State* L) {
	LuaObject slashcommand(L);
	if (!slashcommand.isValidTable())
		return 0;

	GetAttributesSlashCommand* slashCommand = new GetAttributesSlashCommand(slashcommand.getStringField("name"), server);
	parseSlashCommand(slashcommand, slashCommand);
	return 1;
}

int CommandConfigManager::addGetAttributesBatchSlashCommand(lua_State* L) {
	LuaObject slashcommand(L);
	if (!slashcommand.isValidTable())
		return 0;

	GetAttributesBatchSlashCommand* slashCommand = new GetAttributesBatchSlashCommand(slashcommand.getStringField("name"), server);
	parseSlashCommand(slashcommand, slashCommand);
	return 1;
}

int CommandConfigManager::addGetFriendListSlashCommand(lua_State* L) {
	LuaObject slashcommand(L);
	if (!slashcommand.isValidTable())
		return 0;

	GetFriendListSlashCommand* slashCommand = new GetFriendListSlashCommand(slashcommand.getStringField("name"), server);
	parseSlashCommand(slashcommand, slashCommand);
	return 1;
}

int CommandConfigManager::addGetGameTimeSlashCommand(lua_State* L) {
	LuaObject slashcommand(L);
	if (!slashcommand.isValidTable())
		return 0;

	GetGameTimeSlashCommand* slashCommand = new GetGameTimeSlashCommand(slashcommand.getStringField("name"), server);
	parseSlashCommand(slashcommand, slashCommand);
	return 1;
}

int CommandConfigManager::addGetIgnoreListSlashCommand(lua_State* L) {
	LuaObject slashcommand(L);
	if (!slashcommand.isValidTable())
		return 0;

	GetIgnoreListSlashCommand* slashCommand = new GetIgnoreListSlashCommand(slashcommand.getStringField("name"), server);
	parseSlashCommand(slashcommand, slashCommand);
	return 1;
}

int CommandConfigManager::addGetMapLocationsSlashCommand(lua_State* L) {
	LuaObject slashcommand(L);
	if (!slashcommand.isValidTable())
		return 0;

	GetMapLocationsSlashCommand* slashCommand = new GetMapLocationsSlashCommand(slashcommand.getStringField("name"), server);
	parseSlashCommand(slashcommand, slashCommand);
	return 1;
}

int CommandConfigManager::addGetObjVarsSlashCommand(lua_State* L) {
	LuaObject slashcommand(L);
	if (!slashcommand.isValidTable())
		return 0;

	GetObjVarsSlashCommand* slashCommand = new GetObjVarsSlashCommand(slashcommand.getStringField("name"), server);
	parseSlashCommand(slashcommand, slashCommand);
	return 1;
}

int CommandConfigManager::addGetPlayerIdSlashCommand(lua_State* L) {
	LuaObject slashcommand(L);
	if (!slashcommand.isValidTable())
		return 0;

	GetPlayerIdSlashCommand* slashCommand = new GetPlayerIdSlashCommand(slashcommand.getStringField("name"), server);
	parseSlashCommand(slashcommand, slashCommand);
	return 1;
}

int CommandConfigManager::addGetPrototypeSlashCommand(lua_State* L) {
	LuaObject slashcommand(L);
	if (!slashcommand.isValidTable())
		return 0;

	GetPrototypeSlashCommand* slashCommand = new GetPrototypeSlashCommand(slashcommand.getStringField("name"), server);
	parseSlashCommand(slashcommand, slashCommand);
	return 1;
}

int CommandConfigManager::addGetRankSlashCommand(lua_State* L) {
	LuaObject slashcommand(L);
	if (!slashcommand.isValidTable())
		return 0;

	GetRankSlashCommand* slashCommand = new GetRankSlashCommand(slashcommand.getStringField("name"), server);
	parseSlashCommand(slashcommand, slashCommand);
	return 1;
}

int CommandConfigManager::addGetSpawnDelaysSlashCommand(lua_State* L) {
	LuaObject slashcommand(L);
	if (!slashcommand.isValidTable())
		return 0;

	GetSpawnDelaysSlashCommand* slashCommand = new GetSpawnDelaysSlashCommand(slashcommand.getStringField("name"), server);
	parseSlashCommand(slashcommand, slashCommand);
	return 1;
}

int CommandConfigManager::addGetStationNameSlashCommand(lua_State* L) {
	LuaObject slashcommand(L);
	if (!slashcommand.isValidTable())
		return 0;

	GetStationNameSlashCommand* slashCommand = new GetStationNameSlashCommand(slashcommand.getStringField("name"), server);
	parseSlashCommand(slashcommand, slashCommand);
	return 1;
}

int CommandConfigManager::addGetVeteranRewardTimeSlashCommand(lua_State* L) {
	LuaObject slashcommand(L);
	if (!slashcommand.isValidTable())
		return 0;

	GetVeteranRewardTimeSlashCommand* slashCommand = new GetVeteranRewardTimeSlashCommand(slashcommand.getStringField("name"), server);
	parseSlashCommand(slashcommand, slashCommand);
	return 1;
}

int CommandConfigManager::addGetVeteranRewardTimeCsSlashCommand(lua_State* L) {
	LuaObject slashcommand(L);
	if (!slashcommand.isValidTable())
		return 0;

	GetVeteranRewardTimeCsSlashCommand* slashCommand = new GetVeteranRewardTimeCsSlashCommand(slashcommand.getStringField("name"), server);
	parseSlashCommand(slashcommand, slashCommand);
	return 1;
}

int CommandConfigManager::addGiveItemSlashCommand(lua_State* L) {
	LuaObject slashcommand(L);
	if (!slashcommand.isValidTable())
		return 0;

	GiveItemSlashCommand* slashCommand = new GiveItemSlashCommand(slashcommand.getStringField("name"), server);
	parseSlashCommand(slashcommand, slashCommand);
	return 1;
}

int CommandConfigManager::addGiveMaintenanceToVendorSlashCommand(lua_State* L) {
	LuaObject slashcommand(L);
	if (!slashcommand.isValidTable())
		return 0;

	GiveMaintenanceToVendorSlashCommand* slashCommand = new GiveMaintenanceToVendorSlashCommand(slashcommand.getStringField("name"), server);
	parseSlashCommand(slashcommand, slashCommand);
	return 1;
}

int CommandConfigManager::addGivevendormaintSlashCommand(lua_State* L) {
	LuaObject slashcommand(L);
	if (!slashcommand.isValidTable())
		return 0;

	GivevendormaintSlashCommand* slashCommand = new GivevendormaintSlashCommand(slashcommand.getStringField("name"), server);
	parseSlashCommand(slashcommand, slashCommand);
	return 1;
}

int CommandConfigManager::addGmCreateClassResourceSlashCommand(lua_State* L) {
	LuaObject slashcommand(L);
	if (!slashcommand.isValidTable())
		return 0;

	GmCreateClassResourceSlashCommand* slashCommand = new GmCreateClassResourceSlashCommand(slashcommand.getStringField("name"), server);
	parseSlashCommand(slashcommand, slashCommand);
	return 1;
}

int CommandConfigManager::addGmCreateSpecificResourceSlashCommand(lua_State* L) {
	LuaObject slashcommand(L);
	if (!slashcommand.isValidTable())
		return 0;

	GmCreateSpecificResourceSlashCommand* slashCommand = new GmCreateSpecificResourceSlashCommand(slashcommand.getStringField("name"), server);
	parseSlashCommand(slashcommand, slashCommand);
	return 1;
}

int CommandConfigManager::addGmForceCommandSlashCommand(lua_State* L) {
	LuaObject slashcommand(L);
	if (!slashcommand.isValidTable())
		return 0;

	GmForceCommandSlashCommand* slashCommand = new GmForceCommandSlashCommand(slashcommand.getStringField("name"), server);
	parseSlashCommand(slashcommand, slashCommand);
	return 1;
}

int CommandConfigManager::addGmForceRankSlashCommand(lua_State* L) {
	LuaObject slashcommand(L);
	if (!slashcommand.isValidTable())
		return 0;

	GmForceRankSlashCommand* slashCommand = new GmForceRankSlashCommand(slashcommand.getStringField("name"), server);
	parseSlashCommand(slashcommand, slashCommand);
	return 1;
}

int CommandConfigManager::addGmFsVillageSlashCommand(lua_State* L) {
	LuaObject slashcommand(L);
	if (!slashcommand.isValidTable())
		return 0;

	GmFsVillageSlashCommand* slashCommand = new GmFsVillageSlashCommand(slashcommand.getStringField("name"), server);
	parseSlashCommand(slashcommand, slashCommand);
	return 1;
}

int CommandConfigManager::addGmJediStateSlashCommand(lua_State* L) {
	LuaObject slashcommand(L);
	if (!slashcommand.isValidTable())
		return 0;

	GmJediStateSlashCommand* slashCommand = new GmJediStateSlashCommand(slashcommand.getStringField("name"), server);
	parseSlashCommand(slashcommand, slashCommand);
	return 1;
}

int CommandConfigManager::addGmReviveSlashCommand(lua_State* L) {
	LuaObject slashcommand(L);
	if (!slashcommand.isValidTable())
		return 0;

	GmReviveSlashCommand* slashCommand = new GmReviveSlashCommand(slashcommand.getStringField("name"), server);
	parseSlashCommand(slashcommand, slashCommand);
	return 1;
}

int CommandConfigManager::addGmWeaponSlashCommand(lua_State* L) {
	LuaObject slashcommand(L);
	if (!slashcommand.isValidTable())
		return 0;

	GmWeaponSlashCommand* slashCommand = new GmWeaponSlashCommand(slashcommand.getStringField("name"), server);
	parseSlashCommand(slashcommand, slashCommand);
	return 1;
}

int CommandConfigManager::addGotoSlashCommand(lua_State* L) {
	LuaObject slashcommand(L);
	if (!slashcommand.isValidTable())
		return 0;

	GotoSlashCommand* slashCommand = new GotoSlashCommand(slashcommand.getStringField("name"), server);
	parseSlashCommand(slashcommand, slashCommand);
	return 1;
}

int CommandConfigManager::addGrantBadgeSlashCommand(lua_State* L) {
	LuaObject slashcommand(L);
	if (!slashcommand.isValidTable())
		return 0;

	GrantBadgeSlashCommand* slashCommand = new GrantBadgeSlashCommand(slashcommand.getStringField("name"), server);
	parseSlashCommand(slashcommand, slashCommand);
	return 1;
}

int CommandConfigManager::addGrantPadawanTrialsEligibilitySlashCommand(lua_State* L) {
	LuaObject slashcommand(L);
	if (!slashcommand.isValidTable())
		return 0;

	GrantPadawanTrialsEligibilitySlashCommand* slashCommand = new GrantPadawanTrialsEligibilitySlashCommand(slashcommand.getStringField("name"), server);
	parseSlashCommand(slashcommand, slashCommand);
	return 1;
}

int CommandConfigManager::addGrantSkillSlashCommand(lua_State* L) {
	LuaObject slashcommand(L);
	if (!slashcommand.isValidTable())
		return 0;

	GrantSkillSlashCommand* slashCommand = new GrantSkillSlashCommand(slashcommand.getStringField("name"), server);
	parseSlashCommand(slashcommand, slashCommand);
	return 1;
}

int CommandConfigManager::addGrantTitleSlashCommand(lua_State* L) {
	LuaObject slashcommand(L);
	if (!slashcommand.isValidTable())
		return 0;

	GrantTitleSlashCommand* slashCommand = new GrantTitleSlashCommand(slashcommand.getStringField("name"), server);
	parseSlashCommand(slashcommand, slashCommand);
	return 1;
}

int CommandConfigManager::addGrantZoningRightsSlashCommand(lua_State* L) {
	LuaObject slashcommand(L);
	if (!slashcommand.isValidTable())
		return 0;

	GrantZoningRightsSlashCommand* slashCommand = new GrantZoningRightsSlashCommand(slashcommand.getStringField("name"), server);
	parseSlashCommand(slashcommand, slashCommand);
	return 1;
}

int CommandConfigManager::addGroupChatSlashCommand(lua_State* L) {
	LuaObject slashcommand(L);
	if (!slashcommand.isValidTable())
		return 0;

	GroupChatSlashCommand* slashCommand = new GroupChatSlashCommand(slashcommand.getStringField("name"), server);
	parseSlashCommand(slashcommand, slashCommand);
	return 1;
}

int CommandConfigManager::addGroupLootSlashCommand(lua_State* L) {
	LuaObject slashcommand(L);
	if (!slashcommand.isValidTable())
		return 0;

	GroupLootSlashCommand* slashCommand = new GroupLootSlashCommand(slashcommand.getStringField("name"), server);
	parseSlashCommand(slashcommand, slashCommand);
	return 1;
}
/*
int CommandConfigManager::addGroupSaySlashCommand(lua_State* L) {
	LuaObject slashcommand(L);
	if (!slashcommand.isValidTable())
		return 0;

	GroupSaySlashCommand* slashCommand = new GroupSaySlashCommand(slashcommand.getStringField("name"), server);
	parseSlashCommand(slashcommand, slashCommand);
	return 1;
}

int CommandConfigManager::addGsaySlashCommand(lua_State* L) {
	LuaObject slashcommand(L);
	if (!slashcommand.isValidTable())
		return 0;

	GsaySlashCommand* slashCommand = new GsaySlashCommand(slashcommand.getStringField("name"), server);
	parseSlashCommand(slashcommand, slashCommand);
	return 1;
}

int CommandConfigManager::addGtellSlashCommand(lua_State* L) {
	LuaObject slashcommand(L);
	if (!slashcommand.isValidTable())
		return 0;

	GtellSlashCommand* slashCommand = new GtellSlashCommand(slashcommand.getStringField("name"), server);
	parseSlashCommand(slashcommand, slashCommand);
	return 1;
}

int CommandConfigManager::addGuildSlashCommand(lua_State* L) {
	LuaObject slashcommand(L);
	if (!slashcommand.isValidTable())
		return 0;

	GuildSlashCommand* slashCommand = new GuildSlashCommand(slashcommand.getStringField("name"), server);
	parseSlashCommand(slashcommand, slashCommand);
	return 1;
}
*/
int CommandConfigManager::addGuildRemoveSlashCommand(lua_State* L) {
	LuaObject slashcommand(L);
	if (!slashcommand.isValidTable())
		return 0;

	GuildRemoveSlashCommand* slashCommand = new GuildRemoveSlashCommand(slashcommand.getStringField("name"), server);
	parseSlashCommand(slashcommand, slashCommand);
	return 1;
}

int CommandConfigManager::addGuildsaySlashCommand(lua_State* L) {
	LuaObject slashcommand(L);
	if (!slashcommand.isValidTable())
		return 0;

	GuildsaySlashCommand* slashCommand = new GuildsaySlashCommand(slashcommand.getStringField("name"), server);
	parseSlashCommand(slashcommand, slashCommand);
	return 1;
}

int CommandConfigManager::addGuildstatusSlashCommand(lua_State* L) {
	LuaObject slashcommand(L);
	if (!slashcommand.isValidTable())
		return 0;

	GuildstatusSlashCommand* slashCommand = new GuildstatusSlashCommand(slashcommand.getStringField("name"), server);
	parseSlashCommand(slashcommand, slashCommand);
	return 1;
}

int CommandConfigManager::addHandleClientLoginSlashCommand(lua_State* L) {
	LuaObject slashcommand(L);
	if (!slashcommand.isValidTable())
		return 0;

	HandleClientLoginSlashCommand* slashCommand = new HandleClientLoginSlashCommand(slashcommand.getStringField("name"), server);
	parseSlashCommand(slashcommand, slashCommand);
	return 1;
}

int CommandConfigManager::addHarmfulSlashCommand(lua_State* L) {
	LuaObject slashcommand(L);
	if (!slashcommand.isValidTable())
		return 0;

	HarmfulSlashCommand* slashCommand = new HarmfulSlashCommand(slashcommand.getStringField("name"), server);
	parseSlashCommand(slashcommand, slashCommand);
	return 1;
}

int CommandConfigManager::addHarmlessSlashCommand(lua_State* L) {
	LuaObject slashcommand(L);
	if (!slashcommand.isValidTable())
		return 0;

	HarmlessSlashCommand* slashCommand = new HarmlessSlashCommand(slashcommand.getStringField("name"), server);
	parseSlashCommand(slashcommand, slashCommand);
	return 1;
}

int CommandConfigManager::addHarvestCorpseSlashCommand(lua_State* L) {
	LuaObject slashcommand(L);
	if (!slashcommand.isValidTable())
		return 0;

	HarvestCorpseSlashCommand* slashCommand = new HarvestCorpseSlashCommand(slashcommand.getStringField("name"), server);
	parseSlashCommand(slashcommand, slashCommand);
	return 1;
}

int CommandConfigManager::addHarvesterActivateSlashCommand(lua_State* L) {
	LuaObject slashcommand(L);
	if (!slashcommand.isValidTable())
		return 0;

	HarvesterActivateSlashCommand* slashCommand = new HarvesterActivateSlashCommand(slashcommand.getStringField("name"), server);
	parseSlashCommand(slashcommand, slashCommand);
	return 1;
}

int CommandConfigManager::addHarvesterDeactivateSlashCommand(lua_State* L) {
	LuaObject slashcommand(L);
	if (!slashcommand.isValidTable())
		return 0;

	HarvesterDeactivateSlashCommand* slashCommand = new HarvesterDeactivateSlashCommand(slashcommand.getStringField("name"), server);
	parseSlashCommand(slashcommand, slashCommand);
	return 1;
}

int CommandConfigManager::addHarvesterDiscardHopperSlashCommand(lua_State* L) {
	LuaObject slashcommand(L);
	if (!slashcommand.isValidTable())
		return 0;

	HarvesterDiscardHopperSlashCommand* slashCommand = new HarvesterDiscardHopperSlashCommand(slashcommand.getStringField("name"), server);
	parseSlashCommand(slashcommand, slashCommand);
	return 1;
}

int CommandConfigManager::addHarvesterGetResourceDataSlashCommand(lua_State* L) {
	LuaObject slashcommand(L);
	if (!slashcommand.isValidTable())
		return 0;

	HarvesterGetResourceDataSlashCommand* slashCommand = new HarvesterGetResourceDataSlashCommand(slashcommand.getStringField("name"), server);
	parseSlashCommand(slashcommand, slashCommand);
	return 1;
}

int CommandConfigManager::addHarvesterHarvestSlashCommand(lua_State* L) {
	LuaObject slashcommand(L);
	if (!slashcommand.isValidTable())
		return 0;

	HarvesterHarvestSlashCommand* slashCommand = new HarvesterHarvestSlashCommand(slashcommand.getStringField("name"), server);
	parseSlashCommand(slashcommand, slashCommand);
	return 1;
}

int CommandConfigManager::addHarvesterMakeCrateSlashCommand(lua_State* L) {
	LuaObject slashcommand(L);
	if (!slashcommand.isValidTable())
		return 0;

	HarvesterMakeCrateSlashCommand* slashCommand = new HarvesterMakeCrateSlashCommand(slashcommand.getStringField("name"), server);
	parseSlashCommand(slashcommand, slashCommand);
	return 1;
}

int CommandConfigManager::addHarvesterSelectResourceSlashCommand(lua_State* L) {
	LuaObject slashcommand(L);
	if (!slashcommand.isValidTable())
		return 0;

	HarvesterSelectResourceSlashCommand* slashCommand = new HarvesterSelectResourceSlashCommand(slashcommand.getStringField("name"), server);
	parseSlashCommand(slashcommand, slashCommand);
	return 1;
}

int CommandConfigManager::addHarvesterTakeSurveySlashCommand(lua_State* L) {
	LuaObject slashcommand(L);
	if (!slashcommand.isValidTable())
		return 0;

	HarvesterTakeSurveySlashCommand* slashCommand = new HarvesterTakeSurveySlashCommand(slashcommand.getStringField("name"), server);
	parseSlashCommand(slashcommand, slashCommand);
	return 1;
}

int CommandConfigManager::addHasVeteranRewardSlashCommand(lua_State* L) {
	LuaObject slashcommand(L);
	if (!slashcommand.isValidTable())
		return 0;

	HasVeteranRewardSlashCommand* slashCommand = new HasVeteranRewardSlashCommand(slashcommand.getStringField("name"), server);
	parseSlashCommand(slashcommand, slashCommand);
	return 1;
}

int CommandConfigManager::addHaveconsentSlashCommand(lua_State* L) {
	LuaObject slashcommand(L);
	if (!slashcommand.isValidTable())
		return 0;

	HaveconsentSlashCommand* slashCommand = new HaveconsentSlashCommand(slashcommand.getStringField("name"), server);
	parseSlashCommand(slashcommand, slashCommand);
	return 1;
}

int CommandConfigManager::addHeadHitSlashCommand(lua_State* L) {
	LuaObject slashcommand(L);
	if (!slashcommand.isValidTable())
		return 0;

	HeadHitSlashCommand* slashCommand = new HeadHitSlashCommand(slashcommand.getStringField("name"), server);
	parseSlashCommand(slashcommand, slashCommand);
	return 1;
}

int CommandConfigManager::addHeadShotSlashCommand(lua_State* L) {
	LuaObject slashcommand(L);
	if (!slashcommand.isValidTable())
		return 0;

	HeadShotSlashCommand* slashCommand = new HeadShotSlashCommand(slashcommand.getStringField("name"), server);
	parseSlashCommand(slashcommand, slashCommand);
	return 1;
}

int CommandConfigManager::addHealDroidDamageSlashCommand(lua_State* L) {
	LuaObject slashcommand(L);
	if (!slashcommand.isValidTable())
		return 0;

	HealDroidDamageSlashCommand* slashCommand = new HealDroidDamageSlashCommand(slashcommand.getStringField("name"), server);
	parseSlashCommand(slashcommand, slashCommand);
	return 1;
}

int CommandConfigManager::addHealDroidWoundSlashCommand(lua_State* L) {
	LuaObject slashcommand(L);
	if (!slashcommand.isValidTable())
		return 0;

	HealDroidWoundSlashCommand* slashCommand = new HealDroidWoundSlashCommand(slashcommand.getStringField("name"), server);
	parseSlashCommand(slashcommand, slashCommand);
	return 1;
}

int CommandConfigManager::addHealPetSlashCommand(lua_State* L) {
	LuaObject slashcommand(L);
	if (!slashcommand.isValidTable())
		return 0;

	HealPetSlashCommand* slashCommand = new HealPetSlashCommand(slashcommand.getStringField("name"), server);
	parseSlashCommand(slashcommand, slashCommand);
	return 1;
}

int CommandConfigManager::addHealStatesSlashCommand(lua_State* L) {
	LuaObject slashcommand(L);
	if (!slashcommand.isValidTable())
		return 0;

	HealStatesSlashCommand* slashCommand = new HealStatesSlashCommand(slashcommand.getStringField("name"), server);
	parseSlashCommand(slashcommand, slashCommand);
	return 1;
}

int CommandConfigManager::addHealWoundSlashCommand(lua_State* L) {
	LuaObject slashcommand(L);
	if (!slashcommand.isValidTable())
		return 0;

	HealWoundSlashCommand* slashCommand = new HealWoundSlashCommand(slashcommand.getStringField("name"), server);
	parseSlashCommand(slashcommand, slashCommand);
	return 1;
}

int CommandConfigManager::addHemorrhageSlashCommand(lua_State* L) {
	LuaObject slashcommand(L);
	if (!slashcommand.isValidTable())
		return 0;

	HemorrhageSlashCommand* slashCommand = new HemorrhageSlashCommand(slashcommand.getStringField("name"), server);
	parseSlashCommand(slashcommand, slashCommand);
	return 1;
}

int CommandConfigManager::addHoloEmoteSlashCommand(lua_State* L) {
	LuaObject slashcommand(L);
	if (!slashcommand.isValidTable())
		return 0;

	HoloEmoteSlashCommand* slashCommand = new HoloEmoteSlashCommand(slashcommand.getStringField("name"), server);
	parseSlashCommand(slashcommand, slashCommand);
	return 1;
}

int CommandConfigManager::addImagedesignSlashCommand(lua_State* L) {
	LuaObject slashcommand(L);
	if (!slashcommand.isValidTable())
		return 0;

	ImagedesignSlashCommand* slashCommand = new ImagedesignSlashCommand(slashcommand.getStringField("name"), server);
	parseSlashCommand(slashcommand, slashCommand);
	return 1;
}

int CommandConfigManager::addImpaleSlashCommand(lua_State* L) {
	LuaObject slashcommand(L);
	if (!slashcommand.isValidTable())
		return 0;

	ImpaleSlashCommand* slashCommand = new ImpaleSlashCommand(slashcommand.getStringField("name"), server);
	parseSlashCommand(slashcommand, slashCommand);
	return 1;
}

int CommandConfigManager::addInfectSlashCommand(lua_State* L) {
	LuaObject slashcommand(L);
	if (!slashcommand.isValidTable())
		return 0;

	InfectSlashCommand* slashCommand = new InfectSlashCommand(slashcommand.getStringField("name"), server);
	parseSlashCommand(slashcommand, slashCommand);
	return 1;
}

int CommandConfigManager::addInitializeComponentSlashCommand(lua_State* L) {
	LuaObject slashcommand(L);
	if (!slashcommand.isValidTable())
		return 0;

	InitializeComponentSlashCommand* slashCommand = new InitializeComponentSlashCommand(slashcommand.getStringField("name"), server);
	parseSlashCommand(slashcommand, slashCommand);
	return 1;
}

int CommandConfigManager::addInnateSlashCommand(lua_State* L) {
	LuaObject slashcommand(L);
	if (!slashcommand.isValidTable())
		return 0;

	InnateSlashCommand* slashCommand = new InnateSlashCommand(slashcommand.getStringField("name"), server);
	parseSlashCommand(slashcommand, slashCommand);
	return 1;
}

int CommandConfigManager::addInsertItemIntoShipComponentSlotSlashCommand(lua_State* L) {
	LuaObject slashcommand(L);
	if (!slashcommand.isValidTable())
		return 0;

	InsertItemIntoShipComponentSlotSlashCommand* slashCommand = new InsertItemIntoShipComponentSlotSlashCommand(slashcommand.getStringField("name"), server);
	parseSlashCommand(slashcommand, slashCommand);
	return 1;
}

int CommandConfigManager::addInstallMissionTerminalSlashCommand(lua_State* L) {
	LuaObject slashcommand(L);
	if (!slashcommand.isValidTable())
		return 0;

	InstallMissionTerminalSlashCommand* slashCommand = new InstallMissionTerminalSlashCommand(slashcommand.getStringField("name"), server);
	parseSlashCommand(slashcommand, slashCommand);
	return 1;
}

int CommandConfigManager::addInstallShipComponentSlashCommand(lua_State* L) {
	LuaObject slashcommand(L);
	if (!slashcommand.isValidTable())
		return 0;

	InstallShipComponentSlashCommand* slashCommand = new InstallShipComponentSlashCommand(slashcommand.getStringField("name"), server);
	parseSlashCommand(slashcommand, slashCommand);
	return 1;
}

int CommandConfigManager::addInsureSlashCommand(lua_State* L) {
	LuaObject slashcommand(L);
	if (!slashcommand.isValidTable())
		return 0;

	InsureSlashCommand* slashCommand = new InsureSlashCommand(slashcommand.getStringField("name"), server);
	parseSlashCommand(slashcommand, slashCommand);
	return 1;
}

int CommandConfigManager::addIntimidateSlashCommand(lua_State* L) {
	LuaObject slashcommand(L);
	if (!slashcommand.isValidTable())
		return 0;

	IntimidateSlashCommand* slashCommand = new IntimidateSlashCommand(slashcommand.getStringField("name"), server);
	parseSlashCommand(slashcommand, slashCommand);
	return 1;
}

int CommandConfigManager::addIntimidateShotSlashCommand(lua_State* L) {
	LuaObject slashcommand(L);
	if (!slashcommand.isValidTable())
		return 0;

	IntimidateShotSlashCommand* slashCommand = new IntimidateShotSlashCommand(slashcommand.getStringField("name"), server);
	parseSlashCommand(slashcommand, slashCommand);
	return 1;
}

int CommandConfigManager::addInviteSlashCommand(lua_State* L) {
	LuaObject slashcommand(L);
	if (!slashcommand.isValidTable())
		return 0;

	InviteSlashCommand* slashCommand = new InviteSlashCommand(slashcommand.getStringField("name"), server);
	parseSlashCommand(slashcommand, slashCommand);
	return 1;
}

int CommandConfigManager::addInvulnerableSlashCommand(lua_State* L) {
	LuaObject slashcommand(L);
	if (!slashcommand.isValidTable())
		return 0;

	InvulnerableSlashCommand* slashCommand = new InvulnerableSlashCommand(slashcommand.getStringField("name"), server);
	parseSlashCommand(slashcommand, slashCommand);
	return 1;
}

int CommandConfigManager::addItemmovebackSlashCommand(lua_State* L) {
	LuaObject slashcommand(L);
	if (!slashcommand.isValidTable())
		return 0;

	ItemmovebackSlashCommand* slashCommand = new ItemmovebackSlashCommand(slashcommand.getStringField("name"), server);
	parseSlashCommand(slashcommand, slashCommand);
	return 1;
}

int CommandConfigManager::addItemmovedownSlashCommand(lua_State* L) {
	LuaObject slashcommand(L);
	if (!slashcommand.isValidTable())
		return 0;

	ItemmovedownSlashCommand* slashCommand = new ItemmovedownSlashCommand(slashcommand.getStringField("name"), server);
	parseSlashCommand(slashcommand, slashCommand);
	return 1;
}

int CommandConfigManager::addItemmoveforwardSlashCommand(lua_State* L) {
	LuaObject slashcommand(L);
	if (!slashcommand.isValidTable())
		return 0;

	ItemmoveforwardSlashCommand* slashCommand = new ItemmoveforwardSlashCommand(slashcommand.getStringField("name"), server);
	parseSlashCommand(slashcommand, slashCommand);
	return 1;
}

int CommandConfigManager::addItemmoveupSlashCommand(lua_State* L) {
	LuaObject slashcommand(L);
	if (!slashcommand.isValidTable())
		return 0;

	ItemmoveupSlashCommand* slashCommand = new ItemmoveupSlashCommand(slashcommand.getStringField("name"), server);
	parseSlashCommand(slashcommand, slashCommand);
	return 1;
}

int CommandConfigManager::addItemrotateleftSlashCommand(lua_State* L) {
	LuaObject slashcommand(L);
	if (!slashcommand.isValidTable())
		return 0;

	ItemrotateleftSlashCommand* slashCommand = new ItemrotateleftSlashCommand(slashcommand.getStringField("name"), server);
	parseSlashCommand(slashcommand, slashCommand);
	return 1;
}

int CommandConfigManager::addItemrotaterightSlashCommand(lua_State* L) {
	LuaObject slashcommand(L);
	if (!slashcommand.isValidTable())
		return 0;

	ItemrotaterightSlashCommand* slashCommand = new ItemrotaterightSlashCommand(slashcommand.getStringField("name"), server);
	parseSlashCommand(slashcommand, slashCommand);
	return 1;
}

int CommandConfigManager::addJoinSlashCommand(lua_State* L) {
	LuaObject slashcommand(L);
	if (!slashcommand.isValidTable())
		return 0;

	JoinSlashCommand* slashCommand = new JoinSlashCommand(slashcommand.getStringField("name"), server);
	parseSlashCommand(slashcommand, slashCommand);
	return 1;
}

int CommandConfigManager::addJoinGameSlashCommand(lua_State* L) {
	LuaObject slashcommand(L);
	if (!slashcommand.isValidTable())
		return 0;

	JoinGameSlashCommand* slashCommand = new JoinGameSlashCommand(slashcommand.getStringField("name"), server);
	parseSlashCommand(slashcommand, slashCommand);
	return 1;
}

int CommandConfigManager::addKickSlashCommand(lua_State* L) {
	LuaObject slashcommand(L);
	if (!slashcommand.isValidTable())
		return 0;

	KickSlashCommand* slashCommand = new KickSlashCommand(slashcommand.getStringField("name"), server);
	parseSlashCommand(slashcommand, slashCommand);
	return 1;
}

int CommandConfigManager::addKillSlashCommand(lua_State* L) {
	LuaObject slashcommand(L);
	if (!slashcommand.isValidTable())
		return 0;

	KillSlashCommand* slashCommand = new KillSlashCommand(slashcommand.getStringField("name"), server);
	parseSlashCommand(slashcommand, slashCommand);
	return 1;
}

int CommandConfigManager::addKillPlayerSlashCommand(lua_State* L) {
	LuaObject slashcommand(L);
	if (!slashcommand.isValidTable())
		return 0;

	KillPlayerSlashCommand* slashCommand = new KillPlayerSlashCommand(slashcommand.getStringField("name"), server);
	parseSlashCommand(slashcommand, slashCommand);
	return 1;
}

int CommandConfigManager::addKipUpShotSlashCommand(lua_State* L) {
	LuaObject slashcommand(L);
	if (!slashcommand.isValidTable())
		return 0;

	KipUpShotSlashCommand* slashCommand = new KipUpShotSlashCommand(slashcommand.getStringField("name"), server);
	parseSlashCommand(slashcommand, slashCommand);
	return 1;
}

int CommandConfigManager::addKneecapShotSlashCommand(lua_State* L) {
	LuaObject slashcommand(L);
	if (!slashcommand.isValidTable())
		return 0;

	KneecapShotSlashCommand* slashCommand = new KneecapShotSlashCommand(slashcommand.getStringField("name"), server);
	parseSlashCommand(slashcommand, slashCommand);
	return 1;
}

int CommandConfigManager::addKneelSlashCommand(lua_State* L) {
	LuaObject slashcommand(L);
	if (!slashcommand.isValidTable())
		return 0;

	KneelSlashCommand* slashCommand = new KneelSlashCommand(slashcommand.getStringField("name"), server);
	parseSlashCommand(slashcommand, slashCommand);
	return 1;
}

int CommandConfigManager::addKnockdownRecoverySlashCommand(lua_State* L) {
	LuaObject slashcommand(L);
	if (!slashcommand.isValidTable())
		return 0;

	KnockdownRecoverySlashCommand* slashCommand = new KnockdownRecoverySlashCommand(slashcommand.getStringField("name"), server);
	parseSlashCommand(slashcommand, slashCommand);
	return 1;
}

int CommandConfigManager::addLagSlashCommand(lua_State* L) {
	LuaObject slashcommand(L);
	if (!slashcommand.isValidTable())
		return 0;

	LagSlashCommand* slashCommand = new LagSlashCommand(slashcommand.getStringField("name"), server);
	parseSlashCommand(slashcommand, slashCommand);
	return 1;
}

int CommandConfigManager::addLastDitchSlashCommand(lua_State* L) {
	LuaObject slashcommand(L);
	if (!slashcommand.isValidTable())
		return 0;

	LastDitchSlashCommand* slashCommand = new LastDitchSlashCommand(slashcommand.getStringField("name"), server);
	parseSlashCommand(slashcommand, slashCommand);
	return 1;
}

int CommandConfigManager::addLaunchFireworkSlashCommand(lua_State* L) {
	LuaObject slashcommand(L);
	if (!slashcommand.isValidTable())
		return 0;

	LaunchFireworkSlashCommand* slashCommand = new LaunchFireworkSlashCommand(slashcommand.getStringField("name"), server);
	parseSlashCommand(slashcommand, slashCommand);
	return 1;
}

int CommandConfigManager::addLeaveGameSlashCommand(lua_State* L) {
	LuaObject slashcommand(L);
	if (!slashcommand.isValidTable())
		return 0;

	LeaveGameSlashCommand* slashCommand = new LeaveGameSlashCommand(slashcommand.getStringField("name"), server);
	parseSlashCommand(slashcommand, slashCommand);
	return 1;
}

int CommandConfigManager::addLeaveGroupSlashCommand(lua_State* L) {
	LuaObject slashcommand(L);
	if (!slashcommand.isValidTable())
		return 0;

	LeaveGroupSlashCommand* slashCommand = new LeaveGroupSlashCommand(slashcommand.getStringField("name"), server);
	parseSlashCommand(slashcommand, slashCommand);
	return 1;
}

int CommandConfigManager::addLegHitSlashCommand(lua_State* L) {
	LuaObject slashcommand(L);
	if (!slashcommand.isValidTable())
		return 0;

	LegHitSlashCommand* slashCommand = new LegHitSlashCommand(slashcommand.getStringField("name"), server);
	parseSlashCommand(slashcommand, slashCommand);
	return 1;
}

int CommandConfigManager::addLegShotSlashCommand(lua_State* L) {
	LuaObject slashcommand(L);
	if (!slashcommand.isValidTable())
		return 0;

	LegShotSlashCommand* slashCommand = new LegShotSlashCommand(slashcommand.getStringField("name"), server);
	parseSlashCommand(slashcommand, slashCommand);
	return 1;
}

int CommandConfigManager::addLegSweepSlashCommand(lua_State* L) {
	LuaObject slashcommand(L);
	if (!slashcommand.isValidTable())
		return 0;

	LegSweepSlashCommand* slashCommand = new LegSweepSlashCommand(slashcommand.getStringField("name"), server);
	parseSlashCommand(slashcommand, slashCommand);
	return 1;
}

int CommandConfigManager::addLethalShotSlashCommand(lua_State* L) {
	LuaObject slashcommand(L);
	if (!slashcommand.isValidTable())
		return 0;

	LethalShotSlashCommand* slashCommand = new LethalShotSlashCommand(slashcommand.getStringField("name"), server);
	parseSlashCommand(slashcommand, slashCommand);
	return 1;
}

int CommandConfigManager::addLfgSlashCommand(lua_State* L) {
	LuaObject slashcommand(L);
	if (!slashcommand.isValidTable())
		return 0;

	LfgSlashCommand* slashCommand = new LfgSlashCommand(slashcommand.getStringField("name"), server);
	parseSlashCommand(slashcommand, slashCommand);
	return 1;
}

int CommandConfigManager::addListActiveQuestsSlashCommand(lua_State* L) {
	LuaObject slashcommand(L);
	if (!slashcommand.isValidTable())
		return 0;

	ListActiveQuestsSlashCommand* slashCommand = new ListActiveQuestsSlashCommand(slashcommand.getStringField("name"), server);
	parseSlashCommand(slashcommand, slashCommand);
	return 1;
}

int CommandConfigManager::addListCompletedQuestsSlashCommand(lua_State* L) {
	LuaObject slashcommand(L);
	if (!slashcommand.isValidTable())
		return 0;

	ListCompletedQuestsSlashCommand* slashCommand = new ListCompletedQuestsSlashCommand(slashcommand.getStringField("name"), server);
	parseSlashCommand(slashcommand, slashCommand);
	return 1;
}

int CommandConfigManager::addListenSlashCommand(lua_State* L) {
	LuaObject slashcommand(L);
	if (!slashcommand.isValidTable())
		return 0;

	ListenSlashCommand* slashCommand = new ListenSlashCommand(slashcommand.getStringField("name"), server);
	parseSlashCommand(slashcommand, slashCommand);
	return 1;
}

int CommandConfigManager::addListGuildsSlashCommand(lua_State* L) {
	LuaObject slashcommand(L);
	if (!slashcommand.isValidTable())
		return 0;

	ListGuildsSlashCommand* slashCommand = new ListGuildsSlashCommand(slashcommand.getStringField("name"), server);
	parseSlashCommand(slashcommand, slashCommand);
	return 1;
}

int CommandConfigManager::addLogoutServerSlashCommand(lua_State* L) {
	LuaObject slashcommand(L);
	if (!slashcommand.isValidTable())
		return 0;

	LogoutServerSlashCommand* slashCommand = new LogoutServerSlashCommand(slashcommand.getStringField("name"), server);
	parseSlashCommand(slashcommand, slashCommand);
	return 1;
}

int CommandConfigManager::addLootAllSlashCommand(lua_State* L) {
	LuaObject slashcommand(L);
	if (!slashcommand.isValidTable())
		return 0;

	LootAllSlashCommand* slashCommand = new LootAllSlashCommand(slashcommand.getStringField("name"), server);
	parseSlashCommand(slashcommand, slashCommand);
	return 1;
}

int CommandConfigManager::addLootSlashCommand(lua_State* L) {
	LuaObject slashcommand(L);
	if (!slashcommand.isValidTable())
		return 0;

	LootSlashCommand* slashCommand = new LootSlashCommand(slashcommand.getStringField("name"), server);
	parseSlashCommand(slashcommand, slashCommand);
	return 1;
}

int CommandConfigManager::addLootPlayerCorpseSlashCommand(lua_State* L) {
	LuaObject slashcommand(L);
	if (!slashcommand.isValidTable())
		return 0;

	LootPlayerCorpseSlashCommand* slashCommand = new LootPlayerCorpseSlashCommand(slashcommand.getStringField("name"), server);
	parseSlashCommand(slashcommand, slashCommand);
	return 1;
}

int CommandConfigManager::addLowBlowSlashCommand(lua_State* L) {
	LuaObject slashcommand(L);
	if (!slashcommand.isValidTable())
		return 0;

	LowBlowSlashCommand* slashCommand = new LowBlowSlashCommand(slashcommand.getStringField("name"), server);
	parseSlashCommand(slashcommand, slashCommand);
	return 1;
}

int CommandConfigManager::addLungeSlashCommand(lua_State* L) {
	LuaObject slashcommand(L);
	if (!slashcommand.isValidTable())
		return 0;

	LungeSlashCommand* slashCommand = new LungeSlashCommand(slashcommand.getStringField("name"), server);
	parseSlashCommand(slashcommand, slashCommand);
	return 1;
}

int CommandConfigManager::addMakeLeaderSlashCommand(lua_State* L) {
	LuaObject slashcommand(L);
	if (!slashcommand.isValidTable())
		return 0;

	MakeLeaderSlashCommand* slashCommand = new MakeLeaderSlashCommand(slashcommand.getStringField("name"), server);
	parseSlashCommand(slashcommand, slashCommand);
	return 1;
}

int CommandConfigManager::addMakeMasterLooterSlashCommand(lua_State* L) {
	LuaObject slashcommand(L);
	if (!slashcommand.isValidTable())
		return 0;

	MakeMasterLooterSlashCommand* slashCommand = new MakeMasterLooterSlashCommand(slashcommand.getStringField("name"), server);
	parseSlashCommand(slashcommand, slashCommand);
	return 1;
}

int CommandConfigManager::addMakeSurveySlashCommand(lua_State* L) {
	LuaObject slashcommand(L);
	if (!slashcommand.isValidTable())
		return 0;

	MakeSurveySlashCommand* slashCommand = new MakeSurveySlashCommand(slashcommand.getStringField("name"), server);
	parseSlashCommand(slashcommand, slashCommand);
	return 1;
}

int CommandConfigManager::addManufactureSlashCommand(lua_State* L) {
	LuaObject slashcommand(L);
	if (!slashcommand.isValidTable())
		return 0;

	ManufactureSlashCommand* slashCommand = new ManufactureSlashCommand(slashcommand.getStringField("name"), server);
	parseSlashCommand(slashcommand, slashCommand);
	return 1;
}

int CommandConfigManager::addMaskscentSlashCommand(lua_State* L) {
	LuaObject slashcommand(L);
	if (!slashcommand.isValidTable())
		return 0;

	MaskscentSlashCommand* slashCommand = new MaskscentSlashCommand(slashcommand.getStringField("name"), server);
	parseSlashCommand(slashcommand, slashCommand);
	return 1;
}

int CommandConfigManager::addMaxCombatAbilitySlashCommand(lua_State* L) {
	LuaObject slashcommand(L);
	if (!slashcommand.isValidTable())
		return 0;

	MaxCombatAbilitySlashCommand* slashCommand = new MaxCombatAbilitySlashCommand(slashcommand.getStringField("name"), server);
	parseSlashCommand(slashcommand, slashCommand);
	return 1;
}

int CommandConfigManager::addMaxStatsSlashCommand(lua_State* L) {
	LuaObject slashcommand(L);
	if (!slashcommand.isValidTable())
		return 0;

	MaxStatsSlashCommand* slashCommand = new MaxStatsSlashCommand(slashcommand.getStringField("name"), server);
	parseSlashCommand(slashcommand, slashCommand);
	return 1;
}

int CommandConfigManager::addMedicalForageSlashCommand(lua_State* L) {
	LuaObject slashcommand(L);
	if (!slashcommand.isValidTable())
		return 0;

	MedicalForageSlashCommand* slashCommand = new MedicalForageSlashCommand(slashcommand.getStringField("name"), server);
	parseSlashCommand(slashcommand, slashCommand);
	return 1;
}

int CommandConfigManager::addMeditateSlashCommand(lua_State* L) {
	LuaObject slashcommand(L);
	if (!slashcommand.isValidTable())
		return 0;

	MeditateSlashCommand* slashCommand = new MeditateSlashCommand(slashcommand.getStringField("name"), server);
	parseSlashCommand(slashcommand, slashCommand);
	return 1;
}

int CommandConfigManager::addMeleeAssaultSlashCommand(lua_State* L) {
	LuaObject slashcommand(L);
	if (!slashcommand.isValidTable())
		return 0;

	MeleeAssaultSlashCommand* slashCommand = new MeleeAssaultSlashCommand(slashcommand.getStringField("name"), server);
	parseSlashCommand(slashcommand, slashCommand);
	return 1;
}

int CommandConfigManager::addMeleeHitSlashCommand(lua_State* L) {
	LuaObject slashcommand(L);
	if (!slashcommand.isValidTable())
		return 0;

	MeleeHitSlashCommand* slashCommand = new MeleeHitSlashCommand(slashcommand.getStringField("name"), server);
	parseSlashCommand(slashcommand, slashCommand);
	return 1;
}

int CommandConfigManager::addMeleeStrikeSlashCommand(lua_State* L) {
	LuaObject slashcommand(L);
	if (!slashcommand.isValidTable())
		return 0;

	MeleeStrikeSlashCommand* slashCommand = new MeleeStrikeSlashCommand(slashcommand.getStringField("name"), server);
	parseSlashCommand(slashcommand, slashCommand);
	return 1;
}

int CommandConfigManager::addMindBlastSlashCommand(lua_State* L) {
	LuaObject slashcommand(L);
	if (!slashcommand.isValidTable())
		return 0;

	MindBlastSlashCommand* slashCommand = new MindBlastSlashCommand(slashcommand.getStringField("name"), server);
	parseSlashCommand(slashcommand, slashCommand);
	return 1;
}

int CommandConfigManager::addMoneySlashCommand(lua_State* L) {
	LuaObject slashcommand(L);
	if (!slashcommand.isValidTable())
		return 0;

	MoneySlashCommand* slashCommand = new MoneySlashCommand(slashcommand.getStringField("name"), server);
	parseSlashCommand(slashcommand, slashCommand);
	return 1;
}

int CommandConfigManager::addMountSlashCommand(lua_State* L) {
	LuaObject slashcommand(L);
	if (!slashcommand.isValidTable())
		return 0;

	MountSlashCommand* slashCommand = new MountSlashCommand(slashcommand.getStringField("name"), server);
	parseSlashCommand(slashcommand, slashCommand);
	return 1;
}

int CommandConfigManager::addMoveFurnitureSlashCommand(lua_State* L) {
	LuaObject slashcommand(L);
	if (!slashcommand.isValidTable())
		return 0;

	MoveFurnitureSlashCommand* slashCommand = new MoveFurnitureSlashCommand(slashcommand.getStringField("name"), server);
	parseSlashCommand(slashcommand, slashCommand);
	return 1;
}

int CommandConfigManager::addNameStructureSlashCommand(lua_State* L) {
	LuaObject slashcommand(L);
	if (!slashcommand.isValidTable())
		return 0;

	NameStructureSlashCommand* slashCommand = new NameStructureSlashCommand(slashcommand.getStringField("name"), server);
	parseSlashCommand(slashcommand, slashCommand);
	return 1;
}

int CommandConfigManager::addNeurotoxinSlashCommand(lua_State* L) {
	LuaObject slashcommand(L);
	if (!slashcommand.isValidTable())
		return 0;

	NeurotoxinSlashCommand* slashCommand = new NeurotoxinSlashCommand(slashcommand.getStringField("name"), server);
	parseSlashCommand(slashcommand, slashCommand);
	return 1;
}

int CommandConfigManager::addNewbiehelperSlashCommand(lua_State* L) {
	LuaObject slashcommand(L);
	if (!slashcommand.isValidTable())
		return 0;

	NewbiehelperSlashCommand* slashCommand = new NewbiehelperSlashCommand(slashcommand.getStringField("name"), server);
	parseSlashCommand(slashcommand, slashCommand);
	return 1;
}

int CommandConfigManager::addNewbieRequestStartingLocationsSlashCommand(lua_State* L) {
	LuaObject slashcommand(L);
	if (!slashcommand.isValidTable())
		return 0;

	NewbieRequestStartingLocationsSlashCommand* slashCommand = new NewbieRequestStartingLocationsSlashCommand(slashcommand.getStringField("name"), server);
	parseSlashCommand(slashcommand, slashCommand);
	return 1;
}

int CommandConfigManager::addNewbieSelectStartingLocationSlashCommand(lua_State* L) {
	LuaObject slashcommand(L);
	if (!slashcommand.isValidTable())
		return 0;

	NewbieSelectStartingLocationSlashCommand* slashCommand = new NewbieSelectStartingLocationSlashCommand(slashcommand.getStringField("name"), server);
	parseSlashCommand(slashcommand, slashCommand);
	return 1;
}

int CommandConfigManager::addNextCraftingStageSlashCommand(lua_State* L) {
	LuaObject slashcommand(L);
	if (!slashcommand.isValidTable())
		return 0;

	NextCraftingStageSlashCommand* slashCommand = new NextCraftingStageSlashCommand(slashcommand.getStringField("name"), server);
	parseSlashCommand(slashcommand, slashCommand);
	return 1;
}

int CommandConfigManager::addNpcSlashCommand(lua_State* L) {
	LuaObject slashcommand(L);
	if (!slashcommand.isValidTable())
		return 0;

	NpcSlashCommand* slashCommand = new NpcSlashCommand(slashcommand.getStringField("name"), server);
	parseSlashCommand(slashcommand, slashCommand);
	return 1;
}

int CommandConfigManager::addNpcConversationSelectSlashCommand(lua_State* L) {
	LuaObject slashcommand(L);
	if (!slashcommand.isValidTable())
		return 0;

	NpcConversationSelectSlashCommand* slashCommand = new NpcConversationSelectSlashCommand(slashcommand.getStringField("name"), server);
	parseSlashCommand(slashcommand, slashCommand);
	return 1;
}

int CommandConfigManager::addNpcConversationStartSlashCommand(lua_State* L) {
	LuaObject slashcommand(L);
	if (!slashcommand.isValidTable())
		return 0;

	NpcConversationStartSlashCommand* slashCommand = new NpcConversationStartSlashCommand(slashcommand.getStringField("name"), server);
	parseSlashCommand(slashcommand, slashCommand);
	return 1;
}

int CommandConfigManager::addNpcConversationStopSlashCommand(lua_State* L) {
	LuaObject slashcommand(L);
	if (!slashcommand.isValidTable())
		return 0;

	NpcConversationStopSlashCommand* slashCommand = new NpcConversationStopSlashCommand(slashcommand.getStringField("name"), server);
	parseSlashCommand(slashcommand, slashCommand);
	return 1;
}

int CommandConfigManager::addNutrientInjectionSlashCommand(lua_State* L) {
	LuaObject slashcommand(L);
	if (!slashcommand.isValidTable())
		return 0;

	NutrientInjectionSlashCommand* slashCommand = new NutrientInjectionSlashCommand(slashcommand.getStringField("name"), server);
	parseSlashCommand(slashcommand, slashCommand);
	return 1;
}

int CommandConfigManager::addObjectSlashCommand(lua_State* L) {
	LuaObject slashcommand(L);
	if (!slashcommand.isValidTable())
		return 0;

	ObjectSlashCommand* slashCommand = new ObjectSlashCommand(slashcommand.getStringField("name"), server);
	parseSlashCommand(slashcommand, slashCommand);
	return 1;
}

int CommandConfigManager::addObjvarSlashCommand(lua_State* L) {
	LuaObject slashcommand(L);
	if (!slashcommand.isValidTable())
		return 0;

	ObjvarSlashCommand* slashCommand = new ObjvarSlashCommand(slashcommand.getStringField("name"), server);
	parseSlashCommand(slashcommand, slashCommand);
	return 1;
}

int CommandConfigManager::addOpenContainerSlashCommand(lua_State* L) {
	LuaObject slashcommand(L);
	if (!slashcommand.isValidTable())
		return 0;

	OpenContainerSlashCommand* slashCommand = new OpenContainerSlashCommand(slashcommand.getStringField("name"), server);
	parseSlashCommand(slashcommand, slashCommand);
	return 1;
}

int CommandConfigManager::addOpenLotteryContainerSlashCommand(lua_State* L) {
	LuaObject slashcommand(L);
	if (!slashcommand.isValidTable())
		return 0;

	OpenLotteryContainerSlashCommand* slashCommand = new OpenLotteryContainerSlashCommand(slashcommand.getStringField("name"), server);
	parseSlashCommand(slashcommand, slashCommand);
	return 1;
}

int CommandConfigManager::addOverchargeShotSlashCommand(lua_State* L) {
	LuaObject slashcommand(L);
	if (!slashcommand.isValidTable())
		return 0;

	OverchargeShotSlashCommand* slashCommand = new OverchargeShotSlashCommand(slashcommand.getStringField("name"), server);
	parseSlashCommand(slashcommand, slashCommand);
	return 1;
}

int CommandConfigManager::addOverrideActiveMonthsSlashCommand(lua_State* L) {
	LuaObject slashcommand(L);
	if (!slashcommand.isValidTable())
		return 0;

	OverrideActiveMonthsSlashCommand* slashCommand = new OverrideActiveMonthsSlashCommand(slashcommand.getStringField("name"), server);
	parseSlashCommand(slashcommand, slashCommand);
	return 1;
}

int CommandConfigManager::addOverridePadawanTrialsEligibilitySlashCommand(lua_State* L) {
	LuaObject slashcommand(L);
	if (!slashcommand.isValidTable())
		return 0;

	OverridePadawanTrialsEligibilitySlashCommand* slashCommand = new OverridePadawanTrialsEligibilitySlashCommand(slashcommand.getStringField("name"), server);
	parseSlashCommand(slashcommand, slashCommand);
	return 1;
}

int CommandConfigManager::addOverwhelmingShotSlashCommand(lua_State* L) {
	LuaObject slashcommand(L);
	if (!slashcommand.isValidTable())
		return 0;

	OverwhelmingShotSlashCommand* slashCommand = new OverwhelmingShotSlashCommand(slashcommand.getStringField("name"), server);
	parseSlashCommand(slashcommand, slashCommand);
	return 1;
}

int CommandConfigManager::addPanicShotSlashCommand(lua_State* L) {
	LuaObject slashcommand(L);
	if (!slashcommand.isValidTable())
		return 0;

	PanicShotSlashCommand* slashCommand = new PanicShotSlashCommand(slashcommand.getStringField("name"), server);
	parseSlashCommand(slashcommand, slashCommand);
	return 1;
}

int CommandConfigManager::addParalyzeSlashCommand(lua_State* L) {
	LuaObject slashcommand(L);
	if (!slashcommand.isValidTable())
		return 0;

	ParalyzeSlashCommand* slashCommand = new ParalyzeSlashCommand(slashcommand.getStringField("name"), server);
	parseSlashCommand(slashcommand, slashCommand);
	return 1;
}

int CommandConfigManager::addParryRiposteSlashCommand(lua_State* L) {
	LuaObject slashcommand(L);
	if (!slashcommand.isValidTable())
		return 0;

	ParryRiposteSlashCommand* slashCommand = new ParryRiposteSlashCommand(slashcommand.getStringField("name"), server);
	parseSlashCommand(slashcommand, slashCommand);
	return 1;
}

int CommandConfigManager::addPauseDanceSlashCommand(lua_State* L) {
	LuaObject slashcommand(L);
	if (!slashcommand.isValidTable())
		return 0;

	PauseDanceSlashCommand* slashCommand = new PauseDanceSlashCommand(slashcommand.getStringField("name"), server);
	parseSlashCommand(slashcommand, slashCommand);
	return 1;
}

int CommandConfigManager::addPauseMusicSlashCommand(lua_State* L) {
	LuaObject slashcommand(L);
	if (!slashcommand.isValidTable())
		return 0;

	PauseMusicSlashCommand* slashCommand = new PauseMusicSlashCommand(slashcommand.getStringField("name"), server);
	parseSlashCommand(slashcommand, slashCommand);
	return 1;
}

int CommandConfigManager::addPaWithdrawSlashCommand(lua_State* L) {
	LuaObject slashcommand(L);
	if (!slashcommand.isValidTable())
		return 0;

	PaWithdrawSlashCommand* slashCommand = new PaWithdrawSlashCommand(slashcommand.getStringField("name"), server);
	parseSlashCommand(slashcommand, slashCommand);
	return 1;
}

int CommandConfigManager::addPaymaintenanceSlashCommand(lua_State* L) {
	LuaObject slashcommand(L);
	if (!slashcommand.isValidTable())
		return 0;

	PaymaintenanceSlashCommand* slashCommand = new PaymaintenanceSlashCommand(slashcommand.getStringField("name"), server);
	parseSlashCommand(slashcommand, slashCommand);
	return 1;
}

int CommandConfigManager::addPeaceSlashCommand(lua_State* L) {
	LuaObject slashcommand(L);
	if (!slashcommand.isValidTable())
		return 0;

	PeaceSlashCommand* slashCommand = new PeaceSlashCommand(slashcommand.getStringField("name"), server);
	parseSlashCommand(slashcommand, slashCommand);
	return 1;
}
int CommandConfigManager::addPermissionListModifySlashCommand(lua_State* L) {
	LuaObject slashcommand(L);
	if (!slashcommand.isValidTable())
		return 0;

	PermissionListModifySlashCommand* slashCommand = new PermissionListModifySlashCommand(slashcommand.getStringField("name"), server);
	parseSlashCommand(slashcommand, slashCommand);
	return 1;
}

int CommandConfigManager::addPistolWhipSlashCommand(lua_State* L) {
	LuaObject slashcommand(L);
	if (!slashcommand.isValidTable())
		return 0;

	PistolWhipSlashCommand* slashCommand = new PistolWhipSlashCommand(slashcommand.getStringField("name"), server);
	parseSlashCommand(slashcommand, slashCommand);
	return 1;
}

int CommandConfigManager::addPlaceBattlefieldStructureSlashCommand(lua_State* L) {
	LuaObject slashcommand(L);
	if (!slashcommand.isValidTable())
		return 0;

	PlaceBattlefieldStructureSlashCommand* slashCommand = new PlaceBattlefieldStructureSlashCommand(slashcommand.getStringField("name"), server);
	parseSlashCommand(slashcommand, slashCommand);
	return 1;
}

int CommandConfigManager::addPlacedShotSlashCommand(lua_State* L) {
	LuaObject slashcommand(L);
	if (!slashcommand.isValidTable())
		return 0;

	PlacedShotSlashCommand* slashCommand = new PlacedShotSlashCommand(slashcommand.getStringField("name"), server);
	parseSlashCommand(slashcommand, slashCommand);
	return 1;
}

int CommandConfigManager::addPlaceStructureSlashCommand(lua_State* L) {
	LuaObject slashcommand(L);
	if (!slashcommand.isValidTable())
		return 0;

	PlaceStructureSlashCommand* slashCommand = new PlaceStructureSlashCommand(slashcommand.getStringField("name"), server);
	parseSlashCommand(slashcommand, slashCommand);
	return 1;
}

int CommandConfigManager::addPlaceStructureModeSlashCommand(lua_State* L) {
	LuaObject slashcommand(L);
	if (!slashcommand.isValidTable())
		return 0;

	PlaceStructureModeSlashCommand* slashCommand = new PlaceStructureModeSlashCommand(slashcommand.getStringField("name"), server);
	parseSlashCommand(slashcommand, slashCommand);
	return 1;
}

int CommandConfigManager::addPlanetsaySlashCommand(lua_State* L) {
	LuaObject slashcommand(L);
	if (!slashcommand.isValidTable())
		return 0;

	PlanetsaySlashCommand* slashCommand = new PlanetsaySlashCommand(slashcommand.getStringField("name"), server);
	parseSlashCommand(slashcommand, slashCommand);
	return 1;
}

int CommandConfigManager::addPlanetwarpSlashCommand(lua_State* L) {
	LuaObject slashcommand(L);
	if (!slashcommand.isValidTable())
		return 0;

	PlanetwarpSlashCommand* slashCommand = new PlanetwarpSlashCommand(slashcommand.getStringField("name"), server);
	parseSlashCommand(slashcommand, slashCommand);
	return 1;
}

int CommandConfigManager::addPlanetwarpTargetSlashCommand(lua_State* L) {
	LuaObject slashcommand(L);
	if (!slashcommand.isValidTable())
		return 0;

	PlanetwarpTargetSlashCommand* slashCommand = new PlanetwarpTargetSlashCommand(slashcommand.getStringField("name"), server);
	parseSlashCommand(slashcommand, slashCommand);
	return 1;
}

int CommandConfigManager::addPointBlankAreaSlashCommand(lua_State* L) {
	LuaObject slashcommand(L);
	if (!slashcommand.isValidTable())
		return 0;

	PointBlankAreaSlashCommand* slashCommand = new PointBlankAreaSlashCommand(slashcommand.getStringField("name"), server);
	parseSlashCommand(slashcommand, slashCommand);
	return 1;
}

int CommandConfigManager::addPointBlankShotSlashCommand(lua_State* L) {
	LuaObject slashcommand(L);
	if (!slashcommand.isValidTable())
		return 0;

	PointBlankShotSlashCommand* slashCommand = new PointBlankShotSlashCommand(slashcommand.getStringField("name"), server);
	parseSlashCommand(slashcommand, slashCommand);
	return 1;
}

int CommandConfigManager::addPoisonInnoculationSlashCommand(lua_State* L) {
	LuaObject slashcommand(L);
	if (!slashcommand.isValidTable())
		return 0;

	PoisonInnoculationSlashCommand* slashCommand = new PoisonInnoculationSlashCommand(slashcommand.getStringField("name"), server);
	parseSlashCommand(slashcommand, slashCommand);
	return 1;
}

int CommandConfigManager::addPowerAttackSlashCommand(lua_State* L) {
	LuaObject slashcommand(L);
	if (!slashcommand.isValidTable())
		return 0;

	PowerAttackSlashCommand* slashCommand = new PowerAttackSlashCommand(slashcommand.getStringField("name"), server);
	parseSlashCommand(slashcommand, slashCommand);
	return 1;
}

int CommandConfigManager::addPowerBoostSlashCommand(lua_State* L) {
	LuaObject slashcommand(L);
	if (!slashcommand.isValidTable())
		return 0;

	PowerBoostSlashCommand* slashCommand = new PowerBoostSlashCommand(slashcommand.getStringField("name"), server);
	parseSlashCommand(slashcommand, slashCommand);
	return 1;
}

int CommandConfigManager::addProneSlashCommand(lua_State* L) {
	LuaObject slashcommand(L);
	if (!slashcommand.isValidTable())
		return 0;

	ProneSlashCommand* slashCommand = new ProneSlashCommand(slashcommand.getStringField("name"), server);
	parseSlashCommand(slashcommand, slashCommand);
	return 1;
}

int CommandConfigManager::addPurchaseReinforcementSlashCommand(lua_State* L) {
	LuaObject slashcommand(L);
	if (!slashcommand.isValidTable())
		return 0;

	PurchaseReinforcementSlashCommand* slashCommand = new PurchaseReinforcementSlashCommand(slashcommand.getStringField("name"), server);
	parseSlashCommand(slashcommand, slashCommand);
	return 1;
}

int CommandConfigManager::addPurchaseTicketSlashCommand(lua_State* L) {
	LuaObject slashcommand(L);
	if (!slashcommand.isValidTable())
		return 0;

	PurchaseTicketSlashCommand* slashCommand = new PurchaseTicketSlashCommand(slashcommand.getStringField("name"), server);
	parseSlashCommand(slashcommand, slashCommand);
	return 1;
}

int CommandConfigManager::addQuickDrawSlashCommand(lua_State* L) {
	LuaObject slashcommand(L);
	if (!slashcommand.isValidTable())
		return 0;

	QuickDrawSlashCommand* slashCommand = new QuickDrawSlashCommand(slashcommand.getStringField("name"), server);
	parseSlashCommand(slashcommand, slashCommand);
	return 1;
}

int CommandConfigManager::addRallySlashCommand(lua_State* L) {
	LuaObject slashcommand(L);
	if (!slashcommand.isValidTable())
		return 0;

	RallySlashCommand* slashCommand = new RallySlashCommand(slashcommand.getStringField("name"), server);
	parseSlashCommand(slashcommand, slashCommand);
	return 1;
}

int CommandConfigManager::addRangedShotSlashCommand(lua_State* L) {
	LuaObject slashcommand(L);
	if (!slashcommand.isValidTable())
		return 0;

	RangedShotSlashCommand* slashCommand = new RangedShotSlashCommand(slashcommand.getStringField("name"), server);
	parseSlashCommand(slashcommand, slashCommand);
	return 1;
}

int CommandConfigManager::addRapidFireSlashCommand(lua_State* L) {
	LuaObject slashcommand(L);
	if (!slashcommand.isValidTable())
		return 0;

	RapidFireSlashCommand* slashCommand = new RapidFireSlashCommand(slashcommand.getStringField("name"), server);
	parseSlashCommand(slashcommand, slashCommand);
	return 1;
}

int CommandConfigManager::addRecklessShotSlashCommand(lua_State* L) {
	LuaObject slashcommand(L);
	if (!slashcommand.isValidTable())
		return 0;

	RecklessShotSlashCommand* slashCommand = new RecklessShotSlashCommand(slashcommand.getStringField("name"), server);
	parseSlashCommand(slashcommand, slashCommand);
	return 1;
}

int CommandConfigManager::addReconnectToTransferServerSlashCommand(lua_State* L) {
	LuaObject slashcommand(L);
	if (!slashcommand.isValidTable())
		return 0;

	ReconnectToTransferServerSlashCommand* slashCommand = new ReconnectToTransferServerSlashCommand(slashcommand.getStringField("name"), server);
	parseSlashCommand(slashcommand, slashCommand);
	return 1;
}

int CommandConfigManager::addRecruitSkillTrainerSlashCommand(lua_State* L) {
	LuaObject slashcommand(L);
	if (!slashcommand.isValidTable())
		return 0;

	RecruitSkillTrainerSlashCommand* slashCommand = new RecruitSkillTrainerSlashCommand(slashcommand.getStringField("name"), server);
	parseSlashCommand(slashcommand, slashCommand);
	return 1;
}

int CommandConfigManager::addRegainConsciousnessSlashCommand(lua_State* L) {
	LuaObject slashcommand(L);
	if (!slashcommand.isValidTable())
		return 0;

	RegainConsciousnessSlashCommand* slashCommand = new RegainConsciousnessSlashCommand(slashcommand.getStringField("name"), server);
	parseSlashCommand(slashcommand, slashCommand);
	return 1;
}

int CommandConfigManager::addRegenerationSlashCommand(lua_State* L) {
	LuaObject slashcommand(L);
	if (!slashcommand.isValidTable())
		return 0;

	RegenerationSlashCommand* slashCommand = new RegenerationSlashCommand(slashcommand.getStringField("name"), server);
	parseSlashCommand(slashcommand, slashCommand);
	return 1;
}

int CommandConfigManager::addRegisterWithLocationSlashCommand(lua_State* L) {
	LuaObject slashcommand(L);
	if (!slashcommand.isValidTable())
		return 0;

	RegisterWithLocationSlashCommand* slashCommand = new RegisterWithLocationSlashCommand(slashcommand.getStringField("name"), server);
	parseSlashCommand(slashcommand, slashCommand);
	return 1;
}

int CommandConfigManager::addReloadSlashCommand(lua_State* L) {
	LuaObject slashcommand(L);
	if (!slashcommand.isValidTable())
		return 0;

	ReloadSlashCommand* slashCommand = new ReloadSlashCommand(slashcommand.getStringField("name"), server);
	parseSlashCommand(slashcommand, slashCommand);
	return 1;
}

int CommandConfigManager::addRemoteSlashCommand(lua_State* L) {
	LuaObject slashcommand(L);
	if (!slashcommand.isValidTable())
		return 0;

	RemoteSlashCommand* slashCommand = new RemoteSlashCommand(slashcommand.getStringField("name"), server);
	parseSlashCommand(slashcommand, slashCommand);
	return 1;
}

int CommandConfigManager::addRemoveAllowedPlayerSlashCommand(lua_State* L) {
	LuaObject slashcommand(L);
	if (!slashcommand.isValidTable())
		return 0;

	RemoveAllowedPlayerSlashCommand* slashCommand = new RemoveAllowedPlayerSlashCommand(slashcommand.getStringField("name"), server);
	parseSlashCommand(slashcommand, slashCommand);
	return 1;
}

int CommandConfigManager::addRemoveBannedPlayerSlashCommand(lua_State* L) {
	LuaObject slashcommand(L);
	if (!slashcommand.isValidTable())
		return 0;

	RemoveBannedPlayerSlashCommand* slashCommand = new RemoveBannedPlayerSlashCommand(slashcommand.getStringField("name"), server);
	parseSlashCommand(slashcommand, slashCommand);
	return 1;
}

int CommandConfigManager::addRemoveFriendSlashCommand(lua_State* L) {
	LuaObject slashcommand(L);
	if (!slashcommand.isValidTable())
		return 0;

	RemoveFriendSlashCommand* slashCommand = new RemoveFriendSlashCommand(slashcommand.getStringField("name"), server);
	parseSlashCommand(slashcommand, slashCommand);
	return 1;
}

int CommandConfigManager::addRemoveIgnoreSlashCommand(lua_State* L) {
	LuaObject slashcommand(L);
	if (!slashcommand.isValidTable())
		return 0;

	RemoveIgnoreSlashCommand* slashCommand = new RemoveIgnoreSlashCommand(slashcommand.getStringField("name"), server);
	parseSlashCommand(slashcommand, slashCommand);
	return 1;
}

int CommandConfigManager::addRepairBattlefieldStructureSlashCommand(lua_State* L) {
	LuaObject slashcommand(L);
	if (!slashcommand.isValidTable())
		return 0;

	RepairBattlefieldStructureSlashCommand* slashCommand = new RepairBattlefieldStructureSlashCommand(slashcommand.getStringField("name"), server);
	parseSlashCommand(slashcommand, slashCommand);
	return 1;
}

int CommandConfigManager::addRepairShipComponentInSlotSlashCommand(lua_State* L) {
	LuaObject slashcommand(L);
	if (!slashcommand.isValidTable())
		return 0;

	RepairShipComponentInSlotSlashCommand* slashCommand = new RepairShipComponentInSlotSlashCommand(slashcommand.getStringField("name"), server);
	parseSlashCommand(slashcommand, slashCommand);
	return 1;
}

int CommandConfigManager::addReportSlashCommand(lua_State* L) {
	LuaObject slashcommand(L);
	if (!slashcommand.isValidTable())
		return 0;

	ReportSlashCommand* slashCommand = new ReportSlashCommand(slashcommand.getStringField("name"), server);
	parseSlashCommand(slashcommand, slashCommand);
	return 1;
}

int CommandConfigManager::addRequestBadgesSlashCommand(lua_State* L) {
	LuaObject slashcommand(L);
	if (!slashcommand.isValidTable())
		return 0;

	RequestBadgesSlashCommand* slashCommand = new RequestBadgesSlashCommand(slashcommand.getStringField("name"), server);
	parseSlashCommand(slashcommand, slashCommand);
	return 1;
}

int CommandConfigManager::addRequestBiographySlashCommand(lua_State* L) {
	LuaObject slashcommand(L);
	if (!slashcommand.isValidTable())
		return 0;

	RequestBiographySlashCommand* slashCommand = new RequestBiographySlashCommand(slashcommand.getStringField("name"), server);
	parseSlashCommand(slashcommand, slashCommand);
	return 1;
}

int CommandConfigManager::addRequestCharacterMatchSlashCommand(lua_State* L) {
	LuaObject slashcommand(L);
	if (!slashcommand.isValidTable())
		return 0;

	RequestCharacterMatchSlashCommand* slashCommand = new RequestCharacterMatchSlashCommand(slashcommand.getStringField("name"), server);
	parseSlashCommand(slashcommand, slashCommand);
	return 1;
}

int CommandConfigManager::addRequestCharacterSheetInfoSlashCommand(lua_State* L) {
	LuaObject slashcommand(L);
	if (!slashcommand.isValidTable())
		return 0;

	RequestCharacterSheetInfoSlashCommand* slashCommand = new RequestCharacterSheetInfoSlashCommand(slashcommand.getStringField("name"), server);
	parseSlashCommand(slashcommand, slashCommand);
	return 1;
}

int CommandConfigManager::addRequestCoreSampleSlashCommand(lua_State* L) {
	LuaObject slashcommand(L);
	if (!slashcommand.isValidTable())
		return 0;

	RequestCoreSampleSlashCommand* slashCommand = new RequestCoreSampleSlashCommand(slashcommand.getStringField("name"), server);
	parseSlashCommand(slashcommand, slashCommand);
	return 1;
}

int CommandConfigManager::addRequestCraftingSessionSlashCommand(lua_State* L) {
	LuaObject slashcommand(L);
	if (!slashcommand.isValidTable())
		return 0;

	RequestCraftingSessionSlashCommand* slashCommand = new RequestCraftingSessionSlashCommand(slashcommand.getStringField("name"), server);
	parseSlashCommand(slashcommand, slashCommand);
	return 1;
}

int CommandConfigManager::addRequestDraftSlotsSlashCommand(lua_State* L) {
	LuaObject slashcommand(L);
	if (!slashcommand.isValidTable())
		return 0;

	RequestDraftSlotsSlashCommand* slashCommand = new RequestDraftSlotsSlashCommand(slashcommand.getStringField("name"), server);
	parseSlashCommand(slashcommand, slashCommand);
	return 1;
}

int CommandConfigManager::addRequestDraftSlotsBatchSlashCommand(lua_State* L) {
	LuaObject slashcommand(L);
	if (!slashcommand.isValidTable())
		return 0;

	RequestDraftSlotsBatchSlashCommand* slashCommand = new RequestDraftSlotsBatchSlashCommand(slashcommand.getStringField("name"), server);
	parseSlashCommand(slashcommand, slashCommand);
	return 1;
}

int CommandConfigManager::addRequestManfSchematicSlotsSlashCommand(lua_State* L) {
	LuaObject slashcommand(L);
	if (!slashcommand.isValidTable())
		return 0;

	RequestManfSchematicSlotsSlashCommand* slashCommand = new RequestManfSchematicSlotsSlashCommand(slashcommand.getStringField("name"), server);
	parseSlashCommand(slashcommand, slashCommand);
	return 1;
}

int CommandConfigManager::addRequestResourceWeightsSlashCommand(lua_State* L) {
	LuaObject slashcommand(L);
	if (!slashcommand.isValidTable())
		return 0;

	RequestResourceWeightsSlashCommand* slashCommand = new RequestResourceWeightsSlashCommand(slashcommand.getStringField("name"), server);
	parseSlashCommand(slashcommand, slashCommand);
	return 1;
}

int CommandConfigManager::addRequestResourceWeightsBatchSlashCommand(lua_State* L) {
	LuaObject slashcommand(L);
	if (!slashcommand.isValidTable())
		return 0;

	RequestResourceWeightsBatchSlashCommand* slashCommand = new RequestResourceWeightsBatchSlashCommand(slashcommand.getStringField("name"), server);
	parseSlashCommand(slashcommand, slashCommand);
	return 1;
}

int CommandConfigManager::addRequestSetStatMigrationDataSlashCommand(lua_State* L) {
	LuaObject slashcommand(L);
	if (!slashcommand.isValidTable())
		return 0;

	RequestSetStatMigrationDataSlashCommand* slashCommand = new RequestSetStatMigrationDataSlashCommand(slashcommand.getStringField("name"), server);
	parseSlashCommand(slashcommand, slashCommand);
	return 1;
}

int CommandConfigManager::addRequestStatMigrationDataSlashCommand(lua_State* L) {
	LuaObject slashcommand(L);
	if (!slashcommand.isValidTable())
		return 0;

	RequestStatMigrationDataSlashCommand* slashCommand = new RequestStatMigrationDataSlashCommand(slashcommand.getStringField("name"), server);
	parseSlashCommand(slashcommand, slashCommand);
	return 1;
}

int CommandConfigManager::addRequestStatMigrationStartSlashCommand(lua_State* L) {
	LuaObject slashcommand(L);
	if (!slashcommand.isValidTable())
		return 0;

	RequestStatMigrationStartSlashCommand* slashCommand = new RequestStatMigrationStartSlashCommand(slashcommand.getStringField("name"), server);
	parseSlashCommand(slashcommand, slashCommand);
	return 1;
}

int CommandConfigManager::addRequestStatMigrationStopSlashCommand(lua_State* L) {
	LuaObject slashcommand(L);
	if (!slashcommand.isValidTable())
		return 0;

	RequestStatMigrationStopSlashCommand* slashCommand = new RequestStatMigrationStopSlashCommand(slashcommand.getStringField("name"), server);
	parseSlashCommand(slashcommand, slashCommand);
	return 1;
}

int CommandConfigManager::addRequestStimpackSlashCommand(lua_State* L) {
	LuaObject slashcommand(L);
	if (!slashcommand.isValidTable())
		return 0;

	RequestStimpackSlashCommand* slashCommand = new RequestStimpackSlashCommand(slashcommand.getStringField("name"), server);
	parseSlashCommand(slashcommand, slashCommand);
	return 1;
}

int CommandConfigManager::addRequestSurveySlashCommand(lua_State* L) {
	LuaObject slashcommand(L);
	if (!slashcommand.isValidTable())
		return 0;

	RequestSurveySlashCommand* slashCommand = new RequestSurveySlashCommand(slashcommand.getStringField("name"), server);
	parseSlashCommand(slashcommand, slashCommand);
	return 1;
}

int CommandConfigManager::addRequestWaypointAtPositionSlashCommand(lua_State* L) {
	LuaObject slashcommand(L);
	if (!slashcommand.isValidTable())
		return 0;

	RequestWaypointAtPositionSlashCommand* slashCommand = new RequestWaypointAtPositionSlashCommand(slashcommand.getStringField("name"), server);
	parseSlashCommand(slashcommand, slashCommand);
	return 1;
}

int CommandConfigManager::addRescueSlashCommand(lua_State* L) {
	LuaObject slashcommand(L);
	if (!slashcommand.isValidTable())
		return 0;

	RescueSlashCommand* slashCommand = new RescueSlashCommand(slashcommand.getStringField("name"), server);
	parseSlashCommand(slashcommand, slashCommand);
	return 1;
}

int CommandConfigManager::addResendLoginMessageToAllSlashCommand(lua_State* L) {
	LuaObject slashcommand(L);
	if (!slashcommand.isValidTable())
		return 0;

	ResendLoginMessageToAllSlashCommand* slashCommand = new ResendLoginMessageToAllSlashCommand(slashcommand.getStringField("name"), server);
	parseSlashCommand(slashcommand, slashCommand);
	return 1;
}

int CommandConfigManager::addResetJediSlashCommand(lua_State* L) {
	LuaObject slashcommand(L);
	if (!slashcommand.isValidTable())
		return 0;

	ResetJediSlashCommand* slashCommand = new ResetJediSlashCommand(slashcommand.getStringField("name"), server);
	parseSlashCommand(slashcommand, slashCommand);
	return 1;
}

int CommandConfigManager::addResourceSlashCommand(lua_State* L) {
	LuaObject slashcommand(L);
	if (!slashcommand.isValidTable())
		return 0;

	ResourceSlashCommand* slashCommand = new ResourceSlashCommand(slashcommand.getStringField("name"), server);
	parseSlashCommand(slashcommand, slashCommand);
	return 1;
}

int CommandConfigManager::addResourceContainerSplitSlashCommand(lua_State* L) {
	LuaObject slashcommand(L);
	if (!slashcommand.isValidTable())
		return 0;

	ResourceContainerSplitSlashCommand* slashCommand = new ResourceContainerSplitSlashCommand(slashcommand.getStringField("name"), server);
	parseSlashCommand(slashcommand, slashCommand);
	return 1;
}

int CommandConfigManager::addResourceContainerTransferSlashCommand(lua_State* L) {
	LuaObject slashcommand(L);
	if (!slashcommand.isValidTable())
		return 0;

	ResourceContainerTransferSlashCommand* slashCommand = new ResourceContainerTransferSlashCommand(slashcommand.getStringField("name"), server);
	parseSlashCommand(slashcommand, slashCommand);
	return 1;
}

int CommandConfigManager::addResourceSetNameSlashCommand(lua_State* L) {
	LuaObject slashcommand(L);
	if (!slashcommand.isValidTable())
		return 0;

	ResourceSetNameSlashCommand* slashCommand = new ResourceSetNameSlashCommand(slashcommand.getStringField("name"), server);
	parseSlashCommand(slashcommand, slashCommand);
	return 1;
}

int CommandConfigManager::addRespecStatCommitSlashCommand(lua_State* L) {
	LuaObject slashcommand(L);
	if (!slashcommand.isValidTable())
		return 0;

	RespecStatCommitSlashCommand* slashCommand = new RespecStatCommitSlashCommand(slashcommand.getStringField("name"), server);
	parseSlashCommand(slashcommand, slashCommand);
	return 1;
}

int CommandConfigManager::addResSampleLoopSlashCommand(lua_State* L) {
	LuaObject slashcommand(L);
	if (!slashcommand.isValidTable())
		return 0;

	ResSampleLoopSlashCommand* slashCommand = new ResSampleLoopSlashCommand(slashcommand.getStringField("name"), server);
	parseSlashCommand(slashcommand, slashCommand);
	return 1;
}

int CommandConfigManager::addRestartConversionSlashCommand(lua_State* L) {
	LuaObject slashcommand(L);
	if (!slashcommand.isValidTable())
		return 0;

	RestartConversionSlashCommand* slashCommand = new RestartConversionSlashCommand(slashcommand.getStringField("name"), server);
	parseSlashCommand(slashcommand, slashCommand);
	return 1;
}

int CommandConfigManager::addRestartCraftingSessionSlashCommand(lua_State* L) {
	LuaObject slashcommand(L);
	if (!slashcommand.isValidTable())
		return 0;

	RestartCraftingSessionSlashCommand* slashCommand = new RestartCraftingSessionSlashCommand(slashcommand.getStringField("name"), server);
	parseSlashCommand(slashcommand, slashCommand);
	return 1;
}

int CommandConfigManager::addRestrainingShotSlashCommand(lua_State* L) {
	LuaObject slashcommand(L);
	if (!slashcommand.isValidTable())
		return 0;

	RestrainingShotSlashCommand* slashCommand = new RestrainingShotSlashCommand(slashcommand.getStringField("name"), server);
	parseSlashCommand(slashcommand, slashCommand);
	return 1;
}

int CommandConfigManager::addResuscitatePlayerSlashCommand(lua_State* L) {
	LuaObject slashcommand(L);
	if (!slashcommand.isValidTable())
		return 0;

	ResuscitatePlayerSlashCommand* slashCommand = new ResuscitatePlayerSlashCommand(slashcommand.getStringField("name"), server);
	parseSlashCommand(slashcommand, slashCommand);
	return 1;
}

int CommandConfigManager::addRetreatSlashCommand(lua_State* L) {
	LuaObject slashcommand(L);
	if (!slashcommand.isValidTable())
		return 0;

	RetreatSlashCommand* slashCommand = new RetreatSlashCommand(slashcommand.getStringField("name"), server);
	parseSlashCommand(slashcommand, slashCommand);
	return 1;
}

int CommandConfigManager::addRevivePlayerSlashCommand(lua_State* L) {
	LuaObject slashcommand(L);
	if (!slashcommand.isValidTable())
		return 0;

	RevivePlayerSlashCommand* slashCommand = new RevivePlayerSlashCommand(slashcommand.getStringField("name"), server);
	parseSlashCommand(slashcommand, slashCommand);
	return 1;
}

int CommandConfigManager::addRevokeBadgeSlashCommand(lua_State* L) {
	LuaObject slashcommand(L);
	if (!slashcommand.isValidTable())
		return 0;

	RevokeBadgeSlashCommand* slashCommand = new RevokeBadgeSlashCommand(slashcommand.getStringField("name"), server);
	parseSlashCommand(slashcommand, slashCommand);
	return 1;
}

int CommandConfigManager::addRevokeSkillSlashCommand(lua_State* L) {
	LuaObject slashcommand(L);
	if (!slashcommand.isValidTable())
		return 0;

	RevokeSkillSlashCommand* slashCommand = new RevokeSkillSlashCommand(slashcommand.getStringField("name"), server);
	parseSlashCommand(slashcommand, slashCommand);
	return 1;
}

int CommandConfigManager::addRolePlaySlashCommand(lua_State* L) {
	LuaObject slashcommand(L);
	if (!slashcommand.isValidTable())
		return 0;

	RolePlaySlashCommand* slashCommand = new RolePlaySlashCommand(slashcommand.getStringField("name"), server);
	parseSlashCommand(slashcommand, slashCommand);
	return 1;
}

int CommandConfigManager::addRollShotSlashCommand(lua_State* L) {
	LuaObject slashcommand(L);
	if (!slashcommand.isValidTable())
		return 0;

	RollShotSlashCommand* slashCommand = new RollShotSlashCommand(slashcommand.getStringField("name"), server);
	parseSlashCommand(slashcommand, slashCommand);
	return 1;
}

int CommandConfigManager::addRotateFurnitureSlashCommand(lua_State* L) {
	LuaObject slashcommand(L);
	if (!slashcommand.isValidTable())
		return 0;

	RotateFurnitureSlashCommand* slashCommand = new RotateFurnitureSlashCommand(slashcommand.getStringField("name"), server);
	parseSlashCommand(slashcommand, slashCommand);
	return 1;
}

int CommandConfigManager::addSaberArmorBreakSlashCommand(lua_State* L) {
	LuaObject slashcommand(L);
	if (!slashcommand.isValidTable())
		return 0;

	SaberArmorBreakSlashCommand* slashCommand = new SaberArmorBreakSlashCommand(slashcommand.getStringField("name"), server);
	parseSlashCommand(slashcommand, slashCommand);
	return 1;
}

int CommandConfigManager::addSaberBlindSlashCommand(lua_State* L) {
	LuaObject slashcommand(L);
	if (!slashcommand.isValidTable())
		return 0;

	SaberBlindSlashCommand* slashCommand = new SaberBlindSlashCommand(slashcommand.getStringField("name"), server);
	parseSlashCommand(slashcommand, slashCommand);
	return 1;
}

int CommandConfigManager::addSaberBodyHitSlashCommand(lua_State* L) {
	LuaObject slashcommand(L);
	if (!slashcommand.isValidTable())
		return 0;

	SaberBodyHitSlashCommand* slashCommand = new SaberBodyHitSlashCommand(slashcommand.getStringField("name"), server);
	parseSlashCommand(slashcommand, slashCommand);
	return 1;
}

int CommandConfigManager::addSaberDervishSlashCommand(lua_State* L) {
	LuaObject slashcommand(L);
	if (!slashcommand.isValidTable())
		return 0;

	SaberDervishSlashCommand* slashCommand = new SaberDervishSlashCommand(slashcommand.getStringField("name"), server);
	parseSlashCommand(slashcommand, slashCommand);
	return 1;
}

int CommandConfigManager::addSaberHeadHitSlashCommand(lua_State* L) {
	LuaObject slashcommand(L);
	if (!slashcommand.isValidTable())
		return 0;

	SaberHeadHitSlashCommand* slashCommand = new SaberHeadHitSlashCommand(slashcommand.getStringField("name"), server);
	parseSlashCommand(slashcommand, slashCommand);
	return 1;
}

int CommandConfigManager::addSaberHitSlashCommand(lua_State* L) {
	LuaObject slashcommand(L);
	if (!slashcommand.isValidTable())
		return 0;

	SaberHitSlashCommand* slashCommand = new SaberHitSlashCommand(slashcommand.getStringField("name"), server);
	parseSlashCommand(slashcommand, slashCommand);
	return 1;
}

int CommandConfigManager::addSaberLegHitSlashCommand(lua_State* L) {
	LuaObject slashcommand(L);
	if (!slashcommand.isValidTable())
		return 0;

	SaberLegHitSlashCommand* slashCommand = new SaberLegHitSlashCommand(slashcommand.getStringField("name"), server);
	parseSlashCommand(slashcommand, slashCommand);
	return 1;
}

int CommandConfigManager::addSaberPowerAttackSlashCommand(lua_State* L) {
	LuaObject slashcommand(L);
	if (!slashcommand.isValidTable())
		return 0;

	SaberPowerAttackSlashCommand* slashCommand = new SaberPowerAttackSlashCommand(slashcommand.getStringField("name"), server);
	parseSlashCommand(slashcommand, slashCommand);
	return 1;
}

int CommandConfigManager::addSaberSlashSlashCommand(lua_State* L) {
	LuaObject slashcommand(L);
	if (!slashcommand.isValidTable())
		return 0;

	SaberSlashSlashCommand* slashCommand = new SaberSlashSlashCommand(slashcommand.getStringField("name"), server);
	parseSlashCommand(slashcommand, slashCommand);
	return 1;
}

int CommandConfigManager::addSaberSpinAttackSlashCommand(lua_State* L) {
	LuaObject slashcommand(L);
	if (!slashcommand.isValidTable())
		return 0;

	SaberSpinAttackSlashCommand* slashCommand = new SaberSpinAttackSlashCommand(slashcommand.getStringField("name"), server);
	parseSlashCommand(slashcommand, slashCommand);
	return 1;
}

int CommandConfigManager::addSaberStrikeSlashCommand(lua_State* L) {
	LuaObject slashcommand(L);
	if (!slashcommand.isValidTable())
		return 0;

	SaberStrikeSlashCommand* slashCommand = new SaberStrikeSlashCommand(slashcommand.getStringField("name"), server);
	parseSlashCommand(slashcommand, slashCommand);
	return 1;
}

int CommandConfigManager::addSaberStunStrikeSlashCommand(lua_State* L) {
	LuaObject slashcommand(L);
	if (!slashcommand.isValidTable())
		return 0;

	SaberStunStrikeSlashCommand* slashCommand = new SaberStunStrikeSlashCommand(slashcommand.getStringField("name"), server);
	parseSlashCommand(slashcommand, slashCommand);
	return 1;
}

int CommandConfigManager::addSaberSweepSlashCommand(lua_State* L) {
	LuaObject slashcommand(L);
	if (!slashcommand.isValidTable())
		return 0;

	SaberSweepSlashCommand* slashCommand = new SaberSweepSlashCommand(slashcommand.getStringField("name"), server);
	parseSlashCommand(slashcommand, slashCommand);
	return 1;
}

int CommandConfigManager::addSaberSwipeSlashCommand(lua_State* L) {
	LuaObject slashcommand(L);
	if (!slashcommand.isValidTable())
		return 0;

	SaberSwipeSlashCommand* slashCommand = new SaberSwipeSlashCommand(slashcommand.getStringField("name"), server);
	parseSlashCommand(slashcommand, slashCommand);
	return 1;
}

int CommandConfigManager::addSaberThrowSlashCommand(lua_State* L) {
	LuaObject slashcommand(L);
	if (!slashcommand.isValidTable())
		return 0;

	SaberThrowSlashCommand* slashCommand = new SaberThrowSlashCommand(slashcommand.getStringField("name"), server);
	parseSlashCommand(slashcommand, slashCommand);
	return 1;
}

int CommandConfigManager::addSampleSlashCommand(lua_State* L) {
	LuaObject slashcommand(L);
	if (!slashcommand.isValidTable())
		return 0;

	SampleSlashCommand* slashCommand = new SampleSlashCommand(slashcommand.getStringField("name"), server);
	parseSlashCommand(slashcommand, slashCommand);
	return 1;
}

int CommandConfigManager::addSampleDNASlashCommand(lua_State* L) {
	LuaObject slashcommand(L);
	if (!slashcommand.isValidTable())
		return 0;

	SampleDNASlashCommand* slashCommand = new SampleDNASlashCommand(slashcommand.getStringField("name"), server);
	parseSlashCommand(slashcommand, slashCommand);
	return 1;
}

int CommandConfigManager::addScatterHitSlashCommand(lua_State* L) {
	LuaObject slashcommand(L);
	if (!slashcommand.isValidTable())
		return 0;

	ScatterHitSlashCommand* slashCommand = new ScatterHitSlashCommand(slashcommand.getStringField("name"), server);
	parseSlashCommand(slashcommand, slashCommand);
	return 1;
}

int CommandConfigManager::addScatterShotSlashCommand(lua_State* L) {
	LuaObject slashcommand(L);
	if (!slashcommand.isValidTable())
		return 0;

	ScatterShotSlashCommand* slashCommand = new ScatterShotSlashCommand(slashcommand.getStringField("name"), server);
	parseSlashCommand(slashcommand, slashCommand);
	return 1;
}

int CommandConfigManager::addScriptSlashCommand(lua_State* L) {
	LuaObject slashcommand(L);
	if (!slashcommand.isValidTable())
		return 0;

	ScriptSlashCommand* slashCommand = new ScriptSlashCommand(slashcommand.getStringField("name"), server);
	parseSlashCommand(slashcommand, slashCommand);
	return 1;
}

int CommandConfigManager::addSearchCorpseSlashCommand(lua_State* L) {
	LuaObject slashcommand(L);
	if (!slashcommand.isValidTable())
		return 0;

	SearchCorpseSlashCommand* slashCommand = new SearchCorpseSlashCommand(slashcommand.getStringField("name"), server);
	parseSlashCommand(slashcommand, slashCommand);
	return 1;
}

int CommandConfigManager::addSecretSpawnSpamSlashCommand(lua_State* L) {
	LuaObject slashcommand(L);
	if (!slashcommand.isValidTable())
		return 0;

	SecretSpawnSpamSlashCommand* slashCommand = new SecretSpawnSpamSlashCommand(slashcommand.getStringField("name"), server);
	parseSlashCommand(slashcommand, slashCommand);
	return 1;
}

int CommandConfigManager::addSeGogglesSlashCommand(lua_State* L) {
	LuaObject slashcommand(L);
	if (!slashcommand.isValidTable())
		return 0;

	SeGogglesSlashCommand* slashCommand = new SeGogglesSlashCommand(slashcommand.getStringField("name"), server);
	parseSlashCommand(slashcommand, slashCommand);
	return 1;
}

int CommandConfigManager::addSelectDraftSchematicSlashCommand(lua_State* L) {
	LuaObject slashcommand(L);
	if (!slashcommand.isValidTable())
		return 0;

	SelectDraftSchematicSlashCommand* slashCommand = new SelectDraftSchematicSlashCommand(slashcommand.getStringField("name"), server);
	parseSlashCommand(slashcommand, slashCommand);
	return 1;
}

int CommandConfigManager::addSerotoninInjectionSlashCommand(lua_State* L) {
	LuaObject slashcommand(L);
	if (!slashcommand.isValidTable())
		return 0;

	SerotoninInjectionSlashCommand* slashCommand = new SerotoninInjectionSlashCommand(slashcommand.getStringField("name"), server);
	parseSlashCommand(slashcommand, slashCommand);
	return 1;
}

int CommandConfigManager::addServerSlashCommand(lua_State* L) {
	LuaObject slashcommand(L);
	if (!slashcommand.isValidTable())
		return 0;

	ServerSlashCommand* slashCommand = new ServerSlashCommand(slashcommand.getStringField("name"), server);
	parseSlashCommand(slashcommand, slashCommand);
	return 1;
}

int CommandConfigManager::addServerDestroyObjectSlashCommand(lua_State* L) {
	LuaObject slashcommand(L);
	if (!slashcommand.isValidTable())
		return 0;

	ServerDestroyObjectSlashCommand* slashCommand = new ServerDestroyObjectSlashCommand(slashcommand.getStringField("name"), server);
	parseSlashCommand(slashcommand, slashCommand);
	return 1;
}

int CommandConfigManager::addServerSysGroupSlashCommand(lua_State* L) {
	LuaObject slashcommand(L);
	if (!slashcommand.isValidTable())
		return 0;

	ServerSysGroupSlashCommand* slashCommand = new ServerSysGroupSlashCommand(slashcommand.getStringField("name"), server);
	parseSlashCommand(slashcommand, slashCommand);
	return 1;
}

int CommandConfigManager::addSetBiographySlashCommand(lua_State* L) {
	LuaObject slashcommand(L);
	if (!slashcommand.isValidTable())
		return 0;

	SetBiographySlashCommand* slashCommand = new SetBiographySlashCommand(slashcommand.getStringField("name"), server);
	parseSlashCommand(slashcommand, slashCommand);
	return 1;
}

int CommandConfigManager::addSetBiographyAdminSlashCommand(lua_State* L) {
	LuaObject slashcommand(L);
	if (!slashcommand.isValidTable())
		return 0;

	SetBiographyAdminSlashCommand* slashCommand = new SetBiographyAdminSlashCommand(slashcommand.getStringField("name"), server);
	parseSlashCommand(slashcommand, slashCommand);
	return 1;
}

int CommandConfigManager::addSetBoostmoraleSlashCommand(lua_State* L) {
	LuaObject slashcommand(L);
	if (!slashcommand.isValidTable())
		return 0;

	SetBoostmoraleSlashCommand* slashCommand = new SetBoostmoraleSlashCommand(slashcommand.getStringField("name"), server);
	parseSlashCommand(slashcommand, slashCommand);
	return 1;
}

int CommandConfigManager::addSetChargeSlashCommand(lua_State* L) {
	LuaObject slashcommand(L);
	if (!slashcommand.isValidTable())
		return 0;

	SetChargeSlashCommand* slashCommand = new SetChargeSlashCommand(slashcommand.getStringField("name"), server);
	parseSlashCommand(slashcommand, slashCommand);
	return 1;
}

int CommandConfigManager::addSetCurrentSkillTitleSlashCommand(lua_State* L) {
	LuaObject slashcommand(L);
	if (!slashcommand.isValidTable())
		return 0;

	SetCurrentSkillTitleSlashCommand* slashCommand = new SetCurrentSkillTitleSlashCommand(slashcommand.getStringField("name"), server);
	parseSlashCommand(slashcommand, slashCommand);
	return 1;
}

int CommandConfigManager::addSetExperienceSlashCommand(lua_State* L) {
	LuaObject slashcommand(L);
	if (!slashcommand.isValidTable())
		return 0;

	SetExperienceSlashCommand* slashCommand = new SetExperienceSlashCommand(slashcommand.getStringField("name"), server);
	parseSlashCommand(slashcommand, slashCommand);
	return 1;
}

int CommandConfigManager::addSetFactionSlashCommand(lua_State* L) {
	LuaObject slashcommand(L);
	if (!slashcommand.isValidTable())
		return 0;

	SetFactionSlashCommand* slashCommand = new SetFactionSlashCommand(slashcommand.getStringField("name"), server);
	parseSlashCommand(slashcommand, slashCommand);
	return 1;
}

int CommandConfigManager::addSetFactionStandingSlashCommand(lua_State* L) {
	LuaObject slashcommand(L);
	if (!slashcommand.isValidTable())
		return 0;

	SetFactionStandingSlashCommand* slashCommand = new SetFactionStandingSlashCommand(slashcommand.getStringField("name"), server);
	parseSlashCommand(slashcommand, slashCommand);
	return 1;
}

int CommandConfigManager::addSetFirstNameSlashCommand(lua_State* L) {
	LuaObject slashcommand(L);
	if (!slashcommand.isValidTable())
		return 0;

	SetFirstNameSlashCommand* slashCommand = new SetFirstNameSlashCommand(slashcommand.getStringField("name"), server);
	parseSlashCommand(slashcommand, slashCommand);
	return 1;
}

int CommandConfigManager::addSetFormupSlashCommand(lua_State* L) {
	LuaObject slashcommand(L);
	if (!slashcommand.isValidTable())
		return 0;

	SetFormupSlashCommand* slashCommand = new SetFormupSlashCommand(slashcommand.getStringField("name"), server);
	parseSlashCommand(slashcommand, slashCommand);
	return 1;
}

int CommandConfigManager::addSetGodModeSlashCommand(lua_State* L) {
	LuaObject slashcommand(L);
	if (!slashcommand.isValidTable())
		return 0;

	SetGodModeSlashCommand* slashCommand = new SetGodModeSlashCommand(slashcommand.getStringField("name"), server);
	parseSlashCommand(slashcommand, slashCommand);
	return 1;
}

int CommandConfigManager::addSetGrievousAuthorizedSlashCommand(lua_State* L) {
	LuaObject slashcommand(L);
	if (!slashcommand.isValidTable())
		return 0;

	SetGrievousAuthorizedSlashCommand* slashCommand = new SetGrievousAuthorizedSlashCommand(slashcommand.getStringField("name"), server);
	parseSlashCommand(slashcommand, slashCommand);
	return 1;
}

int CommandConfigManager::addSetHueSlashCommand(lua_State* L) {
	LuaObject slashcommand(L);
	if (!slashcommand.isValidTable())
		return 0;

	SetHueSlashCommand* slashCommand = new SetHueSlashCommand(slashcommand.getStringField("name"), server);
	parseSlashCommand(slashcommand, slashCommand);
	return 1;
}

int CommandConfigManager::addSetIntimidateSlashCommand(lua_State* L) {
	LuaObject slashcommand(L);
	if (!slashcommand.isValidTable())
		return 0;

	SetIntimidateSlashCommand* slashCommand = new SetIntimidateSlashCommand(slashcommand.getStringField("name"), server);
	parseSlashCommand(slashcommand, slashCommand);
	return 1;
}

int CommandConfigManager::addSetLastNameSlashCommand(lua_State* L) {
	LuaObject slashcommand(L);
	if (!slashcommand.isValidTable())
		return 0;

	SetLastNameSlashCommand* slashCommand = new SetLastNameSlashCommand(slashcommand.getStringField("name"), server);
	parseSlashCommand(slashcommand, slashCommand);
	return 1;
}

int CommandConfigManager::addSetLoginMessageSlashCommand(lua_State* L) {
	LuaObject slashcommand(L);
	if (!slashcommand.isValidTable())
		return 0;

	SetLoginMessageSlashCommand* slashCommand = new SetLoginMessageSlashCommand(slashcommand.getStringField("name"), server);
	parseSlashCommand(slashcommand, slashCommand);
	return 1;
}

int CommandConfigManager::addSetLoginTitleSlashCommand(lua_State* L) {
	LuaObject slashcommand(L);
	if (!slashcommand.isValidTable())
		return 0;

	SetLoginTitleSlashCommand* slashCommand = new SetLoginTitleSlashCommand(slashcommand.getStringField("name"), server);
	parseSlashCommand(slashcommand, slashCommand);
	return 1;
}

int CommandConfigManager::addSetMatchMakingCharacterIdSlashCommand(lua_State* L) {
	LuaObject slashcommand(L);
	if (!slashcommand.isValidTable())
		return 0;

	SetMatchMakingCharacterIdSlashCommand* slashCommand = new SetMatchMakingCharacterIdSlashCommand(slashcommand.getStringField("name"), server);
	parseSlashCommand(slashcommand, slashCommand);
	return 1;
}

int CommandConfigManager::addSetMatchMakingPersonalIdSlashCommand(lua_State* L) {
	LuaObject slashcommand(L);
	if (!slashcommand.isValidTable())
		return 0;

	SetMatchMakingPersonalIdSlashCommand* slashCommand = new SetMatchMakingPersonalIdSlashCommand(slashcommand.getStringField("name"), server);
	parseSlashCommand(slashcommand, slashCommand);
	return 1;
}

int CommandConfigManager::addSetMaximumSpawnTimeSlashCommand(lua_State* L) {
	LuaObject slashcommand(L);
	if (!slashcommand.isValidTable())
		return 0;

	SetMaximumSpawnTimeSlashCommand* slashCommand = new SetMaximumSpawnTimeSlashCommand(slashcommand.getStringField("name"), server);
	parseSlashCommand(slashcommand, slashCommand);
	return 1;
}

int CommandConfigManager::addSetMinimumSpawnTimeSlashCommand(lua_State* L) {
	LuaObject slashcommand(L);
	if (!slashcommand.isValidTable())
		return 0;

	SetMinimumSpawnTimeSlashCommand* slashCommand = new SetMinimumSpawnTimeSlashCommand(slashcommand.getStringField("name"), server);
	parseSlashCommand(slashcommand, slashCommand);
	return 1;
}

int CommandConfigManager::addSetMoodSlashCommand(lua_State* L) {
	LuaObject slashcommand(L);
	if (!slashcommand.isValidTable())
		return 0;

	SetMoodSlashCommand* slashCommand = new SetMoodSlashCommand(slashcommand.getStringField("name"), server);
	parseSlashCommand(slashcommand, slashCommand);
	return 1;
}

int CommandConfigManager::addSetMoodInternalSlashCommand(lua_State* L) {
	LuaObject slashcommand(L);
	if (!slashcommand.isValidTable())
		return 0;

	SetMoodInternalSlashCommand* slashCommand = new SetMoodInternalSlashCommand(slashcommand.getStringField("name"), server);
	parseSlashCommand(slashcommand, slashCommand);
	return 1;
}

int CommandConfigManager::addSetNameSlashCommand(lua_State* L) {
	LuaObject slashcommand(L);
	if (!slashcommand.isValidTable())
		return 0;

	SetNameSlashCommand* slashCommand = new SetNameSlashCommand(slashcommand.getStringField("name"), server);
	parseSlashCommand(slashcommand, slashCommand);
	return 1;
}

int CommandConfigManager::addSetOwnerSlashCommand(lua_State* L) {
	LuaObject slashcommand(L);
	if (!slashcommand.isValidTable())
		return 0;

	SetOwnerSlashCommand* slashCommand = new SetOwnerSlashCommand(slashcommand.getStringField("name"), server);
	parseSlashCommand(slashcommand, slashCommand);
	return 1;
}

int CommandConfigManager::addSetPerformanceBuffTargetSlashCommand(lua_State* L) {
	LuaObject slashcommand(L);
	if (!slashcommand.isValidTable())
		return 0;

	SetPerformanceBuffTargetSlashCommand* slashCommand = new SetPerformanceBuffTargetSlashCommand(slashcommand.getStringField("name"), server);
	parseSlashCommand(slashcommand, slashCommand);
	return 1;
}

int CommandConfigManager::addSetpermissionSlashCommand(lua_State* L) {
	LuaObject slashcommand(L);
	if (!slashcommand.isValidTable())
		return 0;

	SetpermissionSlashCommand* slashCommand = new SetpermissionSlashCommand(slashcommand.getStringField("name"), server);
	parseSlashCommand(slashcommand, slashCommand);
	return 1;
}

int CommandConfigManager::addSetPlanetLimitSlashCommand(lua_State* L) {
	LuaObject slashcommand(L);
	if (!slashcommand.isValidTable())
		return 0;

	SetPlanetLimitSlashCommand* slashCommand = new SetPlanetLimitSlashCommand(slashcommand.getStringField("name"), server);
	parseSlashCommand(slashcommand, slashCommand);
	return 1;
}

int CommandConfigManager::addSetPlayerAppearanceSlashCommand(lua_State* L) {
	LuaObject slashcommand(L);
	if (!slashcommand.isValidTable())
		return 0;

	SetPlayerAppearanceSlashCommand* slashCommand = new SetPlayerAppearanceSlashCommand(slashcommand.getStringField("name"), server);
	parseSlashCommand(slashcommand, slashCommand);
	return 1;
}

int CommandConfigManager::addSetPlayerStateSlashCommand(lua_State* L) {
	LuaObject slashcommand(L);
	if (!slashcommand.isValidTable())
		return 0;

	SetPlayerStateSlashCommand* slashCommand = new SetPlayerStateSlashCommand(slashcommand.getStringField("name"), server);
	parseSlashCommand(slashcommand, slashCommand);
	return 1;
}

int CommandConfigManager::addSetprivacySlashCommand(lua_State* L) {
	LuaObject slashcommand(L);
	if (!slashcommand.isValidTable())
		return 0;

	SetprivacySlashCommand* slashCommand = new SetprivacySlashCommand(slashcommand.getStringField("name"), server);
	parseSlashCommand(slashcommand, slashCommand);
	return 1;
}

int CommandConfigManager::addSetPublicStateSlashCommand(lua_State* L) {
	LuaObject slashcommand(L);
	if (!slashcommand.isValidTable())
		return 0;

	SetPublicStateSlashCommand* slashCommand = new SetPublicStateSlashCommand(slashcommand.getStringField("name"), server);
	parseSlashCommand(slashcommand, slashCommand);
	return 1;
}

int CommandConfigManager::addSetRankSlashCommand(lua_State* L) {
	LuaObject slashcommand(L);
	if (!slashcommand.isValidTable())
		return 0;

	SetRankSlashCommand* slashCommand = new SetRankSlashCommand(slashcommand.getStringField("name"), server);
	parseSlashCommand(slashcommand, slashCommand);
	return 1;
}

int CommandConfigManager::addSetRetreatSlashCommand(lua_State* L) {
	LuaObject slashcommand(L);
	if (!slashcommand.isValidTable())
		return 0;

	SetRetreatSlashCommand* slashCommand = new SetRetreatSlashCommand(slashcommand.getStringField("name"), server);
	parseSlashCommand(slashcommand, slashCommand);
	return 1;
}

int CommandConfigManager::addSetSpeedSlashCommand(lua_State* L) {
	LuaObject slashcommand(L);
	if (!slashcommand.isValidTable())
		return 0;

	SetSpeedSlashCommand* slashCommand = new SetSpeedSlashCommand(slashcommand.getStringField("name"), server);
	parseSlashCommand(slashcommand, slashCommand);
	return 1;
}

int CommandConfigManager::addSetSpokenLanguageSlashCommand(lua_State* L) {
	LuaObject slashcommand(L);
	if (!slashcommand.isValidTable())
		return 0;

	SetSpokenLanguageSlashCommand* slashCommand = new SetSpokenLanguageSlashCommand(slashcommand.getStringField("name"), server);
	parseSlashCommand(slashcommand, slashCommand);
	return 1;
}

int CommandConfigManager::addSetSteadyaimSlashCommand(lua_State* L) {
	LuaObject slashcommand(L);
	if (!slashcommand.isValidTable())
		return 0;

	SetSteadyaimSlashCommand* slashCommand = new SetSteadyaimSlashCommand(slashcommand.getStringField("name"), server);
	parseSlashCommand(slashcommand, slashCommand);
	return 1;
}

int CommandConfigManager::addSetTEFSlashCommand(lua_State* L) {
	LuaObject slashcommand(L);
	if (!slashcommand.isValidTable())
		return 0;

	SetTEFSlashCommand* slashCommand = new SetTEFSlashCommand(slashcommand.getStringField("name"), server);
	parseSlashCommand(slashcommand, slashCommand);
	return 1;
}

int CommandConfigManager::addSetVeteranRewardSlashCommand(lua_State* L) {
	LuaObject slashcommand(L);
	if (!slashcommand.isValidTable())
		return 0;

	SetVeteranRewardSlashCommand* slashCommand = new SetVeteranRewardSlashCommand(slashcommand.getStringField("name"), server);
	parseSlashCommand(slashcommand, slashCommand);
	return 1;
}

int CommandConfigManager::addSetWarcrySlashCommand(lua_State* L) {
	LuaObject slashcommand(L);
	if (!slashcommand.isValidTable())
		return 0;

	SetWarcrySlashCommand* slashCommand = new SetWarcrySlashCommand(slashcommand.getStringField("name"), server);
	parseSlashCommand(slashcommand, slashCommand);
	return 1;
}

int CommandConfigManager::addSetWaypointActiveStatusSlashCommand(lua_State* L) {
	LuaObject slashcommand(L);
	if (!slashcommand.isValidTable())
		return 0;

	SetWaypointActiveStatusSlashCommand* slashCommand = new SetWaypointActiveStatusSlashCommand(slashcommand.getStringField("name"), server);
	parseSlashCommand(slashcommand, slashCommand);
	return 1;
}

int CommandConfigManager::addSetWaypointNameSlashCommand(lua_State* L) {
	LuaObject slashcommand(L);
	if (!slashcommand.isValidTable())
		return 0;

	SetWaypointNameSlashCommand* slashCommand = new SetWaypointNameSlashCommand(slashcommand.getStringField("name"), server);
	parseSlashCommand(slashcommand, slashCommand);
	return 1;
}

int CommandConfigManager::addShockSlashCommand(lua_State* L) {
	LuaObject slashcommand(L);
	if (!slashcommand.isValidTable())
		return 0;

	ShockSlashCommand* slashCommand = new ShockSlashCommand(slashcommand.getStringField("name"), server);
	parseSlashCommand(slashcommand, slashCommand);
	return 1;
}

int CommandConfigManager::addShowCouncilRankSlashCommand(lua_State* L) {
	LuaObject slashcommand(L);
	if (!slashcommand.isValidTable())
		return 0;

	ShowCouncilRankSlashCommand* slashCommand = new ShowCouncilRankSlashCommand(slashcommand.getStringField("name"), server);
	parseSlashCommand(slashcommand, slashCommand);
	return 1;
}

int CommandConfigManager::addShowDanceVisualsSlashCommand(lua_State* L) {
	LuaObject slashcommand(L);
	if (!slashcommand.isValidTable())
		return 0;

	ShowDanceVisualsSlashCommand* slashCommand = new ShowDanceVisualsSlashCommand(slashcommand.getStringField("name"), server);
	parseSlashCommand(slashcommand, slashCommand);
	return 1;
}

int CommandConfigManager::addShowFactionInformationSlashCommand(lua_State* L) {
	LuaObject slashcommand(L);
	if (!slashcommand.isValidTable())
		return 0;

	ShowFactionInformationSlashCommand* slashCommand = new ShowFactionInformationSlashCommand(slashcommand.getStringField("name"), server);
	parseSlashCommand(slashcommand, slashCommand);
	return 1;
}

int CommandConfigManager::addShowMusicianVisualsSlashCommand(lua_State* L) {
	LuaObject slashcommand(L);
	if (!slashcommand.isValidTable())
		return 0;

	ShowMusicianVisualsSlashCommand* slashCommand = new ShowMusicianVisualsSlashCommand(slashcommand.getStringField("name"), server);
	parseSlashCommand(slashcommand, slashCommand);
	return 1;
}

int CommandConfigManager::addShowPvPRatingSlashCommand(lua_State* L) {
	LuaObject slashcommand(L);
	if (!slashcommand.isValidTable())
		return 0;

	ShowPvPRatingSlashCommand* slashCommand = new ShowPvPRatingSlashCommand(slashcommand.getStringField("name"), server);
	parseSlashCommand(slashcommand, slashCommand);
	return 1;
}

int CommandConfigManager::addShowSpawnRegionSlashCommand(lua_State* L) {
	LuaObject slashcommand(L);
	if (!slashcommand.isValidTable())
		return 0;

	ShowSpawnRegionSlashCommand* slashCommand = new ShowSpawnRegionSlashCommand(slashcommand.getStringField("name"), server);
	parseSlashCommand(slashcommand, slashCommand);
	return 1;
}

int CommandConfigManager::addSitServerSlashCommand(lua_State* L) {
	LuaObject slashcommand(L);
	if (!slashcommand.isValidTable())
		return 0;

	SitServerSlashCommand* slashCommand = new SitServerSlashCommand(slashcommand.getStringField("name"), server);
	parseSlashCommand(slashcommand, slashCommand);
	return 1;
}

int CommandConfigManager::addSkillSlashCommand(lua_State* L) {
	LuaObject slashcommand(L);
	if (!slashcommand.isValidTable())
		return 0;

	SkillSlashCommand* slashCommand = new SkillSlashCommand(slashcommand.getStringField("name"), server);
	parseSlashCommand(slashcommand, slashCommand);
	return 1;
}

int CommandConfigManager::addSmokebombSlashCommand(lua_State* L) {
	LuaObject slashcommand(L);
	if (!slashcommand.isValidTable())
		return 0;

	SmokebombSlashCommand* slashCommand = new SmokebombSlashCommand(slashcommand.getStringField("name"), server);
	parseSlashCommand(slashcommand, slashCommand);
	return 1;
}

int CommandConfigManager::addSniperShotSlashCommand(lua_State* L) {
	LuaObject slashcommand(L);
	if (!slashcommand.isValidTable())
		return 0;

	SniperShotSlashCommand* slashCommand = new SniperShotSlashCommand(slashcommand.getStringField("name"), server);
	parseSlashCommand(slashcommand, slashCommand);
	return 1;
}

int CommandConfigManager::addSnoopSlashCommand(lua_State* L) {
	LuaObject slashcommand(L);
	if (!slashcommand.isValidTable())
		return 0;

	SnoopSlashCommand* slashCommand = new SnoopSlashCommand(slashcommand.getStringField("name"), server);
	parseSlashCommand(slashcommand, slashCommand);
	return 1;
}

int CommandConfigManager::addSocialSlashCommand(lua_State* L) {
	LuaObject slashcommand(L);
	if (!slashcommand.isValidTable())
		return 0;

	SocialSlashCommand* slashCommand = new SocialSlashCommand(slashcommand.getStringField("name"), server);
	parseSlashCommand(slashcommand, slashCommand);
	return 1;
}

int CommandConfigManager::addSocialInternalSlashCommand(lua_State* L) {
	LuaObject slashcommand(L);
	if (!slashcommand.isValidTable())
		return 0;

	SocialInternalSlashCommand* slashCommand = new SocialInternalSlashCommand(slashcommand.getStringField("name"), server);
	parseSlashCommand(slashcommand, slashCommand);
	return 1;
}

int CommandConfigManager::addSpatialChatSlashCommand(lua_State* L) {
	LuaObject slashcommand(L);
	if (!slashcommand.isValidTable())
		return 0;

	SpatialChatSlashCommand* slashCommand = new SpatialChatSlashCommand(slashcommand.getStringField("name"), server);
	parseSlashCommand(slashcommand, slashCommand);
	return 1;
}

int CommandConfigManager::addSpatialChatInternalSlashCommand(lua_State* L) {
	LuaObject slashcommand(L);
	if (!slashcommand.isValidTable())
		return 0;

	SpatialChatInternalSlashCommand* slashCommand = new SpatialChatInternalSlashCommand(slashcommand.getStringField("name"), server);
	parseSlashCommand(slashcommand, slashCommand);
	return 1;
}

int CommandConfigManager::addSpawnStatusSlashCommand(lua_State* L) {
	LuaObject slashcommand(L);
	if (!slashcommand.isValidTable())
		return 0;

	SpawnStatusSlashCommand* slashCommand = new SpawnStatusSlashCommand(slashcommand.getStringField("name"), server);
	parseSlashCommand(slashcommand, slashCommand);
	return 1;
}

int CommandConfigManager::addSpinAttackSlashCommand(lua_State* L) {
	LuaObject slashcommand(L);
	if (!slashcommand.isValidTable())
		return 0;

	SpinAttackSlashCommand* slashCommand = new SpinAttackSlashCommand(slashcommand.getStringField("name"), server);
	parseSlashCommand(slashcommand, slashCommand);
	return 1;
}

int CommandConfigManager::addSplitCreditsWithGroupSlashCommand(lua_State* L) {
	LuaObject slashcommand(L);
	if (!slashcommand.isValidTable())
		return 0;

	SplitCreditsWithGroupSlashCommand* slashCommand = new SplitCreditsWithGroupSlashCommand(slashcommand.getStringField("name"), server);
	parseSlashCommand(slashcommand, slashCommand);
	return 1;
}

int CommandConfigManager::addSpotlightSlashCommand(lua_State* L) {
	LuaObject slashcommand(L);
	if (!slashcommand.isValidTable())
		return 0;

	SpotlightSlashCommand* slashCommand = new SpotlightSlashCommand(slashcommand.getStringField("name"), server);
	parseSlashCommand(slashcommand, slashCommand);
	return 1;
}

int CommandConfigManager::addSprayShotSlashCommand(lua_State* L) {
	LuaObject slashcommand(L);
	if (!slashcommand.isValidTable())
		return 0;

	SprayShotSlashCommand* slashCommand = new SprayShotSlashCommand(slashcommand.getStringField("name"), server);
	parseSlashCommand(slashcommand, slashCommand);
	return 1;
}

int CommandConfigManager::addStabilizersSlashCommand(lua_State* L) {
	LuaObject slashcommand(L);
	if (!slashcommand.isValidTable())
		return 0;

	StabilizersSlashCommand* slashCommand = new StabilizersSlashCommand(slashcommand.getStringField("name"), server);
	parseSlashCommand(slashcommand, slashCommand);
	return 1;
}

int CommandConfigManager::addStandSlashCommand(lua_State* L) {
	LuaObject slashcommand(L);
	if (!slashcommand.isValidTable())
		return 0;

	StandSlashCommand* slashCommand = new StandSlashCommand(slashcommand.getStringField("name"), server);
	parseSlashCommand(slashcommand, slashCommand);
	return 1;
}

int CommandConfigManager::addStartBandSlashCommand(lua_State* L) {
	LuaObject slashcommand(L);
	if (!slashcommand.isValidTable())
		return 0;

	StartBandSlashCommand* slashCommand = new StartBandSlashCommand(slashcommand.getStringField("name"), server);
	parseSlashCommand(slashcommand, slashCommand);
	return 1;
}

int CommandConfigManager::addStartCitySpawnerSlashCommand(lua_State* L) {
	LuaObject slashcommand(L);
	if (!slashcommand.isValidTable())
		return 0;

	StartCitySpawnerSlashCommand* slashCommand = new StartCitySpawnerSlashCommand(slashcommand.getStringField("name"), server);
	parseSlashCommand(slashcommand, slashCommand);
	return 1;
}

int CommandConfigManager::addStartDanceSlashCommand(lua_State* L) {
	LuaObject slashcommand(L);
	if (!slashcommand.isValidTable())
		return 0;

	StartDanceSlashCommand* slashCommand = new StartDanceSlashCommand(slashcommand.getStringField("name"), server);
	parseSlashCommand(slashcommand, slashCommand);
	return 1;
}

int CommandConfigManager::addStartleShotSlashCommand(lua_State* L) {
	LuaObject slashcommand(L);
	if (!slashcommand.isValidTable())
		return 0;

	StartleShotSlashCommand* slashCommand = new StartleShotSlashCommand(slashcommand.getStringField("name"), server);
	parseSlashCommand(slashcommand, slashCommand);
	return 1;
}

int CommandConfigManager::addStartMusicSlashCommand(lua_State* L) {
	LuaObject slashcommand(L);
	if (!slashcommand.isValidTable())
		return 0;

	StartMusicSlashCommand* slashCommand = new StartMusicSlashCommand(slashcommand.getStringField("name"), server);
	parseSlashCommand(slashcommand, slashCommand);
	return 1;
}

int CommandConfigManager::addStartSpawnerSlashCommand(lua_State* L) {
	LuaObject slashcommand(L);
	if (!slashcommand.isValidTable())
		return 0;

	StartSpawnerSlashCommand* slashCommand = new StartSpawnerSlashCommand(slashcommand.getStringField("name"), server);
	parseSlashCommand(slashcommand, slashCommand);
	return 1;
}

int CommandConfigManager::addStartTargetSpawnerSlashCommand(lua_State* L) {
	LuaObject slashcommand(L);
	if (!slashcommand.isValidTable())
		return 0;

	StartTargetSpawnerSlashCommand* slashCommand = new StartTargetSpawnerSlashCommand(slashcommand.getStringField("name"), server);
	parseSlashCommand(slashcommand, slashCommand);
	return 1;
}

int CommandConfigManager::addStartTraceLoggingSlashCommand(lua_State* L) {
	LuaObject slashcommand(L);
	if (!slashcommand.isValidTable())
		return 0;

	StartTraceLoggingSlashCommand* slashCommand = new StartTraceLoggingSlashCommand(slashcommand.getStringField("name"), server);
	parseSlashCommand(slashcommand, slashCommand);
	return 1;
}

int CommandConfigManager::addStasisSlashCommand(lua_State* L) {
	LuaObject slashcommand(L);
	if (!slashcommand.isValidTable())
		return 0;

	StasisSlashCommand* slashCommand = new StasisSlashCommand(slashcommand.getStringField("name"), server);
	parseSlashCommand(slashcommand, slashCommand);
	return 1;
}

int CommandConfigManager::addStatSlashCommand(lua_State* L) {
	LuaObject slashcommand(L);
	if (!slashcommand.isValidTable())
		return 0;

	StatSlashCommand* slashCommand = new StatSlashCommand(slashcommand.getStringField("name"), server);
	parseSlashCommand(slashcommand, slashCommand);
	return 1;
}

int CommandConfigManager::addSteadyaimSlashCommand(lua_State* L) {
	LuaObject slashcommand(L);
	if (!slashcommand.isValidTable())
		return 0;

	SteadyaimSlashCommand* slashCommand = new SteadyaimSlashCommand(slashcommand.getStringField("name"), server);
	parseSlashCommand(slashcommand, slashCommand);
	return 1;
}

int CommandConfigManager::addStopBandSlashCommand(lua_State* L) {
	LuaObject slashcommand(L);
	if (!slashcommand.isValidTable())
		return 0;

	StopBandSlashCommand* slashCommand = new StopBandSlashCommand(slashcommand.getStringField("name"), server);
	parseSlashCommand(slashcommand, slashCommand);
	return 1;
}

int CommandConfigManager::addStopBleedingSlashCommand(lua_State* L) {
	LuaObject slashcommand(L);
	if (!slashcommand.isValidTable())
		return 0;

	StopBleedingSlashCommand* slashCommand = new StopBleedingSlashCommand(slashcommand.getStringField("name"), server);
	parseSlashCommand(slashcommand, slashCommand);
	return 1;
}

int CommandConfigManager::addStopCitySpawnerSlashCommand(lua_State* L) {
	LuaObject slashcommand(L);
	if (!slashcommand.isValidTable())
		return 0;

	StopCitySpawnerSlashCommand* slashCommand = new StopCitySpawnerSlashCommand(slashcommand.getStringField("name"), server);
	parseSlashCommand(slashcommand, slashCommand);
	return 1;
}

int CommandConfigManager::addStopCraftingSessionSlashCommand(lua_State* L) {
	LuaObject slashcommand(L);
	if (!slashcommand.isValidTable())
		return 0;

	StopCraftingSessionSlashCommand* slashCommand = new StopCraftingSessionSlashCommand(slashcommand.getStringField("name"), server);
	parseSlashCommand(slashcommand, slashCommand);
	return 1;
}

int CommandConfigManager::addStopDanceSlashCommand(lua_State* L) {
	LuaObject slashcommand(L);
	if (!slashcommand.isValidTable())
		return 0;

	StopDanceSlashCommand* slashCommand = new StopDanceSlashCommand(slashcommand.getStringField("name"), server);
	parseSlashCommand(slashcommand, slashCommand);
	return 1;
}

int CommandConfigManager::addStoplisteningSlashCommand(lua_State* L) {
	LuaObject slashcommand(L);
	if (!slashcommand.isValidTable())
		return 0;

	StoplisteningSlashCommand* slashCommand = new StoplisteningSlashCommand(slashcommand.getStringField("name"), server);
	parseSlashCommand(slashcommand, slashCommand);
	return 1;
}

int CommandConfigManager::addStopMusicSlashCommand(lua_State* L) {
	LuaObject slashcommand(L);
	if (!slashcommand.isValidTable())
		return 0;

	StopMusicSlashCommand* slashCommand = new StopMusicSlashCommand(slashcommand.getStringField("name"), server);
	parseSlashCommand(slashcommand, slashCommand);
	return 1;
}

int CommandConfigManager::addStoppingShotSlashCommand(lua_State* L) {
	LuaObject slashcommand(L);
	if (!slashcommand.isValidTable())
		return 0;

	StoppingShotSlashCommand* slashCommand = new StoppingShotSlashCommand(slashcommand.getStringField("name"), server);
	parseSlashCommand(slashcommand, slashCommand);
	return 1;
}

int CommandConfigManager::addStopSpawnerSlashCommand(lua_State* L) {
	LuaObject slashcommand(L);
	if (!slashcommand.isValidTable())
		return 0;

	StopSpawnerSlashCommand* slashCommand = new StopSpawnerSlashCommand(slashcommand.getStringField("name"), server);
	parseSlashCommand(slashcommand, slashCommand);
	return 1;
}

int CommandConfigManager::addStopTargetSpawnerSlashCommand(lua_State* L) {
	LuaObject slashcommand(L);
	if (!slashcommand.isValidTable())
		return 0;

	StopTargetSpawnerSlashCommand* slashCommand = new StopTargetSpawnerSlashCommand(slashcommand.getStringField("name"), server);
	parseSlashCommand(slashcommand, slashCommand);
	return 1;
}

int CommandConfigManager::addStopTraceLoggingSlashCommand(lua_State* L) {
	LuaObject slashcommand(L);
	if (!slashcommand.isValidTable())
		return 0;

	StopTraceLoggingSlashCommand* slashCommand = new StopTraceLoggingSlashCommand(slashcommand.getStringField("name"), server);
	parseSlashCommand(slashcommand, slashCommand);
	return 1;
}

int CommandConfigManager::addStopwatchingSlashCommand(lua_State* L) {
	LuaObject slashcommand(L);
	if (!slashcommand.isValidTable())
		return 0;

	StopwatchingSlashCommand* slashCommand = new StopwatchingSlashCommand(slashcommand.getStringField("name"), server);
	parseSlashCommand(slashcommand, slashCommand);
	return 1;
}

int CommandConfigManager::addStructurestatusSlashCommand(lua_State* L) {
	LuaObject slashcommand(L);
	if (!slashcommand.isValidTable())
		return 0;

	StructurestatusSlashCommand* slashCommand = new StructurestatusSlashCommand(slashcommand.getStringField("name"), server);
	parseSlashCommand(slashcommand, slashCommand);
	return 1;
}

int CommandConfigManager::addStunningBlowSlashCommand(lua_State* L) {
	LuaObject slashcommand(L);
	if (!slashcommand.isValidTable())
		return 0;

	StunningBlowSlashCommand* slashCommand = new StunningBlowSlashCommand(slashcommand.getStringField("name"), server);
	parseSlashCommand(slashcommand, slashCommand);
	return 1;
}

int CommandConfigManager::addStunRecoverySlashCommand(lua_State* L) {
	LuaObject slashcommand(L);
	if (!slashcommand.isValidTable())
		return 0;

	StunRecoverySlashCommand* slashCommand = new StunRecoverySlashCommand(slashcommand.getStringField("name"), server);
	parseSlashCommand(slashcommand, slashCommand);
	return 1;
}

int CommandConfigManager::addSuppressionFireSlashCommand(lua_State* L) {
	LuaObject slashcommand(L);
	if (!slashcommand.isValidTable())
		return 0;

	SuppressionFireSlashCommand* slashCommand = new SuppressionFireSlashCommand(slashcommand.getStringField("name"), server);
	parseSlashCommand(slashcommand, slashCommand);
	return 1;
}

int CommandConfigManager::addSurrenderSkillSlashCommand(lua_State* L) {
	LuaObject slashcommand(L);
	if (!slashcommand.isValidTable())
		return 0;

	SurrenderSkillSlashCommand* slashCommand = new SurrenderSkillSlashCommand(slashcommand.getStringField("name"), server);
	parseSlashCommand(slashcommand, slashCommand);
	return 1;
}

int CommandConfigManager::addSurveySlashCommand(lua_State* L) {
	LuaObject slashcommand(L);
	if (!slashcommand.isValidTable())
		return 0;

	SurveySlashCommand* slashCommand = new SurveySlashCommand(slashcommand.getStringField("name"), server);
	parseSlashCommand(slashcommand, slashCommand);
	return 1;
}

int CommandConfigManager::addSweepAttackSlashCommand(lua_State* L) {
	LuaObject slashcommand(L);
	if (!slashcommand.isValidTable())
		return 0;

	SweepAttackSlashCommand* slashCommand = new SweepAttackSlashCommand(slashcommand.getStringField("name"), server);
	parseSlashCommand(slashcommand, slashCommand);
	return 1;
}

int CommandConfigManager::addSwitchWeaponModeSlashCommand(lua_State* L) {
	LuaObject slashcommand(L);
	if (!slashcommand.isValidTable())
		return 0;

	SwitchWeaponModeSlashCommand* slashCommand = new SwitchWeaponModeSlashCommand(slashcommand.getStringField("name"), server);
	parseSlashCommand(slashcommand, slashCommand);
	return 1;
}

int CommandConfigManager::addSwordFlurrySlashCommand(lua_State* L) {
	LuaObject slashcommand(L);
	if (!slashcommand.isValidTable())
		return 0;

	SwordFlurrySlashCommand* slashCommand = new SwordFlurrySlashCommand(slashcommand.getStringField("name"), server);
	parseSlashCommand(slashcommand, slashCommand);
	return 1;
}

int CommandConfigManager::addSynchronizedUiListenSlashCommand(lua_State* L) {
	LuaObject slashcommand(L);
	if (!slashcommand.isValidTable())
		return 0;

	SynchronizedUiListenSlashCommand* slashCommand = new SynchronizedUiListenSlashCommand(slashcommand.getStringField("name"), server);
	parseSlashCommand(slashcommand, slashCommand);
	return 1;
}

int CommandConfigManager::addSynchronizedUiStopListeningSlashCommand(lua_State* L) {
	LuaObject slashcommand(L);
	if (!slashcommand.isValidTable())
		return 0;

	SynchronizedUiStopListeningSlashCommand* slashCommand = new SynchronizedUiStopListeningSlashCommand(slashcommand.getStringField("name"), server);
	parseSlashCommand(slashcommand, slashCommand);
	return 1;
}

int CommandConfigManager::addSystemMessageSlashCommand(lua_State* L) {
	LuaObject slashcommand(L);
	if (!slashcommand.isValidTable())
		return 0;

	SystemMessageSlashCommand* slashCommand = new SystemMessageSlashCommand(slashcommand.getStringField("name"), server);
	parseSlashCommand(slashcommand, slashCommand);
	return 1;
}

int CommandConfigManager::addTakeCoverSlashCommand(lua_State* L) {
	LuaObject slashcommand(L);
	if (!slashcommand.isValidTable())
		return 0;

	TakeCoverSlashCommand* slashCommand = new TakeCoverSlashCommand(slashcommand.getStringField("name"), server);
	parseSlashCommand(slashcommand, slashCommand);
	return 1;
}

int CommandConfigManager::addTameSlashCommand(lua_State* L) {
	LuaObject slashcommand(L);
	if (!slashcommand.isValidTable())
		return 0;

	TameSlashCommand* slashCommand = new TameSlashCommand(slashcommand.getStringField("name"), server);
	parseSlashCommand(slashcommand, slashCommand);
	return 1;
}

int CommandConfigManager::addTargetSlashCommand(lua_State* L) {
	LuaObject slashcommand(L);
	if (!slashcommand.isValidTable())
		return 0;

	TargetSlashCommand* slashCommand = new TargetSlashCommand(slashcommand.getStringField("name"), server);
	parseSlashCommand(slashcommand, slashCommand);
	return 1;
}

int CommandConfigManager::addTauntSlashCommand(lua_State* L) {
	LuaObject slashcommand(L);
	if (!slashcommand.isValidTable())
		return 0;

	TauntSlashCommand* slashCommand = new TauntSlashCommand(slashcommand.getStringField("name"), server);
	parseSlashCommand(slashcommand, slashCommand);
	return 1;
}

int CommandConfigManager::addTeachSlashCommand(lua_State* L) {
	LuaObject slashcommand(L);
	if (!slashcommand.isValidTable())
		return 0;

	TeachSlashCommand* slashCommand = new TeachSlashCommand(slashcommand.getStringField("name"), server);
	parseSlashCommand(slashcommand, slashCommand);
	return 1;
}

int CommandConfigManager::addTeleportSlashCommand(lua_State* L) {
	LuaObject slashcommand(L);
	if (!slashcommand.isValidTable())
		return 0;

	TeleportSlashCommand* slashCommand = new TeleportSlashCommand(slashcommand.getStringField("name"), server);
	parseSlashCommand(slashcommand, slashCommand);
	return 1;
}

int CommandConfigManager::addTeleportTargetSlashCommand(lua_State* L) {
	LuaObject slashcommand(L);
	if (!slashcommand.isValidTable())
		return 0;

	TeleportTargetSlashCommand* slashCommand = new TeleportTargetSlashCommand(slashcommand.getStringField("name"), server);
	parseSlashCommand(slashcommand, slashCommand);
	return 1;
}

int CommandConfigManager::addTeleportToSlashCommand(lua_State* L) {
	LuaObject slashcommand(L);
	if (!slashcommand.isValidTable())
		return 0;

	TeleportToSlashCommand* slashCommand = new TeleportToSlashCommand(slashcommand.getStringField("name"), server);
	parseSlashCommand(slashcommand, slashCommand);
	return 1;
}

int CommandConfigManager::addTellpetSlashCommand(lua_State* L) {
	LuaObject slashcommand(L);
	if (!slashcommand.isValidTable())
		return 0;

	TellpetSlashCommand* slashCommand = new TellpetSlashCommand(slashcommand.getStringField("name"), server);
	parseSlashCommand(slashcommand, slashCommand);
	return 1;
}

int CommandConfigManager::addThrowGrenadeSlashCommand(lua_State* L) {
	LuaObject slashcommand(L);
	if (!slashcommand.isValidTable())
		return 0;

	ThrowGrenadeSlashCommand* slashCommand = new ThrowGrenadeSlashCommand(slashcommand.getStringField("name"), server);
	parseSlashCommand(slashcommand, slashCommand);
	return 1;
}

int CommandConfigManager::addThrowTrapSlashCommand(lua_State* L) {
	LuaObject slashcommand(L);
	if (!slashcommand.isValidTable())
		return 0;

	ThrowTrapSlashCommand* slashCommand = new ThrowTrapSlashCommand(slashcommand.getStringField("name"), server);
	parseSlashCommand(slashcommand, slashCommand);
	return 1;
}

int CommandConfigManager::addThyroidRuptureSlashCommand(lua_State* L) {
	LuaObject slashcommand(L);
	if (!slashcommand.isValidTable())
		return 0;

	ThyroidRuptureSlashCommand* slashCommand = new ThyroidRuptureSlashCommand(slashcommand.getStringField("name"), server);
	parseSlashCommand(slashcommand, slashCommand);
	return 1;
}

int CommandConfigManager::addTipSlashCommand(lua_State* L) {
	LuaObject slashcommand(L);
	if (!slashcommand.isValidTable())
		return 0;

	TipSlashCommand* slashCommand = new TipSlashCommand(slashcommand.getStringField("name"), server);
	parseSlashCommand(slashcommand, slashCommand);
	return 1;
}

int CommandConfigManager::addToggleAwayFromKeyBoardSlashCommand(lua_State* L) {
	LuaObject slashcommand(L);
	if (!slashcommand.isValidTable())
		return 0;

	ToggleAwayFromKeyBoardSlashCommand* slashCommand = new ToggleAwayFromKeyBoardSlashCommand(slashcommand.getStringField("name"), server);
	parseSlashCommand(slashcommand, slashCommand);
	return 1;
}

int CommandConfigManager::addToggleCombatTauntsSlashCommand(lua_State* L) {
	LuaObject slashcommand(L);
	if (!slashcommand.isValidTable())
		return 0;

	ToggleCombatTauntsSlashCommand* slashCommand = new ToggleCombatTauntsSlashCommand(slashcommand.getStringField("name"), server);
	parseSlashCommand(slashcommand, slashCommand);
	return 1;
}

int CommandConfigManager::addToggleDisplayingFactionRankSlashCommand(lua_State* L) {
	LuaObject slashcommand(L);
	if (!slashcommand.isValidTable())
		return 0;

	ToggleDisplayingFactionRankSlashCommand* slashCommand = new ToggleDisplayingFactionRankSlashCommand(slashcommand.getStringField("name"), server);
	parseSlashCommand(slashcommand, slashCommand);
	return 1;
}

int CommandConfigManager::addTorsoShotSlashCommand(lua_State* L) {
	LuaObject slashcommand(L);
	if (!slashcommand.isValidTable())
		return 0;

	TorsoShotSlashCommand* slashCommand = new TorsoShotSlashCommand(slashcommand.getStringField("name"), server);
	parseSlashCommand(slashcommand, slashCommand);
	return 1;
}

int CommandConfigManager::addTotalHealSlashCommand(lua_State* L) {
	LuaObject slashcommand(L);
	if (!slashcommand.isValidTable())
		return 0;

	TotalHealSlashCommand* slashCommand = new TotalHealSlashCommand(slashcommand.getStringField("name"), server);
	parseSlashCommand(slashcommand, slashCommand);
	return 1;
}

int CommandConfigManager::addTransferForceSlashCommand(lua_State* L) {
	LuaObject slashcommand(L);
	if (!slashcommand.isValidTable())
		return 0;

	TransferForceSlashCommand* slashCommand = new TransferForceSlashCommand(slashcommand.getStringField("name"), server);
	parseSlashCommand(slashcommand, slashCommand);
	return 1;
}

int CommandConfigManager::addTransferItemSlashCommand(lua_State* L) {
	LuaObject slashcommand(L);
	if (!slashcommand.isValidTable())
		return 0;

	TransferItemSlashCommand* slashCommand = new TransferItemSlashCommand(slashcommand.getStringField("name"), server);
	parseSlashCommand(slashcommand, slashCommand);
	return 1;
}

int CommandConfigManager::addTransferItemArmorSlashCommand(lua_State* L) {
	LuaObject slashcommand(L);
	if (!slashcommand.isValidTable())
		return 0;

	TransferItemArmorSlashCommand* slashCommand = new TransferItemArmorSlashCommand(slashcommand.getStringField("name"), server);
	parseSlashCommand(slashcommand, slashCommand);
	return 1;
}

int CommandConfigManager::addTransferItemMiscSlashCommand(lua_State* L) {
	LuaObject slashcommand(L);
	if (!slashcommand.isValidTable())
		return 0;

	TransferItemMiscSlashCommand* slashCommand = new TransferItemMiscSlashCommand(slashcommand.getStringField("name"), server);
	parseSlashCommand(slashcommand, slashCommand);
	return 1;
}

int CommandConfigManager::addTransferItemWeaponSlashCommand(lua_State* L) {
	LuaObject slashcommand(L);
	if (!slashcommand.isValidTable())
		return 0;

	TransferItemWeaponSlashCommand* slashCommand = new TransferItemWeaponSlashCommand(slashcommand.getStringField("name"), server);
	parseSlashCommand(slashcommand, slashCommand);
	return 1;
}

int CommandConfigManager::addTransferstructureSlashCommand(lua_State* L) {
	LuaObject slashcommand(L);
	if (!slashcommand.isValidTable())
		return 0;

	TransferstructureSlashCommand* slashCommand = new TransferstructureSlashCommand(slashcommand.getStringField("name"), server);
	parseSlashCommand(slashcommand, slashCommand);
	return 1;
}

int CommandConfigManager::addTraumatizeSlashCommand(lua_State* L) {
	LuaObject slashcommand(L);
	if (!slashcommand.isValidTable())
		return 0;

	TraumatizeSlashCommand* slashCommand = new TraumatizeSlashCommand(slashcommand.getStringField("name"), server);
	parseSlashCommand(slashcommand, slashCommand);
	return 1;
}

int CommandConfigManager::addUnassociateDroidControlDeviceWithShipSlashCommand(lua_State* L) {
	LuaObject slashcommand(L);
	if (!slashcommand.isValidTable())
		return 0;

	UnassociateDroidControlDeviceWithShipSlashCommand* slashCommand = new UnassociateDroidControlDeviceWithShipSlashCommand(slashcommand.getStringField("name"), server);
	parseSlashCommand(slashcommand, slashCommand);
	return 1;
}

int CommandConfigManager::addUnCityBanSlashCommand(lua_State* L) {
	LuaObject slashcommand(L);
	if (!slashcommand.isValidTable())
		return 0;

	UnCityBanSlashCommand* slashCommand = new UnCityBanSlashCommand(slashcommand.getStringField("name"), server);
	parseSlashCommand(slashcommand, slashCommand);
	return 1;
}

int CommandConfigManager::addUnconsentSlashCommand(lua_State* L) {
	LuaObject slashcommand(L);
	if (!slashcommand.isValidTable())
		return 0;

	UnconsentSlashCommand* slashCommand = new UnconsentSlashCommand(slashcommand.getStringField("name"), server);
	parseSlashCommand(slashcommand, slashCommand);
	return 1;
}

int CommandConfigManager::addUnderhandShotSlashCommand(lua_State* L) {
	LuaObject slashcommand(L);
	if (!slashcommand.isValidTable())
		return 0;

	UnderhandShotSlashCommand* slashCommand = new UnderhandShotSlashCommand(slashcommand.getStringField("name"), server);
	parseSlashCommand(slashcommand, slashCommand);
	return 1;
}

int CommandConfigManager::addUnfreezePlayerSlashCommand(lua_State* L) {
	LuaObject slashcommand(L);
	if (!slashcommand.isValidTable())
		return 0;

	UnfreezePlayerSlashCommand* slashCommand = new UnfreezePlayerSlashCommand(slashcommand.getStringField("name"), server);
	parseSlashCommand(slashcommand, slashCommand);
	return 1;
}

int CommandConfigManager::addUninstallShipComponentSlashCommand(lua_State* L) {
	LuaObject slashcommand(L);
	if (!slashcommand.isValidTable())
		return 0;

	UninstallShipComponentSlashCommand* slashCommand = new UninstallShipComponentSlashCommand(slashcommand.getStringField("name"), server);
	parseSlashCommand(slashcommand, slashCommand);
	return 1;
}

int CommandConfigManager::addUninviteSlashCommand(lua_State* L) {
	LuaObject slashcommand(L);
	if (!slashcommand.isValidTable())
		return 0;

	UninviteSlashCommand* slashCommand = new UninviteSlashCommand(slashcommand.getStringField("name"), server);
	parseSlashCommand(slashcommand, slashCommand);
	return 1;
}

int CommandConfigManager::addUnsnoopSlashCommand(lua_State* L) {
	LuaObject slashcommand(L);
	if (!slashcommand.isValidTable())
		return 0;

	UnsnoopSlashCommand* slashCommand = new UnsnoopSlashCommand(slashcommand.getStringField("name"), server);
	parseSlashCommand(slashcommand, slashCommand);
	return 1;
}

int CommandConfigManager::addUseDoctorBagSlashCommand(lua_State* L) {
	LuaObject slashcommand(L);
	if (!slashcommand.isValidTable())
		return 0;

	UseDoctorBagSlashCommand* slashCommand = new UseDoctorBagSlashCommand(slashcommand.getStringField("name"), server);
	parseSlashCommand(slashcommand, slashCommand);
	return 1;
}

int CommandConfigManager::addUseReconDroneSlashCommand(lua_State* L) {
	LuaObject slashcommand(L);
	if (!slashcommand.isValidTable())
		return 0;

	UseReconDroneSlashCommand* slashCommand = new UseReconDroneSlashCommand(slashcommand.getStringField("name"), server);
	parseSlashCommand(slashcommand, slashCommand);
	return 1;
}

int CommandConfigManager::addUseSkillBuffSlashCommand(lua_State* L) {
	LuaObject slashcommand(L);
	if (!slashcommand.isValidTable())
		return 0;

	UseSkillBuffSlashCommand* slashCommand = new UseSkillBuffSlashCommand(slashcommand.getStringField("name"), server);
	parseSlashCommand(slashcommand, slashCommand);
	return 1;
}

int CommandConfigManager::addVentriloquismSlashCommand(lua_State* L) {
	LuaObject slashcommand(L);
	if (!slashcommand.isValidTable())
		return 0;

	VentriloquismSlashCommand* slashCommand = new VentriloquismSlashCommand(slashcommand.getStringField("name"), server);
	parseSlashCommand(slashcommand, slashCommand);
	return 1;
}

int CommandConfigManager::addVertFurnitureSlashCommand(lua_State* L) {
	LuaObject slashcommand(L);
	if (!slashcommand.isValidTable())
		return 0;

	VertFurnitureSlashCommand* slashCommand = new VertFurnitureSlashCommand(slashcommand.getStringField("name"), server);
	parseSlashCommand(slashcommand, slashCommand);
	return 1;
}

int CommandConfigManager::addVitalizeSlashCommand(lua_State* L) {
	LuaObject slashcommand(L);
	if (!slashcommand.isValidTable())
		return 0;

	VitalizeSlashCommand* slashCommand = new VitalizeSlashCommand(slashcommand.getStringField("name"), server);
	parseSlashCommand(slashcommand, slashCommand);
	return 1;
}

int CommandConfigManager::addVolleyFireSlashCommand(lua_State* L) {
	LuaObject slashcommand(L);
	if (!slashcommand.isValidTable())
		return 0;

	VolleyFireSlashCommand* slashCommand = new VolleyFireSlashCommand(slashcommand.getStringField("name"), server);
	parseSlashCommand(slashcommand, slashCommand);
	return 1;
}

int CommandConfigManager::addVolleyFireAttackSlashCommand(lua_State* L) {
	LuaObject slashcommand(L);
	if (!slashcommand.isValidTable())
		return 0;

	VolleyFireAttackSlashCommand* slashCommand = new VolleyFireAttackSlashCommand(slashcommand.getStringField("name"), server);
	parseSlashCommand(slashcommand, slashCommand);
	return 1;
}

int CommandConfigManager::addWarcrySlashCommand(lua_State* L) {
	LuaObject slashcommand(L);
	if (!slashcommand.isValidTable())
		return 0;

	WarcrySlashCommand* slashCommand = new WarcrySlashCommand(slashcommand.getStringField("name"), server);
	parseSlashCommand(slashcommand, slashCommand);
	return 1;
}

int CommandConfigManager::addWarningShotSlashCommand(lua_State* L) {
	LuaObject slashcommand(L);
	if (!slashcommand.isValidTable())
		return 0;

	WarningShotSlashCommand* slashCommand = new WarningShotSlashCommand(slashcommand.getStringField("name"), server);
	parseSlashCommand(slashcommand, slashCommand);
	return 1;
}

int CommandConfigManager::addWatchSlashCommand(lua_State* L) {
	LuaObject slashcommand(L);
	if (!slashcommand.isValidTable())
		return 0;

	WatchSlashCommand* slashCommand = new WatchSlashCommand(slashcommand.getStringField("name"), server);
	parseSlashCommand(slashcommand, slashCommand);
	return 1;
}

int CommandConfigManager::addWaypointSlashCommand(lua_State* L) {
	LuaObject slashcommand(L);
	if (!slashcommand.isValidTable())
		return 0;

	WaypointSlashCommand* slashCommand = new WaypointSlashCommand(slashcommand.getStringField("name"), server);
	parseSlashCommand(slashcommand, slashCommand);
	return 1;
}

int CommandConfigManager::addWipeItemsSlashCommand(lua_State* L) {
	LuaObject slashcommand(L);
	if (!slashcommand.isValidTable())
		return 0;

	WipeItemsSlashCommand* slashCommand = new WipeItemsSlashCommand(slashcommand.getStringField("name"), server);
	parseSlashCommand(slashcommand, slashCommand);
	return 1;
}

int CommandConfigManager::addWookieeRoarSlashCommand(lua_State* L) {
	LuaObject slashcommand(L);
	if (!slashcommand.isValidTable())
		return 0;

	WookieeRoarSlashCommand* slashCommand = new WookieeRoarSlashCommand(slashcommand.getStringField("name"), server);
	parseSlashCommand(slashcommand, slashCommand);
	return 1;
}

/*
int CommandConfigManager::addOpenContainerSlashCommand(lua_State* L) {
	LuaObject slashcommand(L);
	if (!slashcommand.isValidTable())
		return 0;

	String commandname = slashcommand.getStringField("name");
	OpenContainerSlashCommand* slashCommand = new OpenContainerSlashCommand(commandname, server);

	parseOptions(L, slashCommand);

	String alternativeNames = slashcommand.getStringField("alternativeNames");

	slashCommands->put(slashCommand);

	if (!alternativeNames.isEmpty())
		parseAlternativeNames(alternativeNames, slashCommand);

	return 1;
}

int CommandConfigManager::addGroupSaySlashCommand(lua_State* L) {
	LuaObject slashcommand(L);
	if (!slashcommand.isValidTable())
		return 0;

	String commandname = slashcommand.getStringField("name");
	GroupSaySlashCommand* slashCommand = new GroupSaySlashCommand(commandname, server);

	parseOptions(L, slashCommand);

	String alternativeNames = slashcommand.getStringField("alternativeNames");

	slashCommands->put(slashCommand);

	if (!alternativeNames.isEmpty())
		parseAlternativeNames(alternativeNames, slashCommand);

	return 1;
}
*/
