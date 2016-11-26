DathomirTradeOutpostScreenPlay = ScreenPlay:new {
	numberOfActs = 1,

	screenplayName = "DathomirTradeOutpostScreenPlay"
}

registerScreenPlay("DathomirTradeOutpostScreenPlay", true)

function DathomirTradeOutpostScreenPlay:start()
	if (isZoneEnabled("dathomir")) then
		self:spawnMobiles()
	end
end

function DathomirTradeOutpostScreenPlay:spawnMobiles()

	--In buildings
	local pNpc = spawnMobile("dathomir", "scientist",60,5.7,0.6,-6.3,-132,6955370)
	self:setMoodString(pNpc, "conversation")
	spawnMobile("dathomir", "noble", 60, 3.00888, 0.125266, -2.92449, -90, 1392894)
	spawnMobile("dathomir", "businessman", 60, 6.94935, 0.624998, 2.6394, 198.079, 6955367)
	spawnMobile("dathomir", "businessman", 60, -8.09806, 0.625, 4.31086, 153.675, 6955368)
	spawnMobile("dathomir", "nirame_sakute", 60, -2.1912, 0.624999, -6.92293, 24.0649, 6955369)

	--Outside
	spawnMobile("dathomir", "businessman", 60, 590.176, 6, 3058.45, 264.528, 0)
	spawnMobile("dathomir", "businessman", 60, 594.44, 6, 3087.13, 181.146, 0)
	spawnMobile("dathomir", "businessman", 60, 614.681, 6, 3081.65, 80.4705, 0)
	spawnMobile("dathomir", "commoner", 60, 585.943, 6, 3051.56, 118.776, 0)
	spawnMobile("dathomir", "commoner", 60, 598.679, 6, 3046.85, 261.619, 0)
	spawnMobile("dathomir", "commoner", 60, 577.196, 6, 3100.6, 52.588, 0)
	spawnMobile("dathomir", "commoner", 60, 585.757, 6, 3072.92, 217.734, 0)
	spawnMobile("dathomir", "commoner", 60, 621.667, 6, 3092.75, 351.148, 0)
	spawnMobile("dathomir", "commoner", 60, 605.584, 6, 3080.71, 149.629, 0)
	spawnMobile("dathomir", "commoner", 60, 616.733, 6, 3056.95, 135.38, 0)
	spawnMobile("dathomir", "commoner", 60, 618.605, 6, 3071.68, 172.714, 0)
	spawnMobile("dathomir", "mercenary", 60, 578.316, 6, 3092.44, 253.37, 0)
	spawnMobile("dathomir", "mercenary", 60, 566.589, 6, 3070.58, 284.249, 0)
	spawnMobile("dathomir", "mercenary", 60, 559.148, 6, 3076.83, 297.739, 0)
	spawnMobile("dathomir", "mercenary", 60, 584.255, 6, 3094.17, 253.409, 0)
	spawnMobile("dathomir", "scientist", 60, 623.05, 6, 3037.98, 54.874, 0)
	spawnMobile("dathomir", "informant_npc_lvl_3", 0,590,6,3091,-31,0)
	spawnMobile("dathomir", "informant_npc_lvl_3", 0,598,6,3025,180,0)
	spawnMobile("dathomir", "r4", 60, 620.654, 6, 3085.98, 191.123, 0)
	spawnMobile("dathomir", "r4", 60, 619.822, 6, 3097.36, 339.758, 0)
	spawnMobile("dathomir", "r5", 60, 627.744, 6, 3086.77, 278.522, 0)
end
