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
}DATA;

typedef struct ST1
{
	DATA info;
	struct ST1 *link1;//������ �� ��������� �������
}OSHIP;

#define S_input_path_help "���������:\n  1. ������� ������� ���������\n  2. ������� ������ � ������\n  3. ������� ��������� �������� ������\n���� ����������� �������� ������������.\n������ � ����� ���� ����� ��������������.\n�� ����� ������ �������� ���������� \".txt\", ��� ����, ����� �����\n���� ������� ���� � ��������.\n\n��� ��������� ����� ������� Enter\n"
#define S_input_nt_help "���������:\n  1. ������� ������� ���������\n  2. ������� ������ � ������\n  3. ������� ��������� �������� ������\n  4. ������� ����� ���� �������, ����� ���������� ����, ������� �\n     ������� ������\n���� ����������� �������� ����� ��������������.\n������ � ����� ����� ��������������.\n�������� ������ ������ �������� �� ������ ��� ���������� ����,\n������ �� ������� ������ ���������� � �������� �����.\n��� �������� ����� � ����� ����� ������ ����� ������� ����������.\n�������� ������ ����� ��������� �� 1 �� 50 ��������.\n��� ���������� ������������� ���������� �������� ����\n�������� ����� ��������������.\n��� ��������� ����� ������� Enter\n"
char *S_input_number = "��������� ������� ������ ����� � '-'.\n���� ������ �������� ������������.\n����������� ���� ������ �����.\n";

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
char *input_string(int size, char *not_allowed)
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
char* get_nt(char *title, char* name)
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
	if (demo_f != NULL)
		printf("������� ������������ ����-����: \"%s\"?\n", demo_f);
	if (input_yn() && demo_f != NULL)
	{
		file_name = (char*)malloc(8 * sizeof(char));
		strcpy(file_name, "txt.txt");
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
		s = get_nt(title, "���");//���� ���� �������
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
int get_coord(char* title, char ch)
{
	puts(title);
	printf(S_input_number);
	printf("������� ��������� �� ��� %c � ����������� (����� ����� �� -999999 �� 9999999):\n", ch);
	return input_number();
}

/*
��������: ������� ��������� ����� ���������.
�������: ������� �� ���������� ��������.
*/
void get_struct_info(DATA *info)
{
	system("cls");
	info->name = get_nt("���� ������ ���������", "���");
	system("cls");
	info->type = get_type("���� ������ ���������");
	system("cls");
	info->x = get_coord("���� ������ ���������", 'x');
	system("cls");
	info->y = get_coord("���� ������ ���������", 'y');
	system("cls");
	info->z = get_coord("���� ������ ���������", 'z');
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
	printf("��������� ��������� �� ��� x � �����������: %i\n", ship->info.x);
	printf("��������� ��������� �� ��� y � �����������: %i\n", ship->info.y);
	printf("��������� ��������� �� ��� z � �����������: %i\n", ship->info.z);
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
		puts("������ ����");

}

/*
��������: ������� ��� ������������ ������ ��-��� ����� ������.
�������: ��� ������� ���������� NULL.
*/
OSHIP* O_free_all(OSHIP* ship)
{
	OSHIP *link;//��������������� ���������
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
��������: ������� ��� ������ �������������� ����� � ����.
�������: ��� ������� ���������� 1 - ���� ������� ��������, ����� 0.
*/
bool save(char *file_name, OSHIP*ship)
{
	FILE *f;   //��������� �� ������ � �����
	OSHIP*link;//��������� �� ����������� �������
	bool err;  //������ ������
	if (ship != NULL)
	{
		f = fopen(file_name, "w");
		if (f != NULL)
		{
			link = ship;
			do
			{
				err = fprintf(f, "%s\n%s\n%i\n%i\n%i\n", link->info.name, link->info.type, link->info.x, link->info.y, link->info.z) < 0;
				if (err)
					return fclose(f) * 0;
				link = link->link1;
			} while (link != NULL);
		}
		else
			return 0;

		fclose(f);
	}
	else
		return 0;
	return 1;
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
��������: ������� ��� ����� ������ �� �����.
�������: ��� ������� ���������� ��������� �� ������ ������� ������������ ������.
*/
OSHIP *load(char *file_name)
{
	OSHIP* ship;//��������� �� ������ ������� ������
	OSHIP* el;  //��������� �� ����� �������
	OSHIP* last;//��������� �� ��������� ������� ������
	FILE *f;    //��������� �� ������ � �����
	bool err;   //������ ������
	bool end;   //������ ����� �����
	char *s;    //��������� �� ������ ������ ��������� �������


	if ((f = fopen(file_name, "r")) == NULL)
		return NULL;

	err = 0;
	end = 0;
	ship = NULL;

	do
	{
		if ((s = F_gets('\n', 50, f)) != NULL)
		{
			if (s[0] != '\0')
			{
				el = (OSHIP*)malloc(sizeof(OSHIP));

				el->link1 = NULL;
				el->info.type = NULL;
				if (ship != NULL)
				{
					O_add_after(last, el);
					last = last->link1;
				}
				else
					ship = last = el;

				el->info.name = s;
				
				if ((s = F_gets('\n', 50, f)) != NULL)
				{
					el->info.type = s;
					err = fscanf(f, "%i %i %i", &(el->info.x), &(el->info.y), &(el->info.z)) != 3;
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
��������: ������� ��� �������� ���� �����.
�������: ��� ������� ���������� ��������� �� ������ ������� ��������� ������.
*/
OSHIP *input_menu(OSHIP *ship)
{
	int menu;       //��������� ����� ����
	char *file_name;//��������� �� ������ ������ ������ ���� � �����


	do
	{
		system("cls");
		puts("���� ������");
		if (ship != NULL)
			puts("�������� ��� ����� ������ ������ ����� ����");
		puts("1-� ����������");
		puts("2-�� �����");
		puts("0-������� � �������");
		printf("��� �����: ");
		menu = input_number();
		switch (menu)
		{
		case 1:
			ship = O_free_all(ship);
			ship = O_get_structs();
			puts("����� ������ ������� ������");
			system("pause");
			break;
		case 2:
			file_name = get_path("txt.txt");
			ship = O_free_all(ship);
			if ((ship = load(file_name)) != NULL)
				puts("������ ������� ��������");
			else
				puts("�� ������� ��������� ������");
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
��������: ������� ��� �������� ���� ������.
�������: ������� �� ���������� ��������.
*/
void output_menu(OSHIP *ship)
{
	if (ship == NULL)
	{
		puts("��� ������ ��� ������");
		system("pause");
		return;
	}
	int menu;       //��������� ����� ����
	char *file_name;//��������� �� ������ ������ ������ ���� � �����


	do
	{
		system("cls");
		puts("����� ������");
		puts("1-�� �����");
		puts("2-� ����");
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
			if (save(file_name, ship))
				puts("������ ������� �������");
			else
				puts("�� ������� ��������� ������");
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
}

/*
��������: ������� ��� �������� ���� ��������.
�������: ��� ������� ���������� ��������� �� ������ ������� ������.
*/
OSHIP* remove_menu(OSHIP* ship)
{
	int menu;       //��������� ����� ����
	char *file_name;//��������� �� ������ ������ ������ ���� � �����
	

	do
	{
		system("cls");
		puts("��������");
		puts("1-������ �� ����������� ������");
		puts("2-�����");
		puts("0-������� � �������");
		printf("��� �����: ");
		menu = input_number();
		switch (menu)
		{
		case 1:
			system("cls");
			if (ship != NULL)
				ship = O_free_all(ship);
			else
				puts("������ ����. ������� ������");
			system("pause");
			break;
		case 2:
			system("cls");
			file_name = get_path("out.txt");
			if (remove(file_name) == 0)
				puts("���� �����");
			else
				puts("�� ������� ������� ����");
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
��������: ������� ��� �������� ���� �������.
�������: ������� �� ���������� ��������.
*/
void help_menu()
{
	int menu;       //��������� ����� ����

	do
	{
		system("cls");
		puts("��� ��������� ��� ��������, �������� � ���������� �������");
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
			puts("��� ����� ������ ������ ������ ������ ���������");
			puts("��� ����� ����� � ����");
			printf(S_input_nt_help);
			puts("");
			puts("��� ����� ���������, ������������� � ��������");
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
			puts("  ���� � ����� ���� �����-�� ����������, �� ��� ���������");
			puts("  ���� ����� �� ����������, �� �������� ������ ���� � � ����");
			puts("  ������������ �������������� ���� ������.");
			system("pause");
			break;
		case 3:
			system("cls");
			puts("���� ������� ������ �������� ������ �� ����� ��������� ���������, � ������:");
			puts("  1. ��� ��������� - ������ � ������������ ������� 50 ��������");
			puts("  2. ��� ��������� - ������ � ������������ ������� 50 ��������");
			puts("  3. ��������� ��������� �� ��� x");
			puts("  4. ��������� ��������� �� ��� y");
			puts("  5. ��������� ��������� �� ��� z");
			puts("������ ��������� �� ��������� ����");
			system("pause");
			break;
		case 4:
			puts("������� ������ ������ ����������");
			puts("������� ��������� ������� ���������");
			puts("��� ��������� ����� ����������� ����� 50 �������� � ������� ������ ��:");
			puts("  -���������� ����");
			puts("  -��������");
			puts("  -������� ������");
			puts("��� ��������� ������ ���������� � �������� �����");

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

int main()
{
	setlocale(0, "RU");
	int menu;       //��������� ����� ����
	OSHIP *ship;    //��������� �� ������ ������� ������

	ship = NULL;

	do
	{
		system("cls");
		puts("������ � �������");
		puts("������� ����");
		puts("1-���� ������");
		puts("2-����� ������");
		puts("3-��������");
		puts("4-�������");
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
			output_menu(ship);
			break;
		case 3:
			ship = remove_menu(ship);
			break;
		case 4:
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
	ship = O_free_all(ship);
}





























































































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
//**//PF F_gets,maxlen,"������������ ������ ������"
//**//PF is_sm_letter,ch,"����������� ������"
//**//PF is_bi_letter,ch,"����������� ������"

/*END

type:
char void int float bool DATA string OSHIP FILE
*/

