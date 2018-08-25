seansHistorianConvoTemplate = ConvoTemplate:new {
	initialScreen = "",
	templateType = "Lua",
	luaClassHandler = "seansHistorianConvoHandler",
	screens = {}
}

init_sean_in_office_no_quest = ConvoScreen:new {
	id = "init_sean_in_office_no_quest",
	leftDialog = "@conversation/seans_historian:s_79636e28", -- We recently found this wreckage. It is rumored to be the Red-Sin Valon. How exciting! Sean Trenwell funds us out of his own pocket. We hope to find interesting things here. You should talk to Sean to see if he needs any help.
	stopConversation = "true",
	options = {}
}
seansHistorianConvoTemplate:addScreen(init_sean_in_office_no_quest);

init_sean_not_in_office_no_quest = ConvoScreen:new {
	id = "init_sean_not_in_office_no_quest",
	leftDialog = "@conversation/seans_historian:s_3d3d4bab", -- We recently found this wreckage. It is rumored to be the Red-Sin Valon. How exciting! Sean Trenwell funds us out of his own pocket. We hope to find interesting things here. You should talk to Sean when he's in office.
	stopConversation = "true",
	options = {}
}
seansHistorianConvoTemplate:addScreen(init_sean_not_in_office_no_quest);

init_started_searching = ConvoScreen:new {
	id = "init_started_searching",
	leftDialog = "@conversation/seans_historian:s_8d32acbf", -- Did you find anything?
	stopConversation = "false",
	options = {
	--{"@conversation/seans_historian:s_b30bd73c", "interesting_piece"}, -- Yes, I did.
	--{"@conversation/seans_historian:s_9c1a8dd7", "be_sure_to_show"}, -- No, let me keep looking.
	}
}
seansHistorianConvoTemplate:addScreen(init_started_searching);

interesting_piece = ConvoScreen:new {
	id = "interesting_piece",
	leftDialog = "@conversation/seans_historian:s_27540308", -- Well done! What an interesting piece of history. You'd think it would have been destroyed in these dreadful sand storms. Guess not! Take it to Sean. He'll be excited.
	stopConversation = "true",
	options = {}
}
seansHistorianConvoTemplate:addScreen(interesting_piece);

be_sure_to_show = ConvoScreen:new {
	id = "be_sure_to_show",
	leftDialog = "@conversation/seans_historian:s_ed53cd9c", -- Okay. Be sure to show it to me if you do.
	stopConversation = "true",
	options = {}
}
seansHistorianConvoTemplate:addScreen(be_sure_to_show);

init_on_quest = ConvoScreen:new {
	id = "init_on_quest",
	leftDialog = "@conversation/seans_historian:s_65275fb4", -- Ah! You must be the new assistant. Welcome to the crash site of the Red-Sin Valon. Before you start poking around, maybe you'll want to hear a little history about the site first. It will give you a little sensitivity about an already-delicate situation.
	stopConversation = "false",
	options = {
		{"@conversation/seans_historian:s_647601e7", "first_new_settlers"}, -- Sure. Tell me the history.
	}
}
seansHistorianConvoTemplate:addScreen(init_on_quest);

first_new_settlers = ConvoScreen:new {
	id = "first_new_settlers",
	leftDialog = "@conversation/seans_historian:s_1f6355d4", -- The Red-Sin Valon carried the first of the new settlers to Tatooine. The captain of the ship and her crew members helped found Bestine. Despite the early difficulties--a severe economic depression, lack of water and so forth--Bestine survived and became the thriving city we see today. There's so much more depth to it...
	stopConversation = "false",
	options = {
		{"@conversation/seans_historian:s_e547fd1e", "check_the_wreckage"}, -- Yeah?
	}
}
seansHistorianConvoTemplate:addScreen(first_new_settlers);

check_the_wreckage = ConvoScreen:new {
	id = "check_the_wreckage",
	leftDialog = "@conversation/seans_historian:s_4d42d7da", -- Anyway, you should check the wreckage to see what you find. If you do find anything, you can bring it to me. I'm required to screen whatever is found. We don't need to excite Sean Trenwell over nothing, you know what I mean? Go ahead and look around.
	stopConversation = "false",
	options = {
		{"@conversation/seans_historian:s_67e6df55", "be_careful"}, -- Okay.
	}
}
seansHistorianConvoTemplate:addScreen(check_the_wreckage);

be_careful = ConvoScreen:new {
	id = "be_careful",
	leftDialog = "@conversation/seans_historian:s_2fceb7e3", -- And be careful!
	stopConversation = "true",
	options = {}
}
seansHistorianConvoTemplate:addScreen(be_careful);

addConversationTemplate("seansHistorianConvoTemplate", seansHistorianConvoTemplate);
