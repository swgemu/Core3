TalusLostAqualishScreenPlay = ScreenPlay:new {
	numberOfActs = 1, screenplayName = "TalusLostAqualishScreenPlay",


lootContainers = {
           178362,
	   6075911,
	   6075912,
	   6075913,
	   6075914
        },
        
        lootLevel = 25, 
 
        lootGroups = {
                {
                        groups = {
                                {group = "color_crystals", chance = 160000},
                                {group = "junk", chance = 8240000},
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
 
registerScreenPlay("TalusLostAqualishScreenPlay", true)
 
function TalusLostAqualishScreenPlay:start()
	if (isZoneEnabled("talus")) then
                self:spawnMobiles()
                self:initializeLootContainers()
        end
end

function TalusLostAqualishScreenPlay:spawnMobiles()

	spawnMobile("talus", "lost_aqualish_warchief", 300, -94.5, -100.8, -101.9, 171, 4255650)
	spawnMobile("talus", "lost_aqualish_commando", 300, -101.6, -99.1, -106.2, 148, 4255650)
	spawnMobile("talus", "lost_aqualish_commando", 300, -85.6, -101.7, -111.7, -177, 4255650)

	spawnMobile("talus", "lost_aqualish_captain", 300, -72.1, -98.0, -150.8, 149, 4255647)
	spawnMobile("talus", "lost_aqualish_infiltrator", 300, -64.2, -94.4, -153.2, -94, 4255647)
	spawnMobile("talus", "lost_aqualish_infiltrator", 300, -70.9, -97.3, -145.3, -160, 4255647)

	spawnMobile("talus", "lost_aqualish_captain", 300, -27.5, -80.0, -149.6, 31, 4255649)
	spawnMobile("talus", "lost_aqualish_marksman", 300, -19.9, -79.8, -147.5, -35, 4255649)
	spawnMobile("talus", "lost_aqualish_marksman", 300, -28.9, -79.8, -141.8, 167, 4255649)
	spawnMobile("talus", "lost_aqualish_commando", 300, -29.9, -70.5, -83.9, -87, 4255648)
	spawnMobile("talus", "lost_aqualish_commando", 300, -37.2, -70.8, -87.8, -19, 4255648)
	spawnMobile("talus", "lost_aqualish_marksman", 300, -43.2, -70.2, -83.2, 70, 4255648)
	spawnMobile("talus", "lost_aqualish_commando", 300, -54.7, -68.5, -110.3, -78, 4255648)
	spawnMobile("talus", "lost_aqualish_marksman", 300, -60.1, -68.2, -105.2, 159, 4255648)
	spawnMobile("talus", "lost_aqualish_captain", 300, -98.5, -70.1, -112.5, 174, 4255647)
	spawnMobile("talus", "lost_aqualish_commando", 300, -91.2, -70.4, -124.9, -157, 4255647)	
	spawnMobile("talus", "lost_aqualish_commando", 300, -118.5, -69.3, -121.0, -100, 4255647)
	spawnMobile("talus", "lost_aqualish_commando", 300, -119.5, -69.6, -125.7, 33, 4255647)
	spawnMobile("talus", "lost_aqualish_marksman", 300, -116.8, -69.5, -123.9, -55, 4255647)
	spawnMobile("talus", "lost_aqualish_captain", 300, -123.4, -69.2, -170.0, 98, 4255647)
	spawnMobile("talus", "lost_aqualish_outrider", 300, -119.4, -69.5, -173.1, 37, 4255647)
	spawnMobile("talus", "lost_aqualish_outrider", 300, -116.5, -69.2, -172.5, -36, 4255647)
	spawnMobile("talus", "lost_aqualish_commando", 300, -116.2, -68.9, -170.1, -118, 4255647)
	spawnMobile("talus", "lost_aqualish_captain", 300, -118.9, -69.0, -167.9, 171, 4255647)
	spawnMobile("talus", "lost_aqualish_outrider", 300, -39.8, -67.6, -180.9, -90, 4255647)
	spawnMobile("talus", "lost_aqualish_warchief", 300, -18.5, -63.7, -258.8, -38, 4255646)
	spawnMobile("talus", "lost_aqualish_commando", 300, -20.3, -65.6, -242.0, 29, 4255646)
	spawnMobile("talus", "lost_aqualish_marksman", 300, -7.9, -64.0, -227.5, -16, 4255646)
	spawnMobile("talus", "lost_aqualish_outrider", 300, -16.5, -65.2, -218.6, -77, 4255646)
	spawnMobile("talus", "lost_aqualish_scout", 300, 45.3, -56.3, -181.2, 138, 4255644)
	spawnMobile("talus", "lost_aqualish_scout", 300, 63.7, -56.9, -176.5, 61, 4255644)
	spawnMobile("talus", "lost_aqualish_outrider", 300, 61.6, -55.4, -154.0, -62, 4255644)
	spawnMobile("talus", "lost_aqualish_captain", 300, 38.6, -56.0, -157.3, -131, 4255644)
	spawnMobile("talus", "lost_aqualish_captain", 300, -9.2, -45.6, -147.3, 63, 4255644)
	spawnMobile("talus", "lost_aqualish_outrider", 300, -10.8, -45.0, -131.2, -60, 4255644)
	spawnMobile("talus", "lost_aqualish_scout", 300, 4.7, -44.9, -131.6, 36, 4255644)
	spawnMobile("talus", "lost_aqualish_lookout", 300, 46.4, -46.2, -94.8, -14, 4255643)
	spawnMobile("talus", "lost_aqualish_lookout", 300, 41.2, -46.2, -56.1, -102, 4255643)
	spawnMobile("talus", "lost_aqualish_scout", 300, 36.5, -45.5, -48.2, -115, 4255643)
	spawnMobile("talus", "lost_aqualish_outrider", 300, 9.8, -40.5, -75.7, -140, 4255642)
	spawnMobile("talus", "lost_aqualish_lookout", 300, 3.4, -40.4, -65.0, -44, 4255642)
	spawnMobile("talus", "lost_aqualish_lookout", 300, -9.8, -40.9, -66.7, -12, 4255642)
	spawnMobile("talus", "lost_aqualish_scout", 300, -8.3, -30.9, -31.2, 28, 4255641)
	spawnMobile("talus", "lost_aqualish_lookout", 300, 10.3, -23.3, -23.5, 170, 4255641)
	spawnMobile("talus", "lost_aqualish_lookout", 300, -4330.4, 35.1, -1415.0, 82, 0)
	spawnMobile("talus", "lost_aqualish_lookout", 300, -4346.2, 32.4, -1447.3, 157, 0)
	spawnMobile("talus", "lost_aqualish_lookout", 300, -4348.2, 32.4, -1448.2, 178, 0)

end
