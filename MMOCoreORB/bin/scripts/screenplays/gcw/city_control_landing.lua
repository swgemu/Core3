CityControlLanding = ScreenPlay:new {
	numberOfActs = 1,

	screenplayName = "CityControlLanding",

	locations = { {"coronet", "corellia"}, {"theed", "naboo"}, {"bestine", "tatooine"}, {"anchorhead", "tatooine"}},

	coordinates = {
		{-148, 28, -4715, 179}, --Coronet
		{-4897, 6, 4124, 174}, --Theed
		{-1282, 12, -3589, -94}, --Bestine
		{111, 52, -5348, 171}, --Anchorhead
	},

	rebelLanding = {"object/creature/npc/theme_park/player_shuttle.iff", "lukeLeia", "rebel_corporal", "rebel_commando"},
	imperialLanding = {"object/creature/npc/theme_park/lambda_shuttle.iff", "darth_vader", "elite_novatrooper_commander", "elite_novatrooper", "elite_novatrooper", "elite_novatrooper", "elite_novatrooper", "elite_novatrooper", "elite_novatrooper"},

}

registerScreenPlay("CityControlLanding", true)

function CityControlLanding:start()
	self:chanceToSpawn()
end

function CityControlLanding:chanceToSpawn()
	local chance = getRandomNumber(4)

	if (chance <= 5) then
		createEvent(30000, "CityControlLanding", "spawnCityLanding", "", "")
	else
		createEvent(21600 * 1000, "CityControlLandingScreenplay", "chanceToSpawn", "", "")

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

	local controllingFaction = getControllingFaction(planet)
	local rebelLanding = self.rebelLanding
	local imperialLanding = self.imperialLanding

	if (city ~= "bestine") and (controllingFaction == FACTIONREBEL or city == "anchorhead") then
		--(planet, template,  x, z, y, cell, direction)
		local pShuttle = spawnSceneObject(planet, rebelLanding[1], cityCoords[1], cityCoords[2], cityCoords[3], 0, cityCoords[4])
		printf("  spawned Rebel shuttle  ")

		if (pShuttle ~= nil) then
			CreatureObject(pShuttle):setPosture(UPRIGHT)
			CreatureObject(pShuttle):setCustomObjectName("Transport Shuttle")

			local pOid = SceneObject(pShuttle):getObjectID()

			printf("      pShuttle is not null    ")
			printf(" determineCity ==   ")
			printf(determineCity)

			writeData(pOid .. ":rebelTransport", determineCity)
			createEvent(23000, "CityControlLanding", "spawnRebelLandingParty", pShuttle, "")
		end
	else
		--(planet, template,  x, z, y, cell, direction)
		local pShuttle = spawnSceneObject(planet, imperialLanding[1], cityCoords[1], cityCoords[2], cityCoords[3], 0, cityCoords[4])
		printf("spawned imperial lambda")

		if (pShuttle ~= nil) then
			CreatureObject(pShuttle):setPosture(PRONE)
			CreatureObject(pShuttle):setCustomObjectName("Lambda Shuttle")

			local pOid = SceneObject(pShuttle):getObjectID()

			printf("      pShuttle is not null    ")
			printf(" determineCity ==   ")
			printf(determineCity)

			writeData(pOid .. ":imperialLambda", determineCity)
			createEvent(18000, "CityControlLanding", "spawnImperialLandingParty", pShuttle, "")
		end
	end
end

function CityControlLanding:spawnRebelLandingParty(shuttle)
	local pShuttle = shuttle

	if (pShuttle == nil) then
		createEvent(60000, "CityControlLanding", "spawnCityLanding", "", "") --call cleanup?
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
		--local x = -3 + getRandomNumber(0, 6) --TO DO: calculate ship offset
		--local yOffset = -3 + getRandomNumber(0, 6)

		if (template[i] == "lukeLeia") then
			local chosenTemplate = ""
			local tempRoll = getRandomNumber(2)

			if (tempRoll == 2) then
				chosenTemplate = "luke_skywalker"
			else
				chosenTemplate = "leia_organa"
			end

			--template, level, x, z, y, direction, cell, mood},
			local pMobile = spawnMobile(planet, chosenTemplate, 0, xLoc + 10, cityCoords[2], yLoc + 10, cityCoords[4], 0, "")

			if (pMobile ~= nil) then
				AiAgent(pMobile):setAiTemplate("")
			end
		else
			--template, level, x, z, y, direction, cell, mood},
			local pMobile = spawnMobile(planet, template[i], 0, xLoc, cityCoords[2], yLoc, cityCoords[4], 0, "")

			if (pMobile ~= nil) then
				AiAgent(pMobile):setAiTemplate("")
			end
		end
	end
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
		--local x = -3 + getRandomNumber(0, 6)
		--local yOffset = -3 + getRandomNumber(0, 6)

		if (template == "darth_vader") then
			--template, level, x, z, y, direction, cell, mood},
			local pMobile = spawnMobile(planet, template[i], 0, xLoc + 10, cityCoords[2], yLoc + 10, cityCoords[4], 0, "")

			if (pMobile ~= nil) then
				AiAgent(pMobile):setAiTemplate("")
			end
		else
			--template, level, x, z, y, direction, cell, mood},
			local pMobile = spawnMobile(planet, template[i], 0, xLoc, cityCoords[2], yLoc, cityCoords[4], 0, "")

			if (pMobile ~= nil) then
				AiAgent(pMobile):setAiTemplate("")
			end
		end
	end
end

