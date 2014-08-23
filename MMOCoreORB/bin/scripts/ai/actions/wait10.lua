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