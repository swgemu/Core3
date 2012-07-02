BlueleafTempleScreenPlay = ScreenPlay:new {
	numberOfActs = 1,
	
	screenplayName = "BlueleafTempleScreenPlay",
	
	lootContainers = {},
	
	lootLevel = 0,	

	lootGroups = {},
	
	lootContainerRespawn = 0
}

registerScreenPlay("BlueleafTempleScreenPlay", true)

function BlueleafTempleScreenPlay:start()
	if (isZoneEnabled("yavin4")) then
		self:spawnMobiles()
		self:initializeLootContainers()
	end
end

function BlueleafTempleScreenPlay:spawnMobiles()
-- Outside Temple	
spawnMobile("yavin4", "kliknik",900,-895.6,84.8,-2059,-139,0)
spawnMobile("yavin4", "kliknik",900,-896.2,84.8,-2064.1,42,0)
spawnMobile("yavin4", "kliknik",900,-892.3,84.8,-2062.4,-109,0)
spawnMobile("yavin4", "kliknik",900,-884.4,84.8,-2026.1,-96,0)
spawnMobile("yavin4", "kliknik",900,-888.5,84.8,-2023.3,155,0)
spawnMobile("yavin4", "kliknik",900,-888.6,84.8,-2028.8,35,0)

-- Inside Temple
spawnMobile("yavin4", "kliknik_dark_defender",900,-9,-37.3,-9,48,468319)
spawnMobile("yavin4", "kliknik_dark_defender",900,-10.5,-37.3,4.2,111,468319)
spawnMobile("yavin4", "kliknik_dark_defender",900,6.6,-37.3,12.8,-149,468319)
spawnMobile("yavin4", "kliknik_dark_defender",900,10.2,-37.3,4.8,-110,468319)
spawnMobile("yavin4", "kliknik_dark_defender",900,10.9,-37.3,-3.9,-69,468319)
spawnMobile("yavin4", "kliknik_dark_defender",900,-12.1,-37.3,18.2,74,468319)

spawnMobile("yavin4", "kliknik_dark_queen",900,-0.6,-37.3,-28.3,-19,468319)

spawnMobile("yavin4", "kliknik_dark_worker",900,-24,-1.3,10.3,93,468319)
spawnMobile("yavin4", "kliknik_dark_worker",900,-16.4,-1.3,-21,49,468319)
spawnMobile("yavin4", "kliknik_dark_worker",900,12.1,-1.3,-23.4,21,468319)
spawnMobile("yavin4", "kliknik_dark_worker",900,23.4,-1.3,11,-77,468319)

spawnMobile("yavin4", "kliknik_warrior",900,12.4,-1.3,32.4,-93,468318)
spawnMobile("yavin4", "kliknik_warrior",900,-12.8,-1.3,32,93,468318)

end