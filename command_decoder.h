#define NULL '\0'
#define MAX_TOKEN_NR 3
#define MAX_KEYWORD_NR 3
#define MAX_KEYWORD_STRING_LTH 10

enum KeywordCode {CALLIB,GOTO,CALC};
enum TokenType {KEYWORD, NUMBER, STRING};

union TokenValue{
    	enum KeywordCode eKeyword;
    	unsigned int uiNumber;
    	char* pcString;
};

struct Token{
    	enum TokenType eType;
    	union TokenValue uValue;
};

struct Keyword{
	enum KeywordCode eCode;
    	char cString[MAX_KEYWORD_STRING_LTH + 1];
};

unsigned char ucFindTokensInString (char *pcString);
enum Result eStringToKeyword(char pcStr[],enum KeywordCode *peKeywordCode);
void DecodeTokens(void);
void DecodeMsg(char *pcString);