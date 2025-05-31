tutorial_imperial_broker_convo_template = ConvoTemplate:new {
	initialScreen = "greet",
	templateType = "Lua",
	luaClassHandler = "tutorialImperialBrokerConvoHandler",
	screens = {}
}

--[[
	Greeting
]]

greet = ConvoScreen:new {
	id = "greet",
	leftDialog = "@conversation/tutorial_imperial_broker:s_f4f79047", -- Greetings, citizen! Would you like to learn about exciting opportunities for pilots in the Imperial Navy?
	stopConversation = "false",
	animation = {"salute2"},
	options = {
		{"@conversation/tutorial_imperial_broker:s_4b0c16d2", "recruiting"}, -- Are you recruiting Imperial Pilots?
		{"@conversation/tutorial_imperial_broker:s_445a2be4", "no_never_mind"}, -- No. Never mind.
	}
}
tutorial_imperial_broker_convo_template:addScreen(greet);

recruiting = ConvoScreen:new {
	id = "recruiting",
	leftDialog = "@conversation/tutorial_imperial_broker:s_b26292fd", -- The Emperor is building a vast and powerful navy...
	stopConversation = "false",
	animation = {"explain"},
	options = {
		{"@conversation/tutorial_imperial_broker:s_ee369d68", "black_epsilon"}, -- What can you tell me about Black Epsilon?
		{"@conversation/tutorial_imperial_broker:s_5612445a", "storm_squadron"}, -- Tell me about Storm Squadron.
		{"@conversation/tutorial_imperial_broker:s_3930f2e7", "imperial_inquisition"}, -- Yes. The Imperial Inquisition. Enlighten me, pilot.
	}
}
tutorial_imperial_broker_convo_template:addScreen(recruiting);

--[[
	Black Epsilon - Corellia
]]

black_epsilon = ConvoScreen:new {
	id = "black_epsilon",
	leftDialog = "@conversation/tutorial_imperial_broker:s_86cb9899", -- Black Epsilon is stationed at the Imperial Base on Talus...
	stopConversation = "false",
	animation = {"nod_head_once"},
	options = {
		{"@conversation/tutorial_imperial_broker:s_70f18874", "not_interested_be"}, -- I'm not interested in that.
		{"@conversation/tutorial_imperial_broker:s_df2917b1", "more_black_epsilon"}, -- Tell me more
	}
}
tutorial_imperial_broker_convo_template:addScreen(black_epsilon);

more_black_epsilon = ConvoScreen:new {
	id = "more_black_epsilon",
	leftDialog = "@conversation/tutorial_imperial_broker:s_c8bbb089", -- I will add the location of their recruiting officer to your datapad...
	stopConversation = "false",
	animation = {"wave_finger_warning"},
	options = {
		{"@conversation/tutorial_imperial_broker:s_987445c9", "goodbye_salute"}, -- Thank you.
	}
}
tutorial_imperial_broker_convo_template:addScreen(more_black_epsilon);

not_interested_be = ConvoScreen:new {
	id = "not_interested_be",
	leftDialog = "@conversation/tutorial_imperial_broker:s_9f862c74", -- What about Storm Squadron or the Imperial Inquisition?
	stopConversation = "false",
	animation = {"shrug_hands"},
	options = {
		{"@conversation/tutorial_imperial_broker:s_5612445a", "storm_squadron"}, -- Tell me about Storm Squadron.
		{"@conversation/tutorial_imperial_broker:s_3930f2e7", "imperial_inquisition"}, -- Yes. The Imperial Inquisition. Enlighten me, pilot.
	}
}
tutorial_imperial_broker_convo_template:addScreen(not_interested_be);

--[[
	Storm Squadron - Tatooine
]]

storm_squadron = ConvoScreen:new {
	id = "storm_squadron",
	leftDialog = "@conversation/tutorial_imperial_broker:s_e0db13e8", -- Storm Squadron is one of the Empire's finest military units...
	stopConversation = "false",
	animation = {"pose_proudly"},
	options = {
		{"@conversation/tutorial_imperial_broker:s_70f18874", "not_interested_storm"}, -- I'm not interested in that.
		{"@conversation/tutorial_imperial_broker:s_df2917b1", "more_storm"}, -- Tell me more
	}
}
tutorial_imperial_broker_convo_template:addScreen(storm_squadron);

more_storm = ConvoScreen:new {
	id = "more_storm",
	leftDialog = "@conversation/tutorial_imperial_broker:s_d0f9b54", -- I will add the location of the Storm Squadron pilot trainer to your datapad...
	stopConversation = "false",
	animation = {"manipulate_medium"},
	options = {
		{"@conversation/tutorial_imperial_broker:s_987445c9", "goodbye_salute"}, -- Thank you.
	}
}
tutorial_imperial_broker_convo_template:addScreen(more_storm);

not_interested_storm = ConvoScreen:new {
	id = "not_interested_storm",
	leftDialog = "@conversation/tutorial_imperial_broker:s_727cf8b6", -- What about Black Epsilon or the Imperial Inquisition?
	stopConversation = "false",
	animation = {"shrug_hands"},
	options = {
		{"@conversation/tutorial_imperial_broker:s_1b2086de", "black_epsilon"}, -- Black Epsilon?
		{"@conversation/tutorial_imperial_broker:s_23ef3e33", "imperial_inquisition"}, -- Imperial Inquisition?
	}
}
tutorial_imperial_broker_convo_template:addScreen(not_interested_storm);

--[[
	Imperial Inquisition - Naboo
]]

imperial_inquisition = ConvoScreen:new {
	id = "imperial_inquisition",
	leftDialog = "@conversation/tutorial_imperial_broker:s_3c9c6441", -- Imperial Inquisition is a special unit located in the Naboo system...
	stopConversation = "false",
	animation = {"explain"},
	options = {
		{"@conversation/tutorial_imperial_broker:s_70f18874", "not_interested_inquisition"}, -- I'm not interested in that.
		{"@conversation/tutorial_imperial_broker:s_98a4e725", "more_inquisition"}, -- Tell me what you can
	}
}
tutorial_imperial_broker_convo_template:addScreen(imperial_inquisition);

more_inquisition = ConvoScreen:new {
	id = "more_inquisition",
	leftDialog = "@conversation/tutorial_imperial_broker:s_4874a395", -- I will add the location to your datapad...
	stopConversation = "false",
	animation = {"whisper"},
	options = {
		{"@conversation/tutorial_imperial_broker:s_987445c9", "goodbye_salute"}, -- Thank you.
	}
}
tutorial_imperial_broker_convo_template:addScreen(more_inquisition);

not_interested_inquisition = ConvoScreen:new {
	id = "not_interested_inquisition",
	leftDialog = "@conversation/tutorial_imperial_broker:s_42693321", -- What about Black Epsilon or the Imperial Inquisition?
	stopConversation = "false",
	animation = {"shrug_hands"},
	options = {
		{"@conversation/tutorial_imperial_broker:s_ee369d68", "black_epsilon"}, -- Black Epsilon?
		{"@conversation/tutorial_imperial_broker:s_5612445a", "storm_squadron"}, -- Tell me about Storm Squadron.
	}
}
tutorial_imperial_broker_convo_template:addScreen(not_interested_inquisition);

--[[
	Conversation Ending Responses
]]

no_never_mind = ConvoScreen:new {
	id = "no_never_mind",
	leftDialog = "@conversation/tutorial_imperial_broker:s_895d093", -- Ok.
	stopConversation = "true",
	animation = {"salute2"},
	options = {}
}
tutorial_imperial_broker_convo_template:addScreen(no_never_mind);

goodbye_salute = ConvoScreen:new {
	id = "goodbye_salute",
	leftDialog = "@conversation/tutorial_imperial_broker:s_f4792d0c", -- Good hunting!
	stopConversation = "true",
	animation = {"salute2"},
	playerAnimation = {"salute2"},
	options = {}
}
tutorial_imperial_broker_convo_template:addScreen(goodbye_salute);

addConversationTemplate("tutorial_imperial_broker_convo_template", tutorial_imperial_broker_convo_template);
