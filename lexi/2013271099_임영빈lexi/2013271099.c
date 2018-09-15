#include<stdio.h>
#include<conio.h>
#include<ctype.h>
#include<string.h>
#include<stdlib.h>

int keyword_library(char temp[]);//각각의 meta, rop, operator, keyword에 대한 라이브러리입니다.
int operator_library(char temp[]);
int ROP_library(char temp[]);
int meta_library(char temp[]);
/*전체 시스템 구조는 a.txt의 내용을 읽고 읽었을때 문자가 위의 라이브러리에 있는 내용이면 해당 라이브러리 이름과 번호를 내보내주고
아닐 시 문자열을 더 모아서 계속 라이브러리값과 비교합니다. 라이브러리에 추가 되지 않는것은 identifier처리를 해주고 파일을 다읽을면 끝냅니다.
*/
int main()
{
	char ch, temp[40];//temp에는 현재 읽은 문자열이 들어있습니다.
	char temp_1[40];//identifier전용 배열로 temp값을 복사해논 것 입니다.
	char temp_temp[40];//identifier 모아 놓으려고 만들엇습니다.
	char lastword;
	FILE *file_pointer;
	int y = 0;//' '와 엔터를 처리하기 위한 플래그로 쓰입니다.
	char id_collected[40];//identifier각자를 모아줍니다. 미구현입니다.
	int id_count = 0;//id 갯수
	int count, x = 0;
	int count_ouput = 0;//현재 몇번째 출력인지 알려주기 위한 카운터
	file_pointer = fopen("a.txt", "r");
	if (file_pointer == NULL)
	{
		printf("The file could not be opened.\n");
		exit(0);
	}
	while ((ch = fgetc(file_pointer)) != EOF)
	{
		temp[x++] = ch;//temp에 a.txt내용을 추가합니다. 1글자식 그리고 x++
		do {
			temp[x] = '\0';// 배열 닫기 

			if (isgraph(ch) || ch == '_')//_ 포함
			{



				temp[x] = '\0';
				temp_1[x] = '\0';
				if (operator_library(temp) == 1 && (x != 0))//읽은값이 operator와 일치하면
				{
					temp[x] = '\0';
					x = 0;//temp값 다시받기위함
					count_ouput++;//몇번쨰 출력인지 표시
					printf("\n%d.\t", count_ouput);
					printf("\t%d\t", operator_library_num(temp));//몇번째 operator인지 알려줌
					printf("OPERATOR:\t%s", temp);
					y = 0;//나중에 엔터나 스페이스바 없애기용 플래그 입니다.
				}
				else if (meta_library(temp) == 1 && (x != 0))//이하 동일한모양의 라이브러리 주석은 같습니다.
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
				{//identifier 나누는 곳
					memcpy(temp_1, temp, sizeof(char) * 40);//temp_1에 지금까지 읽은값 저장
					lastword = temp_1[x - 1];//값복사인데 안씁니다.
					temp_1[x - 1] = '\0';//방금 읽은 id아닌 부분은 뺍니다.
					temp[0] = temp[x - 1];//이부분은 방금 이 elseif에 있는 조건에 걸린 부분으로 identifier가아닌 다른 라이브러리 값이 있기에 강제로 temp값에 집어 넣어줍니다.
					temp[1] = '\0';
					memcpy(temp_temp, temp, sizeof(char) * 0);//이곳은 id값들 모아두려고 복사해논건데 구현이 다 되지 않았습니다.
					memcpy(temp, temp_temp, sizeof(char) * 0);
					count_ouput++;
					printf("\n%d. \t", count_ouput);

					if (isdigit(temp_1[0]) && isdigit(temp_1[x - 2]))//시작과 끝이 숫자일시 number로
						printf("\t1\tNumber:\t \t%s", temp_1);
					else
					{
						id_count++;//id 따로 만드는데에는 미구현입니다.
						printf("\t0\tIdentifier:\t%s", temp_1);// id출력
						memcpy(id_collected, temp_1, sizeof(char) * 40);
						x = 1;

						y = 1;
					}
				}

			}
			else if ((ch == '\n' || ch == ' ' || ch == '	') && (x != 0))//엔터나 스페이스일때
			{
				if (y == 2) {//안쓰지만 확장성 때문에 만들어 두었습니다.
					x = 0;
					temp[x] = '\0';

				}
				else if (y == 0) {//무조건 읽어들이기 때문에 엔터나 스페이스는 x--로 없에줍니다.
					x--;
					temp[x] = '\0';

				}
				else if (y == 1) {//identifier일때 엔터나 스페이스는 그전(엔터나 스페이스 없는상태)까지의 값을 id로 반환해줍니다.

					memcpy(temp_1, temp, sizeof(char) * 40);//코드는 93쪽 과 동일합니다.
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
//각 키워드나 relop등 라이브러리를 선언 한 곳입니다.-return 1이면 사용했다
//_num붙은 것들은 각각의 몇번째것을 사용했는지 리턴해줍니다. 
int keyword_library(char temp[])//문자열을 받아서
{
	int count = 0, flag = 0;
	char keywords[16][12] = { "if", "else", "while", "do", "for", "include",
		"define", "typedef", "struct", "int", "char", "float",
		"main","double", "void", "return" };
	while (count <= 15)//15개중에 있는지 검사
	{
		if (strcmp(keywords[count], temp) == 0)
		{
			flag = 1;//있으면 break
			break;
		}
		count = count + 1;//몇번째것인지 확인차
	}
	return (flag);//있으면 1 없으면 0 리턴
}
int keyword_library_num(char temp[])//이하 같습니다.
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