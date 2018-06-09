// backup_timer.cpp : ���� �����Դϴ�.
//


#include "stdafx.h"
#include "shadow_util.h"
#include "backup_timer.h"
#include "afxdialogex.h"
#include "volume_shadow_util.h"
#include "MMSystem.h"

// backup_timer ��ȭ �����Դϴ�.

IMPLEMENT_DYNAMIC(backup_timer, CDialogEx)

backup_timer::backup_timer(CWnd* pParent /*=NULL*/)
	: CDialogEx(backup_timer::IDD, pParent)
	, n_radio(0)
	, d_radio(0)
	
{

}


backup_timer::~backup_timer()
{
}

void backup_timer::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);

	DDX_Control(pDX, IDC_LIST3, volume_list);
	DDX_Radio(pDX, IDC_RADIO1, n_radio);
	DDX_Radio(pDX, IDC_RADIO6, d_radio);
}

BOOL backup_timer::OnInitDialog()
{
	CDialog::OnInitDialog();
	
	
	USES_CONVERSION;
	CDialog::OnInitDialog();

	volume_list.InsertColumn(0,"��ȣ", LVCFMT_CENTER, 50, -1);
	volume_list.InsertColumn(1,"�����ѹ�",LVCFMT_CENTER,100,-1);
	volume_list.InsertColumn(2,"����̺�",LVCFMT_CENTER,100,-1);
	volume_list.InsertColumn(3,"���� ��¥",LVCFMT_CENTER,150,-1);
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
			int length = (int)input.tellg(); // ������ġ Ȯ��
			input.seekg(0, ios::beg);
			WCHAR* bstr1 = new WCHAR[length];
			
			input.read(&bstr1[0],length);
			bstr1[length-2]  = '\0';
			input.close();
			Vss_class.vss_init();
			s_prop =  Vss_class.vss_query(bstr1);
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
			int length = (int)input.tellg(); // ������ġ Ȯ��
			input.seekg(0, ios::beg);
			WCHAR* bstr1 = new WCHAR[length];
			input.read(&bstr1[0],length);
			bstr1[length-2]  = '\0';
			input.close();
			Vss_class.vss_init();		
			s_prop =  Vss_class.vss_query(bstr1);
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
			int length = (int)input.tellg(); // ������ġ Ȯ��
			input.seekg(0, ios::beg);
			WCHAR* bstr1 = new WCHAR[length];
			input.read(&bstr1[0],length);
			bstr1[length-2] = '\0';
			input.close();
			Vss_class.vss_init();
			s_prop =  Vss_class.vss_query(bstr1);
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
			int length = (int)input.tellg(); // ������ġ Ȯ��
			input.seekg(0, ios::beg);
			WCHAR* bstr1 = new WCHAR[length];
			
			input.read(&bstr1[0],length);
			bstr1[length-2]  = '\0';
			input.close();
			Vss_class.vss_init();
			s_prop =  Vss_class.vss_query(bstr1);
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
			int length = (int)input.tellg(); // ������ġ Ȯ��
			input.seekg(0, ios::beg);
			WCHAR* bstr1 = new WCHAR[length];
			
			input.read(&bstr1[0],length);
			bstr1[length-2]  = '\0';
			input.close();
			Vss_class.vss_init();
			s_prop =  Vss_class.vss_query(bstr1);
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
			int length = (int)input.tellg(); // ������ġ Ȯ��
			input.seekg(0, ios::beg);
			WCHAR* bstr1 = new WCHAR[length];
			input.read(&bstr1[0],length);
			bstr1[length-2]  = '\0';
			input.close();
			Vss_class.vss_init();
			s_prop =  Vss_class.vss_query(bstr1);
			CString drive = wchar_to_CString(L"F:");
			CString c_date = wchar_to_CString(s_prop.create_date);
			insertitems(volume_list,txt_F_count,drive, c_date);
				txt_F_count++;
			}
		
			
		
		}


		}


	
	return true;
}
BEGIN_MESSAGE_MAP(backup_timer, CDialogEx)
//ON_WM_TIMER()
ON_BN_CLICKED(IDC_BUTTON1, &backup_timer::OnBnClickedButton1)
ON_BN_CLICKED(IDC_BUTTON2, &backup_timer::OnBnClickedButton2)
//ON_BN_CLICKED(IDC_RADIO7, &backup_timer::OnBnClickedRadio7)
END_MESSAGE_MAP()
// backup_timer �޽��� ó�����Դϴ�.



CString backup_timer::wchar_to_CString(WCHAR* source)
{
	CString temp(source);
	CString result;
	result = temp;
	return result;
}

void backup_timer::insertitems(CListCtrl& volume_list, int xml_count, CString drive, CString c_date)
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

void backup_timer::OnBnClickedButton1() // Ÿ�̸� ��ŸƮ
{
	// TODO: ���⿡ ��Ʈ�� �˸� ó���� �ڵ带 �߰��մϴ�.
	CWnd cwnd;
	UpdateData(true);
//	shadow_prop s_prop;
	CString sid, pid, result, c_date, drive, d_object;
	TIMECAPS caps;
	timeGetDevCaps(&caps,sizeof(caps));
	switch (n_radio)
	{
	case 0: // 1��
		{
			switch (d_radio)
			{
			case 0: // c ����̺�
				{
				drive = "C:";
				timerid = (UINT)timeSetEvent(5000,caps.wPeriodMin,(LPTIMECALLBACK)TimeProcC,(DWORD)this,TIME_PERIODIC);
				if(!timerid) AfxMessageBox("Ÿ�̸Ӱ� �۵����� �ʾҽ��ϴ�.", MB_OK | MB_ICONWARNING);
				break;
				}
			case 1: // d ����̺�
				{
					drive = "D:";
				timerid = (UINT)timeSetEvent(5000,caps.wPeriodMin,(LPTIMECALLBACK)TimeProcD,(DWORD)this,TIME_PERIODIC);
				if(!timerid) AfxMessageBox("Ÿ�̸Ӱ� �۵����� �ʾҽ��ϴ�.", MB_OK | MB_ICONWARNING);
				break;
				}
				
			case 2: // f ����̺�
				{
					drive = "F:";
				timerid = (UINT)timeSetEvent(5000,caps.wPeriodMin,(LPTIMECALLBACK)TimeProcF,(DWORD)this,TIME_PERIODIC);
				if(!timerid) AfxMessageBox("Ÿ�̸Ӱ� �۵����� �ʾҽ��ϴ�.", MB_OK | MB_ICONWARNING);
				break;
				}
			default:
				break;
			}
			 break;
		}
	case 1: // 1�ð�
		{
			switch (d_radio)
			{
			case 0: // c ����̺�
				{
					drive = "C:";
				 timerid = (UINT)timeSetEvent(3600000,caps.wPeriodMin,(LPTIMECALLBACK)TimeProcC,(DWORD)this,TIME_PERIODIC);
				if(!timerid) AfxMessageBox("Ÿ�̸Ӱ� �۵����� �ʾҽ��ϴ�.", MB_OK | MB_ICONWARNING);
				break;
				}
			case 1: // d ����̺�
				{
					drive = "D:";
				 timerid = (UINT)timeSetEvent(3600000,caps.wPeriodMin,(LPTIMECALLBACK)TimeProcD,(DWORD)this,TIME_PERIODIC);
				if(!timerid) AfxMessageBox("Ÿ�̸Ӱ� �۵����� �ʾҽ��ϴ�.", MB_OK | MB_ICONWARNING);
				break;
				}
		
			case 2: // f ����̺�
				{			
					drive = "F:";
				timerid = (UINT)timeSetEvent(3600000,caps.wPeriodMin,(LPTIMECALLBACK)TimeProcF,(DWORD)this,TIME_PERIODIC);
				if(!timerid) AfxMessageBox("Ÿ�̸Ӱ� �۵����� �ʾҽ��ϴ�.", MB_OK | MB_ICONWARNING);
				break;
				}
			default:
				break;
			}
			break;
		}
	case 2: // 2�ð�
		{
			switch (d_radio)
			{
			case 0: // c ����̺�
				{
				drive = "C:";
				 timerid = (UINT)timeSetEvent(7200000,caps.wPeriodMin,(LPTIMECALLBACK)TimeProcC,(DWORD)this,TIME_PERIODIC);
				if(!timerid) AfxMessageBox("Ÿ�̸Ӱ� �۵����� �ʾҽ��ϴ�.", MB_OK | MB_ICONWARNING);
				break;
				}
			case 1: // d ����̺�
				{
					drive = "D:";
				 timerid = (UINT) ::timeSetEvent(7200000,caps.wPeriodMin,(LPTIMECALLBACK)TimeProcD,(DWORD)this,TIME_PERIODIC);
				if(!timerid) AfxMessageBox("Ÿ�̸Ӱ� �۵����� �ʾҽ��ϴ�.", MB_OK | MB_ICONWARNING);
				break;
				}
		
			case 2: // f ����̺�
				{
				drive = "F:";
				timerid = (UINT)timeSetEvent(7200000,caps.wPeriodMin,(LPTIMECALLBACK)TimeProcF,(DWORD)this,TIME_PERIODIC);
				if(!timerid) AfxMessageBox("Ÿ�̸Ӱ� �۵����� �ʾҽ��ϴ�.", MB_OK | MB_ICONWARNING);
				break;
				}
			default:
				break;
			}
			break;
		}
	case 3: // 4�ð�
		{
			switch (d_radio)
			{
			case 0: // c ����̺�
				{
				drive = "C:";
				 timerid = (UINT)timeSetEvent(14400000,caps.wPeriodMin,(LPTIMECALLBACK)TimeProcC,(DWORD)this,TIME_PERIODIC);
				if(!timerid) AfxMessageBox("Ÿ�̸Ӱ� �۵����� �ʾҽ��ϴ�.", MB_OK | MB_ICONWARNING);
				break;
				}
			case 1: // d ����̺�
				{
				drive = "D:";
				 timerid = (UINT) ::timeSetEvent(14400000,caps.wPeriodMin,(LPTIMECALLBACK)TimeProcD,(DWORD)this,TIME_PERIODIC);
				if(!timerid) AfxMessageBox("Ÿ�̸Ӱ� �۵����� �ʾҽ��ϴ�.", MB_OK | MB_ICONWARNING);
				break;
				}
		
			case 2: // f ����̺�
				{
				drive = "F:";
				timerid = (UINT)timeSetEvent(14400000,caps.wPeriodMin,(LPTIMECALLBACK)TimeProcF,(DWORD)this,TIME_PERIODIC);
				if(!timerid) AfxMessageBox("Ÿ�̸Ӱ� �۵����� �ʾҽ��ϴ�.", MB_OK | MB_ICONWARNING);
				break;
				}
			default:
				break;
			}
			break;
		}
	case 4: // 6�ð� 
		{
				switch (d_radio)
			{
			case 0: // c ����̺�
				{
				drive = "C:";
				 timerid = (UINT)timeSetEvent(21600000,caps.wPeriodMin,(LPTIMECALLBACK)TimeProcC,(DWORD)this,TIME_PERIODIC);
				if(!timerid) AfxMessageBox("Ÿ�̸Ӱ� �۵����� �ʾҽ��ϴ�.", MB_OK | MB_ICONWARNING);
				break;
				}
			case 1: // d ����̺�
				{
				drive = "D:";
				 timerid = (UINT)timeSetEvent(21600000,caps.wPeriodMin,(LPTIMECALLBACK)TimeProcD,(DWORD)this,TIME_PERIODIC);
				if(!timerid) AfxMessageBox("Ÿ�̸Ӱ� �۵����� �ʾҽ��ϴ�.", MB_OK | MB_ICONWARNING);
				break;
				}
		
			case 2: // f ����̺�
				{
				drive = "F:";
				timerid = (UINT)timeSetEvent(21600000,caps.wPeriodMin,(LPTIMECALLBACK)TimeProcF,(DWORD)this,TIME_PERIODIC);
				if(!timerid) AfxMessageBox("Ÿ�̸Ӱ� �۵����� �ʾҽ��ϴ�.", MB_OK | MB_ICONWARNING);
				break;
				}
			default:
				break;
			}
			
		break;
		}

	}
}

 void CALLBACK backup_timer::TimeProcC(UINT uTimerID,UINT uMsg,DWORD_PTR dwUser,DWORD_PTR dw1,DWORD_PTR dw2)
{
	backup_timer* timer;
	timer = (backup_timer*)dwUser;
	CWnd cwnd;
	
	shadow_prop s_prop;
	CString sid, pid, result, c_date, drive, d_object;
	
	
			char drive_path[MAX_PATH] = "C:\\";
				
				timer->Vss_class.vss_init();
				timer->Vss_class.vss_make(drive_path,timer->txt_C_count);
				timer->Vss_class.vss_snapshot(drive_path,timer->txt_C_count);
				s_prop =  timer->Vss_class.vss_shadowcopylist();
				CString drive_C = timer->wchar_to_CString(L"C:");
				CString c_date_C = timer->wchar_to_CString(s_prop.create_date);
				timer->insertitems(timer->volume_list,timer->txt_C_count,drive_C,c_date_C);
				timer->Vss_class.vss_exit();
				
				timer->txt_C_count++;
		
	
		AfxMessageBox("�۾� �Ϸ�!", MB_OK | MB_ICONWARNING);
	
 }
 
 void CALLBACK backup_timer::TimeProcD(UINT uTimerID,UINT uMsg,DWORD_PTR dwUser,DWORD_PTR dw1,DWORD_PTR dw2)
{
	backup_timer* timer;
	timer = (backup_timer*)dwUser;
	CWnd cwnd;
	
	shadow_prop s_prop;
	CString sid, pid, result, c_date, drive, d_object;
				
			char drive_path[MAX_PATH] = "D:\\";
				timer->Vss_class.vss_init();
				timer->Vss_class.vss_make(drive_path,timer->txt_D_count);
				timer->Vss_class.vss_snapshot(drive_path,timer->txt_D_count);
				s_prop =  timer->Vss_class.vss_shadowcopylist();
				CString drive_D = timer->wchar_to_CString(L"D:");
				CString c_date_D = timer->wchar_to_CString(s_prop.create_date);
				timer->insertitems(timer->volume_list,timer->txt_D_count,drive_D,c_date_D);
				timer->Vss_class.vss_exit();
				timer->txt_D_count++;
				

	 AfxMessageBox("��� �Ϸ�!", MB_OK | MB_ICONWARNING);
	
 }

 void CALLBACK backup_timer::TimeProcF(UINT uTimerID,UINT uMsg,DWORD_PTR dwUser,DWORD_PTR dw1,DWORD_PTR dw2)
{
	backup_timer* timer;
	timer = (backup_timer*)dwUser;
	CWnd cwnd;
	
	shadow_prop s_prop;
	CString sid, pid, result, c_date, drive, d_object;
	
	
			char drive_path[MAX_PATH] = "F:\\";
				timer->Vss_class.vss_init();
				timer->Vss_class.vss_make(drive_path,timer->txt_F_count);
				timer->Vss_class.vss_snapshot(drive_path,timer->txt_F_count);
				s_prop =  timer->Vss_class.vss_shadowcopylist();
				CString drive_F = timer->wchar_to_CString(L"F:");
				CString c_date_F = timer->wchar_to_CString(s_prop.create_date);
				timer->insertitems(timer->volume_list,timer->txt_F_count,drive_F,c_date_F);
			
				timer->txt_F_count++;
		
	
	 AfxMessageBox("��� �Ϸ�!", MB_OK | MB_ICONWARNING);
	
 }

 void backup_timer::OnBnClickedButton2() // Ÿ�̸� ����
 {
	 timeKillEvent(timerid);
	 // TODO: ���⿡ ��Ʈ�� �˸� ó���� �ڵ带 �߰��մϴ�.
 }

