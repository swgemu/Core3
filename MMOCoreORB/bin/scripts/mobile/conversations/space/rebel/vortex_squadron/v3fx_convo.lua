v3fx_convo = ConvoTemplate:new {
	initialScreen = "",
	templateType = "Lua",
	luaClassHandler = "v3fxConvoHandler",
	screens = {}
}

-- Not a Pilot (no JTL skills)
v3fx_convo_no_jtl = ConvoScreen:new {
	id = "no_jtl",
	leftDialog = "@conversation/naboo_rebel_tier3:s_8a226979", -- I cannot help you.
	stopConversation = "true",
	options = {}
}
v3fx_convo:addScreen(v3fx_convo_no_jtl)

-- Imperial/Wrong Faction
v3fx_convo_imperial_pilot = ConvoScreen:new {
	id = "imperial_pilot",
	leftDialog = "@conversation/naboo_rebel_tier3:s_13", -- I cannot help you now.
	stopConversation = "true",
	options = {}
}
v3fx_convo:addScreen(v3fx_convo_imperial_pilot)

-- Neutral Pilot
v3fx_convo_neutral_pilot = ConvoScreen:new {
	id = "neutral_pilot",
	leftDialog = "@conversation/naboo_rebel_tier3:s_13", -- I cannot help you now.
	stopConversation = "true",
	options = {}
}
v3fx_convo:addScreen(v3fx_convo_neutral_pilot)

-- Non-Vortex Rebel Pilot (not on track)
v3fx_convo_non_vortex_pilot = ConvoScreen:new {
	id = "non_vortex_pilot",
	leftDialog = "@conversation/naboo_rebel_tier3:s_3e7fb8a3", -- I appreciate your devotion to the Alliance, but I have nothing for you right now. I suggest you find your commanding officer.
	stopConversation = "true",
	options = {}
}
v3fx_convo:addScreen(v3fx_convo_non_vortex_pilot)

-- Not Tier 2 Complete (not ready for tier 3)
v3fx_convo_not_tier2_complete = ConvoScreen:new {
	id = "not_tier2_complete",
	leftDialog = "@conversation/naboo_rebel_tier3:s_2750c5d9", -- You still have work to do, young one.
	stopConversation = "true",
	options = {}
}
v3fx_convo:addScreen(v3fx_convo_not_tier2_complete)

-- Negative Faction
v3fx_convo_negative_faction = ConvoScreen:new {
	id = "negative_faction",
	leftDialog = "@conversation/naboo_rebel_tier3:s_74967449", -- I thought that we could trust you, %TU... but it seems we were mistaken.
	stopConversation = "false",
	options = {
		{"@conversation/naboo_rebel_tier3:s_ceaea132", "faction_explain"}, -- You can trust me
	}
}
v3fx_convo:addScreen(v3fx_convo_negative_faction)

-- Faction Explain
v3fx_convo_faction_explain = ConvoScreen:new {
	id = "faction_explain",
	leftDialog = "@conversation/naboo_rebel_tier3:s_74967449", -- dynamic
	stopConversation = "true",
	options = {}
}
v3fx_convo:addScreen(v3fx_convo_faction_explain)

-- Has Active Mission
v3fx_convo_has_mission = ConvoScreen:new {
	id = "has_mission",
	leftDialog = "@conversation/naboo_rebel_tier3:s_44fd681b", -- Wouldn't you rather be on your ship? You are still on a mission.
	stopConversation = "true",
	options = {}
}
v3fx_convo:addScreen(v3fx_convo_has_mission)

-- Ready for Tier 4 (completed tier 3)
v3fx_convo_ready_for_tier4 = ConvoScreen:new {
	id = "ready_for_tier4",
	leftDialog = "@conversation/naboo_rebel_tier3:s_cbc2d68c", -- Your work here is done %TU.
	stopConversation = "false",
	options = {
		{"@conversation/naboo_rebel_tier3:s_9ac7f904", "go_to_vrovel"}, -- Am I leaving the Vortex?
		{"@conversation/naboo_rebel_tier3:s_eb3c17f0", "go_to_vrovel"}, -- Was it something I said?
	}
}
v3fx_convo:addScreen(v3fx_convo_ready_for_tier4)

-- Go to Vrovel
v3fx_convo_go_to_vrovel = ConvoScreen:new {
	id = "go_to_vrovel",
	leftDialog = "@conversation/naboo_rebel_tier3:s_cbc2d68c", -- dynamic
	stopConversation = "true",
	options = {}
}
v3fx_convo:addScreen(v3fx_convo_go_to_vrovel)

-- Failed Quest 1
v3fx_convo_failed_quest1 = ConvoScreen:new {
	id = "failed_quest1",
	leftDialog = "@conversation/naboo_rebel_tier3:s_1ba01028", -- Not good enough, %NU. You must start over.
	stopConversation = "true",
	options = {}
}
v3fx_convo:addScreen(v3fx_convo_failed_quest1)

-- Failed Quest 2
v3fx_convo_failed_quest2 = ConvoScreen:new {
	id = "failed_quest2",
	leftDialog = "@conversation/naboo_rebel_tier3:s_4f98b9b7", -- You are not helping the Rebellion.
	stopConversation = "false",
	options = {
		{"@conversation/naboo_rebel_tier3:s_a0e6a107", "retry_quest2"}, -- I can still turn this around.
		{"@conversation/naboo_rebel_tier3:s_30760d01", "retry_quest2"}, -- Give me another shot.
	}
}
v3fx_convo:addScreen(v3fx_convo_failed_quest2)

-- Retry Quest 2
v3fx_convo_retry_quest2 = ConvoScreen:new {
	id = "retry_quest2",
	leftDialog = "@conversation/naboo_rebel_tier3:s_4f98b9b7", -- dynamic
	stopConversation = "true",
	options = {}
}
v3fx_convo:addScreen(v3fx_convo_retry_quest2)

-- Failed Quest 3
v3fx_convo_failed_quest3 = ConvoScreen:new {
	id = "failed_quest3",
	leftDialog = "@conversation/naboo_rebel_tier3:s_840116ce", -- Blast you! You haven't done your job!
	stopConversation = "false",
	options = {
		{"@conversation/naboo_rebel_tier3:s_ded27301", "retry_quest3"}, -- I'm not defeated yet!
		{"@conversation/naboo_rebel_tier3:s_fd2e11b9", "retry_quest3"}, -- I don't see how this helps the Alliance!
	}
}
v3fx_convo:addScreen(v3fx_convo_failed_quest3)

-- Retry Quest 3
v3fx_convo_retry_quest3 = ConvoScreen:new {
	id = "retry_quest3",
	leftDialog = "@conversation/naboo_rebel_tier3:s_840116ce", -- dynamic
	stopConversation = "true",
	options = {}
}
v3fx_convo:addScreen(v3fx_convo_retry_quest3)

-- Failed Quest 4
v3fx_convo_failed_quest4 = ConvoScreen:new {
	id = "failed_quest4",
	leftDialog = "@conversation/naboo_rebel_tier3:s_51fbced7", -- You have failed! Try again, %TU!
	stopConversation = "true",
	options = {}
}
v3fx_convo:addScreen(v3fx_convo_failed_quest4)

-- Quest 1 Complete (collecting reward)
v3fx_convo_excellent_work = ConvoScreen:new {
	id = "excellent_work",
	leftDialog = "@conversation/naboo_rebel_tier3:s_eeb2051f", -- Very nice work, %TU. Are you ready for further training?
	stopConversation = "false",
	options = {
		{"@conversation/naboo_rebel_tier3:s_312", "training_menu"}, -- In what area do I need to be trained?
	}
}
v3fx_convo:addScreen(v3fx_convo_excellent_work)

-- Quest 2 Complete (collecting reward)
v3fx_convo_excellent_work2 = ConvoScreen:new {
	id = "excellent_work2",
	leftDialog = "@conversation/naboo_rebel_tier3:s_6dea91bd", -- That mission was quite dangerous. Perhaps it's time to return to training. I want you to have the skills you need to succeed.
	stopConversation = "false",
	options = {
		{"@conversation/naboo_rebel_tier3:s_312", "training_menu"}, -- In what area do I need to be trained?
	}
}
v3fx_convo:addScreen(v3fx_convo_excellent_work2)

-- Quest 3 Complete (collecting reward)
v3fx_convo_excellent_work3 = ConvoScreen:new {
	id = "excellent_work3",
	leftDialog = "@conversation/naboo_rebel_tier3:s_eeb2051f", -- dynamic
	stopConversation = "false",
	options = {
		{"@conversation/naboo_rebel_tier3:s_312", "training_menu"}, -- In what area do I need to be trained?
	}
}
v3fx_convo:addScreen(v3fx_convo_excellent_work3)

-- Quest 4 Complete (collecting reward)
v3fx_convo_excellent_work4 = ConvoScreen:new {
	id = "excellent_work4",
	leftDialog = "@conversation/naboo_rebel_tier3:s_eeb2051f", -- dynamic
	stopConversation = "false",
	options = {
		{"@conversation/naboo_rebel_tier3:s_312", "training_menu"}, -- In what area do I need to be trained?
	}
}
v3fx_convo:addScreen(v3fx_convo_excellent_work4)

-- Training Menu (dynamic options added by handler)
v3fx_convo_training_menu = ConvoScreen:new {
	id = "training_menu",
	leftDialog = "@conversation/naboo_rebel_tier3:s_eeb2051f", -- dynamic
	stopConversation = "false",
	options = {}
}
v3fx_convo:addScreen(v3fx_convo_training_menu)

-- Goodbye
v3fx_convo_goodbye = ConvoScreen:new {
	id = "goodbye",
	leftDialog = "@conversation/naboo_rebel_tier3:s_8a226979", -- dynamic
	stopConversation = "true",
	options = {}
}
v3fx_convo:addScreen(v3fx_convo_goodbye)

addConversationTemplate("v3fx_convo", v3fx_convo)
