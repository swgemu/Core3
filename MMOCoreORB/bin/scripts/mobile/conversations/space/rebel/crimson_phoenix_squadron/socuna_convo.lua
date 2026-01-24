socuna_convo = ConvoTemplate:new {
	initialScreen = "",
	templateType = "Lua",
	luaClassHandler = "socunaConvoHandler",
	screens = {}
}

-- Imperial Pilot
socuna_convo_imperial_pilot = ConvoScreen:new {
	id = "imperial_pilot",
	leftDialog = "@conversation/tatooine_rebel_trainer_2:s_32c77056", -- I have nothing to say to you.
	stopConversation = "true",
	options = {}
}
socuna_convo:addScreen(socuna_convo_imperial_pilot)

-- Privateer/Pirate Pilot
socuna_convo_neutral_pilot = ConvoScreen:new {
	id = "neutral_pilot",
	leftDialog = "@conversation/tatooine_rebel_trainer_2:s_4243cd30", -- Get out of here, pirate!
	stopConversation = "true",
	options = {}
}
socuna_convo:addScreen(socuna_convo_neutral_pilot)

-- Not Ready (hasn't completed Tier 1)
socuna_convo_not_ready = ConvoScreen:new {
	id = "not_ready",
	leftDialog = "@conversation/tatooine_rebel_trainer_2:s_1d2c155d", -- Hold on, pal. I don't think you're ready to work for me, yet.
	stopConversation = "false",
	options = {
		{"@conversation/tatooine_rebel_trainer_2:s_1f680e83", "not_ready_explain"}, -- You sure?
		{"@conversation/tatooine_rebel_trainer_2:s_57c8489e", "not_ready_explain"}, -- What should I do?
		{"@conversation/tatooine_rebel_trainer_2:s_ca776e30", "not_ready_explain"}, -- Who are you?
	}
}
socuna_convo:addScreen(socuna_convo_not_ready)

-- Not Ready Explain
socuna_convo_not_ready_explain = ConvoScreen:new {
	id = "not_ready_explain",
	leftDialog = "@conversation/tatooine_rebel_trainer_2:s_1d2c155d", -- dynamic
	stopConversation = "true",
	options = {}
}
socuna_convo:addScreen(socuna_convo_not_ready_explain)

-- Has Active Mission (quest 1 in progress)
socuna_convo_has_mission = ConvoScreen:new {
	id = "has_mission",
	leftDialog = "@conversation/tatooine_rebel_trainer_2:s_ef7c4c8", -- Do you have a progress report for me, pilot?
	stopConversation = "false",
	options = {
		{"@conversation/tatooine_rebel_trainer_2:s_9ac87532", "goodbye"}, -- The mission is still in-progress.
		{"@conversation/tatooine_rebel_trainer_2:s_fc01f22f", "excellent_work"}, -- Those Black Sun fighters are history.
		{"@conversation/tatooine_rebel_trainer_2:s_32583e8e", "goodbye"}, -- No, I haven't even left yet.
	}
}
socuna_convo:addScreen(socuna_convo_has_mission)

-- Has Quest 2 In Progress
socuna_convo_has_mission2 = ConvoScreen:new {
	id = "has_mission2",
	leftDialog = "@conversation/tatooine_rebel_trainer_2:s_340e3cc", -- How did the sensor sweep go?
	stopConversation = "false",
	options = {
		{"@conversation/tatooine_rebel_trainer_2:s_9ac87532", "goodbye"}, -- The mission is still in-progress.
		{"@conversation/tatooine_rebel_trainer_2:s_c49dadaf", "excellent_work2"}, -- Sweep is done, and our ship is safe.
	}
}
socuna_convo:addScreen(socuna_convo_has_mission2)

-- Introduction (finished tier 1)
socuna_convo_introduction = ConvoScreen:new {
	id = "introduction",
	leftDialog = "@conversation/tatooine_rebel_trainer_2:s_3e8d2533", -- Are you ready for a very dangerous mission?
	stopConversation = "false",
	options = {
		{"@conversation/tatooine_rebel_trainer_2:s_65c6992e", "quest1_brief"}, -- Yes, I am ready.
		{"@conversation/tatooine_rebel_trainer_2:s_9633bc98", "quest1_brief"}, -- How dangerous?
		{"@conversation/tatooine_rebel_trainer_2:s_3a8e238f", "quest1_brief"}, -- What does it pay?
	}
}
socuna_convo:addScreen(socuna_convo_introduction)

-- Quest 1 Brief
socuna_convo_quest1_brief = ConvoScreen:new {
	id = "quest1_brief",
	leftDialog = "@conversation/tatooine_rebel_trainer_2:s_3e8d2533", -- dynamic - quest granted
	stopConversation = "true",
	options = {}
}
socuna_convo:addScreen(socuna_convo_quest1_brief)

-- Failed Quest 1
socuna_convo_failed_quest1 = ConvoScreen:new {
	id = "failed_quest1",
	leftDialog = "@conversation/tatooine_rebel_trainer_2:s_8af71059", -- So. I hear it was pretty rough out there. Would you like to try helping us again?
	stopConversation = "false",
	options = {
		{"@conversation/tatooine_rebel_trainer_2:s_65c6992e", "retry_quest1"}, -- Yes, I am ready.
	}
}
socuna_convo:addScreen(socuna_convo_failed_quest1)

-- Aborted Quest 1
socuna_convo_aborted_quest1 = ConvoScreen:new {
	id = "aborted_quest1",
	leftDialog = "@conversation/tatooine_rebel_trainer_2:s_f3a2a7d2", -- I can't believe you aborted the first mission I gave you! I hope you're here to try again, soldier!
	stopConversation = "false",
	options = {
		{"@conversation/tatooine_rebel_trainer_2:s_65c6992e", "retry_quest1"}, -- Yes, I am ready.
	}
}
socuna_convo:addScreen(socuna_convo_aborted_quest1)

-- Retry Quest 1
socuna_convo_retry_quest1 = ConvoScreen:new {
	id = "retry_quest1",
	leftDialog = "@conversation/tatooine_rebel_trainer_2:s_3e8d2533", -- dynamic
	stopConversation = "true",
	options = {}
}
socuna_convo:addScreen(socuna_convo_retry_quest1)

-- Excellent Work (Quest 1 Complete)
socuna_convo_excellent_work = ConvoScreen:new {
	id = "excellent_work",
	leftDialog = "@conversation/tatooine_rebel_trainer_2:s_113f133e", -- Are you ready for your next assignment?
	stopConversation = "false",
	options = {
		{"@conversation/tatooine_rebel_trainer_2:s_6c251948", "quest2_brief"}, -- You got it.
	}
}
socuna_convo:addScreen(socuna_convo_excellent_work)

-- Quest 2 Brief
socuna_convo_quest2_brief = ConvoScreen:new {
	id = "quest2_brief",
	leftDialog = "@conversation/tatooine_rebel_trainer_2:s_113f133e", -- dynamic - quest granted
	stopConversation = "true",
	options = {}
}
socuna_convo:addScreen(socuna_convo_quest2_brief)

-- Excellent Work 2 (Quest 2 Complete)
socuna_convo_excellent_work2 = ConvoScreen:new {
	id = "excellent_work2",
	leftDialog = "@conversation/tatooine_rebel_trainer_2:s_340e3cc", -- dynamic
	stopConversation = "false",
	options = {}
}
socuna_convo:addScreen(socuna_convo_excellent_work2)

-- Training Menu (dynamic options added by handler)
socuna_convo_training_menu = ConvoScreen:new {
	id = "training_menu",
	leftDialog = "@conversation/tatooine_rebel_trainer_2:s_269", -- In what do I need to be trained?
	stopConversation = "false",
	options = {}
}
socuna_convo:addScreen(socuna_convo_training_menu)

-- Goodbye
socuna_convo_goodbye = ConvoScreen:new {
	id = "goodbye",
	leftDialog = "@conversation/tatooine_rebel_trainer_2:s_9ac87532", -- The mission is still in-progress.
	stopConversation = "true",
	options = {}
}
socuna_convo:addScreen(socuna_convo_goodbye)

addConversationTemplate("socuna_convo", socuna_convo)
