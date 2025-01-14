#include <iostream>
#include <vector>
#include <string>
#include <random>
#include <algorithm>

using namespace std;

typedef vector<string> Deck;

// Function to generate a random number for shuffling
int random_num() {
    static random_device rd;
    static mt19937 gen(rd());
    uniform_int_distribution<int> distrib(0, 51);
    return distrib(gen);
}

// Function to get the card value
int card_val(char card) {
    if (card == 'A') return 11;
    if (card == 'J' || card == 'Q' || card == 'K' || card == '1') return 10;
    return card - '0';
}

// Generate a single suit
Deck bland_suit() {
    Deck result(13);
    for (int i = 1; i <= 13; i++) {
        if (i == 1) result[i - 1] = "A";
        else if (i == 11) result[i - 1] = "J";
        else if (i == 12) result[i - 1] = "Q";
        else if (i == 13) result[i - 1] = "K";
        else result[i - 1] = to_string(i);
    }
    return result;
}

// Shuffle the deck
void shuffle(Deck& unshuffled) {
    for (int i = 0; i < unshuffled.size(); i++) {
        swap(unshuffled[i], unshuffled[random_num()]);
    }
}

// Generate a full deck
Deck unshuffled_deck() {
    Deck result(52);
    Deck suit = bland_suit();
    for (int i = 0; i < 13; i++) result[i] = "S" + suit[i];
    for (int i = 13; i < 26; i++) result[i] = "D" + suit[i % 13];
    for (int i = 26; i < 39; i++) result[i] = "H" + suit[i % 13];
    for (int i = 39; i < 52; i++) result[i] = "C" + suit[i % 13];
    return result;
}

// Main betting sequence
void bet_sequence(Deck& deck, int& active_pos, int& bet, int& balance) {
    Deck player_cards = {deck[active_pos], deck[active_pos + 1]};
    Deck dealer_cards = {deck[active_pos + 2]};
    active_pos += 3;

    int player_sum = card_val(player_cards[0][1]) + card_val(player_cards[1][1]);
    int player_aces = (player_cards[0][1] == 'A') + (player_cards[1][1] == 'A');
    int dealer_sum = card_val(dealer_cards[0][1]);
    int dealer_aces = (dealer_cards[0][1] == 'A');

    // Dealer draws cards
    while (dealer_sum < 17) {
        dealer_cards.push_back(deck[active_pos++]);
        if (dealer_cards.back()[1] == 'A') dealer_aces++;
        dealer_sum += card_val(dealer_cards.back()[1]);
        while (dealer_sum > 21 and dealer_aces > 0) {
            dealer_sum -= 10;
            dealer_aces--;
        }
    }
    bool dealer_busted = (dealer_sum > 21);

    cout << "Dealer's cards: **";
    for (int i = 1; i < dealer_cards.size(); i++) {
        cout << ' ' << dealer_cards[i];
    }
    cout << endl;

    // Player's turn
    bool player_stands = false, player_busted = false;
    while (not player_stands) {
        cout << "Your cards: ";
        for (const auto& card : player_cards) cout << card << " ";
        cout << "\nCurrent total: " << player_sum << "\n";

        string action;
        cout << "Choose action (Hit/Stand/Double): ";
        cin >> action;

        if (action == "Hit" or action == "Double") {
            if (action == "Double") {
                balance -= bet;
                bet *= 2;
            }

            player_cards.push_back(deck[active_pos++]);
            if (player_cards.back()[1] == 'A') player_aces++;
            player_sum += card_val(player_cards.back()[1]);

            while (player_sum > 21 and player_aces > 0) {
                player_sum -= 10;
                player_aces--;
            }
        } else if (action == "Stand") {
            player_stands = true;
        } else {
            cout << "Invalid action. Try again.\n";
        }

        if (player_sum > 21) {
            player_busted = true;
            player_stands = true;
        }
    }

    cout << "Final Player Total: " << player_sum << "\n";
    cout << "Dealer's cards: ";
    for (const auto& card : dealer_cards) cout << card << " ";
    cout << "\nDealer Total: " << dealer_sum << "\n";

    // Determine the result
    if (player_busted) {
        cout << "You busted. You lose!\n";
    } else if (dealer_busted or player_sum > dealer_sum) {
        balance += bet * 1.5;
        cout << "You win! Net earnings: " << bet*0.5 << "\n";
    } else if (player_sum == dealer_sum) {
        balance += bet;
        cout << "It's a draw. Your bet is returned.\n";
    } else {
        cout << "You lose!\n";
    }
}

int main() {
    int balance = 500;
    int bet;
    Deck main_deck = unshuffled_deck();
    shuffle(main_deck);

    int current_pos = 0;
    cout << "Insert bet: ";
    while (cin >> bet && balance >= bet) {
        cout << "Your bet: " << bet << "€\n";
        cout << "Your bet: " << bet << "€\n";
        balance -= bet;

        bet_sequence(main_deck, current_pos, bet, balance);

        cout << "New balance: " << balance << "€\n";
        if (balance <= 0) {
            cout << "You ran out of balance. Game over!\n";
            break;
        }
        cout << "Insert bet: ";
    }
    return 0;
}