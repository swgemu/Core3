RoriNarmleScreenPlay = ScreenPlay:new {
	numberOfActs = 1,

	screenplayName = "RoriNarmleScreenPlay"
}

registerScreenPlay("RoriNarmleScreenPlay", true)

function RoriNarmleScreenPlay:start()
	if (isZoneEnabled("rori")) then
		self:spawnMobiles()
	end
end

function RoriNarmleScreenPlay:spawnMobiles()
	--thugs

	--misc
	spawnMobile("rori", "imperial_recruiter",0, -5256, 0, -2256, 270, 0)
	spawnMobile("rori", "informant_npc_lvl_1", 0, -5120,0, -2269, 0, 0)
	spawnMobile("rori", "informant_npc_lvl_1", 0, -5127,0, -2266, 45, 0)
	spawnMobile("rori", "informant_npc_lvl_1", 0, -5331,0, -2233, 180, 0)
	spawnMobile("rori", "junk_dealer", 0, -5428.2, 80, -2244.2, 10, 0)

	--trainers
	spawnMobile("rori", "trainer_1hsword", 0, -5219, 80.6094, -2164, 0, 0)
	spawnMobile("rori", "trainer_2hsword", 0, -5214, 80.4173, -2167, 0, 0)
	spawnMobile("rori", "trainer_architect", 0, -5120, 80, -2443, 0, 0)
	spawnMobile("rori", "trainer_architect", 0, 11, 1.1, -14.5, 0, 4635413)
	spawnMobile("rori", "trainer_armorsmith", 0, -12, 1.1, 5, 180, 4635412)
	spawnMobile("rori", "trainer_armorsmith", 0, -5248, 80, -2358, 36, 0)
	spawnMobile("rori", "trainer_artisan", 0, -5160.97, 80, -2325.27, 137, 0)
	spawnMobile("rori", "trainer_artisan", 0, 0, 1.1, -13, 0, 4615384)
	spawnMobile("rori", "trainer_bountyhunter", 0, -5232, 80, -2241, 120, 0)
	spawnMobile("rori", "trainer_brawler", 0, -11, 0, -13, 0, 4615375)
	spawnMobile("rori", "trainer_brawler", 0, -5212, 80, -2449, 180, 0)
	spawnMobile("rori", "trainer_carbine", 0, -5139, 0, -2517, 90, 0)
	spawnMobile("rori", "trainer_chef", 0, -5169, 0, -2326, 140, 0)
	spawnMobile("rori", "trainer_combatmedic", 0, -16.4, 0.26, 10.9, 180, 4635424)
	spawnMobile("rori", "trainer_combatmedic", 0, 26.6041, 0.26, 5.45989, 83, 4635420)
	spawnMobile("rori", "trainer_commando", 0, -5181, 80, -2350, 120, 0)
	spawnMobile("rori", "trainer_doctor", 0, -25.5, 0.26, -4, 180, 4635424)
	spawnMobile("rori", "trainer_doctor", 0, -5104, 0, -2249, 270, 0)
	spawnMobile("rori", "trainer_doctor", 0, 20.5091, 0.26, -6.05941, 12, 4635420)
	spawnMobile("rori", "trainer_droidengineer", 0, -11, 1.1, -12, 0, 4635415)
	spawnMobile("rori", "trainer_entertainer", 0, -5078, 80, -2354, 146, 0)
	spawnMobile("rori", "trainer_medic", 0, -17.4597, 0.26, 0.00620247, 4, 4635424)
	spawnMobile("rori", "trainer_medic", 0, 13.545, 0.26, 5.01144, 165, 4635420)
	spawnMobile("rori", "trainer_merchant", 0, -5159, 80, -2325, 137, 0)
	spawnMobile("rori", "trainer_merchant", 0, 12, 1.13306, 6, 180, 4635411)
	spawnMobile("rori", "trainer_pistol", 0, -5242, 0, -2456, 180, 0)
	spawnMobile("rori", "trainer_polearm", 0, -5278, 0, -2328, 180, 0)
	spawnMobile("rori", "trainer_politician", 0, -5165, 0, -2463, 90, 0)
	spawnMobile("rori", "trainer_ranger", 0, -5167, 0, -2535, 180, 0)
	spawnMobile("rori", "trainer_rifleman", 0, -5215, 80, -2373, 180, 0)
	spawnMobile("rori", "trainer_scout", 0, -12, 0, 5, 180, 4615372)
	spawnMobile("rori", "trainer_scout", 0, -4951.32, 79.9841, -2373.68, 118, 0)
	spawnMobile("rori", "trainer_scout", 0, -5211, 0, -2925, 180, 0)
	spawnMobile("rori", "trainer_tailor", 0, 11, 0, -13, 0, 4615383)
	spawnMobile("rori", "trainer_unarmed", 0, -5288, 79.0383, -2508, 0, 0)
	spawnMobile("rori", "trainer_weaponsmith", 0, -5274, 0, -2424, 0, 0)
	spawnMobile("rori", "trainer_weaponsmith", 0, 0, 1, -13, 0, 4635414)
end
