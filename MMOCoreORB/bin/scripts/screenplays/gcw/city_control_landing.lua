CityControlLanding = ScreenPlay:new {
	numberOfActs = 1,

	screenplayName = "CityControlLanding",

	locations = { {"coronet", "corellia"}, {"theed", "naboo"}, {"bestine", "tatooine"}, {"anchorhead", "tatooine"}},

	coronet = {-151, 28, -4716, 179},
	theed = {-4897, 6, 4124, 174},
	bestine = {-1281, 12, -3592, 174},
	anchorhead = {111, 52, -5348, 171},

	rebelLanding = {"object/creature/npc/theme_park/player_shuttle.iff", "luke_skywalker", "rebel_corporal"},
	imperialLanding = {"object/creature/npc/theme_park/lambda_shuttle.iff", "darth_vader", "elite_novatrooper"},

	testing = true,
}

registerScreenPlay("CityControlLanding", true)

function CityControlLanding:start()
	self:chanceToSpawn()
end

function CityControlLanding:chanceToSpawn()
	local chance = getRandomNumber(4)

	if (testing) then
		chance = 1
	end

	if (chance <= 5) then
		printf("  Chance to spawn <= to 5   ")
		createEvent(30000, "CityControlLanding", "spawnCityLanding", "", "")
	else
		printf("    chance to spawn 6hr timer   ")
		createEvent(21600 * 1000, "CityControlLandingScreenplay", "chanceToSpawn", "", "")

	end
end

function CityControlLanding:spawnCityLanding()

	printf("    spawn city landing called  ")
	local totalLocations = #self.locations
	local determineCity = getRandomNumber(totalLocations)
	local chosenCityPlanet = self.locations[determineCity]
	local city = chosenCityPlanet[1]
	--local city = "coronet"
	local planet = chosenCityPlanet[2]
	--local planet = "corellia"

	if (not isZoneEnabled(planet)) then
		createEvent(60000, "CityControlLanding", "spawnCityLanding", "", "")
	end

	printf ("    location 1   passed      ")
	local controllingFaction = getControllingFaction(planet)
	local rebelLanding = self.rebelLanding
	local imperialLanding = self.imperialLanding

	printf ("     location 2 passed     ")

	if (city ~= "bestine") and (controllingFaction == FACTIONREBEL or city == "anchorhead") then
		--(planet, template,  x, z, y, cell, direction)
		local pShuttle = spawnSceneObject(planet, rebelLanding[1], city[1], city[2], city[3], 0, city[4])
		printf("spawn Rebel shuttle")

		if (pShuttle ~= nil) then
			CreatureObject(pShuttle):setPosture(UPRIGHT)
			CreatureObject(pShuttle):setCustomObjectName("Transport Shuttle")

			local pOid = SceneObject(pShuttle):getObjectID()

			printf("      pShuttle is not null    ")

			writeData(pOid .. ":rebelControlLanding", determineCIty)
			createEvent(23000, "CityControlLanding", "spawnRebelLandingParty", pShuttle, "")
		end
	else
		--(planet, template,  x, z, y, cell, direction)
		local pShuttle = spawnSceneObject(planet, imperialLanding[1], city[1], city[2], city[3], 0, city[4])
		printf("spawned imperial lambda")

		if (pShuttle ~= nil) then
			CreatureObject(pShuttle):setPosture(PRONE)
			CreatureObject(pShuttle):setCustomObjectName("Lambda Shuttle")

			local pOid = SceneObject(pShuttle):getObjectID()

			printf("      pShuttle is not null    ")

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

	local pShuttleID = SceneObject(pShuttle):getObjectiID()
	local determinedCity = readData(pShuttleID .. : "rebelLandingParty")
	local spawnCityPlanet = self.locations[determinedCity]
	local city = spawnCityPlanet[1]
	local planet = spawnCityPlanet[2]
	local totalSpawns = #self.rebelLanding - 1
	local template = self.rebelLanding

	for i = 2, totalSpawns, 1 do
		local xOffset = -3 + getRandomNumber(0, 6)
		local yOffset = -3 + getRandomNumber(0, 6)
		spawnMobile(planet, template[i], 0, city[1] + xOffset, city[2], city[3] + yOffset, city[4], 0)
	end
end

function CityControlLanding:spawnImperialLandingParty(spawnPlanet)
	local pShuttle = shuttle

	if (pShuttle == nil) then
		createEvent(60000, "CityControlLanding", "spawnCityLanding", "", "") --call cleanup?
	end

	local pShuttleID = SceneObject(pShuttle):getObjectiID()
	local determinedCity = readData(pShuttleID .. : "imperialLandingParty")
	local spawnCityPlanet = self.locations[determinedCity]
	local city = spawnCityPlanet[1]
	local planet = spawnCityPlanet[2]
	local totalSpawns = #self.imperialLanding - 1
	local template = self.imperialLanding

	for i = 2, totalSpawns, 1 do
		local xOffset = -3 + getRandomNumber(0, 6)
		local yOffset = -3 + getRandomNumber(0, 6)
		spawnMobile(planet, template[i], 0, city[1] + xOffset, city[2], city[3] + yOffset, city[4], 0)
	end

end

