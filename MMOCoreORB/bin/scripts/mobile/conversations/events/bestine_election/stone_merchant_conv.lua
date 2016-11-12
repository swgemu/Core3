StoneMerchantConvoTemplate = ConvoTemplate:new {
  initialScreen = "",
  templateType = "Lua",
  luaClassHandler = "stone_merchant_conv_handler",
  screens = {}
}

intro_start = ConvoScreen:new {
  id = "intro_start",
  leftDialog = "@conversation/bestine_stone_merchant:s_8762f9f", --I'm in the business of collecting rare stones. Unfortunately, I haven't had much business lately. I guess I should find another business.
  stopConversation = "false",
  options = { }
}
StoneMerchantConvoTemplate:addScreen(intro_start);

may_have_stones = ConvoScreen:new {
  id = "may_have_stones",
  leftDialog = "@conversation/bestine_stone_merchant:s_e21cea57", --You do?! What kind of stones?
  stopConversation = "false",
  options = {}
}
StoneMerchantConvoTemplate:addScreen(may_have_stones);

returned_have_stones = ConvoScreen:new {
  id = "returned_have_stones",
  leftDialog = "@conversation/bestine_stone_merchant:s_f56c7c9f", --Do you have more stones for me?
  stopConversation = "false",
  options = {
  }
}
StoneMerchantConvoTemplate:addScreen(returned_have_stones);

have_carved_stone = ConvoScreen:new {
  id = "have_carved_stone",
  leftDialog = "@conversation/bestine_stone_merchant:s_cc49587f", --Wow! That's just what I'm looking for! I can take it off your hands if you want. I need to test every one very carefully. So what do you say? Which one do you want to give me?
  stopConversation = "false",
  options = {  }
}
StoneMerchantConvoTemplate:addScreen(have_carved_stone);

have_smooth_stone = ConvoScreen:new {
  id = "have_smooth_stone",
  leftDialog = "@conversation/bestine_stone_merchant:s_cc49587f", --Wow! That's just what I'm looking for! I can take it off your hands if you want. I need to test every one very carefully. So what do you say? Which one do you want to give me?
  stopConversation = "false",
  options = {
 }
}
StoneMerchantConvoTemplate:addScreen(have_smooth_stone);

just_looking = ConvoScreen:new {
  id = "just_looking",
  leftDialog = "@conversation/bestine_stone_merchant:s_b04b4ef5", --Alright. If you have any stones, be sure to come back!
  stopConversation = "true",
  options = {  }
}
StoneMerchantConvoTemplate:addScreen(just_looking);

look_for_some = ConvoScreen:new {
  id = "look_for_some",
  leftDialog = "@conversation/bestine_stone_merchant:s_9e6e06eb", --You will? Too bad I don't know where they are. I heard a rumor that Victor Visalis may know. He's over at the capitol. He doesn't usually talk about things other than the election. Maybe if he won the election... oh well. If you ever find any, I'm here.
  stopConversation = "true",
  options = { }
}
StoneMerchantConvoTemplate:addScreen(look_for_some);

probably_bye = ConvoScreen:new {
  id = "probably_bye",
  leftDialog = "@conversation/bestine_stone_merchant:s_1cb401b5", --I'll keep searching!
  stopConversation = "true",
  options = { }
}
StoneMerchantConvoTemplate:addScreen(probably_bye);

give_carved_stone = ConvoScreen:new {
  id = "give_carved_stone",
  leftDialog = "@conversation/bestine_stone_merchant:s_bb2c2468", --Thank you! Here, I'll give you this. We'll say you bought it from me by giving me the stone. It's rare so guard it closely.
  stopConversation = "true",
  options = { }
}
StoneMerchantConvoTemplate:addScreen(give_carved_stone);

give_smooth_stone = ConvoScreen:new {
  id = "give_smooth_stone",
  leftDialog = "@conversation/bestine_stone_merchant:s_bb2c2468", --Thank you! Here, I'll give you this. We'll say you bought it from me by giving me the stone. It's rare so guard it closely.
  stopConversation = "true",
  options = { }
}
StoneMerchantConvoTemplate:addScreen(give_smooth_stone);

keeping_stone = ConvoScreen:new {
  id = "keeping_stone",
  leftDialog = "@conversation/bestine_stone_merchant:s_d7a9bace", --Oh... okay. Well, if you decide you'd rather get it off your hands, feel free to seek me out! I'll surely buy them off you.
  stopConversation = "true",
  options = { }
}
StoneMerchantConvoTemplate:addScreen(keeping_stone);

addConversationTemplate("StoneMerchantConvoTemplate", StoneMerchantConvoTemplate);
