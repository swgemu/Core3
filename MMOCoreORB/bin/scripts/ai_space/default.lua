idleDefault = {
	{id="3154429038",	name="SequenceSpace",	pid="none"}}
addAiTemplate("idleDefault", idleDefault)

moveDefault = {
	{id="368441587",	name="SequenceSpace",	pid="none"}}
addAiTemplate("moveDefault", moveDefault)

rootDefault = {
	{id="1234597753",	name="SequenceSpace",	pid="none"},
	{id="1729558672",	name="TreeSocketSpace",	pid="1234597753",	args={slot=MOVE}},
	{id="869798738",	name="TreeSocketSpace",	pid="1234597753",	args={slot=IDLE}}}
addAiTemplate("rootDefault", rootDefault)

