import ROOT
import sys
import getopt
from ROOT import TTree, TFile
from array import array

input = 'ppjj.hepevt'

def main(argv):

    global input

    try:
        opts, args = getopt.getopt(argv[1:],"i:","input=")
    except:
        print ("\nPass name of input file, with -i or --input options\n")
        sys.exit(2)

    for opt, arg in opts:
        if opt in ("-i", "--input"):
            input = arg

    infile = open(massage(input).name,'r')

    lines = infile.readlines()

    nev     = array('i',[0])
    npart   = array('i',[0])
    nhep    = array('i',[0])
    isthep  = array('i',[0])
    idhep   = array('i',[0])
    jmo1hep = array('i',[0])
    jmo2hep = array('i',[0])
    jda1hep = array('i',[0])
    jda2hep = array('i',[0])
    p1hep   = array('d',[0])
    p2hep   = array('d',[0])
    p3hep   = array('d',[0])
    p4hep   = array('d',[0])
    p5hep   = array('d',[0])
    v1hep   = array('d',[0])
    v2hep   = array('d',[0])
    v3hep   = array('d',[0])
    v4hep   = array('d',[0])
    
    file = TFile(input+".root","recreate")
    tree = TTree("t","hepevt2root")

    tree.Branch("nev"    ,nev    ,'nev/I')
    tree.Branch("npart"  ,npart  ,'npart/I')
    tree.Branch("nhep"   ,nhep   ,'nhep/I')
    tree.Branch("isthep" ,isthep ,'isthep/I')
    tree.Branch("idhep"  ,idhep  ,'idhep/I')
    tree.Branch("jmo1hep",jmo1hep,'jmo1hep/I')
    tree.Branch("jmo2hep",jmo2hep,'jmo2hep/I')
    tree.Branch("jda1hep",jda1hep,'jda1hep/I')
    tree.Branch("jda2hep",jda2hep,'jda2hep/I')
    tree.Branch("p1hep"  ,p1hep  ,'p1hep/D')
    tree.Branch("p2hep"  ,p2hep  ,'p2hep/D')
    tree.Branch("p3hep"  ,p3hep  ,'p3hep/D')
    tree.Branch("p4hep"  ,p4hep  ,'p4hep/D')
    tree.Branch("p5hep"  ,p5hep  ,'p5hep/D')
    tree.Branch("v1hep"  ,v1hep  ,'v1hep/D')
    tree.Branch("v2hep"  ,v2hep  ,'v2hep/D')
    tree.Branch("v3hep"  ,v3hep  ,'v3hep/D')
    tree.Branch("v4hep"  ,v4hep  ,'v4hep/D')
    
    
    for line in lines:
        entries = line.split()
        
        if len(entries)!=18:
            print ("Some problem? Too few elements in line...\n")
            print (line)
            break;
            
        nev[0]     = int(entries[0])
        npart[0]   = int(entries[1])
        nhep[0]    = int(entries[2])
        isthep[0]  = int(entries[3])
        idhep[0]   = int(entries[4])
        jmo1hep[0] = int(entries[5])
        jmo2hep[0] = int(entries[6])
        jda1hep[0] = int(entries[7])
        jda2hep[0] = int(entries[8])
        p1hep[0]   = float(entries[9])
        p2hep[0]   = float(entries[10])
        p3hep[0]   = float(entries[11])
        p4hep[0]   = float(entries[12])
        p5hep[0]   = float(entries[13])
        v1hep[0]   = float(entries[14])
        v2hep[0]   = float(entries[15])
        v3hep[0]   = float(entries[16])
        v4hep[0]   = float(entries[17])
            
        tree.Fill()
            
    file.Write()
    file.Close()

def massage(input):

    outfile = open(input+'.massaged','w')

    with open(input) as file:
        content = file.readlines()
        evn = -999
        npart = -999
        nev = 0

        # get the first line separately, cannot seem to be able
        # to get this fixed...
        evn = content[0].split()[0]
        npart = content[0].split()[1]
        #nev = nev + 1
        for i in range(1, len(content)):

            if len(content[i].split())==2:
                evn = content[i].split()[0]
                npart = content[i].split()[1]
                nev = nev + 1
                continue;

            if (i-nev) % 3 == 0: 

                outfile.write('{} {}'.format(evn,npart) + " " + \
                              content[i-2].strip() + " " + \
                              content[i-1].strip() + " " + \
                              content[i].strip() + '\n')
                
    outfile.close()

    return outfile

if __name__ == '__main__':
    main(sys.argv)

