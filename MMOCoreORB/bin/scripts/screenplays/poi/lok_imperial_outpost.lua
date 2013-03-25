LokImperialOutpostScreenPlay = ScreenPlay:new {
	numberOfActs = 1,

	lootContainers = {
		2975429
	},
	
	lootLevel = 32,	

	lootGroups = {
		{
			groups = {
				{group = "color_crystals", chance = 2500000},
				{group = "junk", chance = 2500000},
				{group = "melee_two_handed", chance = 1000000},
				{group = "rifles", chance = 1000000},
				{group = "carbines", chance = 1000000},
				{group = "pistols", chance = 1000000},
				{group = "clothing_attachments", chance = 500000},
				{group = "armor_attachments", chance = 500000}
			},
			lootChance = 8000000
		}					
	},
	
	lootContainerRespawn = 1200 -- 20 minutes

}

registerScreenPlay("LokImperialOutpostScreenPlay", true)

function LokImperialOutpostScreenPlay:start()
	if (isZoneEnabled("lok")) then
		self:spawnMobiles()
		self:initializeLootContainers()		
	end
end

function LokImperialOutpostScreenPlay:spawnMobiles()

	--Perimeter mobs

	spawnMobile("lok", "at_st", 720, -1762.0, 11.9, -3087.3, 90, 0)
	spawnMobile("lok", "at_st", 720, -1939.5, 11.8, -2945.9, 0, 0)
	spawnMobile("lok", "at_st", 720, -2028.9, 11.9, -3107.5, -90, 0)
	spawnMobile("lok", "at_st", 720, -1918.5, 12.1, -3244.1, 180, 0)

	spawnMobile("lok", "stormtrooper_captain", 300, -2037.7, 11.9, -3072.0, 0, 0)
	spawnMobile("lok", "stormtrooper", 300, -2040.2, 11.9, -3072.0, 0, 0)
	spawnMobile("lok", "stormtrooper_medic", 300, -2037.7, 11.9, -3075.5, 0, 0)
	spawnMobile("lok", "stormtrooper_bombardier", 300, -2040.2, 11.9, -3075.5, 0, 0)
	spawnMobile("lok", "stormtrooper", 300, -2037.7, 11.9, -3079.0, 0, 0)
	spawnMobile("lok", "stormtrooper", 300, -2040.2, 11.9, -3079.0, 0, 0)
	spawnMobile("lok", "stormtrooper_rifleman", 300, -2037.7, 11.9, -3082.5, 0, 0)
	spawnMobile("lok", "stormtrooper_rifleman", 300, -2040.2, 11.9, -3082.5, 0, 0)

	spawnMobile("lok", "stormtrooper", 300, -2086.8, 2.9, -3041.1, 164, 0)
	spawnMobile("lok", "stormtrooper", 300, -2085.8, 2.9, -3045.5, 164, 0)
	spawnMobile("lok", "stormtrooper_rifleman", 300, -2084.8, 2.9, -3049.9, 164, 0)
	spawnMobile("lok", "stormtrooper_rifleman", 300, -2083.8, 2.9, -3054.3, 164, 0)
	spawnMobile("lok", "stormtrooper", 300, -2082.8, 2.9, -3058.7, 164, 0)
	spawnMobile("lok", "stormtrooper", 300, -2081.8, 2.9, -3063.1, 164, 0)

	spawnMobile("lok", "dark_trooper", 300, -2035.2, 11.9, -3102.5, -90, 0)
	spawnMobile("lok", "dark_trooper", 300, -2035.2, 11.9, -3107.5, -90, 0)
	spawnMobile("lok", "dark_trooper", 300, -2035.2, 11.9, -3112.5, -90, 0)
	
	spawnMobile("lok", "stormtrooper_captain", 300, -2020.0, 11.9, -2997.0, 45, 0)
	spawnMobile("lok", "stormtrooper", 300, -2018.0, 11.9, -2995.0, 45, 0)
	spawnMobile("lok", "stormtrooper_medic", 300, -2016.0, 11.9, -2993.0, 45, 0)
	spawnMobile("lok", "stormtrooper_bombardier", 300, -2014.0, 11.9, -2991.0, 45, 0)
	spawnMobile("lok", "stormtrooper", 300, -2022.0, 11.9, -2995.0, 45, 0)
	spawnMobile("lok", "stormtrooper", 300, -2020.0, 11.9, -2993.0, 45, 0)
	spawnMobile("lok", "stormtrooper_rifleman", 300, -2018.0, 11.9, -2991.0, 45, 0)
	spawnMobile("lok", "stormtrooper_rifleman", 300, -2016.0, 11.9, -2989.0, 45, 0)

	spawnMobile("lok", "dark_trooper", 300, -1939.5, 11.9, -2950.9, 0, 0)
	spawnMobile("lok", "dark_trooper", 300, -1934.5, 11.9, -2950.9, 0, 0)
	spawnMobile("lok", "dark_trooper", 300, -1944.5, 11.9, -2950.9, 0, 0)

	spawnMobile("lok", "stormtrooper_squad_leader", 300, -1911.9, 11.9, -2958.6, 90, 0)
	spawnMobile("lok", "stormtrooper_commando", 300, -1914.9, 11.9, -2958.6, 90, 0)
	spawnMobile("lok", "stormtrooper_medic", 300, -1917.9, 11.9, -2958.6, 90, 0)
	spawnMobile("lok", "stormtrooper_bombardier", 300, -1920.9, 11.9, -2958.6, 90, 0)
	spawnMobile("lok", "stormtrooper", 300, -1911.9, 11.9, -2955.1, 90, 0)
	spawnMobile("lok", "stormtrooper", 300, -1914.9, 11.9, -2955.1, 90, 0)
	spawnMobile("lok", "stormtrooper_rifleman", 300, -1917.9, 11.9, -2955.1, 90, 0)
	spawnMobile("lok", "stormtrooper_rifleman", 300, -1920.9, 11.9, -2955.1, 90, 0)

	spawnMobile("lok", "dark_trooper", 300, -1757.0, 11.9, -3087.3, 90, 0)
	spawnMobile("lok", "dark_trooper", 300, -1757.0, 11.9, -3082.3, 90, 0)
	spawnMobile("lok", "dark_trooper", 300, -1757.0, 11.9, -3092.3, 90, 0)

	spawnMobile("lok", "stormtrooper_squad_leader", 300, -1794.4, 11.9, -3100.0, 0, 0)
	spawnMobile("lok", "stormtrooper_commando", 300, -1794.4, 11.9, -3096.5, 0, 0)
	spawnMobile("lok", "stormtrooper_medic", 300, -1794.4, 11.9, -3093.0, 0, 0)
	spawnMobile("lok", "stormtrooper_bombardier", 300, -1794.4, 11.9, -3089.5, 0, 0)
	spawnMobile("lok", "stormtrooper", 300, -1790.9, 11.9, -3100.0, 0, 0)
	spawnMobile("lok", "stormtrooper", 300, -1790.9, 11.9, -3096.5, 0, 0)
	spawnMobile("lok", "stormtrooper_rifleman", 300, -1790.9, 11.9, -3093.0, 0, 0)
	spawnMobile("lok", "stormtrooper_rifleman", 300, -1790.9, 11.9, -3089.5, 0, 0)
	spawnMobile("lok", "stormtrooper", 300, -1794.4, 11.9, -3086.0, 0, 0)
	spawnMobile("lok", "stormtrooper", 300, -1790.9, 11.9, -3086.0, 0, 0)

	spawnMobile("lok", "stormtrooper_captain", 300, -1996.0, 11.9, -3216.0, 90, 0)
	spawnMobile("lok", "stormtrooper_commando", 300, -1992.5, 11.9, -3216.0, 90, 0)
	spawnMobile("lok", "stormtrooper_medic", 300, -1989.0, 11.9, -3216.0, 90, 0)
	spawnMobile("lok", "stormtrooper_bombardier", 300, -1985.5, 11.9, -3216.0, 90, 0)
	spawnMobile("lok", "stormtrooper", 300, -1982.0, 11.9, -3216.0, 90, 0)
	spawnMobile("lok", "stormtrooper", 300, -1996.0, 11.9, -3212.5, 90, 0)
	spawnMobile("lok", "stormtrooper_rifleman", 300, -1992.5, 11.9, -3212.5, 90, 0)
	spawnMobile("lok", "stormtrooper_rifleman", 300, -1989.0, 11.9, -3212.5, 90, 0)
	spawnMobile("lok", "stormtrooper", 300, -1985.5, 11.9, -3212.5, 90, 0)
	spawnMobile("lok", "stormtrooper", 300, -1982.0, 11.9, -3212.5, 90, 0)

	spawnMobile("lok", "stormtrooper_captain", 300, -1880.0, 11.9, -3216.0, 90, 0)
	spawnMobile("lok", "stormtrooper_commando", 300, -1876.5, 11.9, -3216.0, 90, 0)
	spawnMobile("lok", "stormtrooper_medic", 300, -1873.0, 11.9, -3216.0, 90, 0)
	spawnMobile("lok", "stormtrooper_bombardier", 300, -1869.5, 11.9, -3216.0, 90, 0)
	spawnMobile("lok", "stormtrooper", 300, -1866.0, 11.9, -3216.0, 90, 0)
	spawnMobile("lok", "stormtrooper", 300, -1880.0, 11.9, -3212.5, 90, 0)
	spawnMobile("lok", "stormtrooper_rifleman", 300, -1876.5, 11.9, -3212.5, 90, 0)
	spawnMobile("lok", "stormtrooper_rifleman", 300, -1873.0, 11.9, -3212.5, 90, 0)
	spawnMobile("lok", "stormtrooper", 300, -1869.5, 11.9, -3212.5, 90, 0)
	spawnMobile("lok", "stormtrooper", 300, -1866.0, 11.9, -3212.5, 90, 0)

	spawnMobile("lok", "dark_trooper", 300, -1918.5, 11.9, -3239.1, 180, 0)
	spawnMobile("lok", "dark_trooper", 300, -1913.5, 11.9, -3239.1, 180, 0)
	spawnMobile("lok", "dark_trooper", 300, -1923.5, 11.9, -3239.1, 180, 0)

	--powerplant

	spawnMobile("lok", "elite_sand_trooper", 300, -2084.8, 11.9, -2624.5, 175, 0)
	spawnMobile("lok", "imperial_second_lieutenant", 300, -2087.0, 11.9, -2625.0, 175, 0)
	spawnMobile("lok", "sand_trooper", 300, -2078.3, 11.9, -2639.1, 90, 0)
	spawnMobile("lok", "sand_trooper", 300, -2078.3, 11.9, -2645.0, 90, 0)
	spawnMobile("lok", "sand_trooper", 300, -2102.2, 11.9, -2639.1, -90, 0)
	spawnMobile("lok", "sand_trooper", 300, -2102.2, 11.9, -2645.0, -90, 0)
	spawnMobile("lok", "commoner_technician", 300, -2089.9, 11.9, -2630.4, 0, 0)
	spawnMobile("lok", "commoner_technician", 300, -2090.0, 11.9, -2659.0, 0, 0)

	spawnMobile("lok", "stormtrooper_captain", 300, -2095.5, 11.9, -2795.5, 155, 0)
	spawnMobile("lok", "stormtrooper_commando", 300, -2094.0, 11.9, -2798.7, 155, 0)
	spawnMobile("lok", "stormtrooper_medic", 300, -2092.5, 11.9, -2801.9, 155, 0)
	spawnMobile("lok", "stormtrooper_bombardier", 300, -2091.0, 11.9, -2805.1, 155, 0)
	spawnMobile("lok", "stormtrooper", 300, -2089.5, 11.9, -2808.3, 155, 0)
	spawnMobile("lok", "stormtrooper", 300, -2088.0, 11.9, -2811.5, 155, 0)
	spawnMobile("lok", "stormtrooper_rifleman", 300, -2086.5, 11.9, -2814.7, 155, 0)
	spawnMobile("lok", "stormtrooper_rifleman", 300, -2085.0, 11.9, -2817.9, 155, 0)
	spawnMobile("lok", "stormtrooper", 300, -2083.5, 11.9, -2821.1, 155, 0)
	spawnMobile("lok", "stormtrooper", 300, -2082.0, 11.9, -2824.3, 155, 0)

	--inside the walls (not in buildings)

	spawnMobile("lok", "imperial_recruiter", 20, -1843.75, 12.1, -3069.1, 123, 0)
	spawnMobile("lok", "junk_dealer", 20, -2000.5, 11.9, -3143.6, -34, 0)

	spawnMobile("lok", "imperial_surface_marshall", 300, -2001.0, 11.9, -3142.4, 156, 0)
	spawnMobile("lok", "stormtrooper", 300, -2003.3, 11.9, -3142.0, 156, 0)
	spawnMobile("lok", "stormtrooper", 300, -2000.5, 11.9, -3140.6, 156, 0)
	spawnMobile("lok", "stormtrooper", 300, -1998.4, 11.9, -3141.5, -135, 0)
	spawnMobile("lok", "stormtrooper", 300, -2002.3, 11.9, -3139.7, 156, 0)

	spawnMobile("lok", "commoner_technician", 300, -2002.1, 11.9, -3129.0, 0, 0)
	spawnMobile("lok", "commoner_technician", 300, -1999.0, 11.9, -3112.0, -90, 0)
	spawnMobile("lok", "commoner", 300, -2018.3, 11.9, -3051.0, 180, 0)
	spawnMobile("lok", "thug", 30, -2018.3, 11.9, -3040.6, 180, 0)
	spawnMobile("lok", "thug", 30, -2012.3, 11.9, -3034.8, 90, 0)
	spawnMobile("lok", "thug", 30, -2012.3, 11.9, -3029.8, 90, 0)
	spawnMobile("lok", "commoner", 300, -1986.4, 11.9, -3073.4, 45, 0)
	spawnMobile("lok", "commoner", 300, -1986.4, 11.9, -3077.9, -90, 0)

	spawnMobile("lok", "dark_trooper", 300, -2007.1, 11.9, -3030.2, -90, 0)
	spawnMobile("lok", "dark_trooper", 300, -2000.5, 11.9, -3039.8, 90, 0)
	spawnMobile("lok", "dark_trooper", 300, -2000.5, 11.9, -3049.8, 90, 0)

	spawnMobile("lok", "dark_trooper", 300, -1949.3, 11.9, -2989.7, 45, 0)
	spawnMobile("lok", "dark_trooper", 300, -1947.7, 11.9, -2976.2, 90, 0)
	spawnMobile("lok", "dark_trooper", 300, -1931.1, 11.9, -2976.2, -90, 0)
	spawnMobile("lok", "imperial_first_lieutenant", 300, -1939.4, 11.9, -2987.7, 0, 0)

	spawnMobile("lok", "commoner", 300, -1887.6, 11.9, -2975.2, -145, 0)
	spawnMobile("lok", "commoner", 300, -1888.3, 11.9, -2977.2, -40, 0)
	spawnMobile("lok", "commoner", 300, -1890.4, 11.9, -2975.2, 90, 0)
	spawnMobile("lok", "commoner", 300, -1892.1, 11.9, -3001.7, 180, 0)
	spawnMobile("lok", "commoner", 300, -1868.9, 11.9, -3001.7, 180, 0)
	spawnMobile("lok", "commoner", 300, -1897.1, 11.9, -3008.8, 90, 0)
	spawnMobile("lok", "commoner", 300, -1897.1, 11.9, -3014.8, 90, 0)

	spawnMobile("lok", "commoner", 300, -1957.5, 11.9, -3076.1, -90, 0)
	spawnMobile("lok", "commoner", 300, -1954.0, 11.9, -3076.1, -90, 0)
	spawnMobile("lok", "commoner", 300, -1951.5, 11.9, -3076.1, -90, 0)

	spawnMobile("lok", "stormtrooper", 300, -1876.2, 11.9, -3004.3, 0, 0)
	spawnMobile("lok", "stormtrooper", 300, -1876.2, 11.9, -3008.3, 0, 0)
	spawnMobile("lok", "stormtrooper", 300, -1876.2, 11.9, -3012.3, 0, 0)
	spawnMobile("lok", "stormtrooper", 300, -1876.2, 11.9, -3016.3, 0, 0)
	spawnMobile("lok", "imperial_trooper", 300, -1873.2, 11.9, -3037.2, 180, 0)
	spawnMobile("lok", "imperial_trooper", 300, -1879.2, 11.9, -3037.2, 180, 0)
	spawnMobile("lok", "imperial_medic", 300, -1891.9, 11.9, -3021.2, 0, 0)
	spawnMobile("lok", "imperial_medic", 300, -1868.2, 11.9, -3021.2, 0, 0)
	spawnMobile("lok", "stormtrooper_dewback", 300, -1891.9, 11.9, -3010.2, 180, 0)
	spawnMobile("lok", "stormtrooper_dewback", 300, -1868.2, 11.9, -3010.2, 180, 0)

	spawnMobile("lok", "stormtrooper", 300, -2024.4, 11.9, -3054.0, 180, 0)
	spawnMobile("lok", "stormtrooper", 300, -2024.4, 11.9, -3074.3, 0, 0)
	spawnMobile("lok", "imperial_trooper", 300, -1994.0, 11.9, -3086.2, -60, 0)
	spawnMobile("lok", "imperial_second_lieutenant", 300, -2017.0, 11.9, -3087.2, 0, 0)

	spawnMobile("lok", "dark_trooper", 300, -1932.1, 11.9, -3186.3, 90, 0)
	spawnMobile("lok", "dark_trooper", 300, -1907.2, 11.9, -3186.3, -90, 0)
	spawnMobile("lok", "dark_trooper", 300, -1911.1, 11.9, -3169.8, 90, 0)
	spawnMobile("lok", "stormtrooper", 300, -1911.9, 11.9, -3176.9, 90, 0)

	spawnMobile("lok", "protocol_droid_3po_red", 300, -1871.8, 11.9, -3151.6, 180, 0)
	spawnMobile("lok", "commoner", 300, -1869.5, 11.9, -3153.3, -55, 0)
	spawnMobile("lok", "commoner", 300, -1871.8, 11.9, -3153.1, 0, 0)
	spawnMobile("lok", "commoner", 300, -1873.8, 11.9, -3152.7, 45, 0)
	
	spawnMobile("lok", "at_st", 720, -1926.2, 11.8, -3142.9, 90, 0)

	spawnMobile("lok", "stormtrooper_squad_leader", 300, -1885.3, 11.9, -3111.2, 90, 0)
	spawnMobile("lok", "stormtrooper_commando", 300, -1885.3, 11.9, -3114.7, 90, 0)
	spawnMobile("lok", "stormtrooper_medic", 300, -1881.3, 11.9, -3111.2, 90, 0)
	spawnMobile("lok", "stormtrooper_bombardier", 300, -1881.3, 11.9, -3114.7, 90, 0)
	spawnMobile("lok", "stormtrooper", 300, -1877.3, 11.9, -3111.2, 90, 0)
	spawnMobile("lok", "stormtrooper", 300, -1877.3, 11.9, -3114.7, 90, 0)
	spawnMobile("lok", "stormtrooper_rifleman", 300, -1873.3, 11.9, -3111.2, 90, 0)
	spawnMobile("lok", "stormtrooper_rifleman", 300, -1873.3, 11.9, -3114.7, 90, 0)

	spawnMobile("lok", "stormtrooper_sniper", 300, -1821.7, 11.9, -3134.4, 75, 0)

	spawnMobile("lok", "stormtrooper_commando", 300, -1838.1, 11.9, -3078.0, 90, 0)
	spawnMobile("lok", "stormtrooper_commando", 300, -1838.1, 11.9, -3091.6, 90, 0)
	spawnMobile("lok", "stormtrooper_rifleman", 300, -1846.3, 11.9, -3087.4, 90, 0)
	spawnMobile("lok", "stormtrooper_rifleman", 300, -1846.3, 11.9, -3081.6, 90, 0)

	spawnMobile("lok", "stormtrooper_commando", 300, -1807.5, 11.9, -3098.8, 0, 0)
	spawnMobile("lok", "commoner_technician", 300, -1808.9, 11.9, -3077.4, -150, 0)

	spawnMobile("lok", "dark_trooper", 300, -1893.9, 11.9, -3042.0, -135, 0)
	spawnMobile("lok", "dark_trooper", 300, -1898.4, 11.9, -3047.0, -160, 0)
	spawnMobile("lok", "dark_trooper", 300, -1905.7, 11.9, -3059.0, 180, 0)
	spawnMobile("lok", "dark_trooper", 300, -1905.7, 11.9, -3075.7, 180, 0)

	--in the buildings (not main building)

	spawnMobile("lok", "imperial_first_lieutenant", 300, 4.3, 0, 1.68, -90, 8615442)
	spawnMobile("lok", "imperial_medic", 300, 3.1, 0, -3.68, 90, 8615443)
	spawnMobile("lok", "stormtrooper_medic", 300, 0, 0, -0.8, 0, 8615441)

	spawnMobile("lok", "stormtrooper_sniper", 300, 4.2, 0.5, -2.8, -90, 2746039)
	spawnMobile("lok", "stormtrooper_rifleman", 300, -1811.5, 19.0, -3061.8, 0, 0)
	spawnMobile("lok", "stormtrooper_sniper", 300, -1805.4, 19.0, -3062.4, 45, 0)
	spawnMobile("lok", "imperial_warrant_officer_i", 300, -1804.6, 19.0, -3069.3, 90, 0)

	spawnMobile("lok", "stormtrooper_rifleman", 300, -1804.6, 19.0, -3105.9, 90, 0)
	spawnMobile("lok", "stormtrooper_sniper", 300, -1805.4, 19.0, -3111.4, 135, 0)
	spawnMobile("lok", "imperial_army_captain", 300, -1815.2, 19.0, -3109.4, 90, 0)

	spawnMobile("lok", "imperial_first_lieutenant", 300, -2.8, 0, -1.9, 90, 8615437)
	spawnMobile("lok", "imperial_trooper", 300, 4.7, 0, 2.1, 90, 8615435)
	spawnMobile("lok", "imperial_trooper", 300, 0, 0, 1.4, -90, 8615434)

	spawnMobile("lok", "imperial_medic", 300, 4.1, 0, -3.7, 180, 2746314)
	spawnMobile("lok", "imperial_medic", 300, 0, 0, -5.1, -90, 2746312)
	spawnMobile("lok", "stormtrooper_medic", 300, -4.0, 0, -1.8, 0, 2746315)
	spawnMobile("lok", "imperial_medic", 300, 3.5, 0, 2.4, 0, 2746313)
	spawnMobile("lok", "imperial_medic", 300, 4.6, 0, 1.4, 90, 2746313)

	spawnMobile("lok", "imperial_army_captain", 300, -2028.9, 18.9, -3079.7, 180, 0)
	spawnMobile("lok", "stormtrooper_rifleman", 300, -2031.4, 18.9, -3082.2, -90, 0)
	spawnMobile("lok", "stormtrooper_sniper", 300, -2030.6, 18.9, -3088.4, -135, 0)
	spawnMobile("lok", "imperial_master_sergeant", 300, -2025.8, 18.9, -3089.4, 180, 0)

	spawnMobile("lok", "stormtrooper_captain", 300, -2024.6, 19.0, -3049.4, -90, 0)
	spawnMobile("lok", "stormtrooper_rifleman", 300, -2031.4, 19.0, -3046.5, -90, 0)
	spawnMobile("lok", "stormtrooper_sniper", 300, -2031.4, 19.0, -3044.5, -90, 0)
	spawnMobile("lok", "imperial_warrant_officer_i", 300, -2030.6, 19.0, -3039.4, -45, 0)

	spawnMobile("lok", "dark_trooper", 300, 0, 0, -3.0, 180, 8615455)

	spawnMobile("lok", "imperial_major", 300, -4.2, 0, -3.7, 0, 8615451)
	spawnMobile("lok", "stormtrooper", 300, -0.8, 0, -5.4, 0, 8615448)
	spawnMobile("lok", "stormtrooper", 300, 0.8, 0, -5.4, 0, 8615448)

	--main building

	spawnMobile("lok", "commoner", 300, -1902.0, 18.9, -3081.5, -95, 0)
	spawnMobile("lok", "commoner", 300, -1902.0, 18.9, -3084.5, -150, 0)
	spawnMobile("lok", "commoner", 300, -1898.1, 18.9, -3086.8, 45, 0)

	spawnMobile("lok", "stormtrooper_commando", 300, -1894.4, 19.0, -3082.2, -90, 0)
	spawnMobile("lok", "stormtrooper_commando", 300, -1894.4, 19.0, -3086.6, -90, 0)
	spawnMobile("lok", "stormtrooper_colonel", 300, -1892.9, 19.0, -3103.9, 0, 0)
	spawnMobile("lok", "stormtrooper", 300, -1892.9, 19.0, -3093.3, 0, 0)
	spawnMobile("lok", "stormtrooper_bombardier", 300, -1852.3, 19.0, -3092.6, 90, 0)
	spawnMobile("lok", "stormtrooper_bombardier", 300, -1852.3, 19.0, -3097.6, 90, 0)

	spawnMobile("lok", "stormtrooper", 300, 14.6, 7.0, 12.5, -90, 8615430)
	spawnMobile("lok", "stormtrooper", 300, 14.6, 7.0, 10.0, -90, 8615430)
	spawnMobile("lok", "stormtrooper", 300, 14.6, 7.0, 7.5, -90, 8615430)
	spawnMobile("lok", "stormtrooper", 300, 4.4, 7.0, 12.5, 90, 8615430)
	spawnMobile("lok", "stormtrooper", 300, 4.4, 7.0, 10.0, 90, 8615430)
	spawnMobile("lok", "stormtrooper", 300, 4.4, 7.0, 7.5, 90, 8615430)
	spawnMobile("lok", "stormtrooper", 300, 8.2, 7.0, 6.9, 0, 8615430)

	spawnMobile("lok", "stormtrooper_commando", 300, 8.9, 7.0, -7.5, -90, 8615428)
	spawnMobile("lok", "stormtrooper_commando", 300, 8.9, 7.0, -10.5, -90, 8615428)
	spawnMobile("lok", "stormtrooper_colonel", 300, 2.9, 7.0, -15.8, 0, 8615428)
	spawnMobile("lok", "stormtrooper_bombardier", 300, -3.1, 7.0, -7.5, 90, 8615428)
	spawnMobile("lok", "stormtrooper_bombardier", 300, -3.1, 7.0, -10.5, 90, 8615428)
	spawnMobile("lok", "imperial_sergeant", 300, -15.3, 7.0, -14.7, 90, 8615428)

	spawnMobile("lok", "imperial_trooper", 300, -13.1, 7.0, 6.6, 180, 8615429)
	spawnMobile("lok", "imperial_trooper", 300, -9.2, 7.0, 6.6, 180, 8615429)
	spawnMobile("lok", "imperial_first_lieutenant", 300, -10.9, 7.0, 12.6, 0, 8615429)
	spawnMobile("lok", "imperial_staff_corporal", 300, -5.4, 7.0, 12.6, 0, 8615429)
	spawnMobile("lok", "imperial_second_lieutenant", 300, 0.1, 7.0, 12.6, 0, 8615429)

	spawnMobile("lok", "imperial_second_lieutenant", 300, -10.9, 3.4, 2.3, -90, 8615427)
	spawnMobile("lok", "imperial_trooper", 300, -14.9, 1.0, -0.9, 180, 8615427)
	spawnMobile("lok", "imperial_trooper", 300, -16.5, 1.0, -0.9, 180, 8615427)

	spawnMobile("lok", "imperial_lieutenant_colonel", 300, 20.1, 1.0, -5.8, -90, 8615423)
	spawnMobile("lok", "imperial_major", 300, 20.1, 1.0, 1.0, -90, 8615423)
	spawnMobile("lok", "imperial_major_general", 300, 19.0, 1.0, -1.9, -90, 8615423)
	spawnMobile("lok", "imperial_trooper", 300, 10.1, 1.0, -1.9, 0, 8615423)
	spawnMobile("lok", "imperial_trooper", 300, 10.1, 1.0, 2.3, 180, 8615423)

	spawnMobile("lok", "imperial_recruiter", 300, 14.4, 1.0, -21.5, 0, 8615424)

	spawnMobile("lok", "stormtrooper_medic", 60, -3.0, 1.0, -21.1, -120, 8615425)

	spawnMobile("lok", "imperial_warrant_officer_i", 300, -18.1, 1.0, 21.1, 0, 8615422)

	--spawnMobile("lok", "general_otto", 900, 18.7, 1.0, 21.1, -90, 8615421)
		--later on in cu or nge general_otto became the assasination target for han solo's second mission in the rebel themepark. 
		--when attacked he would despawn and several stormtroopers would spawn to 'deal with you'. 
		--every other refrence to general otto indicates that at this time period he is the commanding officer of this base on lok. 
		--he was stationed here by admiral motti to avoid the wrath of darth vader.

	spawnMobile("lok", "imperial_trooper", 300, 5.6, 1.0, -4.2, -90, 8615420)
	spawnMobile("lok", "imperial_trooper", 300, 5.6, 1.0, -7.3, -90, 8615420)
	spawnMobile("lok", "imperial_trooper", 300, 0.0, 1.0, -4.2, -90, 8615420)
	spawnMobile("lok", "imperial_trooper", 300, 0.0, 1.0, -7.3, -90, 8615420)

	--General_Otto & imperial_commander

	local pOtto = spawnMobile("lok", "general_otto", 900, 18.7, 1.0, 21.1, -90, 8615421)
        createObserver(OBJECTDESTRUCTION, "LokImperialOutpostScreenPlay", "notifyOttoDead", pOtto)

end

function LokImperialOutpostScreenPlay:notifyOttoDead(pOtto, pKiller)
     if (readData("lokimperialoutpost:imperial_commander") == 0) then
          local pCommander = spawnMobile("lok", "imperial_commander", 0, 0.0, 2.0, 3.8, 0, 8615420)
			spawnMobile("lok", "dark_trooper", 0, -3.1, 1.0, 0.3, 0, 8615420)
			spawnMobile("lok", "dark_trooper", 0, -1.0, 1.0, 0.3, 0, 8615420)
			spawnMobile("lok", "dark_trooper", 0, 1.0, 1.0, 0.3, 0, 8615420)
			spawnMobile("lok", "dark_trooper", 0, 3.1, 1.0, 0.3, 0, 8615420)
			spawnMobile("lok", "dark_trooper", 0, -1.0, 1.0, 8.1, 90, 8615420)
			spawnMobile("lok", "dark_trooper", 0, -1.0, 1.0, 10.6, 90, 8615420)
			spawnMobile("lok", "dark_trooper", 0, 2.0, 1.0, 8.1, 90, 8615420)
			spawnMobile("lok", "dark_trooper", 0, 2.0, 1.0, 10.6, 90, 8615420)
			spawnMobile("lok", "dark_trooper", 0, 19.1, 1.0, 10.0, 0, 8615420)
			spawnMobile("lok", "dark_trooper", 0, 17.4, 1.0, 8.6, 35, 8615420)
			spawnMobile("lok", "dark_trooper", 0, 19.1, 1.0, 13.2, 0, 8615421)
			spawnMobile("lok", "dark_trooper", 0, 19.1, 1.0, 16.4, 35, 8615421)
			spawnMobile("lok", "dark_trooper", 0, 17.4, 1.0, 14.7, -35, 8615421)
          createObserver(OBJECTDESTRUCTION, "LokImperialOutpostScreenPlay", "notifyCommanderDead", pCommander)
          writeData("lokimperialoutpost:imperial_commander",1)
     end
     
     return 0
end

function LokImperialOutpostScreenPlay:notifyCommanderDead(pCommander, pKiller)
     writeData("lokimperialoutpost:imperial_commander", 0)
     
     return 1
end
