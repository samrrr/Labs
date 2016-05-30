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
} OSHIP;

#define S_input_nt_help "���������:\n  1. ������� ������� ���������\n  2. ������� ������ � ������\n  3. ������� ��������� �������� ������\n  4. ������� ����� ���� �������, ����� ���������� ����, ������� �\n     ������� ������\n���� ����������� �������� ����� ��������������.\n������ � ����� ����� ��������������.\n�������� ������ ������ �������� �� ������ ��� ���������� ����,\n������ �� ������� ������ ���������� � �������� �����.\n��� �������� ����� � ����� ����� ������ ����� ������� ����������.\n�������� ������ ����� ��������� �� 1 �� 50 ��������.\n��� ���������� ������������� ���������� �������� ����\n�������� ����� ��������������.\n��� ��������� ����� ������� Enter\n"
#define S_input_number "��������� ������� ������ ����� � '-'.\n����������� ���� ������ �����.\n"

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
��������: ��� ������� ��� �������� � ����� ����� ���������.
�������: ��� ������� ���������� ��������� �� ��������� �������.
*/
OSHIP *O_get_struct()
{
	OSHIP *n_el;      //��������� �� ��������� �������

	n_el = (OSHIP*)malloc(sizeof(OSHIP));
	get_struct_info(&(n_el->info));
	return n_el;
}

/*
��������: ��� ������� ��� ���������� ������ ����� ������������ �������� ��������� ������.
�������: ��� ������� ���������� ��������� �� ������ ������� ������.
*/
OSHIP* O_add_after(OSHIP *sp, OSHIP *el)
{
	if (sp!=NULL)
		sp->link1 = el;
	return el;
}

/*
��������: ��� ������� ��� ���������� ����� ��������� � ������.
�������: ��� ������� ���������� ��������� �� ������ ������� ������.
*/
OSHIP *O_add(OSHIP *ship_end)
{
	OSHIP *el;    //��������� �� ����������� �������
	puts("������� �������");
	el = O_get_struct();
	ship_end=O_add_after(ship_end, el);

	puts("����� ������� ������� ��������");
	return ship_end;
}

/*
��������: ��� ������� ��� �������� ������ �������� �� ������.
�������: ��� ������� ���������� ��������� �� ������ ������� ������.
*/
OSHIP* O_del_frist(OSHIP *ship, OSHIP *ship_end)
{
	if (ship != NULL && ship != ship_end)
	{
		OSHIP *l;//��������� �� ������ ������ ������� ������
		l = ship;
		ship = ship->link1;
		free(l->info.name);
		free(l->info.type);
		free(l);
		return ship;
	}
	else
		return NULL;
}

/*
��������: ��� ������� ��� ������ �������������� ����� ����� ���������.
�������: ������� �� ���������� ��������.
*/
void O_print_struct(OSHIP *ship)
{
	printf("��� ���������: \"%s\"\n", ship->info.name);
	printf("��� ���������: \"%s\"\n", ship->info.type);
	printf("��������� ��������� �� x � �����������:%i\n", ship->info.x);
	printf("��������� ��������� �� y � �����������:%i\n", ship->info.y);
	printf("��������� ��������� �� z � �����������:%i\n", ship->info.z);
}

/*
��������: ��� ������� ��� �������� ��������� �� ������.
�������: ��� ������� ���������� ��������� �� ������ ������� ������.
*/
OSHIP *O_del(OSHIP *ship, OSHIP *ship_end)
{
	if (ship != NULL)
	{
		puts("�������:");
		O_print_struct(ship);
		puts("���� �� �������");
		ship = O_del_frist(ship,ship_end);
	}
	else
		puts("��� ��������� � �������");
	return ship;
}

/*
��������: ��� ������� ��� ������ ������.
�������: ������� �� ���������� ��������.
*/
void O_print(OSHIP *ship, OSHIP *ship_end)
{
	int i;//��������������� ����������

	puts("����� � ������ �������");
	if (ship != NULL)
	{
		i = 0;
		while (ship != ship_end)
		{
			if (i > 0 && i % 3 == 0)
				system("pause");
			printf("\n�������� �����: %i\n", i + 1);
			O_print_struct(ship);
			ship = ship->link1;
			i++;
		};

		if (i > 0 && i % 3 == 0)
			system("pause");
		printf("\n�������� �����: %i\n", i + 1);
		O_print_struct(ship);

		printf("\n����� �������\n");
	}
	else
		puts("������� �����");

}

/*
��������: ��� ������� ��� ������������ ������ ��-��� ������.
�������: ��� ������� ���������� NULL.
*/
OSHIP* O_free_all(OSHIP* ship, OSHIP *ship_end)
{
	OSHIP *link;//��������������� ���������
	if (ship != NULL)
	{
		link = NULL;
		while (link != ship_end)
		{
			link = ship;
			ship = ship->link1;
			free(link->info.name);
			free(link->info.type);
			free(link);
		}
	}
	return NULL;
}

void main()
{
	setlocale(0, "RU");

	int menu;       //���������� ���������� ������ ����
	OSHIP *ship;    //��������� �� ������ ������� ������
	OSHIP *ship_end;//��������� �� ��������� ������� ������

	ship = NULL;
	ship_end = NULL;

	do
	{
		system("cls");
		puts("������� �� ���� ������������ ������");
		puts("1-���������� �������� � ����� �������");
		puts("2-������ �������� �� ������ �������");
		puts("3-����������� �������");
		puts("4-�������� �������");
		puts("5-�������");
		puts("0-�����");
		menu = input_number();
		system("cls");
		switch (menu)
		{
		case 1:
			if (ship != NULL)
				ship_end = O_add(ship_end);
			else
			{
				ship = ship_end = O_get_struct();

				puts("����� ������� ������� ��������");
			}
			system("pause");
			break;
		case 2:
			if (ship != NULL)
				ship = O_del(ship, ship_end);
			else
				puts("��� ��������� � �������");
			system("pause");
			break;
		case 3:
			O_print(ship, ship_end);
			system("pause");
			break;
		case 4:
			ship=O_free_all(ship, ship_end);
			puts("������� ������� �������");
			system("pause");
			break;
		case 5:
			puts("�������");
			puts("��� ��������� ��� ���������� �������");
			puts("� ���� ��������� ����� ��������� �������� � �������,");
			puts("����� ������� �� �������, �������� �������� �������");
			puts("��� ����� ������:");
			puts("1. ��� �������������� � ������");
			puts("2. ������� ������� ������� ���������");
			puts("3. ������� � ����� ���������");
			puts("�������� ����� ���� �����:");
			puts("1. ���-������ �� 1 �� 50 ��������");
			puts("2. ���-������ �� 1 �� 50 ��������");
			puts("3. ��������� �� x-����� ����� �� -999999 �� 9999999");
			puts("4. ��������� �� y-����� ����� �� -999999 �� 9999999");
			puts("5. ��������� �� z-����� ����� �� -999999 �� 9999999");
			puts("������� ��������� ������� ���������.");

			system("pause");
			break;
		case 0:
			break;
		default:
			puts("��� ������ ������ ����");
			system("pause");
			break;
		}
	} while (menu != 0);
	ship = O_free_all(ship,ship_end);
}












































































//**//PF get_nt,name,"��������� �� ������ ������� ������ � ������ ����, ��� ������"
//**//PF get_type,title,"��������� �� ������ ������� ������ � ���������� ��� �����"
//**//PF get_coord,title,"��������� �� ������ ������� ������ � ���������� ��� �����"
//**//PF is_allowed,not_allowed,"��������� �� ������ ������� ������� ������ � ������������ ���������"
//**//PF input_string,size,"������������ ������ �������� ������"
//**//PF input_string,not_allowed,"��������� �� ������ ������ ������ � ������������ ���������"
//**//PF str_len,s,"��������� �� ������ ������� �������� ������"
//**//PF is_sm_letter,ch,"����������� ������"
//**//PF is_bi_letter,ch,"����������� ������"
//**//PF get_nt,title,"��������� �� ������ ������� ������ � ���������� ��� �����"
//**//PF get_coord,ch,"������ ���������, �������� 'x'"
//**//PF get_struct_info,info,"��������� �� ������ � ���������"

/*PP0
���� ���
PP0*/
/*PP1
������� ������
PP1*/

/*END

type:
char void int float bool DATA string OSHIP FILE
*/