/*
MySQL Data Transfer
Source Host: 192.168.1.153
Source Database: swgemu
Target Host: 192.168.1.153
Target Database: swgemu
Date: 02/12/2008 6:00:54 PM
*/

SET FOREIGN_KEY_CHECKS=0;
-- ----------------------------
-- Table structure for knowledgebase
-- ----------------------------
CREATE TABLE `knowledgebase` (
  `article_id` int(11) NOT NULL auto_increment,
  `article_title` varchar(45) NOT NULL default 'Empty Title',
  `article_text` varchar(255) NOT NULL default 'Empty Body',
  PRIMARY KEY  USING BTREE (`article_id`)
) ENGINE=MyISAM AUTO_INCREMENT=3 DEFAULT CHARSET=latin1;

-- ----------------------------
-- Records 
-- ----------------------------
INSERT INTO `knowledgebase` VALUES ('1', 'Test Title 1', 'Empty Body');
INSERT INTO `knowledgebase` VALUES ('2', 'Test Title 2', 'Empty Body');
