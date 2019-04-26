//////////////////////////////////////////////////////////
// This class has been automatically generated on
// Tue Apr 16 21:44:48 2019 by ROOT version 6.16/00
// from TChain Analyze_Beamline/
//////////////////////////////////////////////////////////

#ifndef Analyze_Beamline_h
#define Analyze_Beamline_h

#include <TROOT.h>
#include <TChain.h>
#include <TFile.h>

// Header file for the classes stored in the TTree if any.

class Analyze_Beamline {
public :
   TTree          *fChain;   //!pointer to the analyzed TTree or TChain
   Int_t           fCurrent; //!current Tree number in a TChain

// Fixed size dimensions of array or collections stored in the TTree if any.

   // Declaration of leaf types
   Long64_t        Date;
   Float_t         IPM2C21A;
   Float_t         IPM2C21A_XPOS;
   Float_t         IPM2C21A_YPOS;
   Float_t         IPM2C24A;
   Float_t         IPM2C24A_XPOS;
   Float_t         IPM2C24A_YPOS;
   Float_t         IPM2H00_XPOS;
   Float_t         IPM2H00_YPOS;
   Float_t         IPM2H01;
   Float_t         IPM2H01_XPOS;
   Float_t         IPM2H01_YPOS;
   Float_t         scaler_calc1;
   Float_t         scaler_calc1b;
   Float_t         scalerS2b;
   Float_t         scalerS16b;
   Float_t         scaler_cS3b;
   Float_t         scaler_cS4b;
   Float_t         scaler_cS5b;
   Float_t         scaler_cS6b;
   Float_t         scaler_cS7b;
   Float_t         scalerS8b;
   Float_t         scalerS9b;
   Float_t         scalerS10b;
   Float_t         scalerS11b;
   Float_t         scalerS12b;
   Float_t         scalerS13b;
   Float_t         scalerS14b;
   Float_t         scalerS15b;
   Float_t         bom_sc_ai_0;
   Float_t         bom_sc_ai_1;
   Float_t         bom_sc_ai_2;
   Float_t         bom_sc_ai_3;
   Float_t         bom_sc_ai_4;
   Float_t         bom_sc_ai_5;
   Float_t         bom_sc_ai_6;
   Float_t         bom_sc_ai_7;
   Float_t         bom_sc_ai_8;
   Float_t         bom_sc_ai_9;
   Float_t         bom_sc_ai_10;
   Float_t         bom_sc_ai_11;
   Float_t         bom_sc_ai_12;
   Float_t         bom_sc_ai_13;
   Float_t         bom_sc_ai_14;
   Float_t         bom_sc_ai_15;
   Float_t         scaler_dS14b;
   Float_t         scaler_dS12b;
   Float_t         scaler_dS13b;

   // List of branches
   TBranch        *b_Date;   //!
   TBranch        *b_IPM2C21A;   //!
   TBranch        *b_IPM2C21A_XPOS;   //!
   TBranch        *b_IPM2C21A_YPOS;   //!
   TBranch        *b_IPM2C24A;   //!
   TBranch        *b_IPM2C24A_XPOS;   //!
   TBranch        *b_IPM2C24A_YPOS;   //!
   TBranch        *b_IPM2H00_XPOS;   //!
   TBranch        *b_IPM2H00_YPOS;   //!
   TBranch        *b_IPM2H01;   //!
   TBranch        *b_IPM2H01_XPOS;   //!
   TBranch        *b_IPM2H01_YPOS;   //!
   TBranch        *b_scaler_calc1;   //!
   TBranch        *b_scaler_calc1b;   //!
   TBranch        *b_scalerS2b;   //!
   TBranch        *b_scalerS16b;   //!
   TBranch        *b_scaler_cS3b;   //!
   TBranch        *b_scaler_cS4b;   //!
   TBranch        *b_scaler_cS5b;   //!
   TBranch        *b_scaler_cS6b;   //!
   TBranch        *b_scaler_cS7b;   //!
   TBranch        *b_scalerS8b;   //!
   TBranch        *b_scalerS9b;   //!
   TBranch        *b_scalerS10b;   //!
   TBranch        *b_scalerS11b;   //!
   TBranch        *b_scalerS12b;   //!
   TBranch        *b_scalerS13b;   //!
   TBranch        *b_scalerS14b;   //!
   TBranch        *b_scalerS15b;   //!
   TBranch        *b_bom_sc_ai_0;   //!
   TBranch        *b_bom_sc_ai_1;   //!
   TBranch        *b_bom_sc_ai_2;   //!
   TBranch        *b_bom_sc_ai_3;   //!
   TBranch        *b_bom_sc_ai_4;   //!
   TBranch        *b_bom_sc_ai_5;   //!
   TBranch        *b_bom_sc_ai_6;   //!
   TBranch        *b_bom_sc_ai_7;   //!
   TBranch        *b_bom_sc_ai_8;   //!
   TBranch        *b_bom_sc_ai_9;   //!
   TBranch        *b_bom_sc_ai_10;   //!
   TBranch        *b_bom_sc_ai_11;   //!
   TBranch        *b_bom_sc_ai_12;   //!
   TBranch        *b_bom_sc_ai_13;   //!
   TBranch        *b_bom_sc_ai_14;   //!
   TBranch        *b_bom_sc_ai_15;   //!
   TBranch        *b_scaler_dS14b;   //!
   TBranch        *b_scaler_dS12b;   //!
   TBranch        *b_scaler_dS13b;   //!

   Analyze_Beamline(TTree *tree=0);
   virtual ~Analyze_Beamline();
   virtual Int_t    Cut(Long64_t entry);
   virtual Int_t    GetEntry(Long64_t entry);
   virtual Long64_t LoadTree(Long64_t entry);
   virtual void     Init(TTree *tree);
   virtual void     Loop();
   virtual Bool_t   Notify();
   virtual void     Show(Long64_t entry = -1);
};

#endif

#ifdef Analyze_Beamline_cxx
Analyze_Beamline::Analyze_Beamline(TTree *tree) : fChain(0) 
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
      f->GetObject("Analyze_Beamline",tree);

#else // SINGLE_TREE

      // The following code should be used if you want this class to access a chain
      // of trees.
      TChain * chain = new TChain("Analyze_Beamline","");
      chain->Add("../Data/Beamline_PVs_Sep_28_Dec_29_2018.root/tr1");
      tree = chain;
#endif // SINGLE_TREE

   }
   Init(tree);
}

Analyze_Beamline::~Analyze_Beamline()
{
   if (!fChain) return;
   delete fChain->GetCurrentFile();
}

Int_t Analyze_Beamline::GetEntry(Long64_t entry)
{
// Read contents of entry.
   if (!fChain) return 0;
   return fChain->GetEntry(entry);
}
Long64_t Analyze_Beamline::LoadTree(Long64_t entry)
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

void Analyze_Beamline::Init(TTree *tree)
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

   fChain->SetBranchAddress("Date", &Date, &b_Date);
   fChain->SetBranchAddress("IPM2C21A", &IPM2C21A, &b_IPM2C21A);
   fChain->SetBranchAddress("IPM2C21A_XPOS", &IPM2C21A_XPOS, &b_IPM2C21A_XPOS);
   fChain->SetBranchAddress("IPM2C21A_YPOS", &IPM2C21A_YPOS, &b_IPM2C21A_YPOS);
   fChain->SetBranchAddress("IPM2C24A", &IPM2C24A, &b_IPM2C24A);
   fChain->SetBranchAddress("IPM2C24A_XPOS", &IPM2C24A_XPOS, &b_IPM2C24A_XPOS);
   fChain->SetBranchAddress("IPM2C24A_YPOS", &IPM2C24A_YPOS, &b_IPM2C24A_YPOS);
   fChain->SetBranchAddress("IPM2H00_XPOS", &IPM2H00_XPOS, &b_IPM2H00_XPOS);
   fChain->SetBranchAddress("IPM2H00_YPOS", &IPM2H00_YPOS, &b_IPM2H00_YPOS);
   fChain->SetBranchAddress("IPM2H01", &IPM2H01, &b_IPM2H01);
   fChain->SetBranchAddress("IPM2H01_XPOS", &IPM2H01_XPOS, &b_IPM2H01_XPOS);
   fChain->SetBranchAddress("IPM2H01_YPOS", &IPM2H01_YPOS, &b_IPM2H01_YPOS);
   fChain->SetBranchAddress("scaler_calc1", &scaler_calc1, &b_scaler_calc1);
   fChain->SetBranchAddress("scaler_calc1b", &scaler_calc1b, &b_scaler_calc1b);
   fChain->SetBranchAddress("scalerS2b", &scalerS2b, &b_scalerS2b);
   fChain->SetBranchAddress("scalerS16b", &scalerS16b, &b_scalerS16b);
   fChain->SetBranchAddress("scaler_cS3b", &scaler_cS3b, &b_scaler_cS3b);
   fChain->SetBranchAddress("scaler_cS4b", &scaler_cS4b, &b_scaler_cS4b);
   fChain->SetBranchAddress("scaler_cS5b", &scaler_cS5b, &b_scaler_cS5b);
   fChain->SetBranchAddress("scaler_cS6b", &scaler_cS6b, &b_scaler_cS6b);
   fChain->SetBranchAddress("scaler_cS7b", &scaler_cS7b, &b_scaler_cS7b);
   fChain->SetBranchAddress("scalerS8b", &scalerS8b, &b_scalerS8b);
   fChain->SetBranchAddress("scalerS9b", &scalerS9b, &b_scalerS9b);
   fChain->SetBranchAddress("scalerS10b", &scalerS10b, &b_scalerS10b);
   fChain->SetBranchAddress("scalerS11b", &scalerS11b, &b_scalerS11b);
   fChain->SetBranchAddress("scalerS12b", &scalerS12b, &b_scalerS12b);
   fChain->SetBranchAddress("scalerS13b", &scalerS13b, &b_scalerS13b);
   fChain->SetBranchAddress("scalerS14b", &scalerS14b, &b_scalerS14b);
   fChain->SetBranchAddress("scalerS15b", &scalerS15b, &b_scalerS15b);
   fChain->SetBranchAddress("bom_sc_ai_0", &bom_sc_ai_0, &b_bom_sc_ai_0);
   fChain->SetBranchAddress("bom_sc_ai_1", &bom_sc_ai_1, &b_bom_sc_ai_1);
   fChain->SetBranchAddress("bom_sc_ai_2", &bom_sc_ai_2, &b_bom_sc_ai_2);
   fChain->SetBranchAddress("bom_sc_ai_3", &bom_sc_ai_3, &b_bom_sc_ai_3);
   fChain->SetBranchAddress("bom_sc_ai_4", &bom_sc_ai_4, &b_bom_sc_ai_4);
   fChain->SetBranchAddress("bom_sc_ai_5", &bom_sc_ai_5, &b_bom_sc_ai_5);
   fChain->SetBranchAddress("bom_sc_ai_6", &bom_sc_ai_6, &b_bom_sc_ai_6);
   fChain->SetBranchAddress("bom_sc_ai_7", &bom_sc_ai_7, &b_bom_sc_ai_7);
   fChain->SetBranchAddress("bom_sc_ai_8", &bom_sc_ai_8, &b_bom_sc_ai_8);
   fChain->SetBranchAddress("bom_sc_ai_9", &bom_sc_ai_9, &b_bom_sc_ai_9);
   fChain->SetBranchAddress("bom_sc_ai_10", &bom_sc_ai_10, &b_bom_sc_ai_10);
   fChain->SetBranchAddress("bom_sc_ai_11", &bom_sc_ai_11, &b_bom_sc_ai_11);
   fChain->SetBranchAddress("bom_sc_ai_12", &bom_sc_ai_12, &b_bom_sc_ai_12);
   fChain->SetBranchAddress("bom_sc_ai_13", &bom_sc_ai_13, &b_bom_sc_ai_13);
   fChain->SetBranchAddress("bom_sc_ai_14", &bom_sc_ai_14, &b_bom_sc_ai_14);
   fChain->SetBranchAddress("bom_sc_ai_15", &bom_sc_ai_15, &b_bom_sc_ai_15);
   fChain->SetBranchAddress("scaler_dS14b", &scaler_dS14b, &b_scaler_dS14b);
   fChain->SetBranchAddress("scaler_dS12b", &scaler_dS12b, &b_scaler_dS12b);
   fChain->SetBranchAddress("scaler_dS13b", &scaler_dS13b, &b_scaler_dS13b);
   Notify();
}

Bool_t Analyze_Beamline::Notify()
{
   // The Notify() function is called when a new file is opened. This
   // can be either for a new TTree in a TChain or when when a new TTree
   // is started when using PROOF. It is normally not necessary to make changes
   // to the generated code, but the routine can be extended by the
   // user if needed. The return value is currently not used.

   return kTRUE;
}

void Analyze_Beamline::Show(Long64_t entry)
{
// Print contents of entry.
// If entry is not specified, print current entry
   if (!fChain) return;
   fChain->Show(entry);
}
Int_t Analyze_Beamline::Cut(Long64_t entry)
{
// This function may be called from Loop.
// returns  1 if entry is accepted.
// returns -1 otherwise.
   return 1;
}
#endif // #ifdef Analyze_Beamline_cxx
