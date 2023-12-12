#include <stdio.h>
#include <wchar.h>
#include <stdlib.h>
#include <wctype.h>

#include "structures.h"

void logEditedCertainWords(Text* text){
    const wchar_t* numbers[] = { L"ноль", L"один", L"два", L"три", L"четыре", L"пять", L"шесть", L"семь", L"восемь", L"девять" };
    for (int i = 0; i <= text->sentenceCounter; i++){
        Sentence* tempSentence = &(text->sentences[i]);

        for (int j = 0; j <= tempSentence->wordsCounter; j++){
            Word* tempWord = &(tempSentence->words[j]);

            wchar_t lastSymbol = tempWord->chars[tempWord->len];

            if (iswdigit(lastSymbol)){
                tempWord->chars[tempWord->len] = L'\0';
                wchar_t number = lastSymbol - L'0';

                wprintf(L"%ls",tempWord->chars);
                if (number >= 0 && number <= 9) {
                    wprintf(L"%ls", numbers[number]);
                }
                wprintf(L"%ls",tempWord->followingChars);
            }
            else{
                wprintf(L"%ls%ls",tempWord->chars, tempWord->followingChars);
            }
        }
        wprintf(L"\n");
    }
}

int findWideSubstringIndex(const wchar_t *wideStr, const wchar_t *subStr){
    const wchar_t *result = wcsstr(wideStr, subStr);

    if (result != NULL) {
        return result - wideStr;
    } else {
        return -1;
    }
}

void logCertainSentences(Text text){

    for (int i = 0; i <= text.sentenceCounter; i++){
        int index = 0, endIndex = 0, flag = 0;
        Word tempWord;

        if (i!=0){
            tempWord = text.sentences[i-1].words[text.sentences[i-1].wordsCounter];
        }
        else{
            tempWord = text.sentences[text.sentenceCounter].words[text.sentences[text.sentenceCounter].wordsCounter];
        }

        for (int j = 0; j <= text.sentences[i].wordsCounter; j++){
            if (wcscmp(tempWord.chars, text.sentences[i].words[j].chars)==0){
                flag = 1;
                index = findWideSubstringIndex(text.sentences[i].chars, tempWord.chars);
                endIndex = index + wcslen(tempWord.chars);
            }
        }

        if (flag == 1){
            for (int k = 0; k < index; k++){
                wprintf(L"%lc", text.sentences[i].chars[k]);
            }
            for (int k = index; k < endIndex; k++){
                wprintf(L"\033[31m%lc\033[0m", text.sentences[i].chars[k]);
            }
            for (int k = endIndex; k <= text.sentences[i].len; k++){
                wprintf(L"%lc", text.sentences[i].chars[k]);
            }
            wprintf(L"\n");
        }
    }
}

int sentenceCmp(const void* a, const void* b){
    Sentence* sentenceA = (Sentence *) a;
    Sentence* sentenceB = (Sentence *) b;
    int result = sentenceB->wordsCounter - sentenceA->wordsCounter;
    return result;
}

Text sortSentencesByWords(Text text){
    qsort(text.sentences, text.sentenceCounter, sizeof(Sentence), sentenceCmp);
    return text;
}

void removeShortSentences(Text* text){
    int newSentenceCounter = 0;
    for (int i = 0; i <= text->sentenceCounter; i++) {
        if (text->sentences[i].wordsCounter+1 > 2) {
            text->sentences[newSentenceCounter++] = text->sentences[i];
        }
    }
    text->sentenceCounter = newSentenceCounter-1;
}
