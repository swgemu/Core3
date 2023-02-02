KraytGraveyardSpawner = InterestAreaSpawner:new {
	screenplayName = "KraytGraveyardSpawner",
	debug = true,
	planet = "tatooine",

	maxSpawns = 2,
	delayChance = 5, -- % chance for spawner to go on delay out of 100
	--delayTimer = 600, -- time in seconds the spawner will not delayed
	delayTimer = 30,
	--respawnTimer = 1800,
	respawnTimer = 10,

	-- {x, z, y, direction}
	spawnerLocations = {
		{7432.9, 6.4, 4561.5, -116},
		{7428, 5.7, 4528.9, 0},
	},

	spawns = {
		{"krayt_dragon_grand", 1, 1800},
		{"krayt_dragon_ancient", 1, 3600},
	},
}

registerScreenPlay("KraytGraveyardSpawner", false)

function KraytGraveyardSpawner:start()
	if (not isZoneEnabled(self.planet)) then
		return
	end

	print(self.screenplayName .. " called start() ")

	self:createSpawners()
	self:populateSpawners()
end