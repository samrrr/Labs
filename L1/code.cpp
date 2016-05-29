// files

#include  <stdio.h>
#include  <Windows.h>
#include  <string.h>
#include <malloc.h>
#include <locale.h>

#define MIN_STRING_LENGTH 2  //минимальная длина строки
#define MAX_STRING_LENGTH 20 //максимальная длина строки
#define MIN_YEAR 1869        //минимальное значение года
#define MAX_YEAR 2016        //максимальное значение года
#define MIN_PRICE 1          //минимальная цена
#define MAX_PRICE 200000     //максимальная цена

typedef struct
{
	char* artist; //исполнитель
	char* album;  //альбом
	int year;     //год издания
	float price;  //цена
}DATA; //структура с информационными полями

typedef struct node
{
	DATA* data; //структура с информационными полями
	node* next; //указатель на следующий узел
	node* prev; //указатель на предыдущий узел
}NODE; //узел

int userchoice();                                     //выбор пункта меню
NODE* add(NODE*);                                     //меню добавления узлов
NODE* add_first(NODE*);                               //добавление узла в начало
NODE* add_n(NODE*);                                   //добавление n-ого узла
NODE* add_last(NODE*);                                //добавление узла в конец
void cnsl_output(NODE*);                              //вывод в консоль
int get_n(int, char*, char*);                         //ввод вспомогательной переменной (кол-во выводимых записей, номер удаляемого узла итп)
NODE* fill_fields();                                  //заполнение информационных полей
char* string_input(char* header, char* inputitem);    //ввод строк
float price_input(char* header);                      //ввод цены
int year_input(char* header);                         //ввод года
char* copy_string(char* original);                    //копия строки
int amt(NODE* list);                                  //количество узлов в списке
int punctuation(char symbol);                         //проверка символа на принадлежность к знакам пунктуации
int menu(NODE*);                                      //меню
NODE* read_from_file(NODE*, char*);                   //добавление записей из файла
NODE* read_to_node(char*);                            //заполнение информационного поля узла данными из файла
char* str_read(char *str, int *i);                    //коррекция считанной строки
void write_to_file(NODE*, char*);                     //вывод списка в файл
int file_read_help();                                 //справка по добавлению записей из файла
char* get_file_name(char*);                           //ввод расположения/имени файла
NODE* free_node(NODE*tmp);                            //освобождение памяти из-под списка
NODE* free_ll(NODE*list);                             //освобождение памяти из-под узла

int main()
{
	setlocale(0, "");
	SetConsoleCP(1251);
	SetConsoleOutputCP(1251);

	NODE* list = NULL; //список
	int uc;//выбор пользователя
	int uc2;//выбор пользователя - 2

	do
	{
		uc = menu(list); //вывод меню

		switch (uc)
		{
		case 1: //тут будет справка
			break;
		case 2: //добавление узлов
			do
			{
				system("cls");
				printf_s("\n ЗАПОЛНЕНИЕ СПИСКА\n\n");
				puts(" 1 - Добавить данные вручную");
				puts(" 2 - Добавить данные из файла");
				puts(" 0 - Вернуться в главное меню");

				uc2 = userchoice();

				switch (uc2)
				{
				case 1: //меню добавления записей с клавиатуры
					list = add(list);
					break;
				case 2: //добавление из файла
				{
					int cont = file_read_help(); //справка по добавлению записей из файла
					if (cont) //если пользоватеь все же хочет добавить записи из файла
					{
						char* fn = get_file_name("ДОБАВЛЕНИЕ ЗАПИСЕЙ ИЗ ФАЙЛА"); //ввод имени файла
						list = read_from_file(list, fn); //добавление записей
						system("pause");
					}
					break;
				}

				case 0: //отмена
					break;
				default:
					system("cls");
					printf_s("\n ОШИБКА\n");
					printf_s("\n Введите существующий пункт\n\n ");
					system("pause");
				}
			} while (uc2 && uc2 < 0 || uc2 > 2);
			break;
		case 3: //вывод списка
			if (list)
			{
				do
				{
					system("cls");

					printf_s("\n ВЫВОД СПИСКА\n\n");
					puts(" 1 - На экран");
					puts(" 2 - Сохранить в файл");
					puts(" 0 - Вернуться в главное меню");

					uc2 = userchoice();

					switch (uc2)
					{
					case 1: //вывод в консоль
						cnsl_output(list);
						break;
					case 2: //вывод в файл
					{
						char* fn = get_file_name("СОХРАНЕНИЕ СПИСКА В ФАЙЛ"); //ввод имени файла
						write_to_file(list, fn); //вывод в файл
						system("pause");
						break;
					}
					case 0: //отмена
						break;
					default:
						system("cls");
						printf_s("\n ОШИБКА\n");
						printf_s("\n Введите существующий пункт\n\n ");
						system("pause");
						break;
					}
				} while (uc2 && uc2 < 0 || uc2 > 2);
			}
			else
			{
				system("cls");
				printf_s("\n ОШИБКА\n");
				printf_s("\n Введите существующий пункт\n\n ");
				system("pause");
			}
			break;
		case 4://удаление списка
			if (list)
				list = free_ll(list);
			else
			{
				system("cls");
				printf_s("\n ОШИБКА\n");
				printf_s("\n Введите существующий пункт\n\n ");
				system("pause");
			}
			break;
		case 0: //выход
			if (list)
				list = free_ll(list);
			break;
		default:
			system("cls");
			printf_s("\n ОШИБКА\n");
			printf_s("\n Введите существующий пункт\n\n ");
			system("pause");
		}
	} while (uc);
	return 0;
}

// ввод выбранного пункта меню
int userchoice()
{
	int uc; //выбор пользователя
	printf_s("\n\n Выбор: ");
	rewind(stdin);
	scanf_s("%d", &uc);
	return uc;
}

//меню добавления узлов с клавиатуры
NODE* add(NODE* list)
{
	int uc;

	do
	{
		system("cls");

		printf_s("\n ДОБАВЛЕНИЕ ДАННЫХ ВРУЧНУЮ\n\n");
		puts(" 1 - В начало списка");
		puts(" 2 - В произвольную позицию");
		puts(" 3 - В конец списка");
		puts(" 0 - Назад");

		uc = userchoice();

		switch (uc)
		{
		case 1:
			list = add_first(list);
			break;
		case 2:
			list = add_n(list);
			break;
		case 3:
			list = add_last(list);
			break;
		case 0:
			break;
		default:
			system("cls");
			printf_s("\n ОШИБКА\n");
			printf_s("\n Введите существующий пункт\n\n ");
			system("pause");
			break;
		}
	} while (uc && uc < 0 || uc > 3);

	return list;
}

//добавление узла в начало
NODE* add_first(NODE* list)
{
	NODE* nta = fill_fields();
	nta->next = list;
	if (list)
		list->prev = nta;
	nta->prev = NULL;

	printf_s("\n Новая запись была добавлена в начало списка\n\n ");
	system("pause");
	return nta;
}

//добавление узла в н-ную позицию
NODE* add_n(NODE* list)
{
	if (!list)
	{
		system("cls");
		printf_s("\n Список пуст, запись будет осуществлена в начало\n\n ");
		system("pause");
		list = add_first(list);
	}
	else
	{
		int n = get_n(amt(list), "Введите номер позиции, в которую следует добавить запись", "add");

		if (n == 1)
			list = add_first(list);
		else
			if (n == amt(list) + 1)
				list = add_last(list);
			else
			{
				NODE* nta = fill_fields();
				NODE *tmp = list;
				int i;
				for (i = 1; i < n - 1; i++)
					tmp = tmp->next;
				nta->next = tmp->next;
				tmp->next->prev = nta;
				nta->prev = tmp;
				tmp->next = nta;

				printf_s("\n Новая запись была добавлена в позицию № %d списка\n\n ", n);
				system("pause");
			}
	}
	return list;
}

//добавление узла в конец
NODE* add_last(NODE* list)
{
	if (!list)
		list = add_first(list);
	else
	{
		NODE* nta = fill_fields();
		NODE* tmp = list;

		while (tmp->next)
			tmp = tmp->next;
		tmp->next = nta;
		nta->prev = tmp;
		nta->next = NULL;

		printf_s("\n Новая запись была добавлена в конец списка\n\n ");
		system("pause");
	}

	return list;
}

//заполнение информационных полей
NODE* fill_fields()
{
	NODE* tmp = (NODE*)malloc(sizeof(NODE));     //вспомогательная переменная (узел)
	if (!tmp)
	{
		printf_s("\n Ошибка выделения памяти\n\n ");
		system("pause");
	}
	else
		tmp->data = (DATA*)malloc(sizeof(DATA)); //вспомогательная переменная (структура с информационными полями)
	if (!(tmp->data))
	{
		printf_s("\n Ошибка выделения памяти\n\n ");
		system("pause");
	}
	else
	{
		tmp->data->artist = copy_string(string_input("ЗАПОЛНЕНИЕ ПОЛЯ ИСПОЛНИТЕЛЬ", "Исполнитель"));

		tmp->data->album = copy_string(string_input("ЗАПОЛНЕНИЕ ПОЛЯ АЛЬБОМ", "Альбом"));

		tmp->data->year = year_input("ЗАПОЛНЕНИЕ ПОЛЯ ГОД");

		tmp->data->price = price_input("ЗАПОЛНЕНИЕ ПОЛЯ ЦЕНА");

		system("cls");
		printf_s("\n ВВЕДЕННЫЕ ДАННЫЕ\n\n");
		printf_s(" %s - %s - %d г. - %.2f USD \n", tmp->data->artist, tmp->data->album, tmp->data->year, tmp->data->price);
	}
	return tmp;
}

// ввод строк
char* string_input(char* header, char* inputitem)
{
	char *tmp;       //временная переменная (вводимая строка)
	char rec;        // переменная хранящая вводимый символ
	int i = 0;       // вспомогательный индекс
	int stop = 0;    // маркер корректности и прекращения ввода
	int correct = 0; // маркер подтверждения корректности ввода со стороны пользователя

	do
	{
		tmp = NULL;  // временная переменная для хранения введенной строки

		do
		{
			do
			{
				system("cls");
				rewind(stdin);
				printf_s("\n Минимальное количество вводимых символов - %d", MIN_STRING_LENGTH);
				printf_s("\n Максимальное количество вводимых символов - %d", MAX_STRING_LENGTH);
				printf_s("\n Ввод всех символов свыше первых %d будет проигнорирован", MAX_STRING_LENGTH);
				printf_s("\n Последовательный ряд знаков пунктуации будет заменен 1-м знаком в данном ряду");
				printf_s("\n Начало ввода с пробела, знаков пунктуации или нажатия Enter недопустимо");
				printf_s("\n Для завершения ввода нажмите Enter\n\n");
				printf_s("\n %s", header);
				printf_s("\n\n %s: ", inputitem);

				// ввод и проверка корректности ввода первого символа строки

				rec = getchar();

				if (punctuation(rec) || rec == '\n' || rec == ' ' || rec == '\t')
				{
					system("cls");
					printf_s("\n ОШИБКА.\n\n Не начинайте ввод с пробелов, знаков пунктуации или нажатия Enter\n\n ");
					system("pause");
				}
				else
				{
					tmp = (char*)malloc(sizeof(char*));
					*tmp = toupper(rec);
					i = 1;
				}
			} while (punctuation(rec) || rec == '\n' || rec == ' ' || rec == '\t');

			// ввод последующих символов

			while ((rec = getchar()) != '\n' && i < MAX_STRING_LENGTH)
			{
				// замена табуляции пробелом

				if (rec == '\t')
					rec = ' ';

				// пропуск избыточных знаков препинания и пробелов

				if (((punctuation(rec)) && punctuation(tmp[i - 1])) || (rec == ' ' && tmp[i - 1] == ' '))
					continue;
				else
				{
					tmp = (char*)realloc(tmp, (i + 1)*sizeof(char));

					if (tmp[i - 1] == ' ') // если перед символом пробел
					{
						tmp[i++] = toupper(rec); // ввод с заглавной буквы

						if (i >= MAX_STRING_LENGTH)
						{
							printf_s("\n Длина строки достигла лимита в %d символов", MAX_STRING_LENGTH);
							printf_s("\n Все введенные символы, свыше первых %d будут проигнорированны\n\n ", MAX_STRING_LENGTH);
							system("pause");
						}
					}
					else
					{
						tmp[i++] = tolower(rec); // ввод прописных букв, в случае если перед символом не стоит пробел

						if (i >= MAX_STRING_LENGTH)
						{
							printf_s("\n Длина строки достигла лимита в %d символов. Строка будет обрезана\n\n ", MAX_STRING_LENGTH);
							system("pause");
						}
					}
				}
			}

			if (*(tmp + i - 1) == ' ') //если последний символ пробел
				i--;
			else
				tmp = (char*)realloc(tmp, (i + 1)*sizeof(char)); //выделение памяти под символ конца строки

			*(tmp + i) = '\0'; //конец строки

			if (i < MIN_STRING_LENGTH) //если введено менее 2 символов
			{
				system("cls");
				printf_s("\n ОШИБКА \n\n Введите более %d символов\n\n ", MIN_STRING_LENGTH);
				system("pause");
			}
			else
				stop = 1; // ввод корректен
		} while (!stop);

		// подтверждение точности ввода данных со стороны пользователя
		do
		{
			system("cls");
			printf_s("\n %s\n\n", header);
			printf_s("\n Проверьте введенные данные: %s", tmp);
			printf_s("\n\n Исправить введенные данные?\n\n 1 - Нет\n 0 - Да");
			correct = userchoice();

			if (correct < 0 || correct > 1)
			{
				system("cls");
				printf_s("\n ОШИБКА\n");
				printf_s("\n Введите существующий пункт\n\n ");
				system("pause");
			}

		} while (correct < 0 || correct > 1);

	} while (!correct); // пока пользователь не подвердит точность введенных данных

	return tmp;
}

// ввод цены
float price_input(char* header)
{
	float price = -1; //цена
	int correct = 0;  //маркер корректности ввода

	do
	{
		do
		{
			system("cls");
			rewind(stdin);
			printf_s("\n Допустимый диапазон значений с %d до %d USD", MIN_PRICE, MAX_PRICE);
			printf_s("\n Ввод осуществляется только арабскими цифрами (0-9)\n ");
			printf_s("\n Целая и дробная части разделяются запятой. В ином случае дробная часть обнуляется");
			printf_s("\n Для завершения ввода нажмите Enter\n\n");
			printf_s("\n %s\n", header);
			printf_s("\n Введите цену: ");

			if (!(scanf_s("%f", &price)))
			{
				system("cls");
				printf_s("\n ОШИБКА.\n\n Ввод осуществляется только арабскими цифрами (0-9)\n\n ");
				system("pause");
				price = -1;
			}
			else
				if (price < MIN_PRICE || price > MAX_PRICE)
				{
					system("cls");
					printf_s("\n ОШИБКА.\n\n Допустимый диапазон значений с %d до %d USD\n\n ", MIN_PRICE, MAX_PRICE);
					system("pause");
					price = -1;
				}
		} while (price < 0);

		do
		{
			system("cls");
			printf_s("\n %s\n\n", header);
			printf_s("\n Проверьте введенные данные: %.2f", price);
			printf_s("\n\n Исправить введенные данные?\n\n 1 - Нет\n 0 - Да");
			correct = userchoice();

			if (correct < 0 || correct > 1)
			{
				system("cls");
				printf_s("\n ОШИБКА\n");
				printf_s("\n Введите существующий пункт\n\n ");
				system("pause");
			}

		} while (correct < 0 || correct > 1);

	} while (!correct);

	return price;
}

// ввод года
int year_input(char* header)
{
	int year = -1;   //год
	int correct = 0; //маркер корректности ввода

	do
	{
		do
		{
			system("cls");
			rewind(stdin);
			printf_s("\n Допустимый диапазон значений с %d по %d год", MIN_YEAR, MAX_YEAR);
			printf_s("\n Ввод осуществляется только арабскими цифрами (0-9)\n");
			printf_s("\n Для завершения ввода нажмите Enter\n\n");
			printf_s("\n %s\n", header);
			printf_s("\n Введите год: ");

			if (!(scanf_s("%d", &year)))
			{
				system("cls");
				printf_s("\n ОШИБКА.\n\n Ввод осуществляется только арабскими цифрами (0-9)\n\n ");
				system("pause");
				year = -1;
			}
			else
				if (year < MIN_YEAR || year > MAX_YEAR)
				{
					system("cls");
					printf_s("\n ОШИБКА.\n\n Допустимый диапазон значений с %d по %d год\n\n ", MIN_YEAR, MAX_YEAR);
					system("pause");
					year = -1;
				}
		} while (year < 0);

		do
		{
			system("cls");
			printf_s("\n %s\n\n", header);
			printf_s("\n Проверьте введенные данные: %d", year);
			printf_s("\n\n Исправить введенные данные?\n\n 1 - Нет\n 0 - Да");
			correct = userchoice();

			if (correct < 0 || correct > 1)
			{
				system("cls");
				printf_s("\n ОШИБКА\n");
				printf_s("\n Введите существующий пункт\n\n ");
				system("pause");
			}

		} while (correct < 0 || correct > 1);

	} while (!correct);

	return year;
}

//копирование строк
char* copy_string(char* original)
{
	char *tmp = NULL; //временная переменная(копия строки)
	unsigned int i;   //индекс

	tmp = (char*)malloc((strlen(original) + 1)*sizeof(char));

	for (i = 0; i < strlen(original); i++) //посимвольное копривование строки в новую переменную
		tmp[i] = original[i];

	tmp[i] = '\0';

	return tmp;
}

//проверка на принадлежность символа к знакам пунктуации
int punctuation(char symbol)
{
	const char pmarks[] = "`'%!,.?;:)(-_=+\"}{][><*&^#@\\/|"; //строка-константа с знаками пунктуации
	int i = 0; //индекс
	int yes = 0; //маркер принадлежности символа к знакам пунктуации

	while (*(pmarks + i) != '\0' && !yes)
	{
		if (symbol == *(pmarks + i))
			yes = 1;
		i++;
	}
	return yes;
}

//количество узлов в списке
int amt(NODE* list)
{
	NODE* tmp = list; //указатель на текущий узел
	int amt = 0;      //количество узлов

	if (tmp)
	{
		do
		{
			amt++;
			tmp = tmp->next;
		} while (tmp);
	}

	return amt;
}

//ввод вспомогат. переменной
int get_n(int amount, char* inputitem, char* s)

{
	system("cls");

	int n; //переменная хранящая вводимый номер записи (узла)

	do
	{
		system("cls");

		printf_s("\n ВСЕГО ЗАПИСЕЙ  - %d\n", amount);

		if (s == "out")
			printf_s("\n Введите число от 1 до %d\n", amount);
		else
			printf_s("\n Введите число от 1 до %d\n", amount + 1);

		printf_s("\n %s: ", inputitem);

		if (!scanf_s("%d", &n))
			n = 0;
		if (!n || (n > amount && s == "out") || (n > amount + 1 && s == "add"))
		{
			system("cls");
			if (s == "out")
				printf_s("\n ОШИБКА.\n Введите число в диапазоне от 1 до %d\n\n ", amount);
			else
				printf_s("\n ОШИБКА.\n Введите число в диапазоне от 1 до %d\n\n ", amount + 1);
			system("pause");
		}
	} while (n < 1 || (n > amount && s == "out") || (n > amount + 1 && s == "add"));

	return n;
}

//вывод в консоль
void cnsl_output(NODE* list)
{
	system("cls");
	int i = 0;
	int n = get_n(amt(list), "Введите количество записей, выводимых на одной странице", "out");

	while (list)
	{
		if (!(i % n))
		{
			if (i && list)
			{
				printf_s("\n Далее - нажмите Enter");
				rewind(stdin);
				getchar();
			}

			system("cls");
			printf_s("\n-------------------------------------------------------------------------------- \n");
			printf_s(" | %3s | %20s | %20s | %6s | %10s, USD |", "№", "Исполнитель", "Альбом", "Год", "Цена");
			printf_s("\n-------------------------------------------------------------------------------- \n");
		}
		printf_s(" | %3d | %20s | %20s | %6d |      %10.2f |", (i++) + 1, list->data->artist, list->data->album, list->data->year, list->data->price);
		printf_s("\n-------------------------------------------------------------------------------- \n");
		list = list->next;
	}
	printf_s("\n Возврат в меню - нажмите Enter");
	rewind(stdin);
	getchar();
}

//меню
int menu(NODE* list)
{
	system("cls");

	if (list)
	{
		printf_s("\n На данный момент записей в списке: %d\n", amt(list));
		printf_s("\n МЕНЮ\n\n");
		puts(" 1 - Справка");
		puts(" 2 - Заполнение списка");
		puts(" 3 - Вывести список");
		puts(" 4 - Очистить список");
		puts(" 0 - Выход");
	}
	else
	{
		printf_s("\n На данный момент список пуст\n");
		printf_s("\n МЕНЮ\n\n");
		puts(" 1 - Справка");
		puts(" 2 - Заполнение списка");
		puts(" 0 - Выход");
	}

	return(userchoice());
}

//добавление записей из файла (вот где-то здесь ошибка, как мне кажется)
NODE* read_from_file(NODE* list, char* fn)
{
	FILE* flist = NULL; //файл
	errno_t err; //это нужно чтобы использовать fopen_s вместо fopen
	NODE* tmp = NULL;//новый узел

	err = fopen_s(&flist, fn, "r"); //открытие файла для чтения

	if (err)
	{
		printf_s("\n Невозможно открыть для чтения файл %s \n ", fn);
		system("pause");
	}
	else
	{
		int uc;

		if (!list) //если список пуст добавление в начало
			uc = 1;
		else //иначе предоставляется выбор куда добавлять
			do
			{
				system("cls");
				printf_s("\n Куда следует добавить записи:\n\n");
				puts(" 1 - В начало");
				puts(" 2 - В конец");

				uc = userchoice();

				if (uc < 1 || uc > 2)
				{
					system("cls");
					printf_s("\n ОШИБКА\n");
					printf_s("\n Введите существующий пункт\n\n ");
					system("pause");
				}
			} while (uc < 1 || uc > 2);

			while (!feof(flist)) //пока не конец файла
			{
				rewind(stdin);
				int i = 0; //индекс считываемой из файла строки
				char str[140]; //считываемая строка
				fgets(str, 140, flist); //считывание строки (wow!)

				if (str[i] != ' ' && str[i + 1] != '-') //если строка не начинается с пробела и при этом за ним не идет символ "-"
				{
					tmp = read_to_node(str); //заполнение информационных полей нового узла данными из строки

					if (uc == 1) //добавление в начало
					{
						tmp->next = list;
						if (list)
							list->prev = tmp;
						tmp->prev = NULL;
						list = tmp;
					}
					else //добавление в конец
					{
						NODE* current = list; //указатель на начало списка
						while (current->next)
							current = current->next;
						current->next = tmp;
						tmp->prev = current;
						tmp->next = NULL;
					}
				}
			}
			err = fclose(flist);

			return list;
	}
}

//заполнение информационных полей узла данными из считанной строки
NODE* read_to_node(char*str)
{
	NODE* tmp = (NODE*)malloc(sizeof(NODE));
	tmp->data = (DATA*)malloc(sizeof(NODE));

	char* artist = NULL; //исполнитель
	char* album = NULL; //альбом
	int year = NULL; //год
	float price; //цена

	int i = 0; //индекс строки

	artist = str_read(str, &i); //здесь в общем возвращает строку из ячейки исполнитель
	if (artist)
	{
		tmp->data->artist = copy_string(artist); //присваивание полученного значения исполнителя

		album = str_read(str, &i); //здесь возвращает строку из ячейки альбом (дольше все по аналогии)
		if (album)
		{
			tmp->data->album = copy_string(album);

			year = atoi(str_read(str, &i)); //получает год
			if (year)
			{
				if (year < MIN_YEAR || year > MAX_YEAR)
					tmp->data->year = 0;
				else
					tmp->data->year = year;
			}
			else
				tmp->data->year = 0;

			price = strtof(str_read(str, &i), '\0'); //получает цену
			if (price)
			{
				if (price < MIN_PRICE || price > MAX_PRICE)
				{
					float f = 0.0;
					tmp->data->price = f;
				}
				else
					tmp->data->price = price;

				return tmp; //и если все поля заполнены без критических ошибок возвращает узел
			}
			else
				return NULL;
		}
		else
			return NULL;
	}
	else
		return NULL;
}

//коррекция считанной строки из файла
char* str_read(char* str, int* i)
{
	char* tmp = NULL; //хранит строку с нужным значением
	int l = *i; //индекс считанной строки
	int j = 0; //индекс строки с нужным значением

	while (str[l] == ' ' || punctuation(str[l]) && str[l] != '\0')
		l++;
	if (str[l] == '\0')
		return NULL;
	else
	{
		while (str[l] != ' ' && j < MAX_STRING_LENGTH)
		{
			if (punctuation(str[l]) && punctuation(str[l + 1]))
				l++;
			else
			{
				tmp = (char*)realloc(tmp, (j + 1)*sizeof(char));
				tmp[j++] = str[l++];
			}
		}

		if (j == MAX_STRING_LENGTH)
			while (str[l] != '|')
				++l;

		if (str[l] == ' ' && str[l + 1] != '|')
		{
			if (j != MAX_STRING_LENGTH - 1)
			{
				tmp = (char*)realloc(tmp, (j + 1)*sizeof(char));
				tmp[j++] = str[l++];

				while (str[l] == ' ' && str[l] != '\0')
					l++;
				if (str[l] == '\0')
					return NULL;
				else
				{
					while (str[l] != ' ' && j < MAX_STRING_LENGTH)
					{
						if (punctuation(str[l]) && punctuation(str[l + 1]))
							i++;
						else
						{
							tmp = (char*)realloc(tmp, (j + 1)*sizeof(char));
							tmp[j++] = str[l++];
						}
					}

					if (j == MAX_STRING_LENGTH)
						while (str[l] != '|')
							++l;
				}
			}
		}

		if (j < MIN_STRING_LENGTH)
		{
			tmp = NULL;
			tmp = (char*)malloc(sizeof("0\0"));
			tmp = "0\0";
		}
		else
		{
			tmp = (char*)realloc(tmp, (j + 1)*sizeof(char));
			tmp[j] = '\0';
		}

		*i = l;

		return tmp;
	}
}

//вывод в файл
void write_to_file(NODE* list, char* fn)
{
	int i = 0; //индекс количества записей
	int uc;
	FILE* flist = NULL;
	errno_t err;
	err = fopen_s(&flist, fn, "w");


	if (err)
	{
		printf_s("\n Невозможно открыть файл %s для записи\n ", fn);
		system("pause");
		return;
	}
	else
	{
		do
		{
			system("cls");
			printf_s("\n СОХРАНЕНИЕ СПИСКА В ФАЙЛ\n\n");
			puts(" 1 - Сохранить файл только для чтения");
			puts(" 2 - Сохранить файл, пригодный для загрузки в программу");
			puts(" 0 - Отмена");
			uc = userchoice();

			if (uc < 0 || uc > 2)
			{
				system("cls");
				printf_s("\n ОШИБКА\n");
				printf_s("\n Введите существующий пункт\n\n ");
				system("pause");
			}
		} while (uc < 0 || uc > 2);

		if (!uc)
			return;
		if (uc == 1)
		{
			fprintf_s(flist, "%s", "\n -------------------------------------------------------------------------------- \n");
			fprintf_s(flist, " | %3s | %20s | %20s | %6s | %10s, USD |", "№", "Исполнитель", "Альбом", "Год", "Цена");
			fprintf_s(flist, "%s", "\n -------------------------------------------------------------------------------- \n");

			while (list)
			{
				fprintf_s(flist, " | %3d | %20s | %20s | %6d |      %10.2f |", (i++) + 1, list->data->artist, list->data->album, list->data->year, list->data->price);
				fprintf_s(flist, "%s", "\n -------------------------------------------------------------------------------- \n");
				list = list->next;
			}
		}

		if (uc == 2)
		{
			fprintf_s(flist, "%s", " -------------------------------------------------------------------------- \n");

			while (list)
			{
				fprintf_s(flist, " | %20s | %20s | %6d |      %10.2f |", list->data->artist, list->data->album, list->data->year, list->data->price);
				fprintf_s(flist, "%s", "\n -------------------------------------------------------------------------- \n");
				list = list->next;
			}
		}
		printf_s("\n Запись закончена");
	}
	err = fclose(flist);
}

//доп справка 
int file_read_help()
{
	system("cls");
	printf_s("\n ДОБАВЛЕНИЕ ЗАПИСЕЙ ИЗ ФАЙЛА\n");
	printf_s("\n Содержимое файла должно соответствовать общим критериям ввода данных\n\n");
	printf_s("\n Для полей Исполнитель и Альбом:\n");
	printf_s("\n Минимальное количество символов  - %d", MIN_STRING_LENGTH);
	printf_s("\n Максимальное количество  - %d", MAX_STRING_LENGTH);
	printf_s("\n Все символы свыше первых %d будут проигнорированы", MAX_STRING_LENGTH);
	printf_s("\n Последовательный ряд знаков пунктуации будет заменен 1-м знаком в данном ряду");
	printf_s("\n Последовательный ряд пробелов будет заменен 1-м пробелом");
	printf_s("\n Знаки пунктуации в начале строки будут проигнорированы\n");
	printf_s("\n Для полей Год Издания и Цена:\n");
	printf_s("\n Допустимый диапазон значений цены с %d до %d USD", MIN_PRICE, MAX_PRICE);
	printf_s("\n Целая и дробная части разделяются запятой. В ином случае дробная часть обнуляется");
	printf_s("\n Допустимый диапазон значений года издания с %d по %d год", MIN_YEAR, MAX_YEAR);
	printf_s("\n В случае, если цена или год издания не попадают в данный диапазон, значение будет замененно 0");

	printf_s("\n\n Продолжить - 1");
	printf_s("\n Отмена - 0");

	return(userchoice());
}

//ввод имени/расположения файла
char* get_file_name(char* header)
{
	int uc;

	do
	{
		system("cls");
		printf_s("\n%s\n", header);
		printf_s("\n Осуществить данную операцию:");
		printf_s("\n 1 - Используя демо-файл");
		printf_s("\n 2 - Ввести расположение файла");

		uc = userchoice();

		if (uc < 1 || uc > 2)
		{
			system("cls");
			printf_s("\n ОШИБКА\n");
			printf_s("\n Введите существующий пункт\n\n ");
			system("pause");
		}
	} while (uc < 1 || uc > 2);

	if (uc == 1)
		return "demo.txt";
	else
	{
		int correct = 0;
		char *tmp = NULL;

		do
		{

			system("cls");
			printf_s("\n Формат ввода расположения файла:\n\n");
			printf_s("\n ДИСК:\\путь\\имя_файла.txt\n");
			printf_s("\n Ввод завершается нажатием клавиши Enter");

			char rec;
			int i = 0;

			while ((rec = getchar()) != '\n')
			{
				tmp = (char*)realloc(tmp, (i + 1)*sizeof(char));
				*(tmp + (i++)) = rec;
			}
			tmp = (char*)realloc(tmp, (i + 1)*sizeof(char));
			*(tmp + i) = '\0';

			do
			{
				system("cls");
				printf_s("\n Вы ввели: %s\n ", tmp);
				printf_s("\n 1 - Это верное расположение файла");
				printf_s("\n 0 - Ввести расположение файла заново");

				correct = userchoice();

				if (correct < 0 || correct > 1)
				{
					system("cls");
					printf_s("\n ОШИБКА\n");
					printf_s("\n Введите существующий пункт\n\n ");
					system("pause");
				}
			} while (correct < 0 || correct > 1);
		} while (!correct);

		return tmp;
	}
}

//освобождение паямяти из-под списка (вот эта функция выдает ошибку, после использования той, что была отмеченна выше)
NODE* free_ll(NODE*list)
{
	NODE* tmp = list;  //указатель на текущий узел
	NODE* next = NULL; //указатель на узел, следующий за текущим

	while (tmp)
	{
		next = tmp->next;
		tmp = free_node(tmp);
		tmp = next;
	}
	return NULL;
}

//из-под узла
NODE* free_node(NODE*tmp)
{
	free(tmp->data->artist);
	free(tmp->data->album);
	free(tmp->data);
	tmp->data = NULL;
	if (tmp->next)
		tmp->next = NULL;
	if (tmp->prev)
		tmp->prev = NULL;
	free(tmp);
	return NULL;
}