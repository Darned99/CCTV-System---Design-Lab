/**
 * Wywołanie funkcji z camera.cpp, aby zainicjować kamerę, wyświetlić strumień wideo i obsłużyć potencjalne błędy.
 * Ten plik będzie koordynował interakcję użytkownika z modułem kamery
 */

/**
 *  Wywołanie initializeCamera() z konfiguracja pliku
 *  Wywołąnie streamVideo(), obsługa wejść użytkownika (np. klawisz do zakończenia programu)
 *  Zamykanie kamery i czyszczenie zasobów po zakończeniu programu
 * 
 */



#include <iostream>
#include <opencv2/opencv.hpp>
#include "camera.h"

int main() {
    
    Camera camera1(0, "Kamera 1");
    Camera camera2(1, "Kamera 2");

    if (!camera1.open() || !camera2.open()) {
        std::cerr << "Błąd inicjalizacji kamer." << std::endl;
        return -1;
    }

    while (true) {

        camera1.showFrame();
        camera2.showFrame();

        if (cv::waitKey(1) == 'q'){
            break;
        }
    }

    return 0;
}


