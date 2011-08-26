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
#include "server/zone/objects/creature/CreatureLocomotion.h"
#include "server/zone/templates/datatables/DataTableIff.h"
#include "server/zone/templates/datatables/DataTableRow.h"

#include "server/zone/ZoneProcessServer.h"
#include "CommandList.h"

CommandList* CommandConfigManager::slashCommands = NULL;
ZoneProcessServer* CommandConfigManager::server = NULL;

CommandConfigManager::CommandConfigManager(ZoneProcessServer* serv) {
	server = serv;

	init();

	setLogging(false);
	setLoggingName("CommandConfigManager");

	registerFunctions();
	registerGlobals();
	registerCommands();
}

void CommandConfigManager::loadCommandData() {
	IffStream* iffStream = TemplateManager::instance()->openIffFile("datatables/command/command_table.iff");

	if (iffStream == NULL) {
		error("Could not load commands.");
		return;
	}

	DataTableIff dtiff;
	dtiff.readObject(iffStream);

	delete iffStream;

	int i;
	for (i = 0; i < dtiff.getTotalRows(); ++i) {
		DataTableRow* row = dtiff.getRow(i);
		QueueCommand* slashCommand;

		// TODO: load in datatables
		bool disabled; // check disabled first and don't load it

		String name;
		bool combat;
		int targetType;
		float maxRangeToTarget;
		String characterAbility;
		float defaultTime;
		int defaultPriority;
		uint64 stateMask = 0; // need to construct statemask
		bool state;
		bool position; // need to add positions one by one

		row->getValue(CommandConfigManager::COMMANDNAME, name);
		slashCommand = createCommand(name);

		if (slashCommand == NULL) {
			error("Could not create command " + name);
			continue;
		}

		row->getValue(CommandConfigManager::ADDTOCOMBATQUEUE, combat);
		slashCommand->setAddToCombatQueue(combat);

		row->getValue(CommandConfigManager::TARGETTYPE, targetType);
		slashCommand->setTargetType(targetType);

		row->getValue(CommandConfigManager::MAXRANGETOTARGET, maxRangeToTarget);
		slashCommand->setMaxRange(maxRangeToTarget);

		row->getValue(CommandConfigManager::CHARACTERABILITY, characterAbility);
		slashCommand->setCharacterAbility(characterAbility);

		row->getValue(CommandConfigManager::DEFAULTTIME, defaultTime);
		slashCommand->setDefaultTime(defaultTime);

		row->getValue(CommandConfigManager::DEFAULTPRIORITY, defaultPriority);
		slashCommand->setDefaultPriority(defaultPriority);

		row->getValue(CommandConfigManager::COVER, state);
		if (state) stateMask |= CreatureState::COVER;
		row->getValue(CommandConfigManager::COMBAT, state);
		if (state) stateMask |= CreatureState::COMBAT;
		row->getValue(CommandConfigManager::PEACE, state);
		if (state) stateMask |= CreatureState::PEACE;
		row->getValue(CommandConfigManager::AIMING, state);
		if (state) stateMask |= CreatureState::AIMING;
		row->getValue(CommandConfigManager::ALERT, state);
		if (state) stateMask |= CreatureState::ALERT;
		row->getValue(CommandConfigManager::BERSERK, state);
		if (state) stateMask |= CreatureState::BERSERK;
		row->getValue(CommandConfigManager::FEIGNDEATH, state);
		if (state) stateMask |= CreatureState::FEIGNDEATH;
		row->getValue(CommandConfigManager::COMBATATTITUDEEVASIVE, state);
		if (state) stateMask |= CreatureState::COMBATATTITUDEEVASIVE;
		row->getValue(CommandConfigManager::COMBATATTITUDENORMAL, state);
		if (state) stateMask |= CreatureState::COMBATATTITUDENORMAL;
		row->getValue(CommandConfigManager::COMBATATTITUDEAGGRESSIVE, state);
		if (state) stateMask |= CreatureState::COMBATATTITUDEAGGRESSIVE;
		row->getValue(CommandConfigManager::TUMBLING, state);
		if (state) stateMask |= CreatureState::TUMBLING;
		row->getValue(CommandConfigManager::RALLIED, state);
		if (state) stateMask |= CreatureState::RALLIED;
		row->getValue(CommandConfigManager::STUNNED, state);
		if (state) stateMask |= CreatureState::STUNNED;
		row->getValue(CommandConfigManager::BLINDED, state);
		if (state) stateMask |= CreatureState::BLINDED;
		row->getValue(CommandConfigManager::DIZZY, state);
		if (state) stateMask |= CreatureState::DIZZY;
		row->getValue(CommandConfigManager::INTIMIDATED, state);
		if (state) stateMask |= CreatureState::INTIMIDATED;
		row->getValue(CommandConfigManager::IMMOBILIZED, state);
		if (state) stateMask |= CreatureState::IMMOBILIZED;
		row->getValue(CommandConfigManager::FROZEN, state);
		if (state) stateMask |= CreatureState::FROZEN;
		row->getValue(CommandConfigManager::SWIMMING, state);
		if (state) stateMask |= CreatureState::SWIMMING;
		row->getValue(CommandConfigManager::SITTINGONCHAIR, state);
		if (state) stateMask |= CreatureState::SITTINGONCHAIR;
		row->getValue(CommandConfigManager::CRAFTING, state);
		if (state) stateMask |= CreatureState::CRAFTING;
		row->getValue(CommandConfigManager::GLOWINGJEDI, state);
		if (state) stateMask |= CreatureState::GLOWINGJEDI;
		row->getValue(CommandConfigManager::MASKSCENT, state);
		if (state) stateMask |= CreatureState::MASKSCENT;
		row->getValue(CommandConfigManager::POISONED, state);
		if (state) stateMask |= CreatureState::POISONED;
		row->getValue(CommandConfigManager::BLEEDING, state);
		if (state) stateMask |= CreatureState::BLEEDING;
		row->getValue(CommandConfigManager::DISEASED, state);
		if (state) stateMask |= CreatureState::DISEASED;
		row->getValue(CommandConfigManager::ONFIRE, state);
		if (state) stateMask |= CreatureState::ONFIRE;
		row->getValue(CommandConfigManager::RIDINGMOUNT, state);
		if (state) stateMask |= CreatureState::RIDINGMOUNT;
		row->getValue(CommandConfigManager::MOUNTEDCREATURE, state);
		if (state) stateMask |= CreatureState::MOUNTEDCREATURE;
		row->getValue(CommandConfigManager::PILOTINGSHIP, state);
		if (state) stateMask |= CreatureState::PILOTINGSHIP;
		row->getValue(CommandConfigManager::PILOTINGPOBSHIP, state);
		if (state) stateMask |= CreatureState::PILOTINGPOBSHIP;
		row->getValue(CommandConfigManager::SHIPOPERATIONS, state);
		if (state) stateMask |= CreatureState::SHIPOPERATIONS;
		row->getValue(CommandConfigManager::SHIPGUNNER, state);
		if (state) stateMask |= CreatureState::SHIPGUNNER;
		row->getValue(CommandConfigManager::SHIPINTERIOR, state);
		if (state) stateMask |= CreatureState::SHIPINTERIOR;

		slashCommand->setStateMask(stateMask);

		row->getValue(CommandConfigManager::STANDING, position);
		if (!position) slashCommand->addInvalidLocomotion(CreatureLocomotion::STANDING);
		row->getValue(CommandConfigManager::SNEAKING, position);
		if (!position) slashCommand->addInvalidLocomotion(CreatureLocomotion::SNEAKING);
		row->getValue(CommandConfigManager::WALKING, position);
		if (!position) slashCommand->addInvalidLocomotion(CreatureLocomotion::WALKING);
		row->getValue(CommandConfigManager::RUNNING, position);
		if (!position) slashCommand->addInvalidLocomotion(CreatureLocomotion::RUNNING);
		row->getValue(CommandConfigManager::KNEELING, position);
		if (!position) slashCommand->addInvalidLocomotion(CreatureLocomotion::KNEELING);
		row->getValue(CommandConfigManager::CROUCHSNEAKING, position);
		if (!position) slashCommand->addInvalidLocomotion(CreatureLocomotion::CROUCHSNEAKING);
		row->getValue(CommandConfigManager::CROUCHWALKING, position);
		if (!position) slashCommand->addInvalidLocomotion(CreatureLocomotion::CROUCHWALKING);
		row->getValue(CommandConfigManager::PRONE, position);
		if (!position) slashCommand->addInvalidLocomotion(CreatureLocomotion::PRONE);
		row->getValue(CommandConfigManager::CRAWLING, position);
		if (!position) slashCommand->addInvalidLocomotion(CreatureLocomotion::CRAWLING);
		row->getValue(CommandConfigManager::CLIMBINGSTATIONARY, position);
		if (!position) slashCommand->addInvalidLocomotion(CreatureLocomotion::CLIMBINGSTATIONARY);
		row->getValue(CommandConfigManager::CLIMBING, position);
		if (!position) slashCommand->addInvalidLocomotion(CreatureLocomotion::CLIMBING);
		row->getValue(CommandConfigManager::HOVERING, position);
		if (!position) slashCommand->addInvalidLocomotion(CreatureLocomotion::HOVERING);
		row->getValue(CommandConfigManager::FLYING, position);
		if (!position) slashCommand->addInvalidLocomotion(CreatureLocomotion::FLYING);
		row->getValue(CommandConfigManager::LYINGDOWN, position);
		if (!position) slashCommand->addInvalidLocomotion(CreatureLocomotion::LYINGDOWN);
		row->getValue(CommandConfigManager::SITTING, position);
		if (!position) slashCommand->addInvalidLocomotion(CreatureLocomotion::SITTING);
		row->getValue(CommandConfigManager::SKILLANIMATING, position);
		if (!position) slashCommand->addInvalidLocomotion(CreatureLocomotion::SKILLANIMATING);
		row->getValue(CommandConfigManager::DRIVINGVEHICLE, position);
		if (!position) slashCommand->addInvalidLocomotion(CreatureLocomotion::DRIVINGVEHICLE);
		row->getValue(CommandConfigManager::RIDINGCREATURE, position);
		if (!position) slashCommand->addInvalidLocomotion(CreatureLocomotion::RIDINGCREATURE);
		row->getValue(CommandConfigManager::KNOCKEDDOWN, position);
		if (!position) slashCommand->addInvalidLocomotion(CreatureLocomotion::KNOCKEDDOWN);
		row->getValue(CommandConfigManager::INCAPACITATED, position);
		if (!position) slashCommand->addInvalidLocomotion(CreatureLocomotion::INCAPACITATED);
		row->getValue(CommandConfigManager::DEAD, position);
		if (!position) slashCommand->addInvalidLocomotion(CreatureLocomotion::DEAD);
		row->getValue(CommandConfigManager::BLOCKING, position);
		if (!position) slashCommand->addInvalidLocomotion(CreatureLocomotion::BLOCKING);
	}

	info("Loaded " + String::valueOf(i) + " commands.");
}

QueueCommand* CommandConfigManager::createCommand(String name) {
	QueueCommand* command = NULL;

	command = commandFactory.createCommand(name, name, server);

	if (command == NULL)
		return command;

	slashCommands->put(command);

	return command;
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
	lua_register(getLuaState(), "AddCommand", addCommand);
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
	setGlobalLong("DIZZY_STATE", CreatureState::DIZZY);
	setGlobalLong("INTIMIDATED_STATE", CreatureState::INTIMIDATED);
	setGlobalLong("IMMOBILIZED_STATE", CreatureState::IMMOBILIZED);
	setGlobalLong("FROZEN_STATE", CreatureState::FROZEN);
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
	setGlobalLong("PILOTINGSHIP_STATE", CreatureState::PILOTINGSHIP);
	setGlobalLong("PILOTINGPOBSHIP_STATE", CreatureState::PILOTINGPOBSHIP);
	setGlobalLong("SHIPOPERATIONS_STATE", CreatureState::SHIPOPERATIONS);
	setGlobalLong("SHIPGUNNER_STATE", CreatureState::SHIPGUNNER);
	setGlobalLong("SHIPINTERIOR_STATE", CreatureState::SHIPINTERIOR);

	// locomotion
	setGlobalInt("INVALID_LOCOMOTION", CreaturePosture::INVALID);
	setGlobalInt("STANDING_LOCOMOTION", CreatureLocomotion::STANDING);
	setGlobalInt("SNEAKING_LOCOMOTION", CreatureLocomotion::SNEAKING);
	setGlobalInt("WALKING_LOCOMOTION", CreatureLocomotion::WALKING);
	setGlobalInt("RUNNING_LOCOMOTION", CreatureLocomotion::RUNNING);
	setGlobalInt("KNEELING_LOCOMOTION", CreatureLocomotion::KNEELING);
	setGlobalInt("CROUCHSNEAKING_LOCOMOTION", CreatureLocomotion::CROUCHSNEAKING);
	setGlobalInt("CROUCHWALKING_LOCOMOTION", CreatureLocomotion::CROUCHWALKING);
	setGlobalInt("PRONE_LOCOMOTION", CreatureLocomotion::PRONE);
	setGlobalInt("CRAWLING_LOCOMOTION", CreatureLocomotion::CRAWLING);
	setGlobalInt("CLIMBINGSTATIONARY_LOCOMOTION", CreatureLocomotion::CLIMBINGSTATIONARY);
	setGlobalInt("CLIMBING_LOCOMOTION", CreatureLocomotion::CLIMBING);
	setGlobalInt("HOVERING_LOCOMOTION", CreatureLocomotion::HOVERING);
	setGlobalInt("FLYING_LOCOMOTION", CreatureLocomotion::FLYING);
	setGlobalInt("LYINGDOWN_LOCOMOTION", CreatureLocomotion::LYINGDOWN);
	setGlobalInt("SITTING_LOCOMOTION", CreatureLocomotion::SITTING);
	setGlobalInt("SKILLANIMATING_LOCOMOTION", CreatureLocomotion::SKILLANIMATING);
	setGlobalInt("DRIVINGVEHICLE_LOCOMOTION", CreatureLocomotion::DRIVINGVEHICLE);
	setGlobalInt("RIDINGCREATURE_LOCOMOTION", CreatureLocomotion::RIDINGCREATURE);
	setGlobalInt("KNOCKEDDOWN_LOCOMOTION", CreatureLocomotion::KNOCKEDDOWN);
	setGlobalInt("INCAPACITATED_LOCOMOTION", CreatureLocomotion::INCAPACITATED);
	setGlobalInt("DEAD_LOCOMOTION", CreatureLocomotion::DEAD);
	setGlobalInt("BLOCKING_LOCOMOTION", CreatureLocomotion::BLOCKING);
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
	command->setInvalidLocomotions(field);

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
	// TODO: load the options from the iff's, then override from luas.
	// TODO: move the modifiers from the command headers to the luas.
	// TODO: huge! turn all this into a factory method

	parseOptions(slashcommand, slashCommand);

	slashCommands->put(slashCommand);

	/*String alternativeNames = slashcommand.getStringField("alternativeNames");
	if (!alternativeNames.isEmpty())
		parseAlternativeNames(alternativeNames, slashCommand);*/
}

int CommandConfigManager::addCommand(lua_State* L) {
	LuaObject slashcommand(L);
	if (!slashcommand.isValidTable())
		return 0;

	// get object from map, then overwrite/fill in variables
	//String name = slashcommand.getStringField("name");

	return 1;
}

void CommandConfigManager::registerCommands() {
	commandFactory.registerCommand<ActionShot1Command>("actionShot1");
	commandFactory.registerCommand<ActionShot2Command>("actionShot2");
	commandFactory.registerCommand<ActivateCloneCommand>("activateClone");
	commandFactory.registerCommand<ActivateQuestCommand>("activateQuest");
	commandFactory.registerCommand<AddAllowedPlayerCommand>("addAllowedPlayer");
	commandFactory.registerCommand<AddBannedPlayerCommand>("addBannedPlayer");
	commandFactory.registerCommand<AddFriendCommand>("addFriend");
	commandFactory.registerCommand<AddIgnoreCommand>("addIgnore");
	commandFactory.registerCommand<AddMapLocationCommand>("addMapLocation");
	commandFactory.registerCommand<AddPowerCommand>("addPower");
	commandFactory.registerCommand<AdjustLotCountCommand>("adjustLotCount");
	commandFactory.registerCommand<AiIgnoreCommand>("aiIgnore");
	commandFactory.registerCommand<AimCommand>("aim");
	commandFactory.registerCommand<AlertCommand>("alert");
	commandFactory.registerCommand<AnimalAttackCommand>("animalAttack");
	commandFactory.registerCommand<AnimalCalmCommand>("animalCalm");
	commandFactory.registerCommand<AnimalScareCommand>("animalScare");
	commandFactory.registerCommand<AnonCommand>("anon");
	commandFactory.registerCommand<ApplyDiseaseCommand>("applyDisease");
	commandFactory.registerCommand<ApplyPoisonCommand>("applyPoison");
	commandFactory.registerCommand<ApplyPowerupCommand>("applyPowerup");
	commandFactory.registerCommand<AreatrackCommand>("areatrack");
	commandFactory.registerCommand<AssignDroidCommand>("assignDroid");
	commandFactory.registerCommand<AssistCommand>("assist");
	commandFactory.registerCommand<AssociateDroidControlDeviceWithShipCommand>("associateDroidControlDeviceWithShip");
	commandFactory.registerCommand<AttackCommand>("attack");
	commandFactory.registerCommand<AuctionCommand>("auction");
	commandFactory.registerCommand<AuctionAcceptCommand>("auctionAccept");
	commandFactory.registerCommand<AuctionBidCommand>("auctionBid");
	commandFactory.registerCommand<AuctionCancelCommand>("auctionCancel");
	commandFactory.registerCommand<AuctionCreateCommand>("auctionCreate");
	commandFactory.registerCommand<AuctionQueryCommand>("auctionQuery");
	commandFactory.registerCommand<AuctionRetrieveCommand>("auctionRetrieve");
	commandFactory.registerCommand<AuctionsayCommand>("auctionsay");
	commandFactory.registerCommand<AvoidIncapacitationCommand>("avoidIncapacitation");
	commandFactory.registerCommand<BandFlourishCommand>("bandFlourish");
	commandFactory.registerCommand<BattlefieldStatusCommand>("battlefieldStatus");
	commandFactory.registerCommand<Berserk1Command>("berserk1");
	commandFactory.registerCommand<Berserk2Command>("berserk2");
	commandFactory.registerCommand<BetCommand>("bet");
	commandFactory.registerCommand<BleedingShotCommand>("bleedingShot");
	commandFactory.registerCommand<BlindAttackCommand>("blindAttack");
	commandFactory.registerCommand<BoardShuttleCommand>("boardShuttle");
	commandFactory.registerCommand<BodyShot1Command>("bodyShot1");
	commandFactory.registerCommand<BodyShot2Command>("bodyShot2");
	commandFactory.registerCommand<BodyShot3Command>("bodyShot3");
	commandFactory.registerCommand<BoostmoraleCommand>("boostmorale");
	commandFactory.registerCommand<BroadcastCommand>("broadcast");
	commandFactory.registerCommand<BroadcastAreaCommand>("broadcastArea");
	commandFactory.registerCommand<BroadcastGalaxyCommand>("broadcastGalaxy");
	commandFactory.registerCommand<BroadcastPlanetCommand>("broadcastPlanet");
	commandFactory.registerCommand<BurstRunCommand>("burstRun");
	commandFactory.registerCommand<BurstShot1Command>("burstShot1");
	commandFactory.registerCommand<BurstShot2Command>("burstShot2");
	commandFactory.registerCommand<CancelCraftingSessionCommand>("cancelCraftingSession");
	commandFactory.registerCommand<CenterOfBeingCommand>("centerOfBeing");
	commandFactory.registerCommand<ChangeBandMusicCommand>("changeBandMusic");
	commandFactory.registerCommand<ChangeDanceCommand>("changeDance");
	commandFactory.registerCommand<ChangeMusicCommand>("changeMusic");
	commandFactory.registerCommand<ChannelForceCommand>("channelForce");
	commandFactory.registerCommand<ChargeShot1Command>("chargeShot1");
	commandFactory.registerCommand<ChargeShot2Command>("chargeShot2");
	commandFactory.registerCommand<CheckForceStatusCommand>("checkForceStatus");
	commandFactory.registerCommand<CitybanCommand>("cityban");
	commandFactory.registerCommand<CitypardonCommand>("citypardon");
	commandFactory.registerCommand<ClaimVeteranRewardCommand>("claimVeteranReward");
	commandFactory.registerCommand<ClearCompletedQuestCommand>("clearCompletedQuest");
	commandFactory.registerCommand<ClearVeteranRewardCommand>("clearVeteranReward");
	commandFactory.registerCommand<ClientQualifiedForSkillCommand>("clientQualifiedForSkill");
	commandFactory.registerCommand<CloneCommand>("clone");
	commandFactory.registerCommand<CloseContainerCommand>("closeContainer");
	commandFactory.registerCommand<ColorlightsCommand>("colorlights");
	commandFactory.registerCommand<CombatCommand>("combat");
	commandFactory.registerCommand<CombatEscapeCommand>("combatEscape");
	commandFactory.registerCommand<CombatModeCheckCommand>("combatModeCheck");
	commandFactory.registerCommand<CombatSpamCommand>("combatSpam");
	commandFactory.registerCommand<CombatTargetCommand>("combatTarget");
	commandFactory.registerCommand<CompleteQuestCommand>("completeQuest");
	commandFactory.registerCommand<ConcealCommand>("conceal");
	commandFactory.registerCommand<ConcealShotCommand>("concealShot");
	commandFactory.registerCommand<ConfusionShotCommand>("confusionShot");
	commandFactory.registerCommand<ConsentCommand>("consent");
	commandFactory.registerCommand<CorpseCommand>("corpse");
	commandFactory.registerCommand<CounterAttackCommand>("counterAttack");
	commandFactory.registerCommand<CoupDeGraceCommand>("coupDeGrace");
	commandFactory.registerCommand<CraftCommand>("craft");
	commandFactory.registerCommand<CreateCreatureCommand>("createCreature");
	commandFactory.registerCommand<CreateManfSchematicCommand>("createManfSchematic");
	commandFactory.registerCommand<CreateMissionElementCommand>("createMissionElement");
	commandFactory.registerCommand<CreateNPCCommand>("createNPC");
	commandFactory.registerCommand<CreatePrototypeCommand>("createPrototype");
	commandFactory.registerCommand<CreateSpawningElementCommand>("createSpawningElement");
	commandFactory.registerCommand<CreateSpawningElementWithDifficultyCommand>("createSpawningElementWithDifficulty");
	commandFactory.registerCommand<CreatureAreaAttackCommand>("creatureAreaAttack");
	commandFactory.registerCommand<CreatureAreaBleedingCommand>("creatureAreaBleeding");
	commandFactory.registerCommand<CreatureAreaComboCommand>("creatureAreaCombo");
	commandFactory.registerCommand<CreatureAreaDiseaseCommand>("creatureAreaDisease");
	commandFactory.registerCommand<CreatureAreaKnockdownCommand>("creatureAreaKnockdown");
	commandFactory.registerCommand<CreatureAreaPoisonCommand>("creatureAreaPoison");
	commandFactory.registerCommand<CreditsCommand>("credits");
	commandFactory.registerCommand<CripplingShotCommand>("cripplingShot");
	commandFactory.registerCommand<CsAppendCommentCommand>("csAppendComment");
	commandFactory.registerCommand<CsCancelTicketCommand>("csCancelTicket");
	commandFactory.registerCommand<CsConnectPlayerCommand>("csConnectPlayer");
	commandFactory.registerCommand<CsCreateTicketCommand>("csCreateTicket");
	commandFactory.registerCommand<CsDisconnectPlayerCommand>("csDisconnectPlayer");
	commandFactory.registerCommand<CsGetArticleCommand>("csGetArticle");
	commandFactory.registerCommand<CsGetCommentsCommand>("csGetComments");
	commandFactory.registerCommand<CsGetTicketsCommand>("csGetTickets");
	commandFactory.registerCommand<CsRequestCategoriesCommand>("csRequestCategories");
	commandFactory.registerCommand<CsSearchKnowledgeBaseCommand>("csSearchKnowledgeBase");
	commandFactory.registerCommand<CuiConsentResponseCommand>("cuiConsentResponse");
	commandFactory.registerCommand<CureDiseaseCommand>("cureDisease");
	commandFactory.registerCommand<CurePoisonCommand>("curePoison");
	commandFactory.registerCommand<CustomizeDroidCommand>("customizeDroid");
	commandFactory.registerCommand<CustomizeVehicleCommand>("customizeVehicle");
	commandFactory.registerCommand<DatabaseCommand>("database");
	commandFactory.registerCommand<DazzleCommand>("dazzle");
	commandFactory.registerCommand<DeactivateQuestCommand>("deactivateQuest");
	commandFactory.registerCommand<DeathBlowCommand>("deathBlow");
	commandFactory.registerCommand<DeathCountCommand>("deathCount");
	commandFactory.registerCommand<DeclareOvertCommand>("declareOvert");
	commandFactory.registerCommand<DeclareresidenceCommand>("declareresidence");
	commandFactory.registerCommand<DeclineCommand>("decline");
	commandFactory.registerCommand<DefaultAttackCommand>("defaultAttack");
	commandFactory.registerCommand<DefuseMinefieldCommand>("defuseMinefield");
	commandFactory.registerCommand<DelegateFactionPointsCommand>("delegateFactionPoints");
	commandFactory.registerCommand<DenyServiceCommand>("denyService");
	commandFactory.registerCommand<DeployTrapCommand>("deployTrap");
	commandFactory.registerCommand<DestroyCommand>("destroy");
	commandFactory.registerCommand<DestroystructureCommand>("destroystructure");
	commandFactory.registerCommand<DetonateDroidCommand>("detonateDroid");
	commandFactory.registerCommand<DiagnoseCommand>("diagnose");
	commandFactory.registerCommand<DisarmingShot1Command>("disarmingShot1");
	commandFactory.registerCommand<DisarmingShot2Command>("disarmingShot2");
	commandFactory.registerCommand<DisbandCommand>("disband");
	commandFactory.registerCommand<DismissGroupMemberCommand>("dismissGroupMember");
	commandFactory.registerCommand<DismountCommand>("dismount");
	commandFactory.registerCommand<DismountandstoreCommand>("dismountandstore");
	commandFactory.registerCommand<DistractCommand>("distract");
	commandFactory.registerCommand<DiveShotCommand>("diveShot");
	commandFactory.registerCommand<DizzyAttackCommand>("dizzyAttack");
	commandFactory.registerCommand<DoubleTapCommand>("doubleTap");
	commandFactory.registerCommand<DragIncapacitatedPlayerCommand>("dragIncapacitatedPlayer");
	commandFactory.registerCommand<DrainForceCommand>("drainForce");
	commandFactory.registerCommand<DuelCommand>("duel");
	commandFactory.registerCommand<DumpTargetInformationCommand>("dumpTargetInformation");
	commandFactory.registerCommand<DumpZoneInformationCommand>("dumpZoneInformation");
	commandFactory.registerCommand<EatCommand>("eat");
	commandFactory.registerCommand<EditAppearanceCommand>("editAppearance");
	commandFactory.registerCommand<EditBankCommand>("editBank");
	commandFactory.registerCommand<EditBankAccountCommand>("editBankAccount");
	commandFactory.registerCommand<EditStatsCommand>("editStats");
	commandFactory.registerCommand<EmboldenpetsCommand>("emboldenpets");
	commandFactory.registerCommand<EmptyMailTargetCommand>("emptyMailTarget");
	commandFactory.registerCommand<EndDuelCommand>("endDuel");
	commandFactory.registerCommand<EnragepetsCommand>("enragepets");
	commandFactory.registerCommand<EquilibriumCommand>("equilibrium");
	commandFactory.registerCommand<ExecuteKnowledgeBaseMessageCommand>("executeKnowledgeBaseMessage");
	commandFactory.registerCommand<ExtinguishFireCommand>("extinguishFire");
	commandFactory.registerCommand<ExtractObjectCommand>("extractObject");
	commandFactory.registerCommand<EyeShotCommand>("eyeShot");
	commandFactory.registerCommand<FactoryCrateSplitCommand>("factoryCrateSplit");
	commandFactory.registerCommand<FanShotCommand>("fanShot");
	commandFactory.registerCommand<FastBlastCommand>("fastBlast");
	commandFactory.registerCommand<FeignDeathCommand>("feignDeath");
	commandFactory.registerCommand<FindCommand>("find");
	commandFactory.registerCommand<FindFriendCommand>("findFriend");
	commandFactory.registerCommand<FindFriendCommand>("findFriend");
	commandFactory.registerCommand<FindMyTrainerCommand>("findMyTrainer");
	commandFactory.registerCommand<FindObjectCommand>("findObject");
	commandFactory.registerCommand<FindPlayerCommand>("findPlayer");
	commandFactory.registerCommand<FireAcidCone1Command>("fireAcidCone1");
	commandFactory.registerCommand<FireAcidCone2Command>("fireAcidCone2");
	commandFactory.registerCommand<FireAcidSingle1Command>("fireAcidSingle1");
	commandFactory.registerCommand<FireAcidSingle2Command>("fireAcidSingle2");
	commandFactory.registerCommand<FireHeavyWeaponCommand>("fireHeavyWeapon");
	commandFactory.registerCommand<FirejetCommand>("firejet");
	commandFactory.registerCommand<FireLightningCone1Command>("fireLightningCone1");
	commandFactory.registerCommand<FireLightningCone2Command>("fireLightningCone2");
	commandFactory.registerCommand<FireLightningSingle1Command>("fireLightningSingle1");
	commandFactory.registerCommand<FireLightningSingle2Command>("fireLightningSingle2");
	commandFactory.registerCommand<FirstAidCommand>("firstAid");
	commandFactory.registerCommand<FishCommand>("fish");
	commandFactory.registerCommand<FlameCone1Command>("flameCone1");
	commandFactory.registerCommand<FlameCone2Command>("flameCone2");
	commandFactory.registerCommand<FlameSingle1Command>("flameSingle1");
	commandFactory.registerCommand<FlameSingle2Command>("flameSingle2");
	commandFactory.registerCommand<FlashSpeederCommand>("flashSpeeder");
	commandFactory.registerCommand<FlourishCommand>("flourish");
	commandFactory.registerCommand<FlurryShot1Command>("flurryShot1");
	commandFactory.registerCommand<FlurryShot2Command>("flurryShot2");
	commandFactory.registerCommand<FlushingShot1Command>("flushingShot1");
	commandFactory.registerCommand<FlushingShot2Command>("flushingShot2");
	commandFactory.registerCommand<ForageCommand>("forage");
	commandFactory.registerCommand<ForceAbsorb1Command>("forceAbsorb1");
	commandFactory.registerCommand<ForceAbsorb2Command>("forceAbsorb2");
	commandFactory.registerCommand<ForceArmor1Command>("forceArmor1");
	commandFactory.registerCommand<ForceArmor2Command>("forceArmor2");
	commandFactory.registerCommand<ForceChokeCommand>("forceChoke");
	commandFactory.registerCommand<ForceCommandCommand>("forceCommand");
	commandFactory.registerCommand<ForceCureDiseaseCommand>("forceCureDisease");
	commandFactory.registerCommand<ForceCurePoisonCommand>("forceCurePoison");
	commandFactory.registerCommand<ForceFeedback1Command>("forceFeedback1");
	commandFactory.registerCommand<ForceFeedback2Command>("forceFeedback2");
	commandFactory.registerCommand<ForceIntimidate1Command>("forceIntimidate1");
	commandFactory.registerCommand<ForceIntimidate2Command>("forceIntimidate2");
	commandFactory.registerCommand<ForceKnockdown1Command>("forceKnockdown1");
	commandFactory.registerCommand<ForceKnockdown2Command>("forceKnockdown2");
	commandFactory.registerCommand<ForceKnockdown3Command>("forceKnockdown3");
	commandFactory.registerCommand<ForceLightningCone1Command>("forceLightningCone1");
	commandFactory.registerCommand<ForceLightningCone2Command>("forceLightningCone2");
	commandFactory.registerCommand<ForceLightningSingle1Command>("forceLightningSingle1");
	commandFactory.registerCommand<ForceLightningSingle2Command>("forceLightningSingle2");
	commandFactory.registerCommand<ForceMeditateCommand>("forceMeditate");
	commandFactory.registerCommand<ForceOfWillCommand>("forceOfWill");
	commandFactory.registerCommand<ForceProtectionCommand>("forceProtection");
	commandFactory.registerCommand<ForceResistBleedingCommand>("forceResistBleeding");
	commandFactory.registerCommand<ForceResistDiseaseCommand>("forceResistDisease");
	commandFactory.registerCommand<ForceResistPoisonCommand>("forceResistPoison");
	commandFactory.registerCommand<ForceResistStatesCommand>("forceResistStates");
	commandFactory.registerCommand<ForceRun1Command>("forceRun1");
	commandFactory.registerCommand<ForceRun2Command>("forceRun2");
	commandFactory.registerCommand<ForceRun3Command>("forceRun3");
	commandFactory.registerCommand<ForceShield1Command>("forceShield1");
	commandFactory.registerCommand<ForceShield2Command>("forceShield2");
	commandFactory.registerCommand<ForceSpeed1Command>("forceSpeed1");
	commandFactory.registerCommand<ForceSpeed2Command>("forceSpeed2");
	commandFactory.registerCommand<ForceThrow1Command>("forceThrow1");
	commandFactory.registerCommand<ForceThrow2Command>("forceThrow2");
	commandFactory.registerCommand<ForceWeaken1Command>("forceWeaken1");
	commandFactory.registerCommand<ForceWeaken2Command>("forceWeaken2");
	commandFactory.registerCommand<FormupCommand>("formup");
	commandFactory.registerCommand<FreezePlayerCommand>("freezePlayer");
	commandFactory.registerCommand<FullAutoArea1Command>("fullAutoArea1");
	commandFactory.registerCommand<FullAutoArea2Command>("fullAutoArea2");
	commandFactory.registerCommand<FullAutoSingle1Command>("fullAutoSingle1");
	commandFactory.registerCommand<FullAutoSingle2Command>("fullAutoSingle2");
	commandFactory.registerCommand<GCommand>("g");
	commandFactory.registerCommand<GallopCommand>("gallop");
	commandFactory.registerCommand<GallopStopCommand>("gallopStop");
	commandFactory.registerCommand<GcCommand>("gc");
	commandFactory.registerCommand<GcwStatusCommand>("gcwStatus");
	commandFactory.registerCommand<GenerateCraftedItemCommand>("generateCraftedItem");
	commandFactory.registerCommand<GetAccountInfoCommand>("getAccountInfo");
	commandFactory.registerCommand<GetAttributesCommand>("getAttributes");
	commandFactory.registerCommand<GetAttributesBatchCommand>("getAttributesBatch");
	commandFactory.registerCommand<GetFriendListCommand>("getFriendList");
	commandFactory.registerCommand<GetGameTimeCommand>("getGameTime");
	commandFactory.registerCommand<GetIgnoreListCommand>("getIgnoreList");
	commandFactory.registerCommand<GetMapLocationsCommand>("getMapLocations");
	commandFactory.registerCommand<GetObjVarsCommand>("getObjVars");
	commandFactory.registerCommand<GetPlayerIdCommand>("getPlayerId");
	commandFactory.registerCommand<GetPrototypeCommand>("getPrototype");
	commandFactory.registerCommand<GetRankCommand>("getRank");
	commandFactory.registerCommand<GetSpawnDelaysCommand>("getSpawnDelays");
	commandFactory.registerCommand<GetStationNameCommand>("getStationName");
	commandFactory.registerCommand<GetVeteranRewardTimeCommand>("getVeteranRewardTime");
	commandFactory.registerCommand<GetVeteranRewardTimeCsCommand>("getVeteranRewardTimeCs");
	commandFactory.registerCommand<GiveItemCommand>("giveItem");
	commandFactory.registerCommand<GiveMaintenanceToVendorCommand>("giveMaintenanceToVendor");
	commandFactory.registerCommand<GivevendormaintCommand>("givevendormaint");
	commandFactory.registerCommand<GmForceCommandCommand>("gmForceCommand");
	commandFactory.registerCommand<GmCreateClassResourceCommand>("gmCreateClassResource");
	commandFactory.registerCommand<GmCreateSpecificResourceCommand>("gmCreateSpecificResource");
	commandFactory.registerCommand<GmForceRankCommand>("gmForceRank");
	commandFactory.registerCommand<GmFsVillageCommand>("gmFsVillage");
	commandFactory.registerCommand<GmJediStateCommand>("gmJediState");
	commandFactory.registerCommand<GmReviveCommand>("gmRevive");
	commandFactory.registerCommand<GotoCommand>("goto");
	commandFactory.registerCommand<GrantBadgeCommand>("grantBadge");
	commandFactory.registerCommand<GrantPadawanTrialsEligibilityCommand>("grantPadawanTrialsEligibility");
	commandFactory.registerCommand<GrantSkillCommand>("grantSkill");
	commandFactory.registerCommand<GrantTitleCommand>("grantTitle");
	commandFactory.registerCommand<GrantZoningRightsCommand>("grantZoningRights");
	commandFactory.registerCommand<GroupChatCommand>("groupChat");
	commandFactory.registerCommand<GroupSayCommand>("groupSay");
	commandFactory.registerCommand<GsayCommand>("gsay");
	commandFactory.registerCommand<GtellCommand>("gtell");
	commandFactory.registerCommand<GuildCommand>("guild");
	commandFactory.registerCommand<GuildremoveCommand>("guildremove");
	commandFactory.registerCommand<GuildsayCommand>("guildsay");
	commandFactory.registerCommand<GuildstatusCommand>("guildstatus");
	commandFactory.registerCommand<HarmfulCommand>("harmful");
	commandFactory.registerCommand<HarmlessCommand>("harmless");
	commandFactory.registerCommand<HarvestCorpseCommand>("harvestCorpse");
	commandFactory.registerCommand<HarvesterActivateCommand>("harvesterActivate");
	commandFactory.registerCommand<HarvesterDeactivateCommand>("harvesterDeactivate");
	commandFactory.registerCommand<HarvesterDiscardHopperCommand>("harvesterDiscardHopper");
	commandFactory.registerCommand<HarvesterGetResourceDataCommand>("harvesterGetResourceData");
	commandFactory.registerCommand<HarvesterHarvestCommand>("harvesterHarvest");
	commandFactory.registerCommand<HarvesterMakeCrateCommand>("harvesterMakeCrate");
	commandFactory.registerCommand<HarvesterSelectResourceCommand>("harvesterSelectResource");
	commandFactory.registerCommand<HarvesterTakeSurveyCommand>("harvesterTakeSurvey");
	commandFactory.registerCommand<HasVeteranRewardCommand>("hasVeteranReward");
	commandFactory.registerCommand<HaveconsentCommand>("haveconsent");
	commandFactory.registerCommand<HeadShot1Command>("headShot1");
	commandFactory.registerCommand<HeadShot2Command>("headShot2");
	commandFactory.registerCommand<HeadShot3Command>("headShot3");
	commandFactory.registerCommand<HealActionSelf1Command>("healActionSelf1");
	commandFactory.registerCommand<HealActionSelf2Command>("healActionSelf2");
	commandFactory.registerCommand<HealActionWoundOther1Command>("healActionWoundOther1");
	commandFactory.registerCommand<HealActionWoundOther2Command>("healActionWoundOther2");
	commandFactory.registerCommand<HealActionWoundSelf1Command>("healActionWoundSelf1");
	commandFactory.registerCommand<HealActionWoundSelf2Command>("healActionWoundSelf2");
	commandFactory.registerCommand<HealAllOther1Command>("healAllOther1");
	commandFactory.registerCommand<HealAllOther2Command>("healAllOther2");
	commandFactory.registerCommand<HealAllSelf1Command>("healAllSelf1");
	commandFactory.registerCommand<HealAllSelf2Command>("healAllSelf2");
	commandFactory.registerCommand<HealBattleFatigueOther1Command>("healBattleFatigueOther1");
	commandFactory.registerCommand<HealBattleFatigueOther2Command>("healBattleFatigueOther2");
	commandFactory.registerCommand<HealBattleFatigueSelf1Command>("healBattleFatigueSelf1");
	commandFactory.registerCommand<HealBattleFatigueSelf2Command>("healBattleFatigueSelf2");
	commandFactory.registerCommand<HealDamageCommand>("healDamage");
	commandFactory.registerCommand<HealDroidDamageCommand>("healDroidDamage");
	commandFactory.registerCommand<HealDroidWoundCommand>("healDroidWound");
	commandFactory.registerCommand<HealEnhanceCommand>("healEnhance");
	commandFactory.registerCommand<HealHealthSelf1Command>("healHealthSelf1");
	commandFactory.registerCommand<HealHealthSelf2Command>("healHealthSelf2");
	commandFactory.registerCommand<HealHealthWoundOther1Command>("healHealthWoundOther1");
	commandFactory.registerCommand<HealHealthWoundOther2Command>("healHealthWoundOther2");
	commandFactory.registerCommand<HealHealthWoundSelf1Command>("healHealthWoundSelf1");
	commandFactory.registerCommand<HealHealthWoundSelf2Command>("healHealthWoundSelf2");
	commandFactory.registerCommand<HealMindCommand>("healMind");
	commandFactory.registerCommand<HealMindSelf1Command>("healMindSelf1");
	commandFactory.registerCommand<HealMindSelf2Command>("healMindSelf2");
	commandFactory.registerCommand<HealMindWoundOther1Command>("healMindWoundOther1");
	commandFactory.registerCommand<HealMindWoundOther2Command>("healMindWoundOther2");
	commandFactory.registerCommand<HealMindWoundSelf1Command>("healMindWoundSelf1");
	commandFactory.registerCommand<HealMindWoundSelf2Command>("healMindWoundSelf2");
	commandFactory.registerCommand<HealPetCommand>("healPet");
	commandFactory.registerCommand<HealStateCommand>("healState");
	commandFactory.registerCommand<HealStatesOtherCommand>("healStatesOther");
	commandFactory.registerCommand<HealStatesSelfCommand>("healStatesSelf");
	commandFactory.registerCommand<HealthShot1Command>("healthShot1");
	commandFactory.registerCommand<HealthShot2Command>("healthShot2");
	commandFactory.registerCommand<HealWoundCommand>("healWound");
	commandFactory.registerCommand<HoloEmoteCommand>("holoEmote");
	commandFactory.registerCommand<ImagedesignCommand>("imagedesign");
	commandFactory.registerCommand<InitializeComponentCommand>("initializeComponent");
	commandFactory.registerCommand<InnateCommand>("innate");
	commandFactory.registerCommand<InsertItemIntoShipComponentSlotCommand>("insertItemIntoShipComponentSlot");
	commandFactory.registerCommand<InstallMissionTerminalCommand>("installMissionTerminal");
	commandFactory.registerCommand<InstallShipComponentCommand>("installShipComponent");
	commandFactory.registerCommand<InsureCommand>("insure");
	commandFactory.registerCommand<Intimidate1Command>("intimidate1");
	commandFactory.registerCommand<Intimidate2Command>("intimidate2");
	commandFactory.registerCommand<IntimidationAttackCommand>("intimidationAttack");
	commandFactory.registerCommand<InviteCommand>("invite");
	commandFactory.registerCommand<InvulnerableCommand>("invulnerable");
	commandFactory.registerCommand<ItemmovebackCommand>("itemmoveback");
	commandFactory.registerCommand<ItemmovedownCommand>("itemmovedown");
	commandFactory.registerCommand<ItemmoveforwardCommand>("itemmoveforward");
	commandFactory.registerCommand<ItemmoveupCommand>("itemmoveup");
	commandFactory.registerCommand<ItemrotateleftCommand>("itemrotateleft");
	commandFactory.registerCommand<ItemrotaterightCommand>("itemrotateright");
	commandFactory.registerCommand<JediMindTrickCommand>("jediMindTrick");
	commandFactory.registerCommand<JoinCommand>("join");
	commandFactory.registerCommand<JoinGameCommand>("joinGame");
	commandFactory.registerCommand<KickCommand>("kick");
	commandFactory.registerCommand<KillCommand>("kill");
	commandFactory.registerCommand<KillPlayerCommand>("killPlayer");
	commandFactory.registerCommand<KipUpShotCommand>("kipUpShot");
	commandFactory.registerCommand<KneelCommand>("kneel");
	commandFactory.registerCommand<KnockdownAttackCommand>("knockdownAttack");
	commandFactory.registerCommand<KnockdownFireCommand>("knockdownFire");
	commandFactory.registerCommand<LagCommand>("lag");
	commandFactory.registerCommand<LastDitchCommand>("lastDitch");
	commandFactory.registerCommand<LaunchFireworkCommand>("launchFirework");
	commandFactory.registerCommand<LeaveGameCommand>("leaveGame");
	commandFactory.registerCommand<LeaveGroupCommand>("leaveGroup");
	commandFactory.registerCommand<LegShot1Command>("legShot1");
	commandFactory.registerCommand<LegShot2Command>("legShot2");
	commandFactory.registerCommand<LegShot3Command>("legShot3");
	commandFactory.registerCommand<LfgCommand>("lfg");
	commandFactory.registerCommand<ListActiveQuestsCommand>("listActiveQuests");
	commandFactory.registerCommand<ListCompletedQuestsCommand>("listCompletedQuests");
	commandFactory.registerCommand<ListenCommand>("listen");
	commandFactory.registerCommand<ListGuildsCommand>("listGuilds");
	//commandFactory.registerCommand<LogoutServerCommand>("logoutServer");
	commandFactory.registerCommand<LootCommand>("loot");
	commandFactory.registerCommand<LootPlayerCorpseCommand>("lootPlayerCorpse");
	commandFactory.registerCommand<LowBlowCommand>("lowBlow");
	commandFactory.registerCommand<MakeLeaderCommand>("makeLeader");
	//commandFactory.registerCommand<MakeMasterLooterCommand>("makeMasterLooter");
	commandFactory.registerCommand<MakeSurveyCommand>("makeSurvey");
	commandFactory.registerCommand<ManufactureCommand>("manufacture");
	commandFactory.registerCommand<MaskscentCommand>("maskscent");
	commandFactory.registerCommand<MaxCombatAbilityCommand>("maxCombatAbility");
	commandFactory.registerCommand<MaxStatsCommand>("maxStats");
	commandFactory.registerCommand<MedicalForageCommand>("medicalForage");
	commandFactory.registerCommand<MeditateCommand>("meditate");
	commandFactory.registerCommand<Melee1hBlindHit1Command>("melee1hBlindHit1");
	commandFactory.registerCommand<Melee1hBlindHit2Command>("melee1hBlindHit2");
	commandFactory.registerCommand<Melee1hBodyHit1Command>("melee1hBodyHit1");
	commandFactory.registerCommand<Melee1hBodyHit2Command>("melee1hBodyHit2");
	commandFactory.registerCommand<Melee1hBodyHit3Command>("melee1hBodyHit3");
	commandFactory.registerCommand<Melee1hDizzyHit1Command>("melee1hDizzyHit1");
	commandFactory.registerCommand<Melee1hDizzyHit2Command>("melee1hDizzyHit2");
	commandFactory.registerCommand<Melee1hHealthHit1Command>("melee1hHealthHit1");
	commandFactory.registerCommand<Melee1hHealthHit2Command>("melee1hHealthHit2");
	commandFactory.registerCommand<Melee1hHit1Command>("melee1hHit1");
	commandFactory.registerCommand<Melee1hHit2Command>("melee1hHit2");
	commandFactory.registerCommand<Melee1hHit3Command>("melee1hHit3");
	commandFactory.registerCommand<Melee1hLunge1Command>("melee1hLunge1");
	commandFactory.registerCommand<Melee1hLunge2Command>("melee1hLunge2");
	commandFactory.registerCommand<Melee1hScatterHit1Command>("melee1hScatterHit1");
	commandFactory.registerCommand<Melee1hScatterHit2Command>("melee1hScatterHit2");
	commandFactory.registerCommand<Melee1hSpinAttack1Command>("melee1hSpinAttack1");
	commandFactory.registerCommand<Melee1hSpinAttack2Command>("melee1hSpinAttack2");
	commandFactory.registerCommand<Melee2hArea1Command>("melee2hArea1");
	commandFactory.registerCommand<Melee2hArea2Command>("melee2hArea2");
	commandFactory.registerCommand<Melee2hArea3Command>("melee2hArea3");
	commandFactory.registerCommand<Melee2hHeadHit1Command>("melee2hHeadHit1");
	commandFactory.registerCommand<Melee2hHeadHit2Command>("melee2hHeadHit2");
	commandFactory.registerCommand<Melee2hHeadHit3Command>("melee2hHeadHit3");
	commandFactory.registerCommand<Melee2hHit1Command>("melee2hHit1");
	commandFactory.registerCommand<Melee2hHit2Command>("melee2hHit2");
	commandFactory.registerCommand<Melee2hHit3Command>("melee2hHit3");
	commandFactory.registerCommand<Melee2hLunge1Command>("melee2hLunge1");
	commandFactory.registerCommand<Melee2hLunge2Command>("melee2hLunge2");
	commandFactory.registerCommand<Melee2hMindHit1Command>("melee2hMindHit1");
	commandFactory.registerCommand<Melee2hMindHit2Command>("melee2hMindHit2");
	commandFactory.registerCommand<Melee2hSpinAttack1Command>("melee2hSpinAttack1");
	commandFactory.registerCommand<Melee2hSpinAttack2Command>("melee2hSpinAttack2");
	commandFactory.registerCommand<Melee2hSweep1Command>("melee2hSweep1");
	commandFactory.registerCommand<Melee2hSweep2Command>("melee2hSweep2");
	commandFactory.registerCommand<MindBlast1Command>("mindBlast1");
	commandFactory.registerCommand<MindBlast2Command>("mindBlast2");
	commandFactory.registerCommand<MindShot1Command>("mindShot1");
	commandFactory.registerCommand<MindShot2Command>("mindShot2");
	commandFactory.registerCommand<MoneyCommand>("money");
	commandFactory.registerCommand<MountCommand>("mount");
	commandFactory.registerCommand<MoveFurnitureCommand>("moveFurniture");
	commandFactory.registerCommand<MultiTargetPistolShotCommand>("multiTargetPistolShot");
	commandFactory.registerCommand<MultiTargetShotCommand>("multiTargetShot");
	commandFactory.registerCommand<NameStructureCommand>("nameStructure");
	commandFactory.registerCommand<NewbiehelperCommand>("newbiehelper");
	commandFactory.registerCommand<NewbieRequestStartingLocationsCommand>("newbieRequestStartingLocations");
	commandFactory.registerCommand<NewbieSelectStartingLocationCommand>("newbieSelectStartingLocation");
	commandFactory.registerCommand<NextCraftingStageCommand>("nextCraftingStage");
	commandFactory.registerCommand<NpcCommand>("npc");
	commandFactory.registerCommand<NpcConversationSelectCommand>("npcConversationSelect");
	commandFactory.registerCommand<NpcConversationStartCommand>("npcConversationStart");
	commandFactory.registerCommand<NpcConversationStopCommand>("npcConversationStop");
	commandFactory.registerCommand<ObjectCommand>("Object");
	commandFactory.registerCommand<ObjvarCommand>("objvar");
	commandFactory.registerCommand<OpenContainerCommand>("openContainer");
	commandFactory.registerCommand<OverChargeShot1Command>("overChargeShot1");
	commandFactory.registerCommand<OverChargeShot2Command>("overChargeShot2");
	commandFactory.registerCommand<OverrideActiveMonthsCommand>("overrideActiveMonths");
	commandFactory.registerCommand<OverridePadawanTrialsEligibilityCommand>("overridePadawanTrialsEligibility");
	commandFactory.registerCommand<PanicShotCommand>("panicShot");
	commandFactory.registerCommand<PauseDanceCommand>("pauseDance");
	commandFactory.registerCommand<PauseMusicCommand>("pauseMusic");
	commandFactory.registerCommand<PaWithdrawCommand>("paWithdraw");
	commandFactory.registerCommand<PaymaintenanceCommand>("paymaintenance");
	commandFactory.registerCommand<PeaceCommand>("peace");
	commandFactory.registerCommand<PermissionListModifyCommand>("permissionListModify");
	commandFactory.registerCommand<PistolMeleeDefense1Command>("pistolMeleeDefense1");
	commandFactory.registerCommand<PistolMeleeDefense2Command>("pistolMeleeDefense2");
	commandFactory.registerCommand<PlaceBattlefieldStructureCommand>("placeBattlefieldStructure");
	commandFactory.registerCommand<PlaceStructureCommand>("placeStructure");
	commandFactory.registerCommand<PlaceStructureModeCommand>("placeStructureMode");
	commandFactory.registerCommand<PlanetCommand>("planet");
	commandFactory.registerCommand<PlanetsayCommand>("planetsay");
	commandFactory.registerCommand<PlanetwarpCommand>("planetwarp");
	commandFactory.registerCommand<PlanetwarpTargetCommand>("planetwarpTarget");
	commandFactory.registerCommand<PointBlankArea1Command>("pointBlankArea1");
	commandFactory.registerCommand<PointBlankArea2Command>("pointBlankArea2");
	commandFactory.registerCommand<PointBlankSingle1Command>("pointBlankSingle1");
	commandFactory.registerCommand<PointBlankSingle2Command>("pointBlankSingle2");
	commandFactory.registerCommand<PolearmActionHit1Command>("polearmActionHit1");
	commandFactory.registerCommand<PolearmActionHit2Command>("polearmActionHit2");
	commandFactory.registerCommand<PolearmArea1Command>("polearmArea1");
	commandFactory.registerCommand<PolearmArea2Command>("polearmArea2");
	commandFactory.registerCommand<PolearmHit1Command>("polearmHit1");
	commandFactory.registerCommand<PolearmHit2Command>("polearmHit2");
	commandFactory.registerCommand<PolearmHit3Command>("polearmHit3");
	commandFactory.registerCommand<PolearmLegHit1Command>("polearmLegHit1");
	commandFactory.registerCommand<PolearmLegHit2Command>("polearmLegHit2");
	commandFactory.registerCommand<PolearmLegHit3Command>("polearmLegHit3");
	commandFactory.registerCommand<PolearmLunge1Command>("polearmLunge1");
	commandFactory.registerCommand<PolearmLunge2Command>("polearmLunge2");
	commandFactory.registerCommand<PolearmSpinAttack1Command>("polearmSpinAttack1");
	commandFactory.registerCommand<PolearmSpinAttack2Command>("polearmSpinAttack2");
	commandFactory.registerCommand<PolearmStun1Command>("polearmStun1");
	commandFactory.registerCommand<PolearmStun2Command>("polearmStun2");
	commandFactory.registerCommand<PolearmSweep1Command>("polearmSweep1");
	commandFactory.registerCommand<PolearmSweep2Command>("polearmSweep2");
	commandFactory.registerCommand<PostureDownAttackCommand>("postureDownAttack");
	commandFactory.registerCommand<PostureUpAttackCommand>("postureUpAttack");
	commandFactory.registerCommand<PowerBoostCommand>("powerBoost");
	commandFactory.registerCommand<ProneCommand>("prone");
	commandFactory.registerCommand<PurchaseReinforcementCommand>("purchaseReinforcement");
	commandFactory.registerCommand<PurchaseTicketCommand>("purchaseTicket");
	commandFactory.registerCommand<QuickHealCommand>("quickHeal");
	commandFactory.registerCommand<RallyCommand>("rally");
	commandFactory.registerCommand<ReconnectToTransferServerCommand>("reconnectToTransferServer");
	commandFactory.registerCommand<RecruitSkillTrainerCommand>("recruitSkillTrainer");
	commandFactory.registerCommand<RegainConsciousnessCommand>("regainConsciousness");
	commandFactory.registerCommand<RegenerationCommand>("regeneration");
	commandFactory.registerCommand<RegisterWithLocationCommand>("registerWithLocation");
	commandFactory.registerCommand<ReloadCommand>("reload");
	commandFactory.registerCommand<RemoteCommand>("remote");
	commandFactory.registerCommand<RemoveAllowedPlayerCommand>("removeAllowedPlayer");
	commandFactory.registerCommand<RemoveBannedPlayerCommand>("removeBannedPlayer");
	commandFactory.registerCommand<RemoveFriendCommand>("removeFriend");
	commandFactory.registerCommand<RemoveIgnoreCommand>("removeIgnore");
	commandFactory.registerCommand<RepairBattlefieldStructureCommand>("repairBattlefieldStructure");
	commandFactory.registerCommand<RepairShipComponentInSlotCommand>("repairShipComponentInSlot");
	commandFactory.registerCommand<ReportCommand>("report");
	commandFactory.registerCommand<RequestBadgesCommand>("requestBadges");
	commandFactory.registerCommand<RequestBiographyCommand>("requestBiography");
	commandFactory.registerCommand<RequestCharacterMatchCommand>("requestCharacterMatch");
	commandFactory.registerCommand<RequestCharacterSheetInfoCommand>("requestCharacterSheetInfo");
	commandFactory.registerCommand<RequestCoreSampleCommand>("requestCoreSample");
	commandFactory.registerCommand<RequestCraftingSessionCommand>("requestCraftingSession");
	commandFactory.registerCommand<RequestDraftSlotsCommand>("requestDraftSlots");
	commandFactory.registerCommand<RequestDraftSlotsBatchCommand>("requestDraftSlotsBatch");
	commandFactory.registerCommand<RequestManfSchematicSlotsCommand>("requestManfSchematicSlots");
	commandFactory.registerCommand<RequestResourceWeightsCommand>("requestResourceWeights");
	commandFactory.registerCommand<RequestResourceWeightsBatchCommand>("requestResourceWeightsBatch");
	commandFactory.registerCommand<RequestSetStatMigrationDataCommand>("requestSetStatMigrationData");
	commandFactory.registerCommand<RequestStatMigrationDataCommand>("requestStatMigrationData");
	commandFactory.registerCommand<RequestStatMigrationStartCommand>("requestStatMigrationStart");
	commandFactory.registerCommand<RequestStatMigrationStopCommand>("requestStatMigrationStop");
	commandFactory.registerCommand<RequestStimpackCommand>("requestStimpack");
	commandFactory.registerCommand<RequestSurveyCommand>("requestSurvey");
	commandFactory.registerCommand<RequestWaypointAtPositionCommand>("requestWaypointAtPosition");
	commandFactory.registerCommand<RescueCommand>("rescue");
	commandFactory.registerCommand<ResendLoginMessageToAllCommand>("resendLoginMessageToAll");
	commandFactory.registerCommand<ResetJediCommand>("resetJedi");
	commandFactory.registerCommand<ResourceCommand>("resource");
	commandFactory.registerCommand<ResourceContainerSplitCommand>("resourceContainerSplit");
	commandFactory.registerCommand<ResourceContainerTransferCommand>("resourceContainerTransfer");
	commandFactory.registerCommand<ResourceSetNameCommand>("resourceSetName");
	commandFactory.registerCommand<ResSampleLoopCommand>("resSampleLoop");
	commandFactory.registerCommand<RestartConversionCommand>("restartConversion");
	commandFactory.registerCommand<RestartCraftingSessionCommand>("restartCraftingSession");
	commandFactory.registerCommand<RetreatCommand>("retreat");
	commandFactory.registerCommand<RevivePlayerCommand>("revivePlayer");
	commandFactory.registerCommand<RevokeBadgeCommand>("revokeBadge");
	commandFactory.registerCommand<RevokeSkillCommand>("revokeSkill");
	commandFactory.registerCommand<RolePlayCommand>("rolePlay");
	commandFactory.registerCommand<RollShotCommand>("rollShot");
	commandFactory.registerCommand<RotateFurnitureCommand>("rotateFurniture");
	commandFactory.registerCommand<Saber1hComboHit1Command>("saber1hComboHit1");
	commandFactory.registerCommand<Saber1hComboHit2Command>("saber1hComboHit2");
	commandFactory.registerCommand<Saber1hComboHit3Command>("saber1hComboHit3");
	commandFactory.registerCommand<Saber1hFlurryCommand>("saber1hFlurry");
	commandFactory.registerCommand<Saber1hFlurry2Command>("saber1hFlurry2");
	commandFactory.registerCommand<Saber1hHeadHit1Command>("saber1hHeadHit1");
	commandFactory.registerCommand<Saber1hHeadHit2Command>("saber1hHeadHit2");
	commandFactory.registerCommand<Saber1hHeadHit3Command>("saber1hHeadHit3");
	commandFactory.registerCommand<Saber1hHit1Command>("saber1hHit1");
	commandFactory.registerCommand<Saber1hHit2Command>("saber1hHit2");
	commandFactory.registerCommand<Saber1hHit3Command>("saber1hHit3");
	commandFactory.registerCommand<Saber2hBodyHit1Command>("saber2hBodyHit1");
	commandFactory.registerCommand<Saber2hBodyHit2Command>("saber2hBodyHit2");
	commandFactory.registerCommand<Saber2hBodyHit3Command>("saber2hBodyHit3");
	commandFactory.registerCommand<Saber2hFrenzyCommand>("saber2hFrenzy");
	commandFactory.registerCommand<Saber2hHit1Command>("saber2hHit1");
	commandFactory.registerCommand<Saber2hHit2Command>("saber2hHit2");
	commandFactory.registerCommand<Saber2hHit3Command>("saber2hHit3");
	commandFactory.registerCommand<Saber2hPhantomCommand>("saber2hPhantom");
	commandFactory.registerCommand<Saber2hSweep1Command>("saber2hSweep1");
	commandFactory.registerCommand<Saber2hSweep2Command>("saber2hSweep2");
	commandFactory.registerCommand<Saber2hSweep3Command>("saber2hSweep3");
	commandFactory.registerCommand<SaberPolearmDervishCommand>("saberPolearmDervish");
	commandFactory.registerCommand<SaberPolearmDervish2Command>("saberPolearmDervish2");
	commandFactory.registerCommand<SaberPolearmHit1Command>("saberPolearmHit1");
	commandFactory.registerCommand<SaberPolearmHit2Command>("saberPolearmHit2");
	commandFactory.registerCommand<SaberPolearmHit3Command>("saberPolearmHit3");
	commandFactory.registerCommand<SaberPolearmLegHit1Command>("saberPolearmLegHit1");
	commandFactory.registerCommand<SaberPolearmLegHit2Command>("saberPolearmLegHit2");
	commandFactory.registerCommand<SaberPolearmLegHit3Command>("saberPolearmLegHit3");
	commandFactory.registerCommand<SaberPolearmSpinAttack1Command>("saberPolearmSpinAttack1");
	commandFactory.registerCommand<SaberPolearmSpinAttack2Command>("saberPolearmSpinAttack2");
	commandFactory.registerCommand<SaberPolearmSpinAttack3Command>("saberPolearmSpinAttack3");
	commandFactory.registerCommand<SaberSlash1Command>("saberSlash1");
	commandFactory.registerCommand<SaberSlash2Command>("saberSlash2");
	commandFactory.registerCommand<SaberThrow1Command>("saberThrow1");
	commandFactory.registerCommand<SaberThrow2Command>("saberThrow2");
	commandFactory.registerCommand<SaberThrow3Command>("saberThrow3");
	commandFactory.registerCommand<SampleCommand>("sample");
	commandFactory.registerCommand<SampleDNACommand>("sampleDNA");
	commandFactory.registerCommand<ScatterShot1Command>("scatterShot1");
	commandFactory.registerCommand<ScatterShot2Command>("scatterShot2");
	commandFactory.registerCommand<ScriptCommand>("script");
	commandFactory.registerCommand<SearchCorpseCommand>("searchCorpse");
	commandFactory.registerCommand<SecretSpawnSpamCommand>("secretSpawnSpam");
	commandFactory.registerCommand<SeGogglesCommand>("seGoggles");
	commandFactory.registerCommand<SelectDraftSchematicCommand>("selectDraftSchematic");
	commandFactory.registerCommand<ServerCommand>("server");
	commandFactory.registerCommand<ServerDestroyObjectCommand>("serverDestroyObject");
	commandFactory.registerCommand<ServerSysGroupCommand>("serverSysGroup");
	commandFactory.registerCommand<SetBiographyAdminCommand>("setBiographyAdmin");
	commandFactory.registerCommand<SetBiographyCommand>("setBiography");
	commandFactory.registerCommand<SetBoostmoraleCommand>("setBoostmorale");
	commandFactory.registerCommand<SetChargeCommand>("setCharge");
	commandFactory.registerCommand<SetCurrentSkillTitleCommand>("setCurrentSkillTitle");
	commandFactory.registerCommand<SetExperienceCommand>("setExperience");
	commandFactory.registerCommand<SetFactionCommand>("setFaction");
	commandFactory.registerCommand<SetFactionStandingCommand>("setFactionStanding");
	commandFactory.registerCommand<SetFirstNameCommand>("setFirstName");
	commandFactory.registerCommand<SetFormupCommand>("setFormup");
	commandFactory.registerCommand<SetGodModeCommand>("setGodMode");
	commandFactory.registerCommand<SetHueCommand>("setHue");
	commandFactory.registerCommand<SetIntimidateCommand>("setIntimidate");
	commandFactory.registerCommand<SetLastNameCommand>("setLastName");
	commandFactory.registerCommand<SetLoginMessageCommand>("setLoginMessage");
	commandFactory.registerCommand<SetLoginTitleCommand>("setLoginTitle");
	commandFactory.registerCommand<SetMatchMakingCharacterIdCommand>("setMatchMakingCharacterId");
	commandFactory.registerCommand<SetMatchMakingPersonalIdCommand>("setMatchMakingPersonalId");
	commandFactory.registerCommand<SetMaximumSpawnTimeCommand>("setMaximumSpawnTime");
	commandFactory.registerCommand<SetMinimumSpawnTimeCommand>("setMinimumSpawnTime");
	commandFactory.registerCommand<SetMoodCommand>("setMood");
	commandFactory.registerCommand<SetMoodInternalCommand>("setMoodInternal");
	commandFactory.registerCommand<SetNameCommand>("setName");
	commandFactory.registerCommand<SetNameCommand>("setName");
	commandFactory.registerCommand<SetOwnerCommand>("setOwner");
	commandFactory.registerCommand<SetPerformanceBuffTargetCommand>("setPerformanceBuffTarget");
	commandFactory.registerCommand<SetpermissionCommand>("setpermission");
	commandFactory.registerCommand<SetPlanetLimitCommand>("setPlanetLimit");
	commandFactory.registerCommand<SetPlayerAppearanceCommand>("setPlayerAppearance");
	commandFactory.registerCommand<SetPlayerStateCommand>("setPlayerState");
	commandFactory.registerCommand<SetprivacyCommand>("setprivacy");
	commandFactory.registerCommand<SetPublicStateCommand>("setPublicState");
	commandFactory.registerCommand<SetRankCommand>("setRank");
	commandFactory.registerCommand<SetRetreatCommand>("setRetreat");
	commandFactory.registerCommand<SetSpeedCommand>("setSpeed");
	commandFactory.registerCommand<SetSpokenLanguageCommand>("setSpokenLanguage");
	commandFactory.registerCommand<SetSteadyaimCommand>("setSteadyaim");
	commandFactory.registerCommand<SetTEFCommand>("setTEF");
	commandFactory.registerCommand<SetVeteranRewardCommand>("setVeteranReward");
	commandFactory.registerCommand<SetWarcryCommand>("setWarcry");
	commandFactory.registerCommand<SetWaypointActiveStatusCommand>("setWaypointActiveStatus");
	commandFactory.registerCommand<SetWaypointNameCommand>("setWaypointName");
	commandFactory.registerCommand<ShowCouncilRankCommand>("showCouncilRank");
	commandFactory.registerCommand<ShowDanceVisualsCommand>("showDanceVisuals");
	commandFactory.registerCommand<ShowFactionInformationCommand>("showFactionInformation");
	commandFactory.registerCommand<ShowMusicianVisualsCommand>("showMusicianVisuals");
	commandFactory.registerCommand<ShowPvPRatingCommand>("showPvPRating");
	commandFactory.registerCommand<ShowSpawnRegionCommand>("showSpawnRegion");
	commandFactory.registerCommand<SitServerCommand>("sitServer");
	commandFactory.registerCommand<SkillCommand>("skill");
	commandFactory.registerCommand<SmokebombCommand>("smokebomb");
	commandFactory.registerCommand<SniperShotCommand>("sniperShot");
	commandFactory.registerCommand<SnoopCommand>("snoop");
	commandFactory.registerCommand<SocialCommand>("social");
	commandFactory.registerCommand<SocialInternalCommand>("socialInternal");
	commandFactory.registerCommand<SpatialChatCommand>("spatialChat");
	commandFactory.registerCommand<SpatialChatInternalCommand>("spatialChatInternal");
	commandFactory.registerCommand<SpawnStatusCommand>("spawnStatus");
	commandFactory.registerCommand<SplitCreditsWithGroupCommand>("splitCreditsWithGroup");
	commandFactory.registerCommand<SpotlightCommand>("spotlight");
	commandFactory.registerCommand<SprayShotCommand>("sprayShot");
	commandFactory.registerCommand<StandCommand>("stand");
	commandFactory.registerCommand<StartBandCommand>("startBand");
	commandFactory.registerCommand<StartCitySpawnerCommand>("startCitySpawner");
	commandFactory.registerCommand<StartDanceCommand>("startDance");
	commandFactory.registerCommand<StartleShot1Command>("startleShot1");
	commandFactory.registerCommand<StartleShot2Command>("startleShot2");
	commandFactory.registerCommand<StartMusicCommand>("startMusic");
	commandFactory.registerCommand<StartSpawnerCommand>("startSpawner");
	commandFactory.registerCommand<StartTargetSpawnerCommand>("startTargetSpawner");
	commandFactory.registerCommand<StartTraceLoggingCommand>("startTraceLogging");
	commandFactory.registerCommand<StatCommand>("stat");
	commandFactory.registerCommand<SteadyaimCommand>("steadyaim");
	commandFactory.registerCommand<StopBandCommand>("stopBand");
	commandFactory.registerCommand<StopBleedingCommand>("stopBleeding");
	commandFactory.registerCommand<StopCitySpawnerCommand>("stopCitySpawner");
	commandFactory.registerCommand<StopCraftingSessionCommand>("stopCraftingSession");
	commandFactory.registerCommand<StopDanceCommand>("stopDance");
	commandFactory.registerCommand<StoplisteningCommand>("stoplistening");
	commandFactory.registerCommand<StopMusicCommand>("stopMusic");
	commandFactory.registerCommand<StoppingShotCommand>("stoppingShot");
	commandFactory.registerCommand<StopSpawnerCommand>("stopSpawner");
	commandFactory.registerCommand<StopTargetSpawnerCommand>("stopTargetSpawner");
	commandFactory.registerCommand<StopTraceLoggingCommand>("stopTraceLogging");
	commandFactory.registerCommand<StopwatchingCommand>("stopwatching");
	commandFactory.registerCommand<StrafeShot1Command>("strafeShot1");
	commandFactory.registerCommand<StrafeShot2Command>("strafeShot2");
	commandFactory.registerCommand<StructurestatusCommand>("structurestatus");
	commandFactory.registerCommand<StunAttackCommand>("stunAttack");
	commandFactory.registerCommand<SuppressionFire1Command>("suppressionFire1");
	commandFactory.registerCommand<SuppressionFire2Command>("suppressionFire2");
	commandFactory.registerCommand<SurpriseShotCommand>("surpriseShot");
	commandFactory.registerCommand<SurrenderSkillCommand>("surrenderSkill");
	commandFactory.registerCommand<SurveyCommand>("survey");
	commandFactory.registerCommand<SynchronizedUiListenCommand>("synchronizedUiListen");
	commandFactory.registerCommand<SynchronizedUiStopListeningCommand>("synchronizedUiStopListening");
	commandFactory.registerCommand<SystemMessageCommand>("systemMessage");
	commandFactory.registerCommand<TakeCoverCommand>("takeCover");
	commandFactory.registerCommand<TameCommand>("tame");
	commandFactory.registerCommand<TargetCommand>("target");
	commandFactory.registerCommand<TauntCommand>("taunt");
	commandFactory.registerCommand<TeachCommand>("teach");
	commandFactory.registerCommand<TeleportCommand>("teleport");
	commandFactory.registerCommand<TeleportTargetCommand>("teleportTarget");
	commandFactory.registerCommand<TeleportToCommand>("teleportTo");
	commandFactory.registerCommand<TellpetCommand>("tellpet");
	commandFactory.registerCommand<TendDamageCommand>("tendDamage");
	commandFactory.registerCommand<TendDamageToolCommand>("tendDamageTool");
	commandFactory.registerCommand<TendWoundCommand>("tendWound");
	commandFactory.registerCommand<TendWoundsToolCommand>("tendWoundsTool");
	commandFactory.registerCommand<ThreatenShotCommand>("threatenShot");
	commandFactory.registerCommand<ThrowGrenadeCommand>("throwGrenade");
	commandFactory.registerCommand<ThrowTrapCommand>("throwTrap");
	commandFactory.registerCommand<TipCommand>("tip");
	commandFactory.registerCommand<ToggleAwayFromKeyBoardCommand>("toggleAwayFromKeyBoard");
	commandFactory.registerCommand<ToggleDisplayingFactionRankCommand>("toggleDisplayingFactionRank");
	commandFactory.registerCommand<TorsoShotCommand>("torsoShot");
	commandFactory.registerCommand<TotalHealOtherCommand>("totalHealOther");
	commandFactory.registerCommand<TotalHealSelfCommand>("totalHealSelf");
	commandFactory.registerCommand<TransferForceCommand>("transferForce");
	commandFactory.registerCommand<TransferItemCommand>("transferItem");
	commandFactory.registerCommand<TransferItemArmorCommand>("transferItemArmor");
	commandFactory.registerCommand<TransferItemMiscCommand>("transferItemMisc");
	commandFactory.registerCommand<TransferItemWeaponCommand>("transferItemWeapon");
	commandFactory.registerCommand<TransferstructureCommand>("transferstructure");
	commandFactory.registerCommand<TumbleToKneelingCommand>("tumbleToKneeling");
	commandFactory.registerCommand<TumbleToProneCommand>("tumbleToProne");
	commandFactory.registerCommand<TumbleToStandingCommand>("tumbleToStanding");
	commandFactory.registerCommand<UnarmedBlind1Command>("unarmedBlind1");
	commandFactory.registerCommand<UnarmedBodyHit1Command>("unarmedBodyHit1");
	commandFactory.registerCommand<UnarmedCombo1Command>("unarmedCombo1");
	commandFactory.registerCommand<UnarmedCombo2Command>("unarmedCombo2");
	commandFactory.registerCommand<UnarmedDizzy1Command>("unarmedDizzy1");
	commandFactory.registerCommand<UnarmedHeadHit1Command>("unarmedHeadHit1");
	commandFactory.registerCommand<UnarmedHit1Command>("unarmedHit1");
	commandFactory.registerCommand<UnarmedHit2Command>("unarmedHit2");
	commandFactory.registerCommand<UnarmedHit3Command>("unarmedHit3");
	commandFactory.registerCommand<UnarmedKnockdown1Command>("unarmedKnockdown1");
	commandFactory.registerCommand<UnarmedKnockdown2Command>("unarmedKnockdown2");
	commandFactory.registerCommand<UnarmedLegHit1Command>("unarmedLegHit1");
	commandFactory.registerCommand<UnarmedLunge1Command>("unarmedLunge1");
	commandFactory.registerCommand<UnarmedLunge2Command>("unarmedLunge2");
	commandFactory.registerCommand<UnarmedSpinAttack1Command>("unarmedSpinAttack1");
	commandFactory.registerCommand<UnarmedSpinAttack2Command>("unarmedSpinAttack2");
	commandFactory.registerCommand<UnarmedStun1Command>("unarmedStun1");
	commandFactory.registerCommand<UnassociateDroidControlDeviceWithShipCommand>("unassociateDroidControlDeviceWithShip");
	commandFactory.registerCommand<UnCityBanCommand>("unCityBan");
	commandFactory.registerCommand<UnconsentCommand>("unconsent");
	commandFactory.registerCommand<UnderHandShotCommand>("underHandShot");
	commandFactory.registerCommand<UnfreezePlayerCommand>("unfreezePlayer");
	commandFactory.registerCommand<UninstallShipComponentCommand>("uninstallShipComponent");
	commandFactory.registerCommand<UninviteCommand>("uninvite");
	commandFactory.registerCommand<UnsnoopCommand>("unsnoop");
	commandFactory.registerCommand<UseReconDroneCommand>("useReconDrone");
	commandFactory.registerCommand<UseSkillBuffCommand>("useSkillBuff");
	commandFactory.registerCommand<VentriloquismCommand>("ventriloquism");
	commandFactory.registerCommand<ToggleCombatTauntsCommand>("toggleCombatTaunts");
	commandFactory.registerCommand<VertFurnitureCommand>("vertFurniture");
	commandFactory.registerCommand<VitalizeCommand>("vitalize");
	commandFactory.registerCommand<VolleyFireCommand>("volleyFire");
	commandFactory.registerCommand<VolleyFireAttackCommand>("volleyFireAttack");
	commandFactory.registerCommand<Warcry1Command>("warcry1");
	commandFactory.registerCommand<Warcry2Command>("warcry2");
	commandFactory.registerCommand<WarningShotCommand>("warningShot");
	commandFactory.registerCommand<WatchCommand>("watch");
	commandFactory.registerCommand<WildShot1Command>("wildShot1");
	commandFactory.registerCommand<WildShot2Command>("wildShot2");
	commandFactory.registerCommand<WipeItemsCommand>("wipeItems");
	commandFactory.registerCommand<WookieeRoarCommand>("wookieeRoar");
	commandFactory.registerCommand<CityInfoCommand>("cityInfo");
	//commandFactory.registerCommand<GroupLootCommand>("groupLoot");
	//commandFactory.registerCommand<OpenLotteryContainerCommand>("openLotteryContainer");
	//commandFactory.registerCommand<CloseLotteryContainerCommand>("closeLotteryContainer");
	commandFactory.registerCommand<RequestQuestTimersAndCountersCommand>("requestQuestTimersAndCounters");
}
