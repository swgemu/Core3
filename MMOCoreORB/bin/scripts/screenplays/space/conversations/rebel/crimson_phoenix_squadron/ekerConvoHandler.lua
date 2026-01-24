local SpaceHelpers = require("utils.space_helpers")

ekerConvoHandler = conv_handler:new {}

function ekerConvoHandler:getInitialScreen(pPlayer, pNpc, pConvTemplate)
	if (pPlayer == nil or pNpc == nil or pConvTemplate == nil) then
		return nil
	end

	local convoTemplate = LuaConversationTemplate(pConvTemplate)

	local faction = CreatureObject(pPlayer):getFaction()
	local playerID = CreatureObject(pPlayer):getObjectID()

	-- JTL is disabled
	if (not isJtlEnabled()) then
		return convoTemplate:getScreen("no_jtl")
	end

	-- Player is Imperial Pilot
	if (SpaceHelpers:isImperialPilot(pPlayer)) then
		return convoTemplate:getScreen("imperial_pilot")
	-- Player is Neutral Pilot
	elseif (SpaceHelpers:isNeutralPilot(pPlayer)) then
		return convoTemplate:getScreen("neutral_pilot")
	end

	local isRebelPilot = SpaceHelpers:isRebelPilot(pPlayer)

	-- Player is a Rebel Pilot but not Crimson Phoenix Squadron
	if (isRebelPilot and not SpaceHelpers:isCrimsonPhoenixSquadron(pPlayer)) then
		return convoTemplate:getScreen("non_crimson_phoenix_pilot")
	end

	local pGhost = CreatureObject(pPlayer):getPlayerObject()

	if (pGhost == nil) then
		return convoTemplate:getScreen("no_jtl")
	end

	local ghost = LuaPlayerObject(pGhost)

	if (ghost == nil) then
		return convoTemplate:getScreen("no_jtl")
	end

	local questOneStarted = SpaceHelpers:isSpaceQuestActive(pPlayer, CrimsonPhoenixSquadronScreenplay.QUEST_STRING_1.type, CrimsonPhoenixSquadronScreenplay.QUEST_STRING_1.name)
	local questTwoStarted = SpaceHelpers:isSpaceQuestActive(pPlayer, CrimsonPhoenixSquadronScreenplay.QUEST_STRING_2.type, CrimsonPhoenixSquadronScreenplay.QUEST_STRING_2.name)
	local questThreeStarted = SpaceHelpers:isSpaceQuestActive(pPlayer, CrimsonPhoenixSquadronScreenplay.QUEST_STRING_3.type, CrimsonPhoenixSquadronScreenplay.QUEST_STRING_3.name)
	local questFourStarted = SpaceHelpers:isSpaceQuestActive(pPlayer, CrimsonPhoenixSquadronScreenplay.QUEST_STRING_4.type, CrimsonPhoenixSquadronScreenplay.QUEST_STRING_4.name)

	local questOneComplete = SpaceHelpers:isSpaceQuestComplete(pPlayer, CrimsonPhoenixSquadronScreenplay.QUEST_STRING_1.type, CrimsonPhoenixSquadronScreenplay.QUEST_STRING_1.name)
	local questTwoComplete = SpaceHelpers:isSpaceQuestComplete(pPlayer, CrimsonPhoenixSquadronScreenplay.QUEST_STRING_2.type, CrimsonPhoenixSquadronScreenplay.QUEST_STRING_2.name)
	local questThreeComplete = SpaceHelpers:isSpaceQuestComplete(pPlayer, CrimsonPhoenixSquadronScreenplay.QUEST_STRING_3.type, CrimsonPhoenixSquadronScreenplay.QUEST_STRING_3.name)
	local questFourComplete = SpaceHelpers:isSpaceQuestComplete(pPlayer, CrimsonPhoenixSquadronScreenplay.QUEST_STRING_4.type, CrimsonPhoenixSquadronScreenplay.QUEST_STRING_4.name)

	local destroyDutyStarted = SpaceHelpers:isSpaceQuestActive(pPlayer, CrimsonPhoenixSquadronScreenplay.QUEST_STRING_DUTY_1.type, CrimsonPhoenixSquadronScreenplay.QUEST_STRING_DUTY_1.name)
	local escortDutyStarted = SpaceHelpers:isSpaceQuestActive(pPlayer, CrimsonPhoenixSquadronScreenplay.QUEST_STRING_DUTY_2.type, CrimsonPhoenixSquadronScreenplay.QUEST_STRING_DUTY_2.name)

	-- Player has an active story quest or duty mission from Eker
	if ((questOneStarted and not questOneComplete) or (questTwoStarted and not questTwoComplete) or (questThreeStarted and not questThreeComplete) or (questFourStarted and not questFourComplete) or destroyDutyStarted or escortDutyStarted) then
		return convoTemplate:getScreen("has_mission")
	-- Check if players have all the tier1 skill boxes, send them to next trainer
	elseif (SpaceHelpers:hasCompletedPilotTier(pPlayer, "rebel_navy", 1)) then
		return convoTemplate:getScreen("completed_eker")
	-- Player has at least one Tier1 skill box
	elseif (SpaceHelpers:hasPilotTierSkill(pPlayer, "rebel_navy", 1)) then
		-- Check if the player can be trained in the remaining Tier1 Skills
		if (SpaceHelpers:hasExperienceForTraining(pPlayer, 1)) then
			return convoTemplate:getScreen("more_training")
		-- Offer Duty missions
		else
			CreatureObject(pPlayer):doAnimation("salute1")

			return convoTemplate:getScreen("duty_missions")
		end
	-- Player has finished quest 4 and has received the reward (first skill box)
	elseif (questFourComplete and getQuestStatus(playerID .. CrimsonPhoenixSquadronScreenplay.QUEST_STRING_4.name .. ":reward") == "1") then
		return convoTemplate:getScreen("missions_complete")
	-- Player has completed quest 4 and needs skill reward
	elseif (questFourComplete and getQuestStatus(playerID .. CrimsonPhoenixSquadronScreenplay.QUEST_STRING_4.name .. ":reward") ~= "1") then
		setQuestStatus(playerID .. CrimsonPhoenixSquadronScreenplay.QUEST_STRING_4.name .. ":reward", 1)

		-- Grant first Tier 1 skill box for free (no XP deduction)
		SpaceHelpers:grantSpaceSkill(pPlayer, "pilot_rebel_navy_starships_01", false)

		-- Grant Faction Standing
		CreatureObject(pPlayer):addFactionPoints("rebel", 100, false)

		-- Increment pilot tier if all tier 1 skills are complete
		if (SpaceHelpers:hasCompletedPilotTier(pPlayer, "rebel_navy", 1) and ghost:getPilotTier() == 1) then
			ghost:incrementPilotTier()
		end

		return convoTemplate:getScreen("missions_complete")
	-- Player has finished quest 3 and needs to start quest 4
	elseif (questThreeComplete and not questFourStarted and getQuestStatus(playerID .. CrimsonPhoenixSquadronScreenplay.QUEST_STRING_3.name .. ":reward") == "1") then
		return convoTemplate:getScreen("excellent_work3")
	-- Player has completed quest 3 and needs reward
	elseif (questThreeComplete and getQuestStatus(playerID .. CrimsonPhoenixSquadronScreenplay.QUEST_STRING_3.name .. ":reward") ~= "1") then
		setQuestStatus(playerID .. CrimsonPhoenixSquadronScreenplay.QUEST_STRING_3.name .. ":reward", 1)

		CreatureObject(pPlayer):addFactionPoints("rebel", 75, false)

		return convoTemplate:getScreen("excellent_work3")
	-- Player has finished quest 2 and needs to start quest 3
	elseif (questTwoComplete and not questThreeStarted and getQuestStatus(playerID .. CrimsonPhoenixSquadronScreenplay.QUEST_STRING_2.name .. ":reward") == "1") then
		return convoTemplate:getScreen("excellent_work2")
	-- Player has completed quest 2 and needs reward
	elseif (questTwoComplete and getQuestStatus(playerID .. CrimsonPhoenixSquadronScreenplay.QUEST_STRING_2.name .. ":reward") ~= "1") then
		setQuestStatus(playerID .. CrimsonPhoenixSquadronScreenplay.QUEST_STRING_2.name .. ":reward", 1)

		CreatureObject(pPlayer):addFactionPoints("rebel", 50, false)

		return convoTemplate:getScreen("excellent_work2")
	-- Player has finished quest 1 and needs to start quest 2
	elseif (questOneComplete and not questTwoStarted and getQuestStatus(playerID .. CrimsonPhoenixSquadronScreenplay.QUEST_STRING_1.name .. ":reward") == "1") then
		return convoTemplate:getScreen("excellent_work")
	-- Player has finished quest 1 and needs reward
	elseif (questOneComplete and getQuestStatus(playerID .. CrimsonPhoenixSquadronScreenplay.QUEST_STRING_1.name .. ":reward") ~= "1") then
		setQuestStatus(playerID .. CrimsonPhoenixSquadronScreenplay.QUEST_STRING_1.name .. ":reward", 1)

		CreatureObject(pPlayer):addFactionPoints("rebel", 25, false)

		return convoTemplate:getScreen("excellent_work")
	-- New pilot
	elseif (not isRebelPilot) then
		return convoTemplate:getScreen("introduction")
	-- Player needs to start/restart quest 1
	elseif (not questOneComplete) then
		return convoTemplate:getScreen("start_mission1")
	end

	return convoTemplate:getScreen("no_jtl")
end

function ekerConvoHandler:runScreenHandlers(pConvTemplate, pPlayer, pNpc, selectedOption, pConvScreen)
	if (pPlayer == nil or pConvScreen == nil) then
		return
	end

	local screen = LuaConversationScreen(pConvScreen)
	local screenID = screen:getScreenID()

	local pClonedScreen = screen:cloneScreen()
	local clonedConversation = LuaConversationScreen(pClonedScreen)

	clonedConversation:setDialogTextTU(CreatureObject(pPlayer):getFirstName())

	local pGhost = CreatureObject(pPlayer):getPlayerObject()

	if (pGhost == nil) then
		return pClonedScreen
	end

	local ghost = LuaPlayerObject(pGhost)

	if (ghost == nil) then
		return pClonedScreen
	end

	local playerID = CreatureObject(pPlayer):getObjectID()

	-- Handle additional training
	if (screenID == "more_training") then
		local skillManager = LuaSkillManager()

		if (not CreatureObject(pPlayer):hasSkill("pilot_rebel_navy_starships_01") and skillManager:fulfillsSkillPrerequisitesAndXp(pPlayer, "pilot_rebel_navy_starships_01")) then
			clonedConversation:addOption("@conversation/tatooine_rebel_trainer_1:s_c06c7aa9", "train_player_fighters") -- Starship Piloting
		end
		if (not CreatureObject(pPlayer):hasSkill("pilot_rebel_navy_weapons_01") and skillManager:fulfillsSkillPrerequisitesAndXp(pPlayer, "pilot_rebel_navy_weapons_01")) then
			clonedConversation:addOption("@conversation/tatooine_rebel_trainer_1:s_d1431f95", "train_player_component") -- Weapons Systems
		end
		if (not CreatureObject(pPlayer):hasSkill("pilot_rebel_navy_procedures_01") and skillManager:fulfillsSkillPrerequisitesAndXp(pPlayer, "pilot_rebel_navy_procedures_01")) then
			clonedConversation:addOption("@conversation/tatooine_rebel_trainer_1:s_8523e1fc", "train_player_basics") -- Flight Procedures
		end
		if (not CreatureObject(pPlayer):hasSkill("pilot_rebel_navy_droid_01") and skillManager:fulfillsSkillPrerequisitesAndXp(pPlayer, "pilot_rebel_navy_droid_01")) then
			clonedConversation:addOption("@conversation/tatooine_rebel_trainer_1:s_b7fc5e5d", "train_player_droid") -- Droid Interface
		end
	-- Handle Skill box granting
	elseif (string.find(screenID, "train_player_")) then
		local skillManager = LuaSkillManager()

		if (screenID == "train_player_droid") then
			if (skillManager:fulfillsSkillPrerequisitesAndXp(pPlayer, "pilot_rebel_navy_droid_01")) then
				SpaceHelpers:grantSpaceSkill(pPlayer, "pilot_rebel_navy_droid_01", true)
			end
		elseif (screenID == "train_player_basics") then
			if (skillManager:fulfillsSkillPrerequisitesAndXp(pPlayer, "pilot_rebel_navy_procedures_01")) then
				SpaceHelpers:grantSpaceSkill(pPlayer, "pilot_rebel_navy_procedures_01", true)
			end
		elseif (screenID == "train_player_fighters") then
			if (skillManager:fulfillsSkillPrerequisitesAndXp(pPlayer, "pilot_rebel_navy_starships_01")) then
				SpaceHelpers:grantSpaceSkill(pPlayer, "pilot_rebel_navy_starships_01", true)
			end
		elseif (screenID == "train_player_component") then
			if (skillManager:fulfillsSkillPrerequisitesAndXp(pPlayer, "pilot_rebel_navy_weapons_01")) then
				SpaceHelpers:grantSpaceSkill(pPlayer, "pilot_rebel_navy_weapons_01", true)
			end
		end

		-- Check if all Tier 1 complete, increment tier
		if (SpaceHelpers:hasCompletedPilotTier(pPlayer, "rebel_navy", 1) and ghost:getPilotTier() == 1) then
			ghost:incrementPilotTier()
		end

		return pClonedScreen
	elseif (screenID == "join_squadron") then
		-- Grant Novice Pilot Skill and Starter Ship
		SpaceHelpers:grantNovicePilot(pPlayer, "rebelPilot")

		-- Set Squadron Type
		SpaceHelpers:setSquadronType(pPlayer, CRIMSON_PHOENIX_SQUADRON)

		-- Start first mission
		patrol_tatooine_rebel_1:startQuest(pPlayer, pNpc)
	elseif (screenID == "accept_mission") then
		patrol_tatooine_rebel_1:startQuest(pPlayer, pNpc)
	elseif (screenID == "start_mission2") then
		patrol_tatooine_rebel_2:startQuest(pPlayer, pNpc)
	elseif (screenID == "start_mission3") then
		destroy_tatooine_rebel_3:startQuest(pPlayer, pNpc)
	elseif (screenID == "start_mission4") then
		assassinate_tatooine_rebel_4:startQuest(pPlayer, pNpc)
	elseif (screenID == "destroy_duty") then
		destroy_duty_tatooine_rebel_6:startQuest(pPlayer, pNpc)
	elseif (screenID == "escort_duty") then
		escort_duty_tatooine_rebel_7:startQuest(pPlayer, pNpc)
	elseif (screenID == "goodbye") then
		CreatureObject(pNpc):doAnimation("goodbye")
	end

	return pClonedScreen
end
