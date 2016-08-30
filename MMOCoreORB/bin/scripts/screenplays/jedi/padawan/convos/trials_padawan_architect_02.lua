local ObjectManager = require("managers.object.object_manager")
local JediPadawanTrial = require("screenplays.jedi.padawan.jedi_padawan_trial")
local ArchitectTrial = require("screenplays.jedi.padawan.trials.trial_architect")

trialsPadawanArchitect02ConvoHandler = Object:new {}

function trialsPadawanArchitect02ConvoHandler:getNextConversationScreen(pConversationTemplate, pPlayer, selectedOption, pConversingNpc)
	local pConversationSession = CreatureObject(pPlayer):getConversationSession()

	local pLastConversationScreen = nil

	if (pConversationSession ~= nil) then
		local conversationSession = LuaConversationSession(pConversationSession)
		pLastConversationScreen = conversationSession:getLastConversationScreen()
	end

	local conversationTemplate = LuaConversationTemplate(pConversationTemplate)

	if (pLastConversationScreen ~= nil) then
		local lastConversationScreen = LuaConversationScreen(pLastConversationScreen)
		local optionLink = lastConversationScreen:getOptionLink(selectedOption)

		return conversationTemplate:getScreen(optionLink)
	end

	return self:getInitialScreen(pPlayer, pConversingNpc, pConversationTemplate)
end

function trialsPadawanArchitect02ConvoHandler:getInitialScreen(pPlayer, pNpc, pConversationTemplate)
	local state = CreatureObject(pPlayer):getScreenPlayState("JediPadawanTrialArchitechScreenPlay")
	local convoTemplate = LuaConversationTemplate(pConversationTemplate)

	if (state == 2) then
		return convoTemplate:getScreen("intro")
	elseif (state == 0 or state == 4) then
		return convoTemplate:getScreen("noquest_player_talk")
	end

end

function trialsPadawanArchitect02ConvoHandler:runScreenHandlers(pConversationTemplate, pConversingPlayer, pConversingNpc, selectedOption, pConversationScreen)
	local screen = LuaConversationScreen(pConversationScreen)
	local screenID = screen:getScreenID()

	if (screenID == "nice_away") then
		CreatureObject(pConversingPlayer):setScreenPlayState(4, "JediPadawanTrialArchitechScreenPlay")
		createEvent(60 * 1000, "JediPadawanTrialArchitechScreenPlay", "despawnNPC02", pConversingNpc)
		CreatureObject(pConversingPlayer):sendSystemMessage("@jedi_trials:padawan_trials_return_to_npc") -- Return to the person who gave you your trial task.
	elseif (screenID == "initiate_attack_fail") then
		JediPadawanTrial:failCurrentTrial(pConversingPlayer)
		createEvent(10 * 1000, "JediPadawanTrialArchitechScreenPlay", "despawnNPC02", pConversingNpc)
	end

	return pConversationScreen
end
