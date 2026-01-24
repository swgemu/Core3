vrovel_convo = ConvoTemplate:new {
	initialScreen = "",
	templateType = "Lua",
	luaClassHandler = "vrovelConvoHandler",
	screens = {}
}

-- Not a Pilot (no JTL skills)
vrovel_convo_no_jtl = ConvoScreen:new {
	id = "no_jtl",
	leftDialog = "@conversation/naboo_rebel_tier4:s_3daae2ee", -- Do I know you?
	stopConversation = "false",
	options = {
		{"@conversation/naboo_rebel_tier4:s_b3218dae", "no_jtl_dismiss"}, -- I don't think so.
		{"@conversation/naboo_rebel_tier4:s_4c695dbd", "no_jtl_dismiss"}, -- No.
	}
}
vrovel_convo:addScreen(vrovel_convo_no_jtl)

-- No JTL Dismiss
vrovel_convo_no_jtl_dismiss = ConvoScreen:new {
	id = "no_jtl_dismiss",
	leftDialog = "@conversation/naboo_rebel_tier4:s_3daae2ee", -- dynamic
	stopConversation = "true",
	options = {}
}
vrovel_convo:addScreen(vrovel_convo_no_jtl_dismiss)

-- Imperial/Wrong Faction
vrovel_convo_imperial_pilot = ConvoScreen:new {
	id = "imperial_pilot",
	leftDialog = "@conversation/naboo_rebel_tier4:s_9", -- Sorry, do I know you?
	stopConversation = "false",
	options = {
		{"@conversation/naboo_rebel_tier4:s_11", "imperial_dismiss"}, -- I don't think so.
		{"@conversation/naboo_rebel_tier4:s_15", "imperial_dismiss"}, -- No.
	}
}
vrovel_convo:addScreen(vrovel_convo_imperial_pilot)

-- Imperial Dismiss
vrovel_convo_imperial_dismiss = ConvoScreen:new {
	id = "imperial_dismiss",
	leftDialog = "@conversation/naboo_rebel_tier4:s_9", -- dynamic
	stopConversation = "true",
	options = {}
}
vrovel_convo:addScreen(vrovel_convo_imperial_dismiss)

-- Neutral Pilot
vrovel_convo_neutral_pilot = ConvoScreen:new {
	id = "neutral_pilot",
	leftDialog = "@conversation/naboo_rebel_tier4:s_9", -- Sorry, do I know you?
	stopConversation = "false",
	options = {
		{"@conversation/naboo_rebel_tier4:s_11", "neutral_dismiss"}, -- I don't think so.
		{"@conversation/naboo_rebel_tier4:s_15", "neutral_dismiss"}, -- No.
	}
}
vrovel_convo:addScreen(vrovel_convo_neutral_pilot)

-- Neutral Dismiss
vrovel_convo_neutral_dismiss = ConvoScreen:new {
	id = "neutral_dismiss",
	leftDialog = "@conversation/naboo_rebel_tier4:s_9", -- dynamic
	stopConversation = "true",
	options = {}
}
vrovel_convo:addScreen(vrovel_convo_neutral_dismiss)

-- Non-Vortex Rebel Pilot (not on track)
vrovel_convo_non_vortex_pilot = ConvoScreen:new {
	id = "non_vortex_pilot",
	leftDialog = "@conversation/naboo_rebel_tier4:s_8cd97e8b", -- You're a Rebel pilot? But you're not part of this unit. Are you lost?
	stopConversation = "false",
	options = {
		{"@conversation/naboo_rebel_tier4:s_dab8fd8e", "non_track_explain"}, -- No. Do you have a mission that I can fly?
	}
}
vrovel_convo:addScreen(vrovel_convo_non_vortex_pilot)

-- Non Track Explain
vrovel_convo_non_track_explain = ConvoScreen:new {
	id = "non_track_explain",
	leftDialog = "@conversation/naboo_rebel_tier4:s_8cd97e8b", -- dynamic
	stopConversation = "true",
	options = {}
}
vrovel_convo:addScreen(vrovel_convo_non_track_explain)

-- Negative Faction
vrovel_convo_negative_faction = ConvoScreen:new {
	id = "negative_faction",
	leftDialog = "@conversation/naboo_rebel_tier4:s_2f2320af", -- What are you, %NU, some kind of double agent?
	stopConversation = "false",
	options = {
		{"@conversation/naboo_rebel_tier4:s_457a7010", "faction_explain"}, -- No
	}
}
vrovel_convo:addScreen(vrovel_convo_negative_faction)

-- Faction Explain
vrovel_convo_faction_explain = ConvoScreen:new {
	id = "faction_explain",
	leftDialog = "@conversation/naboo_rebel_tier4:s_2f2320af", -- dynamic
	stopConversation = "true",
	options = {}
}
vrovel_convo:addScreen(vrovel_convo_faction_explain)

-- Not Tier 3 Complete (not ready for tier 4)
vrovel_convo_not_tier3_complete = ConvoScreen:new {
	id = "not_tier3_complete",
	leftDialog = "@conversation/naboo_rebel_tier4:s_243a81bd", -- Ezkiel is still in need of your services.
	stopConversation = "false",
	options = {
		{"@conversation/naboo_rebel_tier4:s_c2d98904", "not_ready_dismiss"}, -- Ah yes.
		{"@conversation/naboo_rebel_tier4:s_13f3baf7", "not_ready_dismiss"}, -- How did you know?
	}
}
vrovel_convo:addScreen(vrovel_convo_not_tier3_complete)

-- Not Ready Dismiss
vrovel_convo_not_ready_dismiss = ConvoScreen:new {
	id = "not_ready_dismiss",
	leftDialog = "@conversation/naboo_rebel_tier4:s_243a81bd", -- dynamic
	stopConversation = "true",
	options = {}
}
vrovel_convo:addScreen(vrovel_convo_not_ready_dismiss)

-- Has Active Mission
vrovel_convo_has_mission = ConvoScreen:new {
	id = "has_mission",
	leftDialog = "@conversation/naboo_rebel_tier4:s_e59caef0", -- You've received your orders.
	stopConversation = "false",
	options = {
		{"@conversation/naboo_rebel_tier4:s_d92f71f", "goodbye"}, -- Yes, I know.
		{"@conversation/naboo_rebel_tier4:s_9b43a7ee", "goodbye"}, -- Yes sir.
	}
}
vrovel_convo:addScreen(vrovel_convo_has_mission)

-- Failed Mission 1
vrovel_convo_failed_quest1 = ConvoScreen:new {
	id = "failed_quest1",
	leftDialog = "@conversation/naboo_rebel_tier4:s_e8a5b38", -- Blast it! Don't you know how important this mission is?
	stopConversation = "false",
	options = {
		{"@conversation/naboo_rebel_tier4:s_47443361", "retry_quest1"}, -- Don't worry. It'll get done.
		{"@conversation/naboo_rebel_tier4:s_b9b677c2", "retry_quest1"}, -- I ran into a little trouble. It won't happen again.
	}
}
vrovel_convo:addScreen(vrovel_convo_failed_quest1)

-- Retry Quest 1
vrovel_convo_retry_quest1 = ConvoScreen:new {
	id = "retry_quest1",
	leftDialog = "@conversation/naboo_rebel_tier4:s_e8a5b38", -- dynamic
	stopConversation = "true",
	options = {}
}
vrovel_convo:addScreen(vrovel_convo_retry_quest1)

-- Failed Mission 2
vrovel_convo_failed_quest2 = ConvoScreen:new {
	id = "failed_quest2",
	leftDialog = "@conversation/naboo_rebel_tier4:s_4e4d6d23", -- Do you realize what will happen if the Inquisitor reaches his destination?
	stopConversation = "false",
	options = {
		{"@conversation/naboo_rebel_tier4:s_25a79f70", "retry_quest2"}, -- I'm fully aware of the situation, sir!
		{"@conversation/naboo_rebel_tier4:s_d4928d9c", "retry_quest2"}, -- That's not going to happen.
	}
}
vrovel_convo:addScreen(vrovel_convo_failed_quest2)

-- Retry Quest 2
vrovel_convo_retry_quest2 = ConvoScreen:new {
	id = "retry_quest2",
	leftDialog = "@conversation/naboo_rebel_tier4:s_4e4d6d23", -- dynamic
	stopConversation = "true",
	options = {}
}
vrovel_convo:addScreen(vrovel_convo_retry_quest2)

-- Failed Mission 3
vrovel_convo_failed_quest3 = ConvoScreen:new {
	id = "failed_quest3",
	leftDialog = "@conversation/naboo_rebel_tier4:s_d9bfbc18", -- You realize that if the Inquisition gets their hands on that spy...well, you just realize the situation, don't you?
	stopConversation = "false",
	options = {
		{"@conversation/naboo_rebel_tier4:s_23b92517", "retry_quest3"}, -- Of course. I'll bring him in.
		{"@conversation/naboo_rebel_tier4:s_461e9b3f", "retry_quest3"}, -- You've got nothing to worry about.
	}
}
vrovel_convo:addScreen(vrovel_convo_failed_quest3)

-- Retry Quest 3
vrovel_convo_retry_quest3 = ConvoScreen:new {
	id = "retry_quest3",
	leftDialog = "@conversation/naboo_rebel_tier4:s_d9bfbc18", -- dynamic
	stopConversation = "true",
	options = {}
}
vrovel_convo:addScreen(vrovel_convo_retry_quest3)

-- Failed Mission 4
vrovel_convo_failed_quest4 = ConvoScreen:new {
	id = "failed_quest4",
	leftDialog = "@conversation/naboo_rebel_tier4:s_82450216", -- Do you mean to tell me that's the best you can do?
	stopConversation = "false",
	options = {
		{"@conversation/naboo_rebel_tier4:s_f5427310", "retry_quest4"}, -- Of course not!
		{"@conversation/naboo_rebel_tier4:s_28a543ae", "retry_quest4"}, -- I'm not done yet.
	}
}
vrovel_convo:addScreen(vrovel_convo_failed_quest4)

-- Retry Quest 4
vrovel_convo_retry_quest4 = ConvoScreen:new {
	id = "retry_quest4",
	leftDialog = "@conversation/naboo_rebel_tier4:s_82450216", -- dynamic
	stopConversation = "true",
	options = {}
}
vrovel_convo:addScreen(vrovel_convo_retry_quest4)

-- Mission 1 Complete (reward)
vrovel_convo_excellent_work = ConvoScreen:new {
	id = "excellent_work",
	leftDialog = "@conversation/naboo_rebel_tier4:s_4222dbd0", -- Very nice, %TU! We are making inroads. The Inquisition is in for a surprise.
	stopConversation = "false",
	options = {
		{"@conversation/naboo_rebel_tier4:s_6b169ba1", "grant_quest2"}, -- Let's hope they continue to underestimate us.
		{"@conversation/naboo_rebel_tier4:s_d9cced1f", "grant_quest2"}, -- Absolutely.
	}
}
vrovel_convo:addScreen(vrovel_convo_excellent_work)

-- Mission 2 Complete (reward)
vrovel_convo_excellent_work2 = ConvoScreen:new {
	id = "excellent_work2",
	leftDialog = "@conversation/naboo_rebel_tier4:s_e282986e", -- Duty pay, for my best pilot!
	stopConversation = "false",
	options = {
		{"@conversation/naboo_rebel_tier4:s_88099422", "grant_quest3"}, -- Come on, Evin. Don't lay it on too thick.
		{"@conversation/naboo_rebel_tier4:s_a2454aa3", "grant_quest3"}, -- Hey! SOMEBODY'S got to be the best.
	}
}
vrovel_convo:addScreen(vrovel_convo_excellent_work2)

-- Mission 3 Complete (reward)
vrovel_convo_excellent_work3 = ConvoScreen:new {
	id = "excellent_work3",
	leftDialog = "@conversation/naboo_rebel_tier4:s_75a002d0", -- Our secrets are safe for another day!
	stopConversation = "false",
	options = {
		{"@conversation/naboo_rebel_tier4:s_6371b34a", "grant_quest4"}, -- Sure - thanks to me.
		{"@conversation/naboo_rebel_tier4:s_2c61b117", "grant_quest4"}, -- I don't know if the situation is THAT serious.
	}
}
vrovel_convo:addScreen(vrovel_convo_excellent_work3)

-- Mission 4 Complete (reward)
vrovel_convo_excellent_work4 = ConvoScreen:new {
	id = "excellent_work4",
	leftDialog = "@conversation/naboo_rebel_tier4:s_682985ff", -- That was FANTASTIC! I just wish I could have seen the expression on those Imperial faces!
	stopConversation = "false",
	options = {
		{"@conversation/naboo_rebel_tier4:s_2928468c", "training_menu"}, -- The Inquisition won't be operating in this system anytime soon.
		{"@conversation/naboo_rebel_tier4:s_cbb055c6", "training_menu"}, -- They weren't smiling, I can promise you that.
	}
}
vrovel_convo:addScreen(vrovel_convo_excellent_work4)

-- Ready for Mission 4
vrovel_convo_grant_quest4 = ConvoScreen:new {
	id = "grant_quest4",
	leftDialog = "@conversation/naboo_rebel_tier4:s_4a858e06", -- Incredible work out there! The spy is safe and sound - and so is his information. Soon, we'll have new Jedi walking among us! The entire Vortex organization is grateful for your help.
	stopConversation = "false",
	options = {
		{"@conversation/naboo_rebel_tier4:s_5d4e24a2", "quest4_brief"}, -- I'm glad I can be of use.
		{"@conversation/naboo_rebel_tier4:s_9f4dbe82", "quest4_brief"}, -- I'm always ready to fight the Empire.
	}
}
vrovel_convo:addScreen(vrovel_convo_grant_quest4)

-- Quest 4 Brief
vrovel_convo_quest4_brief = ConvoScreen:new {
	id = "quest4_brief",
	leftDialog = "@conversation/naboo_rebel_tier4:s_4a858e06", -- dynamic - quest granted
	stopConversation = "true",
	options = {}
}
vrovel_convo:addScreen(vrovel_convo_quest4_brief)

-- Ready for Mission 3
vrovel_convo_grant_quest3 = ConvoScreen:new {
	id = "grant_quest3",
	leftDialog = "@conversation/naboo_rebel_tier4:s_fc2f8c4c", -- Nice job on that last mission. That Inquisitor didn't know what hit him!
	stopConversation = "false",
	options = {
		{"@conversation/naboo_rebel_tier4:s_5d4e24a2", "quest3_brief"}, -- I'm glad I can be of use.
		{"@conversation/naboo_rebel_tier4:s_9f4dbe82", "quest3_brief"}, -- I'm always ready to fight the Empire.
	}
}
vrovel_convo:addScreen(vrovel_convo_grant_quest3)

-- Quest 3 Brief
vrovel_convo_quest3_brief = ConvoScreen:new {
	id = "quest3_brief",
	leftDialog = "@conversation/naboo_rebel_tier4:s_fc2f8c4c", -- dynamic - quest granted
	stopConversation = "true",
	options = {}
}
vrovel_convo:addScreen(vrovel_convo_quest3_brief)

-- Ready for Mission 2
vrovel_convo_grant_quest2 = ConvoScreen:new {
	id = "grant_quest2",
	leftDialog = "@conversation/naboo_rebel_tier4:s_4222dbd0", -- dynamic
	stopConversation = "false",
	options = {
		{"@conversation/naboo_rebel_tier4:s_5d4e24a2", "quest2_brief"}, -- I'm glad I can be of use.
		{"@conversation/naboo_rebel_tier4:s_9f4dbe82", "quest2_brief"}, -- I'm always ready to fight the Empire.
	}
}
vrovel_convo:addScreen(vrovel_convo_grant_quest2)

-- Quest 2 Brief
vrovel_convo_quest2_brief = ConvoScreen:new {
	id = "quest2_brief",
	leftDialog = "@conversation/naboo_rebel_tier4:s_4222dbd0", -- dynamic - quest granted
	stopConversation = "true",
	options = {}
}
vrovel_convo:addScreen(vrovel_convo_quest2_brief)

-- Training Menu (dynamic options added by handler)
vrovel_convo_training_menu = ConvoScreen:new {
	id = "training_menu",
	leftDialog = "@conversation/naboo_rebel_tier4:s_682985ff", -- dynamic
	stopConversation = "false",
	options = {}
}
vrovel_convo:addScreen(vrovel_convo_training_menu)

-- Goodbye
vrovel_convo_goodbye = ConvoScreen:new {
	id = "goodbye",
	leftDialog = "@conversation/naboo_rebel_tier4:s_3daae2ee", -- dynamic
	stopConversation = "true",
	options = {}
}
vrovel_convo:addScreen(vrovel_convo_goodbye)

addConversationTemplate("vrovel_convo", vrovel_convo)
