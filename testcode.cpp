#include <iostream>
#include <string>
#include <fstream>
using namespace std;
//------------
typedef struct diem
{
	float dai_so = 0;
	float Mac = 0;
	float cpp = 0;
}diem;
typedef struct sv
{
	string ho;
	string ten;
	string ma_sv;
	string phai;
	diem ds_diem;
}sv;
struct node_sv
{
	//data
	sv data;
	//pointer
	node_sv *pnext;
};
typedef struct node_sv node_sv;

typedef struct danh_sach_sv
{
	node_sv *phead = NULL;
	node_sv *ptail = NULL;
}danh_sach_sv;
//================================
void menu();//Xu ly chinh
istream& operator >> (istream &is, sv &a);
node_sv* khoi_tao_node(sv x);
void them(danh_sach_sv &ds_sv, sv x);
void xuat(danh_sach_sv ds_sv);
void load_file(danh_sach_sv &ds_sv);
void xoa_sv(danh_sach_sv &ds_sv, string vt);
void sap_xep(danh_sach_sv &ds_sv);
void main()
{
	menu();
	system("pause");
}
void menu()//Xu ly chinh
{
	//---- setting ----
	danh_sach_sv ds_sv;
	//---- load file ----
	load_file(ds_sv);
	//----- menu -----
	bool kt_menu = true;
	while (kt_menu == true)
	{
		system("cls");
		cout << "1. Nhap sinh vien" << endl;
		cout << "2. Xuat danh sach sinh vien" << endl;
		cout << "3. Xoat sinh vien co ma sinh vien nhap tu ban phim" << endl;
		cout << "4. Sap xep" << endl;
		cout << "0. Thoat" << endl;
		int lc;
		cout << "Nhap lc: ";cin >> lc;
		switch (lc)
		{
		case 1:
		{
			int sl;cout << "nhap sl sinh vien can them: ";cin >> sl;
			cin.ignore();//sv 1 không d? d? li?u th?a cho sv 2
			for (int i = 1;i <= sl;i++)
			{
				cout << "\t\t------- nhap sv " << i << " ----------" << endl;
				//------ thêm 1 sv vào danh sách ------
				sv x;//dùng d? luu t?m d? li?u ngu?i dùng nh?p vào
				cin >> x;
				them(ds_sv, x);//thêm cu?i
			}
			break;
		}
		case 2:
		{
			xuat(ds_sv);
			system("pause");
			break;
		}
		case 3:
		{
			string vt;
			cin.ignore();
			cout << "Nhap ma sinh vien can xoa: ";getline(cin, vt);
			xoa_sv(ds_sv, vt);
			break;
		}
		case 4:
		{
			sap_xep(ds_sv);
			break;
		}
		case 0:
		{
			kt_menu = false;
			break;
		}
		}
	}
}
istream& operator >> (istream &is,sv &a)
{
	cout << "Nhap ho: ";getline(is, a.ho);
	cout << "Nhap ten: ";getline(is, a.ten);
	cout << "Nhap phai: ";getline(is, a.phai);
	cout << "Nhap ma sinh vien: ";getline(is, a.ma_sv);
	//----
	return is;
}
node_sv* khoi_tao_node(sv x)//x dã luu data ngu?i dùng nh?p vào
{
	node_sv *p = new node_sv;
	p->data = x;
	p->pnext = NULL;
	return p;
}
void them(danh_sach_sv &ds_sv, sv x)
{
	node_sv *p = khoi_tao_node(x);
	if (ds_sv.phead == NULL)//r?ng: d?u cu?i = p
	{
		ds_sv.phead = ds_sv.ptail=p;
	}
	else//n pt => Thêm cu?i
	{
		ds_sv.ptail->pnext = p;
		ds_sv.ptail = p;
	}
}
void xuat(danh_sach_sv ds_sv)
{
	int i = 1;
	for (node_sv *k = ds_sv.phead;k != NULL;k = k->pnext)
	{
		cout << "\t\t------ Sv " << i++ <<" ------"<< endl;
		cout << "Ma sv: " << k->data.ma_sv << endl;
		cout << "Ho ten: " << k->data.ho << " " << k->data.ten << endl;
		cout << "Phai: " << k->data.phai << endl;
		cout << "---- Diem: ----" << endl;
		cout << "Dai so: " << k->data.ds_diem.dai_so << endl;
		cout << "Mac: " << k->data.ds_diem.Mac << endl;
		cout << "C++: " << k->data.ds_diem.cpp << endl;
	}
}
void load_file(danh_sach_sv &ds_sv)
{
	ifstream filein("dslk.txt");
	//--- doc file ----
	while (filein.eof() == false)
	{
		sv a;//d? luu t?m d? li?u load t? file
		getline(filein, a.ho, ',');
		getline(filein, a.ten, ',');
		getline(filein, a.ma_sv, ',');
		getline(filein, a.phai, ',');
		filein >> a.ds_diem.dai_so;
		filein.ignore();//b? ,
		filein >> a.ds_diem.Mac;
		filein.ignore();//b? ,
		filein >> a.ds_diem.cpp;
		filein.ignore();//b? \n
		//---- them ---
		them(ds_sv, a);
	}
	filein.close();
}
void xoa_sv(danh_sach_sv &ds_sv, string vt)
{
	//C1: s? d?ng k? thu?t 100% vt không n?m ? d?u
	//C2: th?c hi?n xóa d?u => for khuy?t d? không nh?y bu?c

	node_sv *h = NULL;
	for (node_sv *k = ds_sv.phead;k != NULL;)
	{
		if (_stricmp(k->data.ma_sv.c_str(), vt.c_str()) == 0 && k == ds_sv.phead)
		{
			//---- vt ? d?u => xóa d?u ----
			ds_sv.phead = ds_sv.phead->pnext;
			delete k;//k vô d?nh
			k = ds_sv.phead;//nh?y v? d?u - n?u lên bu?c l?p => sót pt
			//Không du?c nh?y bu?c ==> s? dung for khuy?t
		}
		else//khác vt - ==vt nhung ko ph?i d?u
		{
			if (_stricmp(k->data.ma_sv.c_str(), vt.c_str()) == 0)//trùng
			{
				//---- xóa -----
				h->pnext = k->pnext;
				delete k;//vô d?nh
				k = h;//nh?y l?i  : gi?a/vt liên ti?p/vt cách xa

				if (h->pnext == NULL)//h Ðang là cu?i => chúng ta v?a xóa cu?i
				{
					ds_sv.ptail = h;
					return;
				}
			}
			h = k;//nh?y theo k		= pt 2
			k = k->pnext;
		}
	}
}
void sap_xep(danh_sach_sv &ds_sv)//hoán v? data
{
	for (node_sv* k = ds_sv.phead;k->pnext != NULL;k = k->pnext)//áp cu?i
	{
		for (node_sv *h = k->pnext;h != NULL;h = h->pnext)//cu?i
		{
			if (_stricmp(h->data.ten.c_str(), k->data.ten.c_str()) < 0)
			{
				swap(k->data, h->data);
			}
			else if (_stricmp(h->data.ten.c_str(), k->data.ten.c_str()) == 0)
			{
				if (_stricmp(h->data.ho.c_str(), k->data.ho.c_str()) < 0)
				{
					swap(k->data, h->data);
				}
			}
		}
	}
}
