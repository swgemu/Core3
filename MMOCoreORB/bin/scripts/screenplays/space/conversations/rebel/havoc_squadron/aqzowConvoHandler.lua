local SpaceHelpers = require("utils.space_helpers")

aqzowConvoHandler = conv_handler:new {}

function aqzowConvoHandler:getInitialScreen(pPlayer, pNpc, pConvTemplate)
	if (pPlayer == nil or pNpc == nil or pConvTemplate == nil) then
		return nil
	end

	local convoTemplate = LuaConversationTemplate(pConvTemplate)

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

	-- Check if player has completed Tier 2 (required before talking to Aqzow)
	if (not SpaceHelpers:hasCompletedPilotTier(pPlayer, "rebel_navy", 2)) then
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

	-- Testing resetAqzowQuests
	--HavocSquadronScreenplay:resetAqzowQuests(pPlayer)

	local questOneStarted = SpaceHelpers:isSpaceQuestActive(pPlayer, HavocSquadronScreenplay.TIER3_QUEST_STRING_1.type, HavocSquadronScreenplay.TIER3_QUEST_STRING_1.name)
	local questTwoStarted = SpaceHelpers:isSpaceQuestActive(pPlayer, HavocSquadronScreenplay.TIER3_QUEST_STRING_2.type, HavocSquadronScreenplay.TIER3_QUEST_STRING_2.name)
	local questThreeStarted = SpaceHelpers:isSpaceQuestActive(pPlayer, HavocSquadronScreenplay.TIER3_QUEST_STRING_3.type, HavocSquadronScreenplay.TIER3_QUEST_STRING_3.name)
	local questFourStarted = SpaceHelpers:isSpaceQuestActive(pPlayer, HavocSquadronScreenplay.TIER3_QUEST_STRING_4.type, HavocSquadronScreenplay.TIER3_QUEST_STRING_4.name)

	local questOneComplete = SpaceHelpers:isSpaceQuestComplete(pPlayer, HavocSquadronScreenplay.TIER3_QUEST_STRING_1.type, HavocSquadronScreenplay.TIER3_QUEST_STRING_1.name)
	local questTwoComplete = SpaceHelpers:isSpaceQuestComplete(pPlayer, HavocSquadronScreenplay.TIER3_QUEST_STRING_2.type, HavocSquadronScreenplay.TIER3_QUEST_STRING_2.name)
	local questThreeComplete = SpaceHelpers:isSpaceQuestComplete(pPlayer, HavocSquadronScreenplay.TIER3_QUEST_STRING_3.type, HavocSquadronScreenplay.TIER3_QUEST_STRING_3.name)
	local questFourComplete = SpaceHelpers:isSpaceQuestComplete(pPlayer, HavocSquadronScreenplay.TIER3_QUEST_STRING_4.type, HavocSquadronScreenplay.TIER3_QUEST_STRING_4.name)

	local completedTier3 = SpaceHelpers:hasCompletedPilotTier(pPlayer, "rebel_navy", 3)

	-- Check if players have all the tier 3 skill boxes and finished last mission, send them to Warvog Arkon for Tier 4
	if (questFourComplete and completedTier3) then
		if (ghost:getPilotTier() <= 3) then
			ghost:incrementPilotTier()
		end

		return convoTemplate:getScreen("completed_aqzow")
	end

	-- Player has an active story quest from Aqzow
	if ((questOneStarted and not questOneComplete) or (questTwoStarted and not questTwoComplete) or (questThreeStarted and not questThreeComplete) or (questFourStarted and not questFourComplete)) then
		return convoTemplate:getScreen("has_mission")
	end

	-- Player has negative faction standing with the Rebel Alliance
	if (ghost:getFactionStanding("rebel") < 0) then
		return convoTemplate:getScreen("negative_faction")
	end

	local tier3SkillCount = SpaceHelpers:getPilotTierSkillCount(pPlayer, "rebel_navy", 3)

	-- Reward + Training Checks. Tier 3 grants a skill box for each mission completed
	if (questFourComplete and tier3SkillCount == 3) then
		if (getQuestStatus(playerID .. HavocSquadronScreenplay.TIER3_QUEST_STRING_4.name .. ":reward") ~= "1") then
			setQuestStatus(playerID .. HavocSquadronScreenplay.TIER3_QUEST_STRING_4.name .. ":reward", 1)

			assassinate_corellia_rebel_tier3_4:rewardPlayer(pPlayer)
		end

		return convoTemplate:getScreen("excellent_work4")
	elseif (questThreeComplete and tier3SkillCount == 2) then
		if (getQuestStatus(playerID .. HavocSquadronScreenplay.TIER3_QUEST_STRING_3.name .. ":reward") ~= "1") then
			setQuestStatus(playerID .. HavocSquadronScreenplay.TIER3_QUEST_STRING_3.name .. ":reward", 1)

			delivery_corellia_rebel_tier3_3:rewardPlayer(pPlayer)
		end

		return convoTemplate:getScreen("excellent_work3")
	elseif (questTwoComplete and tier3SkillCount == 1) then
		if (getQuestStatus(playerID .. HavocSquadronScreenplay.TIER3_QUEST_STRING_2.name .. ":reward") ~= "1") then
			setQuestStatus(playerID .. HavocSquadronScreenplay.TIER3_QUEST_STRING_2.name .. ":reward", 1)

			inspect_corellia_rebel_tier3_2:rewardPlayer(pPlayer)
		end

		return convoTemplate:getScreen("excellent_work2")
	elseif (questOneComplete and tier3SkillCount < 1) then
		if (getQuestStatus(playerID .. HavocSquadronScreenplay.TIER3_QUEST_STRING_1.name .. ":reward") ~= "1") then
			setQuestStatus(playerID .. HavocSquadronScreenplay.TIER3_QUEST_STRING_1.name .. ":reward", 1)

			recovery_corellia_rebel_tier3_1:rewardPlayer(pPlayer)
		end

		return convoTemplate:getScreen("excellent_work")
	end

	--[[
		Quest Starters
	]]

	if (not questFourComplete) then
		-- Player is able to start fourth mission
		if (questThreeComplete and not questFourStarted) then
			if (getQuestStatus(playerID .. HavocSquadronScreenplay.TIER3_QUEST_STRING_4.name .. ":attempted") == "1") then
				return convoTemplate:getScreen("failed_quest4")
			else
				return convoTemplate:getScreen("fourth_mission")
			end
		-- Player is able to start third mission
		elseif (questTwoComplete and not questThreeStarted) then
			if (getQuestStatus(playerID .. HavocSquadronScreenplay.TIER3_QUEST_STRING_3.name .. ":attempted") == "1") then
				return convoTemplate:getScreen("failed_quest3")
			else
				return convoTemplate:getScreen("third_mission")
			end
		-- Player is able to start second mission
		elseif (questOneComplete and not questTwoStarted) then
			if (getQuestStatus(playerID .. HavocSquadronScreenplay.TIER3_QUEST_STRING_2.name .. ":attempted") == "1") then
				return convoTemplate:getScreen("failed_quest2")
			else
				return convoTemplate:getScreen("second_mission")
			end
		-- Player is ready for first mission
		elseif (not questOneComplete) then
			if (getQuestStatus(playerID .. HavocSquadronScreenplay.TIER3_QUEST_STRING_1.name .. ":attempted") == "1") then
				return convoTemplate:getScreen("failed_quest1")
			else
				return convoTemplate:getScreen("first_mission")
			end
		end
	end

	return convoTemplate:getScreen("first_mission")
end

function aqzowConvoHandler:runScreenHandlers(pConvTemplate, pPlayer, pNpc, selectedOption, pConvScreen)
	if (pPlayer == nil or pConvScreen == nil) then
		return
	end

	local screen = LuaConversationScreen(pConvScreen)
	local screenID = screen:getScreenID()
	local playerID = CreatureObject(pPlayer):getObjectID()

	local pClonedScreen = screen:cloneScreen()
	local clonedConversation = LuaConversationScreen(pClonedScreen)

	-- Set player name token
	clonedConversation:setDialogTextTU(CreatureObject(pPlayer):getFirstName())

	local pGhost = CreatureObject(pPlayer):getPlayerObject()

	if (pGhost == nil) then
		return pClonedScreen
	end

	local ghost = LuaPlayerObject(pGhost)

	if (ghost == nil) then
		return pClonedScreen
	end

	--[[
		Skill Training Menu - Dynamically add skill options on mission complete screens
	]]
	if (string.find(screenID, "excellent_work")) then
		local screenAppend = ""

		if (screenID == "excellent_work4") then
			screenAppend = "_final"
		end

		if (not CreatureObject(pPlayer):hasSkill("pilot_rebel_navy_starships_03")) then
			clonedConversation:addOption("@conversation/corellia_rebel_tier3:s_89f4d28f", "train_fighters" .. screenAppend) -- I want to know about space superiority fighters.
		end
		if (not CreatureObject(pPlayer):hasSkill("pilot_rebel_navy_weapons_03")) then
			clonedConversation:addOption("@conversation/corellia_rebel_tier3:s_a70b470e", "train_components" .. screenAppend) -- I want to know about advanced starship components.
		end
		if (not CreatureObject(pPlayer):hasSkill("pilot_rebel_navy_procedures_03")) then
			clonedConversation:addOption("@conversation/corellia_rebel_tier3:s_2d6808ba", "train_procedures" .. screenAppend) -- I want to know about advanced space combat.
		end
		if (not CreatureObject(pPlayer):hasSkill("pilot_rebel_navy_droid_03")) then
			clonedConversation:addOption("@conversation/corellia_rebel_tier3:s_c28a300f", "train_droid" .. screenAppend) -- I want to know about system balance programming.
		end

	--[[
		Skill Granting - Grant the selected Tier 3 skill
	]]
	elseif (string.find(screenID, "train_")) then
		if (string.find(screenID, "train_fighters")) then
			SpaceHelpers:grantSpaceSkill(pPlayer, "pilot_rebel_navy_starships_03", false)
		elseif (string.find(screenID, "train_components")) then
			SpaceHelpers:grantSpaceSkill(pPlayer, "pilot_rebel_navy_weapons_03", false)
		elseif (string.find(screenID, "train_procedures")) then
			SpaceHelpers:grantSpaceSkill(pPlayer, "pilot_rebel_navy_procedures_03", false)
		elseif (string.find(screenID, "train_droid")) then
			SpaceHelpers:grantSpaceSkill(pPlayer, "pilot_rebel_navy_droid_03", false)
		end

		-- Check if all Tier 3 skills are now complete
		if (ghost:getPilotTier() <= 3 and SpaceHelpers:hasCompletedPilotTier(pPlayer, "rebel_navy", 3)) then
			ghost:incrementPilotTier()
		end

		return pClonedScreen

	--[[
		Quest Granting - Start missions on terminal accept screens
	]]

	-- Quest 1: Recovery mission (spy on Yavin)
	elseif (screenID == "accept_quest1_a" or screenID == "accept_quest1_b" or screenID == "accept_quest1_c" or screenID == "accept_quest1_d") then
		setQuestStatus(playerID .. HavocSquadronScreenplay.TIER3_QUEST_STRING_1.name .. ":attempted", 1)

		recovery_corellia_rebel_tier3_1:startQuest(pPlayer, pNpc)

	-- Quest 1: Failed retry
	elseif (screenID == "retry_quest1_a" or screenID == "retry_quest1_b") then
		recovery_corellia_rebel_tier3_1:startQuest(pPlayer, pNpc)

	-- Quest 2: Inspect mission (Endor smuggler data)
	elseif (screenID == "accept_quest2_a" or screenID == "accept_quest2_b" or screenID == "accept_quest2_c" or screenID == "accept_quest2_d") then
		setQuestStatus(playerID .. HavocSquadronScreenplay.TIER3_QUEST_STRING_2.name .. ":attempted", 1)

		inspect_corellia_rebel_tier3_2:startQuest(pPlayer, pNpc)

	-- Quest 2: Failed retry
	elseif (screenID == "retry_quest2_a" or screenID == "retry_quest2_b") then
		inspect_corellia_rebel_tier3_2:startQuest(pPlayer, pNpc)

	-- Quest 3: Delivery mission (Nym smuggler intel)
	elseif (screenID == "accept_quest3_a" or screenID == "accept_quest3_b" or screenID == "accept_quest3_c" or screenID == "accept_quest3_d" or screenID == "accept_quest3_e") then
		setQuestStatus(playerID .. HavocSquadronScreenplay.TIER3_QUEST_STRING_3.name .. ":attempted", 1)

		delivery_corellia_rebel_tier3_3:startQuest(pPlayer, pNpc)

	-- Quest 3: Failed retry
	elseif (screenID == "retry_quest3_a" or screenID == "retry_quest3_b") then
		delivery_corellia_rebel_tier3_3:startQuest(pPlayer, pNpc)

	-- Quest 4: Assassinate mission (Imperial pilot intercept)
	elseif (screenID == "accept_quest4_a" or screenID == "accept_quest4_b" or screenID == "accept_quest4_c") then
		setQuestStatus(playerID .. HavocSquadronScreenplay.TIER3_QUEST_STRING_4.name .. ":attempted", 1)

		assassinate_corellia_rebel_tier3_4:startQuest(pPlayer, pNpc)

	-- Quest 4: Failed retry
	elseif (screenID == "retry_quest4_a" or screenID == "retry_quest4_b") then
		assassinate_corellia_rebel_tier3_4:startQuest(pPlayer, pNpc)
	end

	return pClonedScreen
end
