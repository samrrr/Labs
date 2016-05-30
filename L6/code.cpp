#include <conio.h>
#include <malloc.h>
#include <stdio.h>
#include <windows.h>
#include <locale.h>

HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);

/*
Описание: Это функция для вывода числа в битовом представлении.
Возврат: Функция не возвращает значения.
*/
void put_bits(int i)
{
	int m = 31;//Номер выводимого бита
	do
	{
		printf("%i", i <0);
		i <<= 1;
		m--;
	} while (m >= 0);
}

/*
Описание: Это функция для вывода числа в битовом виде c раскраской.
Возврат: Функция не возвращает значения.
*/
void put_colored_bits(int i, int b1, int b2, int b3)
{
	int m = 31;//Номер выводимого бита
	do
	{
		if(m==b1)
			SetConsoleTextAttribute(hConsole, (WORD)(4));
		else
			if (m == b2)
				SetConsoleTextAttribute(hConsole, (WORD)(2));
			else
				if (m == b3)
					SetConsoleTextAttribute(hConsole, (WORD)(15));

		
		printf("%i", i <0);
		i <<= 1;
		m--;
	} while (m >= 0);
	SetConsoleTextAttribute(hConsole, (WORD)(15));
}

/*
Описание: Это функция для получения нажатой клавиши.
Возврат: Эта функция возвращает символ нажатой клавиши.
*/
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
	} while (ch >= -128 && ch <= -17 || ch == '\0' || ch == -32);
	return ch;
}

/*
Описание: Это функция для ввода целого числа.
Возврат: Эта функция возвращает введённое число.
*/
int input_number()
{
	int number;    //Введённое число	
	char *s;       //Указатель на первый символ исходной строки
	int length = 1;//Длина строки
	char ch;       //Введённый символ
	s = (char*)malloc(sizeof(char));
	do
	{
		ch = my_getch();//Получаем символ нажатой кнопки
		switch (ch)
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
			if ((ch >= '0' && ch <= '9' || ch == '-' && length == 1) && length <= 9)
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
Описание: Это функция для ввода целого числа побитово.
Возврат: Эта функция возвращает введённое число.
*/
int input_binary_number()
{
	int i;         //Введённое число	
	char ch;       //Введённый символ
	int n;         //Номер вводимого бита

	i = 0;
	n = 31;

	do
	{
		ch = my_getch();
		switch (ch)
		{
		case '\b':
			if (n < 31)
			{	
				printf("\b \b");
				i = i & ~(1 << ++n);
			}
			break;
		case '0':
		case '1':
			if (n >= 0)
			{
				printf("%c", ch);
				i = i | ((ch - '0') << n--);
			}
			break;
		default:
			break;
		}
	} while (ch != '\n' || n >= 0);
	puts("");
	return i;
}

/*
Описание: Это функция для локального циклического сдвига вправо.
Возврат: Эта функция возвращает изменённое число.
*/
int sdv_p_с(int c, int b1, int b2, int k)
{
	c =
		(c & ~(0xFFFFFFFF >> b1 << b1 << b2 >> b2)) |
		((c & 0xFFFFFFFF) << b2 >> b2 >> b1 >> k << b1) |
		((c & 0xFFFFFFFF) >> b1 << (32 - k) >> b2);
	return c;
}

/*
Описание: Это функция для локального сдвига вправо.
Возврат: Эта функция возвращает изменённое число.
*/
int sdv_p(int c, int b1, int b2, int k)
{
	c =
		(c & ~(0xFFFFFFFF >> b1 << b1 << b2 >> b2)) |
		((c & 0xFFFFFFFF) << b2 >> b2 >> b1 >> k << b1);
	return c;
}

/*
Описание: Это функция для локального сдвига влево.
Возврат: Эта функция возвращает изменённое число.
*/
int sdv_l(int c, int b1, int b2, int k)
{

	c =
		(c & ~(0xFFFFFFFF >> b1 << b1 << b2 >> b2)) |
		((c & 0xFFFFFFFF) >> b1 << b1 << b2 << k >> b2);
	return c;
}

/*
Описание: Это функция для создания меню ввода.
Возврат: Эта функция возвращает число.
*/
int menu_input(int i, bool *is_input,bool *is_res)
{
	int menu;       //Переменная выбранного пункта меню
	do
	{
		system("cls");
		puts("Ввод целого числа");
		if (*is_input == 1)
			puts("Внимание! При вводе нового числа, старое число и старый результат стираются");
		puts("1-ввод в десятичной системе счисления");
		puts("2-ввод в виде битов");
		puts("0-возврат в надменю");
		puts("");
		puts("Ваш выбор:");
		menu = input_number();
		system("cls");
		switch (menu)
		{
		case 1:
			puts("Разрешено вводить только цифры, ввод других символов будет игнорироваться");
			puts("Для окончания ввода нажмите ВВОД");
			puts("Вводите целое число от -99999999 до 999999999:");
			i = input_number();
			*is_input = 1;
			*is_res = 0;
			puts("Число успешно введено");
			system("pause");
			break;
		case 2:
			puts("Разрешено вводить только '1' и '0', ввод других символов будет игнорироваться");
			puts("Надо ввести все 32 бита");
			puts("После того, как введёте все биты нажмите ВВОД");
			puts("Вводите биты начиная с 31:");
			i = input_binary_number();
			*is_input = 1;
			*is_res = 0;
			puts("Число успешно введено");
			system("pause");
			break;
		case 0:
			break;
		default:
			puts("Нет такого пункта меню");
			system("pause");
			break;
		}
	} while (menu != 0);
	return i;
}

/*
Описание: Это функция для создания меню вывода.
Возврат: Эта функция ничего возвращает.
*/
void menu_output(int i,int i_res,bool is_res)
{
	int menu;       //Переменная выбранного пункта меню
	do
	{
		system("cls");
		puts("Вывод целого числа");
		puts("1-вывод исходного числа");
		puts("2-вывод результата обработки числа");
		puts("0-возврат в надменю");
		puts("");
		puts("Ваш выбор:");
		menu = input_number();
		system("cls");
		switch (menu)
		{
		case 1:
			puts("Исходное число:");
			puts("В десятичной системе счисления:");
			printf("%i\n",i);
			puts("В битовом представлении:");
			put_bits(i);
			puts("");
			system("pause");
			break;
		case 2:
			if (is_res)
			{
				puts("Результат обработки:");
				puts("В десятичной системе счисления:");
				printf("%i\n", i_res);
				puts("В битовом представлении:");
				put_bits(i_res);
				puts("");
			}
			else
				puts("Вы ещё не обрабатывали исходное число. Выводить нечего");
			system("pause");
			break;
		case 0:
			break;
		default:
			puts("Нет такого пункта меню");
			system("pause");
			break;
		}
	} while (menu != 0);
}

/*
Описание: Это функция для ввода параметров функции.
Возврат: Эта функция ничего возвращает.
*/
void input_sdvp(int*k, int*b1, int*b2)
{
	do
	{
		puts("Введите номер бита от 0 до 30, с которого будет сдвиг:");
		*b1 = input_number();
		if ((*b1 < 0 || *b1 >= 31))
		{
			puts("Ошибка! Вы ввели число за пределами допустимых значений");
			system("pause");
		}
	} while (*b1<0 || *b1 >= 31);
	do
	{
		printf("Введите номер бита от %i до 31, до которого включительно будет сдвиг:\n", *b1+1);
		*b2 = input_number();
		if (*b2 <= *b1 || *b2 >= 32)
		{
			puts("Ошибка! Вы ввели число за пределами допустимых значений");
			system("pause");
		}
	} while (*b2 <= *b1 || *b2 >= 32);
	do
	{
		printf("Введите количество битов для сдвига от 1 до %i, до которого\nвключительно будет сдвиг:\n", *b2-*b1);
		*k = input_number();
		if (*k<1 || *k > *b2 - *b1)
		{
			puts("Ошибка! Вы ввели число за пределами допустимых значений");
			system("pause");
		}
	} while (*k<1 || *k > *b2 - *b1);
}

/*
Описание: Это функция для создания меню битовых операций.
Возврат: Эта функция ничего возвращает.
*/
int menu_bits(int i, int i_res, bool *is_res)
{
	int menu;       //Переменная выбранного пункта меню
	int k;         //Количество битов для ввода
	int b1;         //Номер первого бита для сдвига 
	int b2;         //Номер последнего бита для сдвига
	int r;          //Вспомогательная переменная

	do
	{
		system("cls");
		puts("Битовые операции");
		if (*is_res == 1)
			puts("Внимание! При обработке старый результат стирается");
		puts("1-локальный циклический сдвиг вправо");
		puts("2-локальный циклический сдвиг влево");
		puts("3-локальный сдвиг вправо");
		puts("4-локальный сдвиг влево");
		puts("0-возврат в надменю");
		puts("");
		puts("Ваш выбор:");

		menu = input_number();
		system("cls");
		switch (menu)
		{
		case 1:
			puts("Локальный циклический сдвиг вправо");
			input_sdvp(&k, &b1, &b2);
			i_res = sdv_p_с(i, b1, 31 - b2, k);
			break;
		case 2:
			puts("Локальный циклический сдвиг влево");
			input_sdvp(&k, &b1, &b2);
			i_res = sdv_p_с(i, b1, 31 - b2, b2 - b1 + 1 - (k));
			break;
		case 3:
			puts("Локальный сдвиг вправо");
			input_sdvp(&k, &b1, &b2);
			i_res = sdv_p(i, b1, 31 - b2, k);
			break;
		case 4:
			puts("Локальный сдвиг влево");
			input_sdvp(&k, &b1, &b2);
			i_res = sdv_l(i, b1, 31 - b2, k);
			break;
		case 0:
			break;
		default:
			puts("Нет такого пункта меню");
			system("pause");
			break;
		}
		if (menu >= 1 && menu <= 4)
		{
			*is_res = 1;

			puts("Операция прошла успешно");

			printf("Число в битовом виде:               ");
			if (menu == 2 || menu == 4)
				put_colored_bits(i, b2, b2 - k, b1 - 1);
			else
				put_colored_bits(i, b1 + k - 1, b2, b1 - 1);
			printf("\n                                    ");
			for (r = 31; r >= 0; r--)
				printf(r <= b2 && r >= b1 ? "|" : " ");
			printf("\nРезультат обработки в битовом виде: ");
			if (menu == 2 || menu == 4)
				put_colored_bits(i_res, b1 + k - 1, b2, b1 - 1);
			else
				put_colored_bits(i_res, b2, b2 - k, b1 - 1);
			puts("");

			system("pause");
		}
	} while (menu != 0);
	return i_res;
}

void main()
{
	setlocale(0, "RU");


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
	SetConsoleTextAttribute(hConsole, (WORD)(15));


	int i;     //Введённое число
	int i_res; //Результат обработки числа
	bool is_input; //Флажок ввода
	bool is_res;   //Флажок результата
	int menu;      //Переменная выбранного пункта меню

	is_input = 0;
	is_res = 0;
	i = 0;
	i_res = 0;

	do
	{
		system("cls");
		puts("Битовые операции");
		puts("1-ввод числа");
		puts("2-вывод числа");
		puts("3-битовые операции с исходным числом");
		puts("4-справка");
		puts("0-выход");
		puts("");
		puts("Ваш выбор:");
		menu = input_number();
		system("cls");
		switch (menu)
		{
		case 1:
			i = menu_input(i, &is_input,&is_res);
			break;
		case 2:
			if(is_input)
				menu_output(i,i_res,is_res);
			else
			{
				puts("Сначала введите число");
				system("pause");
			}
			break;
		case 3:
			if (is_input)
				i_res = menu_bits(i,i_res,&is_res);
			else
			{
				puts("Сначала введите число");
				system("pause");
			}
			break;
		case 4:
			puts("Это программа дла ввода, вывода и побитовой обработки целого");
			puts("числа, записанного в 32 битах.");
			puts("Число можно ввести в битовом виде или в десятичной системе счисления.");
			puts("При вводе в битовом виде можно вводить только '1' и '0' и обязательно");
			puts("надо ввести все 32 бита.");
			puts("При вводе в десятичной системе счисления можно вводить только цифры");
			puts("и можно ввести только число от -99999999 до 999999999.");
			puts("При выборе параметров битовых операций вы вводите:");
			puts("  b1-бит с которого будет сдвиг");
			puts("  b2-бит по который будет сдвиг");
			puts("");
			puts("  k-число битов на которое будет сдвиг");
			puts("При этом вы обязаны соблюдать правила: 30>=b1>=0, 31>=b2>b1, b2-b1>=k>0");
			puts("Результат операции выводиться сразу, а так же его можно вывести в");
			puts("пункте вывод числа.");
			puts("Сдвиг нельзя сделать для одного бита");
			puts("При вводе нового числа, старое число и старый результат стираются");
			puts("При обработке старый результат стирается");
			system("pause");
			break;
		case 0:
			break;
		default:
			puts("Нет такого пункта меню");
			system("pause");
			break;
		}
	} while (menu != 0);
}






































































//**//PF put_colored_bits,i,"Исходное число"
//**//PF sdv_p_с,c,"Исходное число"
//**//PF sdv_p,c,"Исходное число"
//**//PF sdv_l,c,"Исходное число"
//**//PF menu_input,i,"Указатель на исходное число"
//**//PF menu_input,is_res,"Указатель на флажок обработки числа"
//**//PF menu_output,i,"Исходное число"
//**//PF menu_output,i_res,"Флажок обработки"
//**//PF menu_bits,i,"Указатель на исходное число"
//**//PF menu_bits,i_res,"Указатель на результат обработки"
//**//PF menu_bits,is_res,"Указатель на флажок обработки числа"
//**//PF put_bits,i,"Выводимое число"

//**//PF put_colored_bits,b1,"Номер бита с которого начинается красная раскраска"
//**//PF put_colored_bits,b2,"Номер бита с которого начинается зелёная раскраска"
//**//PF put_colored_bits,b3,"Номер бита с которого начинается белая раскраска"
//**//PF menu_input,is_input,"Указатель на флажок ввода"
//**//PF input_sdvp,k,"Указатель на количество бит для сдвига вправо"
//**//PF input_sdvp,b1,"Указатель на номер бита с которого будет сдвиг"
//**//PF input_sdvp,b2,"Указатель на номер бита по который будет сдвиг"


//**//PF sdv_p_с,b2,"Номер бита с конца до которого будет сдвиг"
//**//PF sdv_p,b2,"Номер бита с конца до которого будет сдвиг"
//**//PF sdv_l,b2,"Номер бита с конца до которого будет сдвиг"







/*END


bool void char int short int 
*/