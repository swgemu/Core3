EndorMarauderStrongholdScreenPlay = ScreenPlay:new {
	numberOfActs = 1,

	screenplayName = "EndorMarauderStrongholdScreenPlay",

}

registerScreenPlay("EndorMarauderStrongholdScreenPlay", true)

function EndorMarauderStrongholdScreenPlay:start()
	if (isZoneEnabled("endor")) then
		self:spawnMobiles()
	end
end

function EndorMarauderStrongholdScreenPlay:spawnMobiles()

	local pNpc = spawnMobile("endor", "grassland_blood_marauder", 1200, -4702.4, 82.0, -2284.3, -179, 0)
	self:setMoodString(pNpc, "angry")
	pNpc = spawnMobile("endor", "marauder", 1200, -4715.4, 82.0, -2272.4, -48, 0)
	self:setMoodString(pNpc, "npc_sitting_table_eating")
	spawnMobile("endor", "marauder", 900, -4668.1, 82.2, -2276.4, -85, 0)
	spawnMobile("endor", "marauder", 900, -4667.7, 82.3, -2270.5, -85, 0)
	spawnMobile("endor", "marauder", 900, -4623.3, 92.0, -2277.5, -23, 0)
	spawnMobile("endor", "marauder", 900, -4598.4, 98.8, -2268.2, -127, 0)
	spawnMobile("endor", "marauder", 900, -4598.0, 98.9, -2277.2, -69, 0)

end