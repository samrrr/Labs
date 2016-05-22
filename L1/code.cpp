#include <conio.h>
#include <malloc.h>
#include <stdio.h>
#include <windows.h>
#include <locale.h>
#include <math.h>

typedef struct ST
			{
				char *name;//��������� �� ������ ������ ������, ���������� ��� ���������
				char *type;//��������� �� ������ ������ ������, ���������� ��� ���������
				int x;     //��������� ��������� �� x
				int y;     //��������� ��������� �� y
				int z;     //��������� ��������� �� z
			} SHIP;

//������� ��� ��������� �������

char my_getch()
	{
		char ch;//��� ������� ������

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
			} 
		while (ch >= -128 && ch <= -17 || ch == '\0' || ch == -32);
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
								s = (char *)realloc(s, sizeof(char)*(length + 1));
								printf("%c", ch);
								s[length - 1] = ch;
								length++;
							}
						break;
					}
			} 
		while (ch != '\n' || length == 1 || length == 2 && *s == '-');
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
						printf("\b%c", sy);
						break;
					}
			} 
		while (ch != '\n' || sy == 0);
		printf("\n");
		return sy == 'y' || sy == 'Y';
	}

//������� ��� ����� ������

char *input_string(int size)
	{
		char *s;   //��������� �� ������ ������ �������� ������
		int length;//����� ������
		char ch;   //�������� ������

		length = 1;
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
								s = (char *)realloc(s, sizeof(char)*(length + 1));
								printf("%c", ch);
								s[length - 1] = ch;
								length++;
							}
						break;
					}
			} 
		while (ch != '\n' || length == 1);
		printf("\n");
		return s;
	}

//������� ��� ���������� ������ ������

int str_len(char*s)
	{
		int i = 0;//����� ������

		while (s[i])
			i++;
		return i+1;
	}

//������� ��� ������� ������ �� ��� ��������

SHIP *free_structs(SHIP *ship, int len)
	{
		int i;//��������������� ����������
		if (ship != NULL)
		{
			for (i = 0; i < len; i++)
			{
				free(ship[i].name);
				free(ship[i].type);
			}
			free(ship);
		}
		return NULL;
	}

//������� ��� ������ ������ ����� ���������

void print_struct(SHIP ship)
	{
		printf("��� ���������: \"%s\"\n", ship.name);
		printf("��� ���������: \"%s\"\n", ship.type);
		printf("��������� ��������� �� x:%i\n", ship.x);
		printf("��������� ��������� �� y:%i\n", ship.y);
		printf("��������� ��������� �� z:%i\n", ship.z);
	}

//������� ��� ������ ���� ��������

void print_structs(SHIP *ship,int ships)
	{
		int i;//��������������� ����������

		if (ship != NULL)
		{
			for (i = 0; i < ships; i++)
			{
				if (i % 3 == 0 && i > 0)
					system("pause");
				printf("\n�������� %i\n", i);
				print_struct(ship[i]);
			}
			puts("\n����� �������");
		}
		else
			puts("������ ����");
	}

//������� ��� ����� ����

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
		char *s;  //��������� �� ������ ������ ������
		bool exit;//������ ������

		exit = 0;
		do
			{
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
			} 
		while (!exit);
		return s;
	}

//������� ��� ����� ���������

int get_coord(char ch)
{
	printf("������� ��������� �� %c � ����������� (����� ����� �� -999999 �� 9999999):\n", ch);
	return input_number();
}

//������� ��� ����� ����� ���������

void get_struct(SHIP *info)
	{
		info->name = get_name();
		info->type = get_type();
		info->x = get_coord('x');
		info->y = get_coord('y');
		info->z = get_coord('z');
	}

//������� ��� ����� ������� ��������

SHIP *get_structs(int *ships)
	{
		bool is_end_input;//��������������� ����������
		SHIP *ship;       //������ ������� �������� ������ ��������� ������� �������� ������
		
		is_end_input = false;
		ship = NULL;
		*ships = 0;
		do
			{
				ship = (SHIP*)realloc(ship, (*ships + 1)*sizeof(SHIP));
				get_struct(ship + *ships);
				(*ships)++;
				puts("���������� ����?(y/n)");
				is_end_input = !input_yn();
			} 
		while (!is_end_input);
		return ship;
	}

//������� ��� ��������� ������

SHIP *processing(SHIP *ship, int ship_len, int *ship_result_len)
	{
		SHIP *ship_result;//������ 
		int i;            //��������������� ����������
		int r;            //��������������� ����������
		int len;          //������ ������
		char *name_find;  //��������� ���
		char *type_find;  //��������� ���
		bool is_type_name;//������ ������ �� �����
		bool is_type_type;//������ ������ �� ����

		do
			{
				puts("�������� ��������:");
				puts("1-�� �����");
				puts("2-�� ����");
				puts("3-�� ���� � �� �����");
				i = input_number();
				system("cls");
				if (i < 1 || i > 3)
					{
						puts("��� ������ ������");
						system("pause");
						system("cls");
					}
			}
		while (i < 1 || i > 3);
		is_type_name = i == 1 || i == 3 ? 1 : 0;
		is_type_type = i == 2 || i == 3 ? 1 : 0;
		if (is_type_name)
				name_find = get_name();
		if (is_type_type)
				type_find = get_type();

		ship_result = NULL;
		*ship_result_len = 0;
		for (i = 0; i<ship_len; i++)
		if ((!is_type_name || !strcmp(name_find, ship[i].name))
			&& (!is_type_type || !strcmp(type_find, ship[i].type)))
			{
				ship_result = (SHIP*)realloc(ship_result, sizeof(SHIP)*(*ship_result_len + 1));

				len = str_len(ship[i].name);
				(ship_result + *ship_result_len)->name = (char*)malloc(sizeof(char)*len);
				for (r = 0; r < len; r++)
					(ship_result + *ship_result_len)->name[r] = ship[i].name[r];

				len = str_len(ship[i].type);
				(ship_result + *ship_result_len)->type = (char*)malloc(sizeof(char)*len);
				for (r = 0; r < len; r++)
					(ship_result + *ship_result_len)->type[r] = ship[i].type[r];

				(ship_result + *ship_result_len)->x = ship[i].x;
				(ship_result + *ship_result_len)->y = ship[i].y;
				(ship_result + *ship_result_len)->z = ship[i].z;
				(*ship_result_len)++;
			}
		if (is_type_name)
			free(name_find);
		if (is_type_type)
			free(type_find);
		return ship_result;
	}
int main()
	{
		SHIP *ship=NULL;          //��������� �� ������ ������� ��������� �������
		SHIP *ship_result=NULL;   //��������� �� ������ ������� ������������� �������
		int ship_len=0;           //���������� ��������� � �������� �������
		int ship_result_len=0;    //���������� ��������� � ����������� �������
		int menu;                 //�������� ����� ����
		bool is_input = false;    //������ ������� ��������� ������� (1-�������� ������ �����, 0-�������� ������ �� �����)
		bool is_processed = false;//������ ���������� ��������� ������� (1-��������� ����, 0-��������� �� ����)
		bool is_output = false;   //������ ������� ��������� ������� (1-�������� ������ �����, 0-�������� ������ �� �����)

		setlocale(0, "RU");
		do
			{
		
				system("cls");
				puts("����");
				puts("1-������ ������ � ����������");
				puts("2-������� ������ � ����������");
				puts("3-���������� ������ � ����������");
				puts("4-������� ������������ ������");
				puts("5-�������");
				puts("0-�����");

				menu = input_number();

				system("cls");
	
				switch (menu)
					{
						case 1:

							ship=free_structs(ship, ship_len);
							ship_result=free_structs(ship_result, ship_result_len);

							is_input = true;
							is_output = false;
							is_processed = false;

							ship = get_structs(&ship_len);
							puts("\n���� �������");
							system("pause");
							break;
						case 2:
							if (is_input)
								print_structs(ship, ship_len);
							else
								puts("������ ��� �� �������");
							system("pause");
							break;
						case 3:
							if (is_input)
								{
									ship_result=free_structs(ship_result, ship_result_len);
									ship_result = processing(ship,ship_len,&ship_result_len);
									if (ship_result_len > 0)
										{
											is_output = true;
											puts("��������� ������� ���������");
										}
									else
										{
											is_output = false;
											puts("�� ������� ����������, ��������������� ������� ��������");
										}
									is_processed = true;
								}
							else
								puts("������ �� �������");
							system("pause");
							break;
						case 4:
							if (is_input)
								if (is_processed)
									if (is_output)
										print_structs(ship_result, ship_result_len);
									else
										printf("�� ������� ����������, ��������������� ������� ��������");
								else
									printf("��������� �� �����������");
							else
								printf("��� ������� ������");
							printf("\n");
							system("pause");
							break;
						case 5:
							puts("��� ��������� ������������ �������� ������ ������ � ����������.");
							puts("�������� ����� ���� �����:");
							puts("1. ���-������ �� 1 �� 30 ��������");
							puts("2. ���-������ �� 1 �� 20 ��������");
							puts("3. ��������� �� x-����� ����� �� -999999 �� 9999999");
							puts("4. ��������� �� y-����� ����� �� -999999 �� 9999999");
							puts("5. ��������� �� z-����� ����� �� -999999 �� 9999999");
							puts("��������� ��������� - ����� ������ ������ ��������� �� ��������� ���������");
							puts("�������, ������� ������������� �������� ���������.");
							puts("������� ����� ������� ���������.");
							system("pause");
							break;
						case 0:
							break;
						default:
							printf("����������� ����� ����� ����\n");
							system("pause");
							break;
					}
			} 
		while (menu != 0);

		ship=free_structs(ship, ship_len);
		ship_result=free_structs(ship_result, ship_result_len);
	}
