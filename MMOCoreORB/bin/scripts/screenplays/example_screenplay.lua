ExampleScreenPlay = ScreenPlay:new {
	numberOfActs = 1,
}

--True here tells the server to load this screenplay at server load. False tells it to wait until explicitly started.
registerScreenPlay("ExampleScreenPlay", true)

--This gets executed automatically when the screenplay is started
function ExampleScreenPlay:start()
	self:spawnMobiles()
end

--Put all the initial spawning of mobiles in a nice method like this.
function ExampleScreenPlay:spawnMobiles()
end