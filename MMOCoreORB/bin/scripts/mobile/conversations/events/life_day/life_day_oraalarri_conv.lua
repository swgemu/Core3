lifeDayOraalarriConvoTemplate = ConvoTemplate:new {
	initialScreen = "",
	templateType = "Lua",
	luaClassHandler = "lifeDayOraalarriConvoHandler",
	screens = {}
}

im_sorry = ConvoScreen:new {
	id = "im_sorry",
	leftDialog = "@conversation/lifeday04b:s_5bd07d67", -- (Translated from Shyriiwook) I'm sorry, This is a private gathering for family and friends. 
	stopConversation = "true",
	options = {}
}

lifeDayOraalarriConvoTemplate:addScreen(im_sorry);

greetings = ConvoScreen:new {
	id = "greetings",
	leftDialog = "@conversation/lifeday04b:s_f0c65663", -- (Translated from Shyriiwook) Happy Life Day, friend! We are glad to have you celebrate with us.
	stopConversation = "false",
	options = {
		{"@conversation/lifeday04b:s_8a712dbc", "speak_to_others"}, -- Thank you. What do I do?
		{"@conversation/lifeday04b:s_6cd2786a", "i_understand"} -- I think I will do this later.
	}
}

lifeDayOraalarriConvoTemplate:addScreen(greetings);

speak_to_others = ConvoScreen:new {
	id = "speak_to_others",
	leftDialog = "@conversation/lifeday04b:s_d8cde9a", -- Speak with all those assembled to learn about our holiday. Once you have heard what we have to say, I will see if we can find a Life Day gift for you.
	stopConversation = "true",
	options = {}
}

lifeDayOraalarriConvoTemplate:addScreen(speak_to_others);

i_understand = ConvoScreen:new {
	id = "i_understand",
	leftDialog = "@conversation/lifeday04b:s_feeecf48", -- I understand, but if you wait too long, the time will pass and you will have to wait until next year to join us. Be safe, friend.
	stopConversation = "true",
	options = {}
}

lifeDayOraalarriConvoTemplate:addScreen(i_understand);

no_gift = ConvoScreen:new {
	id = "no_gift",
	leftDialog = "@conversation/lifeday04b:s_b85028af", -- (Translated from Shyriiwook) I hope you have learned something of our ways. Since you have not been with our community for thirty cycles, I do not have a gift for you, but I hope you will keep the spirit of Life Day alive in your heart and return to us next year.
	stopConversation = "true",
	options = {}
}

lifeDayOraalarriConvoTemplate:addScreen(no_gift);

have_spoken = ConvoScreen:new {
	id = "have_spoken",
	leftDialog = "@conversation/lifeday04b:s_b874dc09", -- (Translated from Shyriiwook) You have spoken to those assembled and learned of our ways. Hopefully this day brings you closer to freedom and to harmony and to peace. May you hold Life Day as dear as we do.
	stopConversation = "false",
	options = {
		{"@conversation/lifeday04b:s_ebbd31aa", "have_gifts"} -- I have learned a lot.
	}
}

lifeDayOraalarriConvoTemplate:addScreen(have_spoken);

have_gifts = ConvoScreen:new {
	id = "have_gifts",
	leftDialog = "@conversation/lifeday04b:s_af9f8883", -- (Translated from Shyriiwook) For those beings that have been a part of our community for at least thirty cycles, we have collected gifts to help you remember this day.
	stopConversation = "false",
	options = {}
}

lifeDayOraalarriConvoTemplate:addScreen(have_gifts);

gift_non_wookiee = ConvoScreen:new {
	id = "gift_non_wookiee",
	leftDialog = "@conversation/lifeday04b:s_66b5743f", -- (Translated from Shyriiwook) This is a gift that reflects our Wookiee heritage. We hope you will display your gift with pride and remember your time with us.
	stopConversation = "true",
	options = {}
}

lifeDayOraalarriConvoTemplate:addScreen(gift_non_wookiee);

gift_wookiee = ConvoScreen:new {
	id = "gift_wookiee",
	leftDialog = "@conversation/lifeday04b:s_f0f674e2", -- (Translated from Shyriiwook) Since you are one of our own, you have a choice. You may choose a traditional Life Day robe that may only be worn by Wookiees or you may receive another gift.
	stopConversation = "false",
	options = {
		{"@conversation/lifeday04b:s_352585ec", "enjoy_robe"}, -- I would like the Wookiee Life Day Robe.
		{"@conversation/lifeday04b:s_52645cdc", "enjoy_other_gift"} -- I would like another Life Day gift.
	}
}

lifeDayOraalarriConvoTemplate:addScreen(gift_wookiee);

enjoy_robe = ConvoScreen:new {
	id = "enjoy_robe",
	leftDialog = "@conversation/lifeday04b:s_de3b1306", -- (Translated from Shyriiwook) Enjoy your gift. Happy Life Day to you.
	stopConversation = "true",
	options = {}
}

lifeDayOraalarriConvoTemplate:addScreen(enjoy_robe);

enjoy_other_gift = ConvoScreen:new {
	id = "enjoy_other_gift",
	leftDialog = "@conversation/lifeday04b:s_de3b1306", -- (Translated from Shyriiwook) Enjoy your gift. Happy Life Day to you.
	stopConversation = "true",
	options = {}
}

lifeDayOraalarriConvoTemplate:addScreen(enjoy_other_gift);

return_complete = ConvoScreen:new {
	id = "return_complete",
	leftDialog = "@conversation/lifeday04b:s_fe83540d", -- (Translated from Shyriiwook) It is good to see you again. Thank you for taking part in our celebration. We hope to see you next year.
	stopConversation = "true",
	options = {}
}

lifeDayOraalarriConvoTemplate:addScreen(return_complete);

addConversationTemplate("lifeDayOraalarriConvoTemplate", lifeDayOraalarriConvoTemplate);
