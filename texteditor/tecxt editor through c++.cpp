#include <bits/stdc++.h>
#include <fstream>
using namespace std;
class Text{
    private:
    struct Node{
        string data;
        Node *next=NULL;
    };
    Node *head=NULL;
    Node *tail=NULL;
    stack<Node *> undoStack;
    stack<Node *> redoStack;
    ofstream fout;
    public:
    void settail(){
        Node *temp=head;
        while(temp!=NULL){
            tail=temp;
            temp=temp->next;
        }
    }
    Node * copydata(){
        Node *head1=NULL;
        Node *tail1=NULL;
        Node *temp=head;
        while(temp!=NULL){
            if(head1==NULL){
                head1=new Node();
                head1->data=temp->data;
                tail1=head1;
            }
            else{
                tail1->next=new Node();
                tail1=tail1->next;
                tail1->data=temp->data;
            }
            temp=temp->next;
        }
        return head1;
    }
    void createNode(string str){
        if(head==NULL || tail==NULL){
            head=new Node();
            head->data=str;
            tail=head;
        }
        else{
            Node *temp=new Node();
            temp->data=str;
            tail->next=temp;
            tail=temp;
        }
    }
    void CreateStorage(){
        system("cls");
        cout<<"Enter File name : "<<endl;
        string fname;
        cin>>fname;
        head=NULL;
        tail=NULL;
        fname=fname+".txt";
        fout.open(fname);
        cout<<"-----------Storage created successfully---------- \n"<<endl;
    }
    void insertData() {
        system("cls");
        undoStack.push(copydata());
        cout << "Enter the line or word data to be inserted: \n";
        string newdata;
        cin.ignore();
        getline(cin, newdata);
        string word="";
        for(int ch=0;ch<=newdata.length();ch++){
            if(newdata[ch]==' ' || newdata[ch]=='\0'){
                createNode(word);
                word="";
            }
            else{
                word=word+newdata[ch];
            }
        }
        system("cls");
        cout<<"\-----------inserted Successfully--------------\n";
    }

    void updateData() {
        system("cls");
        undoStack.push(copydata());
        string searchword,updateword;
        cout << "Enter word you want to update: ";
        cin>>searchword;
        int flag=0,i=0;
        Node *temp=head;
        while(temp!=NULL){
            if(temp->data==searchword){
                system("cls");
                displayData();
                flag=1;
                cout<<"***************************************************\n";
                cout<<"Update data "<<searchword<<" present at index "<<i<<endl;
                char ch;
                cout<<"\n Press 'y' for update this index word \n Press 'n' for checking next index word"<<endl;
                cout<<"\n***************************************************\n";
                cin>>ch;
                if(ch=='y' || ch=='Y'){
                    cout << "Enter new word: ";
                    cin>>updateword;
                    temp->data=updateword;
                    cout<<"------------Updated Successfully------------"<<endl;
                    break;
                }
            }
            i++;
            temp=temp->next;
        }
        if(flag==0){
            cout<<"Given word not match"<<endl;
        }
    }

    void appendData() {
        system("cls");
        undoStack.push(copydata());
        cout << "Enter the data to be appended: \n";
        string input;
        cin.ignore();
        getline(cin, input);
        string word="";
        for(int ch=0;ch<=input.length();ch++){
            if(input[ch]==' ' || input[ch]=='\0'){
                createNode(word);
                word="";
            }
            else{
                word=word+input[ch];
            }
        }
        cout<<"***************************************************\n";
        displayData();
        cout<<"\n --------------Append Successfully----------\n";

    }

    void searchData() {
        system("cls");
        cout << "Enter the data to be searched: ";
        string input;
        cin>>input;
        int index = 0,resIndex=-1 ,flag=0;
        Node *temp=head;
        while(temp!=NULL){
            if (temp->data == input) {
                char ch;
                system("cls");
                displayData();
                flag=1;
                resIndex=index;
                cout<<"***************************************************\n";
                cout << "Data found at index " << index << endl;
                cout<<"\n Press 'y' for next word \n Press 'n' for stop"<<endl;
                cout<<"\n***************************************************\n";
                cin>>ch;
                if(ch=='y' || ch=='Y'){
                    index++;
                    temp=temp->next;
                    continue;
                }
                else{
                    break;
                }

            }
            index++;
            temp=temp->next;
        }
        if (flag) {
            cout<<"***************************************************\n";
            cout << "Data found at index " << resIndex << endl;
        } else {
            cout<<"***************************************************\n";
            cout << "Data not found" << endl;
        }
    }

    void deleteData() {
        system("cls");
        displayData();
        undoStack.push(copydata());
        cout << "Enter the word you want deleted: ";
        string word;
        cin >> word;
        int index=0,flag=0;
        Node *temp=head;
        Node *prev=NULL;
        while(temp!=NULL) {
            if(temp->data==word){
                system("cls");
                displayData();
                flag=1;
                cout << "Data found at index " << index << endl;
                cout<<"\n Press 'y' for next word \n Press 'n' for stop"<<endl;
                char ch;
                cin>>ch;
                if(ch=='y' || ch=='Y'){
                    if(temp==head && temp==tail){
                        head=NULL;
                        tail=NULL;
                    }
                    else if(temp==head){
                        head=temp->next;
                    }
                    else if(temp==tail){
                        prev->next=NULL;
                    }
                    else{
                        prev->next=temp->next;
                    }
                    cout<<"***************************************************\n";
                    displayData();
                    cout<<"\n***************************************************\n";
                    cout<<"----------------Deleted successfully----------------\n";
                    break;
                }
        }
        index++;
        prev=temp;
        temp=temp->next;
        }
        if(flag){
            cout<<"--------------Data not found--------------"<<endl;
        }
    }

    void displayData() {
        system("cls");
        if(head==NULL){
            cout<<"***************************************************\n";
            cout<<"Data Not Present"<<endl;
        }
        else{
            cout<<"***************************************************\n";
            Node *temp=head;
            while(temp!=NULL){
                cout<<temp->data<<" ";
                temp=temp->next;
            }
            cout<<endl;
        }
    }

    void undo() {
        if (!undoStack.empty()) {
            redoStack.push(copydata());
            head=undoStack.top();
            undoStack.pop();
            settail();
            cout<<"***************************************************\n";
            displayData();
            cout<<"\n***************************************************\n";
            cout<<"----------------Undo successfully----------------\n";
        } else {
            cout<<"***************************************************\n";
            cout << "Nothing to undo" << endl;
        }
    }

    void redo() {
        if (!redoStack.empty()) {
            undoStack.push(copydata());
            head = redoStack.top();
            redoStack.pop();
            settail();
            cout<<"***************************************************\n";
            displayData();
            cout<<"\n***************************************************\n";
            cout<<"----------------Redo successfully----------------\n";
        } else {
            cout<<"***************************************************\n";
            cout << "-------Nothing to redo------" << endl;
        }
    }

    void saveData(){
        string str="";
        Node *temp=head;
        while(temp!=NULL){
            str+=temp->data+" ";
            temp=temp->next;
        }
        fout<<str;
        fout.close();
        cout<<"----------------Store permanent successfully-----------"<<endl;
        exit(0);
    }
};

int main()
{
    Text text;
    while(true){
        cout<<"\nSelect Choice:-\n";
        cout<<"***************************************************\n";
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
        cout<<"***************************************************\n";
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

