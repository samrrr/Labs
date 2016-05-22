#include <conio.h>
#include <malloc.h>
#include <stdio.h>
#include <windows.h>
#include <locale.h>

typedef struct
{
	char s_name;//��� ���������� �� �����(1-�� ����������� 2-�� ��������)
	char s_type;//��� ���������� �� ����(1-�� ����������� 2-�� ��������)
	char s_x;   //��� ���������� �� x(1-�� ����������� 2-�� ��������)
	char s_y;   //��� ���������� �� y(1-�� ����������� 2-�� ��������)
	char s_z;   //��� ���������� �� z(1-�� ����������� 2-�� ��������)
	char typ[5];//������ ������� 5, � ������� ������� �������� �������� ���������� (1-��� 2-��� 3-x 4-y 5-z 0-��� ��������)
} SORTDATA;

typedef struct
{
	char *name;//��������� �� ������ ������ ������, ���������� ��� ���������
	char *type;//��������� �� ������ ������ ������, ���������� ��� ���������
	int x;     //��������� ��������� �� x
	int y;     //��������� ��������� �� y
	int z;     //��������� ��������� �� z

	char s_name;//��� ������ �� �����(0-�� ����� 1-��, ��� ������ 2-��, ��� ������ 3-������ ����������)
	char s_type;//��� ������ �� ����(0-�� ����� 1-��, ��� ������ 2-��, ��� ������ 3-������ ����������)
	char s_x;   //��� ������ �� x(0-�� ����� 1-��, ��� ������ 2-��, ��� ������ 3-������ ����������)
	char s_y;   //��� ������ �� y(0-�� ����� 1-��, ��� ������ 2-��, ��� ������ 3-������ ����������)
	char s_z;   //��� ������ �� z(0-�� ����� 1-��, ��� ������ 2-��, ��� ������ 3-������ ����������)
} FINDDATA;

typedef struct
{
	char *name;//��������� �� ������ ������ ������, ���������� ��� ���������
	char *type;//��������� �� ������ ������ ������, ���������� ��� ���������
	int x;     //��������� ��������� �� x
	int y;     //��������� ��������� �� y
	int z;     //��������� ��������� �� z
}DATA;

//������� ��� ��������� �������. 

char my_getch()
{
	char ch;//��� ������� ������.
	do
	{
		ch = _getch();
		if (ch == '\r')
			ch = '\n';
		else
			if (ch == '\0' || ch == -32)
				_getch();
			else
				if (ch == '\t')
					ch = ' ';
	} while (ch >= -128 && ch <= -17 || ch == '\0' || ch == -32);
	return ch;
}

//������� ��� ����� ������ �����

int input_number()
{
	int number;    //�������� �����	
	char *s;       //��������� �� ������ ������ �������� ������
	int length = 1;//����� ������
	char ch;       //�������� ������
	s = NULL;
	do
	{
		ch = my_getch();
		switch (ch)
		{
		case 27:
			break;
		case '\b':
			if (length > 1)
			{
				printf("\b \b");
				length--;
				s = (char *)realloc(s, sizeof(char)*length);
			}
			break;
		case '\n':
			if (length>1)
				s[length - 1] = 0;
			break;
		default:
			if ((ch >= '0' && ch <= '9' || ch == '-' && length == 1) && length <= 7)
			{
				s = (char *)realloc(s, sizeof(char)*(length+1));
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

//������� ��� ����� ������ y/n

bool input_yn()
{
	char sy;       //�������� ������
	char ch;       //������� �������

	sy = 0;
	do
	{
		ch = my_getch();
		switch (ch)
		{
		case '\b':
			printf("\b \b");
			sy = 0;
			break;
		case 'y':
		case 'Y':
		case 'n':
		case 'N':
			sy = ch;
			printf("\b%c",sy);
			break;
		}
	} while (ch != '\n' || sy == 0);
	printf("\n");
	return sy == 'y' || sy == 'Y';
}

//������� ��� ����� ������

char *input_string(int size)
{
	char *s;       //��������� �� ������ ������ �������� ������
	int length = 1;//����� ������
	char ch;       //�������� ������
	s = NULL;
	do
	{
		ch = my_getch();
		switch (ch)
		{
		case 27:
			break;
		case '\b':
			if (length > 1)
			{
				printf("\b \b");
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
				s[length - 1] = 0;
			}
			break;
		default:
			if (length <= size && (ch != ' ' || length > 1))
			{
				s = (char *)realloc(s, sizeof(char)*(length+1));
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

//������� ��� ���������� ������ ������

int str_len(char*s)
{
	int i = 1;//����� ������
	while (*s)
		i++, s++;
	return i;
}

//������� ��� ����� ���� ���������

char* get_type()
{
	char *types[4] = { "battleship", "cruiser", "boat", "steelship" };
              //������ ���������� �� ������ ������ ������
	int i;    //��������������� ����������
	char *s;  //��������� �� ������ ������ �������� ������
	char type;//��� ��������
	char len; //����� ������
	puts("�������� ���:");
	for (i = 0; i < 4; i++)
		printf("%i-%s\n", i + 1, types[i]);
	puts("������ �����-���� ���� �������\n");
	type = input_number();
	if (type <= 0 || type >= 5)
	{
		puts("������� ��� (�� 1 �� 20 ��������):");
		s = input_string(20);
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

//������� ��� ����� �����

char* get_name()
{
	char *s;  //��������� �� ������ ������ �������� ������
	bool exit;//������ ������
	exit = 0;
	do{
		puts("������� ��� (��� ������ ��������� ���� �� ���� ������");
		puts("� �� ����� 30 ��������):");
		s = input_string(30);
		if (*s < 'A' || *s > 'Z')
		{
			puts("�������! ��� ������� ���������� �� � ������� �����.");
			puts("�� ������ ������ ������ ���? (y/n)");
			if (input_yn())
				free(s);
			else
				exit = 1;
		}
		else
			exit = 1;
	} while (!exit);
	return s;
}

//������� ��� ����� ���������

int get_coord(char ch)
{
	printf("������� ��������� �� %c � ����������� (����� ����� �� -999999 �� 9999999):\n", ch);
	return input_number();
}

//������� ��������� ����� ���������

void get_struct_info(DATA *info)
{
	info->name = get_name();
	info->type = get_type();
	info->x = get_coord('x');
	info->y = get_coord('y');
	info->z = get_coord('z');
}

//@@

typedef struct ST1
{
	DATA info;        //������ � ���������
	struct ST1 *link1;//��������� �� ��������� �������
} OSHIP;

//������� ��� ����� ������

OSHIP *O_get_structs()
{
	OSHIP* n_sp;      //��������� �� ������ ������� ������
	OSHIP *n_el;      //��������� �� ������� ������
	OSHIP *last_el;   //��������� �� ��������� ������� ������
	bool is_end_input;//��������������� ����������

	n_sp = (OSHIP*)malloc(sizeof(OSHIP));
	get_struct_info(&(n_sp->info));

	printf("���������� ����?('y'-�� 'n'-���):\n");

	if (input_yn())
	{
		is_end_input = false;
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

//������� ��� ���������� ������ � ������ ��������� ������

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

//������� ��� ���������� ������ � ����� ��������� ������

OSHIP* O_add_last(OSHIP *sp, OSHIP *add_sp)
{
	if (sp != NULL)
	{
		OSHIP *li;//��������������� ���������
		for (li = sp; li->link1 != NULL; li = li->link1);
		li->link1 = add_sp;
	}
	else
		sp = add_sp;
	return sp;
}

//������� ��� ���������� ������ ����� ������������ �������� ��������� ������

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

//������� ��� ���������� ����� ��������� � ������

OSHIP *O_add(OSHIP *ship)
{
	int menu;     //��������� ����� ����
	int n;        //����� ��������
	int len;      //���������� ��������� � ������
	OSHIP *new_sp;//��������� �� ������ ������� ������
	OSHIP *link;  //��������������� ���������
	puts("������� ������������������ ���������");
	if (ship != NULL)
	{
		new_sp = O_get_structs();
		do
		{
			system("cls");
			puts("�������");
			puts("1-�������� � ������");
			puts("2-�������� � �����");
			puts("3-�������� ����� n-���� ��������");
			menu = input_number();
			if (menu<1 || menu>4)
			{
				puts("��� ������ ������");
				system("pause");
			}
		} while (menu<1 || menu>4);
		switch (menu)
		{
		case 1:
			ship = O_add_frist(ship, new_sp);
			break;
		case 2:
			ship = O_add_last(ship, new_sp);
			break;
		case 3:
			for (len = 1, link = ship; link->link1 != NULL; link = link->link1, len++);			
			do
			{
				printf("������� ����� �������� ����� �������� ����� �����������\n�������� (�� 1 �� %i)", len);
				n = input_number();
				if (n < 1 || n > len)
					puts("������");
			} while (n < 1 || n > len);

			for (link = ship; n > 1; link = link->link1, n--);
			
			O_add_after(link, new_sp);
			break;
		}
	}
	else
		ship = O_get_structs();

	puts("����� �������� ������� ���������");
	return ship;
}

//������� ��� �������� ������ �������� �� ������ 

void O_del_one(OSHIP **link)
{
	if (*link != NULL)
	{
		OSHIP *l;//
		l = *link;
		*link = (*link)->link1;
		free(l->info.name);
		free(l->info.type);
		free(l);
	}
}

//������� ��� �������� ��������� �� ������

OSHIP *O_del(OSHIP *ship)
{
	int len;       //����� ������� ���������� ��������
	int m;         //����� ���������� ���������� ��������
	int n;         //����� ������� ���������� ��������
	int i;         //��������������� ����������
	OSHIP *link;   //��������������� ���������
	OSHIP **link_l;//��������������� ���������
	if (ship != NULL)
	{
		for (link = ship, len = 1; link->link1 != NULL; link = link->link1, len++);
		puts("�������� ��������� � n �� m");
		do
		{
			printf("������� n(�� 1 �� %i)\n", len);
			n = input_number();
			if (n<1 || n>len)
				puts("������������ ����");
		} while (n<1 || n>len);

		do
		{
			printf("������� m(�� %i �� %i)\n", n,len);
			m = input_number();
			if (m<n || m>len)
				puts("������������ ����");
		} while (m<n || m>len);
		
		for (i = 2, link = ship; i < n; i++, link = link->link1);

		if (n==1)
			link_l = &ship;
		else
			link_l = &link->link1;
		
		i = m - n + 1;

		do
		{
			O_del_one(link_l);
			i--;
		} while (i > 0);
		puts("�������(-�) ������� �������");
	}
	else
		puts("������ ����, ������� ������");

	return ship;
}

//������� ��� �������� ����� �������� ������

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

//������� ��� ������

OSHIP* O_find(OSHIP* ship)
{
	FINDDATA find;  //��������� �� ����� ��������
	OSHIP *ship_res;//��������� �� ������ ������� ������������� ������
	OSHIP *link;    //��������������� ���������
	OSHIP *new_el;  //��������� �� ����� ��������
	select_find(&find);
	ship_res = NULL;

	do
	{
		if (is_need(ship->info,&find))
			{
				new_el = O_create_copy(ship);
				if (ship_res == NULL)
					ship_res = new_el;
				else
					link->link1 = new_el;
				link = new_el;
			}
		ship = ship->link1;
	} while (ship!=NULL);
	if (ship_res != NULL)
		link->link1 = NULL;
	if (ship_res != NULL)
		puts("����� ��������");
	else
		puts("�� ������� ���������, ��������������� �������� ���������");

	return ship_res;
}

//������� ��� ���������� �������� � ��������������� ������.

OSHIP *O_insert(OSHIP *ship, OSHIP *el, SORTDATA*sort)
{
	if (ship!=NULL)
		if (!a_sma_b(ship->info, el->info, sort))
		{
			OSHIP* l;//��������������� ���������
			l = ship;
			while (ship->link1 != NULL)
			{
				if (a_sma_b(ship->link1->info, el->info, sort))
				{
					O_add_after(ship,el);
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

//������� ��� ����������

OSHIP *O_sort(OSHIP *ship)
{
	if (ship == NULL)
	{
		puts("������ �����������");
		return NULL;
	}
	OSHIP *ship_sorted;//��������� �� ������ ������� ���������������� ������
	OSHIP *link;       //��������������� ���������
	SORTDATA sort;     //������ � ����������

	select_sort(&sort);
	ship_sorted = NULL;

	do
	{
		link = ship;
		ship = ship->link1;
		link->link1 = NULL;
		ship_sorted = O_insert(ship_sorted,link,&sort);
	} while (ship != NULL);
	puts("���������� ��������");
	return ship_sorted;
}

//������� ��� ������ �������������� ����� ����� ���������

void O_print_struct(OSHIP *ship)
{
	printf("��� ���������: \"%s\"\n", ship->info.name);
	printf("��� ���������: \"%s\"\n", ship->info.type);
	printf("��������� ��������� �� x � �����������:%i\n", ship->info.x);
	printf("��������� ��������� �� y � �����������:%i\n", ship->info.y);
	printf("��������� ��������� �� z � �����������:%i\n", ship->info.z);
}

//������� ��� ������ ������

void O_print(OSHIP *ship)
{
	int i;//��������������� ����������
	puts("����� � ������� ��������");
	if (ship != NULL)
	{
		i = 0;
		do
		{
			if (i > 0 && i % 3 == 0)
				system("pause");
			printf("\n�������� �����: %i\n", i + 1);
			O_print_struct(ship); 
			ship = ship->link1;
			i++;
		}	
		while (ship != NULL);
		printf("\n����� �������\n");
	}
	else
		puts("������ ����");

}

//������� ��� ������������ ������ �� ��� ������

OSHIP* O_free_all(OSHIP* ship)
{
	OSHIP *link;//
	while(ship != NULL)
	{
		link = ship;
		ship = ship->link1;
		free(link->info.name);
		free(link->info.type);
		free(link);
	}
	return NULL;
}

//������� ��� �������� ����

void O_menu()
{
	int menu;       //��������� ����� ����
	int i;          //��������������� ����������
	OSHIP *ship;    //��������� �� ������ ������� ������ �������� ������
	OSHIP *ship_res;//��������� �� ������ ������� ������ ����������� ������
	bool is_find;   //������ ������

	ship = NULL;
	ship_res = NULL;
	is_find = false;

	do
	{
		system("cls");
		puts("����������� ������");
		puts("1-���������� ��������� � ������");
		puts("2-�������� ��������� �� ������");
		puts("3-����� ��������� ������");
		puts("4-��������� ������");
		puts("5-����� ����������� ���������� ������");
		puts("6-�������");
		puts("0-������� � �������");
		menu = input_number();
		system("cls");
		switch (menu)
		{
		case 1:
			ship = O_add(ship);
			system("pause");
			break;
		case 2:
			ship = O_del(ship);
			system("pause");
			break;
		case 3:
			O_print(ship);
			system("pause");
			break;
		case 4:
			if (ship != NULL)
			{
				do
				{
					system("cls");
					puts("�������� ��� ���������");
					puts("1-����� (��� ���� ����������� ����� ������)");
					puts("2-���������� ��������� ��������� ������");
					puts("0-������� � �������");
					i = input_number();
					if (i<0 || i>2)
					{
						puts("�� ����������� ����� ����� ����");
						system("pause");
					}
				} while (i<0 || i>2);
				switch (i)
				{
				case 1:
						is_find = TRUE;
						ship_res = O_free_all(ship_res);
						ship_res = O_find(ship);
						system("pause");
						break;
				case 2:
						ship = O_sort(ship);
						system("pause");
						break;
				}
			}
			else
			{
				puts("������ ����, ������������ ������");
				system("pause");
			}
			break;
		case 5:
			if (is_find)
				if (ship_res != NULL)
					O_print(ship_res);
				else
					puts("��� ��������� ������ �� ������� ���������,\n��������������� �������� ���������");
			else
				puts("�� ��� �� ���� �� ��������� �����");
			system("pause");
			break;
		case 6:
			puts("�������");
			puts("��� ����� ������:");
			puts("1. ��� �������������� � ������");
			puts("2. ������� ������� ������� ���������");
			puts("3. ������� � ����� ���������");
			puts("�������� ����� ���� �����:");
			puts("1. ���-������ �� 1 �� 30 ��������");
			puts("2. ���-������ �� 1 �� 20 ��������");
			puts("3. ��������� �� x-����� ����� �� -999999 �� 9999999");
			puts("4. ��������� �� y-����� ����� �� -999999 �� 9999999");
			puts("5. ��������� �� z-����� ����� �� -999999 �� 9999999");
			puts("��������� ��������� - ����� ������ ������ ��������� �� ��������� ���������");
			puts("�������, ������� ������������� �������� ���������.");
			puts("������� ����� ������� ���������.");
			puts("��� ���� ������� ������� �������� ����� � ������");
			puts("� � �����");

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
	ship=O_free_all(ship);
	ship_res=O_free_all(ship_res);
}

//@@

typedef struct ST2
{
	DATA info;        //������ � ���������
	struct ST2 *link1;//��������� �� ��������� �������
	struct ST2 *link2;//��������� �� ����������� �������
} DSHIP;

DSHIP *D_get_structs()
{
	DSHIP* n_sp;      //��������� �� ������ ������� ������
	DSHIP *last_el;   //��������� �� ��������� ������� ������
	bool is_end_input;//��������������� ����������

	n_sp = (DSHIP*)malloc(sizeof(DSHIP));
	get_struct_info(&(n_sp->info));
	n_sp->link2 = NULL;

	printf("���������� ����?('y'-�� 'n'-���):\n");

	if (input_yn())
	{
		is_end_input = false;
		last_el = n_sp;
		do
		{
			last_el->link1 = (DSHIP*)malloc(sizeof(DSHIP));
			get_struct_info(&(last_el->link1->info));
			last_el->link1->link2 = last_el;
			last_el = last_el->link1;
			printf("���������� ����?('y'-�� 'n'-���):\n");
			is_end_input = !input_yn();
		} while (!is_end_input);
		last_el->link1 = NULL;
	}
	else
		n_sp->link1 = NULL;
	return n_sp;
}

//������� ��� ���������� ������ � ������ ��������� ������

DSHIP *D_add_frist(DSHIP *ship, DSHIP *sp)
{
	if (ship != NULL)
	{
		DSHIP* next;//��������������� ���������
		for (next = sp; next->link1 != NULL; next = next->link1);
		next->link1 = ship;
		ship->link2 = next;
	}
	return sp;
}

//������� ��� ���������� ������ � ������ ��������� ������.

DSHIP *D_add_last(DSHIP *ship, DSHIP *sp)
{
	if (ship != NULL)
	{
		DSHIP* next;
		for (next = ship; next->link1 != NULL; next = next->link1);
		next->link1 = sp;
		sp->link2 = next;
	}
	else
		ship = sp;
	return ship;
}

//������� ��� ���������� ������ � ������ ��������� ������.

DSHIP *D_add_after(DSHIP *ship, DSHIP *sp)
{
	if (ship != NULL)
	{
		DSHIP* next;
		for (next = sp; next->link1 != NULL; next = next->link1);
		next->link1 = ship->link1;
		if (next->link1 != NULL)
			next->link1->link2 = next;
		ship->link1 = sp;
		sp->link2 = ship;
	}
	else
		ship = sp;
	return ship;
}

//������� ��� ���������� ������ � ������ ��������� ������

DSHIP *D_add(DSHIP *ship)
{
	int menu;     //��������� ����� ����
	int n;        //��������������� ����������
	int len;      //���������� ��������� � ������
	DSHIP *new_sp;//��������� �� ������ ������� ������
	DSHIP *link;  //��������� �� ������ ������� ������
	puts("������� ������������������ ���������");
	if (ship != NULL)
	{
		new_sp = D_get_structs();
		do
		{
			system("cls");
			puts("�������");
			puts("1-�������� � ������");
			puts("2-�������� � �����");
			puts("3-�������� ����� n-���� ��������");
			menu = input_number();
			if (menu<1 || menu>4)
			{
				puts("��� ������ ������");
				system("pause");
			}
		} while (menu<1 || menu>4);
		switch (menu)
		{
		case 1:
			ship = D_add_frist(ship, new_sp);
			break;
		case 2:
			ship = D_add_last(ship, new_sp);
			break;
		case 3:
			for (len = 1, link = ship; link->link1 != NULL; link = link->link1, len++);
			do
			{
				printf("������� ����� �������� ����� �������� ����� �����������\n�������� (�� 1 �� %i)", len);
				n = input_number();
				if (n < 1 || n > len)
					puts("������");
			} while (n < 1 || n > len);

			for (link = ship; n > 1; link = link->link1, n--);

			D_add_after(link, new_sp);
			break;
		}
	}
	else
		ship = D_get_structs();

	puts("����� �������� ������� ���������");
	return ship;
}

//������� ��� �������� ������ �������� �� ������ 

void D_del_one(DSHIP **link)
{
	if (*link != NULL)
	{
		DSHIP *l;//��������������� ���������
		l = *link;
		if ((*link)->link1 != NULL)
			(*link)->link1->link2 = (*link)->link2;
		*link = (*link)->link1;
		free(l->info.name);
		free(l->info.type);
		free(l);
	}
}

//������� ��� �������� ��������� �� ������

DSHIP *D_del(DSHIP *ship)
{
	int len;       //���������� ��������� � ������
	int m;         //����� ���������� ���������� ��������
	int n;         //����� ������� ���������� ��������
	int i;         //��������������� ����������
	DSHIP *link;   //��������������� ���������
	DSHIP **link_l;//��������������� ���������
	if (ship != NULL)
	{
		for (link = ship, len = 1; link->link1 != NULL; link = link->link1, len++);
		puts("�������� ��������� � n �� m");
		do
		{
			printf("������� n(�� 1 �� %i)\n", len);
			n = input_number();
			if (n<1 || n>len)
				puts("������������ ����");
		} while (n<1 || n>len);

		do
		{
			printf("������� m(�� %i �� %i)\n", n, len);
			m = input_number();
			if (m<n || m>len)
				puts("������������ ����");
		} while (m<n || m>len);

		for (i = 2, link = ship; i < n; i++, link = link->link1);

		if (n == 1)
			link_l = &ship;
		else
			link_l = &link->link1;

		i = m - n + 1;

		do
		{
			D_del_one(link_l);
			i--;
		} while (i > 0);
		puts("�������(-�) ������� �������");
	}
	else
		puts("������ ����, ������� ������");

	return ship;
}

//������� ��� �������� ����� �������� ������

DSHIP *D_create_copy(DSHIP* ship)
{
	int i;          //��������������� ����������
	int len;        //���������� ��������� � ������
	DSHIP *new_ship;//��������� �� ����� ��������
	if (ship != NULL)
	{
		new_ship = (DSHIP*)malloc(sizeof(DSHIP));
		new_ship->info.x = ship->info.x;
		new_ship->info.y = ship->info.y;
		new_ship->info.z = ship->info.z;

		len = str_len(ship->info.name);
		new_ship->info.name = (char*)malloc(len*sizeof(char));
		for (i = 0; i < len; i++)
			new_ship->info.name[i] = ship->info.name[i];

		len = str_len(ship->info.type);
		new_ship->info.type = (char*)malloc(len*sizeof(char));
		for (i = 0; i < len; i++)
			new_ship->info.type[i] = ship->info.type[i];
		new_ship->link1 = NULL;
		new_ship->link2 = NULL;
	}
	else
		new_ship = NULL;
	return new_ship;
}

//������� ��� ������

DSHIP* D_find(DSHIP* ship)
{
	FINDDATA find;  //������ � ������
	DSHIP *ship_res;//��������� �� ������ ������� ������������� ������
	DSHIP *link;    //��������������� ���������
	DSHIP *new_el;  //��������� �� ����� ��������

	select_find(&find);
	ship_res = NULL;
	link = NULL;

	do
	{
		if (is_need(ship->info, &find))
		{
			new_el = D_create_copy(ship);
			if (ship_res == NULL)
				ship_res = new_el;
			else
				link->link1 = new_el;
			new_el->link2 = link;
			link = new_el;
		}
		ship = ship->link1;
	} while (ship != NULL);
	if (ship_res != NULL)
		link->link1 = NULL;
	if (ship_res != NULL)
		puts("����� ��������");
	else
		puts("�� ������� ���������, ��������������� �������� ���������");

	return ship_res;
}

//������� ��� ������� �������� � ��������������� ������

DSHIP *D_insert(DSHIP *ship, DSHIP *el, SORTDATA*sort)
{
	if (ship != NULL)
	if (!a_sma_b(ship->info, el->info, sort))
	{
		DSHIP *l;
		l = ship;//��������������� ���������
		while (ship->link1 != NULL)
		{
			if (a_sma_b(ship->link1->info, el->info, sort))
			{
				D_add_after(ship, el);
				return l;
			}
			ship = ship->link1;
		}
		ship->link1 = el;
		ship->link1->link2 = ship;
		return l;
	}
	else
	{
		el->link1 = ship;
		el->link1->link2 = el;
		return el;
	}
	else
	{
		el->link1 = NULL;
		el->link2 = NULL;
		return el;
	}
}

//������� ��� ����������

DSHIP *D_sort(DSHIP *ship)
{
	if (ship == NULL)
	{
		puts("������ �����������");
		return NULL;
	}
	DSHIP *ship_sorted;//
	DSHIP *link;       //
	SORTDATA sort;     //

	select_sort(&sort);
	ship_sorted = NULL;

	do
	{
		link = ship;
		ship = ship->link1;
		link->link1 = NULL;
		link->link2 = NULL;
		ship_sorted = D_insert(ship_sorted, link, &sort);
	} while (ship != NULL);
	puts("���������� ��������");
	return ship_sorted;
}

//������� ��� ������ �������������� ����� ����� ���������

void D_print_struct(DSHIP *ship)
{
	printf("��� ���������: \"%s\"\n", ship->info.name);
	printf("��� ���������: \"%s\"\n", ship->info.type);
	printf("��������� ��������� �� x � �����������:%i\n", ship->info.x);
	printf("��������� ��������� �� y � �����������:%i\n", ship->info.y);
	printf("��������� ��������� �� z � �����������:%i\n", ship->info.z);
}

//������� ��� ������ ������

void D_print(DSHIP *ship)
{
	int i;   //��������������� ����������
	int r;   //��������������� ����������
	int type;//��� ������


	if (ship != NULL)
	{
		do
		{
			puts("1-����� � ������� ��������");
			puts("2-����� � ���������� ��������");
			type = input_number();
			if (type < 1 || type > 2)
				puts("��� ������ ������");
		} while (type < 1 || type > 2);

		if (type == 1)
		{
			i = 0;
			do
			{
				if (i > 0 && i % 3 == 0)
					system("pause");
				i++;
				printf("\n�������� �����: %i\n", i);
				D_print_struct(ship);
				ship = ship->link1;
			} while (ship != NULL);
		}
		else
		{
			i = 1;
			for (; ship->link1!=NULL; ship = ship->link1,i++);
			r = i % 3;
			do
			{
				if (ship->link1!=NULL && i % 3 == r)
					system("pause");
				printf("\n�������� �����: %i\n", i);
				D_print_struct(ship);
				ship = ship->link2;
				i--;
			} while (ship != NULL);
		}
		printf("\n����� �������\n");
	}
	else
		puts("������ ����");
}

//������� ��� ������������ ������ �� ��� ������

DSHIP* D_free_all(DSHIP* ship)
{
	DSHIP *link;//��������������� ���������
	while (ship != NULL)
	{
		link = ship;
		ship = ship->link1;
		free(link->info.name);
		free(link->info.type);
		free(link);
	}
	return NULL;
}

//������� ��� �������� ����

void D_menu()
{
	DSHIP *ship;    //��������� �� ������ ������� ������ �������� ������
	DSHIP *ship_res;//��������� �� ������ ������� ������ ����������� ������
	int menu;       //��������� ����� ����
	int i;          //��������������� ����������
	bool is_find;   //������ ������

	is_find = false;
	ship = NULL;
	ship_res = NULL;

	do
	{
		system("cls");
		puts("����������� ������");
		puts("1-���������� ��������� � ������");
		puts("2-�������� ��������� �� ������");
		puts("3-����� ��������� ������");
		puts("4-��������� ������");
		puts("5-����� ����������� ���������� ������");
		puts("6-�������");
		puts("0-������� � �������");
		menu = input_number();
		system("cls");
		switch (menu)
		{
		case 1:
			ship=D_add(ship);
			system("pause");
			break;
		case 2:
			ship = D_del(ship);
			system("pause");
			break;
		case 3:
			D_print(ship);
			system("pause");
			break;
		case 4:
			if (ship != NULL)
			{
				do
				{
					system("cls");
					puts("�������� ��� ���������");
					puts("1-����� (��� ���� ����������� ����� ������)");
					puts("2-���������� ��������� ��������� ������");
					puts("0-������� � �������");
					i = input_number();
					if (i<0 || i>2)
					{
						puts("�� ����������� ����� ����� ����");
						system("pause");
					}
				} while (i<0 || i>2);
				switch (i)
				{
				case 1:
					is_find = TRUE;
					ship_res = D_free_all(ship_res);
					ship_res = D_find(ship);
					system("pause");
					break;
				case 2:
					ship = D_sort(ship);
					system("pause");
					break;
				}
			}
			else
			{
				puts("������ ����, ������������ ������");
				system("pause");
			}
			break;
		case 5:
			if (is_find)
				if (ship_res != NULL)
					D_print(ship_res);
				else
					puts("��� ��������� ������ �� ������� ���������,\n��������������� �������� ���������");
			else
				puts("�� ��� �� ���� �� ��������� �����");
			system("pause");
			break;
		case 6:
			puts("�������");
			puts("��� ����� ������:");
			puts("1. ��� �������������� � ������");
			puts("2. ������� ������� ������� ���������");
			puts("3. ������� � ����� ���������");
			puts("�������� ����� ���� �����:");
			puts("1. ���-������ �� 1 �� 30 ��������");
			puts("2. ���-������ �� 1 �� 20 ��������");
			puts("3. ��������� �� x-����� ����� �� -999999 �� 9999999");
			puts("4. ��������� �� y-����� ����� �� -999999 �� 9999999");
			puts("5. ��������� �� z-����� ����� �� -999999 �� 9999999");
			puts("��������� ��������� - ����� ������ ������ ��������� �� ��������� ���������");
			puts("�������, ������� ������������� �������� ���������.");
			puts("������� ����� ������� ���������.");
			puts("��� ����������� ������� �������� ����� � ������");
			puts("� � �����");

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
	ship = D_free_all(ship);
	ship_res = D_free_all(ship_res);
}

//@@

typedef struct ST3
{
	DATA info;        //������ � ���������
	struct ST3 *link1;//��������� �� ��������� �������
	struct ST3 *link2;//��������� �� ����������� �������
} CSHIP;

//������� ��� ���������� ������ � ������ ��������� ������

CSHIP *C_add_frist(CSHIP *ship, CSHIP *sp)
{
	if (ship != NULL)
	{
		CSHIP* l;//��������������� ���������
		ship->link2->link1 = sp;
		sp->link2->link1 = ship;
		l = sp->link2;
		sp->link2 = ship->link2;
		ship->link2 = l;
	}
	return sp;
}

//������� ��� ���������� ������ � ������ ��������� ������

CSHIP *C_add_last(CSHIP *ship, CSHIP *sp)
{
	if (ship != NULL)
	{
		CSHIP* l;//��������������� ���������
		ship->link2->link1 = sp;
		sp->link2->link1 = ship;
		l = sp->link2;
		sp->link2 = ship->link2;
		ship->link2 = l;
	}
	else
		ship = sp;
	return ship;
}

//������� ��� ���������� ������ � ������ ��������� ������

CSHIP *C_add_after(CSHIP *ship, CSHIP *sp)
{
	if (ship != NULL)
		ship = C_add_frist(ship->link1,sp)->link2;
	else
		ship = sp;
	return ship;
}

//������� ���������� ��������� �� ������ ������� ������

CSHIP *C_get_structs()
{
	CSHIP *n_sp;      //��������� �� ������ ������� ������
	CSHIP *last_el;   //��������� �� ��������� ������� ������
	CSHIP *new_el;    //��������� �� �������� ���������
	bool is_end_input;//��������� �� �������� ���������

	n_sp = (CSHIP*)malloc(sizeof(CSHIP));
	get_struct_info(&(n_sp->info));
	
	n_sp->link1 = n_sp;
	n_sp->link2 = n_sp;

	printf("���������� ����?('y'-�� 'n'-���):\n");

	if (input_yn())
	{
		is_end_input = false;
		last_el = n_sp;
		do
		{
			new_el = (CSHIP*)malloc(sizeof(CSHIP));
			get_struct_info(&(new_el->info));
			new_el->link1 = new_el;
			new_el->link2 = new_el;
			C_add_after(last_el,new_el);
			last_el = new_el;
			printf("���������� ����?('y'-�� 'n'-���):\n");
			is_end_input = !input_yn();
		} while (!is_end_input);
	}
	return n_sp;
}

//������� ��� ���������� ������ ������

int C_get_len(CSHIP*ship)
{
	int i;      //��������������� ����������
	CSHIP *link;//��������������� ����������
	i = 0;
	if (ship != NULL)
		for (i = 1, link = ship->link1; link != ship; link = link->link1, i++);
	return i;
}

//������� ��� ���������� ��������� � ������

CSHIP *C_add(CSHIP *ship)
{
	int menu;     //��������� ����� ����
	int n;        //��������������� ����������
	int len;      //���������� ��������� � ������
	CSHIP *new_sp;//��������� �� ������ ������� ������
	CSHIP *link;  //��������������� ���������
	puts("������� ������������������ ���������");
	if (ship != NULL)
	{
		new_sp = C_get_structs();
		do
		{
			system("cls");
			puts("�������");
			puts("1-�������� � ������");
			puts("2-�������� � �����");
			puts("3-�������� ����� n-���� ��������");
			menu = input_number();
			if (menu<1 || menu>4)
			{
				puts("��� ������ ������");
				system("pause");
			}
		} while (menu<1 || menu>4);
		switch (menu)
		{
		case 1:
			ship = C_add_frist(ship, new_sp);
			break;
		case 2:
			ship = C_add_last(ship, new_sp);
			break;
		case 3:
			len = C_get_len(ship);
			do
			{
				printf("������� ����� �������� ����� �������� ����� �����������\n�������� (�� 1 �� %i)", len);
				n = input_number();
				if (n < 1 || n > len)
					puts("������");
			} while (n < 1 || n > len);

			for (link = ship; n > 1; link = link->link1, n--);

			C_add_after(link, new_sp);
			break;
		}
	}
	else
		ship = C_get_structs();

	puts("����� �������� ������� ���������");
	return ship;
}

//������� ��� �������� ������ �������� �� ������ 

CSHIP* C_del_one(CSHIP *link)
{
	if (link != NULL)
	if (link->link1 != link)
	{
		link->link1->link2 = link->link2;
		link = link->link1;
		free(link->link2->link1->info.name);
		free(link->link2->link1->info.type);
		free(link->link2->link1);
		link->link2->link1 = link;
	}
	else
	{
		free(link->info.name);
		free(link->info.type);
		free(link);
		link = NULL;
	}
	return link;
}

//������� ��� �������� ��������� �� ������

CSHIP *C_del(CSHIP *ship)
{
	int len;       //���������� ��������� � ������
	int m;         //����� ���������� ���������� ��������
	int n;         //����� ������� ���������� ��������
	int i;         //��������������� ����������
	CSHIP *link;   //��������������� ���������
	if (ship != NULL)
	{
		len = C_get_len(ship);
		puts("�������� ��������� � n �� m");
		do
		{
			printf("������� n(�� 1 �� %i)\n", len);
			n = input_number();
			if (n<1 || n>len)
				puts("������������ ����");
		} while (n<1 || n>len);

		do
		{
			printf("������� m(�� %i �� %i)\n", n, len);
			m = input_number();
			if (m<n || m>len)
				puts("������������ ����");
		} while (m<n || m>len);

		for (i = 1, link = ship; i < n; i++, link = link->link1);


		i = m - n + 1;

		do
		{
			link=C_del_one(link);
			i--;
		} while (i > 0);
		if (n == 1)
			ship = link;
		puts("�������(-�) ������� �������");
	}
	else
		puts("������ ����, ������� ������");

	return ship;
}

//������� ��� ������ �������������� ����� ����� ���������

void C_print_struct(CSHIP *ship)
{
	printf("��� ���������: \"%s\"\n", ship->info.name);
	printf("��� ���������: \"%s\"\n", ship->info.type);
	printf("��������� ��������� �� x � �����������:%i\n", ship->info.x);
	printf("��������� ��������� �� y � �����������:%i\n", ship->info.y);
	printf("��������� ��������� �� z � �����������:%i\n", ship->info.z);
}

//������� ��� ������ ������

void C_print(CSHIP *ship)
{
	int i, r,a; //��������������� ����������
	int type;   //��� ������(1-� ���� ������� 2-� ������)
	CSHIP *link;//��������������� ���������
	int len;    //���������� ��������� � ������
	int n;      //����� ��������, � �������� ���������� �����
	int linkadd;//���������� �����, ������� ���� ��������� � ��������� �� ������� ������, ����� �������� ����� ���������� ���������� ��������

	if (ship != NULL)
	{
		do
		{
			puts("1-����� �� ������� � n-��� ��������");
			puts("2-����� ������ ������� � n-��� ��������");
			type = input_number();
			if (type < 1 || type > 2)
				puts("��� ������ ������");
		} while (type < 1 || type > 2);

		len = C_get_len(ship);

		do
		{
			printf("������� n (�� 1 �� %i)\n",len);
			n = input_number();
			if (n < 1 || n > len)
				puts("��� ������ ������");
		} while (n < 1 || n > len);

		for (i = 1; i != n; i++, ship = ship->link1);

		printf("\n�������� �����: %i\n", i);
		C_print_struct(ship);

		if (type == 1)
		{
			r = (n + 2) % 3;
			linkadd = (char*)&(ship->link1) - (char*)ship;
			a = 1;
		}
		else
		{
			i = i + len - 2;
			r = (i + 1) % 3;
			linkadd = (char*)&(ship->link2) - (char*)ship;
			a = -1;
		}
		if (ship->link1 != ship)
		{
			link = *((CSHIP**)((char*)ship + linkadd));
			do
			{
				if (i % 3 == r)
					system("pause");
				printf("\n�������� �����: %i\n", i % len + 1);
				i += a;
				C_print_struct(link);
				link = *((CSHIP**)((char*)link + linkadd));
			} while (link != ship);
		}

		printf("\n����� �������\n");
	}
	else
		puts("������ ����");
}

//������� ��� ������������ ������ �� ��� ������

CSHIP* C_free_all(CSHIP* ship)
{
	CSHIP *link;//��������������� ���������
	if (ship != NULL)
	{
		ship->link2->link1 = NULL;
		do
		{
			link = ship;
			ship = ship->link1;
			free(link->info.name);
			free(link->info.type);
			free(link);
		} while (ship != NULL);
	}
	return NULL;
}


//������� ��� �������� ����� �������� ������

CSHIP *C_create_copy(CSHIP* ship)
{
	CSHIP *new_ship;//��������� �� ������������ �������
	int i;          //��������� �� ������������ �������
	int len;        //���������� ��������� � ������
	if (ship != NULL)
	{
		new_ship = (CSHIP*)malloc(sizeof(CSHIP));
		new_ship->info.x = ship->info.x;
		new_ship->info.y = ship->info.y;
		new_ship->info.z = ship->info.z;

		len = str_len(ship->info.name);
		new_ship->info.name = (char*)malloc(len*sizeof(char));
		for (i = 0; i < len; i++)
			new_ship->info.name[i] = ship->info.name[i];

		len = str_len(ship->info.type);
		new_ship->info.type = (char*)malloc(len*sizeof(char));
		for (i = 0; i < len; i++)
			new_ship->info.type[i] = ship->info.type[i];
		new_ship->link1 = new_ship;
		new_ship->link2 = new_ship;
	}
	else
		new_ship = NULL;
	return new_ship;
}

//������� ��� ���������� �������� � ��������������� ������

CSHIP *C_insert(CSHIP *ship, CSHIP *el, SORTDATA*sort)
{
	if (ship != NULL)
		if (!a_sma_b(ship->info, el->info, sort))
		{
			CSHIP *l;//�������������� ���������
			l = ship;
			while (ship->link1 != l)
			{
				if (a_sma_b(ship->link1->info, el->info, sort))
				{
					C_add_after(ship, el);
					return l;
				}
				ship = ship->link1;
			}
			C_add_after(ship, el);
			return l;
		}
		else
		{
			C_add_after(ship->link2,el);
			return el;
		}
	else
	{
		el->link1 = el;
		el->link2 = el;
		return el;
	}
}

//������� ��� ����������

CSHIP *C_sort(CSHIP *ship)
{
	if (ship == NULL)
	{
		puts("������ �����������");
		return NULL;
	}
	CSHIP *ship_sorted;//���������� ��������� �� ������ ������� ������
	CSHIP *link;       //��������������� ���������
	SORTDATA sort;     //������ � ����������

	select_sort(&sort);
	ship_sorted = NULL;

	ship->link2->link1 = NULL;

	do
	{
		link = ship;
		ship = ship->link1;
		link->link1 = link;
		link->link2 = link;
		ship_sorted = C_insert(ship_sorted, link, &sort);
	} while (ship != NULL);
	puts("���������� ��������");
	return ship_sorted;
}

//������� ��� ������

CSHIP* C_find(CSHIP* ship)
{
	FINDDATA find;  //������ � ������
	CSHIP *ship_res;//��������� �� ������ ������� ������������� ������
	CSHIP *link;    //��������������� ���������
	CSHIP *new_el;  //��������������� ���������

	select_find(&find);
	ship_res = NULL;
	link = ship;
	ship->link2->link1 = NULL;
	do
	{
		if (is_need(ship->info, &find))
		{
			new_el = C_create_copy(ship);
			ship_res = C_add_frist(ship_res, new_el)->link2;
		}
		ship = ship->link1;
	} while (ship != NULL);
	if (ship_res != NULL)
		puts("����� ��������");
	else
		puts("�� ������� ���������, ��������������� �������� ���������");

	link->link2->link1 = link;

	return ship_res;
}

//������� ��� �������� ����

void C_menu()
{
	int menu;       //��������� ����� ����
	CSHIP *ship;    //��������� �� ������ ������� ������ �������� ������
	CSHIP *ship_res;//��������� �� ������ ������� ������ ����������� ������
	bool is_find;   //������ ������
	int i;          //��������������� ����������

	is_find = false;
	ship = NULL;
	ship_res = NULL;

	do
	{
		system("cls");
		puts("��������� ����������� ������");
		puts("1-���������� ��������� � ������");
		puts("2-�������� ��������� �� ������");
		puts("3-����� ��������� ������");
		puts("4-��������� ������");
		puts("5-����� ����������� ���������� ������");
		puts("6-�������");
		puts("0-������� � �������");
		menu = input_number();
		system("cls");
		switch (menu)
		{
		case 1:
			ship = C_add(ship);
			system("pause");
			break;
		case 2:
			ship = C_del(ship);
			system("pause");
			break;
		case 3:
			C_print(ship);
			system("pause");
			break;
		case 4:
			if (ship != NULL)
			{
				do
				{
					system("cls");
					puts("�������� ��� ���������");
					puts("1-����� (��� ���� ����������� ����� ������)");
					puts("2-���������� ��������� ��������� ������");
					puts("0-������� � �������");
					i = input_number();
					if (i<0 || i>2)
					{
						puts("�� ����������� ����� ����� ����");
						system("pause");
					}
				} while (i<0 || i>2);
				switch (i)
				{
				case 1:
					is_find = TRUE;
					ship_res = C_free_all(ship_res);
					ship_res = C_find(ship);
					system("pause");
					break;
				case 2:
					ship = C_sort(ship);
					system("pause");
					break;
				}
			}
			else
			{
				puts("������ ����, ������������ ������");
				system("pause");
			}
			break;
		case 5:
			if (is_find)
				if (ship_res != NULL)
					C_print(ship_res);
				else
					puts("��� ��������� ������ �� ������� ���������,\n��������������� �������� ���������");
			else
				puts("�� ��� �� ���� �� ��������� �����");
			system("pause");
			break;
		case 6:
			puts("�������");
			puts("��� ����� ������:");
			puts("1. ��� �������������� � ������");
			puts("2. ������� ������� ������� ���������");
			puts("3. ������� � ����� ���������");
			puts("�������� ����� ���� �����:");
			puts("1. ���-������ �� 1 �� 30 ��������");
			puts("2. ���-������ �� 1 �� 20 ��������");
			puts("3. ��������� �� x-����� ����� �� -999999 �� 9999999");
			puts("4. ��������� �� y-����� ����� �� -999999 �� 9999999");
			puts("5. ��������� �� z-����� ����� �� -999999 �� 9999999");
			puts("��������� ��������� - ����� ������ ������ ��������� �� ��������� ���������");
			puts("�������, ������� ������������� �������� ���������.");
			puts("������� ����� ������� ���������.");
			puts("��� ����������� ��������� ������� �������� ����� � n-��� ��������");
			puts("�� ������� � ����� ������� �������");

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
	ship = C_free_all(ship);
	ship_res = C_free_all(ship_res);
}

//@@

int main()
{
	setlocale(0, "RU");
	puts(" ���  �����  ���  ���");
	puts("�   � �     �    �   �");
	puts("�   � ����  �    �����");
	puts("�   � �   � �    �   �");
	puts(" ���  ����   ��� �   �");
	system("pause");
	char menu;//��������� ����� ����
	do
	{
		system("cls");
		puts("������");
		puts("1-����������� ������");
		puts("2-����������� ������");
		puts("3-��������� ����������� ������");
		puts("4-�������");
		puts("0-�����");
		menu = input_number();
		system("cls");
		switch (menu)
		{
		case 1:
			O_menu();
			break;
		case 2:
			D_menu();
			break;
		case 3:
			C_menu();
			break;
		case 4:
			puts("��� ��������� ������������ �������� ������ ������ � ����������.");
			puts("��� ��������� �������� �� �������� ��� �����: ");
			puts("�����������, �����������, ��������� �����������.");
			puts("���������� � ������ ��������� �������������.");
			puts("��� ��������� ��������\\����� ������������ ������� ������ ������,");
			puts("����� ������ �.�.�.");
			puts("��� ��������� �������� ������������ �� ����.");
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
}


