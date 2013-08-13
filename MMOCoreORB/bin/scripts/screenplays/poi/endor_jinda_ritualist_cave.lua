JindaRitualistCaveScreenPlay = ScreenPlay:new {
	numberOfActs = 1,
	
	screenplayName = "JindaRitualistCaveScreenPlay",
	
	lootContainers = {
		189523,
		189524,
		189525,
		189526,
		189527,
		189528
	},
	
	lootLevel = 20,	--Jinda, level 5-51

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
	
	lootContainerRespawn = 1800 -- in seconds, Default 1800
}

registerScreenPlay("JindaRitualistCaveScreenPlay", true)

function JindaRitualistCaveScreenPlay:start()
	if (isZoneEnabled("endor")) then
		self:spawnMobiles()
		self:initializeLootContainers()
	end
end

function JindaRitualistCaveScreenPlay:spawnMobiles()


	--Outside spawns
	spawnMobile("endor", "jinda_veteran",300,-1756.2,27.6,-2.5,-59,0)
	spawnMobile("endor", "jinda_warrior",300,-1760.1,28.6,1.0,131,0)
	spawnMobile("endor", "jinda_tribesman",300,-1761.5,27.8,-2.5,79,0)

	spawnMobile("endor", "jinda_ritualist",300,-1755.5,37.3,24.1,-175,0)
	spawnMobile("endor", "jinda_shaman",300,-1760.3,36.2,21.2,5,0)
	spawnMobile("endor", "jinda_veteran",300,-1752.1,36.2,21.1,-99,0)

	spawnMobile("endor", "jinda_ritualist",300,-1666.4,30.5,2.0,162,0)
	spawnMobile("endor", "jinda_tribesman",300,-1673.3,29.9,-1.2,-166,0)
	spawnMobile("endor", "jinda_veteran",300,-1665.9,28.3,-4.3,-30,0)

	spawnMobile("endor", "jinda_veteran",300,-1678.5,40.1,33.0,14,0)
	spawnMobile("endor", "jinda_ritualist",300,-1670.0,40.5,32.9,-130,0)
	spawnMobile("endor", "jinda_veteran",300,-1677.2,37.8,25.7,-175,0)

	--Right cave branch.
	spawnMobile("endor", "jinda_ritualist",300,-32.9,-21.9,-26.4,19,6016547)
	spawnMobile("endor", "archaic_jinda_ritualist",300,-33.7,-22.7,-24.8,86,6016547)
	spawnMobile("endor", "jinda_ritualist",300,-31.3,-21.5,-25.9,-65,6016547)

	spawnMobile("endor", "jinda_elder_worker",300,-58.9,-35.2,-26.8,-67,6016549)
	spawnMobile("endor", "jinda_elder",300,-58.0,-34.9,-24.5,-124,6016549)
	spawnMobile("endor", "jinda_shaman",300,-60.5,-35.9,-25.3,22,6016549)

	spawnMobile("endor", "jinda_tribesman",300,-71.5,-38.5,-56.8,-28,6016550)
	spawnMobile("endor", "jinda_ritualist",300,-74.4,-38.6,-58.3,-37,6016550)
	spawnMobile("endor", "jinda_warrior",300,-74.8,-38.4,-55.2,146,6016550)

	spawnMobile("endor", "jinda_cub",300,-64.7,-38.9,-71.6,-134,6016550)
	spawnMobile("endor", "jinda_loremaster",300,-65.2,-38.9,-73.9,-49,6016550)

	spawnMobile("endor", "jinda_tribesman",300,-123.0,-41.4,-64.5,50,6016551)
	spawnMobile("endor", "jinda_shaman",300,-124.0,-41.5,-60.4,115,6016551)
	spawnMobile("endor", "jinda_ritualist",300,-121.5,-41.5,-63.1,-86,6016551)

	spawnMobile("endor", "jinda_elder",300,-160.0,-41.9,-61.9,-109,6016555)
	spawnMobile("endor", "jinda_veteran",300,-160.6,-41.3,-67.8,-96,6016555)
	spawnMobile("endor", "jinda_tribesman",300,-161.3,-42.1,-76.2,-89,6016555)
	spawnMobile("endor", "jinda_shaman",300,-160.7,-42.0,-82.8,-69,6016555)

	spawnMobile("endor", "jinda_elder",300,-175.5,-41.8,-63.4,90,6016555)
	spawnMobile("endor", "jinda_ritualist",300,-174.5,-41.9,-69.3,86,6016555)
	spawnMobile("endor", "jinda_tribesman",300,-174.9,-41.3,-75.3,83,6016555)
	spawnMobile("endor", "jinda_warrior",300,-175.3,-41.1,-81.0,93,6016555)

	spawnMobile("endor", "jinda_tribesman",300,-144.2,-45.8,-84.0,46,6016556)
	spawnMobile("endor", "jinda_tribesman",300,-142.9,-46.0,-80.2,149,6016556)

	spawnMobile("endor", "jinda_shaman",300,-106.6,-46.5,-79.8,-136,6016556)
	spawnMobile("endor", "jinda_tribesman",300,-110.9,-46.4,-80.4,127,6016556)
	spawnMobile("endor", "jinda_veteran",300,-109.5,-46.5,-83.4,9,6016556)

	spawnMobile("endor", "jinda_veteran",300,-113.1,-49.9,-25.9,-142,6016561)
	spawnMobile("endor", "jinda_cub",300,-116.4,-50.0,-27.1,105,6016561)
	spawnMobile("endor", "jinda_elder",300,-114.5,-50.2,-28.3,8,6016561)

	spawnMobile("endor", "jinda_warrior",300,-94.7,-31.1,-86.8,-131,6016556)
	spawnMobile("endor", "jinda_loremaster",300,-94.5,-30.6,-90.3,-41,6016556)
	spawnMobile("endor", "jinda_elder_worker",300,-97.3,-31.0,-88.2,112,6016556)

	spawnMobile("endor", "jinda_ritualist",300,-62.9,-22.2,-71.6,-34,6016550)
	spawnMobile("endor", "jinda_tribesman",300,-63.2,-23.0,-63.5,-116,6016550)
	spawnMobile("endor", "jinda_ritualist",300,-65.0,-23.4,-59.0,160,6016550)
	spawnMobile("endor", "jinda_veteran",300,-77.7,-22.3,-41.1,84,6016550)

	spawnMobile("endor", "archaic_jinda_ritualist",300,-8.8,-22.3,-49.0,-51,6016547)
	spawnMobile("endor", "jinda_warrior",300,-7.0,-22.3,-45.0,-121,6016547)
	spawnMobile("endor", "jinda_matriarch",300,-9.6,-22.4,-46.9,119,6016547)



	--Left cave branch
	spawnMobile("endor", "jinda_ritualist",300,20.3,-14.9,-25.1,-76,6016564)
	spawnMobile("endor", "archaic_jinda_ritualist",300,15.9,-15.0,-26.0,83,6016564)
	spawnMobile("endor", "jinda_ritualist",300,19.6,-16.1,-28.4,10,6016564)

	spawnMobile("endor", "jinda_warrior",300,18.4,-23.0,-48.8,-61,6016564)
	spawnMobile("endor", "jinda_ritualist",300,15.1,-22.1,-47.3,68,6016564)
	spawnMobile("endor", "jinda_warrior",300,16.9,-23.7,-50.7,-5,6016564)

	spawnMobile("endor", "jinda_ritualist",300,-20.8,-26.9,-64.5,-175,6016566)
	spawnMobile("endor", "jinda_shaman",300,-25.0,-27.2,-64.3,-175,6016566)
	spawnMobile("endor", "jinda_loremaster",300,-27.1,-27.3,-67.4,43,6016566)
	spawnMobile("endor", "jinda_ritualist",300,-23.2,-26.9,-66.6,14,6016566)

	spawnMobile("endor", "jinda_elder_worker",300,-9.0,-35.5,-99.8,-52,6016567)
	spawnMobile("endor", "jinda_elder",300,-9.8,-35.7,-95.3,-149,6016567)
	spawnMobile("endor", "jinda_warrior",300,-13.2,-35.8,-97.7,86,6016567)

	spawnMobile("endor", "jinda_warrior",300,-43.1,-38.1,-107.9,106,6016567)
	spawnMobile("endor", "jinda_tribesman",300,-39.7,-37.1,-108.1,-66,6016567)

	spawnMobile("endor", "jinda_tribesman",300,-109.4,-46.2,-110.2,107,6016554)
	spawnMobile("endor", "jinda_warrior",300,-108.9,-46.1,-114.3,55,6016554)

	spawnMobile("endor", "jinda_warrior",300,-108.8,-61.6,-107.9,136,6016554)
	spawnMobile("endor", "jinda_warrior",300,-110.0,-61.7,-115.1,44,6016554)
	spawnMobile("endor", "jinda_tribesman",300,-107.5,-61.6,-109.3,-142,6016554)

	spawnMobile("endor", "jinda_veteran",300,-76.6,-63.3,-110.5,-95,6016554)
	spawnMobile("endor", "jinda_tribesman",300,-81.6,-64.1,-109.1,-166,6016554)
	spawnMobile("endor", "jinda_shaman",300,-77.7,-63.6,-113.3,-22,6016554)

	spawnMobile("endor", "jinda_warrior",300,-85.1,-58.0,-186.5,147,6016573)
	spawnMobile("endor", "jinda_warrior",300,-83.6,-57.9,-194.1,41,6016573)

	spawnMobile("endor", "jinda_warrior",300,-44.9,-57.6,-188.9,-22,6016573)
	spawnMobile("endor", "jinda_loremaster",300,-42.5,-58.0,-184.6,-83,6016573)

	spawnMobile("endor", "jinda_loremaster",300,-43.2,-58.5,-160.9,-59,6016573)
	spawnMobile("endor", "jinda_warrior",300,-45.3,-58.7,-155.2,-149,6016573)

	spawnMobile("endor", "jinda_veteran",300,-56.7,-58.3,-236.0,-52,6016574)
	spawnMobile("endor", "archaic_jinda_ritualist",300,-62.3,-58.1,-234.4,108,6016574)
	spawnMobile("endor", "jinda_loremaster",300,-59.8,-57.6,-231.4,131,6016574)

	spawnMobile("endor", "jinda_matriarch",300,-1.1,-62.9,-111.3,18,6016571)
	spawnMobile("endor", "jinda_loremaster",300,4.0,-63.4,-106.2,-126,6016571)

	spawnMobile("endor", "jinda_veteran",300,2.1,-59.5,-68.4,75,6016565)
	spawnMobile("endor", "jinda_matriarch",300,5.6,-59.5,-66.2,164,6016565)

	spawnMobile("endor", "jinda_veteran",300,49.2,-58.2,-80.8,159,6016572)
	spawnMobile("endor", "jinda_matriarch",300,48.7,-58.1,-88.7,-8,6016572)
	spawnMobile("endor", "archaic_jinda_ritualist",300,45.8,-57.8,-83.8,70,6016572)

	spawnMobile("endor", "jinda_veteran",300,38.6,-61.3,-113.5,-68,6016572)
	spawnMobile("endor", "jinda_chief",300,34.3,-61.6,-113.4,12,6016572)
	spawnMobile("endor", "archaic_jinda_ritualist",300,34.0,-61.2,-105.6,133,6016572)
	spawnMobile("endor", "archaic_jinda_ritualist",300,39.1,-61.3,-108.0,-108,6016572)

end
