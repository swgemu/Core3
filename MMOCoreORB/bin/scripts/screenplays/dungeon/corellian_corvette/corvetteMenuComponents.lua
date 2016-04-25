local ObjectManager = require("managers.object.object_manager")

CorvetteTerminalMenuComponent = { }

function CorvetteTerminalMenuComponent:fillObjectMenuResponse(pSceneObject, pMenuResponse, pPlayer)
	
	local corvetteID = readData(SceneObject(pPlayer):getObjectID() .. "corvetteId")
	local questID = readStringData(SceneObject(pSceneObject):getObjectID()..":quest")
	print(questID)

	local menuResponse = LuaObjectMenuResponse(pMenuResponse)
	menuResponse:addRadialMenuItem(20, 3,"@dungeon/corvette:"..questID.."_title")
end

function CorvetteTerminalMenuComponent:handleObjectMenuSelect(pSceneObject, pPlayer, selectedID)
	if (pPlayer == nil or selectedID ~= 20) then
		return
	end
	
	if (selectedID == 20) then
		CorvetteTerminalMessageBox:openAccessTerminal(pPlayer, pSceneObject)
	end

	return
end

CorvetteTerminalMessageBox = { }

function CorvetteTerminalMessageBox:openAccessTerminal(pPlayer, pSceneObject)
	local sui = SuiMessageBox.new("CorvetteEngineMessageBox", "defaultCallback")
	print(SceneObject(pPlayer):getObjectID())
	print(SceneObject(pSceneObject):getObjectID())
	
	local corvetteID = readData(SceneObject(pPlayer):getObjectID() .. "corvetteId")
	local questID = readStringData(SceneObject(pSceneObject):getObjectID()..":quest")
	print(questID)
	local btnOne = 0
	local btnTwo = 0
	local btnThree = 0
	
	if questID == "engine" then
		btnOne = getRandomNumber(40,60)
		btnTwo = engValue1 + 35 
		btnThree = engValue2 - 10
	elseif (questID == "hyperdrive") then
		btnOne =  40 
		btnTwo =  20
		btnThree =  60
	elseif questID == "fuel" then
		btnOne= 30 
		btnTwo= 50 
		btnThree= 80
	end
	print(btnOne)
	print(btnTwo)
	print(btnThree)
	sui.setProperty("btnRevert", "Enabled", "true")
	sui.setProperty("btnRevert", "Visible", "true")
	sui.setProperty("btnRevert", "Text", tostring(btnOne))
	sui.setProperty("btnOk", "Text", tostring(btnTwo))
	sui.setProperty("btnCancel", "Text", tostring(btnThree))
	if questID == "engine" then
		sui.setProperty("bg.caption.lblTitle", "Text", "@dungeon/corvette:engine_name")
		sui.setProperty("Prompt.lblPrompt", "Text", "@dungeon/corvette:engine_settings")
	elseif questID == "fuel" then
		sui.setProperty("bg.caption.lblTitle", "Text", "@dungeon/corvette:fuel_name")
		sui.setProperty("Prompt.lblPrompt", "Text", "@dungeon/corvette:fuel_settings")
	elseif questID == "hyperdrive" then
		sui.setProperty("bg.caption.lblTitle", "Text", "@dungeon/corvette:hyper_name")
		sui.setProperty("Prompt.lblPrompt", "Text", "@dungeon/corvette:hyperdrive_settings")
	end
	sui.subscribeToEvent(SuiEventType.SET_onButton, "btnOk", "CorvetteTerminalMessageBox:defaultCallback")
	sui.subscribeToEvent(SuiEventType.SET_onButton, "btnRevert", "CorvetteTerminalMessageBox:defaultCallback")
	sui.subscribeToEvent(SuiEventType.SET_onButton, "btnCancel", "CorvetteTerminalMessageBox:defaultCallback")
	sui.sendTo(pPlayer)
end

function CorvetteTerminalMessageBox:defaultCallback(pPlayer, pSui, eventIndex, args)
	local cancelPressed = (eventIndex == 1)
			
	if (cancelPressed) then
		CreatureObject(pPlayer):sendSystemMessage("@dungeon/corvette:engine_reset")
		return
	end
	
end
