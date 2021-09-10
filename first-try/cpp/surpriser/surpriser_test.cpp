#include "surpriser.hpp"

using namespace ilrd;

int main()
{
    Surpriser* todaysSurprise = Surpriser::GetRandomSurprise();

    todaysSurprise->SurpriseMe();

    delete todaysSurprise;

    return 0;
}