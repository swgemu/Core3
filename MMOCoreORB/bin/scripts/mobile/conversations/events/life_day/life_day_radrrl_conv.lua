lifeDayRadrrlConvoTemplate = ConvoTemplate:new {
	initialScreen = "",
	templateType = "Lua",
	luaClassHandler = "lifeDayRadrrlConvoHandler",
	screens = {}
}

elder_first = ConvoScreen:new {
	id = "elder_first",
	leftDialog = "@conversation/lifeday04d:s_6cdb10e7", -- (Translated from Shyriiwook) You should speak with our Elder first. Happy Life Day to you.
	stopConversation = "true",
	options = {}
}

lifeDayRadrrlConvoTemplate:addScreen(elder_first);

rememberance = ConvoScreen:new {
	id = "rememberance",
	leftDialog = "@conversation/lifeday04d:s_a1c6d00b", -- (Translated from Shyriiwook) Rememberance of loved ones lost. This is one of the major tenets of Life Day. We use this time to reflect on our ancestors and family members who are no longer among the living.
	stopConversation = "false",
	options = {
		{"@conversation/lifeday04d:s_edb238bc", "sacrifices"} -- Go on.
	}
}

lifeDayRadrrlConvoTemplate:addScreen(rememberance);

sacrifices = ConvoScreen:new {
	id = "sacrifices",
	leftDialog = "@conversation/lifeday04d:s_bcbad5b7", -- (Translated from Shyriiwook) We remember their sacrifices and deeds and the things that made us laugh. By remembering the dead we keep their memory alive and learn from the actions that came before. We use the Life Day orb to help us honor the fallen.
	stopConversation = "false",
	options = {
		{"@conversation/lifeday04d:s_dc4149ee", "participate"}, -- I understand. Go on.
		{"@conversation/lifeday04d:s_775904c7", "life_day_orb"} -- Life Day orb?
	}
}

lifeDayRadrrlConvoTemplate:addScreen(sacrifices);

participate = ConvoScreen:new {
	id = "participate",
	leftDialog = "@conversation/lifeday04d:s_9df9f74c", -- (Translated from Shyriiwook) As you participate today, think of fallen comrades and family members who are no longer with us and use their lives as a lesson to improve your own. Happy Life Day to you.
	stopConversation = "true",
	options = {}
}

lifeDayRadrrlConvoTemplate:addScreen(participate);

life_day_orb = ConvoScreen:new {
	id = "life_day_orb",
	leftDialog = "@conversation/lifeday04d:s_b13f8480", -- (Translated from Shyriiwook) The Life Day orb is a traditional part of our celebration. It shows a field of stars representing the afterlife. We beings of Kashyyyk believe that when we die that we walk off into the stars.
	stopConversation = "false",
	options = {
		{"@conversation/lifeday04d:s_dc4149ee", "always_remember"} -- I understand. Go on.
	}
}

lifeDayRadrrlConvoTemplate:addScreen(life_day_orb);

always_remember = ConvoScreen:new {
	id = "always_remember",
	leftDialog = "@conversation/lifeday04d:s_e26d0d6", -- (Translated from Shyriiwook) Always remember to think of fallen comrades and family members who are no longer with us and use their lives as a lesson to improve your own. Happy Life Day to you.
	stopConversation = "true",
	options = {}
}

lifeDayRadrrlConvoTemplate:addScreen(always_remember);

hello_again = ConvoScreen:new {
	id = "hello_again",
	leftDialog = "@conversation/lifeday04d:s_85a86bcd", -- (Translated from Shyriiwook) Hello again! Rememberance of those who came before us is my personal favorite part of Life Day. I love hearing about all the things our ancestors did. I'd be happy to tell you about it again if you'd like.
	stopConversation = "false",
	options = {
		{"@conversation/lifeday04d:s_611f31c3", "rememberance"}, -- Sure, I'd be happy to hear about that again.
		{"@conversation/lifeday04d:s_a2945896", "thank_you"} -- That's ok, I'm familiar with that now.
	}
}

lifeDayRadrrlConvoTemplate:addScreen(hello_again);

thank_you = ConvoScreen:new {
	id = "thank_you",
	leftDialog = "@conversation/lifeday04d:s_fd38d370", -- (Translated from Shyriiwook) Well thank you for dropping by. Happy Life Day!
	stopConversation = "true",
	options = {}
}

lifeDayRadrrlConvoTemplate:addScreen(thank_you);

addConversationTemplate("lifeDayRadrrlConvoTemplate", lifeDayRadrrlConvoTemplate);
