corvetteCrowleyConvoTemplate = ConvoTemplate:new {
	initialScreen = "",
	templateType = "Lua",
	luaClassHandler = "ticketGiverCrowleyConvoHandler",
	screens = {}
}

no_faction = ConvoScreen:new {
	id = "no_faction",
	leftDialog = "@conversation/corvette_crowley_rebel1:s_c55f8e77", --I've much to do... I'm afraid I don't have time to spare unless it involves urgent Rebel business.
	stopConversation = "true",
	options = {}
}
corvetteCrowleyConvoTemplate:addScreen(no_faction);

already_busy = ConvoScreen:new {
	id = "already_busy",
	leftDialog = "@conversation/corvette_crowley_rebel1:s_2c449c28",--I suppose I could use your help, but I see that you're already busy. Come back when you've finished your current task and maybe you can still help.
	stopConversation = "true",
	options = {}
}
corvetteCrowleyConvoTemplate:addScreen(already_busy);

convo_start = ConvoScreen:new {
	id = "convo_start",
	leftDialog = "@conversation/corvette_crowley_rebel1:s_84bd3f49",--One of our own Corellian corvettes. Unthinkable. The Empire has crafted a diabolical political maneuver. They've stolen a Corellian corvette and are filling it with explosives. They intend to send it hurtling into Centerpoint Station near Corellia. The plan being to make the Rebels look both foolish and dangerous at the same time. We must stop them before they complete their horrible plan.
	stopConversation = "false",
	options = {
		{"@conversation/corvette_crowley_rebel1:s_59f5cee6","quest_start"},--Is there anything I can do to help?
		{"@conversation/corvette_crowley_rebel1:s_df8ea53","convo_exit"} --Not interested.
	}
}
corvetteCrowleyConvoTemplate:addScreen(convo_start);

quest_start = ConvoScreen:new {
	id = "quest_start",
	leftDialog = "@conversation/corvette_crowley_rebel1:s_e77661bc",--Hmm... Indeed. You seem capable enough to help us in this endeavor. We must find the location of that Corellian corvette. We believe it to be somewhere in deep space and thus harder to find and safer in case anything goes wrong. Based on intel gathered, I know of three places you should look. Those being  the Imperial Base on Lok, the Rogue CorSec base on Corellia, and the Imperial prison on Dathomir.
	stopConversation = "false",
	options = {	}
}
corvetteCrowleyConvoTemplate:addScreen(quest_start);

convo_exit = ConvoScreen:new {
	id = "convo_exit",
	leftDialog = "@conversation/corvette_crowley_rebel1:s_f26df06d", -- I'm sorry to hear that. Very well, we'll continue on without you.
	stopConversation = "true",
	options = {}
}
corvetteCrowleyConvoTemplate:addScreen(convo_exit);

which_planet = ConvoScreen:new {
	id = "which_planet",
	leftDialog = "@conversation/corvette_crowley_rebel1:s_dd846d25",--You need to find a document which details the location of the Corellian corvette. Which location do you need more information on?
	stopConversation = "false",
	options = {}
}
corvetteCrowleyConvoTemplate:addScreen(which_planet);

first_location = ConvoScreen:new {
	id = "first_location",
	leftDialog = "@conversation/corvette_crowley_rebel1:s_fa42cc8d",--We have reason to believe that Imperial General Otto, stationed at the Imperial base on Lok, may be supplying the explosives being used on the corvette. General Otto is known to be fairly careless, so it would not be surprising if the information you seek was in an unsecured crate or desk somewhere. Seek out his base and return with any information you find.
	stopConversation = "false",
	options = {}
}
corvetteCrowleyConvoTemplate:addScreen(first_location);

second_location = ConvoScreen:new {
	id = "second_location",
	leftDialog = "@conversation/corvette_crowley_rebel1:s_2621fdc0", --Rumor is that a group of Rogue CorSec operatives have stolen some important documents from the Empire. This could well include the information I'm looking for. If so, it's in their hideout on Corellia.
	stopConversation = "false",
	options = {}
}
corvetteCrowleyConvoTemplate:addScreen(second_location);

third_location = ConvoScreen:new {
	id = "third_location",
	leftDialog = "@conversation/corvette_crowley_rebel1:s_7ed78a88", --Many who have been taken to the Imperial Prison on Dathomir have never been seen again. It is a dangerous and forbidding place. Rumor is that the surviving crew of this corvette is incarcerated there. Travel to this dangerous planet and infiltrate the prison. Search for any information you can find.
	stopConversation = "false",
	options = {	}
}
corvetteCrowleyConvoTemplate:addScreen(third_location);

go_get_intel = ConvoScreen:new {
	id = "go_get_intel",
	leftDialog = "@conversation/corvette_crowley_rebel1:s_71aabcdc",--Hope has been uplifted in me by you. Be swift and come back safely with the information we need.
	stopConversation = "true",
	options = {}
}
corvetteCrowleyConvoTemplate:addScreen(go_get_intel);

hear_locations_quit = ConvoScreen:new {
	id = "hear_locations_quit",
	leftDialog = "@conversation/corvette_crowley_rebel1:s_762ce016", --A pity. I am disappointed but will find another to replace you.
	stopConversation = "true",
	options = {}
}
corvetteCrowleyConvoTemplate:addScreen(hear_locations_quit);

back_already = ConvoScreen:new {
	id = "back_already",
	leftDialog = "@conversation/corvette_crowley_rebel1:s_a4965b23", --I see you have returned. Have you found what we're looking for?
	stopConversation = "false",
	options = {}
}
corvetteCrowleyConvoTemplate:addScreen(back_already);

back_already_reset = ConvoScreen:new {
	id = "back_already_reset",
	leftDialog = "@conversation/corvette_crowley_rebel1:s_cb6caf3", -- That is sad news, but I will do so. It will be difficult to replace you. I'll have to retrieve all documents and data gathered for this mission from you. Sorry, but it's required.
	stopConversation = "true",
	options = { }
}
corvetteCrowleyConvoTemplate:addScreen(back_already_reset);

has_intel = ConvoScreen:new {
	id = "has_intel",
	leftDialog = "@conversation/corvette_crowley_rebel1:s_16205aba", --What exactly have you found?
	stopConversation = "false",
	options = {}
}
corvetteCrowleyConvoTemplate:addScreen(has_intel);

bad_intel_1 = ConvoScreen:new {
	id = "bad_intel_1",
	leftDialog = "@conversation/corvette_crowley_rebel1:s_9dc63a4b",--Unfortunately, this isn't the information needed for our mission. However, any information is good information. I will reward you for this.
	stopConversation = "false",
	options = {}
}
corvetteCrowleyConvoTemplate:addScreen(bad_intel_1);

bad_intel_2 = ConvoScreen:new {
	id = "bad_intel_2",
	leftDialog = "@conversation/corvette_crowley_rebel1:s_9dc63a4b", --Unfortunately, this isn't the information needed for our mission. However, any information is good information. I will reward you for this.
	stopConversation = "false",
	options = {	}
}
corvetteCrowleyConvoTemplate:addScreen(bad_intel_2);

check_other_places = ConvoScreen:new {
	id = "check_other_places",
	leftDialog = "@conversation/corvette_crowley_rebel1:s_da09e61c", --Indeed. You'll need to find the information as quickly as possible.
	stopConversation = "true",
	options = {}
}

corvetteCrowleyConvoTemplate:addScreen(check_other_places);

other_documents = ConvoScreen:new {
	id = "other_documents",
	leftDialog = "@conversation/corvette_crowley_rebel1:s_3bd032cd", --I see. Which documents do you have for me?
	stopConversation = "false",
	options = {	}
}
corvetteCrowleyConvoTemplate:addScreen(other_documents);

good_intel = ConvoScreen:new {
	id = "good_intel",
	leftDialog = "@conversation/corvette_crowley_rebel1:s_397c5f6d",--Excellent! This is exactly the information we've needed! We now know where the Corellian corvette is. You'll need to speak with Lt. Lance at the Rebel Alliance hideout on Corellia. He will provide transportation which will enable you to intercept the stolen Corellian corvette. When you get to the corvette, it must be destroyed before it hits Centerpoint Station near Corellia. Once that has been accomplished return to me for a reward. Now go see Lt. Lance on Corellia.
	stopConversation = "false",
	options = { }
}
corvetteCrowleyConvoTemplate:addScreen(good_intel);

go_to_corvette = ConvoScreen:new {
	id = "go_to_corvette",
	leftDialog = "@conversation/corvette_crowley_rebel1:s_908f0d55", --Good luck, young recruit. Return in victory and be rewarded. May the Force be with you.
	stopConversation = "true",
	options = {}
}
corvetteCrowleyConvoTemplate:addScreen(go_to_corvette);

still_here = ConvoScreen:new {
	id = "still_here",
	leftDialog = "@conversation/corvette_crowley_rebel1:s_bcc53c45",--I am surprised to see you here. Are you in need of more information?
	stopConversation = "false",
	options = {	}
}
corvetteCrowleyConvoTemplate:addScreen(still_here);

still_here_decline = ConvoScreen:new {
	id = "still_here_decline",
	leftDialog = "@conversation/corvette_crowley_rebel1:s_fb051f63", --Are you certain? Very well. But your progress will be erased, any remaining documents will be confiscated, and the travel authorization will be revoked. If you change you mind and decide to try again, you'll have to start from the beginning.
	stopConversation = "false",
	options = {
		{"@conversation/corvette_crowley_rebel1:s_b4b735ef","decline_quest_reset"},--That's okay. I cannot continue.
		{"@conversation/corvette_crowley_rebel1:s_b6a784f4","changed_mind"},--Er... maybe I'll do it. Or at least think about it.
	}
}
corvetteCrowleyConvoTemplate:addScreen(still_here_decline);

decline_quest_reset = ConvoScreen:new {
	id = "decline_quest_reset",
	leftDialog = "@conversation/corvette_crowley_rebel1:s_c03449c4", --A pity, indeed. You have been released from the mission.
	stopConversation = "true",
	options = {}
}
corvetteCrowleyConvoTemplate:addScreen(decline_quest_reset);

changed_mind = ConvoScreen:new {
	id = "changed_mind",
	leftDialog = "@conversation/corvette_crowley_rebel1:s_1b28b4c", -- There is hope yet. Good luck on your mission.
	stopConversation = "true",
	options = {}
}
corvetteCrowleyConvoTemplate:addScreen(changed_mind);

launch_location = ConvoScreen:new {
	id = "launch_location",
	leftDialog = "@conversation/corvette_crowley_rebel1:s_2373d61a", --Lt. Lance at the Rebel hideout on Corellia is waiting to meet you. He will provide transportation which will enable you to intercept the stolen Corellian corvette. After you've victoriously completed your mission, return to me for a reward.
	stopConversation = "true",
	options = {}
}
corvetteCrowleyConvoTemplate:addScreen(launch_location);

reward = ConvoScreen:new {
	id = "reward",
	leftDialog = "@conversation/corvette_crowley_rebel1:s_729d86e2", --You've done an outstanding job! When I heard that the corvette was destroyed, I was ecstatic. Are you here for your reward?
	stopConversation = "false",
	options = {
		{"@conversation/corvette_crowley_rebel1:s_36e1dfe9","give_reward"}, --I am. Thank you.
		{"@conversation/corvette_crowley_rebel1:s_823e1fa","reward_notyet"} --No, I'm not yet ready for it.
	}
}
corvetteCrowleyConvoTemplate:addScreen(reward);

reward_notyet = ConvoScreen:new {
	id = "reward_notyet",
	leftDialog = "@conversation/corvette_crowley_rebel1:s_a539245b", --I see. Well, whenever you're ready, just come talk to me.
	stopConversation = "true",
	options = {}
}
corvetteCrowleyConvoTemplate:addScreen(reward_notyet);

give_reward = ConvoScreen:new {
	id = "give_reward",
	leftDialog = "@conversation/corvette_crowley_rebel1:s_44a0326c", --It is a pleasure to reward you for such a triumphant mission.
	stopConversation = "true",
	options = {}
}
corvetteCrowleyConvoTemplate:addScreen(give_reward);

cant_give_reward = ConvoScreen:new {
	id = "cant_give_reward",
	leftDialog = "@conversation/corvette_crowley_rebel1:s_d3c9d7bc", --Um... while I'd like nothing more than to give you your reward, you do not have room for it at the moment. Please make some space and then talk to me again.
	stopConversation = "true",
	options = {}
}
corvetteCrowleyConvoTemplate:addScreen(cant_give_reward);

addConversationTemplate("corvetteCrowleyConvoTemplate", corvetteCrowleyConvoTemplate);

