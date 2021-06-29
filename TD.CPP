#include<fstream.h>
#include<iomanip.h>
#include<conio.h>
#include<string.h>
#include<stdio.h>
class phoneBook{
	 char name[20],phno[15];
	 public:
	 void getdata();
	 void showdata();
	 void deletedata(char *n);
	 char *getname(){ return name; }
	 char *getphno(){ return phno; }
	 void update(char *nm,char *telno){
		  strcpy(name,nm);
		  strcpy(phno,telno);
	 }
};

void phoneBook :: getdata(){
	 cout<<"\t\nEnter Name : ";
	 gets(name);
	 cout<<"\t\nEnter Phone Number : ";
	 cin>>phno;
}

void phoneBook :: showdata(){
	 cout<<"\n\n -----------------------------------------------\n\n";
	 cout<<"\n\n -----------ADDRESS BOOK DETAILS-----------------\n\n";
	 cout<<"\n\n -----------------------------------------------\n\n";
	 cout<<"\n\n";
	 cout<<setw(20)<<name;
	 cout<<setw(15)<<phno;
}


void phoneBook::deletedata(char *n)
{
	phoneBook ac;
	ifstream inFile;
	ofstream outFile;
	inFile.open("phone.dat",ios::binary);
	if(!inFile)
	{
		cout<<"File could not be open !! Press any Key...";
		return;
	}
	outFile.open("Tempo.dat",ios::binary);
	inFile.seekg(0,ios::beg);
	while(inFile.read((char *) &ac, sizeof(phoneBook)))
	{
		if(strcmp(ac.getphno(),n)!=0)
		{
			outFile.write((char *) &ac, sizeof(phoneBook));
		}
	}
	inFile.close();
	outFile.close();
	remove("phone.dat");
	rename("Tempo.dat","phone.dat");
	cout<<"\n\n\tRecord Deleted .....\n\n";
}

void main(){
	 phoneBook rec;
	 fstream file;
	 file.open("phone.dat", ios::ate | ios::in | ios::out | ios::binary);
	 char ch,nm[20],tel[15],telno[15];
	 int choice,found=0;
	 do {
		  clrscr();
		  cout<<"\n\n-------------------Phone Book---------------------\n\n";
		  cout<<"1) Add New Record\n";
		  cout<<"2) Display All Records\n";
		  cout<<"3) Search Person Name\n";
		  cout<<"4) Search Telephone Number\n";
		  cout<<"5) Update Telephone No.\n";
		  cout<<"6) Deletion of Record\n";
		  cout<<"7) Exit\n";
		  cout<<"Choose your choice : ";
		  cin>>choice;
		  switch(choice){
				case 1 :
					  rec.getdata();
					  cin.get(ch);
					  file.write((char *) &rec, sizeof(rec));
					  break;

				case 2 : //Display All Records
					  file.seekg(0,ios::beg);
					  while(file){
						  file.read((char *) &rec, sizeof(rec));
						  if(!file.eof())
								rec.showdata();
					  }
					  file.clear();
					  getch();
					  break;

				case 3 : //Search Tel. no. when person name is known.
					  cout<<"\n\nEnter Name To Search : ";
					  gets(nm);
					  file.seekg(0,ios::beg);
					  found=0;
					  while(file.read((char *) &rec, sizeof(rec)))
					  {
						  if(strcmp(nm,rec.getname())==0)
						  {
								found=1;
								rec.showdata();
						  }
					  }
					  file.clear();
					  if(found==0)
						  cout<<"\n\n-----------Record Not found-------------\n\n";
					  getch();
					  break;

				case 4 : //Search name on basis of tel. no
					  cout<<"\n\nEnter Telephone No To Search : ";
					  cin>>telno;
					  file.seekg(0,ios::beg);
					  found=0;
					  while(file.read((char *) &rec, sizeof(rec)))
					  {
						  if(strcmp(telno,rec.getphno())==0)
						  {
								found=1;
								rec.showdata();
						  }
					  }
					  file.clear();
					  if(found==0)
						  cout<<"\n\n---------------Record Not found--------------------\n\n";
					  getch();
					  break;

				case 5 : //Update Telephone No.
					  cout<<"\n\nEnter Name : ";
					  gets(nm);
					  file.seekg(0,ios::beg);
					  found=0;
					  int cnt=0;
					  while(file.read((char *) &rec, sizeof(rec)))
					  {
						  cnt++;
						  if(strcmp(nm,rec.getname())==0)
						  {
								found=1;
								break;
						  }
					  }
					  file.clear();
					  if(found==0)
						  cout<<"\n\n-------------Record Not found-------------\n\n";
					  else
					  {
						  int location = (cnt-1) * sizeof(rec);
						  cin.get(ch);
						  if(file.eof())
								file.clear();

						  cout<<"Enter New Telephone No : ";
						  cin>>telno;
						  file.seekp(location);
						  rec.update(nm,telno);
						  file.write((char *) &rec, sizeof(rec));
						  file.flush();
					  }
					  getch();
					  break;
				case 6 : //Deletion on basis of tel. no
					  cout<<"\n\nEnter Telephone No To Delete : ";
					  cin>>telno;
					  file.seekg(0,ios::beg);
					  found=0;
					  while(file.read((char *) &rec, sizeof(rec)))
					  {
						  if(strcmp(telno,rec.getphno())==0)
						  {
								found=1;
								rec.deletedata(telno);
						  }
					  }
					  file.clear();
					  if(found==0)
						  cout<<"\n\n---------------Record Not found--------------------\n\n";
					  getch();
					  break;
	 }}  while(choice<=6);
	out:
	file.close();
	}