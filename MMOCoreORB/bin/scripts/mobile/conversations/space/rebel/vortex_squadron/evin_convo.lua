evin_convo = ConvoTemplate:new {
	initialScreen = "",
	templateType = "Lua",
	luaClassHandler = "evinConvoHandler",
	screens = {}
}

-- Not a Pilot (no JTL skills)
evin_convo_no_jtl = ConvoScreen:new {
	id = "no_jtl",
	leftDialog = "@conversation/naboo_rebel_trainer_1:s_eedd7284", -- Greeting, Sir. Ma'am? Pardon me. I'm terribly sorry. I cannot help you with that. *bzzt*
	stopConversation = "true",
	options = {}
}
evin_convo:addScreen(evin_convo_no_jtl)

-- Imperial Pilot
evin_convo_imperial_pilot = ConvoScreen:new {
	id = "imperial_pilot",
	leftDialog = "@conversation/naboo_rebel_trainer_1:s_85e2e26d", -- Greetings. Can I be of service?
	stopConversation = "false",
	options = {
		{"@conversation/naboo_rebel_trainer_1:s_a425f33d", "imperial_dismiss"}, -- I have no use for you.
		{"@conversation/naboo_rebel_trainer_1:s_c16bab26", "imperial_dismiss"}, -- I need answers, droid.
		{"@conversation/naboo_rebel_trainer_1:s_9f6cf52", "imperial_dismiss"}, -- (Glare in silent hatred.)
	}
}
evin_convo:addScreen(evin_convo_imperial_pilot)

-- Imperial Dismiss
evin_convo_imperial_dismiss = ConvoScreen:new {
	id = "imperial_dismiss",
	leftDialog = "@conversation/naboo_rebel_trainer_1:s_85e2e26d", -- dynamic
	stopConversation = "true",
	options = {}
}
evin_convo:addScreen(evin_convo_imperial_dismiss)

-- Neutral/Privateer Pilot
evin_convo_neutral_pilot = ConvoScreen:new {
	id = "neutral_pilot",
	leftDialog = "@conversation/naboo_rebel_trainer_1:s_968b4bae", -- Oh. Excuse me. I didn't see you there.
	stopConversation = "false",
	options = {
		{"@conversation/naboo_rebel_trainer_1:s_b26194cb", "neutral_explain"}, -- What are you doing here?
		{"@conversation/naboo_rebel_trainer_1:s_ca776e30", "neutral_explain"}, -- Who are you?
		{"@conversation/naboo_rebel_trainer_1:s_1a53f653", "neutral_explain"}, -- I am looking for pilot training.
	}
}
evin_convo:addScreen(evin_convo_neutral_pilot)

-- Neutral Explain
evin_convo_neutral_explain = ConvoScreen:new {
	id = "neutral_explain",
	leftDialog = "@conversation/naboo_rebel_trainer_1:s_968b4bae", -- dynamic
	stopConversation = "true",
	options = {}
}
evin_convo:addScreen(evin_convo_neutral_explain)

-- Not Rebel Pilot
evin_convo_not_rebel_pilot = ConvoScreen:new {
	id = "not_rebel_pilot",
	leftDialog = "@conversation/naboo_rebel_trainer_1:s_326", -- Excuse me. I cannot locate any record of you registering yourself with the Alliance. Please visit a Rebel recruiter to correct this issue.
	stopConversation = "true",
	options = {}
}
evin_convo:addScreen(evin_convo_not_rebel_pilot)

-- Non-Vortex Rebel Pilot (not on track)
evin_convo_non_vortex_pilot = ConvoScreen:new {
	id = "non_vortex_pilot",
	leftDialog = "@conversation/naboo_rebel_trainer_1:s_8c6a4b66", -- Oh. You are an Alliance pilot, but I do not recognize you. How may I be of service?
	stopConversation = "false",
	options = {
		{"@conversation/naboo_rebel_trainer_1:s_ac05bfba", "non_track_explain"}, -- Are there any missions I can fly?
	}
}
evin_convo:addScreen(evin_convo_non_vortex_pilot)

-- Non Track Explain
evin_convo_non_track_explain = ConvoScreen:new {
	id = "non_track_explain",
	leftDialog = "@conversation/naboo_rebel_trainer_1:s_8c6a4b66", -- dynamic
	stopConversation = "true",
	options = {}
}
evin_convo:addScreen(evin_convo_non_track_explain)

-- Has Active Mission
evin_convo_has_mission = ConvoScreen:new {
	id = "has_mission",
	leftDialog = "@conversation/naboo_rebel_trainer_1:s_e31d65b7", -- The duty logs indicate that you are in mid-mission. We have nothing to discuss until you are finished.
	stopConversation = "true",
	options = {}
}
evin_convo:addScreen(evin_convo_has_mission)

-- Has Very First Quest (just joined, needs help)
evin_convo_has_first_quest = ConvoScreen:new {
	id = "has_first_quest",
	leftDialog = "@conversation/naboo_rebel_trainer_1:s_1323cdc1", -- How can I be of service? I have added your first assignment to your log... and I have uploaded codes for a ship control device in your datapad. Go to the Starport and access the terminal to launch into space... unless I forgot something?
	stopConversation = "false",
	options = {
		{"@conversation/naboo_rebel_trainer_1:s_60c4f974", "quest_help"}, -- Where do I go?
		{"@conversation/naboo_rebel_trainer_1:s_85dd7d6c", "quest_help"}, -- How do I get back?
		{"@conversation/naboo_rebel_trainer_1:s_4358efe9", "quest_help"}, -- Where is my ship?
	}
}
evin_convo:addScreen(evin_convo_has_first_quest)

-- Quest Help
evin_convo_quest_help = ConvoScreen:new {
	id = "quest_help",
	leftDialog = "@conversation/naboo_rebel_trainer_1:s_1323cdc1", -- dynamic
	stopConversation = "true",
	options = {}
}
evin_convo:addScreen(evin_convo_quest_help)

-- Introduction (new pilot - no novice skill)
evin_convo_introduction = ConvoScreen:new {
	id = "introduction",
	leftDialog = "@conversation/naboo_rebel_trainer_1:s_cd448c20", -- Greetings. I am V3-FX, Alliance Pilot Relations. May I interest you in our starfighter training program?
	stopConversation = "false",
	options = {
		{"@conversation/naboo_rebel_trainer_1:s_78679b31", "join_squadron"}, -- Sounds like fun. Where do I sign?
		{"@conversation/naboo_rebel_trainer_1:s_1a0322d9", "join_squadron"}, -- I want to fly for the Alliance!
		{"@conversation/naboo_rebel_trainer_1:s_616cd1dd", "join_squadron"}, -- Yes. I am ready to train.
	}
}
evin_convo:addScreen(evin_convo_introduction)

-- Join Squadron (grants novice + ship + first quest)
evin_convo_join_squadron = ConvoScreen:new {
	id = "join_squadron",
	leftDialog = "@conversation/naboo_rebel_trainer_1:s_cd448c20", -- dynamic
	stopConversation = "true",
	options = {}
}
evin_convo:addScreen(evin_convo_join_squadron)

-- No Spaceship (needs ship granted)
evin_convo_no_ship = ConvoScreen:new {
	id = "no_ship",
	leftDialog = "@conversation/naboo_rebel_trainer_1:s_909a1feb", -- You will need a ship, in order to be a pilot. I will add the control codes to your datapad for a simple Z95. I hope that it serves you well.
	stopConversation = "true",
	options = {}
}
evin_convo:addScreen(evin_convo_no_ship)

-- Graduated to Dantooine (already sent to tier 2)
evin_convo_graduated = ConvoScreen:new {
	id = "graduated",
	leftDialog = "@conversation/naboo_rebel_trainer_1:s_b7b55289", -- Hello there! It is good to see you, although I believe you are supposed to be on planet Dantooine... correct?
	stopConversation = "false",
	options = {
		{"@conversation/naboo_rebel_trainer_1:s_741df7ed", "go_to_dantooine"}, -- Where?
		{"@conversation/naboo_rebel_trainer_1:s_2be1e8b", "go_to_dantooine"}, -- (Salute) Requesting more info, sir!
		{"@conversation/naboo_rebel_trainer_1:s_b3bebc5e", "go_to_dantooine"}, -- How do I get there?
	}
}
evin_convo:addScreen(evin_convo_graduated)

-- Go to Dantooine
evin_convo_go_to_dantooine = ConvoScreen:new {
	id = "go_to_dantooine",
	leftDialog = "@conversation/naboo_rebel_trainer_1:s_b7b55289", -- dynamic
	stopConversation = "true",
	options = {}
}
evin_convo:addScreen(evin_convo_go_to_dantooine)

-- All Tier 1 Skills Complete (graduation)
evin_convo_all_tier1_complete = ConvoScreen:new {
	id = "all_tier1_complete",
	leftDialog = "@conversation/naboo_rebel_trainer_1:s_2e5c9032", -- Congratulations, pilot! You have successfully completed the first tier of the Alliance starfighter training program. Your next assignment will take you to planet Dantooine and place you under the guidance of Brother Vrovel... leader of the Vortex organization.
	stopConversation = "false",
	options = {
		{"@conversation/naboo_rebel_trainer_1:s_f75b511f", "graduation_explain"}, -- You got it, metal head!
		{"@conversation/naboo_rebel_trainer_1:s_4efbdbfa", "graduation_explain"}, -- What is 'Vortex?'
		{"@conversation/naboo_rebel_trainer_1:s_b89c30f1", "graduation_explain"}, -- Who is Brother Vrovel?
		{"@conversation/naboo_rebel_trainer_1:s_1df40ac6", "goodbye"}, -- Goodbye, V3.
		{"@conversation/naboo_rebel_trainer_1:s_8334632", "graduation_explain"}, -- Where do I find this Brother Vrovel?
	}
}
evin_convo:addScreen(evin_convo_all_tier1_complete)

-- Graduation Explain
evin_convo_graduation_explain = ConvoScreen:new {
	id = "graduation_explain",
	leftDialog = "@conversation/naboo_rebel_trainer_1:s_2e5c9032", -- dynamic
	stopConversation = "true",
	options = {}
}
evin_convo:addScreen(evin_convo_graduation_explain)

-- Training Menu (dynamic options added by handler)
evin_convo_training_menu = ConvoScreen:new {
	id = "training_menu",
	leftDialog = "@conversation/naboo_rebel_trainer_1:s_cd448c20", -- dynamic
	stopConversation = "false",
	options = {}
}
evin_convo:addScreen(evin_convo_training_menu)

-- Goodbye
evin_convo_goodbye = ConvoScreen:new {
	id = "goodbye",
	leftDialog = "@conversation/naboo_rebel_trainer_1:s_eedd7284", -- dynamic
	stopConversation = "true",
	options = {}
}
evin_convo:addScreen(evin_convo_goodbye)

addConversationTemplate("evin_convo", evin_convo)
