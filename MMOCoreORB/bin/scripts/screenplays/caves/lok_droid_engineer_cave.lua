DroidEngineerCaveScreenPlay = ScreenPlay:new {
	numberOfActs = 1,
	
	screenplayName = "DroidEngineerCaveScreenPlay",
	
	lootContainers = {
		568995,
		871800,
		871802,
		871812
	},
	
	lootLevel = 45,	

	lootGroups = {
		{
			groups = {
				{group = "color_crystals", chance = 200000},
				{group = "nyms_common", chance = 8600000},
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

registerScreenPlay("DroidEngineerCaveScreenPlay", true)

function DroidEngineerCaveScreenPlay:start()
	if (isZoneEnabled("lok")) then
		self:spawnMobiles()
		self:initializeLootContainers()
	end
end

function DroidEngineerCaveScreenPlay:spawnMobiles()
	spawnMobile("lok", "droideka",600,16.3,-21.5,-20.9,-56,568975)
	spawnMobile("lok", "droideka",600,17.2,-35.3,-76.3,11,568976)
	spawnMobile("lok", "droideka",600,-28.2,-43.4,-92.3,109,568978)
	spawnMobile("lok", "droideka",600,-14.6,-44,-97.8,-60,568978)
	spawnMobile("lok", "droideka",600,-57.2,-51.2,-111.9,-100,568978)
	spawnMobile("lok", "droideka",600,-76.7,-67,-136.6,-31,568981)
	spawnMobile("lok", "droideka",600,-48.3,-68.3,-134.6,-105,568981)
	spawnMobile("lok", "droideka",600,-29.1,-68,-110.6,77,568978)
	spawnMobile("lok", "droideka",600,-0.9,-70.9,-108.6,157,568982)
	spawnMobile("lok", "droideka",600,43.9,-65.7,-84.1,-28,568983)
	spawnMobile("lok", "droideka",600,35.4,-66.5,-87.1,-5,568983)
	spawnMobile("lok", "droideka",600,-44.8,-66.8,-157.2,-111,568984)
	spawnMobile("lok", "droideka",600,-59.4,-65.2,-227.8,-2,568985)
	spawnMobile("lok", "droideka",600,-84.4,-65.8,-194.2,30,568984)
	spawnMobile("lok", "droideka",600,-12.7,-30.1,-41.8,-21,568958)
	spawnMobile("lok", "droideka",600,-17.7,-30,-47.7,15,568958)
	spawnMobile("lok", "droideka",600,-63.7,-30.5,-72.8,-73,568961)
	spawnMobile("lok", "droideka",600,-102.1,-38.6,-120.1,47,568965)
	spawnMobile("lok", "droideka",600,-105.2,-36.2,-64.3,-88,568962)
	spawnMobile("lok", "droideka",600,-112.8,-58.3,-28.8,-95,568972)
	spawnMobile("lok", "droideka",600,-140.7,-53.9,-87.2,177,568967)
	spawnMobile("lok", "droideka",600,-175,-49.8,-86.6,139,568966)
	spawnMobile("lok", "droideka",600,-166.7,-49.3,-84.4,-28,568966)
	spawnMobile("lok", "droideka",600,-160.7,-49.6,-56.6,-162,568966)
	spawnMobile("lok", "droideka",600,-117.3,-49.2,-60.1,-76,568962)
	spawnMobile("lok", "droideka",600,-103.6,-53,-59.6,108,568962)
	spawnMobile("lok", "droideka",600,-66.6,-46.5,-31.9,-138,568960)
	spawnMobile("lok", "droideka",600,-57.4,-41.2,-9.8,109,568960)
	
	spawnMobile("lok", "ig_assassin_droid",600,-6.4,-35.1,-79,103,568976)
	spawnMobile("lok", "ig_assassin_droid",600,-15.5,-35,-69,12,568976)
	spawnMobile("lok", "ig_assassin_droid",600,-111.2,-54.3,-112.5,92,568965)
	spawnMobile("lok", "ig_assassin_droid",600,-125.4,-60.3,-137.7,-33,568980)
	spawnMobile("lok", "ig_assassin_droid",600,-101,-70.2,-107.6,175,568965)
	spawnMobile("lok", "ig_assassin_droid",600,-88.8,-72.1,-117.1,-99,568965)
	spawnMobile("lok", "ig_assassin_droid",600,-77.4,-66.1,-196.1,-99,568984)
	spawnMobile("lok", "ig_assassin_droid",600,-53.4,-65.5,-229.5,-6,568985)
	spawnMobile("lok", "ig_assassin_droid",600,-53.1,-65.4,-192.4,6,568984)
	spawnMobile("lok", "ig_assassin_droid",600,1.4,-67.4,-73.3,129,568976)
	spawnMobile("lok", "ig_assassin_droid",600,11.5,-67.3,-70.2,-103,568976)
	spawnMobile("lok", "ig_assassin_droid",600,42.5,-67.2,-73.2,-119,568983)
	spawnMobile("lok", "ig_assassin_droid",600,33.7,-69.3,-106.8,-16,568983)
	spawnMobile("lok", "ig_assassin_droid",600,-34.6,-31.1,-22.8,84,568958)
	spawnMobile("lok", "ig_assassin_droid",600,-43.9,-29.7,-42.3,137,568959)
	spawnMobile("lok", "ig_assassin_droid",600,-75.9,-29.9,-42.1,109,568961)
	spawnMobile("lok", "ig_assassin_droid",600,-103.2,-39.1,-87,-35,568967)
	spawnMobile("lok", "ig_assassin_droid",600,-107.4,-39.1,-81,133,568967)
	spawnMobile("lok", "ig_assassin_droid",600,-104.4,-58.2,-29.9,-76,568972)
	spawnMobile("lok", "ig_assassin_droid",600,-98.6,-54.9,-88.3,-13,568967)
	spawnMobile("lok", "ig_assassin_droid",600,-124.2,-53.8,-86.9,61,568967)
	spawnMobile("lok", "ig_assassin_droid",600,-163,-49.8,-79.5,-137,568966)
	spawnMobile("lok", "ig_assassin_droid",600,-166.7,-49.8,-70.9,167,568966)
	spawnMobile("lok", "ig_assassin_droid",600,-173.4,-49.8,-59.4,40,568966)
	spawnMobile("lok", "ig_assassin_droid",600,-71.4,-47,-69.9,-41,568961)
	spawnMobile("lok", "ig_assassin_droid",600,-64.5,-46.9,-73.5,129,568961)
end
