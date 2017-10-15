#include "CommandConfigManager.h"

#include "server/zone/objects/creature/CreatureObject.h"
#include "server/zone/objects/creature/ai/Creature.h"
#include "server/zone/objects/player/sessions/crafting/CraftingSession.h"

#include "server/zone/objects/guild/GuildObject.h"

#include "server/zone/objects/region/CityRegion.h"

#include "server/zone/managers/player/PlayerManager.h"
#include "server/zone/managers/resource/ResourceManager.h"
#include "server/zone/managers/creature/PetManager.h"
#include "server/zone/managers/structure/StructureManager.h"
#include "server/zone/managers/group/GroupManager.h"
#include "server/zone/managers/collision/CollisionManager.h"
#include "server/zone/managers/combat/CombatManager.h"

#include "server/zone/objects/group/GroupObject.h"

#include "server/login/account/Account.h"

#include "server/zone/ZoneProcessServer.h"
#include "server/zone/ZoneServer.h"
#include "server/zone/Zone.h"

#include "server/zone/objects/creature/commands/JediQueueCommand.h"

#include "server/zone/objects/creature/commands/ActionShot1Command.h"
#include "server/zone/objects/creature/commands/ActionShot2Command.h"
#include "server/zone/objects/creature/commands/ActivateCloneCommand.h"
#include "server/zone/objects/creature/commands/ActivateQuestCommand.h"
#include "server/zone/objects/creature/commands/AddAllowedPlayerCommand.h"
#include "server/zone/objects/creature/commands/AddBannedPlayerCommand.h"
#include "server/zone/objects/creature/commands/AddFriendCommand.h"
#include "server/zone/objects/creature/commands/AddIgnoreCommand.h"
#include "server/zone/objects/creature/commands/AddMapLocationCommand.h"
#include "server/zone/objects/creature/commands/AddPowerCommand.h"
#include "server/zone/objects/creature/commands/AdminCommand.h"
#include "server/zone/objects/creature/commands/AdjustLotCountCommand.h"
#include "server/zone/objects/creature/commands/AiIgnoreCommand.h"
#include "server/zone/objects/creature/commands/AimCommand.h"
#include "server/zone/objects/creature/commands/AlertCommand.h"
#include "server/zone/objects/creature/commands/AnimalAttackCommand.h"
#include "server/zone/objects/creature/commands/AnimalCalmCommand.h"
#include "server/zone/objects/creature/commands/AnimalScareCommand.h"
#include "server/zone/objects/creature/commands/AnonCommand.h"
#include "server/zone/objects/creature/commands/ApplyDiseaseCommand.h"
#include "server/zone/objects/creature/commands/ApplyPoisonCommand.h"
#include "server/zone/objects/creature/commands/ApplyPowerupCommand.h"
#include "server/zone/objects/creature/commands/AreatrackCommand.h"
#include "server/zone/objects/creature/commands/AssignDroidCommand.h"
#include "server/zone/objects/creature/commands/AssistCommand.h"
#include "server/zone/objects/creature/commands/AssociateDroidControlDeviceWithShipCommand.h"
#include "server/zone/objects/creature/commands/AttackCommand.h"
#include "server/zone/objects/creature/commands/AuctionCommand.h"
#include "server/zone/objects/creature/commands/AuctionAcceptCommand.h"
#include "server/zone/objects/creature/commands/AuctionBidCommand.h"
#include "server/zone/objects/creature/commands/AuctionCancelCommand.h"
#include "server/zone/objects/creature/commands/AuctionCreateCommand.h"
#include "server/zone/objects/creature/commands/AuctionQueryCommand.h"
#include "server/zone/objects/creature/commands/AuctionRetrieveCommand.h"
#include "server/zone/objects/creature/commands/AuctionsayCommand.h"
#include "server/zone/objects/creature/commands/AvoidIncapacitationCommand.h"
#include "server/zone/objects/creature/commands/BandFlourishCommand.h"
#include "server/zone/objects/creature/commands/BattlefieldStatusCommand.h"
#include "server/zone/objects/creature/commands/Berserk1Command.h"
#include "server/zone/objects/creature/commands/Berserk2Command.h"
#include "server/zone/objects/creature/commands/BetCommand.h"
#include "server/zone/objects/creature/commands/BleedingShotCommand.h"
#include "server/zone/objects/creature/commands/BlindAttackCommand.h"
#include "server/zone/objects/creature/commands/BoardShuttleCommand.h"
#include "server/zone/objects/creature/commands/BodyShot1Command.h"
#include "server/zone/objects/creature/commands/BodyShot2Command.h"
#include "server/zone/objects/creature/commands/BodyShot3Command.h"
#include "server/zone/objects/creature/commands/BoostmoraleCommand.h"
#include "server/zone/objects/creature/commands/BroadcastCommand.h"
#include "server/zone/objects/creature/commands/BroadcastAreaCommand.h"
#include "server/zone/objects/creature/commands/BroadcastGalaxyCommand.h"
#include "server/zone/objects/creature/commands/BroadcastPlanetCommand.h"
#include "server/zone/objects/creature/commands/BurstRunCommand.h"
#include "server/zone/objects/creature/commands/BurstShot1Command.h"
#include "server/zone/objects/creature/commands/BurstShot2Command.h"
#include "server/zone/objects/creature/commands/CancelCraftingSessionCommand.h"
#include "server/zone/objects/creature/commands/CenterOfBeingCommand.h"
#include "server/zone/objects/creature/commands/ChangeBandMusicCommand.h"
#include "server/zone/objects/creature/commands/ChangeDanceCommand.h"
#include "server/zone/objects/creature/commands/ChangeMusicCommand.h"
#include "server/zone/objects/creature/commands/ChannelForceCommand.h"
#include "server/zone/objects/creature/commands/ChargeShot1Command.h"
#include "server/zone/objects/creature/commands/ChargeShot2Command.h"
#include "server/zone/objects/creature/commands/CheckForceStatusCommand.h"
#include "server/zone/objects/creature/commands/CitybanCommand.h"
#include "server/zone/objects/creature/commands/CitypardonCommand.h"
#include "server/zone/objects/creature/commands/ClaimVeteranRewardCommand.h"
#include "server/zone/objects/creature/commands/ClearCompletedQuestCommand.h"
#include "server/zone/objects/creature/commands/ClearVeteranRewardCommand.h"
#include "server/zone/objects/creature/commands/ClientQualifiedForSkillCommand.h"
#include "server/zone/objects/creature/commands/CloneCommand.h"
#include "server/zone/objects/creature/commands/CloseContainerCommand.h"
#include "server/zone/objects/creature/commands/CloseLotteryContainerCommand.h"
#include "server/zone/objects/creature/commands/ColorlightsCommand.h"
#include "server/zone/objects/creature/commands/CombatCommand.h"
#include "server/zone/objects/creature/commands/CombatEscapeCommand.h"
#include "server/zone/objects/creature/commands/CombatModeCheckCommand.h"
#include "server/zone/objects/creature/commands/CombatSpamCommand.h"
#include "server/zone/objects/creature/commands/CombatTargetCommand.h"
#include "server/zone/objects/creature/commands/CompleteQuestCommand.h"
#include "server/zone/objects/creature/commands/ConcealCommand.h"
#include "server/zone/objects/creature/commands/ConcealShotCommand.h"
#include "server/zone/objects/creature/commands/ConfusionShotCommand.h"
#include "server/zone/objects/creature/commands/ConsentCommand.h"
#include "server/zone/objects/creature/commands/CorpseCommand.h"
#include "server/zone/objects/creature/commands/CounterAttackCommand.h"
#include "server/zone/objects/creature/commands/CoupDeGraceCommand.h"
#include "server/zone/objects/creature/commands/CraftCommand.h"
#include "server/zone/objects/creature/commands/CreateCreatureCommand.h"
#include "server/zone/objects/creature/commands/CreateManfSchematicCommand.h"
#include "server/zone/objects/creature/commands/CreateMissionElementCommand.h"
#include "server/zone/objects/creature/commands/CreateNPCCommand.h"
#include "server/zone/objects/creature/commands/CreatePrototypeCommand.h"
#include "server/zone/objects/creature/commands/CreateSpawningElementCommand.h"
#include "server/zone/objects/creature/commands/CreateSpawningElementWithDifficultyCommand.h"
#include "server/zone/objects/creature/commands/CreatureAreaAttackCommand.h"
#include "server/zone/objects/creature/commands/CreatureAreaBleedingCommand.h"
#include "server/zone/objects/creature/commands/CreatureAreaComboCommand.h"
#include "server/zone/objects/creature/commands/CreatureAreaDiseaseCommand.h"
#include "server/zone/objects/creature/commands/CreatureAreaKnockdownCommand.h"
#include "server/zone/objects/creature/commands/CreatureAreaPoisonCommand.h"
#include "server/zone/objects/creature/commands/CreatureRangedAttackCommand.h"
#include "server/zone/objects/creature/commands/CreditsCommand.h"
#include "server/zone/objects/creature/commands/CripplingShotCommand.h"
#include "server/zone/objects/creature/commands/CsAppendCommentCommand.h"
#include "server/zone/objects/creature/commands/CsCancelTicketCommand.h"
#include "server/zone/objects/creature/commands/CsConnectPlayerCommand.h"
#include "server/zone/objects/creature/commands/CsCreateTicketCommand.h"
#include "server/zone/objects/creature/commands/CsDisconnectPlayerCommand.h"
#include "server/zone/objects/creature/commands/CsGetArticleCommand.h"
#include "server/zone/objects/creature/commands/CsGetCommentsCommand.h"
#include "server/zone/objects/creature/commands/CsGetTicketsCommand.h"
#include "server/zone/objects/creature/commands/CsRequestCategoriesCommand.h"
#include "server/zone/objects/creature/commands/CsSearchKnowledgeBaseCommand.h"
#include "server/zone/objects/creature/commands/CuiConsentResponseCommand.h"
#include "server/zone/objects/creature/commands/CureDiseaseCommand.h"
#include "server/zone/objects/creature/commands/CurePoisonCommand.h"
#include "server/zone/objects/creature/commands/CustomizeDroidCommand.h"
#include "server/zone/objects/creature/commands/CustomizeVehicleCommand.h"
#include "server/zone/objects/creature/commands/DatabaseCommand.h"
#include "server/zone/objects/creature/commands/DazzleCommand.h"
#include "server/zone/objects/creature/commands/DeactivateQuestCommand.h"
#include "server/zone/objects/creature/commands/DeathBlowCommand.h"
#include "server/zone/objects/creature/commands/DeathCountCommand.h"
#include "server/zone/objects/creature/commands/DeclareOvertCommand.h"
#include "server/zone/objects/creature/commands/DeclareresidenceCommand.h"
#include "server/zone/objects/creature/commands/DeclineCommand.h"
#include "server/zone/objects/creature/commands/DefaultAttackCommand.h"
#include "server/zone/objects/creature/commands/DefaultDroidAttackCommand.h"
#include "server/zone/objects/creature/commands/DefuseMinefieldCommand.h"
#include "server/zone/objects/creature/commands/DelegateFactionPointsCommand.h"
#include "server/zone/objects/creature/commands/DenyServiceCommand.h"
#include "server/zone/objects/creature/commands/DeployTrapCommand.h"
#include "server/zone/objects/creature/commands/DestroyCommand.h"
#include "server/zone/objects/creature/commands/DestroystructureCommand.h"
#include "server/zone/objects/creature/commands/DetonateDroidCommand.h"
#include "server/zone/objects/creature/commands/DiagnoseCommand.h"
#include "server/zone/objects/creature/commands/DisarmingShot1Command.h"
#include "server/zone/objects/creature/commands/DisarmingShot2Command.h"
#include "server/zone/objects/creature/commands/DisbandCommand.h"
#include "server/zone/objects/creature/commands/DismissGroupMemberCommand.h"
#include "server/zone/objects/creature/commands/DismountCommand.h"
#include "server/zone/objects/creature/commands/DismountandstoreCommand.h"
#include "server/zone/objects/creature/commands/DistractCommand.h"
#include "server/zone/objects/creature/commands/DiveShotCommand.h"
#include "server/zone/objects/creature/commands/DizzyAttackCommand.h"
#include "server/zone/objects/creature/commands/DoubleTapCommand.h"
#include "server/zone/objects/creature/commands/DragIncapacitatedPlayerCommand.h"
#include "server/zone/objects/creature/commands/DrainForceCommand.h"
#include "server/zone/objects/creature/commands/DuelCommand.h"
#include "server/zone/objects/creature/commands/DumpTargetInformationCommand.h"
#include "server/zone/objects/creature/commands/DumpZoneInformationCommand.h"
#include "server/zone/objects/creature/commands/EatCommand.h"
#include "server/zone/objects/creature/commands/EditAppearanceCommand.h"
#include "server/zone/objects/creature/commands/EditBankCommand.h"
#include "server/zone/objects/creature/commands/EditBankAccountCommand.h"
#include "server/zone/objects/creature/commands/EditStatsCommand.h"
#include "server/zone/objects/creature/commands/EmboldenpetsCommand.h"
#include "server/zone/objects/creature/commands/EmptyMailTargetCommand.h"
#include "server/zone/objects/creature/commands/EndDuelCommand.h"
#include "server/zone/objects/creature/commands/EnragepetsCommand.h"
#include "server/zone/objects/creature/commands/EquilibriumCommand.h"
#include "server/zone/objects/creature/commands/ExecuteKnowledgeBaseMessageCommand.h"
#include "server/zone/objects/creature/commands/ExtinguishFireCommand.h"
#include "server/zone/objects/creature/commands/ExtractObjectCommand.h"
#include "server/zone/objects/creature/commands/EyeShotCommand.h"
#include "server/zone/objects/creature/commands/FactoryCrateSplitCommand.h"
#include "server/zone/objects/creature/commands/FanShotCommand.h"
#include "server/zone/objects/creature/commands/FastBlastCommand.h"
#include "server/zone/objects/creature/commands/FeignDeathCommand.h"
#include "server/zone/objects/creature/commands/FindCommand.h"
#include "server/zone/objects/creature/commands/FindFriendCommand.h"
#include "server/zone/objects/creature/commands/FindMyTrainerCommand.h"
#include "server/zone/objects/creature/commands/FindObjectCommand.h"
#include "server/zone/objects/creature/commands/FindPlayerCommand.h"
#include "server/zone/objects/creature/commands/FireAcidCone1Command.h"
#include "server/zone/objects/creature/commands/FireAcidCone2Command.h"
#include "server/zone/objects/creature/commands/FireAcidSingle1Command.h"
#include "server/zone/objects/creature/commands/FireAcidSingle2Command.h"
#include "server/zone/objects/creature/commands/FireHeavyWeaponCommand.h"
#include "server/zone/objects/creature/commands/FirejetCommand.h"
#include "server/zone/objects/creature/commands/FireLightningCone1Command.h"
#include "server/zone/objects/creature/commands/FireLightningCone2Command.h"
#include "server/zone/objects/creature/commands/FireLightningSingle1Command.h"
#include "server/zone/objects/creature/commands/FireLightningSingle2Command.h"
#include "server/zone/objects/creature/commands/FirstAidCommand.h"
#include "server/zone/objects/creature/commands/FishCommand.h"
#include "server/zone/objects/creature/commands/FlameCone1Command.h"
#include "server/zone/objects/creature/commands/FlameCone2Command.h"
#include "server/zone/objects/creature/commands/FlameSingle1Command.h"
#include "server/zone/objects/creature/commands/FlameSingle2Command.h"
#include "server/zone/objects/creature/commands/FlashSpeederCommand.h"
#include "server/zone/objects/creature/commands/FlourishCommand.h"
#include "server/zone/objects/creature/commands/FlurryShot1Command.h"
#include "server/zone/objects/creature/commands/FlurryShot2Command.h"
#include "server/zone/objects/creature/commands/FlushingShot1Command.h"
#include "server/zone/objects/creature/commands/FlushingShot2Command.h"
#include "server/zone/objects/creature/commands/ForageCommand.h"
#include "server/zone/objects/creature/commands/ForceAbsorb1Command.h"
#include "server/zone/objects/creature/commands/ForceAbsorb2Command.h"
#include "server/zone/objects/creature/commands/ForceArmor1Command.h"
#include "server/zone/objects/creature/commands/ForceArmor2Command.h"
#include "server/zone/objects/creature/commands/ForceChokeCommand.h"
#include "server/zone/objects/creature/commands/ForceCommandCommand.h"
#include "server/zone/objects/creature/commands/ForceCureDiseaseCommand.h"
#include "server/zone/objects/creature/commands/ForceCurePoisonCommand.h"
#include "server/zone/objects/creature/commands/ForceFeedback1Command.h"
#include "server/zone/objects/creature/commands/ForceFeedback2Command.h"
#include "server/zone/objects/creature/commands/ForceIntimidate1Command.h"
#include "server/zone/objects/creature/commands/ForceIntimidate2Command.h"
#include "server/zone/objects/creature/commands/ForceKnockdown1Command.h"
#include "server/zone/objects/creature/commands/ForceKnockdown2Command.h"
#include "server/zone/objects/creature/commands/ForceKnockdown3Command.h"
#include "server/zone/objects/creature/commands/ForceLightningCone1Command.h"
#include "server/zone/objects/creature/commands/ForceLightningCone2Command.h"
#include "server/zone/objects/creature/commands/ForceLightningSingle1Command.h"
#include "server/zone/objects/creature/commands/ForceLightningSingle2Command.h"
#include "server/zone/objects/creature/commands/ForceMeditateCommand.h"
#include "server/zone/objects/creature/commands/ForceOfWillCommand.h"
#include "server/zone/objects/creature/commands/ForceProtectionCommand.h"
#include "server/zone/objects/creature/commands/ForceResistBleedingCommand.h"
#include "server/zone/objects/creature/commands/ForceResistDiseaseCommand.h"
#include "server/zone/objects/creature/commands/ForceResistPoisonCommand.h"
#include "server/zone/objects/creature/commands/ForceResistStatesCommand.h"
#include "server/zone/objects/creature/commands/ForceRun1Command.h"
#include "server/zone/objects/creature/commands/ForceRun2Command.h"
#include "server/zone/objects/creature/commands/ForceRun3Command.h"
#include "server/zone/objects/creature/commands/ForceShield1Command.h"
#include "server/zone/objects/creature/commands/ForceShield2Command.h"
#include "server/zone/objects/creature/commands/ForceSpeed1Command.h"
#include "server/zone/objects/creature/commands/ForceSpeed2Command.h"
#include "server/zone/objects/creature/commands/ForceThrow1Command.h"
#include "server/zone/objects/creature/commands/ForceThrow2Command.h"
#include "server/zone/objects/creature/commands/ForceWeaken1Command.h"
#include "server/zone/objects/creature/commands/ForceWeaken2Command.h"
#include "server/zone/objects/creature/commands/FormupCommand.h"
#include "server/zone/objects/creature/commands/FreezePlayerCommand.h"
#include "server/zone/objects/creature/commands/FullAutoArea1Command.h"
#include "server/zone/objects/creature/commands/FullAutoArea2Command.h"
#include "server/zone/objects/creature/commands/FullAutoSingle1Command.h"
#include "server/zone/objects/creature/commands/FullAutoSingle2Command.h"
#include "server/zone/objects/creature/commands/GallopCommand.h"
#include "server/zone/objects/creature/commands/GallopStopCommand.h"
#include "server/zone/objects/creature/commands/GcCommand.h"
#include "server/zone/objects/creature/commands/GcwStatusCommand.h"
#include "server/zone/objects/creature/commands/GenerateCraftedItemCommand.h"
#include "server/zone/objects/creature/commands/GetAccountInfoCommand.h"
#include "server/zone/objects/creature/commands/GetAttributesCommand.h"
#include "server/zone/objects/creature/commands/GetAttributesBatchCommand.h"
#include "server/zone/objects/creature/commands/GetFriendListCommand.h"
#include "server/zone/objects/creature/commands/GetGameTimeCommand.h"
#include "server/zone/objects/creature/commands/GetIgnoreListCommand.h"
#include "server/zone/objects/creature/commands/GetMapLocationsCommand.h"
#include "server/zone/objects/creature/commands/GetObjVarsCommand.h"
#include "server/zone/objects/creature/commands/GetPlayerIdCommand.h"
#include "server/zone/objects/creature/commands/GetPrototypeCommand.h"
#include "server/zone/objects/creature/commands/GetRankCommand.h"
#include "server/zone/objects/creature/commands/GetSpawnDelaysCommand.h"
#include "server/zone/objects/creature/commands/GetStationNameCommand.h"
#include "server/zone/objects/creature/commands/GetVeteranRewardTimeCommand.h"
#include "server/zone/objects/creature/commands/GetVeteranRewardTimeCsCommand.h"
#include "server/zone/objects/creature/commands/GiveItemCommand.h"
#include "server/zone/objects/creature/commands/GiveMaintenanceToVendorCommand.h"
#include "server/zone/objects/creature/commands/GivevendormaintCommand.h"
#include "server/zone/objects/creature/commands/GmForceCommandCommand.h"
#include "server/zone/objects/creature/commands/GmCreateClassResourceCommand.h"
#include "server/zone/objects/creature/commands/GmCreateSpecificResourceCommand.h"
#include "server/zone/objects/creature/commands/GmForceRankCommand.h"
#include "server/zone/objects/creature/commands/GmFsVillageCommand.h"
#include "server/zone/objects/creature/commands/GmJediStateCommand.h"
#include "server/zone/objects/creature/commands/GmReviveCommand.h"
#include "server/zone/objects/creature/commands/GotoCommand.h"
#include "server/zone/objects/creature/commands/GrantBadgeCommand.h"
#include "server/zone/objects/creature/commands/GrantPadawanTrialsEligibilityCommand.h"
#include "server/zone/objects/creature/commands/GrantSkillCommand.h"
#include "server/zone/objects/creature/commands/GrantTitleCommand.h"
#include "server/zone/objects/creature/commands/GrantZoningRightsCommand.h"
#include "server/zone/objects/creature/commands/GroupChatCommand.h"
#include "server/zone/objects/creature/commands/GroupLootCommand.h"
#include "server/zone/objects/creature/commands/GuildCommand.h"
#include "server/zone/objects/creature/commands/GuildremoveCommand.h"
#include "server/zone/objects/creature/commands/GuildstatusCommand.h"
#include "server/zone/objects/creature/commands/HarmfulCommand.h"
#include "server/zone/objects/creature/commands/HarmlessCommand.h"
#include "server/zone/objects/creature/commands/HarvestCorpseCommand.h"
#include "server/zone/objects/creature/commands/HarvesterActivateCommand.h"
#include "server/zone/objects/creature/commands/HarvesterDeactivateCommand.h"
#include "server/zone/objects/creature/commands/HarvesterDiscardHopperCommand.h"
#include "server/zone/objects/creature/commands/HarvesterGetResourceDataCommand.h"
#include "server/zone/objects/creature/commands/HarvesterHarvestCommand.h"
#include "server/zone/objects/creature/commands/HarvesterMakeCrateCommand.h"
#include "server/zone/objects/creature/commands/HarvesterSelectResourceCommand.h"
#include "server/zone/objects/creature/commands/HarvesterTakeSurvey Command.h"
#include "server/zone/objects/creature/commands/HasVeteranRewardCommand.h"
#include "server/zone/objects/creature/commands/HaveconsentCommand.h"
#include "server/zone/objects/creature/commands/HeadShot1Command.h"
#include "server/zone/objects/creature/commands/HeadShot2Command.h"
#include "server/zone/objects/creature/commands/HeadShot3Command.h"
#include "server/zone/objects/creature/commands/HealActionSelf1Command.h"
#include "server/zone/objects/creature/commands/HealActionSelf2Command.h"
#include "server/zone/objects/creature/commands/HealActionWoundOther1Command.h"
#include "server/zone/objects/creature/commands/HealActionWoundOther2Command.h"
#include "server/zone/objects/creature/commands/HealActionWoundSelf1Command.h"
#include "server/zone/objects/creature/commands/HealActionWoundSelf2Command.h"
#include "server/zone/objects/creature/commands/HealAllOther1Command.h"
#include "server/zone/objects/creature/commands/HealAllOther2Command.h"
#include "server/zone/objects/creature/commands/HealAllSelf1Command.h"
#include "server/zone/objects/creature/commands/HealAllSelf2Command.h"
#include "server/zone/objects/creature/commands/HealBattleFatigueOther1Command.h"
#include "server/zone/objects/creature/commands/HealBattleFatigueOther2Command.h"
#include "server/zone/objects/creature/commands/HealBattleFatigueSelf1Command.h"
#include "server/zone/objects/creature/commands/HealBattleFatigueSelf2Command.h"
#include "server/zone/objects/creature/commands/HealDamageCommand.h"
#include "server/zone/objects/creature/commands/HealDroidDamageCommand.h"
#include "server/zone/objects/creature/commands/HealDroidWoundCommand.h"
#include "server/zone/objects/creature/commands/HealEnhanceCommand.h"
#include "server/zone/objects/creature/commands/HealHealthSelf1Command.h"
#include "server/zone/objects/creature/commands/HealHealthSelf2Command.h"
#include "server/zone/objects/creature/commands/HealHealthWoundOther1Command.h"
#include "server/zone/objects/creature/commands/HealHealthWoundOther2Command.h"
#include "server/zone/objects/creature/commands/HealHealthWoundSelf1Command.h"
#include "server/zone/objects/creature/commands/HealHealthWoundSelf2Command.h"
#include "server/zone/objects/creature/commands/HealMindCommand.h"
#include "server/zone/objects/creature/commands/HealMindSelf1Command.h"
#include "server/zone/objects/creature/commands/HealMindSelf2Command.h"
#include "server/zone/objects/creature/commands/HealMindWoundOther1Command.h"
#include "server/zone/objects/creature/commands/HealMindWoundOther2Command.h"
#include "server/zone/objects/creature/commands/HealMindWoundSelf1Command.h"
#include "server/zone/objects/creature/commands/HealMindWoundSelf2Command.h"
#include "server/zone/objects/creature/commands/HealPetCommand.h"
#include "server/zone/objects/creature/commands/HealStateCommand.h"
#include "server/zone/objects/creature/commands/HealStatesOtherCommand.h"
#include "server/zone/objects/creature/commands/HealStatesSelfCommand.h"
#include "server/zone/objects/creature/commands/HealthShot1Command.h"
#include "server/zone/objects/creature/commands/HealthShot2Command.h"
#include "server/zone/objects/creature/commands/HealWoundCommand.h"
#include "server/zone/objects/creature/commands/HoloEmoteCommand.h"
#include "server/zone/objects/creature/commands/ImagedesignCommand.h"
#include "server/zone/objects/creature/commands/InitializeComponentCommand.h"
#include "server/zone/objects/creature/commands/InnateCommand.h"
#include "server/zone/objects/creature/commands/InsertItemIntoShipComponentSlotCommand.h"
#include "server/zone/objects/creature/commands/InstallMissionTerminalCommand.h"
#include "server/zone/objects/creature/commands/InstallShipComponentCommand.h"
#include "server/zone/objects/creature/commands/InsureCommand.h"
#include "server/zone/objects/creature/commands/Intimidate1Command.h"
#include "server/zone/objects/creature/commands/Intimidate2Command.h"
#include "server/zone/objects/creature/commands/IntimidationAttackCommand.h"
#include "server/zone/objects/creature/commands/InviteCommand.h"
#include "server/zone/objects/creature/commands/InvulnerableCommand.h"
#include "server/zone/objects/creature/commands/ItemmovebackCommand.h"
#include "server/zone/objects/creature/commands/ItemmovedownCommand.h"
#include "server/zone/objects/creature/commands/ItemmoveforwardCommand.h"
#include "server/zone/objects/creature/commands/ItemmoveupCommand.h"
#include "server/zone/objects/creature/commands/ItemrotateleftCommand.h"
#include "server/zone/objects/creature/commands/ItemrotaterightCommand.h"
#include "server/zone/objects/creature/commands/JediMindTrickCommand.h"
#include "server/zone/objects/creature/commands/JoinCommand.h"
#include "server/zone/objects/creature/commands/JoinGameCommand.h"
#include "server/zone/objects/creature/commands/KickCommand.h"
#include "server/zone/objects/creature/commands/KillCommand.h"
#include "server/zone/objects/creature/commands/KillPlayerCommand.h"
#include "server/zone/objects/creature/commands/KipUpShotCommand.h"
#include "server/zone/objects/creature/commands/KneelCommand.h"
#include "server/zone/objects/creature/commands/KnockdownAttackCommand.h"
#include "server/zone/objects/creature/commands/KnockdownFireCommand.h"
#include "server/zone/objects/creature/commands/LagCommand.h"
#include "server/zone/objects/creature/commands/LastDitchCommand.h"
#include "server/zone/objects/creature/commands/LaunchFireworkCommand.h"
#include "server/zone/objects/creature/commands/LeaveGameCommand.h"
#include "server/zone/objects/creature/commands/LeaveGroupCommand.h"
#include "server/zone/objects/creature/commands/LegShot1Command.h"
#include "server/zone/objects/creature/commands/LegShot2Command.h"
#include "server/zone/objects/creature/commands/LegShot3Command.h"
#include "server/zone/objects/creature/commands/LfgCommand.h"
#include "server/zone/objects/creature/commands/ListActiveQuestsCommand.h"
#include "server/zone/objects/creature/commands/ListCompletedQuestsCommand.h"
#include "server/zone/objects/creature/commands/ListenCommand.h"
#include "server/zone/objects/creature/commands/ListGuildsCommand.h"
#include "server/zone/objects/creature/commands/LogoutCommand.h"
#include "server/zone/objects/creature/commands/LogoutServerCommand.h"
#include "server/zone/objects/creature/commands/LootCommand.h"
#include "server/zone/objects/creature/commands/LootAiCorpseCommand.h"
#include "server/zone/objects/creature/commands/LootPlayerCorpseCommand.h"
#include "server/zone/objects/creature/commands/LowBlowCommand.h"
#include "server/zone/objects/creature/commands/MakeLeaderCommand.h"
#include "server/zone/objects/creature/commands/MakeMasterLooterCommand.h"
#include "server/zone/objects/creature/commands/MakeSurveyCommand.h"
#include "server/zone/objects/creature/commands/ManufactureCommand.h"
#include "server/zone/objects/creature/commands/MaskscentCommand.h"
#include "server/zone/objects/creature/commands/MaxCombatAbilityCommand.h"
#include "server/zone/objects/creature/commands/MaxStatsCommand.h"
#include "server/zone/objects/creature/commands/MedicalForageCommand.h"
#include "server/zone/objects/creature/commands/MeditateCommand.h"
#include "server/zone/objects/creature/commands/MediumDiseaseCommand.h"
#include "server/zone/objects/creature/commands/MediumPoisonCommand.h"
#include "server/zone/objects/creature/commands/MildDiseaseCommand.h"
#include "server/zone/objects/creature/commands/MildPoisonCommand.h"
#include "server/zone/objects/creature/commands/StrongPoisonCommand.h"
#include "server/zone/objects/creature/commands/StrongDiseaseCommand.h"

using namespace server::zone::managers::objectcontroller::command;

void CommandConfigManager::registerCommands2() {
	commandFactory.registerCommand<ActionShot1Command>(String("actionShot1").toLowerCase());
	commandFactory.registerCommand<ActionShot2Command>(String("actionShot2").toLowerCase());
	commandFactory.registerCommand<ActivateCloneCommand>(String("activateClone").toLowerCase());
	commandFactory.registerCommand<ActivateQuestCommand>(String("activateQuest").toLowerCase());
	commandFactory.registerCommand<AddAllowedPlayerCommand>(String("addAllowedPlayer").toLowerCase());
	commandFactory.registerCommand<AddBannedPlayerCommand>(String("addBannedPlayer").toLowerCase());
	commandFactory.registerCommand<AddFriendCommand>(String("addFriend").toLowerCase());
	commandFactory.registerCommand<AddIgnoreCommand>(String("addIgnore").toLowerCase());
	commandFactory.registerCommand<AddMapLocationCommand>(String("addMapLocation").toLowerCase());
	commandFactory.registerCommand<AddPowerCommand>(String("addPower").toLowerCase());
	commandFactory.registerCommand<AdjustLotCountCommand>(String("adjustLotCount").toLowerCase());
	commandFactory.registerCommand<AiIgnoreCommand>(String("aiIgnore").toLowerCase());
	commandFactory.registerCommand<AimCommand>(String("aim").toLowerCase());
	commandFactory.registerCommand<AlertCommand>(String("alert").toLowerCase());
	commandFactory.registerCommand<AnimalAttackCommand>(String("animalAttack").toLowerCase());
	commandFactory.registerCommand<AnimalCalmCommand>(String("animalCalm").toLowerCase());
	commandFactory.registerCommand<AnimalScareCommand>(String("animalScare").toLowerCase());
	commandFactory.registerCommand<AnonCommand>(String("anon").toLowerCase());
	commandFactory.registerCommand<ApplyDiseaseCommand>(String("applyDisease").toLowerCase());
	commandFactory.registerCommand<ApplyPoisonCommand>(String("applyPoison").toLowerCase());
	commandFactory.registerCommand<ApplyPowerupCommand>(String("applyPowerup").toLowerCase());
	commandFactory.registerCommand<AreatrackCommand>(String("areatrack").toLowerCase());
	commandFactory.registerCommand<AssignDroidCommand>(String("assignDroid").toLowerCase());
	commandFactory.registerCommand<AssistCommand>(String("assist").toLowerCase());
	commandFactory.registerCommand<AssociateDroidControlDeviceWithShipCommand>(String("associateDroidControlDeviceWithShip").toLowerCase());
	commandFactory.registerCommand<AttackCommand>(String("attack").toLowerCase());
	commandFactory.registerCommand<AuctionCommand>(String("auction").toLowerCase());
	commandFactory.registerCommand<AuctionAcceptCommand>(String("auctionAccept").toLowerCase());
	commandFactory.registerCommand<AuctionBidCommand>(String("auctionBid").toLowerCase());
	commandFactory.registerCommand<AuctionCancelCommand>(String("auctionCancel").toLowerCase());
	commandFactory.registerCommand<AuctionCreateCommand>(String("auctionCreate").toLowerCase());
	commandFactory.registerCommand<AuctionQueryCommand>(String("auctionQuery").toLowerCase());
	commandFactory.registerCommand<AuctionRetrieveCommand>(String("auctionRetrieve").toLowerCase());
	commandFactory.registerCommand<AuctionsayCommand>(String("auctionsay").toLowerCase());
	commandFactory.registerCommand<AvoidIncapacitationCommand>(String("avoidIncapacitation").toLowerCase());
	commandFactory.registerCommand<BandFlourishCommand>(String("bandFlourish").toLowerCase());
	commandFactory.registerCommand<BattlefieldStatusCommand>(String("battlefieldStatus").toLowerCase());
	commandFactory.registerCommand<Berserk1Command>(String("berserk1").toLowerCase());
	commandFactory.registerCommand<Berserk2Command>(String("berserk2").toLowerCase());
	commandFactory.registerCommand<BetCommand>(String("bet").toLowerCase());
	commandFactory.registerCommand<BleedingShotCommand>(String("bleedingShot").toLowerCase());
	commandFactory.registerCommand<BlindAttackCommand>(String("blindAttack").toLowerCase());
	commandFactory.registerCommand<BoardShuttleCommand>(String("boardShuttle").toLowerCase());
	commandFactory.registerCommand<BodyShot1Command>(String("bodyShot1").toLowerCase());
	commandFactory.registerCommand<BodyShot2Command>(String("bodyShot2").toLowerCase());
	commandFactory.registerCommand<BodyShot3Command>(String("bodyShot3").toLowerCase());
	commandFactory.registerCommand<BoostmoraleCommand>(String("boostmorale").toLowerCase());
	commandFactory.registerCommand<BroadcastCommand>(String("broadcast").toLowerCase());
	commandFactory.registerCommand<BroadcastAreaCommand>(String("broadcastArea").toLowerCase());
	commandFactory.registerCommand<BroadcastGalaxyCommand>(String("broadcastGalaxy").toLowerCase());
	commandFactory.registerCommand<BroadcastPlanetCommand>(String("broadcastPlanet").toLowerCase());
	commandFactory.registerCommand<BurstRunCommand>(String("burstRun").toLowerCase());
	commandFactory.registerCommand<BurstShot1Command>(String("burstShot1").toLowerCase());
	commandFactory.registerCommand<BurstShot2Command>(String("burstShot2").toLowerCase());
	commandFactory.registerCommand<CancelCraftingSessionCommand>(String("cancelCraftingSession").toLowerCase());
	commandFactory.registerCommand<CenterOfBeingCommand>(String("centerOfBeing").toLowerCase());
	commandFactory.registerCommand<ChangeBandMusicCommand>(String("changeBandMusic").toLowerCase());
	commandFactory.registerCommand<ChangeDanceCommand>(String("changeDance").toLowerCase());
	commandFactory.registerCommand<ChangeMusicCommand>(String("changeMusic").toLowerCase());
	commandFactory.registerCommand<ChannelForceCommand>(String("channelForce").toLowerCase());
	commandFactory.registerCommand<ChargeShot1Command>(String("chargeShot1").toLowerCase());
	commandFactory.registerCommand<ChargeShot2Command>(String("chargeShot2").toLowerCase());
	commandFactory.registerCommand<CheckForceStatusCommand>(String("checkForceStatus").toLowerCase());
	commandFactory.registerCommand<CitybanCommand>(String("cityban").toLowerCase());
	commandFactory.registerCommand<CitypardonCommand>(String("citypardon").toLowerCase());
	commandFactory.registerCommand<ClaimVeteranRewardCommand>(String("claimVeteranReward").toLowerCase());
	commandFactory.registerCommand<ClearCompletedQuestCommand>(String("clearCompletedQuest").toLowerCase());
	commandFactory.registerCommand<ClearVeteranRewardCommand>(String("clearVeteranReward").toLowerCase());
	commandFactory.registerCommand<ClientQualifiedForSkillCommand>(String("clientQualifiedForSkill").toLowerCase());
	commandFactory.registerCommand<CloneCommand>(String("clone").toLowerCase());
	commandFactory.registerCommand<CloseContainerCommand>(String("closeContainer").toLowerCase());
	commandFactory.registerCommand<ColorlightsCommand>(String("colorlights").toLowerCase());
	commandFactory.registerCommand<CombatCommand>(String("combat").toLowerCase());
	commandFactory.registerCommand<CombatEscapeCommand>(String("combatEscape").toLowerCase());
	commandFactory.registerCommand<CombatModeCheckCommand>(String("combatModeCheck").toLowerCase());
	commandFactory.registerCommand<CombatSpamCommand>(String("combatSpam").toLowerCase());
	commandFactory.registerCommand<CombatTargetCommand>(String("combatTarget").toLowerCase());
	commandFactory.registerCommand<CompleteQuestCommand>(String("completeQuest").toLowerCase());
	commandFactory.registerCommand<ConcealCommand>(String("conceal").toLowerCase());
	commandFactory.registerCommand<ConcealShotCommand>(String("concealShot").toLowerCase());
	commandFactory.registerCommand<ConfusionShotCommand>(String("confusionShot").toLowerCase());
	commandFactory.registerCommand<ConsentCommand>(String("consent").toLowerCase());
	commandFactory.registerCommand<CorpseCommand>(String("corpse").toLowerCase());
	commandFactory.registerCommand<CoupDeGraceCommand>(String("coupDeGrace").toLowerCase());
	commandFactory.registerCommand<CraftCommand>(String("craft").toLowerCase());
	commandFactory.registerCommand<CreateCreatureCommand>(String("createCreature").toLowerCase());
	commandFactory.registerCommand<CreateManfSchematicCommand>(String("createManfSchematic").toLowerCase());
	commandFactory.registerCommand<CreateMissionElementCommand>(String("createMissionElement").toLowerCase());
	commandFactory.registerCommand<CreateNPCCommand>(String("createNPC").toLowerCase());
	commandFactory.registerCommand<CreatePrototypeCommand>(String("createPrototype").toLowerCase());
	commandFactory.registerCommand<CreateSpawningElementCommand>(String("createSpawningElement").toLowerCase());
	commandFactory.registerCommand<CreateSpawningElementWithDifficultyCommand>(String("createSpawningElementWithDifficulty").toLowerCase());
	commandFactory.registerCommand<CreatureAreaAttackCommand>(String("creatureAreaAttack").toLowerCase());
	commandFactory.registerCommand<CreatureAreaBleedingCommand>(String("creatureAreaBleeding").toLowerCase());
	commandFactory.registerCommand<CreatureAreaComboCommand>(String("creatureAreaCombo").toLowerCase());
	commandFactory.registerCommand<CreatureAreaDiseaseCommand>(String("creatureAreaDisease").toLowerCase());
	commandFactory.registerCommand<CreatureAreaKnockdownCommand>(String("creatureAreaKnockdown").toLowerCase());
	commandFactory.registerCommand<CreatureRangedAttackCommand>(String("creatureRangedAttack").toLowerCase());
	commandFactory.registerCommand<CreatureAreaPoisonCommand>(String("creatureAreaPoison").toLowerCase());
	commandFactory.registerCommand<CreditsCommand>(String("credits").toLowerCase());
	commandFactory.registerCommand<CripplingShotCommand>(String("cripplingShot").toLowerCase());
	commandFactory.registerCommand<CsAppendCommentCommand>(String("csAppendComment").toLowerCase());
	commandFactory.registerCommand<CsCancelTicketCommand>(String("csCancelTicket").toLowerCase());
	commandFactory.registerCommand<CsConnectPlayerCommand>(String("csConnectPlayer").toLowerCase());
	commandFactory.registerCommand<CsCreateTicketCommand>(String("csCreateTicket").toLowerCase());
	commandFactory.registerCommand<CsDisconnectPlayerCommand>(String("csDisconnectPlayer").toLowerCase());
	commandFactory.registerCommand<CsGetArticleCommand>(String("csGetArticle").toLowerCase());
	commandFactory.registerCommand<CsGetCommentsCommand>(String("csGetComments").toLowerCase());
	commandFactory.registerCommand<CsGetTicketsCommand>(String("csGetTickets").toLowerCase());
	commandFactory.registerCommand<CsRequestCategoriesCommand>(String("csRequestCategories").toLowerCase());
	commandFactory.registerCommand<CsSearchKnowledgeBaseCommand>(String("csSearchKnowledgeBase").toLowerCase());
	commandFactory.registerCommand<CuiConsentResponseCommand>(String("cuiConsentResponse").toLowerCase());
	commandFactory.registerCommand<CureDiseaseCommand>(String("cureDisease").toLowerCase());
	commandFactory.registerCommand<CurePoisonCommand>(String("curePoison").toLowerCase());
	commandFactory.registerCommand<CustomizeDroidCommand>(String("customizeDroid").toLowerCase());
	commandFactory.registerCommand<CustomizeVehicleCommand>(String("customizeVehicle").toLowerCase());
	commandFactory.registerCommand<DatabaseCommand>(String("database").toLowerCase());
	commandFactory.registerCommand<DazzleCommand>(String("dazzle").toLowerCase());
	commandFactory.registerCommand<DeactivateQuestCommand>(String("deactivateQuest").toLowerCase());
	commandFactory.registerCommand<DeathBlowCommand>(String("deathBlow").toLowerCase());
	commandFactory.registerCommand<DeathCountCommand>(String("deathCount").toLowerCase());
	commandFactory.registerCommand<DeclareOvertCommand>(String("declareOvert").toLowerCase());
	commandFactory.registerCommand<DeclareresidenceCommand>(String("declareresidence").toLowerCase());
	commandFactory.registerCommand<DeclineCommand>(String("decline").toLowerCase());
	commandFactory.registerCommand<DefaultAttackCommand>(String("defaultAttack").toLowerCase());
	commandFactory.registerCommand<DefaultDroidAttackCommand>(String("defaultDroidAttack").toLowerCase());
	commandFactory.registerCommand<DefuseMinefieldCommand>(String("defuseMinefield").toLowerCase());
	commandFactory.registerCommand<DelegateFactionPointsCommand>(String("delegateFactionPoints").toLowerCase());
	commandFactory.registerCommand<DenyServiceCommand>(String("denyService").toLowerCase());
	commandFactory.registerCommand<DeployTrapCommand>(String("deployTrap").toLowerCase());
	commandFactory.registerCommand<DestroyCommand>(String("destroy").toLowerCase());
	commandFactory.registerCommand<DestroystructureCommand>(String("destroystructure").toLowerCase());
	commandFactory.registerCommand<DetonateDroidCommand>(String("detonateDroid").toLowerCase());
	commandFactory.registerCommand<DiagnoseCommand>(String("diagnose").toLowerCase());
	commandFactory.registerCommand<DisarmingShot1Command>(String("disarmingShot1").toLowerCase());
	commandFactory.registerCommand<DisarmingShot2Command>(String("disarmingShot2").toLowerCase());
	commandFactory.registerCommand<DisbandCommand>(String("disband").toLowerCase());
	commandFactory.registerCommand<DismissGroupMemberCommand>(String("dismissGroupMember").toLowerCase());
	commandFactory.registerCommand<DismountCommand>(String("dismount").toLowerCase());
	commandFactory.registerCommand<DismountandstoreCommand>(String("dismountandstore").toLowerCase());
	commandFactory.registerCommand<DistractCommand>(String("distract").toLowerCase());
	commandFactory.registerCommand<DiveShotCommand>(String("diveShot").toLowerCase());
	commandFactory.registerCommand<DizzyAttackCommand>(String("dizzyAttack").toLowerCase());
	commandFactory.registerCommand<DoubleTapCommand>(String("doubleTap").toLowerCase());
	commandFactory.registerCommand<DragIncapacitatedPlayerCommand>(String("dragIncapacitatedPlayer").toLowerCase());
	commandFactory.registerCommand<DrainForceCommand>(String("drainForce").toLowerCase());
	commandFactory.registerCommand<DuelCommand>(String("duel").toLowerCase());
	commandFactory.registerCommand<DumpTargetInformationCommand>(String("dumpTargetInformation").toLowerCase());
	commandFactory.registerCommand<DumpZoneInformationCommand>(String("dumpZoneInformation").toLowerCase());
	commandFactory.registerCommand<EatCommand>(String("eat").toLowerCase());
	commandFactory.registerCommand<EditAppearanceCommand>(String("editAppearance").toLowerCase());
	commandFactory.registerCommand<EditBankCommand>(String("editBank").toLowerCase());
	commandFactory.registerCommand<EditBankAccountCommand>(String("editBankAccount").toLowerCase());
	commandFactory.registerCommand<EditStatsCommand>(String("editStats").toLowerCase());
	commandFactory.registerCommand<EmboldenpetsCommand>(String("emboldenpets").toLowerCase());
	commandFactory.registerCommand<EmptyMailTargetCommand>(String("emptyMailTarget").toLowerCase());
	commandFactory.registerCommand<EndDuelCommand>(String("endDuel").toLowerCase());
	commandFactory.registerCommand<EnragepetsCommand>(String("enragepets").toLowerCase());
	commandFactory.registerCommand<EquilibriumCommand>(String("equilibrium").toLowerCase());
	commandFactory.registerCommand<ExecuteKnowledgeBaseMessageCommand>(String("executeKnowledgeBaseMessage").toLowerCase());
	commandFactory.registerCommand<ExtinguishFireCommand>(String("extinguishFire").toLowerCase());
	commandFactory.registerCommand<ExtractObjectCommand>(String("extractObject").toLowerCase());
	commandFactory.registerCommand<EyeShotCommand>(String("eyeShot").toLowerCase());
	commandFactory.registerCommand<FactoryCrateSplitCommand>(String("factoryCrateSplit").toLowerCase());
	commandFactory.registerCommand<FanShotCommand>(String("fanShot").toLowerCase());
	commandFactory.registerCommand<FastBlastCommand>(String("fastBlast").toLowerCase());
	commandFactory.registerCommand<FeignDeathCommand>(String("feignDeath").toLowerCase());
	commandFactory.registerCommand<FindCommand>(String("find").toLowerCase());
	commandFactory.registerCommand<FindFriendCommand>(String("findFriend").toLowerCase());
	commandFactory.registerCommand<FindFriendCommand>(String("findFriend").toLowerCase());
	commandFactory.registerCommand<FindMyTrainerCommand>(String("findMyTrainer").toLowerCase());
	commandFactory.registerCommand<FindObjectCommand>(String("findObject").toLowerCase());
	commandFactory.registerCommand<FindPlayerCommand>(String("findPlayer").toLowerCase());
	commandFactory.registerCommand<FireAcidCone1Command>(String("fireAcidCone1").toLowerCase());
	commandFactory.registerCommand<FireAcidCone2Command>(String("fireAcidCone2").toLowerCase());
	commandFactory.registerCommand<FireAcidSingle1Command>(String("fireAcidSingle1").toLowerCase());
	commandFactory.registerCommand<FireAcidSingle2Command>(String("fireAcidSingle2").toLowerCase());
	commandFactory.registerCommand<FireHeavyWeaponCommand>(String("fireHeavyWeapon").toLowerCase());
	commandFactory.registerCommand<FirejetCommand>(String("firejet").toLowerCase());
	commandFactory.registerCommand<FireLightningCone1Command>(String("fireLightningCone1").toLowerCase());
	commandFactory.registerCommand<FireLightningCone2Command>(String("fireLightningCone2").toLowerCase());
	commandFactory.registerCommand<FireLightningSingle1Command>(String("fireLightningSingle1").toLowerCase());
	commandFactory.registerCommand<FireLightningSingle2Command>(String("fireLightningSingle2").toLowerCase());
	commandFactory.registerCommand<FirstAidCommand>(String("firstAid").toLowerCase());
	commandFactory.registerCommand<FishCommand>(String("fish").toLowerCase());
	commandFactory.registerCommand<FlameCone1Command>(String("flameCone1").toLowerCase());
	commandFactory.registerCommand<FlameCone2Command>(String("flameCone2").toLowerCase());
	commandFactory.registerCommand<FlameSingle1Command>(String("flameSingle1").toLowerCase());
	commandFactory.registerCommand<FlameSingle2Command>(String("flameSingle2").toLowerCase());
	commandFactory.registerCommand<FlashSpeederCommand>(String("flashSpeeder").toLowerCase());
	commandFactory.registerCommand<FlourishCommand>(String("flourish").toLowerCase());
	commandFactory.registerCommand<FlurryShot1Command>(String("flurryShot1").toLowerCase());
	commandFactory.registerCommand<FlurryShot2Command>(String("flurryShot2").toLowerCase());
	commandFactory.registerCommand<FlushingShot1Command>(String("flushingShot1").toLowerCase());
	commandFactory.registerCommand<FlushingShot2Command>(String("flushingShot2").toLowerCase());
	commandFactory.registerCommand<ForageCommand>(String("forage").toLowerCase());
	commandFactory.registerCommand<ForceAbsorb1Command>(String("forceAbsorb1").toLowerCase());
	commandFactory.registerCommand<ForceAbsorb2Command>(String("forceAbsorb2").toLowerCase());
	commandFactory.registerCommand<ForceArmor1Command>(String("forceArmor1").toLowerCase());
	commandFactory.registerCommand<ForceArmor2Command>(String("forceArmor2").toLowerCase());
	commandFactory.registerCommand<ForceChokeCommand>(String("forceChoke").toLowerCase());
	commandFactory.registerCommand<ForceCommandCommand>(String("forceCommand").toLowerCase());
	commandFactory.registerCommand<ForceCureDiseaseCommand>(String("forceCureDisease").toLowerCase());
	commandFactory.registerCommand<ForceCurePoisonCommand>(String("forceCurePoison").toLowerCase());
	commandFactory.registerCommand<ForceFeedback1Command>(String("forceFeedback1").toLowerCase());
	commandFactory.registerCommand<ForceFeedback2Command>(String("forceFeedback2").toLowerCase());
	commandFactory.registerCommand<ForceIntimidate1Command>(String("forceIntimidate1").toLowerCase());
	commandFactory.registerCommand<ForceIntimidate2Command>(String("forceIntimidate2").toLowerCase());
	commandFactory.registerCommand<ForceKnockdown1Command>(String("forceKnockdown1").toLowerCase());
	commandFactory.registerCommand<ForceKnockdown2Command>(String("forceKnockdown2").toLowerCase());
	commandFactory.registerCommand<ForceKnockdown3Command>(String("forceKnockdown3").toLowerCase());
	commandFactory.registerCommand<ForceLightningCone1Command>(String("forceLightningCone1").toLowerCase());
	commandFactory.registerCommand<ForceLightningCone2Command>(String("forceLightningCone2").toLowerCase());
	commandFactory.registerCommand<ForceLightningSingle1Command>(String("forceLightningSingle1").toLowerCase());
	commandFactory.registerCommand<ForceLightningSingle2Command>(String("forceLightningSingle2").toLowerCase());
	commandFactory.registerCommand<ForceMeditateCommand>(String("forceMeditate").toLowerCase());
	commandFactory.registerCommand<ForceOfWillCommand>(String("forceOfWill").toLowerCase());
	commandFactory.registerCommand<ForceProtectionCommand>(String("forceProtection").toLowerCase());
	commandFactory.registerCommand<ForceResistBleedingCommand>(String("forceResistBleeding").toLowerCase());
	commandFactory.registerCommand<ForceResistDiseaseCommand>(String("forceResistDisease").toLowerCase());
	commandFactory.registerCommand<ForceResistPoisonCommand>(String("forceResistPoison").toLowerCase());
	commandFactory.registerCommand<ForceResistStatesCommand>(String("forceResistStates").toLowerCase());
	commandFactory.registerCommand<ForceRun1Command>(String("forceRun1").toLowerCase());
	commandFactory.registerCommand<ForceRun2Command>(String("forceRun2").toLowerCase());
	commandFactory.registerCommand<ForceRun3Command>(String("forceRun3").toLowerCase());
	commandFactory.registerCommand<ForceShield1Command>(String("forceShield1").toLowerCase());
	commandFactory.registerCommand<ForceShield2Command>(String("forceShield2").toLowerCase());
	commandFactory.registerCommand<ForceSpeed1Command>(String("forceSpeed1").toLowerCase());
	commandFactory.registerCommand<ForceSpeed2Command>(String("forceSpeed2").toLowerCase());
	commandFactory.registerCommand<ForceThrow1Command>(String("forceThrow1").toLowerCase());
	commandFactory.registerCommand<ForceThrow2Command>(String("forceThrow2").toLowerCase());
	commandFactory.registerCommand<ForceWeaken1Command>(String("forceWeaken1").toLowerCase());
	commandFactory.registerCommand<ForceWeaken2Command>(String("forceWeaken2").toLowerCase());
	commandFactory.registerCommand<FormupCommand>(String("formup").toLowerCase());
	commandFactory.registerCommand<FreezePlayerCommand>(String("freezePlayer").toLowerCase());
	commandFactory.registerCommand<FullAutoArea1Command>(String("fullAutoArea1").toLowerCase());
	commandFactory.registerCommand<FullAutoArea2Command>(String("fullAutoArea2").toLowerCase());
	commandFactory.registerCommand<FullAutoSingle1Command>(String("fullAutoSingle1").toLowerCase());
	commandFactory.registerCommand<FullAutoSingle2Command>(String("fullAutoSingle2").toLowerCase());
	commandFactory.registerCommand<GroupChatCommand>(String("g").toLowerCase());
	commandFactory.registerCommand<GallopCommand>(String("gallop").toLowerCase());
	commandFactory.registerCommand<GallopStopCommand>(String("gallopStop").toLowerCase());
	commandFactory.registerCommand<GcCommand>(String("gc").toLowerCase());
	commandFactory.registerCommand<GcwStatusCommand>(String("gcwStatus").toLowerCase());
	commandFactory.registerCommand<GenerateCraftedItemCommand>(String("generateCraftedItem").toLowerCase());
	commandFactory.registerCommand<GetAccountInfoCommand>(String("getAccountInfo").toLowerCase());
	commandFactory.registerCommand<GetAttributesCommand>(String("getAttributes").toLowerCase());
	commandFactory.registerCommand<GetAttributesBatchCommand>(String("getAttributesBatch").toLowerCase());
	commandFactory.registerCommand<GetFriendListCommand>(String("getFriendList").toLowerCase());
	commandFactory.registerCommand<GetGameTimeCommand>(String("getGameTime").toLowerCase());
	commandFactory.registerCommand<GetIgnoreListCommand>(String("getIgnoreList").toLowerCase());
	commandFactory.registerCommand<GetMapLocationsCommand>(String("getMapLocations").toLowerCase());
	commandFactory.registerCommand<GetObjVarsCommand>(String("getObjVars").toLowerCase());
	commandFactory.registerCommand<GetPlayerIdCommand>(String("getPlayerId").toLowerCase());
	commandFactory.registerCommand<GetPrototypeCommand>(String("getPrototype").toLowerCase());
	commandFactory.registerCommand<GetRankCommand>(String("getRank").toLowerCase());
	commandFactory.registerCommand<GetSpawnDelaysCommand>(String("getSpawnDelays").toLowerCase());
	commandFactory.registerCommand<GetStationNameCommand>(String("getStationName").toLowerCase());
	commandFactory.registerCommand<GetVeteranRewardTimeCommand>(String("getVeteranRewardTime").toLowerCase());
	commandFactory.registerCommand<GetVeteranRewardTimeCsCommand>(String("getVeteranRewardTimeCs").toLowerCase());
	commandFactory.registerCommand<GiveItemCommand>(String("giveItem").toLowerCase());
	commandFactory.registerCommand<GiveMaintenanceToVendorCommand>(String("giveMaintenanceToVendor").toLowerCase());
	commandFactory.registerCommand<GivevendormaintCommand>(String("givevendormaint").toLowerCase());
	commandFactory.registerCommand<GmForceCommandCommand>(String("gmForceCommand").toLowerCase());
	commandFactory.registerCommand<GmCreateClassResourceCommand>(String("gmCreateClassResource").toLowerCase());
	commandFactory.registerCommand<GmCreateSpecificResourceCommand>(String("gmCreateSpecificResource").toLowerCase());
	commandFactory.registerCommand<GmForceRankCommand>(String("gmForceRank").toLowerCase());
	commandFactory.registerCommand<GmFsVillageCommand>(String("gmFsVillage").toLowerCase());
	commandFactory.registerCommand<GmJediStateCommand>(String("gmJediState").toLowerCase());
	commandFactory.registerCommand<GmReviveCommand>(String("gmRevive").toLowerCase());
	commandFactory.registerCommand<GotoCommand>(String("goto").toLowerCase());
	commandFactory.registerCommand<GrantBadgeCommand>(String("grantBadge").toLowerCase());
	commandFactory.registerCommand<GrantPadawanTrialsEligibilityCommand>(String("grantPadawanTrialsEligibility").toLowerCase());
	commandFactory.registerCommand<GrantSkillCommand>(String("grantSkill").toLowerCase());
	commandFactory.registerCommand<GrantTitleCommand>(String("grantTitle").toLowerCase());
	commandFactory.registerCommand<GrantZoningRightsCommand>(String("grantZoningRights").toLowerCase());
	commandFactory.registerCommand<GroupChatCommand>(String("groupChat").toLowerCase());
	commandFactory.registerCommand<GroupChatCommand>(String("groupSay").toLowerCase());
	commandFactory.registerCommand<GroupChatCommand>(String("gsay").toLowerCase());
	commandFactory.registerCommand<GroupChatCommand>(String("gtell").toLowerCase());
	commandFactory.registerCommand<GuildCommand>(String("guild").toLowerCase());
	commandFactory.registerCommand<GuildremoveCommand>(String("guildremove").toLowerCase());
	commandFactory.registerCommand<GuildCommand>(String("guildsay").toLowerCase());
	commandFactory.registerCommand<GuildstatusCommand>(String("guildstatus").toLowerCase());
	commandFactory.registerCommand<HarmfulCommand>(String("harmful").toLowerCase());
	commandFactory.registerCommand<HarmlessCommand>(String("harmless").toLowerCase());
	commandFactory.registerCommand<HarvestCorpseCommand>(String("harvestCorpse").toLowerCase());
	commandFactory.registerCommand<HarvesterActivateCommand>(String("harvesterActivate").toLowerCase());
	commandFactory.registerCommand<HarvesterDeactivateCommand>(String("harvesterDeactivate").toLowerCase());
	commandFactory.registerCommand<HarvesterDiscardHopperCommand>(String("harvesterDiscardHopper").toLowerCase());
	commandFactory.registerCommand<HarvesterGetResourceDataCommand>(String("harvesterGetResourceData").toLowerCase());
	commandFactory.registerCommand<HarvesterHarvestCommand>(String("harvesterHarvest").toLowerCase());
	commandFactory.registerCommand<HarvesterMakeCrateCommand>(String("harvesterMakeCrate").toLowerCase());
	commandFactory.registerCommand<HarvesterSelectResourceCommand>(String("harvesterSelectResource").toLowerCase());
	commandFactory.registerCommand<HarvesterTakeSurveyCommand>(String("harvesterTakeSurvey").toLowerCase());
	commandFactory.registerCommand<HasVeteranRewardCommand>(String("hasVeteranReward").toLowerCase());
	commandFactory.registerCommand<HaveconsentCommand>(String("haveconsent").toLowerCase());
	commandFactory.registerCommand<HeadShot1Command>(String("headShot1").toLowerCase());
	commandFactory.registerCommand<HeadShot2Command>(String("headShot2").toLowerCase());
	commandFactory.registerCommand<HeadShot3Command>(String("headShot3").toLowerCase());
	commandFactory.registerCommand<HealActionSelf1Command>(String("healActionSelf1").toLowerCase());
	commandFactory.registerCommand<HealActionSelf2Command>(String("healActionSelf2").toLowerCase());
	commandFactory.registerCommand<HealActionWoundOther1Command>(String("healActionWoundOther1").toLowerCase());
	commandFactory.registerCommand<HealActionWoundOther2Command>(String("healActionWoundOther2").toLowerCase());
	commandFactory.registerCommand<HealActionWoundSelf1Command>(String("healActionWoundSelf1").toLowerCase());
	commandFactory.registerCommand<HealActionWoundSelf2Command>(String("healActionWoundSelf2").toLowerCase());
	commandFactory.registerCommand<HealAllOther1Command>(String("healAllOther1").toLowerCase());
	commandFactory.registerCommand<HealAllOther2Command>(String("healAllOther2").toLowerCase());
	commandFactory.registerCommand<HealAllSelf1Command>(String("healAllSelf1").toLowerCase());
	commandFactory.registerCommand<HealAllSelf2Command>(String("healAllSelf2").toLowerCase());
	commandFactory.registerCommand<HealBattleFatigueOther1Command>(String("healBattleFatigueOther1").toLowerCase());
	commandFactory.registerCommand<HealBattleFatigueOther2Command>(String("healBattleFatigueOther2").toLowerCase());
	commandFactory.registerCommand<HealBattleFatigueSelf1Command>(String("healBattleFatigueSelf1").toLowerCase());
	commandFactory.registerCommand<HealBattleFatigueSelf2Command>(String("healBattleFatigueSelf2").toLowerCase());
	commandFactory.registerCommand<HealDamageCommand>(String("healDamage").toLowerCase());
	commandFactory.registerCommand<HealDroidDamageCommand>(String("healDroidDamage").toLowerCase());
	commandFactory.registerCommand<HealDroidWoundCommand>(String("healDroidWound").toLowerCase());
	commandFactory.registerCommand<HealEnhanceCommand>(String("healEnhance").toLowerCase());
	commandFactory.registerCommand<HealHealthSelf1Command>(String("healHealthSelf1").toLowerCase());
	commandFactory.registerCommand<HealHealthSelf2Command>(String("healHealthSelf2").toLowerCase());
	commandFactory.registerCommand<HealHealthWoundOther1Command>(String("healHealthWoundOther1").toLowerCase());
	commandFactory.registerCommand<HealHealthWoundOther2Command>(String("healHealthWoundOther2").toLowerCase());
	commandFactory.registerCommand<HealHealthWoundSelf1Command>(String("healHealthWoundSelf1").toLowerCase());
	commandFactory.registerCommand<HealHealthWoundSelf2Command>(String("healHealthWoundSelf2").toLowerCase());
	commandFactory.registerCommand<HealMindCommand>(String("healMind").toLowerCase());
	commandFactory.registerCommand<HealMindSelf1Command>(String("healMindSelf1").toLowerCase());
	commandFactory.registerCommand<HealMindSelf2Command>(String("healMindSelf2").toLowerCase());
	commandFactory.registerCommand<HealMindWoundOther1Command>(String("healMindWoundOther1").toLowerCase());
	commandFactory.registerCommand<HealMindWoundOther2Command>(String("healMindWoundOther2").toLowerCase());
	commandFactory.registerCommand<HealMindWoundSelf1Command>(String("healMindWoundSelf1").toLowerCase());
	commandFactory.registerCommand<HealMindWoundSelf2Command>(String("healMindWoundSelf2").toLowerCase());
	commandFactory.registerCommand<HealPetCommand>(String("healPet").toLowerCase());
	commandFactory.registerCommand<HealStateCommand>(String("healState").toLowerCase());
	commandFactory.registerCommand<HealStatesOtherCommand>(String("healStatesOther").toLowerCase());
	commandFactory.registerCommand<HealStatesSelfCommand>(String("healStatesSelf").toLowerCase());
	commandFactory.registerCommand<HealthShot1Command>(String("healthShot1").toLowerCase());
	commandFactory.registerCommand<HealthShot2Command>(String("healthShot2").toLowerCase());
	commandFactory.registerCommand<HealWoundCommand>(String("healWound").toLowerCase());
	commandFactory.registerCommand<HoloEmoteCommand>(String("holoEmote").toLowerCase());
	commandFactory.registerCommand<ImagedesignCommand>(String("imagedesign").toLowerCase());
	commandFactory.registerCommand<InitializeComponentCommand>(String("initializeComponent").toLowerCase());
	commandFactory.registerCommand<InnateCommand>(String("innate").toLowerCase());
	commandFactory.registerCommand<InsertItemIntoShipComponentSlotCommand>(String("insertItemIntoShipComponentSlot").toLowerCase());
	commandFactory.registerCommand<InstallMissionTerminalCommand>(String("installMissionTerminal").toLowerCase());
	commandFactory.registerCommand<InstallShipComponentCommand>(String("installShipComponent").toLowerCase());
	commandFactory.registerCommand<InsureCommand>(String("insure").toLowerCase());
	commandFactory.registerCommand<Intimidate1Command>(String("intimidate1").toLowerCase());
	commandFactory.registerCommand<Intimidate2Command>(String("intimidate2").toLowerCase());
	commandFactory.registerCommand<IntimidationAttackCommand>(String("intimidationAttack").toLowerCase());
	commandFactory.registerCommand<MildPoisonCommand>(String("mildPoison").toLowerCase());
	commandFactory.registerCommand<MediumPoisonCommand>(String("mediumPoison").toLowerCase());
	commandFactory.registerCommand<MediumDiseaseCommand>(String("mediumDisease").toLowerCase());
	commandFactory.registerCommand<StrongPoisonCommand>(String("strongPoison").toLowerCase());
	commandFactory.registerCommand<StrongDiseaseCommand>(String("strongDisease").toLowerCase());
	commandFactory.registerCommand<MildDiseaseCommand>(String("mildDisease").toLowerCase());
	commandFactory.registerCommand<InviteCommand>(String("invite").toLowerCase());
	commandFactory.registerCommand<InvulnerableCommand>(String("invulnerable").toLowerCase());
	commandFactory.registerCommand<ItemmovebackCommand>(String("itemmoveback").toLowerCase());
	commandFactory.registerCommand<ItemmovedownCommand>(String("itemmovedown").toLowerCase());
	commandFactory.registerCommand<ItemmoveforwardCommand>(String("itemmoveforward").toLowerCase());
	commandFactory.registerCommand<ItemmoveupCommand>(String("itemmoveup").toLowerCase());
	commandFactory.registerCommand<ItemrotateleftCommand>(String("itemrotateleft").toLowerCase());
	commandFactory.registerCommand<ItemrotaterightCommand>(String("itemrotateright").toLowerCase());
	commandFactory.registerCommand<JediMindTrickCommand>(String("jediMindTrick").toLowerCase());
	commandFactory.registerCommand<JoinCommand>(String("join").toLowerCase());
	commandFactory.registerCommand<JoinGameCommand>(String("joinGame").toLowerCase());
	commandFactory.registerCommand<KickCommand>(String("kick").toLowerCase());
	commandFactory.registerCommand<KillCommand>(String("kill").toLowerCase());
	commandFactory.registerCommand<KillPlayerCommand>(String("killPlayer").toLowerCase());
	commandFactory.registerCommand<KipUpShotCommand>(String("kipUpShot").toLowerCase());
	commandFactory.registerCommand<KneelCommand>(String("kneel").toLowerCase());
	commandFactory.registerCommand<KnockdownAttackCommand>(String("knockdownAttack").toLowerCase());
	commandFactory.registerCommand<KnockdownFireCommand>(String("knockdownFire").toLowerCase());
	commandFactory.registerCommand<LagCommand>(String("lag").toLowerCase());
	commandFactory.registerCommand<LastDitchCommand>(String("lastDitch").toLowerCase());
	commandFactory.registerCommand<LaunchFireworkCommand>(String("launchFirework").toLowerCase());
	commandFactory.registerCommand<LeaveGameCommand>(String("leaveGame").toLowerCase());
	commandFactory.registerCommand<LeaveGroupCommand>(String("leaveGroup").toLowerCase());
	commandFactory.registerCommand<LegShot1Command>(String("legShot1").toLowerCase());
	commandFactory.registerCommand<LegShot2Command>(String("legShot2").toLowerCase());
	commandFactory.registerCommand<LegShot3Command>(String("legShot3").toLowerCase());
	commandFactory.registerCommand<LfgCommand>(String("lfg").toLowerCase());
	commandFactory.registerCommand<ListActiveQuestsCommand>(String("listActiveQuests").toLowerCase());
	commandFactory.registerCommand<ListCompletedQuestsCommand>(String("listCompletedQuests").toLowerCase());
	commandFactory.registerCommand<ListenCommand>(String("listen").toLowerCase());
	commandFactory.registerCommand<ListGuildsCommand>(String("listGuilds").toLowerCase());
	commandFactory.registerCommand<LogoutCommand>(String("logout").toLowerCase());
	commandFactory.registerCommand<LogoutServerCommand>(String("logoutServer").toLowerCase());
	commandFactory.registerCommand<LootCommand>(String("loot").toLowerCase());
	commandFactory.registerCommand<LootPlayerCorpseCommand>(String("lootPlayerCorpse").toLowerCase());
	commandFactory.registerCommand<LowBlowCommand>(String("lowBlow").toLowerCase());
	commandFactory.registerCommand<MakeLeaderCommand>(String("makeLeader").toLowerCase());
	commandFactory.registerCommand<MakeMasterLooterCommand>(String("makeMasterLooter").toLowerCase());
	commandFactory.registerCommand<MakeSurveyCommand>(String("makeSurvey").toLowerCase());
	commandFactory.registerCommand<ManufactureCommand>(String("manufacture").toLowerCase());
	commandFactory.registerCommand<MaskscentCommand>(String("maskscent").toLowerCase());
	commandFactory.registerCommand<MaxCombatAbilityCommand>(String("maxCombatAbility").toLowerCase());
	commandFactory.registerCommand<MaxStatsCommand>(String("maxStats").toLowerCase());
	commandFactory.registerCommand<MedicalForageCommand>(String("medicalForage").toLowerCase());
	commandFactory.registerCommand<MeditateCommand>(String("meditate").toLowerCase());
}
