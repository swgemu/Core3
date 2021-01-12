CityControlLanding = ScreenPlay:new {
	numberOfActs = 1,

	screenplayName = "CityControlLanding",

	locations = { {"coronet", "corellia"}, {"theed", "naboo"}, {"bestine", "tatooine"}, {"anchorhead", "tatooine"}},

	coronet = {-151, 28, -4716, 179},

	theed = {0, 0, 0, 0},

	bestine = {0, 0, 0, 0},

	anchorhead = {0, 0, 0, 0},

	rebelLanding = {"object/creature/npc/theme_park/player_shuttle.iff", "luke_skywalker", "rebel_corporal"},

	imperialLanding = {"object/creature/npc/theme_park/player_shuttle.iff", "darth_vader", "elite_novatrooper"},

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
	--local city = chosenCityPlanet[1]
	local city = "coronet"
	--local planet = chosenCityPlanet[2]
	local planet = "corellia"

	if (not isZoneEnabled(planet)) then
		createEvent(10000, "CityControlLanding", "spawnCityLanding", "", "")
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
			local pOid = SceneObject(pShuttle):getObjectID()

			CreatureObject(pShuttle):setCustomObjectName("Transport Shuttle")
			CreatureObject(pShuttle):setPosture(PRONE)
			writeData(city .. ":rebelShuttle", pOid)
			createEvent(23000, "CityControlLanding", "spawnRebelLandingParty", "planet", "")
		end
	else
		--(planet, template,  x, z, y, cell, direction)
		--local pShuttle = spawnSceneObject(planet, imperialLanding[1], city[1], city[2], city[3], 0, city[4])
		local pShuttle = spawnSceneObject("corellia", "object/creature/npc/theme_park/player_shuttle.iff", -151, 28, -4716, 0, 179)

		printf("spawned imperial lambda")

		if (pShuttle ~= nil) then
			CreatureObject(pShuttle):setPosture(PRONE)

			local pOid = SceneObject(pShuttle):getObjectID()

			printf("      pShuttle is not null    ")

			CreatureObject(pShuttle):setCustomObjectName("Lambda Shuttle")

			writeData(city .. ":imperialLambda", pOid)
			--CreateEvent(18000, "CityControlLanding", "spawnImperialLandingParty", "planet", "")
		end
	end
end

function CityControlLanding:spawnRebelLandingParty(planet)


end

function CityControlLanding:callLambdaShuttle(planet)

end

