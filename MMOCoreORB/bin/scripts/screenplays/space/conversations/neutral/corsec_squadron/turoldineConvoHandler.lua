turoldineConvoHandler = conv_handler:new {}

function turoldineConvoHandler:getInitialScreen(pPlayer, pNpc, pConvTemplate)
	if (pPlayer == nil or pNpc == nil or pConvTemplate == nil) then
		return nil
	end

	local convoTemplate = LuaConversationTemplate(pConvTemplate)

	local faction = CreatureObject(pPlayer):getFaction()
	local playerID = CreatureObject(pPlayer):getObjectID()

	-- JTL is disabled
	if (not isJtlEnabled()) then
		return convoTemplate:getScreen("not_pilot")
	end

	-- print("turoldineConvoHandler:getInitialScreen  -- called")

	-- Check if the players is a pilot
	if (not SpaceHelpers:isNeutralPilot(pPlayer)) then
		return convoTemplate:getScreen("not_pilot")
	end

	-- We know the player is a neutral pilot, check if pilot is a different squadron
	if (not SpaceHelpers:isCorsecSquadron(pPlayer)) then
		return convoTemplate:getScreen("pilot_not_corsec")
	end

	-- TESTING RESET
	--CorsecSquadronScreenplay:resetTuroldineQuests(pPlayer)

	local pGhost = CreatureObject(pPlayer):getPlayerObject()

	if (pGhost == nil) then
		return convoTemplate:getScreen("not_pilot")
	end

	local ghost = LuaPlayerObject(pGhost)

	if (ghost == nil) then
		return convoTemplate:getScreen("not_pilot")
	end

	local pilotTier = ghost:getPilotTier()

	-- Player is corsec pilot, but not proper tier
	if (pilotTier < 4) then
		return convoTemplate:getScreen("not_proper_tier")
	end

	local questOneStarted = SpaceHelpers:isSpaceQuestActive(pPlayer, CorsecSquadronScreenplay.TIER4_QUEST_STRING_1.type, CorsecSquadronScreenplay.TIER4_QUEST_STRING_1.name) or
							SpaceHelpers:isSpaceQuestActive(pPlayer, CorsecSquadronScreenplay.TIER4_QUEST_STRING_1_SIDE1.type, CorsecSquadronScreenplay.TIER4_QUEST_STRING_1_SIDE1.name) or
							SpaceHelpers:isSpaceQuestActive(pPlayer, CorsecSquadronScreenplay.TIER4_QUEST_STRING_1_SIDE2.type, CorsecSquadronScreenplay.TIER4_QUEST_STRING_1_SIDE2.name)
	local questTwoStarted = SpaceHelpers:isSpaceQuestActive(pPlayer, CorsecSquadronScreenplay.TIER4_QUEST_STRING_2.type, CorsecSquadronScreenplay.TIER4_QUEST_STRING_2.name) or
							SpaceHelpers:isSpaceQuestActive(pPlayer, CorsecSquadronScreenplay.TIER4_QUEST_STRING_2_SIDE1.type, CorsecSquadronScreenplay.TIER4_QUEST_STRING_2_SIDE1.name)
	local questThreeStarted = SpaceHelpers:isSpaceQuestActive(pPlayer, CorsecSquadronScreenplay.TIER4_QUEST_STRING_3.type, CorsecSquadronScreenplay.TIER4_QUEST_STRING_3.name) or
							SpaceHelpers:isSpaceQuestActive(pPlayer, CorsecSquadronScreenplay.TIER4_QUEST_STRING_3_SIDE1.type, CorsecSquadronScreenplay.TIER4_QUEST_STRING_3_SIDE1.name) or
							SpaceHelpers:isSpaceQuestActive(pPlayer, CorsecSquadronScreenplay.TIER4_QUEST_STRING_3_SIDE2A.type, CorsecSquadronScreenplay.TIER4_QUEST_STRING_3_SIDE2A.name) or
							SpaceHelpers:isSpaceQuestActive(pPlayer, CorsecSquadronScreenplay.TIER4_QUEST_STRING_3_SIDE2B.type, CorsecSquadronScreenplay.TIER4_QUEST_STRING_3_SIDE2B.name)
	local questFourStarted = SpaceHelpers:isSpaceQuestActive(pPlayer, CorsecSquadronScreenplay.TIER4_QUEST_STRING_4.type, CorsecSquadronScreenplay.TIER4_QUEST_STRING_4.name) or
							SpaceHelpers:isSpaceQuestActive(pPlayer, CorsecSquadronScreenplay.TIER4_QUEST_STRING_4_SIDE1.type, CorsecSquadronScreenplay.TIER4_QUEST_STRING_4_SIDE1.name) or
							SpaceHelpers:isSpaceQuestActive(pPlayer, CorsecSquadronScreenplay.TIER4_QUEST_STRING_4_SIDE2.type, CorsecSquadronScreenplay.TIER4_QUEST_STRING_4_SIDE2.name) or
							SpaceHelpers:isSpaceQuestActive(pPlayer, CorsecSquadronScreenplay.TIER4_QUEST_STRING_4_SIDE3.type, CorsecSquadronScreenplay.TIER4_QUEST_STRING_4_SIDE3.name)

	local questOneComplete = SpaceHelpers:isSpaceQuestComplete(pPlayer, CorsecSquadronScreenplay.TIER4_QUEST_STRING_1_SIDE2.type, CorsecSquadronScreenplay.TIER4_QUEST_STRING_1_SIDE2.name)
	local questTwoComplete = SpaceHelpers:isSpaceQuestComplete(pPlayer, CorsecSquadronScreenplay.TIER4_QUEST_STRING_2_SIDE1.type, CorsecSquadronScreenplay.TIER4_QUEST_STRING_2_SIDE1.name)
	local questThreeComplete = SpaceHelpers:isSpaceQuestComplete(pPlayer, CorsecSquadronScreenplay.TIER4_QUEST_STRING_3_SIDE2A.type, CorsecSquadronScreenplay.TIER4_QUEST_STRING_3_SIDE2A.name) or
							SpaceHelpers:isSpaceQuestComplete(pPlayer, CorsecSquadronScreenplay.TIER4_QUEST_STRING_3_SIDE2B.type, CorsecSquadronScreenplay.TIER4_QUEST_STRING_3_SIDE2B.name)
	local questFourComplete = SpaceHelpers:isSpaceQuestComplete(pPlayer, CorsecSquadronScreenplay.TIER4_QUEST_STRING_4_SIDE3.type, CorsecSquadronScreenplay.TIER4_QUEST_STRING_4_SIDE3.name)

	local duty1Started = SpaceHelpers:isSpaceQuestActive(pPlayer, CorsecSquadronScreenplay.TIER4_QUEST_STRING_DUTY_1.type, CorsecSquadronScreenplay.TIER4_QUEST_STRING_DUTY_1.name)
	local duty2Started = SpaceHelpers:isSpaceQuestActive(pPlayer, CorsecSquadronScreenplay.TIER4_QUEST_STRING_DUTY_2.type, CorsecSquadronScreenplay.TIER4_QUEST_STRING_DUTY_2.name)
	local duty3Started = SpaceHelpers:isSpaceQuestActive(pPlayer, CorsecSquadronScreenplay.TIER4_QUEST_STRING_DUTY_3.type, CorsecSquadronScreenplay.TIER4_QUEST_STRING_DUTY_3.name)
	local duty4Started = SpaceHelpers:isSpaceQuestActive(pPlayer, CorsecSquadronScreenplay.TIER4_QUEST_STRING_DUTY_4.type, CorsecSquadronScreenplay.TIER4_QUEST_STRING_DUTY_4.name)

	local duty1Complete = SpaceHelpers:isSpaceQuestComplete(pPlayer, CorsecSquadronScreenplay.TIER4_QUEST_STRING_DUTY_1.type, CorsecSquadronScreenplay.TIER4_QUEST_STRING_DUTY_1.name)
	local duty2Complete = SpaceHelpers:isSpaceQuestComplete(pPlayer, CorsecSquadronScreenplay.TIER4_QUEST_STRING_DUTY_2.type, CorsecSquadronScreenplay.TIER4_QUEST_STRING_DUTY_2.name)
	local duty3Complete = SpaceHelpers:isSpaceQuestComplete(pPlayer, CorsecSquadronScreenplay.TIER4_QUEST_STRING_DUTY_3.type, CorsecSquadronScreenplay.TIER4_QUEST_STRING_DUTY_3.name)
	local duty4Complete = SpaceHelpers:isSpaceQuestActive(pPlayer, CorsecSquadronScreenplay.TIER4_QUEST_STRING_DUTY_4.type, CorsecSquadronScreenplay.TIER4_QUEST_STRING_DUTY_4.name)

	local completedTier4 = SpaceHelpers:hasCompletedPilotTier(pPlayer, "neutral", 4)

	--[[
			Quests
	--]]

	-- Player has an active mission from Turoldine
	if ((questOneStarted and not questOneComplete) or (questTwoStarted and not questTwoComplete) or (questThreeStarted and not questThreeComplete) or (questFourStarted and not questFourComplete) or
		(duty1Started and not duty1Complete) or (duty2Started and not duty2Complete) or (duty3Started and not duty3Complete) or (duty4Started and not duty4Complete)) then

		return convoTemplate:getScreen("on_mission")

	-- Check if players have all the tier4 skill boxes and finished the last mission, then send them to next trainer.
	elseif (questFourComplete and completedTier4) then
		-- Players has all the skill boxes, they should be a tier 3. Increment if not proper
		if (ghost:getPilotTier() <= 4) then
			-- Increment pilot to Tier 5!
			ghost:incrementPilotTier()
		end

		-- Player has not earned the master box yet
		if (not SpaceHelpers:hasMasterSkill(pPlayer, "neutral")) then
			return convoTemplate:getScreen("master_mission")
		else
			return convoTemplate:getScreen("here_for_work2")
		end

	-- Reward Checks
	elseif (questFourComplete and getQuestStatus(playerID .. CorsecSquadronScreenplay.TIER4_QUEST_STRING_4.name .. ":reward") ~= "1") then
			return convoTemplate:getScreen("fourth_mission_success")
	elseif (questThreeComplete and getQuestStatus(playerID .. CorsecSquadronScreenplay.TIER4_QUEST_STRING_3.name .. ":reward") ~= "1") then
			return convoTemplate:getScreen("third_mission_success")
	elseif (questTwoComplete and getQuestStatus(playerID .. CorsecSquadronScreenplay.TIER4_QUEST_STRING_2.name .. ":reward") ~= "1") then
			return convoTemplate:getScreen("second_mission_success")
	elseif (questOneComplete and getQuestStatus(playerID .. CorsecSquadronScreenplay.TIER4_QUEST_STRING_1.name .. ":reward") ~= "1") then
			return convoTemplate:getScreen("first_mission_success")
	-- Pilot is able to train
	elseif (not completedTier4 and SpaceHelpers:hasExperienceForTraining(pPlayer, 4)) then
		return convoTemplate:getScreen("ready_train_pilot")

	-- Has not spoken to Turoldine yet
	elseif (getQuestStatus(playerID .. "CorsecSquadronScreenplay:StartedTuroldine") ~= "1") then
		setQuestStatus(playerID .. "CorsecSquadronScreenplay:StartedTuroldine", 1)

		return convoTemplate:getScreen("initial_briefing")
	-- Missions are not complete yet
	elseif (not questFourComplete) then
		-- Player is able to start fourth mission
		if (questThreeComplete and not questFourStarted) then
			if (getQuestStatus(playerID .. CorsecSquadronScreenplay.TIER4_QUEST_STRING_4.name .. ":attempted") == "1") then
				return convoTemplate:getScreen("failed_fourth_mission")
			else
				return convoTemplate:getScreen("fourth_mission")
			end

		-- Player is able to start third mission
		elseif (questTwoComplete and not questThreeStarted) then
			if (getQuestStatus(playerID .. CorsecSquadronScreenplay.TIER4_QUEST_STRING_3.name .. ":attempted") == "1") then
				return convoTemplate:getScreen("failed_third_mission")
			else
				return convoTemplate:getScreen("third_mission")
			end
		-- Player is able to start second mission
		elseif (questOneComplete and not questTwoStarted) then
			if (getQuestStatus(playerID .. CorsecSquadronScreenplay.TIER4_QUEST_STRING_2.name .. ":attempted") == "1") then
				return convoTemplate:getScreen("failed_second_mission")
			else
				return convoTemplate:getScreen("second_mission")
			end
		-- Player is ready for first mission, so either was not given it after training first box or failed
		elseif (not questOneComplete and SpaceHelpers:hasPilotTierSkill(pPlayer, "neutral", 4)) then
			if (getQuestStatus(playerID .. CorsecSquadronScreenplay.TIER4_QUEST_STRING_1.name .. ":attempted") == "1") then
				return convoTemplate:getScreen("failed_first_mission")
			else
				return convoTemplate:getScreen("first_mission")
			end
		end
	end

	return convoTemplate:getScreen("here_for_work2")
end

function turoldineConvoHandler:runScreenHandlers(pConvTemplate, pPlayer, pNpc, selectedOption, pConvScreen)
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

	-- print("turoldineConvoHandler:runScreenHandlers -- Screen ID: " .. screenID)

	local pGhost = CreatureObject(pPlayer):getPlayerObject()

	if (pGhost == nil) then
		return pClonedScreen
	end

	local ghost = LuaPlayerObject(pGhost)

	if (ghost == nil) then
		return pClonedScreen
	end

	if (screenID == "ready_train_pilot") then
		local skillManager = LuaSkillManager()

		local responseString = "initial_"

		if (SpaceHelpers:isSpaceQuestComplete(pPlayer, CorsecSquadronScreenplay.TIER4_QUEST_STRING_4_SIDE3.type, CorsecSquadronScreenplay.TIER4_QUEST_STRING_4_SIDE3.name)) then
			responseString = "final_"
		elseif (SpaceHelpers:isSpaceQuestComplete(pPlayer, CorsecSquadronScreenplay.TIER4_QUEST_STRING_3_SIDE2A.type, CorsecSquadronScreenplay.TIER4_QUEST_STRING_3_SIDE2A.name) or
					SpaceHelpers:isSpaceQuestComplete(pPlayer, CorsecSquadronScreenplay.TIER4_QUEST_STRING_3_SIDE2B.type, CorsecSquadronScreenplay.TIER4_QUEST_STRING_3_SIDE2B.name)) then
			responseString = "mission4_"
		elseif (SpaceHelpers:isSpaceQuestComplete(pPlayer, CorsecSquadronScreenplay.TIER4_QUEST_STRING_2_SIDE1.type, CorsecSquadronScreenplay.TIER4_QUEST_STRING_2_SIDE1.name)) then
			responseString = "mission3_"
		elseif (SpaceHelpers:isSpaceQuestComplete(pPlayer, CorsecSquadronScreenplay.TIER4_QUEST_STRING_1_SIDE2.type, CorsecSquadronScreenplay.TIER4_QUEST_STRING_1_SIDE2.name)) then
			responseString = "mission2_"
		end

		if (not CreatureObject(pPlayer):hasSkill("pilot_neutral_starships_04") and skillManager:fulfillsSkillPrerequisitesAndXp(pPlayer, "pilot_neutral_starships_04")) then
			clonedConversation:addOption("@conversation/corellia_privateer_tier4:s_2794eddd", responseString .. "train_fighters") -- I want to learn exotic vessels.
		end
		if (not CreatureObject(pPlayer):hasSkill("pilot_neutral_weapons_04") and skillManager:fulfillsSkillPrerequisitesAndXp(pPlayer, "pilot_neutral_weapons_04")) then
			clonedConversation:addOption("@conversation/corellia_privateer_tier4:s_e16cb1fa", responseString .. "train_components") -- I want to learn heavy starship component use.
		end
		if (not CreatureObject(pPlayer):hasSkill("pilot_neutral_procedures_04") and skillManager:fulfillsSkillPrerequisitesAndXp(pPlayer, "pilot_neutral_procedures_04")) then
			clonedConversation:addOption("@conversation/corellia_privateer_tier4:s_291ab969", responseString .. "train_techniques") -- I want to learn expert techniques.
		end
		if (not CreatureObject(pPlayer):hasSkill("pilot_neutral_droid_04") and skillManager:fulfillsSkillPrerequisitesAndXp(pPlayer, "pilot_neutral_droid_04")) then
			clonedConversation:addOption("@conversation/corellia_privateer_tier4:s_bc944dc4", responseString .. "train_algorithms") -- I want to learn droid intelligence theory.
		end

	-- Handle Skill box granting
	elseif (string.find(screenID, "_train_")) then
		local skillManager = LuaSkillManager()

		if (string.find(screenID, "train_fighters")) then
			if (skillManager:fulfillsSkillPrerequisitesAndXp(pPlayer, "pilot_neutral_starships_04")) then
				-- Train player Skill Box
				SpaceHelpers:grantSpaceSkill(pPlayer, "pilot_neutral_starships_04", true)
			end
		elseif (string.find(screenID, "train_components")) then
			if (skillManager:fulfillsSkillPrerequisitesAndXp(pPlayer, "pilot_neutral_weapons_04")) then
				-- Train player Skill Box
				SpaceHelpers:grantSpaceSkill(pPlayer, "pilot_neutral_weapons_04", true)
			end
		elseif (string.find(screenID, "train_techniques")) then
			if (skillManager:fulfillsSkillPrerequisitesAndXp(pPlayer, "pilot_neutral_procedures_04")) then
				-- Train player Skill Box
				SpaceHelpers:grantSpaceSkill(pPlayer, "pilot_neutral_procedures_04", true)
			end
		elseif (string.find(screenID, "train_algorithms")) then
			if (skillManager:fulfillsSkillPrerequisitesAndXp(pPlayer, "pilot_neutral_droid_04")) then
				-- Train player Skill Box
				SpaceHelpers:grantSpaceSkill(pPlayer, "pilot_neutral_droid_04", true)
			end
		end

		if (ghost:getPilotTier() <= 4 and SpaceHelpers:hasCompletedPilotTier(pPlayer, "neutral", 4)) then
			-- If player has all of the Tier 2 skills, increment their pilot tier
			ghost:incrementPilotTier()
		end

		-- Either the player is ready to train again or they have all of the missions finished, so send them back to the main screen
		if (SpaceHelpers:hasExperienceForTraining(pPlayer, 4) or SpaceHelpers:isSpaceQuestComplete(pPlayer, CorsecSquadronScreenplay.TIER4_QUEST_STRING_4_SIDE3.type, CorsecSquadronScreenplay.TIER4_QUEST_STRING_4_SIDE3.name)) then
			return self:getInitialScreen(pPlayer, pNpc, pConvTemplate)
		end

	-- Duty Missions
	elseif (screenID == "accept_duty1") then
		destroy_duty_corellia_privateer_tier4_1:startQuest(pPlayer, pNpc)
	elseif (screenID == "accept_duty2") then
		rescue_duty_corellia_privateer_tier4_1:startQuest(pPlayer, pNpc)
	elseif (screenID == "accept_duty3") then
		recovery_duty_corellia_privateer_tier4_1:startQuest(pPlayer, pNpc)
	elseif (screenID == "accept_duty4") then
		escort_duty_corellia_privateer_tier4_1:startQuest(pPlayer, pNpc)

	-- Mission Rewards
	elseif (screenID == "fourth_mission_success") then
		-- Give player the reward and update that they received it
		setQuestStatus(playerID .. CorsecSquadronScreenplay.TIER4_QUEST_STRING_4.name .. ":reward", 1)

		-- Grant Reward
		assassinate_corellia_privateer_tier4_4a:rewardPlayer(pPlayer)
	elseif (screenID == "third_mission_success") then
		-- Give player the reward and update that they received it
		setQuestStatus(playerID .. CorsecSquadronScreenplay.TIER4_QUEST_STRING_3.name .. ":reward", 1)

		-- Grant Reward
		space_battle_corellia_privateer_tier4_3a:rewardPlayer(pPlayer)
	elseif (screenID == "second_mission_success") then
		-- Give player the reward and update that they received it
		setQuestStatus(playerID .. CorsecSquadronScreenplay.TIER4_QUEST_STRING_2.name .. ":reward", 1)

		-- Grant Reward
		assassinate_corellia_privateer_tier4_2a:rewardPlayer(pPlayer)
	elseif (screenID == "first_mission_success") then
		-- Give player the reward and update that they received it
		setQuestStatus(playerID .. CorsecSquadronScreenplay.TIER4_QUEST_STRING_1.name .. ":reward", 1)

		-- Grant Reward
		patrol_corellia_privateer_tier4_1a:rewardPlayer(pPlayer)

	-- Give Missions
	elseif (screenID == "accept_fourth_mission" or screenID == "failed_fourth_mission") then
		setQuestStatus(playerID .. CorsecSquadronScreenplay.TIER4_QUEST_STRING_4.name .. ":attempted", 1)

		--	Give fourth mission to player
		assassinate_corellia_privateer_tier4_4a:startQuest(pPlayer, pNpc)
	elseif (screenID == "accept_third_mission" or screenID == "accept_third_mission2" or screenID == "failed_third_mission") then
		setQuestStatus(playerID .. CorsecSquadronScreenplay.TIER4_QUEST_STRING_3.name .. ":attempted", 1)

		--	Give third mission to player
		space_battle_corellia_privateer_tier4_3a:startQuest(pPlayer, pNpc)
	elseif (screenID == "accept_second_mission" or screenID == "failed_second_mission") then
		setQuestStatus(playerID .. CorsecSquadronScreenplay.TIER4_QUEST_STRING_2.name .. ":attempted", 1)

		--	Give second mission to player
		assassinate_corellia_privateer_tier4_2a:startQuest(pPlayer, pNpc)
	elseif (screenID == "accept_first_mission" or screenID == "failed_first_mission") then
		setQuestStatus(playerID .. CorsecSquadronScreenplay.TIER4_QUEST_STRING_1.name .. ":attempted", 1)

		--	Give first mission to player
		patrol_corellia_privateer_tier4_1a:startQuest(pPlayer, pNpc)
	end

	return pClonedScreen
end
