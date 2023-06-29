#!/bin/bash

TARGET_OS='debian'
TARGET_VERSION='11'

msg() {
    echo "${COLOR_BG_GREEN}${COLOR_FG_BLACK}>> $*${COLOR_RESET}" >&2
}

info() {
    echo "${COLOR_BG_CYAN}${COLOR_FG_BLACK}-- $*${COLOR_RESET}" >&2
}

warning() {
    echo "${COLOR_BG_YELLOW}${COLOR_FG_BLACK}?? WARNING: $*${COLOR_RESET}" >&2
}

error() {
    echo "${COLOR_BG_RED}${COLOR_FG_BLACK}!! ERROR: $1${COLOR_RESET}" >&2
    exit "${2:-126}"
}

yorn() {
    if tty -s; then
        echo -n -e "$* Y\b" > /dev/tty
        read -r yorn < /dev/tty
        case $yorn in
            [Nn]* ) return 1;;
        esac
    fi
    return 0
}

install_git() {
    if [ -n "$(type -P git)" ]; then
        return
    fi

    apt-get update -qq && apt-get -o Dpkg::Progress-Fancy="1" install -y git
}

core3_find_tre_path() {
    local file=""

    if [ -z "$1" ]; then
        # Quick search 
        info "Trying quick search for tre files..."
        local file=$(ls /mnt/?/*/patch_sku1_14_00.tre 2> /dev/null)

        if [ -f "${file}" ]; then
            dirname "${file}"
            return 0
        fi

        # Slower
        info "Trying slower search for tre files..."
        for file in /mnt/?/*/*/patch_sku1_14_00.tre /mnt/?/*/*/SWGEmu/patch_sku1_14_00.tre
        do
            if [ -f "${file}" ]; then
                dirname "${file}"
                return 0
            fi
        done
    fi

    # Ask the user
    info "Using file dialog to get path..."
    path=$(powershell.exe -NoLogo -NonInteractive -NoProfile -Command - << '    EOF' | tr -d '\r'
        function prompt { }
        Function Get-FileName($initialDirectory)
        {
         [System.Reflection.Assembly]::LoadWithPartialName("System.windows.forms") | Out-Null
         $Form = New-Object System.Windows.Forms.OpenFileDialog
         $Form.initialDirectory = $initialDirectory
         $Form.filter = "SWG TRE File| patch_sku1_14_00.tre"
         $Form.title = "Pick one TRE File to copy all tre files"
         $Form.ShowDialog() | Out-Null
         $Form.filename
        } #end function Get-FileName

        Get-FileName -initialDirectory "c:fso"
    EOF
    )

    if [ -n "${path}" ]; then
        file=$(wslpath -u "${path}" 2> /dev/null)

        if [ -f "${file}" ]; then
            dirname "${file}"
            return 0
        fi
    fi

    return 1
}

core3_check_tre_files() {
    local path="$1"

    for filename in "${trefiles[@]}"
    do
        local file="${path}/${filename}"
        if [ ! -f "${file}" ]; then
            warning "Missing TRE file ${file} in ${path}, not using this path."
            return 1
        fi
    done

    return 0
}

core3_copy_tre_files() {
    if core3_check_tre_files "/tre"; then
        msg "/tre files already installed."
        return
    fi

    msg "Searching for your Star Wars Galaxies TRE files."
    info "In order to run the server you must copy required '.tre' files from the windows client."
    info "If you've installed the client on this computer we can copy them for you."

    local path=""
    local prompt=""

    while :
    do
        local path=$(core3_find_tre_path "${prompt}")

        if [ -n "${path}" ] && core3_check_tre_files "${path}"; then
            break
        fi

        if [ "${prompt}" ]; then
            warning "Failed to find TRE file path, the server will not run until you copy them to /tre/"
            return
        fi

        prompt="--prompt"
    done

    info "Copying tre files from ${path} to /tre"
    mkdir -p /tre
    cp -v "${path}"/*.tre /tre || error "Failed to copy tre files from ${path}" 30
    chown -R "${RUN_USER}":"${RUN_USER}" "/tre"
    chmod 775 /tre
    msg "Copied tre files from ${path} to /tre"
}

core3_find_run_user() {
    msg "Looking for RUN_USER.."
    local match=''
    for user in $(awk -F':' '$3 > 999 && $3 < 60000 { print $1 }' /etc/passwd)
    do
        if [ -z "${match}" ]; then
            match="${user}"
        else
            warning "Found more than one user with uid > 999 and < 60000 (${match} vs ${user})"
            match=''
            break
        fi
    done

    if [ -n "${match}" ]; then
        msg "Found user: ${COLOR_BG_YELLOW}${match}"
        yorn "Do you want to use ${user} as the RUN_USER for the server?" ||
            error "Please set RUN_USER before running this script: export RUN_USER='someuser'" 130

        export RUN_USER="${match}"
    fi
}

core3_init_system() {
    local src="${HOME_DIR}/workspace/Core3/docker/Dockerfile"

    if [ ! -f "${src}" ]; then
        warning "Unable to find ${src}, skipping system setup."
        return
    fi

    # use docker/Dockerfile as template to initialize packages and setup
    (
        trap 'rm -f /etc/apt/apt.conf.d/99fancy' EXIT
        echo "cd /;set -xe"
        sed -ne '/^RUN/,/^$/p' "${src}" | sed -e '/^RUN/d' -e 's/; \\//g' -e '/rm .*apt\//d' -e '/useradd /d'
        echo "exit 0"
    ) > /tmp/init_core3.sh

    msg "Running /tmp/init_core3.sh created from ${src}"
    SECONDS=0
    # Use source to keep passing all our vars, keep in a sub-shell to avoid pollution
    (source /tmp/init_core3.sh) || error "/tmp/init_core3.sh failed, RET=$?" 21
    msg "/tmp/init_core3.sh completed in ${SECONDS} second(s)."
}

core3_save_env() {
    env |
    grep -Ev '^SHELL=|^PWD=|^LOGNAME=|^HOME=|^LANG=|^LS_COLORS=|^TERM=|^USER=|^SHLVL=|^PATH=|^MAIL=|^OLDPWD=|^_=' |
    sort |
    sed -e "s/=\(.*\)$/='\1'/" -e 's/^/export /' > "${HOME_DIR}"/.env
    chown "${RUN_USER}":"${RUN_USER}" "${HOME_DIR}"/.env
}

core3_bootstrap() {
    source /etc/os-release

    msg "OS: ${PRETTY_NAME}"

    [ "${ID}" == "${TARGET_OS}" ] || error "Sorry this script is designed for ${TARGET_OS} ${TARGET_VERSION} only." 101

    [ "${VERSION_ID}" == "${TARGET_VERSION}" ] || error "Current support is for ${TARGET_OS} ${TARGET_VERSION} only." 102

    [ "$(id -u)" == 0 ] || error "Must run as root." 103

    export WSL=$(type -P wsl.exe)

    if [ -n "${WSL}" ] && [ -x "${WSL}" ]; then
        info "** Running in Windows Susbsystem for Linux"
        wsl.exe --status
        eval "export RUN_USER=${USERNAME}"
        export ADMIN_PASS=''
        core3_copy_tre_files
    fi

    if [ -z "${RUN_USER}" ]; then
        core3_find_run_user
    fi

    [ -n "${RUN_USER}" ] || error "Unable to determine runtime user, please set RUN_USER and try again." 104

    eval "export HOME_DIR=~${RUN_USER}"

    [ -n "${HOME_DIR}" ] || error "Unable to find home dir for ${RUN_USER}" 105

    if [ ! -d /tre ]; then
        mkdir -vp /tre
        chown -R "${RUN_USER}":"${RUN_USER}" /tre
        chmod 775 /tre
        msg "Created /tre directory, you will need to copy client tre files here before you run the server."
    fi

    msg "Using ${RUN_USER} in ${HOME_DIR}"

    export REPO_PUBLIC_URL=${REPO_PUBLIC_URL:-'https://github.com/swgemu'}
    export REPO_PUBLIC_BRANCH=${REPO_PUBLIC_BRANCH:-'unstable'}

    echo -e 'Dpkg::Progress-Fancy "1";\nAPT::Color "1";' > /etc/apt/apt.conf.d/99fancy

    install_git

    if [ ! -d "${HOME_DIR}" ]; then
        info "Creating ${HOME_DIR}"
        mkdir -p "${HOME_DIR}"
        chown -R "${RUN_USER}":"${RUN_USER}" "${HOME_DIR}"
    fi

    msg "Pulling firstboot from official repo..."

    cd "${HOME_DIR}" || exit

    wget -qO /tmp/firstboot https://raw.githubusercontent.com/swgemu/Core3/unstable/docker/files/firstboot/functions ||
        error "Failed to download firstboot setup. GET HELP." 103

    msg "Loading firstboot functions..."
    source /tmp/firstboot

    if [ ! -d "${HOME_DIR}/workspace/Core3" ]; then
        (
        git config --global --add safe.directory "${HOME_DIR}/workspace/Core3"
        trap 'rm -vf $HOME/.gitconfig' EXIT HUP INT QUIT
        msg "Cloning Core3:${REPO_PUBLIC_BRANCH} from ${REPO_PUBLIC_URL}..."
        core3_clone
        )
    fi

    [ -d "${HOME_DIR}/workspace/Core3/.git" ] || error "Core3 clone failed?" 104

    (core3_init_system) || error "core3_init_system failed." 105

    mkdir -p /firstboot

    mount --bind "${HOME_DIR}/workspace/Core3/docker/files/firstboot" /firstboot ||
        error "Failed to bind mount /firstboot" 106

    trap "umount /firstboot;rmdir /firstboot;rm -f /etc/apt/apt.conf.d/99fancy" EXIT HUP INT QUIT

    local init_sql=true

    if [ -f "${HOME_DIR}/.my.cnf" ]; then
        init_sql=false
        local host port user password
        eval "$(export HOME="${HOME_DIR}";mysql --print-defaults | tail +2l | tr " " "\n" | sed -e '/^$/d' -e 's/--//' -e 's/=/="/' -e 's/$/"/' -e 's/^/local /')"
        export DBHOST="${host}"
        export DBPORT="${port}"
        export DBUSER="${user}"
        export DBPASS="${password}"
        info "Using existing DB settings... mysql://${DBUSER}:${DBPASS}@${DBHOST}:${DBPORT}/"
    fi

    core3_init_env

    core3_init_home

    $init_sql && core3_mysql_setup

    core3_init_config

    core3_save_env

    chown -R "${RUN_USER}":"${RUN_USER}" "${HOME_DIR}"

    chown -R mysql:mysql /var/lib/mysql/.

    echo "${COLOR_BG_GREEN}${COLOR_FG_BLACK}"
    cat <<"    EOF"

    ######  ####### #     # ####### 
    #     # #     # ##    # #       
    #     # #     # # #   # #       
    #     # #     # #  #  # #####   
    #     # #     # #   # # #       
    #     # #     # #    ## #       
    ######  ####### #     # ####### 
    EOF
    echo "${COLOR_RESET}"

    if [ -n "${ADMIN_PASS}" ]; then
        msg "Password for root and ${RUN_USER} is '${COLOR_BG_YELLOW}${ADMIN_PASS}${COLOR_RESET}'"
    fi

    msg "Database password is ${COLOR_BG_YELLOW}${DBPASS}${COLOR_RESET}"
    msg "Check ${HOME_DIR}/.env for other settings."

    if [ -z "${WSL}" ]; then
        echo
        msg "Please logout of all your shells to this server and re-login as ${RUN_USER} to make sure your environment is properly setup."
    fi

    if ! core3_check_tre_files "/tre"; then
        echo
        warning "You still need to copy the client *.tre files to /tre to run the server."
    fi

    echo
    msg "When you login as ${RUN_USER} there are a couple scripts to make things easy:"
    msg "    build - Build the server from source in ${HOME_DIR}/workspace/Core3"
    msg "    run - Run the server in ${HOME_DIR}/workspace/Core3/MMOCoreORB/bin"
}

ESC=$(printf "\033")
export COLOR_FG_BLACK="${ESC}[30m"
export COLOR_FG_RED="${ESC}[31m"
export COLOR_FG_GREEN="${ESC}[32m"
export COLOR_FG_YELLOW="${ESC}[33m"
export COLOR_FG_BLUE="${ESC}[34m"
export COLOR_FG_PURPLE="${ESC}[35m"
export COLOR_FG_CYAN="${ESC}[36m"
export COLOR_FG_WHITE="${ESC}[37m"
export COLOR_BG_RED="${ESC}[41m"
export COLOR_BG_GREEN="${ESC}[42m"
export COLOR_BG_YELLOW="${ESC}[43m"
export COLOR_BG_BLUE="${ESC}[44m"
export COLOR_BG_PURPLE="${ESC}[45m"
export COLOR_BG_CYAN="${ESC}[46m"
export COLOR_BG_WHITE="${ESC}[47m"
export COLOR_RESET="${ESC}[0m"

declare -a trefiles
trefiles=('bottom.tre' 'data_animation_00.tre' 'data_music_00.tre' 'data_other_00.tre' 'data_sample_00.tre' 'data_sample_01.tre' 'data_sample_02.tre' 'data_sample_03.tre' 'data_sample_04.tre' 'data_skeletal_mesh_00.tre' 'data_skeletal_mesh_01.tre' 'data_sku1_00.tre' 'data_sku1_01.tre' 'data_sku1_02.tre' 'data_sku1_03.tre' 'data_sku1_04.tre' 'data_sku1_05.tre' 'data_sku1_06.tre' 'data_sku1_07.tre' 'data_static_mesh_00.tre' 'data_static_mesh_01.tre' 'data_texture_00.tre' 'data_texture_01.tre' 'data_texture_02.tre' 'data_texture_03.tre' 'data_texture_04.tre' 'data_texture_05.tre' 'data_texture_06.tre' 'data_texture_07.tre' 'default_patch.tre' 'patch_00.tre' 'patch_01.tre' 'patch_02.tre' 'patch_03.tre' 'patch_04.tre' 'patch_05.tre' 'patch_06.tre' 'patch_07.tre' 'patch_08.tre' 'patch_09.tre' 'patch_10.tre' 'patch_11_00.tre' 'patch_11_01.tre' 'patch_11_02.tre' 'patch_11_03.tre' 'patch_12_00.tre' 'patch_13_00.tre' 'patch_14_00.tre' 'patch_sku1_12_00.tre' 'patch_sku1_13_00.tre' 'patch_sku1_14_00.tre')

echo "${COLOR_BG_BLUE}${COLOR_FG_BLACK}"
cat <<EOF

######  ####### ####### #######  #####  ####### ######     #    ######  
#     # #     # #     #    #    #     #    #    #     #   # #   #     # 
#     # #     # #     #    #    #          #    #     #  #   #  #     # 
######  #     # #     #    #     #####     #    ######  #     # ######  
#     # #     # #     #    #          #    #    #   #   ####### #       
#     # #     # #     #    #    #     #    #    #    #  #     # #       
######  ####### #######    #     #####     #    #     # #     # #       
                 #####  ####### ######  #######  #####  
                #     # #     # #     # #       #     # 
                #       #     # #     # #             # 
                #       #     # ######  #####    #####  
                #       #     # #   #   #             # 
                #     # #     # #    #  #       #     # 
                 #####  ####### #     # #######  #####  
EOF
echo "${COLOR_RESET}"

core3_bootstrap

exit 0
