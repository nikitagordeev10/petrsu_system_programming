/**
 * task_1.c — программа копирования файлов с использованием потоковых фунций fopen(), fread(), fwrite(), fclose().
 * Программа должна получать два аргумента командной строки, первый аргумент - файл, откуда копировать, второй аргумент - файл, куда копировать.
 * 
 * Copyright (c) <2022> <Гордеев Никита>
 *
 * This code is licensed under a MIT-style license.
 */

#include <stdlib.h>
#include <fcntl.h>
#include <unistd.h>
#include <stdio.h>

int main(int argc, char **argv)
{
    FILE *f1, *f2; 
    char buf[4096];
    int status;

    printf("Первый аргумент - файл, откуда копировать, второй аргумент - файл, куда копировать\n");

    /* Первый аргумент - файл, откуда копировать */
    if ((f1 = fopen(argv[1], "r")) == NULL) {
        printf("Первый файл недоступен\n");
	    exit(EXIT_FAILURE);
    }
    
    /* Второй аргумент - файл, куда копировать */
    if ((f2 = fopen(argv[2], "w")) == NULL) {
        printf("Второй файл недоступен\n");
	    exit(EXIT_FAILURE);
    }
    
    /* Чтение из первого файла и запись во второй файл */
    while ((status = fread(buf, sizeof(char), 4096, f1)) > 0) {
        if (fwrite(buf, sizeof(char), status, f2) != status) {
            printf("Ошибка fwrite!\n");
	        exit(EXIT_FAILURE);
        }
    }

    /* Проверка закрытия первого файла */    
    if (fclose(f1) == EOF) {
        printf("Ошибка fclose!\n");
	    exit(EXIT_FAILURE);    }
    
    /* Проверка закрытия второго файла */
    if (fclose(f2) == EOF) {
        printf("Ошибка fclose!\n");
	    exit(EXIT_FAILURE);
    }
    
    printf("Запись выполнена успешно \n");
    return 0;
}

/* Материалы:
 * У. Ричард Стивенс, Стивен А. Раго Листинг 5.3. Вывод сведений о буферизации для различных потоков ввода/вывода // UNIX. Профессиональное программирование. - 2018. - С. 217-219.
 * У. Ричард Стивенс, Стивен А. Раго Листинг 8.17. Вывод учетной информации из системного файла учетных данных // UNIX. Профессиональное программирование. - 2018. - С. 334-335.
 * У. Ричард Стивенс, Стивен А. Раго Листинг 15.5. Функции popen и pclose // UNIX. Профессиональное программирование. - 2018. - С. 625-626.
 */