#!/bin/bash

ScripDir=$(dirname $(readlink -f $0))
cd "${ScripDir}/../BUILD"

echo ""

case "$1" in
	"GFX" )
		cd Src/GFX
		./GFXMain
		;;

	"GFXTest" )
		cd Src/buildTest
		./SDLTest
		;;

	"RunicTest" )
		cd Src/Runic
		./RunicTest
		;;
	*)
		echo $"Usage: $0 {GFX|GFXTest|RunicTest}"
		exit 1
esac
