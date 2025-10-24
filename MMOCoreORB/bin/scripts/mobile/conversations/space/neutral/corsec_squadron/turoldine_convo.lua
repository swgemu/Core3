turoldine_convo_template = ConvoTemplate:new {
	initialScreen = "",
	templateType = "Lua",
	luaClassHandler = "turoldineConvoHandler",
	screens = {}
}

not_pilot = ConvoScreen:new {
	id = "not_pilot",
	leftDialog = "@conversation/corellia_privateer_tier4:s_1516ae92", -- I think you need to keep moving.
	animation = "wave_on_dismissing",
	playerAnimation = "",
	stopConversation = "false",
	options = {
		{"@conversation/corellia_privateer_tier4:s_a85a848e", "beat_it"}, --  You talking to me?
		{"@conversation/corellia_privateer_tier4:s_81b27773", "see_you"}, --  Oops. Sorry.
	}
}
turoldine_convo_template:addScreen(not_pilot);

pilot_not_corsec = ConvoScreen:new {
	id = "pilot_not_corsec",
	leftDialog = "@conversation/corellia_privateer_tier4:s_32f5282f", -- What brings you to the CorSec, pilot? You'd better not be wasting my time.
	animation = "rub_chin_thoughtful",
	playerAnimation = "",
	stopConversation = "false",
	options = {
		{"@conversation/corellia_privateer_tier4:s_c1ff5062", "here_for_work"}, --  I'm looking for a mission. Do you have any?
	}
}
turoldine_convo_template:addScreen(pilot_not_corsec);

not_proper_tier = ConvoScreen:new {
	id = "not_proper_tier",
	leftDialog = "@conversation/corellia_privateer_tier4:s_df5cb938", -- Commander Ramna's looking for you.
	animation = "rub_chin_thoughtful",
	playerAnimation = "",
	stopConversation = "false",
	options = {
		{"@conversation/corellia_privateer_tier4:s_847048c5", "you_do_it"}, --  Tell her I'm on my way.
		{"@conversation/corellia_privateer_tier4:s_3f570be0", "dont_forget_me"}, --  Oh that's right. I forgot.
	}
}
turoldine_convo_template:addScreen(not_proper_tier);

on_mission = ConvoScreen:new {
	id = "on_mission",
	leftDialog = "@conversation/corellia_privateer_tier4:s_d5f02c52", -- Better get to work.
	animation = "rub_chin_thoughtful",
	playerAnimation = "",
	stopConversation = "false",
	options = {
		{"@conversation/corellia_privateer_tier4:s_a12be3e7", "says_me"}, --  Says who?
		{"@conversation/corellia_privateer_tier4:s_80d8485c", "be_safe"}, --  I'm on it.
	}
}
turoldine_convo_template:addScreen(on_mission);

says_me = ConvoScreen:new {
	id = "says_me",
	leftDialog = "@conversation/corellia_privateer_tier4:s_1683f2af", -- Says me.
	animation = "point_to_self",
	playerAnimation = "",
	stopConversation = "false",
	options = {
		{"@conversation/corellia_privateer_tier4:s_a8aac5df", "not_arguing"}, --  That's quite an argument.
	}
}
turoldine_convo_template:addScreen(says_me);

-- Mission 1

first_mission = ConvoScreen:new {
	id = "first_mission",
	leftDialog = "@conversation/corellia_privateer_tier4:s_eb363f92", -- Time is wasting, %TU. Ready for your next assignment?
	animation = "",
	playerAnimation = "",
	stopConversation = "false",
	options = {
		{"@conversation/corellia_privateer_tier4:s_5c522568", "first_mission_desc"}, --  Yes, of course.
	}
}
turoldine_convo_template:addScreen(first_mission);

first_mission_desc = ConvoScreen:new {
	id = "first_mission_desc",
	leftDialog = "@conversation/corellia_privateer_tier4:s_dffc2e23", -- Now let's get you up to speed. Things have been going well against the Black Suns so far.
	animation = "",
	playerAnimation = "",
	stopConversation = "false",
	options = {
		{"@conversation/corellia_privateer_tier4:s_cc4b75d1", "ramna_distinguished"}, --  Not bad.
		{"@conversation/corellia_privateer_tier4:s_42836ce6", "neither_do_i"}, --  They're tough. I don't think those guys have exactly packed their bags and left.
	}
}
turoldine_convo_template:addScreen(first_mission_desc);

ramna_distinguished = ConvoScreen:new {
	id = "ramna_distinguished",
	leftDialog = "@conversation/corellia_privateer_tier4:s_be919187", -- Commander Ramna tells me you distinguished yourself.
	animation = "rub_chin_thoughtful",
	playerAnimation = "",
	stopConversation = "false",
	options = {
		{"@conversation/corellia_privateer_tier4:s_497bdf7a", "work_to_do"}, --  I did my best; that's all.
	}
}
turoldine_convo_template:addScreen(ramna_distinguished);

work_to_do = ConvoScreen:new {
	id = "work_to_do",
	leftDialog = "@conversation/corellia_privateer_tier4:s_8f8ce354", -- Well you sent those pirates a message. Now we'll just have to wait and see what kind of message they send back. In the meantime, there's work to do.
	animation = "survey",
	playerAnimation = "",
	stopConversation = "false",
	options = {
		{"@conversation/corellia_privateer_tier4:s_d55f2579", "patrol_dant_space"}, --  I'm ready to go.
	}
}
turoldine_convo_template:addScreen(work_to_do);

patrol_dant_space = ConvoScreen:new {
	id = "patrol_dant_space",
	leftDialog = "@conversation/corellia_privateer_tier4:s_1faa7ff3", -- I want to know what's going on out there. But I don't want to actively pursue the Black Suns - yet. They'll come to us soon enough. In the meantime, I want you to patrol Dantooine space.
	animation = "rub_chin_thoughtful",
	playerAnimation = "",
	stopConversation = "false",
	options = {
		{"@conversation/corellia_privateer_tier4:s_fbe69616", "easiest_unless"}, -- That's it? That's all I have to do?
	}
}
turoldine_convo_template:addScreen(patrol_dant_space);

neither_do_i = ConvoScreen:new {
	id = "neither_do_i",
	leftDialog = "@conversation/corellia_privateer_tier4:s_bf7ca96d", -- Neither do I. But until they make a move, it's business as usual.
	animation = "shake_head_no",
	playerAnimation = "",
	stopConversation = "false",
	options = {
		{"@conversation/corellia_privateer_tier4:s_93c94bdf", "just_a_patrol"}, -- Sounds like you've got work for me.
	}
}
turoldine_convo_template:addScreen(neither_do_i);

just_a_patrol = ConvoScreen:new {
	id = "just_a_patrol",
	leftDialog = "@conversation/corellia_privateer_tier4:s_b9f936b3", -- Always. But there's no heavy lifting involved. I want you to just take a patrol.
	animation = "nod_head_once",
	playerAnimation = "",
	stopConversation = "false",
	options = {
		{"@conversation/corellia_privateer_tier4:s_fbe69616", "easiest_unless"}, -- That's it? That's all I have to do?
	}
}
turoldine_convo_template:addScreen(just_a_patrol);

easiest_unless = ConvoScreen:new {
	id = "easiest_unless",
	leftDialog = "@conversation/corellia_privateer_tier4:s_1faa7ff3", -- It'll be the easiest assignment you've ever had - unless those Black Suns show up. And if they DO show up, I'll need you out there. How does that sound to you?
	animation = "shrug_shoulders",
	playerAnimation = "",
	stopConversation = "false",
	options = {
		{"@conversation/corellia_privateer_tier4:s_d0fd857b", "accept_first_mission"}, -- I'll take it.
	}
}
turoldine_convo_template:addScreen(easiest_unless);

accept_first_mission = ConvoScreen:new {
	id = "accept_first_mission",
	leftDialog = "@conversation/corellia_privateer_tier4:s_96047adb", -- Watch yourself up there.
	animation = "salute1",
	playerAnimation = "salute1",
	stopConversation = "true",
	options = {}
}
turoldine_convo_template:addScreen(accept_first_mission);





















-- Mission 2

second_mission = ConvoScreen:new {
	id = "second_mission",
	leftDialog = "@conversation/corellia_privateer_tier4:s_eb363f92", -- Time is wasting, %TU. Ready for your next assignment?
	animation = "point_to_self",
	playerAnimation = "",
	stopConversation = "false",
	options = {
		{"@conversation/corellia_privateer_tier4:s_5c522568", ""}, --  Yes, of course.
	}
}
turoldine_convo_template:addScreen(second_mission);









-- Mission 3

third_mission = ConvoScreen:new {
	id = "third_mission",
	leftDialog = "@conversation/corellia_privateer_tier4:s_eb363f92", -- Time is wasting, %TU. Ready for your next assignment?
	animation = "point_to_self",
	playerAnimation = "",
	stopConversation = "false",
	options = {
		{"@conversation/corellia_privateer_tier4:s_5c522568", ""}, --  Yes, of course.
	}
}
turoldine_convo_template:addScreen(third_mission);







-- Mission 4

fourth_mission = ConvoScreen:new {
	id = "fourth_mission",
	leftDialog = "@conversation/corellia_privateer_tier4:s_eb363f92", -- Time is wasting, %TU. Ready for your next assignment?
	animation = "point_to_self",
	playerAnimation = "",
	stopConversation = "false",
	options = {
		{"@conversation/corellia_privateer_tier4:s_5c522568", ""}, --  Yes, of course.
	}
}
turoldine_convo_template:addScreen(fourth_mission);















--[[

	Duty Missions

]]

here_for_work = ConvoScreen:new {
	id = "here_for_work",
	leftDialog = "@conversation/corellia_privateer_tier4:s_3d991214", -- There's always work to do here at CorSec. I have a few elective duty missions. Take a look and let me give you a briefing.
	animation = "nod_head_once",
	stopConversation = "false",
	options = {
		{"@conversation/corellia_privateer_tier4:s_a490d2c6", "hidden_daggers"}, -- Alright.
	}
}
turoldine_convo_template:addScreen(here_for_work)

hidden_daggers = ConvoScreen:new {
	id = "hidden_daggers",
	leftDialog = "@conversation/corellia_privateer_tier4:s_18f260b3", -- The Hidden Daggers are still testing us. I'm always looking for pilots willing to fly sorties against their ships.
	animation = "explain",
	stopConversation = "false",
	options = {
		{"@conversation/corellia_privateer_tier4:s_6ce4e96f", "blacksun_transport"}, -- Right.
	}
}
turoldine_convo_template:addScreen(hidden_daggers)

blacksun_transport = ConvoScreen:new {
	id = "blacksun_transport",
	leftDialog = "@conversation/corellia_privateer_tier4:s_fb7fd141", -- We've also got a Black Sun Transport up there. I could use your help in bringing it back to base. It may be carrying some useful information..
	animation = "explain",
	playerAnimation = "nod_head_once",
	stopConversation = "false",
	options = {
		{"@conversation/corellia_privateer_tier4:s_2de6d84d", "mining_escort"}, -- Mmm.
	}
}
turoldine_convo_template:addScreen(blacksun_transport)

mining_escort = ConvoScreen:new {
	id = "mining_escort",
	leftDialog = "@conversation/corellia_privateer_tier4:s_fee63808", -- Then, of course, you've got your basic civic-duty assignments. A mining transport is moving through Dathomir space. They need an escort; the Daggers are always interested in transports.
	animation = "explain",
	playerAnimation = "nod_head_once",
	stopConversation = "false",
	options = {
		{"@conversation/corellia_privateer_tier4:s_362a48e0", "duty_missions"}, -- Anything else?
	}
}
turoldine_convo_template:addScreen(mining_escort)

duty_missions = ConvoScreen:new {
	id = "duty_missions",
	leftDialog = "@conversation/corellia_privateer_tier4:s_982fd0ec", -- Last thing - I've just received a report that Hutt pirates are attacking a civilian mining craft. Those miners won't make it out alive without us.
	animation = "explain",
	playerAnimation = "nod_head_once",
	stopConversation = "false",
	options = {
		{"@conversation/corellia_privateer_tier4:s_5c48dd80", ""}, -- Let me take a shot at those Hidden Daggers.
		{"@conversation/corellia_privateer_tier4:s_5d4c8449", ""}, -- I think I can help that mining transport.
		{"@conversation/corellia_privateer_tier4:s_a6caaf6b", ""}, -- Is that Black Sun Transport still up there?
		{"@conversation/corellia_privateer_tier4:s_7aa801dc", ""}, -- Let me get that mining craft. The last thing we need is another pirate clan, moving in.
		{"@conversation/corellia_privateer_tier4:s_bb3bc739", ""}, -- I could use a refresher.
	}
}
turoldine_convo_template:addScreen(duty_missions)

accept_duty1 = ConvoScreen:new {
	id = "accept_duty1",
	leftDialog = "@conversation/corellia_privateer_tier4:s_5ace999c", -- Don't have to ask me twice. Get going.
	animation = "",
	playerAnimation = "",
	stopConversation = "true",
	options = {}
}
rikkh_convo_template:addScreen(accept_duty1)

accept_duty2 = ConvoScreen:new {
	id = "accept_duty2",
	leftDialog = "@conversation/corellia_privateer_tier4:", --
	animation = "",
	playerAnimation = "",
	stopConversation = "true",
	options = {}
}
rikkh_convo_template:addScreen(accept_duty2)

accept_duty3 = ConvoScreen:new {
	id = "accept_duty3",
	leftDialog = "@conversation/corellia_privateer_tier4:", --
	animation = "",
	playerAnimation = "",
	stopConversation = "true",
	options = {}
}
rikkh_convo_template:addScreen(accept_duty3)

accept_duty4 = ConvoScreen:new {
	id = "accept_duty4",
	leftDialog = "@conversation/corellia_privateer_tier4:", --
	animation = "",
	playerAnimation = "",
	stopConversation = "true",
	options = {}
}
rikkh_convo_template:addScreen(accept_duty4)






--[[

	Conversation Enders

]]

beat_it = ConvoScreen:new {
	id = "beat_it",
	leftDialog = "@conversation/corellia_privateer_tier4:s_9f15ecc0", -- I'll do more than talk, if you give me that kind of attitude. Beat it.
	animation = "wave_finger_warning",
	playerAnimation = "point_to_self",
	stopConversation = "true",
	options = {}
}
turoldine_convo_template:addScreen(beat_it);

see_you = ConvoScreen:new {
	id = "see_you",
	leftDialog = "@conversation/corellia_privateer_tier4:s_f0f1c03e", -- See you around.
	animation = "wave_on_dismissing",
	playerAnimation = "",
	stopConversation = "true",
	options = {}
}
turoldine_convo_template:addScreen(see_you);

you_do_it = ConvoScreen:new {
	id = "you_do_it",
	leftDialog = "@conversation/corellia_privateer_tier4:s_14d7da55", -- Why don't you tell her yourself?
	animation = "dismiss",
	playerAnimation = "",
	stopConversation = "true",
	options = {}
}
turoldine_convo_template:addScreen(you_do_it);

dont_forget_me = ConvoScreen:new {
	id = "dont_forget_me",
	leftDialog = "@conversation/corellia_privateer_tier4:s_c56e5a39", -- I hope you don't forget ME when we start working together.
	animation = "dismiss",
	playerAnimation = "",
	stopConversation = "true",
	options = {}
}
turoldine_convo_template:addScreen(dont_forget_me);

not_arguing = ConvoScreen:new {
	id = "not_arguing",
	leftDialog = "@conversation/corellia_privateer_tier4:s_734b72d7", -- I'm not here to argue with you. I'm here to get you to do your job. So do it.
	animation = "wave_on_dismissing",
	playerAnimation = "rub_chin_thoughtful",
	stopConversation = "true",
	options = {}
}
turoldine_convo_template:addScreen(not_arguing);

be_safe = ConvoScreen:new {
	id = "be_safe",
	leftDialog = "@conversation/corellia_privateer_tier4:s_7c181033", -- Be safe.
	animation = "wave_on_dismissing",
	playerAnimation = "",
	stopConversation = "true",
	options = {}
}
turoldine_convo_template:addScreen(be_safe);








addConversationTemplate("turoldine_convo_template", turoldine_convo_template);