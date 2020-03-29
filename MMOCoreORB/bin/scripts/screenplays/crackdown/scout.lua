CrackdownScout = ScreenPlay:new {
	scoutPlanets = { "corellia", "naboo", "tatooine" },
	totalActiveAreas = 8,
	minDistanceBetweenAreas = 200,

	debugNotify = true -- Send system message when successfully triggered (for debugging)
}

registerScreenPlay("CrackdownScout", true)

function CrackdownScout:start()
	for i = 1, #self.scoutPlanets, 1 do
		local planetName = self.scoutPlanets[i]

		if (isZoneEnabled(planetName)) then
			for i = 1, self.totalActiveAreas, 1 do

			end
		end
	end
end

function CrackdownScout:createScoutLocation(planet, areaNumber)
	local scoutLoc = nil
	local attempts = 0

	while scoutLoc == nil and attempts < 10 do
		scoutLoc = self:findValidScoutLocation(planet)
	end

	if (scoutLoc == nil) then
		printLuaError("Error finding a valid scout location in CrackdownScout:createScoutLocation on planet " .. planet)
		return
	end

	local pTheater = spawnSceneObject(planet, "object/static/structure/nobuild/nobuild_32.iff", campLoc[2], campLoc[3], campLoc[4], 0, 0)

	if (pTheater == nil) then
		printLuaError("Error creating theater in FsCounterStrike:spawnCamps().")
		return
	end
end

function CrackdownScout:findValidScoutLocation(planet)
	local found = false
	local attempts = 0

	while found == false and attempts < 50 do
		local randX = -7000 + getRandomNumber(14000)
		local randY = -7000 + getRandomNumber(14000)

		local pCityRegion = getCityRegionAt(planet, randX, randY)

		if (pCityRegion == nil) then

		end
	end

	return nil
end
