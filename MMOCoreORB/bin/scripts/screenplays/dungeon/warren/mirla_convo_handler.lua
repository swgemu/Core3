local ObjectManager = require("managers.object.object_manager")

MirlaConversationHandler = conv_handler:new {}

function MirlaConversationHandler:runScreenHandlers(pConvTemplate, pPlayer, pNpc, selectedOption, pConvScreen)
	local screen = LuaConversationScreen(pConvScreen)

	local screenID = screen:getScreenID()

	if (screenID == "mirla_password") then
		local code = readStringData("warren:mirla:password")
		screen:setDialogTextTO(code)
	elseif (screenID == "mirla_2") then
		local pGhost = CreatureObject(pPlayer):getPlayerObject()

		if (pGhost ~= nil) then
			PlayerObject(pGhost):awardBadge(38) --Warren Compassion
		end

		CreatureObject(pPlayer):setScreenPlayState(WarrenScreenPlay.states.mirla.started, "warren");
	end

	return pConvScreen
end

function MirlaConversationHandler:getInitialScreen(pPlayer, pNpc, pConvTemplate)
	local convoTemplate = LuaConversationTemplate(pConvTemplate)

	if (CreatureObject(pPlayer):hasScreenPlayState(WarrenScreenPlay.states.mirla.done, "warren")) then
		return convoTemplate:getScreen("mirla_done")
	elseif (CreatureObject(pPlayer):hasScreenPlayState(WarrenScreenPlay.states.mirla.started, "warren")) then
		return convoTemplate:getScreen("mirla_get_teraud")
	end

	return convoTemplate:getScreen("mirla_start")
end
