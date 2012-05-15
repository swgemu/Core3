imperial_retreat_kaja_orzee_convotemplate = ConvoTemplate:new {
	initialScreen = "",
	templateType = "Lua",
	luaClassHandler = "imperial_retreat_kaja_orzee_handler",
	screens = {}
}


npc_1_1 = ConvoScreen:new {
	id = "npc_1_1",
	leftDialog = "@theme_park_imperial/kaja_orzee:npc_1_1", --Greetings, citizen.  I am Kaja Orzee, Administrative Assistant to the Emperor, Himself.  I am assuming you are here so that you may help serve the Empire, am I correct?  We are in need of an armed escort to assist in the transportation of an important official.  Do you wish to serve the Empire in this manner?
	stopConversation = "false",
	options = {
		{"@theme_park_imperial/kaja_orzee:player_1_1","accept_2_1"}, --Yes, I wish to serve the Empire in this capacity.
		{"@theme_park_imperial/kaja_orzee:player_2_1","npc_3_1"}, --No, I do not feel I should be entrusted with this duty.
		{"@theme_park_imperial/kaja_orzee:player_3_1","npc_4_1"} --Why aren't you sending a squad of Stormtroopers to do so?
	}
}


imperial_retreat_kaja_orzee_convotemplate:addScreen(npc_1_1);


accept_2_1 = ConvoScreen:new {
	id = "accept_2_1",
	leftDialog = "@theme_park_imperial/kaja_orzee:npc_2_1", --You will be escorting a Moff of a local system to meet with other officials here within the Emperor's retreat.  You will be expected to treat the Governor with proper respect, and see to it that no harm comes to him during his travel.  You may depart now, for the Governor is waiting.
	stopConversation = "true",
	options = {
	}
}


imperial_retreat_kaja_orzee_convotemplate:addScreen(accept_2_1);


npc_3_1 = ConvoScreen:new {
	id = "npc_3_1",
	leftDialog = "@theme_park_imperial/kaja_orzee:npc_3_1", --*sighs* Very well, then.  We will likely have to send Stormtroopers to escort him, then.  Your enthusiatic loyalty to the Empire will be noted, citizen.  If you don't mind, I have business to attend to now.  Good day.
	stopConversation = "true",
	options = {
	}
}


imperial_retreat_kaja_orzee_convotemplate:addScreen(npc_3_1);


npc_4_1 = ConvoScreen:new {
	id = "npc_4_1",
	leftDialog = "@theme_park_imperial/kaja_orzee:npc_4_1", --Recently, one of the Empire's Moffs has been receiving death threats from an unknown sender.  We are currently investigating the source of these threats - Rebel terrorists, no doubt - but the safety of the Moff's life is in jeopardy at this time.  The less attention to the escort, the safer he will be.
	stopConversation = "false",
	options = {
		{"@theme_park_imperial/kaja_orzee:player_1_1","accept_2_1"}, --Yes, I wish to serve the Empire in this capacity.
		{"@theme_park_imperial/kaja_orzee:player_2_1","npc_3_1"} --No, I do not feel I should be entrusted with this duty.
	}
}


imperial_retreat_kaja_orzee_convotemplate:addScreen(npc_4_1);


npc_1_2 = ConvoScreen:new {
	id = "npc_1_2",
	leftDialog = "@theme_park_imperial/kaja_orzee:npc_1_2", --Greetings again, citizen.  There has been progress made on the threats with the Moff, and the Empire has need of you again.  Imperial sector police have recorded a conversation detailing someone hiring an assassin to murder the Moff.  The Empire needs you to track down this person that paid for the contract and retrieve the evidence.  Will you do so?
	stopConversation = "false",
	options = {
		{"@theme_park_imperial/kaja_orzee:player_1_2","accept_1_2"}, --Yes, I will track him down for the Empire.
		{"@theme_park_imperial/kaja_orzee:player_2_2","npc_3_2"}, --I don't believe I am suited to a task such as that.
		{"@theme_park_imperial/kaja_orzee:player_3_2","npc_4_2"} --Wouldn't you want to track down the assassin first?
	}
}


imperial_retreat_kaja_orzee_convotemplate:addScreen(npc_1_2);


accept_1_2 = ConvoScreen:new {
	id = "accept_1_2",
	leftDialog = "@theme_park_imperial/kaja_orzee:npc_2_2", --Very good, then.  He will probably still have receipts of his payment to the assassin, so detain him so that you can bring him and his records here.  If he does not cooperate, you are authorized to use force if necessary.  Here is the location where our droids have last spotted him.  Please make haste.
	stopConversation = "true",
	options = {
	}
}


imperial_retreat_kaja_orzee_convotemplate:addScreen(accept_1_2);


npc_3_2 = ConvoScreen:new {
	id = "npc_3_2",
	leftDialog = "@theme_park_imperial/kaja_orzee:npc_3_2", --I will have to quickly find someone else, then.  Remember, though, that when you let a Rebel terrorist walk free, you might as well be helping them with their anarchy.
	stopConversation = "true",
	options = {
	}
}


imperial_retreat_kaja_orzee_convotemplate:addScreen(npc_3_2);


npc_4_2 = ConvoScreen:new {
	id = "npc_4_2",
	leftDialog = "@theme_park_imperial/kaja_orzee:npc_4_2", --You are dealing with the Empire here, not some ragtag band of misguided Rebels.  We have already detached a team of sector police to track down the assassin, citizen.  What we need is someone to track down the Rebel sympathizer who placed the contract.  We are hoping you will not scare him away before dealing with him.
	stopConversation = "false",
	options = {
		{"@theme_park_imperial/kaja_orzee:player_1_2","accept_1_2"}, --Yes, I will track him down for the Empire.
		{"@theme_park_imperial/kaja_orzee:player_2_2","npc_3_2"} --I don't believe I am suited to a task such as that.
	}
}


imperial_retreat_kaja_orzee_convotemplate:addScreen(npc_4_2);


npc_1_3 = ConvoScreen:new {
	id = "npc_1_3",
	leftDialog = "@theme_park_imperial/kaja_orzee:npc_1_3", --Oh, it's good you stopped by right now.  We have just been informed that the Sector Police have found the assassin, but they are not equipped to handle someone of his caliber.  Shall I tell them that I will be sending a specialist out there to assist them with his capture?
	stopConversation = "false",
	options = {
		{"@theme_park_imperial/kaja_orzee:player_1_3","accept_1_3"}, --Yes, please let them know that.  I will deal with this assassin myself.
		{"@theme_park_imperial/kaja_orzee:player_2_3","npc_3_3"} --Assassin?  Umm... no thanks.  Leave that to the police, I always say.
	}
}


imperial_retreat_kaja_orzee_convotemplate:addScreen(npc_1_3);


accept_1_3 = ConvoScreen:new {
	id = "accept_1_3",
	leftDialog = "@theme_park_imperial/kaja_orzee:npc_2_3", --I shall inform them immediately - they will be glad to hear you are on your way.  Again, try to get the assassin to give himself up so that we can hand him over to the Emperor's Inquistors.  If he is as recalcitrant as was his partner, you are again authorized to use whatever force is necessary.  Good luck!
	stopConversation = "true",
	options = {
	}
}


imperial_retreat_kaja_orzee_convotemplate:addScreen(accept_1_3);


npc_3_3 = ConvoScreen:new {
	id = "npc_3_3",
	leftDialog = "@theme_park_imperial/kaja_orzee:npc_3_3", --You should be ashamed of yourself!  You can handle something like an assassin, but yet you let these new recruits risk their lives?  This is a Rebel assassin, not some trained bounty hunter.  If you don't do it for the police, at least do it for the Emperor!
	stopConversation = "true",
	options = {
	}
}


imperial_retreat_kaja_orzee_convotemplate:addScreen(npc_3_3);


npc_4_3 = ConvoScreen:new {
	id = "npc_4_3",
	leftDialog = "@theme_park_imperial/kaja_orzee:npc_4_3", --Yes, we do, but we cannot dispatch the Guards.  If we did, who would be there to protect the defenseless Emperor?  You handled the previous situation with such professionalism, that I feel you can handle this with ease.  In addition, this you will be doing your part to scourge this galaxy of another Rebel murderer.
	stopConversation = "false",
	options = {
		{"@theme_park_imperial/kaja_orzee:player_1_3","accept_1_3"}, --Yes, please let them know that.  I will deal with this assassin myself.
		{"@theme_park_imperial/kaja_orzee:player_2_3","npc_3_3"} --Assassin?  Umm... no thanks.  Leave that to the police, I always say.
	}
}


imperial_retreat_kaja_orzee_convotemplate:addScreen(npc_4_3);


npc_reset = ConvoScreen:new {
	id = "npc_reset",
	leftDialog = "@theme_park_imperial/kaja_orzee:npc_reset", --Fine, come back when you are more capable of helping.
	stopConversation = "true",
	options = {
	}
}


imperial_retreat_kaja_orzee_convotemplate:addScreen(npc_reset);


npc_work_1 = ConvoScreen:new {
	id = "npc_work_1",
	leftDialog = "@theme_park_imperial/kaja_orzee:npc_work_1", --Where is the governor?
	stopConversation = "false",
	options = {
		{"@theme_park_imperial/kaja_orzee:player_sorry","npc_backtowork"}, --I'll get right back to work.  Just taking a breather.
		{"@theme_park_imperial/kaja_orzee:player_reset","npc_reset"} --I'm sorry, I can't do this right now.
	}
}


imperial_retreat_kaja_orzee_convotemplate:addScreen(npc_work_1);


npc_work_2 = ConvoScreen:new {
	id = "npc_work_2",
	leftDialog = "@theme_park_imperial/kaja_orzee:npc_work_2", --Yes?
	stopConversation = "false",
	options = {
		{"@theme_park_imperial/kaja_orzee:player_sorry",""}, --I'll get right back to work.  Just taking a breather.
		{"@theme_park_imperial/kaja_orzee:player_reset",""} --I'm sorry, I can't do this right now.
	}
}


imperial_retreat_kaja_orzee_convotemplate:addScreen(npc_work_2);


npc_work_3 = ConvoScreen:new {
	id = "npc_work_3",
	leftDialog = "@theme_park_imperial/kaja_orzee:npc_work_3", --Yes? How can I help you, citizen?
	stopConversation = "false",
	options = {
		{"@theme_park_imperial/kaja_orzee:player_sorry",""}, --I'll get right back to work.  Just taking a breather.
		{"@theme_park_imperial/kaja_orzee:player_reset",""} --I'm sorry, I can't do this right now.
	}
}


imperial_retreat_kaja_orzee_convotemplate:addScreen(npc_work_3);


npc_work_4 = ConvoScreen:new {
	id = "npc_work_4",
	leftDialog = "@theme_park_imperial/kaja_orzee:npc_work_4", --Did you need your assignment explained again, citizen?
	stopConversation = "false",
	options = {
		{"@theme_park_imperial/kaja_orzee:player_sorry",""}, --I'll get right back to work.  Just taking a breather.
		{"@theme_park_imperial/kaja_orzee:player_reset",""} --I'm sorry, I can't do this right now.
	}
}


imperial_retreat_kaja_orzee_convotemplate:addScreen(npc_work_4);


npc_reward_1 = ConvoScreen:new {
	id = "npc_reward_1",
	leftDialog = "@theme_park_imperial/kaja_orzee:npc_reward_1", --A superb job, citizen.  The Moff spoke highly of your efficiency. He did mention that you might be deserving of some compensation for your assistance.
	stopConversation = "true",
	options = {
	}
}


imperial_retreat_kaja_orzee_convotemplate:addScreen(npc_reward_1);


npc_reward_2 = ConvoScreen:new {
	id = "npc_reward_2",
	leftDialog = "@theme_park_imperial/kaja_orzee:npc_reward_2", --It is a shame he wouldn't reason with you.  Then again, not all of them are misguided, I guess - some are just plain evil, and need to be taken care of accordingly.  I hope the Interrogation team can use this information to find his accomplices.  Please accept this compensation for your assistance.
	stopConversation = "true",
	options = {
	}
}


imperial_retreat_kaja_orzee_convotemplate:addScreen(npc_reward_2);


npc_reward_3 = ConvoScreen:new {
	id = "npc_reward_3",
	leftDialog = "@theme_park_imperial/kaja_orzee:npc_reward_3", --Our Inquisitor, will be upset to hear the assassin did not come peacefully.  But it was to be expected.  You cannot trust their kind, I say.  If only they would try to work with the Emperor rather than against him.  Oh, and the Inquisitor would like you to have this compensation. He feels you may have earned it.
	stopConversation = "true",
	options = {
	}
}


imperial_retreat_kaja_orzee_convotemplate:addScreen(npc_reward_3);


npc_reward_5 = ConvoScreen:new {
	id = "npc_reward_5",
	leftDialog = "@theme_park_imperial/kaja_orzee:npc_reward_5", --Wonderful!  You have performed in such an exacting manner, I'm certain the Emperor will want to hear of your achievements.  Good work, citizen!  I shall write you a wonderful letter of recommendation and have it placed in your record.  Have yourself a good day, and may the Emperor live forever!
	stopConversation = "true",
	options = {
	}
}


imperial_retreat_kaja_orzee_convotemplate:addScreen(npc_reward_5);


npc_failure_1 = ConvoScreen:new {
	id = "npc_failure_1",
	leftDialog = "@theme_park_imperial/kaja_orzee:npc_failure_1", --Oh dear... I'm not too sure Lord Vader will be pleased to hear that the Moff is dead.
	stopConversation = "true",
	options = {
	}
}


imperial_retreat_kaja_orzee_convotemplate:addScreen(npc_failure_1);


npc_failure_2 = ConvoScreen:new {
	id = "npc_failure_2",
	leftDialog = "@theme_park_imperial/kaja_orzee:npc_failure_2", --I am sorry to hear that you weren't able to complete this. I guess I'll have to record this on your dossier.
	stopConversation = "true",
	options = {
	}
}


imperial_retreat_kaja_orzee_convotemplate:addScreen(npc_failure_2);


npc_failure_3 = ConvoScreen:new {
	id = "npc_failure_3",
	leftDialog = "@theme_park_imperial/kaja_orzee:npc_failure_3", --Well, this just puts a damper on my day. I do not think Lord Hethrir will be too happy to hear that you have failed in this simple assignment.
	stopConversation = "true",
	options = {
	}
}


imperial_retreat_kaja_orzee_convotemplate:addScreen(npc_failure_3);


npc_failure_4 = ConvoScreen:new {
	id = "npc_failure_4",
	leftDialog = "@theme_park_imperial/kaja_orzee:npc_failure_4", --Hmmm... unfortunately, I will not be able to alter these records to show you in a better light. Perhaps you my be able to learn from this failure.
	stopConversation = "true",
	options = {
	}
}


imperial_retreat_kaja_orzee_convotemplate:addScreen(npc_failure_4);


npc_failure_5 = ConvoScreen:new {
	id = "npc_failure_5",
	leftDialog = "@theme_park_imperial/kaja_orzee:npc_failure_5", --Perhaps I misunderstood you. I believed you said you were able to do this. Were you to have told me that you were that incompetant, I wouldn't have assigned this to you.
	stopConversation = "true",
	options = {
	}
}


imperial_retreat_kaja_orzee_convotemplate:addScreen(npc_failure_5);


npc_done = ConvoScreen:new {
	id = "npc_done",
	leftDialog = "@theme_park_imperial/kaja_orzee:next", --Go and speak to Loam Redge.  Your past work has allowed you access to the main hall.
	stopConversation = "true",
	options = {
	}
}


imperial_retreat_kaja_orzee_convotemplate:addScreen(npc_done);


npc_backtowork = ConvoScreen:new {
	id = "npc_backtowork",
	leftDialog = "@theme_park_imperial/kaja_orzee:npc_backtowork", --Don't take too long, I need that task completed.
	stopConversation = "false",
	options = {
		{"@theme_park_imperial/kaja_orzee:player_sorry",""}, --I'll get right back to work.  Just taking a breather.
		{"@theme_park_imperial/kaja_orzee:player_reset","npc_reset"} --I'm sorry, I can't do this right now.
	}
}


imperial_retreat_kaja_orzee_convotemplate:addScreen(npc_backtowork);


npc_dontknowyou_1 = ConvoScreen:new {
	id = "npc_dontknowyou_1",
	leftDialog = "@theme_park_imperial/kaja_orzee:dontknowyou_1", --If you were not sent here by the Emperor, then I have nothing to say to you.
	stopConversation = "true",
	options = {
	}
}


imperial_retreat_kaja_orzee_convotemplate:addScreen(npc_dontknowyou_1);


addConversationTemplate("imperial_retreat_kaja_orzee_convotemplate",imperial_retreat_kaja_orzee_convotemplate);
