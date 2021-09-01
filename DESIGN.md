In this document, we will be breaking down my program and explaining why I chose to design it the way I did.
First, we start with all our #include header's.
After we are using the namespace std for convenience sake and so that I don't need to declare std:: each time.
Now I decided to use an enum CardSuit to store the card suit's enum types. I decided on this because it would make it so much more convenient
to add a type cardSuit to my struct card, rather than a string everytime. Enum just allowed me shorten my code a bit and improved my code efficiency.
After, I created a struct card which stored an int card's value, a cardSuit suit, and a boolean up. I knew a struct would be really good here since a card has
many different and important members related to it. I knew that I would have to access the card's value and suit later on and having a struct would make this very convenient.
The boolean up would also allow me to know if the card needed to be face up or face down (for the dealer).
Next I declared my prototypes, just for good practice and just in case I needed it for an error.

Moving on to the bulk of the code, the card deal() function's purpose was to return a random card.
It would just choose a random value btwn 1-13 for the card's value and then 1-4 for the suit. I also defaulted the card's up value to true. I would change it to down when I needed to, later in the code.


Next, I created a Player class. I used a dynamically allocated card *hand array here instead of a vector just because I wanted to challenge myself in manually managing memory.
The player class would have a name, a dynamically allocated card *hand array, handSize, bet, balance, wins, handValue, aceCount, and betMinimum.
I added a few constructors, default for good practice, one that took in a name and balance (balance was defaulted to 1000 in case the player decided to not deposit their own balance), and a copy constructor.
Both this copy constructor and the Dealer copy constructor were implemented because I needed to use it in my BlackJack class.

The setHand() function would just set the beginning hand for the player using the deal() function. 

The printSuit() function would just return the suit of the parameter card.

printCards() would just display the current hand and the value of that hand. I used a dynamically allocated string array here to correspond with the card's value. With this, I could easily
use the card's value to print out the correct card we had and I used printSuit() to print its suit. Then I cleared the memory of that string array at the end.

placeBet() would set the user's bet to the data member int bet. I also added an input validation step here, so that the program would not crash if an integer wasn't given.
If the user didn't enter an integer or didn't enter an integer that was btwn the betMinimum and balance, then the program wouldn't continue and would continue to ask the user to enter a new bet.

returnHandValue() would loop through the player's hand and use the card's value (card's value is basically just the card e.g. ace, 1, 2, 3...King but represented with an integer 0,1,2,3...13) 
to add a certain amount to the data member handValue. I also created a variable called aceCount. If the card's value was 1 (meaning it is an ace), then I would add 1 to aceCount and add 11 to the handValue.
If the card's value was 11,12,13, that meant it was a king,queen, or jack and they all had the same value of 10 so I added 10 the handValue in these cases.
Else, I just added the actual card value integer to the handValue (since 2 is 2, 3 is 3...10 is 10 etc.). Lastly, I checked if the handValue was over 21, in these cases I used the while loop
        while (handValue > 21 && aceCount > 0)
        {
            aceCount--;
            handValue -= 10;
        }
    to make sure that an ace was worth 1 instead of 11 where it needed to be.
    
hit() would manually manage the memory of hand by creating a new array pointer, copying the old hand into this new array pointer, adding a new random card to this new array pointer with deal(), deleting the memory of the orginal
hand, and then copying the new array pointer into the empty hand. Basically, we are increasing the size of the old array and adding a new random card to the data member *hand through these steps.

getUserChoice() asks the player whether he wants to hit or stay and again uses input validation to make sure the program doesn't crash when the user doesn't input h or s. The program instead will just continue to ask
the user to keep enter h or s until this condition is satisfied. getUserChoice() also uses hit() if the user enters 'h' and also displays the player's updated hand using printCards() after hitting.

finalWin() takes in a int n which represent whether the player lost (0), won (1), or got blackjack (2). Recall from the "Rules", if the player wins by blackjack then we recieves 1.5 the times his bet.
This function also updates the data member wins, based on whether the user won, lost or blackjacked.

resetHand() deletes/clears the old memory taken up by hand, sets handSize to 0, and dynamically allocates 2 chunks of memory for the hand again. This function is used if the player would like to play again. 

clear() deletes/clears the old memory taken by hand, sets handSize to 0 and hand to a nullptr. This will be used when the player would not like to play anymore and the program ends.



Dealer Class
The Dealer class included a hand, bet, balance, aceCount, and handValue. I used a vector for hand here instead of a dynamically allocated array because I wanted to again challenge myself to use a different aspect of STL library.
I didn't want to just repeat code of the Player class and I also was curious to see which was more convenient.

I added a default constructor for good practice and a copy constructor. Both this copy constructor and the Player copy constructor were implemented because I needed to use it in my BlackJack class.

Most of the methods here are self-explanatory and similar to the Player's class. However, I adjusted many parts of it to use a vector instead of a dynamically allocated array.

returnAnswer() returns a boolean whether or not the dealer needs to hit, based on his hand's total value.

addCard() takes in a boolean and adds a card based on returnAnswer() and the parameter boolean given. It also returns a boolean. This will be explained further later

printCards() takes in an int which represents whether we should print out all the cards or keep one hidden. If input is 0, we will print out one card and the other will be "Unknown Card" and we won't display the value of the dealer's cards.
If it is not 0(aka the player's turn is done), then we will just print all cards and the value. We have hidden card at the end of the dynamic array and we clear the memory at the end.


BlackJack Class
This class has a Player and a Dealer. There is a constructor that takes in a player and a dealer and we set them to the data members of the blackjack class.

setup() is where Player places initial bet and then displays player's and dealer's cards.

playerTurn() runs through player's turn until he either stays or busts. Returns a bool value representing whether the user  has already lost/busted or not. 
Remember addCard() in Dealer took in a boolean value as a parameter. This boolean value is the same boolean value returned by playerTurn and represents whether the player had already won or lost.
Thus, addCard() would only add a card to the Dealer's hand only if the player had not lost yet, and his hand still fit the algorithim (hand is still > 16 or soft 17).

dealerTurn() initiates dealer's turn and based on his hand value, his algorithim will make him hit or stay until his value doesn't fit the algorithim in the Dealer class

checkWinner() checks both the dealer and the player's value of cards and sees who won in the end. Respectively adds, subtracts, or pushes bets back if it was a win, lose or tie.
There are many if statements placed here in a certain order to make sure every situation is checked in that order.

printMenu() takes in an int input and based on this input uses fstream, specifically ifstream, to read into a file and print out the menu or print out the rules.
If the input is 0 then we print out the menu, else if the input is 1 (meaning the player chose Rules when the menu showed up) then we set count to 4 and use getline and a for loop based on count to start reading the file only
from the count line. 

isValidName() checks if name doesn't contain/isn't digits. This is an input validation function we use later.

play() runs game and repeats until the player doesn't want to play anymore.
A banner is displayed.
First we have a while condition, which continues to display the menu until the player chooses to play. (The player can click Rules and then the menu will again show up until you decided to enter 2 which signifies you want to play)
There is input validation here as well again to make sure the user inputs 1 or 2.
Then we ask for a name, make sure it's valid using isValidName().
Then we ask if you would like to deposit a balance. We use input validation to make sure it is a y or n that is inputed.
If the user enters y, then we will ask him for a balance to enter.
Then we use input validation by using a while loop to make sure the player enters a balance that is above $5 (the betMinimum). 
We use input validation again to make sure the user enters an integer.
If the user says n then we will just display that he/she will be given a default balance of 1000.

Now we create the player using the balance and name.
Then we create the dealer and then the blackjack game with both the player and dealer as parameters.
We use .setup() to setup the game and then set a boolean choice to the .playerTurn(). This will run the player's turn and also set the boolean value to the boolean variable, which will signify if the player lost already
or has not lost yet.
Now we use dealerTurn() using that boolean variable as a parameter. This will make sure that the dealer will hit/stay as necessary based on his handValue and based on this boolean variable.
After running both turns, we will checkWinner() which will check the winner and auto update the balance and display the appropriate messages. 
Now we will create a while loop that will break only if the player has no money or enters n when prompted if he would like to play again.
There is input validation here again.
If the player has money and would like to play again, then the game will run again.
