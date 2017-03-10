padawan_old_musician_03_convo_template = ConvoTemplate:new {
	initialScreen = "",
	templateType = "Lua",
	luaClassHandler = "padawan_old_musician_03_conv_handler",
	screens = {}
}

intro = ConvoScreen:new {
	id = "intro",
	leftDialog = "@conversation/padawan_old_musician_03:s_16e413e5", -- Hello friend.
	stopConversation = "false",
	options = {
		{"@conversation/padawan_old_musician_03:s_a8d0cb35", "no_kidding"} -- I'm looking for an old friend of Grizzlo.
	}
}
padawan_old_musician_03_convo_template:addScreen(intro);

no_kidding = ConvoScreen:new {
	id = "no_kidding",
	leftDialog = "@conversation/padawan_old_musician_03:s_8da4188a", -- No kidding? Grizzy Two Tone? It's been quite a few years since I've heard that name. Samston, a member of Grizzy's band used to hang out in this here Cantina. He used to sit in that chair right across from me. We were good friends Samston and I. He had many a good stories of Grizzy and the rest of 'The Blue...' something... can't quite recall the bands name. It was a sad day when Samston passed away.
	stopConversation = "false",
	options = {
		{"@conversation/padawan_old_musician_03:s_cbc0ca2b", "good_ten_years"} -- I'm sorry to hear that.  Grizzlo will be as well.
	}
}
padawan_old_musician_03_convo_template:addScreen(no_kidding);

good_ten_years = ConvoScreen:new {
	id = "good_ten_years",
	leftDialog = "@conversation/padawan_old_musician_03:s_a25995cf", -- It's been a good ten years since Samston passed away. As far as I know he has never talked with Grizzy after the whole fiasco between the two of them over that Twi'lek dancer.
	stopConversation = "false",
	options = {
		{"@conversation/padawan_old_musician_03:s_6be6a4b5", "some_girl"} -- What Twi'lek?
	}
}
padawan_old_musician_03_convo_template:addScreen(good_ten_years);

some_girl = ConvoScreen:new {
	id = "some_girl",
	leftDialog = "@conversation/padawan_old_musician_03:s_8dc8e232", -- Oh just some girl the two of them fought over for quite some time. Rumor has it that she is the reason the band broke up.
	stopConversation = "false",
	options = {
		{"@conversation/padawan_old_musician_03:s_3585e154", "need_a_shovel"} -- Do you know where I might be able to find her?
	}
}
padawan_old_musician_03_convo_template:addScreen(some_girl);

need_a_shovel = ConvoScreen:new {
	id = "need_a_shovel",
	leftDialog = "@conversation/padawan_old_musician_03:s_285ac110", -- You are going to need a shovel if you want to talk to her friend, and I'm afraid she isn't going to be saying much. She passed a few years back herself. As a matter of fact, I'm afraid the entire band, except for your friend Grizzlo, is no longer with us. It's a shame really; Samston told me they had two tunes in particular that really made people move.
	stopConversation = "false",
	options = {
		{"@conversation/padawan_old_musician_03:s_afbed875", "gave_ring"} -- Thank you for your time.
	}
}
padawan_old_musician_03_convo_template:addScreen(need_a_shovel);

gave_ring = ConvoScreen:new {
	id = "gave_ring",
	leftDialog = "@conversation/padawan_old_musician_03:s_77c9e846", -- No problem friend. Actually wait one second. Samston gave me this here ring, it belonged to that Twi'lek I was talking about before. I don't have much need for it and I'm sure Grizzy Two Tone would love to have it himself. Tell him Samston always wanted him to have it; it wouldn't be far from the truth. [You worry that the ring will be lost in your inventory, so you stow it in a safe place.]
	stopConversation = "true",
	options = {}
}
padawan_old_musician_03_convo_template:addScreen(gave_ring);

not_on_quest = ConvoScreen:new {
	id = "not_on_quest",
	leftDialog = "@conversation/padawan_old_musician_03:s_4ef8ad4d", -- I'm supposed to meet a friend, Branthon, and go see a theatrical performance tonight. If I don't go, Branthon has promised to write an essay revealing the entire plot of the show. It will consist of at least 20 words! I don't want that to happen.
	stopConversation = "true",
	options = {}
}
padawan_old_musician_03_convo_template:addScreen(not_on_quest);

addConversationTemplate("padawan_old_musician_03_convo_template", padawan_old_musician_03_convo_template);
