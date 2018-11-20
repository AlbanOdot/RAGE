# RAGE
*Really Awesome Graphique Engine. Small graphic engine developped because of reason*

Build instructions :

cd RAGE/Tools/OpenMesh-7.1/build

cmake .. -DCMAKE_INSTALL_PREFIX="THE ABSOLUTE PATH TO THE install SUBDIRECTORY"

make -j

make install

cd ../../..

mkdir Release

cd Release

cmake ..

make -j

The binany is in the bin folder

#Geometry
- (+ || *) = subdivide
- '-' = edge collapse
- _ = half edge collapse

#FXAA
- A = ON / OFF
- & = Show border
- (a|z) = minThreshold(--|++)
- (q|s) = maxThreshold(--|++)

#SSAO
- Z = ON / OFF
- (e|r) = radius(--|++)
- (d|f) = biais(--|++)

#BLOOM
- E = ON / OFF

#HDR
- (t|y) = exposure(--|++)
- (g|h) = gamma(--|++)



