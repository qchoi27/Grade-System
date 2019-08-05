#include<iostream>

using namespace std;

#include<stdlib.h>
#include<stdio.h>
#include<fstream>
#include<iomanip>


//class to acquire and output grades
class student
{
    int studentid,s_score=0,h_score=0,m_score=0,e_score=0,mu_score=0,temp;
    
    char grades[5];
    string name;
    void calculate()
    {
        int scores[5]={s_score,h_score,m_score,e_score,mu_score};
        for (int i=0; i<5; ++i)
        {
            temp=scores[i];
            if(temp>=90)
                grades[i]='A';
            else if(temp>=80)
                grades[i]='B';
            else if(temp>=70)
                grades[i]='C';
            else if(temp>=60)
                grades[i]='D';
            else
                grades[i]='F';
        }
    }
public:
    void getGrades()
    {
        cout<<"\nEnter student ID: ";
        cin>>studentid;
        cout<<"\nEnter name of student: ";
        cin>>name;
        cout<<"\nEnter score in science out of 100: ";
        cin>>s_score;
        cout<<"\nEnter score in history out of 100: ";
        cin>>h_score;
        cout<<"\nEnter score in math out of 100: ";
        cin>>m_score;
        cout<<"\nEnter score in english out of 100: ";
        cin>>e_score;
        cout<<"\nEnter score in music out of 100: ";
        cin>>mu_score;
        calculate();
    }
    
    void showGrades()
    {
        cout<<"\nStudent ID: "<<studentid;
        cout<<"\nStudent name: "<<name;
        cout<<"\nScience grade: "<<s_score<<"%";
        cout<<"\nHistory grade: "<<h_score<<"%";
        cout<<"\nMath grade: "<<m_score<<"%";
        cout<<"\nEnglish grade: "<<e_score<<"%";
        cout<<"\nMusic grade:"<<mu_score<<"%";
    }
    
    void showTable()
    {
        cout<<studentid<<setw(12)<<name<<setw(13)<<grades[0]<<setw(9)<<grades[1]<<setw(9)<<grades[2]<<setw(9)<<grades[3]<<setw(9)<<grades[4]<<setw(3)<<setprecision(3)<<endl;
    }
    int retStudentid()
    {
        return studentid;
    }
};


fstream file;
student st;

// function to show all records
void showRec()
{
    file.open("student.dat",ios::in);
    while(file.read((char*)&st,sizeof(student)))
    {
        st.showGrades();
        cout<<"\n\n======================================\n";
    }
    file.close();
    cin.get();
}

//function to show specific record from file
void showsp(int n)
{
    int x=0;
    file.open("student.dat",ios::in);
    while(file.read((char*)&st,sizeof(student)))
    {
        if(st.retStudentid()==n)
        {
            x=1;
            st.showGrades();
        }
    }
    file.close();
    if(x==0)
        cout<<"\n\nRecord does not exist";
    cin.get();
}

//function to create new record
void newRec()
{
    file.open("student.dat",ios::out|ios::app);
    st.getGrades();
    file.write((char*)&st,sizeof(student));
    file.close();
    cout<<"\n\nStudent record has been created ";
    cin.get();
}

//function to delete student
void deleteRec()
{
    
    int id;
    fstream file2;
    cout<<"\n\n\nDELETE STUDENT";
    cout<<"\n\nEnter student ID: ";
    cin>>id;
    file.open("student.dat",ios::in|ios::out);
    file2.open("del.dat",ios::out);
    file.seekg(0,ios::beg);
    while(file.read((char*)&st,sizeof(student)))
    {
        if(st.retStudentid()!=id)
        {
            file2.write((char*)&st,sizeof(student));
        }
    }
    file2.close();
    file.close();
    remove("student.dat");
    rename("del.dat","student.dat");
    cout<<"\n\nStudent deleted";
    cin.get();
}

//function to show all students' grades report
void showAll()
{
    
    file.open("student.dat",ios::in);
    if(!file)
    {
        cout<<"ERROR!!! FILE COULD NOT BE OPENED";
        cout<<"\n\n\n Program is closing...";
        cin.get();
        exit(0);
    }
    cout<<"\n\nCLASS RESULTS \n\n";
    cout<<"-------------------------------------------------------------------\n";
    cout<<"ID          Name         Science  History   Math    English   Music\n";
    cout<<"-------------------------------------------------------------------\n";
    while(file.read((char*)&st,sizeof(student)))
    {
        st.showTable();
    }
    file.close();
    cin.get();
}

//function to display results menu
void results()
{
    int x,id;
    char ch;
    
    cout<<"\n\n\nRESULTS MENU";
    cout<<"\n\n\n1. Class Results\n\n2. Student Report Card\n\n3. Back to Main Menu";
    cout<<"\n\n\nEnter choice (1-3): ";
    cin>>x;
    switch(x)
    {
        case 1 :
            showAll();
            break;
        case 2 :
        {
            do
            {
                cout<<"\n\nEnter student ID: ";
                cin>>id;
                showsp(id);
                cout<<"\n\nDo you want to see more results (y/n)?";
                cin>>ch;
            } while(ch=='Y'||ch=='y');
            break;
        }
        case 3:
            break;
        default:
            cout<<"\a";
    }
}

//entry & edit menu function
void entryMenu()
{
    
    int id;
    char ch;
    cout<<"\n\n\nENTRY MENU";
    cout<<"\n\n1.ALL STUDENTS' RECORDS";
    cout<<"\n\n2.SEARCH STUDENT";
    cout<<"\n\n3.CREATE STUDENT";
    cout<<"\n\n4.DELETE STUDENT";
    cout<<"\n\n5.BACK TO MAIN MENU";
    cout<<"\n\nEnter choice (1-5): ";
    cin>>ch;
    switch(ch)
    {
        case '1':
            showRec();
            break;
        case '2':
            cout<<"\n\n\tEnter student ID: ";
            cin>>id;
            showsp(id);
            break;
        case '3':
            newRec();
            break;
        case '4':
            deleteRec();
            break;
        case '5':
            break;
        default:
            cout<<"\a";
            entryMenu();
    }
}

//main function
int main()
{
    char ch;
    cout<<"STUDENT REPORT CARD";
    do
    {
        cout<<"\n\n\nMAIN MENU";
        cout<<"\n\n01. RESULTS MENU";
        cout<<"\n\n02. ENTRY/EDIT MENU";
        cout<<"\n\n03. EXIT";
        cout<<"\n\nEnter choice (1-3): ";
        cin>>ch;
        switch(ch)
        {
            case '1':
                results();
                break;
            case '2':
                entryMenu();
                break;
            case '3':
                exit(0);
            default :
                cout<<"\a";
        }
    } while(ch!='3');
    return 0;
}
