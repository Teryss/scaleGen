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

void ScaleMode::Load(){
    fill(begin(minor), end(minor), 0);
    root.clear();
    charOutput = ' ';
    cout << "Scale you want to generate (scale: large letters, type: small, ex: Db major, F# aeolian): " << endl;
    getline(cin, root);
    cout << "Do you want to see the scale in sharps or flats (sharps - s, flats -f): " << endl;
    cin >> charOutput;
}

void ScaleMode::Seperate(){
    stringstream ssSkala(root);
    while(getline(ssSkala, temp, ' ')){
        skalaVec.push_back(temp);
    }
}

void ScaleMode::MatchRoot(){
    root = skalaVec[0];
    failureControl[0] = false;
    for(int i = 0; i < 12; i++){
        if(root == sharps[i] || root == flats[i]) {
          numbSkala = i;
          failureControl[0]= true;
        }
    }
}

void ScaleMode::MatchMode(){
    failureControl[1] = false;
    for(int i = 0; i < 7; i++){
        if(skalaVec[1] == modes[i]) {
          numbMode = i;
          failureControl[1] = true;
        }
    }
    if(skalaVec[1] == "ionian") {
      numbMode = 0;
      failureControl[1] = true;
    }else if(skalaVec[1] == "aeolian") {
      numbMode = 5;
      failureControl[1] = true;
    }
}

void ScaleMode::CheckFlatsSharps(){
    if(charOutput == 's') {
      flat = false;
      failureControl[2] = true;
    }else if (charOutput == 'f') {
      flat = true;
      failureControl[2] = true;
    }else failureControl[2] = false;
}

void ScaleMode::Debug(){
  for (int i = 0; i < 3; i++){
    cout << "Fail " << i << ": " << failureControl[i] << endl;
  }
}

bool ScaleMode::CheckFailure(){
  if (failureControl[0] && failureControl[1] && failureControl[2]){
    return true;
  }
  else{
    cin.ignore();
    skalaVec.clear();
    cout << "Wrong input! Enter again! \n";
    return false;
  }
}

void ScaleMode::CreateScale(){
 counter = numbMode;
    for (int i = 0; i < 7; i++){
        notesNumber.push_back(numbSkala);
        if(counter > 6) counter -= 7;
        numbSkala += major[counter];
        if(numbSkala > 11) numbSkala -= 12;
        counter ++;
    }
}

void ScaleMode::OutputScale(){
    cout << "Scale:" << endl << root << " " << skalaVec[1] << ": ";
    for (int i = 0; i < 7; i++){
        if(flat) cout << flats[notesNumber[i]];
        else cout << sharps[notesNumber[i]];
        cout << " ";
    }
}

void ScaleMode::Chords(){
    cout << endl << "Triad chords that work with this scale: " << endl;

    counter=0;

//creating chord notes
    for (int i = 0; i < 7; i++){
        counter2 = i - 2;
        while (counter != 3){
            counter2 += 2;
            if(counter2 > 6) counter2 -=7;
            chordNotes[counter] = notesNumber[counter2];
            counter++;
        }

    counter=0;
//major or minor thirds in between notes
      for (int i=0; i < 2; i++){
      if (chordNotes[i+1] - chordNotes[i] < 3) chordNotes[i+1] += 12;
      if ((chordNotes[i+1] - chordNotes[i]) == 4) minor[i] = false;
      else minor[i] = true;
    }

//deciding what is the type name of the chord
      if (flat) odp = flats[notesNumber[i]];
      else odp = sharps[notesNumber[i]];

      if (minor [0] == true && minor[1] == false) cout << i+1 << " " << odp << " minor " << endl;
      if (minor [0] == false && minor[1] == true) cout << i+1 << " " << odp << " major " << endl;
      if (minor [0] == false && minor[1] == false) cout << i+1 << " " << odp << " augmented " << endl;
      if (minor [0] == true && minor[1] == true) cout << i+1 << " " << odp << " diminished " << endl;
  }

}

void ScaleMode::Seventh(){
    cout << endl << "Seventh chords that work with this scale: " << endl;

    counter=0;
    for (int i = 0; i < 7; i++){
        counter2 = i - 2;
        //creating chords and getting every note
        while (counter != 4){
            counter2 += 2;
            if(counter2 > 6) counter2 -=7;
            chordNotes[counter] = notesNumber[counter2];
            counter++;
        }
        counter=0;
        //major or minor thirds in between notes
        for (int i=0; i < 3; i++){
          if (chordNotes[i+1] - chordNotes[i] < 3) chordNotes[i+1] += 12;
          if ((chordNotes[i+1] - chordNotes[i]) == 4) minor[i] = false;
          else minor[i] = true;
        }

        //deciding what notes to use to cout
        if (flat) odp = flats[notesNumber[i]];
        else odp = sharps[notesNumber[i]];

        //deciding chord types
    if (minor [0] == true && minor[1] == false && minor [2] == true) cout << i+1 << " " << odp << " minor7 " << endl;
    if (minor [0] == false && minor[1] == true && minor[2] == false) cout << i+1 << " " << odp << " major7 " << endl;
    if (minor [0] == false && minor[1] == true && minor[2] == true) cout << i+1 << " " << odp << " 7 " << endl;
    if (minor [0] == false && minor[1] == false && minor[2] == false) cout << i+1 << " " << odp << " augmented7 " << endl;
    if (minor [0] == true && minor[1] == true && minor [2] == false) cout << i+1 << " " << odp << " diminished7 " << endl;
    }
    correctScale = true; //step for next method
}

void ScaleMode::AskForFindOutChordAndPrepare(){
  cout << "Enter 3 different notes of a chord (ex. C E G, F# A D): " << endl;
  if (correctScale) cin.ignore();
  getline(cin, root);
  stringstream ssSkala(root);

  skalaVec.clear();
  Seperate();

  for(int i = 0; i < skalaVec.size(); i++){
    failureControl[i] = false;
    for(int x = 0; x < 12; x++){
      if(skalaVec[i] == flats[x] || skalaVec[i] == sharps[x]){
        chordNotes[i] = x;
        failureControl[i] = true;
      }
    }
  }
}

bool ScaleMode::CheckNotes(){
  correctScale = true;
  if (!failureControl[0] || !failureControl[1] || !failureControl[2]){
    cout << "I don't know this notes!" << endl;
    correctScale = false;
  }
  return correctScale;
}

void ScaleMode::FindOutChord(){
//making sure the loop will be executed
  counter = 0;
  for(int i = 0; i < skalaVec.size(); i++) correctNotesOrder[i] = false;

  while (correctNotesOrder[0] == false || correctNotesOrder[1] == false){
    if(counter > 8) {
      cout << "Couldn't find the chord. Make sure you entered correct notes and try again!";
      break;
    }
    for(int i = 0; i < skalaVec.size(); i++) correctNotesOrder[i] = true;
    ScaleMode::Method1();
    ScaleMode::Check();
    //ScaleMode::Debug2();
    counter++;
  }

  if (flat) odp = flats[chordNotesMix[0]];
  else odp = sharps[chordNotesMix[0]];
}

void ScaleMode::Method1(){
  for(int i = 0; i < skalaVec.size(); i++){
    counter2 = counter + i;
    while (counter2 > 2) counter2 -= 3;
//cout << "i: " << i << "||" << "counter2: " << counter2 << endl;
    chordNotesMix[i] = chordNotes[counter2];
  }
//Method2
  if(counter > 2 && counter < 6){
    tempInt = chordNotesMix[1];
    chordNotesMix[1] = chordNotesMix[2];
    chordNotesMix[2] = tempInt;
  }
//Method3 (7th chords)
  if (counter > 6 && skalaVec.size() > 3){
    tempInt = chordNotesMix[2];
    chordNotesMix[2] = chordNotesMix[3];
    chordNotesMix[3] = tempInt;
  }
}

void ScaleMode::Debug2(){
  for (int i = 0; i < 3; i++){
    cout << "ChordNotesMix " << i << " : " << chordNotesMix[i] << endl;
    cout << "ChordNotes " << i << " : " << chordNotes[i] << endl;
  }
  cout << endl;
}

void ScaleMode::Check(){
  for(int i = 0; i < skalaVec.size(); i++){
    if (chordNotesMix[i+1] - chordNotesMix[i] < 3) chordNotesMix[i+1] += 12;
    if (i == 1){
      sus[0] = false;
      sus[1] = false;
      if (chordNotesMix[i+1] - chordNotesMix[i] == 2) sus[0] = true;
      if (chordNotesMix[i+1] - chordNotesMix[i] == 4) sus[1] = true;
    }else if (i == 2){
      if (chordNotesMix[2] - chordNotesMix[0] == 6)
    }
    if ((chordNotesMix[i+1] - chordNotesMix[i]) == 4) minor[i] = false;
    else if ((chordNotesMix[i+1] - chordNotesMix[i]) == 3) minor[i] = true;
    else correctNotesOrder[i] = false;
  }
}

void ScaleMode::CoutFoundChord(){

  //output
  if (counter <=  7){
    if(skalaVec.size() > 3){
      if (minor [0] == true && minor[1] == false && minor [2] == true) cout << odp << " minor7 " << endl;
      if (minor [0] == false && minor[1] == true && minor[2] == false) cout << odp << " major7 " << endl;
      if (minor [0] == false && minor[1] == true && minor[2] == true) cout << odp << " 7 " << endl;
      if (minor [0] == false && minor[1] == false && minor[2] == false) cout << odp << " augmented7 " << endl;
      if (minor [0] == true && minor[1] == true && minor [2] == false) cout << odp << " diminished7 " << endl;
    }else{
      if (minor [0] == true && minor[1] == false) cout << odp << " minor " << endl;
      if (minor [0] == false && minor[1] == true) cout << odp << " major " << endl;
      if (minor [0] == false && minor[1] == false) cout << odp << " augmented " << endl;
      if (minor [0] == true && minor[1] == true) cout << odp << " diminished " << endl;

      if (sus[0] == true || sus[1] == true){
        if (sus[0] == true && minor[1] == true) cout << odp << " sus2" << endl;
        if (sus[1] == true && minor[1] == true) cout << odp << " sus4" << endl;
      }
    }
  }
}
