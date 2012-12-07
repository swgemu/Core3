TalusAakuanCaveScreenPlay = ScreenPlay:new {
       numberOfActs = 1, screenplayName = "TalusAakuanCaveScreenPlay",

        lootContainers = {
           6075899,
           6075900,
           6075901,
           6075902,
	   6075903
        },
        
        lootLevel = 25, 
 
        lootGroups = {
                {
                        groups = {
                                {group = "color_crystals", chance = 160000},
                                {group = "junk", chance = 8600000},
                                {group = "melee_weapons", chance = 1000000},
                                {group = "clothing_attachments", chance = 300000},
                                {group = "armor_attachments", chance = 300000}
                        },
                        lootChance = 8000000
                }                                       
        },
        
        lootContainerRespawn = 1800
}
 
registerScreenPlay("TalusAakuanCaveScreenPlay", true)
 
function TalusAakuanCaveScreenPlay:start()
	if (isZoneEnabled("talus")) then
                self:spawnMobiles()
                self:initializeLootContainers()
        end
end

 
function TalusAakuanCaveScreenPlay:spawnMobiles()    
       spawnMobile("talus", "aakuan_follower", 300, 5932.6, 39.2, 4646.6, -73, 0)
       spawnMobile("talus", "aakuan_follower", 300, 5926.5, 40.0, 4647.9, 89, 0)
       spawnMobile("talus", "aakuan_steward", 300, 5928.6, 40.6, 4650.5, -164, 0)
       spawnMobile("talus", "aakuan_sentinel", 300, 24.6, -28.6, -11.5, -50, 4255652)
       spawnMobile("talus", "aakuan_keeper", 300, 24.6, -27.4, -7.5, -128, 4255652)
       spawnMobile("talus", "aakuan_sentinel", 300, 21.9, -41.5, -70.6, 39, 4255653)
       spawnMobile("talus", "aakuan_keeper", 300, 23.1, -42.3, -64.7, -167, 4255653)
       spawnMobile("talus", "aakuan_keeper", 300, 26.0, -42.9, -69.1, -100, 4255653)
       spawnMobile("talus", "aakuan_sentinel", 300, 54.7, -48.6, -58.7, 124, 4255653)
       spawnMobile("talus", "aakuan_follower", 300, 51.1, -49.0, -54.8, 164, 4255653)
       spawnMobile("talus", "aakuan_follower", 300, 49.4, -48.6, -59.1, 69, 4255653)
       spawnMobile("talus", "aakuan_follower", 300, 48.8, -47.6, -71.5, -11, 4255653)
       spawnMobile("talus", "aakuan_follower", 300, 54.7, -47.3, -69.8, -43, 4255653)
       spawnMobile("talus", "aakuan_guardian", 300, 40.6, -46.2, -10.3, 128, 4255653)
       spawnMobile("talus", "aakuan_guardian", 300, 46.8, -46.8, -5.2, -175, 4255653)
       spawnMobile("talus", "aakuan_follower", 300, 42.6, -46.7, -7.0, 142, 4255653)
       spawnMobile("talus", "aakuan_anarchist", 300, 56.8, -68.5, -38.2, 82, 4255653)
       spawnMobile("talus", "aakuan_steward", 300, 95.9, -46.4, -121.1, 171, 4255656)
       spawnMobile("talus", "aakuan_steward", 300, 90.3, -46.0, -120.6, 165, 4255656)
       spawnMobile("talus", "aakuan_warder", 300, 88.9, -46.6, -109.7, -87, 4255656)
       spawnMobile("talus", "aakuan_warder", 300, 81.0, -77.4, -93.4, -72, 4255656)
       spawnMobile("talus", "aakuan_spice_guard", 300, 89.2, -61.2, -8.5, 42, 4255654)
       spawnMobile("talus", "aakuan_steward", 300, 77.1, -60.9, -7.6, 82, 4255654)
       spawnMobile("talus", "aakuan_steward", 300, 89.8, -66.9, -38.0, -11, 4255654)
       spawnMobile("talus", "aakuan_defender", 300, 89.2, -76.3, -58.7, -34, 4255655)
       spawnMobile("talus", "aakuan_steward", 300, 96.4, -75.4, -64.2, 85, 4255655)
       spawnMobile("talus", "aakuan_defender", 300, 88.5, -76.6, -70.6, -34, 4255655)
       spawnMobile("talus", "aakuan_guardian", 300, 56.9, -70.0, -121.8, -10, 4255657)
       spawnMobile("talus", "aakuan_warder", 300, 86.8, -66.9, -136.6, -113, 4255658)
       spawnMobile("talus", "aakuan_sentinel", 300, 83.9, -66.1, -141.8, -143, 4255658)
       spawnMobile("talus", "aakuan_guardian", 300, 116.3, -66.8, -91.1, -160, 4255659)
       spawnMobile("talus", "aakuan_spice_guard", 300, 110.8, -66.7, -92.4, -94, 4255659)
       spawnMobile("talus", "aakuan_warder", 300, 129.2, -66.7, -109.2, -87, 4255659)
       spawnMobile("talus", "aakuan_spice_guard", 300, 144.9, -66.2, -86.5, -125, 4255659)
       spawnMobile("talus", "aakuan_spice_guard", 300, 139.6, -66.7, -86.5, -156, 4255659)
       spawnMobile("talus", "aakuan_anarchist", 300, 153.7, -65.9, -129.6, -47, 4255659)
       spawnMobile("talus", "aakuan_champion", 300, 189.3, -66.1, -105.5, -72, 4255660)
       spawnMobile("talus", "aakuari_assassin", 300, 190.0, -66.3, -97.9, -93, 4255660)
       spawnMobile("talus", "aakuan_warder", 300, 165.0, -66.7, -98.0, -96, 4255660)



end
