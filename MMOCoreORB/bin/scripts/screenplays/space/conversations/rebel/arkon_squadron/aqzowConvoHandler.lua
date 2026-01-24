local SpaceHelpers = require("utils.space_helpers")

aqzowConvoHandler = conv_handler:new {}

function aqzowConvoHandler:getInitialScreen(pPlayer, pNpc, pConvTemplate)
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

	-- Player is a Rebel Pilot but not Havoc Squadron
	if (isRebelPilot and not SpaceHelpers:isHavocSquadron(pPlayer)) then
		return convoTemplate:getScreen("non_havoc_pilot")
	-- Player is not a Rebel pilot
	elseif (not isRebelPilot) then
		return convoTemplate:getScreen("not_rebel_pilot")
	end

	-- Check if player has completed Tier 3
	if (not SpaceHelpers:hasCompletedPilotTier(pPlayer, "rebel_navy", 3)) then
		return convoTemplate:getScreen("not_ready")
	end

	local pGhost = CreatureObject(pPlayer):getPlayerObject()

	if (pGhost == nil) then
		return convoTemplate:getScreen("no_jtl")
	end

	local ghost = LuaPlayerObject(pGhost)

	if (ghost == nil) then
		return convoTemplate:getScreen("no_jtl")
	end

	local questOneStarted = SpaceHelpers:isSpaceQuestActive(pPlayer, HavocSquadronScreenplay.TIER4_QUEST_STRING_1.type, HavocSquadronScreenplay.TIER4_QUEST_STRING_1.name)
	local questTwoStarted = SpaceHelpers:isSpaceQuestActive(pPlayer, HavocSquadronScreenplay.TIER4_QUEST_STRING_2.type, HavocSquadronScreenplay.TIER4_QUEST_STRING_2.name)
	local questThreeStarted = SpaceHelpers:isSpaceQuestActive(pPlayer, HavocSquadronScreenplay.TIER4_QUEST_STRING_3.type, HavocSquadronScreenplay.TIER4_QUEST_STRING_3.name)
	local questFourStarted = SpaceHelpers:isSpaceQuestActive(pPlayer, HavocSquadronScreenplay.TIER4_QUEST_STRING_4.type, HavocSquadronScreenplay.TIER4_QUEST_STRING_4.name)
	local masterQuestStarted = SpaceHelpers:isSpaceQuestActive(pPlayer, HavocSquadronScreenplay.TIER4_QUEST_STRING_MASTER.type, HavocSquadronScreenplay.TIER4_QUEST_STRING_MASTER.name)

	local questOneComplete = SpaceHelpers:isSpaceQuestComplete(pPlayer, HavocSquadronScreenplay.TIER4_QUEST_STRING_1.type, HavocSquadronScreenplay.TIER4_QUEST_STRING_1.name)
	local questTwoComplete = SpaceHelpers:isSpaceQuestComplete(pPlayer, HavocSquadronScreenplay.TIER4_QUEST_STRING_2.type, HavocSquadronScreenplay.TIER4_QUEST_STRING_2.name)
	local questThreeComplete = SpaceHelpers:isSpaceQuestComplete(pPlayer, HavocSquadronScreenplay.TIER4_QUEST_STRING_3.type, HavocSquadronScreenplay.TIER4_QUEST_STRING_3.name)
	local questFourComplete = SpaceHelpers:isSpaceQuestComplete(pPlayer, HavocSquadronScreenplay.TIER4_QUEST_STRING_4.type, HavocSquadronScreenplay.TIER4_QUEST_STRING_4.name)
	local masterQuestComplete = SpaceHelpers:isSpaceQuestComplete(pPlayer, HavocSquadronScreenplay.TIER4_QUEST_STRING_MASTER.type, HavocSquadronScreenplay.TIER4_QUEST_STRING_MASTER.name)

	local escortDutyStarted = SpaceHelpers:isSpaceQuestActive(pPlayer, HavocSquadronScreenplay.TIER4_QUEST_STRING_DUTY_1.type, HavocSquadronScreenplay.TIER4_QUEST_STRING_DUTY_1.name)
	local rescueDutyStarted = SpaceHelpers:isSpaceQuestActive(pPlayer, HavocSquadronScreenplay.TIER4_QUEST_STRING_DUTY_2.type, HavocSquadronScreenplay.TIER4_QUEST_STRING_DUTY_2.name)
	local recoveryDutyStarted = SpaceHelpers:isSpaceQuestActive(pPlayer, HavocSquadronScreenplay.TIER4_QUEST_STRING_DUTY_3.type, HavocSquadronScreenplay.TIER4_QUEST_STRING_DUTY_3.name)
	local destroyDutyStarted = SpaceHelpers:isSpaceQuestActive(pPlayer, HavocSquadronScreenplay.TIER4_QUEST_STRING_DUTY_4.type, HavocSquadronScreenplay.TIER4_QUEST_STRING_DUTY_4.name)

	-- Player has an active story quest or duty mission from Aqzow
	if ((questOneStarted and not questOneComplete) or (questTwoStarted and not questTwoComplete) or (questThreeStarted and not questThreeComplete) or (questFourStarted and not questFourComplete) or (masterQuestStarted and not masterQuestComplete) or escortDutyStarted or rescueDutyStarted or recoveryDutyStarted or destroyDutyStarted) then
		return convoTemplate:getScreen("has_mission")
	-- Player is a master pilot
	elseif (SpaceHelpers:hasMasterSkill(pPlayer, "rebel_navy")) then
		return convoTemplate:getScreen("master_pilot")
	-- Check if players have all the tier4 skill boxes but need master
	elseif (SpaceHelpers:hasCompletedPilotTier(pPlayer, "rebel_navy", 4)) then
		-- Check if master quest is complete
		if (masterQuestComplete) then
			return convoTemplate:getScreen("grant_master")
		else
			return convoTemplate:getScreen("master_quest_brief")
		end
	-- Player has at least one Tier4 skill box
	elseif (SpaceHelpers:hasPilotTierSkill(pPlayer, "rebel_navy", 4)) then
		-- Check if the player can be trained in the remaining Tier4 Skills
		if (SpaceHelpers:hasExperienceForTraining(pPlayer, 4)) then
			return convoTemplate:getScreen("more_training")
		-- Offer Duty missions
		else
			CreatureObject(pPlayer):doAnimation("salute1")

			return convoTemplate:getScreen("duty_missions")
		end
	-- Player has finished quest 4 and has received the reward
	elseif (questFourComplete and getQuestStatus(playerID .. HavocSquadronScreenplay.TIER4_QUEST_STRING_4.name .. ":reward") == "1") then
		return convoTemplate:getScreen("missions_complete")
	-- Player has completed quest 4 and needs reward
	elseif (questFourComplete and getQuestStatus(playerID .. HavocSquadronScreenplay.TIER4_QUEST_STRING_4.name .. ":reward") ~= "1") then
		setQuestStatus(playerID .. HavocSquadronScreenplay.TIER4_QUEST_STRING_4.name .. ":reward", 1)

		-- Grant Faction Standing
		CreatureObject(pPlayer):addFactionPoints("rebel", 500, false)

		return convoTemplate:getScreen("missions_complete")
	-- Player has finished quest 3 and needs to start quest 4
	elseif (questThreeComplete and not questFourStarted and getQuestStatus(playerID .. HavocSquadronScreenplay.TIER4_QUEST_STRING_3.name .. ":reward") == "1") then
		return convoTemplate:getScreen("excellent_work3")
	-- Player has completed quest 3 and needs reward
	elseif (questThreeComplete and getQuestStatus(playerID .. HavocSquadronScreenplay.TIER4_QUEST_STRING_3.name .. ":reward") ~= "1") then
		setQuestStatus(playerID .. HavocSquadronScreenplay.TIER4_QUEST_STRING_3.name .. ":reward", 1)

		CreatureObject(pPlayer):addFactionPoints("rebel", 400, false)

		return convoTemplate:getScreen("excellent_work3")
	-- Player has finished quest 2 and needs to start quest 3
	elseif (questTwoComplete and not questThreeStarted and getQuestStatus(playerID .. HavocSquadronScreenplay.TIER4_QUEST_STRING_2.name .. ":reward") == "1") then
		return convoTemplate:getScreen("excellent_work2")
	-- Player has completed quest 2 and needs reward
	elseif (questTwoComplete and getQuestStatus(playerID .. HavocSquadronScreenplay.TIER4_QUEST_STRING_2.name .. ":reward") ~= "1") then
		setQuestStatus(playerID .. HavocSquadronScreenplay.TIER4_QUEST_STRING_2.name .. ":reward", 1)

		CreatureObject(pPlayer):addFactionPoints("rebel", 350, false)

		return convoTemplate:getScreen("excellent_work2")
	-- Player has finished quest 1 and needs to start quest 2
	elseif (questOneComplete and not questTwoStarted and getQuestStatus(playerID .. HavocSquadronScreenplay.TIER4_QUEST_STRING_1.name .. ":reward") == "1") then
		return convoTemplate:getScreen("excellent_work")
	-- Player has finished quest 1 and needs reward
	elseif (questOneComplete and getQuestStatus(playerID .. HavocSquadronScreenplay.TIER4_QUEST_STRING_1.name .. ":reward") ~= "1") then
		setQuestStatus(playerID .. HavocSquadronScreenplay.TIER4_QUEST_STRING_1.name .. ":reward", 1)

		CreatureObject(pPlayer):addFactionPoints("rebel", 300, false)

		return convoTemplate:getScreen("excellent_work")
	-- New pilot to Aqzow
	elseif (getQuestStatus(playerID .. "HavocSquadronScreenplay:StartedAqzow") ~= "1") then
		return convoTemplate:getScreen("introduction")
	-- Player needs to start/restart quest 1
	elseif (not questOneComplete) then
		return convoTemplate:getScreen("start_mission1")
	end

	return convoTemplate:getScreen("no_jtl")
end

function aqzowConvoHandler:runScreenHandlers(pConvTemplate, pPlayer, pNpc, selectedOption, pConvScreen)
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

		if (not CreatureObject(pPlayer):hasSkill("pilot_rebel_navy_starships_04") and skillManager:fulfillsSkillPrerequisitesAndXp(pPlayer, "pilot_rebel_navy_starships_04")) then
			clonedConversation:addOption("@conversation/corellia_rebel_tier4:s_c06c7aa9", "train_player_fighters") -- Master fighters.
		end
		if (not CreatureObject(pPlayer):hasSkill("pilot_rebel_navy_weapons_04") and skillManager:fulfillsSkillPrerequisitesAndXp(pPlayer, "pilot_rebel_navy_weapons_04")) then
			clonedConversation:addOption("@conversation/corellia_rebel_tier4:s_d1431f95", "train_player_component") -- Master weapons.
		end
		if (not CreatureObject(pPlayer):hasSkill("pilot_rebel_navy_procedures_04") and skillManager:fulfillsSkillPrerequisitesAndXp(pPlayer, "pilot_rebel_navy_procedures_04")) then
			clonedConversation:addOption("@conversation/corellia_rebel_tier4:s_8523e1fc", "train_player_basics") -- Master procedures.
		end
		if (not CreatureObject(pPlayer):hasSkill("pilot_rebel_navy_droid_04") and skillManager:fulfillsSkillPrerequisitesAndXp(pPlayer, "pilot_rebel_navy_droid_04")) then
			clonedConversation:addOption("@conversation/corellia_rebel_tier4:s_b7fc5e5d", "train_player_droid") -- Master droid interface.
		end
	-- Handle Skill box granting
	elseif (string.find(screenID, "train_player_")) then
		local skillManager = LuaSkillManager()

		if (screenID == "train_player_droid") then
			if (skillManager:fulfillsSkillPrerequisitesAndXp(pPlayer, "pilot_rebel_navy_droid_04")) then
				SpaceHelpers:grantSpaceSkill(pPlayer, "pilot_rebel_navy_droid_04", true)
			end
		elseif (screenID == "train_player_basics") then
			if (skillManager:fulfillsSkillPrerequisitesAndXp(pPlayer, "pilot_rebel_navy_procedures_04")) then
				SpaceHelpers:grantSpaceSkill(pPlayer, "pilot_rebel_navy_procedures_04", true)
			end
		elseif (screenID == "train_player_fighters") then
			if (skillManager:fulfillsSkillPrerequisitesAndXp(pPlayer, "pilot_rebel_navy_starships_04")) then
				SpaceHelpers:grantSpaceSkill(pPlayer, "pilot_rebel_navy_starships_04", true)
			end
		elseif (screenID == "train_player_component") then
			if (skillManager:fulfillsSkillPrerequisitesAndXp(pPlayer, "pilot_rebel_navy_weapons_04")) then
				SpaceHelpers:grantSpaceSkill(pPlayer, "pilot_rebel_navy_weapons_04", true)
			end
		end

		return pClonedScreen
	elseif (screenID == "grant_master") then
		-- Grant master skill
		SpaceHelpers:grantSpaceSkill(pPlayer, "pilot_rebel_navy_master", false)

		-- Final pilot tier increment
		if (ghost:getPilotTier() == 4) then
			ghost:incrementPilotTier()
		end

		-- Major faction standing boost
		CreatureObject(pPlayer):addFactionPoints("rebel", 1000, false)
	elseif (screenID == "escort_duty") then
		escort_duty_corellia_rebel_tier4_1:startQuest(pPlayer, pNpc)
	elseif (screenID == "rescue_duty") then
		rescue_duty_corellia_rebel_tier4_1:startQuest(pPlayer, pNpc)
	elseif (screenID == "recovery_duty") then
		recovery_duty_corellia_rebel_tier4_1:startQuest(pPlayer, pNpc)
	elseif (screenID == "destroy_duty") then
		destroy_duty_corellia_rebel_tier4_1:startQuest(pPlayer, pNpc)
	elseif (screenID == "accept_mission") then
		setQuestStatus(playerID .. "HavocSquadronScreenplay:StartedAqzow", 1)

		survival_corellia_rebel_tier4_1:startQuest(pPlayer, pNpc)
	elseif (screenID == "start_mission2") then
		assassinate_corellia_rebel_tier4_2:startQuest(pPlayer, pNpc)
	elseif (screenID == "start_mission3") then
		space_battle_corellia_rebel_tier4_3:startQuest(pPlayer, pNpc)
	elseif (screenID == "start_mission4") then
		recovery_corellia_rebel_tier4_4:startQuest(pPlayer, pNpc)
	elseif (screenID == "start_master_quest") then
		destroy_corellia_rebel_master:startQuest(pPlayer, pNpc)
	elseif (screenID == "goodbye") then
		CreatureObject(pNpc):doAnimation("goodbye")
	end

	return pClonedScreen
end
