local ObjectManager = require("managers.object.object_manager")
local JediPadawanTrial = require("screenplays.jedi.padawan.jedi_padawan_trial")
local ArtistTrial = require("screenplays.jedi.padawan.trials.trial_artist")

trialsPadawanArtist02ConvoHandler = Object:new {}

function trialsPadawanArtist02ConvoHandler:getNextConversationScreen(pConversationTemplate, pPlayer, selectedOption, pConversingNpc)
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

function trialsPadawanArtist02ConvoHandler:getInitialScreen(pPlayer, pNpc, pConversationTemplate)
	local state = CreatureObject(pPlayer):getScreenPlayState("JediPadawanTrialArtistScreenPlay")
	local convoTemplate = LuaConversationTemplate(pConversationTemplate)

	if (state == 2) then
		return convoTemplate:getScreen("intro")
	end

end

function trialsPadawanArtist02ConvoHandler:runScreenHandlers(pConversationTemplate, pConversingPlayer, pConversingNpc, selectedOption, pConversationScreen)
	local screen = LuaConversationScreen(pConversationScreen)
	local screenID = screen:getScreenID()

	if (screenID == "continued_final") then
		CreatureObject(pConversingPlayer):setScreenPlayState(4, "JediPadawanTrialArtistScreenPlay")
		createEvent(60 * 1000, "JediPadawanTrialArtistScreenPlay", "despawnNPC02", pConversingNpc)
		CreatureObject(pConversingPlayer):sendSystemMessage("@jedi_trials:padawan_trials_return_to_npc") -- Return to the person who gave you your trial task.
	end

	return pConversationScreen
end
