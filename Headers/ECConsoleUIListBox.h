//
//  ECConsoleUIListBox.h
//  
//
//  Created by Yufeng Wu on 5/23/23.
//

#ifndef ECConsoleUIListBox_h
#define ECConsoleUIListBox_h

#include <string>
#include <vector>

#include "ECConsoleUIItem.h"

//*****************************************************************************
// Console UI list box: several rows (items) to choose from

class ECConsoleUIListBox : public ECConsoleUIItem
{
public:
    // specifiy the portion of the view for this list box
    ECConsoleUIListBox(int xUL, int yUL, int xLR, int yLR );
    
    // Add a choice item
    void AddChoice(const std::string &text);
    
    // Choose an item
    void Choose(int rIndex);
    
    // Get the chosen one
    int GetChoice() const { return indexChoice; }
    
    // Get displayed text at a specific row
    // Text is relative to the item portion (i.e., relative to (xLR, yLR))
    virtual std::string GetTextAtRow(int r) const;
    
    // Get highlighted part (if any); return the row with highlight
    // if one, return -1; also store the highlightd portion (yLeft, yRight) of this row
    // Assume: at most a single row with highlighted part
    virtual int GetHighlightPosition(int &xLeft, int &xRight) const;

    // Are there any other function you might need to override?
    // Yes, overwrite IsHandlingKeys, HdlKeyUp, HldKeyDown, HdlKeyEnter, and HdlOtherKey
    virtual bool IsHandlingKeys() const;
    // Handle up key
    virtual void HdlKeyUp();
    // Handle down key
    virtual void HdlKeyDown();
    // Handle enter key
    virtual void HdlKeyEnter();
    // Handle other keys
    virtual void HdlOtherKey();

    // Clear the list box; for use in part 4
    void clearListBox();

    // Get the chosen string; for use in part 4
    std::string GetChosenString();
    
private:
    // list to hold choices (strings); each choice will get a single row
    std::vector<std::string> choices;
    // index of currently selected choice; this one will be highlighted
    int indexChoice;
};

#endif /* ECConsoleUIListBox_h */
