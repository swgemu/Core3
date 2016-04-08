keannaLikynaConvoTemplate = ConvoTemplate:new {
	initialScreen = "",
	templateType = "Lua",
	luaClassHandler = "bestine_election_conv_handler",
	screens = {}
}

default_greeting = ConvoScreen:new {
	id = "default_greeting",
	leftDialog = "@conversation/keanna_likyna:s_b1103974", -- Did that, still need to do that... Oh! I didn't see you there. The new election has created a huge work load for me! I'm practically oblivious to everything else. I'm Victor's secretary. I schedule his trips, meetings... just about everything! Are you going to vote for him? It's just so exciting! He has so many great changes in store for Bestine. You should speak with him and hear what he has to say.
	stopConversation = "false",
	options = {
		{"@conversation/keanna_likyna:s_d6ecfaf4","default_end"} -- Okay. Thank You.
	}
}
keannaLikynaConvoTemplate:addScreen(default_greeting);

default_end = ConvoScreen:new {
	id = "default_end",
	leftDialog = "@conversation/keanna_likyna:s_b4ecef81", -- Of course! Good bye!!
	stopConversation = "true",
	options = {}
}
keannaLikynaConvoTemplate:addScreen(default_end);

nquest_start = ConvoScreen:new {
	id = "nquest_start",
	leftDialog = "@conversation/keanna_likyna:s_8080f094", -- He's convinced you to do some dirty work, has he? That's unfortunate. I wish others would play fairly. Oh well. Let's see... I'm sure there's something in his office that'd be of use to you. And his teacher at the Commerce University might have something. Oh, I don't know... what else. Hm. He has an accountant as well. I'm out of ideas.
	stopConversation = "false",
	options = {
		{"@conversation/keanna_likyna:s_be0e4a12","nquest_end"} -- Thank you. Good bye
	}
}
keannaLikynaConvoTemplate:addScreen(nquest_start);

nquest_end = ConvoScreen:new {
	id = "nquest_end",
	leftDialog = "@conversation/keanna_likyna:s_a80d9308", --Good luck!
	stopConversation = "true",
	options = {}
}
keannaLikynaConvoTemplate:addScreen(nquest_end);

in_campaign = ConvoScreen:new {
	id = "in_campaign",
	leftDialog = "@conversation/keanna_likyna:s_398a575d", -- How exciting! I'm so glad you could join us. Evidence, hm? I know exactly the people you should talk to to get such a thing. How about... well, this may or may not work, but there's a terminal in here somewhere with job registries. I'm new, so I really don't know where it is.
	stopConversation = "false",
	options = {
		{"@conversation/keanna_likyna:s_e547fd1e","in_campaign2"} -- Yeah?
	}
}
keannaLikynaConvoTemplate:addScreen(in_campaign);

in_campaign2 = ConvoScreen:new {
	id = "in_campaign2",
	leftDialog = "@conversation/keanna_likyna:s_c14a1c83", -- Also, you can try the orphanage director. She volunteers at the hospital. And... there's a woman in the slums area you can speak with as well. I don't have direct locations for them. I'm sorry. I really hope this can help you! You only need one piece of evidence.
	stopConversation = "false",
	options = {
		{"@conversation/keanna_likyna:s_e547fd1e","thank_you_end"} -- Okay, thank you very much!
	}
}
keannaLikynaConvoTemplate:addScreen(in_campaign2);

next_election = ConvoScreen:new {
	id = "next_election",
	leftDialog = "@conversation/keanna_likyna:s_36d62208", -- So many people have been visiting the capitol lately. I'm just getting ready for the next election. I hope that Victor wins. Of course, I do! He's my boss. Anyway, be sure to talk to the townsfolk often. They may have interesting things to say.
	stopConversation = "true",
	options = {}
}
keannaLikynaConvoTemplate:addScreen(next_election);

thank_you_end = ConvoScreen:new {
	id = "thank_you_end",
	leftDialog = "@conversation/keanna_likyna:s_1f3a981f", -- I hope it goes well. Good bye!
	stopConversation = "true",
	options = {}
}
keannaLikynaConvoTemplate:addScreen(thank_you_end);

addConversationTemplate("keannaLikynaConvoTemplate", keannaLikynaConvoTemplate);
