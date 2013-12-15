#!/bin/sh


destDir=./
variable=Rapidity
sign=""
baseDir=/data/user/asincruz/CMSSW_5_3_11/src/TopAnalysis/Configuration/analysis/diLeptonic/Closure_MadSpinFullStats/PlotsY${sign}0.

# for slope in 000 002 004 006; do
for slope in 000 080 160 240 320; do
    for channel in ee emu mumu; do
#         echo "${baseDir}${slope}/Nominal/${channel}/DiffXS_HypTop${variable}.eps"
        cp "${baseDir}${slope}/Nominal/${channel}/DiffXS_HypTop${variable}.eps"  "${destDir}${channel}_DiffXS_HypTop${variable}${sign}0${slope}.eps"
        ps2pdf14 -dEPSCrop "${destDir}/${channel}_DiffXS_HypTop${variable}${sign}0${slope}.eps" "${destDir}/${channel}_DiffXS_HypTop${variable}${sign}0${slope}.pdf"
        echo "Created ${destDir}/${channel}_DiffXS_HypTop${variable}${sign}0${slope}.pdf"
        rm -f *.eps
    done
done




