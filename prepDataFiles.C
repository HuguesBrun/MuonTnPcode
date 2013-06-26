

nbOfFit = 1;

TString thePath = ".";
TString kind;
prepDataFiles(){

	int myIndex;	
	
	TSystemDirectory dir(thePath, thePath);
	TSystemFile *file;
	TString fname;
	TIter next(dir.GetListOfFiles());
	while ((file=(TSystemFile*)next())) {
		fname = file->GetName();
		if (fname.BeginsWith("TnP")&& fname.Contains("mc")) {
	
			cout << "theName " << fname << endl;
			ofstream myfile;

			TFile *myFile = new TFile(fname);
			TIter nextkey(myFile->GetListOfKeys());
			TKey *key;
			while (key = (TKey*)nextkey()) {
				TString theTypeClasse = key->GetClassName();
				TString theNomClasse = key->GetTitle();
				if ( theTypeClasse == "TDirectoryFile"){
					TDirectory *theDr = (TDirectory*) myFile->Get(theNomClasse);
					TIter nextkey2(theDr->GetListOfKeys());
					TKey *key2;
					while (key2 = (TKey*)nextkey2()) {
						TString theTypeClasse2 = key2->GetClassName();
						TString theNomClasse2 = key2->GetTitle();	
						myfile.open (theNomClasse2+".info");
						if ( theTypeClasse == "TDirectoryFile"){
							TDirectory *theDr2 = (TDirectory*) myFile->Get(theNomClasse+"/"+theNomClasse2);
							TIter nextkey3(theDr2->GetListOfKeys());
							TKey *key3;
							while (key3 = (TKey*)nextkey3()) {
								TString theTypeClasse3 = key3->GetClassName();
								TString theNomClasse3 = key3->GetTitle();	
								cout << "type = " << theTypeClasse3 << " nom = " << theNomClasse3 << endl;
								if ((theNomClasse3.Contains("FromMC"))) {
                                    TString localClasse3 = theNomClasse3;
									localClasse3.ReplaceAll("__","%");
									cout << "apres " << localClasse3 << endl;
									TObjArray* listBin = localClasse3.Tokenize('%');
									TString first = ((TObjString*)listBin->At(0))->GetString();
									TString second = ((TObjString*)listBin->At(2))->GetString();
									myfile << first;
									myfile << " " << second << " ";
                                    RooFitResult *theResults = (RooFitResult*) myFile->Get(theNomClasse+"/"+theNomClasse2+"/"+theNomClasse3+"/fitresults");
									theResults->Print();
									RooArgList theParam = theResults->floatParsFinal();
									int taille = theParam.getSize();
									for (int m = 0 ; m < taille ; m++){
										cout << "m=" << m << endl;
									RooAbsArg *theArg = (RooAbsArg*) theParam.at(m);
									RooAbsReal *theReal = (RooAbsReal*) theArg;
										myfile << theReal->getVal() << " " ;
									}		
												
									myfile << "\n";
								}
							}
						}
						myfile.close();

					}
			
				}
			}
			delete myFile;
		}
	
	}

}
