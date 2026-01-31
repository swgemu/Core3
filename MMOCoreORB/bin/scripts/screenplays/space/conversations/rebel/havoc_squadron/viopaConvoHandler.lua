local SpaceHelpers = require("utils.space_helpers")

viopaConvoHandler = conv_handler:new {}

function viopaConvoHandler:getInitialScreen(pPlayer, pNpc, pConvTemplate)
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

	-- Testing Reset
	--HavocSquadronScreenplay:resetViopaQuests(pPlayer)

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

	-- Check if player has completed Tier 1
	if (not SpaceHelpers:hasCompletedPilotTier(pPlayer, "rebel_navy", 1)) then
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

	-- Player has negative faction standing with the Rebel Alliance
	if (PlayerObject(pGhost):getFactionStanding("rebel") < 0) then
		return convoTemplate:getScreen("negative_faction")
	end

	local questOneStarted = SpaceHelpers:isSpaceQuestActive(pPlayer, HavocSquadronScreenplay.TIER2_QUEST_STRING_1.type, HavocSquadronScreenplay.TIER2_QUEST_STRING_1.name)
	local questTwoStarted = SpaceHelpers:isSpaceQuestActive(pPlayer, HavocSquadronScreenplay.TIER2_QUEST_STRING_2.type, HavocSquadronScreenplay.TIER2_QUEST_STRING_2.name)
	local questThreeStarted = SpaceHelpers:isSpaceQuestActive(pPlayer, HavocSquadronScreenplay.TIER2_QUEST_STRING_3.type, HavocSquadronScreenplay.TIER2_QUEST_STRING_3.name)
	local questFourStarted = SpaceHelpers:isSpaceQuestActive(pPlayer, HavocSquadronScreenplay.TIER2_QUEST_STRING_4.type, HavocSquadronScreenplay.TIER2_QUEST_STRING_4.name)

	local questOneComplete = SpaceHelpers:isSpaceQuestComplete(pPlayer, HavocSquadronScreenplay.TIER2_QUEST_STRING_1.type, HavocSquadronScreenplay.TIER2_QUEST_STRING_1.name)
	local questTwoComplete = SpaceHelpers:isSpaceQuestComplete(pPlayer, HavocSquadronScreenplay.TIER2_QUEST_STRING_2.type, HavocSquadronScreenplay.TIER2_QUEST_STRING_2.name)
	local questThreeComplete = SpaceHelpers:isSpaceQuestComplete(pPlayer, HavocSquadronScreenplay.TIER2_QUEST_STRING_3.type, HavocSquadronScreenplay.TIER2_QUEST_STRING_3.name)
	local questFourComplete = SpaceHelpers:isSpaceQuestComplete(pPlayer, HavocSquadronScreenplay.TIER2_QUEST_STRING_4.type, HavocSquadronScreenplay.TIER2_QUEST_STRING_4.name)

	local destroyDutyStarted = SpaceHelpers:isSpaceQuestActive(pPlayer, HavocSquadronScreenplay.TIER2_QUEST_STRING_DUTY_1.type, HavocSquadronScreenplay.TIER2_QUEST_STRING_DUTY_1.name)
	local recoveryDutyStarted = SpaceHelpers:isSpaceQuestActive(pPlayer, HavocSquadronScreenplay.TIER2_QUEST_STRING_DUTY_2.type, HavocSquadronScreenplay.TIER2_QUEST_STRING_DUTY_2.name)
	local escortDutyStarted = SpaceHelpers:isSpaceQuestActive(pPlayer, HavocSquadronScreenplay.TIER2_QUEST_STRING_DUTY_3.type, HavocSquadronScreenplay.TIER2_QUEST_STRING_DUTY_3.name)

	-- Player has an active quest from Viopa
	if ((questOneStarted and not questOneComplete) or (questTwoStarted and not questTwoComplete) or (questThreeStarted and not questThreeComplete) or (questFourStarted and not questFourComplete) or destroyDutyStarted or recoveryDutyStarted or escortDutyStarted) then
		return convoTemplate:getScreen("has_mission")
	-- Check if players have all the tier2 skill boxes, send them to next trainer
	elseif (SpaceHelpers:hasCompletedPilotTier(pPlayer, "rebel_navy", 2)) then
		return convoTemplate:getScreen("completed_viopa")
	-- Check if the player can be trained in the remaining Tier2 Skills
	elseif (SpaceHelpers:hasExperienceForTraining(pPlayer, 2)) then
		return convoTemplate:getScreen("more_training")
	-- Player has at least one Tier2 skill box
	elseif (SpaceHelpers:hasPilotTierSkill(pPlayer, "rebel_navy", 2) and not questOneComplete) then
		-- Ready for first story mission: has tier 2 skill, introduced, quest 1 not yet attempted
		if (getQuestStatus(playerID .. HavocSquadronScreenplay.TIER2_QUEST_STRING_1.name .. ":introduced") == "1" and getQuestStatus(playerID .. HavocSquadronScreenplay.TIER2_QUEST_STRING_1.name .. ":attempted") ~= "1") then
			return convoTemplate:getScreen("start_mission1")
		-- Offer Duty missions
		else
			return convoTemplate:getScreen("duty_missions")
		end
	-- Player has completed quest 4
	elseif (questFourComplete) then
		if (getQuestStatus(playerID .. HavocSquadronScreenplay.TIER2_QUEST_STRING_4.name .. ":reward") ~= "1") then
			setQuestStatus(playerID .. HavocSquadronScreenplay.TIER2_QUEST_STRING_4.name .. ":reward", 1)

			-- Grant Reward
			assassinate_viopa_rebel_4:rewardPlayer(pPlayer)

			-- Grant Faction Standing
			PlayerObject(pGhost):increaseFactionStanding("rebel", 75)
		end

		return convoTemplate:getScreen("missions_complete")
	-- Player has attempted quest 4 but failed/aborted
	elseif (getQuestStatus(playerID .. HavocSquadronScreenplay.TIER2_QUEST_STRING_4.name .. ":attempted") == "1" and not questFourComplete) then
		return convoTemplate:getScreen("failed_mission4")
	-- Player has finished quest 3, received the reward, needs to start quest 4
	elseif (questThreeComplete and getQuestStatus(playerID .. HavocSquadronScreenplay.TIER2_QUEST_STRING_3.name .. ":reward") == "1") then
		return convoTemplate:getScreen("mission4_brief")
	-- Player has completed quest 3 and needs reward
	elseif (questThreeComplete and getQuestStatus(playerID .. HavocSquadronScreenplay.TIER2_QUEST_STRING_3.name .. ":reward") ~= "1") then
		setQuestStatus(playerID .. HavocSquadronScreenplay.TIER2_QUEST_STRING_3.name .. ":reward", 1)

		-- Grant Reward
		recovery_viopa_rebel_3:rewardPlayer(pPlayer)

		-- Grant Faction Standing
		PlayerObject(pGhost):increaseFactionStanding("rebel", 75)

		return convoTemplate:getScreen("excellent_work3")
	-- Player has attempted quest 3 but failed/aborted
	elseif (getQuestStatus(playerID .. HavocSquadronScreenplay.TIER2_QUEST_STRING_3.name .. ":attempted") == "1" and not questThreeComplete) then
		return convoTemplate:getScreen("failed_mission3")
	-- Player has finished quest 2, received the reward, needs to start quest 3
	elseif (questTwoComplete and getQuestStatus(playerID .. HavocSquadronScreenplay.TIER2_QUEST_STRING_2.name .. ":reward") == "1") then
		return convoTemplate:getScreen("mission3_brief")
	-- Player has completed quest 2 and needs reward
	elseif (questTwoComplete and getQuestStatus(playerID .. HavocSquadronScreenplay.TIER2_QUEST_STRING_2.name .. ":reward") ~= "1") then
		setQuestStatus(playerID .. HavocSquadronScreenplay.TIER2_QUEST_STRING_2.name .. ":reward", 1)

		-- Grant Reward
		escort_viopa_rebel_2:rewardPlayer(pPlayer)

		-- Grant Faction Standing
		PlayerObject(pGhost):increaseFactionStanding("rebel", 75)

		return convoTemplate:getScreen("excellent_work2")
	-- Player has attempted quest 2 but failed/aborted
	elseif (getQuestStatus(playerID .. HavocSquadronScreenplay.TIER2_QUEST_STRING_2.name .. ":attempted") == "1" and not questTwoComplete) then
		return convoTemplate:getScreen("failed_mission2")
	-- Player has finished quest 1, received the reward, needs to start quest 2
	elseif (questOneComplete and getQuestStatus(playerID .. HavocSquadronScreenplay.TIER2_QUEST_STRING_1.name .. ":reward") == "1") then
		return convoTemplate:getScreen("mission2_brief")
	-- Player has completed quest 1 and needs reward
	elseif (questOneComplete and getQuestStatus(playerID .. HavocSquadronScreenplay.TIER2_QUEST_STRING_1.name .. ":reward") ~= "1") then
		setQuestStatus(playerID .. HavocSquadronScreenplay.TIER2_QUEST_STRING_1.name .. ":reward", 1)

		-- Grant Reward
		inspect_viopa_rebel_1:rewardPlayer(pPlayer)

		-- Grant Faction Standing
		PlayerObject(pGhost):increaseFactionStanding("rebel", 75)

		return convoTemplate:getScreen("excellent_work")
	-- Player has attempted quest 1 but failed/aborted
	elseif (getQuestStatus(playerID .. HavocSquadronScreenplay.TIER2_QUEST_STRING_1.name .. ":attempted") == "1" and not questOneComplete) then
		return convoTemplate:getScreen("failed_mission1")
	-- Player has been introduced but hasn't started quest 1 yet - show duty missions
	elseif (getQuestStatus(playerID .. HavocSquadronScreenplay.TIER2_QUEST_STRING_1.name .. ":introduced") == "1") then
		return convoTemplate:getScreen("duty_missions")
	-- New pilot to Viopa
	else
		return convoTemplate:getScreen("introduction")
	end

	return convoTemplate:getScreen("no_jtl")
end

function viopaConvoHandler:runScreenHandlers(pConvTemplate, pPlayer, pNpc, selectedOption, pConvScreen)
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

	-- Handle additional training (dynamic skill options)
	if (screenID == "training_menu") then
		local skillManager = LuaSkillManager()

		if (not CreatureObject(pPlayer):hasSkill("pilot_rebel_navy_starships_02") and skillManager:fulfillsSkillPrerequisitesAndXp(pPlayer, "pilot_rebel_navy_starships_02")) then
			clonedConversation:addOption("@conversation/lok_rebel_trainer_2:s_c6c91897", "train_player_fighters") -- Multi-Role Craft
		end

		if (not CreatureObject(pPlayer):hasSkill("pilot_rebel_navy_weapons_02") and skillManager:fulfillsSkillPrerequisitesAndXp(pPlayer, "pilot_rebel_navy_weapons_02")) then
			clonedConversation:addOption("@conversation/lok_rebel_trainer_2:s_98d991e7", "train_player_component") -- Weapons B, Intermediate Alliance Starship Ordnance
		end

		if (not CreatureObject(pPlayer):hasSkill("pilot_rebel_navy_procedures_02") and skillManager:fulfillsSkillPrerequisitesAndXp(pPlayer, "pilot_rebel_navy_procedures_02")) then
			clonedConversation:addOption("@conversation/lok_rebel_trainer_2:s_73ccefde", "train_player_basics") -- Space Combat Techniques
		end

		if (not CreatureObject(pPlayer):hasSkill("pilot_rebel_navy_droid_02") and skillManager:fulfillsSkillPrerequisitesAndXp(pPlayer, "pilot_rebel_navy_droid_02")) then
			clonedConversation:addOption("@conversation/lok_rebel_trainer_2:s_3c4ff185", "train_player_droid") -- Reactor Engineering Algorithms
		end
	-- Handle duty menu (dynamic duty options)
	elseif (screenID == "duty_menu") then
		clonedConversation:addOption("@conversation/lok_rebel_trainer_2:s_1dfeca09", "destroy_duty")   -- I've been itching to take down some TIE fighters.
		clonedConversation:addOption("@conversation/lok_rebel_trainer_2:s_e02126d9", "recovery_duty")  -- Stealing some Corsair ships sounds like fun.
		clonedConversation:addOption("@conversation/lok_rebel_trainer_2:s_cd3e2b38", "escort_duty")    -- I'll help some of our smugglers sneak by the Empire.
	-- Handle Skill box granting
	elseif (string.find(screenID, "train_player_")) then
		local skillManager = LuaSkillManager()

		if (screenID == "train_player_droid") then
			if (skillManager:fulfillsSkillPrerequisitesAndXp(pPlayer, "pilot_rebel_navy_droid_02")) then
				SpaceHelpers:grantSpaceSkill(pPlayer, "pilot_rebel_navy_droid_02", true)
			end
		elseif (screenID == "train_player_basics") then
			if (skillManager:fulfillsSkillPrerequisitesAndXp(pPlayer, "pilot_rebel_navy_procedures_02")) then
				SpaceHelpers:grantSpaceSkill(pPlayer, "pilot_rebel_navy_procedures_02", true)
			end
		elseif (screenID == "train_player_fighters") then
			if (skillManager:fulfillsSkillPrerequisitesAndXp(pPlayer, "pilot_rebel_navy_starships_02")) then
				SpaceHelpers:grantSpaceSkill(pPlayer, "pilot_rebel_navy_starships_02", true)
			end
		elseif (screenID == "train_player_component") then
			if (skillManager:fulfillsSkillPrerequisitesAndXp(pPlayer, "pilot_rebel_navy_weapons_02")) then
				SpaceHelpers:grantSpaceSkill(pPlayer, "pilot_rebel_navy_weapons_02", true)
			end
		end

		if (SpaceHelpers:hasCompletedPilotTier(pPlayer, "rebel_navy", 2) and ghost:getPilotTier() == 2) then
			ghost:incrementPilotTier()
		end

		return pClonedScreen
	elseif (screenID == "destroy_duty") then
		destroy_duty_viopa_rebel_6:startQuest(pPlayer, pNpc)
	elseif (screenID == "recovery_duty") then
		recovery_duty_viopa_rebel_7:startQuest(pPlayer, pNpc)
	elseif (screenID == "escort_duty") then
		escort_duty_viopa_rebel_5:startQuest(pPlayer, pNpc)
	elseif (screenID == "accept_intro") then
		-- First time accepting from introduction flow - mark as introduced, show duty briefing
		setQuestStatus(playerID .. HavocSquadronScreenplay.TIER2_QUEST_STRING_1.name .. ":introduced", 1)
	elseif (screenID == "intro_destroy_duty") then
		destroy_duty_viopa_rebel_6:startQuest(pPlayer, pNpc)
	elseif (screenID == "intro_recovery_duty") then
		recovery_duty_viopa_rebel_7:startQuest(pPlayer, pNpc)
	elseif (screenID == "intro_escort_duty") then
		escort_duty_viopa_rebel_5:startQuest(pPlayer, pNpc)
	elseif (screenID == "intro_duty_goodbye") then
		CreatureObject(pNpc):doAnimation("goodbye")
	elseif (screenID == "accept_mission1") then
		setQuestStatus(playerID .. HavocSquadronScreenplay.TIER2_QUEST_STRING_1.name .. ":attempted", 1)

		inspect_viopa_rebel_1:startQuest(pPlayer, pNpc)
	elseif (screenID == "start_mission2") then
		setQuestStatus(playerID .. HavocSquadronScreenplay.TIER2_QUEST_STRING_2.name .. ":attempted", 1)

		escort_viopa_rebel_2:startQuest(pPlayer, pNpc)
	elseif (screenID == "start_mission3") then
		setQuestStatus(playerID .. HavocSquadronScreenplay.TIER2_QUEST_STRING_3.name .. ":attempted", 1)

		recovery_viopa_rebel_3:startQuest(pPlayer, pNpc)
	elseif (screenID == "start_mission4") then
		setQuestStatus(playerID .. HavocSquadronScreenplay.TIER2_QUEST_STRING_4.name .. ":attempted", 1)

		assassinate_viopa_rebel_4:startQuest(pPlayer, pNpc)
	elseif (screenID == "retry_mission2") then
		escort_viopa_rebel_2:startQuest(pPlayer, pNpc)
	elseif (screenID == "retry_mission3") then
		recovery_viopa_rebel_3:startQuest(pPlayer, pNpc)
	elseif (screenID == "retry_mission4") then
		assassinate_viopa_rebel_4:startQuest(pPlayer, pNpc)
	elseif (screenID == "goodbye") then
		CreatureObject(pNpc):doAnimation("goodbye")
	end

	return pClonedScreen
end
