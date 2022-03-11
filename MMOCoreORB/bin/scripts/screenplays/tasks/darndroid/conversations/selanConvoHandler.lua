selan_ellison_convo_handler = conv_handler:new {}

local questCrc = 3408891851 --CRC of "quest/c_darndroid1"

function selan_ellison_convo_handler:getInitialScreen(pPlayer, pNpc, pConvTemplate)
	if (pPlayer == nil) then
		return
	end

	local convoTemplate = LuaConversationTemplate(pConvTemplate)

	local pGhost = CreatureObject(pPlayer):getPlayerObject()

	if (pGhost == nil) then
		return
	end

	if (PlayerObject(pGhost):isJournalQuestTaskActive(questCrc, 2) == true) then
		return convoTemplate:getScreen("first_screen")
	else
		return convoTemplate:getScreen("not_ready")
	end
end

function selan_ellison_convo_handler:runScreenHandlers(pConvTemplate, pPlayer, pNpc, selectedOption, pConvScreen)
	if (pPlayer == nil) then
		return
	end

	local screen = LuaConversationScreen(pConvScreen)
	local screenID = screen:getScreenID()

	local pGhost = CreatureObject(pPlayer):getPlayerObject()

	if (pGhost == nil) then
		return
	end

    if (screenID == "appreciate_it") then
		DarnDroid1:giveAmarentTask(pPlayer)
	end

	return pConvScreen
end