FireworkEvent = {
	promptBody = {
		"How long would you like the main event to last in seconds? (This cannot be 0, and does not include the finale at the end)",
		"How many fireworks would you like to fire during the main event? (This cannot be 0, and will automatically be spread out over the course of the event length)",
		"How long would you like the finale to last in seconds? (This can be set to 0 if no finale is needed. The finale will trigger after the main event ends)",
		"How many fireworks would you like to fire during the finale? (This can be set to 0 if no finale is needed. Fireworks will be spread our over the course of the finale length)",
		"Move to the location where you'd like the firework event to be staged and type \"here\" in the box to set it.",
		"How big of a radius around the staging point would you like the fireworks to launch in? (5-10 or more is good to make sure they dont spawn on top of each other)",
	},

	promptTitle = { "Main Event Length", "Main Event Firework Count", "Finale Length", "Finale Firework Count", "Staging Point", "Launch Radius" },

	fireworkTemplates = {
		"object/static/firework/fx_01.iff",
		"object/static/firework/fx_02.iff",
		"object/static/firework/fx_03.iff",
		"object/static/firework/fx_04.iff",
		"object/static/firework/fx_05.iff",
		"object/static/firework/fx_10.iff",
		"object/static/firework/fx_11.iff",
		"object/static/firework/fx_18.iff",
	},

	removeDelay = 20 * 1000, -- How long before a launched firework is removed from the world
	eventWarmup = 5 * 1000, -- Amount of time before event begins after its triggered
}

function FireworkEvent:showMainUI(pPlayer)
	local sui = SuiInputBox.new("FireworkEvent", "suiFireworkEventMainCallback")

	sui.setTargetNetworkId(SceneObject(pPlayer):getObjectID())

	local suiBody = "Enter \"setup\" to setup event, \"data\" to view current event data, \"quit\" to end. After setup type \"begin\" to begin the event."
	sui.setTitle("Firework Event Information")
	sui.setPrompt(suiBody)

	sui.sendTo(pPlayer)
end

function FireworkEvent:suiFireworkEventMainCallback(pPlayer, pSui, eventIndex, args)
	local cancelPressed = (eventIndex == 1)

	if (cancelPressed) then
		return
	end

	local playerID = SceneObject(pPlayer):getObjectID()
	local eventID = readData(playerID .. ":FireworkEvent:eventID")
	local pEvent = getSceneObject(eventID)

	if (args == "setup") then
		if (pEvent ~= nil) then
			CreatureObject(pPlayer):sendSystemMessage("Error: An event already exists. Use \"quit\" to destroy the existing event before running \"setup\" again. Warning, this will end a current event in progress.")
		else
			self:resetDefaults(pPlayer)
			writeData(playerID .. ":FireworkEvent:setupStep", 1)
			self:showSetupUI(pPlayer)
			return
		end
	elseif (args == "data") then
		local mainLength = readData(playerID .. ":FireworkEvent:mainEventLength")
		local mainCount = readData(playerID .. ":FireworkEvent:mainEventCount")
		local finaleLength = readData(playerID .. ":FireworkEvent:finaleLength")
		local finaleCount = readData(playerID .. ":FireworkEvent:finaleCount")

		if (mainLength == 0 or mainCount == 0) then
			CreatureObject(pPlayer):sendSystemMessage("No event data found. Run setup first.")
		else
			local mainPer = mainLength / mainCount
			local dataString = "Firework Event: Main event: " .. mainLength .. " seconds, " .. mainCount .. " fireworks (1 firework every " .. mainPer .. " seconds). "

			if (finaleLength > 0 and finaleCount > 0) then
				local finalePer = finaleLength / finaleCount
				dataString = dataString .. "Finale: " .. finaleLength .. " seconds, " .. finaleCount .. " fireworks (1 firework every " .. finalePer .. " seconds). "
			else
				dataString = dataString .. " No finale data."
			end
			CreatureObject(pPlayer):sendSystemMessage(dataString)
		end
	elseif (args == "quit") then
		self:destroyEvent(pPlayer)
		self:resetDefaults(pPlayer)
		return
	elseif (args == "begin") then
		if (readData(playerID .. ":FireworkEvent:setupCompleted") ~= 1) then
			CreatureObject(pPlayer):sendSystemMessage("Event setup incomplete. Use \"setup\" to set up the event before triggering it.")
		else
			self:startEvent(pPlayer)
		end
	end

	self:showMainUI(pPlayer)
end

function FireworkEvent:showSetupUI(pPlayer)
	local playerID = SceneObject(pPlayer):getObjectID()
	local curStep = readData(playerID .. ":FireworkEvent:setupStep")

	if (readData(playerID .. ":FireworkEvent:setupCompleted") == 1) then
		self:showMainUI(pPlayer)
		return
	end

	local sui = SuiInputBox.new("FireworkEvent", "suiFireworkEventSetupCallback")

	sui.setTargetNetworkId(SceneObject(pPlayer):getObjectID())

	sui.setTitle(self.promptTitle[curStep])
	sui.setPrompt(self.promptBody[curStep])

	sui.sendTo(pPlayer)
end

function FireworkEvent:suiFireworkEventSetupCallback(pPlayer, pSui, eventIndex, args)
	local cancelPressed = (eventIndex == 1)

	if (cancelPressed) then
		return
	end

	local playerID = SceneObject(pPlayer):getObjectID()
	local curStep = readData(playerID .. ":FireworkEvent:setupStep")
	local numArg = tonumber(args)

	if (curStep == 1) then
		if (numArg <= 0 or numArg > 1800) then
			CreatureObject(pPlayer):sendSystemMessage("Main event length must be greater than 0 and less than 1800 (30 minutes).")
		else
			writeData(playerID .. ":FireworkEvent:setupStep", 2)
			writeData(playerID .. ":FireworkEvent:mainEventLength", numArg)
			CreatureObject(pPlayer):sendSystemMessage("Main Event Length: " .. numArg .. " seconds.")
		end
	elseif (curStep == 2) then
		if (numArg <= 0) then
			CreatureObject(pPlayer):sendSystemMessage("Main event firework count must be greater than 0.")
		else
			writeData(playerID .. ":FireworkEvent:setupStep", 3)
			writeData(playerID .. ":FireworkEvent:mainEventCount", numArg)
			CreatureObject(pPlayer):sendSystemMessage("Main Event Count: " .. numArg .. " fireworks.")
		end
	elseif (curStep == 3) then
		if (numArg > 300) then
			CreatureObject(pPlayer):sendSystemMessage("Finale length must be less than 300 (10 minutes).")
		elseif (numArg >= 0) then
			if (numArg == 0) then
				writeData(playerID .. ":FireworkEvent:setupStep", 5)
			else
				writeData(playerID .. ":FireworkEvent:setupStep", 4)
			end

			writeData(playerID .. ":FireworkEvent:finaleLength", numArg)
			CreatureObject(pPlayer):sendSystemMessage("Finale Length: " .. numArg .. " seconds.")
		end
	elseif (curStep == 4) then
		if (numArg > 0) then
			writeData(playerID .. ":FireworkEvent:setupStep", 5)
			writeData(playerID .. ":FireworkEvent:finaleCount", numArg)
			CreatureObject(pPlayer):sendSystemMessage("Finale Count: " .. numArg .. " fireworks.")
		end
	elseif (curStep == 5) then
		if (args == "here") then
			if (SceneObject(pPlayer):getParentID() ~= 0) then
				CreatureObject(pPlayer):sendSystemMessage("ERROR: You must be outside to set a staging area.")
			else
				writeData(playerID .. ":FireworkEvent:spawnPointX", math.floor(SceneObject(pPlayer):getWorldPositionX()))
				writeData(playerID .. ":FireworkEvent:spawnPointZ", math.floor(SceneObject(pPlayer):getWorldPositionZ()))
				writeData(playerID .. ":FireworkEvent:spawnPointY", math.floor(SceneObject(pPlayer):getWorldPositionY()))
				writeStringData(playerID .. ":FireworkEvent:spawnPlanet", SceneObject(pPlayer):getZoneName())
				writeData(playerID .. ":FireworkEvent:heading", math.floor(SceneObject(pPlayer):getDirectionAngle()))
				CreatureObject(pPlayer):sendSystemMessage("Staging Area: Set to your current location and direction.")
				writeData(playerID .. ":FireworkEvent:setupStep", 6)
			end
		else
			CreatureObject(pPlayer):sendSystemMessage("You must stand where you want the firework event to be staged and type \"here\" in the input box.")
		end
	elseif (curStep == 6) then
		if (numArg < 0) then
			CreatureObject(pPlayer):sendSystemMessage("Launch radius must be greater than or equal to 0.")
		else
			writeData(playerID .. ":FireworkEvent:launchRadius", numArg)
			writeData(playerID .. ":FireworkEvent:setupCompleted", 1)
			CreatureObject(pPlayer):sendSystemMessage("Launch radius: " .. numArg .. " meters.")
		end
	end

	self:showSetupUI(pPlayer)
end


function FireworkEvent:startEvent(pPlayer)
	CreatureObject(pPlayer):sendSystemMessage("Firework event has been triggered, and will begin in " .. (self.eventWarmup / 1000) .. " seconds.")
	local playerID = SceneObject(pPlayer):getObjectID()

	local mainLength = readData(playerID .. ":FireworkEvent:mainEventLength")
	local mainCount = readData(playerID .. ":FireworkEvent:mainEventCount")
	local finaleLength = readData(playerID .. ":FireworkEvent:finaleLength")
	local finaleCount = readData(playerID .. ":FireworkEvent:finaleCount")

	writeData(playerID .. ":FireworkEvent:mainEventCountLeft", mainCount)
	writeData(playerID .. ":FireworkEvent:finaleCountLeft", finaleCount)
	writeData(playerID .. ":FireworkEvent:mainEventDelay", mainLength / mainCount)

	if (finaleCount > 0 and finaleLength > 0) then
		writeData(playerID .. ":FireworkEvent:mainEventDelay", finaleLength / finaleCount)
	end

	local heading = readData(playerID .. ":FireworkEvent:heading")
	local x = readData(playerID .. ":FireworkEvent:spawnPointX")
	local z = readData(playerID .. ":FireworkEvent:spawnPointZ")
	local y = readData(playerID .. ":FireworkEvent:spawnPointY")
	local planet = readStringData(playerID .. ":FireworkEvent:spawnPlanet")

	local pControl = spawnSceneObject(planet, "object/tangible/theme_park/invisible_object.iff", x, z, y, 0, heading)

	if (pControl == nil) then
		self:resetDefaults(pPlayer)
		CreatureObject(pPlayer):sendSystemMessage("Error creating firework event control object.")
		return
	end

	local controlID = SceneObject(pControl):getObjectID()
	writeData(playerID .. ":FireworkEvent:eventID", controlID)
	writeData(controlID .. ":FireworkEvent:ownerID", playerID)
	createEvent(self.eventWarmup, "FireworkEvent", "spawnFirework", pControl, "")
end

function FireworkEvent:spawnFirework(pControl)
	if (pControl == nil) then
		return
	end

	local playerID = readData(SceneObject(pControl):getObjectID() .. ":FireworkEvent:ownerID")

	local heading = readData(playerID .. ":FireworkEvent:heading")
	local x = readData(playerID .. ":FireworkEvent:spawnPointX")
	local z = readData(playerID .. ":FireworkEvent:spawnPointZ")
	local y = readData(playerID .. ":FireworkEvent:spawnPointY")
	local planet = readStringData(playerID .. ":FireworkEvent:spawnPlanet")
	local radius = readData(playerID .. ":FireworkEvent:launchRadius")

	local xOffset = (-1 * radius) + getRandomNumber(radius * 2)
	local yOffset = (-1 * radius) + getRandomNumber(radius * 2)

	x = x + xOffset
	y = y + yOffset

	local randFirework = getRandomNumber(1, #self.fireworkTemplates)

	local pFirework = spawnSceneObject(planet, self.fireworkTemplates[randFirework], x, z, y, 0, heading)

	if (pFirework == nil) then
		return
	end

	createEvent(self.removeDelay, "FireworkEvent", "destroyFirework", pFirework, "")

	local mainLength = readData(playerID .. ":FireworkEvent:mainEventLength")
	local mainCount = readData(playerID .. ":FireworkEvent:mainEventCount")
	local mainCountLeft = readData(playerID .. ":FireworkEvent:mainEventCountLeft")
	local finaleLength = readData(playerID .. ":FireworkEvent:finaleLength")
	local finaleCount = readData(playerID .. ":FireworkEvent:finaleCount")
	local finaleCountLeft = readData(playerID .. ":FireworkEvent:finaleCountLeft")

	if (mainCountLeft > 0) then
		mainCountLeft = mainCountLeft - 1
		writeData(playerID .. ":FireworkEvent:mainEventCountLeft", mainCountLeft)
	elseif (finaleCountLeft > 0) then
		finaleCountLeft = finaleCountLeft - 1
		writeData(playerID .. ":FireworkEvent:finaleCountLeft", finaleCountLeft)
	end

	local delayTilNext

	if (mainCountLeft > 0) then
		delayTilNext = mainLength / mainCount
	elseif (finaleCountLeft > 0) then
		delayTilNext = finaleLength / finaleCount
	else
		return
	end

	createEvent(delayTilNext * 1000, "FireworkEvent", "spawnFirework", pControl, "")
end

function FireworkEvent:resetDefaults(pPlayer)
	local playerID = SceneObject(pPlayer):getObjectID()

	deleteData(playerID .. ":FireworkEvent:setupStep")
	deleteData(playerID .. ":FireworkEvent:setupCompleted")
	deleteData(playerID .. ":FireworkEvent:mainEventLength")
	deleteData(playerID .. ":FireworkEvent:mainEventCount")
	deleteData(playerID .. ":FireworkEvent:mainEventLeft")
	deleteData(playerID .. ":FireworkEvent:finaleLength")
	deleteData(playerID .. ":FireworkEvent:finaleCount")
	deleteData(playerID .. ":FireworkEvent:finaleCountLeft")
	deleteData(playerID .. ":FireworkEvent:launchRadius")
	deleteData(playerID .. ":FireworkEvent:heading")
	deleteData(playerID .. ":FireworkEvent:spawnPointX")
	deleteData(playerID .. ":FireworkEvent:spawnPointZ")
	deleteData(playerID .. ":FireworkEvent:spawnPointY")

	deleteStringData(playerID .. ":FireworkEvent:spawnPlanet")
end

function FireworkEvent:destroyFirework(pFirework)
	if (pFirework ~= nil) then
		SceneObject(pFirework):destroyObjectFromWorld()
	end
end

function FireworkEvent:destroyEvent(pPlayer)
	local playerID = SceneObject(pPlayer):getObjectID()

	local eventID = readData(playerID .. ":FireworkEvent:eventID")
	local pControl = getSceneObject(eventID)

	if (pControl ~= nil) then
		deleteData(SceneObject(pControl):getObjectID() .. ":FireworkEvent:eventID")
		SceneObject(pControl):destroyObjectFromWorld()
	end

	deleteData(playerID .. ":FireworkEvent:eventID")
end

function FireworkEvent:cleanUp(pPlayer)
	if (pPlayer == nil) then
		return
	end

	self:destroyEvent(pPlayer)
	self:resetDefaults(pPlayer)
end
