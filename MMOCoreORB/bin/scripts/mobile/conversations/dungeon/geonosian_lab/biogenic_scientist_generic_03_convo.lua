biogenicScientistGeneric03ConvoTemplate = ConvoTemplate:new {
	initialScreen = "",
	templateType = "Lua",
	luaClassHandler = "BiogenicScientistGeneric03ConvoHandler",
	screens = {}
}

init_talk = ConvoScreen:new {
	id = "init_talk",
	leftDialog = "@conversation/biogenic_scientist_generic_03:s_fda0157f", -- All my fault... This is all my fault...
	stopConversation = "false",
	options = {
		{"@conversation/biogenic_scientist_generic_03:s_e82d7c74","locked_in_without_code"}, -- What are you babbling about?
		{"@conversation/biogenic_scientist_generic_03:s_87bb58ec","creatures_cages"}, -- Calm down. What is your fault?
		{"@conversation/biogenic_scientist_generic_03:s_95fa4e8","should_have_helped"} -- Yes, it probably is. Good-bye.
	}
}

biogenicScientistGeneric03ConvoTemplate:addScreen(init_talk);

should_have_helped = ConvoScreen:new {
	id = "should_have_helped",
	leftDialog = "@conversation/biogenic_scientist_generic_03:s_5a0551a4", -- I should have done something... too late now.
	stopConversation = "true",
	options = {
	}
}

biogenicScientistGeneric03ConvoTemplate:addScreen(should_have_helped);

no_it_wont_be = ConvoScreen:new {
	id = "no_it_wont_be",
	leftDialog = "@conversation/biogenic_scientist_generic_03:s_a55d1241", -- No... no it won't be. And it's all my fault. I've killed everyone.
	stopConversation = "true",
	options = {
	}
}

biogenicScientistGeneric03ConvoTemplate:addScreen(no_it_wont_be);

code_all_my_fault = ConvoScreen:new {
	id = "code_all_my_fault",
	leftDialog = "@conversation/biogenic_scientist_generic_03:s_aed85251", -- The code... 92126. They're locked in... and they're going to die... and it's all my fault... my fault.
	stopConversation = "true",
	options = {
	}
}

biogenicScientistGeneric03ConvoTemplate:addScreen(code_all_my_fault);

creatures_cages = ConvoScreen:new {
	id = "creatures_cages",
	leftDialog = "@conversation/biogenic_scientist_generic_03:s_64f42fb0", -- These creatures... the cages. Shouldn't have made them so powerful. Should have made the cages stronger. But I locked them in... with the code...
	stopConversation = "false",
	options = {
		{"@conversation/biogenic_scientist_generic_03:s_5b104c75","code_all_my_fault"}, -- What is the code?
		{"@conversation/biogenic_scientist_generic_03:s_95fa4e8","should_have_helped"} -- Yes, it probably is. Good-bye.
	}
}

biogenicScientistGeneric03ConvoTemplate:addScreen(creatures_cages);

locked_in_without_code = ConvoScreen:new {
	id = "locked_in_without_code",
	leftDialog = "@conversation/biogenic_scientist_generic_03:s_b5665d3a", -- They're locked in... they don't know the code... 92126. They're going to die... all my fault.
	stopConversation = "false",
	options = {
		{"@conversation/biogenic_scientist_generic_03:s_b4e9b11d","no_it_wont_be"}, -- Relax. It will be OK.
		{"@conversation/biogenic_scientist_generic_03:s_95fa4e8","should_have_helped"} -- Yes, it probably is. Good-bye.
	}
}

biogenicScientistGeneric03ConvoTemplate:addScreen(locked_in_without_code);

addConversationTemplate("biogenicScientistGeneric03ConvoTemplate", biogenicScientistGeneric03ConvoTemplate);
