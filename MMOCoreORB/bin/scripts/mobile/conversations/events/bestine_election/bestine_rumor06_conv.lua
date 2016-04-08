bestineRumor06ConvoTemplate = ConvoTemplate:new {
	initialScreen = "",
	templateType = "Lua",
	luaClassHandler = "bestine_election_conv_handler",
	screens = {}
}

election_started = ConvoScreen:new {
	id = "election_started",
	leftDialog = "@conversation/bestine_rumor06:s_c3f5586a", --If Victor Visalis wins this election, a higher degree of defense will be added. The Tusken Raiders are getting restless and may launch an attack soon. I really fear for the city of Bestine. You look... confused. Talk with the governor at the capitol. She knows all the details.
	stopConversation = "true",
	options = {}
}

bestineRumor06ConvoTemplate:addScreen(election_started);

default_greeting = ConvoScreen:new {
	id = "default_greeting",
	leftDialog = "@conversation/bestine_rumor06:s_e63228d2",--The museum holds frequent contests. I bought a painting that had been on showcase last month. It's really beautiful!
	stopConversation = "true",
	options = {}
}

bestineRumor06ConvoTemplate:addScreen(default_greeting);

addConversationTemplate("bestineRumor06ConvoTemplate", bestineRumor06ConvoTemplate);
