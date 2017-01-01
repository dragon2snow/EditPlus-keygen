/* 
 * Project name : EditPlus regcode generator
 * Version : 2.0.0.0-release
 * Author : wxx9248
 * GitHub : https://github.com/wxx9248
 * Mail : wxx9248@qq.com
 * Time : Tue Dec 27 23:27:40 CST 2016
 */

#include <ctype.h>
#include <conio.h>
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>
#include <windows.h>

#include "include\clrscr.h"
#include "include\copy_to_clipboard.h"
#include "include\generate.h"
#include "lang\1033\en_US_1033.h"
#include "lang\2052\zh_CN_2052.h"

typedef struct
{
	char *TITLE;
	char *RIGHTS_INFO;
	char *D_ERROR_MSG_USER_NAME_LOST;
	char *D_ERROR_MSG_USER_NAME_INVALID;
	char *D_ERROR_MSG_PARAMETER_INVALID;
	char *I_MSG_INPUT_USER_NAME;
	char *I_ERROR_MSG_USER_NAME_INVALID;
	char *MSG_USER_NAME_ECHOBACK;
	char *MSG_REGCODE_GEN_RESULT;
	char *QUESTION_MSG_PUT_INTO_CLIPBOARD;
	char *ERROR_MSG_CHOICE_INVALID;
	char *MSG_HELP;
} sLang;

typedef sLang *pLang;

void SetUILanguage(pLang);
void PrintRightInfo(void);
void PrintTips(char *);
bool CheckUserName(char *);

char u_name[16];
char RegCode[30];

sLang Lang;

int main(int argc, char *argv[])
{
	SetUILanguage(&Lang);
	
	char temp;

	PrintRightInfo();
	
	SetConsoleTitle(Lang.TITLE);

	if (argc > 1) 
	{
		for (int i = 1; i < argc; i++)
		{
			if (!strcmp(argv[i], "/?"))
			{
				PrintTips(argv[0]);
				exit(EXIT_SUCCESS);
			}
		}

		for (int i = 1; i < argc; i++)
		{
			if (!strcmp(argv[i], "/u"))
			{
				if (i == argc - 1)
				{
					putchar('\n');
					puts(Lang.D_ERROR_MSG_USER_NAME_LOST);
					exit(EXIT_FAILURE);
				}
				if (argc > 2)
				{
					if (!CheckUserName(argv[i + 1]))
					{
						putchar('\n');
						puts(Lang.D_ERROR_MSG_USER_NAME_INVALID);
						exit(EXIT_FAILURE);
					}
					else
					{
						strncpy(u_name, argv[i + 1], 15);
						break;
					}
				}
			}
			else
			{
				puts(Lang.D_ERROR_MSG_PARAMETER_INVALID);
				exit(EXIT_FAILURE);
			}
		}
		clrscr();

		fputs(Lang.MSG_USER_NAME_ECHOBACK, stdout);
		printf("%s\n", u_name);
		fputs(Lang.MSG_REGCODE_GEN_RESULT, stdout);
		printf("%s\n\n", strncpy(RegCode, generate(u_name), 31));

		fputs(Lang.QUESTION_MSG_PUT_INTO_CLIPBOARD, stdout);

		temp = getche();
		temp = toupper(temp);

		putchar('\n');

		if (temp == 'Y')
		{
			copy_to_clipboard(RegCode);
			exit(EXIT_SUCCESS);
		}
		else if (temp == 'N')
			exit(EXIT_SUCCESS);
		else
		{
			putchar('\n');
			puts(Lang.ERROR_MSG_CHOICE_INVALID);
		}

		return 0;

	}

	for (;;)
	{
		fputs(Lang.I_MSG_INPUT_USER_NAME, stdout);
		scanf("%25s", u_name);

		while (getchar() != '\n')
			continue;

		putchar('\n');

		if (!CheckUserName(u_name))
			puts(Lang.I_ERROR_MSG_USER_NAME_INVALID);
		else break;

	}
		clrscr();

		fputs(Lang.MSG_USER_NAME_ECHOBACK, stdout);
		printf("%s\n", u_name);
		fputs(Lang.MSG_REGCODE_GEN_RESULT, stdout);
		printf("%s\n\n", strncpy(RegCode, generate(u_name), 31));

		fputs(Lang.QUESTION_MSG_PUT_INTO_CLIPBOARD, stdout);

		temp = getche();
		temp = toupper(temp);

		putchar('\n');

		if (temp == 'Y')
		{
			copy_to_clipboard(RegCode);
			exit(EXIT_SUCCESS);
		}
		else if (temp == 'N')
			exit(EXIT_SUCCESS);
		else
		{
			putchar('\n');
			puts(Lang.ERROR_MSG_CHOICE_INVALID);
		}

	return 0;

}


bool CheckUserName(char *u_name)
{
	for (int i = 0; i < strlen(u_name); i++)
		if (!isalnum(u_name[i]))
			return false;
		else if (isdigit(u_name[i]))
			return true;

	return false;
}


void PrintTips(char *prog_name)
{
	fputs(prog_name, stdout);
	fputs(Lang.MSG_HELP, stdout);
}


void PrintRightInfo(void)
{
	clrscr();
	puts(Lang.RIGHTS_INFO);
	putchar('\n');
}

void SetUILanguage(pLang pl)
{
	LANGID Lang = GetUserDefaultLangID();
	switch (Lang)
	{
	case (WORD)2052:
		pl->TITLE = TITLE_2052;
		pl->RIGHTS_INFO = RIGHTS_INFO_2052;
		pl->D_ERROR_MSG_USER_NAME_LOST = D_ERROR_MSG_USER_NAME_LOST_2052;
		pl->D_ERROR_MSG_USER_NAME_INVALID = D_ERROR_MSG_USER_NAME_INVALID_2052;
		pl->D_ERROR_MSG_PARAMETER_INVALID = D_ERROR_MSG_PARAMETER_INVALID_2052;
		pl->I_MSG_INPUT_USER_NAME = I_MSG_INPUT_USER_NAME_2052;
		pl->I_ERROR_MSG_USER_NAME_INVALID = I_ERROR_MSG_USER_NAME_INVALID_2052;
		pl->MSG_USER_NAME_ECHOBACK = MSG_USER_NAME_ECHOBACK_2052;
		pl->MSG_REGCODE_GEN_RESULT = MSG_REGCODE_GEN_RESULT_2052;
		pl->QUESTION_MSG_PUT_INTO_CLIPBOARD = QUESTION_MSG_PUT_INTO_CLIPBOARD_2052;
		pl->ERROR_MSG_CHOICE_INVALID = ERROR_MSG_CHOICE_INVALID_2052;
		pl->MSG_HELP = MSG_HELP_2052;
		break;

	default:
		pl->TITLE = TITLE_1033;
		pl->RIGHTS_INFO = RIGHTS_INFO_1033;
		pl->D_ERROR_MSG_USER_NAME_LOST = D_ERROR_MSG_USER_NAME_LOST_1033;
		pl->D_ERROR_MSG_USER_NAME_INVALID = D_ERROR_MSG_USER_NAME_INVALID_1033;
		pl->D_ERROR_MSG_PARAMETER_INVALID = D_ERROR_MSG_PARAMETER_INVALID_1033;
		pl->I_MSG_INPUT_USER_NAME = I_MSG_INPUT_USER_NAME_1033;
		pl->I_ERROR_MSG_USER_NAME_INVALID = I_ERROR_MSG_USER_NAME_INVALID_1033;
		pl->MSG_USER_NAME_ECHOBACK = MSG_USER_NAME_ECHOBACK_1033;
		pl->MSG_REGCODE_GEN_RESULT = MSG_REGCODE_GEN_RESULT_1033;
		pl->QUESTION_MSG_PUT_INTO_CLIPBOARD = QUESTION_MSG_PUT_INTO_CLIPBOARD_1033;
		pl->ERROR_MSG_CHOICE_INVALID = ERROR_MSG_CHOICE_INVALID_1033;
		pl->MSG_HELP = MSG_HELP_2052;
	}
}
