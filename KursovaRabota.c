#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <windows.h>

typedef struct text {
	char sentence[101];
}TEXT;

typedef struct data {
	TEXT entered_text;
	struct data * next;
}DATA;

void undo(DATA *);
DATA * SaveText(char input[], DATA *);
void transliteration(char input[]);
void freemem(DATA *root);

char cyrillic1[] = { 'ΰ', 'α', 'β', 'γ', 'δ', 'ε', 'ζ', 'η', 'θ', 'ι', 'κ', 'λ', 'μ', 'ν', 'ξ', 'ο', 'π', 'ρ', 'ς', 'σ', 'τ', 'υ', 'φ', 'χ', 'ψ', 'ω', 'ϊ', 'ό', 'ώ', 'ÿ', '\0' };
char cyrillic2[] = { 'ΐ', 'Α', 'Β', 'Γ', 'Δ', 'Ε', 'Ζ', 'Η', 'Θ', 'Ι', 'Κ', 'Λ', 'Μ', 'Ν', 'Ξ', 'Ο', 'Π', 'Ρ', 'Ò', 'Σ', 'Τ', 'Υ', 'Φ', 'Χ', 'Ψ', 'Ω', 'Ϊ', 'ά', 'ή', 'ί', '\0' };

char latin1[] = { 'a', 'b', 'v', 'g', 'd', 'e', 'j', 'z', 'i', 'y', 'k', 'l', 'm', 'n', 'o', 'p', 'r', 's', 't', 'u', 'f', 'h', 'c', '4', '6', 's', 'y', 'u', 'q', 'y', '\0' };
char latin2[] = { 'A', 'B', 'V', 'G', 'D', 'E', 'J', 'Z', 'I', 'Y', 'K', 'L', 'M', 'N', 'O', 'P', 'R', 'S', 'T', 'U', 'F', 'H', 'C', '4', '6', 'S', 'Y', 'U', 'Q', 'Y', '\0' };

int main()
{
	char input[101];
	char *p = input;
	DATA *root = NULL;
	int n;
	char temp[101];
	
	SetConsoleCP(1251);
	SetConsoleOutputCP(1251);

	while (1)
	{

		printf("\nMENU\n");
		printf("1 - Transliterate\n2 - Undo\n3 - Exit\n");
		scanf("%d", &n);
		fflush(stdin);

		switch (n)
		{
		case 1:
			printf("Enter maimunica:\n");
			fgets(temp, sizeof(temp), stdin);
			fgets(input, sizeof(input), stdin);
			root = SaveText(input, root);
			transliteration(input);
			break;
		case 2:
			undo(root);
			break;
		case 3:
			freemem(root);
			system("pause");
			return 0;
		
		default:
			printf("Enter 1-3");
		}
	}
	freemem(root);
	system("pause");
	return 0;
}


DATA * SaveText(char input[101], DATA * root) {
	DATA *curr_item = NULL;
	
	curr_item = (DATA *)malloc(sizeof(DATA));
	strcpy(curr_item->entered_text.sentence, input);
	curr_item->next = root;
	root = curr_item;
	//printf("SAVETEXT: %s", curr_item->entered_text.sentence);
	while (curr_item != NULL) {
		printf("%s\n", curr_item->entered_text.sentence);

		curr_item = curr_item->next;
	}

	return root;
}

void freemem(DATA *root)
{
	DATA *cur_client = root;
	while (root != NULL)
	{
		root = root->next;
		free(cur_client);
		cur_client = root;
	}
}

void transliteration(char input[101])
{
	int j = 0;
	char *p = input;
	int flag = 1;

	for (p = input; *p != '\0'; p++)
	{
		for (j = 0; j <= strlen(latin1); j++)
		{
			if (*p == 'i' && *(p + 1) == 'a')
			{
				*p = 'θ';
				*(p + 1) = 'ÿ';
				printf("%c%c", *p, *(p + 1));
				p = p + 2;
			}
			else if (*p == 'y' && *(p + 1) == 'ξ')
			{
				*p = 'ιξ';
				printf("%c", *p);
				p = p + 2;
			}
			else if (*p == 'z' && *(p + 1) == 'h')
			{
				*p = 'ζ';
				printf("%c", *p);
				p = p + 2;
			}
			else if (*p == 'y' && *(p + 1) == 'a')
			{
				*p = 'ÿ';
				printf("%c", *p);
				p = p + 2;
			}
			else if (*p == 'y' && *(p + 1) == 'u')
			{
				*p = 'ώ';
				printf("%c", *p);
				p = p + 2;
			}
			else if (*p == 's' && *(p + 1) == 'h' && *(p + 2) != 't')
			{
				*p = 'ψ';
				printf("%c", *p);
				p = p + 2;
			}
			else if (*p == 'c' && *(p + 1) == 'h')
			{
				*p = 'χ';
				printf("%c", *p);
				p = p + 2;
			}
			else if (*p == 't' && *(p + 1) == 's')
			{
				*p = 'φ';
				printf("%c", *p);
				p = p + 2;
			}
			else if (*p == 's' && *(p + 1) == 'h' && *(p + 2) == 't')
			{
				*p = 'ω';
				printf("%c", *p);
				p = p + 3;
			}
			else if (*p == latin1[j])
			{
				*p = cyrillic1[j];
			}
			else if (*p == latin2[j])
			{
				*p = cyrillic2[j];
			}
		}
		printf("%c", *p);
	}

	for (p = input; *p != '\0'; p++)
	{
		for (j = 0; j <= strlen(cyrillic1); j++)
		{
			if (*p == 'h' || *p == 'a' || *p == 'u' || *p == 't' || *p == 's')
			{
				p = p + 1;
			}
			else if (flag == 1 && *p == cyrillic1[j]) {
				*p = cyrillic2[j];
				flag = 0;
			}
			else if (*p == '.' && *(p + 1) == cyrillic1[j])
			{
				*(p + 1) = cyrillic2[j];
			}
			else if (*p == '.' && *(p + 1) == ' ' && *(p + 2) == cyrillic1[j])
			{
				*(p + 2) = cyrillic2[j];
			}
		}
		printf("%c", *p);
	}
}

void undo(DATA * root) {
	DATA * curr_item = root;

	while (curr_item != NULL) {
		printf("%s\n", curr_item->entered_text.sentence);

		curr_item = curr_item->next;
	}
}