#include "Weather.h"
#include <cstdlib>

Weather::Weather() {
    current = rand()%5 + 1;
}

int Weather::GetWeather() {
    return current;
}

void Weather::UpdateWeather() {
    int dice = rand()%10;
    switch (current) {
        case 1:
            if (dice < 1) current = current;
            else if (dice < 4) current = 1;
            else if (dice < 8) current = 5;
            else current = 4;
            break;
        case 2:
            if (dice < 2) current = current;
            else if (dice < 5) current = 1;
            else if (dice < 8) current = 5;
            else if (dice < 9) current = 3;
            else current = 4;
            break;
        case 3:
            if (dice < 1) current = current;
            else if (dice < 4) current = 5;
            else if (dice < 6) current = 1;
            else if (dice < 9) current = 4;
            else current = 2;
            break;
        case 4:
            if (dice < 2) current = current;
            else if (dice < 4) current = 5;
            else if (dice < 7) current = 1;
            else if (dice < 9) current = 3;
            else current = 2;
            break;
        case 5:
            if (dice < 2) current = current;
            else if (dice < 4) current = 1;
            else if (dice < 6) current = 2;
            else if (dice < 8) current = 3;
            else current = 4;
            break;

    }
    return;
}
