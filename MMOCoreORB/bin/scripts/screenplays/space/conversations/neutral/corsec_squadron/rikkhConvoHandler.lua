local QuestManager = require("managers.quest.quest_manager")

rikkhConvoHandler = conv_handler:new {}

function rikkhConvoHandler:getInitialScreen(pPlayer, pNpc, pConvTemplate)
	if (pPlayer == nil or pNpc == nil or pConvTemplate == nil) then
		return nil
	end

	local convoTemplate = LuaConversationTemplate(pConvTemplate)

	local faction = CreatureObject(pPlayer):getFaction()
	local playerID = CreatureObject(pPlayer):getObjectID()

	-- JTL is disabled
	if (not isJtlEnabled()) then
		return convoTemplate:getScreen("no_jtl") -- Sorry, but you don't look like a pilot to me.
	end

	print("rikkhConvoHandler:getInitialScreen  -- called")

	-- Check if player has any pilot skills
	if (not SpaceHelpers:isNeutralPilot(pPlayer)) then
		return convoTemplate:getScreen("not_pilot") -- Everything is fine here. Nothing wrong at all.
	end

	-- We know the player is a neutral pilot, check if pilot is a different squadron
	if (not SpaceHelpers:isCorsecSquadron(pPlayer)) then
		return convoTemplate:getScreen("pilot_not_corsec") -- "Well, if it isn't %TU. I've heard your name around the pilot's lounge a few times. What can I do for you?"
	end

	local pGhost = CreatureObject(pPlayer):getPlayerObject()

	if (pGhost == nil) then
		return convoTemplate:getScreen("no_jtl")
	end

	local ghost = LuaPlayerObject(pGhost)

	if (ghost == nil) then
		return convoTemplate:getScreen("no_jtl")
	end

	-- Corsec neutral pilot has completed Tier2 or greater
	if (ghost:getPilotTier() > 2) then
		return convoTemplate:getScreen("finished_tier")
	end

	local questOneStarted = SpaceHelpers:isSpaceQuestActive(pPlayer, CorsecSquadronScreenplay.TIER2_QUEST_STRING_1.type, CorsecSquadronScreenplay.TIER2_QUEST_STRING_1.name)
	local questTwoStarted = SpaceHelpers:isSpaceQuestActive(pPlayer, CorsecSquadronScreenplay.TIER2_QUEST_STRING_2.type, CorsecSquadronScreenplay.TIER2_QUEST_STRING_2.name)
	local questThreeStarted = SpaceHelpers:isSpaceQuestActive(pPlayer, CorsecSquadronScreenplay.TIER2_QUEST_STRING_3.type, CorsecSquadronScreenplay.TIER2_QUEST_STRING_3.name)
	local questFourStarted = SpaceHelpers:isSpaceQuestActive(pPlayer, CorsecSquadronScreenplay.TIER2_QUEST_STRING_4.type, CorsecSquadronScreenplay.TIER2_QUEST_STRING_4.name)

	local questOneComplete = SpaceHelpers:isSpaceQuestComplete(pPlayer, CorsecSquadronScreenplay.TIER2_QUEST_STRING_1.type, CorsecSquadronScreenplay.TIER2_QUEST_STRING_1.name)
	local questTwoComplete = SpaceHelpers:isSpaceQuestComplete(pPlayer, CorsecSquadronScreenplay.TIER2_QUEST_STRING_2.type, CorsecSquadronScreenplay.TIER2_QUEST_STRING_2.name)
	local questThreeComplete = SpaceHelpers:isSpaceQuestComplete(pPlayer, CorsecSquadronScreenplay.TIER2_QUEST_STRING_3.type, CorsecSquadronScreenplay.TIER2_QUEST_STRING_3.name)
	local questFourComplete = SpaceHelpers:isSpaceQuestComplete(pPlayer, CorsecSquadronScreenplay.TIER2_QUEST_STRING_4.type, CorsecSquadronScreenplay.TIER2_QUEST_STRING_4.name)

	--local destroyDutyStarted = SpaceHelpers:isSpaceQuestActive(pPlayer, CorsecSquadronScreenplay.TIER2_QUEST_STRING_DUTY_4_1.type, CorsecSquadronScreenplay.TIER2_QUEST_STRING_DUTY_4_1.name)
	--local escortDutyStarted = SpaceHelpers:isSpaceQuestActive(pPlayer, CorsecSquadronScreenplay.TIER2_QUEST_STRING_DUTY_4_2.type, CorsecSquadronScreenplay.TIER2_QUEST_STRING_DUTY_4_2.name)

	--local destroyDutyComplete = SpaceHelpers:isSpaceQuestComplete(pPlayer, CorsecSquadronScreenplay.TIER2_QUEST_STRING_DUTY_4_1.type, CorsecSquadronScreenplay.TIER2_QUEST_STRING_DUTY_4_1.name)
	--local escortDutyComplete = SpaceHelpers:isSpaceQuestComplete(pPlayer, CorsecSquadronScreenplay.TIER2_QUEST_STRING_DUTY_4_2.type, CorsecSquadronScreenplay.TIER2_QUEST_STRING_DUTY_4_2.name)

	local hasFirstSkill = CreatureObject(pPlayer):hasSkill("pilot_neutral_starships_02")


	--[[
			Quests
	--]]

	-- Player has an active mission from Cpt Rikkh
	if ((questOneStarted and not questOneComplete) or (questTwoStarted and not questTwoComplete) or (questThreeStarted and not questThreeComplete) or (questFourStarted and not questFourComplete) or (destroyDutyStarted and not destroyDutyComplete) or (escortDutyStarted and not escortDutyComplete)) then
		return convoTemplate:getScreen("on_mission")

	-- Check if players have all the tier2 skill boxes, send them to next trainer.
	elseif (SpaceHelpers:hasCompletedPilotTier(pPlayer, "neutral", 2)) then
		return convoTemplate:getScreen("completed_rikkh")

	-- Check if player is ready players first Tier2 box training. Players cannot run any missions until they have 1 of the Tier2 boxes
	elseif (not SpaceHelpers:hasPilotTierSkill(pPlayer, "neutral", 2) and SpaceHelpers:hasExperienceForTraining(pPlayer, 2)) then
		return convoTemplate:getScreen("initial_training")






	--[[

	-- Check if players have all the tier1 skill boxes, send them to next trainer.
	elseif (SpaceHelpers:hasCompletedPilotTier(pPlayer, "neutral", 1)) then
		return convoTemplate:getScreen("completed_rhea")
	-- Player is a CorSec pilot and has at least one of the Tier1 skill boxes
	elseif (SpaceHelpers:hasPilotTierSkill(pPlayer, "neutral", 1)) then
		-- Check if the player can be trained in the remaining Tier1 Skills
		if (SpaceHelpers:hasExperienceForTraining(pPlayer, 1)) then
			return convoTemplate:getScreen("more_training")
		-- Offer Duty missions
		else
			CreatureObject(pPlayer):doAnimation("salute1")

			return convoTemplate:getScreen("duty_missions")
		end
	-- Player has finished 4 and has received the reward, but needs to accept training of first pilot skill
	elseif (questFourComplete and getQuestStatus(playerID .. CorsecSquadronScreenplay.TIER2_QUEST_STRING_4.name .. ":reward") == "1") then
		return convoTemplate:getScreen("missions_complete")
	-- Player has completed quest 4 and needs reward
	elseif (questFourComplete and getQuestStatus(playerID .. CorsecSquadronScreenplay.TIER2_QUEST_STRING_4.name .. ":reward") ~= "1") then
		-- Give player the reward and update that they received it
		setQuestStatus(playerID .. CorsecSquadronScreenplay.TIER2_QUEST_STRING_4.name .. ":reward", 1)

		-- Grant Reward
		assassinate_corellia_privateer_tier1_4a:rewardPlayer(pPlayer)

		return convoTemplate:getScreen("missions_complete")
	-- Player has finished 3, has received the reward and needs to start quest 4
	elseif (questThreeComplete and not questFourStarted and getQuestStatus(playerID .. CorsecSquadronScreenplay.TIER2_QUEST_STRING_3.name .. ":reward") == "1") then
		return convoTemplate:getScreen("excellent_work3")
	-- Player has completed quest 3 and needs reward
	elseif (questThreeComplete and getQuestStatus(playerID .. CorsecSquadronScreenplay.TIER2_QUEST_STRING_3.name .. ":reward") ~= "1") then
		-- Give player the reward and update that they received it
		setQuestStatus(playerID .. CorsecSquadronScreenplay.TIER2_QUEST_STRING_3.name .. ":reward", 1)

		-- Grant Reward
		patrol_corellia_privateer_3:rewardPlayer(pPlayer)

		return convoTemplate:getScreen("excellent_work3")
	-- Player has finished 2, has received the reward and needs to start quest 3
	elseif (questTwoComplete and not questThreeStarted and getQuestStatus(playerID .. CorsecSquadronScreenplay.TIER2_QUEST_STRING_2.name .. ":reward") == "1") then
		return convoTemplate:getScreen("excellent_work2")
	-- Player has completed quest 2 and needs reward
	elseif (questTwoComplete and getQuestStatus(playerID .. CorsecSquadronScreenplay.TIER2_QUEST_STRING_2.name .. ":reward") ~= "1") then
		-- Give player the reward and update that they received it
		setQuestStatus(playerID .. CorsecSquadronScreenplay.TIER2_QUEST_STRING_2.name .. ":reward", 1)

		-- Grant Reward
		destroy_corellia_privateer_2:rewardPlayer(pPlayer)

		return convoTemplate:getScreen("excellent_work2")

	]]




	-- Player has finished quest 1, has received the reward and needs to start quest 2
	elseif (questOneComplete and not questTwoStarted and getQuestStatus(playerID .. CorsecSquadronScreenplay.TIER2_QUEST_STRING_1.name .. ":reward") == "1") then

		return convoTemplate:getScreen("")
	-- Player has finished mission 1 and needs reward
	elseif (questOneComplete and getQuestStatus(playerID .. CorsecSquadronScreenplay.TIER2_QUEST_STRING_1.name .. ":reward") ~= 1) then
		-- Give player the reward and update that they received it
		setQuestStatus(playerID .. CorsecSquadronScreenplay.TIER2_QUEST_STRING_1.name .. ":reward", 1)

		-- Grant Reward
		destroy_corellia_privateer_13a:rewardPlayer(pPlayer)

		return convoTemplate:getScreen("")

	-- Player has first mission
	elseif (questOneStarted and not questOneComplete) then
		return convoTemplate:getScreen("failed_first_mission")
	end

	-- Player needs to train first box prior to starting first mission
	return convoTemplate:getScreen("here_for_work")
end

function rikkhConvoHandler:runScreenHandlers(pConvTemplate, pPlayer, pNpc, selectedOption, pConvScreen)
	if (pPlayer == nil or pConvScreen == nil) then
		return
	end

	local screen = LuaConversationScreen(pConvScreen)
	local screenID = screen:getScreenID()

	local pClonedScreen = screen:cloneScreen()
	local clonedConversation = LuaConversationScreen(pClonedScreen)

	-- Set player as conversation target
	clonedConversation:setDialogTextTU(CreatureObject(pPlayer):getFirstName())

	print("rikkhConvoHandler:runScreenHandlers -- Screen ID: " .. screenID)

	local pGhost = CreatureObject(pPlayer):getPlayerObject()

	if (pGhost == nil) then
		return pClonedScreen
	end

	local ghost = LuaPlayerObject(pGhost)

	if (ghost == nil) then
		return pClonedScreen
	end

	if (screenID == "done_goofing") then
		CreatureObject(pPlayer):doAnimation("laugh")
	elseif (screenID == "initial_training") then
		if (not CreatureObject(pPlayer):hasSkill("pilot_neutral_weapons_02") and skillManager:fulfillsSkillPrerequisitesAndXp(pPlayer, "pilot_neutral_weapons_02")) then
			clonedConversation:addOption("@conversation/corellia_privateer_trainer:s_bf7ea071", "train_player_fighters") -- I want to learn about advanced fighters.
		end
		if (not CreatureObject(pPlayer):hasSkill("pilot_neutral_starships_02") and skillManager:fulfillsSkillPrerequisitesAndXp(pPlayer, "pilot_neutral_starships_02")) then
			clonedConversation:addOption("@conversation/corellia_privateer_trainer:s_737b617c", "train_player_component") -- I want to learn about intermediate starship components.
		end
		if (not CreatureObject(pPlayer):hasSkill("pilot_neutral_procedures_02") and skillManager:fulfillsSkillPrerequisitesAndXp(pPlayer, "pilot_neutral_procedures_02")) then
			clonedConversation:addOption("@conversation/corellia_privateer_trainer:s_c6673868", "train_player_techniques") -- I want to learn about starship defense techniques.
		end
		if (not CreatureObject(pPlayer):hasSkill("pilot_neutral_droid_02") and skillManager:fulfillsSkillPrerequisitesAndXp(pPlayer, "pilot_neutral_droid_02")) then
			clonedConversation:addOption("@conversation/corellia_privateer_trainer:s_aa58928c", "train_player_algorithms") -- I want to learn about reactor engineering algorithms.
		end

	-- Handle Skill box granting
	elseif (string.find(screenID, "train_player_")) then
		local skillManager = LuaSkillManager()

		local deductExperience = (string.find(screenID, "_free") == nil)

		screenID = string.gsub(screenID, "_free", "")

		if (screenID == "train_player_fighters") then
			if (not deductExperience or skillManager:fulfillsSkillPrerequisitesAndXp(pPlayer, "pilot_neutral_starships_02")) then
				-- Train player Skill Box
				SpaceHelpers:grantSpaceSkill(pPlayer, "pilot_neutral_starships_02", deductExperience)
			end
		elseif (screenID == "train_player_component") then
			if (not deductExperience or skillManager:fulfillsSkillPrerequisitesAndXp(pPlayer, "pilot_neutral_weapons_02")) then
				-- Train player Skill Box
				SpaceHelpers:grantSpaceSkill(pPlayer, "pilot_neutral_weapons_02", deductExperience)
			end
		elseif (screenID == "train_player_techniques") then
			if (not deductExperience or skillManager:fulfillsSkillPrerequisitesAndXp(pPlayer, "pilot_neutral_procedures_02")) then
				-- Train player Skill Box
				SpaceHelpers:grantSpaceSkill(pPlayer, "pilot_neutral_procedures_02", deductExperience)
			end
		elseif (screenID == "train_player_droid") then
			if (not deductExperience or skillManager:fulfillsSkillPrerequisitesAndXp(pPlayer, "pilot_neutral_droid_02")) then
				-- Train player Skill Box
				SpaceHelpers:grantSpaceSkill(pPlayer, "pilot_neutral_droid_02", deductExperience)
			end
		end

		-- If player has all of the Tier 2 skills, increment their pilot tier
		if (SpaceHelpers:hasCompletedPilotTier(pPlayer, "neutral", 2) and ghost:getPilotTier() == 2) then
			-- Increment pilot to Tier 2!
			ghost:incrementPilotTier()
		end

		return pClonedScreen

	-- Missions

	elseif (screenID == "accept_destroy1") then
		destroy_duty_corellia_privateer_9:startQuest(pPlayer, pNpc)
	elseif (screenID == "accept_escort") then
		escort_duty_corellia_privateer_10:startQuest(pPlayer, pNpc)
	elseif (screenID == "accept_destroy2") then
		destroy_duty_corellia_privateer_11:startQuest(pPlayer, pNpc)
	elseif (screenID == "accept_recovery") then
		recovery_duty_corellia_privateer_12:startQuest(pPlayer, pNpc)







	elseif ((screenID == "try_first_mission") or (screenID == "cant_wait_first")) then
		--	Give First mission to player
		destroy_corellia_privateer_13a:startQuest(pPlayer, pNpc)
	end




	return pClonedScreen
end
