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

--North East Tree(1 of 2)
	--On the ground
	spawnMobile("endor", "panshee_warrior",300,4528.7,20.1,-2376.6,82,0)--In the hutt
	spawnMobile("endor", "panshee_warrior",300,4531.1,20.2,-2392.6,170,0)--GuardingStairs
	--First Floor
	spawnMobile("endor", "panshee_tribesman",300,4519.6,30.3,-2378.1,106,0)--OverLook#1
	spawnMobile("endor", "panshee_shaman",300,4520.2,30,-2384.2,-84,0)--Hut
	spawnMobile("endor", "panshee_tribesman",300,4523.6,30,-2390.4,-122,0)--GaurdingBridge
	--Second Floor(Top Floor)
	spawnMobile("endor", "panshee_tribesman",300,4534.9,40.3,-2377.8,-148,0)--OverLook#1
	spawnMobile("endor", "panshee_tribesman",300,4519.2,40.3,-2377.2,139,0)--OverLook#2
	spawnMobile("endor", "panshee_shaman",300,4522.4,40.1,-2381.4,-45,0)--Hut#1
	spawnMobile("endor", "panshee_tribesman",300,4519.2,40.3,-2394.2,19,0)--OverLook#3
	spawnMobile("endor", "panshee_shaman",300,4528.2,40.1,-2392.3,166,0)--Hut#2
--South West Tree(1 of 2)
	--On the ground
	spawnMobile("endor", "panshee_warrior",300,4486.7,10.3,-2415.7,-11,0)--GuardingStairs
	--First Floor
	spawnMobile("endor", "panshee_tribesman",300,4499.1,20.3,-2430.1,-63,0)--OverLook#1
	spawnMobile("endor", "panshee_shaman",300,4497.9,20,-2423.2,96,0)--Hut
	spawnMobile("endor", "panshee_tribesman",300,4498.8,20.3,-2414.1,-147,0)--OverLook#1
	--Second Floor(Top Floor)
	spawnMobile("endor", "panshee_tribesman",300,4483.1,30.3,-2430,-148,0)--OverLook#1
	spawnMobile("endor", "panshee_shaman",300,4492.4,30.1,-2428.4,171,0)--Hut#1
	spawnMobile("endor", "panshee_tribesman",300,4499.2,30.3,-2429.9,-73,0)--OverLook#2
	spawnMobile("endor", "panshee_tribesman",300,4494.2,30.3,-2418.4,42,0)--GaurdingBridge
	spawnMobile("endor", "panshee_shaman",300,4490.2,30.1,-2415.9,-7,0)--Hut#2
--The Two Huts
	spawnMobile("endor", "panshee_shaman",300,4477.7,10.1,-2402.9,118,0)--Hut#1
	spawnMobile("endor", "panshee_shaman",300,4484.9,10.1,-2398.4,170,0)--Hut#2

--North Tree(1 of 4)
	--On the ground
	spawnMobile("endor", "panshee_warrior",300,4538.4,20,-2353.3,32,0)--In the hutt
	spawnMobile("endor", "panshee_warrior",300,4538.7,20,-2369.4,-158,0)--In the hutt with a basket
	spawnMobile("endor", "panshee_warrior",300,4541.4,20,-2372.2,-43,0)--Near the drying fish
	spawnMobile("endor", "panshee_warrior",300,4551,20.3,-2362.6,143,0)--GuardingStairs
	--First Floor
	spawnMobile("endor", "panshee_tribesman",300,4532.6,30.3,-2361.1,78,0)--OverLook#1
	spawnMobile("endor", "panshee_shaman",300,4538.2,30,-2365.2,-124,0)--Hut
	spawnMobile("endor", "panshee_tribesman",300,4544.6,30,-2366.4,-178,0)--GaurdingBridge
	--Second Floor(Top Floor)
	spawnMobile("endor", "panshee_tribesman",300,4543.9,40.3,-2349.8,163,0)--OverLook#1
	spawnMobile("endor", "panshee_shaman",300,4538.1,40.1,-2358.4,-73,0)--Hut#1
	spawnMobile("endor", "panshee_tribesman",300,4532.6,40.3,-2361.2,78,0)--OverLook#2
	spawnMobile("endor", "panshee_tribesman",300,4544.1,40.3,-2372.4,-14,0)--OverLook#3
	spawnMobile("endor", "panshee_shaman",300,4549.2,40.1,-2364.7,-159,0)--Hut#2
--East Tree(2 of 4)
	--On the ground
	spawnMobile("endor", "panshee_warrior",300,4591.4,10.2,-2399.6,148,0)--In the hutt with hide
	spawnMobile("endor", "panshee_warrior",300,4603.9,10,-2402.9,85,0)--Near the drying fish
	spawnMobile("endor", "panshee_warrior",300,4608,10,-2403.3,-133,0)--In the hutt with a basket
	spawnMobile("endor", "panshee_warrior",300,4595,10.4,-2420.8,130,0)--GuardingStairs
	--First Floor
	spawnMobile("endor", "panshee_tribesman",300,4595.5,20.3,-2401,153,0)--OverLook#1
	spawnMobile("endor", "panshee_shaman",300,4590,20.1,-2409,46,0)--Hut
	spawnMobile("endor", "panshee_tribesman",300,4584.5,20.3,-2413,77,0)--OverLook#2
	--Second Floor(Top Floor)
	spawnMobile("endor", "panshee_tribesman",300,4607.5,30.3,-2413,-100,0)--OverLook#1
	spawnMobile("endor", "panshee_shaman",300,4599.9,30.1,-2407.7,34,0)--Hut#1
	spawnMobile("endor", "panshee_tribesman",300,4595.5,30.3,-2401,154,0)--OverLook#2
	spawnMobile("endor", "panshee_shaman",300,4593.7,30,-2418,-159,0)--Hut#2
--Middle Tree(3 of 4)
	--On the ground
	spawnMobile("endor", "panshee_warrior",300,4550,20,-2420.8,61,0)--In the hutt with baskets
	spawnMobile("endor", "panshee_warrior",300,4542.5,20,-2403.3,-28,0)--In the hutt with bottles
	spawnMobile("endor", "panshee_warrior",300,4536,20.3,-2411,-51,0)--GuardingStairs
	--First Floor
	spawnMobile("endor", "panshee_warrior",300,4550,30,-2414,121,0)--Guard
	spawnMobile("endor", "panshee_shaman",300,4547.8,30.1,-2408,34,0)--Hut
	spawnMobile("endor", "panshee_tribesman",300,4543,30.3,-2402,175,0)--GuardingBridge
	--Second Floor(Top Floor)
	spawnMobile("endor", "panshee_tribesman",300,4543.9,40.3,-2423.9,-4,0)--GuardingBridge
	spawnMobile("endor", "panshee_tribesman",300,4555.5,40.3,-2413,-118,0)--OverLook#1
	spawnMobile("endor", "panshee_shaman",300,4550,40.1,-2413,147,0)--Hut#1
	spawnMobile("endor", "panshee_tribesman",300,4544.5,40.3,-2401,154,0)--OverLook#2
	spawnMobile("endor", "panshee_shaman",300,4539.7,40,-2408,-37,0)--Hut#2
--South Tree(4 of 4)
	--On the ground
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
	spawnMobile("endor", "panshee_tribesman",300,4544,50.3,-2476,-24,0)--OverLook#1
	spawnMobile("endor", "panshee_shaman",300,4547.7,50.1,-2470.1,147,0)--Hut#1
	spawnMobile("endor", "panshee_tribesman",300,4555.5,50.3,-2464,-109,0)--OverLook#2
	spawnMobile("endor", "panshee_tribesman",300,4544.5,50.3,-2453,150,0)--OverLook#3
	spawnMobile("endor", "panshee_shaman",300,4540.7,50,-2460,-35,0)--Hut#2

end
