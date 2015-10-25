trialsPadawanPeoplesSoldier01ConvoTemplate = ConvoTemplate:new {
	initialScreen = "",
	templateType = "Lua",
	luaClassHandler = "trialsPadawanPeoplesSoldier01ConvoHandler",
	screens = {}
}

intro = ConvoScreen:new {
	id = "intro",
	leftDialog = "@conversation/padawan_peoples_soldier_01:s_6151c35f", -- Can I trust you with some information?
	stopConversation = "false",
	options = {
		{"@conversation/padawan_peoples_soldier_01:s_df607c49", "more_go"} -- I'm listening.
	}
}
trialsPadawanPeoplesSoldier01ConvoTemplate:addScreen(intro);

more_go = ConvoScreen:new {
	id = "more_go",
	leftDialog = "@conversation/padawan_peoples_soldier_01:s_fae10b21", -- I've been working my whole life, and have very little to show for it. More and more of the money I make is being used to line the pockets of the rich. There is little I can do by myself, which is why I am asking you for help. 
	stopConversation = "false",
	options = {
		{"@conversation/padawan_peoples_soldier_01:s_edb238bc", "continue"}, -- Go on.
		{"@conversation/padawan_peoples_soldier_01:s_4e6ee0cd", "greedy"} -- The rich get richer. Too true. So that means I should become one of the rich.
	}
}
trialsPadawanPeoplesSoldier01ConvoTemplate:addScreen(more_go);

greedy = ConvoScreen:new {
	id = "greedy",
	leftDialog = "@conversation/padawan_peoples_soldier_01:s_4f53003d", -- I should have expected as much. The stench of failure surrounds you... which I foolishly thought could be overcome. No chance.
	stopConversation = "false",
	options = {
		{"@conversation/padawan_peoples_soldier_01:s_a082f8ab", "continue_gone"} -- Don't feel so bad... it's all to a good cause. My bank account! Ha!
	}
}
trialsPadawanPeoplesSoldier01ConvoTemplate:addScreen(greedy);

continue = ConvoScreen:new {
	id = "continue",
	leftDialog = "@conversation/padawan_peoples_soldier_01:s_eaa416f0", -- There is a fairly large group of thugs here in town. One of them is holding onto a crucial data disk, on which the location of a huge stock of stolen supplies is stored.
	stopConversation = "false",
	options = {
		{"@conversation/padawan_peoples_soldier_01:s_9f213941", "continue_more"} -- What type of supplies?
	}
}
trialsPadawanPeoplesSoldier01ConvoTemplate:addScreen(continue);

continue_more = ConvoScreen:new {
	id = "continue_more",
	leftDialog = "@conversation/padawan_peoples_soldier_01:s_f3df0aae", -- Medicine, and foods mostly.
	stopConversation = "false",
	options = {
		{"@conversation/padawan_peoples_soldier_01:s_464748ae", "continue_again"}, -- I am willing to help, where do I start?
		{"@conversation/padawan_peoples_soldier_01:s_2ae116f8", "continue_too"} -- What is in it for me?
	}
}
trialsPadawanPeoplesSoldier01ConvoTemplate:addScreen(continue_more);

continue_again = ConvoScreen:new {
	id = "continue_again",
	leftDialog = "@conversation/padawan_peoples_soldier_01:s_e8f293a0", -- I knew I could see the spirit in your eyes. You can find these thugs hanging around and causing trouble. Keep in mind talking with them is an exhausted option. I wouldn't approach any of them without a blaster at my hip. 
	stopConversation = "true",
	options = {}
}
trialsPadawanPeoplesSoldier01ConvoTemplate:addScreen(continue_again);

continue_too = ConvoScreen:new {
	id = "continue_too",
	leftDialog = "@conversation/padawan_peoples_soldier_01:s_a6cac2af", -- With questions like that you might as well join their ranks, I must have read you wrong.
	stopConversation = "false",
	options = {
		{"@conversation/padawan_peoples_soldier_01:s_41ec1c94", "continue_again"}, -- Sorry, it's a bad habit. How can I help?
		{"@conversation/padawan_peoples_soldier_01:s_6b8c7e69", "continue_gone"} -- You did. If there's nothing in this for me, I'm gone.
	}
}
trialsPadawanPeoplesSoldier01ConvoTemplate:addScreen(continue_too);

continue_gone = ConvoScreen:new {
	id = "continue_gone",
	leftDialog = "@conversation/padawan_peoples_soldier_01:s_c0a878d5", -- Indeed. Then fare thee well. No... make that fare thee poorly.
	stopConversation = "true",
	options = {}
}
trialsPadawanPeoplesSoldier01ConvoTemplate:addScreen(continue_gone);

back_notdone = ConvoScreen:new {
	id = "back_notdone",
	leftDialog = "@conversation/padawan_peoples_soldier_01:s_40708207", -- Have you got the disk?
	stopConversation = "false",
	options = {
		{"@conversation/padawan_peoples_soldier_01:s_ddb27082", "continue_on"}, -- Not yet, but I'm working on it.
		{"@conversation/padawan_peoples_soldier_01:s_209a7c7b", "continue_gone"} -- I just remembered that I don't care. Bye.
	}
}
trialsPadawanPeoplesSoldier01ConvoTemplate:addScreen(back_notdone);

continue_on = ConvoScreen:new {
	id = "continue_on",
	leftDialog = "@conversation/padawan_peoples_soldier_01:s_873db52a", -- Don't expect a welcoming party; like I said before, I wouldn't approach them without a blaster on your hip. When you get the disk, bring it back to me.
	stopConversation = "true",
	options = {}
}
trialsPadawanPeoplesSoldier01ConvoTemplate:addScreen(continue_on);

back_done = ConvoScreen:new {
	id = "back_done",
	leftDialog = "@conversation/padawan_peoples_soldier_01:s_d1008bcb", -- What is the problem? Have you done what I've asked?
	stopConversation = "false",
	options = {
		{"@conversation/padawan_peoples_soldier_01:s_b9bc27b2", "back_done_more"} -- Sure enough. I thought it was going to be a challenge.
	}
}
trialsPadawanPeoplesSoldier01ConvoTemplate:addScreen(back_done);

back_done_more = ConvoScreen:new {
	id = "back_done_more",
	leftDialog = "@conversation/padawan_peoples_soldier_01:s_f485390d", -- Good show, all this spice is going to fetch a pretty penny. See you around.
	stopConversation = "false",
	options = {
		{"@conversation/padawan_peoples_soldier_01:s_c7676f2f", "continue_final"} -- Spice! You said it was foods and medicine!
	}
}
trialsPadawanPeoplesSoldier01ConvoTemplate:addScreen(back_done_more);

continue_final = ConvoScreen:new {
	id = "continue_final",
	leftDialog = "@conversation/padawan_peoples_soldier_01:s_53e9175a", -- Would you have returned the disk had you known the contents were worth well over six million credits? Didn't think so. Move along and learn from your mistakes.
	stopConversation = "true",
	options = {}
}
trialsPadawanPeoplesSoldier01ConvoTemplate:addScreen(continue_final);

noquest_player_talks = ConvoScreen:new {
	id = "noquest_player_talks",
	leftDialog = "@conversation/padawan_peoples_soldier_01:s_209a7c7b", -- I just remembered that I don't care. Bye.
	stopConversation = "true",
	options = {}
}
trialsPadawanPeoplesSoldier01ConvoTemplate:addScreen(noquest_player_talks);

addConversationTemplate("trialsPadawanPeoplesSoldier01ConvoTemplate", trialsPadawanPeoplesSoldier01ConvoTemplate);
