#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <string.h>

int main() {
	printf("-------------------------\n�޽����� ���ݺ���!!\n-------------------------\n\n");
	printf("���� �޼����� ����� �Է��Ͻÿ� :\n");
	FILE* fo = fopen("sample3.bmp", "rb");
	FILE* fw = fopen("output.bmp", "wb");

	if (fo == NULL || fw == NULL) {
		printf("File open failed\n");
		return 1;

	}

	//���� ������
	fgetc(fo);
	fgetc(fo);

	int FILESIZE = 0;
	fread(&FILESIZE, sizeof(int), 1, fo);


	//5-9 BYTE �н�
	fgetc(fo); fgetc(fo); fgetc(fo); fgetc(fo);

	//�ȼ���ŸƮ���� �б�
	int PIXELSTART = 0;
	fread(&PIXELSTART, sizeof(int), 1, fo);


	rewind(fo);

	char c;
	//�ȼ����������� ��ŵ
	for (int i = 0; i < PIXELSTART; i++) {
		c = fgetc(fo);
		fputc(c, fw);
	}

	//�� �ȼ� ���̱�

	int cnt = 0;
	char message[500];
	fgets(message, sizeof(message), stdin);
	message[strlen(message) - 1] = '\0'; // ����  �� ����
	int length = strlen(message); //���ڿ� ���� �ľ�
	char i, j, k;
	char s;
	for (int a = PIXELSTART; a < FILESIZE; a += 4) { //�ȼ� ���������� ���� ũ����� 4byte�� ���µ�
		i = fgetc(fo);
		j = fgetc(fo);
		k = fgetc(fo);
		if (cnt <= length - 1) { //���ڿ��� ������ ����ֱ�
			s = message[cnt]; //�� ���ھ� �������� 
			cnt++;
			fgetc(fo);// ���� pass
		}
		else {                 //���ڿ� �� �־����� ������ ���� �κ��� �״�� ��������
			s = fgetc(fo);
		}
		fwrite(&i, 1, 1, fw);
		fwrite(&j, 1, 1, fw);
		fwrite(&k, 1, 1, fw);
		fwrite(&s, 1, 1, fw); //������� ������ ����ֱ�
	}
	fclose(fo);
	fclose(fw);

	return 0;
}