require("ai.ai")

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

Wait10Base = createClass(WaitBase)

function Wait10Base:setWait(pAgent)
	if (pAgent ~= nil) then
		local agent = AiAgent(pAgent)
		agent:setWait(getRandomNumber(10) + 5)
	end
end

Wait10VillageRaiderBase = createClass(Wait10Base)

function Wait10VillageRaiderBase:checkConditions(pAgent)
	if (pAgent ~= nil) then
		local agent = AiAgent(pAgent)
		if (agent:isInRangeOfHome(20)) then
			return true
		end
	end
	return false
end
