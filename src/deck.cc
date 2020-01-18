#include "deck.hh"

#include <cassert>
#include <iostream>

Deck::Deck()
{
    cards = std::make_shared<std::vector<Card>>();
}

std::ostream& operator<<(std::ostream& os, const Deck& d)
{
    os << "[";
    for (Card c : *d.cards)
        os << c;
    os << "]";

    return os;
}

void Deck::brandNew()
{
    // RESET VECTOR MEMORY
    std::vector<Card>().swap(*cards);

    // GENERATE THE BRAND NEW DECK
    for (size_t value = 0; value < 13; value++)
    {
        (*cards).push_back(Card(SPADE, value));
        (*cards).push_back(Card(DIAMOND, value));
        (*cards).push_back(Card(HEART, value));
        (*cards).push_back(Card(CLUB, value));
    }
}

void Deck::shake()
{
    if ((*cards).size() > 0)
    {
        for (int i = 0; i < 10000; i++)
        {
            size_t rnd_1 = rand() % (*cards).size();
            size_t rnd_2 = rand() % (*cards).size();

            Card tmp_card = (*cards).at(rnd_1);

            (*cards).at(rnd_1) = (*cards).at(rnd_2);
            (*cards).at(rnd_2) = tmp_card;
        }
    }
}

template <typename T>
void pop_front(std::vector<T>& vec)
{
    assert(!vec.empty());
    vec.front() = std::move(vec.back());
    vec.pop_back();
}

Card Deck::pick(int index)
{
    Card c = (*cards).at(index);
    pop_front(*cards);
    return c;
}

void Deck::add(Card c)
{
    (*cards).push_back(c);
}

size_t Deck::getSize()
{
    return (*cards).size();
}

int Deck::getValue()
{
    int sum = 0;
    for (size_t i = 0; i < (*cards).size(); i++)
        sum += (*cards).at(i).getValue();
    return sum;
}
