RoriRestussScreenPlay = ScreenPlay:new {
	numberOfActs = 1,

	screenplayName = "RoriRestussScreenPlay"
}

registerScreenPlay("RoriRestussScreenPlay",  true)

function RoriRestussScreenPlay:start()
	if (isZoneEnabled("rori")) then
		self:spawnMobiles()
	end
end

function RoriRestussScreenPlay:spawnMobiles()
	--thugs


	--misc
	spawnMobile("rori", "imperial_recruiter",0, 5348, 0, 5618, 0, 0)
	spawnMobile("rori", "informant_npc_lvl_1",0, 5401, 0, 5857, 45, 0)
	spawnMobile("rori", "informant_npc_lvl_3",0, 5102, 0, 5652, 30, 0)
	spawnMobile("rori", "junk_dealer", 0, 5353.8, 80, 5665.9, 180, 0)

	--trainers
	spawnMobile("rori", "trainer_architect", 0, 11, 1.133, -14.5, 0, 4635774)
	spawnMobile("rori", "trainer_architect", 0, 5510, 80, 5663, 214, 0)
	spawnMobile("rori", "trainer_armorsmith", 0, -12.5, 1.13306, 3.55, 157, 4635773)
	spawnMobile("rori", "trainer_artisan", 0, 0, 1.1, -14, 0, 4635664)
	spawnMobile("rori", "trainer_artisan", 0, 5256, 80, 5600, 13, 0)
	spawnMobile("rori", "trainer_brawler", 0, -11, 1, -14, 0, 4635691)
	spawnMobile("rori", "trainer_brawler", 0, 5335.31, 80, 5530.48, 0, 0)
	spawnMobile("rori", "trainer_chef", 0, 5181, 0, 5668, 180, 0)
	spawnMobile("rori", "trainer_combatmedic", 0, -16.3425, 0.26, 10.8489, 168, 4635732)
	spawnMobile("rori", "trainer_combatmedic", 0, 26.6144, 0.26, 5.52845, 84, 4635728)
	spawnMobile("rori", "trainer_commando", 0, 9.51478, 1.13306, -10.433, 39, 4635689)
	spawnMobile("rori", "trainer_creaturehandler", 0, 5134, 80, 5749, 180, 0)
	spawnMobile("rori", "trainer_dancer", 0, 17.9253, 2.12876, 53.5327, 0, 4635754)
	spawnMobile("rori", "trainer_dancer", 0, 18.0876, 2.12874, 53.6634, 1, 4635403)
	spawnMobile("rori", "trainer_dancer", 0, 5437, 80.6, 5564, 270, 0)
	spawnMobile("rori", "trainer_doctor", 0, 20.8797, 0.26, -4.8809, 46, 4635728)
	spawnMobile("rori", "trainer_doctor", 0, 5373, 80, 5589, 180, 0)
	spawnMobile("rori", "trainer_droidengineer", 0, -11.4803, 1.13306, -13.6866, 4, 4635776)
	spawnMobile("rori", "trainer_droidengineer", 0, 5186, 80, 5719, 90, 0)
	spawnMobile("rori", "trainer_entertainer", 0, 28, 2.1, 73, 270, 4635754)
	spawnMobile("rori", "trainer_entertainer", 0, 29.5159, 2.12878, 73.6413, 88, 4635403)
	spawnMobile("rori", "trainer_entertainer", 0, 5433, 80.6, 5558, 270, 0)
	spawnMobile("rori", "trainer_imagedesigner", 0, -21.5126, 2.12878, 74.0536, 181, 4635404)
	spawnMobile("rori", "trainer_imagedesigner", 0, -22.3, 2.1, 73.1, 90, 4635755)
	spawnMobile("rori", "trainer_imagedesigner", 0, 5255, 0, 5850, 180, 0)
	spawnMobile("rori", "trainer_marksman", 0, 0, 0, -13, 0, 4635690)
	spawnMobile("rori", "trainer_marksman", 0, 0, 1.13306, -13, 0, 4615374)
	spawnMobile("rori", "trainer_marksman", 0, 5528, 80.7357, 5641, 91, 0)
	spawnMobile("rori", "trainer_medic", 0, 13.2069, 0.26, 4.92654, 165, 4635728)
	spawnMobile("rori", "trainer_merchant", 0, 11.6338, 1.13306, 5.69637, 177, 4635772)
	spawnMobile("rori", "trainer_merchant", 0, 5388, 80, 5673, 110, 0)
	spawnMobile("rori", "trainer_musician", 0, 21.5522, 2.12797, 63.5137, 0, 4635403)
	spawnMobile("rori", "trainer_musician", 0, 21.6954, 2.12795, 63.866, 0, 4635754)
	spawnMobile("rori", "trainer_musician", 0, 5432.89, 80.6, 5569.12, 270, 0)
	spawnMobile("rori", "trainer_polearm", 0, 5090, 80, 5759, 180, 0)
	spawnMobile("rori", "trainer_scout", 0, -12.5744, 1.13306, 4.79458, 180, 4635688)
	spawnMobile("rori", "trainer_scout", 0, 5371, 0, 5539, 180, 0)
	spawnMobile("rori", "trainer_tailor", 0, 11, 0, -13, 0, 4635663)
	spawnMobile("rori", "trainer_tailor", 0, 5209, 0, 5729, 180, 0)
	spawnMobile("rori", "trainer_weaponsmith", 0, 0, 1, -13, 0, 4635775)
end
