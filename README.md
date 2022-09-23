UserCode
========

Alberto's UserCode area:

- HcalPedestalTuning

- LNuAA

- UMDMuonCaloInvestigation

- UtilityScripts

It is possible to download individual files from the repository (e.g., single utility scripts) with the following command:
```
wget https://raw.githubusercontent.com/albertobelloni/UserCode/master/PATH_TO_FILE/FILE_NAME```
```
Some details on the available scripts in UtilityScripts:

- `hepevt2root.py`

  option: `-i/--input <inputfilename>`

  Sherpa's default HepEVT output has the following structure:
  
    - each event starts with a line containing the event number and the number of particles in the event
    - the event line is followed by 3 lines for each particle: PDG id / mother / daughter; momentum; vertex

  The script massages the Sherpa output file into a file in which there are only single lines corresponding to the individual particles; the event line is copied at the beginning of each particle line. The output of the script is a very plain ROOT ntuple.