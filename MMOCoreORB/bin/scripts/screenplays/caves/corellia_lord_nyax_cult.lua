LordNyaxCultScreenPlay = ScreenPlay:new {
	numberOfActs = 1,
	
	screenplayName = "LordNyaxCultScreenPlay",
	
	lootContainers = {
		6036023,
		6036026,
		6036035
	},
	
	lootLevel = 26,	

	lootGroups = {
		{
			groups = {
				{group = "color_crystals", chance = 200000},
				{group = "junk", chance = 7600000},
				{group = "heavy_weapons_consumable", chance = 500000},
				{group = "rifles", chance = 500000},
				{group = "carbines", chance = 500000},
				{group = "pistols", chance = 500000},
				{group = "clothing_attachments", chance = 100000},
				{group = "armor_attachments", chance = 100000}
			},
			lootChance = 8000000
		}					
	},
	
	lootContainerRespawn = 1800 -- 30 minutes
}

registerScreenPlay("LordNyaxCultScreenPlay", true)

function LordNyaxCultScreenPlay:start()
	if (isZoneEnabled("corellia")) then
		self:spawnMobiles()
		self:initializeLootContainers()
	end
end

function LordNyaxCultScreenPlay:spawnMobiles()
	--Outside
	spawnMobile("corellia", "fanatic_of_lord_nyax", 300, 1353.6, 31, -320.4, 9, 0)
	spawnMobile("corellia", "visionary_of_lord_nyax", 300, 1359, 31, -317.6, -71, 0)
	spawnMobile("corellia", "zealot_of_lord_nyax", 300, 1356.6, 31, -319.5, -36, 0)
	spawnMobile("corellia", "fiend_of_lord_nyax", 300, 1381.1, 31, -334.4, -157, 0)
	spawnMobile("corellia", "disciple_of_lord_nyax", 300, 1380.3, 31, -336.9, 19, 0)
	spawnMobile("corellia", "minion_of_lord_nyax", 300, 1354.5, 31, -345.9, -120, 0)
	spawnMobile("corellia", "servant_of_lord_nyax", 300, 1351.9, 31, -347.3, 51, 0)
	--Inside
	spawnMobile("corellia", "fiend_of_lord_nyax", 300, 0.200391, 0.25, 5.98459, 0, 6035995)
	spawnMobile("corellia", "fiend_of_lord_nyax", 300, -0.494639, 0.25, 6.25404, 0, 6035995)
	spawnMobile("corellia", "disciple_of_lord_nyax", 300, 3.6188, 0.25, -4.09898, 0, 6035996)
	spawnMobile("corellia", "disciple_of_lord_nyax", 300, 2.61819, 0.25, -3.44736, 0, 6035996)
	spawnMobile("corellia", "zealot_of_lord_nyax", 300, 4.81463, -6.75, 5.40781, 0, 6035998)
	spawnMobile("corellia", "visionary_of_lord_nyax", 300, 3.44729, -6.75, 4.34948, 0, 6035998)
	spawnMobile("corellia", "zealot_of_lord_nyax", 300, 2.80898, -6.75, -7.19805, 0, 6035999)
	spawnMobile("corellia", "disciple_of_lord_nyax", 300, -5.37152, -13.7499, 0.459682, 0, 6036001)
	spawnMobile("corellia", "disciple_of_lord_nyax", 300, -3.0171, -13.7499, -0.894038, 0, 6036001)
	spawnMobile("corellia", "fiend_of_lord_nyax", 300, -1.05993, -13.7499, -2.09377, 0, 6036001)
	spawnMobile("corellia", "fiend_of_lord_nyax", 300, -5.53416, -13.75, -8.46985, 0, 6036001)
	spawnMobile("corellia", "fiend_of_lord_nyax", 300, 16.6905, -13.7584, 4.76515, 0, 6036003)
	spawnMobile("corellia", "visionary_of_lord_nyax", 300, 14.4694, -13.7584, 2.8743, 0, 6036003)
	spawnMobile("corellia", "lord_nyax", 1200, 19.4, -11.4, -21.1, 0, 6036004, true)
end
