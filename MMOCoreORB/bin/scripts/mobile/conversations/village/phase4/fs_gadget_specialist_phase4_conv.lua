-- *FYI, this convo is a progressive subset of: "conversations/village/phase4/chief_engineer_phase4_conv.lua"

villageGadgetSpecialistPhase4ConvoTemplate = ConvoTemplate:new {
  initialScreen = "",
  templateType = "Lua",
  luaClassHandler = "villageGadgetSpecialistPhase4ConvoHandler",
  screens = {}
}

player_without_quest = ConvoScreen:new {
  id = "player_without_quest",
  leftDialog = "@conversation/fs_gadget_specialist:s_5a562246", -- "I've much to do... can I help you?"
  stopConversation = "false",
  options = {
    {"@conversation/fs_gadget_specialist:s_5542b04b", "choose_timid"}, -- "Oh, my apologies. I'll let you get back to work."
  }
}

villageGadgetSpecialistPhase4ConvoTemplate:addScreen(player_without_quest);

specialist_begin = ConvoScreen:new {
  id = "specialist_begin",
  leftDialog = "@conversation/fs_gadget_specialist:s_5a562246", -- "I've much to do... can I help you?"
  stopConversation = "false",
  options = {
    {"@conversation/fs_gadget_specialist:s_79fe19ed", "choose_inquire"}, -- "Yes, I was told you could help me obtain a replacement computer core."
    {"@conversation/fs_gadget_specialist:s_5542b04b", "choose_timid"}, -- "Oh, my apologies. I'll let you get back to work."
  }
}

villageGadgetSpecialistPhase4ConvoTemplate:addScreen(specialist_begin);

choose_timid = ConvoScreen:new {
  id = "choose_timid",
  leftDialog = "@conversation/fs_gadget_specialist:s_1283cb1c", -- "That's quite alright. Good day to you."
  stopConversation = "true",
  options = {}
}

villageGadgetSpecialistPhase4ConvoTemplate:addScreen(choose_timid);

choose_inquire = ConvoScreen:new {
  id = "choose_inquire",
  leftDialog = "@conversation/fs_gadget_specialist:s_b49f7181", -- "A replacement computer core? Who gave you that idea?"
  stopConversation = "false",
  options = {
    {"@conversation/fs_gadget_specialist:s_85bd3ae2", "choose_continue"}, -- "The chief engineer from a village on Dathomir. The village of Aurilia."
    {"@conversation/fs_gadget_specialist:s_55082d0b", "choose_timid_again"}, -- "Er... no one. I'm sorry to have bothered you."
  }
}

villageGadgetSpecialistPhase4ConvoTemplate:addScreen(choose_inquire);

choose_timid_again = ConvoScreen:new {
  id = "choose_timid_again",
  leftDialog = "@conversation/fs_gadget_specialist:s_3d8991fc", -- "I... um... see. Well. Good day then."
  stopConversation = "true",
  options = {}
}

villageGadgetSpecialistPhase4ConvoTemplate:addScreen(choose_timid_again);

choose_continue = ConvoScreen:new {
  id = "choose_continue",
  leftDialog = "@conversation/fs_gadget_specialist:s_4389624e", -- "Aurilia on Dathomir... yeah, I know the place. Well, know of it anyway. I've done business with them in the past. They need a replacement computer core?"
  stopConversation = "false",
  options = {
    {"@conversation/fs_gadget_specialist:s_a1dd9b9e", "choose_affirm"}, -- "That's correct. Their current one was damaged during an attack on the village."
  }
}

villageGadgetSpecialistPhase4ConvoTemplate:addScreen(choose_continue);

choose_affirm = ConvoScreen:new {
  id = "choose_affirm",
  leftDialog = "@conversation/fs_gadget_specialist:s_be68030a", -- "Well, I wish I could help, but I don't have anything like that in stock. Rarely do to be honest. I tend to tinker more with smaller devices. Large systems like a town... or village... computer require far more attention than I'm willing to give."
  stopConversation = "false",
  options = {
    {"@conversation/fs_gadget_specialist:s_4d7434d2", "choose_bummed"}, -- "That's disappointing. But I guess if you don't have one, then you don't have one."
  }
}

villageGadgetSpecialistPhase4ConvoTemplate:addScreen(choose_affirm);

choose_bummed = ConvoScreen:new {
  id = "choose_bummed",
  leftDialog = "@conversation/fs_gadget_specialist:s_533919fc", -- "Tell the Aurilia engineer that I wish I could have been more helpful, but not much I can really do about something like that."
  stopConversation = "false",
  options = {
    {"@conversation/fs_gadget_specialist:s_be1b8c5a", "choose_persist"}, -- "Is there nothing that can be done to find a replacement for Aurilia?"
  }
}

villageGadgetSpecialistPhase4ConvoTemplate:addScreen(choose_bummed);

choose_persist = ConvoScreen:new {
  id = "choose_persist",
  leftDialog = "@conversation/fs_gadget_specialist:s_e5c058a8", -- "Hmm... let me think a minute. You know, there might just be something I can help you with after all. Most satellites have a central computer that is heavily shielded to withstand the extreme nature of their orbit. Once a satellite falls from orbit and is abandoned, anyone can purchase the rights to them. I've done so myself on various occassions."
  stopConversation = "false",
  options = {
    {"@conversation/fs_gadget_specialist:s_fff0f4f2", "choose_persist_continue"}, -- "How do I purchase the rights to a fallen and abandoned satellite?"
  }
}

villageGadgetSpecialistPhase4ConvoTemplate:addScreen(choose_persist);

choose_persist_continue = ConvoScreen:new {
  id = "choose_persist_continue",
  leftDialog = "@conversation/fs_gadget_specialist:s_e79d337", -- "Nothing's easier. you simply go to any starport and speak with the ticket droid. These droids have access to a galactic-wide database that maintains records about satellites in orbit around most known planets. For a fee, you can purchase the rights to one that has fallen and gone unclaimed."
  stopConversation = "false",
  options = {
    {"@conversation/fs_gadget_specialist:s_b9f237f", "choose_starport"}, -- "Sounds reasonable. I'm off to the starport."
    {"@conversation/fs_gadget_specialist:s_46bdeee4", "choose_giveup"}, -- "Sounds like a terrible idea. Thanks for nothing."
  }
}

villageGadgetSpecialistPhase4ConvoTemplate:addScreen(choose_persist_continue);

choose_giveup = ConvoScreen:new {
  id = "choose_giveup",
  leftDialog = "@conversation/fs_gadget_specialist:s_9d19b512", -- "Ha. Whatever. Be on your way, then."
  stopConversation = "true",
  options = {}
}

villageGadgetSpecialistPhase4ConvoTemplate:addScreen(choose_giveup);

choose_starport = ConvoScreen:new {
  id = "choose_starport",
  leftDialog = "@conversation/fs_gadget_specialist:s_bdedc5e2", -- "Wait! Before speaking with the droid, there's one other thing. You'll need a downed satellite tracking device. When you purchase the rights to one, the droid will upload tracking data to your tracking device. It will then help you to locate the fallen satellite. I can provide you with a kit for just such a device for a small fee. Say, 530 credits?"
  stopConversation = "false",
  options = {
    {"@conversation/fs_gadget_specialist:s_a8749106", "choose_kit"}, -- "Sounds fair enough. I'll take one."
    {"@conversation/fs_gadget_specialist:s_a8749106", "choose_kit_nofunds"}, -- "Sounds fair enough. I'll take one."
    {"@conversation/fs_gadget_specialist:s_a8749106", "choose_kit_nospace"}, -- "Sounds fair enough. I'll take one."
    {"@conversation/fs_gadget_specialist:s_8fe6a678", "choose_accuse"}, -- "You must think I just fell off of a bantha! I'll not be scammed so easily."
  }
}

villageGadgetSpecialistPhase4ConvoTemplate:addScreen(choose_starport);

choose_accuse = ConvoScreen:new {
  id = "choose_accuse",
  leftDialog = "@conversation/fs_gadget_specialist:s_6d9d310", -- "Ha. I was just offering to help. You can't expect me to ignore my livelihood and give this kind of thing away for nothing. My price is more than fair. But whatever. Good day."
  stopConversation = "true",
  options = {}
}

villageGadgetSpecialistPhase4ConvoTemplate:addScreen(choose_accuse);

choose_kit_nofunds = ConvoScreen:new {
  id = "choose_kit_nofunds",
  leftDialog = "@conversation/fs_gadget_specialist:s_b518079a", -- "You don't seem to have enough funds at the moment. I'd love to help, but I can't give the kit away for nothing. Come back when you have more funds."
  stopConversation = "true",
  options = {}
}

villageGadgetSpecialistPhase4ConvoTemplate:addScreen(choose_kit_nofunds);

choose_kit_nospace = ConvoScreen:new {
  id = "choose_kit_nospace",
  leftDialog = "@conversation/fs_gadget_specialist:s_faaeb65f", -- "You don't have enough space in your inventory for the kit. Make some room and then come speak with me again."
  stopConversation = "true",
  options = {}
}

villageGadgetSpecialistPhase4ConvoTemplate:addScreen(choose_kit_space);

return_with_funds_or_space = ConvoScreen:new {
  id = "return_with_funds_or_space",
  leftDialog = "@conversation/fs_gadget_specialist:s_7045a2d7", -- "Welcome back. Still interested in a downed satellite tracking device? The price is 530 credits."
  stopConversation = "false",
  options = {
    {"@conversation/fs_gadget_specialist:s_a8749106", "choose_kit"}, -- "Sounds fair enough. I'll take one."
  }
}

villageGadgetSpecialistPhase4ConvoTemplate:addScreen(return_with_funds_or_space);

choose_kit = ConvoScreen:new {
  id = "choose_kit",
  leftDialog = "@conversation/fs_gadget_specialist:s_bdcd33ef", -- "Excellent. I'll just place it in your inventory. Good luck finding a satellite and that replacement computer core."
  stopConversation = "false",
  options = {
    {"@conversation/fs_gadget_specialist:s_c7baf80c", "choose_kit_wonder"}, -- "What do I do with this tracking device kit?"
  }
}

villageGadgetSpecialistPhase4ConvoTemplate:addScreen(choose_kit);

choose_kit_wonder = ConvoScreen:new {
  id = "choose_kit_wonder",
  leftDialog = "@conversation/fs_gadget_specialist:s_4bcdc402", -- "You need to collect or craft all of the required components and place them in the kit. Once you have all of the components, the kit's automated system will build the tracking device."
  stopConversation = "false",
  options = {
    {"@conversation/fs_gadget_specialist:s_7f396fce", "wonder_device"}, -- "How do I use this tracking device?"
  }
}

villageGadgetSpecialistPhase4ConvoTemplate:addScreen(choose_kit_wonder);

wonder_device = ConvoScreen:new {
  id = "wonder_device",
  leftDialog = "@conversation/fs_gadget_specialist:s_f9732f00", -- "Simply use the device's menu and choose to activate the tracking device. If you're on the wrong planet, it will tell you which planet the satellite is on. Once you're on the correct planet, the device can then pinpoint the exact location of the satellite."
  stopConversation = "false",
  options = {
    {"@conversation/fs_gadget_specialist:s_bab2829b", "wonder_again_repeat"}, -- "How do I get tracking data for a fallen satellite?"
  }
}

villageGadgetSpecialistPhase4ConvoTemplate:addScreen(wonder_device);

wonder_again_repeat = ConvoScreen:new {
  id = "wonder_again_repeat",
  leftDialog = "@conversation/fs_gadget_specialist:s_65f76975", -- "Go to any ticket droid at a starport. They have access to the database with information about fallen and abandoned satellites around the galaxy. You can purchase the rights to one of them from the droid."
  stopConversation = "true",
  options = {}
}

villageGadgetSpecialistPhase4ConvoTemplate:addScreen(wonder_again_repeat);

return_with_core = ConvoScreen:new {
  id = "return_with_core",
  leftDialog = "@conversation/fs_gadget_specialist:s_5a562246", -- "I've much to do... can I help you?"
  stopConversation = "false",
  options = {
    {"@conversation/fs_gadget_specialist:s_fe739220", "choose_wonder_core"}, -- "The computer core is ready... now what?"
    {"@conversation/fs_gadget_specialist:s_5542b04b", "choose_timid"}, -- "Oh, my apologies. I'll let you get back to work."
  }
}

villageGadgetSpecialistPhase4ConvoTemplate:addScreen(return_with_core);

choose_wonder_core = ConvoScreen:new {
  id = "choose_wonder_core",
  leftDialog = "@conversation/fs_gadget_specialist:s_d8a8c77e", -- "Now you can bring it to Aurilia's chief engineer and then bask in the glory of a job well done."
  stopConversation = "false",
  options = {
    {"@conversation/fs_gadget_specialist:s_b867b2e4", "choose_wonder_final"}, -- "How do I make this computer core work with the village computer?"
  }
}

villageGadgetSpecialistPhase4ConvoTemplate:addScreen(choose_wonder_core);

choose_wonder_final = ConvoScreen:new {
  id = "choose_wonder_final",
  leftDialog = "@conversation/fs_gadget_specialist:s_70253663", -- "The chief engineer at Aurilia can probably give you more information, but I believe you'll have to modify the core's current interface so that it will be compatible with the village's computer. Usually there's a simple menu on the core itself that will allow you to try and modify it."
  stopConversation = "true",
  options = {}
}

villageGadgetSpecialistPhase4ConvoTemplate:addScreen(choose_wonder_final);

addConversationTemplate("villageGadgetSpecialistPhase4ConvoTemplate", villageGadgetSpecialistPhase4ConvoTemplate);