#include <iostream>
#include <ctime>
#include <cstdlib>
#include <windows.h>
#include <conio.h>
#include <fstream>
using namespace std;
const int BLACK = 0;
const int BLUE = 1;
const int GREEN = 2;
const int CYAN = 3;
const int RED = 4;
const int MAGENTA = 5;
const int YELLOW = 6;
const int WHITE = 7;
int turn = 0;
int printer[50][2];
int topColour = 99;
string cardLines[15][5] = {
    {" ------- ", " -     - ", " -  0  - ", " -     - ", " ------- "},
    {" ------- ", " -     - ", " -  1  - ", " -     - ", " ------- "},
    {" ------- ", " -     - ", " -  2  - ", " -     - ", " ------- "},
    {" ------- ", " -     - ", " -  3  - ", " -     - ", " ------- "},
    {" ------- ", " -     - ", " -  4  - ", " -     - ", " ------- "},
    {" ------- ", " -     - ", " -  5  - ", " -     - ", " ------- "},
    {" ------- ", " -     - ", " -  6  - ", " -     - ", " ------- "},
    {" ------- ", " -     - ", " -  7  - ", " -     - ", " ------- "},
    {" ------- ", " -     - ", " -  8  - ", " -     - ", " ------- "},
    {" ------- ", " -     - ", " -  9  - ", " -     - ", " ------- "},
    {" --------- ", " -       - ", " - SKIP  - ", " -       - ", " --------- "},
    {" --------- ", " -       - ", " -REVERSE- ", " -       - ", " --------- "},
    {" -------- ", " -  +2  - ", " - WILD - ", " - CARD - ", " -------- "},
    {" -------- ", " -      - ", " - WILD - ", " -      - ", " -------- "},
    {" -------- ", " -  +4  - ", " - WILD - ", " - CARD - ", " -------- "},
};

string cardLiness[5] = {
    " -------- ",
    " -      - ",
    " -  UNO - ",
    " -      - ",
    " -------- "};

bool wild_called_allowed(int perform);
void clear_file();
void saveLoadGameResult(int, int);
void penalty(int player[2][8][15], int all_card[8][15], int bari);
bool callUno(int player[2][8][15], int call_kisna_ki);
void playTurn();
void wild_4(int player[2][8][15], int deck[8][15]);
void table(int player[2][8][15], int);
void handleSpecialCard(int perform);
void draw_card(int deck[][15], int player[2][8][15], int &counter);
void printer_value();
void player_cards(int player[2][8][15], int &);
void setColor(int textColor, int bgColor);
void Welome_Plus_Start();
int value_checker(int player[2][8][15], int);
void clearScreen();
void initializeDeck(int deck[][15]);
void shuffleDeck(int deck[8][15]);
void value_giving(int player[2][8][15]);
void dealCards(int player[2][8][15], int cards[8][15]);
void game(int deck[8][15], int player[2][8][15]);
void saved_results();
void PrintBoard(int);
bool isValidPlay(int, int);
void UpdateDiscardPile(int &, int, int[][15]);
void wild_2(int player[2][8][15], int all_card[8][15]);
void intial_again(int deck[][15], int player[2][8][15]);

int main()
{
    srand(time(0));
    int deck[8][15], player[2][8][15];
    // deck is being initialized
    initializeDeck(deck);
    // it is a secondary shuffle
    shuffleDeck(deck);
    // welcome message
    Welome_Plus_Start();
    // intizing all value card here
    value_giving(player);
    // dealing 7 cards to all players
    dealCards(player, deck);
    // here to game is being played
    game(deck, player);
    return 0;
}

void game(int deck[8][15], int player[2][8][15])
{
    setColor(WHITE, BLACK);
    bool draw = 0;
    int perform, card, player_1_wins = 0, player_2_wins = 0;
    int want_to_play;
    char again = 'y';
    string wild_colour_show = "    ";
    int wild_called = 0;
    while (again == 'y' || again == 'Y')
    {
        cout << "1. Start the game  " << endl
             << "2. Results " << endl
             << "3. Exit" << endl;
        cout << "Enter the option (1/2/3) : ";
        cin >> want_to_play;
        // validation
        while ((want_to_play != 1 && want_to_play != 2 && want_to_play != 3) || cin.fail())
        {
            cin.clear(), cin.ignore(100, '\n');
            cout << " ---- Inavlid Entry ---- " << endl;
            cout << "Enter the option (1/2/3) : ";
            cin >> want_to_play;
        }
        clearScreen();
        int topCard = 99, first = 0;
        int counter = 0;
        if (want_to_play == 1)
        {
            do
            {
                // printing the game on screen
                table(player, (turn) ? 0 : 1);
                UpdateDiscardPile(topCard, first, deck);
                // if wild_carded was called this would work then
                if (wild_called && first != 0)
                {
                    int colour;
                    if (topColour == 0 || topColour == 1)
                        colour = 1;
                    if (topColour == 2 || topColour == 3)
                        colour = 2;
                    if (topColour == 4 || topColour == 5)
                        colour = 4;
                    if (topColour == 6 || topColour == 7)
                        colour = 6;
                    cout << "\n            ";
                    setColor(colour, colour);
                    cout << wild_colour_show;
                    setColor(WHITE, BLACK);
                    cout << "\n            ^ NEXT COLOUR " << endl;
                }
                cout << endl
                     << "                  Player " << turn + 1 << " Turn" << endl
                     << endl;
                printer_value();
                player_cards(player, counter);
            not_possible:
            passed:
                // menu for the user want to do
                cout << "\n0. Draw Card " << endl
                     << "1. Play Card " << endl
                     << "E. Exit " << endl;
                char card;
                cout << "Select an option (0/1/E) : ";
                cin >> card;
                while ((card != '0' && card != '1' && card != 'E') || cin.fail()){
                    cin.clear(), cin.ignore(100, '\n');
                    cout << " ---- Inavlid Entry ---- " << endl;
                    cout << "Enter the option (0/1/E) : ";
                    cin >> card;
                }
                // for exxit this would activate
                if (card == 'E'){
                    clearScreen();
                    cout << "Player " << turn + 1 << " left the game " << endl;
                    int kon_jeeta = (turn) ? 0 : 1;
                    cout << "Congratulations!" << endl;
                    cout << "Player " << kon_jeeta + 1 << " wins " << endl;
                    cout << "Press Enter to continue ";
                    cin.ignore();
                    cin.ignore();
                    clearScreen();
                    // updating the scores of players
                    (kon_jeeta) ? player_2_wins++ : player_1_wins++;
                    if (kon_jeeta)
                    {
                        player_2_wins++;
                        saveLoadGameResult(player_1_wins, player_2_wins);
                    }
                    else
                    {
                        player_1_wins++;
                        saveLoadGameResult(player_1_wins, player_2_wins);
                    }
                    break;
                }
                if (card == '0')
                {
                    first++;
                    clearScreen();
                    table(player, (turn) ? 0 : 1);
                    UpdateDiscardPile(topCard, first, deck);
                    // if wind was called
                    if (wild_called && first != 0)
                    {
                        int colour;
                        if (topColour == 0 || topColour == 1)
                            colour = 1;
                        if (topColour == 2 || topColour == 3)
                            colour = 2;
                        if (topColour == 4 || topColour == 5)
                            colour = 4;
                        if (topColour == 6 || topColour == 7)
                            colour = 6;
                        cout << "\n            ";
                        setColor(colour, colour);
                        cout << wild_colour_show;
                        setColor(WHITE, BLACK);
                        cout << "\n            ^ NEXT COLOUR " << endl;
                    }

                    cout << "                  Player " << turn + 1 << " Turn" << endl
                         << endl;
                    draw_card(deck, player, counter);
                    cout << endl;
                    draw = true;
                    // menu for calrd drawing
                    cout << "Card is Drawn See your Card " << endl; //
                    cout << "Do u want to play a card Enter \n1. Play a Card \n2. Pass the Turn\n";
                    cout << "Enter the option (1/2) : ";
                    int pass;
                    cin >> pass;
                    while ((pass != 1 && pass != 2) || cin.fail()){
                        cin.clear(), cin.ignore(100, '\n');
                        cout << " ---- Inavlid Entry ---- " << endl;
                        cout << "Enter the option (1/2) : ";
                        cin >> pass;
                    }
                    if (pass == 1){
                        goto play;
                    }
                    else
                    {
                        // if turn is passed after the play]
                        playTurn();
                    }
                }
                if (card == '1')
                {
                play:
                draw_it:
                    // tkaing the input from user for the card placement
                    cout << "Enter the card placement index (1,2,3,4,,,n) : ";
                    cin >> perform;
                    while ((perform <= 0 || perform >= 31) || (printer[perform - 1][0] == 99) || cin.fail())
                    {
                        cin.clear(), cin.ignore(100, '\n');
                        cout << "---- Invalid Entry ----" << endl;
                        cout << "Enter the card placement index (1,2,3,4,,,n) : ";
                        cin >> perform;
                    }

                    if (isValidPlay(perform - 1, topCard) && wild_called == 0)
                    {
                        topColour = printer[perform - 1][0], topCard = printer[perform - 1][1];
                    }
                    else if (wild_called && wild_called_allowed(perform))
                    {
                        topColour = printer[perform - 1][0], topCard = printer[perform - 1][1];
                        wild_called = 0;
                    }
                    else
                    {
                        cout << "---- INVALID ----" << endl;
                        cout << "Move can't be Played" << endl;
                        if (!draw)
                            goto not_possible;
                        else
                            goto draw_it;
                    }
                    // if the card performed was greater then card index 9 then it was a special card
                    if (printer[perform - 1][1] > 9)
                    {
                        if (printer[perform - 1][1] == 10 || printer[perform - 1][1] == 11)
                            handleSpecialCard(perform - 1);
                        if (printer[perform - 1][1] > 11)
                        {
                            if (printer[perform - 1][1] == 12)
                                wild_2(player, deck);
                            if (printer[perform - 1][1] == 13)
                                wild_called = 1;
                            if (printer[perform - 1][1] == 14)
                            {
                                wild_4(player, deck);
                                wild_called = 1;
                            }
                        }
                        /// working for removing it prom players array
                        if (printer[perform - 1][1] == 10 || printer[perform - 1][1] == 11)
                        {
                            player[(turn) ? 0 : 1][printer[perform - 1][0]][printer[perform - 1][1]] = 99;
                            printer[perform - 1][0] = 99, printer[perform - 1][0] = 99;
                        }
                        else
                        {
                            player[turn][printer[perform - 1][0]][printer[perform - 1][1]] = 99;
                            printer[perform - 1][0] = 99, printer[perform - 1][0] = 99;
                        }
                    }
                    else
                    {
                        // if the card was simple upto 0-9 then just simpaly put it in center
                        player[turn][printer[perform - 1][0]][printer[perform - 1][1]] = 99;
                        printer[perform - 1][0] = 99, printer[perform - 1][0] = 99;
                    }
                    if (printer[perform - 1][1] == 10 || printer[perform - 1][1] == 11)
                    {
                        /// check win
                        if (value_checker(player, (turn) ? 0 : 1) == 0)
                        {
                            int kon_jeeta = (turn) ? 0 : 1;
                            clearScreen();
                            cout << "Congratulations!" << endl;
                            cout << "Player " << kon_jeeta + 1 << " wins " << endl;
                            cin.ignore();
                            (kon_jeeta) ? player_2_wins++ : player_1_wins++;
                            if (kon_jeeta)
                            {
                                player_2_wins++;
                                saveLoadGameResult(player_1_wins, player_2_wins);
                            }
                            else
                            {
                                player_1_wins++;
                                saveLoadGameResult(player_1_wins, player_2_wins);
                            }
                            break;
                        }
                    }
                    else
                    {
                        // checking win condition
                        if (value_checker(player, turn) == 0)
                        {
                            clearScreen();
                            cout << "Congratulations!" << endl;
                            cout << "Player " << turn + 1 << " wins " << endl
                                 << endl;
                            cin.ignore();
                            if (turn)
                            {
                                player_2_wins++;
                                saveLoadGameResult(player_1_wins, player_2_wins);
                            }
                            else
                            {
                                player_1_wins++;
                                saveLoadGameResult(player_1_wins, player_2_wins);
                            }
                            break;
                        }
                    }
                    int call;
                    // uno is applicalbe are not it checks
                    if (printer[perform - 1][1] == 10 || printer[perform - 1][1] == 11)
                    {
                        if (callUno(player, (turn) ? 0 : 1))
                        {
                            cout << "Do u want to call for Uno (1/0) : ";
                            cin >> call;
                            while ((call != 1 && call != 0) || cin.fail())
                            {
                                cin.clear(), cin.ignore(100, '\n');
                                cout << "Invalid Entry" << endl;
                                cout << "Do u want to call for Uno (1/0) : ";
                                cin >> call;
                            }
                            if (!call)
                            {
                                penalty(player, deck, (turn) ? 0 : 1);
                                cout << "Got a Penalty of +2 cards for not calling uno" << endl;
                                cin.ignore();
                            }
                        }
                    }
                    else
                    {
                        if (callUno(player, turn))
                        {
                            cout << "Do u want to call for Uno (1/0) : ";
                            cin >> call;
                            while ((call != 1 && call != 0) || cin.fail())
                            {
                                cin.clear(), cin.ignore(100, '\n');
                                cout << "Invalid Entry" << endl;
                                cout << "Do u want to call for Uno (1/0) : ";
                                cin >> call;
                            }
                            if (!call)
                            {
                                penalty(player, deck, turn);
                                cout << "Got a Penalty of +2 cards for not calling uno" << endl;
                                cin.ignore();
                            }
                        }
                    }
                    if (!(printer[perform - 1][1] == 12))
                        playTurn();
                    if (printer[perform - 1][1] == 14 || printer[perform - 1][1] == 13)
                    {
                        setColor(BLACK, BLUE);
                        cout << "(0/1). BLUE";
                        setColor(WHITE, BLACK);
                        cout << "  ";
                        setColor(BLACK, GREEN);
                        cout << "(2/3). GREEN";
                        setColor(WHITE, BLACK);
                        cout << "  ";
                        setColor(BLACK, RED);
                        cout << "(4/5). RED";
                        setColor(WHITE, BLACK);
                        cout << "  ";
                        setColor(BLACK, YELLOW);
                        cout << "(6/7). YELLOW" << endl;
                        setColor(WHITE, BLACK);
                        cout << "  ";
                        cout << "Enter the TOP COLOUR : ";
                        cin >> topColour;
                        while (topColour < 0 || topColour > 7 || cin.fail())
                        {
                            cin.clear(), cin.ignore(100, '\n');
                            cout << "Invalid Entry " << endl;
                            cout << "Enter the TOP COLOUR for next player : ";
                            cin >> topColour;
                        }
                    }
                }

                cin.ignore();
                counter = 0;
                clearScreen();
                first++;
                perform = 99;
                draw = false;

            } while (1);
        }
        // if player want to check the history
        else if (want_to_play == 2)
        {
            cout << endl
                 << "---------------" << endl;
            cout << "Results History " << endl;
            saved_results();
            cout << "---------------" << endl
                 << endl;
        }
        // if player want to exit eh terminal
        else
        {
            cout << endl;
            setColor(BLUE, WHITE);
            cout << "THANK FOR PLAYING" << endl;
            setColor(WHITE, BLACK);
            break;
        }
    }
}

// chcecking whether the card is valid to use or not
bool isValidPlay(int perform, int topCard)
{
    // frst ot cases are wild so it allowed
    if (printer[perform][1] == 13 || printer[perform][1] == 14)
        return 1;
    if (printer[perform][1] == topCard)
        return 1;
    // from here they are beig checked acc to ther index
    if ((topColour == 0 || topColour == 1) && (printer[perform][0] == 0 || printer[perform][0] == 1))
        return 1;
    if ((topColour == 2 || topColour == 3) && (printer[perform][0] == 2 || printer[perform][0] == 3))
        return 1;
    if ((topColour == 4 || topColour == 5) && (printer[perform][0] == 4 || printer[perform][0] == 5))
        return 1;
    if ((topColour == 6 || topColour == 7) && (printer[perform][0] == 6 || printer[perform][0] == 7))
        return 1;
    if (topCard == 14 || topCard == 13)
        return 1;
    return 0;
}
// cards are bign drawn for the user again and angaina s it is called
void draw_card(int deck[][15], int player[2][8][15], int &counter){
    int placer_colour = rand() % 8;
    int placer_catagory = rand() % 15;
    int checked = 0;
    while (deck[placer_colour][placer_catagory] == 99){
        placer_colour = rand() % 8;
        placer_catagory = rand() % 15;
        checked++;
        if (checked == 120)
        {
            // once it calls this and therir are no card this is called
            intial_again(deck, player);
            shuffleDeck(deck);
        }
    }
    // taking cards from deck to the current player
    player[turn][placer_colour][placer_catagory] = deck[placer_colour][placer_catagory];
    deck[placer_colour][placer_catagory] = 99;
    counter = 0;
    player_cards(player, counter);
}

// initalizing the printer_values as zero for no future problem
void printer_value()
{
    for (int i = 0; i < 50; i++)
    {
        printer[i][0] = 99;
        printer[i][1] = 99;
    }
}

// taking player cards from printer to print it on the screen
void player_cards(int player[2][8][15], int &counter)
{
    for (int i = 0; i < 8; i++)
    {
        for (int j = 0; j < 15; j++)
        {
            if (player[turn][i][j] != 99)
            {
                printer[counter][0] = i;
                printer[counter][1] = j;
                counter++;
            }
        }
    }
    // this called for printing
    PrintBoard(counter);
}

// its printng the board according to my need and current situaltion
void PrintBoard(int counter)
{
    const int max_per_row = 15; // Maximum cards per row
    int cards = 0;
    int card = 0; // Start with the first card
    while (counter > 0)
    {
        // Determine how many cards to display in the current row
        int cards_in_row = (counter > max_per_row) ? max_per_row : counter;

        // Print each line of the cards
        for (int line = 0; line < 5; ++line)
        {
            for (int col = 0; col < cards_in_row; ++col)
            {
                int current_card = card + col; // Use card + col for each specific card
                
                int colour;
                if (printer[current_card][0] == 0 || printer[current_card][0] == 1)
                    colour = 1;
                else if (printer[current_card][0] == 2 || printer[current_card][0] == 3)
                    colour = 2;
                else if (printer[current_card][0] == 4 || printer[current_card][0] == 5)
                    colour = 4;
                else if (printer[current_card][0] == 6 || printer[current_card][0] == 7)
                    colour = 6;

                if (printer[current_card][1] != 14 && printer[current_card][1] != 13) // Top, empty, and bottom lines
                {
                    setColor(WHITE, colour); // Set card color
                    cout << cardLines[printer[current_card][1]][line];
                    setColor(WHITE, BLACK); // Reset color
                    cout << " ";
                }
                else // Middle line with card number
                {
                    setColor(WHITE, BLACK);
                    cout << cardLines[printer[current_card][1]][line] << " ";
                }
            }
            cout << endl; // End the line for all cards in the row
        }

        // Update the remaining card count and the starting card for the next row
        counter -= cards_in_row;
        card += cards_in_row;
        cout << endl; // Add a blank line between rows
    }
}

// saved results  show is called to see the result in terminal from the file
void saved_results(){
    ifstream in("result.txt");
    string line;
    while (getline(in, line))
    {
        cout << line << endl;
    }
    in.close();
}

// id wind 2 os placed the other player gets the penalty of 2 cards
void wild_2(int player[2][8][15], int all_card[8][15])
{
    int play = (turn) ? 0 : 1;
    for (int j = 0; j < 2; j++)
    {
        int placer_colour = rand() % 8;
        int placer_catagory = rand() % 15;
        while (all_card[placer_colour][placer_catagory] == 99)
        {
            placer_colour = rand() % 8;
            placer_catagory = rand() % 15;
        }
        player[play][placer_colour][placer_catagory] = all_card[placer_colour][placer_catagory];
        all_card[placer_colour][placer_catagory] = 99;
    }
}

// it is givng the both cards the first 7 7 cards each
void dealCards(int player[2][8][15], int all_card[8][15])
{
    for (int i = 0; i < 7; i++)
    {
        for (int j = 0; j < 2; j++)
        {
            int placer_colour = rand() % 8;
            int placer_catagory = rand() % 15;
            while (all_card[placer_colour][placer_catagory] == 99)
            {
                placer_colour = rand() % 8;
                placer_catagory = rand() % 15;
            }
            player[j][placer_colour][placer_catagory] = all_card[placer_colour][placer_catagory];
            all_card[placer_colour][placer_catagory] = 99;
        }
    }
}

// assigng the array a 99 value fr my own working int he program
void value_giving(int player[2][8][15])
{
    for (int k = 0; k < 2; k++)
    {
        for (int i = 0; i < 8; i++)
        {
            for (int j = 0; j < 15; j++)
            {
                player[k][i][j] = 99;
            }
        }
    }
}

// initalizing the deck acc to my use
void initializeDeck(int deck[][15])
{
    // giving the value to deck cards
    for (int i = 0; i < 8; i++)
    {
        for (int j = 0; j < 15; j++)
        {
            if (i % 2 == 0)
            {
                deck[i][j] = j;
            }
            else
            {
                (j > 0 && j < 13) ? deck[i][j] = j : deck[i][j] = 99;
            }
        }
    }
}

// shuffling in a simple way but is shuffled again and again for inconvinence
void shuffleDeck(int deck[][15])
{
    // randonly shuffling the values
    for (int i = 0; i < 8; i++)
    {
        for (int j = 0; j < 15; j++)
        {
            if (deck[i][j] != 99)
            {
                int types = rand() % 15;
                while (deck[i][types] == 99)
                {
                    types = rand() % 15;
                }
                int temp = deck[i][j];
                deck[i][j] = deck[i][types];
                deck[i][types] = temp;
            }
        }
    }
}

// provided function for clearing the screen
void clearScreen()
{
    system("cls");
}
// provided function by sir
void setColor(int textColor, int bgColor)
{
    HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
    SetConsoleTextAttribute(hConsole, (bgColor << 4) | textColor);
}

// speecial card handling wand't able to be handled here so it wa sdone outside the box
void handleSpecialCard(int perform)
{
    if (printer[perform][1] == 10)
    {

        turn = (turn == 1) ? 0 : 1;
    }
    else if (printer[perform][1] == 11)
    {
        turn = (turn == 1) ? 0 : 1;
    }
}

// updateing discard pile as user layes the card
void UpdateDiscardPile(int &topCard, int first, int deck[8][15])
{
    int colour;
    if (first == 0)
    {
        topCard = rand() % 10;
        topColour = rand() % 8;
        while (deck[topColour][topCard] == 99)
        {
            topColour = rand() % 8;
            topCard = rand() % 15;
        }
        deck[topColour][topCard] = 99;
    }
    for (int line = 0; line < 5; ++line)
    {
        if (topColour == 0 || topColour == 1)
            colour = 1;
        if (topColour == 2 || topColour == 3)
            colour = 2;
        if (topColour == 4 || topColour == 5)
            colour = 4;
        if (topColour == 6 || topColour == 7)
            colour = 6;
        if (topCard != 14 && topCard != 13){
            setColor(0, 7);
            cout << cardLiness[line];
            setColor(WHITE, BLACK);
            cout << " ";
            setColor(WHITE, colour);
            cout << cardLines[topCard][line];
            setColor(WHITE, BLACK);
            cout << " ";
        }
        else
        {
            setColor(0, 7);
            cout << cardLiness[line];
            setColor(WHITE, BLACK);
            cout << " ";
            setColor(WHITE, BLACK);
            cout << cardLines[topCard][line] << " ";
        }
        setColor(WHITE, BLACK);
        cout << endl;
    }
}

// a short welcome screen
void Welome_Plus_Start()
{
    cout << "                                 ";
    setColor(RED, YELLOW); // Set red text with yellow background
    cout << " WELCOME TO UNO ";
    setColor(WHITE, BLACK);
    cout << endl;
}

// call 2 time the wild 2 as it is simple as the other 2
void wild_4(int player[2][8][15], int deck[8][15])
{
    wild_2(player, deck);
    wild_2(player, deck);
}

// how many card the player have
int value_checker(int player[2][8][15], int bari)
{
    int count = 0;
    for (int i = 0; i < 8; i++)
    {
        for (int j = 0; j < 15; j++)
        {
            if (player[bari][i][j] != 99)
            {
                count++;
            }
        }
    }
    return count;
}

// table is printed by it
void table(int player[2][8][15], int bari)
{
    const int max_per_row = 15; // Maximum cards per row
    int counterr = value_checker(player, bari);
    int card=0;
    while (counterr > 0)
    {
        int cards_in_row = (counterr > max_per_row) ? max_per_row : counterr;

        for (int i = 0; i < 5; i++)
        {
            for (int j = 0; j < cards_in_row; j++)
            {
                setColor(0, 7);
                cout << cardLiness[i];
                setColor(7, 0);
                cout << " ";
            }
            cout << endl;
        }
        cout << endl;
        counterr -= cards_in_row;
        card += cards_in_row;
        cout << endl;
    }
}

// turn change
void playTurn()
{
    turn = (turn) ? 0 : 1;
}

// uno chheck
bool callUno(int player[2][8][15], int call_kisna_ki)
{
    return (value_checker(player, call_kisna_ki) == 1) ? 1 : 0;
}

// penetly for not calling uno
void penalty(int player[2][8][15], int all_card[8][15], int bari)
{
    for (int j = 0; j < 2; j++)
    {
        int placer_colour = rand() % 8;
        int placer_catagory = rand() % 15;
        while (all_card[placer_colour][placer_catagory] == 99)
        {
            placer_colour = rand() % 8;
            placer_catagory = rand() % 15;
        }
        player[bari][placer_colour][placer_catagory] = all_card[placer_colour][placer_catagory];
        all_card[placer_colour][placer_catagory] = 99;
    }
}

// saving the game results
void saveLoadGameResult(int player1, int player2)
{
    clear_file();
    ofstream in("result.txt");
    in << "Player 1 score = " + to_string(player1) << endl;
    in << "Player 2 score = " + to_string(player2) << endl;
    in.close();
}

// this is a helper function i studied from interet
void clear_file()
{
    ofstream file("result.txt", ios::trunc); // 'ios::trunc' ensures the file is truncated
    if (!file)
        cout << "Error opening file!" << endl;
    file.close();
}

// is wild allowed to use are not
bool wild_called_allowed(int perform)
{
    if (printer[perform - 1][1] == 13 || printer[perform - 1][1] == 14)
        return 1;
    if (topColour == 0 || topColour == 1)
    {
        if (printer[perform - 1][0] == 0 || printer[perform - 1][0] == 1)
            return 1;
    }
    if (topColour == 2 || topColour == 3)
    {
        if (printer[perform - 1][0] == 2 || printer[perform - 1][0] == 3)
            return 1;
    }
    if (topColour == 4 || topColour == 5)
    {
        if (printer[perform - 1][0] == 4 || printer[perform - 1][0] == 5)
            return 1;
    }
    if (topColour == 6 || topColour == 7)
    {
        if (printer[perform - 1][0] == 6 || printer[perform - 1][0] == 7)
            return 1;
    }
    return 0;
}

// if the deck is used them this is called in this
void intial_again(int deck[][15], int player[2][8][15])
{
    for (int i = 0; i < 8; i++)
    {
        for (int j = 0; j < 15; j++)
        {
            if (player[0][i][j] == -1 && player[1][i][j] == -1)
            {
                if (i % 2 == 0)
                {
                    deck[i][j] = j;
                }
                else
                {
                    (j > 0 && j < 13) ? deck[i][j] = j : deck[i][j] = 99;
                }
            }
        }
    }
}
