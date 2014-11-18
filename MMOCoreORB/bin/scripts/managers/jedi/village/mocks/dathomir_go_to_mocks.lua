local DathomirGoTo = require("managers.jedi.village.dathomir_go_to")

local realStart

local DathomirGoToMocks = DathomirGoTo
DathomirGoToMocks.mocks = {}

function DathomirGoToMocks.mocks.setup()
	realStart = DathomirGoTo.start
end

function DathomirGoToMocks.mocks.teardown()
	DathomirGoTo.start = realStart
end

function DathomirGoToMocks.mocks.before_each()
	DathomirGoTo.start = spy.new(function() end)
end

function DathomirGoToMocks.mocks.after_each()
end

return DathomirGoToMocks
