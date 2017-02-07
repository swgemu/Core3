local ObjectManager = require("managers.object.object_manager")

SuiAmpPuzzle = {}
function SuiAmpPuzzle:openPuzzle(pPlayer, pPuzzle, pCalibrator)
	local sui = SuiCalibrationGame2.new("SuiAmpPuzzle", "defaultCallback")
	local playerID = SceneObject(pPlayer):getObjectID()
	writeData(playerID .. ":calibratorComponentID", SceneObject(pPuzzle):getObjectID())

	sui.setTargetNetworkId(SceneObject(pCalibrator):getObjectID())
	sui.setForceCloseDistance(10)

	local bar1 = getRandomNumber(0, 2)
	local bar2 = getRandomNumber(0, 1)

	if (bar2 == 0) then
		bar2 = -1
	end

	bar2 = bar2 + bar1

	if (bar2 == -1) then
		bar2 = 2
	elseif (bar2 == 3) then
		bar2 = 0
	end

	local bar3 = 0

	for i = 0, 2, 1 do
		if (i ~= bar1 and i ~= bar2) then
			bar3 = i
		end
	end

	local playerID = SceneObject(pPlayer):getObjectID()

	writeData(playerID .. ":ampPuzzle:bar1", bar1)
	writeData(playerID .. ":ampPuzzle:bar2", bar2)
	writeData(playerID .. ":ampPuzzle:bar3", bar3)

	local coefficient1 = getRandomNumber(1, 100) / 100
	local coefficient2 = getRandomNumber(1, 100) / 100
	local coefficient3 = getRandomNumber(1, 100) / 100

	writeData(playerID .. ":ampPuzzle:coefficient1", coefficient1 * 100)
	writeData(playerID .. ":ampPuzzle:coefficient2", coefficient2 * 100)
	writeData(playerID .. ":ampPuzzle:coefficient3", coefficient3 * 100)

	local sliderPos1 = getRandomNumber(1, 100) / 100
	local sliderPos2 = getRandomNumber(1, 100) / 100
	local sliderPos3 = getRandomNumber(1, 100) / 100

	writeData(playerID .. ":ampPuzzle:sliderPos1", sliderPos1)
	writeData(playerID .. ":ampPuzzle:sliderPos2", sliderPos2)
	writeData(playerID .. ":ampPuzzle:sliderPos3", sliderPos3)

	sui.setProperty("top.sliders.1.slider", "Value", "" .. (100 * sliderPos1))
	sui.setProperty("top.sliders.2.slider", "Value", "" .. (100 * sliderPos2))
	sui.setProperty("top.sliders.3.slider", "Value", "" .. (100 * sliderPos3))

	sui.setProperty("top.sliders.1.title", "Text", "@quest/force_sensitive/fs_crafting:sui_amp_slider1")
	sui.setProperty("top.sliders.2.title", "Text", "@quest/force_sensitive/fs_crafting:sui_amp_slider2")
	sui.setProperty("top.sliders.3.title", "Text", "@quest/force_sensitive/fs_crafting:sui_amp_slider3")

	local tries = 25

	writeData(playerID .. ":ampPuzzle:tries", tries)
	writeData(playerID .. ":ampPuzzle:maxTries", tries)

	sui.setTitle("@quest/force_sensitive/fs_crafting:sui_amp_title")
	sui.setDescription("@quest/force_sensitive/fs_crafting:sui_amp_description")
	sui.setAttemptsDesc("@quest/force_sensitive/fs_crafting:sui_attempts_remaining" .. " 100%")

	local c1, c2, c3
	if (bar1 == 0) then c1 = sliderPos1 elseif (bar1 == 1) then c1 = sliderPos2 else c1 = sliderPos3 end
	if (bar2 == 0) then c2 = sliderPos1 elseif (bar2 == 1) then c2 = sliderPos2 else c2 = sliderPos3 end
	if (bar3 == 0) then c3 = sliderPos1 elseif (bar3 == 1) then c3 = sliderPos2 else c3 = sliderPos3 end

	for i = 1, 7, 1 do
		local n = (i - 1) / 7

		local value = (c1 + (c2 * n) + (c3 * n * n)) / 3

		if value < 0 then
			value = 0
		elseif value > 1 then
			value = 1
		end

		sui.setProperty("top.bars.yours." .. i, "Value", "" .. math.floor(100 * value))
		sui.setProperty("top.bars.yours." .. i, "OnRunScript", "sizeY = (parent.sizeY * Value) / 100\nlocationY = parent.sizeY - sizeY")
		sui.setProperty("top.bars.yours." .. i, "RunScript", "")

		value = (coefficient1 + (coefficient2 * n) + (coefficient3 * n * n)) / 3

		if value < 0 then
			value = 0
		elseif value > 1 then
			value = 1
		end

		sui.setProperty("top.bars.servers." .. i, "Value", "" .. math.floor(100 * value))
		sui.setProperty("top.bars.servers." .. i, "OnRunScript", "sizeY = (parent.sizeY * Value) / 100\nlocationY = parent.sizeY - sizeY")
		sui.setProperty("top.bars.servers." .. i, "RunScript", "")
		writeData(playerID .. ":ampPuzzle:serverBarVal" .. i, math.floor(100 * value))
	end

	sui.setProperty("btnOk", "IsDefaultButton", "true")

	sui.subscribeToEvent(SuiEventType.SET_onButton, "btnOk", "SuiAmpPuzzle:defaultCallback")

	sui.subscribeToPropertyForEvent(SuiEventType.SET_onButton, "top.sliders.1.slider", "Value")
	sui.subscribeToPropertyForEvent(SuiEventType.SET_onButton, "top.sliders.2.slider", "Value")
	sui.subscribeToPropertyForEvent(SuiEventType.SET_onButton, "top.sliders.3.slider", "Value")

	local pageId = sui.sendTo(pPlayer)
	writeData(playerID .. ":ampPuzzle:Pid", pageId)
end

function SuiAmpPuzzle:noCallback(pPlayer, pSui, eventIndex, ...)
end

function SuiAmpPuzzle:defaultCallback(pPlayer, pSui, eventIndex, ...)
	local pGhost = CreatureObject(pPlayer):getPlayerObject()

	if (pGhost == nil) then
		return
	end

	local cancelPressed = (eventIndex == 1)
	local playerID = SceneObject(pPlayer):getObjectID()
	local pageId = readData(playerID .. ":ampPuzzle:Pid")

	if (pageId == 0) then
		return
	end

	local pPageData = LuaSuiBoxPage(pSui):getSuiPageData()

	if (pPageData == nil) then
		printLuaError("SuiAmpPuzzle:defaultCallback, pageData is nil.")
		return
	end

	local suiPageData = LuaSuiPageData(pPageData)

	if (cancelPressed) then
		CreatureObject(pPlayer):sendSystemMessage("@quest/force_sensitive/fs_crafting:phase1_msg_calibration_aborted")
		self:doDataCleanup(pPlayer)
		return
	end

	local puzzleID = readData(playerID .. ":calibratorComponentID")
	local pPuzzle = getSceneObject(puzzleID)

	if (pPuzzle == nil) then
		printLuaError("SuiAmpPuzzle:defaultCallback, pPuzzle nil.")
		return
	end

	local pInventory = CreatureObject(pPlayer):getSlottedObject("inventory")

	if pInventory == nil or SceneObject(pPuzzle):getParentID() ~= SceneObject(pInventory):getObjectID() then
		return
	end

	PlayerObject(pGhost):addSuiBox(pSui)

	local args = {...}

	local sliderPos = { }
	local coefficients = { }
	local barValues = { }

	for i = 1, 3 , 1 do
		sliderPos[i] = args[i] / 100
		coefficients[i] = readData(playerID .. ":ampPuzzle:coefficient" .. i) / 100
		barValues[i] = readData(playerID .. ":ampPuzzle:bar" .. i)

		suiPageData:setProperty("top.sliders." .. i .. ".slider", "Value", tostring(sliderPos[i] * 100))
	end

	local c1, c2, c3
	if (barValues[1] == 0) then c1 = sliderPos[1] elseif (barValues[1] == 1) then c1 = sliderPos[2] else c1 = sliderPos[3] end
	if (barValues[2] == 0) then c2 = sliderPos[1] elseif (barValues[2] == 1) then c2 = sliderPos[2] else c2 = sliderPos[3] end
	if (barValues[3] == 0) then c3 = sliderPos[1] elseif (barValues[3] == 1) then c3 = sliderPos[2] else c3 = sliderPos[3] end

	local e = 0
	for i = 1, 7, 1 do
		local n = (i - 1) / 7

		local value = (c1 + (c2 * n) + (c3 * n * n)) / 3

		if value < 0 then
			value = 0
		elseif value > 1 then
			value = 1
		end

		suiPageData:setProperty("top.bars.yours." .. i, "Value", "" .. math.floor(100 * value))
		suiPageData:setProperty("top.bars.yours." .. i, "RunScript", "")

		local targetValue =  (coefficients[1] + (coefficients[2] * n) + (coefficients[3] * n * n)) / 3
		e = e + math.abs(value - targetValue)

		suiPageData:setProperty("top.bars.servers." .. i, "Value", "" .. readData(playerID .. ":ampPuzzle:serverBarVal" .. i))
		suiPageData:setProperty("top.bars.servers." .. i, "OnRunScript", "sizeY = (parent.sizeY * Value) / 100\nlocationY = parent.sizeY - sizeY")
		suiPageData:setProperty("top.bars.servers." .. i, "RunScript", "")
	end

	local wonPuzzle = false

	if (e < 0.2) then
		wonPuzzle = true
	end

	local tries = readData(playerID .. ":ampPuzzle:tries")
	local maxTries = readData(playerID .. ":ampPuzzle:maxTries")

	tries = tries - 1

	local integrity = math.floor((tries / maxTries) * 100)

	if (wonPuzzle or tries <= 0) then
		suiPageData:subscribeToEvent(SuiEventType.SET_onButton, "btnOk", "SuiAmpPuzzle:noCallback")
		suiPageData:setProperty("top.sliders.1.slider", "GetsInput", "false")
		suiPageData:setProperty("top.sliders.2.slider", "GetsInput", "false")
		suiPageData:setProperty("top.sliders.3.slider", "GetsInput", "false")
		suiPageData:setProperty("btnOk", "Visible", "false")

		if (wonPuzzle) then
			LuaFsCraftingComponentObject(pPuzzle):setStatus(1)
			suiPageData:setProperty("description.desc", "Text", "@quest/force_sensitive/fs_crafting:sui_calibration_success")
		else
			LuaFsCraftingComponentObject(pPuzzle):setStatus(-1)
			suiPageData:setProperty("description.desc", "Text", "@quest/force_sensitive/fs_crafting:sui_calibration_failure")
			suiPageData:setProperty("description.attempts", "Text", "@quest/force_sensitive/fs_crafting:sui_attempts_remaining" .. " " .. integrity .. "%")
		end

		self:doDataCleanup(pPlayer)
	else
		suiPageData:setProperty("description.attempts", "Text", "@quest/force_sensitive/fs_crafting:sui_attempts_remaining" .. " " .. integrity .. "%")
		writeData(playerID .. ":ampPuzzle:tries", tries)
	end

	suiPageData:sendUpdateTo(pPlayer)
end

function SuiAmpPuzzle:doDataCleanup(pPlayer)
	local playerID = SceneObject(pPlayer):getObjectID()

	deleteData(playerID .. ":ampPuzzle:tries")
	deleteData(playerID .. ":ampPuzzle:maxTries")

	for i = 1, 3, 1 do
		deleteData(playerID .. ":ampPuzzle:sliderPos" .. i)
		deleteData(playerID .. ":ampPuzzle:coefficient" .. i)
		deleteData(playerID .. ":ampPuzzle:bar" .. i)
	end

	for i = 1, 7, 1 do
		deleteData(playerID .. ":ampPuzzle:serverBarVal" .. i)
	end

	deleteData(playerID .. ":ampPuzzle:Pid")
end
