rsf_tier1_convo_template = ConvoTemplate:new {
	initialScreen = "",
	templateType = "Lua",
	luaClassHandler = "rsfTier1ConvoHandler",
	screens = {}
}

-- JTL Disabled
no_jtl = ConvoScreen:new {
	id = "no_jtl",
	leftDialog = "@conversation/naboo_privateer_trainer_1:s_7c1fe68f", -- Sorry, but I can't chit-chat with you. I'm busy doing important Royal Security work here.
	stopConversation = "true",
	options = {}
}
rsf_tier1_convo_template:addScreen(no_jtl);

-- Rebel Pilot
rebel_pilot = ConvoScreen:new {
	id = "rebel_pilot",
	leftDialog = "@conversation/naboo_privateer_trainer_1:s_72f94b8e", -- I think you're a pilot for the Rebel Alliance! Look, the Royal Security Forces don't have any use for the likes of you. I think you should leave now.
	stopConversation = "true",
	options = {}
}
rsf_tier1_convo_template:addScreen(rebel_pilot);

-- Imperial Pilot
imperial_pilot = ConvoScreen:new {
	id = "imperial_pilot",
	leftDialog = "@conversation/naboo_privateer_trainer_1:s_7217d77", -- Greetings officer! Nothing to worry about here, we've got everything under control.
	stopConversation = "true",
	options = {}
}
rsf_tier1_convo_template:addScreen(imperial_pilot);

-- Non-RSF Neutral Pilot
non_rsf_pilot = ConvoScreen:new {
	id = "non_rsf_pilot",
	leftDialog = "@conversation/naboo_privateer_trainer_1:s_6b25cc31", -- I've heard you're quite a pilot. What brings you to speak with the Royal Security Forces?
	stopConversation = "false",
	options = {
		{"@conversation/naboo_privateer_trainer_1:s_c1ff5062", "non_rsf_duty_missions"}, -- I'm looking for a mission. Do you have any?
	}
}
rsf_tier1_convo_template:addScreen(non_rsf_pilot);

non_rsf_duty_missions = ConvoScreen:new {
	id = "non_rsf_duty_missions",
	leftDialog = "@conversation/naboo_privateer_trainer_1:s_38d8b2c4", -- I appreciate your enthusiasm, but unless you're a member of the RSF, I'm afraid I cannot help you. Talk to your own contacts if you're looking for a mission.
	stopConversation = "true",
	options = {}
}
rsf_tier1_convo_template:addScreen(non_rsf_duty_missions);

-- Recruitment
recruitment = ConvoScreen:new {
	id = "recruitment",
	leftDialog = "@conversation/naboo_privateer_trainer_1:s_465e6eeb", -- Greetings citizen. Are you here to join the Royal Security Forces?
	stopConversation = "false",
	options = {
		{"@conversation/naboo_privateer_trainer_1:s_36a4e374", "yes_enlist"}, -- Yes, I am.
		{"@conversation/naboo_privateer_trainer_1:s_4c695dbd", "no_enlist"}, -- No.
	}
}
rsf_tier1_convo_template:addScreen(recruitment);

yes_enlist = ConvoScreen:new {
	id = "yes_enlist",
	leftDialog = "@conversation/naboo_privateer_trainer_1:s_c19e20c9", -- Excellent. Consider yourself enlisted. Do you have a starship suitable for service?
	stopConversation = "false",
	options = {
		-- Options added via handler
	}
}
rsf_tier1_convo_template:addScreen(yes_enlist);

no_enlist = ConvoScreen:new {
	id = "no_enlist",
	leftDialog = "@conversation/naboo_privateer_trainer_1:s_f5f16210", -- Very well. Come back and speak with me when you're ready.
	stopConversation = "true",
	options = {}
}
rsf_tier1_convo_template:addScreen(no_enlist);

-- No Ship
no_ship = ConvoScreen:new {
	id = "no_ship",
	leftDialog = "@conversation/naboo_privateer_trainer_1:s_b24af40a", -- You're going to need a ship, of course. I'll add these control codes for a basic one to your datapad. You should consider upgrading to a better ship soon, though.
	stopConversation = "false",
	options = {
		{"@conversation/naboo_privateer_trainer_1:s_b9b27823", "ready_first_assignment"}, -- Thank you.
		{"@conversation/naboo_privateer_trainer_1:s_4358efe9", "where_is_ship"}, -- Where is my ship?
	}
}
rsf_tier1_convo_template:addScreen(no_ship);

yes_ship = ConvoScreen:new {
	id = "yes_ship",
	leftDialog = "@conversation/naboo_privateer_trainer_1:s_5ed33504", -- Excellent. Sounds like you're all set then. Are you ready for your first assignment?
	stopConversation = "false",
	options = {
		{"@conversation/naboo_privateer_trainer_1:s_b3a9fd05", "yes_im_ready"}, -- Sure!
		{"@conversation/naboo_privateer_trainer_1:s_68660d24", "not_ready"}, -- I need to take care of some things first.
	}
}
rsf_tier1_convo_template:addScreen(yes_ship);

where_is_ship = ConvoScreen:new {
	id = "where_is_ship",
	leftDialog = "@conversation/naboo_privateer_trainer_1:s_41c478b2", -- Theed Hangar. Leave the palace the way you came. Take a left when you hit the plaza. Then follow the roads until you reach the power complex. Theed Hangar is on the opposite side of this building. Go inside the hangar and look for the 'starship terminals.' Use one of these terminals to launch your starship.
	stopConversation = "false",
	options = {
		{"@conversation/naboo_privateer_trainer_1:s_b3a9fd05", "yes_im_ready"}, -- Sure!
		{"@conversation/naboo_privateer_trainer_1:s_85dd7d6c", "how_get_back"}, -- How do I get back?
	}
}
rsf_tier1_convo_template:addScreen(where_is_ship);

how_get_back = ConvoScreen:new {
	id = "how_get_back",
	leftDialog = "@conversation/naboo_privateer_trainer_1:s_1664d807", -- You must communicate with the Naboo space station and request permission to land. Fortunately all of the new starship navicomputers automatically add a 'launch waypoint' to your datapad when you take off. Find your way back to this point, fly up to the space station, communicate with them, and ask for landing clearance.
	stopConversation = "false",
	options = {
		{"@conversation/naboo_privateer_trainer_1:s_b3a9fd05", "yes_im_ready"}, -- Sure!
	}
}
rsf_tier1_convo_template:addScreen(how_get_back);

ready_first_assignment = ConvoScreen:new {
	id = "ready_first_assignment",
	leftDialog = "@conversation/naboo_privateer_trainer_1:s_eed2fe3e", -- Think nothing of it. Are you ready for your first assignment?
	stopConversation = "false",
	options = {
		{"@conversation/naboo_privateer_trainer_1:s_b3a9fd05", "yes_im_ready"}, -- Sure!
		{"@conversation/naboo_privateer_trainer_1:s_68660d24", "not_ready"}, -- I need to take care of some things first.
	}
}
rsf_tier1_convo_template:addScreen(ready_first_assignment);

not_ready = ConvoScreen:new {
	id = "not_ready",
	leftDialog = "@conversation/naboo_privateer_trainer_1:s_792ad840", -- OK, OK. Come back when you're ready.
	stopConversation = "true",
	options = {}
}
rsf_tier1_convo_template:addScreen(not_ready);

-- First Mission
yes_im_ready = ConvoScreen:new {
	id = "yes_im_ready",
	leftDialog = "@conversation/naboo_privateer_trainer_1:s_904d71cf", -- Ok! Ready for an assignment already, eh? Well listen up! We've had reports of pirates in the system and we want you to run a patrol. Just make sure everything's on the up and up. This ought to be a piece of cake.
	stopConversation = "false",
	options = {
		{"@conversation/naboo_privateer_trainer_1:s_1db37a0f", "go_patrol"}, -- I'm off!
		{"@conversation/naboo_privateer_trainer_1:s_60c4f974", "where_go"}, -- Where do I go?
	}
}
rsf_tier1_convo_template:addScreen(yes_im_ready);

go_patrol = ConvoScreen:new {
	id = "go_patrol",
	leftDialog = "@conversation/naboo_privateer_trainer_1:s_b02e116", -- That's the spirit. Good luck!
	stopConversation = "true",
	options = {}
}
rsf_tier1_convo_template:addScreen(go_patrol);

where_go = ConvoScreen:new {
	id = "where_go",
	leftDialog = "@conversation/naboo_privateer_trainer_1:s_8853a92c", -- You've got your assignment, and the control device for your ship in your datapad. Go to Theed Hangar and access the terminal to launch into space.
	stopConversation = "true",
	options = {}
}
rsf_tier1_convo_template:addScreen(where_go);

-- Has Active Mission
has_mission = ConvoScreen:new {
	id = "has_mission",
	leftDialog = "@conversation/naboo_privateer_trainer_1:s_61036267", -- You've got your orders! Stop standing around and get back on the job.
	stopConversation = "true",
	options = {}
}
rsf_tier1_convo_template:addScreen(has_mission);

-- First Assignment In Progress
first_assignment = ConvoScreen:new {
	id = "first_assignment",
	leftDialog = "@conversation/naboo_privateer_trainer_1:s_443c036b", -- All I asked was for you to complete one simple patrol. What's the malfunction? Get back out there and secure the area!
	stopConversation = "false",
	options = {
		{"@conversation/naboo_privateer_trainer_1:s_aec5c3dd", "was_attacked"}, -- It wasn't my fault. I was attacked!
		{"@conversation/naboo_privateer_trainer_1:s_ea059f38", "will_do"}, -- Will do!
	}
}
rsf_tier1_convo_template:addScreen(first_assignment);

was_attacked = ConvoScreen:new {
	id = "was_attacked",
	leftDialog = "@conversation/naboo_privateer_trainer_1:s_73f727e7", -- Now hold on, there... there's no reason to fly off the handle. You've got a job to do, that's all. Now get out there and do it. And... good luck!
	stopConversation = "true",
	options = {}
}
rsf_tier1_convo_template:addScreen(was_attacked);

will_do = ConvoScreen:new {
	id = "will_do",
	leftDialog = "@conversation/naboo_privateer_trainer_1:s_b9c77549", -- That's what I want to hear. Now go!
	stopConversation = "true",
	options = {}
}
rsf_tier1_convo_template:addScreen(will_do);

-- Quest 1 Complete
excellent_work = ConvoScreen:new {
	id = "excellent_work",
	leftDialog = "@conversation/naboo_privateer_trainer_1:s_5df0371b", -- Excellent work! It's a good thing we sent you on that patrol. Take this as your payment. If you want another assignment, then just come talk to me.
	stopConversation = "false",
	options = {
		{"@conversation/naboo_privateer_trainer_1:s_3f49e786", "train_me2"}, -- Great!
		{"@conversation/naboo_privateer_trainer_1:s_9237617f", "no_training_yet"}, -- What about training?
	}
}
rsf_tier1_convo_template:addScreen(excellent_work);

no_training_yet = ConvoScreen:new {
	id = "no_training_yet",
	leftDialog = "@conversation/naboo_privateer_trainer_1:s_8fb73c4", -- I'll train you... AFTER you complete a few assignments for me. Now about that patrol...
	stopConversation = "false",
	options = {
		{"@conversation/naboo_privateer_trainer_1:s_3f49e786", "train_me2"}, -- Great!
	}
}
rsf_tier1_convo_template:addScreen(no_training_yet);

-- Quest 2 Start
train_me2 = ConvoScreen:new {
	id = "train_me2",
	leftDialog = "@conversation/naboo_privateer_trainer_1:s_bcdb501b", -- Ready for your next assignment? Good! Obviously we can't allow that random attack on you to stand, so now we need to send a message to those pirates. Go destroy four of the Black Sun pirates... That should send a clear message that we're not going to tolerate their activities.
	stopConversation = "false",
	options = {
		{"@conversation/naboo_privateer_trainer_1:s_7b3b28bf", "go_destroy"}, -- Go!
	}
}
rsf_tier1_convo_template:addScreen(train_me2);

go_destroy = ConvoScreen:new {
	id = "go_destroy",
	leftDialog = "@conversation/naboo_privateer_trainer_1:s_6575e5d0", -- Get up there and put those Black Sun in their place.
	stopConversation = "true",
	options = {}
}
rsf_tier1_convo_template:addScreen(go_destroy);

-- Quest 2 Complete
excellent_work2 = ConvoScreen:new {
	id = "excellent_work2",
	leftDialog = "@conversation/naboo_privateer_trainer_1:s_3d6c25c7", -- Good work, %NU. Here's your payment.
	stopConversation = "false",
	options = {
		{"@conversation/naboo_privateer_trainer_1:s_c4682ea6", "train_me3"}, -- Thanks!
	}
}
rsf_tier1_convo_template:addScreen(excellent_work2);

-- Quest 3 Start
train_me3 = ConvoScreen:new {
	id = "train_me3",
	leftDialog = "@conversation/naboo_privateer_trainer_1:s_c29502", -- Right, back to work! Now that you've eliminated some of the riffraff out there, we want you to run a patrol and make sure there are no more of these criminals in the area.
	stopConversation = "false",
	options = {
		{"@conversation/naboo_privateer_trainer_1:s_ea059f38", "go_patrol3"}, -- Will do!
	}
}
rsf_tier1_convo_template:addScreen(train_me3);

go_patrol3 = ConvoScreen:new {
	id = "go_patrol3",
	leftDialog = "@conversation/naboo_privateer_trainer_1:s_b02e116", -- That's the spirit. Good luck!
	stopConversation = "true",
	options = {}
}
rsf_tier1_convo_template:addScreen(go_patrol3);

-- Quest 3 Complete (with bandolier reward)
excellent_work3 = ConvoScreen:new {
	id = "excellent_work3",
	leftDialog = "@conversation/naboo_privateer_trainer_1:s_cd397d97", -- That was a quick reaction to pick up the escort. It is a good thing we sent you on that patrol. The pilot sent over some money for you to cover any repairs you might have, and here's something to help you organize your things.
	stopConversation = "false",
	options = {
		{"@conversation/naboo_privateer_trainer_1:s_1c8bddbb", "what_is_it"}, -- What is it?
		{"@conversation/naboo_privateer_trainer_1:s_e9c7c6bb", "train_me4"}, -- That will come in handy.
	}
}
rsf_tier1_convo_template:addScreen(excellent_work3);

what_is_it = ConvoScreen:new {
	id = "what_is_it",
	leftDialog = "@conversation/naboo_privateer_trainer_1:s_d05d7112", -- It's a mercenary bandolier. Pretty popular item among the freelance pilot crowd. Really handy to help you keep your things organized.
	stopConversation = "false",
	options = {
		{"@conversation/naboo_privateer_trainer_1:s_e9c7c6bb", "train_me4"}, -- That will come in handy.
	}
}
rsf_tier1_convo_template:addScreen(what_is_it);

-- Quest 4 Start (Assassinate)
train_me4 = ConvoScreen:new {
	id = "train_me4",
	leftDialog = "@conversation/naboo_privateer_trainer_1:s_966bc2b6", -- I don't know about you, but I've had about enough of these criminals operating in our system! We want you to take out their leader this time, and use all necessary force to defeat any wingmen that happen to be with him, too.
	stopConversation = "false",
	options = {
		{"@conversation/naboo_privateer_trainer_1:s_7736f08b", "go_assassinate"}, -- Now it's personal.
		{"@conversation/naboo_privateer_trainer_1:s_7478cd28", "will_train"}, -- Will you train me after this?
	}
}
rsf_tier1_convo_template:addScreen(train_me4);

will_train = ConvoScreen:new {
	id = "will_train",
	leftDialog = "@conversation/naboo_privateer_trainer_1:s_3175b359", -- Yes, yes, you have my word. Take out that leader and I will train you to be a better pilot.
	stopConversation = "false",
	options = {
		{"@conversation/naboo_privateer_trainer_1:s_7736f08b", "go_assassinate"}, -- Now it's personal.
	}
}
rsf_tier1_convo_template:addScreen(will_train);

go_assassinate = ConvoScreen:new {
	id = "go_assassinate",
	leftDialog = "@conversation/naboo_privateer_trainer_1:s_b02e116", -- That's the spirit. Good luck!
	stopConversation = "true",
	options = {}
}
rsf_tier1_convo_template:addScreen(go_assassinate);

-- All Missions Complete - Ready for training
missions_complete = ConvoScreen:new {
	id = "missions_complete",
	leftDialog = "@conversation/naboo_privateer_trainer_1:s_6ea4aa1e", -- That's great work! With their leader destroyed, they're sure to be on the run. Let 'em go to Tatooine if they want to be criminals, but they're not going to aggress merchants while the RSF is on the job. Take these credits and get your ship repaired, if it needs it.
	stopConversation = "false",
	options = {
		{"@conversation/naboo_privateer_trainer_1:s_db74ddc6", "more_training"}, -- How about some training?
		{"@conversation/naboo_privateer_trainer_1:s_c4682ea6", "thanks_bye"}, -- Thanks!
	}
}
rsf_tier1_convo_template:addScreen(missions_complete);

thanks_bye = ConvoScreen:new {
	id = "thanks_bye",
	leftDialog = "@conversation/naboo_privateer_trainer_1:s_cd72f93", -- Good choice.
	stopConversation = "true",
	options = {}
}
rsf_tier1_convo_template:addScreen(thanks_bye);

-- Training Menu
more_training = ConvoScreen:new {
	id = "more_training",
	leftDialog = "@conversation/naboo_privateer_trainer_1:s_122b0165", -- You're really coming along as a pilot, %TU. I think you're ready for some more training. What interests you?
	stopConversation = "false",
	options = {
		-- Options added dynamically via handler
	}
}
rsf_tier1_convo_template:addScreen(more_training);

train_player_fighters = ConvoScreen:new {
	id = "train_player_fighters",
	leftDialog = "@conversation/naboo_privateer_trainer_1:s_cd72f93", -- Good choice.
	stopConversation = "true",
	options = {}
}
rsf_tier1_convo_template:addScreen(train_player_fighters);

train_player_component = ConvoScreen:new {
	id = "train_player_component",
	leftDialog = "@conversation/naboo_privateer_trainer_1:s_cd72f93", -- Good choice.
	stopConversation = "true",
	options = {}
}
rsf_tier1_convo_template:addScreen(train_player_component);

train_player_basics = ConvoScreen:new {
	id = "train_player_basics",
	leftDialog = "@conversation/naboo_privateer_trainer_1:s_cd72f93", -- Good choice.
	stopConversation = "true",
	options = {}
}
rsf_tier1_convo_template:addScreen(train_player_basics);

train_player_droid = ConvoScreen:new {
	id = "train_player_droid",
	leftDialog = "@conversation/naboo_privateer_trainer_1:s_cd72f93", -- Good choice.
	stopConversation = "true",
	options = {}
}
rsf_tier1_convo_template:addScreen(train_player_droid);

-- Duty Missions
duty_missions = ConvoScreen:new {
	id = "duty_missions",
	leftDialog = "@conversation/naboo_privateer_trainer_1:s_63336624", -- Ready for an assignment? We have some duty missions available.
	stopConversation = "false",
	options = {
		{"@conversation/naboo_privateer_trainer_1:s_e814cf37", "duty_options"}, -- I would like a duty mission.
		{"@conversation/naboo_privateer_trainer_1:s_6106187c", "what_is_duty"}, -- What is a duty mission?
		{"@conversation/naboo_privateer_trainer_1:s_2883b989", "not_ready"}, -- Not right now, thanks.
	}
}
rsf_tier1_convo_template:addScreen(duty_missions);

what_is_duty = ConvoScreen:new {
	id = "what_is_duty",
	leftDialog = "@conversation/naboo_privateer_trainer_1:s_a8cdf3dc", -- A duty mission is an open-ended task. That means that there is no true end to it, you just finish whenever you're ready. It's a good way to earn experience to prepare yourself for training. So, what do you say?
	stopConversation = "false",
	options = {
		{"@conversation/naboo_privateer_trainer_1:s_e814cf37", "duty_options"}, -- I would like a duty mission.
		{"@conversation/naboo_privateer_trainer_1:s_2883b989", "not_ready"}, -- Not right now, thanks.
	}
}
rsf_tier1_convo_template:addScreen(what_is_duty);

duty_options = ConvoScreen:new {
	id = "duty_options",
	leftDialog = "@conversation/naboo_privateer_trainer_1:s_e38f886b", -- Good, good. We have a couple to choose from. You can either fight the Black Sun menace in a Destroy Duty, or you can assist the merchant freighters with an Escort Duty.
	stopConversation = "false",
	options = {
		{"@conversation/naboo_privateer_trainer_1:s_40759c25", "destroy_duty"}, -- I want Destroy Duty
		{"@conversation/naboo_privateer_trainer_1:s_629c7d23", "escort_duty"}, -- I want Escort Duty
	}
}
rsf_tier1_convo_template:addScreen(duty_options);

destroy_duty = ConvoScreen:new {
	id = "destroy_duty",
	leftDialog = "@conversation/naboo_privateer_trainer_1:s_6575e5d0", -- Get up there and put those Black Sun in their place.
	stopConversation = "true",
	options = {}
}
rsf_tier1_convo_template:addScreen(destroy_duty);

escort_duty = ConvoScreen:new {
	id = "escort_duty",
	leftDialog = "@conversation/naboo_privateer_trainer_1:s_90b16aa7", -- We'll pay for every transport that makes it through.
	stopConversation = "true",
	options = {}
}
rsf_tier1_convo_template:addScreen(escort_duty);

-- Completed Tier 1 - Go to Captain Kaydine
completed_tier1 = ConvoScreen:new {
	id = "completed_tier1",
	leftDialog = "@conversation/naboo_privateer_trainer_1:s_7c4368e", -- You have accomplished all the tasks I have set for you. Are you ready for some more advanced work?
	stopConversation = "false",
	options = {
		{"@conversation/naboo_privateer_trainer_1:s_5c522568", "go_to_tier2"}, -- Yes, of course.
		{"@conversation/naboo_privateer_trainer_1:s_2883b989", "not_ready"}, -- Not right now, thanks.
	}
}
rsf_tier1_convo_template:addScreen(completed_tier1);

go_to_tier2 = ConvoScreen:new {
	id = "go_to_tier2",
	leftDialog = "@conversation/naboo_privateer_trainer_1:s_919029b", -- Go see Captain Kaydine. He is in one of the large meeting rooms upstairs here in the palace. Should be easy to find, just follow the ego.
	stopConversation = "true",
	options = {}
}
rsf_tier1_convo_template:addScreen(go_to_tier2);

addConversationTemplate("rsf_tier1_convo_template", rsf_tier1_convo_template);
