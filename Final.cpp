#include <iostream>
#include <string>
#include <fstream>
using namespace std;

ofstream file;
ofstream userdata;

class Person{
    public:
    string fname,lname, age;
};

class Employee : public Person{
    int CL, SL, CCL, PL;
    string sal, id;
    public:
    Employee(){
        CL=20, SL=15, CCL=20, PL=30;
    }
    int  get_details();
    void add_user();
    void user_details();
    void apply_leave();
    void search_leave();
    void delete_leave();
    void display_leave();
};

int Employee::get_details(){
    string n;
    cout<<"Enter User ID: ";
    cin.ignore();
    getline(cin,n);
    cout<<endl;
    fstream in("User_details.txt", ios::app | ios::in | ios::out);
    while(!in.eof()){
        string idd,fName,lName,Age,Sal,cl,sl,ccl,pl;
        in>>idd>>fName>>lName>>Age>>Sal>>cl>>sl>>ccl>>pl;
        if(idd==n){
            id=idd;
            fname=fName;
            lname=lName;
            age=Age;
            sal=Sal;
            CL=stoi(cl);
            SL=stoi(sl);
            CCL=stoi(ccl);
            PL=stoi(pl);
            return 1;
        }
    }
    return 0;
}

void Employee::add_user(){
    cout<<"\t\t\t\t\t\tNew User"<<endl<<endl;
    userdata.open("User_details.txt",ios::app | ios::in | ios::out);
    cout<<"Enter ID (Must be of 4 digits): "; cin>>id;
    cout<<"Enter Name: "; cin>>fname; cin>>lname;  
    cout<<"Enter Age: "; cin>>age;
    cout<<"Enter Salary(In Rupees): "; cin>>sal;  
    cout<<endl<<"User added successfully!"<<endl;
    userdata<<id<<" "<<fname<<" "<<lname<<" "<<age<<" "<<sal<<" "<<CL<<" "<<SL<<" "<<CCL<<" "<<PL<<endl;
    userdata.close();
    system("pause");
}

void Employee::user_details(){
    cout<<"\t\t\t\t\t\tUser Details"<<endl<<endl;
    cout<<"ID: "<<id<<endl;
    cout<<"Name: "<<fname<<" "<<lname<<endl;
    cout<<"Age: "<<age<<endl;
    cout<<"Salary: "<<sal<<endl<<endl;
    system("pause");
}

void Employee::apply_leave(){
    file.open("Leave_details.txt",ios::app | ios::in | ios::out);
B:  cout<<"\t\t\t\t\t\tApply For Leave"<<endl<<endl;
    cout<<"1. Casual Leave (Remaining :"<<CL<<")"<<endl;
    cout<<"2. Sick Leave (Remaining :"<<SL<<")"<<endl;
    cout<<"3. Childcare Leave (Remaining :"<<CCL<<")"<<endl;
    cout<<"4. Parental Leave (Remaining :"<<PL<<")"<<endl<<endl;
    cout<<"Choose One Option to proceed : ";
    int choice,days;
    string sdate,edate;
    cin>>choice;
    cout<<endl<<"Enter number of days: ";
    cin>>days;
    cout<<"Enter Start date: ";
    cin.ignore();
    getline(cin,sdate);
    cout<<"Enter End date: ";
    getline(cin,edate);
    if(choice==1 || choice==2 || choice==3 || choice==4)
        file<<id<<" "<<days<<" "<<sdate<<" "<<edate<<" ";
    switch(choice){
        case 1: CL-=days;
                file<<"CL"<<endl;
                cout<<"Remaining CL: "<<CL<<endl;
                break;
        case 2: SL-=days;
                file<<"SL"<<endl;
                cout<<"Remaining SL: "<<SL<<endl;
                break;
        case 3: CCL-=days;
                file<<"CCL"<<endl;
                cout<<"Remaining CCL: "<<CCL<<endl;
                break;
        case 4: PL-=days;
                file<<"PL"<<endl;
                cout<<"Remaining PL: "<<PL<<endl;
                break;
        default:cout<<"Choose from the given choices..."<<endl;
                system("pause");
                goto B;
    }
    file.close();
    
    fstream in("User_details.txt", ios::in | ios::out | ios::app);
    fstream out("new.txt", ios::in | ios::out | ios::app);
    string s;
    while(getline(in,s)){
        string str=s.substr(0,4);
        if(str!=id){
            out<<s<<endl;
        }
    }
    out<<id<<" "<<fname<<" "<<lname<<" "<<age<<" "<<sal<<" "<<CL<<" "<<SL<<" "<<CCL<<" "<<PL<<endl;
    in.close();
    out.close();
    remove("User_details.txt");
    rename("new.txt", "User_details.txt");

    cout<<endl;
    system("pause");
}

void Employee::search_leave(){
    cout<<"\t\t\t\t\t\tSearch For Leave"<<endl<<endl;
    fstream in("Leave_details.txt",ios::in | ios::out | ios::app);
    cout<<" ID   Days  StartDate   EndDate   Type"<<endl;
    while(!in.eof()){
        string ID,DAYS,SDATE,EDATE,TYPE;
        in>>ID>>DAYS>>SDATE>>EDATE>>TYPE;
        if(ID==id)
            cout<<ID<<"   "<<DAYS<<"   "<<SDATE<<"  "<<EDATE<<"   "<<TYPE<<"\n";
    }
    cout<<endl;
    system("pause");
}

void Employee::delete_leave(){
    fstream in("Leave_details.txt", ios::in | ios::out | ios::app);
    fstream out("new2.txt", ios::in | ios::out | ios::app);
    string s;
    cout<<"\t\t\t\t\t\tDeleted Leaves"<<endl<<endl;
    cout<<" ID Days StartDate EndDate  Type"<<endl;
    while(getline(in,s)){
        string str=s.substr(0,4);
        if(str!=id){
            out<<s<<endl;
        }else{
            cout<<s<<endl;
        }
    }
    in.close();
    out.close();
    remove("Leave_details.txt");
    rename("new2.txt", "Leave_details.txt");
    
    fstream input("User_details.txt", ios::in | ios::out | ios::app);
    fstream output("new3.txt", ios::in | ios::out | ios::app);
    while(getline(in,s)){
        string str=s.substr(0,4);
        if(str!=id){
            output<<s<<endl;
        }
    }
    output<<id<<" "<<fname<<" "<<lname<<" "<<age<<" "<<sal<<" "<<"20 15 20 30"<<endl;
    input.close();
    output.close();
    remove("User_details.txt");
    rename("new3.txt", "User_details.txt");
    system("pause");
};

void Employee::display_leave(){
    cout<<"\t\t\t\t\t\tRemaining Leaves"<<endl<<endl;
    cout<<"Employee ID: "<<id<<endl;
    cout<<"Name: "<<fname<<" "<<lname<<endl;
    cout<<"CL: "<<CL<<endl;
    cout<<"SL: "<<SL<<endl;
    cout<<"CCL: "<<CCL<<endl;
    cout<<"PL: "<<PL<<endl<<endl;
    cout<<"CL: Casual Leave ; SL: Sick Leave ; CCL: Childcare Leave ; PL: Parental Leave"<<endl;
    system("pause");
}

int main(){
    int out=0;
    while(out!=1){
        int choice,check=0;
        cout<<endl<<endl<<"\t\t\t\t\t\tLEAVE MANAGEMENT SYSTEM"<<endl<<endl;
        cout<<"1. Add User"<<endl<<"2. User Details"<<endl<<"3. Apply Leave"<<endl<<"4. Search Leave"<<endl<<"5. Delete Leave"<<endl<<"6. Display Leave"<<endl;
        cout<<"Choose the option: "<<endl;
        cin>>choice;
        system("cls");
        Employee e;
        if(choice!=1){
            check = e.get_details();
        }else{
            check=1;
        }
        if(check==1){
            switch(choice){
                case 1: e.add_user();
                        break;
                case 2: e.user_details();
                        break;
                case 3: e.apply_leave();
                        break;
                case 4: e.search_leave();
                        break;
                case 5: e.delete_leave();
                        break;
                case 6: e.display_leave();
                        break;
                default:cout<<"You Entered wrong choice."<<endl;
            }
        }else{
            cout<<"You Entered wrong User ID..."<<endl;
        }
        cout<<endl<<"Do you wanna continue (0->YES)(1->NO) : "<<endl;
        cin>>out;
        system("cls");
    }

    return 0;
}
