imperial_officer_1_conv = ConvoScreen:new {
	id = "initial",
    leftDialog = "@newbie_tutorial/newbie_convo:convo_1_start",
    
    optionText = "",
    optionLink = "",

	children = {  }
}

imperial_officer_1_conv_reply = ConvoScreen:new {
	id = "reply1",
    leftDialog = "@newbie_tutorial/newbie_convo:convo_1_more",
    
    optionText = "@newbie_tutorial/newbie_convo:convo_1_reply_1",
    optionLink = "",

	children = { }
}

imperial_officer_1_conv:addOption(imperial_officer_1_conv_reply)

imperial_officer_1_conv_reply_2 = ConvoScreen:new {
	id = "reply2",
    leftDialog = "@newbie_tutorial/newbie_convo:convo_1_explain",
    
    optionText = "@newbie_tutorial/newbie_convo:convo_1_reply_2",
    optionLink = "",

	children = { }
}

imperial_officer_1_conv_reply:addOption(imperial_officer_1_conv_reply_2)

imperial_officer_1_conv_reply_3 = ConvoScreen:new {
	id = "reply3",
    leftDialog = "@newbie_tutorial/newbie_convo:convo_1_stuff",
    
    optionText = "@newbie_tutorial/newbie_convo:convo_1_reply_3",
    optionLink = "",

	children = { }
}

imperial_officer_1_conv_reply_2:addOption(imperial_officer_1_conv_reply_3)

addConversationTemplate("imperial_officer_1_conv", imperial_officer_1_conv)