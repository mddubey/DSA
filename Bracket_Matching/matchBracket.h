typedef struct{
	int isError;
	int index;
	char bracket;
}ErrorMsg;

ErrorMsg areBracketsMatching(const char* input);
