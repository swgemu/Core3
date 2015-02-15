heroOfTatMotherConvoTemplate = ConvoTemplate:new {
	initialScreen = "",
	templateType = "Lua",
	luaClassHandler = "heroOfTatMotherConvoHandler",
	screens = {}
}

intro = ConvoScreen:new {
	id = "intro",
	leftDialog = "@conversation/quest_hero_of_tatooine_mother:s_76752ac6", -- Who are you? Another one of those filthy pirates? Get away from me...
	stopConversation = "false",
	options = {
		{"@conversation/quest_hero_of_tatooine_mother:s_d28e075c", "what_should_we_do"}, -- I'm no pirate. I'm here to rescue you.
		{"@conversation/quest_hero_of_tatooine_mother:s_6441a2a6", "im_sorry"}, -- As you wish.
	}
}
heroOfTatMotherConvoTemplate:addScreen(intro);

intro_noquest = ConvoScreen:new {
	id = "intro_noquest",
	leftDialog = "@conversation/quest_hero_of_tatooine_mother:s_76752ac6", -- Who are you? Another one of those filthy pirates? Get away from me...
	stopConversation = "true",
	options = {}
}
heroOfTatMotherConvoTemplate:addScreen(intro_noquest);

what_should_we_do = ConvoScreen:new {
	id = "what_should_we_do",
	leftDialog = "@conversation/quest_hero_of_tatooine_mother:s_8892a744", -- Really? Oh I knew that someone would come to save us! What would you like us to do?
	stopConversation = "false",
	options = {
		{"@conversation/quest_hero_of_tatooine_mother:s_5e328776", "right_behind_you"}, -- Follow me. Let's get you out of here.
		{"@conversation/quest_hero_of_tatooine_mother:s_7d25e81f", "waiting_here"}, -- Wait right here. I'll come back for you in a moment.
	}
}
heroOfTatMotherConvoTemplate:addScreen(what_should_we_do);

right_behind_you = ConvoScreen:new {
	id = "right_behind_you",
	leftDialog = "@conversation/quest_hero_of_tatooine_mother:s_877ce91a", -- OK. We'll be right behind you.
	stopConversation = "true",
	options = {}
}
heroOfTatMotherConvoTemplate:addScreen(right_behind_you);

waiting_here = ConvoScreen:new {
	id = "waiting_here",
	leftDialog = "@conversation/quest_hero_of_tatooine_mother:s_cd1765f7", -- OK. We'll wait right here.
	stopConversation = "true",
	options = {}
}
heroOfTatMotherConvoTemplate:addScreen(waiting_here);

im_sorry = ConvoScreen:new {
	id = "im_sorry",
	leftDialog = "@conversation/quest_hero_of_tatooine_mother:s_ecd319b", -- Wait, wait. I'm sorry. You really don't seem like one of those brutes.
	stopConversation = "false",
	options = {
		{"@conversation/quest_hero_of_tatooine_mother:s_8de4e85c", "what_to_do"}, -- I've been sent to rescue you.
		{"@conversation/quest_hero_of_tatooine_mother:s_9fe4df0a", "dont_go"}, -- I've got better things to do with my time.
	}
}
heroOfTatMotherConvoTemplate:addScreen(im_sorry);

what_to_do = ConvoScreen:new {
	id = "what_to_do",
	leftDialog = "@conversation/quest_hero_of_tatooine_mother:s_d0294ce0", -- What would you like us to do?
	stopConversation = "false",
	options = {
		{"@conversation/quest_hero_of_tatooine_mother:s_8beec89f", "right_behind_you"}, -- Follow me. I'll lead you out of here.
		{"@conversation/quest_hero_of_tatooine_mother:s_7d25e81f", "waiting_here"}, -- Wait right here. I'll come back for you in a moment.
	}
}
heroOfTatMotherConvoTemplate:addScreen(what_to_do);

dont_go = ConvoScreen:new {
	id = "dont_go",
	leftDialog = "@conversation/quest_hero_of_tatooine_mother:s_e72f8b74", -- No, please don't go...
	stopConversation = "true",
	options = {}
}
heroOfTatMotherConvoTemplate:addScreen(dont_go);

addConversationTemplate("heroOfTatMotherConvoTemplate", heroOfTatMotherConvoTemplate);