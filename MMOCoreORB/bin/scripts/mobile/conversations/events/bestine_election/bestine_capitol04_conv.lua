bestineCapitol04ConvoTemplate = ConvoTemplate:new {
	initialScreen = "",
	templateType = "Lua",
	luaClassHandler = "bestine_election_conv_handler",
	screens = {}
}

election_started = ConvoScreen:new {
	id = "election_started",
	leftDialog = "@conversation/bestine_capitol04:s_754d87ee", --I guess I didn't make the cut. Like many of the politicians here, I too wanted to work with the governor on her new project. Now, it's between Victor Visalis and Sean Trenwell. I guess they deserve it. Speak with the governor for more details. I really must get back to work.
	stopConversation = "true",
	options = {}
}

bestineCapitol04ConvoTemplate:addScreen(election_started);

default_greeting = ConvoScreen:new {
	id = "default_greeting",
	leftDialog = "@conversation/bestine_capitol04:s_2fcca84c", --Do you think I'll make the next election? I have so many good ideas for Bestine. Listen to them... actually, I'm not going to tell you. You may steal my ideas and run for office. You think you're pretty smart, huh?
	stopConversation = "true",
	options = {}
}

bestineCapitol04ConvoTemplate:addScreen(default_greeting);

addConversationTemplate("bestineCapitol04ConvoTemplate", bestineCapitol04ConvoTemplate);
