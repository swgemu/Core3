rikkh_convo_template = ConvoTemplate:new {
	initialScreen = "",
	templateType = "Lua",
	luaClassHandler = "rikkhConvoHandler",
	screens = {}
}

no_jtl = ConvoScreen:new {
	id = "no_jtl",
	leftDialog = "@conversation/corellia_privateer_trainer:s_698d80f7", -- Sorry, but you don't look like a pilot to me.
	animation = "shake_head_no",
	stopConversation = "true",
	options = {}
}
rikkh_convo_template:addScreen(no_jtl);

not_pilot = ConvoScreen:new {
	id = "not_pilot",
	leftDialog = "@conversation/corellia_privateer_trainer_2:s_5d3166b9", -- Everything is fine here. Nothing wrong at all.
	animation = "shake_head_no",
	stopConversation = "true",
	options = {}
}
rikkh_convo_template:addScreen(not_pilot);

















addConversationTemplate("rikkh_convo_template", rikkh_convo_template);
