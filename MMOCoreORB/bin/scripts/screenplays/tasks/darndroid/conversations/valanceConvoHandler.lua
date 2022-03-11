valance_serth_convo_handler = conv_handler:new {}

local questCrc = 3408891851 --CRC of "quest/c_darndroid1"

function valance_serth_convo_handler:getInitialScreen(pPlayer, pNpc, pConvTemplate)
	if (pPlayer == nil) then
		return
	end

	local convoTemplate = LuaConversationTemplate(pConvTemplate)

	local pGhost = CreatureObject(pPlayer):getPlayerObject()

	if (pGhost == nil) then
		return
	end

    if (CreatureObject(pPlayer):isInCombat() or CreatureObject(pNpc):isInCombat()) then
        return
    end

	if (PlayerObject(pGhost):isJournalQuestTaskActive(questCrc, 5) == true and
		PlayerObject(pGhost):isJournalQuestActive(questCrc) == true) then
		return convoTemplate:getScreen("first_screen")
	else
		return convoTemplate:getScreen("not_ready")
	end
end

function valance_serth_convo_handler:runScreenHandlers(pConvTemplate, pPlayer, pNpc, selectedOption, pConvScreen)
	if (pPlayer == nil) then
		return
	end

	local screen = LuaConversationScreen(pConvScreen)
	local screenID = screen:getScreenID()
	local convoTemplate = LuaConversationTemplate(pConvTemplate)

	local pGhost = CreatureObject(pPlayer):getPlayerObject()

	if (pGhost == nil) then
		return
	end

    if (screenID == "happy_help" or screenID == "expect_return") then
		if (DarnDroid1:completeQuest(pPlayer) == false) then
			return convoTemplate:getScreen("inventory_full")
		end
	end

	return pConvScreen
end