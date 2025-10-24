ramnaConvoHandler = conv_handler:new {}

function ramnaConvoHandler:getInitialScreen(pPlayer, pNpc, pConvTemplate)
	if (pPlayer == nil or pNpc == nil or pConvTemplate == nil) then
		return nil
	end

	local convoTemplate = LuaConversationTemplate(pConvTemplate)

	local faction = CreatureObject(pPlayer):getFaction()
	local playerID = CreatureObject(pPlayer):getObjectID()

	-- JTL is disabled
	if (not isJtlEnabled()) then
		return convoTemplate:getScreen("not_tier3")
	end

	-- TESTING PRINT
	--print("ramnaConvoHandler:getInitialScreen  -- called")

	-- TESTING RESET
	--CorsecSquadronScreenplay:resetRamnaQuests(pPlayer)

	-- Check if player is Corsec Pilot
	if (not SpaceHelpers:isCorsecSquadron(pPlayer)) then
		return convoTemplate:getScreen("pilot_not_corsec")
	end

	local pGhost = CreatureObject(pPlayer):getPlayerObject()

	if (pGhost == nil) then
		return convoTemplate:getScreen("not_tier3")
	end

	local ghost = LuaPlayerObject(pGhost)

	if (ghost == nil) then
		return convoTemplate:getScreen("not_tier3")
	end

	-- Corsec neutral pilot has not completed Tier2
	if (ghost:getPilotTier() < 3) then
		return convoTemplate:getScreen("not_tier3")
	end

	local questOneStarted = SpaceHelpers:isSpaceQuestActive(pPlayer, CorsecSquadronScreenplay.TIER3_QUEST_STRING_1.type, CorsecSquadronScreenplay.TIER3_QUEST_STRING_1.name) or
							SpaceHelpers:isSpaceQuestActive(pPlayer, CorsecSquadronScreenplay.TIER3_QUEST_STRING_1_SIDE1.type, CorsecSquadronScreenplay.TIER3_QUEST_STRING_1_SIDE1.name) or
							SpaceHelpers:isSpaceQuestActive(pPlayer, CorsecSquadronScreenplay.TIER3_QUEST_STRING_1_SIDE2.type, CorsecSquadronScreenplay.TIER3_QUEST_STRING_1_SIDE2.name) or
							SpaceHelpers:isSpaceQuestActive(pPlayer, CorsecSquadronScreenplay.TIER3_QUEST_STRING_1_SIDE3.type, CorsecSquadronScreenplay.TIER3_QUEST_STRING_1_SIDE3.name)
	local questTwoStarted = SpaceHelpers:isSpaceQuestActive(pPlayer, CorsecSquadronScreenplay.TIER3_QUEST_STRING_2.type, CorsecSquadronScreenplay.TIER3_QUEST_STRING_2.name) or
							SpaceHelpers:isSpaceQuestActive(pPlayer, CorsecSquadronScreenplay.TIER3_QUEST_STRING_2_SIDE1.type, CorsecSquadronScreenplay.TIER3_QUEST_STRING_2_SIDE1.name) or
							SpaceHelpers:isSpaceQuestActive(pPlayer, CorsecSquadronScreenplay.TIER3_QUEST_STRING_2_SIDE2.type, CorsecSquadronScreenplay.TIER3_QUEST_STRING_2_SIDE2.name) or
							SpaceHelpers:isSpaceQuestActive(pPlayer, CorsecSquadronScreenplay.TIER3_QUEST_STRING_2_SIDE3.type, CorsecSquadronScreenplay.TIER3_QUEST_STRING_2_SIDE3.name)
	local questThreeStarted = SpaceHelpers:isSpaceQuestActive(pPlayer, CorsecSquadronScreenplay.TIER3_QUEST_STRING_3.type, CorsecSquadronScreenplay.TIER3_QUEST_STRING_3.name) or
							SpaceHelpers:isSpaceQuestActive(pPlayer, CorsecSquadronScreenplay.TIER3_QUEST_STRING_3_SIDE1.type, CorsecSquadronScreenplay.TIER3_QUEST_STRING_3_SIDE1.name) or
							SpaceHelpers:isSpaceQuestActive(pPlayer, CorsecSquadronScreenplay.TIER3_QUEST_STRING_3_SIDE2.type, CorsecSquadronScreenplay.TIER3_QUEST_STRING_3_SIDE2.name) or
							SpaceHelpers:isSpaceQuestActive(pPlayer, CorsecSquadronScreenplay.TIER3_QUEST_STRING_3_SIDE3.type, CorsecSquadronScreenplay.TIER3_QUEST_STRING_3_SIDE3.name)
	local questFourStarted = SpaceHelpers:isSpaceQuestActive(pPlayer, CorsecSquadronScreenplay.TIER3_QUEST_STRING_4.type, CorsecSquadronScreenplay.TIER3_QUEST_STRING_4.name) or
							SpaceHelpers:isSpaceQuestActive(pPlayer, CorsecSquadronScreenplay.TIER3_QUEST_STRING_4_SIDE1.type, CorsecSquadronScreenplay.TIER3_QUEST_STRING_4_SIDE1.name)

	local questOneComplete = SpaceHelpers:isSpaceQuestComplete(pPlayer, CorsecSquadronScreenplay.TIER3_QUEST_STRING_1_SIDE3.type, CorsecSquadronScreenplay.TIER3_QUEST_STRING_1_SIDE3.name)
	local questTwoComplete = SpaceHelpers:isSpaceQuestComplete(pPlayer, CorsecSquadronScreenplay.TIER3_QUEST_STRING_2_SIDE3.type, CorsecSquadronScreenplay.TIER3_QUEST_STRING_2_SIDE3.name)
	local questThreeComplete = SpaceHelpers:isSpaceQuestComplete(pPlayer, CorsecSquadronScreenplay.TIER3_QUEST_STRING_3_SIDE3.type, CorsecSquadronScreenplay.TIER3_QUEST_STRING_3_SIDE3.name)
	local questFourComplete = SpaceHelpers:isSpaceQuestComplete(pPlayer, CorsecSquadronScreenplay.TIER3_QUEST_STRING_4_SIDE1.type, CorsecSquadronScreenplay.TIER3_QUEST_STRING_4_SIDE1.name)

	local completedTier3 = SpaceHelpers:hasCompletedPilotTier(pPlayer, "neutral", 3)

	-- Check if players have all the tier3 skill boxes and finished the last mission, then send them to next trainer.
	if (questFourComplete and completedTier3) then
		-- Players has all the skill boxes, they should be a tier 4. Increment if not proper
		if (ghost:getPilotTier() <= 3) then
			-- Increment pilot to Tier 4
			ghost:incrementPilotTier()
		end

		return convoTemplate:getScreen("completed_ramna")
	end

	--[[
			Quests
	--]]

	-- Player has an active mission from CDR Ramna
	if ((questOneStarted and not questOneComplete) or (questTwoStarted and not questTwoComplete) or (questThreeStarted and not questThreeComplete) or (questFourStarted and not questFourComplete)) then
		return convoTemplate:getScreen("on_mission")
	end

	local tier3SkillCount = SpaceHelpers:getPilotTierSkillCount(pPlayer, "neutral", 3)

	-- Reward Checks. Tier3 grants a skill box for each mission
	if (questFourComplete and tier3SkillCount == 3) then
		if (getQuestStatus(playerID .. CorsecSquadronScreenplay.TIER3_QUEST_STRING_4.name .. ":reward") ~= "1") then
			setQuestStatus(playerID .. CorsecSquadronScreenplay.TIER3_QUEST_STRING_4.name .. ":reward", 1)

			-- Grant Reward
			assassinate_corellia_privateer_tier3_4:rewardPlayer(pPlayer)
		end

		return convoTemplate:getScreen("complete_mission4")
	elseif (questThreeComplete and tier3SkillCount == 2) then
		if (getQuestStatus(playerID .. CorsecSquadronScreenplay.TIER3_QUEST_STRING_3.name .. ":reward") ~= "1") then
			setQuestStatus(playerID .. CorsecSquadronScreenplay.TIER3_QUEST_STRING_3.name .. ":reward", 1)

			-- Grant Reward
			delivery_corellia_privateer_tier3_3:rewardPlayer(pPlayer)
		end

		return convoTemplate:getScreen("complete_mission3")
	elseif (questTwoComplete and tier3SkillCount == 1) then
		if (getQuestStatus(playerID .. CorsecSquadronScreenplay.TIER3_QUEST_STRING_2.name .. ":reward") ~= "1") then
			setQuestStatus(playerID .. CorsecSquadronScreenplay.TIER3_QUEST_STRING_2.name .. ":reward", 1)

			-- Grant Reward
			inspect_corellia_privateer_tier3_2:rewardPlayer(pPlayer)
		end

		return convoTemplate:getScreen("complete_mission2")
	elseif (questOneComplete and tier3SkillCount < 1) then
		if (getQuestStatus(playerID .. CorsecSquadronScreenplay.TIER3_QUEST_STRING_1.name .. ":reward") ~= "1") then
			setQuestStatus(playerID .. CorsecSquadronScreenplay.TIER3_QUEST_STRING_1.name .. ":reward", 1)

			-- Grant Reward
			recovery_corellia_privateer_tier3_1:rewardPlayer(pPlayer)
		end

		return convoTemplate:getScreen("complete_mission1")

	-- Mission Starters
	elseif (not questFourComplete) then
		-- Player is able to start fourth mission
		if (questThreeComplete and not questFourStarted) then
			if (getQuestStatus(playerID .. CorsecSquadronScreenplay.TIER3_QUEST_STRING_4.name .. ":attempted") == "1") then
				return convoTemplate:getScreen("failed_fourth_mission")
			else
				return convoTemplate:getScreen("fourth_mission")
			end

		-- Player is able to start third mission
		elseif (questTwoComplete and not questThreeStarted) then
			if (getQuestStatus(playerID .. CorsecSquadronScreenplay.TIER3_QUEST_STRING_3.name .. ":attempted") == "1") then
				return convoTemplate:getScreen("failed_third_mission")
			else
				return convoTemplate:getScreen("third_mission")
			end
		-- Player is able to start second mission
		elseif (questOneComplete and not questTwoStarted) then
			if (getQuestStatus(playerID .. CorsecSquadronScreenplay.TIER3_QUEST_STRING_2.name .. ":attempted") == "1") then
				return convoTemplate:getScreen("failed_second_mission")
			else
				return convoTemplate:getScreen("second_mission")
			end
		-- Player is ready for first mission, so either was not given it after training first box or failed
		elseif (not questOneComplete) then
			if (getQuestStatus(playerID .. CorsecSquadronScreenplay.TIER3_QUEST_STRING_1.name .. ":attempted") == "1") then
				return convoTemplate:getScreen("failed_first_mission")
			else
				return convoTemplate:getScreen("first_mission")
			end
		end
	end

	return convoTemplate:getScreen("not_tier3")
end

function ramnaConvoHandler:runScreenHandlers(pConvTemplate, pPlayer, pNpc, selectedOption, pConvScreen)
	if (pPlayer == nil or pConvScreen == nil) then
		return
	end

	local screen = LuaConversationScreen(pConvScreen)
	local screenID = screen:getScreenID()
	local playerID = CreatureObject(pPlayer):getObjectID()

	local pClonedScreen = screen:cloneScreen()
	local clonedConversation = LuaConversationScreen(pClonedScreen)

	-- Set player as conversation target
	clonedConversation:setDialogTextTU(CreatureObject(pPlayer):getFirstName())

	--print("ramnaConvoHandler:runScreenHandlers -- Screen ID: " .. screenID)

	local pGhost = CreatureObject(pPlayer):getPlayerObject()

	if (pGhost == nil) then
		return pClonedScreen
	end

	local ghost = LuaPlayerObject(pGhost)

	if (ghost == nil) then
		return pClonedScreen
	end

	if (string.find(screenID, "complete_mission")) then
		local screenAppend = ""

		if (screenID == "complete_mission4") then
			screenAppend = "_final"
		end

		if (not CreatureObject(pPlayer):hasSkill("pilot_neutral_starships_03")) then
			clonedConversation:addOption("@conversation/corellia_privateer_tier3:s_3b154409", "train_warships" .. screenAppend) -- How about special warships?
		end
		if (not CreatureObject(pPlayer):hasSkill("pilot_neutral_weapons_03")) then
			clonedConversation:addOption("@conversation/corellia_privateer_tier3:s_44a12a06", "train_components" .. screenAppend) -- How about advanced starship component use?
		end
		if (not CreatureObject(pPlayer):hasSkill("pilot_neutral_procedures_03")) then
			clonedConversation:addOption("@conversation/corellia_privateer_tier3:s_25c1d490", "train_techniques" .. screenAppend) -- How about advanced techniques?
		end
		if (not CreatureObject(pPlayer):hasSkill("pilot_neutral_droid_03")) then
			clonedConversation:addOption("@conversation/corellia_privateer_tier3:s_88451b48", "train_programming" .. screenAppend) -- How about system balance programming?
		end

	-- Handle Skill box granting
	elseif (string.find(screenID, "train_")) then
		if (string.find(screenID, "train_warships")) then
			-- Train player Skill Box
			SpaceHelpers:grantSpaceSkill(pPlayer, "pilot_neutral_starships_03", false)
		elseif (string.find(screenID, "train_components")) then
			-- Train player Skill Box
			SpaceHelpers:grantSpaceSkill(pPlayer, "pilot_neutral_weapons_03", false)
		elseif (string.find(screenID, "train_techniques")) then
			-- Train player Skill Box
			SpaceHelpers:grantSpaceSkill(pPlayer, "pilot_neutral_procedures_03", false)
		elseif (string.find(screenID, "train_programming")) then
			-- Train player Skill Box
			SpaceHelpers:grantSpaceSkill(pPlayer, "pilot_neutral_droid_03", false)
		end

		if (ghost:getPilotTier() <= 3 and SpaceHelpers:hasCompletedPilotTier(pPlayer, "neutral", 3)) then
			-- If player has all of the Tier 3 skills, increment their pilot tier
			ghost:incrementPilotTier()
		end

	-- Give Missions
	elseif (screenID == "intercept_in_endor" or screenID == "get_back_out" or screenID == "see_you_soon") then
		setQuestStatus(playerID .. CorsecSquadronScreenplay.TIER3_QUEST_STRING_4.name .. ":attempted", 1)

		--	Give fourth mission to player
		assassinate_corellia_privateer_tier3_4:startQuest(pPlayer, pNpc)
	elseif (screenID == "dant_operations" or screenID == "go_back_get_some") then
		setQuestStatus(playerID .. CorsecSquadronScreenplay.TIER3_QUEST_STRING_3.name .. ":attempted", 1)

		--	Give third mission to player
		delivery_corellia_privateer_tier3_3:startQuest(pPlayer, pNpc)
	elseif (screenID == "good_luck_mission2" or screenID == "good_luck_mission2_2" or screenID == "need_good_news" or screenID == "then_go_fight") then
		setQuestStatus(playerID .. CorsecSquadronScreenplay.TIER3_QUEST_STRING_2.name .. ":attempted", 1)

		--	Give second mission to player
		inspect_corellia_privateer_tier3_2:startQuest(pPlayer, pNpc)
	elseif (screenID == "dont_care" or screenID == "keep_going" or screenID == "exactly1") then
		setQuestStatus(playerID .. CorsecSquadronScreenplay.TIER3_QUEST_STRING_1.name .. ":attempted", 1)

		--	Give First mission to player
		recovery_corellia_privateer_tier3_1:startQuest(pPlayer, pNpc)
	end

	return pClonedScreen
end
