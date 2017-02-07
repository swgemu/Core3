local ObjectManager = require("managers.object.object_manager")

SuiArrayPuzzle = {}
function SuiArrayPuzzle:openPuzzle(pPlayer, pPuzzle, pCalibrator)
	local sui = SuiCalibrationGame1.new("SuiArrayPuzzle", "defaultCallback")
	local playerID = SceneObject(pPlayer):getObjectID()
	writeData(playerID .. ":calibratorComponentID", SceneObject(pPuzzle):getObjectID())

	sui.setTargetNetworkId(SceneObject(pCalibrator):getObjectID())
	sui.setForceCloseDistance(10)

	local goal = getRandomNumber(100)
	local cur = { 0, 0, 0, 0, 0 }
	local mod = { 0, 0, 0, 0, 0 }
	local tries = 10

	for i = 1, #cur, 1 do
		cur[i] = getRandomNumber(100)
		mod[i] = getRandomNumber(100)
	end

	sui.setTitle("@quest/force_sensitive/fs_crafting:sui_ssa_title")
	sui.setDescription("@quest/force_sensitive/fs_crafting:sui_ssa_description")
	sui.setAttemptsDesc("@quest/force_sensitive/fs_crafting:sui_attempts_remaining" .. " 100%")

	sui.subscribeToEvent(SuiEventType.SET_onButton, "btnOk", "SuiArrayPuzzle:defaultCallback")

	sui.subscribeToPropertyForEvent(SuiEventType.SET_onButton, "comp.sliders.1.slider", "Value")
	sui.subscribeToPropertyForEvent(SuiEventType.SET_onButton, "comp.sliders.2.slider", "Value")
	sui.subscribeToPropertyForEvent(SuiEventType.SET_onButton, "comp.sliders.3.slider", "Value")
	sui.subscribeToPropertyForEvent(SuiEventType.SET_onButton, "comp.sliders.4.slider", "Value")
	sui.subscribeToPropertyForEvent(SuiEventType.SET_onButton, "comp.sliders.5.slider", "Value")

	sui.setSliderTitle(1, "@quest/force_sensitive/fs_crafting:sui_ssa_slider1")
	sui.setSliderTitle(2, "@quest/force_sensitive/fs_crafting:sui_ssa_slider2")
	sui.setSliderTitle(3, "@quest/force_sensitive/fs_crafting:sui_ssa_slider3")
	sui.setSliderTitle(4, "@quest/force_sensitive/fs_crafting:sui_ssa_slider4")
	sui.setSliderTitle(5, "@quest/force_sensitive/fs_crafting:sui_ssa_slider5")

	local goalTemp = math.floor(20 + (228 * (goal / 100)))

	sui.setProperty("line", "Value", "" .. tostring(goalTemp))

	for i = 1, 5, 1 do
		local pct = cur[i]
		sui.setProperty("comp.sliders." .. i .. ".slider", "Value", tostring(pct))
		pct = pct + mod[i]

		if (pct > 100) then
			pct = pct - 100
		end

		sui.setProperty("comp.bars.bar" .. i .. ".left", "OnRunScript", "sizeX = parent.sizeX * Value / 100.0")
		sui.setProperty("comp.bars.bar" .. i .. ".right", "OnRunScript", "sizeX = parent.sizeX * Value / 100.0\nlocationX = parent.sizeX - sizeX")
		sui.setProperty("comp.bars.bar" .. i .. ".left", "Value", "" .. (pct - 3))
		sui.setProperty("comp.bars.bar" .. i .. ".right", "Value", "" .. (100 - (pct + 3)))
		sui.setProperty("comp.bars.bar" .. i .. ".left", "RunScript", "")
		sui.setProperty("comp.bars.bar" .. i .. ".right", "RunScript", "")
	end

	local pageId = sui.sendTo(pPlayer)

	local playerID = SceneObject(pPlayer):getObjectID()

	writeData(playerID .. ":arrayPuzzle:Pid", pageId)
	writeData(playerID .. ":arrayPuzzle:tries", tries)
	writeData(playerID .. ":arrayPuzzle:maxTries", tries)
	writeData(playerID .. ":arrayPuzzle:goal", goal)

	for i = 1, 5, 1 do
		writeData(playerID .. ":arrayPuzzle:mod" .. i, mod[i])
	end
end

function SuiArrayPuzzle:noCallback(pPlayer, pSui, eventIndex, ...)
end

function SuiArrayPuzzle:defaultCallback(pPlayer, pSui, eventIndex, ...)
	local pGhost = CreatureObject(pPlayer):getPlayerObject()

	if (pGhost == nil) then
		return
	end

	local cancelPressed = (eventIndex == 1)
	local playerID = SceneObject(pPlayer):getObjectID()
	local pageId = readData(playerID .. ":arrayPuzzle:Pid")

	if (pageId == 0) then
		return
	end

	local pPageData = LuaSuiBoxPage(pSui):getSuiPageData()

	if (pPageData == nil) then
		printLuaError("SuiArrayPuzzle:defaultCallback, pageData is nil.")
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
		printLuaError("SuiArrayPuzzle:defaultCallback, pPuzzle nil.")
		return
	end

	local pInventory = CreatureObject(pPlayer):getSlottedObject("inventory")

	if pInventory == nil or SceneObject(pPuzzle):getParentID() ~= SceneObject(pInventory):getObjectID() then
		return
	end

	PlayerObject(pGhost):addSuiBox(pSui)

	local args = {...}

	local current = { 0, 0, 0, 0, 0 }
	local mod = { }

	local playerID = SceneObject(pPlayer):getObjectID()
	local tries = readData(playerID .. ":arrayPuzzle:tries")
	local maxTries = readData(playerID .. ":arrayPuzzle:maxTries")
	local goal = readData(playerID .. ":arrayPuzzle:goal")
	local wonPuzzle = true

	for i = 1, 5, 1 do
		table.insert(mod, i, readData(playerID .. ":arrayPuzzle:mod" .. i))
	end

	for i = 1, #current, 1 do
		current[i] = args[i]
		local pct = current[i] + mod[i]

		if (pct > 100) then
			pct = pct - 100
		end

		local delta = goal - pct

		if (delta < -3 or delta > 2) then
			wonPuzzle = false
		end

		suiPageData:setProperty("comp.sliders." .. i .. ".slider", "Value", tostring(current[i]))
		suiPageData:setProperty("comp.bars.bar" .. i .. ".left", "Value", "" .. (pct - 3))
		suiPageData:setProperty("comp.bars.bar" .. i .. ".right", "Value", "" .. (100 - (pct + 3)))
		suiPageData:setProperty("comp.bars.bar" .. i .. ".left", "RunScript", "")
		suiPageData:setProperty("comp.bars.bar" .. i .. ".right", "RunScript", "")
	end

	tries = tries - 1

	local integrity = math.floor((tries / maxTries) * 100)

	if (wonPuzzle or tries <= 0) then
		suiPageData:subscribeToEvent(SuiEventType.SET_onButton, "btnOk", "SuiArrayPuzzle:noCallback")
		suiPageData:setProperty("comp.sliders.1.slider", "GetsInput", "false")
		suiPageData:setProperty("comp.sliders.2.slider", "GetsInput", "false")
		suiPageData:setProperty("comp.sliders.3.slider", "GetsInput", "false")
		suiPageData:setProperty("comp.sliders.4.slider", "GetsInput", "false")
		suiPageData:setProperty("comp.sliders.5.slider", "GetsInput", "false")
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
		writeData(playerID .. ":arrayPuzzle:tries", tries)
	end

	suiPageData:sendUpdateTo(pPlayer)
end

function SuiArrayPuzzle:doDataCleanup(pPlayer)
	local playerID = SceneObject(pPlayer):getObjectID()

	deleteData(playerID .. ":arrayPuzzle:tries")
	deleteData(playerID .. ":arrayPuzzle:maxTries")
	deleteData(playerID .. ":arrayPuzzle:goal")

	for i = 1, 5, 1 do
		deleteData(playerID .. ":arrayPuzzle:mod" .. i)
	end

	deleteData(playerID .. ":arrayPuzzle:Pid")
end
