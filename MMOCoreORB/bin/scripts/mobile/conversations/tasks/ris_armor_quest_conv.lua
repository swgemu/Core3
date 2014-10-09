risArmorQuestConvoTemplate = ConvoTemplate:new {
	initialScreen = "",
	templateType = "Lua",
	luaClassHandler = "risArmorQuestConvoHandler",
	screens = {}
}

not_master_armorsmith = ConvoScreen:new {
	id = "not_master_armorsmith",
	leftDialog = "@quest_armorsmith:greeting", -- Bah! You waste my time. The armor crafting techniques I have to offer are far beyond your comprehension. Come back when you have mastered the armorsmith profession and maybe then you'll have some chance to understand what I have to teach.
	stopConversation = "true",
	options = {}
}
risArmorQuestConvoTemplate:addScreen(not_master_armorsmith);

quest_1_start = ConvoScreen:new {
	id = "quest_1_start",
	leftDialog = "@quest_armorsmith:quest_1_start", -- You believe you have learned all there is to know about being armorsmith. You haven't! I know far more than you ever will, but still there are a few lessons I could teach you. Learning these things will not be easy for someone such as you. It will be expensive in both time and in credits. Furthermore, I have no patience for insolent students. You do as I say and don't bother me with stupid questions! So what to you say? Give me %DI credits and we'll get started. Be quick about it! I'm very busy.
	stopConversation = "false",
	options = {
	}
}
risArmorQuestConvoTemplate:addScreen(quest_1_start);

quest_1_start_yes = ConvoScreen:new {
	id = "quest_1_start_yes",
	leftDialog = "@quest_armorsmith:quest_1_start_yes", -- I suspected you would agree to my terms. Let's get started. I'm going to teach you how to construct my masterpiece invention: R.I.S armor. This armor has no equal in battle. Everything else is junk compared to this! Of course, it is exceedingly difficult to create, especially for a fledgling armorsmith such as you. But, no matter. We'll take it slow so you can comprehend. Are you with me so far?
	stopConversation = "false",
	options = {
		{"@quest_armorsmith:yes", "quest_1_description"}, -- Yes.
		{"@quest_armorsmith:no", "quest_1_start_no"}, -- No.
	}
}
risArmorQuestConvoTemplate:addScreen(quest_1_start_yes);

quest_1_start_no = ConvoScreen:new {
	id = "quest_1_start_no",
	leftDialog = "@quest_armorsmith:quest_1_start_no", -- Bah! Then be off with the likes of you! I have no time for armorsmith lackies!
	stopConversation = "true",
	options = {}
}
risArmorQuestConvoTemplate:addScreen(quest_1_start_no);

quest_1_description = ConvoScreen:new {
	id = "quest_1_description",
	leftDialog = "@quest_armorsmith:quest_1_description", -- As you know, creating armor starts with the armor segment. That is where we shall start as well. Like all armor segements, R.I.S. segment require resources which I'm sure you already know how to acquire. They also, however, require some special components. For strength, they require bone fragments from a Woolamander Harrower. For flexibility, they require the hide of a Recluse Gurk King. Use this schematic to create the armor segment and bring it back to me. I don't care how you get the materials, but you must construct the segment yourself. You can only learn by doing it yourself! Now go busy yourself with making the armor segment and come back to me when you are done.
	stopConversation = "true",
	options = {}
}
risArmorQuestConvoTemplate:addScreen(quest_1_description);

quest_2_query = ConvoScreen:new {
	id = "quest_2_query",
	leftDialog = "@quest_armorsmith:quest_2_query", -- The student returns! Show me what you have learned in crafting the %TO.
	stopConversation = "false",
	options = {
	}
}
risArmorQuestConvoTemplate:addScreen(quest_2_query);

quest_2_complete = ConvoScreen:new {
	id = "quest_2_complete",
	leftDialog = "@quest_armorsmith:quest_2_complete", -- Let's see how you did... Bah! Look at these mounting tabs! They aren't even on straight! This flexor matrix has the plasticity of carbonite! I was hoping for a better showing, my student, but I guess this will have to do. Keep practicing. If you can't handle the fundamentals, everything else will suffer! But no! I'm sure you don't want to practice. Just rush onto the next lesson, I bet. I suppose that's what you want to do?
	stopConversation = "false",
	options = {
		{"@quest_armorsmith:yes_to_quest_3_start", "quest_3_start"}, -- Yes, I am ready to continue.
		{"@quest_armorsmith:no_to_quest_3_start", "quest_3_start_no"} -- No. I'd rather practice what I've already learned.
	}
}
risArmorQuestConvoTemplate:addScreen(quest_2_complete);


quest_2_incomplete = ConvoScreen:new {
	id = "quest_2_incomplete",
	leftDialog = "@quest_armorsmith:quest_2_incomplete", -- Bah! Then why are you here? Don't expect me to do everything it for you. If you want to learn, but have to be willing to put in the effort! Now get to work!
	stopConversation = "true",
	options = {}
}
risArmorQuestConvoTemplate:addScreen(quest_2_incomplete);

quest_3_start = ConvoScreen:new {
	id = "quest_3_start",
	leftDialog = "@quest_armorsmith:quest_3_start", -- Next I will to teach you how to craft the R.I.S armor layer. A remarkable component this is. Not only does it add additional protection, it can actually reduce encumbrance if masterfully crafted! Like all armor layers, it'll work with any armor segment, making even those inferior armor types better. Here's the schematic. You'll need some feathers from the rare Peko Peko Albatross... a bit nasty of a critter. Hop to it!
	stopConversation = "true",
	options = {}
}
risArmorQuestConvoTemplate:addScreen(quest_3_start);

quest_3_start_no = ConvoScreen:new {
	id = "quest_3_start_no",
	leftDialog = "@quest_armorsmith:quest_3_start_no", -- Fine, fine. Practice up. Come back when you are ready for the next lesson.
	stopConversation = "true",
	options = {}
}		
risArmorQuestConvoTemplate:addScreen(quest_3_start_no);

quest_4_query = ConvoScreen:new {
	id = "quest_4_query",
	leftDialog = "@quest_armorsmith:quest_4_query", -- You return again. Okay, let's see it. Where's the %TO you crafted?
	stopConversation = "false",
	options = {
	}
}
risArmorQuestConvoTemplate:addScreen(quest_4_query);

quest_4_complete = ConvoScreen:new {
	id = "quest_4_complete",
	leftDialog = "@quest_armorsmith:quest_4_complete", -- Let's see how you did this time... Bah! The lattice orientation of the absorption medium should be 65.3 degrees off of the axis of principal stress of the reinforcement matrix. 65.3 degrees! How do you expect this to handle blaster fire any other way? Still, it isn't terrible for a first attempt. Of course, I'd be embarrassed to put my name on that thing, but that's why I'm the teacher and you're the student. Are you ready for the next lesson?
	stopConversation = "false",
	options = {
		{"@quest_armorsmith:yes_to_quest_5_start", "quest_5_start"}, -- Yes. I am ready to learn more.
		{"@quest_armorsmith:no_to_quest_5_start", "quest_5_start_no"} -- No. I'm not ready for the next lesson.
	}
}
risArmorQuestConvoTemplate:addScreen(quest_4_complete);


quest_4_incomplete = ConvoScreen:new {
	id = "quest_4_incomplete",
	leftDialog = "@quest_armorsmith:quest_4_incomplete", -- Well then, go on and get that finished up. I'm not going anywhere.
	stopConversation = "true",
	options = {}
}
risArmorQuestConvoTemplate:addScreen(quest_4_incomplete);

quest_5_start = ConvoScreen:new {
	id = "quest_5_start",
	leftDialog = "@quest_armorsmith:quest_5_start", -- You've finally managed to learned the basics. Now I will teach you how to craft the armor, itself. We'll start with the boots. If you can't get the boots right, I don't care how good the rest of the armor is. If your feet hurt, it just doesn't matter! Here's the schematic for the boots. In addition to the resources you'll also need some scales from a Giant Dune Kimogila. Better pack your desert gear and rocket launcher.
	stopConversation = "true",
	options = {}
}
risArmorQuestConvoTemplate:addScreen(quest_5_start);

quest_5_start_no = ConvoScreen:new {
	id = "quest_5_start_no",
	leftDialog = "@quest_armorsmith:quest_5_start_no", -- No ready, huh? Very well, I'll be here when you are.
	stopConversation = "true",
	options = {}
}		
risArmorQuestConvoTemplate:addScreen(quest_5_start_no);

quest_6_query = ConvoScreen:new {
	id = "quest_6_query",
	leftDialog = "@quest_armorsmith:quest_6_query", -- Back again! Most of my students have quit by this point. Let's see the %TO you crafted.
	stopConversation = "false",
	options = {
	}
}
risArmorQuestConvoTemplate:addScreen(quest_6_query);

quest_6_complete = ConvoScreen:new {
	id = "quest_6_complete",
	leftDialog = "@quest_armorsmith:quest_6_complete", -- A little small, don't you think? Who were you making these for? A Jawa? Nevertheless, these do look marginally acceptable. I think you are getting the hang of this. Tell you what. I think you've learned enough to do this on your own. Here's the rest of the schematics. Don't make me look bad and don't forget to practice, practice. And be sure to come back and visit sometimes. It's not every day that I have a student actually complete my lessons. Now, I'll be getting back to my work...
	stopConversation = "true",
	options = {}
}
risArmorQuestConvoTemplate:addScreen(quest_6_complete);


quest_6_incomplete = ConvoScreen:new {
	id = "quest_6_incomplete",
	leftDialog = "@quest_armorsmith:quest_6_incomplete", -- Don't let me down now! Get crafting!
	stopConversation = "true",
	options = {}
}
risArmorQuestConvoTemplate:addScreen(quest_6_incomplete);

completed_all_quests = ConvoScreen:new {
	id = "completed_all_quests",
	leftDialog = "@quest_armorsmith:armorsmith_quest", -- Welcome back, my student! There is nothing more I'm willing to teach you about R.I.S. armor crafting. Practice, practice. You'll get it right one of these days.
	stopConversation = "true",
	options = {}
}
risArmorQuestConvoTemplate:addScreen(completed_all_quests);

illegal_response = ConvoScreen:new {
	id = "illegal_response",
	leftDialog = "@quest_armorsmith:illegal_response", -- Bah! Trying to pull a fast one over me? I'm far too intelligent to fall for such a dimwitted scheme.
	stopConversation = "true",
	options = {}
}
risArmorQuestConvoTemplate:addScreen(illegal_response);

not_enough_money = ConvoScreen:new {
	id = "not_enough_money",
	leftDialog = "@quest_armorsmith:not_enough_money", -- Bah! You don't even have enough money. What kind of armorsmith are you? Go get some work and come back when you can pay my fee.
	stopConversation = "true",
	options = {}
}
risArmorQuestConvoTemplate:addScreen(not_enough_money);

addConversationTemplate("risArmorQuestConvoTemplate", risArmorQuestConvoTemplate);
