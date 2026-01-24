ulvawop_convo = ConvoTemplate:new {
	initialScreen = "",
	templateType = "Lua",
	luaClassHandler = "ulvawopConvoHandler",
	screens = {}
}

-- Not a Pilot (no JTL skills)
ulvawop_convo_no_jtl = ConvoScreen:new {
	id = "no_jtl",
	leftDialog = "@conversation/tatooine_rebel_tier3:s_d9245236", -- I don't think I know you. I'm certainly not expecting you.
	stopConversation = "true",
	options = {}
}
ulvawop_convo:addScreen(ulvawop_convo_no_jtl)

-- Imperial/Not Rebel Pilot
ulvawop_convo_imperial_pilot = ConvoScreen:new {
	id = "imperial_pilot",
	leftDialog = "@conversation/tatooine_rebel_tier3:s_39d07e54", -- There's nothing for you here.
	stopConversation = "true",
	options = {}
}
ulvawop_convo:addScreen(ulvawop_convo_imperial_pilot)

-- Neutral Pilot
ulvawop_convo_neutral_pilot = ConvoScreen:new {
	id = "neutral_pilot",
	leftDialog = "@conversation/tatooine_rebel_tier3:s_39d07e54", -- There's nothing for you here.
	stopConversation = "true",
	options = {}
}
ulvawop_convo:addScreen(ulvawop_convo_neutral_pilot)

-- Non-Crimson Phoenix Rebel Pilot (not on track)
ulvawop_convo_non_crimson_phoenix_pilot = ConvoScreen:new {
	id = "non_crimson_phoenix_pilot",
	leftDialog = "@conversation/tatooine_rebel_tier3:s_30a2d12d", -- I'm afraid I won't be of much use to you. I suggest you find someone else.
	stopConversation = "true",
	options = {}
}
ulvawop_convo:addScreen(ulvawop_convo_non_crimson_phoenix_pilot)

-- Not Rebel Pilot
ulvawop_convo_not_rebel_pilot = ConvoScreen:new {
	id = "not_rebel_pilot",
	leftDialog = "@conversation/tatooine_rebel_tier3:s_39d07e54", -- There's nothing for you here.
	stopConversation = "true",
	options = {}
}
ulvawop_convo:addScreen(ulvawop_convo_not_rebel_pilot)

-- Not Ready (hasn't completed Tier 2)
ulvawop_convo_not_ready = ConvoScreen:new {
	id = "not_ready",
	leftDialog = "@conversation/tatooine_rebel_tier3:s_614f7f1c", -- You haven't been cleared for this level yet.
	stopConversation = "true",
	options = {}
}
ulvawop_convo:addScreen(ulvawop_convo_not_ready)

-- Has Active Mission
ulvawop_convo_has_mission = ConvoScreen:new {
	id = "has_mission",
	leftDialog = "@conversation/tatooine_rebel_tier3:s_329414b2", -- Please, do not waste your time talking to me. You are needed elsewhere.
	stopConversation = "true",
	options = {}
}
ulvawop_convo:addScreen(ulvawop_convo_has_mission)

-- Negative Faction
ulvawop_convo_negative_faction = ConvoScreen:new {
	id = "negative_faction",
	leftDialog = "@conversation/tatooine_rebel_tier3:s_c3e376a5", -- %TU! Explain yourself! What's this I've heard about you assisting the Empire?
	stopConversation = "false",
	options = {
		{"@conversation/tatooine_rebel_tier3:s_ecb17e60", "faction_explain"}, -- I don't know what you mean
	}
}
ulvawop_convo:addScreen(ulvawop_convo_negative_faction)

-- Faction Explain
ulvawop_convo_faction_explain = ConvoScreen:new {
	id = "faction_explain",
	leftDialog = "@conversation/tatooine_rebel_tier3:s_c3e376a5", -- dynamic
	stopConversation = "true",
	options = {}
}
ulvawop_convo:addScreen(ulvawop_convo_faction_explain)

-- Grant Quest 1 (introduction)
ulvawop_convo_introduction = ConvoScreen:new {
	id = "introduction",
	leftDialog = "@conversation/tatooine_rebel_tier3:s_6f921f12", -- Welcome, %TU. You look different than I expected from your picture.
	stopConversation = "false",
	options = {
		{"@conversation/tatooine_rebel_tier3:s_783af10a", "quest1_brief"}, -- What picture?
		{"@conversation/tatooine_rebel_tier3:s_5b000af8", "quest1_brief"}, -- Different how?
	}
}
ulvawop_convo:addScreen(ulvawop_convo_introduction)

-- Quest 1 Brief
ulvawop_convo_quest1_brief = ConvoScreen:new {
	id = "quest1_brief",
	leftDialog = "@conversation/tatooine_rebel_tier3:s_6f921f12", -- dynamic - quest granted
	stopConversation = "true",
	options = {}
}
ulvawop_convo:addScreen(ulvawop_convo_quest1_brief)

-- Start Mission 1
ulvawop_convo_start_mission1 = ConvoScreen:new {
	id = "start_mission1",
	leftDialog = "@conversation/tatooine_rebel_tier3:s_6f921f12", -- Welcome, %TU. You look different than I expected from your picture.
	stopConversation = "false",
	options = {
		{"@conversation/tatooine_rebel_tier3:s_783af10a", "accept_mission1"}, -- What picture?
		{"@conversation/tatooine_rebel_tier3:s_5b000af8", "accept_mission1"}, -- Different how?
	}
}
ulvawop_convo:addScreen(ulvawop_convo_start_mission1)

-- Accept Mission 1
ulvawop_convo_accept_mission1 = ConvoScreen:new {
	id = "accept_mission1",
	leftDialog = "@conversation/tatooine_rebel_tier3:s_6f921f12", -- dynamic - quest granted
	stopConversation = "true",
	options = {}
}
ulvawop_convo:addScreen(ulvawop_convo_accept_mission1)

-- Failed Quest 1
ulvawop_convo_failed_quest1 = ConvoScreen:new {
	id = "failed_quest1",
	leftDialog = "@conversation/tatooine_rebel_tier3:s_5a66cd79", -- You haven't finished your assignment. Please get back to work.
	stopConversation = "false",
	options = {
		{"@conversation/tatooine_rebel_tier3:s_a68dfaa6", "retry_quest1"}, -- Sure I have!
		{"@conversation/tatooine_rebel_tier3:s_9401fd7b", "retry_quest1"}, -- It's very difficult.
	}
}
ulvawop_convo:addScreen(ulvawop_convo_failed_quest1)

-- Retry Quest 1
ulvawop_convo_retry_quest1 = ConvoScreen:new {
	id = "retry_quest1",
	leftDialog = "@conversation/tatooine_rebel_tier3:s_6f921f12", -- dynamic
	stopConversation = "true",
	options = {}
}
ulvawop_convo:addScreen(ulvawop_convo_retry_quest1)

-- Excellent Work (Quest 1 Complete) - Grants skill
ulvawop_convo_excellent_work = ConvoScreen:new {
	id = "excellent_work",
	leftDialog = "@conversation/tatooine_rebel_tier3:s_8bd6bf55", -- Well done. I look forward to meeting that Imperial officer. Let me teach you a skill.
	stopConversation = "false",
	options = {
		{"@conversation/tatooine_rebel_tier3:s_661", "training_menu"}, -- What are you going to teach me?
	}
}
ulvawop_convo:addScreen(ulvawop_convo_excellent_work)

-- Grant Quest 2
ulvawop_convo_grant_quest2 = ConvoScreen:new {
	id = "grant_quest2",
	leftDialog = "@conversation/tatooine_rebel_tier3:s_1061c440", -- Your reputation is well deserved.
	stopConversation = "false",
	options = {
		{"@conversation/tatooine_rebel_tier3:s_c4dbdf08", "quest2_brief"}, -- So now I have a dossier AND a reputation.
		{"@conversation/tatooine_rebel_tier3:s_de2df0e3", "quest2_brief"}, -- Thanks - I think.
	}
}
ulvawop_convo:addScreen(ulvawop_convo_grant_quest2)

-- Quest 2 Brief
ulvawop_convo_quest2_brief = ConvoScreen:new {
	id = "quest2_brief",
	leftDialog = "@conversation/tatooine_rebel_tier3:s_1061c440", -- dynamic - quest granted
	stopConversation = "true",
	options = {}
}
ulvawop_convo:addScreen(ulvawop_convo_quest2_brief)

-- Failed Quest 2
ulvawop_convo_failed_quest2 = ConvoScreen:new {
	id = "failed_quest2",
	leftDialog = "@conversation/tatooine_rebel_tier3:s_67c8f113", -- You still have work to do.
	stopConversation = "false",
	options = {
		{"@conversation/tatooine_rebel_tier3:s_d85b3a9c", "retry_quest2"}, -- What if I refuse to continue?
		{"@conversation/tatooine_rebel_tier3:s_87d7e908", "retry_quest2"}, -- I know.
	}
}
ulvawop_convo:addScreen(ulvawop_convo_failed_quest2)

-- Retry Quest 2
ulvawop_convo_retry_quest2 = ConvoScreen:new {
	id = "retry_quest2",
	leftDialog = "@conversation/tatooine_rebel_tier3:s_1061c440", -- dynamic
	stopConversation = "true",
	options = {}
}
ulvawop_convo:addScreen(ulvawop_convo_retry_quest2)

-- Excellent Work 2 (Quest 2 Complete) - Grants skill
ulvawop_convo_excellent_work2 = ConvoScreen:new {
	id = "excellent_work2",
	leftDialog = "@conversation/tatooine_rebel_tier3:s_fa6e2383", -- Looks like our information was correct. Thank you for your efforts. Are you ready for a new skill?
	stopConversation = "false",
	options = {
		{"@conversation/tatooine_rebel_tier3:s_661", "training_menu"}, -- What are you going to teach me?
	}
}
ulvawop_convo:addScreen(ulvawop_convo_excellent_work2)

-- Grant Quest 3
ulvawop_convo_grant_quest3 = ConvoScreen:new {
	id = "grant_quest3",
	leftDialog = "@conversation/tatooine_rebel_tier3:s_5852ee6b", -- The intel was correct.
	stopConversation = "false",
	options = {
		{"@conversation/tatooine_rebel_tier3:s_ed4e5e50", "quest3_brief"}, -- Sure was. Do you have my next mission?
		{"@conversation/tatooine_rebel_tier3:s_ab1cce5f", "quest3_brief"}, -- That thermal bomb would have ripped this place apart.
	}
}
ulvawop_convo:addScreen(ulvawop_convo_grant_quest3)

-- Quest 3 Brief
ulvawop_convo_quest3_brief = ConvoScreen:new {
	id = "quest3_brief",
	leftDialog = "@conversation/tatooine_rebel_tier3:s_5852ee6b", -- dynamic - quest granted
	stopConversation = "true",
	options = {}
}
ulvawop_convo:addScreen(ulvawop_convo_quest3_brief)

-- Failed Quest 3
ulvawop_convo_failed_quest3 = ConvoScreen:new {
	id = "failed_quest3",
	leftDialog = "@conversation/tatooine_rebel_tier3:s_c74a6348", -- You must finish what you started.
	stopConversation = "false",
	options = {
		{"@conversation/tatooine_rebel_tier3:s_d454739a", "retry_quest3"}, -- Soon.
		{"@conversation/tatooine_rebel_tier3:s_9173548c", "retry_quest3"}, -- Right away.
	}
}
ulvawop_convo:addScreen(ulvawop_convo_failed_quest3)

-- Retry Quest 3
ulvawop_convo_retry_quest3 = ConvoScreen:new {
	id = "retry_quest3",
	leftDialog = "@conversation/tatooine_rebel_tier3:s_5852ee6b", -- dynamic
	stopConversation = "true",
	options = {}
}
ulvawop_convo:addScreen(ulvawop_convo_retry_quest3)

-- Excellent Work 3 (Quest 3 Complete) - Grants skill
ulvawop_convo_excellent_work3 = ConvoScreen:new {
	id = "excellent_work3",
	leftDialog = "@conversation/tatooine_rebel_tier3:s_f72b6d44", -- Would you like to learn a new skill now?
	stopConversation = "false",
	options = {
		{"@conversation/tatooine_rebel_tier3:s_661", "training_menu"}, -- What are you going to teach me?
	}
}
ulvawop_convo:addScreen(ulvawop_convo_excellent_work3)

-- Grant Quest 4
ulvawop_convo_grant_quest4 = ConvoScreen:new {
	id = "grant_quest4",
	leftDialog = "@conversation/tatooine_rebel_tier3:s_5bd53e0a", -- We meet again.
	stopConversation = "false",
	options = {
		{"@conversation/tatooine_rebel_tier3:s_a91e3c6b", "quest4_brief"}, -- You sent for me?
		{"@conversation/tatooine_rebel_tier3:s_639", "quest4_brief"}, -- Do you have a mission for me?
	}
}
ulvawop_convo:addScreen(ulvawop_convo_grant_quest4)

-- Quest 4 Brief
ulvawop_convo_quest4_brief = ConvoScreen:new {
	id = "quest4_brief",
	leftDialog = "@conversation/tatooine_rebel_tier3:s_5bd53e0a", -- dynamic - quest granted
	stopConversation = "true",
	options = {}
}
ulvawop_convo:addScreen(ulvawop_convo_quest4_brief)

-- Failed Quest 4
ulvawop_convo_failed_quest4 = ConvoScreen:new {
	id = "failed_quest4",
	leftDialog = "@conversation/tatooine_rebel_tier3:s_4748286f", -- That pilot's not going to get the better of you, I hope.
	stopConversation = "false",
	options = {
		{"@conversation/tatooine_rebel_tier3:s_b40f340", "retry_quest4"}, -- Not a chance.
		{"@conversation/tatooine_rebel_tier3:s_9fb0046e", "retry_quest4"}, -- He's good.
	}
}
ulvawop_convo:addScreen(ulvawop_convo_failed_quest4)

-- Retry Quest 4
ulvawop_convo_retry_quest4 = ConvoScreen:new {
	id = "retry_quest4",
	leftDialog = "@conversation/tatooine_rebel_tier3:s_5bd53e0a", -- dynamic
	stopConversation = "true",
	options = {}
}
ulvawop_convo:addScreen(ulvawop_convo_retry_quest4)

-- All Missions Complete - Grants final skill
ulvawop_convo_all_missions_complete = ConvoScreen:new {
	id = "all_missions_complete",
	leftDialog = "@conversation/tatooine_rebel_tier3:s_f9044504", -- There's more I could teach you.
	stopConversation = "false",
	options = {
		{"@conversation/tatooine_rebel_tier3:s_661", "training_menu"}, -- What are you going to teach me?
	}
}
ulvawop_convo:addScreen(ulvawop_convo_all_missions_complete)

-- Training Menu (dynamic options added by handler)
ulvawop_convo_training_menu = ConvoScreen:new {
	id = "training_menu",
	leftDialog = "@conversation/tatooine_rebel_tier3:s_f9044504", -- There's more I could teach you.
	stopConversation = "false",
	options = {}
}
ulvawop_convo:addScreen(ulvawop_convo_training_menu)

-- Completed Ulvawop (send to next trainer - ready for tier 4)
ulvawop_convo_completed_ulvawop = ConvoScreen:new {
	id = "completed_ulvawop",
	leftDialog = "@conversation/tatooine_rebel_tier3:s_fb871ded", -- Central Command has issued new orders for you.
	stopConversation = "false",
	options = {
		{"@conversation/tatooine_rebel_tier3:s_a927c891", "go_to_ufwol"}, -- What's next?
		{"@conversation/tatooine_rebel_tier3:s_554b78dd", "go_to_ufwol"}, -- That's a shame. I'm starting to enjoy the idea of being a spy.
	}
}
ulvawop_convo:addScreen(ulvawop_convo_completed_ulvawop)

-- Go to Ufwol
ulvawop_convo_go_to_ufwol = ConvoScreen:new {
	id = "go_to_ufwol",
	leftDialog = "@conversation/tatooine_rebel_tier3:s_fb871ded", -- dynamic
	stopConversation = "true",
	options = {}
}
ulvawop_convo:addScreen(ulvawop_convo_go_to_ufwol)

-- Goodbye
ulvawop_convo_goodbye = ConvoScreen:new {
	id = "goodbye",
	leftDialog = "@conversation/tatooine_rebel_tier3:s_329414b2", -- Please, do not waste your time talking to me. You are needed elsewhere.
	stopConversation = "true",
	options = {}
}
ulvawop_convo:addScreen(ulvawop_convo_goodbye)

addConversationTemplate("ulvawop_convo", ulvawop_convo)
