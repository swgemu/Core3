trialsPadawanPannaqa02ConvoTemplate = ConvoTemplate:new {
	initialScreen = "",
	templateType = "Lua",
	luaClassHandler = "trialsPadawanPannaqa02ConvoHandler",
	screens = {}
}

intro = ConvoScreen:new {
	id = "intro",
	leftDialog = "@conversation/padawan_pannaqa_02:s_e03f6fd1", -- Yes? May I help you?
	stopConversation = "false",
	options = {
		{"@conversation/padawan_pannaqa_02:s_afd80a03", "continue"} -- I'm looking for Shendo. I was told he might be here?
	}
}
trialsPadawanPannaqa02ConvoTemplate:addScreen(intro);

continue = ConvoScreen:new {
	id = "continue",
	leftDialog = "@conversation/padawan_pannaqa_02:s_3c4de5b4", -- No, he's not around, as usual. He's off goofing around as always. I don't think I've ever seen him without a Sunburn in his hand and spice on his breath.
	stopConversation = "false",
	options = {
		{"@conversation/padawan_pannaqa_02:s_69850509", "continue_more"} -- Do you know where I might find him?
	}
}
trialsPadawanPannaqa02ConvoTemplate:addScreen(continue);

continue_more = ConvoScreen:new {
	id = "continue_more",
	leftDialog = "@conversation/padawan_pannaqa_02:s_499c34de", -- Yeah, I can help you. I'll upload the information to your datapad.
	stopConversation = "true",
	options = {}
}
trialsPadawanPannaqa02ConvoTemplate:addScreen(continue_more);

noquest_player_talks = ConvoScreen:new {
	id = "noquest_player_talks",
	leftDialog = "@conversation/padawan_pannaqa_02:s_62623109", -- Go away. I'm doing stuff here and you're bothering me.
	stopConversation = "true",
	options = {}
}
trialsPadawanPannaqa02ConvoTemplate:addScreen(noquest_player_talks);

addConversationTemplate("trialsPadawanPannaqa02ConvoTemplate", trialsPadawanPannaqa02ConvoTemplate);
