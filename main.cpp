#include <iostream>
#include <fstream>
#include <chrono>
#include <memory>
#include <ctime>

float balance = 1000.0;

const std::string FILE_NAME = "transaction";
const std::string FILE_EXTENSION = ".txt";

// this is how you would hold a reference to a file in a memory safe way
// google what it means: unique_ptr
std::unique_ptr<std::ofstream> fileRef;

// this is unsafe, but it will hold up for now
std::ofstream logFile;

void startLogFile() {
    const auto t = std::chrono::system_clock::now();
    const long ts = std::chrono::duration_cast<std::chrono::seconds>(t.time_since_epoch()).count();
    const std::string fileName = FILE_NAME + "_" + std::to_string(ts) + FILE_EXTENSION;
    logFile.open(fileName);
    logFile<<"******************"<<std::endl;
}

void closeLogFile() {
    logFile<<"******************"<<std::endl;
    logFile.close();
}

void logToFile(const std::string &log) {
    //auto const time = std::time_t();

    if (logFile.is_open()) {
        logFile<<log<<std::endl;
    }
}

void menu() {
    // \n is equal to std::endl;
    std::cout << "\n";
    std::cout << "\n";
    std::cout<< "                   Welcome to FrecklesBank ATM!                         " << std::endl;
    std::cout<< "                   ____________________________                         " << std::endl;
    std::cout<< std::endl;

    std::cout<< " 1. Check Balance" << std::endl;
    std::cout<< " 2. Deposit" << std::endl;
    std::cout<< " 3. Withdraw" << std::endl;
    std::cout<< " 4. Transfer" << std::endl;
    std::cout<< " 5. Exit" << std::endl;
    std::cout<< std::endl;
    std::cout<< "_______________________________________________________________________" << std::endl;
    std::cout << "\n";
    std::cout << "\n";
}


void checkBalance() {
    std::cout<< "Your balance is: "<< balance << std::endl;
}

void deposit() {
    std::cout<<"**************** "<< std::endl;
    std::cout<<"Deposit"<<std::endl;
    std::cout<<"****************"<< std::endl;

    float amount=0;

        std::cout<<"Enter amount to deposit: "<<std::endl;
        std::cin>> amount;
        std::cout<< "$" << amount << " was deposited into current balance."<<std::endl;

    if(amount > 1000){
    std::cout<<"Deposit over $1000 is invalid."<<std::endl;
    }
    else {
        balance = balance + amount;
        logToFile(std::to_string(amount) + " was deposited into current balance.");
        checkBalance();
    }
}

void withdraw() {
    std::cout<<"**************** "<< std::endl;
    std::cout<<"withdraw"<<std::endl;
    std::cout<<"****************"<< std::endl;

    std::cout<<"Your current balance is: "<< balance << std::endl;
    float availablebalance = balance - 50;
    std::cout<<"Balance available for withdrawal: "<< availablebalance << std::endl;


    float withdrawal=0;

    std::cout<<"Enter amount to withdraw: "<<std::endl;
    std::cin>> withdrawal;

    if(withdrawal > availablebalance){
        std::cout<<"invalid withdraw."<<std::endl;
    }
    else {
        std::cout<< "$" << withdrawal << " was withdrawn."<<std::endl;
        balance = availablebalance - withdrawal;
        logToFile(std::to_string(withdrawal) + " was withdrawn from current balance.");
        checkBalance();
    }
}

void transfer() {
    std::cout<<"**************** "<< std::endl;
    std::cout<<"transfer"<<std::endl;
    std::cout<<"****************"<< std::endl;

    std::cout<<"Your current balance is: "<< balance << std::endl;
    float transferBalance = balance - 50;
    std::cout<<"balance available for transfer: "<< transferBalance << std::endl;

    float amountTransfer = 0;

    std::cout<<"Enter amount to transfer: "<<std::endl;
    std::cin>> amountTransfer;

    if(amountTransfer > 500){
        std::cout<<"Must be less than $500."<<std::endl;}
    else {
        std::cout << "$" << amountTransfer << " was transferred to external account."<<std::endl;
        balance = balance - amountTransfer;
        logToFile(std::to_string(amountTransfer) + " was transferred to external account");
        checkBalance();
    }
}


void exitAtm(bool& loop) {
    std::cout<<"Have a nice day \nSincerely FrecklesBank"<<std::endl;
    loop = false;
}

int main() {

    startLogFile();

    int choice;
    bool loop = true;
    float balance = 1000.0;

    while (loop){
        menu();
        std::cout<< "Enter your choice: "<< std::endl;
        std::cin >> choice;

        switch (choice) {
            case 1:
                checkBalance();
                break;
            case 2:
                deposit();
                break;
            case 3:
                withdraw();
                break;
            case 4:
                transfer();
                break;
            case 5:
                exitAtm(loop);
                break;
            default:
                std::cout<<"Invalid Choice"<<std::endl;
            break;
        }


    }

    closeLogFile();

    return 0;

}



