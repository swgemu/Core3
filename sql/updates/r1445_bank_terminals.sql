/*
SQLyog Community Edition- MySQL GUI v6.56
MySQL - 5.0.67-0ubuntu6 : Database - swgemu
*********************************************************************
*/

/*!40101 SET NAMES utf8 */;

/*!40101 SET SQL_MODE=''*/;

/*!40014 SET @OLD_FOREIGN_KEY_CHECKS=@@FOREIGN_KEY_CHECKS, FOREIGN_KEY_CHECKS=0 */;
/*!40101 SET @OLD_SQL_MODE=@@SQL_MODE, SQL_MODE='NO_AUTO_VALUE_ON_ZERO' */;

USE `swgemu`;

/*Table structure for table `terminals` */

DROP TABLE IF EXISTS `terminals`;

CREATE TABLE `terminals` (
  `id` int(11) NOT NULL auto_increment,
  `parentid` bigint(20) NOT NULL default '0',
  `type` tinyint(4) NOT NULL default '0',
  `oX` float NOT NULL default '0',
  `oZ` float NOT NULL default '0',
  `oY` float NOT NULL default '0',
  `oW` float NOT NULL default '0',
  `X` float NOT NULL default '0',
  `Z` float NOT NULL default '0',
  `Y` float NOT NULL,
  `zoneid` tinyint(4) NOT NULL default '0',
  `attributes` text NOT NULL,
  PRIMARY KEY  (`id`)
) ENGINE=MyISAM AUTO_INCREMENT=260 DEFAULT CHARSET=latin1;

/*Data for the table `terminals` */

insert  into `terminals`(`id`,`parentid`,`type`,`oX`,`oZ`,`oY`,`oW`,`X`,`Z`,`Y`,`zoneid`,`attributes`) values (1,1106502,5,0,0,1,0,1,-0.05,-1,8,'');
insert  into `terminals`(`id`,`parentid`,`type`,`oX`,`oZ`,`oY`,`oW`,`X`,`Z`,`Y`,`zoneid`,`attributes`) values (2,1106502,5,0,0,0,1,1,-0.05,2,8,'');
insert  into `terminals`(`id`,`parentid`,`type`,`oX`,`oZ`,`oY`,`oW`,`X`,`Z`,`Y`,`zoneid`,`attributes`) values (3,1590893,5,0,0,-1,0,0,-0.378,-0.5,8,'');
insert  into `terminals`(`id`,`parentid`,`type`,`oX`,`oZ`,`oY`,`oW`,`X`,`Z`,`Y`,`zoneid`,`attributes`) values (5,1105881,5,0,0,0,1,1,-0.05,2,8,'');
insert  into `terminals`(`id`,`parentid`,`type`,`oX`,`oZ`,`oY`,`oW`,`X`,`Z`,`Y`,`zoneid`,`attributes`) values (6,1105881,5,0,0,1,0,1,-0.05,-1,8,'');
insert  into `terminals`(`id`,`parentid`,`type`,`oX`,`oZ`,`oY`,`oW`,`X`,`Z`,`Y`,`zoneid`,`attributes`) values (7,3565796,5,0,0,0,1,1,-0.05,2,8,'');
insert  into `terminals`(`id`,`parentid`,`type`,`oX`,`oZ`,`oY`,`oW`,`X`,`Z`,`Y`,`zoneid`,`attributes`) values (8,3565796,5,0,0,1,0,1,-0.05,-1,8,'');
insert  into `terminals`(`id`,`parentid`,`type`,`oX`,`oZ`,`oY`,`oW`,`X`,`Z`,`Y`,`zoneid`,`attributes`) values (9,1254763,5,0,0,0,1,1,-0.05,2,8,'');
insert  into `terminals`(`id`,`parentid`,`type`,`oX`,`oZ`,`oY`,`oW`,`X`,`Z`,`Y`,`zoneid`,`attributes`) values (10,1254763,5,0,0,1,0,1,-0.05,-1,8,'');
insert  into `terminals`(`id`,`parentid`,`type`,`oX`,`oZ`,`oY`,`oW`,`X`,`Z`,`Y`,`zoneid`,`attributes`) values (11,1233040,5,0,0,0,1,1,-0.05,2,8,'');
insert  into `terminals`(`id`,`parentid`,`type`,`oX`,`oZ`,`oY`,`oW`,`X`,`Z`,`Y`,`zoneid`,`attributes`) values (12,1233040,5,0,0,1,0,1,-0.05,-1,8,'');
insert  into `terminals`(`id`,`parentid`,`type`,`oX`,`oZ`,`oY`,`oW`,`X`,`Z`,`Y`,`zoneid`,`attributes`) values (13,1528389,5,0,0,-1,0,0,-0.378,-0.5,8,'');
insert  into `terminals`(`id`,`parentid`,`type`,`oX`,`oZ`,`oY`,`oW`,`X`,`Z`,`Y`,`zoneid`,`attributes`) values (14,1400866,5,0,0,-1,0,0,-0.378,-0.5,8,'');
insert  into `terminals`(`id`,`parentid`,`type`,`oX`,`oZ`,`oY`,`oW`,`X`,`Z`,`Y`,`zoneid`,`attributes`) values (15,1697352,5,0,0,0,1,1,-0.05,2,5,'');
insert  into `terminals`(`id`,`parentid`,`type`,`oX`,`oZ`,`oY`,`oW`,`X`,`Z`,`Y`,`zoneid`,`attributes`) values (16,1697352,5,0,0,1,0,1,-0.05,-1,5,'');
insert  into `terminals`(`id`,`parentid`,`type`,`oX`,`oZ`,`oY`,`oW`,`X`,`Z`,`Y`,`zoneid`,`attributes`) values (17,474325,5,0,0,0,1,1,-0.05,2,5,'');
insert  into `terminals`(`id`,`parentid`,`type`,`oX`,`oZ`,`oY`,`oW`,`X`,`Z`,`Y`,`zoneid`,`attributes`) values (18,474325,5,0,0,1,0,1,-0.05,-1,5,'');
insert  into `terminals`(`id`,`parentid`,`type`,`oX`,`oZ`,`oY`,`oW`,`X`,`Z`,`Y`,`zoneid`,`attributes`) values (19,1717560,5,0,0,0,1,1,-0.05,2,5,'');
insert  into `terminals`(`id`,`parentid`,`type`,`oX`,`oZ`,`oY`,`oW`,`X`,`Z`,`Y`,`zoneid`,`attributes`) values (20,1717560,5,0,0,1,0,1,-0.05,-1,5,'');
insert  into `terminals`(`id`,`parentid`,`type`,`oX`,`oZ`,`oY`,`oW`,`X`,`Z`,`Y`,`zoneid`,`attributes`) values (21,1650613,5,0,0,0,1,1,-0.05,2,5,'');
insert  into `terminals`(`id`,`parentid`,`type`,`oX`,`oZ`,`oY`,`oW`,`X`,`Z`,`Y`,`zoneid`,`attributes`) values (22,1650613,5,0,0,1,0,1,-0.05,-1,5,'');
insert  into `terminals`(`id`,`parentid`,`type`,`oX`,`oZ`,`oY`,`oW`,`X`,`Z`,`Y`,`zoneid`,`attributes`) values (23,1741514,5,0,0,0,1,1,-0.05,2,5,'');
insert  into `terminals`(`id`,`parentid`,`type`,`oX`,`oZ`,`oY`,`oW`,`X`,`Z`,`Y`,`zoneid`,`attributes`) values (24,1741514,5,0,0,1,0,1,-0.05,-1,5,'');
insert  into `terminals`(`id`,`parentid`,`type`,`oX`,`oZ`,`oY`,`oW`,`X`,`Z`,`Y`,`zoneid`,`attributes`) values (25,3605960,5,0,0,0,1,-4,0.125,-6,3,'');
insert  into `terminals`(`id`,`parentid`,`type`,`oX`,`oZ`,`oY`,`oW`,`X`,`Z`,`Y`,`zoneid`,`attributes`) values (26,4635543,5,0,0,1,0,1,-0.05,-1,6,'');
insert  into `terminals`(`id`,`parentid`,`type`,`oX`,`oZ`,`oY`,`oW`,`X`,`Z`,`Y`,`zoneid`,`attributes`) values (32,8615441,5,0,0,0,1,0,0.125,-6.5,4,'');
insert  into `terminals`(`id`,`parentid`,`type`,`oX`,`oZ`,`oY`,`oW`,`X`,`Z`,`Y`,`zoneid`,`attributes`) values (27,4635543,5,0,0,0,1,1,-0.05,2,6,'');
insert  into `terminals`(`id`,`parentid`,`type`,`oX`,`oZ`,`oY`,`oW`,`X`,`Z`,`Y`,`zoneid`,`attributes`) values (28,4695369,5,0,0,0,1,1,-0.05,2,6,'');
insert  into `terminals`(`id`,`parentid`,`type`,`oX`,`oZ`,`oY`,`oW`,`X`,`Z`,`Y`,`zoneid`,`attributes`) values (29,4695369,5,0,0,1,0,1,-0.05,-1,6,'');
insert  into `terminals`(`id`,`parentid`,`type`,`oX`,`oZ`,`oY`,`oW`,`X`,`Z`,`Y`,`zoneid`,`attributes`) values (30,2745625,5,0,0,-1,0,0,-0.378,-0.5,4,'');
insert  into `terminals`(`id`,`parentid`,`type`,`oX`,`oZ`,`oY`,`oW`,`X`,`Z`,`Y`,`zoneid`,`attributes`) values (31,6705357,5,0,0,0,1,0,0.125,-6.5,3,'');
insert  into `terminals`(`id`,`parentid`,`type`,`oX`,`oZ`,`oY`,`oW`,`X`,`Z`,`Y`,`zoneid`,`attributes`) values (33,4505608,5,0,0,0,1,0,0.125,-6.5,6,'');
insert  into `terminals`(`id`,`parentid`,`type`,`oX`,`oZ`,`oY`,`oW`,`X`,`Z`,`Y`,`zoneid`,`attributes`) values (34,4885426,5,0,0,0,1,0,0.125,-6.5,1,'');
insert  into `terminals`(`id`,`parentid`,`type`,`oX`,`oZ`,`oY`,`oW`,`X`,`Z`,`Y`,`zoneid`,`attributes`) values (35,1366006,5,0,0,0,1,0,0.125,-6.5,1,'');
insert  into `terminals`(`id`,`parentid`,`type`,`oX`,`oZ`,`oY`,`oW`,`X`,`Z`,`Y`,`zoneid`,`attributes`) values (36,1365995,5,0,0,0,1,0,0.125,-6.5,1,'');
insert  into `terminals`(`id`,`parentid`,`type`,`oX`,`oZ`,`oY`,`oW`,`X`,`Z`,`Y`,`zoneid`,`attributes`) values (37,3175406,5,0,0,0,1,1,-0.05,2,7,'');
insert  into `terminals`(`id`,`parentid`,`type`,`oX`,`oZ`,`oY`,`oW`,`X`,`Z`,`Y`,`zoneid`,`attributes`) values (38,3175406,5,0,0,1,0,1,-0.05,-1,7,'');
insert  into `terminals`(`id`,`parentid`,`type`,`oX`,`oZ`,`oY`,`oW`,`X`,`Z`,`Y`,`zoneid`,`attributes`) values (54,4345392,5,0,0,0,1,1,-0.05,2,0,'');
insert  into `terminals`(`id`,`parentid`,`type`,`oX`,`oZ`,`oY`,`oW`,`X`,`Z`,`Y`,`zoneid`,`attributes`) values (41,4965412,5,0,0,0,1,0,0.125,-6.5,7,'');
insert  into `terminals`(`id`,`parentid`,`type`,`oX`,`oZ`,`oY`,`oW`,`X`,`Z`,`Y`,`zoneid`,`attributes`) values (42,7925459,5,0,0,0,1,-4,0.125,-6,9,'');
insert  into `terminals`(`id`,`parentid`,`type`,`oX`,`oZ`,`oY`,`oW`,`X`,`Z`,`Y`,`zoneid`,`attributes`) values (43,3035596,5,0,0,0,1,0,0.125,-6.5,9,'');
insert  into `terminals`(`id`,`parentid`,`type`,`oX`,`oZ`,`oY`,`oW`,`X`,`Z`,`Y`,`zoneid`,`attributes`) values (44,1392860,5,0,0,0,1,-4,0.125,-6,2,'');
insert  into `terminals`(`id`,`parentid`,`type`,`oX`,`oZ`,`oY`,`oW`,`X`,`Z`,`Y`,`zoneid`,`attributes`) values (45,1392892,5,0,0,0,1,0,0.125,-6.5,2,'');
insert  into `terminals`(`id`,`parentid`,`type`,`oX`,`oZ`,`oY`,`oW`,`X`,`Z`,`Y`,`zoneid`,`attributes`) values (46,1855493,5,0,0,1,0,1,-0.05,-1,0,'');
insert  into `terminals`(`id`,`parentid`,`type`,`oX`,`oZ`,`oY`,`oW`,`X`,`Z`,`Y`,`zoneid`,`attributes`) values (47,1855493,5,0,0,0,1,1,-0.05,2,0,'');
insert  into `terminals`(`id`,`parentid`,`type`,`oX`,`oZ`,`oY`,`oW`,`X`,`Z`,`Y`,`zoneid`,`attributes`) values (48,1935515,5,0,0,1,0,1,-0.05,-1,0,'');
insert  into `terminals`(`id`,`parentid`,`type`,`oX`,`oZ`,`oY`,`oW`,`X`,`Z`,`Y`,`zoneid`,`attributes`) values (49,1935515,5,0,0,0,1,1,-0.05,2,0,'');
insert  into `terminals`(`id`,`parentid`,`type`,`oX`,`oZ`,`oY`,`oW`,`X`,`Z`,`Y`,`zoneid`,`attributes`) values (65,1935515,6,0,0,-0.7,0.7,8,0.08,3,0,'');
insert  into `terminals`(`id`,`parentid`,`type`,`oX`,`oZ`,`oY`,`oW`,`X`,`Z`,`Y`,`zoneid`,`attributes`) values (56,4265614,5,0,0,0,1,1,-0.05,2,7,'');
insert  into `terminals`(`id`,`parentid`,`type`,`oX`,`oZ`,`oY`,`oW`,`X`,`Z`,`Y`,`zoneid`,`attributes`) values (55,4345392,5,0,0,1,0,1,-0.05,-1,0,'');
insert  into `terminals`(`id`,`parentid`,`type`,`oX`,`oZ`,`oY`,`oW`,`X`,`Z`,`Y`,`zoneid`,`attributes`) values (57,4265614,5,0,0,1,0,1,-0.05,-1,7,'');
insert  into `terminals`(`id`,`parentid`,`type`,`oX`,`oZ`,`oY`,`oW`,`X`,`Z`,`Y`,`zoneid`,`attributes`) values (64,1855493,6,0,0,-0.7,0.7,8,0.08,3,0,'');
insert  into `terminals`(`id`,`parentid`,`type`,`oX`,`oZ`,`oY`,`oW`,`X`,`Z`,`Y`,`zoneid`,`attributes`) values (60,3005428,5,0,0,0,1,1,-0.05,2,0,'');
insert  into `terminals`(`id`,`parentid`,`type`,`oX`,`oZ`,`oY`,`oW`,`X`,`Z`,`Y`,`zoneid`,`attributes`) values (61,3005428,5,0,0,1,0,1,-0.05,-1,0,'');
insert  into `terminals`(`id`,`parentid`,`type`,`oX`,`oZ`,`oY`,`oW`,`X`,`Z`,`Y`,`zoneid`,`attributes`) values (62,2365903,5,0,0,1,0,1,-0.05,-1,0,'');
insert  into `terminals`(`id`,`parentid`,`type`,`oX`,`oZ`,`oY`,`oW`,`X`,`Z`,`Y`,`zoneid`,`attributes`) values (63,2365903,5,0,0,0,1,1,-0.05,2,0,'');
insert  into `terminals`(`id`,`parentid`,`type`,`oX`,`oZ`,`oY`,`oW`,`X`,`Z`,`Y`,`zoneid`,`attributes`) values (66,2365903,6,0,0,-0.7,0.7,8,0.08,3,0,'');
insert  into `terminals`(`id`,`parentid`,`type`,`oX`,`oZ`,`oY`,`oW`,`X`,`Z`,`Y`,`zoneid`,`attributes`) values (67,3005428,6,0,0,-0.7,0.7,8,0.08,3,0,'');
insert  into `terminals`(`id`,`parentid`,`type`,`oX`,`oZ`,`oY`,`oW`,`X`,`Z`,`Y`,`zoneid`,`attributes`) values (68,4345392,6,0,0,-0.7,0.7,8,0.08,3,0,'');
insert  into `terminals`(`id`,`parentid`,`type`,`oX`,`oZ`,`oY`,`oW`,`X`,`Z`,`Y`,`zoneid`,`attributes`) values (69,474325,6,0,0,-0.7,0.7,8,0.08,3,5,'');
insert  into `terminals`(`id`,`parentid`,`type`,`oX`,`oZ`,`oY`,`oW`,`X`,`Z`,`Y`,`zoneid`,`attributes`) values (70,1650613,6,0,0,-0.7,0.7,8,0.08,3,5,'');
insert  into `terminals`(`id`,`parentid`,`type`,`oX`,`oZ`,`oY`,`oW`,`X`,`Z`,`Y`,`zoneid`,`attributes`) values (71,1697352,6,0,0,-0.7,0.7,8,0.08,3,5,'');
insert  into `terminals`(`id`,`parentid`,`type`,`oX`,`oZ`,`oY`,`oW`,`X`,`Z`,`Y`,`zoneid`,`attributes`) values (72,1717560,6,0,0,-0.7,0.7,8,0.08,3,5,'');
insert  into `terminals`(`id`,`parentid`,`type`,`oX`,`oZ`,`oY`,`oW`,`X`,`Z`,`Y`,`zoneid`,`attributes`) values (73,1741514,6,0,0,-0.7,0.7,8,0.08,3,5,'');
insert  into `terminals`(`id`,`parentid`,`type`,`oX`,`oZ`,`oY`,`oW`,`X`,`Z`,`Y`,`zoneid`,`attributes`) values (74,4635543,6,0,0,-0.7,0.7,8,0.08,3,6,'');
insert  into `terminals`(`id`,`parentid`,`type`,`oX`,`oZ`,`oY`,`oW`,`X`,`Z`,`Y`,`zoneid`,`attributes`) values (75,4695369,6,0,0,-0.7,0.7,8,0.08,3,6,'');
insert  into `terminals`(`id`,`parentid`,`type`,`oX`,`oZ`,`oY`,`oW`,`X`,`Z`,`Y`,`zoneid`,`attributes`) values (76,3175406,6,0,0,-0.7,0.7,8,0.08,3,7,'');
insert  into `terminals`(`id`,`parentid`,`type`,`oX`,`oZ`,`oY`,`oW`,`X`,`Z`,`Y`,`zoneid`,`attributes`) values (77,4265614,6,0,0,-0.7,0.7,8,0.08,3,7,'');
insert  into `terminals`(`id`,`parentid`,`type`,`oX`,`oZ`,`oY`,`oW`,`X`,`Z`,`Y`,`zoneid`,`attributes`) values (78,1105881,6,0,0,-0.7,0.7,8,0.08,3,8,'');
insert  into `terminals`(`id`,`parentid`,`type`,`oX`,`oZ`,`oY`,`oW`,`X`,`Z`,`Y`,`zoneid`,`attributes`) values (79,1106504,6,0,0,0,1,8,0.08,3,8,'');
insert  into `terminals`(`id`,`parentid`,`type`,`oX`,`oZ`,`oY`,`oW`,`X`,`Z`,`Y`,`zoneid`,`attributes`) values (80,1233040,6,0,0,-0.7,0.7,8,0.08,3,8,'');
insert  into `terminals`(`id`,`parentid`,`type`,`oX`,`oZ`,`oY`,`oW`,`X`,`Z`,`Y`,`zoneid`,`attributes`) values (81,1254763,6,0,0,-0.7,0.7,8,0.08,3,8,'');
insert  into `terminals`(`id`,`parentid`,`type`,`oX`,`oZ`,`oY`,`oW`,`X`,`Z`,`Y`,`zoneid`,`attributes`) values (82,3565796,6,0,0,-0.7,0.7,8,0.08,3,8,'');
insert  into `terminals`(`id`,`parentid`,`type`,`oX`,`oZ`,`oY`,`oW`,`X`,`Z`,`Y`,`zoneid`,`attributes`) values (83,2745616,6,0,0,-0.7,0.7,5,0.25,4.7,4,'');
insert  into `terminals`(`id`,`parentid`,`type`,`oX`,`oZ`,`oY`,`oW`,`X`,`Z`,`Y`,`zoneid`,`attributes`) values (84,1400857,6,0,0,-0.7,0.7,5,0.25,4.7,8,'');
insert  into `terminals`(`id`,`parentid`,`type`,`oX`,`oZ`,`oY`,`oW`,`X`,`Z`,`Y`,`zoneid`,`attributes`) values (85,1400846,6,0,0,-0.7,0.7,5,0.25,4.7,8,'');
insert  into `terminals`(`id`,`parentid`,`type`,`oX`,`oZ`,`oY`,`oW`,`X`,`Z`,`Y`,`zoneid`,`attributes`) values (86,1495846,6,0,0,-0.7,0.7,5,0.25,4.7,8,'');
insert  into `terminals`(`id`,`parentid`,`type`,`oX`,`oZ`,`oY`,`oW`,`X`,`Z`,`Y`,`zoneid`,`attributes`) values (87,1365998,6,0,0,0.7,0.7,-5.5,0.125,-3.75,1,'');
insert  into `terminals`(`id`,`parentid`,`type`,`oX`,`oZ`,`oY`,`oW`,`X`,`Z`,`Y`,`zoneid`,`attributes`) values (88,1366009,6,0,0,0.7,0.7,-5.5,0.125,-3.75,1,'');
insert  into `terminals`(`id`,`parentid`,`type`,`oX`,`oZ`,`oY`,`oW`,`X`,`Z`,`Y`,`zoneid`,`attributes`) values (89,4885429,6,0,0,0.7,0.7,-5.5,0.125,-3.75,1,'');
insert  into `terminals`(`id`,`parentid`,`type`,`oX`,`oZ`,`oY`,`oW`,`X`,`Z`,`Y`,`zoneid`,`attributes`) values (90,1392895,6,0,0,0.7,0.7,-5.5,0.125,-3.75,2,'');
insert  into `terminals`(`id`,`parentid`,`type`,`oX`,`oZ`,`oY`,`oW`,`X`,`Z`,`Y`,`zoneid`,`attributes`) values (91,6705360,6,0,0,0.7,0.7,-5.5,0.125,-3.75,3,'');
insert  into `terminals`(`id`,`parentid`,`type`,`oX`,`oZ`,`oY`,`oW`,`X`,`Z`,`Y`,`zoneid`,`attributes`) values (92,8615444,6,0,0,0.7,0.7,-5.5,0.125,-3.75,4,'');
insert  into `terminals`(`id`,`parentid`,`type`,`oX`,`oZ`,`oY`,`oW`,`X`,`Z`,`Y`,`zoneid`,`attributes`) values (93,4505611,6,0,0,0.7,0.7,-5.5,0.125,-3.75,6,'');
insert  into `terminals`(`id`,`parentid`,`type`,`oX`,`oZ`,`oY`,`oW`,`X`,`Z`,`Y`,`zoneid`,`attributes`) values (94,4965415,6,0,0,0.7,0.7,-5.5,0.125,-3.75,7,'');
insert  into `terminals`(`id`,`parentid`,`type`,`oX`,`oZ`,`oY`,`oW`,`X`,`Z`,`Y`,`zoneid`,`attributes`) values (95,3035599,6,0,0,0.7,0.7,-5.5,0.125,-3.75,9,'');
insert  into `terminals`(`id`,`parentid`,`type`,`oX`,`oZ`,`oY`,`oW`,`X`,`Z`,`Y`,`zoneid`,`attributes`) values (96,1392858,6,0,0,1,0,4,0.125,4.5,2,'');
insert  into `terminals`(`id`,`parentid`,`type`,`oX`,`oZ`,`oY`,`oW`,`X`,`Z`,`Y`,`zoneid`,`attributes`) values (97,3605958,6,0,0,1,0,4,0.125,4.5,3,'');
insert  into `terminals`(`id`,`parentid`,`type`,`oX`,`oZ`,`oY`,`oW`,`X`,`Z`,`Y`,`zoneid`,`attributes`) values (98,7925457,6,0,0,1,0,4,0.125,4.5,9,'');
insert  into `terminals`(`id`,`parentid`,`type`,`oX`,`oZ`,`oY`,`oW`,`X`,`Z`,`Y`,`zoneid`,`attributes`) values (99,2203318222975,8,0,0,0,1,27.4,-3.5,-170.7,42,'');
insert  into `terminals`(`id`,`parentid`,`type`,`oX`,`oZ`,`oY`,`oW`,`X`,`Z`,`Y`,`zoneid`,`attributes`) values (259,0,2,0,0,0.999989,-0.00472643,-5705.57,6.52214,4166.91,5,'');
insert  into `terminals`(`id`,`parentid`,`type`,`oX`,`oZ`,`oY`,`oW`,`X`,`Z`,`Y`,`zoneid`,`attributes`) values (258,0,2,0,0,-0.701253,0.712913,-5709.95,6.52214,4170.85,5,'');
insert  into `terminals`(`id`,`parentid`,`type`,`oX`,`oZ`,`oY`,`oW`,`X`,`Z`,`Y`,`zoneid`,`attributes`) values (257,0,2,0,0,0.00270494,0.999996,-5706.13,6.52214,4175.41,5,'');
insert  into `terminals`(`id`,`parentid`,`type`,`oX`,`oZ`,`oY`,`oW`,`X`,`Z`,`Y`,`zoneid`,`attributes`) values (256,0,2,0,0,0.696747,0.717317,-5701.45,6.52214,4171.6,5,'');
insert  into `terminals`(`id`,`parentid`,`type`,`oX`,`oZ`,`oY`,`oW`,`X`,`Z`,`Y`,`zoneid`,`attributes`) values (255,0,2,0,0,0.340515,0.940239,-5128.21,6.52214,4162.91,5,'');
insert  into `terminals`(`id`,`parentid`,`type`,`oX`,`oZ`,`oY`,`oW`,`X`,`Z`,`Y`,`zoneid`,`attributes`) values (254,0,2,0,0,-0.426231,0.904614,-5134.29,6.52214,4162.82,5,'');
insert  into `terminals`(`id`,`parentid`,`type`,`oX`,`oZ`,`oY`,`oW`,`X`,`Z`,`Y`,`zoneid`,`attributes`) values (253,0,2,0,0,0.933594,-0.358332,-5133.53,6.52214,4156.28,5,'');
insert  into `terminals`(`id`,`parentid`,`type`,`oX`,`oZ`,`oY`,`oW`,`X`,`Z`,`Y`,`zoneid`,`attributes`) values (252,0,2,0,0,0.88772,0.460383,-5127.88,6.52214,4157.23,5,'');
insert  into `terminals`(`id`,`parentid`,`type`,`oX`,`oZ`,`oY`,`oW`,`X`,`Z`,`Y`,`zoneid`,`attributes`) values (251,0,2,0,0,0.725226,0.688511,-51.3363,28.5179,-4599.23,0,'');
insert  into `terminals`(`id`,`parentid`,`type`,`oX`,`oZ`,`oY`,`oW`,`X`,`Z`,`Y`,`zoneid`,`attributes`) values (250,0,2,0,0,-0.000426952,1,-55.5427,28.5179,-4595.08,0,'');
insert  into `terminals`(`id`,`parentid`,`type`,`oX`,`oZ`,`oY`,`oW`,`X`,`Z`,`Y`,`zoneid`,`attributes`) values (249,0,2,0,0,0.71332,-0.700838,-59.837,28.5179,-4599.36,0,'');
insert  into `terminals`(`id`,`parentid`,`type`,`oX`,`oZ`,`oY`,`oW`,`X`,`Z`,`Y`,`zoneid`,`attributes`) values (248,0,2,0,0,0.999998,0.00220255,-55.6543,28.5179,-4603.58,0,'');
insert  into `terminals`(`id`,`parentid`,`type`,`oX`,`oZ`,`oY`,`oW`,`X`,`Z`,`Y`,`zoneid`,`attributes`) values (247,0,2,0,0,-0.420564,0.907263,-5272.54,21,-2508.25,0,'');
insert  into `terminals`(`id`,`parentid`,`type`,`oX`,`oZ`,`oY`,`oW`,`X`,`Z`,`Y`,`zoneid`,`attributes`) values (246,0,2,0,0,-0.392422,0.919785,-5109.45,21.3039,-2380.85,0,'');
insert  into `terminals`(`id`,`parentid`,`type`,`oX`,`oZ`,`oY`,`oW`,`X`,`Z`,`Y`,`zoneid`,`attributes`) values (245,0,2,0,0,0.926584,-0.376089,-5109.55,21.3039,-2386.93,0,'');
insert  into `terminals`(`id`,`parentid`,`type`,`oX`,`oZ`,`oY`,`oW`,`X`,`Z`,`Y`,`zoneid`,`attributes`) values (244,0,2,0,0,0.924363,0.381514,-5103.51,21.3039,-2386.97,0,'');
insert  into `terminals`(`id`,`parentid`,`type`,`oX`,`oZ`,`oY`,`oW`,`X`,`Z`,`Y`,`zoneid`,`attributes`) values (243,0,2,0,0,0.378823,0.925469,-5103.47,21.3039,-2380.99,0,'');
insert  into `terminals`(`id`,`parentid`,`type`,`oX`,`oZ`,`oY`,`oW`,`X`,`Z`,`Y`,`zoneid`,`attributes`) values (242,0,2,0,0,0.924999,0.37997,3212.57,300.174,5383.63,0,'');
insert  into `terminals`(`id`,`parentid`,`type`,`oX`,`oZ`,`oY`,`oW`,`X`,`Z`,`Y`,`zoneid`,`attributes`) values (241,0,2,0,0,0.384639,0.923067,3212.47,300.174,5389.78,0,'');
insert  into `terminals`(`id`,`parentid`,`type`,`oX`,`oZ`,`oY`,`oW`,`X`,`Z`,`Y`,`zoneid`,`attributes`) values (240,0,2,0,0,-0.385943,0.922522,3206.58,300.174,5389.66,0,'');
insert  into `terminals`(`id`,`parentid`,`type`,`oX`,`oZ`,`oY`,`oW`,`X`,`Z`,`Y`,`zoneid`,`attributes`) values (239,0,2,0,0,0.926111,-0.377252,3206.57,300.174,5383.56,0,'');
insert  into `terminals`(`id`,`parentid`,`type`,`oX`,`oZ`,`oY`,`oW`,`X`,`Z`,`Y`,`zoneid`,`attributes`) values (238,0,2,0,0,0.78209,-0.623165,-1277.88,12.5279,-3665.29,8,'');
insert  into `terminals`(`id`,`parentid`,`type`,`oX`,`oZ`,`oY`,`oW`,`X`,`Z`,`Y`,`zoneid`,`attributes`) values (237,0,2,0,0,0.993979,0.109575,-1272.86,12.5279,-3668.84,8,'');
insert  into `terminals`(`id`,`parentid`,`type`,`oX`,`oZ`,`oY`,`oW`,`X`,`Z`,`Y`,`zoneid`,`attributes`) values (236,0,2,0,0,0.638094,0.769958,-1269.54,12.5279,-3663.67,8,'');
insert  into `terminals`(`id`,`parentid`,`type`,`oX`,`oZ`,`oY`,`oW`,`X`,`Z`,`Y`,`zoneid`,`attributes`) values (235,0,2,0,0,-0.11758,0.993063,-1274.59,12.5279,-3660.36,8,'');
insert  into `terminals`(`id`,`parentid`,`type`,`oX`,`oZ`,`oY`,`oW`,`X`,`Z`,`Y`,`zoneid`,`attributes`) values (234,0,2,0,0,-0.458174,0.888862,3495.86,5.52789,-4941.62,8,'');
insert  into `terminals`(`id`,`parentid`,`type`,`oX`,`oZ`,`oY`,`oW`,`X`,`Z`,`Y`,`zoneid`,`attributes`) values (233,0,2,0,0,0.941343,-0.337451,3496.46,5.52789,-4947.59,8,'');
insert  into `terminals`(`id`,`parentid`,`type`,`oX`,`oZ`,`oY`,`oW`,`X`,`Z`,`Y`,`zoneid`,`attributes`) values (232,0,2,0,0,0.905612,0.424108,3502.42,5.52789,-4946.99,8,'');
insert  into `terminals`(`id`,`parentid`,`type`,`oX`,`oZ`,`oY`,`oW`,`X`,`Z`,`Y`,`zoneid`,`attributes`) values (231,0,2,0,0,0.27848,0.960442,3501.56,5.52789,-4940.78,8,'');
insert  into `terminals`(`id`,`parentid`,`type`,`oX`,`oZ`,`oY`,`oW`,`X`,`Z`,`Y`,`zoneid`,`attributes`) values (230,0,2,0,0,0.779783,-0.62605,-2997.07,5.52789,2335.08,8,'');
insert  into `terminals`(`id`,`parentid`,`type`,`oX`,`oZ`,`oY`,`oW`,`X`,`Z`,`Y`,`zoneid`,`attributes`) values (229,0,2,0,0,0.787247,-0.616638,-2997.83,5.52789,2338.22,8,'');
insert  into `terminals`(`id`,`parentid`,`type`,`oX`,`oZ`,`oY`,`oW`,`X`,`Z`,`Y`,`zoneid`,`attributes`) values (228,0,2,0,0,-0.115393,0.99332,-2994.22,5.52789,2341.13,8,'');
insert  into `terminals`(`id`,`parentid`,`type`,`oX`,`oZ`,`oY`,`oW`,`X`,`Z`,`Y`,`zoneid`,`attributes`) values (227,0,2,0,0,0.993065,0.11757,-2997.8,5.52789,2332.75,8,'');
insert  into `terminals`(`id`,`parentid`,`type`,`oX`,`oZ`,`oY`,`oW`,`X`,`Z`,`Y`,`zoneid`,`attributes`) values (226,0,2,0,0,-0.444309,0.895873,4800.79,4.27214,-4864.11,5,'');
insert  into `terminals`(`id`,`parentid`,`type`,`oX`,`oZ`,`oY`,`oW`,`X`,`Z`,`Y`,`zoneid`,`attributes`) values (225,0,2,0,0,0.945915,-0.324414,4801.84,4.27214,-4870,5,'');
insert  into `terminals`(`id`,`parentid`,`type`,`oX`,`oZ`,`oY`,`oW`,`X`,`Z`,`Y`,`zoneid`,`attributes`) values (224,0,2,0,0,0.901533,0.432711,4807.86,4.27214,-4869.14,5,'');
insert  into `terminals`(`id`,`parentid`,`type`,`oX`,`oZ`,`oY`,`oW`,`X`,`Z`,`Y`,`zoneid`,`attributes`) values (223,0,2,0,0,0.348279,0.937391,4806.99,4.27214,-4863.23,5,'');
insert  into `terminals`(`id`,`parentid`,`type`,`oX`,`oZ`,`oY`,`oW`,`X`,`Z`,`Y`,`zoneid`,`attributes`) values (222,0,2,0,0,0.699036,0.715086,1791.25,12.5221,2614.05,5,'');
insert  into `terminals`(`id`,`parentid`,`type`,`oX`,`oZ`,`oY`,`oW`,`X`,`Z`,`Y`,`zoneid`,`attributes`) values (221,0,2,0,0,-0.0118409,0.99993,1786.89,12.5221,2618.43,5,'');
insert  into `terminals`(`id`,`parentid`,`type`,`oX`,`oZ`,`oY`,`oW`,`X`,`Z`,`Y`,`zoneid`,`attributes`) values (220,0,2,0,0,0.999535,0.0305048,1787.3,12.5221,2609.75,5,'');
insert  into `terminals`(`id`,`parentid`,`type`,`oX`,`oZ`,`oY`,`oW`,`X`,`Z`,`Y`,`zoneid`,`attributes`) values (219,0,2,0,0,0.714271,-0.699869,1782.75,12.5221,2613.96,5,'');
insert  into `terminals`(`id`,`parentid`,`type`,`oX`,`oZ`,`oY`,`oW`,`X`,`Z`,`Y`,`zoneid`,`attributes`) values (218,0,2,0,0,0.382438,0.923981,5080.22,-191.739,6713.11,5,'');
insert  into `terminals`(`id`,`parentid`,`type`,`oX`,`oZ`,`oY`,`oW`,`X`,`Z`,`Y`,`zoneid`,`attributes`) values (217,0,2,0,0,-0.387525,0.921859,5074.05,-191.739,6712.96,5,'');
insert  into `terminals`(`id`,`parentid`,`type`,`oX`,`oZ`,`oY`,`oW`,`X`,`Z`,`Y`,`zoneid`,`attributes`) values (216,0,2,0,0,0.933015,-0.359837,5074.29,-191.739,6707.02,5,'');
insert  into `terminals`(`id`,`parentid`,`type`,`oX`,`oZ`,`oY`,`oW`,`X`,`Z`,`Y`,`zoneid`,`attributes`) values (215,0,2,0,0,0.916547,0.399928,5080.34,-191.739,6707.01,5,'');
insert  into `terminals`(`id`,`parentid`,`type`,`oX`,`oZ`,`oY`,`oW`,`X`,`Z`,`Y`,`zoneid`,`attributes`) values (214,0,2,0,0,0.707711,0.706502,-5106,80.2418,-2474.65,6,'');
insert  into `terminals`(`id`,`parentid`,`type`,`oX`,`oZ`,`oY`,`oW`,`X`,`Z`,`Y`,`zoneid`,`attributes`) values (213,0,2,0,0,0.707711,0.706502,-5106,80.2418,-2474.65,6,'');
insert  into `terminals`(`id`,`parentid`,`type`,`oX`,`oZ`,`oY`,`oW`,`X`,`Z`,`Y`,`zoneid`,`attributes`) values (212,0,2,0,0,0.710861,-0.703333,-5114.5,80.2418,-2474.43,6,'');
insert  into `terminals`(`id`,`parentid`,`type`,`oX`,`oZ`,`oY`,`oW`,`X`,`Z`,`Y`,`zoneid`,`attributes`) values (211,0,2,0,0,0.999832,0.018351,5181.01,80.1795,5579.75,6,'');
insert  into `terminals`(`id`,`parentid`,`type`,`oX`,`oZ`,`oY`,`oW`,`X`,`Z`,`Y`,`zoneid`,`attributes`) values (210,0,2,0,0,0.00289198,0.999996,5180.9,80.1795,5588.25,6,'');
insert  into `terminals`(`id`,`parentid`,`type`,`oX`,`oZ`,`oY`,`oW`,`X`,`Z`,`Y`,`zoneid`,`attributes`) values (209,0,2,0,0,0.738781,-0.673945,417.655,12.5279,5050.26,4,'');
insert  into `terminals`(`id`,`parentid`,`type`,`oX`,`oZ`,`oY`,`oW`,`X`,`Z`,`Y`,`zoneid`,`attributes`) values (208,0,2,0,0,0.999952,-0.000981364,421.861,12.5279,5046.08,4,'');
insert  into `terminals`(`id`,`parentid`,`type`,`oX`,`oZ`,`oY`,`oW`,`X`,`Z`,`Y`,`zoneid`,`attributes`) values (207,0,2,0,0,0.712983,0.701182,426.155,12.5279,5050.42,4,'');
insert  into `terminals`(`id`,`parentid`,`type`,`oX`,`oZ`,`oY`,`oW`,`X`,`Z`,`Y`,`zoneid`,`attributes`) values (206,0,2,0,0,0.0448483,0.998994,421.88,12.5279,5054.58,4,'');
insert  into `terminals`(`id`,`parentid`,`type`,`oX`,`oZ`,`oY`,`oW`,`X`,`Z`,`Y`,`zoneid`,`attributes`) values (205,0,2,0,0,0.919403,-0.393317,553.466,6.51789,-2976.67,7,'');
insert  into `terminals`(`id`,`parentid`,`type`,`oX`,`oZ`,`oY`,`oW`,`X`,`Z`,`Y`,`zoneid`,`attributes`) values (204,0,2,0,0,0.384654,0.923061,526.914,6.51789,-3003.71,7,'');

/*!40101 SET SQL_MODE=@OLD_SQL_MODE */;
/*!40014 SET FOREIGN_KEY_CHECKS=@OLD_FOREIGN_KEY_CHECKS */;

update `skills` set `skill_id`='149',`skill_name`='combat_pistol_master',`skill_parent`='combat_pistol',`skill_graph_type`='fourByFour',`skill_god_only`='0',`skill_is_title`='1',`skill_is_profession`='0',`skill_is_hidden`='0',`skill_money_required`='10000',`skill_points_required`='1',`skill_requirements_count`='0',`skill_requirements`='combat_pistol_accuracy_04,combat_pistol_speed_04,combat_pistol_ability_04,combat_pistol_support_04',`skill_preclusions`=' ',`skill_xp_type`=' ',`skill_xp_cost`='0',`skill_xp_cap`='0',`skill_required_missions`=' ',`skill_apprenticeships_required`='0',`skill_stats_required`=' ',`skill_species_required`=' ',`skill_jedi_state_required`='none',`skill_abilities`=' ',`skill_commands`='private_pistol_master,multiTargetPistolShot,disarmingShot2,ranged_damage_mitigation_3,cert_pistol_de_10',`skill_mods`='pistol_accuracy=10,pistol_speed=20,pistol_hit_while_moving=10,pistol_aim=4,ranged_defense=5,melee_defense=5,private_pistol_combat_difficulty=100,dodge=25',`skill_schematics_granted`=' ',`skill_schematics_revoked`=' ',`skill_is_searchable`='1',`skill_ender`='0' where `skill_id`='149';
update `skills` set `skill_id`='240',`skill_name`='combat_2hsword_support_03',`skill_parent`='combat_2hsword_support_02',`skill_graph_type`='fourByFour',`skill_god_only`='0',`skill_is_title`='0',`skill_is_profession`='0',`skill_is_hidden`='0',`skill_money_required`='8000',`skill_points_required`='3',`skill_requirements_count`='0',`skill_requirements`='combat_2hsword_support_02',`skill_preclusions`=' ',`skill_xp_type`='combat_general',`skill_xp_cost`='120000',`skill_xp_cap`='300000',`skill_required_missions`=' ',`skill_apprenticeships_required`='0',`skill_stats_required`=' ',`skill_species_required`=' ',`skill_jedi_state_required`='none',`skill_abilities`=' ',`skill_commands`='melee2hMindHit2,cert_sword_2h_scythe',`skill_mods`='private_twohandmelee_combat_difficulty=100',`skill_schematics_granted`=' ',`skill_schematics_revoked`=' ',`skill_is_searchable`='1',`skill_ender`='0' where `skill_id`='240';
