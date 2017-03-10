padawan_pannaqa_02_convo_template = ConvoTemplate:new {
	initialScreen = "",
	templateType = "Lua",
	luaClassHandler = "padawan_pannaqa_02_conv_handler",
	screens = {}
}

intro = ConvoScreen:new {
	id = "intro",
	leftDialog = "@conversation/padawan_pannaqa_02:s_e03f6fd1", -- Yes? May I help you?
	stopConversation = "false",
	options = {
		{"@conversation/padawan_pannaqa_02:s_afd80a03", "not_around"} -- I'm looking for Shendo. I was told he might be here?
	}
}
padawan_pannaqa_02_convo_template:addScreen(intro);

not_around = ConvoScreen:new {
	id = "not_around",
	leftDialog = "@conversation/padawan_pannaqa_02:s_3c4de5b4", -- No, he's not around, as usual. He's off goofing around as always.  I don't think I've ever seen him without a Sunburn in his hand and spice on his breath.
	stopConversation = "false",
	options = {
		{"@conversation/padawan_pannaqa_02:s_69850509", "i_can_help"} -- Do you know where I might find him?
	}
}
padawan_pannaqa_02_convo_template:addScreen(not_around);

i_can_help = ConvoScreen:new {
	id = "i_can_help",
	leftDialog = "@conversation/padawan_pannaqa_02:s_499c34de", -- Yeah, I can help you. I'll upload the information to your datapad.
	stopConversation = "true",
	options = {}
}
padawan_pannaqa_02_convo_template:addScreen(i_can_help);

not_quest_owner = ConvoScreen:new {
	id = "not_quest_owner",
	leftDialog = "@conversation/padawan_pannaqa_02:s_62623109", -- Go away. I'm doing stuff here and you're bothering me.
	stopConversation = "true",
	options = {}
}
padawan_pannaqa_02_convo_template:addScreen(not_quest_owner);

addConversationTemplate("padawan_pannaqa_02_convo_template", padawan_pannaqa_02_convo_template);
