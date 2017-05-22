corvetteDarkstoneConvoTemplate = ConvoTemplate:new {
	initialScreen = "",
	templateType = "Lua",
	luaClassHandler = "ticketGiverDarkstoneConvoHandler",
	screens = {}
}

no_faction = ConvoScreen:new {
	id = "no_faction",
	leftDialog = "@conversation/corvette_colonel_imperial1:s_684f9e1", --I cannot help you, citizen. Please try elsewhere.
	stopConversation = "true",
	options = {}
}
corvetteDarkstoneConvoTemplate:addScreen(no_faction);

already_busy = ConvoScreen:new {
	id = "already_busy",
	leftDialog = "@conversation/corvette_colonel_imperial1:s_33f4749f",--Ah, not now. I could use your help, but I see that you're already busy. Come back when you've finished your current task and maybe I'll have something for you.
	stopConversation = "true",
	options = {}
}
corvetteDarkstoneConvoTemplate:addScreen(already_busy);

convo_start = ConvoScreen:new {
	id = "convo_start",
	leftDialog = "@conversation/corvette_colonel_imperial1:s_d630c3b6",--I am nearing the end of my days serving as the main point of contact in regards to Imperial officers who find themselves in a hostage situation. Every mission is important. As possibly my last, this one proves to be most difficult.
	stopConversation = "false",
	options = {
		{"@conversation/corvette_colonel_imperial1:s_df607c49","convo_start_1"},-- I'm listening.
		{"@conversation/corvette_colonel_imperial1:s_5200ce80","convo_exit"},--I'm not interested. Good-bye.
	}
}
corvetteDarkstoneConvoTemplate:addScreen(convo_start);

convo_start_1 = ConvoScreen:new {
	id = "convo_start_1",
	leftDialog = "@conversation/corvette_colonel_imperial1:s_a5e941d1",--Dr. Bledsoe is the Empire's expert in the areas of disease and medicine. Unfortunately, he was abducted by Alliance terrorists. There's no telling what those ruthless animals will do to him but his existence is extremely important to the Empire's efforts. He needs to be returned. Will you help us?
	stopConversation = "false",
	options = {
		{"@conversation/corvette_colonel_imperial1:s_1944f1e6","quest_start"},-- Yes, I will.
		{"@conversation/corvette_colonel_imperial1:s_157ef5eb","convo_exit"} --I... don't like this at all. I'll have to pass.
	}
}
corvetteDarkstoneConvoTemplate:addScreen(convo_start_1);

convo_exit = ConvoScreen:new {
	id = "convo_exit",
	leftDialog = "@conversation/corvette_colonel_imperial1:s_28586fd5",--Very well.
	stopConversation = "true",
	options = {}
}
corvetteDarkstoneConvoTemplate:addScreen(convo_exit);

quest_start = ConvoScreen:new {
	id = "quest_start",
	leftDialog = "@conversation/corvette_colonel_imperial1:s_a342e94c",--Very well. I shall continue. We have intercepted faint transmissions discussing Dr. Bledsoe's transfer but have been unable to determine where they are they are holding him. This is where you come in. There are three locations at which we believe you might find prisoner transfer orders for Dr. Bledsoe. These three locations are the Woolamander Palace on Yavin IV, the Rogue CorSec base on Corellia, and the Droid Engineer cave on Lok.
	stopConversation = "false",
	options = {}
}
corvetteDarkstoneConvoTemplate:addScreen(quest_start);

which_planet = ConvoScreen:new {
	id = "which_planet",
	leftDialog = "@conversation/corvette_colonel_imperial1:s_ec42069a",--Very well. We have intercepted faint transmissions discussing Dr. Bledsoe's transfer but have been unable to determine where they are they are holding him. This is where you come in. There are three locations at which we believe you might find prisoner transfer orders for Dr. Bledsoe. These three locations are the Woolamander Palace on Yavin IV, the Rogue CorSec base on Corellia, and the Droid Engineer cave on Lok.
	stopConversation = "false",
	options = {}
}
corvetteDarkstoneConvoTemplate:addScreen(which_planet);

first_location = ConvoScreen:new {
	id = "first_location",
	leftDialog = "@conversation/corvette_colonel_imperial1:s_56fe6ddb",--The Woolamander Palace can be found on Yavin IV. I do not know the history of the place. We have received several reports that affiliates of the Alliance still operate from its ruins from time to time. It can be found in the central area of Yavin IV. I don't have anymore information.
	stopConversation = "false",
	options = { }
}
corvetteDarkstoneConvoTemplate:addScreen(first_location);

second_location = ConvoScreen:new {
	id = "second_location",
	leftDialog = "@conversation/corvette_colonel_imperial1:s_3b10534d", --We've discovered that a group of ex-CorSec agents on Corellia have been monitoring local activities of certain Rebel Alliance groups. While we don't know the exact reasons behind this, we do know that these former members of the Corellian Security Forces have turned to a life of crime and are not helping the Alliance. The Empire typically leaves them alone, but we now need to find out if they have information about the abduction of Dr. Bledsoe. Go and search their base.
	stopConversation = "false",
	options = {}
}
corvetteDarkstoneConvoTemplate:addScreen(second_location);

third_location = ConvoScreen:new {
	id = "third_location",
	leftDialog = "@conversation/corvette_colonel_imperial1:s_fc068f1e", --This cave was established by a crazed droid engineer and served as a place to operate on his droids, making them lethal killing machines. What the Alliance is doing there is beyond my comprehension. The cave can be found on Lok in the heart of the volcano. He was mad, indeed.
	stopConversation = "false",
	options = {}
}
corvetteDarkstoneConvoTemplate:addScreen(third_location);

go_get_intel = ConvoScreen:new {
	id = "go_get_intel",
	leftDialog = "@conversation/corvette_colonel_imperial1:s_bd942cc0",--Excellent. Good luck to you.
	stopConversation = "true",
	options = {}
}
corvetteDarkstoneConvoTemplate:addScreen(go_get_intel);

hear_locations_quit = ConvoScreen:new {
	id = "hear_locations_quit",
	leftDialog = "@conversation/corvette_colonel_imperial1:s_74edd9cc", --And that is your choice. I am disappointed..
	stopConversation = "true",
	options = {}
}
corvetteDarkstoneConvoTemplate:addScreen(hear_locations_quit);

back_already = ConvoScreen:new {
	id = "back_already",
	leftDialog = "@conversation/corvette_colonel_imperial1:s_18d01770", --You have returned. I am glad to see you are still well. What have you discovered? Do you have any documents? Or do you need information?
	stopConversation = "false",
	options = {}
}
corvetteDarkstoneConvoTemplate:addScreen(back_already);

back_already_reset = ConvoScreen:new {
	id = "back_already_reset",
	leftDialog = "@conversation/corvette_colonel_imperial1:s_bcecb501", --Very well. You have been released from this mission. You understand that I must remove from you all documents and data connected to this mission. Stand operating procedure.
	stopConversation = "true",
	options = {}
}
corvetteDarkstoneConvoTemplate:addScreen(back_already_reset);

has_intel = ConvoScreen:new {
	id = "has_intel",
	leftDialog = "@conversation/corvette_colonel_imperial1:s_3c50285d", -- Excellent! What have you found on your mission?
	stopConversation = "false",
	options = {}
}
corvetteDarkstoneConvoTemplate:addScreen(has_intel);

bad_intel_1 = ConvoScreen:new {
	id = "bad_intel_1",
	leftDialog = "@conversation/corvette_colonel_imperial1:s_adecb4e7",--Hmm.. this information is very interesting. However, these are not the orders I had been looking for. I will take these off your hands, though, and reward you for finding them.
	stopConversation = "false",
	options = {}
}
corvetteDarkstoneConvoTemplate:addScreen(bad_intel_1);

bad_intel_2 = ConvoScreen:new {
	id = "bad_intel_2",
	leftDialog = "@conversation/corvette_colonel_imperial1:s_adecb4e7", --Hmm.. this information is very interesting. However, these are not the orders I had been looking for. I will take these off your hands, though, and reward you for finding them.
	stopConversation = "false",
	options = {}
}
corvetteDarkstoneConvoTemplate:addScreen(bad_intel_2);

check_other_places = ConvoScreen:new {
	id = "check_other_places",
	leftDialog = "@conversation/corvette_colonel_imperial1:s_33656cd3", --Indeed. I need those documents as soon as possible. Please find them quickly.
	stopConversation = "true",
	options = {}
}

corvetteDarkstoneConvoTemplate:addScreen(check_other_places);

other_documents = ConvoScreen:new {
	id = "other_documents",
	leftDialog = "@conversation/corvette_colonel_imperial1:s_ffa3808c", --Oh, show me the ones you still have.
	stopConversation = "false",
	options = { }
}
corvetteDarkstoneConvoTemplate:addScreen(other_documents);

good_intel = ConvoScreen:new {
	id = "good_intel",
	leftDialog = "@conversation/corvette_colonel_imperial1:s_e6e45415",--Finally! We now know his whereabouts. He has been moved to a Corellian corvette within deep space. I need an Imperial soldier I can trust to go there and rescue the doctor. Ah...You! You are that soldier. Take this item to the shuttle pilot at the Emperor's Retreat. He will help you to intercept the Corellian corvette with Dr. Bledsoe. If your mission is successful I will probably be able to offer you a reward. If you desire one. Either way, I wish you luck in this endeavor.
	stopConversation = "false",
	options = {}
}
corvetteDarkstoneConvoTemplate:addScreen(good_intel);

go_to_corvette = ConvoScreen:new {
	id = "go_to_corvette",
	leftDialog = "@conversation/corvette_colonel_imperial1:s_2a973e2d", --This news pleases me. Please be careful and return safely. Oh, and if you succeed in this mission, I can offer you a reward. Though a true soldier of the Empire would desire no such thing.
	stopConversation = "true",
	options = {}
}
corvetteDarkstoneConvoTemplate:addScreen(go_to_corvette);

still_here = ConvoScreen:new {
	id = "still_here",
	leftDialog = "@conversation/corvette_colonel_imperial1:s_5c4b594c",--I see you have returned. Are you in need of additional assistance?
	stopConversation = "false",
	options = {	}
}
corvetteDarkstoneConvoTemplate:addScreen(still_here);

still_here_decline = ConvoScreen:new {
	id = "still_here_decline",
	leftDialog = "@conversation/corvette_colonel_imperial1:s_80d92f17", --Are you sure? Your progress will be erased from our database, all remaining documents will be taken from you, and the travel authorization will be revoked.
	stopConversation = "false",
	options = {
		{"@conversation/corvette_colonel_imperial1:s_dd109d64","decline_quest_reset"},--That's fine. I resign.
		{"@conversation/corvette_colonel_imperial1:s_7a2a05c4","changed_mind"},--In that case, I'll continue.
	}
}
corvetteDarkstoneConvoTemplate:addScreen(still_here_decline);

decline_quest_reset = ConvoScreen:new {
	id = "decline_quest_reset",
	leftDialog = "@conversation/corvette_colonel_imperial1:s_180bc00a", --Very well. It is sad to hear.
	stopConversation = "true",
	options = {}
}
corvetteDarkstoneConvoTemplate:addScreen(decline_quest_reset);

changed_mind = ConvoScreen:new {
	id = "changed_mind",
	leftDialog = "@conversation/corvette_colonel_imperial1:s_f769f479", -- I am glad to hear of it.
	stopConversation = "true",
	options = {}
}
corvetteDarkstoneConvoTemplate:addScreen(changed_mind);

launch_location = ConvoScreen:new {
	id = "launch_location",
	leftDialog = "@conversation/corvette_colonel_imperial1:s_4002f794", --You must travel to the Emperor's Retreat and present your ticket to the shuttle pilot there. He will help you to intercept the Corellian corvette so that you may continue your mission. If your mission is successful and you desire a reward, return and speak with me afterwards.
	stopConversation = "true",
	options = {}
}
corvetteDarkstoneConvoTemplate:addScreen(launch_location);

reward = ConvoScreen:new {
	id = "reward",
	leftDialog = "@conversation/corvette_colonel_imperial1:s_c48932d",--Your service to the Empire has been adequate. I suppose a reward is in order, if you desire one?
	stopConversation = "false",
	options = {
		{"@conversation/corvette_colonel_imperial1:s_21550a19","give_reward"}, --A reward? Definitely. Hand it over.
		{"@conversation/corvette_colonel_imperial1:s_a38773c1","reward_notyet"} --I'm not sure. Maybe I'll come back later.
	}
}
corvetteDarkstoneConvoTemplate:addScreen(reward);

reward_notyet = ConvoScreen:new {
	id = "reward_notyet",
	leftDialog = "@conversation/corvette_colonel_imperial1:s_dc4a40d6", --Exactly... your reward is serving the Empire. But should you change your mind, simply speak with me again.
	stopConversation = "true",
	options = {}
}
corvetteDarkstoneConvoTemplate:addScreen(reward_notyet);

give_reward = ConvoScreen:new {
	id = "give_reward",
	leftDialog = "@conversation/corvette_colonel_imperial1:s_81ff39a5", --I thought as much. Very well, take it. You did earn this, though I'd hoped the honor of serving the Empire would have been enough.
	stopConversation = "true",
	options = {}
}
corvetteDarkstoneConvoTemplate:addScreen(give_reward);

cant_give_reward = ConvoScreen:new {
	id = "cant_give_reward",
	leftDialog = "@conversation/corvette_colonel_imperial1:s_8e06b4e8", --Ah yes. I would hand it over, as you ask, but you don't have room to carry it. So you'll have to clear some space before you may take it.
	stopConversation = "true",
	options = {}
}
corvetteDarkstoneConvoTemplate:addScreen(cant_give_reward);

addConversationTemplate("corvetteDarkstoneConvoTemplate", corvetteDarkstoneConvoTemplate);

