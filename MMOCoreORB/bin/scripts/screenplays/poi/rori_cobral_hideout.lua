CobralHideoutScreenPlay = ScreenPlay:new {
	numberOfActs = 1,

	screenplayName = "CobralHideoutScreenPlay",

lootContainers = {
           6475949,
	   6475950,
	   6475951,
	   6475952,
	   6475953,
	   6475954
        },
        
        lootLevel = 13, 
 
        lootGroups = {
                {
                        groups = {
                                {group = "color_crystals", chance = 100000},
                                {group = "junk", chance = 6300000},
                                {group = "melee_weapons", chance = 1500000},
				{group = "pistols", chance = 500000},
				{group = "carbines", chance = 500000},
				{group = "rifles", chance = 500000},
                                {group = "clothing_attachments", chance = 300000},
                                {group = "armor_attachments", chance = 300000}
                        },
                        lootChance = 8000000
                }                                       
        },
        
        lootContainerRespawn = 1800 -- 30 minutes
}

registerScreenPlay("CobralHideoutScreenPlay", true)

function CobralHideoutScreenPlay:start()
	if (isZoneEnabled("rori")) then
                self:spawnMobiles()
                self:initializeLootContainers()
        end
end

function CobralHideoutScreenPlay:spawnMobiles()
	spawnMobile("rori", "neo_cobral_thug", 300, 5443.0, 87.0, 5029.0, 19, 0)
	spawnMobile("rori", "neo_cobral_thug", 300, 5448.4, 87.0, 5029.2, -15, 0)
	spawnMobile("rori", "neo_cobral_runner", 300, 5444.9, 87.0, 5044.1, 64, 0)
	spawnMobile("rori", "neo_cobral_runner", 300, 5470.9, 86.7, 5031.5, 18, 0)
	spawnMobile("rori", "neo_cobral_runner", 300, 5421.8, 91.6, 5041.4, -52, 0)
	spawnMobile("rori", "neo_cobral_thug", 300, 0.6, 0.3, 2.6, -13, 6055630)
	spawnMobile("rori", "neo_cobral_thug", 300, -0.6, 0.3, 2.4, 9, 6055630)
	spawnMobile("rori", "neo_cobral_thief", 300, -3.6, 0.3, -3.1, 0, 6055630)
	spawnMobile("rori", "neo_cobral_thief", 300, 4.5, 0.3, -4.4, -89, 6055631)
	spawnMobile("rori", "neo_cobral_thief", 300, -5.1, -6.8, 5.3, 94, 6055632)
	spawnMobile("rori", "neo_cobral_thief", 300, 6.1, -13.8, 9.0, -149, 6055635)
	spawnMobile("rori", "neo_cobral_thug", 300, 6.5, -13.8, 7.3, -134, 6055635)
	spawnMobile("rori", "neo_cobral_thug", 300, 4.2, -13.8, 9.4, -176, 6055635)
	spawnMobile("rori", "neo_cobral_hitman", 300, -10.9, -13.8, 7.0, 86, 6055635)
	spawnMobile("rori", "neo_cobral_thief", 300, -8.5, -13.8, 9.9, 132, 6055635)
	spawnMobile("rori", "neo_cobral_thief", 300, -9.1, -13.8, 4.9, 26, 6055635)
	spawnMobile("rori", "neo_cobral_hitman", 300, -1.9, -20.7, 5.5, -110, 6055637)
	spawnMobile("rori", "neo_cobral_hitman", 300, 4.8, -20.7, 5.0, 83, 6055637)
	spawnMobile("rori", "neo_cobral_assassin", 300, 1.3, -20.7, 11.5, 176, 6055637)
	spawnMobile("rori", "neo_cobral_assassin", 300,-2.5, -20.8, 22.8, 157, 6055638)
	spawnMobile("rori", "neo_cobral_assassin", 300,5.3, -20.8, 22.2, -162, 6055638)
	spawnMobile("rori", "neo_cobral_hitman", 300, 5.2, -20.8, 31.8, -168, 6055638)
	spawnMobile("rori", "neo_cobral_hitman", 300, -2.1, -20.8, 32.2, 155, 6055638)
	spawnMobile("rori", "neo_cobral_boss", 300, 1.6, -20.8, 31.5, 179, 6055638)
end
