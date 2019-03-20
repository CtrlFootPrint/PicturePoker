#ifndef CARD_H
#define CARD_H
#include "window.h"
#include "graphics.h"
#include "random.h"
#include <iostream>
class Cardset
{
    private:
    Sprite card[5];
    int rearrange_[5]; // Used to rearrange the cards
    int count_[6]; // See amount of each card kind
    int card_height_; // y coordinate that cards are printed
    int gfx_height_; // y coordinate that rank gfx are printed
    int card_kind_[5]; // number that varies from 0-5, Star, Mario, Luigi, Flower, Mushroom, Cloud
    bool change_card_[5]; // 0 = Don't swap card, 1 = swap card
    bool hide_value_; // Value used as the default value to hide cards or not
    bool up_or_down_; // Value used to determine if highlighted cards go up or down, up = 0, down = 1
    bool hide_[5]; // 0 show card, 1 hide card i.e. show the back of it
    bool disappear_[5]; // 0 show card, 1 do not draw the card at all - actual value used
    bool det_dis_[5]; // Determines which card should disappear, when flashing
    int hand_rank_ = 0; // 0-6: Junk, 1 pair, 2 pairs, 3 of a kind, full house, 4 of a kind, 5 of a kind
    int major_suit = 0; // Value of highest suit
    int minor_suit = 0; // Value of lowest suit
    public:
    Cardset (int ch, int gh, bool h, bool ud);
    void randomise();
    void drawCards();
    void highlightCard (int card_selected);
    bool NoCardSelected();
    bool NoCardPressed();
    void highlightApplicableCards(int x, int y);
    void hideApplicableCards();
    void switchCards ();
    void coverCards();
    void uncoverCards();
    int anyCardsofSize(int num);
    int whichCardofSize(int num, int order);
    void countCards();
    void arrangeCards();
    void applyArrangement();
    void drawRankGfx ();
    int getHRank ();
    void reset();
    int getSuit1();
    int getSuit2();
    void applyDisappear(int one, int two, int three, int four, int five);
    void showAll();
    void determineDisappear(int opponent_major);
    void AISwitch();
    void setCards(int one, int two, int three, int four, int five); // Debug function
    void printDebug();
    void resetCount();
    void calcHRank();
};
#endif // CARD_H
