corvetteTallonConvoTemplate = ConvoTemplate:new {
	initialScreen = "",
	templateType = "Lua",
	luaClassHandler = "ticketGiverAdarConvoHandler",
	screens = {}
}

no_business = ConvoScreen:new {
	id = "no_business",
	leftDialog = "@conversation/corvette_tallon_rebel1:s_71f656a9", -- He's still missing. We have no word at all since losing communication with him. The Empire's behind this... I just know it. One of our best pilots too.
	stopConversation = "true",
	options = {}
}
corvetteTallonConvoTemplate:addScreen(no_business);

no_faction = ConvoScreen:new {
	id = "no_faction",
	leftDialog = "@conversation/corvette_tallon_rebel1:s_3e144812", --No... no. This can't be allowed to... Oh, my apologies. I didn't see you there. More apologies, because another matter urgently demands my attention. Good bye.
	stopConversation = "true",
	options = {}
}
corvetteTallonConvoTemplate:addScreen(no_faction);

already_busy = ConvoScreen:new {
	id = "already_busy",
	leftDialog = "@conversation/corvette_tallon_rebel1:s_2dd3860f", -- Ah, you're here, but I see that you're already busy. I could've used your help. Maybe come back when you've finished your current task.
	stopConversation = "true",
	options = {}
}
corvetteTallonConvoTemplate:addScreen(already_busy);

quest_start = ConvoScreen:new {
	id = "quest_start",
	leftDialog = "@conversation/corvette_tallon_rebel1:s_f85a3545", -- Arrested... treason... Dathomir prison. It truly is a pity. One of our most trusted and well-decorated pilots has been taken prisoner by the Empire. He was arrested for a crime that was not his doing. The Empire even went as far as planting false evidence to destroy his innocence. He needs to be rescued. He has been taken to a Corellian corvette which is en route to Dathomir. I need security codes in order to assemble a team to rescue him. Will you get those keys for us?
	stopConversation = "false",
	options = {
		{"@conversation/corvette_tallon_rebel1:s_1944f1e6","quest_start1"}, -- Yes, I will
		{"@conversation/corvette_tallon_rebel1:s_df8ea53","decline_quest"} -- Not interested.
	}
}
corvetteTallonConvoTemplate:addScreen(quest_start);

quest_start1 = ConvoScreen:new {
	id = "quest_start1",
		leftDialog = "@conversation/corvette_tallon_rebel1:s_94007006", --There is hope yet! I have been informed that the security override codes I need could be in one of three locations. Based on that information, the places to seek out are a downed Bloodrazor smuggling vessel on Lok, the Imperial Warren on Dantooine and the Imperial Prison itself on Dathomir.  It will be a dangerous journey, filled with obstacles, but justice must be done. We must rescue the officer before he reaches that prison!
	stopConversation = "false",
	options = {
		{"@conversation/corvette_tallon_rebel1:s_3410977a","first_location"}, --Tell me about the Warren.
		{"@conversation/corvette_tallon_rebel1:s_57214562","second_location"}, --Tell me about the Imperial Prison.
		{"@conversation/corvette_tallon_rebel1:s_151358aa","third_location"}, -- Tell me about the downed Bloodrazor vessel.
		{"@conversation/corvette_tallon_rebel1:s_a5591c27","go_get_intel"}, -- I accept this mission.
		{"@conversation/corvette_tallon_rebel1:s_d6695e83","decline_quest_reset"},-- No thanks.
	}
}
corvetteTallonConvoTemplate:addScreen(quest_start1);

decline_quest = ConvoScreen:new {
	id = "decline_quest",
	leftDialog = "@conversation/corvette_tallon_rebel1:s_93fcbaae", -- Your answer is unfortunate. But it is your choice. May the Force be with you.
	stopConversation = "true",
	options = {}
}
corvetteTallonConvoTemplate:addScreen(decline_quest);

decline_quest_reset = ConvoScreen:new {
	id = "decline_quest_reset",
	leftDialog = "@conversation/corvette_tallon_rebel1:s_303462a1", -- I'm sorry to hear of this. I must find someone else to replace you. Good bye.
	stopConversation = "true",
	options = {}
}
corvetteTallonConvoTemplate:addScreen(decline_quest_reset);

decline_quest_reset2 = ConvoScreen:new {
	id = "decline_quest_reset2",
	leftDialog = "@conversation/corvette_tallon_rebel1:s_a24d8ba0", --your answer troubles me. Return if you change your mind. May the Force be with you.
	stopConversation = "true",
	options = {}
}
corvetteTallonConvoTemplate:addScreen(decline_quest_reset2);

which_planet = ConvoScreen:new {
	id = "which_planet",
	leftDialog = "@conversation/corvette_tallon_rebel1:s_57504441", -- I have several locations for you... places that, we think, may have the codes. Which location do you need more information on?
	stopConversation = "false",
	options = {
		{"@conversation/corvette_tallon_rebel1:s_3410977a","first_location"}, --Tell me about the Warren.
		{"@conversation/corvette_tallon_rebel1:s_57214562","second_location"}, --Tell me about the Imperial Prison.
		{"@conversation/corvette_tallon_rebel1:s_151358aa","third_location"}, -- Tell me about the downed Bloodrazor vessel.
		{"@conversation/corvette_tallon_rebel1:s_a5591c27","go_get_intel"}, -- I accept this mission.
		{"@conversation/corvette_tallon_rebel1:s_d6695e83","decline_quest_reset"},-- No thanks.
	}
}
corvetteTallonConvoTemplate:addScreen(which_planet);

first_location = ConvoScreen:new {
	id = "first_location",
	leftDialog = "@conversation/corvette_tallon_rebel1:s_439048cf",--The Empire has conducted many top secret operations at this location. Unfortunately, it has been very difficult to penetrate the defenses of the Warren on our side. We'll need a cunning Alliance operative to enter the establishment and find those codes. The Warren is on Dantooine.
	stopConversation = "false",
	options = {
		{"@conversation/corvette_tallon_rebel1:s_3410977a","first_location"}, --Tell me about the Warren.
		{"@conversation/corvette_tallon_rebel1:s_57214562","second_location"}, --Tell me about the Imperial Prison.
		{"@conversation/corvette_tallon_rebel1:s_151358aa","third_location"}, -- Tell me about the downed Bloodrazor vessel.
		{"@conversation/corvette_tallon_rebel1:s_a5591c27","go_get_intel"}, -- I accept this mission.
		{"@conversation/corvette_tallon_rebel1:s_d6695e83","decline_quest_reset"},-- No thanks.
	}
}
corvetteTallonConvoTemplate:addScreen(first_location);

second_location = ConvoScreen:new {
	id = "second_location",
	leftDialog = "@conversation/corvette_tallon_rebel1:s_e1aa98dd", --Ah the Imperial Prison of Dathomir. Many who are arrested for their 'sins' against the Empire are taken to this location. Most are never seen again. We must not allow our officer to meet the same fate. We've lost too many men as it is! Since the Imperial Prison is where they are taking him, it wouldn't be surprising to find information about his current location there.
	stopConversation = "false",
	options = {
		{"@conversation/corvette_tallon_rebel1:s_3410977a","first_location"}, --Tell me about the Warren.
		{"@conversation/corvette_tallon_rebel1:s_57214562","second_location"}, --Tell me about the Imperial Prison.
		{"@conversation/corvette_tallon_rebel1:s_151358aa","third_location"}, -- Tell me about the downed Bloodrazor vessel.
		{"@conversation/corvette_tallon_rebel1:s_a5591c27","go_get_intel"}, -- I accept this mission.
		{"@conversation/corvette_tallon_rebel1:s_d6695e83","decline_quest_reset"},-- No thanks.
	}
}
corvetteTallonConvoTemplate:addScreen(second_location);

third_location = ConvoScreen:new {
	id = "third_location",
	leftDialog = "@conversation/corvette_tallon_rebel1:s_a073eacd", --The Bloodrazors are a mysterious band of pirates and criminals. It is said they have access to radar technology that can detect certain unique codes used by ships that approach within their range. This is my hope. The downed Bloodrazor vessel is on Lok though the exact location is unknown.
	stopConversation = "false",
	options = {
		{"@conversation/corvette_tallon_rebel1:s_3410977a","first_location"}, --Tell me about the Warren.
		{"@conversation/corvette_tallon_rebel1:s_57214562","second_location"}, --Tell me about the Imperial Prison.
		{"@conversation/corvette_tallon_rebel1:s_151358aa","third_location"}, -- Tell me about the downed Bloodrazor vessel.
		{"@conversation/corvette_tallon_rebel1:s_a5591c27","go_get_intel"}, -- I accept this mission.
		{"@conversation/corvette_tallon_rebel1:s_d6695e83","decline_quest_reset"},-- No thanks.
	}
}
corvetteTallonConvoTemplate:addScreen(third_location);

go_get_intel = ConvoScreen:new {
	id = "go_get_intel",
	leftDialog = "@conversation/corvette_tallon_rebel1:s_90b2e0c5", --You're our only hope in this situation. You have your orders, soldier.
	stopConversation = "true",
	options = {}
}
corvetteTallonConvoTemplate:addScreen(go_get_intel);

back_already = ConvoScreen:new {
	id = "back_already",
	leftDialog = "@conversation/corvette_tallon_rebel1:s_953e3f2c", -- I see you have returned. Have you found the codes I'm looking for? Time is critical.
	stopConversation = "false",
	options = {
		{"@conversation/corvette_tallon_rebel1:s_4d865d46","has_intel"},--I found several interesting documents and codes.
		{"@conversation/corvette_tallon_rebel1:s_60c4f974","which_planet"}, -- Where do I go?
		{"@conversation/corvette_tallon_rebel1:s_e70aed96","decline_quest_reset"} -- I can't continue. Please erase all records of my progress on this mission.
	}
}
corvetteTallonConvoTemplate:addScreen(back_already);

back_already_reset = ConvoScreen:new {
	id = "back_already_reset",
	leftDialog = "@conversation/corvette_tallon_rebel1:s_ed430e90", -- Didn't take ye fer a quitter, guess I wus wrong. Dis not good news, not at all. I'm gonna take all everything about dis from ye. Ye keep nuthin.
	stopConversation = "true",
	options = { }
}
corvetteTallonConvoTemplate:addScreen(back_already_reset);

has_intel = ConvoScreen:new {
	id = "has_intel",
	leftDialog = "@conversation/corvette_tallon_rebel1:s_75b09ea1", --Oh? What have you found?
	stopConversation = "false",
	options = {
		{"@conversation/corvette_tallon_rebel1:s_9b6fd578","bad_intel_1"}, --Show the Imperial Resignation Form.
		{"@conversation/corvette_tallon_rebel1:s_b0e6356e","bad_intel_2"}, --Show the Imperial Purchase Order.
		{"@conversation/corvette_tallon_rebel1:s_135bf1fb","good_intel"}, --Show the Security Override Codes.
		{"@conversation/corvette_tallon_rebel1:s_67499366","go_to_corvette"},--I am leaving for the Corellian corvette.
		{"@conversation/corvette_tallon_rebel1:s_a128e067","check_other_places"},--Looks like I have more to do.
	}
}
corvetteTallonConvoTemplate:addScreen(has_intel);

bad_intel_1 = ConvoScreen:new {
	id = "bad_intel_1",
	leftDialog = "@conversation/corvette_tallon_rebel1:s_b2503658", --This isn't what I'm looking for. I need the security codes as soon as possible! Return to the locations I gave you and find those codes!  Arrgh... well... okay, this is potentially useful information. I'll reward you for finding it. But then you must go find those security codes.
	stopConversation = "false",
	options = {
		{"@conversation/corvette_tallon_rebel1:s_9b6fd578","bad_intel_1"}, --Show the Imperial Resignation Form.
		{"@conversation/corvette_tallon_rebel1:s_b0e6356e","bad_intel_2"}, --Show the Imperial Purchase Order.
		{"@conversation/corvette_tallon_rebel1:s_135bf1fb","good_intel"}, --Show the Security Override Codes.
		{"@conversation/corvette_tallon_rebel1:s_67499366","go_to_corvette"},--I am leaving for the Corellian corvette.
		{"@conversation/corvette_tallon_rebel1:s_a128e067","check_other_places"},--Looks like I have more to do.
	}
}
corvetteTallonConvoTemplate:addScreen(bad_intel_1);

bad_intel_2 = ConvoScreen:new {
	id = "bad_intel_2",
	leftDialog = "@conversation/corvette_tallon_rebel1:s_581c3ef2", -- This isn't what I'm looking for. I need the security codes as soon as possible! Bah... well... okay, this is potentially useful information. I'll reward you for finding it. But then you must go find those security codes.
	stopConversation = "false",
	options = {
		{"@conversation/corvette_tallon_rebel1:s_9b6fd578","bad_intel_1"}, --Show the Imperial Resignation Form.
		{"@conversation/corvette_tallon_rebel1:s_b0e6356e","bad_intel_2"}, --Show the Imperial Purchase Order.
		{"@conversation/corvette_tallon_rebel1:s_135bf1fb","good_intel"}, --Show the Security Override Codes.
		{"@conversation/corvette_tallon_rebel1:s_67499366","go_to_corvette"},--I am leaving for the Corellian corvette.
		{"@conversation/corvette_tallon_rebel1:s_a128e067","check_other_places"},--Looks like I have more to do.
	}
}
corvetteTallonConvoTemplate:addScreen(bad_intel_2);

check_other_places = ConvoScreen:new {
	id = "check_other_places",
	leftDialog = "@conversation/corvette_tallon_rebel1:s_daf0c91a", --Indeed. We need those codes as soon as possible.
	stopConversation = "true",
	options = {}
}

corvetteTallonConvoTemplate:addScreen(check_other_places);

other_documents = ConvoScreen:new {
	id = "other_documents",
	leftDialog = "@conversation/corvette_tallon_rebel1:s_14963f17", -- I see. Which ones do you have?
	stopConversation = "false",
	options = {
		{"@conversation/corvette_tallon_rebel1:s_9b6fd578","bad_intel_1"}, --Show the Imperial Resignation Form.
		{"@conversation/corvette_tallon_rebel1:s_b0e6356e","bad_intel_2"}, --Show the Imperial Purchase Order.
		{"@conversation/corvette_tallon_rebel1:s_135bf1fb","good_intel"}, --Show the Security Override Codes.
		{"@conversation/corvette_tallon_rebel1:s_67499366","go_to_corvette"},--I am leaving for the Corellian corvette.
		{"@conversation/corvette_tallon_rebel1:s_a128e067","check_other_places"},--Looks like I have more to do.
	}
}
corvetteTallonConvoTemplate:addScreen(other_documents);

good_intel = ConvoScreen:new {
	id = "good_intel",
	leftDialog = "@conversation/corvette_tallon_rebel1:s_62379ba", -- Ahh, the codes! We now have the exact location of the Corellian corvette he is on. Here, take this travel authorization to the Rebel hideout on Corellia and meet with Lt. Lance there. He will provide you transport on a starship which is capable of intercepting the Corellian corvette in deep space. Once your mission has been successfully completed, return to me for a reward. I wish you haste and luck on your journey.
	stopConversation = "false",
	options = {
		{"@conversation/corvette_tallon_rebel1:s_67499366","go_to_corvette"},--I am leaving for the Corellian corvette.
		{"@conversation/corvette_tallon_rebel1:s_2f26b4c4","other_documents"}, -- I still have documents for you.
	}
}
corvetteTallonConvoTemplate:addScreen(good_intel);

go_to_corvette = ConvoScreen:new {
	id = "go_to_corvette",
	leftDialog = "@conversation/corvette_tallon_rebel1:s_7cea4aed", --Excellent! I wish you luck and haste in your journey. Succeed in your mission and then return to me for your reward. May the Force be with you.
	stopConversation = "true",
	options = {}
}
corvetteTallonConvoTemplate:addScreen(go_to_corvette);

still_here = ConvoScreen:new {
	id = "still_here",
	leftDialog = "@conversation/corvette_tallon_rebel1:s_7860ffca", --   I am curious as why you have returned. Is there some sort of problem?
	stopConversation = "false",
	options = {
		{"@conversation/corvette_tallon_rebel1:s_3925fbc0","with_shuttle"}, --I forgot the location of our contact.
		{"@conversation/corvette_tallon_rebel1:s_e70aed96","stillhere_quit"}, -- I can't continue. Please erase all records of my progress on this mission.
		{"@conversation/corvette_tallon_rebel1:s_2f26b4c4","other_documents"}, -- I still have documents for you.
	}
}
corvetteTallonConvoTemplate:addScreen(still_here);

stillhere_quit = ConvoScreen:new {
	id = "stillhere_quit",
	leftDialog = "@conversation/corvette_tallon_rebel1:s_b0f80f89", -- Are you sure you wish to quit? I will have to revoke the travel authorization. It is for special operatives only. And I'll have to take any remaining documents you may have relating to this mission.
	stopConversation = "false",
	options = {
		{"@conversation/corvette_tallon_rebel1:s_b0da26cf","disappointed_doit"}, --  I'm sure.
		{"@conversation/corvette_tallon_rebel1:s_4440ce87","decline_quest_reset"}, --I changed my mind.
	}
}
corvetteTallonConvoTemplate:addScreen(stillhere_quit);

disappointed_doit = ConvoScreen:new {
	id = "disappointed_doit",
	leftDialog = "@conversation/corvette_tallon_rebel1:s_d50be1f6", -- Good. Be swift in dealing with this situation.
	stopConversation = "true",
	options = {}
}
corvetteTallonConvoTemplate:addScreen(disappointed_doit);

with_shuttle = ConvoScreen:new {
	id = "with_shuttle",
	leftDialog = "@conversation/corvette_tallon_rebel1:s_49139b6", -- Lt. Lance is at the Rebel hideout on Corellia. He will provide you transportation to the Corellian corvette which houses our well-decorated pilot. We need that pilot returned to us as soon as possible. Once your mission has been successfully completed, return to me for a reward.
	stopConversation = "true",
	options = {}
}
corvetteTallonConvoTemplate:addScreen(with_shuttle);

reward = ConvoScreen:new {
	id = "reward",
	leftDialog = "@conversation/corvette_tallon_rebel1:s_5f61380e", -- I cannot thank you enough for your actions. You have not only rescued a pilot of the Alliance, but also a friend. I am pleased to be able to reward you.
	stopConversation = "false",
	options = {
		{"@conversation/corvette_tallon_rebel1:s_d938179c","give_reward"}, --Great. Let's see this reward then.
		{"@conversation/corvette_tallon_rebel1:s_60bce77f","reward_notyet"} --Reward? Not now. I'll return later.
	}
}
corvetteTallonConvoTemplate:addScreen(reward);

reward_notyet = ConvoScreen:new {
	id = "reward_notyet",
	leftDialog = "@conversation/corvette_tallon_rebel1:s_80747fa2", --  I see. Later it shall be then. Return whenever you are ready.
	stopConversation = "true",
	options = {}
}
corvetteTallonConvoTemplate:addScreen(reward_notyet);

give_reward = ConvoScreen:new {
	id = "give_reward",
	leftDialog = "@conversation/corvette_tallon_rebel1:s_ae9868f4", --[smiling] Eager as always. You've earned this... and the gratitude of the Alliance.
	stopConversation = "true",
	options = {}
}
corvetteTallonConvoTemplate:addScreen(give_reward);

cant_give_reward = ConvoScreen:new {
	id = "cant_give_reward",
	leftDialog = "@conversation/corvette_tallon_rebel1:s_5f449362", -- Ah. I'd like to give this reward to you, but you don't have room to carry it. You'll need to make some space and then speak with me again.
	stopConversation = "true",
	options = {}
}
corvetteTallonConvoTemplate:addScreen(cant_give_reward);

addConversationTemplate("corvetteTallonConvoTemplate", corvetteTallonConvoTemplate);

