spacestation_rebel_convotemplate = ConvoTemplate:new {
	initialScreen = "spacestation_rebel_greeting",
	templateType = "Lua",
	luaClassHandler = "SpacestationRebelConvoHandler",
	screens = {}
}

-- Initial Greeting
spacestation_rebel_greeting = ConvoScreen:new {
	id = "spacestation_rebel_greeting",
	leftDialog = "@conversation/pvp_station_rebel:s_e7fb4e63", --Welcome to the Rebel Alliance Space Station, %TU. Would you like to declare your affiliation with the Rebel Alliance?
	stopConversation = "false",
	options = {
		{"@conversation/pvp_station_rebel:s_370822d1", "spacestation_rebel_declare"}, --Yes
		{"@conversation/pvp_station_rebel:s_457a7010", "spacestation_rebel_decline"}, --No
		{"@conversation/pvp_station_rebel:s_dd67013", "spacestation_rebel_explain_01"}, --What does that mean?
	}
}
spacestation_rebel_convotemplate:addScreen(spacestation_rebel_greeting);

--out of range
out_of_range = ConvoScreen:new {
	id = "out_of_range",
	leftDialog = "@conversation/pvp_station_rebel:s_48f82131", --You need to move closer to this station.
	stopConversation = "true",
	options = {}
}
spacestation_rebel_convotemplate:addScreen(out_of_range);

--Neutral Greeting
spacestation_neutral_greeting = ConvoScreen:new {
	id = "spacestation_neutral_greeting",
	leftDialog = "@conversation/pvp_station_rebel:s_17456755", --Sign up with the Rebel Alliance and we'll talk.
	stopConversation = "true",
	options = {}
}
spacestation_rebel_convotemplate:addScreen(spacestation_neutral_greeting);

--Imperial Greeting
spacestation_imperial_greeting = ConvoScreen:new {
	id = "spacestation_imperial_greeting",
	leftDialog = "@conversation/pvp_station_rebel:s_514ace33", --You are not welcome at this station!
	stopConversation = "true",
	options = {}
}
spacestation_rebel_convotemplate:addScreen(spacestation_imperial_greeting);

--Declare overt
spacestation_rebel_declare = ConvoScreen:new {
	id = "spacestation_rebel_declare",
	leftDialog = "@conversation/pvp_station_rebel:s_62e7ee", --Very well, %TU. Your ship will begin broadcasting your Rebel Alliance affiliation in 30 seconds. You may want to clear the area in the event there are hostiles nearby. Rebel Alliance Station, out.
	stopConversation = "true",
	options = {}
}
spacestation_rebel_convotemplate:addScreen(spacestation_rebel_declare);

--Decline declaring overt
spacestation_rebel_decline = ConvoScreen:new {
	id = "spacestation_rebel_decline",
	leftDialog = "@conversation/pvp_station_rebel:s_b780e818", --In that case, please move away from the station.
	stopConversation = "true",
	options = {}
}
spacestation_rebel_convotemplate:addScreen(spacestation_rebel_decline);

-- Begin explanation
spacestation_rebel_explain_01 = ConvoScreen:new {
	id = "spacestation_rebel_explain_01",
	leftDialog = "@conversation/pvp_station_rebel:s_d2cd41a5", --Although you are a Rebel Alliance Pilot by profession, you have not Declared your factional affiliation. Many Imperial ships [players] will hold fire in the event you are not really affiliated with the Rebel Alliance. You may declare your affiliation with the Alliance to make it clear that you are willing to respond to their attacks.
	stopConversation = "false",
	options = {
		{"@conversation/pvp_station_rebel:s_626fe576", "spacestation_rebel_explain_02"}, --How long does this last?
	}
}
spacestation_rebel_convotemplate:addScreen(spacestation_rebel_explain_01);

-- Continue explanation
spacestation_rebel_explain_02 = ConvoScreen:new {
	id = "spacestation_rebel_explain_02",
	leftDialog = "@conversation/pvp_station_rebel:s_392e22", --You will be a Declared Rebel until you land your ship. The next time you launch, if you want to be a Declared Rebel again, you must speak to a Rebel Alliance Station again.
	stopConversation = "false",
	options = {
		{"@conversation/pvp_station_rebel:s_dc5b544f", "spacestation_rebel_explain_03"}, --All Imperial Pilots will be able to attack me?
	}
}
spacestation_rebel_convotemplate:addScreen(spacestation_rebel_explain_02);

-- Final explanation
spacestation_rebel_explain_03 = ConvoScreen:new {
	id = "spacestation_rebel_explain_03",
	leftDialog = "@conversation/pvp_station_rebel:s_e4046084", --Not all of them, %TU. Just the ones that have Declared their affiliation with the Empire. You'll be able to attack them, and they will be able to attack you. Ready to declare?
	stopConversation = "false",
	options = {
		{"@conversation/pvp_station_rebel:s_370822d1", "spacestation_rebel_declare"}, --Yes
		{"@conversation/pvp_station_rebel:s_457a7010", "spacestation_rebel_decline"}, --No
		{"@conversation/pvp_station_rebel:s_dd67013", "spacestation_rebel_explain_01"}, --What does that mean?
	}
}
spacestation_rebel_convotemplate:addScreen(spacestation_rebel_explain_03);

-- Add Template (EOF)
addConversationTemplate("spacestation_rebel_convotemplate", spacestation_rebel_convotemplate);
