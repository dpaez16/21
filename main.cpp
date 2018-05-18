#include <iostream>
#include <vector>
#include <algorithm>
#include <sstream>
#include <limits>
#include <ctime>
#include <stdlib.h>
#include <utility>
#include <string>

using namespace std;


int RNG(int n) {
        srand(time(NULL));
        return (int)(rand() % n);
}

void clearScreen() {
   for (int i = 0; i < 75; i++)
      cout << endl;
}

void printHand(vector<pair<int, string> > &deck) {
   cout << "Cards You Hit: ";
   if (deck.empty()) {
      cout << endl;
      cout << endl;
   } else {
   for (size_t i = 0; i < deck.size(); i++)
      cout << "[" << deck[i].second << "] ";
   cout << endl;
   cout << endl;
   }
}

void initCards (vector<pair<int, string> > &deck) {
   for (int x = 0; x < 4; x++) {
      for (int i = 0; i < 13; i++) {
         if (i == 0)
            deck.push_back(pair<int, string>(1, "A"));
         else if (i == 1)
            deck.push_back(pair<int, string>(2, "2"));
         else if (i == 2)
            deck.push_back(pair<int, string>(3, "3"));
         else if (i == 3)
            deck.push_back(pair<int, string>(4, "4"));
         else if (i == 4)
            deck.push_back(pair<int, string>(5, "5"));
         else if (i == 5)
            deck.push_back(pair<int, string>(6, "6"));
         else if (i == 6)
            deck.push_back(pair<int, string>(7, "7"));
         else if (i == 7)
            deck.push_back(pair<int, string>(8, "8"));
         else if (i == 8)
            deck.push_back(pair<int, string>(9, "9"));
         else if (i == 9)
            deck.push_back(pair<int, string>(10, "10"));
         else if (i == 10)
            deck.push_back(pair<int, string>(10, "J"));
         else if (i == 11)
            deck.push_back(pair<int, string>(10, "Q"));
         else
            deck.push_back(pair<int, string>(10, "K"));
      }
   }

   int numShuffles = RNG(5) + 1;
   for (int i = 0; i < numShuffles; i++)
      random_shuffle(deck.begin(), deck.end());

}

bool choose() {

   bool choice;
   cout << "Enter 1 or 0 (Yes/No): ";
   while (!(std::cin >> choice)) {
      std::cin.clear();
      std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
   }
   cout << endl;

   return choice;

}

bool chooseLowOrHigh(int s, vector<pair<int, string> > &hand) {

   clearScreen();

   cout << "Ace Low or High?" << endl;

   cout << "Score: " << s << endl;
   cout << endl;

   printHand(hand);

   bool choice;
   cout << "Enter 1 or 0 (Low/High): ";
   while (!(std::cin >> choice)) {
      std::cin.clear();
      std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
   }
   cout << endl;

   clearScreen();

   return choice;

}

void hitMe(int & score, vector<pair<int, string> > &cards, vector<pair<int, string> > &endGameDeck) {
   bool low;
   int currCard = cards[cards.size() - 1].first;

   if (currCard == 1) {
      low = chooseLowOrHigh(score, endGameDeck);

      if (low) {
         score += currCard;
         endGameDeck.push_back(pair<int, string>(1, "A"));
      } else {
         score += 11;
         endGameDeck.push_back(pair<int, string>(11, "A"));
      }
      cards.pop_back();
   } else {
      score += currCard;
      string face = cards[cards.size() - 1].second;
      cards.pop_back();
      endGameDeck.push_back(pair<int, string>(currCard, face));
   }
}

void hitFirst2(int & score, vector<pair<int, string> > &cards, vector<pair<int, string> > &endGameDeck) {

   int firstCard = cards[cards.size() - 1].first;
   int secondCard = cards[cards.size() - 2].first;

   if (firstCard == 1 && secondCard != 1)
      swap(cards[cards.size() - 1], cards[cards.size() - 2]);

   hitMe(score, cards, endGameDeck);
   hitMe(score, cards, endGameDeck);

}

void resultOfGame(int s) {
   clearScreen();
   if (s == 21)
      cout << "You win! :D" << endl;
   else
      cout << "You lose! :(" << endl;

   cout << "Score: " << s << endl;

   cout << endl;

}

int main() {

   bool doneWithGame = false;
   int score = 0;
   int numGames = 0;

   vector<pair<int, string> > cards;
   vector<pair<int, string> > endGameDeck;

   while (!doneWithGame) {

      clearScreen();
      endGameDeck.clear();

      score = 0;
      if (numGames % 3 == 0) {
         cards.clear();
         initCards(cards);
      }

      hitFirst2(score, cards, endGameDeck);


      while (score < 21) {

         cout << "Hit or Stand?" << endl;
         cout << "Score: " << score << endl;
         cout << endl;

         printHand(endGameDeck);

         bool hit = choose();

         if (hit)
            hitMe(score, cards, endGameDeck);
         else
            break;

         clearScreen();
         numGames++;

      }//After this point, either player won or lost

      resultOfGame(score);
      printHand(endGameDeck);

      cout << "Play Again?" << endl;
      cout << endl;

      doneWithGame = !choose();

   }//Game session over

   clearScreen();

   return 0;
}