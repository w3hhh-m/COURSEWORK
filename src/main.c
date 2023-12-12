#include <stdio.h>
#include <wchar.h>
#include <stdlib.h>
#include <wctype.h>
#include <locale.h>

#include "structures.h"
#include "inputHandler.h"
#include "logHandler.h"
#include "taskHandler.h"

int main(){
    setlocale(LC_ALL, "");
    logCwInfo();
    int task = getTask();
    Text text;
    switch(task){
        case 0:
            text = getText();
            logText(text);
            break;
        case 1:
            text = getText();
            logEditedCertainWords(&text);
            break;
        case 2:
            text = getText();
            logCertainSentences(text);
            break;
        case 3:
            text = getText();
            text = sortSentencesByWords(text);
            logText(text);
            break;
        case 4:
            text = getText();
            removeShortSentences(&text);
            logText(text);
            break;
        case 5:
            logHelp();
            break;
    }
}