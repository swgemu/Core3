RoriRebelOutpostScreenPlay = ScreenPlay:new {
	numberOfActs = 1,

	screenplayName = "RoriRebelOutpostScreenPlay"
}

registerScreenPlay("RoriRebelOutpostScreenPlay", true)

function RoriRebelOutpostScreenPlay:start()
	if (isZoneEnabled("rori")) then
		self:spawnMobiles()
	end
end

function RoriRebelOutpostScreenPlay:spawnMobiles()
	--mobs

		--Patrols outside the walls
	spawnMobile("rori", "rebel_army_captain", 360, getRandomNumber(16) + 3618.3, 96.1, getRandomNumber(24) + -6469.6, getRandomNumber(360), 0)
	spawnMobile("rori", "rebel_trooper", 360, getRandomNumber(16) + 3618.3, 96.1, getRandomNumber(24) + -6469.6, getRandomNumber(360), 0)
	spawnMobile("rori", "rebel_medic", 360, getRandomNumber(16) + 3618.3, 96.1, getRandomNumber(24) + -6469.6, getRandomNumber(360), 0)
	spawnMobile("rori", "rebel_trooper", 360, getRandomNumber(16) + 3618.3, 96.1, getRandomNumber(24) + -6469.6, getRandomNumber(360), 0)
	spawnMobile("rori", "rebel_trooper", 360, getRandomNumber(16) + 3618.3, 96.1, getRandomNumber(24) + -6469.6, getRandomNumber(360), 0)
	spawnMobile("rori", "rebel_first_lieutenant", 360, getRandomNumber(16) + 3618.3, 96.1, getRandomNumber(24) + -6469.6, getRandomNumber(360), 0)

	spawnMobile("rori", "rebel_army_captain", 360, getRandomNumber(16) + 3708.4, 96.1, getRandomNumber(24) + -6429.6, getRandomNumber(360), 0)
	spawnMobile("rori", "rebel_trooper", 360, getRandomNumber(16) + 3708.4, 96.1, getRandomNumber(24) + -6429.6, getRandomNumber(360), 0)
	spawnMobile("rori", "rebel_trooper", 360, getRandomNumber(16) + 3708.4, 96.1, getRandomNumber(24) + -6429.6, getRandomNumber(360), 0)
	spawnMobile("rori", "rebel_trooper", 360, getRandomNumber(16) + 3708.4, 96.1, getRandomNumber(24) + -6429.6, getRandomNumber(360), 0)
	spawnMobile("rori", "rebel_trooper", 360, getRandomNumber(16) + 3708.4, 96.1, getRandomNumber(24) + -6429.6, getRandomNumber(360), 0)
	spawnMobile("rori", "rebel_trooper", 360, getRandomNumber(16) + 3708.4, 96.1, getRandomNumber(24) + -6429.6, getRandomNumber(360), 0)

	spawnMobile("rori", "specforce_wilderness_operative", 360, 3696.0, 85.0, -6566.6, -110, 0)
	spawnMobile("rori", "specforce_wilderness_operative", 360, 3685.3, 86.8, -6573.1, 10, 0)
	spawnMobile("rori", "specforce_wilderness_operative", 360, 3664.1, 86.4, -6574.7, 160, 0)
	spawnMobile("rori", "specforce_wilderness_operative", 360, 3629.9, 83.8, -6570.1, -90, 0)

	spawnMobile("rori", "specforce_marine", 360, 3654.9, 96.0, -6499.0, 180, 0)
	spawnMobile("rori", "specforce_marine", 360, 3674.4, 96.0, -6499.0, 180, 0)

		--Outside
	spawnMobile("rori", "rebel_army_captain", 360, 3644, 96, -6404, 133, 0)
	spawnMobile("rori", "rebel_colonel", 360, 3662, 96, -6402, 162, 0)
	spawnMobile("rori", "rebel_surface_marshall", 360, 3660, 96, -6443, 342, 0)
	spawnMobile("rori", "rebel_commando", 360, 3703, 96, -6404, 265, 0)
	spawnMobile("rori", "rebel_commando", 360, 3703, 96, -6431, 270, 0)
	spawnMobile("rori", "rebel_colonel", 360, 3694, 96, -6441, 0, 0)
	spawnMobile("rori", "rebel_specforce_captain", 360, 3679, 96, -6446, 210, 0)
	spawnMobile("rori", "rebel_colonel", 360, 3658, 96, -6443, 90, 0)
	spawnMobile("rori", "rebel_specforce_urban_guerrilla", 360, 3670, 96, -6443, 270, 0)
	spawnMobile("rori", "rebel_colonel", 360, 3641, 96, -6432, 90, 0)
	spawnMobile("rori", "specforce_major", 360, 3671, 96, -6480, 270, 0)
	spawnMobile("rori", "rebel_specforce_sergeant", 360, 3657, 96, -6483, 140, 0)
	spawnMobile("rori", "specforce_wilderness_operative", 360, 3642, 96, -6477, 110, 0)
	spawnMobile("rori", "rebel_specforce_urban_guerrilla", 360, 3656, 96, -6463, 80, 0)
	spawnMobile("rori", "specforce_marine", 360, 3684, 96, -6458, 280, 0)
		--Guard Tower with rifle trainer
	spawnMobile("rori", "rebel_specforce_pathfinder", 360, 3651, 103, -6485, 90, 0)
	spawnMobile("rori", "specforce_wilderness_operative", 360, 3651, 103, -6489, 90, 0)
	spawnMobile("rori", "specforce_lieutenant", 360, 3645, 103, -6494, 180, 0)
	spawnMobile("rori", "rebel_specforce_urban_guerrilla", 360, -2.0, 2, 3.5, 90, 4505604)
		--Guard Tower with carbine trainer
	spawnMobile("rori", "specforce_wilderness_operative", 360, 3635, 103, -6439, 91, 0)
	spawnMobile("rori", "rebel_specforce_pathfinder", 360, 3632, 103, -6432, 0, 0)
	spawnMobile("rori", "specforce_wilderness_operative", 360, -2.5, 2.0, 3.7, 70, 4505993)
		--Guard Tower with marksman trainer
	spawnMobile("rori", "specforce_wilderness_operative", 360, 3680, 103, -6491, 170, 0)
	spawnMobile("rori", "rebel_specforce_pathfinder", 360, 3677, 103, -6481, 180, 0)
	spawnMobile("rori", "specforce_wilderness_operative", 360, 3685, 103, -6485, 50, 0)
		-- Tavern
	spawnMobile("rori", "rebel_medic", 360, -8.5, 0.6, -7.3, 47, 4505636)
	spawnMobile("rori", "specforce_marine", 360, 2.2, 0.6, -2.2, 243, 4505636)
	spawnMobile("rori", "specforce_marine", 360, 2.1, 0.6, -6.5, 280, 4505636)
	spawnMobile("rori", "rebel_high_general", 360, 7.8, 0.6, -4.4, 270, 4505637)
		--Left Storage Shed with quest givers
	spawnMobile("rori", "specforce_marine", 360, 0, 0.1, -6.0, 0, 4505666)
		--Right Storage Shed (Cloner)
	spawnMobile("rori", "rebel_medic", 360, 5.3, 0.1, 0.9, 270, 4505609)
	spawnMobile("rori", "rebel_colonel", 360, 0, 0.1, -6.0, 0, 4505608)

	--misc
	spawnMobile("rori", "rebel_recruiter", 0, 3683, 96, -6460, -101, 0)

	--trainer
	spawnMobile("rori", "trainer_architect", 60, 3677, 96, -6418, 90, 0)
	spawnMobile("rori", "trainer_armorsmith", 60, 3676, 96, -6432, 90, 0)
	spawnMobile("rori", "trainer_carbine", 60, 3627, 104, -6433, 90, 0)
	spawnMobile("rori", "trainer_chef", 60, 3681, 96, -6426, 180, 0)
	spawnMobile("rori", "trainer_commando", 60, -1.6, 0.7, 2.7, 180, 4505792)
	spawnMobile("rori", "trainer_marksman", 60, 3684.5, 104, -6488.5, 260, 0)
	spawnMobile("rori", "trainer_rifleman", 60, 3649, 104, -6491.5, 315, 0)
	spawnMobile("rori", "trainer_weaponsmith", 60, 3681, 96, -6420, 0, 0)
end
