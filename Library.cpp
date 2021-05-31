//LIBRARY MANAGEMENT SOFTWARE

#include <iostream>
#include <fstream>
#include <string>
#include <windows.h>
#include <time.h>

using namespace std;

class BookOperation
{
	public:
		void bookDetailsEntry()
		{
			int book_id;
			char book_name[50], book_author[50];
			fstream fobj("lib_book_details.dat", ios::out|ios::app);
			
			cout << "\nEnter book ID : ";
			cin.sync();
			cin >> book_id;
			
			cout << "\nEnter book name : ";
			cin.sync();
			cin.getline(book_name,50);
			
			cout << "\nEnter book author : ";
			cin.sync();	
			cin.getline(book_author,50);
			
			fobj << " " << book_id << "      " << book_name << "      " << book_author << endl;
			fobj.close();	
				
			cout<<"\n--------Successfully Saved--------";
		}
		
		void searchBookDetails()
		{
			fstream fobj1("lib_book_details.dat", ios::in);
			label_search:
			cout << "\n\nSEARCH MENU ";
			cout << "\n1. Display all";
			cout << "\n2. Search";
			cout << "\n3. Exit";
			
			cout << "\nEnter your choice (1-3) : ";
			
			int choose;
			cin >> choose;
			switch (choose)
			{
				case 1 : 
					char str_line[500];
					char str_line1[500];
					if (fobj1.getline(str_line1, 500)!=NULL)
					{
						cout << "\n\n================================================================================";
						while(fobj1.getline(str_line,500)!=NULL)
						{
							cout<<"\n\n"<<str_line;	
						}
						cout<<"\n\n================================================================================\n\n";
					}
					else
					cout << "\nNo books found.";
					break;
				
					
				case 2 :
					char str_line2[500], str_line5[500];
					cout << "\nEnter book name : ";
					char bookname[10];
					cin.sync();
					cin.getline(bookname, 50);
					if (fobj1.getline(str_line5, 500)!=NULL)
					{
						cout<<"\n\n================================================================================";
						while(fobj1.getline(str_line2,500)!=NULL)
						{
							if(strstr(str_line2, bookname)!=NULL)
							cout<<"\n\n"<<str_line2;	
						}
						cout<<"\n\n================================================================================\n\n";
					}
					else
					cout <<"\nBook not found";
					break;
		
				case 3 :
					Sleep (500);
					cout << "\n\nExiting ";
					for (int i=0; i<=4; i++)
					{
						Sleep (500);
						cout << ".";
					}
					exit(0);
					break; 	
					
				default :
					cout << "\n....Invalid Choice....";
					goto label_search;
					break;			
			}
			fobj1.close();
		}
		
		void delete_book()
		{
			char temp_str[500];
			fstream fin("lib_book_details.dat",ios::in);
			cout << "\nDELETE MENU";
			cout << "\n1. Delete by book ID";
			cout << "\n2. Delete by book name";
			
			cout << "\n4. Enter your choice (1-2) : ";
			
			int choose_del;
			cin >> choose_del;
			switch(choose_del)
			{
				case 1:
					{
						char temp_search[500], bookID[50], temp_search1[500];
						int bookID;
						cout << "\nEnter the book ID : ";
						cin >> bookID;
						if (fin.getline(temp_search1, 500)!=NULL)
						{
							char q;
							cout << "\nAre you sure you want to delete (Y/N) : "; 
							cin >> q;
							if (q=='Y'||q=='y')
							{	
								fstream temp("temp.dat", ios::out|ios::app);
								temp << " " << bookID << "  " << endl;
								temp.close();
								fstream temp_bookID("temp.dat", ios::in);
								cin.sync();
								temp_bookID.getline(bookID, 50);
								temp_bookID.close();
								fstream fout("temp_lib.dat",ios::out|ios::app);
								while(fin.getline(temp_search, 500)!=NULL)
								{
									if (strstr(temp_search, bookID)==NULL)
									{
										fout << temp_search << endl;
									}
							}
							fin.close();
							fout.close();
							remove("lib_book_details.dat");
							rename("temp_lib.dat", "lib_book_details.dat");
							remove("temp.dat");
							cout << "\n....Successfully Deleted....";
						}
						else
						cout << "\nNo books are found to be deleted.";
						}
						break;
					}
				
				case 2:
					{
						cout << "\nEnter the full book name to delete that book data : ";
						char temp_search[500], temp_search1[500];
						cin.sync();
						cin.getline(temp_search, 500);
						if(fin.getline(temp_search1, 500)!=NULL)
						{
							char q;
							cout << "\nAre you sure you want to delete the record (Y/N)? ";
							cin >> q;
							if (q=='Y'|q=='y')
							{
								fstream fout("temp_lib.dat",ios::out|ios::app);
								while(fin.getline(temp_str, 500)!=NULL)
								{
									if(strstr(temp_str,temp_search)==NULL)
									{
										fout << temp_str << endl;
									}	
								}
								fin.close();
								fout.close();
								remove("lib_book_details.dat");
								rename("temp_lib.dat", "lib_book_details.dat");
								cout << "\n....Successfully Deleted....";	
							}
						}
						else
						cout << "\nNo books are found to be deleted";
						break;	
					}
		
					
					default:
						cout << "\n....Invalid Choice....";
						break;
			}
		}
		
		/*void update_book()
		{
			char temp1_str[500], temp1_str1[500];
			fstream fup("lib_book_details.dat", ios::in);
			fstream temp_up("temp1_lib.dat", ios::out|ios::app);
			int bo_ID;
			cout << "\nEnter the ID of the book that you want to update : ";
			cin >> bo_ID;
			if (fup.getline(temp1_str1, 500)!=NULL)
			{
				fstream temp("temp.dat", ios::out|ios::app);
				cin.sync();
				temp << " " << bo_ID << "  " << endl;
				temp.close();
				char ID[10];
				fstream temp1("temp.dat", ios::in);
				cin.sync();
				temp1.getline(ID, 10);
				temp1.close();
				remove("temp.dat");
				while(fup.getline(temp1_str, 500)!=NULL)
				{
					if(strstr(temp1_str, ID)!=NULL)
					{
						int bo_ID2;
						char bo_Name[50], bo_authoror[50];
						cout << "\nEnter new Book ID : ";
						cin >> bo_ID2;
						cout << "\nEnter new Book Name : ";
						cin.sync();
						cin.getline(bo_Name, 50);
						cout << "\nEnter new Book author : ";
						cin.sync();
						cin.getline(bo_authoror, 50);
						cin.sync();
						temp_up << " " << bo_ID2 << "      " << bo_Name << "      " << bo_authoror << endl;
					}
					else if (strstr(temp1_str, ID)==NULL)
					{
						temp_up << temp1_str << endl;
					}
					else
					{
						temp_up << temp1_str << endl;
					}
				}
				fup.close();
				temp_up.close();
				remove("lib_book_details.dat");
				rename("temp1_lib.dat", "lib_book_details.dat");
				cout << "\n....Successfully Updated....";
			}
			else
			cout << "\nNo books are found to be updated";
		}*/
		
		void admin_menu()
		{
			label_admin:
			string admin_pass=" ";
			cout << "\nEnter Administrator Password : ";
			cin.sync();
			getline(cin, admin_pass);
			if (admin_pass=="admin")
			{
				cout << "\a";
				cout << "\n\nADMINISTRATOR MENU";
				cout << "\n1. Delete Book Data";
				//cout << "\n2. Update Book Data";
				cout << "\n2. Reset Program";
				cout << "\n3. Exit Program";
				
				cout << "\nEnter choice (1-3) : ";
				
				int choose_admin;
				cin >> choose_admin;
				BookOperation bookop;
				switch (choose_admin)
				{
					case 1:
						bookop.delete_book();
						break;
					
					case 2:
						{
							char q_reset;
							cout << "\nAll saved data will be deleted and the program will be restored to defaults. Continue anyway? (Y/N) : ";
							cin >> q_reset;
							if (q_reset=='Y'|q_reset=='y')
							{
								cout << "\nResetting";
								for (int i=0; i<5; i++)
								{
									Sleep(500);
									cout << ".";
								}
								remove("lib_book_details.dat");
								remove("lib_issue_return.dat");
								cout << "\n....Restored to defaults....";
							}
							break;
						}
					case 3:
						Sleep (500);
						cout << "\n\nExiting ";
						for (int i=0; i<=4; i++)
						{
							Sleep (500);
							cout << ".";
						}
						exit(0);
						break;
					default:
						cout << "\n....Invalid Choice....";
						break;			
				}
			}
			else
			{
				cout <<"\n....Invalid Password....";
				goto label_admin;
			}
		}
};

class BookIssueReturn
{
	public :
		char date1[10];
		
		void issue_return()
		{
			string lib_pass=" ";
			cout << "\nEnter library password : ";
			cin.sync();
			getline(cin, lib_pass);
			if (lib_pass=="library"||lib_pass=="admin")
			{
				cout << "\a";
				BookIssueReturn bIR;
				cout << "\nISSUE AND RETURN SECTION";
				cout << "\n1. Issue book";
				cout << "\n2. Return book";
				cout << "\n3. Issue and Return status";
				cout << "\n4. Exit Program";
			
				cout << "\nEnter your choice (1-4) : ";
			
				int bir;
				cin >> bir;
				switch(bir)
				{
					case 1:
						bIR.issue_book();
						break;
					case 2:
						bIR.return_book();
						break;
					case 3:
						{
							fstream BIR("lib_issue_return.dat", ios::in);
							fstream BIR2("lib_issue_return.dat", ios::in);
							char tempstr[500], tempstr1[500];
							if (BIR.getline(tempstr1, 500)!=NULL)
							{
								cout << "\n\n===================================================================================================\n\n";
								while(BIR2.getline(tempstr, 500)!=NULL)
								{
									cout << tempstr << endl;
								}
								cout << "\n===================================================================================================";
								BIR.close();
								BIR2.close();
							}
							else
							cout << "\nNo books have been issued or returned.";
							break;
						}
					case 4:
						{
							Sleep (500);
							cout << "\n\nExiting ";
							for (int i=0; i<=4; i++)
							{
								Sleep (500);
								cout << ".";
							}
							exit(0);
							break;
						}	
					default:
						cout << "\n....Invalid Choice....";
						break;				
				}
			}
			else
			{
				cout << "\n....Wrong Password....";
			}
			
		}
		
		void issue_book()
		{
			
			int len=0, i, j, serial;
			char book_name_copy[50], str_copy[50];
			fstream bi_in("lib_issue_return.dat", ios::out|ios::in|ios::app);
			fstream temp_id("temp_id.dat", ios::out|ios::app);
			fstream bd_out("lib_book_details.dat", ios::in);
			fstream ir("issue_return.dat", ios::in);
			fstream ir2("issue_return.dat", ios::out|ios::app);
			char temp_copy[500], stu_name[50], book_id[10]; 
			cout << "\nEnter serial number : ";
			cin >> serial;
			cout << "\nEnter the name of the student you want to issue book to : ";
			cin.sync();
			cin.getline(stu_name, 50);
			cout << "\nEnter the ID of the book you want to issue to the student : ";
			int bookid;
			cin >> bookid;
			cin.sync();
			temp_id << " " << bookid << "  " << endl;
			fstream temp_id2("temp_id.dat", ios::in);
			cin.sync();
			temp_id2.getline(book_id, 10);
			temp_id2.close();
			remove("temp_id.dat");
			len=strlen(book_id);
			while(bd_out.getline(temp_copy, 500)!=NULL)
			{
				if (strstr(temp_copy, book_id)!=NULL)
				{
					int len2=0;
					for (i=len; temp_copy[i]!='\0'; i++)
					len2++;
					for (i=len+4, j=0; temp_copy[i]!='\0', j<len2; i++, j++)
					book_name_copy[j]=temp_copy[i];
				}
			}
			if (ir.getline(str_copy, 500)==NULL)
			{
				cin.sync();
				bi_in << " " << serial << "    " << stu_name << "    " << book_name_copy << "    " << _strdate(date1) << endl;
				ir2 << book_name_copy << endl;
				bi_in.close();
				bd_out.close();
				ir.close();
				ir2.close();
				remove("temp_id.dat");
				remove("temp_id2.dat");
				cout << "\n....Book Issued....";
			}
			else
			{
				int flag=0;
				char temp[500];
				while (ir.getline(temp, 500)!=NULL)
				{
					if (strstr(temp, book_name_copy)==NULL)
						continue;
					else
					{
						flag=1;
						break;
					}
				}
				if (flag==0)
				{
					cin.sync();
					bi_in << " " << serial << "    " << stu_name << "    " << book_name_copy << "    " << _strdate(date1) << endl;
					ir2 << book_name_copy << endl;
					bi_in.close();
					bd_out.close();
					ir.close();
					ir2.close();
					remove("temp_id.dat");
					remove("temp_id2.dat");
					cout << "\n....Book Issued....";
				}
				else
				{
					bi_in.close();
					bd_out.close();
					ir.close();
					ir2.close();
					remove("temp_id.dat");
					remove("temp_id2.dat");
					cout << "\nBook not available for issue.";
				}		
			}
		}
		
		void return_book()
		{
			char temp_str[500];
			char date2[10];
			cout << "\nRETURN MENU";
			cout << "\n1. Return by serial no.";
			cout << "\n2. Return by full book name";
			cout << "\nEnter your choice (1-2) : ";
			int choose_return;
			cin >> choose_return;
			switch (choose_return)
			{
				case 1:
					{
						int serial;
						cout << "\nEnter serial no of the issue return list : ";
						cin >> serial;
						fstream ser("temp.dat", ios::out|ios::app);
						cin.sync();
						ser << " " << serial << "    ";
						ser.close();
						char serial_copy[50];
						fstream ser1("temp.dat", ios::in);
						cin.sync();
						ser1.getline(serial_copy, 50);
						ser1.close();
						remove("temp.dat");
						int len=0;
						len=strlen(serial_copy);
						fstream book_return("lib_issue_return.dat", ios::in);
						char book_return[500], temp_copy[500];
						while(book_return.getline(book_return, 500)!=NULL)
						{
							if (strstr(book_return, serial_copy)!=NULL)
							strcpy(temp_copy, book_return);
						}
						book_return.close();
						fstream check("issue_return.dat", ios::in);
						char str_cpy[500];
						int flag=0;
						while(check.getline(str_cpy, 500)!=NULL)
						{
							if (strstr(temp_copy, str_cpy)==NULL)
							continue;
							else
							{
								flag=1;
								break;
							}
						}
						check.close();
						if (flag==1)
						{
							fstream book_rn("lib_issue_return.dat", ios::in);
							fstream bo_return("temp_ir.dat", ios::out|ios::app);
							while(book_rn.getline(book_return, 500)!=NULL)
							{
								if (strstr(book_return, serial_copy)==NULL)
								bo_return << book_return << endl;
								else
								bo_return << book_return << "    " << _strdate(date2) << endl;
							}
							book_rn.close();
							bo_return.close();
							remove("lib_issue_return.dat");
							rename("temp_ir.dat", "lib_issue_return.dat");
						}
						else
						{
							cout << "\nNo such book have been issued.";
						}
						break;
					}
					
				case 2:
					{
						fstream br_out("lib_issue_return.dat", ios::in);
						fstream temp_return("temp_return.dat", ios::out|ios::app);
						int flag=0;
						char temp_bn[50], temp[500], temp1[500];
						fstream ir("issue_return.dat", ios::in);
						cout << "\nEnter full book name : ";
						cin.sync();
						cin.getline(temp_bn, 50);
						if (ir.getline(temp1, 500)==NULL)
						{
							cout << "\nNo books are found to be returned";
						}
						else
						{
							while (ir.getline(temp1, 500)!=NULL)
							{
								if (strstr(temp1, temp_bn)!=NULL)
								{
									flag=1;
									break;
								}
							}
						}
						ir.close();
						if (flag==0)
							cout << "\nNo books are found to be returned";
						else
						{
							fstream ir2("issue_return_temp.dat", ios::out|ios::app);
							while(br_out.getline(temp, 500)!=NULL)
								{
									if (strstr(temp, temp_bn)!=NULL)
									{
										cin.sync();
										temp_return << temp << "    " << _strdate(date2) << endl;
									}
									else
									{
										cin.sync();
										temp_return << temp << endl;
									}
								}
							while (ir2.getline(temp1, 500)!=NULL)
							{
								if (strstr(temp1, temp_bn)==NULL)
								ir2 << temp_bn << endl;
							}
							br_out.close();
							remove("lib_issue_return.dat");
							temp_return.close();
							rename("temp_return.dat", "lib_issue_return.dat");
							ir2.close();
							remove("issue_return.dat");
							rename("issue_return_temp.dat", "issue_return.dat");
							cout << "\n....Book Returned....";
						}
						break;
					}
				
				default:
					cout << "\n....Invalid Choice....";
					break;	
			}
			
		}
};

void about()
{
	fstream about_out("lib_about.dat", ios::in);
	char about_str[500];
	cout << "\n\n==========================================================================================\n\n";
	while (about_out.getline(about_str, 500)!=NULL)
	{
		cout << about_str << endl;
	}
	cout << "\n==========================================================================================\n";
	about_out.close();
}

void main()
{
	system("COLOR 8F");
	char date[10];
	cout <<"\n                                   **** LIBRARY MANAGEMENT SOFTWARE ****                                   " << _strdate(date);
	BookOperation bo;
	BookIssueReturn bir;
	string pass =" ";
	label_main:
	cout << "\nEnter Program Password : ";
	cin.sync();
	getline(cin, pass);	
	if (pass=="project")
	{
		cout << "\a";
		int choice;
		while(1)
		{
			cout << "\n\nMAIN MENU";
			cout << "\n1. Book Details Entry";
			cout << "\n2. Search Book Details";
			cout << "\n3. Administrator Menu";
			cout << "\n4. Issue and Return Section";
			cout << "\n5. About";
			cout << "\n6. Exit Program";
		
			cout << "\nEnter your choice (1-6) : ";
			cin >> choice;
		
			switch(choice)
			{
				case 1:
					bo.bookDetailsEntry();
					break;
				case 2:
					bo.searchBookDetails();
					break;
				case 3:
					bo.admin_menu();
					break;
				case 4:
					bir.issue_return();
					break;
				case 5:
					about();
					break;	
				case 6:
					Sleep (500);
					cout << "\n\nExiting ";
					for (int i=0; i<=4; i++)
					{
						Sleep (500);
						cout << ".";
					}
					exit(0);
					break;
				default:
					cout << "\n....Invalid Choice....";				
			}
		}
	}
	else
	{
		cout <<"\n....Invalid Password....";
		goto label_main;
	}

}
