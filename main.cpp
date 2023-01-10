#include<iostream>
#include "user.cpp"
#include <ctime>
#include <iomanip>
using namespace std;

//Declarations
void enter(account& u, account user[], int size);
void showBalance(account& u, account user[], int size);
void deposit(account& u, account user[], int size);
void withdraw(account& u, account user[], int size);
void showAllTransactions(account& u, account user[], int size);
void mainWindowLogin(account u[],int size);
//---------------------------------MAIN OPTION WINDOW-----------------------------------
void mainOption(account& u, account user[], int size){
    cout<<"\nMain Window:\n============="<<endl;
    cout<<"Choose one of the following options: "<<endl;
    cout<<"(1) Show balance\n(2) Deposit\n(3) Withdraw"<<
    "\n(4) Show All Transactions\n(5) Sign out of account\nEnter your choice: ";
    string choice;
    cin>>choice;
    if(choice.compare("1")==0)
        showBalance(u, user, size);
    else if(choice.compare("2")==0)
        deposit(u,user, size);
    else if(choice.compare("3")==0)
        withdraw(u,user, size);
    else if(choice.compare("4")==0)
        showAllTransactions(u,user, size);
    //Create another option so that user can go back to main login
    else if(choice.compare("5")==0)
        mainWindowLogin(user,size);
    else{
        cout<<"\nINVALID ENTRY\n";
        mainOption(u,user,size);
    }
}
//-------------------------------MAIN WINDOW TO LOG IN----------------------------------
void mainWindowLogin(account u[],int size){
    int reenter=true;
    cout<<"\nMain Window:\n============="<<endl;
    while(reenter){
    string accno;
    string pass;
    cout<<"Enter Your Account no: "<<endl;
    cin>>accno;
    cout<<"Enter your password: "<<endl;
    cin>>pass;
    int foundAccount=0;//Check if account number exists
    int passMatch=0;//Check if correct password
    for(int i=0; i<size;i++){
        //If the account number is found
        if(u[i].getAccNo().compare(accno)==0){
            foundAccount=1;
            //If the password matches
            if(u[i].getPassword().compare(pass)==0){
                passMatch=1;
                reenter=false;
                mainOption(u[i],u, size);  
            }
            //Prompt user to try login again
            else{
            cout<<"Incorrect Password"<<endl;
            cout<<"Try again\n"<<endl;
            break;
            }
        }
        
    }
    if(foundAccount==0&&passMatch==0){
        cout<<"Account number not found\nTry again\n\n";
    }
}
}
//------------------------------ENTER TO GO BACK TO MAIN WINDOW-------------------------
void enter(account& u, account user[], int size){
    cin.ignore();
    if(cin.get() =='\n'){
        mainOption(u, user, size);
    }
}
//------------------------------------SHOW BALANCE--------------------------------------
void showBalance(account& u, account user[], int size){
   cout<<"\nMain Window --> Show Balance"<<endl;
   cout<<"================================================================"<<endl;
   cout<<"Your current balance is: $"<<fixed<<setprecision(2)<<u.getBalance()<<endl;
   cout<<"----------------------------------------------------------------"<<endl;
   cout<<"Press enter to go back to the Main Window"<<endl;
   enter(u,user, size);
}
//-------------------------------------DEPOSIT------------------------------------------
void deposit(account& u, account user[], int size){
   cout<<"\nMain Window --> Deposit (Enter the following information)"<<endl;
   cout<<"================================================================"<<endl;
   cout<<"The amount you want to deposit: ";
   float amount;
   cin>>amount;
   cout<<"----------------------------------------------------------------"<<endl;
   //Negative deposit
   if(amount<0){
       cout<<"Error: Cannot deposit a negative amount....Press enter"<<
       " to go back to the Main Window\n";
   }
   else{
       u.setBalance(u.getBalance()+amount);
       u.addTransaction("Deposit",amount);
       cout<<"Well done.  This was added to your balance successfully....Press enter"<<
       " to go back to the Main Window\n";
   }
   enter(u,user, size);
}
//------------------------------------WITHDRAW-----------------------------------------
void withdraw(account& u, account user[], int size){
    cout<<"\nMain Window --> Withdraw (Enter the following information)"<<endl;
    cout<<"================================================================"<<endl;
    cout<<"The amount you want to withdraw: ";
    float amount;
    cin>>amount;
    cout<<"----------------------------------------------------------------"<<endl;
    //Entered negative amount
    if(amount<0){
        cout<<"Error: Cannot withdraw a negative amount....Press enter"<<
        " to go back to the Main Window\n";
    }
    //Withdraw amount larger than balance
    else if (amount>u.getBalance()){
        cout<<"Error: Amount larger than balance....Press enter"<<
        " to go back to the Main Window\n";

    }
    else{
        u.addTransaction("Withdraw",amount);
        u.setBalance(u.getBalance()-amount);
        cout<<"Please take your money then....Press enter"<<
        " to go back to the Main Window\n";
    }
    enter(u,user, size);
}
//----------------------------SHOW ALL TRANSACTIONS------------------------------------
void showAllTransactions(account& u, account user[], int size){
    cout<<"\nMain Window --> Show All Transactions"<<endl;
    cout<<"================================================================"<<endl;
    cout<<"\nAccount no: "<<u.getAccNo()<<endl;
    cout<<"-------------------------------------------------------------\n";
     transaction* s=u.getTransactions();
    int n=u.getNumOfTransactions();
    //If no transactions made yet
    if(n==0){
        cout<<"NOTHING TO DISPLAY: No transactions made yet\n\n";
    }
    else{
    cout<<left<<setw(30)<<"Date"<<"| "<<
        left<<setw(20)<<"Type"<<"| "<<
        left<<setw(20)<<"Amount"<<endl;
    cout<<"-------------------------------------------------------------\n";
    
    for(int i=0; i<n;i++){
        cout<<left<<setw(30)<<s[i].getDate()<<"| "<<
        left<<setw(20)<<s[i].getType()<<"| "<<
        left<<fixed<<setprecision(2)<<setw(20)<<s[i].getAmount()<<endl;
    }
    cout<<"-------------------------------------------------------------\n";
    }
    cout<<"\nPress enter to go back to the Main Window\n";
    enter(u,user, size);

}



//----------------------------------MAIN()------------------------------------
int main(){
    account bankAccounts[10];
    //PRINTING OUT PASSWORDS MAKING IT EASIER TO LOGIN
    cout<<"HERE ARE SOME ACCOUNT DETAILS TO MAKE LOGGING IN EASIER\n";
    for(int i=0; i<10;i++){
        cout<<"THE PASSWORD FOR ACCOUNT "<<i+1<< " IS: "<<bankAccounts[i].getPassword()<<endl;
    }
    mainWindowLogin(bankAccounts,10);

}