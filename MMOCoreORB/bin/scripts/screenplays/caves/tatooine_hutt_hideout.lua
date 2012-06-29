HuttHideoutScreenPlay = ScreenPlay:new {
	numberOfActs = 1,
	
	lootContainers = {
		134411,
		8496263,
		8496262,
		8496261,
		8496260
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

registerScreenPlay("HuttHideoutScreenPlay", true)

function HuttHideoutScreenPlay:start()
	if (isZoneEnabled("tatooine")) then
		self:spawnMobiles()
		self:initializeLootContainers()
	end
end

function HuttHideoutScreenPlay:spawnMobiles()
	spawnMobile("tatooine", "jabba_enforcer", 200, -3.5, -12.7, -6.7, 24, 4235585)
	spawnMobile("tatooine", "jabba_henchman", 200, 1.1, -14.4, -9.3, 15, 4235585)
	
	spawnMobile("tatooine", "jabba_compound_guard", 200, -12.1, -32.2, -34, 19, 4235586)
	
	spawnMobile("tatooine", "jabba_enforcer", 200, -10.5, -40.4, -81.3, -178, 4235587)
	spawnMobile("tatooine", "jabba_henchman", 200, 5.8, -40.9, -79.6, -37, 4235587)
	spawnMobile("tatooine", "jabba_enforcer", 200, 14.5, -40.5, -74.2, -131, 4235587)
	spawnMobile("tatooine", "jabba_enforcer", 200, 20, -39.6, -77.9, -50, 4235587)
	spawnMobile("tatooine", "jabba_henchman", 200, 10.7, -41.1, -60.3, -124, 4235587)
	
	spawnMobile("tatooine", "jabba_henchman", 200, 47, -46.7, -50.8, -163, 4235588)
	spawnMobile("tatooine", "jabba_henchman", 200, 50.4, -46.8, -58.6, -19, 4235588)
	spawnMobile("tatooine", "jabba_henchman", 200, 51.6, -46, -91.6, -126, 4235588)
	spawnMobile("tatooine", "jabba_enforcer", 200, 47.1, -46.2, -96.3, 46, 4235588)
	spawnMobile("tatooine", "jabba_compound_guard", 200, 44.9, -46.2, -102.8, -41, 4235588)
	
	spawnMobile("tatooine", "jabba_henchman", 200, 13.9, -45, -121.1, 30, 4235589)
	spawnMobile("tatooine", "jabba_enforcer", 200, 1.5, -45, -141.6, 117, 4235589)
	spawnMobile("tatooine", "jabba_henchman", 200, -10, -45.6, -148, 26, 4235589)
	spawnMobile("tatooine", "jabba_henchman", 200, -12.4, -45, -130.8, 125, 4235589)
	spawnMobile("tatooine", "jabba_henchman", 200, 58.8, -47.1, -124.6, -21, 4235589)
	spawnMobile("tatooine", "jabba_henchman", 200, 73.5, -52.9, -144.7, -178, 4235589)
	spawnMobile("tatooine", "jabba_enforcer", 200, 72.5, -54.4, -151.6, -20, 4235589)
	spawnMobile("tatooine", "jabba_enforcer", 200, 38.2, -55.7, -155.4, -78, 4235589)
	spawnMobile("tatooine", "jabba_henchman", 200, 36.9, -56.1, -157.2, -53, 4235589)
	spawnMobile("tatooine", "jabba_henchman", 200, 67.5, -57.3, -176.7, 62, 4235589)
	spawnMobile("tatooine", "jabba_enforcer", 200, 58.6, -57.7, -185.3, -70, 4235589)
	spawnMobile("tatooine", "jabba_henchman", 200, 53, -57, -185.3, 59, 4235589)
	spawnMobile("tatooine", "jabba_compound_guard", 200, 58.8, -56.4, -159.5, -60, 4235589)
	spawnMobile("tatooine", "jabba_compound_guard", 200, 53.3, -56.6, -160.2, 45, 4235589)
	
	spawnMobile("tatooine", "jabba_compound_guard", 200, 6, -63.9, -181.8, 90, 4235590)
	spawnMobile("tatooine", "jabba_compound_guard", 200, -8.1, -65.1, -201.3, -10, 4235590)
	spawnMobile("tatooine", "jabba_compound_guard", 200, -37.5, -67, -182.8, 91, 4235590)
	
	spawnMobile("tatooine", "jabba_henchman", 200, -18.7, -65.5, -210.3, -152, 4235591)
	spawnMobile("tatooine", "jabba_compound_guard", 200, -22.5, -64.6, -220.2, -131, 4235591)
	spawnMobile("tatooine", "jabba_henchman", 200, -17.6, -65.4, -216.8, -7, 4235591)
	spawnMobile("tatooine", "jabba_henchman", 200, -4.8, -64.2, -231.5, 178, 4235591)
	spawnMobile("tatooine", "jabba_assassin", 200, -1.3, -64.2, -238.5, 88, 4235591)
	spawnMobile("tatooine", "jabba_compound_guard", 200, -224, -65, -249.8, -174, 4235591)
	spawnMobile("tatooine", "jabba_henchman", 200, -19.3, -62.6, -261.6, 43, 4235591)
	spawnMobile("tatooine", "jabba_assassin", 200, -10.6, -63.3, -261.2, -77, 4235591)
	
	spawnMobile("tatooine", "jabba_henchman", 200, -57.1, -70.2, -193, -70, 4235592)
	spawnMobile("tatooine", "jabba_compound_guard", 200, -71.8, -68.6, -182.3, 99, 4235592)
	spawnMobile("tatooine", "jabba_henchman", 200, -59.3, -69.8, -170.9, -53, 4235592)
	spawnMobile("tatooine", "jabba_enforcer", 200, -71.5, -70, -166.7, 141, 4235592)
	spawnMobile("tatooine", "jabba_assassin", 200, -98.3, -72.4, -174.9, 72, 4235592)
	spawnMobile("tatooine", "jabba_henchman", 200, -112.2, -69.1, -119.7, 84, 4235592)
	spawnMobile("tatooine", "jabba_enforcer", 200, -106.1, -68.6, -112.2, -76, 4235592)
	spawnMobile("tatooine", "jabba_assassin", 200, -84.2, -70.3, -129.7, 83, 4235592)
	spawnMobile("tatooine", "jabba_enforcer", 200, -94.9, -102.6, -137.2, 154, 4235592)
	spawnMobile("tatooine", "jabba_enforcer", 200, -95.6, -102.1, -140.6, 0, 4235592)
	
	spawnMobile("tatooine", "jabba_henchman", 200, -51.4, -68.9, -95.4, 135, 4235593)
	spawnMobile("tatooine", "jabba_enforcer", 200, -47.6, -69.3, -95.4, -133, 4235593)
	spawnMobile("tatooine", "jabba_enforcer", 200, -46.3, -69.3, -99, -52, 4235593)
	spawnMobile("tatooine", "jabba_compound_guard", 200, -59.4, -70.1, -88, -179, 4235593)
	spawnMobile("tatooine", "jabba_henchman", 200, -69.4, -68.5, -101.7, 110, 4235593)
	spawnMobile("tatooine", "jabba_compound_guard", 200, -65.6, -68.3, -103.1, -74, 4235593)
	spawnMobile("tatooine", "jabba_assassin", 200, -8.6, -68.6, -97.1, -162, 4235593)
	
	spawnMobile("tatooine", "jabba_compound_guard", 200, -32.1, -80.2, -143.5, 80, 4235594)
	spawnMobile("tatooine", "jabba_henchman", 200, -19.7, -79.8, -146.9, -59, 4235594)
	spawnMobile("tatooine", "jabba_henchman", 200, -21.2, -79.6, -143.8, 160, 4235594)
	
	spawnMobile("tatooine", "jabba_compound_guard", 200, -79, -100.9, -130, -100, 4235595)
	spawnMobile("tatooine", "jabba_assassin", 200, -83.8, -100.6, -106.6, -1, 4235595)
	spawnMobile("tatooine", "jabba_enforcer", 200, -86.4, -100.5, -103.6, 123, 4235595)
	spawnMobile("tatooine", "jabba_assassin", 200, -100.4, -99.9, -114.2, 162, 4235595)
	spawnMobile("tatooine", "jabba_enforcer", 200, -98.3, -100, -105.2, -43, 4235595)
end

function HuttHideoutScreenPlay:initializeLootContainers()
	for k,v in pairs(self.lootContainers) do
		local pContainer = getSceneObject(v)
		createObserver(OPENCONTAINER, "HuttHideoutScreenPlay", "spawnContainerLoot", pContainer)
		self:spawnContainerLoot(pContainer)
	end
end

function HuttHideoutScreenPlay:spawnContainerLoot(pContainer)
	if (pContainer == nil) then
		return
	end
	
	local container = LuaSceneObject(pContainer)
	local time = getTimestamp()
	
	if (readData(container:getObjectID()) > time) then
		return
	end
	
	--If it has loot already, then exit.
	if (container:getContainerObjectsSize() > 0) then
		return
	end

	createLootFromCollection(pContainer, self.lootGroups, self.lootLevel)
	
	writeData(container:getObjectID(), time + self.lootContainerRespawn)
end