museumCuratorConvoTemplate = ConvoTemplate:new {
	initialScreen = "",
	templateType = "Lua",
	luaClassHandler = "museum_curator_conv_handler",
	screens = {}
}

init_votephase = ConvoScreen:new {
	id = "init_votephase",
	leftDialog = "@conversation/lilas_dinhint:s_605d9185", -- Hello and welcome to the Bestine Museum. I hope you enjoy your visit. While I've got your ear, you should know that we are currently seeking a new work of art to feature. Would you like to help?
	stopConversation = "false",
	options = {}
}
museumCuratorConvoTemplate:addScreen(init_votephase);

pick_artist = ConvoScreen:new {
	id = "pick_artist",
	leftDialog = "@conversation/lilas_dinhint:s_3960dc15", -- Ah good. Which artist stood out as your favorite?
	stopConversation = "false",
	options = {}
}
museumCuratorConvoTemplate:addScreen(pick_artist);

explain_contest = ConvoScreen:new {
	id = "explain_contest",
	leftDialog = "@conversation/lilas_dinhint:s_7312fa13", -- Excellent. Once per month, I wish to feature a new work of art here at the museum. We have a fine permanent collection on display, as always, but it is my desire to enhance that collection by offering something new from time to time. To that end, we select a small number of artists and approach them with the chance of having their art featured here in Bestine.
	stopConversation = "false",
	options = {
		{"@conversation/lilas_dinhint:s_5bd69df6", "seek_out_artists"}, -- What do you need me to do?
		{"@conversation/lilas_dinhint:s_463a0bda", "thanks_for_visiting"} -- Um... nevermind. I'm not interested in this.
	}
}
museumCuratorConvoTemplate:addScreen(explain_contest);

seek_out_artists = ConvoScreen:new {
	id = "seek_out_artists",
	leftDialog = "@conversation/lilas_dinhint:s_147d9a5b", -- What I ask is that you seek out the artists we are considering and learn of their work. Then return to me and let me know which of them you preferred. Three artists are involved. I can tell you where to find them if you'd like?
	stopConversation = "false",
	options = {}
}
museumCuratorConvoTemplate:addScreen(seek_out_artists);

find_boulo_siesi = ConvoScreen:new {
	id = "find_boulo_siesi",
	leftDialog = "@conversation/lilas_dinhint:s_36cff745", -- Boulo Siesi is in Wayfar. She's usually by the cantina.
	stopConversation = "false",
	options = {}
}
museumCuratorConvoTemplate:addScreen(find_boulo_siesi);

find_vanvi_hotne = ConvoScreen:new {
	id = "find_vanvi_hotne",
	leftDialog = "@conversation/lilas_dinhint:s_400d075", -- Look for a small square near the Lucky Despot, and you'll find Vanvi Hotne in that area.
	stopConversation = "false",
	options = {}
}
museumCuratorConvoTemplate:addScreen(find_vanvi_hotne);

find_giaal_itotr = ConvoScreen:new {
	id = "find_giaal_itotr",
	leftDialog = "@conversation/lilas_dinhint:s_23b5bcf", -- Giaal Itotr calls Mos Espa home, and you'll usually find him in front of the hotel.
	stopConversation = "false",
	options = {}
}
museumCuratorConvoTemplate:addScreen(find_giaal_itotr);

find_kahfr_oladi = ConvoScreen:new {
	id = "find_kahfr_oladi",
	leftDialog = "@conversation/lilas_dinhint:s_1057c81b", -- Try Mos Eisley to find Kahfr Oladi. You'll probably find her near the bank. 
	stopConversation = "false",
	options = {}
}
museumCuratorConvoTemplate:addScreen(find_kahfr_oladi);

find_klepa_laeel = ConvoScreen:new {
	id = "find_klepa_laeel",
	leftDialog = "@conversation/lilas_dinhint:s_68c6c699", -- You'll find Klepa Laeel in Mos Espa. He's often found towards the back of the starport.
	stopConversation = "false",
	options = {}
}
museumCuratorConvoTemplate:addScreen(find_klepa_laeel);

find_kolka_zteht = ConvoScreen:new {
	id = "find_kolka_zteht",
	leftDialog = "@conversation/lilas_dinhint:s_67026fa8", -- Look near the back of the theater in Mos Entha to find Kolka Zteht.
	stopConversation = "false",
	options = {}
}
museumCuratorConvoTemplate:addScreen(find_kolka_zteht);

pleasure_all_mine = ConvoScreen:new {
	id = "pleasure_all_mine",
	leftDialog = "@conversation/lilas_dinhint:s_8338587c", -- The pleasure is all mine. Return after speaking to the artists. Farewell.
	stopConversation = "true",
	options = {}
}
museumCuratorConvoTemplate:addScreen(pleasure_all_mine);

thanks_for_visiting = ConvoScreen:new {
	id = "thanks_for_visiting",
	leftDialog = "@conversation/lilas_dinhint:s_fb2eead4", -- Very well. Thank you for visiting the museum. 
	stopConversation = "true",
	options = {}
}
museumCuratorConvoTemplate:addScreen(thanks_for_visiting);

picked_vanvi_hotne = ConvoScreen:new {
	id = "picked_vanvi_hotne",
	leftDialog = "@conversation/lilas_dinhint:s_b67247f1", -- Perfect, thank you!
	stopConversation = "true",
	options = {}
}
museumCuratorConvoTemplate:addScreen(picked_vanvi_hotne);

picked_kolka_zteht = ConvoScreen:new {
	id = "picked_kolka_zteht",
	leftDialog = "@conversation/lilas_dinhint:s_b67247f1", -- Perfect, thank you!
	stopConversation = "true",
	options = {}
}
museumCuratorConvoTemplate:addScreen(picked_kolka_zteht);


picked_giaal_itotr = ConvoScreen:new {
	id = "picked_giaal_itotr",
	leftDialog = "@conversation/lilas_dinhint:s_b67247f1", -- Perfect, thank you!
	stopConversation = "true",
	options = {}
}
museumCuratorConvoTemplate:addScreen(picked_giaal_itotr);


picked_kahfr_oladi = ConvoScreen:new {
	id = "picked_kahfr_oladi",
	leftDialog = "@conversation/lilas_dinhint:s_b67247f1", -- Perfect, thank you!
	stopConversation = "true",
	options = {}
}
museumCuratorConvoTemplate:addScreen(picked_kahfr_oladi);


picked_klepa_laeel = ConvoScreen:new {
	id = "picked_klepa_laeel",
	leftDialog = "@conversation/lilas_dinhint:s_b67247f1", -- Perfect, thank you!
	stopConversation = "true",
	options = {}
}
museumCuratorConvoTemplate:addScreen(picked_klepa_laeel);


picked_boulo_siesi = ConvoScreen:new {
	id = "picked_boulo_siesi",
	leftDialog = "@conversation/lilas_dinhint:s_b67247f1", -- Perfect, thank you!
	stopConversation = "true",
	options = {}
}
museumCuratorConvoTemplate:addScreen(picked_boulo_siesi);


enjoy_visit_votephase = ConvoScreen:new {
	id = "enjoy_visit_votephase",
	leftDialog = "@conversation/lilas_dinhint:s_1aabf4f7", -- I hope you enjoy your visit. Take your time and wander through our collection. It's still not as large as I'd like, but I'm working on that.
	stopConversation = "true",
	options = {}
}
museumCuratorConvoTemplate:addScreen(enjoy_visit_votephase);

init_buyphase = ConvoScreen:new {
	id = "init_buyphase",
	leftDialog = "@conversation/lilas_dinhint:s_5d4aadf9", -- Hello and welcome to the Bestine Museum. Would you like to purchase a schematic of our featured artwork?
	stopConversation = "false",
	options = {}
}
museumCuratorConvoTemplate:addScreen(init_buyphase);

in_less_than_an_hour = ConvoScreen:new {
	id = "in_less_than_an_hour",
	leftDialog = "@conversation/lilas_dinhint:s_6dbeccc3", -- We'll begin the search for another featured work of art within the hour.
	stopConversation = "true",
	options = {}
}
museumCuratorConvoTemplate:addScreen(in_less_than_an_hour);

in_a_few_hours = ConvoScreen:new {
	id = "in_a_few_hours",
	leftDialog = "@conversation/lilas_dinhint:s_4f049f4e", -- In just a few hours we'll start the search for our next featured artwork.
	stopConversation = "true",
	options = {}
}
museumCuratorConvoTemplate:addScreen(in_a_few_hours);

in_less_than_a_day = ConvoScreen:new {
	id = "in_less_than_a_day",
	leftDialog = "@conversation/lilas_dinhint:s_5bc37444", -- It will be less than a day before we begin looking for another work of art that we'll feature here the museum.
	stopConversation = "true",
	options = {}
}
museumCuratorConvoTemplate:addScreen(in_less_than_a_day);

in_more_than_a_day = ConvoScreen:new {
	id = "in_more_than_a_day",
	leftDialog = "@conversation/lilas_dinhint:s_519f72a3", -- There's still more than a day before the search for our next featured work of art begins.
	stopConversation = "true",
	options = {}
}
museumCuratorConvoTemplate:addScreen(in_more_than_a_day);

in_less_than_a_week = ConvoScreen:new {
	id = "in_less_than_a_week",
	leftDialog = "@conversation/lilas_dinhint:s_35487421", -- We'll being looking in less than a week for the next work of art to be featured in the museum.
	stopConversation = "true",
	options = {}
}
museumCuratorConvoTemplate:addScreen(in_less_than_a_week);

in_more_than_a_week = ConvoScreen:new {
	id = "in_more_than_a_week",
	leftDialog = "@conversation/lilas_dinhint:s_a9f1e0f9", -- Oh, it'll be more than a week before we begin the search for our next featured work of art.
	stopConversation = "true",
	options = {}
}
museumCuratorConvoTemplate:addScreen(in_more_than_a_week);

schematic_cost = ConvoScreen:new {
	id = "schematic_cost",
	leftDialog = "@conversation/lilas_dinhint:s_486f6", -- I'm asking for a modest... ahem... donation to the museum of 48,000 credits in exchange for the schematic. Oh, and I should warn you that some knowledge of advanced furniture production is required.
	stopConversation = "false",
	options = {}
}
museumCuratorConvoTemplate:addScreen(schematic_cost);

hello_no_voting = ConvoScreen:new {
	id = "hello_no_voting",
	leftDialog = "@conversation/lilas_dinhint:s_aaa43f7b", -- Hello and welcome to the Bestine Museum.
	stopConversation = "true",
	options = {}
}
museumCuratorConvoTemplate:addScreen(hello_no_voting);

already_voted = ConvoScreen:new {
	id = "already_voted",
	leftDialog = "@conversation/lilas_dinhint:s_375a5dc0", -- Thank you for taking part in our contest. Check back when the event ends to see who won. Note that the event is 15 days from beginning to end and that the winning work of art will be on display for 30 days. That 30 days includes the 15 days between events as well as the 15 days of the next event. Thanks again!
	stopConversation = "true",
	options = {}
}
museumCuratorConvoTemplate:addScreen(already_voted);

hello_already_purchased = ConvoScreen:new {
	id = "hello_already_purchased",
	leftDialog = "@conversation/lilas_dinhint:s_aaa43f7b", -- Hello and welcome to the Bestine Museum.
	stopConversation = "false",
	options = {}
}
museumCuratorConvoTemplate:addScreen(hello_already_purchased);

full_inventory = ConvoScreen:new {
	id = "full_inventory",
	leftDialog = "@conversation/lilas_dinhint:s_c845a58c", -- It would appear that you are unable to carry it. Please return after you made some space in your inventory.
	stopConversation = "true",
	options = {}
}
museumCuratorConvoTemplate:addScreen(full_inventory);

not_enough_credits = ConvoScreen:new {
	id = "not_enough_credits",
	leftDialog = "@conversation/lilas_dinhint:s_c8e54945", -- I'm afraid you don't have enough credits, and I must insist on the donation. Please return when you have more funds available.
	stopConversation = "true",
	options = {}
}
museumCuratorConvoTemplate:addScreen(not_enough_credits);

schematic_purchased = ConvoScreen:new {
	id = "schematic_purchased",
	leftDialog = "@conversation/lilas_dinhint:s_7882a978", -- [Smiling] Excellent. Now, where did I leave those. Oh yes, here they are. Thank you for supporting the arts.
	stopConversation = "true",
	options = {}
}
museumCuratorConvoTemplate:addScreen(schematic_purchased);


addConversationTemplate("museumCuratorConvoTemplate", museumCuratorConvoTemplate);