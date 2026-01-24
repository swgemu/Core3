eker_convo = ConvoTemplate:new {
	initialScreen = "",
	templateType = "Lua",
	luaClassHandler = "ekerConvoHandler",
	screens = {}
}

-- Not a Pilot (no JTL skills)
eker_convo_no_jtl = ConvoScreen:new {
	id = "no_jtl",
	leftDialog = "@conversation/tatooine_rebel_trainer_1:s_1d3d8b65", -- You don't look like any sort of pilot to me. I can't help you.
	stopConversation = "true",
	options = {}
}
eker_convo:addScreen(eker_convo_no_jtl)

-- Imperial Pilot
eker_convo_imperial_pilot = ConvoScreen:new {
	id = "imperial_pilot",
	leftDialog = "@conversation/tatooine_rebel_trainer_1:s_d6c8f764", -- Heh. What do you know. An Imperial. Get out of here while you still can!
	stopConversation = "true",
	options = {}
}
eker_convo:addScreen(eker_convo_imperial_pilot)

-- Neutral/Privateer Pilot
eker_convo_neutral_pilot = ConvoScreen:new {
	id = "neutral_pilot",
	leftDialog = "@conversation/tatooine_rebel_trainer_1:s_19d3ee2b", -- I can't help you, smuggler. Try sniffing around Wayfar... you'll find something that suits you.
	stopConversation = "true",
	options = {}
}
eker_convo:addScreen(eker_convo_neutral_pilot)

-- Not a Rebel
eker_convo_not_rebel = ConvoScreen:new {
	id = "not_rebel",
	leftDialog = "@conversation/tatooine_rebel_trainer_1:s_eff4eef6", -- If we are to have any dealings together, you will need to officially join our side. Go find a Recruiter and sign on the dotted line friend.
	stopConversation = "true",
	options = {}
}
eker_convo:addScreen(eker_convo_not_rebel)

-- Non-Crimson Phoenix Rebel Pilot (not on track)
eker_convo_non_crimson_phoenix_pilot = ConvoScreen:new {
	id = "non_crimson_phoenix_pilot",
	leftDialog = "@conversation/tatooine_rebel_trainer_1:s_57c3f83e", -- Always good to see another Rebel pilot... but you're not one of my recruits. What can I do for you?
	stopConversation = "false",
	options = {
		{"@conversation/tatooine_rebel_trainer_1:s_1583743c", "no_missions_available"}, -- Do you have any missions I could fly?
	}
}
eker_convo:addScreen(eker_convo_non_crimson_phoenix_pilot)

-- No Missions Available
eker_convo_no_missions_available = ConvoScreen:new {
	id = "no_missions_available",
	leftDialog = "@conversation/tatooine_rebel_trainer_1:s_57c3f83e", -- dynamic
	stopConversation = "true",
	options = {}
}
eker_convo:addScreen(eker_convo_no_missions_available)

-- Has Active Mission
eker_convo_has_mission = ConvoScreen:new {
	id = "has_mission",
	leftDialog = "@conversation/tatooine_rebel_trainer_1:s_e31d65b7", -- The duty logs indicate that you are in mid-mission. We have nothing to discuss until you are finished.
	stopConversation = "true",
	options = {}
}
eker_convo:addScreen(eker_convo_has_mission)

-- Has Very First Quest (just joined - launch instructions)
eker_convo_has_first_quest = ConvoScreen:new {
	id = "has_first_quest",
	leftDialog = "@conversation/tatooine_rebel_trainer_1:s_c19ed115", -- You've got your assignment, and the control device for your ship in your datapad. Go to the Starport and access the terminal to launch into space.
	stopConversation = "false",
	options = {
		{"@conversation/tatooine_rebel_trainer_1:s_8a4652c6", "launch_instructions"}, -- So now what?
		{"@conversation/tatooine_rebel_trainer_1:s_680cda08", "launch_instructions"}, -- How do I get back from space?
		{"@conversation/tatooine_rebel_trainer_1:s_5bfac9f1", "launch_instructions"}, -- Where's my starship?
	}
}
eker_convo:addScreen(eker_convo_has_first_quest)

-- Launch Instructions
eker_convo_launch_instructions = ConvoScreen:new {
	id = "launch_instructions",
	leftDialog = "@conversation/tatooine_rebel_trainer_1:s_c19ed115", -- dynamic
	stopConversation = "true",
	options = {}
}
eker_convo:addScreen(eker_convo_launch_instructions)

-- Introduction (new pilot - grants novice skill)
eker_convo_introduction = ConvoScreen:new {
	id = "introduction",
	leftDialog = "@conversation/tatooine_rebel_trainer_1:s_1622e456", -- Good to meet you. My name is Da'la Socuna and I am here on behalf of the Rebel Alliance naval forces. I train pilots to fly and fight.
	stopConversation = "false",
	options = {
		{"@conversation/tatooine_rebel_trainer_1:s_78679b31", "join_squadron"}, -- Sounds like fun. Where do I sign?
		{"@conversation/tatooine_rebel_trainer_1:s_3f5c320e", "join_squadron"}, -- I know of the rebellion. I want to help!
		{"@conversation/tatooine_rebel_trainer_1:s_db6b2243", "join_squadron"}, -- We are kindred spirits, Da'la Socuna.
	}
}
eker_convo:addScreen(eker_convo_introduction)

-- Join Squadron (grants novice skill)
eker_convo_join_squadron = ConvoScreen:new {
	id = "join_squadron",
	leftDialog = "@conversation/tatooine_rebel_trainer_1:s_790724e4", -- Then it is fortunate that we have met. I can induct you to the Alliance pilot training program immediately.
	stopConversation = "true",
	options = {}
}
eker_convo:addScreen(eker_convo_join_squadron)

-- No Starship (grants starter ship)
eker_convo_no_starship = ConvoScreen:new {
	id = "no_starship",
	leftDialog = "@conversation/tatooine_rebel_trainer_1:s_19ec1fce", -- Just how exactly do you expect to be a Rebel Alliance pilot without a ship? Here. I'll add these access codes for a small fighter to your datapad. You ought to upgrade to a better ship pretty soon, though.
	stopConversation = "false",
	options = {
		{"@conversation/tatooine_rebel_trainer_1:s_7553991", "grant_quest1"}, -- Yeah, yeah!
		{"@conversation/tatooine_rebel_trainer_1:s_288ce434", "grant_quest1"}, -- Ma'am! Thank you, ma'am!
		{"@conversation/tatooine_rebel_trainer_1:s_a994ca63", "grant_quest1"}, -- For the Alliance!
	}
}
eker_convo:addScreen(eker_convo_no_starship)

-- Grant Quest 1
eker_convo_grant_quest1 = ConvoScreen:new {
	id = "grant_quest1",
	leftDialog = "@conversation/tatooine_rebel_trainer_1:s_784540b7", -- Greetings, pilot! Are you ready for your assignment?
	stopConversation = "false",
	options = {
		{"@conversation/tatooine_rebel_trainer_1:s_d731f764", "quest1_brief"}, -- (Shrug and smile.)
		{"@conversation/tatooine_rebel_trainer_1:s_90377ed4", "quest1_brief"}, -- Affirmative!
		{"@conversation/tatooine_rebel_trainer_1:s_6bb935f1", "quest1_brief"}, -- Yes, Da'la. I am ready.
		{"@conversation/tatooine_rebel_trainer_1:s_7478cd28", "training_question"}, -- Will you train me after this?
	}
}
eker_convo:addScreen(eker_convo_grant_quest1)

-- Quest 1 Brief
eker_convo_quest1_brief = ConvoScreen:new {
	id = "quest1_brief",
	leftDialog = "@conversation/tatooine_rebel_trainer_1:s_784540b7", -- dynamic - quest granted
	stopConversation = "true",
	options = {}
}
eker_convo:addScreen(eker_convo_quest1_brief)

-- Training Question (not yet qualified)
eker_convo_training_question = ConvoScreen:new {
	id = "training_question",
	leftDialog = "@conversation/tatooine_rebel_trainer_1:s_38485fa9", -- Not so fast, Pilot! You need to complete a few assignments before I'll train you. Are you ready?
	stopConversation = "false",
	options = {
		{"@conversation/tatooine_rebel_trainer_1:s_d731f764", "quest1_brief"}, -- (Shrug and smile.)
		{"@conversation/tatooine_rebel_trainer_1:s_90377ed4", "quest1_brief"}, -- Affirmative!
	}
}
eker_convo:addScreen(eker_convo_training_question)

-- Failed Quest 1
eker_convo_failed_quest1 = ConvoScreen:new {
	id = "failed_quest1",
	leftDialog = "@conversation/tatooine_rebel_trainer_1:s_fe789dac", -- Report!
	stopConversation = "false",
	options = {
		{"@conversation/tatooine_rebel_trainer_1:s_151", "retry_quest1"}, -- I failed the mission.
		{"@conversation/tatooine_rebel_trainer_1:s_68ee2577", "retry_quest1"}, -- I could not finish the mission.
	}
}
eker_convo:addScreen(eker_convo_failed_quest1)

-- Failed Quest 1 (Patrol variant)
eker_convo_failed_quest1_patrol = ConvoScreen:new {
	id = "failed_quest1_patrol",
	leftDialog = "@conversation/tatooine_rebel_trainer_1:s_fb9b39e5", -- Report, pilot!
	stopConversation = "false",
	options = {
		{"@conversation/tatooine_rebel_trainer_1:s_4f90bab3", "retry_quest1"}, -- I was unable to finish.
		{"@conversation/tatooine_rebel_trainer_1:s_b9c55cab", "retry_quest1"}, -- I failed the mission.
	}
}
eker_convo:addScreen(eker_convo_failed_quest1_patrol)

-- Retry Quest 1
eker_convo_retry_quest1 = ConvoScreen:new {
	id = "retry_quest1",
	leftDialog = "@conversation/tatooine_rebel_trainer_1:s_784540b7", -- dynamic
	stopConversation = "true",
	options = {}
}
eker_convo:addScreen(eker_convo_retry_quest1)

-- Excellent Work (Quest 1 Complete)
eker_convo_excellent_work = ConvoScreen:new {
	id = "excellent_work",
	leftDialog = "@conversation/tatooine_rebel_trainer_1:s_2c052357", -- Good to see you again, pilot! I will hear your report, now.
	stopConversation = "false",
	options = {
		{"@conversation/tatooine_rebel_trainer_1:s_64b4e5f7", "quest2_grant"}, -- (Brag about blasting TIE fighters)
		{"@conversation/tatooine_rebel_trainer_1:s_97e13b2e", "quest2_grant"}, -- (Brief Da'la with all due accuracy)
		{"@conversation/tatooine_rebel_trainer_1:s_11327023", "quest2_grant"}, -- The patrol was interrupted by a TIE attack.
	}
}
eker_convo:addScreen(eker_convo_excellent_work)

-- Grant Quest 2
eker_convo_quest2_grant = ConvoScreen:new {
	id = "quest2_grant",
	leftDialog = "@conversation/tatooine_rebel_trainer_1:s_406f8d3e", -- It will take a bit to decode your ship sensor data. In the meantime, we have another assignment for you... if you are ready.
	stopConversation = "false",
	options = {
		{"@conversation/tatooine_rebel_trainer_1:s_c92d07b4", "quest2_brief"}, -- Sure. Why not.
		{"@conversation/tatooine_rebel_trainer_1:s_fbac0bde", "quest2_brief"}, -- (Salute) Ma'am! Yes, ma'am!
		{"@conversation/tatooine_rebel_trainer_1:s_7d15be50", "quest2_brief"}, -- I am more than ready, Da'la.
		{"@conversation/tatooine_rebel_trainer_1:s_290", "training_question"}, -- Will you train me after this?
	}
}
eker_convo:addScreen(eker_convo_quest2_grant)

-- Quest 2 Brief
eker_convo_quest2_brief = ConvoScreen:new {
	id = "quest2_brief",
	leftDialog = "@conversation/tatooine_rebel_trainer_1:s_406f8d3e", -- dynamic - quest granted
	stopConversation = "true",
	options = {}
}
eker_convo:addScreen(eker_convo_quest2_brief)

-- Failed Quest 2
eker_convo_failed_quest2 = ConvoScreen:new {
	id = "failed_quest2",
	leftDialog = "@conversation/tatooine_rebel_trainer_1:s_9c146b24", -- I don't like what I'm hearing, pilot! Report, now!
	stopConversation = "false",
	options = {
		{"@conversation/tatooine_rebel_trainer_1:s_6657b5a3", "retry_quest2"}, -- It wasn't my fault!
		{"@conversation/tatooine_rebel_trainer_1:s_740e2e66", "retry_quest2"}, -- Sorry, ma'am!
		{"@conversation/tatooine_rebel_trainer_1:s_54ec182b", "retry_quest2"}, -- I failed to destroy the targets.
	}
}
eker_convo:addScreen(eker_convo_failed_quest2)

-- Retry Quest 2
eker_convo_retry_quest2 = ConvoScreen:new {
	id = "retry_quest2",
	leftDialog = "@conversation/tatooine_rebel_trainer_1:s_406f8d3e", -- dynamic
	stopConversation = "true",
	options = {}
}
eker_convo:addScreen(eker_convo_retry_quest2)

-- Excellent Work 2 (Quest 2 Complete)
eker_convo_excellent_work2 = ConvoScreen:new {
	id = "excellent_work2",
	leftDialog = "@conversation/tatooine_rebel_trainer_1:s_1f0828c5", -- Report mission status!
	stopConversation = "false",
	options = {
		{"@conversation/tatooine_rebel_trainer_1:s_6a7a0499", "quest3_grant"}, -- (Brag about blasting even more TIE fighters)
		{"@conversation/tatooine_rebel_trainer_1:s_6d7d5f1b", "quest3_grant"}, -- All targets eliminated, ma'am!
		{"@conversation/tatooine_rebel_trainer_1:s_dcbc639a", "quest3_grant"}, -- The mission is a success, Da'la.
	}
}
eker_convo:addScreen(eker_convo_excellent_work2)

-- Grant Quest 3
eker_convo_quest3_grant = ConvoScreen:new {
	id = "quest3_grant",
	leftDialog = "@conversation/tatooine_rebel_trainer_1:s_bda1eb17", -- Your ship sensor data has been completely decoded. The Alliance supply route is entirely compromised. We need you to scout a new route for our in-system supply convoy. Are you up to it?
	stopConversation = "false",
	options = {
		{"@conversation/tatooine_rebel_trainer_1:s_c92d07b4", "quest3_brief"}, -- Sure. Why not.
		{"@conversation/tatooine_rebel_trainer_1:s_fbac0bde", "quest3_brief"}, -- (Salute) Ma'am! Yes, ma'am!
	}
}
eker_convo:addScreen(eker_convo_quest3_grant)

-- Quest 3 Brief
eker_convo_quest3_brief = ConvoScreen:new {
	id = "quest3_brief",
	leftDialog = "@conversation/tatooine_rebel_trainer_1:s_bda1eb17", -- dynamic - quest granted
	stopConversation = "true",
	options = {}
}
eker_convo:addScreen(eker_convo_quest3_brief)

-- Failed Quest 3
eker_convo_failed_quest3 = ConvoScreen:new {
	id = "failed_quest3",
	leftDialog = "@conversation/tatooine_rebel_trainer_1:s_a87c06b", -- I already know what happened. Do you have anything to say for yourself?
	stopConversation = "false",
	options = {
		{"@conversation/tatooine_rebel_trainer_1:s_190", "retry_quest3"}, -- It wasn't my fault!
		{"@conversation/tatooine_rebel_trainer_1:s_877e028c", "retry_quest3"}, -- Ma'am! I want another chance, ma'am!
		{"@conversation/tatooine_rebel_trainer_1:s_eab1caa8", "retry_quest3"}, -- I'm not in the habit of making excuses.
	}
}
eker_convo:addScreen(eker_convo_failed_quest3)

-- Retry Quest 3
eker_convo_retry_quest3 = ConvoScreen:new {
	id = "retry_quest3",
	leftDialog = "@conversation/tatooine_rebel_trainer_1:s_bda1eb17", -- dynamic
	stopConversation = "true",
	options = {}
}
eker_convo:addScreen(eker_convo_retry_quest3)

-- Failed Quest 4
eker_convo_failed_quest4 = ConvoScreen:new {
	id = "failed_quest4",
	leftDialog = "@conversation/tatooine_rebel_trainer_1:s_fcd9ce0e", -- This cannot stand, pilot! We need you to take down that Veteran TIE pilot!
	stopConversation = "false",
	options = {
		{"@conversation/tatooine_rebel_trainer_1:s_7e1ada01", "retry_quest4"}, -- Yeah, yeah...
		{"@conversation/tatooine_rebel_trainer_1:s_8ef10336", "retry_quest4"}, -- Affirmative, ma'am!
		{"@conversation/tatooine_rebel_trainer_1:s_e42b260e", "retry_quest4"}, -- I'm on my way.
	}
}
eker_convo:addScreen(eker_convo_failed_quest4)

-- Retry Quest 4
eker_convo_retry_quest4 = ConvoScreen:new {
	id = "retry_quest4",
	leftDialog = "@conversation/tatooine_rebel_trainer_1:s_fcd9ce0e", -- dynamic
	stopConversation = "true",
	options = {}
}
eker_convo:addScreen(eker_convo_retry_quest4)

-- Training Menu (dynamic options added by handler)
eker_convo_training_menu = ConvoScreen:new {
	id = "training_menu",
	leftDialog = "@conversation/tatooine_rebel_trainer_1:s_269", -- In what do I need to be trained?
	stopConversation = "false",
	options = {}
}
eker_convo:addScreen(eker_convo_training_menu)

-- Completed Tier 1 (send to next trainer - Yavin IV)
eker_convo_completed_tier1 = ConvoScreen:new {
	id = "completed_tier1",
	leftDialog = "@conversation/tatooine_rebel_trainer_1:s_63642f8", -- It appears that our time together has come to an end, pilot. Alliance HQ wants you reallocated to special operations on Yavin IV and placed under the command of Major Eker... immediately.
	stopConversation = "false",
	options = {
		{"@conversation/tatooine_rebel_trainer_1:s_abc65d0", "go_to_eker"}, -- Okay. Bye!
		{"@conversation/tatooine_rebel_trainer_1:s_f843dc6a", "go_to_eker"}, -- (Salute) Yes, ma'am!
		{"@conversation/tatooine_rebel_trainer_1:s_d8913d37", "go_to_eker"}, -- If it is my duty, Da'la.
	}
}
eker_convo:addScreen(eker_convo_completed_tier1)

-- Go to Eker
eker_convo_go_to_eker = ConvoScreen:new {
	id = "go_to_eker",
	leftDialog = "@conversation/tatooine_rebel_trainer_1:s_63642f8", -- dynamic
	stopConversation = "true",
	options = {}
}
eker_convo:addScreen(eker_convo_go_to_eker)

-- Graduated (return after completing tier 1)
eker_convo_graduated = ConvoScreen:new {
	id = "graduated",
	leftDialog = "@conversation/tatooine_rebel_trainer_1:s_2e56f341", -- You're not supposed to be here, pilot. You're assigned to Major Eker's group on the moon Yavin IV.
	stopConversation = "false",
	options = {
		{"@conversation/tatooine_rebel_trainer_1:s_b3bebc5e", "directions_to_eker"}, -- How do I get there?
	}
}
eker_convo:addScreen(eker_convo_graduated)

-- Directions to Eker
eker_convo_directions_to_eker = ConvoScreen:new {
	id = "directions_to_eker",
	leftDialog = "@conversation/tatooine_rebel_trainer_1:s_2e56f341", -- dynamic
	stopConversation = "true",
	options = {}
}
eker_convo:addScreen(eker_convo_directions_to_eker)

-- Goodbye
eker_convo_goodbye = ConvoScreen:new {
	id = "goodbye",
	leftDialog = "@conversation/tatooine_rebel_trainer_1:s_e31d65b7", -- The duty logs indicate that you are in mid-mission. We have nothing to discuss until you are finished.
	stopConversation = "true",
	options = {}
}
eker_convo:addScreen(eker_convo_goodbye)

addConversationTemplate("eker_convo", eker_convo)
