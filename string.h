enum Result {OK,ERROR};
enum CompResult {DIFFERENT, EQUAL};

void UIntToHexStr (unsigned int uiValue,char pcStr[]);
enum Result eHexStringToUInt(char pcStr[],unsigned int *puiValue);
void AppendUIntToString (unsigned int uiValue, char pcDestinationStr[]);

void CopyString(char cSource[],char cDestination[]);
enum CompResult eCompareString(char pcStr1[], char pcStr2[]);
void AppendString(char pcSourceStr[],char pcDestinationStr[]);
void ReplaceCharactersInString(char pcString[],char cOldChar,char cNewChar);