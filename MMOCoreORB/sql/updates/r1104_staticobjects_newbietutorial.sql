ALTER TABLE `staticobjects` ADD `client` TINYINT( 1 ) NOT NULL DEFAULT '1';

INSERT INTO `staticobjects` ( `zoneid` , `objectid` , `parentid` , `file` , `oX` , `oY` , `oZ` , `oW` , `X` , `Z` , `Y` , `type` , `client` ) VALUES ('42', '2203318222974', '0', 'object/building/general/shared_newbie_hall_skipped.iff', '0', '0', '0', '1', '500', '0', '500', '512', '0');
INSERT INTO `staticobjects` ( `zoneid` , `objectid` , `parentid` , `file` , `oX` , `oY` , `oZ` , `oW` , `X` , `Z` , `Y` , `type` , `client` ) VALUES ('42', '2203318222975', '2203318222974', 'object/cell/shared_cell.iff', '0', '0', '0', '1', '0', '0', '0', '0', '0');

