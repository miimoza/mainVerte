#include "deck.hh"

#include <cassert>
#include <iostream>
#include <random>

Deck::Deck()
{
    cards = std::make_shared<std::vector<Card>>();
}

std::ostream& operator<<(std::ostream& os, const Deck& d)
{
    os << "[";
    for (size_t i = 0; i < d.cards->size(); i++)
        os << d.cards->at(i);
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

void Deck::shuffle()
{
    if ((*cards).size() > 0)
    {
        for (int i = 0; i < 1000; i++)
        {
            std::random_device rd;
            std::mt19937 mt(rd());
            std::uniform_real_distribution<double> dist(0, (*cards).size() - 1);

            size_t rnd_1 = std::round(dist(mt));
            size_t rnd_2 = std::round(dist(mt));

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
    if (index == 0)
        pop_front(*cards);
    else
        (*cards).erase((*cards).begin() + index);
    return c;
}

void Deck::add(Card c)
{
    (*cards).push_back(c);
}

void Deck::addDeck(Deck deck)
{
    while (deck.getSize() > 0)
        (*cards).push_back(deck.pick());
}

size_t Deck::getSize()
{
    return (*cards).size();
}

int Deck::getValue()
{
    int sum = 0;
    for (size_t i = 0; i < (*cards).size(); i++)
    {
        if ((*cards).at(i).getValue() == 10
            && ((*cards).at(i).getColor() & (DIAMOND | HEART)))
            sum += -1;
        else if ((*cards).at(i).getValue() > 9)
            sum += 11;
        else
            sum += (*cards).at(i).getValue() + 1;
    }
    return sum;
}

void Deck::clear()
{
    (*cards).clear();
}
