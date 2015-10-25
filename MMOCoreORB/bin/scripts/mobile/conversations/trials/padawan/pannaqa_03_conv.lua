trialsPadawanPannaqa03ConvoTemplate = ConvoTemplate:new {
	initialScreen = "",
	templateType = "Lua",
	luaClassHandler = "trialsPadawanPannaqa03ConvoHandler",
	screens = {}
}

intro = ConvoScreen:new {
	id = "intro",
	leftDialog = "@conversation/padawan_pannaqa_03:s_552042df", -- Show me the drink to go way. I'm home and I wanna go drink....
	stopConversation = "false",
	options = {
		{"@conversation/padawan_pannaqa_03:s_70fea75d", "continue"} -- Um, hello?
	}
}
trialsPadawanPannaqa03ConvoTemplate:addScreen(intro);

continue = ConvoScreen:new {
	id = "continue",
	leftDialog = "@conversation/padawan_pannaqa_03:s_2b0e7d3c", -- Pannaqa! You are already many hours late.
	stopConversation = "false",
	options = {
		{"@conversation/padawan_pannaqa_03:s_4cc97351", "continue_more"} -- Pannaqa has been waiting for you for quite a while, Shendo. He needs that vibro-tiller part.
	}
}
trialsPadawanPannaqa03ConvoTemplate:addScreen(continue);

continue_more = ConvoScreen:new {
	id = "continue_more",
	leftDialog = "@conversation/padawan_pannaqa_03:s_6abc7ab9", -- No kidding eh? I guess I should probably get on that huh?
	stopConversation = "false",
	options = {
		{"@conversation/padawan_pannaqa_03:s_7bbf7ffe", "continue_again"}, -- I don't think I can trust you to finish the job.
		{"@conversation/padawan_pannaqa_03:s_b7bc9ab", "continue_too"} -- At this point I do not care, I've lost all hope.
	}
}
trialsPadawanPannaqa03ConvoTemplate:addScreen(continue_more);

continue_again = ConvoScreen:new {
	id = "continue_again",
	leftDialog = "@conversation/padawan_pannaqa_03:s_eb635904", -- So you are going to take the part for me, and I can stay here and drink?
	stopConversation = "false",
	options = {
		{"@conversation/padawan_pannaqa_03:s_1a22a5dc", "continue_final"} -- Basically.
	}
}
trialsPadawanPannaqa03ConvoTemplate:addScreen(continue_again);

continue_too = ConvoScreen:new {
	id = "continue_too",
	leftDialog = "@conversation/padawan_pannaqa_03:s_e51e11cc", -- Cheer up mate, how about I give you the part, and you take it to Pan.. Paqanna.. Whatever his name was. I'm going to keep my eyes on this bottle of ale for you and make sure it doesn't do whatever it is I think it's going to do. [You stash the vibro-tiller part in a safe place.]
	stopConversation = "true",
	options = {}
}
trialsPadawanPannaqa03ConvoTemplate:addScreen(continue_too);

continue_final = ConvoScreen:new {
	id = "continue_final",
	leftDialog = "@conversation/padawan_pannaqa_03:s_b6307da0", -- Deal. Now I can get back to my drinking and wandering. [You stash the vibro-tiller part in a safe place.]
	stopConversation = "true",
	options = {}
}
trialsPadawanPannaqa03ConvoTemplate:addScreen(continue_final);

noquest_player_talks = ConvoScreen:new {
	id = "noquest_player_talks",
	leftDialog = "@conversation/padawan_pannaqa_03:s_2b0e7d3c", -- Pannaqa! You are already many hours late.
	stopConversation = "false",
	options = {
		{"@conversation/padawan_pannaqa_03:s_9035e1f5", "noquest_reply"} -- Um, who?
	}
}
trialsPadawanPannaqa03ConvoTemplate:addScreen(noquest_player_talks);

noquest_reply = ConvoScreen:new {
	id = "noquest_reply",
	leftDialog = "@conversation/padawan_pannaqa_03:s_552042df", -- Show me the drink to go way. I'm home and I wanna go drink....
	stopConversation = "true",
	options = {}
}
trialsPadawanPannaqa03ConvoTemplate:addScreen(noquest_reply);

addConversationTemplate("trialsPadawanPannaqa03ConvoTemplate", trialsPadawanPannaqa03ConvoTemplate);
