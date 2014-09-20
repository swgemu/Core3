lifeDayKkatamkConvoTemplate = ConvoTemplate:new {
	initialScreen = "",
	templateType = "Lua",
	luaClassHandler = "lifeDayKkatamkConvoHandler",
	screens = {}
}


greetings = ConvoScreen:new {
	id = "greetings",
	leftDialog = "@conversation/lifeday04a:s_ada83d27", -- (Translated from Shyriiwook) Greetings friend! You are just in time to join our Life Day celebrations.
	stopConversation = "false",
	options = {
		{"@conversation/lifeday04a:s_643fa34", "explain_life_day"}, -- Life Day? What's that?
		{"@conversation/lifeday04a:s_acf458b4", "too_bad"} -- Life Day? No thanks. I've got other things to do.
	}
}

lifeDayKkatamkConvoTemplate:addScreen(greetings);

explain_life_day = ConvoScreen:new {
	id = "explain_life_day",
	leftDialog = "@conversation/lifeday04a:s_50a0c963", -- (Translated from Shyriiwook) Life Day is a traditional celebration on Kashyyyk, the Wookiee homeworld. I would tell you more, but it is best you experience a Life Day ceremony for yourself.
	stopConversation = "false",
	options = {
		{"@conversation/lifeday04a:s_2a85dd74", "waypoint"}, -- I would like that. What do I do?
		{"@conversation/lifeday04a:s_20268f64", "too_bad"} -- I think I'll pass. Thanks anyway.
	}
}

lifeDayKkatamkConvoTemplate:addScreen(explain_life_day);

too_bad = ConvoScreen:new {
	id = "too_bad",
	leftDialog = "@conversation/lifeday04a:s_b3f5b52e", -- (Translated from Shyriiwook) That is too bad. If you change your mind be sure to find me.
	stopConversation = "true",
	options = {}
}

lifeDayKkatamkConvoTemplate:addScreen(too_bad);

waypoint = ConvoScreen:new {
	id = "waypoint",
	leftDialog = "@conversation/lifeday04a:s_dbcb339", -- (Translated from Shyriiwook) I will give you a waypoint where some of my family have gathered to celebrate. Go there and they will tell you more. Happy Life Day to you.
	stopConversation = "true",
	options = {}
}

lifeDayKkatamkConvoTemplate:addScreen(waypoint);

greetings_wookiee = ConvoScreen:new {
	id = "greetings_wookiee",
	leftDialog = "@conversation/lifeday04a:s_311837be", -- (Translated from Shyriiwook) Ah! A Wookiee cousin! Are you here to celebrate Life Day? 
	stopConversation = "false",
	options = {
		{"@conversation/lifeday04a:s_20e6f0a5", "waypoint_wookiee"}, -- Yes I am. Where can I find a Life Day gathering?
		{"@conversation/lifeday04a:s_acf458b4", "too_bad"} -- Life Day? No thanks. I've got other things to do.
	}
}

lifeDayKkatamkConvoTemplate:addScreen(greetings_wookiee);

waypoint_wookiee = ConvoScreen:new {
	id = "waypoint_wookiee",
	leftDialog = "@conversation/lifeday04a:s_f9bf77a0", -- (Translated from Shyriiwook) I will give you a waypoint where some of my family have gathered to celebrate. Go there and they will welcome you with open arms. Happy Life Day to you.
	stopConversation = "true",
	options = {}
}

lifeDayKkatamkConvoTemplate:addScreen(waypoint_wookiee);

return_incomplete = ConvoScreen:new {
	id = "return_incomplete",
	leftDialog = "@conversation/lifeday04a:s_da120aad", -- (Translated from Shyriiwook) You're back. Were you unable to find the camp?
	stopConversation = "false",
	options = {
		{"@conversation/lifeday04a:s_8fa670", "new_waypoint"} -- Yes. I need directions again.
	}
}

lifeDayKkatamkConvoTemplate:addScreen(return_incomplete);

new_waypoint = ConvoScreen:new {
	id = "new_waypoint",
	leftDialog = "@conversation/lifeday04a:s_1d62f66a", -- (Translated from Shyriiwook) I understand. Sometimes we have to move around to escape persecution. You can find the celebration here.
	stopConversation = "true",
	options = {}
}

lifeDayKkatamkConvoTemplate:addScreen(new_waypoint);

return_complete = ConvoScreen:new {
	id = "return_complete",
	leftDialog = "@conversation/lifeday04a:s_5c9098df", -- (Translated from Shyriiwook) You're back! I'm glad you were able to take part in our traditions. Be sure to spread the harmony of Life Day to all the beings you meet today.
	stopConversation = "true",
	options = {}
}

lifeDayKkatamkConvoTemplate:addScreen(return_complete);

addConversationTemplate("lifeDayKkatamkConvoTemplate", lifeDayKkatamkConvoTemplate);
