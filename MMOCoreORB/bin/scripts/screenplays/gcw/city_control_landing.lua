CityControlLanding = ScreenPlay:new {
	numberOfActs = 1,

	screenplayName = "CityControlLanding",

	locations = {
		--{"coronet", "corellia"},
		--{"bela_vistal", "corellia"},
		{"theed", "naboo"},
		--{"moenia", "naboo"},
		--{"bestine", "tatooine"},
		--{"anchorhead", "tatooine"}
	},

	coordinates = {
		--{x, z, y, direction}
		--{-148, 28, -4715, 179}, -- 1 Coronet
		--{6902, 330, -5550, 179}, -- 2 Bela Vistal
		{-4897, 6, 4124, 179}, -- 3 Theed
		--{4812, 4, -4700, 179}, --  4 Moenia
		--{-1282, 12, -3579, 180}, -- 5 Bestine
		--{111, 52, -5338, 171}, -- 6 Anchorhead
	},

	rebelLanding = {"object/creature/npc/theme_park/player_shuttle.iff", "lukeLeia", "rebel_commandant", "rebel_ensign", "rebel_commodore", "fbase_rebel_commando", "fbase_rebel_commando", "fbase_rebel_heavy_trooper", "fbase_rebel_heavy_trooper"},
	imperialLanding = {"object/creature/npc/theme_park/lambda_shuttle.iff", "darth_vader_city_control", "elite_novatrooper_commander", "elite_novatrooper", "elite_novatrooper", "elite_novatrooper", "elite_novatrooper", "elite_novatrooper", "elite_novatrooper"},

}

registerScreenPlay("CityControlLanding", true)

function CityControlLanding:start()
	self:chanceToSpawn()
end

function CityControlLanding:chanceToSpawn()
	local chance = getRandomNumber(49)

	if (chance <= 50) then --if (chance <= 5) then
		createEvent(90 * 1000, "CityControlLanding", "spawnCityLanding", "", "")
	else
		createEvent(30 * 60 * 1000, "CityControlLandingScreenplay", "chanceToSpawn", "", "") --30min TESTING
		--createEvent(6 * 60 * 60 * 1000, "CityControlLandingScreenplay", "chanceToSpawn", "", "") --6hrs
	end
end

function CityControlLanding:spawnCityLanding()
	local totalLocations = #self.locations
	local determineCity = getRandomNumber(totalLocations)
	local chosenCityPlanet = self.locations[determineCity]
	local cityCoords = self.coordinates[determineCity]
	local city = chosenCityPlanet[1]
	local planet = chosenCityPlanet[2]

	if (not isZoneEnabled(planet)) then
		createEvent(60 * 1000, "CityControlLanding", "spawnCityLanding", "", "")
	end

	writeStringData("CityControlLandingPlanet:", planet)
	writeData("CityControlLandingCity:", determineCity)
	writeData("CityControlLanding:dialogueNumber", getRandomNumber(1, 3))

	local controllingFaction = getControllingFaction(planet)
	local rebelLanding = self.rebelLanding
	local imperialLanding = self.imperialLanding

	if (city ~= "bestine") and (controllingFaction == FACTIONREBEL or city == "anchorhead" or city == "moenia") then
		--(planet, template,  x, z, y, cell, direction)
		local pShuttle = spawnSceneObject(planet, rebelLanding[1], cityCoords[1], cityCoords[2], cityCoords[3], 0, math.rad(cityCoords[4]))

		if (pShuttle ~= nil) then
			CreatureObject(pShuttle):setCustomObjectName("Transport Shuttle")
			CreatureObject(pShuttle):setPosture(PRONE)
			CreatureObject(pShuttle):setOptionBit(NONE)
			local pOid = SceneObject(pShuttle):getObjectID()

			writeData(pOid .. ":rebelTransport", determineCity)
			writeData(1 .. ":LandingParty", pOid)
			writeStringData("LandingType:", "REBEL")
			writeStringData(pOid .. ":shuttlePosture", "PRONE")

			local templateRoll = getRandomNumber(2)
			writeData("RebelCelebrity:", templateRoll)

			createEvent(20000, "CityControlLanding", "handleShuttlePosture", pShuttle, "")
			createEvent(10000, "CityControlLanding", "broadcastMessage", pShuttle, "")
		end
	else
		--(planet, template,  x, z, y, cell, direction)
		local pShuttle = spawnSceneObject(planet, imperialLanding[1], cityCoords[1], cityCoords[2], cityCoords[3], 0, math.rad(cityCoords[4]))

		if (pShuttle ~= nil) then
			CreatureObject(pShuttle):setCustomObjectName("Lambda Shuttle")

			local pOid = SceneObject(pShuttle):getObjectID()

			writeData(pOid .. ":imperialLambda", determineCity)
			writeData(1 .. ":LandingParty", pOid)
			writeStringData("LandingType:", "IMPERIAL")
			writeStringData(pOid .. ":shuttlePosture", "UPRIGHT")

			createEvent(30000, "CityControlLanding", "handleShuttlePosture", pShuttle, "")
			createEvent(20000, "CityControlLanding", "broadcastMessage", pShuttle, "")
		end
	end
end

function CityControlLanding:broadcastMessage(pShuttle)
	if (pShuttle == nil) then
		return
	end

	local playerTable = SceneObject(pShuttle):getPlayersInRange(150)
	local landingType = readStringData("LandingType:")
	local broadcastTemplate = ""

	if (landingType == "REBEL") then
		local celebrity = readData("RebelCelebrity:")

		if (celebrity == 1) then
			broadcastTemplate= "<<Incoming Alliance Transmission: Group control, this is shuttle Alder Six-Two. We have Skywalker on board and are coming in for a landing.>>"
		else
			broadcastTemplate= "<<Incoming Alliance Transmission: Group control, this is shuttle Alder Six-Two. We have the Princess on board and are coming in for a landing.>>"
		end
	else
		broadcastTemplate = "<<Incoming Imperial Transmission: Command station, this is ST321, code clearance blue. We're starting our approach.>>"
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
	local shuttlePosture = readStringData(shuttleID .. ":shuttlePosture")

	if (landingType == "IMPERIAL") then
		if (shuttlePosture == "UPRIGHT") then
			CreatureObject(pShuttle):setPosture(PRONE)
			writeStringData(shuttleID .. ":shuttlePosture", "PRONE")
			createEvent(19000, "CityControlLanding", "spawnImperialLandingParty", pShuttle, "")
			return
		else
			CreatureObject(pShuttle):setPosture(UPRIGHT)
			createEvent(2 * 60 * 1000, "CityControlLanding", "cleanUp", pShuttle, "")
			return
		end
	elseif (landingType == "REBEL") then
		if (shuttlePosture == "PRONE") then
			CreatureObject(pShuttle):setPosture(UPRIGHT)
			writeStringData(shuttleID .. ":shuttlePosture", "UPRIGHT")
			createEvent(23000, "CityControlLanding", "spawnRebelLandingParty", pShuttle, "")
			return
		else
			CreatureObject(pShuttle):setPosture(PRONE)
			createEvent(2 * 60 * 1000, "CityControlLanding", "cleanUp", pShuttle, "")
			return
		end
	else
		printLuaError("Wrong Shuttle Type in CityControlLanding Screenplay")
	end
end

function CityControlLanding:spawnRebelLandingParty(shuttle)
	local pShuttle = shuttle

	if (pShuttle == nil) then
		return
	end

	local pShuttleID = SceneObject(pShuttle):getObjectID()
	local determinedCity = readData(pShuttleID .. ":rebelTransport")

	local spawnCityPlanet = self.locations[determinedCity]
	local coordTable = self.coordinates
	local cityCoords = coordTable[determinedCity]
	local city = spawnCityPlanet[1]
	local planet = spawnCityPlanet[2]

	local totalSpawns = #self.rebelLanding
	local template = self.rebelLanding

	local xLoc = cityCoords[1]
	local yLoc = cityCoords[3]

	for i = 2, totalSpawns, 1 do
		if (template[i] == "lukeLeia") then
			local chosenTemplate = ""
			local celebrity = readData("RebelCelebrity:")
			local yLeiaLuke = yLoc - 11

			if (celebrity == 1) then
				chosenTemplate = "luke_skywalker_city_control"
			else
				chosenTemplate = "leia_organa_city_control"
			end

			--template, level, x, z, y, direction, cell, mood},
			local pMobile = spawnMobile(planet, chosenTemplate, 0, xLoc, cityCoords[2], yLeiaLuke, cityCoords[4], 0, "")

			if (pMobile ~= nil) then
				AiAgent(pMobile):setAiTemplate("citypatrol")
				AiAgent(pMobile):setFollowState(4)
				CreatureObject(pMobile):setPvpStatusBitmask(0)

				local mobileID = SceneObject(pMobile):getObjectID()

				writeData(i .. ":LandingParty", mobileID)
				writeData(mobileID .. ":spawnNumber", i)
				writeStringData("NextPoint:", "speech")
				writeData("CityControlLanding:speechStep", 1)

				createObserver(DESTINATIONREACHED, "CityControlLanding", "destinationReached", pMobile)
				createEvent(5000, "CityControlLanding", "setupMusic", pMobile, "")
				createEvent(5000, "CityControlLanding", "moveTo", pMobile, "")
			end
		else
			local xOffset = xLoc + getRandomNumber(6)
			local yOffset = yLoc - 15

			--template, level, x, z, y, direction, cell, mood},
			local pMobile = spawnMobile(planet, template[i], 0, xOffset, cityCoords[2], yOffset, cityCoords[4], 0, "")

			if (pMobile ~= nil) then
				AiAgent(pMobile):setAiTemplate("")
				AiAgent(pMobile):setFollowState(4)
				CreatureObject(pMobile):setPvpStatusBitmask(1)

				local mobileID = SceneObject(pMobile):getObjectID()

				writeData(i .. ":LandingParty", mobileID)
				writeData(mobileID .. ":spawnNumber", i)

				createObserver(CREATUREDESPAWNED, "CityControlLanding", "onDespawn", pMobile)
			end
		end
	end
end

function CityControlLanding:spawnImperialLandingParty(shuttle)
	local pShuttle = shuttle

	if (pShuttle == nil) then
		return
	end

	local pShuttleID = SceneObject(pShuttle):getObjectID()
	local determinedCity = readData(pShuttleID .. ":imperialLambda")

	local spawnCityPlanet = self.locations[determinedCity]
	local coordTable = self.coordinates
	local cityCoords = coordTable[determinedCity]
	local city = spawnCityPlanet[1]
	local planet = spawnCityPlanet[2]

	local totalSpawns = #self.imperialLanding
	local template = self.imperialLanding
	local xLoc = cityCoords[1]
	local yLoc = cityCoords[3]

	for i = 2, totalSpawns, 1 do
		if (template[i] == "darth_vader_city_control") then

			--template, level, x, z, y, direction, cell, mood},
			local pMobile = spawnMobile(planet, template[i], 0, xLoc , cityCoords[2], yLoc, cityCoords[4], 0, "")

			if (pMobile ~= nil) then
				AiAgent(pMobile):setAiTemplate("citypatrol")
				AiAgent(pMobile):setFollowState(4)
				CreatureObject(pMobile):setPvpStatusBitmask(0)

				local mobileID = SceneObject(pMobile):getObjectID()

				writeData(i .. ":LandingParty", mobileID)
				writeData(mobileID .. ":spawnNumber", i)
				writeStringData("NextPoint:", "speech")
				writeData("CityControlLanding:speechStep", 1)

				createObserver(DESTINATIONREACHED, "CityControlLanding", "destinationReached", pMobile)
				createEvent(5000, "CityControlLanding", "setupMusic", pMobile, "")
				createEvent(5000, "CityControlLanding", "moveTo", pMobile, "")
			end
		else
			local yOffset = (yLoc - 10 - i)

			--template, level, x, z, y, direction, cell, mood},
			local pMobile = spawnMobile(planet, template[i], 0, xLoc, cityCoords[2], yOffset, cityCoords[4], 0, "")

			if (pMobile ~= nil) then
				AiAgent(pMobile):setAiTemplate("")
				AiAgent(pMobile):setFollowState(4)
				AiAgent(pMobile):setCreatureBit(SCANNING_FOR_CONTRABAND)
				CreatureObject(pMobile):setPvpStatusBitmask(1)

				local mobileID = SceneObject(pMobile):getObjectID()

				writeData(i .. ":LandingParty", mobileID)
				writeData(mobileID .. ":spawnNumber", i)

				createObserver(CREATUREDESPAWNED, "CityControlLanding", "onDespawn", pMobile)
			end
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
		self:moveTo(pMobile)
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
    createEvent(10 * 1000, "CityControlLanding", "doSpeech", pMobile, "")
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
			local posY = spawnCoords[3] - 10
			AiAgent(pMobile):setAiTemplate("manualescortwalk")
			AiAgent(pMobile):setNextPosition(spawnCoords[1], spawnCoords[2], posY, 0)
		end
	elseif (landingType == "IMPERIAL") then
		if (nextPoint == "speech") then
			local posY = spawnCoords[3] - 10
			AiAgent(pMobile):setNextPosition(spawnCoords[1], spawnCoords[2], posY, 0)
		else
			AiAgent(pMobile):setAiTemplate("manualescortwalk")
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
		createEvent(1000, "CityControlLanding", "doSpeech", pMobile, "")
	else
		self:despawnLanding()
    end

    return 0
end

function CityControlLanding:despawnLanding()
	local pShuttleID = readData(1 .. ":LandingParty")
	local pShuttle = getSceneObject(pShuttleID)

	if (pShuttle == nil) then
		return
	end

	createEvent(5 * 1000, "CityControlLanding", "despawnMobiles", "", "")
	createEvent(20 * 1000, "CityControlLanding", "handleShuttlePosture", pShuttle, "")
end

function CityControlLanding:despawnMobiles()
	for i = 2, 9, 1 do
		local pMobileID = readData(i .. ":LandingParty")
		local pMobile = getSceneObject(pMobileID)

		if (pMobile ~= nil) then
			if (CreatureObject(pMobile):isInCombat()) then
				createEvent(30 * 1000, "CityControlLanding", "mobileDespawn", pMobile, "")
			else
				createEvent(1000, "CityControlLanding", "moveTo", pMobile, "")
				createEvent(10 * 1000, "CityControlLanding", "mobileDespawn", pMobile, "")
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

function CityControlLanding:onDespawn(mobile)
	local pMobile = mobile

	if (pMobile == nil) then
		return
	end

	local landingType = readStringData("LandingType:")

	if (LandingType == "REBEL") then
		createEvent(60 * 1000, "CityControlLanding", "respawnRebel", pMobile, "")
	else
		createEvent(60 * 1000, "CityControlLanding", "respawnImperial", pMobile, "")
	end
	return 1
end

function CityControlLanding:respawnRebel(pMobile)
	if (pMobile == nil) then
		return
	end

	local cityNumber = readData("CityControlLandingCity:")
	local planet = readStringData("CityControlLandingPlanet:")

	local mobileID= SceneObject(pMobile):getObjectID()

	local spawnCoords = self.coordinates[cityNumber]
	local xOffset = spawnCoords[1] + getRandomNumber(6)
	local yOffset = spawnCoords[3] - 10
	local spawnNumber = readData(mobileID .. ":spawnNumber")
	local rebelLanding = self.rebelLanding
	local template = rebelLanding[spawnNumber]

	deleteData(mobileID .. ":spawnNumber")

	--template, level, x, z, y, direction, cell, mood},
	local pMobile = spawnMobile(planet, template, 0, xOffset, spawnCoords[2], yOffset, spawnCoords[4], 0, "")

	if (pMobile ~= nil) then
		AiAgent(pMobile):setAiTemplate("")
		AiAgent(pMobile):setFollowState(4)

		local mobileID = SceneObject(pMobile):getObjectID()

		writeData(spawnNumber .. ":LandingParty", mobileID)
		writeData(mobileID .. ":spawnNumber", spawnNumber)

		createObserver(CREATUREDESPAWNED, "CityControlLanding", "onDespawn", pMobile)
	end
end

function CityControlLanding:respawnImperial(pMobile)
	if (pMobile == nil) then
		return
	end

	local cityNumber = readData("CityControlLandingCity:")
	local planet = readStringData("CityControlLandingPlanet:")

	local mobileID= SceneObject(pMobile):getObjectID()

	local spawnNumber = readData(mobileID .. ":spawnNumber")
	local spawnCoords = self.coordinates[cityNumber]
	local yOffset = (spawnCoords[3] - 10 - spawnNumber)
	local template = self.imperialLanding[spawnNumber]

	deleteData(mobileID .. ":spawnNumber")

	--template, level, x, z, y, direction, cell, mood},
	local pMobile = spawnMobile(planet, template, 0, spawnCoords[1], spawnCoords[2], yOffset, spawnCoords[4], 0, "")

	if (pMobile ~= nil) then
		AiAgent(pMobile):setAiTemplate("")
		AiAgent(pMobile):setFollowState(4)

		local mobileID = SceneObject(pMobile):getObjectID()

		writeData(spawnNumber .. ":LandingParty", mobileID)
		writeData(mobileID .. ":spawnNumber", spawnNumber)

		createObserver(CREATUREDESPAWNED, "CityControlLanding", "onDespawn", pMobile)
	end
end

function CityControlLanding:cleanUp(shuttle)
	local pShuttle = shuttle

	if (pShuttle == nil) then
		return
	end

	local pShuttleID = SceneObject(pShuttle):getObjectID()

	deleteData(pShuttleID .. "imperialLambda")
	deleteData(pShuttleID .. ":rebelTransport")
	deleteData("CityControlLandingCity:")
	deleteData("CityControlLanding:speechStep")
	deleteStringData(pShuttleID .. ":shuttlePosture")
	deleteStringData("CityControlLandingPlanet:")
	deleteStringData("NextPoint:")

	local landingType = readData("LandingType:")

	if (landingType == "REBEL") then
		local totalRebel = #self.rebelLandin

		for i = 2, totalrebel, 1 do
			deleteData(i .. ":LandingParty")
		end

		deleteData("RebelCelebrity:")
	else
		local totalImperial = #self.imperialLanding

		for i = 2, totalImperial, 1 do
			deleteData(i .. ":LandingParty")
		end
	end

	deleteStringData("LandingType:")
	SceneObject(pShuttle):destroyObjectFromWorld()

	--createEvent(4 * 60 * 60 * 1000, "CityControlLanding", "chanceToSpawn", "", "") --4hrs
	createEvent(30 * 60 * 1000, "CityControlLanding", "chanceToSpawn", "", "") -- 30min TESTING
end