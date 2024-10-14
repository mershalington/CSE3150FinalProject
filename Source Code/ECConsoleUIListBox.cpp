//
//  ECConsoleUIListBox.cpp
//  
//
//  Created by Yufeng Wu on 5/23/23.
//

#include "ECConsoleUIListBox.h"

ECConsoleUIListBox::ECConsoleUIListBox(int xUL, int yUL, int xLR, int yLR) : ECConsoleUIItem(xUL, yUL, xLR, yLR), indexChoice(0) {}

// Add a choice item
void ECConsoleUIListBox::AddChoice(const std::string &text) {
    // simply push string to choices vector
    choices.push_back(text);
}

// Choose an item
void ECConsoleUIListBox::Choose(int rIndex) {
    // assign new index to indexChoice, as long as new index is within vector bounds
    indexChoice = (rIndex < choices.size() && rIndex >= 0)? rIndex : indexChoice;
}
    
// Get displayed text at a specific row
// Text is relative to the item portion (i.e., relative to (xLR, yLR))
std::string ECConsoleUIListBox::GetTextAtRow(int r) const {
    // create string, this is what we will be returning
    std::string textToReturn;

    // r represents the row offset with respect to the beginning of the console (ie. the absolute row number)

    // calculate the row offset relative to the start of the listbox, and make sure it is:
    // 1) >= 0 AND < height of listBox
    // 2) < total number of choices
    // if either condition fails, return empty string
    int listBoxRelativeOffset = r - GetYUL();

    if (listBoxRelativeOffset < 0 || listBoxRelativeOffset >= GetHeight() || listBoxRelativeOffset >= choices.size()) {
        return textToReturn;
    }

    // now calculate the index of the string to return within choices vector by adding the relative offset to the current indexChoice
    // we assume here that the first row displayed in the List Box is ALWAYS the selected choice (ie. the item currently indexed by indexChoice)
    // Professor Wu said he was ok with this approach
    int indexToReturn = indexChoice + listBoxRelativeOffset;

    // make sure the index of the string to return does not fall outside vector bounds; return empty string if it does
    if (indexToReturn >= choices.size()) {
        return textToReturn;
    }

    // grab string from choices vector, make sure it fits in List Box, and return
    textToReturn = choices[indexChoice + listBoxRelativeOffset];
    textToReturn = textToReturn.substr(0, GetWidth());
    return textToReturn;
}
    
// Get highlighted part (if any); return the row with highlight
// if one, return -1; also store the highlightd portion (yLeft, yRight) of this row
// Assume: at most a single row with highlighted part
int ECConsoleUIListBox::GetHighlightPosition(int &xLeft, int &xRight) const {
    // via testing, xLeft and xRight represent bounds on the portion of the row to highlight, relative to the start of the List Box
    // ie. 0 represents the start of the text, GetWidth()-1 represents the end of the text
    // the return value represents the row offset relative to the start of the List Box
    // ie. if we want to always highlight the first row, simply return 0

    // highlight the whole row
    xLeft = 0;
    xRight = GetWidth()-1;

    // highlight the first row
    return 0;
}

// Does the list box handle key presses? Yes...
bool ECConsoleUIListBox::IsHandlingKeys() const {
    return true;
}
    
// Handle up key
void ECConsoleUIListBox::HdlKeyUp() {
    Choose(indexChoice-1);
}

// Handle down key
void ECConsoleUIListBox::HdlKeyDown() {
    Choose(indexChoice+1);
}

// Handle enter key
void ECConsoleUIListBox::HdlKeyEnter() {
    // do nothing for now; I'll just assume that the one which is currently 'chosen' and highlighted is the one that will be selected
}
    
// Handle other keys
void ECConsoleUIListBox::HdlOtherKey() {
    // do nothing for now
}

// Clear list box
void ECConsoleUIListBox::clearListBox() {
    choices.clear();

    // reset indexChoice
    indexChoice = 0;
}

// Get the chosen string
std::string ECConsoleUIListBox::GetChosenString() {
    return choices[indexChoice];
}