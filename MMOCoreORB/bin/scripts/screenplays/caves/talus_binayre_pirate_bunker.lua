TalusBinayrePirateBunkerScreenPlay = ScreenPlay:new {
	numberOfActs = 1, screenplayName = "TalusBinayrePirateBunkerScreenPlay",


lootContainers = {
           8095746,
	   8095745,
	   8095744,
	   178364,
	   8095603,
	   
	  
        },
        
        lootLevel = 20, 
 
        lootGroups = {
                {
                        groups = {
                                {group = "color_crystals", chance = 160000},
                                {group = "junk", chance = 8600000},
                                {group = "melee_weapons", chance = 500000},
				{group = "ranged_weapons", chance = 500000},
                                {group = "clothing_attachments", chance = 300000},
                                {group = "armor_attachments", chance = 300000}
                        },
                        lootChance = 8000000
                }                                       
        },
        
        lootContainerRespawn = 1800
}
 
registerScreenPlay("TalusBinayrePirateBunkerScreenPlay", true)
 
function TalusBinayrePirateBunkerScreenPlay:start()
	if (isZoneEnabled("talus")) then
                self:spawnMobiles()
                self:initializeLootContainers()
        end
end

function TalusBinayrePirateBunkerScreenPlay:spawnMobiles()

	spawnMobile("talus", "binayre_chief", 300, 12.6, -11.5, -20.7, 162, 6075880)
	spawnMobile("talus", "binayre_ruffian", 300, 19.2, -11.5, -20.3, -27, 6075880)
	spawnMobile("talus", "binayre_smuggler", 300, 12.8, -13.8, -15.7, 179, 6075880)
	spawnMobile("talus", "binayre_ruffian", 300, 17.0, -13.8, -4.9, -90, 6075880)
	spawnMobile("talus", "binayre_swindler", 300, 14.1, -13.8, 3.8, -60, 6075879)
	spawnMobile("talus", "binayre_smuggler", 300, 16.7, -13.8, 7.6, 42, 6075879)
	spawnMobile("talus", "binayre_pirate", 300, 14.4, -13.8, 14.3, -80, 6075879)
	spawnMobile("talus", "binayre_ruffian", 300, 8.4, -13.8, 11.8, -44, 6075878)	
	spawnMobile("talus", "binayre_ruffian", 300, 5.7, -13.8, 12.2, -90, 6075878)	
	spawnMobile("talus", "binayre_scalawag", 300, -3.3, -13.8, 9.2, 178, 6075878)	
	spawnMobile("talus", "binayre_ruffian", 300, -4.9, -13.7, 1.6, 165, 6075877)	
	spawnMobile("talus", "binayre_pirate", 300, -3.6, -13.7, -1.7, -31, 6075877)
	spawnMobile("talus", "binayre_ruffian", 300, -2.4, -13.7, -7.9, 143, 6075877)
	spawnMobile("talus", "binayre_pirate", 300, -1.7, -13.7, -10.6, -7, 6075877)
	spawnMobile("talus", "binayre_scalawag", 300, 6.2, -6.8, -7.2, -15, 6075875)
	spawnMobile("talus", "binayre_smuggler", 300, 3.0, -6.8, -6.3, 25, 6075875)
	spawnMobile("talus", "binayre_scalawag", 300, 2.5, -6.8, -2.8, 141, 6075875)
	spawnMobile("talus", "binayre_scalawag", 300, 6.4, -6.8, -3.0, -160, 6075875)
	spawnMobile("talus", "binayre_hooligan", 300, -2.4, 0.3, -3.5, -50, 6075873)
	spawnMobile("talus", "binayre_pirate", 300, 0.5, 0.3, 3.5, -16, 6075872)
	spawnMobile("talus", "binayre_hooligan", 300, 5567.8, 102.0, -4073.0, -128, 0)
	spawnMobile("talus", "binayre_hooligan", 300, 5567.1, 102.0, -4085.6, -51, 0)

end
