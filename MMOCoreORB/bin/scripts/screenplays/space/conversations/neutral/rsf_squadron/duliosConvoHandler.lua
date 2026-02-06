duliosConvoHandler = conv_handler:new {}

function duliosConvoHandler:getInitialScreen(pPlayer, pNpc, pConvTemplate)
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

	-- Check if player is RSF Pilot
	if (not SpaceHelpers:isRSFSquadron(pPlayer)) then
		return convoTemplate:getScreen("pilot_not_rsf")
	end

	local pGhost = CreatureObject(pPlayer):getPlayerObject()

	if (pGhost == nil) then
		return convoTemplate:getScreen("not_tier3")
	end

	local ghost = LuaPlayerObject(pGhost)

	if (ghost == nil) then
		return convoTemplate:getScreen("not_tier3")
	end

	-- RSF neutral pilot has not completed Tier2
	if (ghost:getPilotTier() < 3) then
		return convoTemplate:getScreen("not_tier3")
	end

	local questOneStarted = SpaceHelpers:isSpaceQuestActive(pPlayer, RsfSquadronScreenplay.TIER3_QUEST_STRING_1.type, RsfSquadronScreenplay.TIER3_QUEST_STRING_1.name) or
							SpaceHelpers:isSpaceQuestActive(pPlayer, RsfSquadronScreenplay.TIER3_QUEST_STRING_1_SIDE1.type, RsfSquadronScreenplay.TIER3_QUEST_STRING_1_SIDE1.name) or
							SpaceHelpers:isSpaceQuestActive(pPlayer, RsfSquadronScreenplay.TIER3_QUEST_STRING_1_SIDE2.type, RsfSquadronScreenplay.TIER3_QUEST_STRING_1_SIDE2.name) or
							SpaceHelpers:isSpaceQuestActive(pPlayer, RsfSquadronScreenplay.TIER3_QUEST_STRING_1_SIDE3.type, RsfSquadronScreenplay.TIER3_QUEST_STRING_1_SIDE3.name)
	local questTwoStarted = SpaceHelpers:isSpaceQuestActive(pPlayer, RsfSquadronScreenplay.TIER3_QUEST_STRING_2.type, RsfSquadronScreenplay.TIER3_QUEST_STRING_2.name) or
							SpaceHelpers:isSpaceQuestActive(pPlayer, RsfSquadronScreenplay.TIER3_QUEST_STRING_2_SIDE1.type, RsfSquadronScreenplay.TIER3_QUEST_STRING_2_SIDE1.name) or
							SpaceHelpers:isSpaceQuestActive(pPlayer, RsfSquadronScreenplay.TIER3_QUEST_STRING_2_SIDE2.type, RsfSquadronScreenplay.TIER3_QUEST_STRING_2_SIDE2.name) or
							SpaceHelpers:isSpaceQuestActive(pPlayer, RsfSquadronScreenplay.TIER3_QUEST_STRING_2_SIDE3.type, RsfSquadronScreenplay.TIER3_QUEST_STRING_2_SIDE3.name)
	local questThreeStarted = SpaceHelpers:isSpaceQuestActive(pPlayer, RsfSquadronScreenplay.TIER3_QUEST_STRING_3.type, RsfSquadronScreenplay.TIER3_QUEST_STRING_3.name) or
							SpaceHelpers:isSpaceQuestActive(pPlayer, RsfSquadronScreenplay.TIER3_QUEST_STRING_3_SIDE1.type, RsfSquadronScreenplay.TIER3_QUEST_STRING_3_SIDE1.name) or
							SpaceHelpers:isSpaceQuestActive(pPlayer, RsfSquadronScreenplay.TIER3_QUEST_STRING_3_SIDE2.type, RsfSquadronScreenplay.TIER3_QUEST_STRING_3_SIDE2.name) or
							SpaceHelpers:isSpaceQuestActive(pPlayer, RsfSquadronScreenplay.TIER3_QUEST_STRING_3_SIDE3.type, RsfSquadronScreenplay.TIER3_QUEST_STRING_3_SIDE3.name)
	local questFourStarted = SpaceHelpers:isSpaceQuestActive(pPlayer, RsfSquadronScreenplay.TIER3_QUEST_STRING_4.type, RsfSquadronScreenplay.TIER3_QUEST_STRING_4.name) or
							SpaceHelpers:isSpaceQuestActive(pPlayer, RsfSquadronScreenplay.TIER3_QUEST_STRING_4_SIDE1.type, RsfSquadronScreenplay.TIER3_QUEST_STRING_4_SIDE1.name)

	local questOneComplete = SpaceHelpers:isSpaceQuestComplete(pPlayer, RsfSquadronScreenplay.TIER3_QUEST_STRING_1_SIDE3.type, RsfSquadronScreenplay.TIER3_QUEST_STRING_1_SIDE3.name)
	local questTwoComplete = SpaceHelpers:isSpaceQuestComplete(pPlayer, RsfSquadronScreenplay.TIER3_QUEST_STRING_2_SIDE3.type, RsfSquadronScreenplay.TIER3_QUEST_STRING_2_SIDE3.name)
	local questThreeComplete = SpaceHelpers:isSpaceQuestComplete(pPlayer, RsfSquadronScreenplay.TIER3_QUEST_STRING_3_SIDE3.type, RsfSquadronScreenplay.TIER3_QUEST_STRING_3_SIDE3.name)
	local questFourComplete = SpaceHelpers:isSpaceQuestComplete(pPlayer, RsfSquadronScreenplay.TIER3_QUEST_STRING_4_SIDE1.type, RsfSquadronScreenplay.TIER3_QUEST_STRING_4_SIDE1.name)

	local completedTier3 = SpaceHelpers:hasCompletedPilotTier(pPlayer, "neutral", 3)

	-- Check if players have all the tier3 skill boxes and finished the last mission, then send them to next trainer.
	if (questFourComplete and completedTier3) then
		-- Players has all the skill boxes, they should be a tier 4. Increment if not proper
		if (ghost:getPilotTier() <= 3) then
			-- Increment pilot to Tier 4
			ghost:incrementPilotTier()
		end

		return convoTemplate:getScreen("completed_dulios")
	end

	--[[
			Quests
	--]]

	-- Player has an active mission from CDR Dulios
	if ((questOneStarted and not questOneComplete) or (questTwoStarted and not questTwoComplete) or (questThreeStarted and not questThreeComplete) or (questFourStarted and not questFourComplete)) then
		return convoTemplate:getScreen("on_mission")
	end

	local tier3SkillCount = SpaceHelpers:getPilotTierSkillCount(pPlayer, "neutral", 3)

	-- Reward Checks. Tier3 grants a skill box for each mission
	if (questFourComplete and tier3SkillCount == 3) then
		if (getQuestStatus(playerID .. RsfSquadronScreenplay.TIER3_QUEST_STRING_4.name .. ":reward") ~= "1") then
			setQuestStatus(playerID .. RsfSquadronScreenplay.TIER3_QUEST_STRING_4.name .. ":reward", 1)

			-- Grant Reward
			assassinate_naboo_privateer_tier3_4a:rewardPlayer(pPlayer)
		end

		return convoTemplate:getScreen("complete_mission4")
	elseif (questThreeComplete and tier3SkillCount == 2) then
		if (getQuestStatus(playerID .. RsfSquadronScreenplay.TIER3_QUEST_STRING_3.name .. ":reward") ~= "1") then
			setQuestStatus(playerID .. RsfSquadronScreenplay.TIER3_QUEST_STRING_3.name .. ":reward", 1)

			-- Grant Reward
			inspect_naboo_privateer_tier3_3a:rewardPlayer(pPlayer)
		end

		return convoTemplate:getScreen("complete_mission3")
	elseif (questTwoComplete and tier3SkillCount == 1) then
		if (getQuestStatus(playerID .. RsfSquadronScreenplay.TIER3_QUEST_STRING_2.name .. ":reward") ~= "1") then
			setQuestStatus(playerID .. RsfSquadronScreenplay.TIER3_QUEST_STRING_2.name .. ":reward", 1)

			-- Grant Reward
			escort_naboo_privateer_tier3_2a:rewardPlayer(pPlayer)
		end

		return convoTemplate:getScreen("complete_mission2")
	elseif (questOneComplete and tier3SkillCount < 1) then
		if (getQuestStatus(playerID .. RsfSquadronScreenplay.TIER3_QUEST_STRING_1.name .. ":reward") ~= "1") then
			setQuestStatus(playerID .. RsfSquadronScreenplay.TIER3_QUEST_STRING_1.name .. ":reward", 1)

			-- Grant Reward
			recovery_naboo_privateer_tier3_1a:rewardPlayer(pPlayer)
		end

		return convoTemplate:getScreen("complete_mission1")

	-- Mission Starters
	elseif (not questFourComplete) then
		-- Player is able to start fourth mission
		if (questThreeComplete and not questFourStarted) then
			if (getQuestStatus(playerID .. RsfSquadronScreenplay.TIER3_QUEST_STRING_4.name .. ":attempted") == "1") then
				return convoTemplate:getScreen("failed_fourth_mission")
			else
				return convoTemplate:getScreen("fourth_mission")
			end

		-- Player is able to start third mission
		elseif (questTwoComplete and not questThreeStarted) then
			if (getQuestStatus(playerID .. RsfSquadronScreenplay.TIER3_QUEST_STRING_3.name .. ":attempted") == "1") then
				return convoTemplate:getScreen("failed_third_mission")
			else
				return convoTemplate:getScreen("third_mission")
			end
		-- Player is able to start second mission
		elseif (questOneComplete and not questTwoStarted) then
			if (getQuestStatus(playerID .. RsfSquadronScreenplay.TIER3_QUEST_STRING_2.name .. ":attempted") == "1") then
				return convoTemplate:getScreen("failed_second_mission")
			else
				return convoTemplate:getScreen("second_mission")
			end
		-- Player is ready for first mission, so either was not given it after training first box or failed
		elseif (not questOneComplete) then
			if (getQuestStatus(playerID .. RsfSquadronScreenplay.TIER3_QUEST_STRING_1.name .. ":attempted") == "1") then
				return convoTemplate:getScreen("failed_first_mission")
			else
				return convoTemplate:getScreen("first_mission")
			end
		end
	end

	return convoTemplate:getScreen("not_tier3")
end

function duliosConvoHandler:runScreenHandlers(pConvTemplate, pPlayer, pNpc, selectedOption, pConvScreen)
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
			clonedConversation:addOption("@conversation/naboo_privateer_tier3:s_aa766bd6", "train_warships" .. screenAppend) -- I want to know about special warships.
		end
		if (not CreatureObject(pPlayer):hasSkill("pilot_neutral_weapons_03")) then
			clonedConversation:addOption("@conversation/naboo_privateer_tier3:s_a70b470e", "train_components" .. screenAppend) -- I want to know about advanced starship components.
		end
		if (not CreatureObject(pPlayer):hasSkill("pilot_neutral_procedures_03")) then
			clonedConversation:addOption("@conversation/naboo_privateer_tier3:s_da0e8cd0", "train_techniques" .. screenAppend) -- I want to know about advanced techniques.
		end
		if (not CreatureObject(pPlayer):hasSkill("pilot_neutral_droid_03")) then
			clonedConversation:addOption("@conversation/naboo_privateer_tier3:s_c28a300f", "train_programming" .. screenAppend) -- I want to know about system balance programming.
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
	elseif (screenID == "accept_fourth_mission" or screenID == "nothing_cant_handle") then
		setQuestStatus(playerID .. RsfSquadronScreenplay.TIER3_QUEST_STRING_4.name .. ":attempted", 1)

		--	Give fourth mission to player
		assassinate_naboo_privateer_tier3_4a:startQuest(pPlayer, pNpc)
	elseif (screenID == "accept_third_mission" or screenID == "i_was_better") then
		setQuestStatus(playerID .. RsfSquadronScreenplay.TIER3_QUEST_STRING_3.name .. ":attempted", 1)

		--	Give third mission to player
		inspect_naboo_privateer_tier3_3a:startQuest(pPlayer, pNpc)
	elseif (screenID == "accept_second_mission" or screenID == "stories_about_me") then
		setQuestStatus(playerID .. RsfSquadronScreenplay.TIER3_QUEST_STRING_2.name .. ":attempted", 1)

		--	Give second mission to player
		escort_naboo_privateer_tier3_2a:startQuest(pPlayer, pNpc)
	elseif (screenID == "accept_first_mission" or screenID == "try_first_again") then
		setQuestStatus(playerID .. RsfSquadronScreenplay.TIER3_QUEST_STRING_1.name .. ":attempted", 1)

		--	Give First mission to player
		recovery_naboo_privateer_tier3_1a:startQuest(pPlayer, pNpc)
	end

	return pClonedScreen
end
