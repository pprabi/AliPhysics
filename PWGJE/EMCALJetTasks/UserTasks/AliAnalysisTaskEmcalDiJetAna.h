#ifndef ALIANALYSISTASKEMCALDIJETANA_H
#define ALIANALYSISTASKEMCALDIJETANA_H

class TH1;
class TH2;
class TH3;
class TH3F;
class THnSparse;
class TClonesArray;
class TArrayI;
class AliAnalysisUtils;
class AliAnalysisManager;
class AliGenPythiaEventHeader;

#include "AliJetContainer.h"

#include "AliAnalysisTaskEmcalDiJetBase.h"

class AliAnalysisTaskEmcalDiJetAna : public AliAnalysisTaskEmcalDiJetBase {
 public:
  AliAnalysisTaskEmcalDiJetAna();
  AliAnalysisTaskEmcalDiJetAna(const char *name);
  virtual ~AliAnalysisTaskEmcalDiJetAna();

  void                        UserCreateOutputObjects();
  void                        Terminate(Option_t *option);

  //Setters
  void                        SetCorrelateTwoJets(Bool_t b)        { fDoTwoJets          = b;}
  void                        SetMatchFullCharged(Bool_t b)        { fDoMatchFullCharged = b;}


  //Getters
  Int_t                       GetPtTriggerBin(Double_t pt);

 protected:
  Bool_t                      Run()              ;
  void                        CorrelateJets(const Int_t type);
  void                        CorrelateTwoJets(const Int_t type);
  AliEmcalJet                *GetAssociatedJet(const Int_t iCont, AliEmcalJet *jetTrig);

  Bool_t                      FillHistograms()   ;
  void                        FillDiJetHistos(const AliEmcalJet *jet1 = 0, const AliEmcalJet *jet2 = 0, const Int_t mode = 0);
  Bool_t                      RetrieveEventObjects();

  void                        FillMatchFullChargedHistos(Int_t cFull,Int_t cCharged);
  Int_t                       MatchFullAndChargedJets(Int_t cFull, Int_t cCharged);

 private:
  Bool_t            fDoTwoJets;                           //  correlate trigger jet with leading jet in opposite hemisphere
  Bool_t            fDoMatchFullCharged;                  //  do full-charged matching histos
  TH2F             *fh2CentRhoCh;                         //! cent vs rho charged
  TH2F             *fh2CentRhoScaled;                     //! cent vs rho scaled
  TH3F             *fh3PtEtaPhiJetFull;                   //! pt,eta,phi of full jets
  TH3F             *fh3PtEtaPhiJetCharged;                //! pt,eta,phi of charged jets

  THnSparse        *fhnDiJetVarsFull;                     //! sparse with di-jet properties (full-full)
  THnSparse        *fhnDiJetVarsCh;                       //! sparse with di-jet properties (charged-charged)
  THnSparse        *fhnDiJetVarsFullCharged;              //! sparse with di-jet properties (full-charged)
  THnSparse        *fhnMatchingFullCharged;               //! sparse comparing full with matched charged jet
  TH3F             *fh3JetPtFullFractionDR;               //! full jet pt vs highest shared charged fraction vs DeltaR

  TH3F             *fh3DiJetKtNEFPtAssoc[4];              //! dijet kt vs NEF vs pTassoc for 4 trigger intervals


  AliAnalysisTaskEmcalDiJetAna(const AliAnalysisTaskEmcalDiJetAna&);            // not implemented
  AliAnalysisTaskEmcalDiJetAna &operator=(const AliAnalysisTaskEmcalDiJetAna&); // not implemented

  ClassDef(AliAnalysisTaskEmcalDiJetAna, 3) // dijet analysis task
};
#endif
