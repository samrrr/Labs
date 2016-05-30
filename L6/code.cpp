#include <conio.h>
#include <malloc.h>
#include <stdio.h>
#include <windows.h>
#include <locale.h>

HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);

/*
��������: ��� ������� ��� ������ ����� � ������� �������������.
�������: ������� �� ���������� ��������.
*/
void put_bits(int i)
{
	int m = 31;//����� ���������� ����
	do
	{
		printf("%i", i <0);
		i <<= 1;
		m--;
	} while (m >= 0);
}

/*
��������: ��� ������� ��� ������ ����� � ������� ���� c ����������.
�������: ������� �� ���������� ��������.
*/
void put_colored_bits(int i, int b1, int b2, int b3)
{
	int m = 31;//����� ���������� ����
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
��������: ��� ������� ��� ��������� ������� �������.
�������: ��� ������� ���������� ������ ������� �������.
*/
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
	} while (ch >= -128 && ch <= -17 || ch == '\0' || ch == -32);
	return ch;
}

/*
��������: ��� ������� ��� ����� ������ �����.
�������: ��� ������� ���������� �������� �����.
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
		ch = my_getch();//�������� ������ ������� ������
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
��������: ��� ������� ��� ����� ������ ����� ��������.
�������: ��� ������� ���������� �������� �����.
*/
int input_binary_number()
{
	int i;         //�������� �����	
	char ch;       //�������� ������
	int n;         //����� ��������� ����

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
��������: ��� ������� ��� ���������� ������������ ������ ������.
�������: ��� ������� ���������� ��������� �����.
*/
int sdv_p_�(int c, int b1, int b2, int k)
{
	c =
		(c & ~(0xFFFFFFFF >> b1 << b1 << b2 >> b2)) |
		((c & 0xFFFFFFFF) << b2 >> b2 >> b1 >> k << b1) |
		((c & 0xFFFFFFFF) >> b1 << (32 - k) >> b2);
	return c;
}

/*
��������: ��� ������� ��� ���������� ������ ������.
�������: ��� ������� ���������� ��������� �����.
*/
int sdv_p(int c, int b1, int b2, int k)
{
	c =
		(c & ~(0xFFFFFFFF >> b1 << b1 << b2 >> b2)) |
		((c & 0xFFFFFFFF) << b2 >> b2 >> b1 >> k << b1);
	return c;
}

/*
��������: ��� ������� ��� ���������� ������ �����.
�������: ��� ������� ���������� ��������� �����.
*/
int sdv_l(int c, int b1, int b2, int k)
{

	c =
		(c & ~(0xFFFFFFFF >> b1 << b1 << b2 >> b2)) |
		((c & 0xFFFFFFFF) >> b1 << b1 << b2 << k >> b2);
	return c;
}

/*
��������: ��� ������� ��� �������� ���� �����.
�������: ��� ������� ���������� �����.
*/
int menu_input(int i, bool *is_input,bool *is_res)
{
	int menu;       //���������� ���������� ������ ����
	do
	{
		system("cls");
		puts("���� ������ �����");
		if (*is_input == 1)
			puts("��������! ��� ����� ������ �����, ������ ����� � ������ ��������� ���������");
		puts("1-���� � ���������� ������� ���������");
		puts("2-���� � ���� �����");
		puts("0-������� � �������");
		puts("");
		puts("��� �����:");
		menu = input_number();
		system("cls");
		switch (menu)
		{
		case 1:
			puts("��������� ������� ������ �����, ���� ������ �������� ����� ��������������");
			puts("��� ��������� ����� ������� ����");
			puts("������� ����� ����� �� -99999999 �� 999999999:");
			i = input_number();
			*is_input = 1;
			*is_res = 0;
			puts("����� ������� �������");
			system("pause");
			break;
		case 2:
			puts("��������� ������� ������ '1' � '0', ���� ������ �������� ����� ��������������");
			puts("���� ������ ��� 32 ����");
			puts("����� ����, ��� ������ ��� ���� ������� ����");
			puts("������� ���� ������� � 31:");
			i = input_binary_number();
			*is_input = 1;
			*is_res = 0;
			puts("����� ������� �������");
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
	return i;
}

/*
��������: ��� ������� ��� �������� ���� ������.
�������: ��� ������� ������ ����������.
*/
void menu_output(int i,int i_res,bool is_res)
{
	int menu;       //���������� ���������� ������ ����
	do
	{
		system("cls");
		puts("����� ������ �����");
		puts("1-����� ��������� �����");
		puts("2-����� ���������� ��������� �����");
		puts("0-������� � �������");
		puts("");
		puts("��� �����:");
		menu = input_number();
		system("cls");
		switch (menu)
		{
		case 1:
			puts("�������� �����:");
			puts("� ���������� ������� ���������:");
			printf("%i\n",i);
			puts("� ������� �������������:");
			put_bits(i);
			puts("");
			system("pause");
			break;
		case 2:
			if (is_res)
			{
				puts("��������� ���������:");
				puts("� ���������� ������� ���������:");
				printf("%i\n", i_res);
				puts("� ������� �������������:");
				put_bits(i_res);
				puts("");
			}
			else
				puts("�� ��� �� ������������ �������� �����. �������� ������");
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

/*
��������: ��� ������� ��� ����� ���������� �������.
�������: ��� ������� ������ ����������.
*/
void input_sdvp(int*k, int*b1, int*b2)
{
	do
	{
		puts("������� ����� ���� �� 0 �� 30, � �������� ����� �����:");
		*b1 = input_number();
		if ((*b1 < 0 || *b1 >= 31))
		{
			puts("������! �� ����� ����� �� ��������� ���������� ��������");
			system("pause");
		}
	} while (*b1<0 || *b1 >= 31);
	do
	{
		printf("������� ����� ���� �� %i �� 31, �� �������� ������������ ����� �����:\n", *b1+1);
		*b2 = input_number();
		if (*b2 <= *b1 || *b2 >= 32)
		{
			puts("������! �� ����� ����� �� ��������� ���������� ��������");
			system("pause");
		}
	} while (*b2 <= *b1 || *b2 >= 32);
	do
	{
		printf("������� ���������� ����� ��� ������ �� 1 �� %i, �� ��������\n������������ ����� �����:\n", *b2-*b1);
		*k = input_number();
		if (*k<1 || *k > *b2 - *b1)
		{
			puts("������! �� ����� ����� �� ��������� ���������� ��������");
			system("pause");
		}
	} while (*k<1 || *k > *b2 - *b1);
}

/*
��������: ��� ������� ��� �������� ���� ������� ��������.
�������: ��� ������� ������ ����������.
*/
int menu_bits(int i, int i_res, bool *is_res)
{
	int menu;       //���������� ���������� ������ ����
	int k;         //���������� ����� ��� �����
	int b1;         //����� ������� ���� ��� ������ 
	int b2;         //����� ���������� ���� ��� ������
	int r;          //��������������� ����������

	do
	{
		system("cls");
		puts("������� ��������");
		if (*is_res == 1)
			puts("��������! ��� ��������� ������ ��������� ���������");
		puts("1-��������� ����������� ����� ������");
		puts("2-��������� ����������� ����� �����");
		puts("3-��������� ����� ������");
		puts("4-��������� ����� �����");
		puts("0-������� � �������");
		puts("");
		puts("��� �����:");

		menu = input_number();
		system("cls");
		switch (menu)
		{
		case 1:
			puts("��������� ����������� ����� ������");
			input_sdvp(&k, &b1, &b2);
			i_res = sdv_p_�(i, b1, 31 - b2, k);
			break;
		case 2:
			puts("��������� ����������� ����� �����");
			input_sdvp(&k, &b1, &b2);
			i_res = sdv_p_�(i, b1, 31 - b2, b2 - b1 + 1 - (k));
			break;
		case 3:
			puts("��������� ����� ������");
			input_sdvp(&k, &b1, &b2);
			i_res = sdv_p(i, b1, 31 - b2, k);
			break;
		case 4:
			puts("��������� ����� �����");
			input_sdvp(&k, &b1, &b2);
			i_res = sdv_l(i, b1, 31 - b2, k);
			break;
		case 0:
			break;
		default:
			puts("��� ������ ������ ����");
			system("pause");
			break;
		}
		if (menu >= 1 && menu <= 4)
		{
			*is_res = 1;

			puts("�������� ������ �������");

			printf("����� � ������� ����:               ");
			if (menu == 2 || menu == 4)
				put_colored_bits(i, b2, b2 - k, b1 - 1);
			else
				put_colored_bits(i, b1 + k - 1, b2, b1 - 1);
			printf("\n                                    ");
			for (r = 31; r >= 0; r--)
				printf(r <= b2 && r >= b1 ? "|" : " ");
			printf("\n��������� ��������� � ������� ����: ");
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


	int i;     //�������� �����
	int i_res; //��������� ��������� �����
	bool is_input; //������ �����
	bool is_res;   //������ ����������
	int menu;      //���������� ���������� ������ ����

	is_input = 0;
	is_res = 0;
	i = 0;
	i_res = 0;

	do
	{
		system("cls");
		puts("������� ��������");
		puts("1-���� �����");
		puts("2-����� �����");
		puts("3-������� �������� � �������� ������");
		puts("4-�������");
		puts("0-�����");
		puts("");
		puts("��� �����:");
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
				puts("������� ������� �����");
				system("pause");
			}
			break;
		case 3:
			if (is_input)
				i_res = menu_bits(i,i_res,&is_res);
			else
			{
				puts("������� ������� �����");
				system("pause");
			}
			break;
		case 4:
			puts("��� ��������� ��� �����, ������ � ��������� ��������� ������");
			puts("�����, ����������� � 32 �����.");
			puts("����� ����� ������ � ������� ���� ��� � ���������� ������� ���������.");
			puts("��� ����� � ������� ���� ����� ������� ������ '1' � '0' � �����������");
			puts("���� ������ ��� 32 ����.");
			puts("��� ����� � ���������� ������� ��������� ����� ������� ������ �����");
			puts("� ����� ������ ������ ����� �� -99999999 �� 999999999.");
			puts("��� ������ ���������� ������� �������� �� �������:");
			puts("  b1-��� � �������� ����� �����");
			puts("  b2-��� �� ������� ����� �����");
			puts("");
			puts("  k-����� ����� �� ������� ����� �����");
			puts("��� ���� �� ������� ��������� �������: 30>=b1>=0, 31>=b2>b1, b2-b1>=k>0");
			puts("��������� �������� ���������� �����, � ��� �� ��� ����� ������� �");
			puts("������ ����� �����.");
			puts("����� ������ ������� ��� ������ ����");
			puts("��� ����� ������ �����, ������ ����� � ������ ��������� ���������");
			puts("��� ��������� ������ ��������� ���������");
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






































































//**//PF put_colored_bits,i,"�������� �����"
//**//PF sdv_p_�,c,"�������� �����"
//**//PF sdv_p,c,"�������� �����"
//**//PF sdv_l,c,"�������� �����"
//**//PF menu_input,i,"��������� �� �������� �����"
//**//PF menu_input,is_res,"��������� �� ������ ��������� �����"
//**//PF menu_output,i,"�������� �����"
//**//PF menu_output,i_res,"������ ���������"
//**//PF menu_bits,i,"��������� �� �������� �����"
//**//PF menu_bits,i_res,"��������� �� ��������� ���������"
//**//PF menu_bits,is_res,"��������� �� ������ ��������� �����"
//**//PF put_bits,i,"��������� �����"

//**//PF put_colored_bits,b1,"����� ���� � �������� ���������� ������� ���������"
//**//PF put_colored_bits,b2,"����� ���� � �������� ���������� ������ ���������"
//**//PF put_colored_bits,b3,"����� ���� � �������� ���������� ����� ���������"
//**//PF menu_input,is_input,"��������� �� ������ �����"
//**//PF input_sdvp,k,"��������� �� ���������� ��� ��� ������ ������"
//**//PF input_sdvp,b1,"��������� �� ����� ���� � �������� ����� �����"
//**//PF input_sdvp,b2,"��������� �� ����� ���� �� ������� ����� �����"


//**//PF sdv_p_�,b2,"����� ���� � ����� �� �������� ����� �����"
//**//PF sdv_p,b2,"����� ���� � ����� �� �������� ����� �����"
//**//PF sdv_l,b2,"����� ���� � ����� �� �������� ����� �����"







/*END


bool void char int short int 
*/