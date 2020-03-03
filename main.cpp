#include <iostream>
#include <string>

#include "obiektow.cpp"

using namespace std;

int main()
{

    ScaleMode s1;
    do{
      s1.Load();
      s1.Seperate();
      s1.MatchRoot();
      s1.MatchMode();
      s1.CheckFlatsSharps();
      //s1.Debug();
    }while(!s1.CheckFailure());

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
