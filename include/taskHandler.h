#ifndef TASKHANDLER_H
#define TASKHANDLER_H

#include <wchar.h>
#include "structures.h"

void logEditedCertainWords(Text* text);
int findWideSubstringIndex(const wchar_t *wideStr, const wchar_t *subStr);
void logCertainSentences(Text text);
int sentenceCmp(const void* a, const void* b);
Text sortSentencesByWords(Text text);
void removeShortSentences(Text* text);

#endif