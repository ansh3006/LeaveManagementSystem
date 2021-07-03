#include <iostream>
#include <string>
#include <fstream>
using namespace std;

ofstream file;
ofstream userdata;

class Person{
    public:
    string name, age;
};

class Employee : public Person{
    public:
    static int count;
    int CL, SL, CCL, PL;
    string sal, id;
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
    void update_data();
};

int Employee :: count=0;

int Employee::get_details(){
    string n;
    cout<<"Enter User ID: ";
    cin.ignore();
    getline(cin,n);
    ifstream in("User_details.txt");
    for(int i=0;i<count;i++){
        string idd,Name,Age,Sal,cl,sl,ccl,pl;
        in>>idd>>Name>>Age>>Sal>>cl>>sl>>ccl>>pl;
        if(idd==n){
            id=idd;
            name=Name;
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
    count+=1;
    cout<<"----------------------New User---------------------"<<endl;
    userdata.open("User_details.txt",ios::app | ios::in | ios::out);
    cout<<"Enter ID (Must be of 4 digits): "; cin>>id;
    cout<<"Enter Name: "; cin.ignore(); getline(cin,name);  
    cout<<"Enter Age: "; cin>>age;
    cout<<"Enter Salary(In Rupees): "; cin>>sal;  
    cout<<endl<<"User added successfully!"<<endl;
    userdata<<id<<" "<<name<<" "<<age<<" "<<sal<<" "<<CL<<" "<<SL<<" "<<CCL<<" "<<PL<<endl;
    userdata.close();
}

void Employee::user_details(){
    cout<<"----------------------User Details---------------------"<<endl<<endl;
    cout<<"ID: "<<id<<endl;
    cout<<"Name: "<<name<<endl;
    cout<<"Age: "<<age<<endl;
    cout<<"Salary: "<<sal<<endl;
}

void Employee::apply_leave(){
    file.open("Leave_details.txt",ios::app | ios::in | ios::out);
B:  cout<<"---------------------Apply For Leave----------------------"<<endl;
    cout<<endl<<"1. Casual Leave (Remaining :"<<CL<<")"<<endl;
    cout<<"2. Sick Leave (Remaining :"<<SL<<")"<<endl;
    cout<<"3. Childcare Leave (Remaining :"<<CCL<<")"<<endl;
    cout<<"4. Parental Leave (Remaining :"<<PL<<")"<<endl;
    cout<<"Choose One Option to proceed...";
    int choice,days;
    string sdate,edate;
    cin>>choice;
    cout<<"Enter number of days: ";
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
        default:cout<<"Choose from the given choices...";
                goto B;
    }
    file.close();
}

void Employee::search_leave(){
    cout<<"----------------------Search For Leave-----------------"<<endl;
    ifstream in("Leave_details.txt",ios::in | ios::out | ios::app);
    cout<<endl<<"ID Days  StartDate   EndDate   Type"<<endl;
    for(int i=0;i<count;i++){
        string ID,DAYS,SDATE,EDATE,TYPE;
        in>>ID>>DAYS>>SDATE>>EDATE>>TYPE;
        if(ID==id)
            cout<<ID<<"   "<<DAYS<<"   "<<SDATE<<"  "<<EDATE<<"  "<<TYPE<<"\n";
    }
}

void Employee::delete_leave(){
    fstream in("Leave_details.txt", ios::in | ios::out | ios::app);
    fstream out("new2.txt", ios::in | ios::out | ios::app);
    string s;
    while(getline(in,s)){
        string str=s.substr(0,4);
        if(str!=id){
            out<<s<<endl;
        }
    }
    in.close();
    out.close();
    remove("Leave_details.txt");
    rename("new2.txt", "Leave_details.txt");
};

void Employee::display_leave(){
    cout<<"------------Remaining Leaves------------"<<endl<<endl;
    cout<<"Employee ID: "<<id<<endl;
    cout<<"Name: "<<name<<endl;
    cout<<"CL: "<<CL<<endl;
    cout<<"SL: "<<SL<<endl;
    cout<<"CCL: "<<CCL<<endl;
    cout<<"PL: "<<PL<<endl<<endl;
    cout<<"CL: Casual Leave ; SL: Sick Leave ; CCL: Childcare Leave ; PL: Parental Leave"<<endl;
}

void Employee::update_data(){
    fstream in("User_details.txt", ios::in | ios::out | ios::app);
    fstream out("new.txt", ios::in | ios::out | ios::app);
    string s;
    while(getline(in,s)){
        string str=s.substr(0,4);
        if(str!=id){
            out<<s<<endl;
        }
    }
    out<<id<<" "<<name<<" "<<age<<" "<<sal<<" "<<CL<<" "<<SL<<" "<<CCL<<" "<<PL<<endl;
    in.close();
    out.close();
    remove("User_details.txt");
    rename("new.txt", "User_details.txt");
};

int main(){
    int out=0;
    while(out!=1){
        int choice,check=0;
        cout<<endl<<endl<<"-----------------------LEAVE MANAGEMENT SYSTEM----------------------"<<endl<<endl;
        cout<<"1. Add User"<<endl<<"2. All Users"<<endl<<"3. Apply Leave"<<endl<<"4. Search Leave"<<endl<<"5. Delete Leave"<<endl<<"6. Display Leave"<<endl;
        cout<<"Choose the option: "<<endl;
        cin>>choice;
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
                        e.update_data();
                        break;
                case 4: e.search_leave();
                        break;
                case 5: e.delete_leave();
                        e.update_data();
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
    }

    return 0;
}