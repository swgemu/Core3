--My first code for SWGEmu!
--Coded By: NickWill86

EndorEwokTreeVillage01ScreenPlay = ScreenPlay:new {
	numberOfActs = 1,

}

registerScreenPlay("EndorEwokTreeVillage01ScreenPlay", true)

function EndorEwokTreeVillage01ScreenPlay:start()
	if (isZoneEnabled("endor")) then
		self:spawnMobiles()
	end
end

function EndorEwokTreeVillage01ScreenPlay:spawnMobiles()

--Tree # 1
	--On the ground
	spawnMobile("endor", "panshee_warrior",300,66,9,50,40,0)--FurthestEwokHutFromStairs(4/4)
	spawnMobile("endor", "panshee_warrior",300,71.5,9,46.6,54,0)--EwokHutFromStairs(3/4)
	spawnMobile("endor", "panshee_warrior",300,77,9,37,45,0)--GuardNearTikiTourch(2/4)
	spawnMobile("endor", "panshee_warrior",300,78,9,40,135,0)--GuardNearTikiTourch(1/4)
	spawnMobile("endor", "panshee_warrior",300,61,9,32,-135,0)--GuardingStairs
	--First Floor
	spawnMobile("endor", "panshee_warrior",300,66,19,48,135,0)--Guard
	spawnMobile("endor", "panshee_tribesman",300,62,19,52,135,0)--OverLook#1
	spawnMobile("endor", "panshee_shaman",300,59,19,46,-30,0)--Hut
	spawnMobile("endor", "panshee_tribesman",300,51,19,40,45,0)--OverLook#2
	--Second Floor(Top Floor)
	spawnMobile("endor", "panshee_warrior",300,69,29,41,135,0)--Two Guards
	spawnMobile("endor", "panshee_warrior",300,70,29,42,135,0)--Two Guards
	spawnMobile("endor", "panshee_tribesman",300,62,29,52,135,0)--OverLook#1
	spawnMobile("endor", "panshee_shaman",300,59,29,45,-45,0)--Hut#1
	spawnMobile("endor", "panshee_tribesman",300,52,29,40,45,0)--OverLook#2
	spawnMobile("endor", "panshee_shaman",300,59,29,35,-135,0)--Hut#2

--Tree # 2
	--On the ground
	spawnMobile("endor", "panshee_warrior",300,86.6,9,63.1,170,0)--FurthestEwokHutFromStairs(1/1)
	spawnMobile("endor", "panshee_warrior",300,75.7,9,63.5,175,0)--GuardNearTikiTourch(1/4)
	spawnMobile("endor", "panshee_warrior",300,83.3,9.3,79.8,48,0)--GuardingStairs
	--First Floor
	spawnMobile("endor", "panshee_warrior",300,80.5,19,66.6,-148,0)--Guard
	spawnMobile("endor", "panshee_shaman",300,86.4,19.1,67.1,144,0)--Hut
	--Second Floor
	spawnMobile("endor", "panshee_tribesman",300,71,29.3,71.7,48,0)--OverLook#1
	spawnMobile("endor", "panshee_shaman",300,78.7,29.1,67,-149,0)--Hut
	spawnMobile("endor", "panshee_tribesman",300,82.6,29.3,60.9,-4,0)--OverLook#2
	spawnMobile("endor", "panshee_shaman",300,86.1,29.1,77.5,38,0)--Hut#2

--Tree # 3
	--On the ground
	spawnMobile("endor", "panshee_warrior",300,72.8,9,21.7,27,0)--GuardNearTikiTourch(3/3)
	spawnMobile("endor", "panshee_warrior",300,75.6,9,24.5,-117,0)--GuardNearTikiTourch(2/3)
	spawnMobile("endor", "panshee_warrior",300,93.4,9,19.1,-16,0)--GuardNearTikiTourch(1/3)
	spawnMobile("endor", "panshee_warrior",300,81.5,9.3,3.1,-146,0)--GuardingStairs
	--First Floor
	spawnMobile("endor", "panshee_warrior",300,83.2,19,16.6,33,0)--Guard
	spawnMobile("endor", "panshee_shaman",300,77.7,19.1,13.9,-56,0)--Hut
	spawnMobile("endor", "panshee_tribesman",300,71.2,19.3,10.4,62,0)--OverLook#1
	--Second Floor
	spawnMobile("endor", "panshee_tribesman",300,93.8,29.3,10.9,-125,0)--OverLook#1
	spawnMobile("endor", "panshee_tribesman",300,82.4,29.3,21.9,171,0)--OverLook#2
	spawnMobile("endor", "panshee_tribesman",300,70.9,29.3,10.3,61,0)--OverLook#2
	spawnMobile("endor", "panshee_shaman",300,77.8,29,7.2,-124,0)--Hut
--Tree # 4
	--On the ground
	spawnMobile("endor", "panshee_warrior",300,96.2,9,61.9,157,0)--GuardNearFire(2/2)
	spawnMobile("endor", "panshee_warrior",300,98.8,9,59.3,-94,0)--GuardNearFire(1/2)
	spawnMobile("endor", "panshee_warrior",300,112.7,9.3,71.4,159,0)--GuardingStairs
	--First Floor
	spawnMobile("endor", "panshee_warrior",300,99.2,19,73.8,-61,0)--Guard
	spawnMobile("endor", "panshee_shaman",300,101.1,19.1,67.4,-146,0)--Hut
	spawnMobile("endor", "panshee_tribesman",300,105.3,19.3,61.2,-37,0)--OverLook#1
	--Second Floor
	spawnMobile("endor", "panshee_tribesman",300,104.2,29.3,83.3,141,0)--OverLook#1
	spawnMobile("endor", "panshee_shaman",300,101.3,29.1,77.7,-36,0)--Hut#1
	spawnMobile("endor", "panshee_shaman",300,110.3,29,68.8,116,0)--Hut#2
--Tree # 5
	--On the ground
	spawnMobile("endor", "panshee_warrior",300,95.5,9,36.7,-118,0)--FurthestEwokHutFromStairs(1/1)
	spawnMobile("endor", "panshee_warrior",300,94.6,9,48.3,-9,0)--GuardNearFire(2/2)
	spawnMobile("endor", "panshee_warrior",300,97.3,9,51,-78,0)--GuardNearFire(1/2)
	spawnMobile("endor", "panshee_warrior",300,112.5,9.3,39.5,126,0)--GuardingStairs
	--First Floor
	spawnMobile("endor", "panshee_warrior",300,93.7,19.3,40.1,50,0)--Guard
	spawnMobile("endor", "panshee_shaman",300,100,19.0,36.7,-124,0)--Hut
	spawnMobile("endor", "panshee_tribesman",300,105.1,19.3,29.1,-35,0)--OverLook#1
	--Second Floor
	spawnMobile("endor", "panshee_tribesman",300,104.4,29,46.6,7,0)--OverPassGuard#1
	spawnMobile("endor", "panshee_tribesman",300,99,29,40.6,-88,0)--OverPassGuard#2
	spawnMobile("endor", "panshee_tribesman",300,105.5,29.3,29.1,-36,0)--OverLook#1
	spawnMobile("endor", "panshee_shaman",300,110.1,29.1,37.2,126,0)--Hut#1
end
