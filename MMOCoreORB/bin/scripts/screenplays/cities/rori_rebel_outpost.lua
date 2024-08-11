RoriRebelOutpostScreenPlay = CityScreenPlay:new {
	numberOfActs = 1,

	screenplayName = "RoriRebelOutpostScreenPlay",

	planet = "rori",

	stationaryCommoners = {"commoner", "commoner_fat", "commoner_naboo", "commoner_old"},
	stationaryNpcs = {"agriculturalist", "artisan", "bodyguard", "bothan_diplomat", "bounty_hunter", "businessman", "commoner_technician", "contractor", "entertainer", "explorer", "farmer", "farmer_rancher", "fringer",
				"gambler", "info_broker", "medic", "mercenary", "miner", "naboo_nomad", "noble", "official", "patron_ishitib", "pilot", "rancher", "scientist", "slicer", "traveller"},

	--{respawn, x, z, y, direction, cell, mood}
	stationaryMobiles = {
		{1, 3702.3, 96, -6439.5, 330, 0, "bored"},
		{1, 3645.7, 96, -6439, 80, 0, "happy"},
		{1, 3640.8, 96, -6439.1, 71, 0, "npc_sitting_chair"},
		{1, 3702.6, 96, -6434.3, 94, 0, "npc_use_terminal_high"},
	},

	mobiles = {
		--buildings interior
		{"entertainer", 360, 10, 0, 3.6, 270, 4505634, "happy"},
		{"commoner", 360, 3.7, 0.6, 0.7, 90, 4505634, "npc_sitting_chair"},
		{"patron", 360, 6.1, 0.6, 0.7, 270, 4505634, "npc_sitting_chair"},
		{"patron", 360, 1.8, 0.6, 1.8, 69, 4505634, "npc_standing_drinking"},
		{"vordin_sildor", 60, 4.2, 0.1, 0.8, 196, 4505667, "npc_sitting_chair"},

		--Guard Tower with rifle trainer
		{"rebel_specforce_pathfinder", 360, 3651, 103, -6485, 90, 0, ""},
		{"specforce_wilderness_operative", 360, 3651, 103, -6489, 90, 0, ""},
		{"specforce_lieutenant", 360, 3645, 103, -6494, 180, 0, ""},
		{"rebel_specforce_urban_guerrilla", 360, -2.0, 2, 3.5, 90, 4505604, ""},

		--Guard Tower with carbine trainer
		{"specforce_wilderness_operative", 360, 3635, 103, -6439, 91, 0, ""},
		{"rebel_specforce_pathfinder", 360, 3632, 103, -6432, 0, 0, ""},
		{"specforce_wilderness_operative", 360, -2.5, 2.0, 3.7, 70, 4505993, ""},

		--Guard Tower with marksman trainer
		{"specforce_wilderness_operative", 360, 3680, 103, -6491, 170, 0, ""},
		{"rebel_specforce_pathfinder", 360, 3677, 103, -6481, 180, 0, ""},
		{"specforce_wilderness_operative", 360, 3685, 103, -6485, 50, 0, ""},

		-- Tavern
		{"rebel_medic", 360, -8.5, 0.6, -7.3, 47, 4505636, ""},
		{"specforce_marine", 360, 2.2, 0.6, -2.2, 243, 4505636, ""},
		{"specforce_marine", 360, 2.1, 0.6, -6.5, 280, 4505636, ""},
		{"rebel_high_general", 360, 7.8, 0.6, -4.4, 270, 4505637, ""},
		{"ufwol", 360, -8.4, 0.6, 3.5, 88, 4505635, ""},

		--Left Storage Shed with quest givers
		{"specforce_marine", 360, 0, 0.1, -6.0, 0, 4505666, ""},

		--Right Storage Shed (Cloner, ""},
		{"rebel_medic", 360, 5.3, 0.1, 0.9, -85, 4505609, ""},
		{"rebel_colonel", 360, 0.1, 0.1, -1.5, -5, 4505608, ""},

		--misc
		{"rebel_recruiter", 0, 3683, 96, -6460, -101, 0, ""},

		--trainer
		{"trainer_architect", 60, 3677, 96, -6418, 90, 0, ""},
		{"trainer_armorsmith", 60, 3676, 96, -6432, 90, 0, ""},
		{"trainer_carbine", 60, 3627, 104, -6433, 90, 0, ""},
		{"trainer_chef", 60, 3681, 96, -6426, 180, 0, ""},
		{"trainer_commando", 60, -1.6, 0.7, 2.7, 180, 4505792, ""},
		{"trainer_marksman", 60, 3684.5, 104, -6488.5, 260, 0, ""},
		{"trainer_rifleman", 60, 3649, 104, -6491.5, 315, 0, ""},
		{"trainer_weaponsmith", 60, 3681, 96, -6420, 0, 0, ""},

		--Outside
		{"rebel_army_captain", 360, 3644, 96, -6404, 133, 0, ""},
		{"rebel_colonel", 360, 3662, 96, -6402, 162, 0, ""},
		{"rebel_surface_marshall", 360, 3660, 96, -6443, 342, 0, ""},
		{"rebel_commando", 360, 3703, 96, -6404, 265, 0, ""},
		{"rebel_commando", 360, 3703, 96, -6431, 270, 0, ""},
		{"rebel_colonel", 360, 3694, 96, -6441, 0, 0, ""},
		{"rebel_specforce_captain", 360, 3679, 96, -6446, 210, 0, ""},
		{"rebel_colonel", 360, 3658, 96, -6443, 90, 0, ""},
		{"rebel_specforce_urban_guerrilla", 360, 3670, 96, -6443, 270, 0, ""},
		{"rebel_colonel", 360, 3641, 96, -6432, 90, 0, ""},
		{"specforce_major", 360, 3671, 96, -6480, 270, 0, ""},
		{"rebel_specforce_sergeant", 360, 3657, 96, -6483, 140, 0, ""},
		{"specforce_wilderness_operative", 360, 3642, 96, -6477, 110, 0, ""},
		{"rebel_specforce_urban_guerrilla", 360, 3656, 96, -6463, 80, 0, ""},
		{"specforce_marine", 360, 3684, 96, -6458, 280, 0, ""}
	}
}

registerScreenPlay("RoriRebelOutpostScreenPlay", true)

function RoriRebelOutpostScreenPlay:start()
	if (isZoneEnabled(self.planet)) then
		self:spawnMobiles()
		self:spawnStationaryMobiles()
	end
end

function RoriRebelOutpostScreenPlay:spawnMobiles()
	local mobiles = self.mobiles

	for i = 1, #mobiles, 1 do
		local mob = mobiles[i]

		-- {template, respawn, x, z, y, direction, cell, mood}
		local pMobile = spawnMobile(self.planet, mob[1], mob[2], mob[3], mob[4], mob[5], mob[6], mob[7])

		if (pMobile ~= nil) then
			if mob[8] ~= "" then
				CreatureObject(pMobile):setMoodString(mob[8])
			end

			AiAgent(pMobile):addObjectFlag(AI_STATIC)

			if CreatureObject(pMobile):getPvpStatusBitmask() == 0 then
				CreatureObject(pMobile):clearOptionBit(AIENABLED)
			end
		end
	end

	--Patrols outside the walls
	spawnMobile(self.planet, "rebel_army_captain", 360, getRandomNumber(16) + 3618.3, 96.1, getRandomNumber(24) + -6469.6, getRandomNumber(360), 0)
	spawnMobile(self.planet, "rebel_trooper", 360, getRandomNumber(16) + 3618.3, 96.1, getRandomNumber(24) + -6469.6, getRandomNumber(360), 0)
	spawnMobile(self.planet, "rebel_medic", 360, getRandomNumber(16) + 3618.3, 96.1, getRandomNumber(24) + -6469.6, getRandomNumber(360), 0)
	spawnMobile(self.planet, "rebel_trooper", 360, getRandomNumber(16) + 3618.3, 96.1, getRandomNumber(24) + -6469.6, getRandomNumber(360), 0)
	spawnMobile(self.planet, "rebel_trooper", 360, getRandomNumber(16) + 3618.3, 96.1, getRandomNumber(24) + -6469.6, getRandomNumber(360), 0)
	spawnMobile(self.planet, "rebel_first_lieutenant", 360, getRandomNumber(16) + 3618.3, 96.1, getRandomNumber(24) + -6469.6, getRandomNumber(360), 0)

	spawnMobile(self.planet, "rebel_army_captain", 360, getRandomNumber(16) + 3708.4, 96.1, getRandomNumber(24) + -6429.6, getRandomNumber(360), 0)
	spawnMobile(self.planet, "rebel_trooper", 360, getRandomNumber(16) + 3708.4, 96.1, getRandomNumber(24) + -6429.6, getRandomNumber(360), 0)
	spawnMobile(self.planet, "rebel_trooper", 360, getRandomNumber(16) + 3708.4, 96.1, getRandomNumber(24) + -6429.6, getRandomNumber(360), 0)
	spawnMobile(self.planet, "rebel_trooper", 360, getRandomNumber(16) + 3708.4, 96.1, getRandomNumber(24) + -6429.6, getRandomNumber(360), 0)
	spawnMobile(self.planet, "rebel_trooper", 360, getRandomNumber(16) + 3708.4, 96.1, getRandomNumber(24) + -6429.6, getRandomNumber(360), 0)
	spawnMobile(self.planet, "rebel_trooper", 360, getRandomNumber(16) + 3708.4, 96.1, getRandomNumber(24) + -6429.6, getRandomNumber(360), 0)
	spawnMobile(self.planet, "specforce_wilderness_operative", 360, 3696.0, 85.0, -6566.6, -110, 0)
	spawnMobile(self.planet, "specforce_wilderness_operative", 360, 3685.3, 86.8, -6573.1, 10, 0)
	spawnMobile(self.planet, "specforce_wilderness_operative", 360, 3664.1, 86.4, -6574.7, 160, 0)
	spawnMobile(self.planet, "specforce_wilderness_operative", 360, 3629.9, 83.8, -6570.1, -90, 0)
	spawnMobile(self.planet, "specforce_marine", 360, 3654.9, 96.0, -6499.0, 180, 0)
	spawnMobile(self.planet, "specforce_marine", 360, 3674.4, 96.0, -6499.0, 180, 0)
end
