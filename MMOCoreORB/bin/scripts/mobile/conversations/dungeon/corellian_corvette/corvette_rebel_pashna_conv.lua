corvettePashnaConvoTemplate = ConvoTemplate:new {
	initialScreen = "",
	templateType = "Lua",
	luaClassHandler = "ticketGiverPashnaConvoHandler",
	screens = {}
}

no_faction = ConvoScreen:new {
	id = "no_faction",
	leftDialog = "@conversation/corvette_pashna_rebel1:s_dbef483d", --I have some serious... and unfortunate... business for the Rebellion that demands my attention. Forgive me, but I can't speak with you right now.
	stopConversation = "true",
	options = {}
}
corvettePashnaConvoTemplate:addScreen(no_faction);

already_busy = ConvoScreen:new {
	id = "already_busy",
	leftDialog = "@conversation/corvette_pashna_rebel1:s_ecc372ff",--Oh hmmm... I could really use your help, but I see that you're already busy. Come back when you've finished your current task and perhaps I'll still need your assistance.
	stopConversation = "true",
	options = {}
}
corvettePashnaConvoTemplate:addScreen(already_busy);

convo_start = ConvoScreen:new {
	id = "convo_start",
	leftDialog = "@conversation/corvette_pashna_rebel1:s_bbd30f60",--You couldn't have come at a more distressing time, my friend.
	stopConversation = "false",
	options = {
		{"@conversation/corvette_pashna_rebel1:s_d3412303","convo_start_1"},-- What seems to be the problem?
		{"@conversation/corvette_pashna_rebel1:s_b89af325","convo_exit"} --Be that as it may, good-bye.
	}
}
corvettePashnaConvoTemplate:addScreen(convo_start);

convo_start_1 = ConvoScreen:new {
	id = "convo_start_1",
	leftDialog = "@conversation/corvette_pashna_rebel1:s_77da0881",--You are one of us, therefore I can trust you with this information. It seems that one of our Corellian corvettes has been boarded and seized by a ruthless Imperial commander. This Imperial commander is bent on guiding the ship toward Talus and crashing it into our base there. My first priority is to retake the ship before it crashes into our base. And second is to... well... is to assassinate the Imperial commander responsible for this threat.
	stopConversation = "false",
	options = {
		{"@conversation/corvette_pashna_rebel1:s_e10e18f5","convo_start_2"},--Do you need any help with this situation?
		{"@conversation/corvette_pashna_rebel1:s_f7e9bbb3","convo_exit_2"},--Good luck with that. I'm not interested in getting involved.
	}
}
corvettePashnaConvoTemplate:addScreen(convo_start_1);

convo_start_2 = ConvoScreen:new {
	id = "convo_start_2",
	leftDialog = "@conversation/corvette_pashna_rebel1:s_73f241bd",--In fact, I do. Before we take any measure of action, I need more information regarding this Imperial commander, his background. I can't issue an assassination without knowing he, without a doubt, warrants such a demise. I have reason to believe that such information exists at one of three places: Fort Tusken on Tatooine, a Geonosian laboratory on Yavin IV, or the Mokk stronghold on Dantooine. Can you see to this?
	stopConversation = "false",
	options = {
		{"@conversation/corvette_pashna_rebel1:s_ba7150b1","quest_start"},--Yes, I will help you.
		{"@conversation/corvette_pashna_rebel1:s_436d636d","convo_exit_3"},--That sounds like a problem. I wish I could help, but really I don't care.
	}
}
corvettePashnaConvoTemplate:addScreen(convo_start_2);

convo_exit = ConvoScreen:new {
	id = "convo_exit",
	leftDialog = "@conversation/corvette_pashna_rebel1:s_fe450b8a",--It probably is best that you go. I must concentrate on the tasks at hand.
	stopConversation = "true",
	options = {	}
}
corvettePashnaConvoTemplate:addScreen(convo_exit);

convo_exit_2 = ConvoScreen:new {
	id = "convo_exit_2",
	leftDialog = "@conversation/corvette_pashna_rebel1:s_7384b0d4",--I see. Such apathy is what holds our efforts back from true success. But then, I suppose the idea of assassinating another person can be difficult to accept. I understand your reservations.
	stopConversation = "true",
	options = {	}
}
corvettePashnaConvoTemplate:addScreen(convo_exit_2);

convo_exit_3 = ConvoScreen:new {
	id = "convo_exit_3",
	leftDialog = "@conversation/corvette_pashna_rebel1:s_8f4b486e",--Indeed. Hopefully, someone will come along to help us with the situation.
	stopConversation = "true",
	options = {	}
}
corvettePashnaConvoTemplate:addScreen(convo_exit_3);

quest_start = ConvoScreen:new {
	id = "quest_start",
	leftDialog = "@conversation/corvette_pashna_rebel1:s_ffb796fa",--I am relieved and thankful for your eager assistance. Seek out the documents in the locations I mentioned. If you need more information about any of them, please let me know.
	stopConversation = "false",
	options = {}
}
corvettePashnaConvoTemplate:addScreen(quest_start);

which_planet = ConvoScreen:new {
	id = "which_planet",
	leftDialog = "@conversation/corvette_pashna_rebel1:s_89df7355",--Which location would you like more information about?
	stopConversation = "false",
	options = {}
}
corvettePashnaConvoTemplate:addScreen(which_planet);

first_location = ConvoScreen:new {
	id = "first_location",
	leftDialog = "@conversation/corvette_pashna_rebel1:s_e92b0e11",--An Imperial force led by this Imperial commander was sent to Fort Tusken not long ago. Before he received his current rank, actually. We don't know why his force was there, though we speculate that they intended to research the Sand People living there. Or maybe attempt to broker some sort of deal with them. We do know it went badly and much of the Imperial force was obliterated by the Tusken Raiders. Seek out anything that might have been left behind during their retreat.
	stopConversation = "false",
	options = {}
}
corvettePashnaConvoTemplate:addScreen(first_location);

second_location = ConvoScreen:new {
	id = "second_location",
	leftDialog = "@conversation/corvette_pashna_rebel1:s_fe36e67a", --I don't have much information regarding the Mokk stronghold other than the fact that the Mokk are a Dantari tribe. The stronghold can be found on Dantooine around the northwestern edge of the planet. The Imperial commander we are investigating was known to have led a search of this stronghold looking for members of the Alliance he believed to have been hiding there.
	stopConversation = "false",
	options = {}
}
corvettePashnaConvoTemplate:addScreen(second_location);

third_location = ConvoScreen:new {
	id = "third_location",
	leftDialog = "@conversation/corvette_pashna_rebel1:s_a1ce5a7c", --A fairly new discovery, that one. It is said that the Empire has been conducting secretive experiments there with the help of the Geonosians. Possibly involving biological weapons. The laboratory can be found on Yavin IV in the northwestern part of the planet. I don't have much more information about the place.
	stopConversation = "false",
	options = {}
}
corvettePashnaConvoTemplate:addScreen(third_location);

go_get_intel = ConvoScreen:new {
	id = "go_get_intel",
	leftDialog = "@conversation/corvette_pashna_rebel1:s_49437190",--My nerves have been eased. Please hurry and return safely.
	stopConversation = "true",
	options = {}
}
corvettePashnaConvoTemplate:addScreen(go_get_intel);

hear_locations_quit = ConvoScreen:new {
	id = "hear_locations_quit",
	leftDialog = "@conversation/corvette_pashna_rebel1:s_cc2ec42b", --I am disappointed. However, I wish you well on your endeavors.
	stopConversation = "true",
	options = {}
}
corvettePashnaConvoTemplate:addScreen(hear_locations_quit);

back_already = ConvoScreen:new {
	id = "back_already",
	leftDialog = "@conversation/corvette_pashna_rebel1:s_c26ad0e8", --You have returned! I am glad to see you well. Have you found the documents I sent you out to retrieve?
	stopConversation = "false",
	options = {	}
}
corvettePashnaConvoTemplate:addScreen(back_already);

back_already_reset = ConvoScreen:new {
	id = "back_already_reset",
	leftDialog = "@conversation/corvette_pashna_rebel1:s_29542d1b", -- That is very unfortunate to hear. I hope to find someone else to help us. I'll have to take all mission related documents from you. I'm sure you understand, of course.
	stopConversation = "true",
	options = { }
}
corvettePashnaConvoTemplate:addScreen(back_already_reset);

has_intel = ConvoScreen:new {
	id = "has_intel",
	leftDialog = "@conversation/corvette_pashna_rebel1:s_9463a903", --You found the documents?
	stopConversation = "false",
	options = {}
}
corvettePashnaConvoTemplate:addScreen(has_intel);

bad_intel_1 = ConvoScreen:new {
	id = "bad_intel_1",
	leftDialog = "@conversation/corvette_pashna_rebel1:s_b0c99345",--Mmm. This isn't the correct document, however, we can still use it in our research and in our efforts against the Empire. I'll reward you for recovering them.
	stopConversation = "false",
	options = {	}
}
corvettePashnaConvoTemplate:addScreen(bad_intel_1);

bad_intel_2 = ConvoScreen:new {
	id = "bad_intel_2",
	leftDialog = "@conversation/corvette_pashna_rebel1:s_b0c99345", --Mmm. This isn't the correct document, however, we can still use it in our research and in our efforts against the Empire. I'll reward you for recovering them.
	stopConversation = "false",
	options = {}
}
corvettePashnaConvoTemplate:addScreen(bad_intel_2);

check_other_places = ConvoScreen:new {
	id = "check_other_places",
	leftDialog = "@conversation/corvette_pashna_rebel1:s_697542b9", --Indeed. Try to find those documents as quickly as possible.
	stopConversation = "true",
	options = {}
}

corvettePashnaConvoTemplate:addScreen(check_other_places);

other_documents = ConvoScreen:new {
	id = "other_documents",
	leftDialog = "@conversation/corvette_pashna_rebel1:s_3bd032cd", --I see. Which documents do you have for me?
	stopConversation = "false",
	options = {}
}
corvettePashnaConvoTemplate:addScreen(other_documents);

good_intel = ConvoScreen:new {
	id = "good_intel",
	leftDialog = "@conversation/corvette_pashna_rebel1:s_1cce61b2",--Well done. This is exactly the information we needed. Hmm... this Imperial commander is worse than expected. He must definitely be eliminated. So much so that our primary concern has changed. First priority is now to assassinate this Imperial commander. Take this travel authorization to the Rebel Alliance hideout on Corellia. Speak with Lt. Lance there and he'll give you more instructions. If you prevail, return to me for your reward.
	stopConversation = "false",
	options = {	}
}
corvettePashnaConvoTemplate:addScreen(good_intel);

go_to_corvette = ConvoScreen:new {
	id = "go_to_corvette",
	leftDialog = "@conversation/corvette_pashna_rebel1:s_47eb05e", --No. I have no further instructions for you. You'll need to present your travel authorization to Lt. Lance at the Rebel Alliance hideout on Corellia. If you succeed in your mission, return to me for your reward.
	stopConversation = "true",
	options = {}
}
corvettePashnaConvoTemplate:addScreen(go_to_corvette);

still_here = ConvoScreen:new {
	id = "still_here",
	leftDialog = "@conversation/corvette_pashna_rebel1:s_2f662226",--I see that you have returned. But why? My concern for our mission grows more by the day.
	stopConversation = "false",
	options = {}
}
corvettePashnaConvoTemplate:addScreen(still_here);

still_here_decline = ConvoScreen:new {
	id = "still_here_decline",
	leftDialog = "@conversation/corvette_pashna_rebel1:s_2d18a202", --Are you sure? I'll have to erase all progress you've made, take all remaining documents you've found, and revoke the travel authorization.
	stopConversation = "false",
	options = {
		{"@conversation/corvette_pashna_rebel1:s_ffef947e","decline_quest_reset"},--Go ahead. I still quit.
		{"@conversation/corvette_pashna_rebel1:s_7cd62c6d","changed_mind"},--In that case, I'll still continue.
	}
}
corvettePashnaConvoTemplate:addScreen(still_here_decline);

decline_quest_reset = ConvoScreen:new {
	id = "decline_quest_reset",
	leftDialog = "@conversation/corvette_pashna_rebel1:s_2be3fa16", --I am distressed. I hope to find a replacement.
	stopConversation = "true",
	options = {}
}
corvettePashnaConvoTemplate:addScreen(decline_quest_reset);

changed_mind = ConvoScreen:new {
	id = "changed_mind",
	leftDialog = "@conversation/corvette_pashna_rebel1:s_eccf8e31", -- Good. Return to your duties, soldier.
	stopConversation = "true",
	options = {}
}
corvettePashnaConvoTemplate:addScreen(changed_mind);

launch_location = ConvoScreen:new {
	id = "launch_location",
	leftDialog = "@conversation/corvette_pashna_rebel1:s_aaee7ac8", -- Go to the Rebel Alliance hideout on Corellia. Seek Lt. Lance who will accept your travel authorization and allow you to board a starship which intercept the Imperial commander on the Corellian corvette. After the Imperial commander has been eliminated and you've escaped from the corvette, I will have your reward ready.
	stopConversation = "true",
	options = {}
}
corvettePashnaConvoTemplate:addScreen(launch_location);

reward = ConvoScreen:new {
	id = "reward",
	leftDialog = "@conversation/corvette_pashna_rebel1:s_fd5fb0cf",--It was an unfortunate business, but it is at last at an end. I thank you for your part in this. Would you like your reward?
	stopConversation = "false",
	options = {
		{"@conversation/corvette_pashna_rebel1:s_cb13589","give_reward"}, --Yes, please. Thank you.
		{"@conversation/corvette_pashna_rebel1:s_615637f6","reward_notyet"} --No, not yet. Maybe later.
	}
}
corvettePashnaConvoTemplate:addScreen(reward);

reward_notyet = ConvoScreen:new {
	id = "reward_notyet",
	leftDialog = "@conversation/corvette_pashna_rebel1:s_8a5c56ae", --Whenever you're ready, let me know.
	stopConversation = "true",
	options = {}
}
corvettePashnaConvoTemplate:addScreen(reward_notyet);

give_reward = ConvoScreen:new {
	id = "give_reward",
	leftDialog = "@conversation/corvette_pashna_rebel1:s_5b812563", --Thank you again. Without your help, there would have been no end to the havoc that Imperial monster would have sown. Well done.
	stopConversation = "true",
	options = {}
}
corvettePashnaConvoTemplate:addScreen(give_reward);

cant_give_reward = ConvoScreen:new {
	id = "cant_give_reward",
	leftDialog = "@conversation/corvette_pashna_rebel1:s_2a4d0c46", --You reward is richly deserved, but you seem to have no room for it. Please clear some space and then speak with me again.
	stopConversation = "true",
	options = {}
}
corvettePashnaConvoTemplate:addScreen(cant_give_reward);

addConversationTemplate("corvettePashnaConvoTemplate", corvettePashnaConvoTemplate);

