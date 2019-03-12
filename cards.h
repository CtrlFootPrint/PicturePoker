#include "graphics.h"
class Cardset
{
    public:
    Cardset (int ch, int gh, bool h )
    {
        card_height_ = ch;
        gfx_height_ = gh;
        hide_value_ = h;
    }
    int card_height_; // y coordinate that cards are printed
    int gfx_height_; // y coordinate that rank gfx are printed
    int card_kind_[5]; // number that varies from 0-5, Star, Mario, Luigi, Flower, Mushroom, Cloud
    int rearrange_[5]; // Used to rearrange the cards
    bool change_card_[5]; // 0 = Don't swap card, 1 = swap card
    bool hide_value_;
    bool hide_[5]; // 0 show card, 1 hide card i.e. show the back of it
    bool disappear_[5]; // 0 show card, 1 do not draw the card at all - actual value used
    bool det_dis_[5]; // Determines which card should disappear
    int count_[6] = {0,0,0,0,0,0}; // See amount of each card kind
    int hand_rank_ = 0; // 0-6: Junk, 1 pair, 2 pairs, 3 of a kind, full house, 4 of a kind, 5 of a kind
    int major_suit = 0;
    int minor_suit = 0;
    Sprite p_card[5];
    void initialise()
    {
        for (int i = 0; i<5; i++)
        {
            count_[i] = 0;
            change_card_[i] = 0;
            hide_[i] = hide_value_;
            disappear_[i] = 0;
            rearrange_[i] = 0;
            card_kind_[i] = rand() % 6;
            p_card[i].setCoordinates(52+40*i,card_height_);
            p_card[i].setLengths(32,48);
            p_card[i].setTexture(2+card_kind_[i]); // 2-7 are the sprites for Star-Cloud
            major_suit = 0;
            minor_suit = 0;
        }
        count_[5] = 0; // Since it could not fit in the for loop
    };
    void drawCards(sf::RenderWindow &window)
    {
        for (int i = 0; i<5; i++)
        {
            p_card[i].setTexture(2+card_kind_[i]);
            if (hide_[i]) p_card[i].setTexture(8); // Show the back of the card if it is meant to be hidden
            if (disappear_[i] == 0)p_card[i].draw(window);
        }
    }
    void drawRankGfx (sf::RenderWindow &window)
    {
        Sprite rank_gfx; // Sprite used to draw rank
        if (hand_rank_ == 6)
        {
            rank_gfx.setCoordinates(74,gfx_height_);
            rank_gfx.setLengths(108,15);
        } // 5 of a kind
        else if (hand_rank_ == 5)
        {
            rank_gfx.setCoordinates(73,gfx_height_);
            rank_gfx.setLengths(110,15);
        } // 4 of a kind
        else if (hand_rank_ == 4)
        {
            rank_gfx.setCoordinates(77,gfx_height_);
            rank_gfx.setLengths(103,15);
        } // Full House
        else if (hand_rank_ == 3)
        {
            rank_gfx.setCoordinates(74,gfx_height_);
            rank_gfx.setLengths(107,15);
        } // 3 of a kind
        else if (hand_rank_ == 2)
        {
            rank_gfx.setCoordinates(93,gfx_height_);
            rank_gfx.setLengths(70,15);
        } // 2 Pairs
        else if (hand_rank_ == 1)
        {
            rank_gfx.setCoordinates(100,gfx_height_);
            rank_gfx.setLengths(55,15);
        } // 1 Pair
        else
        {
            rank_gfx.setCoordinates(103,gfx_height_);
            rank_gfx.setLengths(46,15);
        }// Junk
        rank_gfx.setTexture(9+hand_rank_);
        rank_gfx.draw(window);
    }
    void highlightCard (int card_selected)
    {
        if (change_card_[card_selected]== 0)
        {
            p_card[card_selected].y_ -= 8; // lift card if it is about to be selected
            change_card_[card_selected] = 1;
        }
        else
        {
            p_card[card_selected].y_ +=8; // lower card if the selection has been cancelled.
            change_card_[card_selected] = 0;
        }
    }
    bool NoCardSelected ()
    {
        bool check = 1; //0 = There is a card selected, 1 = None of the cards have been seleceted
        for (int i = 0; i<5; i++)
        {
            if (change_card_[i] == 1)check = 0;
        }
        return check;
    }
    void switchCards ()
    {
        for (int i = 0; i<5; i++)
        {
            if (change_card_[i] == 1)
            {
                 card_kind_[i] = rand() % 6;
                 highlightCard(i);
            }
            change_card_[i] = 0;

        }
    }
    void countCards()
    {
        for (int i = 0; i<5 ; i++)
        {
            count_[card_kind_[i]]++;
        }
    }
    int anyCardsofSize(int num) // Return how many x of a kind there
    {
        int statement = 0;
        for (int i = 0; i<6 ; i++)
        {
             if (count_[i] == num) statement++;
        }
        return statement;
    }
    int whichCardofSize(int num, int order)
    {
        int ID[5];
        int pos = 0;
        for (int i = 0; i<5 ; i++)
        {
             if (count_[card_kind_[i]] == num)
             {
                if (pos == 0 || ID[pos-1] != card_kind_[i])
                {
                    ID[pos] = card_kind_[i];
                    pos++;
                }
             }
        }
        return ID[order];
    }
    void arrangeCards() // Change order of cards if it is not 5 of a kind, nor a junk hand
    {
        if (anyCardsofSize(5))
        {
            hand_rank_ = 6;
            for (int i = 0; i < 5; i++ )rearrange_[i] = whichCardofSize(5,0);
        }
        else if (anyCardsofSize(4))
        {
            hand_rank_ = 5;
            for (int i = 0; i < 4; i++ )rearrange_[i] = whichCardofSize(4,0);
            rearrange_[4] = whichCardofSize(1,0);
        }
        else if (anyCardsofSize(3))
        {
            for (int i = 0; i < 3; i++ )rearrange_[i] = whichCardofSize(3,0);
            if (anyCardsofSize(2))
            {
                hand_rank_ = 4;
                for (int i = 0; i < 2; i++ )rearrange_[3+i] = whichCardofSize(2,0);
            }
            else
            {
                hand_rank_ = 3;
                rearrange_[3] = whichCardofSize(1,0);
                rearrange_[4] = whichCardofSize(1,1);
            }
        }
        else if (anyCardsofSize(2))
        {
            for (int i = 0; i < 2; i++ )rearrange_[i] = whichCardofSize(2,0);
            if (anyCardsofSize(2) == 2)
            {
                hand_rank_ = 2;
                for (int i = 0; i < 2; i++ )rearrange_[2+i] = whichCardofSize(2,1);
                rearrange_[4] = whichCardofSize(1,0);
            }
            else
            {
                hand_rank_ = 1;
                rearrange_[2] = whichCardofSize(1,0);
                rearrange_[3] = whichCardofSize(1,1);
                rearrange_[4] = whichCardofSize(1,2);
            }
        }
        else
        {
            hand_rank_ = 0;
            for (int i =0; i<5; i++)rearrange_[i] = card_kind_[i];
        }
    }
    void applyArrangement()
    {
        for (int i = 0; i<5; i++)card_kind_[i] = rearrange_[i];
    }
    void setCards(int one, int two, int three, int four, int five) // Debug function
    {
        card_kind_[0] = one;
        card_kind_[1] = two;
        card_kind_[2] = three;
        card_kind_[3] = four;
        card_kind_[4] = five;
    }
    void highlightApplicableCards(sf::Vector2i localPosition)
    {
        for (int i = 0; i<5; i++)
        {
            if (p_card[i].isPressed(localPosition)) highlightCard(i);
        }
    }
    void hideApplicableCards()
    {
        for (int i = 0; i<5; i++)
        {
            if (change_card_[i] == 1) hide_[i] = 1;
        }
    }
    void hideCards()
    {
        for (int i = 0; i<5; i++)
        {
            hide_[i] = 1;
        }
    }
    void applyDisappear(int one, int two, int three, int four, int five)
    {
        disappear_[0] = one;
        disappear_[1] = two;
        disappear_[2] = three;
        disappear_[3] = four;
        disappear_[4] = five;
    }
    void unhideCards()
    {
        for (int i = 0; i<5; i++)
        {
            hide_[i] = 0;
        }
    }
    int getHRank () // Hand rank
    {
        return hand_rank_;
    }
    int getSuit1 () // Major suit
    {
        if (hand_rank_ == 2)
        {
            if (card_kind_[0]>card_kind_[2]) major_suit = card_kind_[0];
            // Return first suit if it is bigger than second pair
            else major_suit = card_kind_[2]; // Otherwise return second pair.
        }
        else major_suit = card_kind_[0];
        return major_suit;
        // For all the other ranks, the first card is always the "major" suit, after arrangement
    }
    int getSuit2 () // Used to determine winner if the major suit is equal
    {
        if (hand_rank_ == 6) minor_suit = card_kind_[0];
        // It doesn't matter which card is returned since this value won't be used
        else if (hand_rank_ == 5) minor_suit = card_kind_[4];
        // Return last card, won't be used.
        else if (hand_rank_ == 4) minor_suit = card_kind_[3];
        // Return suit of the pair of the full house
        else if (hand_rank_ == 3) minor_suit = card_kind_[3];
        // Value will not be used
        else if (hand_rank_ == 2)
        {
            if (card_kind_[0]<card_kind_[2]) minor_suit = card_kind_[0];
            // Return first suit if it is smaller than second pair
            else minor_suit = card_kind_[2]; // Otherwise return second pair.
        }
        else if (hand_rank_ == 1) minor_suit = card_kind_[2];
        // Value will not be used
        else if (hand_rank_ == 0) minor_suit = card_kind_[1];
        // Value will not be used
        return minor_suit;
    }
    void determineDisappear(int opponent_major)
    {
        int player_major = getSuit1();
        if (hand_rank_ == 6) applyDisappear(1,1,1,1,1);
        else if (hand_rank_ == 5) applyDisappear(1,1,1,1,0);
        else if (hand_rank_ == 4)
        {
            if (player_major != opponent_major)applyDisappear(1,1,1,0,0); //
            else applyDisappear(0,0,0,1,1);

        }
        else if (hand_rank_ == 3) applyDisappear(1,1,1,0,0);
        else if (hand_rank_ == 2)
        {
            if (card_kind_[0]>card_kind_[2] && player_major != opponent_major) applyDisappear(1,1,0,0,0);
            else if (card_kind_[0]>card_kind_[2] && player_major==opponent_major) applyDisappear(0,0,1,1,0);

            if (card_kind_[0]<card_kind_[2]&& player_major != opponent_major)applyDisappear(0,0,1,1,0);
            else if (card_kind_[0]<card_kind_[2] && player_major==opponent_major) applyDisappear(1,1,0,0,0);

        }
        else if (hand_rank_ == 1) applyDisappear(1,1,0,0,0);
    }

};
