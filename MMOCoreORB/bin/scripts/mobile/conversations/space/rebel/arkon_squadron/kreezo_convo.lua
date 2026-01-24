kreezo_convo = ConvoTemplate:new {
	initialScreen = "",
	templateType = "Lua",
	luaClassHandler = "kreezoConvoHandler",
	screens = {}
}

-- JTL Disabled / No Space Expansion
kreezo_convo_no_jtl = ConvoScreen:new {
	id = "no_jtl",
	leftDialog = "@conversation/corellia_rebel_trainer_1:s_e8850b0f", -- You don't look like a pilot to me. There's nothing I can do for you.
	stopConversation = "true",
	options = {}
}
kreezo_convo:addScreen(kreezo_convo_no_jtl)

-- Imperial Pilot
kreezo_convo_imperial_pilot = ConvoScreen:new {
	id = "imperial_pilot",
	leftDialog = "@conversation/corellia_rebel_trainer_1:s_1a5bf5f0", -- You've got a lot of nerve coming here and talking to me, Imperial! Get out of here now!
	stopConversation = "true",
	options = {}
}
kreezo_convo:addScreen(kreezo_convo_imperial_pilot)

-- Neutral/Privateer Pilot
kreezo_convo_neutral_pilot = ConvoScreen:new {
	id = "neutral_pilot",
	leftDialog = "@conversation/corellia_rebel_trainer_1:s_25387b43", -- The Alliance will have nothing to do with you bloodthirsty smugglers! Begone!
	stopConversation = "true",
	options = {}
}
kreezo_convo:addScreen(kreezo_convo_neutral_pilot)

-- Not on Havoc Squadron Track (wrong squadron)
kreezo_convo_non_havoc_pilot = ConvoScreen:new {
	id = "non_havoc_pilot",
	leftDialog = "@conversation/corellia_rebel_trainer_1:s_535b6177", -- Have we met? No? But you are a Rebel pilot, aren't you? What can I do for you?
	stopConversation = "false",
	options = {
		{"@conversation/corellia_rebel_trainer_1:s_1583743c", "duty_missions"}, -- Do you have any missions I could fly?
	}
}
kreezo_convo:addScreen(kreezo_convo_non_havoc_pilot)

-- No Ship - Grants ship
kreezo_convo_no_ship = ConvoScreen:new {
	id = "no_ship",
	leftDialog = "@conversation/corellia_rebel_trainer_1:s_d9d2746c", -- I don't know how you expect to fly for the Rebel Alliance if you don't even have a ship! Here, I'll add the control codes to your datapad for one of our low-end fighters. You should upgrade this as soon as possible.
	stopConversation = "true",
	options = {}
}
kreezo_convo:addScreen(kreezo_convo_no_ship)

-- Negative Faction Standing / Not a Rebel
kreezo_convo_recruitment_negative_standing = ConvoScreen:new {
	id = "recruitment_negative_standing",
	leftDialog = "@conversation/corellia_rebel_trainer_1:s_94b9286d", -- I am only authorized to work with Rebel agents %NU, try visiting one of our Recruiters in the area to sign up.
	stopConversation = "true",
	options = {}
}
kreezo_convo:addScreen(kreezo_convo_recruitment_negative_standing)

-- Recruitment (player has no novice skill)
kreezo_convo_recruitment = ConvoScreen:new {
	id = "recruitment",
	leftDialog = "@conversation/corellia_rebel_trainer_1:s_b40cd69a", -- Haven't I seen you before? I am Kreezo of the Rebel Alliance. Yes - yes, we have met before! Are you still interested in becoming a Rebel fighter pilot?
	stopConversation = "false",
	options = {
		{"@conversation/corellia_rebel_trainer_1:s_26a260", "yes_join"}, -- (Shrug)
		{"@conversation/corellia_rebel_trainer_1:s_866deb6e", "yes_join"}, -- I want to join the Rebellion!
		{"@conversation/corellia_rebel_trainer_1:s_f5e65db0", "yes_join"}, -- You don't know me, Kreezo.
	}
}
kreezo_convo:addScreen(kreezo_convo_recruitment)

-- Join - Player accepted
kreezo_convo_yes_join = ConvoScreen:new {
	id = "yes_join",
	leftDialog = "@conversation/corellia_rebel_trainer_1:s_ae0c01b4", -- Hey there! Ready to get started?
	stopConversation = "false",
	options = {}
}
kreezo_convo:addScreen(kreezo_convo_yes_join)

-- Has Active Quest - Go do your mission
kreezo_convo_has_mission = ConvoScreen:new {
	id = "has_mission",
	leftDialog = "@conversation/corellia_rebel_trainer_1:s_790cea65", -- See that up there? That's space... You should be there finishing your mission. Right?
	stopConversation = "true",
	options = {}
}
kreezo_convo:addScreen(kreezo_convo_has_mission)

-- Has Very First Quest (has mission and certified ship)
kreezo_convo_first_quest_active = ConvoScreen:new {
	id = "first_quest_active",
	leftDialog = "@conversation/corellia_rebel_trainer_1:s_c19ed115", -- You've got your assignment, and the control device for your ship in your datapad. Go to the Starport and access the terminal to launch into space.
	stopConversation = "false",
	options = {
		{"@conversation/corellia_rebel_trainer_1:s_7d5c71fb", "how_to_complete"}, -- How do I complete my assignment?
		{"@conversation/corellia_rebel_trainer_1:s_dda9e202", "where_to_go"}, -- Where should I go now?
		{"@conversation/corellia_rebel_trainer_1:s_cb506bf8", "about_datapad"}, -- My starship? In a datapad?
		{"@conversation/corellia_rebel_trainer_1:s_4b0e9ff2", "how_to_return"}, -- How do I get back here?
	}
}
kreezo_convo:addScreen(kreezo_convo_first_quest_active)

-- How to complete assignment
kreezo_convo_how_to_complete = ConvoScreen:new {
	id = "how_to_complete",
	leftDialog = "@conversation/corellia_rebel_trainer_1:s_efc5edce", -- Start by going to the starport. Leave here and head towards downtown. Take a left when you get out of the slums and you'll run right into the starport. When you get there, go inside and look for a 'starship terminal.' Use this terminal to launch your ship.
	stopConversation = "false",
	options = {
		{"@conversation/corellia_rebel_trainer_1:s_7d5c71fb", "how_to_complete"}, -- How do I complete my assignment?
		{"@conversation/corellia_rebel_trainer_1:s_dda9e202", "where_to_go"}, -- Where should I go now?
		{"@conversation/corellia_rebel_trainer_1:s_cb506bf8", "about_datapad"}, -- My starship? In a datapad?
		{"@conversation/corellia_rebel_trainer_1:s_4b0e9ff2", "how_to_return"}, -- How do I get back here?
	}
}
kreezo_convo:addScreen(kreezo_convo_how_to_complete)

-- Where to go
kreezo_convo_where_to_go = ConvoScreen:new {
	id = "where_to_go",
	leftDialog = "@conversation/corellia_rebel_trainer_1:s_c7f0d385", -- The starport. It's just a little ways from here. Go back the way you came, head towards the center of town. Take a left when you get out of the slums and you'll head right into the starport.
	stopConversation = "false",
	options = {
		{"@conversation/corellia_rebel_trainer_1:s_7d5c71fb", "how_to_complete"}, -- How do I complete my assignment?
		{"@conversation/corellia_rebel_trainer_1:s_dda9e202", "where_to_go"}, -- Where should I go now?
		{"@conversation/corellia_rebel_trainer_1:s_cb506bf8", "about_datapad"}, -- My starship? In a datapad?
		{"@conversation/corellia_rebel_trainer_1:s_4b0e9ff2", "how_to_return"}, -- How do I get back here?
	}
}
kreezo_convo:addScreen(kreezo_convo_where_to_go)

-- About datapad
kreezo_convo_about_datapad = ConvoScreen:new {
	id = "about_datapad",
	leftDialog = "@conversation/corellia_rebel_trainer_1:s_942f0b27", -- The control device holds the command codes for your starter ship. The Alliance has a handful of these banged-up Z95's hidden at various starports. When you go to the starport down the street you can use a 'starship terminal' to manage your ship components and launch into space.
	stopConversation = "false",
	options = {
		{"@conversation/corellia_rebel_trainer_1:s_7d5c71fb", "how_to_complete"}, -- How do I complete my assignment?
		{"@conversation/corellia_rebel_trainer_1:s_dda9e202", "where_to_go"}, -- Where should I go now?
		{"@conversation/corellia_rebel_trainer_1:s_cb506bf8", "about_datapad"}, -- My starship? In a datapad?
		{"@conversation/corellia_rebel_trainer_1:s_4b0e9ff2", "how_to_return"}, -- How do I get back here?
	}
}
kreezo_convo:addScreen(kreezo_convo_about_datapad)

-- How to return
kreezo_convo_how_to_return = ConvoScreen:new {
	id = "how_to_return",
	leftDialog = "@conversation/corellia_rebel_trainer_1:s_14fdabce", -- Your ship navigation system will automatically plot a waypoint when you launch so that you can find your way back home. After your mission is... a success (I hope), fly back to the 'launch waypoint.' Communicate with the space station at this point, and tell the commander you want to land at Tyrena starport.
	stopConversation = "false",
	options = {
		{"@conversation/corellia_rebel_trainer_1:s_7d5c71fb", "how_to_complete"}, -- How do I complete my assignment?
		{"@conversation/corellia_rebel_trainer_1:s_dda9e202", "where_to_go"}, -- Where should I go now?
		{"@conversation/corellia_rebel_trainer_1:s_cb506bf8", "about_datapad"}, -- My starship? In a datapad?
		{"@conversation/corellia_rebel_trainer_1:s_4b0e9ff2", "how_to_return"}, -- How do I get back here?
	}
}
kreezo_convo:addScreen(kreezo_convo_how_to_return)

-- Grant Quest 1 (not completed quest one yet)
kreezo_convo_grant_quest1 = ConvoScreen:new {
	id = "grant_quest1",
	leftDialog = "@conversation/corellia_rebel_trainer_1:s_ae0c01b4", -- Hey there! Ready to get started?
	stopConversation = "false",
	options = {
		{"@conversation/corellia_rebel_trainer_1:s_d731f764", "quest1_accepted"}, -- (Shrug and smile.)
		{"@conversation/corellia_rebel_trainer_1:s_90377ed4", "quest1_accepted"}, -- Affirmative!
		{"@conversation/corellia_rebel_trainer_1:s_b4bce31a", "quest1_accepted"}, -- I am ready, Kreezo.
		{"@conversation/corellia_rebel_trainer_1:s_b39049de", "when_train"}, -- When will you train me?
	}
}
kreezo_convo:addScreen(kreezo_convo_grant_quest1)

-- Quest 1 Accepted
kreezo_convo_quest1_accepted = ConvoScreen:new {
	id = "quest1_accepted",
	leftDialog = "@conversation/corellia_rebel_trainer_1:s_c19ed115", -- You've got your assignment, and the control device for your ship in your datapad. Go to the Starport and access the terminal to launch into space.
	stopConversation = "true",
	options = {}
}
kreezo_convo:addScreen(kreezo_convo_quest1_accepted)

-- When will you train me
kreezo_convo_when_train = ConvoScreen:new {
	id = "when_train",
	leftDialog = "@conversation/corellia_rebel_trainer_1:s_e81be890", -- dynamic - handler will set this
	stopConversation = "false",
	options = {}
}
kreezo_convo:addScreen(kreezo_convo_when_train)

-- Failed Quest 1 Patrol
kreezo_convo_failed_quest1_patrol = ConvoScreen:new {
	id = "failed_quest1_patrol",
	leftDialog = "@conversation/corellia_rebel_trainer_1:s_67119f16", -- Okay, so what happened? We need that route data as soon as possible!
	stopConversation = "false",
	options = {
		{"@conversation/corellia_rebel_trainer_1:s_2f6cbd7e", "retry_quest1"}, -- I was unable to complete the mission.
		{"@conversation/corellia_rebel_trainer_1:s_c549da6d", "retry_quest1"}, -- I aborted the mission.
	}
}
kreezo_convo:addScreen(kreezo_convo_failed_quest1_patrol)

-- Failed Quest 1
kreezo_convo_failed_quest1 = ConvoScreen:new {
	id = "failed_quest1",
	leftDialog = "@conversation/corellia_rebel_trainer_1:s_e2d918c4", -- What happened on your patrol, pilot?
	stopConversation = "false",
	options = {
		{"@conversation/corellia_rebel_trainer_1:s_328afd9b", "retry_quest1"}, -- I was jumped by TIE fighters.
		{"@conversation/corellia_rebel_trainer_1:s_e8f4f19d", "retry_quest1"}, -- I couldn't finish the mission.
	}
}
kreezo_convo:addScreen(kreezo_convo_failed_quest1)

-- Retry Quest 1
kreezo_convo_retry_quest1 = ConvoScreen:new {
	id = "retry_quest1",
	leftDialog = "@conversation/corellia_rebel_trainer_1:s_ae0c01b4", -- Hey there! Ready to get started?
	stopConversation = "true",
	options = {}
}
kreezo_convo:addScreen(kreezo_convo_retry_quest1)

-- Completed Quest 1 - Reward
kreezo_convo_completed_quest1 = ConvoScreen:new {
	id = "completed_quest1",
	leftDialog = "@conversation/corellia_rebel_trainer_1:s_66010040", -- So, let's hear it! What happened out there?
	stopConversation = "false",
	options = {
		{"@conversation/corellia_rebel_trainer_1:s_5bec38ba", "quest1_rewarded"}, -- TIE Fighters attacked me!
		{"@conversation/corellia_rebel_trainer_1:s_43a157c9", "quest1_rewarded"}, -- The patrol was interrupted by an Imperial ambush!
		{"@conversation/corellia_rebel_trainer_1:s_941b03d0", "quest1_rewarded"}, -- Nothing special.
	}
}
kreezo_convo:addScreen(kreezo_convo_completed_quest1)

-- Quest 1 Rewarded
kreezo_convo_quest1_rewarded = ConvoScreen:new {
	id = "quest1_rewarded",
	leftDialog = "@conversation/corellia_rebel_trainer_1:s_282d2761", -- Got another one for ya! It's time to get even with those TIE fighters that jumped you on your last patrol. You ready?
	stopConversation = "true",
	options = {}
}
kreezo_convo:addScreen(kreezo_convo_quest1_rewarded)

-- Grant Quest 2
kreezo_convo_grant_quest2 = ConvoScreen:new {
	id = "grant_quest2",
	leftDialog = "@conversation/corellia_rebel_trainer_1:s_282d2761", -- Got another one for ya! It's time to get even with those TIE fighters that jumped you on your last patrol. You ready?
	stopConversation = "false",
	options = {
		{"@conversation/corellia_rebel_trainer_1:s_c92d07b4", "quest2_accepted"}, -- Sure. Why not.
		{"@conversation/corellia_rebel_trainer_1:s_5792c0f4", "quest2_accepted"}, -- (Salute) Yes sir!
		{"@conversation/corellia_rebel_trainer_1:s_e2d604a4", "quest2_accepted"}, -- I am more than ready, Kreezo.
		{"@conversation/corellia_rebel_trainer_1:s_370", "when_train"}, -- When will you train me?
	}
}
kreezo_convo:addScreen(kreezo_convo_grant_quest2)

-- Quest 2 Accepted
kreezo_convo_quest2_accepted = ConvoScreen:new {
	id = "quest2_accepted",
	leftDialog = "@conversation/corellia_rebel_trainer_1:s_9f5447cf", -- dynamic - quest granted confirmation
	stopConversation = "true",
	options = {}
}
kreezo_convo:addScreen(kreezo_convo_quest2_accepted)

-- Failed Quest 2
kreezo_convo_failed_quest2 = ConvoScreen:new {
	id = "failed_quest2",
	leftDialog = "@conversation/corellia_rebel_trainer_1:s_e46d50f4", -- So let's hear all the gory details.
	stopConversation = "false",
	options = {
		{"@conversation/corellia_rebel_trainer_1:s_5f930245", "retry_quest2"}, -- I couldn't kill them all.
		{"@conversation/corellia_rebel_trainer_1:s_8b760dea", "retry_quest2"}, -- Give me another chance!
		{"@conversation/corellia_rebel_trainer_1:s_9c5aabe", "retry_quest2"}, -- There were too many of them.
	}
}
kreezo_convo:addScreen(kreezo_convo_failed_quest2)

-- Retry Quest 2
kreezo_convo_retry_quest2 = ConvoScreen:new {
	id = "retry_quest2",
	leftDialog = "@conversation/corellia_rebel_trainer_1:s_282d2761", -- Got another one for ya!
	stopConversation = "true",
	options = {}
}
kreezo_convo:addScreen(kreezo_convo_retry_quest2)

-- Completed Quest 2 - Reward
kreezo_convo_completed_quest2 = ConvoScreen:new {
	id = "completed_quest2",
	leftDialog = "@conversation/corellia_rebel_trainer_1:s_9f5447cf", -- Alliance HQ already sent word! You blasted those TIE fighters to dust! You wanna share some details?
	stopConversation = "false",
	options = {
		{"@conversation/corellia_rebel_trainer_1:s_b4ce2d62", "quest2_rewarded"}, -- A magician never reveals his secrets! (male)
		{"@conversation/corellia_rebel_trainer_1:s_c8cdb11", "quest2_rewarded"}, -- A magician never reveals her secrets! (female)
		{"@conversation/corellia_rebel_trainer_1:s_c4e77d66", "quest2_rewarded"}, -- (Provide a detailed report)
		{"@conversation/corellia_rebel_trainer_1:s_656e3c93", "quest2_rewarded"}, -- I don't remember much.
	}
}
kreezo_convo:addScreen(kreezo_convo_completed_quest2)

-- Quest 2 Rewarded
kreezo_convo_quest2_rewarded = ConvoScreen:new {
	id = "quest2_rewarded",
	leftDialog = "@conversation/corellia_rebel_trainer_1:s_aa03098a", -- We have terrible news from Alliance HQ...
	stopConversation = "true",
	options = {}
}
kreezo_convo:addScreen(kreezo_convo_quest2_rewarded)

-- Grant Quest 3
kreezo_convo_grant_quest3 = ConvoScreen:new {
	id = "grant_quest3",
	leftDialog = "@conversation/corellia_rebel_trainer_1:s_aa03098a", -- We have terrible news from Alliance HQ. A refugee convoy was attacked by TIE fighters. Their fighter escort held the TIEs long enough for the transport to escape... but now the transport is lost...
	stopConversation = "false",
	options = {
		{"@conversation/corellia_rebel_trainer_1:s_af95b1e2", "quest3_accepted"}, -- You need me to find it, right?
		{"@conversation/corellia_rebel_trainer_1:s_49bfaf2", "quest3_accepted"}, -- (Salute) For the Alliance!
		{"@conversation/corellia_rebel_trainer_1:s_5adefc5c", "quest3_accepted"}, -- Refugees?! Those monsters!
		{"@conversation/corellia_rebel_trainer_1:s_438", "when_train"}, -- When will you train me?
	}
}
kreezo_convo:addScreen(kreezo_convo_grant_quest3)

-- Quest 3 Accepted
kreezo_convo_quest3_accepted = ConvoScreen:new {
	id = "quest3_accepted",
	leftDialog = "@conversation/corellia_rebel_trainer_1:s_bb9e839f", -- dynamic - quest granted confirmation
	stopConversation = "true",
	options = {}
}
kreezo_convo:addScreen(kreezo_convo_quest3_accepted)

-- Failed Quest 3
kreezo_convo_failed_quest3 = ConvoScreen:new {
	id = "failed_quest3",
	leftDialog = "@conversation/corellia_rebel_trainer_1:s_43092a4a", -- So, lucky for you that wasn't the last refugee transport from the convoy. You ready to try again?
	stopConversation = "false",
	options = {
		{"@conversation/corellia_rebel_trainer_1:s_2a1af6a8", "retry_quest3"}, -- Guess so.
		{"@conversation/corellia_rebel_trainer_1:s_64355c70", "retry_quest3"}, -- Right away, sir!
		{"@conversation/corellia_rebel_trainer_1:s_e102b38d", "retry_quest3"}, -- Without question.
	}
}
kreezo_convo:addScreen(kreezo_convo_failed_quest3)

-- Retry Quest 3
kreezo_convo_retry_quest3 = ConvoScreen:new {
	id = "retry_quest3",
	leftDialog = "@conversation/corellia_rebel_trainer_1:s_aa03098a", -- We have terrible news...
	stopConversation = "true",
	options = {}
}
kreezo_convo:addScreen(kreezo_convo_retry_quest3)

-- Completed Quest 3 - Reward
kreezo_convo_completed_quest3 = ConvoScreen:new {
	id = "completed_quest3",
	leftDialog = "@conversation/corellia_rebel_trainer_1:s_bb9e839f", -- Hey! So what happened up there?
	stopConversation = "false",
	options = {
		{"@conversation/corellia_rebel_trainer_1:s_e37282e3", "quest3_rewarded"}, -- Standard space-hero stuff.
		{"@conversation/corellia_rebel_trainer_1:s_9df39ab2", "quest3_rewarded"}, -- (Salute) The Alliance transport has been rescued!
		{"@conversation/corellia_rebel_trainer_1:s_20ef9c42", "quest3_rewarded"}, -- Mission accomplished.
	}
}
kreezo_convo:addScreen(kreezo_convo_completed_quest3)

-- Quest 3 Rewarded
kreezo_convo_quest3_rewarded = ConvoScreen:new {
	id = "quest3_rewarded",
	leftDialog = "@conversation/corellia_rebel_trainer_1:s_32190415", -- Hey! Good to see ya again...
	stopConversation = "true",
	options = {}
}
kreezo_convo:addScreen(kreezo_convo_quest3_rewarded)

-- Grant Quest 4
kreezo_convo_grant_quest4 = ConvoScreen:new {
	id = "grant_quest4",
	leftDialog = "@conversation/corellia_rebel_trainer_1:s_32190415", -- Hey! Good to see ya again. Got a new mission brewing. You are going to LOVE this!
	stopConversation = "false",
	options = {
		{"@conversation/corellia_rebel_trainer_1:s_1bdcc6fa", "quest4_accepted"}, -- All right. Let's hear it!
		{"@conversation/corellia_rebel_trainer_1:s_6b490480", "quest4_accepted"}, -- (Salute) Affirmative!
		{"@conversation/corellia_rebel_trainer_1:s_2477af4a", "quest4_accepted"}, -- For the Alliance... always.
		{"@conversation/corellia_rebel_trainer_1:s_484", "when_train"}, -- When will you train me?
	}
}
kreezo_convo:addScreen(kreezo_convo_grant_quest4)

-- Quest 4 Accepted
kreezo_convo_quest4_accepted = ConvoScreen:new {
	id = "quest4_accepted",
	leftDialog = "@conversation/corellia_rebel_trainer_1:s_e5a5e513", -- dynamic - quest granted confirmation
	stopConversation = "true",
	options = {}
}
kreezo_convo:addScreen(kreezo_convo_quest4_accepted)

-- Failed Quest 4
kreezo_convo_failed_quest4 = ConvoScreen:new {
	id = "failed_quest4",
	leftDialog = "@conversation/corellia_rebel_trainer_1:s_3339950", -- Too much for you, huh?
	stopConversation = "false",
	options = {
		{"@conversation/corellia_rebel_trainer_1:s_af180d19", "retry_quest4"}, -- They got lucky.
		{"@conversation/corellia_rebel_trainer_1:s_afd8ea50", "retry_quest4"}, -- No, sir! Again, sir!
		{"@conversation/corellia_rebel_trainer_1:s_d2b22f30", "retry_quest4"}, -- I won't fail a second time.
	}
}
kreezo_convo:addScreen(kreezo_convo_failed_quest4)

-- Retry Quest 4
kreezo_convo_retry_quest4 = ConvoScreen:new {
	id = "retry_quest4",
	leftDialog = "@conversation/corellia_rebel_trainer_1:s_32190415", -- Hey! Good to see ya again...
	stopConversation = "true",
	options = {}
}
kreezo_convo:addScreen(kreezo_convo_retry_quest4)

-- Completed Quest 4 - Reward
kreezo_convo_completed_quest4 = ConvoScreen:new {
	id = "completed_quest4",
	leftDialog = "@conversation/corellia_rebel_trainer_1:s_e5a5e513", -- I see you've survived!
	stopConversation = "false",
	options = {
		{"@conversation/corellia_rebel_trainer_1:s_83c26b3", "quest4_rewarded"}, -- That TIE Veteran was nothing.
		{"@conversation/corellia_rebel_trainer_1:s_491", "quest4_rewarded"}, -- (Salute) Affirmative!
		{"@conversation/corellia_rebel_trainer_1:s_cade4505", "quest4_rewarded"}, -- The Force is with me.
	}
}
kreezo_convo:addScreen(kreezo_convo_completed_quest4)

-- Quest 4 Rewarded - Ready for first training
kreezo_convo_quest4_rewarded = ConvoScreen:new {
	id = "quest4_rewarded",
	leftDialog = "@conversation/corellia_rebel_trainer_1:s_a0f35e59", -- Hi there! You now have all the experience you need to be trained in something new...
	stopConversation = "false",
	options = {
		{"@conversation/corellia_rebel_trainer_1:s_611", "first_training"}, -- Yes.
	}
}
kreezo_convo:addScreen(kreezo_convo_quest4_rewarded)

-- First Training (after completing all 4 missions)
kreezo_convo_first_training = ConvoScreen:new {
	id = "first_training",
	leftDialog = "@conversation/corellia_rebel_trainer_1:s_a0f35e59", -- Hi there! You now have all the experience you need to be trained in something new. I can teach you the proper handling of superior starfighters. Specifically, I can give you certifications to fly the Y-Wing. Are you interested in this?
	stopConversation = "false",
	options = {
		{"@conversation/corellia_rebel_trainer_1:s_611", "train_starships"}, -- Yes.
	}
}
kreezo_convo:addScreen(kreezo_convo_first_training)

-- Train Starships skill
kreezo_convo_train_starships = ConvoScreen:new {
	id = "train_starships",
	leftDialog = "@conversation/corellia_rebel_trainer_1:s_246d08d7", -- You have enough experience for more training. Are you ready to learn?
	stopConversation = "false",
	options = {}
}
kreezo_convo:addScreen(kreezo_convo_train_starships)

-- More Training (has XP for training)
kreezo_convo_more_training = ConvoScreen:new {
	id = "more_training",
	leftDialog = "@conversation/corellia_rebel_trainer_1:s_246d08d7", -- You have enough experience for more training. Are you ready to learn?
	stopConversation = "false",
	options = {
		{"@conversation/corellia_rebel_trainer_1:s_614", "training_menu"}, -- I am ready.
	}
}
kreezo_convo:addScreen(kreezo_convo_more_training)

-- Training Menu (dynamic options added by handler)
kreezo_convo_training_menu = ConvoScreen:new {
	id = "training_menu",
	leftDialog = "@conversation/corellia_rebel_trainer_1:s_246d08d7", -- You have enough experience for more training. Are you ready to learn?
	stopConversation = "false",
	options = {}
}
kreezo_convo:addScreen(kreezo_convo_training_menu)

-- Completed Kreezo - Has all tier 1 skills, send to next trainer
kreezo_convo_completed_kreezo = ConvoScreen:new {
	id = "completed_kreezo",
	leftDialog = "@conversation/corellia_rebel_trainer_1:s_b2b30e20", -- Hey, so... the Alliance has asked me to recommend pilots that are ready for more challenge. Evidently something big is going on above planet Lok. Rebel Intelligence is all over it... and they need pilots.
	stopConversation = "false",
	options = {
		{"@conversation/corellia_rebel_trainer_1:s_386363ba", "go_to_viopa"}, -- Yeah, so?
		{"@conversation/corellia_rebel_trainer_1:s_c999ae60", "go_to_viopa"}, -- Let me at 'em!
	}
}
kreezo_convo:addScreen(kreezo_convo_completed_kreezo)

-- Go to Viopa (graduated)
kreezo_convo_go_to_viopa = ConvoScreen:new {
	id = "go_to_viopa",
	leftDialog = "@conversation/corellia_rebel_trainer_1:s_24d9c943", -- What are you doing here? You should be working for Lady Viopa on Lok... right?
	stopConversation = "false",
	options = {
		{"@conversation/corellia_rebel_trainer_1:s_b3bebc5e", "directions_to_viopa"}, -- How do I get there?
	}
}
kreezo_convo:addScreen(kreezo_convo_go_to_viopa)

-- Directions to Viopa
kreezo_convo_directions_to_viopa = ConvoScreen:new {
	id = "directions_to_viopa",
	leftDialog = "@conversation/corellia_rebel_trainer_1:s_24d9c943", -- What are you doing here? You should be working for Lady Viopa on Lok... right?
	stopConversation = "true",
	options = {}
}
kreezo_convo:addScreen(kreezo_convo_directions_to_viopa)

-- Graduated - Already sent to Viopa
kreezo_convo_graduated = ConvoScreen:new {
	id = "graduated",
	leftDialog = "@conversation/corellia_rebel_trainer_1:s_24d9c943", -- What are you doing here? You should be working for Lady Viopa on Lok... right?
	stopConversation = "false",
	options = {
		{"@conversation/corellia_rebel_trainer_1:s_b3bebc5e", "directions_to_viopa"}, -- How do I get there?
	}
}
kreezo_convo:addScreen(kreezo_convo_graduated)

-- Duty Missions (default fallback for completed players)
kreezo_convo_duty_missions = ConvoScreen:new {
	id = "duty_missions",
	leftDialog = "@conversation/corellia_rebel_trainer_1:s_7fcd3228", -- Good to see you again. How are things going?
	stopConversation = "false",
	options = {
		{"@conversation/corellia_rebel_trainer_1:s_b4be0022", "request_duty"}, -- Things'd be better if I had a mission.
		{"@conversation/corellia_rebel_trainer_1:s_83a93ead", "request_duty"}, -- (Salute) Requesting a mission, sir!
		{"@conversation/corellia_rebel_trainer_1:s_e96daa14", "request_duty"}, -- Our work is not finished, Kreezo.
		{"@conversation/corellia_rebel_trainer_1:s_1b107d8a", "ground_forces"}, -- I want to join-up with the ground forces.
	}
}
kreezo_convo:addScreen(kreezo_convo_duty_missions)

-- Request Duty Mission
kreezo_convo_request_duty = ConvoScreen:new {
	id = "request_duty",
	leftDialog = "@conversation/corellia_rebel_trainer_1:s_7fcd3228", -- Good to see you again. How are things going?
	stopConversation = "true",
	options = {}
}
kreezo_convo:addScreen(kreezo_convo_request_duty)

-- Ground Forces
kreezo_convo_ground_forces = ConvoScreen:new {
	id = "ground_forces",
	leftDialog = "@conversation/corellia_rebel_trainer_1:s_7fcd3228", -- dynamic
	stopConversation = "true",
	options = {}
}
kreezo_convo:addScreen(kreezo_convo_ground_forces)

-- Goodbye
kreezo_convo_goodbye = ConvoScreen:new {
	id = "goodbye",
	leftDialog = "@conversation/corellia_rebel_trainer_1:s_7fcd3228", -- Good to see you again. How are things going?
	stopConversation = "true",
	options = {}
}
kreezo_convo:addScreen(kreezo_convo_goodbye)

addConversationTemplate("kreezo_convo", kreezo_convo)
