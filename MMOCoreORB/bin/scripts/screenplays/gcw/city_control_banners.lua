CityControlBanners = ScreenPlay:new {
	numberOfActs = 1,

	screenplayName = "CityControlBanners",

	planets = {"corellia", "naboo", "tatooine"},
	
	bannerLocations = {
		--{x, z, y, cell, direction}
		
		corellia = {
		--Coronet
		--Starport
			{-133.916, 27.982, -4716.004, 0, math.rad(-81.030)},
			{-135.9, 27.982, -4729.8, 0, math.rad(-81.030)},
			--City Entrance
			{-164.7, 27.982, -4828.8, 0, math.rad(180)},
			{-187.3, 27.982, -4828.8, 0, math.rad(180)},
		},
		
		naboo = {
		--Theed
			--Starport
			{-4857.6, 6.4, 4179.2, 0, math.rad(40)},
			{-4844.1, 6.4, 4167.7, 0, math.rad(40)},

		--Keren
		},
		
		tatooine = {
		--mos_eisley
			--Starport
			{3534.7, 5.0, -4796.8, 0, math.rad(89)},
			{3534.4, 5.0, -4808.5, 0, math.rad(89)},
			--City Entrances
			{3247.6, 5.0, -4948.3, 0, math.rad(40)},
			{3252.9, 5.0, -4952.7, 0, math.rad(40)},

		--mos_espa
		},
	},
}

registerScreenPlay("CityControlBanners", false)

function CityControlBanners:spawnGcwControlBanners(zoneName)
	for i = 1, #self.planets, 1 do
		local planetName = self.planets[i]
		
		if (isZoneEnabled(planetName) and planetName == zoneName) then
			local location = self.bannerLocations[planetName]
			local controllingFaction = getControllingFaction(planetName)

			if controllingFaction == FACTIONNEUTRAL then
				controllingFaction = FACTIONIMPERIAL
			end
			
			for j = 1, #location, 1 do
				self:spawnSceneObjects(j, controllingFaction, planetName)
			end
		end
	end
end

function CityControlBanners:spawnSceneObjects(num, controllingFaction, planetName)
	local bannerTable = self.bannerLocations[planetName]
	
	if num <= 0 or num > #bannerTable then
		return
	end
	
	local sceneObjectTable = bannerTable[num]
	local pSceneObject = nil
	local objectTemplate = ""
	
	if controllingFaction == FACTIONIMPERIAL then
		objectTemplate = "object/tangible/gcw/flip_banner_onpole_imperial.iff"
	elseif controllingFaction == FACTIONREBEL then
 		objectTemplate = "object/tangible/gcw/flip_banner_onpole_rebel.iff"
 	end
 	
 	pSceneObject = spawnSceneObject(planetName, objectTemplate, sceneObjectTable[1], sceneObjectTable[2], sceneObjectTable[3], sceneObjectTable[4], sceneObjectTable[5])

	if pSceneObject ~= nil then
		local pSceneObjectID = SceneObject(pSceneObject):getObjectID()
		writeData(pSceneObjectID, num)
		createEvent(3600000, "CityControlBanners", "despawnSceneObjects", pSceneObject, "")
	end
end

function CityControlBanners:despawnSceneObjects(pSceneObject)
	local oldSceneObjectID = SceneObject(pSceneObject):getObjectID()
	local oldScnOData = readData(oldSceneObjectID)
	
	SceneObject(pSceneObject):destroyObjectFromWorld()
	deleteData(oldSceneObjectID)
end

