local ObjectManager = require("managers.object.object_manager")

SuiReceiverPuzzle = {}
function SuiReceiverPuzzle:openPuzzle(pPlayer, pPuzzle, pCalibrator)
	local sui = SuiCalibrationGame3.new("SuiReceiverPuzzle", "defaultCallback")
	local playerID = SceneObject(pPlayer):getObjectID()
	writeData(playerID .. ":calibratorComponentID", SceneObject(pPuzzle):getObjectID())

	sui.setTargetNetworkId(SceneObject(pCalibrator):getObjectID())
	sui.setForceCloseDistance(10)

	local goal = { 0, 0, 0 }
	local current = { 0, 0, 0 }
	local tries = 10

	for i = 1, 3, 1 do
		goal[i] = getRandomNumber(0, 100)
		writeData(playerID .. ":receiverPuzzle:goal" .. i, goal[i])

		sui.setProperty("top.sliders." .. i .. ".slider", "Value", "100")

		local pct = goal[i] / 100
		local dec = math.floor(255 * pct)
		local hex = self:num2hex(dec)

		if (string.len(hex) == 1) then
			hex = "0" .. hex
		end

		local hexValue = "#" .. hex .. hex .. hex
		sui.setProperty("top.bars.server." .. i, "Color", hexValue)
	end

	writeData(playerID .. ":receiverPuzzle:tries", tries)
	writeData(playerID .. ":receiverPuzzle:maxTries", tries)

	sui.setSliderTitle(1, "@quest/force_sensitive/fs_crafting:sui_gyro_slider1")
	sui.setSliderTitle(2, "@quest/force_sensitive/fs_crafting:sui_gyro_slider2")
	sui.setSliderTitle(3, "@quest/force_sensitive/fs_crafting:sui_gyro_slider3")

	sui.setTitle("@quest/force_sensitive/fs_crafting:sui_gyro_title")
	sui.setDescription("@quest/force_sensitive/fs_crafting:sui_gyro_description")
	sui.setAttemptsDesc("@quest/force_sensitive/fs_crafting:sui_attempts_remaining" .. " 100%")

	sui.subscribeToEvent(SuiEventType.SET_onButton, "btnOk", "SuiReceiverPuzzle:defaultCallback")

	sui.subscribeToPropertyForEvent(SuiEventType.SET_onButton, "top.sliders.1.slider", "Value")
	sui.subscribeToPropertyForEvent(SuiEventType.SET_onButton, "top.sliders.2.slider", "Value")
	sui.subscribeToPropertyForEvent(SuiEventType.SET_onButton, "top.sliders.3.slider", "Value")

	local pageId = sui.sendTo(pPlayer)
	writeData(playerID .. ":receiverPuzzle:Pid", pageId)
end

function SuiReceiverPuzzle:defaultCallback(pPlayer, pSui, eventIndex, ...)
	local pGhost = CreatureObject(pPlayer):getPlayerObject()

	if (pGhost == nil) then
		return
	end

	local cancelPressed = (eventIndex == 1)
	local playerID = SceneObject(pPlayer):getObjectID()
	local pageId = readData(playerID .. ":receiverPuzzle:Pid")

	if (pageId == 0) then
		return
	end

	local pPageData = LuaSuiBoxPage(pSui):getSuiPageData()

	if (pPageData == nil) then
		printLuaError("SuiReceiverPuzzle:defaultCallback, pageData is nil.")
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
		printLuaError("SuiReceiverPuzzle:defaultCallback, pPuzzle nil.")
		return
	end

	local pInventory = CreatureObject(pPlayer):getSlottedObject("inventory")

	if pInventory == nil or SceneObject(pPuzzle):getParentID() ~= SceneObject(pInventory):getObjectID() then
		return
	end

	PlayerObject(pGhost):addSuiBox(pSui)

	local args = {...}
	local goal = { }
	local current = { }
	local tries = readData(playerID .. ":receiverPuzzle:tries")
	local maxTries = readData(playerID .. ":receiverPuzzle:maxTries")

	local wonPuzzle = true

	for i = 1, 3, 1 do
		goal[i] = readData(playerID .. ":receiverPuzzle:goal" .. i)
		current[i] = args[i]

		suiPageData:setProperty("top.sliders." .. i .. ".slider", "Value", "" .. current[i])

		local delta = goal[i] - current[i]

		if (delta > 5 or delta < -5) then
			wonPuzzle = false
		end

		local pct = current[i] / 100
		local dec = math.floor(255 * pct)
		local hex = self:num2hex(dec)

		if (string.len(hex) == 1) then
			hex = "0" .. hex
		end

		local hexValue = "#" .. hex .. hex .. hex
		suiPageData:setProperty("top.bars.player." .. i, "Color", hexValue)

		pct = goal[i] / 100
		dec = math.floor(255 * pct)
		hex = self:num2hex(dec)

		if (string.len(hex) == 1) then
			hex = "0" .. hex
		end

		local hexValue = "#" .. hex .. hex .. hex
		suiPageData:setProperty("top.bars.server." .. i, "Color", hexValue)
	end

	tries = tries - 1
	local integrity = (tries / maxTries) * 100

	if (wonPuzzle or tries <= 0) then
		suiPageData:subscribeToEvent(SuiEventType.SET_onButton, "btnOk", "SuiReceiverPuzzle:noCallback")
		suiPageData:setProperty("top.sliders.1.slider", "GetsInput", "false")
		suiPageData:setProperty("top.sliders.2.slider", "GetsInput", "false")
		suiPageData:setProperty("top.sliders.3.slider", "GetsInput", "false")
		suiPageData:setProperty("btnOk", "Visible", "false")

		if (wonPuzzle) then
			LuaFsCraftingComponentObject(pPuzzle):setStatus(1)
			suiPageData:setProperty("description.desc", "Text", "@quest/force_sensitive/fs_crafting:sui_calibration_success")

			for i = 1, 3, 1 do
				local pct = current[i] / 100
				local dec = math.floor(255 * pct)
				local hex = self:num2hex(dec)

				if (string.len(hex) == 1) then
					hex = "0" .. hex
				end

				local hexValue = "#" .. hex .. hex .. hex
				suiPageData:setProperty("top.bars.server." .. i, "Color", hexValue)
				suiPageData:setProperty("top.bars.player." .. i, "Color", hexValue)
			end

		else
			LuaFsCraftingComponentObject(pPuzzle):setStatus(-1)
			suiPageData:setProperty("description.desc", "Text", "@quest/force_sensitive/fs_crafting:sui_calibration_failure")
			suiPageData:setProperty("description.attempts", "Text", "@quest/force_sensitive/fs_crafting:sui_attempts_remaining" .. " " .. integrity .. "%")
		end

		self:doDataCleanup(pPlayer)
	else
		suiPageData:setProperty("description.attempts", "Text", "@quest/force_sensitive/fs_crafting:sui_attempts_remaining" .. " " .. integrity .. "%")
		writeData(playerID .. ":receiverPuzzle:tries", tries)
	end

	suiPageData:sendUpdateTo(pPlayer)
end

function SuiReceiverPuzzle:doDataCleanup(pPlayer)
	local playerID = SceneObject(pPlayer):getObjectID()

	deleteData(playerID .. ":receiverPuzzle:tries")
	deleteData(playerID .. ":receiverPuzzle:maxTries")

	for i = 1, 3, 1 do
		deleteData(playerID .. ":receiverPuzzle:goal" .. i)
	end

	deleteData(playerID .. ":receiverPuzzle:Pid")
end


function SuiReceiverPuzzle:num2hex(num)
	local hexstr = '0123456789abcdef'
	local s = ''
	while num > 0 do
		local mod = math.fmod(num, 16)
		s = string.sub(hexstr, mod+1, mod+1) .. s
		num = math.floor(num / 16)
	end
	if s == '' then s = '0' end
	return s
end
