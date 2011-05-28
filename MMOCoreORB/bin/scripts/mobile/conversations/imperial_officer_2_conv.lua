imperial_officer_2_conv = ConvoScreen:new {
	id = "initial",
    leftDialog = "@newbie_tutorial/newbie_convo:banker_1_start",
    
    optionText = "",
    optionLink = "",

	children = {  }
}
-------
	imperial_officer_2_conv_reply = ConvoScreen:new {
		id = "reply1_1",
	    leftDialog = "@newbie_tutorial/newbie_convo:banker_2_start",
	    
	    optionText = "@newbie_tutorial/newbie_convo:banker_1_reply_1",
	    optionLink = "",
	
		children = { }
	}
	
	imperial_officer_2_conv:addOption(imperial_officer_2_conv_reply)

	-----------
		imperial_officer_2_conv_reply_2_1 = ConvoScreen:new {
			id = "reply2_1", -- will go back to reply1_1 on selection
		    leftDialog = "@newbie_tutorial/newbie_convo:banker_2_more",
		    
		    optionText = "@newbie_tutorial/newbie_convo:banker_2_reply_1",
		    optionLink = "",
		
			children = { }
		}
		
		imperial_officer_2_conv_reply:addOption(imperial_officer_2_conv_reply_2_1)
			
		
		imperial_officer_2_conv_reply_2_2 = ConvoScreen:new {
			id = "reply2_2",
		    leftDialog = "@newbie_tutorial/newbie_convo:banker_2_explain_2",
		    
		    optionText = "@newbie_tutorial/newbie_convo:banker_2_reply_2",
		    optionLink = "",
		
			children = { }
		}
		
		imperial_officer_2_conv_reply:addOption(imperial_officer_2_conv_reply_2_2)
		
		imperial_officer_2_conv_reply_2_3 = ConvoScreen:new {
			id = "reply2_3",
		    leftDialog = "@newbie_tutorial/newbie_convo:banker_2_explain",
		    
		    optionText = "@newbie_tutorial/newbie_convo:banker_2_reply_3",
		    optionLink = "",
		
			children = { }
		}
		
		imperial_officer_2_conv_reply:addOption(imperial_officer_2_conv_reply_2_3)

		------------
			imperial_officer_2_conv_reply_3_3 = ConvoScreen:new {
				id = "reply3_3",
			    leftDialog = "@newbie_tutorial/newbie_convo:banker_2_explain_terminals",
			    
			    optionText = "@newbie_tutorial/newbie_convo:banker_1_reply_3",
			    optionLink = "",
			
				children = { }
			}
			
			imperial_officer_2_conv_reply_2_3:addOption(imperial_officer_2_conv_reply_3_3)
		
			---------
			
				imperial_officer_2_conv_reply_4_3 = ConvoScreen:new {
					id = "reply4_3",
				    leftDialog = "@newbie_tutorial/newbie_convo:banker_2_more_bank",
				    
				    optionText = "@newbie_tutorial/newbie_convo:banker_bank_reply_1",
				    optionLink = "",
				
					children = { }
				}
				
				imperial_officer_2_conv_reply_3_3:addOption(imperial_officer_2_conv_reply_4_3)
				
				-------
				
					imperial_officer_2_conv_reply_5_3 = ConvoScreen:new {
						id = "reply5_3",
					    leftDialog = "@newbie_tutorial/newbie_convo:banker_2_bank_answer",
					    
					    optionText = "@newbie_tutorial/newbie_convo:banker_2_bank_question",
					    optionLink = "",
					
						children = { }
					}
					
					imperial_officer_2_conv_reply_4_3:addOption(imperial_officer_2_conv_reply_5_3)
					
					imperial_officer_2_conv_reply_6_3 = ConvoScreen:new {
						id = "reply6_3",
					    leftDialog = "@newbie_tutorial/newbie_convo:banker_2_bank_answer_2",
					    
					    optionText = "@newbie_tutorial/newbie_convo:banker_bank_question_2",
					    optionLink = "",
					
						children = { }
					}
					
					imperial_officer_2_conv_reply_4_3:addOption(imperial_officer_2_conv_reply_6_3)
					
					imperial_officer_2_conv_reply_7_3 = ConvoScreen:new {
						id = "reply7_3",
					    leftDialog = "@newbie_tutorial/newbie_convo:banker_bazaar_1",
					    
					    optionText = "@newbie_tutorial/newbie_convo:banker_2_reply_2",
					    optionLink = "",
					
						children = { }
					}
					
					imperial_officer_2_conv_reply_4_3:addOption(imperial_officer_2_conv_reply_7_3)
					
					-----
					
						imperial_officer_2_conv_reply_8_3 = ConvoScreen:new {
							id = "reply8_3",
						    leftDialog = "@newbie_tutorial/newbie_convo:banker_bazaar_2",
						    
						    optionText = "@newbie_tutorial/newbie_convo:banker_bazaar_reply_1",
						    optionLink = "",
						
							children = { }
						}
						
						imperial_officer_2_conv_reply_7_3:addOption(imperial_officer_2_conv_reply_8_3)
						
						-----
						
							imperial_officer_2_conv_reply_9_3 = ConvoScreen:new {
								id = "reply9_3",
							    leftDialog = "@newbie_tutorial/newbie_convo:banker_bazaar_3",
							    
							    optionText = "@newbie_tutorial/newbie_convo:banker_bazaar_reply_2",
							    optionLink = "initial",
							
								children = { }
							}
							
							imperial_officer_2_conv_reply_8_3:addOption(imperial_officer_2_conv_reply_9_3)
				
				--------

	------

	imperial_officer_2_conv_reply_1_2 = ConvoScreen:new {
		id = "reply1_2",
	    leftDialog = "@newbie_tutorial/newbie_convo:banker_2_start",
	    
	    optionText = "@newbie_tutorial/newbie_convo:banker_1_reply_2",
	    optionLink = "",
	
		children = { }
	}
	
	imperial_officer_2_conv:addOption(imperial_officer_2_conv_reply_1_2)
	



addConversationTemplate("imperial_officer_2_conv", imperial_officer_2_conv)