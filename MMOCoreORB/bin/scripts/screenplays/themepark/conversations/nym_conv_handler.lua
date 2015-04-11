local ObjectManager = require("managers.object.object_manager")

NymConvoHandler = Object:new {
	themePark = nil
}

function NymConvoHandler:setThemePark(themeParkNew)
	self.themePark = themeParkNew
end

function NymConvoHandler:runScreenHandlers(conversationTemplate, conversingPlayer, conversingNPC, selectedOption, conversationScreen)
	return ObjectManager.withSceneObject(conversingNPC, function(npcObject)
		if (npcObject:getCustomObjectName() == "Hacker") then
			return self:runHackerScreenHandlers(conversationTemplate, conversingPlayer, conversingNPC, selectedOption, conversationScreen)
		elseif (npcObject:getObjectName() == "nym") then
			return self:runNymScreenHandlers(conversationTemplate, conversingPlayer, conversingNPC, selectedOption, conversationScreen)
		elseif (npcObject:getCustomObjectName() == "Choster (Retired Engineer)") then
			return self:runChosterScreenHandlers(conversationTemplate, conversingPlayer, conversingNPC, selectedOption, conversationScreen)
		elseif (npcObject:getObjectName() == "jinkins") then
			return self:runJinkinsScreenHandlers(conversationTemplate, conversingPlayer, conversingNPC, selectedOption, conversationScreen)
		elseif (npcObject:getObjectName() == "kole") then
			return self:runKoleScreenHandlers(conversationTemplate, conversingPlayer, conversingNPC, selectedOption, conversationScreen)
		elseif (npcObject:getCustomObjectName() == "Berema") then
			return self:runBeremaScreenHandlers(conversationTemplate, conversingPlayer, conversingNPC, selectedOption, conversationScreen)
		elseif (npcObject:getCustomObjectName() == "Sergeant Moore (Retired)") then
			return self:runMooreScreenHandlers(conversationTemplate, conversingPlayer, conversingNPC, selectedOption, conversationScreen)
		end
		return conversationScreen
	end)
end

function NymConvoHandler:runNymScreenHandlers(conversationTemplate, conversingPlayer, conversingNPC, selectedOption, conversationScreen)
	local screen = LuaConversationScreen(conversationScreen)

	local screenID = screen:getScreenID()

	return ObjectManager.withCreatureAndPlayerObject(conversingPlayer, function(player,playerObject)
		local conversationScreen = screen:cloneScreen()
		local clonedConversation = LuaConversationScreen(conversationScreen)
		if (screenID == "first_time_hello" or screenID == "yo_es_nym") then
			if (not player:hasScreenPlayState(2, "nym_theme_park_jinkinsNpc")) or (not player:hasScreenPlayState(2, "nym_theme_park_koleNpc")) then
				clonedConversation:addOption("@celebrity/nym:tell_me_quest", "help_others")
			else
				clonedConversation:addOption("@celebrity/nym:tell_me_quest", "quest_info")
			end
		elseif (screenID == "go_lab") then
			local oldWaypointID = tonumber(getQuestStatus(player:getObjectID() .. ":nymFacilityWaypointID"))
			if (oldWaypointID ~= 0) then
				playerObject:removeWaypoint(oldWaypointID, true)
				removeQuestStatus(player:getObjectID() .. ":nymFacilityWaypointID")
			end
			local waypointID = playerObject:addWaypoint("lok", "Imperial Research Facility", "Imperial Research Facility", ThemeParkNym.waypointMap.researchfacility.x, ThemeParkNym.waypointMap.researchfacility.y, WAYPOINT_COLOR_PURPLE, true, true, 0)
			setQuestStatus(player:getObjectID() .. ":nymFacilityWaypointID", waypointID)
			self.themePark:setState(player, 1, "nym_theme_park_nymNpc")
		elseif (screenID == "go_to_officer") then
			local oldWaypointID = tonumber(getQuestStatus(player:getObjectID() .. ":nymGamblerWaypointID"))
			if (oldWaypointID ~= 0) then
				playerObject:removeWaypoint(oldWaypointID, true)
				removeQuestStatus(player:getObjectID() .. ":nymGamblerWaypointID")
			end
			local waypointID = playerObject:addWaypoint("lok", "Nym's Informant", "Nym's Informant", ThemeParkNym.waypointMap.gambler.x, ThemeParkNym.waypointMap.gambler.y, WAYPOINT_COLOR_PURPLE, true, true, 0)
			setQuestStatus(player:getObjectID() .. ":nymGamblerWaypointID", waypointID)
			self.themePark:setState(player, 2, "nym_theme_park_nymNpc")
		end
		return conversationScreen
	end)
end

function NymConvoHandler:runChosterScreenHandlers(conversationTemplate, conversingPlayer, conversingNPC, selectedOption, conversationScreen)
	local screen = LuaConversationScreen(conversationScreen)
	local screenID = screen:getScreenID()
	return ObjectManager.withCreatureAndPlayerObject(conversingPlayer, function(player,playerObject)
		local conversationScreen = screen:cloneScreen()
		local clonedConversation = LuaConversationScreen(conversationScreen)
		if (screenID == "hello") then
			if (player:hasScreenPlayState(1, "nym_theme_park_chosterNpc")) then
				clonedConversation:addOption("@celebrity/lok_engineer:who_are_you", "just_a_guy")
			else
				clonedConversation:addOption("@celebrity/lok_engineer:who_are_you_2", "go_away_dude")
			end
		end
		return conversationScreen
	end)
end

function NymConvoHandler:runJinkinsScreenHandlers(conversationTemplate, conversingPlayer, conversingNPC, selectedOption, conversationScreen)
	local screen = LuaConversationScreen(conversationScreen)
	local screenID = screen:getScreenID()
	return ObjectManager.withCreatureAndPlayerObject(conversingPlayer, function(player,playerObject)
		local conversationScreen = screen:cloneScreen()
		local clonedConversation = LuaConversationScreen(conversationScreen)
		if (screenID == "heres_droid_memory") then
			local oldWaypointID = tonumber(getQuestStatus(player:getObjectID() .. ":nymPirateCaveWaypointID"))
			if (oldWaypointID ~= 0) then
				playerObject:removeWaypoint(oldWaypointID, true)
				removeQuestStatus(player:getObjectID() .. ":nymPirateCaveWaypointID")
			end
			local waypointID = playerObject:addWaypoint("lok", "Sulfur Lake Pirate Hideout", "", ThemeParkNym.waypointMap.piratecave.x, ThemeParkNym.waypointMap.piratecave.y, WAYPOINT_COLOR_PURPLE, true, true, 0)
			setQuestStatus(player:getObjectID() .. ":nymPirateCaveWaypointID", waypointID)
			self.themePark:setState(player, 1, "nym_theme_park_jinkinsNpc")
		elseif (screenID == "heres_the_guy") then
			local oldWaypointID = tonumber(getQuestStatus(player:getObjectID() .. ":nymHermitWaypointID"))
			if (oldWaypointID ~= 0) then
				playerObject:removeWaypoint(oldWaypointID, true)
				removeQuestStatus(player:getObjectID() .. ":nymHermitWaypointID")
			end
			local waypointID = playerObject:addWaypoint("lok", "Hermit", "", ThemeParkNym.waypointMap.choster.x, ThemeParkNym.waypointMap.choster.y, WAYPOINT_COLOR_PURPLE, true, true, 0)
			setQuestStatus(player:getObjectID() .. ":nymHermitWaypointID", waypointID)
			self.themePark:setState(player, 1, "nym_theme_park_chosterNpc")
		elseif (screenID == "good_work" and clonedConversation:getOptionCount() == 0) then
			if (player:hasScreenPlayState(2, "nym_theme_park_koleNpc")) then
				clonedConversation:addOption("@celebrity/jinkins:what_now", "talk_to_nym")
			else
				clonedConversation:addOption("@celebrity/jinkins:what_now", "talk_to_kole")
			end
			clonedConversation:addOption("@celebrity/jinkins:see_ya", "good_bye")
		end
		return conversationScreen
	end)
end

function NymConvoHandler:runKoleScreenHandlers(conversationTemplate, conversingPlayer, conversingNPC, selectedOption, conversationScreen)
	local screen = LuaConversationScreen(conversationScreen)
	local screenID = screen:getScreenID()
	return ObjectManager.withCreatureAndPlayerObject(conversingPlayer, function(player,playerObject)
		local conversationScreen = screen:cloneScreen()
		local clonedConversation = LuaConversationScreen(conversationScreen)
		if (screenID == "first_time_hello" or screenID == "jinkins_is_friend" or screenID == "im_kole" or screenID == "nym_is_chief") then
			if (not player:hasScreenPlayState(2, "nym_theme_park_jinkinsNpc")) then
				clonedConversation:addOption("@celebrity/kole:tell_me_quest", "quest_tease")
			else
				clonedConversation:addOption("@celebrity/kole:tell_me_quest", "quest_info")
			end
		elseif (screenID == "here_is_gas") then
			local oldWaypointID = tonumber(getQuestStatus(player:getObjectID() .. ":nymGasMineWaypointID"))
			if (oldWaypointID ~= 0) then
				playerObject:removeWaypoint(oldWaypointID, true)
				removeQuestStatus(player:getObjectID() .. ":nymGasMineWaypointID")
			end
			local waypointID = playerObject:addWaypoint("lok", "Imperial Gas Mine", "", ThemeParkNym.waypointMap.gasmine.x, ThemeParkNym.waypointMap.gasmine.y, WAYPOINT_COLOR_PURPLE, true, true, 0)
			setQuestStatus(player:getObjectID() .. ":nymGasMineWaypointID", waypointID)
			self.themePark:setState(player, 1, "nym_theme_park_koleNpc")
		elseif (screenID == "here_is_imperial") then
			local oldWaypointID = tonumber(getQuestStatus(player:getObjectID() .. ":nymBribeWaypointID"))
			if (oldWaypointID ~= 0) then
				playerObject:removeWaypoint(oldWaypointID, true)
				removeQuestStatus(player:getObjectID() .. ":nymBribeWaypointID")
			end
			local waypointID = playerObject:addWaypoint("lok", "Sergeant Moore", "", ThemeParkNym.waypointMap.imperialbribe.x, ThemeParkNym.waypointMap.imperialbribe.y, WAYPOINT_COLOR_PURPLE, true, true, 0)
			setQuestStatus(player:getObjectID() .. ":nymBribeWaypointID", waypointID)
			self.themePark:setState(player, 1, "nym_theme_park_mooreNpc")
		end
		return conversationScreen
	end)
end

function NymConvoHandler:runMooreScreenHandlers(conversationTemplate, conversingPlayer, conversingNPC, selectedOption, conversationScreen)
	local screen = LuaConversationScreen(conversationScreen)
	local screenID = screen:getScreenID()
	return ObjectManager.withCreatureObject(conversingPlayer, function(player)
		local conversationScreen = screen:cloneScreen()
		local clonedConversation = LuaConversationScreen(conversationScreen)
		local playerCredits = player:getCashCredits()
		if (screenID == "leave_me_alone") then
			if (not player:hasScreenPlayState(1, "nym_theme_park_mooreNpc")) then
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
			player:subtractCashCredits(50)
		elseif (screenID == "the_good_stuff") then
			player:subtractCashCredits(100)
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
			player:subtractCashCredits(100)
		end
		if (screenID ~= "leave_me_alone" and screenID ~= "what_you_got") then
			clonedConversation:addOption("@celebrity/imperial_bribe:end_convo", "thats_all")
		end
		return conversationScreen
	end)
end

function NymConvoHandler:runHackerScreenHandlers(conversationTemplate, conversingPlayer, conversingNPC, selectedOption, conversationScreen)
	local screen = LuaConversationScreen(conversationScreen)
	local screenID = screen:getScreenID()

	return ObjectManager.withCreatureAndPlayerObject(conversingPlayer, function(player,playerObject)
		-- Hacker states: 1= guessed color, 2 = guessed math, 4 = guessed joke, 8 = door opened
		if (screenID == "right_color") then
			self.themePark:setState(player, 1, "nym_theme_park_hackerNpc")
		elseif (screenID == "right_answer") then
			self.themePark:setState(player, 2, "nym_theme_park_hackerNpc")
		elseif (screenID == "right_joke") then
			self.themePark:setState(player, 4, "nym_theme_park_hackerNpc")
		end
		local guessedColor = player:hasScreenPlayState(1, "nym_theme_park_hackerNpc")
		local guessedMath = player:hasScreenPlayState(2, "nym_theme_park_hackerNpc")
		local guessedJoke = player:hasScreenPlayState(4, "nym_theme_park_hackerNpc")
		local doorStatus = player:hasScreenPlayState(8, "nym_theme_park_hackerNpc")
		if (guessedColor and guessedMath and guessedJoke and not doorStatus) then
			self.themePark:setState(player, 8, "nym_theme_park_hackerNpc")
			playerObject:addPermissionGroup("NymPirateCave", true)
		end
		doorStatus = player:hasScreenPlayState(8, "nym_theme_park_hackerNpc")
		if ((screenID == "right_color") or (screenID == "right_answer") or (screenID == "right_joke")) then
			if (doorStatus) then
				local convoTemplate = LuaConversationTemplate(conversationTemplate)
				local successScreen = convoTemplate:getScreen("success")
				local screenObject = LuaConversationScreen(successScreen)
				conversationScreen = screenObject:cloneScreen()
			else
				conversationScreen = screen:cloneScreen()
				local clonedConversation = LuaConversationScreen(conversationScreen)
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
			self.themePark:removeState(player, 1, "nym_theme_park_hackerNpc")
			self.themePark:removeState(player, 2, "nym_theme_park_hackerNpc")
			self.themePark:removeState(player, 4, "nym_theme_park_hackerNpc")
			self.themePark:removeState(player, 8, "nym_theme_park_hackerNpc")
		end
		return conversationScreen
	end)
end

function NymConvoHandler:cellPlayerPermissionsObserver(pCreature, pCreature2)
	return ObjectManager.withSceneObject(pCreature, function(creatureSceneObject)
		if creatureSceneObject:isCreatureObject() then
			for i = 1, # self.themePark.permissionMap, 1 do
				self.themePark:setCellPermissions(self.themePark.permissionMap[i], pCreature)
			end
		end
		return 0
	end)
end

function NymConvoHandler:runBeremaScreenHandlers(conversationTemplate, conversingPlayer, conversingNPC, selectedOption, conversationScreen)
	local screen = LuaConversationScreen(conversationScreen)
	local screenID = screen:getScreenID()
	return ObjectManager.withCreatureObject(conversingPlayer, function(player)
		local objectID = player:getObjectID()
		local conversationScreen = screen:cloneScreen()
		local clonedConversation = LuaConversationScreen(conversationScreen)
		local playerCredits = player:getCashCredits()
		local curBet = self:readObjectData(objectID, "curBet", "nym_gambler")
		if screenID == "begin_game_5" or screenID == "begin_game_10" or screenID == "begin_game_50" then
			local pickedCard = getRandomNumber(1,3)
			if pickedCard == 1 then
				clonedConversation:addOption("@celebrity/lok_gambler:thermal_detonator", "tie")
				clonedConversation:addOption("@celebrity/lok_gambler:sarlacc", "you_lose_s")
				if player:hasScreenPlayState(2, "nym_theme_park_nymNpc") and not player:hasScreenPlayState(16, "nym_theme_park_nymNpc") then
					clonedConversation:addOption("@celebrity/lok_gambler:bounty_hunter", "begin_game_five_wins")
				else
					clonedConversation:addOption("@celebrity/lok_gambler:bounty_hunter", "you_win_bh")
				end
			elseif pickedCard == 2 then
				if player:hasScreenPlayState(2, "nym_theme_park_nymNpc") and not player:hasScreenPlayState(16, "nym_theme_park_nymNpc") then
					clonedConversation:addOption("@celebrity/lok_gambler:thermal_detonator", "begin_game_five_wins")
				else
					clonedConversation:addOption("@celebrity/lok_gambler:thermal_detonator", "you_win_td")
				end
				clonedConversation:addOption("@celebrity/lok_gambler:sarlacc", "tie")
				clonedConversation:addOption("@celebrity/lok_gambler:bounty_hunter", "you_lose_bh")
			else
				clonedConversation:addOption("@celebrity/lok_gambler:thermal_detonator", "you_lose_td")
				if player:hasScreenPlayState(2, "nym_theme_park_nymNpc") and not player:hasScreenPlayState(16, "nym_theme_park_nymNpc") then
					clonedConversation:addOption("@celebrity/lok_gambler:sarlacc", "begin_game_five_wins")
				else
					clonedConversation:addOption("@celebrity/lok_gambler:sarlacc", "you_win_s")
				end
				clonedConversation:addOption("@celebrity/lok_gambler:bounty_hunter", "tie")
			end
		end
		if screenID == "you_win_s" or screenID == "you_win_bh" or screenID == "you_win_td" or screenID == "begin_game_five_wins" then
			player:sendSystemMessage("@theme_park_nym/messages:card_winner")
			player:addCashCredits(curBet * 2, false)
			if (screenID ~= "begin_game_five_wins") then
				clonedConversation:addOption("@celebrity/lok_gambler:play_again", "bet_how_much")
				clonedConversation:addOption("@celebrity/lok_gambler:leaving", "good_luck")
			end
		end
		if screenID == "you_lose_s" or screenID == "you_lose_td" or screenID == "you_lose_bh" or screenID == "tie" then
			if (screenID == "tie") then
				player:sendSystemMessage("@theme_park_nym/messages:card_tie")
				player:addCashCredits(curBet, false)
			else
				player:sendSystemMessage("@theme_park_nym/messages:card_loser")
			end
			clonedConversation:addOption("@celebrity/lok_gambler:play_again", "bet_how_much")
			clonedConversation:addOption("@celebrity/lok_gambler:leaving", "good_luck")
		end
		if screenID == "begin_game_5" then
			self:writeObjectData(objectID, "curBet", 5, "nym_gambler")
			player:subtractCashCredits(5)
		elseif screenID == "begin_game_10" then
			self:writeObjectData(objectID, "curBet", 10, "nym_gambler")
			player:subtractCashCredits(10)
		elseif screenID == "begin_game_50" then
			self:writeObjectData(objectID, "curBet", 50, "nym_gambler")
			player:subtractCashCredits(50)
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
		return conversationScreen
	end)
end

function NymConvoHandler:getInitialScreen(pPlayer, pNpc, pConversationTemplate)
	return ObjectManager.withSceneObject(pNpc, function(npcObject)
		if (npcObject:getCustomObjectName() == "Hacker") then
			createObserver(SCREENPLAYSTATECHANGED, self.themePark.className, "cellPlayerPermissionsObserver", pPlayer)
			return self:getInitialHackerScreen(pPlayer, pNpc, pConversationTemplate)
		elseif (npcObject:getObjectName() == "nym") then
			return self:getInitialNymScreen(pPlayer, pNpc, pConversationTemplate)
		elseif (npcObject:getCustomObjectName() == "Choster (Retired Engineer)") then
			return self:getInitialChosterScreen(pPlayer, pNpc, pConversationTemplate)
		elseif (npcObject:getObjectName() == "jinkins") then
			return self:getInitialJinkinsScreen(pPlayer, pNpc, pConversationTemplate)
		elseif (npcObject:getObjectName() == "kole") then
			return self:getInitialKoleScreen(pPlayer, pNpc, pConversationTemplate)
		elseif (npcObject:getCustomObjectName() == "Berema") then
			return self:getInitialBeremaScreen(pPlayer, pNpc, pConversationTemplate)
		elseif (npcObject:getCustomObjectName() == "Sergeant Moore (Retired)") then
			return self:getInitialMooreScreen(pPlayer, pNpc, pConversationTemplate)
		end
		return 0
	end)
end

function NymConvoHandler:getInitialHackerScreen(pPlayer, pNpc, pConversationTemplate)
	return ObjectManager.withCreatureObject(pPlayer, function(conversingPlayer)
		local convoTemplate = LuaConversationTemplate(pConversationTemplate)
		-- Hacker states: 1= guessed color, 2 = guessed math, 4 = guessed joke, 8 = door opened
		if (conversingPlayer:hasScreenPlayState(8, "nym_theme_park_hackerNpc")) then
			return convoTemplate:getScreen("doors_open")
		end
		return convoTemplate:getScreen("help_me_hack")
	end)
end

function NymConvoHandler:getInitialNymScreen(pPlayer, pNpc, pConversationTemplate)
	return ObjectManager.withCreatureObject(pPlayer, function(conversingPlayer)
		local convoTemplate = LuaConversationTemplate(pConversationTemplate)
		-- Nym states: 1 = initial talk, 2 = sent to berema, 4 = turned in grenade, 8 =turned in data, 16 = all completed
		if (not conversingPlayer:hasScreenPlayState(1, "nym_theme_park_nymNpc")) then
			return convoTemplate:getScreen("first_time_hello")
		elseif (conversingPlayer:hasScreenPlayState(4, "nym_theme_park_nymNpc") and not conversingPlayer:hasScreenPlayState(8, "nym_theme_park_nymNpc")) then
			return convoTemplate:getScreen("wheres_drive")
		elseif (not conversingPlayer:hasScreenPlayState(4, "nym_theme_park_nymNpc") and conversingPlayer:hasScreenPlayState(8, "nym_theme_park_nymNpc")) then
			return convoTemplate:getScreen("wheres_imggcu")
		elseif (conversingPlayer:hasScreenPlayState(4, "nym_theme_park_nymNpc") and conversingPlayer:hasScreenPlayState(8, "nym_theme_park_nymNpc") and not conversingPlayer:hasScreenPlayState(16, "nym_theme_park_nymNpc")) then
			return convoTemplate:getScreen("youre_the_best")
		elseif (conversingPlayer:hasScreenPlayState(16, "nym_theme_park_nymNpc")) then
			return convoTemplate:getScreen("youre_done")
		end
		return convoTemplate:getScreen("hello_again")
	end)
end

function NymConvoHandler:getInitialChosterScreen(pPlayer, pNpc, pConversationTemplate)
	return ObjectManager.withCreatureObject(pPlayer, function(conversingPlayer)
		local convoTemplate = LuaConversationTemplate(pConversationTemplate)
		-- Choster states: 1 = Sent to talk to choster, 2 = has talked to choster
		if (conversingPlayer:hasScreenPlayState(2, "nym_theme_park_chosterNpc")) then
			return convoTemplate:getScreen("more_questions")
		end
		return convoTemplate:getScreen("hello")
	end)
end

function NymConvoHandler:getInitialJinkinsScreen(pPlayer, pNpc, pConversationTemplate)
	return ObjectManager.withCreatureObject(pPlayer, function(conversingPlayer)
		local convoTemplate = LuaConversationTemplate(pConversationTemplate)
		-- Jinkins states: 1 = started quest, 2 = completed quest
		if (conversingPlayer:hasScreenPlayState(2, "nym_theme_park_jinkinsNpc")) then
			return convoTemplate:getScreen("good_work")
		elseif (conversingPlayer:hasScreenPlayState(1, "nym_theme_park_jinkinsNpc")) then
			return convoTemplate:getScreen("you_got_memory")
		end
		return convoTemplate:getScreen("first_time_hello")
	end)
end

function NymConvoHandler:getInitialKoleScreen(pPlayer, pNpc, pConversationTemplate)
	return ObjectManager.withCreatureObject(pPlayer, function(conversingPlayer)
		local convoTemplate = LuaConversationTemplate(pConversationTemplate)
		-- Kole states: 1 = started quest, 2 = completed quest
		if (conversingPlayer:hasScreenPlayState(2, "nym_theme_park_koleNpc")) then
			return convoTemplate:getScreen("good_work")
		elseif (conversingPlayer:hasScreenPlayState(1, "nym_theme_park_koleNpc")) then
			return convoTemplate:getScreen("bring_gas")
		end
		return convoTemplate:getScreen("first_time_hello")
	end)
end

function NymConvoHandler:getInitialBeremaScreen(pPlayer, pNpc, pConversationTemplate)
	return ObjectManager.withCreatureObject(pPlayer, function(conversingPlayer)
		local convoTemplate = LuaConversationTemplate(pConversationTemplate)
		if (conversingPlayer:hasScreenPlayState(2, "nym_theme_park_nymNpc") and not conversingPlayer:hasScreenPlayState(16, "nym_theme_park_nymNpc")) then
			return convoTemplate:getScreen("nym_sent_you")
		end
		return convoTemplate:getScreen("play_game")
	end)
end

function NymConvoHandler:getInitialMooreScreen(pPlayer, pNpc, pConversationTemplate)
	local convoTemplate = LuaConversationTemplate(pConversationTemplate)
	return convoTemplate:getScreen("leave_me_alone")
end

function NymConvoHandler:getNextConversationScreen(pConversationTemplate, pPlayer, selectedOption, pConversingNpc)
	return ObjectManager.withCreatureObject(pPlayer, function(player)
		local pConversationSession = player:getConversationSession()
		local pLastConversationScreen = nil
		if (pConversationSession ~= nil) then
			local conversationSession = LuaConversationSession(pConversationSession)
			pLastConversationScreen = conversationSession:getLastConversationScreen()
		end
		local conversationTemplate = LuaConversationTemplate(pConversationTemplate)
		if (pLastConversationScreen ~= nil) then
			local lastConversationScreen = LuaConversationScreen(pLastConversationScreen)
			local optionLink = lastConversationScreen:getOptionLink(selectedOption)
			return conversationTemplate:getScreen(optionLink)
		end
		return self:getInitialScreen(pPlayer, pConversingNpc, pConversationTemplate)
	end)
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
