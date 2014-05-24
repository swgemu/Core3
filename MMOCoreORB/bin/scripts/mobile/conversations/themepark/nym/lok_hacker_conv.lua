lokHackerConvoTemplate = ConvoTemplate:new {
	initialScreen = "",
	templateType = "Lua",
	luaClassHandler = "theme_park_nym_conv_handler",
	screens = {}
}

----------
--Hacker return convo
----------
doors_open = ConvoScreen:new {
	id = "doors_open",
	leftDialog = "@celebrity/lok_hacker:doors_open", -- I've already sliced the doors open.  Don't you remember helping me?
	stopConversation = "false",
	options = {
		{"@celebrity/lok_hacker:right", "go_man_go"} -- Oh.  Right.
	}
}
lokHackerConvoTemplate:addScreen(doors_open);

go_man_go = ConvoScreen:new {
	id = "go_man_go",
	leftDialog = "@celebrity/lok_hacker:go_man_go", -- Well don't waste time!  Get in there!
	stopConversation = "true",
	options = {
	}
}
lokHackerConvoTemplate:addScreen(go_man_go);

----------
--Hacker main convo
----------

help_me_hack = ConvoScreen:new {
	id = "help_me_hack",
	leftDialog = "@celebrity/lok_hacker:help_me_hack", -- Aargh!  Can you help me with this thing?  I've found a back door to this security system, but the AI program keeps asking me these stupid questions! Can you lend me your brain?
	stopConversation = "false",
	options = {
		{"@celebrity/lok_hacker:what_are_you_doing", "hacking"}, -- What are you talking about?
		{"@celebrity/lok_hacker:who_are_you", "faulk"} -- Who are you?
	}
}
lokHackerConvoTemplate:addScreen(help_me_hack);

faulk = ConvoScreen:new {
	id = "faulk",
	leftDialog = "@celebrity/lok_hacker:faulk", -- My name is Faulk. I was hired by Borvo the Hutt on Naboo to gather information on the Sulfur Lake Pirates. He's convinced the pirates have hijacked some of his weapons shipments. I've been hiding out in this cave for weeks, waiting for a chance to slice into their network and grab all the data I can find. All this commotion has given me the opening I need, but I can't get past the final safeguards!
	stopConversation = "false",
	options = {
		{"@celebrity/lok_hacker:what_do_you_need", "cant_solve"} -- Tell me what you need.
	}
}
lokHackerConvoTemplate:addScreen(faulk);

hacking = ConvoScreen:new {
	id = "hacking",
	leftDialog = "@celebrity/lok_hacker:hacking", -- I'm trying to slice through the pirates' security system. The system itself is really basic, but the final safeguard includes three questions that I need to answer. The questions don't have anything to do with the pirates or computers. I'm totally lost.
	stopConversation = "false",
	options = {
		{"@celebrity/lok_hacker:what_do_you_need", "cant_solve"} -- Tell me what you need.
	}
}
lokHackerConvoTemplate:addScreen(hacking);

cant_solve = ConvoScreen:new {
	id = "cant_solve",
	leftDialog = "@celebrity/lok_hacker:cant_solve", -- I can't answer these riddles.  Who built this thing? Can you help me answer these questions?
	stopConversation = "false",
	options = {
		{"@celebrity/lok_hacker:helpful", "explain"}, -- Sure.  What are the questions?
		{"@celebrity/lok_hacker:going_away", "jerk"} -- You're too upset about this. I'm leaving.
	}
}
lokHackerConvoTemplate:addScreen(cant_solve);

jerk = ConvoScreen:new {
	id = "jerk",
	leftDialog = "@celebrity/lok_hacker:jerk", -- Fine!  Who needs ya?
	stopConversation = "true",
	options = {
	}
}
lokHackerConvoTemplate:addScreen(jerk);

explain = ConvoScreen:new {
	id = "explain",
	leftDialog = "@celebrity/lok_hacker:explain", -- Great. I need to reroute the access commands, reset the security network, and break the defender chip. But I have to answer one question before I can complete each task. I can give you the questions in any order.
	stopConversation = "false",
	options = {
		{"@celebrity/lok_hacker:codec", "color_codes"}, -- Let's do the network reset.
		{"@celebrity/lok_hacker:rewire", "math_problem"}, -- Let's reroute the access commands.
		{"@celebrity/lok_hacker:defender", "joke"}, -- Let's break the defender chip.
	}
}
lokHackerConvoTemplate:addScreen(explain);

color_codes = ConvoScreen:new {
	id = "color_codes",
	leftDialog = "@celebrity/lok_hacker:color_codes", -- It says, "On a color wheel, this color is the opposite of blue..."  What does that mean?  What's a color wheel?  And what's the opposite of blue?
	stopConversation = "false",
	options = {
		{"@celebrity/lok_hacker:purple", "wrong_color"}, -- I'm pretty sure it's purple.
		{"@celebrity/lok_hacker:brown", "wrong_color"}, -- It's brown!  Hah! I knew that one.
		{"@celebrity/lok_hacker:orange", "right_color"} -- It's orange. I'm sure of it.
	}
}
lokHackerConvoTemplate:addScreen(color_codes);

wrong_color = ConvoScreen:new {
	id = "wrong_color",
	leftDialog = "@celebrity/lok_hacker:wrong_color", -- It says, "On a color wheel, this color is the opposite of blue..."  What does that mean?  What's a color wheel?  And what's the opposite of blue?
	stopConversation = "false",
	options = {
		{"@celebrity/lok_hacker:purple", "wrong_color"}, -- I'm pretty sure it's purple.
		{"@celebrity/lok_hacker:brown", "wrong_color"}, -- It's brown!  Hah! I knew that one.
		{"@celebrity/lok_hacker:orange", "right_color"} -- It's orange. I'm sure of it.
	}
}
lokHackerConvoTemplate:addScreen(wrong_color);

right_color = ConvoScreen:new {
	id = "right_color",
	leftDialog = "@celebrity/lok_hacker:right_color", -- Great!  You must have studied art or something.  I'd have never gotten that.  Now what?
	stopConversation = "false",
	options = {
	}
}
lokHackerConvoTemplate:addScreen(right_color);

math_problem = ConvoScreen:new {
	id = "math_problem",
	leftDialog = "@celebrity/lok_hacker:math_problem", -- It says, "Finish this number pair sequence... 1-2, 3-6, 4-24, 5-120, 6-?
	stopConversation = "false",
	options = {
		{"@celebrity/lok_hacker:seven_twenty", "right_answer"}, -- It's multiplying. 720.
		{"@celebrity/lok_hacker:two_twenty", "wrong_answer"}, -- Uh...220.
		{"@celebrity/lok_hacker:nine", "wrong_answer"} -- It's nine.  I'm sure of it.
	}
}
lokHackerConvoTemplate:addScreen(math_problem);

wrong_answer = ConvoScreen:new {
	id = "wrong_answer",
	leftDialog = "@celebrity/lok_hacker:wrong_answer", -- I don't think so...
	stopConversation = "false",
	options = {
		{"@celebrity/lok_hacker:seven_twenty", "right_answer"}, -- It's multiplying. 720.
		{"@celebrity/lok_hacker:two_twenty", "wrong_answer"}, -- Uh...220.
		{"@celebrity/lok_hacker:nine", "wrong_answer"} -- It's nine.  I'm sure of it.
	}
}
lokHackerConvoTemplate:addScreen(wrong_answer);

right_answer = ConvoScreen:new {
	id = "right_answer",
	leftDialog = "@celebrity/lok_hacker:right_answer", -- I don't think so...
	stopConversation = "false",
	options = {
	}
}
lokHackerConvoTemplate:addScreen(right_answer);

joke = ConvoScreen:new {
	id = "joke",
	leftDialog = "@celebrity/lok_hacker:joke", -- What do you call a womprat that can lift a bantha?
	stopConversation = "false",
	options = {
		{"@celebrity/lok_hacker:wrong_joke", "not_funny"}, -- To get to the other side!
		{"@celebrity/lok_hacker:punchline", "right_joke"}, -- Sir!
		{"@celebrity/lok_hacker:bad_joke", "not_funny"} -- No such thing?
	}
}
lokHackerConvoTemplate:addScreen(joke);

not_funny = ConvoScreen:new {
	id = "not_funny",
	leftDialog = "@celebrity/lok_hacker:not_funny", -- That's not even funny!
	stopConversation = "false",
	options = {
		{"@celebrity/lok_hacker:wrong_joke", "not_funny"}, -- To get to the other side!
		{"@celebrity/lok_hacker:punchline", "right_joke"}, -- Sir!
		{"@celebrity/lok_hacker:bad_joke", "not_funny"} -- No such thing?
	}
}
lokHackerConvoTemplate:addScreen(not_funny);


right_joke = ConvoScreen:new {
	id = "right_joke",
	leftDialog = "@celebrity/lok_hacker:right_joke", -- Ugh...that's terrible.  What kind of...nevermind.  Let's do the next one.
	stopConversation = "false",
	options = {
	}
}
lokHackerConvoTemplate:addScreen(right_joke);

success = ConvoScreen:new {
	id = "success",
	leftDialog = "@celebrity/lok_hacker:success", -- That did it!  It's open!
	stopConversation = "true",
	options = {
	}
}
lokHackerConvoTemplate:addScreen(success);

addConversationTemplate("lokHackerConvoTemplate", lokHackerConvoTemplate);