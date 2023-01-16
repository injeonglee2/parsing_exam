#define _CRT_SECURE_NO_WARNINGS // scanf, strcpy, fopen ���� ���� ���� ������ ���� ����
#include <stdio.h>
#include <string.h>

/****************************************************************************/
/* Startup.cfg ������ ���� Tag name�� value�� �����Ͽ� ��ü Tag Liat ��� ��*/
/*   ����ڰ� ��ȸ�ϰ� ���� Tag�� ��ȣ�� �Է¹޾� ����ϴ� ���α׷�			*/
/****************************************************************************/


/*
argc: argument count. �Լ��� �޴� ������ ����
���α׷��� ������ �� ������ �� "����� �ɼ�"�� "����"�� ����Ǵ� ��
argv[]: argument vector. ������ ����. argv[0] = ���� ������ ��� �� �̸�
���α׷��� ������ �� ������ �� "����� �ɼ��� ���ڿ���"�� ������ ����Ǵ� �迭

strtok: ���ڿ� �и�. ù ��° ���ڰ� NULL�� ��� �ش� ���ڿ����� ������ �������� Ž���Ͽ� �и�
strcmp: ���ڿ� ��. �� ���ڿ��� ���� ��� 0�� ��ȯ
*/


typedef struct tagInfo {		// tag�� ������ ������ ����ü
	char name[32];	// tag �̸� ex) SYSTEM, INFORMATION_SAVE...
	char val[32];	// tag �� ex) YES, LOAD, IO/iodefine.io...
}TAGINFO;


int main(int argc, char* argv[]) {
	// ���� �����
	int i;	// for�� ������ ����� ����

	FILE *pFile;		// ������ ��ġ�� �޴� pointer
	char line[100];		// ���� �� �ٸ����� ������ �����ϴ� line buffer

	char seps[] = " ,\t\n";	// �Ľ��� �� �����ڰ� �Ǵ� ���ڵ�
	char *token;			// �Ľ��� ���ڸ� �޴� pointer

	char fstTag[17][32] =	// Startup.cfg File�� ���� ��� �� 1st Tag
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
	TAGINFO tagList[17];	// ���Ͽ� ���� tag�� ������ ������ ����ü

	int tagNum; // ����ڿ��� ���� �±� ��ȣ

	for (i = 0; i<sizeof(tagList) / 64; i++) {	// ��� tagList ����ü ����� ���Ͽ� " "���� �ʱ�ȭ
		strcpy(tagList[i].name, " ");
		strcpy(tagList[i].val, " ");
	}

	// �Լ� ���� �Է� Ȯ��
	if (argv[1]) {								// �Լ� ���� �� ù ��° ���ڸ� �޾��� �� 
		printf("argv[%d] = %s\n", 1, argv[1]);	// �� ���� �ֿܼ� ���
	}
	else {									// ���ڰ� ���� ��
		printf("No parameters\n");		// ���� �޼��� ���
		return -1;
	}


	// File open�� �� ����Ǿ����� Ȯ��
	if (pFile = fopen(argv[1], "r")) {		// main �Լ��� �� ��° ���ڷ� ���� ������ �б� ���� ������ ��
		printf("File open success\n\n");	// ���� �޼��� ���
	}
	else {									// main �Լ��� �� ��° ���ڷ� ���� ������ ���� �������� ��
		printf("File open failed\n\n");		// ���� �޼��� ���
		return -1;
	}


	// File�� ������ �о� ����ü�� �����ϸ� �ֿܼ� ���
	while (!feof(pFile)) {	// ������ ���� �ƴ� ���
		if (fgets(line, sizeof(line), pFile) == NULL) {	// fgets�� �����Ͽ� line�� �� �� �� ���� ��, �� ��ȯ���� ���� ��� 
			break;						// �Լ� ������ ����
		}
		else if (line[0] == '#' || line[0] == '\n' || line[0] == '\t' || line[0] == ' ') {	// �ּ��̳� �� ������ ��� 
			continue;	// ������� �ʰ� �ݺ��� �����
		}
		else {			// ������ ��� (ó���� ���ڿ��� ������ ���)
			token = strtok(line, seps);	// line buffer�� ������ seps �����ڸ� �������� ������

			for (i = 0; i<sizeof(tagList) / 64; i++) {	// fstTag�� index ����
				strcpy(tagList[i].name, fstTag[i]);	// tag Name�� 2���� �迭�� ������ �̸� ����

				if (!strcmp(token, fstTag[i])) {	// �Ľ��Ͽ� token�� ����� ù ��° ���� fstTag[i]�� ���� ���
					printf("%d:", i + 1);		// �ش� ��ȣ�� �ݷ� ���
					token = strtok(NULL, seps);	// ���� �ܾ� �Ľ��Ͽ� ����
					printf("%s\n", token);		// ���� �ܾ�(val)�� ���
					strcpy(tagList[i].val, token); // ����ü�� ����
				}
			}
		}
	}

	fclose(pFile);	// ���� �ݱ�


					// ����ڿ��� ��ȸ�� Tag �ε����� �޾� �ش� �� ���
	while (1) {	// ����ڿ��� ��ȣ�� �Է¹޾� ��ȸ�ϰ���� ��ȣ�� �Է¹޾� ����ϴ� �κ�
		printf("\n\n\n1~17 �� ��ȸ�ϰ� ���� Tag ��ȣ�� �Է��ϼ��� (0: ����): ");	// �Է¹��� ���ڿ� ���� ����
		scanf("%d", &tagNum);	// �Է¹��� ���ڸ� ����

		if (tagList[tagNum - 1].val[0] == ' ') {	// �ش� �ε����� ���� �Էµ��� �ʾ��� ��� (val ����� ù ��° ���� �ʱⰪ�� ������ �˻�)  
			printf("\n�ش� �ε����� Tag�� ������ ���� �����ϴ�.\n");	// ���� �޼��� ���
		}
		else if ((0<tagNum) && (tagNum<18)) {		// 1~17 ������ ���� �Է¹��� ���
			printf("\n%d:%s\n", tagNum, tagList[tagNum - 1].val);		// �ش� �ε����� �� ���
		}
		else if (tagNum == 0) {	// 0�� �Է¹��� ���
			return 0;			// ���α׷� ����
		}
		else {	// ������ ��� (1~17 ������ ���� �Է����� �ʾ��� ���)
			printf("\n��ȿ���� ���� ��ȣ�Դϴ�.\n");	// ���� �޼��� ���
		}
	}
}