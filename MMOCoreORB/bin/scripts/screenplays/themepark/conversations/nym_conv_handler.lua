local ObjectManager = require("managers.object.object_manager")

NymConvoHandler = conv_handler:new {
	themePark = nil
}

function NymConvoHandler:setThemePark(themeParkNew)
	self.themePark = themeParkNew
end

function NymConvoHandler:runScreenHandlers(pConvTemplate, pPlayer, pNpc, selectedOption, pConvScreen)
	local customName = SceneObject(pNpc):getCustomObjectName()
	local objectName = SceneObject(pNpc):getObjectName()

	if (customName == "Hacker") then
		return self:runHackerScreenHandlers(pConvTemplate, pPlayer, pNpc, selectedOption, pConvScreen)
	elseif (objectName == "nym") then
		return self:runNymScreenHandlers(pConvTemplate, pPlayer, pNpc, selectedOption, pConvScreen)
	elseif (customName == "Choster (Retired Engineer)") then
		return self:runChosterScreenHandlers(pConvTemplate, pPlayer, pNpc, selectedOption, pConvScreen)
	elseif (objectName == "jinkins") then
		return self:runJinkinsScreenHandlers(pConvTemplate, pPlayer, pNpc, selectedOption, pConvScreen)
	elseif (objectName == "kole") then
		return self:runKoleScreenHandlers(pConvTemplate, pPlayer, pNpc, selectedOption, pConvScreen)
	elseif (customName == "Berema") then
		return self:runBeremaScreenHandlers(pConvTemplate, pPlayer, pNpc, selectedOption, pConvScreen)
	elseif (customName == "Sergeant Moore (Retired)") then
		return self:runMooreScreenHandlers(pConvTemplate, pPlayer, pNpc, selectedOption, pConvScreen)
	end
	return pConvScreen
end

function NymConvoHandler:runNymScreenHandlers(pConvTemplate, pPlayer, pNpc, selectedOption, pConvScreen)
	local pGhost = CreatureObject(pPlayer):getPlayerObject()

	if (pGhost == nil) then
		return pConvScreen
	end

	local screen = LuaConversationScreen(pConvScreen)

	local screenID = screen:getScreenID()

	local pConvScreen = screen:cloneScreen()

	local playerID = CreatureObject(pPlayer):getObjectID()
	local clonedConversation = LuaConversationScreen(pConvScreen)
	if (screenID == "first_time_hello" or screenID == "yo_es_nym") then
		if (not CreatureObject(pPlayer):hasScreenPlayState(2, "nym_theme_park_jinkinsNpc")) or (not CreatureObject(pPlayer):hasScreenPlayState(2, "nym_theme_park_koleNpc")) then
			clonedConversation:addOption("@celebrity/nym:tell_me_quest", "help_others")
		else
			clonedConversation:addOption("@celebrity/nym:tell_me_quest", "quest_info")
		end
	elseif (screenID == "go_lab") then
		local oldWaypointID = tonumber(getQuestStatus(playerID .. ":nymFacilityWaypointID"))
		if (oldWaypointID ~= 0) then
			PlayerObject(pGhost):removeWaypoint(oldWaypointID, true)
			removeQuestStatus(playerID .. ":nymFacilityWaypointID")
		end
		local waypointID = PlayerObject(pGhost):addWaypoint("lok", "Imperial Research Facility", "Imperial Research Facility", ThemeParkNym.waypointMap.researchfacility.x, ThemeParkNym.waypointMap.researchfacility.y, WAYPOINT_COLOR_PURPLE, true, true, 0)
		setQuestStatus(playerID .. ":nymFacilityWaypointID", waypointID)
		self.themePark:setState(CreatureObject(pPlayer), 1, "nym_theme_park_nymNpc")
	elseif (screenID == "go_to_officer") then
		local oldWaypointID = tonumber(getQuestStatus(playerID .. ":nymGamblerWaypointID"))
		if (oldWaypointID ~= 0) then
			PlayerObject(pGhost):removeWaypoint(oldWaypointID, true)
			removeQuestStatus(playerID .. ":nymGamblerWaypointID")
		end
		local waypointID = PlayerObject(pGhost):addWaypoint("lok", "Nym's Informant", "Nym's Informant", ThemeParkNym.waypointMap.gambler.x, ThemeParkNym.waypointMap.gambler.y, WAYPOINT_COLOR_PURPLE, true, true, 0)
		setQuestStatus(playerID .. ":nymGamblerWaypointID", waypointID)
		self.themePark:setState(CreatureObject(pPlayer), 2, "nym_theme_park_nymNpc")
	end
	return pConvScreen
end

function NymConvoHandler:runChosterScreenHandlers(pConvTemplate, pPlayer, pNpc, selectedOption, pConvScreen)
	local screen = LuaConversationScreen(pConvScreen)
	local screenID = screen:getScreenID()
	local pConvScreen = screen:cloneScreen()
	local clonedConversation = LuaConversationScreen(pConvScreen)
	if (screenID == "hello") then
		if (CreatureObject(pPlayer):hasScreenPlayState(1, "nym_theme_park_chosterNpc")) then
			clonedConversation:addOption("@celebrity/lok_engineer:who_are_you", "just_a_guy")
		else
			clonedConversation:addOption("@celebrity/lok_engineer:who_are_you_2", "go_away_dude")
		end
	end
	return pConvScreen
end

function NymConvoHandler:runJinkinsScreenHandlers(pConvTemplate, pPlayer, pNpc, selectedOption, pConvScreen)
	local pGhost = CreatureObject(pPlayer):getPlayerObject()

	if (pGhost == nil) then
		return pConvScreen
	end

	local screen = LuaConversationScreen(pConvScreen)
	local screenID = screen:getScreenID()

	local playerID = CreatureObject(pPlayer):getObjectID()
	local pConvScreen = screen:cloneScreen()
	local clonedConversation = LuaConversationScreen(pConvScreen)
	if (screenID == "heres_droid_memory") then
		local oldWaypointID = tonumber(getQuestStatus(playerID .. ":nymPirateCaveWaypointID"))
		if (oldWaypointID ~= 0) then
			PlayerObject(pGhost):removeWaypoint(oldWaypointID, true)
			removeQuestStatus(playerID .. ":nymPirateCaveWaypointID")
		end
		local waypointID = PlayerObject(pGhost):addWaypoint("lok", "Sulfur Lake Pirate Hideout", "", ThemeParkNym.waypointMap.piratecave.x, ThemeParkNym.waypointMap.piratecave.y, WAYPOINT_COLOR_PURPLE, true, true, 0)
		setQuestStatus(playerID .. ":nymPirateCaveWaypointID", waypointID)
		self.themePark:setState(CreatureObject(pPlayer), 1, "nym_theme_park_jinkinsNpc")
	elseif (screenID == "heres_the_guy") then
		local oldWaypointID = tonumber(getQuestStatus(playerID .. ":nymHermitWaypointID"))
		if (oldWaypointID ~= 0) then
			PlayerObject(pGhost):removeWaypoint(oldWaypointID, true)
			removeQuestStatus(playerID .. ":nymHermitWaypointID")
		end
		local waypointID = PlayerObject(pGhost):addWaypoint("lok", "Hermit", "", ThemeParkNym.waypointMap.choster.x, ThemeParkNym.waypointMap.choster.y, WAYPOINT_COLOR_PURPLE, true, true, 0)
		setQuestStatus(playerID .. ":nymHermitWaypointID", waypointID)
		self.themePark:setState(CreatureObject(pPlayer), 1, "nym_theme_park_chosterNpc")
	elseif (screenID == "good_work" and clonedConversation:getOptionCount() == 0) then
		if (CreatureObject(pPlayer):hasScreenPlayState(2, "nym_theme_park_koleNpc")) then
			clonedConversation:addOption("@celebrity/jinkins:what_now", "talk_to_nym")
		else
			clonedConversation:addOption("@celebrity/jinkins:what_now", "talk_to_kole")
		end
		clonedConversation:addOption("@celebrity/jinkins:see_ya", "good_bye")
	end
	return pConvScreen
end

function NymConvoHandler:runKoleScreenHandlers(pConvTemplate, pPlayer, pNpc, selectedOption, pConvScreen)
	local pGhost = CreatureObject(pPlayer):getPlayerObject()

	if (pGhost == nil) then
		return pConvScreen
	end

	local screen = LuaConversationScreen(pConvScreen)
	local screenID = screen:getScreenID()

	local playerID = CreatureObject(pPlayer):getObjectID()
	local pConvScreen = screen:cloneScreen()
	local clonedConversation = LuaConversationScreen(pConvScreen)
	if (screenID == "first_time_hello" or screenID == "jinkins_is_friend" or screenID == "im_kole" or screenID == "nym_is_chief") then
		if (not CreatureObject(pPlayer):hasScreenPlayState(2, "nym_theme_park_jinkinsNpc")) then
			clonedConversation:addOption("@celebrity/kole:tell_me_quest", "quest_tease")
		else
			clonedConversation:addOption("@celebrity/kole:tell_me_quest", "quest_info")
		end
	elseif (screenID == "here_is_gas") then
		local oldWaypointID = tonumber(getQuestStatus(playerID .. ":nymGasMineWaypointID"))
		if (oldWaypointID ~= 0) then
			PlayerObject(pGhost):removeWaypoint(oldWaypointID, true)
			removeQuestStatus(playerID .. ":nymGasMineWaypointID")
		end
		local waypointID = PlayerObject(pGhost):addWaypoint("lok", "Imperial Gas Mine", "", ThemeParkNym.waypointMap.gasmine.x, ThemeParkNym.waypointMap.gasmine.y, WAYPOINT_COLOR_PURPLE, true, true, 0)
		setQuestStatus(playerID .. ":nymGasMineWaypointID", waypointID)
		self.themePark:setState(CreatureObject(pPlayer), 1, "nym_theme_park_koleNpc")
	elseif (screenID == "here_is_imperial") then
		local oldWaypointID = tonumber(getQuestStatus(playerID .. ":nymBribeWaypointID"))
		if (oldWaypointID ~= 0) then
			PlayerObject(pGhost):removeWaypoint(oldWaypointID, true)
			removeQuestStatus(playerID .. ":nymBribeWaypointID")
		end
		local waypointID = PlayerObject(pGhost):addWaypoint("lok", "Sergeant Moore", "", ThemeParkNym.waypointMap.imperialbribe.x, ThemeParkNym.waypointMap.imperialbribe.y, WAYPOINT_COLOR_PURPLE, true, true, 0)
		setQuestStatus(playerID .. ":nymBribeWaypointID", waypointID)
		self.themePark:setState(CreatureObject(pPlayer), 1, "nym_theme_park_mooreNpc")
	end
	return pConvScreen
end

function NymConvoHandler:runMooreScreenHandlers(pConvTemplate, pPlayer, pNpc, selectedOption, pConvScreen)
	local screen = LuaConversationScreen(pConvScreen)
	local screenID = screen:getScreenID()

	local pConvScreen = screen:cloneScreen()
	local clonedConversation = LuaConversationScreen(pConvScreen)
	local playerCredits = CreatureObject(pPlayer):getCashCredits()
	if (screenID == "leave_me_alone") then
		if (not CreatureObject(pPlayer):hasScreenPlayState(1, "nym_theme_park_mooreNpc")) then
			clonedConversation:addOption("@celebrity/imperial_bribe:who_are_you", "nunya")
		else
			clonedConversation:addOption("@celebrity/imperial_bribe:perhaps_bribe", "what_you_got")
		end
	end
	if (screenID == "what_you_got") then
		if (playerCredits >= 50) then
			clonedConversation:addOption("@celebrity/imperial_bribe:give_50", "medium_info")
		else
			clonedConversation:addOption("@celebrity/imperial_bribe:give_50", "you_got_nothing")
		end
		if (playerCredits >= 100) then
			clonedConversation:addOption("@celebrity/imperial_bribe:give_100", "the_good_stuff")
		else
			clonedConversation:addOption("@celebrity/imperial_bribe:give_100", "you_got_nothing")
		end
	elseif (screenID == "medium_info") then
		CreatureObject(pPlayer):subtractCashCredits(50)
	elseif (screenID == "the_good_stuff") then
		CreatureObject(pPlayer):subtractCashCredits(100)
	elseif (screenID == "need_more_cash") then
		if (playerCredits >= 100) then
			clonedConversation:addOption("@celebrity/imperial_bribe:add_100_bribe", "end_droideka_info")
		else
			clonedConversation:addOption("@celebrity/imperial_bribe:add_100_bribe", "you_got_nothing")
		end
	elseif (screenID == "need_more_money") then
		if (playerCredits >= 100) then
			clonedConversation:addOption("@celebrity/imperial_bribe:add_100_bribe", "end_base_info")
		else
			clonedConversation:addOption("@celebrity/imperial_bribe:add_100_bribe", "you_got_nothing")
		end
	elseif ((screenID == "end_base_info") or (screenID == "end_droideka_info")) then
		CreatureObject(pPlayer):subtractCashCredits(100)
	end
	if (screenID ~= "leave_me_alone" and screenID ~= "what_you_got") then
		clonedConversation:addOption("@celebrity/imperial_bribe:end_convo", "thats_all")
	end

	return pConvScreen
end

function NymConvoHandler:runHackerScreenHandlers(pConvTemplate, pPlayer, pNpc, selectedOption, pConvScreen)
	local pGhost = CreatureObject(pPlayer):getPlayerObject()

	if (pGhost == nil) then
		return pConvScreen
	end

	local screen = LuaConversationScreen(pConvScreen)
	local screenID = screen:getScreenID()

	-- Hacker states: 1= guessed color, 2 = guessed math, 4 = guessed joke, 8 = door opened
	if (screenID == "right_color") then
		self.themePark:setState(CreatureObject(pPlayer), 1, "nym_theme_park_hackerNpc")
	elseif (screenID == "right_answer") then
		self.themePark:setState(CreatureObject(pPlayer), 2, "nym_theme_park_hackerNpc")
	elseif (screenID == "right_joke") then
		self.themePark:setState(CreatureObject(pPlayer), 4, "nym_theme_park_hackerNpc")
	end
	local guessedColor = CreatureObject(pPlayer):hasScreenPlayState(1, "nym_theme_park_hackerNpc")
	local guessedMath = CreatureObject(pPlayer):hasScreenPlayState(2, "nym_theme_park_hackerNpc")
	local guessedJoke = CreatureObject(pPlayer):hasScreenPlayState(4, "nym_theme_park_hackerNpc")
	local doorStatus = CreatureObject(pPlayer):hasScreenPlayState(8, "nym_theme_park_hackerNpc")
	if (guessedColor and guessedMath and guessedJoke and not doorStatus) then
		self.themePark:setState(CreatureObject(pPlayer), 8, "nym_theme_park_hackerNpc")
		PlayerObject(pGhost):addPermissionGroup("NymPirateCave", true)
	end
	doorStatus = CreatureObject(pPlayer):hasScreenPlayState(8, "nym_theme_park_hackerNpc")
	if ((screenID == "right_color") or (screenID == "right_answer") or (screenID == "right_joke")) then
		if (doorStatus) then
			local convoTemplate = LuaConversationTemplate(pConvTemplate)
			local successScreen = convoTemplate:getScreen("success")
			local screenObject = LuaConversationScreen(successScreen)
			pConvScreen = screenObject:cloneScreen()
		else
			pConvScreen = screen:cloneScreen()
			local clonedConversation = LuaConversationScreen(pConvScreen)
			if (not guessedColor) then
				clonedConversation:addOption("@celebrity/lok_hacker:codec_2", "color_codes")
			end
			if (not guessedMath) then
				clonedConversation:addOption("@celebrity/lok_hacker:rewire_2", "math_problem")
			end
			if (not guessedJoke) then
				clonedConversation:addOption("@celebrity/lok_hacker:defender_2", "joke")
			end
		end
	end
	if (screenID == "help_me_hack") then
		-- Reset questions if player didnt previously answer them all
		self.themePark:removeState(CreatureObject(pPlayer), 1, "nym_theme_park_hackerNpc")
		self.themePark:removeState(CreatureObject(pPlayer), 2, "nym_theme_park_hackerNpc")
		self.themePark:removeState(CreatureObject(pPlayer), 4, "nym_theme_park_hackerNpc")
		self.themePark:removeState(CreatureObject(pPlayer), 8, "nym_theme_park_hackerNpc")
	end
	return pConvScreen
end

function NymConvoHandler:cellPlayerPermissionsObserver(pCreature, pCreature2)
	if SceneObject(pCreature):isCreatureObject() then
		for i = 1, # self.themePark.permissionMap, 1 do
			self.themePark:setCellPermissions(self.themePark.permissionMap[i], pCreature)
		end
	end
	return 0
end

function NymConvoHandler:runBeremaScreenHandlers(pConvTemplate, pPlayer, pNpc, selectedOption, pConvScreen)
	local screen = LuaConversationScreen(pConvScreen)
	local screenID = screen:getScreenID()

	local objectID = CreatureObject(pPlayer):getObjectID()
	local pConvScreen = screen:cloneScreen()
	local clonedConversation = LuaConversationScreen(pConvScreen)
	local playerCredits = CreatureObject(pPlayer):getCashCredits()
	local curBet = self:readObjectData(objectID, "curBet", "nym_gambler")
	if screenID == "begin_game_5" or screenID == "begin_game_10" or screenID == "begin_game_50" then
		local pickedCard = getRandomNumber(1,3)
		if pickedCard == 1 then
			clonedConversation:addOption("@celebrity/lok_gambler:thermal_detonator", "tie")
			clonedConversation:addOption("@celebrity/lok_gambler:sarlacc", "you_lose_s")
			if CreatureObject(pPlayer):hasScreenPlayState(2, "nym_theme_park_nymNpc") and not CreatureObject(pPlayer):hasScreenPlayState(16, "nym_theme_park_nymNpc") then
				clonedConversation:addOption("@celebrity/lok_gambler:bounty_hunter", "begin_game_five_wins")
			else
				clonedConversation:addOption("@celebrity/lok_gambler:bounty_hunter", "you_win_bh")
			end
		elseif pickedCard == 2 then
			if CreatureObject(pPlayer):hasScreenPlayState(2, "nym_theme_park_nymNpc") and not CreatureObject(pPlayer):hasScreenPlayState(16, "nym_theme_park_nymNpc") then
				clonedConversation:addOption("@celebrity/lok_gambler:thermal_detonator", "begin_game_five_wins")
			else
				clonedConversation:addOption("@celebrity/lok_gambler:thermal_detonator", "you_win_td")
			end
			clonedConversation:addOption("@celebrity/lok_gambler:sarlacc", "tie")
			clonedConversation:addOption("@celebrity/lok_gambler:bounty_hunter", "you_lose_bh")
		else
			clonedConversation:addOption("@celebrity/lok_gambler:thermal_detonator", "you_lose_td")
			if CreatureObject(pPlayer):hasScreenPlayState(2, "nym_theme_park_nymNpc") and not CreatureObject(pPlayer):hasScreenPlayState(16, "nym_theme_park_nymNpc") then
				clonedConversation:addOption("@celebrity/lok_gambler:sarlacc", "begin_game_five_wins")
			else
				clonedConversation:addOption("@celebrity/lok_gambler:sarlacc", "you_win_s")
			end
			clonedConversation:addOption("@celebrity/lok_gambler:bounty_hunter", "tie")
		end
	end
	if screenID == "you_win_s" or screenID == "you_win_bh" or screenID == "you_win_td" or screenID == "begin_game_five_wins" then
		CreatureObject(pPlayer):sendSystemMessage("@theme_park_nym/messages:card_winner")
		CreatureObject(pPlayer):addCashCredits(curBet * 2, false)
		if (screenID ~= "begin_game_five_wins") then
			clonedConversation:addOption("@celebrity/lok_gambler:play_again", "bet_how_much")
			clonedConversation:addOption("@celebrity/lok_gambler:leaving", "good_luck")
		end
	end
	if screenID == "you_lose_s" or screenID == "you_lose_td" or screenID == "you_lose_bh" or screenID == "tie" then
		if (screenID == "tie") then
			CreatureObject(pPlayer):sendSystemMessage("@theme_park_nym/messages:card_tie")
			CreatureObject(pPlayer):addCashCredits(curBet, false)
		else
			CreatureObject(pPlayer):sendSystemMessage("@theme_park_nym/messages:card_loser")
		end
		clonedConversation:addOption("@celebrity/lok_gambler:play_again", "bet_how_much")
		clonedConversation:addOption("@celebrity/lok_gambler:leaving", "good_luck")
	end
	if screenID == "begin_game_5" then
		self:writeObjectData(objectID, "curBet", 5, "nym_gambler")
		CreatureObject(pPlayer):subtractCashCredits(5)
	elseif screenID == "begin_game_10" then
		self:writeObjectData(objectID, "curBet", 10, "nym_gambler")
		CreatureObject(pPlayer):subtractCashCredits(10)
	elseif screenID == "begin_game_50" then
		self:writeObjectData(objectID, "curBet", 50, "nym_gambler")
		CreatureObject(pPlayer):subtractCashCredits(50)
	elseif screenID == "bet_how_much" then
		if (playerCredits >= 5) then
			clonedConversation:addOption("@celebrity/lok_gambler:bet_made_5", "begin_game_5")
		end
		if (playerCredits >= 10) then
			clonedConversation:addOption("@celebrity/lok_gambler:bet_made_10", "begin_game_10")
		end
		if (playerCredits >= 50) then
			clonedConversation:addOption("@celebrity/lok_gambler:bet_made_50", "begin_game_50")
		end
	end
	return pConvScreen
end

function NymConvoHandler:getInitialScreen(pPlayer, pNpc, pConvTemplate)
	local customName = SceneObject(pNpc):getCustomObjectName()
	local objectName = SceneObject(pNpc):getObjectName()

	if (customName == "Hacker") then
		createObserver(SCREENPLAYSTATECHANGED, self.themePark.className, "cellPlayerPermissionsObserver", pPlayer)
		return self:getInitialHackerScreen(pPlayer, pNpc, pConvTemplate)
	elseif (objectName == "nym") then
		return self:getInitialNymScreen(pPlayer, pNpc, pConvTemplate)
	elseif (customName == "Choster (Retired Engineer)") then
		return self:getInitialChosterScreen(pPlayer, pNpc, pConvTemplate)
	elseif (objectName == "jinkins") then
		return self:getInitialJinkinsScreen(pPlayer, pNpc, pConvTemplate)
	elseif (objectName == "kole") then
		return self:getInitialKoleScreen(pPlayer, pNpc, pConvTemplate)
	elseif (customName == "Berema") then
		return self:getInitialBeremaScreen(pPlayer, pNpc, pConvTemplate)
	elseif (customName == "Sergeant Moore (Retired)") then
		return self:getInitialMooreScreen(pPlayer, pNpc, pConvTemplate)
	end
end

function NymConvoHandler:getInitialHackerScreen(pPlayer, pNpc, pConvTemplate)
	local convoTemplate = LuaConversationTemplate(pConvTemplate)
	-- Hacker states: 1= guessed color, 2 = guessed math, 4 = guessed joke, 8 = door opened
	if (CreatureObject(pPlayer):hasScreenPlayState(8, "nym_theme_park_hackerNpc")) then
		return convoTemplate:getScreen("doors_open")
	end
	return convoTemplate:getScreen("help_me_hack")
end

function NymConvoHandler:getInitialNymScreen(pPlayer, pNpc, pConvTemplate)
	local convoTemplate = LuaConversationTemplate(pConvTemplate)
	-- Nym states: 1 = initial talk, 2 = sent to berema, 4 = turned in grenade, 8 =turned in data, 16 = all completed
	if (not CreatureObject(pPlayer):hasScreenPlayState(1, "nym_theme_park_nymNpc")) then
		return convoTemplate:getScreen("first_time_hello")
	elseif (CreatureObject(pPlayer):hasScreenPlayState(4, "nym_theme_park_nymNpc") and not CreatureObject(pPlayer):hasScreenPlayState(8, "nym_theme_park_nymNpc")) then
		return convoTemplate:getScreen("wheres_drive")
	elseif (not CreatureObject(pPlayer):hasScreenPlayState(4, "nym_theme_park_nymNpc") and CreatureObject(pPlayer):hasScreenPlayState(8, "nym_theme_park_nymNpc")) then
		return convoTemplate:getScreen("wheres_imggcu")
	elseif (CreatureObject(pPlayer):hasScreenPlayState(4, "nym_theme_park_nymNpc") and CreatureObject(pPlayer):hasScreenPlayState(8, "nym_theme_park_nymNpc") and not CreatureObject(pPlayer):hasScreenPlayState(16, "nym_theme_park_nymNpc")) then
		return convoTemplate:getScreen("youre_the_best")
	elseif (CreatureObject(pPlayer):hasScreenPlayState(16, "nym_theme_park_nymNpc")) then
		return convoTemplate:getScreen("youre_done")
	end
	return convoTemplate:getScreen("hello_again")
end

function NymConvoHandler:getInitialChosterScreen(pPlayer, pNpc, pConvTemplate)
	local convoTemplate = LuaConversationTemplate(pConvTemplate)
	-- Choster states: 1 = Sent to talk to choster, 2 = has talked to choster
	if (CreatureObject(pPlayer):hasScreenPlayState(2, "nym_theme_park_chosterNpc")) then
		return convoTemplate:getScreen("more_questions")
	end
	return convoTemplate:getScreen("hello")
end

function NymConvoHandler:getInitialJinkinsScreen(pPlayer, pNpc, pConvTemplate)
	local convoTemplate = LuaConversationTemplate(pConvTemplate)
	-- Jinkins states: 1 = started quest, 2 = completed quest
	if (CreatureObject(pPlayer):hasScreenPlayState(2, "nym_theme_park_jinkinsNpc")) then
		return convoTemplate:getScreen("good_work")
	elseif (CreatureObject(pPlayer):hasScreenPlayState(1, "nym_theme_park_jinkinsNpc")) then
		return convoTemplate:getScreen("you_got_memory")
	end
	return convoTemplate:getScreen("first_time_hello")
end

function NymConvoHandler:getInitialKoleScreen(pPlayer, pNpc, pConvTemplate)
	local convoTemplate = LuaConversationTemplate(pConvTemplate)
	-- Kole states: 1 = started quest, 2 = completed quest
	if (CreatureObject(pPlayer):hasScreenPlayState(2, "nym_theme_park_koleNpc")) then
		return convoTemplate:getScreen("good_work")
	elseif (CreatureObject(pPlayer):hasScreenPlayState(1, "nym_theme_park_koleNpc")) then
		return convoTemplate:getScreen("bring_gas")
	end
	return convoTemplate:getScreen("first_time_hello")
end

function NymConvoHandler:getInitialBeremaScreen(pPlayer, pNpc, pConvTemplate)
	local convoTemplate = LuaConversationTemplate(pConvTemplate)
	if (CreatureObject(pPlayer):hasScreenPlayState(2, "nym_theme_park_nymNpc") and not CreatureObject(pPlayer):hasScreenPlayState(16, "nym_theme_park_nymNpc")) then
		return convoTemplate:getScreen("nym_sent_you")
	end
	return convoTemplate:getScreen("play_game")
end

function NymConvoHandler:getInitialMooreScreen(pPlayer, pNpc, pConvTemplate)
	local convoTemplate = LuaConversationTemplate(pConvTemplate)
	return convoTemplate:getScreen("leave_me_alone")
end

function NymConvoHandler:writeObjectData(objectID, key, value, questGiver)
	writeData(objectID .. ":" .. questGiver .. ":" .. key, value)
end

function NymConvoHandler:readObjectData(objectID, key, questGiver)
	return readData(objectID .. ":" .. questGiver .. ":" .. key)
end

function NymConvoHandler:deleteObjectData(objectID, key, questGiver)
	deleteData(objectID .. ":" .. questGiver .. ":" .. key)
end
