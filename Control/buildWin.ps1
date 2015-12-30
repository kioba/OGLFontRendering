#Must be the first statement in your script
Param(
		[Boolean]$c=$False,
		[Boolean]$b=$False,
		[Boolean]$u=$False
	)

################################################################################
###   FUNCTION: CMake   ########################################################
################################################################################

function CMake-Generation
{
	Param (
		$type
	)

	echo ""
	echo "======================================"
	echo "===== Generating $type Application ====="
	echo "======================================"
	echo ""

	cmake -G"Visual Studio 12" -DCMAKE_BUILD_TYPE=Debug -DBUILD_SHARED_LIBS=1 ..\..
}


################################################################################
###   FUNCTION: Build   ########################################################
################################################################################

function Build
{
	Param (
		$buildtype
	)

	echo ""
	echo "===================================="
	echo "===== Building $buildtype Application ====="
	echo "===================================="
	echo ""

	cd ..
	cmake --build $buildtype --use-stderr --config Debug
}


################################################################################
###   FUNCTION: UnitTest   #####################################################
################################################################################

function UnitTest
{
	Param (
		$path
	)

	cd $path

	If ((Test-Path -path "$path\Runic\Debug\RunicUnitTest.exe")) {
		echo ""
		echo "=== Runic Unit Test =============="
		echo ""

		.\Runic\Debug\RunicUnitTest.exe
	}

	If ((Test-Path -path "$path\Ragna\Debug\RagnaUnitTest.exe")) {
		echo ""
		echo "=== Ragna Unit Test =============="
		echo ""

		.\Ragna\Debug\RagnaUnitTest.exe
	}
}

################################################################################
###   MAIN   ###################################################################
################################################################################

$scriptPath = split-path -parent $MyInvocation.MyCommand.Definition
$sourcePath = "$scriptPath\.."

# sets the enviromental variable for SDL2
Set-Item Env:SDL2 "&scriptPath\cmake\SDL2-2.0.3-VC"

$buildtype = "x32"

cd "$sourcePath"
If (!(Test-Path -path "$sourcePath\BUILD")) {
	mkdir .\BUILD
	echo ""
}

cd .\BUILD

If (!(Test-Path -path "$sourcePath\BUILD\$buildtype")) {
	mkdir "$sourcePath\BUILD\$buildtype"
	echo ""
}

cd "$sourcePath\BUILD\$buildtype"

# cmake generation
If($c) {
	CMake-Generation -type $buildtype
}


# build
IF($b) {
	Build -buildtype $buildtype
}


# unit tests
IF ($u) {
	UnitTest -path "$sourcePath\BUILD\$buildtype\Src"
}

cd $scriptPath
