/*creation error �߻�*/
#include <stdio.h>
#include <tchar.h>
#include <Windows.h>

#define DIR_LEN MAX_PATH+1

int _tmain(int argc, TCHAR* argv[])
{
	STARTUPINFO si={0,}; // ����ü ���� ����� ���ÿ� 0���� �ʱ�ȭ. ���μ����� �Ӽ��� �������ϴ� �뵵�� ����ü. 0���� �ʱ�ȭ�� �ʿ�.
	PROCESS_INFORMATION pi; //���� �����Ǵ� ���μ��� ���� ����.

	/*�����ϴ� ���μ����� �Ӽ�*/
	si.cb=sizeof(si); //����ü ������ ũ��
	si.dwFlags=STARTF_USEPOSITION | STARTF_USESIZE;//�̹� ������ ����� ��(����) �о����
	/*STARTF_USERPOSITION�� dwX�� dwY�� ���� ����.
	STARTF_USESIZE �� dwXSize�� dwYSize�� ���� ����
	����ü ����� ���� �����Ǿ� �ִ��� STARTF_USEPOSITION�� STARTF_USESIZE�� ������ �ǹ̰� ����.*/
	si.dwX=100; //���μ��� �������� x��ǥ
	si.dwY=200; //���μ��� �������� y��ǥ
	si.dwXSize=300; //���μ��� �������� ���� ����
	si.dwYSize=200; //���μ��� �������� ���� ����
	si.lpTitle=_T("I am a boy!");//�ܼ� �������� Ÿ��Ʋ �� ����

	TCHAR command[] = _T("AdderProcess.exe 10 20");
	TCHAR cDir[DIR_LEN];
	BOOL state;

	GetCurrentDirectory(DIR_LEN, cDir); // ���� ���丮 Ȯ��
	_fputts(cDir, stdout);
	_fputts(_T("\n"), stdout);

	SetCurrentDirectory(_T("E:\\workspace\\test"));

	GetCurrentDirectory(DIR_LEN, cDir);
	_fputts(cDir, stdout);
	_fputts(_T("\n"), stdout);

	state = CreateProcess( //���μ��� ����
		NULL,			//�������� �̸�
		command,			//main �Լ��� ���޵� ���ڿ�
		NULL, NULL, TRUE,
		CREATE_NEW_CONSOLE, //���μ��� ���� �� ���ο� �ܼ� �����찡 ���������� ����.0�� �����ϸ� x. �ܼ� ��� ���α׷��� �ƴϸ� ���ǹ�.
		NULL,NULL,&si,&pi
		);//CreateProcess

	if(state!=0)
		_fputts(_T("Creation OK! \n"), stdout);
	else
		_fputts(_T("Creation Error! \n"), stdout);

	return 0;
}