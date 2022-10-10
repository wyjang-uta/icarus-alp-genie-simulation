#!/bin/bash

./start.sh 100000 0 20 ICARUS_FLUX.root ICARUS_FHC_nue 12 1000180400 gnout.ICARUS_FHC_1M_nue.root
./start.sh 100000 0 20 ICARUS_FLUX.root ICARUS_FHC_nuebar -12 1000180400 gnout.ICARUS_FHC_1M_nuebar.root
./start.sh 100000 0 20 ICARUS_FLUX.root ICARUS_FHC_numu 14 1000180400 gnout.ICARUS_FHC_1M_numu.root
./start.sh 100000 0 20 ICARUS_FLUX.root ICARUS_FHC_numubar -14 1000180400 gnout.ICARUS_FHC_1M_numubar.root
./start.sh 100000 0 20 ICARUS_FLUX.root ICARUS_RHC_nue 12 1000180400 gnout.ICARUS_RHC_1M_nue.root
./start.sh 100000 0 20 ICARUS_FLUX.root ICARUS_RHC_nuebar -12 1000180400 gnout.ICARUS_RHC_1M_nuebar.root
./start.sh 100000 0 20 ICARUS_FLUX.root ICARUS_RHC_numu 14 1000180400 gnout.ICARUS_RHC_1M_numu.root
./start.sh 100000 0 20 ICARUS_FLUX.root ICARUS_RHC_numubar -14 1000180400 gnout.ICARUS_RHC_1M_numubar.root
