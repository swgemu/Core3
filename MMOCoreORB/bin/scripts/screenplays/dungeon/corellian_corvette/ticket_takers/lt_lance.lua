lt_lance = { planetName = "corellia", npcTemplate = "lt_lance", x = -6518.5, z = 398.0, y = 6044.1, direction = -18, cellID = 0, position = STAND }

ticketTakerLtLance = CorvetteTicketTakerLogic:new {
	numberOfActs = 1,
	npc = lt_lance,
	takerName = "ticketTakerLtLance",
	faction = FACTIONREBEL,
	goodbyeString = "@conversation/corvette_rebel_pilot:s_6e257495", -- No, I'm just passing through.
	helpMeString = "@conversation/corvette_rebel_pilot:s_1a003c0e", -- Ah no. I hear you can help me intercept a Corellian corvette controlled by the Empire?
	nevermindString = "@conversation/corvette_rebel_pilot:s_1a71d76e", -- Um... nothing. Nevermind.
	aboutMissionString = "@conversation/corvette_rebel_pilot:s_1ab00f5e", -- [Tell him about your mission]
}

registerScreenPlay("ticketTakerLtLance", true)

ticketTakerLtLanceConvoHandler = CorvetteTicketTakerConvoHandler:new {
	ticketTaker = ticketTakerLtLance
}
