padawan_bad_cat_01_convo_template = ConvoTemplate:new {
	initialScreen = "",
	templateType = "Lua",
	luaClassHandler = "padawan_bad_cat_01_conv_handler",
	screens = {}
}

intro = ConvoScreen:new {
	id = "intro",
	leftDialog = "@conversation/padawan_bad_cat_01:s_93b5b885", -- We have a slight problem.
	stopConversation = "false",
	options = {
		{"@conversation/padawan_bad_cat_01:s_799aee03", "spooked_cat"}, -- Oh we do, do we?
		{"@conversation/padawan_bad_cat_01:s_34fc22c8", "biggest_problem"} -- No, I think you have a problem.
	}
}
padawan_bad_cat_01_convo_template:addScreen(intro);

biggest_problem = ConvoScreen:new {
	id = "biggest_problem",
	leftDialog = "@conversation/padawan_bad_cat_01:s_1ca2724b", -- Too true, well my best friend is the one with the biggest problem.
	stopConversation = "false",
	options = {
		{"@conversation/padawan_bad_cat_01:s_799aee03", "find_the_cat"}, -- What do you want me to do about it?
		{"@conversation/padawan_bad_cat_01:s_ff470431", "dont_know_what_to_do"} -- As I said, I think this problem is yours alone. I don't care.
	}
}
padawan_bad_cat_01_convo_template:addScreen(biggest_problem);

find_the_cat = ConvoScreen:new {
	id = "find_the_cat",
	leftDialog = "@conversation/padawan_bad_cat_01:s_5455041", -- Find the cat, and ermm... take the necessary steps to make sure this never happens again. I realize that will mean killing the cat, but I don't know that there are any alternative.
	stopConversation = "false",
	options = {
		{"@conversation/padawan_bad_cat_01:s_d36ab1ec", "last_location"}, -- Don't worry... I'll do what needs to be done.
	}
}
padawan_bad_cat_01_convo_template:addScreen(find_the_cat);

last_location = ConvoScreen:new {
	id = "last_location",
	leftDialog = "@conversation/padawan_bad_cat_01:s_ddfbf107", -- Thank you.  I have uploaded the cat's last known location to your datapad.  Return here once this is all behind us.
	stopConversation = "true",
	options = {}
}
padawan_bad_cat_01_convo_template:addScreen(last_location);

spooked_cat = ConvoScreen:new {
	id = "spooked_cat",
	leftDialog = "@conversation/padawan_bad_cat_01:s_913dffdc", -- My pet, a fairly large cat, was spooked during a live performance earlier this evening. It leapt right at my good friend, who was performing with me, and went for his throat.
	stopConversation = "false",
	options = {
		{"@conversation/padawan_bad_cat_01:s_8b81f489", "uploaded_coordinates"}, -- Yes I'll do what I can.
		{"@conversation/padawan_bad_cat_01:s_ecd38d6b", "dont_know_what_to_do"} -- No. Please. Why would I care?
	}
}
padawan_bad_cat_01_convo_template:addScreen(spooked_cat);

uploaded_coordinates = ConvoScreen:new {
	id = "uploaded_coordinates",
	leftDialog = "@conversation/padawan_bad_cat_01:s_a2b99609", -- Okay.  I have uploaded coordinates to your datapad for the cat's last known location.  Return here once it's over. Please.
	stopConversation = "true",
	options = {}
}
padawan_bad_cat_01_convo_template:addScreen(uploaded_coordinates);

dont_know_what_to_do = ConvoScreen:new {
	id = "dont_know_what_to_do",
	leftDialog = "@conversation/padawan_bad_cat_01:s_72bfd7f8", -- We did truly need your help. Now I don't know what to do.
	stopConversation = "true",
	options = {}
}
padawan_bad_cat_01_convo_template:addScreen(dont_know_what_to_do);

quest_completed = ConvoScreen:new {
	id = "quest_completed",
	leftDialog = "@conversation/padawan_bad_cat_01:s_3aa5b0e8", -- I don't think the cat meant any harm, but those animals don't realize how much damage they can do.
	stopConversation = "true",
	options = {}
}
padawan_bad_cat_01_convo_template:addScreen(quest_completed);

not_quest_owner = ConvoScreen:new {
	id = "not_quest_owner",
	leftDialog = "@conversation/padawan_bad_cat_01:s_6766a3d9", -- What am I going to do...
	stopConversation = "true",
	options = {}
}
padawan_bad_cat_01_convo_template:addScreen(not_quest_owner);

intro_target_killed = ConvoScreen:new {
	id = "intro_target_killed",
	leftDialog = "@conversation/padawan_bad_cat_01:s_89952c29", -- Tell me it's all over.
	stopConversation = "false",
	options = {
		{"@conversation/padawan_bad_cat_01:s_5ffd7e8f", "glad_its_over"}, -- It is.  The cat has been taken care of.
	}
}
padawan_bad_cat_01_convo_template:addScreen(intro_target_killed);

glad_its_over = ConvoScreen:new {
	id = "glad_its_over",
	leftDialog = "@conversation/padawan_bad_cat_01:s_b4aeaba0", -- [pause] I'm glad it's over. Thank you for your help.  I owe you my gratitude.
	stopConversation = "true",
	options = {}
}
padawan_bad_cat_01_convo_template:addScreen(glad_its_over);

intro_in_progress = ConvoScreen:new {
	id = "intro_in_progress",
	leftDialog = "@conversation/padawan_bad_cat_01:s_5b82e205", -- Have you taken care of our problem?
	stopConversation = "false",
	options = {
		{"@conversation/padawan_bad_cat_01:s_6077d5", "please_hurry"}, -- Not yet, but I will.
		{"@conversation/padawan_bad_cat_01:s_ee242807", "oh_dear"}, -- No, and I've decided I'm not going to. Deal with it yourself.
	}
}
padawan_bad_cat_01_convo_template:addScreen(intro_in_progress);

please_hurry = ConvoScreen:new {
	id = "please_hurry",
	leftDialog = "@conversation/padawan_bad_cat_01:s_d3af9eee", -- Please hurry.
	stopConversation = "true",
	options = {}
}
padawan_bad_cat_01_convo_template:addScreen(please_hurry);

oh_dear = ConvoScreen:new {
	id = "oh_dear",
	leftDialog = "@conversation/padawan_bad_cat_01:s_bad01abd", -- Oh dear.
	stopConversation = "true",
	options = {}
}
padawan_bad_cat_01_convo_template:addScreen(oh_dear);

addConversationTemplate("padawan_bad_cat_01_convo_template", padawan_bad_cat_01_convo_template);
