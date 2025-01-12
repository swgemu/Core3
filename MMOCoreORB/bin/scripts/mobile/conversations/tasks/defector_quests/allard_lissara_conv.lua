allard_lissara_conv = ConvoTemplate:new {
	initialScreen = "",
	templateType = "Lua",
	luaClassHandler = "AllardLissaraConvoHandler",
	screens = {}
}

active_greeting = ConvoScreen:new {
    id = "active_greeting",
    leftDialog = "@conversation/c_rebdefector_allard:s_850", -- I received word that you were on the way.  No problems, I assume?
    stopConversation = "false",
    options = {
        {"@conversation/c_rebdefector_allard:s_852", "response_attacked"}, -- The informant would have slowed me so I came alone and then mercenaries attacked me, sir.
		{"@conversation/c_rebdefector_allard:s_864", "response_nothing"}, -- It was easy, sir.  The informant gave me information and I came to you.
    }
}
allard_lissara_conv:addScreen(active_greeting)

response_attacked = ConvoScreen:new {
    id = "response_attacked",
    leftDialog = "@conversation/c_rebdefector_allard:s_854", -- I knew about the mercenaries.  I suspect they were hired by rebels. The Informant wouldn't follow you here? Did he give you information for me?
    stopConversation = "false",
    options = {
        {"@conversation/c_rebdefector_allard:s_856", "response_correct_1"}, -- Wookiees walk at night in the trees of Naboo.
        {"@conversation/c_rebdefector_allard:s_860", "response_incorrect_1"}, -- The Pekos have landed, sir.
    }
}
allard_lissara_conv:addScreen(response_attacked)

response_nothing = ConvoScreen:new {
	id = "response_nothing",
	leftDialog = "@conversation/c_rebdefector_allard:s_866", -- No need for false modesty.  I heard that mercenary bullyboys tracked you and attacked.  What was the information?
	stopConversation = "false",
	options = {
		{"@conversation/c_rebdefector_allard:s_856", "response_correct_1"}, -- Wookiees walk at night in the trees of Naboo.
        {"@conversation/c_rebdefector_allard:s_860", "response_incorrect_1"}, -- The Pekos have landed, sir.
	}
}
allard_lissara_conv:addScreen(response_nothing)

response_correct_1 = ConvoScreen:new {
    id = "response_correct_1",
    leftDialog = "@conversation/c_rebdefector_allard:s_858", -- Loyalty like yours is quite admirable.  You will go far with us.
    stopConversation = "true",
    options = {}
}
allard_lissara_conv:addScreen(response_correct_1)

response_correct_2 = ConvoScreen:new {
    id = "response_correct_2",
	leftDialog = "@conversation/c_rebdefector_allard:s_870", -- Your skill has gained us information that will break the Rebels!  Loyalty like yours is quite admirable.  You will go far with us.
    stopConversation = "true",
    options = {}
}
allard_lissara_conv:addScreen(response_correct_2)

response_incorrect_1 = ConvoScreen:new {
    id = "response_incorrect_1",
    leftDialog = "@conversation/c_rebdefector_allard:s_862", -- That doesn't sound like a valid codephrase to me, soldier.  Did you take notes?
    stopConversation = "false",
    options = {
         {"@conversation/c_rebdefector_allard:s_868", "response_correct_2"}, -- Wookiees walk at night in the trees of Naboo.
		 {"@conversation/c_rebdefector_allard:s_872", "response_incorrect_2"}, -- Silver corvettes fly into mountains on Ryloth.
	}
}
allard_lissara_conv:addScreen(response_incorrect_1)

response_incorrect_2 = ConvoScreen:new {
    id = "response_incorrect_2",
	leftDialog = "@conversation/c_rebdefector_allard:s_874", -- That doesn't sound like a valid codephrase to me, soldier.  Did you take notes?
    stopConversation = "true",
    options = {}
}
allard_lissara_conv:addScreen(response_incorrect_2)

waiting_delivery = ConvoScreen:new {
	id = "waiting_delivery",
	leftDialog = "@conversation/c_rebdefector_allard:s_876", -- I'm waiting for a delivery.
    stopConversation = "true",
	options = {}
}
allard_lissara_conv:addScreen(waiting_delivery)

addConversationTemplate("allard_lissara_conv", allard_lissara_conv)
