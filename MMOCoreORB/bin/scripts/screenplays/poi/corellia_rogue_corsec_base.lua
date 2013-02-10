CorsecBaseScreenPlay = ScreenPlay:new {
	numberOfActs = 1,
	
	screenplayName = "CorsecBaseScreenPlay",
	
	lootContainers = {
		6575944,
		6575945
		
	},
	
	lootLevel = 26,	

	lootGroups = {
		{
			groups = {
				{group = "color_crystals", chance = 200000},
				{group = "junk", chance = 8600000},
				{group = "rifles", chance = 500000},
				{group = "pistols", chance = 500000},
				{group = "clothing_attachments", chance = 100000},
				{group = "armor_attachments", chance = 100000}
			},
			lootChance = 8000000
		}					
	},
	
	lootContainerRespawn = 1800 -- 30 minutes
}

registerScreenPlay("CorsecBaseScreenPlay", true)

function CorsecBaseScreenPlay:start()
	if (isZoneEnabled("corellia")) then
		self:spawnMobiles()
		self:initializeLootContainers()
	end
end

function CorsecBaseScreenPlay:spawnMobiles()
	spawnMobile("corellia", "rogue_corsec_trooper",300,4.5,-20.8,30.9,-93,1855730)
	spawnMobile("corellia", "rogue_corsec_trooper",300,-0.9,-20.8,31.1,89,1855730)
	spawnMobile("corellia", "rogue_corsec_trooper",300,-7.1,-13.8,7.1,90,1855727)
	spawnMobile("corellia", "rogue_corsec_trooper",300,0.2,-13.8,7.9,-92,1855727)
	spawnMobile("corellia", "rogue_corsec_trooper",300,-4.1,0.2,1.8,-93,1855742)
	spawnMobile("corellia", "rogue_corsec_trooper",300,-10,0.2,5.8,137,1855742)
	spawnMobile("corellia", "rogue_corsec_trooper",300,5207,5,1515.2,76,0)
	spawnMobile("corellia", "rogue_corsec_trooper",300,5203,5,1515.7,-34,0)
		
	spawnMobile("corellia", "renegade_corsec_trooper",300,5239.7,5,1532,169,0)
	spawnMobile("corellia", "renegade_corsec_trooper",300,5242.2,5,1534.8,104,0)
	spawnMobile("corellia", "renegade_corsec_trooper",300,-7.1,0.2,5.9,114,1855738)
	spawnMobile("corellia", "renegade_corsec_trooper",300,2.5,0.2,-1.4,-50,1855738)
	spawnMobile("corellia", "renegade_corsec_trooper",300,10.6,0.2,1.3,1,1855738)
	spawnMobile("corellia", "renegade_corsec_trooper",300,11.2,0.2,5.3,-171,1855738)
	spawnMobile("corellia", "renegade_corsec_trooper",300,1.6,-20.8,18.9,0,1855730)
		
	spawnMobile("corellia", "corsec_deserter",300,6.8,0.2,7.4,94,1855746)
	spawnMobile("corellia", "corsec_deserter",300,-11.3,0.2,-5.7,-179,1855746)
	spawnMobile("corellia", "corsec_deserter",300,-10.1,0.2,-1.3,95,1855742)
	spawnMobile("corellia", "corsec_deserter",300,5224.9,5,1612.7,38,0)
	spawnMobile("corellia", "corsec_deserter",300,5226.9,5,1616.6,-159,0)
	spawnMobile("corellia", "corsec_deserter",300,5229.2,5,1613.3,-85,0)
	spawnMobile("corellia", "corsec_deserter",300,-3.7,0.3,-3.7,4,1855722)
end
