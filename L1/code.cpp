// files

#include  <stdio.h>
#include  <Windows.h>
#include  <string.h>
#include <malloc.h>
#include <locale.h>

#define MIN_STRING_LENGTH 2  //����������� ����� ������
#define MAX_STRING_LENGTH 20 //������������ ����� ������
#define MIN_YEAR 1869        //����������� �������� ����
#define MAX_YEAR 2016        //������������ �������� ����
#define MIN_PRICE 1          //����������� ����
#define MAX_PRICE 200000     //������������ ����

typedef struct
{
	char* artist; //�����������
	char* album;  //������
	int year;     //��� �������
	float price;  //����
}DATA; //��������� � ��������������� ������

typedef struct node
{
	DATA* data; //��������� � ��������������� ������
	node* next; //��������� �� ��������� ����
	node* prev; //��������� �� ���������� ����
}NODE; //����

int userchoice();                                     //����� ������ ����
NODE* add(NODE*);                                     //���� ���������� �����
NODE* add_first(NODE*);                               //���������� ���� � ������
NODE* add_n(NODE*);                                   //���������� n-��� ����
NODE* add_last(NODE*);                                //���������� ���� � �����
void cnsl_output(NODE*);                              //����� � �������
int get_n(int, char*, char*);                         //���� ��������������� ���������� (���-�� ��������� �������, ����� ���������� ���� ���)
NODE* fill_fields();                                  //���������� �������������� �����
char* string_input(char* header, char* inputitem);    //���� �����
float price_input(char* header);                      //���� ����
int year_input(char* header);                         //���� ����
char* copy_string(char* original);                    //����� ������
int amt(NODE* list);                                  //���������� ����� � ������
int punctuation(char symbol);                         //�������� ������� �� �������������� � ������ ����������
int menu(NODE*);                                      //����
NODE* read_from_file(NODE*, char*);                   //���������� ������� �� �����
NODE* read_to_node(char*);                            //���������� ��������������� ���� ���� ������� �� �����
char* str_read(char *str, int *i);                    //��������� ��������� ������
void write_to_file(NODE*, char*);                     //����� ������ � ����
int file_read_help();                                 //������� �� ���������� ������� �� �����
char* get_file_name(char*);                           //���� ������������/����� �����
NODE* free_node(NODE*tmp);                            //������������ ������ ��-��� ������
NODE* free_ll(NODE*list);                             //������������ ������ ��-��� ����

int main()
{
	setlocale(0, "");
	SetConsoleCP(1251);
	SetConsoleOutputCP(1251);

	NODE* list = NULL; //������
	int uc;//����� ������������
	int uc2;//����� ������������ - 2

	do
	{
		uc = menu(list); //����� ����

		switch (uc)
		{
		case 1: //��� ����� �������
			break;
		case 2: //���������� �����
			do
			{
				system("cls");
				printf_s("\n ���������� ������\n\n");
				puts(" 1 - �������� ������ �������");
				puts(" 2 - �������� ������ �� �����");
				puts(" 0 - ��������� � ������� ����");

				uc2 = userchoice();

				switch (uc2)
				{
				case 1: //���� ���������� ������� � ����������
					list = add(list);
					break;
				case 2: //���������� �� �����
				{
					int cont = file_read_help(); //������� �� ���������� ������� �� �����
					if (cont) //���� ����������� ��� �� ����� �������� ������ �� �����
					{
						char* fn = get_file_name("���������� ������� �� �����"); //���� ����� �����
						list = read_from_file(list, fn); //���������� �������
						system("pause");
					}
					break;
				}

				case 0: //������
					break;
				default:
					system("cls");
					printf_s("\n ������\n");
					printf_s("\n ������� ������������ �����\n\n ");
					system("pause");
				}
			} while (uc2 && uc2 < 0 || uc2 > 2);
			break;
		case 3: //����� ������
			if (list)
			{
				do
				{
					system("cls");

					printf_s("\n ����� ������\n\n");
					puts(" 1 - �� �����");
					puts(" 2 - ��������� � ����");
					puts(" 0 - ��������� � ������� ����");

					uc2 = userchoice();

					switch (uc2)
					{
					case 1: //����� � �������
						cnsl_output(list);
						break;
					case 2: //����� � ����
					{
						char* fn = get_file_name("���������� ������ � ����"); //���� ����� �����
						write_to_file(list, fn); //����� � ����
						system("pause");
						break;
					}
					case 0: //������
						break;
					default:
						system("cls");
						printf_s("\n ������\n");
						printf_s("\n ������� ������������ �����\n\n ");
						system("pause");
						break;
					}
				} while (uc2 && uc2 < 0 || uc2 > 2);
			}
			else
			{
				system("cls");
				printf_s("\n ������\n");
				printf_s("\n ������� ������������ �����\n\n ");
				system("pause");
			}
			break;
		case 4://�������� ������
			if (list)
				list = free_ll(list);
			else
			{
				system("cls");
				printf_s("\n ������\n");
				printf_s("\n ������� ������������ �����\n\n ");
				system("pause");
			}
			break;
		case 0: //�����
			if (list)
				list = free_ll(list);
			break;
		default:
			system("cls");
			printf_s("\n ������\n");
			printf_s("\n ������� ������������ �����\n\n ");
			system("pause");
		}
	} while (uc);
	return 0;
}

// ���� ���������� ������ ����
int userchoice()
{
	int uc; //����� ������������
	printf_s("\n\n �����: ");
	rewind(stdin);
	scanf_s("%d", &uc);
	return uc;
}

//���� ���������� ����� � ����������
NODE* add(NODE* list)
{
	int uc;

	do
	{
		system("cls");

		printf_s("\n ���������� ������ �������\n\n");
		puts(" 1 - � ������ ������");
		puts(" 2 - � ������������ �������");
		puts(" 3 - � ����� ������");
		puts(" 0 - �����");

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
			printf_s("\n ������\n");
			printf_s("\n ������� ������������ �����\n\n ");
			system("pause");
			break;
		}
	} while (uc && uc < 0 || uc > 3);

	return list;
}

//���������� ���� � ������
NODE* add_first(NODE* list)
{
	NODE* nta = fill_fields();
	nta->next = list;
	if (list)
		list->prev = nta;
	nta->prev = NULL;

	printf_s("\n ����� ������ ���� ��������� � ������ ������\n\n ");
	system("pause");
	return nta;
}

//���������� ���� � �-��� �������
NODE* add_n(NODE* list)
{
	if (!list)
	{
		system("cls");
		printf_s("\n ������ ����, ������ ����� ������������ � ������\n\n ");
		system("pause");
		list = add_first(list);
	}
	else
	{
		int n = get_n(amt(list), "������� ����� �������, � ������� ������� �������� ������", "add");

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

				printf_s("\n ����� ������ ���� ��������� � ������� � %d ������\n\n ", n);
				system("pause");
			}
	}
	return list;
}

//���������� ���� � �����
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

		printf_s("\n ����� ������ ���� ��������� � ����� ������\n\n ");
		system("pause");
	}

	return list;
}

//���������� �������������� �����
NODE* fill_fields()
{
	NODE* tmp = (NODE*)malloc(sizeof(NODE));     //��������������� ���������� (����)
	if (!tmp)
	{
		printf_s("\n ������ ��������� ������\n\n ");
		system("pause");
	}
	else
		tmp->data = (DATA*)malloc(sizeof(DATA)); //��������������� ���������� (��������� � ��������������� ������)
	if (!(tmp->data))
	{
		printf_s("\n ������ ��������� ������\n\n ");
		system("pause");
	}
	else
	{
		tmp->data->artist = copy_string(string_input("���������� ���� �����������", "�����������"));

		tmp->data->album = copy_string(string_input("���������� ���� ������", "������"));

		tmp->data->year = year_input("���������� ���� ���");

		tmp->data->price = price_input("���������� ���� ����");

		system("cls");
		printf_s("\n ��������� ������\n\n");
		printf_s(" %s - %s - %d �. - %.2f USD \n", tmp->data->artist, tmp->data->album, tmp->data->year, tmp->data->price);
	}
	return tmp;
}

// ���� �����
char* string_input(char* header, char* inputitem)
{
	char *tmp;       //��������� ���������� (�������� ������)
	char rec;        // ���������� �������� �������� ������
	int i = 0;       // ��������������� ������
	int stop = 0;    // ������ ������������ � ����������� �����
	int correct = 0; // ������ ������������� ������������ ����� �� ������� ������������

	do
	{
		tmp = NULL;  // ��������� ���������� ��� �������� ��������� ������

		do
		{
			do
			{
				system("cls");
				rewind(stdin);
				printf_s("\n ����������� ���������� �������� �������� - %d", MIN_STRING_LENGTH);
				printf_s("\n ������������ ���������� �������� �������� - %d", MAX_STRING_LENGTH);
				printf_s("\n ���� ���� �������� ����� ������ %d ����� ��������������", MAX_STRING_LENGTH);
				printf_s("\n ���������������� ��� ������ ���������� ����� ������� 1-� ������ � ������ ����");
				printf_s("\n ������ ����� � �������, ������ ���������� ��� ������� Enter �����������");
				printf_s("\n ��� ���������� ����� ������� Enter\n\n");
				printf_s("\n %s", header);
				printf_s("\n\n %s: ", inputitem);

				// ���� � �������� ������������ ����� ������� ������� ������

				rec = getchar();

				if (punctuation(rec) || rec == '\n' || rec == ' ' || rec == '\t')
				{
					system("cls");
					printf_s("\n ������.\n\n �� ��������� ���� � ��������, ������ ���������� ��� ������� Enter\n\n ");
					system("pause");
				}
				else
				{
					tmp = (char*)malloc(sizeof(char*));
					*tmp = toupper(rec);
					i = 1;
				}
			} while (punctuation(rec) || rec == '\n' || rec == ' ' || rec == '\t');

			// ���� ����������� ��������

			while ((rec = getchar()) != '\n' && i < MAX_STRING_LENGTH)
			{
				// ������ ��������� ��������

				if (rec == '\t')
					rec = ' ';

				// ������� ���������� ������ ���������� � ��������

				if (((punctuation(rec)) && punctuation(tmp[i - 1])) || (rec == ' ' && tmp[i - 1] == ' '))
					continue;
				else
				{
					tmp = (char*)realloc(tmp, (i + 1)*sizeof(char));

					if (tmp[i - 1] == ' ') // ���� ����� �������� ������
					{
						tmp[i++] = toupper(rec); // ���� � ��������� �����

						if (i >= MAX_STRING_LENGTH)
						{
							printf_s("\n ����� ������ �������� ������ � %d ��������", MAX_STRING_LENGTH);
							printf_s("\n ��� ��������� �������, ����� ������ %d ����� ����������������\n\n ", MAX_STRING_LENGTH);
							system("pause");
						}
					}
					else
					{
						tmp[i++] = tolower(rec); // ���� ��������� ����, � ������ ���� ����� �������� �� ����� ������

						if (i >= MAX_STRING_LENGTH)
						{
							printf_s("\n ����� ������ �������� ������ � %d ��������. ������ ����� ��������\n\n ", MAX_STRING_LENGTH);
							system("pause");
						}
					}
				}
			}

			if (*(tmp + i - 1) == ' ') //���� ��������� ������ ������
				i--;
			else
				tmp = (char*)realloc(tmp, (i + 1)*sizeof(char)); //��������� ������ ��� ������ ����� ������

			*(tmp + i) = '\0'; //����� ������

			if (i < MIN_STRING_LENGTH) //���� ������� ����� 2 ��������
			{
				system("cls");
				printf_s("\n ������ \n\n ������� ����� %d ��������\n\n ", MIN_STRING_LENGTH);
				system("pause");
			}
			else
				stop = 1; // ���� ���������
		} while (!stop);

		// ������������� �������� ����� ������ �� ������� ������������
		do
		{
			system("cls");
			printf_s("\n %s\n\n", header);
			printf_s("\n ��������� ��������� ������: %s", tmp);
			printf_s("\n\n ��������� ��������� ������?\n\n 1 - ���\n 0 - ��");
			correct = userchoice();

			if (correct < 0 || correct > 1)
			{
				system("cls");
				printf_s("\n ������\n");
				printf_s("\n ������� ������������ �����\n\n ");
				system("pause");
			}

		} while (correct < 0 || correct > 1);

	} while (!correct); // ���� ������������ �� ��������� �������� ��������� ������

	return tmp;
}

// ���� ����
float price_input(char* header)
{
	float price = -1; //����
	int correct = 0;  //������ ������������ �����

	do
	{
		do
		{
			system("cls");
			rewind(stdin);
			printf_s("\n ���������� �������� �������� � %d �� %d USD", MIN_PRICE, MAX_PRICE);
			printf_s("\n ���� �������������� ������ ��������� ������� (0-9)\n ");
			printf_s("\n ����� � ������� ����� ����������� �������. � ���� ������ ������� ����� ����������");
			printf_s("\n ��� ���������� ����� ������� Enter\n\n");
			printf_s("\n %s\n", header);
			printf_s("\n ������� ����: ");

			if (!(scanf_s("%f", &price)))
			{
				system("cls");
				printf_s("\n ������.\n\n ���� �������������� ������ ��������� ������� (0-9)\n\n ");
				system("pause");
				price = -1;
			}
			else
				if (price < MIN_PRICE || price > MAX_PRICE)
				{
					system("cls");
					printf_s("\n ������.\n\n ���������� �������� �������� � %d �� %d USD\n\n ", MIN_PRICE, MAX_PRICE);
					system("pause");
					price = -1;
				}
		} while (price < 0);

		do
		{
			system("cls");
			printf_s("\n %s\n\n", header);
			printf_s("\n ��������� ��������� ������: %.2f", price);
			printf_s("\n\n ��������� ��������� ������?\n\n 1 - ���\n 0 - ��");
			correct = userchoice();

			if (correct < 0 || correct > 1)
			{
				system("cls");
				printf_s("\n ������\n");
				printf_s("\n ������� ������������ �����\n\n ");
				system("pause");
			}

		} while (correct < 0 || correct > 1);

	} while (!correct);

	return price;
}

// ���� ����
int year_input(char* header)
{
	int year = -1;   //���
	int correct = 0; //������ ������������ �����

	do
	{
		do
		{
			system("cls");
			rewind(stdin);
			printf_s("\n ���������� �������� �������� � %d �� %d ���", MIN_YEAR, MAX_YEAR);
			printf_s("\n ���� �������������� ������ ��������� ������� (0-9)\n");
			printf_s("\n ��� ���������� ����� ������� Enter\n\n");
			printf_s("\n %s\n", header);
			printf_s("\n ������� ���: ");

			if (!(scanf_s("%d", &year)))
			{
				system("cls");
				printf_s("\n ������.\n\n ���� �������������� ������ ��������� ������� (0-9)\n\n ");
				system("pause");
				year = -1;
			}
			else
				if (year < MIN_YEAR || year > MAX_YEAR)
				{
					system("cls");
					printf_s("\n ������.\n\n ���������� �������� �������� � %d �� %d ���\n\n ", MIN_YEAR, MAX_YEAR);
					system("pause");
					year = -1;
				}
		} while (year < 0);

		do
		{
			system("cls");
			printf_s("\n %s\n\n", header);
			printf_s("\n ��������� ��������� ������: %d", year);
			printf_s("\n\n ��������� ��������� ������?\n\n 1 - ���\n 0 - ��");
			correct = userchoice();

			if (correct < 0 || correct > 1)
			{
				system("cls");
				printf_s("\n ������\n");
				printf_s("\n ������� ������������ �����\n\n ");
				system("pause");
			}

		} while (correct < 0 || correct > 1);

	} while (!correct);

	return year;
}

//����������� �����
char* copy_string(char* original)
{
	char *tmp = NULL; //��������� ����������(����� ������)
	unsigned int i;   //������

	tmp = (char*)malloc((strlen(original) + 1)*sizeof(char));

	for (i = 0; i < strlen(original); i++) //������������ ������������ ������ � ����� ����������
		tmp[i] = original[i];

	tmp[i] = '\0';

	return tmp;
}

//�������� �� �������������� ������� � ������ ����������
int punctuation(char symbol)
{
	const char pmarks[] = "`'%!,.?;:)(-_=+\"}{][><*&^#@\\/|"; //������-��������� � ������� ����������
	int i = 0; //������
	int yes = 0; //������ �������������� ������� � ������ ����������

	while (*(pmarks + i) != '\0' && !yes)
	{
		if (symbol == *(pmarks + i))
			yes = 1;
		i++;
	}
	return yes;
}

//���������� ����� � ������
int amt(NODE* list)
{
	NODE* tmp = list; //��������� �� ������� ����
	int amt = 0;      //���������� �����

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

//���� ���������. ����������
int get_n(int amount, char* inputitem, char* s)

{
	system("cls");

	int n; //���������� �������� �������� ����� ������ (����)

	do
	{
		system("cls");

		printf_s("\n ����� �������  - %d\n", amount);

		if (s == "out")
			printf_s("\n ������� ����� �� 1 �� %d\n", amount);
		else
			printf_s("\n ������� ����� �� 1 �� %d\n", amount + 1);

		printf_s("\n %s: ", inputitem);

		if (!scanf_s("%d", &n))
			n = 0;
		if (!n || (n > amount && s == "out") || (n > amount + 1 && s == "add"))
		{
			system("cls");
			if (s == "out")
				printf_s("\n ������.\n ������� ����� � ��������� �� 1 �� %d\n\n ", amount);
			else
				printf_s("\n ������.\n ������� ����� � ��������� �� 1 �� %d\n\n ", amount + 1);
			system("pause");
		}
	} while (n < 1 || (n > amount && s == "out") || (n > amount + 1 && s == "add"));

	return n;
}

//����� � �������
void cnsl_output(NODE* list)
{
	system("cls");
	int i = 0;
	int n = get_n(amt(list), "������� ���������� �������, ��������� �� ����� ��������", "out");

	while (list)
	{
		if (!(i % n))
		{
			if (i && list)
			{
				printf_s("\n ����� - ������� Enter");
				rewind(stdin);
				getchar();
			}

			system("cls");
			printf_s("\n-------------------------------------------------------------------------------- \n");
			printf_s(" | %3s | %20s | %20s | %6s | %10s, USD |", "�", "�����������", "������", "���", "����");
			printf_s("\n-------------------------------------------------------------------------------- \n");
		}
		printf_s(" | %3d | %20s | %20s | %6d |      %10.2f |", (i++) + 1, list->data->artist, list->data->album, list->data->year, list->data->price);
		printf_s("\n-------------------------------------------------------------------------------- \n");
		list = list->next;
	}
	printf_s("\n ������� � ���� - ������� Enter");
	rewind(stdin);
	getchar();
}

//����
int menu(NODE* list)
{
	system("cls");

	if (list)
	{
		printf_s("\n �� ������ ������ ������� � ������: %d\n", amt(list));
		printf_s("\n ����\n\n");
		puts(" 1 - �������");
		puts(" 2 - ���������� ������");
		puts(" 3 - ������� ������");
		puts(" 4 - �������� ������");
		puts(" 0 - �����");
	}
	else
	{
		printf_s("\n �� ������ ������ ������ ����\n");
		printf_s("\n ����\n\n");
		puts(" 1 - �������");
		puts(" 2 - ���������� ������");
		puts(" 0 - �����");
	}

	return(userchoice());
}

//���������� ������� �� ����� (��� ���-�� ����� ������, ��� ��� �������)
NODE* read_from_file(NODE* list, char* fn)
{
	FILE* flist = NULL; //����
	errno_t err; //��� ����� ����� ������������ fopen_s ������ fopen
	NODE* tmp = NULL;//����� ����

	err = fopen_s(&flist, fn, "r"); //�������� ����� ��� ������

	if (err)
	{
		printf_s("\n ���������� ������� ��� ������ ���� %s \n ", fn);
		system("pause");
	}
	else
	{
		int uc;

		if (!list) //���� ������ ���� ���������� � ������
			uc = 1;
		else //����� ��������������� ����� ���� ���������
			do
			{
				system("cls");
				printf_s("\n ���� ������� �������� ������:\n\n");
				puts(" 1 - � ������");
				puts(" 2 - � �����");

				uc = userchoice();

				if (uc < 1 || uc > 2)
				{
					system("cls");
					printf_s("\n ������\n");
					printf_s("\n ������� ������������ �����\n\n ");
					system("pause");
				}
			} while (uc < 1 || uc > 2);

			while (!feof(flist)) //���� �� ����� �����
			{
				rewind(stdin);
				int i = 0; //������ ����������� �� ����� ������
				char str[140]; //����������� ������
				fgets(str, 140, flist); //���������� ������ (wow!)

				if (str[i] != ' ' && str[i + 1] != '-') //���� ������ �� ���������� � ������� � ��� ���� �� ��� �� ���� ������ "-"
				{
					tmp = read_to_node(str); //���������� �������������� ����� ������ ���� ������� �� ������

					if (uc == 1) //���������� � ������
					{
						tmp->next = list;
						if (list)
							list->prev = tmp;
						tmp->prev = NULL;
						list = tmp;
					}
					else //���������� � �����
					{
						NODE* current = list; //��������� �� ������ ������
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

//���������� �������������� ����� ���� ������� �� ��������� ������
NODE* read_to_node(char*str)
{
	NODE* tmp = (NODE*)malloc(sizeof(NODE));
	tmp->data = (DATA*)malloc(sizeof(NODE));

	char* artist = NULL; //�����������
	char* album = NULL; //������
	int year = NULL; //���
	float price; //����

	int i = 0; //������ ������

	artist = str_read(str, &i); //����� � ����� ���������� ������ �� ������ �����������
	if (artist)
	{
		tmp->data->artist = copy_string(artist); //������������ ����������� �������� �����������

		album = str_read(str, &i); //����� ���������� ������ �� ������ ������ (������ ��� �� ��������)
		if (album)
		{
			tmp->data->album = copy_string(album);

			year = atoi(str_read(str, &i)); //�������� ���
			if (year)
			{
				if (year < MIN_YEAR || year > MAX_YEAR)
					tmp->data->year = 0;
				else
					tmp->data->year = year;
			}
			else
				tmp->data->year = 0;

			price = strtof(str_read(str, &i), '\0'); //�������� ����
			if (price)
			{
				if (price < MIN_PRICE || price > MAX_PRICE)
				{
					float f = 0.0;
					tmp->data->price = f;
				}
				else
					tmp->data->price = price;

				return tmp; //� ���� ��� ���� ��������� ��� ����������� ������ ���������� ����
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

//��������� ��������� ������ �� �����
char* str_read(char* str, int* i)
{
	char* tmp = NULL; //������ ������ � ������ ���������
	int l = *i; //������ ��������� ������
	int j = 0; //������ ������ � ������ ���������

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

//����� � ����
void write_to_file(NODE* list, char* fn)
{
	int i = 0; //������ ���������� �������
	int uc;
	FILE* flist = NULL;
	errno_t err;
	err = fopen_s(&flist, fn, "w");


	if (err)
	{
		printf_s("\n ���������� ������� ���� %s ��� ������\n ", fn);
		system("pause");
		return;
	}
	else
	{
		do
		{
			system("cls");
			printf_s("\n ���������� ������ � ����\n\n");
			puts(" 1 - ��������� ���� ������ ��� ������");
			puts(" 2 - ��������� ����, ��������� ��� �������� � ���������");
			puts(" 0 - ������");
			uc = userchoice();

			if (uc < 0 || uc > 2)
			{
				system("cls");
				printf_s("\n ������\n");
				printf_s("\n ������� ������������ �����\n\n ");
				system("pause");
			}
		} while (uc < 0 || uc > 2);

		if (!uc)
			return;
		if (uc == 1)
		{
			fprintf_s(flist, "%s", "\n -------------------------------------------------------------------------------- \n");
			fprintf_s(flist, " | %3s | %20s | %20s | %6s | %10s, USD |", "�", "�����������", "������", "���", "����");
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
		printf_s("\n ������ ���������");
	}
	err = fclose(flist);
}

//��� ������� 
int file_read_help()
{
	system("cls");
	printf_s("\n ���������� ������� �� �����\n");
	printf_s("\n ���������� ����� ������ ��������������� ����� ��������� ����� ������\n\n");
	printf_s("\n ��� ����� ����������� � ������:\n");
	printf_s("\n ����������� ���������� ��������  - %d", MIN_STRING_LENGTH);
	printf_s("\n ������������ ����������  - %d", MAX_STRING_LENGTH);
	printf_s("\n ��� ������� ����� ������ %d ����� ���������������", MAX_STRING_LENGTH);
	printf_s("\n ���������������� ��� ������ ���������� ����� ������� 1-� ������ � ������ ����");
	printf_s("\n ���������������� ��� �������� ����� ������� 1-� ��������");
	printf_s("\n ����� ���������� � ������ ������ ����� ���������������\n");
	printf_s("\n ��� ����� ��� ������� � ����:\n");
	printf_s("\n ���������� �������� �������� ���� � %d �� %d USD", MIN_PRICE, MAX_PRICE);
	printf_s("\n ����� � ������� ����� ����������� �������. � ���� ������ ������� ����� ����������");
	printf_s("\n ���������� �������� �������� ���� ������� � %d �� %d ���", MIN_YEAR, MAX_YEAR);
	printf_s("\n � ������, ���� ���� ��� ��� ������� �� �������� � ������ ��������, �������� ����� ��������� 0");

	printf_s("\n\n ���������� - 1");
	printf_s("\n ������ - 0");

	return(userchoice());
}

//���� �����/������������ �����
char* get_file_name(char* header)
{
	int uc;

	do
	{
		system("cls");
		printf_s("\n%s\n", header);
		printf_s("\n ����������� ������ ��������:");
		printf_s("\n 1 - ��������� ����-����");
		printf_s("\n 2 - ������ ������������ �����");

		uc = userchoice();

		if (uc < 1 || uc > 2)
		{
			system("cls");
			printf_s("\n ������\n");
			printf_s("\n ������� ������������ �����\n\n ");
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
			printf_s("\n ������ ����� ������������ �����:\n\n");
			printf_s("\n ����:\\����\\���_�����.txt\n");
			printf_s("\n ���� ����������� �������� ������� Enter");

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
				printf_s("\n �� �����: %s\n ", tmp);
				printf_s("\n 1 - ��� ������ ������������ �����");
				printf_s("\n 0 - ������ ������������ ����� ������");

				correct = userchoice();

				if (correct < 0 || correct > 1)
				{
					system("cls");
					printf_s("\n ������\n");
					printf_s("\n ������� ������������ �����\n\n ");
					system("pause");
				}
			} while (correct < 0 || correct > 1);
		} while (!correct);

		return tmp;
	}
}

//������������ ������� ��-��� ������ (��� ��� ������� ������ ������, ����� ������������� ���, ��� ���� ��������� ����)
NODE* free_ll(NODE*list)
{
	NODE* tmp = list;  //��������� �� ������� ����
	NODE* next = NULL; //��������� �� ����, ��������� �� �������

	while (tmp)
	{
		next = tmp->next;
		tmp = free_node(tmp);
		tmp = next;
	}
	return NULL;
}

//��-��� ����
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