jom_irimore_conv = ConvoTemplate:new {
	initialScreen = "",
	templateType = "Lua",
	luaClassHandler = "JomIrimoreConvoHandler",
	screens = {}
}

rebel_greeting = ConvoScreen:new {
    id = "rebel_greeting",
    leftDialog = "@conversation/c_impdefector_jom:s_550", -- Hello!  I have an important mission for the Alliance, if you have the time.
    stopConversation = "false",
    options = {
        {"@conversation/c_impdefector_jom:s_552", "response_rebel_1"}, -- Time? What does this entail?
		{"@conversation/c_impdefector_jom:s_556", "response_start_rebel"}, -- I would be happy to help.
		{"@conversation/c_impdefector_jom:s_568", "response_rebel_no_time"}, -- I don't have time, actually.
    }
}
jom_irimore_conv:addScreen(rebel_greeting)

response_rebel_1 = ConvoScreen:new {
    id = "response_rebel_1",
    leftDialog = "@conversation/c_impdefector_jom:s_554", -- I'm sure you have heard about defectors from the Empire.  We have a fairly high-ranking officer that has decided to come over to the right side.  He's hiding out northeast of here.
    stopConversation = "false",
    options = {
        {"@conversation/c_impdefector_jom:s_564", "response_start_rebel"}, -- I always have time for my brothers-in-arms.
        {"@conversation/c_impdefector_jom:s_560", "response_deny_rebel"}, -- I'd rather not.  Those Imperials make my skin crawl.
    }
}
jom_irimore_conv:addScreen(response_rebel_1)

response_rebel_no_time = ConvoScreen:new {
	id = "response_rebel_no_time",
	leftDialog = "@conversation/c_impdefector_jom:s_570", -- I'm sorry to hear that.  Maybe I will have something for you later, if you have time.
	stopConversation = "true",
	options = {}
}
jom_irimore_conv:addScreen(response_rebel_no_time)

response_start_rebel = ConvoScreen:new {
    id = "response_start_rebel",
    leftDialog = "@conversation/c_impdefector_jom:s_558", -- Thank you!  There's an Imperial defector hiding northwest of Kor Vella.  I'll give you the location in your datapad.  Take him to the Rebel Base to the north.  It's not a short trip, but it will be worth it.  When you get there, talk to Teslo Ten'doora.
    stopConversation = "true",
    options = {}
}
jom_irimore_conv:addScreen(response_start_rebel)

response_deny_rebel = ConvoScreen:new {
    id = "response_deny_rebel",
    leftDialog = "@conversation/c_impdefector_jom:s_562", -- Well, I'm glad you told me.  I wouldn't want you to be in the position of putting your life on  the line for something you don't think you can do.  If you change your attitude, come back and talk to me.
    stopConversation = "true",
    options = {}
}
jom_irimore_conv:addScreen(response_deny_rebel)

imperial_greeting = ConvoScreen:new {
    id = "imperial_greeting",
    leftDialog = "@conversation/c_impdefector_jom:s_572", -- I don't believe I wish to speak to you.  When you change your view on galactic politics, maybe  we can talk then.
    stopConversation = "true",
    options = {}
}
jom_irimore_conv:addScreen(imperial_greeting)

neutral_greeting = ConvoScreen:new {
	id = "neutral_greeting",
	leftDialog = "@conversation/c_impdefector_jom:s_574", -- You look to be a trustworthy sort, I have an important mission that needs doing.  Would you be interested?
	stopConversation = "false",
	options = {
		{"@conversation/c_impdefector_jom:s_576", "response_neutral_1"}, -- Who will I be doing this job for?
	}
}
jom_irimore_conv:addScreen(neutral_greeting)

response_neutral_1 = ConvoScreen:new {
    id = "response_neutral_1",
    leftDialog = "@conversation/c_impdefector_jom:s_578", -- Well, I will tell you this - you may wish to avoid any Imperial entanglements while on this mission.
    stopConversation = "false",
    options = {
        {"@conversation/c_impdefector_jom:s_580", "response_start_neutral"}, -- I'll be helping the Rebel Alliance?  Sign me up!
        {"@conversation/c_impdefector_jom:s_584", "response_deny_neutral"}, -- I'd rather not.  Imperial entanglements seem to follow me.
    }
}
jom_irimore_conv:addScreen(response_neutral_1)

response_start_neutral = ConvoScreen:new {
	id = "response_start_neutral",
	leftDialog = "@conversation/c_impdefector_jom:s_582", -- Thank you!  There's an Imperial defector hiding northwest of Kor Vella.  I'll give you the location in your datapad.  Take him to the Rebel Base to the north.  It's not a short trip, but it will be worth it.  When you get there, talk to Teslo Ten'doora.
	stopConversation = "true",
	options = {}
}
jom_irimore_conv:addScreen(response_start_neutral)

response_deny_neutral = ConvoScreen:new {
	id = "response_deny_neutral",
	leftDialog = "@conversation/c_impdefector_jom:s_586", -- Maybe next time.  Come back if you change your mind.
	stopConversation = "true",
	options = {}
}
jom_irimore_conv:addScreen(response_deny_neutral)

where_defector = ConvoScreen:new {
	id = "where_defector",
	leftDialog = "@conversation/c_impdefector_jom:s_588", -- Good luck with your mission.  Remember, he's hiding near the broken bridge.
	stopConversation = "true",
	options = {}
}
jom_irimore_conv:addScreen(where_defector)

welcome_back = ConvoScreen:new {
	id = "welcome_back",
	leftDialog = "@conversation/c_impdefector_jom:s_590", -- Welcome back.  I have another defector that could use an escort of your calibur.  Would you be willing to take him up to the base?
	stopConversation = "false",
	options = {
		{"@conversation/c_impdefector_jom:s_592", "response_start2"}, -- Certainly.  I am always willing to help.
		{"@conversation/c_impdefector_jom:s_596", "response_deny2"}, -- Not this time, I'm afraid.
	}
}
jom_irimore_conv:addScreen(welcome_back)

response_start2 = ConvoScreen:new {
	id = "response_start2",
	leftDialog = "@conversation/c_impdefector_jom:s_594", -- Excellent.  Same situation as before then.  Pick up the defector in the trench near the broken bridge. Take him to the rebel base and talk to Teslo Ten'doora.
	stopConversation = "true",
	options = {}
}
jom_irimore_conv:addScreen(response_start2)

response_deny2 = ConvoScreen:new {
	id = "response_deny2",
	leftDialog = "@conversation/c_impdefector_jom:s_598", -- Maybe next time, then.
	stopConversation = "true",
	options = {}
}
jom_irimore_conv:addScreen(response_deny2)

nice_day = ConvoScreen:new {
	id = "nice_day",
	leftDialog = "@conversation/c_impdefector_jom:s_600", -- What a nice day today.
	options = {}
}
jom_irimore_conv:addScreen(nice_day)

addConversationTemplate("jom_irimore_conv", jom_irimore_conv)
