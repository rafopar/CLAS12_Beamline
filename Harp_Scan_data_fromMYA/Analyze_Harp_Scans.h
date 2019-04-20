//////////////////////////////////////////////////////////
// This class has been automatically generated on
// Fri Apr 19 16:25:58 2019 by ROOT version 6.16/00
// from TChain Analyze_Harp_Scans/
//////////////////////////////////////////////////////////

#ifndef Analyze_Harp_Scans_h
#define Analyze_Harp_Scans_h

#include <TROOT.h>
#include <TChain.h>
#include <TFile.h>

// Header file for the classes stored in the TTree if any.

class Analyze_Harp_Scans {
public :
   TTree          *fChain;   //!pointer to the analyzed TTree or TChain
   Int_t           fCurrent; //!current Tree number in a TChain

// Fixed size dimensions of array or collections stored in the TTree if any.

   // Declaration of leaf types
   Long64_t        time;
   Double_t        mean_x;
   Double_t        mean_y;
   Double_t        mean_45;
   Double_t        sigma_x;
   Double_t        sigma_y;
   Double_t        sigma_45;
   Double_t        peak_x;
   Double_t        peak_y;
   Double_t        peak_45;
   Double_t        bgr_to_peak_x;
   Double_t        bgr_to_peak_y;
   Double_t        bgr_to_peak_45;
   Double_t        counter;
   Double_t        a;
   Double_t        b;
   Double_t        alpha;

   // List of branches
   TBranch        *b_time;   //!
   TBranch        *b_mean_x;   //!
   TBranch        *b_mean_y;   //!
   TBranch        *b_mean_45;   //!
   TBranch        *b_sigma_x;   //!
   TBranch        *b_sigma_y;   //!
   TBranch        *b_sigma_45;   //!
   TBranch        *b_peak_x;   //!
   TBranch        *b_peak_y;   //!
   TBranch        *b_peak_45;   //!
   TBranch        *b_bgr_to_peak_x;   //!
   TBranch        *b_bgr_to_peak_y;   //!
   TBranch        *b_bgr_to_peak_45;   //!
   TBranch        *b_counter;   //!
   TBranch        *b_a;   //!
   TBranch        *b_b;   //!
   TBranch        *b_alpha;   //!

   Analyze_Harp_Scans(TTree *tree=0);
   virtual ~Analyze_Harp_Scans();
   virtual Int_t    Cut(Long64_t entry);
   virtual Int_t    GetEntry(Long64_t entry);
   virtual Long64_t LoadTree(Long64_t entry);
   virtual void     Init(TTree *tree);
   virtual void     Loop();
   virtual Bool_t   Notify();
   virtual void     Show(Long64_t entry = -1);
};

#endif

#ifdef Analyze_Harp_Scans_cxx
Analyze_Harp_Scans::Analyze_Harp_Scans(TTree *tree) : fChain(0) 
{
// if parameter tree is not specified (or zero), connect the file
// used to generate this class and read the Tree.
   if (tree == 0) {

#ifdef SINGLE_TREE
      // The following code should be used if you want this class to access
      // a single tree instead of a chain
      TFile *f = (TFile*)gROOT->GetListOfFiles()->FindObject("Memory Directory");
      if (!f || !f->IsOpen()) {
         f = new TFile("Memory Directory");
      }
      f->GetObject("Analyze_Harp_Scans",tree);

#else // SINGLE_TREE

      // The following code should be used if you want this class to access a chain
      // of trees.
      TChain * chain = new TChain("Analyze_Harp_Scans","");
      
      //chain->Add("./tagger_scans.root/tr1");
      //chain->Add("./2C21_scans.root/tr1");
      chain->Add("./2H01_scans.root/tr1");
      tree = chain;
#endif // SINGLE_TREE

   }
   Init(tree);
}

Analyze_Harp_Scans::~Analyze_Harp_Scans()
{
   if (!fChain) return;
   delete fChain->GetCurrentFile();
}

Int_t Analyze_Harp_Scans::GetEntry(Long64_t entry)
{
// Read contents of entry.
   if (!fChain) return 0;
   return fChain->GetEntry(entry);
}
Long64_t Analyze_Harp_Scans::LoadTree(Long64_t entry)
{
// Set the environment to read one entry
   if (!fChain) return -5;
   Long64_t centry = fChain->LoadTree(entry);
   if (centry < 0) return centry;
   if (fChain->GetTreeNumber() != fCurrent) {
      fCurrent = fChain->GetTreeNumber();
      Notify();
   }
   return centry;
}

void Analyze_Harp_Scans::Init(TTree *tree)
{
   // The Init() function is called when the selector needs to initialize
   // a new tree or chain. Typically here the branch addresses and branch
   // pointers of the tree will be set.
   // It is normally not necessary to make changes to the generated
   // code, but the routine can be extended by the user if needed.
   // Init() will be called many times when running on PROOF
   // (once per file to be processed).

   // Set branch addresses and branch pointers
   if (!tree) return;
   fChain = tree;
   fCurrent = -1;
   fChain->SetMakeClass(1);

   fChain->SetBranchAddress("time", &time, &b_time);
   fChain->SetBranchAddress("mean_x", &mean_x, &b_mean_x);
   fChain->SetBranchAddress("mean_y", &mean_y, &b_mean_y);
   fChain->SetBranchAddress("mean_45", &mean_45, &b_mean_45);
   fChain->SetBranchAddress("sigma_x", &sigma_x, &b_sigma_x);
   fChain->SetBranchAddress("sigma_y", &sigma_y, &b_sigma_y);
   fChain->SetBranchAddress("sigma_45", &sigma_45, &b_sigma_45);
   fChain->SetBranchAddress("peak_x", &peak_x, &b_peak_x);
   fChain->SetBranchAddress("peak_y", &peak_y, &b_peak_y);
   fChain->SetBranchAddress("peak_45", &peak_45, &b_peak_45);
   fChain->SetBranchAddress("bgr_to_peak_x", &bgr_to_peak_x, &b_bgr_to_peak_x);
   fChain->SetBranchAddress("bgr_to_peak_y", &bgr_to_peak_y, &b_bgr_to_peak_y);
   fChain->SetBranchAddress("bgr_to_peak_45", &bgr_to_peak_45, &b_bgr_to_peak_45);
   fChain->SetBranchAddress("counter", &counter, &b_counter);
   fChain->SetBranchAddress("a", &a, &b_a);
   fChain->SetBranchAddress("b", &b, &b_b);
   fChain->SetBranchAddress("alpha", &alpha, &b_alpha);
   Notify();
}

Bool_t Analyze_Harp_Scans::Notify()
{
   // The Notify() function is called when a new file is opened. This
   // can be either for a new TTree in a TChain or when when a new TTree
   // is started when using PROOF. It is normally not necessary to make changes
   // to the generated code, but the routine can be extended by the
   // user if needed. The return value is currently not used.

   return kTRUE;
}

void Analyze_Harp_Scans::Show(Long64_t entry)
{
// Print contents of entry.
// If entry is not specified, print current entry
   if (!fChain) return;
   fChain->Show(entry);
}
Int_t Analyze_Harp_Scans::Cut(Long64_t entry)
{
// This function may be called from Loop.
// returns  1 if entry is accepted.
// returns -1 otherwise.
   return 1;
}
#endif // #ifdef Analyze_Harp_Scans_cxx
