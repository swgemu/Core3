local ObjectManager = require("managers.object.object_manager")

SuiRadiationSensor = {}
function SuiRadiationSensor:openSensor(pCreatureObject, pSensor)
	local sui = SuiQuestPopup.new()

	-- Default callback for ok and cancel, must always be called before subscribing to any other events
	sui.setDefaultCallback("SuiRadiationSensor", "defaultCallback")

	-- Using object ID, stored in PageData
	if (pSensor == nil) then
		sui.setTargetNetworkId(0)
	else
		sui.setTargetNetworkId(SceneObject(pCreatureObject):getObjectID())
	end

	sui.setForceCloseDistance(0)

	-- Not needed as OK button is subscribed by default callback above
	-- sui.subscribeToEvent(SuiEventType.SET_onClosedOk, "", "SuiSample:eventCallback")

	sui.setTitle("Radiation Sensor")
	sui.setPrompt("\n\nEnemy Threat Level:  Detecting...")
	sui.setViewerObjectId(SceneObject(pSensor):getObjectID())

	local pageId = sui.sendTo(pCreatureObject)
	writeData(SceneObject(pCreatureObject):getObjectID() .. ":radiationSensorPid", pageId)

	createEvent(3 * 1000, "SuiRadiationSensor", "updateSensor", pCreatureObject, "")
end

function SuiRadiationSensor:defaultCallback(pPlayer, pSui, eventIndex, args)
	deleteData(SceneObject(pPlayer):getObjectID() .. ":radiationSensorPid")
end

function SuiRadiationSensor:updateSensor(pCreature)
	if (pCreature == nil) then
		return
	end

	local playerID = SceneObject(pCreature):getObjectID()
	local sensorPid = readData(playerID .. ":radiationSensorPid")

	if (sensorPid == 0) then
		return
	end

	local pBox

	ObjectManager.withCreaturePlayerObject(pCreature, function(playerObject)
		pBox = playerObject:getSuiBox(sensorPid)
	end)

	if (pBox == nil) then
		printf("Error in SuiRadiationSensor:updateSensor, suiBox is nil.\n")
		return
	end

	local pPageData = LuaSuiBoxPage(pBox):getSuiPageData()

	if (pPageData == nil) then
		printf("Error in SuiRadiationSensor:updateSensor, pageData is nil.\n")
		return
	end

	local suiPageData = LuaSuiPageData(pPageData)

	local targetLoc = self:getLocation(pCreature)

	if (targetLoc[1] == 0 and targetLoc[2] == 0) then
		suiPageData:setProperty("comp.info.text", "Text", "\n\nEnemy Threat Level: \n\\#ff0000 -No tracking device detected-")
		suiPageData:sendUpdateTo(pCreature)
		return
	end

	if (SceneObject(pCreature):getZoneName() ~= targetLoc[3]) then
		suiPageData:setProperty("comp.info.text", "Text", "\\#ff0000 \n\nNo Signal")
		suiPageData:sendUpdateTo(pCreature)
		return
	end

	local curX = SceneObject(pCreature):getWorldPositionX()
	local curY = SceneObject(pCreature):getWorldPositionY()

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

		local newDistance = self:calculateSensorResult(pCreature)

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

	suiPageData:sendUpdateTo(pCreature)
	createEvent(3 * 1000, "SuiRadiationSensor", "updateSensor", pCreature, "")

end

function SuiRadiationSensor:hasSensor(pCreature)
	local pSensor = self:getSensor(pCreature)

	return pSensor ~= nil
end

function SuiRadiationSensor:getSensor(pCreature)
	local pDatapad = SceneObject(pCreature):getSlottedObject("datapad")

	if (pDatapad == nil) then
		return nil
	end

	local pSensor = getContainerObjectByTemplate(pDatapad, "object/intangible/data_item/data_geiger_counter.iff", false)

	return pSensor
end

function SuiRadiationSensor:giveSensor(pCreature)
	if (pCreature == nil or self:hasSensor(pCreature)) then
		return
	end

	local pDatapad = SceneObject(pCreature):getSlottedObject("datapad")

	if (pDatapad == nil) then
		return
	end

	local pSensor = giveItem(pDatapad, "object/intangible/data_item/data_geiger_counter.iff", -1)
	writeData(SceneObject(pCreature):getObjectID() .. ":radiationSensorFactor", getRandomNumber(3,7))

	CreatureObject(pCreature):sendSystemMessage("@system_msg:new_datapad_device")
end

function SuiRadiationSensor:removeSensor(pCreature)
	local pSensor = self:getSensor(pCreature)

	if (pSensor ~= nil) then
		local sensorID = SceneObject(pSensor):getObjectID()

		deleteData(sensorID .. ":locX")
		deleteData(sensorID .. ":locY")
		deleteStringSharedMemory(sensorID .. ":locPlanet")

		SceneObject(pSensor):destroyObjectFromWorld()
		SceneObject(pSensor):destroyObjectFromDatabase()
	end

	local playerID = SceneObject(pCreature):getObjectID()

	deleteData(playerID .. ":radiationSensorFactor")
	deleteStringSharedMemory(playerID .. ":radiationSensor:lastDistance")
	deleteData(playerID .. ":radiationSensorPid")
end

function SuiRadiationSensor:setLocation(pCreature, x, y, planet)
	local pSensor = self:getSensor(pCreature)

	if (pSensor == nil) then
		return
	end

	local sensorID = SceneObject(pSensor):getObjectID()

	writeData(sensorID .. ":locX", x)
	writeData(sensorID .. ":locY", y)
	writeStringSharedMemory(sensorID .. ":locPlanet", planet)
end

function SuiRadiationSensor:getLocation(pCreature)
	local pSensor = self:getSensor(pCreature)

	if (pSensor == nil) then
		return { 0, 0, "" }
	end

	local sensorID = SceneObject(pSensor):getObjectID()

	return { readData(sensorID .. ":locX"), readData(sensorID .. ":locY"), readStringSharedMemory(sensorID .. ":locPlanet") }
end

function SuiRadiationSensor:calculateSensorResult(pCreature)
	local curX = SceneObject(pCreature):getWorldPositionX()
	local curY = SceneObject(pCreature):getWorldPositionY()

	local targetLoc = self:getLocation(pCreature)

	local sensorFactor = readData(SceneObject(pCreature):getObjectID() .. ":radiationSensorFactor")

	if (sensorFactor == 0) then
		sensorFactor = getRandomNumber(3,7)
		writeData(SceneObject(pCreature):getObjectID() .. ":radiationSensorFactor", sensorFactor)
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

function SuiRadiationSensor:instructionsCallback(pCreature)
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
