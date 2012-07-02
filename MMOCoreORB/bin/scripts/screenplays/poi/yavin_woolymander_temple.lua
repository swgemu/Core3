WoolymanderTempleScreenPlay = ScreenPlay:new {
	numberOfActs = 1,
	
	screenplayName = "WoolymanderTempleScreenPlay",
	
	lootContainers = {
	   568340,
	   468343,
	   468334,
	   468338
	},
	
	lootLevel = 45,	

	lootGroups = {
		{
			groups = {
				{group = "color_crystals", chance = 160000},
				{group = "junk", chance = 8600000},
				{group = "melee_weapons", chance = 500000},
				{group = "harrower_bone", chance = 500000},
				{group = "clothing_attachments", chance = 300000},
				{group = "armor_attachments", chance = 300000}
			},
			lootChance = 8000000
		}					
	},
	
	lootContainerRespawn = 1800 -- 30 minutes
}

registerScreenPlay("WoolymanderTempleScreenPlay", true)

function WoolymanderTempleScreenPlay:start()
	if (isZoneEnabled("yavin4")) then
		self:spawnMobiles()
		self:initializeLootContainers()
	end
end

function WoolymanderTempleScreenPlay:spawnMobiles()
    
spawnMobile("yavin4", "woolamander_gatherer",240,-19,2,1.4,79,3705355)
spawnMobile("yavin4", "woolamander_gatherer",240,-13.5,2,-4.7,30,3705355)
spawnMobile("yavin4", "woolamander_gatherer",240,-8.2,2,-9.2,91,3705355)
spawnMobile("yavin4", "woolamander_gatherer",240,8.2,2,-9.4,-98,3705355)
spawnMobile("yavin4", "woolamander_gatherer",240,13.5,2,-4.7,-34,3705355)
spawnMobile("yavin4", "woolamander_gatherer",240,18.5,2,1,-91,3705355)
spawnMobile("yavin4", "woolamander_gatherer",240,62.4,2,18.5,137,3705362)
spawnMobile("yavin4", "woolamander_gatherer",240,62.4,2,-7.6,43,3705362)

spawnMobile("yavin4", "woolamander_harrower",900,-83.6,2,22.5,-179,3705359)
spawnMobile("yavin4", "woolamander_harrower",900,-83.6,2,-12.5,-2,3705359)

spawnMobile("yavin4", "woolamander_harvester",480,-73,2,-12,0,3705359)
spawnMobile("yavin4", "woolamander_harvester",480,-73,2,22.1,178,3705359)
spawnMobile("yavin4", "woolamander_harvester",480,-60.5,2,22,178,3705359)
spawnMobile("yavin4", "woolamander_harvester",480,-60.5,2,-12,0,3705359)
spawnMobile("yavin4", "woolamander_harvester",480,-46,2,-13.4,-3,3705359)
spawnMobile("yavin4", "woolamander_harvester",480,-46,2,23.2,175,3705359)
spawnMobile("yavin4", "woolamander_harvester",480,76.2,2,-9,0,3705362)
spawnMobile("yavin4", "woolamander_harvester",480,76.2,2,17.3,179,3705362)

end