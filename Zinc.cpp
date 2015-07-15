#include<iomanip.h>
#include<iostream.h>
#include<conio.h>
#include<stdio.h>
#include<string.h>
#include<fstream.h>
#include<time.h>
#include<process.h>
#include<stdlib.h>
void dis(long);

void showtime()
{	time_t now =time(0);
	tm *ptr=localtime(&now);
	asctime(ptr);
	cout<<"\t\t\t\t\t\tDate: "<<ptr->tm_mday<<"/"<<ptr->tm_mon+1<<"/"
	    <<(1900+ptr->tm_year);
}

class client
{
private:
	int sno,billno,nrmt,billamt;
	long empcd,baccno;
	static int count;
	char ename[20],desig[40],dcode,btcode,dept[40],bname[20];

public:
       tm t;
       void ini()
       {	sno=0;
		nrmt=billamt=0;
		billno=1800;
       }
       void inc()
       {	sno+=1;
		billno+=1;
       }
       void edata(long);
       friend void show();
       friend void notice();
       friend void bill();
       friend long searchi();
       friend void badisp();
       friend long search();
       void head();
       long getcode()
       {	return   empcd;
       }
       int get()
       {	return billamt;
       }
       void dis1();
       void display();
       void print();
}ob;

int cint(int);
void head();
int see(long);

void bill()
{	ifstream file("emp.txt",ios::binary);
	client oob;

     long i;
	i=searchi();

	  if(i==0)
	  {
		cout<<"\n\n\n\t\t\t(PLEASE run option 1 of Menu bar)";
		file.close();
		return;
	      }

	while(!file.eof())
	{	file.read((char *)& oob,sizeof(client));
		if(oob.getcode()==i)
		break;
	}
	file.close();
	client ob1;
	strcpy(ob1.ename,oob.ename);
	strcpy(ob1.dept,oob.dept);
	strcpy(ob1.desig,oob.desig);
	strcpy(ob1.bname,oob.bname);
	ob1.sno=ob.sno+=1;
	ob1.billno=ob.billno+=1;
	ob1.nrmt=oob.nrmt;
	ob1.baccno=oob.baccno;
	ob1.empcd=i;
	cout<<"\n\n\t\t\tENTER BILL AMOUNT:-  \t";
	fflush(stdin);
	cin>>ob1.billamt;
	cout<<"\n\n\t\t\tENTER DEPENDENT CODE:-  \t";
	fflush(stdin);



		cout<<"\n\t\t\t\t ENTER h FOR SELF" ;
		cout<<"\n\t\t\t\t ENTER w FOR WIFE" ;
		cout<<"\n\t\t\t\t ENTER f FOR FATHER" ;
		cout<<"\n\t\t\t\t ENTER m FOR MOTHER" ;
		cout<<"\n\t\t\t\t ENTER s FOR SON" ;
		cout<<"\n\t\t\t\t ENTER d FOR DAUGHTER" ;
		cout<<"\n\t\t\t\t ENTER o FOR OTHER" ;

	      do{
		cout<<"\n\t\t\t ENTER CODE :";
		   cin>>ob1.dcode;



	   if(ob1.dcode=='l'||ob1.dcode=='w'|| ob1.dcode=='f'||ob1.dcode=='m'||ob1.dcode=='s'||ob1.dcode=='d' ||ob1.dcode=='o')
		    break;
	   else
	    {
	     cout<<"\n\n\t\tWRONG CHOICE\n\t\tENTER CORRECT OPTION...";
	    }
	}while(ob1.dcode!='l'||ob1.dcode!='w'|| ob1.dcode!='f'||ob1.dcode!='m'||ob1.dcode!='s'||ob1.dcode!='d' ||ob1.dcode!='o');



	cout<<"\n\n\t\t\tENTER BILLTYPE CODE:-  \t";
	fflush(stdin);
	cout<<"\n\t\t\t\t ENTER c FOR COMPANY's DOCTOR";
	cout<<"\n\t\t\t\t ENTER g FOR GOVT.DOCTOR";
	cout<<"\n\t\t\t\t ENTER r FOR REFERAL DOCTOR";
	cout<<"\n\t\t\t\t ENTER a FOR AYURVEDIC DOCTOR";
	cout<<"\n\t\t\t\t ENTER h FOR HOMEOPATHIC DOCTOR";
	cout<<"\n\t\t\t\t ENTER u FOR UNANI";
	cout<<"\n\t\t\t\t ENTER o FOR OTHER";


	 do {
		cout<<"\n\t\t\t ENTER CODE :";
		cin>>ob1.btcode;
		if(ob1.btcode=='c'||ob1.btcode=='g'||ob1.btcode=='r'||ob1.btcode=='a'||ob1.btcode=='h'||ob1.btcode=='u'||ob1.btcode=='o')
		  break;
		else
		{ cout<<"\n\n\t\t\tWRONG CHOICE\n\t\tENTER CORRECT OPTION";
		}
	  }while(ob1.btcode!='c'||ob1.btcode!='g'||ob1.btcode!='r'||ob1.btcode!='a'||ob1.btcode!='h'||ob1.btcode!='u'||ob1.btcode!='o');

	time_t now= time(0);
	tm *ptr=localtime(&now);
	asctime(ptr);
	ob1.t.tm_sec=ptr->tm_sec;
	ob1.t.tm_min=ptr->tm_min;
	ob1.t.tm_hour=ptr->tm_hour;
	ob1.t.tm_mday=ptr->tm_mday;
	ob1.t.tm_mon=ptr->tm_mon;
	ob1.t.tm_year=ptr->tm_year;
	ofstream o("emp.txt",ios::app|ios::binary);
	o.write((char*)&ob1,sizeof ob1);
	o.close();
	}




void filecopy()
{
       fstream file("emp.txt",ios::in|ios::binary);
       if(!file)
       {
	    cout<<"\n\n\n\t\t\t-*** NO RECORD PRESENT ***-";
	    return;
       }
       ofstream f("bill.txt",ios::binary);
       client ob1;
       fflush(stdin);
       while(file.read((char*)&ob1,sizeof ob1))
       {
	    f.write((char*)&ob1,sizeof ob1);
       }
       file.close();
       f.close();
}
void client::display()
{

       ifstream file("emp.txt",ios::binary);
       int total=0,tamt=0;

       if(!file)
       {
	    cout<<"\n\n\n\t\t\t-*** NO RECORD PRESENT ***-";
	    file.close();
	    return;
       }

       client ob1;
       filecopy();
       long ecode[20];
       int i=0,flag=0;
       for(i=0;i<20;i++)
       ecode[i]=0;
       i=0;
       fflush(stdin);
       while( file.read((char*)&ob1,sizeof ob1))
       {
	    for(int c=0;c<=i;c++)
	    if(ecode[c]==ob1.empcd||ob1.billamt==0)
	    {
		 flag=1;
	    }
	    if(flag!=1)
	    {
		 ecode[i]=ob1.empcd;
		 i++;
		 dis(ecode[i-1]);
		 total=total+1;
	    }
	    flag=0;
	    cout<<endl;

	    tamt=tamt+ob1.billamt;
	}

	cout<<"\nTOTAL NO OF EMPLOYEE = "<<total;
	cout<<"\n\n\tTOTAL AMOUNT = "<<tamt;
	file.close();
}
void dis2(int bill)
{
	int i=0;
	cout<<endl;
	for(i;i<29;i++)
	cout<<" ";
	cout<<"EMPLOYEE TOTALS";
	for(i=0;i<9 ;i++)
	cout<<" ";
	for(i=0;i<10;i++)
	cout<<"-";
	cout<<endl;
	for(i=0;i<34;i++)
	cout<<" ";
	cout<<"0";
	for(i=0;i<18;i++)
	cout<<" ";
	cout<<bill;
	cout<<endl<<endl<<endl;
}
void client::dis1()
{
	int j,l,k;
	cout<<empcd<<" ";
	for( k=0;ename[k]!='\0';k++)
	cout<<ename[k];
	l=strlen(ename);
	for(j=0;j<13-l+2;j++)
	cout<<" ";
	for( k=0;dept[k]!='\0';k++)
	cout<<dept[k];
	l=strlen(dept);
	for(j=0;j<11-l+1;j++)
	cout<<" ";
	cout<<nrmt<<"     "<<dcode<<"    "<<billno<<"    "<<billamt;
	l=cint(billamt);
	cout<<setw(6-l+10);
	cout<<t.tm_mday<<"/"<<t.tm_mon<<"/"<<(t.tm_year+1900);
	cout<<endl;
}
void client::print()
{
	int i=0;
	for(i;i<34;i++)
	cout<<" ";
	cout<<nrmt;
	cout<<"     "<<dcode<<"    "<<billno<<"    "<<billamt;
	cout<<endl;
}
void dis(long ecode)
{
	ifstream file("bill.txt",ios::binary);
	client ob1,ob2;
	int c=0,bill=0;
	fflush(stdin);
	while(file.read((char*)&ob1,sizeof ob1))
	{
	      if(ecode==ob1.getcode()&&ob1.get()!=0)
	      {
		     ob2=ob1;
		     c++;
	      }
	}
	file.close();
	ob2.dis1();
	bill=ob2.get();
	if(c>1)
	{
	     fflush(stdin);
	     file.open("bill.txt",ios::in|ios::binary);
	     int i=1;
	     while(file.read((char*)&ob1,sizeof ob1))
	     {
		    if(ecode==ob1.getcode()&&ob1.get()!=0)
		    {
			  if(i<=(c-1))
			  {
			       i++;
			       ob1.print();
			       bill+=ob1.get();
			  }
		    }
	     }
	}
	dis2(bill);
}
int cint(int n)
{
	int l=1,no=n;
	while(no>0)
	{
	     no=no/10;
	     if(no>0)
	     l++;
	}
	return l;
}

void client::edata(long l)
{
	fflush(stdin);
	empcd=l;
	fflush(stdin);
	cout<<"\n\n\t\tENTER EMPLOYEE NAME:- ";
	fflush(stdin);
	gets(ename);
	cout<<"\n\n\t\tENTER EMPLOYEE DESIGNATION:- ";
	fflush(stdin);
	gets(desig);
	cout<<"\n\n\t\tENTER EMPLOYEE DEPARTMENT:- ";
	fflush(stdin);
	gets(dept);
	fflush(stdin);
	cout<<"\n\n\t\tENTER EMPLOYEE BANK NAME:- ";
	fflush(stdin);
	gets(bname);
	cout<<"\n\n\t\tENTER EMPLOYEE ACCOUNT NO:- ";
	fflush(stdin);
	cin>>baccno;
}
int see(long code)
{
	fflush(stdin);
	ifstream file("emp.txt",ios::binary);
	client ob1;
	int n=0;
	if(!file)
	{
	     file.close();
	     return 0 ;
	}
	while(!file.eof())
	{
	     file.read((char *)& ob1,sizeof(client));
	     if(ob1.getcode()==code)
	     {
		    n=1;
		    file.close();
		    return n;
	     }
	}
	file.close();
	return 0;
}
void show()
{
	ifstream  file;
	file.open("emp.txt",ios::binary);
	fflush(stdin);
	client ob1;
      int l;
	int total=0,tamt=0;
	if(!file)
	{
	     cout<<"\n\n\n\t\t\t-*** NO RECORD PRESENT ***-\n";
	     return;
	}
	while(file.read((char *)&ob1,sizeof ob1))
	{    if(ob1.billamt==0)
		continue;
	     cout<<endl;
	     cout<<ob1.sno;
	     l=cint(ob1.sno);
	     for(int j=0;j<4-l+2;j++)
	     cout<<" ";
	     cout<<ob1.empcd<<"  ";
	     for(int k=0;ob1.ename[k]!='\0';k++)
	     cout<<ob1.ename[k];
	     l=strlen(ob1.ename);
	     for(j=0;j<13-l+7;j++)
	     cout<<" ";
	     for( k=0;ob1.desig[k]!='\0';k++)
	     cout<<ob1.desig[k];
	     l=strlen(ob1.desig);
	     for(j=0;j<11-l+7;j++)
	     cout<<" ";
	     cout<<ob1.billno;
	     cout<<"    ";
	     cout<<ob1.billamt;
	     l=cint(ob1.billamt);
	     for(j=0;j<7-l+2;j++)
	     cout<<" ";
	     cout<<ob1.nrmt<<"     "<<ob1.dcode;
	     cout<<endl;
	     total=total+1;
	     tamt=tamt+ob1.billamt;
	}
	cout<<"\n\n\n\t";
	cout<<"TOTAL NO OF EMPLOYEE= "<<total;
	cout<<"\n\n\tTOTAL AMOUNT= "<<tamt;
	file.close();
}

struct Emp
{
 long int EmpCode;
 int BillAmount;
 int NrmAmount;
};
struct Emp emp_details[100];

void notice()
{
	ifstream  file;
	int i=0;
	long int tempCode=0;
	int tempBillAmt, tempNrmAmt=0;
	fflush(stdin);
	file.open("emp.txt",ios::binary);
	client ob1;
	int total=0,tamt=0;
	if(!file)
	{
	     cout<<"\n\n\n\t\t\t-*** NO RECORD PRESENT ***-";
	     return;
	}
	while(file.read((char *)&ob1,sizeof (ob1)))
	{    if(ob1.get()==0)
		continue;

		emp_details[i].EmpCode =ob1.empcd;
		emp_details[i].BillAmount =ob1.billamt;
		emp_details[i].NrmAmount=ob1.nrmt;


	     i++;

	}

	file.close();
	for(int j=0;j<i;j++)
	{
	   for (int k=0;k<i-1-j;k++)
	   {
	       if(emp_details[k].EmpCode>emp_details[k+1].EmpCode)
	       {
		     tempCode= emp_details[k].EmpCode;
		     tempBillAmt=emp_details[k].BillAmount;
		     tempNrmAmt=emp_details[k].NrmAmount;

		     emp_details[k]=emp_details[k+1] ;

		     emp_details[k+1].EmpCode =tempCode;
		     emp_details[k+1].BillAmount =tempBillAmt;
		     emp_details[k+1].NrmAmount =tempNrmAmt;
		 }

	   }
	   cout<<"\n\n"<<emp_details[k].EmpCode<<"\t\t"<<emp_details[k].BillAmount<<"\t\t"<<emp_details[k].NrmAmount;
	    total=total+1;
	     tamt=tamt+emp_details[k].BillAmount;
	}

	cout<<"\n\n\n\t";
	cout<<"TOTAL NO OF EMPLOYEES=  "<<total;
	cout<<"\n\n\tTOTAL AMOUNT=  "<<tamt;


}
struct bank
{ long cd,bacc;
  char empname[20],bankname[20];
  int billamount;
};


  void badisp()
      {        struct bank e[100];
		 struct bank t[100];

	       int j,i=0;
		ifstream  file;
		file.open("emp.txt",ios::binary);
		fflush(stdin);
		client ob1;
		int l;
		int total=0, tamt=0;
		 if(!file)
		   {
			cout<<"\n\n\n\t\t\t-*** NO RECORD PRESENT ***-";
			file.close();
			return;
		   }



		while(file.read((char *)&ob1,sizeof (ob1)))
		       {
			  if(ob1.get()==0)
			    continue;
			      e[i].cd=ob1.empcd;
			      e[i].bacc=ob1.baccno;
			      strcpy(e[i].empname,ob1.ename);
			      strcpy(e[i].bankname,ob1.bname);
			      e[i].billamount=ob1.billamt;
			  i++;
			}
		 file.close();


		  int v=0,x=0;
		     //  t[0].cd=0;


		   for(j=1;j<=i;j++)
		    {   int flag=0;
		      for(int w=0;w<v;w++)
			{

			  if(t[w].cd==e[x].cd)
			   {
			     t[w].billamount=t[w].billamount+e[x].billamount;
			     flag=1;
			   }
			}

		     if(flag==0)
		       {
			 t[w].cd=e[x].cd;
			 t[w].bacc= e[x].bacc;
			 strcpy(t[w].empname,e[x].empname);
			 strcpy(t[w].bankname,e[x].bankname);
			 t[w].billamount=e[x].billamount;
			 v++;
		       }
		   x++;
		  }

	for ( int k=0;k<v;k++)
	 {
	       cout<<"\n\n"<<k+1;
	      cout<<"\t"<<t[k].cd<<"\t \t";
	   for(int s=0;t[k].empname[s]!='\0';s++)
	     cout<<t[k].empname[s];
	     cout<<"\t\t ";
	  for(s=0;t[k].bankname[s]!='\0';s++)
	     cout<<t[k].bankname[s];
	     cout<<"\t\t "<<t[k].bacc;
	     cout<<"\t \t"<<t[k].billamount;
	    total=total+1;
	      tamt=tamt+t[k].billamount;
      }
		cout<<"\n\n\n\t";
	cout<<"\n\n\tTOTAL AMOUNT= "<<tamt;
	cout<<"\n\n\tTOTAL NO OF EMPLOYEE= " <<total;

 }

long searchi()
{
	long code;
	int no=0;
	ifstream  file;
	fflush(stdin);
	file.open("emp.txt",ios::binary);
	client ob1;
	cout<<"\n\n\t\t\tENTER EMPLOYEE code:-   ";
	cin>>code;
	if(!file)
	{
	     cout<<"\n\n\n\t\t\t\t-*** NO RECORD PRESENT ***-";
	     file.close();
	     return 0;
	}
	while(!file.eof())
	{
	     file.read((char *)& ob1,sizeof(client));
	     if(ob1.getcode()==code)
	     {
		   no=2;
		   cout<<"\n\t\t\t\t-***  RECORD PRESENT ***-";
			cout<<"\n\n\t\t\tEMPLOYEE NAME:-   ";
      puts(ob1.ename);
    /*  cout<<"\n\n\n\t\t\tEMPLOYEE DESIGNATION:-   ";
	puts(ob1.desig);
	cout<<"\n\n\n\t\t\tEMPLOYEE DEPARTMENT:-   ";
	puts(ob1.dept); */
		   break;
	     }
	}
	if(no!=2)
	{
	     cout<<"\n\n\n\t\t\t---*******  NO RECORD IS PRESENT OF THIS CODE *******---";
	     return 0;
	}
     /*	cout<<"\n\n\n\n\n\t\t\tEMPLOYEE NAME:-   ";
   puts(ob1.ename);
  cout<<"\n\n\n\t\t\tEMPLOYEE DESIGNATION:-   ";
	puts(ob1.desig);
	cout<<"\n\n\n\t\t\tEMPLOYEE DEPARTMENT:-   ";
	puts(ob1.dept);
	file.close(); */
     return code;;
}

long search()
{
	long code;
	int no=0;
	ifstream  file;
	fflush(stdin);
	file.open("emp.txt",ios::binary);
	client ob1;
	cout<<"\n\n\t\t\tENTER EMPLOYEE CODE:-   ";
	cin>>code;
	if(!file)
	{
	     cout<<"\n\n\n\t\t\t\t-*** NO RECORD PRESENT ***-";
	     file.close();
	     return 0;
	}
	while(!file.eof())
	{
	     file.read((char *)& ob1,sizeof(client));
	     if(ob1.empcd==code)
	     {
		   no=2;
		   cout<<"\n\t\t\t\t-***  RECORD PRESENT ***-";
			cout<<"\n\n\t\t\tEMPLOYEE NAME:-   ";
		       puts(ob1.ename);
    cout<<"\n\n\n\t\t\tEMPLOYEE DESIGNATION:-   ";
	puts(ob1.desig);
	cout<<"\n\n\n\t\t\tEMPLOYEE DEPARTMENT:-   ";
	puts(ob1.dept);
		   break;
	     }
	}
	if(no!=2)
	{
	     cout<<"\n\n\n\t\t\t---*******  NO RECORD IS PRESENT OF THIS CODE *******---";
	  //   return 0;
	}
     /*	cout<<"\n\n\n\n\n\t\t\tEMPLOYEE NAME:-   ";
   puts(ob1.ename);
  cout<<"\n\n\n\t\t\tEMPLOYEE DESIGNATION:-   ";
	puts(ob1.desig);
	cout<<"\n\n\n\t\t\tEMPLOYEE DEPARTMENT:-   ";
	puts(ob1.dept);
	file.close(); */
     return code;;
}
void client::head()
{
	cout<<"\t\t\t HINDUSTAN ZINC LIMITED, UDAIPUR\n";
	cout<<"\n\t\t\t   (A public limited company)\n";
	cout<<"\t\t\t   **************************\n";
	cout<<endl;
}
void main()
{
	clrscr();
	cout<<"\t\t       WELLCOME IN MEDICAL-BILLING SOFTWARE\n\n";
	cout<<"\t\t   HINDUSTAN ZINC LIMITED, DEBARI (VEDANTA GROUP OF COMPANIES)";
	cout<<"\n\n\n\n\nPrepared by :\n\nNEERAJ SUTHAR";
	getch();
	ob.ini();
	clrscr();
	int i,n;
	char ch,z,y,x;
	ofstream o;
	fflush(stdin);
	do
	{
	   ob.head();
	   cout<<"\t\t       WELLCOME IN MEDICAL-BILLING SOFTWARE\n\n";
	   cout<<"HINDUSTAN ZINC LIMITED, DEBARI (VEDANTA GROUP)";
	   showtime();

	   for(int b=0;b<80;b++)
	   cout<<"-";
	   cout<<"\n\n\n\t\t\t  * MAIN MENU *\t\n";
	   cout<<"\n\n\n\t\t\t 1. ENTER EMPLOYEE DATA.\n\n\n\t\t\t ";
	   cout<<"2. ENTER BILL AMOUNT.\n\n\n\t\t\t";
	   cout<<" 3. DISPLAY BILLWISE CHECKLIST.\n\n\n\t\t\t ";
	   cout<<"4. DISPLAY PAYMENT LIST OF BILLS.\n\n\n\t\t\t ";
	   cout<<"5. DISPLAY NOTICE BOARD.\n\n\n\t\t\t ";
	   cout<<"6. DISPLAY BANK ACCOUNT LIST.\n\n\n\t\t\t ";
	   cout<<"7. SEARCH THE EMPLOYEE.\n\n\n\t\t\t 8. EXIT.";
	   cout<<"\n\n\n\t\t\t ENTER YOUR CHOICE :\t";
	   cin>>n;
	   clrscr();
	   switch(n)

	     case 1:
	     {
	     ob.head();
	     cout<<"\n\t\t           WORKMEN DATA ENTRY PAGE\n\n";
	     cout<<"DEBARI,ZINC SMELTER";
	     showtime();
	     for(int b=0;b<80;b++)
	     cout<<"-";
	     int i=0;
	     long ll;
	     do
	     {
	     cout<<"\n\n\t\tENTER EMPLOYEE CODE:-";
	     fflush(stdin);
	     cin>>ll;
	     if(ll<100000 || ll>999999)
	     cout<<"\n\n\n\t\t-*** INVALID EMPLOYEE CODE ***-\n\n\t"<<
	     "\t (PLEASE ENTER SIX DIGIT CODE)";
	     else
	     {
		i=see(ll);
		if(i==1)
		{
		   cout<<"\n\n\n\t\tRECORD ALREADY PRESENT WITH THIS CODE";
		   cout<<"\n\n\t\t(PLEASE ENTER NEW CODE)";
		}
		else
		{
		   time_t now=time(0);
		   tm *t1=localtime(&now);
		   asctime(t1);
		   ob.t.tm_sec=t1->tm_sec;
		   ob.t.tm_min=t1->tm_min;
		   ob.t.tm_hour=t1->tm_hour;
		   ob.t.tm_mday=t1->tm_mday;
		   ob.t.tm_mon=t1->tm_mon;
		   ob.t.tm_year=t1->tm_year;
		   ob.edata(ll);
		   ob.inc();
		   o.open("emp.txt",ios::app|ios::binary);
		   o.write((char*)&ob,sizeof(ob));
		   o.close();

		}
	     }
	     cout<<"\n\n\t PRESS (Y/y) TO CONTINUE ELSE PRESS ANY OTHER KEY:-";
	     cin>>z;
	     }
	     while(z=='y'||z=='Y');
		     break;

	     case 2:
	     clrscr();
	     ob.head();
	     cout<<"\n\t\t           BILL AMOUNT ENTRY LIST\n\n";
	     cout<<"DEBARI,ZINC SMELTER";
	     showtime();
	     for(int qq=0;qq<80;qq++)
	     cout<<"-";
	     fflush(stdin);
	     do
	     {
	     bill();
	     cout<<"\n\n\t PRESS (Y/y) TO CONTINUE ELSE PRESS ANY OTHER KEY:-";
	     cin>>y;
	     }
	     while(y=='y'||y=='Y');
	     break;

	     case 3:
	     clrscr();
	     ob.head();
	     cout<<"\t\t          MEDICAL BILLWISE CHECKLIST     OF WORKMEN";
	     cout<<" \n\nDEBARI,ZINC SMELTER";
	     showtime();
	     for(int q=0;q<80;q++)
	     cout<<"-";
	     cout<<"Slno"<<"  "<<"Empcd"<<"   "<<"EMPLOYEE NAME";
	     for(i=0;i<7;i++)
	     cout<<" ";
	     cout<<"Designation";
	     for(i=0;i<7;i++)
	     cout<<" ";
	     cout<<"BillNo"<<"  "<<"Billamt"<<"  "<<"Nrmt"<<"  "<<"Dcode\n";
	     for(int v=0;v<80;v++)
	     cout<<"-";
	     cout<<"\n";
	     show();
	     break;

	     case 5:
	     clrscr();
	     ob.head();
	     cout<<"\n\t\t  NOTICE BOARD\WORKMEN MEDICAL REIMBURSEMENT LIST\n\n";
	     cout<<"DEBARI,ZINC SMELTER";
	     showtime();
	     for(int h=0;h<80;h++)
	     cout<<"-";
	     cout<<"\tEMP.NO.\t"<<"\t"<<" RS.\t"<<"\tNR-RS\t";
	  //   <<"\tDATE AND TIME\n" ;
	     for(int g=0;g<80;g++)
	     cout<<"-";
	     cout<<"\n";
	     notice();

	     break;

	     case 6:
	     clrscr();
	     ob.head();
	     cout<<"\n\t\t           WORKMEN BANK ACCOUNT LIST\n\n";
	     cout<<"DEBARI,ZINC SMELTER";
	     showtime();
	     for(int z=0;z<80;z++)
	     cout<<"-";
	     cout<<"Slno"<<"   "<<"Empcd"<<"     "<<"EMPLOYEE NAME";
	     for(i=1;i<=10;i++)
	     cout<<" ";
	     cout<<"BANK NAME      "<<"    "<<"BANK a/c"<<"    "<<"AMOUNT";
	     cout<<"\n";
	     for(int l=0;l<80;l++)
	     cout<<"-";
	     badisp();
	     break;

	     case 4:
	     clrscr();
	     ob.head();
	     cout<<"\n\t\t        EMPLOYEEWISE PAYMENT LIST OF BILLS\n\n";
	     cout<<"DEBARI,ZINC SMELTER";
	     showtime();
	     for(int zx=0;zx<80;zx++)
	     cout<<"-";
	     cout<<"EMPCD"<<"  "<<"EMPLOYEE NAME"<<"  "<<"DEPARTMENT"
	     <<"  "<<"NRMT"<<"  "<<"DCODE"<<"  "<<"BILLNO"
	     <<"  "<<"BILLAMT"<<"  "<<"PAY."<<"  "<< "DATE"<<"  "<<"SIGN.";
	     cout<<endl;
	     for( zx=0;zx<80;zx++)
	     cout<<"-";
	     ob.display();
	     break;

	     case 7:
	     clrscr();
	     ob.head();
	     cout<<"\n\t\t             INFORMATION OF WORKMEN\n\n";
	     cout<<"DEBARI,ZINC SMELTER";
	     showtime();
	     for(int t=0;t<80;t++)
	     cout<<"-";
	     do
	     {
	     search();
	     cout<<"\n\n\t PRESS (Y/y) TO CONTINUE ELSE PRESS ANY OTHER KEY:--";
	     cin>>x;
	     }
	     while(x=='y'||x=='Y');
	     break;

	     case 8:
	     goto ll;

	     default:
	     ob.head();
	     for(int zz=0;zz<80;zz++)
	     cout<<"-";
	     cout<<"\n\n\n\n\t\t\t--*** WRONG CHOICE ***--\n\n\t";
	   }
	  do{
	     cout<<"\n\n\n\n\n\t\tIF YOU WANT TO GO TO MAIN MENU THEN PRESS (g/G)--  ";
	     cin>>ch;
	   if(ch!='g')
	   { cout<<"\n WRONG CHOICE"; }
	   }while(ch!='g');
	   clrscr();
	}while(ch=='g'|| ch=='G');
	ll:	 cout<<" ";
	clrscr();
	cout<<"\nPrepared by:\n\nNEERAJ SUTHAR\nB.TECH-2nd YEAR(INFORMATION TECHNOLOGY)";
	cout<<"\nCOLLEGE OF TECHNOLOGY AND ENGINEERING, UDAIPUR\n\n";
	cout<<"\nPress Any Key to EXIT this program.\n\nThanks For VISIT.";
	getch();
}





