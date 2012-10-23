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


object_mobile_vendor_ithorian_male = object_mobile_vendor_shared_ithorian_male:new {

	templateType = VENDORCREATURE,
	optionsBitmask = 386,
	pvpStatusBitmask = 0,

	objectMenuComponent = {"cpp", "VendorMenuComponent"},
	dataObjectComponent = "VendorDataComponent",	
	containerComponent = {"cpp", "VendorContainerComponent"},
	zoneComponent = "VendorZoneComponent",

	noTrade = 1,

	hair = "",
	clothing = {"Ithorian1","Ithorian2","Ithorian3","Ithorian4","Ithorian5","Ithorian6","Ithorian7","Ithorian8","Ithorian9","Ithorian10",
			"Ithorian11","Ithorian12","Ithorian13","Ithorian14","Ithorian15","Ithorian16","Ithorian17","Ithorian18","Ithorian19","Ithorian20",
			"Ithorian21","Ithorian22","Ithorian23","Ithorian24","Ithorian25","Ithorian26","Ithorian27","Ithorian28","Ithorian29","Ithorian30",
			"Ithorian31","Ithorian32","Ithorian33","Ithorian34","Ithorian35","Ithorian36","Ithorian37","Ithorian38","Ithorian39","Ithorian40",
			"Ithorian41","Ithorian42","Ithorian43","Ithorian44","Ithorian45","Ithorian46","Ithorian47","Ithorian48","Ithorian49","Ithorian50",
			"Ithorian51","Ithorian52","Ithorian53","Ithorian54","Ithorian55","Ithorian56","Ithorian57","Ithorian58","Ithorian59","Ithorian60",
			"Ithorian61","Ithorian62","Ithorian63","Ithorian64","Ithorian65","Ithorian66","Ithorian67","Ithorian68","Ithorian69","Ithorian70",
			"Ithorian71","Ithorian72","Ithorian73","Ithorian74","Ithorian75","Ithorian76","Ithorian77","Ithorian78","Ithorian79","Ithorian80",
			"Ithorian81","Ithorian82","Ithorian83","Ithorian84","Ithorian85","Ithorian86","Ithorian87","Ithorian88","Ithorian89","Ithorian90",
			"Ithorian91","Ithorian92","Ithorian93","Ithorian94","Ithorian95","Ithorian96","Ithorian97","Ithorian98","Ithorian99","Ithorian100",
			"Ithorian101","Ithorian102","Ithorian103","Ithorian104","Ithorian105","Ithorian106","Ithorian107","Ithorian108","Ithorian109","Ithorian110",
			"Ithorian111","Ithorian112","Ithorian113","Ithorian114","Ithorian115","Ithorian116","Ithorian117","Ithorian118","Ithorian119","Ithorian120",
			"Ithorian121","Ithorian122","Ithorian123","Ithorian124","Ithorian125","Ithorian126","Ithorian127","Ithorian128","Ithorian129","Ithorian130",
			"Ithorian131","Ithorian132","Ithorian133","Ithorian134","Ithorian135","Ithorian136","Ithorian137","Ithorian138","Ithorian139","Ithorian140",
			"Ithorian141","Ithorian142","Ithorian143","Ithorian144","Ithorian145","Ithorian146","Ithorian147","Ithorian148","Ithorian149","Ithorian150",
			"Ithorian151","Ithorian152","Ithorian153","Ithorian154","Ithorian155","Ithorian156","Ithorian157","Ithorian158","Ithorian159","Ithorian160",
			"Ithorian161","Ithorian162","Ithorian163","Ithorian164","Ithorian165","Ithorian166","Ithorian167","Ithorian168","Ithorian169","Ithorian170",
			"Ithorian171","Ithorian172","Ithorian173","Ithorian174","Ithorian175","Ithorian176","Ithorian177","Ithorian178","Ithorian179","Ithorian180",
			"Ithorian181","Ithorian182","Ithorian183","Ithorian184","Ithorian185","Ithorian186","Ithorian187","Ithorian188","Ithorian189","Ithorian190",
			"Ithorian191","Ithorian192","Ithorian193","Ithorian194","Ithorian195","Ithorian196","Ithorian197","Ithorian198","Ithorian199","Ithorian200",
			"Ithorian201","Ithorian202","Ithorian203","Ithorian204","Ithorian205","Ithorian206","Ithorian207","Ithorian208","Ithorian209","Ithorian210",
			"Ithorian211","Ithorian212","Ithorian213","Ithorian214","Ithorian215","Ithorian216","Ithorian217","Ithorian218","Ithorian219","Ithorian220",
			"Ithorian221","Ithorian222","Ithorian223","Ithorian224","Ithorian225","Ithorian226","Ithorian227","Ithorian228","Ithorian229","Ithorian230",
			"Ithorian231","Ithorian232","Ithorian233","Ithorian234","Ithorian235","Ithorian236","Ithorian237","Ithorian238","Ithorian239","Ithorian240",
			"Ithorian241","Ithorian242","Ithorian243","Ithorian244","Ithorian245","Ithorian246","Ithorian247","Ithorian248","Ithorian249","Ithorian250",
			"Ithorian251","Ithorian252","Ithorian253","Ithorian254","Ithorian255","Ithorian256","Ithorian257","Ithorian258","Ithorian259","Ithorian260",
			"Ithorian261","Ithorian262","Ithorian263","Ithorian264","Ithorian265","Ithorian266","Ithorian267","Ithorian268","Ithorian269","Ithorian270",
			"Ithorian271","Ithorian272","Ithorian273","Ithorian274","Ithorian275","Ithorian276","Ithorian277","Ithorian278","Ithorian279","Ithorian280",
			"Ithorian281","Ithorian282","Ithorian283","Ithorian284","Ithorian285","Ithorian286","Ithorian287","Ithorian288","Ithorian289","Ithorian290",
			"Ithorian291","Ithorian292","Ithorian293","Ithorian294"}

}

ObjectTemplates:addTemplate(object_mobile_vendor_ithorian_male, "object/mobile/vendor/ithorian_male.iff")
