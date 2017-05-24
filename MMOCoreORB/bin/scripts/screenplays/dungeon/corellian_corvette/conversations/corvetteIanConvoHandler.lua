local ObjectManager = require("managers.object.object_manager")

corvetteIanConvoHandler = conv_handler:new {}

function corvetteIanConvoHandler:getInitialScreen(pPlayer, pNpc, pConvTemplate)
	local convoTemplate = LuaConversationTemplate(pConvTemplate)

	if (readData(SceneObject(pNpc):getObjectID() .. ":alreadyRescued") == 1) then
		return convoTemplate:getScreen("already_rescued")
	else
		return convoTemplate:getScreen("intro")
	end
end

function corvetteIanConvoHandler:runScreenHandlers(pConvTemplate, pPlayer, pNpc, selectedOption, pConvScreen)
	local screen = LuaConversationScreen(pConvScreen)
	local screenID = screen:getScreenID()

	local pConvScreen = screen:cloneScreen()
	local clonedConversation = LuaConversationScreen(pConvScreen)
	if (screenID == "safe_haven" or screenID == "excellent_work") then
		writeData(SceneObject(pNpc):getObjectID() .. ":alreadyRescued", 1)
		createEvent(3000, "CorellianCorvette", "doPrisonerEscape", pNpc, "")
		self:handleReward(pPlayer)
	end

	return pConvScreen
end

function corvetteIanConvoHandler:handleReward(pPlayer)
	local pCorvette = CorellianCorvette:getCorvetteObject(pPlayer)

	if (pCorvette == nil) then
		return
	end

	local questType = readStringData("corvetteQuestType:" .. SceneObject(pCorvette):getObjectID())

	if (questType == "rescue") then
		CorellianCorvette:increaseGroupFactionStanding(pCorvette, "rebel", 250)
		CorellianCorvette:handleQuestSuccess(pCorvette)
	else
		CorellianCorvette:increaseGroupFactionStanding(pCorvette, "rebel", 20)
	end
end
