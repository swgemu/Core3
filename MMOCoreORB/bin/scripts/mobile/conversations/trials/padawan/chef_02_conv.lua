trialsPadawanChef02ConvoTemplate = ConvoTemplate:new {
	initialScreen = "",
	templateType = "Lua",
	luaClassHandler = "trialsPadawanChef02ConvoHandler",
	screens = {}
}

intro = ConvoScreen:new {
	id = "intro",
	leftDialog = "@conversation/padawan_chef_02:s_35494a44", -- Hey... who are you? What are you doing following me? At least you're not that crazed chef. He was out of his mind. I mean, it was just a pie.
	stopConversation = "false",
	options = {
		{"@conversation/padawan_chef_02:s_c1e21c08", "deflect"}, -- I'm here because that crazed chef asked me to be.
		{"@conversation/padawan_chef_02:s_928c6a6a", "depart"} -- The chef wants revenge. But I think I've made a mistake. I'm leaving.
	}
}
trialsPadawanChef02ConvoTemplate:addScreen(intro);

deflect = ConvoScreen:new {
	id = "deflect",
	leftDialog = "@conversation/padawan_chef_02:s_78cca73a", -- What? No! Ha. That's truly unbelievable. Okay, so you're here. Now what? You gonna try and collect some money for that pie?
	stopConversation = "false",
	options = {
		{"@conversation/padawan_chef_02:s_ca28f99d", "kill"} -- Not money, exactly. But I am here to make you pay for that pie. In blood.
	}
}
trialsPadawanChef02ConvoTemplate:addScreen(deflect);

kill = ConvoScreen:new {
	id = "kill",
	leftDialog = "@conversation/padawan_chef_02:s_867ceb54", -- Whoa! Hold it. Just a minute. For a pie? You want blood? Alright. Whatever. Come on. Let's go!
	stopConversation = "true",
	options = {}
}
trialsPadawanChef02ConvoTemplate:addScreen(kill);

depart = ConvoScreen:new {
	id = "depart",
	leftDialog = "@conversation/padawan_chef_02:s_2ad2bbf9", -- Oh. Yeah, good. And you tell that chef... well, tell him his pie was really good. And that I'll try and pay for the next one.
	stopConversation = "true",
	options = {}
}
trialsPadawanChef02ConvoTemplate:addScreen(depart);

noquest_player_talks = ConvoScreen:new {
	id = "noquest_player_talks",
	leftDialog = "@conversation/padawan_chef_02:s_7ca121b2", -- Oh man, that pie was so good. I hope that guy makes another one. I might even pay for the next one
	stopConversation = "true",
	options = {}
}
trialsPadawanChef02ConvoTemplate:addScreen(noquest_player_talks);

addConversationTemplate("trialsPadawanChef02ConvoTemplate", trialsPadawanChef02ConvoTemplate);
