EndorDulokVillageSouthScreenPlay = ScreenPlay:new {
	numberOfActs = 1,

}

registerScreenPlay("EndorDulokVillageSouthScreenPlay", true)

function EndorDulokVillageSouthScreenPlay:start()
	if (isZoneEnabled("endor")) then
		self:spawnMobiles()
	end
end

function EndorDulokVillageSouthScreenPlay:spawnMobiles()

	spawnMobile("endor", "donkuwah_scout",300, 5934.7, 235, -2514.5, -95, 0)
	spawnMobile("endor", "donkuwah_scout",300, 5934.2, 235.1, -2510, -95, 0)
	spawnMobile("endor", "donkuwah_scout",300, 5933.2, 234.7, -2505.3, -95, 0)

	spawnMobile("endor", "crafty_donkuwah_scout",300, 5997.3, 250, -2510.4, -148, 0)
	spawnMobile("endor", "beguiling_donkuwah_scout",300, 5993.7, 250, -2500.4, -104, 0)
	spawnMobile("endor", "tricky_donkuwah_scout",300, 5995.5, 250, -2482.3, -49, 0)

	spawnMobile("endor", "tricky_donkuwah_scout",300, 6075.6, 260, -2525.9, -179, 0)

	spawnMobile("endor", "bewitching_donkuwah_shaman",300, 6055, 262, -2492.5, -8, 0)
	spawnMobile("endor", "donkuwah_cub",300, 6050.2, 262, -2513.6, -151, 0)
	spawnMobile("endor", "donkuwah_cub",300, 6047.1, 262, -2513.7, 147, 0)
	spawnMobile("endor", "donkuwah_cub",300, 6047.3, 262, -2517.2, 34, 0)
	spawnMobile("endor", "donkuwah_cub",300, 6050.4, 262, -2517.3, -52, 0)
	spawnMobile("endor", "grungy_donkuwah_laborer",300, 6060.3, 262, -2519.2, -19, 0)
	spawnMobile("endor", "grungy_donkuwah_laborer",300, 6056.5, 262, -2518.1, 41, 0)
	spawnMobile("endor", "shaggy_donkuwah_youth",300, 6062.3, 262, -2501.1, -177, 0)
	spawnMobile("endor", "donkuwah_tribesman",300, 6045.5, 262, -2501.1, 130, 0)
	spawnMobile("endor", "donkuwah_tribesman",300, 6049.2, 262, -2500.6, -178, 0)

	spawnMobile("endor", "foul_donkuwah_laborer",300, 6091.4, 263, -2481.5, 29, 0)
	spawnMobile("endor", "foul_donkuwah_laborer",300, 6054.1, 262, -2502.9, -19, 0)
	spawnMobile("endor", "foul_donkuwah_laborer",300, 6077.8, 263, -2443.6, 98, 0)
	spawnMobile("endor", "foul_donkuwah_laborer",300, 6036.2, 262, -2453.4, -89, 0)

	spawnMobile("endor", "donkuwah_battlelord",300, 6030.4, 262, -2457.5, 85, 0)
	spawnMobile("endor", "donkuwah_battlelord",300, 6032.8, 262, -2447.9, 105, 0)
	spawnMobile("endor", "donkuwah_shaman",300, 6032.4, 262, -2468, 152, 0)
	spawnMobile("endor", "donkuwah_spiritmaster",300, 6047.4, 262, -2465.5, -65, 0)

	spawnMobile("endor", "eerie_donkuwah_spiritmaster",300, 6089.7, 263.1, -2475.5, -138, 0)
	spawnMobile("endor", "haggard_donkuwah_battlelord",300, 6098.4, 263.2, -2480.2, -134, 0)
	spawnMobile("endor", "vile_donkuwah_battlelord",300, 6100.2, 263, -2490, -68, 0)
	spawnMobile("endor", "vile_donkuwah_battlelord",300, 6093.9, 263, -2498.2, -45, 0)
	spawnMobile("endor", "vile_donkuwah_battlelord",300, 6100.9, 263, -2505.9, -103, 0)
	spawnMobile("endor", "vile_donkuwah_battlelord",300, 6092, 263, -2518.6, -25, 0)

	spawnMobile("endor", "frenzied_donkuwah",300, 6077.9, 263, -2451.1, -69, 0)
	spawnMobile("endor", "frenzied_donkuwah",300, 6084.2, 264.2, -2442.2, -77, 0)
	spawnMobile("endor", "frenzied_donkuwah",300, 6071.9, 263, -2432.8, -174, 0)
	spawnMobile("endor", "frenzied_donkuwah",300, 6062.8, 263, -2439.2, 148, 0)
	spawnMobile("endor", "frenzied_donkuwah",300, 6060.7, 263, -2427.6, -121, 0)

	spawnMobile("endor", "foul_donkuwah_laborer",300, 6044.4, 260, -2442.6, 140, 0)
	spawnMobile("endor", "foul_donkuwah_laborer",300, 6046, 260, -2444.5, -42, 0)

	spawnMobile("endor", "foul_donkuwah_laborer",300, 6075.1, 260, -2504.8, 0, 0)
	spawnMobile("endor", "foul_donkuwah_laborer",300, 6075.1, 260, -2502.7, 175, 0)

	spawnMobile("endor", "vile_donkuwah_battlelord",300, 6081.1, 263.6, -2463.2, 59, 0)
	spawnMobile("endor", "vile_donkuwah_battlelord",300, 6083.2, 263.8, -2464, -49, 0)
	spawnMobile("endor", "vile_donkuwah_battlelord",300, 6083.3, 263.9, -2461.6, -157, 0)

	spawnMobile("endor", "donkuwah_chieftain",300, 6108.6, 265, -2450.7, 60, 0)
	spawnMobile("endor", "enraged_donkuwah",300, 6098.9, 265, -2459.4, -93, 0)
	spawnMobile("endor", "enraged_donkuwah",300, 6096.3, 265, -2454.7, -160, 0)

end
