seansHistorianConvoTemplate = ConvoTemplate:new {
  initialScreen = "",
  templateType = "Lua",
  luaClassHandler = "seans_historian_conv_handler",
  screens = {}
}

sean_inOffice = ConvoScreen:new {
  id = "sean_inOffice",
  leftDialog = "@conversation/seans_historian:s_79636e28", -- We recently found this wreckage. It is rumored to be the Red-Sin Valon. How exciting! Sean Trenwell funds us out of his own pocket. We hope to find interesting things here. You should talk to Sean to see if he needs any help.
  stopConversation = "true",
  options = {
    }
}
seansHistorianConvoTemplate:addScreen(sean_inOffice);

sean_notinOffice = ConvoScreen:new {
  id = "sean_notinOffice",
  leftDialog = "@conversation/seans_historian:s_3d3d4bab", -- We recently found this wreckage. It is rumored to be the Red-Sin Valon. How exciting! Sean Trenwell funds us out of his own pocket. We hope to find interesting things here. You should talk to Sean when he's in office.
  stopConversation = "true",
  options = {
    }
}
seansHistorianConvoTemplate:addScreen(sean_notinOffice);

has_historyQuest = ConvoScreen:new {
  id = "has_historyQuest",
  leftDialog = "@conversation/seans_historian:s_65275fb4", --Ah! You must be the new assistant. Welcome to the crash site of the Red-Sin Valon. Before you start poking around, maybe you'll want to hear a little history about the site first. It will give you a little sensitivity about an already-delicate situation.
  stopConversation = "false",
  options = {
    {"@conversation/seans_historian:s_647601e7","tellme_history"}, -- Sure. Tell me the history.
    }
}
seansHistorianConvoTemplate:addScreen(has_historyQuest);

tellme_history = ConvoScreen:new {
  id = "tellme_history",
  leftDialog = "@conversation/seans_historian:s_1f6355d4", --The Red-Sin Valon carried the first of the new settlers to Tatooine. The captain of the ship and her crew members helped found Bestine. Despite the early difficulties--a severe economic depression, lack of water and so forth--Bestine survived and became the thriving city we see today. There's so much more depth to it...
  stopConversation = "false",
  options = {
    {"@conversation/seans_historian:s_e547fd1e","tellme_history_2"}, --Yeah?
  }
}
seansHistorianConvoTemplate:addScreen(tellme_history);

tellme_history_2 = ConvoScreen:new {
  id = "tellme_history_2",
  leftDialog = "@conversation/seans_historian:s_4d42d7da", --Anyway, you should check the wreckage to see what you find. If you do find anything, you can bring it to me. I'm required to screen whatever is found. We don't need to excite Sean Trenwell over nothing, you know what I mean? Go ahead and look around.
  stopConversation = "false",
  options = {
    {"@conversation/seans_historian:s_67e6df55","tellme_history_3"}, --Okay.
     {"@conversation/seans_historian:s_5ec0adb6","decided_notto"}, --I've decided not to. Good bye.
  }
}
seansHistorianConvoTemplate:addScreen(tellme_history_2);

tellme_history_3 = ConvoScreen:new {
  id = "tellme_history_3",
  leftDialog = "@conversation/seans_historian:s_2fceb7e3", --And be careful!
  stopConversation = "true",
  options = { }
}
seansHistorianConvoTemplate:addScreen(tellme_history_3);

decided_notto = ConvoScreen:new {
  id = "decided_notto",
  leftDialog = "@conversation/seans_historian:s_fcdb7174", --That's a shame. I'll inform Sean about it, then.
  stopConversation = "true",
  options = { }
}
seansHistorianConvoTemplate:addScreen(decided_notto);

hquest_find = ConvoScreen:new {
  id = "hquest_find",
  leftDialog = "@conversation/seans_historian:s_8d32acbf", --Did you find anything?
  stopConversation = "false",
  options = { }
}
seansHistorianConvoTemplate:addScreen(hquest_find);

found_something = ConvoScreen:new {
  id = "found_something",
  leftDialog = "@conversation/seans_historian:s_27540308", --Well done! What an interesting piece of history. You'd think it would have been destroyed in these dreadful sand storms. Guess not! Take it to Sean. He'll be excited.
  stopConversation = "true",
  options = {
   }
}
seansHistorianConvoTemplate:addScreen(found_something);

keep_looking = ConvoScreen:new {
  id = "keep_looking",
  leftDialog = "@conversation/seans_historian:s_ed53cd9c", -- Okay. Be sure to show it to me if you do.
  stopConversation = "true",
  options = {
   }
}
seansHistorianConvoTemplate:addScreen(keep_looking);

addConversationTemplate("seansHistorianConvoTemplate", seansHistorianConvoTemplate);