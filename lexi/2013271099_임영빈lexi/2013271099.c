#include<stdio.h>
#include<conio.h>
#include<ctype.h>
#include<string.h>
#include<stdlib.h>

int keyword_library(char temp[]);//������ meta, rop, operator, keyword�� ���� ���̺귯���Դϴ�.
int operator_library(char temp[]);
int ROP_library(char temp[]);
int meta_library(char temp[]);
/*��ü �ý��� ������ a.txt�� ������ �а� �о����� ���ڰ� ���� ���̺귯���� �ִ� �����̸� �ش� ���̺귯�� �̸��� ��ȣ�� �������ְ�
�ƴ� �� ���ڿ��� �� ��Ƽ� ��� ���̺귯������ ���մϴ�. ���̺귯���� �߰� ���� �ʴ°��� identifieró���� ���ְ� ������ �������� �����ϴ�.
*/
int main()
{
	char ch, temp[40];//temp���� ���� ���� ���ڿ��� ����ֽ��ϴ�.
	char temp_1[40];//identifier���� �迭�� temp���� �����س� �� �Դϴ�.
	char temp_temp[40];//identifier ��� �������� ��������ϴ�.
	char lastword;
	FILE *file_pointer;
	int y = 0;//' '�� ���͸� ó���ϱ� ���� �÷��׷� ���Դϴ�.
	char id_collected[40];//identifier���ڸ� ����ݴϴ�. �̱����Դϴ�.
	int id_count = 0;//id ����
	int count, x = 0;
	int count_ouput = 0;//���� ���° ������� �˷��ֱ� ���� ī����
	file_pointer = fopen("a.txt", "r");
	if (file_pointer == NULL)
	{
		printf("The file could not be opened.\n");
		exit(0);
	}
	while ((ch = fgetc(file_pointer)) != EOF)
	{
		temp[x++] = ch;//temp�� a.txt������ �߰��մϴ�. 1���ڽ� �׸��� x++
		do {
			temp[x] = '\0';// �迭 �ݱ� 

			if (isgraph(ch) || ch == '_')//_ ����
			{



				temp[x] = '\0';
				temp_1[x] = '\0';
				if (operator_library(temp) == 1 && (x != 0))//�������� operator�� ��ġ�ϸ�
				{
					temp[x] = '\0';
					x = 0;//temp�� �ٽùޱ�����
					count_ouput++;//����� ������� ǥ��
					printf("\n%d.\t", count_ouput);
					printf("\t%d\t", operator_library_num(temp));//���° operator���� �˷���
					printf("OPERATOR:\t%s", temp);
					y = 0;//���߿� ���ͳ� �����̽��� ���ֱ�� �÷��� �Դϴ�.
				}
				else if (meta_library(temp) == 1 && (x != 0))//���� �����Ѹ���� ���̺귯�� �ּ��� �����ϴ�.
				{
					temp[x] = '\0';
					x = 0;
					count_ouput++;
					printf("\n%d.\t", count_ouput);

					printf("\t%d\t", meta_library_num(temp));

					printf("META:\t \t%s", temp);
					y = 0;
				}

				else if (ROP_library(temp) == 1 && (x != 0))
				{
					temp[x] = '\0';
					x = 0;
					count_ouput++;
					printf("\n%d.\t", count_ouput);
					printf("\t%d\t", ROP_library_num(temp));
					printf("ROP:\t \t%s", temp);
					y = 0;
				}
				else if (keyword_library(temp) == 1)
				{
					temp[x] = '\0';
					x = 0;
					count_ouput++;
					printf("\n%d\t", count_ouput);
					printf("\t%d\t", keyword_library_num(temp));
					printf("Keyword:\t%s", temp);
					y = 0;
				}

				else if ((ch == '+' || ch == '-' || ch == ',' || ch == '*' || ch == '/' || ch == '%' || ch == '=' || ch == '->' || ch == '!' || ch == '.' || ch == ',' || ch == '&' || ch == '('
					|| ch == ',' || ch == ')' || ch == '{' || ch == '}' || ch == '\"' || ch == '[' || ch == ']' || ch == '\'' || ch == ',' || ch == ':' || ch == ';' || ch == '#' || ch == '>' || ch == '=' || ch == '<'
					|| ch == '>' || ch == '<' || ch == '&' || ch == '|') && keyword_library(temp) == 0 && ROP_library(temp) == 0 && meta_library(temp) == 0 && operator_library(temp) == 0)
				{//identifier ������ ��
					memcpy(temp_1, temp, sizeof(char) * 40);//temp_1�� ���ݱ��� ������ ����
					lastword = temp_1[x - 1];//�������ε� �Ⱦ��ϴ�.
					temp_1[x - 1] = '\0';//��� ���� id�ƴ� �κ��� ���ϴ�.
					temp[0] = temp[x - 1];//�̺κ��� ��� �� elseif�� �ִ� ���ǿ� �ɸ� �κ����� identifier���ƴ� �ٸ� ���̺귯�� ���� �ֱ⿡ ������ temp���� ���� �־��ݴϴ�.
					temp[1] = '\0';
					memcpy(temp_temp, temp, sizeof(char) * 0);//�̰��� id���� ��Ƶη��� �����س�ǵ� ������ �� ���� �ʾҽ��ϴ�.
					memcpy(temp, temp_temp, sizeof(char) * 0);
					count_ouput++;
					printf("\n%d. \t", count_ouput);

					if (isdigit(temp_1[0]) && isdigit(temp_1[x - 2]))//���۰� ���� �����Ͻ� number��
						printf("\t1\tNumber:\t \t%s", temp_1);
					else
					{
						id_count++;//id ���� ����µ����� �̱����Դϴ�.
						printf("\t0\tIdentifier:\t%s", temp_1);// id���
						memcpy(id_collected, temp_1, sizeof(char) * 40);
						x = 1;

						y = 1;
					}
				}

			}
			else if ((ch == '\n' || ch == ' ' || ch == '	') && (x != 0))//���ͳ� �����̽��϶�
			{
				if (y == 2) {//�Ⱦ����� Ȯ�强 ������ ����� �ξ����ϴ�.
					x = 0;
					temp[x] = '\0';

				}
				else if (y == 0) {//������ �о���̱� ������ ���ͳ� �����̽��� x--�� �����ݴϴ�.
					x--;
					temp[x] = '\0';

				}
				else if (y == 1) {//identifier�϶� ���ͳ� �����̽��� ����(���ͳ� �����̽� ���»���)������ ���� id�� ��ȯ���ݴϴ�.

					memcpy(temp_1, temp, sizeof(char) * 40);//�ڵ�� 93�� �� �����մϴ�.
					//	lastword = temp_1[x-1];
					temp_1[x - 1] = '\0';
					temp[0] = temp[x - 1];
					temp[1] = '\0';
					memcpy(temp_temp, temp, sizeof(char) * 0);
					memcpy(temp, temp_temp, sizeof(char) * 0);
					count_ouput++;
					printf("\n%d. \t", count_ouput);
					printf("\t0\tIdentifier:\t%s", temp);

				}

			}

		} while (y == 1);
	}
	system("pause");
	fclose(file_pointer);

	return 0;
}
//�� Ű���峪 relop�� ���̺귯���� ���� �� ���Դϴ�.-return 1�̸� ����ߴ�
//_num���� �͵��� ������ ���°���� ����ߴ��� �������ݴϴ�. 
int keyword_library(char temp[])//���ڿ��� �޾Ƽ�
{
	int count = 0, flag = 0;
	char keywords[16][12] = { "if", "else", "while", "do", "for", "include",
		"define", "typedef", "struct", "int", "char", "float",
		"main","double", "void", "return" };
	while (count <= 15)//15���߿� �ִ��� �˻�
	{
		if (strcmp(keywords[count], temp) == 0)
		{
			flag = 1;//������ break
			break;
		}
		count = count + 1;//���°������ Ȯ����
	}
	return (flag);//������ 1 ������ 0 ����
}
int keyword_library_num(char temp[])//���� �����ϴ�.
{
	int count = 0, flag = 0;
	char keywords[16][12] = { "if", "else", "while", "do", "for", "include",
		"define", "typedef", "struct", "int", "char", "float",
		"double","main", "void", "return" };
	while (count <= 15)
	{
		if (strcmp(keywords[count], temp) == 0)
		{
			flag = 1;
			break;
		}
		count = count + 1;
	}
	return (count + 25);
}

int operator_library(char temp[])
{
	int count = 0, flag = 0;
	char operator[13][12] = { "+", "-", "*", "/", "%", "=",
		"->", "!", ".", ",", "&", "++",
		"--" };
	while (count <= 12)
	{
		if (strcmp(operator[count], temp) == 0)
		{
			flag = 1;
			break;
		}
		count = count + 1;
	}
	return (flag);
}
int operator_library_num(char temp[])
{
	int count = 0, flag = 0;
	char operator[13][12] = { "+", "_", "*", "/", "%", "=",
		"->", "!", ".", ",", "&", "++",
		"--" };
	while (count <= 12)
	{
		if (strcmp(operator[count], temp) == 0)
		{
			flag = 1;
			break;
		}
		count = count + 1;
	}
	return (count + 3);
}

int meta_library(char temp[])
{
	int count = 0, flag = 0;
	char meta[12][12] = { "(", ")", "{", "}", "[", "]",
		"`", ":", ";", "\"", "#" };
	while (count <= 11)
	{
		if (strcmp(meta[count], temp) == 0)
		{
			flag = 1;
			break;
		}
		count = count + 1;
	}
	return (flag);
}
int meta_library_num(char temp[])
{
	int count = 0, flag = 0;
	char meta[12][12] = { "(", ")", "{", "}", "[", "]",
		"`", ":", ";", "\"", "#" };
	while (count <= 11)
	{
		if (strcmp(meta[count], temp) == 0)
		{
			flag = 1;
			break;
		}
		count = count + 1;
	}
	return (count + 16);
}

int ROP_library(char temp[])
{
	int count = 0, flag = 0;
	char meta[10][12] = { ">", ">=", "<", "<=", "<>", "==",
		"=!", "&&", "||" };
	while (count <= 9)
	{
		if (strcmp(meta[count], temp) == 0)
		{
			flag = 1;
			break;
		}
		count = count + 1;
	}
	return (flag);
}
int ROP_library_num(char temp[])
{
	int count = 0, flag = 0;
	char meta[10][12] = { ">", ">=", "<", "<=", "<>", "==",
		"=!", "&&", "||" };
	while (count <= 9)
	{
		if (strcmp(meta[count], temp) == 0)
		{
			flag = 1;
			break;
		}
		count = count + 1;
	}
	return (2);
}