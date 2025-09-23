rikkh_convo_template = ConvoTemplate:new {
	initialScreen = "",
	templateType = "Lua",
	luaClassHandler = "rikkhConvoHandler",
	screens = {}
}

not_pilot = ConvoScreen:new {
	id = "not_pilot",
	leftDialog = "@conversation/corellia_privateer_trainer_2:s_5d3166b9", -- Everything is fine here. Nothing wrong at all.
	animation = "slow_down",
	stopConversation = "true",
	options = {}
}
rikkh_convo_template:addScreen(not_pilot);

pilot_not_corsec = ConvoScreen:new {
	id = "pilot_not_corsec",
	leftDialog = "@conversation/corellia_privateer_trainer_2:s_87bedbc6", -- "Well, if it isn't %TU. I've heard your name around the pilot's lounge a few times. What can I do for you?"
	animation = "wave2",
	stopConversation = "false",
	options = {
		{"@conversation/corellia_privateer_trainer_2:s_b978843d", "non_corsec_missions"}, --  I'm looking for a mission. Do you have anything I can do?
	}
}
rikkh_convo_template:addScreen(pilot_not_corsec);

finished_tier = ConvoScreen:new {
	id = "finished_tier",
	leftDialog = "@conversation/corellia_privateer_trainer_2:s_447b4291", -- %TU!  Long time no see.  I've heard Commander Ramna was quite pleased with your performance.
	animation = "greet",
	stopConversation = "false",
	options = {
		{"@conversation/corellia_privateer_trainer_2:s_6adec6b0", "cocky_pilot"}, -- Of course!
		{"@conversation/corellia_privateer_trainer_2:s_b6b1c40a", "mild_pilot"}, -- Not really
	}
}
rikkh_convo_template:addScreen(finished_tier);

cocky_pilot = ConvoScreen:new {
	id = "cocky_pilot",
	leftDialog = "@conversation/corellia_privateer_trainer_2:s_fc079db2", -- Still the cocky one, aren't you?  Anyway, what brings you back to Corellia?
	animation = "shake_head_disgust",
	stopConversation = "false",
	options = {
		{"@conversation/corellia_privateer_trainer_2:s_8125b624", "find_adwan"}, -- Looking for Adwan Turoldine
		{"@conversation/corellia_privateer_trainer_2:s_74f806bd", "just_visit"}, -- Just visiting
	}
}
rikkh_convo_template:addScreen(cocky_pilot);

mild_pilot = ConvoScreen:new {
	id = "mild_pilot",
	leftDialog = "@conversation/corellia_privateer_trainer_2:s_b9fa1db9", -- She can be a tough one to work with, but she's a good officer.  Anyway, what brings you back to Corellia?
	animation = "",
	stopConversation = "false",
	options = {
		{"@conversation/corellia_privateer_trainer_2:s_8125b624", "find_adwan"}, -- Looking for Adwan Turoldine
		{"@conversation/corellia_privateer_trainer_2:s_74f806bd", "just_visit"}, -- Just visiting
	}
}
rikkh_convo_template:addScreen(mild_pilot);

find_adwan = ConvoScreen:new {
	id = "find_adwan",
	leftDialog = "@conversation/corellia_privateer_trainer_2:s_a635c8aa", -- Turoldine?  Why... he's stationed on Dantooine, I think.  Not Corellia!  Look for him in the Mining outpost.
	animation = "rub_chin_thoughtful",
	stopConversation = "false",
	options = {
		{"@conversation/corellia_privateer_trainer_2:s_3b2fdc7f", "will_thanks"}, -- Will do!  Thanks!
	}
}
rikkh_convo_template:addScreen(find_adwan);

just_visit = ConvoScreen:new {
	id = "just_visit",
	leftDialog = "@conversation/corellia_privateer_trainer_2:s_7282cf08", -- Oh yes, I know what you mean... there's no place like Corellia.
	animation = "nod_head_multiple",
	stopConversation = "false",
	options = {
		{"@conversation/corellia_privateer_trainer_2:s_ea178ddb", "like_corellia"}, -- Talus is like Corellia
		{"@conversation/corellia_privateer_trainer_2:s_264b3207", "start_joke"}, -- You said it!
	}
}
rikkh_convo_template:addScreen(just_visit);

like_corellia = ConvoScreen:new {
	id = "like_corellia",
	leftDialog = "@conversation/corellia_privateer_trainer_2:s_530a5a44", -- Are you insane?  The weather there is terrible, the food tastes awful and the locals are all rude.  Talus is practically a backwater compared to Corellia.
	animation = "laugh",
	stopConversation = "false",
	options = {
		{"@conversation/corellia_privateer_trainer_2:s_8e2edcbe", "start_joke"}, -- If you say so.
	}
}
rikkh_convo_template:addScreen(like_corellia);

start_joke = ConvoScreen:new {
	id = "start_joke",
	leftDialog = "@conversation/corellia_privateer_trainer_2:s_aba61e8d", -- Hey, stop me if you've heard this one.  Three Corellians see an Imperial at the starport.
	animation = "slow_down",
	stopConversation = "false",
	options = {
		{"@conversation/corellia_privateer_trainer_2:s_ec084dd3", "continue_joke"}, -- Go on
		{"@conversation/corellia_privateer_trainer_2:s_30350c6", "heard_it"}, -- I've heard it.
	}
}
rikkh_convo_template:addScreen(start_joke);

heard_it = ConvoScreen:new {
	id = "heard_it",
	leftDialog = "@conversation/corellia_privateer_trainer_2:s_4e6f47aa", -- Oh.  Ok... heh, guess I'm getting to be old, telling the same old jokes over and over.
	animation = "",
	stopConversation = "false",
	options = {
		{"@conversation/corellia_privateer_trainer_2:s_9f5f269", "back_to_work"}, -- No problem
	}
}
rikkh_convo_template:addScreen(heard_it);

continue_joke = ConvoScreen:new {
	id = "continue_joke",
	leftDialog = "@conversation/corellia_privateer_trainer_2:s_76c3352e", -- So, one of the Corellians walked over to the Imperial, taps him on the shoulder, and says, 'Hey, I hear your Darth Vader is a spice-fiend.'
	animation = "",
	stopConversation = "false",
	options = {
		{"@conversation/corellia_privateer_trainer_2:s_ba11bd82", "continue_joke2"}, -- And?.
	}
}
rikkh_convo_template:addScreen(continue_joke);

continue_joke2 = ConvoScreen:new {
	id = "continue_joke2",
	leftDialog = "@conversation/corellia_privateer_trainer_2:s_47fde4be", -- The Imperial just shrugs and says, 'Oh really, I didn't know that.'  So the Corellian goes back to his buddies and tells them, 'I insulted Darth Vader and he didn't even care'.
	animation = "shrug_shoulders",
	stopConversation = "false",
	options = {
		{"@conversation/corellia_privateer_trainer_2:s_b3c84ab4", "continue_joke3"}, -- Then what happened?
	}
}
rikkh_convo_template:addScreen(continue_joke2);

continue_joke3 = ConvoScreen:new {
	id = "continue_joke3",
	leftDialog = "@conversation/corellia_privateer_trainer_2:s_a5293421", -- One of his buddies says, 'You just don't know how to get to him.  Watch this.' and he goes over to the Imperial and says, 'Hey, I hear your Darth Vader was a lying, cheating, idiotic, low-life scum!'  But the Imperial still just shrugs and says, 'Oh, really?  I didn't know that.'
	animation = "point_accusingly",
	stopConversation = "false",
	options = {
		{"@conversation/corellia_privateer_trainer_2:s_ec084dd3", "continue_joke4"}, -- Go on
	}
}
rikkh_convo_template:addScreen(continue_joke3);

continue_joke4 = ConvoScreen:new {
	id = "continue_joke4",
	leftDialog = "@conversation/corellia_privateer_trainer_2:s_f8842e94", -- So he goes back to his Corellian buddies and says, 'You're right!  That guy is unshakable!'  And the third Corellian says, 'I'll get him.  Watch this.'  And he goes over to the Imperial, taps him on the shoulder and says, 'Hey, I heard Darth Vader was a Corellian!'
	animation = "point_to_self",
	stopConversation = "false",
	options = {
		{"@conversation/corellia_privateer_trainer_2:s_b3c84ab4", "continue_joke5"}, -- Then what happened?
	}
}
rikkh_convo_template:addScreen(continue_joke4);

continue_joke5 = ConvoScreen:new {
	id = "continue_joke5",
	leftDialog = "@conversation/corellia_privateer_trainer_2:s_f8842e94", -- The Imperial just shrugged and said, 'Yeah, that's what your buddies were trying to tell me.'
	animation = "shrug_hands",
	stopConversation = "false",
	options = {
		{"@conversation/corellia_privateer_trainer_2:s_99251349", "done_goofing"}, -- (Laugh)
		{"@conversation/corellia_privateer_trainer_2:s_8ed520f1", "terrible_joke"}, -- That was terrible
	}
}
rikkh_convo_template:addScreen(continue_joke5);

completed_rikkh = ConvoScreen:new {
	id = "completed_rikkh",
	leftDialog = "@conversation/corellia_privateer_trainer_2:s_a87fc3e8", -- I want you to travel to Lok and see Commander Ramna.  She'll probably be holed-up in Nym's cantina...
	animation = "explain",
	stopConversation = "false",
	options = {
		{"@conversation/corellia_privateer_trainer_2:s_d24a2285", "good_luck"}, -- Will do.
		{"@conversation/corellia_privateer_trainer_2:s_84be4b94", "why_lok"}, -- Why Lok?
	}
}
rikkh_convo_template:addScreen(completed_rikkh);

why_lok = ConvoScreen:new {
	id = "why_lok",
	leftDialog = "@conversation/corellia_privateer_trainer_2:s_19104bb", -- I don't have all the details.  Suffice to say that sometimes CorSec needs to be a little more proactive.  We can't always wait for trouble to come to us.
	animation = "shake_head_no",
	stopConversation = "false",
	options = {
		{"@conversation/corellia_privateer_trainer_2:s_bcdf778f", "good_luck2"}, -- Ok, see ya.
		{"@conversation/corellia_privateer_trainer_2:s_9b99e4ac", "more_duty"}, -- Can't I just do some duty missions for you?
	}
}
rikkh_convo_template:addScreen(why_lok);

more_duty = ConvoScreen:new {
	id = "more_duty",
	leftDialog = "@conversation/corellia_privateer_trainer_2:s_1d843b61", -- You're much too good a pilot to waste on the trivial tasks that I could assign you.  We need you in Lok.  Now!
	animation = "point_accusingly",
	stopConversation = "false",
	options = {
		{"@conversation/corellia_privateer_trainer_2:s_9e576266", "git_gone"}, -- OK, ok!
	}
}
rikkh_convo_template:addScreen(more_duty);

ready_train_pilot = ConvoScreen:new {
	id = "ready_train_pilot",
	leftDialog = "@conversation/corellia_privateer_trainer_2:s_584a90f8", -- You've done an excellent job for me, %NU.  I can see that you are ready for some training.
	animation = "",
	stopConversation = "false",
	options = {
		-- Added via handler
	}
}
rikkh_convo_template:addScreen(ready_train_pilot);

-- Mission 1

initial_train_fighters = ConvoScreen:new {
	id = "initial_train_fighters",
	leftDialog = "@conversation/corellia_privateer_trainer_2:s_8860b099", -- Good choice.  No doubt that will come in handy for this next assignment. We want you to disrupt operations for Nym in his home system.  Go destroy spacecraft under his control.
	animation = "",
	stopConversation = "false",
	options = {
		{"@conversation/corellia_privateer_trainer_2:s_c42bff89", "start_first_mission"}, -- "Why Nym?
	}
}
rikkh_convo_template:addScreen(initial_train_fighters);

initial_train_components = ConvoScreen:new {
	id = "initial_train_components",
	leftDialog = "@conversation/corellia_privateer_trainer_2:s_8860b099", -- Good choice.  No doubt that will come in handy for this next assignment. We want you to disrupt operations for Nym in his home system.  Go destroy spacecraft under his control.
	animation = "",
	stopConversation = "false",
	options = {
		{"@conversation/corellia_privateer_trainer_2:s_c42bff89", "start_first_mission"}, -- "Why Nym?
	}
}
rikkh_convo_template:addScreen(initial_train_components)

initial_train_techniques = ConvoScreen:new {
	id = "initial_train_techniques",
	leftDialog = "@conversation/corellia_privateer_trainer_2:s_8860b099", -- Good choice.  No doubt that will come in handy for this next assignment. We want you to disrupt operations for Nym in his home system.  Go destroy spacecraft under his control.
	animation = "",
	stopConversation = "false",
	options = {
		{"@conversation/corellia_privateer_trainer_2:s_c42bff89", "start_first_mission"}, -- "Why Nym?
	}
}
rikkh_convo_template:addScreen(initial_train_techniques)

initial_train_algorithms = ConvoScreen:new {
	id = "initial_train_algorithms",
	leftDialog = "@conversation/corellia_privateer_trainer_2:s_8860b099", -- Good choice.  No doubt that will come in handy for this next assignment. We want you to disrupt operations for Nym in his home system.  Go destroy spacecraft under his control.
	animation = "",
	stopConversation = "false",
	options = {
		{"@conversation/corellia_privateer_trainer_2:s_c42bff89", "start_first_mission"}, -- "Why Nym?
	}
}
rikkh_convo_template:addScreen(initial_train_algorithms)

-- Mission 2

mission2_train_fighters = ConvoScreen:new {
	id = "mission2_train_fighters",
	leftDialog = "@conversation/corellia_privateer_trainer_2:s_2b10fbeb", -- Good choice.  Your new abilities will come in handy for this next assignment.  Go escort a freighter through Yavin Space against Rebel aggressions.
	animation = "",
	stopConversation = "false",
	options = {
		{"@conversation/corellia_privateer_trainer_2:s_5f5f76b5", "accept_escort"}, -- We're fighting the Rebel Alliance now?
	}
}
rikkh_convo_template:addScreen(mission2_train_fighters);

mission2_train_components = ConvoScreen:new {
	id = "mission2_train_components",
	leftDialog = "@conversation/corellia_privateer_trainer_2:s_2b10fbeb", -- Good choice.  Your new abilities will come in handy for this next assignment.  Go escort a freighter through Yavin Space against Rebel aggressions.
	animation = "",
	stopConversation = "false",
	options = {
		{"@conversation/corellia_privateer_trainer_2:s_5f5f76b5", "accept_escort"}, -- We're fighting the Rebel Alliance now?
	}
}
rikkh_convo_template:addScreen(mission2_train_components)

mission2_train_techniques = ConvoScreen:new {
	id = "mission2_train_techniques",
	leftDialog = "@conversation/corellia_privateer_trainer_2:s_2b10fbeb", -- Good choice.  Your new abilities will come in handy for this next assignment.  Go escort a freighter through Yavin Space against Rebel aggressions.
	stopConversation = "false",
	options = {
		{"@conversation/corellia_privateer_trainer_2:s_5f5f76b5", "accept_escort"}, -- We're fighting the Rebel Alliance now?
	}
}
rikkh_convo_template:addScreen(mission2_train_techniques)

mission2_train_algorithms = ConvoScreen:new {
	id = "mission2_train_algorithms",
	leftDialog = "@conversation/corellia_privateer_trainer_2:s_2b10fbeb", -- Good choice.  Your new abilities will come in handy for this next assignment.  Go escort a freighter through Yavin Space against Rebel aggressions.
	animation = "",
	stopConversation = "false",
	options = {
		{"@conversation/corellia_privateer_trainer_2:s_5f5f76b5", "accept_escort"}, -- We're fighting the Rebel Alliance now?
	}
}
rikkh_convo_template:addScreen(mission2_train_algorithms)

-- Mission 3

mission3_train_fighters = ConvoScreen:new {
	id = "mission3_train_fighters",
	leftDialog = "@conversation/corellia_privateer_trainer_2:s_c1ef4b1", -- Good choice.  Now I have a special assignment for you.  Fly to Lok and inspect a Nym Cannon Ship for Shipment Orders.
	animation = "",
	stopConversation = "false",
	options = {
		{"@conversation/corellia_privateer_trainer_2:s_82e1c248", "accept_inspect"}, -- What kind of orders?"
	}
}
rikkh_convo_template:addScreen(mission3_train_fighters);

mission3_train_components = ConvoScreen:new {
	id = "mission3_train_components",
	leftDialog = "@conversation/corellia_privateer_trainer_2:s_c1ef4b1", -- Good choice.  Now I have a special assignment for you.  Fly to Lok and inspect a Nym Cannon Ship for Shipment Orders.
	animation = "",
	stopConversation = "false",
	options = {
		{"@conversation/corellia_privateer_trainer_2:s_82e1c248", "accept_inspect"}, -- What kind of orders?"
	}
}
rikkh_convo_template:addScreen(mission3_train_components)

mission3_train_techniques = ConvoScreen:new {
	id = "mission3_train_techniques",
	leftDialog = "@conversation/corellia_privateer_trainer_2:s_c1ef4b1", -- Good choice.  Now I have a special assignment for you.  Fly to Lok and inspect a Nym Cannon Ship for Shipment Orders.
	animation = "",
	stopConversation = "false",
	options = {
		{"@conversation/corellia_privateer_trainer_2:s_82e1c248", "accept_inspect"}, -- What kind of orders?"
	}
}
rikkh_convo_template:addScreen(mission3_train_techniques)

mission3_train_algorithms = ConvoScreen:new {
	id = "mission3_train_algorithms",
	leftDialog = "@conversation/corellia_privateer_trainer_2:s_c1ef4b1", -- Good choice.  Now I have a special assignment for you.  Fly to Lok and inspect a Nym Cannon Ship for Shipment Orders.
	animation = "",
	stopConversation = "false",
	options = {
		{"@conversation/corellia_privateer_trainer_2:s_82e1c248", "accept_inspect"}, -- What kind of orders?"
	}
}
rikkh_convo_template:addScreen(mission3_train_algorithms)

-- Mission 4

mission4_train_fighters = ConvoScreen:new {
	id = "mission4_train_fighters",
	leftDialog = "@conversation/corellia_privateer_trainer_2:s_4165de51", -- Good choice.  Now I have a special assignment for you!  Go to Dantooine Space and destroy a Hutt Transport.  The Hutts are making a large spice shipment through that system and we do not intend to let it reach its destination, which could very well be Corellia.
	animation = "",
	stopConversation = "false",
	options = {
		{"@conversation/corellia_privateer_trainer_2:s_8c00922e", "accept_assassinate"}, -- What if it's not bound for Corellia?
	}
}
rikkh_convo_template:addScreen(mission4_train_fighters);

mission4_train_components = ConvoScreen:new {
	id = "mission4_train_components",
	leftDialog = "@conversation/corellia_privateer_trainer_2:s_4165de51", -- Good choice.  Now I have a special assignment for you!  Go to Dantooine Space and destroy a Hutt Transport.  The Hutts are making a large spice shipment through that system and we do not intend to let it reach its destination, which could very well be Corellia.
	animation = "",
	stopConversation = "false",
	options = {
		{"@conversation/corellia_privateer_trainer_2:s_c42bff89", "accept_assassinate"}, -- What if it's not bound for Corellia?
	}
}
rikkh_convo_template:addScreen(mission4_train_components)

mission4_train_techniques = ConvoScreen:new {
	id = "mission4_train_techniques",
	leftDialog = "@conversation/corellia_privateer_trainer_2:s_4165de51", -- Good choice.  Now I have a special assignment for you!  Go to Dantooine Space and destroy a Hutt Transport.  The Hutts are making a large spice shipment through that system and we do not intend to let it reach its destination, which could very well be Corellia.
	animation = "",
	stopConversation = "false",
	options = {
		{"@conversation/corellia_privateer_trainer_2:s_c42bff89", "accept_assassinate"}, -- What if it's not bound for Corellia?
	}
}
rikkh_convo_template:addScreen(mission4_train_techniques)

mission4_train_algorithms = ConvoScreen:new {
	id = "mission4_train_algorithms",
	leftDialog = "@conversation/corellia_privateer_trainer_2:s_4165de51", -- Good choice.  Now I have a special assignment for you!  Go to Dantooine Space and destroy a Hutt Transport.  The Hutts are making a large spice shipment through that system and we do not intend to let it reach its destination, which could very well be Corellia.
	animation = "",
	stopConversation = "false",
	options = {
		{"@conversation/corellia_privateer_trainer_2:s_c42bff89", "accept_assassinate"}, -- What if it's not bound for Corellia?
	}
}
rikkh_convo_template:addScreen(mission4_train_algorithms)

--[[

	Quest Line Missions

]]

-- Mission 1

first_mission = ConvoScreen:new {
	id = "first_mission",
	leftDialog = "@conversation/corellia_privateer_trainer_2:s_81b96b70", -- We want you to disrupt operations for Nym in his home system.  Go destroy spacecraft under his control.
	animation = "",
	stopConversation = "false",
	options = {
		{"@conversation/corellia_privateer_trainer_2:s_c42bff89", "start_first_mission"}, -- "Why Nym?
	}
}
rikkh_convo_template:addScreen(first_mission);

start_first_mission = ConvoScreen:new {
	id = "start_first_mission",
	leftDialog = "@conversation/corellia_privateer_trainer_2:s_cd54e85d", -- Because although he's not the worst pirate in the world, he does a fair bit of smuggling, piracy and assorted other criminal acts.  If we're going to have to tangle with his thugs, we'd rather do it on his own turf.
	animation = "",
	stopConversation = "true",
	options = {}
}
rikkh_convo_template:addScreen(start_first_mission);

failed_first_mission = ConvoScreen:new {
	id = "failed_first_mission",
	leftDialog = "@conversation/corellia_privateer_trainer_2:s_e00ac98e", -- What happened up there?
	animation = "shrug_hands",
	stopConversation = "false",
	options = {
		{"@conversation/corellia_privateer_trainer_2:s_d21a7a71", "fail_first_terrible"}, -- I failed
	}
}
rikkh_convo_template:addScreen(failed_first_mission);

fail_first_terrible = ConvoScreen:new {
	id = "fail_first_terrible",
	leftDialog = "@conversation/corellia_privateer_trainer_2:s_baddec82", -- Oh that's terrible.  You've got to get back to Lok and destroy that ship!
	animation = "shake_head_disgust",
	stopConversation = "false",
	options = {
		{"@conversation/corellia_privateer_trainer_2:s_40e66be3", "try_first_mission"}, -- I'll try
		{"@conversation/corellia_privateer_trainer_2:s_32e9d36a", "cant_wait_first"}, -- Can't it wait?
	}
}
rikkh_convo_template:addScreen(fail_first_terrible)

complete_first_mission = ConvoScreen:new {
	id = "complete_first_mission",
	leftDialog = "@conversation/corellia_privateer_trainer_2:s_5e86fa24", -- Well, soldier, how did things go?
	animation = "",
	stopConversation = "false",
	options = {
		{"@conversation/corellia_privateer_trainer_2:s_f52a7b2d", "pilot_not_soldier"}, -- I'm a pilot, not a soldier
		{"@conversation/corellia_privateer_trainer_2:s_501489d2", "according_to_plan"}, -- All according to plan
	}
}
rikkh_convo_template:addScreen(complete_first_mission)

pilot_not_soldier = ConvoScreen:new {
	id = "pilot_not_soldier",
	leftDialog = "@conversation/corellia_privateer_trainer_2:s_dd46f361", -- Well that explains the way you dress.  So, PILOT, was the mission a success?
	animation = "laugh_cackle",
	stopConversation = "false",
	options = {
		{"@conversation/corellia_privateer_trainer_2:s_370822d1", "first_mission_success"}, -- Yes
	}
}
rikkh_convo_template:addScreen(pilot_not_soldier)

according_to_plan = ConvoScreen:new {
	id = "according_to_plan",
	leftDialog = "@conversation/corellia_privateer_trainer_2:s_3a126327", -- No plan survives initial contact with the enemy!  But I take it you were successful anyway.  I'll credit your bank for services rendered.
	animation = "shake_head_no",
	stopConversation = "false",
	options = {
		{"@conversation/corellia_privateer_trainer_2:s_5fa9a5d3", "earned_it"}, -- Thanks
		{"@conversation/corellia_privateer_trainer_2:s_da7c5706", "not_mercenary"}, -- I'm not a mercenary!
	}
}
rikkh_convo_template:addScreen(according_to_plan)

first_mission_success = ConvoScreen:new {
	id = "first_mission_success",
	leftDialog = "@conversation/corellia_privateer_trainer_2:s_f68c028e", -- Well then, you've earned your daily credit.  Here you are.  Let me know when you're in need of more work.
	animation = "dismiss",
	stopConversation = "false",
	options = {
		{"@conversation/corellia_privateer_trainer_2:s_5fa9a5d3", "earned_it"}, -- Thanks
		{"@conversation/corellia_privateer_trainer_2:s_da7c5706", "not_mercenary"}, -- I'm not a mercenary!
	}
}
rikkh_convo_template:addScreen(first_mission_success)

not_mercenary = ConvoScreen:new {
	id = "not_mercenary",
	leftDialog = "@conversation/corellia_privateer_trainer_2:s_fd2e713f", -- Oh, you're just working out of a sense of duty to Corellia, huh?  Committed to keeping the planet free of outside influence and that sort of thing.  You expect me to believe that?
	animation = "point_to_self",
	stopConversation = "false",
	options = {
		{"@conversation/corellia_privateer_trainer_2:s_f96e5915", "tell_me_more"}, -- It's true!
		{"@conversation/corellia_privateer_trainer_2:s_b6b1c40a", "get_out"}, -- Not really
	}
}
rikkh_convo_template:addScreen(not_mercenary)

tell_me_more = ConvoScreen:new {
	id = "tell_me_more",
	leftDialog = "@conversation/corellia_privateer_trainer_2:s_df44b897", -- Oh tell me another one!
	animation = "cover_ears_mocking",
	stopConversation = "false",
	options = {
		{"@conversation/corellia_privateer_trainer_2:s_26de1778", "doesnt_believe"}, -- You don't believe me?
	}
}
rikkh_convo_template:addScreen(tell_me_more)

doesnt_believe = ConvoScreen:new {
	id = "doesnt_believe",
	leftDialog = "@conversation/corellia_privateer_trainer_2:s_80e4a5f8", -- Well come on, %NU.  I was born at night, but not LAST night!
	animation = "shrug_shoulders",
	stopConversation = "false",
	options = {
		{"@conversation/corellia_privateer_trainer_2:s_169df3bb", "fine_job"}, -- Never mind.
		{"@conversation/corellia_privateer_trainer_2:s_3cfd3bb4", "idle_threats"}, -- You'd BETTER stop mocking me
	}
}
rikkh_convo_template:addScreen(doesnt_believe)

idle_threats = ConvoScreen:new {
	id = "idle_threats",
	leftDialog = "@conversation/corellia_privateer_trainer_2:s_80e4a5f8", -- Hey now!  Are you threatening me?  I'll have you know this old slice hound still has a bite.
	animation = "gesticulate_wildly",
	playerAnimation = "point_accusingly",
	stopConversation = "false",
	options = {
		{"@conversation/corellia_privateer_trainer_2:s_bc8bf5b3", "back_down"}, -- Never mind.
		{"@conversation/corellia_privateer_trainer_2:s_f0adaca2", "rank_aside"}, -- I'm not scared of you
	}
}
rikkh_convo_template:addScreen(idle_threats)

rank_aside = ConvoScreen:new {
	id = "rank_aside",
	leftDialog = "@conversation/corellia_privateer_trainer_2:s_c66d1ef2", -- If you're expecting I won't set my rank aside for the two seconds it takes to give you a beating, you had better think again!
	animation = "gesticulate_wildly",
	playerAnimation = "threaten",
	stopConversation = "false",
	options = {
		{"@conversation/corellia_privateer_trainer_2:s_225d3518", "too_much"}, -- What are you waiting for?
	}
}
rikkh_convo_template:addScreen(rank_aside)

too_much = ConvoScreen:new {
	id = "too_much",
	leftDialog = "@conversation/corellia_privateer_trainer_2:s_c66d1ef2", -- If you're expecting I won't set my rank aside for the two seconds it takes to give you a beating, you had better think again!
	animation = "stamp_feet",
	playerAnimation = "pound_fist_palm",
	stopConversation = "false",
	options = {
		{"@conversation/corellia_privateer_trainer_2:s_523e23b2", "flatline"}, -- Here I am!
		{"@conversation/corellia_privateer_trainer_2:s_b6a04af3", "woah_take_it_easy"}, -- Roooaaaaaawwwwr!!!
	}
}
rikkh_convo_template:addScreen(too_much)

flatline = ConvoScreen:new {
	id = "flatline",
	leftDialog = "@conversation/corellia_privateer_trainer_2:s_9208410d", -- ...
	animation = "",
	playerAnimation = "point_to_self",
	stopConversation = "false",
	options = {
		{"@conversation/corellia_privateer_trainer_2:s_5b1bed8b", "just_kidding"}, -- Well?
	}
}
rikkh_convo_template:addScreen(flatline)

just_kidding = ConvoScreen:new {
	id = "just_kidding",
	leftDialog = "@conversation/corellia_privateer_trainer_2:s_82d6265", -- Bwaahahahaaha!  Oh I really had you going, there!  I thought you were going to hit me!
	animation = "belly_laugh",
	playerAnimation = "shrug_hands",
	stopConversation = "false",
	options = {
		{"@conversation/corellia_privateer_trainer_2:s_f1679a90", "enough_joking"}, -- (laugh)
		{"@conversation/corellia_privateer_trainer_2:s_d73a1a1e", "enough_joking2"}, -- I was!
	}
}
rikkh_convo_template:addScreen(just_kidding)

woah_take_it_easy = ConvoScreen:new {
	id = "woah_take_it_easy",
	leftDialog = "@conversation/corellia_privateer_trainer_2:s_41e79b8c", -- Woah!  Woah!  Woah!  Slow down, there!  I was just kidding around with you.  Take it easy!
	animation = "slow_down",
	playerAnimation = "gesticulate_wildly",
	stopConversation = "false",
	options = {
		{"@conversation/corellia_privateer_trainer_2:s_f1679a90", "laugh_it_off"}, -- (laugh)
		{"@conversation/corellia_privateer_trainer_2:s_906e4829", "rip_arms_off"}, -- Next time I'll rip your arms off
	}
}
rikkh_convo_template:addScreen(woah_take_it_easy)

laugh_it_off = ConvoScreen:new {
	id = "laugh_it_off",
	leftDialog = "@conversation/corellia_privateer_trainer_2:s_b3b93f51", -- Oh, you really had me going there.  I thought you were going to rip my arms out the sockets.  Enough joking around though, I've got to get back to work.
	animation = "laugh",
	playerAnimation = "laugh",
	stopConversation = "true",
	options = {}
}
rikkh_convo_template:addScreen(laugh_it_off)

rip_arms_off = ConvoScreen:new {
	id = "rip_arms_off",
	leftDialog = "@conversation/corellia_privateer_trainer_2:s_c7b73029", -- Don't worry, %NU... there won't be a next time... I'll remember not to mess around with you.
	animation = "laugh",
	playerAnimation = "",
	stopConversation = "true",
	options = {}
}
rikkh_convo_template:addScreen(rip_arms_off)

-- Mission 2

second_mission = ConvoScreen:new {
	id = "second_mission",
	leftDialog = "@conversation/corellia_privateer_trainer_2:s_b60183cf", -- Go escort a freighter through Yavin Space against Rebel aggressions.
	animation = "",
	stopConversation = "false",
	options = {
		{"@conversation/corellia_privateer_trainer_2:s_5f5f76b5", "accept_escort"}, -- We're fighting the Rebel Alliance now?

	}
}
rikkh_convo_template:addScreen(second_mission);

accept_escort = ConvoScreen:new {
	id = "accept_escort",
	leftDialog = "@conversation/corellia_privateer_trainer_2:s_7d351971", -- No, no, of course not.  Corellia is officially neutral in this little war.  But if they think that means they and the Empire can divide every resource in the galaxy then they've got another think comin'.
	animation = "shake_head_no",
	playerAnimation = "",
	stopConversation = "true",
	options = {}
}
rikkh_convo_template:addScreen(accept_escort)

failed_second_mission = ConvoScreen:new {
	id = "failed_second_mission",
	leftDialog = "@conversation/corellia_privateer_trainer_2:s_6adcde65", -- How did that escort go?
	animation = "",
	stopConversation = "false",
	options = {
		{"@conversation/corellia_privateer_trainer_2:s_b31da30c", "back_to_yavin"}, -- Not very well
		{"@conversation/corellia_privateer_trainer_2:s_158b60f", "take_care_of_business"}, -- Just fine
	}
}
rikkh_convo_template:addScreen(failed_second_mission);

back_to_yavin = ConvoScreen:new {
	id = "back_to_yavin",
	leftDialog = "@conversation/corellia_privateer_trainer_2:s_71b485e4", -- Then don't just stand around here talking to me, get back to Yavin and see that the ship makes it through!
	animation = "",
	stopConversation = "true",
	options = {}
}
rikkh_convo_template:addScreen(back_to_yavin);

take_care_of_business = ConvoScreen:new {
	id = "take_care_of_business",
	leftDialog = "@conversation/corellia_privateer_trainer_2:s_8bec44d9", -- Oh really... then tell me, WHY DIDN'T IT ARRIVE?  I think you'd better get back to Yavin and take care of business!
	animation = "gesticulate_wildly",
	stopConversation = "false",
	options = {
		{"@conversation/corellia_privateer_trainer_2:s_cfa2d559", "now_is_good"}, -- Will do
		{"@conversation/corellia_privateer_trainer_2:s_8f8348b9", "be_smarter"}, -- You don't have to yell
	}
}
rikkh_convo_template:addScreen(take_care_of_business);

now_is_good = ConvoScreen:new {
	id = "now_is_good",
	leftDialog = "@conversation/corellia_privateer_trainer_2:s_3e869ab", -- Good!  How about NOW?  Is NOW good for you?
	animation = "point_away",
	stopConversation = "true",
	options = {}
}
rikkh_convo_template:addScreen(now_is_good);

be_smarter = ConvoScreen:new {
	id = "be_smarter",
	leftDialog = "@conversation/corellia_privateer_trainer_2:s_18206937", -- I'll try being nicer if you'll try being smarter.  Not get back to Yavin and complete your mission!u?
	animation = "explain",
	stopConversation = "true",
	options = {}
}
rikkh_convo_template:addScreen(be_smarter);

complete_second_mission = ConvoScreen:new {
	id = "complete_second_mission",
	leftDialog = "@conversation/corellia_privateer_trainer_2:s_771cfc6b", -- Escort mission a success?
	animation = "",
	stopConversation = "false",
	options = {
		{"@conversation/corellia_privateer_trainer_2:s_370822d1", "duty_calls"}, -- Yes
		{"@conversation/corellia_privateer_trainer_2:s_6adec6b0", "here_is_pay"}, -- Of course!
	}
}
rikkh_convo_template:addScreen(complete_second_mission)

duty_calls = ConvoScreen:new {
	id = "duty_calls",
	leftDialog = "@conversation/corellia_privateer_trainer_2:s_622194e2", -- I know that's not the most glamorous assignment, but when duty calls, we've got to answer.  Am I right?  Or am I right?
	animation = "shrug_hands",
	stopConversation = "false",
	options = {
		{"@conversation/corellia_privateer_trainer_2:s_fecb2cbb", "youre_right"}, -- You're right
	}
}
rikkh_convo_template:addScreen(duty_calls)

youre_right = ConvoScreen:new {
	id = "youre_right",
	leftDialog = "@conversation/corellia_privateer_trainer_2:s_315cee58", -- Of course I'm right!  Now don't you hesitate to see me again the very moment you're available for duty.
	animation = "salute2",
	stopConversation = "true",
	options = {}
}
rikkh_convo_template:addScreen(youre_right)

here_is_pay = ConvoScreen:new {
	id = "here_is_pay",
	leftDialog = "@conversation/corellia_privateer_trainer_2:s_e6e4f8fe", -- That's the stuff.  Here's your pay.  Personally I don't care much for fighting the Rebel Alliance OR the Imperial Navy... seems like too great an opportunity for Corellia to be swept into this war.
	animation = "point_to_self",
	stopConversation = "false",
	options = {
		{"@conversation/corellia_privateer_trainer_2:s_eef93168", "dont_like"}, -- I don't like it either
		{"@conversation/corellia_privateer_trainer_2:s_af6c7acb", "dont_mind"}, -- I don't mind
	}
}
rikkh_convo_template:addScreen(here_is_pay)

dont_like = ConvoScreen:new {
	id = "dont_like",
	leftDialog = "@conversation/corellia_privateer_trainer_2:s_e119b0aa", -- Yeah.  These are tough times, though.  We've got to preserve Corellian interests no matter WHAT it takes.
	animation = "shake_head_disgust",
	stopConversation = "true",
	options = {}
}
rikkh_convo_template:addScreen(dont_like)

dont_mind = ConvoScreen:new {
	id = "dont_mind",
	leftDialog = "@conversation/corellia_privateer_trainer_2:s_529c014", -- You're a cold man, %TU.  Come see me when you're ready for your next assignment.
	animation = "",
	stopConversation = "true",
	options = {}
}
rikkh_convo_template:addScreen(dont_mind)

-- Mission 3

third_mission = ConvoScreen:new {
	id = "third_mission",
	leftDialog = "@conversation/corellia_privateer_trainer_2:s_32103432", -- I have a special assignment for you.  Fly to Lok and inspect a Nym Cannon Ship for Shipment Orders.
	animation = "",
	stopConversation = "false",
	options = {
		{"@conversation/corellia_privateer_trainer_2:s_82e1c248", "accept_inspect"}, -- What kind of orders?
	}
}
rikkh_convo_template:addScreen(third_mission);

accept_inspect = ConvoScreen:new {
	id = "accept_inspect",
	leftDialog = "@conversation/corellia_privateer_trainer_2:s_36f60ccb", -- That's what we want to know... Just what is he shipping around, and who is he doing it for... and that's what you're going to find out!
	animation = "point_to_self",
	playerAnimation = "",
	stopConversation = "true",
	options = {}
}
rikkh_convo_template:addScreen(accept_inspect)

failed_third_mission = ConvoScreen:new {
	id = "failed_third_mission",
	leftDialog = "@conversation/corellia_privateer_trainer_2:s_1c0972b6", -- Did you get the shipment orders?
	animation = "",
	stopConversation = "false",
	options = {
		{"@conversation/corellia_privateer_trainer_2:s_457a7010", "on_your_way"}, -- No
		{"@conversation/corellia_privateer_trainer_2:s_370822d1", "hand_over"}, -- Yes
	}
}
rikkh_convo_template:addScreen(failed_third_mission);

on_your_way = ConvoScreen:new {
	id = "on_your_way",
	leftDialog = "@conversation/corellia_privateer_trainer_2:s_a785d6d0", -- Then you'd best be on your way, right?  Back to Lok!  Get those orders!  No time like the present!
	animation = "check_wrist_device",
	stopConversation = "true",
	options = {}
}
rikkh_convo_template:addScreen(on_your_way)

hand_over = ConvoScreen:new {
	id = "hand_over",
	leftDialog = "@conversation/corellia_privateer_trainer_2:s_f3327326", -- Ok, hand them over.
	animation = "",
	stopConversation = "false",
	options = {
		{"@conversation/corellia_privateer_trainer_2:s_fb8ba48a", "take_it_serious"}, -- I lost them
		{"@conversation/corellia_privateer_trainer_2:s_cd482bef", "bad_liar"}, -- I lied, I didn't get them
	}
}
rikkh_convo_template:addScreen(hand_over);

take_it_serious = ConvoScreen:new {
	id = "take_it_serious",
	leftDialog = "@conversation/corellia_privateer_trainer_2:s_60fbb41a", -- I like you.  You remind me of when I was young and stupid.  Listen up, you'd better start taking this job seriously!  We need those orders.  Go get them.  Now!
	animation = "",
	playerAnimation = "gesticulate_wildly",
	stopConversation = "true",
	options = {}
}
rikkh_convo_template:addScreen(take_it_serious)

bad_liar = ConvoScreen:new {
	id = "bad_liar",
	leftDialog = "@conversation/corellia_privateer_trainer_2:s_9e4b1a6c", -- You are not a very good liar, %NU.  And that's good, since you don't seem to be a very good pilot, either.  Now get back to Lok and get us those shipment orders!
	animation = "",
	playerAnimation = "gesticulate_wildly",
	stopConversation = "true",
	options = {}
}
rikkh_convo_template:addScreen(bad_liar)

complete_third_mission = ConvoScreen:new {
	id = "complete_third_mission",
	leftDialog = "@conversation/corellia_privateer_trainer_2:s_ecba0095", -- What's the good word, %NU?
	animation = "",
	stopConversation = "false",
	options = {
		{"@conversation/corellia_privateer_trainer_2:s_aeca6ebc", "turnover_intelligence"}, -- I have the shipment orders
	}
}
rikkh_convo_template:addScreen(complete_third_mission)

turnover_intelligence = ConvoScreen:new {
	id = "turnover_intelligence",
	leftDialog = "@conversation/corellia_privateer_trainer_2:s_8416980e", -- Perfect!  I'll turn these over to Intelligence.  I've got your payment right here.
	animation = "",
	stopConversation = "false",
	options = {
		{"@conversation/corellia_privateer_trainer_2:s_5fa9a5d3", "maintenance_order"}, -- Thanks
	}
}
rikkh_convo_template:addScreen(turnover_intelligence)

maintenance_order = ConvoScreen:new {
	id = "maintenance_order",
	leftDialog = "@conversation/corellia_privateer_trainer_2:s_39bc34a9", --  Hey, %NU, did I tell you about the maintenance report I just received?
	animation = "check_wrist_device",
	stopConversation = "false",
	options = {
		{"@conversation/corellia_privateer_trainer_2:s_322b6b69", "crew_on_spice"}, -- No, what about it?
	}
}
rikkh_convo_template:addScreen(maintenance_order)

crew_on_spice = ConvoScreen:new {
	id = "crew_on_spice",
	leftDialog = "@conversation/corellia_privateer_trainer_2:s_fb40feab", --  I'm starting to think our maintenance crew is on the spice.  You wouldn't believe some of these 'solutions' they've entered, here.
	animation = "",
	stopConversation = "false",
	options = {
		{"@conversation/corellia_privateer_trainer_2:s_53de9d8f", "solution_for_fix"}, -- Like what?
	}
}
rikkh_convo_template:addScreen(crew_on_spice)

solution_for_fix = ConvoScreen:new {
	id = "solution_for_fix",
	leftDialog = "@conversation/corellia_privateer_trainer_2:s_61189bfc", -- One work-order for the maintenance crew lists the problem as 'Something in cockpit is loose'.  Guess what the maintenance workers wrote as the solution?
	animation = "explain",
	stopConversation = "false",
	options = {
		{"@conversation/corellia_privateer_trainer_2:s_900f01d1", "typical_maintenance"}, -- What?
	}
}
rikkh_convo_template:addScreen(solution_for_fix)

typical_maintenance = ConvoScreen:new {
	id = "typical_maintenance",
	leftDialog = "@conversation/corellia_privateer_trainer_2:s_f9f9a99", -- It says, 'Something in cockpit tightened.''
	animation = "shrug_hands",
	stopConversation = "false",
	options = {
		{"@conversation/corellia_privateer_trainer_2:s_eb93536d", "more_problems"}, -- Funny
	}
}
rikkh_convo_template:addScreen(typical_maintenance)

more_problems = ConvoScreen:new {
	id = "more_problems",
	leftDialog = "@conversation/corellia_privateer_trainer_2:s_1c81fc8b", -- Or how about this:  It says 'Problem:  Hyperdrive volume is unbelievably loud'.... 'Solution:  Hyperdrive volume adjusted to more believable level.'
	animation = "laugh_titter",
	stopConversation = "false",
	options = {
		{"@conversation/corellia_privateer_trainer_2:s_eea02eca", "gets_worse"}, -- You're kidding?
	}
}
rikkh_convo_template:addScreen(more_problems)

gets_worse = ConvoScreen:new {
	id = "gets_worse",
	leftDialog = "@conversation/corellia_privateer_trainer_2:s_513aa336", -- No I'm not.  And they get worse!  This one says 'Problem:  Boosters not operational.' and then 'Solution:  Boosters will not work in OFF mode.'
	animation = "shake_head_disgust",
	stopConversation = "false",
	options = {
		{"@conversation/corellia_privateer_trainer_2:s_c9a83e17", "not_real_reports"}, -- Oh come on!
	}
}
rikkh_convo_template:addScreen(gets_worse)

not_real_reports = ConvoScreen:new {
	id = "not_real_reports",
	leftDialog = "@conversation/corellia_privateer_trainer_2:s_900f01d1", -- What?
	animation = "shrug_shoulders",
	stopConversation = "false",
	options = {
		{"@conversation/corellia_privateer_trainer_2:s_920404b6", "more_reports"}, -- Those can't be real reports
	}
}
rikkh_convo_template:addScreen(not_real_reports)

more_reports = ConvoScreen:new {
	id = "more_reports",
	leftDialog = "@conversation/corellia_privateer_trainer_2:s_b0a6b1e2", -- How about this one: 'Dead bugs found on windshield.'  Solution:  'Live bugs on order'.
	animation = "",
	stopConversation = "false",
	options = {
		{"@conversation/corellia_privateer_trainer_2:s_f1679a90", "made_up_report"}, -- (laugh)
		{"@conversation/corellia_privateer_trainer_2:s_158a5883", "made_up_report2"}, -- I don't believe you
	}
}
rikkh_convo_template:addScreen(more_reports)

made_up_report = ConvoScreen:new {
	id = "made_up_report",
	leftDialog = "@conversation/corellia_privateer_trainer_2:s_ac638560", -- Ha ha!  Ok, I made that last one up...  But there is some kind of comedian working in the maintenance hangar!
	animation = "laugh",
	playerAnimation = "laugh",
	stopConversation = "true",
	options = {}
}
rikkh_convo_template:addScreen(made_up_report)

made_up_report2 = ConvoScreen:new {
	id = "made_up_report2",
	leftDialog = "@conversation/corellia_privateer_trainer_2:s_2d247e7b", -- Ha ha!  Ok, I made that last one up...  But there is SOME kind of comedian working in the maintenance hangar!
	animation = "laugh",
	stopConversation = "true",
	options = {}
}
rikkh_convo_template:addScreen(made_up_report2)

-- Mission 4

fourth_mission = ConvoScreen:new {
	id = "fourth_mission",
	leftDialog = "@conversation/corellia_privateer_trainer_2:s_d8652774", -- I have a special assignment for you!  Go to Dantooine Space and destroy a Hutt Transport.  The Hutts are making a large spice shipment through that system and we do not intend to let it reach its destination, which could very well be Corellia.
	animation = "",
	stopConversation = "false",
	options = {
		{"@conversation/corellia_privateer_trainer_2:s_8c00922e", "accept_assassinate"}, -- What if it's not bound for Corellia?
	}
}
rikkh_convo_template:addScreen(fourth_mission);

accept_assassinate = ConvoScreen:new {
	id = "accept_assassinate",
	leftDialog = "@conversation/corellia_privateer_trainer_2:s_36f60ccb", -- That's what we want to know... Just what is he shipping around, and who is he doing it for... and that's what you're going to find out!
	animation = "point_to_self",
	playerAnimation = "",
	stopConversation = "true",
	options = {}
}
rikkh_convo_template:addScreen(accept_assassinate)

failed_fourth_mission = ConvoScreen:new {
	id = "failed_fourth_mission",
	leftDialog = "@conversation/corellia_privateer_trainer_2:s_e00ac98e", -- What happened?
	animation = "",
	stopConversation = "false",
	options = {
		{"@conversation/corellia_privateer_trainer_2:s_51b81b00", "nonsense"}, -- They were too strong for me
		{"@conversation/corellia_privateer_trainer_2:s_5b5ed110", "pilot_error"}, -- Pilot error
		{"@conversation/corellia_privateer_trainer_2:s_1e666f74", "exploded_equipment"}, -- Equipment malfunction
	}
}
rikkh_convo_template:addScreen(failed_fourth_mission);

nonsense = ConvoScreen:new {
	id = "nonsense",
	leftDialog = "@conversation/corellia_privateer_trainer_2:s_7b7644f7", --  Nonsense!  You can do this!  Go back to Dantooine and eliminate that spice runner!
	animation = "point_accusingly",
	playerAnimation = "",
	stopConversation = "true",
	options = {}
}
rikkh_convo_template:addScreen(nonsense)

pilot_error = ConvoScreen:new {
	id = "pilot_error",
	leftDialog = "@conversation/corellia_privateer_trainer_2:s_d338fc9a", -- And what are you going to do about it?
	animation = "laugh",
	playerAnimation = "",
	stopConversation = "false",
	options = {
		{"@conversation/corellia_privateer_trainer_2:s_4e94fa0f", "let_me_know"}, -- Try again?
		{"@conversation/corellia_privateer_trainer_2:s_f9c365f7", "heres_a_hit"}, -- I don't know
	}
}
rikkh_convo_template:addScreen(pilot_error)

let_me_know = ConvoScreen:new {
	id = "let_me_know",
	leftDialog = "@conversation/corellia_privateer_trainer_2:s_8aec791d", -- Correct in one guess!  Let me know how it goes.
	animation = "applause_polite",
	playerAnimation = "",
	stopConversation = "true",
	options = {}
}
rikkh_convo_template:addScreen(let_me_know)

heres_a_hit = ConvoScreen:new {
	id = "heres_a_hit",
	leftDialog = "@conversation/corellia_privateer_trainer_2:s_36961caf", -- Wrong answer, %NU.  But I'll give you a hint, it involves you, Dantooine, a spice runner, and a successful mission.
	animation = "shake_head_disgust",
	playerAnimation = "",
	stopConversation = "false",
	options = {
		{"@conversation/corellia_privateer_trainer_2:s_485284b6", "report_back_success"}, -- I'll try again
	}
}
rikkh_convo_template:addScreen(heres_a_hit)

report_back_success = ConvoScreen:new {
	id = "report_back_success",
	leftDialog = "@conversation/corellia_privateer_trainer_2:s_106e3dbb", -- I know you will.  Report back when you're done.  When you're SUCCESSFUL this time.
	animation = "point_accusingly",
	playerAnimation = "",
	stopConversation = "true",
	options = {}
}
rikkh_convo_template:addScreen(report_back_success)

exploded_equipment = ConvoScreen:new {
	id = "exploded_equipment",
	leftDialog = "@conversation/corellia_privateer_trainer_2:s_e3064ba1", -- Equipment malfunction?!  Let me guess... someone shot your equipment and it exploded?
	animation = "",
	playerAnimation = "",
	stopConversation = "false",
	options = {
		{"@conversation/corellia_privateer_trainer_2:s_84cdd613", "key_to_success"}, -- Something like that
		{"@conversation/corellia_privateer_trainer_2:s_a9839037", "just_malfunctioned"}, -- No, it just malfunctioned
	}
}
rikkh_convo_template:addScreen(exploded_equipment)

key_to_success = ConvoScreen:new {
	id = "key_to_success",
	leftDialog = "@conversation/corellia_privateer_trainer_2:s_2ef8d174", -- Look, the key to success is to shoot the enemy before the enemy shoots you.  Now get back to Dantooine and kill that spicer!
	animation = "",
	playerAnimation = "",
	stopConversation = "true",
	options = {}
}
rikkh_convo_template:addScreen(key_to_success)

just_malfunctioned = ConvoScreen:new {
	id = "just_malfunctioned",
	leftDialog = "@conversation/corellia_privateer_trainer_2:s_6782f928", -- Excuses, excuses.  Maybe you need to stop buying your equipment from the lowest bidder.  Splurge a little.  Get something that won't break-down on you.  And then get back to Dantooine and destroy that spicer!
	animation = "wave_on_dismissing",
	playerAnimation = "",
	stopConversation = "true",
	options = {}
}
rikkh_convo_template:addScreen(just_malfunctioned)

complete_fourth_mission = ConvoScreen:new {
	id = "complete_fourth_mission",
	leftDialog = "@conversation/corellia_privateer_trainer_2:s_8e80e129", -- %NU!  My favorite pilot.  Did you stop the transport?
	animation = "",
	stopConversation = "false",
	options = {
		{"@conversation/corellia_privateer_trainer_2:s_6f9a9967", "fourth_mission_success"}, -- I blew it to bits
	}
}
rikkh_convo_template:addScreen(complete_fourth_mission)

fourth_mission_success = ConvoScreen:new {
	id = "fourth_mission_success",
	leftDialog = "@conversation/corellia_privateer_trainer_2:s_c16a57f5", -- Good job!  Nothing more satisfying than that, right?  I've got your pay right here.... along with some news.
	animation = "",
	stopConversation = "false",
	options = {
		{"@conversation/corellia_privateer_trainer_2:s_1c8bddbb", ""}, -- What is it?    --- Should return default ?
	}
}
rikkh_convo_template:addScreen(fourth_mission_success)

--[[

	Duty Missions

]]

here_for_work = ConvoScreen:new {
	id = "here_for_work",
	leftDialog = "@conversation/corellia_privateer_trainer_2:s_5d262b71", -- You are here for work now, yes?
	animation = "nod_head_once",
	stopConversation = "false",
	options = {
		{"@conversation/corellia_privateer_trainer_2:s_e107077e", "good_duty"}, -- Yes I am
		{"@conversation/corellia_privateer_trainer_2:s_c545bb40", "no_duty"}, -- No I am not
		{"@conversation/corellia_privateer_trainer_2:s_98dba2b6", "better_ship"}, -- I need a better ship
	}
}
rikkh_convo_template:addScreen(here_for_work)

good_duty = ConvoScreen:new {
	id = "good_duty",
	leftDialog = "@conversation/corellia_privateer_trainer_2:s_178d46a1", -- Good.  Choose an assignment.
	animation = "",
	stopConversation = "false",
	options = {
		{"@conversation/corellia_privateer_trainer_2:s_fa5c5669", "destroy_duty1"}, -- Destroy Duty
		{"@conversation/corellia_privateer_trainer_2:s_56e162f2", "escort_duty"}, -- Escort Duty
		{"@conversation/corellia_privateer_trainer_2:s_fa5c5669", "destroy_duty2"}, -- Destroy Duty
		{"@conversation/corellia_privateer_trainer_2:s_28ea80d", "recovery_duty"}, -- Recovery Duty
	}
}
rikkh_convo_template:addScreen(good_duty)

no_duty = ConvoScreen:new {
	id = "no_duty",
	leftDialog = "@conversation/corellia_privateer_trainer_2:s_9e85f6f2", -- Why not?  We've got bad guys to catch, stolen cargo to recover, Imperial oppression to resist... you think Corellia is just going to magically secure itself?
	animation = "",
	stopConversation = "false",
	options = {
		{"@conversation/corellia_privateer_trainer_2:s_f613ccdb", "lots_to_do"}, -- Ok, what can I do?
		{"@conversation/corellia_privateer_trainer_2:s_82d13497", "too_busy"}, -- I'm busy
	}
}
rikkh_convo_template:addScreen(no_duty)

lots_to_do = ConvoScreen:new {
	id = "lots_to_do",
	leftDialog = "@conversation/corellia_privateer_trainer_2:s_5715d65c", -- Lots.  What do you WANT to do?
	animation = "",
	stopConversation = "false",
	options = {
		{"@conversation/corellia_privateer_trainer_2:s_fa5c5669", "destroy_duty1"}, -- Destroy Duty
		{"@conversation/corellia_privateer_trainer_2:s_56e162f2", "escort_duty"}, -- Escort Duty
		{"@conversation/corellia_privateer_trainer_2:s_fa5c5669", "destroy_duty2"}, -- Destroy Duty
		{"@conversation/corellia_privateer_trainer_2:s_28ea80d", "recovery_duty"}, -- Recovery Duty
	}
}
rikkh_convo_template:addScreen(lots_to_do)

better_ship = ConvoScreen:new {
	id = "better_ship",
	leftDialog = "@conversation/corellia_privateer_trainer_2:s_6d4db3b5", -- What's wrong with the one you've got?
	animation = "rub_chin_thoughtful",
	stopConversation = "false",
	options = {
		{"@conversation/corellia_privateer_trainer_2:s_bc99a4d2", "weak_ship"}, -- It's weak!
		{"@conversation/corellia_privateer_trainer_2:s_3880d2bf", "buy_ship"}, -- I need a hyperdrive
	}
}
rikkh_convo_template:addScreen(better_ship)

weak_ship = ConvoScreen:new {
	id = "weak_ship",
	leftDialog = "@conversation/corellia_privateer_trainer_2:s_aad866ad", -- You'll just have to learn to deal with it... or buy a better ship.  Now are you ready for work or not?
	animation = "",
	stopConversation = "false",
	options = {
		{"@conversation/corellia_privateer_trainer_2:s_e107077e", "good_duty"}, -- Yes I am
		{"@conversation/corellia_privateer_trainer_2:s_c545bb40", "no_duty"}, -- No I am not
		{"@conversation/corellia_privateer_trainer_2:s_98dba2b6", "better_ship"}, -- I need a better ship
	}
}
rikkh_convo_template:addScreen(weak_ship)

destroy_duty1 = ConvoScreen:new {
	id = "destroy_duty1",
	leftDialog = "@conversation/corellia_privateer_trainer_2:s_346ddf", -- You know Corellia's officially neutral in the civil war, right?  Well the Imperials seem to have a hard time remembering that.  Go out there and 'remind' them they aren't welcome as a military power in the Corellia system.
	animation = "explain",
	stopConversation = "false",
	options = {
		{"@conversation/corellia_privateer_trainer_2:s_d24a2285", "accept_duty_destroy1"}, -- Will do.
	}
}
rikkh_convo_template:addScreen(destroy_duty1)

accept_duty_destroy1 = ConvoScreen:new {
	id = "accept_duty_destroy1",
	leftDialog = "@conversation/corellia_privateer_trainer_2:s_f43089c2", -- Excellent!  Good luck, %NU.  And remember, Experience is something you don't get until after you need it.
	animation = "",
	stopConversation = "true",
	options = {}
}
rikkh_convo_template:addScreen(accept_duty_destroy1)

escort_duty = ConvoScreen:new {
	id = "escort_duty",
	leftDialog = "@conversation/corellia_privateer_trainer_2:s_13b10809", -- Travel to Lok Space and protect a transport that has gotten between some Imperial and Rebels.
	animation = "explain",
	stopConversation = "false",
	options = {
		{"@conversation/corellia_privateer_trainer_2:s_3b83352c", "accept_duty_escort"}, -- On my way
	}
}
rikkh_convo_template:addScreen(escort_duty)

accept_duty_escort = ConvoScreen:new {
	id = "accept_duty_escort",
	leftDialog = "@conversation/corellia_privateer_trainer_2:s_7f5b2aa", -- Fantastic!  And remember, if you lose contact with the enemy, look behind you.
	animation = "laugh_titter",
	stopConversation = "true",
	options = {}
}
rikkh_convo_template:addScreen(accept_duty_escort)

destroy_duty2 = ConvoScreen:new {
	id = "destroy_duty2",
	leftDialog = "@conversation/corellia_privateer_trainer_2:s_e5e96bc7", -- Head up to Corellia Space and destroy some Hidden Daggers.  Those pirates have been getting a little too bold lately.
	animation = "explain",
	stopConversation = "false",
	options = {
		{"@conversation/corellia_privateer_trainer_2:s_52467dab", "accept_duty_destroy2"}, -- I'll destroy them
	}
}
rikkh_convo_template:addScreen(destroy_duty2)

accept_duty_destroy2 = ConvoScreen:new {
	id = "accept_duty_destroy2",
	leftDialog = "@conversation/corellia_privateer_trainer_2:s_f1e77b0c", -- Good!  But just remember, no plan ever survives contact with the enemy.
	animation = "slow_down",
	stopConversation = "true",
	options = {}
}
rikkh_convo_template:addScreen(accept_duty_destroy2)

recovery_duty = ConvoScreen:new {
	id = "recovery_duty",
	leftDialog = "@conversation/corellia_privateer_trainer_2:s_8cd19baf", -- Nym's ships have been expanding their operations all the way out to Yavin 4.  We want to put a stop to that, but more importantly we want to recover the cargo he's been swiping from Corellian freighters!  Go recover that cargo in the Yavin system!
	animation = "explain",
	stopConversation = "false",
	options = {
		{"@conversation/corellia_privateer_trainer_2:s_9f5f269", "accept_duty_recovery"}, -- No problem
	}
}
rikkh_convo_template:addScreen(recovery_duty)

accept_duty_recovery = ConvoScreen:new {
	id = "accept_duty_recovery",
	leftDialog = "@conversation/corellia_privateer_trainer_2:s_7f5b2aa", -- Fantastic.  Don't forget:  If the enemy is within range, so are you.
	animation = "applause_polite",
	stopConversation = "true",
	options = {}
}
rikkh_convo_template:addScreen(accept_duty_recovery)

enough_joking = ConvoScreen:new {
	id = "enough_joking",
	leftDialog = "@conversation/corellia_privateer_trainer_2:s_ccadbca4", -- Enough joking around though, %NU.  I've got to get back to work.
	animation = "slow_down",
	playerAnimation = "laugh",
	stopConversation = "true",
	options = {}
}
rikkh_convo_template:addScreen(enough_joking)

enough_joking2 = ConvoScreen:new {
	id = "enough_joking2",
	leftDialog = "@conversation/corellia_privateer_trainer_2:s_9be69a2e", -- I LIKE you, %NU.  You've got the tenacity of a Bull Rancor!  But enough of this joking around... I've got to get back to work.
	animation = "slow_down",
	playerAnimation = "pound_fist_palm",
	stopConversation = "true",
	options = {}
}
rikkh_convo_template:addScreen(enough_joking2)

--[[

	Conversation Enders

]]

will_thanks = ConvoScreen:new {
	id = "will_thanks",
	leftDialog = "@conversation/corellia_privateer_trainer_2:s_c261cfae", -- No problem.
	animation = "wave2",
	stopConversation = "true",
	options = {}
}
rikkh_convo_template:addScreen(will_thanks);

back_to_work = ConvoScreen:new {
	id = "back_to_work",
	leftDialog = "@conversation/corellia_privateer_trainer_2:s_a34ecd3", -- Alright.  Well, I better get back to work.  Don't be a stranger!
	animation = "",
	stopConversation = "true",
	options = {}
}
rikkh_convo_template:addScreen(back_to_work);

done_goofing = ConvoScreen:new {
	id = "done_goofing",
	leftDialog = "@conversation/corellia_privateer_trainer_2:s_53b9240e", -- Ha ha!  Ok, enough goofing off.  I better get back to work.  Enjoy your visit to Corellia.
	animation = "",
	playerAnimation = "laugh",
	stopConversation = "true",
	options = {}
}
rikkh_convo_template:addScreen(done_goofing);

terrible_joke = ConvoScreen:new {
	id = "terrible_joke",
	leftDialog = "@conversation/corellia_privateer_trainer_2:s_12da4881", -- Yeah, well, they can't all be gems.  Anyway I'd better get back to work.  Take care, %NU.
	animation = "shrug_hands",
	stopConversation = "true",
	options = {}
}
rikkh_convo_template:addScreen(terrible_joke);

on_mission = ConvoScreen:new {
	id = "on_mission",
	leftDialog = "@conversation/corellia_privateer_trainer_2:s_658107f", -- I can see you're busy.  Come talk to me when you've got some time.  I can always use your services
	animation = "",
	stopConversation = "true",
	options = {}
}
rikkh_convo_template:addScreen(on_mission);

try_first_mission = ConvoScreen:new {
	id = "try_first_mission",
	leftDialog = "@conversation/corellia_privateer_trainer_2:s_f7394720", -- That's the spirit!  Good luck!  And don't worry, some day we'll look back on this, laugh nervously and change the subject.
	animation = "laugh_titter",
	stopConversation = "true",
	options = {}
}
rikkh_convo_template:addScreen(try_first_mission);

cant_wait_first = ConvoScreen:new {
	id = "cant_wait_first",
	leftDialog = "@conversation/corellia_privateer_trainer_2:s_7b2e95f6", -- I will always cherish the initial misconceptions I had about you.  No it can't 'wait'!  You think they're just going to cruise around waiting for you to go blow 'em up.  Get out there!
	animation = "pound_fist_palm",
	stopConversation = "true",
	options = {}
}
rikkh_convo_template:addScreen(cant_wait_first);

good_luck = ConvoScreen:new {
	id = "good_luck",
	leftDialog = "@conversation/corellia_privateer_trainer_2:s_a80d9308", -- Good luck!
	animation = "",
	stopConversation = "true",
	options = {}
}
rikkh_convo_template:addScreen(good_luck);

good_luck2 = ConvoScreen:new {
	id = "good_luck2",
	leftDialog = "@conversation/corellia_privateer_trainer_2:s_a80d9308", -- Good luck!
	animation = "wave2",
	stopConversation = "true",
	options = {}
}
rikkh_convo_template:addScreen(good_luck2);

git_gone = ConvoScreen:new {
	id = "git_gone",
	leftDialog = "@conversation/corellia_privateer_trainer_2:s_1f3b7ea2", -- Git!
	animation = "point_away",
	stopConversation = "true",
	options = {}
}
rikkh_convo_template:addScreen(git_gone);

buy_ship = ConvoScreen:new {
	id = "buy_ship",
	leftDialog = "@conversation/corellia_privateer_trainer_2:s_8694eb3f", -- You're right about that!  Unfortunately I don't have any better ships to spare.  You'll just have to buy a better ship yourself.
	animation = "nod_head_multiple",
	stopConversation = "true",
	options = {}
}
rikkh_convo_template:addScreen(buy_ship)

too_busy = ConvoScreen:new {
	id = "too_busy",
	leftDialog = "@conversation/corellia_privateer_trainer_2:s_4e3437a8", -- Oh, YOU'RE busy.  You think I don't work here?  Come talk to me when you're ready for an assignment.
	animation = "",
	stopConversation = "true",
	options = {}
}
rikkh_convo_template:addScreen(too_busy)

earned_it = ConvoScreen:new {
	id = "earned_it",
	leftDialog = "@conversation/corellia_privateer_trainer_2:s_163ba63a", -- You've earned it!  Now go out on the town and catch yourself some rest and relaxation.  You look terrible!
	animation = "belly_laugh",
	stopConversation = "true",
	options = {}
}
rikkh_convo_template:addScreen(earned_it)

fine_job = ConvoScreen:new {
	id = "fine_job",
	leftDialog = "@conversation/corellia_privateer_trainer_2:s_be500111", -- Don't get all huffy!  You're doing a fine job for Corellian Security and don't let anyone tell you otherwise!
	animation = "slow_down",
	stopConversation = "true",
	options = {}
}
rikkh_convo_template:addScreen(fine_job)

back_down = ConvoScreen:new {
	id = "back_down",
	leftDialog = "@conversation/corellia_privateer_trainer_2:s_8c0b08bf", -- That's right, 'never mind'!  Another outburst like that and I'll have you on report!
	animation = "slow_down",
	stopConversation = "true",
	options = {}
}
rikkh_convo_template:addScreen(back_down)

get_out = ConvoScreen:new {
	id = "get_out",
	leftDialog = "@conversation/corellia_privateer_trainer_2:s_d52f0739", -- That's what I thought!  Now get out of here and spend your hard-earned pay on Vasarian Brandy and Dancers.  Ha ha!
	animation = "laugh",
	stopConversation = "true",
	options = {}
}
rikkh_convo_template:addScreen(get_out)

addConversationTemplate("rikkh_convo_template", rikkh_convo_template);
