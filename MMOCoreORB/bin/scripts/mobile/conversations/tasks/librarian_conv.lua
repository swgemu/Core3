librarian_convotemplate = ConvoTemplate:new {
	initialScreen = "",
	templateType = "Lua",
	luaClassHandler = "librarian_handler",
	screens = {}
}

want_trivia = ConvoScreen:new {
	id = "want_trivia",
	leftDialog = "@celebrity/librarian:want_trivia",
	stopConversation = "false",
	options = {
		{"@celebrity/librarian:yes","question_1"},
		{"@celebrity/librarian:no","good_bye"}
	}
}

librarian_convotemplate:addScreen(want_trivia);

good_bye = ConvoScreen:new {
	id = "good_bye",
	leftDialog = "@celebrity/librarian:good_bye",
	stopConversation = "true",
	options = {
	}
}

librarian_convotemplate:addScreen(good_bye);

question_1 = ConvoScreen:new {
	id = "question_1",
	leftDialog = "@celebrity/librarian:question_1",
	stopConversation = "false",
	options = {
	}
}

librarian_convotemplate:addScreen(question_1);

question_2 = ConvoScreen:new {
	id = "question_2",
	leftDialog = "@celebrity/librarian:question_2",
	stopConversation = "false",
	options = {
	}
}

librarian_convotemplate:addScreen(question_2);

question_3 = ConvoScreen:new {
	id = "question_3",
	leftDialog = "@celebrity/librarian:question_3",
	stopConversation = "false",
	options = {
	}
}

librarian_convotemplate:addScreen(question_3);

question_4 = ConvoScreen:new {
	id = "question_4",
	leftDialog = "@celebrity/librarian:question_4",
	stopConversation = "false",
	options = {
	}
}

librarian_convotemplate:addScreen(question_4);

question_5 = ConvoScreen:new {
	id = "question_5",
	leftDialog = "@celebrity/librarian:question_5",
	stopConversation = "false",
	options = {
	}
}

librarian_convotemplate:addScreen(question_5);

question_6 = ConvoScreen:new {
	id = "question_6",
	leftDialog = "@celebrity/librarian:question_6",
	stopConversation = "false",
	options = {
	}
}

librarian_convotemplate:addScreen(question_6);

question_7 = ConvoScreen:new {
	id = "question_7",
	leftDialog = "@celebrity/librarian:question_7",
	stopConversation = "false",
	options = {
	}
}

librarian_convotemplate:addScreen(question_7);

question_8 = ConvoScreen:new {
	id = "question_8",
	leftDialog = "@celebrity/librarian:question_8",
	stopConversation = "false",
	options = {
	}
}

librarian_convotemplate:addScreen(question_8);

question_9 = ConvoScreen:new {
	id = "question_9",
	leftDialog = "@celebrity/librarian:question_9",
	stopConversation = "false",
	options = {
	}
}

librarian_convotemplate:addScreen(question_9);

question_10 = ConvoScreen:new {
	id = "question_10",
	leftDialog = "@celebrity/librarian:question_10",
	stopConversation = "false",
	options = {
	}
}

librarian_convotemplate:addScreen(question_10);

question_11 = ConvoScreen:new {
	id = "question_11",
	leftDialog = "@celebrity/librarian:question_11",
	stopConversation = "false",
	options = {
	}
}

librarian_convotemplate:addScreen(question_11);

question_12 = ConvoScreen:new {
	id = "question_12",
	leftDialog = "@celebrity/librarian:question_12",
	stopConversation = "false",
	options = {
	}
}

librarian_convotemplate:addScreen(question_12);

question_13 = ConvoScreen:new {
	id = "question_13",
	leftDialog = "@celebrity/librarian:question_13",
	stopConversation = "false",
	options = {
	}
}

librarian_convotemplate:addScreen(question_13);

question_14 = ConvoScreen:new {
	id = "question_14",
	leftDialog = "@celebrity/librarian:question_14",
	stopConversation = "false",
	options = {
	}
}

librarian_convotemplate:addScreen(question_14);

question_15 = ConvoScreen:new {
	id = "question_15",
	leftDialog = "@celebrity/librarian:question_15",
	stopConversation = "false",
	options = {
	}
}

librarian_convotemplate:addScreen(question_15);

question_16 = ConvoScreen:new {
	id = "question_16",
	leftDialog = "@celebrity/librarian:question_16",
	stopConversation = "false",
	options = {
	}
}

librarian_convotemplate:addScreen(question_16);

question_17 = ConvoScreen:new {
	id = "question_17",
	leftDialog = "@celebrity/librarian:question_17",
	stopConversation = "false",
	options = {
	}
}

librarian_convotemplate:addScreen(question_17);

question_18 = ConvoScreen:new {
	id = "question_18",
	leftDialog = "@celebrity/librarian:question_18",
	stopConversation = "false",
	options = {
	}
}

librarian_convotemplate:addScreen(question_18);

question_19 = ConvoScreen:new {
	id = "question_19",
	leftDialog = "@celebrity/librarian:question_19",
	stopConversation = "false",
	options = {
	}
}

librarian_convotemplate:addScreen(question_19);


question_20 = ConvoScreen:new {
	id = "question_20",
	leftDialog = "@celebrity/librarian:question_20",
	stopConversation = "false",
	options = {
	}
}

librarian_convotemplate:addScreen(question_20);

winner_is_you = ConvoScreen:new {
	id = "winner_is_you",
	leftDialog = "@celebrity/librarian:winner_is_you",
	stopConversation = "false",
	options = {
	}
}

librarian_convotemplate:addScreen(winner_is_you);

too_bad_so_sad = ConvoScreen:new {
	id = "too_bad_so_sad",
	leftDialog = "@celebrity/librarian:too_bad_so_sad",
	stopConversation = "false",
	options = {
	}
}

librarian_convotemplate:addScreen(too_bad_so_sad);

worst_ever_guesser = ConvoScreen:new {
	id = "worst_ever_guesser",
	leftDialog = "@celebrity/librarian:worst_ever_guesser",
	stopConversation = "false",
	options = {
	}
}

librarian_convotemplate:addScreen(worst_ever_guesser);

you_are_right = ConvoScreen:new {
	id = "you_are_right",
	leftDialog = "@celebrity/librarian:you_are_right",
	stopConversation = "false",
	options = {
	}
}

librarian_convotemplate:addScreen(you_are_right);

good_answer = ConvoScreen:new {
	id = "good_answer",
	leftDialog = "@celebrity/librarian:good_answer",
	stopConversation = "false",
	options = {
	}
}

librarian_convotemplate:addScreen(good_answer);

correct = ConvoScreen:new {
	id = "correct",
	leftDialog = "@celebrity/librarian:correct",
	stopConversation = "false",
	options = {
	}
}

librarian_convotemplate:addScreen(correct);

correctamundo = ConvoScreen:new {
	id = "correctamundo",
	leftDialog = "@celebrity/librarian:correctamundo",
	stopConversation = "false",
	options = {
	}
}

librarian_convotemplate:addScreen(correctamundo);

you_got_it = ConvoScreen:new {
	id = "you_got_it",
	leftDialog = "@celebrity/librarian:you_got_it",
	stopConversation = "false",
	options = {
	}
}

librarian_convotemplate:addScreen(you_got_it);

thats_not_it = ConvoScreen:new {
	id = "thats_not_it",
	leftDialog = "@celebrity/librarian:thats_not_it",
	stopConversation = "false",
	options = {
	}
}

librarian_convotemplate:addScreen(thats_not_it);

no_sir = ConvoScreen:new {
	id = "no_sir",
	leftDialog = "@celebrity/librarian:no_sir",
	stopConversation = "false",
	options = {
	}
}

librarian_convotemplate:addScreen(no_sir);

you_are_wrong = ConvoScreen:new {
	id = "you_are_wrong",
	leftDialog = "@celebrity/librarian:you_are_wrong",
	stopConversation = "false",
	options = {
	}
}

librarian_convotemplate:addScreen(you_are_wrong);

incorrect = ConvoScreen:new {
	id = "incorrect",
	leftDialog = "@celebrity/librarian:incorrect",
	stopConversation = "false",
	options = {
	}
}

librarian_convotemplate:addScreen(incorrect);

buzz_wrong_answer = ConvoScreen:new {
	id = "buzz_wrong_answer",
	leftDialog = "@celebrity/librarian:buzz_wrong_answer",
	stopConversation = "false",
	options = {
	}
}

librarian_convotemplate:addScreen(buzz_wrong_answer);

couldnt_be_wronger = ConvoScreen:new {
	id = "couldnt_be_wronger",
	leftDialog = "@celebrity/librarian:couldnt_be_wronger",
	stopConversation = "false",
	options = {
	}
}

librarian_convotemplate:addScreen(couldnt_be_wronger);

most_wrong = ConvoScreen:new {
	id = "most_wrong",
	leftDialog = "@celebrity/librarian:most_wrong",
	stopConversation = "false",
	options = {
	}
}

librarian_convotemplate:addScreen(most_wrong);

bad_answer = ConvoScreen:new {
	id = "bad_answer",
	leftDialog = "@celebrity/librarian:bad_answer",
	stopConversation = "false",
	options = {
	}
}

librarian_convotemplate:addScreen(bad_answer);

most_unfortunate = ConvoScreen:new {
	id = "most_unfortunate",
	leftDialog = "@celebrity/librarian:most_unfortunate",
	stopConversation = "false",
	options = {
	}
}

librarian_convotemplate:addScreen(most_unfortunate);

most_incorrect = ConvoScreen:new {
	id = "most_incorrect",
	leftDialog = "@celebrity/librarian:most_incorrect",
	stopConversation = "false",
	options = {
	}
}

librarian_convotemplate:addScreen(most_incorrect);

worst_answer_ever = ConvoScreen:new {
	id = "worst_answer_ever",
	leftDialog = "@celebrity/librarian:worst_answer_ever",
	stopConversation = "false",
	options = {
	}
}

librarian_convotemplate:addScreen(worst_answer_ever);

wrongest = ConvoScreen:new {
	id = "wrongest",
	leftDialog = "@celebrity/librarian:wrongest",
	stopConversation = "false",
	options = {
	}
}

librarian_convotemplate:addScreen(wrongest);

wrong_squared = ConvoScreen:new {
	id = "wrong_squared",
	leftDialog = "@celebrity/librarian:wrong_squared",
	stopConversation = "false",
	options = {
	}
}

librarian_convotemplate:addScreen(wrong_squared);

you_are_weakest_link = ConvoScreen:new {
	id = "you_are_weakest_link",
	leftDialog = "@celebrity/librarian:you_are_weakest_link",
	stopConversation = "false",
	options = {
	}
}

librarian_convotemplate:addScreen(you_are_weakest_link);

not_even_trying = ConvoScreen:new {
	id = "not_even_trying",
	leftDialog = "@celebrity/librarian:not_even_trying",
	stopConversation = "false",
	options = {
	}
}

librarian_convotemplate:addScreen(not_even_trying);

done = ConvoScreen:new {
	id = "done",
	leftDialog = "@celebrity/librarian:done",
	stopConversation = "false",
	options = {
		{"@celebrity/librarian:thanks","answered_all"}
	}
}

librarian_convotemplate:addScreen(done);

answered_all = ConvoScreen:new {
	id = "answered_all",
	leftDialog = "@celebrity/librarian:answered_all",
	stopConversation = "true",
	options = {
	}
}

librarian_convotemplate:addScreen(answered_all);

addConversationTemplate("librarian_convotemplate", librarian_convotemplate);
