rhea_convo_template = ConvoTemplate:new {
	initialScreen = "",
	templateType = "Lua",
	luaClassHandler = "corellia_privateer_trainer_convo_handler",
	screens = {}
}

no_jtl = ConvoScreen:new {
	id = "no_jtl",
	leftDialog = "@conversation/corellia_privateer_trainer:s_698d80f7", -- Sorry, but you don't look like a pilot to me.
	stopConversation = "true",
	options = {}
}
rhea_convo_template:addScreen(no_jtl);

rebel_pilot = ConvoScreen:new {
	id = "rebel_pilot",
	leftDialog = "@conversation/corellia_privateer_trainer:s_c9f74b42", -- Greetings, citizen.  Keep your nose clean and we won't have any trouble.
	stopConversation = "true",
	options = {}
}
rhea_convo_template:addScreen(rebel_pilot);

imperial_pilot = ConvoScreen:new {
	id = "imperial_pilot",
	leftDialog = "@conversation/corellia_privateer_trainer:s_15502961", -- Nothing to worry about here, sir.  CorSec has the area well secured.
	stopConversation = "true",
	options = {}
}
rhea_convo_template:addScreen(imperial_pilot);

-- Player is a Neutral Pilot but a different squadron

non_corsec_pilot = ConvoScreen:new {
	id = "non_corsec_pilot",
	leftDialog = "@conversation/corellia_privateer_trainer:s_ff684aed", -- Ah, I've heard of you!  You're not a bad pilot from what I understand. What can the CorSec do for you?
	stopConversation = "false",
	options = {
		{"@conversation/corellia_privateer_trainer:s_c1ff5062", "im_looking_for_17"}, -- I'm looking for a mission. Do you have any?
	}
}
rhea_convo_template:addScreen(non_corsec_pilot);

























youve_got_your = ConvoScreen:new {
	id = "youve_got_your",
	leftDialog = "@conversation/corellia_privateer_trainer:s_9e5f75be", -- You've got your assignment and the control device for your ship in your datapad.  Go to the Starport and access the terminal to launch into space.
	stopConversation = "false",
	options = {
		{"@conversation/corellia_privateer_trainer:s_95d0a1f6", "an_assignment_13"}, -- An assignment?
		{"@conversation/corellia_privateer_trainer:s_bdd269be", "what_ship_14"}, -- What ship?
		{"@conversation/corellia_privateer_trainer:s_60c4f974", "where_do_i_15"}, -- Where do I go?
		{"@conversation/corellia_privateer_trainer:s_5e4ebfca", "and_when_im_16"}, -- And when I'm done?
	}
}
rhea_convo_template:addScreen(youve_got_your);









hello__come = ConvoScreen:new {
	id = "hello__come",
	leftDialog = "@conversation/corellia_privateer_trainer:s_f518ba4f", -- Hello!  Come to join the ranks of CorSec?
	stopConversation = "false",
	options = {
		{"@conversation/corellia_privateer_trainer:s_370822d1", "yes_"}, -- Yes
		{"@conversation/corellia_privateer_trainer:s_457a7010", "no_"}, -- No
		{"@conversation/corellia_privateer_trainer:s_4906b993", "what_is_corsec"}, -- What is CorSec?
	}
}
rhea_convo_template:addScreen(hello__come);

youre_going_to = ConvoScreen:new {
	id = "youre_going_to",
	leftDialog = "@conversation/corellia_privateer_trainer:s_149", -- You're going to need a ship, if you're going to fly for CorSec.  I'll add the Ship Control Codes to your datapad for you.  It's not a great ship, but it will get you around.
	stopConversation = "true",
	options = {}
}
rhea_convo_template:addScreen(youre_going_to);

what_are_you = ConvoScreen:new {
	id = "what_are_you",
	leftDialog = "@conversation/corellia_privateer_trainer:s_333f5da9", -- What are you doing talking to me?  Isn't there somewhere you're supposed to be?
	stopConversation = "true",
	options = {}
}
rhea_convo_template:addScreen(what_are_you);

listen_something_important = ConvoScreen:new {
	id = "listen_something_important",
	leftDialog = "@conversation/corellia_privateer_trainer:s_cd44e585", -- Listen, something important has come up.  The captain wants to speak to you right away!  Go speak to Captain Rikkh in the next room.
	stopConversation = "true",
	options = {}
}
rhea_convo_template:addScreen(listen_something_important);

what_happened_to = ConvoScreen:new {
	id = "what_happened_to",
	leftDialog = "@conversation/corellia_privateer_trainer:s_5cdbbd1f", -- What happened to you?  Never mind, never mind.  Get back out there and finish that patrol.
	stopConversation = "false",
	options = {
		{"@conversation/corellia_privateer_trainer:s_133a724d", "are_you_going_102"}, -- Are you going to train me after this?
	}
}
rhea_convo_template:addScreen(what_happened_to);

thats_bad_news = ConvoScreen:new {
	id = "thats_bad_news",
	leftDialog = "@conversation/corellia_privateer_trainer:s_8b8a1542", -- That's bad news, but this is just the reason why CorSec is needed!  Go back out there and take out those pirates.  Defending this system from pirates and killers is all up to us.
	stopConversation = "false",
	options = {
		{"@conversation/corellia_privateer_trainer:s_168", "are_you_going_149"}, -- Are you going to train me after this?
	}
}
rhea_convo_template:addScreen(thats_bad_news);

piracy_in_this = ConvoScreen:new {
	id = "piracy_in_this",
	leftDialog = "@conversation/corellia_privateer_trainer:s_844a124b", -- Piracy in this system has increased 17 percent since you signed-up!  This is inexcusable!  Now get out there and complete that patrol!
	stopConversation = "false",
	options = {
		{"@conversation/corellia_privateer_trainer:s_176", "are_you_going_197"}, -- Are you going to train me after this?
	}
}
rhea_convo_template:addScreen(piracy_in_this);

youre_never_going = ConvoScreen:new {
	id = "youre_never_going",
	leftDialog = "@conversation/corellia_privateer_trainer:s_429077be", -- You're never going to make a dent in the frequency of piracy in the Corellia system until you take out their leader!  Now get back out there and destroy the leader's ship!
	stopConversation = "false",
	options = {
		{"@conversation/corellia_privateer_trainer:s_183", "are_you_going_244"}, -- Are you going to train me after this?
	}
}
rhea_convo_template:addScreen(youre_never_going);

excellent_work_ = ConvoScreen:new {
	id = "excellent_work_",
	leftDialog = "@conversation/corellia_privateer_trainer:s_f053b088", -- Excellent work!
	stopConversation = "false",
	options = {
		{"@conversation/corellia_privateer_trainer:s_1c76874e", "i_was_attacked_78"}, -- I was attacked!
		{"@conversation/corellia_privateer_trainer:s_3557fc9f", "nothing_to_it_101"}, -- Nothing to it.
	}
}
rhea_convo_template:addScreen(excellent_work_);

alright_your_first = ConvoScreen:new {
	id = "alright_your_first",
	leftDialog = "@conversation/corellia_privateer_trainer:s_160", -- Alright, your first assignment is to run a simple patrol.  From time to time pirates move into the area and harass merchants in our system. Just run this simple patrol and make sure there's no criminal activity going on.
	stopConversation = "false",
	options = {
		{"@conversation/corellia_privateer_trainer:s_133a724d", "are_you_going_102"}, -- Are you going to train me after this?
	}
}
rhea_convo_template:addScreen(alright_your_first);

excellent_job_taking = ConvoScreen:new {
	id = "excellent_job_taking",
	leftDialog = "@conversation/corellia_privateer_trainer:s_926359dd", -- Excellent job taking out those pirates.  No doubt, this won't be the end of them.
	stopConversation = "false",
	options = {
		{"@conversation/corellia_privateer_trainer:s_a927c891", "whats_next_125"}, -- What's next?
		{"@conversation/corellia_privateer_trainer:s_257f178d", "it_was_a_148"}, -- It was a snap.
	}
}
rhea_convo_template:addScreen(excellent_job_taking);

so_you_were = ConvoScreen:new {
	id = "so_you_were",
	leftDialog = "@conversation/corellia_privateer_trainer:s_4801be96", -- So, you were ambushed as you ran that patrol.  We need to hit them hard to send a message... make an example out of them.  I'm going to send you in to run that scum out of the system. I am uploading some possible waypoints into your nav computer, destroy any Black Sun you find.
	stopConversation = "false",
	options = {
		{"@conversation/corellia_privateer_trainer:s_168", "are_you_going_149"}, -- Are you going to train me after this?
	}
}
rhea_convo_template:addScreen(so_you_were);

excellent_work_with = ConvoScreen:new {
	id = "excellent_work_with",
	leftDialog = "@conversation/corellia_privateer_trainer:s_f8026f5d", -- Excellent work with that escort.  It's a good thing you were running that patrol, or there's no telling what might have happened to them.  I've got a little something extra for you, too.  It's a mercenary bandolier.  It'll help you keep your things organized.
	stopConversation = "false",
	options = {
		{"@conversation/corellia_privateer_trainer:s_172", "whats_next_173"}, -- What's next?
		{"@conversation/corellia_privateer_trainer:s_ebb99364", "there_are_too_196"}, -- There are too many pirates in this system!
	}
}
rhea_convo_template:addScreen(excellent_work_with);

just_to_be = ConvoScreen:new {
	id = "just_to_be",
	leftDialog = "@conversation/corellia_privateer_trainer:s_964fb39a", -- Just to be sure that's the last of them, we need you to run another patrol.  It's a little longer than the last one, but you already know how crafty those criminals can be.
	stopConversation = "false",
	options = {
		{"@conversation/corellia_privateer_trainer:s_176", "are_you_going_197"}, -- Are you going to train me after this?
	}
}
rhea_convo_template:addScreen(just_to_be);

ha__thatll = ConvoScreen:new {
	id = "ha__thatll",
	leftDialog = "@conversation/corellia_privateer_trainer:s_dc993cdb", -- Ha!  That'll show those thugs that CorSec is not to be trifled with.  You're really going to go places in this organization, I can tell already.
	stopConversation = "false",
	options = {
		{"@conversation/corellia_privateer_trainer:s_a78a4ac3", "what_do_i_220"}, -- What do I do now?
		{"@conversation/corellia_privateer_trainer:s_af264a19", "i_love_being_243"}, -- I love being a starfighter pilot.
	}
}
rhea_convo_template:addScreen(ha__thatll);

enough_of_this = ConvoScreen:new {
	id = "enough_of_this",
	leftDialog = "@conversation/corellia_privateer_trainer:s_8e1ed7f0", -- Enough of this!  Every time we send you out, you find more pirates.  We need to go straight to the source of the problem:  Their leader.  I know you're up to this:  Go find the pirate's leader and take him out.  Let the rest of them go to the outer rim if they want easy prey.
	stopConversation = "false",
	options = {
		{"@conversation/corellia_privateer_trainer:s_183", "are_you_going_244"}, -- Are you going to train me after this?
	}
}
rhea_convo_template:addScreen(enough_of_this);

you_are_definitely = ConvoScreen:new {
	id = "you_are_definitely",
	leftDialog = "@conversation/corellia_privateer_trainer:s_5e6c7400", -- You are definitely ready to move up.  So I'll tell you what. I'll teach you about basic fighters.
	stopConversation = "false",
	options = {
		{"@conversation/corellia_privateer_trainer:s_c06c7aa9", "that_sounds_great"}, -- That sounds great.
	}
}
rhea_convo_template:addScreen(you_are_definitely);

were_quite_satisfied = ConvoScreen:new {
	id = "were_quite_satisfied",
	leftDialog = "@conversation/corellia_privateer_trainer:s_46ea46ad", -- We're quite satisfied with your level of performance.  I think it's time you learned a bit more, though.
	stopConversation = "false",
	options = {
		{"@conversation/corellia_privateer_trainer:s_229", "i_agree_247"}, -- I agree.
	}
}
rhea_convo_template:addScreen(were_quite_satisfied);

whats_on_your = ConvoScreen:new {
	id = "whats_on_your",
	leftDialog = "@conversation/corellia_privateer_trainer:s_a48c20c8", -- What's on your mind, officer? Thinking about performing some duty missions?
	stopConversation = "false",
	options = {
		{"@conversation/corellia_privateer_trainer:s_6106187c", "what_is_a_260"}, -- What is a duty mission?
		{"@conversation/corellia_privateer_trainer:s_1a7f1a1b", "yes_i_am_261"}, -- Yes I am. What duty missions are available?
		{"@conversation/corellia_privateer_trainer:s_6276c98", "no_but_how_262"}, -- No, but how about some training?
		{"@conversation/corellia_privateer_trainer:s_2883b989", "not_right_now_263"}, -- Not right now, thanks.
	}
}
rhea_convo_template:addScreen(whats_on_your);

an_assignment = ConvoScreen:new {
	id = "an_assignment",
	leftDialog = "@conversation/corellia_privateer_trainer:s_cda1bb94", -- Yes. You have your first mission, now. You'll need to fly into space to complete it. Start by launching your starship at the starport.
	stopConversation = "false",
	options = {
		{"@conversation/corellia_privateer_trainer:s_95d0a1f6", "an_assignment_13"}, -- An assignment?
		{"@conversation/corellia_privateer_trainer:s_bdd269be", "what_ship_14"}, -- What ship?
		{"@conversation/corellia_privateer_trainer:s_60c4f974", "where_do_i_15"}, -- Where do I go?
		{"@conversation/corellia_privateer_trainer:s_5e4ebfca", "and_when_im_16"}, -- And when I'm done?
	}
}
rhea_convo_template:addScreen(an_assignment);

what_ship = ConvoScreen:new {
	id = "what_ship",
	leftDialog = "@conversation/corellia_privateer_trainer:s_198b5a97", -- I've given you the control codes to a basic ship. The codes are visible in your datapad. Open your personal datapad, and review your ship status before you launch.
	stopConversation = "false",
	options = {
		{"@conversation/corellia_privateer_trainer:s_95d0a1f6", "an_assignment_13"}, -- An assignment?
		{"@conversation/corellia_privateer_trainer:s_bdd269be", "what_ship_14"}, -- What ship?
		{"@conversation/corellia_privateer_trainer:s_60c4f974", "where_do_i_15"}, -- Where do I go?
		{"@conversation/corellia_privateer_trainer:s_5e4ebfca", "and_when_im_16"}, -- And when I'm done?
	}
}
rhea_convo_template:addScreen(what_ship);

where_do_i = ConvoScreen:new {
	id = "where_do_i",
	leftDialog = "@conversation/corellia_privateer_trainer:s_4ffb02bd", -- Go to the starport. Inside the starport you will find a number of 'starship terminals.' Interface with the terminals in order to launch your starship.
	stopConversation = "false",
	options = {
		{"@conversation/corellia_privateer_trainer:s_95d0a1f6", "an_assignment_13"}, -- An assignment?
		{"@conversation/corellia_privateer_trainer:s_bdd269be", "what_ship_14"}, -- What ship?
		{"@conversation/corellia_privateer_trainer:s_60c4f974", "where_do_i_15"}, -- Where do I go?
		{"@conversation/corellia_privateer_trainer:s_5e4ebfca", "and_when_im_16"}, -- And when I'm done?
	}
}
rhea_convo_template:addScreen(where_do_i);

and_when_im = ConvoScreen:new {
	id = "and_when_im",
	leftDialog = "@conversation/corellia_privateer_trainer:s_2bbff5e2", -- When you're finished with your first mission - fly back to the 'launch waypoint' that we automatically add to your datapad. Communicate with the space station and indicate that you want to land.
	stopConversation = "false",
	options = {
		{"@conversation/corellia_privateer_trainer:s_95d0a1f6", "an_assignment_13"}, -- An assignment?
		{"@conversation/corellia_privateer_trainer:s_bdd269be", "what_ship_14"}, -- What ship?
		{"@conversation/corellia_privateer_trainer:s_60c4f974", "where_do_i_15"}, -- Where do I go?
		{"@conversation/corellia_privateer_trainer:s_5e4ebfca", "and_when_im_16"}, -- And when I'm done?
	}
}
rhea_convo_template:addScreen(and_when_im);

an_assignment_1 = ConvoScreen:new {
	id = "an_assignment_1",
	leftDialog = "@conversation/corellia_privateer_trainer:s_cda1bb94", -- Yes. You have your first mission, now. You'll need to fly into space to complete it. Start by launching your starship at the starport.
	stopConversation = "false",
	options = {
		{"@conversation/corellia_privateer_trainer:s_95d0a1f6", "an_assignment_13"}, -- An assignment?
		{"@conversation/corellia_privateer_trainer:s_bdd269be", "what_ship_14"}, -- What ship?
		{"@conversation/corellia_privateer_trainer:s_60c4f974", "where_do_i_15"}, -- Where do I go?
		{"@conversation/corellia_privateer_trainer:s_5e4ebfca", "and_when_im_16"}, -- And when I'm done?
	}
}
rhea_convo_template:addScreen(an_assignment_1);

what_ship_2 = ConvoScreen:new {
	id = "what_ship_2",
	leftDialog = "@conversation/corellia_privateer_trainer:s_198b5a97", -- I've given you the control codes to a basic ship. The codes are visible in your datapad. Open your personal datapad, and review your ship status before you launch.
	stopConversation = "false",
	options = {
		{"@conversation/corellia_privateer_trainer:s_95d0a1f6", "an_assignment_13"}, -- An assignment?
		{"@conversation/corellia_privateer_trainer:s_bdd269be", "what_ship_14"}, -- What ship?
		{"@conversation/corellia_privateer_trainer:s_60c4f974", "where_do_i_15"}, -- Where do I go?
		{"@conversation/corellia_privateer_trainer:s_5e4ebfca", "and_when_im_16"}, -- And when I'm done?
	}
}
rhea_convo_template:addScreen(what_ship_2);

where_do_i_3 = ConvoScreen:new {
	id = "where_do_i_3",
	leftDialog = "@conversation/corellia_privateer_trainer:s_4ffb02bd", -- Go to the starport. Inside the starport you will find a number of 'starship terminals.' Interface with the terminals in order to launch your starship.
	stopConversation = "false",
	options = {
		{"@conversation/corellia_privateer_trainer:s_95d0a1f6", "an_assignment_13"}, -- An assignment?
		{"@conversation/corellia_privateer_trainer:s_bdd269be", "what_ship_14"}, -- What ship?
		{"@conversation/corellia_privateer_trainer:s_60c4f974", "where_do_i_15"}, -- Where do I go?
		{"@conversation/corellia_privateer_trainer:s_5e4ebfca", "and_when_im_16"}, -- And when I'm done?
	}
}
rhea_convo_template:addScreen(where_do_i_3);

and_when_im_4 = ConvoScreen:new {
	id = "and_when_im_4",
	leftDialog = "@conversation/corellia_privateer_trainer:s_2bbff5e2", -- When you're finished with your first mission - fly back to the 'launch waypoint' that we automatically add to your datapad. Communicate with the space station and indicate that you want to land.
	stopConversation = "false",
	options = {
		{"@conversation/corellia_privateer_trainer:s_95d0a1f6", "an_assignment_13"}, -- An assignment?
		{"@conversation/corellia_privateer_trainer:s_bdd269be", "what_ship_14"}, -- What ship?
		{"@conversation/corellia_privateer_trainer:s_60c4f974", "where_do_i_15"}, -- Where do I go?
		{"@conversation/corellia_privateer_trainer:s_5e4ebfca", "and_when_im_16"}, -- And when I'm done?
	}
}
rhea_convo_template:addScreen(and_when_im_4);

an_assignment_5 = ConvoScreen:new {
	id = "an_assignment_5",
	leftDialog = "@conversation/corellia_privateer_trainer:s_cda1bb94", -- Yes. You have your first mission, now. You'll need to fly into space to complete it. Start by launching your starship at the starport.
	stopConversation = "false",
	options = {
		{"@conversation/corellia_privateer_trainer:s_95d0a1f6", "an_assignment_13"}, -- An assignment?
		{"@conversation/corellia_privateer_trainer:s_bdd269be", "what_ship_14"}, -- What ship?
		{"@conversation/corellia_privateer_trainer:s_60c4f974", "where_do_i_15"}, -- Where do I go?
		{"@conversation/corellia_privateer_trainer:s_5e4ebfca", "and_when_im_16"}, -- And when I'm done?
	}
}
rhea_convo_template:addScreen(an_assignment_5);

what_ship_6 = ConvoScreen:new {
	id = "what_ship_6",
	leftDialog = "@conversation/corellia_privateer_trainer:s_198b5a97", -- I've given you the control codes to a basic ship. The codes are visible in your datapad. Open your personal datapad, and review your ship status before you launch.
	stopConversation = "false",
	options = {
		{"@conversation/corellia_privateer_trainer:s_95d0a1f6", "an_assignment_13"}, -- An assignment?
		{"@conversation/corellia_privateer_trainer:s_bdd269be", "what_ship_14"}, -- What ship?
		{"@conversation/corellia_privateer_trainer:s_60c4f974", "where_do_i_15"}, -- Where do I go?
		{"@conversation/corellia_privateer_trainer:s_5e4ebfca", "and_when_im_16"}, -- And when I'm done?
	}
}
rhea_convo_template:addScreen(what_ship_6);

where_do_i_7 = ConvoScreen:new {
	id = "where_do_i_7",
	leftDialog = "@conversation/corellia_privateer_trainer:s_4ffb02bd", -- Go to the starport. Inside the starport you will find a number of 'starship terminals.' Interface with the terminals in order to launch your starship.
	stopConversation = "false",
	options = {
		{"@conversation/corellia_privateer_trainer:s_95d0a1f6", "an_assignment_13"}, -- An assignment?
		{"@conversation/corellia_privateer_trainer:s_bdd269be", "what_ship_14"}, -- What ship?
		{"@conversation/corellia_privateer_trainer:s_60c4f974", "where_do_i_15"}, -- Where do I go?
		{"@conversation/corellia_privateer_trainer:s_5e4ebfca", "and_when_im_16"}, -- And when I'm done?
	}
}
rhea_convo_template:addScreen(where_do_i_7);

and_when_im_8 = ConvoScreen:new {
	id = "and_when_im_8",
	leftDialog = "@conversation/corellia_privateer_trainer:s_2bbff5e2", -- When you're finished with your first mission - fly back to the 'launch waypoint' that we automatically add to your datapad. Communicate with the space station and indicate that you want to land.
	stopConversation = "false",
	options = {
		{"@conversation/corellia_privateer_trainer:s_95d0a1f6", "an_assignment_13"}, -- An assignment?
		{"@conversation/corellia_privateer_trainer:s_bdd269be", "what_ship_14"}, -- What ship?
		{"@conversation/corellia_privateer_trainer:s_60c4f974", "where_do_i_15"}, -- Where do I go?
		{"@conversation/corellia_privateer_trainer:s_5e4ebfca", "and_when_im_16"}, -- And when I'm done?
	}
}
rhea_convo_template:addScreen(and_when_im_8);

an_assignment_9 = ConvoScreen:new {
	id = "an_assignment_9",
	leftDialog = "@conversation/corellia_privateer_trainer:s_cda1bb94", -- Yes. You have your first mission, now. You'll need to fly into space to complete it. Start by launching your starship at the starport.
	stopConversation = "false",
	options = {
		{"@conversation/corellia_privateer_trainer:s_95d0a1f6", "an_assignment_13"}, -- An assignment?
		{"@conversation/corellia_privateer_trainer:s_bdd269be", "what_ship_14"}, -- What ship?
		{"@conversation/corellia_privateer_trainer:s_60c4f974", "where_do_i_15"}, -- Where do I go?
		{"@conversation/corellia_privateer_trainer:s_5e4ebfca", "and_when_im_16"}, -- And when I'm done?
	}
}
rhea_convo_template:addScreen(an_assignment_9);

what_ship_10 = ConvoScreen:new {
	id = "what_ship_10",
	leftDialog = "@conversation/corellia_privateer_trainer:s_198b5a97", -- I've given you the control codes to a basic ship. The codes are visible in your datapad. Open your personal datapad, and review your ship status before you launch.
	stopConversation = "false",
	options = {
		{"@conversation/corellia_privateer_trainer:s_95d0a1f6", "an_assignment_13"}, -- An assignment?
		{"@conversation/corellia_privateer_trainer:s_bdd269be", "what_ship_14"}, -- What ship?
		{"@conversation/corellia_privateer_trainer:s_60c4f974", "where_do_i_15"}, -- Where do I go?
		{"@conversation/corellia_privateer_trainer:s_5e4ebfca", "and_when_im_16"}, -- And when I'm done?
	}
}
rhea_convo_template:addScreen(what_ship_10);

where_do_i_11 = ConvoScreen:new {
	id = "where_do_i_11",
	leftDialog = "@conversation/corellia_privateer_trainer:s_4ffb02bd", -- Go to the starport. Inside the starport you will find a number of 'starship terminals.' Interface with the terminals in order to launch your starship.
	stopConversation = "false",
	options = {
		{"@conversation/corellia_privateer_trainer:s_95d0a1f6", "an_assignment_13"}, -- An assignment?
		{"@conversation/corellia_privateer_trainer:s_bdd269be", "what_ship_14"}, -- What ship?
		{"@conversation/corellia_privateer_trainer:s_60c4f974", "where_do_i_15"}, -- Where do I go?
		{"@conversation/corellia_privateer_trainer:s_5e4ebfca", "and_when_im_16"}, -- And when I'm done?
	}
}
rhea_convo_template:addScreen(where_do_i_11);

and_when_im_12 = ConvoScreen:new {
	id = "and_when_im_12",
	leftDialog = "@conversation/corellia_privateer_trainer:s_2bbff5e2", -- When you're finished with your first mission - fly back to the 'launch waypoint' that we automatically add to your datapad. Communicate with the space station and indicate that you want to land.
	stopConversation = "false",
	options = {
		{"@conversation/corellia_privateer_trainer:s_95d0a1f6", "an_assignment_13"}, -- An assignment?
		{"@conversation/corellia_privateer_trainer:s_bdd269be", "what_ship_14"}, -- What ship?
		{"@conversation/corellia_privateer_trainer:s_60c4f974", "where_do_i_15"}, -- Where do I go?
		{"@conversation/corellia_privateer_trainer:s_5e4ebfca", "and_when_im_16"}, -- And when I'm done?
	}
}
rhea_convo_template:addScreen(and_when_im_12);

an_assignment_13 = ConvoScreen:new {
	id = "an_assignment_13",
	leftDialog = "@conversation/corellia_privateer_trainer:s_cda1bb94", -- Yes. You have your first mission, now. You'll need to fly into space to complete it. Start by launching your starship at the starport.
	stopConversation = "false",
	options = {
		{"@conversation/corellia_privateer_trainer:s_95d0a1f6", "an_assignment_13"}, -- An assignment?
		{"@conversation/corellia_privateer_trainer:s_bdd269be", "what_ship_14"}, -- What ship?
		{"@conversation/corellia_privateer_trainer:s_60c4f974", "where_do_i_15"}, -- Where do I go?
		{"@conversation/corellia_privateer_trainer:s_5e4ebfca", "and_when_im_16"}, -- And when I'm done?
	}
}
rhea_convo_template:addScreen(an_assignment_13);

what_ship_14 = ConvoScreen:new {
	id = "what_ship_14",
	leftDialog = "@conversation/corellia_privateer_trainer:s_198b5a97", -- I've given you the control codes to a basic ship. The codes are visible in your datapad. Open your personal datapad, and review your ship status before you launch.
	stopConversation = "false",
	options = {
		{"@conversation/corellia_privateer_trainer:s_95d0a1f6", "an_assignment_13"}, -- An assignment?
		{"@conversation/corellia_privateer_trainer:s_bdd269be", "what_ship_14"}, -- What ship?
		{"@conversation/corellia_privateer_trainer:s_60c4f974", "where_do_i_15"}, -- Where do I go?
		{"@conversation/corellia_privateer_trainer:s_5e4ebfca", "and_when_im_16"}, -- And when I'm done?
	}
}
rhea_convo_template:addScreen(what_ship_14);

where_do_i_15 = ConvoScreen:new {
	id = "where_do_i_15",
	leftDialog = "@conversation/corellia_privateer_trainer:s_4ffb02bd", -- Go to the starport. Inside the starport you will find a number of 'starship terminals.' Interface with the terminals in order to launch your starship.
	stopConversation = "false",
	options = {
		{"@conversation/corellia_privateer_trainer:s_95d0a1f6", "an_assignment_13"}, -- An assignment?
		{"@conversation/corellia_privateer_trainer:s_bdd269be", "what_ship_14"}, -- What ship?
		{"@conversation/corellia_privateer_trainer:s_60c4f974", "where_do_i_15"}, -- Where do I go?
		{"@conversation/corellia_privateer_trainer:s_5e4ebfca", "and_when_im_16"}, -- And when I'm done?
	}
}
rhea_convo_template:addScreen(where_do_i_15);

and_when_im_16 = ConvoScreen:new {
	id = "and_when_im_16",
	leftDialog = "@conversation/corellia_privateer_trainer:s_2bbff5e2", -- When you're finished with your first mission - fly back to the 'launch waypoint' that we automatically add to your datapad. Communicate with the space station and indicate that you want to land.
	stopConversation = "false",
	options = {
		{"@conversation/corellia_privateer_trainer:s_95d0a1f6", "an_assignment_13"}, -- An assignment?
		{"@conversation/corellia_privateer_trainer:s_bdd269be", "what_ship_14"}, -- What ship?
		{"@conversation/corellia_privateer_trainer:s_60c4f974", "where_do_i_15"}, -- Where do I go?
		{"@conversation/corellia_privateer_trainer:s_5e4ebfca", "and_when_im_16"}, -- And when I'm done?
	}
}
rhea_convo_template:addScreen(and_when_im_16);

im_looking_for = ConvoScreen:new {
	id = "im_looking_for",
	leftDialog = "@conversation/corellia_privateer_trainer:s_dadaabf", -- As a matter of fact, I do have some duty missions that you could perform. Who knows, maybe if you do well, you might be invited to join the CorSec. Are you ready for a duty mission?
	stopConversation = "false",
	options = {
		{"@conversation/corellia_privateer_trainer:s_6106187c", "what_is_a_260"}, -- What is a duty mission?
		{"@conversation/corellia_privateer_trainer:s_1a7f1a1b", "yes_i_am_261"}, -- Yes I am. What duty missions are available?
		{"@conversation/corellia_privateer_trainer:s_6276c98", "no_but_how_262"}, -- No, but how about some training?
		{"@conversation/corellia_privateer_trainer:s_2883b989", "not_right_now_263"}, -- Not right now, thanks.
	}
}
rhea_convo_template:addScreen(im_looking_for);

im_looking_for_17 = ConvoScreen:new {
	id = "im_looking_for_17",
	leftDialog = "@conversation/corellia_privateer_trainer:s_5b8a384b", -- I'm sorry, unless you are a member of the CorSec, there's very little that I can do for you. You may want to try speaking to your own contacts if you're looking for a mission.
	stopConversation = "true",
	options = {
		{"@conversation/corellia_privateer_trainer:s_6106187c", "what_is_a_260"}, -- What is a duty mission?
		{"@conversation/corellia_privateer_trainer:s_1a7f1a1b", "yes_i_am_261"}, -- Yes I am. What duty missions are available?
		{"@conversation/corellia_privateer_trainer:s_6276c98", "no_but_how_262"}, -- No, but how about some training?
		{"@conversation/corellia_privateer_trainer:s_2883b989", "not_right_now_263"}, -- Not right now, thanks.
	}
}
rhea_convo_template:addScreen(im_looking_for_17);

what_is_a = ConvoScreen:new {
	id = "what_is_a",
	leftDialog = "@conversation/corellia_privateer_trainer:s_d43b2932", -- Duty missions are a good way for you to get experience as a pilot. Only experienced pilots can receive the proper training to learn new skills and abilities.There's no real final objective so you can end the mission whenever you want. So, would you like to take a duty mission?
	stopConversation = "false",
	options = {
		{"@conversation/corellia_privateer_trainer:s_6106187c", "what_is_a_260"}, -- What is a duty mission?
		{"@conversation/corellia_privateer_trainer:s_1a7f1a1b", "yes_i_am_261"}, -- Yes I am. What duty missions are available?
		{"@conversation/corellia_privateer_trainer:s_6276c98", "no_but_how_262"}, -- No, but how about some training?
		{"@conversation/corellia_privateer_trainer:s_2883b989", "not_right_now_263"}, -- Not right now, thanks.
	}
}
rhea_convo_template:addScreen(what_is_a);

yes_i_am = ConvoScreen:new {
	id = "yes_i_am",
	leftDialog = "@conversation/corellia_privateer_trainer:s_d6a6a9fc", -- Well, merchant freighters are always in need of escorts, or if you like you can help in the fight against the pirate leaders. What interests you?
	stopConversation = "false",
	options = {
		{"@conversation/corellia_privateer_trainer:s_9e417b37", "the_pirate_leaders"}, -- The Pirate Leaders
		{"@conversation/corellia_privateer_trainer:s_221daf73", "escorting_merchants"}, -- Escorting Merchants
		{"@conversation/corellia_privateer_trainer:s_c35e70d2", "nothing_right_now"}, -- Nothing right now.
	}
}
rhea_convo_template:addScreen(yes_i_am);

no_but_how = ConvoScreen:new {
	id = "no_but_how",
	leftDialog = "@conversation/corellia_privateer_trainer:s_e5c453e0", -- You're not ready for more training yet. But duty missions are a good way of getting good experience so that you'll be ready for training soon. What do you say? Are you ready to try a duty mission?
	stopConversation = "false",
	options = {
		{"@conversation/corellia_privateer_trainer:s_6106187c", "what_is_a_260"}, -- What is a duty mission?
		{"@conversation/corellia_privateer_trainer:s_1a7f1a1b", "yes_i_am_261"}, -- Yes I am. What duty missions are available?
		{"@conversation/corellia_privateer_trainer:s_6276c98", "no_but_how_262"}, -- No, but how about some training?
		{"@conversation/corellia_privateer_trainer:s_2883b989", "not_right_now_263"}, -- Not right now, thanks.
	}
}
rhea_convo_template:addScreen(no_but_how);

not_right_now = ConvoScreen:new {
	id = "not_right_now",
	leftDialog = "@conversation/corellia_privateer_trainer:s_228", -- Maybe next time then.
	stopConversation = "true",
	options = {}
}
rhea_convo_template:addScreen(not_right_now);

yes_ = ConvoScreen:new {
	id = "yes_",
	leftDialog = "@conversation/corellia_privateer_trainer:s_63a61222", -- We don't let just anyone join.  There'll be a background check of course.
	stopConversation = "false",
	options = {
		{"@conversation/corellia_privateer_trainer:s_1418de80", "of_course_19"}, -- Of course
		{"@conversation/corellia_privateer_trainer:s_77e48d5b", "what_do_you_21"}, -- What do you mean?
		{"@conversation/corellia_privateer_trainer:s_64b308bc", "thats_ridiculous_23"}, -- That's ridiculous!
	}
}
rhea_convo_template:addScreen(yes_);

no_ = ConvoScreen:new {
	id = "no_",
	leftDialog = "@conversation/corellia_privateer_trainer:s_c8c21783", -- In that case, move along.  We're very busy here.
	stopConversation = "true",
	options = {}
}
rhea_convo_template:addScreen(no_);

what_is_corsec = ConvoScreen:new {
	id = "what_is_corsec",
	leftDialog = "@conversation/corellia_privateer_trainer:s_40061f60", -- CorSec is Corellia's local Security force.  As you know, Corellia is officially neutral in the Galactic Civil War... or at least as neutral as a world can be in this day and age.  We provide defense and law enforcement for the entire Corellian system.
	stopConversation = "false",
	options = {
		{"@conversation/corellia_privateer_trainer:s_deaabd84", "oh_no"}, -- Oh.  No thanks
		{"@conversation/corellia_privateer_trainer:s_614b71f0", "i_see"}, -- I see...
	}
}
rhea_convo_template:addScreen(what_is_corsec);

of_course = ConvoScreen:new {
	id = "of_course",
	leftDialog = "@conversation/corellia_privateer_trainer:s_be5a7539", -- This will only take a moment... Ah... Well according to this you've run into a problem with the law.  Are you certain you want to join CorSec?
	stopConversation = "false",
	options = {}
}
rhea_convo_template:addScreen(of_course);

of_course_18 = ConvoScreen:new {
	id = "of_course_18",
	leftDialog = "@conversation/corellia_privateer_trainer:s_7df39542", -- This will only take a moment... Oh... Wow!  You've got an excellent track record.  I guess you've tangled with your share of criminals and thugs in your day. Are you ready to begin?
	stopConversation = "false",
	options = {
		{"@conversation/corellia_privateer_trainer:s_30", "yes_i_am_27"}, -- Yes I am
		{"@conversation/corellia_privateer_trainer:s_51", "no_thanks_28"}, -- No thanks
	}
}
rhea_convo_template:addScreen(of_course_18);

of_course_19 = ConvoScreen:new {
	id = "of_course_19",
	leftDialog = "@conversation/corellia_privateer_trainer:s_ee2895df", -- This will only take a moment... Ah... You've got a pretty clean record here.  I can assure you that it will improve once you're flying for CorSec! Are you ready to begin?
	stopConversation = "false",
	options = {
		{"@conversation/corellia_privateer_trainer:s_30", "yes_i_am_27"}, -- Yes I am
		{"@conversation/corellia_privateer_trainer:s_51", "no_thanks_28"}, -- No thanks
		{"@conversation/corellia_privateer_trainer:s_30", "yes_i_am_27"}, -- Yes I am
		{"@conversation/corellia_privateer_trainer:s_51", "no_thanks_28"}, -- No thanks
	}
}
rhea_convo_template:addScreen(of_course_19);

what_do_you = ConvoScreen:new {
	id = "what_do_you",
	leftDialog = "@conversation/corellia_privateer_trainer:s_b06e1df9", -- Don't worry, this will only take a moment.  We do need to ensure you're not some sort of criminal... Ah... Well according to this you haven't exactly been the most law abiding citizen on Corellia... Are you certain you want to join CorSec?
	stopConversation = "false",
	options = {}
}
rhea_convo_template:addScreen(what_do_you);

what_do_you_20 = ConvoScreen:new {
	id = "what_do_you_20",
	leftDialog = "@conversation/corellia_privateer_trainer:s_ea3dcf32", -- Don't worry, this will only take a moment... Oh... Wow!  You've got an excellent track record.  I guess you've tangled with your share of criminals and thugs in your day. Are you ready to begin?
	stopConversation = "false",
	options = {
		{"@conversation/corellia_privateer_trainer:s_65", "i_guess_so_33"}, -- I guess so.
		{"@conversation/corellia_privateer_trainer:s_96", "i_dont_think_34"}, -- I don't think so
	}
}
rhea_convo_template:addScreen(what_do_you_20);

what_do_you_21 = ConvoScreen:new {
	id = "what_do_you_21",
	leftDialog = "@conversation/corellia_privateer_trainer:s_898027d6", -- Don't worry, this will only take a moment... Ah... You've got a pretty clean record here.  I can assure you that it will improve once you're flying for CorSec! Are you ready to begin?
	stopConversation = "false",
	options = {
		{"@conversation/corellia_privateer_trainer:s_65", "i_guess_so_33"}, -- I guess so.
		{"@conversation/corellia_privateer_trainer:s_96", "i_dont_think_34"}, -- I don't think so
		{"@conversation/corellia_privateer_trainer:s_65", "i_guess_so_33"}, -- I guess so.
		{"@conversation/corellia_privateer_trainer:s_96", "i_dont_think_34"}, -- I don't think so
	}
}
rhea_convo_template:addScreen(what_do_you_21);

thats_ridiculous = ConvoScreen:new {
	id = "thats_ridiculous",
	leftDialog = "@conversation/corellia_privateer_trainer:s_d72a0d47", -- Not at all.  We can't have thugs and ne'er-do-wells joining CorSec.  We're here to provide security for the citizens of Corellia!  Now, this will only take a moment... Ah... Well according to this you've run into a problem with the law.  Are you certain you want to join CorSec?
	stopConversation = "false",
	options = {}
}
rhea_convo_template:addScreen(thats_ridiculous);

thats_ridiculous_22 = ConvoScreen:new {
	id = "thats_ridiculous_22",
	leftDialog = "@conversation/corellia_privateer_trainer:s_cec02f8", -- Not at all.  We can't have thugs and ne'er-do-wells joining CorSec.  We're here to provide security for the citizens of Corellia!  Now, this will only take a moment... Oh... Wow!  You've got an excellent track record.  I guess you've tangled with your share of criminals and thugs in your day. Are you ready to begin?
	stopConversation = "false",
	options = {
		{"@conversation/corellia_privateer_trainer:s_108", "maybe__44"}, -- Maybe.
		{"@conversation/corellia_privateer_trainer:s_139", "maybe_not_45"}, -- Maybe not.
	}
}
rhea_convo_template:addScreen(thats_ridiculous_22);

thats_ridiculous_23 = ConvoScreen:new {
	id = "thats_ridiculous_23",
	leftDialog = "@conversation/corellia_privateer_trainer:s_7396ebcf", -- Not at all.  We can't have thugs and ne'er-do-wells joining CorSec.  We're here to provide security for the citizens of Corellia!  Now, this will only take a moment... Ah... You've got a pretty clean record here.  I can assure you that it'd improve once you're flying for CorSec! Are you ready to begin?
	stopConversation = "false",
	options = {
		{"@conversation/corellia_privateer_trainer:s_108", "maybe__44"}, -- Maybe.
		{"@conversation/corellia_privateer_trainer:s_139", "maybe_not_45"}, -- Maybe not.
		{"@conversation/corellia_privateer_trainer:s_108", "maybe__44"}, -- Maybe.
		{"@conversation/corellia_privateer_trainer:s_139", "maybe_not_45"}, -- Maybe not.
	}
}
rhea_convo_template:addScreen(thats_ridiculous_23);

yes_i_am_24 = ConvoScreen:new {
	id = "yes_i_am_24",
	leftDialog = "@conversation/corellia_privateer_trainer:s_2c6a1c50", -- I'm sorry, but I'm afraid it's completely out of the question with your history.  You're going to have to clean up your act before you can join CorSec.
	stopConversation = "true",
	options = {}
}
rhea_convo_template:addScreen(yes_i_am_24);

no_thanks = ConvoScreen:new {
	id = "no_thanks",
	leftDialog = "@conversation/corellia_privateer_trainer:s_2b418533", -- Perhaps you'll turn your life around, decide to be a part of the solution instead of a part of the problem.  When you're ready to help enforce the law instead of breaking it, come see me.
	stopConversation = "true",
	options = {}
}
rhea_convo_template:addScreen(no_thanks);

yes_i_am_25 = ConvoScreen:new {
	id = "yes_i_am_25",
	leftDialog = "@conversation/corellia_privateer_trainer:s_40617d3", -- Indeed.  Do you have your own ship?
	stopConversation = "false",
	options = {}
}
rhea_convo_template:addScreen(yes_i_am_25);

no_thanks_26 = ConvoScreen:new {
	id = "no_thanks_26",
	leftDialog = "@conversation/corellia_privateer_trainer:s_36adcd36", -- What?  Are you sure?  You'd make an excellent candidate.
	stopConversation = "false",
	options = {
		{"@conversation/corellia_privateer_trainer:s_8acaf405", "positive_i"}, -- Positive.  I don't want to join CorSec
		{"@conversation/corellia_privateer_trainer:s_e258dc9b", "youre_right"}, -- You're right.  Sign me up!
	}
}
rhea_convo_template:addScreen(no_thanks_26);

yes_i_am_27 = ConvoScreen:new {
	id = "yes_i_am_27",
	leftDialog = "@conversation/corellia_privateer_trainer:s_40617d3", -- Indeed.  Do you have your own ship?
	stopConversation = "false",
	options = {}
}
rhea_convo_template:addScreen(yes_i_am_27);

no_thanks_28 = ConvoScreen:new {
	id = "no_thanks_28",
	leftDialog = "@conversation/corellia_privateer_trainer:s_36adcd36", -- What?  Are you sure?  You'd make an excellent candidate.
	stopConversation = "false",
	options = {
		{"@conversation/corellia_privateer_trainer:s_8acaf405", "positive_i"}, -- Positive.  I don't want to join CorSec
		{"@conversation/corellia_privateer_trainer:s_e258dc9b", "youre_right"}, -- You're right.  Sign me up!
	}
}
rhea_convo_template:addScreen(no_thanks_28);

ah_no_i = ConvoScreen:new {
	id = "ah_no_i",
	leftDialog = "@conversation/corellia_privateer_trainer:s_4e95069b", -- You're going to need a ship, if you're going to fly for CorSec.  I'll add the Ship Control Codes to your datapad for you.  It's not a great ship, but it will get you around.
	stopConversation = "false",
	options = {
		{"@conversation/corellia_privateer_trainer:s_b9b27823", "thank_you"}, -- Thank you.
	}
}
rhea_convo_template:addScreen(ah_no_i);

yes_i_do = ConvoScreen:new {
	id = "yes_i_do",
	leftDialog = "@conversation/corellia_privateer_trainer:s_ddfbd948", -- Well then. I think that about does it. Are you ready for your first assignment?
	stopConversation = "false",
	options = {
		{"@conversation/corellia_privateer_trainer:s_43", "yes_im_ready_29"}, -- Yes, I'm ready.
		{"@conversation/corellia_privateer_trainer:s_47", "i_need_to_30"}, -- I need to take care of some things first.
	}
}
rhea_convo_template:addScreen(yes_i_do);

thank_you = ConvoScreen:new {
	id = "thank_you",
	leftDialog = "@conversation/corellia_privateer_trainer:s_80a724aa", -- Well now, I think that does it. Are you ready for your first assignment?
	stopConversation = "false",
	options = {
		{"@conversation/corellia_privateer_trainer:s_4a1d2431", "yes_im_ready"}, -- Yes, I'm ready.
		{"@conversation/corellia_privateer_trainer:s_68660d24", "i_need_to"}, -- I need to take care of some things first.
	}
}
rhea_convo_template:addScreen(thank_you);

yes_im_ready = ConvoScreen:new {
	id = "yes_im_ready",
	leftDialog = "@conversation/corellia_privateer_trainer:s_cc53ba8f", -- Alright, your first assignment is to run a simple patrol.  From time to time pirates move into the area and harass merchants in our system. Just run this simple patrol and make sure there's no criminal activity going on.
	stopConversation = "true",
	options = {}
}
rhea_convo_template:addScreen(yes_im_ready);

i_need_to = ConvoScreen:new {
	id = "i_need_to",
	leftDialog = "@conversation/corellia_privateer_trainer:s_c697d2d5", -- Certainly. Just come speak with me again when you're ready.
	stopConversation = "true",
	options = {}
}
rhea_convo_template:addScreen(i_need_to);

yes_im_ready_29 = ConvoScreen:new {
	id = "yes_im_ready_29",
	leftDialog = "@conversation/corellia_privateer_trainer:s_45", -- Alright, your first assignment is to run a simple patrol.  From time to time pirates move into the area and harass merchants in our system. Just run this simple patrol and make sure there's no criminal activity going on.
	stopConversation = "true",
	options = {}
}
rhea_convo_template:addScreen(yes_im_ready_29);

i_need_to_30 = ConvoScreen:new {
	id = "i_need_to_30",
	leftDialog = "@conversation/corellia_privateer_trainer:s_49", -- Certainly. Just come speak with me again when you're ready.
	stopConversation = "true",
	options = {}
}
rhea_convo_template:addScreen(i_need_to_30);

positive_i = ConvoScreen:new {
	id = "positive_i",
	leftDialog = "@conversation/corellia_privateer_trainer:s_f176d13", -- Oh?  Well.  Ok.  Come see me if you change your mind.  We could really use you.
	stopConversation = "true",
	options = {}
}
rhea_convo_template:addScreen(positive_i);

youre_right = ConvoScreen:new {
	id = "youre_right",
	leftDialog = "@conversation/corellia_privateer_trainer:s_40617d3", -- Indeed.  Do you have your own ship?
	stopConversation = "false",
	options = {}
}
rhea_convo_template:addScreen(youre_right);

i_guess_so = ConvoScreen:new {
	id = "i_guess_so",
	leftDialog = "@conversation/corellia_privateer_trainer:s_1a1a36a3", -- Completely out of the question with your history.  You're going to have to clean up your act before you can join CorSec.
	stopConversation = "true",
	options = {}
}
rhea_convo_template:addScreen(i_guess_so);

i_dont_think = ConvoScreen:new {
	id = "i_dont_think",
	leftDialog = "@conversation/corellia_privateer_trainer:s_8b451c3f", -- All right.  But you'd better clean up your act if you ever change your mind.  We can't have CorSec members with your kind of history.
	stopConversation = "true",
	options = {}
}
rhea_convo_template:addScreen(i_dont_think);

i_guess_so_31 = ConvoScreen:new {
	id = "i_guess_so_31",
	leftDialog = "@conversation/corellia_privateer_trainer:s_f3fdecfc", -- Then I will add you to the roster.  Do you have your own ship?
	stopConversation = "false",
	options = {}
}
rhea_convo_template:addScreen(i_guess_so_31);

i_dont_think_32 = ConvoScreen:new {
	id = "i_dont_think_32",
	leftDialog = "@conversation/corellia_privateer_trainer:s_8358aeb7", -- Very well.  Let me know if you change your mind.
	stopConversation = "true",
	options = {}
}
rhea_convo_template:addScreen(i_dont_think_32);

i_guess_so_33 = ConvoScreen:new {
	id = "i_guess_so_33",
	leftDialog = "@conversation/corellia_privateer_trainer:s_f3fdecfc", -- Then I will add you to the roster.  Do you have your own ship?
	stopConversation = "false",
	options = {}
}
rhea_convo_template:addScreen(i_guess_so_33);

i_dont_think_34 = ConvoScreen:new {
	id = "i_dont_think_34",
	leftDialog = "@conversation/corellia_privateer_trainer:s_8358aeb7", -- Very well.  Let me know if you change your mind.
	stopConversation = "true",
	options = {}
}
rhea_convo_template:addScreen(i_dont_think_34);

ah_no_i_35 = ConvoScreen:new {
	id = "ah_no_i_35",
	leftDialog = "@conversation/corellia_privateer_trainer:s_70", -- You're going to need a ship, if you're going to fly for CorSec.  I'll add the Ship Control Codes to your datapad for you.  It's not a great ship, but it will get you around.
	stopConversation = "false",
	options = {
		{"@conversation/corellia_privateer_trainer:s_72", "thank_you_37"}, -- Thank you.
	}
}
rhea_convo_template:addScreen(ah_no_i_35);

yes_i_do_36 = ConvoScreen:new {
	id = "yes_i_do_36",
	leftDialog = "@conversation/corellia_privateer_trainer:s_86", -- Well then. I think that about does it. Are you ready for your first assignment?
	stopConversation = "false",
	options = {
		{"@conversation/corellia_privateer_trainer:s_88", "yes_im_ready_40"}, -- Yes, I'm ready.
		{"@conversation/corellia_privateer_trainer:s_92", "i_need_to_41"}, -- I need to take care of some things first.
	}
}
rhea_convo_template:addScreen(yes_i_do_36);

thank_you_37 = ConvoScreen:new {
	id = "thank_you_37",
	leftDialog = "@conversation/corellia_privateer_trainer:s_74", -- Well now, I think that does it. Are you ready for your first assignment?
	stopConversation = "false",
	options = {
		{"@conversation/corellia_privateer_trainer:s_76", "yes_im_ready_38"}, -- Yes, I'm ready.
		{"@conversation/corellia_privateer_trainer:s_80", "i_need_to_39"}, -- I need to take care of some things first.
	}
}
rhea_convo_template:addScreen(thank_you_37);

yes_im_ready_38 = ConvoScreen:new {
	id = "yes_im_ready_38",
	leftDialog = "@conversation/corellia_privateer_trainer:s_78", -- Alright, your first assignment is to run a simple patrol.  From time to time pirates move into the area and harass merchants in our system. Just run this simple patrol and make sure there's no criminal activity going on.
	stopConversation = "true",
	options = {}
}
rhea_convo_template:addScreen(yes_im_ready_38);

i_need_to_39 = ConvoScreen:new {
	id = "i_need_to_39",
	leftDialog = "@conversation/corellia_privateer_trainer:s_82", -- Certainly. Just come speak with me again when you're ready.
	stopConversation = "true",
	options = {}
}
rhea_convo_template:addScreen(i_need_to_39);

yes_im_ready_40 = ConvoScreen:new {
	id = "yes_im_ready_40",
	leftDialog = "@conversation/corellia_privateer_trainer:s_90", -- Alright, your first assignment is to run a simple patrol.  From time to time pirates move into the area and harass merchants in our system. Just run this simple patrol and make sure there's no criminal activity going on.
	stopConversation = "true",
	options = {}
}
rhea_convo_template:addScreen(yes_im_ready_40);

i_need_to_41 = ConvoScreen:new {
	id = "i_need_to_41",
	leftDialog = "@conversation/corellia_privateer_trainer:s_94", -- Certainly. Just come speak with me again when you're ready.
	stopConversation = "true",
	options = {}
}
rhea_convo_template:addScreen(i_need_to_41);

maybe_ = ConvoScreen:new {
	id = "maybe_",
	leftDialog = "@conversation/corellia_privateer_trainer:s_342d1bdf", -- It's completely out of the question with your history.  If you want to work for CorSec then you're going to have to clean up your act.
	stopConversation = "true",
	options = {}
}
rhea_convo_template:addScreen(maybe_);

maybe_not = ConvoScreen:new {
	id = "maybe_not",
	leftDialog = "@conversation/corellia_privateer_trainer:s_104", -- It's completely out of the question with your history.  If you want to work for CorSec then you're going to have to clean up your act.
	stopConversation = "true",
	options = {}
}
rhea_convo_template:addScreen(maybe_not);

maybe__42 = ConvoScreen:new {
	id = "maybe__42",
	leftDialog = "@conversation/corellia_privateer_trainer:s_e0dfe067", -- Very well.  I'll go ahead and sign you up.  Do you have your own ship?
	stopConversation = "false",
	options = {}
}
rhea_convo_template:addScreen(maybe__42);

maybe_not_43 = ConvoScreen:new {
	id = "maybe_not_43",
	leftDialog = "@conversation/corellia_privateer_trainer:s_746a1bed", -- Ok.  Bye.  Come see me if you change your mind.
	stopConversation = "true",
	options = {}
}
rhea_convo_template:addScreen(maybe_not_43);

maybe__44 = ConvoScreen:new {
	id = "maybe__44",
	leftDialog = "@conversation/corellia_privateer_trainer:s_e0dfe067", -- Very well.  I'll go ahead and sign you up.  Do you have your own ship?
	stopConversation = "false",
	options = {}
}
rhea_convo_template:addScreen(maybe__44);

maybe_not_45 = ConvoScreen:new {
	id = "maybe_not_45",
	leftDialog = "@conversation/corellia_privateer_trainer:s_746a1bed", -- Ok.  Bye.  Come see me if you change your mind.
	stopConversation = "true",
	options = {}
}
rhea_convo_template:addScreen(maybe_not_45);

ah_no_i_46 = ConvoScreen:new {
	id = "ah_no_i_46",
	leftDialog = "@conversation/corellia_privateer_trainer:s_113", -- You're going to need a ship, if you're going to fly for CorSec.  I'll add the Ship Control Codes to your datapad for you.  It's not a great ship, but it will get you around.
	stopConversation = "false",
	options = {
		{"@conversation/corellia_privateer_trainer:s_115", "thank_you_48"}, -- Thank you.
	}
}
rhea_convo_template:addScreen(ah_no_i_46);

yes_i_do_47 = ConvoScreen:new {
	id = "yes_i_do_47",
	leftDialog = "@conversation/corellia_privateer_trainer:s_129", -- Well then. I think that about does it. Are you ready for your first assignment?
	stopConversation = "false",
	options = {
		{"@conversation/corellia_privateer_trainer:s_131", "yes_im_ready_51"}, -- Yes, I'm ready.
		{"@conversation/corellia_privateer_trainer:s_135", "i_need_to_52"}, -- I need to take care of some things first.
	}
}
rhea_convo_template:addScreen(yes_i_do_47);

thank_you_48 = ConvoScreen:new {
	id = "thank_you_48",
	leftDialog = "@conversation/corellia_privateer_trainer:s_117", -- Well now, I think that does it. Are you ready for your first assignment?
	stopConversation = "false",
	options = {
		{"@conversation/corellia_privateer_trainer:s_119", "yes_im_ready_49"}, -- Yes, I'm ready.
		{"@conversation/corellia_privateer_trainer:s_123", "i_need_to_50"}, -- I need to take care of some things first.
	}
}
rhea_convo_template:addScreen(thank_you_48);

yes_im_ready_49 = ConvoScreen:new {
	id = "yes_im_ready_49",
	leftDialog = "@conversation/corellia_privateer_trainer:s_121", -- Alright, your first assignment is to run a simple patrol.  From time to time pirates move into the area and harass merchants in our system. Just run this simple patrol and make sure there's no criminal activity going on.
	stopConversation = "true",
	options = {}
}
rhea_convo_template:addScreen(yes_im_ready_49);

i_need_to_50 = ConvoScreen:new {
	id = "i_need_to_50",
	leftDialog = "@conversation/corellia_privateer_trainer:s_125", -- Certainly. Just come speak with me again when you're ready.
	stopConversation = "true",
	options = {}
}
rhea_convo_template:addScreen(i_need_to_50);

yes_im_ready_51 = ConvoScreen:new {
	id = "yes_im_ready_51",
	leftDialog = "@conversation/corellia_privateer_trainer:s_133", -- Alright, your first assignment is to run a simple patrol.  From time to time pirates move into the area and harass merchants in our system. Just run this simple patrol and make sure there's no criminal activity going on.
	stopConversation = "true",
	options = {}
}
rhea_convo_template:addScreen(yes_im_ready_51);

i_need_to_52 = ConvoScreen:new {
	id = "i_need_to_52",
	leftDialog = "@conversation/corellia_privateer_trainer:s_137", -- Certainly. Just come speak with me again when you're ready.
	stopConversation = "true",
	options = {}
}
rhea_convo_template:addScreen(i_need_to_52);

oh_no = ConvoScreen:new {
	id = "oh_no",
	leftDialog = "@conversation/corellia_privateer_trainer:s_580337ba", -- Very well, then please move along.  I am very busy.
	stopConversation = "true",
	options = {}
}
rhea_convo_template:addScreen(oh_no);

i_see = ConvoScreen:new {
	id = "i_see",
	leftDialog = "@conversation/corellia_privateer_trainer:s_63a61222", -- We don't let just anyone join.  There'll be a background check of course.
	stopConversation = "false",
	options = {
		{"@conversation/corellia_privateer_trainer:s_1418de80", "of_course_19"}, -- Of course
		{"@conversation/corellia_privateer_trainer:s_77e48d5b", "what_do_you_21"}, -- What do you mean?
		{"@conversation/corellia_privateer_trainer:s_64b308bc", "thats_ridiculous_23"}, -- That's ridiculous!
	}
}
rhea_convo_template:addScreen(i_see);

are_you_going = ConvoScreen:new {
	id = "are_you_going",
	leftDialog = "@conversation/corellia_privateer_trainer:s_8e5b619a", -- Oh no, not quite so fast, %NU.  You complete a few more assignments and then we'll see about getting you some training!
	stopConversation = "true",
	options = {}
}
rhea_convo_template:addScreen(are_you_going);

are_you_going_53 = ConvoScreen:new {
	id = "are_you_going_53",
	leftDialog = "@conversation/corellia_privateer_trainer:s_c91ba06e", -- Not just yet, %NU.  I have just a few more things for you to do before you get any training from me.
	stopConversation = "true",
	options = {}
}
rhea_convo_template:addScreen(are_you_going_53);

are_you_going_54 = ConvoScreen:new {
	id = "are_you_going_54",
	leftDialog = "@conversation/corellia_privateer_trainer:s_e926d5f0", -- Almost, %NU.  I have just a couple more things for you to take care of before you can be trained further.  Starting with that patrol...
	stopConversation = "true",
	options = {}
}
rhea_convo_template:addScreen(are_you_going_54);

are_you_going_55 = ConvoScreen:new {
	id = "are_you_going_55",
	leftDialog = "@conversation/corellia_privateer_trainer:s_28435d2", -- Tell you what, %NU.  Kill that pirate leader and YES, I will train you.
	stopConversation = "true",
	options = {}
}
rhea_convo_template:addScreen(are_you_going_55);

i_was_attacked = ConvoScreen:new {
	id = "i_was_attacked",
	leftDialog = "@conversation/corellia_privateer_trainer:s_9e5f75be", -- You've got your assignment and the control device for your ship in your datapad.  Go to the Starport and access the terminal to launch into space.
	stopConversation = "false",
	options = {
		{"@conversation/corellia_privateer_trainer:s_95d0a1f6", "an_assignment_13"}, -- An assignment?
		{"@conversation/corellia_privateer_trainer:s_bdd269be", "what_ship_14"}, -- What ship?
		{"@conversation/corellia_privateer_trainer:s_60c4f974", "where_do_i_15"}, -- Where do I go?
		{"@conversation/corellia_privateer_trainer:s_5e4ebfca", "and_when_im_16"}, -- And when I'm done?
	}
}
rhea_convo_template:addScreen(i_was_attacked);

i_was_attacked_56 = ConvoScreen:new {
	id = "i_was_attacked_56",
	leftDialog = "@conversation/corellia_privateer_trainer:s_698d80f7", -- Sorry, but you don't look like a pilot to me.
	stopConversation = "true",
	options = {
		{"@conversation/corellia_privateer_trainer:s_95d0a1f6", "an_assignment_13"}, -- An assignment?
		{"@conversation/corellia_privateer_trainer:s_bdd269be", "what_ship_14"}, -- What ship?
		{"@conversation/corellia_privateer_trainer:s_60c4f974", "where_do_i_15"}, -- Where do I go?
		{"@conversation/corellia_privateer_trainer:s_5e4ebfca", "and_when_im_16"}, -- And when I'm done?
	}
}
rhea_convo_template:addScreen(i_was_attacked_56);

i_was_attacked_57 = ConvoScreen:new {
	id = "i_was_attacked_57",
	leftDialog = "@conversation/corellia_privateer_trainer:s_c9f74b42", -- Greetings, citizen.  Keep your nose clean and we won't have any trouble.
	stopConversation = "true",
	options = {
		{"@conversation/corellia_privateer_trainer:s_95d0a1f6", "an_assignment_13"}, -- An assignment?
		{"@conversation/corellia_privateer_trainer:s_bdd269be", "what_ship_14"}, -- What ship?
		{"@conversation/corellia_privateer_trainer:s_60c4f974", "where_do_i_15"}, -- Where do I go?
		{"@conversation/corellia_privateer_trainer:s_5e4ebfca", "and_when_im_16"}, -- And when I'm done?
	}
}
rhea_convo_template:addScreen(i_was_attacked_57);

i_was_attacked_58 = ConvoScreen:new {
	id = "i_was_attacked_58",
	leftDialog = "@conversation/corellia_privateer_trainer:s_15502961", -- Nothing to worry about here, sir.  CorSec has the area well secured.
	stopConversation = "true",
	options = {
		{"@conversation/corellia_privateer_trainer:s_95d0a1f6", "an_assignment_13"}, -- An assignment?
		{"@conversation/corellia_privateer_trainer:s_bdd269be", "what_ship_14"}, -- What ship?
		{"@conversation/corellia_privateer_trainer:s_60c4f974", "where_do_i_15"}, -- Where do I go?
		{"@conversation/corellia_privateer_trainer:s_5e4ebfca", "and_when_im_16"}, -- And when I'm done?
	}
}
rhea_convo_template:addScreen(i_was_attacked_58);

i_was_attacked_59 = ConvoScreen:new {
	id = "i_was_attacked_59",
	leftDialog = "@conversation/corellia_privateer_trainer:s_ff684aed", -- Ah, I've heard of you!  You're not a bad pilot from what I understand. What can the CorSec do for you?
	stopConversation = "false",
	options = {
		{"@conversation/corellia_privateer_trainer:s_95d0a1f6", "an_assignment_13"}, -- An assignment?
		{"@conversation/corellia_privateer_trainer:s_bdd269be", "what_ship_14"}, -- What ship?
		{"@conversation/corellia_privateer_trainer:s_60c4f974", "where_do_i_15"}, -- Where do I go?
		{"@conversation/corellia_privateer_trainer:s_5e4ebfca", "and_when_im_16"}, -- And when I'm done?
		{"@conversation/corellia_privateer_trainer:s_c1ff5062", "im_looking_for_17"}, -- I'm looking for a mission. Do you have any?
	}
}
rhea_convo_template:addScreen(i_was_attacked_59);

i_was_attacked_60 = ConvoScreen:new {
	id = "i_was_attacked_60",
	leftDialog = "@conversation/corellia_privateer_trainer:s_f518ba4f", -- Hello!  Come to join the ranks of CorSec?
	stopConversation = "false",
	options = {
		{"@conversation/corellia_privateer_trainer:s_95d0a1f6", "an_assignment_13"}, -- An assignment?
		{"@conversation/corellia_privateer_trainer:s_bdd269be", "what_ship_14"}, -- What ship?
		{"@conversation/corellia_privateer_trainer:s_60c4f974", "where_do_i_15"}, -- Where do I go?
		{"@conversation/corellia_privateer_trainer:s_5e4ebfca", "and_when_im_16"}, -- And when I'm done?
		{"@conversation/corellia_privateer_trainer:s_c1ff5062", "im_looking_for_17"}, -- I'm looking for a mission. Do you have any?
	}
}
rhea_convo_template:addScreen(i_was_attacked_60);

i_was_attacked_61 = ConvoScreen:new {
	id = "i_was_attacked_61",
	leftDialog = "@conversation/corellia_privateer_trainer:s_149", -- You're going to need a ship, if you're going to fly for CorSec.  I'll add the Ship Control Codes to your datapad for you.  It's not a great ship, but it will get you around.
	stopConversation = "true",
	options = {
		{"@conversation/corellia_privateer_trainer:s_95d0a1f6", "an_assignment_13"}, -- An assignment?
		{"@conversation/corellia_privateer_trainer:s_bdd269be", "what_ship_14"}, -- What ship?
		{"@conversation/corellia_privateer_trainer:s_60c4f974", "where_do_i_15"}, -- Where do I go?
		{"@conversation/corellia_privateer_trainer:s_5e4ebfca", "and_when_im_16"}, -- And when I'm done?
		{"@conversation/corellia_privateer_trainer:s_c1ff5062", "im_looking_for_17"}, -- I'm looking for a mission. Do you have any?
	}
}
rhea_convo_template:addScreen(i_was_attacked_61);

i_was_attacked_62 = ConvoScreen:new {
	id = "i_was_attacked_62",
	leftDialog = "@conversation/corellia_privateer_trainer:s_333f5da9", -- What are you doing talking to me?  Isn't there somewhere you're supposed to be?
	stopConversation = "true",
	options = {
		{"@conversation/corellia_privateer_trainer:s_95d0a1f6", "an_assignment_13"}, -- An assignment?
		{"@conversation/corellia_privateer_trainer:s_bdd269be", "what_ship_14"}, -- What ship?
		{"@conversation/corellia_privateer_trainer:s_60c4f974", "where_do_i_15"}, -- Where do I go?
		{"@conversation/corellia_privateer_trainer:s_5e4ebfca", "and_when_im_16"}, -- And when I'm done?
		{"@conversation/corellia_privateer_trainer:s_c1ff5062", "im_looking_for_17"}, -- I'm looking for a mission. Do you have any?
	}
}
rhea_convo_template:addScreen(i_was_attacked_62);

i_was_attacked_63 = ConvoScreen:new {
	id = "i_was_attacked_63",
	leftDialog = "@conversation/corellia_privateer_trainer:s_cd44e585", -- Listen, something important has come up.  The captain wants to speak to you right away!  Go speak to Captain Rikkh in the next room.
	stopConversation = "true",
	options = {
		{"@conversation/corellia_privateer_trainer:s_95d0a1f6", "an_assignment_13"}, -- An assignment?
		{"@conversation/corellia_privateer_trainer:s_bdd269be", "what_ship_14"}, -- What ship?
		{"@conversation/corellia_privateer_trainer:s_60c4f974", "where_do_i_15"}, -- Where do I go?
		{"@conversation/corellia_privateer_trainer:s_5e4ebfca", "and_when_im_16"}, -- And when I'm done?
		{"@conversation/corellia_privateer_trainer:s_c1ff5062", "im_looking_for_17"}, -- I'm looking for a mission. Do you have any?
	}
}
rhea_convo_template:addScreen(i_was_attacked_63);

i_was_attacked_64 = ConvoScreen:new {
	id = "i_was_attacked_64",
	leftDialog = "@conversation/corellia_privateer_trainer:s_5cdbbd1f", -- What happened to you?  Never mind, never mind.  Get back out there and finish that patrol.
	stopConversation = "false",
	options = {
		{"@conversation/corellia_privateer_trainer:s_95d0a1f6", "an_assignment_13"}, -- An assignment?
		{"@conversation/corellia_privateer_trainer:s_bdd269be", "what_ship_14"}, -- What ship?
		{"@conversation/corellia_privateer_trainer:s_60c4f974", "where_do_i_15"}, -- Where do I go?
		{"@conversation/corellia_privateer_trainer:s_5e4ebfca", "and_when_im_16"}, -- And when I'm done?
		{"@conversation/corellia_privateer_trainer:s_c1ff5062", "im_looking_for_17"}, -- I'm looking for a mission. Do you have any?
		{"@conversation/corellia_privateer_trainer:s_133a724d", "are_you_going_102"}, -- Are you going to train me after this?
	}
}
rhea_convo_template:addScreen(i_was_attacked_64);

i_was_attacked_65 = ConvoScreen:new {
	id = "i_was_attacked_65",
	leftDialog = "@conversation/corellia_privateer_trainer:s_8b8a1542", -- That's bad news, but this is just the reason why CorSec is needed!  Go back out there and take out those pirates.  Defending this system from pirates and killers is all up to us.
	stopConversation = "false",
	options = {
		{"@conversation/corellia_privateer_trainer:s_95d0a1f6", "an_assignment_13"}, -- An assignment?
		{"@conversation/corellia_privateer_trainer:s_bdd269be", "what_ship_14"}, -- What ship?
		{"@conversation/corellia_privateer_trainer:s_60c4f974", "where_do_i_15"}, -- Where do I go?
		{"@conversation/corellia_privateer_trainer:s_5e4ebfca", "and_when_im_16"}, -- And when I'm done?
		{"@conversation/corellia_privateer_trainer:s_c1ff5062", "im_looking_for_17"}, -- I'm looking for a mission. Do you have any?
		{"@conversation/corellia_privateer_trainer:s_133a724d", "are_you_going_102"}, -- Are you going to train me after this?
		{"@conversation/corellia_privateer_trainer:s_168", "are_you_going_149"}, -- Are you going to train me after this?
	}
}
rhea_convo_template:addScreen(i_was_attacked_65);

i_was_attacked_66 = ConvoScreen:new {
	id = "i_was_attacked_66",
	leftDialog = "@conversation/corellia_privateer_trainer:s_844a124b", -- Piracy in this system has increased 17 percent since you signed-up!  This is inexcusable!  Now get out there and complete that patrol!
	stopConversation = "false",
	options = {
		{"@conversation/corellia_privateer_trainer:s_95d0a1f6", "an_assignment_13"}, -- An assignment?
		{"@conversation/corellia_privateer_trainer:s_bdd269be", "what_ship_14"}, -- What ship?
		{"@conversation/corellia_privateer_trainer:s_60c4f974", "where_do_i_15"}, -- Where do I go?
		{"@conversation/corellia_privateer_trainer:s_5e4ebfca", "and_when_im_16"}, -- And when I'm done?
		{"@conversation/corellia_privateer_trainer:s_c1ff5062", "im_looking_for_17"}, -- I'm looking for a mission. Do you have any?
		{"@conversation/corellia_privateer_trainer:s_133a724d", "are_you_going_102"}, -- Are you going to train me after this?
		{"@conversation/corellia_privateer_trainer:s_168", "are_you_going_149"}, -- Are you going to train me after this?
		{"@conversation/corellia_privateer_trainer:s_176", "are_you_going_197"}, -- Are you going to train me after this?
	}
}
rhea_convo_template:addScreen(i_was_attacked_66);

i_was_attacked_67 = ConvoScreen:new {
	id = "i_was_attacked_67",
	leftDialog = "@conversation/corellia_privateer_trainer:s_429077be", -- You're never going to make a dent in the frequency of piracy in the Corellia system until you take out their leader!  Now get back out there and destroy the leader's ship!
	stopConversation = "false",
	options = {
		{"@conversation/corellia_privateer_trainer:s_95d0a1f6", "an_assignment_13"}, -- An assignment?
		{"@conversation/corellia_privateer_trainer:s_bdd269be", "what_ship_14"}, -- What ship?
		{"@conversation/corellia_privateer_trainer:s_60c4f974", "where_do_i_15"}, -- Where do I go?
		{"@conversation/corellia_privateer_trainer:s_5e4ebfca", "and_when_im_16"}, -- And when I'm done?
		{"@conversation/corellia_privateer_trainer:s_c1ff5062", "im_looking_for_17"}, -- I'm looking for a mission. Do you have any?
		{"@conversation/corellia_privateer_trainer:s_133a724d", "are_you_going_102"}, -- Are you going to train me after this?
		{"@conversation/corellia_privateer_trainer:s_168", "are_you_going_149"}, -- Are you going to train me after this?
		{"@conversation/corellia_privateer_trainer:s_176", "are_you_going_197"}, -- Are you going to train me after this?
		{"@conversation/corellia_privateer_trainer:s_183", "are_you_going_244"}, -- Are you going to train me after this?
	}
}
rhea_convo_template:addScreen(i_was_attacked_67);

i_was_attacked_68 = ConvoScreen:new {
	id = "i_was_attacked_68",
	leftDialog = "@conversation/corellia_privateer_trainer:s_f053b088", -- Excellent work!
	stopConversation = "false",
	options = {
		{"@conversation/corellia_privateer_trainer:s_95d0a1f6", "an_assignment_13"}, -- An assignment?
		{"@conversation/corellia_privateer_trainer:s_bdd269be", "what_ship_14"}, -- What ship?
		{"@conversation/corellia_privateer_trainer:s_60c4f974", "where_do_i_15"}, -- Where do I go?
		{"@conversation/corellia_privateer_trainer:s_5e4ebfca", "and_when_im_16"}, -- And when I'm done?
		{"@conversation/corellia_privateer_trainer:s_c1ff5062", "im_looking_for_17"}, -- I'm looking for a mission. Do you have any?
		{"@conversation/corellia_privateer_trainer:s_133a724d", "are_you_going_102"}, -- Are you going to train me after this?
		{"@conversation/corellia_privateer_trainer:s_168", "are_you_going_149"}, -- Are you going to train me after this?
		{"@conversation/corellia_privateer_trainer:s_176", "are_you_going_197"}, -- Are you going to train me after this?
		{"@conversation/corellia_privateer_trainer:s_183", "are_you_going_244"}, -- Are you going to train me after this?
	}
}
rhea_convo_template:addScreen(i_was_attacked_68);

i_was_attacked_69 = ConvoScreen:new {
	id = "i_was_attacked_69",
	leftDialog = "@conversation/corellia_privateer_trainer:s_160", -- Alright, your first assignment is to run a simple patrol.  From time to time pirates move into the area and harass merchants in our system. Just run this simple patrol and make sure there's no criminal activity going on.
	stopConversation = "false",
	options = {
		{"@conversation/corellia_privateer_trainer:s_95d0a1f6", "an_assignment_13"}, -- An assignment?
		{"@conversation/corellia_privateer_trainer:s_bdd269be", "what_ship_14"}, -- What ship?
		{"@conversation/corellia_privateer_trainer:s_60c4f974", "where_do_i_15"}, -- Where do I go?
		{"@conversation/corellia_privateer_trainer:s_5e4ebfca", "and_when_im_16"}, -- And when I'm done?
		{"@conversation/corellia_privateer_trainer:s_c1ff5062", "im_looking_for_17"}, -- I'm looking for a mission. Do you have any?
		{"@conversation/corellia_privateer_trainer:s_133a724d", "are_you_going_102"}, -- Are you going to train me after this?
		{"@conversation/corellia_privateer_trainer:s_168", "are_you_going_149"}, -- Are you going to train me after this?
		{"@conversation/corellia_privateer_trainer:s_176", "are_you_going_197"}, -- Are you going to train me after this?
		{"@conversation/corellia_privateer_trainer:s_183", "are_you_going_244"}, -- Are you going to train me after this?
	}
}
rhea_convo_template:addScreen(i_was_attacked_69);

i_was_attacked_70 = ConvoScreen:new {
	id = "i_was_attacked_70",
	leftDialog = "@conversation/corellia_privateer_trainer:s_926359dd", -- Excellent job taking out those pirates.  No doubt, this won't be the end of them.
	stopConversation = "false",
	options = {
		{"@conversation/corellia_privateer_trainer:s_95d0a1f6", "an_assignment_13"}, -- An assignment?
		{"@conversation/corellia_privateer_trainer:s_bdd269be", "what_ship_14"}, -- What ship?
		{"@conversation/corellia_privateer_trainer:s_60c4f974", "where_do_i_15"}, -- Where do I go?
		{"@conversation/corellia_privateer_trainer:s_5e4ebfca", "and_when_im_16"}, -- And when I'm done?
		{"@conversation/corellia_privateer_trainer:s_c1ff5062", "im_looking_for_17"}, -- I'm looking for a mission. Do you have any?
		{"@conversation/corellia_privateer_trainer:s_133a724d", "are_you_going_102"}, -- Are you going to train me after this?
		{"@conversation/corellia_privateer_trainer:s_168", "are_you_going_149"}, -- Are you going to train me after this?
		{"@conversation/corellia_privateer_trainer:s_176", "are_you_going_197"}, -- Are you going to train me after this?
		{"@conversation/corellia_privateer_trainer:s_183", "are_you_going_244"}, -- Are you going to train me after this?
	}
}
rhea_convo_template:addScreen(i_was_attacked_70);

i_was_attacked_71 = ConvoScreen:new {
	id = "i_was_attacked_71",
	leftDialog = "@conversation/corellia_privateer_trainer:s_4801be96", -- So, you were ambushed as you ran that patrol.  We need to hit them hard to send a message... make an example out of them.  I'm going to send you in to run that scum out of the system. I am uploading some possible waypoints into your nav computer, destroy any Black Sun you find.
	stopConversation = "false",
	options = {
		{"@conversation/corellia_privateer_trainer:s_95d0a1f6", "an_assignment_13"}, -- An assignment?
		{"@conversation/corellia_privateer_trainer:s_bdd269be", "what_ship_14"}, -- What ship?
		{"@conversation/corellia_privateer_trainer:s_60c4f974", "where_do_i_15"}, -- Where do I go?
		{"@conversation/corellia_privateer_trainer:s_5e4ebfca", "and_when_im_16"}, -- And when I'm done?
		{"@conversation/corellia_privateer_trainer:s_c1ff5062", "im_looking_for_17"}, -- I'm looking for a mission. Do you have any?
		{"@conversation/corellia_privateer_trainer:s_133a724d", "are_you_going_102"}, -- Are you going to train me after this?
		{"@conversation/corellia_privateer_trainer:s_168", "are_you_going_149"}, -- Are you going to train me after this?
		{"@conversation/corellia_privateer_trainer:s_176", "are_you_going_197"}, -- Are you going to train me after this?
		{"@conversation/corellia_privateer_trainer:s_183", "are_you_going_244"}, -- Are you going to train me after this?
	}
}
rhea_convo_template:addScreen(i_was_attacked_71);

i_was_attacked_72 = ConvoScreen:new {
	id = "i_was_attacked_72",
	leftDialog = "@conversation/corellia_privateer_trainer:s_f8026f5d", -- Excellent work with that escort.  It's a good thing you were running that patrol, or there's no telling what might have happened to them.  I've got a little something extra for you, too.  It's a mercenary bandolier.  It'll help you keep your things organized.
	stopConversation = "false",
	options = {
		{"@conversation/corellia_privateer_trainer:s_95d0a1f6", "an_assignment_13"}, -- An assignment?
		{"@conversation/corellia_privateer_trainer:s_bdd269be", "what_ship_14"}, -- What ship?
		{"@conversation/corellia_privateer_trainer:s_60c4f974", "where_do_i_15"}, -- Where do I go?
		{"@conversation/corellia_privateer_trainer:s_5e4ebfca", "and_when_im_16"}, -- And when I'm done?
		{"@conversation/corellia_privateer_trainer:s_c1ff5062", "im_looking_for_17"}, -- I'm looking for a mission. Do you have any?
		{"@conversation/corellia_privateer_trainer:s_133a724d", "are_you_going_102"}, -- Are you going to train me after this?
		{"@conversation/corellia_privateer_trainer:s_168", "are_you_going_149"}, -- Are you going to train me after this?
		{"@conversation/corellia_privateer_trainer:s_176", "are_you_going_197"}, -- Are you going to train me after this?
		{"@conversation/corellia_privateer_trainer:s_183", "are_you_going_244"}, -- Are you going to train me after this?
	}
}
rhea_convo_template:addScreen(i_was_attacked_72);

i_was_attacked_73 = ConvoScreen:new {
	id = "i_was_attacked_73",
	leftDialog = "@conversation/corellia_privateer_trainer:s_964fb39a", -- Just to be sure that's the last of them, we need you to run another patrol.  It's a little longer than the last one, but you already know how crafty those criminals can be.
	stopConversation = "false",
	options = {
		{"@conversation/corellia_privateer_trainer:s_95d0a1f6", "an_assignment_13"}, -- An assignment?
		{"@conversation/corellia_privateer_trainer:s_bdd269be", "what_ship_14"}, -- What ship?
		{"@conversation/corellia_privateer_trainer:s_60c4f974", "where_do_i_15"}, -- Where do I go?
		{"@conversation/corellia_privateer_trainer:s_5e4ebfca", "and_when_im_16"}, -- And when I'm done?
		{"@conversation/corellia_privateer_trainer:s_c1ff5062", "im_looking_for_17"}, -- I'm looking for a mission. Do you have any?
		{"@conversation/corellia_privateer_trainer:s_133a724d", "are_you_going_102"}, -- Are you going to train me after this?
		{"@conversation/corellia_privateer_trainer:s_168", "are_you_going_149"}, -- Are you going to train me after this?
		{"@conversation/corellia_privateer_trainer:s_176", "are_you_going_197"}, -- Are you going to train me after this?
		{"@conversation/corellia_privateer_trainer:s_183", "are_you_going_244"}, -- Are you going to train me after this?
	}
}
rhea_convo_template:addScreen(i_was_attacked_73);

i_was_attacked_74 = ConvoScreen:new {
	id = "i_was_attacked_74",
	leftDialog = "@conversation/corellia_privateer_trainer:s_dc993cdb", -- Ha!  That'll show those thugs that CorSec is not to be trifled with.  You're really going to go places in this organization, I can tell already.
	stopConversation = "false",
	options = {
		{"@conversation/corellia_privateer_trainer:s_95d0a1f6", "an_assignment_13"}, -- An assignment?
		{"@conversation/corellia_privateer_trainer:s_bdd269be", "what_ship_14"}, -- What ship?
		{"@conversation/corellia_privateer_trainer:s_60c4f974", "where_do_i_15"}, -- Where do I go?
		{"@conversation/corellia_privateer_trainer:s_5e4ebfca", "and_when_im_16"}, -- And when I'm done?
		{"@conversation/corellia_privateer_trainer:s_c1ff5062", "im_looking_for_17"}, -- I'm looking for a mission. Do you have any?
		{"@conversation/corellia_privateer_trainer:s_133a724d", "are_you_going_102"}, -- Are you going to train me after this?
		{"@conversation/corellia_privateer_trainer:s_168", "are_you_going_149"}, -- Are you going to train me after this?
		{"@conversation/corellia_privateer_trainer:s_176", "are_you_going_197"}, -- Are you going to train me after this?
		{"@conversation/corellia_privateer_trainer:s_183", "are_you_going_244"}, -- Are you going to train me after this?
	}
}
rhea_convo_template:addScreen(i_was_attacked_74);

i_was_attacked_75 = ConvoScreen:new {
	id = "i_was_attacked_75",
	leftDialog = "@conversation/corellia_privateer_trainer:s_8e1ed7f0", -- Enough of this!  Every time we send you out, you find more pirates.  We need to go straight to the source of the problem:  Their leader.  I know you're up to this:  Go find the pirate's leader and take him out.  Let the rest of them go to the outer rim if they want easy prey.
	stopConversation = "false",
	options = {
		{"@conversation/corellia_privateer_trainer:s_95d0a1f6", "an_assignment_13"}, -- An assignment?
		{"@conversation/corellia_privateer_trainer:s_bdd269be", "what_ship_14"}, -- What ship?
		{"@conversation/corellia_privateer_trainer:s_60c4f974", "where_do_i_15"}, -- Where do I go?
		{"@conversation/corellia_privateer_trainer:s_5e4ebfca", "and_when_im_16"}, -- And when I'm done?
		{"@conversation/corellia_privateer_trainer:s_c1ff5062", "im_looking_for_17"}, -- I'm looking for a mission. Do you have any?
		{"@conversation/corellia_privateer_trainer:s_133a724d", "are_you_going_102"}, -- Are you going to train me after this?
		{"@conversation/corellia_privateer_trainer:s_168", "are_you_going_149"}, -- Are you going to train me after this?
		{"@conversation/corellia_privateer_trainer:s_176", "are_you_going_197"}, -- Are you going to train me after this?
		{"@conversation/corellia_privateer_trainer:s_183", "are_you_going_244"}, -- Are you going to train me after this?
	}
}
rhea_convo_template:addScreen(i_was_attacked_75);

i_was_attacked_76 = ConvoScreen:new {
	id = "i_was_attacked_76",
	leftDialog = "@conversation/corellia_privateer_trainer:s_5e6c7400", -- You are definitely ready to move up.  So I'll tell you what. I'll teach you about basic fighters.
	stopConversation = "false",
	options = {
		{"@conversation/corellia_privateer_trainer:s_95d0a1f6", "an_assignment_13"}, -- An assignment?
		{"@conversation/corellia_privateer_trainer:s_bdd269be", "what_ship_14"}, -- What ship?
		{"@conversation/corellia_privateer_trainer:s_60c4f974", "where_do_i_15"}, -- Where do I go?
		{"@conversation/corellia_privateer_trainer:s_5e4ebfca", "and_when_im_16"}, -- And when I'm done?
		{"@conversation/corellia_privateer_trainer:s_c1ff5062", "im_looking_for_17"}, -- I'm looking for a mission. Do you have any?
		{"@conversation/corellia_privateer_trainer:s_133a724d", "are_you_going_102"}, -- Are you going to train me after this?
		{"@conversation/corellia_privateer_trainer:s_168", "are_you_going_149"}, -- Are you going to train me after this?
		{"@conversation/corellia_privateer_trainer:s_176", "are_you_going_197"}, -- Are you going to train me after this?
		{"@conversation/corellia_privateer_trainer:s_183", "are_you_going_244"}, -- Are you going to train me after this?
		{"@conversation/corellia_privateer_trainer:s_c06c7aa9", "that_sounds_great"}, -- That sounds great.
	}
}
rhea_convo_template:addScreen(i_was_attacked_76);

i_was_attacked_77 = ConvoScreen:new {
	id = "i_was_attacked_77",
	leftDialog = "@conversation/corellia_privateer_trainer:s_46ea46ad", -- We're quite satisfied with your level of performance.  I think it's time you learned a bit more, though.
	stopConversation = "false",
	options = {
		{"@conversation/corellia_privateer_trainer:s_95d0a1f6", "an_assignment_13"}, -- An assignment?
		{"@conversation/corellia_privateer_trainer:s_bdd269be", "what_ship_14"}, -- What ship?
		{"@conversation/corellia_privateer_trainer:s_60c4f974", "where_do_i_15"}, -- Where do I go?
		{"@conversation/corellia_privateer_trainer:s_5e4ebfca", "and_when_im_16"}, -- And when I'm done?
		{"@conversation/corellia_privateer_trainer:s_c1ff5062", "im_looking_for_17"}, -- I'm looking for a mission. Do you have any?
		{"@conversation/corellia_privateer_trainer:s_133a724d", "are_you_going_102"}, -- Are you going to train me after this?
		{"@conversation/corellia_privateer_trainer:s_168", "are_you_going_149"}, -- Are you going to train me after this?
		{"@conversation/corellia_privateer_trainer:s_176", "are_you_going_197"}, -- Are you going to train me after this?
		{"@conversation/corellia_privateer_trainer:s_183", "are_you_going_244"}, -- Are you going to train me after this?
		{"@conversation/corellia_privateer_trainer:s_c06c7aa9", "that_sounds_great"}, -- That sounds great.
		{"@conversation/corellia_privateer_trainer:s_229", "i_agree_247"}, -- I agree.
	}
}
rhea_convo_template:addScreen(i_was_attacked_77);

i_was_attacked_78 = ConvoScreen:new {
	id = "i_was_attacked_78",
	leftDialog = "@conversation/corellia_privateer_trainer:s_a48c20c8", -- What's on your mind, officer? Thinking about performing some duty missions?
	stopConversation = "false",
	options = {
		{"@conversation/corellia_privateer_trainer:s_95d0a1f6", "an_assignment_13"}, -- An assignment?
		{"@conversation/corellia_privateer_trainer:s_bdd269be", "what_ship_14"}, -- What ship?
		{"@conversation/corellia_privateer_trainer:s_60c4f974", "where_do_i_15"}, -- Where do I go?
		{"@conversation/corellia_privateer_trainer:s_5e4ebfca", "and_when_im_16"}, -- And when I'm done?
		{"@conversation/corellia_privateer_trainer:s_c1ff5062", "im_looking_for_17"}, -- I'm looking for a mission. Do you have any?
		{"@conversation/corellia_privateer_trainer:s_133a724d", "are_you_going_102"}, -- Are you going to train me after this?
		{"@conversation/corellia_privateer_trainer:s_168", "are_you_going_149"}, -- Are you going to train me after this?
		{"@conversation/corellia_privateer_trainer:s_176", "are_you_going_197"}, -- Are you going to train me after this?
		{"@conversation/corellia_privateer_trainer:s_183", "are_you_going_244"}, -- Are you going to train me after this?
		{"@conversation/corellia_privateer_trainer:s_c06c7aa9", "that_sounds_great"}, -- That sounds great.
		{"@conversation/corellia_privateer_trainer:s_229", "i_agree_247"}, -- I agree.
		{"@conversation/corellia_privateer_trainer:s_6106187c", "what_is_a_260"}, -- What is a duty mission?
		{"@conversation/corellia_privateer_trainer:s_1a7f1a1b", "yes_i_am_261"}, -- Yes I am. What duty missions are available?
		{"@conversation/corellia_privateer_trainer:s_6276c98", "no_but_how_262"}, -- No, but how about some training?
		{"@conversation/corellia_privateer_trainer:s_2883b989", "not_right_now_263"}, -- Not right now, thanks.
	}
}
rhea_convo_template:addScreen(i_was_attacked_78);

nothing_to_it = ConvoScreen:new {
	id = "nothing_to_it",
	leftDialog = "@conversation/corellia_privateer_trainer:s_9e5f75be", -- You've got your assignment and the control device for your ship in your datapad.  Go to the Starport and access the terminal to launch into space.
	stopConversation = "false",
	options = {
		{"@conversation/corellia_privateer_trainer:s_95d0a1f6", "an_assignment_13"}, -- An assignment?
		{"@conversation/corellia_privateer_trainer:s_bdd269be", "what_ship_14"}, -- What ship?
		{"@conversation/corellia_privateer_trainer:s_60c4f974", "where_do_i_15"}, -- Where do I go?
		{"@conversation/corellia_privateer_trainer:s_5e4ebfca", "and_when_im_16"}, -- And when I'm done?
	}
}
rhea_convo_template:addScreen(nothing_to_it);

nothing_to_it_79 = ConvoScreen:new {
	id = "nothing_to_it_79",
	leftDialog = "@conversation/corellia_privateer_trainer:s_698d80f7", -- Sorry, but you don't look like a pilot to me.
	stopConversation = "true",
	options = {
		{"@conversation/corellia_privateer_trainer:s_95d0a1f6", "an_assignment_13"}, -- An assignment?
		{"@conversation/corellia_privateer_trainer:s_bdd269be", "what_ship_14"}, -- What ship?
		{"@conversation/corellia_privateer_trainer:s_60c4f974", "where_do_i_15"}, -- Where do I go?
		{"@conversation/corellia_privateer_trainer:s_5e4ebfca", "and_when_im_16"}, -- And when I'm done?
	}
}
rhea_convo_template:addScreen(nothing_to_it_79);

nothing_to_it_80 = ConvoScreen:new {
	id = "nothing_to_it_80",
	leftDialog = "@conversation/corellia_privateer_trainer:s_c9f74b42", -- Greetings, citizen.  Keep your nose clean and we won't have any trouble.
	stopConversation = "true",
	options = {
		{"@conversation/corellia_privateer_trainer:s_95d0a1f6", "an_assignment_13"}, -- An assignment?
		{"@conversation/corellia_privateer_trainer:s_bdd269be", "what_ship_14"}, -- What ship?
		{"@conversation/corellia_privateer_trainer:s_60c4f974", "where_do_i_15"}, -- Where do I go?
		{"@conversation/corellia_privateer_trainer:s_5e4ebfca", "and_when_im_16"}, -- And when I'm done?
	}
}
rhea_convo_template:addScreen(nothing_to_it_80);

nothing_to_it_81 = ConvoScreen:new {
	id = "nothing_to_it_81",
	leftDialog = "@conversation/corellia_privateer_trainer:s_15502961", -- Nothing to worry about here, sir.  CorSec has the area well secured.
	stopConversation = "true",
	options = {
		{"@conversation/corellia_privateer_trainer:s_95d0a1f6", "an_assignment_13"}, -- An assignment?
		{"@conversation/corellia_privateer_trainer:s_bdd269be", "what_ship_14"}, -- What ship?
		{"@conversation/corellia_privateer_trainer:s_60c4f974", "where_do_i_15"}, -- Where do I go?
		{"@conversation/corellia_privateer_trainer:s_5e4ebfca", "and_when_im_16"}, -- And when I'm done?
	}
}
rhea_convo_template:addScreen(nothing_to_it_81);

nothing_to_it_82 = ConvoScreen:new {
	id = "nothing_to_it_82",
	leftDialog = "@conversation/corellia_privateer_trainer:s_ff684aed", -- Ah, I've heard of you!  You're not a bad pilot from what I understand. What can the CorSec do for you?
	stopConversation = "false",
	options = {
		{"@conversation/corellia_privateer_trainer:s_95d0a1f6", "an_assignment_13"}, -- An assignment?
		{"@conversation/corellia_privateer_trainer:s_bdd269be", "what_ship_14"}, -- What ship?
		{"@conversation/corellia_privateer_trainer:s_60c4f974", "where_do_i_15"}, -- Where do I go?
		{"@conversation/corellia_privateer_trainer:s_5e4ebfca", "and_when_im_16"}, -- And when I'm done?
		{"@conversation/corellia_privateer_trainer:s_c1ff5062", "im_looking_for_17"}, -- I'm looking for a mission. Do you have any?
	}
}
rhea_convo_template:addScreen(nothing_to_it_82);

nothing_to_it_83 = ConvoScreen:new {
	id = "nothing_to_it_83",
	leftDialog = "@conversation/corellia_privateer_trainer:s_f518ba4f", -- Hello!  Come to join the ranks of CorSec?
	stopConversation = "false",
	options = {
		{"@conversation/corellia_privateer_trainer:s_95d0a1f6", "an_assignment_13"}, -- An assignment?
		{"@conversation/corellia_privateer_trainer:s_bdd269be", "what_ship_14"}, -- What ship?
		{"@conversation/corellia_privateer_trainer:s_60c4f974", "where_do_i_15"}, -- Where do I go?
		{"@conversation/corellia_privateer_trainer:s_5e4ebfca", "and_when_im_16"}, -- And when I'm done?
		{"@conversation/corellia_privateer_trainer:s_c1ff5062", "im_looking_for_17"}, -- I'm looking for a mission. Do you have any?
	}
}
rhea_convo_template:addScreen(nothing_to_it_83);

nothing_to_it_84 = ConvoScreen:new {
	id = "nothing_to_it_84",
	leftDialog = "@conversation/corellia_privateer_trainer:s_149", -- You're going to need a ship, if you're going to fly for CorSec.  I'll add the Ship Control Codes to your datapad for you.  It's not a great ship, but it will get you around.
	stopConversation = "true",
	options = {
		{"@conversation/corellia_privateer_trainer:s_95d0a1f6", "an_assignment_13"}, -- An assignment?
		{"@conversation/corellia_privateer_trainer:s_bdd269be", "what_ship_14"}, -- What ship?
		{"@conversation/corellia_privateer_trainer:s_60c4f974", "where_do_i_15"}, -- Where do I go?
		{"@conversation/corellia_privateer_trainer:s_5e4ebfca", "and_when_im_16"}, -- And when I'm done?
		{"@conversation/corellia_privateer_trainer:s_c1ff5062", "im_looking_for_17"}, -- I'm looking for a mission. Do you have any?
	}
}
rhea_convo_template:addScreen(nothing_to_it_84);

nothing_to_it_85 = ConvoScreen:new {
	id = "nothing_to_it_85",
	leftDialog = "@conversation/corellia_privateer_trainer:s_333f5da9", -- What are you doing talking to me?  Isn't there somewhere you're supposed to be?
	stopConversation = "true",
	options = {
		{"@conversation/corellia_privateer_trainer:s_95d0a1f6", "an_assignment_13"}, -- An assignment?
		{"@conversation/corellia_privateer_trainer:s_bdd269be", "what_ship_14"}, -- What ship?
		{"@conversation/corellia_privateer_trainer:s_60c4f974", "where_do_i_15"}, -- Where do I go?
		{"@conversation/corellia_privateer_trainer:s_5e4ebfca", "and_when_im_16"}, -- And when I'm done?
		{"@conversation/corellia_privateer_trainer:s_c1ff5062", "im_looking_for_17"}, -- I'm looking for a mission. Do you have any?
	}
}
rhea_convo_template:addScreen(nothing_to_it_85);

nothing_to_it_86 = ConvoScreen:new {
	id = "nothing_to_it_86",
	leftDialog = "@conversation/corellia_privateer_trainer:s_cd44e585", -- Listen, something important has come up.  The captain wants to speak to you right away!  Go speak to Captain Rikkh in the next room.
	stopConversation = "true",
	options = {
		{"@conversation/corellia_privateer_trainer:s_95d0a1f6", "an_assignment_13"}, -- An assignment?
		{"@conversation/corellia_privateer_trainer:s_bdd269be", "what_ship_14"}, -- What ship?
		{"@conversation/corellia_privateer_trainer:s_60c4f974", "where_do_i_15"}, -- Where do I go?
		{"@conversation/corellia_privateer_trainer:s_5e4ebfca", "and_when_im_16"}, -- And when I'm done?
		{"@conversation/corellia_privateer_trainer:s_c1ff5062", "im_looking_for_17"}, -- I'm looking for a mission. Do you have any?
	}
}
rhea_convo_template:addScreen(nothing_to_it_86);

nothing_to_it_87 = ConvoScreen:new {
	id = "nothing_to_it_87",
	leftDialog = "@conversation/corellia_privateer_trainer:s_5cdbbd1f", -- What happened to you?  Never mind, never mind.  Get back out there and finish that patrol.
	stopConversation = "false",
	options = {
		{"@conversation/corellia_privateer_trainer:s_95d0a1f6", "an_assignment_13"}, -- An assignment?
		{"@conversation/corellia_privateer_trainer:s_bdd269be", "what_ship_14"}, -- What ship?
		{"@conversation/corellia_privateer_trainer:s_60c4f974", "where_do_i_15"}, -- Where do I go?
		{"@conversation/corellia_privateer_trainer:s_5e4ebfca", "and_when_im_16"}, -- And when I'm done?
		{"@conversation/corellia_privateer_trainer:s_c1ff5062", "im_looking_for_17"}, -- I'm looking for a mission. Do you have any?
		{"@conversation/corellia_privateer_trainer:s_133a724d", "are_you_going_102"}, -- Are you going to train me after this?
	}
}
rhea_convo_template:addScreen(nothing_to_it_87);

nothing_to_it_88 = ConvoScreen:new {
	id = "nothing_to_it_88",
	leftDialog = "@conversation/corellia_privateer_trainer:s_8b8a1542", -- That's bad news, but this is just the reason why CorSec is needed!  Go back out there and take out those pirates.  Defending this system from pirates and killers is all up to us.
	stopConversation = "false",
	options = {
		{"@conversation/corellia_privateer_trainer:s_95d0a1f6", "an_assignment_13"}, -- An assignment?
		{"@conversation/corellia_privateer_trainer:s_bdd269be", "what_ship_14"}, -- What ship?
		{"@conversation/corellia_privateer_trainer:s_60c4f974", "where_do_i_15"}, -- Where do I go?
		{"@conversation/corellia_privateer_trainer:s_5e4ebfca", "and_when_im_16"}, -- And when I'm done?
		{"@conversation/corellia_privateer_trainer:s_c1ff5062", "im_looking_for_17"}, -- I'm looking for a mission. Do you have any?
		{"@conversation/corellia_privateer_trainer:s_133a724d", "are_you_going_102"}, -- Are you going to train me after this?
		{"@conversation/corellia_privateer_trainer:s_168", "are_you_going_149"}, -- Are you going to train me after this?
	}
}
rhea_convo_template:addScreen(nothing_to_it_88);

nothing_to_it_89 = ConvoScreen:new {
	id = "nothing_to_it_89",
	leftDialog = "@conversation/corellia_privateer_trainer:s_844a124b", -- Piracy in this system has increased 17 percent since you signed-up!  This is inexcusable!  Now get out there and complete that patrol!
	stopConversation = "false",
	options = {
		{"@conversation/corellia_privateer_trainer:s_95d0a1f6", "an_assignment_13"}, -- An assignment?
		{"@conversation/corellia_privateer_trainer:s_bdd269be", "what_ship_14"}, -- What ship?
		{"@conversation/corellia_privateer_trainer:s_60c4f974", "where_do_i_15"}, -- Where do I go?
		{"@conversation/corellia_privateer_trainer:s_5e4ebfca", "and_when_im_16"}, -- And when I'm done?
		{"@conversation/corellia_privateer_trainer:s_c1ff5062", "im_looking_for_17"}, -- I'm looking for a mission. Do you have any?
		{"@conversation/corellia_privateer_trainer:s_133a724d", "are_you_going_102"}, -- Are you going to train me after this?
		{"@conversation/corellia_privateer_trainer:s_168", "are_you_going_149"}, -- Are you going to train me after this?
		{"@conversation/corellia_privateer_trainer:s_176", "are_you_going_197"}, -- Are you going to train me after this?
	}
}
rhea_convo_template:addScreen(nothing_to_it_89);

nothing_to_it_90 = ConvoScreen:new {
	id = "nothing_to_it_90",
	leftDialog = "@conversation/corellia_privateer_trainer:s_429077be", -- You're never going to make a dent in the frequency of piracy in the Corellia system until you take out their leader!  Now get back out there and destroy the leader's ship!
	stopConversation = "false",
	options = {
		{"@conversation/corellia_privateer_trainer:s_95d0a1f6", "an_assignment_13"}, -- An assignment?
		{"@conversation/corellia_privateer_trainer:s_bdd269be", "what_ship_14"}, -- What ship?
		{"@conversation/corellia_privateer_trainer:s_60c4f974", "where_do_i_15"}, -- Where do I go?
		{"@conversation/corellia_privateer_trainer:s_5e4ebfca", "and_when_im_16"}, -- And when I'm done?
		{"@conversation/corellia_privateer_trainer:s_c1ff5062", "im_looking_for_17"}, -- I'm looking for a mission. Do you have any?
		{"@conversation/corellia_privateer_trainer:s_133a724d", "are_you_going_102"}, -- Are you going to train me after this?
		{"@conversation/corellia_privateer_trainer:s_168", "are_you_going_149"}, -- Are you going to train me after this?
		{"@conversation/corellia_privateer_trainer:s_176", "are_you_going_197"}, -- Are you going to train me after this?
		{"@conversation/corellia_privateer_trainer:s_183", "are_you_going_244"}, -- Are you going to train me after this?
	}
}
rhea_convo_template:addScreen(nothing_to_it_90);

nothing_to_it_91 = ConvoScreen:new {
	id = "nothing_to_it_91",
	leftDialog = "@conversation/corellia_privateer_trainer:s_f053b088", -- Excellent work!
	stopConversation = "false",
	options = {
		{"@conversation/corellia_privateer_trainer:s_95d0a1f6", "an_assignment_13"}, -- An assignment?
		{"@conversation/corellia_privateer_trainer:s_bdd269be", "what_ship_14"}, -- What ship?
		{"@conversation/corellia_privateer_trainer:s_60c4f974", "where_do_i_15"}, -- Where do I go?
		{"@conversation/corellia_privateer_trainer:s_5e4ebfca", "and_when_im_16"}, -- And when I'm done?
		{"@conversation/corellia_privateer_trainer:s_c1ff5062", "im_looking_for_17"}, -- I'm looking for a mission. Do you have any?
		{"@conversation/corellia_privateer_trainer:s_133a724d", "are_you_going_102"}, -- Are you going to train me after this?
		{"@conversation/corellia_privateer_trainer:s_168", "are_you_going_149"}, -- Are you going to train me after this?
		{"@conversation/corellia_privateer_trainer:s_176", "are_you_going_197"}, -- Are you going to train me after this?
		{"@conversation/corellia_privateer_trainer:s_183", "are_you_going_244"}, -- Are you going to train me after this?
	}
}
rhea_convo_template:addScreen(nothing_to_it_91);

nothing_to_it_92 = ConvoScreen:new {
	id = "nothing_to_it_92",
	leftDialog = "@conversation/corellia_privateer_trainer:s_160", -- Alright, your first assignment is to run a simple patrol.  From time to time pirates move into the area and harass merchants in our system. Just run this simple patrol and make sure there's no criminal activity going on.
	stopConversation = "false",
	options = {
		{"@conversation/corellia_privateer_trainer:s_95d0a1f6", "an_assignment_13"}, -- An assignment?
		{"@conversation/corellia_privateer_trainer:s_bdd269be", "what_ship_14"}, -- What ship?
		{"@conversation/corellia_privateer_trainer:s_60c4f974", "where_do_i_15"}, -- Where do I go?
		{"@conversation/corellia_privateer_trainer:s_5e4ebfca", "and_when_im_16"}, -- And when I'm done?
		{"@conversation/corellia_privateer_trainer:s_c1ff5062", "im_looking_for_17"}, -- I'm looking for a mission. Do you have any?
		{"@conversation/corellia_privateer_trainer:s_133a724d", "are_you_going_102"}, -- Are you going to train me after this?
		{"@conversation/corellia_privateer_trainer:s_168", "are_you_going_149"}, -- Are you going to train me after this?
		{"@conversation/corellia_privateer_trainer:s_176", "are_you_going_197"}, -- Are you going to train me after this?
		{"@conversation/corellia_privateer_trainer:s_183", "are_you_going_244"}, -- Are you going to train me after this?
	}
}
rhea_convo_template:addScreen(nothing_to_it_92);

nothing_to_it_93 = ConvoScreen:new {
	id = "nothing_to_it_93",
	leftDialog = "@conversation/corellia_privateer_trainer:s_926359dd", -- Excellent job taking out those pirates.  No doubt, this won't be the end of them.
	stopConversation = "false",
	options = {
		{"@conversation/corellia_privateer_trainer:s_95d0a1f6", "an_assignment_13"}, -- An assignment?
		{"@conversation/corellia_privateer_trainer:s_bdd269be", "what_ship_14"}, -- What ship?
		{"@conversation/corellia_privateer_trainer:s_60c4f974", "where_do_i_15"}, -- Where do I go?
		{"@conversation/corellia_privateer_trainer:s_5e4ebfca", "and_when_im_16"}, -- And when I'm done?
		{"@conversation/corellia_privateer_trainer:s_c1ff5062", "im_looking_for_17"}, -- I'm looking for a mission. Do you have any?
		{"@conversation/corellia_privateer_trainer:s_133a724d", "are_you_going_102"}, -- Are you going to train me after this?
		{"@conversation/corellia_privateer_trainer:s_168", "are_you_going_149"}, -- Are you going to train me after this?
		{"@conversation/corellia_privateer_trainer:s_176", "are_you_going_197"}, -- Are you going to train me after this?
		{"@conversation/corellia_privateer_trainer:s_183", "are_you_going_244"}, -- Are you going to train me after this?
	}
}
rhea_convo_template:addScreen(nothing_to_it_93);

nothing_to_it_94 = ConvoScreen:new {
	id = "nothing_to_it_94",
	leftDialog = "@conversation/corellia_privateer_trainer:s_4801be96", -- So, you were ambushed as you ran that patrol.  We need to hit them hard to send a message... make an example out of them.  I'm going to send you in to run that scum out of the system. I am uploading some possible waypoints into your nav computer, destroy any Black Sun you find.
	stopConversation = "false",
	options = {
		{"@conversation/corellia_privateer_trainer:s_95d0a1f6", "an_assignment_13"}, -- An assignment?
		{"@conversation/corellia_privateer_trainer:s_bdd269be", "what_ship_14"}, -- What ship?
		{"@conversation/corellia_privateer_trainer:s_60c4f974", "where_do_i_15"}, -- Where do I go?
		{"@conversation/corellia_privateer_trainer:s_5e4ebfca", "and_when_im_16"}, -- And when I'm done?
		{"@conversation/corellia_privateer_trainer:s_c1ff5062", "im_looking_for_17"}, -- I'm looking for a mission. Do you have any?
		{"@conversation/corellia_privateer_trainer:s_133a724d", "are_you_going_102"}, -- Are you going to train me after this?
		{"@conversation/corellia_privateer_trainer:s_168", "are_you_going_149"}, -- Are you going to train me after this?
		{"@conversation/corellia_privateer_trainer:s_176", "are_you_going_197"}, -- Are you going to train me after this?
		{"@conversation/corellia_privateer_trainer:s_183", "are_you_going_244"}, -- Are you going to train me after this?
	}
}
rhea_convo_template:addScreen(nothing_to_it_94);

nothing_to_it_95 = ConvoScreen:new {
	id = "nothing_to_it_95",
	leftDialog = "@conversation/corellia_privateer_trainer:s_f8026f5d", -- Excellent work with that escort.  It's a good thing you were running that patrol, or there's no telling what might have happened to them.  I've got a little something extra for you, too.  It's a mercenary bandolier.  It'll help you keep your things organized.
	stopConversation = "false",
	options = {
		{"@conversation/corellia_privateer_trainer:s_95d0a1f6", "an_assignment_13"}, -- An assignment?
		{"@conversation/corellia_privateer_trainer:s_bdd269be", "what_ship_14"}, -- What ship?
		{"@conversation/corellia_privateer_trainer:s_60c4f974", "where_do_i_15"}, -- Where do I go?
		{"@conversation/corellia_privateer_trainer:s_5e4ebfca", "and_when_im_16"}, -- And when I'm done?
		{"@conversation/corellia_privateer_trainer:s_c1ff5062", "im_looking_for_17"}, -- I'm looking for a mission. Do you have any?
		{"@conversation/corellia_privateer_trainer:s_133a724d", "are_you_going_102"}, -- Are you going to train me after this?
		{"@conversation/corellia_privateer_trainer:s_168", "are_you_going_149"}, -- Are you going to train me after this?
		{"@conversation/corellia_privateer_trainer:s_176", "are_you_going_197"}, -- Are you going to train me after this?
		{"@conversation/corellia_privateer_trainer:s_183", "are_you_going_244"}, -- Are you going to train me after this?
	}
}
rhea_convo_template:addScreen(nothing_to_it_95);

nothing_to_it_96 = ConvoScreen:new {
	id = "nothing_to_it_96",
	leftDialog = "@conversation/corellia_privateer_trainer:s_964fb39a", -- Just to be sure that's the last of them, we need you to run another patrol.  It's a little longer than the last one, but you already know how crafty those criminals can be.
	stopConversation = "false",
	options = {
		{"@conversation/corellia_privateer_trainer:s_95d0a1f6", "an_assignment_13"}, -- An assignment?
		{"@conversation/corellia_privateer_trainer:s_bdd269be", "what_ship_14"}, -- What ship?
		{"@conversation/corellia_privateer_trainer:s_60c4f974", "where_do_i_15"}, -- Where do I go?
		{"@conversation/corellia_privateer_trainer:s_5e4ebfca", "and_when_im_16"}, -- And when I'm done?
		{"@conversation/corellia_privateer_trainer:s_c1ff5062", "im_looking_for_17"}, -- I'm looking for a mission. Do you have any?
		{"@conversation/corellia_privateer_trainer:s_133a724d", "are_you_going_102"}, -- Are you going to train me after this?
		{"@conversation/corellia_privateer_trainer:s_168", "are_you_going_149"}, -- Are you going to train me after this?
		{"@conversation/corellia_privateer_trainer:s_176", "are_you_going_197"}, -- Are you going to train me after this?
		{"@conversation/corellia_privateer_trainer:s_183", "are_you_going_244"}, -- Are you going to train me after this?
	}
}
rhea_convo_template:addScreen(nothing_to_it_96);

nothing_to_it_97 = ConvoScreen:new {
	id = "nothing_to_it_97",
	leftDialog = "@conversation/corellia_privateer_trainer:s_dc993cdb", -- Ha!  That'll show those thugs that CorSec is not to be trifled with.  You're really going to go places in this organization, I can tell already.
	stopConversation = "false",
	options = {
		{"@conversation/corellia_privateer_trainer:s_95d0a1f6", "an_assignment_13"}, -- An assignment?
		{"@conversation/corellia_privateer_trainer:s_bdd269be", "what_ship_14"}, -- What ship?
		{"@conversation/corellia_privateer_trainer:s_60c4f974", "where_do_i_15"}, -- Where do I go?
		{"@conversation/corellia_privateer_trainer:s_5e4ebfca", "and_when_im_16"}, -- And when I'm done?
		{"@conversation/corellia_privateer_trainer:s_c1ff5062", "im_looking_for_17"}, -- I'm looking for a mission. Do you have any?
		{"@conversation/corellia_privateer_trainer:s_133a724d", "are_you_going_102"}, -- Are you going to train me after this?
		{"@conversation/corellia_privateer_trainer:s_168", "are_you_going_149"}, -- Are you going to train me after this?
		{"@conversation/corellia_privateer_trainer:s_176", "are_you_going_197"}, -- Are you going to train me after this?
		{"@conversation/corellia_privateer_trainer:s_183", "are_you_going_244"}, -- Are you going to train me after this?
	}
}
rhea_convo_template:addScreen(nothing_to_it_97);

nothing_to_it_98 = ConvoScreen:new {
	id = "nothing_to_it_98",
	leftDialog = "@conversation/corellia_privateer_trainer:s_8e1ed7f0", -- Enough of this!  Every time we send you out, you find more pirates.  We need to go straight to the source of the problem:  Their leader.  I know you're up to this:  Go find the pirate's leader and take him out.  Let the rest of them go to the outer rim if they want easy prey.
	stopConversation = "false",
	options = {
		{"@conversation/corellia_privateer_trainer:s_95d0a1f6", "an_assignment_13"}, -- An assignment?
		{"@conversation/corellia_privateer_trainer:s_bdd269be", "what_ship_14"}, -- What ship?
		{"@conversation/corellia_privateer_trainer:s_60c4f974", "where_do_i_15"}, -- Where do I go?
		{"@conversation/corellia_privateer_trainer:s_5e4ebfca", "and_when_im_16"}, -- And when I'm done?
		{"@conversation/corellia_privateer_trainer:s_c1ff5062", "im_looking_for_17"}, -- I'm looking for a mission. Do you have any?
		{"@conversation/corellia_privateer_trainer:s_133a724d", "are_you_going_102"}, -- Are you going to train me after this?
		{"@conversation/corellia_privateer_trainer:s_168", "are_you_going_149"}, -- Are you going to train me after this?
		{"@conversation/corellia_privateer_trainer:s_176", "are_you_going_197"}, -- Are you going to train me after this?
		{"@conversation/corellia_privateer_trainer:s_183", "are_you_going_244"}, -- Are you going to train me after this?
	}
}
rhea_convo_template:addScreen(nothing_to_it_98);

nothing_to_it_99 = ConvoScreen:new {
	id = "nothing_to_it_99",
	leftDialog = "@conversation/corellia_privateer_trainer:s_5e6c7400", -- You are definitely ready to move up.  So I'll tell you what. I'll teach you about basic fighters.
	stopConversation = "false",
	options = {
		{"@conversation/corellia_privateer_trainer:s_95d0a1f6", "an_assignment_13"}, -- An assignment?
		{"@conversation/corellia_privateer_trainer:s_bdd269be", "what_ship_14"}, -- What ship?
		{"@conversation/corellia_privateer_trainer:s_60c4f974", "where_do_i_15"}, -- Where do I go?
		{"@conversation/corellia_privateer_trainer:s_5e4ebfca", "and_when_im_16"}, -- And when I'm done?
		{"@conversation/corellia_privateer_trainer:s_c1ff5062", "im_looking_for_17"}, -- I'm looking for a mission. Do you have any?
		{"@conversation/corellia_privateer_trainer:s_133a724d", "are_you_going_102"}, -- Are you going to train me after this?
		{"@conversation/corellia_privateer_trainer:s_168", "are_you_going_149"}, -- Are you going to train me after this?
		{"@conversation/corellia_privateer_trainer:s_176", "are_you_going_197"}, -- Are you going to train me after this?
		{"@conversation/corellia_privateer_trainer:s_183", "are_you_going_244"}, -- Are you going to train me after this?
		{"@conversation/corellia_privateer_trainer:s_c06c7aa9", "that_sounds_great"}, -- That sounds great.
	}
}
rhea_convo_template:addScreen(nothing_to_it_99);

nothing_to_it_100 = ConvoScreen:new {
	id = "nothing_to_it_100",
	leftDialog = "@conversation/corellia_privateer_trainer:s_46ea46ad", -- We're quite satisfied with your level of performance.  I think it's time you learned a bit more, though.
	stopConversation = "false",
	options = {
		{"@conversation/corellia_privateer_trainer:s_95d0a1f6", "an_assignment_13"}, -- An assignment?
		{"@conversation/corellia_privateer_trainer:s_bdd269be", "what_ship_14"}, -- What ship?
		{"@conversation/corellia_privateer_trainer:s_60c4f974", "where_do_i_15"}, -- Where do I go?
		{"@conversation/corellia_privateer_trainer:s_5e4ebfca", "and_when_im_16"}, -- And when I'm done?
		{"@conversation/corellia_privateer_trainer:s_c1ff5062", "im_looking_for_17"}, -- I'm looking for a mission. Do you have any?
		{"@conversation/corellia_privateer_trainer:s_133a724d", "are_you_going_102"}, -- Are you going to train me after this?
		{"@conversation/corellia_privateer_trainer:s_168", "are_you_going_149"}, -- Are you going to train me after this?
		{"@conversation/corellia_privateer_trainer:s_176", "are_you_going_197"}, -- Are you going to train me after this?
		{"@conversation/corellia_privateer_trainer:s_183", "are_you_going_244"}, -- Are you going to train me after this?
		{"@conversation/corellia_privateer_trainer:s_c06c7aa9", "that_sounds_great"}, -- That sounds great.
		{"@conversation/corellia_privateer_trainer:s_229", "i_agree_247"}, -- I agree.
	}
}
rhea_convo_template:addScreen(nothing_to_it_100);

nothing_to_it_101 = ConvoScreen:new {
	id = "nothing_to_it_101",
	leftDialog = "@conversation/corellia_privateer_trainer:s_a48c20c8", -- What's on your mind, officer? Thinking about performing some duty missions?
	stopConversation = "false",
	options = {
		{"@conversation/corellia_privateer_trainer:s_95d0a1f6", "an_assignment_13"}, -- An assignment?
		{"@conversation/corellia_privateer_trainer:s_bdd269be", "what_ship_14"}, -- What ship?
		{"@conversation/corellia_privateer_trainer:s_60c4f974", "where_do_i_15"}, -- Where do I go?
		{"@conversation/corellia_privateer_trainer:s_5e4ebfca", "and_when_im_16"}, -- And when I'm done?
		{"@conversation/corellia_privateer_trainer:s_c1ff5062", "im_looking_for_17"}, -- I'm looking for a mission. Do you have any?
		{"@conversation/corellia_privateer_trainer:s_133a724d", "are_you_going_102"}, -- Are you going to train me after this?
		{"@conversation/corellia_privateer_trainer:s_168", "are_you_going_149"}, -- Are you going to train me after this?
		{"@conversation/corellia_privateer_trainer:s_176", "are_you_going_197"}, -- Are you going to train me after this?
		{"@conversation/corellia_privateer_trainer:s_183", "are_you_going_244"}, -- Are you going to train me after this?
		{"@conversation/corellia_privateer_trainer:s_c06c7aa9", "that_sounds_great"}, -- That sounds great.
		{"@conversation/corellia_privateer_trainer:s_229", "i_agree_247"}, -- I agree.
		{"@conversation/corellia_privateer_trainer:s_6106187c", "what_is_a_260"}, -- What is a duty mission?
		{"@conversation/corellia_privateer_trainer:s_1a7f1a1b", "yes_i_am_261"}, -- Yes I am. What duty missions are available?
		{"@conversation/corellia_privateer_trainer:s_6276c98", "no_but_how_262"}, -- No, but how about some training?
		{"@conversation/corellia_privateer_trainer:s_2883b989", "not_right_now_263"}, -- Not right now, thanks.
	}
}
rhea_convo_template:addScreen(nothing_to_it_101);

are_you_going_102 = ConvoScreen:new {
	id = "are_you_going_102",
	leftDialog = "@conversation/corellia_privateer_trainer:s_8e5b619a", -- Oh no, not quite so fast, %NU.  You complete a few more assignments and then we'll see about getting you some training!
	stopConversation = "true",
	options = {}
}
rhea_convo_template:addScreen(are_you_going_102);

whats_next = ConvoScreen:new {
	id = "whats_next",
	leftDialog = "@conversation/corellia_privateer_trainer:s_9e5f75be", -- You've got your assignment and the control device for your ship in your datapad.  Go to the Starport and access the terminal to launch into space.
	stopConversation = "false",
	options = {
		{"@conversation/corellia_privateer_trainer:s_95d0a1f6", "an_assignment_13"}, -- An assignment?
		{"@conversation/corellia_privateer_trainer:s_bdd269be", "what_ship_14"}, -- What ship?
		{"@conversation/corellia_privateer_trainer:s_60c4f974", "where_do_i_15"}, -- Where do I go?
		{"@conversation/corellia_privateer_trainer:s_5e4ebfca", "and_when_im_16"}, -- And when I'm done?
	}
}
rhea_convo_template:addScreen(whats_next);

whats_next_103 = ConvoScreen:new {
	id = "whats_next_103",
	leftDialog = "@conversation/corellia_privateer_trainer:s_698d80f7", -- Sorry, but you don't look like a pilot to me.
	stopConversation = "true",
	options = {
		{"@conversation/corellia_privateer_trainer:s_95d0a1f6", "an_assignment_13"}, -- An assignment?
		{"@conversation/corellia_privateer_trainer:s_bdd269be", "what_ship_14"}, -- What ship?
		{"@conversation/corellia_privateer_trainer:s_60c4f974", "where_do_i_15"}, -- Where do I go?
		{"@conversation/corellia_privateer_trainer:s_5e4ebfca", "and_when_im_16"}, -- And when I'm done?
	}
}
rhea_convo_template:addScreen(whats_next_103);

whats_next_104 = ConvoScreen:new {
	id = "whats_next_104",
	leftDialog = "@conversation/corellia_privateer_trainer:s_c9f74b42", -- Greetings, citizen.  Keep your nose clean and we won't have any trouble.
	stopConversation = "true",
	options = {
		{"@conversation/corellia_privateer_trainer:s_95d0a1f6", "an_assignment_13"}, -- An assignment?
		{"@conversation/corellia_privateer_trainer:s_bdd269be", "what_ship_14"}, -- What ship?
		{"@conversation/corellia_privateer_trainer:s_60c4f974", "where_do_i_15"}, -- Where do I go?
		{"@conversation/corellia_privateer_trainer:s_5e4ebfca", "and_when_im_16"}, -- And when I'm done?
	}
}
rhea_convo_template:addScreen(whats_next_104);

whats_next_105 = ConvoScreen:new {
	id = "whats_next_105",
	leftDialog = "@conversation/corellia_privateer_trainer:s_15502961", -- Nothing to worry about here, sir.  CorSec has the area well secured.
	stopConversation = "true",
	options = {
		{"@conversation/corellia_privateer_trainer:s_95d0a1f6", "an_assignment_13"}, -- An assignment?
		{"@conversation/corellia_privateer_trainer:s_bdd269be", "what_ship_14"}, -- What ship?
		{"@conversation/corellia_privateer_trainer:s_60c4f974", "where_do_i_15"}, -- Where do I go?
		{"@conversation/corellia_privateer_trainer:s_5e4ebfca", "and_when_im_16"}, -- And when I'm done?
	}
}
rhea_convo_template:addScreen(whats_next_105);

whats_next_106 = ConvoScreen:new {
	id = "whats_next_106",
	leftDialog = "@conversation/corellia_privateer_trainer:s_ff684aed", -- Ah, I've heard of you!  You're not a bad pilot from what I understand. What can the CorSec do for you?
	stopConversation = "false",
	options = {
		{"@conversation/corellia_privateer_trainer:s_95d0a1f6", "an_assignment_13"}, -- An assignment?
		{"@conversation/corellia_privateer_trainer:s_bdd269be", "what_ship_14"}, -- What ship?
		{"@conversation/corellia_privateer_trainer:s_60c4f974", "where_do_i_15"}, -- Where do I go?
		{"@conversation/corellia_privateer_trainer:s_5e4ebfca", "and_when_im_16"}, -- And when I'm done?
		{"@conversation/corellia_privateer_trainer:s_c1ff5062", "im_looking_for_17"}, -- I'm looking for a mission. Do you have any?
	}
}
rhea_convo_template:addScreen(whats_next_106);

whats_next_107 = ConvoScreen:new {
	id = "whats_next_107",
	leftDialog = "@conversation/corellia_privateer_trainer:s_f518ba4f", -- Hello!  Come to join the ranks of CorSec?
	stopConversation = "false",
	options = {
		{"@conversation/corellia_privateer_trainer:s_95d0a1f6", "an_assignment_13"}, -- An assignment?
		{"@conversation/corellia_privateer_trainer:s_bdd269be", "what_ship_14"}, -- What ship?
		{"@conversation/corellia_privateer_trainer:s_60c4f974", "where_do_i_15"}, -- Where do I go?
		{"@conversation/corellia_privateer_trainer:s_5e4ebfca", "and_when_im_16"}, -- And when I'm done?
		{"@conversation/corellia_privateer_trainer:s_c1ff5062", "im_looking_for_17"}, -- I'm looking for a mission. Do you have any?
	}
}
rhea_convo_template:addScreen(whats_next_107);

whats_next_108 = ConvoScreen:new {
	id = "whats_next_108",
	leftDialog = "@conversation/corellia_privateer_trainer:s_149", -- You're going to need a ship, if you're going to fly for CorSec.  I'll add the Ship Control Codes to your datapad for you.  It's not a great ship, but it will get you around.
	stopConversation = "true",
	options = {
		{"@conversation/corellia_privateer_trainer:s_95d0a1f6", "an_assignment_13"}, -- An assignment?
		{"@conversation/corellia_privateer_trainer:s_bdd269be", "what_ship_14"}, -- What ship?
		{"@conversation/corellia_privateer_trainer:s_60c4f974", "where_do_i_15"}, -- Where do I go?
		{"@conversation/corellia_privateer_trainer:s_5e4ebfca", "and_when_im_16"}, -- And when I'm done?
		{"@conversation/corellia_privateer_trainer:s_c1ff5062", "im_looking_for_17"}, -- I'm looking for a mission. Do you have any?
	}
}
rhea_convo_template:addScreen(whats_next_108);

whats_next_109 = ConvoScreen:new {
	id = "whats_next_109",
	leftDialog = "@conversation/corellia_privateer_trainer:s_333f5da9", -- What are you doing talking to me?  Isn't there somewhere you're supposed to be?
	stopConversation = "true",
	options = {
		{"@conversation/corellia_privateer_trainer:s_95d0a1f6", "an_assignment_13"}, -- An assignment?
		{"@conversation/corellia_privateer_trainer:s_bdd269be", "what_ship_14"}, -- What ship?
		{"@conversation/corellia_privateer_trainer:s_60c4f974", "where_do_i_15"}, -- Where do I go?
		{"@conversation/corellia_privateer_trainer:s_5e4ebfca", "and_when_im_16"}, -- And when I'm done?
		{"@conversation/corellia_privateer_trainer:s_c1ff5062", "im_looking_for_17"}, -- I'm looking for a mission. Do you have any?
	}
}
rhea_convo_template:addScreen(whats_next_109);

whats_next_110 = ConvoScreen:new {
	id = "whats_next_110",
	leftDialog = "@conversation/corellia_privateer_trainer:s_cd44e585", -- Listen, something important has come up.  The captain wants to speak to you right away!  Go speak to Captain Rikkh in the next room.
	stopConversation = "true",
	options = {
		{"@conversation/corellia_privateer_trainer:s_95d0a1f6", "an_assignment_13"}, -- An assignment?
		{"@conversation/corellia_privateer_trainer:s_bdd269be", "what_ship_14"}, -- What ship?
		{"@conversation/corellia_privateer_trainer:s_60c4f974", "where_do_i_15"}, -- Where do I go?
		{"@conversation/corellia_privateer_trainer:s_5e4ebfca", "and_when_im_16"}, -- And when I'm done?
		{"@conversation/corellia_privateer_trainer:s_c1ff5062", "im_looking_for_17"}, -- I'm looking for a mission. Do you have any?
	}
}
rhea_convo_template:addScreen(whats_next_110);

whats_next_111 = ConvoScreen:new {
	id = "whats_next_111",
	leftDialog = "@conversation/corellia_privateer_trainer:s_5cdbbd1f", -- What happened to you?  Never mind, never mind.  Get back out there and finish that patrol.
	stopConversation = "false",
	options = {
		{"@conversation/corellia_privateer_trainer:s_95d0a1f6", "an_assignment_13"}, -- An assignment?
		{"@conversation/corellia_privateer_trainer:s_bdd269be", "what_ship_14"}, -- What ship?
		{"@conversation/corellia_privateer_trainer:s_60c4f974", "where_do_i_15"}, -- Where do I go?
		{"@conversation/corellia_privateer_trainer:s_5e4ebfca", "and_when_im_16"}, -- And when I'm done?
		{"@conversation/corellia_privateer_trainer:s_c1ff5062", "im_looking_for_17"}, -- I'm looking for a mission. Do you have any?
		{"@conversation/corellia_privateer_trainer:s_133a724d", "are_you_going_102"}, -- Are you going to train me after this?
	}
}
rhea_convo_template:addScreen(whats_next_111);

whats_next_112 = ConvoScreen:new {
	id = "whats_next_112",
	leftDialog = "@conversation/corellia_privateer_trainer:s_8b8a1542", -- That's bad news, but this is just the reason why CorSec is needed!  Go back out there and take out those pirates.  Defending this system from pirates and killers is all up to us.
	stopConversation = "false",
	options = {
		{"@conversation/corellia_privateer_trainer:s_95d0a1f6", "an_assignment_13"}, -- An assignment?
		{"@conversation/corellia_privateer_trainer:s_bdd269be", "what_ship_14"}, -- What ship?
		{"@conversation/corellia_privateer_trainer:s_60c4f974", "where_do_i_15"}, -- Where do I go?
		{"@conversation/corellia_privateer_trainer:s_5e4ebfca", "and_when_im_16"}, -- And when I'm done?
		{"@conversation/corellia_privateer_trainer:s_c1ff5062", "im_looking_for_17"}, -- I'm looking for a mission. Do you have any?
		{"@conversation/corellia_privateer_trainer:s_133a724d", "are_you_going_102"}, -- Are you going to train me after this?
		{"@conversation/corellia_privateer_trainer:s_168", "are_you_going_149"}, -- Are you going to train me after this?
	}
}
rhea_convo_template:addScreen(whats_next_112);

whats_next_113 = ConvoScreen:new {
	id = "whats_next_113",
	leftDialog = "@conversation/corellia_privateer_trainer:s_844a124b", -- Piracy in this system has increased 17 percent since you signed-up!  This is inexcusable!  Now get out there and complete that patrol!
	stopConversation = "false",
	options = {
		{"@conversation/corellia_privateer_trainer:s_95d0a1f6", "an_assignment_13"}, -- An assignment?
		{"@conversation/corellia_privateer_trainer:s_bdd269be", "what_ship_14"}, -- What ship?
		{"@conversation/corellia_privateer_trainer:s_60c4f974", "where_do_i_15"}, -- Where do I go?
		{"@conversation/corellia_privateer_trainer:s_5e4ebfca", "and_when_im_16"}, -- And when I'm done?
		{"@conversation/corellia_privateer_trainer:s_c1ff5062", "im_looking_for_17"}, -- I'm looking for a mission. Do you have any?
		{"@conversation/corellia_privateer_trainer:s_133a724d", "are_you_going_102"}, -- Are you going to train me after this?
		{"@conversation/corellia_privateer_trainer:s_168", "are_you_going_149"}, -- Are you going to train me after this?
		{"@conversation/corellia_privateer_trainer:s_176", "are_you_going_197"}, -- Are you going to train me after this?
	}
}
rhea_convo_template:addScreen(whats_next_113);

whats_next_114 = ConvoScreen:new {
	id = "whats_next_114",
	leftDialog = "@conversation/corellia_privateer_trainer:s_429077be", -- You're never going to make a dent in the frequency of piracy in the Corellia system until you take out their leader!  Now get back out there and destroy the leader's ship!
	stopConversation = "false",
	options = {
		{"@conversation/corellia_privateer_trainer:s_95d0a1f6", "an_assignment_13"}, -- An assignment?
		{"@conversation/corellia_privateer_trainer:s_bdd269be", "what_ship_14"}, -- What ship?
		{"@conversation/corellia_privateer_trainer:s_60c4f974", "where_do_i_15"}, -- Where do I go?
		{"@conversation/corellia_privateer_trainer:s_5e4ebfca", "and_when_im_16"}, -- And when I'm done?
		{"@conversation/corellia_privateer_trainer:s_c1ff5062", "im_looking_for_17"}, -- I'm looking for a mission. Do you have any?
		{"@conversation/corellia_privateer_trainer:s_133a724d", "are_you_going_102"}, -- Are you going to train me after this?
		{"@conversation/corellia_privateer_trainer:s_168", "are_you_going_149"}, -- Are you going to train me after this?
		{"@conversation/corellia_privateer_trainer:s_176", "are_you_going_197"}, -- Are you going to train me after this?
		{"@conversation/corellia_privateer_trainer:s_183", "are_you_going_244"}, -- Are you going to train me after this?
	}
}
rhea_convo_template:addScreen(whats_next_114);

whats_next_115 = ConvoScreen:new {
	id = "whats_next_115",
	leftDialog = "@conversation/corellia_privateer_trainer:s_f053b088", -- Excellent work!
	stopConversation = "false",
	options = {
		{"@conversation/corellia_privateer_trainer:s_95d0a1f6", "an_assignment_13"}, -- An assignment?
		{"@conversation/corellia_privateer_trainer:s_bdd269be", "what_ship_14"}, -- What ship?
		{"@conversation/corellia_privateer_trainer:s_60c4f974", "where_do_i_15"}, -- Where do I go?
		{"@conversation/corellia_privateer_trainer:s_5e4ebfca", "and_when_im_16"}, -- And when I'm done?
		{"@conversation/corellia_privateer_trainer:s_c1ff5062", "im_looking_for_17"}, -- I'm looking for a mission. Do you have any?
		{"@conversation/corellia_privateer_trainer:s_133a724d", "are_you_going_102"}, -- Are you going to train me after this?
		{"@conversation/corellia_privateer_trainer:s_168", "are_you_going_149"}, -- Are you going to train me after this?
		{"@conversation/corellia_privateer_trainer:s_176", "are_you_going_197"}, -- Are you going to train me after this?
		{"@conversation/corellia_privateer_trainer:s_183", "are_you_going_244"}, -- Are you going to train me after this?
	}
}
rhea_convo_template:addScreen(whats_next_115);

whats_next_116 = ConvoScreen:new {
	id = "whats_next_116",
	leftDialog = "@conversation/corellia_privateer_trainer:s_160", -- Alright, your first assignment is to run a simple patrol.  From time to time pirates move into the area and harass merchants in our system. Just run this simple patrol and make sure there's no criminal activity going on.
	stopConversation = "false",
	options = {
		{"@conversation/corellia_privateer_trainer:s_95d0a1f6", "an_assignment_13"}, -- An assignment?
		{"@conversation/corellia_privateer_trainer:s_bdd269be", "what_ship_14"}, -- What ship?
		{"@conversation/corellia_privateer_trainer:s_60c4f974", "where_do_i_15"}, -- Where do I go?
		{"@conversation/corellia_privateer_trainer:s_5e4ebfca", "and_when_im_16"}, -- And when I'm done?
		{"@conversation/corellia_privateer_trainer:s_c1ff5062", "im_looking_for_17"}, -- I'm looking for a mission. Do you have any?
		{"@conversation/corellia_privateer_trainer:s_133a724d", "are_you_going_102"}, -- Are you going to train me after this?
		{"@conversation/corellia_privateer_trainer:s_168", "are_you_going_149"}, -- Are you going to train me after this?
		{"@conversation/corellia_privateer_trainer:s_176", "are_you_going_197"}, -- Are you going to train me after this?
		{"@conversation/corellia_privateer_trainer:s_183", "are_you_going_244"}, -- Are you going to train me after this?
	}
}
rhea_convo_template:addScreen(whats_next_116);

whats_next_117 = ConvoScreen:new {
	id = "whats_next_117",
	leftDialog = "@conversation/corellia_privateer_trainer:s_926359dd", -- Excellent job taking out those pirates.  No doubt, this won't be the end of them.
	stopConversation = "false",
	options = {
		{"@conversation/corellia_privateer_trainer:s_95d0a1f6", "an_assignment_13"}, -- An assignment?
		{"@conversation/corellia_privateer_trainer:s_bdd269be", "what_ship_14"}, -- What ship?
		{"@conversation/corellia_privateer_trainer:s_60c4f974", "where_do_i_15"}, -- Where do I go?
		{"@conversation/corellia_privateer_trainer:s_5e4ebfca", "and_when_im_16"}, -- And when I'm done?
		{"@conversation/corellia_privateer_trainer:s_c1ff5062", "im_looking_for_17"}, -- I'm looking for a mission. Do you have any?
		{"@conversation/corellia_privateer_trainer:s_133a724d", "are_you_going_102"}, -- Are you going to train me after this?
		{"@conversation/corellia_privateer_trainer:s_168", "are_you_going_149"}, -- Are you going to train me after this?
		{"@conversation/corellia_privateer_trainer:s_176", "are_you_going_197"}, -- Are you going to train me after this?
		{"@conversation/corellia_privateer_trainer:s_183", "are_you_going_244"}, -- Are you going to train me after this?
	}
}
rhea_convo_template:addScreen(whats_next_117);

whats_next_118 = ConvoScreen:new {
	id = "whats_next_118",
	leftDialog = "@conversation/corellia_privateer_trainer:s_4801be96", -- So, you were ambushed as you ran that patrol.  We need to hit them hard to send a message... make an example out of them.  I'm going to send you in to run that scum out of the system. I am uploading some possible waypoints into your nav computer, destroy any Black Sun you find.
	stopConversation = "false",
	options = {
		{"@conversation/corellia_privateer_trainer:s_95d0a1f6", "an_assignment_13"}, -- An assignment?
		{"@conversation/corellia_privateer_trainer:s_bdd269be", "what_ship_14"}, -- What ship?
		{"@conversation/corellia_privateer_trainer:s_60c4f974", "where_do_i_15"}, -- Where do I go?
		{"@conversation/corellia_privateer_trainer:s_5e4ebfca", "and_when_im_16"}, -- And when I'm done?
		{"@conversation/corellia_privateer_trainer:s_c1ff5062", "im_looking_for_17"}, -- I'm looking for a mission. Do you have any?
		{"@conversation/corellia_privateer_trainer:s_133a724d", "are_you_going_102"}, -- Are you going to train me after this?
		{"@conversation/corellia_privateer_trainer:s_168", "are_you_going_149"}, -- Are you going to train me after this?
		{"@conversation/corellia_privateer_trainer:s_176", "are_you_going_197"}, -- Are you going to train me after this?
		{"@conversation/corellia_privateer_trainer:s_183", "are_you_going_244"}, -- Are you going to train me after this?
	}
}
rhea_convo_template:addScreen(whats_next_118);

whats_next_119 = ConvoScreen:new {
	id = "whats_next_119",
	leftDialog = "@conversation/corellia_privateer_trainer:s_f8026f5d", -- Excellent work with that escort.  It's a good thing you were running that patrol, or there's no telling what might have happened to them.  I've got a little something extra for you, too.  It's a mercenary bandolier.  It'll help you keep your things organized.
	stopConversation = "false",
	options = {
		{"@conversation/corellia_privateer_trainer:s_95d0a1f6", "an_assignment_13"}, -- An assignment?
		{"@conversation/corellia_privateer_trainer:s_bdd269be", "what_ship_14"}, -- What ship?
		{"@conversation/corellia_privateer_trainer:s_60c4f974", "where_do_i_15"}, -- Where do I go?
		{"@conversation/corellia_privateer_trainer:s_5e4ebfca", "and_when_im_16"}, -- And when I'm done?
		{"@conversation/corellia_privateer_trainer:s_c1ff5062", "im_looking_for_17"}, -- I'm looking for a mission. Do you have any?
		{"@conversation/corellia_privateer_trainer:s_133a724d", "are_you_going_102"}, -- Are you going to train me after this?
		{"@conversation/corellia_privateer_trainer:s_168", "are_you_going_149"}, -- Are you going to train me after this?
		{"@conversation/corellia_privateer_trainer:s_176", "are_you_going_197"}, -- Are you going to train me after this?
		{"@conversation/corellia_privateer_trainer:s_183", "are_you_going_244"}, -- Are you going to train me after this?
	}
}
rhea_convo_template:addScreen(whats_next_119);

whats_next_120 = ConvoScreen:new {
	id = "whats_next_120",
	leftDialog = "@conversation/corellia_privateer_trainer:s_964fb39a", -- Just to be sure that's the last of them, we need you to run another patrol.  It's a little longer than the last one, but you already know how crafty those criminals can be.
	stopConversation = "false",
	options = {
		{"@conversation/corellia_privateer_trainer:s_95d0a1f6", "an_assignment_13"}, -- An assignment?
		{"@conversation/corellia_privateer_trainer:s_bdd269be", "what_ship_14"}, -- What ship?
		{"@conversation/corellia_privateer_trainer:s_60c4f974", "where_do_i_15"}, -- Where do I go?
		{"@conversation/corellia_privateer_trainer:s_5e4ebfca", "and_when_im_16"}, -- And when I'm done?
		{"@conversation/corellia_privateer_trainer:s_c1ff5062", "im_looking_for_17"}, -- I'm looking for a mission. Do you have any?
		{"@conversation/corellia_privateer_trainer:s_133a724d", "are_you_going_102"}, -- Are you going to train me after this?
		{"@conversation/corellia_privateer_trainer:s_168", "are_you_going_149"}, -- Are you going to train me after this?
		{"@conversation/corellia_privateer_trainer:s_176", "are_you_going_197"}, -- Are you going to train me after this?
		{"@conversation/corellia_privateer_trainer:s_183", "are_you_going_244"}, -- Are you going to train me after this?
	}
}
rhea_convo_template:addScreen(whats_next_120);

whats_next_121 = ConvoScreen:new {
	id = "whats_next_121",
	leftDialog = "@conversation/corellia_privateer_trainer:s_dc993cdb", -- Ha!  That'll show those thugs that CorSec is not to be trifled with.  You're really going to go places in this organization, I can tell already.
	stopConversation = "false",
	options = {
		{"@conversation/corellia_privateer_trainer:s_95d0a1f6", "an_assignment_13"}, -- An assignment?
		{"@conversation/corellia_privateer_trainer:s_bdd269be", "what_ship_14"}, -- What ship?
		{"@conversation/corellia_privateer_trainer:s_60c4f974", "where_do_i_15"}, -- Where do I go?
		{"@conversation/corellia_privateer_trainer:s_5e4ebfca", "and_when_im_16"}, -- And when I'm done?
		{"@conversation/corellia_privateer_trainer:s_c1ff5062", "im_looking_for_17"}, -- I'm looking for a mission. Do you have any?
		{"@conversation/corellia_privateer_trainer:s_133a724d", "are_you_going_102"}, -- Are you going to train me after this?
		{"@conversation/corellia_privateer_trainer:s_168", "are_you_going_149"}, -- Are you going to train me after this?
		{"@conversation/corellia_privateer_trainer:s_176", "are_you_going_197"}, -- Are you going to train me after this?
		{"@conversation/corellia_privateer_trainer:s_183", "are_you_going_244"}, -- Are you going to train me after this?
	}
}
rhea_convo_template:addScreen(whats_next_121);

whats_next_122 = ConvoScreen:new {
	id = "whats_next_122",
	leftDialog = "@conversation/corellia_privateer_trainer:s_8e1ed7f0", -- Enough of this!  Every time we send you out, you find more pirates.  We need to go straight to the source of the problem:  Their leader.  I know you're up to this:  Go find the pirate's leader and take him out.  Let the rest of them go to the outer rim if they want easy prey.
	stopConversation = "false",
	options = {
		{"@conversation/corellia_privateer_trainer:s_95d0a1f6", "an_assignment_13"}, -- An assignment?
		{"@conversation/corellia_privateer_trainer:s_bdd269be", "what_ship_14"}, -- What ship?
		{"@conversation/corellia_privateer_trainer:s_60c4f974", "where_do_i_15"}, -- Where do I go?
		{"@conversation/corellia_privateer_trainer:s_5e4ebfca", "and_when_im_16"}, -- And when I'm done?
		{"@conversation/corellia_privateer_trainer:s_c1ff5062", "im_looking_for_17"}, -- I'm looking for a mission. Do you have any?
		{"@conversation/corellia_privateer_trainer:s_133a724d", "are_you_going_102"}, -- Are you going to train me after this?
		{"@conversation/corellia_privateer_trainer:s_168", "are_you_going_149"}, -- Are you going to train me after this?
		{"@conversation/corellia_privateer_trainer:s_176", "are_you_going_197"}, -- Are you going to train me after this?
		{"@conversation/corellia_privateer_trainer:s_183", "are_you_going_244"}, -- Are you going to train me after this?
	}
}
rhea_convo_template:addScreen(whats_next_122);

whats_next_123 = ConvoScreen:new {
	id = "whats_next_123",
	leftDialog = "@conversation/corellia_privateer_trainer:s_5e6c7400", -- You are definitely ready to move up.  So I'll tell you what. I'll teach you about basic fighters.
	stopConversation = "false",
	options = {
		{"@conversation/corellia_privateer_trainer:s_95d0a1f6", "an_assignment_13"}, -- An assignment?
		{"@conversation/corellia_privateer_trainer:s_bdd269be", "what_ship_14"}, -- What ship?
		{"@conversation/corellia_privateer_trainer:s_60c4f974", "where_do_i_15"}, -- Where do I go?
		{"@conversation/corellia_privateer_trainer:s_5e4ebfca", "and_when_im_16"}, -- And when I'm done?
		{"@conversation/corellia_privateer_trainer:s_c1ff5062", "im_looking_for_17"}, -- I'm looking for a mission. Do you have any?
		{"@conversation/corellia_privateer_trainer:s_133a724d", "are_you_going_102"}, -- Are you going to train me after this?
		{"@conversation/corellia_privateer_trainer:s_168", "are_you_going_149"}, -- Are you going to train me after this?
		{"@conversation/corellia_privateer_trainer:s_176", "are_you_going_197"}, -- Are you going to train me after this?
		{"@conversation/corellia_privateer_trainer:s_183", "are_you_going_244"}, -- Are you going to train me after this?
		{"@conversation/corellia_privateer_trainer:s_c06c7aa9", "that_sounds_great"}, -- That sounds great.
	}
}
rhea_convo_template:addScreen(whats_next_123);

whats_next_124 = ConvoScreen:new {
	id = "whats_next_124",
	leftDialog = "@conversation/corellia_privateer_trainer:s_46ea46ad", -- We're quite satisfied with your level of performance.  I think it's time you learned a bit more, though.
	stopConversation = "false",
	options = {
		{"@conversation/corellia_privateer_trainer:s_95d0a1f6", "an_assignment_13"}, -- An assignment?
		{"@conversation/corellia_privateer_trainer:s_bdd269be", "what_ship_14"}, -- What ship?
		{"@conversation/corellia_privateer_trainer:s_60c4f974", "where_do_i_15"}, -- Where do I go?
		{"@conversation/corellia_privateer_trainer:s_5e4ebfca", "and_when_im_16"}, -- And when I'm done?
		{"@conversation/corellia_privateer_trainer:s_c1ff5062", "im_looking_for_17"}, -- I'm looking for a mission. Do you have any?
		{"@conversation/corellia_privateer_trainer:s_133a724d", "are_you_going_102"}, -- Are you going to train me after this?
		{"@conversation/corellia_privateer_trainer:s_168", "are_you_going_149"}, -- Are you going to train me after this?
		{"@conversation/corellia_privateer_trainer:s_176", "are_you_going_197"}, -- Are you going to train me after this?
		{"@conversation/corellia_privateer_trainer:s_183", "are_you_going_244"}, -- Are you going to train me after this?
		{"@conversation/corellia_privateer_trainer:s_c06c7aa9", "that_sounds_great"}, -- That sounds great.
		{"@conversation/corellia_privateer_trainer:s_229", "i_agree_247"}, -- I agree.
	}
}
rhea_convo_template:addScreen(whats_next_124);

whats_next_125 = ConvoScreen:new {
	id = "whats_next_125",
	leftDialog = "@conversation/corellia_privateer_trainer:s_a48c20c8", -- What's on your mind, officer? Thinking about performing some duty missions?
	stopConversation = "false",
	options = {
		{"@conversation/corellia_privateer_trainer:s_95d0a1f6", "an_assignment_13"}, -- An assignment?
		{"@conversation/corellia_privateer_trainer:s_bdd269be", "what_ship_14"}, -- What ship?
		{"@conversation/corellia_privateer_trainer:s_60c4f974", "where_do_i_15"}, -- Where do I go?
		{"@conversation/corellia_privateer_trainer:s_5e4ebfca", "and_when_im_16"}, -- And when I'm done?
		{"@conversation/corellia_privateer_trainer:s_c1ff5062", "im_looking_for_17"}, -- I'm looking for a mission. Do you have any?
		{"@conversation/corellia_privateer_trainer:s_133a724d", "are_you_going_102"}, -- Are you going to train me after this?
		{"@conversation/corellia_privateer_trainer:s_168", "are_you_going_149"}, -- Are you going to train me after this?
		{"@conversation/corellia_privateer_trainer:s_176", "are_you_going_197"}, -- Are you going to train me after this?
		{"@conversation/corellia_privateer_trainer:s_183", "are_you_going_244"}, -- Are you going to train me after this?
		{"@conversation/corellia_privateer_trainer:s_c06c7aa9", "that_sounds_great"}, -- That sounds great.
		{"@conversation/corellia_privateer_trainer:s_229", "i_agree_247"}, -- I agree.
		{"@conversation/corellia_privateer_trainer:s_6106187c", "what_is_a_260"}, -- What is a duty mission?
		{"@conversation/corellia_privateer_trainer:s_1a7f1a1b", "yes_i_am_261"}, -- Yes I am. What duty missions are available?
		{"@conversation/corellia_privateer_trainer:s_6276c98", "no_but_how_262"}, -- No, but how about some training?
		{"@conversation/corellia_privateer_trainer:s_2883b989", "not_right_now_263"}, -- Not right now, thanks.
	}
}
rhea_convo_template:addScreen(whats_next_125);

it_was_a = ConvoScreen:new {
	id = "it_was_a",
	leftDialog = "@conversation/corellia_privateer_trainer:s_9e5f75be", -- You've got your assignment and the control device for your ship in your datapad.  Go to the Starport and access the terminal to launch into space.
	stopConversation = "false",
	options = {
		{"@conversation/corellia_privateer_trainer:s_95d0a1f6", "an_assignment_13"}, -- An assignment?
		{"@conversation/corellia_privateer_trainer:s_bdd269be", "what_ship_14"}, -- What ship?
		{"@conversation/corellia_privateer_trainer:s_60c4f974", "where_do_i_15"}, -- Where do I go?
		{"@conversation/corellia_privateer_trainer:s_5e4ebfca", "and_when_im_16"}, -- And when I'm done?
	}
}
rhea_convo_template:addScreen(it_was_a);

it_was_a_126 = ConvoScreen:new {
	id = "it_was_a_126",
	leftDialog = "@conversation/corellia_privateer_trainer:s_698d80f7", -- Sorry, but you don't look like a pilot to me.
	stopConversation = "true",
	options = {
		{"@conversation/corellia_privateer_trainer:s_95d0a1f6", "an_assignment_13"}, -- An assignment?
		{"@conversation/corellia_privateer_trainer:s_bdd269be", "what_ship_14"}, -- What ship?
		{"@conversation/corellia_privateer_trainer:s_60c4f974", "where_do_i_15"}, -- Where do I go?
		{"@conversation/corellia_privateer_trainer:s_5e4ebfca", "and_when_im_16"}, -- And when I'm done?
	}
}
rhea_convo_template:addScreen(it_was_a_126);

it_was_a_127 = ConvoScreen:new {
	id = "it_was_a_127",
	leftDialog = "@conversation/corellia_privateer_trainer:s_c9f74b42", -- Greetings, citizen.  Keep your nose clean and we won't have any trouble.
	stopConversation = "true",
	options = {
		{"@conversation/corellia_privateer_trainer:s_95d0a1f6", "an_assignment_13"}, -- An assignment?
		{"@conversation/corellia_privateer_trainer:s_bdd269be", "what_ship_14"}, -- What ship?
		{"@conversation/corellia_privateer_trainer:s_60c4f974", "where_do_i_15"}, -- Where do I go?
		{"@conversation/corellia_privateer_trainer:s_5e4ebfca", "and_when_im_16"}, -- And when I'm done?
	}
}
rhea_convo_template:addScreen(it_was_a_127);

it_was_a_128 = ConvoScreen:new {
	id = "it_was_a_128",
	leftDialog = "@conversation/corellia_privateer_trainer:s_15502961", -- Nothing to worry about here, sir.  CorSec has the area well secured.
	stopConversation = "true",
	options = {
		{"@conversation/corellia_privateer_trainer:s_95d0a1f6", "an_assignment_13"}, -- An assignment?
		{"@conversation/corellia_privateer_trainer:s_bdd269be", "what_ship_14"}, -- What ship?
		{"@conversation/corellia_privateer_trainer:s_60c4f974", "where_do_i_15"}, -- Where do I go?
		{"@conversation/corellia_privateer_trainer:s_5e4ebfca", "and_when_im_16"}, -- And when I'm done?
	}
}
rhea_convo_template:addScreen(it_was_a_128);

it_was_a_129 = ConvoScreen:new {
	id = "it_was_a_129",
	leftDialog = "@conversation/corellia_privateer_trainer:s_ff684aed", -- Ah, I've heard of you!  You're not a bad pilot from what I understand. What can the CorSec do for you?
	stopConversation = "false",
	options = {
		{"@conversation/corellia_privateer_trainer:s_95d0a1f6", "an_assignment_13"}, -- An assignment?
		{"@conversation/corellia_privateer_trainer:s_bdd269be", "what_ship_14"}, -- What ship?
		{"@conversation/corellia_privateer_trainer:s_60c4f974", "where_do_i_15"}, -- Where do I go?
		{"@conversation/corellia_privateer_trainer:s_5e4ebfca", "and_when_im_16"}, -- And when I'm done?
		{"@conversation/corellia_privateer_trainer:s_c1ff5062", "im_looking_for_17"}, -- I'm looking for a mission. Do you have any?
	}
}
rhea_convo_template:addScreen(it_was_a_129);

it_was_a_130 = ConvoScreen:new {
	id = "it_was_a_130",
	leftDialog = "@conversation/corellia_privateer_trainer:s_f518ba4f", -- Hello!  Come to join the ranks of CorSec?
	stopConversation = "false",
	options = {
		{"@conversation/corellia_privateer_trainer:s_95d0a1f6", "an_assignment_13"}, -- An assignment?
		{"@conversation/corellia_privateer_trainer:s_bdd269be", "what_ship_14"}, -- What ship?
		{"@conversation/corellia_privateer_trainer:s_60c4f974", "where_do_i_15"}, -- Where do I go?
		{"@conversation/corellia_privateer_trainer:s_5e4ebfca", "and_when_im_16"}, -- And when I'm done?
		{"@conversation/corellia_privateer_trainer:s_c1ff5062", "im_looking_for_17"}, -- I'm looking for a mission. Do you have any?
	}
}
rhea_convo_template:addScreen(it_was_a_130);

it_was_a_131 = ConvoScreen:new {
	id = "it_was_a_131",
	leftDialog = "@conversation/corellia_privateer_trainer:s_149", -- You're going to need a ship, if you're going to fly for CorSec.  I'll add the Ship Control Codes to your datapad for you.  It's not a great ship, but it will get you around.
	stopConversation = "true",
	options = {
		{"@conversation/corellia_privateer_trainer:s_95d0a1f6", "an_assignment_13"}, -- An assignment?
		{"@conversation/corellia_privateer_trainer:s_bdd269be", "what_ship_14"}, -- What ship?
		{"@conversation/corellia_privateer_trainer:s_60c4f974", "where_do_i_15"}, -- Where do I go?
		{"@conversation/corellia_privateer_trainer:s_5e4ebfca", "and_when_im_16"}, -- And when I'm done?
		{"@conversation/corellia_privateer_trainer:s_c1ff5062", "im_looking_for_17"}, -- I'm looking for a mission. Do you have any?
	}
}
rhea_convo_template:addScreen(it_was_a_131);

it_was_a_132 = ConvoScreen:new {
	id = "it_was_a_132",
	leftDialog = "@conversation/corellia_privateer_trainer:s_333f5da9", -- What are you doing talking to me?  Isn't there somewhere you're supposed to be?
	stopConversation = "true",
	options = {
		{"@conversation/corellia_privateer_trainer:s_95d0a1f6", "an_assignment_13"}, -- An assignment?
		{"@conversation/corellia_privateer_trainer:s_bdd269be", "what_ship_14"}, -- What ship?
		{"@conversation/corellia_privateer_trainer:s_60c4f974", "where_do_i_15"}, -- Where do I go?
		{"@conversation/corellia_privateer_trainer:s_5e4ebfca", "and_when_im_16"}, -- And when I'm done?
		{"@conversation/corellia_privateer_trainer:s_c1ff5062", "im_looking_for_17"}, -- I'm looking for a mission. Do you have any?
	}
}
rhea_convo_template:addScreen(it_was_a_132);

it_was_a_133 = ConvoScreen:new {
	id = "it_was_a_133",
	leftDialog = "@conversation/corellia_privateer_trainer:s_cd44e585", -- Listen, something important has come up.  The captain wants to speak to you right away!  Go speak to Captain Rikkh in the next room.
	stopConversation = "true",
	options = {
		{"@conversation/corellia_privateer_trainer:s_95d0a1f6", "an_assignment_13"}, -- An assignment?
		{"@conversation/corellia_privateer_trainer:s_bdd269be", "what_ship_14"}, -- What ship?
		{"@conversation/corellia_privateer_trainer:s_60c4f974", "where_do_i_15"}, -- Where do I go?
		{"@conversation/corellia_privateer_trainer:s_5e4ebfca", "and_when_im_16"}, -- And when I'm done?
		{"@conversation/corellia_privateer_trainer:s_c1ff5062", "im_looking_for_17"}, -- I'm looking for a mission. Do you have any?
	}
}
rhea_convo_template:addScreen(it_was_a_133);

it_was_a_134 = ConvoScreen:new {
	id = "it_was_a_134",
	leftDialog = "@conversation/corellia_privateer_trainer:s_5cdbbd1f", -- What happened to you?  Never mind, never mind.  Get back out there and finish that patrol.
	stopConversation = "false",
	options = {
		{"@conversation/corellia_privateer_trainer:s_95d0a1f6", "an_assignment_13"}, -- An assignment?
		{"@conversation/corellia_privateer_trainer:s_bdd269be", "what_ship_14"}, -- What ship?
		{"@conversation/corellia_privateer_trainer:s_60c4f974", "where_do_i_15"}, -- Where do I go?
		{"@conversation/corellia_privateer_trainer:s_5e4ebfca", "and_when_im_16"}, -- And when I'm done?
		{"@conversation/corellia_privateer_trainer:s_c1ff5062", "im_looking_for_17"}, -- I'm looking for a mission. Do you have any?
		{"@conversation/corellia_privateer_trainer:s_133a724d", "are_you_going_102"}, -- Are you going to train me after this?
	}
}
rhea_convo_template:addScreen(it_was_a_134);

it_was_a_135 = ConvoScreen:new {
	id = "it_was_a_135",
	leftDialog = "@conversation/corellia_privateer_trainer:s_8b8a1542", -- That's bad news, but this is just the reason why CorSec is needed!  Go back out there and take out those pirates.  Defending this system from pirates and killers is all up to us.
	stopConversation = "false",
	options = {
		{"@conversation/corellia_privateer_trainer:s_95d0a1f6", "an_assignment_13"}, -- An assignment?
		{"@conversation/corellia_privateer_trainer:s_bdd269be", "what_ship_14"}, -- What ship?
		{"@conversation/corellia_privateer_trainer:s_60c4f974", "where_do_i_15"}, -- Where do I go?
		{"@conversation/corellia_privateer_trainer:s_5e4ebfca", "and_when_im_16"}, -- And when I'm done?
		{"@conversation/corellia_privateer_trainer:s_c1ff5062", "im_looking_for_17"}, -- I'm looking for a mission. Do you have any?
		{"@conversation/corellia_privateer_trainer:s_133a724d", "are_you_going_102"}, -- Are you going to train me after this?
		{"@conversation/corellia_privateer_trainer:s_168", "are_you_going_149"}, -- Are you going to train me after this?
	}
}
rhea_convo_template:addScreen(it_was_a_135);

it_was_a_136 = ConvoScreen:new {
	id = "it_was_a_136",
	leftDialog = "@conversation/corellia_privateer_trainer:s_844a124b", -- Piracy in this system has increased 17 percent since you signed-up!  This is inexcusable!  Now get out there and complete that patrol!
	stopConversation = "false",
	options = {
		{"@conversation/corellia_privateer_trainer:s_95d0a1f6", "an_assignment_13"}, -- An assignment?
		{"@conversation/corellia_privateer_trainer:s_bdd269be", "what_ship_14"}, -- What ship?
		{"@conversation/corellia_privateer_trainer:s_60c4f974", "where_do_i_15"}, -- Where do I go?
		{"@conversation/corellia_privateer_trainer:s_5e4ebfca", "and_when_im_16"}, -- And when I'm done?
		{"@conversation/corellia_privateer_trainer:s_c1ff5062", "im_looking_for_17"}, -- I'm looking for a mission. Do you have any?
		{"@conversation/corellia_privateer_trainer:s_133a724d", "are_you_going_102"}, -- Are you going to train me after this?
		{"@conversation/corellia_privateer_trainer:s_168", "are_you_going_149"}, -- Are you going to train me after this?
		{"@conversation/corellia_privateer_trainer:s_176", "are_you_going_197"}, -- Are you going to train me after this?
	}
}
rhea_convo_template:addScreen(it_was_a_136);

it_was_a_137 = ConvoScreen:new {
	id = "it_was_a_137",
	leftDialog = "@conversation/corellia_privateer_trainer:s_429077be", -- You're never going to make a dent in the frequency of piracy in the Corellia system until you take out their leader!  Now get back out there and destroy the leader's ship!
	stopConversation = "false",
	options = {
		{"@conversation/corellia_privateer_trainer:s_95d0a1f6", "an_assignment_13"}, -- An assignment?
		{"@conversation/corellia_privateer_trainer:s_bdd269be", "what_ship_14"}, -- What ship?
		{"@conversation/corellia_privateer_trainer:s_60c4f974", "where_do_i_15"}, -- Where do I go?
		{"@conversation/corellia_privateer_trainer:s_5e4ebfca", "and_when_im_16"}, -- And when I'm done?
		{"@conversation/corellia_privateer_trainer:s_c1ff5062", "im_looking_for_17"}, -- I'm looking for a mission. Do you have any?
		{"@conversation/corellia_privateer_trainer:s_133a724d", "are_you_going_102"}, -- Are you going to train me after this?
		{"@conversation/corellia_privateer_trainer:s_168", "are_you_going_149"}, -- Are you going to train me after this?
		{"@conversation/corellia_privateer_trainer:s_176", "are_you_going_197"}, -- Are you going to train me after this?
		{"@conversation/corellia_privateer_trainer:s_183", "are_you_going_244"}, -- Are you going to train me after this?
	}
}
rhea_convo_template:addScreen(it_was_a_137);

it_was_a_138 = ConvoScreen:new {
	id = "it_was_a_138",
	leftDialog = "@conversation/corellia_privateer_trainer:s_f053b088", -- Excellent work!
	stopConversation = "false",
	options = {
		{"@conversation/corellia_privateer_trainer:s_95d0a1f6", "an_assignment_13"}, -- An assignment?
		{"@conversation/corellia_privateer_trainer:s_bdd269be", "what_ship_14"}, -- What ship?
		{"@conversation/corellia_privateer_trainer:s_60c4f974", "where_do_i_15"}, -- Where do I go?
		{"@conversation/corellia_privateer_trainer:s_5e4ebfca", "and_when_im_16"}, -- And when I'm done?
		{"@conversation/corellia_privateer_trainer:s_c1ff5062", "im_looking_for_17"}, -- I'm looking for a mission. Do you have any?
		{"@conversation/corellia_privateer_trainer:s_133a724d", "are_you_going_102"}, -- Are you going to train me after this?
		{"@conversation/corellia_privateer_trainer:s_168", "are_you_going_149"}, -- Are you going to train me after this?
		{"@conversation/corellia_privateer_trainer:s_176", "are_you_going_197"}, -- Are you going to train me after this?
		{"@conversation/corellia_privateer_trainer:s_183", "are_you_going_244"}, -- Are you going to train me after this?
	}
}
rhea_convo_template:addScreen(it_was_a_138);

it_was_a_139 = ConvoScreen:new {
	id = "it_was_a_139",
	leftDialog = "@conversation/corellia_privateer_trainer:s_160", -- Alright, your first assignment is to run a simple patrol.  From time to time pirates move into the area and harass merchants in our system. Just run this simple patrol and make sure there's no criminal activity going on.
	stopConversation = "false",
	options = {
		{"@conversation/corellia_privateer_trainer:s_95d0a1f6", "an_assignment_13"}, -- An assignment?
		{"@conversation/corellia_privateer_trainer:s_bdd269be", "what_ship_14"}, -- What ship?
		{"@conversation/corellia_privateer_trainer:s_60c4f974", "where_do_i_15"}, -- Where do I go?
		{"@conversation/corellia_privateer_trainer:s_5e4ebfca", "and_when_im_16"}, -- And when I'm done?
		{"@conversation/corellia_privateer_trainer:s_c1ff5062", "im_looking_for_17"}, -- I'm looking for a mission. Do you have any?
		{"@conversation/corellia_privateer_trainer:s_133a724d", "are_you_going_102"}, -- Are you going to train me after this?
		{"@conversation/corellia_privateer_trainer:s_168", "are_you_going_149"}, -- Are you going to train me after this?
		{"@conversation/corellia_privateer_trainer:s_176", "are_you_going_197"}, -- Are you going to train me after this?
		{"@conversation/corellia_privateer_trainer:s_183", "are_you_going_244"}, -- Are you going to train me after this?
	}
}
rhea_convo_template:addScreen(it_was_a_139);

it_was_a_140 = ConvoScreen:new {
	id = "it_was_a_140",
	leftDialog = "@conversation/corellia_privateer_trainer:s_926359dd", -- Excellent job taking out those pirates.  No doubt, this won't be the end of them.
	stopConversation = "false",
	options = {
		{"@conversation/corellia_privateer_trainer:s_95d0a1f6", "an_assignment_13"}, -- An assignment?
		{"@conversation/corellia_privateer_trainer:s_bdd269be", "what_ship_14"}, -- What ship?
		{"@conversation/corellia_privateer_trainer:s_60c4f974", "where_do_i_15"}, -- Where do I go?
		{"@conversation/corellia_privateer_trainer:s_5e4ebfca", "and_when_im_16"}, -- And when I'm done?
		{"@conversation/corellia_privateer_trainer:s_c1ff5062", "im_looking_for_17"}, -- I'm looking for a mission. Do you have any?
		{"@conversation/corellia_privateer_trainer:s_133a724d", "are_you_going_102"}, -- Are you going to train me after this?
		{"@conversation/corellia_privateer_trainer:s_168", "are_you_going_149"}, -- Are you going to train me after this?
		{"@conversation/corellia_privateer_trainer:s_176", "are_you_going_197"}, -- Are you going to train me after this?
		{"@conversation/corellia_privateer_trainer:s_183", "are_you_going_244"}, -- Are you going to train me after this?
	}
}
rhea_convo_template:addScreen(it_was_a_140);

it_was_a_141 = ConvoScreen:new {
	id = "it_was_a_141",
	leftDialog = "@conversation/corellia_privateer_trainer:s_4801be96", -- So, you were ambushed as you ran that patrol.  We need to hit them hard to send a message... make an example out of them.  I'm going to send you in to run that scum out of the system. I am uploading some possible waypoints into your nav computer, destroy any Black Sun you find.
	stopConversation = "false",
	options = {
		{"@conversation/corellia_privateer_trainer:s_95d0a1f6", "an_assignment_13"}, -- An assignment?
		{"@conversation/corellia_privateer_trainer:s_bdd269be", "what_ship_14"}, -- What ship?
		{"@conversation/corellia_privateer_trainer:s_60c4f974", "where_do_i_15"}, -- Where do I go?
		{"@conversation/corellia_privateer_trainer:s_5e4ebfca", "and_when_im_16"}, -- And when I'm done?
		{"@conversation/corellia_privateer_trainer:s_c1ff5062", "im_looking_for_17"}, -- I'm looking for a mission. Do you have any?
		{"@conversation/corellia_privateer_trainer:s_133a724d", "are_you_going_102"}, -- Are you going to train me after this?
		{"@conversation/corellia_privateer_trainer:s_168", "are_you_going_149"}, -- Are you going to train me after this?
		{"@conversation/corellia_privateer_trainer:s_176", "are_you_going_197"}, -- Are you going to train me after this?
		{"@conversation/corellia_privateer_trainer:s_183", "are_you_going_244"}, -- Are you going to train me after this?
	}
}
rhea_convo_template:addScreen(it_was_a_141);

it_was_a_142 = ConvoScreen:new {
	id = "it_was_a_142",
	leftDialog = "@conversation/corellia_privateer_trainer:s_f8026f5d", -- Excellent work with that escort.  It's a good thing you were running that patrol, or there's no telling what might have happened to them.  I've got a little something extra for you, too.  It's a mercenary bandolier.  It'll help you keep your things organized.
	stopConversation = "false",
	options = {
		{"@conversation/corellia_privateer_trainer:s_95d0a1f6", "an_assignment_13"}, -- An assignment?
		{"@conversation/corellia_privateer_trainer:s_bdd269be", "what_ship_14"}, -- What ship?
		{"@conversation/corellia_privateer_trainer:s_60c4f974", "where_do_i_15"}, -- Where do I go?
		{"@conversation/corellia_privateer_trainer:s_5e4ebfca", "and_when_im_16"}, -- And when I'm done?
		{"@conversation/corellia_privateer_trainer:s_c1ff5062", "im_looking_for_17"}, -- I'm looking for a mission. Do you have any?
		{"@conversation/corellia_privateer_trainer:s_133a724d", "are_you_going_102"}, -- Are you going to train me after this?
		{"@conversation/corellia_privateer_trainer:s_168", "are_you_going_149"}, -- Are you going to train me after this?
		{"@conversation/corellia_privateer_trainer:s_176", "are_you_going_197"}, -- Are you going to train me after this?
		{"@conversation/corellia_privateer_trainer:s_183", "are_you_going_244"}, -- Are you going to train me after this?
	}
}
rhea_convo_template:addScreen(it_was_a_142);

it_was_a_143 = ConvoScreen:new {
	id = "it_was_a_143",
	leftDialog = "@conversation/corellia_privateer_trainer:s_964fb39a", -- Just to be sure that's the last of them, we need you to run another patrol.  It's a little longer than the last one, but you already know how crafty those criminals can be.
	stopConversation = "false",
	options = {
		{"@conversation/corellia_privateer_trainer:s_95d0a1f6", "an_assignment_13"}, -- An assignment?
		{"@conversation/corellia_privateer_trainer:s_bdd269be", "what_ship_14"}, -- What ship?
		{"@conversation/corellia_privateer_trainer:s_60c4f974", "where_do_i_15"}, -- Where do I go?
		{"@conversation/corellia_privateer_trainer:s_5e4ebfca", "and_when_im_16"}, -- And when I'm done?
		{"@conversation/corellia_privateer_trainer:s_c1ff5062", "im_looking_for_17"}, -- I'm looking for a mission. Do you have any?
		{"@conversation/corellia_privateer_trainer:s_133a724d", "are_you_going_102"}, -- Are you going to train me after this?
		{"@conversation/corellia_privateer_trainer:s_168", "are_you_going_149"}, -- Are you going to train me after this?
		{"@conversation/corellia_privateer_trainer:s_176", "are_you_going_197"}, -- Are you going to train me after this?
		{"@conversation/corellia_privateer_trainer:s_183", "are_you_going_244"}, -- Are you going to train me after this?
	}
}
rhea_convo_template:addScreen(it_was_a_143);

it_was_a_144 = ConvoScreen:new {
	id = "it_was_a_144",
	leftDialog = "@conversation/corellia_privateer_trainer:s_dc993cdb", -- Ha!  That'll show those thugs that CorSec is not to be trifled with.  You're really going to go places in this organization, I can tell already.
	stopConversation = "false",
	options = {
		{"@conversation/corellia_privateer_trainer:s_95d0a1f6", "an_assignment_13"}, -- An assignment?
		{"@conversation/corellia_privateer_trainer:s_bdd269be", "what_ship_14"}, -- What ship?
		{"@conversation/corellia_privateer_trainer:s_60c4f974", "where_do_i_15"}, -- Where do I go?
		{"@conversation/corellia_privateer_trainer:s_5e4ebfca", "and_when_im_16"}, -- And when I'm done?
		{"@conversation/corellia_privateer_trainer:s_c1ff5062", "im_looking_for_17"}, -- I'm looking for a mission. Do you have any?
		{"@conversation/corellia_privateer_trainer:s_133a724d", "are_you_going_102"}, -- Are you going to train me after this?
		{"@conversation/corellia_privateer_trainer:s_168", "are_you_going_149"}, -- Are you going to train me after this?
		{"@conversation/corellia_privateer_trainer:s_176", "are_you_going_197"}, -- Are you going to train me after this?
		{"@conversation/corellia_privateer_trainer:s_183", "are_you_going_244"}, -- Are you going to train me after this?
	}
}
rhea_convo_template:addScreen(it_was_a_144);

it_was_a_145 = ConvoScreen:new {
	id = "it_was_a_145",
	leftDialog = "@conversation/corellia_privateer_trainer:s_8e1ed7f0", -- Enough of this!  Every time we send you out, you find more pirates.  We need to go straight to the source of the problem:  Their leader.  I know you're up to this:  Go find the pirate's leader and take him out.  Let the rest of them go to the outer rim if they want easy prey.
	stopConversation = "false",
	options = {
		{"@conversation/corellia_privateer_trainer:s_95d0a1f6", "an_assignment_13"}, -- An assignment?
		{"@conversation/corellia_privateer_trainer:s_bdd269be", "what_ship_14"}, -- What ship?
		{"@conversation/corellia_privateer_trainer:s_60c4f974", "where_do_i_15"}, -- Where do I go?
		{"@conversation/corellia_privateer_trainer:s_5e4ebfca", "and_when_im_16"}, -- And when I'm done?
		{"@conversation/corellia_privateer_trainer:s_c1ff5062", "im_looking_for_17"}, -- I'm looking for a mission. Do you have any?
		{"@conversation/corellia_privateer_trainer:s_133a724d", "are_you_going_102"}, -- Are you going to train me after this?
		{"@conversation/corellia_privateer_trainer:s_168", "are_you_going_149"}, -- Are you going to train me after this?
		{"@conversation/corellia_privateer_trainer:s_176", "are_you_going_197"}, -- Are you going to train me after this?
		{"@conversation/corellia_privateer_trainer:s_183", "are_you_going_244"}, -- Are you going to train me after this?
	}
}
rhea_convo_template:addScreen(it_was_a_145);

it_was_a_146 = ConvoScreen:new {
	id = "it_was_a_146",
	leftDialog = "@conversation/corellia_privateer_trainer:s_5e6c7400", -- You are definitely ready to move up.  So I'll tell you what. I'll teach you about basic fighters.
	stopConversation = "false",
	options = {
		{"@conversation/corellia_privateer_trainer:s_95d0a1f6", "an_assignment_13"}, -- An assignment?
		{"@conversation/corellia_privateer_trainer:s_bdd269be", "what_ship_14"}, -- What ship?
		{"@conversation/corellia_privateer_trainer:s_60c4f974", "where_do_i_15"}, -- Where do I go?
		{"@conversation/corellia_privateer_trainer:s_5e4ebfca", "and_when_im_16"}, -- And when I'm done?
		{"@conversation/corellia_privateer_trainer:s_c1ff5062", "im_looking_for_17"}, -- I'm looking for a mission. Do you have any?
		{"@conversation/corellia_privateer_trainer:s_133a724d", "are_you_going_102"}, -- Are you going to train me after this?
		{"@conversation/corellia_privateer_trainer:s_168", "are_you_going_149"}, -- Are you going to train me after this?
		{"@conversation/corellia_privateer_trainer:s_176", "are_you_going_197"}, -- Are you going to train me after this?
		{"@conversation/corellia_privateer_trainer:s_183", "are_you_going_244"}, -- Are you going to train me after this?
		{"@conversation/corellia_privateer_trainer:s_c06c7aa9", "that_sounds_great"}, -- That sounds great.
	}
}
rhea_convo_template:addScreen(it_was_a_146);

it_was_a_147 = ConvoScreen:new {
	id = "it_was_a_147",
	leftDialog = "@conversation/corellia_privateer_trainer:s_46ea46ad", -- We're quite satisfied with your level of performance.  I think it's time you learned a bit more, though.
	stopConversation = "false",
	options = {
		{"@conversation/corellia_privateer_trainer:s_95d0a1f6", "an_assignment_13"}, -- An assignment?
		{"@conversation/corellia_privateer_trainer:s_bdd269be", "what_ship_14"}, -- What ship?
		{"@conversation/corellia_privateer_trainer:s_60c4f974", "where_do_i_15"}, -- Where do I go?
		{"@conversation/corellia_privateer_trainer:s_5e4ebfca", "and_when_im_16"}, -- And when I'm done?
		{"@conversation/corellia_privateer_trainer:s_c1ff5062", "im_looking_for_17"}, -- I'm looking for a mission. Do you have any?
		{"@conversation/corellia_privateer_trainer:s_133a724d", "are_you_going_102"}, -- Are you going to train me after this?
		{"@conversation/corellia_privateer_trainer:s_168", "are_you_going_149"}, -- Are you going to train me after this?
		{"@conversation/corellia_privateer_trainer:s_176", "are_you_going_197"}, -- Are you going to train me after this?
		{"@conversation/corellia_privateer_trainer:s_183", "are_you_going_244"}, -- Are you going to train me after this?
		{"@conversation/corellia_privateer_trainer:s_c06c7aa9", "that_sounds_great"}, -- That sounds great.
		{"@conversation/corellia_privateer_trainer:s_229", "i_agree_247"}, -- I agree.
	}
}
rhea_convo_template:addScreen(it_was_a_147);

it_was_a_148 = ConvoScreen:new {
	id = "it_was_a_148",
	leftDialog = "@conversation/corellia_privateer_trainer:s_a48c20c8", -- What's on your mind, officer? Thinking about performing some duty missions?
	stopConversation = "false",
	options = {
		{"@conversation/corellia_privateer_trainer:s_95d0a1f6", "an_assignment_13"}, -- An assignment?
		{"@conversation/corellia_privateer_trainer:s_bdd269be", "what_ship_14"}, -- What ship?
		{"@conversation/corellia_privateer_trainer:s_60c4f974", "where_do_i_15"}, -- Where do I go?
		{"@conversation/corellia_privateer_trainer:s_5e4ebfca", "and_when_im_16"}, -- And when I'm done?
		{"@conversation/corellia_privateer_trainer:s_c1ff5062", "im_looking_for_17"}, -- I'm looking for a mission. Do you have any?
		{"@conversation/corellia_privateer_trainer:s_133a724d", "are_you_going_102"}, -- Are you going to train me after this?
		{"@conversation/corellia_privateer_trainer:s_168", "are_you_going_149"}, -- Are you going to train me after this?
		{"@conversation/corellia_privateer_trainer:s_176", "are_you_going_197"}, -- Are you going to train me after this?
		{"@conversation/corellia_privateer_trainer:s_183", "are_you_going_244"}, -- Are you going to train me after this?
		{"@conversation/corellia_privateer_trainer:s_c06c7aa9", "that_sounds_great"}, -- That sounds great.
		{"@conversation/corellia_privateer_trainer:s_229", "i_agree_247"}, -- I agree.
		{"@conversation/corellia_privateer_trainer:s_6106187c", "what_is_a_260"}, -- What is a duty mission?
		{"@conversation/corellia_privateer_trainer:s_1a7f1a1b", "yes_i_am_261"}, -- Yes I am. What duty missions are available?
		{"@conversation/corellia_privateer_trainer:s_6276c98", "no_but_how_262"}, -- No, but how about some training?
		{"@conversation/corellia_privateer_trainer:s_2883b989", "not_right_now_263"}, -- Not right now, thanks.
	}
}
rhea_convo_template:addScreen(it_was_a_148);

are_you_going_149 = ConvoScreen:new {
	id = "are_you_going_149",
	leftDialog = "@conversation/corellia_privateer_trainer:s_c91ba06e", -- Not just yet, %NU.  I have just a few more things for you to do before you get any training from me.
	stopConversation = "true",
	options = {}
}
rhea_convo_template:addScreen(are_you_going_149);

whats_next_150 = ConvoScreen:new {
	id = "whats_next_150",
	leftDialog = "@conversation/corellia_privateer_trainer:s_9e5f75be", -- You've got your assignment and the control device for your ship in your datapad.  Go to the Starport and access the terminal to launch into space.
	stopConversation = "false",
	options = {
		{"@conversation/corellia_privateer_trainer:s_95d0a1f6", "an_assignment_13"}, -- An assignment?
		{"@conversation/corellia_privateer_trainer:s_bdd269be", "what_ship_14"}, -- What ship?
		{"@conversation/corellia_privateer_trainer:s_60c4f974", "where_do_i_15"}, -- Where do I go?
		{"@conversation/corellia_privateer_trainer:s_5e4ebfca", "and_when_im_16"}, -- And when I'm done?
	}
}
rhea_convo_template:addScreen(whats_next_150);

whats_next_151 = ConvoScreen:new {
	id = "whats_next_151",
	leftDialog = "@conversation/corellia_privateer_trainer:s_698d80f7", -- Sorry, but you don't look like a pilot to me.
	stopConversation = "true",
	options = {
		{"@conversation/corellia_privateer_trainer:s_95d0a1f6", "an_assignment_13"}, -- An assignment?
		{"@conversation/corellia_privateer_trainer:s_bdd269be", "what_ship_14"}, -- What ship?
		{"@conversation/corellia_privateer_trainer:s_60c4f974", "where_do_i_15"}, -- Where do I go?
		{"@conversation/corellia_privateer_trainer:s_5e4ebfca", "and_when_im_16"}, -- And when I'm done?
	}
}
rhea_convo_template:addScreen(whats_next_151);

whats_next_152 = ConvoScreen:new {
	id = "whats_next_152",
	leftDialog = "@conversation/corellia_privateer_trainer:s_c9f74b42", -- Greetings, citizen.  Keep your nose clean and we won't have any trouble.
	stopConversation = "true",
	options = {
		{"@conversation/corellia_privateer_trainer:s_95d0a1f6", "an_assignment_13"}, -- An assignment?
		{"@conversation/corellia_privateer_trainer:s_bdd269be", "what_ship_14"}, -- What ship?
		{"@conversation/corellia_privateer_trainer:s_60c4f974", "where_do_i_15"}, -- Where do I go?
		{"@conversation/corellia_privateer_trainer:s_5e4ebfca", "and_when_im_16"}, -- And when I'm done?
	}
}
rhea_convo_template:addScreen(whats_next_152);

whats_next_153 = ConvoScreen:new {
	id = "whats_next_153",
	leftDialog = "@conversation/corellia_privateer_trainer:s_15502961", -- Nothing to worry about here, sir.  CorSec has the area well secured.
	stopConversation = "true",
	options = {
		{"@conversation/corellia_privateer_trainer:s_95d0a1f6", "an_assignment_13"}, -- An assignment?
		{"@conversation/corellia_privateer_trainer:s_bdd269be", "what_ship_14"}, -- What ship?
		{"@conversation/corellia_privateer_trainer:s_60c4f974", "where_do_i_15"}, -- Where do I go?
		{"@conversation/corellia_privateer_trainer:s_5e4ebfca", "and_when_im_16"}, -- And when I'm done?
	}
}
rhea_convo_template:addScreen(whats_next_153);

whats_next_154 = ConvoScreen:new {
	id = "whats_next_154",
	leftDialog = "@conversation/corellia_privateer_trainer:s_ff684aed", -- Ah, I've heard of you!  You're not a bad pilot from what I understand. What can the CorSec do for you?
	stopConversation = "false",
	options = {
		{"@conversation/corellia_privateer_trainer:s_95d0a1f6", "an_assignment_13"}, -- An assignment?
		{"@conversation/corellia_privateer_trainer:s_bdd269be", "what_ship_14"}, -- What ship?
		{"@conversation/corellia_privateer_trainer:s_60c4f974", "where_do_i_15"}, -- Where do I go?
		{"@conversation/corellia_privateer_trainer:s_5e4ebfca", "and_when_im_16"}, -- And when I'm done?
		{"@conversation/corellia_privateer_trainer:s_c1ff5062", "im_looking_for_17"}, -- I'm looking for a mission. Do you have any?
	}
}
rhea_convo_template:addScreen(whats_next_154);

whats_next_155 = ConvoScreen:new {
	id = "whats_next_155",
	leftDialog = "@conversation/corellia_privateer_trainer:s_f518ba4f", -- Hello!  Come to join the ranks of CorSec?
	stopConversation = "false",
	options = {
		{"@conversation/corellia_privateer_trainer:s_95d0a1f6", "an_assignment_13"}, -- An assignment?
		{"@conversation/corellia_privateer_trainer:s_bdd269be", "what_ship_14"}, -- What ship?
		{"@conversation/corellia_privateer_trainer:s_60c4f974", "where_do_i_15"}, -- Where do I go?
		{"@conversation/corellia_privateer_trainer:s_5e4ebfca", "and_when_im_16"}, -- And when I'm done?
		{"@conversation/corellia_privateer_trainer:s_c1ff5062", "im_looking_for_17"}, -- I'm looking for a mission. Do you have any?
	}
}
rhea_convo_template:addScreen(whats_next_155);

whats_next_156 = ConvoScreen:new {
	id = "whats_next_156",
	leftDialog = "@conversation/corellia_privateer_trainer:s_149", -- You're going to need a ship, if you're going to fly for CorSec.  I'll add the Ship Control Codes to your datapad for you.  It's not a great ship, but it will get you around.
	stopConversation = "true",
	options = {
		{"@conversation/corellia_privateer_trainer:s_95d0a1f6", "an_assignment_13"}, -- An assignment?
		{"@conversation/corellia_privateer_trainer:s_bdd269be", "what_ship_14"}, -- What ship?
		{"@conversation/corellia_privateer_trainer:s_60c4f974", "where_do_i_15"}, -- Where do I go?
		{"@conversation/corellia_privateer_trainer:s_5e4ebfca", "and_when_im_16"}, -- And when I'm done?
		{"@conversation/corellia_privateer_trainer:s_c1ff5062", "im_looking_for_17"}, -- I'm looking for a mission. Do you have any?
	}
}
rhea_convo_template:addScreen(whats_next_156);

whats_next_157 = ConvoScreen:new {
	id = "whats_next_157",
	leftDialog = "@conversation/corellia_privateer_trainer:s_333f5da9", -- What are you doing talking to me?  Isn't there somewhere you're supposed to be?
	stopConversation = "true",
	options = {
		{"@conversation/corellia_privateer_trainer:s_95d0a1f6", "an_assignment_13"}, -- An assignment?
		{"@conversation/corellia_privateer_trainer:s_bdd269be", "what_ship_14"}, -- What ship?
		{"@conversation/corellia_privateer_trainer:s_60c4f974", "where_do_i_15"}, -- Where do I go?
		{"@conversation/corellia_privateer_trainer:s_5e4ebfca", "and_when_im_16"}, -- And when I'm done?
		{"@conversation/corellia_privateer_trainer:s_c1ff5062", "im_looking_for_17"}, -- I'm looking for a mission. Do you have any?
	}
}
rhea_convo_template:addScreen(whats_next_157);

whats_next_158 = ConvoScreen:new {
	id = "whats_next_158",
	leftDialog = "@conversation/corellia_privateer_trainer:s_cd44e585", -- Listen, something important has come up.  The captain wants to speak to you right away!  Go speak to Captain Rikkh in the next room.
	stopConversation = "true",
	options = {
		{"@conversation/corellia_privateer_trainer:s_95d0a1f6", "an_assignment_13"}, -- An assignment?
		{"@conversation/corellia_privateer_trainer:s_bdd269be", "what_ship_14"}, -- What ship?
		{"@conversation/corellia_privateer_trainer:s_60c4f974", "where_do_i_15"}, -- Where do I go?
		{"@conversation/corellia_privateer_trainer:s_5e4ebfca", "and_when_im_16"}, -- And when I'm done?
		{"@conversation/corellia_privateer_trainer:s_c1ff5062", "im_looking_for_17"}, -- I'm looking for a mission. Do you have any?
	}
}
rhea_convo_template:addScreen(whats_next_158);

whats_next_159 = ConvoScreen:new {
	id = "whats_next_159",
	leftDialog = "@conversation/corellia_privateer_trainer:s_5cdbbd1f", -- What happened to you?  Never mind, never mind.  Get back out there and finish that patrol.
	stopConversation = "false",
	options = {
		{"@conversation/corellia_privateer_trainer:s_95d0a1f6", "an_assignment_13"}, -- An assignment?
		{"@conversation/corellia_privateer_trainer:s_bdd269be", "what_ship_14"}, -- What ship?
		{"@conversation/corellia_privateer_trainer:s_60c4f974", "where_do_i_15"}, -- Where do I go?
		{"@conversation/corellia_privateer_trainer:s_5e4ebfca", "and_when_im_16"}, -- And when I'm done?
		{"@conversation/corellia_privateer_trainer:s_c1ff5062", "im_looking_for_17"}, -- I'm looking for a mission. Do you have any?
		{"@conversation/corellia_privateer_trainer:s_133a724d", "are_you_going_102"}, -- Are you going to train me after this?
	}
}
rhea_convo_template:addScreen(whats_next_159);

whats_next_160 = ConvoScreen:new {
	id = "whats_next_160",
	leftDialog = "@conversation/corellia_privateer_trainer:s_8b8a1542", -- That's bad news, but this is just the reason why CorSec is needed!  Go back out there and take out those pirates.  Defending this system from pirates and killers is all up to us.
	stopConversation = "false",
	options = {
		{"@conversation/corellia_privateer_trainer:s_95d0a1f6", "an_assignment_13"}, -- An assignment?
		{"@conversation/corellia_privateer_trainer:s_bdd269be", "what_ship_14"}, -- What ship?
		{"@conversation/corellia_privateer_trainer:s_60c4f974", "where_do_i_15"}, -- Where do I go?
		{"@conversation/corellia_privateer_trainer:s_5e4ebfca", "and_when_im_16"}, -- And when I'm done?
		{"@conversation/corellia_privateer_trainer:s_c1ff5062", "im_looking_for_17"}, -- I'm looking for a mission. Do you have any?
		{"@conversation/corellia_privateer_trainer:s_133a724d", "are_you_going_102"}, -- Are you going to train me after this?
		{"@conversation/corellia_privateer_trainer:s_168", "are_you_going_149"}, -- Are you going to train me after this?
	}
}
rhea_convo_template:addScreen(whats_next_160);

whats_next_161 = ConvoScreen:new {
	id = "whats_next_161",
	leftDialog = "@conversation/corellia_privateer_trainer:s_844a124b", -- Piracy in this system has increased 17 percent since you signed-up!  This is inexcusable!  Now get out there and complete that patrol!
	stopConversation = "false",
	options = {
		{"@conversation/corellia_privateer_trainer:s_95d0a1f6", "an_assignment_13"}, -- An assignment?
		{"@conversation/corellia_privateer_trainer:s_bdd269be", "what_ship_14"}, -- What ship?
		{"@conversation/corellia_privateer_trainer:s_60c4f974", "where_do_i_15"}, -- Where do I go?
		{"@conversation/corellia_privateer_trainer:s_5e4ebfca", "and_when_im_16"}, -- And when I'm done?
		{"@conversation/corellia_privateer_trainer:s_c1ff5062", "im_looking_for_17"}, -- I'm looking for a mission. Do you have any?
		{"@conversation/corellia_privateer_trainer:s_133a724d", "are_you_going_102"}, -- Are you going to train me after this?
		{"@conversation/corellia_privateer_trainer:s_168", "are_you_going_149"}, -- Are you going to train me after this?
		{"@conversation/corellia_privateer_trainer:s_176", "are_you_going_197"}, -- Are you going to train me after this?
	}
}
rhea_convo_template:addScreen(whats_next_161);

whats_next_162 = ConvoScreen:new {
	id = "whats_next_162",
	leftDialog = "@conversation/corellia_privateer_trainer:s_429077be", -- You're never going to make a dent in the frequency of piracy in the Corellia system until you take out their leader!  Now get back out there and destroy the leader's ship!
	stopConversation = "false",
	options = {
		{"@conversation/corellia_privateer_trainer:s_95d0a1f6", "an_assignment_13"}, -- An assignment?
		{"@conversation/corellia_privateer_trainer:s_bdd269be", "what_ship_14"}, -- What ship?
		{"@conversation/corellia_privateer_trainer:s_60c4f974", "where_do_i_15"}, -- Where do I go?
		{"@conversation/corellia_privateer_trainer:s_5e4ebfca", "and_when_im_16"}, -- And when I'm done?
		{"@conversation/corellia_privateer_trainer:s_c1ff5062", "im_looking_for_17"}, -- I'm looking for a mission. Do you have any?
		{"@conversation/corellia_privateer_trainer:s_133a724d", "are_you_going_102"}, -- Are you going to train me after this?
		{"@conversation/corellia_privateer_trainer:s_168", "are_you_going_149"}, -- Are you going to train me after this?
		{"@conversation/corellia_privateer_trainer:s_176", "are_you_going_197"}, -- Are you going to train me after this?
		{"@conversation/corellia_privateer_trainer:s_183", "are_you_going_244"}, -- Are you going to train me after this?
	}
}
rhea_convo_template:addScreen(whats_next_162);

whats_next_163 = ConvoScreen:new {
	id = "whats_next_163",
	leftDialog = "@conversation/corellia_privateer_trainer:s_f053b088", -- Excellent work!
	stopConversation = "false",
	options = {
		{"@conversation/corellia_privateer_trainer:s_95d0a1f6", "an_assignment_13"}, -- An assignment?
		{"@conversation/corellia_privateer_trainer:s_bdd269be", "what_ship_14"}, -- What ship?
		{"@conversation/corellia_privateer_trainer:s_60c4f974", "where_do_i_15"}, -- Where do I go?
		{"@conversation/corellia_privateer_trainer:s_5e4ebfca", "and_when_im_16"}, -- And when I'm done?
		{"@conversation/corellia_privateer_trainer:s_c1ff5062", "im_looking_for_17"}, -- I'm looking for a mission. Do you have any?
		{"@conversation/corellia_privateer_trainer:s_133a724d", "are_you_going_102"}, -- Are you going to train me after this?
		{"@conversation/corellia_privateer_trainer:s_168", "are_you_going_149"}, -- Are you going to train me after this?
		{"@conversation/corellia_privateer_trainer:s_176", "are_you_going_197"}, -- Are you going to train me after this?
		{"@conversation/corellia_privateer_trainer:s_183", "are_you_going_244"}, -- Are you going to train me after this?
	}
}
rhea_convo_template:addScreen(whats_next_163);

whats_next_164 = ConvoScreen:new {
	id = "whats_next_164",
	leftDialog = "@conversation/corellia_privateer_trainer:s_160", -- Alright, your first assignment is to run a simple patrol.  From time to time pirates move into the area and harass merchants in our system. Just run this simple patrol and make sure there's no criminal activity going on.
	stopConversation = "false",
	options = {
		{"@conversation/corellia_privateer_trainer:s_95d0a1f6", "an_assignment_13"}, -- An assignment?
		{"@conversation/corellia_privateer_trainer:s_bdd269be", "what_ship_14"}, -- What ship?
		{"@conversation/corellia_privateer_trainer:s_60c4f974", "where_do_i_15"}, -- Where do I go?
		{"@conversation/corellia_privateer_trainer:s_5e4ebfca", "and_when_im_16"}, -- And when I'm done?
		{"@conversation/corellia_privateer_trainer:s_c1ff5062", "im_looking_for_17"}, -- I'm looking for a mission. Do you have any?
		{"@conversation/corellia_privateer_trainer:s_133a724d", "are_you_going_102"}, -- Are you going to train me after this?
		{"@conversation/corellia_privateer_trainer:s_168", "are_you_going_149"}, -- Are you going to train me after this?
		{"@conversation/corellia_privateer_trainer:s_176", "are_you_going_197"}, -- Are you going to train me after this?
		{"@conversation/corellia_privateer_trainer:s_183", "are_you_going_244"}, -- Are you going to train me after this?
	}
}
rhea_convo_template:addScreen(whats_next_164);

whats_next_165 = ConvoScreen:new {
	id = "whats_next_165",
	leftDialog = "@conversation/corellia_privateer_trainer:s_926359dd", -- Excellent job taking out those pirates.  No doubt, this won't be the end of them.
	stopConversation = "false",
	options = {
		{"@conversation/corellia_privateer_trainer:s_95d0a1f6", "an_assignment_13"}, -- An assignment?
		{"@conversation/corellia_privateer_trainer:s_bdd269be", "what_ship_14"}, -- What ship?
		{"@conversation/corellia_privateer_trainer:s_60c4f974", "where_do_i_15"}, -- Where do I go?
		{"@conversation/corellia_privateer_trainer:s_5e4ebfca", "and_when_im_16"}, -- And when I'm done?
		{"@conversation/corellia_privateer_trainer:s_c1ff5062", "im_looking_for_17"}, -- I'm looking for a mission. Do you have any?
		{"@conversation/corellia_privateer_trainer:s_133a724d", "are_you_going_102"}, -- Are you going to train me after this?
		{"@conversation/corellia_privateer_trainer:s_168", "are_you_going_149"}, -- Are you going to train me after this?
		{"@conversation/corellia_privateer_trainer:s_176", "are_you_going_197"}, -- Are you going to train me after this?
		{"@conversation/corellia_privateer_trainer:s_183", "are_you_going_244"}, -- Are you going to train me after this?
	}
}
rhea_convo_template:addScreen(whats_next_165);

whats_next_166 = ConvoScreen:new {
	id = "whats_next_166",
	leftDialog = "@conversation/corellia_privateer_trainer:s_4801be96", -- So, you were ambushed as you ran that patrol.  We need to hit them hard to send a message... make an example out of them.  I'm going to send you in to run that scum out of the system. I am uploading some possible waypoints into your nav computer, destroy any Black Sun you find.
	stopConversation = "false",
	options = {
		{"@conversation/corellia_privateer_trainer:s_95d0a1f6", "an_assignment_13"}, -- An assignment?
		{"@conversation/corellia_privateer_trainer:s_bdd269be", "what_ship_14"}, -- What ship?
		{"@conversation/corellia_privateer_trainer:s_60c4f974", "where_do_i_15"}, -- Where do I go?
		{"@conversation/corellia_privateer_trainer:s_5e4ebfca", "and_when_im_16"}, -- And when I'm done?
		{"@conversation/corellia_privateer_trainer:s_c1ff5062", "im_looking_for_17"}, -- I'm looking for a mission. Do you have any?
		{"@conversation/corellia_privateer_trainer:s_133a724d", "are_you_going_102"}, -- Are you going to train me after this?
		{"@conversation/corellia_privateer_trainer:s_168", "are_you_going_149"}, -- Are you going to train me after this?
		{"@conversation/corellia_privateer_trainer:s_176", "are_you_going_197"}, -- Are you going to train me after this?
		{"@conversation/corellia_privateer_trainer:s_183", "are_you_going_244"}, -- Are you going to train me after this?
	}
}
rhea_convo_template:addScreen(whats_next_166);

whats_next_167 = ConvoScreen:new {
	id = "whats_next_167",
	leftDialog = "@conversation/corellia_privateer_trainer:s_f8026f5d", -- Excellent work with that escort.  It's a good thing you were running that patrol, or there's no telling what might have happened to them.  I've got a little something extra for you, too.  It's a mercenary bandolier.  It'll help you keep your things organized.
	stopConversation = "false",
	options = {
		{"@conversation/corellia_privateer_trainer:s_95d0a1f6", "an_assignment_13"}, -- An assignment?
		{"@conversation/corellia_privateer_trainer:s_bdd269be", "what_ship_14"}, -- What ship?
		{"@conversation/corellia_privateer_trainer:s_60c4f974", "where_do_i_15"}, -- Where do I go?
		{"@conversation/corellia_privateer_trainer:s_5e4ebfca", "and_when_im_16"}, -- And when I'm done?
		{"@conversation/corellia_privateer_trainer:s_c1ff5062", "im_looking_for_17"}, -- I'm looking for a mission. Do you have any?
		{"@conversation/corellia_privateer_trainer:s_133a724d", "are_you_going_102"}, -- Are you going to train me after this?
		{"@conversation/corellia_privateer_trainer:s_168", "are_you_going_149"}, -- Are you going to train me after this?
		{"@conversation/corellia_privateer_trainer:s_176", "are_you_going_197"}, -- Are you going to train me after this?
		{"@conversation/corellia_privateer_trainer:s_183", "are_you_going_244"}, -- Are you going to train me after this?
	}
}
rhea_convo_template:addScreen(whats_next_167);

whats_next_168 = ConvoScreen:new {
	id = "whats_next_168",
	leftDialog = "@conversation/corellia_privateer_trainer:s_964fb39a", -- Just to be sure that's the last of them, we need you to run another patrol.  It's a little longer than the last one, but you already know how crafty those criminals can be.
	stopConversation = "false",
	options = {
		{"@conversation/corellia_privateer_trainer:s_95d0a1f6", "an_assignment_13"}, -- An assignment?
		{"@conversation/corellia_privateer_trainer:s_bdd269be", "what_ship_14"}, -- What ship?
		{"@conversation/corellia_privateer_trainer:s_60c4f974", "where_do_i_15"}, -- Where do I go?
		{"@conversation/corellia_privateer_trainer:s_5e4ebfca", "and_when_im_16"}, -- And when I'm done?
		{"@conversation/corellia_privateer_trainer:s_c1ff5062", "im_looking_for_17"}, -- I'm looking for a mission. Do you have any?
		{"@conversation/corellia_privateer_trainer:s_133a724d", "are_you_going_102"}, -- Are you going to train me after this?
		{"@conversation/corellia_privateer_trainer:s_168", "are_you_going_149"}, -- Are you going to train me after this?
		{"@conversation/corellia_privateer_trainer:s_176", "are_you_going_197"}, -- Are you going to train me after this?
		{"@conversation/corellia_privateer_trainer:s_183", "are_you_going_244"}, -- Are you going to train me after this?
	}
}
rhea_convo_template:addScreen(whats_next_168);

whats_next_169 = ConvoScreen:new {
	id = "whats_next_169",
	leftDialog = "@conversation/corellia_privateer_trainer:s_dc993cdb", -- Ha!  That'll show those thugs that CorSec is not to be trifled with.  You're really going to go places in this organization, I can tell already.
	stopConversation = "false",
	options = {
		{"@conversation/corellia_privateer_trainer:s_95d0a1f6", "an_assignment_13"}, -- An assignment?
		{"@conversation/corellia_privateer_trainer:s_bdd269be", "what_ship_14"}, -- What ship?
		{"@conversation/corellia_privateer_trainer:s_60c4f974", "where_do_i_15"}, -- Where do I go?
		{"@conversation/corellia_privateer_trainer:s_5e4ebfca", "and_when_im_16"}, -- And when I'm done?
		{"@conversation/corellia_privateer_trainer:s_c1ff5062", "im_looking_for_17"}, -- I'm looking for a mission. Do you have any?
		{"@conversation/corellia_privateer_trainer:s_133a724d", "are_you_going_102"}, -- Are you going to train me after this?
		{"@conversation/corellia_privateer_trainer:s_168", "are_you_going_149"}, -- Are you going to train me after this?
		{"@conversation/corellia_privateer_trainer:s_176", "are_you_going_197"}, -- Are you going to train me after this?
		{"@conversation/corellia_privateer_trainer:s_183", "are_you_going_244"}, -- Are you going to train me after this?
	}
}
rhea_convo_template:addScreen(whats_next_169);

whats_next_170 = ConvoScreen:new {
	id = "whats_next_170",
	leftDialog = "@conversation/corellia_privateer_trainer:s_8e1ed7f0", -- Enough of this!  Every time we send you out, you find more pirates.  We need to go straight to the source of the problem:  Their leader.  I know you're up to this:  Go find the pirate's leader and take him out.  Let the rest of them go to the outer rim if they want easy prey.
	stopConversation = "false",
	options = {
		{"@conversation/corellia_privateer_trainer:s_95d0a1f6", "an_assignment_13"}, -- An assignment?
		{"@conversation/corellia_privateer_trainer:s_bdd269be", "what_ship_14"}, -- What ship?
		{"@conversation/corellia_privateer_trainer:s_60c4f974", "where_do_i_15"}, -- Where do I go?
		{"@conversation/corellia_privateer_trainer:s_5e4ebfca", "and_when_im_16"}, -- And when I'm done?
		{"@conversation/corellia_privateer_trainer:s_c1ff5062", "im_looking_for_17"}, -- I'm looking for a mission. Do you have any?
		{"@conversation/corellia_privateer_trainer:s_133a724d", "are_you_going_102"}, -- Are you going to train me after this?
		{"@conversation/corellia_privateer_trainer:s_168", "are_you_going_149"}, -- Are you going to train me after this?
		{"@conversation/corellia_privateer_trainer:s_176", "are_you_going_197"}, -- Are you going to train me after this?
		{"@conversation/corellia_privateer_trainer:s_183", "are_you_going_244"}, -- Are you going to train me after this?
	}
}
rhea_convo_template:addScreen(whats_next_170);

whats_next_171 = ConvoScreen:new {
	id = "whats_next_171",
	leftDialog = "@conversation/corellia_privateer_trainer:s_5e6c7400", -- You are definitely ready to move up.  So I'll tell you what. I'll teach you about basic fighters.
	stopConversation = "false",
	options = {
		{"@conversation/corellia_privateer_trainer:s_95d0a1f6", "an_assignment_13"}, -- An assignment?
		{"@conversation/corellia_privateer_trainer:s_bdd269be", "what_ship_14"}, -- What ship?
		{"@conversation/corellia_privateer_trainer:s_60c4f974", "where_do_i_15"}, -- Where do I go?
		{"@conversation/corellia_privateer_trainer:s_5e4ebfca", "and_when_im_16"}, -- And when I'm done?
		{"@conversation/corellia_privateer_trainer:s_c1ff5062", "im_looking_for_17"}, -- I'm looking for a mission. Do you have any?
		{"@conversation/corellia_privateer_trainer:s_133a724d", "are_you_going_102"}, -- Are you going to train me after this?
		{"@conversation/corellia_privateer_trainer:s_168", "are_you_going_149"}, -- Are you going to train me after this?
		{"@conversation/corellia_privateer_trainer:s_176", "are_you_going_197"}, -- Are you going to train me after this?
		{"@conversation/corellia_privateer_trainer:s_183", "are_you_going_244"}, -- Are you going to train me after this?
		{"@conversation/corellia_privateer_trainer:s_c06c7aa9", "that_sounds_great"}, -- That sounds great.
	}
}
rhea_convo_template:addScreen(whats_next_171);

whats_next_172 = ConvoScreen:new {
	id = "whats_next_172",
	leftDialog = "@conversation/corellia_privateer_trainer:s_46ea46ad", -- We're quite satisfied with your level of performance.  I think it's time you learned a bit more, though.
	stopConversation = "false",
	options = {
		{"@conversation/corellia_privateer_trainer:s_95d0a1f6", "an_assignment_13"}, -- An assignment?
		{"@conversation/corellia_privateer_trainer:s_bdd269be", "what_ship_14"}, -- What ship?
		{"@conversation/corellia_privateer_trainer:s_60c4f974", "where_do_i_15"}, -- Where do I go?
		{"@conversation/corellia_privateer_trainer:s_5e4ebfca", "and_when_im_16"}, -- And when I'm done?
		{"@conversation/corellia_privateer_trainer:s_c1ff5062", "im_looking_for_17"}, -- I'm looking for a mission. Do you have any?
		{"@conversation/corellia_privateer_trainer:s_133a724d", "are_you_going_102"}, -- Are you going to train me after this?
		{"@conversation/corellia_privateer_trainer:s_168", "are_you_going_149"}, -- Are you going to train me after this?
		{"@conversation/corellia_privateer_trainer:s_176", "are_you_going_197"}, -- Are you going to train me after this?
		{"@conversation/corellia_privateer_trainer:s_183", "are_you_going_244"}, -- Are you going to train me after this?
		{"@conversation/corellia_privateer_trainer:s_c06c7aa9", "that_sounds_great"}, -- That sounds great.
		{"@conversation/corellia_privateer_trainer:s_229", "i_agree_247"}, -- I agree.
	}
}
rhea_convo_template:addScreen(whats_next_172);

whats_next_173 = ConvoScreen:new {
	id = "whats_next_173",
	leftDialog = "@conversation/corellia_privateer_trainer:s_a48c20c8", -- What's on your mind, officer? Thinking about performing some duty missions?
	stopConversation = "false",
	options = {
		{"@conversation/corellia_privateer_trainer:s_95d0a1f6", "an_assignment_13"}, -- An assignment?
		{"@conversation/corellia_privateer_trainer:s_bdd269be", "what_ship_14"}, -- What ship?
		{"@conversation/corellia_privateer_trainer:s_60c4f974", "where_do_i_15"}, -- Where do I go?
		{"@conversation/corellia_privateer_trainer:s_5e4ebfca", "and_when_im_16"}, -- And when I'm done?
		{"@conversation/corellia_privateer_trainer:s_c1ff5062", "im_looking_for_17"}, -- I'm looking for a mission. Do you have any?
		{"@conversation/corellia_privateer_trainer:s_133a724d", "are_you_going_102"}, -- Are you going to train me after this?
		{"@conversation/corellia_privateer_trainer:s_168", "are_you_going_149"}, -- Are you going to train me after this?
		{"@conversation/corellia_privateer_trainer:s_176", "are_you_going_197"}, -- Are you going to train me after this?
		{"@conversation/corellia_privateer_trainer:s_183", "are_you_going_244"}, -- Are you going to train me after this?
		{"@conversation/corellia_privateer_trainer:s_c06c7aa9", "that_sounds_great"}, -- That sounds great.
		{"@conversation/corellia_privateer_trainer:s_229", "i_agree_247"}, -- I agree.
		{"@conversation/corellia_privateer_trainer:s_6106187c", "what_is_a_260"}, -- What is a duty mission?
		{"@conversation/corellia_privateer_trainer:s_1a7f1a1b", "yes_i_am_261"}, -- Yes I am. What duty missions are available?
		{"@conversation/corellia_privateer_trainer:s_6276c98", "no_but_how_262"}, -- No, but how about some training?
		{"@conversation/corellia_privateer_trainer:s_2883b989", "not_right_now_263"}, -- Not right now, thanks.
	}
}
rhea_convo_template:addScreen(whats_next_173);

there_are_too = ConvoScreen:new {
	id = "there_are_too",
	leftDialog = "@conversation/corellia_privateer_trainer:s_9e5f75be", -- You've got your assignment and the control device for your ship in your datapad.  Go to the Starport and access the terminal to launch into space.
	stopConversation = "false",
	options = {
		{"@conversation/corellia_privateer_trainer:s_95d0a1f6", "an_assignment_13"}, -- An assignment?
		{"@conversation/corellia_privateer_trainer:s_bdd269be", "what_ship_14"}, -- What ship?
		{"@conversation/corellia_privateer_trainer:s_60c4f974", "where_do_i_15"}, -- Where do I go?
		{"@conversation/corellia_privateer_trainer:s_5e4ebfca", "and_when_im_16"}, -- And when I'm done?
	}
}
rhea_convo_template:addScreen(there_are_too);

there_are_too_174 = ConvoScreen:new {
	id = "there_are_too_174",
	leftDialog = "@conversation/corellia_privateer_trainer:s_698d80f7", -- Sorry, but you don't look like a pilot to me.
	stopConversation = "true",
	options = {
		{"@conversation/corellia_privateer_trainer:s_95d0a1f6", "an_assignment_13"}, -- An assignment?
		{"@conversation/corellia_privateer_trainer:s_bdd269be", "what_ship_14"}, -- What ship?
		{"@conversation/corellia_privateer_trainer:s_60c4f974", "where_do_i_15"}, -- Where do I go?
		{"@conversation/corellia_privateer_trainer:s_5e4ebfca", "and_when_im_16"}, -- And when I'm done?
	}
}
rhea_convo_template:addScreen(there_are_too_174);

there_are_too_175 = ConvoScreen:new {
	id = "there_are_too_175",
	leftDialog = "@conversation/corellia_privateer_trainer:s_c9f74b42", -- Greetings, citizen.  Keep your nose clean and we won't have any trouble.
	stopConversation = "true",
	options = {
		{"@conversation/corellia_privateer_trainer:s_95d0a1f6", "an_assignment_13"}, -- An assignment?
		{"@conversation/corellia_privateer_trainer:s_bdd269be", "what_ship_14"}, -- What ship?
		{"@conversation/corellia_privateer_trainer:s_60c4f974", "where_do_i_15"}, -- Where do I go?
		{"@conversation/corellia_privateer_trainer:s_5e4ebfca", "and_when_im_16"}, -- And when I'm done?
	}
}
rhea_convo_template:addScreen(there_are_too_175);

there_are_too_176 = ConvoScreen:new {
	id = "there_are_too_176",
	leftDialog = "@conversation/corellia_privateer_trainer:s_15502961", -- Nothing to worry about here, sir.  CorSec has the area well secured.
	stopConversation = "true",
	options = {
		{"@conversation/corellia_privateer_trainer:s_95d0a1f6", "an_assignment_13"}, -- An assignment?
		{"@conversation/corellia_privateer_trainer:s_bdd269be", "what_ship_14"}, -- What ship?
		{"@conversation/corellia_privateer_trainer:s_60c4f974", "where_do_i_15"}, -- Where do I go?
		{"@conversation/corellia_privateer_trainer:s_5e4ebfca", "and_when_im_16"}, -- And when I'm done?
	}
}
rhea_convo_template:addScreen(there_are_too_176);

there_are_too_177 = ConvoScreen:new {
	id = "there_are_too_177",
	leftDialog = "@conversation/corellia_privateer_trainer:s_ff684aed", -- Ah, I've heard of you!  You're not a bad pilot from what I understand. What can the CorSec do for you?
	stopConversation = "false",
	options = {
		{"@conversation/corellia_privateer_trainer:s_95d0a1f6", "an_assignment_13"}, -- An assignment?
		{"@conversation/corellia_privateer_trainer:s_bdd269be", "what_ship_14"}, -- What ship?
		{"@conversation/corellia_privateer_trainer:s_60c4f974", "where_do_i_15"}, -- Where do I go?
		{"@conversation/corellia_privateer_trainer:s_5e4ebfca", "and_when_im_16"}, -- And when I'm done?
		{"@conversation/corellia_privateer_trainer:s_c1ff5062", "im_looking_for_17"}, -- I'm looking for a mission. Do you have any?
	}
}
rhea_convo_template:addScreen(there_are_too_177);

there_are_too_178 = ConvoScreen:new {
	id = "there_are_too_178",
	leftDialog = "@conversation/corellia_privateer_trainer:s_f518ba4f", -- Hello!  Come to join the ranks of CorSec?
	stopConversation = "false",
	options = {
		{"@conversation/corellia_privateer_trainer:s_95d0a1f6", "an_assignment_13"}, -- An assignment?
		{"@conversation/corellia_privateer_trainer:s_bdd269be", "what_ship_14"}, -- What ship?
		{"@conversation/corellia_privateer_trainer:s_60c4f974", "where_do_i_15"}, -- Where do I go?
		{"@conversation/corellia_privateer_trainer:s_5e4ebfca", "and_when_im_16"}, -- And when I'm done?
		{"@conversation/corellia_privateer_trainer:s_c1ff5062", "im_looking_for_17"}, -- I'm looking for a mission. Do you have any?
	}
}
rhea_convo_template:addScreen(there_are_too_178);

there_are_too_179 = ConvoScreen:new {
	id = "there_are_too_179",
	leftDialog = "@conversation/corellia_privateer_trainer:s_149", -- You're going to need a ship, if you're going to fly for CorSec.  I'll add the Ship Control Codes to your datapad for you.  It's not a great ship, but it will get you around.
	stopConversation = "true",
	options = {
		{"@conversation/corellia_privateer_trainer:s_95d0a1f6", "an_assignment_13"}, -- An assignment?
		{"@conversation/corellia_privateer_trainer:s_bdd269be", "what_ship_14"}, -- What ship?
		{"@conversation/corellia_privateer_trainer:s_60c4f974", "where_do_i_15"}, -- Where do I go?
		{"@conversation/corellia_privateer_trainer:s_5e4ebfca", "and_when_im_16"}, -- And when I'm done?
		{"@conversation/corellia_privateer_trainer:s_c1ff5062", "im_looking_for_17"}, -- I'm looking for a mission. Do you have any?
	}
}
rhea_convo_template:addScreen(there_are_too_179);

there_are_too_180 = ConvoScreen:new {
	id = "there_are_too_180",
	leftDialog = "@conversation/corellia_privateer_trainer:s_333f5da9", -- What are you doing talking to me?  Isn't there somewhere you're supposed to be?
	stopConversation = "true",
	options = {
		{"@conversation/corellia_privateer_trainer:s_95d0a1f6", "an_assignment_13"}, -- An assignment?
		{"@conversation/corellia_privateer_trainer:s_bdd269be", "what_ship_14"}, -- What ship?
		{"@conversation/corellia_privateer_trainer:s_60c4f974", "where_do_i_15"}, -- Where do I go?
		{"@conversation/corellia_privateer_trainer:s_5e4ebfca", "and_when_im_16"}, -- And when I'm done?
		{"@conversation/corellia_privateer_trainer:s_c1ff5062", "im_looking_for_17"}, -- I'm looking for a mission. Do you have any?
	}
}
rhea_convo_template:addScreen(there_are_too_180);

there_are_too_181 = ConvoScreen:new {
	id = "there_are_too_181",
	leftDialog = "@conversation/corellia_privateer_trainer:s_cd44e585", -- Listen, something important has come up.  The captain wants to speak to you right away!  Go speak to Captain Rikkh in the next room.
	stopConversation = "true",
	options = {
		{"@conversation/corellia_privateer_trainer:s_95d0a1f6", "an_assignment_13"}, -- An assignment?
		{"@conversation/corellia_privateer_trainer:s_bdd269be", "what_ship_14"}, -- What ship?
		{"@conversation/corellia_privateer_trainer:s_60c4f974", "where_do_i_15"}, -- Where do I go?
		{"@conversation/corellia_privateer_trainer:s_5e4ebfca", "and_when_im_16"}, -- And when I'm done?
		{"@conversation/corellia_privateer_trainer:s_c1ff5062", "im_looking_for_17"}, -- I'm looking for a mission. Do you have any?
	}
}
rhea_convo_template:addScreen(there_are_too_181);

there_are_too_182 = ConvoScreen:new {
	id = "there_are_too_182",
	leftDialog = "@conversation/corellia_privateer_trainer:s_5cdbbd1f", -- What happened to you?  Never mind, never mind.  Get back out there and finish that patrol.
	stopConversation = "false",
	options = {
		{"@conversation/corellia_privateer_trainer:s_95d0a1f6", "an_assignment_13"}, -- An assignment?
		{"@conversation/corellia_privateer_trainer:s_bdd269be", "what_ship_14"}, -- What ship?
		{"@conversation/corellia_privateer_trainer:s_60c4f974", "where_do_i_15"}, -- Where do I go?
		{"@conversation/corellia_privateer_trainer:s_5e4ebfca", "and_when_im_16"}, -- And when I'm done?
		{"@conversation/corellia_privateer_trainer:s_c1ff5062", "im_looking_for_17"}, -- I'm looking for a mission. Do you have any?
		{"@conversation/corellia_privateer_trainer:s_133a724d", "are_you_going_102"}, -- Are you going to train me after this?
	}
}
rhea_convo_template:addScreen(there_are_too_182);

there_are_too_183 = ConvoScreen:new {
	id = "there_are_too_183",
	leftDialog = "@conversation/corellia_privateer_trainer:s_8b8a1542", -- That's bad news, but this is just the reason why CorSec is needed!  Go back out there and take out those pirates.  Defending this system from pirates and killers is all up to us.
	stopConversation = "false",
	options = {
		{"@conversation/corellia_privateer_trainer:s_95d0a1f6", "an_assignment_13"}, -- An assignment?
		{"@conversation/corellia_privateer_trainer:s_bdd269be", "what_ship_14"}, -- What ship?
		{"@conversation/corellia_privateer_trainer:s_60c4f974", "where_do_i_15"}, -- Where do I go?
		{"@conversation/corellia_privateer_trainer:s_5e4ebfca", "and_when_im_16"}, -- And when I'm done?
		{"@conversation/corellia_privateer_trainer:s_c1ff5062", "im_looking_for_17"}, -- I'm looking for a mission. Do you have any?
		{"@conversation/corellia_privateer_trainer:s_133a724d", "are_you_going_102"}, -- Are you going to train me after this?
		{"@conversation/corellia_privateer_trainer:s_168", "are_you_going_149"}, -- Are you going to train me after this?
	}
}
rhea_convo_template:addScreen(there_are_too_183);

there_are_too_184 = ConvoScreen:new {
	id = "there_are_too_184",
	leftDialog = "@conversation/corellia_privateer_trainer:s_844a124b", -- Piracy in this system has increased 17 percent since you signed-up!  This is inexcusable!  Now get out there and complete that patrol!
	stopConversation = "false",
	options = {
		{"@conversation/corellia_privateer_trainer:s_95d0a1f6", "an_assignment_13"}, -- An assignment?
		{"@conversation/corellia_privateer_trainer:s_bdd269be", "what_ship_14"}, -- What ship?
		{"@conversation/corellia_privateer_trainer:s_60c4f974", "where_do_i_15"}, -- Where do I go?
		{"@conversation/corellia_privateer_trainer:s_5e4ebfca", "and_when_im_16"}, -- And when I'm done?
		{"@conversation/corellia_privateer_trainer:s_c1ff5062", "im_looking_for_17"}, -- I'm looking for a mission. Do you have any?
		{"@conversation/corellia_privateer_trainer:s_133a724d", "are_you_going_102"}, -- Are you going to train me after this?
		{"@conversation/corellia_privateer_trainer:s_168", "are_you_going_149"}, -- Are you going to train me after this?
		{"@conversation/corellia_privateer_trainer:s_176", "are_you_going_197"}, -- Are you going to train me after this?
	}
}
rhea_convo_template:addScreen(there_are_too_184);

there_are_too_185 = ConvoScreen:new {
	id = "there_are_too_185",
	leftDialog = "@conversation/corellia_privateer_trainer:s_429077be", -- You're never going to make a dent in the frequency of piracy in the Corellia system until you take out their leader!  Now get back out there and destroy the leader's ship!
	stopConversation = "false",
	options = {
		{"@conversation/corellia_privateer_trainer:s_95d0a1f6", "an_assignment_13"}, -- An assignment?
		{"@conversation/corellia_privateer_trainer:s_bdd269be", "what_ship_14"}, -- What ship?
		{"@conversation/corellia_privateer_trainer:s_60c4f974", "where_do_i_15"}, -- Where do I go?
		{"@conversation/corellia_privateer_trainer:s_5e4ebfca", "and_when_im_16"}, -- And when I'm done?
		{"@conversation/corellia_privateer_trainer:s_c1ff5062", "im_looking_for_17"}, -- I'm looking for a mission. Do you have any?
		{"@conversation/corellia_privateer_trainer:s_133a724d", "are_you_going_102"}, -- Are you going to train me after this?
		{"@conversation/corellia_privateer_trainer:s_168", "are_you_going_149"}, -- Are you going to train me after this?
		{"@conversation/corellia_privateer_trainer:s_176", "are_you_going_197"}, -- Are you going to train me after this?
		{"@conversation/corellia_privateer_trainer:s_183", "are_you_going_244"}, -- Are you going to train me after this?
	}
}
rhea_convo_template:addScreen(there_are_too_185);

there_are_too_186 = ConvoScreen:new {
	id = "there_are_too_186",
	leftDialog = "@conversation/corellia_privateer_trainer:s_f053b088", -- Excellent work!
	stopConversation = "false",
	options = {
		{"@conversation/corellia_privateer_trainer:s_95d0a1f6", "an_assignment_13"}, -- An assignment?
		{"@conversation/corellia_privateer_trainer:s_bdd269be", "what_ship_14"}, -- What ship?
		{"@conversation/corellia_privateer_trainer:s_60c4f974", "where_do_i_15"}, -- Where do I go?
		{"@conversation/corellia_privateer_trainer:s_5e4ebfca", "and_when_im_16"}, -- And when I'm done?
		{"@conversation/corellia_privateer_trainer:s_c1ff5062", "im_looking_for_17"}, -- I'm looking for a mission. Do you have any?
		{"@conversation/corellia_privateer_trainer:s_133a724d", "are_you_going_102"}, -- Are you going to train me after this?
		{"@conversation/corellia_privateer_trainer:s_168", "are_you_going_149"}, -- Are you going to train me after this?
		{"@conversation/corellia_privateer_trainer:s_176", "are_you_going_197"}, -- Are you going to train me after this?
		{"@conversation/corellia_privateer_trainer:s_183", "are_you_going_244"}, -- Are you going to train me after this?
	}
}
rhea_convo_template:addScreen(there_are_too_186);

there_are_too_187 = ConvoScreen:new {
	id = "there_are_too_187",
	leftDialog = "@conversation/corellia_privateer_trainer:s_160", -- Alright, your first assignment is to run a simple patrol.  From time to time pirates move into the area and harass merchants in our system. Just run this simple patrol and make sure there's no criminal activity going on.
	stopConversation = "false",
	options = {
		{"@conversation/corellia_privateer_trainer:s_95d0a1f6", "an_assignment_13"}, -- An assignment?
		{"@conversation/corellia_privateer_trainer:s_bdd269be", "what_ship_14"}, -- What ship?
		{"@conversation/corellia_privateer_trainer:s_60c4f974", "where_do_i_15"}, -- Where do I go?
		{"@conversation/corellia_privateer_trainer:s_5e4ebfca", "and_when_im_16"}, -- And when I'm done?
		{"@conversation/corellia_privateer_trainer:s_c1ff5062", "im_looking_for_17"}, -- I'm looking for a mission. Do you have any?
		{"@conversation/corellia_privateer_trainer:s_133a724d", "are_you_going_102"}, -- Are you going to train me after this?
		{"@conversation/corellia_privateer_trainer:s_168", "are_you_going_149"}, -- Are you going to train me after this?
		{"@conversation/corellia_privateer_trainer:s_176", "are_you_going_197"}, -- Are you going to train me after this?
		{"@conversation/corellia_privateer_trainer:s_183", "are_you_going_244"}, -- Are you going to train me after this?
	}
}
rhea_convo_template:addScreen(there_are_too_187);

there_are_too_188 = ConvoScreen:new {
	id = "there_are_too_188",
	leftDialog = "@conversation/corellia_privateer_trainer:s_926359dd", -- Excellent job taking out those pirates.  No doubt, this won't be the end of them.
	stopConversation = "false",
	options = {
		{"@conversation/corellia_privateer_trainer:s_95d0a1f6", "an_assignment_13"}, -- An assignment?
		{"@conversation/corellia_privateer_trainer:s_bdd269be", "what_ship_14"}, -- What ship?
		{"@conversation/corellia_privateer_trainer:s_60c4f974", "where_do_i_15"}, -- Where do I go?
		{"@conversation/corellia_privateer_trainer:s_5e4ebfca", "and_when_im_16"}, -- And when I'm done?
		{"@conversation/corellia_privateer_trainer:s_c1ff5062", "im_looking_for_17"}, -- I'm looking for a mission. Do you have any?
		{"@conversation/corellia_privateer_trainer:s_133a724d", "are_you_going_102"}, -- Are you going to train me after this?
		{"@conversation/corellia_privateer_trainer:s_168", "are_you_going_149"}, -- Are you going to train me after this?
		{"@conversation/corellia_privateer_trainer:s_176", "are_you_going_197"}, -- Are you going to train me after this?
		{"@conversation/corellia_privateer_trainer:s_183", "are_you_going_244"}, -- Are you going to train me after this?
	}
}
rhea_convo_template:addScreen(there_are_too_188);

there_are_too_189 = ConvoScreen:new {
	id = "there_are_too_189",
	leftDialog = "@conversation/corellia_privateer_trainer:s_4801be96", -- So, you were ambushed as you ran that patrol.  We need to hit them hard to send a message... make an example out of them.  I'm going to send you in to run that scum out of the system. I am uploading some possible waypoints into your nav computer, destroy any Black Sun you find.
	stopConversation = "false",
	options = {
		{"@conversation/corellia_privateer_trainer:s_95d0a1f6", "an_assignment_13"}, -- An assignment?
		{"@conversation/corellia_privateer_trainer:s_bdd269be", "what_ship_14"}, -- What ship?
		{"@conversation/corellia_privateer_trainer:s_60c4f974", "where_do_i_15"}, -- Where do I go?
		{"@conversation/corellia_privateer_trainer:s_5e4ebfca", "and_when_im_16"}, -- And when I'm done?
		{"@conversation/corellia_privateer_trainer:s_c1ff5062", "im_looking_for_17"}, -- I'm looking for a mission. Do you have any?
		{"@conversation/corellia_privateer_trainer:s_133a724d", "are_you_going_102"}, -- Are you going to train me after this?
		{"@conversation/corellia_privateer_trainer:s_168", "are_you_going_149"}, -- Are you going to train me after this?
		{"@conversation/corellia_privateer_trainer:s_176", "are_you_going_197"}, -- Are you going to train me after this?
		{"@conversation/corellia_privateer_trainer:s_183", "are_you_going_244"}, -- Are you going to train me after this?
	}
}
rhea_convo_template:addScreen(there_are_too_189);

there_are_too_190 = ConvoScreen:new {
	id = "there_are_too_190",
	leftDialog = "@conversation/corellia_privateer_trainer:s_f8026f5d", -- Excellent work with that escort.  It's a good thing you were running that patrol, or there's no telling what might have happened to them.  I've got a little something extra for you, too.  It's a mercenary bandolier.  It'll help you keep your things organized.
	stopConversation = "false",
	options = {
		{"@conversation/corellia_privateer_trainer:s_95d0a1f6", "an_assignment_13"}, -- An assignment?
		{"@conversation/corellia_privateer_trainer:s_bdd269be", "what_ship_14"}, -- What ship?
		{"@conversation/corellia_privateer_trainer:s_60c4f974", "where_do_i_15"}, -- Where do I go?
		{"@conversation/corellia_privateer_trainer:s_5e4ebfca", "and_when_im_16"}, -- And when I'm done?
		{"@conversation/corellia_privateer_trainer:s_c1ff5062", "im_looking_for_17"}, -- I'm looking for a mission. Do you have any?
		{"@conversation/corellia_privateer_trainer:s_133a724d", "are_you_going_102"}, -- Are you going to train me after this?
		{"@conversation/corellia_privateer_trainer:s_168", "are_you_going_149"}, -- Are you going to train me after this?
		{"@conversation/corellia_privateer_trainer:s_176", "are_you_going_197"}, -- Are you going to train me after this?
		{"@conversation/corellia_privateer_trainer:s_183", "are_you_going_244"}, -- Are you going to train me after this?
	}
}
rhea_convo_template:addScreen(there_are_too_190);

there_are_too_191 = ConvoScreen:new {
	id = "there_are_too_191",
	leftDialog = "@conversation/corellia_privateer_trainer:s_964fb39a", -- Just to be sure that's the last of them, we need you to run another patrol.  It's a little longer than the last one, but you already know how crafty those criminals can be.
	stopConversation = "false",
	options = {
		{"@conversation/corellia_privateer_trainer:s_95d0a1f6", "an_assignment_13"}, -- An assignment?
		{"@conversation/corellia_privateer_trainer:s_bdd269be", "what_ship_14"}, -- What ship?
		{"@conversation/corellia_privateer_trainer:s_60c4f974", "where_do_i_15"}, -- Where do I go?
		{"@conversation/corellia_privateer_trainer:s_5e4ebfca", "and_when_im_16"}, -- And when I'm done?
		{"@conversation/corellia_privateer_trainer:s_c1ff5062", "im_looking_for_17"}, -- I'm looking for a mission. Do you have any?
		{"@conversation/corellia_privateer_trainer:s_133a724d", "are_you_going_102"}, -- Are you going to train me after this?
		{"@conversation/corellia_privateer_trainer:s_168", "are_you_going_149"}, -- Are you going to train me after this?
		{"@conversation/corellia_privateer_trainer:s_176", "are_you_going_197"}, -- Are you going to train me after this?
		{"@conversation/corellia_privateer_trainer:s_183", "are_you_going_244"}, -- Are you going to train me after this?
	}
}
rhea_convo_template:addScreen(there_are_too_191);

there_are_too_192 = ConvoScreen:new {
	id = "there_are_too_192",
	leftDialog = "@conversation/corellia_privateer_trainer:s_dc993cdb", -- Ha!  That'll show those thugs that CorSec is not to be trifled with.  You're really going to go places in this organization, I can tell already.
	stopConversation = "false",
	options = {
		{"@conversation/corellia_privateer_trainer:s_95d0a1f6", "an_assignment_13"}, -- An assignment?
		{"@conversation/corellia_privateer_trainer:s_bdd269be", "what_ship_14"}, -- What ship?
		{"@conversation/corellia_privateer_trainer:s_60c4f974", "where_do_i_15"}, -- Where do I go?
		{"@conversation/corellia_privateer_trainer:s_5e4ebfca", "and_when_im_16"}, -- And when I'm done?
		{"@conversation/corellia_privateer_trainer:s_c1ff5062", "im_looking_for_17"}, -- I'm looking for a mission. Do you have any?
		{"@conversation/corellia_privateer_trainer:s_133a724d", "are_you_going_102"}, -- Are you going to train me after this?
		{"@conversation/corellia_privateer_trainer:s_168", "are_you_going_149"}, -- Are you going to train me after this?
		{"@conversation/corellia_privateer_trainer:s_176", "are_you_going_197"}, -- Are you going to train me after this?
		{"@conversation/corellia_privateer_trainer:s_183", "are_you_going_244"}, -- Are you going to train me after this?
	}
}
rhea_convo_template:addScreen(there_are_too_192);

there_are_too_193 = ConvoScreen:new {
	id = "there_are_too_193",
	leftDialog = "@conversation/corellia_privateer_trainer:s_8e1ed7f0", -- Enough of this!  Every time we send you out, you find more pirates.  We need to go straight to the source of the problem:  Their leader.  I know you're up to this:  Go find the pirate's leader and take him out.  Let the rest of them go to the outer rim if they want easy prey.
	stopConversation = "false",
	options = {
		{"@conversation/corellia_privateer_trainer:s_95d0a1f6", "an_assignment_13"}, -- An assignment?
		{"@conversation/corellia_privateer_trainer:s_bdd269be", "what_ship_14"}, -- What ship?
		{"@conversation/corellia_privateer_trainer:s_60c4f974", "where_do_i_15"}, -- Where do I go?
		{"@conversation/corellia_privateer_trainer:s_5e4ebfca", "and_when_im_16"}, -- And when I'm done?
		{"@conversation/corellia_privateer_trainer:s_c1ff5062", "im_looking_for_17"}, -- I'm looking for a mission. Do you have any?
		{"@conversation/corellia_privateer_trainer:s_133a724d", "are_you_going_102"}, -- Are you going to train me after this?
		{"@conversation/corellia_privateer_trainer:s_168", "are_you_going_149"}, -- Are you going to train me after this?
		{"@conversation/corellia_privateer_trainer:s_176", "are_you_going_197"}, -- Are you going to train me after this?
		{"@conversation/corellia_privateer_trainer:s_183", "are_you_going_244"}, -- Are you going to train me after this?
	}
}
rhea_convo_template:addScreen(there_are_too_193);

there_are_too_194 = ConvoScreen:new {
	id = "there_are_too_194",
	leftDialog = "@conversation/corellia_privateer_trainer:s_5e6c7400", -- You are definitely ready to move up.  So I'll tell you what. I'll teach you about basic fighters.
	stopConversation = "false",
	options = {
		{"@conversation/corellia_privateer_trainer:s_95d0a1f6", "an_assignment_13"}, -- An assignment?
		{"@conversation/corellia_privateer_trainer:s_bdd269be", "what_ship_14"}, -- What ship?
		{"@conversation/corellia_privateer_trainer:s_60c4f974", "where_do_i_15"}, -- Where do I go?
		{"@conversation/corellia_privateer_trainer:s_5e4ebfca", "and_when_im_16"}, -- And when I'm done?
		{"@conversation/corellia_privateer_trainer:s_c1ff5062", "im_looking_for_17"}, -- I'm looking for a mission. Do you have any?
		{"@conversation/corellia_privateer_trainer:s_133a724d", "are_you_going_102"}, -- Are you going to train me after this?
		{"@conversation/corellia_privateer_trainer:s_168", "are_you_going_149"}, -- Are you going to train me after this?
		{"@conversation/corellia_privateer_trainer:s_176", "are_you_going_197"}, -- Are you going to train me after this?
		{"@conversation/corellia_privateer_trainer:s_183", "are_you_going_244"}, -- Are you going to train me after this?
		{"@conversation/corellia_privateer_trainer:s_c06c7aa9", "that_sounds_great"}, -- That sounds great.
	}
}
rhea_convo_template:addScreen(there_are_too_194);

there_are_too_195 = ConvoScreen:new {
	id = "there_are_too_195",
	leftDialog = "@conversation/corellia_privateer_trainer:s_46ea46ad", -- We're quite satisfied with your level of performance.  I think it's time you learned a bit more, though.
	stopConversation = "false",
	options = {
		{"@conversation/corellia_privateer_trainer:s_95d0a1f6", "an_assignment_13"}, -- An assignment?
		{"@conversation/corellia_privateer_trainer:s_bdd269be", "what_ship_14"}, -- What ship?
		{"@conversation/corellia_privateer_trainer:s_60c4f974", "where_do_i_15"}, -- Where do I go?
		{"@conversation/corellia_privateer_trainer:s_5e4ebfca", "and_when_im_16"}, -- And when I'm done?
		{"@conversation/corellia_privateer_trainer:s_c1ff5062", "im_looking_for_17"}, -- I'm looking for a mission. Do you have any?
		{"@conversation/corellia_privateer_trainer:s_133a724d", "are_you_going_102"}, -- Are you going to train me after this?
		{"@conversation/corellia_privateer_trainer:s_168", "are_you_going_149"}, -- Are you going to train me after this?
		{"@conversation/corellia_privateer_trainer:s_176", "are_you_going_197"}, -- Are you going to train me after this?
		{"@conversation/corellia_privateer_trainer:s_183", "are_you_going_244"}, -- Are you going to train me after this?
		{"@conversation/corellia_privateer_trainer:s_c06c7aa9", "that_sounds_great"}, -- That sounds great.
		{"@conversation/corellia_privateer_trainer:s_229", "i_agree_247"}, -- I agree.
	}
}
rhea_convo_template:addScreen(there_are_too_195);

there_are_too_196 = ConvoScreen:new {
	id = "there_are_too_196",
	leftDialog = "@conversation/corellia_privateer_trainer:s_a48c20c8", -- What's on your mind, officer? Thinking about performing some duty missions?
	stopConversation = "false",
	options = {
		{"@conversation/corellia_privateer_trainer:s_95d0a1f6", "an_assignment_13"}, -- An assignment?
		{"@conversation/corellia_privateer_trainer:s_bdd269be", "what_ship_14"}, -- What ship?
		{"@conversation/corellia_privateer_trainer:s_60c4f974", "where_do_i_15"}, -- Where do I go?
		{"@conversation/corellia_privateer_trainer:s_5e4ebfca", "and_when_im_16"}, -- And when I'm done?
		{"@conversation/corellia_privateer_trainer:s_c1ff5062", "im_looking_for_17"}, -- I'm looking for a mission. Do you have any?
		{"@conversation/corellia_privateer_trainer:s_133a724d", "are_you_going_102"}, -- Are you going to train me after this?
		{"@conversation/corellia_privateer_trainer:s_168", "are_you_going_149"}, -- Are you going to train me after this?
		{"@conversation/corellia_privateer_trainer:s_176", "are_you_going_197"}, -- Are you going to train me after this?
		{"@conversation/corellia_privateer_trainer:s_183", "are_you_going_244"}, -- Are you going to train me after this?
		{"@conversation/corellia_privateer_trainer:s_c06c7aa9", "that_sounds_great"}, -- That sounds great.
		{"@conversation/corellia_privateer_trainer:s_229", "i_agree_247"}, -- I agree.
		{"@conversation/corellia_privateer_trainer:s_6106187c", "what_is_a_260"}, -- What is a duty mission?
		{"@conversation/corellia_privateer_trainer:s_1a7f1a1b", "yes_i_am_261"}, -- Yes I am. What duty missions are available?
		{"@conversation/corellia_privateer_trainer:s_6276c98", "no_but_how_262"}, -- No, but how about some training?
		{"@conversation/corellia_privateer_trainer:s_2883b989", "not_right_now_263"}, -- Not right now, thanks.
	}
}
rhea_convo_template:addScreen(there_are_too_196);

are_you_going_197 = ConvoScreen:new {
	id = "are_you_going_197",
	leftDialog = "@conversation/corellia_privateer_trainer:s_e926d5f0", -- Almost, %NU.  I have just a couple more things for you to take care of before you can be trained further.  Starting with that patrol...
	stopConversation = "true",
	options = {}
}
rhea_convo_template:addScreen(are_you_going_197);

what_do_i = ConvoScreen:new {
	id = "what_do_i",
	leftDialog = "@conversation/corellia_privateer_trainer:s_9e5f75be", -- You've got your assignment and the control device for your ship in your datapad.  Go to the Starport and access the terminal to launch into space.
	stopConversation = "false",
	options = {
		{"@conversation/corellia_privateer_trainer:s_95d0a1f6", "an_assignment_13"}, -- An assignment?
		{"@conversation/corellia_privateer_trainer:s_bdd269be", "what_ship_14"}, -- What ship?
		{"@conversation/corellia_privateer_trainer:s_60c4f974", "where_do_i_15"}, -- Where do I go?
		{"@conversation/corellia_privateer_trainer:s_5e4ebfca", "and_when_im_16"}, -- And when I'm done?
	}
}
rhea_convo_template:addScreen(what_do_i);

what_do_i_198 = ConvoScreen:new {
	id = "what_do_i_198",
	leftDialog = "@conversation/corellia_privateer_trainer:s_698d80f7", -- Sorry, but you don't look like a pilot to me.
	stopConversation = "true",
	options = {
		{"@conversation/corellia_privateer_trainer:s_95d0a1f6", "an_assignment_13"}, -- An assignment?
		{"@conversation/corellia_privateer_trainer:s_bdd269be", "what_ship_14"}, -- What ship?
		{"@conversation/corellia_privateer_trainer:s_60c4f974", "where_do_i_15"}, -- Where do I go?
		{"@conversation/corellia_privateer_trainer:s_5e4ebfca", "and_when_im_16"}, -- And when I'm done?
	}
}
rhea_convo_template:addScreen(what_do_i_198);

what_do_i_199 = ConvoScreen:new {
	id = "what_do_i_199",
	leftDialog = "@conversation/corellia_privateer_trainer:s_c9f74b42", -- Greetings, citizen.  Keep your nose clean and we won't have any trouble.
	stopConversation = "true",
	options = {
		{"@conversation/corellia_privateer_trainer:s_95d0a1f6", "an_assignment_13"}, -- An assignment?
		{"@conversation/corellia_privateer_trainer:s_bdd269be", "what_ship_14"}, -- What ship?
		{"@conversation/corellia_privateer_trainer:s_60c4f974", "where_do_i_15"}, -- Where do I go?
		{"@conversation/corellia_privateer_trainer:s_5e4ebfca", "and_when_im_16"}, -- And when I'm done?
	}
}
rhea_convo_template:addScreen(what_do_i_199);

what_do_i_200 = ConvoScreen:new {
	id = "what_do_i_200",
	leftDialog = "@conversation/corellia_privateer_trainer:s_15502961", -- Nothing to worry about here, sir.  CorSec has the area well secured.
	stopConversation = "true",
	options = {
		{"@conversation/corellia_privateer_trainer:s_95d0a1f6", "an_assignment_13"}, -- An assignment?
		{"@conversation/corellia_privateer_trainer:s_bdd269be", "what_ship_14"}, -- What ship?
		{"@conversation/corellia_privateer_trainer:s_60c4f974", "where_do_i_15"}, -- Where do I go?
		{"@conversation/corellia_privateer_trainer:s_5e4ebfca", "and_when_im_16"}, -- And when I'm done?
	}
}
rhea_convo_template:addScreen(what_do_i_200);

what_do_i_201 = ConvoScreen:new {
	id = "what_do_i_201",
	leftDialog = "@conversation/corellia_privateer_trainer:s_ff684aed", -- Ah, I've heard of you!  You're not a bad pilot from what I understand. What can the CorSec do for you?
	stopConversation = "false",
	options = {
		{"@conversation/corellia_privateer_trainer:s_95d0a1f6", "an_assignment_13"}, -- An assignment?
		{"@conversation/corellia_privateer_trainer:s_bdd269be", "what_ship_14"}, -- What ship?
		{"@conversation/corellia_privateer_trainer:s_60c4f974", "where_do_i_15"}, -- Where do I go?
		{"@conversation/corellia_privateer_trainer:s_5e4ebfca", "and_when_im_16"}, -- And when I'm done?
		{"@conversation/corellia_privateer_trainer:s_c1ff5062", "im_looking_for_17"}, -- I'm looking for a mission. Do you have any?
	}
}
rhea_convo_template:addScreen(what_do_i_201);

what_do_i_202 = ConvoScreen:new {
	id = "what_do_i_202",
	leftDialog = "@conversation/corellia_privateer_trainer:s_f518ba4f", -- Hello!  Come to join the ranks of CorSec?
	stopConversation = "false",
	options = {
		{"@conversation/corellia_privateer_trainer:s_95d0a1f6", "an_assignment_13"}, -- An assignment?
		{"@conversation/corellia_privateer_trainer:s_bdd269be", "what_ship_14"}, -- What ship?
		{"@conversation/corellia_privateer_trainer:s_60c4f974", "where_do_i_15"}, -- Where do I go?
		{"@conversation/corellia_privateer_trainer:s_5e4ebfca", "and_when_im_16"}, -- And when I'm done?
		{"@conversation/corellia_privateer_trainer:s_c1ff5062", "im_looking_for_17"}, -- I'm looking for a mission. Do you have any?
	}
}
rhea_convo_template:addScreen(what_do_i_202);

what_do_i_203 = ConvoScreen:new {
	id = "what_do_i_203",
	leftDialog = "@conversation/corellia_privateer_trainer:s_149", -- You're going to need a ship, if you're going to fly for CorSec.  I'll add the Ship Control Codes to your datapad for you.  It's not a great ship, but it will get you around.
	stopConversation = "true",
	options = {
		{"@conversation/corellia_privateer_trainer:s_95d0a1f6", "an_assignment_13"}, -- An assignment?
		{"@conversation/corellia_privateer_trainer:s_bdd269be", "what_ship_14"}, -- What ship?
		{"@conversation/corellia_privateer_trainer:s_60c4f974", "where_do_i_15"}, -- Where do I go?
		{"@conversation/corellia_privateer_trainer:s_5e4ebfca", "and_when_im_16"}, -- And when I'm done?
		{"@conversation/corellia_privateer_trainer:s_c1ff5062", "im_looking_for_17"}, -- I'm looking for a mission. Do you have any?
	}
}
rhea_convo_template:addScreen(what_do_i_203);

what_do_i_204 = ConvoScreen:new {
	id = "what_do_i_204",
	leftDialog = "@conversation/corellia_privateer_trainer:s_333f5da9", -- What are you doing talking to me?  Isn't there somewhere you're supposed to be?
	stopConversation = "true",
	options = {
		{"@conversation/corellia_privateer_trainer:s_95d0a1f6", "an_assignment_13"}, -- An assignment?
		{"@conversation/corellia_privateer_trainer:s_bdd269be", "what_ship_14"}, -- What ship?
		{"@conversation/corellia_privateer_trainer:s_60c4f974", "where_do_i_15"}, -- Where do I go?
		{"@conversation/corellia_privateer_trainer:s_5e4ebfca", "and_when_im_16"}, -- And when I'm done?
		{"@conversation/corellia_privateer_trainer:s_c1ff5062", "im_looking_for_17"}, -- I'm looking for a mission. Do you have any?
	}
}
rhea_convo_template:addScreen(what_do_i_204);

what_do_i_205 = ConvoScreen:new {
	id = "what_do_i_205",
	leftDialog = "@conversation/corellia_privateer_trainer:s_cd44e585", -- Listen, something important has come up.  The captain wants to speak to you right away!  Go speak to Captain Rikkh in the next room.
	stopConversation = "true",
	options = {
		{"@conversation/corellia_privateer_trainer:s_95d0a1f6", "an_assignment_13"}, -- An assignment?
		{"@conversation/corellia_privateer_trainer:s_bdd269be", "what_ship_14"}, -- What ship?
		{"@conversation/corellia_privateer_trainer:s_60c4f974", "where_do_i_15"}, -- Where do I go?
		{"@conversation/corellia_privateer_trainer:s_5e4ebfca", "and_when_im_16"}, -- And when I'm done?
		{"@conversation/corellia_privateer_trainer:s_c1ff5062", "im_looking_for_17"}, -- I'm looking for a mission. Do you have any?
	}
}
rhea_convo_template:addScreen(what_do_i_205);

what_do_i_206 = ConvoScreen:new {
	id = "what_do_i_206",
	leftDialog = "@conversation/corellia_privateer_trainer:s_5cdbbd1f", -- What happened to you?  Never mind, never mind.  Get back out there and finish that patrol.
	stopConversation = "false",
	options = {
		{"@conversation/corellia_privateer_trainer:s_95d0a1f6", "an_assignment_13"}, -- An assignment?
		{"@conversation/corellia_privateer_trainer:s_bdd269be", "what_ship_14"}, -- What ship?
		{"@conversation/corellia_privateer_trainer:s_60c4f974", "where_do_i_15"}, -- Where do I go?
		{"@conversation/corellia_privateer_trainer:s_5e4ebfca", "and_when_im_16"}, -- And when I'm done?
		{"@conversation/corellia_privateer_trainer:s_c1ff5062", "im_looking_for_17"}, -- I'm looking for a mission. Do you have any?
		{"@conversation/corellia_privateer_trainer:s_133a724d", "are_you_going_102"}, -- Are you going to train me after this?
	}
}
rhea_convo_template:addScreen(what_do_i_206);

what_do_i_207 = ConvoScreen:new {
	id = "what_do_i_207",
	leftDialog = "@conversation/corellia_privateer_trainer:s_8b8a1542", -- That's bad news, but this is just the reason why CorSec is needed!  Go back out there and take out those pirates.  Defending this system from pirates and killers is all up to us.
	stopConversation = "false",
	options = {
		{"@conversation/corellia_privateer_trainer:s_95d0a1f6", "an_assignment_13"}, -- An assignment?
		{"@conversation/corellia_privateer_trainer:s_bdd269be", "what_ship_14"}, -- What ship?
		{"@conversation/corellia_privateer_trainer:s_60c4f974", "where_do_i_15"}, -- Where do I go?
		{"@conversation/corellia_privateer_trainer:s_5e4ebfca", "and_when_im_16"}, -- And when I'm done?
		{"@conversation/corellia_privateer_trainer:s_c1ff5062", "im_looking_for_17"}, -- I'm looking for a mission. Do you have any?
		{"@conversation/corellia_privateer_trainer:s_133a724d", "are_you_going_102"}, -- Are you going to train me after this?
		{"@conversation/corellia_privateer_trainer:s_168", "are_you_going_149"}, -- Are you going to train me after this?
	}
}
rhea_convo_template:addScreen(what_do_i_207);

what_do_i_208 = ConvoScreen:new {
	id = "what_do_i_208",
	leftDialog = "@conversation/corellia_privateer_trainer:s_844a124b", -- Piracy in this system has increased 17 percent since you signed-up!  This is inexcusable!  Now get out there and complete that patrol!
	stopConversation = "false",
	options = {
		{"@conversation/corellia_privateer_trainer:s_95d0a1f6", "an_assignment_13"}, -- An assignment?
		{"@conversation/corellia_privateer_trainer:s_bdd269be", "what_ship_14"}, -- What ship?
		{"@conversation/corellia_privateer_trainer:s_60c4f974", "where_do_i_15"}, -- Where do I go?
		{"@conversation/corellia_privateer_trainer:s_5e4ebfca", "and_when_im_16"}, -- And when I'm done?
		{"@conversation/corellia_privateer_trainer:s_c1ff5062", "im_looking_for_17"}, -- I'm looking for a mission. Do you have any?
		{"@conversation/corellia_privateer_trainer:s_133a724d", "are_you_going_102"}, -- Are you going to train me after this?
		{"@conversation/corellia_privateer_trainer:s_168", "are_you_going_149"}, -- Are you going to train me after this?
		{"@conversation/corellia_privateer_trainer:s_176", "are_you_going_197"}, -- Are you going to train me after this?
	}
}
rhea_convo_template:addScreen(what_do_i_208);

what_do_i_209 = ConvoScreen:new {
	id = "what_do_i_209",
	leftDialog = "@conversation/corellia_privateer_trainer:s_429077be", -- You're never going to make a dent in the frequency of piracy in the Corellia system until you take out their leader!  Now get back out there and destroy the leader's ship!
	stopConversation = "false",
	options = {
		{"@conversation/corellia_privateer_trainer:s_95d0a1f6", "an_assignment_13"}, -- An assignment?
		{"@conversation/corellia_privateer_trainer:s_bdd269be", "what_ship_14"}, -- What ship?
		{"@conversation/corellia_privateer_trainer:s_60c4f974", "where_do_i_15"}, -- Where do I go?
		{"@conversation/corellia_privateer_trainer:s_5e4ebfca", "and_when_im_16"}, -- And when I'm done?
		{"@conversation/corellia_privateer_trainer:s_c1ff5062", "im_looking_for_17"}, -- I'm looking for a mission. Do you have any?
		{"@conversation/corellia_privateer_trainer:s_133a724d", "are_you_going_102"}, -- Are you going to train me after this?
		{"@conversation/corellia_privateer_trainer:s_168", "are_you_going_149"}, -- Are you going to train me after this?
		{"@conversation/corellia_privateer_trainer:s_176", "are_you_going_197"}, -- Are you going to train me after this?
		{"@conversation/corellia_privateer_trainer:s_183", "are_you_going_244"}, -- Are you going to train me after this?
	}
}
rhea_convo_template:addScreen(what_do_i_209);

what_do_i_210 = ConvoScreen:new {
	id = "what_do_i_210",
	leftDialog = "@conversation/corellia_privateer_trainer:s_f053b088", -- Excellent work!
	stopConversation = "false",
	options = {
		{"@conversation/corellia_privateer_trainer:s_95d0a1f6", "an_assignment_13"}, -- An assignment?
		{"@conversation/corellia_privateer_trainer:s_bdd269be", "what_ship_14"}, -- What ship?
		{"@conversation/corellia_privateer_trainer:s_60c4f974", "where_do_i_15"}, -- Where do I go?
		{"@conversation/corellia_privateer_trainer:s_5e4ebfca", "and_when_im_16"}, -- And when I'm done?
		{"@conversation/corellia_privateer_trainer:s_c1ff5062", "im_looking_for_17"}, -- I'm looking for a mission. Do you have any?
		{"@conversation/corellia_privateer_trainer:s_133a724d", "are_you_going_102"}, -- Are you going to train me after this?
		{"@conversation/corellia_privateer_trainer:s_168", "are_you_going_149"}, -- Are you going to train me after this?
		{"@conversation/corellia_privateer_trainer:s_176", "are_you_going_197"}, -- Are you going to train me after this?
		{"@conversation/corellia_privateer_trainer:s_183", "are_you_going_244"}, -- Are you going to train me after this?
	}
}
rhea_convo_template:addScreen(what_do_i_210);

what_do_i_211 = ConvoScreen:new {
	id = "what_do_i_211",
	leftDialog = "@conversation/corellia_privateer_trainer:s_160", -- Alright, your first assignment is to run a simple patrol.  From time to time pirates move into the area and harass merchants in our system. Just run this simple patrol and make sure there's no criminal activity going on.
	stopConversation = "false",
	options = {
		{"@conversation/corellia_privateer_trainer:s_95d0a1f6", "an_assignment_13"}, -- An assignment?
		{"@conversation/corellia_privateer_trainer:s_bdd269be", "what_ship_14"}, -- What ship?
		{"@conversation/corellia_privateer_trainer:s_60c4f974", "where_do_i_15"}, -- Where do I go?
		{"@conversation/corellia_privateer_trainer:s_5e4ebfca", "and_when_im_16"}, -- And when I'm done?
		{"@conversation/corellia_privateer_trainer:s_c1ff5062", "im_looking_for_17"}, -- I'm looking for a mission. Do you have any?
		{"@conversation/corellia_privateer_trainer:s_133a724d", "are_you_going_102"}, -- Are you going to train me after this?
		{"@conversation/corellia_privateer_trainer:s_168", "are_you_going_149"}, -- Are you going to train me after this?
		{"@conversation/corellia_privateer_trainer:s_176", "are_you_going_197"}, -- Are you going to train me after this?
		{"@conversation/corellia_privateer_trainer:s_183", "are_you_going_244"}, -- Are you going to train me after this?
	}
}
rhea_convo_template:addScreen(what_do_i_211);

what_do_i_212 = ConvoScreen:new {
	id = "what_do_i_212",
	leftDialog = "@conversation/corellia_privateer_trainer:s_926359dd", -- Excellent job taking out those pirates.  No doubt, this won't be the end of them.
	stopConversation = "false",
	options = {
		{"@conversation/corellia_privateer_trainer:s_95d0a1f6", "an_assignment_13"}, -- An assignment?
		{"@conversation/corellia_privateer_trainer:s_bdd269be", "what_ship_14"}, -- What ship?
		{"@conversation/corellia_privateer_trainer:s_60c4f974", "where_do_i_15"}, -- Where do I go?
		{"@conversation/corellia_privateer_trainer:s_5e4ebfca", "and_when_im_16"}, -- And when I'm done?
		{"@conversation/corellia_privateer_trainer:s_c1ff5062", "im_looking_for_17"}, -- I'm looking for a mission. Do you have any?
		{"@conversation/corellia_privateer_trainer:s_133a724d", "are_you_going_102"}, -- Are you going to train me after this?
		{"@conversation/corellia_privateer_trainer:s_168", "are_you_going_149"}, -- Are you going to train me after this?
		{"@conversation/corellia_privateer_trainer:s_176", "are_you_going_197"}, -- Are you going to train me after this?
		{"@conversation/corellia_privateer_trainer:s_183", "are_you_going_244"}, -- Are you going to train me after this?
	}
}
rhea_convo_template:addScreen(what_do_i_212);

what_do_i_213 = ConvoScreen:new {
	id = "what_do_i_213",
	leftDialog = "@conversation/corellia_privateer_trainer:s_4801be96", -- So, you were ambushed as you ran that patrol.  We need to hit them hard to send a message... make an example out of them.  I'm going to send you in to run that scum out of the system. I am uploading some possible waypoints into your nav computer, destroy any Black Sun you find.
	stopConversation = "false",
	options = {
		{"@conversation/corellia_privateer_trainer:s_95d0a1f6", "an_assignment_13"}, -- An assignment?
		{"@conversation/corellia_privateer_trainer:s_bdd269be", "what_ship_14"}, -- What ship?
		{"@conversation/corellia_privateer_trainer:s_60c4f974", "where_do_i_15"}, -- Where do I go?
		{"@conversation/corellia_privateer_trainer:s_5e4ebfca", "and_when_im_16"}, -- And when I'm done?
		{"@conversation/corellia_privateer_trainer:s_c1ff5062", "im_looking_for_17"}, -- I'm looking for a mission. Do you have any?
		{"@conversation/corellia_privateer_trainer:s_133a724d", "are_you_going_102"}, -- Are you going to train me after this?
		{"@conversation/corellia_privateer_trainer:s_168", "are_you_going_149"}, -- Are you going to train me after this?
		{"@conversation/corellia_privateer_trainer:s_176", "are_you_going_197"}, -- Are you going to train me after this?
		{"@conversation/corellia_privateer_trainer:s_183", "are_you_going_244"}, -- Are you going to train me after this?
	}
}
rhea_convo_template:addScreen(what_do_i_213);

what_do_i_214 = ConvoScreen:new {
	id = "what_do_i_214",
	leftDialog = "@conversation/corellia_privateer_trainer:s_f8026f5d", -- Excellent work with that escort.  It's a good thing you were running that patrol, or there's no telling what might have happened to them.  I've got a little something extra for you, too.  It's a mercenary bandolier.  It'll help you keep your things organized.
	stopConversation = "false",
	options = {
		{"@conversation/corellia_privateer_trainer:s_95d0a1f6", "an_assignment_13"}, -- An assignment?
		{"@conversation/corellia_privateer_trainer:s_bdd269be", "what_ship_14"}, -- What ship?
		{"@conversation/corellia_privateer_trainer:s_60c4f974", "where_do_i_15"}, -- Where do I go?
		{"@conversation/corellia_privateer_trainer:s_5e4ebfca", "and_when_im_16"}, -- And when I'm done?
		{"@conversation/corellia_privateer_trainer:s_c1ff5062", "im_looking_for_17"}, -- I'm looking for a mission. Do you have any?
		{"@conversation/corellia_privateer_trainer:s_133a724d", "are_you_going_102"}, -- Are you going to train me after this?
		{"@conversation/corellia_privateer_trainer:s_168", "are_you_going_149"}, -- Are you going to train me after this?
		{"@conversation/corellia_privateer_trainer:s_176", "are_you_going_197"}, -- Are you going to train me after this?
		{"@conversation/corellia_privateer_trainer:s_183", "are_you_going_244"}, -- Are you going to train me after this?
	}
}
rhea_convo_template:addScreen(what_do_i_214);

what_do_i_215 = ConvoScreen:new {
	id = "what_do_i_215",
	leftDialog = "@conversation/corellia_privateer_trainer:s_964fb39a", -- Just to be sure that's the last of them, we need you to run another patrol.  It's a little longer than the last one, but you already know how crafty those criminals can be.
	stopConversation = "false",
	options = {
		{"@conversation/corellia_privateer_trainer:s_95d0a1f6", "an_assignment_13"}, -- An assignment?
		{"@conversation/corellia_privateer_trainer:s_bdd269be", "what_ship_14"}, -- What ship?
		{"@conversation/corellia_privateer_trainer:s_60c4f974", "where_do_i_15"}, -- Where do I go?
		{"@conversation/corellia_privateer_trainer:s_5e4ebfca", "and_when_im_16"}, -- And when I'm done?
		{"@conversation/corellia_privateer_trainer:s_c1ff5062", "im_looking_for_17"}, -- I'm looking for a mission. Do you have any?
		{"@conversation/corellia_privateer_trainer:s_133a724d", "are_you_going_102"}, -- Are you going to train me after this?
		{"@conversation/corellia_privateer_trainer:s_168", "are_you_going_149"}, -- Are you going to train me after this?
		{"@conversation/corellia_privateer_trainer:s_176", "are_you_going_197"}, -- Are you going to train me after this?
		{"@conversation/corellia_privateer_trainer:s_183", "are_you_going_244"}, -- Are you going to train me after this?
	}
}
rhea_convo_template:addScreen(what_do_i_215);

what_do_i_216 = ConvoScreen:new {
	id = "what_do_i_216",
	leftDialog = "@conversation/corellia_privateer_trainer:s_dc993cdb", -- Ha!  That'll show those thugs that CorSec is not to be trifled with.  You're really going to go places in this organization, I can tell already.
	stopConversation = "false",
	options = {
		{"@conversation/corellia_privateer_trainer:s_95d0a1f6", "an_assignment_13"}, -- An assignment?
		{"@conversation/corellia_privateer_trainer:s_bdd269be", "what_ship_14"}, -- What ship?
		{"@conversation/corellia_privateer_trainer:s_60c4f974", "where_do_i_15"}, -- Where do I go?
		{"@conversation/corellia_privateer_trainer:s_5e4ebfca", "and_when_im_16"}, -- And when I'm done?
		{"@conversation/corellia_privateer_trainer:s_c1ff5062", "im_looking_for_17"}, -- I'm looking for a mission. Do you have any?
		{"@conversation/corellia_privateer_trainer:s_133a724d", "are_you_going_102"}, -- Are you going to train me after this?
		{"@conversation/corellia_privateer_trainer:s_168", "are_you_going_149"}, -- Are you going to train me after this?
		{"@conversation/corellia_privateer_trainer:s_176", "are_you_going_197"}, -- Are you going to train me after this?
		{"@conversation/corellia_privateer_trainer:s_183", "are_you_going_244"}, -- Are you going to train me after this?
	}
}
rhea_convo_template:addScreen(what_do_i_216);

what_do_i_217 = ConvoScreen:new {
	id = "what_do_i_217",
	leftDialog = "@conversation/corellia_privateer_trainer:s_8e1ed7f0", -- Enough of this!  Every time we send you out, you find more pirates.  We need to go straight to the source of the problem:  Their leader.  I know you're up to this:  Go find the pirate's leader and take him out.  Let the rest of them go to the outer rim if they want easy prey.
	stopConversation = "false",
	options = {
		{"@conversation/corellia_privateer_trainer:s_95d0a1f6", "an_assignment_13"}, -- An assignment?
		{"@conversation/corellia_privateer_trainer:s_bdd269be", "what_ship_14"}, -- What ship?
		{"@conversation/corellia_privateer_trainer:s_60c4f974", "where_do_i_15"}, -- Where do I go?
		{"@conversation/corellia_privateer_trainer:s_5e4ebfca", "and_when_im_16"}, -- And when I'm done?
		{"@conversation/corellia_privateer_trainer:s_c1ff5062", "im_looking_for_17"}, -- I'm looking for a mission. Do you have any?
		{"@conversation/corellia_privateer_trainer:s_133a724d", "are_you_going_102"}, -- Are you going to train me after this?
		{"@conversation/corellia_privateer_trainer:s_168", "are_you_going_149"}, -- Are you going to train me after this?
		{"@conversation/corellia_privateer_trainer:s_176", "are_you_going_197"}, -- Are you going to train me after this?
		{"@conversation/corellia_privateer_trainer:s_183", "are_you_going_244"}, -- Are you going to train me after this?
	}
}
rhea_convo_template:addScreen(what_do_i_217);

what_do_i_218 = ConvoScreen:new {
	id = "what_do_i_218",
	leftDialog = "@conversation/corellia_privateer_trainer:s_5e6c7400", -- You are definitely ready to move up.  So I'll tell you what. I'll teach you about basic fighters.
	stopConversation = "false",
	options = {
		{"@conversation/corellia_privateer_trainer:s_95d0a1f6", "an_assignment_13"}, -- An assignment?
		{"@conversation/corellia_privateer_trainer:s_bdd269be", "what_ship_14"}, -- What ship?
		{"@conversation/corellia_privateer_trainer:s_60c4f974", "where_do_i_15"}, -- Where do I go?
		{"@conversation/corellia_privateer_trainer:s_5e4ebfca", "and_when_im_16"}, -- And when I'm done?
		{"@conversation/corellia_privateer_trainer:s_c1ff5062", "im_looking_for_17"}, -- I'm looking for a mission. Do you have any?
		{"@conversation/corellia_privateer_trainer:s_133a724d", "are_you_going_102"}, -- Are you going to train me after this?
		{"@conversation/corellia_privateer_trainer:s_168", "are_you_going_149"}, -- Are you going to train me after this?
		{"@conversation/corellia_privateer_trainer:s_176", "are_you_going_197"}, -- Are you going to train me after this?
		{"@conversation/corellia_privateer_trainer:s_183", "are_you_going_244"}, -- Are you going to train me after this?
		{"@conversation/corellia_privateer_trainer:s_c06c7aa9", "that_sounds_great"}, -- That sounds great.
	}
}
rhea_convo_template:addScreen(what_do_i_218);

what_do_i_219 = ConvoScreen:new {
	id = "what_do_i_219",
	leftDialog = "@conversation/corellia_privateer_trainer:s_46ea46ad", -- We're quite satisfied with your level of performance.  I think it's time you learned a bit more, though.
	stopConversation = "false",
	options = {
		{"@conversation/corellia_privateer_trainer:s_95d0a1f6", "an_assignment_13"}, -- An assignment?
		{"@conversation/corellia_privateer_trainer:s_bdd269be", "what_ship_14"}, -- What ship?
		{"@conversation/corellia_privateer_trainer:s_60c4f974", "where_do_i_15"}, -- Where do I go?
		{"@conversation/corellia_privateer_trainer:s_5e4ebfca", "and_when_im_16"}, -- And when I'm done?
		{"@conversation/corellia_privateer_trainer:s_c1ff5062", "im_looking_for_17"}, -- I'm looking for a mission. Do you have any?
		{"@conversation/corellia_privateer_trainer:s_133a724d", "are_you_going_102"}, -- Are you going to train me after this?
		{"@conversation/corellia_privateer_trainer:s_168", "are_you_going_149"}, -- Are you going to train me after this?
		{"@conversation/corellia_privateer_trainer:s_176", "are_you_going_197"}, -- Are you going to train me after this?
		{"@conversation/corellia_privateer_trainer:s_183", "are_you_going_244"}, -- Are you going to train me after this?
		{"@conversation/corellia_privateer_trainer:s_c06c7aa9", "that_sounds_great"}, -- That sounds great.
		{"@conversation/corellia_privateer_trainer:s_229", "i_agree_247"}, -- I agree.
	}
}
rhea_convo_template:addScreen(what_do_i_219);

what_do_i_220 = ConvoScreen:new {
	id = "what_do_i_220",
	leftDialog = "@conversation/corellia_privateer_trainer:s_a48c20c8", -- What's on your mind, officer? Thinking about performing some duty missions?
	stopConversation = "false",
	options = {
		{"@conversation/corellia_privateer_trainer:s_95d0a1f6", "an_assignment_13"}, -- An assignment?
		{"@conversation/corellia_privateer_trainer:s_bdd269be", "what_ship_14"}, -- What ship?
		{"@conversation/corellia_privateer_trainer:s_60c4f974", "where_do_i_15"}, -- Where do I go?
		{"@conversation/corellia_privateer_trainer:s_5e4ebfca", "and_when_im_16"}, -- And when I'm done?
		{"@conversation/corellia_privateer_trainer:s_c1ff5062", "im_looking_for_17"}, -- I'm looking for a mission. Do you have any?
		{"@conversation/corellia_privateer_trainer:s_133a724d", "are_you_going_102"}, -- Are you going to train me after this?
		{"@conversation/corellia_privateer_trainer:s_168", "are_you_going_149"}, -- Are you going to train me after this?
		{"@conversation/corellia_privateer_trainer:s_176", "are_you_going_197"}, -- Are you going to train me after this?
		{"@conversation/corellia_privateer_trainer:s_183", "are_you_going_244"}, -- Are you going to train me after this?
		{"@conversation/corellia_privateer_trainer:s_c06c7aa9", "that_sounds_great"}, -- That sounds great.
		{"@conversation/corellia_privateer_trainer:s_229", "i_agree_247"}, -- I agree.
		{"@conversation/corellia_privateer_trainer:s_6106187c", "what_is_a_260"}, -- What is a duty mission?
		{"@conversation/corellia_privateer_trainer:s_1a7f1a1b", "yes_i_am_261"}, -- Yes I am. What duty missions are available?
		{"@conversation/corellia_privateer_trainer:s_6276c98", "no_but_how_262"}, -- No, but how about some training?
		{"@conversation/corellia_privateer_trainer:s_2883b989", "not_right_now_263"}, -- Not right now, thanks.
	}
}
rhea_convo_template:addScreen(what_do_i_220);

i_love_being = ConvoScreen:new {
	id = "i_love_being",
	leftDialog = "@conversation/corellia_privateer_trainer:s_9e5f75be", -- You've got your assignment and the control device for your ship in your datapad.  Go to the Starport and access the terminal to launch into space.
	stopConversation = "false",
	options = {
		{"@conversation/corellia_privateer_trainer:s_95d0a1f6", "an_assignment_13"}, -- An assignment?
		{"@conversation/corellia_privateer_trainer:s_bdd269be", "what_ship_14"}, -- What ship?
		{"@conversation/corellia_privateer_trainer:s_60c4f974", "where_do_i_15"}, -- Where do I go?
		{"@conversation/corellia_privateer_trainer:s_5e4ebfca", "and_when_im_16"}, -- And when I'm done?
	}
}
rhea_convo_template:addScreen(i_love_being);

i_love_being_221 = ConvoScreen:new {
	id = "i_love_being_221",
	leftDialog = "@conversation/corellia_privateer_trainer:s_698d80f7", -- Sorry, but you don't look like a pilot to me.
	stopConversation = "true",
	options = {
		{"@conversation/corellia_privateer_trainer:s_95d0a1f6", "an_assignment_13"}, -- An assignment?
		{"@conversation/corellia_privateer_trainer:s_bdd269be", "what_ship_14"}, -- What ship?
		{"@conversation/corellia_privateer_trainer:s_60c4f974", "where_do_i_15"}, -- Where do I go?
		{"@conversation/corellia_privateer_trainer:s_5e4ebfca", "and_when_im_16"}, -- And when I'm done?
	}
}
rhea_convo_template:addScreen(i_love_being_221);

i_love_being_222 = ConvoScreen:new {
	id = "i_love_being_222",
	leftDialog = "@conversation/corellia_privateer_trainer:s_c9f74b42", -- Greetings, citizen.  Keep your nose clean and we won't have any trouble.
	stopConversation = "true",
	options = {
		{"@conversation/corellia_privateer_trainer:s_95d0a1f6", "an_assignment_13"}, -- An assignment?
		{"@conversation/corellia_privateer_trainer:s_bdd269be", "what_ship_14"}, -- What ship?
		{"@conversation/corellia_privateer_trainer:s_60c4f974", "where_do_i_15"}, -- Where do I go?
		{"@conversation/corellia_privateer_trainer:s_5e4ebfca", "and_when_im_16"}, -- And when I'm done?
	}
}
rhea_convo_template:addScreen(i_love_being_222);

i_love_being_223 = ConvoScreen:new {
	id = "i_love_being_223",
	leftDialog = "@conversation/corellia_privateer_trainer:s_15502961", -- Nothing to worry about here, sir.  CorSec has the area well secured.
	stopConversation = "true",
	options = {
		{"@conversation/corellia_privateer_trainer:s_95d0a1f6", "an_assignment_13"}, -- An assignment?
		{"@conversation/corellia_privateer_trainer:s_bdd269be", "what_ship_14"}, -- What ship?
		{"@conversation/corellia_privateer_trainer:s_60c4f974", "where_do_i_15"}, -- Where do I go?
		{"@conversation/corellia_privateer_trainer:s_5e4ebfca", "and_when_im_16"}, -- And when I'm done?
	}
}
rhea_convo_template:addScreen(i_love_being_223);

i_love_being_224 = ConvoScreen:new {
	id = "i_love_being_224",
	leftDialog = "@conversation/corellia_privateer_trainer:s_ff684aed", -- Ah, I've heard of you!  You're not a bad pilot from what I understand. What can the CorSec do for you?
	stopConversation = "false",
	options = {
		{"@conversation/corellia_privateer_trainer:s_95d0a1f6", "an_assignment_13"}, -- An assignment?
		{"@conversation/corellia_privateer_trainer:s_bdd269be", "what_ship_14"}, -- What ship?
		{"@conversation/corellia_privateer_trainer:s_60c4f974", "where_do_i_15"}, -- Where do I go?
		{"@conversation/corellia_privateer_trainer:s_5e4ebfca", "and_when_im_16"}, -- And when I'm done?
		{"@conversation/corellia_privateer_trainer:s_c1ff5062", "im_looking_for_17"}, -- I'm looking for a mission. Do you have any?
	}
}
rhea_convo_template:addScreen(i_love_being_224);

i_love_being_225 = ConvoScreen:new {
	id = "i_love_being_225",
	leftDialog = "@conversation/corellia_privateer_trainer:s_f518ba4f", -- Hello!  Come to join the ranks of CorSec?
	stopConversation = "false",
	options = {
		{"@conversation/corellia_privateer_trainer:s_95d0a1f6", "an_assignment_13"}, -- An assignment?
		{"@conversation/corellia_privateer_trainer:s_bdd269be", "what_ship_14"}, -- What ship?
		{"@conversation/corellia_privateer_trainer:s_60c4f974", "where_do_i_15"}, -- Where do I go?
		{"@conversation/corellia_privateer_trainer:s_5e4ebfca", "and_when_im_16"}, -- And when I'm done?
		{"@conversation/corellia_privateer_trainer:s_c1ff5062", "im_looking_for_17"}, -- I'm looking for a mission. Do you have any?
	}
}
rhea_convo_template:addScreen(i_love_being_225);

i_love_being_226 = ConvoScreen:new {
	id = "i_love_being_226",
	leftDialog = "@conversation/corellia_privateer_trainer:s_149", -- You're going to need a ship, if you're going to fly for CorSec.  I'll add the Ship Control Codes to your datapad for you.  It's not a great ship, but it will get you around.
	stopConversation = "true",
	options = {
		{"@conversation/corellia_privateer_trainer:s_95d0a1f6", "an_assignment_13"}, -- An assignment?
		{"@conversation/corellia_privateer_trainer:s_bdd269be", "what_ship_14"}, -- What ship?
		{"@conversation/corellia_privateer_trainer:s_60c4f974", "where_do_i_15"}, -- Where do I go?
		{"@conversation/corellia_privateer_trainer:s_5e4ebfca", "and_when_im_16"}, -- And when I'm done?
		{"@conversation/corellia_privateer_trainer:s_c1ff5062", "im_looking_for_17"}, -- I'm looking for a mission. Do you have any?
	}
}
rhea_convo_template:addScreen(i_love_being_226);

i_love_being_227 = ConvoScreen:new {
	id = "i_love_being_227",
	leftDialog = "@conversation/corellia_privateer_trainer:s_333f5da9", -- What are you doing talking to me?  Isn't there somewhere you're supposed to be?
	stopConversation = "true",
	options = {
		{"@conversation/corellia_privateer_trainer:s_95d0a1f6", "an_assignment_13"}, -- An assignment?
		{"@conversation/corellia_privateer_trainer:s_bdd269be", "what_ship_14"}, -- What ship?
		{"@conversation/corellia_privateer_trainer:s_60c4f974", "where_do_i_15"}, -- Where do I go?
		{"@conversation/corellia_privateer_trainer:s_5e4ebfca", "and_when_im_16"}, -- And when I'm done?
		{"@conversation/corellia_privateer_trainer:s_c1ff5062", "im_looking_for_17"}, -- I'm looking for a mission. Do you have any?
	}
}
rhea_convo_template:addScreen(i_love_being_227);

i_love_being_228 = ConvoScreen:new {
	id = "i_love_being_228",
	leftDialog = "@conversation/corellia_privateer_trainer:s_cd44e585", -- Listen, something important has come up.  The captain wants to speak to you right away!  Go speak to Captain Rikkh in the next room.
	stopConversation = "true",
	options = {
		{"@conversation/corellia_privateer_trainer:s_95d0a1f6", "an_assignment_13"}, -- An assignment?
		{"@conversation/corellia_privateer_trainer:s_bdd269be", "what_ship_14"}, -- What ship?
		{"@conversation/corellia_privateer_trainer:s_60c4f974", "where_do_i_15"}, -- Where do I go?
		{"@conversation/corellia_privateer_trainer:s_5e4ebfca", "and_when_im_16"}, -- And when I'm done?
		{"@conversation/corellia_privateer_trainer:s_c1ff5062", "im_looking_for_17"}, -- I'm looking for a mission. Do you have any?
	}
}
rhea_convo_template:addScreen(i_love_being_228);

i_love_being_229 = ConvoScreen:new {
	id = "i_love_being_229",
	leftDialog = "@conversation/corellia_privateer_trainer:s_5cdbbd1f", -- What happened to you?  Never mind, never mind.  Get back out there and finish that patrol.
	stopConversation = "false",
	options = {
		{"@conversation/corellia_privateer_trainer:s_95d0a1f6", "an_assignment_13"}, -- An assignment?
		{"@conversation/corellia_privateer_trainer:s_bdd269be", "what_ship_14"}, -- What ship?
		{"@conversation/corellia_privateer_trainer:s_60c4f974", "where_do_i_15"}, -- Where do I go?
		{"@conversation/corellia_privateer_trainer:s_5e4ebfca", "and_when_im_16"}, -- And when I'm done?
		{"@conversation/corellia_privateer_trainer:s_c1ff5062", "im_looking_for_17"}, -- I'm looking for a mission. Do you have any?
		{"@conversation/corellia_privateer_trainer:s_133a724d", "are_you_going_102"}, -- Are you going to train me after this?
	}
}
rhea_convo_template:addScreen(i_love_being_229);

i_love_being_230 = ConvoScreen:new {
	id = "i_love_being_230",
	leftDialog = "@conversation/corellia_privateer_trainer:s_8b8a1542", -- That's bad news, but this is just the reason why CorSec is needed!  Go back out there and take out those pirates.  Defending this system from pirates and killers is all up to us.
	stopConversation = "false",
	options = {
		{"@conversation/corellia_privateer_trainer:s_95d0a1f6", "an_assignment_13"}, -- An assignment?
		{"@conversation/corellia_privateer_trainer:s_bdd269be", "what_ship_14"}, -- What ship?
		{"@conversation/corellia_privateer_trainer:s_60c4f974", "where_do_i_15"}, -- Where do I go?
		{"@conversation/corellia_privateer_trainer:s_5e4ebfca", "and_when_im_16"}, -- And when I'm done?
		{"@conversation/corellia_privateer_trainer:s_c1ff5062", "im_looking_for_17"}, -- I'm looking for a mission. Do you have any?
		{"@conversation/corellia_privateer_trainer:s_133a724d", "are_you_going_102"}, -- Are you going to train me after this?
		{"@conversation/corellia_privateer_trainer:s_168", "are_you_going_149"}, -- Are you going to train me after this?
	}
}
rhea_convo_template:addScreen(i_love_being_230);

i_love_being_231 = ConvoScreen:new {
	id = "i_love_being_231",
	leftDialog = "@conversation/corellia_privateer_trainer:s_844a124b", -- Piracy in this system has increased 17 percent since you signed-up!  This is inexcusable!  Now get out there and complete that patrol!
	stopConversation = "false",
	options = {
		{"@conversation/corellia_privateer_trainer:s_95d0a1f6", "an_assignment_13"}, -- An assignment?
		{"@conversation/corellia_privateer_trainer:s_bdd269be", "what_ship_14"}, -- What ship?
		{"@conversation/corellia_privateer_trainer:s_60c4f974", "where_do_i_15"}, -- Where do I go?
		{"@conversation/corellia_privateer_trainer:s_5e4ebfca", "and_when_im_16"}, -- And when I'm done?
		{"@conversation/corellia_privateer_trainer:s_c1ff5062", "im_looking_for_17"}, -- I'm looking for a mission. Do you have any?
		{"@conversation/corellia_privateer_trainer:s_133a724d", "are_you_going_102"}, -- Are you going to train me after this?
		{"@conversation/corellia_privateer_trainer:s_168", "are_you_going_149"}, -- Are you going to train me after this?
		{"@conversation/corellia_privateer_trainer:s_176", "are_you_going_197"}, -- Are you going to train me after this?
	}
}
rhea_convo_template:addScreen(i_love_being_231);

i_love_being_232 = ConvoScreen:new {
	id = "i_love_being_232",
	leftDialog = "@conversation/corellia_privateer_trainer:s_429077be", -- You're never going to make a dent in the frequency of piracy in the Corellia system until you take out their leader!  Now get back out there and destroy the leader's ship!
	stopConversation = "false",
	options = {
		{"@conversation/corellia_privateer_trainer:s_95d0a1f6", "an_assignment_13"}, -- An assignment?
		{"@conversation/corellia_privateer_trainer:s_bdd269be", "what_ship_14"}, -- What ship?
		{"@conversation/corellia_privateer_trainer:s_60c4f974", "where_do_i_15"}, -- Where do I go?
		{"@conversation/corellia_privateer_trainer:s_5e4ebfca", "and_when_im_16"}, -- And when I'm done?
		{"@conversation/corellia_privateer_trainer:s_c1ff5062", "im_looking_for_17"}, -- I'm looking for a mission. Do you have any?
		{"@conversation/corellia_privateer_trainer:s_133a724d", "are_you_going_102"}, -- Are you going to train me after this?
		{"@conversation/corellia_privateer_trainer:s_168", "are_you_going_149"}, -- Are you going to train me after this?
		{"@conversation/corellia_privateer_trainer:s_176", "are_you_going_197"}, -- Are you going to train me after this?
		{"@conversation/corellia_privateer_trainer:s_183", "are_you_going_244"}, -- Are you going to train me after this?
	}
}
rhea_convo_template:addScreen(i_love_being_232);

i_love_being_233 = ConvoScreen:new {
	id = "i_love_being_233",
	leftDialog = "@conversation/corellia_privateer_trainer:s_f053b088", -- Excellent work!
	stopConversation = "false",
	options = {
		{"@conversation/corellia_privateer_trainer:s_95d0a1f6", "an_assignment_13"}, -- An assignment?
		{"@conversation/corellia_privateer_trainer:s_bdd269be", "what_ship_14"}, -- What ship?
		{"@conversation/corellia_privateer_trainer:s_60c4f974", "where_do_i_15"}, -- Where do I go?
		{"@conversation/corellia_privateer_trainer:s_5e4ebfca", "and_when_im_16"}, -- And when I'm done?
		{"@conversation/corellia_privateer_trainer:s_c1ff5062", "im_looking_for_17"}, -- I'm looking for a mission. Do you have any?
		{"@conversation/corellia_privateer_trainer:s_133a724d", "are_you_going_102"}, -- Are you going to train me after this?
		{"@conversation/corellia_privateer_trainer:s_168", "are_you_going_149"}, -- Are you going to train me after this?
		{"@conversation/corellia_privateer_trainer:s_176", "are_you_going_197"}, -- Are you going to train me after this?
		{"@conversation/corellia_privateer_trainer:s_183", "are_you_going_244"}, -- Are you going to train me after this?
	}
}
rhea_convo_template:addScreen(i_love_being_233);

i_love_being_234 = ConvoScreen:new {
	id = "i_love_being_234",
	leftDialog = "@conversation/corellia_privateer_trainer:s_160", -- Alright, your first assignment is to run a simple patrol.  From time to time pirates move into the area and harass merchants in our system. Just run this simple patrol and make sure there's no criminal activity going on.
	stopConversation = "false",
	options = {
		{"@conversation/corellia_privateer_trainer:s_95d0a1f6", "an_assignment_13"}, -- An assignment?
		{"@conversation/corellia_privateer_trainer:s_bdd269be", "what_ship_14"}, -- What ship?
		{"@conversation/corellia_privateer_trainer:s_60c4f974", "where_do_i_15"}, -- Where do I go?
		{"@conversation/corellia_privateer_trainer:s_5e4ebfca", "and_when_im_16"}, -- And when I'm done?
		{"@conversation/corellia_privateer_trainer:s_c1ff5062", "im_looking_for_17"}, -- I'm looking for a mission. Do you have any?
		{"@conversation/corellia_privateer_trainer:s_133a724d", "are_you_going_102"}, -- Are you going to train me after this?
		{"@conversation/corellia_privateer_trainer:s_168", "are_you_going_149"}, -- Are you going to train me after this?
		{"@conversation/corellia_privateer_trainer:s_176", "are_you_going_197"}, -- Are you going to train me after this?
		{"@conversation/corellia_privateer_trainer:s_183", "are_you_going_244"}, -- Are you going to train me after this?
	}
}
rhea_convo_template:addScreen(i_love_being_234);

i_love_being_235 = ConvoScreen:new {
	id = "i_love_being_235",
	leftDialog = "@conversation/corellia_privateer_trainer:s_926359dd", -- Excellent job taking out those pirates.  No doubt, this won't be the end of them.
	stopConversation = "false",
	options = {
		{"@conversation/corellia_privateer_trainer:s_95d0a1f6", "an_assignment_13"}, -- An assignment?
		{"@conversation/corellia_privateer_trainer:s_bdd269be", "what_ship_14"}, -- What ship?
		{"@conversation/corellia_privateer_trainer:s_60c4f974", "where_do_i_15"}, -- Where do I go?
		{"@conversation/corellia_privateer_trainer:s_5e4ebfca", "and_when_im_16"}, -- And when I'm done?
		{"@conversation/corellia_privateer_trainer:s_c1ff5062", "im_looking_for_17"}, -- I'm looking for a mission. Do you have any?
		{"@conversation/corellia_privateer_trainer:s_133a724d", "are_you_going_102"}, -- Are you going to train me after this?
		{"@conversation/corellia_privateer_trainer:s_168", "are_you_going_149"}, -- Are you going to train me after this?
		{"@conversation/corellia_privateer_trainer:s_176", "are_you_going_197"}, -- Are you going to train me after this?
		{"@conversation/corellia_privateer_trainer:s_183", "are_you_going_244"}, -- Are you going to train me after this?
	}
}
rhea_convo_template:addScreen(i_love_being_235);

i_love_being_236 = ConvoScreen:new {
	id = "i_love_being_236",
	leftDialog = "@conversation/corellia_privateer_trainer:s_4801be96", -- So, you were ambushed as you ran that patrol.  We need to hit them hard to send a message... make an example out of them.  I'm going to send you in to run that scum out of the system. I am uploading some possible waypoints into your nav computer, destroy any Black Sun you find.
	stopConversation = "false",
	options = {
		{"@conversation/corellia_privateer_trainer:s_95d0a1f6", "an_assignment_13"}, -- An assignment?
		{"@conversation/corellia_privateer_trainer:s_bdd269be", "what_ship_14"}, -- What ship?
		{"@conversation/corellia_privateer_trainer:s_60c4f974", "where_do_i_15"}, -- Where do I go?
		{"@conversation/corellia_privateer_trainer:s_5e4ebfca", "and_when_im_16"}, -- And when I'm done?
		{"@conversation/corellia_privateer_trainer:s_c1ff5062", "im_looking_for_17"}, -- I'm looking for a mission. Do you have any?
		{"@conversation/corellia_privateer_trainer:s_133a724d", "are_you_going_102"}, -- Are you going to train me after this?
		{"@conversation/corellia_privateer_trainer:s_168", "are_you_going_149"}, -- Are you going to train me after this?
		{"@conversation/corellia_privateer_trainer:s_176", "are_you_going_197"}, -- Are you going to train me after this?
		{"@conversation/corellia_privateer_trainer:s_183", "are_you_going_244"}, -- Are you going to train me after this?
	}
}
rhea_convo_template:addScreen(i_love_being_236);

i_love_being_237 = ConvoScreen:new {
	id = "i_love_being_237",
	leftDialog = "@conversation/corellia_privateer_trainer:s_f8026f5d", -- Excellent work with that escort.  It's a good thing you were running that patrol, or there's no telling what might have happened to them.  I've got a little something extra for you, too.  It's a mercenary bandolier.  It'll help you keep your things organized.
	stopConversation = "false",
	options = {
		{"@conversation/corellia_privateer_trainer:s_95d0a1f6", "an_assignment_13"}, -- An assignment?
		{"@conversation/corellia_privateer_trainer:s_bdd269be", "what_ship_14"}, -- What ship?
		{"@conversation/corellia_privateer_trainer:s_60c4f974", "where_do_i_15"}, -- Where do I go?
		{"@conversation/corellia_privateer_trainer:s_5e4ebfca", "and_when_im_16"}, -- And when I'm done?
		{"@conversation/corellia_privateer_trainer:s_c1ff5062", "im_looking_for_17"}, -- I'm looking for a mission. Do you have any?
		{"@conversation/corellia_privateer_trainer:s_133a724d", "are_you_going_102"}, -- Are you going to train me after this?
		{"@conversation/corellia_privateer_trainer:s_168", "are_you_going_149"}, -- Are you going to train me after this?
		{"@conversation/corellia_privateer_trainer:s_176", "are_you_going_197"}, -- Are you going to train me after this?
		{"@conversation/corellia_privateer_trainer:s_183", "are_you_going_244"}, -- Are you going to train me after this?
	}
}
rhea_convo_template:addScreen(i_love_being_237);

i_love_being_238 = ConvoScreen:new {
	id = "i_love_being_238",
	leftDialog = "@conversation/corellia_privateer_trainer:s_964fb39a", -- Just to be sure that's the last of them, we need you to run another patrol.  It's a little longer than the last one, but you already know how crafty those criminals can be.
	stopConversation = "false",
	options = {
		{"@conversation/corellia_privateer_trainer:s_95d0a1f6", "an_assignment_13"}, -- An assignment?
		{"@conversation/corellia_privateer_trainer:s_bdd269be", "what_ship_14"}, -- What ship?
		{"@conversation/corellia_privateer_trainer:s_60c4f974", "where_do_i_15"}, -- Where do I go?
		{"@conversation/corellia_privateer_trainer:s_5e4ebfca", "and_when_im_16"}, -- And when I'm done?
		{"@conversation/corellia_privateer_trainer:s_c1ff5062", "im_looking_for_17"}, -- I'm looking for a mission. Do you have any?
		{"@conversation/corellia_privateer_trainer:s_133a724d", "are_you_going_102"}, -- Are you going to train me after this?
		{"@conversation/corellia_privateer_trainer:s_168", "are_you_going_149"}, -- Are you going to train me after this?
		{"@conversation/corellia_privateer_trainer:s_176", "are_you_going_197"}, -- Are you going to train me after this?
		{"@conversation/corellia_privateer_trainer:s_183", "are_you_going_244"}, -- Are you going to train me after this?
	}
}
rhea_convo_template:addScreen(i_love_being_238);

i_love_being_239 = ConvoScreen:new {
	id = "i_love_being_239",
	leftDialog = "@conversation/corellia_privateer_trainer:s_dc993cdb", -- Ha!  That'll show those thugs that CorSec is not to be trifled with.  You're really going to go places in this organization, I can tell already.
	stopConversation = "false",
	options = {
		{"@conversation/corellia_privateer_trainer:s_95d0a1f6", "an_assignment_13"}, -- An assignment?
		{"@conversation/corellia_privateer_trainer:s_bdd269be", "what_ship_14"}, -- What ship?
		{"@conversation/corellia_privateer_trainer:s_60c4f974", "where_do_i_15"}, -- Where do I go?
		{"@conversation/corellia_privateer_trainer:s_5e4ebfca", "and_when_im_16"}, -- And when I'm done?
		{"@conversation/corellia_privateer_trainer:s_c1ff5062", "im_looking_for_17"}, -- I'm looking for a mission. Do you have any?
		{"@conversation/corellia_privateer_trainer:s_133a724d", "are_you_going_102"}, -- Are you going to train me after this?
		{"@conversation/corellia_privateer_trainer:s_168", "are_you_going_149"}, -- Are you going to train me after this?
		{"@conversation/corellia_privateer_trainer:s_176", "are_you_going_197"}, -- Are you going to train me after this?
		{"@conversation/corellia_privateer_trainer:s_183", "are_you_going_244"}, -- Are you going to train me after this?
	}
}
rhea_convo_template:addScreen(i_love_being_239);

i_love_being_240 = ConvoScreen:new {
	id = "i_love_being_240",
	leftDialog = "@conversation/corellia_privateer_trainer:s_8e1ed7f0", -- Enough of this!  Every time we send you out, you find more pirates.  We need to go straight to the source of the problem:  Their leader.  I know you're up to this:  Go find the pirate's leader and take him out.  Let the rest of them go to the outer rim if they want easy prey.
	stopConversation = "false",
	options = {
		{"@conversation/corellia_privateer_trainer:s_95d0a1f6", "an_assignment_13"}, -- An assignment?
		{"@conversation/corellia_privateer_trainer:s_bdd269be", "what_ship_14"}, -- What ship?
		{"@conversation/corellia_privateer_trainer:s_60c4f974", "where_do_i_15"}, -- Where do I go?
		{"@conversation/corellia_privateer_trainer:s_5e4ebfca", "and_when_im_16"}, -- And when I'm done?
		{"@conversation/corellia_privateer_trainer:s_c1ff5062", "im_looking_for_17"}, -- I'm looking for a mission. Do you have any?
		{"@conversation/corellia_privateer_trainer:s_133a724d", "are_you_going_102"}, -- Are you going to train me after this?
		{"@conversation/corellia_privateer_trainer:s_168", "are_you_going_149"}, -- Are you going to train me after this?
		{"@conversation/corellia_privateer_trainer:s_176", "are_you_going_197"}, -- Are you going to train me after this?
		{"@conversation/corellia_privateer_trainer:s_183", "are_you_going_244"}, -- Are you going to train me after this?
	}
}
rhea_convo_template:addScreen(i_love_being_240);

i_love_being_241 = ConvoScreen:new {
	id = "i_love_being_241",
	leftDialog = "@conversation/corellia_privateer_trainer:s_5e6c7400", -- You are definitely ready to move up.  So I'll tell you what. I'll teach you about basic fighters.
	stopConversation = "false",
	options = {
		{"@conversation/corellia_privateer_trainer:s_95d0a1f6", "an_assignment_13"}, -- An assignment?
		{"@conversation/corellia_privateer_trainer:s_bdd269be", "what_ship_14"}, -- What ship?
		{"@conversation/corellia_privateer_trainer:s_60c4f974", "where_do_i_15"}, -- Where do I go?
		{"@conversation/corellia_privateer_trainer:s_5e4ebfca", "and_when_im_16"}, -- And when I'm done?
		{"@conversation/corellia_privateer_trainer:s_c1ff5062", "im_looking_for_17"}, -- I'm looking for a mission. Do you have any?
		{"@conversation/corellia_privateer_trainer:s_133a724d", "are_you_going_102"}, -- Are you going to train me after this?
		{"@conversation/corellia_privateer_trainer:s_168", "are_you_going_149"}, -- Are you going to train me after this?
		{"@conversation/corellia_privateer_trainer:s_176", "are_you_going_197"}, -- Are you going to train me after this?
		{"@conversation/corellia_privateer_trainer:s_183", "are_you_going_244"}, -- Are you going to train me after this?
		{"@conversation/corellia_privateer_trainer:s_c06c7aa9", "that_sounds_great"}, -- That sounds great.
	}
}
rhea_convo_template:addScreen(i_love_being_241);

i_love_being_242 = ConvoScreen:new {
	id = "i_love_being_242",
	leftDialog = "@conversation/corellia_privateer_trainer:s_46ea46ad", -- We're quite satisfied with your level of performance.  I think it's time you learned a bit more, though.
	stopConversation = "false",
	options = {
		{"@conversation/corellia_privateer_trainer:s_95d0a1f6", "an_assignment_13"}, -- An assignment?
		{"@conversation/corellia_privateer_trainer:s_bdd269be", "what_ship_14"}, -- What ship?
		{"@conversation/corellia_privateer_trainer:s_60c4f974", "where_do_i_15"}, -- Where do I go?
		{"@conversation/corellia_privateer_trainer:s_5e4ebfca", "and_when_im_16"}, -- And when I'm done?
		{"@conversation/corellia_privateer_trainer:s_c1ff5062", "im_looking_for_17"}, -- I'm looking for a mission. Do you have any?
		{"@conversation/corellia_privateer_trainer:s_133a724d", "are_you_going_102"}, -- Are you going to train me after this?
		{"@conversation/corellia_privateer_trainer:s_168", "are_you_going_149"}, -- Are you going to train me after this?
		{"@conversation/corellia_privateer_trainer:s_176", "are_you_going_197"}, -- Are you going to train me after this?
		{"@conversation/corellia_privateer_trainer:s_183", "are_you_going_244"}, -- Are you going to train me after this?
		{"@conversation/corellia_privateer_trainer:s_c06c7aa9", "that_sounds_great"}, -- That sounds great.
		{"@conversation/corellia_privateer_trainer:s_229", "i_agree_247"}, -- I agree.
	}
}
rhea_convo_template:addScreen(i_love_being_242);

i_love_being_243 = ConvoScreen:new {
	id = "i_love_being_243",
	leftDialog = "@conversation/corellia_privateer_trainer:s_a48c20c8", -- What's on your mind, officer? Thinking about performing some duty missions?
	stopConversation = "false",
	options = {
		{"@conversation/corellia_privateer_trainer:s_95d0a1f6", "an_assignment_13"}, -- An assignment?
		{"@conversation/corellia_privateer_trainer:s_bdd269be", "what_ship_14"}, -- What ship?
		{"@conversation/corellia_privateer_trainer:s_60c4f974", "where_do_i_15"}, -- Where do I go?
		{"@conversation/corellia_privateer_trainer:s_5e4ebfca", "and_when_im_16"}, -- And when I'm done?
		{"@conversation/corellia_privateer_trainer:s_c1ff5062", "im_looking_for_17"}, -- I'm looking for a mission. Do you have any?
		{"@conversation/corellia_privateer_trainer:s_133a724d", "are_you_going_102"}, -- Are you going to train me after this?
		{"@conversation/corellia_privateer_trainer:s_168", "are_you_going_149"}, -- Are you going to train me after this?
		{"@conversation/corellia_privateer_trainer:s_176", "are_you_going_197"}, -- Are you going to train me after this?
		{"@conversation/corellia_privateer_trainer:s_183", "are_you_going_244"}, -- Are you going to train me after this?
		{"@conversation/corellia_privateer_trainer:s_c06c7aa9", "that_sounds_great"}, -- That sounds great.
		{"@conversation/corellia_privateer_trainer:s_229", "i_agree_247"}, -- I agree.
		{"@conversation/corellia_privateer_trainer:s_6106187c", "what_is_a_260"}, -- What is a duty mission?
		{"@conversation/corellia_privateer_trainer:s_1a7f1a1b", "yes_i_am_261"}, -- Yes I am. What duty missions are available?
		{"@conversation/corellia_privateer_trainer:s_6276c98", "no_but_how_262"}, -- No, but how about some training?
		{"@conversation/corellia_privateer_trainer:s_2883b989", "not_right_now_263"}, -- Not right now, thanks.
	}
}
rhea_convo_template:addScreen(i_love_being_243);

are_you_going_244 = ConvoScreen:new {
	id = "are_you_going_244",
	leftDialog = "@conversation/corellia_privateer_trainer:s_28435d2", -- Tell you what, %NU.  Kill that pirate leader and YES, I will train you.
	stopConversation = "true",
	options = {}
}
rhea_convo_template:addScreen(are_you_going_244);

that_sounds_great = ConvoScreen:new {
	id = "that_sounds_great",
	leftDialog = "@conversation/corellia_privateer_trainer:s_db7653ed", -- Excellent.  Review this information regarding your new skills, and report back to me when you're ready for another assignment.
	stopConversation = "true",
	options = {}
}
rhea_convo_template:addScreen(that_sounds_great);

i_agree = ConvoScreen:new {
	id = "i_agree",
	leftDialog = "@conversation/corellia_privateer_trainer:s_230", -- Today we'll be learning about basic starfighters. How does that sound?
	stopConversation = "false",
	options = {}
}
rhea_convo_template:addScreen(i_agree);

i_agree_245 = ConvoScreen:new {
	id = "i_agree_245",
	leftDialog = "@conversation/corellia_privateer_trainer:s_231", -- Today we'll be learning about basic starship component use. How does that sound?
	stopConversation = "false",
	options = {}
}
rhea_convo_template:addScreen(i_agree_245);

i_agree_246 = ConvoScreen:new {
	id = "i_agree_246",
	leftDialog = "@conversation/corellia_privateer_trainer:s_232", -- Today we'll be learning about basic starfighter pilot training. How does that sound?
	stopConversation = "false",
	options = {}
}
rhea_convo_template:addScreen(i_agree_246);

i_agree_247 = ConvoScreen:new {
	id = "i_agree_247",
	leftDialog = "@conversation/corellia_privateer_trainer:s_233", -- Today we'll be learning about droid interface basics. How does that sound?
	stopConversation = "false",
	options = {
		{"@conversation/corellia_privateer_trainer:s_247", "that_sounds_great_251"}, -- That sounds great.
	}
}
rhea_convo_template:addScreen(i_agree_247);

that_sounds_great_248 = ConvoScreen:new {
	id = "that_sounds_great_248",
	leftDialog = "@conversation/corellia_privateer_trainer:s_237", -- Excellent.  Review this information regarding your new skills, and report back to me when you're ready for another assignment.
	stopConversation = "true",
	options = {}
}
rhea_convo_template:addScreen(that_sounds_great_248);

that_sounds_great_249 = ConvoScreen:new {
	id = "that_sounds_great_249",
	leftDialog = "@conversation/corellia_privateer_trainer:s_241", -- Excellent.  Review this information regarding your new skills, and report back to me when you're ready for another assignment.
	stopConversation = "true",
	options = {}
}
rhea_convo_template:addScreen(that_sounds_great_249);

that_sounds_great_250 = ConvoScreen:new {
	id = "that_sounds_great_250",
	leftDialog = "@conversation/corellia_privateer_trainer:s_245", -- Excellent.  Review this information regarding your new skills, and report back to me when you're ready for another assignment.
	stopConversation = "true",
	options = {}
}
rhea_convo_template:addScreen(that_sounds_great_250);

that_sounds_great_251 = ConvoScreen:new {
	id = "that_sounds_great_251",
	leftDialog = "@conversation/corellia_privateer_trainer:s_249", -- Excellent.  Review this information regarding your new skills, and report back to me when you're ready for another assignment.
	stopConversation = "true",
	options = {}
}
rhea_convo_template:addScreen(that_sounds_great_251);

what_is_a_252 = ConvoScreen:new {
	id = "what_is_a_252",
	leftDialog = "@conversation/corellia_privateer_trainer:s_d43b2932", -- Duty missions are a good way for you to get experience as a pilot. Only experienced pilots can receive the proper training to learn new skills and abilities.There's no real final objective so you can end the mission whenever you want. So, would you like to take a duty mission?
	stopConversation = "false",
	options = {
		{"@conversation/corellia_privateer_trainer:s_6106187c", "what_is_a_260"}, -- What is a duty mission?
		{"@conversation/corellia_privateer_trainer:s_1a7f1a1b", "yes_i_am_261"}, -- Yes I am. What duty missions are available?
		{"@conversation/corellia_privateer_trainer:s_6276c98", "no_but_how_262"}, -- No, but how about some training?
		{"@conversation/corellia_privateer_trainer:s_2883b989", "not_right_now_263"}, -- Not right now, thanks.
	}
}
rhea_convo_template:addScreen(what_is_a_252);

yes_i_am_253 = ConvoScreen:new {
	id = "yes_i_am_253",
	leftDialog = "@conversation/corellia_privateer_trainer:s_d6a6a9fc", -- Well, merchant freighters are always in need of escorts, or if you like you can help in the fight against the pirate leaders. What interests you?
	stopConversation = "false",
	options = {
		{"@conversation/corellia_privateer_trainer:s_9e417b37", "the_pirate_leaders"}, -- The Pirate Leaders
		{"@conversation/corellia_privateer_trainer:s_221daf73", "escorting_merchants"}, -- Escorting Merchants
		{"@conversation/corellia_privateer_trainer:s_c35e70d2", "nothing_right_now"}, -- Nothing right now.
	}
}
rhea_convo_template:addScreen(yes_i_am_253);

no_but_how_254 = ConvoScreen:new {
	id = "no_but_how_254",
	leftDialog = "@conversation/corellia_privateer_trainer:s_e5c453e0", -- You're not ready for more training yet. But duty missions are a good way of getting good experience so that you'll be ready for training soon. What do you say? Are you ready to try a duty mission?
	stopConversation = "false",
	options = {
		{"@conversation/corellia_privateer_trainer:s_6106187c", "what_is_a_260"}, -- What is a duty mission?
		{"@conversation/corellia_privateer_trainer:s_1a7f1a1b", "yes_i_am_261"}, -- Yes I am. What duty missions are available?
		{"@conversation/corellia_privateer_trainer:s_6276c98", "no_but_how_262"}, -- No, but how about some training?
		{"@conversation/corellia_privateer_trainer:s_2883b989", "not_right_now_263"}, -- Not right now, thanks.
	}
}
rhea_convo_template:addScreen(no_but_how_254);

not_right_now_255 = ConvoScreen:new {
	id = "not_right_now_255",
	leftDialog = "@conversation/corellia_privateer_trainer:s_228", -- Maybe next time then.
	stopConversation = "true",
	options = {}
}
rhea_convo_template:addScreen(not_right_now_255);

what_is_a_256 = ConvoScreen:new {
	id = "what_is_a_256",
	leftDialog = "@conversation/corellia_privateer_trainer:s_d43b2932", -- Duty missions are a good way for you to get experience as a pilot. Only experienced pilots can receive the proper training to learn new skills and abilities.There's no real final objective so you can end the mission whenever you want. So, would you like to take a duty mission?
	stopConversation = "false",
	options = {
		{"@conversation/corellia_privateer_trainer:s_6106187c", "what_is_a_260"}, -- What is a duty mission?
		{"@conversation/corellia_privateer_trainer:s_1a7f1a1b", "yes_i_am_261"}, -- Yes I am. What duty missions are available?
		{"@conversation/corellia_privateer_trainer:s_6276c98", "no_but_how_262"}, -- No, but how about some training?
		{"@conversation/corellia_privateer_trainer:s_2883b989", "not_right_now_263"}, -- Not right now, thanks.
	}
}
rhea_convo_template:addScreen(what_is_a_256);

yes_i_am_257 = ConvoScreen:new {
	id = "yes_i_am_257",
	leftDialog = "@conversation/corellia_privateer_trainer:s_d6a6a9fc", -- Well, merchant freighters are always in need of escorts, or if you like you can help in the fight against the pirate leaders. What interests you?
	stopConversation = "false",
	options = {
		{"@conversation/corellia_privateer_trainer:s_9e417b37", "the_pirate_leaders"}, -- The Pirate Leaders
		{"@conversation/corellia_privateer_trainer:s_221daf73", "escorting_merchants"}, -- Escorting Merchants
		{"@conversation/corellia_privateer_trainer:s_c35e70d2", "nothing_right_now"}, -- Nothing right now.
	}
}
rhea_convo_template:addScreen(yes_i_am_257);

no_but_how_258 = ConvoScreen:new {
	id = "no_but_how_258",
	leftDialog = "@conversation/corellia_privateer_trainer:s_e5c453e0", -- You're not ready for more training yet. But duty missions are a good way of getting good experience so that you'll be ready for training soon. What do you say? Are you ready to try a duty mission?
	stopConversation = "false",
	options = {
		{"@conversation/corellia_privateer_trainer:s_6106187c", "what_is_a_260"}, -- What is a duty mission?
		{"@conversation/corellia_privateer_trainer:s_1a7f1a1b", "yes_i_am_261"}, -- Yes I am. What duty missions are available?
		{"@conversation/corellia_privateer_trainer:s_6276c98", "no_but_how_262"}, -- No, but how about some training?
		{"@conversation/corellia_privateer_trainer:s_2883b989", "not_right_now_263"}, -- Not right now, thanks.
	}
}
rhea_convo_template:addScreen(no_but_how_258);

not_right_now_259 = ConvoScreen:new {
	id = "not_right_now_259",
	leftDialog = "@conversation/corellia_privateer_trainer:s_228", -- Maybe next time then.
	stopConversation = "true",
	options = {}
}
rhea_convo_template:addScreen(not_right_now_259);

the_pirate_leaders = ConvoScreen:new {
	id = "the_pirate_leaders",
	leftDialog = "@conversation/corellia_privateer_trainer:s_cebaf0db", -- You're right.  No sooner do we eliminate one leader than another shows up.  Take out the Corellian Space Pirates!
	stopConversation = "true",
	options = {}
}
rhea_convo_template:addScreen(the_pirate_leaders);

escorting_merchants = ConvoScreen:new {
	id = "escorting_merchants",
	leftDialog = "@conversation/corellia_privateer_trainer:s_3f62bf0", -- Right, those merchants rely on us to provide them with safe passage through the Corellia system.  Just keep escorting them through.
	stopConversation = "true",
	options = {}
}
rhea_convo_template:addScreen(escorting_merchants);

nothing_right_now = ConvoScreen:new {
	id = "nothing_right_now",
	leftDialog = "@conversation/corellia_privateer_trainer:s_27d40413", -- Maybe next time then.
	stopConversation = "true",
	options = {}
}
rhea_convo_template:addScreen(nothing_right_now);

what_is_a_260 = ConvoScreen:new {
	id = "what_is_a_260",
	leftDialog = "@conversation/corellia_privateer_trainer:s_d43b2932", -- Duty missions are a good way for you to get experience as a pilot. Only experienced pilots can receive the proper training to learn new skills and abilities.There's no real final objective so you can end the mission whenever you want. So, would you like to take a duty mission?
	stopConversation = "false",
	options = {
		{"@conversation/corellia_privateer_trainer:s_6106187c", "what_is_a_260"}, -- What is a duty mission?
		{"@conversation/corellia_privateer_trainer:s_1a7f1a1b", "yes_i_am_261"}, -- Yes I am. What duty missions are available?
		{"@conversation/corellia_privateer_trainer:s_6276c98", "no_but_how_262"}, -- No, but how about some training?
		{"@conversation/corellia_privateer_trainer:s_2883b989", "not_right_now_263"}, -- Not right now, thanks.
	}
}
rhea_convo_template:addScreen(what_is_a_260);

yes_i_am_261 = ConvoScreen:new {
	id = "yes_i_am_261",
	leftDialog = "@conversation/corellia_privateer_trainer:s_d6a6a9fc", -- Well, merchant freighters are always in need of escorts, or if you like you can help in the fight against the pirate leaders. What interests you?
	stopConversation = "false",
	options = {
		{"@conversation/corellia_privateer_trainer:s_9e417b37", "the_pirate_leaders"}, -- The Pirate Leaders
		{"@conversation/corellia_privateer_trainer:s_221daf73", "escorting_merchants"}, -- Escorting Merchants
		{"@conversation/corellia_privateer_trainer:s_c35e70d2", "nothing_right_now"}, -- Nothing right now.
	}
}
rhea_convo_template:addScreen(yes_i_am_261);

no_but_how_262 = ConvoScreen:new {
	id = "no_but_how_262",
	leftDialog = "@conversation/corellia_privateer_trainer:s_e5c453e0", -- You're not ready for more training yet. But duty missions are a good way of getting good experience so that you'll be ready for training soon. What do you say? Are you ready to try a duty mission?
	stopConversation = "false",
	options = {
		{"@conversation/corellia_privateer_trainer:s_6106187c", "what_is_a_260"}, -- What is a duty mission?
		{"@conversation/corellia_privateer_trainer:s_1a7f1a1b", "yes_i_am_261"}, -- Yes I am. What duty missions are available?
		{"@conversation/corellia_privateer_trainer:s_6276c98", "no_but_how_262"}, -- No, but how about some training?
		{"@conversation/corellia_privateer_trainer:s_2883b989", "not_right_now_263"}, -- Not right now, thanks.
	}
}
rhea_convo_template:addScreen(no_but_how_262);

not_right_now_263 = ConvoScreen:new {
	id = "not_right_now_263",
	leftDialog = "@conversation/corellia_privateer_trainer:s_228", -- Maybe next time then.
	stopConversation = "true",
	options = {}
}
rhea_convo_template:addScreen(not_right_now_263);

addConversationTemplate("rhea_convo_template", rhea_convo_template);
