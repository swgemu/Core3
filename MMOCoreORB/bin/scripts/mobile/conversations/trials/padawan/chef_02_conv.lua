padawan_chef_02_convo_template = ConvoTemplate:new {
	initialScreen = "",
	templateType = "Lua",
	luaClassHandler = "padawan_chef_02_conv_handler",
	screens = {}
}

intro = ConvoScreen:new {
	id = "intro",
	leftDialog = "@conversation/padawan_chef_02:s_35494a44", -- Hey... who are you? What are you doing following me? At least you're not that crazed chef. He was out of his mind. I mean, it was just a pie.
	stopConversation = "false",
	options = {
		{"@conversation/padawan_chef_02:s_c1e21c08", "truly_unbelievable"}, -- I'm here because that crazed chef asked me to be.
	}
}
padawan_chef_02_convo_template:addScreen(intro);

truly_unbelievable = ConvoScreen:new {
	id = "truly_unbelievable",
	leftDialog = "@conversation/padawan_chef_02:s_78cca73a", -- What? No! Ha. That's truly unbelievable. Okay, so you're here. Now what? You gonna try and collect some money for that pie?
	stopConversation = "false",
	options = {
		{"@conversation/padawan_chef_02:s_ca28f99d", "just_a_minute"}, -- Not money, exactly. But I am here to make you pay for that pie. In blood.
		{"@conversation/padawan_chef_02:s_928c6a6a", "pay_next_time"}, -- The chef wants revenge. But I think I've made a mistake. I'm leaving.
	}
}
padawan_chef_02_convo_template:addScreen(truly_unbelievable);

pay_next_time = ConvoScreen:new {
	id = "pay_next_time",
	leftDialog = "@conversation/padawan_chef_02:s_2ad2bbf9", -- Oh. Yeah, good. And you tell that chef... well, tell him his pie was really good. And that I'll try and pay for the next one.
	stopConversation = "true",
	options = {}
}
padawan_chef_02_convo_template:addScreen(pay_next_time);

just_a_minute = ConvoScreen:new {
	id = "just_a_minute",
	leftDialog = "@conversation/padawan_chef_02:s_867ceb54", -- Whoa! Hold it. Just a minute. For a pie? You want blood? Alright. Whatever. Come on. Let's go!
	stopConversation = "true",
	options = {}
}
padawan_chef_02_convo_template:addScreen(just_a_minute);

not_quest_owner = ConvoScreen:new {
	id = "not_quest_owner",
	leftDialog = "@conversation/padawan_chef_02:s_7ca121b2", -- Oh man, that pie was so good. I hope that guy makes another one. I might even pay for the next one.
	stopConversation = "true",
	options = {}
}
padawan_chef_02_convo_template:addScreen(not_quest_owner);

addConversationTemplate("padawan_chef_02_convo_template", padawan_chef_02_convo_template);
