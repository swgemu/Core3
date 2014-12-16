require("ai.ai")

CompositeBase = createClass(Ai)

function CompositeBase:doAction(pAgent)
	if (pAgent ~= nil) then
		local agent = AiAgent(pAgent)
		local res = agent:getBehaviorStatus()
		return res
	else
		return BEHAVIOR_INVALID
	end
end

Composite = createClass(CompositeBase, Interrupt)
CompositeDefault = createClass(CompositeBase, DefaultInterrupt)
CompositePack = createClass(CompositeBase, PackInterrupt)
CompositeCreaturePet = createClass(CompositeBase, CreaturePetInterrupt)
CompositeDroidPet = createClass(CompositeBase, DroidPetInterrupt)
CompositeFactionPet = createClass(CompositeBase, FactionPetInterrupt)