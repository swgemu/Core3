local ObjectManager = require("managers.object.object_manager")

npcMapLibrarian =
	{
		{
			spawnData = { npcTemplate = "librarian", x = 40.7, z = 33, y = -93.9, direction = -97, cellID = 1688867, position = STAND },
			npcNumber = 1,
			stfFile = "@celebrity/librarian",
		},
	}

Librarian = ThemeParkLogic:new {
	npcMap = npcMapLibrarian,
	className = "Librarian",
	screenPlayState = "librarian",
	planetName = "naboo",
	distance = 500
}

registerScreenPlay("Librarian", true)

librarian_handler = conv_handler:new {}

function librarian_handler:getInitialScreen(pPlayer, pNpc, pConvTemplate)
	local convoTemplate = LuaConversationTemplate(pConvTemplate)
	local objectID = CreatureObject(pPlayer):getObjectID()
	writeData(objectID .. ":librarian", 1)

	return convoTemplate:getScreen("want_trivia")
end

function librarian_handler:runScreenHandlers(pConvTemplate, pPlayer, pNpc, selectedOption, pConvScreen)
	local pGhost = CreatureObject(pPlayer):getPlayerObject()

	if (pGhost == nil) then
		return pConvScreen
	end

	local screen = LuaConversationScreen(pConvScreen)
	local screenID = screen:getScreenID()

	local rightResponses = { "winner_is_you", "you_are_right", "good_answer", "correct", "correctamundo", "you_got_it" }

	local wrongResponses = { "too_bad_so_sad", "worst_ever_guesser", "thats_not_it", "no_sir", "you_are_wrong", "incorrect",
		"buzz_wrong_answer", "couldnt_be_wronger", "most_wrong", "bad_answer", "most_unfortunate",
		"most_incorrect", "worst_answer_ever", "wrongest", "wrong_squared", "you_are_weakest_link", "not_even_trying" }

	local objectID = CreatureObject(pPlayer):getObjectID()

	pConvScreen = screen:cloneScreen()
	local clonedConversation = LuaConversationScreen(pConvScreen)

	if (string.find(screenID, "question") ~= nil) then
		local questionNum = string.match(screenID, '%d+')
		local possibleAnswers = { { "wrong_one_" .. questionNum, wrongResponses[getRandomNumber(#wrongResponses)] },
			{ "wrong_two_" .. questionNum, wrongResponses[getRandomNumber(#wrongResponses)] },
			{ "wrong_three_" .. questionNum, wrongResponses[getRandomNumber(#wrongResponses)] } }

		if questionNum == "20" then
			possibleAnswers[#possibleAnswers+1] = { "right_" .. questionNum, "done" }
		else
			possibleAnswers[#possibleAnswers+1] = { "right_" .. questionNum, rightResponses[getRandomNumber(#rightResponses)] }
		end
		possibleAnswers = self:shuffleAnswers(possibleAnswers)

		writeData(objectID .. ":librarian", questionNum)

		clonedConversation:addOption("@celebrity/librarian:" .. possibleAnswers[1][1], possibleAnswers[1][2])
		clonedConversation:addOption("@celebrity/librarian:" .. possibleAnswers[2][1], possibleAnswers[2][2])
		clonedConversation:addOption("@celebrity/librarian:" .. possibleAnswers[3][1], possibleAnswers[3][2])
		clonedConversation:addOption("@celebrity/librarian:" .. possibleAnswers[4][1], possibleAnswers[4][2])
	end

	if (self:existsInTable(rightResponses, screenID)) then
		nextQuestion = readData(objectID .. ":librarian") + 1
		clonedConversation:addOption("@celebrity/librarian:yes", "question_" .. nextQuestion)
		clonedConversation:addOption("@celebrity/librarian:no", "good_bye")
	end

	if (self:existsInTable(wrongResponses, screenID)) then
		currentQuestion = readData(objectID .. ":librarian")
		writeData(objectID .. ":librarian", 1)
		clonedConversation:addOption("@celebrity/librarian:yes", "question_" .. currentQuestion)
		clonedConversation:addOption("@celebrity/librarian:no", "good_bye")
	end

	if (screenID == "done") then
		PlayerObject(pGhost):awardBadge(111)
	end

	return pConvScreen
end

function librarian_handler:shuffleAnswers(array)
	local arrayCount = #array
	for i = arrayCount, 2, -1 do
		local j = getRandomNumber(1, i)
		array[i], array[j] = array[j], array[i]
	end
	return array
end

function librarian_handler:existsInTable(table, item)
	for key, value in pairs(table) do
		if value == item then return true end
	end
	return false
end
