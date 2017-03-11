padawan_peoples_soldier_01_convo_template = ConvoTemplate:new {
	initialScreen = "",
	templateType = "Lua",
	luaClassHandler = "padawan_peoples_soldier_01_conv_handler",
	screens = {}
}

intro = ConvoScreen:new {
	id = "intro",
	leftDialog = "@conversation/padawan_peoples_soldier_01:s_6151c35f", -- Can I trust you with some information?
	stopConversation = "false",
	options = {
		{"@conversation/padawan_peoples_soldier_01:s_df607c49", "working_whole_life"} -- I'm listening.
	}
}
padawan_peoples_soldier_01_convo_template:addScreen(intro);

working_whole_life = ConvoScreen:new {
	id = "working_whole_life",
	leftDialog = "@conversation/padawan_peoples_soldier_01:s_fae10b21", -- I've been working my whole life, and have very little to show for it.
	stopConversation = "false",
	options = {
		{"@conversation/padawan_peoples_soldier_01:s_edb238bc", "crucial_disk"} -- Go on.
	}
}
padawan_peoples_soldier_01_convo_template:addScreen(working_whole_life);

crucial_disk = ConvoScreen:new {
	id = "crucial_disk",
	leftDialog = "@conversation/padawan_peoples_soldier_01:s_eaa416f0", -- There is a fairly large group of thugs here in town.  One of them is holding onto a crucial data disk, on which the location of a huge stock of stolen supplies is stored.
	stopConversation = "false",
	options = {
		{"@conversation/padawan_peoples_soldier_01:s_9f213941", "medicine_and_food"}, -- What type of supplies?
		{"@conversation/padawan_peoples_soldier_01:s_b84b366c", "spirit_in_your_eyes"}, -- How can I help?
	}
}
padawan_peoples_soldier_01_convo_template:addScreen(crucial_disk);

medicine_and_food = ConvoScreen:new {
	id = "medicine_and_food",
	leftDialog = "@conversation/padawan_peoples_soldier_01:s_f3df0aae", -- Medicine, and foods mostly.
	stopConversation = "false",
	options = {
		{"@conversation/padawan_peoples_soldier_01:s_464748ae", "spirit_in_your_eyes"}, -- I am willing to help, where do I start?
		{"@conversation/padawan_peoples_soldier_01:s_2ae116f8", "join_their_ranks"}, -- What is in it for me?
	}
}
padawan_peoples_soldier_01_convo_template:addScreen(medicine_and_food);

join_their_ranks = ConvoScreen:new {
	id = "join_their_ranks",
	leftDialog = "@conversation/padawan_peoples_soldier_01:s_a6cac2af", -- With questions like that you might as well join their ranks, I must have read you wrong.
	stopConversation = "false",
	options = {
		{"@conversation/padawan_peoples_soldier_01:s_41ec1c94", "hanging_around"}, -- Sorry, it's a bad habit.  How can I help?
		{"@conversation/padawan_peoples_soldier_01:s_6b8c7e69", "fare_thee_well"}, -- You did. If there's nothing in this for me, I'm gone.
	}
}
padawan_peoples_soldier_01_convo_template:addScreen(join_their_ranks);

hanging_around = ConvoScreen:new {
	id = "hanging_around",
	leftDialog = "@conversation/padawan_peoples_soldier_01:s_257d7def", -- You can find these thugs hanging around and being a nuisance. Keep in mind talking with them is an exhausted option. I wouldn't approach any of them without a blaster at my hip.
	stopConversation = "true",
	options = {}
}
padawan_peoples_soldier_01_convo_template:addScreen(hanging_around);

fare_thee_well = ConvoScreen:new {
	id = "fare_thee_well",
	leftDialog = "@conversation/padawan_peoples_soldier_01:s_c0a878d5", -- Indeed. Then fare thee well. No... make that fare thee poorly.
	stopConversation = "true",
	options = {}
}
padawan_peoples_soldier_01_convo_template:addScreen(fare_thee_well);

spirit_in_your_eyes = ConvoScreen:new {
	id = "spirit_in_your_eyes",
	leftDialog = "@conversation/padawan_peoples_soldier_01:s_e8f293a0", -- I knew I could see the spirit in your eyes. You can find these thugs hanging around and harassing people. Keep in mind talking with them is an exhausted option. I wouldn't approach any of them without a blaster at my hip.
	stopConversation = "true",
	options = {}
}
padawan_peoples_soldier_01_convo_template:addScreen(spirit_in_your_eyes);

intro_in_progress = ConvoScreen:new {
	id = "intro_in_progress",
	leftDialog = "@conversation/padawan_peoples_soldier_01:s_d1008bcb", -- What is the problem? Have you done what I've asked?
	stopConversation = "false",
	options = {
		{"@conversation/padawan_peoples_soldier_01:s_ddb27082", "bring_it_back"}, -- Not yet, but I'm working on it.
		{"@conversation/padawan_peoples_soldier_01:s_209a7c7b", "stench_of_failure"} -- I just remembered that I don't care. Bye.
	}
}
padawan_peoples_soldier_01_convo_template:addScreen(intro_in_progress);

bring_it_back = ConvoScreen:new {
	id = "bring_it_back",
	leftDialog = "@conversation/padawan_peoples_soldier_01:s_873db52a", -- Don't expect a welcoming party; like I said before, I wouldn't approach them without a blaster on your hip. When you get the disk, bring it back to me.
	stopConversation = "true",
	options = {}
}
padawan_peoples_soldier_01_convo_template:addScreen(bring_it_back);

stench_of_failure = ConvoScreen:new {
	id = "stench_of_failure",
	leftDialog = "@conversation/padawan_peoples_soldier_01:s_4f53003d", -- I should have expected as much. The stench of failure surrounds you... which I foolishly thought could be overcome. No chance.
	stopConversation = "true",
	options = {}
}
padawan_peoples_soldier_01_convo_template:addScreen(stench_of_failure);

intro_killed_target = ConvoScreen:new {
	id = "intro_killed_target",
	leftDialog = "@conversation/padawan_peoples_soldier_01:s_d1008bcb", -- Have you got the disk?
	stopConversation = "false",
	options = {
		{"@conversation/padawan_peoples_soldier_01:s_b9bc27b2", "pretty_penny"}, -- Sure enough.  I thought it was going to be a challenge.
	}
}
padawan_peoples_soldier_01_convo_template:addScreen(intro_killed_target);

pretty_penny = ConvoScreen:new {
	id = "pretty_penny",
	leftDialog = "@conversation/padawan_peoples_soldier_01:s_f485390d", -- Good show, all this spice is going to fetch a pretty penny.  See you around.
	stopConversation = "false",
	options = {
		{"@conversation/padawan_peoples_soldier_01:s_c7676f2f", "six_million"}, -- Spice!  You said it was foods and medicine!
	}
}
padawan_peoples_soldier_01_convo_template:addScreen(pretty_penny);

six_million = ConvoScreen:new {
	id = "six_million",
	leftDialog = "@conversation/padawan_peoples_soldier_01:s_53e9175a", -- Would you have returned the disk had you known the contents were worth well over six million credits?  Didn't think so.  
	stopConversation = "true",
	options = {}
}
padawan_peoples_soldier_01_convo_template:addScreen(six_million);

completed_quest = ConvoScreen:new {
	id = "completed_quest",
	leftDialog = "@conversation/padawan_peoples_soldier_01:s_a082f8ab", -- Don't feel so bad... it's all to a good cause. My bank account! Ha!
	stopConversation = "true",
	options = {}
}
padawan_peoples_soldier_01_convo_template:addScreen(completed_quest);

not_quest_owner = ConvoScreen:new {
	id = "not_quest_owner",
	leftDialog = "@conversation/padawan_peoples_soldier_01:s_4e6ee0cd", -- The rich get richer. Too true. So that means I should become one of the rich.
	stopConversation = "true",
	options = {}
}
padawan_peoples_soldier_01_convo_template:addScreen(not_quest_owner);

addConversationTemplate("padawan_peoples_soldier_01_convo_template", padawan_peoples_soldier_01_convo_template);
