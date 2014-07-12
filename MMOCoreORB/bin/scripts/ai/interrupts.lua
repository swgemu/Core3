require("ai.ai")

Interrupt = { }
function Interrupt:interrupt(pAgent, pObject, msg)
	if msg == STARTCOMBAT then self:startCombatInterrupt(pAgent, pObject)
	end
end

function Interrupt:startCombatInterrupt(pAgent, pObject)
end

DefaultInterrupt = createClass(Interrupt)
function DefaultInterrupt:startCombatInterrupt(pAgent, pObject)
	if (pAgent ~= pObject) then return end
	self:terminate(pAgent)
	if (pAgent ~= nil) then
		local agent = LuaAiAgent(pAgent)
		agent:setBehaviorStatus(BEHAVIOR_SUSPEND)
		agent:resetBehaviorList()
		agent:executeBehavior()
	end
end

PackInterrupt = createClass(DefaultInterrupt)
function PackInterrupt:startCombatInterrupt(pAgent, pObject)
	if (pAgent ~= pObject) then 
		self:terminate(pAgent)
		if (pAgent ~= nil) then
			local agent = LuaAiAgent(pAgent)
			-- TODO (dannuic): change the range to calculate based on level difference an ferocity
			if agent:checkRange(pObject, 15) then
				agent:assist(pObject)
			end
		end
	end
	DefaultInterrupt:startCombatInterrupt(pAgent, pObject)
end