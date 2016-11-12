bestineRumor01ConvoTemplate = ConvoTemplate:new {
	initialScreen = "",
	templateType = "Lua",
	luaClassHandler = "bestine_election_conv_handler",
	screens = {}
}

election_started = ConvoScreen:new {
	id = "election_started",
	leftDialog = "@conversation/bestine_rumor01:s_a886b683", --If you care about the state of Bestine, then you should vote for one of the new candidates. You can go to the capitol and speak with the governor for more information. The winner of the election will reflect on Bestine, so choose wisely.
	stopConversation = "true",
	options = {}
}

bestineRumor01ConvoTemplate:addScreen(election_started);

default_greeting = ConvoScreen:new {
	id = "default_greeting",
	leftDialog = "@conversation/bestine_rumor01:s_b1225bbd", --I hear there's been way too many attacks on Bestine by the Sand People. It's really hurting our economy.
	stopConversation = "true",
	options = {}
}

bestineRumor01ConvoTemplate:addScreen(default_greeting);

addConversationTemplate("bestineRumor01ConvoTemplate", bestineRumor01ConvoTemplate);
