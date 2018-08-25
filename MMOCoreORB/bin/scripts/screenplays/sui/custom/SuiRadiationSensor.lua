local ObjectManager = require("managers.object.object_manager")

SuiRadiationSensor = {}
function SuiRadiationSensor:openSensor(pPlayer, pSensor)
	local sui = SuiQuestPopup.new()

	-- Default callback for ok and cancel, must always be called before subscribing to any other events
	sui.setDefaultCallback("SuiRadiationSensor", "defaultCallback")

	-- Using object ID, stored in PageData
	if (pSensor == nil) then
		sui.setTargetNetworkId(0)
	else
		sui.setTargetNetworkId(SceneObject(pPlayer):getObjectID())
	end

	sui.setForceCloseDistance(0)

	-- Not needed as OK button is subscribed by default callback above
	-- sui.subscribeToEvent(SuiEventType.SET_onClosedOk, "", "SuiSample:eventCallback")

	sui.setTitle("Radiation Sensor")
	sui.setPrompt("\n\nEnemy Threat Level:  Detecting...")
	sui.setViewerObjectId(SceneObject(pSensor):getObjectID())

	local pageId = sui.sendTo(pPlayer)
	writeData(SceneObject(pPlayer):getObjectID() .. ":radiationSensorPid", pageId)

	createEvent(3 * 1000, "SuiRadiationSensor", "updateSensor", pPlayer, "")
end

function SuiRadiationSensor:defaultCallback(pPlayer, pSui, eventIndex, args)
	deleteData(SceneObject(pPlayer):getObjectID() .. ":radiationSensorPid")
end

function SuiRadiationSensor:updateSensor(pPlayer)
	if (pPlayer == nil) then
		return
	end

	local pGhost = CreatureObject(pPlayer):getPlayerObject()

	if (pGhost == nil) then
		return
	end

	local playerID = SceneObject(pPlayer):getObjectID()
	local sensorPid = readData(playerID .. ":radiationSensorPid")

	if (sensorPid == 0) then
		return
	end

	local pBox = PlayerObject(pGhost):getSuiBox(sensorPid)

	if (pBox == nil) then
		printLuaError("SuiRadiationSensor:updateSensor, suiBox is nil.")
		return
	end

	local pPageData = LuaSuiBoxPage(pBox):getSuiPageData()

	if (pPageData == nil) then
		printLuaError("SuiRadiationSensor:updateSensor, pageData is nil.")
		return
	end

	local suiPageData = LuaSuiPageData(pPageData)

	local targetLoc = self:getLocation(pPlayer)

	if (targetLoc[1] == 0 and targetLoc[2] == 0) then
		suiPageData:setProperty("comp.info.text", "Text", "\n\nEnemy Threat Level: \n\\#ff0000 -No tracking device detected-")
		suiPageData:sendUpdateTo(pPlayer)
		return
	end

	if (SceneObject(pPlayer):getZoneName() ~= targetLoc[3]) then
		suiPageData:setProperty("comp.info.text", "Text", "\\#ff0000 \n\nNo Signal")
		suiPageData:sendUpdateTo(pPlayer)
		return
	end

	local curX = SceneObject(pPlayer):getWorldPositionX()
	local curY = SceneObject(pPlayer):getWorldPositionY()

	local distance = math.sqrt(((curX - targetLoc[1]) ^ 2) + ((curY - targetLoc[2]) ^ 2))
	local variance = getRandomNumber(500, 1000)

	if (distance > 4500 + variance) then
		suiPageData:setProperty("comp.info.text", "Text", "\\#ff0000 \n\nWeak Signal")
	elseif (distance <= 64) then
		suiPageData:setProperty("comp.info.text", "Text", "\\#0000ff \n\nSignal Peak. Target within 64 meters.")
	else
		local lastDistance = tonumber(readStringSharedMemory(playerID .. ":radiationSensor:lastDistance"))

		if (lastDistance == nil) then
			lastDistance = 0
		end

		local newDistance = self:calculateSensorResult(pPlayer)

		lastDistance = self:round(lastDistance, 8)
		newDistance = self:round(newDistance, 8)
		local distDiff = newDistance - lastDistance

		if (lastDistance == 0) then
			distDiff = 0
		end

		if (distDiff == 0) then
			suiPageData:setProperty("comp.info.text", "Text", "\n\nEnemy Threat Level: " .. newDistance .. "\nDelta: 0.  You are not moving.")
		else
			local newString = "\n\nEnemy Threat Level: " .. newDistance .. "\nDelta: "
			if (distDiff > 0) then
				newString = newString .. "\\#00ff00 Moving closer \n "
			else
				newString = newString .. "\\#ff0000 Moving away \n "
			end

			newString = newString .. distDiff
			suiPageData:setProperty("comp.info.text", "Text", newString)
		end

		writeStringSharedMemory(playerID .. ":radiationSensor:lastDistance", newDistance)
	end

	suiPageData:sendUpdateTo(pPlayer)
	createEvent(3 * 1000, "SuiRadiationSensor", "updateSensor", pPlayer, "")

end

function SuiRadiationSensor:hasSensor(pPlayer)
	local pSensor = self:getSensor(pPlayer)

	return pSensor ~= nil
end

function SuiRadiationSensor:getSensor(pPlayer)
	local pDatapad = SceneObject(pPlayer):getSlottedObject("datapad")

	if (pDatapad == nil) then
		return nil
	end

	local pSensor = getContainerObjectByTemplate(pDatapad, "object/intangible/data_item/data_geiger_counter.iff", false)

	return pSensor
end

function SuiRadiationSensor:giveSensor(pPlayer)
	if (pPlayer == nil) then
		return
	end
	
	if (self:hasSensor(pPlayer)) then
		self:removeSensor(pPlayer)
	end

	local pDatapad = SceneObject(pPlayer):getSlottedObject("datapad")

	if (pDatapad == nil) then
		return
	end

	local pSensor = giveItem(pDatapad, "object/intangible/data_item/data_geiger_counter.iff", -1)

	if (pSensor ~= nil) then
		writeData(SceneObject(pPlayer):getObjectID() .. ":radiationSensorFactor", getRandomNumber(3,7))
		CreatureObject(pPlayer):sendSystemMessage("@system_msg:new_datapad_device")

		SceneObject(pSensor):setContainerInheritPermissionsFromParent(false)
		SceneObject(pSensor):clearContainerDefaultDenyPermission(MOVECONTAINER)
		SceneObject(pSensor):setContainerDefaultAllowPermission(MOVECONTAINER)
	else
		CreatureObject(pPlayer):sendSystemMessage("Error: Unable to create radiation sensor. Please bug report.")
	end
end

function SuiRadiationSensor:removeSensor(pPlayer)
	local pSensor = self:getSensor(pPlayer)

	if (pSensor ~= nil) then
		local sensorID = SceneObject(pSensor):getObjectID()

		deleteData(sensorID .. ":locX")
		deleteData(sensorID .. ":locY")
		deleteStringSharedMemory(sensorID .. ":locPlanet")

		SceneObject(pSensor):destroyObjectFromWorld()
		SceneObject(pSensor):destroyObjectFromDatabase()
	end

	local playerID = SceneObject(pPlayer):getObjectID()

	deleteData(playerID .. ":radiationSensorFactor")
	deleteStringSharedMemory(playerID .. ":radiationSensor:lastDistance")
	deleteData(playerID .. ":radiationSensorPid")
end

function SuiRadiationSensor:unsetLocation(pPlayer)
	local pSensor = self:getSensor(pPlayer)

	if (pSensor ~= nil) then
		local sensorID = SceneObject(pSensor):getObjectID()

		deleteData(sensorID .. ":locX")
		deleteData(sensorID .. ":locY")
		deleteStringSharedMemory(sensorID .. ":locPlanet")
	end
end

function SuiRadiationSensor:setLocation(pPlayer, x, y, planet)
	local pSensor = self:getSensor(pPlayer)

	if (pSensor == nil) then
		return
	end

	local sensorID = SceneObject(pSensor):getObjectID()

	writeData(sensorID .. ":locX", math.floor(x))
	writeData(sensorID .. ":locY", math.floor(y))
	writeStringSharedMemory(sensorID .. ":locPlanet", planet)
end

function SuiRadiationSensor:getLocation(pPlayer)
	local pSensor = self:getSensor(pPlayer)

	if (pSensor == nil) then
		return { 0, 0, "" }
	end

	local sensorID = SceneObject(pSensor):getObjectID()

	return { readData(sensorID .. ":locX"), readData(sensorID .. ":locY"), readStringSharedMemory(sensorID .. ":locPlanet") }
end

function SuiRadiationSensor:calculateSensorResult(pPlayer)
	local curX = SceneObject(pPlayer):getWorldPositionX()
	local curY = SceneObject(pPlayer):getWorldPositionY()

	local targetLoc = self:getLocation(pPlayer)

	local sensorFactor = readData(SceneObject(pPlayer):getObjectID() .. ":radiationSensorFactor")

	if (sensorFactor == 0) then
		sensorFactor = getRandomNumber(3,7)
		writeData(SceneObject(pPlayer):getObjectID() .. ":radiationSensorFactor", sensorFactor)
	end

	local distance = math.sqrt(((curX - targetLoc[1]) ^ 2) + ((curY - targetLoc[2]) ^ 2))
	distance = 5000 - distance
	local result

	if (sensorFactor % 2 == 1) then
		result = distance / sensorFactor
	else
		result = math.sqrt(distance / sensorFactor) * 100
	end

	return result
end

function SuiRadiationSensor:round(num, idp)
	local mult = 10^(idp)
	return math.floor(num * mult + 0.5) / mult
end

function SuiRadiationSensor:instructionsCallback(pPlayer)
end

radiationSensorMenuComponent = { }

function radiationSensorMenuComponent:fillObjectMenuResponse(pSceneObject, pMenuResponse, pPlayer)
	local menuResponse = LuaObjectMenuResponse(pMenuResponse)

	menuResponse:addRadialMenuItem(20, 3, "@ui_radial:item_use") -- Use
	menuResponse:addRadialMenuItem(120, 3, "@quest/quest_journal/fs_quests_sad:instructions_title") -- Instructions
end

function radiationSensorMenuComponent:handleObjectMenuSelect(pObject, pPlayer, selectedID)
	if (pPlayer == nil or pObject == nil) then
		return 0
	end

	if (selectedID == 120) then
		local suiManager = LuaSuiManager()
		suiManager:sendMessageBox(pObject, pPlayer, "@quest/quest_journal/fs_quests_sad:instructions_title", "@quest/quest_journal/fs_quests_sad:instructions_text", "@ok", "SuiRadiationSensor", "instructionsCallback")
	elseif (selectedID == 20) then
		SuiRadiationSensor:openSensor(pPlayer, pObject)
	end

	return 0
end
