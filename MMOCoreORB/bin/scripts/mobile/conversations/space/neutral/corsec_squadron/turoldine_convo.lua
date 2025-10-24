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
	leftDialog = "@conversation/corellia_privateer_tier4:s_db8b8333", -- You're a good pilot. You're only going to get better - as long as you keep studying.
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

first_mission_success = ConvoScreen:new {
	id = "first_mission_success",
	leftDialog = "@conversation/corellia_privateer_tier4:s_982697df", -- That was rougher than I expected.
	animation = "",
	playerAnimation = "",
	stopConversation = "false",
	options = {
		{"@conversation/corellia_privateer_tier4:s_4376ab12", "take_a_break"}, -- Black Suns are here to stay.
		{"@conversation/corellia_privateer_tier4:s_770b1869", "fix_your_ship"}, -- My ship's a mess.
	}
}
turoldine_convo_template:addScreen(first_mission_success);

take_a_break = ConvoScreen:new {
	id = "take_a_break",
	leftDialog = "@conversation/corellia_privateer_tier4:s_4345fa87", -- So are we. I want you to take a break. Catch your breath. See me when you're ready for another assignment. In the meantime, here's your duty pay.
	animation = "nod_head_once",
	playerAnimation = "",
	stopConversation = "false",
	options = {
		{"@conversation/corellia_privateer_tier4:s_fc27931b", "earned_it_first"}, -- Thanks.
	}
}
turoldine_convo_template:addScreen(take_a_break);

fix_your_ship = ConvoScreen:new {
	id = "fix_your_ship",
	leftDialog = "@conversation/corellia_privateer_tier4:s_642269cb", -- Take some time, get it fixed. The situation's under control for now. Come see me when you're ready for another assignment. In the meantime, here's your duty pay.
	animation = "shrug_hands",
	playerAnimation = "",
	stopConversation = "false",
	options = {
		{"@conversation/corellia_privateer_tier4:s_fc27931b", "earned_it_first"}, -- Thanks.
	}
}
turoldine_convo_template:addScreen(fix_your_ship);

earned_it_first = ConvoScreen:new {
	id = "earned_it_first",
	leftDialog = "@conversation/corellia_privateer_tier4:s_5dec8b83", -- You've earned it.
	animation = "wave_on_dismissing",
	playerAnimation = "",
	stopConversation = "true",
	options = {}
}
turoldine_convo_template:addScreen(earned_it_first);

failed_first_mission = ConvoScreen:new {
	id = "failed_first_mission",
	leftDialog = "@conversation/corellia_privateer_tier4:s_b26194cb", -- What are you doing here?
	animation = "",
	playerAnimation = "",
	stopConversation = "false",
	options = {
		{"@conversation/corellia_privateer_tier4:s_78c79a4f", "follow_orders"}, -- You sent me on a suicide mission!
		{"@conversation/corellia_privateer_tier4:s_66147141", "need_more_pilots"}, -- Regrouping.
	}
}
turoldine_convo_template:addScreen(failed_first_mission);

follow_orders = ConvoScreen:new {
	id = "follow_orders",
	leftDialog = "@conversation/corellia_privateer_tier4:s_351090c2", -- Hey, you don't like it here, you can find yourself another job. But as long as you're reporting to me, you'll do WHAT I say, WHEN I say it. Do you read me?
	animation = "threaten",
	playerAnimation = "",
	stopConversation = "false",
	options = {
		{"@conversation/corellia_privateer_tier4:s_1b8d65e2", "out_of_my_sight"}, -- Loud and clear - SIR.
	}
}
turoldine_convo_template:addScreen(follow_orders);

out_of_my_sight = ConvoScreen:new {
	id = "out_of_my_sight",
	leftDialog = "@conversation/corellia_privateer_tier4:s_f7f133e1", -- Get out of my sight.
	animation = "dismiss",
	playerAnimation = "",
	stopConversation = "true",
	options = {}
}
turoldine_convo_template:addScreen(out_of_my_sight);

need_more_pilots = ConvoScreen:new {
	id = "need_more_pilots",
	leftDialog = "@conversation/corellia_privateer_tier4:s_80409644", -- How's it looking? Do you need more pilots?
	animation = "",
	playerAnimation = "",
	stopConversation = "false",
	options = {
		{"@conversation/corellia_privateer_tier4:s_2f41692c", "first_see_soon"}, -- I've got it under control.
	}
}
turoldine_convo_template:addScreen(need_more_pilots);

first_see_soon = ConvoScreen:new {
	id = "first_see_soon",
	leftDialog = "@conversation/corellia_privateer_tier4:s_89368a2f", -- OK. I'll see you soon.
	animation = "wave_on_dismissing",
	playerAnimation = "",
	stopConversation = "true",
	options = {}
}
turoldine_convo_template:addScreen(first_see_soon);

-- Mission 2

mission2_train_fighters = ConvoScreen:new {
	id = "mission2_train_fighters",
	leftDialog = "@conversation/corellia_privateer_tier4:s_208869a4", -- So. We've got a situation here.
	animation = "",
	playerAnimation = "",
	stopConversation = "false",
	options = {
		{"@conversation/corellia_privateer_tier4:s_aa048a4e", "up_against"}, -- We? What WE? I was the only one getting painted up there!
		{"@conversation/corellia_privateer_tier4:s_10c8ee3d", "heard_of_daggers"}, -- That's one way to put it.
	}
}
turoldine_convo_template:addScreen(mission2_train_fighters);

mission2_train_components = ConvoScreen:new {
	id = "mission2_train_components",
	leftDialog = "@conversation/corellia_privateer_tier4:s_208869a4", -- So. We've got a situation here.
	animation = "",
	playerAnimation = "",
	stopConversation = "false",
	options = {
		{"@conversation/corellia_privateer_tier4:s_aa048a4e", "up_against"}, -- We? What WE? I was the only one getting painted up there!
		{"@conversation/corellia_privateer_tier4:s_10c8ee3d", "heard_of_daggers"}, -- That's one way to put it.
	}
}
turoldine_convo_template:addScreen(mission2_train_components)

mission2_train_techniques = ConvoScreen:new {
	id = "mission2_train_techniques",
	leftDialog = "@conversation/corellia_privateer_tier4:s_208869a4", -- So. We've got a situation here.
	animation = "",
	playerAnimation = "",
	stopConversation = "false",
	options = {
		{"@conversation/corellia_privateer_tier4:s_aa048a4e", "up_against"}, -- We? What WE? I was the only one getting painted up there!
		{"@conversation/corellia_privateer_tier4:s_10c8ee3d", "heard_of_daggers"}, -- That's one way to put it.
	}
}
turoldine_convo_template:addScreen(mission2_train_techniques)

mission2_train_algorithms = ConvoScreen:new {
	id = "mission2_train_algorithms",
	leftDialog = "@conversation/corellia_privateer_tier4:s_208869a4", -- So. We've got a situation here.
	animation = "",
	playerAnimation = "",
	stopConversation = "false",
	options = {
		{"@conversation/corellia_privateer_tier4:s_aa048a4e", "up_against"}, -- We? What WE? I was the only one getting painted up there!
		{"@conversation/corellia_privateer_tier4:s_10c8ee3d", "heard_of_daggers"}, -- That's one way to put it.
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
		{"@conversation/corellia_privateer_tier4:s_5c522568", "got_a_situation"}, --  Yes, of course.
	}
}
turoldine_convo_template:addScreen(second_mission);

got_a_situation = ConvoScreen:new {
	id = "got_a_situation",
	leftDialog = "@conversation/corellia_privateer_tier4:s_208869a4", -- So. We've got a situation here.
	animation = "",
	playerAnimation = "",
	stopConversation = "false",
	options = {
		{"@conversation/corellia_privateer_tier4:s_aa048a4e", "up_against"}, -- We? What WE? I was the only one getting painted up there!
		{"@conversation/corellia_privateer_tier4:s_10c8ee3d", "heard_of_daggers"}, -- That's one way to put it.
	}
}
turoldine_convo_template:addScreen(got_a_situation);

up_against = ConvoScreen:new {
	id = "up_against",
	leftDialog = "@conversation/corellia_privateer_tier4:s_746fc787", -- I know you're upset. You've got every right to be. But you helped us. Now we know what we're up against.
	animation = "explain",
	playerAnimation = "",
	stopConversation = "false",
	options = {
		{"@conversation/corellia_privateer_tier4:s_e807e589", "full_attack"}, -- And what are we going to do?
	}
}
turoldine_convo_template:addScreen(up_against);

full_attack = ConvoScreen:new {
	id = "full_attack",
	leftDialog = "@conversation/corellia_privateer_tier4:s_da33670a", -- Eventually, we're going to mount a full attack against the Black Suns. But first, we're going to isolate them. The Suns have been busy, building alliances.
	animation = "tap_head",
	playerAnimation = "",
	stopConversation = "false",
	options = {
		{"@conversation/corellia_privateer_tier4:s_a603fe55", "suns_pay_well"}, -- It's a good idea, from their point of view. They can send their flunkies in first.
	}
}
turoldine_convo_template:addScreen(full_attack);

suns_pay_well = ConvoScreen:new {
	id = "suns_pay_well",
	leftDialog = "@conversation/corellia_privateer_tier4:s_c08d38c9", -- Exactly. Don't know why the flunkies haven't figured that one out yet. The Suns must pay well.
	animation = "rub_belly",
	playerAnimation = "",
	stopConversation = "false",
	options = {
		{"@conversation/corellia_privateer_tier4:s_47441fe", "heard_of_daggers"}, -- I'd bet on it.
	}
}
turoldine_convo_template:addScreen(suns_pay_well);

heard_of_daggers = ConvoScreen:new {
	id = "heard_of_daggers",
	leftDialog = "@conversation/corellia_privateer_tier4:s_e20b6ab5", -- Have you ever heard of the Hidden Daggers?
	animation = "",
	playerAnimation = "",
	stopConversation = "false",
	options = {
		{"@conversation/corellia_privateer_tier4:s_2dc3ccb7", "daggers_and_suns"}, -- They're assassins, aren't they?
	}
}
turoldine_convo_template:addScreen(heard_of_daggers);

daggers_and_suns = ConvoScreen:new {
	id = "daggers_and_suns",
	leftDialog = "@conversation/corellia_privateer_tier4:s_ce57a3fe", -- That's right. It's possible that they're working with the Black Suns.
	animation = "explain",
	playerAnimation = "rub_chin_thoughtful",
	stopConversation = "false",
	options = {
		{"@conversation/corellia_privateer_tier4:s_a9f9363a", "dont_check_closet"}, -- I wonder why they need assassins.
	}
}
turoldine_convo_template:addScreen(daggers_and_suns);

dont_check_closet = ConvoScreen:new {
	id = "dont_check_closet",
	leftDialog = "@conversation/corellia_privateer_tier4:s_cce691a5", -- I don't think you need to check your closets before you go to sleep at night, if that's what you mean. The Suns just need hired guns. But these are professionals; we can't take them lightly.
	animation = "laugh",
	playerAnimation = "",
	stopConversation = "false",
	options = {
		{"@conversation/corellia_privateer_tier4:s_6ead851d", "intel_in_dathomir"}, -- Could mean trouble.
	}
}
turoldine_convo_template:addScreen(dont_check_closet);

intel_in_dathomir = ConvoScreen:new {
	id = "intel_in_dathomir",
	leftDialog = "@conversation/corellia_privateer_tier4:s_ba3977c", -- With a capital T. Let's see what we're dealing with.  We've got intel on the locations of several Hidden Dagger ships in the Dathomir System. We need to take them out. And I think you're the pilot for the job.
	animation = "nod_head_once",
	playerAnimation = "",
	stopConversation = "false",
	options = {
		{"@conversation/corellia_privateer_tier4:s_f69ff117", "accept_second_mission"}, -- What will I be facing up there?
	}
}
turoldine_convo_template:addScreen(intel_in_dathomir);

accept_second_mission = ConvoScreen:new {
	id = "accept_second_mission",
	leftDialog = "@conversation/corellia_privateer_tier4:s_c1e97adf", --  You won't be making any friends up there, that's for sure. Just keep your eyes open, and you'll be all right. Report back to me when you're through.
	animation = "explain",
	playerAnimation = "",
	stopConversation = "true",
	options = {}
}
turoldine_convo_template:addScreen(accept_second_mission);

failed_second_mission = ConvoScreen:new {
	id = "failed_second_mission",
	leftDialog = "@conversation/corellia_privateer_tier4:s_b5d3394c", -- Mission failure, %TU.
	animation = "shake_head_disgust",
	playerAnimation = "",
	stopConversation = "false",
	options = {
		{"@conversation/corellia_privateer_tier4:s_87d7e908", "mission_important"}, -- I know.
		{"@conversation/corellia_privateer_tier4:s_87b9d75b", "be_watching"}, -- Can I give it another shot?
	}
}
turoldine_convo_template:addScreen(failed_second_mission);

mission_important = ConvoScreen:new {
	id = "mission_important",
	leftDialog = "@conversation/corellia_privateer_tier4:s_c5a03378", -- I need you to give it another shot. This is important.
	animation = "pound_fist_palm",
	playerAnimation = "slump_head",
	stopConversation = "true",
	options = {}
}
turoldine_convo_template:addScreen(mission_important);

be_watching = ConvoScreen:new {
	id = "be_watching",
	leftDialog = "@conversation/corellia_privateer_tier4:s_61d7c289", -- Absolutely. I'll be watching.
	animation = "nod_head_once",
	playerAnimation = "",
	stopConversation = "true",
	options = {}
}
turoldine_convo_template:addScreen(be_watching);

second_mission_success = ConvoScreen:new {
	id = "second_mission_success",
	leftDialog = "@conversation/corellia_privateer_tier4:s_846dc537", -- Here. This is for you.
	animation = "",
	playerAnimation = "",
	stopConversation = "false",
	options = {
		{"@conversation/corellia_privateer_tier4:s_1c8bddbb", "duty_pay"}, -- What is it?
		{"@conversation/corellia_privateer_tier4:s_fc27931b", "see_you_soon"}, -- Thanks.
	}
}
turoldine_convo_template:addScreen(second_mission_success);

duty_pay = ConvoScreen:new {
	id = "duty_pay",
	leftDialog = "@conversation/corellia_privateer_tier4:s_3839d57f", -- Your duty pay.
	animation = "",
	playerAnimation = "",
	stopConversation = "false",
	options = {
		{"@conversation/corellia_privateer_tier4:s_aab2440f", "come_see_ready"}, -- Excellent. I can use it.
	}
}
turoldine_convo_template:addScreen(duty_pay);

come_see_ready = ConvoScreen:new {
	id = "come_see_ready",
	leftDialog = "@conversation/corellia_privateer_tier4:s_e796f3ec", -- Come see me when you're ready for another mission.
	animation = "dismiss",
	playerAnimation = "applause_polite",
	stopConversation = "true",
	options = {}
}
turoldine_convo_template:addScreen(come_see_ready);

see_you_soon = ConvoScreen:new {
	id = "see_you_soon",
	leftDialog = "@conversation/corellia_privateer_tier4:s_e53904e6", -- You're quite a pilot, %TU. I'll see you soon.
	animation = "salute2",
	playerAnimation = "salute1",
	stopConversation = "true",
	options = {}
}
turoldine_convo_template:addScreen(see_you_soon);

-- Mission 3

mission3_train_fighters = ConvoScreen:new {
	id = "mission3_train_fighters",
	leftDialog = "@conversation/corellia_privateer_tier4:s_b779f640", -- The Black Suns have noticed our activities. They're getting ready to mount a full attack, I think. But we'll be ready.
	animation = "",
	playerAnimation = "",
	stopConversation = "false",
	options = {
		{"@conversation/corellia_privateer_tier4:s_d1be90a9", "coordinated_attack"}, -- What's the plan?
		{"@conversation/corellia_privateer_tier4:s_13811ca0", "hit_suns_below"}, -- What about the Hidden Daggers?
	}
}
turoldine_convo_template:addScreen(mission3_train_fighters);

mission3_train_components = ConvoScreen:new {
	id = "mission3_train_components",
	leftDialog = "@conversation/corellia_privateer_tier4:s_b779f640", -- The Black Suns have noticed our activities. They're getting ready to mount a full attack, I think. But we'll be ready.
	animation = "",
	playerAnimation = "",
	stopConversation = "false",
	options = {
		{"@conversation/corellia_privateer_tier4:s_d1be90a9", "coordinated_attack"}, -- What's the plan?
		{"@conversation/corellia_privateer_tier4:s_13811ca0", "hit_suns_below"}, -- What about the Hidden Daggers?
	}
}
turoldine_convo_template:addScreen(mission3_train_components)

mission3_train_techniques = ConvoScreen:new {
	id = "mission3_train_techniques",
	leftDialog = "@conversation/corellia_privateer_tier4:s_b779f640", -- The Black Suns have noticed our activities. They're getting ready to mount a full attack, I think. But we'll be ready.
	animation = "",
	playerAnimation = "",
	stopConversation = "false",
	options = {
		{"@conversation/corellia_privateer_tier4:s_d1be90a9", "coordinated_attack"}, -- What's the plan?
		{"@conversation/corellia_privateer_tier4:s_13811ca0", "hit_suns_below"}, -- What about the Hidden Daggers?
	}
}
turoldine_convo_template:addScreen(mission3_train_techniques)

mission3_train_algorithms = ConvoScreen:new {
	id = "mission3_train_algorithms",
	leftDialog = "@conversation/corellia_privateer_tier4:s_b779f640", -- The Black Suns have noticed our activities. They're getting ready to mount a full attack, I think. But we'll be ready.
	animation = "",
	playerAnimation = "",
	stopConversation = "false",
	options = {
		{"@conversation/corellia_privateer_tier4:s_d1be90a9", "coordinated_attack"}, -- What's the plan?
		{"@conversation/corellia_privateer_tier4:s_13811ca0", "hit_suns_below"}, -- What about the Hidden Daggers?
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
		{"@conversation/corellia_privateer_tier4:s_5c522568", "noticed_activities"}, --  Yes, of course.
	}
}
turoldine_convo_template:addScreen(third_mission);

noticed_activities = ConvoScreen:new {
	id = "noticed_activities",
	leftDialog = "@conversation/corellia_privateer_tier4:s_b779f640", -- The Black Suns have noticed our activities. They're getting ready to mount a full attack, I think. But we'll be ready.
	animation = "",
	playerAnimation = "",
	stopConversation = "false",
	options = {
		{"@conversation/corellia_privateer_tier4:s_d1be90a9", "coordinated_attack"}, -- What's the plan?
		{"@conversation/corellia_privateer_tier4:s_13811ca0", "hit_suns_below"}, -- What about the Hidden Daggers?
	}
}
turoldine_convo_template:addScreen(noticed_activities);

coordinated_attack = ConvoScreen:new {
	id = "coordinated_attack",
	leftDialog = "@conversation/corellia_privateer_tier4:s_8807601", -- I want you to join forces with several of my other pilots. We need to mount a coordinated attack against these guys. I'll warn you now, it won't be easy.
	animation = "explain",
	playerAnimation = "",
	stopConversation = "false",
	options = {
		{"@conversation/corellia_privateer_tier4:s_76de5e9c", "solve_hidden_daggers"}, -- I didn't come to this post looking for easy.
	}
}
turoldine_convo_template:addScreen(coordinated_attack);

solve_hidden_daggers = ConvoScreen:new {
	id = "solve_hidden_daggers",
	leftDialog = "@conversation/corellia_privateer_tier4:s_4d147f07", -- All right then. Well stick with me. I think I've found a way for us to solve this Hidden Daggers problem, once and for all.
	animation = "tap_head",
	playerAnimation = "shrug_shoulders",
	stopConversation = "false",
	options = {
		{"@conversation/corellia_privateer_tier4:s_aa5afe64", "kill_black_sun"}, -- Oh yeah? What's the plan?
	}
}
turoldine_convo_template:addScreen(solve_hidden_daggers);

kill_black_sun = ConvoScreen:new {
	id = "kill_black_sun",
	leftDialog = "@conversation/corellia_privateer_tier4:s_39547224", -- More on that later. For now, I just want you to take care of those Black Sun fighters in Dantooine. Can I count on you?
	animation = "",
	playerAnimation = "",
	stopConversation = "false",
	options = {
		{"@conversation/corellia_privateer_tier4:s_d9cced1f", "accept_third_mission"}, -- Absolutely.
	}
}
turoldine_convo_template:addScreen(kill_black_sun);

accept_third_mission = ConvoScreen:new {
	id = "accept_third_mission",
	leftDialog = "@conversation/corellia_privateer_tier4:s_1aceb53", -- You're clear to leave.
	animation = "dismiss",
	playerAnimation = "",
	stopConversation = "true",
	options = {}
}
turoldine_convo_template:addScreen(accept_third_mission);

hit_suns_below = ConvoScreen:new {
	id = "hit_suns_below",
	leftDialog = "@conversation/corellia_privateer_tier4:s_ed52d8f6", -- They're still a threat, no doubt about it. But we've found a way to deal with them, thanks to you. So we're hitting the Suns from below. Now it may be time to hit them from above.
	animation = "rub_belly",
	playerAnimation = "",
	stopConversation = "false",
	options = {
		{"@conversation/corellia_privateer_tier4:s_af153b90", "push_back_suns"}, -- Is that my mission?
		{"@conversation/corellia_privateer_tier4:s_77e48d5b", "black_sun_vehement"}, -- What do you mean?
	}
}
turoldine_convo_template:addScreen(hit_suns_below);

push_back_suns = ConvoScreen:new {
	id = "push_back_suns",
	leftDialog = "@conversation/corellia_privateer_tier4:s_475b4478", -- No; not yet. For now, I want you to work with several of my fighters to push back a Black Sun attack in Dantooine. They are moving on our position now.
	animation = "explain",
	playerAnimation = "",
	stopConversation = "false",
	options = {
		{"@conversation/corellia_privateer_tier4:s_50a82bc3", "accept_third_mission2"}, -- How much time do I have?
	}
}
turoldine_convo_template:addScreen(push_back_suns);

black_sun_vehement = ConvoScreen:new {
	id = "black_sun_vehement",
	leftDialog = "@conversation/corellia_privateer_tier4:s_5afdd10d", -- There's a Black Sun Vehement somewhere in the Dantooine System. We're searching for his coordinates now. Once we've located him, I'll want you to take him out.
	animation = "explain",
	playerAnimation = "",
	stopConversation = "false",
	options = {
		{"@conversation/corellia_privateer_tier4:s_d3f6b302", "can_help_us"}, -- Just give me a shot.
	}
}
turoldine_convo_template:addScreen(black_sun_vehement);

can_help_us = ConvoScreen:new {
	id = "can_help_us",
	leftDialog = "@conversation/corellia_privateer_tier4:s_40c0cfc0", -- He's a leader. If he's out of the picture, they'll become disorganized. And that can only help us.
	animation = "tap_head",
	playerAnimation = "",
	stopConversation = "false",
	options = {
		{"@conversation/corellia_privateer_tier4:s_c09d4fa5", "one_of_a_kind"}, -- But another Black Sun will just step into his shoes!
	}
}
turoldine_convo_template:addScreen(can_help_us);

one_of_a_kind = ConvoScreen:new {
	id = "one_of_a_kind",
	leftDialog = "@conversation/corellia_privateer_tier4:s_35d00365", -- Not this guy. He's one of a kind. But I'm getting ahead of myself. We haven't even found this guy yet.
	animation = "",
	playerAnimation = "",
	stopConversation = "false",
	options = {
		{"@conversation/corellia_privateer_tier4:s_963212ec", "join_forces_corsec"}, -- OK...
	}
}
turoldine_convo_template:addScreen(one_of_a_kind);

join_forces_corsec = ConvoScreen:new {
	id = "join_forces_corsec",
	leftDialog = "@conversation/corellia_privateer_tier4:s_35d00365", -- For now, I want you to join forces with my other CorSec fighters. We need your help.
	animation = "",
	playerAnimation = "",
	stopConversation = "false",
	options = {
		{"@conversation/corellia_privateer_tier4:s_62241cb7", "black_sun_moving"}, -- What's going on?
	}
}
turoldine_convo_template:addScreen(join_forces_corsec);

black_sun_moving = ConvoScreen:new {
	id = "black_sun_moving",
	leftDialog = "@conversation/corellia_privateer_tier4:s_cd9ca17f", -- The Black Suns are mounting an attack. They are moving on our position now.
	animation = "",
	playerAnimation = "",
	stopConversation = "false",
	options = {
		{"@conversation/corellia_privateer_tier4:s_50a82bc3", "accept_third_mission2"}, -- How much time do I have?
	}
}
turoldine_convo_template:addScreen(black_sun_moving);

accept_third_mission2 = ConvoScreen:new {
	id = "accept_third_mission2",
	leftDialog = "@conversation/corellia_privateer_tier4:s_add3fe59", -- Not much. I need you to leave immediately.
	animation = "dismiss",
	playerAnimation = "",
	stopConversation = "true",
	options = {}
}
turoldine_convo_template:addScreen(accept_third_mission2);

failed_third_mission = ConvoScreen:new {
	id = "failed_third_mission",
	leftDialog = "@conversation/corellia_privateer_tier4:s_ed86e89f", -- Do I need to find another pilot?
	animation = "sigh_deeply",
	playerAnimation = "",
	stopConversation = "false",
	options = {
		{"@conversation/corellia_privateer_tier4:s_47120e86", "need_another_chance"}, -- No. You just need to give me another chance.
		{"@conversation/corellia_privateer_tier4:s_575d94fc", "blast_to_bits"}, -- They're blasting me to bits up there.
	}
}
turoldine_convo_template:addScreen(failed_third_mission);

need_another_chance = ConvoScreen:new {
	id = "need_another_chance",
	leftDialog = "@conversation/corellia_privateer_tier4:s_535a48bf", -- Is that right?
	animation = "",
	playerAnimation = "embarrassed",
	stopConversation = "false",
	options = {
		{"@conversation/corellia_privateer_tier4:s_d9cced1f", "third_another_chance"}, -- Absolutely.
	}
}
turoldine_convo_template:addScreen(need_another_chance);

third_another_chance = ConvoScreen:new {
	id = "third_another_chance",
	leftDialog = "@conversation/corellia_privateer_tier4:s_8caf8c64", -- OK. I'm giving you another chance.
	animation = "shrug_shoulders",
	playerAnimation = "",
	stopConversation = "true",
	options = {}
}
turoldine_convo_template:addScreen(third_another_chance);

blast_to_bits = ConvoScreen:new {
	id = "blast_to_bits",
	leftDialog = "@conversation/corellia_privateer_tier4:s_a5f9f5fc", -- They're going to blast ALL of us to bits, if you don't get back up there.
	animation = "gesticulate_wildly",
	playerAnimation = "point_to_self",
	stopConversation = "true",
	options = {}
}
turoldine_convo_template:addScreen(blast_to_bits);

third_mission_success = ConvoScreen:new {
	id = "third_mission_success",
	leftDialog = "@conversation/corellia_privateer_tier4:s_c81aa963", -- Nice work, %TU. That wasn't easy.
	animation = "",
	playerAnimation = "",
	stopConversation = "false",
	options = {
		{"@conversation/corellia_privateer_tier4:s_ff224692", "ready_for_pay"}, -- It's done. That's all that matters.
		{"@conversation/corellia_privateer_tier4:s_9696df79", "glad_back"}, -- I'm glad to be back here in one piece.
	}
}
turoldine_convo_template:addScreen(third_mission_success);

ready_for_pay = ConvoScreen:new {
	id = "ready_for_pay",
	leftDialog = "@conversation/corellia_privateer_tier4:s_bb1b5c31", -- Ready for your duty pay?
	animation = "",
	playerAnimation = "",
	stopConversation = "false",
	options = {
		{"@conversation/corellia_privateer_tier4:s_ca51315f", "paid_for_third"}, -- Always.
	}
}
turoldine_convo_template:addScreen(ready_for_pay);

paid_for_third = ConvoScreen:new {
	id = "paid_for_third",
	leftDialog = "@conversation/corellia_privateer_tier4:s_483d677f", -- Here you go. Come see me when you're ready for your next mission.
	animation = "salute1",
	playerAnimation = "salute1",
	stopConversation = "true",
	options = {}
}
turoldine_convo_template:addScreen(paid_for_third);

glad_back = ConvoScreen:new {
	id = "glad_back",
	leftDialog = "@conversation/corellia_privateer_tier4:s_24f79cb0", -- I'm glad you're back, too. Here. I want to give you your duty pay.
	animation = "nod_head_once",
	playerAnimation = "",
	stopConversation = "false",
	options = {
		{"@conversation/corellia_privateer_tier4:s_fc27931b", "stick_with_it"}, -- Thanks.
	}
}
turoldine_convo_template:addScreen(glad_back);

stick_with_it = ConvoScreen:new {
	id = "stick_with_it",
	leftDialog = "@conversation/corellia_privateer_tier4:s_ef2b1c74", -- Stick with it. You'll be earning some real money soon. You've got a real future ahead of you.
	animation = "salute1",
	playerAnimation = "salute1",
	stopConversation = "true",
	options = {}
}
turoldine_convo_template:addScreen(stick_with_it);

-- Mission 4

final_train_fighters = ConvoScreen:new {
	id = "final_train_fighters",
	leftDialog = "@conversation/corellia_privateer_tier4:s_d4c1c824", -- You're doing a great job so far. I have a plan.
	animation = "nod_head_once",
	playerAnimation = "",
	stopConversation = "false",
	options = {
		{"@conversation/corellia_privateer_tier4:s_979d1baf", "isnt_so_crazy"}, --  You! Always with the crazy plans!
		{"@conversation/corellia_privateer_tier4:s_71857d84", "another_assassination"}, --  Don't bother explaining. I'm mad. I just want to fight..
	}
}
turoldine_convo_template:addScreen(final_train_fighters);

final_train_components = ConvoScreen:new {
	id = "final_train_components",
	leftDialog = "@conversation/corellia_privateer_tier4:s_d4c1c824", -- You're doing a great job so far. I have a plan.
	animation = "nod_head_once",
	playerAnimation = "",
	stopConversation = "false",
	options = {
		{"@conversation/corellia_privateer_tier4:s_979d1baf", "isnt_so_crazy"}, --  You! Always with the crazy plans!
		{"@conversation/corellia_privateer_tier4:s_71857d84", "another_assassination"}, --  Don't bother explaining. I'm mad. I just want to fight..
	}
}
turoldine_convo_template:addScreen(final_train_components)

final_train_techniques = ConvoScreen:new {
	id = "final_train_techniques",
	leftDialog = "@conversation/corellia_privateer_tier4:s_d4c1c824", -- You're doing a great job so far. I have a plan.
	animation = "nod_head_once",
	playerAnimation = "",
	stopConversation = "false",
	options = {
		{"@conversation/corellia_privateer_tier4:s_979d1baf", "isnt_so_crazy"}, --  You! Always with the crazy plans!
		{"@conversation/corellia_privateer_tier4:s_71857d84", "another_assassination"}, --  Don't bother explaining. I'm mad. I just want to fight..
	}
}
turoldine_convo_template:addScreen(final_train_techniques)

final_train_algorithms = ConvoScreen:new {
	id = "final_train_algorithms",
	leftDialog = "@conversation/corellia_privateer_tier4:s_d4c1c824", -- You're doing a great job so far. I have a plan.
	animation = "nod_head_once",
	playerAnimation = "",
	stopConversation = "false",
	options = {
		{"@conversation/corellia_privateer_tier4:s_979d1baf", "isnt_so_crazy"}, --  You! Always with the crazy plans!
		{"@conversation/corellia_privateer_tier4:s_71857d84", "another_assassination"}, --  Don't bother explaining. I'm mad. I just want to fight..
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
		{"@conversation/corellia_privateer_tier4:s_5c522568", "fourth_plan"}, --  Yes, of course.
	}
}
turoldine_convo_template:addScreen(fourth_mission);

fourth_plan = ConvoScreen:new {
	id = "fourth_plan",
	leftDialog = "@conversation/corellia_privateer_tier4:s_d4c1c824", -- You're doing a great job so far. I have a plan.
	animation = "nod_head_once",
	playerAnimation = "",
	stopConversation = "false",
	options = {
		{"@conversation/corellia_privateer_tier4:s_979d1baf", "isnt_so_crazy"}, --  You! Always with the crazy plans!
		{"@conversation/corellia_privateer_tier4:s_71857d84", "another_assassination"}, --  Don't bother explaining. I'm mad. I just want to fight..
	}
}
turoldine_convo_template:addScreen(fourth_plan);

isnt_so_crazy = ConvoScreen:new {
	id = "isnt_so_crazy",
	leftDialog = "@conversation/corellia_privateer_tier4:s_bc0e2727", -- It's what they pay me for. And this plan isn't so crazy. We're just going to deal with the Hidden Daggers, once and for all.
	animation = "shrug_shoulders",
	playerAnimation = "smack_self",
	stopConversation = "false",
	options = {
		{"@conversation/corellia_privateer_tier4:s_4cda51e6", "split_time"}, -- I thought we WERE dealing with them.
	}
}
turoldine_convo_template:addScreen(isnt_so_crazy)

split_time = ConvoScreen:new {
	id = "split_time",
	leftDialog = "@conversation/corellia_privateer_tier4:s_7e6d012f", -- We were splitting our time between the two groups. But now we've struck a real blow against the Suns, they'll need a little time to regroup.
	animation = "explain",
	playerAnimation = "",
	stopConversation = "false",
	options = {
		{"@conversation/corellia_privateer_tier4:s_74fdf9dc", "stronger_group"}, -- So they won't be available to help the assassins?
	}
}
turoldine_convo_template:addScreen(split_time)

stronger_group = ConvoScreen:new {
	id = "stronger_group",
	leftDialog = "@conversation/corellia_privateer_tier4:s_317c39a8", -- Exactly. And between CorSec and the Daggers, I think we're the stronger group. So let's just  take them out once and for all.
	animation = "tap_head",
	playerAnimation = "",
	stopConversation = "false",
	options = {
		{"@conversation/corellia_privateer_tier4:s_f4176967", "ever_assassinated"}, -- What did you have in mind?
	}
}
turoldine_convo_template:addScreen(stronger_group)

ever_assassinated = ConvoScreen:new {
	id = "ever_assassinated",
	leftDialog = "@conversation/corellia_privateer_tier4:s_621643f5", -- Have you ever assassinated anybody?
	animation = "rub_chin_thoughtful",
	playerAnimation = "",
	stopConversation = "false",
	options = {
		{"@conversation/corellia_privateer_tier4:s_f2a6dda8", "nicely_put"}, -- Do you mean to tell me I'm going to assassinate an assassin?
	}
}
turoldine_convo_template:addScreen(ever_assassinated)

nicely_put = ConvoScreen:new {
	id = "nicely_put",
	leftDialog = "@conversation/corellia_privateer_tier4:s_4e33510b", -- Nicely put.
	animation = "nod_head_once",
	playerAnimation = "",
	stopConversation = "false",
	options = {
		{"@conversation/corellia_privateer_tier4:s_88d56cda", "youre_the_best"}, -- I don't think that'll be easy.
	}
}
turoldine_convo_template:addScreen(nicely_put)

youre_the_best = ConvoScreen:new {
	id = "youre_the_best",
	leftDialog = "@conversation/corellia_privateer_tier4:s_d6593a09", -- Neither do I. That's why I'm sending you. You're the best.
	animation = "laugh",
	playerAnimation = "",
	stopConversation = "false",
	options = {
		{"@conversation/corellia_privateer_tier4:s_e8d7e137", "should_be"}, -- I'm flattered.
	}
}
turoldine_convo_template:addScreen(youre_the_best)

should_be = ConvoScreen:new {
	id = "should_be",
	leftDialog = "@conversation/corellia_privateer_tier4:s_2e256f44", -- You should be.
	animation = "laugh",
	playerAnimation = "",
	stopConversation = "false",
	options = {
		{"@conversation/corellia_privateer_tier4:s_4de5d7c6", "element_of_surprise"}, -- But I'm not interested in getting myself killed.
	}
}
turoldine_convo_template:addScreen(should_be)

element_of_surprise = ConvoScreen:new {
	id = "element_of_surprise",
	leftDialog = "@conversation/corellia_privateer_tier4:s_2b122b72", -- You'll have the element of surprise. The Daggers think we're focused on the Suns. They won't see you coming.
	animation = "laugh",
	playerAnimation = "",
	stopConversation = "false",
	options = {
		{"@conversation/corellia_privateer_tier4:s_82288395", "accept_fourth_mission"}, -- I hope you're right.
	}
}
turoldine_convo_template:addScreen(element_of_surprise)

another_assassination = ConvoScreen:new {
	id = "another_assassination",
	leftDialog = "@conversation/corellia_privateer_tier4:s_3eecd6e9", -- Then I'll cut to the chase. I'm sending you on an assassination mission
	animation = "",
	playerAnimation = "",
	stopConversation = "false",
	options = {
		{"@conversation/corellia_privateer_tier4:s_7bbc6fc1", "daggers_leader"}, --  Who am I killing?
	}
}
turoldine_convo_template:addScreen(another_assassination)

daggers_leader = ConvoScreen:new {
	id = "daggers_leader",
	leftDialog = "@conversation/corellia_privateer_tier4:s_bc808f0b", -- One of the leaders of the Hidden Daggers.
	animation = "",
	playerAnimation = "",
	stopConversation = "false",
	options = {
		{"@conversation/corellia_privateer_tier4:s_a6167ed7", "general_idea"}, --  I'm assassinating...an assassin?
	}
}
turoldine_convo_template:addScreen(daggers_leader)

general_idea = ConvoScreen:new {
	id = "general_idea",
	leftDialog = "@conversation/corellia_privateer_tier4:s_218fee99", -- That's the idea.
	animation = "nod_head_once",
	playerAnimation = "",
	stopConversation = "false",
	options = {
		{"@conversation/corellia_privateer_tier4:s_88d56cda", "youre_the_best"}, --  I don't think that'll be easy.
	}
}
turoldine_convo_template:addScreen(general_idea)

accept_fourth_mission = ConvoScreen:new {
	id = "accept_fourth_mission",
	leftDialog = "@conversation/corellia_privateer_tier4:s_6e4a17c", -- We'll find out.  You'll find your first mark in the Dathomir system.
	animation = "dismiss",
	playerAnimation = "",
	stopConversation = "true",
	options = {}
}
turoldine_convo_template:addScreen(accept_fourth_mission);

failed_fourth_mission = ConvoScreen:new {
	id = "failed_third_mission",
	leftDialog = "@conversation/corellia_privateer_tier4:s_6862706c", -- No good.
	animation = "shake_head_no",
	playerAnimation = "",
	stopConversation = "false",
	options = {
		{"@conversation/corellia_privateer_tier4:s_182c692f", "kills_not_excuses"}, -- Maybe your plan is no good!
		{"@conversation/corellia_privateer_tier4:s_c71818a8", "see_that_you"}, -- This time I'll take care of them.
	}
}
turoldine_convo_template:addScreen(failed_fourth_mission);

kills_not_excuses = ConvoScreen:new {
	id = "kills_not_excuses",
	leftDialog = "@conversation/corellia_privateer_tier4:s_b6570fbb", -- Pilots under my command don't make excuses. They make kills. Get back up there.
	animation = "point_accusingly",
	playerAnimation = "stamp_feet",
	stopConversation = "true",
	options = {}
}
turoldine_convo_template:addScreen(kills_not_excuses);

see_that_you = ConvoScreen:new {
	id = "see_that_you",
	leftDialog = "@conversation/corellia_privateer_tier4:s_b679efe", -- See that you do.
	animation = "wave_on_dismissing",
	playerAnimation = "",
	stopConversation = "true",
	options = {}
}
turoldine_convo_template:addScreen(see_that_you);

fourth_mission_success = ConvoScreen:new {
	id = "fourth_mission_success",
	leftDialog = "@conversation/corellia_privateer_tier4:s_f0a6575a", -- Hah! So much for those Hidden Daggers!
	animation = "laugh",
	playerAnimation = "",
	stopConversation = "false",
	options = {
		{"@conversation/corellia_privateer_tier4:s_3f1b21c2", "dont_we_all"}, -- I want those Black Suns out of here too.
		{"@conversation/corellia_privateer_tier4:s_20ef9c42", "great_job"}, -- Mission accomplished.
	}
}
turoldine_convo_template:addScreen(fourth_mission_success);

dont_we_all = ConvoScreen:new {
	id = "dont_we_all",
	leftDialog = "@conversation/corellia_privateer_tier4:s_fc9e5d39", -- Don't we all! We're making headway. For now, though, take a break. Here's your duty pay. Take it down to the cantina. They'll like the color of your money.
	animation = "laugh",
	playerAnimation = "",
	stopConversation = "false",
	options = {
		{"@conversation/corellia_privateer_tier4:s_fcab4be0", "see_you_around"}, -- Good idea.
	}
}
turoldine_convo_template:addScreen(fourth_mission_dont_we_allsuccess);

see_you_around = ConvoScreen:new {
	id = "see_you_around",
	leftDialog = "@conversation/corellia_privateer_tier4:s_5d88d407", -- I'll see you around, %TU.
	animation = "salute1",
	playerAnimation = "salute1",
	stopConversation = "true",
	options = {}
}
turoldine_convo_template:addScreen(see_you_around);

great_job = ConvoScreen:new {
	id = "great_job",
	leftDialog = "@conversation/corellia_privateer_tier4:s_6e4a17c", -- Absolutely. I've got your duty pay. I wish I could give you more. You're doing a great job.
	animation = "salute1",
	playerAnimation = "salute1",
	stopConversation = "true",
	options = {}
}
turoldine_convo_template:addScreen(great_job);

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
	leftDialog = "@conversation/corellia_privateer_tier4:s_39b10484", -- I won't force you. If you don't want to do it, I will tell them you're injured. Of course, if you do choose to obey the order, it will most certainly not reflect in any way on your career here at the CorSec.
	animation = "shrug_shoulders",
	playerAnimation = "",
	stopConversation = "false",
	options = {
		{"@conversation/corellia_privateer_tier4:s_be7682ed", "theed_naboo"}, -- Where does it say I have to go?
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
