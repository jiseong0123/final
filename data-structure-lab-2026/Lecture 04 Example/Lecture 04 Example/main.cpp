#include <iostream>
#include "Rectangle.h"
#include "Pet.h"
#include "Music.h"
using namespace std;

int main() {
    Rectangle rect(5, 5);

    cout << "넓이: " << rect.getArea() << endl;
    cout << "둘레: " << rect.getPerimeter() << endl;

    if (rect.isSquare())
        cout << "정사각형입니다." << endl;
    else
        cout << "정사각형이 아닙니다." << endl;

    Pet myPet("Kong", 5, "Cat");
    cout << "My Pet's name is " << myPet.getName() << endl;

    Puppy myPuppy("Lucky", 10, "Dog", "Poodle");
    cout << "My puppy's breed is " << myPuppy.getBreed() << endl;

    MusicStreamingService myService("Melon");

    myService.addMusic("SWIM", "BTS", "ARIRANG", 2026);
    myService.addMusic("RUDE", "Hearts2Hearts", "RUDE", 2026);
    myService.addMusic("BANGBANG", "IVE", "REVIVE", 2026);
    myService.addMusic("JUMP", "BlackPink", "Jump", 2025);
    myService.addMusic("ShutDown", "BlackPink", "BornPink", 2025);

    string music_title;
    cout << "Enter the Music Title: ";
    cin >> music_title;

    Music* result = myService.searchByTitle(music_title);

    if (result != NULL) {
        cout << "Found: " << result->getTitle() << " by " << result->getArtist() << endl;
    }
    else {
        cout << "Not Found" << endl;
    }

    string artist_name;
    cout << "Enter the Artist Name: ";
    cin >> artist_name;

    vector<Music*> artistResult = myService.searchByArtist(artist_name);
    if (artistResult.size() > 0) {
        cout << "Found" << artistResult.size() << "song by" << artist_name << " :" << endl;
        for (int i = 0; i < artistResult.size(); i++) {
            cout << artistResult[i]->getTitle() << endl;
        }
    }
    else {
        cout << "Not Found " << endl;
    }
    return 0;
};