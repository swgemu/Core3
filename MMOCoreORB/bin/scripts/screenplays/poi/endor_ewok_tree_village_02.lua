--Coded By: NickWill86

EndorEwokTreeVillage02ScreenPlay = ScreenPlay:new {
	numberOfActs = 1,

}

registerScreenPlay("EndorEwokTreeVillage02ScreenPlay", true)

function EndorEwokTreeVillage02ScreenPlay:start()
	if (isZoneEnabled("endor")) then
		self:spawnMobiles()
	end
end

function EndorEwokTreeVillage02ScreenPlay:spawnMobiles()
--Tree # 1
	--On the ground..
	spawnMobile("endor", "panshee_warrior",300,4553,30,-2466,3,0)--Near The Drying Fish
	spawnMobile("endor", "panshee_warrior",300,4554,30,-2472,-179,0)--Near The Spears
	spawnMobile("endor", "panshee_warrior",300,4559,30,-2472,159,0)--Near the Basket
	spawnMobile("endor", "panshee_warrior",300,4536,30.3,-2464,-28,0)--GuardingStairs
	--First Floor
	spawnMobile("endor", "panshee_warrior",300,4550,40,-2466,121,0)--Guard
	spawnMobile("endor", "panshee_tribesman",300,4555,40.3,-2464,-120,0)--OverLook#1
	spawnMobile("endor", "panshee_shaman",300,4547.8,40.1,-2460,34,0)--Hut
	spawnMobile("endor", "panshee_tribesman",300,4542,40,-2455,120,0)--GuardingBridge
	--Second Floor(Top Floor)
	spawnMobile("endor", "panshee_tribesman",300,2544,50.3,-2476,-32,0)--OverLook#1
	--spawnMobile("endor", "panshee_shaman",300,59,29,45,-45,0)--Hut#1
	--spawnMobile("endor", "panshee_tribesman",300,52,29,40,45,0)--OverLook#2
	--spawnMobile("endor", "panshee_shaman",300,59,29,35,-135,0)--Hut#2

end
