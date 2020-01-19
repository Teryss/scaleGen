#include "obiektow.h"
#include <iostream>
#include <stdio.h>
#include <vector>
#include <cstdlib>
#include <sstream>
#include <string>
#include <numeric>
#include <limits>

using namespace std;

ScaleMode::ScaleMode(string output, char output2):skala(output), charOutput(output2)
{
}
ScaleMode::ScaleMode()
{
}

void ScaleMode::Load(){
    fill(begin(minor), end(minor), 0);
    //std::fill( std::begin( a ), std::end( a ), 0 );
    skala.clear();
    charOutput = ' ';
    cin.ignore();
    cout << "Scale you want to generate (scale: large letters, type: small, ex: Db major, F# aeolian): " << endl;
    getline(cin, skala);
    cout << "Do you want to see the scale in sharps or flats (sharps - s, flats -f): " << endl;
    cin >> charOutput;
}
//obiekt zaczyna od tej funkcji w dół
void ScaleMode::Seperate(){
    stringstream ssSkala(skala);
    while(getline(ssSkala, temp, ch)){
        skalaVec.push_back(temp);
    }
}

void ScaleMode::MatchRoot(){
    skala = skalaVec[0];
    minor[0] = false;
    for(int i = 0; i < 12; i++){
        if(skala == tonesUp[i] || skala == tonesDown[i]) {
          numbSkala = i;
          minor[0]= true;
        }
    }

}

void ScaleMode::MatchMode(){
    minor[1] = false;
    for(int i = 0; i < 7; i++){
        if(skalaVec[1] == modes[i]) {
          numbMode = i;
          minor[1] = true;
        }
    }
    if(skalaVec[1] == "ionian") {
      numbMode = 0;
      minor[1] = true;
    }else if(skalaVec[1] == "aeolian") {
      numbMode = 5;
      minor[1] = true;
    }
}

bool ScaleMode::CheckModeAndRoot(){
  if(minor[0] == false || minor[1] == false || !correctFlats){
    correctScale = false;
    skalaVec.clear();
  }else correctScale = true;
  return correctScale;
}

void ScaleMode::CheckFlatsSharps(){
    if(charOutput == 's') {
      flat = false;
      correctFlats = true;
    }else if (charOutput == 'f') {
      flat = true;
      correctFlats = true;
    }else correctFlats = false;
}

void ScaleMode::CreateScale(){
 tempInt = numbMode;
    for (int i = 0; i < 7; i++){
        skaleInt.push_back(numbSkala);
        if(tempInt > 6) tempInt -= 7;
        numbSkala += major[tempInt];
        if(numbSkala > 11) numbSkala -= 12;
        tempInt ++;
    }
}

void ScaleMode::OutputScale(){
    cout << "Scale:" << endl << skalaVec[0] << ": ";
    for (int i = 0; i < 7; i++){
        if(flat) cout << tonesDown[skaleInt[i]];
        else cout << tonesUp[skaleInt[i]];
        cout << " ";
    }
}

void ScaleMode::Chords(){
    cout << endl << "Triad chords that work with this scale: " << endl;

    tempInt=0;
    for (int i = 0; i < 7; i++){
        iX = i - 2;
        while (tempInt != 3){
            iX += 2;
            if(iX > 6) iX -=7;
            chordNotes[tempInt] = skaleInt[iX];
            tempInt++;
        }
        tempInt=0;
        //major or minor thirds in between notes
        for (int i=0; i < 2; i++){
          if (chordNotes[i+1] - chordNotes[i] < 3) chordNotes[i+1] += 12;
          if ((chordNotes[i+1] - chordNotes[i]) == 4) minor[i] = false;
          else minor[i] = true;
        }

        //deciding what is the type name of the chord
        if (flat) odp = tonesDown[skaleInt[i]];
        else odp = tonesUp[skaleInt[i]];

        if (minor [0] == true && minor[1] == false) cout << i+1 << " " << odp << " minor " << endl;
        if (minor [0] == false && minor[1] == true) cout << i+1 << " " << odp << " major " << endl;
        if (minor [0] == false && minor[1] == false) cout << i+1 << " " << odp << " augmented " << endl;
        if (minor [0] == true && minor[1] == true) cout << i+1 << " " << odp << " diminished " << endl;
    }

}

void ScaleMode::Seventh(){
    cout << endl << "Seventh chords that work with this scale: " << endl;

    tempInt=0;
    for (int i = 0; i < 7; i++){
        iX = i - 2;
        //creating chords and getting every note
        while (tempInt != 4){
            iX += 2;
            if(iX > 6) iX -=7;
            chordNotes[tempInt] = skaleInt[iX];
            tempInt++;
        }
        tempInt=0;
        //major or minor thirds in between notes
        for (int i=0; i < 3; i++){
          if (chordNotes[i+1] - chordNotes[i] < 3) chordNotes[i+1] += 12;
          if ((chordNotes[i+1] - chordNotes[i]) == 4) minor[i] = false;
          else minor[i] = true;
        }

        //deciding what notes to use to cout
        if (flat) odp = tonesDown[skaleInt[i]];
        else odp = tonesUp[skaleInt[i]];

        //deciding chord types
    if (minor [0] == true && minor[1] == false && minor [2] == true) cout << i+1 << " " << odp << " minor7 " << endl;
    if (minor [0] == false && minor[1] == true && minor[2] == false) cout << i+1 << " " << odp << " major7 " << endl;
    if (minor [0] == false && minor[1] == true && minor[2] == true) cout << i+1 << " " << odp << " 7 " << endl;
    if (minor [0] == false && minor[1] == false && minor[2] == false) cout << i+1 << " " << odp << " augmented7 " << endl;
    if (minor [0] == true && minor[1] == true && minor [2] == false) cout << i+1 << " " << odp << " diminished7 " << endl;
    }
}

void ScaleMode::AskForFindOutChordAndPrepare(){
  cout << "Enter 3 different notes of a chord (ex. C E G, F# A D): " << endl;
  cin.ignore();
  getline(cin, skala);
  stringstream ssSkala(skala);

  skalaVec.clear();
  while(getline(ssSkala, temp, ' ')){
    skalaVec.push_back(temp);
  }

  for(int i = 0; i < skalaVec.size(); i++){
    minor[i] = false;
    for(int x = 0; x < 12; x++){
      if(skalaVec[i] == tonesUp[x] || skalaVec[i] == tonesDown[x]){
        chordNotes[i] = x;
        minor[i] = true;
      }
    }
  }
}

bool ScaleMode::CheckNotes(){
  correctScale = true;
  if (minor[0] == false || minor[1] == false || minor[2] == false){
    cout << "I don't know this notes!" << endl;
    correctScale = false;
  }
  return correctScale;
}

void ScaleMode::Method1(){
  //making sure the loop will be executed
  for(int i = 0; i < skalaVec.size(); i++) correctNotesOrder[i] = false;
  tempInt = 0;

  while (correctNotesOrder[0] == false || correctNotesOrder[1] == false){
    //default values for correct notes
    for(int i = 0; i < skalaVec.size(); i++) correctNotesOrder[i] = true;

    //changing order of notes depending on which try to match it is
    for(int i = 0; i < skalaVec.size(); i++){
      iX = tempInt + i;
      /*if (tempInt > skalaVec.size() - 1){ //method2
        if (iX + methodOrder[i] > 2) iX -= 3;
        chordNotesMix[i] = chordNotes[iX + methodOrder[i]];
        chordNotes[i] = chordNotesMix[i];
      }*/
      if (iX > 2) iX -= 3;
      chordNotesMix[i] = chordNotes[iX];
      }
    }

    //checking if the order is correct and if yes, setting values to cout
    for(int i = 0; i < skalaVec.size(); i++){
      if (chordNotesMix[i+1] - chordNotesMix[i] < 3) chordNotesMix[i+1] += 12;
      if ((chordNotesMix[i+1] - chordNotesMix[i]) == 4) minor[i] = false;
      else if ((chordNotesMix[i+1] - chordNotesMix[i]) == 3) minor[i] = true;
      else correctNotesOrder[i] = false;
    }
}

void ScaleMode::CoutFoundChord(){
  //depending on input, prepare output
  if (flat) odp = tonesDown[chordNotesMix[0]];
  else odp = tonesUp[chordNotesMix[0]];

  //output
  if (minor [0] == true && minor[1] == false) cout << odp << " minor " << endl;
  if (minor [0] == false && minor[1] == true) cout << odp << " major " << endl;
  if (minor [0] == false && minor[1] == false) cout << odp << " augmented " << endl;
  if (minor [0] == true && minor[1] == true) cout << odp << " diminished " << endl;
}
