bestineRumor02ConvoTemplate = ConvoTemplate:new {
	initialScreen = "",
	templateType = "Lua",
	luaClassHandler = "bestine_election_conv_handler",
	screens = {}
}

election_started = ConvoScreen:new {
	id = "election_started",
	leftDialog = "@conversation/bestine_rumor02:s_f9db7bbe", --Bestine really doesn't need heightened defenses. I'm going to vote for Sean Trenwell, Director of Commerce in the upcoming election. We could really use more merchants around here. What do you think? I really think you should vote. The governor is taking votes at the capitol.
	stopConversation = "true",
	options = {}
}

bestineRumor02ConvoTemplate:addScreen(election_started);

default_greeting = ConvoScreen:new {
	id = "default_greeting",
	leftDialog = "@conversation/bestine_rumor02:s_f74566b1", --Maybe voting for Sean Trenwell wasn't such a good idea. I heard some pretty nasty rumors about him. He seems to be blinded by money. But really, who isn't?
	stopConversation = "true",
	options = {}
}

bestineRumor02ConvoTemplate:addScreen(default_greeting);

addConversationTemplate("bestineRumor02ConvoTemplate", bestineRumor02ConvoTemplate);
