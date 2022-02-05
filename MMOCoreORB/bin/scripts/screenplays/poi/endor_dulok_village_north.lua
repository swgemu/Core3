EndorDulokVillageNorthScreenPlay = ScreenPlay:new {
	numberOfActs = 1,
	planet = "endor",

	mobiles = {
		{"donkuwah_chieftain",300, -1194.2, 25.0, 2988.4, 26, 0},
		{"enraged_donkuwah",300, -1199.9, 25.0, 2981.6, 175, 0},
		{"enraged_donkuwah",300, -1198.1, 25.0, 2980.0, -104, 0},
		{"eerie_donkuwah_spiritmaster",300, -1178.1, 17.0, 2964.4, -142, 0},
		{"haggard_donkuwah_battlelord",300, -1171.0, 17.0, 2957.4, -83, 0},
		{"vile_donkuwah_battlelord",300, -1158.6, 17.0, 2953.2, -113, 0},
		{"donkuwah_battlelord",300, -1171.1, 12.0, 2927.1, -98, 0},
		{"donkuwah_battlelord",300, -1175.2, 12.0, 2928.6, 157, 0},
		{"donkuwah_battlelord",300, -1181.3, 12.0, 2922.7, 31, 0},
		{"donkuwah_battlelord",300, -1169.1, 12.0, 2920.7, -28, 0},
		{"donkuwah_shaman",300, -1158.3, 12.0, 2933.3, -76, 0},
		{"donkuwah_spiritmaster",300, -1181.2, 12.0, 2944.2, 171, 0},
		{"foul_donkuwah_laborer",300, -1199.8, 12.0, 2925.2, -78, 0},
		{"foul_donkuwah_laborer",300, -1202.0, 12.0, 2928.5, -168, 0},
		{"foul_donkuwah_laborer",300, -1205.0, 12.0, 2925.8, 102, 0},
		{"crafty_donkuwah_scout",300, -1205.9, 12.0, 2909.7, 158, 0},
		{"beguiling_donkuwah_scout",300, -1213.1, 12.0, 2906.6, -165, 0},
		{"tricky_donkuwah_scout",300, -1207.5, 12.0, 2911.2, 174, 0},
		{"donkuwah_scout",300, -1252.9, 12.0, 2929.5, -119, 0},
		{"donkuwah_scout",300, -1256.2, 12.0, 2930.9, -149, 0},
		{"donkuwah_scout",300, -1253.7, 12.0, 2925.6, -85, 0},
		{"donkuwah_laborer",300, -1238.1, 12.0, 2942.6, -127, 0},
		{"donkuwah_laborer",300, -1241.5, 12.0, 2944.6, -172, 0},
		{"foul_donkuwah_laborer",300, -1251.1, 12.0, 2950.8, -123, 0},
		{"donkuwah_cub",300, -1270.2, 12.0, 2960.4, 38, 0},
		{"donkuwah_cub",300, -1270.8, 12.0, 2962.6, 27, 0},
		{"donkuwah_cub",300, -1270.2, 12.0, 2964.8, 93, 0},
		{"donkuwah_cub",300, -1266.7, 12.0, 2963.3, -102, 0},
		{"donkuwah_tribesman",300, -1259.0, 12.0, 2954.0, -38, 0},
		{"donkuwah_tribesman",300, -1262.9, 12.0, 2956.3, 49, 0},
		{"shaggy_donkuwah_youth",300, -1253.1, 12.0, 2973.1, -128, 0},
		{"bewitching_donkuwah_shaman",300, -1261.7, 12.0, 2978.3, -136, 0},
		{"grungy_donkuwah_laborer",300, -1273.0, 12.3, 2978.1, -160, 0},
		{"grungy_donkuwah_laborer",300, -1275.9, 12.1, 2974.6, 117, 0},
		{"gnarled_donkuwah_spiritmaster",300, -1244.5, 15.1, 2974.0, 15, 0},
		{"vile_donkuwah_battlelord",300, -1246.4, 18.0, 2988.9, 125, 0},
		{"vile_donkuwah_battlelord",300, -1231.0, 18.0, 2982.0, -76, 0},
		{"vile_donkuwah_battlelord",300, -1231.5, 18.0, 2985.6, -105, 0},
		{"frenzied_donkuwah",300, -1228.9, 18.0, 2990.7, -22, 0},
		{"frenzied_donkuwah",300, -1230.3, 18.0, 2993.7, 108, 0},
		{"frenzied_donkuwah",300, -1227.4, 18.0, 2993.4, -125, 0},
		{"vicious_donkuwah_battlelord",300, -1221.6, 18, 2986.1, 27,  0},
	}

}

registerScreenPlay("EndorDulokVillageNorthScreenPlay", true)

function EndorDulokVillageNorthScreenPlay:start()
	if (isZoneEnabled(self.planet)) then
		self:spawnMobiles()
	end
end

function EndorDulokVillageNorthScreenPlay:spawnMobiles()
	local mobiles = self.mobiles

	for i = 1, #mobiles do
		local mob = mobiles[i]

		local pMobile = spawnMobile(self.planet, mob[1], mob[2], mob[3], mob[4], mob[5], mob[6], mob[7])

		if pMobile ~= nil then
			AiAgent(pMobile):addCreatureFlag(AI_STATIONARY)
		end
	end
end
