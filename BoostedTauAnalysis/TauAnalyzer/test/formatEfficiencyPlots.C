{
  //initial
  gROOT->Reset();

  //get CMSSW path
  const char* CMSSWPathCString = gSystem->Getenv("CMSSW_BASE");
  if (!CMSSWPathCString) {
    CMSSWPathCString = "";
    cout << "Error: environment variable CMSSW_BASE is not set.  ";
    cout << "Please run cmsenv from within your CMSSW project area.\n";
  }
  string CMSSWPathCPPString(CMSSWPathCString);

  //load
  string macroPath(CMSSWPathCPPString + "/src/BoostedTauAnalysis/TauAnalyzer/test/");
  gROOT->ProcessLine("#include <utility>");
  gSystem->Load((macroPath + "STLDictionary.so").c_str());
  gROOT->LoadMacro((macroPath + "Plot.C++").c_str());
//   gSystem->Load((macroPath + "Plot_C.so").c_str());

  //needed so vector<Color_t> and vector<Style_t> work
  vector<short> dummy;

  //unit strings
  string unitPT("p_{T} (GeV)");
  string unitPTTau("Reco #tau p_{T} (GeV)");
  string unitPTMu("Reco #mu p_{T} (GeV)");
  string unitEta("#eta");
  string unitEtaTau("Reco #tau #eta");
  string unitEtaMu("Reco #mu #eta");
  string unitDR("#DeltaR(visible gen #tau, gen #mu)");
  string noUnit("");

  //map of bin labels for certain efficiency plots
  vector<string> binLabels;
  binLabels.push_back("kNull");
  binLabels.push_back("kOneProng0PiZero");
  binLabels.push_back("kOneProng1PiZero");
  binLabels.push_back("kOneProng2PiZero");
  binLabels.push_back("kOneProng3PiZero");
  binLabels.push_back("kOneProngNPiZero");
  binLabels.push_back("kTwoProng0PiZero");
  binLabels.push_back("kTwoProng1PiZero");
  binLabels.push_back("kTwoProng2PiZero");
  binLabels.push_back("kTwoProng3PiZero");
  binLabels.push_back("kTwoProngNPiZero");
  binLabels.push_back("kThreeProng0PiZero");
  binLabels.push_back("kThreeProng1PiZero");
  binLabels.push_back("kThreeProng2PiZero");
  binLabels.push_back("kThreeProng3PiZero");
  binLabels.push_back("kThreeProngNPiZero");
  binLabels.push_back("kRareDecayMode");
  map<string, vector<string> > binLabelMap;
  binLabelMap["muHadGenDecayMode"] = binLabels;
  binLabelMap["muHadCorrectRecoDecayModeGenDecayMode"] = binLabels;
  binLabelMap["muHadRecoDecayMode"] = binLabels;
  binLabelMap["muHadGen1ProngRecoDecayMode"] = binLabels;
  binLabelMap["muHadGen1Prong1Pi0RecoDecayMode"] = binLabels;
  binLabelMap["muHadGen3ProngRecoDecayMode"] = binLabels;

  //map of inputs to efficiency histograms
  map<string, pair<string, string> > effHistMap;
  effHistMap["numeratorPT"] = make_pair(string("denominatorPT"), unitPT);
  effHistMap["numeratorEta"] = make_pair(string("denominatorEta"), unitEta);
  map<string, pair<string, string> > effHistMapMu;
  effHistMapMu["numeratorPT"] = make_pair(string("denominatorPT"), unitPTMu);
  effHistMapMu["numeratorEta"] = make_pair(string("denominatorEta"), unitEtaMu);
  map<string, pair<string, string> > effHistMapTau;
  effHistMapTau["numeratorPT"] = make_pair(string("denominatorPT"), unitPTTau);
  effHistMapTau["numeratorEta"] = make_pair(string("denominatorEta"), unitEtaTau);

  //map of inputs to 1D histograms
  map<string, string> hist1DMap;
  hist1DMap["numeratorPT"] = unitPT;
  hist1DMap["denominatorPT"] = unitPT;
  hist1DMap["numeratorEta"] = unitEta;
  hist1DMap["denominatorEta"] = unitEta;
  map<string, string> hist1DMapMu;
  hist1DMapMu["numeratorPT"] = unitPTMu;
  hist1DMapMu["denominatorPT"] = unitPTMu;
  hist1DMapMu["numeratorEta"] = unitEtaMu;
  hist1DMapMu["denominatorEta"] = unitEtaMu;
  map<string, string> hist1DMapTau;
  hist1DMapTau["numeratorPT"] = unitPTTau;
  hist1DMapTau["denominatorPT"] = unitPTTau;
  hist1DMapTau["numeratorEta"] = unitEtaTau;
  hist1DMapTau["denominatorEta"] = unitEtaTau;

  //make individual efficiency plots for signal
  vector<string> effInputFiles;
  effInputFiles.push_back("../../GenMatchedRecoObjectProducer/test/HPSTauEff.root");
  effInputFiles.push_back("../../GenMatchedRecoObjectProducer/test/HPSTauPTEff.root");
  effInputFiles.push_back("../../GenMatchedRecoObjectProducer/test/HPSTauPTEtaDMFEff.root");
  effInputFiles.push_back("../../GenMatchedRecoObjectProducer/test/HPSTauPTEtaDMFIsoEff.root");
  effInputFiles.push_back("../../GenMatchedRecoObjectProducer/test/HPSTauPTEtaEff.root");
  effInputFiles.push_back("../../GenMatchedRecoObjectProducer/test/softMuEtaEff.root");
  effInputFiles.push_back("../../GenMatchedRecoObjectProducer/test/softMuPTEff.root");
  for (vector<string>::const_iterator iFile = effInputFiles.begin(); iFile != effInputFiles.end(); 
       ++iFile) {
    const unsigned int strLen = iFile->find(".root");
    const string outputFileName(iFile->substr(0, strLen) + "_final.root");
    plotNice(*iFile, effHistMap, binLabelMap, hist1DMap, outputFileName, "noPDF");
  }
}
