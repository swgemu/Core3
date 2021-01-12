CityControlLanding = ScreenPlay:new {
	numberOfActs = 1,

	screenplayName = "CityControlLanding",

	locations = {{"coronet", "corellia"}, {"theed", "naboo"}, {"bestine", "tatooine"}, {"anchorhead", "tatooine"}},

	coordinates = {
		--{x, z, y, direction}
		{-148, 28, -4715, 179}, --Coronet
		{-4897, 6, 4124, 179}, --Theed
		{-1282, 12, -3589, 180}, --Bestine
		{111, 52, -5348, 171}, --Anchorhead
	},

	rebelLanding = {"object/creature/npc/theme_park/transport_shuttle.iff", "lukeLeia", "rebel_corporal", "rebel_commando"},
	imperialLanding = {"object/creature/npc/theme_park/lambda_shuttle.iff", "darth_vader", "elite_novatrooper_commander", "elite_novatrooper", "elite_novatrooper", "elite_novatrooper", "elite_novatrooper", "elite_novatrooper", "elite_novatrooper"},

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
	local coordTable = self.coordinates
	local cityCoords = coordTable[determineCity]
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

	if (city ~= "bestine") and (controllingFaction == FACTIONREBEL or city == "anchorhead") then
		--(planet, template,  x, z, y, cell, direction)
		local pShuttle = spawnSceneObject(planet, rebelLanding[1], cityCoords[1], cityCoords[2], cityCoords[3], 0, math.rad(cityCoords[4]))
		printf("  spawned rebel transport  ")

		if (pShuttle ~= nil) then
			CreatureObject(pShuttle):setCustomObjectName("Transport Shuttle")

			local pOid = SceneObject(pShuttle):getObjectID()

			printf("      pShuttle is not null    ")
			printf(" determineCity ==   ")
			printf(determineCity)

			writeData(pOid .. ":rebelTransport", determineCity)
			writeStringData(pOid .. ":shuttleType", "transport")
			writeStringData(pOid .. ":shuttlePosture", "PRONE")

			createEvent(10000, "CityControlLanding", "handleShuttlePosture", pShuttle, "")
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
			writeStringData(pOid .. ":shuttleType", "lambda")
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
	local shuttleType = readStringData(shuttleID .. ":shuttleType")
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
			createEvent(20000, "CityControlLanding", "spawnImperialLandingParty", pShuttle, "")
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
				AiAgent(pMobile):setAiTemplate("")
				AiAgent(pMobile):setFollowState(4)

				local mobileID = SceneObject(pMobile):getObjectID()

				writeData(i .. ":rebelLandingParty", mobileID)
			end
		else
			local xOffset = xLoc + getRandomNumber(6)
			local yOffset = yLoc - 15

			--template, level, x, z, y, direction, cell, mood},
			local pMobile = spawnMobile(planet, template[i], 0, xLoc, cityCoords[2], yLoc, cityCoords[4], 0, "")

			if (pMobile ~= nil) then
				AiAgent(pMobile):setAiTemplate("")
				AiAgent(pMobile):setFollowState(4)

				local mobileID = SceneObject(pMobile):getObjectID()

				writeData(i .. ":rebelLandingParty", mobileID)
				createObserver(CREATUREDESPAWNED, "CityControlLanding", "onDespawn", pMobile)
			end
		end
	end

	createEvent(10 * 60 * 1000, "CityControlLanding", "despawnRebelLanding", pShuttle, "")
	printf("   should despawn rebel laning    ")
end

function CityControlLanding:spawnImperialLandingParty(shuttle)
	local pShuttle = shuttle

	if (pShuttle == nil) then
		createEvent(60000, "CityControlLanding", "spawnCityLanding", "", "") --call cleanup?
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
				AiAgent(pMobile):setAiTemplate("")
				AiAgent(pMobile):setFollowState(4)

				local mobileID = SceneObject(pMobile):getObjectID()

				writeData(i .. ":imperialLandingParty", mobileID)
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
			end
		end
	end
	createEvent(10 * 60 * 1000, "CityControlLanding", "despawnImperialLanding", pShuttle, "")
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
			createEvent(5000, "CityControlLanding", "despawn", pMobileID, "")
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

	local shuttleType = readData(pShuttleID .. ":shuttleType")
	local totalRebel = #self.rebelLanding
	local totalImperial = #self.imperialLanding

	if (shuttleType == "transport") then
		for i = 2, totalrebel, 1 do
			deleteData(i .. ":rebelLandingParty")
		end
	else
		for i = 2, totalImperial, 1 do
			deleteData(i .. "imperialLandingParty")
		end
	end

	deleteStringData(pShuttleID .. ":shuttleType")
	SceneObject(pShuttle):destroyObjectFromWorld()

	createEvent(300 * 60 * 1000, "CityControlLanding", "chanceToSpawn", "", "")
end

function CityControlLanding:onDespawn(mobile)
	local pMobile = mobile

	if (pMobile == nil) then
		printf( "    pMobile is nil for re-spawn    ")
		return
	end

	local mobileID= SceneObject(pMobile):getObjectID()
	local landingFaction = readStringData("LandingType:")
	local planet = readStringData("CityControlLandingPlanet:")

	if (planet == nil) then
		return
	end

	local cityNum = readData("CityControlLandingCity:")
	local coordTable = self.coordinates
	local cityCoords = coordTable[cityNum]

	local xLoc = cityCoords[1]
	local yLoc = cityCoords[3]
	local spawnNumber
	local spawnTable

	if (landingFaction == "REBEL") then
		spawnNumber = readData("rebelLandingParty", mobileID)

		if (spawnNumber ~= nil) then
			local rebelLanding = self.rebelLanding
			spawnTable = rebelLanding[spawnNumber]

			local xOffset = xLoc + getRandomNumber(6)
			local yOffset = yLoc - 15

			--template, level, x, z, y, direction, cell, mood},
			local pMobile = spawnMobile(planet, template[i], 0, xLoc, cityCoords[2], yLoc, cityCoords[4], 0, "")

			if (pMobile ~= nil) then
				AiAgent(pMobile):setAiTemplate("")
				AiAgent(pMobile):setFollowState(4)

				local mobileID = SceneObject(pMobile):getObjectID()

				writeData(i .. ":rebelLandingParty", mobileID)
				createObserver(CREATUREDESPAWNED, "CityControlLanding", "onDespawn", pMobile)
			end
		end
	else
		spawnNumber = readData("imperialLandingParty", mobileID)

		if (spawnNumber ~= nil) then
			local imperialLanding = self.imperialLanding
			spawnTable = imperialLanding[spawnNumber]

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
				createObserver(CREATUREDESPAWNED, "CityControlLanding", "onDespawn", pMobile)
			end
		end
	end
end