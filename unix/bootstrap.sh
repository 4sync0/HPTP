#!/bin/bash

MAGENTA="$(tput setaf 5)"
YELLOW="$(tput setaf 3)"
DEFAULT="$(tput sgr0)"


# if dockerfile found change dir during script timelapse
if [ "$HOME" = "/root" ]; then
    HOME=""
    trap "HOME=/root" EXIT
fi


root_dir="${HOME}/HPTP"
cd $root_dir

OS="$(head -n 3 /etc/os-release | grep -oP '(?<=ID=)\S+')" # regex ;~;

function task() {

    read -p "${MAGENTA}${1}    ${DEFAULT}" option

    if [ "$option" == "N" ] || [ "$option" == "n" ]
    then
        exit 0
    elif [ "$option" == "Y" ] || [ "$option" == "y" ]
    then
        echo -e "${YELLOW}${2}${DEFAULT}"
    else
        exit 1

    fi
}

function compile() {
    cd build/
    cmake -B ${HOME}/HPTP/build/ -S ${HOME}/HPTP/
    make

    echo "${YELLOW}Succesfully compiled HPTP. Exitting bootstrap ${DEFAULT}"
    exit 0
}


function vcpkgInstall() {
    echo "${YELLOW}Setting up vcpkg ${DEFAULT}"

    git clone https://github.com/Microsoft/vcpkg.git
    ./vcpkg/bootstrap-vcpkg.sh
    vcpkg install Poco
    vcpkg install Boost

    task "installed dependencies succesfully, automatically compile HPTP? Y/N" "Compiling HPTP..."
    compile

}


function dependencies() {
    if [[ "$OS" == ${1} ]]
    then
        $2 git
        $2 gcc
        $2 vcpkg
        $2 CMake

        echo -e "${YELLOW}Installed dependencies succesfully ${DEFAULT}"
        vcpkgInstall
    fi
}


task "unix bootstrap for HPTP, proceed? Y/N" "--proceeding with HPTP installation--"

echo -e """${YELLOW}
dependencies installation list:
    - Vcpkg dependencies (git and gcc)
    - Vcpkg
    - Poco (vcpkg)
    - Boost (vcpkg)
    - CMake
${DEFAULT}"""

sleep 1

task "continue with the installation? Y/N" "Installing dependencies..."


dependencies fedora "sudo dnf install"
dependencies debian "sudo apt-get install"
dependencies ubuntu "sudo apt-get install"
dependencies arch "sudo pacman -S"
dependencies opensuse-tumbleweed "sudo zypper install"
dependencies alpine "sudo apk add"
dependencies centos "sudo dnf install"
dependencies linuxmint "sudo apt-get install"
dependencies pop "sudo apt-get install"

echo -e "${YELLOW}your distribution doesn't seem to be covered by the script, please provide the command to install packages (main package manager ex; dnf install for fedora) ${DEFAULT}"
echo -e "${YELLOW}make sure the package manager provides those dependencies ${DEFAULT}"

read -p "-> " cmd

dependencies $OS "sudo ${cmd}"