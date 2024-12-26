#include<iostream>
#include<fstream>
#include<string.h>
#include<stdlib.h>
#include<conio.h>
using namespace std;

class BANK{
	private:
		char name[30];
		int PIN;
		float balance;
	public:
		void getAccountDetails()
		{
			cout<<"\n Enter your name: ";
    		cin.get(name,30);
    		fflush(stdin);
			cout<<"	Set your PIN: ";
			cin>>PIN;
			balance = 0;
		}
		void showAccount()
		{
			cout<<"\n\t\t\t\t\t--------------------------------------\n";
			cout<<"\t\t\t\t\t            Account Details             \n";
			cout<<"\t\t\t\t\t--------------------------------------\n";
			cout<<endl<<"\t\t\t\t\tName:      "<<name<<endl<<endl;
			cout<<"\t\t\t\t\tPIN:       "<<PIN<<endl<<endl;
			cout<<"\t\t\t\t\tBalance:   $"<<balance<<endl<<endl;
		}
		int openAccount(char* , int);
		void viewAccountDetails(char* , int);
		void viewAllAccounts();
		void depositMoney(char* , int);
		int withdrawMoney(char* , int);
		int transferMoney(char* , int , char* );
		int close_Account(char* , int);
};

int BANK::openAccount(char* n, int p){
	ifstream fin;
	bool AccountExist = false;
	fin.open("Bank.txt",ios::in | ios::binary);
	if(!fin)
		cout<<"\n File not found\n";
	else
	{
		fin.read((char*)this , sizeof(*this));
		while(!fin.eof())
		{
			if(!strcmp(n , name))	
			{
				cout<<"\n Account name already taken. Please select another!\n";
				AccountExist = true;
				return 0;
			}
			else if(p==PIN)
			{
				cout<<"\n PIN already taken. Please select another!\n";
				AccountExist = true;
				return 0;
			}
			fin.read((char*)this , sizeof(*this));
		}
	}
	fin.close();
	if(AccountExist == false)
	{
		ofstream fout;
		fout.open("Bank.txt",ios::app | ios::binary);
		if(!fout)
			cout<<"\n File not found!\n";
		else
		{
			strcpy(name , n);
			PIN = p;
			balance = 0;
			fout.write((char*)this , sizeof(*this)); 
		}
		cout<<" Account has successfully been opened!"<<endl;
		fout.close();
	}
}

void BANK::viewAccountDetails(char *n , int p){
	ifstream fin;
	int counter=0;
	fin.open("Bank.txt" , ios::in | ios::binary);
	if(!fin)
	{
		cout<<"\n File not found!\n"<<endl;
	}
	else{
		fin.read((char*)this , sizeof(*this)); 
		while(!fin.eof())
		{
			if((!strcmp(n,name)) && p == PIN)
			{
				showAccount();
				counter++;
			}
			fin.read((char*)this , sizeof(*this));
		}
		if(counter == 0)
		{
			cout<<"\n Account not found. It may not be opened yet!"<<endl;
		}
	}
	fin.close();
}

void BANK::viewAllAccounts(){
	ifstream fin;
	int counter=0;
	fin.open("Bank.txt" , ios::in | ios::binary);
	if(!fin)
	{
		cout<<"\n File not found!\n"<<endl;
	}
	else
	{
		fin.read((char*)this , sizeof(*this));
		while(!fin.eof())
		{
			showAccount();
			fin.read((char*)this , sizeof(*this));
		}
	}
	fin.close();
}

void BANK::depositMoney(char* n , int p)
{
	fstream file;
	float newAmount=0 ; 
	int counter=0;
	file.open("Bank.txt" , ios::in | ios::out | ios::ate | ios::binary);
	if(!file)
	{
		cout<<"\n File not found!\n";
	}
	else
	{
		file.seekg(0);
		file.read((char*)this , sizeof(*this));
		while(!file.eof())
		{
			if((!strcmp(n , name)) && p==PIN)
			{
				cout<<"\n Enter the money to be deposited: ";
				cin>>newAmount;
				if(newAmount<0)
						newAmount = -newAmount;
				file.seekp(file.tellp() - sizeof(*this));
				balance += newAmount;
				file.write((char*)this , sizeof(*this));
				showAccount();
				counter++;
			}
			file.read((char*)this , sizeof(*this));
		}
		if(counter==0)
			cout<<"\n Account not found. It may not be opened yet!\n";
		file.close();
	}
}

int BANK::withdrawMoney(char* n , int p)
{
	float newAmount = 0;
	int counter=0;
	fstream file;
	file.open("Bank.txt",ios::in | ios::out | ios::ate | ios::binary);
	if(!file)
	{
		cout<<"\n File not found!\n";
	}
	else{
		file.seekg(0);
		file.read((char*)this , sizeof(*this));
		while(!file.eof())
		{
			if(!strcmp(n,name) && p==PIN)
			{
				if(balance==0)
					cout<<"\n Insufficient Funds!"<<endl;
				else
				{
					cout<<"\n Enter the money to be withdrawn: ";
					cin>>newAmount;
					if(newAmount<0)
						newAmount = -newAmount;
					if(newAmount>balance)
					{
						cout<<"\n Insufficient Funds!\n";
						counter++;
						return 0;
					}
					file.seekp(file.tellp() - sizeof(*this));
					balance -= newAmount;
					file.write((char*)this , sizeof(*this));
					showAccount();
				}
				counter++;
			}
			file.read((char*)this , sizeof(*this));
		}
		if(counter==0)
		{
			cout<<"\n Account not found. It may not be opened yet!"<<endl;
		}
		file.close();
	}
}

int BANK::transferMoney(char* n1 , int p1 , char* n2)
{
	fstream file;
	float newAmount = 0 ;
	int counter1 = 0 , counter2=0;
	file.open("Bank.txt" , ios::in | ios::out | ios::ate | ios::binary);
	if(!file)
	{
		cout<<"\n File not found!\n";
	}
	else
	{
		file.seekg(0);
		file.read((char*)this , sizeof(*this));
		while(!file.eof())
		{
			if(!strcmp(n1 , name) && p1==PIN)
			{
				if(balance==0)
					cout<<"\n Insufficient Funds!"<<endl;
				else
				{
					cout<<"\n Enter the money to be transfered: ";
					cin>>newAmount;
					if(newAmount<0)
						newAmount = -newAmount;
					if(newAmount>balance)
					{
						cout<<"\nInsufficient Funds!\n";
						counter1++;
						return 0;
					}
					file.seekp(file.tellp() - sizeof(*this));
					balance -= newAmount;
					file.write((char*)this , sizeof(*this));
					showAccount();
				}
				counter1++;
			}
			file.read((char*)this , sizeof(*this));
		}
		if(counter1==0)
		{
			cout<<"\n Sender's Account not found. It may not be opened yet!\n";
		}
		file.clear();
		file.seekg(0);
		file.read((char*)this , sizeof(*this));
		while(!file.eof())
		{
			if(!strcmp(n2 , name))
			{
				file.seekp(file.tellp() - sizeof(*this));
				balance += newAmount;
				file.write((char*)this , sizeof(*this));
				counter2++;
			}
			file.read((char*)this , sizeof(*this));
		}
		if(counter2==0)
			cout<<"\n Reciever's Account not found. It may not be opened yet!\n";
		else
		{
			cout<<"\n Amount successfully transfered!"<<endl;
		}
	}
	file.close();
}

int BANK::close_Account(char* n ,int p)
{
	ifstream fin;
	ofstream fout;
	int counter = 0;
	fin.open("Bank.txt",ios::in | ios::binary);
	if(!fin)
		cout<<"\n File not found\n"<<endl;
	else
	{
		fout.open("tempfile.txt" , ios::out | ios::binary);
		fin.read((char*)this , sizeof(*this));
		while(!fin.eof())
		{
			if(strcmp(n , name))
			{
				fout.write((char*)this , sizeof(*this));
			}
			else
				counter++;
			fin.read((char*)this , sizeof(*this));
		}
		fin.close();
		fout.close();
		if(counter==0)
		{
			cout<<"\n Account not found. It may not be opened yet!\n";
			return 0;
		}
		remove("Bank.txt");
		rename("tempfile.txt","Bank.txt");
		cout<<"\n Account has been successfully closed!\n";
	}
}

void clearScreen()
{
	cout<<"\n Press any key to continue......";
	getch();
	system("CLS");
}

int main()
{
	int managerPIN = 9999;
	BANK user;
	int choice;
	char username[30];
	int pin;
	while(1)
	{
		system("color 70");
		cout<<"\t\t\t\t\t|---------------------------------------|"<<endl;
		cout<<"\t\t\t\t\t|         THE BANK APPLICATION          |"<<endl;
		cout<<"\t\t\t\t\t|---------------------------------------|"<<endl;
		cout<<"\t\t\t\t\t         Program Written in: C++       "<<endl;
		cout<<"\t\t\t\t\t           Made By RAYYAN ARIF           "<<endl<<endl;
		clearScreen();
		cout<<"\n You can perform the following operations!\n"<<endl;
		cout<<" 1. Open Account\n"<<endl;
		cout<<" 2. View Your Account Details\n"<<endl;
		cout<<" 3. View All Account Details ( Accessed only by the Manager )\n"<<endl;
		cout<<" 4. Deposit Money\n"<<endl;
		cout<<" 5. Withdraw Money\n"<<endl;
		cout<<" 6. Transfer Money To Another Account\n"<<endl;
		cout<<" 7. Close Your Account\n"<<endl;
		cout<<" 8. Exit The Bank Application\n"<<endl;
		cout<<" Enter your choice (1-8): ";
		cin>>choice;
		cin.ignore();
		clearScreen();
		switch(choice)
		{
			case 1:
				cout<<"\n Enter your Account Name: ";
				cin.get(username,30);
    			fflush(stdin);
				cout<<" Enter your PIN: ";
				cin>>pin;
				user.openAccount(username , pin);
				clearScreen();
				break;
			case 2:
				cout<<"\n Enter your Account Name: ";
				cin.get(username,30);
    			fflush(stdin);
				cout<<" Enter your PIN: ";
				cin>>pin;
				user.viewAccountDetails(username , pin);
				clearScreen();
				break;
			case 3:
				cout<<"\n Enter manager's PIN: ";
				cin>>pin;
				if(pin == managerPIN)
				{
					cout<<"\n WELCOME THE MANAGER! \n";
					user.viewAllAccounts();
				}
				else
				{
					cout<<"\n This option is only available to the Manager\n";
				}
				clearScreen();
				break;
			case 4:
				cout<<"\n Enter your Account Name: ";
				cin.get(username,30);
    			fflush(stdin);
				cout<<" Enter your PIN: ";
				cin>>pin;
				user.depositMoney(username , pin);
				clearScreen();
				break;
			case 5:
				cout<<"\n Enter your Account Name: ";
				cin.get(username,30);
    			fflush(stdin);
				cout<<" Enter your PIN: ";
				cin>>pin;
				user.withdrawMoney(username, pin);
				clearScreen();
				break;
			case 6:
				char receiver[30];
				cout<<"\n Enter your Account Name: ";
				cin.get(username,30);
    			fflush(stdin);
				cout<<" Enter your PIN: ";
				cin>>pin;
				cin.ignore();
				cout<<" Enter Reciever's Account Name: ";
				cin.get(receiver,30);
    			fflush(stdin);
    			if(!strcmp(username , receiver))
    				cout<<"\n You cannot transfer money to your account!\n";
    			else
					user.transferMoney(username , pin , receiver);
				clearScreen();
				break;
			case 7:
				cout<<"\n Enter your Account Name: ";
				cin.get(username,30);
    			fflush(stdin);
				cout<<" Enter your PIN: ";
				cin>>pin;
				user.close_Account(username , pin);
				clearScreen();
				break;
			case 8:
				cout<<"\n Thanks for using the application!"<<endl;
				return 0;
			default:
				cout<<"\n Invalid choice. Please enter a valid choice!"<<endl;
				clearScreen();
				break;
		}
	}
	return 0;
}