DantariVillageScreenPlay = ScreenPlay:new {
	numberOfActs = 1,

}

registerScreenPlay("DantariVillageScreenPlay", true)

function DantariVillageScreenPlay:start()
	if (isZoneEnabled("danotooine")) then
		self:spawnMobiles()
	end
end

function DantariVillageScreenPlay:spawnMobiles()
	spawnMobile("dantooine", "dantari_battlelord",900,-3848.4,2,-5722.2,-50,0)
	spawnMobile("dantooine", "dantari_battlelord",900,-3839.2,6,-5696.3,-165,0)
	spawnMobile("dantooine", "dantari_battlelord",900,-3848.6,6,-5695,-170,0)
	spawnMobile("dantooine", "dantari_battlelord",900,-3865.1,2.5,-5696.2,-96,0)
	spawnMobile("dantooine", "dantari_battlelord",900,-3873.1,2.5,-5697.2,76,0)
	spawnMobile("dantooine", "dantari_battlelord",900,-7207.8,3,-913.9,160,0)
	spawnMobile("dantooine", "dantari_battlelord",900,-7202.1,3,-921.8,-78,0)
	spawnMobile("dantooine", "dantari_battlelord",900,-7242.2,3,-864,127,0)
	spawnMobile("dantooine", "dantari_battlelord",900,-7158.5,3,-836.6,-158,0)
	spawnMobile("dantooine", "dantari_battlelord",900,-7132.3,3,-894.6,-98,0)
	spawnMobile("dantooine", "dantari_battlelord",900,-7134.5,3,-886.6,-120,0)
	spawnMobile("dantooine", "dantari_battlelord",900,5584.4,0.5,-657.8,-88,0)
	spawnMobile("dantooine", "dantari_battlelord",900,5557.1,0.2,-619.2,154,0)
	spawnMobile("dantooine", "dantari_battlelord",900,5592.4,1.4,-619.1,-151,0)
	spawnMobile("dantooine", "dantari_battlelord",900,5593.2,0.8,-645.8,-76,0)
	
	spawnMobile("dantooine", "dantari_chief",900,-3839.3,8,-5753.5,30,0)
	spawnMobile("dantooine", "dantari_chief",900,-3886.9,2.5,-5686,-159,0)
	spawnMobile("dantooine", "dantari_chief",900,-7209.2,3,-923.1,32,0)
	spawnMobile("dantooine", "dantari_chief",900,5567,0.2,-648.2,-145,0)
	
	spawnMobile("dantooine", "dantari_raider",900,-3893.6,2.4,-5708.2,85,0)
	spawnMobile("dantooine", "dantari_raider",900,-3088.7,2.5,-5720.3,61,0)
	spawnMobile("dantooine", "dantari_raider",900,-3882.9,2.5,-5730.6,28,0)
	spawnMobile("dantooine", "dantari_raider",900,-3871.6,2.5,-5735.8,7,0)
	spawnMobile("dantooine", "dantari_raider",900,-3860.9,2.5,-5734.5,-49,0)
	spawnMobile("dantooine", "dantari_raider",900,-3797.3,5,-5717.5,-136,0)
	spawnMobile("dantooine", "dantari_raider",900,-3787.6,4.4,-5727.9,-120,0)
	spawnMobile("dantooine", "dantari_raider",900,-7166.9,3,-938.9,-26,0)
	spawnMobile("dantooine", "dantari_raider",900,-7186.7,3,-941.2,3,0)
	spawnMobile("dantooine", "dantari_raider",900,-7225.4,3,-898.7,41,0)
	spawnMobile("dantooine", "dantari_raider",900,-7242.7,3,-886.4,87,0)
	spawnMobile("dantooine", "dantari_raider",900,-7220.4,3,-856.4,169,0)
	spawnMobile("dantooine", "dantari_raider",900,-7180.3,3,-842.1,156,0)
	spawnMobile("dantooine", "dantari_raider",900,-7146.8,3,-856.4,-130,0)
	spawnMobile("dantooine", "dantari_raider",900,-7143.2,3,-913.4,-55,0)
	spawnMobile("dantooine", "dantari_raider",900,5514.5,0.4,-707.7,144,0)
	spawnMobile("dantooine", "dantari_raider",900,5540.9,0.2,-699,-74,0)
	spawnMobile("dantooine", "dantari_raider",900,5544.9,0.2,-678.5,136,0)
end
