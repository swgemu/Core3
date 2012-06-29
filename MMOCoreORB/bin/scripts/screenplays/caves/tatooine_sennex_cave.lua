SennexCaveScreenPlay = ScreenPlay:new {
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

registerScreenPlay("SennexCaveScreenPlay", true)

function SennexCaveScreenPlay:start()
	self:spawnMobiles()
	self:initializeLootContainers()
end

function SennexCaveScreenPlay:spawnMobiles()
	--spawnMobile("tatooine", "jabba_enforcer", 200, -3.5, -12.7, -6.7, 24, 4235585)
end

function SennexCaveScreenPlay:initializeLootContainers()
	for k,v in pairs(self.lootContainers) do
		local pContainer = getSceneObject(v)
		createObserver(OPENCONTAINER, "SennexCaveScreenPlay", "spawnContainerLoot", pContainer)
		self:spawnContainerLoot(pContainer)
	end
end

function SennexCaveScreenPlay:spawnContainerLoot(pContainer)
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