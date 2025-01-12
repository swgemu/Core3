imperial_defector_conv = ConvoTemplate:new {
	initialScreen = "",
	templateType = "Lua",
	luaClassHandler = "ImperialDefectorConvoHandler",
	screens = {}
}

active_greeting = ConvoScreen:new {
    id = "active_greeting",
    leftDialog = "@conversation/c_impdefector_def:s_58", -- Excuse me, you are the person that will take me to Officer Ten'doora, are you not?
    stopConversation = "false",
    options = {
        {"@conversation/c_impdefector_def:s_60", "response_active"}, -- Yes, I'm here to take you to him.
    }
}
imperial_defector_conv:addScreen(active_greeting)

response_active = ConvoScreen:new {
    id = "response_active",
    leftDialog = "@conversation/c_impdefector_def:s_62", -- The plans have changed.  The information that I have is very time sensitive and I'll only slow you down.  You need to get to Officer Ten'doora within 20 minutes and give him this message:  Droids need Star Destroyers in the evening.
    stopConversation = "false",
    options = {
        {"@conversation/c_impdefector_def:s_68", "response_start"}, -- Got it.  I'm on my way.
        {"@conversation/c_impdefector_def:s_64", "response_surprise"}, -- Droids need Star Destroyers in the evening?  You have to be kidding me.
    }
}
imperial_defector_conv:addScreen(response_active)

response_surprise = ConvoScreen:new {
	id = "response_surprise",
	leftDialog = "@conversation/c_impdefector_def:s_66", -- Do you think that I'm risking my life out here for nothing?  Just tell him what I said and don't screw it up.  Time is ticking.
	stopConversation = false,
	options = {
		{"@conversation/c_impdefector_def:s_68", "response_start"}, -- Got it. I'm on my way.
	}
}
imperial_defector_conv:addScreen(response_surprise)

response_start = ConvoScreen:new {
	id = "response_start",
	leftDialog = "@conversation/c_impdefector_def:s_70", -- You have 20 minutes.  Hurry!
	stopConversation = "true",
	options = {}
}
imperial_defector_conv:addScreen(response_start)

get_moving = ConvoScreen:new {
	id = "get_moving",
	leftDialog = "@conversation/c_impdefector_def:s_72", -- Why are you standing around, get moving!
	stopConversation = "true",
	options = {}
}
imperial_defector_conv:addScreen(get_moving)

inactive_greeting = ConvoScreen:new {
    id = "inactive_greeting",
    leftDialog = "@conversation/c_impdefector_def:s_74", -- Can't a person just enjoy a lovely day?  Please leave me be.
    stopConversation = "true",
    options = {}
}
imperial_defector_conv:addScreen(inactive_greeting)

addConversationTemplate("imperial_defector_conv", imperial_defector_conv)
