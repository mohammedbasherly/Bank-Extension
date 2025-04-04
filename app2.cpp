#include <iostream>
using namespace std;

#include "/home/hazard/vs code/lib/clients_data.h"
#include "/home/hazard/vs code/lib/matrix_lib.h"
#include "/home/hazard/vs code/lib/global_funcs.h"

using namespace clients_data;
using namespace matrix_lib;
using namespace global_funcs;

enum enOption {
    clientList = 1,
    newClient = 2,
    deleteClient = 3,
    updateClient = 4,
    findClient = 5,
    transactions = 6,
    exitProgram = 7
};

enum enTransaction {
    deposit = 1,
    withdraw = 2,
    totalBalances = 3,
    mainMenu = 4
};

void showMainMenuScreen()
{
    system("clear");
    cout << " ===============================================\n";
    cout << "\t\tMain Menu Screen\n";
    cout << " ===============================================\n";
    cout << "\t" << "[1] Show Clients List\n";
    cout << "\t" << "[2] Add New Client\n";
    cout << "\t" << "[3] Delete Client\n";
    cout << "\t" << "[4] Update Client Info\n";
    cout << "\t" << "[5] Find Client\n";
    cout << "\t" << "[6] Transactions\n";
    cout << "\t" << "[7] Exit\n";
    cout << " ===============================================\n";
}

void showScreenHeader(enOption option)
{
    system("clear");
    switch (option)
    {
    case enOption::clientList:
        cout << " ===============================================\n";
        cout << "\t\tClients List Screen\n";
        cout << " ===============================================\n";
        return;
    case enOption::newClient:
        cout << " ===============================================\n";
        cout << "\t\tAdd New Client Screen\n";
        cout << " ===============================================\n";
        return;
    case enOption::deleteClient:
        cout << " ===============================================\n";
        cout << "\t\tDelete Client Screen\n";
        cout << " ===============================================\n";
        return;
    case enOption::updateClient:
        cout << " ===============================================\n";
        cout << "\t\tUpdate Client Screen\n";
        cout << " ===============================================\n";
        return;
    case enOption::findClient:
        cout << " ===============================================\n";
        cout << "\t\tFind Client Screen\n";
        cout << " ===============================================\n";
        return;
    case enOption::transactions:
        cout << " ===============================================\n";
        cout << "\t\tTransactions Screen\n";
        cout << " ===============================================\n";
        return;
    case enOption::exitProgram:
        cout << " ===============================================\n";
        cout << "\t\tExit Program Screen\n";
        cout << " ===============================================\n";
        return;
    default:
        break;
    }
}

void showScreenBottom()
{
    cout << "\nPress any key to go back to [Main Menu Screen] ...";
    cin.ignore();
    cin.get();
}

void clientListScreen(string filePath, string delim = "#//#")
{
    showScreenHeader(enOption::clientList);
    showAllClients(filePath, delim);
    showScreenBottom();
}

void newClientScreen(string filePath, string delim = "#//#")
{
    cin.ignore();
    showScreenHeader(enOption::newClient);
    addNewClients(filePath, delim);
    showScreenBottom();
}

void deleteClientScreen(string filePath, string delim = "#//#")
{
    cin.ignore();
    showScreenHeader(enOption::deleteClient);
    string accountNumber = readString("Enter Account Number: ");
    deleteClientByAccountNumber(filePath, accountNumber, delim);
    showScreenBottom();
}

void updateClientScreen(string filePath, string delim = "#//#")
{
    cin.ignore();
    showScreenHeader(enOption::updateClient);
    string accountNumber = readString("Enter Account Number: ");
    updateClientData(filePath, accountNumber, delim);
    showScreenBottom();
}

void findClientScreen(string filePath, string delim = "#//#")
{
    cin.ignore();
    showScreenHeader(enOption::findClient);
    string accountNumber = readString("Enter Account Number: ");
    printClientDataCardByAccountNumber(filePath, accountNumber, delim);
    showScreenBottom();
}

void exitProgramScreen()
{
    showScreenHeader(enOption::exitProgram);
    cout << "Press any key to end the program...";
    cin.ignore();
    cin.get();
}

void showScreenHeader(enTransaction transaction)
{
    system("clear");
    switch (transaction)
    {
    case enTransaction::deposit:
        cout << " ----------------------------------------------\n";
        cout << "\t\tDeposit Screen\n";
        cout << " ----------------------------------------------\n";
        break;
    case enTransaction::withdraw:
        cout << " ----------------------------------------------\n";
        cout << "\t\tWithdraw Screen\n";
        cout << " ----------------------------------------------\n";
        break;
    default:
        break;
    }
}

void depositToClient(float depositAmount, string filePath, string accountNumber, string delim = "#//#")
{
    vector<stClinetData> vClients = convertClientsDataFileToVector(filePath, delim);
    for (stClinetData &client : vClients)
    {
        if (client.accountNumber == accountNumber)
        {
            client.accountBalance += depositAmount;
            uploadClientsDataLinesToFile(filePath, convertCLientsDataToLines(vClients), true);
            if (depositAmount > 0)
                cout << "\nDeposit Transaction has been done succefully !\n";
            else
                cout << "\nWithdraw Transaction has been done succefully !\n";
            cout << "New Balance is " << client.accountBalance << endl;
            break;
        }
    }
}

void showTransactionsScreenBottom()
{
    cout << "\nPress any key to go back to [Transactions Menu Screen] ...";
    cin.ignore();
    cin.get();
}

void depositScreen(string filePath, string delim = "#//#")
{
    cin.ignore();
    showScreenHeader(enTransaction::deposit);
    string accountNumber = readString("Enter Account Number: ");
    printClientDataCardByAccountNumber(filePath, accountNumber, delim);
    if (isAccountNumberFound(filePath, accountNumber, delim))
    {
        float depositAmount = readFloatNumber("\nEnter deposit amount: ");
        char isSure = readCharacter("\nAre you sure you want to perform this transaction? [y/n]? ");
        if (isSure == 'y' || isSure == 'Y')
        {
            depositToClient(depositAmount, filePath, accountNumber, delim);
            
        }
    }
    showTransactionsScreenBottom();
}

void withdrawScreen(string filePath, string delim = "#//#")
{
    cin.ignore();
    showScreenHeader(enTransaction::withdraw);
    string accountNumber = readString("Enter Account Number: ");
    printClientDataCardByAccountNumber(filePath, accountNumber, delim);
    if (isAccountNumberFound(filePath, accountNumber, delim))
    {
        float depositAmount;
        bool isAmountOkay;
        do
        {
            depositAmount = readFloatNumber("\nEnter withdraw amount: ");
            float balance = getClientByAccountNumber(filePath, accountNumber).accountBalance;
            isAmountOkay = balance > depositAmount;
            if (isAmountOkay)
            {
                char isSure = readCharacter("\nAre you sure you want to perform this transaction? [y/n]? ");
                if (isSure == 'y' || isSure == 'Y')
                    depositToClient(depositAmount * -1, filePath, accountNumber, delim);
            }
            else
                cout << "\nAmount exceed client's balanca, you can withdraw up to: " << balance;
        } while (!isAmountOkay);
        
    }
    showTransactionsScreenBottom();
}

void totalBalancesScreen(string filePath, string delim = "#//#")
{
    showScreenHeader(enTransaction::totalBalances);
    printClientsBalances(filePath, delim);
    showTransactionsScreenBottom();
}

void startTransactionScreen(enTransaction transaction, string filePath, string delim = "#//#")
{
    switch (transaction)
    {
    case enTransaction::deposit:
        depositScreen(filePath, delim);
        return;
    case enTransaction::withdraw:
        withdrawScreen(filePath, delim);
        return;
    case enTransaction::totalBalances:
        totalBalancesScreen(filePath, delim);
        return;
    default:
        break;
    }
}

void transactionsMenu(string filePath, string delim = "#//#")
{
    enTransaction transaction;
    do
    {
        showScreenHeader(enOption::transactions);
        cout << "\t" << "[1] Deposit\n";
        cout << "\t" << "[2] Withdraw\n";
        cout << "\t" << "[3] Total Balances\n";
        cout << "\t" << "[4] Main Menu\n";
        cout << " ===============================================\n";
        transaction = (enTransaction) readIntNumberInRange(1, 4, "What do you want to do? [1-4]? ");
        startTransactionScreen(transaction, filePath, delim);
    } while (transaction != enTransaction::mainMenu);
    showScreenBottom();
}

void startScreen(enOption option, string filePath, string delim = "#//#")
{
    switch (option)
    {
    case enOption::clientList:
        clientListScreen(filePath, delim);
        return;
    case enOption::newClient:
        newClientScreen(filePath, delim);
        return;
    case enOption::deleteClient:
        deleteClientScreen(filePath, delim);
        return;
    case enOption::updateClient:
        updateClientScreen(filePath, delim);
        return;
    case enOption::findClient:
        findClientScreen(filePath, delim);
        return;
    case enOption::transactions:
        transactionsMenu(filePath, delim);
        return;
    case enOption::exitProgram:
        exitProgramScreen();
        return;
    default:
        break;
    }
}

void startProgram(string filePath, string delim = "#//#")
{
    enOption option;
    do
    {
        showMainMenuScreen();
        option = (enOption) readIntNumberInRange(1, 7, "Choose an option? [1-7]? ");
        startScreen(option, filePath, delim);
    } while (option != enOption::exitProgram);
    
}

int main()
{
    string filePath = "Bank_Clients.txt";
    startProgram(filePath);

    return 0;
}