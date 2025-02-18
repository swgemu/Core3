local QuestManager = require("managers.quest.quest_manager")

rheaConvoHandler = conv_handler:new {}

function rheaConvoHandler:getInitialScreen(pPlayer, pNpc, pConvTemplate)
	local convoTemplate = LuaConversationTemplate(pConvTemplate)

	local faction = CreatureObject(pPlayer):getFaction()
	local playerID = CreatureObject(pPlayer):getObjectID()

	-- JTL is disabled
	if (not isJtlEnabled()) then
		return convoTemplate:getScreen("no_jtl") -- Sorry, but you don't look like a pilot to me.
	end

	-- Player is Rebel Pilot
	if (SpaceHelpers:isRebelPilot(pPlayer)) then
		return convoTemplate:getScreen("rebel_pilot") -- Greetings, citizen.  Keep your nose clean and we won't have any trouble.
	-- Player is Imperial Pilots
	elseif (SpaceHelpers:isImperialPilot(pPlayer)) then
		return convoTemplate:getScreen("imperial_pilot") -- Nothing to worry about here, sir.  CorSec has the area well secured.
	end

	--print("rheaConvoHandler:getInitialScreen  -- called")

	local isNeutralPilot = SpaceHelpers:isNeutralPilot(pPlayer)
	local hasShip = SpaceHelpers:hasCertifiedShip(pPlayer, true)

	local questOneStarted = SpaceHelpers:isSpaceQuestActive(pPlayer, CorsecSquadronScreenplay.QUEST_STRING_1.type, CorsecSquadronScreenplay.QUEST_STRING_1.name)
	local questTwoStarted = SpaceHelpers:isSpaceQuestActive(pPlayer, CorsecSquadronScreenplay.QUEST_STRING_2.type, CorsecSquadronScreenplay.QUEST_STRING_2.name)
	local questThreeStarted = SpaceHelpers:isSpaceQuestActive(pPlayer, CorsecSquadronScreenplay.QUEST_STRING_3.type, CorsecSquadronScreenplay.QUEST_STRING_3.name)
	local questFourStarted = SpaceHelpers:isSpaceQuestActive(pPlayer, CorsecSquadronScreenplay.QUEST_STRING_4.type, CorsecSquadronScreenplay.QUEST_STRING_4.name)

	local questOneComplete = SpaceHelpers:isSpaceQuestComplete(pPlayer, CorsecSquadronScreenplay.QUEST_STRING_1.type, CorsecSquadronScreenplay.QUEST_STRING_1.name) and SpaceHelpers:isSpaceQuestComplete(pPlayer, CorsecSquadronScreenplay.QUEST_STRING_1_SIDE.type, CorsecSquadronScreenplay.QUEST_STRING_1_SIDE.name)
	local questTwoComplete = SpaceHelpers:isSpaceQuestComplete(pPlayer, CorsecSquadronScreenplay.QUEST_STRING_2.type, CorsecSquadronScreenplay.QUEST_STRING_2.name)
	local questThreeComplete = SpaceHelpers:isSpaceQuestComplete(pPlayer, CorsecSquadronScreenplay.QUEST_STRING_3.type, CorsecSquadronScreenplay.QUEST_STRING_3.name) and SpaceHelpers:isSpaceQuestComplete(pPlayer, CorsecSquadronScreenplay.QUEST_STRING_3_SIDE.type, CorsecSquadronScreenplay.QUEST_STRING_3_SIDE.name)
	local questFourComplete = SpaceHelpers:isSpaceQuestComplete(pPlayer, CorsecSquadronScreenplay.QUEST_STRING_4.type, CorsecSquadronScreenplay.QUEST_STRING_4.name)

	local destroyDutyStarted = SpaceHelpers:isSpaceQuestActive(pPlayer, CorsecSquadronScreenplay.QUEST_STRING_DUTY_5.type, CorsecSquadronScreenplay.QUEST_STRING_DUTY_5.name)
	local escortDutyStarted = SpaceHelpers:isSpaceQuestActive(pPlayer, CorsecSquadronScreenplay.QUEST_STRING_DUTY_6.type, CorsecSquadronScreenplay.QUEST_STRING_DUTY_6.name)

	local destroyDutyComplete = SpaceHelpers:isSpaceQuestComplete(pPlayer, CorsecSquadronScreenplay.QUEST_STRING_DUTY_5.type, CorsecSquadronScreenplay.QUEST_STRING_DUTY_5.name)
	local escortDutyComplete = SpaceHelpers:isSpaceQuestComplete(pPlayer, CorsecSquadronScreenplay.QUEST_STRING_DUTY_6.type, CorsecSquadronScreenplay.QUEST_STRING_DUTY_6.name)

	if (isNeutralPilot and not SpaceHelpers:isCorsecSquadron(pPlayer)) then
		return convoTemplate:getScreen("non_corsec_pilot") -- Ah, I've heard of you!  You're not a bad pilot from what I understand. What can the CorSec do for you?
	-- Player does not have neutral pilot novice skill
	elseif (not isNeutralPilot) then
		return convoTemplate:getScreen("recruitment") -- Hello!  Come to join the ranks of CorSec?

	-- Check to ensure player has a starter ship or one they can use
	elseif (not hasShip and not questOneStarted) then
		return convoTemplate:getScreen("no_ship") -- You're going to need a ship, if you're going to fly for CorSec.  I'll add the Ship Control Codes to your datapad for you.  It's not a great ship, but it will get you around.
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
		-- Grant Neutral Newbie Ship
		grantStarterShip(pPlayer, "neutral")
	end

	--[[
			Quests
	--]]

	-- Player has an active quest from Sgt Rhea
	if ((questTwoStarted and not questTwoComplete) or (questThreeStarted and not questThreeComplete) or (questFourStarted and not questFourComplete) or (destroyDutyStarted and not destroyDutyComplete) or (escortDutyStarted and not escortDutyComplete)) then
		return convoTemplate:getScreen("has_mission")
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
	elseif (questFourComplete and getQuestStatus(playerID .. CorsecSquadronScreenplay.QUEST_STRING_4.name .. ":reward") == "1") then
		return convoTemplate:getScreen("missions_complete")
	-- Player has completed quest 4 and needs reward
	elseif (questFourComplete and getQuestStatus(playerID .. CorsecSquadronScreenplay.QUEST_STRING_4.name .. ":reward") ~= "1") then
		-- Give player the reward and update that they received it
		setQuestStatus(playerID .. CorsecSquadronScreenplay.QUEST_STRING_4.name .. ":reward", 1)

		-- Grant Reward
		assassinate_corellia_privateer_tier1_4a:rewardPlayer(pPlayer)

		return convoTemplate:getScreen("missions_complete")
	-- Player has finished 3, has received the reward and needs to start quest 4
	elseif (questThreeComplete and not questFourStarted and getQuestStatus(playerID .. CorsecSquadronScreenplay.QUEST_STRING_3.name .. ":reward") == "1") then
		return convoTemplate:getScreen("excellent_work3")
	-- Player has completed quest 3 and needs reward
	elseif (questThreeComplete and getQuestStatus(playerID .. CorsecSquadronScreenplay.QUEST_STRING_3.name .. ":reward") ~= "1") then
		-- Give player the reward and update that they received it
		setQuestStatus(playerID .. CorsecSquadronScreenplay.QUEST_STRING_3.name .. ":reward", 1)

		-- Grant Reward
		patrol_corellia_privateer_3:rewardPlayer(pPlayer)

		return convoTemplate:getScreen("excellent_work3")
	-- Player has finished 2, has received the reward and needs to start quest 3
	elseif (questTwoComplete and not questThreeStarted and getQuestStatus(playerID .. CorsecSquadronScreenplay.QUEST_STRING_2.name .. ":reward") == "1") then
		return convoTemplate:getScreen("excellent_work2")
	-- Player has completed quest 2 and needs reward
	elseif (questTwoComplete and getQuestStatus(playerID .. CorsecSquadronScreenplay.QUEST_STRING_2.name .. ":reward") ~= "1") then
		-- Give player the reward and update that they received it
		setQuestStatus(playerID .. CorsecSquadronScreenplay.QUEST_STRING_2.name .. ":reward", 1)

		-- Grant Reward
		destroy_corellia_privateer_2:rewardPlayer(pPlayer)

		return convoTemplate:getScreen("excellent_work2")
	-- Player has finished quest 1, has received the reward and needs to start quest 2
	elseif (questOneComplete and not questTwoStarted and getQuestStatus(playerID .. CorsecSquadronScreenplay.QUEST_STRING_1.name .. ":reward") == "1") then
		return convoTemplate:getScreen("excellent_work")
	-- Player has finished quest 1 and needs reward
	elseif (questOneComplete and getQuestStatus(playerID .. CorsecSquadronScreenplay.QUEST_STRING_1.name .. ":reward") ~= 1) then
		-- Give player the reward and update that they received it
		setQuestStatus(playerID .. CorsecSquadronScreenplay.QUEST_STRING_1.name .. ":reward", 1)

		-- Grant Reward
		patrol_corellia_privateer_1:rewardPlayer(pPlayer)

		return convoTemplate:getScreen("excellent_work")
	-- Player has first quest active, the mission giver will offer assistance
	elseif (questOneStarted and not questOneComplete) then
		return convoTemplate:getScreen("first_assignment")
	-- Player has failed or aborted the first quest
	elseif (not questOneComplete) then
		return convoTemplate:getScreen("yes_im_ready")
	end

	return convoTemplate:getScreen("no_jtl")
end

function rheaConvoHandler:runScreenHandlers(pConvTemplate, pPlayer, pNpc, selectedOption, pConvScreen)
	if (pPlayer == nil or pConvScreen == nil) then
		return
	end

	local screen = LuaConversationScreen(pConvScreen)
	local screenID = screen:getScreenID()

	local pClonedScreen = screen:cloneScreen()
	local clonedConversation = LuaConversationScreen(pClonedScreen)

	-- Set player as conversation target
	clonedConversation:setDialogTextTU(CreatureObject(pPlayer):getFirstName())

	--print("runScreenHandlers -- Screen ID: " .. screenID)

	local pGhost = CreatureObject(pPlayer):getPlayerObject()

	if (pGhost == nil) then
		return pClonedScreen
	end

	local ghost = LuaPlayerObject(pGhost)

	if (ghost == nil) then
		return pClonedScreen
	end

	-- Handle additional training
	if (screenID == "more_training") then
		local skillManager = LuaSkillManager()

		if (not CreatureObject(pPlayer):hasSkill("pilot_neutral_starships_01") and skillManager:fulfillsSkillPrerequisitesAndXp(pPlayer, "pilot_neutral_starships_01")) then
			clonedConversation:addOption("@conversation/corellia_privateer_trainer:s_c06c7aa9", "train_player_fighters") -- I'm interested in basic fighters.
		end
		if (not CreatureObject(pPlayer):hasSkill("pilot_neutral_weapons_01") and skillManager:fulfillsSkillPrerequisitesAndXp(pPlayer, "pilot_neutral_weapons_01")) then
			clonedConversation:addOption("@conversation/corellia_privateer_trainer:s_d1431f95", "train_player_component") -- I'm interested in basic starship component use.
		end
		if (not CreatureObject(pPlayer):hasSkill("pilot_neutral_procedures_01") and skillManager:fulfillsSkillPrerequisitesAndXp(pPlayer, "pilot_neutral_procedures_01")) then
			clonedConversation:addOption("@conversation/corellia_privateer_trainer:s_8523e1fc", "train_player_basics") -- I'm interested in basic training
		end
		if (not CreatureObject(pPlayer):hasSkill("pilot_neutral_droid_01") and skillManager:fulfillsSkillPrerequisitesAndXp(pPlayer, "pilot_neutral_droid_01")) then
			clonedConversation:addOption("@conversation/corellia_privateer_trainer:s_b7fc5e5d", "train_player_droid") -- I'm interested in droid interface basics.
		end
	-- Handle Skill box granting
	elseif (string.find(screenID, "train_player_")) then
		local skillManager = LuaSkillManager()

		local deductExperience = (string.find(screenID, "_free") == nil)

		screenID = string.gsub(screenID, "_free", "")

		if (screenID == "train_player_droid") then
			if (not deductExperience or skillManager:fulfillsSkillPrerequisitesAndXp(pPlayer, "pilot_neutral_droid_01")) then
				-- Train player Skill Box
				SpaceHelpers:grantSpaceSkill(pPlayer, "pilot_neutral_droid_01", deductExperience)
			end
		elseif (screenID == "train_player_basics") then
			if (not deductExperience or skillManager:fulfillsSkillPrerequisitesAndXp(pPlayer, "pilot_neutral_procedures_01")) then
				-- Train player Skill Box
				SpaceHelpers:grantSpaceSkill(pPlayer, "pilot_neutral_procedures_01", deductExperience)
			end
		elseif (screenID == "train_player_fighters") then
			if (not deductExperience or skillManager:fulfillsSkillPrerequisitesAndXp(pPlayer, "pilot_neutral_starships_01")) then
				-- Train player Skill Box
				SpaceHelpers:grantSpaceSkill(pPlayer, "pilot_neutral_starships_01", deductExperience)
			end
		elseif (screenID == "train_player_component") then
			if (not deductExperience or skillManager:fulfillsSkillPrerequisitesAndXp(pPlayer, "pilot_neutral_weapons_01")) then
				-- Train player Skill Box
				SpaceHelpers:grantSpaceSkill(pPlayer, "pilot_neutral_weapons_01", deductExperience)
			end
		end

		return pClonedScreen
	elseif (screenID == "destroy_duty") then
		--destroy_duty_corellia_privateer_6:startQuest(pPlayer, pNpc)
	elseif (screenID == "escort_duty") then
		escort_duty_corellia_privateer_7:startQuest(pPlayer, pNpc)
	elseif (screenID == "yes_join" or screenID == "i_see") then
		CreatureObject(pPlayer):doAnimation("nod_head_once")

		local corsecStanding = ghost:getFactionStanding("corsec")

		if (corsecStanding < 0) then
			clonedConversation:addOption("@conversation/corellia_privateer_trainer:s_1418de80", "of_course_no_good") -- Of course
			clonedConversation:addOption("@conversation/corellia_privateer_trainer:s_77e48d5b", "what_no_good") -- What do you mean?
			clonedConversation:addOption("@conversation/corellia_privateer_trainer:s_64b308bc", "ridiculous_no_good") -- That's ridiculous!
		elseif (corsecStanding > 200) then
			clonedConversation:addOption("@conversation/corellia_privateer_trainer:s_1418de80", "of_course_great") -- Of course
			clonedConversation:addOption("@conversation/corellia_privateer_trainer:s_77e48d5b", "what_great") -- What do you mean?
			clonedConversation:addOption("@conversation/corellia_privateer_trainer:s_64b308bc", "ridiculous_great") -- That's ridiculous!
		else
			clonedConversation:addOption("@conversation/corellia_privateer_trainer:s_1418de80", "of_course") -- Of course
			clonedConversation:addOption("@conversation/corellia_privateer_trainer:s_77e48d5b", "what_do_you_mean") -- What do you mean?
			clonedConversation:addOption("@conversation/corellia_privateer_trainer:s_64b308bc", "ridiculous") -- That's ridiculous!
		end
	elseif (screenID == "no_join") then
			CreatureObject(pPlayer):doAnimation("shake_head_no")

	-- Negative corsec faction
	elseif (screenID == "of_course_no_good") then
		CreatureObject(pPlayer):doAnimation("nod_head_multiple")
		CreatureObject(pNpc):doAnimation("check_wrist_device")
	elseif (screenID == "maybe_no_good") then
		CreatureObject(pPlayer):doAnimation("shrug_hands")
		CreatureObject(pNpc):doAnimation("wave_finger_warning")
	elseif (screenID == "maybe_not_no_good") then
		CreatureObject(pPlayer):doAnimation("wave_on_dismissing")
		CreatureObject(pNpc):doAnimation("wave_finger_warning")
	elseif (screenID == "ridiculous_no_good") then
		CreatureObject(pPlayer):doAnimation("shake_head_disgust")
		CreatureObject(pNpc):doAnimation("shake_head_disgust")

	-- Positive corsec faction
	elseif (screenID == "of_course_great" or screenID == "of_course") then
		CreatureObject(pNpc):doAnimation("check_wrist_device")
	elseif (screenID == "ridiculous_great") then
		CreatureObject(pPlayer):doAnimation("shake_head_disgust")
	elseif (screenID == "positive_reject") then
		CreatureObject(pPlayer):doAnimation("nod_head_multiple")
		CreatureObject(pNpc):doAnimation("shrug_shoulders")
	elseif (screenID == "maybe_great") then
		CreatureObject(pPlayer):doAnimation("rub_chin_thoughtful")
		CreatureObject(pNpc):doAnimation("nod_head_once")

		-- Grant freelance pilot novice box
		SpaceHelpers:grantNovicePilot(pPlayer, "neutralPilot")

		-- Sets Corsec Squadron
		SpaceHelpers:setSquadronType(pPlayer, CORSEC_SQUADRON)

		-- Set pilot tier
		PlayerObject(pGhost):incrementPilotTier()
	elseif (screenID == "goodbye") then
		CreatureObject(pPlayer):doAnimation("slump_head")
		CreatureObject(pNpc):doAnimation("goodbye")
	elseif (screenID == "yes_i_am") then
		CreatureObject(pPlayer):doAnimation("nod_head_once")
		CreatureObject(pNpc):doAnimation("point_to_self")

		-- Grant freelance pilot novice box
		SpaceHelpers:grantNovicePilot(pPlayer, "neutralPilot")

		-- Sets Corsec Squadron
		SpaceHelpers:setSquadronType(pPlayer, CORSEC_SQUADRON)

		-- Set pilot tier
		PlayerObject(pGhost):incrementPilotTier()

		if (not SpaceHelpers:hasCertifiedShip(pPlayer, true)) then
			clonedConversation:addOption("@conversation/corellia_privateer_trainer:s_5091cb8e", "no_ship") -- Ah... no I don't.
		else
			clonedConversation:addOption("@conversation/corellia_privateer_trainer:s_90ec63e0", "yes_ship") -- Yes, I do.
		end
	elseif (screenID == "what_do_you_mean") then
		CreatureObject(pPlayer):doAnimation("cover_mouth")
	elseif (screenID == "join_denied") then
		CreatureObject(pPlayer):doAnimation("wave_finger_warning")
	elseif (screenID == "i_dont_think") then
		CreatureObject(pPlayer):doAnimation("wave_on_dismissing")
	elseif (screenID == "i_dont_think_so") then -- Very well.  Let me know if you change your mind.
		CreatureObject(pPlayer):doAnimation("laugh_titter")
		CreatureObject(pNpc):doAnimation("wave_on_dismissing")
	elseif (screenID == "ridiculous") then
		CreatureObject(pPlayer):doAnimation("shake_head_disgust")
		CreatureObject(pNpc):doAnimation("pound_fist_palm")
	elseif (screenID == "no_ship") then
		if (not SpaceHelpers:hasCertifiedShip(pPlayer, true)) then
			-- Grant Neutral Newbie Ship
			grantStarterShip(pPlayer, "neutral");
		end

	-- Missions
	elseif (screenID == "yes_im_ready") then
		patrol_corellia_privateer_1:startQuest(pPlayer, pNpc)
	elseif (screenID == "i_was_attacked") then
		CreatureObject(pPlayer):doAnimation("pound_fist_palm")
		CreatureObject(pNpc):doAnimation("explain")
	elseif (screenID == "nothing_to_it") then
		CreatureObject(pPlayer):doAnimation("nod_head_multiple")
		CreatureObject(pNpc):doAnimation("rub_chin_thoughtful")
	elseif (screenID == "train_me2") then
		destroy_corellia_privateer_2:startQuest(pPlayer, pNpc)
	elseif (screenID == "whats_next") then
		CreatureObject(pPlayer):doAnimation("shrug_hands")
	elseif (screenID == "was_a_snap") then
		CreatureObject(pPlayer):doAnimation("snap_finger1")
		CreatureObject(pNpc):doAnimation("explain")
	elseif (screenID == "train_me3") then
		CreatureObject(pNpc):doAnimation("shake_head_no")
		CreatureObject(pPlayer):doAnimation("belly_laugh")

		patrol_corellia_privateer_3:startQuest(pPlayer, pNpc)
	elseif (screenID == "train_me4") then
		CreatureObject(pNpc):doAnimation("nod_head_once")
		CreatureObject(pPlayer):doAnimation("belly_laugh")

		assassinate_corellia_privateer_tier1_4a:startQuest(pPlayer, pNpc)
	end

	return pClonedScreen
end
