#define NULL '\0'
#define MAX_BUF_SIZE 254
#include "string.h"

void CopyString(char cSource[],char cDestination[]){
    
    unsigned char ucCharacterCounter;
        
    for(ucCharacterCounter=0;cSource[ucCharacterCounter]!=NULL;ucCharacterCounter++){
        cDestination[ucCharacterCounter]=cSource[ucCharacterCounter];
    }
    cDestination[ucCharacterCounter]=NULL;
}

enum CompResult eCompareString(char pcStr1[], char pcStr2[]){
    
    unsigned char ucCharacterCounter;
    
    for(ucCharacterCounter=0; pcStr1[ucCharacterCounter]!=NULL; ucCharacterCounter++){
        if(pcStr1[ucCharacterCounter]!=pcStr2[ucCharacterCounter]){
            return DIFFERENT;
        }
    }
    if(pcStr2[ucCharacterCounter]==NULL){
        return EQUAL;
    }
    return DIFFERENT;
}

void AppendString(char pcSourceStr[],char pcDestinationStr[]){
    
    unsigned char ucCharacterCounter;
    
    for(ucCharacterCounter=0;pcDestinationStr[ucCharacterCounter]!=NULL;ucCharacterCounter++){
        continue;
    }
    CopyString(pcSourceStr,&pcDestinationStr[ucCharacterCounter]);
}

void ReplaceCharactersInString(char pcString[],char cOldChar,char cNewChar){
    
    unsigned char ucCharacterCounter;
    
    for(ucCharacterCounter=0; pcString[ucCharacterCounter]!=NULL; ucCharacterCounter++){
        if(pcString[ucCharacterCounter]==cOldChar){
            pcString[ucCharacterCounter]=cNewChar;
        }
    }
}

void UIntToHexStr (unsigned int uiValue,char pcStr[]){
    unsigned char ucTetradCounter;
    unsigned int uiTetradValue=uiValue;
	pcStr[0]='0';
    pcStr[1]='x';
    pcStr[6]=NULL;
    for(ucTetradCounter=0;ucTetradCounter<4;ucTetradCounter++)
    {
        uiTetradValue = uiValue ;
        uiTetradValue=((uiTetradValue>>(ucTetradCounter*4))&0xF);
        //printf("%d\n", uiTetradValue);
        if(uiTetradValue<=9){
            pcStr[5-ucTetradCounter]=uiTetradValue+'0';
        }
        else{
            pcStr[5-ucTetradCounter]='A'+(uiTetradValue-10);
        }
}
}

enum Result eHexStringToUInt(char pcStr[],unsigned int *puiValue){
	char cSingleCharacter;
    char cResultCharacter;
	unsigned char ucCharacterCounter;	
	*puiValue=0;
    if(pcStr[0]!='0' || pcStr[1]!='x' || pcStr[2]==NULL){
        return ERROR;
    }
    for(ucCharacterCounter=2;pcStr[ucCharacterCounter]!=NULL;ucCharacterCounter++){
        cSingleCharacter=pcStr[ucCharacterCounter];
        if(ucCharacterCounter>6){
            return ERROR;
        }
        else if(cSingleCharacter>='0' && cSingleCharacter<='9'){
            cResultCharacter=cSingleCharacter-'0';
        }
        else if(cSingleCharacter>='A' && cSingleCharacter<='F'){
            cResultCharacter=cSingleCharacter-'A'+10;
        }
        else return ERROR;
        *puiValue=(unsigned int)(*puiValue<<4|cResultCharacter);
    }
    return OK;
}

void AppendUIntToString (unsigned int uiValue, char pcDestinationStr[]){
    unsigned char ucCharacterCounter;
    for(ucCharacterCounter=0;pcDestinationStr[ucCharacterCounter]!=NULL;ucCharacterCounter++){
        ;
    }
    UIntToHexStr(uiValue,&pcDestinationStr[ucCharacterCounter]);
}