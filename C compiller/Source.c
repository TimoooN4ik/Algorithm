#include <math.h>
#include <stdio.h>
#include <string.h>
#include <malloc.h>
#include <stdbool.h>        //correct since format c99

int maxLength = 0;

int changeComment() {
    int i = 0, n = 180, comCount = 0;
    char str[180];
    char* estr;
    bool comment = false, start = false;
    FILE* in = fopen("fileStart.c", "r"), * out = fopen("file.c", "w");     //открываем файл на чтение, запись
    if (in == NULL) {
        printf("error");
        return 0;
    }
    rewind(out);
    while ((estr = fgets(str, sizeof(str), in)) != NULL) {
        i = 0;
        while (str[i] != '\0')                      //считываем построчно, пока не найдем конец строки
        {
            if (str[i] == '/' && str[i + 1] == '*' && !comment) {       //ищем совпадение по два последовательным символам / и *
                str[i + 1] = '/';
                comment = true;
                start = true;
                comCount = 0;
            }
            if (str[i] == '*' && str[i + 1] == '/') {
                str[i] = ' ';
                str[i + 1] = ' ';

                int j = 0;
                while (str[2 + j] != '\0')
                    str[2 + j] = str[3 + j++];
                start = false;
            }
            i++;
        }
        if (comment && comCount++ > 0) {    //Если находим / и * последовательно, до момента, пока не найдем последовательность * и / - выставляем в начало строки //
            if (start) {
                comCount++;
                fprintf(out, "%c", '/');
                fprintf(out, "%c", '/');
                int j = 0;
                do {
                    fprintf(out, "%c", str[j]);
                    j++;
                } while (str[j] != '\0');
            }
            if (!start) {
                if (comCount != 2) {
                    fprintf(out, "%c", '/');
                    fprintf(out, "%c", '/');
                }
                comment = false;
                fputs(str, out);
            }
        }
        else
            fputs(str, out);
    }
    fclose(in);
    fclose(out);
    
    return 1;
}

int checkAndReplaceSymbols()
{
    int i = 0, c, row = 0, libs = 0, countOfSpace = 0, length = 0;
    bool space = false, enter = false, dSpace = false;
    FILE* in, * out;
    if ((in = fopen("file.c", "r")) == NULL) {
        printf("input file empty\n");
        return 0;
    }
    if ((out = fopen("fileOut.c", "w")) == NULL) {
        printf("Output file not exist");
        return 0;
    }
    rewind(out);
    while ((c = fgetc(in)) != EOF) {
        
        if (c != '\n')
            length++;
        else
            if (length > maxLength)
                maxLength = length;

        i++;

        if (c == ')') {
            fprintf(out, "%c", c);
            space = false;
            enter = false;
            countOfSpace = 0;
            continue;
        }
        if (c == '{' || c == '=' || c == '+' || c == '/' || c == '*' || c == '<' || c == '>' || c == ',' || c == '-' || c == '!') {
            if (row >= libs && !space && !enter && c != ',' && c != '{')
                fputc(' ', out);

            if (c == '{' && !enter) {
                fputc('\n', out);
            }

            space = false;
            enter = false;
            dSpace = false;

            fprintf(out, "%c", c);

            if (row > libs && (c == '=' || c == '+' || c == '/' || c == '*' || c == '<' || c == '>' || c == ',' || c == '-')) {
                fputc(' ', out);
                space = true;
                dSpace = true;
            }
            countOfSpace = 0;
            continue;
        }
        if (c == '}') {
            if(!enter)
                fputc('\n', out);
            space = false;
            enter = false;
            dSpace = false;
            fprintf(out, "%c", c);
            countOfSpace = 0;
            continue;
        }
        if (c == ' ') {
            space = true;
            if(!dSpace)
                fprintf(out, "%c", c);
            dSpace = false;
            countOfSpace++;
            continue;
        }
        if (c == '\n') {
            row++;
            space = false;
            enter = true;
            dSpace = false;
            fprintf(out, "%c", c);
            countOfSpace = 0;
            continue;
        }
        if (c == '#') {
            libs++;
            space = false;
            enter = false;
            dSpace = false;
            fprintf(out, "%c", c);
            countOfSpace = 0;
            continue;
        }
        if (c == ';') {
            space = false;
            enter = false;
            countOfSpace = 0;
            fprintf(out, "%c", c);
            fputc(' ', out);
            dSpace = true;
            continue;
        }
        space = false;
        enter = false;
        dSpace = false;
        fprintf(out, "%c", c);
        countOfSpace = 0;
    }
    fclose(in);
    //ftruncate(fileno(out), i);
    fclose(out);
    return 1;
}

int cleancleanExtraSpaces()
{
    int i = 0, n = 180;
    char str[180];
    char *estr;
    FILE* in = fopen("fileOut.c", "r"), * out = fopen("fileOut2.c", "w");
    if (in == NULL || out == NULL) {
        printf("error");
        return 0;
    }
    rewind(out);
    while ((estr = fgets(str, sizeof(str), in)) != NULL) {
        i = 0;
        while (str[i] != '\0') {        //когда добавляли лишние пробелы, для ++, --, // и символы внутри комментариев обросли лишними пробелами
        //Находим комбинации " - - ", " + + ", " / / " и удаляем лишнее пробелы

            if (i > 0 && str[i] == '-' || str[i] == '+' || str[i] == '/') {
                if (str[i - 1] == ' ' && str[i + 1] == ' ' && str[i + 2] == str[i]) {
                    str[i - 1] = str[i];
                    str[i + 2] = ' ';
                    if (str[i + 3] == ' ')
                        for (int j = i + 1; str[j] != '\0' || j < n - 2; j++)
                            str[j] = str[j + 3];
                    else
                        for (int j = i + 1; str[j] != '\0' || j < n - 2; j++)
                            str[j] = str[j + 2];
                }
            }
            if (i == 0 && str[i] == '-' || str[i] == '+' || str[i] == '/') {
                if (str[i + 1] == ' ' && str[i + 3] == ' ' && str[i + 2] == str[i]) {
                    str[i + 1] = str[i];
                    str[i + 2] = ' ';
                    for (int j = i + 2; str[j] != '\0' || j < n - 2; j++)
                        str[j] = str[j + 2];
                }
            }
            if (str[i] == '=') {
                if (str[i + 1] == ' ' && str[i + 2] == str[i]) {
                    str[i + 1] = str[i];
                    str[i + 2] = ' ';
                    for (int j = i + 2; str[j] != '\0' || j < n - 2; j++)
                        str[j] = str[j + 1];
                }
            }
            if (str[i] == '!') {
                if (str[i + 1] == ' ' && str[i + 2] == '=') {
                    str[i + 1] = '=';
                    str[i + 2] = ' ';
                    for (int j = i + 2; str[j] != '\0' || j < n - 2; j++)
                        str[j] = str[j + 1];
                }
            }
            i++;
        }
        strncpy(str, str, i);
        fputs(str, out);
    }
    fclose(in);
    fclose(out);

    //free(estr);
    return 1;
}

int infCycle(char str[180], int cycleType)
{
    if (cycleType) {        //1 - while, 0 - for
        int i = 0, position = 0;
        while (str[i] != '\0')
        {
            if (str[i] == '=' || str[i] == '>' || str[i] == '<')
                return 0;
            
            if (str[i] == 't' && str[i + 1] == 'r' && str[i + 2] == 'u' && str[i + 3] == 'e') {
                return -1;
            }
            i++;
        }
    }
    else {
        int i = 0, sign = 0, position = 0;
        while (str[i] != '\0')
        {
            switch (str[i])
            {
            case ';':
                sign++;
                if(sign < 2)
                    position = i;
                break;
            default:
                break;
            }

            if (sign == 2) {
                if (i - position <= 3) {
                    position = 0;
                    return -1;
                }
            }

            i++;
        }
        return 0;
    }
    return -1;
}

int writeToReport(int length, char str[180], bool class, int rows)     //переменная class указывает класс объекта. true - метод, false - поле
{
    int i = 0, j = 0, row = 0, countOfRec = 0, intoTheComm = 0, bracketF = 0, tmpCounter = 0, checkFuncNameInto = 0, cycleUp = 0, maxCycleUp = 0;
    int numOfInfCycle = 0;
    FILE* in = fopen("report.txt", "a+") , * read = fopen("fileOut2.c", "r");
    char name[100];
    char* estr;
    if (in == NULL || read == NULL) {
        printf("error");
        return 0;
    }

    if (class) {        //рассматриваемый объект - метод. проверям рекурсию и максимальную вложенность циклов
        for (int i = 0; i < length; i++)
            name[i] = str[i];
        name[length] = '(';
        bool cDo = false;       //флаг, что цикл просто while, а не конструкция do-while
        bool cycle = false;

        while ((estr = fgets(str, 180, read)) != NULL) {
            i = 0, j = 0, intoTheComm = 0, checkFuncNameInto = 0;

            while (str[i] != '\0') {           //зашли в нужную функцию, проверяем на наличие рекурсии

                switch (str[i])
                {
                case '/':
                    intoTheComm++;
                    break;
                case '{':
                    bracketF++;         //зашли в функцию/цикл/условие...
                    if (cycle && intoTheComm == 0)
                        cycleUp++;
                    break;
                case '}':
                    bracketF--;         //вышли из функции/цикла/условия...
                    if (cycle && intoTheComm == 0) {
                        if(maxCycleUp < cycleUp)
                            maxCycleUp = cycleUp;
                        cycleUp--;
                        if (cycleUp == 0)
                            cycle = false;
                    }
                    break;
                default:
                    break;
                }

                if (row >= rows) {      //в заново открытом файле нужно чтобы количество пройденых строк было не меньше строки, в которой нашли имя функции
                    
                    if (i + 2 < 180 && str[i] == 'f' && str[i + 1] == 'o' && str[i + 2] == 'r') {
                        cycle = true;
                        if (infCycle(&str[0], 0) == -1)
                            numOfInfCycle++;
                    }
                    else if (i + 4 < 180 && !cDo && str[i] == 'w' && str[i + 1] == 'h' && str[i + 2] == 'i' && str[i + 3] == 'l' && str[i + 4] == 'e') {
                        if (infCycle(&str[0], 1) == -1)
                            numOfInfCycle++;
                    }
                    /*else if (i + 1 < 180 && str[i] == 'd' && str[i + 1] == 'o') {
                        //if (infCycle(&str[0], 1) == -1)
                            //numOfInfCycle++;
                    }*/

                    int k = i;
                    j = 0;
                    while (name[j] != '(' && j < length + 1) {
                        if (name[j] == str[k] && intoTheComm == 0) {    //поиск имени функции внутри ее тела
                            j++;
                            k++;
                            if(j == length)                             //если имя полностью совпало - записываем как рекурсивный вызов
                                checkFuncNameInto++;
                        }
                        else
                            break;
                    }
                    
                }
                i++;
            }
            if (checkFuncNameInto > 0)
                countOfRec++;
            row++;

            if (bracketF == 0 && row > rows)
                break;
        }
        fprintf(in, "\n%d recursive calls in a function: ", countOfRec);
        for(int i = 0; i < length; i++)
            fprintf(in, "%c", name[i]);
        fprintf(in, "%c", '\n');

        fprintf(in, "maximum of loops: %d\n", maxCycleUp);

        fprintf(in, "%d endless cycles\n", numOfInfCycle);
    }
    else {              //рассматриваемый объект - поле. инициализацию переменных
        for (int i = 0; i < length; i++)
            name[i] = str[i];
        name[length] = '(';

        for (int i = 0; i < length; i++)    //записываем переменную как не инициализированную
            fprintf(in, "%c", name[i]);
        fprintf(in, " - not initialized variable\n");
        numOfInfCycle = 0;
    }

    fclose(in);
    fclose(read);
}

int nameLength(char str[180], int bracketF, int rows)
{
    int i = 0, varNameLgth = 0;
    bool initVar = false;
    while (str[i] != '\0') {
        if (str[i] == ' ') {
            if (str[i + 1] == '(') {
                if(bracketF == 0 && i > 0)
                    writeToReport(i, &str[0], true, rows);
            }
        }
        else if (str[i] == '(')
            if (bracketF == 0)                          //объявления функций внутри функции
                writeToReport(i, &str[0], true, rows);      //нашли объявленную функцию. Отправляем для записи имени функции и внутри тела функции ее имени, для проверки на рекурсию
        if (str[i] == '=' && bracketF != 0) {
            initVar = true;                     //нашли объявленную переменную. Далее проверям, чтобы после каждой переменной шел знак =
            varNameLgth = i;
        }
        if (str[i] == ',' || str[i] == ';' && bracketF != 0) {
            if(!initVar)
                writeToReport(i - varNameLgth, &str[varNameLgth], false, rows);     //Если нет = после переменно - записываем ее как не инициализированную
            else
                initVar = false;
            varNameLgth = i+2;
            if (str[i] == ';')
                return 0;
        }
        i++;
    }
    return 0;
}

int checkRecurseFunc()
{
    int i = 0, n = 180, bracketF = 0, bracketR = 0, lengthNamesVariable = 0, intoTheComm = 0, rows = 0;
    bool quot = false, apos = false;
    char str[180];
    char tmpStr[180];
    char* estr;
    FILE* in = fopen("fileOut2.c", "r");
    if (in == NULL) {
        printf("error");
        return 0;
    }
    while ((estr = fgets(str, sizeof(str), in)) != NULL) {
        i = 0;
        intoTheComm = 0;
        rows++;
        for (int k = 0; k < 180; k++)
            tmpStr[k] = str[k];
        while (str[i] != '\0')      //дополнительные флаги, для понимания ситуации
        {
            switch (str[i])
            {
            case '\'':
                apos = !apos;       //отвечает, за то, что зашли в ковычки и не стоит больше рассматривать эту строку для поиска типов данных, пока не выйдем из ковычек
                break;
            case '/':
                intoTheComm++;      //отвечает, за то, что зашли в комментарий и не стоит больше рассматривать эту строку для поиска типов данных
                break;
            case '{':
                bracketF++;         //зашли в функцию/цикл/условие...
                break;
            case '}':               //bracketF отвечает за то, что мы нашли тип данных для объявления функции
                bracketF--;         //вышли из функции/цикла/условия...
                break;
            case '(':
                bracketR++;         //зашли в аргументы функции
                break;
            case ')':
                bracketR--;         //вышли из аргументов функции
                break;
            case '"':
                quot = !quot;
                break;
            default:
                break;
            }

            //ищем последовательность симовлов по объявлению типов int void double float char bool
            if (!apos && intoTheComm == 0 && !quot && bracketR == 0 && str[i] == 'i' || str[i] == 'v' || str[i] == 'd' || str[i] == 'f' || str[i] == 'c' || str[i] == 'b') {
                if (str[i + 1] == 'n' || str[i + 1] == 'o' || str[i + 1] == 'l' || str[i + 1] == 'h') {
                    if (str[i + 2] == 't' || str[i + 2] == 'o' || str[i + 2] == 'i' || str[i + 2] == 'u' || str[i + 2] == 'a') {    //int
                        if (str[i + 3] == ' ') {
                            //нашли int
                            lengthNamesVariable = nameLength(&tmpStr[i + 4], bracketF, rows);
                        }
                        else if (str[i + 3] == 'd' || str[i + 3] == 'b' || str[i + 3] == 'a' || str[i + 3] == 'r' || str[i + 3] == 'l') {     //char void bool
                            if (str[i + 4] == ' ') {
                                //нашли void or char
                                    lengthNamesVariable = nameLength(&tmpStr[i + 5], bracketF, rows);
                            }
                            else if (str[i + 4] == 'l' || str[i + 4] == 't') {   //float
                                if (str[i + 5] == ' ') {
                                    //нашли float
                                    lengthNamesVariable = nameLength(&tmpStr[i + 6], bracketF, rows);
                                }
                                else if (str[i+5] == 'e' && str[i+6] == ' ') {                      //double
                                    //нашли double
                                    lengthNamesVariable = nameLength(&tmpStr[i + 7], bracketF, rows);
                                }
                            }
                        }
                    }
                }
            }
            i++;
        }
    }
    fclose(in);
    return 1;
}

int lastCheck()
{
    int i = 0, n = 180, border = 0;
    bool comment = false, quot = false;
    char str[180];
    char* estr;
    FILE* in = fopen("fileOut2.c", "r"), * out = fopen("fileEnd.c", "w");
    if (in == NULL || out == NULL) {
        printf("error");
        return 0;
    }
    while ((estr = fgets(str, sizeof(str), in)) != NULL) {
        i = 0;
        while (str[i] != '\0')
        {
            switch (str[i])
            {
            case '"':
                quot = !quot;
                break;
            case '/':
                comment = true;
                break;
            case '{':
                if (!comment && !quot) {
                    border++;
                    int position = pow(2, border);
                    if (border > 1 && str[0] != ' ') {          //добавляем пропущенные пробелы, после замены типа комментариев
                        for (int j = 0; j < position; j++)
                            fputc(' ', out);
                    }
                }
                break;
            case '}':
                if (!comment && !quot) {
                    int position = pow(2, border);
                    if (border > 1 && str[0] != ' ') {
                        for (int j = 0; j < position; j++)
                            fputc(' ', out);
                    }
                    border--;
                }
                break;
            default:
                break;
            }
            i++;
        }
        comment = false;
        fputs(str, out);
    }
    fclose(in);
    fclose(out);
    return 0;
}

void writeAllOnOneFile()            //запись все в один файл. Исправленный код и отчет
{
    int i = 0;
    char str[180];
    char* estr;
    FILE* in = fopen("report.txt", "r"), * out = fopen("fileEnd.c", "a+");
    if (in == NULL || out == NULL) {
        printf("error");
        return 0;
    }

    fprintf(out, "\n//---------------------------------------------------\n");

    while ((estr = fgets(str, sizeof(str), in)) != NULL) {
        fputs(str, out);
    }

    fclose(in);
    fclose(out);
}

int main()
{
    remove("report.txt");
    if(changeComment())                 //преобразуем комментарии к виду //
        printf("comments +\n");

    if (checkAndReplaceSymbols() > 0) {                //добавляем пробелы и переносы строки
        printf("spaceses and orher symbols added\n");
        cleancleanExtraSpaces();                        //убираем лишние ранее добавленные пробелы и переносы
    }
    else
        printf("error with edit file\n");
    
    checkRecurseFunc();                                 //проверям функции на рекурсию и на вложенность циклов. смотрим неинициализированные переменные

    lastCheck();
    writeAllOnOneFile();

    remove("fileOut2.c");
    remove("file.c");
    remove("fileOut.c");
    remove("report.txt");

    return 0;
}