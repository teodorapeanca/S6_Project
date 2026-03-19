#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <chrono>

struct Pixel
{
    int r;
    int g;
    int b;
};

int main()
{
    std::ifstream file("C:\\Users\\teodo\\source\\repos\\ImageProcessingParallel\\x64\\Debug\\input.ppm");

    if (!file)
    {
        std::cout << "Nu s-a putut deschide imaginea!\n";
        return 1;
    }

    std::string format;
    int width, height, maxColor;

    file >> format;
    file >> width >> height;
    file >> maxColor;

    std::vector<Pixel> pixels;
    Pixel p;

    for (int i = 0; i < width * height; i++)
    {
        file >> p.r >> p.g >> p.b;
        pixels.push_back(p);
    }

    file.close();

    std::vector<Pixel> grayPixels(width * height);

    auto startSeq = std::chrono::high_resolution_clock::now();

    for (int i = 0; i < pixels.size(); i++)
    {
        int gray = (pixels[i].r + pixels[i].g + pixels[i].b) / 3;

        grayPixels[i].r = gray;
        grayPixels[i].g = gray;
        grayPixels[i].b = gray;
    }

    auto endSeq = std::chrono::high_resolution_clock::now();
    std::chrono::duration<double> durationSeq = endSeq - startSeq;

    std::cout << "Format imagine: " << format << std::endl;
    std::cout << "Latime: " << width << std::endl;
    std::cout << "Inaltime: " << height << std::endl;
    std::cout << "Valoare maxima culoare: " << maxColor << std::endl;
    std::cout << "Numar pixeli cititi: " << pixels.size() << std::endl;

    std::cout << "Primul pixel: "
        << pixels[0].r << " "
        << pixels[0].g << " "
        << pixels[0].b << std::endl;

    std::cout << "Primul pixel grayscale secvential: "
        << grayPixels[0].r << " "
        << grayPixels[0].g << " "
        << grayPixels[0].b << std::endl;

    std::cout << "Timp executie secvential: " << durationSeq.count() << " secunde" << std::endl;

    std::ofstream outFile("C:\\Users\\teodo\\source\\repos\\ImageProcessingParallel\\x64\\Debug\\output.ppm");

    if (!outFile)
    {
        std::cout << "Nu s-a putut crea fisierul de iesire!\n";
        return 1;
    }

    outFile << "P3\n";
    outFile << width << " " << height << "\n";
    outFile << maxColor << "\n";

    for (int i = 0; i < grayPixels.size(); i++)
    {
        outFile << grayPixels[i].r << " "
            << grayPixels[i].g << " "
            << grayPixels[i].b << "\n";
    }

    outFile.close();

    std::cout << "Imaginea grayscale a fost salvata in output.ppm" << std::endl;

    return 0;
}