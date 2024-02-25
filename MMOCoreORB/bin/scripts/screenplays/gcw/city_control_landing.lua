CityControlLanding = ScreenPlay:new {
	numberOfActs = 1,

	screenplayName = "CityControlLanding",

	locations = {
		{"coronet", "corellia"},
		{"bela_vistal", "corellia"},
		{"theed", "naboo"},
		{"moenia", "naboo"},
		{"bestine", "tatooine"},
		{"anchorhead", "tatooine"}
	},

	coordinates = {
		--{x, z, y, direction}
		{-148, 28, -4715, 179}, -- 1 Coronet
		{6902, 330, -5550, 179}, -- 2 Bela Vistal
		{-4897, 6, 4124, 179}, -- 3 Theed
		{4812, 4, -4700, 179}, --  4 Moenia
		{-1282, 12, -3584, 180}, -- 5 Bestine
		{112, 52, -5340, 180}, -- 6 Anchorhead
	},

	rebelLanding = {"object/creature/npc/theme_park/player_shuttle2.iff", "leia_organa_city_control", "rebel_commandant", "rebel_commandant", "rebel_commandant", "rebel_commandant", "rebel_commandant", "rebel_commandant", "rebel_commandant"},
	imperialLanding = {"object/creature/npc/theme_park/lambda_shuttle.iff", "darth_vader_city_control", "elite_novatrooper_commander", "elite_novatrooper", "elite_novatrooper", "elite_novatrooper", "elite_novatrooper", "elite_novatrooper", "elite_novatrooper"},
	rebelSpawnOffsetY = 5,
	imperialSpawnOffsetY = 12,
}

registerScreenPlay("CityControlLanding", true)

function CityControlLanding:start()
	self:chanceToSpawn()
end

function CityControlLanding:chanceToSpawn()
	local chance = getRandomNumber(100)

	if (chance <= 15) then -- 15% Chance
		createEvent(20 * 60 * 1000, "CityControlLanding", "spawnCityLanding", "0", "false") --20min after chance roll to allow for load time
	else
		createEvent(6 * 60 * 60 * 1000, "CityControlLanding", "chanceToSpawn", "", "") --6hrs
	end
end

function CityControlLanding:spawnCityLanding(spawnCity, manual)
	local totalLocations = #self.locations
	local determineCity = spawnCity

	if (determineCity == nil) then
		determineCity = getRandomNumber(totalLocations)
	end

	local chosenCityPlanet = self.locations[determineCity]
	local cityCoords = self.coordinates[determineCity]
	local city = chosenCityPlanet[1]
	local planet = chosenCityPlanet[2]

	if (not isZoneEnabled(planet) or readStringData("CityControlLandingStatus:") == "true") then
		createEvent(20 * 60 * 1000, "CityControlLanding", "spawnCityLanding", spawnCity, manual)
		return
	end

	writeStringData("CityControlLandingPlanet:", planet)
	writeData("CityControlLandingCity:", determineCity)
	writeData("CityControlLanding:dialogueNumber", getRandomNumber(1, 3))

	local controllingFaction = getControllingFaction(planet)
	local shuttleTemplate = ""
	local landingType = ""
	local shuttlePosture = ""

	if (city ~= "bestine") and (controllingFaction == FACTIONREBEL or city == "anchorhead" or city == "moenia") then
		landingType = "REBEL"
		shuttlePosture = "PRONE"
		shuttleTemplate = self.rebelLanding[1]
	else
		landingType = "IMPERIAL"
		shuttlePosture = "UPRIGHT"
		shuttleTemplate = self.imperialLanding[1]
	end

	local pShuttle = spawnSceneObject(planet, shuttleTemplate, cityCoords[1], cityCoords[2], cityCoords[3], 0, math.rad(cityCoords[4]))

	if (pShuttle ~= nil) then

		if (shuttleTemplate == "object/creature/npc/theme_park/player_shuttle2.iff") then
			CreatureObject(pShuttle):setPosture(PRONE)
		else
			CreatureObject(pShuttle):setPosture(UPRIGHT)
		end

		local pOid = SceneObject(pShuttle):getObjectID()
		writeData(1 .. ":LandingParty", pOid)
		writeStringData("CityControlLandingStatus:", "true")
		writeStringData("CityLandingManualControl:", manual)
		writeStringData("LandingType:", landingType)
		writeStringData("ShuttlePosture:", shuttlePosture)

		local playerTable = SceneObject(pShuttle):getPlayersInRange(150)

		if (#playerTable > 0) then
			createEvent(34 * 1000, "CityControlLanding", "handleShuttlePosture", pShuttle, "")
			createEvent(10 * 1000, "CityControlLanding", "broadcastMessage", pShuttle, "")
		else
			SceneObject(pShuttle):destroyObjectFromWorld()
			createEvent(20 * 1000, "CityControlLanding", "cleanUp", "", "")
		end
	end
end

function CityControlLanding:broadcastMessage(pShuttle)
	if (pShuttle == nil) then
		return
	end

	local playerTable = SceneObject(pShuttle):getPlayersInRange(150)
	local landingType = readStringData("LandingType:")
	local landingStep = readStringData("NextPoint:")
	local broadcastTemplate = ""

	if (landingStep == "shuttle")   then
		if (landingType == "REBEL") then
			broadcastTemplate= "@gcwlaunchevent:closingbroadcast_1"
		else
			broadcastTemplate = "@gcwlaunchevent:closingbroadcast_0"
		end
	else
		if (landingType == "REBEL") then
			broadcastTemplate= "@gcwlaunchevent:areabroadcast_1"
		else
			broadcastTemplate = "@gcwlaunchevent:areabroadcast_0"
		end
	end

	if (#playerTable > 0) then
		for i = 1, #playerTable, 1 do
			local pPlayer = playerTable[i]

			if (pPlayer ~= nil and broadcastTemplate ~= nil) then
				CreatureObject(pPlayer):sendSystemMessage(broadcastTemplate)
			end
		end
	end
end

function CityControlLanding:handleShuttlePosture(shuttle)
	local pShuttle = shuttle

	if (pShuttle == nil) then
		return
	end

	local shuttleID = SceneObject(pShuttle):getObjectID()
	local landingType = readStringData("LandingType:")
	local shuttlePosture = readStringData("ShuttlePosture:")

	if (landingType == "IMPERIAL") then
		if (shuttlePosture == "UPRIGHT") then
			CreatureObject(pShuttle):setCustomObjectName("Lambda Shuttle")
			CreatureObject(pShuttle):setPosture(PRONE)
			writeStringData("ShuttlePosture:", "PRONE")
			createEvent(19000, "CityControlLanding", "spawnLandingParty", "", "")
		else
			CreatureObject(pShuttle):setPosture(UPRIGHT)
		end
	elseif (landingType == "REBEL") then
		if (shuttlePosture == "PRONE") then
			CreatureObject(pShuttle):setCustomObjectName("Transport Shuttle")
			CreatureObject(pShuttle):setPosture(UPRIGHT)
			writeStringData("ShuttlePosture:", "UPRIGHT")
			createEvent(25000, "CityControlLanding", "spawnLandingParty", "", "")
		else
			CreatureObject(pShuttle):setPosture(PRONE)
		end
	else
		printLuaError("Wrong Landing Type in CityControlLanding Screenplay")
	end
end

function CityControlLanding:spawnLandingParty()
	local landingType = readStringData("LandingType:")
	local totalSpawns

	if (landingType == "REBEL") then
		totalSpawns = #self.rebelLanding
	else
		totalSpawns = #self.imperialLanding
	end

	for i = 2, totalSpawns, 1 do
		self:spawnMobile(i)
	end
end

function CityControlLanding:spawnMobile(spawnNumber)
	local landingType = readStringData("LandingType:")
	local determinedCity = readData("CityControlLandingCity:")
	local spawnCityPlanet = self.locations[determinedCity]

	local city = spawnCityPlanet[1]
	local planet = spawnCityPlanet[2]
	local cityCoords = self.coordinates[determinedCity]

	local totalSpawns
	local template
	local xLoc = cityCoords[1]
	local yLoc = cityCoords[3]

	if (landingType == "REBEL") then
		template = self.rebelLanding
		totalSpawns = #self.rebelLanding
		yLoc = cityCoords[3] - 11
	else
		template = self.imperialLanding
		totalSpawns = #self.imperialLanding
	end

	if (template[spawnNumber] == "leia_organa_city_control" or template[spawnNumber] == "darth_vader_city_control") then
		--template, level, x, z, y, direction, cell, mood},
		local pMobile = spawnMobile(planet, template[spawnNumber], 0, xLoc, cityCoords[2], yLoc, cityCoords[4], 0, "")

		if (pMobile ~= nil) then
			AiAgent(pMobile):addObjectFlag(AI_STATIONARY)
			CreatureObject(pMobile):setPvpStatusBitmask(0)

			local mobileID = SceneObject(pMobile):getObjectID()

			writeStringData("NextPoint:", "speech")
			writeData("CityControlLanding:speechStep", 1)
			writeData(spawnNumber .. ":LandingParty", mobileID)

			createObserver(DESTINATIONREACHED, "CityControlLanding", "destinationReached", pMobile)
			createEvent(5 * 1000, "CityControlLanding", "setupMusic", pMobile, "")
			createEvent(5 * 1000, "CityControlLanding", "moveTo", pMobile, "")
		end
	else
		if (landingType == "REBEL") then
			xLoc = cityCoords[1] + getRandomNumber(-3, 3)
			yLoc = cityCoords[3] - self.rebelSpawnOffsetY
		else
			yLoc = cityCoords[3] - self.imperialSpawnOffsetY - spawnNumber

			if (spawnNumber == 3 or spawnNumber == 5 or spawnNumber == 7) then
				xLoc = cityCoords[1] - 1
			elseif (spawnNumber == 4 or spawnNumber == 6 or spawnNumber == 8) then
				xLoc = cityCoords[1] + 1
			else
				xLoc = cityCoords[1]
			end
		end

		local pMobile = spawnMobile(planet, template[spawnNumber], 0, xLoc, cityCoords[2], yLoc, cityCoords[4], 0, "")

		if (pMobile ~= nil) then
			AiAgent(pMobile):setMovementState(AI_PATROLLING)
			CreatureObject(pMobile):setPvpStatusBitmask(1)

			local mobileID = SceneObject(pMobile):getObjectID()

			writeData(spawnNumber .. ":LandingParty", mobileID)
			writeData(mobileID .. ":spawnNumber", spawnNumber)

			createObserver(CREATUREDESPAWNED, "CityControlLanding", "onDespawn", pMobile)
		end
	end
end

function CityControlLanding:setupMusic(pMobile)
	if (pMobile == nil) then
		return
	end

	local playerTable = SceneObject(pMobile):getPlayersInRange(150)
	local landingType = readStringData("LandingType:")
	local musicTemplate = ""

	if (landingType == "REBEL") then
		musicTemplate = "sound/music_leia_theme_stereo.snd"
	else
		musicTemplate = "sound/music_emperor_theme_stereo.snd"
	end

	if (#playerTable > 0) then
		for i = 1, #playerTable, 1 do
			local pPlayer = playerTable[i]

			if (pPlayer ~= nil and musicTemplate ~= nil) then
				CreatureObject(pPlayer):playMusicMessage(musicTemplate)
			end
		end
	end
end

function CityControlLanding:doSpeech(pMobile)
	if (pMobile == nil or CreatureObject(pMobile):isDead()) then
	return 1
	end

	local speechStep = readData("CityControlLanding:speechStep")
	local speechType = 0

	if (speechStep == 0) then
		speechStep = 1
	elseif (speechStep == 11) then
		writeStringData("NextPoint:", "shuttle")
		createObserver(DESTINATIONREACHED, "CityControlLanding", "destinationReached", pMobile)
		createEvent(2000, "CityControlLanding", "moveTo", pMobile, "")
		return
	end

	local landingType = readStringData("LandingType:")
	local speechAnims = { "", "", "pound_fist_palm", "", "force_push", "", "force_choke", "", "", "point_forward" }

	if (landingType == "REBEL") then
		speechType = 1
		speechAnims = { "", "", "point_right", "", "pound_fist_palm", "", "nod_head_once", "", "", "point_forward" }
	end

	local dialogueNum = readData("CityControlLanding:dialogueNumber")

	spatialChat(pMobile, "@gcwlaunchevent:dialogue_" .. speechType .. "_" .. dialogueNum .. "_" .. speechStep)

	if (speechAnims[speechStep] ~= "") then
		CreatureObject(pMobile):doAnimation(speechAnims[speechStep])
	end

	writeData("CityControlLanding:speechStep", speechStep + 1)
	createEvent(12 * 1000, "CityControlLanding", "doSpeech", pMobile, "")
end

function CityControlLanding:moveTo(pMobile)
	if (pMobile == nil or CreatureObject(pMobile):isDead()) then
		return
	end

	local cityNumber = readData("CityControlLandingCity:")
	local spawnCoords = self.coordinates[cityNumber]
	local landingType = readStringData("LandingType:")
	local nextPoint = readStringData("NextPoint:")

	if (landingType == "REBEL") then
		if (nextPoint == "speech") then
			local posY = spawnCoords[3] - 18
			AiAgent(pMobile):setNextPosition(spawnCoords[1], spawnCoords[2], posY, 0)
		else
			local posY = spawnCoords[3] - 11
			AiAgent(pMobile):setNextPosition(spawnCoords[1], spawnCoords[2], posY, 0)
		end
	elseif (landingType == "IMPERIAL") then
		if (nextPoint == "speech") then
			local posY = spawnCoords[3] - 10
			AiAgent(pMobile):setNextPosition(spawnCoords[1], spawnCoords[2], posY, 0)
		else
			AiAgent(pMobile):setNextPosition(spawnCoords[1], spawnCoords[2], spawnCoords[3], 0)
		end
	else
		printLuaError("Wrong LandingType in CityControlLanding:moveTo Function")
	end

	AiAgent(pMobile):stopWaiting()
	AiAgent(pMobile):setWait(0)
	AiAgent(pMobile):executeBehavior()
end

function CityControlLanding:destinationReached(pMobile)
	if (pMobile == nil or CreatureObject(pMobile):isDead()) then
		return 1
	end

	local mobileID = SceneObject(pMobile):getObjectID()

	local pointName = readStringData("NextPoint:")

	if (pointName == "speech") then
		createEvent(5 * 1000, "CityControlLanding", "doSpeech", pMobile, "")
		return 1
	else
		self:despawnLanding()
		return 1
	end
end

function CityControlLanding:despawnLanding()
	local pShuttleID = readData(1 .. ":LandingParty")
	local pShuttle = getSceneObject(pShuttleID)

	if (pShuttle == nil) then
		return
	end

	createEvent(5 * 1000, "CityControlLanding", "despawnMobiles", "", "")
	createEvent(26 * 1000, "CityControlLanding", "broadcastMessage", pShuttle, "")
	createEvent(28 * 1000, "CityControlLanding", "handleShuttlePosture", pShuttle, "")
	createEvent(5 * 60 * 1000, "CityControlLanding", "cleanUp", "", "")
end

function CityControlLanding:despawnMobiles()
	local landingType = readStringData("LandingType:")

	if (landingType == "REBEL") then
		totalSpawns = #self.rebelLanding
	else
		totalSpawns = #self.imperialLanding
	end

	for i = 2, totalSpawns, 1 do
		local pMobileID = readData(i .. ":LandingParty")
		local pMobile = getSceneObject(pMobileID)

		if (pMobile ~= nil) then
			if (CreatureObject(pMobile):isInCombat()) then
				createEvent(30 * 1000, "CityControlLanding", "mobileDespawn", pMobile, "")
			else
				createEvent(1000, "CityControlLanding", "moveTo", pMobile, "")
				createEvent(18 * 1000, "CityControlLanding", "mobileDespawn", pMobile, "")
			end
		end
	end
end

function CityControlLanding:mobileDespawn(pMobile)

	if (pMobile == nil or CreatureObject(pMobile):isDead()) then
		return
	end

	if (CreatureObject(pMobile):isInCombat()) then
		createEvent(30 * 1000, "CityControlLanding", "mobileDespawn", pMobile, "")
		return
	end

	dropObserver(CREATUREDESPAWNED, "CityControlLanding", "onDespawn", pMobile)
	SceneObject(pMobile):destroyObjectFromWorld()
end

function CityControlLanding:onDespawn(pMobile)
	if (pMobile == nil) then
		return
	end

	local pointName = readStringData("NextPoint:")

	if (pointName == "speech") then
		createEvent(20 * 1000, "CityControlLanding", "respawnDelay", pMobile, "")
		return 0
	end

	return 1
end

function CityControlLanding:respawnDelay(pMobile)
	if (pMobile == nil) then
		return
	end

	local mobileID = SceneObject(pMobile):getObjectID()
	local spawnNumber = readData(mobileID .. ":spawnNumber")

	self:spawnMobile(spawnNumber)

	deleteData(mobileID .. ":spawnNumber")
	deleteData(spawnNumber .. ":LandingParty")
end

function CityControlLanding:cleanUp()
	deleteStringData("CityControlLandingPlanet:")
	deleteStringData("ShuttlePosture:")
	deleteStringData("NextPoint:")

	deleteData("CityControlLandingCity:")
	deleteData("CityControlLanding:speechStep")
	deleteData("CityControlLanding:dialogueNumber")


	local landingType = readStringData("LandingType:")
	local totalCleanup = #self.imperialLanding

	if (landingType == "REBEL") then
		totalCleanup = #self.rebelLanding
	end

	for i = 2, totalCleanup, 1 do
		local mobileID = readData(i .. ":LandingParty")

		deleteData(mobileID .. ":spawnNumber", i)
		deleteData(i .. ":LandingParty", mobileID)
	end

	deleteStringData("LandingType:")

	local pShuttleID = readData(1 .. ":LandingParty")
	local pShuttle = getSceneObject(pShuttleID)

	if (pShuttle == nil) then
		return
	end

	SceneObject(pShuttle):destroyObjectFromWorld()
	deleteData(1 .. ":LandingParty")

	local manualControl = readStringData("CityLandingManualControl:")

	if (manualControl == "false") then
		createEvent(4 * 60 * 60 * 1000, "CityControlLanding", "chanceToSpawn", "", "") -- 4 hrs
	end

	deleteStringData("CityLandingManualControl:")
	deleteStringData("CityControlLandingStatus:")
end

function  CityControlLanding:showMainUI(pPlayer)
	local sui = SuiListBox.new("CityControlLanding", "suiCCLMainCallback")

	sui.setTargetNetworkId(SceneObject(pPlayer):getObjectID())

	sui.setTitle("GCW City Control Landing")
	sui.setPrompt("Select City for Landing: The planetary faction control will determine the type of landing.")

	sui.add("Coronet", "")
	sui.add("Bela Vistal", "")
	sui.add("Theed", "")
	sui.add("Moenia", "")
	sui.add("Bestine", "")
	sui.add("Anchorhead", "")

	sui.sendTo(pPlayer)
end


function CityControlLanding:suiCCLMainCallback(pPlayer, pSui, eventIndex, args)
	local cancelPressed = (eventIndex == 1)

	if (cancelPressed or pPlayer == nil) then
		return
	end

	local cityNum = tonumber(args) + 1
	local city = self.locations[cityNum]

	if (readStringData("CityControlLandingStatus:") == "true") then
		CreatureObject(pPlayer):sendSystemMessage("There is already GCW City Control Landing Event in Progress, please wait until it completes before starting another.")
		StaffTools:openSUI(pPlayer)
		return
	end

	self:spawnCityLanding(cityNum, "true")

	CreatureObject(pPlayer):sendSystemMessage("GCW City Control Landing Starting for " .. city[1])

	StaffTools:openSUI(pPlayer)
end