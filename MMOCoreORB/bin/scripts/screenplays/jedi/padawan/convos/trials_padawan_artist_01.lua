local ObjectManager = require("managers.object.object_manager")
local JediPadawanTrial = require("screenplays.jedi.padawan.jedi_padawan_trial")
local ArtistTrial = require("screenplays.jedi.padawan.trials.trial_artist")

trialsPadawanArtist01ConvoHandler = Object:new {}

function trialsPadawanArtist01ConvoHandler:getNextConversationScreen(pConversationTemplate, pPlayer, selectedOption, pConversingNpc)
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

function trialsPadawanArtist01ConvoHandler:getInitialScreen(pPlayer, pNpc, pConversationTemplate)
	local state = CreatureObject(pPlayer):getScreenPlayState("JediPadawanTrialArtistScreenPlay")
	local convoTemplate = LuaConversationTemplate(pConversationTemplate)

	if (state == 1) then
		return convoTemplate:getScreen("intro")
	elseif (state == nil) then
		return convoTemplate:getScreen("noquest_player_talks")
	elseif (state == 2) then
	return convoTemplate:getScreen("back_not_done")
	elseif (state == 4) then
		return convoTemplate:getScreen("back_done")
	elseif (state == 8) then
		return convoTemplate:getScreen("helped_success")
	end

end

function trialsPadawanArtist01ConvoHandler:runScreenHandlers(pConversationTemplate, pConversingPlayer, pConversingNpc, selectedOption, pConversationScreen)
	local screen = LuaConversationScreen(pConversationScreen)
	local screenID = screen:getScreenID()

	if (screenID == "choose_hate") then
				JediPadawanTrial:failCurrentTrial(pConversingPlayer)
	elseif (screenID == "helped_but_too" or screenID == "helped_success") then
				JediPadawanTrial:passCurrentTrial(pConversingPlayer, pConversingNpc, 1)
	elseif (screenID == "choose_help_too") then
				CreatureObject(pConversingPlayer):setScreenPlayState(2, "JediPadawanTrialArtistScreenPlay")
				ArtistTrial:startPart2(pConversingPlayer)
	end

	return pConversationScreen
end
