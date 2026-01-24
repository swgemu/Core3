aqzow_convo = ConvoTemplate:new {
	initialScreen = "",
	templateType = "Lua",
	luaClassHandler = "aqzowConvoHandler",
	screens = {}
}

-- Not a Pilot (no JTL skills)
aqzow_convo_no_jtl = ConvoScreen:new {
	id = "no_jtl",
	leftDialog = "@conversation/corellia_rebel_tier4:s_92c6d3dd", -- You don't look like a pilot to me!
	stopConversation = "true",
	options = {}
}
aqzow_convo:addScreen(aqzow_convo_no_jtl)

-- Wrong Faction (Imperial or Neutral)
aqzow_convo_wrong_faction = ConvoScreen:new {
	id = "wrong_faction",
	leftDialog = "@conversation/corellia_rebel_tier4:s_774fb2f0", -- Eh? Who's that? Who are you? Tell me your faction!
	stopConversation = "false",
	options = {
		{"@conversation/corellia_rebel_tier4:s_7e579e1e", "privateer_response"}, -- I'm a privateer.
		{"@conversation/corellia_rebel_tier4:s_fb4c1f1f", "imperial_response"}, -- I'm an Imperial.
	}
}
aqzow_convo:addScreen(aqzow_convo_wrong_faction)

-- Privateer Response
aqzow_convo_privateer_response = ConvoScreen:new {
	id = "privateer_response",
	leftDialog = "@conversation/corellia_rebel_tier4:s_774fb2f0", -- dynamic
	stopConversation = "true",
	options = {}
}
aqzow_convo:addScreen(aqzow_convo_privateer_response)

-- Imperial Response
aqzow_convo_imperial_response = ConvoScreen:new {
	id = "imperial_response",
	leftDialog = "@conversation/corellia_rebel_tier4:s_774fb2f0", -- dynamic
	stopConversation = "true",
	options = {}
}
aqzow_convo:addScreen(aqzow_convo_imperial_response)

-- Non-Havoc Rebel Pilot (not on track)
aqzow_convo_non_havoc_pilot = ConvoScreen:new {
	id = "non_havoc_pilot",
	leftDialog = "@conversation/corellia_rebel_tier4:s_84c908b8", -- Eh? Who's that? You're no... wait, you ARE a Rebel pilot. But you don't fly with this unit. What are you doing here?
	stopConversation = "false",
	options = {
		{"@conversation/corellia_rebel_tier4:s_6222b64d", "no_missions_available"}, -- Do you have any missions that I could fly?
	}
}
aqzow_convo:addScreen(aqzow_convo_non_havoc_pilot)

-- No Missions Available
aqzow_convo_no_missions_available = ConvoScreen:new {
	id = "no_missions_available",
	leftDialog = "@conversation/corellia_rebel_tier4:s_84c908b8", -- dynamic
	stopConversation = "true",
	options = {}
}
aqzow_convo:addScreen(aqzow_convo_no_missions_available)

-- Not Ready (hasn't completed Tier 3)
aqzow_convo_not_ready = ConvoScreen:new {
	id = "not_ready",
	leftDialog = "@conversation/corellia_rebel_tier4:s_4f44d41d", -- No no! You don't belong here!
	stopConversation = "false",
	options = {
		{"@conversation/corellia_rebel_tier4:s_e0dc5fad", "not_ready_explain"}, -- I don't?
		{"@conversation/corellia_rebel_tier4:s_e86f1062", "not_ready_explain"}, -- How do you know?
	}
}
aqzow_convo:addScreen(aqzow_convo_not_ready)

-- Not Ready Explain
aqzow_convo_not_ready_explain = ConvoScreen:new {
	id = "not_ready_explain",
	leftDialog = "@conversation/corellia_rebel_tier4:s_4f44d41d", -- dynamic
	stopConversation = "true",
	options = {}
}
aqzow_convo:addScreen(aqzow_convo_not_ready_explain)

-- Has Active Mission
aqzow_convo_has_mission = ConvoScreen:new {
	id = "has_mission",
	leftDialog = "@conversation/corellia_rebel_tier4:s_256f3624", -- %TU, you lack discipline!
	stopConversation = "false",
	options = {
		{"@conversation/corellia_rebel_tier4:s_4ccb8d59", "goodbye"}, -- I just lack motivation.
		{"@conversation/corellia_rebel_tier4:s_c1013aa7", "goodbye"}, -- Whatever.
	}
}
aqzow_convo:addScreen(aqzow_convo_has_mission)

-- Negative Faction
aqzow_convo_negative_faction = ConvoScreen:new {
	id = "negative_faction",
	leftDialog = "@conversation/corellia_rebel_tier4:s_de1e215f", -- Traitor!
	stopConversation = "false",
	options = {
		{"@conversation/corellia_rebel_tier4:s_7090182", "faction_explain"}, -- What?!
	}
}
aqzow_convo:addScreen(aqzow_convo_negative_faction)

-- Faction Explain
aqzow_convo_faction_explain = ConvoScreen:new {
	id = "faction_explain",
	leftDialog = "@conversation/corellia_rebel_tier4:s_436c2ab2", -- You've been assisting the Empire! Working AGAINST the Rebel Alliance!
	stopConversation = "true",
	options = {}
}
aqzow_convo:addScreen(aqzow_convo_faction_explain)

-- Introduction (hasn't met Aqzow yet)
aqzow_convo_introduction = ConvoScreen:new {
	id = "introduction",
	leftDialog = "@conversation/corellia_rebel_tier4:s_71f899d5", -- It's about time you got here, pilot. Suit up.
	stopConversation = "false",
	options = {
		{"@conversation/corellia_rebel_tier4:s_34d61fa3", "quest1_brief"}, -- Um...I don't think we've met.
	}
}
aqzow_convo:addScreen(aqzow_convo_introduction)

-- Grant Quest 1
aqzow_convo_grant_quest1 = ConvoScreen:new {
	id = "grant_quest1",
	leftDialog = "@conversation/corellia_rebel_tier4:s_5bf6779f", -- OK %NU, let's talk business! This situation is SERIOUS!
	stopConversation = "false",
	options = {
		{"@conversation/corellia_rebel_tier4:s_3609c810", "quest1_brief"}, -- It is?
		{"@conversation/corellia_rebel_tier4:s_3c546115", "goodbye"}, -- Some other time? I'm really busy!
		{"@conversation/corellia_rebel_tier4:s_ef3e641a", "quest1_brief"}, -- I'm here to help.
	}
}
aqzow_convo:addScreen(aqzow_convo_grant_quest1)

-- Quest 1 Brief
aqzow_convo_quest1_brief = ConvoScreen:new {
	id = "quest1_brief",
	leftDialog = "@conversation/corellia_rebel_tier4:s_5bf6779f", -- dynamic - quest granted
	stopConversation = "true",
	options = {}
}
aqzow_convo:addScreen(aqzow_convo_quest1_brief)

-- Failed Quest 1
aqzow_convo_failed_quest1 = ConvoScreen:new {
	id = "failed_quest1",
	leftDialog = "@conversation/corellia_rebel_tier4:s_4f755af2", -- In my day, a pilot would NEVER leave a job unfinished!
	stopConversation = "false",
	options = {
		{"@conversation/corellia_rebel_tier4:s_8f3b3edb", "retry_quest1"}, -- I'm not done yet!
		{"@conversation/corellia_rebel_tier4:s_88563b84", "retry_quest1"}, -- I'm ashamed.
	}
}
aqzow_convo:addScreen(aqzow_convo_failed_quest1)

-- Retry Quest 1
aqzow_convo_retry_quest1 = ConvoScreen:new {
	id = "retry_quest1",
	leftDialog = "@conversation/corellia_rebel_tier4:s_4f755af2", -- dynamic
	stopConversation = "true",
	options = {}
}
aqzow_convo:addScreen(aqzow_convo_retry_quest1)

-- Excellent Work (Quest 1 Complete)
aqzow_convo_excellent_work = ConvoScreen:new {
	id = "excellent_work",
	leftDialog = "@conversation/corellia_rebel_tier4:s_f95cd5f5", -- Mission accomplished! And you know what that means.
	stopConversation = "false",
	options = {
		{"@conversation/corellia_rebel_tier4:s_95c399f6", "training_menu"}, -- I sure do.
		{"@conversation/corellia_rebel_tier4:s_6f679fea", "training_menu"}, -- What does it mean?
	}
}
aqzow_convo:addScreen(aqzow_convo_excellent_work)

-- Grant Quest 2
aqzow_convo_grant_quest2 = ConvoScreen:new {
	id = "grant_quest2",
	leftDialog = "@conversation/corellia_rebel_tier4:s_1047bc70", -- Nice work out there. You really kicked those guys where it counts. Ready for round two?
	stopConversation = "false",
	options = {
		{"@conversation/corellia_rebel_tier4:s_6adec6b0", "quest2_brief"}, -- Of course!
		{"@conversation/corellia_rebel_tier4:s_dcabe09b", "goodbye"}, -- Oh, I'm not here for a mission! I was just looking for the cantina.
		{"@conversation/corellia_rebel_tier4:s_beaf1664", "quest2_brief"}, -- Another errand for Nym the pirate?
	}
}
aqzow_convo:addScreen(aqzow_convo_grant_quest2)

-- Quest 2 Brief
aqzow_convo_quest2_brief = ConvoScreen:new {
	id = "quest2_brief",
	leftDialog = "@conversation/corellia_rebel_tier4:s_1047bc70", -- dynamic - quest granted
	stopConversation = "true",
	options = {}
}
aqzow_convo:addScreen(aqzow_convo_quest2_brief)

-- Failed Quest 2
aqzow_convo_failed_quest2 = ConvoScreen:new {
	id = "failed_quest2",
	leftDialog = "@conversation/corellia_rebel_tier4:s_1909d363", -- You've got to get back out there. You realize what will happen if that Inquisitor gets a hold of your friends?
	stopConversation = "false",
	options = {
		{"@conversation/corellia_rebel_tier4:s_87d7e908", "retry_quest2"}, -- I know.
		{"@conversation/corellia_rebel_tier4:s_e42b260e", "retry_quest2"}, -- I'm on my way.
	}
}
aqzow_convo:addScreen(aqzow_convo_failed_quest2)

-- Retry Quest 2
aqzow_convo_retry_quest2 = ConvoScreen:new {
	id = "retry_quest2",
	leftDialog = "@conversation/corellia_rebel_tier4:s_1909d363", -- dynamic
	stopConversation = "true",
	options = {}
}
aqzow_convo:addScreen(aqzow_convo_retry_quest2)

-- Excellent Work 2 (Quest 2 Complete)
aqzow_convo_excellent_work2 = ConvoScreen:new {
	id = "excellent_work2",
	leftDialog = "@conversation/corellia_rebel_tier4:s_da8e9da5", -- See? You could save the day after all! Not bad.
	stopConversation = "false",
	options = {
		{"@conversation/corellia_rebel_tier4:s_def742", "training_menu"}, -- You were right.
		{"@conversation/corellia_rebel_tier4:s_b20c71fe", "training_menu"}, -- It wasn't easy.
	}
}
aqzow_convo:addScreen(aqzow_convo_excellent_work2)

-- Grant Quest 3
aqzow_convo_grant_quest3 = ConvoScreen:new {
	id = "grant_quest3",
	leftDialog = "@conversation/corellia_rebel_tier4:s_e8f374d9", -- Hey Rebel! I've got a new assignment for you.
	stopConversation = "false",
	options = {
		{"@conversation/corellia_rebel_tier4:s_1c8bddbb", "quest3_brief"}, -- What is it?
		{"@conversation/corellia_rebel_tier4:s_f48fdfbd", "goodbye"}, -- Ship's in the shop.
		{"@conversation/corellia_rebel_tier4:s_1551b284", "quest3_brief"}, -- Something good?
		{"@conversation/corellia_rebel_tier4:s_60080304", "quest3_brief"}, -- Not another Inquisitor assignment, I hope.
	}
}
aqzow_convo:addScreen(aqzow_convo_grant_quest3)

-- Quest 3 Brief
aqzow_convo_quest3_brief = ConvoScreen:new {
	id = "quest3_brief",
	leftDialog = "@conversation/corellia_rebel_tier4:s_e8f374d9", -- dynamic - quest granted
	stopConversation = "true",
	options = {}
}
aqzow_convo:addScreen(aqzow_convo_quest3_brief)

-- Failed Quest 3
aqzow_convo_failed_quest3 = ConvoScreen:new {
	id = "failed_quest3",
	leftDialog = "@conversation/corellia_rebel_tier4:s_d3d98e75", -- That was a complete disaster!
	stopConversation = "false",
	options = {
		{"@conversation/corellia_rebel_tier4:s_e30b9697", "retry_quest3"}, -- Hey, things don't always turn out right!
		{"@conversation/corellia_rebel_tier4:s_10eafe13", "retry_quest3"}, -- I'm not done yet!
	}
}
aqzow_convo:addScreen(aqzow_convo_failed_quest3)

-- Retry Quest 3
aqzow_convo_retry_quest3 = ConvoScreen:new {
	id = "retry_quest3",
	leftDialog = "@conversation/corellia_rebel_tier4:s_d3d98e75", -- dynamic
	stopConversation = "true",
	options = {}
}
aqzow_convo:addScreen(aqzow_convo_retry_quest3)

-- Excellent Work 3 (Quest 3 Complete)
aqzow_convo_excellent_work3 = ConvoScreen:new {
	id = "excellent_work3",
	leftDialog = "@conversation/corellia_rebel_tier4:s_10d8bf69", -- I salute you, Rebel!
	stopConversation = "false",
	options = {
		{"@conversation/corellia_rebel_tier4:s_aed5139a", "training_menu"}, -- No need for that.
		{"@conversation/corellia_rebel_tier4:s_cb6eb294", "training_menu"}, -- Aw shucks.
	}
}
aqzow_convo:addScreen(aqzow_convo_excellent_work3)

-- Grant Quest 4
aqzow_convo_grant_quest4 = ConvoScreen:new {
	id = "grant_quest4",
	leftDialog = "@conversation/corellia_rebel_tier4:s_ceb77d0c", -- We've got the Empire on the run! Let's kick 'em while they're down!
	stopConversation = "false",
	options = {
		{"@conversation/corellia_rebel_tier4:s_5673ded2", "quest4_brief"}, -- Are they really on the run?
		{"@conversation/corellia_rebel_tier4:s_9976a72", "goodbye"}, -- Get somebody else to do your dirty work! I need a break.
		{"@conversation/corellia_rebel_tier4:s_5fe6ae71", "quest4_brief"}, -- Haha! You're joking, right?
	}
}
aqzow_convo:addScreen(aqzow_convo_grant_quest4)

-- Quest 4 Brief
aqzow_convo_quest4_brief = ConvoScreen:new {
	id = "quest4_brief",
	leftDialog = "@conversation/corellia_rebel_tier4:s_ceb77d0c", -- dynamic - quest granted
	stopConversation = "true",
	options = {}
}
aqzow_convo:addScreen(aqzow_convo_quest4_brief)

-- Failed Quest 4
aqzow_convo_failed_quest4 = ConvoScreen:new {
	id = "failed_quest4",
	leftDialog = "@conversation/corellia_rebel_tier4:s_78b8ac8f", -- Oh what is THIS. I told you to take out those freighters!
	stopConversation = "false",
	options = {
		{"@conversation/corellia_rebel_tier4:s_4dd9a7b9", "retry_quest4"}, -- Those ships have guns!
		{"@conversation/corellia_rebel_tier4:s_35dd4aa2", "retry_quest4"}, -- Yes, I know!
	}
}
aqzow_convo:addScreen(aqzow_convo_failed_quest4)

-- Retry Quest 4
aqzow_convo_retry_quest4 = ConvoScreen:new {
	id = "retry_quest4",
	leftDialog = "@conversation/corellia_rebel_tier4:s_78b8ac8f", -- dynamic
	stopConversation = "true",
	options = {}
}
aqzow_convo:addScreen(aqzow_convo_retry_quest4)

-- Excellent Work 4 (Quest 4 Complete)
aqzow_convo_excellent_work4 = ConvoScreen:new {
	id = "excellent_work4",
	leftDialog = "@conversation/corellia_rebel_tier4:s_81e25d24", -- You showed them! Let's see the Empire try to build a station in THIS system!
	stopConversation = "false",
	options = {
		{"@conversation/corellia_rebel_tier4:s_61485366", "training_menu"}, -- It's not going to happen anytime soon.
		{"@conversation/corellia_rebel_tier4:s_197c8928", "training_menu"}, -- Happy to serve.
	}
}
aqzow_convo:addScreen(aqzow_convo_excellent_work4)

-- Training Menu (dynamic options added by handler)
aqzow_convo_training_menu = ConvoScreen:new {
	id = "training_menu",
	leftDialog = "@conversation/corellia_rebel_tier4:s_8907c99", -- Hey! You! You're still pretty wet behind the ears, you know. What you need are SKILLS! And you've come to the right place. I grant skills. Even to fools like yourself!
	stopConversation = "false",
	options = {
		{"@conversation/corellia_rebel_tier4:s_421", "train_skill"}, -- What skill am I to learn?
	}
}
aqzow_convo:addScreen(aqzow_convo_training_menu)

-- Train Skill (dynamic)
aqzow_convo_train_skill = ConvoScreen:new {
	id = "train_skill",
	leftDialog = "@conversation/corellia_rebel_tier4:s_8907c99", -- dynamic
	stopConversation = "false",
	options = {}
}
aqzow_convo:addScreen(aqzow_convo_train_skill)

-- Duty Missions Menu
aqzow_convo_duty_missions = ConvoScreen:new {
	id = "duty_missions",
	leftDialog = "@conversation/corellia_rebel_tier4:s_a5958aac", -- I'd like to see you do some WORK for a change! Sign up for something, pronto. Or do I have to explain it to you again?
	stopConversation = "false",
	options = {
		{"@conversation/corellia_rebel_tier4:s_647ad2bc", "destroy_duty"}, -- I'll take care of those Black Suns.
		{"@conversation/corellia_rebel_tier4:s_d9116b4d", "escort_duty"}, -- I'll escort those freighters.
		{"@conversation/corellia_rebel_tier4:s_8450d7db", "recovery_duty"}, -- Let me take a crack at disabling those troop transports.
		{"@conversation/corellia_rebel_tier4:s_9943289", "rescue_duty"}, -- I want to help those scientists.
		{"@conversation/corellia_rebel_tier4:s_9775f996", "explain_duties"}, -- Can you explain it again?
	}
}
aqzow_convo:addScreen(aqzow_convo_duty_missions)

-- Destroy Duty (Black Suns - Dantooine)
aqzow_convo_destroy_duty = ConvoScreen:new {
	id = "destroy_duty",
	leftDialog = "@conversation/corellia_rebel_tier4:s_d8209030", -- Then you're going to Dantooine! Goodbye!
	stopConversation = "true",
	options = {}
}
aqzow_convo:addScreen(aqzow_convo_destroy_duty)

-- Escort Duty (Freighters - Dathomir)
aqzow_convo_escort_duty = ConvoScreen:new {
	id = "escort_duty",
	leftDialog = "@conversation/corellia_rebel_tier4:s_fed79efe", -- Then hurry up and get yourself over to Dathomir!
	stopConversation = "true",
	options = {}
}
aqzow_convo:addScreen(aqzow_convo_escort_duty)

-- Recovery Duty (Troop Transports - Endor)
aqzow_convo_recovery_duty = ConvoScreen:new {
	id = "recovery_duty",
	leftDialog = "@conversation/corellia_rebel_tier4:s_b0d064ef", -- Endor it is! Leave immediately!
	stopConversation = "true",
	options = {}
}
aqzow_convo:addScreen(aqzow_convo_recovery_duty)

-- Rescue Duty (Scientists - Dantooine)
aqzow_convo_rescue_duty = ConvoScreen:new {
	id = "rescue_duty",
	leftDialog = "@conversation/corellia_rebel_tier4:s_835acc11", -- You think you're a hero or something? Fine! Go on! You'll find your scientists in the Dantooine system.
	stopConversation = "true",
	options = {}
}
aqzow_convo:addScreen(aqzow_convo_rescue_duty)

-- Explain Duties
aqzow_convo_explain_duties = ConvoScreen:new {
	id = "explain_duties",
	leftDialog = "@conversation/corellia_rebel_tier4:s_4bce8f6f", -- Fine, listen up. We are looking at several situations here, and I'd like to see what you can do. First of all, the Black Suns have been taking a lot of business from us lately. Nym doesn't like it. We need a pilot to send them a message. A LOUD message. Heh!
	stopConversation = "false",
	options = {
		{"@conversation/corellia_rebel_tier4:s_384", "duty_missions"}, -- Okay...
	}
}
aqzow_convo:addScreen(aqzow_convo_explain_duties)

-- Completed Tier 4 (send to Burke for master training)
aqzow_convo_completed_tier4 = ConvoScreen:new {
	id = "completed_tier4",
	leftDialog = "@conversation/corellia_rebel_tier4:s_b6b4b241", -- Attention! Alliance Headquarters has approved your transfer. You are now serving under the command of Admiral Willham Burke, good man. You are to report to Admiral Burke immediately, so pack up your gear and get moving.
	stopConversation = "false",
	options = {
		{"@conversation/corellia_rebel_tier4:s_bbe3529b", "go_to_burke"}, -- Who is Admiral Burke?
		{"@conversation/corellia_rebel_tier4:s_36f346a5", "go_to_burke"}, -- What if I don't have any gear, sir?
	}
}
aqzow_convo:addScreen(aqzow_convo_completed_tier4)

-- Go to Burke
aqzow_convo_go_to_burke = ConvoScreen:new {
	id = "go_to_burke",
	leftDialog = "@conversation/corellia_rebel_tier4:s_b6b4b241", -- dynamic
	stopConversation = "true",
	options = {}
}
aqzow_convo:addScreen(aqzow_convo_go_to_burke)

-- Master Pilot (returning after completing Burke's training)
aqzow_convo_master_pilot = ConvoScreen:new {
	id = "master_pilot",
	leftDialog = "@conversation/corellia_rebel_tier4:s_d318a2bb", -- Back from your assignment with Admiral Burke, I see! I hope that everything went according to plan. I can use your help around here!
	stopConversation = "false",
	options = {
		{"@conversation/corellia_rebel_tier4:s_647ad2bc", "destroy_duty"}, -- I'll take care of those Black Suns.
		{"@conversation/corellia_rebel_tier4:s_d9116b4d", "escort_duty"}, -- I'll escort those freighters.
		{"@conversation/corellia_rebel_tier4:s_8450d7db", "recovery_duty"}, -- Let me take a crack at disabling those troop transports.
		{"@conversation/corellia_rebel_tier4:s_9943289", "rescue_duty"}, -- I want to help those scientists.
		{"@conversation/corellia_rebel_tier4:s_9775f996", "explain_duties"}, -- Can you explain it again?
	}
}
aqzow_convo:addScreen(aqzow_convo_master_pilot)

-- Goodbye
aqzow_convo_goodbye = ConvoScreen:new {
	id = "goodbye",
	leftDialog = "@conversation/corellia_rebel_tier4:s_256f3624", -- %TU, you lack discipline!
	stopConversation = "true",
	options = {}
}
aqzow_convo:addScreen(aqzow_convo_goodbye)

addConversationTemplate("aqzow_convo", aqzow_convo)
