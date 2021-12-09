--Copyright (C) 2007 <SWGEmu>

--This File is part of Core3.

--This program is free software; you can redistribute
--it and/or modify it under the terms of the GNU Lesser
--General Public License as published by the Free Software
--Foundation; either version 2 of the License,
--or (at your option) any later version.

--This program is distributed in the hope that it will be useful,
--but WITHOUT ANY WARRANTY; without even the implied warranty of
--MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.
--See the GNU Lesser General Public License for
--more details.

--You should have received a copy of the GNU Lesser General
--Public License along with this program; if not, write to
--the Free Software Foundation, Inc., 51 Franklin St, Fifth Floor, Boston, MA 02110-1301 USA

--Linking Engine3 statically or dynamically with other modules
--is making a combined work based on Engine3.
--Thus, the terms and conditions of the GNU Lesser General Public License
--cover the whole combination.

--In addition, as a special exception, the copyright holders of Engine3
--give you permission to combine Engine3 program with free software
--programs or libraries that are released under the GNU LGPL and with
--code included in the standard release of Core3 under the GNU LGPL
--license (or modified versions of such code, with unchanged license).
--You may copy and distribute such a system following the terms of the
--GNU LGPL for Engine3 and the licenses of the other code concerned,
--provided that you include the source code of that other code when
--and as the GNU LGPL requires distribution of source code.

--Note that people who make modified versions of Engine3 are not obligated
--to grant this special exception for their modified versions;
--it is their choice whether to do so. The GNU Lesser General Public License
--gives permission to release a modified version without this exception;
--this exception also makes it possible to release a modified version
--which carries forward this exception.

-- Support quick check of syntax from cmd line
if Object == nil and arg ~= nil then
		Object = { }
		function Object:new(init)
				return init
		end
end

ServerEventAutomation = Object:new {
	vebose = false,
	syntax_version = 3,
	config = nil
}

function ServerEventAutomation:playerLoggedIn(pPlayer)
	if (pPlayer == nil) then
		return
	end
	self:logPlayerEvent(pPlayer, "playerLoggedIn")

	-- Are we configured?
	if self.config == nil then
		return
	end

	self:sendEventEmails(pPlayer, "playerLoggedIn")

	if self.config.surveys ~= nil then
		self:scheduleSurvey(pPlayer, getRandomNumber(5, 10), "playerLoggedIn")
	end
end

function ServerEventAutomation:playerLoggedOut(pPlayer)
	if (pPlayer == nil) then
		return
	end
	self:logPlayerEvent(pPlayer, "playerLoggedOut")
end

function ServerEventAutomation:sendEventEmails(pPlayer, source_event)
	if (pPlayer == nil) then
		return
	end

	-- Is email configured?
	if self.config.emails == nil then
		return
	end

	local now = getTimestamp()

	for email_id, email in pairs(self.config.emails) do
		if (email.start_time == nil or now >= email.start_time) and (email.end_time == nil or now <= email.end_time) then
			if not self:getEmailSent(pPlayer, email) then
				if email.target == nil or email.target(self, pPlayer, email) then
						self:sendEventEmail(pPlayer, email)
						self:logPlayerEvent(pPlayer, "sentEventEmail:" .. email_id)
						if email.after_send ~= nil then
								email.after_send(self, pPlayer, email)
						end
						self:setEmailSent(pPlayer, email)
				else
						self:logPlayerEvent(pPlayer, "filteredFromEventEmail:" .. email_id)
				end
			else
				if self.verbose then
					self:logPlayerEvent(pPlayer, "emailAlreadySent:" .. email_id)
				end
			end
		else
			if self.verbose then
				self:logEvent("email " .. email_id .. " is not eligible to send, now = " .. now .. " email.start_time = " .. email.start_time .. " email.end_time = " .. email.end_time)
			end
		end
	end
end

function ServerEventAutomation:sendEventEmail(pPlayer, email)
	local firstName = CreatureObject(pPlayer):getFirstName()
	local from = email.sender
	local subject = email.subject
	local body = email.body

	if from == nil then
		from = "Server Event System"
	end

	if subject == nil then
		subject = "New Server Event"
	end

	if body == nil then
		self:logPlayerEvent(pPlayer, "invalidConfiguration, body missing")
		return
	end

	body = string.gsub(body, "%%firstname%%", firstName)

	sendMail(from, subject, body, firstName)
end

function ServerEventAutomation:sendSurveys(pPlayer, source_event)
	if (pPlayer == nil) then
		return
	end

	-- Are surveys configured?
	if self.config.surveys == nil then
		return
	end

	local now = getTimestamp()

	for survey_id, survey in pairs(self.config.surveys) do
		if (survey.start_time == nil or now >= survey.start_time) and (survey.end_time == nil or now <= survey.end_time) then
			if not self:getSurveySent(pPlayer, survey) then
				if survey.target == nil or survey.target(self, pPlayer, survey) then
						self:sendSurvey(pPlayer, survey)
						if survey.after_send ~= nil then
								survey.after_send(self, pPlayer, survey)
						end
				else
						self:logPlayerEvent(pPlayer, "filteredFromSurvey:" .. survey_id)
				end
			else
				if self.verbose then
					self:logPlayerEvent(pPlayer, "surveyAlreadySent:" .. survey_id)
				end
			end
		else
			if self.verbose then
				self:logEvent("survey " .. survey_id .. " is not eligible to send, now = " .. now .. " survey.start_time = " .. survey.start_time .. " survey.end_time = " .. survey.end_time)
			end
		end
	end
end

function ServerEventAutomation:sendSurvey(pPlayer, survey)
	local firstName = CreatureObject(pPlayer):getFirstName()
	local title = survey.title
	local body = survey.body

	if title == nil then
		title = "In-Game Survey"
	end

	if body == nil then
		self:logPlayerEvent(pPlayer, "invalidConfiguration, body missing")
		return
	end

	if survey.options == nil then
		self:logPlayerEvent(pPlayer, "invalidConfiguration, options missing")
		return
	end

	body = string.gsub(body, "%%firstname%%", firstName)

	local sui = SuiListBox.new("ServerEventAutomation", "handleSurveyResponse")
	sui.setProperty("", "Size", survey.size or "500,250")
	sui.setTargetNetworkId(SceneObject(pPlayer):getObjectID())
	sui.setTitle(title)
	sui.setPrompt(body)
	sui.setStoredData("survey_id", survey.id)
	sui.setStoredData("start_tm", getTimestamp())

	options = self:shuffleOptions(survey.options)

	for i = 1, #options, 1 do
		sui.add(options[i][1], options[i][2])
	end

	self:logPlayerEvent(pPlayer, "Sending survey " .. survey.id)

	sui.sendTo(pPlayer)
end

function ServerEventAutomation:shuffleOptions(array)
    local arrayCount = #array
    for i = arrayCount, 2, -1 do
        local j = getRandomNumber(1, i)
        array[i], array[j] = array[j], array[i]
    end
    return array
end

function ServerEventAutomation:handleSurveyResponse(pPlayer, pSui, eventIndex, args)
	local cancelPressed = (eventIndex == 1)

	local pPageData = LuaSuiBoxPage(pSui):getSuiPageData()

	if (pPageData == nil) then
		self:logPlayerEvent(pPlayer, "nil pPageData")
		return
	end

	local suiPageData = LuaSuiPageData(pPageData)
	local survey_id = suiPageData:getStoredData("survey_id") or "unknown"
	local start_tm = suiPageData:getStoredData("start_tm") or getTimestamp()
	local delta = getTimestamp() - start_tm
	local response = suiPageData:getStoredData(tostring(args))
	local survey = self.config.surveys[survey_id]

	if cancelPressed then
		self:logPlayerEvent(pPlayer, survey_id .. ": Cancelled Survey")
		self:scheduleSurvey(pPlayer, getRandomNumber(60, 180), "user_cancelled")
		return
	end

	if tonumber(args) < 0 then
		self:logPlayerEvent(pPlayer, survey_id .. ": Ignored Survey")
		self:scheduleSurvey(pPlayer, getRandomNumber(60, 180), "user_ignored")
		return
	end

	local accountID = 0
	local pGhost = CreatureObject(pPlayer):getPlayerObject()

	if pGhost == nil then
		self:logPlayerEvent(pPlayer, "ServerEventAutomation:handleSurveyResponse missing ghost?")
	else
		accountID = PlayerObject(pGhost):getAccountID()
	end

	self:logPlayerEvent(pPlayer, survey_id .. ": Selected " .. response .. " after " .. delta .. " seconds.")

	local result = '{"survey_id":"' .. survey_id .. '"'
	   .. ',"account_id":' .. accountID
	   .. ',"character_oid":' .. CreatureObject(pPlayer):getObjectID()
	   .. ',"response":"' .. response .. '"'
	   .. ',"timestamp":"' .. getFormattedTime() .. '"'
	   .. ',"time":' .. getTimestamp()
	   .. ',"answer_seconds":' .. delta
	   .. "}\n"

	local fh = io.open("log/SurveyAnswers.log", "a+")
	fh:write(result)
	fh:flush()
	fh:close()

	self:logEvent("Finished survey " .. survey.id .. " title: " .. survey.title)

	self:setSurveySent(pPlayer, survey)
end

function ServerEventAutomation:scheduleSurvey(pPlayer, when, reason)
	if pPlayer == nil then
		self:logEvent("scheduleSurvey called with nil player")
		return
	end

	self:logPlayerEvent(pPlayer, "scheduleSurvey " .. tostring(when))

	createEvent(when * 1000, "ServerEventAutomation", "sendSurveys", pPlayer, reason)
end

function ServerEventAutomation:getEmailSentKey(pPlayer, item)
	return CreatureObject(pPlayer):getObjectID() .. ":ServerEventAutomation:" .. item.namespace .. ":" .. item.id
end

function ServerEventAutomation:setEmailSent(pPlayer, item)
	setQuestStatus(self:getEmailSentKey(pPlayer, item), getTimestamp())
end

function ServerEventAutomation:getEmailSent(pPlayer, item)
	local when = getQuestStatus(self:getEmailSentKey(pPlayer, item))

	if when == nil then
		return false
	end

	return true
end

function ServerEventAutomation:getSurveySentKey(pPlayer, item)
	if pPlayer == nil then
		self:logEvent("ERROR: ServerEventAutomation:getSurveySentKey pPlayer is nil")
		return "unknownPlayer"
	end

	local pGhost = CreatureObject(pPlayer):getPlayerObject()

	if pGhost == nil then
		self:logPlayerEvent(pPlayer, "ServerEventAutomation:getSurveySentKey missing ghost?")
		return "missingGhost"
	end

	return "accountID:" .. PlayerObject(pGhost):getAccountID() .. ":ServerEventAutomation:" .. item.namespace .. ":" .. item.id
end

function ServerEventAutomation:setSurveySent(pPlayer, item)
	setQuestStatus(self:getSurveySentKey(pPlayer, item), getTimestamp())
end

function ServerEventAutomation:getSurveySent(pPlayer, item)
	local when = getQuestStatus(self:getSurveySentKey(pPlayer, item))

	if when == nil then
		return false
	end

	return true
end

function ServerEventAutomation:logEvent(what)
	local fh = io.open("log/ServerEventAutomation.log", "a+")
	fh:write(string.format("%s [ServerEventAutomation] %s\n", getFormattedTime(), what))
	fh:flush()
	fh:close()
end

function ServerEventAutomation:logPlayerEvent(pPlayer, what)
	if pPlayer == nil then
		self:logEvent("NIL PLAYER: " .. what)
		return
	end

	local creature = CreatureObject(pPlayer)
	local pGhost = CreatureObject(pPlayer):getPlayerObject()

	if pGhost == nil then
		self:logEvent("NIL GHOST ON OID " .. creature:getObjectID() .. ": " .. what)
		return
	end

	local ghost = PlayerObject(pGhost)

	self:logEvent(string.format(
		"playerEvent %s (account_id: %s, oid: %d, %s) on %s at %s %s - %s",
		creature:getFirstName(),
		ghost:getAccountID(),
		creature:getObjectID(),
		ghost:getPlayedTimeString(),
		creature:getZoneName(),
		math.floor(creature:getWorldPositionX()),
		math.floor(creature:getWorldPositionY()),
		what
	))
end

function ServerEventAutomation:init(config_file)
	local seaconfig = loadfile(config_file)

	if seaconfig == nil then
		return
	end

	seaconfig()

	if self.config == nil then
		self:logEvent("WARNING: Configuration error, didn't set ServerEventAutomation.config")
		return
	end

	-- Check to see if the config is compatiable with the code
	if self.config.syntax_version == nil or self.config.syntax_version > self.syntax_version then
		self:logEvent("WARNING: Configuartion syntax_version doesn't match code syntax_version(" .. self.syntax_version .. "), please verify feature support.")
		self.config = nil
		return
	end

	local now = getTimestamp()

	if self.config.emails ~= nil then
		for email_id, email in pairs(self.config.emails) do
			if (email.end_time ~= nil and now > email.end_time) then
				self:logEvent("Discarding email " .. email_id .. " because end_time is in the past.")
				self.config.emails[email_id] = nil
			else
				self.config.emails[email_id].id = email_id
				self.config.emails[email_id].namespace = "email"
			end
		end
	end

	if self.config.surveys ~= nil then
		for survey_id, survey in pairs(self.config.surveys) do
			if (survey.end_time ~= nil and now > survey.end_time) then
				self:logEvent("Discarding survey " .. survey_id .. " because end_time is in the past.")
				self.config.surveys[survey_id] = nil
			else
				self.config.surveys[survey_id].id = survey_id
				self.config.surveys[survey_id].namespace = "survey"
			end
		end
	end

	if self.config.verbose ~= nil and self.config.verbose then
		self.verbose = true
		self:logEvent("Loaded config from " .. config_file)
	end
end

ServerEventAutomation:init("conf/ServerEventAutomationConfig.lua")

return ServerEventAutomation
