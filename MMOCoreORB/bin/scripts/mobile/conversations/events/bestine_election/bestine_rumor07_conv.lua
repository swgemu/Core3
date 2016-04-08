bestineRumor07ConvoTemplate = ConvoTemplate:new {
	initialScreen = "",
	templateType = "Lua",
	luaClassHandler = "bestine_election_conv_handler",
	screens = {}
}

election_started = ConvoScreen:new {
	id = "election_started",
	leftDialog = "@conversation/bestine_rumor07:s_3626560c", --Visalis is on our side. If he wins the election, more Imperial Troops will be recruited and sent to Bestine. I hear the Tusken Raiders are getting restless. You should vote. The governor is taking them over at the capitol. Oh-break is over. Move along, citizen.
	stopConversation = "true",
	options = {}
}

bestineRumor07ConvoTemplate:addScreen(election_started);

default_greeting = ConvoScreen:new {
	id = "default_greeting",
	leftDialog = "@conversation/bestine_rumor07:s_49709fbf",--We're clenching our fists tighter around the Rebel Alliance. Soon, they won't be in existence. They're nothing but trouble. You should stay away from them.
	stopConversation = "true",
	options = {}
}

bestineRumor07ConvoTemplate:addScreen(default_greeting);

addConversationTemplate("bestineRumor07ConvoTemplate", bestineRumor07ConvoTemplate);
