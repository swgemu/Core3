kaydine_convo_template = ConvoTemplate:new {
	initialScreen = "",
	templateType = "Lua",
	luaClassHandler = "kaydineConvoHandler",
	screens = {}
}

-- Not a pilot or JTL disabled
not_pilot = ConvoScreen:new {
	id = "not_pilot",
	leftDialog = "@conversation/naboo_privateer_trainer_2:s_3db3463f", -- How do you do civilian! Captain Kaydine, at your service.
	stopConversation = "true",
	options = {}
}
kaydine_convo_template:addScreen(not_pilot);

-- Pilot but not RSF
pilot_not_rsf = ConvoScreen:new {
	id = "pilot_not_rsf",
	leftDialog = "@conversation/naboo_privateer_trainer_2:s_7ac0f961", -- How do you do. Captain Kaydine, at your service.
	stopConversation = "false",
	options = {
		{"@conversation/naboo_privateer_trainer_2:s_c1ff5062", "non_rsf_missions"}, -- I'm looking for a mission. Do you have any?
	}
}
kaydine_convo_template:addScreen(pilot_not_rsf);

non_rsf_missions = ConvoScreen:new {
	id = "non_rsf_missions",
	leftDialog = "@conversation/naboo_privateer_trainer_2:s_7458c693", -- Sorry, kiddo. You don't have RSF clearance to fly any of my missions.
	stopConversation = "true",
	options = {}
}
kaydine_convo_template:addScreen(non_rsf_missions);

-- Not ready for Tier 2 yet
not_ready_tier2 = ConvoScreen:new {
	id = "not_ready_tier2",
	leftDialog = "@conversation/naboo_privateer_trainer_2:s_eac39719", -- Sorry, kiddo. You're still in need of training! Come back when you've learned to handle yourself better.
	stopConversation = "true",
	options = {}
}
kaydine_convo_template:addScreen(not_ready_tier2);

-- Already finished Tier 3
finished_tier3 = ConvoScreen:new {
	id = "finished_tier3",
	leftDialog = "@conversation/naboo_privateer_trainer_2:s_2d86b58b", -- Hey, kiddo! What are you still doing around here? You got bigger, better things to be doing!
	stopConversation = "true",
	options = {}
}
kaydine_convo_template:addScreen(finished_tier3);

-- On mission already
on_mission = ConvoScreen:new {
	id = "on_mission",
	leftDialog = "@conversation/naboo_privateer_trainer_2:s_e95a95a5", -- I believe you have some business to attend to... in space?
	stopConversation = "true",
	options = {}
}
kaydine_convo_template:addScreen(on_mission);

-- Completed Kaydine's tier, go to next trainer (Dulios)
completed_kaydine = ConvoScreen:new {
	id = "completed_kaydine",
	leftDialog = "@conversation/naboo_privateer_trainer_2:s_aae78dca", -- I think it's time for you to take on more responsibilities. Head deeper into the palace, my friend! Look for Commander Dulios.
	stopConversation = "true",
	options = {}
}
kaydine_convo_template:addScreen(completed_kaydine);

-- Here for work (default greeting)
here_for_work = ConvoScreen:new {
	id = "here_for_work",
	leftDialog = "@conversation/naboo_privateer_trainer_2:s_c5fcc7f5", -- Greetings, Captain %TU! Are you ready to take my place on the duty roster?
	stopConversation = "false",
	options = {
		{"@conversation/naboo_privateer_trainer_2:s_6114e8b7", "duty_options"}, -- I'm ready for duty
		{"@conversation/naboo_privateer_trainer_2:s_45d20070", "ready_train_pilot"}, -- I need training
	}
}
kaydine_convo_template:addScreen(here_for_work);

-- Duty mission options
duty_options = ConvoScreen:new {
	id = "duty_options",
	leftDialog = "@conversation/naboo_privateer_trainer_2:s_63053557", -- Good! What duty element do you want to participate in today?
	stopConversation = "false",
	options = {
		{"@conversation/naboo_privateer_trainer_2:s_c892e540", "accept_duty_destroy1"}, -- Destroy Ay'Nat Legion pirates in this system.
		{"@conversation/naboo_privateer_trainer_2:s_9b73da8", "accept_duty_escort"}, -- Protect the Royal Kylantha cargo.
		{"@conversation/naboo_privateer_trainer_2:s_30297e22", "accept_duty_recovery"}, -- Recover ships stolen by the Ay'Nat Legion.
	}
}
kaydine_convo_template:addScreen(duty_options);

accept_duty_destroy1 = ConvoScreen:new {
	id = "accept_duty_destroy1",
	leftDialog = "@conversation/naboo_privateer_trainer_2:s_bb291959", -- Excellent! Be careful up there! Those Ay'Nat outlaws are deadly enemies!
	stopConversation = "true",
	options = {}
}
kaydine_convo_template:addScreen(accept_duty_destroy1);

accept_duty_escort = ConvoScreen:new {
	id = "accept_duty_escort",
	leftDialog = "@conversation/naboo_privateer_trainer_2:s_2e7b17f3", -- It's very likely you'll fall under attack from Ay'Nat Legion pirates. Be careful...
	stopConversation = "true",
	options = {}
}
kaydine_convo_template:addScreen(accept_duty_escort);

accept_duty_recovery = ConvoScreen:new {
	id = "accept_duty_recovery",
	leftDialog = "@conversation/naboo_privateer_trainer_2:s_a0072111", -- Hm. A grim job if there ever was one. I respect your courage. Good luck!
	stopConversation = "true",
	options = {}
}
kaydine_convo_template:addScreen(accept_duty_recovery);

-- Training screen (options added dynamically)
ready_train_pilot = ConvoScreen:new {
	id = "ready_train_pilot",
	leftDialog = "@conversation/naboo_privateer_trainer_2:s_8a84109d", -- It must be your lucky day. I actually do have some elective duty missions. Take a look and tell me what you want.
	stopConversation = "false",
	options = {}
}
kaydine_convo_template:addScreen(ready_train_pilot);

-- Training completion screens
initial_train_fighters = ConvoScreen:new {
	id = "initial_train_fighters",
	leftDialog = "@conversation/naboo_privateer_trainer_2:s_4aa3066e", -- Ah yes! Good choice! Learning to fly many different types of ships makes an effective pilot!
	stopConversation = "true",
	options = {}
}
kaydine_convo_template:addScreen(initial_train_fighters);

initial_train_components = ConvoScreen:new {
	id = "initial_train_components",
	leftDialog = "@conversation/naboo_privateer_trainer_2:s_8ad6a62e", -- You bet! New components should make your ship more than a match against a dozen Ay'Nat Ghost Fighters!
	stopConversation = "true",
	options = {}
}
kaydine_convo_template:addScreen(initial_train_components);

initial_train_techniques = ConvoScreen:new {
	id = "initial_train_techniques",
	leftDialog = "@conversation/naboo_privateer_trainer_2:s_f32117e", -- You bet! New defense procedures should make you more than a match against a dozen Ay'Nat Ghost Fighters!
	stopConversation = "true",
	options = {}
}
kaydine_convo_template:addScreen(initial_train_techniques);

initial_train_algorithms = ConvoScreen:new {
	id = "initial_train_algorithms",
	leftDialog = "@conversation/naboo_privateer_trainer_2:s_fd75abb", -- You bet! New droid algorithms in there should make you more than a match against a dozen Ay'Nat Ghost Fighters!
	stopConversation = "true",
	options = {}
}
kaydine_convo_template:addScreen(initial_train_algorithms);

-- Mission 2 training screens
mission2_train_fighters = ConvoScreen:new {
	id = "mission2_train_fighters",
	leftDialog = "@conversation/naboo_privateer_trainer_2:s_4aa3066e", -- Ah yes! Good choice!
	stopConversation = "true",
	options = {}
}
kaydine_convo_template:addScreen(mission2_train_fighters);

mission2_train_components = ConvoScreen:new {
	id = "mission2_train_components",
	leftDialog = "@conversation/naboo_privateer_trainer_2:s_8ad6a62e", -- You bet! New components...
	stopConversation = "true",
	options = {}
}
kaydine_convo_template:addScreen(mission2_train_components);

mission2_train_techniques = ConvoScreen:new {
	id = "mission2_train_techniques",
	leftDialog = "@conversation/naboo_privateer_trainer_2:s_f32117e", -- You bet! New defense procedures...
	stopConversation = "true",
	options = {}
}
kaydine_convo_template:addScreen(mission2_train_techniques);

mission2_train_algorithms = ConvoScreen:new {
	id = "mission2_train_algorithms",
	leftDialog = "@conversation/naboo_privateer_trainer_2:s_fd75abb", -- You bet! New droid algorithms...
	stopConversation = "true",
	options = {}
}
kaydine_convo_template:addScreen(mission2_train_algorithms);

-- Mission 3 training screens
mission3_train_fighters = ConvoScreen:new {
	id = "mission3_train_fighters",
	leftDialog = "@conversation/naboo_privateer_trainer_2:s_4aa3066e",
	stopConversation = "true",
	options = {}
}
kaydine_convo_template:addScreen(mission3_train_fighters);

mission3_train_components = ConvoScreen:new {
	id = "mission3_train_components",
	leftDialog = "@conversation/naboo_privateer_trainer_2:s_8ad6a62e",
	stopConversation = "true",
	options = {}
}
kaydine_convo_template:addScreen(mission3_train_components);

mission3_train_techniques = ConvoScreen:new {
	id = "mission3_train_techniques",
	leftDialog = "@conversation/naboo_privateer_trainer_2:s_f32117e",
	stopConversation = "true",
	options = {}
}
kaydine_convo_template:addScreen(mission3_train_techniques);

mission3_train_algorithms = ConvoScreen:new {
	id = "mission3_train_algorithms",
	leftDialog = "@conversation/naboo_privateer_trainer_2:s_fd75abb",
	stopConversation = "true",
	options = {}
}
kaydine_convo_template:addScreen(mission3_train_algorithms);

-- Mission 4 training screens
mission4_train_fighters = ConvoScreen:new {
	id = "mission4_train_fighters",
	leftDialog = "@conversation/naboo_privateer_trainer_2:s_4aa3066e",
	stopConversation = "true",
	options = {}
}
kaydine_convo_template:addScreen(mission4_train_fighters);

mission4_train_components = ConvoScreen:new {
	id = "mission4_train_components",
	leftDialog = "@conversation/naboo_privateer_trainer_2:s_8ad6a62e",
	stopConversation = "true",
	options = {}
}
kaydine_convo_template:addScreen(mission4_train_components);

mission4_train_techniques = ConvoScreen:new {
	id = "mission4_train_techniques",
	leftDialog = "@conversation/naboo_privateer_trainer_2:s_f32117e",
	stopConversation = "true",
	options = {}
}
kaydine_convo_template:addScreen(mission4_train_techniques);

mission4_train_algorithms = ConvoScreen:new {
	id = "mission4_train_algorithms",
	leftDialog = "@conversation/naboo_privateer_trainer_2:s_fd75abb",
	stopConversation = "true",
	options = {}
}
kaydine_convo_template:addScreen(mission4_train_algorithms);

-- Final training screens
final_train_fighters = ConvoScreen:new {
	id = "final_train_fighters",
	leftDialog = "@conversation/naboo_privateer_trainer_2:s_4aa3066e",
	stopConversation = "true",
	options = {}
}
kaydine_convo_template:addScreen(final_train_fighters);

final_train_components = ConvoScreen:new {
	id = "final_train_components",
	leftDialog = "@conversation/naboo_privateer_trainer_2:s_8ad6a62e",
	stopConversation = "true",
	options = {}
}
kaydine_convo_template:addScreen(final_train_components);

final_train_techniques = ConvoScreen:new {
	id = "final_train_techniques",
	leftDialog = "@conversation/naboo_privateer_trainer_2:s_f32117e",
	stopConversation = "true",
	options = {}
}
kaydine_convo_template:addScreen(final_train_techniques);

final_train_algorithms = ConvoScreen:new {
	id = "final_train_algorithms",
	leftDialog = "@conversation/naboo_privateer_trainer_2:s_fd75abb",
	stopConversation = "true",
	options = {}
}
kaydine_convo_template:addScreen(final_train_algorithms);

-- First Mission: Disable Ay'Nat Captain
first_mission = ConvoScreen:new {
	id = "first_mission",
	leftDialog = "@conversation/naboo_privateer_trainer_2:s_130b925b", -- We'll need you to catch up to the Ay'Nat Captain's personal starship... a rather fast vessel! Disable him, and protect the RSF Boarding Team while they arrest him.
	stopConversation = "false",
	options = {
		{"@conversation/naboo_privateer_trainer_2:s_1b428a9f", "start_first_mission"}, -- Yes, Captain. I'm ready.
		{"@conversation/naboo_privateer_trainer_2:s_1c2b565d", "not_ready"}, -- Not quite yet, sir.
	}
}
kaydine_convo_template:addScreen(first_mission);

failed_first_mission = ConvoScreen:new {
	id = "failed_first_mission",
	leftDialog = "@conversation/naboo_privateer_trainer_2:s_65042122", -- So, I hear you were not able to destroy all three of the Ay'Nat Legion's outlaw fighters. But don't worry...
	stopConversation = "false",
	options = {
		{"@conversation/naboo_privateer_trainer_2:s_4a1d2431", "try_first_mission"}, -- Yes, I'm ready.
		{"@conversation/naboo_privateer_trainer_2:s_1c2b565d", "not_ready"}, -- Not quite yet, sir.
	}
}
kaydine_convo_template:addScreen(failed_first_mission);

start_first_mission = ConvoScreen:new {
	id = "start_first_mission",
	leftDialog = "@conversation/naboo_privateer_trainer_2:s_a80d9308", -- Good luck!
	stopConversation = "true",
	options = {}
}
kaydine_convo_template:addScreen(start_first_mission);

try_first_mission = ConvoScreen:new {
	id = "try_first_mission",
	leftDialog = "@conversation/naboo_privateer_trainer_2:s_726bdb69", -- Good! Then let's get you back out there right away!
	stopConversation = "true",
	options = {}
}
kaydine_convo_template:addScreen(try_first_mission);

cant_wait_first = ConvoScreen:new {
	id = "cant_wait_first",
	leftDialog = "@conversation/naboo_privateer_trainer_2:s_a80d9308", -- Good luck!
	stopConversation = "true",
	options = {}
}
kaydine_convo_template:addScreen(cant_wait_first);

-- First Mission Complete
complete_first_mission = ConvoScreen:new {
	id = "complete_first_mission",
	leftDialog = "@conversation/naboo_privateer_trainer_2:s_9abb9538", -- Fantastic work! The space station holocomm'd me regarding a massive battle between a lone RSF pilot...
	stopConversation = "false",
	options = {
		{"@conversation/naboo_privateer_trainer_2:s_aa77ffde", "according_to_plan"}, -- It was nothing
	}
}
kaydine_convo_template:addScreen(complete_first_mission);

according_to_plan = ConvoScreen:new {
	id = "according_to_plan",
	leftDialog = "@conversation/naboo_privateer_trainer_2:s_8d90962a", -- Nonsense! You've earned this.
	stopConversation = "true",
	options = {}
}
kaydine_convo_template:addScreen(according_to_plan);

first_mission_success = ConvoScreen:new {
	id = "first_mission_success",
	leftDialog = "@conversation/naboo_privateer_trainer_2:s_9248b2ba", -- Well you've certainly earned it. I'll talk to you later.
	stopConversation = "true",
	options = {}
}
kaydine_convo_template:addScreen(first_mission_success);

-- Second Mission: Escort Prison Ship
second_mission = ConvoScreen:new {
	id = "second_mission",
	leftDialog = "@conversation/naboo_privateer_trainer_2:s_ec671b3f", -- Well, the Empire has demanded that the prisoners be turned over for questioning.
	stopConversation = "false",
	options = {
		{"@conversation/naboo_privateer_trainer_2:s_2d67b7a8", "accept_escort_details"}, -- Where do I come in?
		{"@conversation/naboo_privateer_trainer_2:s_1c2b565d", "not_ready"}, -- Not quite yet, sir.
	}
}
kaydine_convo_template:addScreen(second_mission);

accept_escort_details = ConvoScreen:new {
	id = "accept_escort_details",
	leftDialog = "@conversation/naboo_privateer_trainer_2:s_287eca83", -- We needed to get that prisoner ship out of the Naboo system to keep the Empire happy.
	stopConversation = "false",
	options = {
		{"@conversation/naboo_privateer_trainer_2:s_1b428a9f", "accept_escort"}, -- Yes, Captain. I'm ready.
		{"@conversation/naboo_privateer_trainer_2:s_1c2b565d", "not_ready"}, -- Not quite yet, sir.
	}
}
kaydine_convo_template:addScreen(accept_escort_details);

failed_second_mission = ConvoScreen:new {
	id = "failed_second_mission",
	leftDialog = "@conversation/naboo_privateer_trainer_2:s_6da2c92b", -- I realize there were a lot of fighters up there to deal with... but nothing changes the fact that the Ay'Nat Legion must go!
	stopConversation = "false",
	options = {
		{"@conversation/naboo_privateer_trainer_2:s_4a1d2431", "back_to_escort"}, -- Yes, I'm ready.
		{"@conversation/naboo_privateer_trainer_2:s_1c2b565d", "not_ready"}, -- Not quite yet, sir.
	}
}
kaydine_convo_template:addScreen(failed_second_mission);

accept_escort = ConvoScreen:new {
	id = "accept_escort",
	leftDialog = "@conversation/naboo_privateer_trainer_2:s_57ba8a73", -- In that case, let's get you back up there. This time make sure the RSF prison ship makes it out of the system.
	stopConversation = "true",
	options = {}
}
kaydine_convo_template:addScreen(accept_escort);

back_to_escort = ConvoScreen:new {
	id = "back_to_escort",
	leftDialog = "@conversation/naboo_privateer_trainer_2:s_57ba8a73", -- In that case, let's get you back up there. This time make sure the RSF prison ship makes it out of the system.
	stopConversation = "true",
	options = {}
}
kaydine_convo_template:addScreen(back_to_escort);

now_is_good = ConvoScreen:new {
	id = "now_is_good",
	leftDialog = "@conversation/naboo_privateer_trainer_2:s_d586f458", -- Excellent! Get back out there and do me proud!
	stopConversation = "true",
	options = {}
}
kaydine_convo_template:addScreen(now_is_good);

be_smarter = ConvoScreen:new {
	id = "be_smarter",
	leftDialog = "@conversation/naboo_privateer_trainer_2:s_85263c6d", -- We can't afford to botch this opportunity!
	stopConversation = "true",
	options = {}
}
kaydine_convo_template:addScreen(be_smarter);

-- Second Mission Complete
complete_second_mission = ConvoScreen:new {
	id = "complete_second_mission",
	leftDialog = "@conversation/naboo_privateer_trainer_2:s_70287826", -- Now that's showing some excellent leadership potential! You've really earned your pay this time.
	stopConversation = "false",
	options = {
		{"@conversation/naboo_privateer_trainer_2:s_5fa9a5d3", "duty_calls"}, -- Thanks
	}
}
kaydine_convo_template:addScreen(complete_second_mission);

duty_calls = ConvoScreen:new {
	id = "duty_calls",
	leftDialog = "@conversation/naboo_privateer_trainer_2:s_9248b2ba", -- Well you've certainly earned it. I'll talk to you later.
	stopConversation = "true",
	options = {}
}
kaydine_convo_template:addScreen(duty_calls);

here_is_pay = ConvoScreen:new {
	id = "here_is_pay",
	leftDialog = "@conversation/naboo_privateer_trainer_2:s_ae21cb72", -- Thanks to you! Great work, %NU. You've really earned these credits.
	stopConversation = "true",
	options = {}
}
kaydine_convo_template:addScreen(here_is_pay);

-- Third Mission: Recover Stolen Ships
third_mission = ConvoScreen:new {
	id = "third_mission",
	leftDialog = "@conversation/naboo_privateer_trainer_2:s_35fb22d6", -- The Royal family has increased security in the wake of recent theft. A number of Her Majesty's personal starships have gone missing.
	stopConversation = "false",
	options = {
		{"@conversation/naboo_privateer_trainer_2:s_a6c7fa2b", "accept_inspect"}, -- What are the details?
		{"@conversation/naboo_privateer_trainer_2:s_1c2b565d", "not_ready"}, -- Not quite yet, sir.
	}
}
kaydine_convo_template:addScreen(third_mission);

failed_third_mission = ConvoScreen:new {
	id = "failed_third_mission",
	leftDialog = "@conversation/naboo_privateer_trainer_2:s_85263c6d", -- We can't afford to botch this opportunity! RSF has a new battery of information... and another chance...
	stopConversation = "false",
	options = {
		{"@conversation/naboo_privateer_trainer_2:s_4a1d2431", "on_your_way"}, -- Yes, I'm ready.
		{"@conversation/naboo_privateer_trainer_2:s_1c2b565d", "not_ready"}, -- Not quite yet, sir.
	}
}
kaydine_convo_template:addScreen(failed_third_mission);

accept_inspect = ConvoScreen:new {
	id = "accept_inspect",
	leftDialog = "@conversation/naboo_privateer_trainer_2:s_3cef63a0", -- Fly out to your choice of strike points... look for Ay'Nat Legion fighters.
	stopConversation = "true",
	options = {}
}
kaydine_convo_template:addScreen(accept_inspect);

on_your_way = ConvoScreen:new {
	id = "on_your_way",
	leftDialog = "@conversation/naboo_privateer_trainer_2:s_726bdb69", -- Good! Then let's get you back out there right away!
	stopConversation = "true",
	options = {}
}
kaydine_convo_template:addScreen(on_your_way);

take_it_serious = ConvoScreen:new {
	id = "take_it_serious",
	leftDialog = "@conversation/naboo_privateer_trainer_2:s_bb291959", -- Excellent! Be careful up there! Those Ay'Nat outlaws are deadly enemies!
	stopConversation = "true",
	options = {}
}
kaydine_convo_template:addScreen(take_it_serious);

bad_liar = ConvoScreen:new {
	id = "bad_liar",
	leftDialog = "@conversation/naboo_privateer_trainer_2:s_da8818c5", -- If you say so, %NU. I still say it's an impressive accomplishment.
	stopConversation = "true",
	options = {}
}
kaydine_convo_template:addScreen(bad_liar);

-- Third Mission Complete
complete_third_mission = ConvoScreen:new {
	id = "complete_third_mission",
	leftDialog = "@conversation/naboo_privateer_trainer_2:s_ef08027f", -- That's excellent news for the peaceful citizens of the Naboo system.
	stopConversation = "false",
	options = {
		{"@conversation/naboo_privateer_trainer_2:s_5fa9a5d3", "turnover_intelligence"}, -- Thanks
	}
}
kaydine_convo_template:addScreen(complete_third_mission);

turnover_intelligence = ConvoScreen:new {
	id = "turnover_intelligence",
	leftDialog = "@conversation/naboo_privateer_trainer_2:s_9248b2ba", -- Well you've certainly earned it. I'll talk to you later.
	stopConversation = "true",
	options = {}
}
kaydine_convo_template:addScreen(turnover_intelligence);

-- Fourth Mission: Hunt Ace Outlaws
fourth_mission = ConvoScreen:new {
	id = "fourth_mission",
	leftDialog = "@conversation/naboo_privateer_trainer_2:s_c4ef0e93", -- We need you to slip in to Ay'Nat-controlled space, and hunt down a trio of Ace outlaws.
	stopConversation = "false",
	options = {
		{"@conversation/naboo_privateer_trainer_2:s_1b428a9f", "accept_assassinate"}, -- Yes, Captain. I'm ready.
		{"@conversation/naboo_privateer_trainer_2:s_1c2b565d", "not_ready"}, -- Not quite yet, sir.
	}
}
kaydine_convo_template:addScreen(fourth_mission);

failed_fourth_mission = ConvoScreen:new {
	id = "failed_fourth_mission",
	leftDialog = "@conversation/naboo_privateer_trainer_2:s_65042122", -- So, I hear you were not able to destroy all three of the Ay'Nat Legion's outlaw fighters. But don't worry...
	stopConversation = "false",
	options = {
		{"@conversation/naboo_privateer_trainer_2:s_4a1d2431", "nonsense"}, -- Yes, I'm ready.
		{"@conversation/naboo_privateer_trainer_2:s_1c2b565d", "not_ready"}, -- Not quite yet, sir.
	}
}
kaydine_convo_template:addScreen(failed_fourth_mission);

accept_assassinate = ConvoScreen:new {
	id = "accept_assassinate",
	leftDialog = "@conversation/naboo_privateer_trainer_2:s_ff45f1fd", -- Good luck to you, Captain %TU!
	stopConversation = "true",
	options = {}
}
kaydine_convo_template:addScreen(accept_assassinate);

nonsense = ConvoScreen:new {
	id = "nonsense",
	leftDialog = "@conversation/naboo_privateer_trainer_2:s_726bdb69", -- Good! Then let's get you back out there right away!
	stopConversation = "true",
	options = {}
}
kaydine_convo_template:addScreen(nonsense);

let_me_know = ConvoScreen:new {
	id = "let_me_know",
	leftDialog = "@conversation/naboo_privateer_trainer_2:s_d586f458", -- Excellent! Get back out there and do me proud!
	stopConversation = "true",
	options = {}
}
kaydine_convo_template:addScreen(let_me_know);

report_back_success = ConvoScreen:new {
	id = "report_back_success",
	leftDialog = "@conversation/naboo_privateer_trainer_2:s_a80d9308", -- Good luck!
	stopConversation = "true",
	options = {}
}
kaydine_convo_template:addScreen(report_back_success);

key_to_success = ConvoScreen:new {
	id = "key_to_success",
	leftDialog = "@conversation/naboo_privateer_trainer_2:s_225b33f", -- Good luck, son!
	stopConversation = "true",
	options = {}
}
kaydine_convo_template:addScreen(key_to_success);

just_malfunctioned = ConvoScreen:new {
	id = "just_malfunctioned",
	leftDialog = "@conversation/naboo_privateer_trainer_2:s_b0ab3e88", -- Oh! You had me going there. Well you've earned that, anyway.
	stopConversation = "true",
	options = {}
}
kaydine_convo_template:addScreen(just_malfunctioned);

-- Fourth Mission Complete
complete_fourth_mission = ConvoScreen:new {
	id = "complete_fourth_mission",
	leftDialog = "@conversation/naboo_privateer_trainer_2:s_76e6f264", -- Captain %TU! You are doing a fantastic job! I think you've grown enough as a pilot to warrant advancement.
	stopConversation = "false",
	options = {
		{"@conversation/naboo_privateer_trainer_2:s_5fa9a5d3", "fourth_mission_success"}, -- Thanks
	}
}
kaydine_convo_template:addScreen(complete_fourth_mission);

fourth_mission_success = ConvoScreen:new {
	id = "fourth_mission_success",
	leftDialog = "@conversation/naboo_privateer_trainer_2:s_aa83c988", -- Head deeper into the palace, my friend! Look for Commander Dulios.
	stopConversation = "true",
	options = {}
}
kaydine_convo_template:addScreen(fourth_mission_success);

-- Not ready
not_ready = ConvoScreen:new {
	id = "not_ready",
	leftDialog = "@conversation/naboo_privateer_trainer_2:s_943f6352", -- Alright. Hurry up and come back when you're ready.
	stopConversation = "true",
	options = {}
}
kaydine_convo_template:addScreen(not_ready);

addConversationTemplate("kaydine_convo_template", kaydine_convo_template)
