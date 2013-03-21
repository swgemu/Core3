BloodRazerTransportScreenPlay = ScreenPlay:new {
	numberOfActs = 1,

	screenplayName = "BloodRazerTransportScreenPlay",

	lootContainers = {
		568806, --toolchest
		568951,	--magseal
		568948  --magseal
	},
	
	lootLevel = 29,	

	lootGroups = {
		{
			groups = {
				{group = "color_crystals", chance = 2500000},
				{group = "junk", chance = 2500000},
				{group = "melee_two_handed", chance = 1000000},
				{group = "rifles", chance = 1000000},
				{group = "carbines", chance = 1000000},
				{group = "pistols", chance = 1000000},
				{group = "clothing_attachments", chance = 500000},
				{group = "armor_attachments", chance = 500000}
			},
			lootChance = 8000000
		}					
	},
	
	lootContainerRespawn = 1200 -- 20 minutes
}

registerScreenPlay("BloodRazerTransportScreenPlay", true)

function BloodRazerTransportScreenPlay:start()
	if (isZoneEnabled("lok")) then
		self:spawnMobiles()
		self:initializeLootContainers()
	end
end

function BloodRazerTransportScreenPlay:spawnMobiles()

	spawnMobile("lok", "blood_razor_scout", 300, 3568.4, 17.2, 2336.7, 70, 0)
	spawnMobile("lok", "blood_razor_scout", 300, 3695.7, 21.9, 2382.9, 90, 0)
	spawnMobile("lok", "blood_razor_scout", 300, 3859.5, 30.6, 2336.6, -100, 0)
	spawnMobile("lok", "blood_razor_scout", 300, 3870.8, 2.1, 2162.6, -100, 0)
	spawnMobile("lok", "blood_razor_scout", 300, 3452.1, 23.2, 2170.8, -75, 0)
	spawnMobile("lok", "blood_razor_scout", 300, 3583.6, 12.6, 1993.6, -135, 0)
	spawnMobile("lok", "blood_razor_scout", 300, 3494.3, 21.0, 2040.2, -117, 0)
	spawnMobile("lok", "blood_razor_scout", 300, 3480.4, 24.2, 2278.2, -52, 0)

	spawnMobile("lok", "blood_razor_guard", 300, 3640.2, 1.4, 2239.2, 98, 0)
	spawnMobile("lok", "blood_razor_guard", 300, 3648.5, 1.4, 2238.2, 98, 0)
	spawnMobile("lok", "blood_razor_guard", 300, 3657.3, 1.5, 2235.9, 105, 0)

	spawnMobile("lok", "blood_razor_weak_pirate", 300, 3679.0, 1.7, 2207.8, 25, 0)
	spawnMobile("lok", "blood_razor_weak_pirate", 300, 3675.8, 1.7, 2209.5, 25, 0)
	spawnMobile("lok", "blood_razor_weak_pirate", 300, 3672.6, 0.9, 2193.5, -50, 0)
	spawnMobile("lok", "blood_razor_weak_pirate", 300, 3669.4, 0.9, 2192.8, -50, 0)
	spawnMobile("lok", "blood_razor_weak_pirate", 300, 3618.1, 0.9, 2215.1, -25, 0)
	spawnMobile("lok", "blood_razor_weak_pirate", 300, 3614.5, 0.9, 2213.9, -25, 0)
	spawnMobile("lok", "blood_razor_weak_pirate", 300, 3616.4, 0.9, 2191.5, 0, 0)
	spawnMobile("lok", "blood_razor_weak_pirate", 300, 3613.5, 0.9, 2191.5, 0, 0)
	spawnMobile("lok", "blood_razor_weak_pirate", 300, 3644.3, 0.9, 2154.0, -145, 0)
	spawnMobile("lok", "blood_razor_weak_pirate", 300, 3641.4, 0.9, 2156.1, -145, 0)
	spawnMobile("lok", "blood_razor_weak_pirate", 300, 3624.4, 0.9, 2136.2, -160, 0)
	spawnMobile("lok", "blood_razor_weak_pirate", 300, 3620.8, 0.9, 2137.7, -160, 0)

	spawnMobile("lok", "blood_razor_strong_pirate", 300, 3608.3, 0.9, 2150.2, 90, 0)
	spawnMobile("lok", "blood_razor_strong_pirate", 300, 3608.9, 0.9, 2155.1, 90, 0)
	spawnMobile("lok", "blood_razor_strong_pirate", 300, 3604.9, 0.9, 2172.9, 100, 0)
	spawnMobile("lok", "blood_razor_strong_pirate", 300, 3606.8, 0.9, 2168.3, 100, 0)
	spawnMobile("lok", "blood_razor_strong_pirate", 300, 3615.2, 0.9, 2173.4, 135, 0)
	spawnMobile("lok", "blood_razor_strong_pirate", 300, 3613.1, 0.9, 2171.9, 135, 0)
	spawnMobile("lok", "blood_razor_strong_pirate", 300, 3658.5, 0.9, 2169.7, -52, 0)
	spawnMobile("lok", "blood_razor_strong_pirate", 300, 3661.4, 0.9, 2173.6, -52, 0)

	spawnMobile("lok", "thug", 90, 3639.3, 0.9, 2183.9, -90, 0)
	spawnMobile("lok", "thug", 90, -5.2, 0, 3.8, 90, 568777)
	spawnMobile("lok", "thug", 90, 4.4, 0, 3.7, -140, 568751)
	spawnMobile("lok", "thug", 90, 3.8, 0, 1.3, -90, 568751)
	spawnMobile("lok", "thug", 90, 4.2, 0, -3.9, -21, 568759)

	spawnMobile("lok", "blood_razor_destroyer", 300, 1.0, 0, -5.3, 0, 568778)
	spawnMobile("lok", "blood_razor_destroyer", 300, -1.0, 0, -5.3, 0, 568778)
	spawnMobile("lok", "blood_razor_officer", 300, -3.7, 0, -3.0, -175, 568781)
	spawnMobile("lok", "blood_razor_elite_pirate", 300, 4.1, 0, 3.3, 0, 568779)

	spawnMobile("lok", "blood_razor_elite_pirate", 300, -5.1, 0, 1.7, 0, 568749)
	spawnMobile("lok", "blood_razor_officer", 300, 4.6, 0, -3.8, 0, 568752)
	spawnMobile("lok", "blood_razor_captain", 300, -4.8, 0, -3.9, -90, 568753)
	
	spawnMobile("lok", "blood_razor_elite_pirate", 300, 3.7, 0, 1.5, -90, 568758)
	spawnMobile("lok", "blood_razor_officer", 300, 4.1, 0, 4.1, 0, 568758)
	spawnMobile("lok", "blood_razor_captain", 300, -4.1, 0, -1.8, -180, 568760)

end
