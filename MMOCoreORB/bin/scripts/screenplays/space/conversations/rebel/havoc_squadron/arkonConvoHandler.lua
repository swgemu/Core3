local SpaceHelpers = require("utils.space_helpers")

arkonConvoHandler = conv_handler:new {}

function arkonConvoHandler:getInitialScreen(pPlayer, pNpc, pConvTemplate)
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

	-- Check if player has completed Tier 3 (required before talking to Arkon)
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

	local questOneComplete = SpaceHelpers:isSpaceQuestComplete(pPlayer, HavocSquadronScreenplay.TIER4_QUEST_STRING_1.type, HavocSquadronScreenplay.TIER4_QUEST_STRING_1.name)
	local questTwoComplete = SpaceHelpers:isSpaceQuestComplete(pPlayer, HavocSquadronScreenplay.TIER4_QUEST_STRING_2.type, HavocSquadronScreenplay.TIER4_QUEST_STRING_2.name)
	local questThreeComplete = SpaceHelpers:isSpaceQuestComplete(pPlayer, HavocSquadronScreenplay.TIER4_QUEST_STRING_3.type, HavocSquadronScreenplay.TIER4_QUEST_STRING_3.name)
	local questFourComplete = SpaceHelpers:isSpaceQuestComplete(pPlayer, HavocSquadronScreenplay.TIER4_QUEST_STRING_4.type, HavocSquadronScreenplay.TIER4_QUEST_STRING_4.name)

	-- Duty mission checks
	local duty1Started = SpaceHelpers:isSpaceQuestActive(pPlayer, HavocSquadronScreenplay.TIER4_QUEST_STRING_DUTY_1.type, HavocSquadronScreenplay.TIER4_QUEST_STRING_DUTY_1.name)
	local duty2Started = SpaceHelpers:isSpaceQuestActive(pPlayer, HavocSquadronScreenplay.TIER4_QUEST_STRING_DUTY_2.type, HavocSquadronScreenplay.TIER4_QUEST_STRING_DUTY_2.name)
	local duty3Started = SpaceHelpers:isSpaceQuestActive(pPlayer, HavocSquadronScreenplay.TIER4_QUEST_STRING_DUTY_3.type, HavocSquadronScreenplay.TIER4_QUEST_STRING_DUTY_3.name)
	local duty4Started = SpaceHelpers:isSpaceQuestActive(pPlayer, HavocSquadronScreenplay.TIER4_QUEST_STRING_DUTY_4.type, HavocSquadronScreenplay.TIER4_QUEST_STRING_DUTY_4.name)

	local duty1Complete = SpaceHelpers:isSpaceQuestComplete(pPlayer, HavocSquadronScreenplay.TIER4_QUEST_STRING_DUTY_1.type, HavocSquadronScreenplay.TIER4_QUEST_STRING_DUTY_1.name)
	local duty2Complete = SpaceHelpers:isSpaceQuestComplete(pPlayer, HavocSquadronScreenplay.TIER4_QUEST_STRING_DUTY_2.type, HavocSquadronScreenplay.TIER4_QUEST_STRING_DUTY_2.name)
	local duty3Complete = SpaceHelpers:isSpaceQuestComplete(pPlayer, HavocSquadronScreenplay.TIER4_QUEST_STRING_DUTY_3.type, HavocSquadronScreenplay.TIER4_QUEST_STRING_DUTY_3.name)
	local duty4Complete = SpaceHelpers:isSpaceQuestComplete(pPlayer, HavocSquadronScreenplay.TIER4_QUEST_STRING_DUTY_4.type, HavocSquadronScreenplay.TIER4_QUEST_STRING_DUTY_4.name)

	-- Player has an active story or duty quest from Arkon
	if ((questOneStarted and not questOneComplete) or (questTwoStarted and not questTwoComplete) or
		(questThreeStarted and not questThreeComplete) or (questFourStarted and not questFourComplete) or
		(duty1Started and not duty1Complete) or (duty2Started and not duty2Complete) or
		(duty3Started and not duty3Complete) or (duty4Started and not duty4Complete)) then
		return convoTemplate:getScreen("has_mission")
	end

	-- Player has negative faction standing with the Rebel Alliance
	if (ghost:getFactionStanding("rebel") < 0) then
		return convoTemplate:getScreen("negative_faction")
	end

	--[[
		Reward Checks - Quest complete but reward not yet given
		NOTE: These MUST run before the completed tier check, otherwise the quest 4
		reward is skipped when all tier 4 skills are already trained.
	]]

	-- Player has completed quest 4 and needs reward
	if (questFourComplete and getQuestStatus(playerID .. HavocSquadronScreenplay.TIER4_QUEST_STRING_4.name .. ":reward") ~= "1") then
		setQuestStatus(playerID .. HavocSquadronScreenplay.TIER4_QUEST_STRING_4.name .. ":reward", 1)

		-- Grant Reward via quest reward system
		recovery_corellia_rebel_tier4_4:rewardPlayer(pPlayer)

		return convoTemplate:getScreen("excellent_work4")
	-- Player has completed quest 3 and needs reward
	elseif (questThreeComplete and getQuestStatus(playerID .. HavocSquadronScreenplay.TIER4_QUEST_STRING_3.name .. ":reward") ~= "1") then
		setQuestStatus(playerID .. HavocSquadronScreenplay.TIER4_QUEST_STRING_3.name .. ":reward", 1)

		-- Grant Reward
		space_battle_corellia_rebel_tier4_3:rewardPlayer(pPlayer)

		return convoTemplate:getScreen("excellent_work3")
	-- Player has completed quest 2 and needs reward
	elseif (questTwoComplete and getQuestStatus(playerID .. HavocSquadronScreenplay.TIER4_QUEST_STRING_2.name .. ":reward") ~= "1") then
		setQuestStatus(playerID .. HavocSquadronScreenplay.TIER4_QUEST_STRING_2.name .. ":reward", 1)

		-- Grant Reward
		assassinate_corellia_rebel_tier4_2:rewardPlayer(pPlayer)

		return convoTemplate:getScreen("excellent_work2")
	-- Player has completed quest 1 and needs reward
	elseif (questOneComplete and getQuestStatus(playerID .. HavocSquadronScreenplay.TIER4_QUEST_STRING_1.name .. ":reward") ~= "1") then
		setQuestStatus(playerID .. HavocSquadronScreenplay.TIER4_QUEST_STRING_1.name .. ":reward", 1)

		-- Grant Reward
		survival_corellia_rebel_tier4_1:rewardPlayer(pPlayer)

		return convoTemplate:getScreen("excellent_work")
	end

	local completedTier4 = SpaceHelpers:hasCompletedPilotTier(pPlayer, "rebel_navy", 4)

	-- Check if players have all the tier 4 skill boxes and completed final quest
	if (questFourComplete and completedTier4) then
		-- Increment pilot tier if not already
		if (ghost:getPilotTier() <= 4) then
			ghost:incrementPilotTier()
		end

		-- Player has not earned the master box yet
		if (not SpaceHelpers:hasMasterSkill(pPlayer, "rebel_navy")) then
			return convoTemplate:getScreen("master_mission")
		else
			return convoTemplate:getScreen("completed_arkon")
		end
	end

	-- Player has a Tier 4 skill box but not all 4 (needs training - safety net for interrupted conversations)
	if (not completedTier4 and SpaceHelpers:hasPilotTierSkill(pPlayer, "rebel_navy", 4)) then
		return convoTemplate:getScreen("ready_train_pilot")
	end

	--[[
		Quest Granting
	]]

	if (not questFourComplete) then
		-- Player is able to start fourth mission
		if (questThreeComplete and not questFourStarted) then
			if (getQuestStatus(playerID .. HavocSquadronScreenplay.TIER4_QUEST_STRING_4.name .. ":attempted") == "1") then
				return convoTemplate:getScreen("failed_quest4")
			else
				return convoTemplate:getScreen("fourth_mission")
			end
		-- Player is able to start third mission
		elseif (questTwoComplete and not questThreeStarted) then
			if (getQuestStatus(playerID .. HavocSquadronScreenplay.TIER4_QUEST_STRING_3.name .. ":attempted") == "1") then
				return convoTemplate:getScreen("failed_quest3")
			else
				return convoTemplate:getScreen("third_mission")
			end
		-- Player is able to start second mission
		elseif (questOneComplete and not questTwoStarted) then
			if (getQuestStatus(playerID .. HavocSquadronScreenplay.TIER4_QUEST_STRING_2.name .. ":attempted") == "1") then
				return convoTemplate:getScreen("failed_quest2")
			else
				return convoTemplate:getScreen("second_mission")
			end
		-- Player is ready for first mission (has a tier 4 skill from training)
		elseif (not questOneComplete and SpaceHelpers:hasPilotTierSkill(pPlayer, "rebel_navy", 4)) then
			if (getQuestStatus(playerID .. HavocSquadronScreenplay.TIER4_QUEST_STRING_1.name .. ":attempted") == "1") then
				return convoTemplate:getScreen("failed_quest1")
			else
				return convoTemplate:getScreen("first_mission")
			end
		end
	end

	-- Player has met Arkon before but needs to grind XP via duty missions
	if (getQuestStatus(playerID .. "HavocSquadronScreenplay:MetArkonTier4") == "1") then
		return convoTemplate:getScreen("duty_menu")
	end

	-- New pilot to Arkon (first meeting)
	return convoTemplate:getScreen("introduction")
end

function arkonConvoHandler:runScreenHandlers(pConvTemplate, pPlayer, pNpc, selectedOption, pConvScreen)
	if (pPlayer == nil or pConvScreen == nil) then
		return
	end

	local screen = LuaConversationScreen(pConvScreen)
	local screenID = screen:getScreenID()
	local playerID = CreatureObject(pPlayer):getObjectID()

	local pClonedScreen = screen:cloneScreen()
	local clonedConversation = LuaConversationScreen(pClonedScreen)

	-- Set player name tokens
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
		Skill Training Menu - Dynamically add skill options based on missing Tier 4 skills
	]]
	if (screenID == "ready_train_pilot") then
		local responseString = "initial_"

		if (SpaceHelpers:isSpaceQuestComplete(pPlayer, HavocSquadronScreenplay.TIER4_QUEST_STRING_4.type, HavocSquadronScreenplay.TIER4_QUEST_STRING_4.name)) then
			responseString = "final_"
		elseif (SpaceHelpers:isSpaceQuestComplete(pPlayer, HavocSquadronScreenplay.TIER4_QUEST_STRING_3.type, HavocSquadronScreenplay.TIER4_QUEST_STRING_3.name)) then
			responseString = "mission4_"
		elseif (SpaceHelpers:isSpaceQuestComplete(pPlayer, HavocSquadronScreenplay.TIER4_QUEST_STRING_2.type, HavocSquadronScreenplay.TIER4_QUEST_STRING_2.name)) then
			responseString = "mission3_"
		elseif (SpaceHelpers:isSpaceQuestComplete(pPlayer, HavocSquadronScreenplay.TIER4_QUEST_STRING_1.type, HavocSquadronScreenplay.TIER4_QUEST_STRING_1.name)) then
			responseString = "mission2_"
		end

		if (not CreatureObject(pPlayer):hasSkill("pilot_rebel_navy_starships_04")) then
			clonedConversation:addOption("@conversation/corellia_rebel_tier4:s_2a5db9a8", responseString .. "train_fighters") -- I would like hyper-maneuverable starfighters, please.
		end
		if (not CreatureObject(pPlayer):hasSkill("pilot_rebel_navy_weapons_04")) then
			clonedConversation:addOption("@conversation/corellia_rebel_tier4:s_77758001", responseString .. "train_components") -- I would like heavy starship component use, please.
		end
		if (not CreatureObject(pPlayer):hasSkill("pilot_rebel_navy_procedures_04")) then
			clonedConversation:addOption("@conversation/corellia_rebel_tier4:s_6065ab8b", responseString .. "train_procedures") -- I would like special weapons and tactics, please.
		end
		if (not CreatureObject(pPlayer):hasSkill("pilot_rebel_navy_droid_04")) then
			clonedConversation:addOption("@conversation/corellia_rebel_tier4:s_f819adf9", responseString .. "train_droid") -- I would like droid intelligence theory, please.
		end

	--[[
		Skill Granting - Grant the selected Tier 4 skill
	]]
	elseif (string.find(screenID, "_train_")) then
		if (string.find(screenID, "train_fighters")) then
			SpaceHelpers:grantSpaceSkill(pPlayer, "pilot_rebel_navy_starships_04", false)
		elseif (string.find(screenID, "train_components")) then
			SpaceHelpers:grantSpaceSkill(pPlayer, "pilot_rebel_navy_weapons_04", false)
		elseif (string.find(screenID, "train_procedures")) then
			SpaceHelpers:grantSpaceSkill(pPlayer, "pilot_rebel_navy_procedures_04", false)
		elseif (string.find(screenID, "train_droid")) then
			SpaceHelpers:grantSpaceSkill(pPlayer, "pilot_rebel_navy_droid_04", false)
		end

		-- Check if all Tier 4 skills are now complete
		if (ghost:getPilotTier() <= 4 and SpaceHelpers:hasCompletedPilotTier(pPlayer, "rebel_navy", 4)) then
			ghost:incrementPilotTier()
		end

		return pClonedScreen

	--[[
		First Meeting - Set metTier4 flag so introduction doesn't replay
	]]
	elseif (screenID == "intro_arkon") then
		setQuestStatus(playerID .. "HavocSquadronScreenplay:MetArkonTier4", 1)

	--[[
		Duty Mission Granting
	]]
	elseif (screenID == "accept_duty1") then
		escort_duty_corellia_rebel_tier4_1:startQuest(pPlayer, pNpc)
	elseif (screenID == "accept_duty2") then
		rescue_duty_corellia_rebel_tier4_1:startQuest(pPlayer, pNpc)
	elseif (screenID == "accept_duty3") then
		recovery_duty_corellia_rebel_tier4_1:startQuest(pPlayer, pNpc)
	elseif (screenID == "accept_duty4") then
		destroy_duty_corellia_rebel_tier4_1:startQuest(pPlayer, pNpc)

	--[[
		Quest Granting - Start missions on terminal accept screens
	]]

	-- Quest 1: Survival mission (Black Sun assault)
	elseif (screenID == "accept_quest1_a" or screenID == "accept_quest1_b" or screenID == "accept_quest1_c") then
		setQuestStatus(playerID .. HavocSquadronScreenplay.TIER4_QUEST_STRING_1.name .. ":attempted", 1)

		survival_corellia_rebel_tier4_1:startQuest(pPlayer, pNpc)

	-- Quest 1: Failed retry
	elseif (screenID == "retry_quest1_a" or screenID == "retry_quest1_b") then
		survival_corellia_rebel_tier4_1:startQuest(pPlayer, pNpc)

	-- Quest 2: Assassinate mission (Inquisitor intercept)
	elseif (screenID == "accept_quest2_a" or screenID == "accept_quest2_b") then
		setQuestStatus(playerID .. HavocSquadronScreenplay.TIER4_QUEST_STRING_2.name .. ":attempted", 1)

		assassinate_corellia_rebel_tier4_2:startQuest(pPlayer, pNpc)

	-- Quest 2: Failed retry
	elseif (screenID == "retry_quest2_a" or screenID == "retry_quest2_b") then
		assassinate_corellia_rebel_tier4_2:startQuest(pPlayer, pNpc)

	-- Quest 3: Space battle mission (Imperial base strike)
	elseif (screenID == "accept_quest3_a" or screenID == "accept_quest3_b" or screenID == "accept_quest3_c") then
		setQuestStatus(playerID .. HavocSquadronScreenplay.TIER4_QUEST_STRING_3.name .. ":attempted", 1)

		space_battle_corellia_rebel_tier4_3:startQuest(pPlayer, pNpc)

	-- Quest 3: Failed retry
	elseif (screenID == "retry_quest3_a" or screenID == "retry_quest3_b") then
		space_battle_corellia_rebel_tier4_3:startQuest(pPlayer, pNpc)

	-- Quest 4: Recovery mission (scientist rescue)
	elseif (screenID == "accept_quest4_a" or screenID == "accept_quest4_b") then
		setQuestStatus(playerID .. HavocSquadronScreenplay.TIER4_QUEST_STRING_4.name .. ":attempted", 1)

		recovery_corellia_rebel_tier4_4:startQuest(pPlayer, pNpc)

	-- Quest 4: Failed retry
	elseif (screenID == "retry_quest4_a" or screenID == "retry_quest4_b") then
		recovery_corellia_rebel_tier4_4:startQuest(pPlayer, pNpc)

	-- Master Quest: Destroy mission
	elseif (screenID == "accept_master_quest") then
		destroy_corellia_rebel_master:startQuest(pPlayer, pNpc)
	end

	return pClonedScreen
end
