lifeDayTebeurraConvoTemplate = ConvoTemplate:new {
	initialScreen = "",
	templateType = "Lua",
	luaClassHandler = "lifeDayTebeurraConvoHandler",
	screens = {}
}

elder_first = ConvoScreen:new {
	id = "elder_first",
	leftDialog = "@conversation/lifeday04e:s_a104d858", -- (Translated from Shyriiwook) You should speak with our Elder first.
	stopConversation = "true",
	options = {}
}

lifeDayTebeurraConvoTemplate:addScreen(elder_first);

life_day_began = ConvoScreen:new {
	id = "life_day_began",
	leftDialog = "@conversation/lifeday04e:s_3c9de914", -- (Translated from Shyriiwook) Life Day began as a holiday celebrated only by us Wookiees, but it has since grown beyond the borders of Kashyyyk.
	stopConversation = "false",
	options = {
		{"@conversation/lifeday04e:s_77e48d5b", "concepts"} -- What do you mean?
	}
}

lifeDayTebeurraConvoTemplate:addScreen(life_day_began);

concepts = ConvoScreen:new {
	id = "concepts",
	leftDialog = "@conversation/lifeday04e:s_2110a567", -- (Translated from Shyriiwook) The concepts of Life Day are universal in nature. Many who have learned of Life Day have begun to celebrate it on their own worlds. It is our hope that you will too.
	stopConversation = "false",
	options = {
		{"@conversation/lifeday04e:s_533ce9b7", "important"} -- How is Life Day celebrated on your world?
	}
}

lifeDayTebeurraConvoTemplate:addScreen(concepts);

important = ConvoScreen:new {
	id = "important",
	leftDialog = "@conversation/lifeday04e:s_467df5bd", -- (Translated from Shyriiwook) It is important to us to be home for Life Day. It is not unusual for a Wookiee to brave many hardships to get home to celebrate at the Tree of Life.
	stopConversation = "false",
	options = {
		{"@conversation/lifeday04e:s_b84f1c5d", "the_empire"} -- But you are not on your homeworld now. Why?
	}
}

lifeDayTebeurraConvoTemplate:addScreen(important);

the_empire = ConvoScreen:new {
	id = "the_empire",
	leftDialog = "@conversation/lifeday04e:s_cc720b6", -- (Translated from Shyriiwook) Because of the Empire, it is not safe. Some will still elude the Empire and return, but for now, we do what we can.
	stopConversation = "false",
	options = {
		{"@conversation/lifeday04e:s_f9a62733", "let_others"} -- What else can you tell me?
	}
}

lifeDayTebeurraConvoTemplate:addScreen(the_empire);

let_others = ConvoScreen:new {
	id = "let_others",
	leftDialog = "@conversation/lifeday04e:s_29cc9282", -- (Translated from Shyriiwook) I will let the others here tell you. Happy Life Day to you.
	stopConversation = "true",
	options = {}
}

lifeDayTebeurraConvoTemplate:addScreen(let_others);

hear_again = ConvoScreen:new {
	id = "hear_again",
	leftDialog = "@conversation/lifeday04e:s_187a402b", -- (Translated from Shyriiwook) Thanks for taking part in our festivities! Would you like to hear about origins of Life Day again?
	stopConversation = "false",
	options = {
		{"@conversation/lifeday04e:s_f4a3b496", "life_day_began"}, -- Sure, tell me about Life Day again.
		{"@conversation/lifeday04e:s_9c6c907c", "pleasure"} -- No thanks, just thought I'd say hello again.
	}
}

lifeDayTebeurraConvoTemplate:addScreen(hear_again);

pleasure = ConvoScreen:new {
	id = "pleasure",
	leftDialog = "@conversation/lifeday04e:s_1cb72c3b", -- (Translated from Shyriiwook) It was a pleasure to see you again. Happy Life Day!
	stopConversation = "true",
	options = {}
}

lifeDayTebeurraConvoTemplate:addScreen(pleasure);

addConversationTemplate("lifeDayTebeurraConvoTemplate", lifeDayTebeurraConvoTemplate);
