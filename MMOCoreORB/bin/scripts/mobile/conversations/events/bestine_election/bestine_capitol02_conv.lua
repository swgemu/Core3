bestineCapitol02ConvoTemplate = ConvoTemplate:new {
	initialScreen = "",
	templateType = "Lua",
	luaClassHandler = "bestine_election_conv_handler",
	screens = {}
}

election_started = ConvoScreen:new {
	id = "election_started",
	leftDialog = "@conversation/bestine_capitol02:s_bdbf995f", --The capitol is buzzing about the new election! I'm glad you've come! I hope you're going to vote. The eligible candidates are Victor Visalis and Sean Trenwell. The governor is collecting votes, and the winner will work closely with her on a new project. You should go talk with her.
	stopConversation = "true",
	options = {}
}

bestineCapitol02ConvoTemplate:addScreen(election_started);

default_greeting = ConvoScreen:new {
	id = "default_greeting",
	leftDialog = "@conversation/bestine_capitol02:s_d18211cb", --The Empire has taken a new direct standing against the people. I really hope the poor folk won't be too oppressed by the changes. We'll have to see what happens.
	stopConversation = "true",
	options = {}
}

bestineCapitol02ConvoTemplate:addScreen(default_greeting);

addConversationTemplate("bestineCapitol02ConvoTemplate", bestineCapitol02ConvoTemplate);