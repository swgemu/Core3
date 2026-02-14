aqzow_convo = ConvoTemplate:new {
	initialScreen = "",
	templateType = "Lua",
	luaClassHandler = "aqzowConvoHandler",
	screens = {}
}

-- ========================================
-- Gate Screens (stopConversation = true)
-- ========================================

-- Not a Pilot (no JTL skills at all)
no_jtl = ConvoScreen:new {
	id = "no_jtl",
	leftDialog = "@conversation/corellia_rebel_tier3:s_195b98b2", -- I only speak to pilots. Move along now.
	animation = "rub_belly",
	stopConversation = "true",
	options = {}
}
aqzow_convo:addScreen(no_jtl)

-- Imperial Pilot
imperial_pilot = ConvoScreen:new {
	id = "imperial_pilot",
	leftDialog = "@conversation/corellia_rebel_tier3:s_346f07d4", -- Move on.
	animation = "laugh",
	stopConversation = "true",
	options = {}
}
aqzow_convo:addScreen(imperial_pilot)

-- Neutral Pilot
neutral_pilot = ConvoScreen:new {
	id = "neutral_pilot",
	leftDialog = "@conversation/corellia_rebel_tier3:s_346f07d4", -- Move on.
	animation = "laugh",
	stopConversation = "true",
	options = {}
}
aqzow_convo:addScreen(neutral_pilot)

-- Not Rebel Pilot
not_rebel_pilot = ConvoScreen:new {
	id = "not_rebel_pilot",
	leftDialog = "@conversation/corellia_rebel_tier3:s_346f07d4", -- Move on.
	animation = "laugh",
	stopConversation = "true",
	options = {}
}
aqzow_convo:addScreen(not_rebel_pilot)

-- Non-Havoc Rebel Pilot (wrong track)
non_havoc_pilot = ConvoScreen:new {
	id = "non_havoc_pilot",
	leftDialog = "@conversation/corellia_rebel_tier3:s_853538e8", -- I'm not taking transfers. Return to your unit, pilot.
	animation = "check_wrist_device",
	stopConversation = "true",
	options = {}
}
aqzow_convo:addScreen(non_havoc_pilot)

-- Not Ready (hasn't completed Tier 2)
not_ready = ConvoScreen:new {
	id = "not_ready",
	leftDialog = "@conversation/corellia_rebel_tier3:s_b9ba3998", -- Lady Viopa is waiting for you.
	animation = "wave_on_dismissing",
	stopConversation = "true",
	options = {}
}
aqzow_convo:addScreen(not_ready)

-- Has Active Mission
has_mission = ConvoScreen:new {
	id = "has_mission",
	leftDialog = "@conversation/corellia_rebel_tier3:s_a54fd6b7", -- Do not speak to me until you have completed your mission.
	animation = "shake_head_no",
	stopConversation = "true",
	options = {}
}
aqzow_convo:addScreen(has_mission)

-- ========================================
-- Negative Faction
-- ========================================

negative_faction = ConvoScreen:new {
	id = "negative_faction",
	leftDialog = "@conversation/corellia_rebel_tier3:s_a08c36ef", -- As if the Empire weren't causing us enough grief... now there are reports that YOU are working against the Rebel Alliance, too!
	animation = "shrug_hands",
	stopConversation = "false",
	options = {
		{"@conversation/corellia_rebel_tier3:s_77e48d5b", "faction_grounded"}, -- What do you mean?
	}
}
aqzow_convo:addScreen(negative_faction)

faction_grounded = ConvoScreen:new {
	id = "faction_grounded",
	leftDialog = "@conversation/corellia_rebel_tier3:s_23d7a2b6", -- What I MEAN, Pilot, is that you are grounded until further notice...
	animation = "explain",
	stopConversation = "false",
	options = {
		{"@conversation/corellia_rebel_tier3:s_14c18bea", "faction_hands_tied"}, -- It's not true!
	}
}
aqzow_convo:addScreen(faction_grounded)

faction_hands_tied = ConvoScreen:new {
	id = "faction_hands_tied",
	leftDialog = "@conversation/corellia_rebel_tier3:s_ae7e01af", -- My hands are tied. Until you improve your standing with the Rebel Alliance, we cannot trust you with any more missions.
	animation = "slump_head",
	stopConversation = "true",
	options = {}
}
aqzow_convo:addScreen(faction_hands_tied)

-- ========================================
-- Completed Tier 3 / Transfer to Tier 4
-- ========================================

completed_aqzow = ConvoScreen:new {
	id = "completed_aqzow",
	leftDialog = "@conversation/corellia_rebel_tier3:s_6100696", -- All right! I've done the best I can with you. Your transfer has come through.
	animation = "nod_head_once",
	playerAnimation = "salute1",
	stopConversation = "false",
	options = {
		{"@conversation/corellia_rebel_tier3:s_ad721916", "tier4_watch_mouth"}, -- Finally!
		{"@conversation/corellia_rebel_tier3:s_987445c9", "tier4_report_arkon_polite"}, -- Thank you, sir.
	}
}
aqzow_convo:addScreen(completed_aqzow)

tier4_watch_mouth = ConvoScreen:new {
	id = "tier4_watch_mouth",
	leftDialog = "@conversation/corellia_rebel_tier3:s_9795f675", -- Watch your mouth, pilot! You should be thanking your lucky stars that you've been trained by the great Aqzow.
	animation = "pound_fist_palm",
	playerAnimation = "slow_down",
	stopConversation = "false",
	options = {
		{"@conversation/corellia_rebel_tier3:s_8bf9d94d", "tier4_report_arkon_snarky"}, -- Whatever you say, sir.
	}
}
aqzow_convo:addScreen(tier4_watch_mouth)

tier4_report_arkon_snarky = ConvoScreen:new {
	id = "tier4_report_arkon_snarky",
	leftDialog = "@conversation/corellia_rebel_tier3:s_11fa74eb", -- Well I'm very happy to say that you're going to be reporting to Warvog Arkon. You two deserve each other...
	stopConversation = "true",
	options = {}
}
aqzow_convo:addScreen(tier4_report_arkon_snarky)

tier4_report_arkon_polite = ConvoScreen:new {
	id = "tier4_report_arkon_polite",
	leftDialog = "@conversation/corellia_rebel_tier3:s_30be37b", -- You're welcome. And congratulations, solider... Warvog Arkon... Dismissed!
	animation = "salute1",
	playerAnimation = "salute1",
	stopConversation = "true",
	options = {}
}
aqzow_convo:addScreen(tier4_report_arkon_polite)

-- ========================================
-- Failed Quest Screens
-- ========================================

-- Failed Quest 1
failed_quest1 = ConvoScreen:new {
	id = "failed_quest1",
	leftDialog = "@conversation/corellia_rebel_tier3:s_2ccbae6", -- Idiot!
	animation = "shake_head_disgust",
	stopConversation = "false",
	options = {
		{"@conversation/corellia_rebel_tier3:s_d9f9ff9a", "retry_quest1_a"}, -- I can do it. There's still time.
		{"@conversation/corellia_rebel_tier3:s_8a0c5437", "retry_quest1_b"}, -- Hey! They're good!
	}
}
aqzow_convo:addScreen(failed_quest1)

retry_quest1_a = ConvoScreen:new {
	id = "retry_quest1_a",
	leftDialog = "@conversation/corellia_rebel_tier3:s_57127d49", -- If you screw up again, don't bother coming back.
	animation = "point_forward",
	stopConversation = "true",
	options = {}
}
aqzow_convo:addScreen(retry_quest1_a)

retry_quest1_b = ConvoScreen:new {
	id = "retry_quest1_b",
	leftDialog = "@conversation/corellia_rebel_tier3:s_5f3f0268", -- No excuses! Get back out there!
	animation = "point_away",
	stopConversation = "true",
	options = {}
}
aqzow_convo:addScreen(retry_quest1_b)

-- Failed Quest 2
failed_quest2 = ConvoScreen:new {
	id = "failed_quest2",
	leftDialog = "@conversation/corellia_rebel_tier3:s_98dbd811", -- The fleet still needs your help!
	animation = "point_away",
	stopConversation = "false",
	options = {
		{"@conversation/corellia_rebel_tier3:s_bf9854b5", "retry_quest2_a"}, -- I know!
		{"@conversation/corellia_rebel_tier3:s_1dd40de5", "retry_quest2_b"}, -- I'm doing the best I can!
	}
}
aqzow_convo:addScreen(failed_quest2)

retry_quest2_a = ConvoScreen:new {
	id = "retry_quest2_a",
	leftDialog = "@conversation/corellia_rebel_tier3:s_81c19652", -- Then why are you HERE?! Scram!
	animation = "gesticulate_wildly",
	stopConversation = "true",
	options = {}
}
aqzow_convo:addScreen(retry_quest2_a)

retry_quest2_b = ConvoScreen:new {
	id = "retry_quest2_b",
	leftDialog = "@conversation/corellia_rebel_tier3:s_f01922ee", -- The only thing you're DOING is making me CRAZY! Get OUT of here!!
	animation = "gesticulate_wildly",
	stopConversation = "true",
	options = {}
}
aqzow_convo:addScreen(retry_quest2_b)

-- Failed Quest 3
failed_quest3 = ConvoScreen:new {
	id = "failed_quest3",
	leftDialog = "@conversation/corellia_rebel_tier3:s_c317f1e7", -- If I didn't know better, I'd think you were working for the Emperor. Do your job!!
	animation = "standing_raise_fist",
	stopConversation = "false",
	options = {
		{"@conversation/corellia_rebel_tier3:s_45ab7a66", "failed_q3_hug"}, -- You don't have to be so mean about it.
		{"@conversation/corellia_rebel_tier3:s_9b43a7ee", "retry_quest3_b"}, -- Yes sir.
	}
}
aqzow_convo:addScreen(failed_quest3)

failed_q3_hug = ConvoScreen:new {
	id = "failed_q3_hug",
	leftDialog = "@conversation/corellia_rebel_tier3:s_8137160f", -- Aw. Do you want a hug?
	animation = "accept_affection",
	stopConversation = "false",
	options = {
		{"@conversation/corellia_rebel_tier3:s_e1e40ead", "retry_quest3_a"}, -- That would be nice.
	}
}
aqzow_convo:addScreen(failed_q3_hug)

retry_quest3_a = ConvoScreen:new {
	id = "retry_quest3_a",
	leftDialog = "@conversation/corellia_rebel_tier3:s_f2003333", -- What do I look like, Lady Viopa? I'll give you a bear hug all right...
	animation = "pound_fist_chest",
	playerAnimation = "accept_affection",
	stopConversation = "true",
	options = {}
}
aqzow_convo:addScreen(retry_quest3_a)

retry_quest3_b = ConvoScreen:new {
	id = "retry_quest3_b",
	leftDialog = "@conversation/corellia_rebel_tier3:s_1aff29b0", -- I'm going to seriously consider early retirement.
	animation = "smack_self",
	playerAnimation = "embarrassed",
	stopConversation = "true",
	options = {}
}
aqzow_convo:addScreen(retry_quest3_b)

-- Failed Quest 4
failed_quest4 = ConvoScreen:new {
	id = "failed_quest4",
	leftDialog = "@conversation/corellia_rebel_tier3:s_85ccda8d", -- I was wrong when I said you were my best pilot.
	stopConversation = "false",
	options = {
		{"@conversation/corellia_rebel_tier3:s_f1a5d3e2", "retry_quest4_a"}, -- Let me prove it to you!
		{"@conversation/corellia_rebel_tier3:s_292cca3d", "retry_quest4_b"}, -- I AM your best pilot. I'm just not done yet.
	}
}
aqzow_convo:addScreen(failed_quest4)

retry_quest4_a = ConvoScreen:new {
	id = "retry_quest4_a",
	leftDialog = "@conversation/corellia_rebel_tier3:s_e73e9bb1", -- Don't fail me again.
	stopConversation = "true",
	options = {}
}
aqzow_convo:addScreen(retry_quest4_a)

retry_quest4_b = ConvoScreen:new {
	id = "retry_quest4_b",
	leftDialog = "@conversation/corellia_rebel_tier3:s_e07a3d4a", -- Then stop wasting my time and get back out there!
	animation = "gesticulate_wildly",
	stopConversation = "true",
	options = {}
}
aqzow_convo:addScreen(retry_quest4_b)

-- ========================================
-- Reward Screens (Quest Complete, Grant Reward + Train Skill)
-- ========================================

-- Quest 1 Reward
excellent_work = ConvoScreen:new {
	id = "excellent_work",
	leftDialog = "@conversation/corellia_rebel_tier3:s_620547d7", -- Soldiers in my unit must be well-trained in all areas. Where are you lacking?
	animation = "rub_chin_thoughtful",
	stopConversation = "false",
	options = {
	}
}
aqzow_convo:addScreen(excellent_work)

-- Quest 2 Reward
excellent_work2 = ConvoScreen:new {
	id = "excellent_work2",
	leftDialog = "@conversation/corellia_rebel_tier3:s_da836e9e", -- It is time to continue your training.
	animation = "snap_finger1",
	stopConversation = "false",
	options = {
	}
}
aqzow_convo:addScreen(excellent_work2)

-- Quest 3 Reward
excellent_work3 = ConvoScreen:new {
	id = "excellent_work3",
	leftDialog = "@conversation/corellia_rebel_tier3:s_86e0190", -- You're good, but you need to know more if you're ever going to be great.
	animation = "nod_head_once",
	stopConversation = "false",
	options = {
	}
}
aqzow_convo:addScreen(excellent_work3)

-- Quest 4 Reward (uses %NU prose token for player name)
excellent_work4 = ConvoScreen:new {
	id = "excellent_work4",
	leftDialog = "@conversation/corellia_rebel_tier3:s_85bda55d", -- Outstanding performance up there pilot... You are truly one of the best of the best now %NU.
	animation = "salute1",
	stopConversation = "false",
	options = {
	}
}
aqzow_convo:addScreen(excellent_work4)

-- ========================================
-- Skill Training
-- ========================================

-- Training Menu (dynamic options added by handler based on missing skills)
ready_train_pilot = ConvoScreen:new {
	id = "ready_train_pilot",
	leftDialog = "@conversation/corellia_rebel_tier3:s_620547d7", -- Soldiers in my unit must be well-trained in all areas. Where are you lacking?
	stopConversation = "false",
	options = {
		-- Options added dynamically by handler
	}
}
aqzow_convo:addScreen(ready_train_pilot)

-- Per-phase training terminal screens (skill granted by handler)
-- Initial phase (before quest 1)
initial_train_fighters = ConvoScreen:new {
	id = "initial_train_fighters",
	leftDialog = "@conversation/corellia_rebel_tier3:s_da65a262", -- Very good. One of my pilots will train you. When you're done, come see me for your next mission.
	animation = "nod_head_once",
	stopConversation = "true",
	options = {}
}
aqzow_convo:addScreen(initial_train_fighters)

initial_train_components = ConvoScreen:new {
	id = "initial_train_components",
	leftDialog = "@conversation/corellia_rebel_tier3:s_da65a262",
	animation = "nod_head_once",
	stopConversation = "true",
	options = {}
}
aqzow_convo:addScreen(initial_train_components)

initial_train_procedures = ConvoScreen:new {
	id = "initial_train_procedures",
	leftDialog = "@conversation/corellia_rebel_tier3:s_da65a262",
	animation = "nod_head_once",
	stopConversation = "true",
	options = {}
}
aqzow_convo:addScreen(initial_train_procedures)

initial_train_droid = ConvoScreen:new {
	id = "initial_train_droid",
	leftDialog = "@conversation/corellia_rebel_tier3:s_da65a262",
	animation = "offer_affection",
	stopConversation = "true",
	options = {}
}
aqzow_convo:addScreen(initial_train_droid)

-- Mission 2 phase (after quest 1 complete)
mission2_train_fighters = ConvoScreen:new {
	id = "mission2_train_fighters",
	leftDialog = "@conversation/corellia_rebel_tier3:s_da65a262",
	animation = "nod_head_once",
	stopConversation = "true",
	options = {}
}
aqzow_convo:addScreen(mission2_train_fighters)

mission2_train_components = ConvoScreen:new {
	id = "mission2_train_components",
	leftDialog = "@conversation/corellia_rebel_tier3:s_da65a262",
	animation = "nod_head_once",
	stopConversation = "true",
	options = {}
}
aqzow_convo:addScreen(mission2_train_components)

mission2_train_procedures = ConvoScreen:new {
	id = "mission2_train_procedures",
	leftDialog = "@conversation/corellia_rebel_tier3:s_da65a262",
	animation = "nod_head_once",
	stopConversation = "true",
	options = {}
}
aqzow_convo:addScreen(mission2_train_procedures)

mission2_train_droid = ConvoScreen:new {
	id = "mission2_train_droid",
	leftDialog = "@conversation/corellia_rebel_tier3:s_da65a262",
	animation = "offer_affection",
	stopConversation = "true",
	options = {}
}
aqzow_convo:addScreen(mission2_train_droid)

-- Mission 3 phase (after quest 2 complete)
mission3_train_fighters = ConvoScreen:new {
	id = "mission3_train_fighters",
	leftDialog = "@conversation/corellia_rebel_tier3:s_da65a262",
	animation = "nod_head_once",
	stopConversation = "true",
	options = {}
}
aqzow_convo:addScreen(mission3_train_fighters)

mission3_train_components = ConvoScreen:new {
	id = "mission3_train_components",
	leftDialog = "@conversation/corellia_rebel_tier3:s_da65a262",
	animation = "nod_head_once",
	stopConversation = "true",
	options = {}
}
aqzow_convo:addScreen(mission3_train_components)

mission3_train_procedures = ConvoScreen:new {
	id = "mission3_train_procedures",
	leftDialog = "@conversation/corellia_rebel_tier3:s_da65a262",
	animation = "nod_head_once",
	stopConversation = "true",
	options = {}
}
aqzow_convo:addScreen(mission3_train_procedures)

mission3_train_droid = ConvoScreen:new {
	id = "mission3_train_droid",
	leftDialog = "@conversation/corellia_rebel_tier3:s_da65a262",
	animation = "offer_affection",
	stopConversation = "true",
	options = {}
}
aqzow_convo:addScreen(mission3_train_droid)

-- Mission 4 phase (after quest 3 complete)
mission4_train_fighters = ConvoScreen:new {
	id = "mission4_train_fighters",
	leftDialog = "@conversation/corellia_rebel_tier3:s_da65a262",
	animation = "nod_head_once",
	stopConversation = "true",
	options = {}
}
aqzow_convo:addScreen(mission4_train_fighters)

mission4_train_components = ConvoScreen:new {
	id = "mission4_train_components",
	leftDialog = "@conversation/corellia_rebel_tier3:s_da65a262",
	animation = "nod_head_once",
	stopConversation = "true",
	options = {}
}
aqzow_convo:addScreen(mission4_train_components)

mission4_train_procedures = ConvoScreen:new {
	id = "mission4_train_procedures",
	leftDialog = "@conversation/corellia_rebel_tier3:s_da65a262",
	animation = "nod_head_once",
	stopConversation = "true",
	options = {}
}
aqzow_convo:addScreen(mission4_train_procedures)

mission4_train_droid = ConvoScreen:new {
	id = "mission4_train_droid",
	leftDialog = "@conversation/corellia_rebel_tier3:s_da65a262",
	animation = "offer_affection",
	stopConversation = "true",
	options = {}
}
aqzow_convo:addScreen(mission4_train_droid)

-- Final phase (after quest 4 complete, last skill)
final_train_fighters = ConvoScreen:new {
	id = "final_train_fighters",
	leftDialog = "@conversation/corellia_rebel_tier3:s_da65a262",
	animation = "nod_head_once",
	stopConversation = "true",
	options = {}
}
aqzow_convo:addScreen(final_train_fighters)

final_train_components = ConvoScreen:new {
	id = "final_train_components",
	leftDialog = "@conversation/corellia_rebel_tier3:s_da65a262",
	animation = "nod_head_once",
	stopConversation = "true",
	options = {}
}
aqzow_convo:addScreen(final_train_components)

final_train_procedures = ConvoScreen:new {
	id = "final_train_procedures",
	leftDialog = "@conversation/corellia_rebel_tier3:s_da65a262",
	animation = "nod_head_once",
	stopConversation = "true",
	options = {}
}
aqzow_convo:addScreen(final_train_procedures)

final_train_droid = ConvoScreen:new {
	id = "final_train_droid",
	leftDialog = "@conversation/corellia_rebel_tier3:s_da65a262",
	animation = "offer_affection",
	stopConversation = "true",
	options = {}
}
aqzow_convo:addScreen(final_train_droid)

-- ========================================
-- Quest 1: Recovery Mission (Spy on Yavin)
-- ========================================

-- Introduction / First Meeting with Aqzow
introduction = ConvoScreen:new {
	id = "introduction",
	leftDialog = "@conversation/corellia_rebel_tier3:s_c5648040", -- How did you like Lady Viopa?
	animation = "beckon",
	stopConversation = "false",
	options = {
		{"@conversation/corellia_rebel_tier3:s_fb0a082d", "mommy_treatment"}, -- A lovely lady.
		{"@conversation/corellia_rebel_tier3:s_f8e71988", "is_that_right"}, -- I'm ready for my mission.
	}
}
aqzow_convo:addScreen(introduction)

-- First Mission (edge case: has tier 3 skill, needs quest 1)
first_mission = ConvoScreen:new {
	id = "first_mission",
	leftDialog = "@conversation/corellia_rebel_tier3:s_c5648040", -- How did you like Lady Viopa?
	animation = "beckon",
	stopConversation = "false",
	options = {
		{"@conversation/corellia_rebel_tier3:s_fb0a082d", "mommy_treatment"}, -- A lovely lady.
		{"@conversation/corellia_rebel_tier3:s_f8e71988", "is_that_right"}, -- I'm ready for my mission.
	}
}
aqzow_convo:addScreen(first_mission)

-- "A lovely lady" path
mommy_treatment = ConvoScreen:new {
	id = "mommy_treatment",
	leftDialog = "@conversation/corellia_rebel_tier3:s_512343e1", -- You like that mommy treatment?
	stopConversation = "false",
	options = {
		{"@conversation/corellia_rebel_tier3:s_17a593ae", "kindergarten"}, -- Sure, who doesn't?
		{"@conversation/corellia_rebel_tier3:s_9ce7f436", "sugar_spice"}, -- It's OK, I guess.
	}
}
aqzow_convo:addScreen(mommy_treatment)

kindergarten = ConvoScreen:new {
	id = "kindergarten",
	leftDialog = "@conversation/corellia_rebel_tier3:s_3bb82587", -- Are you kidding? This isn't kindergarten. We're at war, soldier!
	animation = "snap_finger2",
	playerAnimation = "shrug_hands",
	stopConversation = "false",
	options = {
		{"@conversation/corellia_rebel_tier3:s_b6c1a98e", "spy_intro_a"}, -- I'm here to do my job.
	}
}
aqzow_convo:addScreen(kindergarten)

sugar_spice = ConvoScreen:new {
	id = "sugar_spice",
	leftDialog = "@conversation/corellia_rebel_tier3:s_d1f24c43", -- Can't stand all that sugar and spice, myself.
	animation = "yawn",
	playerAnimation = "shrug_shoulders",
	stopConversation = "false",
	options = {
		{"@conversation/corellia_rebel_tier3:s_a114fef2", "spy_intro_b"}, -- I'm reporting for duty.
	}
}
aqzow_convo:addScreen(sugar_spice)

-- "I'm ready for my mission" path
is_that_right = ConvoScreen:new {
	id = "is_that_right",
	leftDialog = "@conversation/corellia_rebel_tier3:s_535a48bf", -- Is that right?
	stopConversation = "false",
	options = {
		{"@conversation/corellia_rebel_tier3:s_fafb0eec", "spy_intro_c"}, -- Put me out there!
		{"@conversation/corellia_rebel_tier3:s_5c2a6c79", "bite_tongue"}, -- Are you trying to say something?
	}
}
aqzow_convo:addScreen(is_that_right)

bite_tongue = ConvoScreen:new {
	id = "bite_tongue",
	leftDialog = "@conversation/corellia_rebel_tier3:s_c207cb86", -- You should learn to bite your tongue - before someone bites it off for you.
	stopConversation = "false",
	options = {
		{"@conversation/corellia_rebel_tier3:s_9d826c99", "spy_intro_d"}, -- When you put it that way...what's my mission?
	}
}
aqzow_convo:addScreen(bite_tongue)

-- Quest 1 Spy Chain - Path A (from kindergarten)
spy_intro_a = ConvoScreen:new {
	id = "spy_intro_a",
	leftDialog = "@conversation/corellia_rebel_tier3:s_5748a2bb", -- Good. Let's cut to the chase. We've learned that there was an Imperial spy operating on Yavin.
	animation = "nod_head_once",
	playerAnimation = "salute1",
	stopConversation = "false",
	options = {
		{"@conversation/corellia_rebel_tier3:s_d8376b91", "spy_found_a"}, -- A spy? On Yavin? We've got secret hangars here.
	}
}
aqzow_convo:addScreen(spy_intro_a)

spy_found_a = ConvoScreen:new {
	id = "spy_found_a",
	leftDialog = "@conversation/corellia_rebel_tier3:s_88dd0a6e", -- They're not so secret anymore. The spy found them. He's very good - and now he's making his way back to the Imperial fleet.
	animation = "nod_head_once",
	stopConversation = "false",
	options = {
		{"@conversation/corellia_rebel_tier3:s_15c65a41", "stop_him_a"}, -- If he tells the Empire about those hangars, they'll attack us for sure.
	}
}
aqzow_convo:addScreen(spy_found_a)

stop_him_a = ConvoScreen:new {
	id = "stop_him_a",
	leftDialog = "@conversation/corellia_rebel_tier3:s_a7e7494d", -- He's not going to tell anybody ANYTHING. Because you're going to stop him, aren't you.
	stopConversation = "false",
	options = {
		{"@conversation/corellia_rebel_tier3:s_c1d821eb", "find_ship_a"}, -- Oh, I'll stop him all right.
	}
}
aqzow_convo:addScreen(stop_him_a)

find_ship_a = ConvoScreen:new {
	id = "find_ship_a",
	leftDialog = "@conversation/corellia_rebel_tier3:s_f940636f", -- Find his ship. When you do, launch a space assault droid - that will give you control of his ship.
	stopConversation = "false",
	options = {
		{"@conversation/corellia_rebel_tier3:s_9d1fa2a2", "accept_quest1_a"}, -- When can I leave?
	}
}
aqzow_convo:addScreen(find_ship_a)

accept_quest1_a = ConvoScreen:new {
	id = "accept_quest1_a",
	leftDialog = "@conversation/corellia_rebel_tier3:s_90b730b5", -- Immediately.
	animation = "dismiss",
	stopConversation = "true",
	options = {}
}
aqzow_convo:addScreen(accept_quest1_a)

-- Quest 1 Spy Chain - Path B (from sugar_spice)
spy_intro_b = ConvoScreen:new {
	id = "spy_intro_b",
	leftDialog = "@conversation/corellia_rebel_tier3:s_5748a2bb", -- Good. Let's cut to the chase. We've learned that there was an Imperial spy operating on Yavin.
	animation = "nod_head_once",
	stopConversation = "false",
	options = {
		{"@conversation/corellia_rebel_tier3:s_e078d62c", "spy_found_b"}, -- A spy? On Yavin? We've got secret hangars here!
	}
}
aqzow_convo:addScreen(spy_intro_b)

spy_found_b = ConvoScreen:new {
	id = "spy_found_b",
	leftDialog = "@conversation/corellia_rebel_tier3:s_88dd0a6e", -- They're not so secret anymore. The spy found them...
	animation = "nod_head_once",
	stopConversation = "false",
	options = {
		{"@conversation/corellia_rebel_tier3:s_15c65a41", "stop_him_b"}, -- If he tells the Empire about those hangars, they'll attack us for sure.
	}
}
aqzow_convo:addScreen(spy_found_b)

stop_him_b = ConvoScreen:new {
	id = "stop_him_b",
	leftDialog = "@conversation/corellia_rebel_tier3:s_a7e7494d", -- He's not going to tell anybody ANYTHING. Because you're going to stop him, aren't you.
	stopConversation = "false",
	options = {
		{"@conversation/corellia_rebel_tier3:s_c1d821eb", "find_ship_b"}, -- Oh, I'll stop him all right.
	}
}
aqzow_convo:addScreen(stop_him_b)

find_ship_b = ConvoScreen:new {
	id = "find_ship_b",
	leftDialog = "@conversation/corellia_rebel_tier3:s_f940636f", -- Find his ship. When you do, launch a space assault droid...
	playerAnimation = "pound_fist_palm",
	stopConversation = "false",
	options = {
		{"@conversation/corellia_rebel_tier3:s_9d1fa2a2", "accept_quest1_b"}, -- When can I leave?
	}
}
aqzow_convo:addScreen(find_ship_b)

accept_quest1_b = ConvoScreen:new {
	id = "accept_quest1_b",
	leftDialog = "@conversation/corellia_rebel_tier3:s_90b730b5", -- Immediately.
	animation = "dismiss",
	stopConversation = "true",
	options = {}
}
aqzow_convo:addScreen(accept_quest1_b)

-- Quest 1 Spy Chain - Path C (from "Put me out there!")
spy_intro_c = ConvoScreen:new {
	id = "spy_intro_c",
	leftDialog = "@conversation/corellia_rebel_tier3:s_a2f4d2bd", -- We've learned that there was an Imperial spy operating on Yavin.
	stopConversation = "false",
	options = {
		{"@conversation/corellia_rebel_tier3:s_e078d62c", "spy_found_c"}, -- A spy? On Yavin? We've got secret hangars here!
	}
}
aqzow_convo:addScreen(spy_intro_c)

spy_found_c = ConvoScreen:new {
	id = "spy_found_c",
	leftDialog = "@conversation/corellia_rebel_tier3:s_88dd0a6e", -- They're not so secret anymore. The spy found them...
	animation = "nod_head_once",
	stopConversation = "false",
	options = {
		{"@conversation/corellia_rebel_tier3:s_15c65a41", "stop_him_c"}, -- If he tells the Empire about those hangars, they'll attack us for sure.
	}
}
aqzow_convo:addScreen(spy_found_c)

stop_him_c = ConvoScreen:new {
	id = "stop_him_c",
	leftDialog = "@conversation/corellia_rebel_tier3:s_4fca3087", -- You must stop him.
	stopConversation = "false",
	options = {
		{"@conversation/corellia_rebel_tier3:s_fd2da9fe", "find_ship_c"}, -- Oh, I'll stop him.
	}
}
aqzow_convo:addScreen(stop_him_c)

find_ship_c = ConvoScreen:new {
	id = "find_ship_c",
	leftDialog = "@conversation/corellia_rebel_tier3:s_f940636f", -- Find his ship. When you do, launch a space assault droid...
	stopConversation = "false",
	options = {
		{"@conversation/corellia_rebel_tier3:s_9d1fa2a2", "accept_quest1_c"}, -- When can I leave?
	}
}
aqzow_convo:addScreen(find_ship_c)

accept_quest1_c = ConvoScreen:new {
	id = "accept_quest1_c",
	leftDialog = "@conversation/corellia_rebel_tier3:s_90b730b5", -- Immediately.
	stopConversation = "true",
	options = {}
}
aqzow_convo:addScreen(accept_quest1_c)

-- Quest 1 Spy Chain - Path D (from bite_tongue)
spy_intro_d = ConvoScreen:new {
	id = "spy_intro_d",
	leftDialog = "@conversation/corellia_rebel_tier3:s_a0640cce", -- There was an Imperial spy operating on Yavin.
	stopConversation = "false",
	options = {
		{"@conversation/corellia_rebel_tier3:s_eaf68b63", "spy_found_d"}, -- A spy? On Yavin? He must not find our hangars!
	}
}
aqzow_convo:addScreen(spy_intro_d)

spy_found_d = ConvoScreen:new {
	id = "spy_found_d",
	leftDialog = "@conversation/corellia_rebel_tier3:s_5a165de6", -- He already has. And he escaped our forces. He's very good - and now he's making his way back to the Imperial fleet.
	stopConversation = "false",
	options = {
		{"@conversation/corellia_rebel_tier3:s_15c65a41", "stop_him_d"}, -- If he tells the Empire about those hangars, they'll attack us for sure.
	}
}
aqzow_convo:addScreen(spy_found_d)

stop_him_d = ConvoScreen:new {
	id = "stop_him_d",
	leftDialog = "@conversation/corellia_rebel_tier3:s_860361d0", -- He won't - IF you can stop him.
	stopConversation = "false",
	options = {
		{"@conversation/corellia_rebel_tier3:s_c1d821eb", "find_ship_d"}, -- Oh, I'll stop him all right.
	}
}
aqzow_convo:addScreen(stop_him_d)

find_ship_d = ConvoScreen:new {
	id = "find_ship_d",
	leftDialog = "@conversation/corellia_rebel_tier3:s_f940636f", -- Find his ship. When you do, launch a space assault droid...
	stopConversation = "false",
	options = {
		{"@conversation/corellia_rebel_tier3:s_9d1fa2a2", "accept_quest1_d"}, -- When can I leave?
	}
}
aqzow_convo:addScreen(find_ship_d)

accept_quest1_d = ConvoScreen:new {
	id = "accept_quest1_d",
	leftDialog = "@conversation/corellia_rebel_tier3:s_90b730b5", -- Immediately.
	stopConversation = "true",
	options = {}
}
aqzow_convo:addScreen(accept_quest1_d)

-- ========================================
-- Quest 2: Inspect Mission (Endor Smuggler Data)
-- ========================================

second_mission = ConvoScreen:new {
	id = "second_mission",
	leftDialog = "@conversation/corellia_rebel_tier3:s_c75a413", -- Good. You're here.
	animation = "beckon",
	stopConversation = "false",
	options = {
		{"@conversation/corellia_rebel_tier3:s_5688bc93", "ships_not_safe"}, -- Those Rebel ships are safe now.
		{"@conversation/corellia_rebel_tier3:s_f8e71988", "going_to_endor"}, -- I'm ready for my mission.
	}
}
aqzow_convo:addScreen(second_mission)

-- Path A: "Those Rebel ships are safe now"
ships_not_safe = ConvoScreen:new {
	id = "ships_not_safe",
	leftDialog = "@conversation/corellia_rebel_tier3:s_7169d6ae", -- No. They're not.
	animation = "shake_head_no",
	stopConversation = "false",
	options = {
		{"@conversation/corellia_rebel_tier3:s_6851e7af", "ships_sabotaged"}, -- What are you talking about? I escorted them out of here myself!
	}
}
aqzow_convo:addScreen(ships_not_safe)

ships_sabotaged = ConvoScreen:new {
	id = "ships_sabotaged",
	leftDialog = "@conversation/corellia_rebel_tier3:s_6e641199", -- Several ships were forced out of hyperspace in the Endor system. We suspect sabotage.
	animation = "explain",
	stopConversation = "false",
	options = {
		{"@conversation/corellia_rebel_tier3:s_be9c87b0", "find_out_spy"}, -- It must have been that spy!
		{"@conversation/corellia_rebel_tier3:s_b5bf7e24", "guard_repairs"}, -- What's my mission?
	}
}
aqzow_convo:addScreen(ships_sabotaged)

find_out_spy = ConvoScreen:new {
	id = "find_out_spy",
	leftDialog = "@conversation/corellia_rebel_tier3:s_7b1ee144", -- We are going to find out how he infiltrated us.
	animation = "nod_head_once",
	playerAnimation = "pound_fist_palm",
	stopConversation = "false",
	options = {
		{"@conversation/corellia_rebel_tier3:s_7a70c49d", "endor_dangerous"}, -- Endor is a dangerous system.
		{"@conversation/corellia_rebel_tier3:s_238ef790", "help_chain"}, -- Those ships have got to get moving, fast.
	}
}
aqzow_convo:addScreen(find_out_spy)

-- Path A-1: Endor dangerous chain
endor_dangerous = ConvoScreen:new {
	id = "endor_dangerous",
	leftDialog = "@conversation/corellia_rebel_tier3:s_1c95e862", -- It's infested with Hutt smugglers.
	stopConversation = "false",
	options = {
		{"@conversation/corellia_rebel_tier3:s_d75df92e", "could_attack"}, -- They could attack our ships!
	}
}
aqzow_convo:addScreen(endor_dangerous)

could_attack = ConvoScreen:new {
	id = "could_attack",
	leftDialog = "@conversation/corellia_rebel_tier3:s_ca8f086e", -- They would - if they thought they could get away with it.
	animation = "snap_finger1",
	stopConversation = "false",
	options = {
		{"@conversation/corellia_rebel_tier3:s_a4f58384", "help_repairs"}, -- We can't leave those Rebel ships out there, defenseless.
	}
}
aqzow_convo:addScreen(could_attack)

help_repairs = ConvoScreen:new {
	id = "help_repairs",
	leftDialog = "@conversation/corellia_rebel_tier3:s_4c82b8a", -- You catch on quick. I want you to get out there and help them with their repairs.
	animation = "tap_head",
	stopConversation = "false",
	options = {
		{"@conversation/corellia_rebel_tier3:s_8df62c80", "smugglers_info"}, -- First, I need data on the Endor system.
	}
}
aqzow_convo:addScreen(help_repairs)

smugglers_info = ConvoScreen:new {
	id = "smugglers_info",
	leftDialog = "@conversation/corellia_rebel_tier3:s_660e75ca", -- The smugglers have the information you need.
	stopConversation = "false",
	options = {
		{"@conversation/corellia_rebel_tier3:s_4c6cb546", "computers_info"}, -- The smugglers?
	}
}
aqzow_convo:addScreen(smugglers_info)

computers_info = ConvoScreen:new {
	id = "computers_info",
	leftDialog = "@conversation/corellia_rebel_tier3:s_1e51cf02", -- Their onboard computers carry valuable information about the system...
	stopConversation = "false",
	options = {
		{"@conversation/corellia_rebel_tier3:s_41072d99", "accept_quest2_a"}, -- And they're willing to share that with us?
	}
}
aqzow_convo:addScreen(computers_info)

accept_quest2_a = ConvoScreen:new {
	id = "accept_quest2_a",
	leftDialog = "@conversation/corellia_rebel_tier3:s_66eebb00", -- Their opinion doesn't matter. Hack into those ships and get that data.
	animation = "shrug_shoulders",
	stopConversation = "true",
	options = {}
}
aqzow_convo:addScreen(accept_quest2_a)

-- Path A-2: Help chain (ships got to get moving)
help_chain = ConvoScreen:new {
	id = "help_chain",
	leftDialog = "@conversation/corellia_rebel_tier3:s_2d9931cd", -- You can help. I want you to get out there and help those ships with their repairs.
	stopConversation = "false",
	options = {
		{"@conversation/corellia_rebel_tier3:s_6b7870ee", "hutt_smugglers"}, -- Of course - but first I need data on the Endor system.
	}
}
aqzow_convo:addScreen(help_chain)

hutt_smugglers = ConvoScreen:new {
	id = "hutt_smugglers",
	leftDialog = "@conversation/corellia_rebel_tier3:s_a47c19a7", -- You can get that from the Hutt smugglers.
	stopConversation = "false",
	options = {
		{"@conversation/corellia_rebel_tier3:s_a51658ea", "system_info_b"}, -- Excuse me?
	}
}
aqzow_convo:addScreen(hutt_smugglers)

system_info_b = ConvoScreen:new {
	id = "system_info_b",
	leftDialog = "@conversation/corellia_rebel_tier3:s_36a32229", -- They carry valuable system information in their onboard computers...
	stopConversation = "false",
	options = {
		{"@conversation/corellia_rebel_tier3:s_230806b6", "accept_quest2_b"}, -- And they're willing to tell us what they know?
	}
}
aqzow_convo:addScreen(system_info_b)

accept_quest2_b = ConvoScreen:new {
	id = "accept_quest2_b",
	leftDialog = "@conversation/corellia_rebel_tier3:s_4f685543", -- We don't plan on asking. Your job is to hack into those smuggling ships and get that data.
	stopConversation = "true",
	options = {}
}
aqzow_convo:addScreen(accept_quest2_b)

-- Path B: Guard repairs (from "What's my mission?")
guard_repairs = ConvoScreen:new {
	id = "guard_repairs",
	leftDialog = "@conversation/corellia_rebel_tier3:s_9edfea48", -- Get out there and guard them while they make repairs.
	stopConversation = "false",
	options = {
		{"@conversation/corellia_rebel_tier3:s_c8489609", "smuggler_data"}, -- Will do. But first I need information on Endor.
	}
}
aqzow_convo:addScreen(guard_repairs)

smuggler_data = ConvoScreen:new {
	id = "smuggler_data",
	leftDialog = "@conversation/corellia_rebel_tier3:s_7a38a99d", -- You can get that data from Hutt smugglers.
	animation = "nod_head_once",
	stopConversation = "false",
	options = {
		{"@conversation/corellia_rebel_tier3:s_96a4f294", "system_info_c"}, -- Hutt smugglers?
	}
}
aqzow_convo:addScreen(smuggler_data)

system_info_c = ConvoScreen:new {
	id = "system_info_c",
	leftDialog = "@conversation/corellia_rebel_tier3:s_36a32229", -- They carry valuable system information in their onboard computers...
	stopConversation = "false",
	options = {
		{"@conversation/corellia_rebel_tier3:s_230806b6", "accept_quest2_c"}, -- And they're willing to tell us what they know?
	}
}
aqzow_convo:addScreen(system_info_c)

accept_quest2_c = ConvoScreen:new {
	id = "accept_quest2_c",
	leftDialog = "@conversation/corellia_rebel_tier3:s_4f685543", -- We don't plan on asking. Your job is to hack into those smuggling ships and get that data.
	stopConversation = "true",
	options = {}
}
aqzow_convo:addScreen(accept_quest2_c)

-- Path C: Going to Endor (from "I'm ready for my mission")
going_to_endor = ConvoScreen:new {
	id = "going_to_endor",
	leftDialog = "@conversation/corellia_rebel_tier3:s_4519b6a1", -- You're going to Endor. Several ships from our fleet are there. They were forced out of hyperspace.
	stopConversation = "false",
	options = {
		{"@conversation/corellia_rebel_tier3:s_5a2f7b49", "sabotage"}, -- By what?
	}
}
aqzow_convo:addScreen(going_to_endor)

sabotage = ConvoScreen:new {
	id = "sabotage",
	leftDialog = "@conversation/corellia_rebel_tier3:s_6c04c8a5", -- Who knows? Could be sabotage. You're going to need data on the system.
	animation = "shrug_shoulders",
	stopConversation = "false",
	options = {
		{"@conversation/corellia_rebel_tier3:s_89d52fe6", "not_uploaded"}, -- Is it uploaded to my ship?
	}
}
aqzow_convo:addScreen(sabotage)

not_uploaded = ConvoScreen:new {
	id = "not_uploaded",
	leftDialog = "@conversation/corellia_rebel_tier3:s_3dd2eade", -- I'm afraid not. You'll have to get it yourself - from Hutt smugglers.
	animation = "shake_head_no",
	stopConversation = "false",
	options = {
		{"@conversation/corellia_rebel_tier3:s_e37c2bae", "accept_quest2_d"}, -- Smugglers?
	}
}
aqzow_convo:addScreen(not_uploaded)

accept_quest2_d = ConvoScreen:new {
	id = "accept_quest2_d",
	leftDialog = "@conversation/corellia_rebel_tier3:s_a4f4a27", -- Their ships have more data on Endor than we do. Hack into their onboard computers and see what's there.
	stopConversation = "true",
	options = {}
}
aqzow_convo:addScreen(accept_quest2_d)

-- ========================================
-- Quest 3: Delivery Mission (Nym Smuggler Intel)
-- ========================================

third_mission = ConvoScreen:new {
	id = "third_mission",
	leftDialog = "@conversation/corellia_rebel_tier3:s_d40f6011", -- We've definitely got the Emperor's attention. This system is lousy with Imperial forces!
	animation = "beckon",
	stopConversation = "false",
	options = {
		{"@conversation/corellia_rebel_tier3:s_c4d60644", "how_did_you_do"}, -- I'll say.
		{"@conversation/corellia_rebel_tier3:s_5e62a10a", "offense_time_e"}, -- Give me a mission! I'm ready to fight.
	}
}
aqzow_convo:addScreen(third_mission)

-- "I'll say" path
how_did_you_do = ConvoScreen:new {
	id = "how_did_you_do",
	leftDialog = "@conversation/corellia_rebel_tier3:s_2370b50f", -- How did you do up there?
	stopConversation = "false",
	options = {
		{"@conversation/corellia_rebel_tier3:s_74ea771e", "offense_time_a"}, -- Those Imperials didn't know what hit 'em.
		{"@conversation/corellia_rebel_tier3:s_f8e71988", "that_bad"}, -- I'm ready for my mission.
	}
}
aqzow_convo:addScreen(how_did_you_do)

-- Path A: "Those Imperials didn't know what hit 'em"
offense_time_a = ConvoScreen:new {
	id = "offense_time_a",
	leftDialog = "@conversation/corellia_rebel_tier3:s_83adb39e", -- We're through playing defense. It's time to hit these Imperials with everything we've got.
	animation = "point_forward",
	playerAnimation = "flex_biceps",
	stopConversation = "false",
	options = {
		{"@conversation/corellia_rebel_tier3:s_84180d3b", "nym_smugglers_a"}, -- Sounds good to me!
	}
}
aqzow_convo:addScreen(offense_time_a)

nym_smugglers_a = ConvoScreen:new {
	id = "nym_smugglers_a",
	leftDialog = "@conversation/corellia_rebel_tier3:s_2cf76f20", -- The Empire has moved one of their fleets to the Endor system... The Nym smugglers know all about that fleet.
	animation = "nod_head_once",
	playerAnimation = "nod_head_once",
	stopConversation = "false",
	options = {
		{"@conversation/corellia_rebel_tier3:s_225227ba", "accept_quest3_a"}, -- Will they give us that information?
	}
}
aqzow_convo:addScreen(nym_smugglers_a)

accept_quest3_a = ConvoScreen:new {
	id = "accept_quest3_a",
	leftDialog = "@conversation/corellia_rebel_tier3:s_7e4588fd", -- Absolutely. They don't like the Empire any more than we do. I want you to make contact with one of Nym's smugglers...
	stopConversation = "true",
	options = {}
}
aqzow_convo:addScreen(accept_quest3_a)

-- Path B: "I'm ready for my mission" → "that bad, eh?"
that_bad = ConvoScreen:new {
	id = "that_bad",
	leftDialog = "@conversation/corellia_rebel_tier3:s_20715042", -- It was that bad, eh?
	animation = "laugh",
	stopConversation = "false",
	options = {
		{"@conversation/corellia_rebel_tier3:s_beaa457b", "offense_time_b"}, -- I SAID I'm ready for my mission.
		{"@conversation/corellia_rebel_tier3:s_5d8e37f3", "havent_seen_greatness"}, -- I was GREAT out there!
	}
}
aqzow_convo:addScreen(that_bad)

offense_time_b = ConvoScreen:new {
	id = "offense_time_b",
	leftDialog = "@conversation/corellia_rebel_tier3:s_83adb39e", -- We're through playing defense...
	animation = "point_forward",
	stopConversation = "false",
	options = {
		{"@conversation/corellia_rebel_tier3:s_84180d3b", "nym_smugglers_b"}, -- Sounds good to me!
	}
}
aqzow_convo:addScreen(offense_time_b)

nym_smugglers_b = ConvoScreen:new {
	id = "nym_smugglers_b",
	leftDialog = "@conversation/corellia_rebel_tier3:s_2cf76f20", -- The Empire has moved one of their fleets to the Endor system...
	animation = "nod_head_once",
	playerAnimation = "nod_head_once",
	stopConversation = "false",
	options = {
		{"@conversation/corellia_rebel_tier3:s_225227ba", "accept_quest3_b"}, -- Will they give us that information?
	}
}
aqzow_convo:addScreen(nym_smugglers_b)

accept_quest3_b = ConvoScreen:new {
	id = "accept_quest3_b",
	leftDialog = "@conversation/corellia_rebel_tier3:s_7e4588fd", -- Absolutely...
	stopConversation = "true",
	options = {}
}
aqzow_convo:addScreen(accept_quest3_b)

-- Path C: "I was GREAT out there!" → haven't seen greatness → watch mouth
havent_seen_greatness = ConvoScreen:new {
	id = "havent_seen_greatness",
	leftDialog = "@conversation/corellia_rebel_tier3:s_281a242e", -- Ha! You haven't SEEN greatness until you've seen me in action.
	animation = "laugh",
	playerAnimation = "flex_biceps",
	stopConversation = "false",
	options = {
		{"@conversation/corellia_rebel_tier3:s_cae661b8", "watch_mouth_q3"}, -- Yeah right. That's why you're down here assigning missions.
		{"@conversation/corellia_rebel_tier3:s_f8e71988", "offense_time_d"}, -- I'm ready for my mission.
	}
}
aqzow_convo:addScreen(havent_seen_greatness)

watch_mouth_q3 = ConvoScreen:new {
	id = "watch_mouth_q3",
	leftDialog = "@conversation/corellia_rebel_tier3:s_96534c26", -- Watch your mouth. Remember what I told you before.
	animation = "wave_finger_warning",
	stopConversation = "false",
	options = {
		{"@conversation/corellia_rebel_tier3:s_f8e71988", "offense_time_c"}, -- I'm ready for my mission.
	}
}
aqzow_convo:addScreen(watch_mouth_q3)

offense_time_c = ConvoScreen:new {
	id = "offense_time_c",
	leftDialog = "@conversation/corellia_rebel_tier3:s_83adb39e", -- We're through playing defense...
	animation = "point_forward",
	stopConversation = "false",
	options = {
		{"@conversation/corellia_rebel_tier3:s_84180d3b", "nym_smugglers_c"}, -- Sounds good to me!
	}
}
aqzow_convo:addScreen(offense_time_c)

nym_smugglers_c = ConvoScreen:new {
	id = "nym_smugglers_c",
	leftDialog = "@conversation/corellia_rebel_tier3:s_2cf76f20", -- The Empire has moved one of their fleets to the Endor system...
	animation = "nod_head_once",
	playerAnimation = "nod_head_once",
	stopConversation = "false",
	options = {
		{"@conversation/corellia_rebel_tier3:s_225227ba", "accept_quest3_c"}, -- Will they give us that information?
	}
}
aqzow_convo:addScreen(nym_smugglers_c)

accept_quest3_c = ConvoScreen:new {
	id = "accept_quest3_c",
	leftDialog = "@conversation/corellia_rebel_tier3:s_7e4588fd", -- Absolutely...
	stopConversation = "true",
	options = {}
}
aqzow_convo:addScreen(accept_quest3_c)

-- Path D: Direct from "haven't seen greatness" → "I'm ready"
offense_time_d = ConvoScreen:new {
	id = "offense_time_d",
	leftDialog = "@conversation/corellia_rebel_tier3:s_83adb39e", -- We're through playing defense...
	animation = "point_forward",
	stopConversation = "false",
	options = {
		{"@conversation/corellia_rebel_tier3:s_84180d3b", "nym_smugglers_d"}, -- Sounds good to me!
	}
}
aqzow_convo:addScreen(offense_time_d)

nym_smugglers_d = ConvoScreen:new {
	id = "nym_smugglers_d",
	leftDialog = "@conversation/corellia_rebel_tier3:s_2cf76f20", -- The Empire has moved one of their fleets to the Endor system...
	animation = "nod_head_once",
	playerAnimation = "nod_head_once",
	stopConversation = "false",
	options = {
		{"@conversation/corellia_rebel_tier3:s_225227ba", "accept_quest3_d"}, -- Will they give us that information?
	}
}
aqzow_convo:addScreen(nym_smugglers_d)

accept_quest3_d = ConvoScreen:new {
	id = "accept_quest3_d",
	leftDialog = "@conversation/corellia_rebel_tier3:s_7e4588fd", -- Absolutely...
	stopConversation = "true",
	options = {}
}
aqzow_convo:addScreen(accept_quest3_d)

-- Path E: Shortcut from "Give me a mission! I'm ready to fight."
offense_time_e = ConvoScreen:new {
	id = "offense_time_e",
	leftDialog = "@conversation/corellia_rebel_tier3:s_83adb39e", -- We're through playing defense...
	animation = "point_forward",
	stopConversation = "false",
	options = {
		{"@conversation/corellia_rebel_tier3:s_84180d3b", "nym_smugglers_e"}, -- Sounds good to me!
	}
}
aqzow_convo:addScreen(offense_time_e)

nym_smugglers_e = ConvoScreen:new {
	id = "nym_smugglers_e",
	leftDialog = "@conversation/corellia_rebel_tier3:s_2cf76f20", -- The Empire has moved one of their fleets to the Endor system...
	animation = "nod_head_once",
	playerAnimation = "nod_head_once",
	stopConversation = "false",
	options = {
		{"@conversation/corellia_rebel_tier3:s_225227ba", "accept_quest3_e"}, -- Will they give us that information?
	}
}
aqzow_convo:addScreen(nym_smugglers_e)

accept_quest3_e = ConvoScreen:new {
	id = "accept_quest3_e",
	leftDialog = "@conversation/corellia_rebel_tier3:s_7e4588fd", -- Absolutely...
	stopConversation = "true",
	options = {}
}
aqzow_convo:addScreen(accept_quest3_e)

-- ========================================
-- Quest 4: Assassinate Mission (Imperial Pilot Intercept)
-- ========================================

fourth_mission = ConvoScreen:new {
	id = "fourth_mission",
	leftDialog = "@conversation/corellia_rebel_tier3:s_a20d4e92", -- Hm. You're quite a pilot.
	animation = "rub_chin_thoughtful",
	stopConversation = "false",
	options = {
		{"@conversation/corellia_rebel_tier3:s_90b3d410", "arrogant"}, -- Of course I am.
		{"@conversation/corellia_rebel_tier3:s_efd88602", "dont_get_pleased"}, -- Glad you think so.
		{"@conversation/corellia_rebel_tier3:s_4cff5cf8", "imperial_pilot_c"}, -- I just want another mission.
	}
}
aqzow_convo:addScreen(fourth_mission)

-- Path A: "Of course I am" → arrogant
arrogant = ConvoScreen:new {
	id = "arrogant",
	leftDialog = "@conversation/corellia_rebel_tier3:s_313f990a", -- Sounds like you're one of our most arrogant pilots as well.
	playerAnimation = "pose_proudly",
	stopConversation = "false",
	options = {
		{"@conversation/corellia_rebel_tier3:s_a09da7f1", "i_do"}, -- You like that?
	}
}
aqzow_convo:addScreen(arrogant)

i_do = ConvoScreen:new {
	id = "i_do",
	leftDialog = "@conversation/corellia_rebel_tier3:s_6ebb13d3", -- I do.
	animation = "nod_head_once",
	stopConversation = "false",
	options = {
		{"@conversation/corellia_rebel_tier3:s_1e76a9f3", "imperial_pilot_a"}, -- Give me my mission. I can handle anything.
	}
}
aqzow_convo:addScreen(i_do)

imperial_pilot_a = ConvoScreen:new {
	id = "imperial_pilot_a",
	leftDialog = "@conversation/corellia_rebel_tier3:s_94dbd157", -- The Empire is sending one of their best fighter pilots to this location. His orders are simple: terminate our fleet.
	animation = "explain",
	stopConversation = "false",
	options = {
		{"@conversation/corellia_rebel_tier3:s_31a0221f", "irrelevant_a"}, -- What's his ETA?
	}
}
aqzow_convo:addScreen(imperial_pilot_a)

irrelevant_a = ConvoScreen:new {
	id = "irrelevant_a",
	leftDialog = "@conversation/corellia_rebel_tier3:s_4a2c18a8", -- That is irrelevant. We are sending our best pilot to make sure that he never reaches the Endor system.
	playerAnimation = "check_wrist_device",
	stopConversation = "false",
	options = {
		{"@conversation/corellia_rebel_tier3:s_8f422d5c", "accept_quest4_a"}, -- And that would be me.
	}
}
aqzow_convo:addScreen(irrelevant_a)

accept_quest4_a = ConvoScreen:new {
	id = "accept_quest4_a",
	leftDialog = "@conversation/corellia_rebel_tier3:s_26995dc5", -- How did you know? I want you to intercept him in the Dathomir system. Get going.
	animation = "laugh",
	playerAnimation = "point_to_self",
	stopConversation = "true",
	options = {}
}
aqzow_convo:addScreen(accept_quest4_a)

-- Path B: "Glad you think so"
dont_get_pleased = ConvoScreen:new {
	id = "dont_get_pleased",
	leftDialog = "@conversation/corellia_rebel_tier3:s_2168be5a", -- Don't get too pleased with yourself. We're about to find out what you're REALLY made of.
	animation = "wave_finger_warning",
	playerAnimation = "pose_proudly",
	stopConversation = "false",
	options = {
		{"@conversation/corellia_rebel_tier3:s_1e76a9f3", "imperial_pilot_b"}, -- Give me my mission. I can handle anything.
	}
}
aqzow_convo:addScreen(dont_get_pleased)

imperial_pilot_b = ConvoScreen:new {
	id = "imperial_pilot_b",
	leftDialog = "@conversation/corellia_rebel_tier3:s_109a5e4a", -- The Empire is sending one of their best fighter pilots here. His orders are simple: terminate our fleet.
	animation = "explain",
	stopConversation = "false",
	options = {
		{"@conversation/corellia_rebel_tier3:s_31a0221f", "irrelevant_b"}, -- What's his ETA?
	}
}
aqzow_convo:addScreen(imperial_pilot_b)

irrelevant_b = ConvoScreen:new {
	id = "irrelevant_b",
	leftDialog = "@conversation/corellia_rebel_tier3:s_4a2c18a8", -- That is irrelevant. We are sending our best pilot to make sure that he never reaches the Endor system.
	animation = "shake_head_no",
	playerAnimation = "check_wrist_device",
	stopConversation = "false",
	options = {
		{"@conversation/corellia_rebel_tier3:s_8f422d5c", "accept_quest4_b"}, -- And that would be me.
	}
}
aqzow_convo:addScreen(irrelevant_b)

accept_quest4_b = ConvoScreen:new {
	id = "accept_quest4_b",
	leftDialog = "@conversation/corellia_rebel_tier3:s_26995dc5", -- How did you know? I want you to intercept him in the Dathomir system. Get going.
	animation = "laugh",
	playerAnimation = "point_to_self",
	stopConversation = "true",
	options = {}
}
aqzow_convo:addScreen(accept_quest4_b)

-- Path C: "I just want another mission" (direct)
imperial_pilot_c = ConvoScreen:new {
	id = "imperial_pilot_c",
	leftDialog = "@conversation/corellia_rebel_tier3:s_109a5e4a", -- The Empire is sending one of their best fighter pilots here. His orders are simple: terminate our fleet.
	animation = "explain",
	playerAnimation = "shrug_shoulders",
	stopConversation = "false",
	options = {
		{"@conversation/corellia_rebel_tier3:s_31a0221f", "irrelevant_c"}, -- What's his ETA?
	}
}
aqzow_convo:addScreen(imperial_pilot_c)

irrelevant_c = ConvoScreen:new {
	id = "irrelevant_c",
	leftDialog = "@conversation/corellia_rebel_tier3:s_fed6ceb3", -- That is irrelevant. We are sending our best pilot to make sure that he never reaches the Endor system.
	playerAnimation = "check_wrist_device",
	stopConversation = "false",
	options = {
		{"@conversation/corellia_rebel_tier3:s_8f422d5c", "accept_quest4_c"}, -- And that would be me.
	}
}
aqzow_convo:addScreen(irrelevant_c)

accept_quest4_c = ConvoScreen:new {
	id = "accept_quest4_c",
	leftDialog = "@conversation/corellia_rebel_tier3:s_26995dc5", -- How did you know? I want you to intercept him in the Dathomir system. Get going.
	animation = "laugh",
	playerAnimation = "point_to_self",
	stopConversation = "true",
	options = {}
}
aqzow_convo:addScreen(accept_quest4_c)

addConversationTemplate("aqzow_convo", aqzow_convo)
