# RatioPlotRoot
## Creating histograms for the ratio between variables of electron and muon
irem.salk@hotmail.com

PT: Transverse momentum which is boost invariant part in other words x and y components of the momentum. <br />
Phi: Azimuthal angle that goes around the beam <br />
Eta: Pseudorapidity that defines as a geometric quantity. It is a function of polar angle θ which is the angle between the particle three-momentum p  and the positive direction of the beam axis that goes from ∞ to −∞ as θ goes from 0 to π.<br />

In this project, we compared variables of two particles those are pt, eta and phi values of electron and muon with the given data. <br />
We used Delphes and Root for this purpose. 


 TO RUN THIS FILE :<br />
           Open the Delphes folder on the terminal ex: cd Delphes-3.5.0
Start ROOT and load Delphes shared library: <br />
Open ROOT on the terminal then, <br />
           
           
           // root[0] gSystem->Load("libDelphes");
           // root [1]  .X Folder_Name/Ratio.C("events_PYTHIA8_0_1.root");
           
"events_PYTHIA8_0_1.root" file contains the data which we use in this analysis.



