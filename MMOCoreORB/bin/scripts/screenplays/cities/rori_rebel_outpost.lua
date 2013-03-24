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
		--Outside
	spawnMobile("rori", "rebel_army_captain", 360, 3644, 96, -6404, 133, 0)
	spawnMobile("rori", "rebel_colonel", 360, 3662, 96, -6402, 162, 0)
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
	spawnMobile("rori", "rebel_recruiter", 0, 3683, 0, -6460, -101, 0)

	--quest
	spawnMobile("rori", "booto_lubble", 60, 4.0, 0.7, 0.5, 170, 4505791)

	--trainer
	spawnMobile("rori", "trainer_armorsmith", 0, 3676, 94.2, -6419, 57, 0)
	spawnMobile("rori", "trainer_carbine", 0, 3627, 104, -6433, 89, 0)
	spawnMobile("rori", "trainer_commando", 0, -1.6, 0.7, 2.7, 180, 4505792)
	spawnMobile("rori", "trainer_marksman", 0, 3684.5, 104, -6488.5, 260, 0)
	spawnMobile("rori", "trainer_rifleman", 0, 3649, 104, -6491.5, 315, 0)
	spawnMobile("rori", "trainer_weaponsmith", 0, 3681, 0, -6420, 180, 0)
end
