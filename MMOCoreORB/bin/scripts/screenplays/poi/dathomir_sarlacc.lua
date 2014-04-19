DathominrSarlaccScreenPlay = ScreenPlay:new {
	numberOfActs = 1,

	screenplayName = "DathominrSarlaccScreenPlay",

}

registerScreenPlay("DathominrSarlaccScreenPlay", true)

function DathominrSarlaccScreenPlay:start()
	if (isZoneEnabled("dathomir")) then
		self:spawnMobiles()

	end
end

function DathominrSarlaccScreenPlay:spawnMobiles()

	spawnMobile("dathomir", "mutant_rancor", 360, -2096.8, 29.2, 3186.8, -40, 0)
	spawnMobile("dathomir", "mutant_rancor", 360, -2077.2, 41.8, 3249.2, 0, 0)
	spawnMobile("dathomir", "mutant_rancor", 360, -2016.8, 37.9, 3225.3, 140, 0)
	spawnMobile("dathomir", "mutant_rancor", 360, -2032.2, 32.9, 3185.2, -94, 0)
	spawnMobile("dathomir", "mutant_rancor", 360, -2065.2, 21.2, 3156.0, -94, 0)
	spawnMobile("dathomir", "mutant_rancor", 360, -2060.2, 24.8, 3107.7, -168, 0)
	spawnMobile("dathomir", "mutant_rancor", 360, -2028.3, 26.3, 3091.1, 84, 0)
	spawnMobile("dathomir", "mutant_rancor", 360, -1965.2, 45.7, 3146.2, -4, 0)
	spawnMobile("dathomir", "mutant_rancor", 360, -1944.2, 25.4, 3070.8, -114, 0)
	spawnMobile("dathomir", "mutant_rancor", 360, -1986.1, 25.8, 2986.7, 134, 0)
	spawnMobile("dathomir", "mutant_rancor", 360, -2046.2, 34.3, 3014.0, -154, 0)
	spawnMobile("dathomir", "mutant_rancor", 360, -2064.1, 39.0, 2967.1, 171, 0)
	spawnMobile("dathomir", "mutant_rancor", 360, -2125.6, 29.1, 3009.9, -104, 0)
	spawnMobile("dathomir", "mutant_rancor", 360, -2147.1, 44.3, 3071.2, -33, 0)
	spawnMobile("dathomir", "mutant_rancor", 360, -2145.9, 23.9, 3153.2, -84, 0)
	spawnMobile("dathomir", "mutant_rancor", 360, -2246.0, 44.4, 3211.5, -64, 0)
	spawnMobile("dathomir", "mutant_rancor", 360, -2169.7, 28.2, 3293.6, -11, 0)

	spawnMobile("dathomir", "monstrous_brute", 480, -2038.7, 32.7, 3310.1, 3, 0)
	spawnMobile("dathomir", "monstrous_brute", 480, -1923.2, 46.8, 3226.5, 43, 0)
	spawnMobile("dathomir", "ancient_bull_rancor", 720, -2210.3, 32.1, 3039.9, 0, 0)

	spawnMobile("dathomir", "mutant_baz_nitch", 300, -2132.8, 26.7, 3280.0, 76, 0)
	spawnMobile("dathomir", "mutant_baz_nitch", 300, -2128.8, 26.8, 3286.6, -176, 0)
	spawnMobile("dathomir", "mutant_baz_nitch", 300, -2124.6, 26.9, 3280.5, 146, 0)
	spawnMobile("dathomir", "mutant_baz_nitch", 300, -1965.2, 42.5, 3208.5, -175, 0)
	spawnMobile("dathomir", "mutant_baz_nitch", 300, -1960.4, 43.1, 3200.5, -106, 0)
	spawnMobile("dathomir", "mutant_baz_nitch", 300, -1967.6, 44.1, 3196.3, -146, 0)
	spawnMobile("dathomir", "mutant_baz_nitch", 300, -1960.7, 44.6, 3190.5, 146, 0)
	spawnMobile("dathomir", "mutant_baz_nitch", 300, -1949.6, 43.9, 3191.5, 46, 0)

	spawnMobile("dathomir", "disturbed_bolma", 300, -1905.1, 48.3, 3151.9, 0, 0)
	spawnMobile("dathomir", "disturbed_bolma", 300, -1898.1, 47.8, 3151.9, 0, 0)
	spawnMobile("dathomir", "disturbed_bolma", 300, -1891.1, 47.3, 3151.9, 0, 0)
	spawnMobile("dathomir", "disturbed_bolma", 300, -2002.2, 21.6, 3057.1, -90, 0)
	spawnMobile("dathomir", "disturbed_bolma", 300, -2002.2, 21.3, 3050.1, -90, 0)
	spawnMobile("dathomir", "disturbed_bolma", 300, -2002.2, 21.0, 3043.1, -90, 0)
	spawnMobile("dathomir", "disturbed_bolma", 300, -2200.4, 28.1, 3132.1, -110, 0)
	spawnMobile("dathomir", "disturbed_bolma", 300, -2208.4, 28.5, 3139.5, -110, 0)

	spawnMobile("dathomir", "nocuous_kamurith", 300, -2140.5, 26.0, 3210.5, 180, 0)
	spawnMobile("dathomir", "nocuous_kamurith", 300, -2159.9, 24.4, 3180.5, 171, 0)
	spawnMobile("dathomir", "nocuous_kamurith", 300, -2113.0, 20.0, 3140.5, -161, 0)
	spawnMobile("dathomir", "nocuous_kamurith", 300, -2002.9, 43.2, 3142.0, 1, 0)
	spawnMobile("dathomir", "nocuous_kamurith", 300, -2171.9, 27.6, 2992.5, -18, 0)

end
