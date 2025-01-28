/*
 Navicat Premium Data Transfer

 Source Server         : localhost_3306
 Source Server Type    : MySQL
 Source Server Version : 80033 (8.0.33)
 Source Host           : localhost:3306
 Source Schema         : lab4

 Target Server Type    : MySQL
 Target Server Version : 80033 (8.0.33)
 File Encoding         : 65001

 Date: 24/12/2023 21:06:13
*/

SET NAMES utf8mb4;
SET FOREIGN_KEY_CHECKS = 0;

-- ----------------------------
-- Table structure for sc
-- ----------------------------
DROP TABLE IF EXISTS `sc`;
CREATE TABLE `sc`  (
  `Sno` char(12) CHARACTER SET utf8mb4 COLLATE utf8mb4_0900_ai_ci NOT NULL,
  `Sname` varchar(50) CHARACTER SET utf8mb4 COLLATE utf8mb4_0900_ai_ci NULL DEFAULT NULL,
  `Cno` char(10) CHARACTER SET utf8mb4 COLLATE utf8mb4_0900_ai_ci NOT NULL,
  `Cname` varchar(50) CHARACTER SET utf8mb4 COLLATE utf8mb4_0900_ai_ci NULL DEFAULT NULL,
  `Grade` smallint NULL DEFAULT NULL,
  `credit` smallint NULL DEFAULT NULL,
  PRIMARY KEY (`Sno`, `Cno`) USING BTREE
) ENGINE = InnoDB CHARACTER SET = utf8mb4 COLLATE = utf8mb4_0900_ai_ci ROW_FORMAT = Dynamic;

-- ----------------------------
-- Records of sc
-- ----------------------------
INSERT INTO `sc` VALUES ('202108010200', 'wolf', '001', 'cs', 90, 5);
INSERT INTO `sc` VALUES ('202108010200', 'wolf', '002', 'os', 95, 5);
INSERT INTO `sc` VALUES ('202108010200', 'wolf', '003', 'cp', 85, 3);
INSERT INTO `sc` VALUES ('202108010266', 'bronya', '001', 'cs', 60, 5);
INSERT INTO `sc` VALUES ('202108010266', 'bronya', '005', 'is', 90, 3);
INSERT INTO `sc` VALUES ('202108010299', 'void', '001', 'cs', 100, 5);
INSERT INTO `sc` VALUES ('202108010299', 'void', '002', 'os', 90, 5);
INSERT INTO `sc` VALUES ('202108010299', 'void', '004', 'db', 100, 3);

-- ----------------------------
-- Table structure for student
-- ----------------------------
DROP TABLE IF EXISTS `student`;
CREATE TABLE `student`  (
  `Sno` char(12) CHARACTER SET utf8mb4 COLLATE utf8mb4_0900_ai_ci NOT NULL,
  `Sname` varchar(50) CHARACTER SET utf8mb4 COLLATE utf8mb4_0900_ai_ci NULL DEFAULT NULL,
  `S_a_avg` double(4, 2) NULL DEFAULT NULL,
  `S_w_avg` double(4, 2) NULL DEFAULT NULL,
  `GPA` double(4, 1) NULL DEFAULT NULL,
  PRIMARY KEY (`Sno`) USING BTREE
) ENGINE = InnoDB CHARACTER SET = utf8mb4 COLLATE = utf8mb4_0900_ai_ci ROW_FORMAT = Dynamic;

-- ----------------------------
-- Records of student
-- ----------------------------
INSERT INTO `student` VALUES ('202108010200', 'wolf', 0.00, NULL, NULL);
INSERT INTO `student` VALUES ('202108010266', 'bronya', 0.00, NULL, NULL);
INSERT INTO `student` VALUES ('202108010299', 'void', 0.00, NULL, NULL);

-- ----------------------------
-- Function structure for func_4_2_1_Calculate_Avg
-- ----------------------------
DROP FUNCTION IF EXISTS `func_4_2_1_Calculate_Avg`;
delimiter ;;
CREATE FUNCTION `func_4_2_1_Calculate_Avg`()
 RETURNS double
BEGIN
	DECLARE	res REAL;
	UPDATE student
		SET S_a_avg = (
			SELECT AVG(Grade)
    			FROM SC
    			WHERE student.Sno = sc.Sno
		);
	SELECT AVG(Grade) INTO res
    	FROM SC,student
    	WHERE student.Sno = sc.Sno; 
	RETURN res;
END
;;
delimiter ;

-- ----------------------------
-- Function structure for func_4_2_2_Calculate_target_Avg
-- ----------------------------
DROP FUNCTION IF EXISTS `func_4_2_2_Calculate_target_Avg`;
delimiter ;;
CREATE FUNCTION `func_4_2_2_Calculate_target_Avg`(target varchar(50))
 RETURNS double
BEGIN
	DECLARE	res REAL;
	UPDATE student
		SET S_a_avg = (
			SELECT AVG(Grade)
    			FROM SC
    			WHERE student.Sno = sc.Sno AND
        			student.Sname = target
		);
	SELECT AVG(Grade) INTO res
    	FROM SC,student
    	WHERE student.Sno = sc.Sno AND
        	student.Sname = target;
    RETURN res;
END
;;
delimiter ;

-- ----------------------------
-- Function structure for func_4_2_3_Calculate_target_weighted_Avg
-- ----------------------------
DROP FUNCTION IF EXISTS `func_4_2_3_Calculate_target_weighted_Avg`;
delimiter ;;
CREATE FUNCTION `func_4_2_3_Calculate_target_weighted_Avg`(target_sname varchar(50))
 RETURNS double
BEGIN
	DECLARE	res REAL;
	DECLARE target_sno char(12);
	SELECT student.sno INTO target_sno
		FROM student
		WHERE student.sname = target_sname;
  	UPDATE student
	  SET S_w_avg = (
		  SELECT SUM(Grade*credit) / SUM(credit)
      FROM SC
      WHERE student.Sno = sc.Sno AND sc.sno = target_sno
	);
	SELECT SUM(Grade*credit) / SUM(credit) INTO res
      FROM SC,student
      WHERE student.Sno = sc.Sno AND sc.sno = target_sno;
    RETURN res;
END
;;
delimiter ;

-- ----------------------------
-- Procedure structure for Proc4.1.1_Calculate_Avg
-- ----------------------------
DROP PROCEDURE IF EXISTS `Proc4.1.1_Calculate_Avg`;
delimiter ;;
CREATE PROCEDURE `Proc4.1.1_Calculate_Avg`()
BEGIN
	UPDATE student
	SET S_a_avg = (
		SELECT AVG(Grade)
    FROM SC
    WHERE student.Sno = sc.sno
	);
END
;;
delimiter ;

-- ----------------------------
-- Procedure structure for Proc4.1.2_Calculate_target_Avg
-- ----------------------------
DROP PROCEDURE IF EXISTS `Proc4.1.2_Calculate_target_Avg`;
delimiter ;;
CREATE PROCEDURE `Proc4.1.2_Calculate_target_Avg`(target varchar(50))
BEGIN
	UPDATE student
	SET S_a_avg = (
		SELECT AVG(Grade)
    FROM SC
    WHERE student.Sno = sc.Sno AND
        student.Sname = target
	);
END
;;
delimiter ;

-- ----------------------------
-- Procedure structure for Proc4.1.3_Calculate_target_weighted_Avg
-- ----------------------------
DROP PROCEDURE IF EXISTS `Proc4.1.3_Calculate_target_weighted_Avg`;
delimiter ;;
CREATE PROCEDURE `Proc4.1.3_Calculate_target_weighted_Avg`(target_sname varchar(50))
BEGIN
	DECLARE target_sno char(12);
	SELECT student.sno INTO target_sno
		FROM student
		WHERE student.sname = target_sname;
  UPDATE student
	  SET S_w_avg = (
		  SELECT SUM(Grade*credit) / SUM(credit)
      FROM SC
      WHERE student.Sno = sc.Sno AND sc.sno = target_sno
	);
	
END
;;
delimiter ;

-- ----------------------------
-- Procedure structure for Proc4.1.3_Calculate_weighted_Avg
-- ----------------------------
DROP PROCEDURE IF EXISTS `Proc4.1.3_Calculate_weighted_Avg`;
delimiter ;;
CREATE PROCEDURE `Proc4.1.3_Calculate_weighted_Avg`()
BEGIN
  UPDATE student
	  SET S_w_avg = (
		  SELECT SUM(Grade*credit) / SUM(credit)
      FROM SC
      WHERE student.Sno = sc.Sno
	);
	
END
;;
delimiter ;

-- ----------------------------
-- Procedure structure for Proc4.1.4_return_target_weighted_avg
-- ----------------------------
DROP PROCEDURE IF EXISTS `Proc4.1.4_return_target_weighted_avg`;
delimiter ;;
CREATE PROCEDURE `Proc4.1.4_return_target_weighted_avg`(target_sname varchar(50),
	out result REAL)
BEGIN
	DECLARE target_sno char(12);
	SELECT student.sno INTO target_sno
		FROM student
		WHERE student.sname = target_sname;
	SELECT SUM(Grade*credit) / SUM(credit) INTO result
      FROM SC,student
      WHERE student.Sno = sc.Sno AND sc.sno = target_sno;
END
;;
delimiter ;

-- ----------------------------
-- Procedure structure for PROC_CURSOR
-- ----------------------------
DROP PROCEDURE IF EXISTS `PROC_CURSOR`;
delimiter ;;
CREATE PROCEDURE `PROC_CURSOR`(target_sname VARCHAR(50),
	out result FLOAT(4,2))
BEGIN
    DECLARE total_credit INT;
    DECLARE total_GPA FLOAT;
    DECLARE temp_grade INT;
    DECLARE temp_credit INT;
    DECLARE temp_GPA FLOAT;
    DECLARE done INT DEFAULT 0;
    DECLARE mycursor CURSOR FOR
    						SELECT Grade,credit
    						FROM sc
    						WHERE sc.sname = target_sname;
    DECLARE CONTINUE HANDLER FOR NOT FOUND SET done = 1;
    OPEN mycursor;
    SET total_GPA = 0;
    SET total_credit = 0;
    my_loop:LOOP
    	FETCH mycursor INTO temp_grade,temp_credit;
    	IF done THEN LEAVE my_loop;
    	END IF;
    	IF temp_grade BETWEEN 90 AND 100 THEN  
    		SET temp_GPA = 4.0;
    	ELSEIF temp_grade BETWEEN 85 AND 89 THEN 
    		SET temp_GPA = 3.7;
    	ELSEIF temp_grade BETWEEN 80 AND 84 THEN 
    		SET temp_GPA = 3.3;
    	ELSEIF temp_grade BETWEEN 75 AND 79 THEN 
    		SET temp_GPA = 3.0;
    	ELSEIF temp_grade BETWEEN 70 AND 74 THEN 
    		SET temp_GPA = 2.7;
    	ELSEIF temp_grade BETWEEN 67 AND 69 THEN 
    		SET temp_GPA = 2.3;
    	ELSEIF temp_grade BETWEEN 65 AND 66 THEN 
    		SET temp_GPA = 2.0;
    	ELSEIF temp_grade BETWEEN 62 AND 64 THEN 
    		SET temp_GPA = 1.7;
    	ELSEIF temp_grade BETWEEN 60 AND 61 THEN 
    		SET temp_GPA = 1.0;
    	ELSEIF temp_grade BETWEEN 0 AND 59 THEN 
    		SET temp_GPA = 0;
    	END IF;
    	SET total_GPA = total_GPA + temp_GPA * temp_credit;
    	SET total_credit = total_credit + temp_credit;
    END LOOP;
    CLOSE mycursor;
    # DEALLOCATE mycursor;
    SET result = total_GPA/total_credit;
END
;;
delimiter ;

-- ----------------------------
-- Procedure structure for 快速清除学生成绩
-- ----------------------------
DROP PROCEDURE IF EXISTS `快速清除学生成绩`;
delimiter ;;
CREATE PROCEDURE `快速清除学生成绩`()
BEGIN
	UPDATE student
		SET S_a_avg = 0;
	UPDATE student
		SET S_w_avg = 0;

END
;;
delimiter ;

SET FOREIGN_KEY_CHECKS = 1;
