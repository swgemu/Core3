function printf(...) io.write(string.format(unpack(arg))) end

function writeData(key, data)
	writeSharedMemory(string.format(key), data)
end

function writeStringData(key, data)
	writeStringSharedMemory(string.format(key), string.format(data))
end

function deleteData(key)
	deleteSharedMemory(string.format(key))
end

function deleteStringData(key)
	deleteStringSharedMemory(string.format(key))
end

function readData(key)
	return readSharedMemory(string.format(key))
end

function readStringData(key)
	return readStringSharedMemory(string.format(key))
end

Object = { 
}

-- for creation of new instances
function Object:new (o)
	o = o or { }
	setmetatable(o, self)
    self.__index = self
    return o
end

ScreenPlay = Object:new {
	screenplayName = "",
	numerOfActs = 0,
	startingEvent = nil,
	
	lootContainers = {},
	lootLevel = 0,
	lootGroups = {},
	lootContainerRespawn = 1800 -- 30 minutes
}

function ScreenPlay:initializeLootContainers()
	for k,v in pairs(self.lootContainers) do
		local pContainer = getSceneObject(v)
		if (pContainer ~= nil) then
			createObserver(OPENCONTAINER, self.screenplayName, "spawnContainerLoot", pContainer)
			self:spawnContainerLoot(pContainer)
			
			local container = LuaSceneObject(pContainer)
			container:setContainerDefaultAllowPermission(MOVEOUT + OPEN)
		end
	end
end

function ScreenPlay:spawnContainerLoot(pContainer)
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



Act = Object:new {
		
}


-- Theme parks

includeFile("themepark/themeParkLogic.lua")
includeFile("themepark/conversations/mission_giver_conv_handler.lua")
includeFile("themepark/conversations/mission_target_conv_handler.lua")
includeFile("themepark/rebel/themeParkRebel.lua")
includeFile("themepark/jabba/themeParkJabba.lua")
includeFile("themepark/tutorial.lua")

includeFile("recruiters/recruiters.lua")
includeFile("tasks/mozo_bondog.lua")
includeFile("tasks/dolac_legasi.lua")
includeFile("tasks/hedon_istee.lua")
includeFile("tasks/vardias_tyne.lua")
includeFile("tasks/ris_armor_quest.lua")
includeFile("recruiters/imperialrecruiter.lua")
includeFile("recruiters/rebelrecruiter.lua")
includeFile("dungeon/death_watch_bunker.lua")
includeFile("dungeon/geonosian_lab.lua")
includeFile("dungeon/warren/warren.lua")
includeFile("dungeon/death_watch_bunker_conv_handles.lua")

--Caves
includeFile("caves/corellia_afarathu_cave.lua")
includeFile("caves/corellia_lord_nyax_cult.lua")
includeFile("caves/corellia_rebel_hideout.lua")
includeFile("caves/naboo_narglatch_cave.lua")
includeFile("caves/tatooine_hutt_hideout.lua")
includeFile("caves/tatooine_sennex_cave.lua")
includeFile("caves/tatooine_squill_cave.lua")
includeFile("caves/tatooine_tusken_bunker.lua")
includeFile("caves/corellia_drall_cave.lua")
includeFile("caves/dantooine_kunga_stronghold.lua")
includeFile("caves/dantooine_janta_cave.lua")
includeFile("caves/dantooine_force_crystal_hunter_cave.lua")
includeFile("caves/lok_droid_engineer_cave.lua")
includeFile("caves/dathomir_rancor_cave.lua")
includeFile("caves/dathomir_spider_clan_cave.lua")

--POIs
includeFile("poi/tatooine_fort_tusken.lua")
includeFile("poi/corellia_rogue_corsec_base.lua")
includeFile("poi/dantooine_dantari_village.lua")
includeFile("poi/naboo_mauler_stronghold.lua")
includeFile("poi/yavin4_woolamander_temple.lua")
includeFile("poi/yavin4_blueleaf_temple.lua")
includeFile("poi/dantooine_mokk_stronghold.lua")
includeFile("poi/naboo_weapon_testing_facility.lua")
includeFile("poi/rori_rebel_military_base.lua")

--Tests
--includeFile("tests/options_bitmask_test.lua")
--includeFile("event/stresstest_20120128.lua")
