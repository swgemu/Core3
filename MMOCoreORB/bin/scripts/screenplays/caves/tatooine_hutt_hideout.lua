HuttHideoutScreenPlay = ScreenPlay:new {
	numberOfActs = 1,
	
	screenplayName = "HuttHideoutScreenPlay",
	
	lootContainers = {
		134411,
		8496263,
		8496262,
		8496261,
		8496260
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

registerScreenPlay("HuttHideoutScreenPlay", true)

function HuttHideoutScreenPlay:start()
	if (isZoneEnabled("tatooine")) then
		self:spawnMobiles()
		self:initializeLootContainers()
	end
end

function HuttHideoutScreenPlay:spawnMobiles()
	spawnMobile("tatooine", "jabba_enforcer", 300, -3.5, -12.7, -6.7, 24, 4235585)
	spawnMobile("tatooine", "jabba_henchman", 300, 1.1, -14.4, -9.3, 15, 4235585)
	
	spawnMobile("tatooine", "jabba_compound_guard", 300, -12.1, -32.2, -34, 19, 4235586)
	
	spawnMobile("tatooine", "jabba_enforcer", 300, -10.5, -40.4, -81.3, -178, 4235587)
	spawnMobile("tatooine", "jabba_henchman", 300, 5.8, -40.9, -79.6, -37, 4235587)
	spawnMobile("tatooine", "jabba_enforcer", 300, 14.5, -40.5, -74.2, -131, 4235587)
	spawnMobile("tatooine", "jabba_enforcer", 300, 20, -39.6, -77.9, -50, 4235587)
	spawnMobile("tatooine", "jabba_henchman", 300, 10.7, -41.1, -60.3, -124, 4235587)
	
	spawnMobile("tatooine", "jabba_henchman", 300, 47, -46.7, -50.8, -163, 4235588)
	spawnMobile("tatooine", "jabba_henchman", 300, 50.4, -46.8, -58.6, -19, 4235588)
	spawnMobile("tatooine", "jabba_henchman", 300, 51.6, -46, -91.6, -126, 4235588)
	spawnMobile("tatooine", "jabba_enforcer", 300, 47.1, -46.2, -96.3, 46, 4235588)
	spawnMobile("tatooine", "jabba_compound_guard", 300, 44.9, -46.2, -102.8, -41, 4235588)
	
	spawnMobile("tatooine", "jabba_henchman", 300, 13.9, -45, -121.1, 30, 4235589)
	spawnMobile("tatooine", "jabba_enforcer", 300, 1.5, -45, -141.6, 117, 4235589)
	spawnMobile("tatooine", "jabba_henchman", 300, -10, -45.6, -148, 26, 4235589)
	spawnMobile("tatooine", "jabba_henchman", 300, -12.4, -45, -130.8, 125, 4235589)
	spawnMobile("tatooine", "jabba_henchman", 300, 58.8, -47.1, -124.6, -21, 4235589)
	spawnMobile("tatooine", "jabba_henchman", 300, 73.5, -52.9, -144.7, -178, 4235589)
	spawnMobile("tatooine", "jabba_enforcer", 300, 72.5, -54.4, -151.6, -20, 4235589)
	spawnMobile("tatooine", "jabba_enforcer", 300, 38.2, -55.7, -155.4, -78, 4235589)
	spawnMobile("tatooine", "jabba_henchman", 300, 36.9, -56.1, -157.2, -53, 4235589)
	spawnMobile("tatooine", "jabba_henchman", 300, 67.5, -57.3, -176.7, 62, 4235589)
	spawnMobile("tatooine", "jabba_enforcer", 300, 58.6, -57.7, -185.3, -70, 4235589)
	spawnMobile("tatooine", "jabba_henchman", 300, 53, -57, -185.3, 59, 4235589)
	spawnMobile("tatooine", "jabba_compound_guard", 300, 58.8, -56.4, -159.5, -60, 4235589)
	spawnMobile("tatooine", "jabba_compound_guard", 300, 53.3, -56.6, -160.2, 45, 4235589)
	
	spawnMobile("tatooine", "jabba_compound_guard", 300, 6, -63.9, -181.8, 90, 4235590)
	spawnMobile("tatooine", "jabba_compound_guard", 300, -8.1, -65.1, -201.3, -10, 4235590)
	spawnMobile("tatooine", "jabba_compound_guard", 300, -37.5, -67, -182.8, 91, 4235590)
	
	spawnMobile("tatooine", "jabba_henchman", 300, -18.7, -65.5, -210.3, -152, 4235591)
	spawnMobile("tatooine", "jabba_compound_guard", 300, -22.5, -64.6, -220.2, -131, 4235591)
	spawnMobile("tatooine", "jabba_henchman", 300, -17.6, -65.4, -216.8, -7, 4235591)
	spawnMobile("tatooine", "jabba_henchman", 300, -4.8, -64.2, -231.5, 178, 4235591)
	spawnMobile("tatooine", "jabba_assassin", 300, -1.3, -64.2, -238.5, 88, 4235591)
	spawnMobile("tatooine", "jabba_compound_guard", 300, -22.4, -65, -249.8, -174, 4235591)
	spawnMobile("tatooine", "jabba_henchman", 300, -19.3, -62.6, -261.6, 43, 4235591)
	spawnMobile("tatooine", "jabba_assassin", 300, -10.6, -63.3, -261.2, -77, 4235591)
	
	spawnMobile("tatooine", "jabba_henchman", 300, -57.1, -70.2, -193, -70, 4235592)
	spawnMobile("tatooine", "jabba_compound_guard", 300, -71.8, -68.6, -182.3, 99, 4235592)
	spawnMobile("tatooine", "jabba_henchman", 300, -59.3, -69.8, -170.9, -53, 4235592)
	spawnMobile("tatooine", "jabba_enforcer", 300, -71.5, -70, -166.7, 141, 4235592)
	spawnMobile("tatooine", "jabba_assassin", 300, -98.3, -72.4, -174.9, 72, 4235592)
	spawnMobile("tatooine", "jabba_henchman", 300, -112.2, -69.1, -119.7, 84, 4235592)
	spawnMobile("tatooine", "jabba_enforcer", 300, -106.1, -68.6, -112.2, -76, 4235592)
	spawnMobile("tatooine", "jabba_assassin", 300, -84.2, -70.3, -129.7, 83, 4235592)
	spawnMobile("tatooine", "jabba_enforcer", 300, -94.9, -102.6, -137.2, 154, 4235592)
	spawnMobile("tatooine", "jabba_enforcer", 300, -95.6, -102.1, -140.6, 0, 4235592)
	
	spawnMobile("tatooine", "jabba_henchman", 300, -51.4, -68.9, -95.4, 135, 4235593)
	spawnMobile("tatooine", "jabba_enforcer", 300, -47.6, -69.3, -95.4, -133, 4235593)
	spawnMobile("tatooine", "jabba_enforcer", 300, -46.3, -69.3, -99, -52, 4235593)
	spawnMobile("tatooine", "jabba_compound_guard", 300, -59.4, -70.1, -88, -179, 4235593)
	spawnMobile("tatooine", "jabba_henchman", 300, -69.4, -68.5, -101.7, 110, 4235593)
	spawnMobile("tatooine", "jabba_compound_guard", 300, -65.6, -68.3, -103.1, -74, 4235593)
	spawnMobile("tatooine", "jabba_assassin", 300, -8.6, -68.6, -97.1, -162, 4235593)
	
	spawnMobile("tatooine", "jabba_compound_guard", 300, -32.1, -80.2, -143.5, 80, 4235594)
	spawnMobile("tatooine", "jabba_henchman", 300, -19.7, -79.8, -146.9, -59, 4235594)
	spawnMobile("tatooine", "jabba_henchman", 300, -21.2, -79.6, -143.8, 160, 4235594)
	
	spawnMobile("tatooine", "jabba_compound_guard", 300, -78.6, -100.8, -125.9, -124, 4235595)
	spawnMobile("tatooine", "jabba_assassin", 300, -83.8, -100.6, -106.6, -1, 4235595)
	spawnMobile("tatooine", "jabba_enforcer", 300, -86.4, -100.5, -103.6, 123, 4235595)
	spawnMobile("tatooine", "jabba_assassin", 300, -100.4, -99.9, -114.2, 162, 4235595)
	spawnMobile("tatooine", "jabba_enforcer", 300, -98.3, -100, -105.2, -43, 4235595)
end
