valance_serth_convo_handler = conv_handler:new {}

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

	if (DarnDroid2:isPlayerOnQuest1(pGhost)) then
		return convoTemplate:getScreen("first_screen")
	elseif (DarnDroid2:isPlayerReadyForQuest2(pGhost)) then
		return convoTemplate:getScreen("need_help")
	elseif (DarnDroid2:isPlayerOnQuest2Part1(pGhost)) then
		return convoTemplate:getScreen("on_part1")
	elseif (DarnDroid2:isPlayerDoneQuest2Part2(pGhost)) then
		return convoTemplate:getScreen("completed_part2")
	elseif (DarnDroid2:isPlayerFailedSpaceMission(pGhost)) then
		return convoTemplate:getScreen("failed_space")
	elseif (DarnDroid2:isPlayerDoneSpaceMission(pGhost)) then
		return convoTemplate:getScreen("completed_space")
	elseif (DarnDroid2:isPlayerCompletedAll(pGhost)) then
		return convoTemplate:getScreen("completed_all")
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
		if (DarnDroid1:completeQuest(pPlayer)) then
			return convoTemplate:getScreen("inventory_full")
		end
	elseif (screenID == "ill_help" or screenID == "will_help") then
		DarnDroid2:giveQuest(pPlayer)
	elseif (screenID == "tell_more") then
		DarnDroid2:giveSpaceMission(pPlayer)
	elseif (screenID == "do_that") then
		DarnDroid2:giveMemWipeTask(pPlayer)
	end

	return pConvScreen
end