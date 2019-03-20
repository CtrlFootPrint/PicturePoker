#include "card.h"
Cardset::Cardset (int ch, int gh, bool h, bool ud)
{
    card_height_ = ch;
    gfx_height_ = gh;
    hide_value_ = h;
    up_or_down_ = ud;
    for (int i = 0; i<5; i++)
    {
        count_[i] = 0;
        change_card_[i] = 0;
        hide_[i] = hide_value_;
        disappear_[i] = 0;
        rearrange_[i] = 0;
        card[i].setCoordinates(52+40*i,card_height_);
        card[i].setLengths(32,48);
        card[i].setTexture(2+card_kind_[i]); // 2-7 are the sprites for Star-Cloud
        major_suit = 0;
        minor_suit = 0;
    }
    count_[5] = 0; // Since it could not fit in the for loop
}
void Cardset::drawCards()
{
    for (int i = 0; i<5; i++)
        {
            card[i].setTexture(2+card_kind_[i]);
            if (hide_[i]) card[i].setTexture(8); // Show the back of the card if it is meant to be hidden
            if (disappear_[i] == 0)card[i].draw();
        }
}
void Cardset::randomise()
{
    for (int i = 0; i<5; i++)
    {
        card_kind_[i] = Random::getRandom(0,6);
    }
}

void Cardset::highlightCard(int card_selected)
{
    if (change_card_[card_selected]== 0)
    {
        if (up_or_down_ == 0)card[card_selected].displaceY(-8); // lift card if it is about to be selected
        else card[card_selected].displaceY(8); // lower card if it is about to be selected

        change_card_[card_selected] = 1;
    }
    else
    {
        if (up_or_down_ == 0)card[card_selected].displaceY(8); // lower card if the selection has been cancelled.
        else card[card_selected].displaceY(-8); // lift card if the selection has been cancelled.
        change_card_[card_selected] = 0;
    }
}

bool Cardset::NoCardSelected()
{
    bool check = 1; //0 = There is a card selected, 1 = None of the cards have been seleceted
    for (int i = 0; i<5; i++)
    {
        if (change_card_[i] == 1)check = 0;
    }
    return check;
}

bool Cardset::NoCardPressed()
{
    bool check = 1; //0 = There is a card selected, 1 = None of the cards have been seleceted
    for (int i = 0; i<5; i++)
    {
        if (card[i].isPressed())check = 0;
    }
    return check;

}
void Cardset::highlightApplicableCards(int x, int y)
{
    for (int i = 0; i<5; i++)
    {
        if (card[i].isPressed()) highlightCard(i);
    }
}


void Cardset::hideApplicableCards()
    {
        for (int i = 0; i<5; i++)
        {
            if (change_card_[i] == 1) hide_[i] = 1;
        }
    }
void Cardset::switchCards ()
{
    for (int i = 0; i<5; i++)
    {
        if (change_card_[i] == 1)
        {
            card_kind_[i] = Random::getRandom(0,6);
            highlightCard(i);
        }
        change_card_[i] = 0;
    }
}

void Cardset::uncoverCards()
{
    for (int i = 0; i<5; i++)
    {
        hide_[i] = 0;
    }
}
void Cardset::coverCards()
{
    for (int i = 0; i<5; i++)
    {
        hide_[i] = 1;
    }
}

void Cardset::countCards()
{
    for (int i = 0; i<5 ; i++)
    {
        count_[card_kind_[i]]++;
    }

}

int Cardset::anyCardsofSize(int num) // Return how many x of a kind there
{
    int statement = 0;
    for (int i = 0; i<6 ; i++)
    {
        if (count_[i] == num) statement++;
    }
    return statement;
}


int Cardset::whichCardofSize(int num, int order)
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

void Cardset::arrangeCards() // Change order of cards if it is not 5 of a kind, nor a junk hand
{
    calcHRank();
    if (anyCardsofSize(5))
    {
        for (int i = 0; i < 5; i++ )rearrange_[i] = whichCardofSize(5,0);
    }
    else if (anyCardsofSize(4))
    {
        for (int i = 0; i < 4; i++ )rearrange_[i] = whichCardofSize(4,0);
        rearrange_[4] = whichCardofSize(1,0);
    }
    else if (anyCardsofSize(3))
    {
        for (int i = 0; i < 3; i++ )rearrange_[i] = whichCardofSize(3,0);
        if (anyCardsofSize(2))
        {
            for (int i = 0; i < 2; i++ )rearrange_[3+i] = whichCardofSize(2,0);
        }
        else
        {
            rearrange_[3] = whichCardofSize(1,0);
            rearrange_[4] = whichCardofSize(1,1);
        }
    }
    else if (anyCardsofSize(2))
    {
        for (int i = 0; i < 2; i++ )rearrange_[i] = whichCardofSize(2,0);
        if (anyCardsofSize(2) == 2)
        {
            for (int i = 0; i < 2; i++ )rearrange_[2+i] = whichCardofSize(2,1);
            rearrange_[4] = whichCardofSize(1,0);
        }
        else
        {
            rearrange_[2] = whichCardofSize(1,0);
            rearrange_[3] = whichCardofSize(1,1);
            rearrange_[4] = whichCardofSize(1,2);
        }
    }
    else
    {
        for (int i =0; i<5; i++)rearrange_[i] = card_kind_[i];
    }
}


void Cardset::applyArrangement()
{
    for (int i = 0; i<5; i++)card_kind_[i] = rearrange_[i];
}

void Cardset::drawRankGfx ()
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
    rank_gfx.draw();
}


int Cardset::getHRank () // Hand rank
{
    return hand_rank_;
}

void Cardset::reset()
{
    for (int i = 0; i<5; i++)
    {
        count_[i] = 0;
        change_card_[i] = 0;
        hide_[i] = hide_value_;
        disappear_[i] = 0;
        rearrange_[i] = 0;
        card_kind_[i] = Random::getRandom(0,6);
        major_suit = 0;
        minor_suit = 0;
    }
    count_[5] = 0; // Since it could not fit in the for loop
}

int Cardset::getSuit1 () // Major suit
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

int Cardset::getSuit2 () // Used to determine winner if the major suit is equal
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
void Cardset::applyDisappear(int one, int two, int three, int four, int five)
{
    disappear_[0] = one;
    disappear_[1] = two;
    disappear_[2] = three;
    disappear_[3] = four;
    disappear_[4] = five;
}
void Cardset::showAll()
{
    for (int i = 0; i<5; i++)disappear_[i] = 0;
}
void Cardset::determineDisappear(int opponent_major)
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

void Cardset::setCards(int one, int two, int three, int four, int five) // Debug function
{
    card_kind_[0] = one;
    card_kind_[1] = two;
    card_kind_[2] = three;
    card_kind_[3] = four;
    card_kind_[4] = five;
}

void Cardset::AISwitch()
{
    countCards();
    calcHRank();
    if (hand_rank_ == 0) // Junk
    {
        if (Random::getRandom(0,3)) // Either two choices, 2/3 chance this one will be done
        {
            int keep;
            keep = Random::getRandom(0,5); // Keep one of the 5 cards
            for (int i = 0; i<5; i++)
            {
                if (i!=keep) highlightCard(i); // Keep one card and draw four cards
            }
        }
        else
        {
            for (int i = 0; i<5; i++)
            {
                highlightCard(i); // Draw all the cards
            }
        }
    }
    if (hand_rank_ == 1)// 1 Pair
    {
        if (Random::getRandom(0,3))
        {
            for (int i = 0; i<5; i++)
            {
                if (card_kind_[i]!=whichCardofSize(2,0)) highlightCard(i); // Keep the pair and draw three cards
            }
        }
        else
        {
            int keep;
            keep = Random::getRandom(0,3); // Keep one of the three cards
            int counter = 0;
            for (int i = 0; i<5; i++)
            {
                if (card_kind_[i]!=whichCardofSize(2,0))
                {
                    if (counter!=keep)
                    {
                        highlightCard(i); // Keep the pair and draw three cards
                    }
                    counter++;
                }
            }
        }
    }
    if (hand_rank_ == 2)
    {
        if (Random::getRandom(0,5)) // 4/5 chance that the computer only changes one card
        {
            for (int i = 0; i<5; i++)
            {
                if (card_kind_[i]!=whichCardofSize(2,0) && card_kind_[i]!=whichCardofSize(2,1) )
                highlightCard(i); // Keep both pairs and draw the remaining card
            }
        }
        else
        {
            int major_s;
            if (whichCardofSize(2,0)>whichCardofSize(2,1))major_s = whichCardofSize(2,0);
            else major_s = whichCardofSize(2,1);
            for (int i = 0; i<5; i++)
            {
                if (card_kind_[i]!=major_s)
                highlightCard(i); // Keep the best pair and draw three cards
            }
        }
    }
    if (hand_rank_ == 3) // 3 of a Kind
    {
        if (Random::getRandom(0,5)) // 4/5 chance that the computer changes both card
        {
            for (int i = 0; i<5; i++)
            {
                if (card_kind_[i]!=whichCardofSize(3,0))
                highlightCard(i); // Keep both pairs and draw the remaining card
            }
        }
        else
        {
            int keep;
            keep = Random::getRandom(0,2); // Keep one of the three cards
            int counter = 0;
            for (int i = 0; i<5; i++)
            {
                if (card_kind_[i]!=whichCardofSize(3,0))
                {
                    if (counter!=keep)
                    {
                        highlightCard(i); // Keep the pair and draw three cards
                    }
                    counter++;
                }
            }
        }
    }
    if (hand_rank_ == 4) // Full House
    {
        if (Random::getRandom(0,8)); // 7/8 chance that the computer changes nothing
        else
        {
            for (int i = 0; i<5; i++)
            {
                if (card_kind_[i]==whichCardofSize(2,0)) highlightCard(i); // Draw both pairs
            }

        }

    }
    if (hand_rank_ == 5) // 4 of a Kind
    {
        for (int i = 0; i<5; i++)
        {
            if (card_kind_[i]!=whichCardofSize(4,0)) highlightCard(i); // Draw the single card
        }
    // This is the only option made, since it would be disadvatageous to keep the remaining card
    }
    // AI does not switch cards if there is a 5 of a kind


    resetCount();

};
void Cardset::printDebug()
{
    std::cout << whichCardofSize(4,0) << " Hand Rank: ";
    std::cout << getHRank() << "\n";
}


void Cardset::resetCount()
{
    for (int i = 0; i<6; i++)
    {
        count_[i] = 0;
    }
}

void Cardset::calcHRank()
{
    if (anyCardsofSize(5))
    {
        hand_rank_ = 6;
    }
    else if (anyCardsofSize(4))
    {
        hand_rank_ = 5;
    }
    else if (anyCardsofSize(3))
    {
        if (anyCardsofSize(2))hand_rank_ = 4;
        else hand_rank_ = 3;
    }
    else if (anyCardsofSize(2))
    {
        if (anyCardsofSize(2) == 2)hand_rank_ = 2;
        else hand_rank_ = 1;
    }
    else
    {
        hand_rank_ = 0;
    }
}
