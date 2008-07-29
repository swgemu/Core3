/*
MySQL Data Transfer
Source Host: localhost
Source Database: swgemu
Target Host: localhost
Target Database: swgemu
Date: 15.07.2008 14:29:29
*/

DROP TABLE IF EXISTS ignorelist;

SET FOREIGN_KEY_CHECKS=0;
-- ----------------------------
-- Table structure for ignorelist
-- ----------------------------
CREATE TABLE `ignorelist` (
  `character_id` mediumint(8) unsigned NOT NULL,
  `firstname` varchar(15) NOT NULL,
  `surname` varchar(20) default NULL,
  `ignore_id` mediumint(8) NOT NULL,
  `ignore_firstname` varchar(15) NOT NULL,
  `ignore_surname` varchar(20) default NULL,
  `ignore_galaxy` varchar(50) NOT NULL,
  `ix` int(10) unsigned NOT NULL auto_increment,
  PRIMARY KEY  (`ix`),
  KEY `char_id_ix` (`character_id`),
  KEY `ignorename_ix` (`firstname`),
  KEY `ignore_id` (`ignore_id`),
  KEY `ignore_firstname_ix` (`ignore_firstname`),
  KEY `ignore_galaxy_ix` (`ignore_galaxy`)
) ENGINE=MyISAM AUTO_INCREMENT=279 DEFAULT CHARSET=latin1;

-- ----------------------------
-- Records 
-- ----------------------------
