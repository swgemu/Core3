hedon_istee_convotemplate = ConvoTemplate:new {
initialScreen = "",
templateType = "Lua",
luaClassHandler = "hedon_istee_handler",
screens = {}
}

--You've completed all quests
next_quest = ConvoScreen:new {
id = "next",
leftDialog = "@static_npc/tatooine/hedon_istee:next", --Thanks for all your help. Maybe I'll see you again one day.
stopConversation = "true",
options = {
}
}

hedon_istee_convotemplate:addScreen(next_quest);

--You are not qualified for this quest
notyet = ConvoScreen:new {
id = "notyet",
leftDialog = "@static_npc/tatooine/hedon_istee:notyet", --Greetings, I'm afraid you're not strong enough to help me yet.
stopConversation = "true",
options = {
}
}

hedon_istee_convotemplate:addScreen(notyet);

--You are already working
cantwork = ConvoScreen:new {
id = "cantwork",
leftDialog = "@static_npc/tatooine/hedon_istee:cantwork", --I'm afraid I'm a very demanding individual and therefore working for me would require your full attention. Do come back when you can offer me that. You won't be sorry you did.
stopConversation = "true",
options = {
}
}

hedon_istee_convotemplate:addScreen(cantwork);

---
--MISSION 1: Gamorrean
---
--Intro
npc_1_1 = ConvoScreen:new {
id = "npc_1_1",
leftDialog = "@static_npc/tatooine/hedon_istee:npc_1_1", --I'm a former initiate of the B'omarr Order that decided not to attempt "enlightenment." My former brothers, however, have different ideas. They've sent one of their bodyguards to either force me back "into the fold" or dispose of me. You look like you may be able to help someone in desperate need.
stopConversation = "false",
options = {
{"@static_npc/tatooine/hedon_istee:player_1_1", "npc_2_1"}, --Sounds horrible! I'll go and see if I can convince him otherwise.
{"@static_npc/tatooine/hedon_istee:player_2_1", "npc_3_1"}, --No.  I don't want to get involved.
{"@static_npc/tatooine/hedon_istee:player_3_1", "npc_4_1"}, --What's so bad about "enlightenment?"
}
}

hedon_istee_convotemplate:addScreen(npc_1_1);

--Accepted
npc_2_1 = ConvoScreen:new {
id = "npc_2_1",
leftDialog = "@static_npc/tatooine/hedon_istee:npc_2_1", --Splendid! I knew you'd appreciate my predicament - you seem a being who knows how to enjoy the finer things in life. The bodyguard is a Gamorrean named Drognuz. He may not understand any other language than violence.
stopConversation = "true",
options = {
}
}

hedon_istee_convotemplate:addScreen(npc_2_1);

--Declined
npc_3_1 = ConvoScreen:new {
id = "npc_3_1",
leftDialog = "@static_npc/tatooine/hedon_istee:npc_3_1", --Did I mention that I am a most generous being when it comes to rewarding those that save my life? You wouldn't want to miss out, would you? Please change your mind.
stopConversation = "true",
options = {
}
}

hedon_istee_convotemplate:addScreen(npc_3_1);


--More
npc_4_1 = ConvoScreen:new {
id = "npc_4_1",
leftDialog = "@static_npc/tatooine/hedon_istee:npc_4_1", --It involves surgically removing my brain from my body and placing it in a vat of nutrients. I like my brain where it is, thank you, and have decided that a vat of nutrients is not the finest accommodation the galaxy has to offer.
stopConversation = "true",
options = {
{"@static_npc/tatooine/hedon_istee:player_1_1", "npc_2_1"}, --Sounds horrible! I'll go and see if I can convince him otherwise.
{"@static_npc/tatooine/hedon_istee:player_2_1", "npc_3_1"} --No.  I don't want to get involved.
}
}

hedon_istee_convotemplate:addScreen(npc_4_1);

--Not finished
npc_work_1 = ConvoScreen:new {
id = "npc_work_1",
leftDialog = "@static_npc/tatooine/hedon_istee:npc_work_1", --Have you taken care of the Gamorrean yet?
stopConversation = "false",
options = {
{"@static_npc/tatooine/hedon_istee:player_sorry_1", "npc_backtowork_1"}, --Not yet.  But I am still working on this.
{"@static_npc/tatooine/hedon_istee:player_reset_1", "npc_reset_1"} --I've changed my mind.  This job doesn't interest me anymore.
}
}

hedon_istee_convotemplate:addScreen(npc_work_1);

--Not finished, continue
npc_backtowork_1 = ConvoScreen:new {
id = "npc_backtowork_1",
leftDialog = "@static_npc/tatooine/hedon_istee:npc_backtowork_1", --Hurry already!
stopConversation = "true",
options = {
}
}

hedon_istee_convotemplate:addScreen(npc_backtowork_1);

--Not finished, abandon
npc_reset_1 = ConvoScreen:new {
id = "npc_reset_1",
leftDialog = "@static_npc/tatooine/hedon_istee:npc_reset_1", --Did I mention that I am a most generous being when it comes to rewarding those that save my life? You wouldn't want to miss out, would you? Please change your mind.
stopConversation = "true",
options = {
}
}

hedon_istee_convotemplate:addScreen(npc_reset_1);

--Reward
npc_reward_1 = ConvoScreen:new {
id = "npc_reward_1",
leftDialog = "@static_npc/tatooine/hedon_istee:npc_reward_1", --Well handled, friend. I just hope that's the last I'll hear of those bizarre monks. I'm not sure why they're so interested in harming me when they're supposed to be pacifists. I suppose I have to give up some of my hard earned credits as thanks.
stopConversation = "true",
options = {
}
}

hedon_istee_convotemplate:addScreen(npc_reward_1);


---
--MISSION 2: Bounty Hunter
---
--Intro
npc_1_2 = ConvoScreen:new {
id = "npc_1_2",
leftDialog = "@static_npc/tatooine/hedon_istee:npc_1_2", --It seems the B'omarr have hired a bounty hunter to bring me back into their serene embrace. I must have really impressed the abbot during my stay at the monastery. In any case, this bounty hunter will no doubt claim my life if you don't stop them. Will you help?
stopConversation = "false",
options = {
{"@static_npc/tatooine/hedon_istee:player_1_2", "npc_2_2"}, --Yes, I'll save your life.
{"@static_npc/tatooine/hedon_istee:player_2_2", "npc_3_2"}, --Bounty Hunter?  Um.. no thanks.
{"@static_npc/tatooine/hedon_istee:player_3_2", "npc_4_2"}, --What kind of accusations?
}
}

hedon_istee_convotemplate:addScreen(npc_1_2);

--Accepted
npc_2_2 = ConvoScreen:new {
id = "npc_2_2",
leftDialog = "@static_npc/tatooine/hedon_istee:npc_2_2", --Excellent! The bounty hunter goes by the name of Rath Kanaz. I can tell you now that bounty hunters a very deceptive and cunning individuals. They may hurl some wild and baseless accusations to justify their actions. Don't listen to a word they say - it's all noncense.
stopConversation = "true",
options = {
}
}

hedon_istee_convotemplate:addScreen(npc_2_2);

--Declined
npc_3_2 = ConvoScreen:new {
id = "npc_3_2",
leftDialog = "@static_npc/tatooine/hedon_istee:npc_3_2", --But I thought we were good friends? I fear I'm at a loss for words. I'm not accustomed to this sort of treatment from a trusted companion. What is the galaxy coming to? 
stopConversation = "true",
options = {
}
}

hedon_istee_convotemplate:addScreen(npc_3_2);


--More
npc_4_2 = ConvoScreen:new {
id = "npc_4_2",
leftDialog = "@static_npc/tatooine/hedon_istee:npc_4_2", --Oh, he may go on about a stolen precious object or something equally as ridiculous. The B'omarr Order has no doubt deceived the poor soul. Those monks will stop at nothing to convince their hirelings of the justice of their cause. Pay it no mind, friend.
stopConversation = "true",
options = {
{"@static_npc/tatooine/hedon_istee:player_1_2", "npc_2_2"}, --Yes, I'll save your life.
{"@static_npc/tatooine/hedon_istee:player_2_2", "npc_3_2"} --Bounty Hunter?  Um.. no thanks.
}
}

hedon_istee_convotemplate:addScreen(npc_4_2);

--Not finished
npc_work_2 = ConvoScreen:new {
id = "npc_work_2",
leftDialog = "@static_npc/tatooine/hedon_istee:npc_work_2", --Has the Bounty Hunter been taken care of?
stopConversation = "false",
options = {
{"@static_npc/tatooine/hedon_istee:player_sorry_2", "npc_backtowork_2"}, --Not yet.  I've just tracked down his location and am on my way to eliminate him.
{"@static_npc/tatooine/hedon_istee:player_reset_2", "npc_reset_2"} --I'm sorry, but I don't want to get between you and a Bounty Hunter after all.  I can't do this.
}
}

hedon_istee_convotemplate:addScreen(npc_work_2);

--Not finished, continue
npc_backtowork_2 = ConvoScreen:new {
id = "npc_backtowork_2",
leftDialog = "@static_npc/tatooine/hedon_istee:npc_backtowork_2", --Well, I guess I'll have to go into hiding until you are able to handle the situation.
stopConversation = "true",
options = {
}
}

hedon_istee_convotemplate:addScreen(npc_backtowork_2);

--Not finished, abandon
npc_reset_2 = ConvoScreen:new {
id = "npc_reset_2",
leftDialog = "@static_npc/tatooine/hedon_istee:npc_reset_2", --But I thought we were good friends? I fear I'm at a loss for words. I'm not accustomed to this sort of treatment from a trusted companion. What is the galaxy coming to? 
stopConversation = "true",
options = {
}
}

hedon_istee_convotemplate:addScreen(npc_reset_2);

--Reward
npc_reward_2 = ConvoScreen:new {
id = "npc_reward_2",
leftDialog = "@static_npc/tatooine/hedon_istee:npc_reward_2", --I told you the bounty hunter would make wild claims. I assure you I don't know a thing about any "sacred scroll." I'm glad you're much smarter than the average mercenary, friend. As much as it saddens me to part with these credits, you have earned them.
stopConversation = "true",
options = {
}
}

hedon_istee_convotemplate:addScreen(npc_reward_2);


---
--MISSION 3: Bomarr Monk
---
--Intro
npc_1_3 = ConvoScreen:new {
id = "npc_1_3",
leftDialog = "@static_npc/tatooine/hedon_istee:npc_1_3", --All right, I admit it! I did steal a sacred scroll from the B'omarr Order! They could care less that I didn't want to achieve "enlightenment" - in fact, the abbot claimed I was a hopeless "sensualist" and had me expelled! Will you please return this scroll to the abbot so I can have peace?
stopConversation = "false",
options = {
{"@static_npc/tatooine/hedon_istee:player_1_3", "npc_2_3"}, --If it will put you at ease, I will do it.
{"@static_npc/tatooine/hedon_istee:player_2_3", "npc_3_3"}, --No, this is something you should do yourself.
{"@static_npc/tatooine/hedon_istee:player_3_3", "npc_4_3"}, --Why is this scroll important?
}
}

hedon_istee_convotemplate:addScreen(npc_1_3);

--Accepted
npc_2_3 = ConvoScreen:new {
id = "npc_2_3",
leftDialog = "@static_npc/tatooine/hedon_istee:npc_2_3", --Stalwart and true is how I'll describe you from now on! The abbot and his retinue have agreed to meet at these coordinates. Just hand them the scroll and leave. Whatever you do, don't accept an invitation to their monastery. They might try to "enlighten" you once you're there.
stopConversation = "true",
options = {
}
}

hedon_istee_convotemplate:addScreen(npc_2_3);

--Declined
npc_3_3 = ConvoScreen:new {
id = "npc_3_3",
leftDialog = "@static_npc/tatooine/hedon_istee:npc_3_3", --You can't back out on me now! After all, it was you who left those B'omarr thugs rotting in the desert! I won't get a moment's peace if you refuse to help me. Please reconsider!
stopConversation = "true",
options = {
}
}

hedon_istee_convotemplate:addScreen(npc_3_3);


--More
npc_4_3 = ConvoScreen:new {
id = "npc_4_3",
leftDialog = "@static_npc/tatooine/hedon_istee:npc_4_3", --I think it describes the complicated procedures involved in "enlightenment" - which is essentially how to remove and transport a living brain. All I know is that they thought it valuable, so therefore I assumed I could get a good price for it on the black market.
stopConversation = "true",
options = {
{"@static_npc/tatooine/hedon_istee:player_1_3", "npc_2_3"}, --If it will put you at ease, I will do it.
{"@static_npc/tatooine/hedon_istee:player_2_3", "npc_3_3"} --No, this is something you should do yourself.
}
}

hedon_istee_convotemplate:addScreen(npc_4_3);

--Not finished
npc_work_3 = ConvoScreen:new {
id = "npc_work_3",
leftDialog = "@static_npc/tatooine/hedon_istee:npc_work_3", --So, have you given it back?  Did they say they'll leave me alone now?
stopConversation = "false",
options = {
{"@static_npc/tatooine/hedon_istee:player_sorry_3", "npc_backtowork_3"}, --I haven't delievered it yet.  I will, though.
{"@static_npc/tatooine/hedon_istee:player_reset_3", "npc_reset_3"} --I think it would be better if you did this yourself.
}
}

hedon_istee_convotemplate:addScreen(npc_work_3);

--Not finished, continue
npc_backtowork_3 = ConvoScreen:new {
id = "npc_backtowork_3",
leftDialog = "@static_npc/tatooine/hedon_istee:npc_backtowork_3", --Please hurry before they send someone else to kill me!
stopConversation = "true",
options = {
}
}

hedon_istee_convotemplate:addScreen(npc_backtowork_3);

--Not finished, abandon
npc_reset_3 = ConvoScreen:new {
id = "npc_reset_3",
leftDialog = "@static_npc/tatooine/hedon_istee:npc_reset_3", --You can't back out on me now! After all, it was you who left those B'omarr thugs rotting in the desert! I won't get a moment's peace if you refuse to help me. Please reconsider!
stopConversation = "true",
options = {
}
}

hedon_istee_convotemplate:addScreen(npc_reset_3);

--Reward
npc_reward_3 = ConvoScreen:new {
id = "npc_reward_3",
leftDialog = "@static_npc/tatooine/hedon_istee:npc_reward_3", --I shall never forget you my friend. You have brought serenity to my life and have made it possible for me to get back to the important task of living it. I'm running a bit low on credits but I do have this map as a thanks for your help. Supposedly it leads to a treasure but I haven't mustered the courage to go there yet. Be careful if you do.
stopConversation = "true",
options = {
}
}

hedon_istee_convotemplate:addScreen(npc_reward_3);

addConversationTemplate("hedon_istee_convotemplate", hedon_istee_convotemplate);