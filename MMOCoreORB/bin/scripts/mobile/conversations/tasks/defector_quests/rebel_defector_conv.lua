rebel_defector_conv = ConvoTemplate:new {
	initialScreen = "",
	templateType = "Lua",
	luaClassHandler = "RebelDefectorConvoHandler",
	screens = {}
}

active_greeting = ConvoScreen:new {
    id = "active_greeting",
    leftDialog = "@conversation/c_rebdefector_def:s_800", -- Hey, are you the person that is supposed to take me to talk to Allard?
    stopConversation = "false",
    options = {
        {"@conversation/c_rebdefector_def:s_802", "response_active"}, -- Yes, I am supposed to take you.
    }
}
rebel_defector_conv:addScreen(active_greeting)

response_active = ConvoScreen:new {
    id = "response_active",
    leftDialog = "@conversation/c_rebdefector_def:s_804", -- Well, I'm sorry to do this, but there has been a change of plan.  The information that I have is very time sensitive and this bum leg of mine will only slow you down.  You need to get to Allard within 20 minutes and give him this message: Wookiees walk at night in the trees of Naboo.
    stopConversation = "false",
    options = {
        {"@conversation/c_rebdefector_def:s_810", "response_start"}, -- Got it.  I'm on my way.
        {"@conversation/c_rebdefector_def:s_806", "response_surprise"}, -- Wookiees walk at night in the trees of Naboo?  What kind of code is that?
    }
}
rebel_defector_conv:addScreen(response_active)

response_surprise = ConvoScreen:new {
	id = "response_surprise",
	leftDialog = "@conversation/c_rebdefector_def:s_808", -- It's one that one that will get us both killed if you don't hurry.  Go now!
	stopConversation = false,
	options = {
		{"@conversation/c_rebdefector_def:s_810", "response_start"}, -- Got it. I'm on my way.
	}
}
rebel_defector_conv:addScreen(response_surprise)

response_start = ConvoScreen:new {
	id = "response_start",
	leftDialog = "@conversation/c_rebdefector_def:s_812", -- You have 20 minutes.  Hurry!
	stopConversation = "true",
	options = {}
}
rebel_defector_conv:addScreen(response_start)

get_moving = ConvoScreen:new {
	id = "get_moving",
	leftDialog = "@conversation/c_rebdefector_def:s_814", -- Why are you standing around, get moving!
	stopConversation = "true",
	options = {}
}
rebel_defector_conv:addScreen(get_moving)

inactive_greeting = ConvoScreen.new {
    id = "inactive_greeting",
    leftDialog = "@conversation/c_rebdefector_def:s_816", -- Can't a person just enjoy a lovely day?  Please leave me be.
    stopConversation = "true",
    options = {}
}
rebel_defector_conv:addScreen(inactive_greeting)

addConversationTemplate("rebel_defector_conv", rebel_defector_conv)
