local Syren = require("screenplays.events.syren.syren")

imperialJevanMonsulConvoHandler = conv_handler:new {}

function imperialJevanMonsulConvoHandler:getInitialScreen(pPlayer, pNpc, pConvTemplate)
	local convoTemplate = LuaConversationTemplate(pConvTemplate)

	if pPlayer ~= nil and SceneObject(pPlayer):isPlayerCreature() then
		local creature = LuaCreatureObject(pPlayer)
		local pGhost = creature:getPlayerObject()
		if pGhost ~= nil then
			local ghost = LuaPlayerObject(pGhost)
			if creature:isImperial() then
				if ghost:isJournalQuestTaskActive(Syren.act1.IMPERIAL_CRC, Syren.act1.RETURN_TO_CONTACT) then  -- Update for part 2
					return convoTemplate:getScreen("finish_act1")
				elseif ghost:isJournalQuestTaskComplete(Syren.act1.IMPERIAL_CRC, Syren.act1.TALK_TO_DOCTOR) then
					return convoTemplate:getScreen("welcome_back_no_datapad")
				elseif ghost:isJournalQuestTaskActive(Syren.act1.IMPERIAL_CRC, Syren.act1.TALK_TO_DOCTOR) then
					return convoTemplate:getScreen("welcome_back_doctor")
				elseif ghost:isJournalQuestTaskComplete(Syren.act1.IMPERIAL_CRC, Syren.act1.SPICE_FOUND) then
					return convoTemplate:getScreen("welcome_back_found_spice")
				elseif ghost:isJournalQuestTaskComplete(Syren.act1.IMPERIAL_CRC, Syren.act1.CRASH_SITE_FOUND) then
					return convoTemplate:getScreen("welcome_back_found_crash_site")
				elseif ghost:isJournalQuestTaskActive(Syren.act1.IMPERIAL_CRC, Syren.act1.LOOK_FOR_PILOT) then
					return convoTemplate:getScreen("welcome_back_no_info")
				else
					return convoTemplate:getScreen("start")
				end
			elseif creature:isRebel() then
				return convoTemplate:getScreen("different_faction_rebel")
			else
				return convoTemplate:getScreen("different_faction_neutral")
			end
		end
	end
end

function imperialJevanMonsulConvoHandler:runScreenHandlers(pConvTemplate, pPlayer, pNpc, selectedOption, pConvScreen)
	local screen = LuaConversationScreen(pConvScreen)
	local screenID = screen:getScreenID()

	if screenID == "accept" or screenID == "accept_job" then
		SecretsOfTheSyren:accept_quest_looking_for_pilot(pPlayer, Syren.act1.IMPERIAL_CRC)
	elseif screenID == "doctor" then
		SecretsOfTheSyren:accept_quest_talk_to_doctor(pPlayer, Syren.act1.IMPERIAL_CRC)
	elseif screenID == "finish_act1" then
		SecretsOfTheSyren:completeAct1(pPlayer, Syren.act1.IMPERIAL_CRC)
	end

	return pConvScreen
end
