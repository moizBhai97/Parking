#include <iostream>
#include <fstream>
#include<conio.h>
#include<windows.h>
#include<iomanip>
#include<string>

using namespace std;

string name;
const int max_park=5;
int vehicle_count;

void create();
void write();
void main_page();
void admin();
void staff();
void new_admin();
void new_staff();
void delete_admin();
void delete_staff();
void write2();
void edit();
void stats();
void display();
void set_index(char &ch, int &num);
int payment(string, int, int);
bool token_check(string );
void initial_vehicle_count();

void clear()
{
   system("cls");
}

int payment(string line,int ex_hour,int ex_min)
{
    int count=0;
    for(int i=0; line[i]!=':';i++)
    {
        count++;
    }

    int start= (int(line[count-2]-'0')*10+int(line[count-1]-'0'))*60 + (int(line[count+1]-'0')*10+int(line[count+2]-'0'));

    int end=ex_hour*60+ex_min;
    int total=end-start;

    if(total>0 && total<=60 && line[6]=='c')
      return 50;
    else if(total>0 && total<=60 && line[6]=='b')
      return 30;
    else if(total>60 && total<=120 && line[6]=='c')
      return 100;
    else if(total>60 && total<=120 && line[6]=='b')
      return 50;
    else if(total>120 && line[6]=='c')
      return 300;
    else if(total>120 && total<=2 && line[6]=='b')
      return 100;
    else if(total<0)
      return -1;
}

 void create()
 {
     clear();
     int day,month,year,count=0;
     string name;

     cout<<"Enter file name:(in .txt format)(Enter 0 to exit) ";
     cin>>name;

     if(name=="0")
        staff();

     for(int i=0; name[i]!='\0';i++)
     {
         if(i>0 && name[i]=='.')
           count++;
     }

     if(count>0 && name[count+1]=='t' && name[count+2]=='x' && name[count+3]=='t' && name[count+4]=='\0')
     {
         ofstream in_file(name);

        cout<<"Enter Date:"<<endl;

        cout<<endl<<"Enter month: ";
        do
        {
            while(!(cin>>month))
            {
                 cout<<"Error! Enter a number: ";
                 cin.clear();
                 cin.ignore(1000,'\n');
            }

            if(month>0 && month <13)
              break;
            else cout<<"Error! Retry: ";

        }while(1);

        cout<<"Enter day: ";
        do
        {
            while(!(cin>>day))
            {
                 cout<<"Error! Enter a number: ";
                 cin.clear();
                 cin.ignore(1000,'\n');
            }

            if((day>0 && day<32 && month!=2) || (month==2 && day>0 && day<30))
              break;
            else cout<<"Error! Retry: ";

        }while(1);

        cout<<endl<<"Enter year: ";
        do
        {
            while(!(cin>>year))
            {
                 cout<<"Error! Enter a number: ";
                 cin.clear();
                 cin.ignore(1000,'\n');
            }

            if(year>2000 && year<2023)
              break;
            else cout<<"Error! Retry(2000-2023): ";

        }while(1);

       in_file<<"Date: "<<day<<"/"<<month<<"/"<<year<<endl;
       in_file <<"Index\t\tType\t\tNumber-Plate\t\tEntry-Time\t\tExit-Time"<<","<<"\t\tAmount-Paid"<< endl;
       in_file.close();
       cout<<"Done!"<<endl;
       getch();
       staff();
    }
    else
    {
        cout<<"Error: enter name in .txt format."<<endl;
        getch();
        create();
    }

 }

 void edit()
 {
     clear();

     int count=0;

     cout<<"Enter File name:(in .txt form)(Enter 0 to exit) ";
     cin>>name;
     if(name=="0")
        staff();

     for(int i=0; name[i]!='\0';i++)
     {
         if(i>0 && name[i]=='.')
           count++;
     }

     if(count>0 && name[count+1]=='t' && name[count+2]=='x' && name[count+3]=='t' && name[count+4]=='\0')
     {
         initial_vehicle_count();
         //cout<<vehicle_count;
         cout<<"Done!"<<endl;
         getch();
         staff();
     }

    else
    {
        cout<<"Error: enter name in .txt format."<<endl;
        getch();
        edit();
    }

 }

 void set_index(char &ch, int &num)
 {
     string line;
     ifstream in_file(name);
     if(in_file)
    {
        while(getline(in_file,line))

        if(line[1]=='n')
        {
            ch='A';
            num=0;
        }
        else
        {
            ch=line[0];
            num=int(line[1]-'0')*100+int(line[2]-'0')*10+int(line[3]-'0');

            num++;
            if(num>999)
            {
                num=0;
                ch++;
            }
        }
    }
    else
    {
        cout<<"Error! Create file or change destination file."<<endl;
        getch();
        staff();
    }

    in_file.close();


 }

 void write()
 {
    clear();

    if(vehicle_count>= max_park)
    {
        cout<<"Parking full no entry allowed!"<<endl;
        getch();
        staff();
    }

    static char ch;
    static int num;

    set_index(ch,num);
    int in_hour,in_min,option;
    string line,type,plate;

    ifstream in_file(name);
    ofstream temp_file("temp.txt");

    if(in_file && temp_file)
    {
        while(getline(in_file,line))
        {
            temp_file<<line<<endl;
        }

        cout<<"Enter type:(1.car / 2.bike / 0.Exit)"<<endl;
        do
        {
            while(!(cin>>option))
            {
                 cout<<"Error! Enter a number: ";
                 cin.clear();
                 cin.ignore(1000,'\n');
            }

            if(option==1 || option==2)
              break;

            if(option==0)
            {
                in_file.close();
                temp_file.close();
                staff();
            }
            else cout<<"Error! Retry: ";

        }while(1);

        if(option==1)
          type="car";
        else if(option==2)
          type="bike";

        cout<<endl<<"Enter Plate number:(enter 5 characters) ";
        do
        {
            cin>>plate;

            if(plate.size()==5)
              break;
            else cout<<"Error! Retry: ";
        }while(1);

        cout<<endl<<"Enter starting time: "<<endl;

        cout<<"Enter hour:(9-22) ";
        do
        {
            while(!(cin>>in_hour))
            {
                 cout<<"Error! Enter a number: ";
                 cin.clear();
                 cin.ignore(1000,'\n');
            }

            if(in_hour>=9 && in_hour<=22)
              break;
            else cout<<"Error! Retry: ";

        }while(1);

        cout<<endl<<"Enter min:(0-59) ";
        do
        {
            while(!(cin>>in_min))
            {
                 cout<<"Error! Enter a number: ";
                 cin.clear();
                 cin.ignore(1000,'\n');
            }

            if(in_min>=0 && in_min<=59)
              break;
            else cout<<"Error! Retry: ";

        }while(1);

        temp_file<<ch<<setfill('0')<<setw(3)<<num<<"\t\t"<<type<<"\t\t"<<plate<<"\t\t\t"<<setfill('0')<<setw(2)<<in_hour<<":"<<setfill('0')<<setw(2)<<in_min<<"\t\t";

        num++;
        if(num>999)
        {
            ch++;
            num=0;
        }
    }
    else
    {
        cout<<"Error! Create file or change destination file."<<endl;
        getch();
        staff();
    }

    in_file.close();
    temp_file.close();

    remove(name.c_str());
    rename("temp.txt",name.c_str());

    vehicle_count++;

    if(num>0)
        cout<<"Generating token: "<<ch<<setfill('0')<<setw(3)<<num-1<<endl;
    else cout<<"Generating token: "<<ch<<setfill('0')<<setw(3)<<999<<endl;
    cout<<"Done!"<<endl;

    getch();

    staff();
 }

 bool token_check(string token)
 {
     string line;
     ifstream in_file(name);

     if(in_file)
     {
         while(getline(in_file,line))
         {
             if(token[0]==line[0] && token[1]==line[1] && token[2]==line[2] && token[3]==line[3]&& line.size()<30)
             {
                 in_file.close();
                 return true;
             }
        }
    }

    else
    {
        cout<<"Error! Create file or change destination file."<<endl;
        getch();
        staff();
    }

    in_file.close();

    return false;
 }

 void write2()
 {
     clear();

     int ex_hour,ex_min,pay,count=0;
     bool flag;
     string token,line;

     cout<<"Enter token:(Enter 0 to exit) ";
     cin>>token;

     if(token=="0")
        staff();

     flag=token_check(token);

     ifstream in_file(name);
     ofstream temp_file("temp.txt");


     if(in_file && temp_file)
     {
            if(flag==true)
            {
                cout<<"Enter exit time: "<<endl;

                cout<<"Enter hour:(9-23) ";
                do
                {
                   while(!(cin>>ex_hour))
                   {
                      cout<<"Error! Enter a number: ";
                      cin.clear();
                      cin.ignore(100,'\n');
                  }

                  if(ex_hour>=9 && ex_hour<=23)
                     break;
                 else cout<<"Error! Retry: ";

              }while(1);

              cout<<endl<<"Enter min:(0-59) ";
              do
              {
                 while(!(cin>>ex_min))
                 {
                 cout<<"Error! Enter a number: ";
                 cin.clear();
                 cin.ignore(1000,'\n');
                 }

                 if(ex_min>=0 && ex_min<=59)
                    break;
                 else cout<<"Error! Retry: ";

            }while(1);

            while(getline(in_file,line))
            {
                if(token[0]==line[0] && token[1]==line[1] && token[2]==line[2] && token[3]==line[3])
                {
                    pay=payment(line,ex_hour,ex_min);
                    if(pay==-1)
                    {
                        in_file.close();
                        temp_file.close();
                        cout<<"Error! Exit time is smaller than entry time retry.";
                        getch();
                        write2();
                    }
                    temp_file<<line<<"\t"<<setfill('0')<<setw(2)<<ex_hour<<":"<<setfill('0')<<setw(2)<<ex_min<<","<<"\t\t\t"<<pay<<endl;
               }

               else
                   temp_file<<line<<endl;
          }
        }

        else
        {
            cout<<"Error! No such token.";
            in_file.close();
            temp_file.close();
            getch();
            write2();
        }

    }
    else
    {
        cout<<"Error! Create file or change destination file."<<endl;
        getch();
        staff();
    }

    in_file.close();
    temp_file.close();

    remove(name.c_str());
    rename("temp.txt",name.c_str());

    vehicle_count--;
    cout<<"Done!"<<endl;

    getch();

    staff();
 }

 void main_page()
 {
     int option;

     name="/0";

     clear();
     cout<<"Car parking ticketing (Open 9:00 to 23:00)"<<endl;
     cout<<"***********************"<<endl<<endl;
     cout<<"1.Admin"<<endl;
     cout<<"2.Staff"<<endl;
     cout<<"3.Exit"<<endl;
     cout<<endl<<"***********************"<<endl;
     cout<<endl<<"Enter option: ";
     while(!(cin>>option))
     {
         cout<<"Error! Enter a number: ";
         cin.clear();
         cin.ignore(1000,'\n');
     }

     switch(option)
     {
         case 1: main_page();
                 break;
         case 2: staff();
                 break;
         case 3: exit(0);
                 break;
         default: cout<<"Error"<<endl;
                  getch();
                  main_page();
     }
 }

 void staff()
 {
     int option;

     clear();
     cout<<"Staff"<<endl;
     cout<<"***********************"<<endl<<endl;
     cout<<"1.New file"<<endl;
     cout<<"2.Destination file"<<endl;
     cout<<"3.Vehicle entry"<<endl;
     cout<<"4.Vehicle exit"<<endl;
     cout<<"5.Stats"<<endl;
     cout<<"6.Display"<<endl;
     cout<<"7.Exit"<<endl;
     cout<<endl<<"***********************"<<endl;

     cout<<endl<<"Enter option: ";
     while(!(cin>>option))
     {
         cout<<"Error! Enter a number: ";
         cin.clear();
         cin.ignore(1000,'\n');
     }

     switch(option)
     {
         case 1: create();
                 break;
         case 2: edit();
                 break;
         case 3: write();
                 break;
         case 4: write2();
                 break;
         case 5: stats();
                 break;
         case 6: display();
                 break;
         case 7: main_page();
                 break;
         default: cout<<"Error"<<endl;
                  getch();
                  staff();
     }
 }

 void stats()
 {
     clear();

     int count1=0,count2=0,add=0;
     string line,str,word;
     ifstream in_file(name);
     if(in_file)
    {
        while(getline(in_file,line))
        {
            if(line[6]=='c')
                count1++;
            else if(line[6]=='b')
                count2++;
            stringstream str(line);

            while(getline(str,word,','))
            {

                 if(word.size()<=10)
                 {

                    add=add+stoi(word);
                 }
            }
        }
    }
    else
    {
        cout<<"Error! Create file or change destination file."<<endl;
        getch();
        staff();
    }

    in_file.close();

    cout<<"Total cars: "<<count1<<endl;
    cout<<"Total bikes: "<<count2<<endl;
    cout<<"Total amount received: Rs."<<add<<endl;
    getch();

    staff();
 }

 void display()
 {
     clear();

     string line;
     ifstream in_file(name);
     if(in_file)
    {
        while(getline(in_file,line))
        {
            cout<<line<<endl;
        }
    }
    else
    {
        cout<<"Error! Create file or change destination file."<<endl;
        getch();
        staff();
    }

    in_file.close();

    cout<<"************************************************************************************************************************"<<endl;
    cout<<"Done!"<<endl;

    getch();

    staff();
}

void initial_vehicle_count()
{
     string line;
     ifstream in_file(name);
     if(in_file)
    {
        while(getline(in_file,line))
        {
            if(line.size()<30 && line[0]!='D')
                vehicle_count++;
        }
    }
    else
    {
        cout<<"Error! Create file or change destination file."<<endl;
        getch();
        staff();
    }

    in_file.close();
}

int main()
{
    main_page();
    return 0;
}
