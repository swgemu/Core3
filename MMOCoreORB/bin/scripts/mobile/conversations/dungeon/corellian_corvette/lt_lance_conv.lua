corvetteLtLanceConvoTemplate = ConvoTemplate:new {
	initialScreen = "",
	templateType = "Lua",
	luaClassHandler = "ticketTakerLtLanceConvoHandler",
	screens = {}
}

start = ConvoScreen:new {
	id = "start",
	leftDialog = "@conversation/corvette_rebel_pilot:s_669e781c", -- I am so bored, they've kept me in here managing flight schedules for what feels like an eternity now. Please tell me you're here with my reassignment orders?
	stopConversation = "false",
	options = {}
}

corvetteLtLanceConvoTemplate:addScreen(start);

goodbye = ConvoScreen:new {
	id = "goodbye",
	leftDialog = "@conversation/corvette_rebel_pilot:s_c1674c48", -- Passing through? This is a military base. You should be more... oh, who am I kidding. Just try not to get into trouble, okay.
	stopConversation = "true",
	options = {}
}

corvetteLtLanceConvoTemplate:addScreen(goodbye);

too_many = ConvoScreen:new {
	id = "too_many",
	leftDialog = "@conversation/corvette_rebel_pilot:s_7c51b25", -- Well, I'd like to help you, but the transportation I can provide only has room for 10 or less. You'll need to reduce your group size and then speak with me again
	stopConversation = "true",
	options = {}
}

corvetteLtLanceConvoTemplate:addScreen(too_many);

wrong_faction = ConvoScreen:new {
	id = "wrong_faction",
	leftDialog = "@conversation/corvette_rebel_pilot:s_84d3ed4b", -- Well, I'd like to help you, but I'm only allowed to transport members of the Rebel alliance. You'll need to adjust your group and then speak with me again.
	stopConversation = "true",
	options = {}
}

corvetteLtLanceConvoTemplate:addScreen(wrong_faction);

wrong_faction_too_many = ConvoScreen:new {
	id = "wrong_faction_too_many",
	leftDialog = "@conversation/corvette_rebel_pilot:s_e1cf0c03", -- Well, I'd like to help you, but the transportation I can provide only has room for 10 or less. Plus, I'm only allowed to transport members of the Rebel Alliance. You'll need to adjust your group and then speak with me again.
	stopConversation = "true",
	options = {}
}

corvetteLtLanceConvoTemplate:addScreen(wrong_faction_too_many);

continue = ConvoScreen:new {
	id = "continue",
	leftDialog = "@conversation/corvette_rebel_pilot:s_e2aa2143", -- Oh, there's lots of things I could help you with. And possibly even something like that. What's your story?
	stopConversation = "false",
	options = {}
}

corvetteLtLanceConvoTemplate:addScreen(continue);

goodbye2 = ConvoScreen:new {
	id = "goodbye2",
	leftDialog = "@conversation/corvette_rebel_pilot:s_29e528c6", -- Ah okay. Good luck with whatever it is you're up to. Come back if I can help. Because... really... I'm totally bored.
	stopConversation = "true",
	options = {}
}

corvetteLtLanceConvoTemplate:addScreen(goodbye2);

mission_too_many = ConvoScreen:new {
	id = "mission_too_many",
	leftDialog = "@conversation/corvette_rebel_pilot:s_a538ed35", -- Ah yes, I was briefed about something like that earlier today. It was one of our Corellian CR-90 corvettes, I believe. I'm glad we're going to do something about it. I can definitely help you, but the transportation I can provide only has room for 10 or less. You'll need to reduce your group size and then speak with me again.
	stopConversation = "true",
	options = {}
}

corvetteLtLanceConvoTemplate:addScreen(mission_too_many);

mission_wrong_faction = ConvoScreen:new {
	id = "mission_wrong_faction",
	leftDialog = "@conversation/corvette_rebel_pilot:s_808bd5e8", -- Ah yes, I was briefed about something like that earlier today. It was one of our Corellian CR-90 corvettes, I believe. I'm glad we're going to do something about it. I can definitely help you, but I'm only allowed to transport members of the Rebel alliance. You'll need to adjust your group and then speak with me again.
	stopConversation = "true",
	options = {}
}

corvetteLtLanceConvoTemplate:addScreen(mission_wrong_faction);

mission_wrong_faction_too_many = ConvoScreen:new {
	id = "mission_wrong_faction_too_many",
	leftDialog = "@conversation/corvette_rebel_pilot:s_221a046", -- Ah yes, I was briefed about something like that earlier today. It was one of our Corellian CR-90 corvettes, I believe. I'm glad we're going to do something about it. I can definitely help you, but the transportation I can provide only has room for 10 or less. Plus, I'm only allowed to transport members of the Rebel Alliance. You'll need to adjust your group and then speak with me again.
	stopConversation = "true",
	options = {}
}

corvetteLtLanceConvoTemplate:addScreen(mission_wrong_faction_too_many);

mission = ConvoScreen:new {
	id = "mission",
	leftDialog = "@conversation/corvette_rebel_pilot:s_4816807a", -- Ah yes, I was briefed about something like that earlier today. It was one of our Corellian CR-90 corvettes, I believe. I'm glad we're going to do something about it. I can definitely help you. But we're working against the clock here. Once on the corvette, you'll only have an hour to complete your mission. After that, it's too late.
	stopConversation = "false",
	options = {
		{"@conversation/corvette_rebel_pilot:s_62aa5014","authorization"}, -- Good, when can we go?
		{"@conversation/corvette_rebel_pilot:s_e851c3db","goodbye3"} -- I've changed my mind, and I think I'll be going.
	}
}

corvetteLtLanceConvoTemplate:addScreen(mission);

authorization = ConvoScreen:new {
	id = "authorization",
	leftDialog = "@conversation/corvette_rebel_pilot:s_52a4b87d", -- Eager to go... I like that. Let's get things rolling. First I'll need to see your authorization form...
	stopConversation = "true",
	options = {}
}

corvetteLtLanceConvoTemplate:addScreen(authorization);

goodbye3 = ConvoScreen:new {
	id = "goodbye3",
	leftDialog = "@conversation/corvette_rebel_pilot:s_35e19d9c", -- What? But this is... oh, I get it. Need to stock up on supplies or something like that. I understand. I'll be here when you're ready.
	stopConversation = "true",
	options = {}
}

corvetteLtLanceConvoTemplate:addScreen(goodbye3);

addConversationTemplate("corvetteLtLanceConvoTemplate", corvetteLtLanceConvoTemplate);
