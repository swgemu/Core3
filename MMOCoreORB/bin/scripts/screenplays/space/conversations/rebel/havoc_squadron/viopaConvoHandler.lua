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
	if (ghost:getFactionStanding("rebel") < 0) then
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

	local destroyDutyComplete = SpaceHelpers:isSpaceQuestComplete(pPlayer, HavocSquadronScreenplay.TIER2_QUEST_STRING_DUTY_1.type, HavocSquadronScreenplay.TIER2_QUEST_STRING_DUTY_1.name)
	local recoveryDutyComplete = SpaceHelpers:isSpaceQuestComplete(pPlayer, HavocSquadronScreenplay.TIER2_QUEST_STRING_DUTY_2.type, HavocSquadronScreenplay.TIER2_QUEST_STRING_DUTY_2.name)
	local escortDutyComplete = SpaceHelpers:isSpaceQuestComplete(pPlayer, HavocSquadronScreenplay.TIER2_QUEST_STRING_DUTY_3.type, HavocSquadronScreenplay.TIER2_QUEST_STRING_DUTY_3.name)

	local completedTier2 = SpaceHelpers:hasCompletedPilotTier(pPlayer, "rebel_navy", 2)

	-- viopaSmuggler flag states:
	-- 0/nil = Not sent to Vrak yet
	-- 1 = Sent to meet Vrak (after Mission 1 reward)
	-- 2 = Met Vrak, ready for Mission 2
	-- 3 = Sent to confront Vrak (after Mission 3 reward)
	-- 4 = Confronted Vrak, ready for Mission 4
	local viopaSmuggler = getQuestStatus(playerID .. "HavocSquadron:viopaSmuggler")

	if (viopaSmuggler == nil) then
		viopaSmuggler = 0
	else
		viopaSmuggler = tonumber(viopaSmuggler) or 0
	end

	--[[
			Quests
	--]]

	-- Player has an active mission from Viopa
	if ((questOneStarted and not questOneComplete) or (questTwoStarted and not questTwoComplete) or (questThreeStarted and not questThreeComplete) or (questFourStarted and not questFourComplete) or
		(destroyDutyStarted and not destroyDutyComplete) or (recoveryDutyStarted and not recoveryDutyComplete) or (escortDutyStarted and not escortDutyComplete)) then

		return convoTemplate:getScreen("has_mission")

	-- Check if players have all the tier2 skill boxes and finished the last mission, then send them to next trainer
	elseif (questFourComplete and completedTier2) then
		-- Player has all the skill boxes, they should be tier 3. Increment if not proper
		if (ghost:getPilotTier() <= 2) then
			ghost:incrementPilotTier()
		end

		return convoTemplate:getScreen("completed_viopa")

	-- Reward Checks
	elseif (questFourComplete and getQuestStatus(playerID .. HavocSquadronScreenplay.TIER2_QUEST_STRING_4.name .. ":reward") ~= "1") then
		return convoTemplate:getScreen("missions_complete")

	-- Mission 3 Complete: Check if player needs to confront Vrak
	elseif (questThreeComplete and getQuestStatus(playerID .. HavocSquadronScreenplay.TIER2_QUEST_STRING_3.name .. ":reward") ~= "1") then
		return convoTemplate:getScreen("excellent_work3")

	-- Player has confronted Vrak (viopaSmuggler == 4), ready for Mission 4
	elseif (questThreeComplete and viopaSmuggler == 4 and not questFourStarted) then
		return convoTemplate:getScreen("vrak_confronted")

	-- Player rewarded for Mission 3, needs to be sent to confront Vrak (or was sent but hasn't done it)
	elseif (questThreeComplete and getQuestStatus(playerID .. HavocSquadronScreenplay.TIER2_QUEST_STRING_3.name .. ":reward") == "1" and (viopaSmuggler == 2 or viopaSmuggler == 3) and not questFourStarted) then
		return convoTemplate:getScreen("send_confront_vrak")

	elseif (questTwoComplete and getQuestStatus(playerID .. HavocSquadronScreenplay.TIER2_QUEST_STRING_2.name .. ":reward") ~= "1") then
		return convoTemplate:getScreen("excellent_work2")

	-- Player failed/aborted Mission 2 - check this BEFORE check_vrak
	elseif (questOneComplete and not questTwoComplete and not questTwoStarted and getQuestStatus(playerID .. HavocSquadronScreenplay.TIER2_QUEST_STRING_2.name .. ":attempted") == "1") then
		return convoTemplate:getScreen("failed_mission2")

	-- Player was sent to Vrak (viopaSmuggler == 1) or met Vrak (viopaSmuggler == 2), check status
	elseif (questOneComplete and (viopaSmuggler == 1 or viopaSmuggler == 2) and not questTwoStarted) then
		return convoTemplate:getScreen("check_vrak")

	-- Player rewarded for Mission 1 but hasn't been sent to Vrak yet
	elseif (questOneComplete and getQuestStatus(playerID .. HavocSquadronScreenplay.TIER2_QUEST_STRING_1.name .. ":reward") == "1" and viopaSmuggler == 0) then
		return convoTemplate:getScreen("send_to_vrak")

	elseif (questOneComplete and getQuestStatus(playerID .. HavocSquadronScreenplay.TIER2_QUEST_STRING_1.name .. ":reward") ~= "1") then
		return convoTemplate:getScreen("excellent_work")

	-- Pilot is able to train
	elseif (not completedTier2 and SpaceHelpers:hasExperienceForTraining(pPlayer, 2)) then
		return convoTemplate:getScreen("more_training")

	elseif (not questFourComplete) then
		-- Player is able to start fourth mission
		if (questThreeComplete and not questFourStarted) then
			if (getQuestStatus(playerID .. HavocSquadronScreenplay.TIER2_QUEST_STRING_4.name .. ":attempted") == "1") then
				return convoTemplate:getScreen("failed_mission4")
			else
				return convoTemplate:getScreen("mission4_brief")
			end

		-- Player is able to start third mission
		elseif (questTwoComplete and not questThreeStarted) then
			if (getQuestStatus(playerID .. HavocSquadronScreenplay.TIER2_QUEST_STRING_3.name .. ":attempted") == "1") then
				return convoTemplate:getScreen("failed_mission3")
			else
				return convoTemplate:getScreen("mission3_brief")
			end

		-- Player is ready for first mission
		elseif (not questOneComplete and SpaceHelpers:hasPilotTierSkill(pPlayer, "rebel_navy", 2)) then
			if (getQuestStatus(playerID .. HavocSquadronScreenplay.TIER2_QUEST_STRING_1.name .. ":attempted") == "1") then
				return convoTemplate:getScreen("failed_mission1")
			else
				return convoTemplate:getScreen("start_mission1")
			end
		end
	end

	-- Player has been introduced but hasn't started quest 1 yet - show duty missions
	if (getQuestStatus(playerID .. HavocSquadronScreenplay.TIER2_QUEST_STRING_1.name .. ":introduced") == "1") then
		return convoTemplate:getScreen("duty_missions")
	end

	-- New pilot to Viopa
	return convoTemplate:getScreen("introduction")
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

	-- Handle check_vrak dynamic options based on viopaSmuggler flag
	elseif (screenID == "check_vrak") then
		local viopaSmuggler = getQuestStatus(playerID .. "HavocSquadron:viopaSmuggler")

		if (viopaSmuggler == nil) then
			viopaSmuggler = 0
		else
			viopaSmuggler = tonumber(viopaSmuggler) or 0
		end

		if (viopaSmuggler == 2) then
			-- Player met Vrak, show confirmation options (each leads to different intermediate screen)
			clonedConversation:addOption("@conversation/lok_rebel_trainer_2:s_14310e04", "vrak_meeting_formal") -- Yes milady, it seems he can assist us.
			clonedConversation:addOption("@conversation/lok_rebel_trainer_2:s_3892fde6", "vrak_meeting_casual") -- Sure did. He was a weird fellow.
		else
			-- Player hasn't met Vrak yet (viopaSmuggler == 1), show "not yet" option
			clonedConversation:addOption("@conversation/lok_rebel_trainer_2:s_38aeb877", "not_yet_vrak") -- Oh I was just passing by. I can't help right now.
		end

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

		if (SpaceHelpers:hasCompletedPilotTier(pPlayer, "rebel_navy", 2) and ghost:getPilotTier() <= 2) then
			ghost:incrementPilotTier()
		end

		return pClonedScreen

	-- Mission Rewards
	elseif (screenID == "mission4_rewarded") then
		if (getQuestStatus(playerID .. HavocSquadronScreenplay.TIER2_QUEST_STRING_4.name .. ":reward") ~= "1") then
			setQuestStatus(playerID .. HavocSquadronScreenplay.TIER2_QUEST_STRING_4.name .. ":reward", 1)

			-- Grant Reward
			assassinate_viopa_rebel_4:rewardPlayer(pPlayer)

			-- Grant Faction Standing
			ghost:increaseFactionStanding("rebel", 75)
		end
	elseif (screenID == "mission3_rewarded") then
		if (getQuestStatus(playerID .. HavocSquadronScreenplay.TIER2_QUEST_STRING_3.name .. ":reward") ~= "1") then
			setQuestStatus(playerID .. HavocSquadronScreenplay.TIER2_QUEST_STRING_3.name .. ":reward", 1)

			-- Grant Reward
			recovery_viopa_rebel_3:rewardPlayer(pPlayer)

			-- Grant Faction Standing
			ghost:increaseFactionStanding("rebel", 75)
		end
	elseif (screenID == "mission2_rewarded_humble" or screenID == "mission2_rewarded_payment") then
		if (getQuestStatus(playerID .. HavocSquadronScreenplay.TIER2_QUEST_STRING_2.name .. ":reward") ~= "1") then
			setQuestStatus(playerID .. HavocSquadronScreenplay.TIER2_QUEST_STRING_2.name .. ":reward", 1)

			-- Grant Reward
			escort_viopa_rebel_2:rewardPlayer(pPlayer)

			-- Grant Faction Standing
			ghost:increaseFactionStanding("rebel", 75)
		end
	elseif (screenID == "excellent_work") then
		if (getQuestStatus(playerID .. HavocSquadronScreenplay.TIER2_QUEST_STRING_1.name .. ":reward") ~= "1") then
			setQuestStatus(playerID .. HavocSquadronScreenplay.TIER2_QUEST_STRING_1.name .. ":reward", 1)

			-- Grant Reward
			inspect_viopa_rebel_1:rewardPlayer(pPlayer)

			-- Grant Faction Standing
			ghost:increaseFactionStanding("rebel", 75)
		end

	-- Duty Missions
	elseif (screenID == "destroy_duty") then
		destroy_duty_viopa_rebel_6:startQuest(pPlayer, pNpc)
	elseif (screenID == "recovery_duty") then
		recovery_duty_viopa_rebel_7:startQuest(pPlayer, pNpc)
	elseif (screenID == "escort_duty") then
		escort_duty_viopa_rebel_5:startQuest(pPlayer, pNpc)

	-- Introduction Flow
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

	-- Give Missions (Mission 1 - first time accept)
	elseif (screenID == "accept_mission1_easy" or screenID == "accept_mission1_consider") then
		setQuestStatus(playerID .. HavocSquadronScreenplay.TIER2_QUEST_STRING_1.name .. ":attempted", 1)

		inspect_viopa_rebel_1:startQuest(pPlayer, pNpc)

	-- Mission 1 - retry accept
	elseif (screenID == "retry_mission1_accept" or screenID == "retry_mission1_convinced") then
		inspect_viopa_rebel_1:startQuest(pPlayer, pNpc)

	elseif (screenID == "start_mission3") then
		setQuestStatus(playerID .. HavocSquadronScreenplay.TIER2_QUEST_STRING_3.name .. ":attempted", 1)

		recovery_viopa_rebel_3:startQuest(pPlayer, pNpc)
	elseif (screenID == "start_mission4") then
		setQuestStatus(playerID .. HavocSquadronScreenplay.TIER2_QUEST_STRING_4.name .. ":attempted", 1)

		assassinate_viopa_rebel_4:startQuest(pPlayer, pNpc)
	elseif (screenID == "retry_mission2_eager" or screenID == "retry_mission2_reluctant") then
		escort_viopa_rebel_2:startQuest(pPlayer, pNpc)
	elseif (screenID == "retry_mission3") then
		recovery_viopa_rebel_3:startQuest(pPlayer, pNpc)
	elseif (screenID == "retry_mission4") then
		assassinate_viopa_rebel_4:startQuest(pPlayer, pNpc)
	elseif (screenID == "goodbye") then
		CreatureObject(pNpc):doAnimation("goodbye")

	-- Vrak Smuggler Flow
	elseif (screenID == "send_to_vrak_accept") then
		-- Set flag so Vrak knows to give first meeting conversation
		setQuestStatus(playerID .. "HavocSquadron:viopaSmuggler", 1)

		-- Create waypoint to Vrak in Tyrena Cantina on Corellia
		PlayerObject(pGhost):addWaypoint("corellia", "Vrak (Tyrena Cantina)", "", -5244, 0, -2234, WAYPOINT_PURPLE, true, true, 0)

	elseif (screenID == "not_yet_vrak") then
		-- Player hasn't met Vrak yet, recreate waypoint in case they deleted it
		PlayerObject(pGhost):addWaypoint("corellia", "Vrak (Tyrena Cantina)", "", -5244, 0, -2234, WAYPOINT_PURPLE, true, true, 0)

	elseif (screenID == "mission2_granted_sweetie" or screenID == "mission2_granted_goodluck") then
		-- Player accepted Mission 2 (escort hacker to Dantooine)
		setQuestStatus(playerID .. HavocSquadronScreenplay.TIER2_QUEST_STRING_2.name .. ":attempted", 1)
		escort_viopa_rebel_2:startQuest(pPlayer, pNpc)

	elseif (screenID == "accept_confront_vrak") then
		-- Set flag so Vrak knows to give confrontation conversation
		setQuestStatus(playerID .. "HavocSquadron:viopaSmuggler", 3)

		-- Create waypoint to Vrak in Tyrena Cantina on Corellia
		PlayerObject(pGhost):addWaypoint("corellia", "Vrak (Tyrena Cantina)", "", -5244, 0, -2234, WAYPOINT_PURPLE, true, true, 0)
	end

	return pClonedScreen
end
