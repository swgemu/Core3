BattlefieldSpawner = ScreenPlay:new {
	numberOfActs = 1,

	screenplayName = "BattlefieldSpawner",

	planets = {"corellia", "naboo", "tatooine", "dathomir", "yavin4", "talus", "rori", "endor"},

	noBuildRadius = 768,

	battlefields = {
		--{objecTemplate, x, z, y, size}

		--Templates:
		--object/battlefield_marker/battlefield_marker_128m.iff
		--object/battlefield_marker/battlefield_marker_192m.iff
		--object/battlefield_marker/battlefield_marker_256m.iff
		--object/battlefield_marker/battlefield_marker_384m.iff
		--object/battlefield_marker/battlefield_marker_512mm.iff

		corellia = {
			{"object/battlefield_marker/battlefield_marker_128m.iff", 3784, 380, -4048, 128},
			{"object/battlefield_marker/battlefield_marker_128m.iff", -1856, 7, -1232, 128},
			{"object/battlefield_marker/battlefield_marker_128m.iff", 246, 50, 4552, 128},
			{"object/battlefield_marker/battlefield_marker_128m.iff", -3570, 30, -2615, 128},
		},

		naboo = {
			{"object/battlefield_marker/battlefield_marker_128m.iff", -5032, -207, 6632, 128},
			{"object/battlefield_marker/battlefield_marker_128m.iff", -4168, 45, -589, 128},
			{"object/battlefield_marker/battlefield_marker_256m.iff", -3776, 10, -5344, 256},
		},

		tatooine = {
			{"object/battlefield_marker/battlefield_marker_256m.iff", 4949, 34, 4643, 256},
			{"object/battlefield_marker/battlefield_marker_128m.iff", 2396, 0, 4238, 128},
			{"object/battlefield_marker/battlefield_marker_128m.iff", -1873, 20, -585, 128},
			{"object/battlefield_marker/battlefield_marker_128m.iff", -2739, 34, -1560, 128},
		},

		dathomir = {
			{"object/battlefield_marker/battlefield_marker_128m.iff", 4245, 79, -3725, 128},
		},

		yavin4 = {
			{"object/battlefield_marker/battlefield_marker_256m.iff", -4230, 103, 3755, 256},
			{"object/battlefield_marker/battlefield_marker_256m.iff", 3791, 868, -2416, 256},
		},

		talus = {
			{"object/battlefield_marker/battlefield_marker_128m.iff", -491, 0, 4578, 128},
			{"object/battlefield_marker/battlefield_marker_128m.iff", -5331, 43, 2799, 128},
			{"object/battlefield_marker/battlefield_marker_256m.iff", -3342, 26, -3141, 256},
		},

		rori = {
			{"object/battlefield_marker/battlefield_marker_256m.iff", -2306, 79, 6467, 256},
			{"object/battlefield_marker/battlefield_marker_128m.iff", 2955, 108, -1249, 128},
			{"object/battlefield_marker/battlefield_marker_128m.iff", -3424, 100, -6129, 128},
		},

		endor = {
			{"object/battlefield_marker/battlefield_marker_128m.iff", -3677, 17, -4393, 128},
		},

	},
}

registerScreenPlay("BattlefieldSpawner", true)

function BattlefieldSpawner:start()
	for i = 1, #self.planets, 1 do
		local planetName = self.planets[i]

		if (isZoneEnabled(planetName)) then
			local location = self.battlefields[planetName]

			for j = 1, #location, 1 do
				self:spawnBattlefield(location, j, planetName)
				self:spawnActiveArea(location, j, planetName)
			end
		end
	end
end

function BattlefieldSpawner:spawnBattlefield(location, num, planetName)
	if num <= 0 or num > #location then
		return
	end

	local sceneObjectTable = location[num]

	pObj = spawnSceneObject(planetName, sceneObjectTable[1], sceneObjectTable[2], sceneObjectTable[3], sceneObjectTable[4], 0, math.rad(0))

	if (pObj ~= nil) then
		SceneObject(pObj):setRadius(sceneObjectTable[5])
	end
end

function BattlefieldSpawner:spawnActiveArea(location, num, planetName)
	if num <= 0 or num > #location then
		return
	end

	local sceneObjectTable = location[num]

	local pActiveArea = spawnActiveArea(planetName, "object/active_area.iff", sceneObjectTable[2], sceneObjectTable[3], sceneObjectTable[4], self.noBuildRadius, 0)

	if (pActiveArea ~= nil) then
		ActiveArea(pActiveArea):setNoBuildArea(true)
		ActiveArea(pActiveArea):setNoSpawnArea(true)
	end
end
