amarent_loren_convo_handler = conv_handler:new {}

local questCrc = 3408891851 --CRC of "quest/c_darndroid1"
local imperialCrc = 3679112276 --CRC of "imperial"

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

	if (PlayerObject(pGhost):isJournalQuestTaskActive(questCrc, 3) == true) then
		return convoTemplate:getScreen("first_screen")
	elseif (PlayerObject(pGhost):isJournalQuestTaskActive(questCrc, 4) == true) then
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

	if (screenID == "life_worth" or screenID == "come_on" or screenID == "forgiven" or screenID == "bribe_credits") then
		DarnDroid1:giveShipTask(pPlayer, shipTask[screenID])
	end

	if (screenID == "need_waypoint") then
		DarnDroid1:giveShipWaypoint(pPlayer)
	end

	if (screenID == "sent_me") then
		local rank = CreatureObject(pPlayer):getFactionRank()
		local factionCrc = TangibleObject(pPlayer):getFaction()

		if (factionCrc == imperialCrc and rank > 0) then
	        clonedConversation:addOption("@conversation/c_ddroid_amarent:s_285","my_influence") --I'm sure you can make time for someone of my influence.
		end
		clonedConversation:addOption("@conversation/c_ddroid_amarent:s_301","need_info") --I need information about a ship that may be lost.
	end

	if (screenID == "need_info") then
		if (CreatureObject(pPlayer):getCashCredits() >= 1000) then
			clonedConversation:addOption("@conversation/c_ddroid_amarent:s_305","bribe_credits") --Would these 1000 credits show that I'm a member of the Imperial Transit Authority?
		end
		clonedConversation:addOption("@conversation/c_ddroid_amarent:s_309","life_worth") --Is your life really worth a silly rule like that?
	end

	return pConvScreen
end