Wait10 = Ai:new {}

function Wait10:start(pAgent)
	if (pAgent ~= nil) then
		local agent = LuaAiAgent(pAgent)
		agent:setWait(10)
	end
	return 0
end

addAiBehavior("Wait10")