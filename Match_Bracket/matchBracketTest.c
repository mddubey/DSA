#include "testUtils.h"
#include "matchBracket.h"
#include <stdlib.h>
//create setup, tearDown, fixtureSetup, fixtureTearDown methods if needed

void test_matchs_all_brackets_of_input_string(){
	char* input = "[{(ram)dfas}]";
	ErrorMsg result;
	result = areBracketsMatching(input);
	ASSERT(0==result.isError);
};

void test_gives_error_if_there_is_nothing_on_stack_when_closing_bracket_occurs(){
	char* input = "}";
	ErrorMsg result;
	result = areBracketsMatching(input);
	ASSERT(1==result.isError==result.index);
	ASSERT('}'==result.bracket);
}

void test_gives_error_if_the_opening_bracket_doesnot_match(){
	char* input = "Digs(Raj)Naam]";
	ErrorMsg result;
	result = areBracketsMatching(input);
	ASSERT(result.isError==1);
	ASSERT(result.bracket==']');
	ASSERT(result.index==14);
}

void test_gives_error_if_anything_left_on_stack_on_the_end_of_string(){
	char* input = "([Digs(Raj)Naam]";
	ErrorMsg result;
	result = areBracketsMatching(input);
	ASSERT(result.isError==1);
	ASSERT(result.bracket=='\0');
	ASSERT(result.index==0);
}