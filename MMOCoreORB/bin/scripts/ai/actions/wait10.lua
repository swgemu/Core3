Wait10 = Wait:new {}

function Wait10:setWait(pAgent)
	if (pAgent ~= nil) then
		local agent = LuaAiAgent(pAgent)
		agent:setWait(10)
	end
end