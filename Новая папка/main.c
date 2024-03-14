#include<stdlib.h>  // для работы с памятью
#include<stdio.h>   // стандартная библиотека си
#include<string.h>  // для работы со строками

#define size 96 // размер массива структур
#define N 6 //количество пунктво меню

struct letter{
	char RuLetter;
	char EnLetter;
	char Morse[10];
};

struct letter translate[] = {{'А', 'A', "*-"}, {'Б', 'B', "-***"}, {'В', 'W', "*--"},
								{'Г', 'G', "--*"}, {'Д', 'D', "-**"}, {'Е', 'E', "*"}, 
								{'Ж', 'V', "***-"}, {'З', 'Z', "--**"}, {'И', 'I', "**"}, 
								{'Й', 'J', "*---"}, {'К', 'K', "-*-"}, {'Л', 'L', "*-**"}, 
								{'М', 'M', "--"}, {'Н', 'N', "-*"},	{'О', 'O', "---"}, 
								{'П', 'P', "*--*"}, {'Р', 'R', "*-*"}, {'С', 'S', "***"},
								{'Т', 'T', "-"}, {'У', 'U', "**-"}, {'Ф', 'F', "**-*"}, 
								{'Х', 'H', "****"}, {'Ц', 'C', "-*-*"}, {'Ч', '#', "---*"},
								{'Ш', '#', "----"}, {'Щ', 'Q', "--*-"}, {'Ъ', '#', "--*--"},
								{'Ы', 'Y', "-*--"}, {'Ь', 'X', "-**-"}, {'Э', '#', "**-**"},
								{'Ю', '*', "**--"}, {'Я', '#', "*-*-"}, {')', ')', "-*--*-"},
								{'а', 'a', "*-"}, {'б', 'b', "-***"}, {'в', 'w', "*--"},
								{'г', 'g', "--*"}, {'д', 'd', "-**"}, {'е', 'e', "*"}, 
								{'ж', 'v', "***-"}, {'з', 'z', "--**"}, {'и', 'i', "**"}, 
								{'й', 'j', "*---"}, {'к', 'k', "-*-"}, {'л', 'l', "*-**"}, 
								{'м', 'm', "--"}, {'н', 'n', "-*"},	{'о', 'o', "---"}, 
								{'п', 'p', "*--*"}, {'р', 'r', "*-*"}, {'с', 's', "***"},
								{'т', 't', "-"}, {'у', 'u', "**-"}, {'ф', 'f', "**-*"}, 
								{'х', 'h', "****"}, {'ц', 'c', "-*-*"}, {'ч', '#', "---*"},
								{'ш', '#', "----"}, {'щ', 'q', "--*-"}, {'ъ', '#', "--*--"},
								{'ы', 'y', "-*--"}, {'ь', 'x', "-**-"}, {'э', '#', "**-**"},
								{'ю', '*', "**--"}, {'я', '#', "*-*-"},	{'1', '1', "*----"},
								{'2', '2', "**---"}, {'3', '3', "***--"}, {'4', '4', "****-"}, 
								{'5', '5', "*****"}, {'6', '6', "-****"}, {'7', '7', "--***"}, 
								{'8', '8', "---**"}, {'9', '9', "----*"}, {'0', '0', "-----"}, 
								{'.', '#', "******"}, {',', '.', "*-*-*-"}, {'!', ',', "--**--"}, 
								{'#', '!', "-*-*--"}, {'?', '?', "**--**"}, {'\'', '\'', "*----*"}, 
								{'"', '"', "*-**-*"}, {';', ';', "-*-*-*"}, {':', ':', "---***"},
								{'-', '-',	"-****-"}, {'+', '+', "*-*-*"}, {'_', '_', "**--*-"}, 
								{'/', '/', "-**-*"}, {'#', '(', "-*--*"}, {'(', ')', "-*--*-"}, 
								{'&', '&', "*-***"}, {'$', '$', "***-**-"}, {'@', '@', "*--*-*"}, 
								{' ', ' ', ' '}, {'\n', '\n', '\n'}, {'\t', '\t', '\t'} };

const char * const Menu[] = {"none", "Перевести текст с русского в код азбуки Морзе",
									 "Перевести текст с английского в код азбуки Морзе",
									 "Перевести код азбуки Морзе на русский язык",
									 "Перевести код азбуки Морзе на английский язык",
									 "Очистить",
									 "Завершить"};


int DoMenu(char * s[], int max); //Функция вызова меню
void EnteringString(char **t, int *len); // Функция ввода строки
void Print(char *text); // Функция вывода введённого текста
void PrintMorze(struct letter Morze[], int len); //функция вывода морзе
void PrintRu(struct letter *Morze, int len); // функция вывода русского языка
void PrintEn(struct letter *Morze, int len); // функция вывода английского языка
void RussianToMorseTranslation(char *text, int len, struct letter * Morze); // перевод с русского в морзе
void EnglishToMorseTranslation(char *text, int len, struct letter * Morze); // перевод с английского в морзе
int CountAndSplitLettersMorse(char *text, int len, struct letter **Morze); // подсчёт и разделение на буквы
void MorseToRussianTranslation(struct letter *Morze, int count); // перевод с морзе на русский
void MorseToEnglishTranslation(struct letter *Morze, int count); // перевод с морзе на английский
void SaveFileMorze(struct letter *Morze, int len); // сохранение в файл морзе
void SaveFileRu(struct letter *Morze, int len); // сохранение в файл русский
void SaveFileEn(struct letter *Morze, int len); // сохранение в файл английский
void LoadFile(char **t, int *len); // загрузка файла

int main(){
	
	system("chcp 1251>NUL");
	
	int k;
	char *text;
	int len = 1;
	int count = 0;
	char choice;
	
	struct letter *Morze;
	
	do{
		k = DoMenu((char **)Menu, N);
		switch(k){
			case 1: // Перевести текст с русского в код азбуки Морзе
				printf("Загрузить файл?\n(y/n) ");
				scanf("%c", &choice);
				fflush(stdin);
				if (choice == 'y')
					LoadFile(&text, &len);
				else
					EnteringString(&text, &len);
				if(*text){
					Morze = (struct letter *)malloc(len * sizeof(struct letter));
					RussianToMorseTranslation(text, len, Morze);
					PrintMorze(Morze, len-1);
					printf("Сохранить?\n(y/n) ");
					scanf("%c", &choice);
					if (choice == 'y')
						SaveFileMorze(Morze, len-1);
				}
				break;
			case 2: // Перевести текст с английского в код азбуки Морзе
				printf("Загрузить файл?\n(y/n) ");
				scanf("%c", &choice);
				fflush(stdin);
				if (choice == 'y')
					LoadFile(&text, &len);
				else
					EnteringString(&text, &len);
				if (*text){
					Morze = (struct letter *)malloc(len * sizeof(struct letter));
					EnglishToMorseTranslation(text, len, Morze);
					PrintMorze(Morze, len-1);
					printf("Сохранить?\n(y/n) ");
					scanf("%c", &choice);
					if (choice == 'y')
						SaveFileMorze(Morze, len-1);
				}
				break;
			case 3: // Перевести код азбуки Морзе на русский язык"
				printf("Загрузить файл?\n(y/n) ");
				scanf("%c", &choice);
				fflush(stdin);
				if (choice == 'y')
					LoadFile(&text, &len);
				else
					EnteringString(&text, &len);
				if (*text){
					Morze = (struct letter *)malloc(sizeof(struct letter));
					count = CountAndSplitLettersMorse(text, len, &Morze);
					MorseToRussianTranslation(Morze, count);
					PrintRu(Morze, count+1);
					printf("Сохранить?\n(y/n) ");
					scanf("%c", &choice);
					if (choice == 'y')
						SaveFileRu(Morze, count);
				}	
				break;
			case 4: // Перевести код азбуки Морзе на английский язык
				printf("Загрузить файл?\n(y/n) ");
				scanf("%c", &choice);
				fflush(stdin);
				if (choice == 'y')
					LoadFile(&text, &len);
				else
					EnteringString(&text, &len);
				if (*text){
					Morze = (struct letter *)malloc(sizeof(struct letter));
					count = CountAndSplitLettersMorse(text, len, &Morze);
					MorseToEnglishTranslation(Morze, count);
					PrintEn(Morze, count+1);
					printf("Сохранить?\n(y/n) ");
					scanf("%c", &choice);
					if (choice == 'y')
						SaveFileEn(Morze, count);
				}
				break;
			case 5: // Очистить
				system("cls");
				break;	
		}
	}while(k != N);
	
	free(text);
	free(Morze);
	
	system("pause");
	return 0;
}


int DoMenu(char * s[], int max){
	int i = 1;
	for (i = 1; i <= max; i++)
		printf("   %d. %s\n", i , s[i]);
	printf("   >");
	fflush(stdin);
	scanf("%d", &i);
	fflush(stdin);
	return i<1||i>max?0:i;
}

void EnteringString(char **t, int *len){
	char c;
	*len = 1;
	*t = (char *)malloc(sizeof(char));
	printf("Введите ваш текст: ");
	while((c = getchar()) != '\n' && *t != NULL){
		(*t)[(*len) - 1] = c;
		(*len)++;
		*t = (char *)realloc((*t), (*len));
	}
	if(*t != NULL)
		(*t)[(*len)-1] = '\0';
}

void Print(char *text){
	printf("Ваш текст:\n%s\n", text);
}

void PrintMorze(struct letter *Morze, int len){
	printf("Перевод в морзе:\n");
	for(int k = 0; k < len; k++){
		printf("%s ", Morze[k].Morse);
	}
	printf("\n");
}

void PrintRu(struct letter *Morze, int len){
	printf("Перевод на русский:\n");
	for(int k = 0; k < len-1; k++){
		printf("%c", Morze[k].RuLetter);
	}
	printf("\n");
}

void PrintEn(struct letter *Morze, int len){
	printf("Перевод на английский:\n");
	for(int k = 0; k < len-1; k++){
		printf("%c", Morze[k].EnLetter);
	}
	printf("\n");
}

void RussianToMorseTranslation(char *text, int len, struct letter * Morze){
	for(int i = 0; i < len; i++){
		for(int j = 0; j < size; j++){
			if(text[i] == translate[j].RuLetter){
				Morze[i].RuLetter = text[i];
				strcpy(Morze[i].Morse, translate[j].Morse);
				break;
			}
			else{
				Morze[i].RuLetter = text[i];
				strcpy(Morze[i].Morse, "#");
			}
		}
	}
}

void EnglishToMorseTranslation(char *text, int len, struct letter * Morze){
	for(int i = 0; i < len; i++){
		for(int j = 0; j < size; j++){
			if(text[i] == translate[j].EnLetter){
				Morze[i].EnLetter = text[i];
				strcpy(Morze[i].Morse, translate[j].Morse);
				break;
			}
			else{
				Morze[i].EnLetter = text[i];
				strcpy(Morze[i].Morse, "#");
			}
		}
	}
}

int CountAndSplitLettersMorse(char *text, int len, struct letter **Morze){
	
	int count = 0;
	int lenletter = 0;

	for(int i = 0; i < len-1; i++){
		if(text[i] == '\n' || text[i] == '\t' || text[i] == ' '){
			(*Morze)[count].Morse[lenletter] = '\0';
			count++;
			lenletter = 0;
			*Morze = (struct letter *)realloc(*Morze, (count+1)*sizeof(struct letter));
			if(text[i] == '\n' || text[i] == '\t'){
				(*Morze)[count].Morse[lenletter] = text[i];
				count++;
				*Morze = (struct letter *)realloc(*Morze, (count+1)*sizeof(struct letter));
			}
			continue;
		}
		if(lenletter < 10){
			(*Morze)[count].Morse[lenletter] = text[i];
			lenletter++;
		}
	}
	(*Morze)[count].Morse[lenletter] = '\0';
	return count+1;
}

void MorseToRussianTranslation(struct letter *Morze, int count){
	for(int i = 0; i <= count; i++){
		for(int j = 0; j < size; j++){
			if(strcmp(Morze[i].Morse, translate[j].Morse) == 0){
				Morze[i].RuLetter = translate[j].RuLetter;
				break;
			}
			else if(Morze[i].Morse[0] == '\0'){
				Morze[i].RuLetter = ' ';
				break;
			}
			else{
				Morze[i].RuLetter = '#';
			}
		}
	}
}

void MorseToEnglishTranslation(struct letter *Morze, int count){
	for(int i = 0; i <= count; i++){
		for(int j = 0; j < size; j++){
			if(strcmp(Morze[i].Morse, translate[j].Morse) == 0){
				Morze[i].EnLetter = translate[j].EnLetter;
				break;
			}
			else if(Morze[i].Morse[0] == '\0'){
				Morze[i].EnLetter = ' ';
				break;
			}
			else{
				Morze[i].EnLetter = '#';
			}
		}
	}	
}

void SaveFileMorze(struct letter *Morze, int len){
	
	FILE *fp;
	char file_name[255];
	printf("Введите имя файла: ");
	scanf("%s", file_name);
	getchar();
	printf("Имя файла: %s\n", file_name);
	
	if(fp = fopen(file_name, "a")){
		printf("Файл открыт\n");
		for(int i = 0; i < len; i++){
			fprintf(fp, "%s ", Morze[i].Morse);
		}
		fprintf(fp, "\n");
		printf("Файл успешно сохранён\n");
	}else{
		printf("Не удалось открыть файл.\n");
	}
	
	fclose(fp);	
}

void SaveFileRu(struct letter *Morze, int len){
	
	FILE *fp;
	char file_name[255];
	printf("Введите имя файла: ");
	scanf("%s", file_name);
	getchar();
	printf("Имя файла: %s\n", file_name);
	
	if(fp = fopen(file_name, "a")){
		printf("Файл открыт\n");
		for(int i = 0; i < len; i++){
			fprintf(fp, "%c", Morze[i].RuLetter);
		}
		fprintf(fp, "\n");
		printf("Файл успешно сохранён\n");
	}else{
		printf("Не удалось открыть файл.\n");
	}
	
	fclose(fp);	
}

void SaveFileEn(struct letter *Morze, int len){
	
	FILE *fp;
	char file_name[255];
	printf("Введите имя файла: ");
	scanf("%s", file_name);
	getchar();
	printf("Имя файла: %s\n", file_name);
	
	if(fp = fopen(file_name, "a")){
		printf("Файл открыт\n");
		for(int i = 0; i < len; i++){
			fprintf(fp, "%c", Morze[i].EnLetter);
		}
		fprintf(fp, "\n");
		printf("Файл успешно сохранён\n");
	}else{
		printf("Не удалось открыть файл.\n");
	}
	
	fclose(fp);	
}

void LoadFile(char **t, int *len){
	char c;
	*len = 1;
	*t = (char *)malloc(sizeof(char));
	
	FILE *fp;
	char file_name[255];
	printf("Введите имя файла: ");
	scanf("%s", file_name);
	fflush(stdin);
//	printf("Имя файла: %s\n", file_name);
	
	if(fp = fopen(file_name, "r")){
		while((c = fgetc(fp)) != EOF && *t != NULL){
			(*t)[(*len) - 1] = c;
			(*len)++;
			*t = (char *)realloc((*t), (*len));
		}
		if(*t != NULL)
			(*t)[(*len)-1] = '\0';
	}else{
		printf("Не удалось открыть файл.\n");
	}
	
	fclose(fp);	
}

