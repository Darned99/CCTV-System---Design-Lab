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



#include "camera.h"
#include <opencv2/opencv.hpp>
#include <iostream>

int main() {
    // Ścieżki do klasyfikatorów Haar
    std::string faceCascadePath = cv::data::haar_cascades + "haarcascade_frontalface_default.xml";
    std::string bodyCascadePath = cv::data::haar_cascades + "haarcascade_fullbody.xml";

    // Tworzenie obiektów kamer
    Camera camera1(0, "Kamera 1", faceCascadePath, bodyCascadePath, "video1.mp4");
    Camera camera2(1, "Kamera 2", faceCascadePath, bodyCascadePath, "video2.mp4");

    // Otwieranie kamer
    if (!camera1.open() || !camera2.open()) {
        std::cerr << "Nie udało się otworzyć jednej lub obu kamer." << std::endl;
        return -1;
    }

    while (true) {
        cv::Mat frame1, frame2;

        // Przechwytywanie obrazu
        camera1.capture >> frame1;
        camera2.capture >> frame2;

        if (frame1.empty() || frame2.empty()) {
            std::cerr << "Błąd przechwytywania obrazu." << std::endl;
            break;
        }

        // Detekcja twarzy i ciał
        camera1.detectAndDisplay(frame1);
        camera2.detectAndDisplay(frame2);

        // Zapis do pliku wideo
        camera1.writeToFile(frame1);
        camera2.writeToFile(frame2);

        // Wyświetlanie kamer
        camera1.showFrame(frame1);
        camera2.showFrame(frame2);

        // Zakończenie programu po naciśnięciu 'q'
        if (cv::waitKey(1) == 'q') {
            break;
        }
    }

    // Zwolnienie zasobów
    camera1.release();
    camera2.release();
    cv::destroyAllWindows();

    return 0;
}