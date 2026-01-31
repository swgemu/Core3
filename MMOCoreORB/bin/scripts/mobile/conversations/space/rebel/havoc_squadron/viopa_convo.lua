viopa_convo = ConvoTemplate:new {
	initialScreen = "",
	templateType = "Lua",
	luaClassHandler = "viopaConvoHandler",
	screens = {}
}

-- Not a Pilot (no JTL skills)
viopa_convo_no_jtl = ConvoScreen:new {
	id = "no_jtl",
	leftDialog = "@conversation/lok_rebel_trainer_2:s_14fcd38b", -- I don't know what you're doing here, but I'm certain that you shouldn't be talking to me.
	stopConversation = "true",
	options = {}
}
viopa_convo:addScreen(viopa_convo_no_jtl)

-- Imperial Pilot
viopa_convo_imperial_pilot = ConvoScreen:new {
	id = "imperial_pilot",
	leftDialog = "@conversation/lok_rebel_trainer_2:s_ab3a1cf4", -- Does Lord Nym know that you are in here?
	animation = "rub_chin_thoughtful",
	stopConversation = "true",
	options = {}
}
viopa_convo:addScreen(viopa_convo_imperial_pilot)

-- Neutral Pilot
viopa_convo_neutral_pilot = ConvoScreen:new {
	id = "neutral_pilot",
	leftDialog = "@conversation/lok_rebel_trainer_2:s_422f9bfa", -- Are you one of Nym's employees?
	animation = "rub_chin_thoughtful",
	stopConversation = "true",
	options = {}
}
viopa_convo:addScreen(viopa_convo_neutral_pilot)

-- Non-Havoc Rebel Pilot (wrong squadron track)
viopa_convo_non_havoc_pilot = ConvoScreen:new {
	id = "non_havoc_pilot",
	leftDialog = "@conversation/lok_rebel_trainer_2:s_148ee1c2", -- What are you doing here? I heard that you were working for a different part of the Alliance Navy.
	stopConversation = "false",
	options = {
		{"@conversation/lok_rebel_trainer_2:s_1583743c", "duty_missions"}, -- Do you have any missions I could fly?
	}
}
viopa_convo:addScreen(viopa_convo_non_havoc_pilot)

-- Not Rebel Pilot (rebel non-member)
viopa_convo_not_rebel_pilot = ConvoScreen:new {
	id = "not_rebel_pilot",
	leftDialog = "@conversation/lok_rebel_trainer_2:s_b3a02be2", -- What are you doing here, %TU? I heard you were working for a different part of the Alliance Navy. It's a shame, I could have used a skilled pilot like you.
	animation = "bow3",
	playerAnimation = "greet",
	stopConversation = "true",
	options = {}
}
viopa_convo:addScreen(viopa_convo_not_rebel_pilot)

-- Not Ready (hasn't completed Tier 1)
viopa_convo_not_ready = ConvoScreen:new {
	id = "not_ready",
	leftDialog = "@conversation/lok_rebel_trainer_2:s_b02ee4b4", -- I'm sure you have important things to attend to, then. Sorry to interrupt you.
	stopConversation = "true",
	options = {}
}
viopa_convo:addScreen(viopa_convo_not_ready)

-- Has Active Mission
viopa_convo_has_mission = ConvoScreen:new {
	id = "has_mission",
	leftDialog = "@conversation/lok_rebel_trainer_2:s_2baec20", -- I like this palace too, %NU, but your services are urgently required elsewhere. Get out there and show them why you are my favorite pilot.
	animation = "bow3",
	playerAnimation = "greet",
	stopConversation = "true",
	options = {}
}
viopa_convo:addScreen(viopa_convo_has_mission)

-- Has Another Mission (on different quest)
viopa_convo_another_mission = ConvoScreen:new {
	id = "another_mission",
	leftDialog = "@conversation/lok_rebel_trainer_2:s_d356f8d", -- I don't mean to overstep my bounds, but I believe that you have obligations elsewhere. Finish up, and then we can talk.
	stopConversation = "true",
	options = {}
}
viopa_convo:addScreen(viopa_convo_another_mission)

-- Negative Faction Standing
viopa_convo_negative_faction = ConvoScreen:new {
	id = "negative_faction",
	leftDialog = "@conversation/lok_rebel_trainer_2:s_4104f818", -- My dear, you are in big trouble.
	animation = "cover_mouth",
	stopConversation = "false",
	options = {
		{"@conversation/lok_rebel_trainer_2:s_e00ac98e", "faction_explain"}, -- What happened?
	}
}
viopa_convo:addScreen(viopa_convo_negative_faction)

-- Faction Explain
viopa_convo_faction_explain = ConvoScreen:new {
	id = "faction_explain",
	leftDialog = "@conversation/lok_rebel_trainer_2:s_dd8c097b", -- You've been grounded. The intelligence department delivered a scathing report on you. It's terrible!
	animation = "weeping",
	stopConversation = "true",
	options = {}
}
viopa_convo:addScreen(viopa_convo_faction_explain)

-- ============================================================================
-- Introduction Tree (isCorrectRebelPilot - first time meeting Viopa)
-- ============================================================================

-- Introduction (Level 1)
viopa_convo_introduction = ConvoScreen:new {
	id = "introduction",
	leftDialog = "@conversation/lok_rebel_trainer_2:s_15250124", -- Greetings %TU. My name is Viopa. I function as the Alliance's go-between for the Rebellion and Lord Nym...
	animation = "bow3",
	playerAnimation = "wave1",
	stopConversation = "false",
	options = {
		{"@conversation/lok_rebel_trainer_2:s_65f334d5", "intro_yes_milady"}, -- Yes milady, so I've been told.
		{"@conversation/lok_rebel_trainer_2:s_334b8b3a", "intro_under_woman"}, -- No one told me I would work under a woman.
		{"@conversation/lok_rebel_trainer_2:s_8125c052", "intro_decent_creds"}, -- Working for Nym! This should finally give some decent creds.
		{"@conversation/lok_rebel_trainer_2:s_9d418971", "intro_decline_mistaken"}, -- I'm sorry, milady. You must have me mistaken for someone else.
	}
}
viopa_convo:addScreen(viopa_convo_introduction)

-- Branch 181: "Yes milady" path (Level 2a)
viopa_convo_intro_yes_milady = ConvoScreen:new {
	id = "intro_yes_milady",
	leftDialog = "@conversation/lok_rebel_trainer_2:s_e58d7043", -- Excellent. I'm certain that I will enjoy getting to know you as we work together %NU. We have a few duties that could use your expertise my friend, are you ready to get started?
	animation = "explain",
	stopConversation = "false",
	options = {
		{"@conversation/lok_rebel_trainer_2:s_7ac528cc", "accept_intro"}, -- Yes, milady. What do you have for me?
		{"@conversation/lok_rebel_trainer_2:s_9990d560", "intro_nym_pirate"}, -- What is the Alliance doing with Nym? Isn't he a pirate?
	}
}
viopa_convo:addScreen(viopa_convo_intro_yes_milady)

-- Branch 182: "Nym is a pirate" sub-path (Level 3a)
viopa_convo_intro_nym_pirate = ConvoScreen:new {
	id = "intro_nym_pirate",
	leftDialog = "@conversation/lok_rebel_trainer_2:s_129e1011", -- Some people may call him a pirate, and he doesn't exactly follow the laws of the Empire but neither do we, mm? In times like these, we need all the help we can get. Lord Nym is actually a nice person once you get to know him.
	animation = "dismiss",
	stopConversation = "false",
	options = {
		{"@conversation/lok_rebel_trainer_2:s_97bbc2e4", "accept_intro"}, -- I suppose. All right, you said you had some things for me to do?
		{"@conversation/lok_rebel_trainer_2:s_db065042", "intro_overreacting"}, -- Well I won't stand for it, I'm going to ask to be reassigned.
	}
}
viopa_convo:addScreen(viopa_convo_intro_nym_pirate)

-- Branch 183: "Ask to be reassigned" sub-path (Level 4a)
viopa_convo_intro_overreacting = ConvoScreen:new {
	id = "intro_overreacting",
	leftDialog = "@conversation/lok_rebel_trainer_2:s_62fa8365", -- I really think you are overreacting, my friend. This is war and Nym is good ally. His help is invaluable in the fight against the Empire.
	stopConversation = "false",
	options = {
		{"@conversation/lok_rebel_trainer_2:s_c103ad7e", "accept_intro"}, -- Hmm. Okay, I guess it's a necessity. What do you need me to do?
		{"@conversation/lok_rebel_trainer_2:s_c6f65083", "intro_decline_closeminded"}, -- He's no better than the Empire. I'm out of here!
	}
}
viopa_convo:addScreen(viopa_convo_intro_overreacting)

-- Branch 185: "Work under a woman" path (Level 2b)
viopa_convo_intro_under_woman = ConvoScreen:new {
	id = "intro_under_woman",
	leftDialog = "@conversation/lok_rebel_trainer_2:s_438969d3", -- Well life is just full of pleasant surprises like that. Now we have a lot of things for a skilled pilot to do. Are you ready to get started?
	stopConversation = "false",
	options = {
		{"@conversation/lok_rebel_trainer_2:s_f6927823", "intro_fishy_operation"}, -- No. This whole operation seems fishy. Working with a pirate!
		{"@conversation/lok_rebel_trainer_2:s_1ec75f6d", "accept_intro"}, -- I'll live with it. Let me show these goons how it's done.
	}
}
viopa_convo:addScreen(viopa_convo_intro_under_woman)

-- Branch 186: "Fishy operation" sub-path (Level 3b)
viopa_convo_intro_fishy_operation = ConvoScreen:new {
	id = "intro_fishy_operation",
	leftDialog = "@conversation/lok_rebel_trainer_2:s_44dd253a", -- That's such a rude thing to say. Some people may call him a pirate, and he doesn't exactly follow the laws of the Empire but neither do we, mm? In times like these, we need all the help we can get. Lord Nym is actually a nice person once you get to know him.
	stopConversation = "false",
	options = {
		{"@conversation/lok_rebel_trainer_2:s_d21eee5e", "accept_intro"}, -- Fine. Let me show these goons how it's done.
		{"@conversation/lok_rebel_trainer_2:s_c6f65083", "intro_decline_ignorance"}, -- He's no better than the Empire. I'm out of here!
	}
}
viopa_convo:addScreen(viopa_convo_intro_fishy_operation)

-- Branch 188: "Decent creds" path (Level 2c)
viopa_convo_intro_decent_creds = ConvoScreen:new {
	id = "intro_decent_creds",
	leftDialog = "@conversation/lok_rebel_trainer_2:s_50dbe32c", -- You sound like you've spent too much time in the palace already, my friend. Though I can't deny that working here has certain... privileges. I'm sure you will fit right in. Now we have plenty of tasks for you. Ready to work?
	stopConversation = "false",
	options = {
		{"@conversation/lok_rebel_trainer_2:s_1df58e48", "accept_intro"}, -- Do I get to keep the loot? I mean, I'm ready.
		{"@conversation/lok_rebel_trainer_2:s_e2539e81", "intro_nym_greedy"}, -- On second thought, I've heard that Nym is pretty greedy.
	}
}
viopa_convo:addScreen(viopa_convo_intro_decent_creds)

-- Branch 189: "Nym is greedy" sub-path (Level 3c)
viopa_convo_intro_nym_greedy = ConvoScreen:new {
	id = "intro_nym_greedy",
	leftDialog = "@conversation/lok_rebel_trainer_2:s_bcff0c86", -- I thought you were a respected pilot of the Alliance, not a mercenary. Even so, I'm sure you would find the compensation adequate and the experience thrilling.
	stopConversation = "false",
	options = {
		{"@conversation/lok_rebel_trainer_2:s_17e79a2c", "accept_intro"}, -- Any advance payment? Okay fine, what do you need done?
		{"@conversation/lok_rebel_trainer_2:s_98672851", "intro_decline_mercenary"}, -- I think I'd be better off with gigs I know would pay well. See ya!
	}
}
viopa_convo:addScreen(viopa_convo_intro_nym_greedy)

-- Introduction Decline: Mistaken identity
viopa_convo_intro_decline_mistaken = ConvoScreen:new {
	id = "intro_decline_mistaken",
	leftDialog = "@conversation/lok_rebel_trainer_2:s_5c191b57", -- Oh I'm so sorry. Enjoy your stay at Lord Nym's palace then.
	animation = "dismiss",
	stopConversation = "true",
	options = {}
}
viopa_convo:addScreen(viopa_convo_intro_decline_mistaken)

-- Introduction Decline: Close-minded (from overreacting path)
viopa_convo_intro_decline_closeminded = ConvoScreen:new {
	id = "intro_decline_closeminded",
	leftDialog = "@conversation/lok_rebel_trainer_2:s_bc44d715", -- I did not think you were so close-minded, %TU. Hopefully you'll find a spot better suited for you somewhere else in the Rebellion. Farewell.
	stopConversation = "true",
	options = {}
}
viopa_convo:addScreen(viopa_convo_intro_decline_closeminded)

-- Introduction Decline: Ignorance (from fishy operation path)
viopa_convo_intro_decline_ignorance = ConvoScreen:new {
	id = "intro_decline_ignorance",
	leftDialog = "@conversation/lok_rebel_trainer_2:s_7348150", -- We don't need that kind of ignorance in the Rebellion. I do hope you come to your senses.
	stopConversation = "true",
	options = {}
}
viopa_convo:addScreen(viopa_convo_intro_decline_ignorance)

-- Introduction Decline: Mercenary (from nym greedy path)
viopa_convo_intro_decline_mercenary = ConvoScreen:new {
	id = "intro_decline_mercenary",
	leftDialog = "@conversation/lok_rebel_trainer_2:s_b0d973e8", -- Sad indeed, I had high hopes for you %TU. Good luck in your adventures, maybe I'll see you some day again.
	stopConversation = "true",
	options = {}
}
viopa_convo:addScreen(viopa_convo_intro_decline_mercenary)

-- Accept Intro (all accept paths converge here - sets attempted flag, shows duty briefing)
viopa_convo_accept_intro = ConvoScreen:new {
	id = "accept_intro",
	leftDialog = "@conversation/lok_rebel_trainer_2:s_565951d5", -- Lord Nym has asked for our help in stealing some Corsair ships. We have some smugglers that require an escort through Imperial areas and we have the chance to strike a blow to the Empire by attacking some of their patrols. We want you to assist with these duties until you feel you have enough experience to proceed with training but they are strictly volunteer assignments and can be aborted at any time.
	animation = "explain",
	stopConversation = "false",
	options = {
		{"@conversation/lok_rebel_trainer_2:s_e02126d9", "intro_recovery_duty"}, -- Stealing some Corsair ships sounds like fun.
		{"@conversation/lok_rebel_trainer_2:s_cd3e2b38", "intro_escort_duty"}, -- I'll help some of our smugglers sneak by the Empire.
		{"@conversation/lok_rebel_trainer_2:s_1dfeca09", "intro_destroy_duty"}, -- I've been itching to take down some TIE fighters.
		{"@conversation/lok_rebel_trainer_2:s_cd1a5817", "intro_duty_goodbye"}, -- I have some quick things I need to fix first. I will be back.
	}
}
viopa_convo:addScreen(viopa_convo_accept_intro)

-- Intro Duty: Recovery (stealing Corsair ships)
viopa_convo_intro_recovery_duty = ConvoScreen:new {
	id = "intro_recovery_duty",
	leftDialog = "@conversation/lok_rebel_trainer_2:s_a0ee0d37", -- Yes. It will give you the chance to try the pirate lifestyle for a day, sweetie. You will receive more information once you're up in space. Good luck dear!
	stopConversation = "true",
	options = {}
}
viopa_convo:addScreen(viopa_convo_intro_recovery_duty)

-- Intro Duty: Escort (smuggler escort)
viopa_convo_intro_escort_duty = ConvoScreen:new {
	id = "intro_escort_duty",
	leftDialog = "@conversation/lok_rebel_trainer_2:s_8447c7d7", -- Great! It's been a madhouse up there lately so be careful sweetie.
	stopConversation = "true",
	options = {}
}
viopa_convo:addScreen(viopa_convo_intro_escort_duty)

-- Intro Duty: Destroy (TIE fighters)
viopa_convo_intro_destroy_duty = ConvoScreen:new {
	id = "intro_destroy_duty",
	leftDialog = "@conversation/lok_rebel_trainer_2:s_ca434bbe", -- Then I can help you scratch that itch, dear. Get up in orbit; you will get more information once you are there. Be careful out there, sweetie.
	stopConversation = "true",
	options = {}
}
viopa_convo:addScreen(viopa_convo_intro_destroy_duty)

-- Intro Duty: Goodbye (not ready yet)
viopa_convo_intro_duty_goodbye = ConvoScreen:new {
	id = "intro_duty_goodbye",
	leftDialog = "@conversation/lok_rebel_trainer_2:s_17653741", -- All right, sweetie. Don't take too long, though. We could really use your help.
	stopConversation = "true",
	options = {}
}
viopa_convo:addScreen(viopa_convo_intro_duty_goodbye)

-- ============================================================================
-- Mission 1 Flow: readyForMission1
-- ============================================================================

-- Start Mission 1 (ready for mission 1)
viopa_convo_start_mission1 = ConvoScreen:new {
	id = "start_mission1",
	leftDialog = "@conversation/lok_rebel_trainer_2:s_258ff649", -- Good to see you again dear. You are just in time too, we have an opportunity we can't miss that require your superior skills.
	animation = "bow3",
	playerAnimation = "wave1",
	stopConversation = "false",
	options = {
		{"@conversation/lok_rebel_trainer_2:s_3a42c050", "explain_mission1"}, -- What can I do to help, milady?
		{"@conversation/lok_rebel_trainer_2:s_65316548", "pirates_retort"}, -- Can't these 'space pirates' do something by themselves?
		{"@conversation/lok_rebel_trainer_2:s_21e0c701", "pay_retort"}, -- I hope this pays well. I am the best you've got, after all.
		{"@conversation/lok_rebel_trainer_2:s_e9c1932", "decline_mission1"}, -- I'm sorry, I can't right now. I'll be back.
	}
}
viopa_convo:addScreen(viopa_convo_start_mission1)

-- Pirates Retort (Can't these pirates do it?)
viopa_convo_pirates_retort = ConvoScreen:new {
	id = "pirates_retort",
	leftDialog = "@conversation/lok_rebel_trainer_2:s_f182a09c", -- Well they do often have a bit too much to drink so I don't want to trust them with a sensitive operation like this, dear.
	animation = "laugh_titter",
	stopConversation = "false",
	options = {
		{"@conversation/lok_rebel_trainer_2:s_fc4b144b", "explain_mission1"}, -- That's understandable. What do I need to do?
	}
}
viopa_convo:addScreen(viopa_convo_pirates_retort)

-- Pay Retort (I hope this pays well)
viopa_convo_pay_retort = ConvoScreen:new {
	id = "pay_retort",
	leftDialog = "@conversation/lok_rebel_trainer_2:s_ae5a02a8", -- Indeed you are. Unfortunately, our budget is a bit limited, as you may have noticed. I'm sure you'll find the rewards sufficient though, in terms of excitement, if nothing else.
	stopConversation = "false",
	options = {
		{"@conversation/lok_rebel_trainer_2:s_f1de2910", "explain_mission1"}, -- If I wanted excitement I'd... Oh well, what do you need?
	}
}
viopa_convo:addScreen(viopa_convo_pay_retort)

-- Explain Mission 1 (mission briefing - convergence point)
viopa_convo_explain_mission1 = ConvoScreen:new {
	id = "explain_mission1",
	leftDialog = "@conversation/lok_rebel_trainer_2:s_c91bccf0", -- Well, apparently an Imperial shuttle has broken down near the Trade Federation route. It might be carrying some valuable information, so we want you to hurry there before they complete their repair. Attach a spy droid. It will transfer the shuttle's data to your ship.
	animation = "explain",
	stopConversation = "false",
	options = {
		{"@conversation/lok_rebel_trainer_2:s_d08d9709", "already_repaired"}, -- What should I do if they have already repaired it?
		{"@conversation/lok_rebel_trainer_2:s_b2683b4a", "accept_mission1_easy"}, -- Piece of cake.
	}
}
viopa_convo:addScreen(viopa_convo_explain_mission1)

-- Already Repaired (follow-up question)
viopa_convo_already_repaired = ConvoScreen:new {
	id = "already_repaired",
	leftDialog = "@conversation/lok_rebel_trainer_2:s_b9f9d416", -- If the ship is still in the vicinity, try to disable it and access its data.
	stopConversation = "false",
	options = {
		{"@conversation/lok_rebel_trainer_2:s_16d870fe", "accept_mission1_consider"}, -- Consider it done.
		{"@conversation/lok_rebel_trainer_2:s_780265b8", "decline_mission1_prepare"}, -- This sounds a bit complicated. I need to do some preparation first.
	}
}
viopa_convo:addScreen(viopa_convo_already_repaired)

-- Accept Mission 1: Piece of cake (grants mission)
viopa_convo_accept_mission1_easy = ConvoScreen:new {
	id = "accept_mission1_easy",
	leftDialog = "@conversation/lok_rebel_trainer_2:s_a3790fac", -- I hope you are correct %NU and I hope you can beat their rescue team to the ship. I've taken the liberty to update your ships droid with the coordinates. Good luck!
	animation = "kiss_blow_kiss",
	playerAnimation = "embarrassed",
	stopConversation = "true",
	options = {}
}
viopa_convo:addScreen(viopa_convo_accept_mission1_easy)

-- Accept Mission 1: Consider it done (grants mission)
viopa_convo_accept_mission1_consider = ConvoScreen:new {
	id = "accept_mission1_consider",
	leftDialog = "@conversation/lok_rebel_trainer_2:s_507b9d02", -- Excellent %NU. Good luck and see you soon!
	animation = "kiss_blow_kiss",
	playerAnimation = "accept_affection",
	stopConversation = "true",
	options = {}
}
viopa_convo:addScreen(viopa_convo_accept_mission1_consider)

-- Decline Mission 1: Can't right now
viopa_convo_decline_mission1 = ConvoScreen:new {
	id = "decline_mission1",
	leftDialog = "@conversation/lok_rebel_trainer_2:s_b3a90c9", -- Hurry back, we only have this opportunity for a limited time and I would hate to be forced to use the second best pilot in the palace and not you.
	animation = "bow3",
	stopConversation = "true",
	options = {}
}
viopa_convo:addScreen(viopa_convo_decline_mission1)

-- Decline Mission 1: Need preparation
viopa_convo_decline_mission1_prepare = ConvoScreen:new {
	id = "decline_mission1_prepare",
	leftDialog = "@conversation/lok_rebel_trainer_2:s_2c95410e", -- All right. But do hurry, dear. It won't be there for long.
	animation = "nod_head_once",
	stopConversation = "true",
	options = {}
}
viopa_convo:addScreen(viopa_convo_decline_mission1_prepare)

-- ============================================================================
-- Mission 1 Flow: hasFailedMission1
-- ============================================================================

-- Failed Mission 1
viopa_convo_failed_mission1 = ConvoScreen:new {
	id = "failed_mission1",
	leftDialog = "@conversation/lok_rebel_trainer_2:s_1cb5d5fd", -- I heard about your misfortune, dear. But don't fret; luck is with us. It appears the shuttle that slipped out of your grasp was a decoy. We have another opportunity. The enemy may be on his guard this time, so be careful %NU.
	animation = "offer_affection",
	playerAnimation = "embarrassed",
	stopConversation = "false",
	options = {
		{"@conversation/lok_rebel_trainer_2:s_9c24c239", "retry_mission1_accept"}, -- I won't fail again!
		{"@conversation/lok_rebel_trainer_2:s_b862718f", "retry_mission1_refuse"}, -- I'm not going back up there again. It's suicide.
	}
}
viopa_convo:addScreen(viopa_convo_failed_mission1)

-- Retry Mission 1: Accept (grants mission)
viopa_convo_retry_mission1_accept = ConvoScreen:new {
	id = "retry_mission1_accept",
	leftDialog = "@conversation/lok_rebel_trainer_2:s_960afa57", -- I know you won't, my dear. I've uploaded the new location to your nav computer. Hurry!
	stopConversation = "true",
	options = {}
}
viopa_convo:addScreen(viopa_convo_retry_mission1_accept)

-- Retry Mission 1: Refuse (it's suicide)
viopa_convo_retry_mission1_refuse = ConvoScreen:new {
	id = "retry_mission1_refuse",
	leftDialog = "@conversation/lok_rebel_trainer_2:s_6a43381d", -- I understand. I really think your skills are more than sufficient to pull this off though, %NU.
	stopConversation = "false",
	options = {
		{"@conversation/lok_rebel_trainer_2:s_c3e498de", "retry_mission1_decline"}, -- I think you overestimate me, milady.
		{"@conversation/lok_rebel_trainer_2:s_79f026e1", "retry_mission1_convinced"}, -- I suppose you could be right. I will give it another shot.
	}
}
viopa_convo:addScreen(viopa_convo_retry_mission1_refuse)

-- Retry Mission 1: Convinced (grants mission)
viopa_convo_retry_mission1_convinced = ConvoScreen:new {
	id = "retry_mission1_convinced",
	leftDialog = "@conversation/lok_rebel_trainer_2:s_cbd8ba35", -- Excellent, I knew I could count on you %NU. I've uploaded the new coordinates to your nav computer. Hurry up there!
	animation = "point_up",
	stopConversation = "true",
	options = {}
}
viopa_convo:addScreen(viopa_convo_retry_mission1_convinced)

-- Retry Mission 1: Final Decline
viopa_convo_retry_mission1_decline = ConvoScreen:new {
	id = "retry_mission1_decline",
	leftDialog = "@conversation/lok_rebel_trainer_2:s_3769a087", -- I don't agree. But maybe another opportunity will come your way, when you are feeling more confident. Don't stay away too long, dear.
	animation = "shake_head_no",
	stopConversation = "true",
	options = {}
}
viopa_convo:addScreen(viopa_convo_retry_mission1_decline)

-- Excellent Work (Quest 1 Complete)
viopa_convo_excellent_work = ConvoScreen:new {
	id = "excellent_work",
	leftDialog = "@conversation/lok_rebel_trainer_2:s_61e761a4", -- Fantastic job, %NU! You managed to get the data, even though the ship was already repaired. I'm very impressed. This little bonus doesn't begin to reflect what you did for us, but it's all I can give you at the moment.
	animation = "celebrate",
	playerAnimation = "wave1",
	stopConversation = "false",
	options = {
		{"@conversation/lok_rebel_trainer_2:s_db9d43d", "mission1_encrypted_data"}, -- Thank you, milady. So what was the data?
		{"@conversation/lok_rebel_trainer_2:s_6fad62ec", "mission1_farewell"}, -- No problem. Time to spend this bonus. See you around, lady!
	}
}
viopa_convo:addScreen(viopa_convo_excellent_work)

-- Branch 126: Data is encrypted
viopa_convo_mission1_encrypted_data = ConvoScreen:new {
	id = "mission1_encrypted_data",
	leftDialog = "@conversation/lok_rebel_trainer_2:s_826d3c9d", -- It's heavily encrypted, so we are not sure, %NU. I will let you know as soon as I find out more.
	stopConversation = "false",
	options = {
		{"@conversation/lok_rebel_trainer_2:s_6ab7832d", "mission1_duties_available"}, -- All right. What should I do in the meantime?
		{"@conversation/lok_rebel_trainer_2:s_6258192a", "mission1_duties_later"}, -- All right. See you later, then.
	}
}
viopa_convo:addScreen(viopa_convo_mission1_encrypted_data)

-- Branch 127: Duties available
viopa_convo_mission1_duties_available = ConvoScreen:new {
	id = "mission1_duties_available",
	leftDialog = "@conversation/lok_rebel_trainer_2:s_6752d582", -- Well, we do have some duties around Lok. We could use your invaluable assistance, %NU.
	animation = "explain",
	stopConversation = "false",
	options = {
		{"@conversation/lok_rebel_trainer_2:s_e565e3d3", "accept_intro"}, -- What duties are available, milady?
		{"@conversation/lok_rebel_trainer_2:s_faf8066c", "mission1_menial_tasks"}, -- Bah! Menial tasks like that are a waste of my time.
		{"@conversation/lok_rebel_trainer_2:s_dc7c029d", "mission1_presence_appreciated"}, -- I can't right now, I'm afraid. I will be back, though.
	}
}
viopa_convo:addScreen(viopa_convo_mission1_duties_available)

-- Branch 128: Menial tasks response
viopa_convo_mission1_menial_tasks = ConvoScreen:new {
	id = "mission1_menial_tasks",
	leftDialog = "@conversation/lok_rebel_trainer_2:s_122e5dd7", -- It's the little victories that will win us this war, dear.
	stopConversation = "false",
	options = {
		{"@conversation/lok_rebel_trainer_2:s_4212435c", "accept_intro"}, -- Fine. What tasks are available right now?
		{"@conversation/lok_rebel_trainer_2:s_27101a28", "mission1_come_back"}, -- I don't have time now. I'll be back.
	}
}
viopa_convo:addScreen(viopa_convo_mission1_menial_tasks)

-- Branch 131: Duties later (guilting player)
viopa_convo_mission1_duties_later = ConvoScreen:new {
	id = "mission1_duties_later",
	leftDialog = "@conversation/lok_rebel_trainer_2:s_43fbe907", -- We have some more duties around Lok that could use some attention. But if you have something better to do...
	animation = "explain",
	stopConversation = "false",
	options = {
		{"@conversation/lok_rebel_trainer_2:s_9b82774b", "mission1_come_back_soon"}, -- Yes, I'll be back later.
		{"@conversation/lok_rebel_trainer_2:s_d0b37ad2", "accept_intro"}, -- Okay okay! What needs to be done?
	}
}
viopa_convo:addScreen(viopa_convo_mission1_duties_later)

-- Mission 1 Farewell: Spending bonus
viopa_convo_mission1_farewell = ConvoScreen:new {
	id = "mission1_farewell",
	leftDialog = "@conversation/lok_rebel_trainer_2:s_ad5cafda", -- I sure hope so %NU. You are always sorely missed when you are not around.
	animation = "kiss_blow_kiss",
	playerAnimation = "goodbye",
	stopConversation = "true",
	options = {}
}
viopa_convo:addScreen(viopa_convo_mission1_farewell)

-- Mission 1 Presence Appreciated: Can't do duties now
viopa_convo_mission1_presence_appreciated = ConvoScreen:new {
	id = "mission1_presence_appreciated",
	leftDialog = "@conversation/lok_rebel_trainer_2:s_fbef6556", -- Please do. Your presence is always appreciated, dear.
	animation = "bow3",
	playerAnimation = "goodbye",
	stopConversation = "true",
	options = {}
}
viopa_convo:addScreen(viopa_convo_mission1_presence_appreciated)

-- Mission 1 Come Back: Don't have time for menial tasks
viopa_convo_mission1_come_back = ConvoScreen:new {
	id = "mission1_come_back",
	leftDialog = "@conversation/lok_rebel_trainer_2:s_fbef6556", -- Please do. Your presence is always appreciated, dear.
	animation = "bow3",
	playerAnimation = "goodbye",
	stopConversation = "true",
	options = {}
}
viopa_convo:addScreen(viopa_convo_mission1_come_back)

-- Mission 1 Come Back Soon: From duties later
viopa_convo_mission1_come_back_soon = ConvoScreen:new {
	id = "mission1_come_back_soon",
	leftDialog = "@conversation/lok_rebel_trainer_2:s_f828b1ef", -- Very well. Come back soon, %NU.
	animation = "bow3",
	playerAnimation = "goodbye",
	stopConversation = "true",
	options = {}
}
viopa_convo:addScreen(viopa_convo_mission1_come_back_soon)

-- ============================================================================
-- Mission 2 Flow
-- ============================================================================

-- Failed Mission 2
viopa_convo_failed_mission2 = ConvoScreen:new {
	id = "failed_mission2",
	leftDialog = "@conversation/lok_rebel_trainer_2:s_3406294f", -- Glad to have you back in one piece, %NU. We received word from the hacker. He's sent coordinates for a new rendezvous.
	animation = "bow3",
	playerAnimation = "greet",
	stopConversation = "false",
	options = {
		{"@conversation/lok_rebel_trainer_2:s_137a1cc5", "retry_mission2_eager"}, -- Good. I want another chance at this.
		{"@conversation/lok_rebel_trainer_2:s_809dbad9", "retry_mission2_reluctant"}, -- Fine, I'll give it another chance.
		{"@conversation/lok_rebel_trainer_2:s_ef962200", "retry_mission2_defer"}, -- I have to fix my ship first. I will be back as soon as I can.
	}
}
viopa_convo:addScreen(viopa_convo_failed_mission2)

-- Retry Mission 2 - Eager response
viopa_convo_retry_mission2_eager = ConvoScreen:new {
	id = "retry_mission2_eager",
	leftDialog = "@conversation/lok_rebel_trainer_2:s_6bcf16a1", -- Excellent. I'll have the technicians upload the coordinates to your nav computer. I hope everything goes well this time, dear. Take well care of yourself.
	animation = "offer_affection",
	playerAnimation = "nod_head_once",
	stopConversation = "true",
	options = {}
}
viopa_convo:addScreen(viopa_convo_retry_mission2_eager)

-- Retry Mission 2 - Reluctant response
viopa_convo_retry_mission2_reluctant = ConvoScreen:new {
	id = "retry_mission2_reluctant",
	leftDialog = "@conversation/lok_rebel_trainer_2:s_1eaa0d45", -- Great, sweetie, I'm sure you'll have better luck this time. Be careful up there. The new coordinates should be uploaded to your nav computer by the time you reach your ship.
	animation = "bow3",
	playerAnimation = "goodbye",
	stopConversation = "true",
	options = {}
}
viopa_convo:addScreen(viopa_convo_retry_mission2_reluctant)

-- Retry Mission 2 - Defer (fix ship first)
viopa_convo_retry_mission2_defer = ConvoScreen:new {
	id = "retry_mission2_defer",
	leftDialog = "@conversation/lok_rebel_trainer_2:s_d5693494", -- All right. Hurry though, dear. This hacker seems rather nervous. I don't want him to change his mind.
	animation = "nod_head_once",
	playerAnimation = "goodbye",
	stopConversation = "true",
	options = {}
}
viopa_convo:addScreen(viopa_convo_retry_mission2_defer)

-- Excellent Work 2 (Quest 2 Complete)
viopa_convo_excellent_work2 = ConvoScreen:new {
	id = "excellent_work2",
	leftDialog = "@conversation/lok_rebel_trainer_2:s_a3c6ae82", -- I was so worried when I heard about the attacks on you, %NU! We suspect that someone told the Empire about your rendezvous. We are trying to figure out who the traitor is now. Anyway, I'm so glad to have you back in one piece.
	animation = "offer_affection",
	playerAnimation = "greet",
	stopConversation = "false",
	options = {
		{"@conversation/lok_rebel_trainer_2:s_4bf53cea", "mission2_rewarded_humble"}, -- Thank you, milady. It was close, but the hacker came through for us.
		{"@conversation/lok_rebel_trainer_2:s_1d34c320", "mission2_rewarded_payment"}, -- Piece of cake. There was the matter of payment. I believe?
	}
}
viopa_convo:addScreen(viopa_convo_excellent_work2)

-- Mission 2 Rewarded: Humble response
viopa_convo_mission2_rewarded_humble = ConvoScreen:new {
	id = "mission2_rewarded_humble",
	leftDialog = "@conversation/lok_rebel_trainer_2:s_71350221", -- Fantastic! I will have the intelligence department analyze the information right away. You should get some rest and come back when you're ready for some more action.
	animation = "applause_excited",
	playerAnimation = "bow3",
	stopConversation = "true",
	options = {}
}
viopa_convo:addScreen(viopa_convo_mission2_rewarded_humble)

-- Mission 2 Rewarded: Payment response
viopa_convo_mission2_rewarded_payment = ConvoScreen:new {
	id = "mission2_rewarded_payment",
	leftDialog = "@conversation/lok_rebel_trainer_2:s_6c130469", -- Oh, but of course, my dear. Get some rest while we analyze the data and come back when you are ready for some action.
	animation = "bow3",
	playerAnimation = "hair_flip",
	stopConversation = "true",
	options = {}
}
viopa_convo:addScreen(viopa_convo_mission2_rewarded_payment)

-- ============================================================================
-- Mission 3 Flow
-- ============================================================================

-- Mission 3 Brief (ready for mission 3)
viopa_convo_mission3_brief = ConvoScreen:new {
	id = "mission3_brief",
	leftDialog = "@conversation/lok_rebel_trainer_2:s_e942aa77", -- Welcome back, sweetie. The intelligence department has finished analyzing the encrypted data. It's still a bit vague.
	animation = "bow3",
	playerAnimation = "greet",
	stopConversation = "false",
	options = {
		{"@conversation/lok_rebel_trainer_2:s_c8c2d2ea", "goodbye"}, -- I was just stopping by to say hi; I have to get going.
		{"@conversation/lok_rebel_trainer_2:s_c6b08612", "start_mission3"}, -- What did they figure out?
	}
}
viopa_convo:addScreen(viopa_convo_mission3_brief)

-- Start Mission 3
viopa_convo_start_mission3 = ConvoScreen:new {
	id = "start_mission3",
	leftDialog = "@conversation/lok_rebel_trainer_2:s_e942aa77", -- dynamic - quest granted
	stopConversation = "true",
	options = {}
}
viopa_convo:addScreen(viopa_convo_start_mission3)

-- Failed Mission 3
viopa_convo_failed_mission3 = ConvoScreen:new {
	id = "failed_mission3",
	leftDialog = "@conversation/lok_rebel_trainer_2:s_e57d94c7", -- Welcome back dear. I heard what happened. The good news is that we have a second chance. The officer's shuttle seems to have malfunctioned. It's slowed him down considerably.
	animation = "bow3",
	playerAnimation = "greet",
	stopConversation = "false",
	options = {
		{"@conversation/lok_rebel_trainer_2:s_307dbfe0", "retry_mission3"}, -- Good. I won't let him slip away this time!
		{"@conversation/lok_rebel_trainer_2:s_6e92867a", "goodbye"}, -- I have to repair my ship.
	}
}
viopa_convo:addScreen(viopa_convo_failed_mission3)

-- Retry Mission 3
viopa_convo_retry_mission3 = ConvoScreen:new {
	id = "retry_mission3",
	leftDialog = "@conversation/lok_rebel_trainer_2:s_e942aa77", -- dynamic
	stopConversation = "true",
	options = {}
}
viopa_convo:addScreen(viopa_convo_retry_mission3)

-- Excellent Work 3 (Quest 3 Complete)
viopa_convo_excellent_work3 = ConvoScreen:new {
	id = "excellent_work3",
	leftDialog = "@conversation/lok_rebel_trainer_2:s_9417b6d9", -- A splendid performance as always, my dear %NU. Our intelligence department is interrogating the officer now. Hopefully we will find out soon what's going on. You should get some rest in the meantime.
	animation = "kiss_blow_kiss",
	playerAnimation = "greet",
	stopConversation = "false",
	options = {
		{"@conversation/lok_rebel_trainer_2:s_ce671a71", "mission3_rewarded"}, -- Thank you, milady. I will be back soon.
		{"@conversation/lok_rebel_trainer_2:s_27a9d3e4", "mission3_rewarded"}, -- I don't think I need it, milady. Is there anything I can do?
	}
}
viopa_convo:addScreen(viopa_convo_excellent_work3)

-- Mission 3 Rewarded
viopa_convo_mission3_rewarded = ConvoScreen:new {
	id = "mission3_rewarded",
	leftDialog = "@conversation/lok_rebel_trainer_2:s_9417b6d9", -- dynamic
	stopConversation = "true",
	options = {}
}
viopa_convo:addScreen(viopa_convo_mission3_rewarded)

-- ============================================================================
-- Mission 4 Flow
-- ============================================================================

-- Mission 4 Brief (ready for mission 4)
viopa_convo_mission4_brief = ConvoScreen:new {
	id = "mission4_brief",
	leftDialog = "@conversation/lok_rebel_trainer_2:s_106f742d", -- Just who I wanted to see. Glad you are here, %NU. As you may have heard, we managed to get some information out of the kidnapped officer. We have spent the last few days executing many successful raids against the Imperial fleet, thanks to this information. We have also tracked down the person who set you up.
	animation = "bow3",
	playerAnimation = "greet",
	stopConversation = "false",
	options = {
		{"@conversation/lok_rebel_trainer_2:s_5be79320", "start_mission4"}, -- That is great news. Who was it?
		{"@conversation/lok_rebel_trainer_2:s_697b5183", "goodbye"}, -- I hope you give him what he deserves. I will be back.
		{"@conversation/lok_rebel_trainer_2:s_cf884764", "start_mission4"}, -- I hope you flayed him and fed him to the Kimogilas!
	}
}
viopa_convo:addScreen(viopa_convo_mission4_brief)

-- Start Mission 4
viopa_convo_start_mission4 = ConvoScreen:new {
	id = "start_mission4",
	leftDialog = "@conversation/lok_rebel_trainer_2:s_106f742d", -- dynamic - quest granted
	stopConversation = "true",
	options = {}
}
viopa_convo:addScreen(viopa_convo_start_mission4)

-- Failed Mission 4
viopa_convo_failed_mission4 = ConvoScreen:new {
	id = "failed_mission4",
	leftDialog = "@conversation/lok_rebel_trainer_2:s_bbed8565", -- Hurry %NU. Get back up there! We can still keep the freighter from reaching the outpost!
	animation = "gesticulate_wildly",
	playerAnimation = "embarrassed",
	stopConversation = "false",
	options = {
		{"@conversation/lok_rebel_trainer_2:s_1d85385d", "too_guarded"}, -- I can't do it. He's too heavily guarded.
		{"@conversation/lok_rebel_trainer_2:s_6e943bb6", "retry_mission4"}, -- I will give it another try!
	}
}
viopa_convo:addScreen(viopa_convo_failed_mission4)

-- Too Guarded
viopa_convo_too_guarded = ConvoScreen:new {
	id = "too_guarded",
	leftDialog = "@conversation/lok_rebel_trainer_2:s_bbed8565", -- dynamic
	stopConversation = "true",
	options = {}
}
viopa_convo:addScreen(viopa_convo_too_guarded)

-- Retry Mission 4
viopa_convo_retry_mission4 = ConvoScreen:new {
	id = "retry_mission4",
	leftDialog = "@conversation/lok_rebel_trainer_2:s_106f742d", -- dynamic
	stopConversation = "true",
	options = {}
}
viopa_convo:addScreen(viopa_convo_retry_mission4)

-- Missions Complete (Quest 4 Complete)
viopa_convo_missions_complete = ConvoScreen:new {
	id = "missions_complete",
	leftDialog = "@conversation/lok_rebel_trainer_2:s_662d6c41", -- I have some bad news, dear. It appears this was not the heart of the Imperial fleet at all. They received a diversion order to another system. We are tracking it down right now. This part of the fleet just didn't get the order in time and decided to try and make it to the Imperial outpost instead.
	animation = "bow3",
	playerAnimation = "greet",
	stopConversation = "false",
	options = {
		{"@conversation/lok_rebel_trainer_2:s_dcec6e65", "mission4_rewarded"}, -- So all that for nothing?
		{"@conversation/lok_rebel_trainer_2:s_4a44213c", "mission4_rewarded"}, -- Alright. So what do we do now?
	}
}
viopa_convo:addScreen(viopa_convo_missions_complete)

-- Mission 4 Rewarded
viopa_convo_mission4_rewarded = ConvoScreen:new {
	id = "mission4_rewarded",
	leftDialog = "@conversation/lok_rebel_trainer_2:s_662d6c41", -- dynamic
	stopConversation = "true",
	options = {}
}
viopa_convo:addScreen(viopa_convo_mission4_rewarded)

-- ============================================================================
-- Training and Duty Flow
-- ============================================================================

-- More Training (can buy skills)
viopa_convo_more_training = ConvoScreen:new {
	id = "more_training",
	leftDialog = "@conversation/lok_rebel_trainer_2:s_53e43cdb", -- Ohh %NU, great to see you! One of Nym's pilots said he saw great skill in you and thought that you may be ready to learn some new tricks, if you would like to?
	animation = "bow3",
	playerAnimation = "greet",
	stopConversation = "false",
	options = {
		{"@conversation/lok_rebel_trainer_2:s_95cc4d4e", "training_menu"}, -- I would like some training, what can he teach me?
		{"@conversation/lok_rebel_trainer_2:s_2f0a6ba8", "training_menu"}, -- What could these dregs possibly teach me?
		{"@conversation/lok_rebel_trainer_2:s_dede1eae", "training_menu"}, -- Do I have to pay them for the training?
		{"@conversation/lok_rebel_trainer_2:s_c1c28382", "goodbye"}, -- I can't right now, milady. I will be back.
	}
}
viopa_convo:addScreen(viopa_convo_more_training)

-- Training Menu (dynamic options added by handler)
viopa_convo_training_menu = ConvoScreen:new {
	id = "training_menu",
	leftDialog = "@conversation/lok_rebel_trainer_2:s_4ee75073", -- He thought that you looked ready to learn one of the following skills.
	stopConversation = "false",
	options = {}
}
viopa_convo:addScreen(viopa_convo_training_menu)

-- Train Player: Multi-Role Craft
viopa_convo_train_player_fighters = ConvoScreen:new {
	id = "train_player_fighters",
	leftDialog = "@conversation/lok_rebel_trainer_2:s_5a954a3f", -- Excellent choice. When you are ready, come back to me. We have much to do still.
	stopConversation = "true",
	options = {}
}
viopa_convo:addScreen(viopa_convo_train_player_fighters)

-- Train Player: Intermediate Alliance Starship Ordnance
viopa_convo_train_player_component = ConvoScreen:new {
	id = "train_player_component",
	leftDialog = "@conversation/lok_rebel_trainer_2:s_5a954a3f", -- Excellent choice. When you are ready, come back to me. We have much to do still.
	stopConversation = "true",
	options = {}
}
viopa_convo:addScreen(viopa_convo_train_player_component)

-- Train Player: Space Combat Techniques
viopa_convo_train_player_basics = ConvoScreen:new {
	id = "train_player_basics",
	leftDialog = "@conversation/lok_rebel_trainer_2:s_5a954a3f", -- Excellent choice. When you are ready, come back to me. We have much to do still.
	stopConversation = "true",
	options = {}
}
viopa_convo:addScreen(viopa_convo_train_player_basics)

-- Train Player: Reactor Engineering Algorithms
viopa_convo_train_player_droid = ConvoScreen:new {
	id = "train_player_droid",
	leftDialog = "@conversation/lok_rebel_trainer_2:s_5a954a3f", -- Excellent choice. When you are ready, come back to me. We have much to do still.
	stopConversation = "true",
	options = {}
}
viopa_convo:addScreen(viopa_convo_train_player_droid)

-- Duty Missions (ready for duty)
viopa_convo_duty_missions = ConvoScreen:new {
	id = "duty_missions",
	leftDialog = "@conversation/lok_rebel_trainer_2:s_5aa92dc4", -- Hi, sweetie. Ready to help out with some duties?
	animation = "bow3",
	playerAnimation = "greet",
	stopConversation = "false",
	options = {
		{"@conversation/lok_rebel_trainer_2:s_937eedf9", "duty_menu"}, -- Yes, milady.
		{"@conversation/lok_rebel_trainer_2:s_20b704e7", "goodbye"}, -- Not right now. I have to attend to a few things.
		{"@conversation/lok_rebel_trainer_2:s_8be640b8", "duty_menu"}, -- Sure.
	}
}
viopa_convo:addScreen(viopa_convo_duty_missions)

-- Duty Menu
viopa_convo_duty_menu = ConvoScreen:new {
	id = "duty_menu",
	leftDialog = "@conversation/lok_rebel_trainer_2:s_5aa92dc4", -- Hi, sweetie. Ready to help out with some duties?
	stopConversation = "false",
	options = {}
}
viopa_convo:addScreen(viopa_convo_duty_menu)

-- Destroy Duty
viopa_convo_destroy_duty = ConvoScreen:new {
	id = "destroy_duty",
	leftDialog = "@conversation/lok_rebel_trainer_2:s_5aa92dc4", -- dynamic
	stopConversation = "true",
	options = {}
}
viopa_convo:addScreen(viopa_convo_destroy_duty)

-- Recovery Duty
viopa_convo_recovery_duty = ConvoScreen:new {
	id = "recovery_duty",
	leftDialog = "@conversation/lok_rebel_trainer_2:s_5aa92dc4", -- dynamic
	stopConversation = "true",
	options = {}
}
viopa_convo:addScreen(viopa_convo_recovery_duty)

-- Escort Duty
viopa_convo_escort_duty = ConvoScreen:new {
	id = "escort_duty",
	leftDialog = "@conversation/lok_rebel_trainer_2:s_5aa92dc4", -- dynamic
	stopConversation = "true",
	options = {}
}
viopa_convo:addScreen(viopa_convo_escort_duty)

-- ============================================================================
-- Vrak Smuggler Flow (between missions)
-- ============================================================================

-- Send to Vrak (after Mission 1 reward, before Mission 2)
-- Note: Uses same initial dialog as mission2_brief but routes to Vrak meeting instead of starting Mission 2
viopa_convo_send_to_vrak = ConvoScreen:new {
	id = "send_to_vrak",
	leftDialog = "@conversation/lok_rebel_trainer_2:s_b2335add", -- Ohh good to see you, %NU, I need your help. The data you retrieved earlier has proven impossible to decipher...
	animation = "bow3",
	playerAnimation = "greet",
	stopConversation = "false",
	options = {
		{"@conversation/lok_rebel_trainer_2:s_95a207fe", "send_to_vrak_count_on_you"}, -- Alright, what do you need help with, milady?
		{"@conversation/lok_rebel_trainer_2:s_eb569089", "send_to_vrak_charming"}, -- Sounds great. This interests me why?
		{"@conversation/lok_rebel_trainer_2:s_38aeb877", "goodbye"}, -- Oh I was just passing by. I can't help right now.
	}
}
viopa_convo:addScreen(viopa_convo_send_to_vrak)

-- Polite path - "I'm so glad I can always count on you..."
viopa_convo_send_to_vrak_count_on_you = ConvoScreen:new {
	id = "send_to_vrak_count_on_you",
	leftDialog = "@conversation/lok_rebel_trainer_2:s_d70d3929", -- I'm so glad I can always count on you, sweetie. I was hoping you could travel to the smuggler and acquire his services for us.
	animation = "applause_excited",
	stopConversation = "false",
	options = {
		{"@conversation/lok_rebel_trainer_2:s_c84e7a8", "send_to_vrak_why_me"}, -- Why me? I'm a pilot.
		{"@conversation/lok_rebel_trainer_2:s_d14eedc8", "send_to_vrak_accept"}, -- Of course. Where can I find him?
	}
}
viopa_convo:addScreen(viopa_convo_send_to_vrak_count_on_you)

-- "Why me? I'm a pilot." explanation
viopa_convo_send_to_vrak_why_me = ConvoScreen:new {
	id = "send_to_vrak_why_me",
	leftDialog = "@conversation/lok_rebel_trainer_2:s_6c7c317", -- Well, let's just say that some of Nym's employees can be a little less than dependable at times - especially unsupervised in a cantina. I need someone I can trust completely.
	animation = "explain",
	stopConversation = "false",
	options = {
		{"@conversation/lok_rebel_trainer_2:s_97f6ca14", "send_to_vrak_accept"}, -- I see. All right, where do I find him?
		{"@conversation/lok_rebel_trainer_2:s_2ccdbfbb", "send_to_vrak_decline"}, -- I'm afraid I can't right now though, milady.
	}
}
viopa_convo:addScreen(viopa_convo_send_to_vrak_why_me)

-- Sarcastic path - "You're so charming, dear..."
viopa_convo_send_to_vrak_charming = ConvoScreen:new {
	id = "send_to_vrak_charming",
	leftDialog = "@conversation/lok_rebel_trainer_2:s_ba9fbf52", -- You're so charming, dear. I was hoping you could travel to the smuggler and acquire his services for us.
	animation = "explain",
	stopConversation = "false",
	options = {
		{"@conversation/lok_rebel_trainer_2:s_d6d2881d", "send_to_vrak_not_errand_boy"}, -- I'm not an errand boy.
		{"@conversation/lok_rebel_trainer_2:s_35e906c1", "send_to_vrak_accept"}, -- Fine. I don't really have anything to do right now anyway.
	}
}
viopa_convo:addScreen(viopa_convo_send_to_vrak_charming)

-- "I'm not an errand boy." explanation
viopa_convo_send_to_vrak_not_errand_boy = ConvoScreen:new {
	id = "send_to_vrak_not_errand_boy",
	leftDialog = "@conversation/lok_rebel_trainer_2:s_8204eb26", -- Oh of course not, my dear. I need someone I trust, though. Some of Nym's employees are not really that dependable at times.
	animation = "explain",
	stopConversation = "false",
	options = {
		{"@conversation/lok_rebel_trainer_2:s_6e6242ff", "send_to_vrak_accept"}, -- That's an understatement. All right, I'll do it. Where is he?
		{"@conversation/lok_rebel_trainer_2:s_b59feb8d", "send_to_vrak_decline"}, -- You could say that again. I can't right now, though.
	}
}
viopa_convo:addScreen(viopa_convo_send_to_vrak_not_errand_boy)

-- Decline going to Vrak
viopa_convo_send_to_vrak_decline = ConvoScreen:new {
	id = "send_to_vrak_decline",
	leftDialog = "@conversation/lok_rebel_trainer_2:s_1dcfe231", -- Hmm. I will see if we can reschedule the meeting. Do hurry back dear.
	animation = "rub_chin_thoughtful",
	playerAnimation = "goodbye",
	stopConversation = "true",
	options = {}
}
viopa_convo:addScreen(viopa_convo_send_to_vrak_decline)

-- Accept going to Vrak (all accept paths converge here)
viopa_convo_send_to_vrak_accept = ConvoScreen:new {
	id = "send_to_vrak_accept",
	leftDialog = "@conversation/lok_rebel_trainer_2:s_cafeab9", -- He's agreed to meet a contact of ours on Corellia. His name is Vrak and he will be waiting in the cantina of Tyrena. Do be careful, dear. I've learned that the Empire is scouring the galaxy for the data you stole. It must be very important.
	animation = "bow3",
	playerAnimation = "goodbye",
	stopConversation = "true",
	options = {}
}
viopa_convo:addScreen(viopa_convo_send_to_vrak_accept)

-- Check if player met Vrak (viopaSmuggler == 1 or 2)
-- viopaSmuggler == 1: Player was sent but hasn't met Vrak yet (only "not yet" option shows)
-- viopaSmuggler == 2: Player met Vrak (confirmation options show)
viopa_convo_check_vrak = ConvoScreen:new {
	id = "check_vrak",
	leftDialog = "@conversation/lok_rebel_trainer_2:s_d0299d36", -- Greetings %NU. Did you meet with the smuggler?
	animation = "bow3",
	playerAnimation = "greet",
	stopConversation = "false",
	options = {}
	-- Options are added dynamically in the handler based on viopaSmuggler flag
}
viopa_convo:addScreen(viopa_convo_check_vrak)

-- Player hasn't met Vrak yet - remind them to go
viopa_convo_not_yet_vrak = ConvoScreen:new {
	id = "not_yet_vrak",
	leftDialog = "@conversation/lok_rebel_trainer_2:s_cafeab9", -- He's agreed to meet a contact of ours on Corellia. His name is Vrak and he will be waiting in the cantina of Tyrena. Do be careful, dear. I've learned that the Empire is scouring the galaxy for the data you stole. It must be very important.
	animation = "bow3",
	playerAnimation = "goodbye",
	stopConversation = "true",
	options = {}
}
viopa_convo:addScreen(viopa_convo_not_yet_vrak)

-- ============================================================================
-- FORMAL PATH (s_14310e04: "Yes milady, it seems he can assist us.")
-- ============================================================================

-- Entry: Player confirms meeting Vrak (formal path)
viopa_convo_vrak_meeting_formal = ConvoScreen:new {
	id = "vrak_meeting_formal",
	leftDialog = "@conversation/lok_rebel_trainer_2:s_4acb55cd", -- Excellent, what do we need to do?
	animation = "applause_excited",
	stopConversation = "false",
	options = {
		{"@conversation/lok_rebel_trainer_2:s_e811b51e", "formal_data_question"}, -- I need the Imperial data.
		{"@conversation/lok_rebel_trainer_2:s_41ee99fd", "formal_hacker_hope"}, -- He's set up a meeting with a hacker in Dantooine.
	}
}
viopa_convo:addScreen(viopa_convo_vrak_meeting_formal)

-- Formal path A: Player asks about Imperial data
viopa_convo_formal_data_question = ConvoScreen:new {
	id = "formal_data_question",
	leftDialog = "@conversation/lok_rebel_trainer_2:s_c4ecbd2f", -- Of course. What will you do with it?
	animation = "nod_head_once",
	stopConversation = "false",
	options = {
		{"@conversation/lok_rebel_trainer_2:s_902e7f6f", "formal_data_ready"}, -- Vrak set up a meeting with a hacker in Dantooine.
	}
}
viopa_convo:addScreen(viopa_convo_formal_data_question)

-- Formal path A: Data ready to upload (accept/defer)
viopa_convo_formal_data_ready = ConvoScreen:new {
	id = "formal_data_ready",
	leftDialog = "@conversation/lok_rebel_trainer_2:s_a3de93c4", -- Excellent. I will have a copy of the data uploaded to your ship's computer as soon as you are ready to take off, my dear.
	animation = "nod_head_once",
	stopConversation = "false",
	options = {
		{"@conversation/lok_rebel_trainer_2:s_1813f9b", "mission2_granted_sweetie"}, -- I'm ready milady.
		{"@conversation/lok_rebel_trainer_2:s_e2b5ea1a", "mission2_defer_goodbye"}, -- I will be back later. I have some things I need to address.
	}
}
viopa_convo:addScreen(viopa_convo_formal_data_ready)

-- Formal path B: Hacker hope response
viopa_convo_formal_hacker_hope = ConvoScreen:new {
	id = "formal_hacker_hope",
	leftDialog = "@conversation/lok_rebel_trainer_2:s_6280da8c", -- All right. I hope this hacker is good. We've had no success so far.
	animation = "nod_head_once",
	stopConversation = "false",
	options = {
		{"@conversation/lok_rebel_trainer_2:s_232c0049", "formal_ready_to_go"}, -- Vrak seemed sure that he could do it.
		{"@conversation/lok_rebel_trainer_2:s_94558476", "formal_data_ready"}, -- Who knows. Anyway, he wants me to take the data there.
	}
}
viopa_convo:addScreen(viopa_convo_formal_hacker_hope)

-- Formal path B: Ready to go? (accept/defer)
viopa_convo_formal_ready_to_go = ConvoScreen:new {
	id = "formal_ready_to_go",
	leftDialog = "@conversation/lok_rebel_trainer_2:s_a1062586", -- All right, good. Are you planning to meet him in Dantooine with a copy of the data?
	animation = "nod_head_once",
	stopConversation = "false",
	options = {
		{"@conversation/lok_rebel_trainer_2:s_c8427191", "mission2_granted_goodluck"}, -- Yes. I'm ready to leave anytime.
		{"@conversation/lok_rebel_trainer_2:s_b1f9f1bc", "mission2_defer_goodbye"}, -- That's right. Unfortunately, I have some things to fix first.
	}
}
viopa_convo:addScreen(viopa_convo_formal_ready_to_go)

-- ============================================================================
-- CASUAL PATH (s_3892fde6: "Sure did. He was a weird fellow.")
-- ============================================================================

-- Entry: Player confirms meeting Vrak (casual path)
viopa_convo_vrak_meeting_casual = ConvoScreen:new {
	id = "vrak_meeting_casual",
	leftDialog = "@conversation/lok_rebel_trainer_2:s_4ca03ddb", -- How so?
	animation = "rub_chin_thoughtful",
	stopConversation = "false",
	options = {
		{"@conversation/lok_rebel_trainer_2:s_97682590", "casual_hacker_hope"}, -- Oh nothing. Anyway, he's arranged a meeting with a hacker.
		{"@conversation/lok_rebel_trainer_2:s_b3f9c754", "casual_nervous_warning"}, -- He seemed very nervous. Maybe just a profession trait.
	}
}
viopa_convo:addScreen(viopa_convo_vrak_meeting_casual)

-- Casual path A: Hacker hope response
viopa_convo_casual_hacker_hope = ConvoScreen:new {
	id = "casual_hacker_hope",
	leftDialog = "@conversation/lok_rebel_trainer_2:s_6280da8c", -- All right. I hope this hacker is good. We've had no success so far.
	animation = "nod_head_once",
	stopConversation = "false",
	options = {
		{"@conversation/lok_rebel_trainer_2:s_232c0049", "casual_ready_to_go"}, -- Vrak seemed sure that he could do it.
		{"@conversation/lok_rebel_trainer_2:s_fde7cbe6", "casual_data_ready"}, -- Who knows? Anyway, he wants me to take the data there.
	}
}
viopa_convo:addScreen(viopa_convo_casual_hacker_hope)

-- Casual path A: Ready to go? (accept/defer)
viopa_convo_casual_ready_to_go = ConvoScreen:new {
	id = "casual_ready_to_go",
	leftDialog = "@conversation/lok_rebel_trainer_2:s_a1062586", -- All right, good. Are you planning to meet him in Dantooine with a copy of the data?
	animation = "nod_head_once",
	stopConversation = "false",
	options = {
		{"@conversation/lok_rebel_trainer_2:s_c8427191", "mission2_granted_goodluck"}, -- Yes. I'm ready to leave anytime.
		{"@conversation/lok_rebel_trainer_2:s_b1f9f1bc", "mission2_defer_goodbye"}, -- That's right. Unfortunately, I have some things to fix first.
	}
}
viopa_convo:addScreen(viopa_convo_casual_ready_to_go)

-- Casual path A: Data ready to upload (accept/defer)
viopa_convo_casual_data_ready = ConvoScreen:new {
	id = "casual_data_ready",
	leftDialog = "@conversation/lok_rebel_trainer_2:s_a4ab00c9", -- Excellent. I will have a copy of the data uploaded to your ship's computer as soon as you are ready to take off, dear.
	animation = "nod_head_once",
	stopConversation = "false",
	options = {
		{"@conversation/lok_rebel_trainer_2:s_359d1c6c", "mission2_granted_sweetie"}, -- I'm ready, milady.
		{"@conversation/lok_rebel_trainer_2:s_e2b5ea1a", "mission2_defer_goodbye"}, -- I will be back later. I have some things I need to address.
	}
}
viopa_convo:addScreen(viopa_convo_casual_data_ready)

-- Casual path B: Nervous warning
viopa_convo_casual_nervous_warning = ConvoScreen:new {
	id = "casual_nervous_warning",
	leftDialog = "@conversation/lok_rebel_trainer_2:s_b2e9f5b5", -- Maybe so. but the Empire is searching the galaxy for this data, so you have to be careful. Trust no one, dear. What did you find out?
	animation = "nod_head_once",
	stopConversation = "false",
	options = {
		{"@conversation/lok_rebel_trainer_2:s_105c0da2", "casual_nervous_hacker"}, -- Vrak arranged a meeting with a hacker in Dantooine.
	}
}
viopa_convo:addScreen(viopa_convo_casual_nervous_warning)

-- Casual path B: Nervous hacker hope
viopa_convo_casual_nervous_hacker = ConvoScreen:new {
	id = "casual_nervous_hacker",
	leftDialog = "@conversation/lok_rebel_trainer_2:s_6280da8c", -- All right. I hope this hacker is good. We've had no success so far.
	animation = "nod_head_once",
	stopConversation = "false",
	options = {
		{"@conversation/lok_rebel_trainer_2:s_232c0049", "casual_nervous_ready"}, -- Vrak seemed sure that he could do it.
		{"@conversation/lok_rebel_trainer_2:s_fde7cbe6", "casual_nervous_upload"}, -- Who knows? Anyway, he wants me to take the data there.
	}
}
viopa_convo:addScreen(viopa_convo_casual_nervous_hacker)

-- Casual path B: Nervous ready to go? (accept/defer)
viopa_convo_casual_nervous_ready = ConvoScreen:new {
	id = "casual_nervous_ready",
	leftDialog = "@conversation/lok_rebel_trainer_2:s_a1062586", -- All right, good. Are you planning to meet him in Dantooine with a copy of the data?
	animation = "nod_head_once",
	stopConversation = "false",
	options = {
		{"@conversation/lok_rebel_trainer_2:s_c8427191", "mission2_granted_goodluck"}, -- Yes. I'm ready to leave anytime.
		{"@conversation/lok_rebel_trainer_2:s_b1f9f1bc", "mission2_defer_goodbye"}, -- That's right. Unfortunately, I have some things to fix first.
	}
}
viopa_convo:addScreen(viopa_convo_casual_nervous_ready)

-- Casual path B: Nervous data upload (accept/defer)
viopa_convo_casual_nervous_upload = ConvoScreen:new {
	id = "casual_nervous_upload",
	leftDialog = "@conversation/lok_rebel_trainer_2:s_62d83905", -- Excellent. I will have a copy of the data uploaded to your ship's computer as soon as you are ready to take off, dear.
	animation = "nod_head_once",
	stopConversation = "false",
	options = {
		{"@conversation/lok_rebel_trainer_2:s_359d1c6c", "mission2_granted_sweetie"}, -- I'm ready, milady.
		{"@conversation/lok_rebel_trainer_2:s_e2b5ea1a", "mission2_defer_goodbye"}, -- I will be back later. I have some things I need to address.
	}
}
viopa_convo:addScreen(viopa_convo_casual_nervous_upload)

-- ============================================================================
-- MISSION 2 GRANT / DEFER SCREENS (shared by all paths)
-- ============================================================================

-- Mission 2 granted - sweetie variant (used by data_ready paths)
viopa_convo_mission2_granted_sweetie = ConvoScreen:new {
	id = "mission2_granted_sweetie",
	leftDialog = "@conversation/lok_rebel_trainer_2:s_5b7c65e8", -- How did I ever manage without you, sweetie? I'll let the technicians know what you need. Do be careful though, my dear, this all seems a bit too easy.
	animation = "laugh_titter",
	playerAnimation = "salute1",
	stopConversation = "true",
	options = {}
}
viopa_convo:addScreen(viopa_convo_mission2_granted_sweetie)

-- Mission 2 granted - good luck variant (used by ready_to_go paths)
viopa_convo_mission2_granted_goodluck = ConvoScreen:new {
	id = "mission2_granted_goodluck",
	leftDialog = "@conversation/lok_rebel_trainer_2:s_62d83905", -- Excellent. I will have a copy of the data uploaded to your ship's computer. Good luck, dear!
	animation = "bow3",
	playerAnimation = "goodbye",
	stopConversation = "true",
	options = {}
}
viopa_convo:addScreen(viopa_convo_mission2_granted_goodluck)

-- Mission 2 deferred - player will come back later
viopa_convo_mission2_defer_goodbye = ConvoScreen:new {
	id = "mission2_defer_goodbye",
	leftDialog = "@conversation/lok_rebel_trainer_2:s_54e06202", -- Sounds good, %NU. We'll be ready when you come back.
	animation = "bow3",
	playerAnimation = "goodbye",
	stopConversation = "true",
	options = {}
}
viopa_convo:addScreen(viopa_convo_mission2_defer_goodbye)

-- Send player to confront Vrak (after Mission 3, before Mission 4)
viopa_convo_send_confront_vrak = ConvoScreen:new {
	id = "send_confront_vrak",
	leftDialog = "@conversation/lok_rebel_trainer_2:s_2d07d661", -- We've narrowed it down to Vrak, the smuggler that set up the meeting with the hacker. After our successful attacks on the Imperial fleet, the Empire has rerouted their ships and we are curious what Vrak might know. Would you go have a chat with him, dear?
	animation = "explain",
	stopConversation = "false",
	options = {
		{"@conversation/lok_rebel_trainer_2:s_38f4aa90", "accept_confront_vrak"}, -- I will do more than talk to him.
		{"@conversation/lok_rebel_trainer_2:s_dce7fb", "accept_confront_vrak"}, -- If he knows anything, I will get it out of him.
	}
}
viopa_convo:addScreen(viopa_convo_send_confront_vrak)

-- Accept confronting Vrak
viopa_convo_accept_confront_vrak = ConvoScreen:new {
	id = "accept_confront_vrak",
	leftDialog = "@conversation/lok_rebel_trainer_2:s_386d56a1", -- Excellent, excellent. He doesn't know that we are onto him, so he should still be in the cantina in Tyrena. Good luck, dear.
	animation = "bow3",
	playerAnimation = "goodbye",
	stopConversation = "true",
	options = {}
}
viopa_convo:addScreen(viopa_convo_accept_confront_vrak)

-- Player returns after confronting Vrak (viopaSmuggler == 4)
viopa_convo_vrak_confronted = ConvoScreen:new {
	id = "vrak_confronted",
	leftDialog = "@conversation/lok_rebel_trainer_2:s_fdc272e0", -- The thing is, though, since we have launched our attacks on the Imperial fleet, we've noticed some peculiar behavior. It seems that the data we stole has lead to something even bigger.
	animation = "bow3",
	playerAnimation = "greet",
	stopConversation = "false",
	options = {
		{"@conversation/lok_rebel_trainer_2:s_5be79320", "start_mission4"}, -- That is great news. Who was it?
	}
}
viopa_convo:addScreen(viopa_convo_vrak_confronted)

-- ============================================================================
-- Completed / Goodbye
-- ============================================================================

-- Completed Viopa (send to next trainer - ready for tier 3)
viopa_convo_completed_viopa = ConvoScreen:new {
	id = "completed_viopa",
	leftDialog = "@conversation/lok_rebel_trainer_2:s_5884fe0d", -- Good to see you, dear. It saddens me, but I'm afraid you have been transferred to another member of the Alliance.
	animation = "greet",
	playerAnimation = "bow3",
	stopConversation = "false",
	options = {
		{"@conversation/lok_rebel_trainer_2:s_a333c9dd", "go_to_arkon"}, -- I hope I won't be reporting to another woman.
		{"@conversation/lok_rebel_trainer_2:s_668e43a2", "go_to_arkon"}, -- I will miss you, milady...
	}
}
viopa_convo:addScreen(viopa_convo_completed_viopa)

-- Go to Arkon
viopa_convo_go_to_arkon = ConvoScreen:new {
	id = "go_to_arkon",
	leftDialog = "@conversation/lok_rebel_trainer_2:s_5884fe0d", -- dynamic
	stopConversation = "true",
	options = {}
}
viopa_convo:addScreen(viopa_convo_go_to_arkon)

-- Goodbye
viopa_convo_goodbye = ConvoScreen:new {
	id = "goodbye",
	leftDialog = "@conversation/lok_rebel_trainer_2:s_9199b1bf", -- All right, sweetie. Don't be a stranger.
	stopConversation = "true",
	options = {}
}
viopa_convo:addScreen(viopa_convo_goodbye)

addConversationTemplate("viopa_convo", viopa_convo)
