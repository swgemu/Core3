MaulerStrongholdScreenPlay = ScreenPlay:new {
	numberOfActs = 1,
	
	screenplayName = "MaulerStrongholdScreenPlay",
	
	lootContainers = {
		625318,
		2705435
	},
	
	lootLevel = 26,	

	lootGroups = {
		{
			groups = {
				{group = "color_crystals", chance = 160000},
				{group = "junk", chance = 8600000},
				{group = "rifles", chance = 500000},
				{group = "pistols", chance = 500000},
				{group = "clothing_attachments", chance = 300000},
				{group = "armor_attachments", chance = 300000}
			},
			lootChance = 8000000
		}					
	},
	
	lootContainerRespawn = 1800 -- 30 minutes
}

registerScreenPlay("MaulerStrongholdScreenPlay", true)

function MaulerStrongholdScreenPlay:start()
	if (isZoneEnabled("naboo")) then
		self:spawnMobiles()
		self:initializeLootContainers()
	end
end

function MaulerStrongholdScreenPlay:spawnMobiles()
	spawnMobile("naboo", "mauler",300,2887.8,77.7,1190.7,-11,0)
	spawnMobile("naboo", "mauler",300,2939.1,73.2,1195.3,7,0)
	spawnMobile("naboo", "mauler",300,3020.6,76.3,1121,-8,0)
	spawnMobile("naboo", "mauler",300,3022.7,75.8,1120.5,44,0)
	spawnMobile("naboo", "mauler",300,2960.2,94.1,1082.1,15,0)
	spawnMobile("naboo", "mauler",300,2903.8,117.8,1036.7,-6,0)
	spawnMobile("naboo", "mauler",300,2901.6,118,1035.9,-9,0)
	spawnMobile("naboo", "mauler",300,2846.6,97.3,1068.2,6,0)
	spawnMobile("naboo", "mauler",300,2845.3,97.5,1068,-3,0)
	spawnMobile("naboo", "mauler",300,2778.1,77.6,1143.3,-11,0)
	spawnMobile("naboo", "mauler",300,2780.1,77.4,1143.3,-94,0)
	spawnMobile("naboo", "mauler",300,2891.5,94,1117.2,7,0)
	spawnMobile("naboo", "mauler",300,2890.7,94,1105.2,2,0)
	spawnMobile("naboo", "mauler",300,2891.5,94,1104.5,28,0)
	spawnMobile("naboo", "mauler",300,2901.8,94,1119.7,-146,0)
	
	spawnMobile("naboo", "mauler_acolyte",300,2941.1,72.8,1195.2,-4,0)
	spawnMobile("naboo", "mauler_acolyte",300,2910.5,94,1130.1,47,0)
	
	spawnMobile("naboo", "mauler_apprentice",300,2928,94,1110.5,-90,0)
	spawnMobile("naboo", "mauler_apprentice",300,2889.7,77.8,1190,0,0)
	
	spawnMobile("naboo", "mauler_lord",300,2900.4,94,1128.9,108,0)
	
	spawnMobile("naboo", "mauler_master",300,2918.2,95.5,1117.8,-1,0)
	spawnMobile("naboo", "mauler_master",300,2958.5,94.1,1081,0,0)
	
	spawnMobile("naboo", "mauler_veermok",300,2924.5,94,1110.4,5,0)
end
