local Syren = require("screenplays.events.syren.syren")

kailaMinConvoHandler = conv_handler:new{}

function kailaMinConvoHandler:getInitialScreen(pPlayer, pNpc, pConvTemplate)
	local convoTemplate = LuaConversationTemplate(pConvTemplate)

	if pPlayer ~= nil and SceneObject(pPlayer):isPlayerCreature() then
		local creature = LuaCreatureObject(pPlayer)
		local pGhost = creature:getPlayerObject()
		if pGhost ~= nil then
			local ghost = LuaPlayerObject(pGhost)
			if ghost:isJournalQuestTaskComplete(Syren.act2.REBEL_CRC, Syren.act2.AMBUSH_COMPLETE) or
				ghost:isJournalQuestTaskComplete(Syren.act2.IMPERIAL_CRC, Syren.act2.AMBUSH_COMPLETE) or
				ghost:isJournalQuestTaskComplete(Syren.act2.NEUTRAL_CRC, Syren.act2.AMBUSH_COMPLETE) then
				return convoTemplate:getScreen("start_ambushed")
			elseif ghost:isJournalQuestTaskActive(Syren.act2.REBEL_CRC, Syren.act2.TALK_TO_KAILA) or
				ghost:isJournalQuestTaskActive(Syren.act2.IMPERIAL_CRC, Syren.act2.TALK_TO_KAILA) or
				ghost:isJournalQuestTaskActive(Syren.act2.NEUTRAL_CRC, Syren.act2.TALK_TO_KAILA)  then
				return convoTemplate:getScreen("start")
			else
				return convoTemplate:getScreen("start_not_ready")
			end
		end
	end
end

function kailaMinConvoHandler:runScreenHandlers(pConvTemplate, pPlayer, pNpc, selectedOption, pConvScreen)
	local screen = LuaConversationScreen(pConvScreen)
	local screenID = screen:getScreenID()

	if screenID == "tell_more" then
		if pPlayer ~= nil and SceneObject(pPlayer):isPlayerCreature() then
			local creature = LuaCreatureObject(pPlayer)
			local pGhost = creature:getPlayerObject()
			if pGhost ~= nil then
				local ghost = LuaPlayerObject(pGhost)
				if ghost:isJournalQuestTaskActive(Syren.act2.REBEL_CRC, Syren.act2.TALK_TO_KAILA) then
					SecretsOfTheSyren:acceptQuestGoToAmbush(pPlayer, Syren.act2.REBEL_CRC)
				elseif ghost:isJournalQuestTaskActive(Syren.act2.IMPERIAL_CRC, Syren.act2.TALK_TO_KAILA) then
					SecretsOfTheSyren:acceptQuestGoToAmbush(pPlayer, Syren.act2.IMPERIAL_CRC)
				elseif ghost:isJournalQuestTaskActive(Syren.act2.NEUTRAL_CRC, Syren.act2.TALK_TO_KAILA) then
					SecretsOfTheSyren:acceptQuestGoToAmbush(pPlayer, Syren.act2.NEUTRAL_CRC)
				end
			end
		end
	end

	return pConvScreen
end
