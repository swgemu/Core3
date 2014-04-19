WoolamanderTempleScreenPlay = ScreenPlay:new {
	numberOfActs = 1,
	
	screenplayName = "WoolamanderTempleScreenPlay",
	
	lootContainers = {
		568340,
		468343,
		468334,
		468338
	},
	
	lootLevel = 26,	

	lootGroups = {
		{
			groups = {
				{group = "color_crystals", chance = 100000},
				{group = "junk", chance = 8600000},
				{group = "melee_weapons", chance = 1000000},
				{group = "clothing_attachments", chance = 100000},
				{group = "armor_attachments", chance = 200000}
			},
			lootChance = 8000000
		}					
	},
	
	lootContainerRespawn = 1800 -- 30 minutes
}

registerScreenPlay("WoolamanderTempleScreenPlay", true)

function WoolamanderTempleScreenPlay:start()
	if (isZoneEnabled("yavin4")) then
		self:spawnMobiles()
		self:initializeLootContainers()
	end
end

function WoolamanderTempleScreenPlay:spawnMobiles()
	spawnMobile("yavin4", "woolamander_gatherer",300,-19,2,1.4,79,3705355)
	spawnMobile("yavin4", "woolamander_gatherer",300,-13.5,2,-4.7,30,3705355)
	spawnMobile("yavin4", "woolamander_gatherer",300,-8.2,2,-9.2,91,3705355)
	spawnMobile("yavin4", "woolamander_gatherer",300,8.2,2,-9.4,-98,3705355)
	spawnMobile("yavin4", "woolamander_gatherer",300,13.5,2,-4.7,-34,3705355)
	spawnMobile("yavin4", "woolamander_gatherer",300,18.5,2,1,-91,3705355)
	spawnMobile("yavin4", "woolamander_gatherer",300,62.4,2,18.5,137,3705362)
	spawnMobile("yavin4", "woolamander_gatherer",300,62.4,2,-7.6,43,3705362)
	
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

	spawnMobile("yavin4", "woolamander_gatherer",300,431.4,81.0,-684.6,143,0)
	spawnMobile("yavin4", "woolamander_gatherer",300,435.1,81.0,-693.3,48,0)
	spawnMobile("yavin4", "woolamander_gatherer",300,438.0,81.0,-688.6,-69,0)
	spawnMobile("yavin4", "woolamander_gatherer",300,484.0,81.0,-607.5,-108,0)
	spawnMobile("yavin4", "woolamander_gatherer",300,487.8,81.0,-624.7,131,0)
	spawnMobile("yavin4", "woolamander_gatherer",300,534.2,81.0,-660.7,-143,0)
	spawnMobile("yavin4", "woolamander_gatherer",300,540.0,81.0,-665.9,-173,0)
	spawnMobile("yavin4", "woolamander_harvester",300,537.6,81.0,-680.1,135,0)
	spawnMobile("yavin4", "woolamander_harvester",300,545.2,81.0,-686.9,-45,0)

end
