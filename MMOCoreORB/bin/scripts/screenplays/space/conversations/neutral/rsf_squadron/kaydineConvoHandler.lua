kaydineConvoHandler = conv_handler:new {}

function kaydineConvoHandler:getInitialScreen(pPlayer, pNpc, pConvTemplate)
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

	-- Check if player has any pilot skills
	if (not SpaceHelpers:isNeutralPilot(pPlayer)) then
		return convoTemplate:getScreen("not_pilot")
	end

	-- We know the player is a neutral pilot, check if pilot is a different squadron
	if (not SpaceHelpers:isRSFSquadron(pPlayer)) then
		return convoTemplate:getScreen("pilot_not_rsf")
	end

	local pGhost = CreatureObject(pPlayer):getPlayerObject()

	if (pGhost == nil) then
		return convoTemplate:getScreen("not_pilot")
	end

	local ghost = LuaPlayerObject(pGhost)

	if (ghost == nil) then
		return convoTemplate:getScreen("not_pilot")
	end

	-- RSF neutral pilot has completed Tier 3
	if (ghost:getPilotTier() > 3) then
		return convoTemplate:getScreen("finished_tier3")
	end

	-- Player hasn't completed Tier 1 yet
	if (ghost:getPilotTier() < 2) then
		return convoTemplate:getScreen("not_ready_tier2")
	end

	local questOneStarted = SpaceHelpers:isSpaceQuestActive(pPlayer, RsfSquadronScreenplay.TIER2_QUEST_STRING_1.type, RsfSquadronScreenplay.TIER2_QUEST_STRING_1.name)
	local questTwoStarted = SpaceHelpers:isSpaceQuestActive(pPlayer, RsfSquadronScreenplay.TIER2_QUEST_STRING_2.type, RsfSquadronScreenplay.TIER2_QUEST_STRING_2.name)
	local questThreeStarted = SpaceHelpers:isSpaceQuestActive(pPlayer, RsfSquadronScreenplay.TIER2_QUEST_STRING_3.type, RsfSquadronScreenplay.TIER2_QUEST_STRING_3.name)
	local questFourStarted = SpaceHelpers:isSpaceQuestActive(pPlayer, RsfSquadronScreenplay.TIER2_QUEST_STRING_4.type, RsfSquadronScreenplay.TIER2_QUEST_STRING_4.name)

	local questOneComplete = SpaceHelpers:isSpaceQuestComplete(pPlayer, RsfSquadronScreenplay.TIER2_QUEST_STRING_1.type, RsfSquadronScreenplay.TIER2_QUEST_STRING_1.name)
	local questTwoComplete = SpaceHelpers:isSpaceQuestComplete(pPlayer, RsfSquadronScreenplay.TIER2_QUEST_STRING_2.type, RsfSquadronScreenplay.TIER2_QUEST_STRING_2.name)
	local questThreeComplete = SpaceHelpers:isSpaceQuestComplete(pPlayer, RsfSquadronScreenplay.TIER2_QUEST_STRING_3.type, RsfSquadronScreenplay.TIER2_QUEST_STRING_3.name)
	local questFourComplete = SpaceHelpers:isSpaceQuestComplete(pPlayer, RsfSquadronScreenplay.TIER2_QUEST_STRING_4.type, RsfSquadronScreenplay.TIER2_QUEST_STRING_4.name)

	local destroyDuty1Started = SpaceHelpers:isSpaceQuestActive(pPlayer, RsfSquadronScreenplay.TIER2_QUEST_STRING_DUTY_1.type, RsfSquadronScreenplay.TIER2_QUEST_STRING_DUTY_1.name)
	local escortDutyStarted = SpaceHelpers:isSpaceQuestActive(pPlayer, RsfSquadronScreenplay.TIER2_QUEST_STRING_DUTY_2.type, RsfSquadronScreenplay.TIER2_QUEST_STRING_DUTY_2.name)
	local destroyDuty2Started = SpaceHelpers:isSpaceQuestActive(pPlayer, RsfSquadronScreenplay.TIER2_QUEST_STRING_DUTY_3.type, RsfSquadronScreenplay.TIER2_QUEST_STRING_DUTY_3.name)
	local recoveryDutyStarted = SpaceHelpers:isSpaceQuestActive(pPlayer, RsfSquadronScreenplay.TIER2_QUEST_STRING_DUTY_4.type, RsfSquadronScreenplay.TIER2_QUEST_STRING_DUTY_4.name)

	local destroyDuty1Complete = SpaceHelpers:isSpaceQuestComplete(pPlayer, RsfSquadronScreenplay.TIER2_QUEST_STRING_DUTY_1.type, RsfSquadronScreenplay.TIER2_QUEST_STRING_DUTY_1.name)
	local escortDutyComplete = SpaceHelpers:isSpaceQuestComplete(pPlayer, RsfSquadronScreenplay.TIER2_QUEST_STRING_DUTY_2.type, RsfSquadronScreenplay.TIER2_QUEST_STRING_DUTY_2.name)
	local destroyDuty2Complete = SpaceHelpers:isSpaceQuestComplete(pPlayer, RsfSquadronScreenplay.TIER2_QUEST_STRING_DUTY_3.type, RsfSquadronScreenplay.TIER2_QUEST_STRING_DUTY_3.name)
	local recoveryDutyComplete = SpaceHelpers:isSpaceQuestComplete(pPlayer, RsfSquadronScreenplay.TIER2_QUEST_STRING_DUTY_4.type, RsfSquadronScreenplay.TIER2_QUEST_STRING_DUTY_4.name)

	local completedTier2 = SpaceHelpers:hasCompletedPilotTier(pPlayer, "neutral", 2)

	--[[
			Quests
	--]]

	-- Player has an active mission from Captain Kaydine
	if ((questOneStarted and not questOneComplete) or (questTwoStarted and not questTwoComplete) or (questThreeStarted and not questThreeComplete) or (questFourStarted and not questFourComplete) or
		(destroyDuty1Started and not destroyDuty1Complete) or (escortDutyStarted and not escortDutyComplete) or (destroyDuty2Started and not destroyDuty2Complete) or (recoveryDutyStarted and not recoveryDutyComplete)) then

		return convoTemplate:getScreen("on_mission")

	-- Check if players have all the tier2 skill boxes and finished the last mission, then send them to next trainer.
	elseif (questFourComplete and completedTier2) then
		-- Player has all the skill boxes, they should be tier 3. Increment if not proper
		if (ghost:getPilotTier() <= 2) then
			ghost:incrementPilotTier()
		end

		return convoTemplate:getScreen("completed_kaydine")
	-- Reward Checks
	elseif (questFourComplete and getQuestStatus(playerID .. RsfSquadronScreenplay.TIER2_QUEST_STRING_4.name .. ":reward") ~= "1") then
			return convoTemplate:getScreen("complete_fourth_mission")
	elseif (questThreeComplete and getQuestStatus(playerID .. RsfSquadronScreenplay.TIER2_QUEST_STRING_3.name .. ":reward") ~= "1") then
			return convoTemplate:getScreen("complete_third_mission")
	elseif (questTwoComplete and getQuestStatus(playerID .. RsfSquadronScreenplay.TIER2_QUEST_STRING_2.name .. ":reward") ~= "1") then
			return convoTemplate:getScreen("complete_second_mission")
	elseif (questOneComplete and getQuestStatus(playerID .. RsfSquadronScreenplay.TIER2_QUEST_STRING_1.name .. ":reward") ~= "1") then
			return convoTemplate:getScreen("complete_first_mission")
	-- Pilot is able to train
	elseif (not completedTier2 and SpaceHelpers:hasExperienceForTraining(pPlayer, 2)) then
		return convoTemplate:getScreen("ready_train_pilot")
	elseif (not questFourComplete) then
		-- Player is able to start fourth mission
		if (questThreeComplete and not questFourStarted) then
			if (getQuestStatus(playerID .. RsfSquadronScreenplay.TIER2_QUEST_STRING_4.name .. ":attempted") == "1") then
				return convoTemplate:getScreen("failed_fourth_mission")
			else
				return convoTemplate:getScreen("fourth_mission")
			end

		-- Player is able to start third mission
		elseif (questTwoComplete and not questThreeStarted) then
			if (getQuestStatus(playerID .. RsfSquadronScreenplay.TIER2_QUEST_STRING_3.name .. ":attempted") == "1") then
				return convoTemplate:getScreen("failed_third_mission")
			else
				return convoTemplate:getScreen("third_mission")
			end
		-- Player is able to start second mission
		elseif (questOneComplete and not questTwoStarted) then
			if (getQuestStatus(playerID .. RsfSquadronScreenplay.TIER2_QUEST_STRING_2.name .. ":attempted") == "1") then
				return convoTemplate:getScreen("failed_second_mission")
			else
				return convoTemplate:getScreen("second_mission")
			end
		-- Player is ready for first mission
		elseif (not questOneComplete and SpaceHelpers:hasPilotTierSkill(pPlayer, "neutral", 2)) then
			if (getQuestStatus(playerID .. RsfSquadronScreenplay.TIER2_QUEST_STRING_1.name .. ":attempted") == "1") then
				return convoTemplate:getScreen("failed_first_mission")
			else
				return convoTemplate:getScreen("first_mission")
			end
		end
	end

	return convoTemplate:getScreen("here_for_work")
end

function kaydineConvoHandler:runScreenHandlers(pConvTemplate, pPlayer, pNpc, selectedOption, pConvScreen)
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

	if (screenID == "ready_train_pilot") then
		local skillManager = LuaSkillManager()

		local responseString = "initial_"

		if (SpaceHelpers:isSpaceQuestComplete(pPlayer, RsfSquadronScreenplay.TIER2_QUEST_STRING_4.type, RsfSquadronScreenplay.TIER2_QUEST_STRING_4.name)) then
			responseString = "final_"
		elseif (SpaceHelpers:isSpaceQuestComplete(pPlayer, RsfSquadronScreenplay.TIER2_QUEST_STRING_3.type, RsfSquadronScreenplay.TIER2_QUEST_STRING_3.name)) then
			responseString = "mission4_"
		elseif (SpaceHelpers:isSpaceQuestComplete(pPlayer, RsfSquadronScreenplay.TIER2_QUEST_STRING_2.type, RsfSquadronScreenplay.TIER2_QUEST_STRING_2.name)) then
			responseString = "mission3_"
		elseif (SpaceHelpers:isSpaceQuestComplete(pPlayer, RsfSquadronScreenplay.TIER2_QUEST_STRING_1.type, RsfSquadronScreenplay.TIER2_QUEST_STRING_1.name)) then
			responseString = "mission2_"
		end

		if (not CreatureObject(pPlayer):hasSkill("pilot_neutral_starships_02") and skillManager:fulfillsSkillPrerequisitesAndXp(pPlayer, "pilot_neutral_starships_02")) then
			clonedConversation:addOption("@conversation/naboo_privateer_trainer_2:s_21", responseString .. "train_fighters") -- I am interested in advanced fighters.
		end
		if (not CreatureObject(pPlayer):hasSkill("pilot_neutral_weapons_02") and skillManager:fulfillsSkillPrerequisitesAndXp(pPlayer, "pilot_neutral_weapons_02")) then
			clonedConversation:addOption("@conversation/naboo_privateer_trainer_2:s_5", responseString .. "train_components") -- I am interested in intermediate starship component use.
		end
		if (not CreatureObject(pPlayer):hasSkill("pilot_neutral_procedures_02") and skillManager:fulfillsSkillPrerequisitesAndXp(pPlayer, "pilot_neutral_procedures_02")) then
			clonedConversation:addOption("@conversation/naboo_privateer_trainer_2:s_44", responseString .. "train_techniques") -- I am interested in starship defense training.
		end
		if (not CreatureObject(pPlayer):hasSkill("pilot_neutral_droid_02") and skillManager:fulfillsSkillPrerequisitesAndXp(pPlayer, "pilot_neutral_droid_02")) then
			clonedConversation:addOption("@conversation/naboo_privateer_trainer_2:s_76", responseString .. "train_algorithms") -- I am interested in reactor engineering algorithms.
		end

	-- Handle Skill box granting
	elseif (string.find(screenID, "_train_")) then
		local skillManager = LuaSkillManager()

		if (string.find(screenID, "train_fighters")) then
			if (skillManager:fulfillsSkillPrerequisitesAndXp(pPlayer, "pilot_neutral_starships_02")) then
				SpaceHelpers:grantSpaceSkill(pPlayer, "pilot_neutral_starships_02", true)
			end
		elseif (string.find(screenID, "train_components")) then
			if (skillManager:fulfillsSkillPrerequisitesAndXp(pPlayer, "pilot_neutral_weapons_02")) then
				SpaceHelpers:grantSpaceSkill(pPlayer, "pilot_neutral_weapons_02", true)
			end
		elseif (string.find(screenID, "train_techniques")) then
			if (skillManager:fulfillsSkillPrerequisitesAndXp(pPlayer, "pilot_neutral_procedures_02")) then
				SpaceHelpers:grantSpaceSkill(pPlayer, "pilot_neutral_procedures_02", true)
			end
		elseif (string.find(screenID, "train_algorithms")) then
			if (skillManager:fulfillsSkillPrerequisitesAndXp(pPlayer, "pilot_neutral_droid_02")) then
				SpaceHelpers:grantSpaceSkill(pPlayer, "pilot_neutral_droid_02", true)
			end
		end

		if (ghost:getPilotTier() <= 2 and SpaceHelpers:hasCompletedPilotTier(pPlayer, "neutral", 2)) then
			ghost:incrementPilotTier()
		end

		return pClonedScreen

	-- Duty Missions
	elseif (screenID == "accept_duty_destroy1") then
		destroy_duty_naboo_privateer_9:startQuest(pPlayer, pNpc)
	elseif (screenID == "accept_duty_escort") then
		escort_duty_naboo_privateer_10:startQuest(pPlayer, pNpc)
	elseif (screenID == "accept_duty_destroy2") then
		destroy_duty_naboo_privateer_11:startQuest(pPlayer, pNpc)
	elseif (screenID == "accept_duty_recovery") then
		CreatureObject(pPlayer):sendSystemMessage("Recovery Duty Missions are not implemented yet!")

	-- Mission Rewards
	elseif (screenID == "fourth_mission_success") then
		setQuestStatus(playerID .. RsfSquadronScreenplay.TIER2_QUEST_STRING_4.name .. ":reward", 1)
		assassinate_naboo_privateer_tier2_4a:rewardPlayer(pPlayer)
	elseif (screenID == "turnover_intelligence") then
		setQuestStatus(playerID .. RsfSquadronScreenplay.TIER2_QUEST_STRING_3.name .. ":reward", 1)
		inspect_naboo_privateer_15:rewardPlayer(pPlayer)
	elseif (screenID == "duty_calls" or screenID == "here_is_pay") then
		setQuestStatus(playerID .. RsfSquadronScreenplay.TIER2_QUEST_STRING_2.name .. ":reward", 1)
		escort_naboo_privateer_14:rewardPlayer(pPlayer)
	elseif (screenID == "according_to_plan" or screenID == "first_mission_success") then
		setQuestStatus(playerID .. RsfSquadronScreenplay.TIER2_QUEST_STRING_1.name .. ":reward", 1)
		destroy_naboo_privateer_13a:rewardPlayer(pPlayer)

	-- Give Missions
	elseif (screenID == "accept_assassinate" or screenID == "nonsense" or screenID == "let_me_know" or screenID == "report_back_success" or screenID == "key_to_success" or screenID == "just_malfunctioned") then
		setQuestStatus(playerID .. RsfSquadronScreenplay.TIER2_QUEST_STRING_4.name .. ":attempted", 1)
		assassinate_naboo_privateer_tier2_4a:startQuest(pPlayer, pNpc)
	elseif (screenID == "accept_inspect" or screenID == "on_your_way" or screenID == "take_it_serious" or screenID == "bad_liar") then
		setQuestStatus(playerID .. RsfSquadronScreenplay.TIER2_QUEST_STRING_3.name .. ":attempted", 1)
		inspect_naboo_privateer_15:startQuest(pPlayer, pNpc)
	elseif (screenID == "accept_escort" or screenID == "back_to_escort" or screenID == "now_is_good" or screenID == "be_smarter") then
		setQuestStatus(playerID .. RsfSquadronScreenplay.TIER2_QUEST_STRING_2.name .. ":attempted", 1)
		escort_naboo_privateer_14:startQuest(pPlayer, pNpc)
	elseif ((screenID == "start_first_mission") or (screenID == "try_first_mission") or (screenID == "cant_wait_first")) then
		setQuestStatus(playerID .. RsfSquadronScreenplay.TIER2_QUEST_STRING_1.name .. ":attempted", 1)
		destroy_naboo_privateer_13a:startQuest(pPlayer, pNpc)
	end

	return pClonedScreen
end
