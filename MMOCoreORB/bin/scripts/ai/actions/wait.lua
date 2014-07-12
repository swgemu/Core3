require("ai.ai")
require("ai.interrupts")

--Wait = Ai:new {}
WaitBase = createClass(Ai)

function WaitBase:start(pAgent)
	self:setWait(pAgent)
	
	return 0
end

function WaitBase:doAction(pAgent)
	if (pAgent ~= nil) then
		local agent = LuaAiAgent(pAgent)
		if (agent:isWaiting()) then
			return BEHAVIOR_RUNNING
		end
	end
	return BEHAVIOR_SUCCESS
end

function WaitBase:terminate(pAgent)
	if (pAgent ~= nil) then
		local agent = LuaAiAgent(pAgent)
		agent:setWait(0)
	end
	
	return 0
end

-- By default, wait indefinitely
function WaitBase:setWait(pAgent)
	if (pAgent ~= nil) then
		local agent = LuaAiAgent(pAgent)
		agent:setWait(-1)
	end
end

--[[function Wait:interrupt(pAgent, pObject, msg)
	if msg == STARTCOMBAT and pAgent == pObject then
		Ai:startCombatInterrupt(pAgent, pObject)
	end
	
	return 0
end]]

Wait = createClass(WaitBase, Interrupt)
WaitDefault = createClass(WaitBase, DefaultInterrupt)
WaitPack = createClass(WaitBase, PackInterrupt)