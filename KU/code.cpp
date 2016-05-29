#include <conio.h>
#include <malloc.h>
#include <stdio.h>
#include <windows.h>
#include <locale.h>

typedef struct
{
	char *name;//��������� �� ������ ������ ������, ���������� ��� ���������
	char *type;//��������� �� ������ ������ ������, ���������� ��� ���������
	int x;     //��������� ��������� �� x
	int y;     //��������� ��������� �� y
	int z;     //��������� ��������� �� z
	int m;     //������������� � ��
	int speed; //�������� � ��/�
}DATA;

typedef struct ST1
{
	DATA info;
	struct ST1 *link1;//������ �� ��������� �������
}OSHIP;

typedef struct
{
	char s_name; //��� ���������� �� �����(1-�� ����������� 2-�� ��������)
	char s_type; //��� ���������� �� ����(1-�� ����������� 2-�� ��������)
	char s_x;    //��� ���������� �� x(1-�� ����������� 2-�� ��������)
	char s_y;    //��� ���������� �� y(1-�� ����������� 2-�� ��������)
	char s_z;    //��� ���������� �� z(1-�� ����������� 2-�� ��������)
	char s_m;    //��� ���������� �� �������������(1-�� ����������� 2-�� ��������)
	char s_speed;//��� ���������� �� ��������(1-�� ����������� 2-�� ��������)
	char typ[7]; //������ ������� 7, � ������� ������� �������� �������� ���������� (1-��� 2-��� 3-x 4-y 6-m 5-speed 0-��� ��������)
} SORTDATA;

typedef struct
{
	char *name;//��������� �� ������ ������ ������, ���������� ��� ���������
	char *type;//��������� �� ������ ������ ������, ���������� ��� ���������
	int x;     //��������� ��������� �� x
	int y;     //��������� ��������� �� y
	int z;     //��������� ��������� �� z
	int m;     //��������� ��������� �� z
	int speed; //��������� ��������� �� z

	char s_name; //��� ������ �� �����(0-�� ����� 1-��, ��� ������ 2-��, ��� ������ 3-������ ����������)
	char s_type; //��� ������ �� ����(0-�� ����� 1-��, ��� ������ 2-��, ��� ������ 3-������ ����������)
	char s_x;    //��� ������ �� x(0-�� ����� 1-��, ��� ������ 2-��, ��� ������ 3-������ ����������)
	char s_y;    //��� ������ �� y(0-�� ����� 1-��, ��� ������ 2-��, ��� ������ 3-������ ����������)
	char s_z;    //��� ������ �� z(0-�� ����� 1-��, ��� ������ 2-��, ��� ������ 3-������ ����������)
	char s_m;    //��� ������ �� �������������(0-�� ����� 1-��, ��� ������ 2-��, ��� ������ 3-������ ����������)
	char s_speed;//��� ������ �� ��������(0-�� ����� 1-��, ��� ������ 2-��, ��� ������ 3-������ ����������)
} FINDDATA;

#define S_input_path_help "���������:\n  1. ������� ������� ���������\n  2. ������� ������ � ������\n  3. ������� ��������� �������� ������\n���� ����������� �������� ������������.\n������ � ����� ���� ����� ��������������.\n�� ����� ������ �������� ���������� \".txt\", ��� ����, ����� �����\n���� ������� ���� � ��������.\n\n��� ��������� ����� ������� Enter\n"
#define S_input_nt_help "���������:\n  1. ������� ������� ���������\n  2. ������� ������ � ������\n  3. ������� ��������� �������� ������\n  4. ������� ����� ���� �������, ����� ���������� ����, ������� �\n     ������� ������\n���� ����������� �������� ����� ��������������.\n������ � ����� ����� ��������������.\n�������� ������ ������ �������� �� ������ ��� ���������� ����,\n������ �� ������� ������ ���������� � �������� �����.\n��� �������� ����� � ����� ����� ������ ����� ������� ����������.\n�������� ������ ����� ��������� �� 1 �� 50 ��������.\n��� ���������� ������������� ���������� �������� ����\n�������� ����� ��������������.\n��� ��������� ����� ������� Enter\n"
#define S_input_number "��������� ������� ������ ����� � '-'.\n����������� ���� ������ �����.\n"
#define S_table_fringe "|----------------------------------------------------|----------------------------------------------------|---------|---------|---------|-------------|--------|\n"

/*
��������: ������� ��� ��������� �������. 
�������: �������� ������.
*/
char my_getch()
{
	char ch;//��� ������� ������.
	do
	{
		if ((ch = _getch()) == '\r')
			ch = '\n';
		else
			if (ch == '\0' || ch == -32)
			{
				if (kbhit())
					_getch();
			}
			else
				if (ch == '\t')
					ch = ' ';
	} while (ch >= -128 && ch <= -17 || ch == '\0' || ch == -32);
	return ch;
}

/*
��������: ������� ��� ����� ������ �����.
�������: �������� �����.
*/
int input_number()
{
	int number;    //�������� �����	
	char *s;       //��������� �� ������ ������ �������� ������
	int length = 1;//����� ������
	char ch;       //�������� ������
	s = (char*)malloc(sizeof(char));
	do
	{
		switch (ch = my_getch())//�������� ������ ������� ������
		{
		case '\b':
			if (length > 1)
			{
				printf("\b \b");
				length--;
				s = (char *)realloc(s, sizeof(char)*length);
			}
			break;
		case '\n':
			s[length - 1] = '\0';
			break;
		default:
			if ((ch >= '0' && ch <= '9' || ch == '-' && length == 1) && length <= 7)
			{
				s = (char *)realloc(s, sizeof(char)*(length + 1));
				printf("%c", ch);
				s[length - 1] = ch;
				length++;
			}
			break;
		}
	} while (ch != '\n' || length == 1 || length == 2 && *s == '-');
	number = atoi(s);
	free(s);
	printf("\n");
	return number;
}

/*
��������: ������� ��� ����� ������ y/n.
�������: 1 - 'y', 0 - 'n'.
*/
bool input_yn()
{
	char sy;       //�������� ������
	char ch;       //������� �������
	
	printf("��� �����(����� ������� ������ 'y' � 'n'): ");

	sy = '\0';

	do
	{
		
		switch (ch = my_getch())//�������� ������ ������� �������
		{
		case '\b':
			if (sy != '\0')
			{
				printf("\b \b");
			sy = '\0';
			}
			break;
		case 'y':
		case 'Y':
		case 'n':
		case 'N':
			if (sy != '\0')
				printf("\b \b");
			printf("%c", sy = ch);
			break;
		}
	} while (ch != '\n' || sy == '\0');
	printf("\n");
	return sy == 'y' || sy == 'Y';
}

/*
��������: ������� ��� ��������, �������� �� ����������� ������.
�������: 1 - ��������, 0 - �� ��������.
*/
bool is_allowed(char ch, char *not_allowed)
{
	bool b;//������ ���������� ������� � �����������
	for (b = 0; !b && *not_allowed != '\0'; not_allowed++)
		b = ch == *not_allowed;
	return !b;
}

/*
��������: ������� ��� ����� ������.
�������: ��������� �� ������ ������ �������� ������.
*/
char *input_string(int size,char *not_allowed)
{
	char *s;       //��������� �� ������ ������ �������� ������
	int length = 1;//����� ������
	char ch;       //�������� ������
	s = NULL;
	do
	{
		switch (ch = my_getch())
		{
		case '\b':
			if (length > 1)
			{
				printf("\b \b");//������� 1 ������
				length--;
				s = (char *)realloc(s, sizeof(char)*length);
			}
			break;
		case '\n':
			if (length > 1)
			{
				while (s[length - 2] == ' ')
				{
					length--; 
					s = (char *)realloc(s, sizeof(char)*length);
				}
				s[length - 1] = '\0';
			}
			break;
		default:
			if (is_allowed(ch, not_allowed) && length <= size && (ch != ' ' || length > 1 && s[length - 2] != ' '))
			{
				s = (char *)realloc(s, sizeof(char)*(length + 1));
				printf("%c", ch);
				s[length - 1] = ch;
				length++;
			}
			break;
		}
	} while (ch != '\n' || length == 1);
	printf("\n");

	return s;
}

/*
��������: ������� ��� ���������� ����� ������.
�������: ����� ������.
*/
int str_len(char*s)
{
	int i = 1;//����� ������
	while (*s)
		i++, s++;
	return i;
}

/*
��������: ������� ��� ��������, �������� �� ������ ��������� ������.
�������: 1 - ��������, 0 - �� ��������.
*/
bool is_sm_letter(char ch)
{
	return ch >= 'a' && ch <= 'z';
}

/*
��������: ������� ��� ��������, �������� �� ������ �������� ������.
�������: 1 - ��������, 0 - �� ��������.
*/
bool is_bi_letter(char ch)
{
	return ch >= 'A' && ch <= 'Z';
}

/*
��������: ������� ��� ��������� �������� ������.
�������: ������� �� ���������� ��������.
*/
void correct_name(char* s)
{
	if (s == NULL)
		return;
	if (*s == 0)
		return;

	char ra = 'A' - 'a';//������� � ����� ��������� � �������� ����
	bool is_p_let;      //������ ����������� �������(1-���������� ������ ����� 0-���������� ������ �� �����)

	if (is_sm_letter(*s))
	{
		*s += ra;//������ �� ��������� ����� ��������
		is_p_let = 1;
	}
	else
		is_p_let = is_bi_letter(*s);

	for (s = s + 1; *s; s++)
		if (is_p_let)
			if (is_bi_letter(*s))
				*s = *s - ra;//������ �� �������� ����� ���������
			else
				is_p_let = is_sm_letter(*s);
		else
			is_p_let = is_sm_letter(*s) || is_bi_letter(*s);
}

/*
��������: ������� ��� ����� �����.
�������: ��������� �� ������ ������ �������� ������.
*/
char* get_nt(char *title,char* name)
{
	char *s;  //��������� �� ������ ������ �����
	bool exit;//������ ������
	exit = 0;
	do
	{
		system("cls");
		puts(title);
		printf(S_input_nt_help);
		printf("������� %s:\n", name);
		s = input_string(50, "\x1b[]{}\\|*/-+,.^%$#@!&_=:;\"'1234567890`~");
		correct_name(s);
		printf("���������� ���:\n%s\n", s);
		puts("������� ����� ��� ���?('y'-�� 'n'-���)");
		if (input_yn())
		{
			free(s);
			s = NULL;
		}
		else
		exit = 1;
	} while (!exit);
	return s;
}

/*
��������: ������� ��� ����� ���� � �����.
�������: ��������� �� ������ ������ �������� ������.
*/
char* get_path(char* demo_f)
{
	char* file_name;//��������� �� ������ ������ ������, ���������� ���� � �����
	system("cls");
	if (demo_f!=NULL)
		printf("������� ������������ ����-����: \"%s\"?\n", demo_f);
	if (input_yn()&& demo_f!=NULL)
	{
		file_name = (char*)malloc(8*sizeof(char));
		strcpy(file_name,"txt.txt");
	}
	else
	{
		printf(S_input_path_help);
		puts("������� ���� � �����(���� � ����� ������ ��������� ���� �� 1 ������,");
		puts("�� �� ����� 70):");
		file_name = input_string(70, "");
	}

	return file_name;
}

/*
��������: ������� ��� ����� ���� ���������.
�������: ��������� �� ������ ������ �������� ������.
*/
char* get_type(char* title)
{
	char *types[] = { "Unknown", "Pinnace", "Rowbarge",
		"Galleon", "Shallop", "Bark", "Galliot", "Brigantine",
		"Galley", "Hoy", "Ketch", "Ship", "Sloop", "Fireship",
		"Ship of the Line", "Bomb Vessel", "Storeship", "Snow",
		"Yacht", "Praam" };
	//������ ���������� �� ������ ������ ������
	int i;    //��������������� ����������
	char *s;  //��������� �� ������ ������ �������� ������
	char type;//��� ���������
	char len; //����� ������
	puts("�������� ���:");
	for (i = 0; i < 20; i++)
		printf("%i-%s\n", i + 1, types[i]);
	puts("������ �����-���� ���� �������");
	printf("��� �����: ");
	type = input_number();
	if (type <= 0 || type > 20)
	{
		system("cls");
		s = get_nt(title,"���");//���� ���� �������
	}
	else
	{
		len = str_len(types[type - 1]);
		s = (char*)malloc(sizeof(char)*len);
		for (i = 0; i < len; i++)
			s[i] = types[type - 1][i];
	}
	return s;
}

/*
��������: ������� ��� ����� ���������.
�������: �������� ����������.
*/
int get_coord(char* title,char ch)
{
	puts(title);
	printf(S_input_number);
	printf("������� ��������� �� ��� %c � ����������� (����� ����� �� -999999 �� 9999999):\n", ch);
	return input_number();
}

/*
��������: ��� ������� ��� ����� ����� � �������� ��������.
�������: ��� ������� ���������� �������� �����.
*/
int get_sized(char* title,int min, int max, char* name)
{
	int num;//�������� �����
	do
	{
		puts(title);
		printf(S_input_number);
		printf("������� %s (����� ����� �� %i �� %i):\n", name, min, max);
		num = input_number();
		if (num < min || num > max)
		{
			printf("������. ���������� ������� %s(�� %i �� %i)\n", name, min, max);
			system("pause");
			system("cls");
		}
	} while (num < min || num > max);
	return num;
}

/*
��������: ������� ��������� ����� ���������.
�������: ������� �� ���������� ��������.
*/
void get_struct_info(DATA *info)
{
	system("cls");
	info->name = get_nt("���� ������ ���������","���");
	system("cls");
	info->type = get_type("���� ������ ���������");
	system("cls");
	info->x = get_coord("���� ������ ���������",'x');
	system("cls");
	info->y = get_coord("���� ������ ���������",'y');
	system("cls");
	info->z = get_coord("���� ������ ���������",'z');
	system("cls");
	info->m = get_sized("���� ������ ���������",10, 100000, "�������������");
	system("cls");
	info->speed = get_sized("���� ������ ���������", 0, 1000, "�������� � ��/�");
}

/*
��������: ������� ��� ����� ������.
�������: ��� ������� ���������� ��������� �� ������ ������� ������.
*/
OSHIP *O_get_structs()
{
	OSHIP* n_sp;      //��������� �� ������ ������� ������ ������
	OSHIP *n_el;      //��������� �� ����� �������
	OSHIP *last_el;   //��������� �� ��������� ������� ������
	bool is_end_input;//������ ������

	n_sp = (OSHIP*)malloc(sizeof(OSHIP));
	get_struct_info(&(n_sp->info));

	printf("���������� ����?('y'-�� 'n'-���):\n");

	if (input_yn())
	{
		last_el = n_sp;
		do
		{
			n_el = (OSHIP*)malloc(sizeof(OSHIP));
			get_struct_info(&(n_el->info));
			last_el->link1 = n_el;
			last_el = n_el;
			printf("���������� ����?('y'-�� 'n'-���):\n");
			is_end_input = !input_yn();
		} while (!is_end_input);
		last_el->link1 = NULL;
	}
	else
		n_sp->link1 = NULL;
	return n_sp;
}

/*
��������: ������� ��� ������ �������������� ����� ����� ���������.
�������: ������� �� ���������� ��������.
*/
void O_print_struct(OSHIP *ship)
{
	printf("��� ���������: \"%s\"\n", ship->info.name);
	printf("��� ���������: \"%s\"\n", ship->info.type);
	printf("��������� ��������� (x,y,z) � �����������: (%i,%i,%i)\n", ship->info.x, ship->info.y, ship->info.z);
	printf("�������������: %i\n", ship->info.m);
	printf("�������� � ��/�: %i\n", ship->info.speed);
}

/*
��������: ������� ��� ������ ������.
�������: ������� �� ���������� ��������.
*/
void O_print(OSHIP *ship)
{
	int i;//����� ���������
	puts("����� � ������� ��������");
	if (ship != NULL)
	{
		i = 0;
		do
		{
			if (i > 0 && i % 3 == 0)
			{
				system("pause");
				system("cls");
			}
			printf("�������� ����� %i\n", i + 1);
			O_print_struct(ship);
			puts("");
			ship = ship->link1;//��������� � ���������� �������
			i++;
		} while (ship != NULL);
		puts("����� �������");
	}
	else
		puts("��������� �����");

}

/*
��������: ������� ��� ������������ ������ ��-��� ����� ������.
�������: ��� ������� ���������� NULL.
*/
OSHIP* O_free_all(OSHIP* ship)
{
	OSHIP *link;//��������� �� �������, ��-��� �������� ������������� ������
	while (ship != NULL)
	{
		link = ship;//��������� ��������� �� ��������� �������
		ship = ship->link1;//��������� � ���������� �������
		free(link->info.name);
		link->info.name = NULL;
		free(link->info.type);
		link->info.type = NULL;
		free(link);
		link = NULL;
	}
	return NULL;
}

/*
��������: ��� ������� ��� �������� ���������� ��������� � ������.
�������: ��� ������� ���������� ���������� ��������� � ������.
*/
int O_get_len(OSHIP* ship)
{
	int i;      //���������� ��������� � ������
	i = 0;
	while (ship != NULL)
	{
		i++;
		ship = ship->link1;
	}
	return i;
}

/*
��������: ������� ��� ���������� �� ����� ������.
�������: ��� ������� ���������� ��������� �� ������ ������ ��������� ������.
*/
char* F_gets(char end, int maxlen, FILE* f)
{
	if (feof(f))
		return NULL;

	char *s;  //��������� �� ������ ������ ����������� ������
	bool exit;//������ ������
	int len;  //����� ������

	s = NULL;
	len = 0;
	exit = 0;
	do
	{
		s = (char*)realloc(s, sizeof(char)*(len + 1));
		exit = !fscanf(f,"%c",s + len);
		if (exit)
		{
			free(s);
			s = NULL;
		}
		else
		{
			if (s[len] == end)
			{
				s[len] = '\0';
				exit = 1;
			}
			len++;
		}
	} while (!exit);
	return s;
}

/*
��������: ��� ������� ��� ���������� ������ ����� ������������ �������� ��������� ������.
�������: ������� �� ���������� ��������.
*/
void O_add_after(OSHIP *sp, OSHIP *add_sp)
{
	if (sp != NULL)
	{
		OSHIP *li;//��������������� ���������
		for (li = add_sp; li->link1 != NULL; li = li->link1);
		li->link1 = sp->link1;
		sp->link1 = add_sp;
	}
}

/*
��������: ������� ��� �������� ������������ ������ � �����.
�������: ��� ������� ���������� 1 - ���� ������ ���������, 0 - ���� ���� ����, ��� ��� �� ����������, -1 - ���� ������ � ����� ����������.
*/
int test_file(char*file_name)
{
	FILE* f;     //��������� �� ������ � �����
	char* s;     //��������� �� ������ ������ ������
	int i;       //��������������� ����������
	if ((f = fopen(file_name, "r")) == NULL)
		return 0;
	if (feof(f))
		return 0;

	do
	{
		s = F_gets('\n', 50, f);
		if (s == NULL)
		{
			fclose(f);
			return -1;
		}
		if (s[0] == '\0')
			if (feof(f))
			{
				free(s);
				fclose(f);
				return 1;
			}
			else
			{
				free(s);
				fclose(f);
				return -1;
			}
		free(s);

		s = F_gets('\n', 20, f);
		if (s == NULL || s[0]=='\0')
		{
			free(s);
			fclose(f);
			return -1;
		}

		if (fscanf(f, "%i %i %i %i %i", &i, &i, &i, &i, &i) != 5)
		{
			fclose(f);
			return -1;
		}
		fscanf(f,"\n");
	} while (!feof(f));

	fclose(f);
	return 1;
}

/*
��������: ������� ��� ������ �������������� ����� � ���� � "��������" ����.
�������: ��� ������� ���������� 1 - ���� ������� ��������, ����� 0.
*/
bool save_good_placed(char*file_name, OSHIP*ship)
{
	if (ship == NULL)
	{
		puts("������ ����������");
		return 0;
	}
	FILE* f;     //��������� �� ������ � �����

	if ((f = fopen(file_name, "r")) != NULL)
		fclose(f);

	if (f == NULL)
	{
		f = fopen(file_name, "w");
	}
	else
	{
		puts("���� ��� ����������. ������� ������������ ���?");
		if (!input_yn())
		{
			puts("��������� �� ���� ��������� � ����");
			return 0;
		}
		f = fopen(file_name, "w");
	}
	if (f == NULL)
	{
		puts("������! �� ������� ������� ����");

		return 0;
	}
	if (fputs(S_table_fringe, f) < 0)
	{
		puts("�� ����� ������ ��������� ������");
		return fclose(f) * 0;
	}

	if (fprintf(f, "|%52s|%52s|%9s|%9s|%9s|%13s|%8s|\n", "��� ���������", "��� ���������", "x", "y", "z", "�������������", "��������") < 0)
	{
		puts("�� ����� ������ ��������� ������");
		return fclose(f) * 0;
	}

	if (fputs(S_table_fringe, f) < 0)
	{
		puts("�� ����� ������ ��������� ������");
		return fclose(f) * 0;
	}

	do
	{
		if( fprintf(f, "|%52s|%52s|%9i|%9i|%9i|%13i|%8i|\n", ship->info.name, ship->info.type, ship->info.x, ship->info.y, ship->info.z, ship->info.m, ship->info.speed) < 0)
		{
			puts("�� ����� ������ ��������� ������");
			return fclose(f) * 0;
		}

		if (fputs(S_table_fringe, f) < 0)
		{
			puts("�� ����� ������ ��������� ������");
			return fclose(f) * 0;
		}
		ship = ship->link1;
	} while (ship != NULL);
	fclose(f);
	puts("������ ������� �������� � ����");

	return 1;
}

/*
��������: ������� ��� ������ �������������� ����� � ����.
�������: ��� ������� ���������� 1 - ���� ������� ��������, ����� 0.
*/
bool save(char*file_name, OSHIP*ship, bool is_add)
{
	if (ship == NULL)
	{
		puts("������ ����������");
		return 0;
	}

	FILE* f;     //��������� �� ������ � �����
	OSHIP* link; //��������� �� ����������� �������
	f ;
	if ((f = fopen(file_name, "r")) != NULL)
		fclose(f);

	if (!is_add)
		if (f == NULL)
		{
			f = fopen(file_name, "w");
		}
		else
		{
			puts("���� ��� ����������. ������� ������������ ���?");
			if (!input_yn())
			{
				puts("��������� �� ���� ��������� � ����");
				return 0;
			}
			f = fopen(file_name, "w");
		}
	else
		if (f != NULL)
			f = fopen(file_name, "a");

	if (f == NULL)
	{
		puts("������! �� ������� ������� ����");
		return 0;
	}

	link = ship;
	do
	{
		if (fprintf(f, "%s\n%s\n%i\n%i\n%i\n%i\n%i\n", link->info.name, link->info.type, link->info.x, link->info.y, link->info.z, link->info.m, link->info.speed) < 0)
		{
			puts("�� ����� ������ ��������� ������");
			return fclose(f) * 0;
		}
		link = link->link1;
	} while (link != NULL);

	fclose(f);
	puts("������ ������� �������� � ����");
	return 1;
}

/*
��������: ������� ��� ����� ������ �� �����.
�������: ��� ������� ���������� ��������� �� ������ ������� ������������ ������.
*/
OSHIP *load(char *file_name)
{
	OSHIP* ship;//��������� �� ������ ������� ������
	OSHIP* el;  //��������������� ���������
	OSHIP* last;//��������� �� ��������� ������� ������
	FILE *f;    //��������� �� ������ � �����
	bool err;   //������ ������
	bool end;   //������ ����� �����
	char *s;    //��������� �� ������ ������ ��������� �������

	f = fopen(file_name, "r");

	if (f == NULL)
		return NULL;

	err = 0;
	end = 0;
	ship = NULL;

	do
	{
		s = F_gets('\n', 50, f);
		if (s != NULL)
		{
			if (s[0] != '\0')
			{
				el = (OSHIP*)malloc(sizeof(OSHIP));

				el->link1 = NULL;
				el->info.type = NULL;
				el->info.name = s;

				if (ship != NULL)
				{
					O_add_after(last, el);
					last = last->link1;
				}
				else
					ship = last = el;

				
				if ((s = F_gets('\n', 50, f)) != NULL)
				{
					el->info.type = s;
					err = fscanf(f, "%i %i %i %i %i", &(el->info.x), &(el->info.y), &(el->info.z), &(el->info.m), &(el->info.speed)) != 5;
				}
				else
					err = 1;
				fscanf(f, "\n");
			}
			else
			{
				free(s);
				end = 1;
			}
		}
		else
			if (feof(f))
				end = 1;
			else
				err = 1;
	} while (!err && !end);

	if (err)
		ship = O_free_all(ship);

	fclose(f);
	return ship;
}

/*
��������: ��� ������� ��� ������ ���� ����������.
�������: ������� �� ���������� ��������.
*/
void select_sort(SORTDATA *sort)
{
	bool b;   //��������������� ������
	int i;    //��������������� ����������
	int len;  //���������� ���������
	int r;    //��������������� ����������
	int o;    //��������������� ����������

	do
	{
		puts("�� �������� ����� ����� ����������� ���������� (�� 1 �� 7)?");
		len = input_number();
		if (len < 1 || len > 7)
			puts("������");
	} while (len < 1 || len > 7);
	puts("�� ������ �������� ����������� � ������ �������?");

	do
	{
		puts("��������");
		puts("1-���");
		puts("2-���");
		puts("3-x");
		puts("4-y");
		puts("5-z");
		puts("6-�������������");
		puts("7-��������");

		r = input_number();
		if (r < 1 || r > 7)
			puts("������");
	} while (r< 1 || r > 7);
	sort->typ[0] = r;
	do
	{
		puts("����������� �� ������� ��������:");
		puts("1-�� �����������");
		puts("2-�� ��������");
		r = input_number();
		if (r < 1 || r > 7)
			puts("������");
	} while (r < 1 || r > 7);
	switch (sort->typ[0])
	{
	case 1:
		sort->s_name = r;
		break;
	case 2:
		sort->s_type = r;
		break;
	case 3:
		sort->s_x = r;
		break;
	case 4:
		sort->s_y = r;
		break;
	case 5:
		sort->s_z = r;
		break;
	case 6:
		sort->s_m = r;
		break;
	case 7:
		sort->s_speed = r;
		break;
	}
	for (i = 1; i < len; i++)
	{
		puts("�� ������ �����?");
		do
		{
			do
			{
				puts("��������");
				puts("1-���");
				puts("2-���");
				puts("3-x");
				puts("4-y");
				puts("5-z");
				puts("6-�������������");
				puts("7-��������");

				r = input_number();
				if (r < 1 || r > 7)
				{
					puts("��� ������ ������ ����");
					system("pause");
				}
			} while (r < 1 || r > 7);
			b = 1;
			for (o = 0; o < i && b; o++)
				b = sort->typ[o] != r;
			if (!b)
				puts("�� ��� �������� ������ ����. �������� ������ ������");
		} while (!b);
		sort->typ[i] = r;
		do
		{
			puts("����������� �� ������� ��������:");
			puts("1-�� �����������");
			puts("2-�� ��������");
			r = input_number();
			if (r < 1 || r > 7)
				puts("������");
		} while (r < 1 || r > 7);
		switch (sort->typ[i])
		{
		case 1:
			sort->s_name = r;
			break;
		case 2:
			sort->s_type = r;
			break;
		case 3:
			sort->s_x = r;
			break;
		case 4:
			sort->s_y = r;
			break;
		case 5:
			sort->s_z = r;
			break;
		case 6:
			sort->s_m = r;
			break;
		case 7:
			sort->s_speed = r;
			break;
		}
	}
	if (len < 7)
		sort->typ[len] = 0;
}

//������� ��� ������ ���� ������

/*
��������: ��� ������� ��� ������ ���� ������.
�������: ������� �� ���������� ��������.
*/
void select_find(FINDDATA *find)
{
	int i;      //��������������� ����������
	int len;    //���������� �����, �� ������� ����� ����������� �����
	int r;      //��������������� ����������
	char typ[7];//������ ������� 7 ������ � ����������
	int o;      //��������������� ����������

	for (i = 0; i < 7; i++)
		typ[i] = 0;

	find->s_name = 0;
	find->s_type = 0;
	find->s_x = 0;
	find->s_y = 0;
	find->s_z = 0;

	do
	{
		puts("�� �������� ����� ����� ����������� ����� (�� 1 �� 7)?");
		len = input_number();
		if (len < 1 || len > 7)
			puts("������");
	} while (len < 1 || len > 7);

	i = 0;
	do
	{
		do
		{
			do
			{
				puts("�������� ����, �� �������� ����� ����������� �����");
				puts("��������");
				puts("1-���");
				puts("2-���");
				puts("3-x");
				puts("4-y");
				puts("5-z");
				puts("6-�������������");
				puts("7-��������");

				r = input_number();
				if (r < 1 || r > 7)
					puts("������");
			} while (r < 1 || r > 7);
			if (typ[r - 1] != 0)
				puts("�� ��� �������� ������ ����. �������� ������ ������");
		} while (typ[r - 1] != 0);
		typ[r - 1] = 1;
		puts("������� �������� ��� ���������:");
		switch (r)
		{
		case 1:
			find->name = get_nt("���� ������ ��� ���������", "��� ���������");
			break;
		case 2:
			find->type = get_type("���� ������ ��� ���������");
			break;
		case 3:
			find->x = get_coord("���� ������ ��� ���������", 'x');
			break;
		case 4:
			find->y = get_coord("���� ������ ��� ���������", 'y');
			break;
		case 5:
			find->z = get_coord("���� ������ ��� ���������", 'z');
			break;
		case 6:
			find->m = get_sized("���� ������ ��� ���������", 10, 100000, "�������������");
			break;
		case 7:
			find->speed = get_sized("���� ������ ��� ���������", 0, 1000, "�������� � ��/�");
			break;
		}

		do
		{
			puts("������� ������� ��� ��������� ��� ������� ������� ��������:");
			puts("1-��������� �������� ��������");
			puts("2-������ ��������� ��������");
			puts("3-��������� � �������� ���������");
			o = input_number();
			if (o < 1 || o > 3)
				puts("������");
		} while (o < 1 || o > 3);

		switch (r)
		{
		case 1:
			find->s_name = o;
			break;
		case 2:
			find->s_type = o;
			break;
		case 3:
			find->s_x = o;
			break;
		case 4:
			find->s_y = o;
			break;
		case 5:
			find->s_z = o;
			break;
		case 6:
			find->s_m = o;
			break;
		case 7:
			find->s_speed = o;
			break;
		}
		i++;
	} while (i<len);

}

/*
��������: ��� ������� ��� ��������� ���� ���������.
�������: ��� ������� ���������� 1 ���� a ������ b, ����� 0.
*/
bool a_sma_b(DATA a, DATA b, SORTDATA * sort_t)
{
	char state;//�������� ����������(1 - a < b, 0 - a == b, -1 - a > b)
	int i;     //��������������� ����������

	state = 0;
	for (i = 0; i < 7 && sort_t->typ[i] && !state; i++)
	{
		switch (sort_t->typ[i])
		{
		case 1:
			state = strcmp(a.name, b.name) > 0;
			if (!state)
				state = -(strcmp(a.name, b.name) < 0);
			if (sort_t->s_name == 2)
				state = -state;
			break;
		case 2:
			state = strcmp(a.type, b.type)>0;
			if (!state)
				state = -(strcmp(a.type, b.type)<0);
			if (sort_t->s_type == 2)
				state = -state;
			break;
		case 3:
			state = a.x > b.x;
			if (!state)
				state = -(a.x < b.x);
			if (sort_t->s_x == 2)
				state = -state;
			break;
		case 4:
			state = a.y > b.y;
			if (!state)
				state = -(a.y < b.y);
			if (sort_t->s_y == 2)
				state = -state;
			break;
		case 5:
			state = a.z > b.z;
			if (!state)
				state = -(a.z < b.z);
			if (sort_t->s_z == 2)
				state = -state;
			break;
		case 6:
			state = a.m > b.m;
			if (!state)
				state = -(a.m < b.m);
			if (sort_t->s_m == 2)
				state = -state;
			break;
		case 7:
			state = a.speed > b.speed;
			if (!state)
				state = -(a.speed < b.speed);
			if (sort_t->s_speed == 2)
				state = -state;
			break;
		}
	}
	return state == 1;
}

/*
��������: ������� ��� �����������, �������� �� ������� ��������� ������.
�������: ��� ������� ���������� 1 ���� ��������, ����� 0.
*/
bool is_need(DATA info, FINDDATA *find)
{
	switch (find->s_name)
	{
	case 1:
		if (strcmp(info.name, find->name) <= 0)
			return 0;
		break;
	case 2:
		if (strcmp(info.name, find->name) >= 0)
			return 0;
		break;
	case 3:
		if (strcmp(info.name, find->name) != 0)
			return 0;
		break;
	}
	switch (find->s_type)
	{
	case 1:
		if (strcmp(info.type, find->type) <= 0)
			return 0;
		break;
	case 2:
		if (strcmp(info.type, find->type) >= 0)
			return 0;
		break;
	case 3:
		if (strcmp(info.type, find->type) != 0)
			return 0;
		break;
	}
	switch (find->s_x)
	{
	case 1:
		if (info.x <= find->x)
			return 0;
		break;
	case 2:
		if (info.x >= find->x)
			return 0;
		break;
	case 3:
		if (info.x != find->x)
			return 0;
		break;
	}
	switch (find->s_y)
	{
	case 1:
		if (info.y <= find->y)
			return 0;
		break;
	case 2:
		if (info.y >= find->y)
			return 0;
		break;
	case 3:
		if (info.y != find->y)
			return 0;
		break;
	}
	switch (find->s_z)
	{
	case 1:
		if (info.z <= find->z)
			return 0;
		break;
	case 2:
		if (info.z >= find->z)
			return 0;
		break;
	case 3:
		if (info.z != find->z)
			return 0;
		break;
	}
	switch (find->s_m)
	{
	case 1:
		if (info.m <= find->m)
			return 0;
		break;
	case 2:
		if (info.m >= find->m)
			return 0;
		break;
	case 3:
		if (info.m != find->m)
			return 0;
		break;
	}
	switch (find->s_speed)
	{
	case 1:
		if (info.speed <= find->speed)
			return 0;
		break;
	case 2:
		if (info.speed >= find->speed)
			return 0;
		break;
	case 3:
		if (info.speed != find->speed)
			return 0;
		break;
	}
	return 1;
}

/*
��������: ��� ������� ��� ���������� ������ � ������ ��������� ������.
�������: ��� ������� ���������� ��������� �� ������ ������� ������.
*/
OSHIP* O_add_frist(OSHIP *sp, OSHIP *add_sp)
{
	if (add_sp != NULL)
	{
		OSHIP *li;//��������������� ���������
		for (li = add_sp; li->link1 != NULL; li = li->link1);
		li->link1 = sp;
		return add_sp;
	}
	else
		return sp;
}


/*
��������: ��� ������� ��� ���������� ������ � �������� �����.
�������: ��� ������� ���������� ��������� �� ������ ������� ������.
*/
OSHIP *O_insert_spis(OSHIP *ship, OSHIP *nsp)
{
	int menu;      //��������� ����� ����
	int n;         //����� ��������
	int len;       //���������� ��������� � ������
	OSHIP *link;   //��������� �� ����������� �������
	char*file_name;//��������� �� ������ ������ ������, ���������� ���� � �����


	len = O_get_len(ship);
	do
	{
		system("cls");
		puts("�������");
		puts("1-�������� � ������ ���������");
		puts("2-�������� ����� n-���� �������� � ���������");
		puts("3-�������� � ����� ���������, ���������� � ����");
		puts("0-������ ������, �� �������� ��");
		menu = input_number();
		if (menu<0 || menu>3)
		{
			puts("��� ������ ������");
			system("pause");
		}
		switch (menu)
		{
		case 1:
			ship = O_add_frist(ship, nsp);
			puts("����� �������� ������� ���������");
			menu = 0;
			break;
		case 2:
			if (ship != NULL)
			{
				do
				{
					printf("������� ����� ��������, ����� �������� ����� �����������\n�������� (�� 1 �� %i):", len);
					n = input_number();
					if (n < 1 || n > len)
					{
						puts("������");
						printf("������ ����� �� 1 �� %i\n",len);
						system("pause");
					}
				} while (n < 1 || n > len);

				for (link = ship; n > 1; link = link->link1, n--);

				O_add_after(link, nsp);
				puts("����� �������� ������� ���������");
				menu = 0;
			}
			else
			{
				puts("��� ��������� � ���������");
				puts("������� �������� ������ � ������ ���������?('y'-�� 'n'-���)");
				if (input_yn())
				{
					ship = nsp;
					menu = 0;
					puts("����� �������� ������� ���������");
				}

			}
			break;
		case 3:
				
			
			file_name = get_path(NULL);
			
			if (test_file(file_name) != -1)
				if (save(file_name, nsp,1))
				{
					nsp = O_free_all(nsp);
					menu = 0;
				}
				else
					system("pause");
			else
			{
				puts("��������� ���� ���� �������� ��� �������� ������ �� ������ ���������");
				system("pause");
			}
			free(file_name);
			file_name = NULL;
			break;
		case 0:
			nsp = O_free_all(nsp);
			puts("������ ���� ������� ������");
			break;
		}
	} while (menu);

	return ship;
}

/*
��������: ������� ��� �������� ���� �����.
�������: ��� ������� ���������� ��������� �� ������ ������� ��������� ������.
*/
OSHIP *input_menu(OSHIP *ship)
{
	int menu;       //��������� ����� ����
	char *file_name;//��������� �� ������ ������ ������ ���� � �����
	OSHIP* nsp;     //��������� �� ������ ������� ��������� ������

	do
	{
		system("cls");
		puts("���� ������ � ���������");
		puts("1-� ����������");
		puts("2-�� �����");
		puts("0-������� � �������");
		printf("��� �����: ");
		menu = input_number();
		switch (menu)
		{
		case 1:
			nsp = O_get_structs();
			puts("������ ������� �������");
			system("pause");
			ship = O_insert_spis(ship, nsp);
			nsp = NULL;
			system("pause");
			break;
		case 2:
			file_name = get_path("txt.txt");

			nsp = load(file_name);
			if (nsp != NULL)
			{
				puts("������ ������� ���������");
				system("pause");
				ship = O_insert_spis(ship, nsp);
				nsp = NULL;
			}
			else
				puts("�� ������� ��������� ������ �� �����");
			
			free(file_name);
			
			system("pause");
			break;
		case 0:
			break;
		default:
			puts("��� ������ ������ ����");
			system("pause");
			break;
		}
	} while (menu);

	return ship;
}

/*
��������: ������� ��� �������� ���� ������ ������.
�������: ������� �� ���������� ��������.
*/
void output_menu(OSHIP *ship,char* title)
{
	if (ship == NULL)
	{
		puts("��������� ����� ������������� ������");
		puts("��� ����� ��������� ��������: ������� ����->���� ������ � ���������");
		system("pause");
		return;
	}
	int menu;       //��������� ����� ����
	char *file_name;//��������� �� ������ ������ ������ ���� � �����

	file_name = (char*)malloc(sizeof(char)* 8);
	strcpy(file_name, "txt.txt");

	do
	{
		system("cls");
		printf("����� %s\n",title);
		puts("1-�� �����");
		puts("2-� ����");
		puts("3-��������� ������������ ����");
		puts("0-������� � �������");
		printf("��� �����: ");
		menu = input_number();
		switch (menu)
		{
		case 1:
			system("cls");
			O_print(ship);
			system("pause");
			break;
		case 2:
			system("cls");
			file_name = get_path("out.txt");

			puts("������� �������� ���� � '��������' ���� ?");
			puts("��� ������ � '��������' ���� ���� ����� ����� ���������� ���������");
			puts("� ������ ������ ���������, �� ����� �������� ��������� � �������");
			puts("���������� ���������");
			puts("(y-�� n-���):");
			if (input_yn())
				save_good_placed(file_name, ship);
			else
				save(file_name, ship, 0);
			free(file_name);
			system("pause");
			break;
		case 3:
			system("cls");
			file_name = get_path(NULL);
			if (test_file(file_name) != -1)
				save(file_name, ship, 1);
			else
				puts("��������� ���� ���� �������� ��� �������� ������ �� ������ ���������");

			free(file_name);
			file_name = NULL;

			system("pause");
			break;
		case 0:
			break;
		default:
			puts("��� ������ ������ ����");
			system("pause");
			break;
		}
	} while (menu);

}

/*
��������: ������� ��� �������� ���� ��������.
�������: ��� ������� ���������� ��������� �� ������ ������� ������.
*/
OSHIP* remove_menu(OSHIP* ship)
{
	int menu;       //��������� ����� ����
	char *file_name;//��������� �� ������ ������ ������ ���� � �����
	
	file_name = (char*)malloc(sizeof(char) * 8);
	strcpy(file_name, "txt.txt");

	do
	{
		system("cls");
		puts("�������� ���������");
		puts("1-��������� �� ����������� ������");
		puts("2-����� � ����������");
		puts("0-������� � �������");
		printf("��� �����: ");
		menu = input_number();
		switch (menu)
		{
		case 1:
			system("cls");
			if (ship != NULL)
			{
				ship = O_free_all(ship);
				puts("�������� ��������� �� ����������� ������ ������ �������");
			}
			else
				puts("��������� �����. ������� �� ����������� ������ ������");
			system("pause");
			break;
		case 2:
			system("cls");
			
			file_name = get_path("out.txt");
			
			if (remove(file_name) == 0)
				puts("���� � ���������� �����");
			else
				puts("�� ������� ������� ���� � ����������");

			free(file_name);
			file_name = NULL;

			system("pause");
			break;
		case 0:
			break;
		default:
			puts("��� ������ ������ ����");
			system("pause");
			break;
		}
	} while (menu);
	return ship;
}

/*
��������: ������� ��� �������� ���� �������.
�������: ������� �� ���������� ��������.
*/
void help_menu()
{
	int menu;       //��������� ����� ����

	do
	{
		system("cls");
		puts("�������");
		puts("1-�� �����");
		puts("2-�� ������");
		puts("3-�� ��������� ������");
		puts("4-�����������");
		puts("0-������� � �������");
		printf("��� �����: ");
		menu = input_number();
		system("cls");
		switch (menu)
		{
		case 1:
			system("cls");
			puts("������� ������ ��������� ����������");
			puts("��� ����� ����� � ����");
			printf(S_input_nt_help);
			puts("");
			puts("��� ����� ���������");
			puts(S_input_number);
			system("pause");
			break;
		case 2:
			system("cls");
			puts("��� ������ �� �����:");
			puts("  �������� ��������� ���������������");
			puts("  �������� ��������� ���������� �������� �� 3 ��. �� ���");
			puts("");
			puts("��� ������ � ����:");
			puts("  ������������ ������ ������� ������ � ��������� ���� ����");
			puts("  ���� � ����� ���� �����-�� ����������, �� ������������");
			puts("  ������������ ���, ��� �� ��������������");
			puts("  ���� ����� �� ����������, �� �������� ������ ���� � � ����");
			puts("  ������������ ������.");
			puts("  ���� ����� �������� � '��������' � � ������� ����.");
			puts("  ��� ������ � ���� � '��������' ����, ��������� ��� � �������");
			puts("  ���� ��������� ����� ����������, �� ����� �������� ���������");
			puts("  � ������� ��������.");
			puts("  ��� ������ � ������� ���� ���� ����� ����� ��������� ������");
			puts("  � ������� ������ ���������.");
			puts("��� ���������� ������ � ����:");
			puts("  ������ � ����� ����� ��������� �� ������������.");
			puts("  ������ ����� ��������� � ���� ������ ���� ������");
			puts("  � ����� ���������.");
			puts("  �������� ������ � ������ ���� ����������.");

			system("pause");
			break;
		case 3:
			system("cls");
			puts("��� ��������� ��� ��������, ��������, ���������� ���������");
			puts("���� ������� ��������� �������� ������ �� ����� ���������, � ������:");
			puts("  1. ��� ��������� - ������ � ������������ ������ 50 ��������");
			puts("  2. ��� ��������� - ������ � ������������ ������ 50 ��������");
			puts("  3. ��������� ��������� �� ��� x");
			puts("  4. ��������� ��������� �� ��� y");
			puts("  5. ��������� ��������� �� ��� z");
			puts("  6. �������������");
			puts("  7. �������� ���������");
			puts("������ ��������� �� ��������� ����");
			system("pause");
			break;
		case 4:
			puts("������� ������ ��������� ����������");
			puts("������� ��������� ������� ���������");
			puts("��� ��������� ����� ����������� ����� 50 �������� � ������� ������ ��:");
			puts("  -���������� ����");
			puts("  -��������");
			puts("  -������� ������");
			puts("��� ��������� ������ ���������� � ������� �����");
			puts("��� ��������� ����� ����������� ����� 50 �������� � ������� ������ ��:");
			puts("  -���������� ����");
			puts("  -��������");
			puts("  -������� ������");
			puts("��� ��������� ������ ���������� � ������� �����");
			puts("������������� ��������� ����� ���� ������ � �� � ������ ����� ������ ��");
			puts("10 �� 100000");
			puts("�������� ��������� ����� ���� ������ � ��/� � ������ ����� ������ ��");
			puts("0 �� 1000");
			system("pause");
			break;
		case 0:
			break;
		default:
			puts("��� ������ ������ ����");
			system("pause");
			break;
		}
	} while (menu);
}

/*
��������: ��� ������� ��� �������� ����� �������� ������.
�������: ��� ������� ���������� ��������� �� ����������� �������.
*/
OSHIP *O_create_copy(OSHIP* ship)
{
	OSHIP *new_ship;//��������� �� ����� ��������
	int i;          //��������������� ����������
	int len;        //���������� ��������� � ������
	if (ship != NULL)
	{
		new_ship = (OSHIP*)malloc(sizeof(OSHIP));
		new_ship->info.x = ship->info.x;
		new_ship->info.y = ship->info.y;
		new_ship->info.z = ship->info.z;
		new_ship->info.m = ship->info.m;
		new_ship->info.speed = ship->info.speed;

		len = str_len(ship->info.name);
		new_ship->info.name = (char*)malloc(len*sizeof(char));
		for (i = 0; i < len; i++)
			new_ship->info.name[i] = ship->info.name[i];

		len = str_len(ship->info.type);
		new_ship->info.type = (char*)malloc(len*sizeof(char));
		for (i = 0; i < len; i++)
			new_ship->info.type[i] = ship->info.type[i];
		new_ship->link1 = NULL;
	}
	else
		new_ship = NULL;
	return new_ship;
}

/*
��������: ��� ������� ��� ������.
�������: ��� ������� ���������� ��������� �� ������ ������� ������.
*/
OSHIP* O_find(FINDDATA*find, OSHIP*ship)
{
	if (ship == NULL)
	{
		puts("��� ��������� � ���������");
		return NULL;
	}
	OSHIP* ship_res;//��������� �� ������ ������� ������ � ������������ ������
	OSHIP* link;    //��������������� ���������
	OSHIP* new_el;  //��������� �� ������������ �������

	ship_res = NULL;

	do
	{
		if (is_need(ship->info, find))
		{
			new_el = O_create_copy(ship);
			if (ship_res == NULL)
				ship_res = new_el;
			else
				link->link1 = new_el;
			link = new_el;
		}
		ship = ship->link1;
	} while (ship != NULL);
	if (ship_res != NULL)
	{
		link->link1 = NULL;
		puts("����� ��������");
	}
	else
		puts("�� ������� ���������, ��������������� �������� ���������");
	return ship_res;
}

/*
��������: ��� ������� ��� ���������� �������� � ��������������� ������.
�������: ��� ������� ���������� ��������� �� ������ ������� ������.
*/
OSHIP *O_insert(OSHIP *ship, OSHIP *el, SORTDATA*sort)
{
	if (ship != NULL)
		if (!a_sma_b(ship->info, el->info, sort))
		{
			OSHIP* l;//��������������� ���������
			l = ship;
			while (ship->link1 != NULL)
			{
				if (a_sma_b(ship->link1->info, el->info, sort))
				{
					O_add_after(ship, el);
					return l;
				}
				ship = ship->link1;
			}
			ship->link1 = el;
			return l;
		}
		else
		{
			el->link1 = ship;
			return el;
		}
	else
	{
		el->link1 = NULL;
		return el;
	}
}

/*
��������: ��� ������� ��� ����������.
�������: ��� ������� ���������� ��������� �� ������ ������� ������.
*/
OSHIP *O_sort(OSHIP *ship, SORTDATA *sort)
{
	if (ship == NULL)
	{
		puts("������ �����������");
		return NULL;
	}
	OSHIP *ship_sorted;//��������� �� ������ ������� ���������������� ������
	OSHIP *link;       //��������� �� ����������� �������

	ship_sorted = NULL;

	do
	{
		link = ship;
		ship = ship->link1;
		link->link1 = NULL;
		ship_sorted = O_insert(ship_sorted, link, sort);
	} while (ship != NULL);
	puts("���������� ��������");
	puts("��� ������ �������������� ��������� ��������:");
	puts("������� ����->����� ���������");
	return ship_sorted;
}

/*
��������: ��� ������� ��� �������� ���� ��������� ������.
�������: ��� ������� ���������� ��������� �� ������ ������� ������.
*/
OSHIP* calculate_menu(OSHIP* ship)
{
	if (ship == NULL)
	{
		puts("��������� ����� ������������� ������");
		puts("��� ����� ��������� ��������: ������� ����->���� ������ � ���������");
		system("pause");
		return ship;
	}
	SORTDATA sort; //��������� ����������
	FINDDATA find; //��������� ������
	OSHIP*link;    //��������������� ���������
	OSHIP*ship_res;//��������� �� ������ ������� ������ � ������������ ������
	int menu;      //��������� ����� ����

	find.name = NULL;
	find.type = NULL;

	do
	{
		system("cls");
		puts("���������");
		puts("1-���������� ��������� ���������");
		puts("2-�����");
		puts("0-������� � �������");
		printf("��� �����: ");
		menu = input_number();
		system("cls");
		switch (menu)
		{
		case 1:
			select_sort(&sort);
			ship=O_sort(ship, &sort);
			system("pause");
			break;
		case 2:
			free(find.name);
			find.name = NULL;
			free(find.type);
			find.type = NULL;
			select_find(&find);
			ship_res = O_find(&find, ship);
			system("pause");
			if (ship_res!=NULL)
			{
				output_menu(ship_res, "����������� ������");
				ship_res = O_free_all(ship_res);
			}
			break;
		case 0:
			break;
		default:
			puts("��� ������ ������ ����");
			system("pause");
			break;
		}
	} while (menu);
	free(find.name);
	find.name = NULL;
	free(find.type);
	find.type = NULL;
	return ship;
}

/*
��������: ��� ������� ��� �������������� ������ ��������.
�������: ������� �� ���������� ��������.
*/
void edit_one(OSHIP *ship)
{
	int menu;//��������� ����� ����

	do
	{
		system("cls");
		puts("������������� �������:");
		O_print_struct(ship);

		puts("���� ��������������");
		puts("1-������������� ���� ���");
		puts("2-������������� ���� ���");
		puts("3-������������� ���� x");
		puts("4-������������� ���� y");
		puts("5-������������� ���� z");
		puts("6-������������� ���� �������������");
		puts("7-������������� ���� ��������");
		puts("0-����� � �������");
		puts("��� �����:");
		menu = input_number();
		system("cls");
		switch (menu)
		{
		case 1:
			free(ship->info.name);
			ship->info.name = NULL;
			ship->info.name = get_nt("���� ������ ��� ���������", "���");
			puts("���� ��� ������� ���������������");
			system("pause");
			break;
		case 2:
			free(ship->info.type);
			ship->info.type = NULL;
			ship->info.type = get_type("���� ������ ��� ���������");
			puts("���� ��� ������� ���������������");
			system("pause");
			break;
		case 3:
			ship->info.x = get_coord("���� ������ ��� ���������", 'x');
			puts("���� x ������� ���������������");
			system("pause");
			break;
		case 4:
			ship->info.y = get_coord("���� ������ ��� ���������", 'y');
			puts("���� y ������� ���������������");
			system("pause");
			break;
		case 5:
			ship->info.z = get_coord("���� ������ ��� ���������", 'z');
			puts("���� z ������� ���������������");
			system("pause");
			break;
		case 6:
			ship->info.m = get_sized("���� ������ ��� ���������", 10, 100000, "�������������");
			puts("���� �������������� ������� ���������������");
			system("pause");
			break;
		case 7:
			ship->info.speed = get_sized("���� ������ ��� ���������", 0, 1000, "�������� � ��/�");
			puts("���� �������� ������� ���������������");
			system("pause");
			break;
		case 0:
			break;
		}
	} while (menu);
}

/*
��������: ��� ������� ��� �������� ���� ��������� ��������� ������.
�������: ������� �� ���������� ��������.
*/
void charg_menu(OSHIP *ship)
{
	if (ship == NULL)
	{
		puts("��������� ����� ������������ ������");
		puts("��� ����� ��������� ��������: ������� ����->���� ������ � ���������");
		system("pause");
		return;
	}
	OSHIP* link;              //��������� �� ������������� �������
	int len = O_get_len(ship);//���������� ��������� � ������
	int n;                    //����� ����������� ��������
	if (len != 0)
		do
		{
			puts(S_input_number);
			printf("������� ����� �������������� �������� �� 1 �� %i(0-������� � �������):\n",len);
			n = input_number();
			if (n < 0 || n > len)
			{
				puts("������! �� ����� ����� ��� ������� ��������");
				system("pause");
			}
			else
			{
				if (n > 0)
				{
					link = ship;
					for (; n > 1; n--,link=link->link1);
					edit_one(link);
				}
			}
		} while (n!=0);
}

/*
��������: ��� ������� ��� �������� ������ �������� �� ������.
�������: ������� �� ���������� ��������.
*/
void O_del_one(OSHIP **link)
{
	if (*link != NULL)
	{
		OSHIP *l;//��������������� ���������
		l = *link;
		*link = (*link)->link1;
		free(l->info.name);
		free(l->info.type);
		free(l);
	}
}

/*
��������: ��� ������� ��� �������� ���� �������� ���������.
�������: ��� ������� ���������� ��������� �� ������ ������� ������.
*/
OSHIP* del_menu(OSHIP* ship)
{
	int menu;                 //��������� ����� ����
	int len = O_get_len(ship);//���������� ��������� � ������
	OSHIP *link;              //��������������� ���������
	OSHIP **link_l;           //��������� �� ������ ������ � ������� �������� ����� ���������� ��������
	int n;                    //����� ������� ��������� ��������
	int m;                    //����� ���������� ��������� ��������
	int i;                    //��������������� ����������

	do
	{
		if (ship != NULL)
		{
			puts("�������� ��������� ���������");
			puts("1-������� �������� � n �� m");
			puts("2-������� ������ �������");
			puts("3-������� ��������� �������");
			puts("0-����� � �������");
			puts("��� �����:");
			menu = input_number();
			system("cls");
			switch (menu)
			{
			case 1:
				n = get_sized("�������� ��������� ��������� � n �� m", 1, len, "n");
				m = get_sized("�������� ��������� ��������� � n �� m", n, len, "m");

				for (i = 2, link = ship; i < n; i++, link = link->link1);

				if (n == 1)
					link_l = &ship;
				else
					link_l = &link->link1;

				i = m - n + 1;

				do
				{
					O_del_one(link_l);
					i--;
				} while (i > 0);

				puts("�������� ������� �������");
				system("pause");
				len = O_get_len(ship);
				break;
			case 2:
				O_del_one(&ship);

				puts("������� ������� ������");
				system("pause");
				len--;
				break;
			case 3:
				link_l = &ship;
				for (; (*link_l)->link1 != NULL; link_l = &(*link_l)->link1);
				O_del_one(link_l);
				puts("������� ������� ������");
				system("pause");
				len--;
				break;
			case 0:
				break;
			default:
				puts("��� ������ ������ ����");
				system("pause");
				break;
			}
		}
		else
		{
			puts("� ��������� ������ ��� ���������.");
			puts("������ �� �������� � ������� ����");
			system("pause");
			menu = 0;
		}
	} while (menu);
	return ship;
}

/*
��������: ��� ������� ��� �������� ���� ��������������.
�������: ��� ������� ���������� ��������� �� ������ ������� ������.
*/
OSHIP* edit_menu(OSHIP *ship)
{
	if (ship == NULL)
	{
		puts("��������� ����� ������������� ������");
		puts("��� ����� ��������� ��������: ������� ����->���� ������ � ���������");
		system("pause");
		return ship;
	}
	int menu;       //��������� ����� ����

	do
	{
		system("cls");
		puts("�������������� ���������");
		puts("1-��������� ������ ��������");
		puts("2-�������� ���������");
		puts("0-������� � �������");
		printf("��� �����: ");
		menu = input_number();
		system("cls");
		switch (menu)
		{
		case 1:
			charg_menu(ship);
			break;
		case 2:
			ship = del_menu(ship);
			break;
		case 0:
			break;
		default:
			puts("��� ������ ������ ����");
			system("pause");
			break;
		}
	} while (menu&&ship!=NULL);
	return ship;
}

/*
��������: ��� ������� ��� �������� ���� ���������� ��������� ��� ������.
�������: ��� ������� ���������� ��������� �� ������ ������� ������.
*/
void exit_save(OSHIP* ship)
{
	bool saved;     //������ ���������� � ����
	char *file_name;//��������� �� ������ ������ ������ ���� � �����

	do
	{
		system("cls");
		puts("������ � ����������� ������ ��������� ���������");
		puts("��� ������ ��� ����� �������");
		puts("������� ��������� � � ����?(y-�� n-���)");
		if (input_yn())
		{
			file_name = get_path("out.txt");
			saved = save(file_name, ship, 0);
			free(file_name);
			if (saved)
			{
				puts("��������� ������� ��������� � ����");
				system("pause");
			}
		}
		else
			saved = 1;
	} while (!saved);
}

/*
��������: ��� ������� ��� �������� �������� ����.
_________
*/
int main()
{
	setlocale(0, "RU");
	int menu;       //��������� ����� ����
	OSHIP *ship;    //��������� �� ������ ������� ������

	//��������� ������� ������
	HANDLE hCon = CreateConsoleScreenBuffer(GENERIC_READ | GENERIC_WRITE, 0, NULL, CONSOLE_TEXTMODE_BUFFER, NULL);
	if (hCon != INVALID_HANDLE_VALUE) {
		CONSOLE_FONT_INFOEX cfi;
		cfi.cbSize = sizeof(CONSOLE_FONT_INFOEX);
		cfi.nFont = 0;
		cfi.dwFontSize.X = 0;
		cfi.dwFontSize.Y = 24;
		cfi.FontFamily = FF_DONTCARE;
		cfi.FontWeight = 400;
		wcscpy(cfi.FaceName, L"Lucida Console");
		SetCurrentConsoleFontEx(hCon, FALSE, &cfi);
	}



	puts("        II         II                   II         II                          ");
	puts("        I II       I II                 I II       I II                        ");
	puts("        I   II     I   II               I   II     I   II                      ");
	puts("        I     II   I     II             I     II   I     II                    ");
	puts("        I   II     I   II               I   II     I   II                      ");
	puts("        I II       I II                 I II       I II                        ");
	puts("   IIIIIIIIIIIIIIIIIIIIIIIIIIIII  IIIIIIIIIIIIIIIIIIIIIIIIIIIII                ");
	puts("    I                         I    I                         I                 ");
	puts("     III                   III      III                   III                  ");
	puts("        IIIII         IIIII             IIIII         IIIII                    ");
	puts("             IIIIIIIII                       IIIIIIIII                         ");
	puts("~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~");

	puts("��� ������������ ��������� ��� ������ � ����������.");
	puts("���������� ������� ���������.");
	puts("���� ������� ��������� �������� ������ �� ����� ���������, � ������:");
	puts("  1. ��� ��������� - ������ � ������������ ������ 50 ��������");
	puts("  2. ��� ��������� - ������ � ������������ ������ 50 ��������");
	puts("  3. ��������� ��������� �� ��� x");
	puts("  4. ��������� ��������� �� ��� y");
	puts("  5. ��������� ��������� �� ��� z");
	puts("  6. �������������");
	puts("  7. �������� ���������");


	system("pause");

	ship = NULL;

	do
	{
		system("cls");
		puts("������� ����");
		puts("1-���� ������ � ���������");
		puts("2-����� ���������");
		puts("3-��������� ���������");
		puts("4-�������������� ���������");
		puts("5-�������� ���������");
		puts("6-�������");
		puts("0-�����");
		printf("��� �����: ");
		menu = input_number();
		system("cls");
		switch (menu)
		{
		case 1:
			ship = input_menu(ship);
			break;
		case 2:
			output_menu(ship,"���������");
			break;
		case 3:
			ship=calculate_menu(ship);
			break;
		case 4:
			ship = edit_menu(ship);
			break;
		case 5:
			ship = remove_menu(ship);
			break;
		case 6:
			help_menu();
			break;
		case 0:
			break;
		default:
			puts("��� ������ ������ ����");
			system("pause");
			break;
		}
	} while (menu);
	if (ship != NULL)
		exit_save(ship);

	ship = O_free_all(ship);
}

















































































//**//PF get_sized,title,"��������� �� ������ ������� ������ � ���������� ��� �����"
//**//PF get_sized,name,"��������� �� ������ ������� ������ � ������ ����, ��� ������"
//**//PF get_nt,name,"��������� �� ������ ������� ������ � ������ ����, ��� ������"
//**//PF get_path,demo_f,"��������� �� ������ ������� ������ � ���� � ���� �����"
//**//PF get_type,title,"��������� �� ������ ������� ������ � ���������� ��� �����"
//**//PF get_coord,title,"��������� �� ������ ������� ������ � ���������� ��� �����"
//**//PF is_allowed,not_allowed,"��������� �� ������ ������� ������� ������ � ������������ ���������"
//**//PF input_string,size,"������������ ������ �������� ������"
//**//PF input_string,not_allowed,"��������� �� ������ ������ ������ � ������������ ���������"
//**//PF str_len,s,"��������� �� ������ ������� �������� ������"
//**//PF get_nt,title,"��������� �� ������ ������� ������ � ���������� ��� �����"
//**//PF get_coord,ch,"������ ���������, �������� 'x'"
//**//PF get_struct_info,info,"��������� �� ������ � ���������"
//**//PF F_gets,end,"������ �������� ����� ������"
//**//PF F_gets,maxlen,"������������ ����� ������"
//**//PF is_sm_letter,ch,"����������� ������"
//**//PF is_bi_letter,ch,"����������� ������"
//**//PF get_sized,min,"����������� �������� ��� ��������� �����"
//**//PF get_sized,max,"����������� �������� ��� ��������� �����"
//**//PF get_sized,_title,"��������� �� ������ ������� ��������� �����"
//**//PF save,is_add,"������ ������ � ������ ����������"
//**//PF select_sort,sort,"��������� �� ��������� � ����������� ����������"
//**//PF select_find,find,"��������� �� ��������� � ����������� ������"
//**//PF a_sma_b,a,"������ �������� a"
//**//PF a_sma_b,b,"������ �������� b"
//**//PF a_sma_b,sort_t,"��������� �� ��������� � ����������� ����������"
//**//PF is_need,info,"������ ��������"
//**//PF is_need,find,"��������� �� ��������� � ����������� ������"
//**//PF output_menu,title,"��������� �� ������ ������� ������ � ��������� ����, ��� �������"
//**//PF O_find,find,"��������� �� ��������� � ����������� ������"
//**//PF O_sort,sort,"��������� �� ��������� � ����������� ����������"
//**//PF O_insert,sort,"��������� �� ��������� � ����������� ����������"
/*END

type:
char void int float bool DATA string OSHIP FILE
*/

