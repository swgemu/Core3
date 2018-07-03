ShuttleDropoff = {
	promptBody = {
		"Which shuttle would you like to spawn? (\"lambda\", \"shuttle\", \"transport\", \"theed transport\").",
		"Move to the location where you'd like the shuttle to land and type \"here\" in the box to set its spawn point.",
		"Would you like the shuttle to spawn NPCs upon landing? (\"yes\" or \"no\").",
		"Enter the spawn template name of the NPC (e.g. stormtrooper, nightsister_elder) Note: These will be spawned as event mobs.",
		"Enter the number of NPCs to spawn.",
		"Enter the level of the event NPC's to spawn."
	},

	promptTitle = { "Shuttle Type", "Landing Area", "Spawn NPCs on Landing?", "NPC Template", "Number of NPCs", "NPC Level" },

	shuttleTemplate = {
		"object/creature/npc/theme_park/lambda_shuttle.iff",
		"object/creature/npc/theme_park/player_shuttle.iff",
		"object/creature/npc/theme_park/player_transport.iff",
		"object/creature/npc/theme_park/player_transport_theed_hangar.iff"
	},

	shuttleName = { "Lambda Shuttle", "Shuttle", "Transport", "Theed Transport" },

	shuttleLandingTime = { 18, 23, 27, 34 }, -- Time it takes each shuttle to land in seconds

	shuttleCleanup = 8 * 60 * 60, -- Automatic shuttle cleanup after 8 hours if the shuttle has not been told to lift off

}

function ShuttleDropoff:resetDefaults(pPlayer)
	local playerID = SceneObject(pPlayer):getObjectID()

	deleteData(playerID .. ":ShuttleDropoff:setupStep")
	deleteData(playerID .. ":ShuttleDropoff:setupCompleted")
	deleteData(playerID .. ":ShuttleDropoff:shuttleType")
	deleteData(playerID .. ":ShuttleDropoff:heading")
	deleteData(playerID .. ":ShuttleDropoff:numSpawns")
	deleteData(playerID .. ":ShuttleDropoff:spawnPointX")
	deleteData(playerID .. ":ShuttleDropoff:spawnPointZ")
	deleteData(playerID .. ":ShuttleDropoff:spawnPointY")
	deleteData(playerID .. ":ShuttleDropoff:shuttleStatus")
	deleteData(playerID .. ":ShuttleDropoff:spawnLevel")

	deleteStringData(playerID .. ":ShuttleDropoff:spawnTemplate")
	deleteStringData(playerID .. ":ShuttleDropoff:spawnPlanet")
end

function ShuttleDropoff:destroyShuttle(pPlayer)
	local playerID = SceneObject(pPlayer):getObjectID()

	local shuttleID = readData(playerID .. ":ShuttleDropoff:shuttleID")
	local pShuttle = getSceneObject(shuttleID)

	if (pShuttle ~= nil) then
		SceneObject(pShuttle):destroyObjectFromWorld()
	end

	deleteData(playerID .. ":ShuttleDropoff:shuttleID")
end

function ShuttleDropoff:spawnShuttle(pPlayer, manualControl)
	local playerID = SceneObject(pPlayer):getObjectID()

	local type = readData(playerID .. ":ShuttleDropoff:shuttleType")
	local posX = readData(playerID .. ":ShuttleDropoff:spawnPointX")
	local posZ = readData(playerID .. ":ShuttleDropoff:spawnPointZ")
	local posY = readData(playerID .. ":ShuttleDropoff:spawnPointY")
	local heading = readData(playerID .. ":ShuttleDropoff:heading")
	local planet = readStringData(playerID .. ":ShuttleDropoff:spawnPlanet")

	if (type < 3) then
		heading = heading + 180
	end

	local pShuttle = spawnSceneObject(planet, self.shuttleTemplate[type], posX, posZ, posY, 0, heading)

	if (pShuttle == nil) then
		CreatureObject(pPlayer):sendSystemMessage("Error creating shuttle. Please try again.")
		return nil
	end

	if (type ~= 1) then
		CreatureObject(pShuttle):setPosture(PRONE)
	end

	CreatureObject(pShuttle):setCustomObjectName(self.shuttleName[type])

	writeData(playerID .. ":ShuttleDropoff:shuttleID", SceneObject(pShuttle):getObjectID())

	if (manualControl) then
		writeData(playerID .. ":ShuttleDropoff:shuttleStatus", -1) -- Creating shuttle
		createEvent(5 * 1000, "ShuttleDropoff", "allowManualControl", pPlayer, "")
	else
		writeData(playerID .. ":ShuttleDropoff:shuttleStatus", 1) -- Spawned
	end

	createEvent(self.shuttleCleanup * 1000, "ShuttleDropoff", "cleanUp", pPlayer, "")

	return pShuttle
end

function ShuttleDropoff:doFlyby(pPlayer)
	local pShuttle = self:spawnShuttle(pPlayer, false)

	if (pShuttle == nil) then
		CreatureObject(pPlayer):sendSystemMessage("Error executing flyby, shuttle not found.")
		return
	end

	local type = readData(SceneObject(pPlayer):getObjectID() .. ":ShuttleDropoff:shuttleType")
	CreatureObject(pPlayer):sendSystemMessage("Beginning flyby.")

	createEvent(6 * 1000, "ShuttleDropoff", "landShuttle", pPlayer, "")
	createEvent((self.shuttleLandingTime[type] + 9) * 1000, "ShuttleDropoff", "doTakeOff", pPlayer, "")
end

function ShuttleDropoff:landShuttle(pPlayer)
	local playerID = SceneObject(pPlayer):getObjectID()
	local shuttleID = readData(playerID .. ":ShuttleDropoff:shuttleID")
	local type = readData(playerID .. ":ShuttleDropoff:shuttleType")
	local pShuttle = getSceneObject(shuttleID)

	if (pShuttle == nil) then
		CreatureObject(pPlayer):sendSystemMessage("Error executing shuttle landing, shuttle not found.")
		return
	end

	if (type == 1) then
		CreatureObject(pShuttle):setPosture(PRONE)
	else
		CreatureObject(pShuttle):setPosture(UPRIGHT)
	end

	writeData(playerID .. ":ShuttleDropoff:shuttleStatus", 2) -- Landing
	createEvent(self.shuttleLandingTime[type] * 1000, "ShuttleDropoff", "dropOffNpcs", pPlayer, "")
	CreatureObject(pPlayer):sendSystemMessage("Shuttle Update: Shuttle is now landing..")
end

function ShuttleDropoff:dropOffNpcs(pPlayer)
	if (pPlayer == nil) then
		return
	end

	local playerID = SceneObject(pPlayer):getObjectID()
	local posX = readData(playerID .. ":ShuttleDropoff:spawnPointX")
	local posZ = readData(playerID .. ":ShuttleDropoff:spawnPointZ")
	local posY = readData(playerID .. ":ShuttleDropoff:spawnPointY")
	local template = readStringData(playerID .. ":ShuttleDropoff:spawnTemplate")
	local mobLevel = readData(playerID .. ":ShuttleDropoff:spawnLevel")
	local numSpawns = readData(playerID .. ":ShuttleDropoff:numSpawns")
	local heading = readData(playerID .. ":ShuttleDropoff:heading")
	local planet = readStringData(playerID .. ":ShuttleDropoff:spawnPlanet")

	writeData(playerID .. ":ShuttleDropoff:shuttleStatus", 3) -- Landed

	for i = 1, numSpawns, 1 do
		local xOffset = -3 + getRandomNumber(0, 6)
		local yOffset = -3 + getRandomNumber(0, 6)
		spawnEventMobile(planet, template, mobLevel, posX + xOffset, posZ, posY + yOffset, heading, 0)
	end
end

function ShuttleDropoff:cleanUp(pPlayer)
	if (pPlayer == nil) then
		return
	end

	self:resetDefaults(pPlayer)
	self:destroyShuttle(pPlayer)
end

function ShuttleDropoff:doTakeOff(pPlayer)
	if (pPlayer == nil) then
		return
	end

	local playerID = SceneObject(pPlayer):getObjectID()
	local shuttleID = readData(playerID .. ":ShuttleDropoff:shuttleID")
	local type = readData(playerID .. ":ShuttleDropoff:shuttleType")
	local pShuttle = getSceneObject(shuttleID)

	if (pShuttle == nil) then
		CreatureObject(pPlayer):sendSystemMessage("Error executing shuttle take off, shuttle not found.")
		return
	end

	if (type == 1) then
		CreatureObject(pShuttle):setPosture(UPRIGHT)
	else
		CreatureObject(pShuttle):setPosture(PRONE)
	end

	writeData(playerID .. ":ShuttleDropoff:shuttleStatus", 4) -- Taking off
	createEvent(20 * 1000, "ShuttleDropoff", "cleanUp", pPlayer, "")
	CreatureObject(pPlayer):sendSystemMessage("Shuttle Update: Shuttle has taken off.")
end

function ShuttleDropoff:showMainUI(pPlayer)
	local sui = SuiInputBox.new("ShuttleDropoff", "suiShuttleDropoffMainCallback")

	sui.setTargetNetworkId(SceneObject(pPlayer):getObjectID())

	local suiBody = "Enter \"setup\" to setup data, \"data\" to view current data, \"quit\" to end. After setup type \"f\" to have the shuttle do an automatic fly-by. Type \"m\" to spawn and manually control the shuttle then use \"land\" to make it land, \"leave\" to make it take off."
	sui.setTitle("Information")
	sui.setPrompt(suiBody)

	sui.sendTo(pPlayer)
end

function ShuttleDropoff:allowManualControl(pPlayer)
	if (pPlayer == nil) then
		return
	end

	writeData(SceneObject(pPlayer):getObjectID() .. ":ShuttleDropoff:shuttleStatus", 1)
end

function ShuttleDropoff:suiShuttleDropoffMainCallback(pPlayer, pSui, eventIndex, args)
	local cancelPressed = (eventIndex == 1)

	if (cancelPressed) then
		return
	end

	local playerID = SceneObject(pPlayer):getObjectID()
	local shuttleID = readData(playerID .. ":ShuttleDropoff:shuttleID")
	local pShuttle = getSceneObject(shuttleID)

	if (args == "setup") then
		if (pShuttle ~= nil) then
			CreatureObject(pPlayer):sendSystemMessage("Error: A shuttle already exists. Use \"quit\" to destroy the existing shuttle before running \"setup\" again.")
		else
			self:resetDefaults(pPlayer)
			writeData(playerID .. ":ShuttleDropoff:setupStep", 1)
			self:showSetupUI(pPlayer)
			return
		end
	elseif (args == "data") then
		local sType = readData(playerID .. ":ShuttleDropoff:shuttleType")

		if (sType == 0) then
			CreatureObject(pPlayer):sendSystemMessage("No shuttle data entered. Run setup first.")
		else
			local numSpawns = readData(playerID .. ":ShuttleDropoff:numSpawns")

			if (numSpawns == 0) then
				CreatureObject(pPlayer):sendSystemMessage("Shuttle: " .. self.shuttleName[sType] .. ". Number of spawns: " .. numSpawns)
			else
				local sTemp = readStringData(playerID .. ":ShuttleDropoff:spawnTemplate")
				CreatureObject(pPlayer):sendSystemMessage("Shuttle: " .. self.shuttleName[sType] .. ". Number of spawns: " .. numSpawns .. ". Spawn template: " .. sTemp)
			end
		end
	elseif (args == "quit") then
		self:resetDefaults(pPlayer)
		self:destroyShuttle(pPlayer)
		return
	elseif (args == "f") then
		if (readData(playerID .. ":ShuttleDropoff:setupCompleted") ~= 1) then
			CreatureObject(pPlayer):sendSystemMessage("Shuttle setup incomplete. Use \"setup\" to set up the shuttle before triggering a flyby.")
		else
			self:doFlyby(pPlayer)
		end
	elseif (args == "m" or args == "land" or args == "leave") then
		if (args == "m") then
			if (readData(playerID .. ":ShuttleDropoff:setupCompleted") == 1) then
				if (pShuttle ~= nil) then
					CreatureObject(pPlayer):sendSystemMessage("Existing shuttle found. Use \"land\" and \"leave\" to control it, or \"quit\" to end the event.")
				else
					ShuttleDropoff:spawnShuttle(pPlayer, true)
				end
			else
				CreatureObject(pPlayer):sendSystemMessage("Shuttle setup has not been completed. Use \"setup\" to configure the shuttle.")
			end
		else
			if (pShuttle == nil) then
				CreatureObject(pPlayer):sendSystemMessage("No shuttle found. Type \"m\" first to enter manual control before trying to land or leave.")
			else
				local shuttleStatus = readData(playerID .. ":ShuttleDropoff:shuttleStatus")
				if (args == "land") then
					if (shuttleStatus == -1) then
						CreatureObject(pPlayer):sendSystemMessage("Please allow 5 seconds after entering manual control for the shuttle to be created.")
					elseif (shuttleStatus == 1) then
						self:landShuttle(pPlayer)
					elseif (shuttleStatus == 2) then
						CreatureObject(pPlayer):sendSystemMessage("Shuttle is already in the process of landing.")
					elseif (shuttleStatus == 3) then
						CreatureObject(pPlayer):sendSystemMessage("Shuttle has already landed.")
					elseif (shuttleStatus == 4) then
						CreatureObject(pPlayer):sendSystemMessage("Shuttle is currently taking off.")
					end
				else
					if (shuttleStatus == 1) then
						CreatureObject(pPlayer):sendSystemMessage("Shuttle is not currently on the ground.")
					elseif (shuttleStatus == 2) then
						CreatureObject(pPlayer):sendSystemMessage("Shuttle is currently in the process of landing.")
					elseif (shuttleStatus == 3) then
						self:doTakeOff(pPlayer)
					elseif (shuttleStatus == 4) then
						CreatureObject(pPlayer):sendSystemMessage("Shuttle is already taking off.")
					end
				end
			end
		end
	end

	self:showMainUI(pPlayer)
end

function ShuttleDropoff:showSetupUI(pPlayer)
	local playerID = SceneObject(pPlayer):getObjectID()
	local curStep = readData(playerID .. ":ShuttleDropoff:setupStep")

	if (readData(playerID .. ":ShuttleDropoff:setupCompleted") == 1 or curStep == 0) then
		self:showMainUI(pPlayer)
		return
	end

	local sui = SuiInputBox.new("ShuttleDropoff", "suiShuttleDropoffSetupCallback")

	sui.setTargetNetworkId(SceneObject(pPlayer):getObjectID())

	sui.setTitle(self.promptTitle[curStep])
	sui.setPrompt(self.promptBody[curStep])

	sui.sendTo(pPlayer)
end

function ShuttleDropoff:suiShuttleDropoffSetupCallback(pPlayer, pSui, eventIndex, args)
	local cancelPressed = (eventIndex == 1)

	if (cancelPressed) then
		return
	end

	local playerID = SceneObject(pPlayer):getObjectID()
	local curStep = readData(playerID .. ":ShuttleDropoff:setupStep")

	if (curStep == 1) then
		if (args ~= "lambda" and args ~= "shuttle" and args ~= "transport" and args ~= "theed transport") then
			CreatureObject(pPlayer):sendSystemMessage("Invalid shuttle type. Please choose from the available shuttle types listed.")
		else
			local shuttleNum
			if (args == "lambda") then
				shuttleNum = 1
			elseif (args == "shuttle") then
				shuttleNum = 2
			elseif (args == "transport") then
				shuttleNum = 3
			else
				shuttleNum = 4
			end

			writeData(playerID .. ":ShuttleDropoff:setupStep", 2)
			writeData(playerID .. ":ShuttleDropoff:shuttleType", shuttleNum)
			CreatureObject(pPlayer):sendSystemMessage("Shuttle Type: " .. self.shuttleName[shuttleNum])
		end
	elseif (curStep == 2) then
		if (args == "here") then
			if (SceneObject(pPlayer):getParentID() ~= 0) then
				CreatureObject(pPlayer):sendSystemMessage("ERROR: You must be outside to set a landing area.")
			else
				writeData(playerID .. ":ShuttleDropoff:spawnPointX", math.floor(SceneObject(pPlayer):getWorldPositionX()))
				writeData(playerID .. ":ShuttleDropoff:spawnPointZ", math.floor(SceneObject(pPlayer):getWorldPositionZ()))
				writeData(playerID .. ":ShuttleDropoff:spawnPointY", math.floor(SceneObject(pPlayer):getWorldPositionY()))
				writeStringData(playerID .. ":ShuttleDropoff:spawnPlanet", SceneObject(pPlayer):getZoneName())
				writeData(playerID .. ":ShuttleDropoff:heading", math.floor(SceneObject(pPlayer):getDirectionAngle()))
				writeData(playerID .. ":ShuttleDropoff:setupStep", 3)
				CreatureObject(pPlayer):sendSystemMessage("Landing Area: Set to your current location and direction.")
			end
		else
			CreatureObject(pPlayer):sendSystemMessage("You must stand where you want the shuttle to land and type \"here\" in the input box.")
		end
	elseif (curStep == 3) then
		if (args == "yes") then
			CreatureObject(pPlayer):sendSystemMessage("Spawn NPCs on Landing?: yes.")
			writeData(playerID .. ":ShuttleDropoff:setupStep", 4)
		elseif (args == "no") then
			CreatureObject(pPlayer):sendSystemMessage("Spawn NPCs on Landing?: no.")
			writeData(playerID .. ":ShuttleDropoff:setupCompleted", 1)
		else
			CreatureObject(pPlayer):sendSystemMessage("You must enter yes or no.")
		end
	elseif (curStep == 4) then
		if (args == "") then
			CreatureObject(pPlayer):sendSystemMessage("You must enter a spawn template.")
		else
			writeStringData(playerID .. ":ShuttleDropoff:spawnTemplate", args)
			CreatureObject(pPlayer):sendSystemMessage("NPC Template: " .. args)
			writeData(playerID .. ":ShuttleDropoff:setupStep", 5)
		end
	elseif (curStep == 5) then
		local spawnNumber = tonumber(args)

		if (spawnNumber ~= nil and spawnNumber > 0 and spawnNumber <= 10) then
			writeData(playerID .. ":ShuttleDropoff:numSpawns", spawnNumber)
			writeData(playerID .. ":ShuttleDropoff:setupStep", 6)
		else
			CreatureObject(pPlayer):sendSystemMessage("You must enter a spawn number between 1 and 10.")
		end
	elseif (curStep == 6) then
		local spawnLevel = tonumber(args)

		if (spawnLevel ~= nil and spawnLevel > 0) then
			writeData(playerID .. ":ShuttleDropoff:spawnLevel", spawnLevel)
			writeData(playerID .. ":ShuttleDropoff:setupCompleted", 1)
		else
			CreatureObject(pPlayer):sendSystemMessage("You must enter a spawn level greater than 0.")
		end
	end

	self:showSetupUI(pPlayer)
end
