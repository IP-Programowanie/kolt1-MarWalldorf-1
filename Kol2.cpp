#include "Wybor.h"

using namespace std;

/*
* Uwaga: Zadania kod rozwiazania zaania umieszczać pomiędzy #ifdef a #endif.
*/

#ifdef Kol_2
#define _CRT_SECURE_NO_WARNINGS
#include <iostream>
#include <cstring>
#include <cmath>
#include <stdexcept>
using namespace std;
class Wlasciciel {};
class Samochod
{
protected:
    char numerRejestracyjny[20]; 
    double stanLicznika;
    bool stanDopuszczenia;
    Wlasciciel wlasciciel;
    static Samochod* wzorcowySamochod;
    static constexpr double MIN_WARTOSC = 400;
public:
    Samochod(const char* numerRejestracyjny, double stanLicznika, bool stanDopuszczenia, const Wlasciciel& wlasciciel)
        : stanLicznika(stanLicznika), stanDopuszczenia(stanDopuszczenia), wlasciciel(wlasciciel)
    {
        strncpy(this->numerRejestracyjny, numerRejestracyjny, 20);
        this->numerRejestracyjny[19] = '\0'; 
    }
    Samochod() : stanLicznika(0), stanDopuszczenia(false), wlasciciel(Wlasciciel())
    {
        numerRejestracyjny[0] = '\0'; 
        if (wzorcowySamochod) {
            strncpy(numerRejestracyjny, wzorcowySamochod->numerRejestracyjny, 20);
            stanLicznika = wzorcowySamochod->stanLicznika;
            stanDopuszczenia = wzorcowySamochod->stanDopuszczenia;
            wlasciciel = wzorcowySamochod->wlasciciel;
        }
        else
        {
                     throw runtime_error("Brak wzorcowego samochodu");
        }
    }
    void setStanLicznika(double stan)
    {
        if (stan < 0) throw invalid_argument("Stan licznika nie moze byc ujemny");
        stanLicznika = stan;
    }
    double getStanLicznika() const
    {
        return stanLicznika;
    }
    virtual double obliczWartosc(double WAR_POC, double WSP_SPRAW) const
    {
        double wartosc = (WAR_POC - 0.2 * stanLicznika)* WSP_SPRAW;
        if (wartosc<400)
        {
            throw runtime_error("Wartosc nie moze byc mniejsza niz 400");
        }
        else
        {
            return (WAR_POC - 0.2 * stanLicznika) * WSP_SPRAW;
        }
    }
    virtual double obliczZasieg() const
    {
        if (!stanDopuszczenia) throw runtime_error("Samochod niedopuszczony do jazdy!");
        return 800;
    }
    static void setWzorcowySamochod(Samochod* wzorzec)
    {
        wzorcowySamochod = wzorzec;
    }
};
Samochod* Samochod::wzorcowySamochod = nullptr;
class SamochodElektryczny : public Samochod
{
private:
    double stanBaterii;

public:
    SamochodElektryczny(const char* numerRejestracyjny, double stanLicznika, bool stanDopuszczenia, const Wlasciciel& wlasciciel, double stanBaterii)
        : Samochod(numerRejestracyjny, stanLicznika, stanDopuszczenia, wlasciciel), stanBaterii(stanBaterii) {}
    SamochodElektryczny() : Samochod(), stanBaterii(100) {}
    double obliczWartosc(double WAR_POCZ, double WSP_SPRAW) const override
    {
        double wartosc = (WAR_POCZ - 0.2 * getStanLicznika()) * WSP_SPRAW;
        if (!stanDopuszczenia)
        {
            wartosc *= 0.7;
        }
        return wartosc;
    }
    double obliczZasieg() const override
    {
        if (stanBaterii > 100|| stanBaterii<0)
        {
            throw runtime_error("Samochod nie moze miec powyzej 100 lub ponizej 0 procent baterii");
        }
        
        if (!stanDopuszczenia) throw runtime_error("Samochod niedopuszczony do jazdy");
        return 2.5 * stanBaterii;
    }
    double getStanBaterii() const
    {

        return stanBaterii;
    }
};
bool operator!=(const Samochod& lhs, const Samochod& rhs)
{
    return fabs(lhs.getStanLicznika() - rhs.getStanLicznika()) > 20;
}
int main()
{
    setlocale(LC_ALL, "");
    Wlasciciel wlasciciel;
    Samochod wzorcowySamochod("XYZ123", 100, true, wlasciciel);
    Samochod::setWzorcowySamochod(&wzorcowySamochod);
    Samochod samochod1;
    SamochodElektryczny samochodElektryczny1;
    double wartoscSamochod1 = samochod1.obliczWartosc(10000, 1.0);
    double wartoscSamochodElektryczny1 = samochodElektryczny1.obliczWartosc(10000, 0.7);
    cout << "Wartosc Samochod1: " << wartoscSamochod1 << endl;
    cout << "Wartosc SamochodElektryczny1: " << wartoscSamochodElektryczny1 << endl;
    try {
        double zasiegSamochod1 = samochod1.obliczZasieg();
        double zasiegSamochodElektryczny1 = samochodElektryczny1.obliczZasieg();

        cout << "Zasieg Samochod1: " << zasiegSamochod1 << endl;
        cout << "Zasieg SamochodElektryczny1: " << zasiegSamochodElektryczny1 << endl;
    }
    catch (const runtime_error& e)
    {
        cout << "Blad obliczania zasiegu: " << e.what() << endl;
    }
    if (samochod1 != samochodElektryczny1)
    {
        cout << "Samochody różnią się stanem licznika o więcej niż 20 km." << endl;
    }
    else
    {
        cout << "Samochody mają podobny stan licznika." << endl;
    }
    return 0;
}
#endif
