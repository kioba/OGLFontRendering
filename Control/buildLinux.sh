#!/bin/bash
#-x


################################################################################
### CMAKE part #################################################################
################################################################################
function GenerateCmake
{
	echo ""
	echo "=== Generating CMAKE =============================="
	echo ""
	cmake -DCMAKE_BUILD_TYPE=Debug -DBUILD_SHARED_LIBS=1 ..
}


################################################################################
### BUILD part #################################################################
################################################################################

function BuildTarget
{
	echo ""
	echo "=== Building project =============================="
	echo ""
	make
}


################################################################################
### UnitTest part ##############################################################
################################################################################

function UnitTest
{
	cd "${ScripDir}/../BUILD/Src"

	if [[ -f "Runic/RunicUnitTest" ]]; then
		echo ""
		echo "=== Runic UnitTest ================================"
		echo ""

		./Runic/RunicUnitTest
	fi

	if [[ -f "Ragna/RagnaUnitTest" ]]; then
		echo ""
		echo "=== Ragna UnitTest ================================"
		echo ""

		./Ragna/RagnaUnitTest
	fi
}


################################################################################
### main part ##################################################################
################################################################################

ScripDir=$(dirname $(readlink -f $0))
cd "${ScripDir}/.."
echo "${ScripDir}/.."

if [[ ! -d "BUILD" ]]; then
	mkdir BUILD
	echo "=== BUILD folder created! ==="
fi

cd BUILD/

for i in "$@"
do
	case "$i" in
		-c|CMAKE)
			GenerateCmake
			# shift # past argument=value
			;;
		-b|BUILD)
			BuildTarget
			# shift # past argument=value
			;;

		-u|UNITTEST)
			UnitTest
			;;

		*)
			echo "what the hack?"		# unknown option
		;;
	esac
done



exit $?
