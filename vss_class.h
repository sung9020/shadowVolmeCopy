#pragma once
#pragma comment (lib, "C:/Program Files/Microsoft SDKs/Windows/v7.1/Lib/x64/vssapi.lib")

#include "stdafx.h"
//#include "vld.h"
#include <iostream>
#include <Windows.h>
#include <stdio.h>
#include <shlwapi.h>
#include <vss.h>
#include <vswriter.h>
#include <vsbackup.h> 
#include <stdlib.h>
#include <tchar.h>
#include <msxml6.h>
#include <fstream>


const __int64 IN_WEEK = (__int64)10000000*60*60*24*7;
const __int64 IN_DAY = (__int64)10000000*60*60*24;
const __int64 IN_HOUR = (__int64)10000000*60*60;
const __int64 IN_MIN = (__int64)10000000*60;
const __int64 IN_SEC = (__int64)10000000;



using namespace std;

class vss_class
{


public :

	VSS_COMPONENT_TYPE pct;
	VSS_WRITER_STATE eWriterStatus;
	IVssWMFiledesc *ppFiledesc;
	UINT pcWriters;
	BSTR pbstrPath, pbstrFilename, pbstrRange, pbstrMetadata;
	UINT iWriter; 
	UINT pcdirectedTarget;
	BSTR pbstrSourcePath ,pbstrDestinationPath;
	BSTR pbstrSourceFileName, pbstrDestinationFilename;
	BSTR pbstrSourceRangeList, pbstrDestinationRangeList;

	VSS_PWSZ wszExpose;
	IVssAsync* pDoShadowCopy;
	IVssBackupComponents *pBackup;
	IVssComponent *vssComponent;
	IVssAsync *pAsync;		  
	IVssAsync *pPrepare; 
	IVssAsync *pResult;
	IVssWriterComponents *IvsswriterCompnent;
	IVssWriterComponentsExt *IvsswriterCompnentext;
	IVssComponent *ivssComponent;
	OSVERSIONINFO osvi;
	BOOL bIsWindowsVistaOr7;
	BSTR bstrXML;
	BSTR metaXML[MAX_PATH];
	HRESULT result;
	VSS_ID snapshotsetId;
	IVssWMFiledesc *filedesc;
	IVssWMComponent *ppCompnent;

	PVSSCOMPONENTINFO ppinfo;
	BSTR path,pbstrFilespec,pbstrAlternateLocation;
	VSS_ID pidWriterinstance;
	IVssExamineWriterMetadata *ppMetadata;
	UINT pcPartialFiles;
	VSS_ID pidWriterInstance;
	UINT pcIncludeFiles,pcExcludeFile,pcComponent;
	VSS_ID pidinstance, pidWriter;
	VSS_ID pidWriters[MAX_PATH];
	BSTR pbstrWriterName;
	VSS_USAGE_TYPE pUsage;
	VSS_SOURCE_TYPE pSource;
	IVssWMComponent *ppComponent;
	HANDLE hToken;
	DWORD infoLen;
	TOKEN_ELEVATION elevation;
	VSS_SNAPSHOT_PROP snapshotProp;
	VSS_ID idInstance ;
	VSS_ID idWriter ;

	HRESULT vss_init(BSTR bstrxml = NULL)
	{
#if (_WIN32_WINNT >= _WIN32_WINNT_VISTA)
		/* A program using VSS must run in elevated mode */

		OpenProcessToken(GetCurrentProcess(), TOKEN_QUERY , &hToken);

		GetTokenInformation(hToken, TokenElevation, &elevation, sizeof(elevation), &infoLen);

		if (!elevation.TokenIsElevated)
		{
			exit(3);
		}	
		CloseHandle(hToken);

#else
#error you are using an old version of sdk or not supported operating system
#endif


		result = CreateVssBackupComponents(&pBackup);
		//����� �����ϱ����ؼ� ��� ������Ʈ�� �ּҸ� �ο��޴´�. 
		if(result == S_OK)
		{
			result = pBackup->InitializeForBackup(bstrxml);
			//��� ������Ʈ�� ����� ���� �ʱ�ȭ�Ѵ�. 
			if(result == S_OK)
				result =  pBackup -> SetContext( VSS_CTX_BACKUP | VSS_CTX_CLIENT_ACCESSIBLE_WRITERS | VSS_CTX_APP_ROLLBACK);
			//���� �������� ī��(��� ������Ʈ�� �ʱ�ȭ �ϰų� ��������� ������ ���������� ����
			//writer�� �����ϴ� ī������ �ǹ�

			return result;

		}
		else
		{
			vss_release(pBackup);
			return E_FAIL;
		}
	}



	void vss_release(IUnknown *unkn)
	{
		unkn->Release();
	}


	void vss_make(_TCHAR *volumename,int num)
	{


		WCHAR VOLUMENAME[MAX_PATH] = {0};
		size_t ConvertedChars = 0;
		mbstowcs_s(&ConvertedChars,VOLUMENAME,volumename,strlen(volumename)+1);

		/*
		ZeroMemory(&osvi, sizeof(OSVERSIONINFO));
		osvi.dwOSVersionInfoSize = sizeof(OSVERSIONINFO);
		GetVersionEx(&osvi);
		bIsWindowsVistaOr7 =  ((osvi.dwMajorVersion > 6) || ( (osvi.dwMajorVersion == 6) && (osvi.dwMinorVersion >= 0) ));
		*/

		result = vss_init();		


		//	result =  pBackup -> SetContext(VSS_CTX_BACKUP | VSS_VOLSNAP_ATTR_TRANSPORTABLE | VSS_CTX_CLIENT_ACCESSIBLE_WRITERS);


		if(result != S_OK)
		{
			vss_release(pBackup);
			abort();
			//WINAPI �������
		}
		result = pBackup->SetBackupState(true,false,VSS_BT_FULL);
		// ���ÿ�Ҹ� ������ ������� �ǹ��Ѵ�.
		if(result != S_OK)
		{
			vss_release(pBackup);
		}
		result = pBackup->GatherWriterMetadata(&pAsync);
		//�۰��� �񵿱��� ������ �����Ѵ�. 
		if(result == S_OK)
		{
			result = pAsync->Wait();
			//wait�� ������ �۰��� ��� �Ϸ�
			if(result == S_OK)
			{
				UINT pcWriter = 0;

				result = pBackup->GetWriterMetadataCount(&pcWriter);
				//�۰��� ���� �޾ƿ´�.
				if(result == S_OK)
				{

					for(UINT i = 0; i< pcWriter; i++)
					{
						result = pBackup->GetWriterMetadata(i,&pidWriterInstance,&ppMetadata);
					  //�۰����� ���� �ִ� ��Ÿ������ ������ �޾ƿ´�.
						if(result == S_OK)
						{
							ppMetadata->SaveAsXML(&metaXML[i]);
							_bstr_t bstr1;
							bstr1 = metaXML[i];
							WCHAR buf[100];
							if(wcscmp(VOLUMENAME,L"C:\\")== 0)
							{
								wsprintfW(buf,L"C:\\Backup\\metaXML_C%d_%d.xml",num,i);
								ofstream output;
								output.open(buf);
								output << bstr1 <<endl;
								output.close();
							}
							else if(wcscmp(VOLUMENAME,L"D:\\")==0)
							{
								wsprintfW(buf,L"C:\\Backup\\metaXML_D%d_%d.xml",num,i);
								ofstream output;
								output.open(buf);
								output << bstr1 <<endl;
								output.close();
							}
							else
							{
								wsprintfW(buf,L"C:\\Backup\\metaXML_F%d_%d.xml",num,i);
								ofstream output;
								output.open(buf);
								output << bstr1 <<endl;
								output.close();
							}


						}
						if(result == S_OK)
						{
							result = ppMetadata->GetIdentity(&pidinstance,&pidWriter, &pbstrWriterName, &pUsage,&pSource);
							//��Ÿ�����Ͱ� ���� �ִ� �ڽ��� ������ ��ȯ�Ѵ�.
							//usage �۰��� ���� �մ� �������� ��� ����
							//source �۰��� �����ִ� �������� ����
						}

						UINT pcIncludeFiles,pcExcludeFiles, pcComponents;

						if(result == S_OK)
						{
							result = ppMetadata->GetFileCounts(&pcIncludeFiles,&pcExcludeFiles,&pcComponents);
							//include �������̽� �Ű������� ����Ǿ�����
							//exclude ����ϴµ� ���ܵǴ� �������� ���� (������ ���� �⺻ �۰��� ������)
							//component����� ��¥ ���ԵǴ� ������ҵ�(���ϼ�)

							if(result == S_OK)
							{


								for(UINT j=0; j< pcComponents; j++)
								{
									result = ppMetadata->GetComponent(j,&ppComponent);

									if(result == S_OK)
									{
										PVSSCOMPONENTINFO ppinfo;

										ppComponent->GetComponentInfo(&ppinfo);
									//ppinfo�� ������ ������ ����� ���ԵǴ� ���ϵ��� ���� �˼� �ִ�.
										if(ppinfo->bSelectable ==TRUE) 
									// ����� ���ð����� ��������̸� �����ҿ� ��������� �߰��Ѵ�.
									//������ ���� ������ ���� �����ҿ� �Ͻ������� �߰��ȴ�.
										{
											result = pBackup->AddComponent(pidinstance,pidWriter,ppinfo->type,ppinfo->bstrLogicalPath,ppinfo->bstrComponentName);

										}


									}


								}// pccomponent ����
							}
						}


					} // writer ��Ÿ������ ���� 
				}

			}
		}
	}// vss_make() ����





	void vss_snapshot(_TCHAR *volumename, int i)
	{
		vss_snapshot2(pBackup,volumename, i);
	}
	//�� ����� �κ�.. !
	void vss_expose(wchar_t* w_snapshotid,shadow_prop* prop)
	{
		VSS_ID sid;
		VSS_PWSZ wszExposed;
		CLSIDFromString(w_snapshotid,&sid);

		result = pBackup->ExposeSnapshot(sid,NULL,VSS_VOLSNAP_ATTR_EXPOSED_REMOTELY, L"test",&wszExposed);


	}

	shadow_prop vss_shadowcopylist()
	{

		shadow_prop prop = {0};
		//���� ������ ������ ���´�. 
		result = pBackup->GetSnapshotProperties(snapshotsetId, &snapshotProp);
		if(result == S_OK)
		{
			StringFromGUID2(snapshotProp.m_SnapshotId,prop.sid,128);
			//������ �������� �����ϴ� ���� �߿��� ������ ���̵�
			StringFromGUID2(snapshotProp.m_SnapshotSetId,prop.sgid,128);
			size_t ConvertedChars = 0;
			wcscpy_s(prop.pid,snapshotProp.m_pwszOriginalVolumeName);
			//���� ������ �����̸��� ���´�. 
			//������ ������ �̸��� ���� + {num-num-num...} ���·� ����
			//wcscpy_s(prop.v_path,pwszExposed);

			wcscpy_s(prop.d_object,snapshotProp.m_pwszSnapshotDeviceObject);

			SYSTEMTIME stUTC, stLocal, UMT_UTC, UMT_Local;
			FILETIME ftCreate, UMT_TIME;
			LARGE_INTEGER largeint;
			ftCreate.dwHighDateTime = HILONG(snapshotProp.m_tsCreationTimestamp);
			ftCreate.dwLowDateTime = LOLONG(snapshotProp.m_tsCreationTimestamp);

			FileTimeToSystemTime(&ftCreate,&stUTC);
			SystemTimeToTzSpecificLocalTime(NULL,&stUTC,&stLocal);
			char create_Date[260];
			sprintf_s(create_Date,"%02d-%02d-%d %02d:%02d:%02d",stLocal.wMonth,stLocal.wDay,stLocal.wYear,stLocal.wHour,stLocal.wMinute,stLocal.wSecond);
			size_t ConvertedChars2 = 0;
			mbstowcs_s(&ConvertedChars2,prop.create_date,create_Date,strlen(create_Date)+1); 
			SystemTimeToFileTime(&stUTC,&UMT_TIME);
			memcpy(&largeint,&UMT_TIME,sizeof(FILETIME));
			largeint.QuadPart +=  IN_HOUR * 9;
			memcpy(&UMT_TIME, &largeint, sizeof(FILETIME));
			FileTimeToSystemTime(&UMT_TIME,&UMT_UTC);
			SystemTimeToTzSpecificLocalTime(NULL,&UMT_UTC,&UMT_Local);
			char network_Date[260];
			sprintf_s(network_Date,"%d.%02d.%02d-%02d.%02d.%02d",UMT_Local.wYear,UMT_Local.wMonth,UMT_Local.wDay,UMT_Local.wHour,UMT_Local.wMinute,UMT_Local.wSecond);
			size_t ConvertedChars3 = 0;
			mbstowcs_s(&ConvertedChars3,prop.network_date,network_Date,strlen(network_Date)+1); 

		}
		return  prop;

	}
	
	shadow_prop vss_query(WCHAR* w_Snapshotsetid)
	{
		//������ ���̵� ������ ���鼭 �������� ã�� �Լ�
		shadow_prop prop;
		IVssEnumObject *ppEnum;
		VSS_OBJECT_PROP rgelt;
		ULONG pceltFetched;
		long plDeletedSnapshots = 0;
		//		VSS_ID pNondeletedSnapshotID;
		WCHAR sid[MAX_PATH];
		result = pBackup->Query(GUID_NULL,VSS_OBJECT_NONE,VSS_OBJECT_SNAPSHOT,&ppEnum);
		//ppeum ������ ���� ������ �����ִ� �������̽�
		//������ ������ ��ĵ�� �� �ֵ��� �޼��带 �����ϰ� �ִ�. 
		if(result == S_OK)
		{
			while(1)
			{
				result = ppEnum->Next(1,&rgelt,&pceltFetched);
				//�������� ������ ��ȸ�Ҽ� �ִ� �޼��� 
				if(result == S_FALSE) break;
				if((rgelt.Type == VSS_OBJECT_SNAPSHOT) | (rgelt.Type == VSS_OBJECT_SNAPSHOT_SET))
				{
					StringFromGUID2(rgelt.Obj.Snap.m_SnapshotId,sid,128);

					if(!wcscmp(sid,w_Snapshotsetid))
					{

						{

							StringFromGUID2(rgelt.Obj.Snap.m_SnapshotId,prop.sid,128);
							StringFromGUID2(rgelt.Obj.Snap.m_SnapshotSetId,prop.sgid,128);
							size_t ConvertedChars = 0;
							wcscpy_s(prop.pid,rgelt.Obj.Snap.m_pwszOriginalVolumeName);

							//wcscpy_s(prop.v_path,pwszExposed);

							wcscpy_s(prop.d_object,rgelt.Obj.Snap.m_pwszSnapshotDeviceObject);
							//�� �������� �ּҰ� �ʹ� �߿�. 
							SYSTEMTIME stUTC, stLocal, UMT_UTC, UMT_Local;
							FILETIME ftCreate, UMT_TIME;
							LARGE_INTEGER largeint;
							ftCreate.dwHighDateTime = HILONG(rgelt.Obj.Snap.m_tsCreationTimestamp);
							ftCreate.dwLowDateTime = LOLONG(rgelt.Obj.Snap.m_tsCreationTimestamp);

							FileTimeToSystemTime(&ftCreate,&stUTC);
							SystemTimeToTzSpecificLocalTime(NULL,&stUTC,&stLocal);
							char create_Date[260];
							sprintf_s(create_Date,"%02d-%02d-%d %02d:%02d:%02d",stLocal.wMonth,stLocal.wDay,stLocal.wYear,stLocal.wHour,stLocal.wMinute,stLocal.wSecond);
							size_t ConvertedChars2 = 0;
							mbstowcs_s(&ConvertedChars2,prop.create_date,create_Date,strlen(create_Date)+1); 
							SystemTimeToFileTime(&stUTC,&UMT_TIME);
							memcpy(&largeint,&UMT_TIME,sizeof(FILETIME));
							largeint.QuadPart -=  IN_HOUR * 9;
							memcpy(&UMT_TIME, &largeint, sizeof(FILETIME));
							FileTimeToSystemTime(&UMT_TIME,&UMT_UTC);
							SystemTimeToTzSpecificLocalTime(NULL,&UMT_UTC,&UMT_Local);
							char network_Date[260];
							sprintf_s(network_Date,"%d.%02d.%02d-%02d.%02d.%02d",UMT_Local.wYear,UMT_Local.wMonth,UMT_Local.wDay,UMT_Local.wHour,UMT_Local.wMinute,UMT_Local.wSecond);
							size_t ConvertedChars3 = 0;
							mbstowcs_s(&ConvertedChars3,prop.network_date,network_Date,strlen(network_Date)+1); 
							//�������� ���� ��¥���� ����Ÿ�ӿ��� �ý��� Ÿ������ �ٲٰ� ����.

							VssFreeSnapshotProperties(&rgelt.Obj.Snap);

							//      }
						}
						return  prop;
					}
				} 
				else;
			}
		}
		if(ppEnum != NULL)
		{
			CoTaskMemFree(ppEnum);

		}

	}
	LONG vss_delete(wchar_t* w_snapshotid)
	{
		LONG plDeletedSnapshots;
		VSS_ID pNondeletedSnapshotID;
		VSS_ID sid;
		CLSIDFromString(w_snapshotid,&sid);
		result = pBackup->DeleteSnapshots(sid,VSS_OBJECT_SNAPSHOT,TRUE,&plDeletedSnapshots,&pNondeletedSnapshotID);
		//������ ���̵� �־��ָ� �ý��� ������ �������� ��������
		if(result == S_OK)
			return plDeletedSnapshots;
		else return 0;
	}

	void vss_filelist(FILE_Tree directory,shadow_prop* prop)
	{
	
		vss_filelist2(directory.root,prop->d_object);

	}	

	void vss_exit()
	{


		VssFreeSnapshotProperties(&snapshotProp);
		pDoShadowCopy->Release();
		pPrepare->Release();
		pAsync->Release();
		pBackup->FreeWriterMetadata();
		pBackup->Release();
		//��� ������Ʈ�� �ʱ�ȭ �����ִ� �Լ�
	}

private:
	void vss_snapshot2(IVssBackupComponents *pBackup, _TCHAR *volumename, int i)
	{

		WCHAR VOLUMENAME[MAX_PATH] = {0};
		size_t ConvertedChars = 0;
		mbstowcs_s(&ConvertedChars,VOLUMENAME,volumename,strlen(volumename)+1);
		result = pBackup->StartSnapshotSet(&snapshotsetId);
		//������ ���̵� �ּҸ� �ο��޴´�.
		if(result != S_OK) vss_release(pBackup);

		if(result == S_OK)
			result = pBackup ->AddToSnapshotSet(VOLUMENAME,GUID_NULL,&snapshotsetId);
		//���� ����� ������ �־��ش�.
		if(result != S_OK) vss_release(pBackup);

		result = pBackup->PrepareForBackup(&pPrepare);
		//����� �غ��ϸ鼭 WRITER�� ����� ���� ����� �غ��Ѵ�.
		if(result == S_OK)
			result = pPrepare ->Wait(); //writer ���� ����ȭ 
		if(result == S_OK)
			result = pBackup -> GatherWriterStatus(&pPrepare);
		if(result == S_OK)
			if(pPrepare->Wait() == S_OK){};
		if(result == S_OK)
			result = pBackup ->DoSnapshotSet(&pDoShadowCopy);
		//WRITER�� ��Ż��°� ���۵Ǹ� ����� �����Ѵ�. 

		if(result == S_OK)
		{
			HRESULT hr;
			result = pDoShadowCopy ->Wait();
			while(true){

				pDoShadowCopy->QueryStatus(&hr,NULL);
				if(hr == VSS_S_ASYNC_FINISHED)
					break;
			}

		}	

		if(result == S_OK) 
		{
			result = pBackup->SaveAsXML(&bstrXML);
			//���� ��� ������Ʈ�� ������ ���� �����ϴ�.
			//������ ���� ���Ŀ� ����� ������ ���� ������ ����.
			_bstr_t bstr1;
			bstr1 = bstrXML;
			WCHAR buf[100];
			if(wcscmp(VOLUMENAME,L"C:\\")== 0)
			{
				wsprintfW(buf,L"C:\\Backup\\bstrXML_C_%d.xml",i);
				ofstream output;
				output.open(buf);
				output << bstr1 <<endl;
				output.close();
			}
			else if(wcscmp(VOLUMENAME,L"D:\\")==0)
			{
				wsprintfW(buf,L"C:\\Backup\\bstrXML_D_%d.xml",i);
				ofstream output;
				output.open(buf);
				output << bstr1 <<endl;
				output.close();
			}
			else
			{
				wsprintfW(buf,L"C:\\Backup\\bstrXML_F_%d.xml",i);
				ofstream output;
				output.open(buf);
				output << bstr1 <<endl;
				output.close();
			}
		}
		// save_xml 
		if(result == S_OK)
		{
			pBackup->GetSnapshotProperties(snapshotsetId,&snapshotProp);
			WCHAR buf[30];
			WCHAR w_SnapshotsetId[129];
			StringFromGUID2(snapshotProp.m_SnapshotId,w_SnapshotsetId,128);
			//������ ���̵� �����صξ�� ���߿� �����ؼ� ������ ���� �ִ�. 
			if(wcscmp(VOLUMENAME,L"C:\\")== 0)
			{
				wsprintfW(buf,L"C:\\Backup\\C_%d_sid.txt",i);
				wofstream output;
				output.open(buf);
				output << w_SnapshotsetId <<endl;
				output.close();
			}
			else if(wcscmp(VOLUMENAME,L"D:\\")==0)
			{
				wsprintfW(buf,L"C:\\Backup\\D_%d_sid.txt",i);
				wofstream output;
				output.open(buf);
				output << w_SnapshotsetId <<endl;

				output.close();
			}
			else
			{
				wsprintfW(buf,L"C:\\Backup\\F_%d_sid.txt",i);
				wofstream output;
				output.open(buf);
				output << w_SnapshotsetId <<endl;
				output.close();
			}

		}

	}
	
	/*

	BOOL vss_filelist3(Node* Current,WCHAR* src = 0, shadow_prop* prop = 0)
	{
		HANDLE hHandle; 
		WIN32_FIND_DATAW find_data; 
		BOOL bResult=TRUE; 
		//	WCHAR fname[MAX_PATH]; 
		WCHAR WildCard[MAX_PATH]; 
		WCHAR SrcFile[MAX_PATH]; 
		WCHAR DestFile[MAX_PATH];
		wcscpy_s(WildCard,src); 
		wcscat_s(WildCard, L"\\*.*"); 
		hHandle = FindFirstFileW(WildCard,&find_data);
		if(hHandle == INVALID_HANDLE_VALUE)
			return false;
		while(bResult)
		{

			wsprintfW(SrcFile, L"%s\\%s",src,find_data.cFileName);

			if(find_data.dwFileAttributes & FILE_ATTRIBUTE_DIRECTORY)
			{
				if(wcscmp(find_data.cFileName,L".") && wcscmp(find_data.cFileName,L".."))
				{


				}
			}
			else
			{

			}
			bResult = FindNextFileW(hHandle,&find_data);

		}

		FindClose(hHandle);

		return true;
	}
	*/

	
	void vss_filelist2(Node* Current,WCHAR* PATH)
	{

	HANDLE hFileHandle;
	WIN32_FIND_DATAW find_data;
	//		WCHAR *path;

	int count = 0;
	//		BOOL NEXTFILE;
	int  f_size;//fname ������
	WCHAR WildCard[500];
	WCHAR SrcFile[500];
	ULONGLONG file_size;
	SYSTEMTIME stUTC, stLocal;
	FILETIME ftCreate;
	

	if(Current->type == 0) //��Ʈ �϶�
	{
	
	wcscpy_s(WildCard,PATH); 
	wcscat_s(WildCard, L"\\*.*"); 
	wcscpy_s(Current->FNAME,wcslen(L"ROOT")+1,L"ROOT");
	
	hFileHandle = FindFirstFileW(WildCard, &find_data);  // ��Ʈ�϶� �۽�Ʈ ���� 
	if(hFileHandle != INVALID_HANDLE_VALUE )
	{
	if(find_data.cFileName[0] != L'.')
	{
	f_size = wcslen(find_data.cFileName) + 1;
	Node* ParentNode = 0;
	Node* insertNode = new Node();
	insertNode->type = 2;
	file_size = (find_data.nFileSizeHigh * ((ULONGLONG)MAXDWORD + 1)) + find_data.nFileSizeLow;
	insertNode->file_size = file_size/1024;
	FileTimeToSystemTime(&find_data.ftLastWriteTime,&stUTC);
	SystemTimeToTzSpecificLocalTime(NULL,&stUTC,&stLocal);
	WCHAR create_Date[38]= {0};
	wsprintfW(create_Date,L"%d-%02d-%02d %02d:%02d:%02d",stLocal.wYear,stLocal.wMonth,stLocal.wDay,stLocal.wHour,stLocal.wMinute,stLocal.wSecond);
	wcscpy_s(insertNode->CREATED_DATE,wcslen(create_Date)+1,create_Date);
	wcscpy_s(insertNode->FNAME,wcslen(find_data.cFileName)+1,find_data.cFileName); // ���� �˻��� �����̸��� �߰�
	ParentNode = Current;
	Current->cid[0] = insertNode;
	Current = Current->cid[0]; // �ڱ� ��ġ�� ã�� �̵��Ѵ�.
	Current->pid = ParentNode;
	Current->pid->Numofchild++;
	count = 1;
	
	
	if(find_data.dwFileAttributes & FILE_ATTRIBUTE_DIRECTORY) // �����尡 ���丮 �� ���
	{
	wsprintfW(SrcFile, L"%s\\%s",PATH,find_data.cFileName);
	Current->type = 1; //���丮���� ���, ������ �ֱ� ������ ����.
	vss_filelist2(Current,SrcFile);
	Current = Current->pid;
	}
	else
	{
	Current = Current->pid;
	}
	}
	}	
	while(FindNextFileW(hFileHandle,&find_data)) //��Ʈ �϶� �ؽ�Ʈ ����, Current�� �θ� ����Ű�� ��
	{
	if(find_data.cFileName[0] == L'.')
	continue;
	else
	{
	
	f_size = wcslen(find_data.cFileName) + 1;
	Node* ParentNode = 0;
	Node* insertNode = new Node();
	insertNode->type = 2;
	file_size = (find_data.nFileSizeHigh * ((ULONGLONG)MAXDWORD + 1)) + find_data.nFileSizeLow;
	insertNode->file_size = file_size/1024;
	FileTimeToSystemTime(&find_data.ftLastWriteTime,&stUTC);
	SystemTimeToTzSpecificLocalTime(NULL,&stUTC,&stLocal);
	WCHAR create_Date[38]= {0};
	wsprintfW(create_Date,L"%d-%02d-%02d %02d:%02d:%02d",stLocal.wYear,stLocal.wMonth,stLocal.wDay,stLocal.wHour,stLocal.wMinute,stLocal.wSecond);
	wcscpy_s(insertNode->CREATED_DATE,wcslen(create_Date)+1,create_Date);
	wcscpy_s(insertNode->FNAME,wcslen(find_data.cFileName)+1,find_data.cFileName); // ���� �˻��� �����̸��� �߰�
	ParentNode = Current;
	Current->cid[count] = insertNode;
	Current = Current->cid[count];
	Current->pid = ParentNode;
	Current->pid->Numofchild++;    						//������´� current�� ���� �ڽ��� ����Ű������.
	count++;

	if(find_data.dwFileAttributes & FILE_ATTRIBUTE_DIRECTORY) // �����尡 ���丮 �� ���
	{

	Current->type = 1; //���丮���� ���, ������ �ֱ� ������ ����.
	wsprintfW(SrcFile, L"%s\\%s",PATH,find_data.cFileName);
	vss_filelist2(Current,SrcFile);
	Current = Current->pid;
	}
	else
	{	
	Current = Current->pid;
	}
	}
	}


	}  //��Ʈ �˻� ��


	else // ��Ʈ�� �ƴҶ� �۽�Ʈ����
	{
		
	
	wcscpy_s(WildCard,PATH); 
	wcscat_s(WildCard, L"\\*.*"); 

	hFileHandle = FindFirstFileW(WildCard, &find_data); // �θ��� �н��� �ּҷ� ����.
	if(hFileHandle != INVALID_HANDLE_VALUE )
	{
	if(find_data.cFileName[0] != L'.')
	{

	f_size = wcslen(find_data.cFileName) + 1;
	Node* ParentNode = 0;
	Node* insertNode = new Node();

	//�ڽ��� �̸��� �ֱ����� �����غ� 
	insertNode->type = 2;
	file_size = (find_data.nFileSizeHigh * ((ULONGLONG)MAXDWORD + 1)) + find_data.nFileSizeLow;
	insertNode->file_size = file_size/1024;
	FileTimeToSystemTime(&find_data.ftLastWriteTime,&stUTC);
	SystemTimeToTzSpecificLocalTime(NULL,&stUTC,&stLocal);
	WCHAR create_Date[38]= {0};
	wsprintfW(create_Date,L"%d-%02d-%02d %02d:%02d:%02d",stLocal.wYear,stLocal.wMonth,stLocal.wDay,stLocal.wHour,stLocal.wMinute,stLocal.wSecond);
	wcscpy_s(insertNode->CREATED_DATE,wcslen(create_Date)+1,create_Date);
	wcscpy_s(insertNode->FNAME,wcslen(find_data.cFileName)+1,find_data.cFileName); // ���� �˻��� �����̸��� �߰�
	ParentNode = Current;
	Current->cid[0] = insertNode;
	Current = Current->cid[0]; // �ڱ� ��ġ�� ã�� �̵��Ѵ�.
	Current->pid = ParentNode;

	Current->pid->Numofchild++;
	count = 1;
	
	if(find_data.dwFileAttributes & FILE_ATTRIBUTE_DIRECTORY) // �����尡 ���丮 �� ���
	{
	Current->type = 1; //���丮���� ���, ������ �ֱ� ������ ����.
	wsprintfW(SrcFile, L"%s\\%s",PATH,find_data.cFileName);
	vss_filelist2(Current,SrcFile);
	Current = Current->pid;
	}
	else
	{
	Current = Current->pid;
	}
	}
	else
	{
	while(FindNextFileW(hFileHandle,&find_data))
	{
	if(find_data.cFileName[0] == L'.')
	continue;
	else
	{

	f_size = wcslen(find_data.cFileName) + 1;
	Node* ParentNode = 0;
	Node* insertNode = new Node();
		
	insertNode->type = 2;
	file_size = (find_data.nFileSizeHigh * ((ULONGLONG)MAXDWORD + 1)) + find_data.nFileSizeLow;
	insertNode->file_size = file_size/1024;
	FileTimeToSystemTime(&find_data.ftLastWriteTime,&stUTC);
	SystemTimeToTzSpecificLocalTime(NULL,&stUTC,&stLocal);
	WCHAR create_Date[38]= {0};
	wsprintfW(create_Date,L"%d-%02d-%02d %02d:%02d:%02d",stLocal.wYear,stLocal.wMonth,stLocal.wDay,stLocal.wHour,stLocal.wMinute,stLocal.wSecond);
	wcscpy_s(insertNode->CREATED_DATE,wcslen(create_Date)+1,create_Date);
	wcscpy_s(insertNode->FNAME,wcslen(find_data.cFileName)+1,find_data.cFileName); // ���� �˻��� �����̸��� �߰�
	ParentNode = Current;
	Current->cid[count] = insertNode;
	Current = Current->cid[count];
	Current->pid = ParentNode;

	Current->pid->Numofchild++;
	count++;
	


	if(find_data.dwFileAttributes & FILE_ATTRIBUTE_DIRECTORY) // �����尡 ���丮 �� ���
	{

	Current->type = 1; //���丮���� ���, ������ �ֱ� ������ ����.

	wsprintfW(SrcFile, L"%s\\%s",PATH,find_data.cFileName);
	vss_filelist2(Current,SrcFile);
	Current = Current->pid;
	}
	else
	{
	Current = Current->pid;
	}
	}
	}
	}

	

	}

	}

	}
	

	};
	


	/*
	result = pBackup->GetWriterComponentsCount(&iWriter);
	if(result == S_OK)
	{
	for(int i = 0; i< iWriter; i++)
	{
	result = pBackup->GetWriterComponents(i,&IvsswriterCompnentext);

	if(result == S_OK)
	{
	UINT iComponent;
	result = IvsswriterCompnentext->GetComponentCount(&iComponent);

	if(result == S_OK)
	{
	for(int j = 0; j < iComponent; j++)
	{
	result = IvsswriterCompnentext->GetComponent(j,&ivssComponent);
	if(result == S_OK)
	{

	result = ivssComponent->GetDirectedTargetCount(&pcdirectedTarget);
	if(result == S_OK)
	result = ivssComponent->GetPartialFileCount(&pcPartialFiles);

	}
	if(result == S_OK)
	{


	result = ivssComponent->GetDirectedTarget(pcdirectedTarget,&pbstrSourcePath,&pbstrSourceFileName,&pbstrSourceRangeList,&pbstrDestinationPath,&pbstrDestinationFilename,&pbstrDestinationRangeList);

	if(result == S_OK)
	result = ivssComponent->GetPartialFile(pcPartialFiles,&pbstrPath,&pbstrFilename,&pbstrRange,&pbstrMetadata);

	}
	if(result == S_OK)

	ivssComponent->AddDirectedTarget(pbstrSourcePath,pbstrSourceFileName,pbstrSourceRangeList,pbstrDestinationPath,pbstrDestinationFilename,pbstrDestinationRangeList);

	if (result == S_OK)
	ivssComponent->AddPartialFile(pbstrPath,pbstrFilename,pbstrRange,pbstrMetadata);
	}
	}


	}

	}

	}
	*/
	/*
	BOOL vss_restore2(_TCHAR* volumename)
	{
		
		result = pBackup->InitializeForRestore(bstrXML);
		if(result == S_OK)
			result = pBackup->GatherWriterMetadata(&pAsync);
		if(result == S_OK)
		{
			result = pAsync->Wait();
		}
		HRESULT hr = S_OK;
		while(true){

			pAsync->QueryStatus(&hr,NULL);
			if(hr == VSS_S_ASYNC_FINISHED)
				break;
		}

		if(result == S_OK)
			result = pBackup->GetWriterMetadataCount(&pcWriters);

		if(result == S_OK)
		{
			for(UINT i = 0; i< pcWriters;i++)
			{												
				result = pBackup->GetWriterMetadata(i,&pidWriterInstance,&ppMetadata);


				if(result == S_OK){
					result = ppMetadata->GetIdentity(&pidinstance,&pidWriter,&pbstrWriterName,&pUsage,&pSource);
				}
				if(result ==S_OK)
					result = ppMetadata->GetFileCounts(&pcIncludeFiles,&pcExcludeFile,&pcComponent);
				if(result == S_OK)
				{

					for(UINT j = 0; j<pcComponent; j++)
					{
						result = ppMetadata->GetComponent(j,&ppCompnent);
						if(result == S_OK)
						{
							result = ppComponent->GetComponentInfo(&ppinfo);

							if(result == S_OK)
							{
								if(ppinfo->bSelectable == TRUE)
								{
									result = pBackup->SetSelectedForRestore(pidWriter,ppinfo->type,ppinfo->bstrLogicalPath,ppinfo->bstrComponentName,true);

								}
							}
						}
					}
				}

			}


			if(result == S_OK)
				result = pBackup ->GetWriterComponentsCount(&pcWriters);

			if(result == S_OK)
			{
				for(UINT w = 0; w < pcWriters; w++)
				{

					result = pBackup->GetWriterComponents(w,&IvsswriterCompnentext);
					if(result == S_OK)

						IvsswriterCompnentext->GetWriterInfo(&idInstance,&idWriter);
					if(result == S_OK)
					{
						IvsswriterCompnentext->GetComponentCount(&pcComponent);
						for(UINT c = 0; c < pcComponent; c++)
						{
							VSS_COMPONENT_TYPE pct;
							result = IvsswriterCompnentext->GetComponent(c,&ivssComponent);

							if(result == S_OK)
								result =ivssComponent->GetLogicalPath(&pbstrPath);	
							if(result == S_OK)
								result =ivssComponent->GetComponentName(&pbstrWriterName);
							if(result == S_OK)
								result =ivssComponent->GetComponentType(&pct);
							if(result == S_OK)
								result = pBackup->SetSelectedForRestore(idWriter,pct,pbstrPath,pbstrWriterName,true);
						}
					}

				}
			}
		}



		result = pBackup->PreRestore(&pPrepare);
		if(result == S_OK)
		{
			result = pPrepare->Wait();
		}			
		*/

/*
		if(result == S_OK)
			result = pBackup->GatherWriterMetadata(&pAsync); // VSS Identify event�� ���������� �� writer�� requester�� ����� ����
		if (result == S_OK)
			result = pAsync->Wait();
		if(result == S_OK)
		{
			result = pBackup ->GetWriterComponentsCount(&pcWriters);

			for(UINT w = 0; w < pcWriters; w++)
			{

				result = pBackup->GetWriterComponents(w,&IvsswriterCompnentext);
				if(result == S_OK)

					IvsswriterCompnentext->GetWriterInfo(&idInstance,&idWriter);
				if(result == S_OK)
				{
					IvsswriterCompnentext->GetComponentCount(&pcComponent);
					for(UINT c = 0; c < pcComponent; c++)
					{
						IvsswriterCompnentext->GetComponent(c,&ivssComponent);
						ivssComponent->GetLogicalPath(&pbstrPath);				
						ivssComponent->GetComponentName(&pbstrWriterName);
						ivssComponent->GetComponentType(&pct);
						pBackup->SetFileRestoreStatus(idWriter,pct,pbstrPath,pbstrWriterName,VSS_RS_ALL);
					}
				}

			}


			if(result == S_OK)
				result = pBackup->GetWriterMetadataCount(&pcWriters);

			if(result == S_OK)
			{
				for(UINT i = 0; i< pcWriters;i++)
				{												
					result = pBackup->GetWriterMetadata(i,&pidWriterInstance,&ppMetadata);


					if(result == S_OK){
						result = ppMetadata->GetIdentity(&pidinstance,&pidWriter,&pbstrWriterName,&pUsage,&pSource);
					}
					if(result ==S_OK)
						result = ppMetadata->GetFileCounts(&pcIncludeFiles,&pcExcludeFile,&pcComponent);
					if(result == S_OK)
					{

						for(UINT j = 0; j<pcComponent; j++)
						{
							result = ppMetadata->GetComponent(j,&ppCompnent);
							if(result == S_OK)
							{
								result = ppComponent->GetComponentInfo(&ppinfo);

								if(result == S_OK)
								{
									if(ppinfo->bSelectable == TRUE)
									{
										result = pBackup->SetFileRestoreStatus(pidWriter,ppinfo->type,ppinfo->bstrLogicalPath,ppinfo->bstrComponentName,VSS_RS_ALL);

									}
								}
							}
						}
					}

				}
			}

		}

		if(result == S_OK)
			result = pBackup->PostRestore(&pResult);
		if(result == S_OK)
			result = pResult->Wait();
		if(result == S_OK)
		{
			pResult->Release();
			pPrepare->Release();
		}


	}
	*/
	/*

	BOOL vss_filelist3(Node* Current,WCHAR* src = 0, shadow_prop* prop = 0)
	{
		HANDLE hHandle; 
		WIN32_FIND_DATAW find_data; 
		BOOL bResult=TRUE; 
		//	WCHAR fname[MAX_PATH]; 
		WCHAR WildCard[MAX_PATH]; 
		WCHAR SrcFile[MAX_PATH]; 
		WCHAR DestFile[MAX_PATH];
		wcscpy_s(WildCard,src); 
		wcscat_s(WildCard, L"\\*.*"); 
		hHandle = FindFirstFileW(WildCard,&find_data);
		if(hHandle == INVALID_HANDLE_VALUE)
			return false;
		while(bResult)
		{

			wsprintfW(SrcFile, L"%s\\%s",src,find_data.cFileName);

			if(find_data.dwFileAttributes & FILE_ATTRIBUTE_DIRECTORY)
			{
				if(wcscmp(find_data.cFileName,L".") && wcscmp(find_data.cFileName,L".."))
				{


				}
			}
			else
			{

			}
			bResult = FindNextFileW(hHandle,&find_data);

		}

		FindClose(hHandle);

		return true;
	}
	*/