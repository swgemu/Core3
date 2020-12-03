BattlefieldSpawner = ScreenPlay:new {
	numberOfActs = 1,

	screenplayName = "BattlefieldSpawner",

	planets = {"corellia", "naboo", "tatooine", "dathomir", "yavin4", "talus", "rori", "endor"},

	battlefields = {
		--{objecTemplate, x, z, y, 0, 0}

		--Templates:
		--object/battlefield_marker/battlefield_marker_128m.iff
		--object/battlefield_marker/battlefield_marker_192m.iff
		--object/battlefield_marker/battlefield_marker_256m.iff
		--object/battlefield_marker/battlefield_marker_384m.iff
		--object/battlefield_marker/battlefield_marker_512mm.iff

		corellia = {
			{"object/battlefield_marker/battlefield_marker_128m.iff", 3784, 380, -4048},
			{"object/battlefield_marker/battlefield_marker_128m.iff", -1856, 7, -1232},
			{"object/battlefield_marker/battlefield_marker_128m.iff", 246, 50, 4552},
			{"object/battlefield_marker/battlefield_marker_128m.iff", -3570, 30, -2615},
		},

		naboo = {
			{"object/battlefield_marker/battlefield_marker_128m.iff", -5032, -207, 6632},
			{"object/battlefield_marker/battlefield_marker_128m.iff", -4168, 45, -589},
			{"object/battlefield_marker/battlefield_marker_256m.iff", -3776, 10, -5344},
		},

		tatooine = {
			{"object/battlefield_marker/battlefield_marker_256m.iff", 4949, 34, 4643},
			{"object/battlefield_marker/battlefield_marker_128m.iff", 2396, 0, 4238},
			{"object/battlefield_marker/battlefield_marker_128m.iff", -1873, 20, -585},
			{"object/battlefield_marker/battlefield_marker_128m.iff", -2739, 34, -1560},
		},

		dathomir = {
			{"object/battlefield_marker/battlefield_marker_128m.iff", 4245, 79, -3725},
		},

		yavin4 = {
			{"object/battlefield_marker/battlefield_marker_256m.iff", -4230, 103, 3755},
			{"object/battlefield_marker/battlefield_marker_256m.iff", 3791, 868, -2416},
		},

		talus = {
			{"object/battlefield_marker/battlefield_marker_128m.iff", -491, 0, 4578},
			{"object/battlefield_marker/battlefield_marker_128m.iff", -5331, 43, 2799},
			{"object/battlefield_marker/battlefield_marker_256m.iff", -3342, 26, -3141},
		},

		rori = {
			{"object/battlefield_marker/battlefield_marker_256m.iff", -2306, 79, 6467},
			{"object/battlefield_marker/battlefield_marker_128m.iff", 2955, 108, -1249},
			{"object/battlefield_marker/battlefield_marker_128m.iff", -3424, 100, -6129},
		},

		endor = {
			{"object/battlefield_marker/battlefield_marker_128m.iff", -3677, 17, -4393},
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
				self:spawnBattlefields(location, j, planetName)
			end
		end
	end
end

function BattlefieldSpawner:spawnBattlefields(location, num, planetName)
	if num <= 0 or num > #location then
		return
	end

	local sceneObjectTable = location[num]
	local pSceneObject = nil

	pSceneObject = spawnSceneObject(planetName, sceneObjectTable[1], sceneObjectTable[2], sceneObjectTable[3], sceneObjectTable[4], 0, math.rad(0))

end
