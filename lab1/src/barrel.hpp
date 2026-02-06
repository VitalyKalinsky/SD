#ifndef BARREL_HPP
#define BARREL_HPP

class Barrel
{
private:
    double volume;
    double current_volume;
    double alcohol_content;

public:
    Barrel();
    Barrel(double total_volume, double alcohol_percent = 0);
    ~Barrel();

    double get_total_volume() const;
    double get_current_volume() const;
    double get_alcohol_content() const;
    double get_alcohol_percent() const;

    void pour_from(Barrel &source, double amount);
};

#endif