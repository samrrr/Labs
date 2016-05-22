#include <conio.h>
#include <malloc.h>
#include <stdio.h>
#include <windows.h>
#include <locale.h>
#include <math.h>

typedef struct ST
			{
				char *name;//Указатель на первый символ строки, содержащий имя кораблика
				char *type;//Указатель на первый символ строки, содержащий тип кораблика
				int x;     //Положение кораблика по x
				int y;     //Положение кораблика по y
				int z;     //Положение кораблика по z
			} SHIP;

//Функция для получения символа

char my_getch()
	{
		char ch;//Код нажатой кнопки

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

//Функция для ввода целого числа

int input_number()
	{
		int number;    //Введённое число	
		char *s;       //Указатель на первый символ исходной строки
		int length = 1;//Длина строки
		char ch;       //Введённый символ

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

//Функция для ввода ответа y/n

bool input_yn()
	{
		char sy;       //Введённый символ
		char ch;       //Нажатая клавиша

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

//Функция для ввода строки

char *input_string(int size)
	{
		char *s;   //Указатель на первый символ исходной строки
		int length;//Длина строки
		char ch;   //Введённый символ

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

//Функция для вычисления длинны строки

int str_len(char*s)
	{
		int i = 0;//Длина строки

		while (s[i])
			i++;
		return i+1;
	}

//Функция для очистки памяти из под структур

SHIP *free_structs(SHIP *ship, int len)
	{
		int i;//Вспомогательная переменная
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

//Функция для вывода данных одной структуры

void print_struct(SHIP ship)
	{
		printf("Имя кораблика: \"%s\"\n", ship.name);
		printf("Тип кораблика: \"%s\"\n", ship.type);
		printf("Положение кораблика по x:%i\n", ship.x);
		printf("Положение кораблика по y:%i\n", ship.y);
		printf("Положение кораблика по z:%i\n", ship.z);
	}

//Функция для вывода всех структур

void print_structs(SHIP *ship,int ships)
	{
		int i;//Вспомогательная переменная

		if (ship != NULL)
		{
			for (i = 0; i < ships; i++)
			{
				if (i % 3 == 0 && i > 0)
					system("pause");
				printf("\nКораблик %i\n", i);
				print_struct(ship[i]);
			}
			puts("\nВывод окончен");
		}
		else
			puts("Массив пуст");
	}

//Функция для ввода типа

char* get_type()
	{
		char *types[4] = { "battleship", "cruiser", "boat", "steelship" };
		//Массив указателей на первый символ строки
		int i;    //Вспомогательная переменная
		char *s;  //Указатель на первый символ вводимой строки
		char type;//Тип ораблика
		char len; //Длина строки

		puts("Выберите тип:");
		for (i = 0; i < 4; i++)
			printf("%i-%s\n", i + 1, types[i]);
		puts("другое число-ввод типа вручную\n");
		type = input_number();
		if (type <= 0 || type >= 5)
			{
				puts("Вводите тип (от 1 до 20 символов):");
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

//Функция для ввода имени

char* get_name()
	{
		char *s;  //Указатель на первый символ строки
		bool exit;//Флажок выхода

		exit = 0;
		do
			{
				puts("Введите имя (имя должно содержать хотя бы один символ");
				puts("и не более 30 символов):");
				s = input_string(30);
				if (*s < 'A' || *s > 'Z')
					{
						puts("Вниание! Имя корабля начинается не с большой буквы.");
						puts("Вы хотите ввести другое имя? (y/n)");
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

//Функция для ввода координат

int get_coord(char ch)
{
	printf("Вводите положение по %c в сантиметрах (целое число от -999999 до 9999999):\n", ch);
	return input_number();
}

//Функция для ввода полей структуры

void get_struct(SHIP *info)
	{
		info->name = get_name();
		info->type = get_type();
		info->x = get_coord('x');
		info->y = get_coord('y');
		info->z = get_coord('z');
	}

//Функция для ввода массива структур

SHIP *get_structs(int *ships)
	{
		bool is_end_input;//Вспомогательная переменная
		SHIP *ship;       //Адресс первого элемента первой структуры массива исходных данных
		
		is_end_input = false;
		ship = NULL;
		*ships = 0;
		do
			{
				ship = (SHIP*)realloc(ship, (*ships + 1)*sizeof(SHIP));
				get_struct(ship + *ships);
				(*ships)++;
				puts("Продолжить ввод?(y/n)");
				is_end_input = !input_yn();
			} 
		while (!is_end_input);
		return ship;
	}

//Функция для обработки данных

SHIP *processing(SHIP *ship, int ship_len, int *ship_result_len)
	{
		SHIP *ship_result;//Адресс 
		int i;            //Вспомогательная переменная
		int r;            //Вспомогательная переменная
		int len;          //Длинна строки
		char *name_find;  //Требуемое имя
		char *type_find;  //Требуемый тип
		bool is_type_name;//Флажок поиска по имени
		bool is_type_type;//Флажок поиска по типу

		do
			{
				puts("Выберите критерий:");
				puts("1-по имени");
				puts("2-по типу");
				puts("3-по типу и по имени");
				i = input_number();
				system("cls");
				if (i < 1 || i > 3)
					{
						puts("Нет такого пункта");
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
		SHIP *ship=NULL;          //Указатель на первый элемент исходного массива
		SHIP *ship_result=NULL;   //Указатель на первый элемент обработанного массива
		int ship_len=0;           //Количество элементов в исходном массиве
		int ship_result_len=0;    //Количество элементов в обработаном массиве
		int menu;                 //Выбраный пункт меню
		bool is_input = false;    //Флажок наличия исходного массива (1-исходный массив введён, 0-исходный массив не введён)
		bool is_processed = false;//Флажок проведения обработки массива (1-обработка была, 0-обработки не было)
		bool is_output = false;   //Флажок наличия исходного массива (1-исходный массив введён, 0-исходный массив не введён)

		setlocale(0, "RU");
		do
			{
		
				system("cls");
				puts("Меню");
				puts("1-Ввести данные о корабликах");
				puts("2-Вывести данные о корабликах");
				puts("3-Обработать данные о корабликах");
				puts("4-Вывести обработанные данные");
				puts("5-Справка");
				puts("0-Выход");

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
							puts("\nВвод окончен");
							system("pause");
							break;
						case 2:
							if (is_input)
								print_structs(ship, ship_len);
							else
								puts("Данные ещё не введены");
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
											puts("Обработка успешно завершена");
										}
									else
										{
											is_output = false;
											puts("Не найдено корабликов, соответствующих данному критерию");
										}
									is_processed = true;
								}
							else
								puts("Данные не введены");
							system("pause");
							break;
						case 4:
							if (is_input)
								if (is_processed)
									if (is_output)
										print_structs(ship_result, ship_result_len);
									else
										printf("Не найдено корабликов, соответствующих данному критерию");
								else
									printf("Обработка не проводилась");
							else
								printf("Нет входных данных");
							printf("\n");
							system("pause");
							break;
						case 5:
							puts("Эта программа обрабатывает заданный массив данных о корабликах.");
							puts("Кораблик имеет пять полей:");
							puts("1. Имя-строка от 1 до 30 символов");
							puts("2. Тип-строка от 1 до 20 символов");
							puts("3. Положение по x-целое число от -999999 до 9999999");
							puts("4. Положение по y-целое число от -999999 до 9999999");
							puts("5. Положение по z-целое число от -999999 до 9999999");
							puts("Результат обработки - новый массив данных состоящий из элементов исходного");
							puts("массива, которые соответствуют заданным критериям.");
							puts("Русские буквы вводить запрещено.");
							system("pause");
							break;
						case 0:
							break;
						default:
							printf("Неправильно введён пункт меню\n");
							system("pause");
							break;
					}
			} 
		while (menu != 0);

		ship=free_structs(ship, ship_len);
		ship_result=free_structs(ship_result, ship_result_len);
	}
