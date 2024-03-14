#include<stdlib.h>  // ��� ������ � �������
#include<stdio.h>   // ����������� ���������� ��
#include<string.h>  // ��� ������ �� ��������

#define size 96 // ������ ������� ��������
#define N 6 //���������� ������� ����

struct letter{
	char RuLetter;
	char EnLetter;
	char Morse[10];
};

struct letter translate[] = {{'�', 'A', "*-"}, {'�', 'B', "-***"}, {'�', 'W', "*--"},
								{'�', 'G', "--*"}, {'�', 'D', "-**"}, {'�', 'E', "*"}, 
								{'�', 'V', "***-"}, {'�', 'Z', "--**"}, {'�', 'I', "**"}, 
								{'�', 'J', "*---"}, {'�', 'K', "-*-"}, {'�', 'L', "*-**"}, 
								{'�', 'M', "--"}, {'�', 'N', "-*"},	{'�', 'O', "---"}, 
								{'�', 'P', "*--*"}, {'�', 'R', "*-*"}, {'�', 'S', "***"},
								{'�', 'T', "-"}, {'�', 'U', "**-"}, {'�', 'F', "**-*"}, 
								{'�', 'H', "****"}, {'�', 'C', "-*-*"}, {'�', '#', "---*"},
								{'�', '#', "----"}, {'�', 'Q', "--*-"}, {'�', '#', "--*--"},
								{'�', 'Y', "-*--"}, {'�', 'X', "-**-"}, {'�', '#', "**-**"},
								{'�', '*', "**--"}, {'�', '#', "*-*-"}, {')', ')', "-*--*-"},
								{'�', 'a', "*-"}, {'�', 'b', "-***"}, {'�', 'w', "*--"},
								{'�', 'g', "--*"}, {'�', 'd', "-**"}, {'�', 'e', "*"}, 
								{'�', 'v', "***-"}, {'�', 'z', "--**"}, {'�', 'i', "**"}, 
								{'�', 'j', "*---"}, {'�', 'k', "-*-"}, {'�', 'l', "*-**"}, 
								{'�', 'm', "--"}, {'�', 'n', "-*"},	{'�', 'o', "---"}, 
								{'�', 'p', "*--*"}, {'�', 'r', "*-*"}, {'�', 's', "***"},
								{'�', 't', "-"}, {'�', 'u', "**-"}, {'�', 'f', "**-*"}, 
								{'�', 'h', "****"}, {'�', 'c', "-*-*"}, {'�', '#', "---*"},
								{'�', '#', "----"}, {'�', 'q', "--*-"}, {'�', '#', "--*--"},
								{'�', 'y', "-*--"}, {'�', 'x', "-**-"}, {'�', '#', "**-**"},
								{'�', '*', "**--"}, {'�', '#', "*-*-"},	{'1', '1', "*----"},
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

const char * const Menu[] = {"none", "��������� ����� � �������� � ��� ������ �����",
									 "��������� ����� � ����������� � ��� ������ �����",
									 "��������� ��� ������ ����� �� ������� ����",
									 "��������� ��� ������ ����� �� ���������� ����",
									 "��������",
									 "���������"};


int DoMenu(char * s[], int max); //������� ������ ����
void EnteringString(char **t, int *len); // ������� ����� ������
void Print(char *text); // ������� ������ ��������� ������
void PrintMorze(struct letter Morze[], int len); //������� ������ �����
void PrintRu(struct letter *Morze, int len); // ������� ������ �������� �����
void PrintEn(struct letter *Morze, int len); // ������� ������ ����������� �����
void RussianToMorseTranslation(char *text, int len, struct letter * Morze); // ������� � �������� � �����
void EnglishToMorseTranslation(char *text, int len, struct letter * Morze); // ������� � ����������� � �����
int CountAndSplitLettersMorse(char *text, int len, struct letter **Morze); // ������� � ���������� �� �����
void MorseToRussianTranslation(struct letter *Morze, int count); // ������� � ����� �� �������
void MorseToEnglishTranslation(struct letter *Morze, int count); // ������� � ����� �� ����������
void SaveFileMorze(struct letter *Morze, int len); // ���������� � ���� �����
void SaveFileRu(struct letter *Morze, int len); // ���������� � ���� �������
void SaveFileEn(struct letter *Morze, int len); // ���������� � ���� ����������
void LoadFile(char **t, int *len); // �������� �����

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
			case 1: // ��������� ����� � �������� � ��� ������ �����
				printf("��������� ����?\n(y/n) ");
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
					printf("���������?\n(y/n) ");
					scanf("%c", &choice);
					if (choice == 'y')
						SaveFileMorze(Morze, len-1);
				}
				break;
			case 2: // ��������� ����� � ����������� � ��� ������ �����
				printf("��������� ����?\n(y/n) ");
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
					printf("���������?\n(y/n) ");
					scanf("%c", &choice);
					if (choice == 'y')
						SaveFileMorze(Morze, len-1);
				}
				break;
			case 3: // ��������� ��� ������ ����� �� ������� ����"
				printf("��������� ����?\n(y/n) ");
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
					printf("���������?\n(y/n) ");
					scanf("%c", &choice);
					if (choice == 'y')
						SaveFileRu(Morze, count);
				}	
				break;
			case 4: // ��������� ��� ������ ����� �� ���������� ����
				printf("��������� ����?\n(y/n) ");
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
					printf("���������?\n(y/n) ");
					scanf("%c", &choice);
					if (choice == 'y')
						SaveFileEn(Morze, count);
				}
				break;
			case 5: // ��������
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
	printf("������� ��� �����: ");
	while((c = getchar()) != '\n' && *t != NULL){
		(*t)[(*len) - 1] = c;
		(*len)++;
		*t = (char *)realloc((*t), (*len));
	}
	if(*t != NULL)
		(*t)[(*len)-1] = '\0';
}

void Print(char *text){
	printf("��� �����:\n%s\n", text);
}

void PrintMorze(struct letter *Morze, int len){
	printf("������� � �����:\n");
	for(int k = 0; k < len; k++){
		printf("%s ", Morze[k].Morse);
	}
	printf("\n");
}

void PrintRu(struct letter *Morze, int len){
	printf("������� �� �������:\n");
	for(int k = 0; k < len-1; k++){
		printf("%c", Morze[k].RuLetter);
	}
	printf("\n");
}

void PrintEn(struct letter *Morze, int len){
	printf("������� �� ����������:\n");
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
	printf("������� ��� �����: ");
	scanf("%s", file_name);
	getchar();
	printf("��� �����: %s\n", file_name);
	
	if(fp = fopen(file_name, "a")){
		printf("���� ������\n");
		for(int i = 0; i < len; i++){
			fprintf(fp, "%s ", Morze[i].Morse);
		}
		fprintf(fp, "\n");
		printf("���� ������� �������\n");
	}else{
		printf("�� ������� ������� ����.\n");
	}
	
	fclose(fp);	
}

void SaveFileRu(struct letter *Morze, int len){
	
	FILE *fp;
	char file_name[255];
	printf("������� ��� �����: ");
	scanf("%s", file_name);
	getchar();
	printf("��� �����: %s\n", file_name);
	
	if(fp = fopen(file_name, "a")){
		printf("���� ������\n");
		for(int i = 0; i < len; i++){
			fprintf(fp, "%c", Morze[i].RuLetter);
		}
		fprintf(fp, "\n");
		printf("���� ������� �������\n");
	}else{
		printf("�� ������� ������� ����.\n");
	}
	
	fclose(fp);	
}

void SaveFileEn(struct letter *Morze, int len){
	
	FILE *fp;
	char file_name[255];
	printf("������� ��� �����: ");
	scanf("%s", file_name);
	getchar();
	printf("��� �����: %s\n", file_name);
	
	if(fp = fopen(file_name, "a")){
		printf("���� ������\n");
		for(int i = 0; i < len; i++){
			fprintf(fp, "%c", Morze[i].EnLetter);
		}
		fprintf(fp, "\n");
		printf("���� ������� �������\n");
	}else{
		printf("�� ������� ������� ����.\n");
	}
	
	fclose(fp);	
}

void LoadFile(char **t, int *len){
	char c;
	*len = 1;
	*t = (char *)malloc(sizeof(char));
	
	FILE *fp;
	char file_name[255];
	printf("������� ��� �����: ");
	scanf("%s", file_name);
	fflush(stdin);
//	printf("��� �����: %s\n", file_name);
	
	if(fp = fopen(file_name, "r")){
		while((c = fgetc(fp)) != EOF && *t != NULL){
			(*t)[(*len) - 1] = c;
			(*len)++;
			*t = (char *)realloc((*t), (*len));
		}
		if(*t != NULL)
			(*t)[(*len)-1] = '\0';
	}else{
		printf("�� ������� ������� ����.\n");
	}
	
	fclose(fp);	
}

