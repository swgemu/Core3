arkon_convo = ConvoTemplate:new {
	initialScreen = "",
	templateType = "Lua",
	luaClassHandler = "arkonConvoHandler",
	screens = {}
}

-- Not a Pilot (no JTL skills)
arkon_convo_no_jtl = ConvoScreen:new {
	id = "no_jtl",
	leftDialog = "@conversation/corellia_rebel_tier3:s_195b98b2", -- I only speak to pilots. Move along now.
	stopConversation = "true",
	options = {}
}
arkon_convo:addScreen(arkon_convo_no_jtl)

-- Imperial/Not Rebel Pilot
arkon_convo_imperial_pilot = ConvoScreen:new {
	id = "imperial_pilot",
	leftDialog = "@conversation/corellia_rebel_tier3:s_346f07d4", -- Move on.
	stopConversation = "true",
	options = {}
}
arkon_convo:addScreen(arkon_convo_imperial_pilot)

-- Neutral Pilot
arkon_convo_neutral_pilot = ConvoScreen:new {
	id = "neutral_pilot",
	leftDialog = "@conversation/corellia_rebel_tier3:s_346f07d4", -- Move on.
	stopConversation = "true",
	options = {}
}
arkon_convo:addScreen(arkon_convo_neutral_pilot)

-- Non-Havoc Rebel Pilot (not on track)
arkon_convo_non_havoc_pilot = ConvoScreen:new {
	id = "non_havoc_pilot",
	leftDialog = "@conversation/corellia_rebel_tier3:s_853538e8", -- I'm not taking transfers. Return to your unit, pilot.
	stopConversation = "true",
	options = {}
}
arkon_convo:addScreen(arkon_convo_non_havoc_pilot)

-- Not Rebel Pilot
arkon_convo_not_rebel_pilot = ConvoScreen:new {
	id = "not_rebel_pilot",
	leftDialog = "@conversation/corellia_rebel_tier3:s_346f07d4", -- Move on.
	stopConversation = "true",
	options = {}
}
arkon_convo:addScreen(arkon_convo_not_rebel_pilot)

-- Not Ready (hasn't completed Tier 2)
arkon_convo_not_ready = ConvoScreen:new {
	id = "not_ready",
	leftDialog = "@conversation/corellia_rebel_tier3:s_b9ba3998", -- Lady Viopa is waiting for you.
	stopConversation = "true",
	options = {}
}
arkon_convo:addScreen(arkon_convo_not_ready)

-- Has Active Mission
arkon_convo_has_mission = ConvoScreen:new {
	id = "has_mission",
	leftDialog = "@conversation/corellia_rebel_tier3:s_a54fd6b7", -- Do not speak to me until you have completed your mission.
	stopConversation = "true",
	options = {}
}
arkon_convo:addScreen(arkon_convo_has_mission)

-- Negative Faction
arkon_convo_negative_faction = ConvoScreen:new {
	id = "negative_faction",
	leftDialog = "@conversation/corellia_rebel_tier3:s_a08c36ef", -- As if the Empire weren't causing us enough grief... now there are reports that YOU are working against the Rebel Alliance, too!
	stopConversation = "false",
	options = {
		{"@conversation/corellia_rebel_tier3:s_77e48d5b", "faction_explain"}, -- What do you mean?
	}
}
arkon_convo:addScreen(arkon_convo_negative_faction)

-- Faction Explain
arkon_convo_faction_explain = ConvoScreen:new {
	id = "faction_explain",
	leftDialog = "@conversation/corellia_rebel_tier3:s_a08c36ef", -- dynamic
	stopConversation = "true",
	options = {}
}
arkon_convo:addScreen(arkon_convo_faction_explain)

-- Grant Quest 1 (introduction)
arkon_convo_introduction = ConvoScreen:new {
	id = "introduction",
	leftDialog = "@conversation/corellia_rebel_tier3:s_c5648040", -- How did you like Lady Viopa?
	stopConversation = "false",
	options = {
		{"@conversation/corellia_rebel_tier3:s_fb0a082d", "quest1_brief"}, -- A lovely lady.
		{"@conversation/corellia_rebel_tier3:s_f8e71988", "quest1_brief"}, -- I'm ready for my mission.
	}
}
arkon_convo:addScreen(arkon_convo_introduction)

-- Quest 1 Brief
arkon_convo_quest1_brief = ConvoScreen:new {
	id = "quest1_brief",
	leftDialog = "@conversation/corellia_rebel_tier3:s_c5648040", -- dynamic - quest granted
	stopConversation = "true",
	options = {}
}
arkon_convo:addScreen(arkon_convo_quest1_brief)

-- Start Mission 1
arkon_convo_start_mission1 = ConvoScreen:new {
	id = "start_mission1",
	leftDialog = "@conversation/corellia_rebel_tier3:s_c5648040", -- How did you like Lady Viopa?
	stopConversation = "false",
	options = {
		{"@conversation/corellia_rebel_tier3:s_fb0a082d", "accept_mission1"}, -- A lovely lady.
		{"@conversation/corellia_rebel_tier3:s_f8e71988", "accept_mission1"}, -- I'm ready for my mission.
	}
}
arkon_convo:addScreen(arkon_convo_start_mission1)

-- Accept Mission 1
arkon_convo_accept_mission1 = ConvoScreen:new {
	id = "accept_mission1",
	leftDialog = "@conversation/corellia_rebel_tier3:s_c5648040", -- dynamic - quest granted
	stopConversation = "true",
	options = {}
}
arkon_convo:addScreen(arkon_convo_accept_mission1)

-- Failed Quest 1
arkon_convo_failed_quest1 = ConvoScreen:new {
	id = "failed_quest1",
	leftDialog = "@conversation/corellia_rebel_tier3:s_2ccbae6", -- Idiot!
	stopConversation = "false",
	options = {
		{"@conversation/corellia_rebel_tier3:s_d9f9ff9a", "retry_quest1"}, -- I can do it. There's still time.
		{"@conversation/corellia_rebel_tier3:s_8a0c5437", "retry_quest1"}, -- Hey! They're good!
	}
}
arkon_convo:addScreen(arkon_convo_failed_quest1)

-- Retry Quest 1
arkon_convo_retry_quest1 = ConvoScreen:new {
	id = "retry_quest1",
	leftDialog = "@conversation/corellia_rebel_tier3:s_c5648040", -- dynamic
	stopConversation = "true",
	options = {}
}
arkon_convo:addScreen(arkon_convo_retry_quest1)

-- Excellent Work (Quest 1 Complete) - Grants skill
arkon_convo_excellent_work = ConvoScreen:new {
	id = "excellent_work",
	leftDialog = "@conversation/corellia_rebel_tier3:s_620547d7", -- Soldiers in my unit must be well-trained in all areas. Where are you lacking?
	stopConversation = "false",
	options = {
		{"@conversation/corellia_rebel_tier3:s_269", "training_menu"}, -- In what do I need to be trained?
	}
}
arkon_convo:addScreen(arkon_convo_excellent_work)

-- Grant Quest 2
arkon_convo_grant_quest2 = ConvoScreen:new {
	id = "grant_quest2",
	leftDialog = "@conversation/corellia_rebel_tier3:s_c75a413", -- Good. You're here.
	stopConversation = "false",
	options = {
		{"@conversation/corellia_rebel_tier3:s_5688bc93", "quest2_brief"}, -- Those Rebel ships are safe now.
		{"@conversation/corellia_rebel_tier3:s_167", "quest2_brief"}, -- I'm ready for my mission.
	}
}
arkon_convo:addScreen(arkon_convo_grant_quest2)

-- Quest 2 Brief
arkon_convo_quest2_brief = ConvoScreen:new {
	id = "quest2_brief",
	leftDialog = "@conversation/corellia_rebel_tier3:s_c75a413", -- dynamic - quest granted
	stopConversation = "true",
	options = {}
}
arkon_convo:addScreen(arkon_convo_quest2_brief)

-- Failed Quest 2
arkon_convo_failed_quest2 = ConvoScreen:new {
	id = "failed_quest2",
	leftDialog = "@conversation/corellia_rebel_tier3:s_98dbd811", -- The fleet still needs your help!
	stopConversation = "false",
	options = {
		{"@conversation/corellia_rebel_tier3:s_bf9854b5", "retry_quest2"}, -- I know!
		{"@conversation/corellia_rebel_tier3:s_1dd40de5", "retry_quest2"}, -- I'm doing the best I can!
	}
}
arkon_convo:addScreen(arkon_convo_failed_quest2)

-- Retry Quest 2
arkon_convo_retry_quest2 = ConvoScreen:new {
	id = "retry_quest2",
	leftDialog = "@conversation/corellia_rebel_tier3:s_c75a413", -- dynamic
	stopConversation = "true",
	options = {}
}
arkon_convo:addScreen(arkon_convo_retry_quest2)

-- Excellent Work 2 (Quest 2 Complete) - Grants skill
arkon_convo_excellent_work2 = ConvoScreen:new {
	id = "excellent_work2",
	leftDialog = "@conversation/corellia_rebel_tier3:s_da836e9e", -- Are you prepared to continue your training.
	stopConversation = "false",
	options = {
		{"@conversation/corellia_rebel_tier3:s_269", "training_menu"}, -- In what do I need to be trained?
	}
}
arkon_convo:addScreen(arkon_convo_excellent_work2)

-- Grant Quest 3
arkon_convo_grant_quest3 = ConvoScreen:new {
	id = "grant_quest3",
	leftDialog = "@conversation/corellia_rebel_tier3:s_d40f6011", -- We've definitely got the Emperor's attention. This system is lousy with Imperial forces!
	stopConversation = "false",
	options = {
		{"@conversation/corellia_rebel_tier3:s_c4d60644", "quest3_brief"}, -- I'll say.
		{"@conversation/corellia_rebel_tier3:s_5e62a10a", "quest3_brief"}, -- Give me a mission! I'm ready to fight.
	}
}
arkon_convo:addScreen(arkon_convo_grant_quest3)

-- Quest 3 Brief
arkon_convo_quest3_brief = ConvoScreen:new {
	id = "quest3_brief",
	leftDialog = "@conversation/corellia_rebel_tier3:s_d40f6011", -- dynamic - quest granted
	stopConversation = "true",
	options = {}
}
arkon_convo:addScreen(arkon_convo_quest3_brief)

-- Failed Quest 3
arkon_convo_failed_quest3 = ConvoScreen:new {
	id = "failed_quest3",
	leftDialog = "@conversation/corellia_rebel_tier3:s_c317f1e7", -- If I didn't know better, I'd think you were working for the Emperor. Do your job!!
	stopConversation = "false",
	options = {
		{"@conversation/corellia_rebel_tier3:s_45ab7a66", "retry_quest3"}, -- You don't have to be so mean about it.
		{"@conversation/corellia_rebel_tier3:s_9b43a7ee", "retry_quest3"}, -- Yes sir.
	}
}
arkon_convo:addScreen(arkon_convo_failed_quest3)

-- Retry Quest 3
arkon_convo_retry_quest3 = ConvoScreen:new {
	id = "retry_quest3",
	leftDialog = "@conversation/corellia_rebel_tier3:s_d40f6011", -- dynamic
	stopConversation = "true",
	options = {}
}
arkon_convo:addScreen(arkon_convo_retry_quest3)

-- Excellent Work 3 (Quest 3 Complete) - Grants skill
arkon_convo_excellent_work3 = ConvoScreen:new {
	id = "excellent_work3",
	leftDialog = "@conversation/corellia_rebel_tier3:s_86e0190", -- You're good, but you need to know more if you're ever going to be great.
	stopConversation = "false",
	options = {
		{"@conversation/corellia_rebel_tier3:s_269", "training_menu"}, -- In what do I need to be trained?
	}
}
arkon_convo:addScreen(arkon_convo_excellent_work3)

-- Grant Quest 4
arkon_convo_grant_quest4 = ConvoScreen:new {
	id = "grant_quest4",
	leftDialog = "@conversation/corellia_rebel_tier3:s_a20d4e92", -- Hm. You're quite a pilot.
	stopConversation = "false",
	options = {
		{"@conversation/corellia_rebel_tier3:s_90b3d410", "quest4_brief"}, -- Of course I am.
		{"@conversation/corellia_rebel_tier3:s_efd88602", "quest4_brief"}, -- Glad you think so.
		{"@conversation/corellia_rebel_tier3:s_4cff5cf8", "quest4_brief"}, -- I just want another mission.
	}
}
arkon_convo:addScreen(arkon_convo_grant_quest4)

-- Quest 4 Brief
arkon_convo_quest4_brief = ConvoScreen:new {
	id = "quest4_brief",
	leftDialog = "@conversation/corellia_rebel_tier3:s_a20d4e92", -- dynamic - quest granted
	stopConversation = "true",
	options = {}
}
arkon_convo:addScreen(arkon_convo_quest4_brief)

-- Failed Quest 4
arkon_convo_failed_quest4 = ConvoScreen:new {
	id = "failed_quest4",
	leftDialog = "@conversation/corellia_rebel_tier3:s_85ccda8d", -- I was wrong when I said you were my best pilot.
	stopConversation = "false",
	options = {
		{"@conversation/corellia_rebel_tier3:s_f1a5d3e2", "retry_quest4"}, -- Let me prove it to you!
		{"@conversation/corellia_rebel_tier3:s_292cca3d", "retry_quest4"}, -- I AM your best pilot. I'm just not done yet.
	}
}
arkon_convo:addScreen(arkon_convo_failed_quest4)

-- Retry Quest 4
arkon_convo_retry_quest4 = ConvoScreen:new {
	id = "retry_quest4",
	leftDialog = "@conversation/corellia_rebel_tier3:s_a20d4e92", -- dynamic
	stopConversation = "true",
	options = {}
}
arkon_convo:addScreen(arkon_convo_retry_quest4)

-- All Missions Complete - Grants final skill
arkon_convo_all_missions_complete = ConvoScreen:new {
	id = "all_missions_complete",
	leftDialog = "@conversation/corellia_rebel_tier3:s_85bda55d", -- Outstanding performance up there pilot, I'm proud of you, and of myself of course, for giving such excellent training. You have only one field of expertise left to train in and then you have learned all that I and my men can teach you. You are truly one of the best of the best now %NU.
	stopConversation = "false",
	options = {
		{"@conversation/corellia_rebel_tier3:s_269", "training_menu"}, -- In what do I need to be trained?
	}
}
arkon_convo:addScreen(arkon_convo_all_missions_complete)

-- Training Menu (dynamic options added by handler)
arkon_convo_training_menu = ConvoScreen:new {
	id = "training_menu",
	leftDialog = "@conversation/corellia_rebel_tier3:s_620547d7", -- Soldiers in my unit must be well-trained in all areas. Where are you lacking?
	stopConversation = "false",
	options = {}
}
arkon_convo:addScreen(arkon_convo_training_menu)

-- Completed Arkon (send to next trainer - ready for tier 4)
arkon_convo_completed_arkon = ConvoScreen:new {
	id = "completed_arkon",
	leftDialog = "@conversation/corellia_rebel_tier3:s_6100696", -- All right! I've done the best I can with you. Your transfer has come through.
	stopConversation = "false",
	options = {
		{"@conversation/corellia_rebel_tier3:s_ad721916", "go_to_aqzow"}, -- Finally!
		{"@conversation/corellia_rebel_tier3:s_987445c9", "go_to_aqzow"}, -- Thank you, sir.
	}
}
arkon_convo:addScreen(arkon_convo_completed_arkon)

-- Go to Aqzow
arkon_convo_go_to_aqzow = ConvoScreen:new {
	id = "go_to_aqzow",
	leftDialog = "@conversation/corellia_rebel_tier3:s_6100696", -- dynamic
	stopConversation = "true",
	options = {}
}
arkon_convo:addScreen(arkon_convo_go_to_aqzow)

-- Goodbye
arkon_convo_goodbye = ConvoScreen:new {
	id = "goodbye",
	leftDialog = "@conversation/corellia_rebel_tier3:s_a54fd6b7", -- Do not speak to me until you have completed your mission.
	stopConversation = "true",
	options = {}
}
arkon_convo:addScreen(arkon_convo_goodbye)

addConversationTemplate("arkon_convo", arkon_convo)
