#include "PrimaryGeneratorAction.hh"

#include <G4ParticleTable.hh>
#include <G4Event.hh>
#include <G4SystemOfUnits.hh>
#include <G4ParticleGun.hh>
#include <Randomize.hh>
#include <G4GeneralParticleSource.hh>

// Task 2b.1 Include the proper header file for GPS

using namespace std;

PrimaryGeneratorAction::PrimaryGeneratorAction()
{
    // Task 2b.1: Comment out the particle gun creation and instatiate a GPS instead
    //fGun = new G4ParticleGun();
    

    // Task 2a.1: Set the basic properties for the particles to be produced
    string sParticle = "e-";
    G4ParticleDefinition *myParticle = G4ParticleTable::GetParticleTable()->FindParticle(sParticle);
    //fGun->SetParticleDefinition(myParticle);
    G4double energy = 100.*MeV;
    //fGun->SetParticleEnergy(energy);
    //fGun->SetParticleMomentumDirection(G4ThreeVector(1.,0.,0.));
 
    // Task 2b.1: Set the same properties for the GPS (removing previous lines)
    // Task 2b.2: You can remove or keep the previous lines in the later stages
    
    
    
}

PrimaryGeneratorAction::~PrimaryGeneratorAction()
{
    // Task 2b.2: Delete the GPS instead of the gun
    //delete fGun;
    delete fGPS;
}

void PrimaryGeneratorAction::GeneratePrimaries(G4Event* anEvent)
{
    //// Task 2a.2: Include the position randomization
    //G4double x0=4.*cm, y0=4.*cm, z0 = 4.*cm;
    //G4double dx0 = 1.*cm, dy0 = 1.*cm, dz0 = 1.*cm;

    string sParticle = "e-";
    G4ParticleDefinition *myParticle = G4ParticleTable::GetParticleTable()->FindParticle(sParticle);
    G4double energy = 100.*MeV;
    //// Random initial coords
    //x0 += dx0*(G4UniformRand()-0.5);
    //y0 += dy0*(G4UniformRand()-0.5);
    //z0 += dz0*(G4UniformRand()-0.5);
    //fGun->SetParticlePosition(G4ThreeVector(x0,y0,z0));

    //// Task 2b.1: Comment out all previous commands in this method (there is no fGun!)
    //// Task 2b.1: The method for vertex creation remains the same,.just change the object to your GPS
    //fGun->GeneratePrimaryVertex(anEvent);
    fGPS = new G4GeneralParticleSource();
    fGPS->SetParticleDefinition(myParticle);
    fGPS->GetCurrentSource()->GetEneDist()->SetMonoEnergy(energy);
    fGPS->GetCurrentSource()->GetAngDist()->SetParticleMomentumDirection(G4ThreeVector(1.,0.,0.));
    fGPS->GetCurrentSource()->GetPosDist()->SetCentreCoords(G4ThreeVector(0,0,0));
}
