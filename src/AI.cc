#include "AI.hh"

#include <iostream>

AI::AI(Deck hand, Deck cemetery)
{
    this->hand = Deck();
    this->cemetery = Deck();
    this->combo = Deck();

    this->hand.copyDeck(hand);
    this->cemetery.copyDeck(cemetery);
}

std::string AI::get_command()
{
    std::cout << "hand:" << hand << "\n";
    std::cout << "cemetery:" << cemetery << "\n";

    combo.addDeck(get_best_combo());

    std::string command;

    command += get_combo_indexes();
    command += ";";

    update_hand();
    command += get_pickway();

    std::cout << "IA command:" << command << "\n";

    return command;
}

Deck AI::get_best_combo()
{
    std::shared_ptr<std::vector<Deck>> combos = hand.generateCombos();

    for (auto d : *combos)
        std::cout << d;
    std::cout << "\n";

    size_t best_index = 0;
    for (size_t i = 1; i < (*combos).size(); i++)
        if ((*combos).at(i).getValue() > (*combos).at(best_index).getValue())
            best_index = i;

    return (*combos).at(best_index);
}

std::string AI::get_combo_indexes()
{
    std::string combo_indexes;

    for (size_t i = 0; i < hand.getSize(); i++)
    {
        size_t value = hand.getValueAt(i);
        enum Color color = hand.getColorAt(i);

        for (size_t j = 0; j < combo.getSize(); j++)
        {
            if (combo.getValueAt(j) == value && combo.getColorAt(j) == color)
            {
                combo_indexes += std::to_string(i);
                combo_indexes += ",";
                break;
            }
        }
    }

    // Remove the last comma
    if (combo_indexes.size() > 1)
        combo_indexes.pop_back();

    return combo_indexes;
}

void AI::update_hand()
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

std::string AI::get_pickway()
{
    std::cout << "real hand:" << hand << "combo" << combo << "\n";

    return "h";
}
