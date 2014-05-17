chosterConvoTemplate = ConvoTemplate:new {
	initialScreen = "",
	templateType = "Lua",
	luaClassHandler = "theme_park_nym_conv_handler",
	screens = {}
}

----------
--Choster initial convo
----------
hello = ConvoScreen:new {
	id = "hello",
	leftDialog = "@celebrity/lok_engineer:hello", -- Something I can help you with?  I don't seem to recall your face, but I'm getting a little long in the tooth.  Do we know each other?
	stopConversation = "false",
	options = {
	-- Either or depending on if they are on quest line
	-- {"@celebrity/lok_engineer:who_are_you", "just_a_guy"}, -- I don't think so.  Who are you?
	-- {"@celebrity/lok_engineer:who_are_you_2", "go_away_dude"}, -- Who are you?
	}
}
chosterConvoTemplate:addScreen(hello);

go_away_dude = ConvoScreen:new {
	id = "go_away_dude",
	leftDialog = "@celebrity/lok_engineer:go_away_dude", -- Nobody. And you like your fingers attached to your hands, you'll just leave it at that.
	stopConversation = "true",
	options = {
	}
}
chosterConvoTemplate:addScreen(go_away_dude);

just_a_guy = ConvoScreen:new {
	id = "just_a_guy",
	leftDialog = "@celebrity/lok_engineer:just_a_guy", -- Just someone who's been stuck on Lok for too long, but you can call me Choster. It seems I've seen a thousand fringers just like you wandering this wasteland. You sure we haven't met?
	stopConversation = "false",
	options = {
		{"@celebrity/lok_engineer:jinkins_sent_me", "i_know_jinkins"}, -- No. But I'm a friend of Jinkin's.
	}
}
chosterConvoTemplate:addScreen(just_a_guy);

i_know_jinkins = ConvoScreen:new {
	id = "i_know_jinkins",
	leftDialog = "@celebrity/lok_engineer:i_know_jinkins", -- Ah, yes! Jinkins. A brilliant engineer. I'm not sure why he sticks with those Lok Revenants, though. He could have made a fortune as a starship designer, but he's been loyal to Nym since before the Battle of Naboo. But, if Jinkins sent you, then I'm sure I know why. You want to know about the Sulfur Lake Pirates and the engineering work I did for them.
	stopConversation = "false",
	options = {
		{"@celebrity/lok_engineer:talk_pirates", "sulfur_lake_pirates"}, -- No. But I'm a friend of Jinkin's.
	}
}
chosterConvoTemplate:addScreen(i_know_jinkins);

sulfur_lake_pirates = ConvoScreen:new {
	id = "sulfur_lake_pirates",
	leftDialog = "@celebrity/lok_engineer:sulfur_lake_pirates", -- The Sulfur Lake Pirates aren't the brightest pirate band on Lok. First, they named themselves after the lake where they have their "hidden" lair. When they realized that every other group on Lok knew where they were holed up, the Sulfur crew hired me to set up some defenses. We eventually had a... falling out. There's no band of thieves that I hate more.
	stopConversation = "false",
	options = {
		{"@celebrity/lok_engineer:hate_pirates", "pirates_fired"}, -- Why do you hate them?
	}
}
chosterConvoTemplate:addScreen(sulfur_lake_pirates);

pirates_fired = ConvoScreen:new {
	id = "pirates_fired",
	leftDialog = "@celebrity/lok_engineer:pirates_fired", -- After I set up their systems, the Sulfur morons decided that it would be easier, and maybe safer, to kill me instead of pay me. I barely escaped their bloodthirsty veermok with my life.  I had to change my name and find an image designer to give me a new face. But I don't forget or forgive being betrayed. I came back here to hide on Lok, waiting for a chance to repay them.
	stopConversation = "false",
	options = {
		{"@celebrity/lok_engineer:talk_engineer", "security_system"}, -- What kind of work did you do?
	}
}
chosterConvoTemplate:addScreen(pirates_fired);

security_system = ConvoScreen:new {
	id = "security_system",
	leftDialog = "@celebrity/lok_engineer:security_system", -- I established the safeguards on their security system. It's not too dangerous, but does keep visitors out of the back room. Anyone who wants to enter needs to punch in a series of codes, which only the pirates know. But I did leave a backdoor: I gave the security system a rudimentary AI that will ask three questions to anyone who doesn't have the code.
	stopConversation = "false",
	options = {
		{"@celebrity/lok_engineer:defenses", "which_defense"}, -- Can you tell me more about this system's "backdoor"?
	}
}
chosterConvoTemplate:addScreen(security_system);

which_defense = ConvoScreen:new {
	id = "which_defense",
	leftDialog = "@celebrity/lok_engineer:which_defense", -- I established the safeguards on their security system. It's not too dangerous, but does keep visitors out of the back room. Anyone who wants to enter needs to punch in a series of codes, which only the pirates know. But I did leave a backdoor: I gave the security system a rudimentary AI that will ask three questions to anyone who doesn't have the code.
	stopConversation = "false",
	options = {
		{"@celebrity/lok_engineer:color_defense", "pirate_artist"}, -- Tell me about the color spectrum.
		{"@celebrity/lok_engineer:math_defense", "sequential_numbers"}, -- Tell me about the math problems.
		{"@celebrity/lok_engineer:other_defense", "pirate_joker"}, -- Tell me about the Tatooine jokes.
		{"@celebrity/lok_engineer:i_will_help", "good_luck"}, -- I'll deal with them.
	}
}
chosterConvoTemplate:addScreen(which_defense);

good_luck = ConvoScreen:new {
	id = "good_luck",
	leftDialog = "@celebrity/lok_engineer:good_luck", -- Well, take care. If you need to ask me about the defenses again, I'll be here. I hope you give those pirates what they deserve.
	stopConversation = "true",
	options = {
	}
}
chosterConvoTemplate:addScreen(good_luck);

pirate_artist = ConvoScreen:new {
	id = "pirate_artist",
	leftDialog = "@celebrity/lok_engineer:pirate_artist", -- In my youth, I tried to make my fortune by forging famous holopaintings. I wasn't very successful, but I did learn basic facts about the "color wheel." The color spectrum includes both primary and secondary colors, and there are opposing colors on the color wheel. Red is the opposite of green, for example. The security system's AI seemed fascinated with the color wheel, so you might do a little research on that.
	stopConversation = "false",
	options = {
		{"@celebrity/lok_engineer:math_defense", "sequential_numbers"}, -- Tell me about the math problems.
		{"@celebrity/lok_engineer:other_defense", "pirate_joker"}, -- Tell me about the Tatooine jokes.
		{"@celebrity/lok_engineer:i_will_help", "good_luck"}, -- I'll deal with them.
	}
}
chosterConvoTemplate:addScreen(pirate_artist);

sequential_numbers = ConvoScreen:new {
	id = "sequential_numbers",
	leftDialog = "@celebrity/lok_engineer:sequential_numbers", -- Well, at the time I was very intrigued by sequential numbers. If you're presented with a string of numbers, like 1, 3, 5, and 7, what comes next?  Nine of course.  That's just a simple odd number sequence.  The sequence the AI uses might be a bit harder, but it could also be as easy as 1-2-3.
	stopConversation = "false",
	options = {
		{"@celebrity/lok_engineer:color_defense", "pirate_artist"}, -- Tell me about the color spectrum.
		{"@celebrity/lok_engineer:other_defense", "pirate_joker"}, -- Tell me about the Tatooine jokes.
		{"@celebrity/lok_engineer:i_will_help", "good_luck"}, -- I'll deal with them.
	}
}
chosterConvoTemplate:addScreen(sequential_numbers);

pirate_joker = ConvoScreen:new {
	id = "pirate_joker",
	leftDialog = "@celebrity/lok_engineer:pirate_joker", -- A few years back, I was stranded on Tatooine. I was "befriended" by a Rodian drunk who liked to tell really terrible jokes. The jokes always involved Tatooine native species, like Jawas or dewbacks. The jokes were just awful... How do you get a one-armed Jawa out of a tree? Wave. I tried to purge the jokes from my brain by transferring them to the AI. If the system asks you a joke, just pick the most obvious punch line.
	stopConversation = "false",
	options = {
		{"@celebrity/lok_engineer:color_defense", "pirate_artist"}, -- Tell me about the color spectrum.
		{"@celebrity/lok_engineer:math_defense", "sequential_numbers"}, -- Tell me about the math problems.
		{"@celebrity/lok_engineer:i_will_help", "good_luck"}, -- I'll deal with them.
	}
}
chosterConvoTemplate:addScreen(pirate_joker);

----------
--Choster return convo
----------
more_questions = ConvoScreen:new {
	id = "more_questions",
	leftDialog = "@celebrity/lok_engineer:more_questions", -- Did you want to ask me something else?
	stopConversation = "false",
	options = {
		{"@celebrity/lok_engineer:ask_about_defenses", "which_defense_2"}, -- I wanted to ask you about the security at the pirate base.
	}
}
chosterConvoTemplate:addScreen(more_questions);

which_defense_2 = ConvoScreen:new {
	id = "which_defense_2",
	leftDialog = "@celebrity/lok_engineer:which_defense_2", -- About the colors spectrum, the math problems, or the Tatooine jokes?
	stopConversation = "false",
	options = {
		{"@celebrity/lok_engineer:color_defense", "pirate_artist"}, -- Tell me about the color spectrum.
		{"@celebrity/lok_engineer:math_defense", "sequential_numbers"}, -- Tell me about the math problems.
		{"@celebrity/lok_engineer:other_defense", "pirate_joker"}, -- Tell me about the Tatooine jokes.
	}
}
chosterConvoTemplate:addScreen(which_defense_2);

addConversationTemplate("chosterConvoTemplate", chosterConvoTemplate);
