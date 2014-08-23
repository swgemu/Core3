require("ai.ai")
require("ai.interrupts")

WaitBase = createClass(Ai)

function WaitBase:start(pAgent)
	self:setWait(pAgent)
	
	return 0
end

function WaitBase:doAction(pAgent)
	if (pAgent ~= nil) then
		local agent = AiAgent(pAgent)
		if (agent:isWaiting()) then
			return BEHAVIOR_RUNNING
		end
	end
	return BEHAVIOR_SUCCESS
end

function WaitBase:terminate(pAgent)
	if (pAgent ~= nil) then
		local agent = AiAgent(pAgent)
		agent:setWait(0)
	end
	
	return 0
end

-- By default, wait indefinitely
function WaitBase:setWait(pAgent)
	if (pAgent ~= nil) then
		local agent = AiAgent(pAgent)
		agent:setWait(-1)
	end
end

Wait = createClass(WaitBase, Interrupt)
WaitDefault = createClass(WaitBase, DefaultInterrupt)
WaitPack = createClass(WaitBase, PackInterrupt)
WaitPet = createClass(WaitBase, PetInterrupt)