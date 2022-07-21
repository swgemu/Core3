local Syren = require("screenplays.events.syren.syren")

doctorEdvarVangConvoHandler = conv_handler:new{}

function doctorEdvarVangConvoHandler:getInitialScreen(pPlayer, pNpc, pConvTemplate)
	local convoTemplate = LuaConversationTemplate(pConvTemplate)

	if pPlayer ~= nil and SceneObject(pPlayer):isPlayerCreature() then
		local creature = LuaCreatureObject(pPlayer)
		local pGhost = creature:getPlayerObject()
		if pGhost ~= nil then
			local ghost = LuaPlayerObject(pGhost)
			if ghost:isJournalQuestTaskComplete(Syren.act1.REBEL_CRC, Syren.act1.TALK_TO_DOCTOR) or
				ghost:isJournalQuestTaskComplete(Syren.act1.IMPERIAL_CRC, Syren.act1.TALK_TO_DOCTOR) or
				ghost:isJournalQuestTaskComplete(Syren.act1.NEUTRAL_CRC, Syren.act1.TALK_TO_DOCTOR) then
				return convoTemplate:getScreen("already_talked")
			elseif ghost:isJournalQuestTaskActive(Syren.act1.REBEL_CRC, Syren.act1.TALK_TO_DOCTOR) or
				ghost:isJournalQuestTaskActive(Syren.act1.IMPERIAL_CRC, Syren.act1.TALK_TO_DOCTOR) or
				ghost:isJournalQuestTaskActive(Syren.act1.NEUTRAL_CRC, Syren.act1.TALK_TO_DOCTOR)  then
				return convoTemplate:getScreen("start")
			else
				return convoTemplate:getScreen("quest_not_ready_yet")
			end
		end
	end
end

function doctorEdvarVangConvoHandler:runScreenHandlers(pConvTemplate, pPlayer, pNpc, selectedOption, pConvScreen)
	local screen = LuaConversationScreen(pConvScreen)
	local screenID = screen:getScreenID()

	if screenID == "dangerous" then
		if pPlayer ~= nil and SceneObject(pPlayer):isPlayerCreature() then
			local creature = LuaCreatureObject(pPlayer)
			local pGhost = creature:getPlayerObject()
			if pGhost ~= nil then
				local ghost = LuaPlayerObject(pGhost)
				if ghost:isJournalQuestTaskActive(Syren.act1.REBEL_CRC, Syren.act1.TALK_TO_DOCTOR) then
					SecretsOfTheSyren:acceptQuestLookingForMoxxar(pPlayer, Syren.act1.REBEL_CRC)
				elseif ghost:isJournalQuestTaskActive(Syren.act1.IMPERIAL_CRC, Syren.act1.TALK_TO_DOCTOR) then
					SecretsOfTheSyren:acceptQuestLookingForMoxxar(pPlayer, Syren.act1.IMPERIAL_CRC)
				elseif ghost:isJournalQuestTaskActive(Syren.act1.NEUTRAL_CRC, Syren.act1.TALK_TO_DOCTOR) then
					SecretsOfTheSyren:acceptQuestLookingForMoxxar(pPlayer, Syren.act1.NEUTRAL_CRC)
				end
			end
		end
	end

	return pConvScreen
end
