beremaConvoTemplate = ConvoTemplate:new {
	initialScreen = "",
	templateType = "Lua",
	luaClassHandler = "theme_park_nym_conv_handler",
	screens = {}
}

----------
--Only if player is on nym quest
----------
nym_sent_you = ConvoScreen:new {
	id = "nym_sent_you",
	leftDialog = "@celebrity/lok_gambler:nym_sent_you", -- I've been expecting you. Nym was supposed to send someone to meet me days ago. But, before I give you any information, let's play a game.
	stopConversation = "false",
	options = {
		{"@celebrity/lok_gambler:tell_me_something", "games_first"}, -- What can you tell me right now?
		{"@celebrity/lok_gambler:talk_nym", "nym_rules"}, -- Tell me about Nym.
		{"@celebrity/lok_gambler:what_game", "explain_game"}, -- Tell me about the game.
	}
}
beremaConvoTemplate:addScreen(nym_sent_you);

games_first = ConvoScreen:new {
	id = "games_first",
	leftDialog = "@celebrity/lok_gambler:games_first", -- I won't say anything until we've played some cards.  You ready?
	stopConversation = "false",
	options = {
		{"@celebrity/lok_gambler:what_game", "explain_game"}, -- Tell me about the game.
	}
}
beremaConvoTemplate:addScreen(games_first);

nym_rules = ConvoScreen:new {
	id = "nym_rules",
	leftDialog = "@celebrity/lok_gambler:nym_rules", -- I like Nym. He's helped me out of a few scrapes over the years. He even bought up all my markers in the galaxy. Now, I'm in his pocket, but it's better than being dead.
	stopConversation = "false",
	options = {
		{"@celebrity/lok_gambler:what_game", "explain_game"}, -- Tell me about the game.
	}
}
beremaConvoTemplate:addScreen(nym_rules);

begin_game_five_wins = ConvoScreen:new {
	id = "begin_game_five_wins",
	leftDialog = "@celebrity/lok_gambler:begin_game_five_wins", -- Well, you're pretty good. I'll play another hand if you want, or you can ask me some questions...
	stopConversation = "false",
	options = {
		{"@celebrity/lok_gambler:tell_me_more", "lab_info"}, -- Tell me about the Imperial Lab.
		{"@celebrity/lok_gambler:play_again", "bet_how_much"} -- Let's play again.
	}
}
beremaConvoTemplate:addScreen(begin_game_five_wins);

lab_info = ConvoScreen:new {
	id = "lab_info",
	leftDialog = "@celebrity/lok_gambler:lab_info", -- The lab, eh? Yeah, I know about it. It's pretty well-guarded. Rather than rely on General Otto and his goons, the Imperials in charge of the lab hired mercenaries to protect it. They're all blood thirsty and will shoot on sight. The scientists shouldn't give you too much trouble, but there might be other dangers...
	stopConversation = "false",
	options = {
		{"@celebrity/lok_gambler:other_dangers", "other_dangers_info"}, -- What other dangers?
		{"@celebrity/lok_gambler:hard_drive_where", "hard_drive_loc"}, -- Where's the memory module?
		{"@celebrity/lok_gambler:imggcu_where", "imggcu_loc"}, -- Where are the IMGGCUs?
		{"@celebrity/lok_gambler:leaving", "good_luck"} -- I'll be going now.
	}
}
beremaConvoTemplate:addScreen(lab_info);

other_dangers_info = ConvoScreen:new {
	id = "other_dangers_info",
	leftDialog = "@celebrity/lok_gambler:other_dangers_info", -- Well, I hear they're doing some other, illegal experiments in that base. Creating monsters that will rip your arms off and beat you to death with them. Or so the rumors go.
	stopConversation = "false",
	options = {
		{"@celebrity/lok_gambler:hard_drive_where", "hard_drive_loc"}, -- Where's the memory module?
		{"@celebrity/lok_gambler:imggcu_where", "imggcu_loc"}, -- Where are the IMGGCUs?
		{"@celebrity/lok_gambler:leaving", "good_luck"} -- I'll be going now.
	}
}
beremaConvoTemplate:addScreen(other_dangers_info);

hard_drive_loc = ConvoScreen:new {
	id = "hard_drive_loc",
	leftDialog = "@celebrity/lok_gambler:hard_drive_loc", -- Well, once you get inside, you'll find four corridors leading from the central room. The computer room is to the west, I think. Somewhere in there you'll find your memory module.
	stopConversation = "false",
	options = {
		{"@celebrity/lok_gambler:other_dangers", "other_dangers_info"}, -- What other dangers?
		{"@celebrity/lok_gambler:imggcu_where", "imggcu_loc"}, -- Where are the IMGGCUs?
		{"@celebrity/lok_gambler:leaving", "good_luck"} -- I'll be going now.
	}
}
beremaConvoTemplate:addScreen(hard_drive_loc);

imggcu_loc = ConvoScreen:new {
	id = "imggcu_loc",
	leftDialog = "@celebrity/lok_gambler:imggcu_loc", -- Heh, you know about those, eh? Unfortunately, I don't know where they store 'em. But, if the Imperials are getting ready to ship the IMGGCUs off of Lok, the explosives are probably stored in a locker or crate, awaiting transport. You'll have to look around a bit, I'm sure.
	stopConversation = "false",
	options = {
		{"@celebrity/lok_gambler:other_dangers", "other_dangers_info"}, -- What other dangers?
		{"@celebrity/lok_gambler:hard_drive_where", "hard_drive_loc"}, -- Where's the memory module?
		{"@celebrity/lok_gambler:leaving", "good_luck"} -- I'll be going now.
	}
}
beremaConvoTemplate:addScreen(imggcu_loc);

----------
-- Base gambling game convo
----------

explain_game = ConvoScreen:new {
	id = "explain_game",
	leftDialog = "@celebrity/lok_gambler:explain_game", -- We'll play Desert Draw. The game is simple. Just six cards. I pick one of mine and hold it behind my back, then you pick one of yours and then we compare them to see who wins. Simple, eh?
	stopConversation = "false",
	options = {
		{"@celebrity/lok_gambler:game_rules", "explain_rules"}, -- How do we know who wins?
		{"@celebrity/lok_gambler:sure_lets_play", "bet_how_much"} -- Ok, I'm game.  Let's do it.
	}
}
beremaConvoTemplate:addScreen(explain_game);

explain_rules = ConvoScreen:new {
	id = "explain_rules",
	leftDialog = "@celebrity/lok_gambler:explain_rules", -- We each have three cards. A Bounty Hunter, the Sarlacc, and a Thermal Detonator.  I pick one, you pick one, then we compare.  Bounty Hunter beats a Thermal Detonator. Thermal Detonator beats a Sarlacc, and Sarlacc beats the Bounty Hunter. It's really just that simple. Wanna try a hand?
	stopConversation = "false",
	options = {
		{"@celebrity/lok_gambler:sure_lets_play", "bet_how_much"} -- Ok, I'm game.  Let's do it.
	}
}
beremaConvoTemplate:addScreen(explain_rules);

begin_game = ConvoScreen:new {
	id = "begin_game",
	leftDialog = "@celebrity/lok_gambler:begin_game", -- Ok, I've picked my card.  Which one are you going to go with?
	stopConversation = "false",
	options = {
	-- Handled in screen handler
	}
}
beremaConvoTemplate:addScreen(begin_game);

begin_game_5 = ConvoScreen:new {
	id = "begin_game_5",
	leftDialog = "@celebrity/lok_gambler:begin_game", -- Ok, I've picked my card.  Which one are you going to go with?
	stopConversation = "false",
	options = {
	-- Handled in screen handler
	}
}
beremaConvoTemplate:addScreen(begin_game_5);

begin_game_10 = ConvoScreen:new {
	id = "begin_game_10",
	leftDialog = "@celebrity/lok_gambler:begin_game", -- Ok, I've picked my card.  Which one are you going to go with?
	stopConversation = "false",
	options = {
	-- Handled in screen handler
	}
}
beremaConvoTemplate:addScreen(begin_game_10);

begin_game_50 = ConvoScreen:new {
	id = "begin_game_50",
	leftDialog = "@celebrity/lok_gambler:begin_game", -- Ok, I've picked my card.  Which one are you going to go with?
	stopConversation = "false",
	options = {
	-- Handled in screen handler
	}
}
beremaConvoTemplate:addScreen(begin_game_50);



game_description = ConvoScreen:new {
	id = "game_description",
	leftDialog = "@celebrity/lok_gambler:game_description", -- It's called Desert Draw.  It's really simple.  We each have three cards, we both pick a card and show them at the same time. The winner gets the credits.
	stopConversation = "false",
	options = {
		{"@celebrity/lok_gambler:sure_lets_play", "bet_how_much"} -- Ok, I'm game.  Let's do it.
	}
}
beremaConvoTemplate:addScreen(game_description);

you_win_td = ConvoScreen:new {
	id = "you_win_td",
	leftDialog = "@celebrity/lok_gambler:you_win_td", -- Your Thermal Detonator blows up my Sarlacc.  You win.
	stopConversation = "false",
	options = {
	-- Handled in screen handler
	}
}
beremaConvoTemplate:addScreen(you_win_td);

you_lose_td = ConvoScreen:new {
	id = "you_lose_td",
	leftDialog = "@celebrity/lok_gambler:you_lose_td", -- My Bounty Hunter disarms the Thermal Detonator.  You lose!
	stopConversation = "false",
	options = {
	-- Handled in screen handler
	}
}
beremaConvoTemplate:addScreen(you_lose_td);

you_win_bh = ConvoScreen:new {
	id = "you_win_bh",
	leftDialog = "@celebrity/lok_gambler:you_win_bh", -- Your Bounty Hunter disarms my Thermal Detonator.  Stang!
	stopConversation = "false",
	options = {
	-- Handled in screen handler
	}
}
beremaConvoTemplate:addScreen(you_win_bh);

you_lose_bh = ConvoScreen:new {
	id = "you_lose_bh",
	leftDialog = "@celebrity/lok_gambler:you_lose_bh", -- My Sarlacc eats your Bounty Hunter!  You lose.
	stopConversation = "false",
	options = {
	-- Handled in screen handler
	}
}
beremaConvoTemplate:addScreen(you_lose_bh);

you_win_s = ConvoScreen:new {
	id = "you_win_s",
	leftDialog = "@celebrity/lok_gambler:you_win_s", -- Stang! Your Sarlacc swallows my Bounty Hunter.  You win.
	stopConversation = "false",
	options = {
	-- Handled in screen handler
	}
}
beremaConvoTemplate:addScreen(you_win_s);

you_lose_s = ConvoScreen:new {
	id = "you_lose_s",
	leftDialog = "@celebrity/lok_gambler:you_lose_s", -- My Thermal Detonator blows up your Sarlacc!  I win!  You lose.
	stopConversation = "false",
	options = {
	-- Handled in screen handler
	}
}
beremaConvoTemplate:addScreen(you_lose_s);

tie = ConvoScreen:new {
	id = "tie",
	leftDialog = "@celebrity/lok_gambler:tie", -- We both picked the same card. It's a tie.
	stopConversation = "false",
	options = {
	-- Handled in screen handler
	}
}
beremaConvoTemplate:addScreen(tie);

play_game = ConvoScreen:new {
	id = "play_game",
	leftDialog = "@celebrity/lok_gambler:play_game", -- Interested in wagering a little cash?  Maybe making some money?  I have a game that's perfect. Wanna hear about it?
	stopConversation = "false",
	options = {
		{"@celebrity/lok_gambler:what_game", "game_description"} -- Tell me about the game.
	}
}
beremaConvoTemplate:addScreen(play_game);

bet_how_much = ConvoScreen:new {
	id = "bet_how_much",
	leftDialog = "@celebrity/lok_gambler:bet_how_much", -- How much you wanna bet?  Can't play without credits you know.
	stopConversation = "false",
	options = {
	-- Handled in screen handler
	}
}
beremaConvoTemplate:addScreen(bet_how_much);

good_luck = ConvoScreen:new {
	id = "good_luck",
	leftDialog = "@celebrity/lok_gambler:good_luck", -- Good luck.
	stopConversation = "true",
	options = {
	}
}
beremaConvoTemplate:addScreen(good_luck);

addConversationTemplate("beremaConvoTemplate", beremaConvoTemplate);
