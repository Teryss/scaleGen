#include <iostream>
#include <string>

#include "obiektow.cpp"

using namespace std;

int main()
{
  string output;
  char output2;
  bool correct=false;

    cout << "Scale you want to generate (scale: large letters, type: small, ex: Db major, F# aeolian): " << endl;
    getline(cin, output);
    cout << "You want notes flat or sharp?(flats - f, sharps -s):" << endl;
    cin >> output2;

    ScaleMode s1(output, output2);

    s1.Seperate();
    s1.MatchRoot();
    s1.MatchMode();
    s1.CheckFlatsSharps();
    correct = s1.CheckModeAndRoot();
    while(!correct){
      cout << "Wrong scale root or mode or letter for flats/sharps! Enter again!" << endl;
      s1.Load();
      s1.Seperate();
      s1.MatchRoot();
      s1.MatchMode();
      s1.CheckFlatsSharps();
      correct = s1.CheckModeAndRoot();
    }
    s1.CreateScale();
    s1.OutputScale();
    s1.Chords();
    s1.Seventh();
    do{
      s1.AskForFindOutChordAndPrepare();
    }while(!s1.CheckNotes());
    s1.FindOutChord();
    s1.CoutFoundChord();

    return 0;
}
