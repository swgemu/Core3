BartendersConversationTemplate = ConvoTemplate:new {
	initialScreen = "bartender_start",
	templateType = "Lua",
	luaClassHandler = "BartenderConversationHandler",
	screens = {}
}

bartender_start = ConvoScreen:new {
	id = "bartender_start",
	leftDialog = "@bartender:greet",
	stopConversation = "false",
	options = {
		{"@bartender:opt_buy", "opt_buy"}, -- "I'd like to buy a drink..."
		{"@bartender:talk_to_me", "talk_to_me"}, -- "Tell me about current events."
	}
}
BartendersConversationTemplate:addScreen(bartender_start);

bartender_rumor_start = ConvoScreen:new {
	id = "bartender_rumor_start",
	leftDialog = "@bartender:greet",
	stopConversation = "false",
	options = {
		{"@bartender:opt_buy", "opt_buy"}, -- "I'd like to buy a drink..."
		{"@bartender:opt_rumor", "opt_rumor"}, -- "Heard anything interesting lately?"
	}
}
BartendersConversationTemplate:addScreen(bartender_rumor_start);

query_buy = ConvoScreen:new {
	id = "query_buy",
	leftDialog = "@bartender:query_buy", -- You still look like you could use a drink though. Can I interest you in one of fine beverages?"
	stopConversation = "false",
	options = {
		{"@bartender:opt_yes", "opt_yes"}, -- "Yes"
		{"@bartender:opt_no", "opt_no"}, -- "No"
	}
}
BartendersConversationTemplate:addScreen(query_buy);

opt_yes = ConvoScreen:new {
	id = "opt_yes",
	leftDialog = "@bartender:msg_yes", -- "Your patronage is kindly appreciated."
	stopConversation = "true",
	options = {}
}
BartendersConversationTemplate:addScreen(opt_yes);

opt_no = ConvoScreen:new {
	id = "opt_no",
	leftDialog = "@bartender:msg_no", -- "Then get out of my bar you miserable wretch. Your kind is not appreciated around here..."
	stopConversation = "true",
	options = {}
}
BartendersConversationTemplate:addScreen(opt_no);

opt_buy = ConvoScreen:new {
	id = "opt_buy",
	leftDialog = "@bartender:msg_buy", --"Well, you have come to the right place! Allow me to provide you with a menu of our choice selections."
	stopConversation = "true",
	options = {}
}
BartendersConversationTemplate:addScreen(opt_buy);

talk_to_me = ConvoScreen:new {
	id = "talk_to_me",
	leftDialog = "@bartender:monthly_fiction_1", -- "I heard something about the drall...you know those guys from Corellia?  Rumor has it there's been some anti-imperial sentiment amongst them, and they're planning on doing something about it.  Couldn't tell you what, but I think the Empire might take matters into their own hands soon."
	stopConversation = "true",
	options = {}
}
BartendersConversationTemplate:addScreen(talk_to_me);

opt_rumor = ConvoScreen:new {
	id = "opt_rumor",
	leftDialog = "@bartender:monthly_fiction_1", -- "Can't say that I have heard anything recently..."
	stopConversation = "true",
	options = {}
}
BartendersConversationTemplate:addScreen(opt_rumor);

addConversationTemplate("BartendersConversationTemplate", BartendersConversationTemplate);
