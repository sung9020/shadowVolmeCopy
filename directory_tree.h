
#pragma once
#include "stdafx.h"
//#include "vld.h"
#include "vss_class.h"
#include "afxwin.h"
#include "file_list_view.h"
#include <stdlib.h>
#include <iostream>
#include <Windows.h>
#include <stdio.h>
#include <shlwapi.h>

using namespace std;

class Node
{
public:

	WIN32_FIND_DATA find_data;
	Node* pid;
	Node* cid;
	WCHAR* FNAME;
	
};

class tree
{
private :
	Node* root;

public :
 
	tree()
	{
		root->pid = NULL;
		root->cid = NULL;
		root->FNAME = L"∑Á∆Æ";
	}
	
	/*bool insert_node(WCHAR *FNAME)
	{
		

	}
	*/
};
