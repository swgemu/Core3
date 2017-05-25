CorvetteSui = ScreenPlay:new {}

function CorvetteSui:sendEngineSui(pPlayer, pSceneObject)
	local sui = SuiMessageBox.new("CorvetteSui", "engineSuiCallback")
	sui.setTitle("@dungeon/corvette:engine_title") -- ENGINE SETTINGS
	sui.setPrompt("@dungeon/corvette:engine_settings") -- Select Engine settings for the Corvette: Exiting without making a selection will force the engine to its default setting.
	sui.setTargetNetworkId(SceneObject(pSceneObject):getObjectID())
	sui.setForceCloseDistance(10)
	sui.setProperty("", "Size", "250,175")
	sui.setProperty("btnRevert", "OnPress", "RevertWasPressed=1\r\nparent.btnOk.press=t")
	sui.subscribeToPropertyForEvent(SuiEventType.SET_onClosedOk, "btnRevert", "RevertWasPressed")

	local engineID = SceneObject(pSceneObject):getObjectID()
	local valueA = readData(engineID .. ":valueA")
	local valueB = readData(engineID .. ":valueB")
	local valueC = readData(engineID .. ":valueC")

	if (valueA == 0) then
		valueA = getRandomNumber(40, 60)
		valueB = valueA + 35
		valueC = valueA - 10

		writeData(engineID .. ":valueA", valueA)
		writeData(engineID .. ":valueB", valueB)
		writeData(engineID .. ":valueC", valueC)
	end


	sui.setOkButtonText(tostring(valueC))
	sui.setCancelButtonText(tostring(valueB))
	sui.setOtherButtonText(tostring(valueA))
	sui.sendTo(pPlayer)
end

function CorvetteSui:engineSuiCallback(pPlayer, pSui, eventIndex, ...)
	local pPageData = LuaSuiBoxPage(pSui):getSuiPageData()

	if (pPageData == nil) then
		return
	end

	local suiPageData = LuaSuiPageData(pPageData)

	local engineID = suiPageData:getTargetNetworkId()

	local valueA = readData(engineID .. ":valueA")
	local valueB = readData(engineID .. ":valueB")
	local valueC = readData(engineID .. ":valueC")

	deleteData(engineID .. ":valueA")
	deleteData(engineID .. ":valueB")
	deleteData(engineID .. ":valueC")

	if (pPlayer == nil) then
		return
	end

	local pEngine = getSceneObject(engineID)

	if (pEngine == nil) then
		return
	end

	local corvetteID = readData(SceneObject(pPlayer):getObjectID() .. "corvetteID")
	local pCorvette = getSceneObject(corvetteID)

	if (pCorvette == nil) then
		return
	end

	if (readData(corvetteID .. ":engineDestroyed") == 1) then
		CreatureObject(pPlayer):sendSystemMessage("@dungeon/corvette:blew_up") -- You have successfully managed to destroy the engines! Your mission is complete.
		return
	end

	local cancelPressed = (eventIndex == 1)
	local args = {...}
	local revertPressed = args[1]
	local pickedValue = 0

	if (cancelPressed) then -- B
		pickedValue = valueB
		writeData(corvetteID .. ":engineSetting", valueB)
	elseif (revertPressed ~= nil) then -- A
		pickedValue = valueA
		writeData(corvetteID .. ":engineSetting", valueA)
	elseif (eventIndex == 0) then -- C
		pickedValue = valueC
		writeData(corvetteID .. ":engineSetting", valueC)
	end

	CreatureObject(pPlayer):sendSystemMessage("You have set the engine to " .. tostring(pickedValue) .. "%") -- You have set the engine to

	if (revertPressed ~= nil or cancelPressed) then
		CreatureObject(pPlayer):sendSystemMessage("@dungeon/corvette:engine_result") -- The engine appears to be running normally.
		return
	end

	local fuelSetting = readData(corvetteID .. ":fuelSetting")
	local hyperdriveSetting = readData(corvetteID .. ":hyperdriveSetting")

	if (fuelSetting == 0 or hyperdriveSetting == 0 or fuelSetting < hyperdriveSetting) then
		CreatureObject(pPlayer):sendSystemMessage("@dungeon/corvette:calculations") -- Your calculations must be off...
		return
	end

	CreatureObject(pPlayer):sendSystemMessage("@dungeon/corvette:blew_up") -- You have successfully managed to destroy the engines! Your mission is complete.
	writeData(corvetteID .. ":engineDestroyed", 1)
	CorellianCorvette:handleQuestSuccess(pCorvette)
end

function CorvetteSui:sendFuelSui(pPlayer, pSceneObject)
	local sui = SuiMessageBox.new("CorvetteSui", "fuelSuiCallback")
	sui.setTitle("@dungeon/corvette:fuel_title") -- FUEL SETTINGS
	sui.setPrompt("@dungeon/corvette:fuel_settings") -- Select Fuel Intake settings for the Corvette: Exiting without making a selection will force the fuel intake to its default setting.
	sui.setTargetNetworkId(SceneObject(pSceneObject):getObjectID())
	sui.setForceCloseDistance(10)
	sui.setProperty("", "Size", "250,175")
	sui.setOkButtonText("50")
	sui.setCancelButtonText("80")
	sui.setOtherButtonText("30")
	sui.setProperty("btnRevert", "OnPress", "RevertWasPressed=1\r\nparent.btnOk.press=t")
	sui.subscribeToPropertyForEvent(SuiEventType.SET_onClosedOk, "btnRevert", "RevertWasPressed")

	sui.sendTo(pPlayer)
end

function CorvetteSui:fuelSuiCallback(pPlayer, pSui, eventIndex, ...)
	if (pPlayer == nil) then
		return
	end

	local pPageData = LuaSuiBoxPage(pSui):getSuiPageData()

	if (pPageData == nil) then
		return
	end

	local suiPageData = LuaSuiPageData(pPageData)

	local fuelID = suiPageData:getTargetNetworkId()

	local pFuel = getSceneObject(fuelID)

	if (pFuel == nil) then
		return
	end

	local corvetteID = readData(SceneObject(pPlayer):getObjectID() .. "corvetteID")
	local pCorvette = getSceneObject(corvetteID)

	if (pCorvette == nil) then
		return
	end

	local cancelPressed = (eventIndex == 1)
	local args = {...}
	local revertPressed = args[1]
	local fuelSetting = 0
	local hyperdriveSetting = readData(corvetteID .. ":hyperdriveSetting")
	local engineSetting = readData(corvetteID .. ":engineSetting")

	if (cancelPressed) then -- 80
		fuelSetting = 80
	elseif (revertPressed ~= nil) then -- 30
		fuelSetting = 30
	elseif (eventIndex == 0) then -- 50
		fuelSetting = 50
	end

	writeData(corvetteID .. ":fuelSetting", fuelSetting)
	CreatureObject(pPlayer):sendSystemMessage("@dungeon/corvette:fuel_" .. fuelSetting)
	CreatureObject(pPlayer):sendSystemMessage("Hyperdrive is at " .. hyperdriveSetting)

	if (engineSetting == 0) then
		CreatureObject(pPlayer):sendSystemMessage("@dungeon/corvette:engine_result") -- The engine appears to be running normally.
	else
		CreatureObject(pPlayer):sendSystemMessage("Engine is at " .. engineSetting)
	end

	if (fuelSetting > hyperdriveSetting) then
		CreatureObject(pPlayer):sendSystemMessage("@dungeon/corvette:engine_reset") -- 	The engines will have to be reset.
	end
end

function CorvetteSui:sendHyperdriveSui(pPlayer, pSceneObject)
	local sui = SuiMessageBox.new("CorvetteSui", "hyperdriveSuiCallback")
	sui.setTitle("@dungeon/corvette:hyperdrive_title") -- HYPERDRIVE SETTINGS
	sui.setPrompt("@dungeon/corvette:hyperdrive_settings") -- Select Power setting for the Hyperdrive: Exiting without setting the Hyperdrive power setting will force it to its default state.
	sui.setTargetNetworkId(SceneObject(pSceneObject):getObjectID())
	sui.setForceCloseDistance(10)
	sui.setProperty("", "Size", "250,175")
	sui.setOkButtonText("20")
	sui.setCancelButtonText("60")
	sui.setOtherButtonText("40")
	sui.setProperty("btnRevert", "OnPress", "RevertWasPressed=1\r\nparent.btnOk.press=t")
	sui.subscribeToPropertyForEvent(SuiEventType.SET_onClosedOk, "btnRevert", "RevertWasPressed")

	sui.sendTo(pPlayer)
end

function CorvetteSui:hyperdriveSuiCallback(pPlayer, pSui, eventIndex, ...)
	if (pPlayer == nil) then
		return
	end

	local pPageData = LuaSuiBoxPage(pSui):getSuiPageData()

	if (pPageData == nil) then
		return
	end

	local suiPageData = LuaSuiPageData(pPageData)

	local hyperdriveID = suiPageData:getTargetNetworkId()

	local pHyperdrive = getSceneObject(hyperdriveID)

	if (pHyperdrive == nil) then
		return
	end

	local corvetteID = readData(SceneObject(pPlayer):getObjectID() .. "corvetteID")
	local pCorvette = getSceneObject(corvetteID)

	if (pCorvette == nil) then
		return
	end

	local cancelPressed = (eventIndex == 1)
	local args = {...}
	local revertPressed = args[1]
	local powerSetting = 0
	local fuelSetting = readData(corvetteID .. ":fuelSetting")
	local engineSetting = readData(corvetteID .. ":engineSetting")

	if (cancelPressed) then -- 60
		powerSetting = 60
	elseif (revertPressed ~= nil) then -- 40
		powerSetting = 40
	elseif (eventIndex == 0) then -- 20
		powerSetting = 20
	end

	writeData(corvetteID .. ":hyperdriveSetting", powerSetting)
	CreatureObject(pPlayer):sendSystemMessage("@dungeon/corvette:hypr_" .. powerSetting)
	CreatureObject(pPlayer):sendSystemMessage("Fuel is at " .. fuelSetting)

	if (engineSetting == 0) then
		CreatureObject(pPlayer):sendSystemMessage("@dungeon/corvette:engine_result") -- The engine appears to be running normally.
	else
		CreatureObject(pPlayer):sendSystemMessage("Engine is at " .. engineSetting)
	end

	if (fuelSetting > powerSetting) then
		CreatureObject(pPlayer):sendSystemMessage("@dungeon/corvette:engine_reset") -- 	The engines will have to be reset.
	end
end

function CorvetteSui:sendKeypadSui(pKeypad, pPlayer)
	local sui = SuiKeypad.new("CorvetteSui", "keypadSuiCallback")
	sui.setTargetNetworkId(SceneObject(pKeypad):getObjectID())
	sui.setForceCloseDistance(10)
	sui.hideSliceButton()
	sui.hideKeycardButton()
	sui.sendTo(pPlayer)
end

function CorvetteSui:keypadSuiCallback(pPlayer, pSui, eventIndex, args)
	if (pPlayer == nil) then
		return
	end

	local pPageData = LuaSuiBoxPage(pSui):getSuiPageData()

	if (pPageData == nil) then
		return
	end

	local suiPageData = LuaSuiPageData(pPageData)

	local keypadID = suiPageData:getTargetNetworkId()

	local pKeypad = getSceneObject(keypadID)

	if (pKeypad == nil) then
		return
	end

	local corvetteID = readData(SceneObject(pPlayer):getObjectID() .. "corvetteID")
	local pCorvette = getSceneObject(corvetteID)

	if (pCorvette == nil) then
		return
	end

	local cancelPressed = (eventIndex == 1)

	if (cancelPressed) then
		return
	end

	local keypadRoom = readStringSharedMemory(keypadID .. ":keypadRoom")
	local keypadCode = CorellianCorvette:readDataFromGroup(pCorvette, ":code:" .. keypadRoom)
	local enteredCode = 0

	if (args ~= nil and args ~= "") then
		enteredCode = tonumber(args)
	end

	if (keypadCode ~= nil and keypadCode ~= "" and enteredCode == keypadCode) then
		CreatureObject(pPlayer):sendSystemMessage("@dungeon/corvette:open") -- This door is now unlocked.
		CorellianCorvette:unlockRoom(pCorvette, keypadRoom)
	else
		CreatureObject(pPlayer):sendSystemMessage("@dungeon/corvette:lock") -- This door is still locked.
	end
end
