j_pai_brek_convo_template = ConvoTemplate:new {
	initialScreen = "nothing_i_can",
	templateType = "Lua",
	luaClassHandler = "jPaiBrekConvoHandler",
	screens = {}
}

nothing_i_can = ConvoScreen:new {
	id = "nothing_i_can",
	leftDialog = "@conversation/rebel_broker:s_2a805b93", -- Nothing I can do for you, friend. But if you know anyone that might make a good pilot, you ought to send them to see me. Good day.
	stopConversation = "true",
	options = {
	}
}
j_pai_brek_convo_template:addScreen(nothing_i_can);

hello_friend_its = ConvoScreen:new {
	id = "hello_friend_its",
	leftDialog = "@conversation/rebel_broker:s_b8e72ced", -- Hello, friend. It's always good to see that another skilled pilot has joined the ranks of the Alliance. What can I do for you?
	stopConversation = "false",
	options = {
		{"@conversation/rebel_broker:s_fc2710b9", "i_would_like"}, -- I would like to retire as a Rebel Pilot.
		{"@conversation/rebel_broker:s_3fd213c", "nothing_really"}, -- Nothing, really.
	}
}
j_pai_brek_convo_template:addScreen(hello_friend_its);

i_said_good = ConvoScreen:new {
	id = "i_said_good",
	leftDialog = "@conversation/rebel_broker:s_ee2fdf32", -- I said 'Good day'!
	stopConversation = "true",
	options = {
	}
}
j_pai_brek_convo_template:addScreen(i_said_good);

is_there_something = ConvoScreen:new {
	id = "is_there_something",
	leftDialog = "@conversation/rebel_broker:s_c4b91b55", -- Is there something I can help you with?
	stopConversation = "false",
	options = {
		{"@conversation/rebel_broker:s_d70dba34", "yes_"}, -- Yes.
		{"@conversation/rebel_broker:s_4c695dbd", "no_"}, -- No.
	}
}
j_pai_brek_convo_template:addScreen(is_there_something);

hello_friend_good = ConvoScreen:new {
	id = "hello_friend_good",
	leftDialog = "@conversation/rebel_broker:s_aad360f4", -- Hello, friend. Good day to you!
	stopConversation = "true",
	options = {
	}
}
j_pai_brek_convo_template:addScreen(hello_friend_good);

yes__ = ConvoScreen:new {
	id = "yes__",
	leftDialog = "@conversation/rebel_broker:s_9fdd7cf3", -- Yes?
	stopConversation = "false",
	options = {
		{"@conversation/rebel_broker:s_ca776e30", "who_are_you"}, -- Who are you?
	}
}
j_pai_brek_convo_template:addScreen(yes__);

i_would_like = ConvoScreen:new {
	id = "i_would_like",
	leftDialog = "@conversation/rebel_broker:s_b42be0ca", -- Wow, that's quite a bombshell. Are you sure? If you retire, you will lose all of your pilot skills and your mission logs will be erased. If you join up with the Alliance again, you will start out as a new recruit.
	stopConversation = "false",
	options = {
		{"@conversation/rebel_broker:s_658b5a75", "yes_i_want"}, -- Yes, I want to retire.
		{"@conversation/rebel_broker:s_697a1143", "ive_changed_my_1"}, -- I've changed my mind. I'll stay.
	}
}
j_pai_brek_convo_template:addScreen(i_would_like);

nothing_really = ConvoScreen:new {
	id = "nothing_really",
	leftDialog = "@conversation/rebel_broker:s_7671cbe2", -- I see. Best of luck to you in the future, then!
	stopConversation = "true",
	options = {
	}
}
j_pai_brek_convo_template:addScreen(nothing_really);

yes_i_want = ConvoScreen:new {
	id = "yes_i_want",
	leftDialog = "@conversation/rebel_broker:s_c3bfda20", -- Alright. I'll start getting the paperwork ready. If you want to change your mind, now's the time...
	stopConversation = "false",
	options = {
		{"@conversation/rebel_broker:s_f72f24be", "i_want_to"}, -- I want to retire.
		{"@conversation/rebel_broker:s_697a1143", "ive_changed_my_1"}, -- I've changed my mind. I'll stay.
	}
}
j_pai_brek_convo_template:addScreen(yes_i_want);

ive_changed_my = ConvoScreen:new {
	id = "ive_changed_my",
	leftDialog = "@conversation/rebel_broker:s_568d0bc", -- That's a relief. We'd really hate to lose a good pilot like yourself.
	stopConversation = "true",
	options = {
	}
}
j_pai_brek_convo_template:addScreen(ive_changed_my);

i_want_to = ConvoScreen:new {
	id = "i_want_to",
	leftDialog = "@conversation/rebel_broker:s_6ed0d2aa", -- Very well. We hate to lose a good pilot like yourself, but in the end, it's your decision.
	stopConversation = "true",
	options = {
	}
}
j_pai_brek_convo_template:addScreen(i_want_to);

ive_changed_my_1 = ConvoScreen:new {
	id = "ive_changed_my_1",
	leftDialog = "@conversation/rebel_broker:s_568d0bc", -- That's a relief. We'd really hate to lose a good pilot like yourself.
	stopConversation = "true",
	options = {
	}
}
j_pai_brek_convo_template:addScreen(ive_changed_my_1);

yes_ = ConvoScreen:new {
	id = "yes_",
	leftDialog = "@conversation/rebel_broker:s_ef21d878", -- And what would that be?
	stopConversation = "false",
	options = {
		{"@conversation/rebel_broker:s_c2a4c0b1", "are_you_recruiting"}, -- Are you recruiting pilots for the Rebel Alliance?
		{"@conversation/rebel_broker:s_169df3bb", "never_mind_3"}, -- Never mind.
	}
}
j_pai_brek_convo_template:addScreen(yes_);

no_ = ConvoScreen:new {
	id = "no_",
	leftDialog = "@conversation/rebel_broker:s_d6b3d709", -- It was nice meeting you.
	stopConversation = "true",
	options = {
	}
}
j_pai_brek_convo_template:addScreen(no_);

are_you_recruiting = ConvoScreen:new {
	id = "are_you_recruiting",
	leftDialog = "@conversation/rebel_broker:s_5af29bb7", -- No, of course not. That would be illegal.
	stopConversation = "false",
	options = {
		{"@conversation/rebel_broker:s_895d093", "ok_"}, -- Ok.
		{"@conversation/rebel_broker:s_c4d665ba", "i_dont_believe"}, -- I don't believe you.
	}
}
j_pai_brek_convo_template:addScreen(are_you_recruiting);

never_mind = ConvoScreen:new {
	id = "never_mind",
	leftDialog = "@conversation/rebel_broker:s_d6b3d709", -- It was nice meeting you.
	stopConversation = "true",
	options = {
	}
}
j_pai_brek_convo_template:addScreen(never_mind);

ok_ = ConvoScreen:new {
	id = "ok_",
	leftDialog = "@conversation/rebel_broker:s_d6b3d709", -- It was nice meeting you.
	stopConversation = "true",
	options = {
	}
}
j_pai_brek_convo_template:addScreen(ok_);

i_dont_believe = ConvoScreen:new {
	id = "i_dont_believe",
	leftDialog = "@conversation/rebel_broker:s_1c0a2eb0", -- I cannot imagine why not. If someone has been spreading rumors about me, you should report them... not me. I'm not doing anything wrong at all. Nothing whatsoever.
	stopConversation = "false",
	options = {
		{"@conversation/rebel_broker:s_50f22f35", "ok_just_checking"}, -- Ok, just checking.
		{"@conversation/rebel_broker:s_dbb2bd71", "you_are_lying"}, -- You are lying!
	}
}
j_pai_brek_convo_template:addScreen(i_dont_believe);

ok_just_checking = ConvoScreen:new {
	id = "ok_just_checking",
	leftDialog = "@conversation/rebel_broker:s_d6b3d709", -- It was nice meeting you.
	stopConversation = "true",
	options = {
	}
}
j_pai_brek_convo_template:addScreen(ok_just_checking);

you_are_lying = ConvoScreen:new {
	id = "you_are_lying",
	leftDialog = "@conversation/rebel_broker:s_28a5ab46", -- I most certainly am not! And I resent the implication! It's an absurd accusation! Ridiculous! Now if you'll excuse me, this conversation is over. Good day!
	stopConversation = "true",
	options = {
	}
}
j_pai_brek_convo_template:addScreen(you_are_lying);

who_are_you = ConvoScreen:new {
	id = "who_are_you",
	leftDialog = "@conversation/rebel_broker:s_8a4e6549", -- My name is J'pai Brek. How can I help you?
	stopConversation = "false",
	options = {
		{"@conversation/rebel_broker:s_e81a1436", "i_want_to_2"}, -- I want to be a pilot.
		{"@conversation/rebel_broker:s_169df3bb", "never_mind_3"}, -- Never mind.
	}
}
j_pai_brek_convo_template:addScreen(who_are_you);

i_want_to_2 = ConvoScreen:new {
	id = "i_want_to_2",
	leftDialog = "@conversation/rebel_broker:s_1adbb986", -- I see. Well, that does sound very exciting. But what makes you think I can help you with that?
	stopConversation = "false",
	options = {
		{"@conversation/rebel_broker:s_c0dd7feb", "i_received_a"}, -- I received a transmission from the Rebel Alliance
	}
}
j_pai_brek_convo_template:addScreen(i_want_to_2);

never_mind_3 = ConvoScreen:new {
	id = "never_mind_3",
	leftDialog = "@conversation/rebel_broker:s_d6b3d709", -- It was nice meeting you.
	stopConversation = "true",
	options = {
	}
}
j_pai_brek_convo_template:addScreen(never_mind_3);

i_received_a = ConvoScreen:new {
	id = "i_received_a",
	leftDialog = "@conversation/rebel_broker:s_3bde39e1", -- In that case, yes, I can direct you to a unit in need of volunteers. Do you have a preference for duty anywhere in particular?
	stopConversation = "false",
	options = {
		{"@conversation/rebel_broker:s_63cd6ccb", "naboo__14"}, -- Naboo.
		{"@conversation/rebel_broker:s_d15ec255", "corellia__15"}, -- Corellia.
		{"@conversation/rebel_broker:s_6491bb19", "tatooine__16"}, -- Tatooine.
	}
}
j_pai_brek_convo_template:addScreen(i_received_a);

naboo_ = ConvoScreen:new {
	id = "naboo_",
	leftDialog = "@conversation/rebel_broker:s_3714bdfe", -- Now that's quite a dangerous assignment! We have managed to install an Alliance Trainer droid in the city of Moenia. The Empire is quite strong in the Naboo system, but Moenia belongs to Borvo the Hutt... and he's indifferent to the Rebellion - so long as we stay out of his way.
	stopConversation = "false",
	options = {
		{"@conversation/rebel_broker:s_159911f5", "tell_me_more_12"}, -- Tell me more.
		{"@conversation/rebel_broker:s_70f18874", "im_not_interested_13"}, -- I'm not interested in that.
	}
}
j_pai_brek_convo_template:addScreen(naboo_);

corellia_ = ConvoScreen:new {
	id = "corellia_",
	leftDialog = "@conversation/rebel_broker:s_98a75031", -- Corellia's official stance is to remain neutral in the war against the Empire, but that has made it a useful place for us to marshal our forces.
	stopConversation = "false",
	options = {
		{"@conversation/rebel_broker:s_159911f5", "tell_me_more_12"}, -- Tell me more.
		{"@conversation/rebel_broker:s_70f18874", "im_not_interested_13"}, -- I'm not interested in that.
	}
}
j_pai_brek_convo_template:addScreen(corellia_);

tatooine_ = ConvoScreen:new {
	id = "tatooine_",
	leftDialog = "@conversation/rebel_broker:s_80d99409", -- Tatooine is a backwater world far removed from most of the action. It seems the criminals and pirates give us as much trouble there as the Empire. Still, it's an important assignment as the remote location allows us to gather resources and supplies without constant harassment from the Empire.
	stopConversation = "false",
	options = {
		{"@conversation/rebel_broker:s_159911f5", "tell_me_more_12"}, -- Tell me more.
		{"@conversation/rebel_broker:s_70f18874", "im_not_interested_13"}, -- I'm not interested in that.
	}
}
j_pai_brek_convo_template:addScreen(tatooine_);

tell_me_more = ConvoScreen:new {
	id = "tell_me_more",
	leftDialog = "@conversation/rebel_broker:s_c0ca92b1", -- Here, I'll add the location of our FX-model droid to your datapad. Whatever you do, don't allow that to fall into Imperial hands! Go there and speak with the droid.
	stopConversation = "true",
	options = {
	}
}
j_pai_brek_convo_template:addScreen(tell_me_more);

im_not_interested = ConvoScreen:new {
	id = "im_not_interested",
	leftDialog = "@conversation/rebel_broker:s_84d6bcaa", -- I don't blame you. The Empire has been absolutely ruthless in its war against the Alliance. What about Corellia or Tatooine?
	stopConversation = "false",
	options = {
		{"@conversation/rebel_broker:s_63cd6ccb", "naboo__14"}, -- Naboo.
		{"@conversation/rebel_broker:s_d15ec255", "corellia__15"}, -- Corellia.
		{"@conversation/rebel_broker:s_6491bb19", "tatooine__16"}, -- Tatooine.
	}
}
j_pai_brek_convo_template:addScreen(im_not_interested);

naboo__4 = ConvoScreen:new {
	id = "naboo__4",
	leftDialog = "@conversation/rebel_broker:s_3714bdfe", -- Now that's quite a dangerous assignment! We have managed to install an Alliance Trainer droid in the city of Moenia. The Empire is quite strong in the Naboo system, but Moenia belongs to Borvo the Hutt... and he's indifferent to the Rebellion - so long as we stay out of his way.
	stopConversation = "false",
	options = {
		{"@conversation/rebel_broker:s_159911f5", "tell_me_more_12"}, -- Tell me more.
		{"@conversation/rebel_broker:s_70f18874", "im_not_interested_13"}, -- I'm not interested in that.
	}
}
j_pai_brek_convo_template:addScreen(naboo__4);

corellia__5 = ConvoScreen:new {
	id = "corellia__5",
	leftDialog = "@conversation/rebel_broker:s_98a75031", -- Corellia's official stance is to remain neutral in the war against the Empire, but that has made it a useful place for us to marshal our forces.
	stopConversation = "false",
	options = {
		{"@conversation/rebel_broker:s_159911f5", "tell_me_more_12"}, -- Tell me more.
		{"@conversation/rebel_broker:s_70f18874", "im_not_interested_13"}, -- I'm not interested in that.
	}
}
j_pai_brek_convo_template:addScreen(corellia__5);

tatooine__6 = ConvoScreen:new {
	id = "tatooine__6",
	leftDialog = "@conversation/rebel_broker:s_80d99409", -- Tatooine is a backwater world far removed from most of the action. It seems the criminals and pirates give us as much trouble there as the Empire. Still, it's an important assignment as the remote location allows us to gather resources and supplies without constant harassment from the Empire.
	stopConversation = "false",
	options = {
		{"@conversation/rebel_broker:s_159911f5", "tell_me_more_12"}, -- Tell me more.
		{"@conversation/rebel_broker:s_70f18874", "im_not_interested_13"}, -- I'm not interested in that.
	}
}
j_pai_brek_convo_template:addScreen(tatooine__6);

tell_me_more_7 = ConvoScreen:new {
	id = "tell_me_more_7",
	leftDialog = "@conversation/rebel_broker:s_31bc521f", -- Then let me add this location to your datapad. We have an operative stationed in a 'safe house' here in Tyrena... in the slums not far from here.
	stopConversation = "true",
	options = {
	}
}
j_pai_brek_convo_template:addScreen(tell_me_more_7);

im_not_interested_8 = ConvoScreen:new {
	id = "im_not_interested_8",
	leftDialog = "@conversation/rebel_broker:s_18dad60e", -- What about Naboo or Tatooine then?
	stopConversation = "false",
	options = {
		{"@conversation/rebel_broker:s_63cd6ccb", "naboo__14"}, -- Naboo.
		{"@conversation/rebel_broker:s_d15ec255", "corellia__15"}, -- Corellia.
		{"@conversation/rebel_broker:s_6491bb19", "tatooine__16"}, -- Tatooine.
	}
}
j_pai_brek_convo_template:addScreen(im_not_interested_8);

naboo__9 = ConvoScreen:new {
	id = "naboo__9",
	leftDialog = "@conversation/rebel_broker:s_3714bdfe", -- Now that's quite a dangerous assignment! We have managed to install an Alliance Trainer droid in the city of Moenia. The Empire is quite strong in the Naboo system, but Moenia belongs to Borvo the Hutt... and he's indifferent to the Rebellion - so long as we stay out of his way.
	stopConversation = "false",
	options = {
		{"@conversation/rebel_broker:s_159911f5", "tell_me_more_12"}, -- Tell me more.
		{"@conversation/rebel_broker:s_70f18874", "im_not_interested_13"}, -- I'm not interested in that.
	}
}
j_pai_brek_convo_template:addScreen(naboo__9);

corellia__10 = ConvoScreen:new {
	id = "corellia__10",
	leftDialog = "@conversation/rebel_broker:s_98a75031", -- Corellia's official stance is to remain neutral in the war against the Empire, but that has made it a useful place for us to marshal our forces.
	stopConversation = "false",
	options = {
		{"@conversation/rebel_broker:s_159911f5", "tell_me_more_12"}, -- Tell me more.
		{"@conversation/rebel_broker:s_70f18874", "im_not_interested_13"}, -- I'm not interested in that.
	}
}
j_pai_brek_convo_template:addScreen(corellia__10);

tatooine__11 = ConvoScreen:new {
	id = "tatooine__11",
	leftDialog = "@conversation/rebel_broker:s_80d99409", -- Tatooine is a backwater world far removed from most of the action. It seems the criminals and pirates give us as much trouble there as the Empire. Still, it's an important assignment as the remote location allows us to gather resources and supplies without constant harassment from the Empire.
	stopConversation = "false",
	options = {
		{"@conversation/rebel_broker:s_159911f5", "tell_me_more_12"}, -- Tell me more.
		{"@conversation/rebel_broker:s_70f18874", "im_not_interested_13"}, -- I'm not interested in that.
	}
}
j_pai_brek_convo_template:addScreen(tatooine__11);

tell_me_more_12 = ConvoScreen:new {
	id = "tell_me_more_12",
	leftDialog = "@conversation/rebel_broker:s_43cd3e42", -- Here, I'll add the location of our Tatooine contact to your datapad. Whatever you do, don't allow that to fall into Imperial hands! This will take you to the Mos Espa cantina. Speak with Commander Da'la Socuna.
	stopConversation = "true",
	options = {
	}
}
j_pai_brek_convo_template:addScreen(tell_me_more_12);

im_not_interested_13 = ConvoScreen:new {
	id = "im_not_interested_13",
	leftDialog = "@conversation/rebel_broker:s_bbc28ec8", -- Want to be a little closer to the action, huh? I'd recommend Corellia or Naboo, in that case.
	stopConversation = "false",
	options = {
		{"@conversation/rebel_broker:s_63cd6ccb", "naboo__14"}, -- Naboo.
		{"@conversation/rebel_broker:s_d15ec255", "corellia__15"}, -- Corellia.
		{"@conversation/rebel_broker:s_6491bb19", "tatooine__16"}, -- Tatooine.
	}
}
j_pai_brek_convo_template:addScreen(im_not_interested_13);

naboo__14 = ConvoScreen:new {
	id = "naboo__14",
	leftDialog = "@conversation/rebel_broker:s_3714bdfe", -- Now that's quite a dangerous assignment! We have managed to install an Alliance Trainer droid in the city of Moenia. The Empire is quite strong in the Naboo system, but Moenia belongs to Borvo the Hutt... and he's indifferent to the Rebellion - so long as we stay out of his way.
	stopConversation = "false",
	options = {
		{"@conversation/rebel_broker:s_159911f5", "tell_me_more_12"}, -- Tell me more.
		{"@conversation/rebel_broker:s_70f18874", "im_not_interested_13"}, -- I'm not interested in that.
	}
}
j_pai_brek_convo_template:addScreen(naboo__14);

corellia__15 = ConvoScreen:new {
	id = "corellia__15",
	leftDialog = "@conversation/rebel_broker:s_98a75031", -- Corellia's official stance is to remain neutral in the war against the Empire, but that has made it a useful place for us to marshal our forces.
	stopConversation = "false",
	options = {
		{"@conversation/rebel_broker:s_159911f5", "tell_me_more_12"}, -- Tell me more.
		{"@conversation/rebel_broker:s_70f18874", "im_not_interested_13"}, -- I'm not interested in that.
	}
}
j_pai_brek_convo_template:addScreen(corellia__15);

tatooine__16 = ConvoScreen:new {
	id = "tatooine__16",
	leftDialog = "@conversation/rebel_broker:s_80d99409", -- Tatooine is a backwater world far removed from most of the action. It seems the criminals and pirates give us as much trouble there as the Empire. Still, it's an important assignment as the remote location allows us to gather resources and supplies without constant harassment from the Empire.
	stopConversation = "false",
	options = {
		{"@conversation/rebel_broker:s_159911f5", "tell_me_more_12"}, -- Tell me more.
		{"@conversation/rebel_broker:s_70f18874", "im_not_interested_13"}, -- I'm not interested in that.
	}
}
j_pai_brek_convo_template:addScreen(tatooine__16);

addConversationTemplate("j_pai_brek_convo_template", j_pai_brek_convo_template);
