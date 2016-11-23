heraldNaboo2ConvoTemplate = ConvoTemplate:new {
	initialScreen = "init",
	templateType = "Lua",
	luaClassHandler = "multi_dest_herald_conv_handler",
	screens = {}
}

init = ConvoScreen:new {
	id = "init",
	leftDialog = "@conversation/heraldnaboo2:s_91946cec", -- I apologize. I'm in a bit of a hurry. I only planned to be here in this city for only a few hours. Gathering these supplies took longer than I thought. I really must get back to my studies..
	stopConversation = "false",
	options = {
		{"@conversation/heraldnaboo2:s_adb2e1e", "bye"}, -- Okay. I'll let you go.
		{"@conversation/heraldnaboo2:s_9adfee98", "veermok"}, -- What do you study?
	}
}
heraldNaboo2ConvoTemplate:addScreen(init);

bye = ConvoScreen:new {
	id = "bye",
	leftDialog = "@conversation/heraldnaboo2:s_60613aaf", -- Bye!
	stopConversation = "true",
	options = {}
}
heraldNaboo2ConvoTemplate:addScreen(bye);

veermok = ConvoScreen:new {
	id = "veermok",
	leftDialog = "@conversation/heraldnaboo2:s_d482409c", -- The veermok, of course! Have you seen a more interesting creature? I take every chance I can get to educate others on my findings. Too bad I don't have the time right now! You can go see them yourself, if you'd like.
	stopConversation = "false",
	options = {
		{"@conversation/heraldnaboo2:s_d6695e83", "some_other_time"}, -- No thanks.
		{"@conversation/heraldnaboo2:s_137b7430", "interested"}, -- I'd like to, actually.
	}
}
heraldNaboo2ConvoTemplate:addScreen(veermok);

some_other_time = ConvoScreen:new {
	id = "some_other_time",
	leftDialog = "@conversation/heraldnaboo2:s_401feeb9", -- Maybe some other time, then. Maybe you'd rather visit the Gungans at their stronghold. They're always looking for new allies. They're my allies, in fact, and very supportive of my research. If you're not interested, I really must get going. I hope you don't mind.
	stopConversation = "false",
	options = {
		{"@conversation/heraldnaboo2:s_8182146c", "bye"}, -- I have to go too. Bye!
		{"@conversation/heraldnaboo2:s_7d197017", "loc1"}, -- Where are the Gungans?
	}
}
heraldNaboo2ConvoTemplate:addScreen(some_other_time);

loc1 = ConvoScreen:new {
	id = "loc1",
	leftDialog = "@conversation/heraldnaboo2:s_23545d1", -- Oh, you know, I really can't explain it right now. Let me download the information into your datapad. I must be well on my way. It's feeding time for the veermok. It's such a sight to see!
	stopConversation = "true",
	options = {}
}
heraldNaboo2ConvoTemplate:addScreen(loc1);

interested = ConvoScreen:new {
	id = "interested",
	leftDialog = "@conversation/heraldnaboo2:s_fcab5bd8", -- You're interested in them as much as I am! How exciting! After I gather my supplies, I'm headed to the Gungan Stronghold, however. I have some deals to conduct with my allies there. The Gungans are really friendly when you get to know them. I'll be off to my studies after that. It's the vermok's feeding time.
	stopConversation = "false",
	options = {
		{"@conversation/heraldnaboo2:s_b6fc48e0", "loc2"}, -- So, where are these veermoks?
		{"@conversation/heraldnaboo2:s_48315a3d", "loc1a"}, -- I think I'll visit them too.
	}
}
heraldNaboo2ConvoTemplate:addScreen(interested);

loc2 = ConvoScreen:new {
	id = "loc2",
	leftDialog = "@conversation/heraldnaboo2:s_c4e2d7fa", -- Oh yes! I babble on and on so much. I'll just download the information into your datapad. It's really the quickest way. I really must get going.
	stopConversation = "true",
	options = {}
}
heraldNaboo2ConvoTemplate:addScreen(loc2);

loc1a = ConvoScreen:new {
	id = "loc1a",
	leftDialog = "@conversation/heraldnaboo2:s_b2b33aae", -- You and I are so alike. They don't like visitors much, but maybe you can ally with them as well. Let me download the information into your datapad, assuming you have one.
	stopConversation = "true",
	options = {}
}
heraldNaboo2ConvoTemplate:addScreen(loc1a);

addConversationTemplate("heraldNaboo2ConvoTemplate", heraldNaboo2ConvoTemplate);
