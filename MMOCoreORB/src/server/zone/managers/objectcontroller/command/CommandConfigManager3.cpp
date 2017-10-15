#include "CommandConfigManager.h"

#include "server/zone/objects/creature/CreatureObject.h"
#include "server/zone/objects/creature/ai/Creature.h"

#include "server/zone/objects/player/sessions/crafting/CraftingSession.h"
#include "server/zone/objects/player/sessions/EntertainingSession.h"

#include "server/zone/objects/player/events/ForceMeditateTask.h"

#include "server/zone/objects/guild/GuildObject.h"

#include "server/zone/objects/region/CityRegion.h"

#include "server/zone/managers/player/PlayerManager.h"
#include "server/zone/managers/resource/ResourceManager.h"
#include "server/zone/managers/creature/PetManager.h"
#include "server/zone/managers/structure/StructureManager.h"
#include "server/zone/managers/skill/SkillManager.h"
#include "server/zone/managers/skill/PerformanceManager.h"
#include "server/zone/managers/director/DirectorManager.h"
#include "server/zone/managers/group/GroupManager.h"
#include "server/zone/managers/collision/CollisionManager.h"
#include "server/zone/managers/combat/CombatManager.h"

#include "server/zone/objects/group/GroupObject.h"

#include "server/login/account/Account.h"

#include "server/zone/objects/creature/ai/Creature.h"
#include "server/zone/objects/tangible/Instrument.h"

#include "server/zone/ZoneProcessServer.h"
#include "server/zone/ZoneServer.h"
#include "server/zone/Zone.h"

#include "server/zone/objects/creature/commands/JediQueueCommand.h"

#include "server/zone/objects/creature/commands/Melee1hBlindHit1Command.h"
#include "server/zone/objects/creature/commands/Melee1hBlindHit2Command.h"
#include "server/zone/objects/creature/commands/Melee1hBodyHit1Command.h"
#include "server/zone/objects/creature/commands/Melee1hBodyHit2Command.h"
#include "server/zone/objects/creature/commands/Melee1hBodyHit3Command.h"
#include "server/zone/objects/creature/commands/Melee1hDizzyHit1Command.h"
#include "server/zone/objects/creature/commands/Melee1hDizzyHit2Command.h"
#include "server/zone/objects/creature/commands/Melee1hHealthHit1Command.h"
#include "server/zone/objects/creature/commands/Melee1hHealthHit2Command.h"
#include "server/zone/objects/creature/commands/Melee1hHit1Command.h"
#include "server/zone/objects/creature/commands/Melee1hHit2Command.h"
#include "server/zone/objects/creature/commands/Melee1hHit3Command.h"
#include "server/zone/objects/creature/commands/Melee1hLunge1Command.h"
#include "server/zone/objects/creature/commands/Melee1hLunge2Command.h"
#include "server/zone/objects/creature/commands/Melee1hScatterHit1Command.h"
#include "server/zone/objects/creature/commands/Melee1hScatterHit2Command.h"
#include "server/zone/objects/creature/commands/Melee1hSpinAttack1Command.h"
#include "server/zone/objects/creature/commands/Melee1hSpinAttack2Command.h"
#include "server/zone/objects/creature/commands/Melee2hArea1Command.h"
#include "server/zone/objects/creature/commands/Melee2hArea2Command.h"
#include "server/zone/objects/creature/commands/Melee2hArea3Command.h"
#include "server/zone/objects/creature/commands/Melee2hHeadHit1Command.h"
#include "server/zone/objects/creature/commands/Melee2hHeadHit2Command.h"
#include "server/zone/objects/creature/commands/Melee2hHeadHit3Command.h"
#include "server/zone/objects/creature/commands/Melee2hHit1Command.h"
#include "server/zone/objects/creature/commands/Melee2hHit2Command.h"
#include "server/zone/objects/creature/commands/Melee2hHit3Command.h"
#include "server/zone/objects/creature/commands/Melee2hLunge1Command.h"
#include "server/zone/objects/creature/commands/Melee2hLunge2Command.h"
#include "server/zone/objects/creature/commands/Melee2hMindHit1Command.h"
#include "server/zone/objects/creature/commands/Melee2hMindHit2Command.h"
#include "server/zone/objects/creature/commands/Melee2hSpinAttack1Command.h"
#include "server/zone/objects/creature/commands/Melee2hSpinAttack2Command.h"
#include "server/zone/objects/creature/commands/Melee2hSweep1Command.h"
#include "server/zone/objects/creature/commands/Melee2hSweep2Command.h"
#include "server/zone/objects/creature/commands/MildDiseaseCommand.h"
#include "server/zone/objects/creature/commands/MildPoisonCommand.h"
#include "server/zone/objects/creature/commands/MindBlast1Command.h"
#include "server/zone/objects/creature/commands/MindBlast2Command.h"
#include "server/zone/objects/creature/commands/MindShot1Command.h"
#include "server/zone/objects/creature/commands/MindShot2Command.h"
#include "server/zone/objects/creature/commands/MinefieldAttackCommand.h"
#include "server/zone/objects/creature/commands/MoneyCommand.h"
#include "server/zone/objects/creature/commands/MountCommand.h"
#include "server/zone/objects/creature/commands/MoveFurnitureCommand.h"
#include "server/zone/objects/creature/commands/MultiTargetPistolShotCommand.h"
#include "server/zone/objects/creature/commands/MultiTargetShotCommand.h"
#include "server/zone/objects/creature/commands/NameStructureCommand.h"
#include "server/zone/objects/creature/commands/NewbiehelperCommand.h"
#include "server/zone/objects/creature/commands/NewbieRequestStartingLocationsCommand.h"
#include "server/zone/objects/creature/commands/NewbieSelectStartingLocationCommand.h"
#include "server/zone/objects/creature/commands/NextCraftingStageCommand.h"
#include "server/zone/objects/creature/commands/NpcCommand.h"
#include "server/zone/objects/creature/commands/NpcConversationSelectCommand.h"
#include "server/zone/objects/creature/commands/NpcConversationStartCommand.h"
#include "server/zone/objects/creature/commands/NpcConversationStopCommand.h"
#include "server/zone/objects/creature/commands/ObjectCommand.h"
#include "server/zone/objects/creature/commands/ObjvarCommand.h"
#include "server/zone/objects/creature/commands/OpenContainerCommand.h"
#include "server/zone/objects/creature/commands/OpenLotteryContainerCommand.h"
#include "server/zone/objects/creature/commands/OverChargeShot1Command.h"
#include "server/zone/objects/creature/commands/OverChargeShot2Command.h"
#include "server/zone/objects/creature/commands/OverrideActiveMonthsCommand.h"
#include "server/zone/objects/creature/commands/OverridePadawanTrialsEligibilityCommand.h"
#include "server/zone/objects/creature/commands/PanicShotCommand.h"
#include "server/zone/objects/creature/commands/PauseDanceCommand.h"
#include "server/zone/objects/creature/commands/PauseMusicCommand.h"
#include "server/zone/objects/creature/commands/PaWithdrawCommand.h"
#include "server/zone/objects/creature/commands/PaymaintenanceCommand.h"
#include "server/zone/objects/creature/commands/PeaceCommand.h"
#include "server/zone/objects/creature/commands/PermissionListModifyCommand.h"
#include "server/zone/objects/creature/commands/PistolMeleeDefense1Command.h"
#include "server/zone/objects/creature/commands/PistolMeleeDefense2Command.h"
#include "server/zone/objects/creature/commands/PlaceBattlefieldStructureCommand.h"
#include "server/zone/objects/creature/commands/PlaceStructureCommand.h"
#include "server/zone/objects/creature/commands/PlaceStructureModeCommand.h"
#include "server/zone/objects/creature/commands/PlanetCommand.h"
#include "server/zone/objects/creature/commands/PlanetsayCommand.h"
#include "server/zone/objects/creature/commands/PlanetwarpCommand.h"
#include "server/zone/objects/creature/commands/PlanetwarpTargetCommand.h"
#include "server/zone/objects/creature/commands/PointBlankArea1Command.h"
#include "server/zone/objects/creature/commands/PointBlankArea2Command.h"
#include "server/zone/objects/creature/commands/PointBlankSingle1Command.h"
#include "server/zone/objects/creature/commands/PointBlankSingle2Command.h"
#include "server/zone/objects/creature/commands/PolearmActionHit1Command.h"
#include "server/zone/objects/creature/commands/PolearmActionHit2Command.h"
#include "server/zone/objects/creature/commands/PolearmArea1Command.h"
#include "server/zone/objects/creature/commands/PolearmArea2Command.h"
#include "server/zone/objects/creature/commands/PolearmHit1Command.h"
#include "server/zone/objects/creature/commands/PolearmHit2Command.h"
#include "server/zone/objects/creature/commands/PolearmHit3Command.h"
#include "server/zone/objects/creature/commands/PolearmLegHit1Command.h"
#include "server/zone/objects/creature/commands/PolearmLegHit2Command.h"
#include "server/zone/objects/creature/commands/PolearmLegHit3Command.h"
#include "server/zone/objects/creature/commands/PolearmLunge1Command.h"
#include "server/zone/objects/creature/commands/PolearmLunge2Command.h"
#include "server/zone/objects/creature/commands/PolearmSpinAttack1Command.h"
#include "server/zone/objects/creature/commands/PolearmSpinAttack2Command.h"
#include "server/zone/objects/creature/commands/PolearmStun1Command.h"
#include "server/zone/objects/creature/commands/PolearmStun2Command.h"
#include "server/zone/objects/creature/commands/PolearmSweep1Command.h"
#include "server/zone/objects/creature/commands/PolearmSweep2Command.h"
#include "server/zone/objects/creature/commands/PostureDownAttackCommand.h"
#include "server/zone/objects/creature/commands/PostureUpAttackCommand.h"
#include "server/zone/objects/creature/commands/PowerBoostCommand.h"
#include "server/zone/objects/creature/commands/ProneCommand.h"
#include "server/zone/objects/creature/commands/PurchaseReinforcementCommand.h"
#include "server/zone/objects/creature/commands/PurchaseTicketCommand.h"
#include "server/zone/objects/creature/commands/QuickHealCommand.h"
#include "server/zone/objects/creature/commands/RallyCommand.h"
#include "server/zone/objects/creature/commands/ReconnectToTransferServerCommand.h"
#include "server/zone/objects/creature/commands/RecruitSkillTrainerCommand.h"
#include "server/zone/objects/creature/commands/RegainConsciousnessCommand.h"
#include "server/zone/objects/creature/commands/RegenerationCommand.h"
#include "server/zone/objects/creature/commands/RegisterWithLocationCommand.h"
#include "server/zone/objects/creature/commands/ReloadCommand.h"
#include "server/zone/objects/creature/commands/RemoteCommand.h"
#include "server/zone/objects/creature/commands/RemoveAllowedPlayerCommand.h"
#include "server/zone/objects/creature/commands/RemoveBannedPlayerCommand.h"
#include "server/zone/objects/creature/commands/RemoveFriendCommand.h"
#include "server/zone/objects/creature/commands/RemoveIgnoreCommand.h"
#include "server/zone/objects/creature/commands/RepairBattlefieldStructureCommand.h"
#include "server/zone/objects/creature/commands/RepairShipComponentInSlotCommand.h"
#include "server/zone/objects/creature/commands/ReportCommand.h"
#include "server/zone/objects/creature/commands/RequestBadgesCommand.h"
#include "server/zone/objects/creature/commands/RequestBiographyCommand.h"
#include "server/zone/objects/creature/commands/RequestCharacterMatchCommand.h"
#include "server/zone/objects/creature/commands/RequestCharacterSheetInfoCommand.h"
#include "server/zone/objects/creature/commands/RequestCoreSampleCommand.h"
#include "server/zone/objects/creature/commands/RequestCraftingSessionCommand.h"
#include "server/zone/objects/creature/commands/RequestDraftSlotsCommand.h"
#include "server/zone/objects/creature/commands/RequestDraftSlotsBatchCommand.h"
#include "server/zone/objects/creature/commands/RequestManfSchematicSlotsCommand.h"
#include "server/zone/objects/creature/commands/RequestResourceWeightsCommand.h"
#include "server/zone/objects/creature/commands/RequestResourceWeightsBatchCommand.h"
#include "server/zone/objects/creature/commands/RequestSetStatMigrationDataCommand.h"
#include "server/zone/objects/creature/commands/RequestStatMigrationDataCommand.h"
#include "server/zone/objects/creature/commands/RequestStatMigrationStartCommand.h"
#include "server/zone/objects/creature/commands/RequestStatMigrationStopCommand.h"
#include "server/zone/objects/creature/commands/RequestStimpackCommand.h"
#include "server/zone/objects/creature/commands/RequestSurveyCommand.h"
#include "server/zone/objects/creature/commands/RequestWaypointAtPositionCommand.h"
#include "server/zone/objects/creature/commands/RescueCommand.h"
#include "server/zone/objects/creature/commands/ResendLoginMessageToAllCommand.h"
#include "server/zone/objects/creature/commands/ResetJediCommand.h"
#include "server/zone/objects/creature/commands/ResourceCommand.h"
#include "server/zone/objects/creature/commands/ResourceContainerSplitCommand.h"
#include "server/zone/objects/creature/commands/ResourceContainerTransferCommand.h"
#include "server/zone/objects/creature/commands/ResourceSetNameCommand.h"
#include "server/zone/objects/creature/commands/ResSampleLoopCommand.h"
#include "server/zone/objects/creature/commands/RestartConversionCommand.h"
#include "server/zone/objects/creature/commands/RestartCraftingSessionCommand.h"
#include "server/zone/objects/creature/commands/RetreatCommand.h"
#include "server/zone/objects/creature/commands/RevivePlayerCommand.h"
#include "server/zone/objects/creature/commands/RevokeBadgeCommand.h"
#include "server/zone/objects/creature/commands/RevokeSkillCommand.h"
#include "server/zone/objects/creature/commands/RolePlayCommand.h"
#include "server/zone/objects/creature/commands/RollShotCommand.h"
#include "server/zone/objects/creature/commands/RotateFurnitureCommand.h"
#include "server/zone/objects/creature/commands/Saber1hComboHit1Command.h"
#include "server/zone/objects/creature/commands/Saber1hComboHit2Command.h"
#include "server/zone/objects/creature/commands/Saber1hComboHit3Command.h"
#include "server/zone/objects/creature/commands/Saber1hFlurryCommand.h"
#include "server/zone/objects/creature/commands/Saber1hFlurry2Command.h"
#include "server/zone/objects/creature/commands/Saber1hHeadHit1Command.h"
#include "server/zone/objects/creature/commands/Saber1hHeadHit2Command.h"
#include "server/zone/objects/creature/commands/Saber1hHeadHit3Command.h"
#include "server/zone/objects/creature/commands/Saber1hHit1Command.h"
#include "server/zone/objects/creature/commands/Saber1hHit2Command.h"
#include "server/zone/objects/creature/commands/Saber1hHit3Command.h"
#include "server/zone/objects/creature/commands/Saber2hBodyHit1Command.h"
#include "server/zone/objects/creature/commands/Saber2hBodyHit2Command.h"
#include "server/zone/objects/creature/commands/Saber2hBodyHit3Command.h"
#include "server/zone/objects/creature/commands/Saber2hFrenzyCommand.h"
#include "server/zone/objects/creature/commands/Saber2hHit1Command.h"
#include "server/zone/objects/creature/commands/Saber2hHit2Command.h"
#include "server/zone/objects/creature/commands/Saber2hHit3Command.h"
#include "server/zone/objects/creature/commands/Saber2hPhantomCommand.h"
#include "server/zone/objects/creature/commands/Saber2hSweep1Command.h"
#include "server/zone/objects/creature/commands/Saber2hSweep2Command.h"
#include "server/zone/objects/creature/commands/Saber2hSweep3Command.h"
#include "server/zone/objects/creature/commands/SaberPolearmDervishCommand.h"
#include "server/zone/objects/creature/commands/SaberPolearmDervish2Command.h"
#include "server/zone/objects/creature/commands/SaberPolearmHit1Command.h"
#include "server/zone/objects/creature/commands/SaberPolearmHit2Command.h"
#include "server/zone/objects/creature/commands/SaberPolearmHit3Command.h"
#include "server/zone/objects/creature/commands/SaberPolearmLegHit1Command.h"
#include "server/zone/objects/creature/commands/SaberPolearmLegHit2Command.h"
#include "server/zone/objects/creature/commands/SaberPolearmLegHit3Command.h"
#include "server/zone/objects/creature/commands/SaberPolearmSpinAttack1Command.h"
#include "server/zone/objects/creature/commands/SaberPolearmSpinAttack2Command.h"
#include "server/zone/objects/creature/commands/SaberPolearmSpinAttack3Command.h"
#include "server/zone/objects/creature/commands/SaberSlash1Command.h"
#include "server/zone/objects/creature/commands/SaberSlash2Command.h"
#include "server/zone/objects/creature/commands/SaberThrow1Command.h"
#include "server/zone/objects/creature/commands/SaberThrow2Command.h"
#include "server/zone/objects/creature/commands/SaberThrow3Command.h"
#include "server/zone/objects/creature/commands/SampleCommand.h"
#include "server/zone/objects/creature/commands/SampleDNACommand.h"
#include "server/zone/objects/creature/commands/ScatterShot1Command.h"
#include "server/zone/objects/creature/commands/ScatterShot2Command.h"
#include "server/zone/objects/creature/commands/ScriptCommand.h"
#include "server/zone/objects/creature/commands/SearchCorpseCommand.h"
#include "server/zone/objects/creature/commands/SecretSpawnSpamCommand.h"
#include "server/zone/objects/creature/commands/SeGogglesCommand.h"
#include "server/zone/objects/creature/commands/SelectDraftSchematicCommand.h"
#include "server/zone/objects/creature/commands/ServerCommand.h"
#include "server/zone/objects/creature/commands/ServerDestroyObjectCommand.h"
#include "server/zone/objects/creature/commands/ServerSysGroupCommand.h"
#include "server/zone/objects/creature/commands/SetBiographyAdminCommand.h"
#include "server/zone/objects/creature/commands/SetBiographyCommand.h"
#include "server/zone/objects/creature/commands/SetBoostmoraleCommand.h"
#include "server/zone/objects/creature/commands/SetChargeCommand.h"
#include "server/zone/objects/creature/commands/SetCurrentSkillTitleCommand.h"
#include "server/zone/objects/creature/commands/SetExperienceCommand.h"
#include "server/zone/objects/creature/commands/SetFactionCommand.h"
#include "server/zone/objects/creature/commands/SetFactionStandingCommand.h"
#include "server/zone/objects/creature/commands/SetFirstNameCommand.h"
#include "server/zone/objects/creature/commands/SetFormupCommand.h"
#include "server/zone/objects/creature/commands/SetGodModeCommand.h"
#include "server/zone/objects/creature/commands/SetHueCommand.h"
#include "server/zone/objects/creature/commands/SetIntimidateCommand.h"
#include "server/zone/objects/creature/commands/SetLastNameCommand.h"
#include "server/zone/objects/creature/commands/SetLoginMessageCommand.h"
#include "server/zone/objects/creature/commands/SetLoginTitleCommand.h"
#include "server/zone/objects/creature/commands/SetMatchMakingCharacterIdCommand.h"
#include "server/zone/objects/creature/commands/SetMatchMakingPersonalIdCommand.h"
#include "server/zone/objects/creature/commands/SetMaximumSpawnTimeCommand.h"
#include "server/zone/objects/creature/commands/SetMinimumSpawnTimeCommand.h"
#include "server/zone/objects/creature/commands/SetMoodCommand.h"
#include "server/zone/objects/creature/commands/SetMoodInternalCommand.h"
#include "server/zone/objects/creature/commands/SetNameCommand.h"
#include "server/zone/objects/creature/commands/SetNameCommand.h"
#include "server/zone/objects/creature/commands/SetOwnerCommand.h"
#include "server/zone/objects/creature/commands/SetPerformanceBuffTargetCommand.h"
#include "server/zone/objects/creature/commands/SetpermissionCommand.h"
#include "server/zone/objects/creature/commands/SetPlanetLimitCommand.h"
#include "server/zone/objects/creature/commands/SetPlayerAppearanceCommand.h"
#include "server/zone/objects/creature/commands/SetPlayerStateCommand.h"
#include "server/zone/objects/creature/commands/SetprivacyCommand.h"
#include "server/zone/objects/creature/commands/SetPublicStateCommand.h"
#include "server/zone/objects/creature/commands/SetRankCommand.h"
#include "server/zone/objects/creature/commands/SetRetreatCommand.h"
#include "server/zone/objects/creature/commands/SetSpeedCommand.h"
#include "server/zone/objects/creature/commands/SetSpokenLanguageCommand.h"
#include "server/zone/objects/creature/commands/SetSteadyaimCommand.h"
#include "server/zone/objects/creature/commands/SetTEFCommand.h"
#include "server/zone/objects/creature/commands/SetVeteranRewardCommand.h"
#include "server/zone/objects/creature/commands/SetWarcryCommand.h"
#include "server/zone/objects/creature/commands/SetWaypointActiveStatusCommand.h"
#include "server/zone/objects/creature/commands/SetWaypointNameCommand.h"
#include "server/zone/objects/creature/commands/ShowCouncilRankCommand.h"
#include "server/zone/objects/creature/commands/ShowDanceVisualsCommand.h"
#include "server/zone/objects/creature/commands/ShowFactionInformationCommand.h"
#include "server/zone/objects/creature/commands/ShowMusicianVisualsCommand.h"
#include "server/zone/objects/creature/commands/ShowPvPRatingCommand.h"
#include "server/zone/objects/creature/commands/ShowSpawnRegionCommand.h"
#include "server/zone/objects/creature/commands/SitServerCommand.h"
#include "server/zone/objects/creature/commands/SkillCommand.h"
#include "server/zone/objects/creature/commands/SmokebombCommand.h"
#include "server/zone/objects/creature/commands/SniperShotCommand.h"
#include "server/zone/objects/creature/commands/SnoopCommand.h"
#include "server/zone/objects/creature/commands/SocialCommand.h"
#include "server/zone/objects/creature/commands/SocialInternalCommand.h"
#include "server/zone/objects/creature/commands/SpatialChatCommand.h"
#include "server/zone/objects/creature/commands/SpatialChatInternalCommand.h"
#include "server/zone/objects/creature/commands/SpawnStatusCommand.h"
#include "server/zone/objects/creature/commands/SplitCreditsWithGroupCommand.h"
#include "server/zone/objects/creature/commands/SpotlightCommand.h"
#include "server/zone/objects/creature/commands/SprayShotCommand.h"
#include "server/zone/objects/creature/commands/StandCommand.h"
#include "server/zone/objects/creature/commands/StartBandCommand.h"
#include "server/zone/objects/creature/commands/StartCitySpawnerCommand.h"
#include "server/zone/objects/creature/commands/StartDanceCommand.h"
#include "server/zone/objects/creature/commands/StartleShot1Command.h"
#include "server/zone/objects/creature/commands/StartleShot2Command.h"
#include "server/zone/objects/creature/commands/StartMusicCommand.h"
#include "server/zone/objects/creature/commands/StartSpawnerCommand.h"
#include "server/zone/objects/creature/commands/StartTargetSpawnerCommand.h"
#include "server/zone/objects/creature/commands/StartTraceLoggingCommand.h"
#include "server/zone/objects/creature/commands/StatCommand.h"
#include "server/zone/objects/creature/commands/SteadyaimCommand.h"
#include "server/zone/objects/creature/commands/StopBandCommand.h"
#include "server/zone/objects/creature/commands/StopBleedingCommand.h"
#include "server/zone/objects/creature/commands/StopCitySpawnerCommand.h"
#include "server/zone/objects/creature/commands/StopCraftingSessionCommand.h"
#include "server/zone/objects/creature/commands/StopDanceCommand.h"
#include "server/zone/objects/creature/commands/StoplisteningCommand.h"
#include "server/zone/objects/creature/commands/StopMusicCommand.h"
#include "server/zone/objects/creature/commands/StoppingShotCommand.h"
#include "server/zone/objects/creature/commands/StopSpawnerCommand.h"
#include "server/zone/objects/creature/commands/StopTargetSpawnerCommand.h"
#include "server/zone/objects/creature/commands/StopTraceLoggingCommand.h"
#include "server/zone/objects/creature/commands/StopwatchingCommand.h"
#include "server/zone/objects/creature/commands/StrafeShot1Command.h"
#include "server/zone/objects/creature/commands/StrafeShot2Command.h"
#include "server/zone/objects/creature/commands/StructurestatusCommand.h"
#include "server/zone/objects/creature/commands/StunAttackCommand.h"

using namespace server::zone::managers::objectcontroller::command;


void CommandConfigManager::registerCommands3() {
	commandFactory.registerCommand<Melee1hBlindHit1Command>(String("melee1hBlindHit1").toLowerCase());
	commandFactory.registerCommand<Melee1hBlindHit2Command>(String("melee1hBlindHit2").toLowerCase());
	commandFactory.registerCommand<Melee1hBodyHit1Command>(String("melee1hBodyHit1").toLowerCase());
	commandFactory.registerCommand<Melee1hBodyHit2Command>(String("melee1hBodyHit2").toLowerCase());
	commandFactory.registerCommand<Melee1hBodyHit3Command>(String("melee1hBodyHit3").toLowerCase());
	commandFactory.registerCommand<Melee1hDizzyHit1Command>(String("melee1hDizzyHit1").toLowerCase());
	commandFactory.registerCommand<Melee1hDizzyHit2Command>(String("melee1hDizzyHit2").toLowerCase());
	commandFactory.registerCommand<Melee1hHealthHit1Command>(String("melee1hHealthHit1").toLowerCase());
	commandFactory.registerCommand<Melee1hHealthHit2Command>(String("melee1hHealthHit2").toLowerCase());
	commandFactory.registerCommand<Melee1hHit1Command>(String("melee1hHit1").toLowerCase());
	commandFactory.registerCommand<Melee1hHit2Command>(String("melee1hHit2").toLowerCase());
	commandFactory.registerCommand<Melee1hHit3Command>(String("melee1hHit3").toLowerCase());
	commandFactory.registerCommand<Melee1hLunge1Command>(String("melee1hLunge1").toLowerCase());
	commandFactory.registerCommand<Melee1hLunge2Command>(String("melee1hLunge2").toLowerCase());
	commandFactory.registerCommand<Melee1hScatterHit1Command>(String("melee1hScatterHit1").toLowerCase());
	commandFactory.registerCommand<Melee1hScatterHit2Command>(String("melee1hScatterHit2").toLowerCase());
	commandFactory.registerCommand<Melee1hSpinAttack1Command>(String("melee1hSpinAttack1").toLowerCase());
	commandFactory.registerCommand<Melee1hSpinAttack2Command>(String("melee1hSpinAttack2").toLowerCase());
	commandFactory.registerCommand<Melee2hArea1Command>(String("melee2hArea1").toLowerCase());
	commandFactory.registerCommand<Melee2hArea2Command>(String("melee2hArea2").toLowerCase());
	commandFactory.registerCommand<Melee2hArea3Command>(String("melee2hArea3").toLowerCase());
	commandFactory.registerCommand<Melee2hHeadHit1Command>(String("melee2hHeadHit1").toLowerCase());
	commandFactory.registerCommand<Melee2hHeadHit2Command>(String("melee2hHeadHit2").toLowerCase());
	commandFactory.registerCommand<Melee2hHeadHit3Command>(String("melee2hHeadHit3").toLowerCase());
	commandFactory.registerCommand<Melee2hHit1Command>(String("melee2hHit1").toLowerCase());
	commandFactory.registerCommand<Melee2hHit2Command>(String("melee2hHit2").toLowerCase());
	commandFactory.registerCommand<Melee2hHit3Command>(String("melee2hHit3").toLowerCase());
	commandFactory.registerCommand<Melee2hLunge1Command>(String("melee2hLunge1").toLowerCase());
	commandFactory.registerCommand<Melee2hLunge2Command>(String("melee2hLunge2").toLowerCase());
	commandFactory.registerCommand<Melee2hMindHit1Command>(String("melee2hMindHit1").toLowerCase());
	commandFactory.registerCommand<Melee2hMindHit2Command>(String("melee2hMindHit2").toLowerCase());
	commandFactory.registerCommand<Melee2hSpinAttack1Command>(String("melee2hSpinAttack1").toLowerCase());
	commandFactory.registerCommand<Melee2hSpinAttack2Command>(String("melee2hSpinAttack2").toLowerCase());
	commandFactory.registerCommand<Melee2hSweep1Command>(String("melee2hSweep1").toLowerCase());
	commandFactory.registerCommand<Melee2hSweep2Command>(String("melee2hSweep2").toLowerCase());
	commandFactory.registerCommand<MindBlast1Command>(String("mindBlast1").toLowerCase());
	commandFactory.registerCommand<MindBlast2Command>(String("mindBlast2").toLowerCase());
	commandFactory.registerCommand<MindShot1Command>(String("mindShot1").toLowerCase());
	commandFactory.registerCommand<MindShot2Command>(String("mindShot2").toLowerCase());
	commandFactory.registerCommand<MinefieldAttackCommand>(String("minefieldAttack").toLowerCase());
	commandFactory.registerCommand<MoneyCommand>(String("money").toLowerCase());
	commandFactory.registerCommand<MountCommand>(String("mount").toLowerCase());
	commandFactory.registerCommand<MoveFurnitureCommand>(String("moveFurniture").toLowerCase());
	commandFactory.registerCommand<MultiTargetPistolShotCommand>(String("multiTargetPistolShot").toLowerCase());
	commandFactory.registerCommand<MultiTargetShotCommand>(String("multiTargetShot").toLowerCase());
	commandFactory.registerCommand<NameStructureCommand>(String("nameStructure").toLowerCase());
	commandFactory.registerCommand<NewbiehelperCommand>(String("newbiehelper").toLowerCase());
	commandFactory.registerCommand<NewbieRequestStartingLocationsCommand>(String("newbieRequestStartingLocations").toLowerCase());
	commandFactory.registerCommand<NewbieSelectStartingLocationCommand>(String("newbieSelectStartingLocation").toLowerCase());
	commandFactory.registerCommand<NextCraftingStageCommand>(String("nextCraftingStage").toLowerCase());
	commandFactory.registerCommand<NpcCommand>(String("npc").toLowerCase());
	commandFactory.registerCommand<NpcConversationSelectCommand>(String("npcConversationSelect").toLowerCase());
	commandFactory.registerCommand<NpcConversationStartCommand>(String("npcConversationStart").toLowerCase());
	commandFactory.registerCommand<NpcConversationStopCommand>(String("npcConversationStop").toLowerCase());
	commandFactory.registerCommand<ObjectCommand>(String("Object").toLowerCase());
	commandFactory.registerCommand<ObjvarCommand>(String("objvar").toLowerCase());
	commandFactory.registerCommand<OpenContainerCommand>(String("openContainer").toLowerCase());
	commandFactory.registerCommand<OverChargeShot1Command>(String("overChargeShot1").toLowerCase());
	commandFactory.registerCommand<OverChargeShot2Command>(String("overChargeShot2").toLowerCase());
	commandFactory.registerCommand<OverrideActiveMonthsCommand>(String("overrideActiveMonths").toLowerCase());
	commandFactory.registerCommand<OverridePadawanTrialsEligibilityCommand>(String("overridePadawanTrialsEligibility").toLowerCase());
	commandFactory.registerCommand<PanicShotCommand>(String("panicShot").toLowerCase());
	commandFactory.registerCommand<PauseDanceCommand>(String("pauseDance").toLowerCase());
	commandFactory.registerCommand<PauseMusicCommand>(String("pauseMusic").toLowerCase());
	commandFactory.registerCommand<PaWithdrawCommand>(String("paWithdraw").toLowerCase());
	commandFactory.registerCommand<PaymaintenanceCommand>(String("paymaintenance").toLowerCase());
	commandFactory.registerCommand<PeaceCommand>(String("peace").toLowerCase());
	commandFactory.registerCommand<PermissionListModifyCommand>(String("permissionListModify").toLowerCase());
	commandFactory.registerCommand<PistolMeleeDefense1Command>(String("pistolMeleeDefense1").toLowerCase());
	commandFactory.registerCommand<PistolMeleeDefense2Command>(String("pistolMeleeDefense2").toLowerCase());
	commandFactory.registerCommand<PlaceBattlefieldStructureCommand>(String("placeBattlefieldStructure").toLowerCase());
	commandFactory.registerCommand<PlaceStructureCommand>(String("placeStructure").toLowerCase());
	commandFactory.registerCommand<PlaceStructureModeCommand>(String("placeStructureMode").toLowerCase());
	commandFactory.registerCommand<PlanetCommand>(String("planet").toLowerCase());
	commandFactory.registerCommand<PlanetsayCommand>(String("planetsay").toLowerCase());
	commandFactory.registerCommand<PlanetwarpCommand>(String("planetwarp").toLowerCase());
	commandFactory.registerCommand<PlanetwarpTargetCommand>(String("planetwarpTarget").toLowerCase());
	commandFactory.registerCommand<PointBlankArea1Command>(String("pointBlankArea1").toLowerCase());
	commandFactory.registerCommand<PointBlankArea2Command>(String("pointBlankArea2").toLowerCase());
	commandFactory.registerCommand<PointBlankSingle1Command>(String("pointBlankSingle1").toLowerCase());
	commandFactory.registerCommand<PointBlankSingle2Command>(String("pointBlankSingle2").toLowerCase());
	commandFactory.registerCommand<PolearmActionHit1Command>(String("polearmActionHit1").toLowerCase());
	commandFactory.registerCommand<PolearmActionHit2Command>(String("polearmActionHit2").toLowerCase());
	commandFactory.registerCommand<PolearmArea1Command>(String("polearmArea1").toLowerCase());
	commandFactory.registerCommand<PolearmArea2Command>(String("polearmArea2").toLowerCase());
	commandFactory.registerCommand<PolearmHit1Command>(String("polearmHit1").toLowerCase());
	commandFactory.registerCommand<PolearmHit2Command>(String("polearmHit2").toLowerCase());
	commandFactory.registerCommand<PolearmHit3Command>(String("polearmHit3").toLowerCase());
	commandFactory.registerCommand<PolearmLegHit1Command>(String("polearmLegHit1").toLowerCase());
	commandFactory.registerCommand<PolearmLegHit2Command>(String("polearmLegHit2").toLowerCase());
	commandFactory.registerCommand<PolearmLegHit3Command>(String("polearmLegHit3").toLowerCase());
	commandFactory.registerCommand<PolearmLunge1Command>(String("polearmLunge1").toLowerCase());
	commandFactory.registerCommand<PolearmLunge2Command>(String("polearmLunge2").toLowerCase());
	commandFactory.registerCommand<PolearmSpinAttack1Command>(String("polearmSpinAttack1").toLowerCase());
	commandFactory.registerCommand<PolearmSpinAttack2Command>(String("polearmSpinAttack2").toLowerCase());
	commandFactory.registerCommand<PolearmStun1Command>(String("polearmStun1").toLowerCase());
	commandFactory.registerCommand<PolearmStun2Command>(String("polearmStun2").toLowerCase());
	commandFactory.registerCommand<PolearmSweep1Command>(String("polearmSweep1").toLowerCase());
	commandFactory.registerCommand<PolearmSweep2Command>(String("polearmSweep2").toLowerCase());
	commandFactory.registerCommand<PostureDownAttackCommand>(String("postureDownAttack").toLowerCase());
	commandFactory.registerCommand<PostureUpAttackCommand>(String("postureUpAttack").toLowerCase());
	commandFactory.registerCommand<PowerBoostCommand>(String("powerBoost").toLowerCase());
	commandFactory.registerCommand<ProneCommand>(String("prone").toLowerCase());
	commandFactory.registerCommand<PurchaseReinforcementCommand>(String("purchaseReinforcement").toLowerCase());
	commandFactory.registerCommand<PurchaseTicketCommand>(String("purchaseTicket").toLowerCase());
	commandFactory.registerCommand<QuickHealCommand>(String("quickHeal").toLowerCase());
	commandFactory.registerCommand<RallyCommand>(String("rally").toLowerCase());
	commandFactory.registerCommand<ReconnectToTransferServerCommand>(String("reconnectToTransferServer").toLowerCase());
	commandFactory.registerCommand<RecruitSkillTrainerCommand>(String("recruitSkillTrainer").toLowerCase());
	commandFactory.registerCommand<RegainConsciousnessCommand>(String("regainConsciousness").toLowerCase());
	commandFactory.registerCommand<RegenerationCommand>(String("regeneration").toLowerCase());
	commandFactory.registerCommand<RegisterWithLocationCommand>(String("registerWithLocation").toLowerCase());
	commandFactory.registerCommand<ReloadCommand>(String("reload").toLowerCase());
	commandFactory.registerCommand<RemoteCommand>(String("remote").toLowerCase());
	commandFactory.registerCommand<RemoveAllowedPlayerCommand>(String("removeAllowedPlayer").toLowerCase());
	commandFactory.registerCommand<RemoveBannedPlayerCommand>(String("removeBannedPlayer").toLowerCase());
	commandFactory.registerCommand<RemoveFriendCommand>(String("removeFriend").toLowerCase());
	commandFactory.registerCommand<RemoveIgnoreCommand>(String("removeIgnore").toLowerCase());
	commandFactory.registerCommand<RepairBattlefieldStructureCommand>(String("repairBattlefieldStructure").toLowerCase());
	commandFactory.registerCommand<RepairShipComponentInSlotCommand>(String("repairShipComponentInSlot").toLowerCase());
	commandFactory.registerCommand<ReportCommand>(String("report").toLowerCase());
	commandFactory.registerCommand<RequestBadgesCommand>(String("requestBadges").toLowerCase());
	commandFactory.registerCommand<RequestBiographyCommand>(String("requestBiography").toLowerCase());
	commandFactory.registerCommand<RequestCharacterMatchCommand>(String("requestCharacterMatch").toLowerCase());
	commandFactory.registerCommand<RequestCharacterSheetInfoCommand>(String("requestCharacterSheetInfo").toLowerCase());
	commandFactory.registerCommand<RequestCoreSampleCommand>(String("requestCoreSample").toLowerCase());
	commandFactory.registerCommand<RequestCraftingSessionCommand>(String("requestCraftingSession").toLowerCase());
	commandFactory.registerCommand<RequestDraftSlotsCommand>(String("requestDraftSlots").toLowerCase());
	commandFactory.registerCommand<RequestDraftSlotsBatchCommand>(String("requestDraftSlotsBatch").toLowerCase());
	commandFactory.registerCommand<RequestManfSchematicSlotsCommand>(String("requestManfSchematicSlots").toLowerCase());
	commandFactory.registerCommand<RequestResourceWeightsCommand>(String("requestResourceWeights").toLowerCase());
	commandFactory.registerCommand<RequestResourceWeightsBatchCommand>(String("requestResourceWeightsBatch").toLowerCase());
	commandFactory.registerCommand<RequestSetStatMigrationDataCommand>(String("requestSetStatMigrationData").toLowerCase());
	commandFactory.registerCommand<RequestStatMigrationDataCommand>(String("requestStatMigrationData").toLowerCase());
	commandFactory.registerCommand<RequestStatMigrationStartCommand>(String("requestStatMigrationStart").toLowerCase());
	commandFactory.registerCommand<RequestStatMigrationStopCommand>(String("requestStatMigrationStop").toLowerCase());
	commandFactory.registerCommand<RequestStimpackCommand>(String("requestStimpack").toLowerCase());
	commandFactory.registerCommand<RequestSurveyCommand>(String("requestSurvey").toLowerCase());
	commandFactory.registerCommand<RequestWaypointAtPositionCommand>(String("requestWaypointAtPosition").toLowerCase());
	commandFactory.registerCommand<RescueCommand>(String("rescue").toLowerCase());
	commandFactory.registerCommand<ResendLoginMessageToAllCommand>(String("resendLoginMessageToAll").toLowerCase());
	commandFactory.registerCommand<ResetJediCommand>(String("resetJedi").toLowerCase());
	commandFactory.registerCommand<ResourceCommand>(String("resource").toLowerCase());
	commandFactory.registerCommand<ResourceContainerSplitCommand>(String("resourceContainerSplit").toLowerCase());
	commandFactory.registerCommand<ResourceContainerTransferCommand>(String("resourceContainerTransfer").toLowerCase());
	commandFactory.registerCommand<ResourceSetNameCommand>(String("resourceSetName").toLowerCase());
	commandFactory.registerCommand<ResSampleLoopCommand>(String("resSampleLoop").toLowerCase());
	commandFactory.registerCommand<RestartConversionCommand>(String("restartConversion").toLowerCase());
	commandFactory.registerCommand<RestartCraftingSessionCommand>(String("restartCraftingSession").toLowerCase());
	commandFactory.registerCommand<RetreatCommand>(String("retreat").toLowerCase());
	commandFactory.registerCommand<RevivePlayerCommand>(String("revivePlayer").toLowerCase());
	commandFactory.registerCommand<RevokeBadgeCommand>(String("revokeBadge").toLowerCase());
	commandFactory.registerCommand<RevokeSkillCommand>(String("revokeSkill").toLowerCase());
	commandFactory.registerCommand<RolePlayCommand>(String("rolePlay").toLowerCase());
	commandFactory.registerCommand<RollShotCommand>(String("rollShot").toLowerCase());
	commandFactory.registerCommand<RotateFurnitureCommand>(String("rotateFurniture").toLowerCase());
	commandFactory.registerCommand<Saber1hComboHit1Command>(String("saber1hComboHit1").toLowerCase());
	commandFactory.registerCommand<Saber1hComboHit2Command>(String("saber1hComboHit2").toLowerCase());
	commandFactory.registerCommand<Saber1hComboHit3Command>(String("saber1hComboHit3").toLowerCase());
	commandFactory.registerCommand<Saber1hFlurryCommand>(String("saber1hFlurry").toLowerCase());
	commandFactory.registerCommand<Saber1hFlurry2Command>(String("saber1hFlurry2").toLowerCase());
	commandFactory.registerCommand<Saber1hHeadHit1Command>(String("saber1hHeadHit1").toLowerCase());
	commandFactory.registerCommand<Saber1hHeadHit2Command>(String("saber1hHeadHit2").toLowerCase());
	commandFactory.registerCommand<Saber1hHeadHit3Command>(String("saber1hHeadHit3").toLowerCase());
	commandFactory.registerCommand<Saber1hHit1Command>(String("saber1hHit1").toLowerCase());
	commandFactory.registerCommand<Saber1hHit2Command>(String("saber1hHit2").toLowerCase());
	commandFactory.registerCommand<Saber1hHit3Command>(String("saber1hHit3").toLowerCase());
	commandFactory.registerCommand<Saber2hBodyHit1Command>(String("saber2hBodyHit1").toLowerCase());
	commandFactory.registerCommand<Saber2hBodyHit2Command>(String("saber2hBodyHit2").toLowerCase());
	commandFactory.registerCommand<Saber2hBodyHit3Command>(String("saber2hBodyHit3").toLowerCase());
	commandFactory.registerCommand<Saber2hFrenzyCommand>(String("saber2hFrenzy").toLowerCase());
	commandFactory.registerCommand<Saber2hHit1Command>(String("saber2hHit1").toLowerCase());
	commandFactory.registerCommand<Saber2hHit2Command>(String("saber2hHit2").toLowerCase());
	commandFactory.registerCommand<Saber2hHit3Command>(String("saber2hHit3").toLowerCase());
	commandFactory.registerCommand<Saber2hPhantomCommand>(String("saber2hPhantom").toLowerCase());
	commandFactory.registerCommand<Saber2hSweep1Command>(String("saber2hSweep1").toLowerCase());
	commandFactory.registerCommand<Saber2hSweep2Command>(String("saber2hSweep2").toLowerCase());
	commandFactory.registerCommand<Saber2hSweep3Command>(String("saber2hSweep3").toLowerCase());
	commandFactory.registerCommand<SaberPolearmDervishCommand>(String("saberPolearmDervish").toLowerCase());
	commandFactory.registerCommand<SaberPolearmDervish2Command>(String("saberPolearmDervish2").toLowerCase());
	commandFactory.registerCommand<SaberPolearmHit1Command>(String("saberPolearmHit1").toLowerCase());
	commandFactory.registerCommand<SaberPolearmHit2Command>(String("saberPolearmHit2").toLowerCase());
	commandFactory.registerCommand<SaberPolearmHit3Command>(String("saberPolearmHit3").toLowerCase());
	commandFactory.registerCommand<SaberPolearmLegHit1Command>(String("saberPolearmLegHit1").toLowerCase());
	commandFactory.registerCommand<SaberPolearmLegHit2Command>(String("saberPolearmLegHit2").toLowerCase());
	commandFactory.registerCommand<SaberPolearmLegHit3Command>(String("saberPolearmLegHit3").toLowerCase());
	commandFactory.registerCommand<SaberPolearmSpinAttack1Command>(String("saberPolearmSpinAttack1").toLowerCase());
	commandFactory.registerCommand<SaberPolearmSpinAttack2Command>(String("saberPolearmSpinAttack2").toLowerCase());
	commandFactory.registerCommand<SaberPolearmSpinAttack3Command>(String("saberPolearmSpinAttack3").toLowerCase());
	commandFactory.registerCommand<SaberSlash1Command>(String("saberSlash1").toLowerCase());
	commandFactory.registerCommand<SaberSlash2Command>(String("saberSlash2").toLowerCase());
	commandFactory.registerCommand<SaberThrow1Command>(String("saberThrow1").toLowerCase());
	commandFactory.registerCommand<SaberThrow2Command>(String("saberThrow2").toLowerCase());
	commandFactory.registerCommand<SaberThrow3Command>(String("saberThrow3").toLowerCase());
	commandFactory.registerCommand<SampleCommand>(String("sample").toLowerCase());
	commandFactory.registerCommand<SampleDNACommand>(String("sampleDNA").toLowerCase());
	commandFactory.registerCommand<ScatterShot1Command>(String("scatterShot1").toLowerCase());
	commandFactory.registerCommand<ScatterShot2Command>(String("scatterShot2").toLowerCase());
	commandFactory.registerCommand<ScriptCommand>(String("script").toLowerCase());
	commandFactory.registerCommand<SearchCorpseCommand>(String("searchCorpse").toLowerCase());
	commandFactory.registerCommand<SecretSpawnSpamCommand>(String("secretSpawnSpam").toLowerCase());
	commandFactory.registerCommand<SeGogglesCommand>(String("seGoggles").toLowerCase());
	commandFactory.registerCommand<SelectDraftSchematicCommand>(String("selectDraftSchematic").toLowerCase());
	commandFactory.registerCommand<ServerCommand>(String("server").toLowerCase());
	commandFactory.registerCommand<ServerDestroyObjectCommand>(String("serverDestroyObject").toLowerCase());
	commandFactory.registerCommand<ServerSysGroupCommand>(String("serverSysGroup").toLowerCase());
	commandFactory.registerCommand<SetBiographyAdminCommand>(String("setBiographyAdmin").toLowerCase());
	commandFactory.registerCommand<SetBiographyCommand>(String("setBiography").toLowerCase());
	commandFactory.registerCommand<SetBoostmoraleCommand>(String("setBoostmorale").toLowerCase());
	commandFactory.registerCommand<SetChargeCommand>(String("setCharge").toLowerCase());
	commandFactory.registerCommand<SetCurrentSkillTitleCommand>(String("setCurrentSkillTitle").toLowerCase());
	commandFactory.registerCommand<SetExperienceCommand>(String("setExperience").toLowerCase());
	commandFactory.registerCommand<SetFactionCommand>(String("setFaction").toLowerCase());
	commandFactory.registerCommand<SetFactionStandingCommand>(String("setFactionStanding").toLowerCase());
	commandFactory.registerCommand<SetFirstNameCommand>(String("setFirstName").toLowerCase());
	commandFactory.registerCommand<SetFormupCommand>(String("setFormup").toLowerCase());
	commandFactory.registerCommand<SetGodModeCommand>(String("setGodMode").toLowerCase());
	commandFactory.registerCommand<SetHueCommand>(String("setHue").toLowerCase());
	commandFactory.registerCommand<SetIntimidateCommand>(String("setIntimidate").toLowerCase());
	commandFactory.registerCommand<SetLastNameCommand>(String("setLastName").toLowerCase());
	commandFactory.registerCommand<SetLoginMessageCommand>(String("setLoginMessage").toLowerCase());
	commandFactory.registerCommand<SetLoginTitleCommand>(String("setLoginTitle").toLowerCase());
	commandFactory.registerCommand<SetMatchMakingCharacterIdCommand>(String("setMatchMakingCharacterId").toLowerCase());
	commandFactory.registerCommand<SetMatchMakingPersonalIdCommand>(String("setMatchMakingPersonalId").toLowerCase());
	commandFactory.registerCommand<SetMaximumSpawnTimeCommand>(String("setMaximumSpawnTime").toLowerCase());
	commandFactory.registerCommand<SetMinimumSpawnTimeCommand>(String("setMinimumSpawnTime").toLowerCase());
	commandFactory.registerCommand<SetMoodCommand>(String("setMood").toLowerCase());
	commandFactory.registerCommand<SetMoodInternalCommand>(String("setMoodInternal").toLowerCase());
	commandFactory.registerCommand<SetNameCommand>(String("setName").toLowerCase());
	commandFactory.registerCommand<SetNameCommand>(String("setName").toLowerCase());
	commandFactory.registerCommand<SetOwnerCommand>(String("setOwner").toLowerCase());
	commandFactory.registerCommand<SetPerformanceBuffTargetCommand>(String("setPerformanceBuffTarget").toLowerCase());
	commandFactory.registerCommand<SetpermissionCommand>(String("setpermission").toLowerCase());
	commandFactory.registerCommand<SetPlanetLimitCommand>(String("setPlanetLimit").toLowerCase());
	commandFactory.registerCommand<SetPlayerAppearanceCommand>(String("setPlayerAppearance").toLowerCase());
	commandFactory.registerCommand<SetPlayerStateCommand>(String("setPlayerState").toLowerCase());
	commandFactory.registerCommand<SetprivacyCommand>(String("setprivacy").toLowerCase());
	commandFactory.registerCommand<SetPublicStateCommand>(String("setPublicState").toLowerCase());
	commandFactory.registerCommand<SetRankCommand>(String("setRank").toLowerCase());
	commandFactory.registerCommand<SetRetreatCommand>(String("setRetreat").toLowerCase());
	commandFactory.registerCommand<SetSpeedCommand>(String("setSpeed").toLowerCase());
	commandFactory.registerCommand<SetSpokenLanguageCommand>(String("setSpokenLanguage").toLowerCase());
	commandFactory.registerCommand<SetSteadyaimCommand>(String("setSteadyaim").toLowerCase());
	commandFactory.registerCommand<SetTEFCommand>(String("setTEF").toLowerCase());
	commandFactory.registerCommand<SetVeteranRewardCommand>(String("setVeteranReward").toLowerCase());
	commandFactory.registerCommand<SetWarcryCommand>(String("setWarcry").toLowerCase());
	commandFactory.registerCommand<SetWaypointActiveStatusCommand>(String("setWaypointActiveStatus").toLowerCase());
	commandFactory.registerCommand<SetWaypointNameCommand>(String("setWaypointName").toLowerCase());
	commandFactory.registerCommand<ShowCouncilRankCommand>(String("showCouncilRank").toLowerCase());
	commandFactory.registerCommand<ShowDanceVisualsCommand>(String("showDanceVisuals").toLowerCase());
	commandFactory.registerCommand<ShowFactionInformationCommand>(String("showFactionInformation").toLowerCase());
	commandFactory.registerCommand<ShowMusicianVisualsCommand>(String("showMusicianVisuals").toLowerCase());
	commandFactory.registerCommand<ShowPvPRatingCommand>(String("showPvPRating").toLowerCase());
	commandFactory.registerCommand<ShowSpawnRegionCommand>(String("showSpawnRegion").toLowerCase());
	commandFactory.registerCommand<SitServerCommand>(String("sitServer").toLowerCase());
	commandFactory.registerCommand<SkillCommand>(String("skill").toLowerCase());
	commandFactory.registerCommand<SmokebombCommand>(String("smokebomb").toLowerCase());
	commandFactory.registerCommand<SniperShotCommand>(String("sniperShot").toLowerCase());
	commandFactory.registerCommand<SnoopCommand>(String("snoop").toLowerCase());
	commandFactory.registerCommand<SocialCommand>(String("social").toLowerCase());
	commandFactory.registerCommand<SocialInternalCommand>(String("socialInternal").toLowerCase());
	commandFactory.registerCommand<SpatialChatCommand>(String("spatialChat").toLowerCase());
	commandFactory.registerCommand<SpatialChatInternalCommand>(String("spatialChatInternal").toLowerCase());
	commandFactory.registerCommand<SpawnStatusCommand>(String("spawnStatus").toLowerCase());
	commandFactory.registerCommand<SplitCreditsWithGroupCommand>(String("splitCreditsWithGroup").toLowerCase());
	commandFactory.registerCommand<SpotlightCommand>(String("spotlight").toLowerCase());
	commandFactory.registerCommand<SprayShotCommand>(String("sprayShot").toLowerCase());
	commandFactory.registerCommand<StandCommand>(String("stand").toLowerCase());
	commandFactory.registerCommand<StartBandCommand>(String("startBand").toLowerCase());
	commandFactory.registerCommand<StartCitySpawnerCommand>(String("startCitySpawner").toLowerCase());
	commandFactory.registerCommand<StartDanceCommand>(String("startDance").toLowerCase());
	commandFactory.registerCommand<StartleShot1Command>(String("startleShot1").toLowerCase());
	commandFactory.registerCommand<StartleShot2Command>(String("startleShot2").toLowerCase());
	commandFactory.registerCommand<StartMusicCommand>(String("startMusic").toLowerCase());
	commandFactory.registerCommand<StartSpawnerCommand>(String("startSpawner").toLowerCase());
	commandFactory.registerCommand<StartTargetSpawnerCommand>(String("startTargetSpawner").toLowerCase());
	commandFactory.registerCommand<StartTraceLoggingCommand>(String("startTraceLogging").toLowerCase());
	commandFactory.registerCommand<StatCommand>(String("stat").toLowerCase());
	commandFactory.registerCommand<SteadyaimCommand>(String("steadyaim").toLowerCase());
	commandFactory.registerCommand<StopBandCommand>(String("stopBand").toLowerCase());
	commandFactory.registerCommand<StopBleedingCommand>(String("stopBleeding").toLowerCase());
	commandFactory.registerCommand<StopCitySpawnerCommand>(String("stopCitySpawner").toLowerCase());
	commandFactory.registerCommand<StopCraftingSessionCommand>(String("stopCraftingSession").toLowerCase());
	commandFactory.registerCommand<StopDanceCommand>(String("stopDance").toLowerCase());
	commandFactory.registerCommand<StoplisteningCommand>(String("stoplistening").toLowerCase());
	commandFactory.registerCommand<StopMusicCommand>(String("stopMusic").toLowerCase());
	commandFactory.registerCommand<StoppingShotCommand>(String("stoppingShot").toLowerCase());
	commandFactory.registerCommand<StopSpawnerCommand>(String("stopSpawner").toLowerCase());
	commandFactory.registerCommand<StopTargetSpawnerCommand>(String("stopTargetSpawner").toLowerCase());
	commandFactory.registerCommand<StopTraceLoggingCommand>(String("stopTraceLogging").toLowerCase());
	commandFactory.registerCommand<StopwatchingCommand>(String("stopwatching").toLowerCase());
	commandFactory.registerCommand<StrafeShot1Command>(String("strafeShot1").toLowerCase());
	commandFactory.registerCommand<StrafeShot2Command>(String("strafeShot2").toLowerCase());
	commandFactory.registerCommand<StructurestatusCommand>(String("structurestatus").toLowerCase());
	commandFactory.registerCommand<StunAttackCommand>(String("stunAttack").toLowerCase());
}
