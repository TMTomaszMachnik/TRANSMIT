#include "string.h"
#include "command_decoder.h"

struct Keyword asKeywordList[MAX_KEYWORD_NR]={
    {CALLIB,"callib"},
    {GOTO, "goto" },			
		{CALC, "calc"}
};

extern struct Token asToken[MAX_TOKEN_NR];
extern unsigned char ucTokenNr;

unsigned char ucFindTokensInString (char *pcString){

	enum State{TOKEN, DELIMETER};
    	enum State eState = TOKEN;
    	unsigned char ucCharacterCounter;
    	unsigned char ucTokenTableIndex=0;

    	for(ucCharacterCounter=0;;ucCharacterCounter++){
    		switch(eState){
    			case TOKEN:{
    		    		if(ucTokenTableIndex==MAX_TOKEN_NR){
      	          		return ucTokenTableIndex;
      	       	}
      	      	else if(*pcString==' '){
      	          		eState=DELIMETER;
      	      	}
      	     		else if(*pcString==NULL){
      	          		return ucTokenTableIndex;
      	      	}
      	      	else if(ucCharacterCounter==0){
      	          		asToken[ucTokenTableIndex].uValue.pcString=pcString;
      	          		ucTokenTableIndex++;
      	          		eState=TOKEN;
      	      	}
      	      	else{
      	          		eState=TOKEN;
      	      	}
      	      break;
      	  	}
      	  	case DELIMETER:{
      	      	if(*pcString==' '){
      	         		eState=DELIMETER;
      	      	}
      	      	else if(*pcString==NULL){
      	          		return ucTokenTableIndex;
      	      	}
      	      	else{
      	          		asToken[ucTokenTableIndex].uValue.pcString=pcString;
      	          		ucTokenTableIndex++;
      	         		eState=TOKEN;
      	      	}
      	      break;
      	 	}	
		}
    pcString++;
    }
}

enum Result eStringToKeyword(char pcStr[],enum KeywordCode *peKeywordCode){
    
	unsigned char ucKeywordCounter;
    	
	for(ucKeywordCounter=0;ucKeywordCounter<MAX_KEYWORD_NR;ucKeywordCounter++){
    		if(eCompareString(pcStr, asKeywordList[ucKeywordCounter].cString)==EQUAL){
            	*peKeywordCode=asKeywordList[ucKeywordCounter].eCode;
            	return OK;
      	}
    	}
    	return ERROR;
}

void DecodeTokens(){

	unsigned char ucTokenCounter;
	char *cCurrentToken;
 	unsigned int uiValue;
	union TokenValue uValue;
	
	enum KeywordCode peKeywordCode;
   	enum TokenType eType;
    
    	for(ucTokenCounter=0;ucTokenCounter<ucTokenNr;ucTokenCounter++){
        
      	cCurrentToken=asToken[ucTokenCounter].uValue.pcString;
        
        	if(eStringToKeyword(cCurrentToken,&peKeywordCode)==OK){
            	eType=KEYWORD;
            	uValue.eKeyword=peKeywordCode;
        	}
        	else if(eHexStringToUInt(cCurrentToken,&uiValue)==OK){
        	    eType=NUMBER;
        	    uValue.uiNumber=uiValue;
        	}
        	else{
        	    eType=STRING;
        	    uValue.pcString=cCurrentToken;
        	}
        	asToken[ucTokenCounter].eType=eType;
        	asToken[ucTokenCounter].uValue=uValue;
    	}
}
void DecodeMsg(char *pcString){
    
	unsigned char ucTokenCounter;
	
	ucTokenNr=ucFindTokensInString(pcString);
    	for(ucTokenCounter=0;ucTokenCounter<ucTokenNr;ucTokenCounter++){
      	ReplaceCharactersInString(asToken[ucTokenCounter].uValue.pcString,' ', NULL);
    	}
    	DecodeTokens();
}

