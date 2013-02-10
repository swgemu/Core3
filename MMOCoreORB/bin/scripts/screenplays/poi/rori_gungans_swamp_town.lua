RoriGungansSwampTownScreenPlay = ScreenPlay:new {
	numberOfActs = 1,

}

registerScreenPlay("RoriGungansSwampTownScreenPlay", true)

function RoriGungansSwampTownScreenPlay:start()
	if (isZoneEnabled("rori")) then
		self:spawnMobiles()
	end
end

function RoriGungansSwampTownScreenPlay:spawnMobiles()
	spawnMobile("rori", "rorgungan_warrior", 360, -2005.7, 78.0, 3362.5, 18, 0)
	spawnMobile("rori", "rorgungan_warrior", 360, -2004.6, 78.0, 3360.5, 78, 0)
	spawnMobile("rori", "rorgungan_warrior", 360, -2004.2, 78.0, 3358.8, 82, 0)
	spawnMobile("rori", "rorgungan_warchief", 360, -2016.4, 79.5, 3348.5, 137, 0)
	spawnMobile("rori", "rorgungan_warchief", 360, -2042.7, 78.9, 3330.3, 5, 0)
	spawnMobile("rori", "lieutenant_ori", 480, -2048.0, 77.8, 3334.9, 79, 0)
	spawnMobile("rori", "thug", 360, -2040.9, 77.5, 3336.0, -110, 0)
	spawnMobile("rori", "thug", 360, -2040.0, 78.0, 3338.2, -129, 0)
	spawnMobile("rori", "thug", 360, -2041.9, 77.7, 3338.2, -136, 0)
	spawnMobile("rori", "rorgungan_warrior", 360, -2071.9, 77.5, 3364.0, -5, 0)
	spawnMobile("rori", "rorgungan_warrior", 360, -2073.7, 77.6, 3364.2, 5, 0)
	spawnMobile("rori", "rorgungan_warrior", 360, -2075.1, 77.5, 3365.6, 0, 0)
	spawnMobile("rori", "rorgungan_warrior", 360, -2077.6, 77.8, 3366.4, 31, 0)
	spawnMobile("rori", "rorgungan_warchief", 360, -2075.3, 78.4, 3368.7, 0, 0)
	spawnMobile("rori", "rorgungan_warrior", 360, -2098.4, 76.7, 3337.4, -117, 0)
	spawnMobile("rori", "rorgungan_warrior", 360, -2098.6, 77.3, 3332.3, -107, 0)
	spawnMobile("rori", "rorgungan_warrior", 360, -2099.4, 76.7, 3335.3, -120, 0)
	spawnMobile("rori", "rorgungan_warchief", 360, -2102.3, 77.4, 3336.7, -51, 0)
	spawnMobile("rori", "lieutenant_heb_nee", 480, -2104.6, 77.5, 3333.8, -122, 0)
	spawnMobile("rori", "rorgungan_warrior", 360, -2083.1, 75.6, 3306.1, -6, 0)
	spawnMobile("rori", "rorgungan_warrior", 360, -2085.6, 75.7, 3305.8, -51, 0)
	spawnMobile("rori", "rorgungan_warrior", 360, -2085.1, 76.9, 3308.7, -6, 0)
	spawnMobile("rori", "rorgungan_warrior", 360, -2080.9, 75.8, 3280.7, 22, 0)
	spawnMobile("rori", "rorgungan_warrior", 360, -2079.5, 75.8, 3278.6, 11, 0)
	spawnMobile("rori", "rorgungan_warrior", 360, -2077.7, 75.8, 3281.5, 16, 0)
	spawnMobile("rori", "rorgungan_warchief", 360, -2071.2, 75.8, 3280.6, -49, 0)
	spawnMobile("rori", "rorgungan_warrior", 360, -2068.7, 75.8, 3255.4, -18, 0)
	spawnMobile("rori", "rorgungan_warrior", 360, -2070.9, 75.8, 3255.0, -22, 0)
	spawnMobile("rori", "captain_hassk", 600, -2087.4, 75.8, 3257.8, 123, 0)
	spawnMobile("rori", "rorgungan_warrior", 360, -2130.9, 76.2, 3272.9, -45, 0)
	spawnMobile("rori", "rorgungan_warrior", 360, -2133.9, 76.0, 3271.4, -92, 0)
	spawnMobile("rori", "rorgungan_warrior", 360, -2129.5, 76.4, 3276.3, -10, 0)
	spawnMobile("rori", "rorgungan_warrior", 360, -2134.4, 75.5, 3266.3, -90, 0)
	spawnMobile("rori", "rorgungan_warchief", 360, -2127.2, 76.1, 3270.1, -57, 0)
	spawnMobile("rori", "rorgungan_warrior", 360, -2085.8, 76.2, 3210.0, 178, 0)
	spawnMobile("rori", "rorgungan_warrior", 360, -2079.8, 76.6, 3215.9, 111, 0)
	spawnMobile("rori", "rorgungan_warrior", 360, -2084.8, 75.3, 3216.7, 140, 0)
	spawnMobile("rori", "rorgungan_warrior", 360, -2025.8, 75.1, 3276.9, 69, 0)
	spawnMobile("rori", "rorgungan_warrior", 360, -2031.6, 76.0, 3262.0, 154, 0)
	spawnMobile("rori", "rorgungan_warrior", 360, -2032.6, 75.8, 3250.6, 136, 0)
end
