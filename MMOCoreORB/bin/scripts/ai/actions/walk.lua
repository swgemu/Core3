require("ai.actions.move")
require("ai.interrupts")

WalkBase = createClass(MoveBase)

-- overrides so that we walk instead of run
function WalkBase:findNextPosition(pAgent)
	if (pAgent ~= nil) then
		local agent = AiAgent(pAgent)
		if (agent:findNextPosition(agent:getMaxDistance(), true)) then
			return true
		end
	end
	return false
end

Walk = createClass(WalkBase, Interrupt)
WalkDefault = createClass(WalkBase, DefaultInterrupt)
WalkPack = createClass(WalkBase, PackInterrupt)