arkon_convo = ConvoTemplate:new {
	initialScreen = "",
	templateType = "Lua",
	luaClassHandler = "arkonConvoHandler",
	screens = {}
}

-- ========================================
-- Gate Screens
-- ========================================

-- Not a Pilot (JTL disabled)
no_jtl = ConvoScreen:new {
	id = "no_jtl",
	leftDialog = "@conversation/corellia_rebel_tier4:s_92c6d3dd", -- You don't look like a pilot to me!
	animation = "wave_on_dismissing",
	stopConversation = "true",
	options = {}
}
arkon_convo:addScreen(no_jtl)

-- Imperial Pilot
imperial_pilot = ConvoScreen:new {
	id = "imperial_pilot",
	leftDialog = "@conversation/corellia_rebel_tier4:s_2da082b6", -- IMPERIAL?! I hate Imperials! Get out of here!
	animation = "standing_raise_fist",
	stopConversation = "true",
	options = {}
}
arkon_convo:addScreen(imperial_pilot)

-- Neutral Pilot
neutral_pilot = ConvoScreen:new {
	id = "neutral_pilot",
	leftDialog = "@conversation/corellia_rebel_tier4:s_649d2a19", -- Privateer? No privateers here! Go on, get out of here!
	animation = "shake_head_disgust",
	stopConversation = "true",
	options = {}
}
arkon_convo:addScreen(neutral_pilot)

-- Not Rebel Pilot
not_rebel_pilot = ConvoScreen:new {
	id = "not_rebel_pilot",
	leftDialog = "@conversation/corellia_rebel_tier4:s_92c6d3dd", -- You don't look like a pilot to me!
	animation = "wave_on_dismissing",
	stopConversation = "true",
	options = {}
}
arkon_convo:addScreen(not_rebel_pilot)

-- Non-Havoc Rebel Pilot (wrong track)
non_havoc_pilot = ConvoScreen:new {
	id = "non_havoc_pilot",
	leftDialog = "@conversation/corellia_rebel_tier4:s_84c908b8", -- ...you ARE a Rebel pilot. But you don't fly with this unit. What are you doing here?
	stopConversation = "false",
	options = {
		{"@conversation/corellia_rebel_tier4:s_6222b64d", "non_havoc_reject"}, -- Do you have any missions that I could fly?
	}
}
arkon_convo:addScreen(non_havoc_pilot)

non_havoc_reject = ConvoScreen:new {
	id = "non_havoc_reject",
	leftDialog = "@conversation/corellia_rebel_tier4:s_c73f5fdb", -- You should know better than that. Only your commanding officer can give you missions...
	stopConversation = "true",
	options = {}
}
arkon_convo:addScreen(non_havoc_reject)

-- Not Ready (hasn't completed Tier 3)
not_ready = ConvoScreen:new {
	id = "not_ready",
	leftDialog = "@conversation/corellia_rebel_tier4:s_4f44d41d", -- No no! You don't belong here!
	animation = "wave_finger_warning",
	stopConversation = "false",
	options = {
		{"@conversation/corellia_rebel_tier4:s_e0dc5fad", "not_ready_work"}, -- I don't?
		{"@conversation/corellia_rebel_tier4:s_e86f1062", "not_ready_rude"}, -- How do you know?
	}
}
arkon_convo:addScreen(not_ready)

not_ready_work = ConvoScreen:new {
	id = "not_ready_work",
	leftDialog = "@conversation/corellia_rebel_tier4:s_3bcc34e7", -- Oh no! You've got WORK to do, junior!
	stopConversation = "true",
	options = {}
}
arkon_convo:addScreen(not_ready_work)

not_ready_rude = ConvoScreen:new {
	id = "not_ready_rude",
	leftDialog = "@conversation/corellia_rebel_tier4:s_5e0e14bc", -- BECAUSE I just know, that's how!...
	animation = "stamp_feet",
	stopConversation = "true",
	options = {}
}
arkon_convo:addScreen(not_ready_rude)

-- Has Active Mission
has_mission = ConvoScreen:new {
	id = "has_mission",
	leftDialog = "@conversation/corellia_rebel_tier4:s_256f3624", -- %TU, you lack discipline!
	stopConversation = "false",
	options = {
		{"@conversation/corellia_rebel_tier4:s_4ccb8d59", "on_mission_boot"}, -- I just lack motivation.
		{"@conversation/corellia_rebel_tier4:s_c1013aa7", "on_mission_whatever"}, -- Whatever.
	}
}
arkon_convo:addScreen(has_mission)

on_mission_boot = ConvoScreen:new {
	id = "on_mission_boot",
	leftDialog = "@conversation/corellia_rebel_tier4:s_549b97e6", -- I'll motivate you with the tip of my BOOT! Get to work!
	animation = "standing_raise_fist",
	stopConversation = "true",
	options = {}
}
arkon_convo:addScreen(on_mission_boot)

on_mission_whatever = ConvoScreen:new {
	id = "on_mission_whatever",
	leftDialog = "@conversation/corellia_rebel_tier4:s_86df2510", -- Is that your idea of a comeback? Grow up! Get to work!
	animation = "wave_on_dismissing",
	playerAnimation = "shrug_shoulders",
	stopConversation = "true",
	options = {}
}
arkon_convo:addScreen(on_mission_whatever)

-- ========================================
-- Negative Faction
-- ========================================

negative_faction = ConvoScreen:new {
	id = "negative_faction",
	leftDialog = "@conversation/corellia_rebel_tier4:s_de1e215f", -- Traitor!
	animation = "slit_throat",
	stopConversation = "false",
	options = {
		{"@conversation/corellia_rebel_tier4:s_7090182", "neg_faction_accuse"}, -- What?!
	}
}
arkon_convo:addScreen(negative_faction)

neg_faction_accuse = ConvoScreen:new {
	id = "neg_faction_accuse",
	leftDialog = "@conversation/corellia_rebel_tier4:s_436c2ab2", -- You've been assisting the Empire! Working AGAINST the Rebel Alliance!
	animation = "pound_fist_palm",
	stopConversation = "false",
	options = {
		{"@conversation/corellia_rebel_tier4:s_77e48d5b", "neg_faction_grounded"}, -- What do you mean?
	}
}
arkon_convo:addScreen(neg_faction_accuse)

neg_faction_grounded = ConvoScreen:new {
	id = "neg_faction_grounded",
	leftDialog = "@conversation/corellia_rebel_tier4:s_2744b825", -- What I mean, pilot, is that you are grounded until further notice...
	animation = "explain",
	stopConversation = "false",
	options = {
		{"@conversation/corellia_rebel_tier4:s_ad621c08", "neg_faction_improve"}, -- Ever?
	}
}
arkon_convo:addScreen(neg_faction_grounded)

neg_faction_improve = ConvoScreen:new {
	id = "neg_faction_improve",
	leftDialog = "@conversation/corellia_rebel_tier4:s_ee83a0c2", -- 'Til you improve your standing with the Rebel Alliance...
	animation = "point_accusingly",
	stopConversation = "true",
	options = {}
}
arkon_convo:addScreen(neg_faction_improve)

-- ========================================
-- Reward Screens (Quest Complete)
-- ========================================

-- Quest 1 Reward
excellent_work = ConvoScreen:new {
	id = "excellent_work",
	leftDialog = "@conversation/corellia_rebel_tier4:s_f95cd5f5", -- Mission accomplished! And you know what that means.
	animation = "applause_excited",
	stopConversation = "false",
	options = {
		{"@conversation/corellia_rebel_tier4:s_6f679fea", "reward_m1_explain"}, -- What does it mean?
	}
}
arkon_convo:addScreen(excellent_work)

reward_m1_explain = ConvoScreen:new {
	id = "reward_m1_explain",
	leftDialog = "@conversation/corellia_rebel_tier4:s_b4e09e44", -- Duty pay, you nitwit!
	animation = "tap_head",
	stopConversation = "true",
	options = {}
}
arkon_convo:addScreen(reward_m1_explain)

-- Quest 2 Reward
excellent_work2 = ConvoScreen:new {
	id = "excellent_work2",
	leftDialog = "@conversation/corellia_rebel_tier4:s_da8e9da5", -- See? You could save the day after all! Not bad.
	animation = "shrug_hands",
	stopConversation = "false",
	options = {
		{"@conversation/corellia_rebel_tier4:s_def742", "ready_train_pilot"}, -- You were right.
		{"@conversation/corellia_rebel_tier4:s_b20c71fe", "reward_m2_explain"}, -- It wasn't easy.
	}
}
arkon_convo:addScreen(excellent_work2)

reward_m2_explain = ConvoScreen:new {
	id = "reward_m2_explain",
	leftDialog = "@conversation/corellia_rebel_tier4:s_868699d3", -- I don't give my pilots easy missions. But I DO pay them well.
	animation = "snap_finger1",
	playerAnimation = "shake_head_no",
	stopConversation = "false",
	options = {
		{"@conversation/corellia_rebel_tier4:s_def742", "ready_train_pilot"}, -- You were right.
	}
}
arkon_convo:addScreen(reward_m2_explain)

-- Quest 3 Reward
excellent_work3 = ConvoScreen:new {
	id = "excellent_work3",
	leftDialog = "@conversation/corellia_rebel_tier4:s_10d8bf69", -- I salute you, Rebel!
	animation = "salute1",
	stopConversation = "false",
	options = {
		{"@conversation/corellia_rebel_tier4:s_aed5139a", "reward_m3_humble"}, -- No need for that.
		{"@conversation/corellia_rebel_tier4:s_cb6eb294", "reward_m3_shucks"}, -- Aw shucks.
	}
}
arkon_convo:addScreen(excellent_work3)

reward_m3_humble = ConvoScreen:new {
	id = "reward_m3_humble",
	leftDialog = "@conversation/corellia_rebel_tier4:s_9a4a59e0", -- Maybe you just want your duty pay.
	animation = "rub_chin_thoughtful",
	playerAnimation = "embarrassed",
	stopConversation = "false",
	options = {
		{"@conversation/corellia_rebel_tier4:s_f60b81f8", "ready_train_pilot"}, -- That's fine.
	}
}
arkon_convo:addScreen(reward_m3_humble)

reward_m3_shucks = ConvoScreen:new {
	id = "reward_m3_shucks",
	leftDialog = "@conversation/corellia_rebel_tier4:s_e3653d50", -- Here's your duty pay! You've earned it.
	stopConversation = "false",
	options = {
		{"@conversation/corellia_rebel_tier4:s_fc27931b", "ready_train_pilot"}, -- Thanks.
	}
}
arkon_convo:addScreen(reward_m3_shucks)

-- Quest 4 Reward
excellent_work4 = ConvoScreen:new {
	id = "excellent_work4",
	leftDialog = "@conversation/corellia_rebel_tier4:s_81e25d24", -- You showed them! Let's see the Empire try to build a station in THIS system!
	animation = "laugh",
	stopConversation = "false",
	options = {
		{"@conversation/corellia_rebel_tier4:s_61485366", "ready_train_pilot"}, -- It's not going to happen anytime soon.
		{"@conversation/corellia_rebel_tier4:s_197c8928", "reward_m4_serve"}, -- Happy to serve.
	}
}
arkon_convo:addScreen(excellent_work4)

reward_m4_serve = ConvoScreen:new {
	id = "reward_m4_serve",
	leftDialog = "@conversation/corellia_rebel_tier4:s_4c97efb1", -- And I'm happy to give you your duty pay, junior!
	animation = "salute1",
	stopConversation = "false",
	options = {
		{"@conversation/corellia_rebel_tier4:s_61485366", "ready_train_pilot"}, -- It's not going to happen anytime soon.
	}
}
arkon_convo:addScreen(reward_m4_serve)

-- ========================================
-- Skill Training
-- ========================================

-- Training Menu (dynamic options added by handler based on missing skills)
ready_train_pilot = ConvoScreen:new {
	id = "ready_train_pilot",
	leftDialog = "@conversation/corellia_rebel_tier4:s_8907c99", -- Hey! You! You're still pretty wet behind the ears... Which one would you like?
	animation = "beckon",
	stopConversation = "false",
	options = {}
}
arkon_convo:addScreen(ready_train_pilot)

-- Per-phase training terminal screens (skill granted by handler)
-- Initial phase (before quest 1)
initial_train_fighters = ConvoScreen:new {
	id = "initial_train_fighters",
	leftDialog = "@conversation/corellia_rebel_tier4:s_66d4c0f2", -- You don't have to shout! I've never seen anybody so excited about starships.
	stopConversation = "true",
	options = {}
}
arkon_convo:addScreen(initial_train_fighters)

initial_train_components = ConvoScreen:new {
	id = "initial_train_components",
	leftDialog = "@conversation/corellia_rebel_tier4:s_62c873d4", -- Are you sure? Well too late it's yours now!... for a NERF-HERDER!
	stopConversation = "true",
	options = {}
}
arkon_convo:addScreen(initial_train_components)

initial_train_procedures = ConvoScreen:new {
	id = "initial_train_procedures",
	leftDialog = "@conversation/corellia_rebel_tier4:s_ba9df4a6", -- Oh all right. Here you go. Now go away and stop bothering me.
	stopConversation = "true",
	options = {}
}
arkon_convo:addScreen(initial_train_procedures)

initial_train_droid = ConvoScreen:new {
	id = "initial_train_droid",
	leftDialog = "@conversation/corellia_rebel_tier4:s_11769c29", -- Sure! I wasn't ALWAYS an old man... Now go on; get out of here.
	animation = "giveup",
	stopConversation = "true",
	options = {}
}
arkon_convo:addScreen(initial_train_droid)

-- Mission 2 phase (after quest 1 complete)
mission2_train_fighters = ConvoScreen:new {
	id = "mission2_train_fighters",
	leftDialog = "@conversation/corellia_rebel_tier4:s_66d4c0f2",
	stopConversation = "true",
	options = {}
}
arkon_convo:addScreen(mission2_train_fighters)

mission2_train_components = ConvoScreen:new {
	id = "mission2_train_components",
	leftDialog = "@conversation/corellia_rebel_tier4:s_62c873d4",
	stopConversation = "true",
	options = {}
}
arkon_convo:addScreen(mission2_train_components)

mission2_train_procedures = ConvoScreen:new {
	id = "mission2_train_procedures",
	leftDialog = "@conversation/corellia_rebel_tier4:s_ba9df4a6",
	stopConversation = "true",
	options = {}
}
arkon_convo:addScreen(mission2_train_procedures)

mission2_train_droid = ConvoScreen:new {
	id = "mission2_train_droid",
	leftDialog = "@conversation/corellia_rebel_tier4:s_11769c29",
	animation = "giveup",
	stopConversation = "true",
	options = {}
}
arkon_convo:addScreen(mission2_train_droid)

-- Mission 3 phase (after quest 2 complete)
mission3_train_fighters = ConvoScreen:new {
	id = "mission3_train_fighters",
	leftDialog = "@conversation/corellia_rebel_tier4:s_66d4c0f2",
	stopConversation = "true",
	options = {}
}
arkon_convo:addScreen(mission3_train_fighters)

mission3_train_components = ConvoScreen:new {
	id = "mission3_train_components",
	leftDialog = "@conversation/corellia_rebel_tier4:s_62c873d4",
	stopConversation = "true",
	options = {}
}
arkon_convo:addScreen(mission3_train_components)

mission3_train_procedures = ConvoScreen:new {
	id = "mission3_train_procedures",
	leftDialog = "@conversation/corellia_rebel_tier4:s_ba9df4a6",
	stopConversation = "true",
	options = {}
}
arkon_convo:addScreen(mission3_train_procedures)

mission3_train_droid = ConvoScreen:new {
	id = "mission3_train_droid",
	leftDialog = "@conversation/corellia_rebel_tier4:s_11769c29",
	animation = "giveup",
	stopConversation = "true",
	options = {}
}
arkon_convo:addScreen(mission3_train_droid)

-- Mission 4 phase (after quest 3 complete)
mission4_train_fighters = ConvoScreen:new {
	id = "mission4_train_fighters",
	leftDialog = "@conversation/corellia_rebel_tier4:s_66d4c0f2",
	stopConversation = "true",
	options = {}
}
arkon_convo:addScreen(mission4_train_fighters)

mission4_train_components = ConvoScreen:new {
	id = "mission4_train_components",
	leftDialog = "@conversation/corellia_rebel_tier4:s_62c873d4",
	stopConversation = "true",
	options = {}
}
arkon_convo:addScreen(mission4_train_components)

mission4_train_procedures = ConvoScreen:new {
	id = "mission4_train_procedures",
	leftDialog = "@conversation/corellia_rebel_tier4:s_ba9df4a6",
	stopConversation = "true",
	options = {}
}
arkon_convo:addScreen(mission4_train_procedures)

mission4_train_droid = ConvoScreen:new {
	id = "mission4_train_droid",
	leftDialog = "@conversation/corellia_rebel_tier4:s_11769c29",
	animation = "giveup",
	stopConversation = "true",
	options = {}
}
arkon_convo:addScreen(mission4_train_droid)

-- Final phase (after quest 4 complete, last skill)
final_train_fighters = ConvoScreen:new {
	id = "final_train_fighters",
	leftDialog = "@conversation/corellia_rebel_tier4:s_66d4c0f2",
	stopConversation = "true",
	options = {}
}
arkon_convo:addScreen(final_train_fighters)

final_train_components = ConvoScreen:new {
	id = "final_train_components",
	leftDialog = "@conversation/corellia_rebel_tier4:s_62c873d4",
	stopConversation = "true",
	options = {}
}
arkon_convo:addScreen(final_train_components)

final_train_procedures = ConvoScreen:new {
	id = "final_train_procedures",
	leftDialog = "@conversation/corellia_rebel_tier4:s_ba9df4a6",
	stopConversation = "true",
	options = {}
}
arkon_convo:addScreen(final_train_procedures)

final_train_droid = ConvoScreen:new {
	id = "final_train_droid",
	leftDialog = "@conversation/corellia_rebel_tier4:s_11769c29",
	animation = "giveup",
	stopConversation = "true",
	options = {}
}
arkon_convo:addScreen(final_train_droid)

-- ========================================
-- Failed Quest Screens
-- ========================================

-- Failed Quest 1
failed_quest1 = ConvoScreen:new {
	id = "failed_quest1",
	leftDialog = "@conversation/corellia_rebel_tier4:s_4f755af2", -- In my day, a pilot would NEVER leave a job unfinished!
	animation = "gesticulate_wildly",
	stopConversation = "false",
	options = {
		{"@conversation/corellia_rebel_tier4:s_8f3b3edb", "retry_quest1_a"}, -- I'm not done yet!
		{"@conversation/corellia_rebel_tier4:s_88563b84", "retry_quest1_b"}, -- I'm ashamed.
	}
}
arkon_convo:addScreen(failed_quest1)

retry_quest1_a = ConvoScreen:new {
	id = "retry_quest1_a",
	leftDialog = "@conversation/corellia_rebel_tier4:s_76c0ae11", -- Hurry up! There's no time to waste!
	animation = "wave_finger_warning",
	stopConversation = "true",
	options = {}
}
arkon_convo:addScreen(retry_quest1_a)

retry_quest1_b = ConvoScreen:new {
	id = "retry_quest1_b",
	leftDialog = "@conversation/corellia_rebel_tier4:s_fa6bfaff", -- Oh. I didn't mean to upset you! ...try again!
	animation = "offer_affection",
	playerAnimation = "embarrassed",
	stopConversation = "true",
	options = {}
}
arkon_convo:addScreen(retry_quest1_b)

-- Failed Quest 2
failed_quest2 = ConvoScreen:new {
	id = "failed_quest2",
	leftDialog = "@conversation/corellia_rebel_tier4:s_1909d363", -- You've got to get back out there...
	animation = "stamp_feet",
	stopConversation = "false",
	options = {
		{"@conversation/corellia_rebel_tier4:s_87d7e908", "retry_quest2_a"}, -- I know.
		{"@conversation/corellia_rebel_tier4:s_e42b260e", "retry_quest2_b"}, -- I'm on my way.
	}
}
arkon_convo:addScreen(failed_quest2)

retry_quest2_a = ConvoScreen:new {
	id = "retry_quest2_a",
	leftDialog = "@conversation/corellia_rebel_tier4:s_16e3e795", -- Your ship is waiting. Watch your back.
	animation = "wave_finger_warning",
	stopConversation = "true",
	options = {}
}
arkon_convo:addScreen(retry_quest2_a)

retry_quest2_b = ConvoScreen:new {
	id = "retry_quest2_b",
	leftDialog = "@conversation/corellia_rebel_tier4:s_13835aab", -- You don't have much time.
	animation = "check_wrist_device",
	stopConversation = "true",
	options = {}
}
arkon_convo:addScreen(retry_quest2_b)

-- Failed Quest 3
failed_quest3 = ConvoScreen:new {
	id = "failed_quest3",
	leftDialog = "@conversation/corellia_rebel_tier4:s_d3d98e75", -- That was a complete disaster!
	animation = "smack_self",
	stopConversation = "false",
	options = {
		{"@conversation/corellia_rebel_tier4:s_e30b9697", "retry_quest3_a"}, -- Hey, things don't always turn out right!
		{"@conversation/corellia_rebel_tier4:s_10eafe13", "retry_quest3_b"}, -- I'm not done yet!
	}
}
arkon_convo:addScreen(failed_quest3)

retry_quest3_a = ConvoScreen:new {
	id = "retry_quest3_a",
	leftDialog = "@conversation/corellia_rebel_tier4:s_f5d1e7f4", -- Don't sass me, junior!...
	animation = "wave_finger_warning",
	stopConversation = "true",
	options = {}
}
arkon_convo:addScreen(retry_quest3_a)

retry_quest3_b = ConvoScreen:new {
	id = "retry_quest3_b",
	leftDialog = "@conversation/corellia_rebel_tier4:s_42b12fa4", -- I should hope not! Good grief!
	stopConversation = "true",
	options = {}
}
arkon_convo:addScreen(retry_quest3_b)

-- Failed Quest 4
failed_quest4 = ConvoScreen:new {
	id = "failed_quest4",
	leftDialog = "@conversation/corellia_rebel_tier4:s_78b8ac8f", -- Oh what is THIS. I told you to take out those freighters!
	animation = "gesticulate_wildly",
	stopConversation = "false",
	options = {
		{"@conversation/corellia_rebel_tier4:s_4dd9a7b9", "retry_quest4_a"}, -- Those ships have guns!
		{"@conversation/corellia_rebel_tier4:s_35dd4aa2", "retry_quest4_b"}, -- Yes, I know!
	}
}
arkon_convo:addScreen(failed_quest4)

retry_quest4_a = ConvoScreen:new {
	id = "retry_quest4_a",
	leftDialog = "@conversation/corellia_rebel_tier4:s_2eec3c3b", -- YOUR ship has guns! Start using them!
	animation = "stamp_feet",
	stopConversation = "true",
	options = {}
}
arkon_convo:addScreen(retry_quest4_a)

retry_quest4_b = ConvoScreen:new {
	id = "retry_quest4_b",
	leftDialog = "@conversation/corellia_rebel_tier4:s_6561f20e", -- Well then why aren't you DOING it? Get back out there!
	animation = "implore",
	stopConversation = "true",
	options = {}
}
arkon_convo:addScreen(retry_quest4_b)

-- ========================================
-- Quest 1: Survival Mission (Black Sun Assault - Dathomir)
-- ========================================

-- Quest 1 Briefing Entry
first_mission = ConvoScreen:new {
	id = "first_mission",
	leftDialog = "@conversation/corellia_rebel_tier4:s_5bf6779f", -- OK %NU, let's talk business! This situation is SERIOUS!
	animation = "pound_fist_palm",
	stopConversation = "false",
	options = {
		{"@conversation/corellia_rebel_tier4:s_3609c810", "quest1_serious"}, -- It is?
		{"@conversation/corellia_rebel_tier4:s_3c546115", "quest1_dismiss"}, -- Some other time? I'm really busy!
		{"@conversation/corellia_rebel_tier4:s_ef3e641a", "quest1_pirate"}, -- I'm here to help.
	}
}
arkon_convo:addScreen(first_mission)

-- Quest 1 Dismiss
quest1_dismiss = ConvoScreen:new {
	id = "quest1_dismiss",
	leftDialog = "@conversation/corellia_rebel_tier4:s_9be0e2f1", -- What? You worthless bum! Fine! See if I ever try to give you a mission again!
	animation = "wave_on_dismissing",
	stopConversation = "true",
	options = {}
}
arkon_convo:addScreen(quest1_dismiss)

-- PATH A: "It is?"
quest1_serious = ConvoScreen:new {
	id = "quest1_serious",
	leftDialog = "@conversation/corellia_rebel_tier4:s_99069e90", -- YES! It's ALWAYS serious when we're talking about Imperials!
	animation = "explain",
	stopConversation = "false",
	options = {
		{"@conversation/corellia_rebel_tier4:s_6318beeb", "quest1_situation"}, -- What's the situation?
	}
}
arkon_convo:addScreen(quest1_serious)

quest1_situation = ConvoScreen:new {
	id = "quest1_situation",
	leftDialog = "@conversation/corellia_rebel_tier4:s_d98a6441", -- Apparently, the Black Suns are preparing to launch an assault on one of our mining interests in the Dathomir system.
	stopConversation = "false",
	options = {
		{"@conversation/corellia_rebel_tier4:s_d566a3c", "quest1_empire"}, -- And how are the Imperials involved?
		{"@conversation/corellia_rebel_tier4:s_f35bbdbd", "quest1_mining"}, -- Mining interests? You make it sound almost legitimate.
	}
}
arkon_convo:addScreen(quest1_situation)

-- PATH A1: "And how are the Imperials involved?"
quest1_empire = ConvoScreen:new {
	id = "quest1_empire",
	leftDialog = "@conversation/corellia_rebel_tier4:s_50669846", -- Apparently, the Empire's had just about enough of our activities in the area...
	stopConversation = "false",
	options = {
		{"@conversation/corellia_rebel_tier4:s_53544796", "quest1_miners_a"}, -- Sounds like a problem.
	}
}
arkon_convo:addScreen(quest1_empire)

quest1_miners_a = ConvoScreen:new {
	id = "quest1_miners_a",
	leftDialog = "@conversation/corellia_rebel_tier4:s_9f50a13", -- Back to those poor miners. They're outgunned...
	stopConversation = "false",
	options = {
		{"@conversation/corellia_rebel_tier4:s_f5cc7cf3", "quest1_defend_a"}, -- Can't the vessels defend themselves?
	}
}
arkon_convo:addScreen(quest1_miners_a)

quest1_defend_a = ConvoScreen:new {
	id = "quest1_defend_a",
	leftDialog = "@conversation/corellia_rebel_tier4:s_526ce515", -- Negative! They outgun YOU, too. Don't try to blast them to smithereens...
	animation = "wave_finger_warning",
	stopConversation = "false",
	options = {
		{"@conversation/corellia_rebel_tier4:s_410d920c", "accept_quest1_a"}, -- Alright, let's do this!
	}
}
arkon_convo:addScreen(quest1_defend_a)

accept_quest1_a = ConvoScreen:new {
	id = "accept_quest1_a",
	leftDialog = "@conversation/corellia_rebel_tier4:s_a434ad25", -- One more thing Rebel. All the missions I provide you with will be high risk missions...
	animation = "dismiss",
	stopConversation = "true",
	options = {}
}
arkon_convo:addScreen(accept_quest1_a)

-- PATH A2: "Mining interests?"
quest1_mining = ConvoScreen:new {
	id = "quest1_mining",
	leftDialog = "@conversation/corellia_rebel_tier4:s_f5e4dcb6", -- Stop talking and start listening!... The Black Suns are preparing to launch an assault on one of our mining interests.
	animation = "gesticulate_wildly",
	stopConversation = "false",
	options = {
		{"@conversation/corellia_rebel_tier4:s_9d0a2207", "quest1_outgunned_b"}, -- Should I target the Black Suns directly?
	}
}
arkon_convo:addScreen(quest1_mining)

quest1_outgunned_b = ConvoScreen:new {
	id = "quest1_outgunned_b",
	leftDialog = "@conversation/corellia_rebel_tier4:s_526ce515", -- Negative! They outgun YOU, too...
	animation = "wave_finger_warning",
	stopConversation = "false",
	options = {
		{"@conversation/corellia_rebel_tier4:s_c2bbb747", "quest1_follow_b"}, -- Fine by me.
	}
}
arkon_convo:addScreen(quest1_outgunned_b)

quest1_follow_b = ConvoScreen:new {
	id = "quest1_follow_b",
	leftDialog = "@conversation/corellia_rebel_tier4:s_1bb2f893", -- They're using my men because they know every inch of Dathomir space...
	stopConversation = "false",
	options = {
		{"@conversation/corellia_rebel_tier4:s_7065a3b", "accept_quest1_b"}, -- Great.
	}
}
arkon_convo:addScreen(quest1_follow_b)

accept_quest1_b = ConvoScreen:new {
	id = "accept_quest1_b",
	leftDialog = "@conversation/corellia_rebel_tier4:s_a434ad25", -- One more thing Rebel. All the missions I provide you with will be high risk missions...
	animation = "dismiss",
	stopConversation = "true",
	options = {}
}
arkon_convo:addScreen(accept_quest1_b)

-- PATH C: "I'm here to help."
quest1_pirate = ConvoScreen:new {
	id = "quest1_pirate",
	leftDialog = "@conversation/corellia_rebel_tier4:s_e380bbf8", -- So you are! I hope you don't mind helping pirates.
	stopConversation = "false",
	options = {
		{"@conversation/corellia_rebel_tier4:s_2a5d0bf1", "quest1_criminal_c"}, -- They're criminals.
	}
}
arkon_convo:addScreen(quest1_pirate)

quest1_criminal_c = ConvoScreen:new {
	id = "quest1_criminal_c",
	leftDialog = "@conversation/corellia_rebel_tier4:s_d79718db", -- And pirates are criminals.
	stopConversation = "false",
	options = {
		{"@conversation/corellia_rebel_tier4:s_dfc39325", "quest1_partner_c"}, -- So are you, according to the Empire.
	}
}
arkon_convo:addScreen(quest1_criminal_c)

quest1_partner_c = ConvoScreen:new {
	id = "quest1_partner_c",
	leftDialog = "@conversation/corellia_rebel_tier4:s_f51574ed", -- Haha! Good point. Well then I'm a criminal. And you're going to help me...
	animation = "laugh",
	stopConversation = "false",
	options = {
		{"@conversation/corellia_rebel_tier4:s_d9cced1f", "quest1_miners_c"}, -- Absolutely.
	}
}
arkon_convo:addScreen(quest1_partner_c)

quest1_miners_c = ConvoScreen:new {
	id = "quest1_miners_c",
	leftDialog = "@conversation/corellia_rebel_tier4:s_2284c46", -- Look, you don't have to like what we do. But those miners aren't hurting anybody...
	stopConversation = "false",
	options = {
		{"@conversation/corellia_rebel_tier4:s_af22b9b2", "accept_quest1_c"}, -- I guess so.
	}
}
arkon_convo:addScreen(quest1_miners_c)

accept_quest1_c = ConvoScreen:new {
	id = "accept_quest1_c",
	leftDialog = "@conversation/corellia_rebel_tier4:s_a434ad25", -- One more thing Rebel. All the missions I provide you with will be high risk missions...
	animation = "dismiss",
	stopConversation = "true",
	options = {}
}
arkon_convo:addScreen(accept_quest1_c)

-- ========================================
-- Quest 2: Assassinate Mission (Inquisitor Intercept - Dathomir)
-- ========================================

-- Quest 2 Briefing Entry
second_mission = ConvoScreen:new {
	id = "second_mission",
	leftDialog = "@conversation/corellia_rebel_tier4:s_1047bc70", -- Nice work out there. You really kicked those guys where it counts. Ready for round two?
	stopConversation = "false",
	options = {
		{"@conversation/corellia_rebel_tier4:s_6adec6b0", "quest2_intel"}, -- Of course!
		{"@conversation/corellia_rebel_tier4:s_dcabe09b", "quest2_dismiss"}, -- Oh, I'm not here for a mission!
		{"@conversation/corellia_rebel_tier4:s_beaf1664", "quest2_nym"}, -- Another errand for Nym?
	}
}
arkon_convo:addScreen(second_mission)

-- Quest 2 Dismiss
quest2_dismiss = ConvoScreen:new {
	id = "quest2_dismiss",
	leftDialog = "@conversation/corellia_rebel_tier4:s_f15aeb5", -- With pilots like you, who needs Imperials?
	animation = "shake_head_disgust",
	stopConversation = "true",
	options = {}
}
arkon_convo:addScreen(quest2_dismiss)

-- PATH A: "Of course!"
quest2_intel = ConvoScreen:new {
	id = "quest2_intel",
	leftDialog = "@conversation/corellia_rebel_tier4:s_d16ee99f", -- Here's the situation. Intel reports that the Emperor is sending an Inquisitor to Dathomir.
	stopConversation = "false",
	options = {
		{"@conversation/corellia_rebel_tier4:s_29544149", "quest2_why"}, -- Then why send an Inquisitor?
	}
}
arkon_convo:addScreen(quest2_intel)

quest2_why = ConvoScreen:new {
	id = "quest2_why",
	leftDialog = "@conversation/corellia_rebel_tier4:s_f59d9106", -- Well, %TU, think about it. The Empire needs to know what the Alliance is planning...
	stopConversation = "false",
	options = {
		{"@conversation/corellia_rebel_tier4:s_7052aaab", "quest2_seen"}, -- I'll take it as it comes.
	}
}
arkon_convo:addScreen(quest2_why)

quest2_seen = ConvoScreen:new {
	id = "quest2_seen",
	leftDialog = "@conversation/corellia_rebel_tier4:s_37e345fe", -- Have you ever seen an Inquisitor up close?
	stopConversation = "false",
	options = {
		{"@conversation/corellia_rebel_tier4:s_eb1c3d4e", "quest2_mortal"}, -- Are you crazy? No one can kill an Inquisitor!
	}
}
arkon_convo:addScreen(quest2_seen)

quest2_mortal = ConvoScreen:new {
	id = "quest2_mortal",
	leftDialog = "@conversation/corellia_rebel_tier4:s_f3603d67", -- Don't talk back to me, junior!... The Inquisitors are mortal...
	animation = "stamp_feet",
	playerAnimation = "shake_head_no",
	stopConversation = "false",
	options = {
		{"@conversation/corellia_rebel_tier4:s_77633b61", "quest2_notforme"}, -- Easy for you to say. They're not gunning for you.
	}
}
arkon_convo:addScreen(quest2_mortal)

quest2_notforme = ConvoScreen:new {
	id = "quest2_notforme",
	leftDialog = "@conversation/corellia_rebel_tier4:s_a64a6f6f", -- They're not gunning for YOU either, junior!... I've got a mission for you.
	animation = "explain",
	stopConversation = "false",
	options = {
		{"@conversation/corellia_rebel_tier4:s_99d3b4fd", "accept_quest2_a"}, -- What have you got for me?
	}
}
arkon_convo:addScreen(quest2_notforme)

accept_quest2_a = ConvoScreen:new {
	id = "accept_quest2_a",
	leftDialog = "@conversation/corellia_rebel_tier4:s_abf08a18", -- Check your ship's computer. All the information you need is there. Good luck.
	animation = "dismiss",
	stopConversation = "true",
	options = {}
}
arkon_convo:addScreen(accept_quest2_a)

-- PATH C: "Another errand for Nym?"
quest2_nym = ConvoScreen:new {
	id = "quest2_nym",
	leftDialog = "@conversation/corellia_rebel_tier4:s_87e30fff", -- Not this time, my grumpy friend. This time, you'll be helping your beloved Rebellion.
	stopConversation = "false",
	options = {
		{"@conversation/corellia_rebel_tier4:s_96bfa401", "quest2_money"}, -- Not at all - if it helps the Rebellion.
	}
}
arkon_convo:addScreen(quest2_nym)

quest2_money = ConvoScreen:new {
	id = "quest2_money",
	leftDialog = "@conversation/corellia_rebel_tier4:s_3b361a5f", -- You should think about leaving the Alliance and working for Nym! You'll make more money.
	stopConversation = "false",
	options = {
		{"@conversation/corellia_rebel_tier4:s_7fca522a", "quest2_future"}, -- ...will I quit the Rebellion and start working for Nym full time? Forget it.
	}
}
arkon_convo:addScreen(quest2_money)

quest2_future = ConvoScreen:new {
	id = "quest2_future",
	leftDialog = "@conversation/corellia_rebel_tier4:s_a04dd423", -- Think of your future, junior! Someday you'll be a crazy old man like me...
	stopConversation = "false",
	options = {
		{"@conversation/corellia_rebel_tier4:s_8fc8c755", "quest2_intel_c"}, -- What?...Never mind. Do you have a mission for me?
	}
}
arkon_convo:addScreen(quest2_future)

quest2_intel_c = ConvoScreen:new {
	id = "quest2_intel_c",
	leftDialog = "@conversation/corellia_rebel_tier4:s_8b4d636d", -- Intel reports that the Emperor is sending an Inquisitor to Dathomir.
	stopConversation = "false",
	options = {
		{"@conversation/corellia_rebel_tier4:s_29544149", "quest2_why_c"}, -- Then why send an Inquisitor?
	}
}
arkon_convo:addScreen(quest2_intel_c)

quest2_why_c = ConvoScreen:new {
	id = "quest2_why_c",
	leftDialog = "@conversation/corellia_rebel_tier4:s_f59d9106", -- Well, %TU, think about it. The Empire needs to know what the Alliance is planning...
	stopConversation = "false",
	options = {
		{"@conversation/corellia_rebel_tier4:s_b045a378", "quest2_seen_c"}, -- Touche.
	}
}
arkon_convo:addScreen(quest2_why_c)

quest2_seen_c = ConvoScreen:new {
	id = "quest2_seen_c",
	leftDialog = "@conversation/corellia_rebel_tier4:s_37e345fe", -- Have you ever seen an Inquisitor up close?
	stopConversation = "false",
	options = {
		{"@conversation/corellia_rebel_tier4:s_eb1c3d4e", "quest2_mortal_c"}, -- Are you crazy? No one can kill an Inquisitor!
	}
}
arkon_convo:addScreen(quest2_seen_c)

quest2_mortal_c = ConvoScreen:new {
	id = "quest2_mortal_c",
	leftDialog = "@conversation/corellia_rebel_tier4:s_f3603d67", -- Don't talk back to me, junior!... The Inquisitors are mortal...
	animation = "stamp_feet",
	playerAnimation = "shake_head_no",
	stopConversation = "false",
	options = {
		{"@conversation/corellia_rebel_tier4:s_77633b61", "quest2_notforme_c"}, -- Easy for you to say. They're not gunning for you.
	}
}
arkon_convo:addScreen(quest2_mortal_c)

quest2_notforme_c = ConvoScreen:new {
	id = "quest2_notforme_c",
	leftDialog = "@conversation/corellia_rebel_tier4:s_a64a6f6f", -- They're not gunning for YOU either, junior!... I've got a mission for you.
	animation = "explain",
	stopConversation = "false",
	options = {
		{"@conversation/corellia_rebel_tier4:s_99d3b4fd", "accept_quest2_b"}, -- What have you got for me?
	}
}
arkon_convo:addScreen(quest2_notforme_c)

accept_quest2_b = ConvoScreen:new {
	id = "accept_quest2_b",
	leftDialog = "@conversation/corellia_rebel_tier4:s_abf08a18", -- Check your ship's computer. All the information you need is there. Good luck.
	animation = "dismiss",
	stopConversation = "true",
	options = {}
}
arkon_convo:addScreen(accept_quest2_b)

-- ========================================
-- Quest 3: Space Battle Mission (Imperial Base Strike - Dathomir)
-- ========================================

-- Quest 3 Briefing Entry
third_mission = ConvoScreen:new {
	id = "third_mission",
	leftDialog = "@conversation/corellia_rebel_tier4:s_e8f374d9", -- Hey Rebel! I've got a new assignment for you.
	animation = "beckon",
	stopConversation = "false",
	options = {
		{"@conversation/corellia_rebel_tier4:s_1c8bddbb", "quest3_please"}, -- What is it?
		{"@conversation/corellia_rebel_tier4:s_f48fdfbd", "quest3_dismiss"}, -- Ship's in the shop.
		{"@conversation/corellia_rebel_tier4:s_1551b284", "quest3_something"}, -- Something good?
		{"@conversation/corellia_rebel_tier4:s_60080304", "quest3_noinquisitor"}, -- Not another Inquisitor assignment, I hope.
	}
}
arkon_convo:addScreen(third_mission)

-- Quest 3 Dismiss
quest3_dismiss = ConvoScreen:new {
	id = "quest3_dismiss",
	leftDialog = "@conversation/corellia_rebel_tier4:s_1af32f06", -- Likely story. Why don't you just tell me that your dog ate your blasters?
	animation = "shake_head_disgust",
	stopConversation = "true",
	options = {}
}
arkon_convo:addScreen(quest3_dismiss)

-- PATH A: "What is it?"
quest3_please = ConvoScreen:new {
	id = "quest3_please",
	leftDialog = "@conversation/corellia_rebel_tier4:s_7d2fc507", -- Say please!
	stopConversation = "false",
	options = {
		{"@conversation/corellia_rebel_tier4:s_3b95cf2f", "quest3_question"}, -- I said, 'What is it?'!
	}
}
arkon_convo:addScreen(quest3_please)

quest3_question = ConvoScreen:new {
	id = "quest3_question",
	leftDialog = "@conversation/corellia_rebel_tier4:s_ff9fae78", -- What kind of question is that?
	stopConversation = "false",
	options = {
		{"@conversation/corellia_rebel_tier4:s_900f01d1", "quest3_whatever"}, -- What?
	}
}
arkon_convo:addScreen(quest3_question)

quest3_whatever = ConvoScreen:new {
	id = "quest3_whatever",
	leftDialog = "@conversation/corellia_rebel_tier4:s_cbcfe001", -- Well, whatever! You know what I mean. Don't be obstinate, junior!
	stopConversation = "false",
	options = {
		{"@conversation/corellia_rebel_tier4:s_99d3b4fd", "quest3_dathomir_a"}, -- What have you got for me?
	}
}
arkon_convo:addScreen(quest3_whatever)

quest3_dathomir_a = ConvoScreen:new {
	id = "quest3_dathomir_a",
	leftDialog = "@conversation/corellia_rebel_tier4:s_ccac6a71", -- You're going to Dathomir. I want you to join some of my men on a guerilla strike against an Imperial base.
	stopConversation = "false",
	options = {
		{"@conversation/corellia_rebel_tier4:s_f50be00f", "quest3_bwing_a"}, -- I like the sound of that!
	}
}
arkon_convo:addScreen(quest3_dathomir_a)

quest3_bwing_a = ConvoScreen:new {
	id = "quest3_bwing_a",
	leftDialog = "@conversation/corellia_rebel_tier4:s_8cac3c56", -- I thought you would! Now you don't have to take the whole base apart. You're just going to pave the way for an Alliance B-Wing squadron.
	stopConversation = "false",
	options = {
		{"@conversation/corellia_rebel_tier4:s_8729f60e", "quest3_route_a"}, -- Smart.
	}
}
arkon_convo:addScreen(quest3_bwing_a)

quest3_route_a = ConvoScreen:new {
	id = "quest3_route_a",
	leftDialog = "@conversation/corellia_rebel_tier4:s_31fd5acf", -- Of course it's smart! It was my idea. Now listen up. Your first objective is to find out what route those Imperial freighters plan to use.
	stopConversation = "false",
	options = {
		{"@conversation/corellia_rebel_tier4:s_a9e4fd02", "accept_quest3_a"}, -- How do I do that?
	}
}
arkon_convo:addScreen(quest3_route_a)

accept_quest3_a = ConvoScreen:new {
	id = "accept_quest3_a",
	leftDialog = "@conversation/corellia_rebel_tier4:s_abf08a18", -- Check your ship's computer. All the information you need is there. Good luck.
	animation = "dismiss",
	stopConversation = "true",
	options = {}
}
arkon_convo:addScreen(accept_quest3_a)

-- PATH C: "Something good?"
quest3_something = ConvoScreen:new {
	id = "quest3_something",
	leftDialog = "@conversation/corellia_rebel_tier4:s_83f72ca3", -- Something that will help the Rebellion. How does that sound to you?
	stopConversation = "false",
	options = {
		{"@conversation/corellia_rebel_tier4:s_eb703128", "quest3_confident"}, -- In that case, I'm listening.
	}
}
arkon_convo:addScreen(quest3_something)

quest3_confident = ConvoScreen:new {
	id = "quest3_confident",
	leftDialog = "@conversation/corellia_rebel_tier4:s_7afc40b8", -- Fine. Well the Alliance is feeling more confident, now that you've terminated that Inquisitor.
	stopConversation = "false",
	options = {
		{"@conversation/corellia_rebel_tier4:s_c55a344e", "quest3_damage"}, -- They'll send another one eventually.
	}
}
arkon_convo:addScreen(quest3_confident)

quest3_damage = ConvoScreen:new {
	id = "quest3_damage",
	leftDialog = "@conversation/corellia_rebel_tier4:s_5e4c5d9a", -- And now we have the chance to REALLY do some damage. And that's where you come in.
	stopConversation = "false",
	options = {
		{"@conversation/corellia_rebel_tier4:s_d1be90a9", "quest3_dathomir_c"}, -- What's the plan?
	}
}
arkon_convo:addScreen(quest3_damage)

quest3_dathomir_c = ConvoScreen:new {
	id = "quest3_dathomir_c",
	leftDialog = "@conversation/corellia_rebel_tier4:s_a6e1a5f4", -- That's because it's top secret!... You're going to Dathomir. I want you to join some of my men on a guerilla strike against an Imperial base.
	stopConversation = "false",
	options = {
		{"@conversation/corellia_rebel_tier4:s_f50be00f", "quest3_bwing_c"}, -- I like the sound of that!
	}
}
arkon_convo:addScreen(quest3_dathomir_c)

quest3_bwing_c = ConvoScreen:new {
	id = "quest3_bwing_c",
	leftDialog = "@conversation/corellia_rebel_tier4:s_8cac3c56", -- I thought you would!... pave the way for an Alliance B-Wing squadron.
	stopConversation = "false",
	options = {
		{"@conversation/corellia_rebel_tier4:s_8729f60e", "quest3_route_c"}, -- Smart.
	}
}
arkon_convo:addScreen(quest3_bwing_c)

quest3_route_c = ConvoScreen:new {
	id = "quest3_route_c",
	leftDialog = "@conversation/corellia_rebel_tier4:s_31fd5acf", -- Of course it's smart!... find out what route those Imperial freighters plan to use.
	stopConversation = "false",
	options = {
		{"@conversation/corellia_rebel_tier4:s_a9e4fd02", "accept_quest3_b"}, -- How do I do that?
	}
}
arkon_convo:addScreen(quest3_route_c)

accept_quest3_b = ConvoScreen:new {
	id = "accept_quest3_b",
	leftDialog = "@conversation/corellia_rebel_tier4:s_abf08a18", -- Check your ship's computer. All the information you need is there. Good luck.
	animation = "dismiss",
	stopConversation = "true",
	options = {}
}
arkon_convo:addScreen(accept_quest3_b)

-- PATH D: "Not another Inquisitor assignment..."
quest3_noinquisitor = ConvoScreen:new {
	id = "quest3_noinquisitor",
	leftDialog = "@conversation/corellia_rebel_tier4:s_7da3fc7a", -- No. Those don't come along very often.
	stopConversation = "false",
	options = {
		{"@conversation/corellia_rebel_tier4:s_7ce1c24", "quest3_dontlike"}, -- [exhale loudly]
	}
}
arkon_convo:addScreen(quest3_noinquisitor)

quest3_dontlike = ConvoScreen:new {
	id = "quest3_dontlike",
	leftDialog = "@conversation/corellia_rebel_tier4:s_d054f893", -- I don't like targeting Inquisitors. You want to know why?
	stopConversation = "false",
	options = {
		{"@conversation/corellia_rebel_tier4:s_841d27db", "quest3_angryatme"}, -- Why?
	}
}
arkon_convo:addScreen(quest3_dontlike)

quest3_angryatme = ConvoScreen:new {
	id = "quest3_angryatme",
	leftDialog = "@conversation/corellia_rebel_tier4:s_b45dc260", -- Because it makes another Inquisitors angry - angry at ME. And that's trouble I don't need.
	stopConversation = "false",
	options = {
		{"@conversation/corellia_rebel_tier4:s_997f2d21", "quest3_nevermind"}, -- But you said...
	}
}
arkon_convo:addScreen(quest3_angryatme)

quest3_nevermind = ConvoScreen:new {
	id = "quest3_nevermind",
	leftDialog = "@conversation/corellia_rebel_tier4:s_d06c9b96", -- Even I don't know what the Alliance has planned.
	stopConversation = "false",
	options = {
		{"@conversation/corellia_rebel_tier4:s_99d3b4fd", "quest3_dathomir_d"}, -- What have you got for me?
	}
}
arkon_convo:addScreen(quest3_nevermind)

quest3_dathomir_d = ConvoScreen:new {
	id = "quest3_dathomir_d",
	leftDialog = "@conversation/corellia_rebel_tier4:s_ccac6a71", -- You're going to Dathomir... guerilla strike against an Imperial base.
	stopConversation = "false",
	options = {
		{"@conversation/corellia_rebel_tier4:s_f50be00f", "quest3_bwing_d"}, -- I like the sound of that!
	}
}
arkon_convo:addScreen(quest3_dathomir_d)

quest3_bwing_d = ConvoScreen:new {
	id = "quest3_bwing_d",
	leftDialog = "@conversation/corellia_rebel_tier4:s_8cac3c56", -- I thought you would!... pave the way for B-Wing squadron.
	stopConversation = "false",
	options = {
		{"@conversation/corellia_rebel_tier4:s_8729f60e", "quest3_route_d"}, -- Smart.
	}
}
arkon_convo:addScreen(quest3_bwing_d)

quest3_route_d = ConvoScreen:new {
	id = "quest3_route_d",
	leftDialog = "@conversation/corellia_rebel_tier4:s_31fd5acf", -- Of course it's smart!... find out what route...
	stopConversation = "false",
	options = {
		{"@conversation/corellia_rebel_tier4:s_a9e4fd02", "quest3_stealth_d"}, -- How do I do that?
	}
}
arkon_convo:addScreen(quest3_route_d)

quest3_stealth_d = ConvoScreen:new {
	id = "quest3_stealth_d",
	leftDialog = "@conversation/corellia_rebel_tier4:s_268606ba", -- They'll never know it was you.
	stopConversation = "false",
	options = {
		{"@conversation/corellia_rebel_tier4:s_d9cced1f", "accept_quest3_c"}, -- Absolutely.
	}
}
arkon_convo:addScreen(quest3_stealth_d)

accept_quest3_c = ConvoScreen:new {
	id = "accept_quest3_c",
	leftDialog = "@conversation/corellia_rebel_tier4:s_abf08a18", -- Check your ship's computer. All the information you need is there. Good luck.
	animation = "dismiss",
	stopConversation = "true",
	options = {}
}
arkon_convo:addScreen(accept_quest3_c)

-- ========================================
-- Quest 4: Recovery Mission (Space Station - Lok)
-- ========================================

-- Quest 4 Briefing Entry
fourth_mission = ConvoScreen:new {
	id = "fourth_mission",
	leftDialog = "@conversation/corellia_rebel_tier4:s_ceb77d0c", -- We've got the Empire on the run! Let's kick 'em while they're down!
	stopConversation = "false",
	options = {
		{"@conversation/corellia_rebel_tier4:s_5673ded2", "quest4_notrun"}, -- Are they really on the run?
		{"@conversation/corellia_rebel_tier4:s_9976a72", "quest4_dismiss"}, -- Get somebody else to do your dirty work!
		{"@conversation/corellia_rebel_tier4:s_5fe6ae71", "quest4_joke"}, -- Haha! You're joking, right?
	}
}
arkon_convo:addScreen(fourth_mission)

-- Quest 4 Dismiss
quest4_dismiss = ConvoScreen:new {
	id = "quest4_dismiss",
	leftDialog = "@conversation/corellia_rebel_tier4:s_9e3df78d", -- Is it your naptime? Well fine then!
	animation = "shake_head_disgust",
	stopConversation = "true",
	options = {}
}
arkon_convo:addScreen(quest4_dismiss)

-- PATH A: "Are they really on the run?"
quest4_notrun = ConvoScreen:new {
	id = "quest4_notrun",
	leftDialog = "@conversation/corellia_rebel_tier4:s_1c669", -- Well, no. Not exactly. But we've managed to hit them pretty hard lately.
	stopConversation = "false",
	options = {
		{"@conversation/corellia_rebel_tier4:s_2ac3e9a6", "quest4_smart"}, -- The Empire doesn't run.
	}
}
arkon_convo:addScreen(quest4_notrun)

quest4_smart = ConvoScreen:new {
	id = "quest4_smart",
	leftDialog = "@conversation/corellia_rebel_tier4:s_9e1c0119", -- Yes, but the Rebels are being smart. They're deciding to strike now, while the iron is hot.
	stopConversation = "false",
	options = {
		{"@conversation/corellia_rebel_tier4:s_bed0dfe7", "quest4_station"}, -- I like that!
	}
}
arkon_convo:addScreen(quest4_smart)

quest4_station = ConvoScreen:new {
	id = "quest4_station",
	leftDialog = "@conversation/corellia_rebel_tier4:s_e93fce3e", -- You're probably right, %NU. We've received word that they're planning to build a space station in the Lok system.
	stopConversation = "false",
	options = {
		{"@conversation/corellia_rebel_tier4:s_d1be90a9", "quest4_plan"}, -- What's the plan?
	}
}
arkon_convo:addScreen(quest4_station)

quest4_plan = ConvoScreen:new {
	id = "quest4_plan",
	leftDialog = "@conversation/corellia_rebel_tier4:s_b607bb2e", -- Yep. A BIG one. We can't let them build that station. So here's the plan!...
	stopConversation = "false",
	options = {
		{"@conversation/corellia_rebel_tier4:s_cd445db2", "quest4_kidnap"}, -- I like the sound of that.
	}
}
arkon_convo:addScreen(quest4_plan)

quest4_kidnap = ConvoScreen:new {
	id = "quest4_kidnap",
	leftDialog = "@conversation/corellia_rebel_tier4:s_127f2e23", -- You're going to kidnap one of their technical supervisors. He knows the plan...
	stopConversation = "false",
	options = {
		{"@conversation/corellia_rebel_tier4:s_4519dec9", "quest4_crazy"}, -- You are crazy!
	}
}
arkon_convo:addScreen(quest4_kidnap)

quest4_crazy = ConvoScreen:new {
	id = "quest4_crazy",
	leftDialog = "@conversation/corellia_rebel_tier4:s_8762aa6e", -- Crazy like a SQUALL! Don't underestimate me, %TU!...
	animation = "pound_fist_palm",
	stopConversation = "false",
	options = {
		{"@conversation/corellia_rebel_tier4:s_42880861", "accept_quest4_a"}, -- Okay...
	}
}
arkon_convo:addScreen(quest4_crazy)

accept_quest4_a = ConvoScreen:new {
	id = "accept_quest4_a",
	leftDialog = "@conversation/corellia_rebel_tier4:s_abf08a18", -- Check your ship's computer. All the information you need is there. Good luck.
	animation = "dismiss",
	stopConversation = "true",
	options = {}
}
arkon_convo:addScreen(accept_quest4_a)

-- PATH C: "Haha! You're joking, right?"
quest4_joke = ConvoScreen:new {
	id = "quest4_joke",
	leftDialog = "@conversation/corellia_rebel_tier4:s_449db6d4", -- I am! Try and keep up, will you?
	stopConversation = "false",
	options = {
		{"@conversation/corellia_rebel_tier4:s_2ac3e9a6", "quest4_smart_c"}, -- The Empire doesn't run.
	}
}
arkon_convo:addScreen(quest4_joke)

quest4_smart_c = ConvoScreen:new {
	id = "quest4_smart_c",
	leftDialog = "@conversation/corellia_rebel_tier4:s_dbcde2d3", -- And it's paid off. And now we have the chance to REALLY do some damage.
	stopConversation = "false",
	options = {
		{"@conversation/corellia_rebel_tier4:s_d1be90a9", "quest4_station_c"}, -- What's the plan?
	}
}
arkon_convo:addScreen(quest4_smart_c)

quest4_station_c = ConvoScreen:new {
	id = "quest4_station_c",
	leftDialog = "@conversation/corellia_rebel_tier4:s_e93fce3e", -- ...they're planning to build a space station in the Lok system.
	stopConversation = "false",
	options = {
		{"@conversation/corellia_rebel_tier4:s_c3363bcd", "quest4_plan_c"}, -- Uh huh.
	}
}
arkon_convo:addScreen(quest4_station_c)

quest4_plan_c = ConvoScreen:new {
	id = "quest4_plan_c",
	leftDialog = "@conversation/corellia_rebel_tier4:s_b607bb2e", -- Yep. A BIG one. We can't let them build that station...
	stopConversation = "false",
	options = {
		{"@conversation/corellia_rebel_tier4:s_cd445db2", "quest4_kidnap_c"}, -- I like the sound of that.
	}
}
arkon_convo:addScreen(quest4_plan_c)

quest4_kidnap_c = ConvoScreen:new {
	id = "quest4_kidnap_c",
	leftDialog = "@conversation/corellia_rebel_tier4:s_127f2e23", -- You're going to kidnap one of their technical supervisors...
	stopConversation = "false",
	options = {
		{"@conversation/corellia_rebel_tier4:s_4519dec9", "quest4_crazy_c"}, -- You are crazy!
	}
}
arkon_convo:addScreen(quest4_kidnap_c)

quest4_crazy_c = ConvoScreen:new {
	id = "quest4_crazy_c",
	leftDialog = "@conversation/corellia_rebel_tier4:s_8762aa6e", -- Crazy like a SQUALL!...
	animation = "pound_fist_palm",
	stopConversation = "false",
	options = {
		{"@conversation/corellia_rebel_tier4:s_42880861", "quest4_dontworry_c"}, -- Okay...
	}
}
arkon_convo:addScreen(quest4_crazy_c)

quest4_dontworry_c = ConvoScreen:new {
	id = "quest4_dontworry_c",
	leftDialog = "@conversation/corellia_rebel_tier4:s_268606ba", -- They'll never know it was you.
	stopConversation = "false",
	options = {
		{"@conversation/corellia_rebel_tier4:s_d9cced1f", "accept_quest4_b"}, -- Absolutely.
	}
}
arkon_convo:addScreen(quest4_dontworry_c)

accept_quest4_b = ConvoScreen:new {
	id = "accept_quest4_b",
	leftDialog = "@conversation/corellia_rebel_tier4:s_abf08a18", -- Check your ship's computer. All the information you need is there. Good luck.
	animation = "dismiss",
	stopConversation = "true",
	options = {}
}
arkon_convo:addScreen(accept_quest4_b)

-- ========================================
-- Introduction / First Meeting
-- ========================================

-- First meeting entry (default fallback for new players)
introduction = ConvoScreen:new {
	id = "introduction",
	leftDialog = "@conversation/corellia_rebel_tier4:s_71f899d5", -- It's about time you got here, pilot. Suit up.
	stopConversation = "false",
	options = {
		{"@conversation/corellia_rebel_tier4:s_34d61fa3", "intro_arkon"}, -- Um...I don't think we've met.
	}
}
arkon_convo:addScreen(introduction)

intro_arkon = ConvoScreen:new {
	id = "intro_arkon",
	leftDialog = "@conversation/corellia_rebel_tier4:s_450d7208", -- You can call me Arkon. I imagine that Aqzow sent you?
	animation = "slow_down",
	stopConversation = "false",
	options = {
		{"@conversation/corellia_rebel_tier4:s_d70dba34", "intro_unfortunate"}, -- Yes.
	}
}
arkon_convo:addScreen(intro_arkon)

intro_unfortunate = ConvoScreen:new {
	id = "intro_unfortunate",
	leftDialog = "@conversation/corellia_rebel_tier4:s_c384d95e", -- How unfortunate.
	animation = "cover_mouth",
	stopConversation = "false",
	options = {
		{"@conversation/corellia_rebel_tier4:s_2846f47d", "intro_what_said"}, -- Um, yes. Well, I'm here now.
	}
}
arkon_convo:addScreen(intro_unfortunate)

intro_what_said = ConvoScreen:new {
	id = "intro_what_said",
	leftDialog = "@conversation/corellia_rebel_tier4:s_981faf84", -- What did he say about me?
	animation = "tap_foot",
	stopConversation = "false",
	options = {
		{"@conversation/corellia_rebel_tier4:s_8209f997", "intro_spit"}, -- Nothing I can repeat.
	}
}
arkon_convo:addScreen(intro_what_said)

intro_spit = ConvoScreen:new {
	id = "intro_spit",
	leftDialog = "@conversation/corellia_rebel_tier4:s_3dc78ada", -- Sounds like he hasn't changed. Bleh. I spit on him.
	animation = "shake_head_disgust",
	stopConversation = "false",
	options = {
		{"@conversation/corellia_rebel_tier4:s_afc14266", "intro_goody"}, -- Um, OK. Maybe I should just get to work.
	}
}
arkon_convo:addScreen(intro_spit)

intro_goody = ConvoScreen:new {
	id = "intro_goody",
	leftDialog = "@conversation/corellia_rebel_tier4:s_fc6dfba9", -- Are you one of those goody two-shoes Rebels?
	stopConversation = "false",
	options = {
		{"@conversation/corellia_rebel_tier4:s_4057d656", "intro_boring"}, -- As a matter of fact, I do! How did you know that?
		{"@conversation/corellia_rebel_tier4:s_73313039", "intro_smart"}, -- Really, I just want to work.
	}
}
arkon_convo:addScreen(intro_goody)

-- True Believer path
intro_boring = ConvoScreen:new {
	id = "intro_boring",
	leftDialog = "@conversation/corellia_rebel_tier4:s_58e80738", -- True believers are boring.
	stopConversation = "false",
	options = {
		{"@conversation/corellia_rebel_tier4:s_761dd18e", "intro_enlightened"}, -- I'm not in it for the money.
	}
}
arkon_convo:addScreen(intro_boring)

-- Worker path
intro_smart = ConvoScreen:new {
	id = "intro_smart",
	leftDialog = "@conversation/corellia_rebel_tier4:s_b1f1f364", -- We could never hold our own against the Imperials. We needed your guns. And you needed us!
	stopConversation = "false",
	options = {
		{"@conversation/corellia_rebel_tier4:s_fcddb599", "intro_enlightened"}, -- It does. Very wise of you to recognize that.
	}
}
arkon_convo:addScreen(intro_smart)

-- Both paths converge here → duty mission explanation (player needs XP before training)
intro_enlightened = ConvoScreen:new {
	id = "intro_enlightened",
	leftDialog = "@conversation/corellia_rebel_tier4:s_29f4061f", -- Oh! So enlightened! Bah! Never mind. Let's talk about your mission.
	stopConversation = "false",
	options = {
		{"@conversation/corellia_rebel_tier4:s_98588d70", "duty_explain_1"}, -- OK fine.
	}
}
arkon_convo:addScreen(intro_enlightened)

-- ========================================
-- Duty Mission Menu
-- ========================================

-- Duty Menu (shown when player needs to grind XP or post-master)
duty_menu = ConvoScreen:new {
	id = "duty_menu",
	leftDialog = "@conversation/corellia_rebel_tier4:s_a5958aac", -- I'd like to see you do some WORK for a change! Sign up for something, pronto...
	animation = "gesticulate_wildly",
	stopConversation = "false",
	options = {
		{"@conversation/corellia_rebel_tier4:s_647ad2bc", "accept_duty4"}, -- I'll take care of those Black Suns.
		{"@conversation/corellia_rebel_tier4:s_d9116b4d", "accept_duty1"}, -- I'll escort those freighters.
		{"@conversation/corellia_rebel_tier4:s_8450d7db", "accept_duty3"}, -- Let me take a crack at disabling those troop transports.
		{"@conversation/corellia_rebel_tier4:s_9943289", "accept_duty2"}, -- I want to help those scientists.
		{"@conversation/corellia_rebel_tier4:s_9775f996", "duty_explain_1"}, -- Can you explain it again?
	}
}
arkon_convo:addScreen(duty_menu)

-- Duty Accept Screens
accept_duty1 = ConvoScreen:new {
	id = "accept_duty1",
	leftDialog = "@conversation/corellia_rebel_tier4:s_fed79efe", -- Then hurry up and get yourself over to Dathomir!
	animation = "dismiss",
	stopConversation = "true",
	options = {}
}
arkon_convo:addScreen(accept_duty1)

accept_duty2 = ConvoScreen:new {
	id = "accept_duty2",
	leftDialog = "@conversation/corellia_rebel_tier4:s_835acc11", -- You think you're a hero or something? Fine! ...Dantooine system.
	animation = "dismiss",
	stopConversation = "true",
	options = {}
}
arkon_convo:addScreen(accept_duty2)

accept_duty3 = ConvoScreen:new {
	id = "accept_duty3",
	leftDialog = "@conversation/corellia_rebel_tier4:s_b0d064ef", -- Endor it is! Leave immediately!
	animation = "dismiss",
	stopConversation = "true",
	options = {}
}
arkon_convo:addScreen(accept_duty3)

accept_duty4 = ConvoScreen:new {
	id = "accept_duty4",
	leftDialog = "@conversation/corellia_rebel_tier4:s_d8209030", -- Then you're going to Dantooine! Goodbye!
	animation = "dismiss",
	stopConversation = "true",
	options = {}
}
arkon_convo:addScreen(accept_duty4)

-- ========================================
-- Duty Explanation Chain
-- ========================================

duty_explain_1 = ConvoScreen:new {
	id = "duty_explain_1",
	leftDialog = "@conversation/corellia_rebel_tier4:s_4bce8f6f", -- Fine, listen up... Black Suns taking business from us... need a pilot to send them a message...
	stopConversation = "false",
	options = {
		{"@conversation/corellia_rebel_tier4:s_42880861", "duty_explain_2"}, -- Okay...
	}
}
arkon_convo:addScreen(duty_explain_1)

duty_explain_2 = ConvoScreen:new {
	id = "duty_explain_2",
	leftDialog = "@conversation/corellia_rebel_tier4:s_dc241019", -- What'd you say?
	animation = "listen",
	stopConversation = "false",
	options = {
		{"@conversation/corellia_rebel_tier4:s_48529763", "duty_explain_3"}, -- I said, 'Okay'!
	}
}
arkon_convo:addScreen(duty_explain_2)

duty_explain_3 = ConvoScreen:new {
	id = "duty_explain_3",
	leftDialog = "@conversation/corellia_rebel_tier4:s_f13513cd", -- Hmph! Well here's some good news. One of our men has raided an Imperial outpost on Dathomir...
	playerAnimation = "explain",
	stopConversation = "false",
	options = {
		{"@conversation/corellia_rebel_tier4:s_c3363bcd", "duty_explain_4"}, -- Uh huh.
	}
}
arkon_convo:addScreen(duty_explain_3)

duty_explain_4 = ConvoScreen:new {
	id = "duty_explain_4",
	leftDialog = "@conversation/corellia_rebel_tier4:s_900f01d1", -- What?
	animation = "listen",
	stopConversation = "false",
	options = {
		{"@conversation/corellia_rebel_tier4:s_539f9a2e", "duty_explain_5"}, -- Nothing!
	}
}
arkon_convo:addScreen(duty_explain_4)

duty_explain_5 = ConvoScreen:new {
	id = "duty_explain_5",
	leftDialog = "@conversation/corellia_rebel_tier4:s_e3e480fe", -- Don't smart off to me!
	animation = "threaten",
	stopConversation = "false",
	options = {
		{"@conversation/corellia_rebel_tier4:s_7e602d1b", "duty_explain_6"}, -- I'm not!
	}
}
arkon_convo:addScreen(duty_explain_5)

duty_explain_6 = ConvoScreen:new {
	id = "duty_explain_6",
	leftDialog = "@conversation/corellia_rebel_tier4:s_6429f86b", -- Here's some MORE good news. Another group of our men infiltrated Imperial troop transports in the Endor system...
	stopConversation = "false",
	options = {
		{"@conversation/corellia_rebel_tier4:s_8e9d0848", "duty_explain_end"}, -- [nod]
	}
}
arkon_convo:addScreen(duty_explain_6)

duty_explain_end = ConvoScreen:new {
	id = "duty_explain_end",
	leftDialog = "@conversation/corellia_rebel_tier4:s_9bbb9999", -- ...Rebel rescue mission! Scientists through Dantooine... So what's it going to be, junior?
	stopConversation = "false",
	options = {
		{"@conversation/corellia_rebel_tier4:s_647ad2bc", "accept_duty4"}, -- I'll take care of those Black Suns.
		{"@conversation/corellia_rebel_tier4:s_d9116b4d", "accept_duty1"}, -- I'll escort those freighters.
		{"@conversation/corellia_rebel_tier4:s_8450d7db", "accept_duty3"}, -- Let me take a crack at disabling those troop transports.
		{"@conversation/corellia_rebel_tier4:s_9943289", "accept_duty2"}, -- I want to help those scientists.
		{"@conversation/corellia_rebel_tier4:s_9775f996", "duty_explain_1"}, -- Can you explain it again?
	}
}
arkon_convo:addScreen(duty_explain_end)

-- ========================================
-- Admiral Burke Transfer (Master Mission)
-- ========================================

-- Master mission entry (completed all tier 4 quests, no master skill yet)
master_mission = ConvoScreen:new {
	id = "master_mission",
	leftDialog = "@conversation/corellia_rebel_tier4:s_b6b4b241", -- Attention! Alliance Headquarters has approved your transfer...
	animation = "beckon",
	stopConversation = "false",
	options = {
		{"@conversation/corellia_rebel_tier4:s_bbe3529b", "burke_who"}, -- Who is Admiral Burke?
		{"@conversation/corellia_rebel_tier4:s_36f346a5", "burke_nogear"}, -- What if I don't have any gear, sir?
	}
}
arkon_convo:addScreen(master_mission)

-- PATH A: "Who is Admiral Burke?"
burke_who = ConvoScreen:new {
	id = "burke_who",
	leftDialog = "@conversation/corellia_rebel_tier4:s_bcbc9230", -- Admiral Willham Burke is head of the fourth battle fleet...
	stopConversation = "false",
	options = {
		{"@conversation/corellia_rebel_tier4:s_86677c6b", "burke_request"}, -- What does he want with me?
	}
}
arkon_convo:addScreen(burke_who)

burke_request = ConvoScreen:new {
	id = "burke_request",
	leftDialog = "@conversation/corellia_rebel_tier4:s_6634adb9", -- I don't have the answer to that one... Admiral Burke requested you personally.
	stopConversation = "false",
	options = {
		{"@conversation/corellia_rebel_tier4:s_bcc6b959", "burke_location"}, -- Where do I need to report?
	}
}
arkon_convo:addScreen(burke_request)

burke_location = ConvoScreen:new {
	id = "burke_location",
	leftDialog = "@conversation/corellia_rebel_tier4:s_d74e67f", -- ...Admiral Burke is in Doaba Guerfel on Corellia...
	stopConversation = "false",
	options = {
		{"@conversation/corellia_rebel_tier4:s_2c4789b", "accept_master_quest"}, -- Understood.
	}
}
arkon_convo:addScreen(burke_location)

-- PATH B: "What if I don't have any gear?"
burke_nogear = ConvoScreen:new {
	id = "burke_nogear",
	leftDialog = "@conversation/corellia_rebel_tier4:s_8057f803", -- Then it won't take you too long to pack!...
	animation = "laugh",
	stopConversation = "false",
	options = {
		{"@conversation/corellia_rebel_tier4:s_ff9bf289", "accept_master_quest"}, -- Always, sir.
	}
}
arkon_convo:addScreen(burke_nogear)

-- Both paths converge here (triggers master quest grant)
accept_master_quest = ConvoScreen:new {
	id = "accept_master_quest",
	leftDialog = "@conversation/corellia_rebel_tier4:s_4ef35507", -- He is expecting you right away... Dismissed, pilot.
	animation = "dismiss",
	playerAnimation = "nod_head_once",
	stopConversation = "true",
	options = {}
}
arkon_convo:addScreen(accept_master_quest)

-- ========================================
-- Completed Arkon (Post-Master Duty Menu)
-- ========================================

-- Post-master duty menu (player has master skill, returns to Arkon for duty missions)
completed_arkon = ConvoScreen:new {
	id = "completed_arkon",
	leftDialog = "@conversation/corellia_rebel_tier4:s_d318a2bb", -- Back from your assignment with Admiral Burke, I see!...
	stopConversation = "false",
	options = {
		{"@conversation/corellia_rebel_tier4:s_647ad2bc", "accept_duty4"}, -- I'll take care of those Black Suns.
		{"@conversation/corellia_rebel_tier4:s_d9116b4d", "accept_duty1"}, -- I'll escort those freighters.
		{"@conversation/corellia_rebel_tier4:s_8450d7db", "accept_duty3"}, -- Let me take a crack at disabling those troop transports.
		{"@conversation/corellia_rebel_tier4:s_9943289", "accept_duty2"}, -- I want to help those scientists.
		{"@conversation/corellia_rebel_tier4:s_9775f996", "duty_explain_1"}, -- Can you explain it again?
	}
}
arkon_convo:addScreen(completed_arkon)

addConversationTemplate("arkon_convo", arkon_convo)
