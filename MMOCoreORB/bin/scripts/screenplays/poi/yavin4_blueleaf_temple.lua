BlueleafTempleScreenPlay = ScreenPlay:new {
	numberOfActs = 1,
	
	screenplayName = "BlueleafTempleScreenPlay",

	lootContainers = {
		9145383,
		9145384,
		9765486,		
		9765485
	},
	
	lootLevel = 26,	

	lootGroups = {
		{
			groups = {
				{group = "color_crystals", chance = 3100000},
				{group = "junk", chance = 3500000},
				{group = "heavy_weapons_consumable", chance = 600000},
				{group = "rifles", chance = 600000},
				{group = "carbines", chance = 600000},
				{group = "pistols", chance = 600000},
				{group = "clothing_attachments", chance = 500000},
				{group = "armor_attachments", chance = 500000}
			},
			lootChance = 8000000
		}					
	},
	
	lootContainerRespawn = 1800 -- 30 minutes
}

registerScreenPlay("BlueleafTempleScreenPlay", true)

function BlueleafTempleScreenPlay:start()
	if (isZoneEnabled("yavin4")) then
		self:spawnMobiles()
		self:initializeLootContainers()
	end
end

function BlueleafTempleScreenPlay:spawnMobiles()
	-- Outside Temple	
	spawnMobile("yavin4", "kliknik_dark_hunter",600,-895.6,84.8,-2059,-139,0)
	spawnMobile("yavin4", "kliknik_dark_hunter",600,-896.2,84.8,-2064.1,42,0)
	spawnMobile("yavin4", "kliknik_dark_hunter",600,-892.3,84.8,-2062.4,-109,0)
	spawnMobile("yavin4", "kliknik_dark_hunter",600,-884.4,84.8,-2026.1,-96,0)
	spawnMobile("yavin4", "kliknik_dark_hunter",600,-888.5,84.8,-2023.3,155,0)
	spawnMobile("yavin4", "kliknik_dark_hunter",600,-888.6,84.8,-2028.8,35,0)
	
	-- Inside Temple
	spawnMobile("yavin4", "kliknik_dark_defender",600,-9,-37.3,-9,48,468319)
	spawnMobile("yavin4", "kliknik_dark_defender",600,-10.5,-37.3,4.2,111,468319)
	spawnMobile("yavin4", "kliknik_dark_defender",600,6.6,-37.3,12.8,-149,468319)
	spawnMobile("yavin4", "kliknik_dark_defender",600,10.2,-37.3,4.8,-110,468319)
	spawnMobile("yavin4", "kliknik_dark_defender",600,10.9,-37.3,-3.9,-69,468319)
	spawnMobile("yavin4", "kliknik_dark_defender",600,-12.1,-37.3,18.2,74,468319)
	
	spawnMobile("yavin4", "kliknik_dark_queen",600,-0.6,-37.3,-28.3,-19,468319)
	
	spawnMobile("yavin4", "kliknik_dark_worker",600,-24,-1.3,10.3,93,468319)
	spawnMobile("yavin4", "kliknik_dark_worker",600,-16.4,-1.3,-21,49,468319)
	spawnMobile("yavin4", "kliknik_dark_worker",600,12.1,-1.3,-23.4,21,468319)
	spawnMobile("yavin4", "kliknik_dark_worker",600,23.4,-1.3,11,-77,468319)
	
	spawnMobile("yavin4", "kliknik_dark_warrior",600,12.4,-1.3,32.4,-93,468318)
	spawnMobile("yavin4", "kliknik_dark_warrior",600,-12.8,-1.3,32,93,468318)
end
