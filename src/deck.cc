#include "deck.hh"

#include <algorithm>
#include <cassert>
#include <iostream>
#include <random>

Deck::Deck()
{
    cards = std::make_shared<std::vector<Card>>();
}

std::ostream& operator<<(std::ostream& os, const Deck& d)
{
    for (size_t i = 0; i < d.cards->size(); i++)
        os << d.cards->at(i);

    return os;
}

void Deck::dumpBack()
{
    for (size_t i = 0; i < cards->size(); i++)
        std::cout << "🂠 ";
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

void Deck::sort()
{
    std::sort((*cards).begin(), (*cards).end());
}

template <typename T>
void pop_front(std::vector<T>& vec)
{
    assert(!vec.empty());
    vec.front() = std::move(vec.back());
    vec.pop_back();
}

Card Deck::getCard(size_t index)
{
    return Card(getColorAt(index), getValueAt(index));
}

Card Deck::pick(size_t index)
{
    Card c = (*cards).at(index);
    if (index == 0)
        pop_front(*cards);
    else
        (*cards).erase((*cards).begin() + index);
    return c;
}

void Deck::popBack()
{
    (*cards).pop_back();
}

void Deck::add(Card c)
{
    (*cards).push_back(c);
}

size_t Deck::getValueAt(size_t i)
{
    return (*cards).at(i).getValue();
}

enum Color Deck::getColorAt(size_t i)
{
    return (*cards).at(i).getColor();
}

void Deck::addDeck(Deck deck)
{
    while (deck.getSize() > 0)
        (*cards).push_back(deck.pick());
}

void Deck::copyDeck(Deck deck)
{
    for (size_t i = 0; i < deck.getSize(); i++)
        add(Card(deck.getColorAt(i), deck.getValueAt(i)));
}

size_t Deck::getSize()
{
    return (*cards).size();
}

int Deck::getValue()
{
    int sum = 0;
    for (size_t i = 0; i < (*cards).size(); i++)
        sum += (*cards).at(i).getCardValue();

    return sum;
}

int Deck::find(Card c)
{
    for (size_t i = 0; i < getSize(); i++)
        if ((*cards).at(i) == c)
            return i;
    return -1;
}

bool Deck::checkGreenHand()
{
    return getValue() <= 7;
}

bool Deck::checkSameValue()
{
    bool res = true;
    for (size_t i = 0; res && i < (*cards).size() - 1; i++)
        res &= ((*cards).at(i).getValue() == (*cards).at(i + 1).getValue());
    return res;
}

bool Deck::checkSameColor()
{
    bool res = true;
    for (size_t i = 0; res && i < (*cards).size() - 1; i++)
        res &= ((*cards).at(i).getColor() == (*cards).at(i + 1).getColor());
    return res;
}

bool Deck::checkSequence()
{
    bool res = true;
    for (size_t i = 0; res && i < (*cards).size() - 1; i++)
        res &= ((*cards).at(i).getValue() + 1 == (*cards).at(i + 1).getValue());
    return res;
}

bool Deck::checkCombo()
{
    sort();
    if (checkSameValue())
        return true;
    if (checkSameColor() && checkSequence())
        return true;
    return false;
}

void Deck::__generateCombination(std::shared_ptr<std::vector<Deck>> combos,
                                 Deck combination, size_t offset, size_t k)
{
    if (k == 0)
    {
        Deck c = Deck();
        c.copyDeck(combination);
        if (c.checkCombo())
            (*combos).push_back(c);
    } else
    {
        for (size_t i = offset; i <= (*cards).size() - k; ++i)
        {
            combination.add((*cards).at(i));
            __generateCombination(combos, combination, i + 1, k - 1);
            combination.popBack();
        }
    }
}

std::shared_ptr<std::vector<Deck>> Deck::generateCombos()
{
    std::shared_ptr<std::vector<Deck>> combos =
        std::make_shared<std::vector<Deck>>();

    Deck combination = Deck();
    for (size_t i = 1; i <= (*cards).size(); i++)
        __generateCombination(combos, combination, 0, i);

    return combos;
}

void Deck::clear()
{
    (*cards).clear();
}
