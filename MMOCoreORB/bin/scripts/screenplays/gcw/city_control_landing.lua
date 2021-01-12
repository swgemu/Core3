CityControlLanding = ScreenPlay:new {
	numberOfActs = 1,

	screenplayName = "CityControlLanding",

	locations = {
		{"coronet", "corellia"},
		{"bela_vistal", "corellia"},
		--{"theed", "naboo"},
		--{"moenia", "naboo"},
		{"bestine", "tatooine"},
		--{"anchorhead", "tatooine"}
	},

	coordinates = {
		--{x, z, y, direction}
		{-148, 28, -4715, 179}, --Coronet
		{6902, 330, -5550, 179}, -- Bela Vistal
		--{-4897, 6, 4124, 179}, --Theed
		--{4812, 4, -4700, 179}, --  Moenia
		{-1282, 12, -3589, 180}, --Bestine
		--{111, 52, -5348, 171}, --Anchorhead
	},

	rebelLanding = {"object/creature/npc/theme_park/event_transport.iff", "lukeLeia", "rebel_commandant", "rebel_ensign", "rebel_engineer", "rebel_commodore", "fbase_rebel_commando", "fbase_rebel_commando"},
	imperialLanding = {"object/creature/npc/theme_park/lambda_shuttle.iff", "darth_vader", "elite_novatrooper_squad_leader", "elite_novatrooper", "elite_novatrooper", "elite_novatrooper", "elite_novatrooper", "elite_novatrooper", "elite_novatrooper_cadet"},

}

registerScreenPlay("CityControlLanding", true)

function CityControlLanding:start()
	self:chanceToSpawn()
end

function CityControlLanding:chanceToSpawn()
	local chance = getRandomNumber(4)

	if (chance <= 5) then
		printf("  Landing sequence Started  ")
		createEvent(90 * 1000, "CityControlLanding", "spawnCityLanding", "", "")
	else
		createEvent(360 * 60 * 1000, "CityControlLandingScreenplay", "chanceToSpawn", "", "")
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
		createEvent(60000, "CityControlLanding", "spawnCityLanding", "", "")
	end

	printf ( "    CALLED spawnCityLanding     ")

	writeStringData("CityControlLandingPlanet:", planet)
	writeData("CityControlLandingCity:", determineCity)

	local controllingFaction = getControllingFaction(planet)
	local rebelLanding = self.rebelLanding
	local imperialLanding = self.imperialLanding

	if (city ~= "bestine") and (controllingFaction == FACTIONREBEL or city == "anchorhead" or city == "moenia") then
		--(planet, template,  x, z, y, cell, direction)
		local pShuttle = spawnSceneObject(planet, rebelLanding[1], cityCoords[1], cityCoords[2], cityCoords[3], 0, math.rad(cityCoords[4]))
		printf("  spawned rebel transport  ")

		if (pShuttle ~= nil) then
			CreatureObject(pShuttle):setCustomObjectName("Transport Shuttle")
			CreatureObject(pShuttle):setPosture(PRONE)
			local pOid = SceneObject(pShuttle):getObjectID()

			printf("      pShuttle is not null    ")
			printf(" determineCity ==   ")
			printf(determineCity)

			writeData(pOid .. ":rebelTransport", determineCity)
			writeStringData("ShuttleType:", "transport")
			writeStringData(pOid .. ":shuttlePosture", "PRONE")

			printf("  REBEL SHUTTLE DROP IN 30s")
			createEvent(30000, "CityControlLanding", "handleShuttlePosture", pShuttle, "")
		end
	else
		--(planet, template,  x, z, y, cell, direction)
		local pShuttle = spawnSceneObject(planet, imperialLanding[1], cityCoords[1], cityCoords[2], cityCoords[3], 0, math.rad(cityCoords[4]))
		printf("spawned imperial lambda")

		if (pShuttle ~= nil) then
			CreatureObject(pShuttle):setCustomObjectName("Lambda Shuttle")

			local pOid = SceneObject(pShuttle):getObjectID()

			printf("      pShuttle is not null    ")
			printf(" determineCity ==   ")
			printf(determineCity)

			writeData(pOid .. ":imperialLambda", determineCity)
			writeStringData("ShuttleType:", "lambda")
			writeStringData(pOid .. ":shuttlePosture", "UPRIGHT")

			createEvent(10000, "CityControlLanding", "handleShuttlePosture", pShuttle, "")
		end
	end
end

function CityControlLanding:handleShuttlePosture(shuttle)
	local pShuttle = shuttle

	if (pShuttle == nil) then
		return
	end

	local shuttleID = SceneObject(pShuttle):getObjectID()
	local shuttleType = readStringData("ShuttleType:")
	local shuttlePosture = readStringData(shuttleID .. ":shuttlePosture")

	printf("    SHUTTLE TYPE ==    ")
	printf(shuttleType)

	printf("    Shuttle Posture ==   ")
	printf(shuttlePosture)

	if (shuttleType == "lambda") then
		printf(" passed imperial lambda check")
		if (shuttlePosture == "UPRIGHT") then
			CreatureObject(pShuttle):setPosture(PRONE)
			writeStringData(shuttleID .. ":shuttlePosture", "PRONE")
			createEvent(19000, "CityControlLanding", "spawnImperialLandingParty", pShuttle, "")
			return
		else
			CreatureObject(pShuttle):setPosture(UPRIGHT)
			createEvent(10 * 60 * 1000, "CityControlLanding", "cleanUp", pShuttle, "")
			return
		end
	elseif (shuttleType == "transport") then
		printf(" passed rebel transport check")
		if (shuttlePosture == "PRONE") then
			CreatureObject(pShuttle):setPosture(UPRIGHT)
			writeStringData(shuttleID .. ":shuttlePosture", "UPRIGHT")
			createEvent(23000, "CityControlLanding", "spawnRebelLandingParty", pShuttle, "")
			return
		else
			CreatureObject(pShuttle):setPosture(PRONE)
			createEvent(10 * 60 * 1000, "CityControlLanding", "cleanUp", pShuttle, "")
			return
		end
	else
		printLuaError("   Wrong Shuttle Type in CityControlLanding Screenplay   ")
	end
end

function CityControlLanding:spawnRebelLandingParty(shuttle)
	local pShuttle = shuttle

	if (pShuttle == nil) then
		return
	end

	local pShuttleID = SceneObject(pShuttle):getObjectID()
	local determinedCity = readData(pShuttleID .. ":rebelTransport")

	printf("     Determined City =   ")
	printf(determinedCity)


	local spawnCityPlanet = self.locations[determinedCity]
	local coordTable = self.coordinates
	local cityCoords = coordTable[determinedCity]
	local city = spawnCityPlanet[1]

	printf("   City = ")
	printf(city)


	local planet = spawnCityPlanet[2]

	printf("   Planet = ")
	printf(planet)


	local totalSpawns = #self.rebelLanding
	local template = self.rebelLanding

	local xLoc = cityCoords[1]
	local yLoc = cityCoords[3]

	printf( " x Location =  ")
	printf(xLoc)
	printf("  y Location =  ")
	printf(yLoc)

	for i = 2, totalSpawns, 1 do
		if (template[i] == "lukeLeia") then
			local chosenTemplate = ""
			local tempRoll = getRandomNumber(2)
			local yLeiaLuke = yLoc - 15

			if (tempRoll == 2) then
				chosenTemplate = "luke_skywalker"
			else
				chosenTemplate = "leia_organa"
			end

			--template, level, x, z, y, direction, cell, mood},
			local pMobile = spawnMobile(planet, chosenTemplate, 0, xLoc, cityCoords[2], yLeiaLuke, cityCoords[4], 0, "")

			if (pMobile ~= nil) then
				AiAgent(pMobile):setAiTemplate("citypatrol")
				AiAgent(pMobile):setFollowState(4)
				CreatureObject(pMobile):clearOptionBit(CONVERSABLE)

				local mobileID = SceneObject(pMobile):getObjectID()

				writeData(i .. ":rebelLandingParty", mobileID)
				writeData(mobileID .. ":spawnNumber", i)
				createEvent(2000, "CityControlLanding", "setupMusic", pMobile, "")
			end
		else
			local xOffset = xLoc + getRandomNumber(6)
			local yOffset = yLoc - 15

			--template, level, x, z, y, direction, cell, mood},
			local pMobile = spawnMobile(planet, template[i], 0, xOffset, cityCoords[2], yOffset, cityCoords[4], 0, "")

			if (pMobile ~= nil) then
				AiAgent(pMobile):setAiTemplate("")
				AiAgent(pMobile):setFollowState(4)

				local mobileID = SceneObject(pMobile):getObjectID()

				writeData(i .. ":rebelLandingParty", mobileID)
				writeData(mobileID .. ":spawnNumber", i)

				createObserver(CREATUREDESPAWNED, "CityControlLanding", "onDespawn", pMobile)
			end
		end
	end

	createEvent(10 * 60 * 1000, "CityControlLanding", "despawnRebelLanding", pShuttle, "")
end

function CityControlLanding:spawnImperialLandingParty(shuttle)
	local pShuttle = shuttle

	if (pShuttle == nil) then
		return
	end

	local pShuttleID = SceneObject(pShuttle):getObjectID()
	local determinedCity = readData(pShuttleID .. ":imperialLambda")

	printf("     Determined City =   ")
	printf(determinedCity)

	local spawnCityPlanet = self.locations[determinedCity]
	local coordTable = self.coordinates
	local cityCoords = coordTable[determinedCity]
	local city = spawnCityPlanet[1]

	printf("   City = ")
	printf(city)

	local planet = spawnCityPlanet[2]

	printf("   Planet = ")
	printf(planet)


	local totalSpawns = #self.imperialLanding
	local template = self.imperialLanding
	local xLoc = cityCoords[1]
	local yLoc = cityCoords[3]


	for i = 2, totalSpawns, 1 do

		if (template == "darth_vader") then
			local yVader = yLoc - 5

			--template, level, x, z, y, direction, cell, mood},
			local pMobile = spawnMobile(planet, template[i], 0, xLoc , cityCoords[2], yVader, cityCoords[4], 0, "")

			if (pMobile ~= nil) then
				AiAgent(pMobile):setAiTemplate("citypatrol")
				AiAgent(pMobile):setFollowState(4)
				CreatureObject(pMobile):clearOptionBit(CONVERSABLE)

				local mobileID = SceneObject(pMobile):getObjectID()

				writeData(i .. ":imperialLandingParty", mobileID)
				writeData(mobileID .. ":spawnNumber", i)
				createEvent(2000, "CityControlLanding", "setupMusic", pMobile, "")
			end
		else
			local yOffset = (yLoc - 10 - i)

			--template, level, x, z, y, direction, cell, mood},
			local pMobile = spawnMobile(planet, template[i], 0, xLoc, cityCoords[2], yOffset, cityCoords[4], 0, "")

			if (pMobile ~= nil) then
				AiAgent(pMobile):setAiTemplate("")
				AiAgent(pMobile):setFollowState(4)

				local aiAgent = AiAgent(pMobile)
				aiAgent:setCreatureBit(SCANNING_FOR_CONTRABAND)

				local mobileID = SceneObject(pMobile):getObjectID()

				writeData(i .. ":imperialLandingParty", mobileID)
				writeData(mobileID .. ":spawnNumber", i)

				createObserver(CREATUREDESPAWNED, "CityControlLanding", "onDespawn", pMobile)
			end
		end
	end
	createEvent(2 * 60 * 1000, "CityControlLanding", "despawnImperialLanding", pShuttle, "")
end

function CityControlLanding:setupMusic(mobile)
	local pMobile = mobile

	if (pMobile == nil) then
		return
	end

	local playerTable = SceneObject(pMobile):getPlayersInRange(100)
	local shuttleType = readStringData("ShuttleType:")
	local musicTemplate = "sound/music_emperor_theme.snd"

	if (shuttleType == "transport") then
		local musicTemplate = "sound/music_leia_theme_stereo.snd"
	end

	for i = 1, #playerTable, 1 do
		local pPlayer = playerTable[i]

		if (pPlayer ~= nil) then
			CreatureObject(pPlayer):playMusicMessage(musicTemplate)
		end
	end
end

function CityControlLanding:despawnRebelLanding(shuttle)
	local pShuttle = shuttle

	if (pShuttle == nil) then
		return
	end

	local pShuttleID = SceneObject(pShuttle):getObjectID()
	local determinedCity = readData(pShuttleID .. ":rebelTransport")

	printf("     Determined City Despawn City =   ")
	printf(determinedCity)

	local spawnCityPlanet = self.locations[determinedCity]
	local coordTable = self.coordinates
	local cityCoords = coordTable[determinedCity]
	local totalSpawns = #self.rebelLanding

	printf("    Total despawns:   ")
	printf(totalSpawns)

	for i = 2, totalSpawns, 1 do
		local pMobileID = readData(i .. ":rebelLandingParty")

		if (pMobileID ~= nil) then
			printf("   pMobileID despawn is not nul   ")
			local pMobile = CreatureObject(pMobileID):getObject()

			--AiAgent(pMobile):stopWaiting()
			--AiAgent(pMobile):setWait(0)
			--AiAgent(pMobile):setNextPosition(cityCoords[1], cityCoords[2], cityCoords[3], 0)
			--AiAgent(pMobile):executeBehavior()

			--createObserver(DESTINATIONREACHED, "CityControlLanding", "despawnMovile", pMobile)
			createEvent(getRandomNumber(5) * 1000, "CityControlLanding", "despawns", pMobile, "")
		end
	end
	createEvent(3000, "CityControlLanding", "handleShuttlePosture", pShuttle, "")
end

function CityControlLanding:despawnImperialLanding(shuttle)
	local pShuttle = shuttle

	if (pShuttle == nil) then
		return
	end

	local pShuttleID = SceneObject(pShuttle):getObjectID()
	local determinedCity = readData(pShuttleID .. ":imperialLambda")

	printf("     Determined City Despawn City =   ")
	printf(determinedCity)

	local spawnCityPlanet = self.locations[determinedCity]
	local coordTable = self.coordinates
	local cityCoords = coordTable[determinedCity]
	local totalSpawns = #self.imperialLanding

	printf("    Total despawns:   ")
	printf(totalSpawns)

	for i = 2, totalSpawns, 1 do
		local pMobileID = readData(i .. ":imperialLandingParty")

		printf("   pMobileID   ==   ")
		printf(pMobileID)

		if (pMobileID ~= nil) then
			printf("   pMobileID despawn is not nul   ")

			--AiAgent(pMobile):setNextPosition(cityCoords[1], cityCoords[2], cityCoords[3], 0)
			--AiAgent(pMobile):executeBehavior()

			--createObserver(DESTINATIONREACHED, "CityControlLanding", "despawnMovile", pMobile)
			createEvent(5000, "CityControlLanding", "despawn", tostring(pMobileID), "")
		end
	end
	createEvent(3000, "CityControlLanding", "handleShuttlePosture", pShuttle, "")
end

function CityControlLanding:despawn(pMobileID)
	local despawnID = pMobileID

	printf("   Mobile Despawn Called    ")

	if (despawnID == nil) then
		printf("    MOBILE ID TO DESPAWN NIL    ")
		return
	end

	if (CreatureObject(despawnMob):isInCombat()) then
		createEvent(5 * 1000, "CityControlLanding", "despawn", despawnID, "")
		return
	end

	SceneObject(despawnID):destroyObjectFromWorld()
end

function CityControlLanding:onDespawn(mobile)
	local pMobile = mobile

	if (pMobile == nil) then
		return
	end

	local shuttleType = readStringData("ShuttleType:")

	if (shuttleType == "transport") then
		createEvent(3 * 60 * 1000, "CityControlLanding", "respawnRebel", pMobile, "")
	else
		createEvent(10000, "CityControlLanding", "respawnImperial", pMobile, "")
	end
	return 1
end

function CityControlLanding:respawnRebel(mobile)
	local pMobile = mobile
	local cityNumber = readData("CityControlLandingCity:")
	local planet = readStringData("CityControlLandingPlanet:")

	if (pMobile == nil) then
		return
	end

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

		writeData(spawnNumber .. ":rebelLandingParty", mobileID)
		writeData(mobileID .. ":spawnNumber", spawnNumber)

		createObserver(CREATUREDESPAWNED, "CityControlLanding", "onDespawn", pMobile)
	end
end

function CityControlLanding:respawnImperial(mobile)
	local pMobile = mobile
	local cityNumber = readData("CityControlLandingCity:")
	local planet = readStringData("CityControlLandingPlanet:")

	if (pMobile == nil) then
		return
	end

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

		writeData(spawnNumber .. ":rebelLandingParty", mobileID)
		writeData(mobileID .. ":spawnNumber", spawnNumber)

		createObserver(CREATUREDESPAWNED, "CityControlLanding", "onDespawn", pMobile)
	end
end

function CityControlLanding:cleanUp(shuttle)
	local pShuttle = shuttle

	if (pShuttle == nil) then
		return
	end

	printf("  CLEANUP TRIGGERED!!!   ")
	local pShuttleID = SceneObject(pShuttle):getObjectID()

	deleteData(pShuttleID .. "imperialLambda")
	deleteData(pShuttleID .. ":rebelTransport")
	deleteStringData(pShuttleID .. ":shuttlePosture")
	deleteStringData("CityControlLandingPlanet:")
	deleteData("CityControlLandingCity:")

	local shuttleType = readData("ShuttleType:")

	if (shuttleType == "transport") then
		local totalRebel = #self.rebelLanding

		for i = 2, totalrebel, 1 do
			deleteData(i .. ":rebelLandingParty")
		end
	else
		local totalImperial = #self.imperialLanding

		for i = 2, totalImperial, 1 do
			deleteData(i .. ":imperialLandingParty")
		end
	end

	deleteStringData("ShuttleType")
	SceneObject(pShuttle):destroyObjectFromWorld()

	createEvent(300 * 60 * 1000, "CityControlLanding", "chanceToSpawn", "", "")
end