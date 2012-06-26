HuttHideoutScreenPlay = ScreenPlay:new {
	numberOfActs = 1,
	
	lootContainers = {
		134411,
		8496263,
		8496262,
		8496260
	},
	
	lootLevel = 32,	
	lootGroups = "armor_attachments",
	lootContainerRespawn = 1800 -- 30 minutes
}

registerScreenPlay("HuttHideoutScreenPlay", true)

function HuttHideoutScreenPlay:start()
	self:spawnMobiles()
	self:initializeLootContainers()
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
end

function HuttHideoutScreenPlay:initializeLootContainers()
	for k,v in pairs(self.lootContainers) do
		local pContainer = getSceneObject(v)
		createObserver(OPENCONTAINER, "HuttHideoutScreenPlay", "spawnContainerLoot", pContainer)
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
	
	local lootGroup = self:selectLootGroup()
	createLoot(pContainer, lootGroup, self.lootLevel)
	
	writeData(container:getObjectID(), time + self.lootContainerRespawn)
end

function HuttHideoutScreenPlay:selectLootGroup()
	--TODO: Expand this to allow for multiple loot groups.
	return self.lootGroups
end