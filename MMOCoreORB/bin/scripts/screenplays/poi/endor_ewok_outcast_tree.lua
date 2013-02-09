EndorEwokOutcastTreeScreenPlay = ScreenPlay:new {
	numberOfActs = 1,

}

registerScreenPlay("EndorEwokOutcastTreeScreenPlay", true)

function EndorEwokOutcastTreeScreenPlay:start()
	self:spawnMobiles()
end

function EndorEwokOutcastTreeScreenPlay:spawnMobiles()
    	spawnMobile("endor", "ewok_outcast",300, -4800.3, 19.9, 1147.4, -126, 0)
	spawnMobile("endor", "ewok_outcast",300, -4784.1, 19.9, 1143.3, 94, 0)
	spawnMobile("endor", "ewok_outcast",300, -4793.8, 9.9, 1150.3, 94, 0)
	spawnMobile("endor", "ewok_outcast",300, -4802.6, 0.2, 1146.7, -71, 0)
	spawnMobile("endor", "ewok_outcast_raider",300, -4827.9, 0.7, 1160.6, 85, 0)
end
