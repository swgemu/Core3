ral_mundi_convo_template = ConvoTemplate:new {
	initialScreen = "",
	templateType = "Lua",
	luaClassHandler = "ralMundiConvoHandler",
	screens = {}
}

no_jtl = ConvoScreen:new {
	id = "no_jtl",
	leftDialog = "@conversation/greeter_coronet_merchant:s_198d9a41", -- Greetings and welcome to Coronet. I apologize, but I don't have time to chat right now. If you'll excuse me.
	stopConversation = "true",
	options = {
	}
}
ral_mundi_convo_template:addScreen(no_jtl);

initial_greeting = ConvoScreen:new {
	id = "initial_greeting",
	leftDialog = "@conversation/greeter_coronet_merchant:s_4a019574", -- Greetings and welcome to Coronet. I apologize for my fading enthusiasm, but I've been waiting for quite some time for a shipment of goods to arrive. These two shipwrights have been waiting with me, and one of them is becoming especially belligerent.
	stopConversation = "false",
	options = {
		{"@conversation/greeter_coronet_merchant:s_80e2ba26", "why_are_they"}, -- Why are they waiting with you?
	}
}
ral_mundi_convo_template:addScreen(initial_greeting);

why_are_they = ConvoScreen:new {
	id = "why_are_they",
	leftDialog = "@conversation/greeter_coronet_merchant:s_82cd91e", -- They ordered some parts from me, and those parts should be in the missing shipment. I gave them a good price, but the long wait seems to have eroded their goodwill.
	stopConversation = "false",
	options = {
		{"@conversation/greeter_coronet_merchant:s_d48167e1", "thats_too_bad"}, -- That's too bad. I hope your goods arrive soon.
	}
}
ral_mundi_convo_template:addScreen(why_are_they);

thats_too_bad = ConvoScreen:new {
	id = "thats_too_bad",
	leftDialog = "@conversation/greeter_coronet_merchant:s_8ae971c3", -- Thank you for the kind words. It's more important than you might realize. I've put all of my available funds into this shipment. Without it I cannot complete my starships and uphold the construction contracts for them. I could lose everything.
	stopConversation = "false",
	options = {
		{"@conversation/greeter_coronet_merchant:s_89", "i_wish_i"}, -- I wish I could do something to help.
	}
}
ral_mundi_convo_template:addScreen(thats_too_bad);





--[[
"conversation/greeter_coronet_merchant"
"s_12157feb", "The military gives out free ships?");
"s_144ec5cc", "Sounds good. Thanks!");
"s_17bc5d9b", "When you approach the space station, use SHIFT+C to target it and open communication with the commander. You will be asked if you want to purchase repairs or if you want to land on the planet.");
"s_198d9a41", "Greetings and welcome to Coronet. I apologize, but I don't have time to chat. If you get involved with space flight, I might be able to answer some questions, but otherwise I'm not going to be of much help.");
"s_1a06c1df", "It doesn't.");
"s_21bf1a8c", "How do I join the Alliance?");
"s_270c87b2", "How do I get them to repair my ship?");
"s_27186cee", "I don't have enough money.");
"s_29894b97", "I don't know how to check.");
"s_3059f369", "What then?");
"s_309c383a", "On the lower right-hand side of your screen, there should be a 'letter' icon that is flashing. Double-click on this icon, and it will bring up your personal email. Read over the subject and sender, and scroll through the body text to get all the details.");
"s_32146025", "Then what?");
"s_3c81054", "That's what I hear. The Empire's pretty well-equipped after all and can't really have much of a navy if their pilots don't have ships. I've also heard rumors that the Alliance has a fleet of ships available so they can get new recruits into the fray as soon as possible.");
"s_472f61d1", "Local space stations are the easiest way to get your ship repaired. When you are heading back here, you should stop at the space station and ask them for repairs. They will provide a quick estimate on what it will take to get you back on track.");
"s_495777c0", "Have you checked any vendors? Merchants use vendors to help sell their merchandise. Shipwrights put finished starships and ship components for sale on their vendors, and then you can go to those vendors and purchase what you need.");
"s_4a019574", "Greetings and welcome to Coronet. I apologize for my fading enthusiasm, but I've been waiting for quite some time for a shipment of goods to arrive. These two shipwrights have been waiting with me, and one of them is becoming especially belligerent.");
"s_4eb2ac5d", "Good luck, kid! Anything else?");
"s_50095b25", "Not a problem. Anything else?");
"s_52939a0", "How do I check my email?");
"s_558a361a", "The Imperial Navy? I've heard that they are sending out recruitment emails to everyone they can locate these days. Have you checked your email today?");
"s_5618d2cd", "No. I have received no email.");
"s_5b893f7c", "It does.");
"s_5e410744", "Right-click on the map location to create and activate a waypoint. Follow the waypoint to the trainer's location.");
"s_5ff8baab", "I was wondering if you could answer some questions?");
"s_659f0dee", "Seeing as I have little else to do at the moment, ask away.");
"s_68cb68ff", "Is there anyone else I could fly for?");
"s_6f0ab63b", "Stay safe, my friend.");
"s_726e332f", "There are all sorts of civilian contracts available on the 'mission terminals' you find throughout town. Look for them near any major structure. Use the terminal to bring up the current list of local contracts. Choose the one that interests you the most, and you'll make money when the task is complete.");
"s_75698511", "Your best bet is to get in touch with the Empire and sign up for their training program. There are others who will urge you to put your efforts to use in the Alliance, but fools will be fools. Anything else?");
"s_80e2ba26", "Why are they waiting with you?");
"s_82cd91e", "They ordered some parts from me, and those parts should be in the missing shipment. I gave them a good price, but the long wait seems to have eroded their goodwill.");
"s_8515e448", "Yes. I have an email from the Imperial Navy.");
"s_8ae971c3", "Thank you for the kind words.");
"s_8b23fac", "I want to learn to fly.");
"s_8b37a99a", "How do I make money?");
"s_8cf9be64", "Where can I find a vendor?");
"s_8dd808e3", "Ask away.");
"s_8ef8dbfb", "I have another question.");
"s_93280d8a", "Good idea. Thanks!");
"s_9f7f7c0a", "I think that the majority of pilot trainers are registered with the planetary map. Try opening the planetary map with CTRL+V. On the right-hand side, there is a listing of categories. Look under 'trainer' to find any local pilot teacher who's looking for pupils.");
"s_a185791a", "Things are tough all over what with the Alliance and the Empire making with war and all. A lot of pilots are flying for either the Empire or the Rebellion these days. Ever think of joining the military to get a starship?");
"s_a463a3c1", "You're welcome. Anything else?");
"s_a9850aec", "I got an email from the Alliance!");
"s_acc368b1", "How do I join the Empire?");
"s_adc9d9e5", "Strange. Seems that if they undertook the risk to send you a message, they would make it clear how to respond. Why don't you check your email a little more carefully.");
"s_add31f19", "I need a starship.");
"s_af4397a9", "Interesting. Well, good luck with that. I don't want to get too close to the Galactic Civil War, myself.");
"s_b5d34085", "Could I ask some questions while you wait?");
"s_b641cda6", "Where can I find a bazaar terminal?");
"s_b78b7ed6", "Well, you're a pilot, and you've managed to land here, so that at least means starships are getting through to Corellia. But I still have no idea why my cargo has been delayed for so long.");
"s_b9b27823", "Thank you.");
"s_ba3c26af", "You did? These are desperate times, indeed. The email should probably indicate where you are supposed to go for initial recruitment.");
"s_ba95f774", "Bazaar terminals are located all over major cities. Check the areas surrounding major hot spots like the starport, the bank, any of the cantinas, or even the hospitals.");
"s_c2db6878", "Good-bye.");
"s_c4682ea6", "Thanks!");
"s_c9e97ed5", "How else would I join up?");
"s_cb747ceb", "Hmm. Me neither. Maybe you should give it a little time?");
"s_cc7c9754", "Don't mention it. Anything else?");
"s_cdb17e79", "How do I check the planetary map?");
"s_cf5fc0f", "How do I repair my starship?");
"s_d48167e1", "That's too bad. I hope your goods arrive soon.");
"s_d4c6e8cd", "No problem! Anything else?");
"s_d9231b4f", "There are freelance pilots working in most systems. Some are CorSec pilots, others are part of the RSF of Naboo, and of course, others are smugglers or pirates. I wouldn't recommend those last two if you want to pursue a lengthy career, but, at the same time, some of the best military pilots I know were once smugglers. Most freelance organizations will send recruitment emails. You might try checking your email for something like that.");
"s_da08c873", "That's sort of tricky. There may be some Alliance pilots bold enough to register their locations on the planetary map. Have you looked at the planetary map yet?");
"s_db064e66", "You have the look of a pilot from the Alliance. I'd better not find out you Rebels have stolen my shipment of goods.");
"s_e013f498", "Look for the flashing 'envelope' icon on your interface. It's placed on the lower right-hand side of your screen by default.");
"s_e1c13ebb", "Double-click on the envelope icon, and read your mail! Anything else?");
"s_e843e3ab", "Use the command CTRL+V to open the planetary map. On the right side of your display, you will see a listing of trainers by category. All local trainers who register with the planet will appear on this list. Click the 'Trainer' tab and then look for a pilot trainer.");
"s_e8b5b2ac", "Hello, sir. You're an Imperial Pilot, correct? Would you happen to know why my shipment might have been delayed? It's quite far behind schedule.");
"s_f2a4df5e", "Good idea! Thanks.");
"s_f3ec92a", "Use the planetary map to travel to the vendors listed on it, but not all vendors will be listed there. For the unlisted ones, you'll have to travel around looking for player-owned buildings that hold vendors. Once you've found a vendor, double-click it to see what it has for sale. You can also check bazaar terminals, but the listings on those will only be low-end starships and ship components, if even that.");
"s_f5f72ae1", "My pleasure. Anything else?");
"s_f90ad503", "I see. Thanks!");
"s_fbc4f153", "Hey, my pleasure. As long as I'm not busy. Anything else?");
"s_fd5402d8", "Ah! Then it should give you information about where to go to start your naval adventure. Good luck, my friend!");



]]
















welcome_i_cannot = ConvoScreen:new {
	id = "welcome_i_cannot",
	leftDialog = "@conversation/greeter_coronet_merchant:s_156", -- Welcome! I cannot thank you enough for your assistance. Thank you once again!
	stopConversation = "true",
	options = {
	}
}
ral_mundi_convo_template:addScreen(welcome_i_cannot);

the_missing_shipment = ConvoScreen:new {
	id = "the_missing_shipment",
	leftDialog = "@conversation/greeter_coronet_merchant:s_124", -- The missing shipment was at the capitol building? Unbelievable. I'll send some droids to go retrieve it. And the mystery crate contained spice? I'm astounded. Why in the world would a smuggled crate of spice end up at the capitol building? You don't think this involved the Diktat, do you? No, that's patently absurd, isn't it?  I'll have to alert CorSec of all this. Not that there's much they can do at this point. Thank you, though, for your help!
	stopConversation = "false",
	options = {
		{"@conversation/greeter_coronet_merchant:s_125", "it_was_my"}, -- It was my pleasure.
	}
}
ral_mundi_convo_template:addScreen(the_missing_shipment);

you_defeated_tomi = ConvoScreen:new {
	id = "you_defeated_tomi",
	leftDialog = "@conversation/greeter_coronet_merchant:s_123", -- You defeated Tomi? Well, I suppose it would come to that sooner or later. If you would, please, go to the capitol and find out if my shipment is really there. I cannot imagine why it would be at the capitol building.
	stopConversation = "true",
	options = {
	}
}
ral_mundi_convo_template:addScreen(you_defeated_tomi);

go_to_that = ConvoScreen:new {
	id = "go_to_that",
	leftDialog = "@conversation/greeter_coronet_merchant:s_122", -- Go to that bunker where Tomi is hiding and make him explain to you what is going on with all this.
	stopConversation = "true",
	options = {
	}
}
ral_mundi_convo_template:addScreen(go_to_that);

go_pressure_some = ConvoScreen:new {
	id = "go_pressure_some",
	leftDialog = "@conversation/greeter_coronet_merchant:s_155", -- Go pressure some Ragtags into revealing where to find Tomi Jinsin. You should be able to find some on the outskirts of the city. They are usually loitering around and harassing people.
	stopConversation = "true",
	options = {
	}
}
ral_mundi_convo_template:addScreen(go_pressure_some);

attacked_by_ragtags = ConvoScreen:new {
	id = "attacked_by_ragtags",
	leftDialog = "@conversation/greeter_coronet_merchant:s_109", -- Attacked by Ragtags? Those thugs who plague the planet? And amid the debris of what looked like the destroyed engines of large freighter or transport, no less. Very interesting.
	stopConversation = "false",
	options = {
		{"@conversation/greeter_coronet_merchant:s_114", "did_you_discover"}, -- Did you discover anything about the strange crate in your shipment?
	}
}
ral_mundi_convo_template:addScreen(attacked_by_ragtags);

you_didnt_find = ConvoScreen:new {
	id = "you_didnt_find",
	leftDialog = "@conversation/greeter_coronet_merchant:s_108", -- You didn't find anything? Nothing at all? Would you please go look again? I just know there must be some clue as to what happened out there. Maybe the transport broke down. Or was attacked. Please look again and be sure to fly the entire route.
	stopConversation = "false",
	options = {
		{"@conversation/greeter_coronet_merchant:s_110", "okay_ill_go"}, -- Okay, I'll go look again.
		{"@conversation/greeter_coronet_merchant:s_111", "i_dont_think"}, -- I don't think so. I'm done with this.
	}
}
ral_mundi_convo_template:addScreen(you_didnt_find);

launch_into_space = ConvoScreen:new {
	id = "launch_into_space",
	leftDialog = "@conversation/greeter_coronet_merchant:s_159", -- Launch into space and trace the route taken by the transport that was to deliver my shipment. Return to me when you've completed that and report anything out of the ordinary that happens.
	stopConversation = "true",
	options = {
	}
}
ral_mundi_convo_template:addScreen(launch_into_space);

whats_the_problem = ConvoScreen:new {
	id = "whats_the_problem",
	leftDialog = "@conversation/greeter_coronet_merchant:s_47", -- What's the problem?
	stopConversation = "false",
	options = {
		{"@conversation/greeter_coronet_merchant:s_48", "i_need_the_3"}, -- I need the route information again.
	}
}
ral_mundi_convo_template:addScreen(whats_the_problem);

excellent_and_good = ConvoScreen:new {
	id = "excellent_and_good",
	leftDialog = "@conversation/greeter_coronet_merchant:s_103", -- Excellent and good work. Let me take a look at these. Hmmm... this is odd. There's a crate in this shipment with no identification. I do not know what that could be or why it is in my shipment. While I look into this, I ask that you launch into Corellia space and trace the route flown by the transport delivering the shipment. Maybe you'll find a clue as to what happened.
	stopConversation = "false",
	options = {
		{"@conversation/greeter_coronet_merchant:s_104", "understood_ill_launch_5"}, -- Understood. I'll launch into Corellia space.
		{"@conversation/greeter_coronet_merchant:s_105", "i_dont_think_6"}, -- I don't think I'm interested. But good luck.
	}
}
ral_mundi_convo_template:addScreen(excellent_and_good);

you_have_the = ConvoScreen:new {
	id = "you_have_the",
	leftDialog = "@conversation/greeter_coronet_merchant:s_100", -- You have the shipment invoice, but I also need the shipping schedule. Speak with the starport master and ask for the shipping schedule for the transport delivering my shipment.
	stopConversation = "true",
	options = {
	}
}
ral_mundi_convo_template:addScreen(you_have_the);

you_have_the_1 = ConvoScreen:new {
	id = "you_have_the_1",
	leftDialog = "@conversation/greeter_coronet_merchant:s_102", -- You have the shipping schedule, but I still need the shipment invoice. Go speak to my assistant, Abagga Creel, and ask her for it.
	stopConversation = "true",
	options = {
	}
}
ral_mundi_convo_template:addScreen(you_have_the_1);

go_speak_to = ConvoScreen:new {
	id = "go_speak_to",
	leftDialog = "@conversation/greeter_coronet_merchant:s_101", -- Go speak to my assistant, Abagga Creel, and ask her for the shipment invoice. Also, speak with the starport master and ask for the shipping schedule for the transport delivering my shipment.
	stopConversation = "true",
	options = {
	}
}
ral_mundi_convo_template:addScreen(go_speak_to);



it_was_my = ConvoScreen:new {
	id = "it_was_my",
	leftDialog = "@conversation/greeter_coronet_merchant:s_126", -- You did a wonderful job. I have an opening in my warehouse if you're...no, what am I saying. That position is far beneath someone like you. But you do have my thanks. And now I must get back to making my starships.
	stopConversation = "true",
	options = {
	}
}
ral_mundi_convo_template:addScreen(it_was_my);

did_you_discover = ConvoScreen:new {
	id = "did_you_discover",
	leftDialog = "@conversation/greeter_coronet_merchant:s_115", -- Indeed I did. A low level employee in my warehouse named Tomi Jinsin has been accessing shipment records and adding something to deliveries from time to time over the past few months. Adding things like this unexplained crate. He's been fairly obvious about it. If I'd been paying more attention, I'd have likely noticed sooner. It's odd in a way. Almost like he wanted me to discover what he was doing.
	stopConversation = "false",
	options = {
		{"@conversation/greeter_coronet_merchant:s_116", "why_would_he"}, -- Why would he do that?
	}
}
ral_mundi_convo_template:addScreen(did_you_discover);

why_would_he = ConvoScreen:new {
	id = "why_would_he",
	leftDialog = "@conversation/greeter_coronet_merchant:s_117", -- Hmm? Oh, it's probably nothing. I'm sure he was just careless. In any case, we must find Tomi Jinsin. Unfortunately, I do not have any record of where he might live. But I suspect there must be some connection with these Ragtags. Maybe if you put some pressure on those thugs, they'll reveal what they know about Tomi. Seems like our best bet at this juncture.
	stopConversation = "false",
	options = {
		{"@conversation/greeter_coronet_merchant:s_118", "thats_a_good"}, -- That's a good idea. I'll go intimidate some Ragtags.
		{"@conversation/greeter_coronet_merchant:s_119", "no_thanks_i"}, -- No thanks. I think I've had enough of this.
	}
}
ral_mundi_convo_template:addScreen(why_would_he);

thats_a_good = ConvoScreen:new {
	id = "thats_a_good",
	leftDialog = "@conversation/greeter_coronet_merchant:s_120", -- You'll find Ragtags outside of most Corellia cities and Coronet is no exception. They're usually loitering around on the outskirts of the city. If you find anything about Tomi or my missing shipment, please follow it through.
	stopConversation = "true",
	options = {
	}
}
ral_mundi_convo_template:addScreen(thats_a_good);

no_thanks_i = ConvoScreen:new {
	id = "no_thanks_i",
	leftDialog = "@conversation/greeter_coronet_merchant:s_121", -- I understand. Those Ragtags are likely to get violent. I don't blame you for stepping away.
	stopConversation = "true",
	options = {
	}
}
ral_mundi_convo_template:addScreen(no_thanks_i);

okay_ill_go = ConvoScreen:new {
	id = "okay_ill_go",
	leftDialog = "@conversation/greeter_coronet_merchant:s_112", -- Thank you. Be sure to fly the entire route.
	stopConversation = "true",
	options = {
	}
}
ral_mundi_convo_template:addScreen(okay_ill_go);

i_dont_think = ConvoScreen:new {
	id = "i_dont_think",
	leftDialog = "@conversation/greeter_coronet_merchant:s_113", -- Very well. I probably should not ask so much of someone I barely know.
	stopConversation = "true",
	options = {
	}
}
ral_mundi_convo_template:addScreen(i_dont_think);

i_need_the = ConvoScreen:new {
	id = "i_need_the",
	leftDialog = "@conversation/greeter_coronet_merchant:s_57", -- Very well. Here is the information.
	stopConversation = "true",
	options = {
	}
}
ral_mundi_convo_template:addScreen(i_need_the);

i_need_the_3 = ConvoScreen:new {
	id = "i_need_the_3",
	leftDialog = "@conversation/greeter_coronet_merchant:s_49", -- Very well. I will transfer the information to you now.
	stopConversation = "true",
	options = {
	}
}
ral_mundi_convo_template:addScreen(i_need_the_3);

understood_ill_launch = ConvoScreen:new {
	id = "understood_ill_launch",
	leftDialog = "@conversation/greeter_coronet_merchant:s_160", -- Oh my, it looks like you already have a mission for space. Talk to me again when you've completed it and are ready for a new space mission.
	stopConversation = "true",
	options = {
	}
}
ral_mundi_convo_template:addScreen(understood_ill_launch);

understood_ill_launch_4 = ConvoScreen:new {
	id = "understood_ill_launch_4",
	leftDialog = "@conversation/greeter_coronet_merchant:s_53", -- I appreciate your enthusiasm, but it appears you don't have a ship. Here take this one, I don't need it anymore, and it should be more than adequate for your needs.
	stopConversation = "false",
	options = {
	}
}
ral_mundi_convo_template:addScreen(understood_ill_launch_4);

understood_ill_launch_5 = ConvoScreen:new {
	id = "understood_ill_launch_5",
	leftDialog = "@conversation/greeter_coronet_merchant:s_106", -- Thank you. Return and report anything out of the ordinary to me.
	stopConversation = "true",
	options = {
	}
}
ral_mundi_convo_template:addScreen(understood_ill_launch_5);

i_dont_think_6 = ConvoScreen:new {
	id = "i_dont_think_6",
	leftDialog = "@conversation/greeter_coronet_merchant:s_107", -- Very well. I'll try to pursue this on my own.
	stopConversation = "true",
	options = {
	}
}
ral_mundi_convo_template:addScreen(i_dont_think_6);

thank_you_i = ConvoScreen:new {
	id = "thank_you_i",
	leftDialog = "@conversation/greeter_coronet_merchant:s_160", -- Oh my, it looks like you already have a mission for space. Talk to me again when you've completed it and are ready for a new space mission.
	stopConversation = "true",
	options = {
	}
}
ral_mundi_convo_template:addScreen(thank_you_i);

thank_you_i_7 = ConvoScreen:new {
	id = "thank_you_i_7",
	leftDialog = "@conversation/greeter_coronet_merchant:s_53", -- I appreciate your enthusiasm, but it appears you don't have a ship. Here take this one, I don't need it anymore, and it should be more than adequate for your needs.
	stopConversation = "false",
	options = {
	}
}
ral_mundi_convo_template:addScreen(thank_you_i_7);

thank_you_i_8 = ConvoScreen:new {
	id = "thank_you_i_8",
	leftDialog = "@conversation/greeter_coronet_merchant:s_106", -- Thank you. Return and report anything out of the ordinary to me.
	stopConversation = "true",
	options = {
	}
}
ral_mundi_convo_template:addScreen(thank_you_i_8);




i_wish_i = ConvoScreen:new {
	id = "i_wish_i",
	leftDialog = "@conversation/greeter_coronet_merchant:s_91", -- Maybe you can. You could help me track down my missing shipment. If you're able to find it, then not only will I be able to fulfill the order these two gentlemen placed, but I'll also be able to complete construction on my own starships.
	stopConversation = "false",
	options = {
		{"@conversation/greeter_coronet_merchant:s_92", "what_would_i"}, -- What would I need to do?
	}
}
ral_mundi_convo_template:addScreen(i_wish_i);

what_would_i = ConvoScreen:new {
	id = "what_would_i",
	leftDialog = "@conversation/greeter_coronet_merchant:s_94", -- To start, go speak with my assistant, Abagga Creel, and get a shipment invoice for the missing shipment. She's at our office building here in Coronet. Also, speak to the starport master and get a shipping schedule for the transport that was supposed to make the delivery.
	stopConversation = "false",
	options = {
		{"@conversation/greeter_coronet_merchant:s_96", "okay_ill_do"}, -- Okay, I'll do it.
		{"@conversation/greeter_coronet_merchant:s_97", "no_thanks_im"}, -- No thanks. I'm not interested.
	}
}
ral_mundi_convo_template:addScreen(what_would_i);

okay_ill_do = ConvoScreen:new {
	id = "okay_ill_do",
	leftDialog = "@conversation/greeter_coronet_merchant:s_98", -- Thank you! Return to me when you have both the invoice and the schedule.
	stopConversation = "true",
	options = {
	}
}
ral_mundi_convo_template:addScreen(okay_ill_do);

no_thanks_im = ConvoScreen:new {
	id = "no_thanks_im",
	leftDialog = "@conversation/greeter_coronet_merchant:s_99", -- I understand. Hopefully it'll arrive soon anyway.
	stopConversation = "true",
	options = {
	}
}
ral_mundi_convo_template:addScreen(no_thanks_im);

addConversationTemplate("ral_mundi_convo_template", ral_mundi_convo_template);
