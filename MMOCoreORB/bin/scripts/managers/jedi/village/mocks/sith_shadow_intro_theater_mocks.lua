local SithShadowIntroTheater = require("managers.jedi.village.sith_shadow_intro_theater")

local realStart

local SithShadowIntroTheaterMocks = SithShadowIntroTheater
SithShadowIntroTheaterMocks.mocks = {}

function SithShadowIntroTheaterMocks.mocks.setup()
	realStart = SithShadowIntroTheater.start
end

function SithShadowIntroTheaterMocks.mocks.teardown()
	SithShadowIntroTheater.start = realStart
end

function SithShadowIntroTheaterMocks.mocks.before_each()
	SithShadowIntroTheater.start = spy.new(function() end)
end

function SithShadowIntroTheaterMocks.mocks.after_each()
end

return SithShadowIntroTheaterMocks
