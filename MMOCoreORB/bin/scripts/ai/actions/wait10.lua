require("ai.actions.wait")
require("ai.interrupts")

Wait10Base = createClass(WaitBase)

function Wait10Base:setWait(pAgent)
	if (pAgent ~= nil) then
		local agent = AiAgent(pAgent)
		agent:setWait(getRandomNumber(10) + 5)
	end
end

Wait10 = createClass(Wait10Base, Interrupt)
Wait10Default = createClass(Wait10Base, DefaultInterrupt)
Wait10Pack = createClass(Wait10Base, PackInterrupt)
Wait10CreaturePet = createClass(Wait10Base, CreaturePetInterrupt)
Wait10DroidPet = createClass(Wait10Base, DroidPetInterrupt)
Wait10FactionPet = createClass(Wait10Base, FactionPetInterrupt)

function Wait10CreaturePet:setWait(pAgent)
	if (pAgent ~= nil) then
		local agent = AiAgent(pAgent)
		if agent:getFollowState() == PATROLLING then
			agent:setWait(5)
		end
	end
end

function Wait10DroidPet:setWait(pAgent)
	if (pAgent ~= nil) then
		local agent = AiAgent(pAgent)
		if agent:getFollowState() == PATROLLING then
			agent:setWait(5)
		end
	end
end

function Wait10FactionPet:setWait(pAgent)
	if (pAgent ~= nil) then
		local agent = AiAgent(pAgent)
		if agent:getFollowState() == PATROLLING then
			agent:setWait(5)
		end
	end
end
