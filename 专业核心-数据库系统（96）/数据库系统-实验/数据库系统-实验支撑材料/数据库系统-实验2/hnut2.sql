/*
 Navicat Premium Data Transfer

 Source Server         : localhost_3306
 Source Server Type    : MySQL
 Source Server Version : 80033 (8.0.33)
 Source Host           : localhost:3306
 Source Schema         : hnut2

 Target Server Type    : MySQL
 Target Server Version : 80033 (8.0.33)
 File Encoding         : 65001

 Date: 29/12/2023 16:30:08
*/

SET NAMES utf8mb4;
SET FOREIGN_KEY_CHECKS = 0;

-- ----------------------------
-- Table structure for class
-- ----------------------------
DROP TABLE IF EXISTS `class`;
CREATE TABLE `class`  (
  `Sname` char(10) CHARACTER SET utf8mb4 COLLATE utf8mb4_0900_ai_ci NULL DEFAULT NULL,
  `Sno` char(9) CHARACTER SET utf8mb4 COLLATE utf8mb4_0900_ai_ci NOT NULL,
  `Sgrade` smallint NULL DEFAULT NULL,
  PRIMARY KEY (`Sno`) USING BTREE,
  INDEX `Sname`(`Sname` ASC) USING BTREE,
  CONSTRAINT `class_ibfk_1` FOREIGN KEY (`Sname`) REFERENCES `student` (`Sname`) ON DELETE CASCADE ON UPDATE CASCADE
) ENGINE = InnoDB CHARACTER SET = utf8mb4 COLLATE = utf8mb4_0900_ai_ci ROW_FORMAT = Dynamic;

-- ----------------------------
-- Records of class
-- ----------------------------

-- ----------------------------
-- Table structure for course
-- ----------------------------
DROP TABLE IF EXISTS `course`;
CREATE TABLE `course`  (
  `Cno` char(9) CHARACTER SET utf8mb4 COLLATE utf8mb4_0900_ai_ci NOT NULL,
  `Cname` char(20) CHARACTER SET utf8mb4 COLLATE utf8mb4_0900_ai_ci NULL DEFAULT NULL,
  `Cpno` char(9) CHARACTER SET utf8mb4 COLLATE utf8mb4_0900_ai_ci NULL DEFAULT NULL,
  `Ctype` char(5) CHARACTER SET utf8mb4 COLLATE utf8mb4_0900_ai_ci NULL DEFAULT NULL,
  `Cdept` char(20) CHARACTER SET utf8mb4 COLLATE utf8mb4_0900_ai_ci NULL DEFAULT NULL,
  `Chours` smallint NULL DEFAULT NULL,
  `Ccredit` smallint NULL DEFAULT NULL,
  PRIMARY KEY (`Cno`) USING BTREE
) ENGINE = InnoDB CHARACTER SET = utf8mb4 COLLATE = utf8mb4_0900_ai_ci ROW_FORMAT = Dynamic;

-- ----------------------------
-- Records of course
-- ----------------------------
INSERT INTO `course` VALUES ('GE001234', '数据库系统', '计算机系统', '专业核心', '计算机科学系', 40, 3);
INSERT INTO `course` VALUES ('SGE001234', '数据库系统', '计算机系统', '专业核心', '计算机科学系', 40, 3);

-- ----------------------------
-- Table structure for source
-- ----------------------------
DROP TABLE IF EXISTS `source`;
CREATE TABLE `source`  (
  `SNO` char(9) CHARACTER SET utf8mb4 COLLATE utf8mb4_0900_ai_ci NOT NULL,
  `SNAME` char(10) CHARACTER SET utf8mb4 COLLATE utf8mb4_0900_ai_ci NOT NULL,
  `SGRADE` smallint NULL DEFAULT NULL,
  `SSEX` char(2) CHARACTER SET utf8mb4 COLLATE utf8mb4_0900_ai_ci NOT NULL,
  `SGROUP` smallint NULL DEFAULT NULL,
  PRIMARY KEY (`SNO`) USING BTREE,
  UNIQUE INDEX `SNO`(`SNO` ASC) USING BTREE,
  CONSTRAINT `C1` CHECK ((`SSEX` = _utf8mb4'男') or (`SSEX` = _utf8mb4'女'))
) ENGINE = InnoDB CHARACTER SET = utf8mb4 COLLATE = utf8mb4_0900_ai_ci ROW_FORMAT = Dynamic;

-- ----------------------------
-- Records of source
-- ----------------------------
INSERT INTO `source` VALUES ('202108010', '甘晴void', 100, '男', 22);

-- ----------------------------
-- Table structure for student
-- ----------------------------
DROP TABLE IF EXISTS `student`;
CREATE TABLE `student`  (
  `Sno` char(9) CHARACTER SET utf8mb4 COLLATE utf8mb4_0900_ai_ci NOT NULL,
  `Sname` char(20) CHARACTER SET utf8mb4 COLLATE utf8mb4_0900_ai_ci NOT NULL,
  `Ssex` char(2) CHARACTER SET utf8mb4 COLLATE utf8mb4_0900_ai_ci NULL DEFAULT NULL,
  `Ssage` smallint NULL DEFAULT NULL,
  `Sclass` char(10) CHARACTER SET utf8mb4 COLLATE utf8mb4_0900_ai_ci NOT NULL,
  PRIMARY KEY (`Sname`, `Sclass`) USING BTREE,
  UNIQUE INDEX `Sno`(`Sno` ASC) USING BTREE,
  CONSTRAINT `student_chk_1` CHECK ((`Ssex` = _utf8mb4'男') or (`Ssex` = _utf8mb4'女')),
  CONSTRAINT `student_chk_2` CHECK (`Ssage` < 25)
) ENGINE = InnoDB CHARACTER SET = utf8mb4 COLLATE = utf8mb4_0900_ai_ci ROW_FORMAT = Dynamic;

-- ----------------------------
-- Records of student
-- ----------------------------

-- ----------------------------
-- Table structure for teacher_salary
-- ----------------------------
DROP TABLE IF EXISTS `teacher_salary`;
CREATE TABLE `teacher_salary`  (
  `NAME` char(10) CHARACTER SET utf8mb4 COLLATE utf8mb4_0900_ai_ci NOT NULL,
  `JOB` char(20) CHARACTER SET utf8mb4 COLLATE utf8mb4_0900_ai_ci NOT NULL,
  `SALARY` smallint NOT NULL,
  PRIMARY KEY (`NAME`) USING BTREE
) ENGINE = InnoDB CHARACTER SET = utf8mb4 COLLATE = utf8mb4_0900_ai_ci ROW_FORMAT = Dynamic;

-- ----------------------------
-- Records of teacher_salary
-- ----------------------------
INSERT INTO `teacher_salary` VALUES ('甘晴void', '教授', 5000);
INSERT INTO `teacher_salary` VALUES ('甘晴void3', '教授', 2000);
INSERT INTO `teacher_salary` VALUES ('甘晴wolf', '教授', 3000);

-- ----------------------------
-- Table structure for ts_u
-- ----------------------------
DROP TABLE IF EXISTS `ts_u`;
CREATE TABLE `ts_u`  (
  `NAME` char(10) CHARACTER SET utf8mb4 COLLATE utf8mb4_0900_ai_ci NULL DEFAULT NULL,
  `JOB` char(20) CHARACTER SET utf8mb4 COLLATE utf8mb4_0900_ai_ci NULL DEFAULT NULL,
  `SALARY` smallint NULL DEFAULT NULL,
  `TAG` char(10) CHARACTER SET utf8mb4 COLLATE utf8mb4_0900_ai_ci NULL DEFAULT NULL
) ENGINE = InnoDB CHARACTER SET = utf8mb4 COLLATE = utf8mb4_0900_ai_ci ROW_FORMAT = Dynamic;

-- ----------------------------
-- Records of ts_u
-- ----------------------------
INSERT INTO `ts_u` VALUES ('甘晴wolf', '教授', 3000, 'BEFORE');
INSERT INTO `ts_u` VALUES ('甘晴wolf', '教授', 3000, 'AFTER');
INSERT INTO `ts_u` VALUES ('甘晴void3', '教授', 2000, 'BEFORE');
INSERT INTO `ts_u` VALUES ('甘晴void3', '教授', 2000, 'AFTER');

-- ----------------------------
-- Triggers structure for table teacher_salary
-- ----------------------------
DROP TRIGGER IF EXISTS `TS_T1`;
delimiter ;;
CREATE TRIGGER `TS_T1` BEFORE INSERT ON `teacher_salary` FOR EACH ROW BEGIN
	IF (NEW.JOB = '教授') AND (NEW.SALARY<5000) THEN
	INSERT INTO TS_U VALUES(NEW.NAME,NEW.JOB,NEW.SALARY,'BEFORE');
	END IF;
END
;;
delimiter ;

-- ----------------------------
-- Triggers structure for table teacher_salary
-- ----------------------------
DROP TRIGGER IF EXISTS `TS_T2`;
delimiter ;;
CREATE TRIGGER `TS_T2` AFTER INSERT ON `teacher_salary` FOR EACH ROW BEGIN
	IF (NEW.JOB = '教授') AND (NEW.SALARY<5000) THEN
	INSERT INTO TS_U VALUES(NEW.NAME,NEW.JOB,NEW.SALARY,'AFTER');
	END IF;
END
;;
delimiter ;

SET FOREIGN_KEY_CHECKS = 1;
