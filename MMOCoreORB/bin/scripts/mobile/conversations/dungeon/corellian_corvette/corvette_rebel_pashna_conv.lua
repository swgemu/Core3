corvettePashnaConvoTemplate = ConvoTemplate:new {
	initialScreen = "",
	templateType = "Lua",
	luaClassHandler = "ticketGiverPashnaConvoHandler",
	screens = {}
}

no_business = ConvoScreen:new {
	id = "no_business",
	leftDialog = "@conversation/corvette_pashna_rebel1:s_ed0270a5", --That Imperial Commander must be stopped, but I'm not yet convinced that killing him is the only option. He's violent and ruthless and definitely a major threat, but assassinating him seems to lower us to his level. But perhaps I'm being naive... 
	stopConversation = "true",
	options = {}
}
corvettePashnaConvoTemplate:addScreen(no_business);

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

quest_start = ConvoScreen:new {
	id = "quest_start",
	leftDialog = "@conversation/corvette_pashna_rebel1:s_bbd30f60",--You couldn't have come at a more distressing time, my friend.
	stopConversation = "false",
	options = {
		{"@conversation/corvette_pashna_rebel1:s_d3412303","quest_start1"},-- What seems to be the problem?
		{"@conversation/corvette_pashna_rebel1:s_b89af325","decline_quest"} --Be that as it may, good-bye.
	}
}
corvettePashnaConvoTemplate:addScreen(quest_start);

quest_start1 = ConvoScreen:new {
	id = "quest_start1",
	leftDialog = "@conversation/corvette_pashna_rebel1:s_77da0881",--You are one of us, therefore I can trust you with this information. It seems that one of our Corellian corvettes has been boarded and seized by a ruthless Imperial commander. This Imperial commander is bent on guiding the ship toward Talus and crashing it into our base there. My first priority is to retake the ship before it crashes into our base. And second is to... well... is to assassinate the Imperial commander responsible for this threat.
	stopConversation = "false",
	options = {
		{"@conversation/corvette_pashna_rebel1:s_e10e18f5","quest_start2"},--Do you need any help with this situation?
		{"@conversation/corvette_pashna_rebel1:s_f7e9bbb3","decline_quest_reset"},--Good luck with that. I'm not interested in getting involved.
	}
}
corvettePashnaConvoTemplate:addScreen(quest_start1);

quest_start2 = ConvoScreen:new {
	id = "quest_start2",
	leftDialog = "@conversation/corvette_pashna_rebel1:s_73f241bd",--In fact, I do. Before we take any measure of action, I need more information regarding this Imperial commander, his background. I can't issue an assassination without knowing he, without a doubt, warrants such a demise. I have reason to believe that such information exists at one of three places: Fort Tusken on Tatooine, a Geonosian laboratory on Yavin IV, or Lord Nyax's compound on Corellia. Can you see to this?
	stopConversation = "false",
	options = {
		{"@conversation/corvette_pashna_rebel1:s_ba7150b1","quest_start3"},--Yes, I will help you.
		{"@conversation/corvette_pashna_rebel1:s_436d636d","decline_quest2"},--That sounds like a problem. I wish I could help, but really I don't care.
	}
}
corvettePashnaConvoTemplate:addScreen(quest_start2);

quest_start3 = ConvoScreen:new {
	id = "quest_start3",
	leftDialog = "@conversation/corvette_pashna_rebel1:s_ffb796fa",--I am relieved and thankful for your eager assistance. Seek out the documents in the locations I mentioned. If you need more information about any of them, please let me know.
	stopConversation = "false",
	options = {
		{"@conversation/corvette_pashna_rebel1:s_26d40ca6","first_location"}, --Tell me more about Fort Tusken and why any information would be there.
		{"Tell me more about Lord Nyax's compound on Corellia.","second_location"}, --Tell me more about Lord Nyax's compound on Corellia.
		{"@conversation/corvette_pashna_rebel1:s_2534c3e3","third_location"}, --Tell me more about the Geonosian Bunker.
		{"@conversation/corvette_pashna_rebel1:s_a5591c27","go_get_intel"}, -- I accept this mission.
		{"@conversation/corvette_pashna_rebel1:s_36cb0506","decline_quest_reset"},--No, maybe another time. Good bye.
	}
}--@conversation/corvette_pashna_rebel1:s_98df29e5
corvettePashnaConvoTemplate:addScreen(quest_start3);

decline_quest = ConvoScreen:new {
	id = "decline_quest",
	leftDialog = "@conversation/corvette_pashna_rebel1:s_fe450b8a", -- It probably is best that you go. I must concentrate on the tasks at hand.
	stopConversation = "true",
	options = {}
}
corvettePashnaConvoTemplate:addScreen(decline_quest);

decline_quest2 = ConvoScreen:new {
	id = "decline_quest2",
	leftDialog = "@conversation/corvette_pashna_rebel1:s_7384b0d4", --I see. Such apathy is what holds our efforts back from true success. But then, I suppose the idea of assassinating another person can be difficult to accept. I understand your reservations.
	stopConversation = "true",
	options = {}
}
corvettePashnaConvoTemplate:addScreen(decline_quest2);

decline_quest_reset = ConvoScreen:new {
	id = "decline_quest_reset",
	leftDialog = "@conversation/corvette_pashna_rebel1:s_29542d1b", --That is very unfortunate to hear. I hope to find someone else to help us. I'll have to take all mission related documents from you. I'm sure you understand, of course.
	stopConversation = "true",
	options = {}
}
corvettePashnaConvoTemplate:addScreen(decline_quest_reset);

decline_quest_reset2 = ConvoScreen:new {
	id = "decline_quest_reset2",
	leftDialog = "@conversation/corvette_pashna_rebel1:s_cb6caf3", --That is sad news, but I will do so. It will be difficult to replace you. I'll have to retrieve all documents and data gathered for this mission from you. Sorry, but it's required.
	stopConversation = "true",
	options = {}
}
corvettePashnaConvoTemplate:addScreen(decline_quest_reset2);

which_planet = ConvoScreen:new {
	id = "which_planet",
	leftDialog = "@conversation/corvette_pashna_rebel1:s_89df7355",--Which location would you like more information about?
	stopConversation = "false",
	options = {
		{"@conversation/corvette_pashna_rebel1:s_26d40ca6","first_location"}, --Tell me more about Fort Tusken and why any information would be there.
		{"@conversation/corvette_pashna_rebel1:s_98df29e5","second_location"}, --Tell me more about Lord Nyax's compound on Corellia.
		{"@conversation/corvette_pashna_rebel1:s_2534c3e3","third_location"}, --Tell me more about the Geonosian Bunker.
		{"@conversation/corvette_pashna_rebel1:s_a5591c27","go_get_intel"}, -- I accept this mission.
		{"@conversation/corvette_pashna_rebel1:s_36cb0506","decline_quest_reset"},--No, maybe another time. Good bye.
	}
}
corvettePashnaConvoTemplate:addScreen(which_planet);

first_location = ConvoScreen:new {
	id = "first_location",
	leftDialog = "@conversation/corvette_pashna_rebel1:s_e92b0e11",--An Imperial force led by this Imperial commander was sent to Fort Tusken not long ago. Before he received his current rank, actually. We don't know why his force was there, though we speculate that they intended to research the Sand People living there. Or maybe attempt to broker some sort of deal with them. We do know it went badly and much of the Imperial force was obliterated by the Tusken Raiders. Seek out anything that might have been left behind during their retreat. 
	stopConversation = "false",
	options = {
		{"@conversation/corvette_pashna_rebel1:s_26d40ca6","first_location"}, --Tell me more about Fort Tusken and why any information would be there.
		{"@conversation/corvette_pashna_rebel1:s_98df29e5","second_location"}, --Tell me more about Lord Nyax's compound on Corellia.
		{"@conversation/corvette_pashna_rebel1:s_2534c3e3","third_location"}, --Tell me more about the Geonosian Bunker.
		{"@conversation/corvette_pashna_rebel1:s_a5591c27","go_get_intel"}, -- I accept this mission.
		{"@conversation/corvette_pashna_rebel1:s_36cb0506","decline_quest_reset"},--No, maybe another time. Good bye.
	}
}
corvettePashnaConvoTemplate:addScreen(first_location);

second_location = ConvoScreen:new {
	id = "second_location",
	leftDialog = "@conversation/corvette_pashna_rebel1:s_fe36e67a",
	stopConversation = "false",
	options = {
		{"@conversation/corvette_pashna_rebel1:s_26d40ca6","first_location"}, --Tell me more about Fort Tusken and why any information would be there.
		{"@conversation/corvette_pashna_rebel1:s_98df29e5","second_location"}, --Tell me more about Lord Nyax's compound on Corellia.
		{"@conversation/corvette_pashna_rebel1:s_2534c3e3","third_location"}, --Tell me more about the Geonosian Bunker.
		{"@conversation/corvette_pashna_rebel1:s_a5591c27","go_get_intel"}, -- I accept this mission.
		{"@conversation/corvette_pashna_rebel1:s_36cb0506","decline_quest_reset"},--No, maybe another time. Good bye.
	}
}
corvettePashnaConvoTemplate:addScreen(second_location);

third_location = ConvoScreen:new {
	id = "third_location",
	leftDialog = "@conversation/corvette_pashna_rebel1:s_a1ce5a7c", --A fairly new discovery, that one. It is said that the Empire has been conducting secretive experiments there with the help of the Geonosians. Possibly involving biological weapons. The laboratory can be found on Yavin IV in the northwestern part of the planet. I don't have much more information about the place.
	stopConversation = "false",
	options = {
		{"@conversation/corvette_pashna_rebel1:s_26d40ca6","first_location"}, --Tell me more about Fort Tusken and why any information would be there.
		{"@conversation/corvette_pashna_rebel1:s_98df29e5","second_location"}, --Tell me more about Lord Nyax's compound on Corellia.
		{"@conversation/corvette_pashna_rebel1:s_2534c3e3","third_location"}, --Tell me more about the Geonosian Bunker.
		{"@conversation/corvette_pashna_rebel1:s_a5591c27","go_get_intel"}, -- I accept this mission.
		{"@conversation/corvette_pashna_rebel1:s_36cb0506","decline_quest_reset"},--No, maybe another time. Good bye.
	}
}
corvettePashnaConvoTemplate:addScreen(third_location);

go_get_intel = ConvoScreen:new {
	id = "go_get_intel",
	leftDialog = "@conversation/corvette_pashna_rebel1:s_49437190",--My nerves have been eased. Please hurry and return safely.
	stopConversation = "true",
	options = {}
}
corvettePashnaConvoTemplate:addScreen(go_get_intel);

back_already = ConvoScreen:new {
	id = "back_already",
	leftDialog = "@conversation/corvette_pashna_rebel1:s_c26ad0e8", --You have returned! I am glad to see you well. Have you found the documents I sent you out to retrieve?
	stopConversation = "false",
	options = {
		{"@conversation/corvette_pashna_rebel1:s_aa504b9e","has_intel"},--I think I've found something...
		{"@conversation/corvette_pashna_rebel1:s_278c1c25","which_planet"},--Not yet. I need more information about the locations I'm to search.
		{"@conversation/corvette_pashna_rebel1:s_1729866a","decline_quest_reset"} --I've decided to abort the mission. Please erase all records of my progress.
	}
}
corvettePashnaConvoTemplate:addScreen(back_already);

back_already_reset = ConvoScreen:new {
	id = "back_already_reset",
	leftDialog = "@conversation/corvette_pashna_rebel1:s_ed430e90", -- Didn't take ye fer a quitter, guess I wus wrong. Dis not good news, not at all. I'm gonna take all everything about dis from ye. Ye keep nuthin.
	stopConversation = "true",
	options = { }
}
corvettePashnaConvoTemplate:addScreen(back_already_reset);

has_intel = ConvoScreen:new {
	id = "has_intel",
	leftDialog = "@conversation/corvette_pashna_rebel1:s_9463a903", --You found the documents?
	stopConversation = "false",
	options = {
		{"@conversation/corvette_pashna_rebel1:s_8b325a7c","bad_intel_1"}, --Show Recall Notice.
		{"@conversation/corvette_pashna_rebel1:s_f62f461c","bad_intel_2"}, --Show Prisoner Transfer Orders.
		{"@conversation/corvette_pashna_rebel1:s_bb2081d2","good_intel"}, --Show Imperial Dossier.
		{"@conversation/corvette_pashna_rebel1:s_6992624d","go_to_corvette"},--I am heading to the Corellian corvette. Anything else?
		{"@conversation/corvette_pashna_rebel1:s_a128e067","check_other_places"},--Looks like I have more to do.
	}
}
corvettePashnaConvoTemplate:addScreen(has_intel);

bad_intel_1 = ConvoScreen:new {
	id = "bad_intel_1",
	leftDialog = "@conversation/corvette_pashna_rebel1:s_b0c99345",--Mmm. This isn't the correct document, however, we can still use it in our research and in our efforts against the Empire. I'll reward you for recovering them.
	stopConversation = "false",
	options = {
		{"@conversation/corvette_pashna_rebel1:s_8b325a7c","bad_intel_1"}, --Show Recall Notice.
		{"@conversation/corvette_pashna_rebel1:s_f62f461c","bad_intel_2"}, --Show Prisoner Transfer Orders.
		{"@conversation/corvette_pashna_rebel1:s_bb2081d2","good_intel"}, --Show Imperial Dossier.
		{"@conversation/corvette_pashna_rebel1:s_6992624d","go_to_corvette"},--I am heading to the Corellian corvette. Anything else?
		{"@conversation/corvette_pashna_rebel1:s_a128e067","check_other_places"},--Looks like I have more to do.
	}
}
corvettePashnaConvoTemplate:addScreen(bad_intel_1);

bad_intel_2 = ConvoScreen:new {
	id = "bad_intel_2",
	leftDialog = "@conversation/corvette_pashna_rebel1:s_b0c99345", --Mmm. This isn't the correct document, however, we can still use it in our research and in our efforts against the Empire. I'll reward you for recovering them.
	stopConversation = "false",
	options = {
		{"@conversation/corvette_pashna_rebel1:s_8b325a7c","bad_intel_1"}, --Show Recall Notice.
		{"@conversation/corvette_pashna_rebel1:s_f62f461c","bad_intel_2"}, --Show Prisoner Transfer Orders.
		{"@conversation/corvette_pashna_rebel1:s_bb2081d2","good_intel"}, --Show Imperial Dossier.
		{"@conversation/corvette_pashna_rebel1:s_6992624d","go_to_corvette"},--I am heading to the Corellian corvette. Anything else?
		{"@conversation/corvette_pashna_rebel1:s_a128e067","check_other_places"},--Looks like I have more to do.
	}
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
	options = {
		{"@conversation/corvette_pashna_rebel1:s_8b325a7c","bad_intel_1"}, --Show Recall Notice.
		{"@conversation/corvette_pashna_rebel1:s_f62f461c","bad_intel_2"}, --Show Prisoner Transfer Orders.
		{"@conversation/corvette_pashna_rebel1:s_bb2081d2","good_intel"}, --Show Imperial Dossier.
		{"@conversation/corvette_pashna_rebel1:s_6992624d","go_to_corvette"},--I am heading to the Corellian corvette. Anything else?
		{"@conversation/corvette_pashna_rebel1:s_a128e067","check_other_places"},--Looks like I have more to do.
	}
}
corvettePashnaConvoTemplate:addScreen(other_documents);

good_intel = ConvoScreen:new {
	id = "good_intel",
	leftDialog = "@conversation/corvette_pashna_rebel1:s_1cce61b2",--Well done. This is exactly the information we needed. Hmm... this Imperial commander is worse than expected. He must definitely be eliminated. So much so that our primary concern has changed. First priority is now to assassinate this Imperial commander. Take this travel authorization to the Rebel Alliance hideout on Corellia. Speak with Lt. Lance there and he'll give you more instructions. If you prevail, return to me for your reward.
	stopConversation = "false",
	options = {
		{"@conversation/corvette_pashna_rebel1:s_6992624d","go_to_corvette"},--I am heading to the Corellian corvette. Anything else?
		{"@conversation/corvette_pashna_rebel1:s_2f26b4c4","other_documents"},--I still have documents for you.
	}
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
	options = {
		{"@conversation/corvette_pashna_rebel1:s_60c4f974","with_shuttle"}, --	Where do I go?
		{"@conversation/corvette_pashna_rebel1:s_32abdf15","stillhere_quit"},--I can't do this anymore. I have to resign from the mission.
		{"@conversation/corvette_pashna_rebel1:s_2f26b4c4","other_documents"},--I still have documents for you.
	}
}
corvettePashnaConvoTemplate:addScreen(still_here);

stillhere_quit = ConvoScreen:new {
	id = "stillhere_quit",
	leftDialog = "@conversation/corvette_pashna_rebel1:s_fb051f63", --Are you certain? Very well. But your progress will be erased, any remaining documents will be confiscated, and the travel authorization will be revoked. If you change you mind and decide to try again, you'll have to start from the beginning.
	stopConversation = "false",
	options = {
		{"@conversation/corvette_pashna_rebel1:s_b4b735ef","decline_quest_reset"},--That's okay. I cannot continue.
		{"@conversation/corvette_pashna_rebel1:s_b6a784f4","stillhere_changemind"},--Er... maybe I'll do it. Or at least think about it.
	}
}
corvettePashnaConvoTemplate:addScreen(stillhere_quit);

stillhere_changemind = ConvoScreen:new {
	id = "stillhere_changemind",
	leftDialog = "@conversation/corvette_pashna_rebel1:s_1b28b4c", -- There is hope yet. Good luck on your mission.
	stopConversation = "true",
	options = {}
}
corvettePashnaConvoTemplate:addScreen(stillhere_changemind);

with_shuttle = ConvoScreen:new {
	id = "with_shuttle",
	leftDialog = "@conversation/corvette_pashna_rebel1:s_2373d61a", --Lt. Lance at the Rebel hideout on Corellia is waiting to meet you. He will provide transportation which will enable you to intercept the stolen Corellian corvette. After you've victoriously completed your mission, return to me for a reward.
	stopConversation = "true",
	options = {}
}
corvettePashnaConvoTemplate:addScreen(with_shuttle);

reward = ConvoScreen:new {
	id = "reward",
	leftDialog = "@conversation/corvette_pashna_rebel1:s_fd5fb0cf",--It was an unfortunate business, but it is at last at an end. I thank you for your part in this. Would you like your reward?
	stopConversation = "false",
	options = {
		{"@conversation/corvette_pashna_rebel1:s_cb13589","give_reward"}, --Yes, please. Thank you.
		{"@conversation/corvette_pashna_rebel1:s_823e1fa","reward_notyet"} --No, I'm not yet ready for it.
	}
}
corvettePashnaConvoTemplate:addScreen(reward);

reward_notyet = ConvoScreen:new {
	id = "reward_notyet",
	leftDialog = "@conversation/corvette_pashna_rebel1:s_a539245b", --I see. Well, whenever you're ready, just come talk to me.
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

