EndorJindaStaticScreenPlay = ScreenPlay:new {
	numberOfActs = 1,

}

registerScreenPlay("EndorJindaStaticScreenPlay", true)

function EndorJindaStaticScreenPlay:start()
	self:spawnMobiles()
end

function EndorJindaStaticScreenPlay:spawnMobiles()    
	spawnMobile("endor", "jinda_worker",300, -3824.6, 2.5, -1874.2, 136, 0)
	spawnMobile("endor", "jinda_worker",300, -3821.0, 2.4, -1876.9, 32, 0)
	spawnMobile("endor", "jinda_warrior",300, -3824.7, 3.2, -1878.4, -151, 0)
end
