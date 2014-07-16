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
		if (pAgent ~= nil and pObject ~= nil) then
			local agent = LuaAiAgent(pAgent)
			local scno = LuaSceneObject(pObject)
			if scno:isAiAgent() then
				local source = LuaAiAgent(pObject)
				if source:getSocialGroup() ~= agent:getSocialGroup() or not agent:checkLineOfSight(pObject) then
					return
				end
			end

			-- if the source is not an AiAgent (like a lair) then don't check social group
			-- TODO (dannuic): change the range to calculate based on level difference and ferocity
			if agent:checkRange(pObject, 15) then
				agent:assist(pObject)
			end
		end
	end

	DefaultInterrupt:startCombatInterrupt(pAgent, pObject)
end

PetInterrupt = createClass(DefaultInterrupt)
function PetInterrupt:startCombatInterrupt(pAgent, pObject)
	if pAgent == nil or pObject == nil then return end
	local agent = LuaAiAgent(pAgent)
	if agent:getOwner() ~= pObject then return end -- this is where the friend checks will go
	DefaultInterrupt:startCombatInterrupt(pAgent, pObject)
	agent:setBehaviorStatus(BEHAVIOR_SUSPEND)
	agent:resetBehaviorList()
	agent:executeBehavior()
end
