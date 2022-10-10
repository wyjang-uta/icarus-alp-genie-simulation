#!/bin/bash

# this is a script to run GENIE-MC simulation
# -n is number of events to be simulated.
# -f is flux description file (standard ROOT file). Format is <root filename>,<histogram name>
# -p is incoming particle id by PDG code.
#     12 is for nue
#    -12 is for nuebar
#     14 is for numu
#    -14 is for numubar
# -t is target material PDG code. 1000180400 is for LAr.
# -o is to specify output filename.

GENIECMD=gevgen

# default parameters
NEVENT=1000000
ELOW=0
EHIGH=20
FLUXFILE=ICARUS_FLUX.root
FLUXHIST=ICARUS_FHC_numu
BEAMPDGCODE=14
TARGETPDGCODE=1000180400
OUTFILE=gnout.ICARUS_FHC_1M_numu.root
RUN=1
SEED=1
XSECPATH=/wyjang/sw/genie/3.02.00/x86_64-fc35-gnu/genie_xsec/v3_02_00/NULL/G1802a00000-k250-e1000/data/gxspl-NUsmall.xml
GENIECMD="time gevgen -n $NEVENT -e $ELOW,$EHIGH -f $FLUXFILE,$FLUXHIST -p $BEAMPDGCODE -t $TARGETPDGCODE -o $OUTFILE --run $RUN --seed $SEED --cross-sections $XSECPATH"

if [ $# -gt 0 ] ; then
  if [ ! $# -eq 8 ] ; then
    echo "This program requires 8 input parameters."
  else
    NEVENT=$1
    ELOW=$2
    EHIGH=$3
    FLUXFILE=$4
    FLUXHIST=$5
    BEAMPDGCODE=$6
    TARGETPDGCODE=$7
    OUTFILE=$8
    GENIECMD="time gevgen -n $NEVENT -e $ELOW,$EHIGH -f $FLUXFILE,$FLUXHIST -p $BEAMPDGCODE -t $TARGETPDGCODE -o $OUTFILE --run $RUN --seed $SEED --cross-sections $XSECPATH"
    echo $GENIECMD
    $GENIECMD
  fi
else
  echo "Start GENIE-MC with default parameter sets"
  echo $GENIECMD
  $GENIECMD
fi
