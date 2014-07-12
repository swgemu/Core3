Walk = Move:new {}

-- overrides so that we walk instead of run
function Walk:findNextPosition(pAgent)
	if (pAgent ~= nil) then
		local agent = LuaAiAgent(pAgent)
		if (agent:findNextPosition(agent:getMaxDistance(), true)) then
			return true
		end
	end
	return false
end