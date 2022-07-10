gerakVurtimisConvoTemplate = ConvoTemplate:new {
	initialScreen = "init",
	templateType = "Lua",
	luaClassHandler = "GerakVurtimisConvoHandler",
	screens = {}
}

init = ConvoScreen:new {
	id = "init",
	leftDialog = "@conversation/lf_safetyquestgiver:s_109", -- I cannot believe how blasted nasty this place has become!
	stopConversation = "false",
	options = {
		{"@conversation/lf_safetyquestgiver:s_111", "meaning1"}, -- What do you mean?
		{"@conversation/lf_safetyquestgiver:s_123", "explanation"}, -- It isn't that bad!  I think the city is quite clean.
		{"@conversation/lf_safetyquestgiver:s_138", "mock"}, -- Nasty?  Only if you are too weak to protect yourself.
	}
}
gerakVurtimisConvoTemplate:addScreen(init);

meaning1 = ConvoScreen:new {
	id = "meaning1",
	leftDialog = "@conversation/lf_safetyquestgiver:s_113", -- You haven't noticed all the creatures and bandits swarming around outside of town?  It's so bad that you can't travel without a shuttle or a blaster rifle.  And my son has neither and is coming to visit soon.  I'm afraid for him.
	stopConversation = "false",
	options = {
		{"@conversation/lf_safetyquestgiver:s_115", "give_quest1_2"}, -- I'd be happy to clear the way.
		{"@conversation/lf_safetyquestgiver:s_119", "not_interested"}, -- I'm not interested
	}
}
gerakVurtimisConvoTemplate:addScreen(meaning1);

explanation = ConvoScreen:new {
	id = "explanation",
	leftDialog = "@conversation/lf_safetyquestgiver:s_125", -- No no, not the city.  I'm talking about the wilderness.  If you live in a major city it's all right.  But if there's no shuttle port, traveling here is just dangerous.   And my son has neither and is coming to visit soon.  I'm afraid for him
	stopConversation = "false",
	options = {
		{"@conversation/lf_safetyquestgiver:s_127", "give_quest1_1"}, -- I'd be happy to help you make the area safer.
		{"@conversation/lf_safetyquestgiver:s_131", "not_interested"}, -- I'm not interested.
	}
}
gerakVurtimisConvoTemplate:addScreen(explanation);

mock = ConvoScreen:new {
	id = "mock",
	leftDialog = "@conversation/lf_safetyquestgiver:s_142", -- You think so?  If you are so tough, I have a job for you then.  I want some of the dangerous creatures cleared out.  You strong enough for that?
	stopConversation = "false",
	options = {
		{"@conversation/lf_safetyquestgiver:s_146", "give_quest1_1"}, -- Why not?  I could use the credits.
		{"@conversation/lf_safetyquestgiver:s_154", "not_tough"}, -- Nah.  Sounds too boring.
	}
}
gerakVurtimisConvoTemplate:addScreen(mock);

not_interested = ConvoScreen:new {
	id = "not_interested",
	leftDialog = "@conversation/lf_safetyquestgiver:s_121", -- I wish you would reconsider.  If you do, come back and talk to me.
	stopConversation = "true",
	options = {}
}
gerakVurtimisConvoTemplate:addScreen(not_interested);

not_tough = ConvoScreen:new {
	id = "not_tough",
	leftDialog = "@conversation/lf_safetyquestgiver:s_158", -- Guess you aren't as tough as you say you are.  If you change your mind, I'll be here.
	stopConversation = "true",
	options = {}
}
gerakVurtimisConvoTemplate:addScreen(not_tough);

give_quest1_1 = ConvoScreen:new {
	id = "give_quest1_1",
	leftDialog = "@conversation/lf_safetyquestgiver:s_129", -- Great!  First thing, I need you to go thin out the worrt population.  Come back when you are done.
	stopConversation = "true",
	options = {}
}
gerakVurtimisConvoTemplate:addScreen(give_quest1_1);

give_quest1_2 = ConvoScreen:new {
	id = "give_quest1_2",
	leftDialog = "@conversation/lf_safetyquestgiver:s_129", -- Thank you!  First thing, I need you to go thin out the worrt population.  Come back when you are done.
	stopConversation = "true",
	options = {}
}
gerakVurtimisConvoTemplate:addScreen(give_quest1_2);

-- Has quest 1

quest1_status = ConvoScreen:new {
	id = "quest1_status",
	leftDialog = "@conversation/lf_safetyquestgiver:s_162", -- How are you doing with the worrts?
	stopConversation = "false",
	options = {
		{"@conversation/lf_safetyquestgiver:s_174", "not_finished1"}, -- I'm not finished yet.
	}
}
gerakVurtimisConvoTemplate:addScreen(quest1_status);

not_finished1 = ConvoScreen:new {
	id = "not_finished1",
	leftDialog = "@conversation/lf_safetyquestgiver:s_178", --  Well, I believe in you.  You can do it!
	stopConversation = "true",
	options = {}
}
gerakVurtimisConvoTemplate:addScreen(not_finished1);

turn_in1 = ConvoScreen:new {
	id = "turn_in1",
	leftDialog = "@conversation/lf_safetyquestgiver:s_170", -- Excellent!  Thanks for taking care of that.  I transferred some credits into your bank account.  Come back and talk to me when you are ready for another job.
	stopConversation = "true",
	options = {}
}
gerakVurtimisConvoTemplate:addScreen(turn_in1);

-- Quest 1 is complete

prompt_quest2 = ConvoScreen:new {
	id = "prompt_quest2",
	leftDialog = "@conversation/lf_safetyquestgiver:s_182", -- Welcome back.  I have another assignment if you are willing.
	stopConversation = "false",
	options = {
		{"@conversation/lf_safetyquestgiver:s_186", "give_quest2"}, -- Sure.  I'm always ready for a good fight.
		{"@conversation/lf_safetyquestgiver:s_194", "too_busy"}, -- Sorry, I'm too busy right now.
	}
}
gerakVurtimisConvoTemplate:addScreen(prompt_quest2);

too_busy = ConvoScreen:new {
	id = "too_busy",
	leftDialog = "@conversation/lf_safetyquestgiver:s_198", -- Fine.  Come back when you have more free time.
	stopConversation = "true",
	options = {}
}
gerakVurtimisConvoTemplate:addScreen(too_busy);

give_quest2 = ConvoScreen:new {
	id = "give_quest2",
	leftDialog = "@conversation/lf_safetyquestgiver:s_190", -- There's an infestation of rills.  Please go kill 10 of them.
	stopConversation = "true",
	options = {}
}
gerakVurtimisConvoTemplate:addScreen(give_quest2);

-- Has quest 2

quest2_status = ConvoScreen:new {
	id = "quest2_status",
	leftDialog = "@conversation/lf_safetyquestgiver:s_202", -- How are you doing with the rills?
	stopConversation = "false",
	options = {
		{"@conversation/lf_safetyquestgiver:s_206", "not_finished2"}, -- I'm not quite done yet.
	}
}
gerakVurtimisConvoTemplate:addScreen(quest2_status);

not_finished2 = ConvoScreen:new {
	id = "not_finished2",
	leftDialog = "@conversation/lf_safetyquestgiver:s_210", --  Come back to me when you finish.
	stopConversation = "true",
	options = {}
}
gerakVurtimisConvoTemplate:addScreen(not_finished2);

turn_in2 = ConvoScreen:new {
	id = "turn_in2",
	leftDialog = "@conversation/lf_safetyquestgiver:s_170", -- Excellent!  Thanks for taking care of that.  I transferred some credits into your bank account.  Come back and talk to me when you are ready for another job.
	stopConversation = "true",
	options = {}
}
gerakVurtimisConvoTemplate:addScreen(turn_in2);

-- Quest 2 is complete

prompt_quest3 = ConvoScreen:new {
	id = "prompt_quest3",
	leftDialog = "@conversation/lf_safetyquestgiver:s_222", -- Hello again!  Now that I know that you are an accomplished hunter, I can tell you about something that is far more serious and dangerous than the pests near the city.
	stopConversation = "false",
	options = {
		{"@conversation/lf_safetyquestgiver:s_226", "meaning3"}, -- What do you mean?
		{"@conversation/lf_safetyquestgiver:s_265", "meaning3"}, -- Good.  I want to go after tougher prey.  Tell me more.
	}
}
gerakVurtimisConvoTemplate:addScreen(prompt_quest3);

meaning3 = ConvoScreen:new {
	id = "meaning3",
	leftDialog = "@conversation/lf_safetyquestgiver:s_230", -- About a week ago, a particularly nasty gang of thugs ambushed a caravan of people who were moving to the city.  There were... no survivors.
	stopConversation = "false",
	options = {
		{"@conversation/lf_safetyquestgiver:s_233", "terrible"}, -- That's terrible!
		{"@conversation/lf_safetyquestgiver:s_249", "effect_me"}, -- And how does this affect me?
	}
}
gerakVurtimisConvoTemplate:addScreen(meaning3);

terrible = ConvoScreen:new {
	id = "terrible",
	leftDialog = "@conversation/lf_safetyquestgiver:s_236", -- Yes.  While I know that getting the families' lost possessions back will not make up for the loss of their loved ones, at least it will help with their debts, and maybe give them something to remember their children by.
	stopConversation = "false",
	options = {
		{"@conversation/lf_safetyquestgiver:s_238", "give_quest3"}, -- I will get the possessions back, if you want me to
		{"@conversation/lf_safetyquestgiver:s_244", "not_dealing"}, -- I'd rather not deal with this.
	}
}
gerakVurtimisConvoTemplate:addScreen(terrible);

effect_me = ConvoScreen:new {
	id = "effect_me",
	leftDialog = "@conversation/lf_safetyquestgiver:s_252", -- I want you to go after these bandits and get back what they stole.
	stopConversation = "false",
	options = {
		{"@conversation/lf_safetyquestgiver:s_254", "give_quest3"}, -- Sure.  A little revenge is great with caf in the morning.
		{"@conversation/lf_safetyquestgiver:s_260", "not_dealing"}, -- Not now.  I'm tired.  I'll go after them tomorrow.
	}
}
gerakVurtimisConvoTemplate:addScreen(effect_me);

not_dealing = ConvoScreen:new {
	id = "not_dealing",
	leftDialog = "@conversation/lf_safetyquestgiver:s_246", -- I thought better of you. But when you are done being afraid, come back to me..
	stopConversation = "true",
	options = {}
}
gerakVurtimisConvoTemplate:addScreen(not_dealing);

give_quest3 = ConvoScreen:new {
	id = "give_quest3",
	leftDialog = "@conversation/lf_safetyquestgiver:s_257", -- Thank you.  I'll see you when you get back.
	stopConversation = "true",
	options = {}
}
gerakVurtimisConvoTemplate:addScreen(give_quest3);

quest3_status = ConvoScreen:new {
	id = "quest3_status",
	leftDialog = "@conversation/lf_safetyquestgiver:s_268", -- Have you found everything yet?
	stopConversation = "false",
	options = {
		{"@conversation/lf_safetyquestgiver:s_270", "transport"}, -- Not yet.
		{"@conversation/lf_safetyquestgiver:s_284", "new_loc3"}, -- Actually, I'm lost.  Can you give me that waypoint again?
	}
}
gerakVurtimisConvoTemplate:addScreen(quest3_status);

transport = ConvoScreen:new {
	id = "transport",
	leftDialog = "@conversation/lf_safetyquestgiver:s_273", -- Ok.  I'm clearing some space in my transport for when you are done.
	stopConversation = "true",
	options = {}
}
gerakVurtimisConvoTemplate:addScreen(transport);

new_loc3 = ConvoScreen:new {
	id = "new_loc3",
	leftDialog = "@conversation/lf_safetyquestgiver:s_288", -- Sure.  I'll copy that to you now.
	stopConversation = "true",
	options = {}
}
gerakVurtimisConvoTemplate:addScreen(new_loc3);

turn_in3 = ConvoScreen:new {
	id = "turn_in3",
	leftDialog = "@conversation/lf_safetyquestgiver:s_280", -- This will be such a great help to them.  Thank you very much.  You deserve more, but this is all that I have for now.
	stopConversation = "true",
	options = {}
}
gerakVurtimisConvoTemplate:addScreen(turn_in3);

-- Quest 3 is complete

prompt_quest4 = ConvoScreen:new {
	id = "prompt_quest4",
	leftDialog = "@conversation/lf_safetyquestgiver:s_292", -- Well, you seem to have stirred up a flewt nest!
	stopConversation = "false",
	options = {
		{"@conversation/lf_safetyquestgiver:s_296", "bandits"}, -- What do you mean?
		{"@conversation/lf_safetyquestgiver:s_320", "target"}, -- So?
	}
}
gerakVurtimisConvoTemplate:addScreen(prompt_quest4);

bandits = ConvoScreen:new {
	id = "bandits",
	leftDialog = "@conversation/lf_safetyquestgiver:s_300", -- It looks like those bandits didn't take too kindly to your attack.  I hear that they started reappearing en force.
	stopConversation = "false",
	options = {
		{"@conversation/lf_safetyquestgiver:s_304", "give_quest4"}, -- Hmm... guess I should encourage them to go back to hiding.
		{"@conversation/lf_safetyquestgiver:s_312", "no_concern"}, -- I don't really think I need to concern myself with them any more.
	}
}
gerakVurtimisConvoTemplate:addScreen(bandits);

target = ConvoScreen:new {
	id = "target",
	leftDialog = "@conversation/lf_safetyquestgiver:s_324", -- Looks like you are now one of the bandits' targets.  If you don't want to have to watch your back every second, you should probably go do something about them.
	stopConversation = "false",
	options = {
		{"@conversation/lf_safetyquestgiver:s_328", "give_quest4"}, -- I tend to watch my back anyway, but you're right.  I'll go take care of them.
		{"@conversation/lf_safetyquestgiver:s_336", "funeral"}, -- I have had enough of this.  I'm done!  No more brigands!
	}
}
gerakVurtimisConvoTemplate:addScreen(target);

give_quest4 = ConvoScreen:new {
	id = "give_quest4",
	leftDialog = "@conversation/lf_safetyquestgiver:s_308", -- I think that their leader is the one that you really want.  Unfortunately, the leaders tend to be hard to find.  I'll bet one of those guys out there has some information that will lead you to the leader.  When you find it come back to me.
	stopConversation = "true",
	options = {}
}
gerakVurtimisConvoTemplate:addScreen(give_quest4);

no_concern = ConvoScreen:new {
	id = "no_concern",
	leftDialog = "@conversation/lf_safetyquestgiver:s_316", -- If you are now one of their targets, I don't think they will leave you alone.  If you change your mind, come back to me.
	stopConversation = "true",
	options = {}
}
gerakVurtimisConvoTemplate:addScreen(no_concern);

funeral = ConvoScreen:new {
	id = "funeral",
	leftDialog = "@conversation/lf_safetyquestgiver:s_340", -- For some reason I don't think they will respect your wishes.  But if you want to ignore them, it's your funeral.  Come back if you change your mind.
	stopConversation = "true",
	options = {}
}
gerakVurtimisConvoTemplate:addScreen(funeral);

quest4_status = ConvoScreen:new {
	id = "quest4_status",
	leftDialog = "@conversation/lf_safetyquestgiver:s_342", -- How did it go?
	stopConversation = "false",
	options = {
		{"@conversation/lf_safetyquestgiver:s_344", "good_luck"}, -- I haven't found anything yet.
		{"@conversation/lf_safetyquestgiver:s_352", "new_loc4"}, -- I need the location again.
	}
}
gerakVurtimisConvoTemplate:addScreen(quest4_status);

good_luck = ConvoScreen:new {
	id = "good_luck",
	leftDialog = "@conversation/lf_safetyquestgiver:s_346", -- There has to be something.  Good luck!
	stopConversation = "true",
	options = {}
}
gerakVurtimisConvoTemplate:addScreen(good_luck);

new_loc4 = ConvoScreen:new {
	id = "new_loc4",
	leftDialog = "@conversation/lf_safetyquestgiver:s_354", -- All right.  I'm copying the data to you now.
	stopConversation = "true",
	options = {}
}
gerakVurtimisConvoTemplate:addScreen(new_loc4);

turn_in4 = ConvoScreen:new {
	id = "turn_in4",
	leftDialog = "@conversation/lf_safetyquestgiver:s_350", -- Great!  Let me take a look at it... give me a moment.
	stopConversation = "true",
	options = {}
}
gerakVurtimisConvoTemplate:addScreen(turn_in4);

-- Quest 4 Complete

prompt_quest5 = ConvoScreen:new {
	id = "prompt_quest5",
	leftDialog = "@conversation/lf_safetyquestgiver:s_356", -- Welcome back.  Ready to squish a bug?
	stopConversation = "false",
	options = {
		{"@conversation/lf_safetyquestgiver:s_358", "give_quest5_1"}, -- If you mean hunting down the brigand leader, then yes.
		{"@conversation/lf_safetyquestgiver:s_362", "give_quest5_2"}, -- Yep.  Less competition for me...I mean, yes, of course.
	}
}
gerakVurtimisConvoTemplate:addScreen(prompt_quest5);

give_quest5_1 = ConvoScreen:new {
	id = "give_quest5_1",
	leftDialog = "@conversation/lf_safetyquestgiver:s_360", -- That's exactly what I mean.  Here is the location of the camp.
	stopConversation = "true",
	options = {}
}
gerakVurtimisConvoTemplate:addScreen(give_quest5_1);

give_quest5_2 = ConvoScreen:new {
	id = "give_quest5_2",
	leftDialog = "@conversation/lf_safetyquestgiver:s_364", -- Hm...less competition?  Well, if you leave innocent travelers alone, that's your life.  I just want this thug eliminated.
	stopConversation = "true",
	options = {}
}
gerakVurtimisConvoTemplate:addScreen(give_quest5_2);

quest5_status = ConvoScreen:new {
	id = "quest5_status",
	leftDialog = "@conversation/lf_safetyquestgiver:s_366", -- I have been hearing rumors, but nothing confirmed.  How is it going?
	stopConversation = "false",
	options = {
		{"@conversation/lf_safetyquestgiver:s_388", "leader_alive"}, -- I haven't gotten to the leader yet.
		{"@conversation/lf_safetyquestgiver:s_392", "new_loc5"}, -- Actually, I need the location again.
	}
}
gerakVurtimisConvoTemplate:addScreen(quest5_status);

leader_alive = ConvoScreen:new {
	id = "leader_alive",
	leftDialog = "@conversation/lf_safetyquestgiver:s_390", -- I guess the rumors were optimistic.  No matter, come back when you are done.
	stopConversation = "true",
	options = {}
}
gerakVurtimisConvoTemplate:addScreen(leader_alive);

new_loc5 = ConvoScreen:new {
	id = "new_loc5",
	leftDialog = "@conversation/lf_safetyquestgiver:s_394", -- It's a good thing I keep copies!  Here you are.
	stopConversation = "true",
	options = {}
}
gerakVurtimisConvoTemplate:addScreen(new_loc5);

turn_in5_1 = ConvoScreen:new {
	id = "turn_in5_1",
	leftDialog = "@conversation/lf_safetyquestgiver:s_370", -- I'm glad the area is safe for travelers now.  Too many people died because of them.  Thank you from the bottom of my heart.  Take this.
	stopConversation = "true",
	options = {}
}
gerakVurtimisConvoTemplate:addScreen(turn_in5_1);

turn_in5_2 = ConvoScreen:new {
	id = "turn_in5_2",
	leftDialog = "@conversation/lf_safetyquestgiver:s_374", -- They did indeed, and I put my trust in the right one.  Too many good people died because of them.  Take this as thanks for the great service you did.
	stopConversation = "true",
	options = {}
}
gerakVurtimisConvoTemplate:addScreen(turn_in5_2);

turn_in5_3 = ConvoScreen:new {
	id = "turn_in5_3",
	leftDialog = "@conversation/lf_safetyquestgiver:s_378", -- Yes, well...I guess their leader was better at organizing than fighting.  Many good people died because of him.
	stopConversation = "true",
	options = {}
}
gerakVurtimisConvoTemplate:addScreen(turn_in5_3);

thank_you = ConvoScreen:new {
	id = "thank_you",
	leftDialog = "@conversation/lf_safetyquestgiver:s_396", -- Thanks again for all your help.
	stopConversation = "true",
	options = {}
}
gerakVurtimisConvoTemplate:addScreen(thank_you);


addConversationTemplate("gerakVurtimisConvoTemplate", gerakVurtimisConvoTemplate);