local ObjectManager = require("managers.object.object_manager")

corvettePrisonerConvoHandler = conv_handler:new {}

function corvettePrisonerConvoHandler:getInitialScreen(pPlayer, pNpc, pConvTemplate)
	local convoTemplate = LuaConversationTemplate(pConvTemplate)

	if (readData(SceneObject(pNpc):getObjectID() .. ":alreadyRescued") == 1) then
		return convoTemplate:getScreen("rescued")
	else
		return convoTemplate:getScreen("not_rescued")
	end
end

function corvettePrisonerConvoHandler:runScreenHandlers(pConvTemplate, pPlayer, pNpc, selectedOption, pConvScreen)
	local screen = LuaConversationScreen(pConvScreen)
	local screenID = screen:getScreenID()

	local pConvScreen = screen:cloneScreen()
	local clonedConversation = LuaConversationScreen(pConvScreen)
	if (screenID == "not_rescued") then
		writeData(SceneObject(pNpc):getObjectID() .. ":alreadyRescued", 1)
		createEvent(3000, "CorellianCorvette", "doPrisonerEscape", pNpc, "")
		self:handleReward(pPlayer)
	end

	return pConvScreen
end

function corvettePrisonerConvoHandler:handleReward(pPlayer)
	local pCorvette = CorellianCorvette:getCorvetteObject(pPlayer)

	if (pCorvette == nil) then
		return
	end

	local corvetteFaction = CorellianCorvette:getBuildingFaction(pCorvette)

	if (corvetteFaction == "neutral") then
		corvetteFaction = "jabba"
	end

	CorellianCorvette:increaseGroupFactionStanding(pCorvette, corvetteFaction, 10)
end
