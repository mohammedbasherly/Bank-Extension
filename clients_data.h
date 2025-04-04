#pragma once

#include <iostream>
#include <iomanip>
#include <fstream>
using namespace std;

#include "/home/hazard/vs code/lib/global_funcs.h"
#include "/home/hazard/vs code/lib/matrix_lib.h"
#include "/home/hazard/vs code/lib/clients_data.h"

using namespace global_funcs;
using namespace matrix_lib;

namespace clients_data {
  //const string clientsFilePath = "clients.txt";

  struct stClinetData {
    string  accountNumber = "";
    string pinCode = "";
    string fullName = "";
    string phone = "";
    float accountBalance = -1;
  };

  stClinetData readClientData(string accountNumber = "", string msg = "")
  {
      stClinetData clientData;

      cout << msg << endl;
      clientData.accountNumber = accountNumber == ""? readString("Account Number: ") : accountNumber;
      clientData.pinCode = readString("Pin code: ");
      clientData.fullName = readString("Full Name: ");
      clientData.phone = readString("Phone Number: ");
      clientData.accountBalance = readFloatNumber("Account Balance: ");

      return clientData;
  }

  string convertClientDataRecordToLine(stClinetData &clientData, string delim = "#//#")
  {
      string record = "";

      record += clientData.accountNumber + delim;
      record += clientData.pinCode + delim;
      record += clientData.fullName + delim;
      record += clientData.phone + delim;
      record += to_string(clientData.accountBalance);

      return record;
  }

  stClinetData convertLineToClientDataRecord(string text, string delim = "#//#")
  {
      stClinetData clientData;

      vector<string> vTokens = splitStringIntoVector(text, delim);

      clientData.accountNumber = vTokens[0];
      clientData.pinCode = vTokens[1];
      clientData.fullName = vTokens[2];
      clientData.phone = vTokens[3];
      clientData.accountBalance = stof(vTokens[4]);

      return clientData;
  }

  void printClientDataCard(stClinetData &clientData)
  {
      cout << "Account Number : " << clientData.accountNumber << endl;
      cout << "Pin code       : " << clientData.pinCode << endl;
      cout << "Full Name      : " << clientData.fullName << endl;
      cout << "Phone Number   : " << clientData.phone << endl;
      cout << "Account Balance: " << clientData.accountBalance << endl;
  }

  vector<stClinetData> readClientsData()
  {
      vector<stClinetData> vClientsData;
      char addMore = 'y';
      short i = 0;

      cout << endl;
      do
      {
          i++;
          cout << "- Client " << i << " ...";
          vClientsData.push_back(readClientData());
          cout << endl;

          cout << "Client " << i << " is added successfully, do you want to add more clients? [y/n]? ";
          addMore = readCharacter();
          cout << endl;
      } while (addMore == 'y' || addMore == 'Y');

      return vClientsData;
  }

  vector<string> convertCLientsDataToLines(vector<stClinetData> &vClientsData)
  {
    vector<string> clientsDataLines;

    string *ptr;
    ptr = new string;
    *ptr = "";

    for (stClinetData &client : vClientsData)
    {
      *ptr = convertClientDataRecordToLine(client);   
      clientsDataLines.push_back(*ptr);
    }
    delete ptr;

    return clientsDataLines;
  }

  void printClientsDataLines(vector<string> &lines)
  {
    for (string &line : lines)
    {
        cout << line << endl;
    }
  }

  void uploadClientsDataLinesToFile(string filePath, vector<string> lines, bool overwrite = false)
  {
    fstream file;
    if (overwrite)
      file.open(filePath, ios::out);
    else
      file.open(filePath, ios::out | ios::app);
      
    for (string &line : lines)
    {
      file << line << endl;
    }
    file.close();
  }

  void uploadClientDataLineToFile(string filePath, string line)
  {
    fstream file;
    file.open(filePath, ios::out | ios::app);
    file << line << endl;
    file.close();
  }

  vector<string> loadFileContentToVector(string filePath)
  {
    vector<string> vFile;

    fstream file;
    file.open(filePath, ios::in);

    string* ptrLine;
    ptrLine = new string;

    if (file.is_open())
    {
      while(getline(file, *ptrLine))
      {
        vFile.push_back(*ptrLine);
      }
      file.close();
    }
    return vFile;
  }
  
  bool isAccountNumberFound(vector<stClinetData> &vClientsData, string accountNumber)
  {
    for (stClinetData client : vClientsData)
    {
      if (client.accountNumber == accountNumber)
        return true;
    }
    return false;
  }

  bool isAccountNumberFound(string filePath, string accountNumber, string delim = "#//#")
  {
    vector<string> vLines = loadFileContentToVector(filePath);
    for (string &line : vLines)
    {
      line = line.substr(0, line.find(delim));
      if (line == accountNumber)
        return true;
    }
    return false;
  }

  void addNewClient(string filePath, string delim = "#//#")
  {
    string accountNumber = readString("Account Number: ");
    if (!isAccountNumberFound(filePath, accountNumber))
    {
      stClinetData client = readClientData(accountNumber);
      uploadClientDataLineToFile(filePath, convertClientDataRecordToLine(client, delim));
      cout << "\nClient is added succesfully <3\n";
    }
    else
      cout << "\nAccount Number (" << accountNumber << ") is already existed";
  }

  void addNewClients(string filePath, string delim = "#//#")
  {
    char addMore = 'y';
    do
    {
      cout << endl;
      addNewClient(filePath, delim);
      addMore = readCharacter(", do you want to add a new one? [y/n]? ");
    } while (tolower(addMore) == 'y');
    
  }

  void copyFileContentIntoVector(string& filePath, vector<string>& vFile)
  {
    fstream file;

    file.open(filePath, ios::in);

    string* ptrLine;
    ptrLine = new string;

    if (file.is_open())
    {
      while (getline(file, *ptrLine))
      {
        vFile.push_back(*ptrLine);
      }
      file.close();
    }
  }

  vector<stClinetData> convertLinesToClientsDataRecords(vector<string> &vLines, string delim ="#//#")
  {
    vector<stClinetData> vClientsData;
    for (string &line : vLines)
    {
      vClientsData.push_back(convertLineToClientDataRecord(line, delim));
    }
    return vClientsData;
  }

  void showClientsDataHeader(short size)
  {
    cout << "\n\t\t\t\tClinets List [" << size << " Client(s)]\n";
    cout << " _________________________________________________________________________________________\n\n";
    cout << " | " << left << setw(15) << "AccountNumber";
    cout << " | " << left << setw(10) << "Pin Code";
    cout << " | " << left << setw(25) << "Client Name";
    cout << " | " << left << setw(12) << "Phone Number";
    cout << " | " << left << setw(12) << "Balance";
    cout << "\n _________________________________________________________________________________________\n\n";
  }

  void printClientData(stClinetData &client)
  {
    cout << " | " << left << setw(15) << client.accountNumber;
    cout << " | " << left << setw(10) << client.pinCode;
    cout << " | " << left << setw(25) << client.fullName;
    cout << " | " << left << setw(12) << client.phone;
    cout << " | " << left << setw(12) << client.accountBalance;
  }

  void printClientsData(vector<stClinetData> &vClients)
  {
    for (stClinetData &client : vClients)
    {
      printClientData(client);
      cout << endl;
    }
    cout << " _________________________________________________________________________________________\n\n";
  }

  void showAllClients(string filePath, string delim = "#//#")
  {
    vector<string> vClientsLines = loadFileContentToVector(filePath);
    vector<stClinetData> vClientsData = convertLinesToClientsDataRecords(vClientsLines, delim);
    if (vClientsData.size() != 0)
    {
      showClientsDataHeader(vClientsLines.size());
      printClientsData(vClientsData);
    }
    else
    {
      cout << "\nNo Clients in system yet !\n";
    }
  }

  void showAllClients(vector<stClinetData> &vClientsData)
  {
    showClientsDataHeader(vClientsData.size());
    printClientsData(vClientsData);
  }

  vector<stClinetData> convertClientsDataFileToVector(string filePath, string delim = "#//#")
  {
    vector<string> vClientsLines = loadFileContentToVector(filePath);
    vector<stClinetData> vClientsData = convertLinesToClientsDataRecords(vClientsLines, delim);

    return vClientsData;
  }

  void printClientDataCardByAccountNumber(string filePath, string accountNumber, string delim = "#//#", string msg = "")
  {
    vector<stClinetData> vClientsData = convertClientsDataFileToVector(filePath, delim);
    for (stClinetData client : vClientsData)
    {
      if (client.accountNumber == accountNumber)
      {
        cout << msg << endl;
        printClientDataCard(client);
        return;
      }
    }
    cout << "\nClient with account number (" << accountNumber << ") is not found.\n";
  }

  void printClientDataCardByAccountNumber(vector<stClinetData> &vClientsData, string accountNumber, string msg = "")
  {
    for (stClinetData client : vClientsData)
    {
      if (client.accountNumber == accountNumber)
      {
        cout << msg << endl;
        printClientDataCard(client);
        return;
      }
    }
    cout << "\nClient with account number (" << accountNumber << ") is not found.\n";
  }

  stClinetData getClientByAccountNumber(vector<stClinetData> &vClientsData, string accountNumber)
  {
    stClinetData clientData;
    for (stClinetData &client : vClientsData)
    {
      if (client.accountNumber == accountNumber)
      {
        clientData = client;
      }
    }
    return clientData;
  }

  stClinetData getClientByAccountNumber(string filePath, string accountNumber)
  {
    stClinetData clientData;
    vector<stClinetData> vClientsData = convertClientsDataFileToVector(filePath);
    for (stClinetData client : vClientsData)
    {
      if (client.accountNumber == accountNumber)
        clientData = client;
    }
    return clientData;
  }

  void deleteClientByAccountNumber(string filePath, string accountNumber, string delim = "#//#")
  {
    vector<stClinetData> vClientsData = convertClientsDataFileToVector(filePath, delim);
    if (isAccountNumberFound(vClientsData, accountNumber))
    {
      printClientDataCardByAccountNumber(vClientsData, accountNumber);
      cout << endl;
      char isSure = readCharacter("are you sure you want to delete this client? [y/n]? ");
      if (isSure == 'y' || isSure == 'Y')
      {
        fstream file;
        file.open(filePath, ios::out);
        string clientLine = "";
        for (stClinetData client : vClientsData)
        {
          if (client.accountNumber != accountNumber)
          {
            clientLine = convertClientDataRecordToLine(client, delim);
            file << clientLine << endl;
          }
        }
        cout << "Client is deleted succefully.\n";
        file.close();
      }
    }
    else
    {
      cout << "Client with account number (" << accountNumber << ") is not found\n";
    }
  }

  void deleteClientByAccountNumber(vector<stClinetData> &vClientsData, string accountNumber)
  {
    vector<stClinetData> vClientsData2;
    if (isAccountNumberFound(vClientsData, accountNumber))
    {
      printClientDataCardByAccountNumber(vClientsData, accountNumber);
      cout << endl;
      char isSure = readCharacter("are you sure you want to delete this client? [y/n]? ");
      if (isSure == 'y' || isSure == 'Y')
      {
        for (stClinetData client : vClientsData)
        {
          if (client.accountNumber != accountNumber)
          {
            vClientsData2.push_back(client);
          }
        }
        vClientsData = vClientsData2;
        cout << "Client is deleted from Vector succefully.\n";
      }
    }
    else
    {
      cout << "Client with account number (" << accountNumber << ") is not found\n";
    }
  }

  void changeClientRecord(stClinetData &clientData, string accountNumber)
  {
      cout << "Account Number: " << accountNumber << endl;
      clientData.pinCode = readString("Pin code: ");
      clientData.fullName = readString("Full Name: ");
      clientData.phone = readString("Phone Number: ");
      clientData.accountBalance = readFloatNumber("Account Balance: ");
  }

  void saveClientsDataToFile(string filePath, vector<stClinetData> &vClientsData, string delim = "#//#")
  {
    fstream file;
    file.open(filePath, ios::out); // overwrite

    string line = "";
    for (stClinetData &client : vClientsData)
    {
      line = convertClientDataRecordToLine(client, delim);
      file << line << endl;
    }
    file.close();
  }

  void updateClientData(vector<stClinetData> vClientsData, string accountNumber)
  {
    if (isAccountNumberFound(vClientsData, accountNumber))
    {
      printClientDataCardByAccountNumber(vClientsData, accountNumber);
      cout << endl;
      char isSure = readCharacter("are you sure you want to update this client? [y/n]? ");
      if (isSure == 'y' || isSure == 'Y')
      {
        for (stClinetData &client : vClientsData)
        {
          if (client.accountNumber == accountNumber)
          {
            changeClientRecord(client, accountNumber);
            break;
          }
        }
        cout << "\nCLient has been updated succefully.\n";
      }
    }
    else
    {
      cout << "\nClient with account number (" << accountNumber << ") is not found\n";
    }
  }

  void updateClientData(string filePath, string accountNumber, string delim = "#//#")
  {
    vector<stClinetData> vClientsData = convertClientsDataFileToVector(filePath, delim);
    if (isAccountNumberFound(vClientsData, accountNumber))
    {
      printClientDataCardByAccountNumber(vClientsData, accountNumber);
      cout << endl;
      char isSure = readCharacter("are you sure you want to update this client? [y/n]? ");
      if (isSure == 'y' || isSure == 'Y')
      {
        for (stClinetData &client : vClientsData)
        {
          if (client.accountNumber == accountNumber)
          {
            changeClientRecord(client, accountNumber);
            break;
          }
        }
        saveClientsDataToFile(filePath, vClientsData, delim);
        cout << "\nCLient has been updated succefully.\n";
      }
    }
    else
    {
      cout << "\nClient with account number (" << accountNumber << ") is not found\n";
    }
  }
 
  void printClientsBalances(string filePath, string delim = "#//#")
  {
    vector<stClinetData> vClients = convertClientsDataFileToVector(filePath, delim);
    float totalBalance = 0;
    if (vClients.size() != 0)
    {
      cout << "\n\t\t\tBalances List [" << vClients.size() << " Client(s)]\n";
      cout << " _________________________________________________________________________\n\n";
      cout << " | " << left << setw(15) << "AccountNumber";
      cout << " | " << left << setw(25) << "Client Name";
      cout << " | " << left << setw(12) << "Balance";
      cout << "\n _________________________________________________________________________\n\n";
      for (stClinetData &client : vClients)
      {
        cout << " | " << left << setw(15) << client.accountNumber;
        cout << " | " << left << setw(25) << client.fullName;
        cout << " | " << left << setw(12) << client.accountBalance;
        cout << endl;
        totalBalance += client.accountBalance;
      }
      cout << " _________________________________________________________________________\n";
      cout << "\n\t\t\tTotal Balances = " << totalBalance << endl;
    }
    else
    {
      cout << "\nNo Clients in system yet !\n";
    }
  }

}
