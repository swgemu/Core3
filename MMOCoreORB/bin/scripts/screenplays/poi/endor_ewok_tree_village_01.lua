--My first code for SWGEmu!
--Coded By: NickWill86
--This is only a sample of this POI, if you like where the Ewoks are placed, i will added more to the other trees around it.

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
	spawnMobile("endor", "panshee_warrior",300,66,9,50,40,0)--FurthestHutFromStairs(4/4)
	spawnMobile("endor", "panshee_warrior",300,77,9,37,45,0)--GuardNearTikiTourch	
	spawnMobile("endor", "panshee_warrior",300,78,9,40,135,0)--GuardNearTikiTourch
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


end
