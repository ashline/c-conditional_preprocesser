#!/bin/sh
cat <<- _eoi_
	##############################################################
	Running tests for C conditional directive preprocessor
	##############################################################
	
	Test 1
	------
		Goal:Testing behaviour when no directives are present

		Input
		----- 
_eoi_
		cat test_cases/test1.c
		cat <<- _eoi_
		-----------------------------------------------------
		Output
		------
_eoi_
		gcc cdpp.c -g -o cdpp `echo $1`
		./cdpp test_cases/test1.c test_cases/result1.c
		cat test_cases/result1.c
		cat <<- _eoi_
		----------------------------------------------------
		Error Output
		------------ 
_eoi_
		cat error_log
cat <<- _eoi_
	#############################################################

	Test 2
	------
		Goal:Testing behaviour when no conditional directives 
			are present but #define is present

		Input
		----- 
_eoi_
		cat test_cases/test2.c
		cat <<- _eoi_
		-----------------------------------------------------
		Output
		------
_eoi_
		./cdpp test_cases/test2.c test_cases/result2.c
		cat test_cases/result2.c
		cat <<- _eoi_
		----------------------------------------------------
		Error Output
		------------ 
_eoi_
		cat error_log
cat <<- _eoi_
	#############################################################

	Test 3
	------
		Goal:Testing comment removal
	
		Input
		----- 
_eoi_
		cat test_cases/test3.c
		cat <<- _eoi_
		-----------------------------------------------------
		Output
		------
_eoi_
		./cdpp test_cases/test3.c test_cases/result3.c
		cat test_cases/result3.c
		cat <<- _eoi_
		----------------------------------------------------
		Error Output
		------------ 
_eoi_
		cat error_log
cat <<- _eoi_
	#############################################################

	Test 4
	------
		Goal:Testing definition of single macro and #ifdef, 
		     #ifndef, #endif for defined and undefined macros
	
		Input
		----- 
_eoi_
		cat test_cases/test4.c
		cat <<- _eoi_
		-----------------------------------------------------
		Output
		------
_eoi_
		./cdpp test_cases/test4.c test_cases/result4.c
		cat test_cases/result4.c
		cat <<- _eoi_
		----------------------------------------------------
		Error Output
		------------ 
_eoi_
		cat error_log
cat <<- _eoi_
	#############################################################

	Test 5
	------
		Goal:Testing #ifdef, #else, #endif when macro is added,
		     removed and added again

		Input
		----- 
_eoi_
		cat test_cases/test5.c
		cat <<- _eoi_
		-----------------------------------------------------
		Output
		------
_eoi_
		./cdpp test_cases/test5.c test_cases/result5.c
		cat test_cases/result5.c
		cat <<- _eoi_
		----------------------------------------------------
		Error Output
		------------ 
_eoi_
		cat error_log
cat <<- _eoi_
	#############################################################

	Test 6
	------
		Goal:Testing #ifndef, #else, #endif when macro is added, 
		     removed and added again

		Input
		----- 
_eoi_
		cat test_cases/test6.c
		cat <<- _eoi_
		-----------------------------------------------------
		Output
		------
_eoi_
		./cdpp test_cases/test6.c test_cases/result6.c
		cat test_cases/result6.c
		cat <<- _eoi_
		----------------------------------------------------
		Error Output
		------------ 
_eoi_
		cat error_log
cat <<- _eoi_
	#############################################################

	Test 7
	------
		Goal:Testing #ifdef #else #endif for multiple defined 
		     macros
		Input
		----- 
_eoi_
		cat test_cases/test7.c
		cat <<- _eoi_
		-----------------------------------------------------
		Output
		------
_eoi_
		./cdpp test_cases/test7.c test_cases/result7.c
		cat test_cases/result7.c
		cat <<- _eoi_
		----------------------------------------------------
		Error Output
		------------ 
_eoi_
		cat error_log
cat <<- _eoi_
	#############################################################

	Test 8
	------
		Goal:Testing #ifdef #else, #endif for multiple undefined 
		     macros

		Input
		----- 
_eoi_
		cat test_cases/test8.c
		cat <<- _eoi_
		-----------------------------------------------------
		Output
		------
_eoi_
		./cdpp test_cases/test8.c test_cases/result8.c
		cat test_cases/result8.c
		cat <<- _eoi_
		----------------------------------------------------
		Error Output
		------------ 
_eoi_
		cat error_log
cat <<- _eoi_
	#############################################################

	Test 9
	------
		Goal:Testing #ifndef #else #endif for multiple defined 
			macros

		Input
		----- 
_eoi_
		cat test_cases/test9.c
		cat <<- _eoi_
		-----------------------------------------------------
		Output
		------
_eoi_
		./cdpp test_cases/test9.c test_cases/result9.c
		cat test_cases/result9.c
		cat <<- _eoi_
		----------------------------------------------------
		Error Output
		------------ 
_eoi_
		cat error_log
cat <<- _eoi_
	#############################################################

	Test 10
	------
		Goal:Testing #ifndef ,#else, #endif for multiple 
			undefined macros

		Input
		----- 
_eoi_
		cat test_cases/test10.c
		cat <<- _eoi_
		-----------------------------------------------------
		Output
		------
_eoi_
		./cdpp test_cases/test10.c test_cases/result10.c
		cat test_cases/result10.c
		cat <<- _eoi_
		----------------------------------------------------
		Error Output
		------------ 
_eoi_
		cat error_log
cat <<- _eoi_
	#############################################################

	Test 11
	-------
		Goal:Testing nested conditions

		Input
		----- 
_eoi_
		cat test_cases/test11.c
		cat <<- _eoi_
		-----------------------------------------------------
		Output
		------
_eoi_
		./cdpp test_cases/test11.c test_cases/result11.c
		cat test_cases/result11.c
		cat <<- _eoi_
		----------------------------------------------------
		Error Output
		------------ 
_eoi_
		cat error_log
cat <<- _eoi_
	#############################################################

	Test 12
	-------
		Goal:Testing mismatched comments

		Input
		----- 
_eoi_
		cat test_cases/test12.c
		cat <<- _eoi_
		-----------------------------------------------------
		Output
		------
_eoi_
		./cdpp test_cases/test12.c test_cases/result12.c
		cat test_cases/result12.c
		cat <<- _eoi_
		----------------------------------------------------
		Error Output
		------------ 
_eoi_
		cat error_log
cat <<- _eoi_
	#############################################################

	Test 13
	-------
		Goal:Testing mismatched conditions, missing #endif

		Input
		----- 
_eoi_
		cat test_cases/test13.c
		cat <<- _eoi_
		-----------------------------------------------------
		Output
		------
_eoi_
		./cdpp test_cases/test13.c test_cases/result13.c
		cat test_cases/result13.c
		cat <<- _eoi_
		----------------------------------------------------
		Error Output
		------------ 
_eoi_
		cat error_log
cat <<- _eoi_
	#############################################################

	Test 14
	-------
		Goal:Testing mismatched conditions, missing opening 
			statement

		Input
		----- 
_eoi_
		cat test_cases/test14.c
		cat <<- _eoi_
		-----------------------------------------------------
		Output
		------
_eoi_
		./cdpp test_cases/test14.c test_cases/result14.c
		cat test_cases/result14.c
		cat <<- _eoi_
		----------------------------------------------------
		Error Output
		------------ 
_eoi_
		cat error_log
cat <<- _eoi_
	#############################################################

	Test 15
	-------
		Goal:Testing missing macros on conditions

		Input
		----- 
_eoi_
		cat test_cases/test15.c
		cat <<- _eoi_
		-----------------------------------------------------
		Output
		------
_eoi_
		./cdpp test_cases/test15.c test_cases/result15.c
		cat test_cases/result15.c
		cat <<- _eoi_
		----------------------------------------------------
		Error Output
		------------ 
_eoi_
		cat error_log
		
echo "#########################################################"
