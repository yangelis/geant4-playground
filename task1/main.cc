#include <vector>

// Task 4e.1: Look how different managers are aliased as RunManager.
//            (single- or multi-threaded depending on the condition)
#ifdef G4MULTITHREADED
    #include <G4MTRunManager.hh>
    using RunManager = G4MTRunManager;
#else
    #include <G4RunManager.hh>
    using RunManager = G4RunManager;
#endif

#ifdef G4VIS_USE
    #include <G4VisExecutive.hh>
#endif

#ifdef G4UI_USE
    #include <G4UIExecutive.hh>
#endif

#include <G4String.hh>
#include <G4UImanager.hh>

#include "ActionInitialization.hh"

// Task 1: See that we need to include the proper header
#include "DetectorConstruction.hh"
#include "PhysicsList.hh"

// Task 3b.4: Include (temporarily if you want) header for QGSP

// Task 4b.1: Include the proper header to enable scoring manager

// Task 4c.3: Include the proper header to enable analysis tools

using namespace std;

/* Main function that enables to:
 * - run any number of macros (put them as command-line arguments)
 * - start interactive UI mode (no arguments or "-i")
 */
int main(int argc, char** argv)
{
    std::cout << "Application starting..." << std::endl;

    vector<G4String> macros;
    bool interactive = false;

    // Parse command line arguments
    if  (argc == 1)
    {
        interactive = true;
    }
    else
    {
        for (int i = 1; i < argc; i++)
        {
            G4String arg = argv[i];
            if (arg == "-i" || arg == "--interactive")
            {
                interactive = true;
                continue;
            }
            else
            {
                macros.push_back(arg);
            }
        }
    }

    // Create the run manager (MT or non-MT) and make it a bit verbose.
    auto runManager = new RunManager();
    runManager->SetVerboseLevel(1);

    #ifdef G4VIS_USE
        G4VisManager* visManager = new G4VisExecutive();
        visManager->Initialize();
    #endif

    // Task 3b.4: Replace (only temporarily) PhysicsList with QGSP
    runManager->SetUserInitialization(new PhysicsList());

    // Task 1: See that we instantiate the detector construction here
    runManager->SetUserInitialization(new DetectorConstruction());
    runManager->SetUserInitialization(new ActionInitialization());

    #ifdef G4UI_USE
        G4UIExecutive* ui = nullptr;
        if (interactive)
        {
            ui = new G4UIExecutive(argc, argv);
        }
    #endif

    G4UImanager* UImanager = G4UImanager::GetUIpointer();

    // Task 4b.1: You need to access the scoring manager here (or above)

    for (auto macro : macros)
    {
        G4String command = "/control/execute ";
        UImanager->ApplyCommand(command + macro);
    }

    #ifdef G4UI_USE
        if (interactive)
        {
            if (ui->IsGUI())
            {
                UImanager->ApplyCommand("/control/execute macros/ui.mac");
            }
            else
            {
                UImanager->ApplyCommand("/run/initialize");
            }
            ui->SessionStart();
            delete ui;
        }
    #endif

    delete runManager;
    
    // Task 4c.3: Close the analysis output by uncommmenting the following lines
    // G4AnalysisManager* man = G4AnalysisManager::Instance();
    // man->CloseFile();

    std::cout << "Application successfully ended.\nBye :-)" << std::endl;

    return 0;
}
