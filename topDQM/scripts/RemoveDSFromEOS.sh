#! /bin/sh

source /afs/cern.ch/cms/caf/setup.sh

basepathpath="/eos/cms/store/group/comm_dqm/harvesting_output/mc/mc/"
release="6_0_1_PostLS1v2_patch3"
path=$basepathpath$release


for ds in `/afs/cern.ch/project/eos/installation/0.3.15/bin/eos.select ls ${path}`;do
    for run in `/afs/cern.ch/project/eos/installation/0.3.15/bin/eos.select ls ${path}/${ds}`;do
        for data in `/afs/cern.ch/project/eos/installation/0.3.15/bin/eos.select ls ${path}/${ds}/${run}/nevents`;do
            for file in `/afs/cern.ch/project/eos/installation/0.3.15/bin/eos.select ls ${path}/${ds}/${run}/nevents/${data}`;do
                echo
                echo ${path}/${ds}/${run}/nevents/${data}/${file}
                `/afs/cern.ch/project/eos/installation/0.3.15/bin/eos.select rm ${path}/${ds}/${run}/nevents/${data}/${file}`
            done
            echo
            echo ${path}/${ds}/${run}/nevents/${data}
            `/afs/cern.ch/project/eos/installation/0.3.15/bin/eos.select rmdir ${path}/${ds}/${run}/nevents/${data}`
        done
        echo
        echo ${path}/${ds}/${run}
        `/afs/cern.ch/project/eos/installation/0.3.15/bin/eos.select rmdir ${path}/${ds}/${run}/nevents`
        `/afs/cern.ch/project/eos/installation/0.3.15/bin/eos.select rmdir ${path}/${ds}/${run}`
    done
    echo 
    echo ${path}/${ds}
    `/afs/cern.ch/project/eos/installation/0.3.15/bin/eos.select rmdir ${path}/${ds}`
done