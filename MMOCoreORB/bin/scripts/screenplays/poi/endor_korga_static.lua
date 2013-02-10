EndorKorgaStaticScreenPlay = ScreenPlay:new {
	numberOfActs = 1,

}

registerScreenPlay("EndorKorgaStaticScreenPlay", true)

function EndorKorgaStaticScreenPlay:start()
	if (isZoneEnabled("endor")) then
		self:spawnMobiles()
	end
end

function EndorKorgaStaticScreenPlay:spawnMobiles()    
	spawnMobile("endor", "korga_ancient",300, -1793.9, 399.6, 6013.9, -37, 0)
	spawnMobile("endor", "tainted_korga_dark_shaman",300, -5888.5, 23.3, 2358.4, -91, 0)
	spawnMobile("endor", "tricky_korga_scout",300, -6800.4, 108.4, -3445.0, 14, 0)
	spawnMobile("endor", "tricky_korga_scout",300, -6795.7, 107.6, -3452.7, 90, 0)
end
