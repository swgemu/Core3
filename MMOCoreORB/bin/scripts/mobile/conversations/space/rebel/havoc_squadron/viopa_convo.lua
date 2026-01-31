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

-- Introduction / Ready for First Skill (correct rebel pilot ready to start tier 2)
viopa_convo_introduction = ConvoScreen:new {
	id = "introduction",
	leftDialog = "@conversation/lok_rebel_trainer_2:s_15250124", -- Greetings %TU. My name is Viopa. I function as the Alliance's go-between for the Rebellion and Lord Nym...
	animation = "bow3",
	playerAnimation = "wave1",
	stopConversation = "false",
	options = {
		{"@conversation/lok_rebel_trainer_2:s_5c1d4116", "accept_intro"}, -- What can I do to help, milady?
		{"@conversation/lok_rebel_trainer_2:s_69f4c38c", "goodbye"}, -- Can't these 'space pirates' do something by themselves?
	}
}
viopa_convo:addScreen(viopa_convo_introduction)

-- Accept Intro / Mission 1 Brief
viopa_convo_accept_intro = ConvoScreen:new {
	id = "accept_intro",
	leftDialog = "@conversation/lok_rebel_trainer_2:s_e8a92b79", -- Good to see you again dear. You are just in time too, we have an opportunity we can't miss that require your superior skills.
	stopConversation = "true",
	options = {}
}
viopa_convo:addScreen(viopa_convo_accept_intro)

-- Start Mission 1 (ready for mission 1)
viopa_convo_start_mission1 = ConvoScreen:new {
	id = "start_mission1",
	leftDialog = "@conversation/lok_rebel_trainer_2:s_e8a92b79", -- Good to see you again dear. You are just in time too, we have an opportunity we can't miss that require your superior skills.
	animation = "bow3",
	playerAnimation = "wave1",
	stopConversation = "false",
	options = {
		{"@conversation/lok_rebel_trainer_2:s_5c1d4116", "accept_mission1"}, -- What can I do to help, milady?
		{"@conversation/lok_rebel_trainer_2:s_69f4c38c", "goodbye"}, -- Can't these 'space pirates' do something by themselves?
	}
}
viopa_convo:addScreen(viopa_convo_start_mission1)

-- Accept Mission 1
viopa_convo_accept_mission1 = ConvoScreen:new {
	id = "accept_mission1",
	leftDialog = "@conversation/lok_rebel_trainer_2:s_e8a92b79", -- dynamic - quest granted
	stopConversation = "true",
	options = {}
}
viopa_convo:addScreen(viopa_convo_accept_mission1)

-- Failed Mission 1
viopa_convo_failed_mission1 = ConvoScreen:new {
	id = "failed_mission1",
	leftDialog = "@conversation/lok_rebel_trainer_2:s_e8a92b79", -- Good to see you again dear (retry)
	animation = "offer_affection",
	playerAnimation = "embarrassed",
	stopConversation = "false",
	options = {
		{"@conversation/lok_rebel_trainer_2:s_5c1d4116", "accept_mission1"}, -- What can I do to help, milady?
	}
}
viopa_convo:addScreen(viopa_convo_failed_mission1)

-- Excellent Work (Quest 1 Complete)
viopa_convo_excellent_work = ConvoScreen:new {
	id = "excellent_work",
	leftDialog = "@conversation/lok_rebel_trainer_2:s_61e761a4", -- Fantastic job, %NU! You managed to get the data, even though the ship was already repaired. I'm very impressed. This little bonus doesn't begin to reflect what you did for us, but it's all I can give you at the moment.
	animation = "celebrate",
	playerAnimation = "wave1",
	stopConversation = "false",
	options = {
		{"@conversation/lok_rebel_trainer_2:s_88d113c1", "mission1_rewarded"}, -- Thank you, milady. So what was the data?
		{"@conversation/lok_rebel_trainer_2:s_e91ff6c6", "goodbye"}, -- No problem. Time to spend this bonus. See you around, lady!
	}
}
viopa_convo:addScreen(viopa_convo_excellent_work)

-- Mission 1 Rewarded
viopa_convo_mission1_rewarded = ConvoScreen:new {
	id = "mission1_rewarded",
	leftDialog = "@conversation/lok_rebel_trainer_2:s_61e761a4", -- dynamic
	stopConversation = "true",
	options = {}
}
viopa_convo:addScreen(viopa_convo_mission1_rewarded)

-- Mission 2 Brief (ready for mission 2)
viopa_convo_mission2_brief = ConvoScreen:new {
	id = "mission2_brief",
	leftDialog = "@conversation/lok_rebel_trainer_2:s_b2335add", -- Ohh good to see you, %NU, I need your help. The data you retrieved earlier has proven impossible to decipher. Fortunately, Nym knows of a smuggler that specializes in these kind of predicaments.
	animation = "bow3",
	playerAnimation = "greet",
	stopConversation = "false",
	options = {
		{"@conversation/lok_rebel_trainer_2:s_95a207fe", "start_mission2"}, -- Alright, what do you need help with, milady?
		{"@conversation/lok_rebel_trainer_2:s_eb569089", "start_mission2"}, -- Sounds great. This interests me why?
		{"@conversation/lok_rebel_trainer_2:s_38aeb877", "goodbye"}, -- Oh I was just passing by. I can't help right now.
	}
}
viopa_convo:addScreen(viopa_convo_mission2_brief)

-- Start Mission 2
viopa_convo_start_mission2 = ConvoScreen:new {
	id = "start_mission2",
	leftDialog = "@conversation/lok_rebel_trainer_2:s_b2335add", -- dynamic - quest granted
	stopConversation = "true",
	options = {}
}
viopa_convo:addScreen(viopa_convo_start_mission2)

-- Failed Mission 2
viopa_convo_failed_mission2 = ConvoScreen:new {
	id = "failed_mission2",
	leftDialog = "@conversation/lok_rebel_trainer_2:s_3406294f", -- Glad to have you back in one piece, %NU. We received word from the hacker. He's sent coordinates for a new rendezvous.
	animation = "bow3",
	playerAnimation = "greet",
	stopConversation = "false",
	options = {
		{"@conversation/lok_rebel_trainer_2:s_137a1cc5", "retry_mission2"}, -- Good. I want another chance at this.
		{"@conversation/lok_rebel_trainer_2:s_809dbad9", "retry_mission2"}, -- Fine, I'll give it another chance.
		{"@conversation/lok_rebel_trainer_2:s_ef962200", "goodbye"}, -- I have to fix my ship first. I will be back as soon as I can.
	}
}
viopa_convo:addScreen(viopa_convo_failed_mission2)

-- Retry Mission 2
viopa_convo_retry_mission2 = ConvoScreen:new {
	id = "retry_mission2",
	leftDialog = "@conversation/lok_rebel_trainer_2:s_b2335add", -- dynamic
	stopConversation = "true",
	options = {}
}
viopa_convo:addScreen(viopa_convo_retry_mission2)

-- Excellent Work 2 (Quest 2 Complete)
viopa_convo_excellent_work2 = ConvoScreen:new {
	id = "excellent_work2",
	leftDialog = "@conversation/lok_rebel_trainer_2:s_a3c6ae82", -- I was so worried when I heard about the attacks on you, %NU! We suspect that someone told the Empire about your rendezvous. We are trying to figure out who the traitor is now. Anyway, I'm so glad to have you back in one piece.
	animation = "offer_affection",
	playerAnimation = "greet",
	stopConversation = "false",
	options = {
		{"@conversation/lok_rebel_trainer_2:s_4bf53cea", "mission2_rewarded"}, -- Thank you, milady. It was close, but the hacker came through for us.
		{"@conversation/lok_rebel_trainer_2:s_1d34c320", "mission2_rewarded"}, -- Piece of cake. There was the matter of payment. I believe?
	}
}
viopa_convo:addScreen(viopa_convo_excellent_work2)

-- Mission 2 Rewarded
viopa_convo_mission2_rewarded = ConvoScreen:new {
	id = "mission2_rewarded",
	leftDialog = "@conversation/lok_rebel_trainer_2:s_a3c6ae82", -- dynamic
	stopConversation = "true",
	options = {}
}
viopa_convo:addScreen(viopa_convo_mission2_rewarded)

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

-- Mission 4 Brief (ready for mission 4)
viopa_convo_mission4_brief = ConvoScreen:new {
	id = "mission4_brief",
	leftDialog = "@conversation/lok_rebel_trainer_2:s_106f742d", -- Just who I wanted to see. Glad you are here, %NU. As you may have heard, we managed to get some information out of the kidnapped officer. We have spent the last few days executing many successful raids against the Imperial fleet, thanks to this information. We have also tracked down the person who set you up.
	animation = "bow3",
	playerAnimation = "greet",
	stopConversation = "false",
	options = {
		{"@conversation/lok_rebel_trainer_2:s_51b8de7f", "start_mission4"}, -- That is great news. Who was it?
		{"@conversation/lok_rebel_trainer_2:s_4ad18f6d", "goodbye"}, -- I hope you give him what he deserves. I will be back.
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

-- More Training (can buy skills)
viopa_convo_more_training = ConvoScreen:new {
	id = "more_training",
	leftDialog = "@conversation/lok_rebel_trainer_2:s_53e43cdb", -- Ohh %NU, great to see you! One of Nym's pilots said he saw great skill in you and thought that you may be ready to learn some new tricks, if you would like to?
	animation = "bow3",
	playerAnimation = "greet",
	stopConversation = "false",
	options = {
		{"@conversation/lok_rebel_trainer_2:s_6c48a7f3", "training_menu"}, -- I would like some training, what can he teach me?
		{"@conversation/lok_rebel_trainer_2:s_a02f33dc", "goodbye"}, -- What could these dregs possibly teach me?
	}
}
viopa_convo:addScreen(viopa_convo_more_training)

-- Training Menu (dynamic options added by handler)
viopa_convo_training_menu = ConvoScreen:new {
	id = "training_menu",
	leftDialog = "@conversation/lok_rebel_trainer_2:s_53e43cdb", -- Ohh %NU, great to see you!
	stopConversation = "false",
	options = {}
}
viopa_convo:addScreen(viopa_convo_training_menu)

-- Duty Missions (ready for duty)
viopa_convo_duty_missions = ConvoScreen:new {
	id = "duty_missions",
	leftDialog = "@conversation/lok_rebel_trainer_2:s_5aa92dc4", -- Hi, sweetie. Ready to help out with some duties?
	animation = "bow3",
	playerAnimation = "greet",
	stopConversation = "false",
	options = {
		{"@conversation/lok_rebel_trainer_2:s_94f9ca8c", "duty_menu"}, -- Yes, milady.
		{"@conversation/lok_rebel_trainer_2:s_9dee4c22", "goodbye"}, -- Not right now. I have to attend to a few things.
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
	leftDialog = "@conversation/lok_rebel_trainer_2:s_5aa92dc4", -- Hi, sweetie. (generic)
	stopConversation = "true",
	options = {}
}
viopa_convo:addScreen(viopa_convo_goodbye)

addConversationTemplate("viopa_convo", viopa_convo)
