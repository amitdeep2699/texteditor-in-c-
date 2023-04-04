#include <bits/stdc++.h>
#include <fstream>
using namespace std;
class Text{
    private:
    vector<string> data;
    stack<vector<string>> undoStack;
    stack<vector<string>> redoStack;
    public:
    void CreateStorage(){
        data.clear();
        system("cls");
        cout<<"------Storage created Successfully----- \n"<<endl;
    }
    void insertData() {
        system("cls");
        cout << "Enter the line or word data to be inserted: \n";
        cout << "*********************************************\n";
        string newdata;
        cin.ignore();
        getline(cin, newdata);
        string word="";
        for(auto ch: newdata){
            if(ch==' '){
                data.push_back(word);
                word="";
            }
            else{
                word=word+ch;
            }
        }
        data.push_back(word);
        undoStack.push(data);
    }

    void updateData() {
        system("cls");
        displayData();
        undoStack.push(data);
        string searchword,updateword;
        cout << "Enter word you want to update: ";
        cin>>searchword;
        int flag=0;
        for(int i=0;i<=data.size();i++){
            if(data[i]==searchword){
                system("cls");
                flag=1;
                cout << "*********************************************\n";
                cout<<"Update data "<<searchword<<" present at index "<<i<<endl;
                char ch;
                cout<<"\n Press 'y' for update this index word \n Press 'n' for checking next index word"<<endl;
                cout << "*********************************************\n";
                cin>>ch;
                if(ch=='y' || ch=='Y'){
                    cout << "Enter new word: ";
                    cin>>updateword;
                    data[i]=updateword;
                    displayData();
                    cout<<"---Updated Successfully--"<<endl;
                    break;
                }
                else{
                    continue;
                }
            }
        }
        if(flag==0){
            cout << "*********************************************\n";
            cout<<"Given word not match"<<endl;
        }
    }

    void appendData() {
        system("cls");
        undoStack.push(data);
        cout << "Enter the data to be appended: \n";
        cout << "*********************************************\n";
        string input;
        cin.ignore();
        getline(cin, input);
        string word="";
        for(auto x:input){
            if(x==' '){
                data.push_back(word);
                word="";
            }
            else{
                word=word+x;
            }
        }
        data.push_back(word);
        displayData();
        cout<<"*******Append Successfully****\n"<<endl;
        cout << "*********************************************\n";
    }

    void searchData() {
        system("cls");
        cout << "Enter the data to be searched: ";
        cout << "*********************************************\n";
        string input;
        cin>>input;
        int index = -1;
        for (int i = 0; i < data.size(); i++) {
            if (data[i] == input) {
                index = i;
                char ch;
                system("cls");
                cout << "*********************************************\n";
                cout << "Data found at index " << index << endl;
                cout<<"\n Press 'y' for next word \n Press 'n' for stop"<<endl;
                cout << "*********************************************\n";
                cin>>ch;
                if(ch=='y' || ch=='Y'){
                    continue;
                }
                else{
                    break;
                }

            }
        }
        if (index != -1) {
            cout << "Last Data found at index " << index << endl;
        } else {
            cout << "Data not found" << endl;
        }
    }

    void deleteData() {
        system("cls");
        displayData();
        cout << "Enter the index of the data to be deleted: ";
        cout << "*********************************************\n";
        string deletword;
        cin >> deletword;
        int index=0,flag=0;
        for(auto x:data){
            if(x==deletword){
                flag=1;
                cout<<"\n Press 'y' for delete data present at index "<< index<<"\n Press 'n' for stop"<<endl;
                cout << "*********************************************\n";
                char ch;
                cin>>ch;
                if(ch=='y' || ch=='Y'){
                    undoStack.push(data);
                    data.erase(data.begin() + index+1);
                    cout << "********Deleted Successfully********" << endl;
                    break;
                }
                else{
                    continue;
                }

            }
            index++;
        }
        if(flag==0){
            cout << "Word " <<deletword<<" not present"<< endl;
        }
    }

    void displayData() {
        system("cls");
        if(data.empty()){
            cout<<"Data Not Present"<<endl;
        }
        else{
            cout << "*********************************************\n";
            cout << "Data:" << endl;
            for(auto x:data){
                cout<<x<<" ";
            }
            cout<<endl;
        }
        cout << "\n*********************************************\n";
    }

    void undo() {
        system("cls");
        displayData();
        if (!undoStack.empty()) {
            redoStack.push(data);
            data = undoStack.top();
            undoStack.pop();
            displayData();
            cout<<"*****Undo Successfully****"<<endl;
        } else {
            cout << "Nothing to undo" << endl;
        }
    }

    void redo() {
        system("cls");
        displayData();
        if (!redoStack.empty()) {
            undoStack.push(data);
            data = redoStack.top();
            redoStack.pop();
            displayData();
            cout<<"*****Redo Successfully****"<<endl;
        } else {
            cout << "Nothing to redo" << endl;
        }
    }

    void saveData() {
        ofstream file("data.txt");
}
};

int main()
{
    Text text;
    while(true){
        cout <<"******************************************************\n";
        cout<<"Select Choice:-\n\n";
        cout<<"1-> Create Storage for your data"<<endl;
        cout<<"2-> Insert"<<endl;
        cout<<"3-> Update"<<endl;
        cout<<"4-> Append Data"<<endl;
        cout<<"5-> Search Data"<<endl;
        cout<<"6-> Delete Data"<<endl;
        cout<<"7-> Display Data"<<endl;
        cout<<"8-> Undo Data"<<endl;
        cout<<"9-> Redo Data"<<endl;
        cout<<"10-> Save data in permanent storage"<<endl;
        cout << "******************************************************\n";
        int choice;
        cin>>choice;
        switch(choice){
            case 1:{
                text.CreateStorage();
                break;}
            case 2:{
                text.insertData();
                break;}
            case 3:{
                text.updateData();
                break;}
            case 4:{
                text.appendData();
                break;}
            case 5:{
                text.searchData();
                break;}
            case 6:{
                text.deleteData();
                break;}
            case 7:{
                text.displayData();
                break;}
            case 8:{
                text.undo();
                break;}
            case 9:{
                text.redo();
                break;}
            case 10:{
                text.saveData();
                break;}
            default:{
                cout<<"Invalid input\n please choose correct input:- "<<endl;
                break;}
        }
    }
    return 0;
}
