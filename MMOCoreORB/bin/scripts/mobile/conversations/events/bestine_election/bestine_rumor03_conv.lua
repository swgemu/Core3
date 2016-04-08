bestineRumor03ConvoTemplate = ConvoTemplate:new {
	initialScreen = "",
	templateType = "Lua",
	luaClassHandler = "bestine_election_conv_handler",
	screens = {}
}

election_started = ConvoScreen:new {
	id = "election_started",
	leftDialog = "@conversation/bestine_rumor03:s_cd086fbf", --Merchants? A Museum? Historians?! C'mon! What we really need is added defense against Tusken Raiders! In the upcoming election, my vote is for Victor Visalis, Officer of Defense. You should vote too. Go ask the governor at the capitol for more information.
	stopConversation = "true",
	options = {}
}

bestineRumor03ConvoTemplate:addScreen(election_started);

default_greeting = ConvoScreen:new {
	id = "default_greeting",
	leftDialog = "@conversation/bestine_rumor03:s_848f500b", --Victor Visalis did well in office, I think. Well... other than hunting down rebels with his newly-hired band of troopers. It was pretty horrible for a while. But, what can ya do? This is an Imperial city after all.
	stopConversation = "true",
	options = {}
}

bestineRumor03ConvoTemplate:addScreen(default_greeting);

addConversationTemplate("bestineRumor03ConvoTemplate", bestineRumor03ConvoTemplate);
