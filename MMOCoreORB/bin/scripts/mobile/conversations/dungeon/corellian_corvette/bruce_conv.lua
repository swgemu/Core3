corvetteBruceConvoTemplate = ConvoTemplate:new {
	initialScreen = "",
	templateType = "Lua",
	luaClassHandler = "ticketGiverBruceConvoHandler",
	screens = {}
}

no_business = ConvoScreen:new {
	id = "no_business",
	leftDialog = "@conversation/corvette_bruce_neutral_destroy:s_33849d1f", -- Oy, who'd a known that slimeball could run so fast... maybe Jabba can give me some big work and I'll make me money back. Hey, go away... can't you see I've got me own worries.
	stopConversation = "true",
	options = {}
}

corvetteBruceConvoTemplate:addScreen(no_business);

already_busy = ConvoScreen:new {
	id = "already_busy",
	leftDialog = "@conversation/corvette_bruce_neutral_destroy:s_1ffa4e4b", -- Hmmm... I could use yer help, but I can see that ye are already busy. Come back when ye have finished yer current task and maybe we can do business.
	stopConversation = "true",
	options = {}
}

corvetteBruceConvoTemplate:addScreen(already_busy);

start = ConvoScreen:new {
	id = "start",
	leftDialog = "@conversation/corvette_bruce_neutral_destroy:s_f7dab98e", -- G'day! Jabba has me do a most urgent mission and me need yer help! I heard yer name whispered in the palace so me think, dis here fellow wuld be perfect fer dis kinda job.
	stopConversation = "false",
	options = {
		{"@conversation/corvette_bruce_neutral_destroy:s_574dc833","hutt_has_problem"}, -- Me, eh? Well how can I help?
		{"@conversation/corvette_bruce_neutral_destroy:s_b6988a9c","you_could_leave"} -- Sorry, in a rush. Maybe next time.
	}
}

corvetteBruceConvoTemplate:addScreen(start);

you_could_leave = ConvoScreen:new {
	id = "you_could_leave",
	leftDialog = "@conversation/corvette_bruce_neutral_destroy:s_a5cbd64e", -- Durnit! Dis not be good.
	stopConversation = "true",
	options = {}
}

corvetteBruceConvoTemplate:addScreen(you_could_leave);

hutt_has_problem = ConvoScreen:new {
	id = "hutt_has_problem",
	leftDialog = "@conversation/corvette_bruce_neutral_destroy:s_f87d1b5b", -- Well we have us a traitor who gave up important stuff to dem CorSec about Jabba. Dis stuff is, as me speak, being transported on a corvette. We must make dis here ship blow up before it reach its destination.
	stopConversation = "false",
	options = {
		{"@conversation/corvette_bruce_neutral_destroy:s_9dae0fe3","the_plan"} -- So what's the plan?
	}
}

corvetteBruceConvoTemplate:addScreen(hutt_has_problem);

the_plan = ConvoScreen:new {
	id = "the_plan",
	leftDialog = "@conversation/corvette_bruce_neutral_destroy:s_65c58ea3", -- Well dat be the tricky part. Dere be these destruct sequences out dere somewhere but dey could be at any of three locations, me information wus not too specific. Me need ye to find it.
	stopConversation = "false",
	options = {
		{"@conversation/corvette_bruce_neutral_destroy:s_d6cf9803","first_location"}, -- Okay, what's the first possible location?
		{"@conversation/corvette_bruce_neutral_destroy:s_47a242b","second_location"}, -- Alright, what about the second location?
		{"@conversation/corvette_bruce_neutral_destroy:s_7f2cdc","third_location"}, -- Right, what's the third location?
		{"@conversation/corvette_bruce_neutral_destroy:s_65ecd99d","go_get_intel"}, -- Alright, I will try and find the sequence.
		{"@conversation/corvette_bruce_neutral_destroy:s_369d526d","reset"},-- Sorry, this sounds like something I can't do right now.
	}
}

corvetteBruceConvoTemplate:addScreen(the_plan);

first_location = ConvoScreen:new {
	id = "first_location",
	leftDialog = "@conversation/corvette_bruce_neutral_destroy:s_5d72e2a5", -- Well on the planet of Naboo, sum of dem Maulers have been planning a raid against dem CorSec. Jabba think dem may have whut we wunt and haven't used it yet. Dey no wunt to give it up though so go dere and take it from dem. It sure ta be in dem camp sumwhere.
	stopConversation = "false",
	options = {
		{"@conversation/corvette_bruce_neutral_destroy:s_47a242b","second_location"}, -- Alright, what about the second location?
		--{"@conversation/corvette_bruce_neutral_destroy:s_7f2cdc","third_location"}, -- Right, what's the third location?
		{"@conversation/corvette_bruce_neutral_destroy:s_65ecd99d","go_get_intel"},--Alright, I will try and find the sequence.
		{"@conversation/corvette_bruce_neutral_destroy:s_369d526d","reset"},--Sorry, this sounds like something I can't do right now.
	}
}

corvetteBruceConvoTemplate:addScreen(first_location);

second_location = ConvoScreen:new {
	id = "second_location",
	leftDialog = "@conversation/corvette_bruce_neutral_destroy:s_bb218f7b", -- Well Jabba have a strong suspicion dem Rogue CorSec culd have dis here information. Dey after all former employees. Maybe dem stupid CorSec forget to change the sequence.
	stopConversation = "false",
	options = {
		--{"@conversation/corvette_bruce_neutral_destroy:s_d6cf9803","first_location"}, -- Okay, what's the first possible location?
		{"@conversation/corvette_bruce_neutral_destroy:s_7f2cdc","third_location"}, -- Right, what's the third location?
		{"@conversation/corvette_bruce_neutral_destroy:s_65ecd99d","go_get_intel"},--Alright, I will try and find the sequence.
		{"@conversation/corvette_bruce_neutral_destroy:s_369d526d","reset"},--Sorry, this sounds like something I can't do right now.
	}
}

corvetteBruceConvoTemplate:addScreen(second_location);

third_location = ConvoScreen:new {
	id = "third_location",
	leftDialog = "@conversation/corvette_bruce_neutral_destroy:s_7f918abd", -- Well if all else fails, on the dreaded planet of Dathomir, there be dem Nightsisters. Jabba once sent a traitor to one of dem slave camps, since he wus a bit of a womanizer. Wonderful sense of humor he has Jabba. Anyway, the traitor probably dead but he had some information dat may have been wut we want and the Sisters may have it now.
	stopConversation = "false",
	options = {
		--{"@conversation/corvette_bruce_neutral_destroy:s_d6cf9803","first_location"}, -- Okay, what's the first possible location?
		--{"@conversation/corvette_bruce_neutral_destroy:s_47a242b","second_location"}, -- Alright, what about the second location?
		{"@conversation/corvette_bruce_neutral_destroy:s_8bd8c49d","which_planet"}, -- Could you repeat the information on the locations?
		{"@conversation/corvette_bruce_neutral_destroy:s_65ecd99d","go_get_intel"},--Alright, I will try and find the sequence.
		{"@conversation/corvette_bruce_neutral_destroy:s_369d526d","reset"},--Sorry, this sounds like something I can't do right now.
	}
}

corvetteBruceConvoTemplate:addScreen(third_location);


go_get_intel = ConvoScreen:new {
	id = "go_get_intel",
	leftDialog = "@conversation/corvette_bruce_neutral_destroy:s_c58b6642", -- Marvellous! Time is of essence here so if ye wunt, ye can check back after ye found one of the documents to see if dat be it. Or wait until ye have all three, as long as yer fast.
	stopConversation = "true",
	options = {}
}

corvetteBruceConvoTemplate:addScreen(go_get_intel);

back_already = ConvoScreen:new {
	id = "back_already",
	leftDialog = "@conversation/corvette_bruce_neutral_destroy:s_cfec2ce3", -- Ah, yer back! Any luck?
	stopConversation = "false",
	options = {
		{"@conversation/corvette_bruce_neutral_destroy:s_ca5faf1b","has_intel"}, -- I've found some documents that may be it.
		{"@conversation/corvette_bruce_neutral_destroy:s_8bd8c49d","which_planet"}, -- Could you repeat the information on the locations?
		{"@conversation/corvette_bruce_neutral_destroy:s_283ba480","reset2"} -- Sorry, I give up, this is taking too long.
	}
}

corvetteBruceConvoTemplate:addScreen(back_already);

which_planet = ConvoScreen:new {
	id = "which_planet",
	leftDialog = "@conversation/corvette_bruce_neutral_destroy:s_dea1004c", -- Have ye been out drinkin? Okay me go over it again.
	stopConversation = "false",
	options = {
		{"@conversation/corvette_bruce_neutral_destroy:s_d6cf9803","first_location"}, -- Okay, what's the first possible location?
		{"@conversation/corvette_bruce_neutral_destroy:s_47a242b","second_location"}, -- Alright, what about the second location?
		{"@conversation/corvette_bruce_neutral_destroy:s_7f2cdc","third_location"}, -- Right, what's the third location?
		{"@conversation/corvette_bruce_neutral_destroy:s_65ecd99d","go_get_intel"},--Alright, I will try and find the sequence.
		{"@conversation/corvette_bruce_neutral_destroy:s_369d526d","maybe_next_time"},--Sorry, this sounds like something I can't do right now.
	}
}

corvetteBruceConvoTemplate:addScreen(which_planet);



has_intel = ConvoScreen:new {
	id = "has_intel",
	leftDialog = "@conversation/corvette_bruce_neutral_destroy:s_68f1fe27", -- Well fork dem over!
	stopConversation = "false",
	options = {
	{"@conversation/corvette_bruce_neutral_destroy:s_d6cf9803","good_intel"},--Here's a document labeled 'CorSec Destruction Code Sequences'.
	{"@conversation/corvette_bruce_neutral_destroy:s_47a242b","bad_intel_1"},--Not sure about this one, it's 'Bounty Hunter Means and Methods'.
	{"@conversation/corvette_bruce_neutral_destroy:s_7f2cdc","bad_intel_2"},--Maybe this 'The Edict of Jiaan' could be useful?
	{"@conversation/corvette_bruce_neutral_destroy:s_65ecd99d","go_get_intel"},--Alright, I'll take care of it.
	{"@conversation/corvette_bruce_neutral_destroy:s_369d526d","maybe_next_time"},--So I guess I'll have to go and check the other places.
	}
}

corvetteBruceConvoTemplate:addScreen(has_intel);

bad_intel_1 = ConvoScreen:new {
	id = "bad_intel_1",
	leftDialog = "@conversation/corvette_bruce_neutral_destroy:s_c866c945", --  Not sure if dis any useful. I suppose me have to pay ye for yer troubles in getting it though.
	stopConversation = "false",
	options = {
		{"@conversation/corvette_bruce_neutral_destroy:s_3e583623","good_intel"}, --  Here's a document labeled 'CorSec Destruction Code Sequences'.
		{"@conversation/corvette_bruce_neutral_destroy:s_d3f9d91d","bad_intel_1"}, -- Not sure about this one, it's 'Bounty Hunter Means and Methods'.
		{"@conversation/corvette_bruce_neutral_destroy:s_90650308","bad_intel_2"}, --  Maybe this 'The Edict of Jiaan' could be useful?
		{"@conversation/corvette_bruce_neutral_destroy:s_65ecd99d","go_get_intel"},--Alright, I'll take care of it.
		{"@conversation/corvette_bruce_neutral_destroy:s_369d526d","maybe_next_time"},--So I guess I'll have to go and check the other places.
	}
}

corvetteBruceConvoTemplate:addScreen(bad_intel_1);

bad_intel_2 = ConvoScreen:new {
	id = "bad_intel_2",
	leftDialog = "@conversation/corvette_bruce_neutral_destroy:s_269fe8a6", -- Culd be interesting me suppose. Here's some creds fer it.
	stopConversation = "false",
	options = {
		{"@conversation/corvette_bruce_neutral_destroy:s_3bfca8b3","other_documents"}, -- I was wondering if these other documents would be of use?
		{"@conversation/corvette_bruce_neutral_destroy:s_c5ae9239","now_hurry"} -- On my way to check one of the other hideouts.
	}
}

corvetteBruceConvoTemplate:addScreen(bad_intel_2);

now_hurry = ConvoScreen:new {
	id = "now_hurry",
	leftDialog = "@conversation/corvette_bruce_neutral_destroy:s_7a77d96c", --  Yes and hurry, we're running out of time here!
	stopConversation = "true",
	options = {}
}

corvetteBruceConvoTemplate:addScreen(now_hurry);

other_documents = ConvoScreen:new {
	id = "other_documents",
	leftDialog = "@conversation/corvette_bruce_neutral_destroy:s_dcf8e793", -- Let me take a look.
	stopConversation = "false",
	options = {
		{"@conversation/corvette_bruce_neutral_destroy:s_d3f9d91d","bad_intel_1"}, -- Not sure about this one, it's 'Bounty Hunter Means and Methods'.
		{"@conversation/corvette_bruce_neutral_destroy:s_90650308","bad_intel_2"}, --  Maybe this 'The Edict of Jiaan' could be useful?
		{"@conversation/corvette_bruce_neutral_destroy:s_3e583623","good_intel"} --  Here's a document labeled 'CorSec Destruction Code Sequences'.
	}
}

corvetteBruceConvoTemplate:addScreen(other_documents);

good_intel = ConvoScreen:new {
	id = "good_intel",
	leftDialog = "@conversation/corvette_bruce_neutral_destroy:s_3da0d379", -- Fantalistic! Now ye just need to fly up to that corvette and make it go boom! Take dis here travel form and show to Klaatu outside behind the palace. He'll hook ye up! Destroy dat ship den come see me for yer reward!
	stopConversation = "false",
	options = {
	{"@conversation/corvette_bruce_neutral_destroy:s_3e583623","good_intel"}, --  Here's a document labeled 'CorSec Destruction Code Sequences'.
		{"@conversation/corvette_bruce_neutral_destroy:s_d3f9d91d","bad_intel_1"}, -- Not sure about this one, it's 'Bounty Hunter Means and Methods'.
		{"@conversation/corvette_bruce_neutral_destroy:s_90650308","bad_intel_2"}, --  Maybe this 'The Edict of Jiaan' could be useful?
		{"@conversation/corvette_bruce_neutral_destroy:s_77928d48","go_to_corvette"},--Alright, I'll take care of it.
		{"@conversation/corvette_bruce_neutral_destroy:s_369d526d","maybe_next_time"},--So I guess I'll have to go and check the other places.
	}
}

corvetteBruceConvoTemplate:addScreen(good_intel);

go_to_corvette = ConvoScreen:new {
	id = "go_to_corvette",
	leftDialog = "@conversation/corvette_bruce_neutral_destroy:s_adbdb619", -- Great, hurry and good look to ye! Come back if you blow up dat ship and get yer reward. Don't come back if ye fail.
	stopConversation = "true",
	options = {}
}

corvetteBruceConvoTemplate:addScreen(go_to_corvette);

reset2 = ConvoScreen:new {
	id = "reset2",
	leftDialog = "@conversation/corvette_bruce_neutral_destroy:s_ed430e90", -- Didn't take ye fer a quitter, guess I wus wrong. Dis not good news, not at all. I'm gonna take all everything about dis from ye. Ye keep nuthin.
	stopConversation = "true",
	options = { }
}

corvetteBruceConvoTemplate:addScreen(reset2);

still_here = ConvoScreen:new {
	id = "still_here",
	leftDialog = "@conversation/corvette_bruce_neutral_destroy:s_28c81b92", --  Ye haven't left yet? Whut ye still doing here?
	stopConversation = "false",
	options = {
		{"@conversation/corvette_bruce_neutral_destroy:s_2972f7c","with_shuttle"}, -- Where was Klaatu again?
		{"@conversation/corvette_bruce_neutral_destroy:s_dc1051b","disappointed"}, -- Something came up, can't do it right now.
		{"@conversation/corvette_bruce_neutral_destroy:s_3bfca8b3","hasStuff"}, -- I was wondering if these other documents would be of use?
	}
}

corvetteBruceConvoTemplate:addScreen(still_here);

with_shuttle = ConvoScreen:new {
	id = "with_shuttle",
	leftDialog = "@conversation/corvette_bruce_neutral_destroy:s_224ca617", -- He be outside behind the palace! Come talk to me if ye destroy dat ship and get yer reward. Now hurry!
	stopConversation = "true",
	options = {}
}

corvetteBruceConvoTemplate:addScreen(with_shuttle);

disappointed = ConvoScreen:new {
	id = "disappointed",
	leftDialog = "@conversation/corvette_bruce_neutral_destroy:s_21328697", -- Whut the?! Ye giving up now, we almost done! If yer quit, I have ta take everything ye gotten up to dis time from ye.
	stopConversation = "false",
	options = {
		{"@conversation/corvette_bruce_neutral_destroy:s_d036761d","ill_do_it"}, -- Fine, I'll do it.
		{"@conversation/corvette_bruce_neutral_destroy:s_77455336","reset3"}, --Yeah I'm sorry, I can't do this.
	}
}

corvetteBruceConvoTemplate:addScreen(disappointed);

reset3 = ConvoScreen:new {
	id = "reset3",
	leftDialog = "@conversation/corvette_bruce_neutral_destroy:s_d725eac", -- Fine! Get outta here and don't come back, ye here?
	stopConversation = "true",
	options = {}
}

corvetteBruceConvoTemplate:addScreen(reset3);

ill_do_it = ConvoScreen:new {
	id = "ill_do_it",
	leftDialog = "@conversation/corvette_bruce_neutral_destroy:s_20f0bac1", -- Knew ye wuld come around. Now hurry!
	stopConversation = "true",
	options = {}
}

corvetteBruceConvoTemplate:addScreen(ill_do_it);


reward = ConvoScreen:new {
	id = "reward",
	leftDialog = "@conversation/corvette_bruce_neutral_destroy:s_2a75ee0f", -- Yay! Jabba is happy with me... er... I mean ye. Right... ye. Dem CorSec and dat ship be destroyed! Good, good! Want yer reward?
	stopConversation = "false",
	options = {
		{"@conversation/corvette_bruce_neutral_destroy:s_e61c9f7a","give_reward"}, --Yes, I'd like my reward please. I've earned it.
		{"@conversation/corvette_bruce_neutral_destroy:s_a2329c74","reward_notyet"} --Not just yet. I'll come back.
	}
}

corvetteBruceConvoTemplate:addScreen(reward);

reward_notyet = ConvoScreen:new {
	id = "reward_notyet",
	leftDialog = "@conversation/corvette_bruce_neutral_destroy:s_557298a9", -- Not yet? Ye be a strange one. Why not take dis reward sooner rather den later? Stange one.
	stopConversation = "true",
	options = {}
}

corvetteBruceConvoTemplate:addScreen(reward_notyet);

give_reward = ConvoScreen:new {
	id = "give_reward",
	leftDialog = "@conversation/corvette_bruce_neutral_destroy:s_40e26fa7", --Yea. Okay. Dis here be your reward. Ye like?
	stopConversation = "true",
	options = {}
}

corvetteBruceConvoTemplate:addScreen(give_reward);

cant_give_reward = ConvoScreen:new {
	id = "cant_give_reward",
	leftDialog = "@conversation/corvette_bruce_neutral_destroy:s_4af1600f", -- Yea. Only ye no have room to take it. Best that ye make some room and den come back.
	stopConversation = "true",
	options = {}
}

corvetteBruceConvoTemplate:addScreen(cant_give_reward);

addConversationTemplate("corvetteBruceConvoTemplate", corvetteBruceConvoTemplate);

