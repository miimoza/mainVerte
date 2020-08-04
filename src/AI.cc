#include "AI.hh"

#include <iostream>
#include <string>

AI::AI(Deck hand, Deck cemetery, size_t nb_cards_opponent)
{
    this->nb_cards_opponent = nb_cards_opponent;
    this->hand = Deck();
    this->cemetery = Deck();
    this->combo = Deck();

    this->hand.copyDeck(hand);
    this->cemetery.copyDeck(cemetery);
}

std::string AI::getCommand()
{
    float greenhand_limit = (nb_cards_opponent > 3) ? 7 : nb_cards_opponent;
    if (hand.getValue() <= greenhand_limit)
        return "greenhand";

    combo.addDeck(getBestCombo(hand));

    std::string command;

    command += getComboIndexes();
    command += ";";

    updateHand();
    command += getPickway();

    // std::cout << "IA command:" << command << "\n";

    return command;
}

Deck AI::getBestCombo(Deck hand)
{
    // INITIALISATION
    float average_value_per_card =
        (float)hand.getValue() / (float)hand.getSize();
    float limit_pair_value =
        (float)nb_cards_opponent + average_value_per_card / 5;

    std::shared_ptr<std::vector<Deck>> combos = hand.generateCombos();

    /*for (auto d : *combos)
        std::cout << d << ",";
    std::cout << "\n";*/

    size_t best_index = 0;
    for (size_t combo_index = 1; combo_index < (*combos).size(); combo_index++)
    {
        // TECHNIC: ITS BEST TO PUT A LOW VALUE PAIR THAN A HIGH VALUE CARD
        if ((*combos).at(combo_index).getSize()
                > (*combos).at(best_index).getSize()
            && (*combos).at(combo_index).getValue() > limit_pair_value)
            best_index = combo_index;
        else if ((*combos).at(combo_index).getValue()
                 > (*combos).at(best_index).getValue())
            best_index = combo_index;
    }
    return (*combos).at(best_index);
}

std::string AI::getComboIndexes()
{
    std::string combo_indexes;

    for (size_t i = 0; i < combo.getSize(); i++)
        combo_indexes += (std::to_string(hand.find(combo.getCard(i))) + ",");

    // Remove the last comma
    if (combo_indexes.size() > 1)
        combo_indexes.pop_back();

    return combo_indexes;
}

void AI::updateHand()
{
    for (int i = hand.getSize() - 1; i >= 0; i--)
    {
        size_t value = hand.getValueAt(i);
        enum Color color = hand.getColorAt(i);

        for (size_t j = 0; j < combo.getSize(); j++)
        {
            if (combo.getValueAt(j) == value && combo.getColorAt(j) == color)
            {
                hand.pick(i);
                break;
            }
        }
    }
}

float AI::getCardCapacity(Card card)
{
    float ambition = 0.5;

    Deck eventual_deck = Deck();
    eventual_deck.copyDeck(hand);
    eventual_deck.add(card);

    size_t nb_real_combo_eventual = 0;
    std::shared_ptr<std::vector<Deck>> eventual_combos =
        eventual_deck.generateCombos();
    for (Deck d : *eventual_combos)
        nb_real_combo_eventual += (d.getSize() > 1);

    size_t nb_real_combo_hand = 0;
    std::shared_ptr<std::vector<Deck>> hand_combos = hand.generateCombos();
    for (Deck d : *hand_combos)
        nb_real_combo_hand += (d.getSize() > 1);

    float average_value_per_card =
        (float)hand.getValue() / (float)hand.getSize();

    float combo_coeff = (nb_real_combo_eventual - nb_real_combo_hand) * 2;
    float value_coeff =
        (average_value_per_card - ambition - card.getCardValue()) / 2;

    /*
// ambition
std::cout << "value:" << hand.getValue() << "\n";
std::cout << "size :" << hand.getSize() << "\n";
std::cout << "nb_real_combo_eventual:" << nb_real_combo_eventual << "\n";
std::cout << "nb_real_combo_hand:" << nb_real_combo_hand << "\n";
std::cout << "average_value_per_card:" << average_value_per_card << "\n";
std::cout << "combo coeff:" << combo_coeff << "\n";
std::cout << "value coeff:" << value_coeff << "\n";
std::cout << "capacity" << combo_coeff + value_coeff << "\n";
*/

    return combo_coeff + value_coeff;
}

std::string AI::getPickway()
{
    size_t best_cemetery_card_index = 0;
    for (size_t i = 1; i < cemetery.getSize(); i++)
        if (getCardCapacity(cemetery.getCard(i))
            > getCardCapacity(cemetery.getCard(best_cemetery_card_index)))
            best_cemetery_card_index = i;

    // std::cout << "best cemetery:" <<
    // cemetery.getCard(best_cemetery_card_index) << "\n";

    if (getCardCapacity(cemetery.getCard(best_cemetery_card_index)) > 0)
        return "c" + std::to_string(best_cemetery_card_index);
    return "h";
}
