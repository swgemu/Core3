amarent_loren_convo_handler = conv_handler:new {}

local shipTask = { --How did the player get Amarent to talk?
	bribe_credits = "bribe",
	life_worth = "threaten",
	come_on = "imperial",
	forgiven = "imperial"
}

function amarent_loren_convo_handler:getInitialScreen(pPlayer, pNpc, pConvTemplate)
	if (pPlayer == nil) then
		return
	end

	local convoTemplate = LuaConversationTemplate(pConvTemplate)

	local pGhost = CreatureObject(pPlayer):getPlayerObject()

	if (pGhost == nil) then
		return
	end

	if (PlayerObject(pGhost):isJournalQuestTaskActive(DarnDroid1.questCrc, DarnDroid1.TASK_TALKTOAMARENT)) then
		return convoTemplate:getScreen("first_screen")
	elseif (PlayerObject(pGhost):isJournalQuestTaskActive(DarnDroid1.questCrc, DarnDroid1.TASK_FINDSHIP)) then
		return convoTemplate:getScreen("more_help")
	else
		return convoTemplate:getScreen("not_ready")
	end
end

function amarent_loren_convo_handler:runScreenHandlers(pConvTemplate, pPlayer, pNpc, selectedOption, pConvScreen)
	if (pPlayer == nil) then
		return
	end

	local screen = LuaConversationScreen(pConvScreen)
	local screenID = screen:getScreenID()

	local pConvScreen = screen:cloneScreen()
	local clonedConversation = LuaConversationScreen(pConvScreen)

	local pGhost = CreatureObject(pPlayer):getPlayerObject()

	if (pGhost == nil) then
		return
	end

	if (screenID == "first_screen") then
		PlayerObject(pGhost):completeJournalQuestTask(DarnDroid1.questCrc, DarnDroid1.TASK_TALKTOAMARENT, true)
	elseif (screenID == "life_worth" or screenID == "come_on" or screenID == "forgiven" or screenID == "bribe_credits") then
		if (screenID == "life_worth") then
			PlayerObject(pGhost):activateJournalQuestTask(DarnDroid1.questCrc, DarnDroid1.TASK_INTIMIDATEDAMARENT, false)
		elseif (screenID == "bribe_credits") then
			PlayerObject(pGhost):activateJournalQuestTask(DarnDroid1.questCrc, DarnDroid1.TASK_BRIBEDAMARENT, false)
		end

		DarnDroid1:giveShipTask(pPlayer, shipTask[screenID])
	elseif (screenID == "need_waypoint") then
		DarnDroid1:giveWaypoint(pPlayer, "talus", "Talus Crash Site", -2368, 2043)
	elseif (screenID == "sent_me") then
		local rank = CreatureObject(pPlayer):getFactionRank()
		local factionCrc = TangibleObject(pPlayer):getFaction()

		if (factionCrc == DarnDroid1.imperialCrc and rank > 0) then
			clonedConversation:addOption("@conversation/c_ddroid_amarent:s_285","my_influence") --I'm sure you can make time for someone of my influence.
		end

		clonedConversation:addOption("@conversation/c_ddroid_amarent:s_301","need_info") --I need information about a ship that may be lost.
	elseif (screenID == "need_info") then
		if (CreatureObject(pPlayer):getCashCredits() >= 1000) then
			clonedConversation:addOption("@conversation/c_ddroid_amarent:s_305","bribe_credits") --Would these 1000 credits show that I'm a member of the Imperial Transit Authority?
		end
		clonedConversation:addOption("@conversation/c_ddroid_amarent:s_309","life_worth") --Is your life really worth a silly rule like that?
	end

	return pConvScreen
end