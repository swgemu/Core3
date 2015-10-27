local ObjectManager = require("managers.object.object_manager")
local JediPadawanTrial = require("screenplays.jedi.padawan.jedi_padawan_trial")
local ArchitectTrial = require("screenplays.jedi.padawan.trials.trial_architect")

trialsPadawanArchitect01ConvoHandler = Object:new {}

function trialsPadawanArchitect01ConvoHandler:getNextConversationScreen(pConversationTemplate, pPlayer, selectedOption, pConversingNpc)
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

function trialsPadawanArchitect01ConvoHandler:getInitialScreen(pPlayer, pNpc, pConversationTemplate)
	local state = CreatureObject(pPlayer):getScreenPlayState("JediPadawanTrialArchitechScreenPlay")
	local convoTemplate = LuaConversationTemplate(pConversationTemplate)

	if (state == 1) then
		return convoTemplate:getScreen("intro")
	elseif (state == 2 or state == nil) then
		return convoTemplate:getScreen("not_yet_done")
	elseif (state == 4) then
		return convoTemplate:getScreen("done_with_task")
	elseif (state == 8) then
		return convoTemplate:getScreen("over_sour_success")
	end

end

function trialsPadawanArchitect01ConvoHandler:runScreenHandlers(pConversationTemplate, pConversingPlayer, pConversingNpc, selectedOption, pConversationScreen)
	local screen = LuaConversationScreen(pConversationScreen)
	local screenID = screen:getScreenID()

	if (screenID == "yes_kill_fail" or screenID == "no_decline") then
				JediPadawanTrial:failCurrentTrial(pConversingPlayer)
	elseif (screenID == "back_chose_success") then
				JediPadawanTrial:passCurrentTrial(pConversingPlayer, pConversingNpc, "JediPadawanTrialArchitechScreenPlay")
	elseif (screenID == "yes_accept") then
				CreatureObject(pConversingPlayer):setScreenPlayState(2, "JediPadawanTrialArchitechScreenPlay")
				ArchitectTrial:startPart2(pConversingPlayer)
	end

	return pConversationScreen
end
