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
    bool failureControl[3];
    std::string sharps[12] = {"A", "A#", "B", "C", "C#", "D", "D#", "E", "F", "F#", "G", "G#"};
    std::string flats[12] = {"A", "Bb", "B", "C", "Db", "D", "Eb", "E", "F", "Gb", "G", "Ab"};
    std::string modes[7] = {"major", "dorian", "phrygian", "lydian", "mixolydian", "minor", "locrian"};
    int major[8] = {2, 2, 1, 2, 2, 2, 1};
    int chordNotes[4];
    int chordNotesMix[4];
    vector<int> notesNumber;
    std::vector<string> skalaVec;
    std::string root,odp,temp;
    char charOutput;
    int numbSkala, numbMode, counter, counter2, tempInt;
    bool flat, correctScale;
    bool minor[3];
    bool correctNotesOrder[3];
    bool sus[2];

public:

    void Load(); //loading input
    void Seperate(); //seperate input
    void MatchRoot(); //match scale root
    void MatchMode(); //match scale mode
    void CheckFlatsSharps(); //check if a scale root is a sharp or flat
    void Debug();
    void Debug2();
    bool CheckFailure(); //check for bad input
    void CreateScale(); //creating a scale and moving it into a vector
    void OutputScale(); //reading the numbers from vector, matching the letters for numbers and outputing
    void Chords(); //create, decide the type and output chords
    void Seventh(); //chords but with 4th additional note (7th chords)
    void AskForFindOutChordAndPrepare(); //finds out chord by notes
    bool CheckNotes(); //checks notes before looking for a chord
    void FindOutChord(); //sorting notes
    void Check(); //checking if the notes match a chord
    void Method1(); //changing the notes order and commpare
    void Method2(); //changing the notes sequence and compare
    void CoutFoundChord(); //outputing found chord
};
#endif /* OBIEKTOW_H_ */
