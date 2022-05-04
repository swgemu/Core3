CityControlBanners = ScreenPlay:new {
	numberOfActs = 1,

	screenplayName = "CityControlBanners",

	planets = {"corellia", "naboo", "tatooine"},

	bannerLocations = {
		--{x, z, y, cell, direction}

		corellia = {
		--Coronet
			-- Capitol Building
			{-201.33, 29.30, -4509.67, 0, 0},
			{-218.77, 29.30, -4509.60, 0, 0},
			--Starport
			{-133.916, 27.982, -4716.004, 0, -81.030},
			{-135.9, 27.982, -4729.8, 0, -81.030},
			--City Entrance
			{-164.7, 27.982, -4828.8, 0, 180},
			{-187.3, 27.982, -4828.8, 0, 180},
			--Shuttleports
			{-342.169, 28.759, -4635.953, 0, 0},
			{-38.48, 28.61, -4404.32, 0, 0},
		--Tyrena
			--Starport
			{-5031.657, 28.759, -4635.953, 0, 44.667},
			{-5047.141, 20.996, -2287.384, 0, 44.667},
			--Shuttleports
			{-5017.379, 21.614, -2380.858, 0, 4.363},
			{-5606.011, 21.635, -2803.129, 0, -89.704},
		--Kor Vella
			--City Entrance
			{-3360.386, 55.779, 2936.398, 0, -45.685},
			{-3355.916, 85.779, 2941.185, 0, -45.685},
			--Shuttleport
			{-3787.623, 86.614, 3239.500, 0, -0.596},
			--Cantina
			{-3476.185, 78.000, 3039.794, 0, -24.252},
			{-3512.640, 78.001, 3127.799, 0, -24.252},
		--Doaba Guerfel
			--Starport
			{3331.759, 307.980, 5533.433, 0, 27.536},
			{3344.699, 307.980, 5526.786, 0, 27.536},
			--Shuttleport
			{3080.039, 280.613, 4980.584, 0, -89.819},
			--Cantina
			{3244.707, 300.000, 5327.266, 0, 44.738},
			{3201.665, 299.990, 5306.973, 0, 44.827},
		},

		naboo = {
		--Theed
			--Starport
			{-4857.6, 6.4, 4179.2, 0, 40},
			{-4844.1, 6.4, 4167.7, 0, 40},
			--Shuttleports
			{-5008.926, 6.616, 4088.254, 0, 40.481},
			{-5398.103, 6.620, 4317.130, 0, -0.549},
			{-5861.508, 6.630, 4159.208, 0, -89.708},
			--Palace
			{-5517.272, 6.000, 4408.494, 0, -0.637},
			{-5474.731, 6.000, 4408.479, 0, -0.637},
			--Cantina
			{-5149.495, 5.976, 4283.133, 0, 38.227},
			{-5211.593, 6.012, 4211.072, 0, 39.212},
			-- Bridge1
			{-5233.98, 6.00, 4293.32, 0, 116},
			{-5226.88, 6.00, 4307.14, 0, 116},
			{-5279.18, 6.00, 4316.30, 0, 116},
			{-5272.13, 6.00, 4330.13, 0, 116},
			--Bridge2
			{-5278.42, 6.03, 4216.68, 0, 57.277},
			{-5270.15, 6.03, 4203.60, 0, 57.277},
			{-5313.16, 6.00, 4176.60, 0, 57.277},
			{-5321.39, 6.00, 4189.71, 0, 57.277},
		--Kaadara
			--Starport
			{5193.132, -192.000, 6679.711, 0, 0.479},
			{5193.126, -192.000, 6664.911, 0, -0.246},
			--Shuttleport
			{5136.622, -191.419, 6621.154, 0, -43.057},
			--Cantina
			{4968.349, -192.000, 6755.781, 0, -34.811},
			{5025.385, -192.000, 6679.831, 0, -34.555},
		--Keren
			--Starport
			{1444.121, 13.013, 2754.006, 0, -80.176},
			{1444.874, 13.000, 2786.762, 0, 80.334},
			--Shuttleports
			{1554.686, 25.621, 2843.536, 0, 1.042},
			{2026.436, 19.623, 2538.717, 0, 89.546},
			--Cantina
			{2114.806, 30.000, 2571.001, 0, -0.282},
			{2109.912, 30.000, 2475.628, 0, 0.400},
		},

		tatooine = {
		--Mos Eisley
			--Starport
			{3534.7, 5.000, -4796.8, 0, 89},
			{3534.966, 5.000, -4809.208, 0, 88.671},
			--Shuttleport
			{3428.934, 5.541, -4639.000, 0, 122.00},
			--City Entrances
			{3247.6, 5.0, -4948.3, 0, 40},
			{3252.9, 5.0, -4952.7, 0, 40},
			{3750.359, 4.990, -4816.347, 0, -84.641},
			{3749.354, 5.000, -4791.782, 0, -80.663},
			{3358.474, 5.000, -4996.857, 0, 38.747},
			--Cantina
			{2114.135, 30.000, 2570.943, 0, -0.619},
			{3465.033, 5.00, -4851.613, 0, -8.728},
		--Mos Espa
			--Faction Spawn Area
			{-2960.898, 5.000, 1968.413, 0, 74.044},
			{-2963.693, 5.000, 1978.555, 0, 74.044},
			{-2993.608, 5.000, 1964.793, 0, 74.044},
		--Mos Entha
			--Starport
			{1303.348, 7.000, 3146.391, 0, -37.104},
			--Shuttleports
			{1381.281, 7.575, 3472.505, 0, 0.763},
			{1716.585, 7.602, 3190.000, 0, 0.725},
			--Bank
			{1285.980, 7.640, 2954.362, 0, 44.918},
		},
	},
}

registerScreenPlay("CityControlBanners", false)

function CityControlBanners:spawnGcwControlBanners(zoneName)
	for i = 1, #self.planets, 1 do
		local planetName = self.planets[i]

		if (isZoneEnabled(planetName) and planetName == zoneName) then
			local location = self.bannerLocations[planetName]

			for j = 1, #location, 1 do
				self:manageSceneObjects(location, j, planetName)
			end
		end
	end
end

function CityControlBanners:manageSceneObjects(location, num, planetName)
	if num <= 0 or num > #location then
		return
	end

	local despawnID = readData(planetName .. ":control:banner:" .. num)
	local despawnBannerObject = getSceneObject(despawnID)

	if (despawnBannerObject ~= nil) then
		SceneObject(despawnBannerObject):destroyObjectFromWorld()
		deleteData(planetName .. ":control:banner" .. num)
	end

	local controllingFaction = getControllingFaction(planetName)
	local sceneObjectTable = location[num]
	local pSceneObject = nil
	local objectTemplate = ""

	if controllingFaction == FACTIONREBEL then
		objectTemplate = "object/tangible/gcw/flip_banner_onpole_rebel.iff"
	else
		objectTemplate = "object/tangible/gcw/flip_banner_onpole_imperial.iff"
	end

	pSceneObject = spawnSceneObject(planetName, objectTemplate, sceneObjectTable[1], sceneObjectTable[2], sceneObjectTable[3], sceneObjectTable[4], math.rad(sceneObjectTable[5]))

	if pSceneObject ~= nil then
		local pSceneObjectID = SceneObject(pSceneObject):getObjectID()
		writeData(planetName .. ":control:banner:" .. num, pSceneObjectID)
	end
end
