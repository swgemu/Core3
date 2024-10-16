gil_burtin_convo_template = ConvoTemplate:new {
	initialScreen = "hello_nice_to",
	templateType = "Lua",
	luaClassHandler = "gilBurtinConvoHandler",
	screens = {}
}

--[[

	Generic Responses

]]

hello_nice_to = ConvoScreen:new {
	id = "hello_nice_to",
	leftDialog = "@conversation/privateer_broker:s_c3f7c619", -- Hello. Nice to see you!
	stopConversation = "true",
	options = {
	}
}
gil_burtin_convo_template:addScreen(hello_nice_to);

you_dont_look = ConvoScreen:new {
	id = "you_dont_look",
	leftDialog = "@conversation/privateer_broker:s_79be144a", -- You don't look like a pilot to me. But I guess you can still hang-out here if you like. Try to be quiet, though.
	stopConversation = "true",
	options = {
	}
}
gil_burtin_convo_template:addScreen(you_dont_look);


--[[

	Player is a Neutral Pilot
	- Retire
	- End Conversation Response

]]

hey_ive_heard = ConvoScreen:new {
	id = "hey_ive_heard",
	leftDialog = "@conversation/privateer_broker:s_13dd951a", -- Hey, I've heard people talkin' about you! Rumor is you've turned into a pretty decent pilot! What can I do for you?
	stopConversation = "false",
	options = {
		{"@conversation/privateer_broker:s_a6f3f40b", "ive_come_to_retire"}, -- I've come to retire my status as a pilot.
		{"@conversation/privateer_broker:s_8cb932b7", "nothing_goodbye"}, -- Nothing. Goodbye.
	}
}
gil_burtin_convo_template:addScreen(hey_ive_heard);

ive_come_to_retire = ConvoScreen:new {
	id = "ive_come_to_retire",
	leftDialog = "@conversation/privateer_broker:s_d0969d78", -- You want to what? Retire? You know if you retire, you'll lose all your pilot skills and they'll throw out your mission record, right? If you ever want to join up again, you'll start out as a new recruit. Are you sure that's what you want?
	stopConversation = "false",
	options = {
		{"@conversation/privateer_broker:s_71bc4ac7", "yes_retire"}, -- Yes. I want to retire.
		{"@conversation/privateer_broker:s_eaf87760", "eh_i_changed_1"}, -- Eh, I changed my mind. I'll stay.
	}
}
gil_burtin_convo_template:addScreen(ive_come_to_retire);

yes_retire = ConvoScreen:new {
	id = "yes_retire",
	leftDialog = "@conversation/privateer_broker:s_bdf43a8a", -- Well, you're the boss. I'll get the documents ready to transfer. If you want to change your mind, now's the time...
	stopConversation = "false",
	options = {
		{"@conversation/privateer_broker:s_f72f24be", "i_want_to_retire"}, -- I want to retire.
		{"@conversation/privateer_broker:s_eaf87760", "eh_i_changed_1"}, -- Eh, I changed my mind. I'll stay.
	}
}
gil_burtin_convo_template:addScreen(yes_retire);


--[[

	Player is not a pilot for any faction
	- End Conversation Response
	- Join as Neutral Pilot

]]

yes__ = ConvoScreen:new {
	id = "yes__",
	leftDialog = "@conversation/privateer_broker:s_9fdd7cf3", -- Yes?
	stopConversation = "false",
	options = {
		{"@conversation/privateer_broker:s_169df3bb", "never_mind"}, -- Never mind.
		{"@conversation/privateer_broker:s_f6dbaaf2", "ive_come_to_join"}, -- I've come to join the Pilots Guild.
	}
}
gil_burtin_convo_template:addScreen(yes__);

ive_come_to_join = ConvoScreen:new {
	id = "ive_come_to_join",
	leftDialog = "@conversation/privateer_broker:s_2d7a0d3", -- Indeed? Well, shame about that. We've had some trouble you see...
	stopConversation = "false",
	options = {
		{"@conversation/privateer_broker:s_562906b3", "what_trouble"}, -- What trouble?
	}
}
gil_burtin_convo_template:addScreen(ive_come_to_join);

what_trouble = ConvoScreen:new {
	id = "what_trouble",
	leftDialog = "@conversation/privateer_broker:s_5626358b", -- Well it's Imperial Decree 875a subparagraph 13! The Pilots Guild used to oversee almost all aspects of space travel from training new pilots to establishing preferred travel routes, but the Emperor won't even allow us to distribute 'The Basics of Space Flight' without express written consent.
	stopConversation = "false",
	options = {
		{"@conversation/privateer_broker:s_ce87b83e", "what_is_the"}, -- What is 'The Basics of Space Flight'?
		{"@conversation/privateer_broker:s_f90d3de4", "why_dont_you"}, -- Why don't you get permission to distribute it then?
		{"@conversation/privateer_broker:s_61657d0f", "i_see"}, -- I see.
	}
}
gil_burtin_convo_template:addScreen(what_trouble);

what_is_the = ConvoScreen:new {
	id = "what_is_the",
	leftDialog = "@conversation/privateer_broker:s_d3a7e09", -- Oh, handy book, that. Explained all an aspiring pilot needs to know about piloting privately-owned starships. Travel routes, where to go to get private contracts, how to get certified by the necessary authorities to engage in commerce... you know, all that sort of stuff.
	stopConversation = "false",
	options = {
		{"@conversation/privateer_broker:s_ce87b83e", "what_is_the"}, -- What is 'The Basics of Space Flight'?
		{"@conversation/privateer_broker:s_f90d3de4", "why_dont_you_1"}, -- Why don't you get permission to distribute it then?
		{"@conversation/privateer_broker:s_61657d0f", "i_see"}, -- I see.
	}
}
gil_burtin_convo_template:addScreen(what_is_the);

why_dont_you_1 = ConvoScreen:new {
	id = "why_dont_you",
	leftDialog = "@conversation/privateer_broker:s_bad24bb9", -- On a case-by-case basis? Impossible! Do you have any idea how many pilots there are in the galaxy? Thousands! Hundreds of thousands! Millions!
	stopConversation = "false",
	options = {
		{"@conversation/privateer_broker:s_ce87b83e", "what_is_the_6"}, -- What is 'The Basics of Space Flight'?
		{"@conversation/privateer_broker:s_f90d3de4", "why_dont_you_1"}, -- Why don't you get permission to distribute it then?
		{"@conversation/privateer_broker:s_61657d0f", "i_see"}, -- I see.
	}
}
gil_burtin_convo_template:addScreen(why_dont_you_1);

i_see = ConvoScreen:new {
	id = "i_see",
	leftDialog = "@conversation/privateer_broker:s_74c33af", -- That's not the half of it! Imperial Decree 875a subparagraph 19 mandates that we still engage in recruitment activities - you know, job fairs and mass recruitments and that sort of thing - but then any potential recruits are directed straight to the Imperial Academy.
	stopConversation = "false",
	options = {
		{"@conversation/privateer_broker:s_22c8a818", "so_where_is"}, -- So where is the Imperial Academy?
		{"@conversation/privateer_broker:s_77becf16", "not_really"}, -- I don't want to fly for the Empire.
	}
}
gil_burtin_convo_template:addScreen(i_see);

so_where_is = ConvoScreen:new {
	id = "so_where_is",
	leftDialog = "@conversation/privateer_broker:s_d1caa227", -- You mean you actually WANT to fly for the Empire? There's a war on, you know. It's very dangerous.
	stopConversation = "false",
	options = {
		{"@conversation/privateer_broker:s_3269c6d", "not_really"}, -- Not really.
		{"@conversation/privateer_broker:s_757d93fb", "yes_i_do"}, -- Yes I do.
	}
}
gil_burtin_convo_template:addScreen(so_where_is);

not_really = ConvoScreen:new {
	id = "not_really",
	leftDialog = "@conversation/privateer_broker:s_e6455de", -- I don't blame you for not wanting to fly for the Empire. It's dangerous what with the Rebel Alliance and all. Do you have any idea what the kill ratio of X-wings to TIE Fighters is?
	stopConversation = "false",
	options = {
		{"@conversation/privateer_broker:s_da0b2f54", "no_what_is"}, -- No, what is it?
		{"@conversation/privateer_broker:s_7f3a602f", "where_else_can"}, -- Where else can I learn to be a pilot?
	}
}
gil_burtin_convo_template:addScreen(not_really);

no_what_is = ConvoScreen:new {
	id = "no_what_is",
	leftDialog = "@conversation/privateer_broker:s_80d6e310", -- Well... I don't actually know, but I bet it isn't very good.
	stopConversation = "false",
	options = {
		{"@conversation/privateer_broker:s_da0b2f54", "no_what_is"}, -- No, what is it?
		{"@conversation/privateer_broker:s_7f3a602f", "where_else_can"}, -- Where else can I learn to be a pilot?
	}
}
gil_burtin_convo_template:addScreen(no_what_is);

where_else_can = ConvoScreen:new {
	id = "where_else_can",
	leftDialog = "@conversation/privateer_broker:s_4cc40305", -- Lots of places! Look, CorSec off on Corellia is a prime example. They're always looking for new recruits. And there's the RSF on Naboo, as well. Not to mention work you could get right here in the Outer Rim. Or even the Rebel Alliance, if you don't mind getting executed. What sort of piloting are you interested in?
	stopConversation = "false",
	options = {
		{"@conversation/privateer_broker:s_fd3512f0", "corsec"}, -- CorSec?
		{"@conversation/privateer_broker:s_83c3a855", "rsf"}, -- RSF?
		{"@conversation/privateer_broker:s_2c417dde", "tatooine"}, -- Tatooine?
		{"@conversation/privateer_broker:s_6ea276b4", "rebel_alliance"}, -- Rebel Alliance?
	}
}
gil_burtin_convo_template:addScreen(where_else_can);


-- CorSec

corsec = ConvoScreen:new {
	id = "corsec",
	leftDialog = "@conversation/privateer_broker:s_8c645195", -- That's right. Corellian Security. Since Corellia is officially neutral in this whole Empire versus the Alliance business, they've got to provide for their own defense. Some of the best pilots in the galaxy come from Corellia, you know?
	stopConversation = "false",
	options = {
		{"@conversation/privateer_broker:s_159911f5", "tell_me_more_corsec"}, -- Tell me more.
		{"@conversation/privateer_broker:s_e3ec2640", "im_not_interested_corsec"}, -- I'm not interested.
	}
}
gil_burtin_convo_template:addScreen(corsec);

tell_me_more_corsec = ConvoScreen:new {
	id = "tell_me_more_corsec",
	leftDialog = "@conversation/privateer_broker:s_f58ab655", -- Here, I'll add this location to your datapad... Go to CorSec headquarters on Coronet. It's just down the street from the starport. Go inside and talk to the CorSec Pilot trainer. He can tell you all about CorSec and get you signed-up!
	stopConversation = "false",
	options = {
		{"@conversation/privateer_broker:s_e4c89252", "thanks_bye"}, -- Thanks. Bye!
		{"@conversation/privateer_broker:s_f51c795", "on_second_thought_37"}, -- On second thought... never mind.
	}
}
gil_burtin_convo_template:addScreen(tell_me_more_corsec);

im_not_interested_corsec = ConvoScreen:new {
	id = "im_not_interested_corsec",
	leftDialog = "@conversation/privateer_broker:s_d6791368", -- Oh... well how about the RSF or work here on Tatooine? Are you interested in that sort of thing?
	stopConversation = "false",
	options = {
		{"@conversation/privateer_broker:s_fd3512f0", "corsec"}, -- CorSec?
		{"@conversation/privateer_broker:s_83c3a855", "rsf"}, -- RSF?
		{"@conversation/privateer_broker:s_2c417dde", "tatooine"}, -- Tatooine?
		{"@conversation/privateer_broker:s_6ea276b4", "rebel_alliance"}, -- Rebel Alliance?
	}
}
gil_burtin_convo_template:addScreen(im_not_interested_corsec);

-- RSF

rsf = ConvoScreen:new {
	id = "rsf",
	leftDialog = "@conversation/privateer_broker:s_fd94591f", -- Yes. Royal Security Force. Talk about a cushy job! Think of it as Naboo's version of CorSec... only, of course, Naboo's also got the Empire defending it. It is the Emperor's home world, you know!
	stopConversation = "false",
	options = {
		{"@conversation/privateer_broker:s_159911f5", "tell_me_more_rsf"}, -- Tell me more.
		{"@conversation/privateer_broker:s_e3ec2640", "not_interested_rsf"}, -- I'm not interested.
	}
}
gil_burtin_convo_template:addScreen(rsf);

tell_me_more_rsf = ConvoScreen:new {
	id = "tell_me_more_rsf",
	leftDialog = "@conversation/privateer_broker:s_1d78d511", -- Here, I'll add this location to your datapad... go see the RSF Pilot trainer in the Theed Palace. He can tell you all about the RSF. He'll probably bore you to death with long flowery speeches about their 'noble history' and all that nonsense.
	stopConversation = "false",
	options = {
		{"@conversation/privateer_broker:s_e4c89252", "thanks_bye"}, -- Thanks. Bye!
		{"@conversation/privateer_broker:s_f51c795", "not_interested_rsf"}, -- On second thought... never mind.
	}
}
gil_burtin_convo_template:addScreen(tell_me_more_rsf);

not_interested_rsf = ConvoScreen:new {
	id = "not_interested_rsf",
	leftDialog = "@conversation/privateer_broker:s_8bed64bc", -- Oh... well how about CorSec or work here on Tatooine? Are you interested in that sort of thing?
	stopConversation = "false",
	options = {
		{"@conversation/privateer_broker:s_fd3512f0", "corsec"}, -- CorSec?
		{"@conversation/privateer_broker:s_83c3a855", "rsf"}, -- RSF?
		{"@conversation/privateer_broker:s_2c417dde", "tatooine"}, -- Tatooine?
		{"@conversation/privateer_broker:s_6ea276b4", "rebel_alliance"}, -- Rebel Alliance?
	}
}
gil_burtin_convo_template:addScreen(not_interested_rsf);

-- Tatooine

tatooine = ConvoScreen:new {
	id = "tatooine",
	leftDialog = "@conversation/privateer_broker:s_f800df2d", -- Yes. Well... not really my thing, you understand, but there has always been a certain... ah... 'fringe element' on the outer worlds. Smugglers, ruffians, pirates, thugs... that sort of thing.
	stopConversation = "false",
	options = {
		{"@conversation/privateer_broker:s_159911f5", "tell_me_more_tatooine"}, -- Tell me more.
		{"@conversation/privateer_broker:s_e3ec2640", "not_interested_tatooine"}, -- I'm not interested.
	}
}
gil_burtin_convo_template:addScreen(tatooine);

tell_me_more_tatooine = ConvoScreen:new {
	id = "tell_me_more_tatooine",
	leftDialog = "@conversation/privateer_broker:s_bedc35ff", -- Here, I'll add this location to your datapad... this is the Mos Eisley cantina. They don't get a lot of attention from the law out here in the Tatooine system, so there's always someone there looking for pilots willing to brave the wild frontier, so to speak.
	stopConversation = "false",
	options = {
		{"@conversation/privateer_broker:s_e4c89252", "thanks_bye"}, -- Thanks. Bye!
		{"@conversation/privateer_broker:s_f51c795", "not_interested_tatooine"}, -- On second thought... never mind.
	}
}
gil_burtin_convo_template:addScreen(tell_me_more_tatooine);

not_interested_tatooine = ConvoScreen:new {
	id = "not_interested_tatooine",
	leftDialog = "@conversation/privateer_broker:s_8e1dc39f", -- Oh... well how about CorSec or the RSF? Are you interested in that?
	stopConversation = "false",
	options = {
		{"@conversation/privateer_broker:s_fd3512f0", "corsec"}, -- CorSec?
		{"@conversation/privateer_broker:s_83c3a855", "rsf"}, -- RSF?
		{"@conversation/privateer_broker:s_2c417dde", "tatooine"}, -- Tatooine?
		{"@conversation/privateer_broker:s_6ea276b4", "rebel_alliance"}, -- Rebel Alliance?
	}
}
gil_burtin_convo_template:addScreen(not_interested_tatooine);

-- Rebel Alliance

rebel_alliance = ConvoScreen:new {
	id = "rebel_alliance",
	leftDialog = "@conversation/privateer_broker:s_a5fd1ad3", -- Say, that's pretty dangerous. Going up against the Empire's huge fleet with nothing but whatever ragtag bunch you can get to oppose them? Still, I suppose the Empire DID destroy Alderaan...
	stopConversation = "false",
	options = {
		{"@conversation/privateer_broker:s_159911f5", "tell_me_more_rebel"}, -- Tell me more.
		{"@conversation/privateer_broker:s_e3ec2640", "not_interested_rebel"}, -- I'm not interested.
	}
}
gil_burtin_convo_template:addScreen(rebel_alliance);

tell_me_more_rebel = ConvoScreen:new {
	id = "tell_me_more_rebel",
	leftDialog = "@conversation/privateer_broker:s_fdea49b9", -- Ok, but you didn't hear this from me... Meet this fellow in the park in front of the Tyrena Starport. He can tell you where to go from there.
	stopConversation = "false",
	options = {
		{"@conversation/privateer_broker:s_e4c89252", "thanks_bye"}, -- Thanks. Bye!
		{"@conversation/privateer_broker:s_f51c795", "not_interested_tatooine"}, -- On second thought... never mind.
	}
}
gil_burtin_convo_template:addScreen(tell_me_more_rebel);

-- Empire

empire_coordinates = ConvoScreen:new {
	id = "empire_coordinates",
	leftDialog = "@conversation/privateer_broker:s_3cb06a88", -- Ok, ok. Here, I'll add these coordinates to your datapad.
	stopConversation = "false",
	options = {
		{"@conversation/privateer_broker:s_e6101168", "what_is_this"}, -- What is this?
		{"@conversation/privateer_broker:s_fc27931b", "thanks_"}, -- Thanks.
	}
}
gil_burtin_convo_template:addScreen(empire_coordinates);

empire_coordinates2 = ConvoScreen:new {
	id = "empire_coordinates2",
	leftDialog = "@conversation/privateer_broker:s_3cb06a88", -- Ok, ok. Here, I'll add these coordinates to your datapad.
	stopConversation = "false",
	options = {
		{"@conversation/privateer_broker:s_e6101168", "what_is_this"}, -- What is this?
		{"@conversation/privateer_broker:s_fc27931b", "thanks_"}, -- Thanks.
	}
}
gil_burtin_convo_template:addScreen(empire_coordinates2);

what_is_this = ConvoScreen:new {
	id = "what_is_this",
	leftDialog = "@conversation/privateer_broker:s_e19a5c9a", -- That's the location of the Imperial Pilot recruiter. You go talk to him and he'll get you all fixed up. You'll be dead in no time.
	stopConversation = "false",
	options = {
		{"@conversation/privateer_broker:s_cf4d3521", "well_see_about"}, -- We'll see about that.
		{"@conversation/privateer_broker:s_ee816dc0", "hey_"}, -- Hey!
	}
}
gil_burtin_convo_template:addScreen(what_is_this);

hey_ = ConvoScreen:new {
	id = "hey_",
	leftDialog = "@conversation/privateer_broker:s_b31be86", -- Just tellin' it like it is, my friend. They're going to put you in a tiny little ball with a tiny little gun built by the lowest bidder.
	stopConversation = "false",
	options = {
		{"@conversation/privateer_broker:s_44d6c7b2", "well_see_about"}, -- I don't care!
		{"@conversation/privateer_broker:s_759870d1", "other_choices"}, -- Uh... I think I changed my mind. Can't I choose to do something else?
	}
}
gil_burtin_convo_template:addScreen(hey_);

other_choices = ConvoScreen:new {
	id = "other_choices",
	leftDialog = "@conversation/privateer_broker:s_bd56d5dd", -- Of course you have a choice. We all have choices. There are still... other places you could go to get some basic flight training.
	stopConversation = "false",
	options = {
		{"@conversation/privateer_broker:s_1fd99cce", "empire_coordinates"}, -- I want to fly for the Empire.
		{"@conversation/privateer_broker:s_fea04ae8", "not_really"}, -- What other places?
	}
}
gil_burtin_convo_template:addScreen(other_choices);

yes_i_do = ConvoScreen:new {
	id = "yes_i_do",
	leftDialog = "@conversation/privateer_broker:s_f3e5d7a0", -- Oh. Well... then why did you come to see me? The Empire dumps more recruitment on the Holonet daily than we do in a year.
	stopConversation = "false",
	options = {
		{"@conversation/privateer_broker:s_56acd306", "i_was_just"}, -- I was just nearby.
		{"@conversation/privateer_broker:s_43f7f8f5", "empire_coordinates2"}, -- Are you going to direct me to the Academy?
		{"@conversation/privateer_broker:s_c2320129", "not_really"}, -- I don't really want to fly for the Empire.
	}
}
gil_burtin_convo_template:addScreen(yes_i_do);

i_was_just = ConvoScreen:new {
	id = "i_was_just",
	leftDialog = "@conversation/privateer_broker:s_f97198ff", -- I see. Well... in that case... say you don't really want to fly for the Empire, do you?
	stopConversation = "false",
	options = {
		{"@conversation/privateer_broker:s_cc9259e0", "other_choices"}, -- Do I have a choice?
		{"@conversation/privateer_broker:s_3269c6d", "not_really"}, -- Not really.
		{"@conversation/privateer_broker:s_f43b859", "not_really"}, -- I would rather be independent.
		{"@conversation/privateer_broker:s_757d93fb", "empire_coordinates"}, -- Yes I do.
	}
}
gil_burtin_convo_template:addScreen(i_was_just);

--[[

	Conversation Ending Responses

]]

nothing_goodbye = ConvoScreen:new {
	id = "nothing_goodbye",
	leftDialog = "@conversation/privateer_broker:s_f15359b4", -- So long!
	stopConversation = "true",
	options = {
	}
}
gil_burtin_convo_template:addScreen(nothing_goodbye);

eh_i_changed = ConvoScreen:new {
	id = "eh_i_changed",
	leftDialog = "@conversation/privateer_broker:s_fcd4dd70", -- That's what I like to hear. Take care, friend.
	stopConversation = "true",
	options = {
	}
}
gil_burtin_convo_template:addScreen(eh_i_changed);

i_want_to_retire = ConvoScreen:new {
	id = "i_want_to_retire",
	leftDialog = "@conversation/privateer_broker:s_2059cc73", -- It's a blasted shame - that's what it is. Waste of a fine pilot. Take care in life, friend.
	stopConversation = "true",
	options = {
	}
}
gil_burtin_convo_template:addScreen(i_want_to_retire);

eh_i_changed_1 = ConvoScreen:new {
	id = "eh_i_changed_1",
	leftDialog = "@conversation/privateer_broker:s_fcd4dd70", -- That's what I like to hear. Take care, friend.
	stopConversation = "true",
	options = {
	}
}
gil_burtin_convo_template:addScreen(eh_i_changed_1);

never_mind = ConvoScreen:new {
	id = "never_mind",
	leftDialog = "@conversation/privateer_broker:s_1d546116", -- Hm? Well, ok. See ya.
	stopConversation = "true",
	options = {
	}
}
gil_burtin_convo_template:addScreen(never_mind);

thanks_ = ConvoScreen:new {
	id = "thanks_",
	leftDialog = "@conversation/privateer_broker:s_510d393e", -- It's your funeral, pilot.
	stopConversation = "true",
	options = {
	}
}
gil_burtin_convo_template:addScreen(thanks_);

well_see_about = ConvoScreen:new {
	id = "well_see_about",
	leftDialog = "@conversation/privateer_broker:s_a59f385f", -- Let's see if you change your tune when you see that dinky little fighter with NO SHIELDS they give you! Ha!
	stopConversation = "true",
	options = {
	}
}
gil_burtin_convo_template:addScreen(well_see_about);

thanks_bye = ConvoScreen:new {
	id = "thanks_bye",
	leftDialog = "@conversation/privateer_broker:s_9ba377a3", -- Take care, friend.
	stopConversation = "true",
	options = {
	}
}
gil_burtin_convo_template:addScreen(thanks_bye);

addConversationTemplate("gil_burtin_convo_template", gil_burtin_convo_template);
