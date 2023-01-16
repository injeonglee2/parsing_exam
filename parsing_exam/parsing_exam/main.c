#define _CRT_SECURE_NO_WARNINGS // scanf, strcpy, fopen 보안 경고로 인한 컴파일 에러 방지
#include <stdio.h>
#include <string.h>

/****************************************************************************/
/* Startup.cfg 파일을 열어 Tag name과 value를 저장하여 전체 Tag Liat 출력 후*/
/*   사용자가 조회하고 싶은 Tag의 번호를 입력받아 출력하는 프로그램			*/
/****************************************************************************/


/*
argc: argument count. 함수가 받는 인자의 갯수
프로그램을 실행할 때 지정해 준 "명령행 옵션"의 "개수"가 저장되는 곳
argv[]: argument vector. 인자의 모음. argv[0] = 실행 파일의 경로 및 이름
프로그램을 실행할 때 지정해 준 "명령행 옵션의 문자열들"이 실제로 저장되는 배열

strtok: 문자열 분리. 첫 번째 인자가 NULL일 경우 해당 문자열에서 구분자 다음부터 탐색하여 분리
strcmp: 문자열 비교. 두 문자열이 같을 경우 0을 반환
*/


typedef struct tagInfo {		// tag의 정보를 저장할 구조체
	char name[32];	// tag 이름 ex) SYSTEM, INFORMATION_SAVE...
	char val[32];	// tag 값 ex) YES, LOAD, IO/iodefine.io...
}TAGINFO;


int main(int argc, char* argv[]) {
	// 변수 선언부
	int i;	// for문 내에서 사용할 변수

	FILE *pFile;		// 파일의 위치를 받는 pointer
	char line[100];		// 파일 한 줄마다의 내용을 저장하는 line buffer

	char seps[] = " ,\t\n";	// 파싱할 때 구분자가 되는 문자들
	char *token;			// 파싱한 문자를 받는 pointer

	char fstTag[17][32] =	// Startup.cfg File의 정의 목록 중 1st Tag
	{ "SYSTEM",
		"INFORMATION_SAVE",
		"MESSAGE_SAVE",
		"EVENT_SAVE",
		"IO",
		"IO_DRIVER",
		"S_INTLKS",
		"V_INTLKS",
		"ALARM_MANAGEMENT_FILE",
		"ALARM_HISTORY_FILE",
		"FUNCTION",
		"NAVIGATION",
		"GUI_DISPLAY",
		"CONTROLPRO",
		"EASYCLUSTER_MODULE",
		"EASYCLUSTER_CLUSTER",
		"USER_CODE" };
	TAGINFO tagList[17];	// 파일에 적힌 tag의 내용을 저장할 구조체

	int tagNum; // 사용자에게 받을 태그 번호

	for (i = 0; i<sizeof(tagList) / 64; i++) {	// 모든 tagList 구조체 멤버에 대하여 " "으로 초기화
		strcpy(tagList[i].name, " ");
		strcpy(tagList[i].val, " ");
	}

	// 함수 인자 입력 확인
	if (argv[1]) {								// 함수 실행 시 첫 번째 인자를 받았을 때 
		printf("argv[%d] = %s\n", 1, argv[1]);	// 그 값을 콘솔에 출력
	}
	else {									// 인자가 없을 때
		printf("No parameters\n");		// 에러 메세지 출력
		return -1;
	}


	// File open이 잘 실행되었는지 확인
	if (pFile = fopen(argv[1], "r")) {		// main 함수의 두 번째 인자로 받은 파일을 읽기 모드로 열었을 때
		printf("File open success\n\n");	// 성공 메세지 출력
	}
	else {									// main 함수의 두 번째 인자로 받은 파일을 열기 실패했을 때
		printf("File open failed\n\n");		// 실패 메세지 출력
		return -1;
	}


	// File의 내용을 읽어 구조체에 저장하며 콘솔에 출력
	while (!feof(pFile)) {	// 파일의 끝이 아닐 경우
		if (fgets(line, sizeof(line), pFile) == NULL) {	// fgets를 실행하여 line에 한 줄 씩 저장 후, 그 반환값이 없을 경우 
			break;						// 함수 비정상 종료
		}
		else if (line[0] == '#' || line[0] == '\n' || line[0] == '\t' || line[0] == ' ') {	// 주석이나 빈 문장일 경우 
			continue;	// 출력하지 않고 반복문 재실행
		}
		else {			// 나머지 경우 (처리할 문자열을 만났을 경우)
			token = strtok(line, seps);	// line buffer의 내용을 seps 구분자를 기점으로 나누기

			for (i = 0; i<sizeof(tagList) / 64; i++) {	// fstTag의 index 마다
				strcpy(tagList[i].name, fstTag[i]);	// tag Name에 2차원 배열에 지정된 이름 복사

				if (!strcmp(token, fstTag[i])) {	// 파싱하여 token에 저장된 첫 번째 값이 fstTag[i]와 같을 경우
					printf("%d:", i + 1);		// 해당 번호와 콜론 출력
					token = strtok(NULL, seps);	// 다음 단어 파싱하여 저장
					printf("%s\n", token);		// 다음 단어(val)를 출력
					strcpy(tagList[i].val, token); // 구조체에 저장
				}
			}
		}
	}

	fclose(pFile);	// 파일 닫기


					// 사용자에게 조회할 Tag 인덱스를 받아 해당 값 출력
	while (1) {	// 사용자에게 번호를 입력받아 조회하고싶은 번호를 입력받아 출력하는 부분
		printf("\n\n\n1~17 중 조회하고 싶은 Tag 번호를 입력하세요 (0: 종료): ");	// 입력받을 숫자에 대한 설명
		scanf("%d", &tagNum);	// 입력받은 숫자를 저장

		if (tagList[tagNum - 1].val[0] == ' ') {	// 해당 인덱스의 값이 입력되지 않았을 경우 (val 멤버의 첫 번째 값이 초기값과 같은지 검사)  
			printf("\n해당 인덱스의 Tag에 지정된 값이 없습니다.\n");	// 오류 메세지 출력
		}
		else if ((0<tagNum) && (tagNum<18)) {		// 1~17 사이의 값을 입력받을 경우
			printf("\n%d:%s\n", tagNum, tagList[tagNum - 1].val);		// 해당 인덱스의 값 출력
		}
		else if (tagNum == 0) {	// 0을 입력받을 경우
			return 0;			// 프로그램 종료
		}
		else {	// 나머지 경우 (1~17 사이의 값을 입력하지 않았을 경우)
			printf("\n유효하지 않은 번호입니다.\n");	// 오류 메세지 출력
		}
	}
}