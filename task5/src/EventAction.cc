#include "EventAction.hh"

#include <G4SDManager.hh>
#include <G4THitsMap.hh>
#include <G4SystemOfUnits.hh>
#include <G4Event.hh>

#include "Analysis.hh"

using namespace std;

void EventAction::EndOfEventAction(const G4Event* event)
{
    G4SDManager* sdm = G4SDManager::GetSDMpointer();
    G4AnalysisManager* analysis = G4AnalysisManager::Instance();

    // FIXMETask 4c.2: Get the hit collections
 G4HCofThisEvent* hcofEvent = event->GetHCofThisEvent();

    // If there is no hit collection, there is nothing to be done
    if(!hcofEvent) return;

    // The variable fWaterTankId is initialized to -1 (see EventAction.hh) so this block 
    // of code is executed only at the end of the first event. After the first execution 
    // fAbsorberId gets a non-negative value and this block is skipped for all subsequent 
    // events.

    // Task 5: retrieve fWaterTankId. How is the hit collection named?
    // As before, fScintillatorId is defined in EventAction.hh and initialized to -1
 if (fWaterTankId < 0)
    {
      fWaterTankId = sdm->GetCollectionID("waterTank/energy");      
      G4cout << "EventAction: waterTank  energy scorer ID: " << fWaterTankId << G4endl;
    }

    G4int histogramId = 1;     // Note: We know this but in principle, we should ask


    if (fWaterTankId >= 0)
    {

      G4THitsMap<G4double>* hitMapWaterTank = nullptr; 
      //hitMapWaterTank = dynamic_cast<G4THitsMap<G4double>*>(------------));


      if (hitMapWaterTank)
      {
          for (auto pair : *(hitMapWaterTank->GetMap()))
          {
              G4double energy = *(pair.second);
	      //We have to associate the position of the center of thefirst slice to
	      //the origin of our histogram
	      //The position of the center of the i-th slice is given by
	      //0.25 * cm + sliceNmber; 
              //The slice  thickness is 0.1*cm. See line 53 of DetectorConstruction.cc
	      
	      //In short:
	      G4double x = 0.25 + (pair.first * 1.0); // in cm
	     	      
	      // Task 5. Store the position to the histogram
	      //analysis->FillH1(histogramId, x, INSERT_HERE_THE_VARIABLE_ENERGY / keV);

          }
      }

    }
}
