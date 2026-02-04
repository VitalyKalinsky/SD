#include "barrel.hpp"
#include <iostream>
#include <cmath>

using namespace std;

Barrel::Barrel()
{
    volume = 0.0;
    current_volume = 0.0;
    alcohol_content = 0.0;
    cout << "Constructor_def called for " << this << endl;
}

Barrel::Barrel(double total_volume, double alcohol_percent)
{
    volume = total_volume;
    current_volume = total_volume;

    if (total_volume < 0.0)
    {
        cout << "Объём не может быть отрицательным!" << endl;
        volume = 0.0;
        current_volume = 0.0;
    }

    if (alcohol_percent < 0.0)
    {
        cout << "Проценты не может быть меньше 0!" << endl;
        alcohol_percent = 0.0;
    }

    if (alcohol_percent > 100.0)
    {
        cout << "Проценты не может быть больше 100!" << endl;
        alcohol_percent = 100.0;
    }

    alcohol_content = current_volume * alcohol_percent / 100.0;

    cout << "Barrel constructor called for " << this
         << " with volume " << volume
         << " and alcohol " << alcohol_percent << "%" << endl;
}

Barrel::~Barrel()
{
    cout << "Barrel destructor called for " << this << endl;
}

double Barrel::get_total_volume() const
{
    return volume;
}

double Barrel::get_current_volume() const
{
    return current_volume;
}

double Barrel::get_alcohol_content() const
{
    return alcohol_content;
}

double Barrel::get_alcohol_percent() const
{
    if (current_volume == 0)
        return 0;
    return (alcohol_content / current_volume) * 100.0;
}

void Barrel::pour_from(Barrel &source, double amount)
{

    double alcohol_in_pour = amount * source.get_alcohol_percent() / 100.0;

    source.current_volume -= amount;
    source.alcohol_content -= alcohol_in_pour;

    this->current_volume += amount;
    this->alcohol_content += alcohol_in_pour;

    if (source.current_volume < 0)
        source.current_volume = 0;
    if (source.alcohol_content < 0)
        source.alcohol_content = 0;
    if (this->alcohol_content > this->current_volume)
    {
        this->alcohol_content = this->current_volume;
    }
}