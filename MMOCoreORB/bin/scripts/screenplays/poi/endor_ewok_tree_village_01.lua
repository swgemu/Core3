EwokTreeVillage01ScreenPlay = ScreenPlay:new {
	numberOfActs = 1,

	screenplayName = "EwokTreeVillage01ScreenPlay",

	lootContainers = {
		5035775
	},

	lootLevel = 38,

	lootGroups = {
		{
			groups = {
				{group = "color_crystals", chance = 3500000},
				{group = "junk", chance = 3500000},
				{group = "rifles", chance = 1000000},
				{group = "pistols", chance = 1000000},
				{group = "clothing_attachments", chance = 500000},
				{group = "armor_attachments", chance = 500000}
			},
			lootChance = 8000000
		}
	},

	lootContainerRespawn = 1800 -- 30 minutes
}

registerScreenPlay("EwokTreeVillage01ScreenPlay", true)

function EwokTreeVillage01ScreenPlay:start()
	if (isZoneEnabled("endor")) then
		self:spawnMobiles()
		self:initializeLootContainers()
	end
end

function EwokTreeVillage01ScreenPlay:spawnMobiles()

--Tree # 1
	--On the ground
	spawnMobile("endor", "panshee_warrior",10,66,9,50,40,0)--FurthestHutFromStairs(4/4)
	spawnMobile("endor", "panshee_warrior",10,77,9,37,45,0)--GuardNearTikiTourch	
	spawnMobile("endor", "panshee_warrior",10,78,9,40,135,0)--GuardNearTikiTourch
	spawnMobile("endor", "panshee_warrior",10,61,9,32,-135,0)--GuardingStairs
	--First Floor
	spawnMobile("endor", "panshee_warrior",10,66,19,48,135,0)--Guard
	spawnMobile("endor", "panshee_tribesman",10,62,19,52,135,0)--OverLook#1
	spawnMobile("endor", "panshee_shaman",10,59,19,46,-30,0)--Hut
	spawnMobile("endor", "panshee_tribesman",10,51,19,40,45,0)--OverLook#2
	--Second Floor(Top Floor)
	spawnMobile("endor", "panshee_warrior",10,69,29,41,135,0)--Two Guards
	spawnMobile("endor", "panshee_warrior",10,70,29,42,135,0)--Two Guards
	spawnMobile("endor", "panshee_tribesman",10,62,29,52,135,0)--OverLook#1
	spawnMobile("endor", "panshee_shaman",10,59,29,45,-45,0)--Hut#1
	spawnMobile("endor", "panshee_tribesman",10,52,29,40,45,0)--OverLook#2
	spawnMobile("endor", "panshee_shaman",10,59,29,35,-135,0)--Hut#2


end
