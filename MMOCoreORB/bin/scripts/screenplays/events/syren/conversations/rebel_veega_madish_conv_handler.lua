local Syren = require("screenplays.events.syren.syren")

rebelVeegaMadishConvoHandler = conv_handler:new {}

function rebelVeegaMadishConvoHandler:getInitialScreen(pPlayer, pNpc, pConvTemplate)
	local convoTemplate = LuaConversationTemplate(pConvTemplate)

	if pPlayer ~= nil and SceneObject(pPlayer):isPlayerCreature() then
		local creature = LuaCreatureObject(pPlayer)
		local pGhost = creature:getPlayerObject()
		if pGhost ~= nil then
			local ghost = LuaPlayerObject(pGhost)
			if creature:isRebel() then
				if ghost:isJournalQuestTaskComplete(Syren.act2.REBEL_CRC, Syren.act2.TALK_TO_KAILA) then
					return convoTemplate:getScreen("finished")
				elseif ghost:isJournalQuestTaskActive(Syren.act2.REBEL_CRC, Syren.act2.TALK_TO_KAILA) then
					return convoTemplate:getScreen("where_is_she")
				elseif ghost:isJournalQuestTaskActive(Syren.act1.REBEL_CRC, Syren.act1.RETURN_TO_CONTACT) or ghost:isJournalQuestComplete(Syren.act1.REBEL_CRC) then
					return convoTemplate:getScreen("start_finish")
				elseif ghost:isJournalQuestTaskComplete(Syren.act1.REBEL_CRC, Syren.act1.TALK_TO_DOCTOR) then
					return convoTemplate:getScreen("welcome_back_no_datapad")
				elseif ghost:isJournalQuestTaskActive(Syren.act1.REBEL_CRC, Syren.act1.TALK_TO_DOCTOR) then
					return convoTemplate:getScreen("welcome_back_doctor")
				elseif ghost:isJournalQuestTaskComplete(Syren.act1.REBEL_CRC, Syren.act1.SPICE_FOUND) then
					return convoTemplate:getScreen("welcome_back_found_spice")
				elseif ghost:isJournalQuestTaskComplete(Syren.act1.REBEL_CRC, Syren.act1.CRASH_SITE_FOUND) then
					return convoTemplate:getScreen("welcome_back_found_crash_site")
				elseif ghost:isJournalQuestTaskActive(Syren.act1.REBEL_CRC, Syren.act1.LOOK_FOR_PILOT) then
					return convoTemplate:getScreen("welcome_back_no_info")
				else
					return convoTemplate:getScreen("start")
				end
			elseif creature:isImperial() then
				return convoTemplate:getScreen("different_faction_imperial")
			else
				return convoTemplate:getScreen("different_faction_neutral")
			end
		end
	end
end

function rebelVeegaMadishConvoHandler:runScreenHandlers(pConvTemplate, pPlayer, pNpc, selectedOption, pConvScreen)
	local screen = LuaConversationScreen(pConvScreen)
	local screenID = screen:getScreenID()

	if screenID == "accept" or screenID == "accept_job" then
		SecretsOfTheSyren:acceptQuestLookingForPilot(pPlayer, Syren.act1.REBEL_CRC)
	elseif screenID == "doctor" then
		SecretsOfTheSyren:acceptQuestTalkToDoctor(pPlayer, Syren.act1.REBEL_CRC)
	elseif screenID == "start_finish" then
		SecretsOfTheSyren:finishAct1(pPlayer, Syren.act1.REBEL_CRC)
	elseif screenID == "where_is_she" then
		SecretsOfTheSyren:acceptQuestGoToKailaMin(pPlayer, Syren.act2.REBEL_CRC)
	end

	return pConvScreen
end
