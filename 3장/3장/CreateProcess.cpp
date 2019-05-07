/*creation error 발생*/
#include <stdio.h>
#include <tchar.h>
#include <Windows.h>

#define DIR_LEN MAX_PATH+1

int _tmain(int argc, TCHAR* argv[])
{
	STARTUPINFO si={0,}; // 구조체 변수 선언과 동시에 0으로 초기화. 프로세스의 속성을 지정ㅇ하는 용도의 구조체. 0으로 초기화가 필요.
	PROCESS_INFORMATION pi; //새로 생성되는 프로세스 관련 정보.

	/*생성하는 프로세스의 속성*/
	si.cb=sizeof(si); //구조체 변수의 크기
	si.dwFlags=STARTF_USEPOSITION | STARTF_USESIZE;//이미 설정된 멤버의 값(정보) 읽어오기
	/*STARTF_USERPOSITION은 dwX와 dwY의 값을 참조.
	STARTF_USESIZE 은 dwXSize와 dwYSize의 값을 참조
	구조체 멤버의 값이 지정되어 있더라도 STARTF_USEPOSITION과 STARTF_USESIZE가 없으면 의미가 없다.*/
	si.dwX=100; //프로세스 윈도우의 x좌표
	si.dwY=200; //프로세스 윈도우의 y좌표
	si.dwXSize=300; //프로세스 윈도우의 가로 길이
	si.dwYSize=200; //프로세스 윈도우의 세로 길이
	si.lpTitle=_T("I am a boy!");//콘솔 윈도우의 타이틀 바 제목

	TCHAR command[] = _T("AdderProcess.exe 10 20");
	TCHAR cDir[DIR_LEN];
	BOOL state;

	GetCurrentDirectory(DIR_LEN, cDir); // 현재 디렉토리 확인
	_fputts(cDir, stdout);
	_fputts(_T("\n"), stdout);

	SetCurrentDirectory(_T("E:\\workspace\\test"));

	GetCurrentDirectory(DIR_LEN, cDir);
	_fputts(cDir, stdout);
	_fputts(_T("\n"), stdout);

	state = CreateProcess( //프로세스 생성
		NULL,			//실행파일 이름
		command,			//main 함수에 전달될 문자열
		NULL, NULL, TRUE,
		CREATE_NEW_CONSOLE, //프로세스 실행 시 새로운 콘솔 윈도우가 독립적으로 실행.0을 전달하면 x. 콘솔 기반 프로그램이 아니면 무의미.
		NULL,NULL,&si,&pi
		);//CreateProcess

	if(state!=0)
		_fputts(_T("Creation OK! \n"), stdout);
	else
		_fputts(_T("Creation Error! \n"), stdout);

	return 0;
}