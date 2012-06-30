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
	numerOfActs = 0,
	startingEvent = nil
}

Act = Object:new {
		
}



includeFile("themepark/tutorial.lua")
includeFile("themepark/themepark_jabba.lua")
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
includeFile("dungeon/warren/mirla_convo_handler.lua")
includeFile("dungeon/warren/oevitt_piboi_convo_handler.lua")
includeFile("dungeon/warren/warren.lua")
includeFile("dungeon/death_watch_bunker_conv_handles.lua")
includeFile("themepark/imperial_retreat/kaja_orzee_handler.lua")

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
includeFile("caves/naboo_weapons_facility.lua")
includeFile("caves/dantooine_kunga_stronghold.lua")
includeFile("caves/dantooine_janta_cave.lua")
includeFile("caves/dantooine_force_crystal_hunter_cave.lua")

--POIs
includeFile("poi/tatooine_fort_tusken.lua")
includeFile("poi/corellia_rogue_corsec_base.lua")
includeFile("poi/dantooine_dantari_village.lua")

--Tests
--includeFile("tests/options_bitmask_test.lua")
--includeFile("event/stresstest_20120128.lua")