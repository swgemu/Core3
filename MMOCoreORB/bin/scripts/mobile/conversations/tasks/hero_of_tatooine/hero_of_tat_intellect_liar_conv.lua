heroOfTatIntellectLiarConvoTemplate = ConvoTemplate:new {
	initialScreen = "init",
	templateType = "Lua",
	luaClassHandler = "heroOfTatIntellectLiarConvoHandler",
	screens = {}
}

init = ConvoScreen:new {
	id = "init",
	leftDialog = "",
	stopConversation = "false",
	options = {
		{"@quest/hero_of_tatooine/intellect_liar:response_0", "equipment"}, -- What do you know about the stolen equipment?
		{"@quest/hero_of_tatooine/intellect_liar:response_1", "smugglers"}, -- What do you know about the other smugglers?
		{"@quest/hero_of_tatooine/intellect_liar:response_2", "bye"}, -- Thank you for your time.
	}
}
heroOfTatIntellectLiarConvoTemplate:addScreen(init);

init_noquest = ConvoScreen:new {
	id = "init_noquest",
	leftDialog = "",
	stopConversation = "true",
	options = {}
}
heroOfTatIntellectLiarConvoTemplate:addScreen(init_noquest);

equipment = ConvoScreen:new {
	id = "equipment",
	leftDialog = "",
	stopConversation = "false",
	options = {
		{"@quest/hero_of_tatooine/intellect_liar:response_1", "smugglers"}, -- What do you know about the other smugglers?
		{"@quest/hero_of_tatooine/intellect_liar:response_2", "bye"}, -- Thank you for your time.
	}
}
heroOfTatIntellectLiarConvoTemplate:addScreen(equipment);

smugglers = ConvoScreen:new {
	id = "smugglers",
	leftDialog = "",
	stopConversation = "false",
	options = {
		{"@quest/hero_of_tatooine/intellect_liar:response_0", "equipment"}, -- What do you know about the stolen equipment?
		{"@quest/hero_of_tatooine/intellect_liar:response_2", "bye"}, -- Thank you for your time.
	}
}
heroOfTatIntellectLiarConvoTemplate:addScreen(smugglers);

bye = ConvoScreen:new {
	id = "bye",
	leftDialog = "",
	stopConversation = "true",
	options = {
	}
}
heroOfTatIntellectLiarConvoTemplate:addScreen(bye);

addConversationTemplate("heroOfTatIntellectLiarConvoTemplate", heroOfTatIntellectLiarConvoTemplate);