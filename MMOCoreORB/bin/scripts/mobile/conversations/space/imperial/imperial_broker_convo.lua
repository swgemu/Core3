imperial_broker_convo_template = ConvoTemplate:new {
	initialScreen = "",
	templateType = "Lua",
	luaClassHandler = "imperialBrokerConvoHandler",
	screens = {}
}

--[[

	Greetings for non-affiliated players

]]

no_jtl = ConvoScreen:new {
	id = "no_jtl",
	leftDialog = "@conversation/imperial_broker:s_be46803", -- I don't think I can help you, citizen. You don't look like much of a pilot.
	stopConversation = "true",
	options = {}
}
imperial_broker_convo_template:addScreen(no_jtl);

--[[

	Player is Imperial Pilot - Handle retirement

]]

hello_imperial_pilot = ConvoScreen:new {
	id = "hello_imperial_pilot",
	leftDialog = "@conversation/imperial_broker:s_e60ef8f6", -- Hello, pilot. I hope that your service in the Imperial Navy treats you well. How may I be of assistance?
	stopConversation = "false",
	options = {
		{"@conversation/imperial_broker:s_8812be10", "request_retire"}, -- I would like to retire from the Imperial Navy.
		{"@conversation/imperial_broker:s_169df3bb", "never_mind_pilot"}, -- Never mind.
	}
}
imperial_broker_convo_template:addScreen(hello_imperial_pilot);

request_retire = ConvoScreen:new {
	id = "request_retire",
	leftDialog = "@conversation/imperial_broker:s_458bda80", -- Did I hear you correctly? You want to retire? You are aware that you would lose all your pilot skills, and your mission records would be deleted. If you sign up again, you will start as a new recruit. Are you sure this is what you want to do?
	stopConversation = "false",
	options = {
		{"@conversation/imperial_broker:s_658b5a75", "want_retirement"}, -- Yes, I want to retire.
		{"@conversation/imperial_broker:s_f220efed", "right_choice"}, -- I changed my mind. I will stay.
	}
}
imperial_broker_convo_template:addScreen(request_retire);

want_retirement = ConvoScreen:new {
	id = "want_retirement",
	leftDialog = "@conversation/imperial_broker:s_fbeabc76", -- If that's what you want, I'll start getting your discharge papers together. If you want to change your mind, now is the time.
	stopConversation = "false",
	options = {
		{"@conversation/imperial_broker:s_f72f24be", "confirm_retirement"}, -- I want to retire.
		{"@conversation/imperial_broker:s_f220efed", "right_choice"}, -- I changed my mind. I will stay.
	}
}
imperial_broker_convo_template:addScreen(want_retirement);

--[[

	Player is a rebel

]]

rebel_player = ConvoScreen:new {
	id = "rebel_player",
	leftDialog = "@conversation/imperial_broker:s_6a1562ad", -- What do you want?
	stopConversation = "false",
	options = {
		{"@conversation/imperial_broker:s_840482e7", "stop_bothering"}, -- Nothing
	}
}
imperial_broker_convo_template:addScreen(rebel_player);

--[[

	Player is not a pilot or rebel

]]

greet_male_imp = ConvoScreen:new {
	id = "greet_male_imp",
	leftDialog = "@conversation/imperial_broker:s_2eee3e2e", -- Yes, sir!  How may I be of assistance?
	stopConversation = "false",
	options = {
		{"@conversation/imperial_broker:s_4b0c16d2", "recruiting_male"}, -- Are you recruiting Imperial Pilots?
		{"@conversation/imperial_broker:s_169df3bb", "never_mind"}, -- Never mind.
	}
}
imperial_broker_convo_template:addScreen(greet_male_imp);

recruiting_male = ConvoScreen:new {
	id = "recruiting_male",
	leftDialog = "@conversation/imperial_broker:s_8c387e5c", -- Sir! Yes, sir!  Are you here to sign-up?
	stopConversation = "false",
	options = {
		{"@conversation/imperial_broker:s_8ed93c34", "no_just_checking_male"}, -- No, just checking.
		{"@conversation/imperial_broker:s_b0ea6e8c", "yes_recruiting_male"}, -- Yes.  What do I need to do?
	}
}
imperial_broker_convo_template:addScreen(recruiting_male);

no_just_checking_male = ConvoScreen:new {
	id = "no_just_checking_male",
	leftDialog = "@conversation/imperial_broker:s_8755e6eb", -- Very well, sir.  Please come see me if you change your mind.  The Empire could use more soldiers of your caliber in space!
	stopConversation = "true",
	options = {}
}
imperial_broker_convo_template:addScreen(no_just_checking_male);

yes_recruiting_male = ConvoScreen:new {
	id = "yes_recruiting_male",
	leftDialog = "@conversation/imperial_broker:s_4577214d", -- I'm authorized to send you to one of three assignments, sir.  You can choose Storm Squadron in the Tatooine system, Black Epsilon in the Corellia system, or the Imperial Inquisition in the Naboo system.
	stopConversation = "false",
	options = {
		{"@conversation/imperial_broker:s_1b2086de", "black_epsilon_male"}, -- Black Epsilon?
		{"@conversation/imperial_broker:s_4cafd748", "storm_squadron"}, -- Storm Squadron?
		{"@conversation/imperial_broker:s_23ef3e33", "imperial_inquisition_male"}, -- Imperial Inquisition?
	}
}
imperial_broker_convo_template:addScreen(yes_recruiting_male);

-- Female

greet_female_imp = ConvoScreen:new {
	id = "greet_female_imp",
	leftDialog = "@conversation/imperial_broker:s_fda95628", -- Yes, ma'am!  How may I be of assistance?
	stopConversation = "false",
	options = {
		{"@conversation/imperial_broker:s_4b0c16d2", "recruiting_female"}, -- Are you recruiting Imperial Pilots?
		{"@conversation/imperial_broker:s_169df3bb", "never_mind"}, -- Never mind.
	}
}
imperial_broker_convo_template:addScreen(greet_female_imp);

recruiting_female = ConvoScreen:new {
	id = "recruiting_female",
	leftDialog = "@conversation/imperial_broker:s_d78c7ec0", -- Ma'am!  Yes, ma'am!  Are you here to sign-up?
	stopConversation = "false",
	options = {
		{"@conversation/imperial_broker:s_8ed93c34", "no_just_checking_female"}, -- No, just checking.
		{"@conversation/imperial_broker:s_b0ea6e8c", "yes_recruiting_female"}, -- Yes.  What do I need to do?
	}
}
imperial_broker_convo_template:addScreen(recruiting_female);

yes_recruiting_female = ConvoScreen:new {
	id = "yes_recruiting_female",
	leftDialog = "@conversation/imperial_broker:s_b8884586", -- I'm authorized to send you to one of three assignments, ma'am.  You can choose Storm Squadron in the Tatooine system, Black Epsilon in the Corellia system, or the Imperial Inquisition in the Naboo system.
	stopConversation = "false",
	options = {
		{"@conversation/imperial_broker:s_1b2086de", "black_epsilon_female"}, -- Black Epsilon?
		{"@conversation/imperial_broker:s_4cafd748", "storm_squadron"}, -- Storm Squadron?
		{"@conversation/imperial_broker:s_23ef3e33", "imperial_inquisition_female"}, -- Imperial Inquisition?
	}
}
imperial_broker_convo_template:addScreen(yes_recruiting_female);

-- Greet Neutral

greet_neutral = ConvoScreen:new {
	id = "greet_neutral",
	leftDialog = "@conversation/imperial_broker:s_59be173", -- Can I help you?
	stopConversation = "false",
	options = {
		{"@conversation/imperial_broker:s_4b0c16d2", "recruiting_neutral"}, -- Are you recruiting Imperial Pilots?
		{"@conversation/imperial_broker:s_445a2be4", "no_never_mind"}, -- No. Never mind.
	}
}
imperial_broker_convo_template:addScreen(greet_neutral);

recruiting_neutral = ConvoScreen:new {
	id = "recruiting_neutral",
	leftDialog = "@conversation/imperial_broker:s_14270b3", -- Are you here to sign-up?
	stopConversation = "false",
	options = {
		{"@conversation/imperial_broker:s_8ed93c34", "no_just_checking"}, -- No, just checking.
		{"@conversation/imperial_broker:s_b0ea6e8c", "yes_neutral_recruit"}, -- Yes.  What do I need to do?
	}
}
imperial_broker_convo_template:addScreen(recruiting_neutral);

no_just_checking = ConvoScreen:new {
	id = "no_just_checking",
	leftDialog = "@conversation/imperial_broker:s_2a4c66e4", -- Come see me if you change your mind.  Someone has to stand up to the Rebel Alliance and maintain order in the galaxy.
	stopConversation = "true",
	options = {}
}
imperial_broker_convo_template:addScreen(no_just_checking);

yes_neutral_recruit = ConvoScreen:new {
	id = "yes_neutral_recruit",
	leftDialog = "@conversation/imperial_broker:s_106caa1d", -- The units with vacancies currently are the Storm Squadron in the Tatooine system, Black Epsilon in the Corellia system, or the Imperial Inquisition in the Naboo system.
	stopConversation = "false",
	options = {
		{"@conversation/imperial_broker:s_1b2086de", "black_epsilon_neutral"}, -- Black Epsilon?
		{"@conversation/imperial_broker:s_4cafd748", "storm_squadron_neutral"}, -- Storm Squadron?
		{"@conversation/imperial_broker:s_23ef3e33", "imperial_inquisition_neutral"}, -- Imperial Inquisition?
	}
}
imperial_broker_convo_template:addScreen(yes_neutral_recruit);

-- Already conversed male

something_else_male = ConvoScreen:new {
	id = "something_else_male",
	leftDialog = "@conversation/imperial_broker:s_8d91ee22", -- Was there something else, sir?
	stopConversation = "false",
	options = {
		{"@conversation/imperial_broker:s_1b2086de", "black_epsilon_male"}, -- Black Epsilon?
		{"@conversation/imperial_broker:s_4cafd748", "storm_squadron"}, -- Storm Squadron?
		{"@conversation/imperial_broker:s_23ef3e33", "imperial_inquisition_male"}, -- Imperial Inquisition?
	}
}
imperial_broker_convo_template:addScreen(something_else_male);

-- Already conversed female

something_else_female = ConvoScreen:new {
	id = "something_else_female",
	leftDialog = "@conversation/imperial_broker:s_ac926b4b", -- Was there something else, ma'am?
	stopConversation = "false",
	options = {
		{"@conversation/imperial_broker:s_1b2086de", "black_epsilon_female"}, -- Black Epsilon?
		{"@conversation/imperial_broker:s_4cafd748", "storm_squadron"}, -- Storm Squadron?
		{"@conversation/imperial_broker:s_23ef3e33", "imperial_inquisition_female"}, -- Imperial Inquisition?
	}
}
imperial_broker_convo_template:addScreen(something_else_female);

--[[

	Squadrons

]]


-- Black Epsilon

-- Male

black_epsilon_male = ConvoScreen:new {
	id = "black_epsilon_male",
	leftDialog = "@conversation/imperial_broker:s_772c81dd", -- Yes, sir.  Black Epsilon is stationed at the Imperial Base on Talus, as Corellia itself is officially neutral... for now.  There are reports of considerable Rebel activity in the area, as you can imagine.  They could really use more pilots there, sir.
	stopConversation = "false",
	options = {
		{"@conversation/imperial_broker:s_70f18874", "not_interested_be_male"}, -- I'm not interested in that.
		{"@conversation/imperial_broker:s_df2917b1", "more_black_epsilon_male"}, -- Tell me more
	}
}
imperial_broker_convo_template:addScreen(black_epsilon_male);

more_black_epsilon_male = ConvoScreen:new {
	id = "more_black_epsilon_male",
	leftDialog = "@conversation/imperial_broker:s_cc37bca4", -- Yes, sir.  I can't release any specific details about their current engagements, but I will add the location of their own recruiter to your datapad.  If you'll speak with this officer in the Imperial Base on Talus, he will get you squared away.
	stopConversation = "true",
	options = {}
}
imperial_broker_convo_template:addScreen(more_black_epsilon_male);

not_interested_be_male = ConvoScreen:new {
	id = "not_interested_be_male",
	leftDialog = "@conversation/imperial_broker:s_a7d90105", -- Very well, sir.  What about Storm Squadron or the Imperial Inquisition?
	stopConversation = "false",
	options = {
		{"@conversation/imperial_broker:s_1b2086de", "black_epsilon_male"}, -- Black Epsilon?
		{"@conversation/imperial_broker:s_4cafd748", "storm_squadron"}, -- Storm Squadron?
		{"@conversation/imperial_broker:s_23ef3e33", "imperial_inquisition_male"}, -- Imperial Inquisition?
	}
}
imperial_broker_convo_template:addScreen(not_interested_be_male);

-- Female

black_epsilon_female = ConvoScreen:new {
	id = "black_epsilon_female",
	leftDialog = "@conversation/imperial_broker:s_c2c89e35", -- Yes, ma'am.  Black Epsilon is stationed at the Imperial Base on Talus, as Corellia itself is officially neutral... for now.  There are reports of considerable Rebel activity in the area, as you can imagine.  They could really use more pilots there, ma'am.
	stopConversation = "false",
	options = {
		{"@conversation/imperial_broker:s_70f18874", "not_interested_be_female"}, -- I'm not interested in that.
		{"@conversation/imperial_broker:s_df2917b1", "more_black_epsilon_female"}, -- Tell me more
	}
}
imperial_broker_convo_template:addScreen(black_epsilon_female);

more_black_epsilon_female = ConvoScreen:new {
	id = "more_black_epsilon_female",
	leftDialog = "@conversation/imperial_broker:s_b945b46a", -- Yes, ma'am.  I can't release any specific details about their current engagements, but I will add the location of their own recruiter to your datapad.  If you'll speak with this officer in the Imperial Base on Talus, he will get you squared away.
	stopConversation = "true",
	options = {}
}
imperial_broker_convo_template:addScreen(more_black_epsilon_female);

not_interested_be_female = ConvoScreen:new {
	id = "not_interested_be_female",
	leftDialog = "@conversation/imperial_broker:s_407fb5e3", -- Very well, ma'am.  What about Storm Squadron or the Imperial Inquisition?
	stopConversation = "false",
	options = {
		{"@conversation/imperial_broker:s_1b2086de", "black_epsilon_female"}, -- Black Epsilon?
		{"@conversation/imperial_broker:s_4cafd748", "storm_squadron"}, -- Storm Squadron?
		{"@conversation/imperial_broker:s_23ef3e33", "imperial_inquisition_female"}, -- Imperial Inquisition?
	}
}
imperial_broker_convo_template:addScreen(not_interested_be_female);

-- Neutral

black_epsilon_neutral = ConvoScreen:new {
	id = "black_epsilon_neutral",
	leftDialog = "@conversation/imperial_broker:s_86cb9899", -- Yes.  Black Epsilon is stationed at the Imperial Base on Talus, as Corellia itself is officially neutral... for now.  There are reports of considerable Rebel activity in the area.
	stopConversation = "false",
	options = {
		{"@conversation/imperial_broker:s_70f18874", "epsilon_neutral_no_interest"}, -- I'm not interested in that.
		{"@conversation/imperial_broker:s_df2917b1", "more_black_epsilon_neutral"}, -- Tell me more
	}
}
imperial_broker_convo_template:addScreen(black_epsilon_neutral);

more_black_epsilon_neutral = ConvoScreen:new {
	id = "more_black_epsilon_neutral",
	leftDialog = "@conversation/imperial_broker:s_3d734747", -- I won't release any specific details about their current engagements, but I will add the location of their recruiting officer to your datapad.  You can find him in the Imperial Base on Talus, in the Corellia system.
	stopConversation = "true",
	options = {}
}
imperial_broker_convo_template:addScreen(more_black_epsilon_neutral);

epsilon_neutral_no_interest = ConvoScreen:new {
	id = "epsilon_neutral_no_interest",
	leftDialog = "@conversation/imperial_broker:s_9f862c74", -- What about Storm Squadron or the Imperial Inquisition?
	stopConversation = "false",
	options = {
		{"@conversation/imperial_broker:s_1b2086de", "black_epsilon_neutral"}, -- Black Epsilon?
		{"@conversation/imperial_broker:s_4cafd748", "storm_squadron_neutral"}, -- Storm Squadron?
		{"@conversation/imperial_broker:s_23ef3e33", "imperial_inquisition_neutral"}, -- Imperial Inquisition?
	}
}
imperial_broker_convo_template:addScreen(epsilon_neutral_no_interest);


-- Storm Squadron

storm_squadron = ConvoScreen:new {
	id = "storm_squadron",
	leftDialog = "@conversation/imperial_broker:s_e0db13e8", -- Storm Squadron is one of the Empire's finest military units, in space or otherwise.  They're the very model of the sort of hard-core, dedicated, soldiers that secure the Empire throughout the galaxy.
	stopConversation = "false",
	options = {}
}
imperial_broker_convo_template:addScreen(storm_squadron);

-- Male

not_interested_storm_male = ConvoScreen:new {
	id = "not_interested_storm_male",
	leftDialog = "@conversation/imperial_broker:s_a8b71650", -- Yes, sir.  What about Black Epsilon or the Imperial Inquisition?
	stopConversation = "false",
	options = {
		{"@conversation/imperial_broker:s_1b2086de", "black_epsilon_male"}, -- Black Epsilon?
		{"@conversation/imperial_broker:s_4cafd748", "storm_squadron"}, -- Storm Squadron?
		{"@conversation/imperial_broker:s_23ef3e33", "imperial_inquisition_male"}, -- Imperial Inquisition?
	}
}
imperial_broker_convo_template:addScreen(not_interested_storm_male);

storm_more_male = ConvoScreen:new {
	id = "storm_more_male",
	leftDialog = "@conversation/imperial_broker:s_5817eef2", -- Yes, sir.  I can't release any specific details about their current engagements, but I will add the location of the Storm Squadron commander to your datapad.  He'll be glad to have a soldier of your standing.  You can find him in the Bestine Pilot's Club next to the capitol building on Tatooine.
	stopConversation = "true",
	options = {}
}
imperial_broker_convo_template:addScreen(storm_more_male);

-- Female

not_interested_storm_female = ConvoScreen:new {
	id = "not_interested_storm_female",
	leftDialog = "@conversation/imperial_broker:s_42693321", -- I see.  What about Black Epsilon or the Imperial Inquisition?
	stopConversation = "false",
	options = {
		{"@conversation/imperial_broker:s_1b2086de", "black_epsilon_female"}, -- Black Epsilon?
		{"@conversation/imperial_broker:s_4cafd748", "storm_squadron"}, -- Storm Squadron?
		{"@conversation/imperial_broker:s_23ef3e33", "imperial_inquisition_female"}, -- Imperial Inquisition?
	}
}
imperial_broker_convo_template:addScreen(not_interested_storm_female);

storm_more_female = ConvoScreen:new {
	id = "storm_more_female",
	leftDialog = "@conversation/imperial_broker:s_cd41504a", -- Yes, ma'am.  I can't release any specific details about their current engagements, but I will add this location to your datapad.  Talk to the trainer in the Bestine Pilot's Club, near the capitol building on Tatooine.
	stopConversation = "true",
	options = {}
}
imperial_broker_convo_template:addScreen(storm_more_female);

-- Neutral

storm_squadron_neutral = ConvoScreen:new {
	id = "storm_squadron_neutral",
	leftDialog = "@conversation/imperial_broker:s_e0db13e8", -- Storm Squadron is one of the Empire's finest military units, in space or otherwise.  They're the very model of the sort of hard-core, dedicated, soldiers that secure the Empire throughout the galaxy.
	stopConversation = "false",
	options = {
		{"@conversation/imperial_broker:s_70f18874", "storm_squadron_neutral_no_int"}, -- I'm not interested in that.
		{"@conversation/imperial_broker:s_df2917b1", "more_storm_neutral"}, -- Tell me more
	}
}
imperial_broker_convo_template:addScreen(storm_squadron_neutral);

storm_squadron_neutral_no_int = ConvoScreen:new {
	id = "storm_squadron_neutral_no_int",
	leftDialog = "@conversation/imperial_broker:s_727cf8b6", -- What about Black Epsilon or the Imperial Inquisition?
	stopConversation = "false",
	options = {
		{"@conversation/imperial_broker:s_1b2086de", "black_epsilon_neutral"}, -- Black Epsilon?
		{"@conversation/imperial_broker:s_4cafd748", "storm_squadron_neutral"}, -- Storm Squadron?
		{"@conversation/imperial_broker:s_23ef3e33", "imperial_inquisition_neutral"}, -- Imperial Inquisition?
	}
}
imperial_broker_convo_template:addScreen(storm_squadron_neutral_no_int);

more_storm_neutral = ConvoScreen:new {
	id = "more_storm_neutral",
	leftDialog = "@conversation/imperial_broker:s_7287c2b7", -- I won't release any specific details about their current engagements, but I will add the location of the Storm Squadron pilot trainer to your datapad.  You'll find him in the Bestine Pilot's club on Tatooine, next to the capitol building.
	stopConversation = "true",
	options = {}
}
imperial_broker_convo_template:addScreen(more_storm_neutral);


-- Imperial Inquisition

--  Male
imperial_inquisition_male = ConvoScreen:new {
	id = "imperial_inquisition_male",
	leftDialog = "@conversation/imperial_broker:s_929272e8", -- Imperial Inquisition is a special unit located in the Naboo system, sir.  They tend to deal in highly classified missions, so I'm afraid there's not a lot I'm authorized to tell you.
	stopConversation = "false",
	options = {
		{"@conversation/imperial_broker:s_70f18874", "not_interested_inquisition_male"}, -- I'm not interested in that.
		{"@conversation/imperial_broker:s_13a23fbc", "what_inquisition_male"}, -- Tell me what you can
	}
}
imperial_broker_convo_template:addScreen(imperial_inquisition_male);

not_interested_inquisition_male = ConvoScreen:new {
	id = "not_interested_inquisition_male",
	leftDialog = "@conversation/imperial_broker:s_ed23ffff", -- Are you interested in either Black Epsilon or the Storm Squadron, sir?
	stopConversation = "false",
	options = {
		{"@conversation/imperial_broker:s_1b2086de", "black_epsilon_male"}, -- Black Epsilon?
		{"@conversation/imperial_broker:s_4cafd748", "storm_squadron"}, -- Storm Squadron?
		{"@conversation/imperial_broker:s_23ef3e33", "imperial_inquisition_male"}, -- Imperial Inquisition?
	}
}
imperial_broker_convo_template:addScreen(not_interested_inquisition_male);

what_inquisition_male = ConvoScreen:new {
	id = "what_inquisition_male",
	leftDialog = "@conversation/imperial_broker:s_f05830e3", -- There's not much more I can say, sir, but I will add the location to your datapad.  Talk to the Imperial Pilot trainer in Kaadara.  You'll find the association hall in the main plaza.
	stopConversation = "true",
	options = {}
}
imperial_broker_convo_template:addScreen(what_inquisition_male);

-- Female

imperial_inquisition_female = ConvoScreen:new {
	id = "imperial_inquisition_female",
	leftDialog = "@conversation/imperial_broker:s_b89f31b", -- Imperial Inquisition is a special unit located in the Naboo system, ma'am.  They tend to deal in highly classified missions, so I'm afraid there's not a lot I'm authorized to tell you.
	stopConversation = "false",
	options = {
		{"@conversation/imperial_broker:s_70f18874", "not_interested_inquisition_female"}, -- I'm not interested in that.
		{"@conversation/imperial_broker:s_13a23fbc", "what_inquisition_female"}, -- Tell me what you can
	}
}
imperial_broker_convo_template:addScreen(imperial_inquisition_female);

not_interested_inquisition_female = ConvoScreen:new {
	id = "not_interested_inquisition_female",
	leftDialog = "@conversation/imperial_broker:s_d28bda49", -- Would you be interested in either Black Epsilon or the Storm Squadron, ma'am?
	stopConversation = "false",
	options = {
		{"@conversation/imperial_broker:s_1b2086de", "black_epsilon_female"}, -- Black Epsilon?
		{"@conversation/imperial_broker:s_4cafd748", "storm_squadron"}, -- Storm Squadron?
		{"@conversation/imperial_broker:s_23ef3e33", "imperial_inquisition_female"}, -- Imperial Inquisition?
	}
}
imperial_broker_convo_template:addScreen(not_interested_inquisition_female);

what_inquisition_female = ConvoScreen:new {
	id = "what_inquisition_female",
	leftDialog = "@conversation/imperial_broker:s_8ac37a1f", -- There's not much more I can say, ma'am, but I will add this location to your datapad.  Talk to the Pilot Trainer in the association hall on Kaadara, near the main plaza.
	stopConversation = "true",
	options = {}
}
imperial_broker_convo_template:addScreen(what_inquisition_female);

-- Neutral

imperial_inquisition_neutral = ConvoScreen:new {
	id = "imperial_inquisition_neutral",
	leftDialog = "@conversation/imperial_broker:s_3c9c6441", -- Imperial Inquisition is a special unit located in the Naboo system.  Their mission is highly classified.
	stopConversation = "false",
	options = {
		{"@conversation/imperial_broker:s_70f18874", "inquisition_neutral_no_int"}, -- I'm not interested in that.
		{"@conversation/imperial_broker:s_13a23fbc", "more_inquisition_neutral"}, -- Tell me what you can
	}
}
imperial_broker_convo_template:addScreen(imperial_inquisition_neutral);

inquisition_neutral_no_int = ConvoScreen:new {
	id = "inquisition_neutral_no_int",
	leftDialog = "@conversation/imperial_broker:s_ed23ffff", -- Are you interested in either Black Epsilon or the Storm Squadron, sir?
	stopConversation = "false",
	options = {
		{"@conversation/imperial_broker:s_1b2086de", "black_epsilon_neutral"}, -- Black Epsilon?
		{"@conversation/imperial_broker:s_4cafd748", "storm_squadron_neutral"}, -- Storm Squadron?
		{"@conversation/imperial_broker:s_23ef3e33", "imperial_inquisition_neutral"}, -- Imperial Inquisition?
	}
}
imperial_broker_convo_template:addScreen(inquisition_neutral_no_int);

more_inquisition_neutral = ConvoScreen:new {
	id = "more_inquisition_neutral",
	leftDialog = "@conversation/imperial_broker:s_2fe6ab5f", -- Highly.  Classified.  Right?  I will add the location of the unit's pilot trainer to your datapad.  You may speak to him in the main plaza association hall in Kaadara, on Naboo.
	stopConversation = "true",
	options = {}
}
imperial_broker_convo_template:addScreen(more_inquisition_neutral);

--[[

	Conversation Ending Responses

]]

neutral_wookiee = ConvoScreen:new {
	id = "neutral_wookiee",
	leftDialog = "@conversation/imperial_broker:s_6e2d55ee", -- HAHAHAHA!
	stopConversation = "true",
	options = {}
}
imperial_broker_convo_template:addScreen(neutral_wookiee);

neutral_female = ConvoScreen:new {
	id = "neutral_female",
	leftDialog = "@conversation/imperial_broker:s_fb390611", -- Do you need directions or something, dear?  The bazaar terminals are near the starport.
	stopConversation = "true",
	options = {}
}
imperial_broker_convo_template:addScreen(neutral_female);

get_lost_ = ConvoScreen:new {
	id = "get_lost_",
	leftDialog = "@conversation/imperial_broker:s_b845eeb6", -- Get lost!
	stopConversation = "true",
	options = {}
}
imperial_broker_convo_template:addScreen(get_lost_);

no_business = ConvoScreen:new {
	id = "no_business",
	leftDialog = "@conversation/imperial_broker:s_e2dae58f", -- You have no business with me. Be on your way.
	stopConversation = "true",
	options = {}
}
imperial_broker_convo_template:addScreen(no_business);

never_mind_pilot = ConvoScreen:new {
	id = "never_mind_pilot",
	leftDialog = "@conversation/imperial_broker:s_6441a2a6", -- As you wish.
	stopConversation = "true",
	options = {}
}
imperial_broker_convo_template:addScreen(never_mind_pilot);

never_mind = ConvoScreen:new {
	id = "never_mind",
	leftDialog = "@conversation/imperial_broker:s_f5f50ae3", -- Of course.  My mistake.
	stopConversation = "true",
	options = {}
}
imperial_broker_convo_template:addScreen(never_mind);

right_choice = ConvoScreen:new {
	id = "right_choice",
	leftDialog = "@conversation/imperial_broker:s_e8ccc35c", -- You've made the right choice, pilot. Dismissed.
	stopConversation = "true",
	options = {}
}
imperial_broker_convo_template:addScreen(right_choice);

confirm_retirement = ConvoScreen:new {
	id = "confirm_retirement",
	leftDialog = "@conversation/imperial_broker:s_ccdbfea7", -- Very well. You are now discharged from the Imperial Navy. I must say that I am disappointed. I expected better from you.
	stopConversation = "true",
	options = {}
}
imperial_broker_convo_template:addScreen(confirm_retirement);

no_just_checking_female = ConvoScreen:new {
	id = "no_just_checking_female",
	leftDialog = "@conversation/imperial_broker:s_83a7ae89", -- Very well, ma'am.  Please come see me if you change your mind.  The Empire could use more soldiers of your caliber in space!
	stopConversation = "true",
	options = {}
}
imperial_broker_convo_template:addScreen(no_just_checking_female);

stop_bothering = ConvoScreen:new {
	id = "stop_bothering",
	leftDialog = "@conversation/imperial_broker:s_d1c489c0", -- In that case, please stop bothering me.  I am very busy.
	stopConversation = "true",
	options = {}
}
imperial_broker_convo_template:addScreen(stop_bothering);

-- Wookiee wants to be pilot
pilot_wookiee = ConvoScreen:new {
	id = "pilot_wookiee",
	leftDialog = "@conversation/imperial_broker:s_b19ac578", -- HAHAHAHAHA!  Imagine that!  A big fur-ball like you flying a ship for the Empire!  Oh that is RICH!
	stopConversation = "true",
	options = {}
}
imperial_broker_convo_template:addScreen(pilot_wookiee);

-- Rebel male wants to be pilot
pilot_rebel = ConvoScreen:new {
	id = "pilot_rebel",
	leftDialog = "@conversation/imperial_broker:s_3bbddad5", -- Sir, I don't intend any disrespect, but the Imperial Pilots are the finest in the Galaxy.  You don't look like the sort of person who could last one week in the cadet academy, let alone pilot any sort of Imperial craft.  Now I think you should leave.  I am very busy.
	stopConversation = "true",
	options = {}
}
imperial_broker_convo_template:addScreen(pilot_rebel);

-- Rebel female wants to be pilot
pilot_female = ConvoScreen:new {
	id = "pilot_female",
	leftDialog = "@conversation/imperial_broker:s_99e09eaf", -- Ma'am, you wouldn't last one nano-second as an Imperial pilot.  It's a strenuous, demanding profession that requires the utmost dedication.  Not to mention the fact that females are notoriously bad pilots!  Now if you will excuse me, good day!
	stopConversation = "true",
	options = {}
}
imperial_broker_convo_template:addScreen(pilot_female);

no_never_mind = ConvoScreen:new {
	id = "no_never_mind",
	leftDialog = "@conversation/imperial_broker:s_895d093", -- Ok.
	stopConversation = "true",
	options = {}
}
imperial_broker_convo_template:addScreen(no_never_mind);

addConversationTemplate("imperial_broker_convo_template", imperial_broker_convo_template);
