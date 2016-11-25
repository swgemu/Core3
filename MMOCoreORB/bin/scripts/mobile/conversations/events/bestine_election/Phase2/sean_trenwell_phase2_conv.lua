seanTrenwellPhase2ConvoTemplate = ConvoTemplate:new {
	initialScreen = "",
	templateType = "Lua",
	luaClassHandler = "seanTrenwellPhase2ConvoHandler",
	screens = {}
}

notInOffice_noElection = ConvoScreen:new {
	id = "notInOffice_noElection",
	leftDialog = "@conversation/sean_trenwell:s_6718926b", --Well, I lost the election, but there's always next time. I still have many good ideas for Bestine. You should come back when the next election starts. In fact, the townsfolk usually talk about things like this when they happen. Be sure to talk to them.
	stopConversation = "true",
	options = {}
}
seanTrenwellPhase2ConvoTemplate:addScreen(notInOffice_noElection);

disk_to_hutt = ConvoScreen:new {
	id = "disk_to_hutt",
	leftDialog = "@conversation/sean_trenwell:s_2810bcdc", --How could you give that disk to someone working for Jabba the Hutt??!! My career is in serious jeopardy because of you! I knew I couldn't trust you. Get out of here!!
	stopConversation = "true",
	options = {}
}
seanTrenwellPhase2ConvoTemplate:addScreen(disk_to_hutt);

sean_inOffice = ConvoScreen:new {
	id = "sean_inOffice",
	leftDialog = "@conversation/sean_trenwell:s_7f70fe38", --Now that I'm in office, I can finally set some of my ideas into action. The marketplace could definitely use some attention, and I should make sure everything at the museum is going well.
	stopConversation = "false",
	options = {}
}
seanTrenwellPhase2ConvoTemplate:addScreen(sean_inOffice);

inOffice_alreadyReceivedReward = ConvoScreen:new {
	id = "inOffice_alreadyReceivedReward",
	leftDialog = "@conversation/sean_trenwell:s_c27445f0", --Reward? I think not. You already received one.
	stopConversation = "true",
	options = {}
}
seanTrenwellPhase2ConvoTemplate:addScreen(inOffice_alreadyReceivedReward);

inOffice_giveReward = ConvoScreen:new {
	id = "inOffice_giveReward",
	leftDialog = "@conversation/sean_trenwell:s_f81b7edd", --Oh yeah! Again I thank you for the help and for your support, I've prepared a little gift for you.
	stopConversation = "true",
	options = {}
}
seanTrenwellPhase2ConvoTemplate:addScreen(inOffice_giveReward);

inOffice_giveReward_noroom = ConvoScreen:new {
	id = "inOffice_giveReward_noroom",
	leftDialog = "@conversation/sean_trenwell:s_88b2f5bd", --I have a nice reward for you, but you don't seem to have room to take it. Please return after making some room in your inventory.
	stopConversation = "true",
	options = {}
}
seanTrenwellPhase2ConvoTemplate:addScreen(inOffice_giveReward_noroom);

inOffice_giveHistoryReward_noroom_returned = ConvoScreen:new {
	id = "inOffice_giveHistoryReward_noroom_returned",
	leftDialog = "@conversation/sean_trenwell:s_64f4dd40", -- I'm glad you're back, but you still don't have room. You need to have space in your inventory. Please come speak to me when you do.
	stopConversation = "true",
	options = {}
}
seanTrenwellPhase2ConvoTemplate:addScreen(inOffice_giveHistoryReward_noroom_returned);

inOffice_giveHistoryReward = ConvoScreen:new {
	id = "inOffice_giveHistoryReward",
	leftDialog = "@conversation/sean_trenwell:s_b893398e", --Ah good to see you again. Please, take this as a token of my gratitude.
	stopConversation = "true",
	options = {}
}
seanTrenwellPhase2ConvoTemplate:addScreen(inOffice_giveHistoryReward);

inOffice_HowsWork = ConvoScreen:new {
	id = "inOffice_HowsWork",
	leftDialog = "@conversation/sean_trenwell:s_c1c018c3", --Good for you. I always like to see people taking an interest in politics.
	stopConversation = "true",
	options = {}
}
seanTrenwellPhase2ConvoTemplate:addScreen(inOffice_HowsWork);

inOffice_playerVoted = ConvoScreen:new {
	id = "inOffice_playerVoted",
	leftDialog = "@conversation/sean_trenwell:s_f1b007b2", --I heard and greatly appreciate it! When the election is over, if I win I'd like to thank you for your support. Come back and speak to me if that happens.
	stopConversation = "true",
	options = {}
}
seanTrenwellPhase2ConvoTemplate:addScreen(inOffice_playerVoted);

inOffice_yourPlans = ConvoScreen:new {
	id = "inOffice_yourPlans",
	leftDialog = "@conversation/sean_trenwell:s_dab387e8", --Indeed I do! History is a passion of mine, especially since my ancestors were among the original settlers of Bestine. I've gotten enough funding to hire a historian. We made an exciting new discovery just last week! A terrible desert storm came through and kicked up loose sand and beneath was a wrecked ship. We think it may be the Red-Sin Valon, the vessel used to transport the early settlers to Tatooine. It's so exciting!
	stopConversation = "false",
	options = {
		{"@conversation/sean_trenwell:s_4ff8cd88","inOffice_yourPlans_2"}, --I suppose
	}
}
seanTrenwellPhase2ConvoTemplate:addScreen(inOffice_yourPlans);

inOffice_yourPlans_2 = ConvoScreen:new {
	id = "inOffice_yourPlans_2",
	leftDialog = "@conversation/sean_trenwell:s_d485fca4", --Yes. Anyway, lately we've experienced brutal attacks from the Sand People. My historian is having a hard time of it, and I'm not sure her efforts can continue. She doesn't possess a brawler's spirit or the skill of a marksman. She's just a scholar. It's depressing to think that our attempts to restore the Red-Sin Valon have been fruitless. Do you think you can help? You seem like an adventurer. Or am I wrong?
	stopConversation = "false",
	options = {
		{"@conversation/sean_trenwell:s_9a679e7f","inOffice_youre_wrong"}, --You're wrong.
		{"@conversation/sean_trenwell:s_1e35bbba","inOffice_adventurer"}, --I am an adventurer!
	}
}
seanTrenwellPhase2ConvoTemplate:addScreen(inOffice_yourPlans_2);

inOffice_youre_wrong = ConvoScreen:new {
	id = "inOffice_youre_wrong",
	leftDialog = "@conversation/sean_trenwell:s_61503fc8",--Oh. That's unfortunate. If you know of an adventurer, please send him or her my way. It would really help me. Thank you.
	stopConversation = "true",
	options = {}
}
seanTrenwellPhase2ConvoTemplate:addScreen(inOffice_youre_wrong);

inOffice_adventurer = ConvoScreen:new {
	id = "inOffice_adventurer",
	leftDialog = "@conversation/sean_trenwell:s_a5cd533e",--Just my luck! I could really use your help. The Red-Sin Valon find is phenomenal in of itself, but what if there's more? I want you to bring back any information you can. There must be some sort of log of the events surrounding the early settlement attempts. I'd really like for you to find it. Do you think you can do that?
	stopConversation = "false",
	options = {
		{"@conversation/sean_trenwell:s_b45b3794","inOffice_accept_HQuest"},	--Sounds like fun. I'll do it!
		{"@conversation/sean_trenwell:s_2ac8d04c","inOffice_decline_HQuest"},	--No, I can't.
	}
}
seanTrenwellPhase2ConvoTemplate:addScreen(inOffice_adventurer);

inOffice_accept_HQuest = ConvoScreen:new {
	id = "inOffice_accept_HQuest",
	leftDialog = "@conversation/sean_trenwell:s_78b31931",  --Let me see your datapad for a second. I'll punch in the location for you. Return to me if you find anything. Be sure to speak with my historian at the site. Oh, and beware of the Tuskens!
	stopConversation = "true",
	options = {}
}
seanTrenwellPhase2ConvoTemplate:addScreen(inOffice_accept_HQuest);

inOffice_decline_HQuest = ConvoScreen:new {
	id = "inOffice_decline_HQuest",
	leftDialog = "@conversation/sean_trenwell:s_dc13d9c7",  --I understand. Maybe later, then.
	stopConversation = "true",
	options = {}
}
seanTrenwellPhase2ConvoTemplate:addScreen(inOffice_decline_HQuest);

historyQuest_SpokeToContact = ConvoScreen:new {
	id = "historyQuest_SpokeToContact",
	leftDialog = "@conversation/sean_trenwell:s_7fc36aab",  -- And has the disk been dealt with?
	stopConversation = "false",
	options = { }
}
seanTrenwellPhase2ConvoTemplate:addScreen(historyQuest_SpokeToContact);

historyQuest_HasDisk = ConvoScreen:new {
	id = "historyQuest_HasDisk",
	leftDialog = "@conversation/sean_trenwell:s_5ae436c2",  -- Please! Take the disk out of here! Take it to my contact. Here, I'll give you the location again. Get rid of it quickly.
	stopConversation = "true",
	options = {  }
}
seanTrenwellPhase2ConvoTemplate:addScreen(historyQuest_HasDisk);

historyQuest_DestroyedDisk_noroom = ConvoScreen:new {
	id = "historyQuest_DestroyedDisk_noroom",
	leftDialog = "@conversation/sean_trenwell:s_2e05a27f",  --I'm grateful to you and would like to reward you, but you have no room in your inventory. Please, speak to me again when you've made some room.
	stopConversation = "true",
	options = {  }
}
seanTrenwellPhase2ConvoTemplate:addScreen(historyQuest_DestroyedDisk_noroom);

historyQuest_DestroyedDisk = ConvoScreen:new {
	id = "historyQuest_DestroyedDisk",
	leftDialog = "@conversation/sean_trenwell:s_bc42a527",  --Finally! I'm so grateful to you. Please, take this as my token of eternal gratitude.
	stopConversation = "true",
	options = { }
}
seanTrenwellPhase2ConvoTemplate:addScreen(historyQuest_DestroyedDisk);

historyQuest_SearchedCrashSite = ConvoScreen:new {
	id = "historyQuest_SearchedCrashSite",
	leftDialog = "@conversation/sean_trenwell:s_2e38174d",  --Well returned! Did you find anything?
	stopConversation = "false",
	options = {
		{"@conversation/sean_trenwell:s_b30bd73c","searchedCrashSite_Found"},  --Yes, I did. 
		{"@conversation/sean_trenwell:s_c8a36ac7","searchedCrashSite_NotFound"},  --No, unfortunately. Nothing of use.
	}
}
seanTrenwellPhase2ConvoTemplate:addScreen(historyQuest_SearchedCrashSite);

searchedCrashSite_Found = ConvoScreen:new {
	id = "searchedCrashSite_Found",
	leftDialog = "@conversation/sean_trenwell:s_9d0c2f9e",  --What did you find? Can I see it? Does it mention my ancestor? Let me have it, please.
	stopConversation = "false",
	options = {
		{"@conversation/sean_trenwell:s_81a382e3","historyQuest_ShowDisk"},  --Here you are.
	}
}
seanTrenwellPhase2ConvoTemplate:addScreen(searchedCrashSite_Found);

historyQuest_ShowDisk = ConvoScreen:new {
	id = "historyQuest_ShowDisk",
	leftDialog = "@conversation/sean_trenwell:s_8dc34668",  -- Oh no. This isn't good. If the governor finds out that I'm related to such a person, she may just kick me out of office. Here, take it back. Tell you what. If you find some way to destroy it, I'll give you something. Just... get rid of it!
	stopConversation = "false",
	options = {
		{"@conversation/sean_trenwell:s_fcf4d778","historyQuest_SeansContact"}, --How?
	}
}
seanTrenwellPhase2ConvoTemplate:addScreen(historyQuest_ShowDisk);


historyQuest_SeansContact = ConvoScreen:new {
	id = "HistoryQuest_SeansContact",
	leftDialog = "@conversation/sean_trenwell:s_5caf6cfd",  -- I have a contact with whom you can meet. He has ways of destroying information. Please seek him out. And whatever you do, do not give it to anyone else! This is my career we're talking about here. You'll know where to find him.
	stopConversation = "true",
	options = {
	}
}
seanTrenwellPhase2ConvoTemplate:addScreen(historyQuest_SeansContact);

searchedCrashSite_NotFound = ConvoScreen:new {
	id = "searchedCrashSite_NotFound",
	leftDialog = "@conversation/sean_trenwell:s_2d1057e6",  --Will you try again? I know there's something out there! Look more closely. I'll be waiting anxiously.
	stopConversation = "true",
	options = {	}
}
seanTrenwellPhase2ConvoTemplate:addScreen(searchedCrashSite_NotFound);

historyQuest_SeanHistorian = ConvoScreen:new {
	id = "historyQuest_SeanHistorian",
	leftDialog = "@conversation/sean_trenwell:s_ca646df4",  --My historian, who's out at the crash site. She needs to screen and catalog whatever you find. Go and speak with her.
	stopConversation = "true",
	options = { }
}
seanTrenwellPhase2ConvoTemplate:addScreen(historyQuest_SeanHistorian);

historyQuest_CrashSite = ConvoScreen:new {
	id = "historyQuest_CrashSite",
	leftDialog = "@conversation/sean_trenwell:s_d349c913",  --See if you can find anything of value. Did you speak to my historian? Speak to her when you get to the site.
	stopConversation = "false",
	options = {
		{"@conversation/sean_trenwell:s_1059c36e","historyQuest_CrashSite_dothat"}, --Okay, I'll do that.
		{"@conversation/sean_trenwell:s_3ba540c","historyQuest_CrashSite_quit"}, --No thanks, I'd rather not. I'm done with this.
	}
}
seanTrenwellPhase2ConvoTemplate:addScreen(historyQuest_CrashSite);

historyQuest_CrashSite_dothat = ConvoScreen:new {
	id = "historyQuest_CrashSite_dothat",
	leftDialog = "@conversation/sean_trenwell:s_f47244aa",  --Excellent. If you find anything, be sure to let my historian screen it. Then report back to me.
	stopConversation = "true",
	options = {}
}
seanTrenwellPhase2ConvoTemplate:addScreen(historyQuest_CrashSite_dothat);

historyQuest_CrashSite_quit = ConvoScreen:new {
	id = "historyQuest_CrashSite_quit",
	leftDialog = "@conversation/sean_trenwell:s_75491d63",  --As you wish. I'm disappointed, but I understand how these things are.
	stopConversation = "true",
	options = {}
}
seanTrenwellPhase2ConvoTemplate:addScreen(historyQuest_CrashSite_quit);

addConversationTemplate("seanTrenwellPhase2ConvoTemplate", seanTrenwellPhase2ConvoTemplate);
