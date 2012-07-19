ForceCrystalCaveScreenPlay = ScreenPlay:new {
	numberOfActs = 1,
}

registerScreenPlay("ForceCrystalCaveScreenPlay", true)

function ForceCrystalCaveScreenPlay:start()
	self:spawnMobiles()
end

function ForceCrystalCaveScreenPlay:spawnMobiles()   
	spawnMobile("dantooine", "force_crystal_hunter",1800,89,-62,-13.4,-139,8535485)
	spawnMobile("dantooine", "force_crystal_hunter",1800,52.5,-67.9,-42.9,32,8535484)
	spawnMobile("dantooine", "force_crystal_hunter",1800,76.3,-77,-89.3,-81,8535486)
	
	spawnMobile("dantooine", "force_sensitive_crypt_crawler",1800,26.1,-43,-68.3,84,8535484)
	spawnMobile("dantooine", "force_sensitive_crypt_crawler",1800,64.1,-68.9,-36.8,86,8535485)
	spawnMobile("dantooine", "force_sensitive_crypt_crawler",1800,85.3,-77.2,-62.9,-57,8535486)
	spawnMobile("dantooine", "force_sensitive_crypt_crawler",1800,69.3,-75.7,-65.4,30,8535486)
	
	spawnMobile("dantooine", "untrained_wielder_of_the_dark_side",1800,0.7,-13.6,-6.9,-82,8535483)
	spawnMobile("dantooine", "untrained_wielder_of_the_dark_side",1800,65.6,-77,-78.4,-10,8535486)
	spawnMobile("dantooine", "untrained_wielder_of_the_dark_side",1800,23.8,-38.4,-32.8,-2,8535484)
	spawnMobile("dantooine", "untrained_wielder_of_the_dark_side",1800,22.4,-42.1,-64.1,38,8535484)
	spawnMobile("dantooine", "untrained_wielder_of_the_dark_side",1800,49.8,-48.5,-65.6,-51,8535484)
	spawnMobile("dantooine", "untrained_wielder_of_the_dark_side",1800,49.7,-48,-17.7,167,8535484)
end