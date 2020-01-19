#ifndef OBIEKTOW_H_
#define OBIEKTOW_H_

#include <iostream>
#include <vector>
#include <stdio.h>
#include <cstdlib>
#include <string>
#include <sstream>
#include <numeric>
#include <limits>

using namespace std;

class ScaleMode{
    std::string tonesUp[12] = {"A", "A#", "B", "C", "C#", "D", "D#", "E", "F", "F#", "G", "G#"};
    std::string tonesDown[12] = {"A", "Bb", "B", "C", "Db", "D", "Eb", "E", "F", "Gb", "G", "Ab"};
    std::string modes[7] = {"major", "dorian", "phrygian", "lydian", "mixolydian", "minor", "locrian"};
    int major[8] = {2, 2, 1, 2, 2, 2, 1};
    int methodOrder[3] = {0, 1, -1};
    int chordNotes[4];
    int chordNotesMix[4];
    vector<int> skaleInt;
    std::vector<string> skalaVec;
    std::string skala,odp,temp;
    char ch = ' ', charOutput;
    int numbSkala, numbMode, tempInt, iX;
    bool flat = false;
    bool minor[3];
    bool correctNotesOrder[3];
    bool correctScale, correctFlats;

public:

    ScaleMode(string, char);
    ScaleMode();

    void Load(); //loading input
    void Seperate(); //seperating every word
    void MatchRoot(); //matching input to a scale root
    void MatchMode(); //matching input to a musical mode
    bool CheckModeAndRoot(); //checking for a match
    void CheckFlatsSharps(); //check if a scale root is a sharp or flat
    void CreateScale(); //creating a scale and moving it into a vector
    void OutputScale(); //reading the numbers from vector, matching the letters for numbers and outputing
    void Chords(); //create, decide the type and output chords
    void Seventh(); //chords but with 4th additional note
    void AskForFindOutChordAndPrepare(); //finds out chord by notes
    bool CheckNotes(); //checks notes before looking for a chord
    void FindOutChord();
    void Check();
    void Method1(); //changing the notes order and commpare
    void Method2(); //changing the notes sequence and compare
    void CoutFoundChord(); //outputing found chord
};
#endif /* OBIEKTOW_H_ */
