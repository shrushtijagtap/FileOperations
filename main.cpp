#include <fstream>
#include <iostream>
#include<cstring>
using namespace std;
 
class directory
{
int rollno;
char name[20];
char div;
char address[20];
public:
void add(directory k);
char* searchname(int p);
void display(directory k);
void delete_r(directory k);
void update(directory k);
};

void directory :: add(directory k)
{
    int rno;
    char n[20];
    char d;
    char a[20];
    char ans;
    while(1)
    {
    ofstream of;
    of.open("dt.data", ios::app | ios::binary);
    cout<<"Enter rollno name division and address \n";
    cin>>rno>>n>>d>>a;
    strcpy(k.name,n);
    k.rollno=rno;
    k.div=d;
    strcpy(k.address,a);
    of.write((char*)&k,sizeof(k));
    of.close();
    
    cout<<"Do you want to continue"<<endl;
    cin>>ans;
    if(ans=='n'||ans=='N')
   	 break;
    }
}
void directory :: display(directory k)
{
    fstream rd;
    rd.open("dt.data",ios::in | ios::binary);
    rd.read((char*)&k,sizeof(k));
    cout<<"roll no"<<"\t\t"<<"name"<<"\t\t"<<"div"<<"\t\t"<<"address"<<endl;
    while(rd)
    {
        cout<<k.rollno<<"\t\t"<<k.name<<"\t\t"<<k.div<<"\t\t"<<k.address<<endl;
        rd.read((char*)&k,sizeof(k));
    }
    rd.close();
}
char* directory :: searchname(int p)
{
    fstream fin;
    directory ob;
    fin.open("dt.data",ios::in | ios::binary);
    fin.read((char*)&ob,sizeof(ob));
    while(fin)
    {
            if(ob.rollno==p)
            {
              fin.close();
              cout<<"name is\t"<<ob.name<<endl;
              cout<<"div is\t"<<ob.div<<endl;
              cout<<"address is\t"<<ob.address<<endl;
            }
        fin.read((char*)&ob,sizeof(ob));
    }
    fin.close();
}
void directory ::delete_r(directory k)
{
int rn;
cout<<"Enter roll no whose record is to be deleted"<<endl;
cin>>rn;
ifstream fin;
ofstream o;
fin.open("dt.data",ios::in | ios:: binary);
o.open("temp.data",ios::out | ios:: binary);
while(fin.read((char*)&k,sizeof(k)))
{
      if(k.rollno!=rn)
      	o.write((char*)&k,sizeof(k));       
}
cout<<" DELETED .. ";
o.close();
fin.close();
remove("dt.data");
rename("temp.data","dt.data");
} 

void directory :: update(directory k)
{
    int rno;
    fstream fp;
    fp.open("dt.txt",ios::in | ios::binary | ios::out | ios::ate);
    fp.seekg(0, ios::beg);
    int pos = -1;
    int i = 0;
cout<<"Enter rollno whose record is to be deleted"<<endl;
cin>>rno;
    while(fp.read ((char *)&k, sizeof(k)))
    {
        if(rno==k.rollno)
        {
             pos = i;
            break;
         }
         i++;
    } 
    int offset = pos*sizeof(k);
    fp.seekp(offset);
    cout<<"enter div and updated address"<<endl;
    cin>>k.div>>k.address;
    fp.write((char *)&k,sizeof(k));
    cout<<"\n Record is updated";
    fp.seekg(0);
    fp.close();
}

int main()
{
directory obj;
	int choice;
	char N[20];
	double ph;
	do
	{
		cout<<"1.add data"<<endl;
		cout<<"2.display data"<<endl;
		cout<<"3.search by phone no."<<endl;
		cout<<"4.delete"<<endl;
		cout<<"5.update"<<endl;
		cout<<"6.EXIT"<<endl;
		cin>>choice;
		switch(choice)
		{
			case 1:obj.add(obj);
				    break;
			case 2:cout<<"Data is "<<endl;
				    obj.display(obj);
				    break;
			case 3:cout<<"Enter roll no whose name is to be searched"<<endl;
			        cin>>ph;
			        obj.searchname(ph);
			        break;
			case 4:obj.delete_r(obj);break;
			case 5:obj.update(obj);break;
			case 6:break;
			default:cout<<"invalid choice";
				      break;	
		}
	}while(choice!=6);
return 0;
}
