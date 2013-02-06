TalusKahmurraBiogenticResearchStationScreenPlay = ScreenPlay:new {
	numberOfActs = 1, screenplayName = "TalusKahmurraBiogenticResearchStationScreenPlay",


	lootContainers = {
           6075909,
	   6075908,
	   6075907,
	   6075906,
	   6075905,
	   6075904
	 },
        
        lootLevel = 40, 
 
        lootGroups = {
                {
                        groups = {
                                {group = "color_crystals", chance = 160000},
                                {group = "junk", chance = 8240000},
                                {group = "melee_weapons", chance = 1000000},
                                {group = "clothing_attachments", chance = 300000},
                                {group = "armor_attachments", chance = 300000}
                        },
                        lootChance = 8000000
                }                                       
        },
        
        lootContainerRespawn = 1800
}
 
registerScreenPlay("TalusKahmurraBiogenticResearchStationScreenPlay", true)
 
function TalusKahmurraBiogenticResearchStationScreenPlay:start()
	if (isZoneEnabled("talus")) then
                self:spawnMobiles()
                self:initializeLootContainers()
        end
end

function TalusKahmurraBiogenticResearchStationScreenPlay:spawnMobiles()

	spawnMobile("talus", "rabid_mutant_kahmurra", 300, -5.1, -13.8, -14.9, 80, 4795365)
	spawnMobile("talus", "mutated_kahmurra", 300, 0.6, -13.8, -9.6, -7, 4795365)
	spawnMobile("talus", "mutated_kahmurra", 300, 3.7, -13.8, -2.2, 12, 4795365)
	spawnMobile("talus", "mutated_kahmurra", 300, -6.1, -13.8, -8.6, -118, 4795365)
	spawnMobile("talus", "frenzied_kahmurra", 300, 5.8, -6.8, -1.8, 160, 4795363)
	spawnMobile("talus", "genetically_enchanced_kahmurra", 300, 7.8, -6.8, -14.1, -79, 4795362)
	spawnMobile("talus", "genetically_enchanced_kahmurra", 300, 1.3, -6.8, -13.1, -1, 4795362)
	spawnMobile("talus", "genetically_enchanced_kahmurra", 300, -6.0, -6.8, -14.1, 32, 4795362)
	spawnMobile("talus", "berserk_kahmurra", 300, -2.7, -6.8, -6.2, 124, 4795361)
	spawnMobile("talus", "berserk_kahmurra", 300, -6.8, -6.8, -7.5, -120, 4795361)
	spawnMobile("talus", "berserk_kahmurra", 300, -4.5, -6.8, -0.3, 0, 4795361)
	spawnMobile("talus", "mutated_kahmurra", 300, 2.4, 0.3, -3.8, -93, 4795359)
	spawnMobile("talus", "mutated_kahmurra", 300, 0.2, 0.3, 7.6, -1, 4795357)
	spawnMobile("talus", "kahmurra", 300, -4796.3, 16.6, -4753.1, 122, 0)
	spawnMobile("talus", "kahmurra", 300, -4780.3, 17.2, -4737.9, 41, 0)
end
