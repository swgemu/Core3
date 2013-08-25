NabooAbandonedImperialOutputScreenPlay = ScreenPlay:new {
	numberOfActs = 1,
	
	screenplayName = "NabooAbandonedImperialOutputScreenPlay",

}

registerScreenPlay("NabooAbandonedImperialOutputScreenPlay", true)

function NabooAbandonedImperialOutputScreenPlay:start()
	if (isZoneEnabled("naboo")) then
		self:spawnMobiles()

	end
end

function NabooAbandonedImperialOutputScreenPlay:spawnMobiles()

	-- Outside
	spawnMobile("naboo", "thief", 180, 964.6, 261.1, -1345.6, 158, 0)
	spawnMobile("naboo", "scavenger", 180, 975.0, 262.2, -1332.9, -132, 0)	
	
	-- Corridor
	spawnMobile("naboo", "nightspider", 180, 3.8, 0.5, -3.6, -62, 7825776)
	spawnMobile("naboo", "nightspider", 180, 3.8, 0.5, 2.9, 172, 7825777)
	spawnMobile("naboo", "nightspider", 180, -1.9, 2.0, 3.4, 66, 7825777)
	
	-- Top floor
	spawnMobile("naboo", "nightspider", 180, 971.0, 267.5, -1341.7, 113, 0 )
	spawnMobile("naboo", "nightspider_aggressor", 180, 974.1, 267.5, -1341.9, -121, 0 )
	spawnMobile("naboo", "nightspider_poison_spitter", 180, 977.1, 267.5, -1343.6, -173, 0 )
	spawnMobile("naboo", "nightspider_aggressor", 180, 972.2, 267.5, -1345.1, 7, 0 )
end
