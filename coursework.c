#define _CRT_SECURE_NO_WARNINGS
#define _CRT_NONSTDC_NO_DEPRECATE
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <locale.h>
#include <conio.h>
#include <ctype.h>

#pragma execution_character_set("utf-8")

#define INF_ABOUT_STaW "Course work for option 4.6, created by Kseniya Kopasova\n"
#define LEN_TEXT 100;
#define LEN_WORD 1000;


//объявляем все функции

void file_help();
void text_print_func(char** splitted_text, int output_numb);
char* text_input_func();
char** split_text_func(char* text, char* splitter, int* output_numb, int func_value);
void text_free_func(char** splitted_text, char* text, int output_numb);
void text_deleting_repeat_func(char** splitted_text, int* output_numb);
void print_word_and_number_repetitions(char* text);
//int numb_word(char** splitted_text, int output_numb);
char* text_reverse(char* text);
void toLower(char* text);
void bubble_sort(char** splitted_text, int output_numb, int index);
void text_func_four(char** splitted_text, int output_numb);

int main() {
	printf(INF_ABOUT_STaW);

///чтобы компилятор воспинимал кирилицу
	setlocale(LC_ALL, "ru_RU.UNF-8");
	SetConsoleCP(1251);
	SetConsoleOutputCP(1251);
///
	char func_value = 0; //значение функции
	scanf("%c", &func_value);
	getchar();

	if (!isdigit(func_value)) {
		printf("Error: Некорректный ввод.\n");
	}

	int output_numb = 0;
	char** splitted_text;
	char* text;
	
	/////////////
		
	switch (func_value) {
		case '0'://выводимм текст после первичной обработки
			//ввод и первичная обрботка
			text = text_input_func();
			splitted_text = split_text_func(text, ".", &output_numb, func_value);
				
			//выводим текст после первичной обработки и особождаем память
			text_print_func(splitted_text, output_numb);
			text_free_func(splitted_text, text, output_numb);

			break;
			
		case '1'://выводим функцию под номером 1

			//ввод и первичная обрботка
			text = text_input_func();
			splitted_text = split_text_func(text, ".", &output_numb, func_value);
		
			print_word_and_number_repetitions(text);
			text_free_func(splitted_text, text, output_numb);
			
			break;
			
		case '2'://выводим функцию под номером 2

			//ввод и обработка
			text = text_input_func();
			splitted_text = split_text_func(text_reverse(text), ".", &output_numb, func_value);
			
			//вывод и освобождение памяти
			text_print_func(splitted_text, output_numb);
			text_free_func(splitted_text, text, output_numb);
			
			break;
			
		case '3'://выводим функцию под номером 3

			//обработка и ввод
			text = text_input_func();
			splitted_text = split_text_func(text, ".", &output_numb, func_value);
			
			//вывод и освобождение памяти
			text_print_func(splitted_text, output_numb);
			text_free_func(splitted_text, text, output_numb);
			
			break;
			
		case '4'://выводим функцию под номером 4

			text = text_input_func();
			splitted_text = split_text_func(text, ".", &output_numb, func_value);
										
			//вывод и освобождение памяти
			text_func_four(splitted_text, output_numb);
			text_free_func(splitted_text, text, output_numb);
			break;
			
		case '5'://выводим справки о всех функциях

			file_help();
			break;
	
		default:
			//прописать тип ошибок
			printf("Error: Неправильно введена функция.\n");
			break;
		}


	return 0;
}

//функция для вывода справки (func_value=5)
void file_help() {
	printf("%s\n%s\n%s\n%s\n%s\n%s\n%s\n",
		"Справка:",
		"0 - вывод текста после первичной обязательной обработки;",
		"1 - распечатать каждое слово и количество его повторений в тексте;",
		"2 - преобразовать каждое предложение так, что символы в каждом слове шли в обратном порядке;",
		"3 - удалить предложения, в которых встречается запятая;",
		"4 - отсортировать предложения по уменьшению значения кода 5 символа предложения;",
		"5 - вывод справки о функциях, которые реализует программа.");
}

//принимаем текст
char* text_input_func() {

	int len = 0;
	int add_memory = LEN_TEXT;
	char input_char;
	char* text = malloc(sizeof(char) * add_memory);//выделяем память на массив с указателями
	//динамическое выделение памяти под исходный текст

	while ((input_char = getchar())) {
		if ((input_char == '\n')) {
			if ((len > 0) && (text[len - 1] == '\n')) {
				break;
			}
		}
		
		if (text[0] == '.') {
			printf("Error: Ошибка ввода.\n");
		}
		if (len >= add_memory && text!=NULL) {
			add_memory += LEN_TEXT;
			text = realloc(text, sizeof(char) * add_memory);
		}
		text[len++] = input_char;
	}

	text[len] = '\0';
	 
	/*if (text[strlen(text) - 2] != '.') {
		text[strlen(text) - 2] = '.';
	}*/
	return text;
}

//выводим текст
void text_print_func(char** splitted_text, int output_numb) {
	for (int i = 0; i < output_numb; i++) {
		printf("%s\n", splitted_text[i]);

	}
}

//функция освобождения динамической памяти
void text_free_func(char** splitted_text, char* text, int output_numb) {
	for (int i = 0; i < output_numb; i++) {
		free(splitted_text[i]);
	}
	free(splitted_text);
	int len_text = strlen(text);
	
}

//функция удаления одинаковых предложений
void text_deleting_repeat_func(char** splitted_text, int* output_numb) {
	for (int i = 0; (i < (*output_numb)) && (splitted_text[i]); i++) {
		for (int j = i+1; (j < (*output_numb)) && (splitted_text[j]); j++) {
			if (stricmp(splitted_text[i], splitted_text[j]) == 0) {
				free(splitted_text[j]);
				for (int k = j; k < (*output_numb); k++) {
					splitted_text[k] = splitted_text[k + 1];
				}
				(*output_numb)--;
				j--;
			}
		}
	}
}

//считаем количество слов
/*
int numb_word(char** splitted_text, int output_numb) {
	int word_count = 0;
	for (int i = 0; i < output_numb; i++) {
		for (int j = 0; j < ((int)strlen(splitted_text[i])+1); j++) {
			if (((splitted_text[i][j] == ' ') || (splitted_text[i][j] == ',') || (splitted_text[i][j] == '.')) && ((splitted_text[i][j - 1] != ' ') && (splitted_text[i][j - 1] != ',') && (splitted_text[i][j - 1] != '.'))) {
				word_count++;
			}
		}
	}
	return word_count;
}
*/

//все для функции 1
struct WordCount {
	char word[100];
	int count;
};

//функция для сравнения двух слов
int compare(const void* a, const void* b) {
	struct WordCount* f = (struct WordCount*)a;
	struct WordCount* s = (struct WordCount*)b;
	return (strcmp(f->word, s->word));
	
}

//переводим текст в нижний регистр
void toLower(char* text) {
	for (int i = 0; text[i]; i++) {
		text[i] = tolower(text[i]);
	}
}

//функция 1 - печать каждого слова и кол-во его повторений
void print_word_and_number_repetitions(char* text) {
	//определяем переменную
	toLower(text);
	struct WordCount word_count[100];
	int count = 0;
	int len_str = strlen(text);
	if (text[len_str - 1] == '\n') {
		text[len_str - 1] = '\0';
	}
	char* temp_word = strtok(text, " ,.");
	while (temp_word != NULL) {
		int fl = 0; //флаг слова

		for (int i = 0; i < count; i++) {
			if ((strcmp(word_count[i].word, temp_word) == 0) && (isalnum(text[i]))) {
				fl = 1;
				word_count[i].count++;
				break;
			}
		}
		if (!fl) {
			strcpy(word_count[count].word, temp_word);
			word_count[count].count = 1;
			count++;
		}
		temp_word = strtok(NULL, " ,.");
	}	

	qsort(word_count, count, sizeof(struct WordCount), compare);

	//Слова и количество повторений
	for (int i = 0; ((strcmp(word_count[i].word, " ") != 0) && (word_count[i].count!=0)); i++) {
		printf("%s - %d\n", word_count[i].word, word_count[i].count);
	}
}

//bubble sort для 4 функици
void bubble_sort(char** splitted_text, int output_numb, int index) {
	char temp;
	
	for (int k = 0; k < output_numb; k++) {
		int len_sent = strlen(splitted_text[k]);
		for (int i = index; i < len_sent + (index-1); i++) {
			for (int j = index; j < len_sent - i + (index - 1); j++) {
				if ((splitted_text[k][j] > splitted_text[k][j + 1])) {
					temp = splitted_text[k][j];
					splitted_text[k][j] = splitted_text[k][j + 1];
					splitted_text[k][j + 1] = temp;
				}
			}
		}
	}	
}

//функция 4
void text_func_four(char** splitted_text, int output_numb) {
	for (int i = 0; i < output_numb; i++) {
		int len_sent = strlen(splitted_text[i]);
		int index=4;
			if (isalnum(splitted_text[i][4]) && ((len_sent-1)>=5)) {
				index = 4;
				bubble_sort(splitted_text, output_numb, index);
				break;
			}
			else {
				index++;
				for (int l = 0; l < len_sent; l++) {
					if (isalnum(splitted_text[i][index])) {
						bubble_sort(splitted_text, output_numb, index);
						break;
					}
				}
			}

	}

	for (int i = 0; i < output_numb; i++) {
		if (strlen(splitted_text[i]) - 1 < 5) {
			printf("-1\n");
		}
		else {
			printf("%s\n", splitted_text[i]);
		}
	}
}

//функция 2 преворачиваем слова
char* text_reverse(char* text) {
	int len_str = strlen(text);
	int start = 0;
	int fl = 0;
	for (int i = 0; i <= (len_str); i++) {
		if ((fl == 0) && (isalnum(text[i]))) {
			start = i;
			fl = 1;
		}
		if (((text[i] == ',') || (text[i] == ' ') || (text[i] == '.')) && (isalnum(text[i - 1]))) {
			int stop = i - 1;
			for (int j = start, k = stop; j < k; j++, k--) {
				char temp = text[j];
				text[j] = text[k];
				text[k] = temp;
			}
			fl = 0;
		}
	}
	return text;
}

//функция разделения предложений и удаления предложений с запятыми
char** split_text_func(char* text, char* splitter, int* output_numb, int  func_value) {
	char** splitted_text = malloc(sizeof(char*));

	int count_sent = 0; //счетчик предложений
	int last_ind = 0;
	int deleting_sent = 0; //флаг удаления предложения
	//int comma_counter = 0; //счетчик запятых
	int was_letter_printed = 0;

	for (int i = 0; i < (int)strlen(text); i++) {
		//если вызвана функция 3, то удаляем предложение с запятой
		if ((func_value == '3') && (text[i] == ',')) {
			deleting_sent = 1;
		}
		/*
		//запятые 
		if (text[i] == ',') {
			comma_counter++;
			if (comma_counter > 1) {
				deleting_sent = 1;
			}
		}
		else {
			comma_counter = 0;
		}*/
		// считаем предложения и разделяем текст на предложения
		if (strchr(splitter, text[i])) {
			
			if (deleting_sent == 1) {
				deleting_sent = 0;
				last_ind = 0;
				continue;
			}

			count_sent++;
			if (splitted_text != NULL && count_sent != 0 && last_ind!=0) {
				splitted_text = realloc(splitted_text, count_sent * sizeof(char*));
				splitted_text[count_sent - 1] = malloc((last_ind + 2) * sizeof(char));
			}
			int chr_temp= 0; 
			for (int j = last_ind; j >= 0; j--) {
				/////////////пропуск запятой и точки в начале предложения
				
				if ((!isspace(text[i - j])) && (text[i - j] != ',')) {
					was_letter_printed = 1;
				}
				if ((!was_letter_printed) && ((isspace(text[i - j])) || (text[i - j] == ','))) {
					continue;
				}
				splitted_text[count_sent - 1][chr_temp++] = text[i - j];
			}

			while (isspace(splitted_text[count_sent - 1][chr_temp - 1])) {
				chr_temp--;
			}

			splitted_text[count_sent - 1][chr_temp] = '\0';
			last_ind = 0;
			continue;
		}
		last_ind++;
		was_letter_printed = 0;
	}
	*output_numb = count_sent;
	text_deleting_repeat_func(splitted_text, output_numb);
	return splitted_text;
}