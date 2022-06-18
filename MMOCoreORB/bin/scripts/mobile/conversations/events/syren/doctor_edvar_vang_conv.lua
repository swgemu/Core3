doctorEdvarVangConvoTemplate = ConvoTemplate:new {
	initialScreen = "start",
	templateType = "Lua",
	luaClassHandler = "doctorEdvarVangConvoHandler",
	screens = {}
}

start = ConvoScreen:new {
	id = "start",
	leftDialog = "@conversation/c_story1_1_doc:s_718", -- Hello, may I help you?
	stopConversation = "false",
	options = {
		{"@conversation/c_story1_1_doc:s_720", "analyze"}, -- I have this spice sample that I need analyzed.
	}
}

doctorEdvarVangConvoTemplate:addScreen(start);

analyze = ConvoScreen:new {
	id = "analyze",
	leftDialog = "@conversation/c_story1_1_doc:s_722", -- Well, let me see it.  Find it in your kid's room? I keep hearing more and more stories about that, kids these days...wait a minute.  Where did you get this?!
	stopConversation = "false",
	options = {
		{"@conversation/c_story1_1_doc:s_724", "too_hot"}, -- I found it on a ship that crashed.
		{"@conversation/c_story1_1_doc:s_732", "do_not_mind"} -- Never mind where I found it, what is it?
	}
}

doctorEdvarVangConvoTemplate:addScreen(analyze);

too_hot = ConvoScreen:new {
	id = "too_hot",
	leftDialog = "@conversation/c_story1_1_doc:s_726", -- Why did you bring this to me?  This is far too hot for me to touch.  Do you realize how much danger this will bring me?  Get out!  Get out of here now!
	stopConversation = "false",
	options = {
		{"@conversation/c_story1_1_doc:s_728", "dangerous"} -- Is this illegal?  Is it dangerous?
	}
}

doctorEdvarVangConvoTemplate:addScreen(too_hot);

dangerous = ConvoScreen:new {
	id = "dangerous",
	leftDialog = "@conversation/c_story1_1_doc:s_730", -- It's dangerous to me! Out!  If you really must find out what that stuff is, go talk to a friend of mine.  He would know more about it than I do anyway.  Take this data and get out!
	stopConversation = "true",
	options = {}
}

doctorEdvarVangConvoTemplate:addScreen(dangerous);

do_not_mind = ConvoScreen:new {
	id = "do_not_mind",
	leftDialog = "@conversation/c_story1_1_doc:s_734", -- It's ... what the? I haven't seen anything like this since... do you realize what this represents?
	stopConversation = "false",
	options = {
		{"@conversation/c_story1_1_doc:s_736", "dangerous"}, -- Is this illegal?  Is it dangerous?
	}
}

doctorEdvarVangConvoTemplate:addScreen(do_not_mind);

already_talked = ConvoScreen:new {
	id = "already_talked",
	leftDialog = "@conversation/c_story1_1_doc:s_740", -- I don't think you should talk to me anymore.
	stopConversation = "true",
	options = {}
}

doctorEdvarVangConvoTemplate:addScreen(already_talked);

quest_not_ready_yet = ConvoScreen:new {
	id = "quest_not_ready_yet",
	leftDialog = "@conversation/c_story1_1_doc:s_742", -- How is your health today?
	stopConversation = "true",
	options = {}
}

doctorEdvarVangConvoTemplate:addScreen(quest_not_ready_yet);

addConversationTemplate("doctorEdvarVangConvoTemplate", doctorEdvarVangConvoTemplate);
