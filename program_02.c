#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <string.h>

int main() {
	printf("-------------------------\n메시지를 숨격보자!!\n-------------------------\n\n");
	printf("숨길 메세지를 영어로 입력하시오 :\n");
	FILE* fo = fopen("sample3.bmp", "rb");
	FILE* fw = fopen("output.bmp", "wb");

	if (fo == NULL || fw == NULL) {
		printf("File open failed\n");
		return 1;

	}

	//파일 사이즈
	fgetc(fo);
	fgetc(fo);

	int FILESIZE = 0;
	fread(&FILESIZE, sizeof(int), 1, fo);


	//5-9 BYTE 패스
	fgetc(fo); fgetc(fo); fgetc(fo); fgetc(fo);

	//픽셀스타트지점 읽기
	int PIXELSTART = 0;
	fread(&PIXELSTART, sizeof(int), 1, fo);


	rewind(fo);

	char c;
	//픽셀시작점까지 스킵
	for (int i = 0; i < PIXELSTART; i++) {
		c = fgetc(fo);
		fputc(c, fw);
	}

	//각 픽셀 보이기

	int cnt = 0;
	char message[500];
	fgets(message, sizeof(message), stdin);
	message[strlen(message) - 1] = '\0'; // 문자  끝 지정
	int length = strlen(message); //문자열 길이 파악
	char i, j, k;
	char s;
	for (int a = PIXELSTART; a < FILESIZE; a += 4) { //픽셀 시작점부터 파일 크기까지 4byte씩 도는데
		i = fgetc(fo);
		j = fgetc(fo);
		k = fgetc(fo);
		if (cnt <= length - 1) { //문자열을 투명도에 집어넣기
			s = message[cnt]; //한 문자씩 가져오기 
			cnt++;
			fgetc(fo);// 단지 pass
		}
		else {                 //문자열 다 넣었으면 나머지 투명도 부분은 그대로 가져오기
			s = fgetc(fo);
		}
		fwrite(&i, 1, 1, fw);
		fwrite(&j, 1, 1, fw);
		fwrite(&k, 1, 1, fw);
		fwrite(&s, 1, 1, fw); //출력파일 투명도에 집어넣기
	}
	fclose(fo);
	fclose(fw);

	return 0;
}