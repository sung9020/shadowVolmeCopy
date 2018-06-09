// volume_shadow_util.cpp : 구현 파일입니다.
//

#include "stdafx.h"
#include "shadow_util.h"
#include "volume_shadow_util.h"
#include "afxdialogex.h"
#include "backup_timer.h"
#include <iostream>
#include <fstream>
#include <vector>
#include <string>

// volume_shadow_util 대화 상자입니다.

IMPLEMENT_DYNAMIC(volume_shadow_util, CDialogEx)

	volume_shadow_util::volume_shadow_util(CWnd* pParent /*=NULL*/)
	: CDialogEx(volume_shadow_util::IDD, pParent)

{

}

volume_shadow_util::~volume_shadow_util()
{

}

void volume_shadow_util::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Radio(pDX, IDC_RADIO1, m_radio);
	DDX_Control(pDX, IDC_LIST3, volume_list);
}


BEGIN_MESSAGE_MAP(volume_shadow_util, CDialogEx)
	ON_BN_CLICKED(IDC_BUTTON1, &volume_shadow_util::OnBnClickedButton1)
	ON_BN_CLICKED(IDC_BUTTON2, &volume_shadow_util::OnBnClickedButton2)
	ON_BN_CLICKED(IDC_BUTTON4, &volume_shadow_util::OnBnClickedButton4)
	ON_BN_CLICKED(IDC_BUTTON3, &volume_shadow_util::OnBnClickedButton3)
	ON_BN_CLICKED(IDC_BUTTON5, &volume_shadow_util::OnBnClickedButton5)
	
	ON_BN_CLICKED(IDC_BUTTON6, &volume_shadow_util::OnBnClickedButton6)

END_MESSAGE_MAP()


// volume_shadow_util 메시지 처리기입니다.
BOOL volume_shadow_util::OnInitDialog()
{
	USES_CONVERSION;
	CDialog::OnInitDialog();

	volume_list.InsertColumn(0,"번호", LVCFMT_CENTER, 50, -1);
	volume_list.InsertColumn(1,"누적넘버",LVCFMT_CENTER,100,-1);
	volume_list.InsertColumn(2,"드라이브",LVCFMT_CENTER,100,-1);
	volume_list.InsertColumn(3,"생성 날짜",LVCFMT_CENTER,150,-1);
	shadow_prop s_prop;
	HANDLE hFileHandle = new HANDLE;
	WIN32_FIND_DATAW find_data;
	//	WCHAR *path;
	CString sid, pid, result, c_date, drive, d_object;
	WCHAR buf[100];
	wifstream input;




	txt_C_count= 0;
	txt_D_count= 0;
	txt_F_count = 0;

	hFileHandle = FindFirstFileW(L"C:\\Backup\\*_sid.txt",&find_data);
	if(hFileHandle != INVALID_HANDLE_VALUE)
	{
		if(wcsncmp(find_data.cFileName,L"C",1) == 0)
		{		

			wsprintfW(buf,L"C:\\Backup\\C_%d_sid.txt",txt_C_count);
			input.open(buf,ios::binary);

			input.seekg(0,ios::end);
			int length = (int)input.tellg(); // 현재위치 확인
			input.seekg(0, ios::beg);
			WCHAR* bstr1 = new WCHAR[length];

			input.read(&bstr1[0],length);
			bstr1[length-2]  = '\0';
			input.close();
			Vss_class.vss_init();
			s_prop =  Vss_class.vss_query(bstr1);
			delete[] bstr1;
			CString drive = wchar_to_CString(L"C:");
			CString c_date = wchar_to_CString(s_prop.create_date);
			insertitems(volume_list,txt_C_count,drive, c_date);
			txt_C_count++;


		}
		else if(wcsncmp(find_data.cFileName,L"D",1) == 0)
		{

			wsprintfW(buf,L"C:\\Backup\\D_%d_sid.txt",txt_D_count);
			input.open(buf,ios::binary);

			input.seekg(0,ios::end);
			int length = (int)input.tellg(); // 현재위치 확인
			input.seekg(0, ios::beg);
			WCHAR* bstr1 = new WCHAR[length];
			input.read(&bstr1[0],length);
			bstr1[length-2]  = '\0';
			input.close();
			Vss_class.vss_init();		
			s_prop =  Vss_class.vss_query(bstr1);
			delete[] bstr1;
			CString drive = wchar_to_CString(L"D:");
			CString c_date = wchar_to_CString(s_prop.create_date);
			insertitems(volume_list,txt_D_count,drive, c_date);

			txt_D_count++;
		}
		else if(wcsncmp(find_data.cFileName,L"F",1) == 0)
		{
			wsprintfW(buf,L"C:\\Backup\\F_%d_sid.txt",txt_F_count);
			input.open(buf, ios::binary);

			input.seekg(0,ios::end);
			int length = (int)input.tellg(); // 현재위치 확인
			input.seekg(0, ios::beg);
			WCHAR* bstr1 = new WCHAR[length];
			input.read(&bstr1[0],length);
			bstr1[length-2] = '\0';
			input.close();
			Vss_class.vss_init();
			s_prop =  Vss_class.vss_query(bstr1);
			delete[] bstr1;
			CString drive = wchar_to_CString(L"F:");
			CString c_date = wchar_to_CString(s_prop.create_date);
			insertitems(volume_list,txt_F_count,drive, c_date);

			txt_F_count++;


		}


		while(FindNextFileW(hFileHandle,&find_data))
		{
			if(wcsncmp(find_data.cFileName,L"C",1) == 0)
			{
				wsprintfW(buf,L"C:\\Backup\\C_%d_sid.txt",txt_C_count);
				input.open(buf,ios::binary);
				input.seekg(0,ios::end);
				int length = (int)input.tellg(); // 현재위치 확인
				input.seekg(0, ios::beg);
				WCHAR* bstr1 = new WCHAR[length];

				input.read(&bstr1[0],length);
				bstr1[length-2]  = '\0';
				input.close();
				Vss_class.vss_init();
				s_prop =  Vss_class.vss_query(bstr1);
				delete[] bstr1;
				CString drive = wchar_to_CString(L"C:");
				CString c_date = wchar_to_CString(s_prop.create_date);
				insertitems(volume_list,txt_C_count,drive, c_date);

				txt_C_count++;
			}
			else if(wcsncmp(find_data.cFileName,L"D",1) == 0)
			{
				wsprintfW(buf,L"C:\\Backup\\D_%d_sid.txt",txt_D_count);
				input.open(buf,ios::binary);
				input.seekg(0,ios::end);
				int length = (int)input.tellg(); // 현재위치 확인
				input.seekg(0, ios::beg);
				WCHAR* bstr1 = new WCHAR[length];

				input.read(&bstr1[0],length);
				bstr1[length-2]  = '\0';
				input.close();
				Vss_class.vss_init();
				s_prop =  Vss_class.vss_query(bstr1);
				delete[] bstr1;
				CString drive = wchar_to_CString(L"D:");
				CString c_date = wchar_to_CString(s_prop.create_date);
				insertitems(volume_list,txt_D_count,drive, c_date);
				txt_D_count++;
			}
			else if(wcsncmp(find_data.cFileName,L"F",1) == 0)
			{
				wsprintfW(buf,L"C:\\Backup\\F_%d_sid.txt",txt_F_count);
				input.open(buf,ios::binary);
				input.seekg(0,ios::end);
				int length = (int)input.tellg(); // 현재위치 확인
				input.seekg(0, ios::beg);
				WCHAR* bstr1 = new WCHAR[length];
				input.read(&bstr1[0],length);
				bstr1[length-2]  = '\0';
				input.close();
				Vss_class.vss_init();
				s_prop =  Vss_class.vss_query(bstr1);
				delete[] bstr1;
				CString drive = wchar_to_CString(L"F:");
				CString c_date = wchar_to_CString(s_prop.create_date);
				insertitems(volume_list,txt_F_count,drive, c_date);
				txt_F_count++;
			}



		}


	}

	return true;
}
void volume_shadow_util::OnBnClickedButton1() // 백업 타이머 시작
{
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다. 
	//백업시간 설정
	backup_timer log;

	log.DoModal();

	update_list();

}


void volume_shadow_util::OnBnClickedButton2()  //볼륨 카피 시작 
{
	CWnd cwnd;
	UpdateData(true);
	shadow_prop s_prop;
	CString sid, pid, result, c_date, drive, d_object;

	switch (m_radio)
	{
	case 0: //c 드라이브
		{
			char drive_path[MAX_PATH] = "C:\\";
			Vss_class.vss_init();
			Vss_class.vss_make(drive_path,txt_C_count);
			Vss_class.vss_snapshot(drive_path,txt_C_count);
			s_prop =  Vss_class.vss_shadowcopylist();
			CString drive = wchar_to_CString(L"C:");
			CString c_date = wchar_to_CString(s_prop.create_date);
			insertitems(volume_list,txt_C_count,drive,c_date);
			Vss_class.vss_exit();

			txt_C_count++;


			break;
		}
	case 1: //d 드라이브 
		{

			char drive_path[MAX_PATH] = "D:\\";
			Vss_class.vss_init();
			Vss_class.vss_make(drive_path,txt_D_count);
			Vss_class.vss_snapshot(drive_path,txt_D_count);
			s_prop =  Vss_class.vss_shadowcopylist();
			CString drive = wchar_to_CString(L"D:");
			CString c_date = wchar_to_CString(s_prop.create_date);
			insertitems(volume_list,txt_D_count,drive,c_date);
			Vss_class.vss_exit();
			txt_D_count++;

			//Vss_class.vss_filelist();
			/*
			sid = wchar_to_CString(s_prop.sid);
			pid = wchar_to_CString(s_prop.pid);
			c_date = wchar_to_CString(s_prop.create_date);
			d_object = wchar_to_CString(s_prop.d_object);
			drive = drive_path;
			//	result += '['+ drive + "드라이브 : " + sid+ '|' +'|'+ c_date;
			CString str;
			str.Format(_T("%d"),(xml_D_count+1));
			result += str + "번째" +'['+ drive + "드라이브 : " +  d_object;
			AddStringEx(volume_list,result);
			*/
			break;
		}
	case 2: //f 드라이브 
		{
			char drive_path[MAX_PATH] = "F:\\";
			Vss_class.vss_init();
			Vss_class.vss_make(drive_path,txt_F_count);
			Vss_class.vss_snapshot(drive_path,txt_F_count);
			s_prop =  Vss_class.vss_shadowcopylist();
			CString drive = wchar_to_CString(L"F:");
			CString c_date = wchar_to_CString(s_prop.create_date);
			insertitems(volume_list,txt_F_count,drive,c_date);

			txt_F_count++;

			break;
		}
	default:
		{
			break;
		}
	}
}


void volume_shadow_util::OnBnClickedButton4()	//카피 삭제 시작 
{	USES_CONVERSION;

int select = GetIndex();
// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.
if(select != -1 )
{
	CString num, drive;
	WCHAR buf[100];
	num = volume_list.GetItemText(select,1); // 누적넘버
	drive = volume_list.GetItemText(select,2); // 드라이브
	int m_num = _ttoi(num);
	wifstream input;
	//		WCHAR* bstr1;
	shadow_prop prop;
	LONG isdelete;
	int total = volume_list.GetItemCount();
	int compare_c = 0;
	int compare_d = 0;
	int compare_f = 0;
	HANDLE hFileHandle;
	WIN32_FIND_DATAW find_data;
	shadow_prop s_prop;

	hFileHandle = FindFirstFileW(L"C:\\Backup\\*_sid.txt",&find_data);
	if(hFileHandle != INVALID_HANDLE_VALUE)
	{
		if(wcsncmp(find_data.cFileName,L"C",1) == 0)
		{		
			compare_c++;

		}
		else if(wcsncmp(find_data.cFileName,L"D",1) == 0)
		{
			compare_d++;		
		}
		else if(wcsncmp(find_data.cFileName,L"F",1) == 0)
		{
			compare_f++;


		}
		while(FindNextFileW(hFileHandle,&find_data))
		{
			if(wcsncmp(find_data.cFileName,L"C",1) == 0)
			{
				compare_c++;
			}
			else if(wcsncmp(find_data.cFileName,L"D",1) == 0)
			{
				compare_d++;
			}
			else if(wcsncmp(find_data.cFileName,L"F",1) == 0)
			{
				compare_f++;
			}



		}
		
	}


	if(wcscmp(T2W(drive.GetBuffer(0)),L"C:")== 0)
	{
	if(select+1 == compare_c)
	{
		wsprintfW(buf,L"C:\\Backup\\C_%d_sid.txt",m_num);

		input.open(buf,ios::binary);
		input.seekg(0,ios::end);
		int length = (int)input.tellg(); // 현재위치 확인
		input.seekg(0, ios::beg);
		WCHAR* bstr1 = new WCHAR[length];

		input.read(&bstr1[0],length);
		bstr1[length-2]  = '\0';
		input.close();
		Vss_class.vss_init();
		prop = Vss_class.vss_query(bstr1);
		delete[] bstr1;
		isdelete = Vss_class.vss_delete(prop.sid);
		if(isdelete>0)
		{
			volume_list.DeleteItem(select);

			DeleteFileW(buf);
			AfxMessageBox("삭제 완료!", MB_OK | MB_ICONINFORMATION);
			update_list();

		}
	}
	else 
	{
			AfxMessageBox("삭제 불가!", MB_OK | MB_ICONWARNING);
	}
	}
	else if(wcscmp(T2W(drive.GetBuffer(0)),L"D:")== 0)
	{
		if(select+1 == compare_d)
	{
		wsprintfW(buf,L"C:\\Backup\\D_%d_sid.txt",m_num);

		input.open(buf,ios::binary);
		input.seekg(0,ios::end);
		int length = (int)input.tellg(); // 현재위치 확인
		input.seekg(0, ios::beg);
		WCHAR* bstr1 = new WCHAR[length];

		input.read(&bstr1[0],length);
		bstr1[length-2]  = '\0';
		input.close();
		Vss_class.vss_init();
		prop = Vss_class.vss_query(bstr1);
		delete[] bstr1;
		isdelete = Vss_class.vss_delete(prop.sid);
		if(isdelete>0)
		{
			volume_list.DeleteItem(select);

			DeleteFileW(buf);
			update_list();
		}
	}
	else
	{
		AfxMessageBox("삭제 불가!", MB_OK | MB_ICONWARNING);
	}
	}
	else if(wcscmp(T2W(drive.GetBuffer(0)),L"F:")== 0)
	{
		if(select+1 == compare_f)
	{
		wsprintfW(buf,L"C:\\Backup\\F_%d_sid.txt",m_num);

		input.open(buf,ios::binary);
		input.seekg(0,ios::end);
		int length = (int)input.tellg(); // 현재위치 확인
		input.seekg(0, ios::beg);
		WCHAR* bstr1 = new WCHAR[length];

		input.read(&bstr1[0],length);
		bstr1[length-2]  = '\0';
		input.close();
		Vss_class.vss_init();
		prop = Vss_class.vss_query(bstr1);
		delete[] bstr1;
		isdelete =Vss_class.vss_delete(prop.sid);
		if(isdelete>0)
		{
			volume_list.DeleteItem(select);

			DeleteFileW(buf);
			AfxMessageBox("삭제 완료!", MB_OK | MB_ICONWARNING);
			update_list();
		}
	}
	else 
	{
			AfxMessageBox("삭제 불가!", MB_OK | MB_ICONWARNING);
	}

	}
}
}
void volume_shadow_util::insertitems(CListCtrl& volume_list, int xml_count, CString drive, CString c_date)
{
	int total_count = volume_list.GetItemCount();
	if(total_count != 0)
	{
		volume_list.InsertItem(total_count,"");
		CString total_count_s;
		total_count_s.Format(_T("%d"),(total_count ));
		volume_list.SetItemText(total_count ,0,total_count_s);
		CString Num;
		Num.Format(_T("%d"),(xml_count));
		volume_list.SetItemText(total_count,1,Num);
		volume_list.SetItemText(total_count,2,drive);
		volume_list.SetItemText(total_count,3,c_date);
	}
	else 
	{
		volume_list.InsertItem(total_count ,"");
		CString total_count_s;
		total_count_s.Format(_T("%d"),(total_count));
		volume_list.SetItemText(total_count,0,total_count_s);
		CString Num;
		Num.Format(_T("%d"),(xml_count));
		volume_list.SetItemText(total_count,1,Num);
		volume_list.SetItemText(total_count,2,drive);
		volume_list.SetItemText(total_count,3,c_date);
	}

}
int volume_shadow_util::GetIndex()
{
	int nSelectedItem = volume_list.GetNextItem( -1, LVNI_SELECTED );
	CString strKey = volume_list.GetItemText(nSelectedItem, 0);
	if ( strKey == "")
	{
		return -1;
	}
	return nSelectedItem;
} 


void volume_shadow_util::OnBnClickedButton3()  //파일 시스템 뷰 시작
{
	USES_CONVERSION;

	int select = GetIndex();
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.
	if(select != -1 )
	{
		CString num, drive;
		WCHAR buf[100];
		num = volume_list.GetItemText(select,1); // 누적넘버
		drive = volume_list.GetItemText(select,2); // 드라이브
		int m_num = _ttoi(num);
		wifstream input;
		//		WCHAR* bstr1;
		shadow_prop prop;
		//		LONG isdelete;
		if(wcscmp(T2W(drive.GetBuffer(0)),L"C:")== 0)
		{
			wsprintfW(buf,L"C:\\Backup\\C_%d_sid.txt",m_num);

			input.open(buf,ios::binary);
			input.seekg(0,ios::end);
			int length = (int)input.tellg(); // 현재위치 확인
			input.seekg(0, ios::beg);
			WCHAR* bstr1 = new WCHAR[length];

			input.read(&bstr1[0],length);
			bstr1[length-2]  = '\0';
			input.close();
			Vss_class.vss_init();
			prop = Vss_class.vss_query(bstr1);
			delete[] bstr1;
			FILE_Tree directory;
			Vss_class.vss_filelist(directory,&prop);
			file_list_view log;
			log.tree = &directory;
			log.drive = L"C:";
			log.prop = &prop;
			log.DoModal();
			directory.freetree(directory.root);
		}
		else if(wcscmp(T2W(drive.GetBuffer(0)),L"D:")== 0)
		{
			wsprintfW(buf,L"C:\\Backup\\D_%d_sid.txt",m_num);

			input.open(buf,ios::binary);
			input.seekg(0,ios::end);
			int length = (int)input.tellg(); // 현재위치 확인
			input.seekg(0, ios::beg);
			WCHAR* bstr1 = new WCHAR[length];

			input.read(&bstr1[0],length);
			bstr1[length-2]  = '\0';
			input.close();
			Vss_class.vss_init();
			prop = Vss_class.vss_query(bstr1);
			delete[] bstr1;
			FILE_Tree directory;
			Vss_class.vss_filelist(directory,&prop);
			file_list_view log;
			log.tree = &directory;
			log.drive = L"D:";
			log.prop = &prop;
			log.DoModal();
			directory.freetree(directory.root);
		}
		else if(wcscmp(T2W(drive.GetBuffer(0)),L"F:")== 0)
		{
			wsprintfW(buf,L"C:\\Backup\\F_%d_sid.txt",m_num);

			input.open(buf,ios::binary);
			input.seekg(0,ios::end);
			int length = (int)input.tellg(); // 현재위치 확인
			input.seekg(0, ios::beg);
			WCHAR* bstr1 = new WCHAR[length];

			input.read(&bstr1[0],length);
			bstr1[length-2]  = '\0';
			input.close();
			Vss_class.vss_init();
			prop = Vss_class.vss_query(bstr1);
			delete[] bstr1;
			//	Vss_class.vss_expose(bstr1,&prop);
			FILE_Tree directory;
			Vss_class.vss_filelist(directory,&prop);
			file_list_view log;
			log.tree = &directory;
			log.drive = L"F:";
			log.prop = &prop;
			log.DoModal();
			directory.freetree(directory.root);
		}


	}




}


void volume_shadow_util::OnBnClickedButton5() 	//볼륨 파일 복사
{
	USES_CONVERSION;


	ITEMIDLIST        *pidlBrowse;
	WCHAR    pszPathname[MAX_PATH];
	BROWSEINFOW BrInfo;
	BrInfo.hwndOwner = NULL; //GetSafeHwnd();
	BrInfo.pidlRoot = NULL;
	memset( &BrInfo, 0, sizeof(BrInfo) );
	BrInfo.pszDisplayName = pszPathname;
	BrInfo.lpszTitle = L"복사할 디렉토리를 선택하세요";
	BrInfo.ulFlags = BIF_RETURNONLYFSDIRS;


	// 다이얼로그를 띄우기
	pidlBrowse = ::SHBrowseForFolderW(&BrInfo);   


	if( pidlBrowse != NULL)
	{
		// 패스를 얻어옴
		::SHGetPathFromIDListW(pidlBrowse, pszPathname);   
	}
	if(pidlBrowse != NULL)
	{
		int select = GetIndex();
		// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.
		if(select != -1 )
		{
			CString num, drive;
			WCHAR buf[100];
			num = volume_list.GetItemText(select,1); // 누적넘버
			drive = volume_list.GetItemText(select,2); // 드라이브
			int m_num = _ttoi(num);
			wifstream input;
			//		WCHAR* bstr1;
			shadow_prop prop;
			//		LONG isdelete;
			if(wcscmp(T2W(drive.GetBuffer(0)),L"C:")== 0)
			{
				switch(AfxMessageBox("선택 볼륨의 파일이 해당 폴더로 복사됩니다", MB_OKCANCEL | MB_ICONQUESTION))
				{
				case IDOK:
					{
						drive.ReleaseBuffer();
						wsprintfW(buf,L"C:\\Backup\\C_%d_sid.txt",m_num);
						input.open(buf,ios::binary);
						input.seekg(0,ios::end);
						int length = (int)input.tellg(); // 현재위치 확인
						input.seekg(0, ios::beg);
						WCHAR* bstr1 = new WCHAR[length];
						input.read(&bstr1[0],length);
						bstr1[length-2]  = '\0';

						input.close();
						Vss_class.vss_init();
						prop = Vss_class.vss_query(bstr1);
						delete[] bstr1;
						volume_Copy(prop.d_object,pszPathname);
						AfxMessageBox("복사 완료!", MB_OK | MB_ICONINFORMATION);
						break;
					}
				case IDCANCEL:
					{
						drive.ReleaseBuffer();
						break;
					}
				}
			}

			else if(wcscmp(T2W(drive.GetBuffer(0)),L"D:")== 0)
			{
				switch(AfxMessageBox("선택 볼륨의 파일이 해당 폴더로 복사됩니다", MB_OKCANCEL | MB_ICONQUESTION))
				{
				case IDOK:
					{
						drive.ReleaseBuffer();
						wsprintfW(buf,L"C:\\Backup\\D_%d_sid.txt",m_num);
						input.open(buf,ios::binary);
						input.seekg(0,ios::end);
						int length = (int)input.tellg(); // 현재위치 확인
						input.seekg(0, ios::beg);
						WCHAR* bstr1 = new WCHAR[length];
						input.read(&bstr1[0],length);
						bstr1[length-2]  = '\0';
						input.close();
						Vss_class.vss_init();
						prop = Vss_class.vss_query(bstr1);
						delete[] bstr1;
						volume_Copy(prop.d_object,pszPathname);
						AfxMessageBox("복사 완료!", MB_OK | MB_ICONINFORMATION);
						break;
					}
				case IDCANCEL:
					{
						drive.ReleaseBuffer();
						break;
					}
				}
			}
			else if(wcscmp(T2W(drive.GetBuffer(0)),L"F:")== 0)
			{
				switch(AfxMessageBox("선택 볼륨의 파일이 해당 폴더로 복사됩니다", MB_OKCANCEL | MB_ICONQUESTION))
				{
				case IDOK:
					{
						drive.ReleaseBuffer();
						wsprintfW(buf,L"C:\\Backup\\F_%d_sid.txt",m_num);
						input.open(buf,ios::binary);
						input.seekg(0,ios::end);
						int length = (int)input.tellg(); // 현재위치 확인
						input.seekg(0, ios::beg);
						WCHAR* bstr1 = new WCHAR[length];
						input.read(&bstr1[0],length);
						bstr1[length-2]  = '\0';
						input.close();
						Vss_class.vss_init();
						prop = Vss_class.vss_query(bstr1);
						delete[] bstr1;
						volume_Copy(prop.d_object,pszPathname);

						AfxMessageBox("복사 완료!", MB_OK | MB_ICONINFORMATION);
						break;
					}
				case IDCANCEL:
					{
						drive.ReleaseBuffer();
						break;
					}
				}
			}


		}

		// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.
	}
}




CString volume_shadow_util::wchar_to_CString(WCHAR* source)
{
	CString temp(source);
	CString result;
	result = temp;
	return result;
}




void volume_shadow_util::OnBnClickedButton6() // 카피 복원 시작 
{
	USES_CONVERSION;

	int select = GetIndex();
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.
	if(select != -1 )
	{
		CString num, drive;
		WCHAR buf[100];
		num = volume_list.GetItemText(select,1); // 누적넘버
		drive = volume_list.GetItemText(select,2); // 드라이브
		int m_num = _ttoi(num);
		wifstream input;
		//		WCHAR* bstr1;
		shadow_prop prop;
		//		LONG isdelete;
		if(wcscmp(T2W(drive.GetBuffer(0)),L"C:")== 0)
		{
			WCHAR drive_path[MAX_PATH] = L"C:\\";
			wsprintfW(buf,L"C:\\Backup\\C_%d_sid.txt",m_num);
			input.open(buf,ios::binary);
			input.seekg(0,ios::end);
			int length = (int)input.tellg(); // 현재위치 확인
			input.seekg(0, ios::beg);
			WCHAR* bstr1 = new WCHAR[length];

			input.read(&bstr1[0],length);
			bstr1[length-2]  = '\0';
			input.close();
			Vss_class.vss_init();
			prop = Vss_class.vss_query(bstr1);
			delete[] bstr1;
			volume_restore(prop.d_object,drive_path);
			AfxMessageBox("C: 복구완료!", MB_OK | MB_ICONINFORMATION);
		}
		else if(wcscmp(T2W(drive.GetBuffer(0)),L"D:")== 0)
		{
			WCHAR drive_path[MAX_PATH] = L"D:\\";
			wsprintfW(buf,L"C:\\Backup\\D_%d_sid.txt",m_num);

			input.open(buf,ios::binary);
			input.seekg(0,ios::end);
			int length = (int)input.tellg(); // 현재위치 확인
			input.seekg(0, ios::beg);
			WCHAR* bstr1 = new WCHAR[length];

			input.read(&bstr1[0],length);
			bstr1[length-2]  = '\0';
			input.close();
			Vss_class.vss_init();
			prop = Vss_class.vss_query(bstr1);
			delete[] bstr1;
			volume_restore(prop.d_object,drive_path);		
			AfxMessageBox("D: 복구완료!", MB_OK | MB_ICONINFORMATION);

		}
		else if(wcscmp(T2W(drive.GetBuffer(0)),L"F:")== 0)
		{
			WCHAR drive_path[MAX_PATH] = L"F:\\";
			wsprintfW(buf,L"C:\\Backup\\F_%d_sid.txt",m_num);

			input.open(buf,ios::binary);
			input.seekg(0,ios::end);
			int length = (int)input.tellg(); // 현재위치 확인
			input.seekg(0, ios::beg);
			WCHAR* bstr1 = new WCHAR[length];

			input.read(&bstr1[0],length);
			bstr1[length-2]  = '\0';
			input.close();
			Vss_class.vss_init();
			prop = Vss_class.vss_query(bstr1);
			delete[] bstr1;
			volume_restore(prop.d_object,drive_path);	
			AfxMessageBox("F: 복구완료!", MB_OK | MB_ICONINFORMATION);
		}


	}
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.
}

char* volume_shadow_util::ConvertUnicodeToMultybyte(WCHAR *strUnicode)
{
	int nLen = WideCharToMultiByte(CP_ACP,0,strUnicode,-1,NULL,0,NULL,NULL);
	char* pMultibyte = new char[nLen];
	memset(pMultibyte,0x00,(nLen)*sizeof(char));
	WideCharToMultiByte(CP_ACP,0,strUnicode,-1,pMultibyte,nLen,NULL,NULL);

	return pMultibyte;
}

DWORD CALLBACK volume_shadow_util::CopyProgressRoutine( 
	LARGE_INTEGER TotalFileSize, // total file size, in bytes 
	LARGE_INTEGER TotalBytesTransferred, 
	// total number of bytes transferred 
	LARGE_INTEGER StreamSize, // total number of bytes for this stream 
	LARGE_INTEGER StreamBytesTransferred, 
	// total number of bytes transferred for 
	// this stream 
	DWORD dwStreamNumber, // the current stream 
	DWORD dwCallbackReason, // reason for callback 
	HANDLE hSourceFile, // handle to the source file 
	HANDLE hDestinationFile, // handle to the destination file 
	LPVOID lpData // passed by CopyFileEx 
	) 
{ 
	//wprintf(L"[%%%I64u] TotalFileSize: %I64u, Transffered: %I64u\n", 
	TRACE("[%%%I64u] TotalFileSize: %I64u, Transffered: %I64u\n", 
		TotalBytesTransferred.QuadPart*100 / TotalFileSize.QuadPart, 
		TotalFileSize, TotalBytesTransferred);

	// nPos = (int)((double)TotalBytesTransferred.QuadPart / (double)TotalFileSize.QuadPart *100);

	//volume_shadow_util* self = (volume_shadow_util*)lpData;

	//self->SetSliderPos(nPos, self->m_nCurCnt, self->m_nTotalCnt);

	return PROGRESS_CONTINUE; 
}

BOOL volume_shadow_util::volume_restore(WCHAR *Src, WCHAR *pszPathname)
{
	HANDLE hHandle; 
	WIN32_FIND_DATAW find_data; 
	BOOL bResult=TRUE; 
	//	WCHAR fname[MAX_PATH]; 
	WCHAR WildCard[MAX_PATH]; 
	WCHAR SrcFile[MAX_PATH]; 
	WCHAR DestFile[MAX_PATH];
	wcscpy_s(WildCard,Src); 
	wcscat_s(WildCard, L"\\*.*"); 
	hHandle = FindFirstFileW(WildCard,&find_data);
	CreateDirectoryW(pszPathname,NULL);
	//미리 부모인 폴더를 만들어준다.
	if(hHandle == INVALID_HANDLE_VALUE)
		return false;
	while(bResult) 
	{

		wsprintfW(SrcFile, L"%s\\%s",Src,find_data.cFileName);
		wsprintfW(DestFile, L"%s\\%s",pszPathname,find_data.cFileName);
		if(find_data.dwFileAttributes & FILE_ATTRIBUTE_DIRECTORY) 
			//폴더면 재귀로 다시 들어간다.
		{
			if(wcscmp(find_data.cFileName,L".") && wcscmp(find_data.cFileName,L".."))
			{
				volume_restore(SrcFile,DestFile);
			}
		}
		else
		{
			//파일이면 복사한다. 
			MoveFileExW(SrcFile,DestFile,MOVEFILE_REPLACE_EXISTING | MOVEFILE_COPY_ALLOWED);
		}
		bResult = FindNextFileW(hHandle,&find_data);

	}

	FindClose(hHandle);

	return true;

}

BOOL volume_shadow_util::volume_Copy(WCHAR *Src, WCHAR *pszPathname)
{
	HANDLE hHandle; 
	WIN32_FIND_DATAW find_data; 
	BOOL bResult=TRUE; 
	//	WCHAR fname[MAX_PATH]; 
	WCHAR WildCard[MAX_PATH]; 
	WCHAR SrcFile[MAX_PATH]; 
	WCHAR DestFile[MAX_PATH];
	wcscpy_s(WildCard,Src); 
	wcscat_s(WildCard, L"\\*.*"); 
	hHandle = FindFirstFileW(WildCard,&find_data);
	CreateDirectoryW(pszPathname,NULL);
	if(hHandle == INVALID_HANDLE_VALUE)
		return false;
	while(bResult)
	{

		wsprintfW(SrcFile, L"%s\\%s",Src,find_data.cFileName);
		wsprintfW(DestFile, L"%s\\%s",pszPathname,find_data.cFileName);
		if(find_data.dwFileAttributes & FILE_ATTRIBUTE_DIRECTORY)
		{
			if(wcscmp(find_data.cFileName,L".") && wcscmp(find_data.cFileName,L".."))
			{
				volume_Copy(SrcFile,DestFile);
			}
		}
		else
		{
			CopyFileW(SrcFile,DestFile,false);
		}
		bResult = FindNextFileW(hHandle,&find_data);

	}

	FindClose(hHandle);

	return true;

}

void volume_shadow_util::update_list()
{
	USES_CONVERSION;


	shadow_prop s_prop;
	HANDLE hFileHandle = new HANDLE;
	WIN32_FIND_DATAW find_data;
	//	WCHAR *path;
	CString sid, pid, result, c_date, drive, d_object;
	WCHAR buf[100];
	wifstream input;

	volume_list.DeleteAllItems();

	txt_C_count = 0;
	txt_D_count = 0;
	txt_F_count = 0;

	hFileHandle = FindFirstFileW(L"C:\\Backup\\*_sid.txt",&find_data);
	if(hFileHandle != INVALID_HANDLE_VALUE)
	{
		if(wcsncmp(find_data.cFileName,L"C",1) == 0)
		{		

			wsprintfW(buf,L"C:\\Backup\\C_%d_sid.txt",txt_C_count);
			input.open(buf,ios::binary);

			input.seekg(0,ios::end);
			int length = (int)input.tellg(); // 현재위치 확인
			input.seekg(0, ios::beg);
			WCHAR* bstr1 = new WCHAR[length];

			input.read(&bstr1[0],length);
			bstr1[length-2]  = '\0';
			input.close();
			Vss_class.vss_init();
			s_prop =  Vss_class.vss_query(bstr1);
			delete[] bstr1;
			CString drive = wchar_to_CString(L"C:");
			CString c_date = wchar_to_CString(s_prop.create_date);
			insertitems(volume_list,txt_C_count,drive, c_date);
			txt_C_count++;


		}
		else if(wcsncmp(find_data.cFileName,L"D",1) == 0)
		{

			wsprintfW(buf,L"C:\\Backup\\D_%d_sid.txt",txt_D_count);
			input.open(buf,ios::binary);
			input.seekg(0,ios::end);
			int length = (int)input.tellg(); // 현재위치 확인
			input.seekg(0, ios::beg);
			WCHAR* bstr1 = new WCHAR[length];
			input.read(&bstr1[0],length);
			bstr1[length-2]  = '\0';
			input.close();
			Vss_class.vss_init();		
			s_prop =  Vss_class.vss_query(bstr1);
			delete[] bstr1;
			CString drive = wchar_to_CString(L"D:");
			CString c_date = wchar_to_CString(s_prop.create_date);
			insertitems(volume_list,txt_D_count,drive, c_date);

			txt_D_count++;
		}
		else if(wcsncmp(find_data.cFileName,L"F",1) == 0)
		{
			wsprintfW(buf,L"C:\\Backup\\F_%d_sid.txt",txt_F_count);
			input.open(buf, ios::binary);
			input.seekg(0,ios::end);
			int length = (int)input.tellg(); // 현재위치 확인
			input.seekg(0, ios::beg);
			WCHAR* bstr1 = new WCHAR[length];
			input.read(&bstr1[0],length);
			bstr1[length-2] = '\0';
			input.close();
			Vss_class.vss_init();
			s_prop =  Vss_class.vss_query(bstr1);
			delete[] bstr1;
			CString drive = wchar_to_CString(L"F:");
			CString c_date = wchar_to_CString(s_prop.create_date);
			insertitems(volume_list,txt_F_count,drive, c_date);

			txt_F_count++;


		}


		while(FindNextFileW(hFileHandle,&find_data))
		{
			if(wcsncmp(find_data.cFileName,L"C",1) == 0)
			{
				wsprintfW(buf,L"C:\\Backup\\C_%d_sid.txt",txt_C_count);
				input.open(buf,ios::binary);
				input.seekg(0,ios::end);
				int length = (int)input.tellg(); // 현재위치 확인
				input.seekg(0, ios::beg);
				WCHAR* bstr1 = new WCHAR[length];

				input.read(&bstr1[0],length);
				bstr1[length-2]  = '\0';
				input.close();
				Vss_class.vss_init();
				s_prop =  Vss_class.vss_query(bstr1);
				delete[] bstr1;
				CString drive = wchar_to_CString(L"C:");
				CString c_date = wchar_to_CString(s_prop.create_date);
				insertitems(volume_list,txt_C_count,drive, c_date);

				txt_C_count++;
			}
			else if(wcsncmp(find_data.cFileName,L"D",1) == 0)
			{
				wsprintfW(buf,L"C:\\Backup\\D_%d_sid.txt",txt_D_count);
				input.open(buf,ios::binary);
				input.seekg(0,ios::end);
				int length = (int)input.tellg(); // 현재위치 확인
				input.seekg(0, ios::beg);
				WCHAR* bstr1 = new WCHAR[length];

				input.read(&bstr1[0],length);
				bstr1[length-2]  = '\0';
				input.close();
				Vss_class.vss_init();
				s_prop =  Vss_class.vss_query(bstr1);
				delete[] bstr1;
				CString drive = wchar_to_CString(L"D:");
				CString c_date = wchar_to_CString(s_prop.create_date);
				insertitems(volume_list,txt_D_count,drive, c_date);
				txt_D_count++;
			}
			else if(wcsncmp(find_data.cFileName,L"F",1) == 0)
			{
				wsprintfW(buf,L"C:\\Backup\\F_%d_sid.txt",txt_F_count);
				input.open(buf,ios::binary);
				input.seekg(0,ios::end);
				int length = (int)input.tellg(); // 현재위치 확인
				input.seekg(0, ios::beg);
				WCHAR* bstr1 = new WCHAR[length];
				input.read(&bstr1[0],length);
				bstr1[length-2]  = '\0';
				input.close();
				Vss_class.vss_init();
				s_prop =  Vss_class.vss_query(bstr1);
				delete[] bstr1;
				CString drive = wchar_to_CString(L"F:");
				CString c_date = wchar_to_CString(s_prop.create_date);
				insertitems(volume_list,txt_F_count,drive, c_date);
				txt_F_count++;
			}



		}


	}
}


//void volume_shadow_util::OnClose()
//{
//	// TODO: 여기에 메시지 처리기 코드를 추가 및/또는 기본값을 호출합니다.
//
//	CDialogEx::OnClose();
//}
