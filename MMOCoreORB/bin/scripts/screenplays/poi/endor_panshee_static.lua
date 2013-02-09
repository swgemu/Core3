EndorPansheeStaticScreenPlay = ScreenPlay:new {
	numberOfActs = 1,

}

registerScreenPlay("EndorPansheeStaticScreenPlay", true)

function EndorPansheeStaticScreenPlay:start()
	self:spawnMobiles()
end

function EndorPansheeStaticScreenPlay:spawnMobiles()  
	spawnMobile("endor", "weathered_panshee_shaman", 300, -7555.3, 271.2, 4452.2, 147, 0)
	spawnMobile("endor", "panshee_warrior", 300, -5441.6, 184.11, -2184.3, -19, 0)
	spawnMobile("endor", "panshee_warrior", 300, -5447.3, 182.2, -2177.4, -14, 0)
	spawnMobile("endor", "panshee_warrior", 300, -5465.1, 185.2, -2180.5, -55, 0)
	spawnMobile("endor", "panshee_warrior", 300, -5466.8, 185.3, -2182.1, -53, 0)
	spawnMobile("endor", "archaic_panshee_ritualist", 300, -5450.6, 183.8, -2193.6, 114, 0)
end
