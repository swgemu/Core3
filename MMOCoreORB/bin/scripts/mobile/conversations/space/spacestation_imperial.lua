spacestation_imperial_convotemplate = ConvoTemplate:new {
	initialScreen = "spacestation_imperial_greeting",
	templateType = "Lua",
	luaClassHandler = "SpacestationImperialConvoHandler",
	screens = {}
}

-- Initial Greeting
spacestation_imperial_greeting = ConvoScreen:new {
	id = "spacestation_imperial_greeting",
	leftDialog = "@conversation/pvp_station_imperial:s_afe52489", --Welcome to the Imperial Space Station, %TU. Would you like to declare your affiliation with the Empire?
	stopConversation = "false",
	options = {
		{"@conversation/pvp_station_imperial:s_370822d1", "spacestation_imperial_declare"}, --Yes
		{"@conversation/pvp_station_imperial:s_457a7010", "spacestation_imperial_decline"}, --No
		{"@conversation/pvp_station_imperial:s_dd67013", "spacestation_imperial_explain_01"}, --What does that mean?
	}
}
spacestation_imperial_convotemplate:addScreen(spacestation_imperial_greeting);

--out of range
out_of_range = ConvoScreen:new {
	id = "out_of_range",
	leftDialog = "@conversation/pvp_station_imperial:s_48f82131", --You need to move closer to this station.
	stopConversation = "true",
	options = {}
}
spacestation_imperial_convotemplate:addScreen(out_of_range);

--Neutral Greeting
spacestation_neutral_greeting = ConvoScreen:new {
	id = "spacestation_neutral_greeting",
	leftDialog = "@conversation/pvp_station_imperial:s_2e491159", --Sign up with the Empire and we'll talk.
	stopConversation = "true",
	options = {}
}
spacestation_imperial_convotemplate:addScreen(spacestation_neutral_greeting);

--Rebel Greeting
spacestation_rebel_greeting = ConvoScreen:new {
	id = "spacestation_rebel_greeting",
	leftDialog = "@conversation/pvp_station_imperial:s_f48e8567", --You are not welcome at this station Rebel, SCUM!
	stopConversation = "true",
	options = {}
}
spacestation_imperial_convotemplate:addScreen(spacestation_rebel_greeting);

--Declare overt
spacestation_imperial_declare = ConvoScreen:new {
	id = "spacestation_imperial_declare",
	leftDialog = "@conversation/pvp_station_imperial:s_7b492de4", --Very well, %TU. Your ship will begin broadcasting your Imperial affiliation in 30 seconds. You may want to clear the area in the event there are hostiles nearby. Imperial Station, out.
	stopConversation = "true",
	options = {}
}
spacestation_imperial_convotemplate:addScreen(spacestation_imperial_declare);

--Decline declaring overt
spacestation_imperial_decline = ConvoScreen:new {
	id = "spacestation_imperial_decline",
	leftDialog = "@conversation/pvp_station_imperial:s_1e8d6243", --In that case, please move away from the station. Clear the area for official traffic.
	stopConversation = "true",
	options = {}
}
spacestation_imperial_convotemplate:addScreen(spacestation_imperial_decline);

-- Begin explanation
spacestation_imperial_explain_01 = ConvoScreen:new {
	id = "spacestation_imperial_explain_01",
	leftDialog = "@conversation/pvp_station_imperial:s_25329880", --Although you are an Imperial Pilot by profession, you have not Declared your factional affiliation. Many Rebel ships [players] will hold-fire in the event you are not really affiliated with the Empire. You may declare your affiliation with the Empire to make it clear that you are willing to respond to their attacks.
	stopConversation = "false",
	options = {
		{"@conversation/pvp_station_imperial:s_626fe576", "spacestation_imperial_explain_02"}, --How long does this last?
	}
}
spacestation_imperial_convotemplate:addScreen(spacestation_imperial_explain_01);

-- Continue explanation
spacestation_imperial_explain_02 = ConvoScreen:new {
	id = "spacestation_imperial_explain_02",
	leftDialog = "@conversation/pvp_station_imperial:s_41ebf230", --You will be Declared Imperial until you land your ship. The next time you launch, if you want to be a Declared Imperial again, you must speak to an Imperial Station again.
	stopConversation = "false",
	options = {
		{"@conversation/pvp_station_imperial:s_3a7768e6", "spacestation_imperial_explain_03"}, --All Rebel Pilots will be able to attack me?
	}
}
spacestation_imperial_convotemplate:addScreen(spacestation_imperial_explain_02);

-- Final explanation
spacestation_imperial_explain_03 = ConvoScreen:new {
	id = "spacestation_imperial_explain_03",
	leftDialog = "@conversation/pvp_station_imperial:s_ef2a0e9c", --Not all of them, %TU. Just the ones that have Declared their affiliation with the Rebel Alliance. You'll be able to attack them, and they will be able to attack you. Ready to declare?
	stopConversation = "false",
	options = {
		{"@conversation/pvp_station_imperial:s_370822d1", "spacestation_imperial_declare"}, --Yes
		{"@conversation/pvp_station_imperial:s_457a7010", "spacestation_imperial_decline"}, --No
		{"@conversation/pvp_station_imperial:s_dd67013", "spacestation_imperial_explain_01"}, --What does that mean?
	}
}
spacestation_imperial_convotemplate:addScreen(spacestation_imperial_explain_03);

-- Add Template (EOF)
addConversationTemplate("spacestation_imperial_convotemplate", spacestation_imperial_convotemplate);
