EndorPubamStaticScreenPlay = ScreenPlay:new {
	numberOfActs = 1,

}

registerScreenPlay("EndorPubamStaticScreenPlay", true)

function EndorPubamStaticScreenPlay:start()
	if (isZoneEnabled("endor")) then
		self:spawnMobiles()
	end
end

function EndorPubamStaticScreenPlay:spawnMobiles()    
	spawnMobile("endor", "tainted_pubam_dark_shaman",300, -6880.6, 205.4, 1364.0, 93, 0)

--	spawnMobile("endor", "ewok_outcast",300,  0)
end
