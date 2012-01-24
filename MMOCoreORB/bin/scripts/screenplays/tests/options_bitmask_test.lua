options_bitmask_test = ScreenPlay:new {
	numberOfActs = 1,
}

registerScreenPlay("options_bitmask_test", true)

function options_bitmask_test:start()
	if (not isZoneEnabled("simple")) then
		return 0
	end

	for i = -1, i < 32 do
		local pMobile = spawnMobile("simple", "dolac_legasi", 0, 0 + i, 0, 0, 0, 0)
		local mobile = LuaCreatureObject(pMobile)
		
		if (i == -1) then
			mobile:setOptionsBitmask(0)
		else
			mobile:setOptionsBitmask(2^i)
		end
	end
	
	return 0
end