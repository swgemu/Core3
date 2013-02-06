EndorOrphanedMarauderCaveScreenPlay = ScreenPlay:new {
	numberOfActs = 1, screenplayName = "EndorOrphanedMarauderCaveScreenPlay",


	lootContainers = {
           	733413,
		733416,
		733422
        },
        
        lootLevel = 50, 
 
        lootGroups = {
                {
                        groups = {
                                {group = "color_crystals", chance = 160000},
                                {group = "junk", chance = 7240000},
                                {group = "melee_weapons", chance = 1000000},
				{group = "ranged_weapons", chance = 1000000},
                                {group = "clothing_attachments", chance = 300000},
                                {group = "armor_attachments", chance = 300000}
                        },
                        lootChance = 8000000
                }                                       
        },
        
        lootContainerRespawn = 1800
}
 
registerScreenPlay("EndorOrphanedMarauderCaveScreenPlay", true)
 
function EndorOrphanedMarauderCaveScreenPlay:start()
	if (isZoneEnabled("endor")) then
                self:spawnMobiles()
                self:initializeLootContainers()
        end
end

function EndorOrphanedMarauderCaveScreenPlay:spawnMobiles()

	spawnMobile("endor", "berserk_marauder", 300, 191.7, -66.7, -101.7, 105, 733405)
	spawnMobile("endor", "berserk_marauder", 300, 188.0, -66.1, -103.1, -78, 733405)
	spawnMobile("endor", "berserk_marauder", 300, 188.2, -66.1, -98.6, -101, 733405)
	spawnMobile("endor", "frenzied_marauder", 300, 136.0, -67.0, -97.7, -144, 733404)
	spawnMobile("endor", "frenzied_marauder", 300, 134.5, -66.9, -93.0, -48, 733404)
	spawnMobile("endor", "frenzied_marauder", 300, 131.4, -66.9, -88.7, 116, 733404)
	spawnMobile("endor", "frenzied_marauder", 300, 152.6, -66.2, -129.1, 109, 733404)
	spawnMobile("endor", "frenzied_marauder", 300, 121.1, -66.5, -127.7, 66, 733404)
	spawnMobile("endor", "frenzied_marauder", 300, 125.6, -66.5, -126.8, -73, 733404)
	spawnMobile("endor", "feral_marauder", 300, 95.4, -66.0, -110.7, -168, 733401)
	spawnMobile("endor", "feral_marauder", 300, 64.9, -66.5, -136.3, -33, 733402)
	spawnMobile("endor", "marauder", 300, 52.3, -77.0, -91.0, 45, 733402)
	spawnMobile("endor", "marauder", 300, 94.8, -75.7, -69.5, -48, 733400)
	spawnMobile("endor", "marauder", 300, 92.2, -75.9, -67.1, 77, 733400)
	spawnMobile("endor", "berserk_marauder", 300, 95.4, -75.6, -66.1, -132, 733400)
	spawnMobile("endor", "frenzied_marauder", 300, 63.9, -75.2, -56.3, 110, 733400)
	spawnMobile("endor", "berserk_marauder", 300, 70.5, -75.2, -61.7, 28, 733400)
	spawnMobile("endor", "berserk_marauder", 300, 54.6, -68.2, -43.4, 55, 733398)
	spawnMobile("endor", "marauder", 300, 89.7, -62.3, -18.4, -39, 733399)
	spawnMobile("endor", "marauder", 300, 92.3, -62.0, -15.7, -89, 733399)
	spawnMobile("endor", "marauder", 300, 90.0, -61.9, -13.0, 179, 733399)
	spawnMobile("endor", "marauder", 300, 87.7, -62.2, -14.9, 96, 733399)
	spawnMobile("endor", "marauder", 300, 44.7, -47.1, -8.6, -139, 733398)
	spawnMobile("endor", "marauder", 300, 44.3, -47.2, -12.1, 7, 733398)
	spawnMobile("endor", "marauder", 300, 46.4, -48.0, -60.3, 86, 733398)
	spawnMobile("endor", "marauder", 300, 51.7, -48.1, -67.8, 94, 733398)
	spawnMobile("endor", "marauder", 300, 23.0, -42.2, -62.0, 0, 733398)
	spawnMobile("endor", "marauder", 300, 26.1, -41.9, -60.6, -10, 733398)
	spawnMobile("endor", "frenzied_marauder", 300, 76.6, -45.7, -147.8, 33, 733407)
	spawnMobile("endor", "frenzied_marauder", 300, 82.3, -46.4, -148.1, -23, 733407)
	spawnMobile("endor", "marauder", 300, 89.7, -46.6, -113.3, -40, 733401)
	spawnMobile("endor", "marauder", 300, 91.7, -46.5, -108.0, -102, 733401)
	spawnMobile("endor", "marauder", 300, 86.2, -46.7, -109.8, -79, 733401)
	spawnMobile("endor", "feral_marauder", 300, -6889.2, 8.0, 724.5, 72, 0)
	spawnMobile("endor", "feral_marauder", 300, -6888.3, 7.9, 730.4, 144, 0)
	spawnMobile("endor", "feral_marauder", 300, -6882.6, 7.4, 727.3, -90, 0)
	spawnMobile("endor", "feral_marauder", 300, -6906.2, 10.6, 687.4, 131, 0)
	spawnMobile("endor", "feral_marauder", 300, -6906.8, 10.8, 681.8, 85, 0)
	spawnMobile("endor", "feral_marauder", 300, -6899.9, 10.2, 685.5, -102, 0)

end
