corvetteYondallaConvoTemplate = ConvoTemplate:new {
	initialScreen = "",
	templateType = "Lua",
	luaClassHandler = "ticketGiverYondallaConvoHandler",
	screens = {}
}

no_business = ConvoScreen:new {
	id = "no_business",
	leftDialog = "@conversation/corvette_yondalla_neutral_rescue:s_14b16106", -- [She doesn't seem to notice you.] The fool had to go and land himself in the custody of the Corellian Security Force... this is not good. Jabba must learn of this... but I'd really rather not have to tell him myself. Being the target of his anger is not one of my ambitions. Ah what to do...
	stopConversation = "true",
	options = {}
}

corvetteYondallaConvoTemplate:addScreen(no_business);

already_busy = ConvoScreen:new {
	id = "already_busy",
	leftDialog = "@conversation/corvette_yondalla_neutral_rescue:s_310d2ff3", -- Something's come up. I can see that you're busy now, but come talk to me when you finish with that. I could use your help.
	stopConversation = "true",
	options = {}
}

corvetteYondallaConvoTemplate:addScreen(already_busy);

start = ConvoScreen:new {
	id = "start",
	leftDialog = "@conversation/corvette_yondalla_neutral_rescue:s_f5664125", -- About time you got here. You're the ones Jabba sent, right?
	stopConversation = "false",
	options = {
		{"@conversation/corvette_yondalla_neutral_rescue:s_dfb8d44e","hutt_has_problem"}, --  Well, no. But maybe I can help anyway.	
		{"@conversation/corvette_yondalla_neutral_rescue:s_259d132f","you_could_leave"} -- Sorry, no, not me.
	}
}

corvetteYondallaConvoTemplate:addScreen(start);

you_could_leave = ConvoScreen:new {
	id = "you_could_leave",
	leftDialog = "@conversation/corvette_yondalla_neutral_rescue:s_839794f9", -- Argh, solving this by myself is going to take forever!
	stopConversation = "true",
	options = {}
}

corvetteYondallaConvoTemplate:addScreen(you_could_leave);

prefer_tatooine = ConvoScreen:new {
	id = "prefer_tatooine",
	leftDialog = "@conversation/corvette_yondalla_neutral_rescue:s_fa7bc000", -- Bah! Consider yourself fortunate that I haven't time to report your insolence to Jabba!
	stopConversation = "true",
	options = {}
}

corvetteYondallaConvoTemplate:addScreen(prefer_tatooine);


hutt_has_problem = ConvoScreen:new {
	id = "hutt_has_problem",
	leftDialog = "@conversation/corvette_yondalla_neutral_rescue:s_2bdf5b50", -- Yeah okay. Normally I don't need help, but this may be a special case. One of Jabba's top assassins was captured. He's currently on a CorSec corvette and on his way to being traded to the Empire at the Imperial Prison on Dathomir in exchange for the release of an imprisoned CorSec officer. Jabba does not want him talking to Imperial officers. He could reveal too much. We must find the location of that corvette and intercept it. I have three leads on how to do that.
	stopConversation = "false",
	options = {
		{"@conversation/corvette_yondalla_neutral_rescue:s_f9acd930","first_lead"}, --Okay what's the first lead?
		{"@conversation/corvette_yondalla_neutral_rescue:s_fa7b5bf6","second_lead"}, -- And the second?
		{"@conversation/corvette_yondalla_neutral_rescue:s_7837378f","third_lead"}, --Right, and the third lead?
		{"@conversation/corvette_yondalla_neutral_rescue:s_f7147ad","go_get_intel"},-- Alright, I'll try and find the right papers. 
		{"@conversation/corvette_yondalla_neutral_rescue:s_3dfd3c32","prefer_tatooine"} --I prefer to stay here on Tatooine, sorry. 
	}
}

corvetteYondallaConvoTemplate:addScreen(hutt_has_problem);


which_planet = ConvoScreen:new {
	id = "which_planet",
	leftDialog = "@conversation/corvette_yondalla_neutral_rescue:s_f9bdde1d", -- Bah! Fine. Talus, Naboo, or Lok... which planet, yes?
	stopConversation = "false",
	options = {
		{"@conversation/corvette_yondalla_neutral_rescue:s_f9acd930","first_lead"}, --Okay what's the first lead?
		{"@conversation/corvette_yondalla_neutral_rescue:s_fa7b5bf6","second_lead"}, -- And the second?
		{"@conversation/corvette_yondalla_neutral_rescue:s_7837378f","third_lead"}, --Right, and the third lead?
	}
}

corvetteYondallaConvoTemplate:addScreen(which_planet);

first_lead = ConvoScreen:new {
	id = "first_lead",
	leftDialog = "@conversation/corvette_yondalla_neutral_rescue:s_fd1dd7d9", --A former Imperial scientist was working in a bio-genetics lab on Talus. He was in charge of genetic experiments aiming to transform the goat-like murra from Corellia into an efficient all-terrain fighting animal. The resulting creature was named a kahmurra, though the Empire considered it a failure and cancelled all funding. This scientist was a target of our assassin, and the bio-genetics laboratory is where the assassin was captured. Search it for any information left behind.
	stopConversation = "false",
	options = {
		{"@conversation/corvette_yondalla_neutral_rescue:s_f9acd930","first_lead"}, --Okay what's the first lead?
		{"@conversation/corvette_yondalla_neutral_rescue:s_fa7b5bf6","second_lead"}, -- And the second?
		{"@conversation/corvette_yondalla_neutral_rescue:s_7837378f","third_lead"}, --Right, and the third lead?
		{"@conversation/corvette_yondalla_neutral_rescue:s_f7147ad","go_get_intel"},-- Alright, I'll try and find the right papers. 
		{"@conversation/corvette_yondalla_neutral_rescue:s_3dfd3c32","prefer_tatooine"} --I prefer to stay here on Tatooine, sorry. 
	}
}

corvetteYondallaConvoTemplate:addScreen(first_lead);

second_lead = ConvoScreen:new {
	id = "second_lead",
	leftDialog = "@conversation/corvette_yondalla_neutral_rescue:s_d0344ca8", --A small-time gang of thieves, the Cobral. Their hideout can be found on Rori. Unfortunately, I have little information to give you about them. Search their hideout and find any data connected to the exchange of Jabba's assassin into Imperial hands.
	stopConversation = "false",
	options = {
		{"@conversation/corvette_yondalla_neutral_rescue:s_f9acd930","first_lead"}, --Okay what's the first lead?
		{"@conversation/corvette_yondalla_neutral_rescue:s_fa7b5bf6","second_lead"}, -- And the second?
		{"@conversation/corvette_yondalla_neutral_rescue:s_7837378f","third_lead"}, --Right, and the third lead?
		{"@conversation/corvette_yondalla_neutral_rescue:s_f7147ad","go_get_intel"},-- Alright, I'll try and find the right papers. 
		{"@conversation/corvette_yondalla_neutral_rescue:s_3dfd3c32","prefer_tatooine"} --I prefer to stay here on Tatooine, sorry. 
	}
}

corvetteYondallaConvoTemplate:addScreen(second_lead);

third_lead = ConvoScreen:new {
	id = "third_lead",
	leftDialog = "@conversation/corvette_yondalla_neutral_rescue:s_7952bf9c",--This is the tricky one. What I need may actually be found on Endor. A group of Rebels stole some information from a sliced CorSec transmission and fled to Endor with it. I've heard rumors that these Rebels have some connection with the Korgas on Endor.
	stopConversation = "false",
	options = {
		{"@conversation/corvette_yondalla_neutral_rescue:s_f9acd930","first_lead"}, --Okay what's the first lead?
		{"@conversation/corvette_yondalla_neutral_rescue:s_fa7b5bf6","second_lead"}, -- And the second?
		{"@conversation/corvette_yondalla_neutral_rescue:s_7837378f","third_lead"}, --Right, and the third lead?
		{"@conversation/corvette_yondalla_neutral_rescue:s_f7147ad","go_get_intel"},-- Alright, I'll try and find the right papers. 
		{"@conversation/corvette_yondalla_neutral_rescue:s_3dfd3c32","prefer_tatooine"} --I prefer to stay here on Tatooine, sorry. 
	}
}

corvetteYondallaConvoTemplate:addScreen(third_lead);

go_get_intel = ConvoScreen:new {
	id = "go_get_intel",
	leftDialog = "@conversation/corvette_yondalla_neutral_rescue:s_541c41dc", -- Excellent. Make haste and don't disappoint me. Return with one of the documents, or all three at once. It's up to you, as long as you do it fast.
	stopConversation = "true",
	options = {}
}

corvetteYondallaConvoTemplate:addScreen(go_get_intel);

back_already = ConvoScreen:new {
	id = "back_already",
	leftDialog = "@conversation/corvette_yondalla_neutral_rescue:s_e248445b", -- What's your progress?
	stopConversation = "false",
	options = {
		{"@conversation/corvette_yondalla_neutral_rescue:s_aa693144","has_intel"}, -- I have retrieved some documents.
		{"@conversation/corvette_yondalla_neutral_rescue:s_51573633","which_planet"}, -- Could you repeat the three leads on how to find the captured assassin?
		{"@conversation/corvette_yondalla_neutral_rescue:s_ec881702","reset"} -- I cannot continue. Erase my progress from your records.
	}
}

corvetteYondallaConvoTemplate:addScreen(back_already);

reset = ConvoScreen:new {
	id = "reset",
	leftDialog = "@conversation/corvette_yondalla_neutral_rescue:s_49b0321c", -- What?! I can't, I have something else on my plate right now. I trusted you with this! If you quit, I'll have to revoke your travel authorization and take all mission documents you've gathered. Not to mention erasing all knowledge of your progress so far. That means starting completely over!
	stopConversation = "false",
	options = {
		{"@conversation/corvette_yondalla_neutral_rescue:s_998ee768","cant_do_this"}, --I'm sorry, I just can't do this right now.
		{"@conversation/corvette_yondalla_neutral_rescue:s_3e2c6672","ill_do_it"} -- Alright, I suppose I owe it to you.
	}
}

corvetteYondallaConvoTemplate:addScreen(reset);

cant_do_this = ConvoScreen:new {
	id = "cant_do_this",
	leftDialog = "@conversation/corvette_yondalla_neutral_rescue:s_54c95fe4", -- I'll be...just get out of here!
	stopConversation = "true",
	options = {}
}

corvetteBruceConvoTemplate:addScreen(cant_do_this);

ill_do_it = ConvoScreen:new {
	id = "ill_do_it",
	leftDialog = "@conversation/corvette_yondalla_neutral_rescue:s_4d118a1d", --Thank you, now hurry please.
	stopConversation = "true",
	options = {}
}

corvetteBruceConvoTemplate:addScreen(ill_do_it);

has_intel = ConvoScreen:new {
	id = "has_intel",
	leftDialog = "@conversation/corvette_yondalla_neutral_rescue:s_7bf4c415", --Good, let me see.
	stopConversation = "false",
	options = {
		{"@conversation/corvette_yondalla_neutral_rescue:s_58879de3","bad_intel_1"}, --What about 'A Galaxy Befuddled by A. Rahringt'?
		{"@conversation/corvette_yondalla_neutral_rescue:s_2a00185a","bad_intel_2"}, --I managed to snatch 'Galactic Phrasebook and Travel Guide'.
		{"@conversation/corvette_yondalla_neutral_rescue:s_a9be41f8","good_intel"}, -- This 'CorSec Prisoner Transfer Document' must be it.
		{"@conversation/corvette_yondalla_neutral_rescue:s_92ca8435","go_to_corvette"}, --Alright Klaatu will assist me in intercepting the corvette?
		{"@conversation/corvette_yondalla_neutral_rescue:s_6919fb6b","now_hurry"} -- Alright, I will get back to finding it.
	}
}

corvetteYondallaConvoTemplate:addScreen(has_intel);

bad_intel_1 = ConvoScreen:new {
	id = "bad_intel_1",
	leftDialog = "@conversation/corvette_yondalla_neutral_rescue:s_c0031bea", -- Could be useful perhaps. I suppose I should reward you for the time it took you to retrieve it. Anything else?
	stopConversation = "false",
	options = {
		{"@conversation/corvette_yondalla_neutral_rescue:s_d27dcffe","other_documents"}, -- I had some other documents I came across.
		{"@conversation/corvette_yondalla_neutral_rescue:s_6919fb6b","now_hurry"} -- Alright, I will get back to finding it.
	}
}

corvetteYondallaConvoTemplate:addScreen(bad_intel_1);

bad_intel_2 = ConvoScreen:new {
	id = "bad_intel_2",
	leftDialog = "@conversation/corvette_yondalla_neutral_rescue:s_b82fdb5a", -- I'll have a look at it later. Here is some credits for your time in retrieving it.
	stopConversation = "false",
	options = {
		{"@conversation/corvette_yondalla_neutral_rescue:s_d27dcffe","other_documents"}, -- I had some other documents I came across.
		{"@conversation/corvette_yondalla_neutral_rescue:s_6919fb6b","now_hurry"} -- Alright, I will get back to finding it.
	}
}

corvetteYondallaConvoTemplate:addScreen(bad_intel_2);

now_hurry = ConvoScreen:new {
	id = "now_hurry",
	leftDialog = "@conversation/corvette_yondalla_neutral_rescue:s_fdc18de4", -- Yes, check the other places and hurry.
	stopConversation = "true",
	options = {}
}

corvetteYondallaConvoTemplate:addScreen(now_hurry);

other_documents = ConvoScreen:new {
	id = "other_documents",
	leftDialog = "@conversation/corvette_yondalla_neutral_rescue:s_c2bb14db", -- Oh, let me have a look at them.
	stopConversation = "false",
	options = {
		{"@conversation/corvette_yondalla_neutral_rescue:s_a9be41f8","good_intel"}, -- This 'CorSec Prisoner Transfer Document' must be it.
		{"@conversation/corvette_yondalla_neutral_rescue:s_58879de3","bad_intel_1"}, -- What about 'A Galaxy Befuddled by A. Rahringt'?
		{"@conversation/corvette_yondalla_neutral_rescue:s_2a00185a","bad_intel_2"}, -- I managed to snatch 'Galactic Phrasebook and Travel Guide'.
		{"@conversation/corvette_yondalla_neutral_rescue:s_92ca8435","go_to_corvette"}, --Alright Klaatu will assist me in intercepting the corvette?
		{"@conversation/corvette_yondalla_neutral_rescue:s_6919fb6b","now_hurry"} -- Alright, I will get back to finding it.
	}
}

corvetteYondallaConvoTemplate:addScreen(other_documents);

good_intel = ConvoScreen:new {
	id = "good_intel",
	leftDialog = "@conversation/corvette_yondalla_neutral_rescue:s_562787e1", -- Fantastic! According to this, the transport would not yet be on Dathomir. It's still possible to intercept it. Take this travel authorization to Klaatu. He's behind Jabba's Palace... out back with the small shuttlecraft that makes periodic deliveries. Klaatu'll make the necessary arrangements. Then once you're successfully completed your mission, come back to me for your reward.
	stopConversation = "false",
	options = {
		{"@conversation/corvette_yondalla_neutral_rescue:s_a9be41f8","good_intel"}, -- This 'CorSec Prisoner Transfer Document' must be it.
		{"@conversation/corvette_yondalla_neutral_rescue:s_58879de3","bad_intel_1"}, -- What about 'A Galaxy Befuddled by A. Rahringt'?
		{"@conversation/corvette_yondalla_neutral_rescue:s_2a00185a","bad_intel_2"}, -- I managed to snatch 'Galactic Phrasebook and Travel Guide'.
		{"@conversation/corvette_yondalla_neutral_rescue:s_92ca8435","go_to_corvette"}, --Alright Klaatu will assist me in intercepting the corvette?
		{"@conversation/corvette_yondalla_neutral_rescue:s_6919fb6b","now_hurry"} -- Alright, I will get back to finding it.
	}
}

corvetteYondallaConvoTemplate:addScreen(good_intel);

go_to_corvette = ConvoScreen:new {
	id = "go_to_corvette",
	leftDialog = "@conversation/corvette_yondalla_neutral_rescue:s_86991d8f", -- Yes, just show him that travel authorization. Find the assassin on board and get him out of there. I'm sorry I can't come and assist you, but another matter of great importance has arisen that I must deal with. It never ends, but I couldn't imagine doing anything else. So I can't complain. I can, however, reward you if you succeed. Bear that in mind.
	stopConversation = "true",
	options = {}
}

corvetteYondallaConvoTemplate:addScreen(go_to_corvette);

still_here = ConvoScreen:new {
	id = "still_here",
	leftDialog = "@conversation/corvette_yondalla_neutral_rescue:s_9fe2c46a", -- You still here? Didn't I say that you had to get on that ship fast?
	stopConversation = "false",
	options = {
		{"@conversation/corvette_yondalla_neutral_rescue:s_2972f7c","with_shuttle"}, -- Where was Klaatu again?
		{"@conversation/corvette_yondalla_neutral_rescue:s_5dc4acd","reset"}, -- I've changed my mind. Erase all progress I've made from your records.
		{"@conversation/corvette_yondalla_neutral_rescue:s_4e2be81c","other_documents"}, -- I still have some of the other documents that I found.
	}
}

corvetteYondallaConvoTemplate:addScreen(still_here);

with_shuttle = ConvoScreen:new {
	id = "with_shuttle",
	leftDialog = "@conversation/corvette_yondalla_neutral_rescue:s_3ffc96c6", -- He's outside with the shuttle... back behind this building, Lord Jabba's palace! If you succeed in your mission, return to me for your reward, yes? Now hurry!
	stopConversation = "true",
	options = {}
}

corvetteYondallaConvoTemplate:addScreen(with_shuttle);

reward = ConvoScreen:new {
	id = "reward",
	leftDialog = "@conversation/corvette_yondalla_neutral_rescue:s_b13f163d", -- Well done. The assassin is safely back in Jabba's hands. Well, I suppose it remains to be seen how safe that will be for him. Regardless, you've done your part and done it well. Are you here for your reward?
	stopConversation = "false",
	options = {
		{"@conversation/corvette_yondalla_neutral_rescue:s_9fb0ad73","give_reward"}, -- Yes I am, thank you.
		{"@conversation/corvette_yondalla_neutral_rescue:s_c8d78390","reward_notyet"} --Not yet. I'll come back for it.
	}
}

corvetteYondallaConvoTemplate:addScreen(reward);

reward_notyet = ConvoScreen:new {
	id = "reward_notyet",
	leftDialog = "@conversation/corvette_yondalla_neutral_rescue:s_fe8eb1aa", -- Ah... very well. If that is what you want, come back when you're ready for it.
	stopConversation = "true",
	options = {}
}

corvetteYondallaConvoTemplate:addScreen(reward_notyet);

give_reward = ConvoScreen:new {
	id = "give_reward",
	leftDialog = "@conversation/corvette_yondalla_neutral_rescue:s_7e1ef500", -- No, allow me to thank you. Here is your reward. I hope it serves you well.
	stopConversation = "true",
	options = {}
}

corvetteYondallaConvoTemplate:addScreen(give_reward);

cant_give_reward = ConvoScreen:new {
	id = "cant_give_reward",
	leftDialog = "@conversation/corvette_yondalla_neutral_rescue:s_7604ad47", -- Hmm... you have truly earned your reward, but you do not have room for it in your inventory, yes? Please come back and speak with me after clearing some space, yes?Ah... it would appear that you have no space to carry your reward. I'll have to ask that you make room and then come speak to me again.
	stopConversation = "true",
	options = {}
}

corvetteYondallaConvoTemplate:addScreen(cant_give_reward);

addConversationTemplate("corvetteYondallaConvoTemplate", corvetteYondallaConvoTemplate);

