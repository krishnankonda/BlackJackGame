/**
    Final Project
    blackjackgame.cpp
    CS50
    @author Krishna Konda
    Visual Studio 2019
*/

#include <iostream>
#include <string>
#include <fstream>
#include <vector>
#include <cctype>
#include <iomanip>
#include <cstdlib>
#include <ctime>
#include <algorithm>


using namespace std;

//Card suit's enum types
enum cardSuit
{
	Hearts, Spades, Clubs, Diamonds
};

//Card struct which includes card's value, its suit, and whether it is face up or face down
struct card 
{
    int val;
    cardSuit suit;
    bool up; 
};

//Prototypes
card deal();
void printMenu(int input = 0);
void displayBanner();
bool isValidName(string name); 
void play();


//Returns a random new card
card deal() 
{
    card topCard;

    //Chooses random number between 1 and 13 for the value
    topCard.val = (rand() % 13) + 1; 
    int suit = rand() % 4;

    //Chooses random number between 1 and 4 for the suit
    switch (suit)
    {
        case 0:
            topCard.suit = Spades;
            break;
        case 1:
            topCard.suit = Hearts;
            break;
        case 2:
            topCard.suit = Diamonds;
            break;
        case 3:
            topCard.suit = Clubs;
            break;
    }

    //We will change this to false later if this is the dealer's face down card
    topCard.up = true;

    //Returns this new card
    return topCard;
}


//Player Class
class Player
{
private:
    string name;
    card* hand;
    int handSize;
    int bet;
    int balance;
    int tallyWin;
    int handValue;
    int aceCount;
    //Some high stakes tables may keep a higher bet minimum. This variable allows me to change the bet minimum in these cases.
    int betMinimum;
public:
    //Default Constructor
    Player()
    {
        name = "Player";
        handSize = 2;
        hand = new card[handSize];
        balance = 1000;
        tallyWin = 0;
        betMinimum = 5;
        handValue = 0;
        bet = 0;
        aceCount = 0;
    }

    //Another Constructor that takes in a name and balance
    Player(string name2, int balance2 = 1000)
    {
        name = name2;
        handSize = 2;
        hand = new card[handSize];
        balance = balance2;
        tallyWin = 0;
        betMinimum = 5;
        handValue=0;
        bet = 0;
        aceCount = 0;
    }

    //Copy Constructor
    Player(const Player& player2)
    {
        name = player2.name;
        handSize = player2.handSize;
        balance = player2.balance;
        aceCount = player2.aceCount;
        tallyWin = 0;
        betMinimum = 5;
        handValue = 0;
        bet = 0;
        hand = new card[handSize];
        for (int i = 0; i < handSize; i++)
        {
            hand[i] = player2.hand[i];
        }
    }

    //Sets player's initial hand (gives him 2 cards)
    void setHand()
    {
        for (int i = 0; i < handSize; i++)
        {
            hand[i] = deal();
        }
    }
    //Takes in a card as a parameter card's suit 
    string printSuit(card topCard)
    {
        //Checks enum's suit value (0, 1, 2, or 3) and then returns the char version of suit so that we can easily display later
        switch (topCard.suit)
        {
        case 0:
            return "Hearts";
        case 1:
            return "Spades";
        case 2:
            return "Clubs";
        case 3:
            return "Diamonds";
        }
    }
    //Prints out all Cards in hand
    void printCards()
    {
        string* cardTypes = new string[13];
        cardTypes[0] = "Ace";
        cardTypes[1] = "2";
        cardTypes[2] = "3";
        cardTypes[3] = "4";
        cardTypes[4] = "5";
        cardTypes[5] = "6";
        cardTypes[6] = "7";
        cardTypes[7] = "8";
        cardTypes[8] = "9";
        cardTypes[9] = "10";
        cardTypes[10] = "Jack";
        cardTypes[11] = "Queen";
        cardTypes[12] = "King";
        for (int i = 0;i < handSize; i++)
        {
            cout << cardTypes[(hand[i].val - 1)] << " of " << printSuit(hand[i]) << endl;
        }
        cout << endl;
        cout << "Value of your cards: " << returnHandValue() << endl;
        cout << endl;
        delete[] cardTypes;
    }
    //Asks player to input bet btwn the betMinimum and the user's balance. After input validation, sets value to bet.
    void placeBet()
    {
        cout << "Enter how much you'd like to bet (Between $" << betMinimum << " and $" << balance << "): " << endl;
        cin >> bet;
        while (!cin || !(bet >= betMinimum && bet <= balance))
        {
            cout << "Enter how much you'd like to bet (Between $" << betMinimum << " and $" << balance << "): " << endl;
            cin.clear();
            cin.ignore();
            cin >> bet;
        }
    }

    //Returns value of the hand
    int returnHandValue()
    {
        aceCount = 0;
        handValue = 0;
        for (int i = 0;i < handSize; i++)
        {
            if (hand[i].val == 11 || hand[i].val == 12 || hand[i].val == 13)
            {
                handValue += 10;
            }
            else if (hand[i].val == 1)
            {
                aceCount++;
                handValue += 11;
            }
            else
            {
                handValue += hand[i].val;
            }
        }
        while (handValue > 21 && aceCount > 0)
        {
            aceCount--;
            handValue -= 10;
        }
        return handValue;
    }

    //Returns Bet
    int returnBet()
    {
        return bet;
    }

    //Returns Balance
    int returnBalance()
    {
        return balance;
    }

    //Returns Wins
    int returnWins()
    {
        return tallyWin;
    }

    //Adds one more card to user's hand
    void hit()
    {
        handSize++;
        card* newHand = new card[handSize];
        for (int i = 0; i < handSize - 1; i++)
        {
            newHand[i] = hand[i];
        }
        delete[] hand;
        hand = newHand;
        hand[handSize - 1] = deal();
    }

    //Asks player whether he wants to hit or stay
    bool getUserChoice()
    {
        char input;
        cout << "Would you like to hit or stay? ('h' or 's')" << endl;
        cin >> input;
        while ((input != 'h') && (input != 's'))
        {
            cout << "Please enter h or s" << endl;
            cin >> input;
        }
        if (input == 'h')
        {
            hit();
            cout << "Your Cards" << endl;
            cout << "----------" << endl;
            printCards();
            return true;
        }
        else
        {
            return false;
        }
        return false;
    }

    //Adds or removes amount of money for win. i will be 0 for lose, 1 for win, and 2 for blackjack
    void finalWin(int i)
    {
        if (i == 0)
        {
            balance -= bet;
        }
        else if (i == 1)
        {
            balance += bet;
            tallyWin++;
        }
        else if (i == 2)
        {
            balance += bet * 1.5;
            tallyWin++;
        }
    }

    //Resets hand if user wants to play again
    void resetHand()
    {
        delete[] hand;
        handSize = 2;
        hand = new card[handSize];
    }

    //Clears memory once game is completely over
    void clear()
    {
        delete[] hand;
        handSize = 0;
        hand = nullptr;
    }
};


//Dealer Class
class Dealer
{
private:
    vector<card> hand;
    int bet;
    int balance;
    int aceCount;
    int handValue;
public:
    //Default Constructor
    Dealer()
    {
        hand = {};
        bet = 0;
        balance = 100000;
        aceCount = 0;
        handValue = 0;
    }

    //Copy Constructor
    Dealer(const Dealer &dealer2)
    {
        hand = dealer2.hand;
        bet = dealer2.bet;
        balance = dealer2.balance;
        aceCount = dealer2.aceCount;
        handValue = dealer2.handValue;
    }

    //Sets dealer's initial hand (gives him 2 cards)
    void setHand()
    {
        for (int i = 0; i < 2; i++)
        {
            hand.push_back(deal());
        }
        hand.at(1).up = false;
    }

    //Sets player's bet to dealer's bet (amount he will gain if he wins or give back to the player if he loses)
    void setBet(int bet2)
    {
        bet = bet2;
    }

    //Takes in a card as a parameter card's suit 
    string printSuit(card topCard)
    {
        //Checks enum's suit value (0, 1, 2, or 3) and then returns the char version of suit so that we can easily display later
        switch (topCard.suit)
        {
        case 0:
            return "Hearts";
        case 1:
            return "Spades";
        case 2:
            return "Clubs";
        case 3:
            return "Diamonds";
        }
    }
    
    //Returns value of hand
    int returnHandValue()
    {
        aceCount = 0;
        handValue = 0;
        for (int i = 0;i < hand.size(); i++)
        {
            if (hand.at(i).val == 11 || hand.at(i).val == 12 || hand.at(i).val == 13)
            {
                handValue += 10;
            }
            else if (hand.at(i).val == 1)
            {
                aceCount++;
                handValue += 11;
            }
            else
            {
                handValue += hand.at(i).val;
            }
        }
        while (handValue > 21 && aceCount > 0)
        {
            aceCount--;
            handValue -= 10;
        }
        return handValue;
    }

    //Adds card if the hand is 16 or lower, or 17 with 1 ace in the hand
    bool addCard(bool choice)
    {
        if ((returnAnswer() == true) && (choice == true))
        {
            hand.push_back(deal());
            return true;
        }
        return false;
    }

    //Checks if the hand is 16 or lower, or is 17 with at least one ace
    bool returnAnswer()
    {
        if (returnHandValue() <= 16 || (returnHandValue() == 17 && aceCount == 1))
        {
            return true;
        }
        return false;
    }

    //Prints out all Cards except one face down hidden card 
    //If input is 1, then all Cards (including the face down card) are printed out since input will signify whether the player's turn is done
    //If the Player's turn is done then we can display all of the dealer's cards
    void printCards(int input = 0)
    {
        string* cardTypes = new string[14];
        cardTypes[0] = "Ace";
        cardTypes[1] = "2";
        cardTypes[2] = "3";
        cardTypes[3] = "4";
        cardTypes[4] = "5";
        cardTypes[5] = "6";
        cardTypes[6] = "7";
        cardTypes[7] = "8";
        cardTypes[8] = "9";
        cardTypes[9] = "10";
        cardTypes[10] = "Jack";
        cardTypes[11] = "Queen";
        cardTypes[12] = "King";
        cardTypes[13] = "Hidden Card";
        if (input == 0)
        {
            for (int i = 0; i < hand.size(); i++)
            {
                //If the card's face value is true then it will be displayed
                if ((hand[i].up))
                {
                    cout << cardTypes[(hand.at(i).val - 1)] << " of " << printSuit(hand.at(i)) << endl;
                }
                //Else if the card's face value is false then "Unknown Card" will be displayed
                else
                {
                    cout << cardTypes[13] << " ";
                }
            }
        }
        else
        {
            for (int i = 0;i < hand.size(); i++)
            {
                cout << cardTypes[(hand.at(i).val - 1)] << " of " << printSuit(hand.at(i)) << endl;
            }
            cout << endl;
            cout << "Value of dealer's cards: " << returnHandValue() << endl;
            cout << endl;
        }
        cout << endl;
        delete[] cardTypes;
    }

    //Updates the balance for dealer. If i is 0, the dealer won. If i is 1, the dealer lost.
    void updateBalance(int i)
    {
        if (i == 0)
        {
            balance += bet;
        }
        else if (i == 1)
        {
            balance -= bet;
        }
    }

    //Resets hand
    void resetHand()
    {
        hand.clear();
    }
};


//BlackJack Game Class
class BlackJack
{
private:
    Player player1;
    Dealer dealer1;
public:
    //Default Constructor
    BlackJack()
    {
    }
    //Another constructor that takes in a player and dealer
    BlackJack(Player player2, Dealer dealer2)
    {
        player1 = player2;
        dealer1 = dealer2;
    }

    //Player places initial bet and then displays player's and dealer's cards
    void setup()
    {
        player1.placeBet();
        dealer1.setBet(player1.returnBet());
        player1.setHand();
        cout << "Your Cards" << endl;
        cout << "----------" << endl;
        player1.printCards();
        dealer1.setHand();
        cout << "Dealer's Cards" << endl;
        cout << "--------------" << endl;
        dealer1.printCards();
    }

    //Runs through player's turn until he either stays or busts. Returns a bool value representing whether the user already lost/busted or not
    bool playerTurn()
    {
        bool choice = true;
        bool choice2 = true;
        while (choice)
        {
            if (player1.returnHandValue() < 21)
            {
                choice = player1.getUserChoice();
            }
            else if (player1.returnHandValue() > 21)
            {
                cout << "Bust. You have lost" << endl;
                choice = false;
                choice2 = false;
            }
            else if (player1.returnHandValue() == 21)
            {
                cout << "\nBlackJack!" << endl << endl;
                choice = false;
            }
        }
        cout << "Your Final Hand" << endl;
        cout << "---------------" << endl;
        player1.printCards();
        return choice2;
    }

    //Initiates dealer's turn and based on his hand value, his algorithim will make him hit or stay until his value doesn't fit the algorithim in the Dealer class
    void dealerTurn(bool choice2)
    {
        bool choice = true;
        cout << "Dealer's Hand" << endl;
        cout << "-------------" << endl;
        dealer1.printCards(1);
        while (choice)
        {
            choice = dealer1.addCard(choice2);
            if (choice == true)
            {
                cout << "Dealer's Hand" << endl;
                cout << "-------------" << endl;
                dealer1.printCards(1);
                cout << endl;
            }
        }
        cout << "Dealer's Final Hand" << endl;
        cout << "-------------------" << endl;
        dealer1.printCards(1);
        cout << endl;
    }

    //Checks both the dealer and the player's value of cards and sees who won in the end.
    //Respectively adds, subtracts, or pushes bets back if it was a win, lose or tie
    void checkWinner()
    {
        int i = 0;
        if ((dealer1.returnHandValue() == 21) && (player1.returnHandValue()==21))
        {
            cout << "Push. Bets returned" << endl;
            cout << "Your Balance : " << player1.returnBalance() << endl;
            cout << "Wins: " << player1.returnWins();
        }
        else if (player1.returnHandValue() > 21 || dealer1.returnHandValue() == 21)
        {
            i = 0;
            cout << "Dealer wins. You lose." << endl;
            player1.finalWin(i);
            dealer1.updateBalance(i);
            cout << "Your Balance : " << player1.returnBalance() << endl;
            cout << "Wins: " << player1.returnWins();
        }
        else if (player1.returnHandValue() == 21 && dealer1.returnHandValue() != 21)
        {
            i = 2;
            cout << "You win! Dealer loses." << endl;
            player1.finalWin(i);
            dealer1.updateBalance(i);
            cout << "Your Balance : " << player1.returnBalance() << endl;
            cout << "Wins: " << player1.returnWins();
        }
        else if (dealer1.returnHandValue() > 21)
        {
            i = 1;
            cout << "You win! Dealer loses." << endl;
            player1.finalWin(i);
            dealer1.updateBalance(i);
            cout << "Your Balance : " << player1.returnBalance() << endl;
            cout << "Wins: " << player1.returnWins();
        }
        else if (dealer1.returnHandValue() == player1.returnHandValue())
        {
            cout << "Push. Bets returned" << endl;
            cout << "Your Balance : " << player1.returnBalance() << endl;
            cout << "Wins: " << player1.returnWins();
        }
        else if ((dealer1.returnHandValue() > player1.returnHandValue()))
        {
            i = 0;
            cout << "Dealer wins. You lose." << endl;
            player1.finalWin(i);
            dealer1.updateBalance(i);
            cout << "Your Balance : " << player1.returnBalance() << endl;
            cout << "Wins: " << player1.returnWins();
        }
        else if ((dealer1.returnHandValue() < player1.returnHandValue()))
        {
            i = 1;
            cout << "You win! Dealer loses." << endl;
            player1.finalWin(i);
            dealer1.updateBalance(i);
            cout << "Your Balance : " << player1.returnBalance() << endl;
            cout << "Wins: " << player1.returnWins();
        }
    }

    //Function that resets hands if the game will repeat
    void resetHands()
    {
        player1.resetHand();
        dealer1.resetHand();
    }

    int returnPlayerBalance()
    {
        return player1.returnBalance();
    }

    //clears player1 memory once game is completely over
    void clear()
    {
        player1.clear();
    }
};

//Displays menu with options of rules or playing the game
void printMenu(int input)
{
    int rand = time(0);
    srand(rand);
    ifstream infile;
    infile.open("menu.txt");
    string text;
    int count = 0;
    if (input == 0)
    {
        if (infile.is_open())
        {
            while (getline(infile, text) && count !=4)
            {
                cout << text << '\n';
                count++;
            }
            infile.clear();
        }
        else
        {
            cout << "File could not be opened";
        }
    }
    else if(input == 1)
    {
        count = 4;
        infile.seekg(0);
        for (int i = 0; i < count + 1; i++)
        {
            getline(infile, text);
        }
        while (!infile.eof())
        {
            cout << text << '\n';
            getline(infile, text);
        }
        cout << endl;
    }
}

//Displays welcome banner at start of game
void displayBanner()
{
    cout << R"(.------..------..------..------..------..------..------..------..------.)" << endl;
    cout << R"(|B.--. ||L.--. ||A.--. ||C.--. ||K.--. ||J.--. ||A.--. ||C.--. ||K.--. |)" << endl;
    cout << R"(| :(): || :/\: || (\/) || :/\: || :/\: || :(): || (\/) || :/\: || :/\: |)" << endl;
    cout << R"(| ()() || (__) || :\/: || :\/: || :\/: || ()() || :\/: || :\/: || :\/: |)" << endl;
    cout << R"(| '--'B|| '--'L|| '--'A|| '--'C|| '--'K|| '--'J|| '--'A|| '--'C|| '--'K|)" << endl;
    cout << R"(`------'`------'`------'`------'`------'`------'`------'`------'`------')" << endl;

}

//Checks if name doesn't contain/isn't digits.
bool isValidName(string name)
{
    if (find_if(name.begin(), name.end(), ::isdigit) != name.end())
    {
        return false;
    }
    return true;
}

//Runs game and repeats until the player doesn't want to play anymore
void play()
{
    bool repeat=true;
    short int input = 0;
    string name;
    char ans = ' ';
    displayBanner();
    while (input != 2)
    {
        printMenu();
        cout << "Please enter 1 or 2" << endl;
        cin >> input;
        while (!cin || ((input != 1) && (input != 2)))
        {
            cout << "Please enter 1 or 2" << endl;
            cin.clear();
            cin.ignore();
            cin >> input;
        }
        printMenu(input);
        if (input == 1)
        {
            input = 0;
        }
    }
    cout << "Enter your name: ";
    cin >> name;
    while (isValidName(name) == false)
    {
        cout << "Player name must be alphabetical characters only!\n";
        cout << "Enter a valid name: ";
        cin >> name;
    }
    cout << name << ", would you like to deposit your own balance?" << endl;
    cout << "Please enter y or n" << endl;
    cin >> ans;
    while ((ans != 'y') && (ans != 'n'))
    {
        cout << "Please enter y or n" << endl;
        cin >> ans;
    }
    int balance = 1000;
    if (ans == 'y')
    {
        cout << "Enter the balance you would like to deposit (Must be greater than 5): ";
        cin >> balance;
        while (!(balance >= 5))
        {
            cout << "Enter the balance you would like to deposit (Must be greater than 5): ";
            cin >> balance;
            while (!cin)
            {
                cout << "Please enter an integer: " << endl;
                cin.clear();
                cin.ignore();
                cin >> input;
            }
        }
    }
    else
    {
        cout << "You will be given the default balance of $1000" << endl;
    }

    Player player1(name, balance);
    Dealer dealer1;
    BlackJack game(player1, dealer1);
    game.setup();
    bool choice = game.playerTurn();
    game.dealerTurn(choice);
    game.checkWinner();
    ans = ' ';
    while (repeat)
    {
        cout << "\nWould you like to play again? y or n" << endl;
        cin >> ans;
        while ((ans != 'y') && (ans != 'n'))
        {
            cout << "Please enter y or n" << endl;
            cin >> ans;
        }
        if (ans == 'n')
        {
            cout << "Thanks for playing!" << endl;
            repeat = false;
            game.clear();
            break;
        }
        int balance = game.returnPlayerBalance();
        if (balance <= 6)
        {
            cout << "Sorry you don't have enough money" << endl;
            cout << "Thanks for playing!" << endl;
            repeat = false;
            game.clear();
        }
        else if (ans == 'y')
        {
            game.resetHands();
            game.setup();
            choice = game.playerTurn();
            game.dealerTurn(choice);
            game.checkWinner();
        }
    }
}

int main()
{
    play();
}