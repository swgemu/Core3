--This is to be used for static spawns that are NOT part of caves, cities, dungeons, poi's, or other large screenplays.
EndorStaticSpawnsScreenPlay = ScreenPlay:new 
{
	numberOfActs = 1,

	screenplayName = "EndorStaticSpawnsScreenPlay",
}

registerScreenPlay("EndorStaticSpawnsScreenPlay", true)

function EndorStaticSpawnsScreenPlay:start()
	if (isZoneEnabled("endor")) then
		self:spawnMobiles()
	end
end

function EndorStaticSpawnsScreenPlay:spawnMobiles()

	--Need to add the rest of static spawns (Incomplete).

	--Donkuwah Hut 4031 -7668
	spawnMobile("endor", "tainted_donkuwah_dark_shaman",300, 4031.5, 0.8, -7668.1, -34, 0)

	spawnMobile("endor", "jinda_worker",300, -3824.6, 2.5, -1874.2, 136, 0)
	spawnMobile("endor", "jinda_worker",300, -3821.0, 2.4, -1876.9, 32, 0)
	spawnMobile("endor", "jinda_warrior",300, -3824.7, 3.2, -1878.4, -151, 0)

	spawnMobile("endor", "korga_ancient",300, -1793.9, 399.6, 6013.9, -37, 0)
	spawnMobile("endor", "tainted_korga_dark_shaman",300, -5888.5, 23.3, 2358.4, -91, 0)
	spawnMobile("endor", "tricky_korga_scout",300, -6800.4, 108.4, -3445.0, 14, 0)
	spawnMobile("endor", "tricky_korga_scout",300, -6795.7, 107.6, -3452.7, 90, 0)

	spawnMobile("endor", "weathered_panshee_shaman", 300, -7555.3, 271.2, 4452.2, 147, 0)
	spawnMobile("endor", "panshee_warrior", 300, -5441.6, 184.11, -2184.3, -19, 0)
	spawnMobile("endor", "panshee_warrior", 300, -5447.3, 182.2, -2177.4, -14, 0)
	spawnMobile("endor", "panshee_warrior", 300, -5465.1, 185.2, -2180.5, -55, 0)
	spawnMobile("endor", "panshee_warrior", 300, -5466.8, 185.3, -2182.1, -53, 0)
	spawnMobile("endor", "archaic_panshee_ritualist", 300, -5450.6, 183.8, -2193.6, 114, 0)

	spawnMobile("endor", "tainted_pubam_dark_shaman",300, -6880.6, 205.4, 1364.0, 93, 0)

	--ewok outcast tree
	spawnMobile("endor", "ewok_outcast",300, -4800.3, 19.9, 1147.4, -126, 0)
	spawnMobile("endor", "ewok_outcast",300, -4784.1, 19.9, 1143.3, 94, 0)
	spawnMobile("endor", "ewok_outcast",300, -4793.8, 9.9, 1150.3, 94, 0)
	spawnMobile("endor", "ewok_outcast",300, -4802.6, 0.2, 1146.7, -71, 0)
	spawnMobile("endor", "ewok_outcast_raider",300, -4827.9, 0.7, 1160.6, 85, 0)
	
	--merek spawns (3900, 5750)
    spawnMobile("endor", "king_merek_harvester", 600, 3900, 199, 5750, getRandomNumber(360), 0)
    spawnMobile("endor", "merek_harvester", 300, 3886, 199, 5768, getRandomNumber(360), 0)
    spawnMobile("endor", "merek_harvester", 300, 3899, 199, 5774, getRandomNumber(360), 0)
    spawnMobile("endor", "merek_harvester", 300, 3915, 202, 5793, getRandomNumber(360), 0)
    spawnMobile("endor", "merek_harvester", 300, 3942, 199, 5754, getRandomNumber(360), 0)
    spawnMobile("endor", "merek_harvester", 300, 3938, 199, 5734, getRandomNumber(360), 0)
end
