teslo_tendoora_conv = ConvoTemplate:new {
	initialScreen = "",
	templateType = "Lua",
	luaClassHandler = "TesloTendooraConvoHandler",
	screens = {}
}

active_greeting = ConvoScreen:new {
    id = "active_greeting",
    leftDialog = "@conversation/c_impdefector_teslo:s_53", -- Congratulations on making it this far.  How treacherous was the trip?
    stopConversation = "false",
    options = {
        {"@conversation/c_impdefector_teslo:s_55", "response_attacked"}, -- The defector sent me alone and I was attacked by mercenaries.
		{"@conversation/c_impdefector_teslo:s_67", "response_nothing"}, -- It was nothing. I have a message for you.
    }
}
teslo_tendoora_conv:addScreen(active_greeting)

response_attacked = ConvoScreen:new {
    id = "response_attacked",
    leftDialog = "@conversation/c_impdefector_teslo:s_57", -- But you did make it, at least.  Did he give you a message for me?
    stopConversation = "false",
    options = {
        {"@conversation/c_impdefector_teslo:s_59", "response_correct_1"}, -- Droids need Star Destroyers in the evening.
        {"@conversation/c_impdefector_teslo:s_63", "response_incorrect_1"}, -- Imperials are dancing on the heads of pins.
    }
}
teslo_tendoora_conv:addScreen(response_attacked)

response_nothing = ConvoScreen:new {
	id = "response_nothing",
	leftDialog = "@conversation/c_impdefector_teslo:s_69", -- What is it?
	stopConversation = "false",
	options = {
		{"@conversation/c_impdefector_teslo:s_59", "response_correct_1"}, -- Droids need Star Destroyers in the evening.
        {"@conversation/c_impdefector_teslo:s_63", "response_incorrect_1"}, -- Imperials are dancing on the heads of pins.
	}
}
teslo_tendoora_conv:addScreen(response_nothing)

response_correct_1 = ConvoScreen:new {
    id = "response_correct_1",
    leftDialog = "@conversation/c_impdefector_teslo:s_61", -- You are kidding?  Really?  This is exciting news, indeed.  Loyalty like yours deserves a reward.  Pardon me now, while I contact my superior.
    stopConversation = "true",
    options = {}
}
teslo_tendoora_conv:addScreen(response_correct_1)

response_correct_2 = ConvoScreen:new {
    id = "response_correct_2",
    leftDialog = "@conversation/c_impdefector_teslo:s_73", -- You are kidding?  Really?  This is exciting news, indeed.  Loyalty like yours deserves a reward.  Pardon me now, while I contact my superior.
    stopConversation = "true",
    options = {}
}
teslo_tendoora_conv:addScreen(response_correct_2)

response_incorrect_1 = ConvoScreen:new {
    id = "response_incorrect_1",
    leftDialog = "@conversation/c_impdefector_teslo:s_65", -- Now you are just making stuff up.
    stopConversation = "false",
    options = {
         {"@conversation/c_impdefector_teslo:s_71", "response_correct_2"}, -- Droids need Star Destroyers in the evening.
         {"@conversation/c_impdefector_teslo:s_75", "response_incorrect_2"}, -- Imperials are dancing on the heads of pins.
	}
}
teslo_tendoora_conv:addScreen(response_incorrect_1)

response_incorrect_2 = ConvoScreen:new {
    id = "response_incorrect_2",
    leftDialog = "@conversation/c_impdefector_teslo:s_77", -- Now you are just making stuff up.
    stopConversation = "true",
    options = {}
}
teslo_tendoora_conv:addScreen(response_incorrect_2)

waiting_delivery = ConvoScreen:new {
	id = "waiting_delivery",
	leftDialog = "@conversation/c_impdefector_teslo:s_79", -- Pardon me, but I'm waiting for a delivery.
	stopConversation = "true",
	options = {}
}
teslo_tendoora_conv:addScreen(waiting_delivery)

addConversationTemplate("teslo_tendoora_conv", teslo_tendoora_conv)
