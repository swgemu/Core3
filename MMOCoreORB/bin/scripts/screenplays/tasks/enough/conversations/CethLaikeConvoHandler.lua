CethLaikeConvoHandler = conv_handler:new {}

function CethLaikeConvoHandler:runScreenHandlers(pConvTemplate, pPlayer, pNpc, selectedOption, pConvScreen)
	if (pPlayer == nil) then
		return
	end

	local screen = LuaConversationScreen(pConvScreen)
	local screenID = screen:getScreenID()

	local pGhost = CreatureObject(pPlayer):getPlayerObject()

	if (pGhost == nil) then
		return
	end

	return pConvScreen
end

function CethLaikeConvoHandler:getInitialScreen(pPlayer, pNpc, pConvTemplate)
	if (pPlayer == nil) then
		return
	end

	--print("CethLaikeConvoHandler:getInitialScreen -- called ")

	local faction = CreatureObject(pPlayer):getFaction()

	if (faction == FACTIONREBEL) then
		return convoTemplate:getScreen("rebel_greeting")
	elseif (faction == FACTIONNEUTRAL) then
		return convoTemplate:getScreen("neutral_greeting")
	end

	local convoTemplate = LuaConversationTemplate(pConvTemplate)
	local pGhost = CreatureObject(pPlayer):getPlayerObject()

	if (pGhost == nil) then
		return
	end

	local ghost = LuaPlayerObject(pGhost)

		--[[
	removeQuestStatus(SceneObject(pPlayer):getObjectID() .. ":EnoughQuest:FlailKills:")
	removeQuestStatus(SceneObject(pPlayer):getObjectID() .. ":EnoughQuest:BinayreGangSymbols:")

	--- to clear quest
	ghost:clearJournalQuestTask(EnoughQuest.IMPERIAL_CRC, 0, true)
	ghost:clearJournalQuestTask(EnoughQuest.IMPERIAL_CRC, 1, true)
	ghost:clearJournalQuestTask(EnoughQuest.IMPERIAL_CRC, 2, true)
	ghost:clearJournalQuestTask(EnoughQuest.IMPERIAL_CRC, 3, true)
	ghost:clearJournalQuestTask(EnoughQuest.IMPERIAL_CRC, 4, true)
	ghost:clearJournalQuestTask(EnoughQuest.IMPERIAL_CRC, 5, true)
	ghost:clearJournalQuestTask(EnoughQuest.IMPERIAL_CRC, 6, true)
	ghost:clearJournalQuestTask(EnoughQuest.IMPERIAL_CRC, 7, true)
	ghost:clearJournalQuestTask(EnoughQuest.IMPERIAL_CRC, 8, true)

	ghost:clearJournalQuest(EnoughQuest.IMPERIAL_CRC, true)



	if not PlayerObject(pGhost):isJournalQuestActive(EnoughQuest.IMPERIAL_CRC) then
		return convoTemplate:getScreen("imperial_greeting")
	elseif EnoughQuest:activeTask(ghost, EnoughQuest.IMPERIAL_CRC, EnoughQuest.GO_TO_LOCATION) then
		return convoTemplate:getScreen("where_friend")
	elseif EnoughQuest:activeTask(ghost, EnoughQuest.IMPERIAL_CRC, EnoughQuest.WAIT_FOR_SIGNAL1) or EnoughQuest:activeTask(ghost, EnoughQuest.IMPERIAL_CRC, EnoughQuest.REWARD1) then
		return convoTemplate:getScreen("no_pilot")
	elseif EnoughQuest:activeTask(ghost, EnoughQuest.IMPERIAL_CRC, EnoughQuest.DESTROY_MULTI) or
		EnoughQuest:activeTask(ghost, EnoughQuest.IMPERIAL_CRC, EnoughQuest.DESTROY_MULTI_AND_LOOT) then
		return convoTemplate:getScreen("ground_kill")
	end
	]]

	return convoTemplate:getScreen("neutral_greeting")
end