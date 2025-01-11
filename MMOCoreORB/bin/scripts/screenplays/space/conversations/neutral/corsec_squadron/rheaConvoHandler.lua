local QuestManager = require("managers.quest.quest_manager")

rheaConvoHandler = conv_handler:new {}

function rheaConvoHandler:getInitialScreen(pPlayer, pNpc, pConvTemplate)
	local convoTemplate = LuaConversationTemplate(pConvTemplate)

	local faction = CreatureObject(pPlayer):getFaction()
	local playerID = CreatureObject(pPlayer):getObjectID()

	-- JTL is disabled
	if (not isJtlEnabled()) then
		CreatureObject(pNpc):doAnimation("shake_head_no")

		return convoTemplate:getScreen("no_jtl") -- Sorry, but you don't look like a pilot to me.
	end

	-- Player is Rebel Pilot
	if (SpaceHelpers:isRebelPilot(pPlayer)) then
		CreatureObject(pNpc):doAnimation("wave_on_dismissing")

		return convoTemplate:getScreen("rebel_pilot") -- Greetings, citizen.  Keep your nose clean and we won't have any trouble.
	-- Player is Imperial Pilots
	elseif (SpaceHelpers:isImperialPilot(pPlayer)) then
		CreatureObject(pNpc):doAnimation("standing_placate")

		return convoTemplate:getScreen("imperial_pilot") -- Nothing to worry about here, sir.  CorSec has the area well secured.
	end

	local isNeutralPilot = SpaceHelpers:isNeutralPilot(pPlayer)
	local hasShip = SpaceHelpers:hasCertifiedShip(pPlayer, true)

	local questOneStarted = SpaceHelpers:isSpaceQuestActive(pPlayer, "patrol", "corellia_privateer_1")
	local questTwoStarted = SpaceHelpers:isSpaceQuestActive(pPlayer, "destroy", "corellia_privateer_2")
	local questThreeStarted = SpaceHelpers:isSpaceQuestActive(pPlayer, "patrol", "corellia_privateer_3")
	local questFourStarted = SpaceHelpers:isSpaceQuestActive(pPlayer, "assassinate", "corellia_privateer_tier1_4a")

	local questOneComplete = SpaceHelpers:isSpaceQuestComplete(pPlayer, "patrol", "corellia_privateer_1")
	local questTwoComplete = SpaceHelpers:isSpaceQuestComplete(pPlayer, "destroy", "corellia_privateer_2")
	local questThreeComplete = SpaceHelpers:isSpaceQuestComplete(pPlayer, "patrol", "corellia_privateer_3")
	local questFourComplete = SpaceHelpers:isSpaceQuestComplete(pPlayer, "assassinate", "corellia_privateer_tier1_4a")

	if (isNeutralPilot and not SpaceHelpers:isCorsecSquadron(pPlayer)) then
		CreatureObject(pNpc):doAnimation("point_accusingly")

		return convoTemplate:getScreen("non_corsec_pilot") -- Ah, I've heard of you!  You're not a bad pilot from what I understand. What can the CorSec do for you?
	-- Player does not have neutral pilot novice skill
	elseif (not isNeutralPilot) then
		CreatureObject(pNpc):doAnimation("greet")

		return convoTemplate:getScreen("recruitment") -- Hello!  Come to join the ranks of CorSec?

	-- Check to ensure player has a starter ship or one they can use
	elseif (not hasShip and not questOneStarted) then
		CreatureObject(pNpc):doAnimation("explain")

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

	-- Player has finished quest 4
	if (questFourComplete) then
		CreatureObject(pPlayer):sendSystemMessage("You are ready to train...")


	-- Player is actively working on Quest 4
	elseif (questFourStarted) then


	-- Player has finished quest 3
	elseif (questThreeComplete) then


	-- Player is actively working on Quest 3
	elseif (questThreeStarted) then


	-- Player has finished quest 2
	elseif (questTwoComplete) then


	-- Player is actively working on Quest 2
	elseif (questTwoStarted) then


	-- Player has finished quest 1 and needs to start quest 2
	elseif (questOneComplete) then
		CreatureObject(pPlayer):sendSystemMessage("Quest 2 is not implemented yet.")



		return convoTemplate:getScreen("no_jtl")

	-- Player has finished quest 1 final task
	elseif (not questOneComplete and SpaceHelpers:isSpaceQuestTaskComplete(pPlayer, "patrol", "corellia_privateer_1", 2)) then
		CreatureObject(pNpc):doAnimation("applause_polite")

		ThemeParkLogic:giveCredits(pPlayer, 100)

		-- Complete Journal Quest 1
		SpaceHelpers:completeSpaceQuest(pPilot, "patrol", "corellia_privateer_1", 1)

		return convoTemplate:getScreen("")
	-- Player has first quest active, the mission giver will offer assistance
	elseif (questOneStarted and not questOneComplete) then
		CreatureObject(pNpc):doAnimation("point_away")

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

	local pConvScreen = screen:cloneScreen()
	local clonedConversation = LuaConversationScreen(pConvScreen)

	clonedConversation:setDialogTextTU(CreatureObject(pPlayer):getFirstName())

	print("runScreenHandlers -- Screen ID: " .. screenID)

	local pGhost = CreatureObject(pPlayer):getPlayerObject()

	if (pGhost == nil) then
		return pConvScreen
	end

	local ghost = LuaPlayerObject(pGhost)

	if (ghost == nil) then
		return pConvScreen
	end

	if (screenID == "testing_reset") then
		CorsecSquadronScreenplay:resetRheaQuests(pPlayer)
		return pConvScreen
	elseif (PlayerObject(pGhost):isPrivileged()) then
		clonedConversation:addOption("GODMODE - Reset Sgt Rhea Quests", "testing_reset")
	end

	if (screenID == "non_corsec_pilot") then
		local isOnQuest = true -- TODO add in function to check for active space quest?

		if ((CreatureObject(pPlayer):hasSkill("pilot_neutral_starships_01") or CreatureObject(pPlayer):hasSkill("pilot_neutral_procedures_01") or CreatureObject(pPlayer):hasSkill("pilot_neutral_weapons_01") or CreatureObject(pPlayer):hasSkill("pilot_neutral_droid_01")) and not isOnQuest) then
			clonedConversation:addOption("@conversation/corellia_privateer_trainer:s_c1ff5062", "duty_missions") -- I'm looking for a mission. Do you have any?
		else
			clonedConversation:addOption("@conversation/corellia_privateer_trainer:s_c1ff5062", "no_missions") -- I'm looking for a mission. Do you have any?
		end
	elseif (screenID == "yes_join" or screenID == "i_see") then
		CreatureObject(pPlayer):doAnimation("nod_head_once")
		CreatureObject(pNpc):doAnimation("slow_down")

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
	elseif (screenID == "yes_denied" or screenID == "no_denied") then
		CreatureObject(pNpc):doAnimation("shake_head_no")
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
	elseif (screenID == "slow_down") then
		CreatureObject(pNpc):doAnimation("slow_down")
	elseif (screenID == "yes_im_ready") then
		SpaceHelpers:activateSpaceQuest(pPlayer, pNpc, "patrol", "corellia_privateer_1", 1)

		-- Write players quest step status
		setQuestStatus(SceneObject(pPlayer):getObjectID() .. ":CorsecSquadron", CorsecSquadronScreenplay.ACCEPTED_MISSION_1)

		-- Create inital observer for player entering Corellia Space

		if (not hasObserver(ZONESWITCHED, "CorsecSquadronScreenplay", "enteredZone", pPlayer)) then
			createObserver(ZONESWITCHED, "CorsecSquadronScreenplay", "enteredZone", pPlayer, 1)
		end
	elseif (screenID == "an_assignment_exp" or screenID == "where_to_go") then
		CreatureObject(pNpc):doAnimation("point_away")
	elseif (screenID == "what_ship" or screenID == "when_done") then
		CreatureObject(pNpc):doAnimation("explain")
	end

	return pConvScreen
end
