KungaStrongholdScreenPlay = ScreenPlay:new {
	numberOfActs = 1,
}

registerScreenPlay("KungaStrongholdScreenPlay", true)

function KungaStrongholdScreenPlay:start()
	self:spawnMobiles()
end

function KungaStrongholdScreenPlay:spawnMobiles()

spawnMobile("dantooine", "kunga_clan_leader",1800,-63.3,-65.3,-231.8,70,529402)

spawnMobile("dantooine", "kunga_clan_primalist",1800,-65.3,-30.6,-67.2,-28,529378)
spawnMobile("dantooine", "kunga_clan_primalist",1800,-66.5,-31.2,-61.9,-63,529378)
spawnMobile("dantooine", "kunga_clan_primalist",1800,-100.5,-38.4,-121.4,90,529382)
spawnMobile("dantooine", "kunga_clan_primalist",1800,-84.8,-66.3,-161.5,152,529401)
spawnMobile("dantooine", "kunga_clan_primalist",1800,-80.5,-65.6,-157.1,173,529401)
spawnMobile("dantooine", "kunga_clan_primalist",1800,-83,-66.3,-192.3,35,529401)
spawnMobile("dantooine", "kunga_clan_primalist",1800,-77.3,-66.4,-194.2,8,529401)

spawnMobile("dantooine", "kunga_harvester",900,-71.9,-30.3,-42.9,149,529378)
spawnMobile("dantooine", "kunga_harvester",900,-74.6,-30.1,-44.2,151,529378)

spawnMobile("dantooine", "kunga_hunter",1800,-105.2,-36.8,-61.5,-74,529379)
spawnMobile("dantooine", "kunga_hunter",1800,-107.6,-36.4,-64,-20,529379)
spawnMobile("dantooine", "kunga_hunter",1800,-104.4,-39.5,-116.9,44,529382)
spawnMobile("dantooine", "kunga_hunter",1800,-100.2,-38.7,-120.3,8,529382)
spawnMobile("dantooine", "kunga_hunter",900,-14.9,-44.1,-100.7,-36,529395)
spawnMobile("dantooine", "kunga_hunter",900,-8.2,-44,-96.2,-93,529395)
spawnMobile("dantooine", "kunga_hunter",900,-39.8,-44.9,-96.9,64,529395)
spawnMobile("dantooine", "kunga_hunter",900,-40.4,-45.3,-105.3,17,529395)

spawnMobile("dantooine", "kunga_loreweaver",1800,-116.7,-58.3,-30.6,108,529389)
spawnMobile("dantooine", "kunga_loreweaver",1800,-112.8,-57.8,-33.7,54,529389)
spawnMobile("dantooine", "kunga_loreweaver",1800,-106.1,-58.2,-33.7,-72,529389)
spawnMobile("dantooine", "kunga_loreweaver",1800,-107.6,-58.1,-28.6,-119,529389)
spawnMobile("dantooine", "kunga_loreweaver",1800,-166.4,-49.6,-81.1,-17,529383)
spawnMobile("dantooine", "kunga_loreweaver",900,-97.4,-70.5,-109.7,172,529382)
spawnMobile("dantooine", "kunga_loreweaver",900,-91,-71.4,-108.8,-158,529382)

spawnMobile("dantooine", "kunga_rockshaper",1800,-13.9,-30.3,-47.8,1,529375)
spawnMobile("dantooine", "kunga_rockshaper",1800,-11.6,-30.3,-43.2,-102,529375)
spawnMobile("dantooine", "kunga_rockshaper",1800,-173,-50,-61.1,62,529383)
spawnMobile("dantooine", "kunga_rockshaper",1800,-162,-49.6,-59.9,-18,529383)
spawnMobile("dantooine", "kunga_rockshaper",1800,-75.4,-53.3,-114.2,82,529382)
spawnMobile("dantooine", "kunga_rockshaper",1800,-107.7,-54.2,-112.2,-93,529382)
spawnMobile("dantooine", "kunga_rockshaper",900,-105.4,-69.9,-112.2,116,529382)
spawnMobile("dantooine", "kunga_rockshaper",900,-67.3,-65.8,-141.4,-82,529398)
spawnMobile("dantooine", "kunga_rockshaper",900,-65,-66.3,-138.9,-69,529398)

spawnMobile("dantooine", "kunga_scout",900,-139.1,-49.6,-62.1,76,529379)
spawnMobile("dantooine", "kunga_scout",900,-141.1,-49.5,-57.7,101,529379)
spawnMobile("dantooine", "kunga_scout",900,-81.3,-67.7,-132.4,-7,529398)
spawnMobile("dantooine", "kunga_scout",900,-78.6,-67.4,-132.1,-11,529398)

spawnMobile("dantooine", "kunga_shaman",1800,-39.5,-32.3,-24.4,116,529375)
spawnMobile("dantooine", "kunga_shaman",1800,-170.1,-49.5,-79.2,5,529383)
spawnMobile("dantooine", "kunga_shaman",1800,-175.5,-48.9,-77.3,5,529383)

spawnMobile("dantooine", "kunga_soothsayer",900,-18.8,-29.8,-22.1,-85,529375)
spawnMobile("dantooine", "kunga_soothsayer",900,12.9,-35.5,-79.3,0,529393)
spawnMobile("dantooine", "kunga_soothsayer",900,-7.9,-35.4,-76.8,103,529393)
spawnMobile("dantooine", "kunga_soothsayer",900,-9,-34.8,-66.2,147,529393)

end