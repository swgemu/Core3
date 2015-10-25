trialsPadawanOldMusician03ConvoTemplate = ConvoTemplate:new {
	initialScreen = "",
	templateType = "Lua",
	luaClassHandler = "trialsPadawanOldMusician03ConvoHandler",
	screens = {}
}

intro = ConvoScreen:new {
	id = "intro",
	leftDialog = "@conversation/padawan_old_musician_03:s_16e413e5", -- Hello friend.
	stopConversation = "false",
	options = {
		{"@conversation/padawan_old_musician_03:s_a8d0cb35", "curious"} -- I'm looking for an old friend of Grizzlo.
	}
}
trialsPadawanOldMusician03ConvoTemplate:addScreen(intro);

curious = ConvoScreen:new {
	id = "curious",
	leftDialog = "@conversation/padawan_old_musician_03:s_8da4188a", -- No kidding? Grizzy Two Tone? It's been quite a few years since I've heard that name. Samston, a member of Grizzy's band used to hang out in this here Cantina. He used to sit in that chair right across from me. We were good friends Samston and I. He had many a good stories of Grizzy and the rest of 'The Blue...' something... can't quite recall the bands name. It was a sad day when Samston passed away. 
	stopConversation = "false",
	options = {
		{"@conversation/padawan_old_musician_03:s_cbc0ca2b", "continue"} -- I'm sorry to hear that. Grizzlo will be as well.
	}
}
trialsPadawanOldMusician03ConvoTemplate:addScreen(curious);

continue = ConvoScreen:new {
	id = "continue",
	leftDialog = "@conversation/padawan_old_musician_03:s_a25995cf", -- It's been a good ten years since Samston passed away. As far as I know he has never talked with Grizzy after the whole fiasco between the two of them over that Twi'lek dancer.
	stopConversation = "false",
	options = {
		{"@conversation/padawan_old_musician_03:s_6be6a4b5", "continue_more"} -- What Twi'lek?
	}
}
trialsPadawanOldMusician03ConvoTemplate:addScreen(continue);

continue_more = ConvoScreen:new {
	id = "continue_more",
	leftDialog = "@conversation/padawan_old_musician_03:s_8dc8e232", -- Oh just some girl the two of them fought over for quite some time. Rumor has it that she is the reason the band broke up.
	stopConversation = "false",
	options = {
		{"@conversation/padawan_old_musician_03:s_3585e154", "continue_accept"} -- Do you know where I might be able to find her?
	}
}
trialsPadawanOldMusician03ConvoTemplate:addScreen(continue_more);

continue_accept = ConvoScreen:new {
	id = "continue_accept",
	leftDialog = "@conversation/padawan_old_musician_03:s_285ac110", -- You are going to need a shovel if you want to talk to her friend, and I'm afraid she isn't going to be saying much. She passed a few years back herself. As a matter of fact, I'm afraid the entire band, except for your friend Grizzlo, is no longer with us. It's a shame really; Samston told me they had two tunes in particular that really made people move.
	stopConversation = "false",
	options = {
		{"@conversation/padawan_old_musician_03:s_afbed875", "continue_finish"} -- Thank you for your time.
	}
}
trialsPadawanOldMusician03ConvoTemplate:addScreen(continue_accept);

continue_finish = ConvoScreen:new {
	id = "continue_finish",
	leftDialog = "@conversation/padawan_old_musician_03:s_77c9e846", -- No problem friend. Actually wait one second. Samston gave me this here ring, it belonged to that Twi'lek I was talking about before. I don't have much need for it and I'm sure Grizzy Two Tone would love to have it himself. Tell him Samston always wanted him to have it; it wouldn't be far from the truth. [You worry that the ring will be lost in your inventory, so you stow it in a safe place.]
	stopConversation = "true",
	options = {}
}
trialsPadawanOldMusician03ConvoTemplate:addScreen(continue_finish);

noquest_player_talks = ConvoScreen:new {
	id = "noquest_player_talks",
	leftDialog = "@conversation/padawan_old_musician_03:s_4ef8ad4d", -- I'm supposed to meet a friend, Branthon, and go see a theatrical performance tonight. If I don't go, Branthon has promised to write an essay revealing the entire plot of the show. It will consist of at least 20 words! I don't want that to happen.
	stopConversation = "true",
	options = {}
}
trialsPadawanOldMusician03ConvoTemplate:addScreen(noquest_player_talks);

addConversationTemplate("trialsPadawanOldMusician03ConvoTemplate", trialsPadawanOldMusician03ConvoTemplate);
