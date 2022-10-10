#include "GHepParticle.h"
#include "NtpMCEventRecord.h"
#include "PDGCodes.h"
#include "TGenPhaseSpace.h"

using namespace genie;

bool IsSingleElectron(const EventRecord* eventRecord);
bool IsSinglePositron(const EventRecord* eventRecord);
bool IsSinglePiZero(const EventRecord* eventRecord);
bool IsSinglePiPlus(const EventRecord* eventRecord);
bool IsSinglePiMinus(const EventRecord* eventRecord);

void analysis_v3(const char* mode="FHC", const char* beam="nue", const ULong64_t nevent=1e+6)
{
  TString infile_name;
  TString infile_prefix("gnout.ICARUS_");
  TString infile_mode(mode);
  TString infile_beam(beam);
  TString infile_suffix(".root");
  infile_name = infile_prefix + infile_mode + "_1M_" + infile_beam + infile_suffix;
  TString outfile_name;
  TString outfile_prefix("result_icarus_");
  TString outfile_suffix("_analysis.root");
  outfile_name = outfile_prefix + infile_mode + "_1M_" + infile_beam + outfile_suffix;

  TFile infile(infile_name);

  TString beamLatex;
  if( strcmp(beam, "numu") == 0 )
  {
    beamLatex = "#nu_{#mu}";
  }
  else if( strcmp(beam, "numubar") == 0 )
  {
    beamLatex = "#bar{#nu}_{#mu}";
  }
  else if( strcmp(beam, "nue") == 0 )
  {
    beamLatex = "#nu_{e}";
  }
  else if( strcmp(beam, "nuebar") == 0 )
  {
    beamLatex = "#bar{#nu}_{e}";
  }
  TH1D* energy_pi0 = new TH1D(Form("icarus_%s_pi0",      beam), Form("Beam: %s, %s / #pi^{0} Energy Spectrum;Energy (GeV);Entries", beamLatex.Data(), mode), 100, 0., 10.);
  TH1D* energy_eta = new TH1D(Form("icarus_%s_eta",      beam), Form("Beam: %s, %s / #eta Energy Spectrum;Energy (GeV);Entries", beamLatex.Data(), mode), 100, 0., 10.);
  TH1D* energy_rho = new TH1D(Form("icarus_%s_rho",      beam), Form("Beam: %s, %s / #rho Energy Spectrum;Energy (GeV);Entries", beamLatex.Data(), mode), 100, 0., 10.);
  TH1D* energy_elec = new TH1D(Form("icarus_%s_elec_E",    beam), "e- FHC", 100, 0., 10.);
  TH1D* energy_single_elec = new TH1D(Form("icarus_%s_single_elec_E",    beam), "e- FHC", 100, 0., 10.);
  TH1D* energy_digamma = new TH1D(Form("icarus_%s_digamma",      beam), "#gamma#gamma FHC", 100, 0., 10.);

  TTree* ghep_tree = dynamic_cast<TTree*>(infile.Get("gtree"));

  Long64_t nev = ghep_tree->GetEntries();
  genie::NtpMCEventRecord * mcrec = 0;
  ghep_tree->SetBranchAddress("gmcrec", &mcrec);

  GHepParticle* fpart;

  TLorentzVector neutralMesons;
  TLorentzVector *gamma1, *gamma2;
  TGenPhaseSpace event;
  Double_t masses[2] = {0., 0.}; // two photon decay

  EventRecord *myEvent;
  Int_t pionCount = 0;
  Int_t elecCount = 0;
  for(Long64_t i = 0; i <= nev-1; i++) {

    ghep_tree->GetEntry(i);
    myEvent = mcrec->event;

    // Process pion events
    pionCount = myEvent->NEntries(kPdgPi0, kIStStableFinalState); // kPdgPi0 == 111
    if( pionCount > 0 )
    {
      // loop over all pi0's in the event
      for( Int_t particlePosition = myEvent->ParticlePosition(kPdgPi0, kIStStableFinalState, 0);
          particlePosition != -1;
          particlePosition = myEvent->ParticlePosition(kPdgPi0, kIStStableFinalState, particlePosition+1))
      {
        fpart = myEvent->FindParticle(kPdgPi0, kIStStableFinalState, particlePosition);
        energy_pi0->Fill(fpart->E());

        // Process decay of pi0
        neutralMesons.SetPxPyPzE(fpart->Px(),
            fpart->Py(),
            fpart->Pz(),
            fpart->E());
        event.SetDecay(neutralMesons, 2, masses);
        Double_t weight = event.Generate();
        gamma1 = event.GetDecay(0);
        gamma2 = event.GetDecay(1);
        energy_digamma->Fill(gamma1->E());
        energy_digamma->Fill(gamma2->E());
      }
    }


    // Process electron events
    elecCount = myEvent->NEntries(kPdgElectron, kIStStableFinalState); // pdg code 11 == e-
    if( elecCount > 0 )
    {
      // loop over all electron's in the event
      for( Int_t particlePosition = myEvent->ParticlePosition(kPdgElectron, kIStStableFinalState, 0);
          particlePosition != -1;
          particlePosition = myEvent->ParticlePosition(kPdgElectron, kIStStableFinalState, particlePosition+1))
      {
        fpart = myEvent->FindParticle(kPdgElectron, kIStStableFinalState, particlePosition);
        energy_elec->Fill(fpart->E());
      }
    }
    if( elecCount == 1)
    {
      fpart = myEvent->FindParticle(kPdgElectron, kIStStableFinalState, 0);
      energy_single_elec->Fill(fpart->E());
    }
  }


  TFile* fOutput = new TFile(outfile_name, "recreate");
  energy_pi0->Write();
  energy_elec->Write();
  energy_single_elec->Write();
  energy_digamma->Write();

  fOutput->Close();

}

bool IsSingleElectron(const EventRecord* eventRecord)
{
  return eventRecord->NEntries(kPdgElectron, kIStStableFinalState);
}

bool IsSinglePositron(const EventRecord* eventRecord)
{
  return eventRecord->NEntries(kPdgPositron, kIStStableFinalState);
}

bool IsSinglePiZero(const EventRecord* eventRecord)
{
  return eventRecord->NEntries(kPdgPi0, kIStStableFinalState);
}

bool IsSinglePiPlus(const EventRecord* eventRecord)
{
  return eventRecord->NEntries(kPdgPiP, kIStStableFinalState);
}

bool IsSinglePiMinus(const EventRecord* eventRecord)
{
  return eventRecord->NEntries(kPdgPiM, kIStStableFinalState);
}
