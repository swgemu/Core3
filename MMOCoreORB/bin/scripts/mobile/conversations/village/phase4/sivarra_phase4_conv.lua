villageSivarraPhase4ConvoTemplate = ConvoTemplate:new {
  initialScreen = "",
  templateType = "Lua",
  luaClassHandler = "villageSivarraPhase4ConvoHandler",
  screens = {}
}

intro_not_eligible = ConvoScreen:new {
  id = "intro_not_eligible",
  leftDialog = "@conversation/fs_combat_healing_quest:s_48b1807b", -- "What? Do I look like I have time to chit chat?!?"
  stopConversation = "true",
  options = {}
}

villageSivarraPhase4ConvoTemplate:addScreen(intro_not_eligible);

intro_full_inventory = ConvoScreen:new {
  id = "intro_full_inventory",
  leftDialog = "@conversation/fs_combat_healing_quest:s_a7b82bb9", -- "Huh? I can't deal with you if you don't have any room to hold things, clear up some room and come back! And hurry, I'm not sure how long we have."
  stopConversation = "true",
  options = {}
}

villageSivarraPhase4ConvoTemplate:addScreen(intro_full_inventory);

intro_give_first_set_reward = ConvoScreen:new {
  id = "intro_give_first_set_reward",
  leftDialog = "@conversation/fs_combat_healing_quest:s_8d7b6d3", -- "Hmm... I see the Force has gifted you as a healer. You seem to have unlocked some potential in yourself. I wish I could guide you more, but that is all I can do for you. There is still much to do, let me know if you would like to help some more."
  stopConversation = "true",
  options = {}
}

villageSivarraPhase4ConvoTemplate:addScreen(intro_give_first_set_reward);

intro_give_second_set_reward = ConvoScreen:new {
  id = "intro_give_second_set_reward",
  leftDialog = "@conversation/fs_combat_healing_quest:s_5b948c11", -- "Ah! Yes, you're back! You've done so much, I happen to have an extra tank that we don't have room for, I'm sure a gifted healer such as yourself will find a good place for it."
  stopConversation = "true",
  options = {}
}

villageSivarraPhase4ConvoTemplate:addScreen(intro_give_second_set_reward);

intro_has_otherquest = ConvoScreen:new {
  id = "intro_has_otherquest",
  leftDialog = "@conversation/fs_combat_healing_quest:s_5b2d3e0f", -- "Who? Oh, you seem far too busy to help me now, if you have time please see if there are any other medics available."
  stopConversation = "true",
  options = {}
}

villageSivarraPhase4ConvoTemplate:addScreen(intro_has_otherquest);

intro_has_no_medic = ConvoScreen:new {
  id = "intro_has_no_medic",
  leftDialog = "@conversation/fs_combat_healing_quest:s_14e60463", -- "You don't seem to have any medical training at all. I'm sorry, but I don't think you are going to be able to help me"
  stopConversation = "true",
  options = {}
}

villageSivarraPhase4ConvoTemplate:addScreen(intro_has_no_medic);

intro_begin = ConvoScreen:new {
  id = "intro_begin",
  leftDialog = "@conversation/fs_combat_healing_quest:s_7ed32afc", -- "Huh? Oh! Great! More medics! The troops are in desperate need of support. Are you here to provide the medical support?"
  stopConversation = "false",
  options = {
    {"@conversation/fs_combat_healing_quest:s_8fddaea0", "choose_accept"}, -- "Yes, I want to help."
    {"@conversation/fs_combat_healing_quest:s_d4d1a11f", "choose_decline"}, -- "Sorry, no."
  }
}

villageSivarraPhase4ConvoTemplate:addScreen(intro_begin);

choose_decline = ConvoScreen:new {
  id = "choose_decline",
  leftDialog = "@conversation/fs_combat_healing_quest:s_df4917e", -- "Too bad, too bad, we need some help here, but I'm sure you already realized that. Excuse me, I have much to do."
  stopConversation = "true",
  options = {}
}

villageSivarraPhase4ConvoTemplate:addScreen(choose_decline);

choose_accept = ConvoScreen:new {
  id = "choose_accept",
  leftDialog = "@conversation/fs_combat_healing_quest:s_ad2d5f2b", -- "Help? Yes, you can help! What I need you to help with is troop support. This may put you in direct harms way, and you won't be able to help the other villagers with their tasks, but I will make sure Noldan helps you to develop your healing abilities even more. Are you sure?"
  stopConversation = "false",
  options = {
    {"@conversation/fs_combat_healing_quest:s_25b83816", "choose_certain"}, -- "Yes, I'm sure."
    {"@conversation/fs_combat_healing_quest:s_5d4f7fdb", "choose_uncertain"}, -- "On second thought..."
  }
}

villageSivarraPhase4ConvoTemplate:addScreen(choose_accept);

choose_certain = ConvoScreen:new {
  id = "choose_certain",
  leftDialog = "@conversation/fs_combat_healing_quest:s_1f0513d3", -- "Yes! Yes! I need you to go find the groups of defenders and join them, you will need to support them while they are defending us as any good medic would. Be careful, you will be in harms way sometimes! If you can help out fifty times that would be a great help! Oh, and you can come back and talk to me or the droids to track your progress!"
  stopConversation = "true",
  options = {}
}

villageSivarraPhase4ConvoTemplate:addScreen(choose_certain);

choose_uncertain = ConvoScreen:new {
  id = "choose_uncertain",
  leftDialog = "@conversation/fs_combat_healing_quest:s_8c663fab", -- "I see, I see... I was hoping you would be made of sterner stuff, but I guess not."
  stopConversation = "true",
  options = {}
}

villageSivarraPhase4ConvoTemplate:addScreen(choose_uncertain);

intro_start_second_set = ConvoScreen:new {
  id = "intro_start_second_set",
  leftDialog = "@conversation/fs_combat_healing_quest:s_6a7931f2", -- "Hmm... I can tell you are a great healer, I may have something else for you if you are interested in helping some more."
  stopConversation = "false",
  options = {
    {"@conversation/fs_combat_healing_quest:s_aa2e6c00", "choose_continue"}, -- "Sure, I'll help."
    {"@conversation/fs_combat_healing_quest:s_2e7fd1c", "choose_cease"}, -- "Sorry, maybe later."
  }
}

villageSivarraPhase4ConvoTemplate:addScreen(intro_start_second_set);

choose_continue = ConvoScreen:new {
  id = "choose_continue",
  leftDialog = "@conversation/fs_combat_healing_quest:s_3fd56843", -- "Brilliant! I need you to, well to help the troops more. If you can help out a total of 100 times that would be wonderful."
  stopConversation = "true",
  options = {}
}

villageSivarraPhase4ConvoTemplate:addScreen(choose_continue);

choose_cease = ConvoScreen:new {
  id = "choose_cease",
  leftDialog = "@conversation/fs_combat_healing_quest:s_671a071f", -- "Well, let me know if you change your mind!"
  stopConversation = "true",
  options = {}
}

villageSivarraPhase4ConvoTemplate:addScreen(choose_cease);

intro_in_progress = ConvoScreen:new {
  id = "intro_in_progress",
  leftDialog = "@conversation/fs_combat_healing_quest:s_e6d3592a", -- "I see, I see, yes very good, it looks like %TO"
  stopConversation = "false",
  options = {
    {"@conversation/fs_combat_healing_quest:s_67e6df55", "update_continue"}, -- "Okay."
  }
}

villageSivarraPhase4ConvoTemplate:addScreen(intro_in_progress);

update_continue = ConvoScreen:new {
  id = "update_continue",
  leftDialog = "@conversation/fs_combat_healing_quest:s_e734fdf3", -- "Keep at it!"
  stopConversation = "true",
  options = {}
}

villageSivarraPhase4ConvoTemplate:addScreen(update_continue);

intro_completed_quest = ConvoScreen:new {
  id = "intro_completed_quest",
  leftDialog = "@conversation/fs_combat_healing_quest:s_7263868e", -- "Thank you! Thank you so much for your help! Can't talk much, still have much to do."
  stopConversation = "true",
  options = {}
}

villageSivarraPhase4ConvoTemplate:addScreen(intro_completed_quest);

addConversationTemplate("villageSivarraPhase4ConvoTemplate", villageSivarraPhase4ConvoTemplate);
