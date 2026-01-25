local SpaceHelpers = require("utils.space_helpers")

kreezoConvoHandler = conv_handler:new {}

function kreezoConvoHandler:getInitialScreen(pPlayer, pNpc, pConvTemplate)
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

	-- Reset test
	--CreatureObject(pPlayer):surrenderSkill("pilot_rebel_navy_novice")
	--HavocSquadronScreenplay:resetKreezoQuests(pPlayer)

	-- Player is Imperial Pilot
	if (SpaceHelpers:isImperialPilot(pPlayer)) then
		return convoTemplate:getScreen("imperial_pilot")
	-- Player is Neutral Pilot
	elseif (SpaceHelpers:isNeutralPilot(pPlayer)) then
		return convoTemplate:getScreen("neutral_pilot")
	end

	local isRebelPilot = SpaceHelpers:isRebelPilot(pPlayer)
	local hasShip = SpaceHelpers:hasCertifiedShip(pPlayer, true)

	local questOneStarted = SpaceHelpers:isSpaceQuestActive(pPlayer, HavocSquadronScreenplay.QUEST_STRING_1.type, HavocSquadronScreenplay.QUEST_STRING_1.name)
	local questTwoStarted = SpaceHelpers:isSpaceQuestActive(pPlayer, HavocSquadronScreenplay.QUEST_STRING_2.type, HavocSquadronScreenplay.QUEST_STRING_2.name)
	local questThreeStarted = SpaceHelpers:isSpaceQuestActive(pPlayer, HavocSquadronScreenplay.QUEST_STRING_3.type, HavocSquadronScreenplay.QUEST_STRING_3.name)
	local questFourStarted = SpaceHelpers:isSpaceQuestActive(pPlayer, HavocSquadronScreenplay.QUEST_STRING_4.type, HavocSquadronScreenplay.QUEST_STRING_4.name)

	local questOneComplete = SpaceHelpers:isSpaceQuestComplete(pPlayer, HavocSquadronScreenplay.QUEST_STRING_1.type, HavocSquadronScreenplay.QUEST_STRING_1.name) and SpaceHelpers:isSpaceQuestComplete(pPlayer, HavocSquadronScreenplay.QUEST_STRING_1_SIDE.type, HavocSquadronScreenplay.QUEST_STRING_1_SIDE.name)
	local questTwoComplete = SpaceHelpers:isSpaceQuestComplete(pPlayer, HavocSquadronScreenplay.QUEST_STRING_2.type, HavocSquadronScreenplay.QUEST_STRING_2.name)
	local questThreeComplete = SpaceHelpers:isSpaceQuestComplete(pPlayer, HavocSquadronScreenplay.QUEST_STRING_3.type, HavocSquadronScreenplay.QUEST_STRING_3.name) and SpaceHelpers:isSpaceQuestComplete(pPlayer, HavocSquadronScreenplay.QUEST_STRING_3_SIDE.type, HavocSquadronScreenplay.QUEST_STRING_3_SIDE.name)
	local questFourComplete = SpaceHelpers:isSpaceQuestComplete(pPlayer, HavocSquadronScreenplay.QUEST_STRING_4.type, HavocSquadronScreenplay.QUEST_STRING_4.name)

	local destroyDutyStarted = SpaceHelpers:isSpaceQuestActive(pPlayer, HavocSquadronScreenplay.QUEST_STRING_DUTY_1.type, HavocSquadronScreenplay.QUEST_STRING_DUTY_1.name)
	local escortDutyStarted = SpaceHelpers:isSpaceQuestActive(pPlayer, HavocSquadronScreenplay.QUEST_STRING_DUTY_2.type, HavocSquadronScreenplay.QUEST_STRING_DUTY_2.name)

	local destroyDutyComplete = SpaceHelpers:isSpaceQuestComplete(pPlayer, HavocSquadronScreenplay.QUEST_STRING_DUTY_1.type, HavocSquadronScreenplay.QUEST_STRING_DUTY_1.name)
	local escortDutyComplete = SpaceHelpers:isSpaceQuestComplete(pPlayer, HavocSquadronScreenplay.QUEST_STRING_DUTY_2.type, HavocSquadronScreenplay.QUEST_STRING_DUTY_2.name)

	-- Player is a Rebel Pilot but a different squadron
	if (isRebelPilot and not SpaceHelpers:isHavocSquadron(pPlayer)) then
		return convoTemplate:getScreen("non_havoc_pilot")
	-- Player does not have rebel pilot novice skill
	elseif (not isRebelPilot) then
		-- Check faction standing
		local pGhost = CreatureObject(pPlayer):getPlayerObject()
		if (pGhost ~= nil) then
			local rebelStanding = PlayerObject(pGhost):getFactionStanding("rebel")
			if (rebelStanding < 0) then
				return convoTemplate:getScreen("recruitment_negative_standing")
			end
		end
		return convoTemplate:getScreen("recruitment")
	-- Check to ensure player has a starter ship or one they can use
	elseif (not hasShip and not questOneStarted) then
		return convoTemplate:getScreen("no_ship")
	end

	local pGhost = CreatureObject(pPlayer):getPlayerObject()

	if (pGhost == nil) then
		return convoTemplate:getScreen("no_jtl")
	end

	local ghost = LuaPlayerObject(pGhost)

	if (ghost == nil) then
		return convoTemplate:getScreen("no_jtl")
	end

	-- Player destroyed their ship control device
	if (not hasShip) then
		-- Grant Rebel Newbie Ship
		grantStarterShip(pPlayer, "rebel")
	end

	--[[
			Quests
	--]]

	-- Player has an active quest from Kreezo
	if ((questTwoStarted and not questTwoComplete) or (questThreeStarted and not questThreeComplete) or (questFourStarted and not questFourComplete) or (destroyDutyStarted and not destroyDutyComplete) or (escortDutyStarted and not escortDutyComplete)) then
		return convoTemplate:getScreen("has_mission")
	-- Check if players have all the tier1 skill boxes, send them to next trainer.
	elseif (SpaceHelpers:hasCompletedPilotTier(pPlayer, "rebel_navy", 1)) then
		return convoTemplate:getScreen("completed_kreezo")
	-- Player is a Havoc pilot and has at least one of the Tier1 skill boxes
	elseif (SpaceHelpers:hasPilotTierSkill(pPlayer, "rebel_navy", 1)) then
		-- Check if the player can be trained in the remaining Tier1 Skills
		if (SpaceHelpers:hasExperienceForTraining(pPlayer, 1)) then
			return convoTemplate:getScreen("more_training")
		-- Offer Duty missions
		else
			CreatureObject(pPlayer):doAnimation("salute1")

			return convoTemplate:getScreen("duty_missions")
		end
	-- Player has completed quest 4 and needs reward
	elseif (questFourComplete) then
		if (getQuestStatus(playerID .. HavocSquadronScreenplay.QUEST_STRING_4.name .. ":reward") ~= "1") then
			-- Give player the reward and update that they received it
			setQuestStatus(playerID .. HavocSquadronScreenplay.QUEST_STRING_4.name .. ":reward", 1)

			-- Grant Reward
			assassinate_corellia_rebel_4:rewardPlayer(pPlayer)

			-- Grant Faction Standing
			PlayerObject(pGhost):increaseFactionStanding("rebel", 75)
		end

		return convoTemplate:getScreen("missions_complete")
	-- Player has finished 3, has received the reward and needs to start quest 4
	elseif (questThreeComplete and not questFourStarted and getQuestStatus(playerID .. HavocSquadronScreenplay.QUEST_STRING_3.name .. ":reward") == "1") then
		return convoTemplate:getScreen("grant_quest4")
	-- Player has completed quest 3 and needs reward (reward given in runScreenHandlers when they respond)
	elseif (questThreeComplete and getQuestStatus(playerID .. HavocSquadronScreenplay.QUEST_STRING_3.name .. ":reward") ~= "1") then
		return convoTemplate:getScreen("excellent_work3")
	-- Player has finished 2, has received the reward and needs to start quest 3
	elseif (questTwoComplete and not questThreeStarted and getQuestStatus(playerID .. HavocSquadronScreenplay.QUEST_STRING_2.name .. ":reward") == "1") then
		return convoTemplate:getScreen("excellent_work2")
	-- Player has completed quest 2 and needs reward
	elseif (questTwoComplete and getQuestStatus(playerID .. HavocSquadronScreenplay.QUEST_STRING_2.name .. ":reward") ~= "1") then
		-- Give player the reward and update that they received it
		setQuestStatus(playerID .. HavocSquadronScreenplay.QUEST_STRING_2.name .. ":reward", 1)

		-- Grant Reward
		destroy_corellia_rebel_2:rewardPlayer(pPlayer)

		-- Grant Faction Standing
		PlayerObject(pGhost):increaseFactionStanding("rebel", 50)

		return convoTemplate:getScreen("excellent_work2")
	-- Player has finished quest 1, received reward, needs to start quest 2
	elseif (questOneComplete and not questTwoStarted and getQuestStatus(playerID .. HavocSquadronScreenplay.QUEST_STRING_1.name .. ":reward") == "1") then
		return convoTemplate:getScreen("grant_quest2")
	-- Player has finished quest 1 and needs to report to Kreezo
	elseif (questOneComplete and getQuestStatus(playerID .. HavocSquadronScreenplay.QUEST_STRING_1.name .. ":reward") ~= "1") then
		return convoTemplate:getScreen("excellent_work")
	-- Player has first quest active, the mission giver will offer assistance
	elseif (questOneStarted and not questOneComplete) then
		return convoTemplate:getScreen("first_quest_active")
	-- Player has attempted quest 1 but failed/aborted
	elseif (getQuestStatus(playerID .. HavocSquadronScreenplay.QUEST_STRING_1.name .. ":attempted") == "1" and not questOneComplete) then
		return convoTemplate:getScreen("failed_quest1")
	-- Player needs to start quest 1
	elseif (not questOneComplete) then
		return convoTemplate:getScreen("yes_ship")
	end

	return convoTemplate:getScreen("no_jtl")
end

function kreezoConvoHandler:runScreenHandlers(pConvTemplate, pPlayer, pNpc, selectedOption, pConvScreen)
	if (pPlayer == nil or pConvScreen == nil) then
		return
	end

	local screen = LuaConversationScreen(pConvScreen)
	local screenID = screen:getScreenID()

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

	-- Handle first free training after completing all 4 missions (player chooses which skill)
	if (screenID == "missions_complete") then
		if (not CreatureObject(pPlayer):hasSkill("pilot_rebel_navy_starships_01")) then
			clonedConversation:addOption("@conversation/corellia_rebel_trainer_1:s_26970ef", "train_player_fighters_free") -- I am interested in basic starfighter training.
		end
		if (not CreatureObject(pPlayer):hasSkill("pilot_rebel_navy_weapons_01")) then
			clonedConversation:addOption("@conversation/corellia_rebel_trainer_1:s_3fa70900", "train_player_component_free") -- I am interested in basic starship component use.
		end
		if (not CreatureObject(pPlayer):hasSkill("pilot_rebel_navy_procedures_01")) then
			clonedConversation:addOption("@conversation/corellia_rebel_trainer_1:s_8c272224", "train_player_basics_free") -- I am interested in starfighter survival tactics.
		end
		if (not CreatureObject(pPlayer):hasSkill("pilot_rebel_navy_droid_01")) then
			clonedConversation:addOption("@conversation/corellia_rebel_trainer_1:s_9480f430", "train_player_droid_free") -- I am interested in droid interface basics.
		end
	-- Handle additional training (requires XP)
	elseif (screenID == "more_training") then
		local skillManager = LuaSkillManager()

		if (not CreatureObject(pPlayer):hasSkill("pilot_rebel_navy_starships_01") and skillManager:fulfillsSkillPrerequisitesAndXp(pPlayer, "pilot_rebel_navy_starships_01")) then
			clonedConversation:addOption("@conversation/corellia_rebel_trainer_1:s_26970ef", "train_player_fighters") -- I am interested in basic starfighter training.
		end
		if (not CreatureObject(pPlayer):hasSkill("pilot_rebel_navy_weapons_01") and skillManager:fulfillsSkillPrerequisitesAndXp(pPlayer, "pilot_rebel_navy_weapons_01")) then
			clonedConversation:addOption("@conversation/corellia_rebel_trainer_1:s_3fa70900", "train_player_component") -- I am interested in basic starship component use.
		end
		if (not CreatureObject(pPlayer):hasSkill("pilot_rebel_navy_procedures_01") and skillManager:fulfillsSkillPrerequisitesAndXp(pPlayer, "pilot_rebel_navy_procedures_01")) then
			clonedConversation:addOption("@conversation/corellia_rebel_trainer_1:s_8c272224", "train_player_basics") -- I am interested in starfighter survival tactics.
		end
		if (not CreatureObject(pPlayer):hasSkill("pilot_rebel_navy_droid_01") and skillManager:fulfillsSkillPrerequisitesAndXp(pPlayer, "pilot_rebel_navy_droid_01")) then
			clonedConversation:addOption("@conversation/corellia_rebel_trainer_1:s_9480f430", "train_player_droid") -- I am interested in droid interface basics.
		end
	-- Handle Skill box granting
	elseif (string.find(screenID, "train_player_")) then
		local skillManager = LuaSkillManager()

		local deductExperience = (string.find(screenID, "_free") == nil)

		screenID = string.gsub(screenID, "_free", "")

		if (screenID == "train_player_droid") then
			if (not deductExperience or skillManager:fulfillsSkillPrerequisitesAndXp(pPlayer, "pilot_rebel_navy_droid_01")) then
				SpaceHelpers:grantSpaceSkill(pPlayer, "pilot_rebel_navy_droid_01", deductExperience)
			end
		elseif (screenID == "train_player_basics") then
			if (not deductExperience or skillManager:fulfillsSkillPrerequisitesAndXp(pPlayer, "pilot_rebel_navy_procedures_01")) then
				SpaceHelpers:grantSpaceSkill(pPlayer, "pilot_rebel_navy_procedures_01", deductExperience)
			end
		elseif (screenID == "train_player_fighters") then
			if (not deductExperience or skillManager:fulfillsSkillPrerequisitesAndXp(pPlayer, "pilot_rebel_navy_starships_01")) then
				SpaceHelpers:grantSpaceSkill(pPlayer, "pilot_rebel_navy_starships_01", deductExperience)
			end
		elseif (screenID == "train_player_component") then
			if (not deductExperience or skillManager:fulfillsSkillPrerequisitesAndXp(pPlayer, "pilot_rebel_navy_weapons_01")) then
				SpaceHelpers:grantSpaceSkill(pPlayer, "pilot_rebel_navy_weapons_01", deductExperience)
			end
		end

		if (SpaceHelpers:hasCompletedPilotTier(pPlayer, "rebel_navy", 1) and ghost:getPilotTier() == 1) then
			-- Increment pilot to Tier 2!
			ghost:incrementPilotTier()
		end

		return pClonedScreen
	elseif (screenID == "destroy_duty") then
		destroy_duty_corellia_rebel_6:startQuest(pPlayer, pNpc)
	elseif (screenID == "escort_duty") then
		escort_duty_corellia_rebel_7:startQuest(pPlayer, pNpc)
	-- Recruitment flow - gender-based branching for "I want to join the Rebellion!"
	elseif (screenID == "yes_join") then
		local convoTemplate = LuaConversationTemplate(pConvTemplate)
		local isMale = (CreatureObject(pPlayer):getGender() == 0)

		if (isMale) then
			return convoTemplate:getScreen("male_join_confirm")
		else
			return convoTemplate:getScreen("female_join_confirm")
		end
	elseif (screenID == "shrug_response") then
		local isMale = (CreatureObject(pPlayer):getGender() == 0)

		clonedConversation:addOption("@conversation/corellia_rebel_trainer_1:s_99dfe276", "no_join") -- Interested? Is there money in it?

		if (isMale) then
			clonedConversation:addOption("@conversation/corellia_rebel_trainer_1:s_b0643db5", "male_teach_me") -- You're going to teach ME?
		else
			clonedConversation:addOption("@conversation/corellia_rebel_trainer_1:s_b0643db5", "female_teach_me") -- You're going to teach ME?
		end
	elseif (screenID == "of_course") then
		local convoTemplate = LuaConversationTemplate(pConvTemplate)
		local isMale = (CreatureObject(pPlayer):getGender() == 0)

		if (isMale) then
			return convoTemplate:getScreen("male_destiny")
		else
			return convoTemplate:getScreen("female_pretty_face")
		end
	elseif (screenID == "yes_i_am" or screenID == "male_welcome_alliance") then
		-- Grant rebel pilot novice box
		SpaceHelpers:grantNovicePilot(pPlayer, "rebelPilot")

		-- Sets Havoc Squadron
		SpaceHelpers:setSquadronType(pPlayer, HAVOC_SQUADRON)

		-- Set pilot tier
		if (ghost:getPilotTier() < 1) then
			ghost:incrementPilotTier()
		end

		if (not SpaceHelpers:hasCertifiedShip(pPlayer, true)) then
			clonedConversation:addOption("@conversation/naboo_rebel_trainer_1:s_a42932d7", "no_ship") -- I will need a starship.
		else
			clonedConversation:addOption("@conversation/corellia_rebel_trainer_1:s_fc27931b", "yes_ship") -- Thanks.
		end
	elseif (screenID == "no_ship") then
		if (not SpaceHelpers:hasCertifiedShip(pPlayer, true)) then
			-- Grant Rebel Newbie Ship
			grantStarterShip(pPlayer, "rebel")
		end
	-- Missions
	elseif (screenID == "yes_im_ready") then
		local playerID = CreatureObject(pPlayer):getObjectID()

		-- Track that quest was attempted
		setQuestStatus(playerID .. HavocSquadronScreenplay.QUEST_STRING_1.name .. ":attempted", 1)

		patrol_corellia_rebel_1:startQuest(pPlayer, pNpc)
	elseif (screenID == "retry_quest1") then
		patrol_corellia_rebel_1:startQuest(pPlayer, pNpc)
	-- Quest 1 completion screens - give reward
	elseif (screenID == "i_was_attacked" or screenID == "imperial_ambush" or screenID == "not_resistance" or screenID == "tie_intercepted") then
		local playerID = CreatureObject(pPlayer):getObjectID()

		-- Only give reward once
		if (getQuestStatus(playerID .. HavocSquadronScreenplay.QUEST_STRING_1.name .. ":reward") ~= "1") then
			setQuestStatus(playerID .. HavocSquadronScreenplay.QUEST_STRING_1.name .. ":reward", 1)

			-- Grant Reward
			patrol_corellia_rebel_1:rewardPlayer(pPlayer)

			-- Grant Faction Standing
			PlayerObject(pGhost):increaseFactionStanding("rebel", 25)
		end
	elseif (screenID == "train_me2" or screenID == "quest2_accepted") then
		destroy_corellia_rebel_2:startQuest(pPlayer, pNpc)
	elseif (screenID == "train_me3" or screenID == "quest3_accepted") then
		patrol_corellia_rebel_3:startQuest(pPlayer, pNpc)
	elseif (screenID == "train_me4") then
		assassinate_corellia_rebel_4:startQuest(pPlayer, pNpc)
	-- Viopa waypoint
	elseif (screenID == "go_to_viopa" or screenID == "directions_to_viopa") then
		SpaceHelpers:addViopaWaypoint(pPlayer)
	-- Completed Quest 2 - gender-specific options
	elseif (screenID == "completed_quest2") then
		local isMale = (CreatureObject(pPlayer):getGender() == 0)

		if (isMale) then
			clonedConversation:addOption("@conversation/corellia_rebel_trainer_1:s_b4ce2d62", "quest2_rewarded") -- A magician never reveals his secrets!
		else
			clonedConversation:addOption("@conversation/corellia_rebel_trainer_1:s_c8cdb11", "quest2_rewarded") -- A magician never reveals her secrets!
		end

		clonedConversation:addOption("@conversation/corellia_rebel_trainer_1:s_c4e77d66", "quest2_rewarded") -- (Provide a detailed report)
		clonedConversation:addOption("@conversation/corellia_rebel_trainer_1:s_656e3c93", "quest2_rewarded") -- I don't remember much.
	-- Excellent Work 2 - gender-specific options
	elseif (screenID == "excellent_work2") then
		local isMale = (CreatureObject(pPlayer):getGender() == 0)

		if (isMale) then
			clonedConversation:addOption("@conversation/corellia_rebel_trainer_1:s_b4ce2d62", "whats_next") -- A magician never reveals his secrets!
		else
			clonedConversation:addOption("@conversation/corellia_rebel_trainer_1:s_c8cdb11", "whats_next") -- A magician never reveals her secrets!
		end

		clonedConversation:addOption("@conversation/corellia_rebel_trainer_1:s_c4e77d66", "was_a_snap") -- (Provide a detailed report)
		clonedConversation:addOption("@conversation/corellia_rebel_trainer_1:s_656e3c93", "whats_next") -- I don't remember much.
	-- Quest 3 Importance - gender-specific dialog
	elseif (screenID == "quest3_importance") then
		local isMale = (CreatureObject(pPlayer):getGender() == 0)

		if (not isMale) then
			clonedConversation:setDialogTextStringId("@conversation/corellia_rebel_trainer_1:s_6076cccb") -- They're civilian refugees, honey!
		end
	-- Quest 3 Rewarded - give reward and gender-specific dialog
	elseif (screenID == "quest3_rewarded") then
		local playerID = CreatureObject(pPlayer):getObjectID()

		-- Only give reward once
		if (getQuestStatus(playerID .. HavocSquadronScreenplay.QUEST_STRING_3.name .. ":reward") ~= "1") then
			setQuestStatus(playerID .. HavocSquadronScreenplay.QUEST_STRING_3.name .. ":reward", 1)

			-- Grant Reward
			patrol_corellia_rebel_3:rewardPlayer(pPlayer)

			-- Grant Faction Standing
			PlayerObject(pGhost):increaseFactionStanding("rebel", 50)
		end

		local isMale = (CreatureObject(pPlayer):getGender() == 0)

		if (not isMale) then
			clonedConversation:setDialogTextStringId("@conversation/corellia_rebel_trainer_1:s_8bc574b8") -- You're one in a million. You know that?
			clonedConversation:setAnimationName("wave_finger_warning")
		end
	-- Quest 3 Reward Explain - species-specific dialog
	elseif (screenID == "quest3_reward_explain") then
		local species = CreatureObject(pPlayer):getSpecies()

		-- Wookiee (2) or Ithorian (5)
		if (species == 2 or species == 5) then
			clonedConversation:setDialogTextStringId("@conversation/corellia_rebel_trainer_1:s_88620d24") -- It's a multi-pocket bandolier.
		end
	--[[
		PATH A: Casual path ("All right. Let's hear it!")
		4 options (females get grief option), loops until goodbye
	--]]
	elseif (screenID == "quest4_accepted" or screenID == "quest4_commander" or screenID == "quest4_location" or screenID == "quest4_grief") then
		-- Start the quest when first entering this conversation branch
		if (screenID == "quest4_accepted") then
			assassinate_corellia_rebel_4:startQuest(pPlayer, pNpc)
		end

		local isMale = (CreatureObject(pPlayer):getGender() == 0)

		clonedConversation:addOption("@conversation/corellia_rebel_trainer_1:s_492633c2", "quest4_commander") -- Who's this commander?
		clonedConversation:addOption("@conversation/corellia_rebel_trainer_1:s_44ca831b", "quest4_location") -- Where will I find him?

		if (not isMale) then
			clonedConversation:addOption("@conversation/corellia_rebel_trainer_1:s_632bed94", "quest4_grief") -- You're the cause of my grief, Kreezo.
		end

		clonedConversation:addOption("@conversation/corellia_rebel_trainer_1:s_6f169e12", "quest4_goodbye") -- Sounds easy enough, I'll take care of it!

	--[[
		PATH B: Military/Salute path ("(Salute) Affirmative!")
		2 options, loops until salute goodbye
	--]]
	elseif (screenID == "quest4_salute_accepted" or screenID == "quest4_salute_pilot") then
		-- Start the quest when first entering this conversation branch
		if (screenID == "quest4_salute_accepted") then
			assassinate_corellia_rebel_4:startQuest(pPlayer, pNpc)
		end

		clonedConversation:addOption("@conversation/corellia_rebel_trainer_1:s_469", "quest4_salute_goodbye") -- (Salute) Yes sir!
		clonedConversation:addOption("@conversation/corellia_rebel_trainer_1:s_87a8cca7", "quest4_salute_pilot") -- How will I know this pilot?

	-- Path B Goodbye - gender-specific dialog
	elseif (screenID == "quest4_salute_goodbye") then
		local isMale = (CreatureObject(pPlayer):getGender() == 0)

		if (isMale) then
			clonedConversation:setDialogTextStringId("@conversation/corellia_rebel_trainer_1:s_fe6d50dd") -- Good luck, man.
		end
		-- Female uses default dialog "Good luck."

	--[[
		PATH C: Alliance/Formal path ("For the Alliance... always.")
		3 options, loops until alliance goodbye
	--]]
	elseif (screenID == "quest4_alliance_accepted" or screenID == "quest4_alliance_veteran" or screenID == "quest4_alliance_targets") then
		-- Start the quest when first entering this conversation branch
		if (screenID == "quest4_alliance_accepted") then
			assassinate_corellia_rebel_4:startQuest(pPlayer, pNpc)
		end

		clonedConversation:addOption("@conversation/corellia_rebel_trainer_1:s_cf04e474", "quest4_alliance_veteran") -- What more do we know of this TIE veteran?
		clonedConversation:addOption("@conversation/corellia_rebel_trainer_1:s_d779178a", "quest4_alliance_targets") -- What other targets are in the area?
		clonedConversation:addOption("@conversation/corellia_rebel_trainer_1:s_52e212a5", "quest4_alliance_goodbye") -- I will bring honor to the Alliance.
	end

	return pClonedScreen
end
