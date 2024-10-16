imperial_broker_convo_template = ConvoTemplate:new {
	initialScreen = "",
	templateType = "Lua",
	luaClassHandler = "imperialBrokerConvoHandler",
	screens = {}
}

i_dont_think = ConvoScreen:new {
	id = "i_dont_think",
	leftDialog = "@conversation/imperial_broker:s_be46803", -- I don't think I can help you, citizen. You don't look like much of a pilot.
	stopConversation = "true",
	options = {
	}
}
imperial_broker_convo_template:addScreen(i_dont_think);

hello_pilot_i = ConvoScreen:new {
	id = "hello_pilot_i",
	leftDialog = "@conversation/imperial_broker:s_e60ef8f6", -- Hello, pilot. I hope that your service in the Imperial Navy treats you well. How may I be of assistance?
	stopConversation = "false",
	options = {
		{"@conversation/imperial_broker:s_8812be10", "i_would_like"}, -- I would like to retire from the Imperial Navy.
		{"@conversation/imperial_broker:s_169df3bb", "never_mind"}, -- Never mind.
	}
}
imperial_broker_convo_template:addScreen(hello_pilot_i);

hahahaha__ = ConvoScreen:new {
	id = "hahahaha__",
	leftDialog = "@conversation/imperial_broker:s_6e2d55ee", -- HAHAHAHA!
	stopConversation = "true",
	options = {
	}
}
imperial_broker_convo_template:addScreen(hahahaha__);

do_you_need = ConvoScreen:new {
	id = "do_you_need",
	leftDialog = "@conversation/imperial_broker:s_fb390611", -- Do you need directions or something, dear?  The bazaar terminals are near the starport.
	stopConversation = "true",
	options = {
	}
}
imperial_broker_convo_template:addScreen(do_you_need);

get_lost_ = ConvoScreen:new {
	id = "get_lost_",
	leftDialog = "@conversation/imperial_broker:s_b845eeb6", -- Get lost!
	stopConversation = "true",
	options = {
	}
}
imperial_broker_convo_template:addScreen(get_lost_);

was_there_something = ConvoScreen:new {
	id = "was_there_something",
	leftDialog = "@conversation/imperial_broker:s_8d91ee22", -- Was there something else, sir?
	stopConversation = "false",
	options = {
		{"@conversation/imperial_broker:s_1b2086de", "black_epsilon_65"}, -- Black Epsilon?
		{"@conversation/imperial_broker:s_4cafd748", "storm_squadron_66"}, -- Storm Squadron?
		{"@conversation/imperial_broker:s_23ef3e33", "imperial_inquisition_67"}, -- Imperial Inquisition?
	}
}
imperial_broker_convo_template:addScreen(was_there_something);

was_there_something_1 = ConvoScreen:new {
	id = "was_there_something_1",
	leftDialog = "@conversation/imperial_broker:s_ac926b4b", -- Was there something else, ma'am?
	stopConversation = "false",
	options = {
		{"@conversation/imperial_broker:s_66", "black_epsilon_41"}, -- Black Epsilon?
		{"@conversation/imperial_broker:s_75", "storm_squadron_42"}, -- Storm Squadron?
		{"@conversation/imperial_broker:s_85", "imperial_inquisition_43"}, -- Imperial Inquisition?
	}
}
imperial_broker_convo_template:addScreen(was_there_something_1);

you_have_no = ConvoScreen:new {
	id = "you_have_no",
	leftDialog = "@conversation/imperial_broker:s_e2dae58f", -- You have no business with me. Be on your way.
	stopConversation = "true",
	options = {
	}
}
imperial_broker_convo_template:addScreen(you_have_no);

yes_sir_ = ConvoScreen:new {
	id = "yes_sir_",
	leftDialog = "@conversation/imperial_broker:s_2eee3e2e", -- Yes, sir!  How may I be of assistance?
	stopConversation = "false",
	options = {
		{"@conversation/imperial_broker:s_4b0c16d2", "are_you_recruiting"}, -- Are you recruiting Imperial Pilots?
		{"@conversation/imperial_broker:s_53", "never_mind_6"}, -- Never mind.
	}
}
imperial_broker_convo_template:addScreen(yes_sir_);

yes_maam_ = ConvoScreen:new {
	id = "yes_maam_",
	leftDialog = "@conversation/imperial_broker:s_fda95628", -- Yes, ma'am!  How may I be of assistance?
	stopConversation = "false",
	options = {
		{"@conversation/imperial_broker:s_57", "are_you_recruiting_22"}, -- Are you recruiting Imperial Pilots?
		{"@conversation/imperial_broker:s_94", "never_mind_23"}, -- Never mind.
	}
}
imperial_broker_convo_template:addScreen(yes_maam_);

what_do_you = ConvoScreen:new {
	id = "what_do_you",
	leftDialog = "@conversation/imperial_broker:s_6a1562ad", -- What do you want?
	stopConversation = "false",
	options = {
		{"@conversation/imperial_broker:s_840482e7", "nothing_"}, -- Nothing
		{"@conversation/imperial_broker:s_61a663b2", "i_want_to_46"}, -- I want to be an Imperial Pilot
	}
}
imperial_broker_convo_template:addScreen(what_do_you);

can_i_help = ConvoScreen:new {
	id = "can_i_help",
	leftDialog = "@conversation/imperial_broker:s_59be173", -- Can I help you?
	stopConversation = "false",
	options = {
		{"@conversation/imperial_broker:s_106", "are_you_recruiting_47"}, -- Are you recruiting Imperial Pilots?
		{"@conversation/imperial_broker:s_445a2be4", "no_never_mind"}, -- No. Never mind.
	}
}
imperial_broker_convo_template:addScreen(can_i_help);

i_would_like = ConvoScreen:new {
	id = "i_would_like",
	leftDialog = "@conversation/imperial_broker:s_458bda80", -- Did I hear you correctly? You want to retire? You are aware that you would lose all your pilot skills, and your mission records would be deleted. If you sign up again, you will start as a new recruit. Are you sure this is what you want to do?
	stopConversation = "false",
	options = {
		{"@conversation/imperial_broker:s_658b5a75", "yes_i_want"}, -- Yes, I want to retire.
		{"@conversation/imperial_broker:s_13", "i_changed_my"}, -- I changed my mind. I will stay.
	}
}
imperial_broker_convo_template:addScreen(i_would_like);

never_mind = ConvoScreen:new {
	id = "never_mind",
	leftDialog = "@conversation/imperial_broker:s_6441a2a6", -- As you wish.
	stopConversation = "true",
	options = {
	}
}
imperial_broker_convo_template:addScreen(never_mind);

yes_i_want = ConvoScreen:new {
	id = "yes_i_want",
	leftDialog = "@conversation/imperial_broker:s_fbeabc76", -- If that's what you want, I'll start getting your discharge papers together. If you want to change your mind, now is the time.
	stopConversation = "false",
	options = {
		{"@conversation/imperial_broker:s_f72f24be", "i_want_to"}, -- I want to retire.
		{"@conversation/imperial_broker:s_f220efed", "i_changed_my_2"}, -- I changed my mind. I will stay.
	}
}
imperial_broker_convo_template:addScreen(yes_i_want);

i_changed_my = ConvoScreen:new {
	id = "i_changed_my",
	leftDialog = "@conversation/imperial_broker:s_15", -- You've made the right choice, pilot. Dismissed.
	stopConversation = "true",
	options = {
	}
}
imperial_broker_convo_template:addScreen(i_changed_my);

i_want_to = ConvoScreen:new {
	id = "i_want_to",
	leftDialog = "@conversation/imperial_broker:s_ccdbfea7", -- Very well. You are now discharged from the Imperial Navy. I must say that I am disappointed. I expected better from you.
	stopConversation = "true",
	options = {
	}
}
imperial_broker_convo_template:addScreen(i_want_to);

i_changed_my_2 = ConvoScreen:new {
	id = "i_changed_my_2",
	leftDialog = "@conversation/imperial_broker:s_e8ccc35c", -- You've made the right choice, pilot. Dismissed.
	stopConversation = "true",
	options = {
	}
}
imperial_broker_convo_template:addScreen(i_changed_my_2);

black_epsilon = ConvoScreen:new {
	id = "black_epsilon",
	leftDialog = "@conversation/imperial_broker:s_772c81dd", -- Yes, sir.  Black Epsilon is stationed at the Imperial Base on Talus, as Corellia itself is officially neutral... for now.  There are reports of considerable Rebel activity in the area, as you can imagine.  They could really use more pilots there, sir.
	stopConversation = "false",
	options = {
		{"@conversation/imperial_broker:s_70f18874", "im_not_interested"}, -- I'm not interested in that.
		{"@conversation/imperial_broker:s_df2917b1", "tell_me_more"}, -- Tell me more
	}
}
imperial_broker_convo_template:addScreen(black_epsilon);

storm_squadron = ConvoScreen:new {
	id = "storm_squadron",
	leftDialog = "@conversation/imperial_broker:s_e0db13e8", -- Storm Squadron is one of the Empire's finest military units, in space or otherwise.  They're the very model of the sort of hard-core, dedicated, soldiers that secure the Empire throughout the galaxy.
	stopConversation = "false",
	options = {
		{"@conversation/imperial_broker:s_40", "im_not_interested_13"}, -- I'm not interested in that.
		{"@conversation/imperial_broker:s_43", "tell_me_more_14"}, -- Tell me more
	}
}
imperial_broker_convo_template:addScreen(storm_squadron);

imperial_inquisition = ConvoScreen:new {
	id = "imperial_inquisition",
	leftDialog = "@conversation/imperial_broker:s_929272e8", -- Imperial Inquisition is a special unit located in the Naboo system, sir.  They tend to deal in highly classified missions, so I'm afraid there's not a lot I'm authorized to tell you.
	stopConversation = "false",
	options = {
		{"@conversation/imperial_broker:s_48", "im_not_interested_18"}, -- I'm not interested in that.
		{"@conversation/imperial_broker:s_13a23fbc", "tell_me_what"}, -- Tell me what you can
	}
}
imperial_broker_convo_template:addScreen(imperial_inquisition);

black_epsilon_3 = ConvoScreen:new {
	id = "black_epsilon_3",
	leftDialog = "@conversation/imperial_broker:s_c2c89e35", -- Yes, ma'am.  Black Epsilon is stationed at the Imperial Base on Talus, as Corellia itself is officially neutral... for now.  There are reports of considerable Rebel activity in the area, as you can imagine.  They could really use more pilots there, ma'am.
	stopConversation = "false",
	options = {
		{"@conversation/imperial_broker:s_69", "im_not_interested_29"}, -- I'm not interested in that.
		{"@conversation/imperial_broker:s_72", "tell_me_more_30"}, -- Tell me more
	}
}
imperial_broker_convo_template:addScreen(black_epsilon_3);

storm_squadron_4 = ConvoScreen:new {
	id = "storm_squadron_4",
	leftDialog = "@conversation/imperial_broker:s_77", -- Storm Squadron is one of the Empire's finest military units, in space or otherwise.  They're the very model of the sort of hard-core, dedicated, soldiers that secure the Empire throughout the galaxy.
	stopConversation = "false",
	options = {
		{"@conversation/imperial_broker:s_79", "im_not_interested_34"}, -- I'm not interested in that.
		{"@conversation/imperial_broker:s_82", "tell_me_more_35"}, -- Tell me more
	}
}
imperial_broker_convo_template:addScreen(storm_squadron_4);

imperial_inquisition_5 = ConvoScreen:new {
	id = "imperial_inquisition_5",
	leftDialog = "@conversation/imperial_broker:s_b89f31b", -- Imperial Inquisition is a special unit located in the Naboo system, ma'am.  They tend to deal in highly classified missions, so I'm afraid there's not a lot I'm authorized to tell you.
	stopConversation = "false",
	options = {
		{"@conversation/imperial_broker:s_88", "im_not_interested_39"}, -- I'm not interested in that.
		{"@conversation/imperial_broker:s_91", "tell_me_what_40"}, -- Tell me what you can
	}
}
imperial_broker_convo_template:addScreen(imperial_inquisition_5);

are_you_recruiting = ConvoScreen:new {
	id = "are_you_recruiting",
	leftDialog = "@conversation/imperial_broker:s_8c387e5c", -- Sir! Yes, sir!  Are you here to sign-up?
	stopConversation = "false",
	options = {
		{"@conversation/imperial_broker:s_8ed93c34", "no_just_checking"}, -- No, just checking.
		{"@conversation/imperial_broker:s_b0ea6e8c", "yes_what"}, -- Yes.  What do I need to do?
	}
}
imperial_broker_convo_template:addScreen(are_you_recruiting);

never_mind_6 = ConvoScreen:new {
	id = "never_mind_6",
	leftDialog = "@conversation/imperial_broker:s_f5f50ae3", -- Of course.  My mistake.
	stopConversation = "true",
	options = {
	}
}
imperial_broker_convo_template:addScreen(never_mind_6);

no_just_checking = ConvoScreen:new {
	id = "no_just_checking",
	leftDialog = "@conversation/imperial_broker:s_8755e6eb", -- Very well, sir.  Please come see me if you change your mind.  The Empire could use more soldiers of your caliber in space!
	stopConversation = "true",
	options = {
	}
}
imperial_broker_convo_template:addScreen(no_just_checking);

yes_what = ConvoScreen:new {
	id = "yes_what",
	leftDialog = "@conversation/imperial_broker:s_4577214d", -- I'm authorized to send you to one of three assignments, sir.  You can choose Storm Squadron in the Tatooine system, Black Epsilon in the Corellia system, or the Imperial Inquisition in the Naboo system.
	stopConversation = "false",
	options = {
		{"@conversation/imperial_broker:s_1b2086de", "black_epsilon_65"}, -- Black Epsilon?
		{"@conversation/imperial_broker:s_4cafd748", "storm_squadron_66"}, -- Storm Squadron?
		{"@conversation/imperial_broker:s_23ef3e33", "imperial_inquisition_67"}, -- Imperial Inquisition?
	}
}
imperial_broker_convo_template:addScreen(yes_what);

black_epsilon_7 = ConvoScreen:new {
	id = "black_epsilon_7",
	leftDialog = "@conversation/imperial_broker:s_772c81dd", -- Yes, sir.  Black Epsilon is stationed at the Imperial Base on Talus, as Corellia itself is officially neutral... for now.  There are reports of considerable Rebel activity in the area, as you can imagine.  They could really use more pilots there, sir.
	stopConversation = "false",
	options = {
		{"@conversation/imperial_broker:s_70f18874", "im_not_interested"}, -- I'm not interested in that.
		{"@conversation/imperial_broker:s_df2917b1", "tell_me_more"}, -- Tell me more
	}
}
imperial_broker_convo_template:addScreen(black_epsilon_7);

storm_squadron_8 = ConvoScreen:new {
	id = "storm_squadron_8",
	leftDialog = "@conversation/imperial_broker:s_e0db13e8", -- Storm Squadron is one of the Empire's finest military units, in space or otherwise.  They're the very model of the sort of hard-core, dedicated, soldiers that secure the Empire throughout the galaxy.
	stopConversation = "false",
	options = {
		{"@conversation/imperial_broker:s_40", "im_not_interested_13"}, -- I'm not interested in that.
		{"@conversation/imperial_broker:s_43", "tell_me_more_14"}, -- Tell me more
	}
}
imperial_broker_convo_template:addScreen(storm_squadron_8);

imperial_inquisition_9 = ConvoScreen:new {
	id = "imperial_inquisition_9",
	leftDialog = "@conversation/imperial_broker:s_929272e8", -- Imperial Inquisition is a special unit located in the Naboo system, sir.  They tend to deal in highly classified missions, so I'm afraid there's not a lot I'm authorized to tell you.
	stopConversation = "false",
	options = {
		{"@conversation/imperial_broker:s_48", "im_not_interested_18"}, -- I'm not interested in that.
		{"@conversation/imperial_broker:s_13a23fbc", "tell_me_what"}, -- Tell me what you can
	}
}
imperial_broker_convo_template:addScreen(imperial_inquisition_9);

im_not_interested = ConvoScreen:new {
	id = "im_not_interested",
	leftDialog = "@conversation/imperial_broker:s_a7d90105", -- Very well, sir.  What about Storm Squadron or the Imperial Inquisition?
	stopConversation = "false",
	options = {
		{"@conversation/imperial_broker:s_1b2086de", "black_epsilon_65"}, -- Black Epsilon?
		{"@conversation/imperial_broker:s_4cafd748", "storm_squadron_66"}, -- Storm Squadron?
		{"@conversation/imperial_broker:s_23ef3e33", "imperial_inquisition_67"}, -- Imperial Inquisition?
	}
}
imperial_broker_convo_template:addScreen(im_not_interested);

tell_me_more = ConvoScreen:new {
	id = "tell_me_more",
	leftDialog = "@conversation/imperial_broker:s_cc37bca4", -- Yes, sir.  I can't release any specific details about their current engagements, but I will add the location of their own recruiter to your datapad.  If you'll speak with this officer in the Imperial Base on Talus, he will get you squared away.
	stopConversation = "true",
	options = {
	}
}
imperial_broker_convo_template:addScreen(tell_me_more);

black_epsilon_10 = ConvoScreen:new {
	id = "black_epsilon_10",
	leftDialog = "@conversation/imperial_broker:s_772c81dd", -- Yes, sir.  Black Epsilon is stationed at the Imperial Base on Talus, as Corellia itself is officially neutral... for now.  There are reports of considerable Rebel activity in the area, as you can imagine.  They could really use more pilots there, sir.
	stopConversation = "false",
	options = {
		{"@conversation/imperial_broker:s_70f18874", "im_not_interested"}, -- I'm not interested in that.
		{"@conversation/imperial_broker:s_df2917b1", "tell_me_more"}, -- Tell me more
	}
}
imperial_broker_convo_template:addScreen(black_epsilon_10);

storm_squadron_11 = ConvoScreen:new {
	id = "storm_squadron_11",
	leftDialog = "@conversation/imperial_broker:s_e0db13e8", -- Storm Squadron is one of the Empire's finest military units, in space or otherwise.  They're the very model of the sort of hard-core, dedicated, soldiers that secure the Empire throughout the galaxy.
	stopConversation = "false",
	options = {
		{"@conversation/imperial_broker:s_40", "im_not_interested_13"}, -- I'm not interested in that.
		{"@conversation/imperial_broker:s_43", "tell_me_more_14"}, -- Tell me more
	}
}
imperial_broker_convo_template:addScreen(storm_squadron_11);

imperial_inquisition_12 = ConvoScreen:new {
	id = "imperial_inquisition_12",
	leftDialog = "@conversation/imperial_broker:s_929272e8", -- Imperial Inquisition is a special unit located in the Naboo system, sir.  They tend to deal in highly classified missions, so I'm afraid there's not a lot I'm authorized to tell you.
	stopConversation = "false",
	options = {
		{"@conversation/imperial_broker:s_48", "im_not_interested_18"}, -- I'm not interested in that.
		{"@conversation/imperial_broker:s_13a23fbc", "tell_me_what"}, -- Tell me what you can
	}
}
imperial_broker_convo_template:addScreen(imperial_inquisition_12);

im_not_interested_13 = ConvoScreen:new {
	id = "im_not_interested_13",
	leftDialog = "@conversation/imperial_broker:s_a8b71650", -- Yes, sir.  What about Black Epsilon or the Imperial Inquisition?
	stopConversation = "false",
	options = {
		{"@conversation/imperial_broker:s_1b2086de", "black_epsilon_65"}, -- Black Epsilon?
		{"@conversation/imperial_broker:s_4cafd748", "storm_squadron_66"}, -- Storm Squadron?
		{"@conversation/imperial_broker:s_23ef3e33", "imperial_inquisition_67"}, -- Imperial Inquisition?
	}
}
imperial_broker_convo_template:addScreen(im_not_interested_13);

tell_me_more_14 = ConvoScreen:new {
	id = "tell_me_more_14",
	leftDialog = "@conversation/imperial_broker:s_5817eef2", -- Yes, sir.  I can't release any specific details about their current engagements, but I will add the location of the Storm Squadron commander to your datapad.  He'll be glad to have a soldier of your standing.  You can find him in the Bestine Pilot's Club next to the capitol building on Tatooine.
	stopConversation = "true",
	options = {
	}
}
imperial_broker_convo_template:addScreen(tell_me_more_14);

black_epsilon_15 = ConvoScreen:new {
	id = "black_epsilon_15",
	leftDialog = "@conversation/imperial_broker:s_772c81dd", -- Yes, sir.  Black Epsilon is stationed at the Imperial Base on Talus, as Corellia itself is officially neutral... for now.  There are reports of considerable Rebel activity in the area, as you can imagine.  They could really use more pilots there, sir.
	stopConversation = "false",
	options = {
		{"@conversation/imperial_broker:s_70f18874", "im_not_interested"}, -- I'm not interested in that.
		{"@conversation/imperial_broker:s_df2917b1", "tell_me_more"}, -- Tell me more
	}
}
imperial_broker_convo_template:addScreen(black_epsilon_15);

storm_squadron_16 = ConvoScreen:new {
	id = "storm_squadron_16",
	leftDialog = "@conversation/imperial_broker:s_e0db13e8", -- Storm Squadron is one of the Empire's finest military units, in space or otherwise.  They're the very model of the sort of hard-core, dedicated, soldiers that secure the Empire throughout the galaxy.
	stopConversation = "false",
	options = {
		{"@conversation/imperial_broker:s_40", "im_not_interested_13"}, -- I'm not interested in that.
		{"@conversation/imperial_broker:s_43", "tell_me_more_14"}, -- Tell me more
	}
}
imperial_broker_convo_template:addScreen(storm_squadron_16);

imperial_inquisition_17 = ConvoScreen:new {
	id = "imperial_inquisition_17",
	leftDialog = "@conversation/imperial_broker:s_929272e8", -- Imperial Inquisition is a special unit located in the Naboo system, sir.  They tend to deal in highly classified missions, so I'm afraid there's not a lot I'm authorized to tell you.
	stopConversation = "false",
	options = {
		{"@conversation/imperial_broker:s_48", "im_not_interested_18"}, -- I'm not interested in that.
		{"@conversation/imperial_broker:s_13a23fbc", "tell_me_what"}, -- Tell me what you can
	}
}
imperial_broker_convo_template:addScreen(imperial_inquisition_17);

im_not_interested_18 = ConvoScreen:new {
	id = "im_not_interested_18",
	leftDialog = "@conversation/imperial_broker:s_ed23ffff", -- Are you interested in either Black Epsilon or the Storm Squadron, sir?
	stopConversation = "false",
	options = {
		{"@conversation/imperial_broker:s_1b2086de", "black_epsilon_65"}, -- Black Epsilon?
		{"@conversation/imperial_broker:s_4cafd748", "storm_squadron_66"}, -- Storm Squadron?
		{"@conversation/imperial_broker:s_23ef3e33", "imperial_inquisition_67"}, -- Imperial Inquisition?
	}
}
imperial_broker_convo_template:addScreen(im_not_interested_18);

tell_me_what = ConvoScreen:new {
	id = "tell_me_what",
	leftDialog = "@conversation/imperial_broker:s_f05830e3", -- There's not much more I can say, sir, but I will add the location to your datapad.  Talk to the Imperial Pilot trainer in Kaadara.  You'll find the association hall in the main plaza.
	stopConversation = "true",
	options = {
	}
}
imperial_broker_convo_template:addScreen(tell_me_what);

black_epsilon_19 = ConvoScreen:new {
	id = "black_epsilon_19",
	leftDialog = "@conversation/imperial_broker:s_772c81dd", -- Yes, sir.  Black Epsilon is stationed at the Imperial Base on Talus, as Corellia itself is officially neutral... for now.  There are reports of considerable Rebel activity in the area, as you can imagine.  They could really use more pilots there, sir.
	stopConversation = "false",
	options = {
		{"@conversation/imperial_broker:s_70f18874", "im_not_interested"}, -- I'm not interested in that.
		{"@conversation/imperial_broker:s_df2917b1", "tell_me_more"}, -- Tell me more
	}
}
imperial_broker_convo_template:addScreen(black_epsilon_19);

storm_squadron_20 = ConvoScreen:new {
	id = "storm_squadron_20",
	leftDialog = "@conversation/imperial_broker:s_e0db13e8", -- Storm Squadron is one of the Empire's finest military units, in space or otherwise.  They're the very model of the sort of hard-core, dedicated, soldiers that secure the Empire throughout the galaxy.
	stopConversation = "false",
	options = {
		{"@conversation/imperial_broker:s_40", "im_not_interested_13"}, -- I'm not interested in that.
		{"@conversation/imperial_broker:s_43", "tell_me_more_14"}, -- Tell me more
	}
}
imperial_broker_convo_template:addScreen(storm_squadron_20);

imperial_inquisition_21 = ConvoScreen:new {
	id = "imperial_inquisition_21",
	leftDialog = "@conversation/imperial_broker:s_929272e8", -- Imperial Inquisition is a special unit located in the Naboo system, sir.  They tend to deal in highly classified missions, so I'm afraid there's not a lot I'm authorized to tell you.
	stopConversation = "false",
	options = {
		{"@conversation/imperial_broker:s_48", "im_not_interested_18"}, -- I'm not interested in that.
		{"@conversation/imperial_broker:s_13a23fbc", "tell_me_what"}, -- Tell me what you can
	}
}
imperial_broker_convo_template:addScreen(imperial_inquisition_21);

are_you_recruiting_22 = ConvoScreen:new {
	id = "are_you_recruiting_22",
	leftDialog = "@conversation/imperial_broker:s_d78c7ec0", -- Ma'am!  Yes, ma'am!  Are you here to sign-up?
	stopConversation = "false",
	options = {
		{"@conversation/imperial_broker:s_60", "no_just_checking_24"}, -- No, just checking.
		{"@conversation/imperial_broker:s_63", "yes_what_25"}, -- Yes.  What do I need to do?
	}
}
imperial_broker_convo_template:addScreen(are_you_recruiting_22);

never_mind_23 = ConvoScreen:new {
	id = "never_mind_23",
	leftDialog = "@conversation/imperial_broker:s_96", -- Of course.  My mistake.
	stopConversation = "true",
	options = {
	}
}
imperial_broker_convo_template:addScreen(never_mind_23);

no_just_checking_24 = ConvoScreen:new {
	id = "no_just_checking_24",
	leftDialog = "@conversation/imperial_broker:s_83a7ae89", -- Very well, ma'am.  Please come see me if you change your mind.  The Empire could use more soldiers of your caliber in space!
	stopConversation = "true",
	options = {
	}
}
imperial_broker_convo_template:addScreen(no_just_checking_24);

yes_what_25 = ConvoScreen:new {
	id = "yes_what_25",
	leftDialog = "@conversation/imperial_broker:s_b8884586", -- I'm authorized to send you to one of three assignments, ma'am.  You can choose Storm Squadron in the Tatooine system, Black Epsilon in the Corellia system, or the Imperial Inquisition in the Naboo system.
	stopConversation = "false",
	options = {
		{"@conversation/imperial_broker:s_66", "black_epsilon_41"}, -- Black Epsilon?
		{"@conversation/imperial_broker:s_75", "storm_squadron_42"}, -- Storm Squadron?
		{"@conversation/imperial_broker:s_85", "imperial_inquisition_43"}, -- Imperial Inquisition?
	}
}
imperial_broker_convo_template:addScreen(yes_what_25);

black_epsilon_26 = ConvoScreen:new {
	id = "black_epsilon_26",
	leftDialog = "@conversation/imperial_broker:s_c2c89e35", -- Yes, ma'am.  Black Epsilon is stationed at the Imperial Base on Talus, as Corellia itself is officially neutral... for now.  There are reports of considerable Rebel activity in the area, as you can imagine.  They could really use more pilots there, ma'am.
	stopConversation = "false",
	options = {
		{"@conversation/imperial_broker:s_69", "im_not_interested_29"}, -- I'm not interested in that.
		{"@conversation/imperial_broker:s_72", "tell_me_more_30"}, -- Tell me more
	}
}
imperial_broker_convo_template:addScreen(black_epsilon_26);

storm_squadron_27 = ConvoScreen:new {
	id = "storm_squadron_27",
	leftDialog = "@conversation/imperial_broker:s_77", -- Storm Squadron is one of the Empire's finest military units, in space or otherwise.  They're the very model of the sort of hard-core, dedicated, soldiers that secure the Empire throughout the galaxy.
	stopConversation = "false",
	options = {
		{"@conversation/imperial_broker:s_79", "im_not_interested_34"}, -- I'm not interested in that.
		{"@conversation/imperial_broker:s_82", "tell_me_more_35"}, -- Tell me more
	}
}
imperial_broker_convo_template:addScreen(storm_squadron_27);

imperial_inquisition_28 = ConvoScreen:new {
	id = "imperial_inquisition_28",
	leftDialog = "@conversation/imperial_broker:s_b89f31b", -- Imperial Inquisition is a special unit located in the Naboo system, ma'am.  They tend to deal in highly classified missions, so I'm afraid there's not a lot I'm authorized to tell you.
	stopConversation = "false",
	options = {
		{"@conversation/imperial_broker:s_88", "im_not_interested_39"}, -- I'm not interested in that.
		{"@conversation/imperial_broker:s_91", "tell_me_what_40"}, -- Tell me what you can
	}
}
imperial_broker_convo_template:addScreen(imperial_inquisition_28);

im_not_interested_29 = ConvoScreen:new {
	id = "im_not_interested_29",
	leftDialog = "@conversation/imperial_broker:s_407fb5e3", -- Very well, ma'am.  What about Storm Squadron or the Imperial Inquisition?
	stopConversation = "false",
	options = {
		{"@conversation/imperial_broker:s_66", "black_epsilon_41"}, -- Black Epsilon?
		{"@conversation/imperial_broker:s_75", "storm_squadron_42"}, -- Storm Squadron?
		{"@conversation/imperial_broker:s_85", "imperial_inquisition_43"}, -- Imperial Inquisition?
	}
}
imperial_broker_convo_template:addScreen(im_not_interested_29);

tell_me_more_30 = ConvoScreen:new {
	id = "tell_me_more_30",
	leftDialog = "@conversation/imperial_broker:s_b945b46a", -- Yes, ma'am.  I can't release any specific details about their current engagements, but I will add the location of their own recruiter to your datapad.  If you'll speak with this officer in the Imperial Base on Talus, he will get you squared away.
	stopConversation = "true",
	options = {
	}
}
imperial_broker_convo_template:addScreen(tell_me_more_30);

black_epsilon_31 = ConvoScreen:new {
	id = "black_epsilon_31",
	leftDialog = "@conversation/imperial_broker:s_c2c89e35", -- Yes, ma'am.  Black Epsilon is stationed at the Imperial Base on Talus, as Corellia itself is officially neutral... for now.  There are reports of considerable Rebel activity in the area, as you can imagine.  They could really use more pilots there, ma'am.
	stopConversation = "false",
	options = {
		{"@conversation/imperial_broker:s_69", "im_not_interested_29"}, -- I'm not interested in that.
		{"@conversation/imperial_broker:s_72", "tell_me_more_30"}, -- Tell me more
	}
}
imperial_broker_convo_template:addScreen(black_epsilon_31);

storm_squadron_32 = ConvoScreen:new {
	id = "storm_squadron_32",
	leftDialog = "@conversation/imperial_broker:s_77", -- Storm Squadron is one of the Empire's finest military units, in space or otherwise.  They're the very model of the sort of hard-core, dedicated, soldiers that secure the Empire throughout the galaxy.
	stopConversation = "false",
	options = {
		{"@conversation/imperial_broker:s_79", "im_not_interested_34"}, -- I'm not interested in that.
		{"@conversation/imperial_broker:s_82", "tell_me_more_35"}, -- Tell me more
	}
}
imperial_broker_convo_template:addScreen(storm_squadron_32);

imperial_inquisition_33 = ConvoScreen:new {
	id = "imperial_inquisition_33",
	leftDialog = "@conversation/imperial_broker:s_b89f31b", -- Imperial Inquisition is a special unit located in the Naboo system, ma'am.  They tend to deal in highly classified missions, so I'm afraid there's not a lot I'm authorized to tell you.
	stopConversation = "false",
	options = {
		{"@conversation/imperial_broker:s_88", "im_not_interested_39"}, -- I'm not interested in that.
		{"@conversation/imperial_broker:s_91", "tell_me_what_40"}, -- Tell me what you can
	}
}
imperial_broker_convo_template:addScreen(imperial_inquisition_33);

im_not_interested_34 = ConvoScreen:new {
	id = "im_not_interested_34",
	leftDialog = "@conversation/imperial_broker:s_42693321", -- I see.  What about Black Epsilon or the Imperial Inquisition?
	stopConversation = "false",
	options = {
		{"@conversation/imperial_broker:s_66", "black_epsilon_41"}, -- Black Epsilon?
		{"@conversation/imperial_broker:s_75", "storm_squadron_42"}, -- Storm Squadron?
		{"@conversation/imperial_broker:s_85", "imperial_inquisition_43"}, -- Imperial Inquisition?
	}
}
imperial_broker_convo_template:addScreen(im_not_interested_34);

tell_me_more_35 = ConvoScreen:new {
	id = "tell_me_more_35",
	leftDialog = "@conversation/imperial_broker:s_cd41504a", -- Yes, ma'am.  I can't release any specific details about their current engagements, but I will add this location to your datapad.  Talk to the trainer in the Bestine Pilot's Club, near the capitol building on Tatooine.
	stopConversation = "true",
	options = {
	}
}
imperial_broker_convo_template:addScreen(tell_me_more_35);

black_epsilon_36 = ConvoScreen:new {
	id = "black_epsilon_36",
	leftDialog = "@conversation/imperial_broker:s_c2c89e35", -- Yes, ma'am.  Black Epsilon is stationed at the Imperial Base on Talus, as Corellia itself is officially neutral... for now.  There are reports of considerable Rebel activity in the area, as you can imagine.  They could really use more pilots there, ma'am.
	stopConversation = "false",
	options = {
		{"@conversation/imperial_broker:s_69", "im_not_interested_29"}, -- I'm not interested in that.
		{"@conversation/imperial_broker:s_72", "tell_me_more_30"}, -- Tell me more
	}
}
imperial_broker_convo_template:addScreen(black_epsilon_36);

storm_squadron_37 = ConvoScreen:new {
	id = "storm_squadron_37",
	leftDialog = "@conversation/imperial_broker:s_77", -- Storm Squadron is one of the Empire's finest military units, in space or otherwise.  They're the very model of the sort of hard-core, dedicated, soldiers that secure the Empire throughout the galaxy.
	stopConversation = "false",
	options = {
		{"@conversation/imperial_broker:s_79", "im_not_interested_34"}, -- I'm not interested in that.
		{"@conversation/imperial_broker:s_82", "tell_me_more_35"}, -- Tell me more
	}
}
imperial_broker_convo_template:addScreen(storm_squadron_37);

imperial_inquisition_38 = ConvoScreen:new {
	id = "imperial_inquisition_38",
	leftDialog = "@conversation/imperial_broker:s_b89f31b", -- Imperial Inquisition is a special unit located in the Naboo system, ma'am.  They tend to deal in highly classified missions, so I'm afraid there's not a lot I'm authorized to tell you.
	stopConversation = "false",
	options = {
		{"@conversation/imperial_broker:s_88", "im_not_interested_39"}, -- I'm not interested in that.
		{"@conversation/imperial_broker:s_91", "tell_me_what_40"}, -- Tell me what you can
	}
}
imperial_broker_convo_template:addScreen(imperial_inquisition_38);

im_not_interested_39 = ConvoScreen:new {
	id = "im_not_interested_39",
	leftDialog = "@conversation/imperial_broker:s_d28bda49", -- Would you be interested in either Black Epsilon or the Storm Squadron, ma'am?
	stopConversation = "false",
	options = {
		{"@conversation/imperial_broker:s_66", "black_epsilon_41"}, -- Black Epsilon?
		{"@conversation/imperial_broker:s_75", "storm_squadron_42"}, -- Storm Squadron?
		{"@conversation/imperial_broker:s_85", "imperial_inquisition_43"}, -- Imperial Inquisition?
	}
}
imperial_broker_convo_template:addScreen(im_not_interested_39);

tell_me_what_40 = ConvoScreen:new {
	id = "tell_me_what_40",
	leftDialog = "@conversation/imperial_broker:s_8ac37a1f", -- There's not much more I can say, ma'am, but I will add this location to your datapad.  Talk to the Pilot Trainer in the association hall on Kaadara, near the main plaza.
	stopConversation = "true",
	options = {
	}
}
imperial_broker_convo_template:addScreen(tell_me_what_40);

black_epsilon_41 = ConvoScreen:new {
	id = "black_epsilon_41",
	leftDialog = "@conversation/imperial_broker:s_c2c89e35", -- Yes, ma'am.  Black Epsilon is stationed at the Imperial Base on Talus, as Corellia itself is officially neutral... for now.  There are reports of considerable Rebel activity in the area, as you can imagine.  They could really use more pilots there, ma'am.
	stopConversation = "false",
	options = {
		{"@conversation/imperial_broker:s_69", "im_not_interested_29"}, -- I'm not interested in that.
		{"@conversation/imperial_broker:s_72", "tell_me_more_30"}, -- Tell me more
	}
}
imperial_broker_convo_template:addScreen(black_epsilon_41);

storm_squadron_42 = ConvoScreen:new {
	id = "storm_squadron_42",
	leftDialog = "@conversation/imperial_broker:s_77", -- Storm Squadron is one of the Empire's finest military units, in space or otherwise.  They're the very model of the sort of hard-core, dedicated, soldiers that secure the Empire throughout the galaxy.
	stopConversation = "false",
	options = {
		{"@conversation/imperial_broker:s_79", "im_not_interested_34"}, -- I'm not interested in that.
		{"@conversation/imperial_broker:s_82", "tell_me_more_35"}, -- Tell me more
	}
}
imperial_broker_convo_template:addScreen(storm_squadron_42);

imperial_inquisition_43 = ConvoScreen:new {
	id = "imperial_inquisition_43",
	leftDialog = "@conversation/imperial_broker:s_b89f31b", -- Imperial Inquisition is a special unit located in the Naboo system, ma'am.  They tend to deal in highly classified missions, so I'm afraid there's not a lot I'm authorized to tell you.
	stopConversation = "false",
	options = {
		{"@conversation/imperial_broker:s_88", "im_not_interested_39"}, -- I'm not interested in that.
		{"@conversation/imperial_broker:s_91", "tell_me_what_40"}, -- Tell me what you can
	}
}
imperial_broker_convo_template:addScreen(imperial_inquisition_43);

nothing_ = ConvoScreen:new {
	id = "nothing_",
	leftDialog = "@conversation/imperial_broker:s_d1c489c0", -- In that case, please stop bothering me.  I am very busy.
	stopConversation = "true",
	options = {
	}
}
imperial_broker_convo_template:addScreen(nothing_);

i_want_to_44 = ConvoScreen:new {
	id = "i_want_to_44",
	leftDialog = "@conversation/imperial_broker:s_b19ac578", -- HAHAHAHAHA!  Imagine that!  A big fur-ball like you flying a ship for the Empire!  Oh that is RICH!
	stopConversation = "true",
	options = {
	}
}
imperial_broker_convo_template:addScreen(i_want_to_44);

i_want_to_45 = ConvoScreen:new {
	id = "i_want_to_45",
	leftDialog = "@conversation/imperial_broker:s_3bbddad5", -- Sir, I don't intend any disrespect, but the Imperial Pilots are the finest in the Galaxy.  You don't look like the sort of person who could last one week in the cadet academy, let alone pilot any sort of Imperial craft.  Now I think you should leave.  I am very busy.
	stopConversation = "true",
	options = {
	}
}
imperial_broker_convo_template:addScreen(i_want_to_45);

i_want_to_46 = ConvoScreen:new {
	id = "i_want_to_46",
	leftDialog = "@conversation/imperial_broker:s_99e09eaf", -- Ma'am, you wouldn't last one nano-second as an Imperial pilot.  It's a strenuous, demanding profession that requires the utmost dedication.  Not to mention the fact that females are notoriously bad pilots!  Now if you will excuse me, good day!
	stopConversation = "true",
	options = {
	}
}
imperial_broker_convo_template:addScreen(i_want_to_46);

are_you_recruiting_47 = ConvoScreen:new {
	id = "are_you_recruiting_47",
	leftDialog = "@conversation/imperial_broker:s_14270b3", -- Are you here to sign-up?
	stopConversation = "false",
	options = {
		{"@conversation/imperial_broker:s_109", "no_just_checking_48"}, -- No, just checking.
		{"@conversation/imperial_broker:s_112", "yes_what_49"}, -- Yes.  What do I need to do?
	}
}
imperial_broker_convo_template:addScreen(are_you_recruiting_47);

no_never_mind = ConvoScreen:new {
	id = "no_never_mind",
	leftDialog = "@conversation/imperial_broker:s_895d093", -- Ok.
	stopConversation = "true",
	options = {
	}
}
imperial_broker_convo_template:addScreen(no_never_mind);

no_just_checking_48 = ConvoScreen:new {
	id = "no_just_checking_48",
	leftDialog = "@conversation/imperial_broker:s_2a4c66e4", -- Come see me if you change your mind.  Someone has to stand up to the Rebel Alliance and maintain order in the galaxy.
	stopConversation = "true",
	options = {
	}
}
imperial_broker_convo_template:addScreen(no_just_checking_48);

yes_what_49 = ConvoScreen:new {
	id = "yes_what_49",
	leftDialog = "@conversation/imperial_broker:s_106caa1d", -- The units with vacancies currently are the Storm Squadron in the Tatooine system, Black Epsilon in the Corellia system, or the Imperial Inquisition in the Naboo system.
	stopConversation = "false",
	options = {
		{"@conversation/imperial_broker:s_115", "black_epsilon_55"}, -- Black Epsilon?
		{"@conversation/imperial_broker:s_124", "storm_squadron_56"}, -- Storm Squadron?
		{"@conversation/imperial_broker:s_134", "imperial_inquisition_57"}, -- Imperial Inquisition?
	}
}
imperial_broker_convo_template:addScreen(yes_what_49);

black_epsilon_50 = ConvoScreen:new {
	id = "black_epsilon_50",
	leftDialog = "@conversation/imperial_broker:s_86cb9899", -- Yes.  Black Epsilon is stationed at the Imperial Base on Talus, as Corellia itself is officially neutral... for now.  There are reports of considerable Rebel activity in the area.
	stopConversation = "false",
	options = {
		{"@conversation/imperial_broker:s_118", "im_not_interested_53"}, -- I'm not interested in that.
		{"@conversation/imperial_broker:s_121", "tell_me_more_54"}, -- Tell me more
	}
}
imperial_broker_convo_template:addScreen(black_epsilon_50);

storm_squadron_51 = ConvoScreen:new {
	id = "storm_squadron_51",
	leftDialog = "@conversation/imperial_broker:s_126", -- Storm Squadron is one of the Empire's finest military units, in space or otherwise.  They're the very model of the sort of hard-core, dedicated, soldiers that secure the Empire throughout the galaxy.
	stopConversation = "false",
	options = {
		{"@conversation/imperial_broker:s_128", "im_not_interested_58"}, -- I'm not interested in that.
		{"@conversation/imperial_broker:s_131", "tell_me_more_59"}, -- Tell me more
	}
}
imperial_broker_convo_template:addScreen(storm_squadron_51);

imperial_inquisition_52 = ConvoScreen:new {
	id = "imperial_inquisition_52",
	leftDialog = "@conversation/imperial_broker:s_3c9c6441", -- Imperial Inquisition is a special unit located in the Naboo system.  Their mission is highly classified.
	stopConversation = "false",
	options = {
		{"@conversation/imperial_broker:s_137", "im_not_interested_63"}, -- I'm not interested in that.
		{"@conversation/imperial_broker:s_141", "tell_me_what_64"}, -- Tell me what you can
	}
}
imperial_broker_convo_template:addScreen(imperial_inquisition_52);

im_not_interested_53 = ConvoScreen:new {
	id = "im_not_interested_53",
	leftDialog = "@conversation/imperial_broker:s_9f862c74", -- What about Storm Squadron or the Imperial Inquisition?
	stopConversation = "false",
	options = {
		{"@conversation/imperial_broker:s_115", "black_epsilon_55"}, -- Black Epsilon?
		{"@conversation/imperial_broker:s_124", "storm_squadron_56"}, -- Storm Squadron?
		{"@conversation/imperial_broker:s_134", "imperial_inquisition_57"}, -- Imperial Inquisition?
	}
}
imperial_broker_convo_template:addScreen(im_not_interested_53);

tell_me_more_54 = ConvoScreen:new {
	id = "tell_me_more_54",
	leftDialog = "@conversation/imperial_broker:s_3d734747", -- I won't release any specific details about their current engagements, but I will add the location of their recruiting officer to your datapad.  You can find him in the Imperial Base on Talus, in the Corellia system.
	stopConversation = "true",
	options = {
	}
}
imperial_broker_convo_template:addScreen(tell_me_more_54);

black_epsilon_55 = ConvoScreen:new {
	id = "black_epsilon_55",
	leftDialog = "@conversation/imperial_broker:s_86cb9899", -- Yes.  Black Epsilon is stationed at the Imperial Base on Talus, as Corellia itself is officially neutral... for now.  There are reports of considerable Rebel activity in the area.
	stopConversation = "false",
	options = {
		{"@conversation/imperial_broker:s_118", "im_not_interested_53"}, -- I'm not interested in that.
		{"@conversation/imperial_broker:s_121", "tell_me_more_54"}, -- Tell me more
	}
}
imperial_broker_convo_template:addScreen(black_epsilon_55);

storm_squadron_56 = ConvoScreen:new {
	id = "storm_squadron_56",
	leftDialog = "@conversation/imperial_broker:s_126", -- Storm Squadron is one of the Empire's finest military units, in space or otherwise.  They're the very model of the sort of hard-core, dedicated, soldiers that secure the Empire throughout the galaxy.
	stopConversation = "false",
	options = {
		{"@conversation/imperial_broker:s_128", "im_not_interested_58"}, -- I'm not interested in that.
		{"@conversation/imperial_broker:s_131", "tell_me_more_59"}, -- Tell me more
	}
}
imperial_broker_convo_template:addScreen(storm_squadron_56);

imperial_inquisition_57 = ConvoScreen:new {
	id = "imperial_inquisition_57",
	leftDialog = "@conversation/imperial_broker:s_3c9c6441", -- Imperial Inquisition is a special unit located in the Naboo system.  Their mission is highly classified.
	stopConversation = "false",
	options = {
		{"@conversation/imperial_broker:s_137", "im_not_interested_63"}, -- I'm not interested in that.
		{"@conversation/imperial_broker:s_141", "tell_me_what_64"}, -- Tell me what you can
	}
}
imperial_broker_convo_template:addScreen(imperial_inquisition_57);

im_not_interested_58 = ConvoScreen:new {
	id = "im_not_interested_58",
	leftDialog = "@conversation/imperial_broker:s_727cf8b6", -- What about Black Epsilon or the Imperial Inquisition?
	stopConversation = "false",
	options = {
		{"@conversation/imperial_broker:s_1b2086de", "black_epsilon_65"}, -- Black Epsilon?
		{"@conversation/imperial_broker:s_4cafd748", "storm_squadron_66"}, -- Storm Squadron?
		{"@conversation/imperial_broker:s_23ef3e33", "imperial_inquisition_67"}, -- Imperial Inquisition?
	}
}
imperial_broker_convo_template:addScreen(im_not_interested_58);

tell_me_more_59 = ConvoScreen:new {
	id = "tell_me_more_59",
	leftDialog = "@conversation/imperial_broker:s_7287c2b7", -- I won't release any specific details about their current engagements, but I will add the location of the Storm Squadron pilot trainer to your datapad.  You'll find him in the Bestine Pilot's club on Tatooine, next to the capitol building.
	stopConversation = "true",
	options = {
	}
}
imperial_broker_convo_template:addScreen(tell_me_more_59);

black_epsilon_60 = ConvoScreen:new {
	id = "black_epsilon_60",
	leftDialog = "@conversation/imperial_broker:s_772c81dd", -- Yes, sir.  Black Epsilon is stationed at the Imperial Base on Talus, as Corellia itself is officially neutral... for now.  There are reports of considerable Rebel activity in the area, as you can imagine.  They could really use more pilots there, sir.
	stopConversation = "false",
	options = {
		{"@conversation/imperial_broker:s_70f18874", "im_not_interested"}, -- I'm not interested in that.
		{"@conversation/imperial_broker:s_df2917b1", "tell_me_more"}, -- Tell me more
	}
}
imperial_broker_convo_template:addScreen(black_epsilon_60);

storm_squadron_61 = ConvoScreen:new {
	id = "storm_squadron_61",
	leftDialog = "@conversation/imperial_broker:s_e0db13e8", -- Storm Squadron is one of the Empire's finest military units, in space or otherwise.  They're the very model of the sort of hard-core, dedicated, soldiers that secure the Empire throughout the galaxy.
	stopConversation = "false",
	options = {
		{"@conversation/imperial_broker:s_40", "im_not_interested_13"}, -- I'm not interested in that.
		{"@conversation/imperial_broker:s_43", "tell_me_more_14"}, -- Tell me more
	}
}
imperial_broker_convo_template:addScreen(storm_squadron_61);

imperial_inquisition_62 = ConvoScreen:new {
	id = "imperial_inquisition_62",
	leftDialog = "@conversation/imperial_broker:s_929272e8", -- Imperial Inquisition is a special unit located in the Naboo system, sir.  They tend to deal in highly classified missions, so I'm afraid there's not a lot I'm authorized to tell you.
	stopConversation = "false",
	options = {
		{"@conversation/imperial_broker:s_48", "im_not_interested_18"}, -- I'm not interested in that.
		{"@conversation/imperial_broker:s_13a23fbc", "tell_me_what"}, -- Tell me what you can
	}
}
imperial_broker_convo_template:addScreen(imperial_inquisition_62);

im_not_interested_63 = ConvoScreen:new {
	id = "im_not_interested_63",
	leftDialog = "@conversation/imperial_broker:s_139", -- Are you interested in either Black Epsilon or the Storm Squadron, sir?
	stopConversation = "false",
	options = {
		{"@conversation/imperial_broker:s_1b2086de", "black_epsilon_65"}, -- Black Epsilon?
		{"@conversation/imperial_broker:s_4cafd748", "storm_squadron_66"}, -- Storm Squadron?
		{"@conversation/imperial_broker:s_23ef3e33", "imperial_inquisition_67"}, -- Imperial Inquisition?
	}
}
imperial_broker_convo_template:addScreen(im_not_interested_63);

tell_me_what_64 = ConvoScreen:new {
	id = "tell_me_what_64",
	leftDialog = "@conversation/imperial_broker:s_2fe6ab5f", -- Highly.  Classified.  Right?  I will add the location of the unit's pilot trainer to your datapad.  You may speak to him in the main plaza association hall in Kaadara, on Naboo.
	stopConversation = "true",
	options = {
	}
}
imperial_broker_convo_template:addScreen(tell_me_what_64);

black_epsilon_65 = ConvoScreen:new {
	id = "black_epsilon_65",
	leftDialog = "@conversation/imperial_broker:s_772c81dd", -- Yes, sir.  Black Epsilon is stationed at the Imperial Base on Talus, as Corellia itself is officially neutral... for now.  There are reports of considerable Rebel activity in the area, as you can imagine.  They could really use more pilots there, sir.
	stopConversation = "false",
	options = {
		{"@conversation/imperial_broker:s_70f18874", "im_not_interested"}, -- I'm not interested in that.
		{"@conversation/imperial_broker:s_df2917b1", "tell_me_more"}, -- Tell me more
	}
}
imperial_broker_convo_template:addScreen(black_epsilon_65);

storm_squadron_66 = ConvoScreen:new {
	id = "storm_squadron_66",
	leftDialog = "@conversation/imperial_broker:s_e0db13e8", -- Storm Squadron is one of the Empire's finest military units, in space or otherwise.  They're the very model of the sort of hard-core, dedicated, soldiers that secure the Empire throughout the galaxy.
	stopConversation = "false",
	options = {
		{"@conversation/imperial_broker:s_40", "im_not_interested_13"}, -- I'm not interested in that.
		{"@conversation/imperial_broker:s_43", "tell_me_more_14"}, -- Tell me more
	}
}
imperial_broker_convo_template:addScreen(storm_squadron_66);

imperial_inquisition_67 = ConvoScreen:new {
	id = "imperial_inquisition_67",
	leftDialog = "@conversation/imperial_broker:s_929272e8", -- Imperial Inquisition is a special unit located in the Naboo system, sir.  They tend to deal in highly classified missions, so I'm afraid there's not a lot I'm authorized to tell you.
	stopConversation = "false",
	options = {
		{"@conversation/imperial_broker:s_48", "im_not_interested_18"}, -- I'm not interested in that.
		{"@conversation/imperial_broker:s_13a23fbc", "tell_me_what"}, -- Tell me what you can
	}
}
imperial_broker_convo_template:addScreen(imperial_inquisition_67);

addConversationTemplate("imperial_broker_convo_template", imperial_broker_convo_template);
