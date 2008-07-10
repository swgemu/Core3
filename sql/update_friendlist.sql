/*
MySQL Data Transfer
Source Host: localhost
Source Database: swgemu
Target Host: localhost
Target Database: swgemu
Date: 10.07.2008 20:35:37
*/


DROP TABLE IF EXISTS friendlist;

SET FOREIGN_KEY_CHECKS=0;
-- ----------------------------
-- Table structure for friendlist
-- ----------------------------
CREATE TABLE `friendlist` (
  `character_id` mediumint(8) unsigned NOT NULL,
  `firstname` varchar(15) NOT NULL,
  `surname` varchar(20) default NULL,
  `friend_id` mediumint(8) NOT NULL,
  `friend_firstname` varchar(15) NOT NULL,
  `friend_surname` varchar(20) default NULL,
  `friend_galaxy` varchar(50) NOT NULL,
  `ix` int(10) unsigned NOT NULL auto_increment,
  PRIMARY KEY  (`ix`),
  KEY `char_id_ix` (`character_id`),
  KEY `firstname_ix` (`firstname`),
  KEY `friend_id` (`friend_id`),
  KEY `friend_firstname_ix` (`friend_firstname`),
  KEY `friend_galaxy_ix` (`friend_galaxy`)
) ENGINE=MyISAM AUTO_INCREMENT=222 DEFAULT CHARSET=latin1;

-- ----------------------------
-- Records 
-- ----------------------------
