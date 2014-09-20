lifeDayAnarraConvoTemplate = ConvoTemplate:new {
	initialScreen = "",
	templateType = "Lua",
	luaClassHandler = "lifeDayAnarraConvoHandler",
	screens = {}
}

elder_first = ConvoScreen:new {
	id = "elder_first",
	leftDialog = "@conversation/lifeday04c:s_98c49a08", -- (Translated from Shyriiwook) You should speak to our Elder first. Happy Life Day to you.
	stopConversation = "true",
	options = {}
}

lifeDayAnarraConvoTemplate:addScreen(elder_first);

renewel = ConvoScreen:new {
	id = "renewel",
	leftDialog = "@conversation/lifeday04c:s_f25a4a72", -- (Translated from Shyriiwook) Renewal of Life. This is one of the goals of Life Day. Because of how the Empire has treated so many of our kind, this aspect of Life Day has taken on even greater meaning.
	stopConversation = "false",
	options = {
		{"@conversation/lifeday04c:s_8e0ee46c", "life_was_simple"} -- What has the Empire done to Wookiees?
	}
}

lifeDayAnarraConvoTemplate:addScreen(renewel);

life_was_simple = ConvoScreen:new {
	id = "life_was_simple",
	leftDialog = "@conversation/lifeday04c:s_efa923bc", -- (Translated from Shyriiwook) Life on our homeworld was simple and peaceful. We did not make war, nor were we a violent race. This made us easy targets for the Empire who desired our strength. Many were forced into labor camps. Some Wookiees were even forced to help build the Death Star.
	stopConversation = "false",
	options = {
		{"@conversation/lifeday04c:s_959f717", "appreciate_freedom"} -- I see. Go on.
	}
}

lifeDayAnarraConvoTemplate:addScreen(life_was_simple);

appreciate_freedom = ConvoScreen:new {
	id = "appreciate_freedom",
	leftDialog = "@conversation/lifeday04c:s_f34ce8c", -- (Translated from Shyriiwook) Because of the Empire, we have learned to appreciate our freedom. We cannot take our lives for granted. Each sunrise, each childbirth, each breath is a renewal, a reminder that we must live each day to the fullest.
	stopConversation = "false",
	options = {}
}

lifeDayAnarraConvoTemplate:addScreen(appreciate_freedom);

work_for_empire = ConvoScreen:new {
	id = "work_for_empire",
	leftDialog = "@conversation/lifeday04c:s_801a269f", -- (Translated from Shyriiwook) I've heard you work for the Empire. If that's true, you should reconsider your allegiances. You may be good but the higher up you go, the darker the world becomes.
	stopConversation = "false",
	options = {
		{"@conversation/lifeday04c:s_bd5e746e", "hope_you_will"} -- I'll consider your words.
	}
}

lifeDayAnarraConvoTemplate:addScreen(work_for_empire);

hope_you_will = ConvoScreen:new {
	id = "hope_you_will",
	leftDialog = "@conversation/lifeday04c:s_4f6d5fb7", -- (Translated from Shyriiwook) I hope you will. Regardless, remember to be thankful for life and all that comes with it. Happy Life Day to you.
	stopConversation = "true",
	options = {}
}

lifeDayAnarraConvoTemplate:addScreen(hope_you_will);

share_our_tale = ConvoScreen:new {
	id = "share_our_tale",
	leftDialog = "@conversation/lifeday04c:s_cf3aa2f6", -- (Translated from Shyriiwook) I hope you will take our tale and share it with others so that others may learn how to live each day to the fullest...and to not take their own freedom for granted.
	stopConversation = "false",
	options = {
		{"@conversation/lifeday04c:s_9103b44a", "thank_you"} -- I will do that.
	}
}

lifeDayAnarraConvoTemplate:addScreen(share_our_tale);

thank_you = ConvoScreen:new {
	id = "thank_you",
	leftDialog = "@conversation/lifeday04c:s_d7baeead", -- (Translated from Shyriiwook) Thank you. Remember to celebrate your life and the lives of those around you. Happy Life Day.
	stopConversation = "true",
	options = {}
}

lifeDayAnarraConvoTemplate:addScreen(thank_you);

tell_again = ConvoScreen:new {
	id = "tell_again",
	leftDialog = "@conversation/lifeday04c:s_a60b4b13", -- (Translated from Shyriiwook) I enjoyed our conversation earlier! Would you like to hear about the Renewal of Life again?
	stopConversation = "false",
	options = {
		{"@conversation/lifeday04c:s_7a600ade", "renewel"}, -- Yes, please tell me again.
		{"@conversation/lifeday04c:s_554c5307", "pleasure"} -- No thank you.
	}
}

lifeDayAnarraConvoTemplate:addScreen(tell_again);

pleasure = ConvoScreen:new {
	id = "pleasure",
	leftDialog = "@conversation/lifeday04c:s_1256a081", -- (Translated from Shyriiwook) Well it's a pleasure to see you again. Happy Life Day!
	stopConversation = "true",
	options = {}
}

lifeDayAnarraConvoTemplate:addScreen(pleasure);

addConversationTemplate("lifeDayAnarraConvoTemplate", lifeDayAnarraConvoTemplate);
