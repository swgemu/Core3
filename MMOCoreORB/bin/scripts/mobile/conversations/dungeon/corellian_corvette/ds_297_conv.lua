corvetteDS297ConvoTemplate = ConvoTemplate:new {
	initialScreen = "start",
	templateType = "Lua",
	luaClassHandler = "ticketTakerDS297ConvoHandler",
	screens = {}
}

start = ConvoScreen:new {
	id = "start",
	leftDialog = "@conversation/corvette_imperial_pilot:s_e1b151c2", -- Greetings citizen. What brings you to this exclusive retreat at which you probably have no legitimate business?
	stopConversation = "false",
	options = {}
}

corvetteDS297ConvoTemplate:addScreen(start);

goodbye = ConvoScreen:new {
	id = "goodbye",
	leftDialog = "@conversation/corvette_imperial_pilot:s_3fa1e397", -- I see, well I wouldn't dally if I were you. Might want to move along.
	stopConversation = "true",
	options = {}
}

corvetteDS297ConvoTemplate:addScreen(goodbye);

too_many = ConvoScreen:new {
	id = "too_many",
	leftDialog = "@conversation/corvette_imperial_pilot:s_7c51b25", -- Well, I'd like to help you, but the transportation I can provide only has room for 10 or less. You'll need to reduce your group size and then speak with me again
	stopConversation = "true",
	options = {}
}

corvetteDS297ConvoTemplate:addScreen(too_many);

wrong_faction = ConvoScreen:new {
	id = "wrong_faction",
	leftDialog = "@conversation/corvette_imperial_pilot:s_dd163c95", -- Well, I'd like to help you, but I'm only authorized to transport those of Imperial standing. You'll need to adjust your group and then speak with me again.
	stopConversation = "true",
	options = {}
}

corvetteDS297ConvoTemplate:addScreen(wrong_faction);

wrong_faction_too_many = ConvoScreen:new {
	id = "wrong_faction_too_many",
	leftDialog = "@conversation/corvette_imperial_pilot:s_4044790f", -- Well, I'd like to help you, but the transportation I can provide only has room for 10 or less. In addition to that, I'm only authorized to transport those of Imperial standing. You'll need to adjust your group and then speak with me again.
	stopConversation = "true",
	options = {}
}

corvetteDS297ConvoTemplate:addScreen(wrong_faction_too_many);

continue = ConvoScreen:new {
	id = "continue",
	leftDialog = "@conversation/corvette_imperial_pilot:s_6cca850b", -- Really. Where would you hear that, I wonder. Just out of curiosity, any particular blockade runner? 
	stopConversation = "false",
	options = {}
}

corvetteDS297ConvoTemplate:addScreen(continue);

goodbye2 = ConvoScreen:new {
	id = "goodbye2",
	leftDialog = "@conversation/corvette_imperial_pilot:s_e84669ef", -- Right. Well, good luck with whatever you're trying to do.
	stopConversation = "true",
	options = {}
}

corvetteDS297ConvoTemplate:addScreen(goodbye2);

mission_too_many = ConvoScreen:new {
	id = "mission_too_many",
	leftDialog = "@conversation/corvette_imperial_pilot:s_37545a64", -- I think I heard about that one recently... some Rebel intel was discovered recently and word of it managed to cross my path. A Corellian CR-90 corvette, I believe. I think I can help you, but the transportation I can provide only has room for 10 or less. You'll need to reduce your group size and then speak with me again.
	stopConversation = "true",
	options = {}
}

corvetteDS297ConvoTemplate:addScreen(mission_too_many);

mission_wrong_faction = ConvoScreen:new {
	id = "mission_wrong_faction",
	leftDialog = "@conversation/corvette_imperial_pilot:s_db4a97a9", -- I think I heard about that one recently... some Rebel intel was discovered recently and word of it managed to cross my path. It was a Corellian CR-90 corvette, I believe. I think I can help you, but I'm only authorized to transport those of Imperial standing. You'll need to adjust your group and then speak with me again.
	stopConversation = "true",
	options = {}
}

corvetteDS297ConvoTemplate:addScreen(mission_wrong_faction);

mission_wrong_faction_too_many = ConvoScreen:new {
	id = "mission_wrong_faction_too_many",
	leftDialog = "@conversation/corvette_imperial_pilot:s_d5421c5c", -- I think I heard about that one recently... some Rebel intel was discovered recently and word of it managed to cross my path. It was a Corellian CR-90 corvette, I believe. I think I can help you, but the transportation I can provide only has room for 10 or less. In addition to that, I'm only authorized to transport those of Imperial standing. You'll need to adjust your group and then speak with me again.
	stopConversation = "true",
	options = {}
}

corvetteDS297ConvoTemplate:addScreen(mission_wrong_faction_too_many);

mission = ConvoScreen:new {
	id = "mission",
	leftDialog = "@conversation/corvette_imperial_pilot:s_500c4dc0", -- I think I heard about that one recently... some Rebel intel was discovered recently and word of it managed to cross my path. A Corellian CR-90 corvette, I believe. I think I can help you. Once on the corvette, you'll have a limited amount of time to complete your mission. Be sure to finish and escape in less than an hour.
	stopConversation = "false",
	options = {
		{"@conversation/corvette_imperial_pilot:s_62aa5014","authorization"}, -- Good, when can we go?
		{"@conversation/corvette_imperial_pilot:s_d553beb4","goodbye3"}, -- I've changed my mind, and I'm leaving.
	}
}

corvetteDS297ConvoTemplate:addScreen(mission);

authorization = ConvoScreen:new {
	id = "authorization",
	leftDialog = "@conversation/corvette_imperial_pilot:s_fbc421e2", -- Eager to go... good. Let's get things started. Let me see your authorization, and we'll go from there.
	stopConversation = "true",
	options = {}
}

corvetteDS297ConvoTemplate:addScreen(authorization);

goodbye3 = ConvoScreen:new {
	id = "goodbye3",
	leftDialog = "@conversation/corvette_imperial_pilot:s_b5aa0f29", -- I suppose it's your choice. But failing to fulfill your mission won't reflect well when your service to the Empire is being considered.
	stopConversation = "true",
	options = {}
}

corvetteDS297ConvoTemplate:addScreen(goodbye3);

addConversationTemplate("corvetteDS297ConvoTemplate", corvetteDS297ConvoTemplate);
