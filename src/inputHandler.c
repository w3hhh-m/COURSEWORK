#include <stdio.h>
#include <wchar.h>
#include <stdlib.h>
#include <wctype.h>

#include "structures.h"

Sentence getSentence(int* newLineCounter){

    wchar_t symbol; 

    Word tempWord;
    Sentence tempSentence;

    int tempSentenceIndex = 0, tempSentenceBuffer = 2;
    int tempWordCounter = 0, tempWordCounterBuffer = 2;
    int tempWordIndex = 0, tempWordBuffer = 2;
    int followingCharsIndex = 0, followingCharsBuffer = 2;
    int isEnded = 0, isFirst = 1;

    tempWord.chars = malloc(sizeof(wchar_t)*tempWordBuffer);
    tempWord.followingChars = malloc(sizeof(wchar_t)*followingCharsBuffer);
    tempSentence.chars = malloc(sizeof(wchar_t)*tempSentenceBuffer);
    tempSentence.words = malloc(sizeof(Word)*tempWordCounterBuffer);

    do{

        symbol = getwchar();
        
        if (symbol == '\n'){
            (*newLineCounter)++;
            if (*newLineCounter == 2){
                break;
            }
        }
        else{
            newLineCounter = 0;
        }


        if (tempSentenceIndex==tempSentenceBuffer){
            tempSentenceBuffer *= 2;
            tempSentence.chars = realloc(tempSentence.chars, sizeof(wchar_t)*tempSentenceBuffer);
        }
        if (tempWordIndex==tempWordBuffer){
            tempWordBuffer *= 2;
            tempWord.chars = realloc(tempWord.chars, sizeof(wchar_t)*tempWordBuffer);
        }
        if (followingCharsIndex==followingCharsBuffer){
            followingCharsBuffer *= 2;
            tempWord.followingChars = realloc(tempWord.followingChars, sizeof(wchar_t)*followingCharsBuffer);
        }
        if (tempWordCounter==tempWordCounterBuffer){
            tempWordCounterBuffer *= 2;
            tempSentence.words = realloc(tempSentence.words, sizeof(Word)*tempWordCounterBuffer);
        }


        if (isFirst==1 && iswspace(symbol)){
            continue;
        }
        isFirst = 0;

        if (!iswpunct(symbol)&&!iswspace(symbol)&&isEnded!=1){
            tempWord.chars[tempWordIndex++] = symbol;
            tempSentence.chars[tempSentenceIndex++] = symbol;
        }
        else if(!iswpunct(symbol)&&!iswspace(symbol)&&isEnded==1){
            isEnded = 0;
            tempWord.chars[tempWordIndex] = L'\0';
            tempWord.len = tempWordIndex-1;
            tempWord.followingChars[followingCharsIndex] = L'\0';
            tempWord.followingLen = followingCharsIndex -1;
            tempSentence.words[tempWordCounter++] = tempWord;

            tempWordIndex = 0, followingCharsIndex = 0;
            tempWordBuffer = 2, followingCharsBuffer = 2;
            tempWord.chars = calloc(tempWordBuffer, sizeof(wchar_t));
            tempWord.followingChars = calloc(followingCharsBuffer, sizeof(wchar_t));

            tempWord.chars[tempWordIndex++] = symbol;
            tempSentence.chars[tempSentenceIndex++] = symbol;
        } 
        else {
            isEnded = 1;
            tempWord.followingChars[followingCharsIndex++] = symbol;
            tempSentence.chars[tempSentenceIndex++] = symbol;
            
            if (symbol == L'.'){
                tempWord.chars[tempWordIndex] = L'\0';
                tempWord.len = tempWordIndex-1;
                tempWord.followingChars[followingCharsIndex] = L'\0';
                tempWord.followingLen = followingCharsIndex -1;

                tempSentence.chars[tempSentenceIndex] = L'\0';
                tempSentence.len = tempSentenceIndex-1;
                tempSentence.words[tempWordCounter] = tempWord;
                tempSentence.wordsCounter = tempWordCounter;

                return tempSentence;
            }
        }
    } while(symbol != L'.');
}

Text getText(){
    int newLineCounter = 0;
    int textIndex = 0, textBuffSize = 2;

    Text rawText;
    rawText.sentences = malloc(textBuffSize*sizeof(Sentence));

    Sentence tempSentence;

    while(1){
        tempSentence = getSentence(&newLineCounter);
        if (newLineCounter == 2){
            break;
        }
        else{
            newLineCounter = 0;
        }
        if (textIndex == textBuffSize){
            textBuffSize *= 2;
            rawText.sentences = realloc(rawText.sentences, textBuffSize*sizeof(Sentence));
        }
        rawText.sentences[textIndex++] = tempSentence;
    }
    textIndex--;


    int isUnique[textIndex];
    for (int i = 0; i <= textIndex; i ++){
        isUnique[i] = 1;
    }

    for(int i = 0; i <= textIndex; i++){
        for (int j = i+1; j <= textIndex; j++){
            if (!wcscasecmp(rawText.sentences[i].chars, rawText.sentences[j].chars)){
                isUnique[j] = 0;
            }
        }
    }

    int uniqueIndex = 0;
    Text uniqueText;

    uniqueText.sentences = malloc(textIndex*sizeof(Sentence));

    for (int i = 0; i <= textIndex; i++){
        if (isUnique[i] == 1){
            uniqueText.sentences[uniqueIndex++] = rawText.sentences[i];
        }
    }

    uniqueText.sentenceCounter = uniqueIndex-1;

    return uniqueText;
}

int getTask(){
    int choice;
    wscanf(L"%d", &choice);
    return choice;
}