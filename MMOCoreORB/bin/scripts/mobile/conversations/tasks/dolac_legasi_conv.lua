dolac_legasi_convotemplate = ConvoTemplate:new {
	initialScreen = "",
	templateType = "Lua",
	luaClassHandler = "dolac_legasi_handler",
	screens = {}
}

----------
--This is shown if you've completed all Dolac Legasi's Quests
----------
nextQuest = ConvoScreen:new {
	id = "next",
	leftDialog = "@static_npc/dathomir/dathomir_imperialprison_dolac_legasi:next", --You've conquered the darkness. Or have you? Can anyone ever truly do that? Not when the darkness lives inside of us. You can feel it, can't you? You of all beings should be able to feel it.
	stopConversation = "true",
	options = {
	}
}

dolac_legasi_convotemplate:addScreen(nextQuest);

----------
--These are shown if you are not Imperial
----------
dontknowyou_1 = ConvoScreen:new {
	id = "dontknowyou_1",
	leftDialog = "@static_npc/dathomir/dathomir_imperialprison_dolac_legasi:dontknowyou_1",
	stopConversation = "true",
	options = {
	}
}

dolac_legasi_convotemplate:addScreen(dontknowyou_1);

dontknowyou_3 = ConvoScreen:new {
	id = "dontknowyou_3",
	leftDialog = "@static_npc/dathomir/dathomir_imperialprison_dolac_legasi:dontknowyou_3",
	stopConversation = "true",
	options = {
	}
}

dolac_legasi_convotemplate:addScreen(dontknowyou_3);

----------
--This is displayed if you have not completed the Mozo Bondog quest line.
----------
notyet = ConvoScreen:new {
	id = "notyet",
	leftDialog = "@static_npc/dathomir/dathomir_imperialprison_dolac_legasi:notyet",
	stopConversation = "true",
	options = {
	}
}

dolac_legasi_convotemplate:addScreen(notyet);

----------
--Quest 1 of 3
----------
npc_1_1 = ConvoScreen:new {
	id = "npc_1_1",
	leftDialog = "@static_npc/dathomir/dathomir_imperialprison_dolac_legasi:npc_1_1", --Has the fool Mozo sent you to solve the mystery of the disappearing inmates? I doubt you can, stranger. Odd, isn't it, that I call you stranger when I must seem just as strange to you? Stranger, perhaps. But in this place, most things seem strange. About those disappearing inmates... Interested?
	stopConversation = "false",
	options = {
		{"@static_npc/dathomir/dathomir_imperialprison_dolac_legasi:player_1_1", "npc_2_1"}, --Yes.
		{"@static_npc/dathomir/dathomir_imperialprison_dolac_legasi:player_2_1", "npc_3_1"}, --No.
		{"@static_npc/dathomir/dathomir_imperialprison_dolac_legasi:player_3_1", "npc_4_1"} --Tell me more about the disappearances.
	}
}

dolac_legasi_convotemplate:addScreen(npc_1_1);

npc_2_1 = ConvoScreen:new {
	id = "npc_2_1",
	leftDialog = "@static_npc/dathomir/dathomir_imperialprison_dolac_legasi:npc_2_1", --As it turns out, one of them has reappeared. Finding him will undoubtably shed some light on where the others have gone. But you must hurry. Dathomir is not exactly the sort of place one wishes to wander about. There are many horrors, both seen and unseen, that can claim a being's life... or soul.
	stopConversation = "true",
	options = {
	}
}

dolac_legasi_convotemplate:addScreen(npc_2_1);

npc_3_1 = ConvoScreen:new {
	id = "npc_3_1",
	leftDialog = "@static_npc/dathomir/dathomir_imperialprison_dolac_legasi:npc_3_1", --I didn't think you'd be the one to solve this riddle. I'm not sure what made you think you could. Was it the fact that the Force is strong in you? Oh dear, I've said too much.
	stopConversation = "true",
	options = {
	}
}

dolac_legasi_convotemplate:addScreen(npc_3_1);

npc_4_1 = ConvoScreen:new {
	id = "npc_4_1",
	leftDialog = "@static_npc/dathomir/dathomir_imperialprison_dolac_legasi:npc_4_1", --As I said, Dathomir is full of strange occurrences. In most cases, the prison cells were still sealed and there was no evidence of a breakout. What do you think this would imply?
	stopConversation = "false",
	options = {
		{"@static_npc/dathomir/dathomir_imperialprison_dolac_legasi:player_4_1", "npc_5_1"} --The inmates had help on the inside.
	}
}

dolac_legasi_convotemplate:addScreen(npc_4_1);

npc_5_1 = ConvoScreen:new {
	id = "npc_5_1",
	leftDialog = "@static_npc/dathomir/dathomir_imperialprison_dolac_legasi:npc_5_1", --That is a good conclusion, yet the recording devices show no evidence of any foul play. And there's the issue of the wraiths.
	stopConversation = "false",
	options = {
		{"@static_npc/dathomir/dathomir_imperialprison_dolac_legasi:player_5_1", "npc_6_1"} --What are the wraiths?
	}
}

dolac_legasi_convotemplate:addScreen(npc_5_1);

npc_6_1 = ConvoScreen:new {
	id = "npc_6_1",
	leftDialog = "@static_npc/dathomir/dathomir_imperialprison_dolac_legasi:npc_6_1", --The specters of those who have died on Dathomir. And those must surely number in the thousands. Could the wraiths have helped these inmates escape? Locate the lost inmate and you might have your answer. Do you wish to do it?
	stopConversation = "false",
	options = {
		{"@static_npc/dathomir/dathomir_imperialprison_dolac_legasi:player_1_1", "npc_2_1"}, --Yes.
		{"@static_npc/dathomir/dathomir_imperialprison_dolac_legasi:player_2_1", "npc_3_1"} --No.
	}
}

dolac_legasi_convotemplate:addScreen(npc_6_1);

----------
--Quest 2 of 3
----------

npc_1_2 = ConvoScreen:new {
	id = "npc_1_2",
	leftDialog = "@static_npc/dathomir/dathomir_imperialprison_dolac_legasi:npc_1_2", --You'd like to know where the 'place of shadows' is, wouldn't you? And what the shadow stone is? Perhaps I know of a place where this exists. But do you truly wish to go there?
	stopConversation = "false",
	options = {
		{"@static_npc/dathomir/dathomir_imperialprison_dolac_legasi:player_1_2", "npc_2_2"}, --Yes.
		{"@static_npc/dathomir/dathomir_imperialprison_dolac_legasi:player_2_2", "npc_3_2"} --No.
	}
}

dolac_legasi_convotemplate:addScreen(npc_1_2);

npc_2_2 = ConvoScreen:new {
	id = "npc_2_2",
	leftDialog = "@static_npc/dathomir/dathomir_imperialprison_dolac_legasi:npc_2_2", --Very well. Bring me the shadow shard and I may be able to help you solve this mystery. You can only get the shard by shattering the shadow stone. The wraiths will try to stop you.
	stopConversation = "false",
	options = {
		{"@static_npc/dathomir/dathomir_imperialprison_dolac_legasi:player_3_2", "npc_4_2"} --How do you know where the shadow stone is?
	}
}

dolac_legasi_convotemplate:addScreen(npc_2_2);

npc_3_2 = ConvoScreen:new {
	id = "npc_3_2",
	leftDialog = "@static_npc/dathomir/dathomir_imperialprison_dolac_legasi:npc_3_2", --Perhaps you are wiser than you look. This affair is beyond your feeble skills.
	stopConversation = "true",
	options = {
	}
}

dolac_legasi_convotemplate:addScreen(npc_3_2);

npc_4_2 = ConvoScreen:new {
	id = "npc_4_2",
	leftDialog = "@static_npc/dathomir/dathomir_imperialprison_dolac_legasi:npc_4_2", --The whispers told me, of course. I am not without my own skills, stranger. Why do you think I'm here? I was considered far too dangerous to be allowed to remain free, yet no one dared execute me. Isn't that odd?
	stopConversation = "false",
	options = {
		{"@static_npc/dathomir/dathomir_imperialprison_dolac_legasi:player_4_2", "npc_5_2"} --Who sent you here?
	}
}

dolac_legasi_convotemplate:addScreen(npc_4_2);

npc_5_2 = ConvoScreen:new {
	id = "npc_5_2",
	leftDialog = "@static_npc/dathomir/dathomir_imperialprison_dolac_legasi:npc_5_2", --The Emperor, who else? He declared me a threat to the Empire and had me imprisoned here. Don't you find that amusing? The Emperor declaring me a threat? I chuckle everytime I think of that.
	stopConversation = "false",
	options = {
		{"@static_npc/dathomir/dathomir_imperialprison_dolac_legasi:player_5_2", "npc_6_2"} --Why did the Emperor feel you were a threat?.
	}
}

dolac_legasi_convotemplate:addScreen(npc_5_2);

npc_6_2 = ConvoScreen:new {
	id = "npc_6_2",
	leftDialog = "@static_npc/dathomir/dathomir_imperialprison_dolac_legasi:npc_6_2", --Perhaps because he knew I could one day challenge him for control of the Empire. I was close to finding the key that would have allowed me to do that. But that is another matter...
	stopConversation = "true",
	options = {
	}
}

dolac_legasi_convotemplate:addScreen(npc_6_2);

----------
--Quest 3 of 3
----------

npc_1_3 = ConvoScreen:new {
	id = "npc_1_3",
	leftDialog = "@static_npc/dathomir/dathomir_imperialprison_dolac_legasi:npc_1_3", --The shard has revealed the ancient evil behind these wraiths. Do you think you can stop it? Do you dare try?
	stopConversation = "false",
	options = {
		{"@static_npc/dathomir/dathomir_imperialprison_dolac_legasi:player_1_3", "npc_2_3"}, --Yes.
		{"@static_npc/dathomir/dathomir_imperialprison_dolac_legasi:player_2_3", "npc_3_3"}, --No.
		{"@static_npc/dathomir/dathomir_imperialprison_dolac_legasi:player_3_3", "npc_4_3"} --What is this ancient evil?
	}
}

dolac_legasi_convotemplate:addScreen(npc_1_3);

npc_2_3 = ConvoScreen:new {
	id = "npc_2_3",
	leftDialog = "@static_npc/dathomir/dathomir_imperialprison_dolac_legasi:npc_2_3", --Go to these coordinates and face the master of these wraiths. This sinister force is strong with the dark side. It is not likely that you'll return.
	stopConversation = "true",
	options = {
	}
}

dolac_legasi_convotemplate:addScreen(npc_2_3);

npc_3_3 = ConvoScreen:new {
	id = "npc_3_3",
	leftDialog = "@static_npc/dathomir/dathomir_imperialprison_dolac_legasi:npc_3_3", --The dark side has a strong influence on the weak-minded. It is perhaps best that you choose not to face this power.
	stopConversation = "true",
	options = {
	}
}

dolac_legasi_convotemplate:addScreen(npc_3_3);

npc_4_3 = ConvoScreen:new {
	id = "npc_4_3",
	leftDialog = "@static_npc/dathomir/dathomir_imperialprison_dolac_legasi:npc_4_3", --The shard was a piece of a Sith holocron and it is a Sith that you go to face now. This agent of evil has enslaved many souls on Dathomir. This dark warrior can enslave the minds of others.
	stopConversation = "false",
	options = {
		{"@static_npc/dathomir/dathomir_imperialprison_dolac_legasi:player_4_3", "npc_5_3"} --Is this how the inmates were allowed to escape?
	}
}

dolac_legasi_convotemplate:addScreen(npc_4_3);

npc_5_3 = ConvoScreen:new {
	id = "npc_5_3",
	leftDialog = "@static_npc/dathomir/dathomir_imperialprison_dolac_legasi:npc_5_3", --The Emperor, who else? He declared me a threat to the Empire and had me imprisoned here. Don't you find that amusing? The Emperor declaring me a threat? I chuckle everytime I think of that.
	stopConversation = "false",
	options = {
		{"@static_npc/dathomir/dathomir_imperialprison_dolac_legasi:player_5_3", "npc_6_3"} --You've known this all along, haven't you?
	}
}

dolac_legasi_convotemplate:addScreen(npc_5_3);

npc_6_3 = ConvoScreen:new {
	id = "npc_6_3",
	leftDialog = "@static_npc/dathomir/dathomir_imperialprison_dolac_legasi:npc_6_3", --Yes, I have watched it happen time and again. The Sith wanted my allegiance but I refused to give it. I was too powerful to be controlled like the others so the Sith warrior was making arrangements to have me destroyed. I couldn't allow this to happen. Shall you go and end this menace once and for all?
	stopConversation = "false",
	options = {
		{"@static_npc/dathomir/dathomir_imperialprison_dolac_legasi:player_1_3", "npc_2_3"}, --Yes.
		{"@static_npc/dathomir/dathomir_imperialprison_dolac_legasi:player_2_3", "npc_3_3"} --No.
	}
}

dolac_legasi_convotemplate:addScreen(npc_6_3);

----------
--Already working for Dolac Legasi
----------
npc_work_1 = ConvoScreen:new {
	id = "npc_work_1",
	leftDialog = "@static_npc/dathomir/dathomir_imperialprison_dolac_legasi:npc_work_1", --Have you found the missing inmate? What secrets await to be revealed?
	stopConversation = "false",
	options = {
		{"@static_npc/dathomir/dathomir_imperialprison_dolac_legasi:player_sorry", ""}, --I'll keep working on the mission.
		{"@static_npc/dathomir/dathomir_imperialprison_dolac_legasi:player_reset", "npc_reset"} --I don't want this mission right now.
	}
}

dolac_legasi_convotemplate:addScreen(npc_work_1);

npc_work_2 = ConvoScreen:new {
	id = "npc_work_2",
	leftDialog = "@static_npc/dathomir/dathomir_imperialprison_dolac_legasi:npc_work_2", --Where is the shard of the shadow stone? I cannot help you if I do not have it.
	stopConversation = "false",
	options = {
		{"@static_npc/dathomir/dathomir_imperialprison_dolac_legasi:player_sorry", ""}, --I'll keep working on the mission.
		{"@static_npc/dathomir/dathomir_imperialprison_dolac_legasi:player_reset", "npc_reset"} --I don't want this mission right now.
	}
}

dolac_legasi_convotemplate:addScreen(npc_work_2);

npc_work_3 = ConvoScreen:new {
	id = "npc_work_3",
	leftDialog = "@static_npc/dathomir/dathomir_imperialprison_dolac_legasi:npc_work_3", --Have you confronted this ancient evil? It will conquer this planet if you fail to stop it.
	stopConversation = "false",
	options = {
		{"@static_npc/dathomir/dathomir_imperialprison_dolac_legasi:player_sorry", ""}, --I'll keep working on the mission.
		{"@static_npc/dathomir/dathomir_imperialprison_dolac_legasi:player_reset", "npc_reset"} --I don't want this mission right now.
	}
}

dolac_legasi_convotemplate:addScreen(npc_work_3);

----------
--This is displayed if the player chooses to reset the mission.
----------
npc_reset = ConvoScreen:new {
	id = "npc_reset",
	leftDialog = "@static_npc/dathomir/dathomir_imperialprison_dolac_legasi:npc_reset", --This is beyond you. Go back to the light where all is safe. The dark is no place for you.
	stopConversation = "true",
	options = {
	}
}

dolac_legasi_convotemplate:addScreen(npc_reset);

---------
--Reward Messages
---------
npc_reward_1 = ConvoScreen:new {
	id = "npc_reward_1",
	leftDialog = "@static_npc/dathomir/dathomir_imperialprison_dolac_legasi:npc_reward_1", --More questions? How could this be? That is the nature of clues. They answer old questions and create new ones. There will always be questions. Claim the reward Mozo has provided for you.
	stopConversation = "true",
	options = {
	}
}

dolac_legasi_convotemplate:addScreen(npc_reward_1);

npc_reward_2 = ConvoScreen:new {
	id = "npc_reward_2",
	leftDialog = "@static_npc/dathomir/dathomir_imperialprison_dolac_legasi:npc_reward_2", --You have brought me the crystal shard. Excellent. I must study its secrets before I can help you fight the wraiths.
	stopConversation = "true",
	options = {
	}
}

dolac_legasi_convotemplate:addScreen(npc_reward_2);

npc_reward_3 = ConvoScreen:new {
	id = "npc_reward_3",
	leftDialog = "@static_npc/dathomir/dathomir_imperialprison_dolac_legasi:npc_reward_3", --There are many evils in this universe. The Sith are but one of these. I am another. Remember that the light cannot exist without darkness.
	stopConversation = "true",
	options = {
	}
}

dolac_legasi_convotemplate:addScreen(npc_reward_3);

----------
--Failure Messages
----------
npc_failure_1 = ConvoScreen:new {
	id = "npc_failure_1",
	leftDialog = "@static_npc/dathomir/dathomir_imperialprison_dolac_legasi:npc_failure_1", --What hope did you have against such an ancient evil? You are nothing compared to its power.
	stopConversation = "true",
	options = {
	}
}

dolac_legasi_convotemplate:addScreen(npc_failure_1);

npc_failure_2 = ConvoScreen:new {
	id = "npc_failure_2",
	leftDialog = "@static_npc/dathomir/dathomir_imperialprison_dolac_legasi:npc_failure_2", --No shard, no secrets revealed. Such a waste.
	stopConversation = "true",
	options = {
	}
}

dolac_legasi_convotemplate:addScreen(npc_failure_2);

npc_failure_3 = ConvoScreen:new {
	id = "npc_failure_3",
	leftDialog = "@static_npc/dathomir/dathomir_imperialprison_dolac_legasi:npc_failure_3", --The darkness will spread from Dathomir to other planets. Perhaps the Emperor will have to become involved.
	stopConversation = "true",
	options = {
	}
}

dolac_legasi_convotemplate:addScreen(npc_failure_3);


addConversationTemplate("dolac_legasi_convotemplate", dolac_legasi_convotemplate);
