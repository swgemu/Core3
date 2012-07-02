WeaponsFacilityScreenPlay = ScreenPlay:new {
	numberOfActs = 1,
}

registerScreenPlay("WeaponsFacilityScreenPlay", true)

function WeaponsFacilityScreenPlay:start()
	self:spawnMobiles()
end

function WeaponsFacilityScreenPlay:spawnMobiles()
	spawnMobile("naboo", "dark_trooper",900,2.3,-12,38.9,-177,6335643)
	spawnMobile("naboo", "dark_trooper",900,-42.8,-20,47.1,88,6335644)
	spawnMobile("naboo", "dark_trooper",900,-68.5,-20,28.8,54,6335645)
	spawnMobile("naboo", "dark_trooper",900,-64.6,-20,16.3,102,6335646)
	spawnMobile("naboo", "dark_trooper",900,-73.4,-20,81.1,90,6335647)
	spawnMobile("naboo", "dark_trooper",900,5,-12,57.7,-117,6335643)
	spawnMobile("naboo", "dark_trooper",900,36.7,-20,125.6,0,6335651)
	spawnMobile("naboo", "dark_trooper",900,36.7,-20,135.7,179,6335651)
	spawnMobile("naboo", "dark_trooper",900,1.9,-20,67.1,-52,6335659)
	spawnMobile("naboo", "dark_trooper",900,-33.9,-20,97,85,6335657)
	spawnMobile("naboo", "dark_trooper",900,-21.4,-20,-2.1,21,6335654)
	spawnMobile("naboo", "dark_trooper",900,56.7,-12,9.1,-77,6335652)
	spawnMobile("naboo", "dark_trooper",900,37,-12,22.2,-178,6335652)
		
	spawnMobile("naboo", "imperial_inquisitor",900,-72.1,-20,31.9,52,6335645)
	spawnMobile("naboo", "imperial_inquisitor",900,3.3,-12,55.8,2,6335643)
	spawnMobile("naboo", "imperial_inquisitor",900,37,-12,11.3,-95,6335652)
		
	spawnMobile("naboo", "stormtrooper",900,3.7,0.3,-3.7,6,6335641)
	spawnMobile("naboo", "stormtrooper",900,7.8,-12,30.7,-89,6335643)
	spawnMobile("naboo", "stormtrooper",900,-59.9,-20,31,76,6335645)
	spawnMobile("naboo", "stormtrooper",900,-51.1,-20,15.8,-90,6335646)
	spawnMobile("naboo", "stormtrooper",900,-65.8,-20,58,173,6335645)
	spawnMobile("naboo", "stormtrooper",900,6.8,-12,65.4,177,6335643)
	spawnMobile("naboo", "stormtrooper",900,22.9,-12,51.7,-94,6335643)
	spawnMobile("naboo", "stormtrooper",900,-6.5,-20,75.6,136,6335659)
	spawnMobile("naboo", "stormtrooper",900,-31.5,-20,100.6,176,6335657)
	spawnMobile("naboo", "stormtrooper",900,-12.3,-20,-2.2,1,6335654)
	spawnMobile("naboo", "stormtrooper",900,21.7,-12,4.9,177,6335652)
	spawnMobile("naboo", "stormtrooper",900,21.7,-12,-2.2,0,6335652)
	spawnMobile("naboo", "stormtrooper",900,57.1,-12,12.1,-177,6335652)
		
	spawnMobile("naboo", "stormtrooper_bombardier",900,-54.6,-20,35.2,-12,6335645)
	spawnMobile("naboo", "stormtrooper_bombardier",900,-0.3,-12,65,158,6335643)
	spawnMobile("naboo", "stormtrooper_bombardier",900,-21.2,-20,8,173,6335654)
		
	spawnMobile("naboo", "stormtrooper_captain",900,37.1,-12,16.3,-135,6335652)
	spawnMobile("naboo", "stormtrooper_captain",900,-74.9,-20,85.2,176,6335647)
		
	spawnMobile("naboo", "stormtrooper_commando",900,-13.2,-12,42.6,3,6335643)
	spawnMobile("naboo", "stormtrooper_commando",900,-12,-20,100.2,-55,6335657)
	spawnMobile("naboo", "stormtrooper_commando",900,26.2,-12,1.7,-55,6335652)
		
	spawnMobile("naboo", "stormtrooper_major",900,22.5,-12,44.1,-92,6335643)
	spawnMobile("naboo", "stormtrooper_major",900,-51.9,-20,9.4,-82,6335646)
	spawnMobile("naboo", "stormtrooper_major",900,72,-12,58.6,88,6335650)
	spawnMobile("naboo", "stormtrooper_major",900,25.6,-20,118.1,61,6335651)
		
	spawnMobile("naboo", "stormtrooper_medic",900,-1.1,-12,31,47,6335643)
	spawnMobile("naboo", "stormtrooper_medic",900,-64.8,-20,8.6,4,6335646)
	spawnMobile("naboo", "stormtrooper_medic",900,-74.7,-20,77.5,45,6335647)
	spawnMobile("naboo", "stormtrooper_medic",900,25.7,-20,131.4,86,6335651)
	spawnMobile("naboo", "stormtrooper_medic",900,-27.4,-20,114,179,6335657)
	spawnMobile("naboo", "stormtrooper_medic",900,-11.9,-20,8.3,179,6335654)
	spawnMobile("naboo", "stormtrooper_medic",900,58.7,-12,20,-110,6335652)
		
	spawnMobile("naboo", "stormtrooper_rifleman",900,-12.4,-12,52.1,-178,6335643)
	spawnMobile("naboo", "stormtrooper_rifleman",900,-67.2,-20,52.1,100,6335645)
	spawnMobile("naboo", "stormtrooper_rifleman",900,72.5,-12,83,88,6335649)
	spawnMobile("naboo", "stormtrooper_rifleman",900,59,-12,22.8,-151,6335652)
		
	spawnMobile("naboo", "stormtrooper_squad_leader",900,4675.99,25,-5809.56,216.285,0)
	spawnMobile("naboo", "stormtrooper_squad_leader",900,4678.77,25,-5757.9,226.393,0)
	spawnMobile("naboo", "stormtrooper_squad_leader",900,-16.6,-20,103.8,110,6335657)
end
	