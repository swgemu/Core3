bestineCapitol01ConvoTemplate = ConvoTemplate:new {
	initialScreen = "",
	templateType = "Lua",
	luaClassHandler = "bestine_election_conv_handler",
	screens = {}
}

election_started = ConvoScreen:new {
	id = "election_started",
	leftDialog = "@conversation/bestine_capitol01:s_f9dda042", --You look a little lost. Or have you come to the capitol to vote in the upcoming election? Confused? You haven't heard of the changes to Bestine? I thought everyone had heard of it! Must be an outsider. Oh well! Do you want to hear about it?
	stopConversation = "false",
	options = {
		{"@conversation/bestine_capitol01:s_c82e9a2f","election_yes"}, -- Yes, please.
		{"@conversation/bestine_capitol01:s_90ce1297","election_no"}, -- No, thank you
	}
}

bestineCapitol01ConvoTemplate:addScreen(election_started);

default_greeting = ConvoScreen:new {
	id = "default_greeting",
	leftDialog = "@conversation/bestine_capitol01:s_da5842cb", --Another election should be coming up in the following months. I wonder who will win and what effects it will have on the city of Bestine. You should probably keep an eye out for upcoming announcements.
	stopConversation = "true",
	options = {}
}

bestineCapitol01ConvoTemplate:addScreen(default_greeting);

election_yes = ConvoScreen:new {
	id = "election_yes",
	leftDialog = "@conversation/bestine_capitol01:s_8819f19f", --The governor is appointing someone to work closely with her on a new project. Currently, the only two candidates eligible are Victor Visalis, Officer of Defense and Sean Trenwell, Director of Commerce. You'll probably have to speak with the governor for more information about the voting process and further details. Unfortunately, I have to get back to work.
	stopConversation = "true",
	options = {}
}

bestineCapitol01ConvoTemplate:addScreen(election_yes);

election_no = ConvoScreen:new {
	id = "election_no",
	leftDialog = "@conversation/bestine_capitol01:s_edaf838a", --That's a pity. Okay, then. Have a good day!
	stopConversation = "true",
	options = {}
}

bestineCapitol01ConvoTemplate:addScreen(election_no);

addConversationTemplate("bestineCapitol01ConvoTemplate", bestineCapitol01ConvoTemplate);

