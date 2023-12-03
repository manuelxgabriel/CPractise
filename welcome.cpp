// The intent of this walkthrough is to review module 14 concepts
//   and to introduce module 14+ concepts in a practical way.

// ========================================================
// PART 1 - Objectives:
// - overriding functions
// - making run time polymorphism work
// - using base class pointers/references with virtual methods
// - override keyword
// - virtual destructors
// ========================================================
//
// Setup a class hierarchy & some overrides:
// -----------------------------------------
// Create a UIElement class
// Implement a public method: enable() that prints "UIElement.enable()\n"
// Create 2 classes: Button & TextBox - both inherit from UIElement
// Override Button.enable() to print "Button.enable()\n"
// Override Textbox.enable() to print "TextBox.enable()\n"

#include <iostream>
#include <vector>

class UIElement {
public:
    virtual void enable() { std::cout <<"UIElement.enable()\n";}
};

class Button : public UIElement {
public:
    void enable() { std::cout << "Button.enable()\n";}
};

class Textbox : public UIElement {
public:
    void enable() { std::cout << "Textbox.enable()\n"; }
};


// Create a Dialog class
// Give it a protected std::vector of UIElements uiElements.
// Write a public method: enableUI() that calls enable() on all vector
// elements.

class Dialog {
protected:
    std::vector<UIElement*> uiElements;
public:
    void enableUI() {
        std::cout << "Dialog.EnableUI()\n";
        for(UIElement* element : uiElements){
            element->enable();
        }

    }
};


class IntroDialog : public Dialog {
private:
    Button btn1;
    Textbox text1;
public:
    IntroDialog(Button valueButton, Textbox valueText){
        uiElements.push_back(&valueButton);
        uiElements.push_back(&valueText);
    }
};



// Create an IntroDialog class (that inherits from Dialog)
// Give it private instances of Button btn1 and TextBox text1
// Implement a constructor that adds btn1 and text1 to the uiElements
// vector

// Enable Polymorphism (dynamic binding):
// --------------------------------------
// In main() instantiate a IntroDialog introDialog, and have it call enableUI();
// You should find it outputs:
//    UIElement.enable()
//    UIElement.enable()
// Polymorphism isn't working. How do we get it to output:
//    Button.enable()
//    Textbox.enable()
// Fix this!:
// Hint 1: Add the override keyword to Button.enable() and TextBox.enable()
//         to ensure our overrides are working correctly.
// Hint 2: What are the 2 requirements for dynamic polymorphism?
// Hint 3: You can't make a vector of references:
//         https://stackoverflow.com/questions/922360/why-cant-i-make-a-vector-of-references
//
// Explain how object slicing was preventing this setup from working.
//
// To illustrate why a base class destructor should always be virtual:
// ---------------------------------------------------------------
// Create a constructor & destructor for the Button class
// Output "btn.constructor()" and "btn.destructor()" in each.
// Create the UI elements in the IntroDialog on the heap instead of the
//  stack (have the uiElements vector keep track of them rather than
//  having individual vars).
// Write a destructor for IntroDialog that deallocates the elements.
// Run and observe the output
// Note the Button destructor is not called - If Button had used dyamically
// allocated memory internally, this would result in a memory leak!
// Fix this by adding a virtual destructor in the base class (UIElement).
// Run and observe the output - "btn.destructor()" should now be visible.


// ========================================================
// PART 2 - Objectives:
// - pure virtual functions
// - abstract classes
// ========================================================
//
// In IntroDialog():
//    Delete the lines that create UIElements on the heap
//    comment in the lines that created UIElements on the stack
//	  Delete the ~IntroDialog() (destructor)
//	We only used heap allocation to illustrate the need for a virtual
//    destructor in the base class.
//
// Prevent base class instantiation:
// ---------------------------------
// In main() instantiate a UIElement e directly.
// Would you ever need to do this?  No!
//
// *** GOAL #1: CAN WE PREVENT BASE CLASS INSTANCES FROM BEING CREATED? YES!
//
// - Make a base class constructor that is protected
//   Now only derived classes can use it
//   However, there is a better way though (which we'll see in a moment!)
//
// Force derived classes to implement an "interface":
// --------------------------------------------------
// Create a new class Scrollbar that derives from UIElement.
// Instantiate Scrollbar sbar in IntroDialog.
// Add it to the list of uiElements. Run!
// Observe when sbar.enable() was called it used the base version.
// There is (currently) no requirement that Scrollbar implement enable()
//   - result: UIElement.enable() is called.
//
// *** GOAL #2: CAN WE FORCE DERIVED CLASSES TO IMPLEMENT A METHOD?  YES!
//
// Make methods of the class pure virtual (no implementation)
// This makes UIElement an abstract class.
// No implementation means we can't instantiate it!
//
// The protected base class constructor (which prevented direct UIElement
//   instantiation is no longer needed (the fact that the class is now
//  abstract prevents instantiation).
// - Comment it out.
// Only derived classes that implement the base class interface
//   (the pure virtual functions) can be instantiated
// Try to compile.
// It fails: Scrollbar doesn't implement UIElement's interface (missing
//  enable()).  Fix it & ensure it works.
//
// Create another pure virtual function for UIElement: disable()
// Try to compile - it should fail.
// Why?  No derived classes (Button/TextBox/Scrollbar) implement disable().
// Implement disable() in all 3 derived classes
// Implement disableUI() in Dialog and call it in main().
//
// To accomplish both GOALS above, we used pure virtual functions to
// make UIElement into an abstract class.
//
// GOAL 1 accomplished: UIElement can't be instantiated.
// GOAL 2 accomplished: Derived classes are forced to implement a base
//                      class interface.

// To tidy things up:
//  Make Dialog.enableUI() & Dialog.disableUI() protected since we would
//  probably never want to call them directly.
//  Write a public Dialog.open() and have it call enableUI()
//  Write a public Dialog.close() and have it call disableUI()
//  Call IntroDialog.open() and IntroDialog.close() in main();

// You have just created a base Dialog class that sets up derived
// classes to automatically enable all ui elements when opened and
// disable them when closed!