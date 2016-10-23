local ObjectManager = require("managers.object.object_manager")

deathWatchRescueScientistConvoHandler = conv_handler:new {}

function deathWatchRescueScientistConvoHandler:getInitialScreen(pPlayer, pNpc, pConvTemplate)
	local convoTemplate = LuaConversationTemplate(pConvTemplate)
	if (CreatureObject(pPlayer):hasScreenPlayState(2, "death_watch_bunker_rebel_sidequest")) then
		return convoTemplate:getScreen("return_thanks")
	elseif (CreatureObject(pPlayer):hasScreenPlayState(1, "death_watch_bunker_rebel_sidequest")) then
		CreatureObject(pPlayer):setScreenPlayState(2, "death_watch_bunker_rebel_sidequest")
		CreatureObject(pPlayer):sendSystemMessageWithDI("@theme_park/messages:theme_park_credits_pp", "487")
		CreatureObject(pPlayer):addCashCredits(487, true)
		return convoTemplate:getScreen("thanks1")
	elseif (CreatureObject(pPlayer):isOnLeave() or not CreatureObject(pPlayer):isRebel()) then
		return convoTemplate:getScreen("thanks2")
	else
		return convoTemplate:getScreen("thanks3")
	end
end
