foreman_convotemplate = ConvoTemplate:new {
	initialScreen = "convoscreen1",
	templateType = "Lua",
	luaClassHandler = "death_watch_foreman_handler",
	screens = {}
}


foreman_convoscreen1 = ConvoScreen:new {
	id = "convoscreen1",
	leftDialog = "@conversation/death_watch_foreman:s_8dc6968d",
	stopConversation = "false",
	options = {
		{"@conversation/death_watch_foreman:s_637e6c80", "convoscreen2"},
		{"@conversation/death_watch_foreman:s_57097d43", "convoscreen3"},
	}
}

foreman_convotemplate:addScreen(foreman_convoscreen1);

foreman_convoscreen2 = ConvoScreen:new {
	id = "convoscreen2",
	leftDialog = "@conversation/death_watch_foreman:s_81b8b95b",
	stopConversation = "false",
	options = {
		{"@conversation/death_watch_foreman:s_7d2eea07", "convoscreen2_1"},
	}
}

foreman_convotemplate:addScreen(foreman_convoscreen2);

foreman_convoscreen2_1 = ConvoScreen:new {
	id = "convoscreen2_1",
	leftDialog = "@conversation/death_watch_foreman:s_dd6f26cc",
	stopConversation = "false",
	options = {
		{"@conversation/death_watch_foreman:s_1c4d0bbb", "convoscreen2_2"},
	}
}

foreman_convotemplate:addScreen(foreman_convoscreen2_1);

foreman_convoscreen2_2 = ConvoScreen:new {
	id = "convoscreen2_2",
	leftDialog = "@conversation/death_watch_foreman:s_e83ca277",
	stopConversation = "false",
	options = {
		{"@conversation/death_watch_foreman:s_7d65b570", "convoscreen2_3"},
	}
}

foreman_convotemplate:addScreen(foreman_convoscreen2_2);

foreman_convoscreen2_3 = ConvoScreen:new {
	id = "convoscreen2_3",
	leftDialog = "@conversation/death_watch_foreman:s_7a654750",
	stopConversation = "false",
	options = {
		{"@conversation/death_watch_foreman:s_82599d96", "convoscreen2_4"},
	}
}

foreman_convotemplate:addScreen(foreman_convoscreen2_3);

foreman_convoscreen2_4 = ConvoScreen:new {
	id = "convoscreen2_4",
	leftDialog = "@conversation/death_watch_foreman:s_286d283f",
	stopConversation = "false",
	options = {
		{"@conversation/death_watch_foreman:s_b491aba5", "convoscreen2_5"},
	}
}

foreman_convotemplate:addScreen(foreman_convoscreen2_4);

foreman_convoscreen2_5 = ConvoScreen:new {
	id = "convoscreen2_5",
	leftDialog = "@conversation/death_watch_foreman:s_8deeb761",
	stopConversation = "false",
	options = {
		{"@conversation/death_watch_foreman:s_dc1d4717", "convoscreen2_6"},
	}
}

foreman_convotemplate:addScreen(foreman_convoscreen2_5);

foreman_convoscreen2_6 = ConvoScreen:new {
	id = "convoscreen2_6",
	leftDialog = "@conversation/death_watch_foreman:s_b75a73ed",
	stopConversation = "false",
	options = {
		{"@conversation/death_watch_foreman:s_44bb7cbc", "convoscreen2_7"},
	}
}

foreman_convotemplate:addScreen(foreman_convoscreen2_6);

foreman_convoscreen2_7 = ConvoScreen:new {
	id = "convoscreen2_7",
	leftDialog = "@conversation/death_watch_foreman:s_ac0e598b",
	stopConversation = "false",
	options = {
		{"@conversation/death_watch_foreman:s_4e099c6a", "convoscreen4"},
	}
}

foreman_convotemplate:addScreen(foreman_convoscreen2_7);

foreman_convoscreen3 = ConvoScreen:new {
	id = "convoscreen3",
	leftDialog = "@conversation/death_watch_foreman:s_6d069da0",
	stopConversation = "false",
	options = {
		{"@conversation/death_watch_foreman:s_687ef712", "convoscreen4"},
	}
}

foreman_convotemplate:addScreen(foreman_convoscreen3);

foreman_convoscreen4 = ConvoScreen:new {
	id = "convoscreen4",
	leftDialog = "@conversation/death_watch_foreman:s_c2d12633",
	stopConversation = "false",
	options = {
		{"@conversation/death_watch_foreman:s_19ecd0cd", "convoscreen5"},
	}
}

foreman_convotemplate:addScreen(foreman_convoscreen4);

foreman_convoscreen5 = ConvoScreen:new {
	id = "convoscreen5",
	leftDialog = "@conversation/death_watch_foreman:s_645da2b5",
	stopConversation = "false",
	options = {
		{"@conversation/death_watch_foreman:s_1265571c", "convoscreen6"},--use force?
		{"@conversation/death_watch_foreman:s_2236f9d7", "convoscreen7"},--is there a cure?
		{"@conversation/death_watch_foreman:s_71ad5afa", "convoscreen8"},--no thanks
	}
}

foreman_convotemplate:addScreen(foreman_convoscreen5);

foreman_convoscreen6 = ConvoScreen:new {
	id = "convoscreen6",
	leftDialog = "@conversation/death_watch_foreman:s_c7f1e2ee",
	stopConversation = "false",
	options = {
		{"@conversation/death_watch_foreman:s_ce027a15", "convoscreen6_1"},--accept quest
	}
}

foreman_convotemplate:addScreen(foreman_convoscreen6);

foreman_convoscreen6_1 = ConvoScreen:new {
	id = "convoscreen6_1",
	leftDialog = "@conversation/death_watch_foreman:s_471cd71d",
	stopConversation = "true",
	options = {
	}
}

foreman_convotemplate:addScreen(foreman_convoscreen6_1);

foreman_convoscreen7 = ConvoScreen:new {
	id = "convoscreen7",
	leftDialog = "@conversation/death_watch_foreman:s_45d9624a",
	stopConversation = "false",
	options = {
		{"@conversation/death_watch_foreman:s_6c1f32dd", "convoscreen7_1"},--accept quest
	}
}

foreman_convotemplate:addScreen(foreman_convoscreen7);

foreman_convoscreen7_1 = ConvoScreen:new {
	id = "convoscreen7_1",
	leftDialog = "@conversation/death_watch_foreman:s_44557f4a",
	stopConversation = "true",
	options = {
	}
}

foreman_convotemplate:addScreen(foreman_convoscreen7_1);

foreman_convoscreen8 = ConvoScreen:new {
	id = "convoscreen8",
	leftDialog = "@conversation/death_watch_foreman:s_f79fa021",
	stopConversation = "true",
	options = {
	}
}

foreman_convotemplate:addScreen(foreman_convoscreen8);

foreman_convoscreen9 = ConvoScreen:new { --player in stage 1, npc not busy, already spoken, quest not taken
	id = "convoscreen9",
	leftDialog = "@conversation/death_watch_foreman:s_1511575f",
	stopConversation = "false",
	options = {
		{"@conversation/death_watch_foreman:s_26fa42a7", "convoscreen9_1"},--accept quest
		{"@conversation/death_watch_foreman:s_f501c596", "convoscreen9_2"},--decline quest
		{"@conversation/death_watch_foreman:s_f73c5ae7", "convoscreen9_3"},--more info
	}
}

foreman_convotemplate:addScreen(foreman_convoscreen9);

foreman_convoscreen9_1 = ConvoScreen:new {
	id = "convoscreen9_1",
	leftDialog = "@conversation/death_watch_foreman:s_471cd71d",
	stopConversation = "true",
	options = {
	}
}

foreman_convotemplate:addScreen(foreman_convoscreen9_1);

foreman_convoscreen9_2 = ConvoScreen:new {
	id = "convoscreen9_2",
	leftDialog = "@conversation/death_watch_foreman:s_8f36c784",
	stopConversation = "true",
	options = {
	}
}

foreman_convotemplate:addScreen(foreman_convoscreen9_2);

foreman_convoscreen9_3 = ConvoScreen:new { 
	id = "convoscreen9_3",
	leftDialog = "@conversation/death_watch_foreman:s_1511575f",
	stopConversation = "false",
	options = {
		{"@conversation/death_watch_foreman:s_ce027a15", "convoscreen9_1"},--accept quest
		{"@conversation/death_watch_foreman:s_f501c596", "convoscreen9_2"},--decline quest
	}
}

foreman_convotemplate:addScreen(foreman_convoscreen9_3);

foreman_convoscreen10 = ConvoScreen:new { 
	id = "convoscreen10",
	leftDialog = "@conversation/death_watch_foreman:s_4f17ac67",
	stopConversation = "false",
	options = {
		{"@conversation/death_watch_foreman:s_c825f420", "convoscreen10_1"},--continue quest
		{"@conversation/death_watch_foreman:s_3055077f", "convoscreen10_2"},--abort quest
	}
}

foreman_convotemplate:addScreen(foreman_convoscreen10);

foreman_convoscreen10_1 = ConvoScreen:new {
	id = "convoscreen10_1",
	leftDialog = "@conversation/death_watch_foreman:s_de774e37",
	stopConversation = "true",
	options = {
	}
}

foreman_convotemplate:addScreen(foreman_convoscreen10_1);

foreman_convoscreen10_2 = ConvoScreen:new {
	id = "convoscreen10_2",
	leftDialog = "@conversation/death_watch_foreman:s_d8f6c63f",
	stopConversation = "true",
	options = {
	}
}

foreman_convotemplate:addScreen(foreman_convoscreen10_2);

foreman_convoscreen11 = ConvoScreen:new {
	id = "convoscreen11",
	leftDialog = "@conversation/death_watch_foreman:s_9e37f61f",
	stopConversation = "true",
	options = {
	}
}

foreman_convotemplate:addScreen(foreman_convoscreen11);

foreman_convoscreen12 = ConvoScreen:new {
	id = "convoscreen12",
	leftDialog = "@conversation/death_watch_foreman:s_d9db9b00",
	stopConversation = "true",
	options = {
	}
}

foreman_convotemplate:addScreen(foreman_convoscreen12);

foreman_convoscreen13 = ConvoScreen:new {
	id = "convoscreen13",
	leftDialog = "@conversation/death_watch_foreman:s_3310d1b6",--done but killed
	stopConversation = "false",
	options = {
		{"@conversation/death_watch_foreman:s_d62e85a9", "convoscreen13_1"},
	}
}

foreman_convotemplate:addScreen(foreman_convoscreen13);

foreman_convoscreen13_1 = ConvoScreen:new {
	id = "convoscreen13_1",
	leftDialog = "@conversation/death_watch_foreman:s_9b4dd6c7",
	stopConversation = "false",
	options = {
		{"@conversation/death_watch_foreman:s_bdb717fb", "convoscreen15"},
	}
}

foreman_convotemplate:addScreen(foreman_convoscreen13_1);

foreman_convoscreen14 = ConvoScreen:new {
	id = "convoscreen14",
	leftDialog = "@conversation/death_watch_foreman:s_27b9acbc",--done and not killed
	stopConversation = "false",
	options = {
		{"@conversation/death_watch_foreman:s_bdb717fb", "convoscreen15"},
	}
}

foreman_convotemplate:addScreen(foreman_convoscreen14);

foreman_convoscreen15 = ConvoScreen:new {
	id = "convoscreen15",
	leftDialog = "@conversation/death_watch_foreman:s_9cf7119e",
	stopConversation = "false",
	options = {
		{"@conversation/death_watch_foreman:s_5dbddef", "convoscreen15_1"},
		{"@conversation/death_watch_foreman:s_728cbacc", "convoscreen15_2"},
	}
}

foreman_convotemplate:addScreen(foreman_convoscreen15);

foreman_convoscreen15_1 = ConvoScreen:new {
	id = "convoscreen15_1",
	leftDialog = "@conversation/death_watch_foreman:s_bc5213a",
	stopConversation = "false",
	options = {
		{"@conversation/death_watch_foreman:s_b5a845f9", "convoscreen16"},--accept
		{"@conversation/death_watch_foreman:s_728cbacc", "convoscreen15_2"},
	}
}

foreman_convotemplate:addScreen(foreman_convoscreen15_1);

foreman_convoscreen15_2 = ConvoScreen:new {
	id = "convoscreen15_2",
	leftDialog = "@conversation/death_watch_foreman:s_23237572",
	stopConversation = "false",
	options = {
		{"@conversation/death_watch_foreman:s_6204ccac", "convoscreen16"},--accept
		{"@conversation/death_watch_foreman:s_a618b93a", "convoscreen15_3"},
	}
}

foreman_convotemplate:addScreen(foreman_convoscreen15_2);

foreman_convoscreen15_3 = ConvoScreen:new {
	id = "convoscreen15_3",
	leftDialog = "@conversation/death_watch_foreman:s_d8f6c63f",
	stopConversation = "true",
	options = {
	}
}

foreman_convotemplate:addScreen(foreman_convoscreen15_3);

foreman_convoscreen16 = ConvoScreen:new {
	id = "convoscreen16",
	leftDialog = "@conversation/death_watch_foreman:s_787e689e",
	stopConversation = "true",
	options = {
	}
}

foreman_convotemplate:addScreen(foreman_convoscreen16);

--come back, spoken about it but not accepted
foreman_convoscreen17 = ConvoScreen:new {
	id = "convoscreen17",
	leftDialog = "@conversation/death_watch_foreman:s_d1eff807",
	stopConversation = "false",
	options = {
		{"@conversation/death_watch_foreman:s_dd657c44", "convoscreen16"},--accept
		{"@conversation/death_watch_foreman:s_a618b93a", "convoscreen15_3"},
	}
}

foreman_convotemplate:addScreen(foreman_convoscreen17);

foreman_convoscreen18 = ConvoScreen:new {
	id = "convoscreen18",
	leftDialog = "@conversation/death_watch_foreman:s_7b9dc7c7",
	stopConversation = "false",
	options = {
		{"@conversation/death_watch_foreman:s_145fd34", "convoscreen18_1"},
	}
}

foreman_convotemplate:addScreen(foreman_convoscreen18);

foreman_convoscreen18_1 = ConvoScreen:new {
	id = "convoscreen18_1",
	leftDialog = "@conversation/death_watch_foreman:s_579c9bc5",
	stopConversation = "true",
	options = {
	}
}

foreman_convotemplate:addScreen(foreman_convoscreen18_1);

foreman_convoscreen19 = ConvoScreen:new {
	id = "convoscreen19",
	leftDialog = "@conversation/death_watch_foreman:s_dd7c0dd3",
	stopConversation = "false",
	options = {
		{"@conversation/death_watch_foreman:s_a33b6055", "convoscreen20"},
	}
}

foreman_convotemplate:addScreen(foreman_convoscreen19);

foreman_convoscreen20 = ConvoScreen:new {
	id = "convoscreen20",
	leftDialog = "@conversation/death_watch_foreman:s_286d283f",
	stopConversation = "false",
	options = {
		{"@conversation/death_watch_foreman:s_83d1549d", "convoscreen21"},
	}
}

foreman_convotemplate:addScreen(foreman_convoscreen20);

foreman_convoscreen21 = ConvoScreen:new {
	id = "convoscreen21",
	leftDialog = "@conversation/death_watch_foreman:s_e5e9e886",
	stopConversation = "false",
	options = {
		{"@conversation/death_watch_foreman:s_d4b1da9f", "convoscreen22"},
		{"@conversation/death_watch_foreman:s_54ee97f2", "convoscreen23"},
		
	}
}

foreman_convotemplate:addScreen(foreman_convoscreen21);

foreman_convoscreen22 = ConvoScreen:new {
	id = "convoscreen22",
	leftDialog = "@conversation/death_watch_foreman:s_262e7b86",
	stopConversation = "false",
	options = {	
		{"@conversation/death_watch_foreman:s_9bea7011", "convoscreen24"},
	}
}

foreman_convotemplate:addScreen(foreman_convoscreen22);

foreman_convoscreen23 = ConvoScreen:new {
	id = "convoscreen23",
	leftDialog = "@conversation/death_watch_foreman:s_23cbff5d",
	stopConversation = "true",
	options = {	
	}
}

foreman_convotemplate:addScreen(foreman_convoscreen23);

foreman_convoscreen24 = ConvoScreen:new {
	id = "convoscreen24",
	leftDialog = "@conversation/death_watch_foreman:s_6864fcd4",
	stopConversation = "true",
	options = {	
	}
}

foreman_convotemplate:addScreen(foreman_convoscreen24);

-- return unsuccessful before time runs out
foreman_convoscreen25 = ConvoScreen:new {
	id = "convoscreen25",
	leftDialog = "@conversation/death_watch_foreman:s_de4a182e",
	stopConversation = "false",
	options = {	
		{"@conversation/death_watch_foreman:s_9bea7011", "convoscreen25_1"},
	}
}

foreman_convotemplate:addScreen(foreman_convoscreen25);

foreman_convoscreen25_1 = ConvoScreen:new {
	id = "convoscreen25_1",
	leftDialog = "@conversation/death_watch_foreman:s_3b67f1eb",
	stopConversation = "true",
	options = {	
	}
}

foreman_convotemplate:addScreen(foreman_convoscreen25_1);

-- return after time runs out
foreman_convoscreen26 = ConvoScreen:new {
	id = "convoscreen26",
	leftDialog = "@conversation/death_watch_foreman:s_4af1601a",
	stopConversation = "false",
	options = {	
		{"@conversation/death_watch_foreman:s_e55f453d", "convoscreen26_1"},
		{"@conversation/death_watch_foreman:s_b99aaac2", "convoscreen23"},
	}
}

foreman_convotemplate:addScreen(foreman_convoscreen26);

foreman_convoscreen26_1 = ConvoScreen:new {
	id = "convoscreen26_1",
	leftDialog = "@conversation/death_watch_foreman:s_6b8a415c",
	stopConversation = "true",
	options = {	
	}
}

foreman_convotemplate:addScreen(foreman_convoscreen26_1);

foreman_convoscreen27 = ConvoScreen:new {
	id = "convoscreen27",
	leftDialog = "@conversation/death_watch_foreman:s_c1dc6296",
	stopConversation = "false",
	options = {	
		{"@conversation/death_watch_foreman:s_5597accd", "convoscreen28"},
	}
}

foreman_convotemplate:addScreen(foreman_convoscreen27);

foreman_convoscreen28 = ConvoScreen:new {
	id = "convoscreen28",
	leftDialog = "@conversation/death_watch_foreman:s_b4feb773",
	stopConversation = "false",
	options = {	
		{"@conversation/death_watch_foreman:s_c04f0d0d", "convoscreen29"},
	}
}

foreman_convotemplate:addScreen(foreman_convoscreen28);

foreman_convoscreen29 = ConvoScreen:new {
	id = "convoscreen29",
	leftDialog = "@conversation/death_watch_foreman:s_95879f15",
	stopConversation = "false",
	options = {	
		{"@conversation/death_watch_foreman:s_ed0d4e5a", "convoscreen30"},
	}
}

foreman_convotemplate:addScreen(foreman_convoscreen29);

foreman_convoscreen30 = ConvoScreen:new {
	id = "convoscreen30",
	leftDialog = "@conversation/death_watch_foreman:s_18426338",
	stopConversation = "true",
	options = {	
	}
}

foreman_convotemplate:addScreen(foreman_convoscreen30);

foreman_convoscreen31 = ConvoScreen:new {
	id = "convoscreen31",
	leftDialog = "@conversation/death_watch_foreman:s_52f3e83e",
	stopConversation = "true",
	options = {	
	}
}

foreman_convotemplate:addScreen(foreman_convoscreen31);

foreman_convoscreen32 = ConvoScreen:new {
	id = "convoscreen32",
	leftDialog = "@conversation/death_watch_foreman:s_1d1d45a9",
	stopConversation = "true",
	options = {	
	}
}

foreman_convotemplate:addScreen(foreman_convoscreen32);

foreman_convoscreen33 = ConvoScreen:new {
	id = "convoscreen33",
	leftDialog = "@conversation/death_watch_foreman:s_e1dd8e6e",
	stopConversation = "true",
	options = {	
	}
}

foreman_convotemplate:addScreen(foreman_convoscreen33);

foreman_convoscreen34 = ConvoScreen:new {
	id = "convoscreen34",
	leftDialog = "@conversation/death_watch_foreman:s_5af847c7",
	stopConversation = "true",
	options = {	
	}
}

foreman_convotemplate:addScreen(foreman_convoscreen34);

addConversationTemplate("foreman_convotemplate", foreman_convotemplate);

--[[
turn on pumps
option_somethingyoucantdo: s_a33b6055", --Let me guess. It is something that your guys can't do either.
s_286d283f -- The drill needs water pressure

option_moreinfo_pumps: s_83d1549d", --What do you need in order to get water pressure down here?
explain_pumps: s_e5e9e886", --Upstairs there is a pump room. There are four pumps that all need to be on in order to get the water down to us. Unfortunately the circuit breakers on those things are all ancient and trip at the slightest surge. If you could maybe go up there and turn them all on for us I know we could get underway.
option_acceptsomething: s_d4b1da9f", --Ok fine I will do this for you but you are going to owe me.
s_54ee97f2	35	I don't really have time to deal with this right now.
--> response_quit_pumps: s_23cbff5d", --Choice is yours. We will figure out some other way to get them online I suppose.
response_accept_deal_pumps: s_262e7b86", --Deal. Now listen those pumps can be tricky. Generally when you trip one of the valves it causes the one or ones next to it on the circuit to flip as well.  You will have to play with it for a while in order to get them all online. Also we really don't have a lot of time so if you are not back soon I am going to have to see if there is anything else I can do to get it on.
option_yes,yes: s_9bea7011",--Ok, cool your jets. I am on it.
s_6864fcd4	47	Good. Once you get those pumps back online come on back and we will discuss what I owe you.

return_unsuccessful_pumps: s_4af1601a", --So you are back? We still don't have any water pressure down here maybe you would like to head back up and try again?
option_declinepumps: s_b99aaac2", --No thanks, I can't figure out how to get those pumps to work.
--> response_quit_pumps: s_23cbff5d", --Choice is yours. We will figure out some other way to get them online I suppose.
option_tryagain: s_e55f453d", --Yes, I will give it another shot.
s_6b8a415c	49	Remember those pumps can be tricky. Generally when you trip one of the valves it causes the one or ones next to it on the circuit to flip as well.  You will have to play with it for a while in order to get them all online.

return_pumpsnotfinished: s_de4a182e", --What are you doing back here. We still don't have any water pressure down here. I am telling you that we don't have very much time left.
option_yes,yes: s_9bea7011",--Ok, cool your jets. I am on it.
s_3b67f1eb	23	Ok, please hurry because the Mandalorians will be wondering were their ore is shortly.

thankyoupumps: s_c1dc6296", --I don't know how you managed to get those pumps working without the Mandalorians taking you out. You must be a lot tougher then you look. I can't thank you enough for all your help.
s_5597accd	36	How about a reward?
--> explainreward: s_b4feb773", --We don't really have a whole lot to give but I will tell you what. I can sneak you some of this ore that we are mining. Now before you get all mad about just getting ore let me tell you that this is the stuff that the Mandalores use in their armor.
option_someore?: s_c04f0d0d", --I risked my life for some ore?
response_someore?: s_95879f15", --Hey it is not just any ore. This is the stuff that the Mandalorians use in their armor. They keep a pretty careful track of what we mine but I know that I can sneak you some of this stuff without them noticing it.
option_moreinfogeneral: s_ed0d4e5a", --You make Mandalorian armor out of this ore?
s_18426338	6	Hey all I know is that this stuff is used in the making of the armor. They keep a pretty tight watch on how much of this stuff we mine, but I know I can sneak you some every now and again. Here you go. If you check back with me occasionally, I should be able to sneak you out some more. Not too often mind you, but I will do my best.
option_thankyou?: s_dbf0d0f9", --Thank you, I could really use some more of that.
hereyougo??: s_829888a9", --Here you go.
or
s_52f3e83e	34	This is the same ore that the Mandalores use to make their armor. I am willing to sneak you some but you are going to need to make some room in your inventory so I can.


return after quest:
notyet3days: s_1d1d45a9", --Hey it is you again. Glad to still you are still breathing. If you have come looking for ore I am sorry but I can't sneak you out any right now. The Mandalorians are running inventory right now and will notice anything that is missing. Check back with me later.
return_3dayspassed: s_e1dd8e6e", --Good to see you again my friend. I was able to secure some more of this ore for you. If you need some more check back with me later and maybe I can sneak some more out under the noses of the Mandalorians.
inventoryfull: s_5af847c7", --You are going to have to clear out some inventory space in order for me to give you any more of this ore.

s_3f363bf3	24	No need to be sarcastic. The Mandalorians keep us under a pretty tight watch down here. They don't really trust anyone who isn't Mandalorian and then they will only partially trust you.
s_63fae5b4	45	You know I can't thank you enough. Without your help there is no way we could get this job completed on time.
response_declinehelpforsomethin: s_8f36c784", --Ok, well if you change your mind you know where I am.
quitresponse: s_d8f6c63f", --Yeah, well I guess it was to much to ask of a complete stranger but I was hoping that it would all work out. Wish us luck because we are going to need it.
option_thankyou?: s_dbf0d0f9", --Thank you, I could really use some more of that.

Start Conversation:
start_quest: s_8dc6968d", --Hey, what are you doing down here? You shouldn't be walking around down here unless you are working or the Mandalorians authorized you to be here and you certainly don't have the look of a miner.
option_a: s_637e6c80", --I have received authorization from the Mandalorians.
response_a: s_81b8b95b", --Yeah, yeah...whatever you say there pally. I wouldn't want to be in your shoes if the Mandalorians catch you down here bothering their miners.
option_a_a:s_7d2eea07", --So what are you all doing down here?
rseponse_a_a: s_dd6f26cc", --We mine for the alum that the Mandalores use to make their armor. Basically, we get to work down in these nasty caves all day long so the Mandalorians can look nice.
option_a_a_a: s_1c4d0bbb", --You work for the Mandalorians?
response_a_a_a: s_e83ca277", --I guess it isn't that bad. The Mandalorians don't pay us a whole lot but they generally don't directly mistreat any of us unless we do something to make them mad...which doesn't seem that hard to do. Hmmmm...now that I think about it this isn't the best life but it is better then telling them we quit.
otpion_a_a_a_a: s_7d65b570", --What sort of work are you doing?
response_a_a_a_a: s_7a654750", --Work in the loosest sense of the word. Although we are not really getting a whole lot of work done at this moment.
option_ta_1: s_82599d96", --Sounds fun. But didn't you say you weren't getting much done?
response_ta_1: s_286d283f", --The drill uses a liquid coolant system in order to keep it from overheating and exploding. Well the problem is that we are not getting any pressure down here so if we turn on the drill...BOOM!
option_ta_2: s_b491aba5",--You are still using liquid coolant for you laser drill?
response_ta_2: s_8deeb761", --It's old technology. The Mandalorians don't exactly splurge on mining equipment. In fact if you havn't noticed already nothing around here is exactly in tip top shape.
option_ta_3: s_dc1d4717", --Sounds to me like you should be happy your not working.
response_ta_3: s_b75a73ed", --Yeah right. The Mandalorains are expecting their ore and they don't much like excuses. If we can't get this drill back online and get back on schedule...well lets just say I prefer to it not coming to that.
option_ta_4: s_44bb7cbc", --What is the other problem with the drill?
response_ta_4: s_ac0e598b", --Its this blasted laser they have us working with. Dumb thing never works right and then when we finally did get it working again, Haldo went off his rocker, ripped it's battery out, and took off with it.
option_c: s_4e099c6a", --So who is this Haldo guy who ran off with your battery?

option_b: s_57097d43", --Don't worry about me and the Mandalorians. I can handle them.
response_b: s_6d069da0", --You're braver then I will ever be. But if you really are that tough, maybe you would like to help recover our drill battery that Haldo ran off with?
option_c: s_687ef712", --Haldo? Who is Haldo and why would he take the battery?

response_c: s_c2d12633" --Haldo was one of the men on my crew. My guess is that his rebreather wasn't working properly and he breathed too much of the alum fumes. Blasted air vents haven't been working right either, so we have been using our masks a lot.

option_d: s_19ecd0cd", --Have you sent anyone out to try to find Haldo?
respone_d: s_645da2b5", --I asked for volunteers but no one was willing to go search. Not that I blame them, I don't even want to go out and try to find him. People with alum sickness become real messed up in the head. You never know what they are going to do. A lot of times they get really violent.

option_e_1: s_1265571c", --So I will have to take the battery from him by force?
respone_e_1: s_c7f1e2ee", --Hey now! I didn't say anything about using force on him. He is sick and there is a cure up in the medical lab. Granted there have been a few cases where alum sickness will make a person so demented that they can't come back, but Haldo has only been ill for a little while.
option_e_1_a: s_ce027a15",--Ok I will go see what I can do for your co-worker.
response_e_1_a: s_471cd71d", --That would be a lifesaver. No one else is willing to go out and try to find him. Guys who get hit with alum sickness generally are unstable and sometimes can be quite dangerous.
=> quest accepted

option_e_2: s_2236f9d7", --If he is sick is there anyway to help him?
response_e_2: s_45d9624a", --Yeah, well there is a cure. We would have gone and got it, but the Mandalorians don't much care for us wandering around when we are supposed to be working, so none of us have gone up to get it.
option_e_2_a: s_6c1f32dd", --Where can I find this cure?
response_e_2_a: s_44557f4a", --It is located upstairs in the medical lab. One of the medical droids should be able to give it to you. They don't require any special code or anything to help you out. At least they didn't last time I used them but the Mandalorians don't really consult us when they make changes to things around here.
=> quest accepted

option_e_3: s_71ad5afa", --I am sorry but I don't really have time to help your sick co-worker.
response_e_3: s_f79fa021", --That is pretty much what I expected. I would have been shocked if a complete stranger such as yourself offered to help us out.

----alts:
return_unsuccessful_haldo: s_4f17ac67", --Have you managed to find Haldo yet? We really need that battery back before the Mandalorians come down here to check up on our progress.
option_e_1_a: s_3055077f", --I don't really have time for this right now, sorry.
quitresponse: s_d8f6c63f", --Yeah, well I guess it was to much to ask of a complete stranger but I was hoping that it would all work out. Wish us luck because we are going to need it.
option_notyethaldo: s_c825f420", --Not yet, but I am still looking for him.
medicine_and_battery: s_de774e37", --Great. Now remember there is some medicine in the medical lab that should be able to help him out. And once you get that battery bring it on back to me so we can get this drill working again.

return_questnottaken_haldo: s_1511575f", --Hey you are back again. You know Haldo is still running around down here with our battery. Are you sure you don't want to give us a hand and try to get it back for us?
option_d_1: s_26fa42a7", --Yes I will see if I can find him for you.
alternativ zu dem drüber: option_e_1_a: s_ce027a15",--Ok I will go see what I can do for your co-worker.
response_d_1: s_471cd71d", --That would be a lifesaver. No one else is willing to go out and try to find him. Guys who get hit with alum sickness generally are unstable and sometimes can be quite dangerous.
option_declinehelphaldo: s_f501c596", --No thanks, I can't look for him right now.
response_declinehelpforsomethin: s_8f36c784", --Ok, well if you change your mind you know where I am.

option_moreinfocure: s_f73c5ae7", --Where can I find this cure if I decide to help out?
s_44557f4a	25	It is located upstairs in the medical lab. One of the medical droids should be able to give it to you. They don't require any special code or anything to help you out. At least they didn't last time I used them but the Mandalorians don't really consult us when they make changes to things around here.

moving from haldo quest to battery quest
return_justbattery: s_3310d1b6", --I guess I should thank you for getting us the battery back but you didn't have to kill Haldo. He was sick in the head from the fumes and the medicine from the medical droid could have cured him.
return_successful_haldo: s_27b9acbc", --Thank you for helping Haldo and getting the battery back for us. Now we can get back to....oh no! The battery's connections are all covered with dirt and grime. Haldo must have got them dirty after he took it.

clean the battery
option_acceptbattery: s_b5a845f9", --Ok, I will take it over to the workshop for you.
option_declinecleanbattery: s_a618b93a	76	No thanks, I think I will avoid the workshop if it is monitored.
response_accept_battery: s_b7c0824", --That is the best news that I have heard all day. If you get that battery come on back to me and I will see about getting this drill back online.
response_whatifbatterydirty: s_9cf7119e", --We won't get a good solid connection and the drill won't fire is what will happen. I hate to ask but could you perhaps take this battery over to the workshop and have one of treadwell clean it up?
moreinfo_cleanbattery: s_bc5213a", --Just speak to the treadwell when you are in there and he will take care of the dirty battery. Oh and try not to kill him while you are there. We sort of need him for repairs around this place.
option_whatifbatterydirty: s_bdb717fb", --What happens if the battery connections are dirty?
offerbatteryquest: s_d1eff807", --Could you do us one more favor and take this battery over to the workshop. The treadwell in there can clean it off without any problems.

option_accept_cleanbattery: s_dd657c44",--Sure, I will come back to you as soon as I get it cleaned.
batterydone: s_f46d76f6", --Hey you are back. I was sort of half expecting you not to return. Oh yeah, this is excellent. The battery is clean and ready to be installed in the drill. And you didn't destroy the treadwell...thats a plus. Unfortunately there is one other issue that we are having.
return_finishedbattery: s_dd7c0dd3", --Hey, you're back. I was sort of half expecting you not to return. Oh yeah, this is excellent. The battery is clean and ready to be installed in the drill. Unfortunately there is one other issue that we are having.
sendoff_cleanbattery: s_787e689e",--I figured you would be up for that whole danger thing. Once the treadwell has cleaned the battery, come on back to me so we can get that battery installed back into the drill.
notyet_cleanbattery: s_145fd34", --Not yet, but I will get this battery cleaned soon.
option_cantyousendsomeoneelse: s_728cbacc", --Why don't one of you go take it to the workshop?
response_cantyousendsomeoneelse: s_23237572", --I would love to but the Mandalorians keep track of who comes and goes from the workshop. If one of us goes in they will ask why and I would rather they didn't know about the whole Haldo incident. Since you are a stranger they will just correctly assume you are an intruder and try to kill you...which they probably have been doing anyways.
option_accepthelpbattery: s_f4fd5da3", --That is the best news that I have heard all day. If you get that battery, come on back to me and I will see about getting this drill back online.
s_5dbddef	42	How do you get it cleaned off?
s_6204ccac	43	Good point. Ok I will take the battery to the workshop.
s_579c9bc5	38	Well that battery doesn't really do us alot of good in its current state. Why don't you hold onto it and if you do get a chance run it over to the workshop and get it cleaned. We would really appreciate it.
come back quickly: s_fb5cf4cd", --Ok, please hurry. I am sure that we don't have a whole lot of time left. Once you get the battery come back to me as quick as you can.
return_batteryclean: s_7b9dc7c7", --Have you managed to get that battery cleaned yet?

]]