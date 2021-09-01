Hi! My name is Krishna Konda.
Welcome to my BlackJackGame. In this game, you will be playing blackjack against one opponent, the dealer (the computer in this case).
First and foremost, to run this project, just enter "make blackjackgame" and then enter "./blackjackgame" like many other programs.
Once you run this, you will be greeted with a welcome banner and a menu with 2 options, Rules and Play.
If you've never played blackjack or would like to refresh your memory on the game, I encourage you to type in 1 and read the rules before you play.
After this, you will greeted with the menu again where you can choose between play and rules again. Enter 2 this time if you'd like to play.
The program will ask you to enter your name. The game won't proceed unless it's a valid name. 
After this step, you can either deposit your own balance for gambling (any amount you'd like) or you can enter n and start with a default balance of $1000, provided by the casino.
Now you may enter how much you'd like to bet on your next game. Enter how much you'd like to bet. The game won't proceed unless it is a value between $5 and your current balance.
Once you've completed this step, both your cards and the dealer's cards will be displayed. Just like in a real game of blackjack, you will not be able to see one of the dealer's cards.
With this information presented to you, you will have a choice to either hit or stay. The program won't proceed until you enter h or s.
If you hit, the program will display your updated hand and the updated value of this hand. You will be given the choice to hit or stay again, unless you have busted (your hand value went over 21).
If at any time (including your beginning hand), your hand value is 21 or blackjack, you will not be given the choice to hit or stay and the program will proceed immediately to the dealer's turn.
Assuming you have busted, chosen stay, or gotten blackjack, the program will proceed to the dealer's turn.
The dealer's turn is based on a certain algorithim that is also used in casinos. This information is inside the "Rules" from the Menu before.
For clarity, the dealer's rules for hitting is that if his hand is less than or equal to 16 or he has a "soft 17" (an ace and a 6), then he must take a hit.
If the dealer's hand is 17 or higher without an ace, then the dealer must stand. Thus, based on these rules, the dealer will continue to hit or stay until he satisfies these rules.
Once the dealer's turn is over, many things will be displayed.
First your final hand and the final value of your hand will be displayed. Next, the dealer's original hand and value will be displayed.
After this, if the dealer hit multiple or even one time, all of the dealer's hands throughout this turn will be displayed (e.g. he hit once, his hand and value will be displayed, hits again, that new updated hand displayed etc.)
Now, the dealer's final hand and final value of his hand will be displayed.
Lastly, the result of your game will be displayed based on whoever won/if you guys tied.
Then, your balance will be updated (after you won or lost or tied) and will be displayed, as well your total wins throughout this session will be updated and displayed.
Now the program will ask you if you'd like to play again. The program won't proceed unless you enter y or n.
If you type y, the program will repeat and start with asking for a new bet and then showing yours and the dealer's new hands etc.
If you type n, the program will thank you for playing and end. Your total wins and balance will update everytime you win/lose/tie as long as you keep playing.
If you type y but you are out of balance, then the program will let you know that you are out of balance and will end the game.
