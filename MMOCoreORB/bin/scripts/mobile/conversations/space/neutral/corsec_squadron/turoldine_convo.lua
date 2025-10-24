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

ready_train_pilot = ConvoScreen:new {
	id = "ready_train_pilot",
	leftDialog = "@conversation/corellia_privateer_trainer_2:s_db8b8333", -- You're a good pilot. You're only going to get better - as long as you keep studying.
	animation = "",
	stopConversation = "false",
	options = {
		-- Added via handler
	}
}
turoldine_convo_template:addScreen(ready_train_pilot);

initial_briefing = ConvoScreen:new {
	id = "initial_briefing",
	leftDialog = "@conversation/corellia_privateer_tier4:s_be78b6f8", -- Ah, %TU, good to see you. I wish I had time to give you a warmer welcome, but I'm afraid you have to get started right away. Allow me to give you a briefing.
	animation = "",
	playerAnimation = "",
	stopConversation = "false",
	options = {
		{"@conversation/corellia_privateer_tier4:s_5c522568", "hidden_daggers"}, --  Yes, of course.
	}
}
turoldine_convo_template:addScreen(initial_briefing);

-- Mission 1

initial_train_fighters = ConvoScreen:new {
	id = "initial_train_fighters",
	leftDialog = "@conversation/corellia_privateer_tier4:s_dffc2e23", -- Now let's get you up to speed. Things have been going well against the Black Suns so far.
	animation = "",
	stopConversation = "false",
	options = {
		{"@conversation/corellia_privateer_tier4:s_cc4b75d1", "ramna_distinguished"}, --  Not bad.
		{"@conversation/corellia_privateer_tier4:s_42836ce6", "neither_do_i"}, --  They're tough. I don't think those guys have exactly packed their bags and left.
	}
}
turoldine_convo_template:addScreen(initial_train_fighters);

initial_train_components = ConvoScreen:new {
	id = "initial_train_components",
	leftDialog = "@conversation/corellia_privateer_tier4:s_dffc2e23", -- Now let's get you up to speed. Things have been going well against the Black Suns so far.
	animation = "",
	stopConversation = "false",
	options = {
		{"@conversation/corellia_privateer_tier4:s_cc4b75d1", "ramna_distinguished"}, --  Not bad.
		{"@conversation/corellia_privateer_tier4:s_42836ce6", "neither_do_i"}, --  They're tough. I don't think those guys have exactly packed their bags and left.
	}
}
turoldine_convo_template:addScreen(initial_train_components)

initial_train_techniques = ConvoScreen:new {
	id = "initial_train_techniques",
	leftDialog = "@conversation/corellia_privateer_tier4:s_dffc2e23", -- Now let's get you up to speed. Things have been going well against the Black Suns so far.
	animation = "",
	stopConversation = "false",
	options = {
		{"@conversation/corellia_privateer_tier4:s_cc4b75d1", "ramna_distinguished"}, --  Not bad.
		{"@conversation/corellia_privateer_tier4:s_42836ce6", "neither_do_i"}, --  They're tough. I don't think those guys have exactly packed their bags and left.
	}
}
turoldine_convo_template:addScreen(initial_train_techniques)

initial_train_algorithms = ConvoScreen:new {
	id = "initial_train_algorithms",
	leftDialog = "@conversation/corellia_privateer_tier4:s_dffc2e23", -- Now let's get you up to speed. Things have been going well against the Black Suns so far.
	animation = "",
	stopConversation = "false",
	options = {
		{"@conversation/corellia_privateer_tier4:s_cc4b75d1", "ramna_distinguished"}, --  Not bad.
		{"@conversation/corellia_privateer_tier4:s_42836ce6", "neither_do_i"}, --  They're tough. I don't think those guys have exactly packed their bags and left.
	}
}
turoldine_convo_template:addScreen(initial_train_algorithms)

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

mission2_train_fighters = ConvoScreen:new {
	id = "mission2_train_fighters",
	leftDialog = "@conversation/corellia_privateer_tier4:s_dffc2e23", -- Now let's get you up to speed. Things have been going well against the Black Suns so far.
	animation = "",
	stopConversation = "false",
	options = {
		{"@conversation/corellia_privateer_tier4:s_cc4b75d1", ""}, --  Not bad.
		{"@conversation/corellia_privateer_tier4:s_42836ce6", ""}, --  They're tough. I don't think those guys have exactly packed their bags and left.
	}
}
turoldine_convo_template:addScreen(mission2_train_fighters);

mission2_train_components = ConvoScreen:new {
	id = "mission2_train_components",
	leftDialog = "@conversation/corellia_privateer_tier4:s_dffc2e23", -- Now let's get you up to speed. Things have been going well against the Black Suns so far.
	animation = "",
	stopConversation = "false",
	options = {
		{"@conversation/corellia_privateer_tier4:s_cc4b75d1", ""}, --  Not bad.
		{"@conversation/corellia_privateer_tier4:s_42836ce6", ""}, --  They're tough. I don't think those guys have exactly packed their bags and left.
	}
}
turoldine_convo_template:addScreen(mission2_train_components)

mission2_train_techniques = ConvoScreen:new {
	id = "mission2_train_techniques",
	leftDialog = "@conversation/corellia_privateer_tier4:s_dffc2e23", -- Now let's get you up to speed. Things have been going well against the Black Suns so far.
	animation = "",
	stopConversation = "false",
	options = {
		{"@conversation/corellia_privateer_tier4:s_cc4b75d1", ""}, --  Not bad.
		{"@conversation/corellia_privateer_tier4:s_42836ce6", ""}, --  They're tough. I don't think those guys have exactly packed their bags and left.
	}
}
turoldine_convo_template:addScreen(mission2_train_techniques)

mission2_train_algorithms = ConvoScreen:new {
	id = "mission2_train_algorithms",
	leftDialog = "@conversation/corellia_privateer_tier4:s_dffc2e23", -- Now let's get you up to speed. Things have been going well against the Black Suns so far.
	animation = "",
	stopConversation = "false",
	options = {
		{"@conversation/corellia_privateer_tier4:s_cc4b75d1", ""}, --  Not bad.
		{"@conversation/corellia_privateer_tier4:s_42836ce6", ""}, --  They're tough. I don't think those guys have exactly packed their bags and left.
	}
}
turoldine_convo_template:addScreen(mission2_train_algorithms)

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

mission3_train_fighters = ConvoScreen:new {
	id = "mission3_train_fighters",
	leftDialog = "@conversation/corellia_privateer_tier4:s_dffc2e23", -- Now let's get you up to speed. Things have been going well against the Black Suns so far.
	animation = "",
	stopConversation = "false",
	options = {
		{"@conversation/corellia_privateer_tier4:s_cc4b75d1", ""}, --  Not bad.
		{"@conversation/corellia_privateer_tier4:s_42836ce6", ""}, --  They're tough. I don't think those guys have exactly packed their bags and left.
	}
}
turoldine_convo_template:addScreen(mission3_train_fighters);

mission3_train_components = ConvoScreen:new {
	id = "mission3_train_components",
	leftDialog = "@conversation/corellia_privateer_tier4:s_dffc2e23", -- Now let's get you up to speed. Things have been going well against the Black Suns so far.
	animation = "",
	stopConversation = "false",
	options = {
		{"@conversation/corellia_privateer_tier4:s_cc4b75d1", ""}, --  Not bad.
		{"@conversation/corellia_privateer_tier4:s_42836ce6", ""}, --  They're tough. I don't think those guys have exactly packed their bags and left.
	}
}
turoldine_convo_template:addScreen(mission3_train_components)

mission3_train_techniques = ConvoScreen:new {
	id = "mission3_train_techniques",
	leftDialog = "@conversation/corellia_privateer_tier4:s_dffc2e23", -- Now let's get you up to speed. Things have been going well against the Black Suns so far.
	animation = "",
	stopConversation = "false",
	options = {
		{"@conversation/corellia_privateer_tier4:s_cc4b75d1", ""}, --  Not bad.
		{"@conversation/corellia_privateer_tier4:s_42836ce6", ""}, --  They're tough. I don't think those guys have exactly packed their bags and left.
	}
}
turoldine_convo_template:addScreen(mission3_train_techniques)

mission3_train_algorithms = ConvoScreen:new {
	id = "mission3_train_algorithms",
	leftDialog = "@conversation/corellia_privateer_tier4:s_dffc2e23", -- Now let's get you up to speed. Things have been going well against the Black Suns so far.
	animation = "",
	stopConversation = "false",
	options = {
		{"@conversation/corellia_privateer_tier4:s_cc4b75d1", ""}, --  Not bad.
		{"@conversation/corellia_privateer_tier4:s_42836ce6", ""}, --  They're tough. I don't think those guys have exactly packed their bags and left.
	}
}
turoldine_convo_template:addScreen(mission3_train_algorithms)

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

final_train_fighters = ConvoScreen:new {
	id = "final_train_fighters",
	leftDialog = "@conversation/corellia_privateer_tier4:s_dffc2e23", -- Now let's get you up to speed. Things have been going well against the Black Suns so far.
	animation = "",
	stopConversation = "false",
	options = {
		{"@conversation/corellia_privateer_tier4:s_cc4b75d1", ""}, --  Not bad.
		{"@conversation/corellia_privateer_tier4:s_42836ce6", ""}, --  They're tough. I don't think those guys have exactly packed their bags and left.
	}
}
turoldine_convo_template:addScreen(final_train_fighters);

final_train_components = ConvoScreen:new {
	id = "final_train_components",
	leftDialog = "@conversation/corellia_privateer_tier4:s_dffc2e23", -- Now let's get you up to speed. Things have been going well against the Black Suns so far.
	animation = "",
	stopConversation = "false",
	options = {
		{"@conversation/corellia_privateer_tier4:s_cc4b75d1", ""}, --  Not bad.
		{"@conversation/corellia_privateer_tier4:s_42836ce6", ""}, --  They're tough. I don't think those guys have exactly packed their bags and left.
	}
}
turoldine_convo_template:addScreen(final_train_components)

final_train_techniques = ConvoScreen:new {
	id = "final_train_techniques",
	leftDialog = "@conversation/corellia_privateer_tier4:s_dffc2e23", -- Now let's get you up to speed. Things have been going well against the Black Suns so far.
	animation = "",
	stopConversation = "false",
	options = {
		{"@conversation/corellia_privateer_tier4:s_cc4b75d1", ""}, --  Not bad.
		{"@conversation/corellia_privateer_tier4:s_42836ce6", ""}, --  They're tough. I don't think those guys have exactly packed their bags and left.
	}
}
turoldine_convo_template:addScreen(final_train_techniques)

final_train_algorithms = ConvoScreen:new {
	id = "final_train_algorithms",
	leftDialog = "@conversation/corellia_privateer_tier4:s_dffc2e23", -- Now let's get you up to speed. Things have been going well against the Black Suns so far.
	animation = "",
	stopConversation = "false",
	options = {
		{"@conversation/corellia_privateer_tier4:s_cc4b75d1", ""}, --  Not bad.
		{"@conversation/corellia_privateer_tier4:s_42836ce6", ""}, --  They're tough. I don't think those guys have exactly packed their bags and left.
	}
}
turoldine_convo_template:addScreen(final_train_algorithms)

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




-- Master Mission

master_mission = ConvoScreen:new {
	id = "master_mission",
	leftDialog = "@conversation/corellia_privateer_tier4:s_631ae8ac", -- It's time for you to make a decision. I have received two requests for CorSec's best pilot. And as far as I'm concerned, that's you. It's strange that I received both of these within a few hours of each other. Usually when that happens, it means that the two are related. But apparently not this time.
	animation = "",
	playerAnimation = "",
	stopConversation = "false",
	options = {
		{"@conversation/corellia_privateer_tier4:s_f50bf532", "odd_requests"}, -- Who sent them?
	}
}
turoldine_convo_template:addScreen(master_mission);

odd_requests = ConvoScreen:new {
	id = "odd_requests",
	leftDialog = "@conversation/corellia_privateer_tier4:s_fbff7add", -- The request came in from the Alliance - an Admiral Willham Burke sent it. And oddly enough, the order came in from Imperial High Command. It is signed Grand Admiral Nial Declann. It is very rare that we have any communication with the Imperial Navy, much less a Grand Admiral.
	animation = "explain",
	playerAnimation = "",
	stopConversation = "false",
	options = {
		{"@conversation/corellia_privateer_tier4:s_66a2d521", "alliance_request"}, -- What can you tell me about the request from the Alliance?
		{"@conversation/corellia_privateer_tier4:s_cd2c7c7", "imperial_request"}, -- What does the order from the Empire say?
	}
}
turoldine_convo_template:addScreen(odd_requests);

alliance_request = ConvoScreen:new {
	id = "alliance_request",
	leftDialog = "@conversation/corellia_privateer_tier4:s_c13ffa70", -- It would seem that Admiral Burke is looking for pilots from the CorSec to assist the Alliance in a highly sensitive operation. Not surprisingly, he makes no mention of what that operation is to be. But he does mention that I should only send the best, which means that it is highly dangerous.
	animation = "rub_chin_thoughtful",
	playerAnimation = "",
	stopConversation = "false",
	options = {
		{"@conversation/corellia_privateer_tier4:s_392b269e", "alliance_ties"}, --  Why would the Alliance be asking for CorSec pilots?
	}
}
turoldine_convo_template:addScreen(alliance_request);

alliance_ties = ConvoScreen:new {
	id = "alliance_ties",
	leftDialog = "@conversation/corellia_privateer_tier4:s_6020d1e0", --  It's not something we talk about much, but the CorSec has pretty close ties to the Alliance. This isn't the first time that the Alliance has asked for help from our organization. Of course, the CorSec denies any knowledge of this and officially claims that any member caught helping the Alliance is a rogue agent.
	animation = "explain",
	playerAnimation = "",
	stopConversation = "false",
	options = {
		{"@conversation/corellia_privateer_tier4:s_cad40f33", "seek_out_burke"}, --  Where can I find Admiral Burke?
		{"@conversation/corellia_privateer_tier4:s_5812b51a", "imperial_request"}, --  What about that Imperial order?
	}
}
turoldine_convo_template:addScreen(alliance_ties);

seek_out_burke = ConvoScreen:new {
	id = "seek_out_burke",
	leftDialog = "@conversation/corellia_privateer_tier4:s_9b4653d9", -- It says that if we have any pilots who are interested they should seek out Admiral Burke in Doaba Guerfel on Corellia. Any support we can offer will be most appreciated.
	animation = "",
	playerAnimation = "",
	stopConversation = "false",
	options = {
		{"@conversation/corellia_privateer_tier4:s_62b7e5d1", "should_help_alliance"}, --  Do you think I should help the Alliance?
		{"@conversation/corellia_privateer_tier4:s_3a5c85dc", "imperial_request"}, --  Tell me more about the Imperial order.
	}
}
turoldine_convo_template:addScreen(seek_out_burke);

should_help_alliance = ConvoScreen:new {
	id = "should_help_alliance",
	leftDialog = "@conversation/corellia_privateer_tier4:s_89bbd3f9", -- I cannot tell you what you should do. All I can say is that your decision will not hurt your position in the Corsec in any way. This is strictly a volunteer assignment. But you could learn a lot from this guy. It's up to you. If you want to help the Alliance, go to Doaba Guerfel and speak to Admiral Willham Burke. Dismissed, pilot.
	animation = "explain",
	stopConversation = "true",
	options = {}
}
turoldine_convo_template:addScreen(should_help_alliance)

imperial_request = ConvoScreen:new {
	id = "imperial_request",
	leftDialog = "@conversation/corellia_privateer_tier4:s_6160d176", -- This is a request - and that's unusual. Usually, when they want something from us, they issue an order. I make it a point never to force any of my pilots to obey any order issued by the Empire, but we do try to make a good show of it. But this order was sent by a Grand Admiral of the Imperial fleet. I think if we ignore this one, we'll regret it later.
	animation = "rub_chin_thoughtful",
	playerAnimation = "",
	stopConversation = "false",
	options = {
		{"@conversation/corellia_privateer_tier4:s_7177c3f2", "whois_declann"}, -- Who is Grand Admiral Nial Declann?
	}
}
turoldine_convo_template:addScreen(imperial_request);

whois_declann = ConvoScreen:new {
	id = "whois_declann",
	leftDialog = "@conversation/corellia_privateer_tier4:s_c5f93f4", -- He is one of the most powerful men in the Imperial Navy. When he speaks, people listen. I have never seen a Grand Admiral issue an order to our corps before, so it must be something important.
	animation = "explain",
	playerAnimation = "",
	stopConversation = "false",
	options = {
		{"@conversation/corellia_privateer_tier4:s_d2a15608", "help_the_empire"}, -- So I have to go and help the Empire?
	}
}
turoldine_convo_template:addScreen(whois_declann);

help_the_empire = ConvoScreen:new {
	id = "help_the_empire",
	leftDialog = "@conversation/corellia_privateer_tier4:s_be7682ed", -- I won't force you. If you don't want to do it, I will tell them you're injured. Of course, if you do choose to obey the order, it will most certainly not reflect in any way on your career here at the CorSec.
	animation = "shrug_shoulders",
	playerAnimation = "",
	stopConversation = "false",
	options = {
		{"@conversation/corellia_privateer_tier4:s_62b7e5d1", "theed_naboo"}, -- Where does it say I have to go?
		{"@conversation/corellia_privateer_tier4:s_72be4afa", "alliance_request"}, -- Tell me about the Alliance's request.
	}
}
turoldine_convo_template:addScreen(help_the_empire);

theed_naboo = ConvoScreen:new {
	id = "theed_naboo",
	leftDialog = "@conversation/corellia_privateer_tier4:s_2eb9ea1f", -- Grand Admiral Nial Declann is stationed in Theed Palace on Naboo. Going to see him is not an entirely bad thing. Having a Grand Admiral's support for the CorSec would go a long way in ensuring that the Empire doesn't decide to move into our system. Also, I understand that there are many things that the Empire can teach a pilot such as yourself.
	animation = "",
	playerAnimation = "",
	stopConversation = "false",
	options = {
		{"@conversation/corellia_privateer_tier4:s_4e60c8d4", "decide_assist_empire"}, -- So should I obey the Empire?
		{"@conversation/corellia_privateer_tier4:s_55127f07", "alliance_request"}, -- Tell me more about the Alliance's request.
	}
}
turoldine_convo_template:addScreen(theed_naboo);

decide_assist_empire = ConvoScreen:new {
	id = "decide_assist_empire",
	leftDialog = "@conversation/corellia_privateer_tier4:s_6c2be16f", -- I cannot make that decision for you. Each of us must decide our own path. Be thankful for this choice, because not everyone in the galaxy has that luxury. If you decide that you want to help the Empire head to Theed Palace and report in to Admiral Declann. Good luck.
	animation = "explain",
	stopConversation = "true",
	options = {}
}
turoldine_convo_template:addScreen(decide_assist_empire);































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

here_for_work2 = ConvoScreen:new {
	id = "here_for_work2",
	leftDialog = "@conversation/corellia_privateer_tier4:s_1b5769c8", -- Just here for more work?  Sure you are.
	animation = "greet",
	stopConversation = "false",
	options = {
		{"@conversation/corellia_privateer_tier4:s_5c48dd80", "accept_duty1"}, -- Let me take a shot at those Hidden Daggers.
		{"@conversation/corellia_privateer_tier4:s_5d4c8449", "accept_duty2"}, -- I think I can help that mining transport.
		{"@conversation/corellia_privateer_tier4:s_a6caaf6b", "accept_duty3"}, -- Is that Black Sun Transport still up there?
		{"@conversation/corellia_privateer_tier4:s_7aa801dc", "accept_duty4"}, -- Let me get that mining craft. The last thing we need is another pirate clan, moving in.
		{"@conversation/corellia_privateer_tier4:s_bb3bc739", "hidden_daggers"}, -- I could use a refresher.
	}
}
turoldine_convo_template:addScreen(here_for_work2)

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
		{"@conversation/corellia_privateer_tier4:s_5c48dd80", "accept_duty1"}, -- Let me take a shot at those Hidden Daggers.
		{"@conversation/corellia_privateer_tier4:s_5d4c8449", "accept_duty2"}, -- I think I can help that mining transport.
		{"@conversation/corellia_privateer_tier4:s_a6caaf6b", "accept_duty3"}, -- Is that Black Sun Transport still up there?
		{"@conversation/corellia_privateer_tier4:s_7aa801dc", "accept_duty4"}, -- Let me get that mining craft. The last thing we need is another pirate clan, moving in.
		{"@conversation/corellia_privateer_tier4:s_bb3bc739", "hidden_daggers"}, -- I could use a refresher.
	}
}
turoldine_convo_template:addScreen(duty_missions)

accept_duty1 = ConvoScreen:new {
	id = "accept_duty1",
	leftDialog = "@conversation/corellia_privateer_tier4:s_5ace999c", -- Don't have to ask me twice. Get going.
	animation = "dismiss",
	playerAnimation = "",
	stopConversation = "true",
	options = {}
}
turoldine_convo_template:addScreen(accept_duty1)

accept_duty2 = ConvoScreen:new {
	id = "accept_duty2",
	leftDialog = "@conversation/corellia_privateer_tier4:s_a87e8cba", -- They'll appreciate the escort. Good luck.
	animation = "dismiss",
	playerAnimation = "",
	stopConversation = "true",
	options = {}
}
turoldine_convo_template:addScreen(accept_duty2)

accept_duty3 = ConvoScreen:new {
	id = "accept_duty3",
	leftDialog = "@conversation/corellia_privateer_tier4:s_4b924eb9", -- Sure is. Bring it back in.
	animation = "dismiss",
	playerAnimation = "",
	stopConversation = "true",
	options = {}
}
turoldine_convo_template:addScreen(accept_duty3)

accept_duty4 = ConvoScreen:new {
	id = "accept_duty4",
	leftDialog = "@conversation/corellia_privateer_tier4:s_873be682", -- I agree. Take care of it as quickly as you can.
	animation = "dismiss",
	playerAnimation = "",
	stopConversation = "true",
	options = {}
}
turoldine_convo_template:addScreen(accept_duty4)

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