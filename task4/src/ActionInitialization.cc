#include "ActionInitialization.hh"
#include "PrimaryGeneratorAction.hh"
//! Optional user classes
#include "RunAction.hh"
#include "StackingAction.hh"
// Task 4a.2: Include the header for SteppingAction
#include "SteppingAction.hh"
// Task 4c.2: Include the header for EventAction
#include "EventAction.hh"

void ActionInitialization::Build() const
{
  SetUserAction(new PrimaryGeneratorAction());
  /* These two classes are used only in task3-4.*/
  RunAction *theRunAction = new RunAction();
  SetUserAction(theRunAction);
  SetUserAction(new StackingAction(theRunAction));

  // Task 4a.2: Add a properly initialized instance of SteppingAction
  SetUserAction(new SteppingAction(theRunAction));
  // Task 4c.2: Add a properly initialized instance of EventAction
  SetUserAction(new EventAction());
}

void ActionInitialization::BuildForMaster() const
{
  // By default, don't do anything. This applies only in MT mode:
  SetUserAction(new RunAction());
}
