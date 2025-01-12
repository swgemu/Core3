jaek_vercet_conv = ConvoTemplate:new {
	initialScreen = "",
	templateType = "Lua",
	luaClassHandler = "JaekVercetConvoHandler",
	screens = {}
}

imperial_greeting = ConvoScreen:new {
    id = "imperial_greeting",
    leftDialog = "@conversation/c_rebdefector_jaek:s_496", -- Hello!  I have an important mission for you.
    stopConversation = "false",
    options = {
        {"@conversation/c_rebdefector_jaek:s_498", "response_imperial_1"}, -- What must I do?
		{"@conversation/c_rebdefector_jaek:s_510", "response_start_imperial"}, -- I am always interested in a good mission.
		{"@conversation/c_rebdefector_jaek:s_514", "response_imperial_no_time"}, -- I don't have time right now.
    }
}
jaek_vercet_conv:addScreen(imperial_greeting)

response_imperial_1 = ConvoScreen:new {
    id = "response_imperial_1",
    leftDialog = "@conversation/c_rebdefector_jaek:s_500", -- Every so often, one of these rebel insurgents realizes that the Rebels are misguided.  In this case, this former rebel held some power in their poor excuse for a military.  His knowledge will help us crush the scum.
    stopConversation = "false",
    options = {
        {"@conversation/c_rebdefector_jaek:s_502", "response_start_imperial"}, -- I am honored to accept this assignment.
        {"@conversation/c_rebdefector_jaek:s_506", "response_deny_imperial"}, -- I don't have time, actually.
    }
}
jaek_vercet_conv:addScreen(response_imperial_1)

response_imperial_no_time = ConvoScreen:new {
    id = "response_imperial_no_time",
    leftDialog = "@conversation/c_rebdefector_jaek:s_516", -- If you are in the middle of something then get to it.  Talk to me when you have time.
    stopConversation = "true",
    options = {}
}
jaek_vercet_conv:addScreen(response_imperial_no_time)

response_start_imperial = ConvoScreen:new {
    id = "response_start_imperial",
    leftDialog = "@conversation/c_rebdefector_jaek:s_504", -- Good.  The defector is holed up in a safe place.  His former compatriots may have discovered that he is joining the right side.  I will give you coordinates to his location.  Escort him to the Emperor's Retreat and speak to Lt. Allard Lissara.  He will take it from there.
    stopConversation = "true",
    options = {}
}
jaek_vercet_conv:addScreen(response_start_imperial)

response_deny_imperial = ConvoScreen:new {
    id = "response_deny_imperial",
    leftDialog = "@conversation/c_rebdefector_jaek:s_508", -- If you are in the middle of something then get to it.  Talk to me when you have time.
	stopConversation = "true",
    options = {}
}
jaek_vercet_conv:addScreen(response_deny_imperial)

rebel_greeting = ConvoScreen:new {
    id = "rebel_greeting",
    leftDialog = "@conversation/c_rebdefector_jaek:s_518", -- Go away, scum.  I don't talk to your kind.
    stopConversation = "true",
    options = {}
}
jaek_vercet_conv:addScreen(rebel_greeting)

neutral_greeting = ConvoScreen:new {
    id = "neutral_greeting",
    leftDialog = "@conversation/c_rebdefector_jaek:s_520", -- Hello.  How would you like the opportunity to do something special for the Empire?
    stopConversation = "false",
    options = {
		{"@conversation/c_rebdefector_jaek:s_522", "response_neutral_1"}, -- How special?
	}
}
jaek_vercet_conv:addScreen(neutral_greeting)

response_neutral_1 = ConvoScreen:new {
    id = "response_neutral_1",
    leftDialog = "@conversation/c_rebdefector_jaek:s_524", -- Special enough that you will be gaining significant favor with the Imperial Military.
    stopConversation = "false",
    options = {
		{"@conversation/c_rebdefector_jaek:s_526", "response_start_neutral"}, -- I've always wanted an Imperial career.  I would be honored to help.
		{"@conversation/c_rebdefector_jaek:s_530", "response_deny_neutral"}, -- If it's all the same to you, I'd rather not get involved.
	}
}
jaek_vercet_conv:addScreen(response_neutral_1)

response_start_neutral = ConvoScreen:new {
    id = "response_start_neutral",
    leftDialog = "@conversation/c_rebdefector_jaek:s_528", -- Very good. I have a former rebel that wants the opportunity to make up for his rabble rousing.  The Emperor's retreat is fairly nearby and this guy needs an escort there.  When you get to the retreat, speak to Lt. Allard Lissara.
    stopConversation = "true",
    options = {}
}
jaek_vercet_conv:addScreen(response_start_neutral)

response_deny_neutral = ConvoScreen:new {
    id = "response_deny_neutral",
    leftDialog = "@conversation/c_rebdefector_jaek:s_532", -- It's your loss.  Not everyone is given a chance to show his loyalty to the senior officers.  If you change your mind, come back and talk to me.  Maybe I will have something for you then.
    stopConversation = "true",
    options = {}
}
jaek_vercet_conv:addScreen(response_deny_neutral)

where_defector = ConvoScreen:new {
	id = "where_defector",
	leftDialog = "@conversation/c_rebdefector_jaek:s_534", -- Good luck with your mission.  Remember, he's hiding west of Moenia.
	stopConversation = "true",
	options = {}
}
jaek_vercet_conv:addScreen(where_defector)

welcome_back = ConvoScreen:new {
	id = "welcome_back",
	leftDialog = "@conversation/c_rebdefector_jaek:s_536", -- Welcome back.  I have another informant that could use an experienced escort .  Would you be willing to take him to Lt. Lissara?
	stopConversation = "false",
	options = {
		{"@conversation/c_rebdefector_jaek:s_538", "response_start2"}, -- Certainly.  I am always willing to help.
		{"@conversation/c_rebdefector_jaek:s_542", "response_deny2"}, -- Not this time, I'm afraid.
	}
}
jaek_vercet_conv:addScreen(welcome_back)

response_start2 = ConvoScreen:new {
	id = "response_start2",
	leftDialog = "@conversation/c_rebdefector_jaek:s_540", -- Excellent.  Same situation as before then.  Pick up the defector west of Moenia. Take him to the Emperor's Retreat and talk to Lt. Allard Lissara.
	stopConversation = "true",
	options = {}
}
jaek_vercet_conv:addScreen(response_start2)

response_deny2 = ConvoScreen:new {
	id = "response_deny2",
	leftDialog = "@conversation/c_rebdefector_jaek:s_544", -- When you wish to help the Empire, come back and talk to me.
	stopConversation = "true",
	options = {}
}
jaek_vercet_conv:addScreen(response_deny2)

nice_day = ConvoScreen:new {
	id = "nice_day",
	leftDialog = "@conversation/c_rebdefector_jaek:s_546", -- What a nice day today.
	stopConversation = "true",
	options = {}
}
jaek_vercet_conv:addScreen(nice_day)

addConversationTemplate("jaek_vercet_conv", jaek_vercet_conv)
