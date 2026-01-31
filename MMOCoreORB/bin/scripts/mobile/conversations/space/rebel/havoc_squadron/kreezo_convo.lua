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
	animation = "wave_finger_warning",
	options = {}
}
kreezo_convo:addScreen(kreezo_convo_imperial_pilot)

-- Neutral/Privateer Pilot
kreezo_convo_neutral_pilot = ConvoScreen:new {
	id = "neutral_pilot",
	leftDialog = "@conversation/corellia_rebel_trainer_1:s_25387b43", -- The Alliance will have nothing to do with you bloodthirsty smugglers! Begone!
	stopConversation = "false",
	animation = "point_accusingly",
	options = {
		{"@conversation/corellia_rebel_trainer_1:s_3fa4f0ff", "neutral_pilot_fine"}, -- Fine!
		{"@conversation/corellia_rebel_trainer_1:s_34e352c7", "neutral_pilot_corsec"}, -- I'm a CorSec pilot!
		{"@conversation/corellia_rebel_trainer_1:s_a42bf003", "neutral_pilot_rsf"}, -- I'm a RSF Pilot!
	}
}
kreezo_convo:addScreen(kreezo_convo_neutral_pilot)

-- Neutral pilot response - Fine!
kreezo_convo_neutral_pilot_fine = ConvoScreen:new {
	id = "neutral_pilot_fine",
	leftDialog = "@conversation/corellia_rebel_trainer_1:s_29cee3c8", -- Okay. I can appreciate that, I guess. Good luck...
	stopConversation = "true",
	animation = "goodbye",
	options = {}
}
kreezo_convo:addScreen(kreezo_convo_neutral_pilot_fine)

-- Neutral pilot response - CorSec
kreezo_convo_neutral_pilot_corsec = ConvoScreen:new {
	id = "neutral_pilot_corsec",
	leftDialog = "@conversation/corellia_rebel_trainer_1:s_29cee3c8", -- Okay. I can appreciate that, I guess. Good luck...
	stopConversation = "true",
	animation = "goodbye",
	options = {}
}
kreezo_convo:addScreen(kreezo_convo_neutral_pilot_corsec)

-- Neutral pilot response - RSF
kreezo_convo_neutral_pilot_rsf = ConvoScreen:new {
	id = "neutral_pilot_rsf",
	leftDialog = "@conversation/corellia_rebel_trainer_1:s_29cee3c8", -- Okay. I can appreciate that, I guess. Good luck...
	stopConversation = "true",
	animation = "goodbye",
	options = {}
}
kreezo_convo:addScreen(kreezo_convo_neutral_pilot_rsf)

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
	stopConversation = "false",
	animation = "nod_head_multiple",
	options = {
		{"@conversation/corellia_rebel_trainer_1:s_d731f764", "yes_im_ready"}, -- (Shrug and smile.)
		{"@conversation/corellia_rebel_trainer_1:s_90377ed4", "yes_im_ready"}, -- Affirmative!
		{"@conversation/corellia_rebel_trainer_1:s_b4bce31a", "yes_im_ready"}, -- I am ready, Kreezo.
	}
}
kreezo_convo:addScreen(kreezo_convo_no_ship)

-- Not a Rebel
kreezo_convo_recruitment_not_rebel = ConvoScreen:new {
	id = "recruitment_not_rebel",
	leftDialog = "@conversation/corellia_rebel_trainer_1:s_b4da544c", -- This is out of my hands. I can't give you any more assignments until you prove your dedication to the cause.  Fight FOR the Rebel Alliance and improve your standing.
	stopConversation = "true",
	options = {}
}
kreezo_convo:addScreen(kreezo_convo_recruitment_not_rebel)

-- Recruitment (player has no novice skill)
kreezo_convo_recruitment = ConvoScreen:new {
	id = "recruitment",
	leftDialog = "@conversation/corellia_rebel_trainer_1:s_b40cd69a", -- Haven't I seen you before? I am Kreezo of the Rebel Alliance. Yes - yes, we have met before! Are you still interested in becoming a Rebel fighter pilot?
	stopConversation = "false",
	animation = "greet",
	playerAnimation = "",
	options = {
		{"@conversation/corellia_rebel_trainer_1:s_26a260", "shrug_response"}, -- (Shrug)
		{"@conversation/corellia_rebel_trainer_1:s_866deb6e", "yes_join"}, -- I want to join the Rebellion!
		{"@conversation/corellia_rebel_trainer_1:s_f5e65db0", "of_course"}, -- You don't know me, Kreezo.
	}
}
kreezo_convo:addScreen(kreezo_convo_recruitment)

-- Join - Player accepted (shrug response)
kreezo_convo_shrug_response = ConvoScreen:new {
	id = "shrug_response",
	leftDialog = "@conversation/corellia_rebel_trainer_1:s_85384000", -- So you are interested? Or... you aren't interested?
	stopConversation = "false",
	animation = "shrug_hands",
	playerAnimation = "shrug_hands",
	options = {}
}
kreezo_convo:addScreen(kreezo_convo_shrug_response)

-- Join - Male player confirm
kreezo_convo_male_join_confirm = ConvoScreen:new {
	id = "male_join_confirm",
	leftDialog = "@conversation/corellia_rebel_trainer_1:s_d390e9dc", -- Perfect thing for a strapping fella such as yourself! I'll be your trainer - and you'll be my... killer! How does that sound?
	stopConversation = "false",
	animation = "shrug_shoulders",
	options = {
		{"@conversation/corellia_rebel_trainer_1:s_c8fa77b8", "male_welcome_alliance"}, -- I can't wait!
		{"@conversation/corellia_rebel_trainer_1:s_7daee3c9", "check_back"}, -- Sounds wrong for me.
	}
}
kreezo_convo:addScreen(kreezo_convo_male_join_confirm)

-- Join - Male welcome to alliance (grants skill, then ship options)
kreezo_convo_male_welcome_alliance = ConvoScreen:new {
	id = "male_welcome_alliance",
	leftDialog = "@conversation/corellia_rebel_trainer_1:s_71b1981e", -- Great! Welcome to the Alliance!
	stopConversation = "false",
	animation = "celebrate",
	options = {}
}
kreezo_convo:addScreen(kreezo_convo_male_welcome_alliance)

-- Join - Female player confirm
kreezo_convo_female_join_confirm = ConvoScreen:new {
	id = "female_join_confirm",
	leftDialog = "@conversation/corellia_rebel_trainer_1:s_a2fa88c1", -- Are you sure you want to sign up, honey? It's pretty rough up there.
	stopConversation = "false",
	animation = "shake_head_no",
	options = {
		{"@conversation/corellia_rebel_trainer_1:s_d48ff4ca", "female_kidding"}, -- You're kidding, right?
		{"@conversation/corellia_rebel_trainer_1:s_e6f57b04", "female_relax_sweetie"}, -- Call me that again and you die!
	}
}
kreezo_convo:addScreen(kreezo_convo_female_join_confirm)

-- Female response - relax sweetie (after "Call me that again and you die!")
kreezo_convo_female_relax_sweetie = ConvoScreen:new {
	id = "female_relax_sweetie",
	leftDialog = "@conversation/corellia_rebel_trainer_1:s_cafe8309", -- Whoa! Relax, sweetie! I meant nothing by it. Say - if you're really hot for flying starships, I'll set you up. Are you sure you want to join?
	stopConversation = "false",
	animation = "standing_placate",
	options = {
		{"@conversation/corellia_rebel_trainer_1:s_1df785ab", "yes_i_am"}, -- Yes, I'm sure!
		{"@conversation/corellia_rebel_trainer_1:s_d36193f9", "female_forget_it"}, -- Forget it! I'll find someone else!
	}
}
kreezo_convo:addScreen(kreezo_convo_female_relax_sweetie)

-- Female response - forget it (player leaves)
kreezo_convo_female_forget_it = ConvoScreen:new {
	id = "female_forget_it",
	leftDialog = "@conversation/corellia_rebel_trainer_1:s_6f06b651", -- Well - I doubt it... but okay. See you later!
	stopConversation = "true",
	animation = "goodbye",
	options = {}
}
kreezo_convo:addScreen(kreezo_convo_female_forget_it)

-- Female response - kidding (NPC tries to protect her)
kreezo_convo_female_kidding = ConvoScreen:new {
	id = "female_kidding",
	leftDialog = "@conversation/corellia_rebel_trainer_1:s_b73cae6e", -- I'm just trying to protect you, darling. Are you sure you want to join up with the Alliance? You could get killed!
	stopConversation = "false",
	animation = "shrug_hands",
	options = {
		{"@conversation/corellia_rebel_trainer_1:s_4ad222a2", "female_tough"}, -- It can't be that tough if you're still alive.
		{"@conversation/corellia_rebel_trainer_1:s_2b436278", "female_angry"}, -- Just shut up and start the training, okay?
	}
}
kreezo_convo:addScreen(kreezo_convo_female_kidding)

-- Female response - tough (she's got a brain)
kreezo_convo_female_tough = ConvoScreen:new {
	id = "female_tough",
	leftDialog = "@conversation/corellia_rebel_trainer_1:s_1d24deda", -- Hah! Ha! You got a brain in that pretty skull, eh? Good! It will serve you well in battle.
	stopConversation = "false",
	animation = "belly_laugh",
	options = {
		{"@conversation/corellia_rebel_trainer_1:s_c1b9a6e", "yes_i_am"}, -- Then what are we waiting for?
	}
}
kreezo_convo:addScreen(kreezo_convo_female_tough)

-- Female please - NPC pleads for player to join
kreezo_convo_female_please = ConvoScreen:new {
	id = "female_please",
	leftDialog = "@conversation/corellia_rebel_trainer_1:s_83058593", -- Please? The Alliance could really use more strong, intelligent, women pilots... such as you. You can't turn your back on them!
	stopConversation = "false",
	animation = "beg",
	options = {
		{"@conversation/corellia_rebel_trainer_1:s_c6891c87", "yes_i_am"}, -- I will join the Alliance.
		{"@conversation/corellia_rebel_trainer_1:s_70852580", "goodbye"}, -- I'm turning my back on you, not them.
	}
}
kreezo_convo:addScreen(kreezo_convo_female_please)

-- Female response - angry
kreezo_convo_female_angry = ConvoScreen:new {
	id = "female_angry",
	leftDialog = "@conversation/corellia_rebel_trainer_1:s_18617361", -- Whoa! Relax the attitude, okay? I'll train you... I'll train you...
	stopConversation = "false",
	animation = "standing_placate",
	options = {
		{"@conversation/corellia_rebel_trainer_1:s_9aa60522", "yes_i_am"}, -- Let's go!
	}
}
kreezo_convo:addScreen(kreezo_convo_female_angry)

-- Male response - "You're going to teach ME?" path
kreezo_convo_male_teach_me = ConvoScreen:new {
	id = "male_teach_me",
	leftDialog = "@conversation/corellia_rebel_trainer_1:s_c65bb61c", -- Well... yeah! I am a very experienced starfighter pilot. I can teach you everything you need to know - provided that you agree to fly for the Rebel Alliance. How does that strike you?
	stopConversation = "false",
	animation = "explain",
	options = {
		{"@conversation/corellia_rebel_trainer_1:s_e096316d", "yes_i_am"}, -- Sounds wizard. Let's go.
		{"@conversation/corellia_rebel_trainer_1:s_d74fc3aa", "appreciate_that"}, -- I don't want to die for the Rebels.
	}
}
kreezo_convo:addScreen(kreezo_convo_male_teach_me)

-- Female response - "You're going to teach ME?" path
kreezo_convo_female_teach_me = ConvoScreen:new {
	id = "female_teach_me",
	leftDialog = "@conversation/corellia_rebel_trainer_1:s_62a0670", -- You got some sort of problem with me, sister? I've been flying for years and years. What I teach you will keep you alive!
	stopConversation = "false",
	animation = "threaten",
	options = {
		{"@conversation/corellia_rebel_trainer_1:s_5a28f5e9", "yes_i_am"}, -- Relax, flyboy. I'll join your little club.
		{"@conversation/corellia_rebel_trainer_1:s_4dd8aee0", "thanks_no_thanks"}, -- Thanks, but no thanks.
	}
}
kreezo_convo:addScreen(kreezo_convo_female_teach_me)

-- Male response - destiny (You don't know me path)
kreezo_convo_male_destiny = ConvoScreen:new {
	id = "male_destiny",
	leftDialog = "@conversation/corellia_rebel_trainer_1:s_3d8dd8ba", -- "Fine, fine. I'm not looking to fight you - I train pilots... to fight the Empire! What do you say? Are you willing to join the Rebel Alliance?"
	stopConversation = "false",
	animation = "standing_placate",
	options = {
		{"@conversation/corellia_rebel_trainer_1:s_24af7536", "yes_i_am"}, -- The Force has guided me to this... my destiny.
		{"@conversation/corellia_rebel_trainer_1:s_4785a810", "goodbye"}, -- The Alliance is not ready for me.
	}
}
kreezo_convo:addScreen(kreezo_convo_male_destiny)

-- Female response - pretty face (You don't know me path)
kreezo_convo_female_pretty_face = ConvoScreen:new {
	id = "female_pretty_face",
	leftDialog = "@conversation/corellia_rebel_trainer_1:s_4df7e8e8", -- Oh, but I do! Such a pretty face as yours is hard to forget!
	stopConversation = "false",
	animation = "beckon",
	options = {
		{"@conversation/corellia_rebel_trainer_1:s_70d92009", "female_please"}, -- (Stare intently and silently)
		{"@conversation/corellia_rebel_trainer_1:s_1b11fff2", "goodbye"}, -- You're wasting my time.
		{"@conversation/corellia_rebel_trainer_1:s_c6891c87", "yes_i_am"}, -- I will join the Alliance.
	}
}
kreezo_convo:addScreen(kreezo_convo_female_pretty_face)

-- Join - Player accepted
kreezo_convo_yes_join = ConvoScreen:new {
	id = "yes_join",
	leftDialog = "@conversation/corellia_rebel_trainer_1:s_ae0c01b4", -- Hey there! Ready to get started?
	stopConversation = "false",
	options = {}
}
kreezo_convo:addScreen(kreezo_convo_yes_join)

-- No Join - Player declined (money question)
kreezo_convo_no_join = ConvoScreen:new {
	id = "no_join",
	leftDialog = "@conversation/corellia_rebel_trainer_1:s_12d04a63", -- Ha! Ha! You're funny! People don't get rich flying for the Alliance, okay? They do it because the Empire makes their lives miserable... So join up, already!
	stopConversation = "false",
	animation = "belly_laugh",
	playerAnimation = "shake_head_no",
	options = {
		{"@conversation/corellia_rebel_trainer_1:s_2bf47615", "yes_i_am"}, -- Yeah, sure. Why not.
		{"@conversation/corellia_rebel_trainer_1:s_bc874dd9", "goodbye"}, -- I really don't mind the Empire.
	}
}
kreezo_convo:addScreen(kreezo_convo_no_join)

-- Of course - You don't know me response
kreezo_convo_of_course = ConvoScreen:new {
	id = "of_course",
	leftDialog = "@conversation/corellia_rebel_trainer_1:s_44e3a645", -- Of course. You look like a Rebel to me... Do you have a ship?
	stopConversation = "false",
	animation = "check_wrist_device",
	options = {}
}
kreezo_convo:addScreen(kreezo_convo_of_course)

-- Yes I am - Grants pilot skill (dynamic options added by handler)
kreezo_convo_yes_i_am = ConvoScreen:new {
	id = "yes_i_am",
	leftDialog = "@conversation/corellia_rebel_trainer_1:s_13b7333c", -- Finally. You are now part of the Alliance pilot training program.
	stopConversation = "false",
	animation = "point_to_self",
	playerAnimation = "nod_head_once",
	options = {}
}
kreezo_convo:addScreen(kreezo_convo_yes_i_am)

-- Yes Ship - Player has a ship
kreezo_convo_yes_ship = ConvoScreen:new {
	id = "yes_ship",
	leftDialog = "@conversation/corellia_rebel_trainer_1:s_ef3cb7bd", -- No problem. Are you ready for your first assignment?
	stopConversation = "false",
	playerAnimation = "nod_head_once",
	options = {
		{"@conversation/corellia_rebel_trainer_1:s_d731f764", "yes_im_ready"}, -- (Shrug and smile.)
		{"@conversation/corellia_rebel_trainer_1:s_90377ed4", "yes_im_ready"}, -- Affirmative!
		{"@conversation/corellia_rebel_trainer_1:s_b4bce31a", "yes_im_ready"}, -- I am ready, Kreezo.
	}
}
kreezo_convo:addScreen(kreezo_convo_yes_ship)

-- Has Active Quest - Go do your mission
kreezo_convo_has_mission = ConvoScreen:new {
	id = "has_mission",
	leftDialog = "@conversation/corellia_rebel_trainer_1:s_790cea65", -- See that up there? That's space... You should be there finishing your mission. Right?
	stopConversation = "true",
	animation = "point_up",
	options = {}
}
kreezo_convo:addScreen(kreezo_convo_has_mission)

-- Has Very First Quest (has mission and certified ship)
kreezo_convo_first_quest_active = ConvoScreen:new {
	id = "first_quest_active",
	leftDialog = "@conversation/corellia_rebel_trainer_1:s_c19ed115", -- You've got your assignment, and the control device for your ship in your datapad. Go to the Starport and access the terminal to launch into space.
	stopConversation = "false",
	animation = "point_away",
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
	animation = "point_away",
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
	animation = "point_away",
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
	animation = "explain",
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
	animation = "explain",
	options = {
		{"@conversation/corellia_rebel_trainer_1:s_7d5c71fb", "how_to_complete"}, -- How do I complete my assignment?
		{"@conversation/corellia_rebel_trainer_1:s_dda9e202", "where_to_go"}, -- Where should I go now?
		{"@conversation/corellia_rebel_trainer_1:s_cb506bf8", "about_datapad"}, -- My starship? In a datapad?
		{"@conversation/corellia_rebel_trainer_1:s_4b0e9ff2", "how_to_return"}, -- How do I get back here?
	}
}
kreezo_convo:addScreen(kreezo_convo_how_to_return)

-- Yes I'm Ready - Grants Quest 1 (screen that starts quest)
kreezo_convo_yes_im_ready = ConvoScreen:new {
	id = "yes_im_ready",
	leftDialog = "@conversation/corellia_rebel_trainer_1:s_c19ed115", -- You've got your assignment, and the control device for your ship in your datapad. Go to the Starport and access the terminal to launch into space.
	stopConversation = "true",
	options = {}
}
kreezo_convo:addScreen(kreezo_convo_yes_im_ready)

-- When will you train me - Quest 2
kreezo_convo_when_train_quest2 = ConvoScreen:new {
	id = "when_train_quest2",
	leftDialog = "@conversation/corellia_rebel_trainer_1:s_b979a424", -- Slow down, there, %NU. I need to know you can be trusted to complete assignments as they are given. I'll train you AFTER you've finished doing a couple more things for me. Now, are you ready to get back to work?
	stopConversation = "false",
	animation = "slow_down",
	options = {
		{"@conversation/corellia_rebel_trainer_1:s_c92d07b4", "quest2_accepted"}, -- Sure. Why not.
		{"@conversation/corellia_rebel_trainer_1:s_5792c0f4", "quest2_accepted"}, -- (Salute) Yes sir!
		{"@conversation/corellia_rebel_trainer_1:s_e2d604a4", "quest2_accepted"}, -- I am more than ready, Kreezo.
		{"@conversation/corellia_rebel_trainer_1:s_b39049de", "when_train_quest2"}, -- When will you train me?
	}
}
kreezo_convo:addScreen(kreezo_convo_when_train_quest2)

-- When will you train me - Quest 4
kreezo_convo_when_train_quest4 = ConvoScreen:new {
	id = "when_train_quest4",
	leftDialog = "@conversation/corellia_rebel_trainer_1:s_b8281380", -- Not quite yet, %NU. I just need for you to complete one more assignment. Are you up for it?
	stopConversation = "false",
	animation = "slow_down",
	options = {
		{"@conversation/corellia_rebel_trainer_1:s_1bdcc6fa", "quest4_accepted"}, -- All right. Let's hear it! (Path A)
		{"@conversation/corellia_rebel_trainer_1:s_6b490480", "quest4_salute_accepted"}, -- (Salute) Affirmative! (Path B)
		{"@conversation/corellia_rebel_trainer_1:s_2477af4a", "quest4_alliance_accepted"}, -- For the Alliance... always. (Path C)
		{"@conversation/corellia_rebel_trainer_1:s_b39049de", "when_train_quest4"}, -- When will you train me?
	}
}
kreezo_convo:addScreen(kreezo_convo_when_train_quest4)

-- Failed Quest 1
kreezo_convo_failed_quest1 = ConvoScreen:new {
	id = "failed_quest1",
	leftDialog = "@conversation/corellia_rebel_trainer_1:s_e2d918c4", -- What happened on your patrol, pilot?
	stopConversation = "false",
	animation = "point_accusingly",
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

-- Failed Quest 2
kreezo_convo_failed_quest2 = ConvoScreen:new {
	id = "failed_quest2",
	leftDialog = "@conversation/corellia_rebel_trainer_1:s_e46d50f4", -- So let's hear all the gory details.
	stopConversation = "false",
	animation = "listen",
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

-- Failed Quest 3
kreezo_convo_failed_quest3 = ConvoScreen:new {
	id = "failed_quest3",
	leftDialog = "@conversation/corellia_rebel_trainer_1:s_43092a4a", -- So what happened out there?
	stopConversation = "false",
	animation = "explain",
	options = {
		{"@conversation/corellia_rebel_trainer_1:s_2a1af6a8", "retry_quest3"}, -- The transport was destroyed.
		{"@conversation/corellia_rebel_trainer_1:s_64355c70", "retry_quest3"}, -- There were too many TIEs.
		{"@conversation/corellia_rebel_trainer_1:s_e102b38d", "retry_quest3"}, -- I couldn't find it in time.
	}
}
kreezo_convo:addScreen(kreezo_convo_failed_quest3)

-- Retry Quest 3
kreezo_convo_retry_quest3 = ConvoScreen:new {
	id = "retry_quest3",
	leftDialog = "@conversation/corellia_rebel_trainer_1:s_aa03098a", -- We have terrible news from Alliance HQ. A refugee convoy was attacked by TIE fighters...
	stopConversation = "true",
	options = {}
}
kreezo_convo:addScreen(kreezo_convo_retry_quest3)

-- Failed Quest 4
kreezo_convo_failed_quest4 = ConvoScreen:new {
	id = "failed_quest4",
	leftDialog = "@conversation/corellia_rebel_trainer_1:s_3339950", -- What happened up there?
	stopConversation = "false",
	animation = "shake_head_no",
	options = {
		{"@conversation/corellia_rebel_trainer_1:s_af180d19", "retry_quest4"}, -- That TIE Veteran was tough.
		{"@conversation/corellia_rebel_trainer_1:s_afd8ea50", "retry_quest4"}, -- Give me another shot at him!
		{"@conversation/corellia_rebel_trainer_1:s_d2b22f30", "retry_quest4"}, -- I was overwhelmed by numbers.
	}
}
kreezo_convo:addScreen(kreezo_convo_failed_quest4)

-- Retry Quest 4
kreezo_convo_retry_quest4 = ConvoScreen:new {
	id = "retry_quest4",
	leftDialog = "@conversation/corellia_rebel_trainer_1:s_32190415", -- Hey! Good to see ya again. Got a new mission brewing. You are going to LOVE this!
	stopConversation = "true",
	options = {}
}
kreezo_convo:addScreen(kreezo_convo_retry_quest4)

-- Grant Quest 2
kreezo_convo_grant_quest2 = ConvoScreen:new {
	id = "grant_quest2",
	leftDialog = "@conversation/corellia_rebel_trainer_1:s_282d2761", -- Got another one for ya! It's time to get even with those TIE fighters that jumped you on your last patrol. You ready?
	stopConversation = "false",
	animation = "nod_head_once",
	options = {
		{"@conversation/corellia_rebel_trainer_1:s_c92d07b4", "quest2_accepted"}, -- Sure. Why not.
		{"@conversation/corellia_rebel_trainer_1:s_5792c0f4", "quest2_accepted"}, -- (Salute) Yes sir!
		{"@conversation/corellia_rebel_trainer_1:s_e2d604a4", "quest2_accepted"}, -- I am more than ready, Kreezo.
		{"@conversation/corellia_rebel_trainer_1:s_b39049de", "when_train_quest2"}, -- When will you train me?
	}
}
kreezo_convo:addScreen(kreezo_convo_grant_quest2)

-- Quest 2 Accepted
kreezo_convo_quest2_accepted = ConvoScreen:new {
	id = "quest2_accepted",
	leftDialog = "@conversation/corellia_rebel_trainer_1:s_a592576c", -- Gonzo! Let's strike back at the infernal Empire. Find four TIE fighters in the Corellia system and destroy them!
	animation = "explain",
	stopConversation = "false",
	options = {
		{"@conversation/corellia_rebel_trainer_1:s_908b3b7a", "quest2_details"}, -- What do you want me to do about it?
		{"@conversation/corellia_rebel_trainer_1:s_ef167e72", "quest2_location"}, -- Where am I headed?
		{"@conversation/corellia_rebel_trainer_1:s_dc649bb3", "quest2_goodbye"}, -- I'm on my way!
	}
}
kreezo_convo:addScreen(kreezo_convo_quest2_accepted)

-- Quest 2 Details
kreezo_convo_quest2_details = ConvoScreen:new {
	id = "quest2_details",
	leftDialog = "@conversation/corellia_rebel_trainer_1:s_b416fca1", -- Blast 'em! Alliance HQ says you gotta bring down four TIE fighters, should be a walk in the park for you, right?
	animation = "explain",
	stopConversation = "false",
	options = {
		{"@conversation/corellia_rebel_trainer_1:s_ef167e72", "quest2_location"}, -- Where am I headed?
		{"@conversation/corellia_rebel_trainer_1:s_dc649bb3", "quest2_goodbye"}, -- I'm on my way!
	}
}
kreezo_convo:addScreen(kreezo_convo_quest2_details)

-- Quest 2 Location
kreezo_convo_quest2_location = ConvoScreen:new {
	id = "quest2_location",
	leftDialog = "@conversation/corellia_rebel_trainer_1:s_7c899d3e", -- We don't have an exact location, search the Corellia system for TIE fighters and blast 'em!
	animation = "explain",
	stopConversation = "true",
	options = {}
}
kreezo_convo:addScreen(kreezo_convo_quest2_location)

-- Quest 2 Goodbye
kreezo_convo_quest2_goodbye = ConvoScreen:new {
	id = "quest2_goodbye",
	leftDialog = "@conversation/corellia_rebel_trainer_1:s_90f5b9d8", -- Make sure you stay in one piece, man!
	animation = "goodbye",
	stopConversation = "true",
	options = {}
}
kreezo_convo:addScreen(kreezo_convo_quest2_goodbye)

-- Grant Quest 4
kreezo_convo_grant_quest4 = ConvoScreen:new {
	id = "grant_quest4",
	leftDialog = "@conversation/corellia_rebel_trainer_1:s_32190415", -- Hey! Good to see ya again. Got a new mission brewing. You are going to LOVE this!
	stopConversation = "false",
	animation = "greet",
	options = {
		{"@conversation/corellia_rebel_trainer_1:s_1bdcc6fa", "quest4_accepted"}, -- All right. Let's hear it! (Path A)
		{"@conversation/corellia_rebel_trainer_1:s_6b490480", "quest4_salute_accepted"}, -- (Salute) Affirmative! (Path B)
		{"@conversation/corellia_rebel_trainer_1:s_2477af4a", "quest4_alliance_accepted"}, -- For the Alliance... always. (Path C)
		{"@conversation/corellia_rebel_trainer_1:s_b39049de", "when_train_quest4"}, -- When will you train me?
	}
}
kreezo_convo:addScreen(kreezo_convo_grant_quest4)

--[[
	PATH A: Casual path ("All right. Let's hear it!")
	Options loop with female-only grief option until goodbye
--]]

-- Quest 4 Accepted (Path A - options added dynamically for gender)
kreezo_convo_quest4_accepted = ConvoScreen:new {
	id = "quest4_accepted",
	leftDialog = "@conversation/corellia_rebel_trainer_1:s_96595faf", -- Most of the grief we've been getting here in Corellia can be traced back to a single operation and a lone commander...
	stopConversation = "false",
	animation = "explain",
	options = {}
}
kreezo_convo:addScreen(kreezo_convo_quest4_accepted)

-- Quest 4 Commander Info (Path A)
kreezo_convo_quest4_commander = ConvoScreen:new {
	id = "quest4_commander",
	leftDialog = "@conversation/corellia_rebel_trainer_1:s_7f50c50e", -- He's an old Imperial Ace pilot traveling incognito. He'll be flying a standard TIE fighter. Your targeting system will recognize his signal as that of a 'TIE Veteran' pilot.
	stopConversation = "false",
	animation = "explain",
	options = {}
}
kreezo_convo:addScreen(kreezo_convo_quest4_commander)

-- Quest 4 Location Info (Path A)
kreezo_convo_quest4_location = ConvoScreen:new {
	id = "quest4_location",
	leftDialog = "@conversation/corellia_rebel_trainer_1:s_3de34560", -- We have a nav point for you. Very likely he can be found in this area along with several of his trainees. Be careful - they're just trainees... but there might be a lot of them.
	stopConversation = "false",
	animation = "wave_finger_warning",
	options = {}
}
kreezo_convo:addScreen(kreezo_convo_quest4_location)

-- Quest 4 Grief (Path A - Female Only response)
kreezo_convo_quest4_grief = ConvoScreen:new {
	id = "quest4_grief",
	leftDialog = "@conversation/corellia_rebel_trainer_1:s_e66b30af", -- Aw. How could you say that? After all I've done for you?
	stopConversation = "false",
	animation = "slump_head",
	options = {}
}
kreezo_convo:addScreen(kreezo_convo_quest4_grief)

-- Quest 4 Goodbye (Path A)
kreezo_convo_quest4_goodbye = ConvoScreen:new {
	id = "quest4_goodbye",
	leftDialog = "@conversation/corellia_rebel_trainer_1:s_4aa8e211", -- I'm sure you will, don't get too confident though. Good luck!
	stopConversation = "true",
	animation = "goodbye",
	options = {}
}
kreezo_convo:addScreen(kreezo_convo_quest4_goodbye)

--[[
	PATH B: Military/Salute path ("(Salute) Affirmative!")
	2 options, gender-specific goodbye
--]]

-- Quest 4 Salute Accepted (Path B - options added dynamically)
kreezo_convo_quest4_salute_accepted = ConvoScreen:new {
	id = "quest4_salute_accepted",
	leftDialog = "@conversation/corellia_rebel_trainer_1:s_75a759b0", -- Most of our problems here in Corellia are the work of one TIE Veteran pilot. He's moved a lot of trainees into the area with hopes of overwhelming us with superior numbers. We want you to take him out. It'll set the Empire back pretty far, I think...
	stopConversation = "false",
	animation = "explain",
	options = {}
}
kreezo_convo:addScreen(kreezo_convo_quest4_salute_accepted)

-- Quest 4 Salute Pilot Info (Path B)
kreezo_convo_quest4_salute_pilot = ConvoScreen:new {
	id = "quest4_salute_pilot",
	leftDialog = "@conversation/corellia_rebel_trainer_1:s_72767fa4", -- He's a veteran pilot traveling incognito. Should be in a standard TIE fighter. Your tactical computer will recognize his signal as a 'TIE Veteran.'
	stopConversation = "false",
	animation = "explain",
	options = {}
}
kreezo_convo:addScreen(kreezo_convo_quest4_salute_pilot)

-- Quest 4 Salute Goodbye (Path B - dialog set dynamically for gender)
kreezo_convo_quest4_salute_goodbye = ConvoScreen:new {
	id = "quest4_salute_goodbye",
	leftDialog = "@conversation/corellia_rebel_trainer_1:s_90422eb5", -- Good luck. (female default, male gets s_fe6d50dd)
	stopConversation = "true",
	animation = "goodbye",
	options = {}
}
kreezo_convo:addScreen(kreezo_convo_quest4_salute_goodbye)

--[[
	PATH C: Alliance/Formal path ("For the Alliance... always.")
	3 options, formal salute goodbye
--]]

-- Quest 4 Alliance Accepted (Path C - options added dynamically)
kreezo_convo_quest4_alliance_accepted = ConvoScreen:new {
	id = "quest4_alliance_accepted",
	leftDialog = "@conversation/corellia_rebel_trainer_1:s_1f34ee71", -- So you know - the operations being carried out against our transports are the work of one lone commander. The Empire dispatched him here some time ago. His mission is to destabilize Alliance traffic so that they can capture our munitions, and kidnap our special-operations personnel.
	stopConversation = "false",
	animation = "explain",
	options = {}
}
kreezo_convo:addScreen(kreezo_convo_quest4_alliance_accepted)

-- Quest 4 Alliance Veteran Info (Path C)
kreezo_convo_quest4_alliance_veteran = ConvoScreen:new {
	id = "quest4_alliance_veteran",
	leftDialog = "@conversation/corellia_rebel_trainer_1:s_6d453fbf", -- This TIE pilot is flying a standard fighter. Your tactical computer will recognize him as a 'TIE Veteran.'
	stopConversation = "false",
	animation = "explain",
	options = {}
}
kreezo_convo:addScreen(kreezo_convo_quest4_alliance_veteran)

-- Quest 4 Alliance Targets Info (Path C)
kreezo_convo_quest4_alliance_targets = ConvoScreen:new {
	id = "quest4_alliance_targets",
	leftDialog = "@conversation/corellia_rebel_trainer_1:s_c3d77bb4", -- Expect the rally point to be patrolled by junior TIE cadets. They will be quick to respond if they see you first - so be very careful. Keep your eye out for the veteran TIE fighter pilot, eliminate him, and get back here as soon as you can.
	stopConversation = "false",
	animation = "explain",
	options = {}
}
kreezo_convo:addScreen(kreezo_convo_quest4_alliance_targets)

-- Quest 4 Alliance Goodbye (Path C)
kreezo_convo_quest4_alliance_goodbye = ConvoScreen:new {
	id = "quest4_alliance_goodbye",
	leftDialog = "@conversation/corellia_rebel_trainer_1:s_f11f8879", -- Just bring us victory, my friend.
	stopConversation = "true",
	animation = "salute1",
	options = {}
}
kreezo_convo:addScreen(kreezo_convo_quest4_alliance_goodbye)

-- Excellent Work - Quest 1 complete, ready for quest 2
kreezo_convo_excellent_work = ConvoScreen:new {
	id = "excellent_work",
	leftDialog = "@conversation/corellia_rebel_trainer_1:s_66010040", -- So, let's hear it! What happened out there?
	stopConversation = "false",
	animation = "salute2",
	options = {
		{"@conversation/corellia_rebel_trainer_1:s_5bec38ba", "i_was_attacked"}, -- TIE Fighters attacked me!
		{"@conversation/corellia_rebel_trainer_1:s_43a157c9", "imperial_ambush"}, -- The patrol was interrupted by an Imperial ambush!
		{"@conversation/corellia_rebel_trainer_1:s_941b03d0", "nothing_to_it"}, -- Nothing special.
	}
}
kreezo_convo:addScreen(kreezo_convo_excellent_work)

-- I was attacked - Quest 1 report (TIE Fighters attacked me!)
kreezo_convo_i_was_attacked = ConvoScreen:new {
	id = "i_was_attacked",
	leftDialog = "@conversation/corellia_rebel_trainer_1:s_ab8b2db5", -- You don't say! In that case, we can scrap the new transport route. Alliance HQ is going to have to come up with another plan. Good work, pilot!
	stopConversation = "true",
	animation = "rub_chin_thoughtful",
	options = {}
}
kreezo_convo:addScreen(kreezo_convo_i_was_attacked)

-- Imperial ambush - Quest 1 report (The patrol was interrupted by an Imperial ambush!)
kreezo_convo_imperial_ambush = ConvoScreen:new {
	id = "imperial_ambush",
	leftDialog = "@conversation/corellia_rebel_trainer_1:s_4b1458bf", -- That's bad news. This means that the Empire is aware of our plans to reopen secret transport routes here in Corellia. Bad, bad news. Glad you're okay, though! Great work!
	stopConversation = "true",
	animation = "shake_head_disgust",
	options = {}
}
kreezo_convo:addScreen(kreezo_convo_imperial_ambush)

-- Nothing to it - Quest 1 report (nothing special) - NPC questions player
kreezo_convo_nothing_to_it = ConvoScreen:new {
	id = "nothing_to_it",
	leftDialog = "@conversation/corellia_rebel_trainer_1:s_73af9681", -- Really? Alliance HQ is saying that other patrols are getting smacked by long-range TIE sweeps. You didn't encounter any resistance?
	stopConversation = "false",
	animation = "rub_chin_thoughtful",
	options = {
		{"@conversation/corellia_rebel_trainer_1:s_a66b0c40", "not_resistance"}, -- I wouldn't call it 'resistance.'
		{"@conversation/corellia_rebel_trainer_1:s_c02ffe47", "tie_intercepted"}, -- A wing of TIE fighters intercepted me.
	}
}
kreezo_convo:addScreen(kreezo_convo_nothing_to_it)

-- Not resistance - Quest 1 report follow-up
kreezo_convo_not_resistance = ConvoScreen:new {
	id = "not_resistance",
	leftDialog = "@conversation/corellia_rebel_trainer_1:s_5b72d948", -- Oh no? So I guess you made quick work of them. Good. Bad news for the new transport route, though. Check back with me later for another assignment.
	stopConversation = "true",
	animation = "shake_head_no",
	options = {}
}
kreezo_convo:addScreen(kreezo_convo_not_resistance)

-- TIE intercepted - Quest 1 report follow-up
kreezo_convo_tie_intercepted = ConvoScreen:new {
	id = "tie_intercepted",
	leftDialog = "@conversation/corellia_rebel_trainer_1:s_cea58c15", -- Ha! Bad luck for them, huh? Glad to see you're still in one piece. Alliance HQ will likely scrap their plans for a new transport route.
	stopConversation = "true",
	animation = "laugh",
	options = {}
}
kreezo_convo:addScreen(kreezo_convo_tie_intercepted)

-- Excellent Work 2 - Quest 2 complete, ready for quest 3 (options added dynamically for gender)
kreezo_convo_excellent_work2 = ConvoScreen:new {
	id = "excellent_work2",
	leftDialog = "@conversation/corellia_rebel_trainer_1:s_9f5447cf", -- Alliance HQ already sent word! You blasted those TIE fighters to dust! You wanna share some details?
	stopConversation = "false",
	options = {}
}
kreezo_convo:addScreen(kreezo_convo_excellent_work2)

-- What's next - Quest 2 report
kreezo_convo_whats_next = ConvoScreen:new {
	id = "whats_next",
	leftDialog = "@conversation/corellia_rebel_trainer_1:s_aa03098a", -- We have terrible news from Alliance HQ. A refugee convoy was attacked by TIE fighters...
	stopConversation = "false",
	playerAnimation = "shrug_hands",
	options = {
		{"@conversation/corellia_rebel_trainer_1:s_af95b1e2", "train_me3"}, -- You need me to find it, right?
		{"@conversation/corellia_rebel_trainer_1:s_49bfaf2", "train_me3"}, -- (Salute) For the Alliance!
		{"@conversation/corellia_rebel_trainer_1:s_5adefc5c", "train_me3"}, -- Refugees?! Those monsters!
	}
}
kreezo_convo:addScreen(kreezo_convo_whats_next)

-- Was a snap - Quest 2 report (detailed)
kreezo_convo_was_a_snap = ConvoScreen:new {
	id = "was_a_snap",
	leftDialog = "@conversation/corellia_rebel_trainer_1:s_aa03098a", -- We have terrible news from Alliance HQ. A refugee convoy was attacked by TIE fighters...
	stopConversation = "false",
	animation = "explain",
	playerAnimation = "snap_finger1",
	options = {
		{"@conversation/corellia_rebel_trainer_1:s_af95b1e2", "train_me3"}, -- You need me to find it, right?
		{"@conversation/corellia_rebel_trainer_1:s_49bfaf2", "train_me3"}, -- (Salute) For the Alliance!
		{"@conversation/corellia_rebel_trainer_1:s_5adefc5c", "train_me3"}, -- Refugees?! Those monsters!
	}
}
kreezo_convo:addScreen(kreezo_convo_was_a_snap)

-- Train Me 3 - Grants Quest 3
kreezo_convo_train_me3 = ConvoScreen:new {
	id = "train_me3",
	leftDialog = "@conversation/corellia_rebel_trainer_1:s_e564c71b", -- Am I that obvious? Search for the transport. When you find it - escort it out of the system before the Empire can finish 'em off, okay?
	stopConversation = "false",
	animation = "shrug_hands",
	options = {
		{"@conversation/corellia_rebel_trainer_1:s_ad33f74a", "quest3_location"}, -- Where do I look?
		{"@conversation/corellia_rebel_trainer_1:s_3f36d6ff", "quest3_importance"}, -- Why is this trans so important?
		{"@conversation/corellia_rebel_trainer_1:s_b897f5e1", "quest3_goodbye"}, -- I'm on it!
	}
}
kreezo_convo:addScreen(kreezo_convo_train_me3)

-- Quest 3 Location
kreezo_convo_quest3_location = ConvoScreen:new {
	id = "quest3_location",
	leftDialog = "@conversation/corellia_rebel_trainer_1:s_86cd4fa8", -- We'll upload a suite of navigation points that are likely candidates. The transport pilot is no slouch - he will be trying to get back to friendly territory as soon as he can. From what I heard, they're pretty badly damaged.
	animation = "explain",
	stopConversation = "false",
	options = {
		{"@conversation/corellia_rebel_trainer_1:s_ad33f74a", "quest3_location"}, -- Where do I look?
		{"@conversation/corellia_rebel_trainer_1:s_3f36d6ff", "quest3_importance"}, -- Why is this trans so important?
		{"@conversation/corellia_rebel_trainer_1:s_b897f5e1", "quest3_goodbye"}, -- I'm on it!
	}
}
kreezo_convo:addScreen(kreezo_convo_quest3_location)

-- Quest 3 Importance (dialog set dynamically for gender)
kreezo_convo_quest3_importance = ConvoScreen:new {
	id = "quest3_importance",
	leftDialog = "@conversation/corellia_rebel_trainer_1:s_5f75a31a", -- They're civilian refugees, man! Some Gungan, some Human, and a handful of MonCal... (male default, female set in handler)
	animation = "explain",
	stopConversation = "false",
	options = {
		{"@conversation/corellia_rebel_trainer_1:s_ad33f74a", "quest3_location"}, -- Where do I look?
		{"@conversation/corellia_rebel_trainer_1:s_3f36d6ff", "quest3_importance"}, -- Why is this trans so important?
		{"@conversation/corellia_rebel_trainer_1:s_b897f5e1", "quest3_goodbye"}, -- I'm on it!
	}
}
kreezo_convo:addScreen(kreezo_convo_quest3_importance)

-- Quest 3 Goodbye
kreezo_convo_quest3_goodbye = ConvoScreen:new {
	id = "quest3_goodbye",
	leftDialog = "@conversation/corellia_rebel_trainer_1:s_6bed0484", -- Go get 'em!
	animation = "goodbye",
	stopConversation = "true",
	options = {}
}
kreezo_convo:addScreen(kreezo_convo_quest3_goodbye)

-- Excellent Work 3 - Quest 3 complete, ready for quest 4
kreezo_convo_excellent_work3 = ConvoScreen:new {
	id = "excellent_work3",
	leftDialog = "@conversation/corellia_rebel_trainer_1:s_bb9e839f", -- Hey! So what happened up there?
	stopConversation = "false",
	animation = "greet",
	options = {
		{"@conversation/corellia_rebel_trainer_1:s_e37282e3", "quest3_rewarded"}, -- Standard space-hero stuff.
		{"@conversation/corellia_rebel_trainer_1:s_9df39ab2", "quest3_rewarded"}, -- (Salute) The Alliance transport has been rescued!
		{"@conversation/corellia_rebel_trainer_1:s_20ef9c42", "quest3_rewarded"}, -- Mission accomplished.
	}
}
kreezo_convo:addScreen(kreezo_convo_excellent_work3)

-- Quest 3 Rewarded (dialog set dynamically for gender)
kreezo_convo_quest3_rewarded = ConvoScreen:new {
	id = "quest3_rewarded",
	leftDialog = "@conversation/corellia_rebel_trainer_1:s_7bebfa97", -- Ha! Excellent! Keep up the heroics! (male default, female set in handler)
	stopConversation = "false",
	animation = "laugh",
	options = {
		{"@conversation/corellia_rebel_trainer_1:s_1c8bddbb", "quest3_reward_explain"}, -- What is it?
	}
}
kreezo_convo:addScreen(kreezo_convo_quest3_rewarded)

-- Quest 3 Reward Explain (dialog set dynamically for species)
kreezo_convo_quest3_reward_explain = ConvoScreen:new {
	id = "quest3_reward_explain",
	leftDialog = "@conversation/corellia_rebel_trainer_1:s_420fb842", -- It's a flight suit! You'll look like a real soldier in this, huh? (default, Wookiee/Ithorian set in handler)
	stopConversation = "true",
	options = {}
}
kreezo_convo:addScreen(kreezo_convo_quest3_reward_explain)

-- Missions Complete - All 4 quests done, ready for first training (options added dynamically based on skills player doesn't have)
kreezo_convo_missions_complete = ConvoScreen:new {
	id = "missions_complete",
	leftDialog = "@conversation/corellia_rebel_trainer_1:s_a0f35e59", -- Hi there! You now have all the experience you need to be trained in something new. I can teach you the proper handling of superior starfighters...
	stopConversation = "false",
	options = {}
}
kreezo_convo:addScreen(kreezo_convo_missions_complete)

-- More Training (has XP for training)
kreezo_convo_more_training = ConvoScreen:new {
	id = "more_training",
	leftDialog = "@conversation/corellia_rebel_trainer_1:s_246d08d7", -- You have enough experience for more training. Are you ready to learn?
	stopConversation = "false",
	animation = "explain",
	options = {}
}
kreezo_convo:addScreen(kreezo_convo_more_training)

-- Train Player Fighters - Grants starships_01 skill
kreezo_convo_train_player_fighters = ConvoScreen:new {
	id = "train_player_fighters",
	leftDialog = "@conversation/corellia_rebel_trainer_1:s_248af92", -- Here is your introduction to Alliance starfighter use.
	stopConversation = "true",
	animation = "nod_head_once",
	options = {}
}
kreezo_convo:addScreen(kreezo_convo_train_player_fighters)

-- Train Player Fighters Free - Grants starships_01 skill (no XP cost)
kreezo_convo_train_player_fighters_free = ConvoScreen:new {
	id = "train_player_fighters_free",
	leftDialog = "@conversation/corellia_rebel_trainer_1:s_248af92", -- Here is your introduction to Alliance starfighter use.
	stopConversation = "true",
	animation = "nod_head_once",
	options = {}
}
kreezo_convo:addScreen(kreezo_convo_train_player_fighters_free)

-- Train Player Component - Grants weapons_01 skill
kreezo_convo_train_player_component = ConvoScreen:new {
	id = "train_player_component",
	leftDialog = "@conversation/corellia_rebel_trainer_1:s_6929ad0f", -- Congratulations. You have achieved the first rank of Weapons specialization.
	stopConversation = "true",
	animation = "nod_head_once",
	options = {}
}
kreezo_convo:addScreen(kreezo_convo_train_player_component)

-- Train Player Component Free - Grants weapons_01 skill (no XP cost)
kreezo_convo_train_player_component_free = ConvoScreen:new {
	id = "train_player_component_free",
	leftDialog = "@conversation/corellia_rebel_trainer_1:s_6929ad0f", -- Congratulations. You have achieved the first rank of Weapons specialization.
	stopConversation = "true",
	animation = "nod_head_once",
	options = {}
}
kreezo_convo:addScreen(kreezo_convo_train_player_component_free)

-- Train Player Basics - Grants procedures_01 skill
kreezo_convo_train_player_basics = ConvoScreen:new {
	id = "train_player_basics",
	leftDialog = "@conversation/corellia_rebel_trainer_1:s_4cccd3f2", -- No problem... no problem. Here's your introduction to Alliance starfighter techniques.
	stopConversation = "true",
	animation = "nod_head_once",
	options = {}
}
kreezo_convo:addScreen(kreezo_convo_train_player_basics)

-- Train Player Basics Free - Grants procedures_01 skill (no XP cost)
kreezo_convo_train_player_basics_free = ConvoScreen:new {
	id = "train_player_basics_free",
	leftDialog = "@conversation/corellia_rebel_trainer_1:s_4cccd3f2", -- No problem... no problem. Here's your introduction to Alliance starfighter techniques.
	stopConversation = "true",
	animation = "nod_head_once",
	options = {}
}
kreezo_convo:addScreen(kreezo_convo_train_player_basics_free)

-- Train Player Droid - Grants droid_01 skill
kreezo_convo_train_player_droid = ConvoScreen:new {
	id = "train_player_droid",
	leftDialog = "@conversation/corellia_rebel_trainer_1:s_7fd68073", -- Great! You now have basic droid programming abilities!
	stopConversation = "true",
	animation = "nod_head_once",
	options = {}
}
kreezo_convo:addScreen(kreezo_convo_train_player_droid)

-- Train Player Droid Free - Grants droid_01 skill (no XP cost)
kreezo_convo_train_player_droid_free = ConvoScreen:new {
	id = "train_player_droid_free",
	leftDialog = "@conversation/corellia_rebel_trainer_1:s_7fd68073", -- Great! You now have basic droid programming abilities!
	stopConversation = "true",
	animation = "nod_head_once",
	options = {}
}
kreezo_convo:addScreen(kreezo_convo_train_player_droid_free)

-- Completed Kreezo - Has all tier 1 skills, send to next trainer
kreezo_convo_completed_kreezo = ConvoScreen:new {
	id = "completed_kreezo",
	leftDialog = "@conversation/corellia_rebel_trainer_1:s_b2b30e20", -- Hey, so... the Alliance has asked me to recommend pilots that are ready for more challenge. Evidently something big is going on above planet Lok. Rebel Intelligence is all over it... and they need pilots.
	stopConversation = "false",
	animation = "shake_head_no",
	options = {
		{"@conversation/corellia_rebel_trainer_1:s_386363ba", "viopa_date"}, -- Yeah, so?
		{"@conversation/corellia_rebel_trainer_1:s_c999ae60", "viopa_meet"}, -- Let me at 'em!
	}
}
kreezo_convo:addScreen(kreezo_convo_completed_kreezo)

--[[
	PATH A: Casual path ("Yeah, so?") - Viopa info loop
	3 looping options with gender-specific goodbye
--]]

-- Viopa Date - Path A entry (options added dynamically, waypoint granted in handler)
kreezo_convo_viopa_date = ConvoScreen:new {
	id = "viopa_date",
	leftDialog = "@conversation/corellia_rebel_trainer_1:s_c36f7614", -- So? So you've got a date with Lady Viopa of Alliance Intel. You think you can handle it?
	stopConversation = "false",
	animation = "shrug_hands",
	options = {}
}
kreezo_convo:addScreen(kreezo_convo_viopa_date)

-- Viopa Who - Path A info (loops back to Path A options)
kreezo_convo_viopa_who = ConvoScreen:new {
	id = "viopa_who",
	leftDialog = "@conversation/corellia_rebel_trainer_1:s_44f7abd1", -- I've never met her. I think she's Mon Cal? I know she's high-ranking Alliance Intel... so she's not exactly my type.
	stopConversation = "false",
	animation = "shrug_hands",
	options = {}
}
kreezo_convo:addScreen(kreezo_convo_viopa_who)

-- Viopa Where - Path A info (loops back to Path A options)
kreezo_convo_viopa_where_a = ConvoScreen:new {
	id = "viopa_where_a",
	leftDialog = "@conversation/corellia_rebel_trainer_1:s_e003aec9", -- She's staying with Nym on Lok. The Rebellion has made a deal to keep Viopa safe in Nym's compound.
	stopConversation = "false",
	animation = "explain",
	options = {}
}
kreezo_convo:addScreen(kreezo_convo_viopa_where_a)

-- Viopa Bye Casual Female - Path A goodbye (female)
kreezo_convo_viopa_bye_casual_female = ConvoScreen:new {
	id = "viopa_bye_casual_female",
	leftDialog = "@conversation/corellia_rebel_trainer_1:s_4cc5bfd8", -- Maybe when this war is over, you'll let me buy you a drink...
	stopConversation = "true",
	animation = "rub_chin_thoughtful",
	options = {}
}
kreezo_convo:addScreen(kreezo_convo_viopa_bye_casual_female)

-- Viopa Bye Casual Male - Path A goodbye (male)
kreezo_convo_viopa_bye_casual_male = ConvoScreen:new {
	id = "viopa_bye_casual_male",
	leftDialog = "@conversation/corellia_rebel_trainer_1:s_9cdc2b64", -- Take care, buddy!
	stopConversation = "true",
	animation = "goodbye",
	options = {}
}
kreezo_convo:addScreen(kreezo_convo_viopa_bye_casual_male)

--[[
	PATH B: Eager path ("Let me at 'em!") - Viopa/Nym info loop
	3 looping options with Nym sub-branch, gender-specific goodbye
--]]

-- Viopa Meet - Path B entry (options added dynamically, waypoint granted in handler)
kreezo_convo_viopa_meet = ConvoScreen:new {
	id = "viopa_meet",
	leftDialog = "@conversation/corellia_rebel_trainer_1:s_d828284a", -- You got it! Meet the Alliance Intel chief stationed on Lok. Her name is Lady Viopa, and she hangs out in Nym's compound. She'll have work for you when you arrive.
	stopConversation = "false",
	animation = "explain",
	options = {}
}
kreezo_convo:addScreen(kreezo_convo_viopa_meet)

-- Viopa Know More - Path B info (loops back to Path B options)
kreezo_convo_viopa_know_more = ConvoScreen:new {
	id = "viopa_know_more",
	leftDialog = "@conversation/corellia_rebel_trainer_1:s_d2d0a643", -- Nothing, really. She's kinda spooky. Alliance Intel folks generally are, though. Just do your duty and stay out of trouble!
	stopConversation = "false",
	animation = "shrug_hands",
	options = {}
}
kreezo_convo:addScreen(kreezo_convo_viopa_know_more)

-- Nym Info - Path B sub-branch (static option to nym_crossed)
kreezo_convo_nym_info = ConvoScreen:new {
	id = "nym_info",
	leftDialog = "@conversation/corellia_rebel_trainer_1:s_79ff003e", -- Well... nothing. I've had some trouble with his group in the past. But now that we're all working for the Alliance, I can put it behind me.
	stopConversation = "false",
	animation = "shake_head_no",
	options = {
		{"@conversation/corellia_rebel_trainer_1:s_9965dc21", "nym_crossed"}, -- You crossed Nym?
	}
}
kreezo_convo:addScreen(kreezo_convo_nym_info)

-- Nym Crossed - Path B sub-branch response (loops back to Path B options)
kreezo_convo_nym_crossed = ConvoScreen:new {
	id = "nym_crossed",
	leftDialog = "@conversation/corellia_rebel_trainer_1:s_6abdc31f", -- Heh. Once this war is over, if you still want to know - I'll be glad to tell you. For now... take a hike! Good luck out there, pilot.
	stopConversation = "false",
	animation = "laugh",
	options = {}
}
kreezo_convo:addScreen(kreezo_convo_nym_crossed)

-- Viopa Bye Formal Female - Path B goodbye (female)
kreezo_convo_viopa_bye_formal_female = ConvoScreen:new {
	id = "viopa_bye_formal_female",
	leftDialog = "@conversation/corellia_rebel_trainer_1:s_4cc5bfd8", -- Maybe when this war is over, you'll let me buy you a drink...
	stopConversation = "true",
	animation = "goodbye",
	options = {}
}
kreezo_convo:addScreen(kreezo_convo_viopa_bye_formal_female)

-- Viopa Bye Formal Male - Path B goodbye (male)
kreezo_convo_viopa_bye_formal_male = ConvoScreen:new {
	id = "viopa_bye_formal_male",
	leftDialog = "@conversation/corellia_rebel_trainer_1:s_9cdc2b64", -- Take care, buddy!
	stopConversation = "true",
	animation = "goodbye",
	options = {}
}
kreezo_convo:addScreen(kreezo_convo_viopa_bye_formal_male)

-- Go to Viopa (graduated)
kreezo_convo_go_to_viopa = ConvoScreen:new {
	id = "go_to_viopa",
	leftDialog = "@conversation/corellia_rebel_trainer_1:s_24d9c943", -- What are you doing here? You should be working for Lady Viopa on Lok... right?
	stopConversation = "false",
	animation = "shrug_shoulders",
	options = {
		{"@conversation/corellia_rebel_trainer_1:s_b3bebc5e", "directions_to_viopa"}, -- How do I get there?
	}
}
kreezo_convo:addScreen(kreezo_convo_go_to_viopa)

-- Directions to Viopa
kreezo_convo_directions_to_viopa = ConvoScreen:new {
	id = "directions_to_viopa",
	leftDialog = "@conversation/corellia_rebel_trainer_1:s_6f8c5bda", -- You're a pilot, now. Fly there!
	stopConversation = "true",
	animation = "shrug_hands",
	options = {}
}
kreezo_convo:addScreen(kreezo_convo_directions_to_viopa)

-- Duty Missions (default fallback for completed players)
kreezo_convo_duty_missions = ConvoScreen:new {
	id = "duty_missions",
	leftDialog = "@conversation/corellia_rebel_trainer_1:s_7fcd3228", -- Good to see you again. How are things going?
	stopConversation = "false",
	animation = "greet",
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
	leftDialog = "@conversation/corellia_rebel_trainer_1:s_64977077", -- I don't have any missions to assign, but I do have an elective duty mission roster. You could either patrol the system for searching for Imperials, or you could help escort Alliance transports. Would you be interested in an elective duty task?
	stopConversation = "false",
	options = {
		{"@conversation/corellia_rebel_trainer_1:s_46fa0a69", "destroy_duty"}, -- I should sweep and clear Corellia space.
		{"@conversation/corellia_rebel_trainer_1:s_5c625403", "escort_duty"}, -- I would like to protect Alliance transports.
		{"@conversation/corellia_rebel_trainer_1:s_6106187c", "what_is_duty"}, -- What is a duty mission?
	}
}
kreezo_convo:addScreen(kreezo_convo_request_duty)

-- What is a duty mission
kreezo_convo_what_is_duty = ConvoScreen:new {
	id = "what_is_duty",
	leftDialog = "@conversation/corellia_rebel_trainer_1:s_59bfc3b4", -- A duty mission is THE best way to get experience as a pilot. I know that you're anxious to get training, and experience from these missions will get you there faster. Duty missions have no real end so you can just finish up whenever you want. What do you think?
	stopConversation = "false",
	animation = "explain",
	options = {
		{"@conversation/corellia_rebel_trainer_1:s_46fa0a69", "destroy_duty"}, -- I should sweep and clear Corellia space.
		{"@conversation/corellia_rebel_trainer_1:s_5c625403", "escort_duty"}, -- I would like to protect Alliance transports.
	}
}
kreezo_convo:addScreen(kreezo_convo_what_is_duty)

-- Destroy Duty - Grants destroy duty mission
kreezo_convo_destroy_duty = ConvoScreen:new {
	id = "destroy_duty",
	leftDialog = "@conversation/corellia_rebel_trainer_1:s_10d17e63", -- Well... be careful, then. Follow the navigation points and defeat any hostiles that come your way. These 'duty' missions have been prepared for you to gain some much needed space combat experience. You can return to the ground at any time when you feel that you have learned enough.
	stopConversation = "true",
	animation = "salute1",
	options = {}
}
kreezo_convo:addScreen(kreezo_convo_destroy_duty)

-- Escort Duty - Grants escort duty mission
kreezo_convo_escort_duty = ConvoScreen:new {
	id = "escort_duty",
	leftDialog = "@conversation/corellia_rebel_trainer_1:s_69e5db34", -- I'm sure the transport pilots would agree! Follow all nav points, and protect all transports that come under your supervision. These 'duty' missions have been prepared for you to gain some much needed space combat experience. You can return to the ground at any time when you feel that you have learned enough. Good luck!
	stopConversation = "true",
	animation = "salute1",
	options = {}
}
kreezo_convo:addScreen(kreezo_convo_escort_duty)

-- Ground Forces
kreezo_convo_ground_forces = ConvoScreen:new {
	id = "ground_forces",
	leftDialog = "@conversation/corellia_rebel_trainer_1:s_28eea20", -- I didn't see that coming!  You're sure you know what you're getting into?  You could be opening yourself to attack when you least expect it... even as a covert operative.
	stopConversation = "false",
	animation = "slow_down",
	options = {
		{"@conversation/corellia_rebel_trainer_1:s_13d3df42", "boots_on_ground"}, -- I know
	}
}
kreezo_convo:addScreen(kreezo_convo_ground_forces)

kreezo_convo_boots_on_ground = ConvoScreen:new {
	id = "boots_on_ground",
	leftDialog = "@conversation/corellia_rebel_trainer_1:s_2098126f", -- Excellent!  The Rebel Alliance can use some more boots on the ground, too.  Go to a Rebel Recruiter and sign-up!  Heh... they can be hard to find, you know?  But I'm sure you'll manage.
	stopConversation = "true",
	animation = "pound_fist_chest",
	options = {}
}
kreezo_convo:addScreen(kreezo_convo_boots_on_ground)

-- Appreciate That
kreezo_convo_appreciate = ConvoScreen:new {
	id = "appreciate_that",
	leftDialog = "@conversation/corellia_rebel_trainer_1:s_29cee3c8", -- Okay. I can appreciate that, I guess. Good luck...
	stopConversation = "true",
	options = {}
}
kreezo_convo:addScreen(kreezo_convo_appreciate)

-- No Thanks
kreezo_convo_no_thanks = ConvoScreen:new {
	id = "thanks_no_thanks",
	leftDialog = "@conversation/corellia_rebel_trainer_1:s_c61a299", -- You're breakin' my heart!
	stopConversation = "true",
	options = {}
}
kreezo_convo:addScreen(kreezo_convo_no_thanks)

-- Check Back
kreezo_convo_check_back = ConvoScreen:new {
	id = "check_back",
	leftDialog = "@conversation/corellia_rebel_trainer_1:s_431ae604", -- Well, what can you do? Check back with me if you ever get the urge to join up. I'll get you started!
	stopConversation = "true",
	options = {}
}
kreezo_convo:addScreen(kreezo_convo_check_back)

-- Goodbye

kreezo_convo_goodbye = ConvoScreen:new {
	id = "goodbye",
	leftDialog = "@conversation/corellia_rebel_trainer_1:s_29cee3c8", -- Okay. I can appreciate that, I guess. Good luck...
	stopConversation = "true",
	animation = "goodbye",
	playerAnimation = "slump_head",
	options = {}
}
kreezo_convo:addScreen(kreezo_convo_goodbye)

addConversationTemplate("kreezo_convo", kreezo_convo)
