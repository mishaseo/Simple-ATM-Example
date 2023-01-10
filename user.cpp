#include <iostream> 
#include <ctime>
#include <algorithm>
using namespace std;

class transaction{
    string date;
    string type;
    float amount;

    public:
    transaction(){}
    string getDate(){
        return this->date;
    }
    string getType(){
        return this->type;
    }
    float getAmount(){
        return this->amount;
    }
    friend class account;

    //Using default destrctor
};


class account{
    static int user_count;//Account number counter
    string account_no;
    string password;
    float balance;
    transaction* transactions;
    int trans_count;//Keep count of # of transactions
    int trans_max;//Max size of transactions array
    //Create random password
    string randomPass(){
            char num[36]={'1','2','3','4','5',
            '6','7','8','9','0','a', 'b', 'c', 
            'd', 'e', 'f', 'g',
            'h', 'i', 'j', 'k', 'l', 'm', 'n',
            'o', 'p', 'q', 'r', 's', 't', 'u',
            'v', 'w', 'x', 'y', 'z' };
            string res="";
            //Max length of password
            int n=1 + ( rand() % ( 10 - 1 + 1 ) );
            for(int i=0; i<n;i++){
                res=res+num[rand()%10];
            }  
            return res;
        }

    public:
        account(){
            user_count+=1;
            this->account_no=to_string(user_count);
            this->password=randomPass();
            this->balance=5000;
            this->trans_count=0;
            this->trans_max=9;//index 9
            transactions=new transaction[trans_max+1]; 
        }
        string getAccNo(){
            return this->account_no;
        }
        string getPassword(){
            return this->password;
        }
        float getBalance(){
            return this->balance;
        }
        transaction* getTransactions(){
            return transactions;
        }
        int getNumOfTransactions(){
            return trans_count;
        }
        void setBalance(float amount){
            this->balance=amount;
        }
        //Increases size of transaction array by 10
        void resize(){
            transaction* temp= new transaction[trans_max+11];
            for(int i=0; i<=trans_max;i++){
                temp[i]=transactions[i];
            }
            delete []transactions;
            transactions=NULL; 
            transactions=temp;
            trans_max=trans_max+10;
        }
        void addTransaction(string type, float amount){
            //If reached max size of the array
            if(trans_count==trans_max+1){
                resize(); 
            }
            transaction* current=&(transactions[trans_count]);
            trans_count++;
            //Update the attributes
            time_t now=time(0);
            string date_time=ctime(&now);
            date_time.erase(remove(date_time.begin(), date_time.end(), '\n'), date_time.end());
            (*current).date=date_time;
            (*current).amount=amount;
            (*current).type=type;
        }

        //Destructor
        ~account(){
            delete[]transactions;
            transactions=NULL;
        }
    
};
 
int account::user_count=0;

